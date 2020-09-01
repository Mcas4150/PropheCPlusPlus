/*
  ==============================================================================

    VAOnePoleFilter.cpp
    Created: 31 Aug 2020 5:10:02pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VAOnePoleFilter.h"
//#include <cmath>

#define M_PI           3.14159265358979323846

//==============================================================================
VAOnePoleFilter::VAOnePoleFilter()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    m_dAlpha = 1.0;
    m_dBeta = 0.0;
    m_dZ1 = 0.0;
    m_dGamma = 1.0;
    m_dDelta = 0.0;
    m_dEpsilon = 0.0;
    m_da0 = 1.0;
    m_dFeedback = 0.0;

    // --- always set the default!
//    m_uFilterType = LPF1;

    // --- flush storage
    reset();
}

VAOnePoleFilter::~VAOnePoleFilter()
{
}


void VAOnePoleFilter::update()
{
    // base class does modulation, changes m_fFc
    FilterEngine::update();

    double wd = 2*M_PI*m_dFc;
    double T  = 1/m_dSampleRate;
    double wa = (2/T)*tan(wd*T/2);
    double g  = wa*T/2;

    m_dAlpha = g/(1.0 + g);
}

// do the filter
double VAOnePoleFilter::doFilter(double xn)
{
    // return xn if filter not supported
//    if(m_uFilterType != LPF1 && m_uFilterType != HPF1)
//        return xn;

    // for diode filter support
    xn = xn*m_dGamma + m_dFeedback + m_dEpsilon*getFeedbackOutput();
    
    // calculate v(n)
    double vn = (m_da0*xn - m_dZ1)*m_dAlpha;

    // form LP output
    double lpf = vn + m_dZ1;

    // update memory
    m_dZ1 = vn + lpf;

    double hpf = xn - lpf;

    if(m_uFilterType == LPF1)
        return lpf;
    else if(m_uFilterType == HPF1)
        return hpf;
    


    return xn; // should never get here
}
