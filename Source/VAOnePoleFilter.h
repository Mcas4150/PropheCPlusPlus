/*
  ==============================================================================

    VAOnePoleFilter.h
    Created: 31 Aug 2020 5:10:01pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FilterEngine.h"

//==============================================================================
/*
*/
class VAOnePoleFilter  : public FilterEngine
{
public:
    VAOnePoleFilter();
    ~VAOnePoleFilter() override;

        // Trapezoidal Integrator Components
    double m_dAlpha;            // Feed Forward coeff

    // -- ADDED for Korg35 and Moog Ladder Filter ---- //
    double m_dBeta;

    // -- ADDED for Diode Ladder Filter  ---- //
    double m_dGamma;        // Pre-Gain
    double m_dDelta;        // FB_IN Coeff
    double m_dEpsilon;        // FB_OUT scalar
    double m_da0;            // input gain

    // note: this is NOT being used as a z-1 storage register!
    double m_dFeedback;        // our own feedback coeff from S

    // provide access to set feedback input
    void setFeedback(double fb){m_dFeedback = fb;}

    // provide access to our feedback output
    // m_dFeedback & m_dDelta = 0 for non-Diode filters
    double getFeedbackOutput(){return m_dBeta*(m_dZ1 + m_dFeedback*m_dDelta);}

    // original function
    // double getFeedbackOutput(){return m_dZ1*m_dBeta;}
    // ----------------------------------------------- //

    // -- CFilter Overrides ---
    virtual void reset(){m_dZ1 = 0; m_dFeedback = 0;}

    // recalc the coeff
    virtual void update() override;
    
    // do the filter
    virtual double doFilter(double xn) override;

protected:
    double m_dZ1;        // our z-1 storage location
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VAOnePoleFilter)
};
