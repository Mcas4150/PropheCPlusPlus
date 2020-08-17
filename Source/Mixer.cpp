/*
 ==============================================================================
 
 Mixer.cpp
 Created: 28 May 2019 9:50:55pm
 Author:  Mike Cassidy
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "Mixer.h"

//==============================================================================
Mixer::Mixer(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, osc1Level(0.0f, 1.0f, "")
, labeledoscALevelKnob("OSC A", osc1Level)
, osc2Level(0.0f, 1.0f, "")
, labeledOsc2LevelKnob("OSC B", osc2Level)
, noiseLevel(0.0f, 1.0f, "")
, labeledNoiseLevelKnob("NOISE", noiseLevel)
{
    setSize(200, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("MIXER");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);
    
    osc1Level.setRange(0.0f, 1.0f);
    osc1Level.setValue(1.0f);
    addAndMakeVisible(labeledoscALevelKnob);
    osc1LevelVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc1Level", osc1Level);
    
    osc2Level.setRange(0.0f, 1.0f);
    osc2Level.setValue(1.0f);
    addAndMakeVisible(labeledOsc2LevelKnob);
    osc2LevelVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc2Level", osc2Level);
    
    noiseLevel.setRange(0.0, 1.0f);
    noiseLevel.setValue(0.0f);
    addAndMakeVisible(labeledNoiseLevelKnob);
    noiseLevelVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "noiseLevel", noiseLevel);
    
   
}

Mixer::~Mixer()
{
}

void Mixer::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
//    GroupComponent::paint(g);
//    g.setFont(12);
//
    g.setFont(6);
//    mainGroup.paint(g);
    
    //    g.setColour (Colours::grey);
    //    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    //
    //    g.setColour (Colours::white);

    //    g.drawText ("Mixer", getLocalBounds(),
    //                Justification::centred, true);   // draw some placeholder text
}

void Mixer::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    
    auto bounds = getLocalBounds().reduced(5);
    
    mainGroup.setBounds(area);
    mainGroup.setColour(1, Colours::white);
    auto widgetsArea = bounds.reduced(10);
    widgetsArea.removeFromTop(5);
    int width = (widgetsArea.getWidth() - (7 - 1) * 7.5) / 3;
    labeledoscALevelKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(20);
    labeledOsc2LevelKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(20);
    labeledNoiseLevelKnob.setBounds(widgetsArea.removeFromLeft(width));
    
}
