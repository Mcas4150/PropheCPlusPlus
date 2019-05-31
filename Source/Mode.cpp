/*
  ==============================================================================

    Mode.cpp
    Created: 30 May 2019 11:09:47pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Mode.h"

//==============================================================================
Mode::Mode(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
{
    setSize(150, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("MODE");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    addAndMakeVisible(&mainGroup);
    
    retrigModeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    retrigModeToggle.setRange(0, 2);
    retrigModeToggle.setValue(1);
    retrigModeToggle.addListener(this);
    addAndMakeVisible(&retrigModeToggle);
    retrigModeToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "retrigMode", retrigModeToggle);
    retrigModeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    repeatModeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    repeatModeToggle.setRange(0, 2);
    repeatModeToggle.setValue(1);
    repeatModeToggle.addListener(this);
    addAndMakeVisible(&repeatModeToggle);
    repeatModeToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "repeatMode", repeatModeToggle);
    repeatModeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    droneModeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    droneModeToggle.setRange(0, 2);
    droneModeToggle.setValue(1);
    droneModeToggle.addListener(this);
    addAndMakeVisible(&droneModeToggle);
    droneModeToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "droneMode", droneModeToggle);
    droneModeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
}

Mode::~Mode()
{
}

void Mode::paint (Graphics& g)
{

}

void Mode::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    auto bounds = getLocalBounds().reduced(5);
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    retrigModeToggle.setBounds(25, 35, 20, 30);
    repeatModeToggle.setBounds(65, 35, 20, 30);
    droneModeToggle.setBounds(105, 35, 20, 30);

}
void Mode::sliderValueChanged(Slider* slider)
{
    
}
