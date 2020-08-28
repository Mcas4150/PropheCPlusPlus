/*
 ==============================================================================
 
 Mixer.h
 Created: 28 May 2019 9:50:55pm
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
class Mixer    : public Component
{
public:
    Mixer(JuceSynthFrameworkAudioProcessor&);
    ~Mixer();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    JuceSynthFrameworkAudioProcessor& processor;
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    
    GroupComponent mainGroup;
    
    BasicKnob osc1Level; LabeledKnob labeledoscALevelKnob;
    BasicKnob osc2Level; LabeledKnob labeledOsc2LevelKnob;
    BasicKnob noiseLevel; LabeledKnob labeledNoiseLevelKnob;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1LevelVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2LevelVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> noiseLevelVal;
    
    GroupLookAndFeel groupLookAndFeel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mixer)
};
