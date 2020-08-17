/*
 ==============================================================================
 
 Master.cpp
 Created: 28 May 2019 10:02:42pm
 Author:  Mike Cassidy
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "Master.h"

//==============================================================================
Master::Master(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, mastergainSlider(0.0f, 1.0f, "")
, labeledMasterGainKnob("VOLUME", mastergainSlider)
, masterTuneSlider(-1.0f, 1.0f, "")
, labeledMasterTuneKnob("TUNE", masterTuneSlider)
//    , scopeComponent(processor.getAudioBufferQueue())
{
    
    setSize(60, 220);
    setLookAndFeel(lookAndFeel);
    
    mastergainSlider.setRange(0.0f, 1.0f);
    mastergainSlider.setValue(1.0f);
    addAndMakeVisible(labeledMasterGainKnob);
    mastergainVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (*processor.valTreeState, "mastergain", mastergainSlider);
    
    
    masterTuneSlider.setRange(-1.0f, 1.0f);
    masterTuneSlider.setValue(0);
    addAndMakeVisible(labeledMasterTuneKnob);
    masterTuneVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (*processor.valTreeState, "masterTune", masterTuneSlider);
    
    //       addAndMakeVisible (scopeComponent);
}

Master::~Master()
{
}

void Master::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
    
}

void Master::resized()
{
    
   
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //    labeledMasterGainKnob.setBounds(915, 250, 50, 50);
    //    scopeComponent.setBounds(0, 10, 50, 50);
    
    labeledMasterTuneKnob.setBounds(0, 10, 50, 65);
    labeledMasterGainKnob.setBounds(0, 110, 50, 65);
    //    scopeComponent.setBounds(5 , 25, 75, 75);
}
