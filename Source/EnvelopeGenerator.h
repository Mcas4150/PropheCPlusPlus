/*
  ==============================================================================

    EnvelopeGenerator.h
    Created: 25 Aug 2020 4:25:11pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Common/Constants.h"
//==============================================================================
/*
*/
#define EG_DEFAULT_STATE_TIME 1000 // 1000 mSec


class EnvelopeGenerator  : public juce::Component
{
public:
    EnvelopeGenerator();
    ~EnvelopeGenerator() override;
    
    
    bool m_bResetToZero; // return to zero
    bool m_bLegatoMode;  // S-trigger
    bool m_bOutputEG;     // true if this EG is being used to control the DCA output

protected:
    double m_dSampleRate;
    
    // --- current output
    double m_dEnvelopeOutput;

    //--- Coefficient, offset and TCO values
    //    for each state
    double m_dAttackCoeff;
    double m_dAttackOffset;
    double m_dAttackTCO;

    double m_dDecayCoeff;
    double m_dDecayOffset;
    double m_dDecayTCO;

    double m_dReleaseCoeff;
    double m_dReleaseOffset;
    double m_dReleaseTCO;

    //--- ADSR times from user
    float m_dAttackTime_mSec;    // att: is a time duration
    float m_dDecayTime_mSec;    // dcy: is a time to decay 1->0
    float m_dReleaseTime_mSec;    // rel: is a time to decay 1->0
    
    // --- this is set internally; user normally not allowed to adjust
    float m_dShutdownTime_mSec; // shutdown is a time

    // --- sustain is a level, not a time
    float m_dSustainLevel;

    // --- for modulating attack and decay times
    float m_dAttackTimeScalar;    // for velocity -> attack time mod
    float m_dDecayTimeScalar;    // for note# -> decay time mod

    // --- inc value for shutdown
    double m_dIncShutdown;
    
    
    UINT m_uState;
    enum {off, attack, decay, sustain, release, shutdown};

public:
    
    inline UINT getState() {return m_uState;}
    inline double getEnvOutput(){return m_dEnvelopeOutput;}

    // --- is the EG active
    inline bool isActive()
    {
        if(m_uState != release && m_uState != off )
            return true;
        
        return false;
    }

    // --- can do note off now?
    inline bool canNoteOff()
    {
        if(m_uState != release && m_uState != shutdown && m_uState != off)
            return true;
        
        return false;
    }
    
    // --- reset
    void reset();
    
    
    
    // --- function to set the time constants
//    void setEGMode(UINT u);
    
    // --- calculate time params
    void calculateAttackTime();
    void calculateDecayTime();
    void calculateReleaseTime();

    // --- go to release state; reset counter
    void noteOff();

    // --- go to shutdown state
    void shutDown();

    // --- mutators
    inline void setState(UINT u){m_uState = u;}
    inline void setSampleRate(double d){m_dSampleRate = d;}
    
//    void setOsc2SquareMode(std::atomic<float>* setting)
//    {
//        osc2SquareSetting = *setting;
//    }
    // --- called during updates
    inline void setAttackTime_mSec(std::atomic<float>* setting)
    {
        m_dAttackTime_mSec = *setting;
        calculateAttackTime();
    }
    inline void setDecayTime_mSec(std::atomic<float>* setting)
    {
        m_dDecayTime_mSec = *setting;
        calculateDecayTime();
    }
    inline void setReleaseTime_mSec(std::atomic<float>* setting)
    {
        m_dReleaseTime_mSec = *setting;
        calculateReleaseTime();
    }
    inline void setShutdownTime_mSec(std::atomic<float>* setting)
    {
        m_dShutdownTime_mSec = *setting;
    }

    // --- sustain is a level not a time
    inline void setSustainLevel(std::atomic<float>* setting)
    {
        m_dSustainLevel = *setting;
        
        // --- sustain level affects decay
        calculateDecayTime();
        
        // --- and release, if not in release state
        if(m_uState != release)
            calculateReleaseTime();
    }

    // reset and go to attack state
    inline void startEG()
    {
        // --- ignore
        if(m_uState != off && m_uState != release)
            return;

        // --- reset and go
        reset();
        m_uState = attack;
    }

