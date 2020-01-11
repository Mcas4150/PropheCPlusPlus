/*
  ==============================================================================

    Mode.h
    Created: 30 May 2019 11:09:47pm
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
class Mode    : public Component, public Slider::Listener
{
public:
    Mode(JuceSynthFrameworkAudioProcessor&);
    ~Mode();

    void paint (Graphics&) override;
    void resized() override;
      void sliderValueChanged (Slider*) override;

private:
    JuceSynthFrameworkAudioProcessor& processor;
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    GroupLookAndFeel groupLookAndFeel;
    
    Slider retrigModeToggle;
    Slider repeatModeToggle;
    Slider droneModeToggle;
    
    Label offLabel;
    Label droneLabel;
    Label repeatLabel;
    Label normalLabel;
    Label normalLabel2;
    Label retrigLabel;

    
    GroupComponent mainGroup;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> retrigModeToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> repeatModeToggleVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> droneModeToggleVal;
    
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mode)
};
