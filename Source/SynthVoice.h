

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

    
//    static double noteHz(int midiNoteNumber, double centsOffset)
//    {
//        double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
//        hertz *= std::pow(2.0, centsOffset / 1200);
//        return hertz;
//    }


    
//  ======================  OSCILLATOR A======================
    void processFrequency (float currentFrequency)
    {
        auto freq = currentFrequency * (std::pow(2, pitchBendSetting + masterTuneSetting));
        osc1processedFrequency = getModulationMatrixOutput(freq, modOscAFreqSetting);
        osc2processedFrequency = getModulationMatrixOutput(freq, modOscBFreqSetting);
    }
    
    void setOsc1Freq(std::atomic<float>* setting)
    {
        osc1FreqSetting = std::pow(2,*setting);
    }
    
    void setOsc1Oct(std::atomic<float>* setting)
    {
        osc1OctSetting =  std::pow(2, *setting);
    }
    
    void setOsc1SawMode(std::atomic<float>* setting)
    {
        osc1SawSetting = *setting;
    }
    
    void setOsc1SquareMode(std::atomic<float>* setting)
    {
        osc1SquareSetting = *setting;
    }
    
    void setOsc1PWSetting(std::atomic<float>* setting)
    {
        osc1PWSetting = *setting;
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
//           TODO:: ADD PITCH RANGE
//            return sawOsc.saw(processedFrequency/getPitchRangeSetting());
            
            return osc1saw.saw(osc1processedFrequency * osc1FreqSetting * osc1OctSetting);
        }
        return 0;
    }
    
    double getOsc1Square() {
        if(osc1SquareSetting)
        {
//           TODO:: ADD PITCH RANGE
//            double squareFrequency = osc1square.square(processedFrequency/getPitchRangeSetting());
            double squareFrequency = osc1square.square(osc1processedFrequency * osc1FreqSetting * osc1OctSetting);
            
            if(osc1PWSetting > 0){
            return osc1square.pulse(squareFrequency,  getModulationMatrixOutput(getOsc1PWSetting(), modOscAPWSetting));
            } else {
                return squareFrequency;
            }

        }
        return 0;
    }
    
//    double getOsc1()
//    {
//
//        return
//     ( osc1.saw(processedFrequency * osc1FreqSetting * osc1OctSetting) * osc1SawSetting
//        +
//     osc1.square(processedFrequency * osc1FreqSetting * osc1OctSetting) * osc1SquareSetting
//      );
////  needs to be averaged properly
//
//    }
    
   
    
    

