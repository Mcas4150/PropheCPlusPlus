

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"
#include "SliderLookAndFeel.h"

//==============================================================================
/*
 */
class OscillatorB    : public Component, public Slider::Listener
{
public:
    OscillatorB(JuceSynthFrameworkAudioProcessor&);
    ~OscillatorB();
    
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    
private:
    JuceSynthFrameworkAudioProcessor& processor;
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;

    GroupComponent mainGroup;
    //    Slider Blendslider;
    
    BasicKnob osc2FreqKnob; LabeledKnob labeledOsc2FreqKnob;
    BasicKnob osc2OctKnob; LabeledKnob labeledOsc2OctKnob;
    BasicKnob osc2PulseWidthKnob; LabeledKnob labeledOsc2PulseWidthKnob;
    Slider osc2SawShapeToggle;
    Slider osc2SquareShapeToggle;
    Slider osc2TriangleShapeToggle;
    Slider osc2LoFreqToggle;
    Label lowLabel;
    Label offLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2SawShapeVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2SquareShapeVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2TriangleShapeVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2LoFreqVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2FreqVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2OctVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2PulseWidthVal;
    
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    GroupLookAndFeel groupLookAndFeel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorB)
};
