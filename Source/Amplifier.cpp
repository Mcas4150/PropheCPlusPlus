

#include "../JuceLibraryCode/JuceHeader.h"
#include "Amplifier.h"

//==============================================================================
Amplifier::Amplifier(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, attackSlider(1.5f, 7400.0f, "ms")
, labeledAmpAttackKnob("ATTACK", attackSlider)
, decaySlider(0.5f, 11000.0f, "ms")
, labeledAmpDecayKnob("DECAY", decaySlider)
, sustainSlider(0.0f, 1.0f, "ms")
, labeledAmpSustainKnob("SUSTAIN", sustainSlider)
, releaseSlider(0.5f, 11000.0f, "ms")
, labeledAmpReleaseKnob("RELEASE", releaseSlider)
{
    setSize(250, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("AMPLIFIER");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    addAndMakeVisible(&mainGroup);
    
    
    //slider initialization values
    attackSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider.setRange(1.5f, 7400.0f);
    attackSlider.setValue(0.1f);
    attackSlider.addListener(this);
    attackVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);
    //        addAndMakeVisible(&attackSlider);
    addAndMakeVisible(labeledAmpAttackKnob);
    
    //        decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.5f, 11000.0f);
    decaySlider.setValue(1.0f);
    decaySlider.addListener(this);
    //        decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    //        addAndMakeVisible(&decaySlider);
    
    decayVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);
    addAndMakeVisible(labeledAmpDecayKnob);
    
    //        sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.addListener(this);
    //        sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    //        addAndMakeVisible(&sustainSlider);
    sustainVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);
    addAndMakeVisible(labeledAmpSustainKnob);
    
    //        releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.5f, 11000.0f);
    releaseSlider.setValue(0.8f);
    releaseSlider.addListener(this);
    //        releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    //        addAndMakeVisible(&releaseSlider);
    releaseVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);
    addAndMakeVisible(labeledAmpReleaseKnob);
    //sends value of the sliders to the tree state in the processor
    
    
    
}

Amplifier::~Amplifier()
{
    setLookAndFeel(nullptr);
}

void Amplifier::paint (Graphics& g)
{
    //fancy stuff for the UI background etc
    
    
    //    g.fillAll (Colours::black);
    //    g.fillAll (Colours:: 667966);
    juce::Rectangle <float> area (5, 5, 240, 90);
    //    Image background = ImageCache::getFromMemory (BinaryData::metal_jpg, BinaryData::metal_jpgSize);
    //    g.drawImage(background, area);
    g.setColour(Colours::white);
    //static positioning for now due to time, make dynamic later
    //    g.drawText ("A", 53, 50, 20, 20, Justification::centredTop);
    //    g.drawText ("D", 77, 50, 20, 20, Justification::centredTop);
    //    g.drawText ("S", 103, 50, 20, 20, Justification::centredTop);
    //    g.drawText ("R", 128, 50, 20, 20, Justification::centredTop);
    //    g.drawText("Envelope", 35, 30, 20, 75, Justification::centredTop);
    
    //    g.setColour(Colours::white);
    //    g.drawRoundedRectangle(area, 10.0f, 2.0f);
    
}

void Amplifier::resized()
{
    //draws the sliders...we use a rectangle object to dynamically size the UI (if we want to resize for IPad etc without needing to change ALL settings
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    
    auto bounds = getLocalBounds().reduced(5);
    
    mainGroup.setBounds(area);
    mainGroup.setColour(1, Colours::white);
    auto widgetsArea = bounds.reduced(10);
    widgetsArea.removeFromTop(5);
    int width = (widgetsArea.getWidth() - (4 - 1) * 10) / 4;
    labeledAmpAttackKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    labeledAmpDecayKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    labeledAmpSustainKnob.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    labeledAmpReleaseKnob.setBounds(widgetsArea.removeFromLeft(width));
    
    //draw sliders by reducing area from rectangle above
    //    attackSlider.setBounds (15, 15, 75, 75);
    //    decaySlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    //    sustainSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    //    releaseSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}



void Amplifier::sliderValueChanged(Slider* slider)
{
    
}
