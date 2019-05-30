

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"

//==============================================================================
/*
 */
class Amplifier    : public Component
{
public:
    Amplifier(JuceSynthFrameworkAudioProcessor&);
    ~Amplifier();
    
    void paint (Graphics&) override;
    void resized() override;
    
    
private:
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    
    GroupComponent mainGroup;
    
    BasicKnob attackSlider; LabeledKnob labeledAmpAttackKnob;
    BasicKnob decaySlider; LabeledKnob labeledAmpDecayKnob;
    BasicKnob sustainSlider; LabeledKnob labeledAmpSustainKnob;
    BasicKnob releaseSlider; LabeledKnob labeledAmpReleaseKnob;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseVal;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Amplifier)
};