//============OSCILLATOR B======================
    
    
    
    void setOsc2Freq(std::atomic<float>* setting)
    {
        
        osc2FreqSetting = std::pow(2, *setting);
    }
    
    void setOsc2Oct(std::atomic<float>* setting)
    {
        
        osc2OctSetting =  std::pow(2, *setting);
    }
    
    void setOsc2SawMode(std::atomic<float>* setting)
    {
        osc2SawSetting = *setting;
    }
    
    void setOsc2TriangleMode(std::atomic<float>* setting)
       {
           osc2TriangleSetting = *setting;
       }
    
    void setOsc2SquareMode(std::atomic<float>* setting)
    {
        osc2SquareSetting = *setting;
    }
    
    double getOsc2PWSetting(){
        double pwm = osc1PWSetting;

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
    //           TODO:: ADD PITCH RANGE
    //            return sawOsc.saw(processedFrequency/getPitchRangeSetting());
                
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
    //           TODO:: ADD PITCH RANGE
    //            double squareFrequency = osc1square.square(processedFrequency/getPitchRangeSetting());
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
        double limiterDenominator = osc2TriangleSetting + osc2SquareSetting + osc2SawSetting;
        if (limiterDenominator < 1){
            return 1;
        } else {
            return limiterDenominator;
        }
       
        double osc2Value = (getOsc2Saw() + getOsc2Triangle() + getOsc2Square())/ limiterDenominator;
        return osc2Value;
        
     

    }

    
    
    //=========MIXER========================
    
    
    
    void setNoiseLevel(std::atomic<float>* setting)
    {
        noiseLevelSetting = *setting;
    }
    
    void setOsc1Level(std::atomic<float>* setting)
    {
        osc1LevelSetting = *setting;
    }
    
    void setOsc2Level(std::atomic<float>* setting)
    {
        osc2LevelSetting = *setting;
   
    }
    
    
    double getMixerSound()
    {
       

        return

//       getOsc1() * osc1LevelSetting
//        +
//       getOsc2() * osc2LevelSetting
//        +
//        osc3.noise() * noiseLevelSetting;
        
//        osc1.saw(processedFrequency * osc1FreqSetting * osc1OctSetting) * osc1SawSetting * osc1LevelSetting
        getOsc1Saw() * osc1LevelSetting
        +
        getOsc1Square() * osc1LevelSetting
        +
        getOsc2Output() * osc2LevelSetting
        +
        osc3.noise() * noiseLevelSetting;
        
        

    }
    
        //=========ENVELOPE========================
    void startEnvelopes()
    {
        ampEnvelope.trigger = 1;
        ampEnvelope.attackphase=1;
        ampEnvelope.decayphase=0;
        filterEnvelope.trigger = 1;
        filterEnvelope.attackphase=1;
        filterEnvelope.decayphase=0;
        lfoEnv1.trigger = 1;
        lfoEnv1.attackphase=1;
        lfoEnv1.decayphase=0;
       
    }
    
    void stopEnvelopes()
    {
        ampEnvelope.trigger = 0;
        ampEnvelope.attackphase=0;
        ampEnvelope.decayphase=1;
        filterEnvelope.trigger = 0;
        filterEnvelope.attackphase=0;
        filterEnvelope.decayphase=1;
        lfoEnv1.trigger = 0;
        lfoEnv1.attackphase=0;
        lfoEnv1.decayphase=1;
        
    }
    
    
    //  ========AMPLIFIER====================================
    
    void setAmpEnvelope(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
//        ampEnvelope.setAttack(*attack);
//        ampEnvelope.setDecay(*decay);
//        ampEnvelope.setSustain(*sustain);
//        ampEnvelope.setRelease(*release);
        m_EG1.setAttackTime_mSec(attack);
        m_EG1.setDecayTime_mSec(decay);
        m_EG1.setSustainLevel(sustain);
        m_EG1.setReleaseTime_mSec(release);
        
        
    }
    
    
    
    double getAmpEnvelope()
    {
        
        return  ampEnvelope.adsr(1., ampEnvelope.trigger);
        
    }

    
    //=========FILTER==========================
    

    void setFilterCutoff (std::atomic<float>* setting)
    {
        cutoffSetting = *setting;
    }
    
    void setFilterRes (std::atomic<float>*setting)
    {
        resonance = *setting;
    }
    
    
    void setEnvAmt (std::atomic<float>* setting)
    {
        envAmt = *setting;
    }
    
    void setKeyAmt (std::atomic<float>* setting)
    {
        //        keyAmt = *setting;
    }
    
    void setFilterEnvelopeParams(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
        filterEnvelope.setAttack(*attack);
        filterEnvelope.setDecay(*decay);
        filterEnvelope.setSustain(*sustain);
        filterEnvelope.setRelease(*release);
    }
    
    double getFilterEnvelope()
    {
        
        return filterEnvelope.adsr(1., filterEnvelope.trigger);
        
    }
    
    
    double getFilterCutoff()
    {
        
        double cutoffValue = 0;
        cutoffValue = getFilterEnvelope() *  cutoffSetting;
//        cutoffValue += getLfoValue() * modAmtLfoSetting * modFilterSetting;
        if(cutoffValue < 30.0f)
        {
            cutoffValue = 30.0f;
        }
        else if (cutoffValue > 4000.0f)
        {
            cutoffValue = 4000.0f;
        }
        return cutoffValue;
        
    }
    

    
    

    
    //=========LFO==========================
    
    
//    TODO:: is lfo Enveloped, triggered by Start note?
    
    void setLfoRateSetting(std::atomic<float>* setting)
    {
        
        lfoRateSetting = *setting;
    }
    
    
