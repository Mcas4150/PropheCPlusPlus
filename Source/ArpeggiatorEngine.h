/*
  ==============================================================================

    ArpeggiatorEngine.h
    Created: 28 Aug 2020 2:35:32pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ArpeggiatorEngine  : public juce::Component
{
public:
    ArpeggiatorEngine();
    ~ArpeggiatorEngine() override;
    
    inline void prepareArpeggiator(double sampleRate)
    {
        
        notes.clear();
        currentNote = 0;
        lastNoteValue = -1;
        time = 0;
        speed = 0.5;
        rate = static_cast<float>(sampleRate);
    }
    
    
    inline void processArpeggiator(MidiBuffer& midiMessages, int numSamples)
    {
        auto noteDuration = static_cast<int> (std::ceil (rate * 0.25f * (0.1f + (1.0f - (speed)))));

          for (const auto metadata : midiMessages)
          {
              const auto msg = metadata.getMessage();
              if      (msg.isNoteOn())  notes.add (msg.getNoteNumber());
              else if (msg.isNoteOff()) notes.removeValue (msg.getNoteNumber());
          }

          midiMessages.clear();

          if ((time + numSamples) >= noteDuration)
          {
              auto offset = jmax (0, jmin ((int) (noteDuration - time), numSamples - 1));

              if (lastNoteValue > 0)
              {
                  midiMessages.addEvent (MidiMessage::noteOff (1, lastNoteValue), offset);
                  lastNoteValue = -1;
              }

              if (notes.size() > 0)
              {
                  currentNote = (currentNote + 1) % notes.size();
                  lastNoteValue = notes[currentNote];
                  midiMessages.addEvent (MidiMessage::noteOn  (1, lastNoteValue, (uint8) 127), offset);
              }

          }

          time = (time + numSamples) % noteDuration;

           
           
    }
   
private:
    
    int speed;
       int currentNote, lastNoteValue;
       int time;
       float rate;
       SortedSet<int> notes;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpeggiatorEngine)
};
