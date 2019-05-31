

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
    
    
    void setOsc1Freq(float* setting)
    {
        osc1FreqSetting = *setting;
    }
    
    
    
    void setOsc1Oct(float* setting)
    {
        osc1OctSetting = *setting;
    }
    
//    void setOsc1
    
    
    void getOscType(float* selection)
    {
        theWave = *selection;
        double sample1;
        switch (theWave)
        {
            case 0:
                sample1 = osc1.square(processedFrequency);
                break;
            case 1:
                sample1 = osc1.saw(processedFrequency);
                break;
            case 2:
                sample1 = osc1.triangle(processedFrequency);
                break;
            default:
                sample1 = osc1.sinewave(processedFrequency);
                break;
        }
    
    }
    
   
    
    
    

    
//============OSCILLATOR B======================
    
    
    
    void setOsc2Freq(float* setting)
    {
        
        osc2FreqSetting = *setting;
    }
    
    void setOsc2Oct(float* setting)
    {
        
        osc2OctSetting = *setting;
    }
    
    
    
    void getOsc2Type(float* selection)
    {
        
        theWave2 = *selection;
        double sample2;
        switch (theWave2)
        {
            case 0:
                sample2 = osc2.saw(processedFrequency / 2.0);
                break;
            case 1:
                sample2 = osc2.square(processedFrequency / 2.0);
                break;
            case 2:
                sample2 = osc2.triangle(processedFrequency / 2.0);
                break;
            default:
                sample2 = osc2.sinewave(processedFrequency / 2.0);
                break;
        }
    }
    

    
    
    //=========MIXER========================
    
    
    
    void setNoiseLevel(float* setting)
    {
        noiseLevelSetting = *setting;
    }
    
    void setOsc1Level(float* setting)
    {
        osc1LevelSetting = *setting;
    }
    
    void setOsc2Level(float* setting)
    {
        osc2LevelSetting = *setting;
    }
    
    
    double getMixerSound()
    {
        
        return

        osc1.saw(processedFrequency * (std::pow(2, osc1FreqSetting)) * (std::pow(2, osc1OctSetting))   )  * osc1LevelSetting
        
        + osc2.saw(processedFrequency* (std::pow(2, osc2FreqSetting )) * (std::pow(2, osc2OctSetting))  ) * osc2LevelSetting
        
          + osc3.noise() * noiseLevelSetting
        ;

    }
    
    
    //  ========AMPLIFIER====================================
    
    void setAmpEnvelope(float* attack, float* decay, float* sustain, float* release)
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
    
    void setFilterType (float* setting)
    {
        filterChoice = *setting;
    }
    
    void setFilterCutoff (float* setting)
    {
        cutoffSetting = *setting;
    }
    
    void setFilterRes (float* setting)
    {
        resonance = *setting;
    }
    
    
    void setEnvAmt (float* setting)
    {
        envAmt = *setting;
    }
    
    void setKeyAmt (float* setting)
    {
        //        keyAmt = *setting;
    }
    
    void setFilterEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
    {
        filterEnvelope.setAttack(*attack);
        filterEnvelope.setDecay(*decay);
        filterEnvelope.setSustain(*sustain);
        filterEnvelope.setRelease(*release);
    }
    
    double getFilterEnvelope()
    {
        
        return  filterEnvelope.adsr(1., filterEnvelope.trigger);
        
    }
    
    
    double getFilterCutoff()
    {
        
        double cutoffValue = 0;
        cutoffValue = getFilterEnvelope() *  cutoffSetting;
        
        cutoffValue += getLfoValue()* lfoFilter;
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
    
    
    void setPitchBend (float* setting){
        pitchBendPosition = midiPitchWheel != 0 ? midiPitchWheel : *setting;
        pitchBendSetting =  pitchBendPosition;
    }
    
    
    void pitchWheelMoved (int newPitchWheelValue) override
    {
        midiPitchWheel = (newPitchWheelValue-8191.5f)/8191.5f;
    }
    
    
    
    
    
    //=========GLIDE========================
    
    
    void setGlideRate(float* setting)
    {
        glideRateSetting = *setting;
    }
    
    
    void setGlideMode(float* setting)
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
    
    
    void setLfoRateSetting(float* setting)
    {
        
        lfoRateSetting = *setting;
    }
    
    void setLfoDelaySetting(float* setting)
    {
        lfoEnv.setAttack(*setting);
        lfoEnv.setDecay(1.0f);
        lfoEnv.setSustain(1.0f);
        lfoEnv.setRelease(1.0f);
        lfoDelaySetting = *setting;
    }
    
    double setLfoType(float* setting)
    
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
        double lfoValue = lfoRateSetting != 0 ? lfo.triangle(lfoEnv.adsr(lfoRateSetting , lfoEnv.trigger)) : 0;
        return lfoValue;
    }
    

    
        //=========MODULATION========================
    
    
    
    void setModAmtFilterEnv (float* setting)
    {
        lfoFilter = *setting;
    }
    
    
    void setmodAmtLfo(float* setting)
    {
        modAmtLfoSetting = *setting ;
    }
    
    

    
    

    
    // ////////////   MASTER
    
    
    void setMasterTune (float* setting)
    {
        masterTuneSetting = *setting;
    }
    
    
    void setMasterGain(float* mGain)
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
           
            processedFrequency = freq;
            

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
    
    
    int theWave, theWave2;
    float osc1FreqSetting;
    float osc2FreqSetting;
    float osc1OctSetting;
    float osc2OctSetting;
    float osc2blend;
    
    int noteNumber;
    
    
    //    float pitchBend = 0.0f;
    float pitchBendUpSemitones = 2.0f;
    float pitchBendDownSemitones = 2.0f;
    
    
    
    maxiFilter filter1;
    maxiEnv filterEnvelope;
    int filterChoice;
    float cutoffSetting;
    float lfoFilter;
    float resonance;
    float keyAmt;
    float envAmt;
    double frequency;
    double currentFrequency;
    double processedFrequency;
    
    
    double lfoRateSetting;
    double lfoDelaySetting;
    int lfoType;
    
    
    
    float modAmtLfoSetting;
    
    double noiseLevelSetting;
    double osc1LevelSetting;
    double osc2LevelSetting;
    
    float pitchBendSetting;
    double pitchBendPosition;
    double midiPitchWheel;
    
    double glideRateSetting;
    Boolean glideModeSetting;
    
    float masterTuneSetting;
    float masterGain;
    

    maxiOsc osc1, osc2, osc3, lfo;
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
