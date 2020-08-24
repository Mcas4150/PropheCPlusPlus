/*
  ==============================================================================

    ModulationMatrix.h
    Created: 24 Aug 2020 12:30:54pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "synthFunctions.h"

//==============================================================================
/*
*/
class ModulationMatrix  : public juce::Component
{
public:
    ModulationMatrix();
    ~ModulationMatrix() override;

protected:
    // --- the matrix of mod-rows with the worst-case size (every source
    //     modulates every destination
    //     This is a double-pointer because it is allocated dynamically (*)
    //     and points to an array of pointers(**)
    modMatrixRow** m_ppMatrixCore;

    // --- current size depending on number of rows added
    int m_nSize;

public:
    
    // sources: where each source (LFO, EG, ETC) writes its output value
    double m_dSources[MAX_SOURCES];

    // destinations: where the newly calculated mod values are read from
    double m_dDestinations[MAX_DESTINATIONS];
    
    // --- get the matrix core
        modMatrixRow** getModMatrixCore(){return m_ppMatrixCore;}
        
        // --- set the matrix core
        void setModMatrixCore(modMatrixRow** pModMatrix)
        {
            if(m_ppMatrixCore)
            {
                for(int i=0; i<m_nSize; i++)
                {
                    // delete pointer
                    modMatrixRow* pRow = m_ppMatrixCore[i];
                    delete pRow;
                    m_nSize--;
                }
                m_nSize = 0;
                delete [] m_ppMatrixCore;
            }

            m_ppMatrixCore = pModMatrix;
            m_nSize = getMatrixSize();
        }

        // --- get number of non-NULL rows
        int getMatrixSize()
        {
            int nSize = 0;
            if(!m_ppMatrixCore) return nSize;

            for(int i=0; i<MAX_SOURCES*MAX_DESTINATIONS; i++)
            {
                modMatrixRow* pRow = m_ppMatrixCore[i];
                if(pRow)
                    nSize++;
            }
            return nSize;
        }

        // config changes
        inline void clearMatrix()
        {
            if(!m_ppMatrixCore) return;

            for(int i=0; i<(MAX_SOURCES*MAX_DESTINATIONS); i++)
            {
                m_ppMatrixCore[i] = NULL;
            }
        }
        
        inline void clearSources()
        {
            for(int i=0; i<MAX_SOURCES; i++)
            {
                m_dSources[i] = 0.0;
            }
        }

        // called on each pass through the matrix
        inline void clearDestinations()
        {
            for(int i=0; i<MAX_DESTINATIONS; i++)
            {
                m_dDestinations[i] = 0.0;
            }
        }

        inline void addModMatrixRow(modMatrixRow* pRow)
        {
            if(!m_ppMatrixCore)
                createMatrixCore();

            // add if not already existing
            if(!matrixRowExists(pRow->uSourceIndex, pRow->uDestinationIndex))
            {
                m_ppMatrixCore[m_nSize] = pRow;
                m_nSize++;
            }
            else
                delete pRow;
        }

        // check for duplicate row
        inline bool matrixRowExists(int uSourceIndex, int uDestinationIndex)
        {
            if(!m_ppMatrixCore) return false;

            for(int i=0; i<m_nSize; i++)
            {
                modMatrixRow* pRow = m_ppMatrixCore[i];
                
                // find matching source/destination pairs
                if(pRow->uSourceIndex == uSourceIndex && pRow->uDestinationIndex == uDestinationIndex)
                {
                    return true;
                }
            }
            return false;
        }

        inline void createMatrixCore()
        {
            if(m_ppMatrixCore)
                delete [] m_ppMatrixCore;

            // --- dynamic allocation of matrix core
            m_ppMatrixCore = new modMatrixRow*[MAX_SOURCES*MAX_DESTINATIONS];
            memset(m_ppMatrixCore, 0, MAX_SOURCES*MAX_DESTINATIONS*sizeof(modMatrixRow*));
        }

        // thie deletes the pointer too!
        inline void deleteModMatrix()
        {
            if(!m_ppMatrixCore) return;

            for(int i=0; i<m_nSize; i++)
            {
                // delete pointer
                modMatrixRow* pRow = m_ppMatrixCore[i];
                delete pRow;
                m_nSize--;
            }
            m_nSize = 0;
            delete [] m_ppMatrixCore;
            m_ppMatrixCore = NULL;
        }
        
