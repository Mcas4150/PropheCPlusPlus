/*
 ==============================================================================
 
 Wheels.cpp
 Created: 29 May 2019 12:51:45pm
 Author:  Mike Cassidy
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "Wheels.h"

//==============================================================================
Wheels::Wheels(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
{
    
    setSize(100, 150);
    //    setLookAndFeel(pitchBendLookAndFeel);
    
    
    pitchBendSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    pitchBendSlider.setRange(-1.0f, 1.0f);
    pitchBendSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&pitchBendSlider);
    pitchBendSlider.setLookAndFeel(&pitchBendLookAndFeel);
    pitchBendSlider.addListener(this);
    
    pitchBendVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (*processor.valTreeState, "pitchBend", pitchBendSlider);
    
}

Wheels::~Wheels()
{
    pitchBendVal = nullptr;
    pitchBendSlider.setLookAndFeel(nullptr);
}

void Wheels::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
    pitchBendSlider.setBounds(0, 45, 90, 30);
}

void Wheels::resized()
{
    
    
}

void Wheels::sliderValueChanged (Slider *slider)
{
    
    
}

void Wheels::sliderDragEnded(Slider *slider){
    slider->setValue(0);
}
