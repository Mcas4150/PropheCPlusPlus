

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "EnvelopeGenerator.h"
#include "FilterEngine.h"
#include "MoogFilter.h"
#include "Oscillator.h"
#include "maximilian.h"



class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast <SynthSound*>(sound) != nullptr;
    }


    using Setting = std::atomic<float>;
    
//  ======================  OSCILLATOR A======================
    void processFrequency (float currentFrequency)
    {
        auto freq = currentFrequency * (std::pow(2, pitchBendSetting + masterTuneSetting));
        osc1processedFrequency = getModulationMatrixOutput(freq, modOscAFreqSetting);
        osc2processedFrequency = getModulationMatrixOutput(freq, modOscBFreqSetting);
    }
    
    void setOscAParams(Setting* freq, Setting* oct, Setting* sawMode, Setting* squareMode, Setting* pW )
    {

        m_OscA.setFreq(*freq);
        m_OscA.setOct(*oct);
        m_OscA.setSawMode(*sawMode);
        m_OscA.setSquareMode(*squareMode);
        m_OscA.setPW(*pW);
    }


    double getOscAOutput(){
        return
        m_OscA.getSaw(osc1processedFrequency) + m_OscA.getSquare(osc1processedFrequency,getModulationMatrixOutput(m_OscA.getPWSetting(), modOscAPWSetting));
   
    }

//============OSCILLATOR B======================
    
    void setOscBParams(Setting* freq, Setting* oct, Setting* sawMode, Setting* squareMode, Setting* triangleMode, Setting* pW, Setting* loFreqMode)
    {
         m_OscB.setFreq(*freq);
         m_OscB.setOct(*oct);
         m_OscB.setSawMode(*sawMode);
         m_OscB.setSquareMode(*squareMode);
         m_OscB.setTriangleMode(*triangleMode);
         m_OscB.setPW(*pW);
         m_OscB.setLoFreq(*loFreqMode);
    }


    double getOsc2Output()
    {
        
        if (m_OscB.loFreqSetting != 0)
        {
         osc2processedFrequency = 15;
                        
        }
        
        return
        
        m_OscB.getSaw(osc2processedFrequency) + m_OscB.getTriangle(osc2processedFrequency) + m_OscB.getSquare(osc2processedFrequency, getModulationMatrixOutput(m_OscB.getPWSetting(), modOscBPWSetting));
        
        

    }

    
    //=========MIXER========================
    

    void setMixerParams(Setting* osc1Level, Setting* osc2Level, Setting* noiseLevel)
    {
        osc1LevelSetting = *osc1Level;
        osc2LevelSetting = *osc2Level;
        noiseLevelSetting = *noiseLevel;
    }
    
    
    double getMixerOutput()
    {
        return

        getOscAOutput() * osc1LevelSetting
        +
        getOsc2Output() * osc2LevelSetting
        +
        osc3.noise() * noiseLevelSetting;
    }
    

    //  ========AMPLIFIER====================================
    
    void setAmpEnvelope(Setting* attack, Setting* decay, Setting* sustain, Setting* release)
    {

        m_EG1.setAttackTime_mSec(attack);
        m_EG1.setDecayTime_mSec(decay);
        m_EG1.setSustainLevel(sustain);
        m_EG1.setReleaseTime_mSec(release);
        
    }
    

    //=========FILTER==========================
    

    void setFilterParams(Setting* cutoff, Setting* resonance, Setting* envAmt, Setting* keyAmt, Setting* attack, Setting* decay, Setting* sustain, Setting* release)
    {
        filterCutoffSetting = *cutoff;
        filterResonanceSetting = *resonance;
        filterEnvAmtSetting = *envAmt;
        filterKeyAmtSetting = *keyAmt;
        m_Filter1.setCutoff(*cutoff);
        m_Filter1.setResonance(*resonance);
        m_FilterEG.setAttackTime_mSec(attack);
        m_FilterEG.setDecayTime_mSec(decay);
        m_FilterEG.setSustainLevel(sustain);
        m_FilterEG.setReleaseTime_mSec(release);
    }
    
    double getFilterOutput()
    {
        auto filteredEnvelope = filterCutoffSetting * dFilterEGOut;
        double filterModulation = getModulationMatrixOutput(filteredEnvelope, modFilterSetting );
        return  filter1.lores(getMixerOutput(),  filterModulation , filterResonanceSetting);
                   
        
    }
    

    //=========LFO==========================

    void setLfoParams(Setting* rate, Setting* sawMode, Setting* triangleMode, Setting* squareMode)
    {
        lfoRateSetting =    *rate;
        lfoSawSetting = *sawMode;
        lfoTriangleSetting = *triangleMode;
        lfoSquareSetting = *squareMode;
    }

    
    double getLfoValue()
    {
        double SumSettings = lfoSawSetting + lfoTriangleSetting + lfoSquareSetting;
        double lfoValue = lfoRateSetting && SumSettings != 0 ?
        (
            (
               lfoSaw.saw(lfoRateSetting * lfoSawSetting)
               +
               lfoTriangle.triangle(lfoRateSetting * lfoTriangleSetting)
               +
               lfoSquare.square(lfoRateSetting * lfoSquareSetting)
            )
                /
            (
             SumSettings
            )
         )
        : 0;
        double modulatedValue = lfoValue * modAmtLfoSetting;
        return modulatedValue;
    }
    
    
