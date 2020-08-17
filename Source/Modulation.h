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
    void extracted();
    
Modulation(JuceSynthFrameworkAudioProcessor&);
    ~Modulation();
    
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    
private:
    
    JuceSynthFrameworkAudioProcessor& processor;
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    GroupLookAndFeel groupLookAndFeel;
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
    Label modAmtFilterEnvLabel;
    Label modAmtOscBLabel;
    Label modAmtLfoLabel;
    Label osc1FreqLabel;
    Label osc1PWLabel;
    Label osc2FreqLabel;
    Label osc2PWLabel;
    Label filterLabel;
    
    GroupComponent mainGroup;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> modAmtFilterEnvVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> modAmtOscBVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> modAmtLfoVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterEnvRouteToggleVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2RouteToggleVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoRouteToggleVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1FreqToggleVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1PWToggleVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2FreqToggleVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2PWToggleVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterToggleVal;
    
    
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Modulation)
};
