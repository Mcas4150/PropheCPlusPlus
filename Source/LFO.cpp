
#include "../JuceLibraryCode/JuceHeader.h"
#include "LFO.h"
#include <cmath>
#define TWOPI_F 6.283185f


void LFO::populateWaveformComboBox(ComboBox& cb)
{
    cb.clear(dontSendNotification);
    int itemNumber = 0;
    cb.addItem("Sine", ++itemNumber);
    cb.addItem("Triangle", ++itemNumber);
    cb.addItem("Square", ++itemNumber);
    cb.addItem("Square (sloped edges)", ++itemNumber);
}

// Function for calculating "biased" LFO waveforms with output range [0, 1].
// Phase range [0, 1], output also [0, 1] (not [-1, +1] as for the ordinary Sine function).
float LFO::getSample(float phase, Waveform waveform)
{
    switch (waveform)
    {
        case kWaveformTriangle:
            if (phase < 0.25f)
                return 0.5f + 2.0f*phase;
            else if (phase < 0.75f)
                return 1.0f - 2.0f*(phase - 0.25f);
            else
                return 2.0f*(phase - 0.75f);
        case kWaveformSquare:
            if (phase < 0.5f)
                return 1.0f;
            else
                return 0.0f;
        case kWaveformSquareSlopedEdges:
            if (phase < 0.48f)
                return 1.0f;
            else if (phase < 0.5f)
                return 1.0f - 50.0f*(phase - 0.48f);
            else if (phase < 0.98f)
                return 0.0f;
            else
                return 50.0f*(phase - 0.98f);
        case kWaveformSine:
        default:
            return 0.5f + 0.5f*sinf(TWOPI_F * phase);
    }
}





LFO::LFO(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, lfoRate(0, 30, "")
, labeledLfoRate("FREQUENCY", lfoRate)
{
    setSize(165, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("LFO");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);
    
    
    lfoRate.setRange(0, 30);
    //    lfoRate.setSkewFactorFromMidPoint(15);
    lfoRate.setValue (0);
    addAndMakeVisible(labeledLfoRate);
    rateVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "lfoRate", lfoRate);
    
    
    //    lfoDelay.setSliderStyle(Slider::SliderStyle::LinearVertical);
    //    lfoDelay.setRange(0, 30);
    //    lfoDelay.setSkewFactorFromMidPoint(15);
    //    lfoDelay.setValue (0);
    //    lfoDelay.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    //    addAndMakeVisible(&lfoDelay);
    //    delayVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "lfoDelay", lfoDelay);
    
    
    
    //    lfoSelect = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> (processor.valTreeState, "lfoMenu", lfoMenu);
    //
    //
    //    lfoMenu.addItem("Sine", 1);
    //    lfoMenu.addItem("Triangle", 2);
    //    lfoMenu.addItem("Square", 3);
    //    lfoMenu.addItem("SquareSlopedEdges", 4);
    //    lfoMenu.setJustificationType(Justification::centred);
    //    addAndMakeVisible(&lfoMenu);
    
    
    lfoSawShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    lfoSawShapeToggle.setRange(0, 1);
    lfoSawShapeToggle.setValue(1);
    lfoSawShapeToggle.addListener(this);
    addAndMakeVisible(&lfoSawShapeToggle);
    
    lfoSawShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "lfoSawShape", lfoSawShapeToggle);
    
    lfoSquareShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    lfoSquareShapeToggle.setRange(0, 1);
    lfoSquareShapeToggle.setValue(0);
    lfoSquareShapeToggle.addListener(this);
    addAndMakeVisible(&lfoSquareShapeToggle);
    
    lfoSquareShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "lfoSquareShape", lfoSquareShapeToggle);
    
    
    lfoTriangleShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    lfoTriangleShapeToggle.setRange(0, 1);
    lfoTriangleShapeToggle.setValue(0);
    lfoTriangleShapeToggle.addListener(this);
    addAndMakeVisible(&lfoTriangleShapeToggle);
    
    lfoTriangleShapeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "lfoTriangleShape", lfoTriangleShapeToggle);
    
    
    lfoSawShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    lfoSquareShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    lfoTriangleShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    
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
