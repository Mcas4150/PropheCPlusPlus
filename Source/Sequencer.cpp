/*
  ==============================================================================

    Sequencer.cpp
    Created: 30 May 2019 11:11:11pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sequencer.h"

//==============================================================================
Sequencer::Sequencer(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
{
    setSize(90, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("SEQUENCER");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);

    sequenceModeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sequenceModeToggle.setRange(0, 2);
    sequenceModeToggle.setValue(1);
    sequenceModeToggle.addListener(this);
    addAndMakeVisible(&sequenceModeToggle);
    sequenceModeToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (*processor.valTreeState, "sequenceMode", sequenceModeToggle);
    sequenceModeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    sequenceRecordToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sequenceRecordToggle.setRange(0, 2);
    sequenceRecordToggle.setValue(1);
    sequenceRecordToggle.addListener(this);
    addAndMakeVisible(&sequenceRecordToggle);
    sequenceRecordToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (*processor.valTreeState, "sequenceRecord", sequenceRecordToggle);
    sequenceRecordToggle.setLookAndFeel(&sliderToggleLookAndFeel);
}

Sequencer::~Sequencer()
{
}

void Sequencer::paint (Graphics& g)
{
    

}

void Sequencer::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    
    sequenceModeToggle.setBounds(20, 30, 20, 40);
    sequenceRecordToggle.setBounds(50, 35, 20, 30);
}
void Sequencer::sliderValueChanged(Slider* slider)
{
    
}
