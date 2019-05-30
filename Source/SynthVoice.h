

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
    
    //    void setPitchBend(int pitchWheelPos)
    //    {
    //        if (pitchWheelPos > 8192)
    //        {
    //            // shifting up
    //            pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
    //        }
    //        else
    //        {
    //            // shifting down
    //            pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
    //        }
    //    }
    //
    //    float pitchBendCents()
    //    {
    //        if (pitchBend >= 0.0f)
    //        {
    //            // shifting up
    //            return pitchBend * pitchBendUpSemitones * 100;
    //        }
    //        else
    //        {
    //            // shifting down
    //            return pitchBend * pitchBendDownSemitones * 100;
    //        }
    //    }
    
    static double noteHz(int midiNoteNumber, double centsOffset)
    {
        double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        hertz *= std::pow(2.0, centsOffset / 1200);
        return hertz;
    }
    
    //=======================================================
    
    void getOscType(float* selection)
    {
        theWave = *selection;
        
    }
    
    void getOsc2Type(float* selection)
    {
        
        theWave2 = *selection;
    }
    //=======================================================
    
    double getDCOSound(){
        return osc1.saw(processedFrequency);
    }
    
    double setOscType ()
    
    {
        double sample1, sample2;
        
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
        
        return sample1 + osc2blend * sample2;
    }
    
    
    
//    OSCILLATOR A
    
    
    void setOsc1Freq(float* setting)
    {
        osc1FreqSetting = *setting;
    }
    
    
    
    void setOsc1Oct(float* setting)
    {
        osc1OctSetting = *setting;
    }
    
    
    
    
    
