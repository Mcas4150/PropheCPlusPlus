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
, modAmtFilterEnvKnob(0.0f, 1.0f, "")
, labeledModAmtFilterEnvKnob("AMOUNT", modAmtFilterEnvKnob)
, osc2ModAmtKnob(0.0f, 1.0f, "")
, labeledOsc2ModAmtKnob("AMOUNT", osc2ModAmtKnob)
, modAmtLfoKnob(0.0f, 1.0f, "%")
, labeledModAmtLfoKnob("AMOUNT", modAmtLfoKnob)
{
    
    setSize(150, 285);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("MODULATION");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    addAndMakeVisible(&mainGroup);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    modAmtFilterEnvKnob.setRange(1, 5);
    modAmtFilterEnvKnob.setValue(1);
    addAndMakeVisible(labeledModAmtFilterEnvKnob);
    lfoFilterVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "", modAmtFilterEnvKnob);
    
    osc2ModAmtKnob.setRange(1, 5);
    osc2ModAmtKnob.setValue(1);
    addAndMakeVisible(labeledOsc2ModAmtKnob);
    osc2ModAmtVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc2ModAmt", osc2ModAmtKnob);
    
    modAmtLfoKnob.setRange(0.00, 1.00);
    modAmtLfoKnob.setValue(0.00);
    addAndMakeVisible(labeledModAmtLfoKnob);
    modAmtLfoVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "modAmtLfo", modAmtLfoKnob);
    
    filterEnvRouteToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    filterEnvRouteToggle.setRange(0, 1);
    filterEnvRouteToggle.setValue(1);
    filterEnvRouteToggle.addListener(this);
    addAndMakeVisible(&filterEnvRouteToggle);
    
    filterEnvRouteToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterEnvRoute", filterEnvRouteToggle);
    
    osc2RouteToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2RouteToggle.setRange(0, 1);
    osc2RouteToggle.setValue(1);
    osc2RouteToggle.addListener(this);
    addAndMakeVisible(&osc2RouteToggle);
    
    osc2RouteToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc2Route", osc2RouteToggle);
    
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
    
    oscAFreqToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscAFreqToggle", oscAFreqToggle);
    
    oscAPWToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscAPWToggle.setRange(0, 2);
    oscAPWToggle.setValue(1);
    oscAPWToggle.addListener(this);
    addAndMakeVisible(&oscAPWToggle);
    
    oscAPWToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscAPW", oscAPWToggle);
    
    osc2FreqToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2FreqToggle.setRange(0, 2);
    osc2FreqToggle.setValue(1);
    osc2FreqToggle.addListener(this);
    addAndMakeVisible(&osc2FreqToggle);
    
    osc2FreqToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc2FreqToggle", osc2FreqToggle);
    
    osc2PWToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2PWToggle.setRange(0, 2);
    osc2PWToggle.setValue(1);
    osc2PWToggle.addListener(this);
    addAndMakeVisible(&osc2PWToggle);
    
    osc2PWToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc2PW", osc2PWToggle);
    
    filterToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    filterToggle.setRange(0, 2);
    filterToggle.setValue(1);
    filterToggle.addListener(this);
    addAndMakeVisible(&filterToggle);
    
    filterToggleVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterToggle", filterToggle);
    
    
    filterEnvRouteToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2RouteToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    lfoRouteToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscAFreqToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    oscAPWToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2FreqToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2PWToggle.setLookAndFeel(&sliderToggleLookAndFeel);
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
    labeledModAmtFilterEnvKnob.setBounds(15, 25, 50, 65);
    filterEnvRouteToggle.setBounds(70, 35, 20, 30);
    
    labeledOsc2ModAmtKnob.setBounds(15, 115, 50, 65);
    osc2RouteToggle.setBounds(70, 125, 20, 30);
    labeledModAmtLfoKnob.setBounds(15, 205, 50, 65);
    lfoRouteToggle.setBounds(70, 215, 20, 30);
    
    oscAFreqToggle.setBounds(112, 25, 20, 40);
    oscAPWToggle.setBounds(112, 75, 20, 40);
    osc2FreqToggle.setBounds(112, 125, 20, 40);
    osc2PWToggle.setBounds(112, 175, 20, 40);
    filterToggle.setBounds(112, 225, 20, 40);
    //   .setBounds (100, 65, 25, 100);
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
