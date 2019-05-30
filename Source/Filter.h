

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"

//==============================================================================
/*
 */
class Filter    : public Component, public Slider::Listener
{
public:
    Filter(JuceSynthFrameworkAudioProcessor&);
    ~Filter();
    
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    
private:
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    BasicKnob filterCutoff; LabeledKnob labeledFilterCutoff;
    BasicKnob filterRes; LabeledKnob labeledFilterRes;
    BasicKnob envAmt; LabeledKnob labeledEnvAmt;
    BasicKnob keyAmt; LabeledKnob labeledKeyAmt;
    BasicKnob filterAttack; LabeledKnob labeledFilterAttack;
    BasicKnob filterDecay; LabeledKnob labeledFilterDecay;
    BasicKnob filterSustain; LabeledKnob labeledFilterSustain;
    BasicKnob filterRelease; LabeledKnob labeledFilterRelease;
    
    
    GroupComponent mainGroup;
    
    ComboBox filterMenu;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> envAmtVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> keyAmtVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterAttackVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterDecayVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterSustainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterReleaseVal;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
