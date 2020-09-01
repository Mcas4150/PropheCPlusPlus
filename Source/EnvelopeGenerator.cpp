/*
  ==============================================================================

    EnvelopeGenerator.cpp
    Created: 25 Aug 2020 4:25:11pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopeGenerator.h"

//==============================================================================
// code credited to Will Pirkle, "Designing Software Plugins in C++", 2015

//

EnvelopeGenerator::EnvelopeGenerator()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    m_dSampleRate = 44100;

    m_dAttackTime_mSec = EG_DEFAULT_STATE_TIME;
    m_dDecayTime_mSec = EG_DEFAULT_STATE_TIME;
    m_dReleaseTime_mSec = EG_DEFAULT_STATE_TIME;
    
    m_dAttackTCO = exp(-0.5);  // fast attack
    //    m_dAttackTCO = exp(-5.0);
    m_dDecayTCO = exp(-5.0);
    m_dReleaseTCO = m_dDecayTCO;

    m_dAttackTimeScalar = 1.0;
    m_dDecayTimeScalar = 1.0;
    
    m_dSustainLevel = 1.0;
    m_dEnvelopeOutput = 0.0;

    m_dIncShutdown = 0.0;
    
    // --- user normally not allowed to set the time, this initilizes it
    m_dShutdownTime_mSec = 10.0; // mSec

    // --- states and flags
    m_uState = off;

    m_bOutputEG = false;
//    m_uEGMode = analog;
//    setEGMode(m_uEGMode);
    m_bResetToZero = false;
    m_bLegatoMode = false;

    // --- default modulation matrix inits
//    m_pModulationMatrix = NULL;
//
//    // --- everything is disconnected unless you use mod matrix
//    m_uModDestEGOutput = SOURCE_NONE;
//    m_uModDestBiasedEGOutput = SOURCE_NONE;
//    m_uModSourceEGAttackScaling = DEST_NONE;
//    m_uModSourceEGDecayScaling = DEST_NONE;
//    m_uModSourceSustainOverride = DEST_NONE;

    // --- default is NO Global Params
//    m_pGlobalEGParams = NULL;
}

EnvelopeGenerator::~EnvelopeGenerator()
{
}

void EnvelopeGenerator::reset()
{
    m_dAttackTimeScalar = 1.0;
    m_dDecayTimeScalar = 1.0;

    // --- state
    m_uState = off;
    
    // --- Note: sustain pedal may still be down
    //           so it is a sticky variable
//    m_bReleasePending = false;
        
    // --- reset
//    setEGMode(m_uEGMode);

    // --- may be modified in noteOff()
    calculateReleaseTime();
    
    // --- if reset to zero, clear
    //     else let it stay frozen
    if(m_bResetToZero)
    {
        m_dEnvelopeOutput = 0.0;
    }
    
}


void EnvelopeGenerator::calculateAttackTime()
{
    // --- samples for the exponential rate
    double dSamples = m_dSampleRate*((m_dAttackTimeScalar*m_dAttackTime_mSec)/1000.0);

    // --- coeff and base for iterative exponential calculation
    m_dAttackCoeff = exp(-log((1.0 + m_dAttackTCO)/m_dAttackTCO)/dSamples);
    m_dAttackOffset = (1.0 + m_dAttackTCO)*(1.0 - m_dAttackCoeff);
}

// --- changes to the decay rate OR the sustain level require
//     an update in analog mode
void EnvelopeGenerator::calculateDecayTime()
{
    // --- samples for the exponential rate
    double dSamples = m_dSampleRate*((m_dDecayTimeScalar*m_dDecayTime_mSec)/1000.0);
    
    // --- coeff and base for iterative exponential calculation
    m_dDecayCoeff = exp(-log((1.0 + m_dDecayTCO)/m_dDecayTCO)/dSamples);
    m_dDecayOffset = (m_dSustainLevel - m_dDecayTCO)*(1.0 - m_dDecayCoeff);
}

void EnvelopeGenerator::calculateReleaseTime()
{
    // --- samples for the exponential rate
    double dSamples = m_dSampleRate*(m_dReleaseTime_mSec/1000.0);

    // --- coeff and base for iterative exponential calculation
    m_dReleaseCoeff = exp(-log((1.0 + m_dReleaseTCO)/m_dReleaseTCO)/dSamples);
    m_dReleaseOffset = -m_dReleaseTCO*(1.0 - m_dReleaseCoeff);
}

// --- go to release state; reset
void EnvelopeGenerator::noteOff()
{
//    if(m_bSustainOverride)
//    {
//        // --- set m_bReleasePending flag
//        m_bReleasePending = true;
//        return;
//    }

    // --- go directly to release state
    if(m_dEnvelopeOutput > 0)
        m_uState = release;
    else // sustain was already at zero
        m_uState = off;
}

// --- goto shutdown state
void EnvelopeGenerator::shutDown()
{
    // --- legato mode - ignore
    if(m_bLegatoMode)
        return;
    
    // --- calculate the linear inc values based on current outputs
    m_dIncShutdown = -(1000.0*m_dEnvelopeOutput)/m_dShutdownTime_mSec/m_dSampleRate;

    // --- set state and reset counter
    m_uState = shutdown;

//    // --- for sustain pedal
//    m_bSustainOverride = false;
//    m_bReleasePending = false;
}
