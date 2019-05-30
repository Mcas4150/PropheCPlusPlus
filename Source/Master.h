/*
 ==============================================================================
 
 Master.h
 Created: 28 May 2019 10:02:42pm
 Author:  Mike Cassidy
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ScopeComponent.h"
#include "../Common/LabeledKnob.h"

//==============================================================================
/*
 */
class Master    : public Component
{
public:
    Master(JuceSynthFrameworkAudioProcessor&);
    ~Master();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    BasicKnob mastergainSlider; LabeledKnob labeledMasterGainKnob;
    BasicKnob masterTuneSlider; LabeledKnob labeledMasterTuneKnob;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mastergainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> masterTuneVal;
    
    
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Master)
};
