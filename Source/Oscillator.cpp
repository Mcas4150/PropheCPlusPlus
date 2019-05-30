
#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, oscAFreqKnob(20.0f, 5000.0f, "hz")
, labeledOscAFreqKnob("FREQUENCY", oscAFreqKnob)
, oscAOctKnob(0, 3, "st")
, labeledOscAOctKnob("OCTAVE", oscAOctKnob)
, oscAPulseWidthKnob(0, 3, "st")
, labeledOscAPulseWidthKnob("PW", oscAPulseWidthKnob)
{
    setSize(275, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("OSCILLATOR A");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    addAndMakeVisible(&mainGroup);
    
    oscAFreqKnob.setRange(20.0f, 5000.0f);
    oscAFreqKnob.setValue(440.0f);
    addAndMakeVisible(labeledOscAFreqKnob);
    oscAFreqVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscAFreq", oscAFreqKnob);
    
    oscAOctKnob.setRange(0, 3);
    oscAOctKnob.setValue(0);
    addAndMakeVisible(labeledOscAOctKnob);
    oscAOctVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscAOct", oscAOctKnob);
    
    oscAPulseWidthKnob.setRange(0, 3);
    oscAPulseWidthKnob.setValue(0);
    addAndMakeVisible(labeledOscAPulseWidthKnob);
    oscAPulseWidthVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscAPulseWidth", oscAPulseWidthKnob);
    
    
    
    //    oscMenu.addItem("Square", 1);
    //    oscMenu.addItem("Saw", 2);
    //    oscMenu.addItem("Triangle", 3);
    //    oscMenu.addItem("Sine", 4);
    //
    //    oscMenu.setJustificationType(Justification::centred);
    //    addAndMakeVisible(&oscMenu);
    
    oscASawShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscASawShapeToggle.setRange(0, 1);
    oscASawShapeToggle.setValue(1);
    oscASawShapeToggle.addListener(this);
    addAndMakeVisible(&oscASawShapeToggle);
    
    oscASawShapeVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscASawShape", oscASawShapeToggle);
    
    oscASquareShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscASquareShapeToggle.setRange(0, 1);
    oscASquareShapeToggle.setValue(0);
    oscASquareShapeToggle.addListener(this);
    addAndMakeVisible(&oscASquareShapeToggle);
    
    oscASquareShapeVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscASquareShape", oscASquareShapeToggle);
    
    
    oscASyncToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscASyncToggle.setRange(0, 1);
    oscASyncToggle.setValue(0);
    oscASyncToggle.addListener(this);
    addAndMakeVisible(&oscASyncToggle);
    
    oscASyncVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscASync", oscASyncToggle);
    
    
    waveSelection = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype", oscMenu);
    
    
    oscASawShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscASquareShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscASyncToggle.setLookAndFeel(&sliderToggleLookAndFeel);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    //background stuff
    //    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    //
    ////    g.fillAll (Colours::black);
    //    g.setColour(Colours::white);
    //    g.drawText("Oscillator One", titleArea, Justification::centredTop);
    //
    //
    //    juce::Rectangle <float> area (25, 25, 150, 150);
    ////    Image background = ImageCache::getFromMemory (BinaryData::metal_jpg, BinaryData::metal_jpgSize);
    ////    g.drawImage(background, area);
    //   g.setColour(Colours::silver);
    //    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized()
{
    //    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    //    oscMenu.setBounds(area.removeFromTop(20));
    
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    
    auto bounds = getLocalBounds().reduced(5);
    
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    auto widgetsArea = bounds.reduced(10);
    auto bottomWidgetsArea = bounds.reduced(10);
    widgetsArea.removeFromTop(5);
    int width = (widgetsArea.getWidth() - (4 - 1) * 10) / 4;
    int height = (widgetsArea.getHeight());
    labeledOscAFreqKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    labeledOscAOctKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    oscASawShapeToggle.setBounds(135, 35, 20, 30);
    widgetsArea.removeFromLeft(5);
    oscASquareShapeToggle.setBounds(160, 35, 20, 30);
    widgetsArea.removeFromLeft(40);
    labeledOscAPulseWidthKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(5);
    oscASyncToggle.setBounds(235, 35, 20, 30);
}


void Oscillator::sliderValueChanged(Slider* slider)
{
    if(slider->getValue() == 1.0 || slider->getValue() == 0){
        return;
    }
    else if(slider->getValue() > 0.5){
        slider->setValue(1.0);
    } else {
        slider->setValue(0);
    }
}
