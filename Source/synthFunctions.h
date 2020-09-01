/*
  ==============================================================================

    synthFunctions.h
    Created: 21 Aug 2020 10:28:22pm
    Author:  Mike Cassidy

  ==============================================================================
*/

#pragma once


using UINT = uint32;

/* pitchShiftMultiplier()

    returns a multiplier for a given pitch shift in semitones
    to shift octaves,     call pitchShiftMultiplier(octaveValue*12.0);
    to shift semitones,   call pitchShiftMultiplier(semitonesValue);
    to shift cents,       call pitchShiftMultiplier(centsValue/100.0);
*/
inline double pitchShiftMultiplier(double dPitchShiftSemitones)
{
    if(dPitchShiftSemitones == 0)
        return 1.0;

    // 2^(N/12)
//    return fastPow(2.0, dPitchShiftSemitones/12.0);
    return pow(2.0, dPitchShiftSemitones/12.0);
}




// --- Modulation Matrix Stuff --- //
enum sources{
    SOURCE_NONE = 0,

    SOURCE_UI_OSCB_FO,

    SOURCE_LFO1,                       /* Exponential outputs */
    SOURCE_FILTER_EG,
    
    SOURCE_VELOCITY,            /* MIDI  */
    SOURCE_MIDI_VOLUME_CC07,        /* MIDI Volume */
    SOURCE_MIDI_PAN_CC10,            /* MIDI Pan */
    SOURCE_MIDI_EXPRESSION_CC11,    /* MIDI Expression */
    SOURCE_MODWHEEL,
    SOURCE_PITCHBEND,
    SOURCE_SUSTAIN_PEDAL,
    SOURCE_MIDI_NOTE_NUM,
    MAX_SOURCES
};

enum destinations{
    DEST_NONE = 0,

    // --- GUI control layer modulation (-1)
    DEST_UI_OSC1_FO,
    DEST_UI_OSC2_FO,

    DEST_UI_FILTER1_FC,
    DEST_UI_FILTER1_Q,


    // --- LAYER 0 DESTINATIONS
    //     add more L0 destinations in this chunk
    //     see CModulationMatrix::checkDestinationLayer())
    DEST_LFO1_FO, // <- keep this first
    DEST_LFO2_FO,
    DEST_ALL_LFO_FO,
    DEST_LFO1_OUTPUT_AMP,
    DEST_LFO2_OUTPUT_AMP,
    DEST_ALL_LFO_OUTPUT_AMP,
   
    // --- END OF LAYER 0 DESTINATIONS

    // --- LAYER 1 DESTINATIONS
    DEST_HARD_SYNC_RATIO,
    DEST_OSC1_FO,
    DEST_OSC2_FO,
    DEST_OSC1_PULSEWIDTH,
    DEST_OSC2_PULSEWIDTH,

    DEST_OSC1_OUTPUT_AMP,
    DEST_OSC2_OUTPUT_AMP,
    DEST_OSC3_OUTPUT_AMP,
    DEST_ALL_OSC_OUTPUT_AMP,
    DEST_FILTER1_FC,
    DEST_FILTER1_KEYTRACK, // the control value, overriding the GUI
// filter eg
    DEST_DCA_VELOCITY,
    DEST_DCA_EG,
    DEST_DCA_AMP,
    DEST_DCA_PAN,
    // --- END OF LAYER 1 DESTINATIONS

    MAX_DESTINATIONS
};


//enum transform{
//    TRANSFORM_NONE = 0,
//    TRANSFORM_UNIPOLAR_TO_BIPOLAR,
//    TRANSFORM_BIPOLAR_TO_UNIPOLAR,
//    TRANSFORM_MIDI_NORMALIZE,
//    TRANSFORM_INVERT_MIDI_NORMALIZE,
//    TRANSFORM_MIDI_TO_BIPOLAR,
//    TRANSFORM_MIDI_TO_PAN,
//    TRANSFORM_MIDI_SWITCH,
//    TRANSFORM_MIDI_TO_ATTENUATION,
//    TRANSFORM_NOTE_NUMBER_TO_FREQUENCY,
//    MAX_TRANSFORMS /* not needed? */
//};


struct modMatrixRow
{
    // --- index of source
    UINT uSourceIndex;

    // --- index of destination
    UINT uDestinationIndex;

    // --- for GUI -> Control
    double dUIContolValue;

    // --- needs to default to 1.0 in case no GUI control
    double* pModIntensity;    // <- "ucControl" in MMA DLS
    double* pModRange;        // <- "lScale" in MMA DLS

    // --- transform on Source
    UINT uSourceTransform;

    // --- to easily turn on/off a modulation routing
    bool bEnable;
};





inline modMatrixRow** createModMatrixCore()
{
    modMatrixRow** pCore = new modMatrixRow*[MAX_SOURCES*MAX_DESTINATIONS];
    memset(pCore, 0, MAX_SOURCES*MAX_DESTINATIONS*sizeof(modMatrixRow*));
    return pCore;
}

