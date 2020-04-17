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
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);
    
    retrigModeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    retrigModeToggle.setRange(0, 2);
    retrigModeToggle.setValue(1);
    retrigModeToggle.addListener(this);
    addAndMakeVisible(&retrigModeToggle);
    retrigModeToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "retrigMode", retrigModeToggle);
    retrigModeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    retrigLabel.setText("RETRIG", dontSendNotification);
    retrigLabel.setFont (Font (9.0f, Font::bold));
    addAndMakeVisible(&retrigLabel);
    normalLabel.setText("NORMAL", dontSendNotification);
    normalLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&normalLabel);
    
    repeatModeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    repeatModeToggle.setRange(0, 2);
    repeatModeToggle.setValue(1);
    repeatModeToggle.addListener(this);
    addAndMakeVisible(&repeatModeToggle);
    repeatModeToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "repeatMode", repeatModeToggle);
    repeatModeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    repeatLabel.setText("REPEAT", dontSendNotification);
    repeatLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&repeatLabel);
    normalLabel2.setText("NORMAL", dontSendNotification);
    normalLabel2.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&normalLabel2);
    
    
    droneModeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    droneModeToggle.setRange(0, 2);
    droneModeToggle.setValue(1);
    droneModeToggle.addListener(this);
    addAndMakeVisible(&droneModeToggle);
    droneModeToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "droneMode", droneModeToggle);
    droneModeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    droneLabel.setText("DRONE", dontSendNotification);
    droneLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&droneLabel);
    
    offLabel.setText("OFF", dontSendNotification);
    offLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&offLabel);
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
 
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    
    retrigLabel.setBounds(15, 25, 40, 10);
    retrigModeToggle.setBounds(25, 35, 20, 30);
    normalLabel.setBounds(15, 65, 40, 10);
    
    repeatLabel.setBounds(55, 25, 40, 10);
    repeatModeToggle.setBounds(65, 35, 20, 30);
    normalLabel2.setBounds(55, 65, 40, 10);
    
    droneLabel.setBounds(98, 25, 40, 10);
    droneModeToggle.setBounds(105, 35, 20, 30);
    offLabel.setBounds(103, 65, 40, 10);
}
void Mode::sliderValueChanged(Slider* slider)
{
    
}