    // --- go to off state
    inline void stopEG()
    {
        m_uState = off;
    }
    
    
//    inline void update()
//    {
//        // --- Global Parameters
//        if(m_pGlobalEGParams)
//        {
//            if(m_dAttackTime_mSec != m_pGlobalEGParams->dAttackTime_mSec)
//                setAttackTime_mSec(m_pGlobalEGParams->dAttackTime_mSec);
//
//            if(m_dDecayTime_mSec != m_pGlobalEGParams->dDecayTime_mSec)
//                setDecayTime_mSec(m_pGlobalEGParams->dDecayTime_mSec);
//
//            if(m_dReleaseTime_mSec != m_pGlobalEGParams->dReleaseTime_mSec)
//                setReleaseTime_mSec(m_pGlobalEGParams->dReleaseTime_mSec);
//
//            if(m_dSustainLevel != m_pGlobalEGParams->dSustainLevel)
//                setSustainLevel(m_pGlobalEGParams->dSustainLevel);
//
//            m_dShutdownTime_mSec = m_pGlobalEGParams->dShutdownTime_mSec;
//            m_bResetToZero = m_pGlobalEGParams->bResetToZero;
//            m_bLegatoMode =  m_pGlobalEGParams->bLegatoMode;
//        }
//
//        // --- Modulation Matrix
//        //
//        // --- get from matrix Sources
//        if(!m_pModulationMatrix || !m_bOutputEG) return;
//
//        // --- with mod matrix, when value is 0 there is NO modulation, so here
//        if(m_uModSourceEGAttackScaling != DEST_NONE && m_dAttackTimeScalar == 1.0)
//        {
//            double dScale = m_pModulationMatrix->m_dDestinations[m_uModSourceEGAttackScaling];
//            if(m_dAttackTimeScalar != 1.0 - dScale)
//            {
//                m_dAttackTimeScalar = 1.0 - dScale;
//                calculateAttackTime();
//            }
//        }
//
//        // --- for vel->attack and note#->decay scaling modulation
//        //     NOTE: make sure this is only called ONCE during a new note event!
//        if(m_uModSourceEGDecayScaling != DEST_NONE && m_dDecayTimeScalar == 1.0)
//        {
//            double dScale = m_pModulationMatrix->m_dDestinations[m_uModSourceEGDecayScaling];
//            if(m_dDecayTimeScalar != 1.0 - dScale)
//            {
//                m_dDecayTimeScalar = 1.0 - dScale;
//                calculateDecayTime();
//            }
//        }
//        if(m_uModSourceSustainOverride != DEST_NONE)
//        {
//            double dSustain = m_pModulationMatrix->m_dDestinations[m_uModSourceSustainOverride];
//            if(dSustain == 0)
//                setSustainOverride(false);
//            else
//                setSustainOverride(true);
//        }
//    }
    inline double doEnvelope(double* pBiasedOutput = NULL)
    {
        // --- decode the state
        switch(m_uState)
        {
            case off:
            {
                // --- output is OFF
                m_dEnvelopeOutput = 0.0;
                break;
            }
            case attack:
            {
                // --- render value
                m_dEnvelopeOutput = m_dAttackOffset + m_dEnvelopeOutput*m_dAttackCoeff;

                // --- check go to next state
                if(m_dEnvelopeOutput >= 1.0 || m_dAttackTimeScalar*m_dAttackTime_mSec <= 0.0)
                {
                    m_dEnvelopeOutput = 1.0;
                    m_uState = decay;    // go to next state
                    break;
                }

                break;
            }
            case decay:
            {
                // --- render value
                m_dEnvelopeOutput = m_dDecayOffset + m_dEnvelopeOutput*m_dDecayCoeff;
            
                // --- check go to next state
                if(m_dEnvelopeOutput <= m_dSustainLevel || m_dDecayTimeScalar*m_dDecayTime_mSec <= 0.0)
                {
                    m_dEnvelopeOutput = m_dSustainLevel;
                    m_uState = sustain;        // go to next state
                    break;
                }

                break;
            }
            case sustain:
            {
                // --- render value
                m_dEnvelopeOutput = m_dSustainLevel;

                break;
            }
            case release:
            {
//                // --- if sustain pedal is down, override and return
//                if(m_bSustainOverride)
//                {
//                    m_dEnvelopeOutput = m_dSustainLevel;
//                    break;
//                }
//                else
                    // --- render value
                    m_dEnvelopeOutput = m_dReleaseOffset + m_dEnvelopeOutput*m_dReleaseCoeff;
        
                // --- check go to next state
                if(m_dEnvelopeOutput <= 0.0 || m_dReleaseTime_mSec <= 0.0)
                {
                    m_dEnvelopeOutput = 0.0;
                    m_uState = off;        // go to next state
                    break;
                }
                break;
            }
//            case shutdown:
//            {
//                if(m_bResetToZero)
//                {
//                    // --- the shutdown state is just a linear taper since it is so short
//                    m_dEnvelopeOutput += m_dIncShutdown;
//
//                    // --- check go to next state
//                    if(m_dEnvelopeOutput <= 0)
//                    {
//                        m_uState = off;        // go to next state
//                        m_dEnvelopeOutput = 0.0; // reset envelope
//                        break;
//                    }
//                }
//                else
//                {
//                    // --- we are guaranteed to be retriggered
//                    //     just go to off state
//                    m_uState = off;
//                }
//                break;
//            }
        }

        // --- write to modulation outputs
//        if(m_pModulationMatrix)
//        {
//            m_pModulationMatrix->m_dSources[m_uModDestEGOutput] = m_dEnvelopeOutput;
//
//            // add quad phase/stereo output
//            m_pModulationMatrix->m_dSources[m_uModDestBiasedEGOutput] = m_dEnvelopeOutput - m_dSustainLevel;
//        }

        // --- set the biased (pitchEG) output if there is one
        if(pBiasedOutput)
            *pBiasedOutput = m_dEnvelopeOutput - m_dSustainLevel;

        // --- set the normal
        return m_dEnvelopeOutput;
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeGenerator)
};
