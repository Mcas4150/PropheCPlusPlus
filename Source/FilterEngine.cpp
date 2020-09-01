/*
  ==============================================================================

    FilterEngine.cpp
    Created: 28 Aug 2020 6:52:21pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterEngine.h"

//==============================================================================
FilterEngine::FilterEngine()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    m_dSampleRate = 44100;
    m_dQControl = 1.0; // Q is 1 to 10 on GUI
    m_dFc = FILTER_FC_DEFAULT;
    m_dQ = FILTER_Q_DEFAULT;
    m_dFcControl = FILTER_FC_DEFAULT;
}

FilterEngine::~FilterEngine()
{
}