//    double getOscBModValue()
//    {
//        return modAmtOscBSetting != 0 ? (  getOsc2Output()  * modAmtOscBSetting ) : 1;
//
//    }
    
   void setOscBModValue()
       {
           oscBModValue =  modAmtOscBSetting != 0 ? (  getOsc2Output()  * modAmtOscBSetting ) : 1;

       }

    double getFakeOscB()
    {
        return modAmtOscBSetting != 0 ? (  oscB.saw(5)  * modAmtOscBSetting ) : 1;
    }

    
        //=========MODULATION========================
    
    void setModMatrix (Setting* modAmtFilterEnv, Setting* modAmtLfo , Setting* modAmtOscB , Setting* modOscAFreqMode , Setting* modOscAPWMode , Setting* modOscBFreqMode , Setting* modOscBPWMode , Setting* modFilterMode)
    {
        modAmtFilterEnvSetting = *modAmtFilterEnv;
        modAmtOscBSetting = *modAmtOscB;
        modAmtLfoSetting = *modAmtLfo;
        modOscAFreqSetting = *modOscAFreqMode;
        modOscAPWSetting = *modOscAPWMode;
        modOscBFreqSetting = *modOscBFreqMode;
        modOscBPWSetting = *modOscBPWMode;
        modFilterSetting = *modFilterMode;
    };

    
    double getModulationMatrixOutput(double modulationParameter, int modulationSetting){
    
        return modulationParameter + (modulationParameter * getLfoValue() * getFakeOscB() * modulationSetting);
    }
    
    
    //=============    PITCH  WHEEL =============
        
    void setPitchBend (Setting* setting)
    {
//            pitchBendPosition = midiPitchWheel != 0 ? midiPitchWheel : *setting;
//            pitchBendSetting =  pitchBendPosition;
    }
        
    void pitchWheelMoved (int newPitchWheelValue) override
    {
        midiPitchWheel = (newPitchWheelValue-8191.5f)/8191.5f;
    }
        
        //=========GLIDE========================
        
    void setGlideParams(Setting* rate, Setting* mode)
    {
        glideRateSetting = *rate;
        glideModeSetting = *mode == -1.0f ? false : true;
    }
        
    void processGlide()
    {
        if(glideModeSetting && currentFrequency < frequency){
            currentFrequency += .1 * (1-glideRateSetting);
            currentFrequency = currentFrequency > frequency ? frequency : currentFrequency;
        }
        else if(glideModeSetting && currentFrequency > frequency){
            currentFrequency -= .1 * (1-glideRateSetting);
            currentFrequency = currentFrequency < frequency ? frequency : currentFrequency;
        }
        else {
            currentFrequency = frequency;
        }
    }
    
    // ////////////   MASTER
    
    void setMasterParams (Setting* tune, Setting* gain)
    {
        masterTuneSetting = *tune;
        masterGain = *gain;
    }
    
    //==========PLAYING============================
    
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        
        noteNumber = midiNoteNumber;
        //        setPitchBend(currentPitchWheelPosition);
        frequency = MidiMessage::getMidiNoteInHertz(noteNumber);
        //        level = velocity;
        if(currentFrequency == 0){
            currentFrequency = frequency;
        }
        m_EG1.reset();
        m_FilterEG.reset();

        m_EG1.startEG();
        m_FilterEG.startEG();

    }

    
    void stopNote (float velocity, bool allowTailOff) override
    {
        
//        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();

        m_EG1.noteOff();
        m_FilterEG.noteOff();
    
    }
    

    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }

    
    //=================PROCESSING======================
    
    
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
     
            m_Filter1.update();
            processGlide();
            processFrequency(currentFrequency);
    
            dEGOut = m_EG1.doEnvelope();
            
            
            dFilterEGOut = m_FilterEG.doEnvelope();
            
