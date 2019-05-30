

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator2.h"

//==============================================================================
Oscillator2::Oscillator2(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, oscBFreqKnob(-2.0, 2.0, "")
, labeledOscBFreqKnob("FREQUENCY", oscBFreqKnob)
, oscBOctKnob(0, 3, "st")
, labeledOscBOctKnob("OCTAVE", oscBOctKnob)
, oscBPulseWidthKnob(0, 3, "st")
, labeledOscBPulseWidthKnob("PW", oscBPulseWidthKnob)
{
    setSize(330, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("OSCILLATOR B");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    addAndMakeVisible(&mainGroup);
    
    //    osc2Menu.addItem("Saw", 1);
    //    osc2Menu.addItem("Square", 2);
    //    osc2Menu.addItem("Triangle", 3);
    //    osc2Menu.addItem("Sine", 4);
    //    osc2Menu.setJustificationType(Justification::centred);
    ////    addAndMakeVisible(&osc2Menu);
    ////
    //    waveSelection2 = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype2", osc2Menu);
    //
    //    //slider initialization values
    //    Blendslider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    //    Blendslider.setRange(0.0f, 1.0f);
    //    Blendslider.setValue(1.0f);
    //    Blendslider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    ////    addAndMakeVisible(&Blendslider);
    ////
    //    //sends value of the sliders to the tree state in the processor
    //    blendVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "blend", Blendslider);
    oscBFreqKnob.setRange(-2.0, 2.0f);
    oscBFreqKnob.setValue(0.0f);
    addAndMakeVisible(labeledOscBFreqKnob);
    oscBFreqVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc2Freq", oscBFreqKnob);
    
    oscBOctKnob.setRange(0, 3);
    oscBOctKnob.setValue(0);
    addAndMakeVisible(labeledOscBOctKnob);
    oscBOctVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscBOct", oscBOctKnob);
    
    oscBPulseWidthKnob.setRange(0, 3);
    oscBPulseWidthKnob.setValue(0);
    addAndMakeVisible(labeledOscBPulseWidthKnob);
    oscBPulseWidthVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscBPulseWidth", oscBPulseWidthKnob);
    
    oscBSawShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscBSawShapeToggle.setRange(0, 1);
    oscBSawShapeToggle.setValue(1);
    oscBSawShapeToggle.addListener(this);
    addAndMakeVisible(&oscBSawShapeToggle);
    
    oscBSawShapeVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscBSawShape", oscBSawShapeToggle);
    
    oscBSquareShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscBSquareShapeToggle.setRange(0, 1);
    oscBSquareShapeToggle.setValue(0);
    oscBSquareShapeToggle.addListener(this);
    addAndMakeVisible(&oscBSquareShapeToggle);
    
    oscBSquareShapeVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscBSquareShape", oscBSquareShapeToggle);
    
    
    oscBTriangleShapeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscBTriangleShapeToggle.setRange(0, 1);
    oscBTriangleShapeToggle.setValue(0);
    oscBTriangleShapeToggle.addListener(this);
    addAndMakeVisible(&oscBTriangleShapeToggle);
    
    oscBTriangleShapeVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscBTriangleShape", oscBTriangleShapeToggle);
    
    
    oscBSawShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscBSquareShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscBTriangleShapeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
}

Oscillator2::~Oscillator2()
{
}

void Oscillator2::paint (Graphics& g)
{
    //background stuff
    //    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    //
    ////    g.fillAll (Colours::black);
    //    g.setColour(Colours::white);
    //    g.drawText("Oscillator Two", titleArea, Justification::centredTop);
    //
    //
    //    juce::Rectangle <float> area (25, 25, 150, 150);
    ////    Image background = ImageCache::getFromMemory (BinaryData::metal_jpg, BinaryData::metal_jpgSize);
    ////    g.drawImage(background, area);
    //    g.setColour(Colours::silver);
    //    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator2::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    
    auto bounds = getLocalBounds().reduced(5);
    
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    auto widgetsArea = bounds.reduced(10);
    auto bottomWidgetsArea = bounds.reduced(10);
    widgetsArea.removeFromTop(5);
    int width = (widgetsArea.getWidth() - (4 - 1) * 10) / 5;
    int height = (widgetsArea.getHeight());
    labeledOscBFreqKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    labeledOscBOctKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    oscBSawShapeToggle.setBounds(135, 35, 20, 30);
    widgetsArea.removeFromLeft(5);
    oscBTriangleShapeToggle.setBounds(160, 35, 20, 30);
    widgetsArea.removeFromLeft(5);
    oscBSquareShapeToggle.setBounds(185, 35, 20, 30);
    widgetsArea.removeFromLeft(55);
    labeledOscBPulseWidthKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(5);
    //    oscSyncToggle.setBounds(235, 35, 20, 30);
    
}

void Oscillator2::sliderValueChanged(Slider* slider)
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
