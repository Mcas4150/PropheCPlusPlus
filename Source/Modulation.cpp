/*
 ==============================================================================
 
 Modulation.cpp
 Created: 28 May 2019 9:44:32pm
 Author:  Mike Cassidy
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "Modulation.h"

//==============================================================================
Modulation::Modulation(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, lfoFilterEnv(0.0f, 1.0f, "")
, labeledLfoFilterEnv("AMOUNT", lfoFilterEnv)
, oscBModAmtKnob(0.0f, 1.0f, "")
, labeledOscBModAmtKnob("AMOUNT", oscBModAmtKnob)
, lfoModAmtKnob(0.0f, 1.0f, "%")
, labeledLfoModAmtKnob("AMOUNT", lfoModAmtKnob)
{
    
    setSize(150, 285);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("MODULATION");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    addAndMakeVisible(&mainGroup);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    lfoFilterEnv.setRange(1, 5);
    lfoFilterEnv.setValue(1);
    addAndMakeVisible(labeledLfoFilterEnv);
    lfoFilterVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "lfoFilterEnv", lfoFilterEnv);
    
    oscBModAmtKnob.setRange(1, 5);
    oscBModAmtKnob.setValue(1);
    addAndMakeVisible(labeledOscBModAmtKnob);
    oscBModAmtVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscBModAmt", oscBModAmtKnob);
    
    lfoModAmtKnob.setRange(0.00, 1.00);
    lfoModAmtKnob.setValue(0.00);
    addAndMakeVisible(labeledLfoModAmtKnob);
    lfoModAmtVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "lfoModAmt", lfoModAmtKnob);
    
    filterEnvRouteToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    filterEnvRouteToggle.setRange(0, 1);
    filterEnvRouteToggle.setValue(1);
    filterEnvRouteToggle.addListener(this);
    addAndMakeVisible(&filterEnvRouteToggle);
    
    filterEnvRouteToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterEnvRoute", filterEnvRouteToggle);
    
    oscBRouteToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscBRouteToggle.setRange(0, 1);
    oscBRouteToggle.setValue(1);
    oscBRouteToggle.addListener(this);
    addAndMakeVisible(&oscBRouteToggle);
    
    oscBRouteToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscBRoute", oscBRouteToggle);
    
    lfoRouteToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    lfoRouteToggle.setRange(0, 1);
    lfoRouteToggle.setValue(1);
    lfoRouteToggle.addListener(this);
    addAndMakeVisible(& lfoRouteToggle);
    
    lfoRouteToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "lfoRoute",  lfoRouteToggle);
    
    oscAFreqToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscAFreqToggle.setRange(0, 2);
    oscAFreqToggle.setValue(1);
    oscAFreqToggle.addListener(this);
    addAndMakeVisible(&oscAFreqToggle);
    
    oscAFreqToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscAFreq", oscAFreqToggle);
    
    oscAPWToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscAPWToggle.setRange(0, 2);
    oscAPWToggle.setValue(1);
    oscAPWToggle.addListener(this);
    addAndMakeVisible(&oscAPWToggle);
    
    oscAPWToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscAPW", oscAPWToggle);
    
    oscBFreqToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscBFreqToggle.setRange(0, 2);
    oscBFreqToggle.setValue(1);
    oscBFreqToggle.addListener(this);
    addAndMakeVisible(&oscBFreqToggle);
    
    oscBFreqToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscBFreq", oscBFreqToggle);
    
    oscBPWToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscBPWToggle.setRange(0, 2);
    oscBPWToggle.setValue(1);
    oscBPWToggle.addListener(this);
    addAndMakeVisible(&oscBPWToggle);
    
    oscBPWToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscBPW", oscBPWToggle);
    
    filterToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    filterToggle.setRange(0, 2);
    filterToggle.setValue(1);
    filterToggle.addListener(this);
    addAndMakeVisible(&filterToggle);
    
    filterToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterToggle", filterToggle);
    
    
    filterEnvRouteToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscBRouteToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    lfoRouteToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscAFreqToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscAPWToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscBFreqToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscBPWToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    filterToggle.setLookAndFeel(&sliderToggleLookAndFeel);
}

Modulation::~Modulation()
{
}

void Modulation::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    Line<float> line (Point<float> (100, 25),
                      Point<float> (100, 270));
    g.setColour(Colours::silver);
    g.drawLine (line, 1);
    
    
}

void Modulation::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    auto bounds = getLocalBounds().reduced(5);
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    auto widgetsArea = bounds.reduced(10);
    auto bottomWidgetsArea = bounds.reduced(10);
    widgetsArea.removeFromTop(5);
    widgetsArea.removeFromBottom(175);
    bottomWidgetsArea.removeFromBottom(5);
    bottomWidgetsArea.removeFromTop(80);
    int width = (widgetsArea.getWidth() - (4 - 1) * 10) / 4;
    int height = (widgetsArea.getHeight());
    labeledLfoFilterEnv.setBounds(15, 25, 50, 65);
    filterEnvRouteToggle.setBounds(70, 35, 20, 30);
    
    labeledOscBModAmtKnob.setBounds(15, 115, 50, 65);
    oscBRouteToggle.setBounds(70, 125, 20, 30);
    labeledLfoModAmtKnob.setBounds(15, 205, 50, 65);
    lfoRouteToggle.setBounds(70, 215, 20, 30);
    
    oscAFreqToggle.setBounds(112, 25, 20, 40);
    oscAPWToggle.setBounds(112, 75, 20, 40);
    oscBFreqToggle.setBounds(112, 125, 20, 40);
    oscBPWToggle.setBounds(112, 175, 20, 40);
    filterToggle.setBounds(112, 225, 20, 40);
    //   lfoFilterEnv.setBounds (100, 65, 25, 100);
}



void Modulation::sliderValueChanged(Slider* slider)
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