//    OSCILLATOR B
    
    
    
    void setOsc2Freq(float* setting)
    {
        
        osc2FreqSetting = *setting;
    }
    
    void setOsc2Oct(float* setting)
    {
        
        osc2OctSetting = *setting;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    //
    //=======================================================
    
    void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack(*attack);
        env1.setDecay(*decay);
        env1.setSustain(*sustain);
        env1.setRelease(*release);
    }
    
    //=======================================================
    
    double setEnvelope()
    {
        return env1.adsr(setOscType(), env1.trigger);
    }
    
    //=======================================================
    
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
    
    
    void getWillsParams(float* mGain, float* blend)
    {
        masterGain = *mGain;
        osc2blend = *blend;
        //        pitchBendUpSemitones = *pbup;
        //        pitchBendDownSemitones = *pbdn;
    }
    
    //    void getFilterParams (float* filterType, float* filterCutoff, float* filterRes, float* lfoFilterEnv)
    //    {
    //        filterChoice = *filterType;
    //        cutoff = *filterCutoff;
    //        resonance = *filterRes;
    //        lfoFilter = *lfoFilterEnv;
    //    }
    
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
    
    void setLfoFilterEnv (float* setting)
    {
        lfoFilter = *setting;
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
    
    void setMasterTune (float* setting)
    {
        masterTuneSetting = *setting;
    }
    
    void setPitchBend (float* setting){
        pitchBendPosition = midiPitchWheel != 0 ? midiPitchWheel : *setting;
        pitchBendSetting =  pitchBendPosition;
    }
    
    void setNoiseLevel(float* setting)
    {
        noiseLevelSetting = *setting;
    }
    
    void setOsc1Level(float* setting)
    {
        osc1OctSetting = *setting;
    }
    
    void setOsc2Level(float* setting)
    {
        osc2OctSetting = *setting;
    }
    
    
    double getMixerSound()
    {
        
        return
        //        getOsc1Sound()
        //        (
        osc1.saw(processedFrequency * (std::pow(2, osc1FreqSetting + osc1OctSetting))) + osc2.saw(processedFrequency* (std::pow(2, osc2FreqSetting + osc2OctSetting))) / 2;
        //        * osc1LevelSetting;
        
        //        +  osc2.saw(processedFrequency)   * osc2LevelSetting;
        //        + osc3.noise() * noiseLevelSetting ) /   ( osc1LevelSetting + osc2LevelSetting + noiseLevelSetting  )  ;
        //        getOsc2Sound
        
        
    }
    
    
    void setGlideRate(float* setting)
    {
        glideRateSetting = *setting;
    }
    
    
    void setGlideMode(float* setting)
    {
        glideModeSetting = *setting == -1.0f ? false : true;
    }
    
    double calculateFilterCutoff(double currentVolume)
    {
        
        //        int menuChoice = *tree.getRawParameterValue("filterType");
        //        int freq = *tree.getRawParameterValue("filterCutoff");
        //        int res = *tree.getRawParameterValue("filterRes");
        //        //    int lfoPhase = *tree.getRawParameterValue("lfoRate");
        //        int lfoPhase = *tree.getRawParameterValue("lfoRate") * lastSampleRate;
        //        //
        //        float lfoOut = sin(2*M_PI * lfoPhase);
        //        //    float lfoOut = sin(2*M_PI * 20);
        //        //
        //        float lfoOutMapped = jmap(lfoOut, -1.f, 1.f, 0.5f, 1.0f);
        //        float frequency = freq * lfoOutMapped;
        //
        //        if (lfoPhase > 1){
        //            lfoPhase -= 1;
        //        }
        double cutoffValue = 0;
        cutoffValue = currentVolume*cutoffSetting;
//                cutoffValue = currentVolume*filterEnvelope;
        cutoffValue += getLfoValue()*lfoFilter;
        if(cutoffValue < 30.0f)
        {
            cutoffValue = 30.0f;
        }
        else if (cutoffValue > 4000.0f)
        {
            cutoffValue = 4000.0f;
        }
        return cutoffValue;
        
        
        //
        
    }
    
    //    if (menuChoice == 0)
    //        {
    //            stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
    //        }
    //
    //        if (menuChoice == 1)
    //        {
    //            stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
    //        }
    //
    //        if (menuChoice == 2)
    //        {
    //            stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
    //
    //        }
    //
    //        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    
    
    double getLfoValue()
    {
        double lfoValue = lfoRateSetting != 0 ? lfo.triangle(lfoEnv.adsr(lfoRateSetting , lfoEnv.trigger)) : 0;
        return lfoValue;
    }
    
    
    void setLfoModAmt(float* setting)
    {
        lfoModAmtSetting = *setting;
        
    }
    
    
    //=======================================================
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        noteNumber = midiNoteNumber;
        env1.trigger = 1;
        env1.attackphase=1;
        env1.decayphase=0;
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
    
    //=======================================================
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        env1.trigger = 0;
        env1.attackphase=0;
        env1.decayphase=1;
        lfoEnv.trigger = 0;
        lfoEnv.attackphase=0;
        lfoEnv.decayphase=1;
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
    
    //=======================================================
    
    void pitchWheelMoved (int newPitchWheelValue) override
    {
        midiPitchWheel = (newPitchWheelValue-8191.5f)/8191.5f;
    }
    
    //=======================================================
    
    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }
    
    //=======================================================
    
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
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
            auto freq = currentFrequency * (std::pow(2, pitchBendSetting + masterTuneSetting));
            //            processedFrequency = freq + (freq * getLfoValue());
            processedFrequency = freq;
            auto myCurrentVolume = env1.adsr(1., env1.trigger) * masterGain;
            
                        double oscSound = getMixerSound();
            
            double filteredSound = filter1.lores(oscSound * myCurrentVolume, calculateFilterCutoff(myCurrentVolume), resonance);
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, filteredSound /4);
            }
            ++startSample;
        }
    }
    
    //=======================================================
private:
    double level;
    double frequency;
    double currentFrequency;
    double processedFrequency;
    double lfoRateSetting;
    double lfoDelaySetting;
    int lfoType;
    //    double lfoFilterEnvSetting;
    int theWave, theWave2;
    
    float masterGain;
    float osc2blend;
    
    int noteNumber;
    //    float pitchBend = 0.0f;
    float pitchBendUpSemitones = 2.0f;
    float pitchBendDownSemitones = 2.0f;
    
    int filterChoice;
    float cutoffSetting;
    float lfoFilter;
    float resonance;
    float keyAmt;
    float envAmt;
    float lfoModAmtSetting;
    float osc1FreqSetting;
    float osc2FreqSetting;
    float osc1OctSetting;
    float osc2OctSetting;
    float masterTuneSetting;
    float pitchBendSetting;
    double pitchBendPosition;
    double midiPitchWheel;
    double noiseLevelSetting;
    double osc1LevelSetting;
    double osc2LevelSetting;
    double glideRateSetting;
    
    Boolean glideModeSetting;
    
    maxiOsc osc1, osc2, osc3, lfo;
    maxiEnv env1;
    maxiEnv filterEnvelope;
    maxiEnv lfoEnv;
    maxiFilter filter1;
    
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
