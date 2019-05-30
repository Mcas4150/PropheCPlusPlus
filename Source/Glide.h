
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
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    BasicKnob glideRateKnob; LabeledKnob labeledGlideRateKnob;
    Slider glideModeToggle;
    
    GroupComponent mainGroup;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> glideRateVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> glideModeVal;
    
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Glide)
};
