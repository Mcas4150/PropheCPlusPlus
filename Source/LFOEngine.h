/*
  ==============================================================================

    LFOEngine.h
    Created: 2 Sep 2020 5:19:14pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "maximilian.h"

//==============================================================================
/*
*/
class LFOEngine  : public juce::Component
{
public:
    LFOEngine(AudioProcessorValueTreeState&);
    ~LFOEngine() override;


    
    using Setting = std::atomic<float>;
    
    inline void setLfoParams(Setting* rate, Setting* sawMode, Setting* triangleMode, Setting* squareMode)
    {
        lfoRateSetting =    *rate;
        lfoSawSetting = *sawMode;
        lfoTriangleSetting = *triangleMode;
        lfoSquareSetting = *squareMode;
    }
    
    inline void processBlock()
    {
        newLfoRateSetting = *m_state.getRawParameterValue("lfoRate");
    }

    
    inline auto getLfoValue()
    {
        double SumSettings = lfoSawSetting + lfoTriangleSetting + lfoSquareSetting;
        double lfoValue = newLfoRateSetting && SumSettings  != 0 ?
        (
            (
               lfoSaw.saw(newLfoRateSetting * lfoSawSetting)
               +
               lfoTriangle.triangle(newLfoRateSetting * lfoTriangleSetting)
               +
               lfoSquare.square(newLfoRateSetting * lfoSquareSetting)
            )
                /
            (
             SumSettings
            )
         ) * .5
        : 1;

        return  lfoValue;
    }
    

private:
    AudioProcessorValueTreeState& m_state;
    double lfoRateSetting;
    // --- the setting for saw LFO
    int lfoSawSetting;
    int lfoTriangleSetting;
    int lfoSquareSetting;
    float newLfoRateSetting;
    
    maxiOsc   lfoSaw, lfoTriangle, lfoSquare;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOEngine)
};
