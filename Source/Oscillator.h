/*
  ==============================================================================

    Oscillator.h
    Created: 21 Aug 2020 10:25:01pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Oscillator  : public juce::Component
{
public:
    Oscillator();
    ~Oscillator() override;

  
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
    
    float osc1FreqSetting;
    float osc1OctSetting;
    float  osc1SawSetting;
    float osc1SquareSetting;
    float osc1PWSetting;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
