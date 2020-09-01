/*
  ==============================================================================

    FilterEngine.h
    Created: 28 Aug 2020 6:52:21pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "synthFunctions.h"
#include "ModulationMatrix.h"

//==============================================================================
/*
*/

#define FILTER_FC_MOD_RANGE 46.881879936465680
#define FILTER_FC_MIN 80        // 80Hz
#define FILTER_FC_MAX 18000        // 18kHz
#define FILTER_FC_DEFAULT 10000    // 10kHz
#define FILTER_Q_DEFAULT 0.707    // Butterworth

class FilterEngine  : public juce::Component
{
public:
    FilterEngine();
    ~FilterEngine() override;

    ModulationMatrix* m_pModulationMatrix;
    // --- ATTRIBUTES
    // --- PUBLIC: these variables may be get/set
    //             you may make get/set functions for them
    //             if you like, but will add function call layer

    // --- the user's cutoff frequency control position
    double m_dFcControl;
    
    double m_dQControl;
    // --- NOTE: these are shared; even though some filters won't use some of them
    //           need to maintain the indexing
    enum{LPF1,HPF1,LPF2,HPF2,BPF2,BSF2,LPF4,HPF4,BPF4};

    // --- our selected filter type
    int m_uFilterType;
    
    uint32 m_uModSourceFc;
    uint32 m_uSourceFcControl;
    
    
    inline void setCutoff(float setting)
     {
         m_dFcControl = setting;
     }
     
     inline void setResonance(float setting)
     {
         m_dQControl = setting;
     }
     
     inline void setEnvAmt(float setting)
     {
         envAmtSetting = setting;
     }
     
     inline void setKeyAmt(float setting)
     {
         keyAmtSetting = setting;
     }
    

        
    inline void setFcMod(double d){m_dFcMod = d;}

    // --- VIRTUAL FUNCTIONS ----------------------------------------- //
    //
    // --- PURE ABSTRACT: derived class MUST implement
    virtual double doFilter(double xn) = 0;

    // --- ABSTRACT: derived class overrides if needed
    //
    inline virtual void setSampleRate(double d)
    {
        m_dSampleRate = d;
    }

    // --- flush buffers, reset filter
    virtual void reset();

    // --- decode the Q value; this can change from filter to filter
    virtual void setQControl(double dQControl);
    
    

    
    // --- recalculate the Fc (called after modulations)
    inline virtual void update()
    {
        // --- update Q (filter-dependent)
        setQControl(m_dQControl);
        
        //    if(m_pModulationMatrix)
        //        {
        //            m_dFcMod = m_pModulationMatrix->m_dDestinations[m_uModSourceFc];
        //            if(m_pModulationMatrix->m_dDestinations[m_uSourceFcControl] > 0)
        //                m_dFcControl = m_pModulationMatrix->m_dDestinations[m_uSourceFcControl];
        //        }
        //    
        
        
        m_dFc = m_dFcControl*pitchShiftMultiplier(m_dFcMod);
        // --- do the modulation freq shift
//        m_dFc = m_dFcControl*pitchShiftMultiplier(m_dFcMod);

        // --- bound the final frequency
        if(m_dFc > FILTER_FC_MAX)
            m_dFc = FILTER_FC_MAX;
        if(m_dFc < FILTER_FC_MIN)
            m_dFc = FILTER_FC_MIN;
    }

protected:
    // --- PROTECTED: generally these are either basic calc variables
    //                and modulation stuff
    //
    double m_dSampleRate;    // fs

    // --- the actual cutoff used in the calculation
    double m_dFc;
    
    // --- the current value of Q (internal)
    double m_dQ;

    // --- our cutoff frequency modulation input
    double m_dFcMod;

    // --- add more mods here

    
private:
    
    float cutoffSetting;
    float resonanceSetting;
    float envAmtSetting;
    float keyAmtSetting;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterEngine)
};
