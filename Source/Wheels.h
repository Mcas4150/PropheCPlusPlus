/*
 ==============================================================================
 
 Wheels.h
 Created: 29 May 2019 12:51:45pm
 Author:  Mike Cassidy
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SliderLookAndFeel.h"
//==============================================================================
/*
 */
class Wheels    : public Component, public Slider::Listener
{
public:
    Wheels(JuceSynthFrameworkAudioProcessor&);
    ~Wheels();
    
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    void sliderDragEnded (Slider*) override;
    
private:
    Slider pitchBendSlider;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pitchBendVal;
    PitchBendLookAndFeel pitchBendLookAndFeel;
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wheels)
};
