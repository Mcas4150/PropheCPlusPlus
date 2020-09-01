

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"
#include "SliderLookAndFeel.h"


// code credited to Will Pirkle, "Designing Software Plugins in C++", 2015
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
    JuceSynthFrameworkAudioProcessor& processor;
    GroupLookAndFeel groupLookAndFeel;
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
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> resVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> envAmtVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> keyAmtVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterAttackVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterDecayVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterSustainVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterReleaseVal;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