//            auto filteredEnvelope = filterCutoffSetting * dFilterEGOut;
//            double filterModulation = getModulationMatrixOutput(filteredEnvelope, modFilterSetting );
//            return  filter1.lores(getMixerOutput(),  filterModulation , filterResonanceSetting);
            double dMixerOut = getMixerOutput();
            double dFilterOut = m_Filter1.doFilter(dMixerOut);
            
//            double  masterOutput = getFilterOutput() * masterGain * dEGOut;
            double  masterOutput = dFilterOut * dEGOut * masterGain;
//
            

            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, masterOutput /4);
            }
            ++startSample;
        }
    }
    
    //=======================================================
private:
    double level;
    
    int noteNumber;
    
    //    float pitchBend = 0.0f;
    float pitchBendUpSemitones = 2.0f;
    float pitchBendDownSemitones = 2.0f;
    
   
    float filterCutoffSetting;
    float filterResonanceSetting;
    float filterKeyAmtSetting;
    float filterEnvAmtSetting;
    double frequency;
    double currentFrequency;
    double osc1processedFrequency;
    double osc2processedFrequency;
    double dEGOut;
    double dFilterEGOut;
    
    double lfoRateSetting;
    // --- the setting for saw LFO
    int lfoSawSetting;
    int lfoTriangleSetting;
    int lfoSquareSetting;
    
    
    float modAmtFilterEnvSetting;
    float modAmtOscBSetting;
    float modAmtLfoSetting;
    int modOscAFreqSetting;
    int modOscAPWSetting;
    int modOscBFreqSetting;
    int modOscBPWSetting;
    int modFilterSetting;
    double oscBModValue;
    
    int arpeggiatorMode;

    double noiseLevelSetting;
    double osc1LevelSetting;
    double osc2LevelSetting;
    
    float pitchBendSetting;
    double pitchBendPosition;
    double midiPitchWheel;
    
    double glideRateSetting;
    bool glideModeSetting;
    
    float masterTuneSetting;
    float masterGain;
    
    maxiOsc  osc3, lfoSaw, lfoTriangle, lfoSquare, oscB;
    maxiFilter filter1;
    
    Oscillator m_OscA, m_OscB;
    
    EnvelopeGenerator m_EG1;
    EnvelopeGenerator m_FilterEG;
    
    MoogFilter m_Filter1;
    
    enum
    {
        osc1Index,
        osc2Index,
        filterIndex,
        masterGainIndex
    };
    
};
