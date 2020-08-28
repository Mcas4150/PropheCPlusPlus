

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"
#include "SliderLookAndFeel.h"



//==============================================================================
/*
 */
class OscillatorA   : public Component, public Slider::Listener
{
public:
    OscillatorA(JuceSynthFrameworkAudioProcessor&);
    ~OscillatorA();
    
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    
    
    void setOsc1Freq(std::atomic<float>* setting)
    {
        osc1FreqSetting = std::pow(2,*setting);
    }
    
    void setOsc1Oct(std::atomic<float>* setting)
    {
        osc1OctSetting =  std::pow(2, *setting);
    }
    
    void setOsc1SawMode(std::atomic<float>* setting)
    {
        osc1SawSetting = *setting;
    }
    
    void setOsc1SquareMode(std::atomic<float>* setting)
    {
        osc1SquareSetting = *setting;
    }
    
    void setOsc1PWSetting(std::atomic<float>* setting)
    {
        osc1PWSetting = *setting;
    }
      
    
private:
    
    JuceSynthFrameworkAudioProcessor& processor;
    
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    ComboBox oscMenu;
    GroupComponent mainGroup;
    BasicKnob osc1FreqKnob; LabeledKnob labeledoscAFreqKnob;
    BasicKnob osc1OctKnob; LabeledKnob labeledoscAOctKnob;
    BasicKnob osc1PulseWidthKnob; LabeledKnob labeledoscAPulseWidthKnob;
    Slider osc1SawShapeToggle;
    Slider osc1SquareShapeToggle;
    Slider osc1SyncToggle;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1SawShapeVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1SquareShapeVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1SyncVal;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1FreqVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1OctVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1PulseWidthVal;
    
    float osc1FreqSetting;
    float osc1OctSetting;
    float osc1SawSetting;
    float osc1SquareSetting;
    float osc1PWSetting;
    
    GroupLookAndFeel groupLookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorA)
};
