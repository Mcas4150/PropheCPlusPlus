
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
    
    
    enum Waveform
    {
        kWaveformSine = 0,
        kWaveformTriangle,
        kWaveformSquare,
        kWaveformSquareSlopedEdges,
        kNumWaveforms
    };
    
    static void populateWaveformComboBox(ComboBox& cb);
    void sliderValueChanged (Slider*) override;
    
    static float getSample(float phase, Waveform waveform);
    
private:
    //    Slider lfoRate, lfoDelay;
    ComboBox lfoMenu;
    
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
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> lfoSelect;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> rateVal;
//    delete
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayVal;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO)
};
