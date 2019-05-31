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
                  )
, tree(*this, nullptr, "PARAMETERS",
       {
           
//           OSCILLATOR A
           
           std::make_unique<AudioParameterFloat>("wavetype", "WaveType", NormalisableRange<float>(0.0f, 2.0f), 0.0f),
        std::make_unique<AudioParameterFloat>("osc1Freq", "Osc1Freq", NormalisableRange<float>(-2.0f, 2.0f), 0.0f),
          std::make_unique<AudioParameterFloat>("osc1Oct", "Osc1Oct", NormalisableRange<float>(0.0f, 3.0f), 0.0f),
           
//           OSCILLATOR B
           
           std::make_unique<AudioParameterFloat>("osc2Freq", "Osc2Freq", NormalisableRange<float>(-2.0f, 2.0f), 0.0f),
           
           std::make_unique<AudioParameterFloat>("osc2Oct", "Osc2Oct", NormalisableRange<float>(0.0f, 3.0f), 0.0f),
          
           
           std::make_unique<AudioParameterFloat>("wavetype2", "WaveType2", NormalisableRange<float>(0.0f, 2.0f), 0.0f),
           

        
           
//           MIXER
           
           std::make_unique<AudioParameterFloat>("osc1Level", "Osc1Level", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
           std::make_unique<AudioParameterFloat>("osc2Level", "Osc2Level", NormalisableRange<float>(0.0f, 1.0f), 0.5f),
           std::make_unique<AudioParameterFloat>("noiseLevel", "NoiseLevel", NormalisableRange<float>(0.0f, 1.0f), 0.0f),
           
           
           std::make_unique<AudioParameterFloat>("blend", "Osc2Blend", NormalisableRange<float>(0.0f, 1.0f), 0.6f),
           
           
//          FILTER
        
           std::make_unique<AudioParameterFloat>("filterType", "FilterType", NormalisableRange<float>(0.0f, 2.0f), 0.0f),
           
           std::make_unique<AudioParameterFloat>("filterCutoff", "FilterCutoff", NormalisableRange<float>(8.3f, 8500.0f), 5000.0f),
           std::make_unique<AudioParameterFloat>("filterRes", "FilterRes", NormalisableRange<float>(1.0f, 10.0f), 1.0f),
           std::make_unique<AudioParameterFloat>("envAmt", "EnvAmt", NormalisableRange<float>(0.0f, 1.0f), 1.0f),
           std::make_unique<AudioParameterFloat>("keyAmt", "keyAmt", NormalisableRange<float>(0.0f, 1.0f), 0.0f),
           std::make_unique<AudioParameterFloat>("filterAttack", "FilterAttack", NormalisableRange<float>(1.5f, 7400.0f), 0.1f),
           std::make_unique<AudioParameterFloat>("filterDecay", "FilterDecay", NormalisableRange<float>(0.5f, 11000.0f), 1.0f),
           std::make_unique<AudioParameterFloat>("filterSustain", "FilterSustain", NormalisableRange<float>(0.0f, 1.0f), 0.8f),
           std::make_unique<AudioParameterFloat>("filterRelease", "FilterRelease", NormalisableRange<float>(0.5f, 11000.0f), 0.1f),
           
           
//           PITCH
           
           std::make_unique<AudioParameterFloat>("pitchBend", "PitchBend", NormalisableRange<float>(-1.0f, 1.0f), 0.0f),
           
           
//           GLIDE
           std::make_unique<AudioParameterFloat>("glideRate", "GlideRate", NormalisableRange<float>(0.0f, 0.99f), 0.0f),
           std::make_unique<AudioParameterFloat>("glideMode", "GlideMode", NormalisableRange<float>(0.0f, 1.0f), 0.0f),
           
         
//           LFO
           
           std::make_unique<AudioParameterFloat>("lfoRate", "LfoRate", NormalisableRange<float>(0.0f, 30.0f), 0.0f),
           std::make_unique<AudioParameterFloat>("lfoDelay", "LfoDelay", NormalisableRange<float>(30.0f, 50000.0f), 30.0f),
           
//        MODULATION
           
         std::make_unique<AudioParameterFloat>("modAmtFilterEnv", "ModAmtFilterEnv", NormalisableRange<float>(0.0f, 1.00), 0),
           
         std::make_unique<AudioParameterFloat>("modAmtLfo", "ModAmtLfo", NormalisableRange<float>(0.0f, 1.00f), 0),
           
           
           
//          AMPLIFIER
           
           std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(1.5f, 7400.0f), 0.1f),
           std::make_unique<AudioParameterFloat>("decay", "Decay", NormalisableRange<float>(0.5f, 11000.0f), 1.0f),
           std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.0f, 1.0f), 0.8f),
           std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.5f, 11000.0f), 0.1f),
          

