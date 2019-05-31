/*
 ==============================================================================
 
 Oscillator.h
 Created: 11 Jan 2018 1:41:05pm
 Author:  Joshua Hodge
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"
#include "SliderLookAndFeel.h"


//==============================================================================
/*
 */
class Oscillator   : public Component, public Slider::Listener
{
public:
    Oscillator(JuceSynthFrameworkAudioProcessor&);
    ~Oscillator();
    
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    
private:
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    ComboBox oscMenu;
    GroupComponent mainGroup;
    BasicKnob oscAFreqKnob; LabeledKnob labeledOscAFreqKnob;
    BasicKnob oscAOctKnob; LabeledKnob labeledOscAOctKnob;
    BasicKnob oscAPulseWidthKnob; LabeledKnob labeledOscAPulseWidthKnob;
    Slider oscASawShapeToggle;
    Slider oscASquareShapeToggle;
    Slider oscASyncToggle;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscASawShapeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscASquareShapeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscASyncVal;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscAFreqVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscAOctVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscAPulseWidthVal;
    
    
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
