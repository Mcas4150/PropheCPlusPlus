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
    BasicKnob modAmtFilterEnvKnob; LabeledKnob labeledModAmtFilterEnvKnob;
    BasicKnob osc2ModAmtKnob; LabeledKnob labeledOsc2ModAmtKnob;
    BasicKnob modAmtLfoKnob; LabeledKnob labeledModAmtLfoKnob;
    
    Slider filterEnvRouteToggle;
    Slider osc2RouteToggle;
    Slider lfoRouteToggle;
    Slider osc1FreqToggle;
    Slider osc1PWToggle;
    Slider osc2FreqToggle;
    Slider osc2PWToggle;
    Slider filterToggle;
    
    GroupComponent mainGroup;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfoFilterVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2ModAmtVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> modAmtLfoVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterEnvRouteToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2RouteToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfoRouteToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc1FreqToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc1PWToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2FreqToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2PWToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterToggleVal;
    
    
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Modulation)
};
