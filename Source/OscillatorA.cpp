
#include "../JuceLibraryCode/JuceHeader.h"
#include "OscillatorA.h"

//==============================================================================
OscillatorA::OscillatorA(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, osc1FreqKnob(-2.0, 2.0f, "st")
, labeledoscAFreqKnob("FREQUENCY", osc1FreqKnob)
, osc1OctKnob(0.0f, 3.0f, "oct")
, labeledoscAOctKnob("OCTAVE", osc1OctKnob)
, osc1PulseWidthKnob(0.0f, 0.99f, "st")
, labeledoscAPulseWidthKnob("PW", osc1PulseWidthKnob)
{
    setSize(275, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("OSCILLATOR A");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);
    
    osc1FreqKnob.setRange(-2.0, 2.0f);
    osc1FreqKnob.setValue(0.0f);
    addAndMakeVisible(labeledoscAFreqKnob);
    osc1FreqVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc1Freq", osc1FreqKnob);
    
    osc1OctKnob.setRange(0.0f, 3.0f);
    osc1OctKnob.setValue(0.0f);
    addAndMakeVisible(labeledoscAOctKnob);
    osc1OctVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc1Oct", osc1OctKnob);
    
    osc1PulseWidthKnob.setRange(0.0f, 0.99f);
    osc1PulseWidthKnob.setValue(0.0);
    addAndMakeVisible(labeledoscAPulseWidthKnob)
    ;
    osc1PulseWidthVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc1PW", osc1PulseWidthKnob);
    

    osc1SawShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1SawShapeToggle.setRange(0, 1);
    osc1SawShapeToggle.setValue(1);
    osc1SawShapeToggle.addListener(this);
    addAndMakeVisible(&osc1SawShapeToggle);
    
    osc1SawShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc1SawMode", osc1SawShapeToggle);
    
    osc1SquareShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1SquareShapeToggle.setRange(0, 1);
    osc1SquareShapeToggle.setValue(0);
    osc1SquareShapeToggle.addListener(this);
    addAndMakeVisible(&osc1SquareShapeToggle);
    
    osc1SquareShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc1SquareMode", osc1SquareShapeToggle);
    
    
    osc1SyncToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1SyncToggle.setRange(0, 1);
    osc1SyncToggle.setValue(0);
    osc1SyncToggle.addListener(this);
    addAndMakeVisible(&osc1SyncToggle);
    
    osc1SyncVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc1Sync", osc1SyncToggle);
    
    
    waveSelection = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> (processor.valTreeState, "wavetype", oscMenu);
    
    
    osc1SawShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc1SquareShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc1SyncToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
}

OscillatorA::~OscillatorA()
{
}

void OscillatorA::paint (Graphics& g)
{

    juce::Rectangle <float> sawLabel (135, 25, 20, 10);
    juce::Rectangle <float> squareLabel (160, 25, 20, 10);
    
    Image sawImage = ImageCache::getFromMemory (BinaryData::saw_png, BinaryData::saw_pngSize);
    Image squareImage = ImageCache::getFromMemory (BinaryData::square_png, BinaryData::square_pngSize);
    
    g.drawImage(sawImage, sawLabel);
    g.drawImage(squareImage, squareLabel);
}

void OscillatorA::resized()
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


void OscillatorA::sliderValueChanged(Slider* slider)
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
