
#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, osc1FreqKnob(-2.0, 2.0f, "st")
, labeledoscAFreqKnob("FREQUENCY", osc1FreqKnob)
, osc1OctKnob(0.0f, 3.0f, "oct")
, labeledoscAOctKnob("OCTAVE", osc1OctKnob)
, osc1PulseWidthKnob(0, 3, "st")
, labeledoscAPulseWidthKnob("PW", osc1PulseWidthKnob)
{
    setSize(275, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("OSCILLATOR A");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    addAndMakeVisible(&mainGroup);
    
    osc1FreqKnob.setRange(-2.0, 2.0f);
    osc1FreqKnob.setValue(0.0f);
    addAndMakeVisible(labeledoscAFreqKnob);
    osc1FreqVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc1Freq", osc1FreqKnob);
    
    osc1OctKnob.setRange(0.0f, 3.0f);
    osc1OctKnob.setValue(0.0f);
    addAndMakeVisible(labeledoscAOctKnob);
    osc1OctVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc1Oct", osc1OctKnob);
    
    osc1PulseWidthKnob.setRange(0, 3);
    osc1PulseWidthKnob.setValue(0);
    addAndMakeVisible(labeledoscAPulseWidthKnob);
    osc1PulseWidthVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc1PulseWidth", osc1PulseWidthKnob);
    
    
    
    //    oscMenu.addItem("Square", 1);
    //    oscMenu.addItem("Saw", 2);
    //    oscMenu.addItem("Triangle", 3);
    //    oscMenu.addItem("Sine", 4);
    //
    //    oscMenu.setJustificationType(Justification::centred);
    //    addAndMakeVisible(&oscMenu);
    
    osc1SawShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1SawShapeToggle.setRange(0, 1);
    osc1SawShapeToggle.setValue(1);
    osc1SawShapeToggle.addListener(this);
    addAndMakeVisible(&osc1SawShapeToggle);
    
    osc1SawShapeVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc1SawMode", osc1SawShapeToggle);
    
    osc1SquareShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1SquareShapeToggle.setRange(0, 1);
    osc1SquareShapeToggle.setValue(0);
    osc1SquareShapeToggle.addListener(this);
    addAndMakeVisible(&osc1SquareShapeToggle);
    
    osc1SquareShapeVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc1SquareMode", osc1SquareShapeToggle);
    
    
    osc1SyncToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1SyncToggle.setRange(0, 1);
    osc1SyncToggle.setValue(0);
    osc1SyncToggle.addListener(this);
    addAndMakeVisible(&osc1SyncToggle);
    
    osc1SyncVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc1Sync", osc1SyncToggle);
    
    
    waveSelection = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype", oscMenu);
    
    
    osc1SawShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc1SquareShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc1SyncToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
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
    
    juce::Rectangle <float> sawLabel (135, 25, 20, 10);
    juce::Rectangle <float> squareLabel (160, 25, 20, 10);
    
    Image sawImage = ImageCache::getFromMemory (BinaryData::saw_png, BinaryData::saw_pngSize);
    Image squareImage = ImageCache::getFromMemory (BinaryData::square_png, BinaryData::square_pngSize);
    
    g.drawImage(sawImage, sawLabel);
    g.drawImage(squareImage, squareLabel);
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
    widgetsArea.removeFromTop(5);
    int width = (widgetsArea.getWidth() - (4 - 1) * 10) / 4;
    labeledoscAFreqKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    labeledoscAOctKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    osc1SawShapeToggle.setBounds(135, 35, 20, 30);
    widgetsArea.removeFromLeft(5);
    osc1SquareShapeToggle.setBounds(160, 35, 20, 30);
    widgetsArea.removeFromLeft(40);
    labeledoscAPulseWidthKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(5);
    osc1SyncToggle.setBounds(235, 35, 20, 30);
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
