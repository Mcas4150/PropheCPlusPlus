

#include "../JuceLibraryCode/JuceHeader.h"
#include "OscillatorB.h"

//==============================================================================
OscillatorB::OscillatorB(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, osc2FreqKnob(-2.0, 2.0, "st")
, labeledOsc2FreqKnob("FREQUENCY", osc2FreqKnob)
, osc2OctKnob(0.0f, 3.0f, "oct")
, labeledOsc2OctKnob("OCTAVE", osc2OctKnob)
, osc2PulseWidthKnob(0, 3, "st")
, labeledOsc2PulseWidthKnob("PW", osc2PulseWidthKnob)

{
    setSize(330, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("OSCILLATOR B");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);
    
    using Attachment = SliderParameterAttachment;
 
    osc2FreqKnob.setRange(-2.0, 2.0f);
    osc2FreqKnob.setValue(0.0f);
    addAndMakeVisible(labeledOsc2FreqKnob);
    osc2FreqVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc2Freq", osc2FreqKnob);
    
    osc2OctKnob.setRange(0.0f, 3.0f);
    osc2OctKnob.setValue(0.0f);
    addAndMakeVisible(labeledOsc2OctKnob);
    osc2OctVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc2Oct", osc2OctKnob);
    
    osc2PulseWidthKnob.setRange(0, 3);
    osc2PulseWidthKnob.setValue(0);
    addAndMakeVisible(labeledOsc2PulseWidthKnob);
    osc2PulseWidthVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc2PW", osc2PulseWidthKnob);
    
    osc2SawShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2SawShapeToggle.setRange(0, 1);
    osc2SawShapeToggle.setValue(1);
    osc2SawShapeToggle.addListener(this);
    addAndMakeVisible(&osc2SawShapeToggle);
    
    osc2SawShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc2SawMode", osc2SawShapeToggle);
    
    osc2SquareShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2SquareShapeToggle.setRange(0, 1);
    osc2SquareShapeToggle.setValue(0);
    osc2SquareShapeToggle.addListener(this);
    addAndMakeVisible(&osc2SquareShapeToggle);
    
    osc2SquareShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc2SquareMode", osc2SquareShapeToggle);
    
    
    osc2TriangleShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2TriangleShapeToggle.setRange(0, 1);
    osc2TriangleShapeToggle.setValue(0);
    osc2TriangleShapeToggle.addListener(this);
    addAndMakeVisible(&osc2TriangleShapeToggle);
    
    osc2TriangleShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc2TriangleMode", osc2TriangleShapeToggle);
    
    
    osc2SawShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2SquareShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2TriangleShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    
    osc2TriangleShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2TriangleShapeToggle.setRange(0, 1);
    osc2TriangleShapeToggle.setValue(0);
    osc2TriangleShapeToggle.addListener(this);
    addAndMakeVisible(&osc2TriangleShapeToggle);
    
    osc2TriangleShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc2TriangleMode", osc2TriangleShapeToggle);
    
    osc2LoFreqToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2LoFreqToggle.setRange(0, 1);
    osc2LoFreqToggle.setValue(0);
    osc2LoFreqToggle.addListener(this);
    addAndMakeVisible(&osc2LoFreqToggle);
    
    osc2LoFreqVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc2LoFreqMode", osc2LoFreqToggle);
    
    
    osc2SawShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2SquareShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2TriangleShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2LoFreqToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    lowLabel.setText("Low", dontSendNotification);
    lowLabel.setFont (Font (9.0f, Font::bold));
    addAndMakeVisible(&lowLabel);
    offLabel.setText("off", dontSendNotification);
    offLabel.setFont (Font (9.0f, Font::bold));
    addAndMakeVisible(&offLabel);
}

OscillatorB::~OscillatorB()
{
}

void OscillatorB::paint (Graphics& g)
{

    
    juce::Rectangle <float> sawLabel (135, 25, 20, 10);
    juce::Rectangle <float> triangleLabel (160, 25, 20, 10);
    juce::Rectangle <float> squareLabel (185, 25, 20, 10);
    
    Image sawImage = ImageCache::getFromMemory (BinaryData::saw_png, BinaryData::saw_pngSize);
    Image triangleImage = ImageCache::getFromMemory (BinaryData::triangle_png, BinaryData::triangle_pngSize);
    Image squareImage = ImageCache::getFromMemory (BinaryData::square_png, BinaryData::square_pngSize);
    
    g.drawImage(sawImage, sawLabel);
    g.drawImage(triangleImage, triangleLabel);
    g.drawImage(squareImage, squareLabel);
}

void OscillatorB::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    
    auto bounds = getLocalBounds().reduced(5);
    
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    auto widgetsArea = bounds.reduced(10);
   
    widgetsArea.removeFromTop(5);
    int width = (widgetsArea.getWidth() - (4 - 1) * 10) / 5;
   
    labeledOsc2FreqKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    labeledOsc2OctKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    osc2SawShapeToggle.setBounds(135, 35, 20, 30);
    widgetsArea.removeFromLeft(5);
    osc2TriangleShapeToggle.setBounds(160, 35, 20, 30);
    widgetsArea.removeFromLeft(5);
    osc2SquareShapeToggle.setBounds(185, 35, 20, 30);
    widgetsArea.removeFromLeft(55);
    labeledOsc2PulseWidthKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(5);
    osc2LoFreqToggle.setBounds(265, 35, 20, 30);
    widgetsArea.removeFromLeft(55);
    //    oscSyncToggle.setBounds(235, 35, 20, 30);
    
}

void OscillatorB::sliderValueChanged(Slider* slider)
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
