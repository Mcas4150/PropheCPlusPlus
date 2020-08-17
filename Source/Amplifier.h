

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"
#include "SliderLookAndFeel.h"

//==============================================================================
/*
 */
class Amplifier    : public Component, public Slider::Listener
{
public:
    Amplifier(JuceSynthFrameworkAudioProcessor&);
    ~Amplifier();
    
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;

    
private:
    JuceSynthFrameworkAudioProcessor& processor;
    
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    GroupLookAndFeel groupLookAndFeel;
    
    GroupComponent mainGroup;
    
    BasicKnob attackSlider; LabeledKnob labeledAmpAttackKnob;
    BasicKnob decaySlider; LabeledKnob labeledAmpDecayKnob;
    BasicKnob sustainSlider; LabeledKnob labeledAmpSustainKnob;
    BasicKnob releaseSlider; LabeledKnob labeledAmpReleaseKnob;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseVal;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Amplifier)
};