inline modMatrixRow* createModMatrixRow(int uSource, int uDestination, double* pIntensity, double* pRange, int uTransform, bool bEnable = true)
{
    modMatrixRow* pRow = new modMatrixRow;
    pRow->uSourceIndex = uSource;
    pRow->uDestinationIndex = uDestination;
    pRow->pModIntensity = pIntensity; // 0->1
    pRow->pModRange = pRange;
    pRow->uSourceTransform = uTransform; // for AmpMod
    pRow->bEnable = bEnable; // on/off
    pRow->dUIContolValue = 0.0;

    return pRow;
}
//
//struct globalOscillatorParams
//{
//    // --- common
//    double dOscFo;
//    double dFoRatio;
//    double dAmplitude;    // 0->1 from GUI
//    double dPulseWidthControl; // from GUI
//    int nOctave;            // octave tweak
//    int nSemitones;        // semitones tweak
//    int nCents;            // cents tweak
//    int uWaveform;        // to store type
//
//    // --- LFOs
//    int uLFOMode;        // to store MODE
//
//    // --- CSampleOscillators
//    int uLoopMode;
//};
//
//struct globalFilterParams
//{
//    // --- the user's cutoff frequency control position
//    double dFcControl;
//    double dQControl;
//    double dAuxControl;
//    double dSaturation;
//    int uFilterType;
//    int uNLP;
//};
//
//struct globalEGParams
//{
//    double dAttackTime_mSec;    // att: is a time duration
//    double dDecayTime_mSec;    // dcy: is a time to decay 1->0
//    double dReleaseTime_mSec;    // rel: is a time to decay 1->0
//    double dSustainLevel;
//    double dShutdownTime_mSec; // shutdown is a time
//    bool bResetToZero;
//    bool bLegatoMode;
//};
//
//struct globalDCAParams
//{
//    double dAmplitude_dB;        // the user's control setting in dB
//    double dPanControl;
//};
//
//struct globalNanoSynthParams
//{
//    globalOscillatorParams    osc1Params;
//    globalOscillatorParams    osc2Params;
//    globalOscillatorParams    lfo1Params;
//    globalFilterParams        filter1Params;
//    globalEGParams            eg1Params;
//    globalDCAParams            dcaParams;
//};
//
//struct globalVoiceParams
//{
//    // --- common
//    int uVoiceMode;
//    double dHSRatio;
//    double dPortamentoTime_mSec;
//
//    // --- ranges
//    double dOscFoPitchBendModRange;
//    double dFilterModRange;
//    double dAmpModRange;
//    double dOscFoModRange;
//    double dOscHardSyncModRange;
//
//    // --- intensities
//    double dFilterKeyTrackIntensity;
//
//    double dLFO1OscModIntensity;
//    double dLFO1HSModIntensity;
//    double dLFO1Filter1ModIntensity;
//    double dLFO1Filter2ModIntensity;
//    double dLFO1DCAAmpModIntensity;
//    double dLFO1DCAPanModIntensity;
//
//    double dLFO2OscModIntensity;
//    double dLFO2HSModIntensity;
//    double dLFO2Filter1ModIntensity;
//    double dLFO2Filter2ModIntensity;
//    double dLFO2DCAAmpModIntensity;
//    double dLFO2DCAPanModIntensity;
//
//    double dEG1OscModIntensity;
//    double dEG1Filter1ModIntensity;
//    double dEG1Filter2ModIntensity;
//    double dEG1DCAAmpModIntensity;
//
//    double dEG2OscModIntensity;
//    double dEG2Filter1ModIntensity;
//    double dEG2Filter2ModIntensity;
//    double dEG2DCAAmpModIntensity;
//
//    double dEG3OscModIntensity;
//    double dEG3Filter1ModIntensity;
//    double dEG3Filter2ModIntensity;
//    double dEG3DCAAmpModIntensity;
//
//    double dEG4OscModIntensity;
//    double dEG4Filter1ModIntensity;
//    double dEG4Filter2ModIntensity;
//    double dEG4DCAAmpModIntensity;
//
//};
//
//
//struct globalSynthParams
//{
//    globalVoiceParams        voiceParams;
//    globalOscillatorParams    osc1Params;
//    globalOscillatorParams    osc2Params;
//    globalOscillatorParams    osc3Params;
//    globalOscillatorParams    osc4Params;
//    globalOscillatorParams    lfo1Params;
//    globalOscillatorParams    lfo2Params;
//    globalFilterParams        filter1Params;
//    globalFilterParams        filter2Params;
//    globalEGParams            eg1Params;
//    globalEGParams            eg2Params;
//    globalEGParams            eg3Params;
//    globalEGParams            eg4Params;
//    globalDCAParams            dcaParams;
//};
