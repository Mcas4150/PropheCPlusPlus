
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"
#include "SliderLookAndFeel.h"

class LFO    : public Component, public Slider::Listener
{
public:
    LFO(JuceSynthFrameworkAudioProcessor&);
    ~LFO();
    
    void paint (Graphics&) override;
    void resized() override;
    

    void sliderValueChanged (Slider*) override;
    

    
private:
    JuceSynthFrameworkAudioProcessor& processor;

    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    GroupLookAndFeel groupLookAndFeel;
    
    GroupComponent mainGroup;
    
    BasicKnob lfoRate; LabeledKnob labeledLfoRate;
    
    Slider lfoSawShapeToggle;
    Slider lfoSquareShapeToggle;
    Slider lfoTriangleShapeToggle;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoSawShapeVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoSquareShapeVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoTriangleShapeVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> rateVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayVal;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO)
};
