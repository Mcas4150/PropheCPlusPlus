/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JuceSynthFrameworkAudioProcessor::JuceSynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  ),valTreeState(*this, &mUndoManager, "PARAMETERS", createParameters())
{

#endif

    
    mySynth.clearVoices();
    
    
//  monophonic
    for (int i = 0; i < 1 ; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

JuceSynthFrameworkAudioProcessor::~JuceSynthFrameworkAudioProcessor()
{
}

//==============================================================================

AudioProcessorValueTreeState::ParameterLayout JuceSynthFrameworkAudioProcessor::createParameters()
{
    AudioProcessorValueTreeState::ParameterLayout params;
    
    using Range = NormalisableRange<float>;

    
    
/// TODO:: Normalize Ranges
    
    ////           OSCILLATOR A

    params.add ( std::make_unique<AudioParameterFloat>("osc1Freq", "Osc1Freq", Range { -2.0f, 2.0f, 0.1f }, 0.0f ));
    params.add ( std::make_unique<AudioParameterFloat>("osc1Oct", "Osc1Oct", Range {0.0f, 3.0f, 1.0f}, 0.0f)) ;
    params.add ( std::make_unique<AudioParameterInt>("osc1SawMode", "Osc1SawMode", 0, 1, 1));
    params.add ( std::make_unique<AudioParameterInt>("osc1SquareMode", "Osc1SquareMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterFloat>("osc1PW", "Osc1PW", Range {0.0f, 0.99f, 0.01f}, 0.5f));

    ////           OSCILLATOR B
    params.add ( std::make_unique<AudioParameterFloat>("osc2Freq", "Osc2Freq", Range {-2.0f, 2.0f, 0.1f }, 0.0f));
    params.add ( std::make_unique<AudioParameterFloat>("osc2Oct", "Osc2Oct", Range {0.0f, 3.0f, 1.0f}, 0.0f));
    params.add (  std::make_unique<AudioParameterFloat>("osc2SawMode", "Osc2SawMode", NormalisableRange<float>(0, 1), 1));
    params.add (  std::make_unique<AudioParameterFloat>("osc2TriangleMode", "Osc2TriangleMode", NormalisableRange<float>(0, 1), 0));
    params.add (  std::make_unique<AudioParameterFloat>("osc2SquareMode", "Osc2SquareMode", NormalisableRange<float>(0, 1), 0));
    params.add ( std::make_unique<AudioParameterFloat>("osc2PW", "Osc2PW", Range {0.0f, 0.99f, 0.01f}, 0.5f));
    params.add ( std::make_unique<AudioParameterInt>("osc2LoFreqMode", "Osc2LoFreqMode", 0, 1, 0));
    
    ////           MIXER
    params.add (std::make_unique<AudioParameterFloat>("osc1Level", "Osc1Level", Range { 0.0f, 1.0f, 0.01} , 0.5f));
    params.add ( std::make_unique<AudioParameterFloat>("osc2Level", "Osc2Level", Range { 0.0f, 1.0f, 0.01} , 0.5f));
    params.add ( std::make_unique<AudioParameterFloat>("noiseLevel", "NoiseLevel", Range { 0.0f, 1.0f, 0.01 } , 0.0f));

    ////          FILTER
    params.add ( std::make_unique<AudioParameterFloat>("filterCutoff", "FilterCutoff", Range {8.0f, 8500.0f, 1.0f}, 5000.0f));
    params.add ( std::make_unique<AudioParameterFloat>("filterRes", "FilterRes", Range {1.0f, 10.0f, 0.1f}, 1.0f));
    params.add ( std::make_unique<AudioParameterFloat>("envAmt", "EnvAmt", NormalisableRange<float>(0.0f, 1.0f), 1.0f));
    params.add ( std::make_unique<AudioParameterFloat>("keyAmt", "keyAmt", NormalisableRange<float>(0.0f, 1.0f), 0.0f));
    params.add ( std::make_unique<AudioParameterFloat>("filterAttack", "FilterAttack", Range { 1.0f, 7400.0f, 1.0f} , 0.1f));
    params.add ( std::make_unique<AudioParameterFloat>("filterDecay", "FilterDecay", Range { 1.0f, 11000.0f, 1.0f } , 1.0f));
    params.add ( std::make_unique<AudioParameterFloat>("filterSustain", "FilterSustain", Range { 0.0f, 1.0f, 0.01f} , 0.8f));
    params.add ( std::make_unique<AudioParameterFloat>("filterRelease", "FilterRelease", Range { 1.0f, 11000.0f, 1.0f }, 0.1f));

    ////           PITCH
    params.add ( std::make_unique<AudioParameterFloat>("pitchBend", "PitchBend", NormalisableRange<float>(-1.0f, 1.0f), 0.0f));

    ////           GLIDE
    params.add ( std::make_unique<AudioParameterFloat>("glideRate", "GlideRate", Range { 0.0f, 0.99f, 0.01 } , 0.0f));
    params.add ( std::make_unique<AudioParameterFloat>("glideMode", "GlideMode", NormalisableRange<float>(0.0f, 1.0f), 0.0f));

    ////           LFO
    params.add ( std::make_unique<AudioParameterFloat>("lfoRate", "LfoRate", Range {0.1f, 30.0f, 0.01f}, 0.1f));
    params.add ( std::make_unique<AudioParameterInt>("lfoSawMode", "lfoSawMode", 0, 1, 1));
    params.add ( std::make_unique<AudioParameterInt>("lfoTriangleMode", "lfoTriangleMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterInt>("lfoSquareMode", "lfoSquareMode", 0, 1, 0));

    ////        MODULATION
    params.add ( std::make_unique<AudioParameterFloat>("modAmtFilterEnv", "ModAmtFilterEnv", Range {0.0f, 1.00f, 0.01f}, 0.0f));
    params.add ( std::make_unique<AudioParameterFloat>("modAmtOscB", "ModAmtOscB", Range{0.0f, 1.00f, 0.01f}, 0.0f));
    params.add ( std::make_unique<AudioParameterFloat>("modAmtLfo", "ModAmtLfo", Range{0.0f, 1.00f, 0.01f}, 0.0f));
    params.add ( std::make_unique<AudioParameterInt>("modOscAFreqMode", "modOscAFreqMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterInt>("modOscAPWMode", "modOscAPWMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterInt>("modOscBFreqMode", "modOscBFreqMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterInt>("modOscBPWMode", "modOscBPWMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterInt>("modFilterMode", "modFilterMode", 0, 1, 0));

    ////          AMPLIFIER

    params.add ( std::make_unique<AudioParameterFloat>("attack", "Attack", Range { 1.0f, 7400.0f, 1.0f} , 0.1f));
    params.add ( std::make_unique<AudioParameterFloat>("decay", "Decay", Range { 1.0f, 11000.0f, 1.0f } , 1.0f));
    params.add ( std::make_unique<AudioParameterFloat>("sustain", "Sustain", Range { 0.0f, 1.0f, 0.01f} , 0.8f));
    params.add ( std::make_unique<AudioParameterFloat>("release", "Release", Range { 1.0f, 11000.0f, 1.0f }, 0.1f));

    ////           MASTER
    params.add ( std::make_unique<AudioParameterFloat>("mastergain", "MasterGain", Range {0.0f, 1.0f, 0.01 }, 1.0f));
    params.add ( std::make_unique<AudioParameterFloat>("masterTune", "MasterTune", Range {-1.0f, 1.0f, 0.01 }, 0.0f));
    

    return params;
}

//==============================================================================
const String JuceSynthFrameworkAudioProcessor::getName() const
{
    return "Pro-One";
}

bool JuceSynthFrameworkAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool JuceSynthFrameworkAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool JuceSynthFrameworkAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}


int JuceSynthFrameworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int JuceSynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceSynthFrameworkAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceSynthFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceSynthFrameworkAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceSynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    m_EG1.setSampleRate(lastSampleRate);
    m_EG1.m_bOutputEG = true;


}

void JuceSynthFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceSynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif



void JuceSynthFrameworkAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;


    //get the voice and get the params needed to make the voice
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        //if myVoice sucessfully casts as a SynthVoice*, get the voice and set the params
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
  
//            OSCILLATOR A
            
            myVoice->setOscAParams(getParamValue("osc1Freq"),
                                   getParamValue("osc1Oct"),
                                   getParamValue("osc1SawMode"),
                                   getParamValue("osc1SquareMode"),
                                   getParamValue("osc1PW"));
            
//            OSCILLATOR B
            myVoice->setOscBParams(getParamValue("osc2Freq"),
                                   getParamValue("osc2Oct"),
                                   getParamValue("osc2SawMode"),
                                   getParamValue("osc2SquareMode"),
                                   getParamValue("osc2TriangleMode"),
                                   getParamValue("osc2PW"),
                                   getParamValue("osc2LoFreqMode"));
                                   
//            MIXER
            
            myVoice->setMixerParams(getParamValue("osc1Level"),
                                    getParamValue("osc2Level"),
                                    getParamValue("noiseLevel"));
            
//            Filter
         
            myVoice->setFilterParams(getParamValue("filterCutoff"),
                                        getParamValue("filterRes"),
                                        getParamValue("envAmt"),
                                        getParamValue("keyAmt"),
                                        getParamValue("filterAttack"),
                                        getParamValue("filterDecay"),
                                        getParamValue("filterSustain"),
                                        getParamValue("filterRelease"));
            //PITCH
       
            myVoice->setPitchBend(getParamValue("pitchBend"));
            
//            GLIDE
            
            myVoice->setGlideParams(getParamValue("glideRate"),
                                    getParamValue("glideMode"));
            
//          LFO
            myVoice->setLfoParams(getParamValue("lfoRate"),
                                  getParamValue("lfoSawMode"),
                                  getParamValue("lfoTriangleMode"),
                                  getParamValue("lfoSquareMode"));
                                  

//
//            MODULATION
            myVoice->setModMatrix(getParamValue("modAmtFilterEnv"),
                                  getParamValue("modAmtLfo"),
                                  getParamValue("modAmtOscB"),
                                  getParamValue("modOscAFreqMode"),
                                  getParamValue("modOscAPWMode"),
                                  getParamValue("modOscBFreqMode"),
                                  getParamValue("modOscBPWMode"),
                                  getParamValue("modFilterMode"));

//           AMPLIFIER
            
            myVoice->setAmpEnvelope(getParamValue("attack"),
                                       getParamValue("decay"),
                                       getParamValue("sustain"),
                                       getParamValue("release"));
//            m_EG1.setAttackTime_mSec(getParamValue("attack"));
//            m_EG1.setDecayTime_mSec(getParamValue("decay"));
//            m_EG1.setSustainLevel(getParamValue("sustain"));
//            m_EG1.setReleaseTime_mSec(getParamValue("release"));
//            MASTER
            myVoice->setMasterTune(getParamValue("masterTune"));
            myVoice->setMasterGain(getParamValue("mastergain"));
            
        }
    }
    buffer.clear();
    
    keyboardState.processNextMidiBuffer (midiMessages, 0, buffer.getNumSamples(), true);

    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    scopeDataCollector.process (buffer.getReadPointer (0), (size_t) buffer.getNumSamples());
}

//==============================================================================
bool JuceSynthFrameworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceSynthFrameworkAudioProcessor::createEditor()
{
    return new JuceSynthFrameworkAudioProcessorEditor (*this);
//      return new JuceSynthFrameworkAudioProcessorEditor (*this, valTreeState);
}

//==============================================================================
void JuceSynthFrameworkAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr<XmlElement> xml(valTreeState.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void JuceSynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
     std::unique_ptr<XmlElement> params(getXmlFromBinary(data, sizeInBytes));
    if(params != nullptr) {
        if(params ->hasTagName(valTreeState.state.getType())) {
            valTreeState.state = ValueTree::fromXml(*params);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceSynthFrameworkAudioProcessor();
}

