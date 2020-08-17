

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
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
//        pwm = pwmSetting - pwmSetting * lfoPwmSetting * pwmModeSetting * getLfoValue();
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
            
            return osc1saw.saw(processedFrequency * osc1FreqSetting * osc1OctSetting);
        }
        return 0;
    }
    
    double getOsc1Square() {
        if(osc1SquareSetting)
        {
//           TODO:: ADD PITCH RANGE
//            double squareFrequency = osc1square.square(processedFrequency/getPitchRangeSetting());
            double squareFrequency = osc1square.square(processedFrequency * osc1FreqSetting * osc1OctSetting);
            
            if(osc1PWSetting > 0){
            return osc1square.pulse(squareFrequency, getOsc1PWSetting());
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
    
    void setOsc2SquareMode(std::atomic<float>* setting)
    {
        osc2SquareSetting = *setting;
    }
    

//    double getOsc2()
//    {
//
//        return
//        ( osc2.saw(processedFrequency * osc2FreqSetting * osc2OctSetting) * osc2SawSetting
//         +
//         osc2.square(processedFrequency * osc2FreqSetting * osc2OctSetting) * osc2SquareSetting
//         );
//        //  needs to be averaged properly
//
//    }

    
    
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
        osc2.saw(processedFrequency * osc2FreqSetting * osc2OctSetting) * osc2SawSetting * osc2LevelSetting
        +
        osc3.noise() * noiseLevelSetting;
        
        

    }
    
    
    //  ========AMPLIFIER====================================
    
    void setAmpEnvelope(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
        ampEnvelope.setAttack(*attack);
        ampEnvelope.setDecay(*decay);
        ampEnvelope.setSustain(*sustain);
        ampEnvelope.setRelease(*release);
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
        
        cutoffValue += getLfoValue()* modAmtFilterEnvSetting;
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
    
    //    void getFilterParams (float* filterType, float* filterCutoff, float* filterRes, float* )
    //    {
    //        filterChoice = *filterType;
    //        cutoff = *filterCutoff;
    //        resonance = *filterRes;
    //        lfoFilter = *;
    //    }
    
        //            stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
    
    
    
//=============    PITCH  =============
    
    
    void setPitchBend (std::atomic<float>* setting){
//        pitchBendPosition = midiPitchWheel != 0 ? midiPitchWheel : *setting;
//        pitchBendSetting =  pitchBendPosition;
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

    

    
    //=========LFO==========================
    
    
    void setLfoRateSetting(std::atomic<float>* setting)
    {
        
        lfoRateSetting = *setting;
    }
    
    void setLfoDelaySetting(std::atomic<float>* setting)
    {
        lfoEnv.setAttack(*setting);
        lfoEnv.setDecay(1.0f);
        lfoEnv.setSustain(1.0f);
        lfoEnv.setRelease(1.0f);
        lfoDelaySetting = *setting;
    }
    
    double setLfoType(std::atomic<float>* setting)
    
//    Not a switch but an aggregate
    
    {
        
        double lfoChoice;
        
        switch (lfoType)
        {
            case 0:
                lfoChoice = lfo.square(lfoEnv.adsr(lfoRateSetting , lfoEnv.trigger));
                break;
            case 1:
                lfoChoice = lfo.triangle(lfoEnv.adsr(lfoRateSetting , lfoEnv.trigger));
                break;
            case 2:
                lfoChoice = lfo.triangle(lfoEnv.adsr(lfoRateSetting , lfoEnv.trigger));
                break;
            default:
                lfoChoice = lfo.sinewave(lfoEnv.adsr(lfoRateSetting , lfoEnv.trigger));
                break;
        }
        //
        return lfoChoice;
        //        lfo.triangle(lfoEnv.adsr(lfoRateSetting , lfoEnv.trigger))
        //
        
    }
    
    
    double getLfoValue()
    {
        double lfoValue = lfoRateSetting != 0 ? lfo.triangle(lfoEnv.adsr(lfoRateSetting , lfoEnv.trigger))  : 0;
        return lfoValue;
    }
    
//    void
    

    
        //=========MODULATION========================
    
    
    
    void setModAmtFilterEnv (std::atomic<float>* setting)
    {
        modAmtFilterEnvSetting = *setting;
    }
    
//    void setModAmtOscB(float* setting)
//    {
//        modAmtOscBSetting = *setting ;
//    }
    
    void setModAmtLfo(std::atomic<float>* setting)
    {
        modAmtLfoSetting = *setting ;
    }
    
//    void setToggleFilter(float* setting)
//    {
////        toggleFilterSetting = *setting ;
//        toggleFilterSetting   = *setting == -1.0f ? false : true;
//    }
//
   
    
    

    
    

    
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
        ampEnvelope.trigger = 1;
        ampEnvelope.attackphase=1;
        ampEnvelope.decayphase=0;
        filterEnvelope.trigger = 1;
        filterEnvelope.attackphase=1;
        filterEnvelope.decayphase=0;
        lfoEnv.trigger = 1;
        lfoEnv.attackphase=1;
        lfoEnv.decayphase=0;
        //        setPitchBend(currentPitchWheelPosition);
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        //        level = velocity;
        if(currentFrequency == 0){
            currentFrequency = frequency;
        }
    }

    
    void stopNote (float velocity, bool allowTailOff) override
    {
        ampEnvelope.trigger = 0;
        ampEnvelope.attackphase=0;
        ampEnvelope.decayphase=1;
        filterEnvelope.trigger = 0;
        filterEnvelope.attackphase=0;
        filterEnvelope.decayphase=1;
        lfoEnv.trigger = 0;
        lfoEnv.attackphase=0;
        lfoEnv.decayphase=1;
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
    

    
    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }
    
    
    
    
    
    
    //=================PROCESSING======================
    
    
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            
            
            double mixerOutput = getMixerSound();
            double ampEnvOutput = getAmpEnvelope();
            

            auto amplifierOutput = ampEnvOutput * mixerOutput ;
            
            processGlide();
            
            auto freq = currentFrequency * (std::pow(2, pitchBendSetting + masterTuneSetting));
            //            processedFrequency = freq + (freq * getLfoValue());
//            processedFrequency = freq;
//            processedFrequency = freq + (freq * getLfoValue() * modAmtLfoSetting * toggleFilterSetting);
                     
            
            
            processedFrequency = freq + (freq * getLfoValue() * modAmtLfoSetting);
            

            double filteredSound = filter1.lores(amplifierOutput, getFilterCutoff(), resonance);
    
            
            double processedOutput = filteredSound;
            
            double  masterOutput = processedOutput * masterGain;
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
    float  osc1SawSetting;
    float osc1SquareSetting;
    float osc1PWSetting;
    
    float osc2FreqSetting;
    float osc2OctSetting;
    float   osc2SawSetting;
    float osc2SquareSetting;
    
   
    
    float osc2blend;
    
    int noteNumber;
    
    
    //    float pitchBend = 0.0f;
    float pitchBendUpSemitones = 2.0f;
    float pitchBendDownSemitones = 2.0f;
    
    
    
    maxiFilter filter1;
    maxiEnv filterEnvelope;
    float cutoffSetting;
    float resonance;
    float keyAmt;
    float envAmt;
    double frequency;
    double currentFrequency;
    double processedFrequency;
    
    
    double lfoRateSetting;
    double lfoDelaySetting;
    int lfoType;
    
    
    float modAmtFilterEnvSetting;
//    float modAmtOscBSetting;
    float modAmtLfoSetting;
    
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
    

    maxiOsc osc1saw, osc1square, osc2, osc3, lfo;
    maxiEnv ampEnvelope;
    maxiEnv lfoEnv;

    
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
