/*
  ==============================================================================

    Arpeggiator.cpp
    Created: 30 May 2019 11:10:59pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Arpeggiator.h"

//==============================================================================
Arpeggiator::Arpeggiator(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
{
    setSize(75, 95);
    setLookAndFeel(lookAndFeel);

    mainGroup.setText("ARP");

    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);
    
    arpModeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    arpModeToggle.setRange(0, 2);
    arpModeToggle.setValue(1);
    arpModeToggle.addListener(this);
    addAndMakeVisible(&arpModeToggle);
    arpModeToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "arpMode", arpModeToggle);
    arpModeToggle.setLookAndFeel(&sliderToggleLookAndFeel);

}

Arpeggiator::~Arpeggiator()
{
}

void Arpeggiator::paint (Graphics& g)
{

}

void Arpeggiator::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
   
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    arpModeToggle.setBounds(30, 30, 20, 40);
}
void Arpeggiator::sliderValueChanged(Slider* slider)
{
    
}
