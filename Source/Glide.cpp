
#include "../JuceLibraryCode/JuceHeader.h"
#include "Glide.h"

//==============================================================================
Glide::Glide(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, glideRateKnob(0.0f, 0.99f, "")
, labeledGlideRateKnob("RATE", glideRateKnob)

{
    setSize(125, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("GLIDE");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    addAndMakeVisible(&mainGroup);
    
    glideRateKnob.setRange(0.0f, 0.99f);
    glideRateKnob.setValue(0);
    addAndMakeVisible(labeledGlideRateKnob);
    glideRateVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "glideRate", glideRateKnob);
    
    glideModeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    glideModeToggle.setRange(0, 1);
    glideModeToggle.setValue(0);
    glideModeToggle.addListener(this);
    addAndMakeVisible(&glideModeToggle);
    glideModeVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "glideMode", glideModeToggle);
    glideModeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
}

Glide::~Glide()
{
}

void Glide::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
}

void Glide::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    auto bounds = getLocalBounds().reduced(5);
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    // This method is where you should set the bounds of any child
    // components that your component contains..
    labeledGlideRateKnob.setBounds(15, 20, 50, 65);
    glideModeToggle.setBounds(80, 35, 20, 30);
}

void Glide::sliderValueChanged(Slider* slider)
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
