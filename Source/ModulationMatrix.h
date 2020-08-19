/*
  ==============================================================================

    ModulationMatrix.h
    Created: 19 Aug 2020 2:53:19pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

class ModulationMatrix : public ModulationMatrix
{
    
public:
    ModulationMatrix(void);
    ~ModulationMatrix(void);
private:
    modMatrixRow** m_ppMatrixCore;
    int m_nSize;
    
    
public:
    double m_dSources[MAX_SOURCES];
    double m_dDestinations[MAX_DESTINATIONS]
    
}
