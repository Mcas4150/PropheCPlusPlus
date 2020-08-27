
#include "../JuceLibraryCode/JuceHeader.h"
#include "LFO.h"
#include <cmath>



LFO::LFO(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, lfoRate(0.1, 30, "Hz")
, labeledLfoRate("FREQUENCY", lfoRate)
{
    setSize(165, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("LFO");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);
    
    
    lfoRate.setRange(0.1f, 30.0f);
    //    lfoRate.setSkewFactorFromMidPoint(15);
    lfoRate.setValue (0.1f);
    addAndMakeVisible(labeledLfoRate);
    rateVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "lfoRate", lfoRate);
    
    
    lfoSawShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    lfoSawShapeToggle.setRange(0, 1);
    lfoSawShapeToggle.setValue(1);
    lfoSawShapeToggle.addListener(this);
    addAndMakeVisible(&lfoSawShapeToggle);
    
    lfoSawShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "lfoSawMdoe", lfoSawShapeToggle);
    
    lfoTriangleShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    lfoTriangleShapeToggle.setRange(0, 1);
    lfoTriangleShapeToggle.setValue(0);
    lfoTriangleShapeToggle.addListener(this);
    addAndMakeVisible(&lfoTriangleShapeToggle);
    
    lfoTriangleShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "lfoTriangleMode", lfoTriangleShapeToggle);
    
    lfoSquareShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    lfoSquareShapeToggle.setRange(0, 1);
    lfoSquareShapeToggle.setValue(0);
    lfoSquareShapeToggle.addListener(this);
    addAndMakeVisible(&lfoSquareShapeToggle);
    
    lfoSquareShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "lfoSquareMode", lfoSquareShapeToggle);
    
    
    lfoSawShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    lfoTriangleShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    lfoSquareShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    
    
}

LFO::~LFO()
{
}

void LFO::paint (Graphics& g)
{
    juce::Rectangle <float> sawLabel (70, 25, 20, 10);
    juce::Rectangle <float> triangleLabel (95, 25, 20, 10);
    juce::Rectangle <float> squareLabel (120, 25, 20, 10);
    
    Image sawImage = ImageCache::getFromMemory (BinaryData::saw_png, BinaryData::saw_pngSize);
    Image triangleImage = ImageCache::getFromMemory (BinaryData::triangle_png, BinaryData::triangle_pngSize);
    Image squareImage = ImageCache::getFromMemory (BinaryData::square_png, BinaryData::square_pngSize);
    
    g.drawImage(sawImage, sawLabel);
    g.drawImage(triangleImage, triangleLabel);
    g.drawImage(squareImage, squareLabel);
}

void LFO::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    
    auto bounds = getLocalBounds().reduced(5);
    
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    auto widgetsArea = bounds.reduced(10);
    labeledLfoRate.setBounds(15, 20, 50, 65);
    widgetsArea.removeFromLeft(10);
    lfoSawShapeToggle.setBounds(70, 35, 20, 30);
    widgetsArea.removeFromLeft(5);
    lfoTriangleShapeToggle.setBounds(95, 35, 20, 30);
    widgetsArea.removeFromLeft(5);
    lfoSquareShapeToggle.setBounds(120, 35, 20, 30);
}


void LFO::sliderValueChanged(Slider* slider)
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
