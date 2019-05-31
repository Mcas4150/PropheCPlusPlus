/*
  ==============================================================================

    Sequencer.h
    Created: 30 May 2019 11:11:11pm
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
class Sequencer    : public Component, public Slider::Listener
{
public:
    Sequencer(JuceSynthFrameworkAudioProcessor&);
    ~Sequencer();

    void paint (Graphics&) override;
    void resized() override;
      void sliderValueChanged (Slider*) override;

private:
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    
    Slider sequenceModeToggle;
    Slider sequenceRecordToggle;
    
    GroupComponent mainGroup;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sequenceModeToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sequenceRecordToggleVal;
    
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sequencer)
};
