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
    
    for (int i = 0; i < 5; i++)
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
    params.add ( std::make_unique<AudioParameterFloat>("osc1Oct", "Osc1Oct", Range {0.0f, 3.0f, 0.01f}, 0.0f)) ;
    params.add ( std::make_unique<AudioParameterInt>("osc1SawMode", "Osc1SawMode", 0, 1, 1));
    params.add ( std::make_unique<AudioParameterInt>("osc1SquareMode", "Osc1SquareMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterFloat>("osc1PW", "Osc1PW", Range {0.0f, 0.99f, 0.01f}, 0.5f));

    ////           OSCILLATOR B
    params.add ( std::make_unique<AudioParameterFloat>("osc2Freq", "Osc2Freq", Range { -2.0f, 2.0f, 0.1f } , 0.0f));
    params.add ( std::make_unique<AudioParameterFloat>("osc2Oct", "Osc2Oct", NormalisableRange<float>(0.0f, 3.0f), 0.0f));
    params.add (  std::make_unique<AudioParameterFloat>("osc2SawMode", "Osc2SawMode", NormalisableRange<float>(0, 1), 1));
    params.add (  std::make_unique<AudioParameterFloat>("osc2SquareMode", "Osc2SquareMode", NormalisableRange<float>(0, 1), 0));

    ////           MIXER
    params.add (std::make_unique<AudioParameterFloat>("osc1Level", "Osc1Level", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
    params.add ( std::make_unique<AudioParameterFloat>("osc2Level", "Osc2Level", NormalisableRange<float>(0.0f, 1.0f), 0.5f));
    params.add ( std::make_unique<AudioParameterFloat>("noiseLevel", "NoiseLevel", NormalisableRange<float>(0.0f, 1.0f), 0.0f));

    ////          FILTER
    params.add ( std::make_unique<AudioParameterFloat>("filterCutoff", "FilterCutoff", NormalisableRange<float>(8.3f, 8500.0f), 5000.0f));
    params.add ( std::make_unique<AudioParameterFloat>("filterRes", "FilterRes", NormalisableRange<float>(1.0f, 10.0f), 1.0f));
    params.add ( std::make_unique<AudioParameterFloat>("envAmt", "EnvAmt", NormalisableRange<float>(0.0f, 1.0f), 1.0f));
    params.add ( std::make_unique<AudioParameterFloat>("keyAmt", "keyAmt", NormalisableRange<float>(0.0f, 1.0f), 0.0f));
    params.add ( std::make_unique<AudioParameterFloat>("filterAttack", "FilterAttack", NormalisableRange<float>(1.5f, 7400.0f), 0.1f));
    params.add ( std::make_unique<AudioParameterFloat>("filterDecay", "FilterDecay", NormalisableRange<float>(0.5f, 11000.0f), 1.0f));
    params.add ( std::make_unique<AudioParameterFloat>("filterSustain", "FilterSustain", NormalisableRange<float>(0.0f, 1.0f), 0.8f));
    params.add ( std::make_unique<AudioParameterFloat>("filterRelease", "FilterRelease", NormalisableRange<float>(0.5f, 11000.0f), 0.1f));

    ////           PITCH
    params.add ( std::make_unique<AudioParameterFloat>("pitchBend", "PitchBend", NormalisableRange<float>(-1.0f, 1.0f), 0.0f));

    ////           GLIDE
    params.add ( std::make_unique<AudioParameterFloat>("glideRate", "GlideRate", NormalisableRange<float>(0.0f, 0.99f), 0.0f));
    params.add ( std::make_unique<AudioParameterFloat>("glideMode", "GlideMode", NormalisableRange<float>(0.0f, 1.0f), 0.0f));

    ////           LFO
    params.add ( std::make_unique<AudioParameterFloat>("lfoRate", "LfoRate", Range {0.0f, 30.0f, 0.01f}, 0.0f));
    params.add ( std::make_unique<AudioParameterInt>("lfoSawMode", "lfoSawMode", 0, 1, 1));
    params.add ( std::make_unique<AudioParameterInt>("lfoTriangleMode", "lfoTriangleMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterInt>("lfoSquareMode", "lfoSquareMode", 0, 1, 0));

    ////        MODULATION
    params.add ( std::make_unique<AudioParameterFloat>("modAmtFilterEnv", "ModAmtFilterEnv", NormalisableRange<float>(0.0f, 1.00), 0.0f));
    params.add ( std::make_unique<AudioParameterFloat>("modAmtLfo", "ModAmtLfo", NormalisableRange<float>(0.0f, 1.00f), 0.0f));
    params.add ( std::make_unique<AudioParameterInt>("modOscAFreqMode", "modOscAFreqMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterInt>("modOscAPWMode", "modOscAPWMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterInt>("modOscBFreqMode", "modOscBFreqMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterInt>("modOscBPWMode", "modOscBPWMode", 0, 1, 0));
    params.add ( std::make_unique<AudioParameterInt>("modFilterMode", "modFilterMode", 0, 1, 0));

    ////          AMPLIFIER

    params.add ( std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(1.5f, 7400.0f), 0.1f));
    params.add ( std::make_unique<AudioParameterFloat>("decay", "Decay", NormalisableRange<float>(0.5f, 11000.0f), 1.0f));
    params.add ( std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.0f, 1.0f), 0.8f));
    params.add ( std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.5f, 11000.0f), 0.1f));

    ////           MASTER
    params.add ( std::make_unique<AudioParameterFloat>("mastergain", "MasterGain", NormalisableRange<float>(0.0f, 1.0f), 0.3f));
    params.add ( std::make_unique<AudioParameterFloat>("masterTune", "MasterTune", NormalisableRange<float>(-1.0f, 1.0f), 0.0f));
    

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
    //
    //    dsp::ProcessSpec spec;
    //    spec.sampleRate = lastSampleRate;
    //    spec.maximumBlockSize = samplesPerBlock;
    //    spec.numChannels = getTotalNumOutputChannels();
    
    
    
    
    
    

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
    //const int totalNumInputChannels  = getTotalNumInputChannels();
    //const int totalNumOutputChannels = getTotalNumOutputChannels();

    //get the voice and get the params needed to make the voice
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        //if myVoice sucessfully casts as a SynthVoice*, get the voice and set the params
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
  
            
//            OSCILLATOR A
            
            myVoice->setOsc1Freq(valTreeState.getRawParameterValue("osc1Freq"));
            myVoice->setOsc1Oct(valTreeState.getRawParameterValue("osc1Oct"));
            myVoice->setOsc1SawMode(valTreeState.getRawParameterValue("osc1SawMode"));
            myVoice->setOsc1SquareMode(valTreeState.getRawParameterValue("osc1SquareMode"));
            myVoice->setOsc1PWSetting(valTreeState.getRawParameterValue("osc1PW"));
            
//            OSCILLATOR B
            
            myVoice->setOsc2Freq(valTreeState.getRawParameterValue("osc2Freq"));
            myVoice->setOsc2Oct(valTreeState.getRawParameterValue("osc2Oct"));
            myVoice->setOsc2SawMode(valTreeState.getRawParameterValue("osc2SawMode"));
            myVoice->setOsc2SquareMode(valTreeState.getRawParameterValue("osc2SquareMode"));
            
//            MIXER
            
            myVoice->setNoiseLevel(valTreeState.getRawParameterValue("noiseLevel"));
            myVoice->setOsc1Level(valTreeState.getRawParameterValue("osc1Level"));
            myVoice->setOsc2Level(valTreeState.getRawParameterValue("osc2Level"));
            
            
            
//            Filter
            
            
            myVoice->setFilterCutoff(valTreeState.getRawParameterValue("filterCutoff"));
            myVoice->setFilterRes(valTreeState.getRawParameterValue("filterRes"));
            myVoice->setEnvAmt(valTreeState.getRawParameterValue("envAmt"));
            myVoice->setKeyAmt(valTreeState.getRawParameterValue("keyAMt"));
            myVoice->setFilterEnvelopeParams(valTreeState.getRawParameterValue("filterAttack"),
                                        valTreeState.getRawParameterValue("filterDecay"),
                                        valTreeState.getRawParameterValue("filterSustain"),
                                        valTreeState.getRawParameterValue("filterRelease"));
            //PITCH
            
            
            myVoice->setPitchBend(valTreeState.getRawParameterValue("pitchBend"));
            
            
//            GLIDE
            
            myVoice->setGlideRate(valTreeState.getRawParameterValue("glideRate"));
            myVoice->setGlideMode(valTreeState.getRawParameterValue("glideMode"));
            
            
        
            
//          LFO
            
            
          
            myVoice->setLfoRateSetting(valTreeState.getRawParameterValue("lfoRate"));
            myVoice->setLfoSawMode(valTreeState.getRawParameterValue("lfoSawMode"));
            myVoice->setLfoTriangleMode(valTreeState.getRawParameterValue("lfoTriangleMode"));
            myVoice->setLfoSquareMode(valTreeState.getRawParameterValue("lfoSquareMode"));
            
            
            
            
          
            
//            MODULATION
            
            
            myVoice->setModAmtFilterEnv(valTreeState.getRawParameterValue("modAmtFilterEnv"));
            myVoice->setModAmtLfo(valTreeState.getRawParameterValue("modAmtLfo"));
//        myVoice->setModAmtOscB(valTreeState.getRawParameterValue("modAmtOscB"));
       
            myVoice->setModModeOscAFreq(valTreeState.getRawParameterValue("modOscAFreqMode"));
            myVoice->setModModeOscAPW(valTreeState.getRawParameterValue("modOscAPWMode"));
            myVoice->setModModeOscBFreq(valTreeState.getRawParameterValue("modOscBFreqMode"));
            myVoice->setModModeOscBPW(valTreeState.getRawParameterValue("modOscBPWMode"));
            myVoice->setModModeFilter(valTreeState.getRawParameterValue("modFilterMode"));
            
            
            
            
//           AMPLIFIER
            
            myVoice->setAmpEnvelope(valTreeState.getRawParameterValue("attack"),
                                       valTreeState.getRawParameterValue("decay"),
                                       valTreeState.getRawParameterValue("sustain"),
                                       valTreeState.getRawParameterValue("release"));
            
//            MASTER
            myVoice->setMasterTune(valTreeState.getRawParameterValue("masterTune"));
            myVoice->setMasterGain(valTreeState.getRawParameterValue("mastergain"));
            
            
            

        }
    }
    buffer.clear();
    
    keyboardState.processNextMidiBuffer (midiMessages, 0, buffer.getNumSamples(), true);

    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    //
    //    dsp::AudioBlock<float> block (buffer);
    //    stateVariableFilter.process(dsp::ProcessContextReplacing<float> (block));
    
    
    // ??
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

