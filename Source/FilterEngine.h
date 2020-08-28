/*
  ==============================================================================

    FilterEngine.h
    Created: 28 Aug 2020 6:52:21pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterEngine  : public juce::Component
{
public:
    FilterEngine();
    ~FilterEngine() override;


    inline void setCutoff(float setting)
     {
         cutoffSetting = setting;
     }
     
     inline void setResonance(float setting)
     {
         resonanceSetting = setting;
     }
     
     inline void setEnvAmt(float setting)
     {
         envAmtSetting = setting;
     }
     
     inline void setKeyAmt(float setting)
     {
         keyAmtSetting = setting;
     }
    
    inline double getFilterOutput(double audioInput, double envelopeOutput, double modmatrixOutput)
    {
//
//        auto filteredEnvelope = cutoffSetting * envelopeOutput;
//        double filterModulation = getModulationMatrixOutput(filteredEnvelope, modFilterSetting );
//        double filterOutput = filter1.lores(getMixerOutput(),  filterModulation , resonanceSetting);
        
    }
    
private:
    
    float cutoffSetting;
    float resonanceSetting;
    float envAmtSetting;
    float keyAmtSetting;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterEngine)
};
