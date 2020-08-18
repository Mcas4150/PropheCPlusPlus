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
, modAmtLfoKnob(0.0f, 1.0f, "")
, labeledModAmtLfoKnob("AMOUNT", modAmtLfoKnob)
{
    
    setSize(150, 285);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("MODULATION");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    
    /// MOD AMOUNTS
    
   // MOD FILTER ENV
    
    modAmtFilterEnvKnob.setRange(0.00, 1.00);
    modAmtFilterEnvKnob.setValue(0.00);
    addAndMakeVisible(labeledModAmtFilterEnvKnob);
    modAmtFilterEnvVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "modAmtFilterEnv", modAmtFilterEnvKnob);
    modAmtFilterEnvLabel.setText("FIL ENV", dontSendNotification);
    modAmtFilterEnvLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&modAmtFilterEnvLabel);

    // MOD OSC B
    
    osc2ModAmtKnob.setRange(0.00, 1.00);
    osc2ModAmtKnob.setValue(0.00);
    addAndMakeVisible(labeledOsc2ModAmtKnob);
    modAmtOscBVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "modAmtOscB", osc2ModAmtKnob);
    modAmtOscBLabel.setText("OSC B", dontSendNotification);
    modAmtOscBLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&modAmtOscBLabel);
    
    // MOD LFO
    
    modAmtLfoKnob.setRange(0.00, 1.00);
    modAmtLfoKnob.setValue(0.00);
    addAndMakeVisible(labeledModAmtLfoKnob);
    modAmtLfoVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "modAmtLfo", modAmtLfoKnob);
    modAmtLfoLabel.setText("LFO", dontSendNotification);
    modAmtLfoLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&modAmtLfoLabel);
    
    
    ///  TOGGLES
    
    // FROM TOGGLES
    
    filterEnvRouteToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    filterEnvRouteToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    filterEnvRouteToggle.setRange(0, 1);
    filterEnvRouteToggle.setValue(0);
    filterEnvRouteToggle.addListener(this);
    addAndMakeVisible(&filterEnvRouteToggle);
    filterEnvRouteToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "filterEnvRoute", filterEnvRouteToggle);
    
    
    osc2RouteToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2RouteToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2RouteToggle.setRange(0, 1);
    osc2RouteToggle.setValue(0);
    osc2RouteToggle.addListener(this);
    addAndMakeVisible(&osc2RouteToggle);
    osc2RouteToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "osc2Route", osc2RouteToggle);
    
    lfoRouteToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    lfoRouteToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    lfoRouteToggle.setRange(0, 1);
    lfoRouteToggle.setValue(0);
    lfoRouteToggle.addListener(this);
    addAndMakeVisible(& lfoRouteToggle);
    lfoRouteToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "lfoRoute",  lfoRouteToggle);
    
    
    // TO TOGGLES
    
    osc1FreqToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc1FreqToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1FreqToggle.setRange(0, 1);
    osc1FreqToggle.setValue(0);
    osc1FreqToggle.addListener(this);
    addAndMakeVisible(&osc1FreqToggle);
    osc1FreqToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "modOscAFreqMode", osc1FreqToggle);
    osc1FreqLabel.setText("OSC A FREQ", dontSendNotification);
    osc1FreqLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&osc1FreqLabel);
    
    
    osc1PWToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc1PWToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1PWToggle.setRange(0, 1);
    osc1PWToggle.setValue(0);
    osc1PWToggle.addListener(this);
    addAndMakeVisible(&osc1PWToggle);
    osc1PWLabel.setText("OSC A PW", dontSendNotification);
    osc1PWLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&osc1PWLabel);
    osc1PWToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "modOscAPWMode", osc1PWToggle);
    
    
    osc2FreqToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2FreqToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2FreqToggle.setRange(0, 1);
    osc2FreqToggle.setValue(0);
    osc2FreqToggle.addListener(this);
    addAndMakeVisible(&osc2FreqToggle);
    osc2FreqLabel.setText("OSC B FREQ", dontSendNotification);
    osc2FreqLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&osc2FreqLabel);
    osc2FreqToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "modOscBFreqMode", osc2FreqToggle);
    
    
    osc2PWToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    osc2PWToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2PWToggle.setRange(0, 1);
    osc2PWToggle.setValue(0);
    osc2PWToggle.addListener(this);
    addAndMakeVisible(&osc2PWToggle);
    osc2PWLabel.setText("OSC B PW", dontSendNotification);
    osc2PWLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&osc2PWLabel);
    osc2PWToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "modOscBPWMode", osc2PWToggle);

    
    filterToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    filterToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    filterToggle.setRange(0, 1);
    filterToggle.setValue(0);
    filterToggle.addListener(this);
    addAndMakeVisible(&filterToggle);
    filterLabel.setText("FILTER", dontSendNotification);
    filterLabel.setFont (Font (8.0f, Font::bold));
    addAndMakeVisible(&filterLabel);
    filterToggleVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "modFilterMode", filterToggle);
    
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
    modAmtFilterEnvLabel.setBounds(40, 70, 40, 40 );
    labeledOsc2ModAmtKnob.setBounds(15, 115, 50, 65);
    modAmtOscBLabel.setBounds(40, 160, 40, 40 );
    osc2RouteToggle.setBounds(70, 125, 20, 30);
    labeledModAmtLfoKnob.setBounds(15, 205, 50, 65);
    lfoRouteToggle.setBounds(70, 215, 20, 30);
    modAmtLfoLabel.setBounds(40, 250, 40, 40 );
    osc1FreqToggle.setBounds(112, 25, 20, 40);
    osc1FreqLabel.setBounds(102, 52, 40, 30);
    osc1PWToggle.setBounds(112, 75, 20, 40);
    osc1PWLabel.setBounds(102, 102, 40, 30);
    osc2FreqToggle.setBounds(112, 125, 20, 40);
    osc2FreqLabel.setBounds(102, 152, 40, 30);
    osc2PWToggle.setBounds(112, 175, 20, 40);
    osc2PWLabel.setBounds(102, 202, 40, 30);
    filterToggle.setBounds(112, 225, 20, 40);
    filterLabel.setBounds(102, 252, 40, 30);
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
