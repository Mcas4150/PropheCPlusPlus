/*
  ==============================================================================

    MoogFilter.cpp
    Created: 1 Sep 2020 8:52:48am
    Author:  Mike Cassidy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MoogFilter.h"

//==============================================================================
MoogFilter::MoogFilter()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    m_dK = 0.0;
    m_dAlpha_0 = 1.0;

    // --- Oberheim variables
    m_dA = 0.0; m_dB = 0.0; m_dC = 0.0;
    m_dD = 0.0; m_dE = 0.0;
    
    // --- set all as LPF types
    m_LPF1.m_uFilterType = LPF1;
    m_LPF2.m_uFilterType = LPF1;
    m_LPF3.m_uFilterType = LPF1;
    m_LPF4.m_uFilterType = LPF1;

    // --- set default filter type
    m_uFilterType = LPF4;

    // --- flush everything
    reset();
}

MoogFilter::~MoogFilter()
{
}

void MoogFilter::reset()
{
    // flush everything
    m_LPF1.reset();
    m_LPF2.reset();
    m_LPF3.reset();
    m_LPF4.reset();
}

void MoogFilter::setQControl(double dQControl)
{
    // this maps dQControl = 1->10 to K = 0 -> 4
    m_dK = (4.0)*(dQControl - 1.0)/(10.0 - 1.0);
}
