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
#include "CustomLookAndFeel.h"

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
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    
    GroupComponent mainGroup;
    
    BasicKnob oscALevel; LabeledKnob labeledOscALevelKnob;
    BasicKnob osc2Level; LabeledKnob labeledOsc2LevelKnob;
    BasicKnob noiseLevel; LabeledKnob labeledNoiseLevelKnob;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscALevelVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2LevelVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> noiseLevelVal;
    
    GroupLookAndFeel groupLookAndFeel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mixer)
};