        inline bool enableModMatrixRow(int uSourceIndex, int uDestinationIndex, bool bEnable)
        {
            if(!m_ppMatrixCore) return false;

            for(int i=0; i<m_nSize; i++)
            {
                modMatrixRow* pRow = m_ppMatrixCore[i];
                
                // find matching source/destination pairs
                if(pRow->uSourceIndex == uSourceIndex && pRow->uDestinationIndex == uDestinationIndex)
                {
                    pRow->bEnable = bEnable;
                    return true; // found it
                }
            }
            return false;
        }

        // --- returns true for queried layer
        inline bool checkDestinationLayer(int uLayer, modMatrixRow* pRow)
        {
            bool bLayer0 = false;
            if(pRow->uDestinationIndex >= DEST_LFO1_FO &&
               pRow->uDestinationIndex <= DEST_ALL_EG_SUSTAIN_OVERRIDE)
                // then, we are layer 0; see synthfunctions.h
                bLayer0 = true;

            if(uLayer == 0)
                return bLayer0;

            if(uLayer == 1)
                return !bLayer0;

            return false;
        }

        // go through each row and transfer/accumulate sources into destinations
        // destination += source*intensity*range
        inline void doModulationMatrix(int uModLayer)
        {
            if(!m_ppMatrixCore) return;

            // clear dest registers
            clearDestinations();

            for(int i=0; i<m_nSize; i++)
            {
                // get the row
                modMatrixRow* pRow = m_ppMatrixCore[i];

                // --- this should never happen!
                if(!pRow) continue;

                // --- if disabled, skip row
                if(!pRow->bEnable) continue;

                // --- check the mod layer
                if(!checkDestinationLayer(uModLayer, pRow)) continue;

                // get the source value
                double dSource = m_dSources[pRow->uSourceIndex];

//                switch(pRow->uSourceTransform)
//                {
//                    case TRANSFORM_UNIPOLAR_TO_BIPOLAR:
//                        dSource = unipolarToBipolar(dSource);
//                        break;
//
//                    case TRANSFORM_BIPOLAR_TO_UNIPOLAR:
//                        dSource = bipolarToUnipolar(dSource);
//                        break;
//
//                    case TRANSFORM_MIDI_TO_ATTENUATION:
//                        dSource = mmaMIDItoAtten(dSource);
//                        break;
//
//                    case TRANSFORM_MIDI_TO_PAN:
//                        dSource = midiToPanValue(dSource);
//                        break;
//
//                    case TRANSFORM_MIDI_SWITCH:
//                        dSource = dSource > 63 ? 1.0 : 0.0;
//                        break;
//
//                    case TRANSFORM_MIDI_TO_BIPOLAR:
//                        dSource = midiToBipolar(dSource);
//                        break;
//
//                    case TRANSFORM_NOTE_NUMBER_TO_FREQUENCY:
//                        dSource = midiFreqTable[(int)dSource];
//                        break;
//
//                    case TRANSFORM_MIDI_NORMALIZE:
//                        dSource/= 127.0; // 0->1 NOTE: MMA DLS uses divide-by-128 instead!, 0->0.9999
//                        break;
//
//                    case TRANSFORM_INVERT_MIDI_NORMALIZE:
//                        dSource/= 127.0; // 0->1 NOTE: MMA DLS uses divide-by-128 instead!, 0->0.9999
//                        dSource = 1.0 - dSource; // 1->0 NOTE: MMA DLS uses divide-by-128 instead!, 0.9999->0
//                        break;
//
//                    default:
//                        break;
//                }

                // destination += source*intensity*range
                //
                double dModValue = dSource*(*pRow->pModIntensity)*(*pRow->pModRange);

                // first check DEST_ALL types
                switch(pRow->uDestinationIndex)
                {
                    case DEST_ALL_OSC_FO:
                        m_dDestinations[DEST_OSC1_FO] += dModValue;
                        m_dDestinations[DEST_OSC2_FO] += dModValue;
//                        m_dDestinations[DEST_OSC3_FO] += dModValue;
//                        m_dDestinations[DEST_OSC4_FO] += dModValue;
                        m_dDestinations[DEST_ALL_OSC_FO] += dModValue;
                        break;

                    case DEST_ALL_OSC_PULSEWIDTH:
                        m_dDestinations[DEST_OSC1_PULSEWIDTH] += dModValue;
                        m_dDestinations[DEST_OSC2_PULSEWIDTH] += dModValue;
                        m_dDestinations[DEST_OSC3_PULSEWIDTH] += dModValue;
                        m_dDestinations[DEST_OSC4_PULSEWIDTH] += dModValue;
                        m_dDestinations[DEST_ALL_OSC_PULSEWIDTH] += dModValue;
                        break;
                    
                    case DEST_ALL_OSC_FO_RATIO:
                        m_dDestinations[DEST_OSC1_FO_RATIO] += dModValue;
                        m_dDestinations[DEST_OSC2_FO_RATIO] += dModValue;
                        m_dDestinations[DEST_OSC3_FO_RATIO] += dModValue;
                        m_dDestinations[DEST_OSC4_FO_RATIO] += dModValue;
                        m_dDestinations[DEST_ALL_OSC_FO_RATIO] += dModValue;
                        break;

                    case DEST_ALL_OSC_OUTPUT_AMP:
                        m_dDestinations[DEST_OSC1_OUTPUT_AMP] += dModValue;
                        m_dDestinations[DEST_OSC2_OUTPUT_AMP] += dModValue;
                        m_dDestinations[DEST_OSC3_OUTPUT_AMP] += dModValue;
                        m_dDestinations[DEST_OSC4_OUTPUT_AMP] += dModValue;
                        m_dDestinations[DEST_ALL_OSC_OUTPUT_AMP] += dModValue;
                        break;

                    case DEST_ALL_LFO_FO:
                        m_dDestinations[DEST_LFO1_FO] += dModValue;
//                        m_dDestinations[DEST_LFO2_FO] += dModValue;
//                        m_dDestinations[DEST_ALL_LFO_FO] += dModValue;
                        break;

                    case DEST_ALL_LFO_OUTPUT_AMP:
                        m_dDestinations[DEST_LFO1_OUTPUT_AMP] += dModValue;
                        m_dDestinations[DEST_LFO2_OUTPUT_AMP] += dModValue;
                        m_dDestinations[DEST_ALL_LFO_OUTPUT_AMP] += dModValue;
                        break;

                    case DEST_ALL_FILTER_FC:
                        m_dDestinations[DEST_FILTER1_FC] += dModValue;
                        m_dDestinations[DEST_FILTER2_FC] += dModValue;
                        m_dDestinations[DEST_ALL_FILTER_FC] += dModValue;
                        break;

                    case DEST_ALL_FILTER_KEYTRACK:
                        m_dDestinations[DEST_FILTER1_KEYTRACK] += dModValue;
                        m_dDestinations[DEST_FILTER2_KEYTRACK] += dModValue;
                        m_dDestinations[DEST_ALL_FILTER_KEYTRACK] += dModValue;
                        break;

                    case DEST_ALL_EG_ATTACK_SCALING:
                        m_dDestinations[DEST_EG1_ATTACK_SCALING] += dModValue;
                        m_dDestinations[DEST_EG2_ATTACK_SCALING] += dModValue;
                        m_dDestinations[DEST_EG3_ATTACK_SCALING] += dModValue;
                        m_dDestinations[DEST_EG4_ATTACK_SCALING] += dModValue;
                        m_dDestinations[DEST_ALL_EG_ATTACK_SCALING] += dModValue;
                        break;

                    case DEST_ALL_EG_DECAY_SCALING:
                        m_dDestinations[DEST_EG1_DECAY_SCALING] += dModValue;
                        m_dDestinations[DEST_EG2_DECAY_SCALING] += dModValue;
                        m_dDestinations[DEST_EG3_DECAY_SCALING] += dModValue;
                        m_dDestinations[DEST_EG4_DECAY_SCALING] += dModValue;
                        m_dDestinations[DEST_ALL_EG_DECAY_SCALING] += dModValue;
                        break;

                    case DEST_ALL_EG_SUSTAIN_OVERRIDE:
                        m_dDestinations[DEST_EG1_SUSTAIN_OVERRIDE] += dModValue;
                        m_dDestinations[DEST_EG2_SUSTAIN_OVERRIDE] += dModValue;
                        m_dDestinations[DEST_EG3_SUSTAIN_OVERRIDE] += dModValue;
                        m_dDestinations[DEST_EG4_SUSTAIN_OVERRIDE] += dModValue;
                        m_dDestinations[DEST_ALL_EG_SUSTAIN_OVERRIDE] += dModValue;
                        break;

                    // for all "single" source/dest, this is the modulation
                    default:
                        m_dDestinations[pRow->uDestinationIndex] += dModValue;
                }
            }
        }
private:
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationMatrix)
    
};

    

