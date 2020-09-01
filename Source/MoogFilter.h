/*
  ==============================================================================

    MoogFilter.h
    Created: 1 Sep 2020 8:52:48am
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once
#include "FilterEngine.h"
#include "VAOnePoleFilter.h"
#include <JuceHeader.h>
//#include <cmath>
#define M_PI           3.14159265358979323846
//==============================================================================
/*
*/
class MoogFilter  : public FilterEngine
{
public:
    MoogFilter();
    ~MoogFilter() override;

    VAOnePoleFilter m_LPF1;
    VAOnePoleFilter m_LPF2;
    VAOnePoleFilter m_LPF3;
    VAOnePoleFilter m_LPF4;

    // -- CFilter Overrides --
    virtual void reset();
    virtual void setQControl(double dQControl);
    //virtual void update();
    //virtual double doFilter(double xn);

    // variables
    double m_dK;        // K, set with Q
    double m_dGamma;    // see block diagram
    double m_dAlpha_0;    // see block diagram

    // Oberheim Xpander variations
    double m_dA;
    double m_dB;
    double m_dC;
    double m_dD;
    double m_dE;

    inline virtual void update()
    {
        // do any modulation first
        FilterEngine::update();

        // prewarp for BZT
        double wd = 2*M_PI*m_dFc;
        double T  = 1/m_dSampleRate;
        double wa = (2/T)*tan(wd*T/2);
        double g  = wa*T/2;

        // G - the feedforward coeff in the VA One Pole
        //     same for LPF, HPF
        double G = g/(1.0 + g);

        // set alphas
        m_LPF1.m_dAlpha = G;
        m_LPF2.m_dAlpha = G;
        m_LPF3.m_dAlpha = G;
        m_LPF4.m_dAlpha = G;

        // set betas
        m_LPF1.m_dBeta = G*G*G/(1.0 + g);
        m_LPF2.m_dBeta = G*G/(1.0 + g);
        m_LPF3.m_dBeta = G/(1.0 + g);
        m_LPF4.m_dBeta = 1.0/(1.0 + g);

        m_dGamma = G*G*G*G; // G^4

        m_dAlpha_0 = 1.0/(1.0 + m_dK*m_dGamma);

        // Oberhein variation
        switch(m_uFilterType)
        {
            case LPF4:
                m_dA = 0.0; m_dB = 0.0; m_dC = 0.0; m_dD = 0.0; m_dE = 1.0;
                break;

            case LPF2:
                m_dA = 0.0; m_dB = 0.0; m_dC = 1.0; m_dD = 0.0; m_dE = 0.0;
                break;

            case BPF4:
                m_dA = 0.0; m_dB = 0.0; m_dC = 4.0; m_dD = -8.0; m_dE = 4.0;
                break;

            case BPF2:
                m_dA = 0.0; m_dB = 2.0; m_dC = -2.0; m_dD = 0.0; m_dE = 0.0;
                break;

            case HPF4:
                m_dA = 1.0; m_dB = -4.0; m_dC = 6.0; m_dD = -4.0; m_dE = 1.0;
                break;

            case HPF2:
                m_dA = 1.0; m_dB = -2.0; m_dC = 1.0; m_dD = 0.0; m_dE = 0.0;
                break;

            default: // LPF4
                m_dA = 0.0; m_dB = 0.0; m_dC = 0.0; m_dD = 0.0; m_dE = 1.0;
                break;
        }
    }

    inline virtual double doFilter(double xn)
    {
        // --- return xn if filter not supported
        if(m_uFilterType == BSF2 || m_uFilterType == LPF1 || m_uFilterType == HPF1)
            return xn;

        double dSigma = m_LPF1.getFeedbackOutput() +
                        m_LPF2.getFeedbackOutput() +
                        m_LPF3.getFeedbackOutput() +
                        m_LPF4.getFeedbackOutput();

        // --- for passband gain compensation
        //     you can connect this to a GUI control
        //     and let user choose instead
//        xn *= 1.0 + m_dAuxControl*m_dK;

        // calculate input to first filter
        double dU = (xn - m_dK*dSigma)*m_dAlpha_0;
//
//        if(m_uNLP == ON)
//            dU = fasttanh(m_dSaturation*dU);
    
        // --- cascade of 4 filters
        double dLP1 = m_LPF1.doFilter(dU);
        double dLP2 = m_LPF2.doFilter(dLP1);
        double dLP3 = m_LPF3.doFilter(dLP2);
        double dLP4 = m_LPF4.doFilter(dLP3);

        // --- Oberheim variations
        return m_dA*dU + m_dB*dLP1 + m_dC*dLP2 + m_dD*dLP3 +  m_dE*dLP4;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoogFilter)
};
