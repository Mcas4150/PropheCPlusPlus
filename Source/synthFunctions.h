/*
  ==============================================================================

    synthFunctions.h
    Created: 21 Aug 2020 10:28:22pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once


double pitchShiftMultiplier(double dPitchShiftSemitones)
    {
        return pow2(dPitchShiftSemitones/12.0);
    }
