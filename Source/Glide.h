
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"
#include "SliderLookAndFeel.h"

//==============================================================================
/*
 */
class Glide    : public Component, public Slider::Listener
{
public:
    Glide(JuceSynthFrameworkAudioProcessor&);
    ~Glide();
    
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    
private:
    JuceSynthFrameworkAudioProcessor& processor;
    
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    GroupLookAndFeel groupLookAndFeel;
    BasicKnob glideRateKnob; LabeledKnob labeledGlideRateKnob;
    Slider glideModeToggle;
    Label normalLabel;
    Label autoLabel;
    
    GroupComponent mainGroup;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> glideRateVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> glideModeVal;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Glide)
};
