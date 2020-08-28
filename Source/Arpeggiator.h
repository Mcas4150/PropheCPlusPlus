/*
  ==============================================================================

    Arpeggiator.h
    Created: 30 May 2019 11:10:59pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Common/LabeledKnob.h"
#include "SliderLookAndFeel.h"
//==============================================================================
/*
*/
class Arpeggiator    : public Component, public Slider::Listener
{
public:
    Arpeggiator(JuceSynthFrameworkAudioProcessor&);
    ~Arpeggiator();

    void paint (Graphics&) override;
    void resized() override;
      void sliderValueChanged (Slider*) override;
    
//    
//    inline void prepareArpeggiator(double sampleRate)
//    {
//        
//        notes.clear();
//        currentNote = 0;
//        lastNoteValue = -1;
//        time = 0;
//        speed = 0.5;
//        rate = static_cast<float>(sampleRate);
//    }
//    
//    
//    inline void setArpeggiator(std::atomic<float>* setting)
//       {
//        
//           
//           
//       }
//    
//    
//
//    auto noteDuration = static_cast<int> (std::ceil (rate * 0.25f * (0.1f + (1.0f - (speed)))));
//
//    for (const auto metadata : midiMessages)
//    {
//        const auto msg = metadata.getMessage();
//        if      (msg.isNoteOn())  notes.add (msg.getNoteNumber());
//        else if (msg.isNoteOff()) notes.removeValue (msg.getNoteNumber());
//    }
//
//    midiMessages.clear();
//
//    if ((time + numSamples) >= noteDuration)
//    {
//        auto offset = jmax (0, jmin ((int) (noteDuration - time), numSamples - 1));
//
//        if (lastNoteValue > 0)
//        {
//            midiMessages.addEvent (MidiMessage::noteOff (1, lastNoteValue), offset);
//            lastNoteValue = -1;
//        }
//
//        if (notes.size() > 0)
//        {
//            currentNote = (currentNote + 1) % notes.size();
//            lastNoteValue = notes[currentNote];
//            midiMessages.addEvent (MidiMessage::noteOn  (1, lastNoteValue, (uint8) 127), offset);
//        }
//
//    }
//
//    time = (time + numSamples) % noteDuration;
//
//    
    

private:
    SharedResourcePointer<BasicLookAndFeel> lookAndFeel;
    SliderToggleLookAndFeel sliderToggleLookAndFeel;
    GroupLookAndFeel groupLookAndFeel;
    
    Slider arpModeToggle;
    
    GroupComponent mainGroup;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> arpModeToggleVal;
 
    
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Arpeggiator)
};