//           MASTER

           std::make_unique<AudioParameterFloat>("mastergain", "MasterGain", NormalisableRange<float>(0.0f, 1.0f), 0.3f),
           std::make_unique<AudioParameterFloat>("masterTune", "MasterTune", NormalisableRange<float>(-1.0f, 1.0f), 0.0f)
           
       }),
lfoPhase(0.0f)
#endif
{
    
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
            
            myVoice->setOsc1Freq(tree.getRawParameterValue("osc1Freq"));
            myVoice->setOsc1Oct(tree.getRawParameterValue("osc1Oct"));
            myVoice->getOscType(tree.getRawParameterValue("wavetype"));
            
            
//            OSCILLATOR B
            
            myVoice->setOsc2Freq(tree.getRawParameterValue("osc2Freq"));
            myVoice->setOsc2Oct(tree.getRawParameterValue("osc2Oct"));
            myVoice->getOsc2Type(tree.getRawParameterValue("wavetype2"));
            
            
//            MIXER
            
            myVoice->setNoiseLevel(tree.getRawParameterValue("noiseLevel"));
            myVoice->setOsc1Level(tree.getRawParameterValue("osc1Level"));
            myVoice->setOsc2Level(tree.getRawParameterValue("osc2Level"));
            
            
            
//            Filter
            
            myVoice->setFilterType(tree.getRawParameterValue("filterType"));
            
            myVoice->setFilterCutoff(tree.getRawParameterValue("filterCutoff"));
            myVoice->setFilterRes(tree.getRawParameterValue("filterRes"));
            myVoice->setEnvAmt(tree.getRawParameterValue("envAmt"));
            myVoice->setKeyAmt(tree.getRawParameterValue("keyAMt"));
        myVoice->setFilterEnvelopeParams(tree.getRawParameterValue("filterAttack"),
                                        tree.getRawParameterValue("filterDecay"),
                                        tree.getRawParameterValue("filterSustain"),
                                     tree.getRawParameterValue("filterRelease"));
            //PITCH
            
            
            myVoice->setPitchBend(tree.getRawParameterValue("pitchBend"));
            
            
//            GLIDE
            
            myVoice->setGlideRate(tree.getRawParameterValue("glideRate"));
            myVoice->setGlideMode(tree.getRawParameterValue("glideMode"));
            
            
        
            
//          LFO
            
            
            myVoice->setLfoType(tree.getRawParameterValue("lfoMenu"));
            myVoice->setLfoRateSetting(tree.getRawParameterValue("lfoRate"));
            myVoice->setLfoDelaySetting(tree.getRawParameterValue("lfoDelay"));
            
          
            
//            MODULATION
            
            
        myVoice->setmodAmtLfo(tree.getRawParameterValue("modAmtLfo"));
        myVoice->setModAmtFilterEnv(tree.getRawParameterValue("modAmtFilterEnv"));
            
            
//           AMPLIFIER
            
            myVoice->setAmpEnvelope(tree.getRawParameterValue("attack"),
                                       tree.getRawParameterValue("decay"),
                                       tree.getRawParameterValue("sustain"),
                                       tree.getRawParameterValue("release"));
            
//            MASTER
            myVoice->setMasterTune(tree.getRawParameterValue("masterTune"));
            myVoice->setMasterGain(tree.getRawParameterValue("mastergain"));
            
            
            

        }
    }
    
    buffer.clear();
    keyboardState.processNextMidiBuffer (midiMessages, 0, buffer.getNumSamples(), true);

    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    //
    //    dsp::AudioBlock<float> block (buffer);
    //    stateVariableFilter.process(dsp::ProcessContextReplacing<float> (block));
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
}

//==============================================================================
void JuceSynthFrameworkAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceSynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceSynthFrameworkAudioProcessor();
}

