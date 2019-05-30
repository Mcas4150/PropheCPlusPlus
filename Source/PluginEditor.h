/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Oscillator2.h"
#include "Amplifier.h"
#include "Filter.h"
#include "Glide.h"
#include "Mixer.h"
#include "Modulation.h"
#include "LFO.h"
#include "ScopeComponent.h"
#include "Master.h"
#include "Wheels.h"
#include "SliderLookAndFeel.h"
#include "../Common/LabeledKnob.h"


//==============================================================================
/**
 */
class JuceSynthFrameworkAudioProcessorEditor  : public AudioProcessorEditor

{
public:
    JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor&);
    ~JuceSynthFrameworkAudioProcessorEditor();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    MidiKeyboardComponent keyboardComponent;
    ScopeComponent<float> scopeComponent;
    
    Oscillator oscGui;
    Oscillator2 osc2Gui;
    Amplifier ampGui;
    Filter filterGui;
    LFO lfoGui;
    Glide glideGui;
    Wheels wheelsGui;
    Mixer mixerGui;
    Modulation modulationGui;
    Master masterGui;
    SliderLookAndFeel sliderLookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessorEditor)
};