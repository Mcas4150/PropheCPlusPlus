
#include "../JuceLibraryCode/JuceHeader.h"
#include "Glide.h"

//==============================================================================
Glide::Glide(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, glideRateKnob(0.0f, 0.99f, "%")
, labeledGlideRateKnob("RATE", glideRateKnob)

{
    setSize(125, 95);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("GLIDE");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);
    
    glideRateKnob.setRange(0.0f, 0.99f);
    glideRateKnob.setValue(0);
    addAndMakeVisible(labeledGlideRateKnob);
    glideRateVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "glideRate", glideRateKnob);
    
    glideModeToggle.setSliderStyle(Slider::SliderStyle::LinearVertical);
    glideModeToggle.setRange(0, 1);
    glideModeToggle.setValue(0);
    glideModeToggle.addListener(this);
    addAndMakeVisible(&glideModeToggle);
    glideModeVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.valTreeState, "glideMode", glideModeToggle);
    glideModeToggle.setLookAndFeel(&sliderToggleLookAndFeel);
    
    autoLabel.setText("AUTO", dontSendNotification);
    autoLabel.setFont (Font (9.0f, Font::bold));
    addAndMakeVisible(&autoLabel);
    normalLabel.setText("NORMAL", dontSendNotification);
    normalLabel.setFont (Font (9.0f, Font::bold));
    addAndMakeVisible(&normalLabel);
    
    
    
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
  
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    // This method is where you should set the bounds of any child
    // components that your component contains..
    labeledGlideRateKnob.setBounds(15, 20, 50, 65);
    
    autoLabel.setBounds(72, 25, 40, 10);
    glideModeToggle.setBounds(80, 35, 20, 30);
    normalLabel.setBounds(70, 68, 40, 10);
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
