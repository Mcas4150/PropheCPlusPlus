/*
  ==============================================================================

    Oscillator.h
    Created: 21 Aug 2020 10:25:01pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "maximilian.h"

//==============================================================================
/*
*/
class Oscillator  : public juce::Component
{
public:
    Oscillator();
    ~Oscillator() override;

    
  
    
    
  inline void setFreq(float setting)
  {
      freqSetting = std::pow(2, setting);
  }
  
  inline void setOct(float setting)
  {
      octSetting =  std::pow(2, setting);
  }
  
  inline void setSawMode(float setting)
  {
      sawSetting = setting;
  }
  
  inline void setSquareMode(float setting)
  {
      squareSetting = setting;
  }
    
  inline void setTriangleMode(float setting)
  {
      triangleSetting = setting;
  }
  
  inline void setPW(float setting)
  {
      pWSetting = setting;
  }
    
  inline void setLoFreq(float setting)
  {
      loFreqSetting = setting;
  }
    
  inline double getPWSetting(){
        double pwm = pWSetting;

        if(pwm > 0.99f){
            return 0.99;
        } else if (pwm < 0){
            return 0;
        } else {
            return pwm;
        }
  }
    
  inline double getSaw(double frequency) {
            if(sawSetting)
            {
                return oscSaw.saw(frequency * freqSetting * octSetting);
            }
            return 0;
        }
    
  inline double getTriangle(double frequency) {
            if(triangleSetting)
            {
                return oscTriangle.triangle(frequency * freqSetting * octSetting );
            }
            return 0;
        }
        
        
  inline double getSquare(double frequency, double modOutput) {
            if(squareSetting)
            {

                double squareFrequency = oscSquare.square(frequency * freqSetting * octSetting );
                
                if(pWSetting > 0){
                return oscSquare.pulse(squareFrequency,  modOutput);
                } else {
                    return squareFrequency;
                }

            }
            return 0;
        }
   
    
private:
    
    float freqSetting;
    float octSetting;
    float sawSetting;
    float squareSetting;
    float triangleSetting;
    float pWSetting;
    float loFreqSetting;
    
    maxiOsc oscSaw, oscSquare, oscTriangle;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
