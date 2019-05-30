/*
 ==============================================================================
 
 Modulation.h
 Created: 28 May 2019 9:44:32pm
 Author:  Mike Cassidy
 
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
class Modulation    : public Component, public Slider::Listener
{
public:
    Modulation(JuceSynthFrameworkAudioProcessor&);
    ~Modulation();
    
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    
private:
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    BasicKnob lfoFilterEnv; LabeledKnob labeledLfoFilterEnv;
    BasicKnob oscBModAmtKnob; LabeledKnob labeledOscBModAmtKnob;
    BasicKnob lfoModAmtKnob; LabeledKnob labeledLfoModAmtKnob;
    
    Slider filterEnvRouteToggle;
    Slider oscBRouteToggle;
    Slider lfoRouteToggle;
    Slider oscAFreqToggle;
    Slider oscAPWToggle;
    Slider oscBFreqToggle;
    Slider oscBPWToggle;
    Slider filterToggle;
    
    GroupComponent mainGroup;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfoFilterVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscBModAmtVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfoModAmtVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterEnvRouteToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscBRouteToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfoRouteToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscAFreqToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscAPWToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscBFreqToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscBPWToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterToggleVal;
    
    
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Modulation)
};
