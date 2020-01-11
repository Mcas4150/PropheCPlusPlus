

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"
#include "SliderLookAndFeel.h"

//==============================================================================
/*
 */
class Oscillator2    : public Component, public Slider::Listener
{
public:
    Oscillator2(JuceSynthFrameworkAudioProcessor&);
    ~Oscillator2();
    
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    
private:
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    ComboBox osc2Menu;
    GroupComponent mainGroup;
    //    Slider Blendslider;
    
    BasicKnob osc2FreqKnob; LabeledKnob labeledOsc2FreqKnob;
    BasicKnob osc2OctKnob; LabeledKnob labeledOsc2OctKnob;
    BasicKnob osc2PulseWidthKnob; LabeledKnob labeledOsc2PulseWidthKnob;
    Slider osc2SawShapeToggle;
    Slider osc2SquareShapeToggle;
    Slider osc2TriangleShapeToggle;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2SawShapeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2SquareShapeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2TriangleShapeVal;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2FreqVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2OctVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2PulseWidthVal;
    
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    GroupLookAndFeel groupLookAndFeel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator2)
};
