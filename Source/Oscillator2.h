

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
    
    BasicKnob oscBFreqKnob; LabeledKnob labeledOscBFreqKnob;
    BasicKnob oscBOctKnob; LabeledKnob labeledOscBOctKnob;
    BasicKnob oscBPulseWidthKnob; LabeledKnob labeledOscBPulseWidthKnob;
    Slider oscBSawShapeToggle;
    Slider oscBSquareShapeToggle;
    Slider oscBTriangleShapeToggle;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscBSawShapeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscBSquareShapeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscBTriangleShapeVal;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscBFreqVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscBOctVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscBPulseWidthVal;
    
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator2)
};
