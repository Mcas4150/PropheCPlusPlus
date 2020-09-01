/*
  ==============================================================================

    ModulationMatrix.h
    Created: 24 Aug 2020 12:30:54pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "synthFunctions.h"

//==============================================================================
/*
*/
class ModulationMatrix  : public juce::Component
{
public:
    ModulationMatrix();
    ~ModulationMatrix() override;
    
    using Setting = std::atomic<float>;

protected:

public:
    float modAmtFilterEnvSetting;
    float modAmtOscBSetting ;
    float modAmtLfoSetting;
    float modOscAFreqSetting ;
    float modOscAPWSetting ;
    float modOscBFreqSetting ;
    float modOscBPWSetting ;
    float modFilterSetting;
    
    // sources: where each source (LFO, EG, ETC) writes its output value
    
        void setModMatrix (Setting* modAmtFilterEnv, Setting* modAmtLfo , Setting* modAmtOscB , Setting* modOscAFreqMode , Setting* modOscAPWMode , Setting* modOscBFreqMode , Setting* modOscBPWMode , Setting* modFilterMode)
        {
 
            modAmtFilterEnvSetting = *modAmtFilterEnv;
            modAmtOscBSetting = *modAmtOscB;
            modAmtLfoSetting = *modAmtLfo;
            modOscAFreqSetting = *modOscAFreqMode;
            modOscAPWSetting = *modOscAPWMode;
            modOscBFreqSetting = *modOscBFreqMode;
            modOscBPWSetting = *modOscBPWMode;
            modFilterSetting = *modFilterMode;
            
        };

    
private:
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationMatrix)
    
};

    

