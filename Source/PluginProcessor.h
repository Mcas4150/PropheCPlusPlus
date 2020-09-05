/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"
#include "SynthSound.h"
#include "EnvelopeGenerator.h"
#include "ArpeggiatorEngine.h"
#include "Oscillator.h"
#include "AudioBufferQueue.h"
#include "ScopeDataCollector.h"
#include "ScopeComponent.h"
#include "ModulationMatrix.h"
#include "LFOEngine.h"

//==============================================================================
/**
 */
class JuceSynthFrameworkAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JuceSynthFrameworkAudioProcessor();
    ~JuceSynthFrameworkAudioProcessor();
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
    
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
    
    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    //==============================================================================
    const String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override{ return 0.0;} ;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    auto getParamValue(StringRef parameter)
    {
        std::atomic<float>* RawParam = valTreeState.getRawParameterValue(parameter);
        return RawParam;
    }
    
    UndoManager              mUndoManager;
    AudioProcessorValueTreeState valTreeState;
    MidiKeyboardState keyboardState;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
    AudioBufferQueue<float>& getAudioBufferQueue() noexcept  { return audioBufferQueue; }
    Synthesiser mySynth;
    SynthVoice* myVoice;
    ModulationMatrix m_ModMatrix;

    EnvelopeGenerator* m_EG1;
    ArpeggiatorEngine m_Arp;
    LFOEngine m_LFO;
//    LFO& mm_LFO;
//    
    
    
private:
  
    double lastSampleRate;
    
    AudioBufferQueue<float> audioBufferQueue;
    ScopeDataCollector<float> scopeDataCollector { audioBufferQueue };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessor)
};
