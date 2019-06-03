/*
  ==============================================================================

    Arpeggiator.h
    Created: 30 May 2019 11:10:59pm
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
class Arpeggiator    : public Component, public Slider::Listener
{
public:
    Arpeggiator(JuceSynthFrameworkAudioProcessor&);
    ~Arpeggiator();

    void paint (Graphics&) override;
    void resized() override;
      void sliderValueChanged (Slider*) override;

private:
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    GroupLookAndFeel groupLookAndFeel;
    
    Slider arpModeToggle;
    
    GroupComponent mainGroup;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> arpModeToggleVal;
 
    
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Arpeggiator)
};
