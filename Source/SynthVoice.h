

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "EnvelopeGenerator.h"
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
    
    void setOscAParams(Setting* oscAFreq, Setting* oscAOct, Setting* oscASawMode, Setting* oscASquareMode, Setting* oscAPW )
    {
        osc1FreqSetting = std::pow(2, *oscAFreq);
        osc1OctSetting = std::pow(2, *oscAOct);
        osc1SawSetting = *oscASawMode;
        osc1SquareSetting = *oscASquareMode;
        osc1PWSetting = *oscAPW;
    }

    
    double getOsc1PWSetting(){
        double pwm = osc1PWSetting;

        if(pwm > 0.99f){
            return 0.99;
        } else if (pwm < 0){
            return 0;
        } else {
            return pwm;
        }
    }
    
    double getOsc1Saw() {
        if(osc1SawSetting)
        {
            return osc1saw.saw(osc1processedFrequency * osc1FreqSetting * osc1OctSetting);
        }
        return 0;
    }
    
    double getOsc1Square() {
        if(osc1SquareSetting)
        {
            double squareFrequency = osc1square.square(osc1processedFrequency * osc1FreqSetting * osc1OctSetting);
            
            if(osc1PWSetting > 0){
            return osc1square.pulse(squareFrequency,  getModulationMatrixOutput(getOsc1PWSetting(), modOscAPWSetting));
            } else {
                return squareFrequency;
            }

        }
        return 0;
    }
    

    double getOscAOutput(){
        return
            
        getOsc1Saw() + getOsc1Square();
   
    }


//============OSCILLATOR B======================
    
    void setOscBParams(Setting* frequency, Setting* oct, Setting* sawMode, Setting* squareMode, Setting* triangleMode, Setting* PW, Setting* LoFreqMode)
    {
        osc2FreqSetting = std::pow(2, *frequency);
        osc2OctSetting = std::pow(2, *oct);
        osc2SawSetting = *sawMode;
        osc2TriangleSetting = *triangleMode;
        osc2SquareSetting = *squareMode;
        osc2PWSetting = *PW;
        osc2LoFreqSetting = *LoFreqMode;
    }

    
    double getOsc2PWSetting(){
        double pwm = osc2PWSetting;

        if(pwm > 0.99f){
            return 0.99;
        } else if (pwm < 0){
            return 0;
        } else {
            return pwm;
        }
    }
    
    double getOsc2Saw() {
            if(osc2SawSetting)
            {
                return osc2saw.saw(osc2processedFrequency * osc2FreqSetting * osc2OctSetting);
            }
            return 0;
        }
    
    double getOsc2Triangle() {
            if(osc2TriangleSetting)
            {
                return osc2triangle.triangle(osc2processedFrequency * osc2FreqSetting * osc2OctSetting);
            }
            return 0;
        }
        
        
    double getOsc2Square() {
            if(osc2SquareSetting)
            {

                double squareFrequency = osc2square.square(osc2processedFrequency * osc2FreqSetting * osc2OctSetting);
                
                if(osc2PWSetting > 0){
                return osc2square.pulse(squareFrequency,  getModulationMatrixOutput(getOsc2PWSetting(), modOscBPWSetting));
                } else {
                    return squareFrequency;
                }

            }
            return 0;
        }

    double getOsc2Output()
    {

        return getOsc2Saw() + getOsc2Triangle() + getOsc2Square();

    }

    
    //=========MIXER========================
    

    void setMixerParams(Setting* osc1Level, Setting* osc2Level, Setting* noiseLevel)
    {
        osc1LevelSetting = *osc1Level;
        osc2LevelSetting = *osc2Level;
        noiseLevelSetting = *noiseLevel;
    }
    
    
    double getMixerSound()
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
        m_FilterEG.setAttackTime_mSec(attack);
        m_FilterEG.setDecayTime_mSec(decay);
        m_FilterEG.setSustainLevel(sustain);
        m_FilterEG.setReleaseTime_mSec(release);
    }
    

     double getProcessedFilter()
     {
         double mixerOutput = getMixerSound();
         auto filteredEnvelope = filterCutoffSetting * dFilterEGOut;
         auto filteredMod =  getModulationMatrixOutput(filteredEnvelope, modFilterSetting ) ;
         double filteredSound = filter1.lores(mixerOutput, filteredMod , filterResonanceSetting);
         return filteredSound;
     }
    
    
    //=========LFO==========================

    void setLfoParams(Setting* rate, Setting* sawMode, Setting* triangleMode, Setting* squareMode)
    {
        lfoRateSetting = *rate;
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
    
    
    double getOscBModValue()
    {
        return lfoRateSetting != 0 ? (  getOsc2Output()  * modAmtOscBSetting ) : 1;

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
        return modulationParameter + (modulationParameter * getLfoValue()   * modulationSetting);
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
    
//    Arpeggiator
    
    void setArpeggiatorParams(Setting* mode)
    {
        arpeggiatorMode = *mode;
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
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
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
        

        allowTailOff = true;
        
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
     
            
            processGlide();
            processFrequency(currentFrequency);
    
            dEGOut = m_EG1.doEnvelope();
            dFilterEGOut = m_FilterEG.doEnvelope();
            
            double filteredSound = getProcessedFilter() ;
            
            double processedOutput = filteredSound;
            
            double  masterOutput = processedOutput * masterGain * dEGOut;

            
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
    
    float osc1FreqSetting;
    float osc1OctSetting;
    float osc1SawSetting;
    float osc1SquareSetting;
    float osc1PWSetting;
    
    float osc2FreqSetting;
    float osc2OctSetting;
    float osc2SawSetting;
    float osc2TriangleSetting;
    float osc2SquareSetting;
    float osc2PWSetting;
    float osc2LoFreqSetting;
   

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
    
    maxiOsc osc1saw, osc1square, osc2saw, osc2triangle, osc2square, osc3, lfoSaw, lfoTriangle, lfoSquare;
    maxiEnv lfoEnv1;
    maxiFilter filter1;
    
    EnvelopeGenerator m_EG1;
    EnvelopeGenerator m_FilterEG;
    
    enum
    {
        osc1Index,
        osc2Index,
        filterIndex,
        masterGainIndex
    };
    
};