//    Refactor into one?
    
    void setLfoSawMode(std::atomic<float>* setting)
    {
        lfoSawSetting = *setting;
    }
    
    void setLfoTriangleMode(std::atomic<float>* setting)
    {
        lfoTriangleSetting = *setting;
    }
    
    void setLfoSquareMode(std::atomic<float>* setting)
    {
        lfoSquareSetting = *setting;
    }
    
    
    double getLfoValue()
    {
        double SumSettings = lfoSawSetting + lfoTriangleSetting + lfoSquareSetting;
        double lfoValue = lfoRateSetting && SumSettings != 0 ?
        (
            (
//             lfoSaw.saw(lfoEnv1.adsr(lfoRateSetting * lfoSawSetting , lfoEnv1.trigger))
//             +
//             lfoTriangle.triangle(lfoEnv2.adsr(lfoRateSetting * lfoTriangleSetting , lfoEnv2.trigger))
//             +
//             lfoSquare.square(lfoEnv3.adsr(lfoRateSetting * lfoSquareSetting , lfoEnv3.trigger))
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
        
        double modulatedValue = lfoRateSetting != 0 ? (  getOsc2Output()      * modAmtOscBSetting ) : 1;
        return modulatedValue;
    }

    
        //=========MODULATION========================
    
    
    
    void setModAmtFilterEnv (std::atomic<float>* setting)
    {
        modAmtFilterEnvSetting = *setting;
    }
    
    void setModAmtOscB(std::atomic<float>* setting)
    {
        modAmtOscBSetting = *setting ;
    }
    
    void setModAmtLfo(std::atomic<float>* setting)
    {
        modAmtLfoSetting = *setting ;
    }
    
    
    void setModModeOscAFreq(std::atomic<float>* setting)
    {
        modOscAFreqSetting = *setting;
    }
    
    void setModModeOscAPW(std::atomic<float>* setting)
    {
        modOscAPWSetting = *setting;
    }
    
    void setModModeOscBFreq(std::atomic<float>* setting)
    {
        modOscBFreqSetting = *setting;
    }
    
    void setModModeOscBPW(std::atomic<float>* setting)
    {
        modOscBPWSetting = *setting;
    }
    
    void setModModeFilter(std::atomic<float>* setting)
    {
        modFilterSetting = *setting;
    }
    

    
    double getModulationMatrixOutput(double modulationParameter, int modulationSetting){
        double modulationOutput = modulationParameter + (modulationParameter * getLfoValue()   * modulationSetting);
        return modulationOutput;
    }
    
    

    //=============    PITCH  WHEEL =============
        
        
        void setPitchBend (std::atomic<float>* setting){
//            pitchBendPosition = midiPitchWheel != 0 ? midiPitchWheel : *setting;
//            pitchBendSetting =  pitchBendPosition;
        }
        
        
        void pitchWheelMoved (int newPitchWheelValue) override
        {
            midiPitchWheel = (newPitchWheelValue-8191.5f)/8191.5f;
        }
        
        
        
        
        
        //=========GLIDE========================
        
        
        void setGlideRate(std::atomic<float>* setting)
        {
            glideRateSetting = *setting;
        }
        
        
        void setGlideMode(std::atomic<float>* setting)
        {
            glideModeSetting = *setting == -1.0f ? false : true;
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
    
    
    void setMasterTune (std::atomic<float>* setting)
    {
        masterTuneSetting = *setting;
    }
    
    
    void setMasterGain(std::atomic<float>* mGain)
    {
          masterGain = *mGain;


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
        m_bNoteOn = true;
        startEnvelopes();
        
//        osc1.update();
//        osc2.update();
//
//        m_osc1.startOscillator();
//        m_osc2.startOscillator();
//        m_LFO1.startOscillator();
        m_EG1.startEG();
        
//        m_EG1.doEnvelope();
        
//        double dEGOut = m_EG1.doEnvelope();
    }

    
    void stopNote (float velocity, bool allowTailOff) override
    {
        
        stopEnvelopes();
    
        
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
        m_bNoteOn = false;
        
        m_EG1.stopEG();
        m_EG1.reset();
        
//    m_osc1.stopOscillator();
//    m_osc2.stopOscillator();
//    m_LFO2.stopOscillator();

    }
    

    
    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }
    
    

    
    double getProcessedFilter()
    {
        double mixerOutput = getMixerSound();
//        double ampEnvOutput = getAmpEnvelope();
//        auto amplifierOutput = ampEnvOutput * mixerOutput ;
        auto filteredMod =  getModulationMatrixOutput(getFilterCutoff(), modFilterSetting) ;
        double filteredSound = filter1.lores(mixerOutput, filteredMod , resonance);
        return filteredSound;
    }
    
    
    //=================PROCESSING======================
    
    
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            if(m_bNoteOn)
            {
                dEGOut =    m_EG1.doEnvelope();
            
            
            }
//            processFrquency(currentFrequency);
              
//            double mixerOutput = getMixerSound();
//            double ampEnvOutput = getAmpEnvelope();
//
//
//            auto amplifierOutput = ampEnvOutput * mixerOutput ;
            
//            mixerOutput = getMixerSound
//            filterOutput = MixerOutput * getFilter();
//            vcaOutput = FilterOutput * getAmpEnvelope()
            
            processGlide();
            processFrequency(currentFrequency);
    
            
            double filteredSound = getProcessedFilter();
            
            double processedOutput = filteredSound;
            
            double  masterOutput = processedOutput * masterGain * dEGOut;
//
//    * masterGain

            
            
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


    //    double Setting;
    

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
   
    
    float osc2blend;
    
    int noteNumber;
    bool m_bNoteOn;
    
    //    float pitchBend = 0.0f;
    float pitchBendUpSemitones = 2.0f;
    float pitchBendDownSemitones = 2.0f;
    
    
    
   
    float cutoffSetting;
    float resonance;
    float keyAmt;
    float envAmt;
    double frequency;
    double currentFrequency;
    double osc1processedFrequency;
    double osc2processedFrequency;
    double dEGOut;
    
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
    
//    Boolean toggleFilterSetting;
    
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
    maxiEnv ampEnvelope;
    maxiEnv lfoEnv1;
    maxiEnv filterEnvelope;
    maxiFilter filter1;
    
    EnvelopeGenerator m_EG1;
    
    enum
    {
        osc1Index,
        osc2Index,
        filterIndex,
        masterGainIndex
    };
    
    //    juce::dsp::ProcessorChain<Oscillator<float>, Oscillator<float>, <dsp::StateVariableFilter::Filter<float>, juce::dsp::Gain<float>> processorChain;
    //    dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float> , dsp::StateVariableFilter::Parameters<float>> stateVariableFilter;
};
