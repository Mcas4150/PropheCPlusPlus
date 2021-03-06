/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
JuceSynthFrameworkAudioProcessorEditor::JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , processor (p)
    , keyboardComponent(p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
    , scopeComponent (processor.getAudioBufferQueue())
    , oscGui(p)
    , osc2Gui(p)
    , ampGui(p)
    , filterGui(p)
    , lfoGui(p)
    , glideGui(p)
    , wheelsGui(p)
    , mixerGui(p)
    , modeGui(p)
    , arpGui(p)
    , sequencerGui(p)
    , modulationGui(p)
    , masterGui(p)
{
    setSize (1000, 600);
    
    //    1000 x 600
    
    addAndMakeVisible(&oscGui);
    addAndMakeVisible(&osc2Gui);
    addAndMakeVisible(&lfoGui);
    addAndMakeVisible(&modulationGui);
    addAndMakeVisible(&ampGui);
    addAndMakeVisible(&filterGui);
    addAndMakeVisible(&glideGui);
    addAndMakeVisible(&scopeComponent);
    addAndMakeVisible(&mixerGui);
    addAndMakeVisible(&sequencerGui);
    addAndMakeVisible(&arpGui);
    addAndMakeVisible(&modeGui);
    addAndMakeVisible(&wheelsGui);
    addAndMakeVisible(&masterGui);
    addAndMakeVisible(&keyboardComponent);
    
}

JuceSynthFrameworkAudioProcessorEditor::~JuceSynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void JuceSynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    // 950 x 300
    //
    g.fillAll(Colour(71,69,64));
    juce::Rectangle <float> woodLeft (0, 0, 20, 600);
    juce::Rectangle <float> woodRight (980, 0, 20, 600);
    juce::Rectangle <float> metalInner (29, 9, 943, 283);
    juce::Rectangle <float> plasticStrip (20, 300, 960, 75);
    juce::Rectangle <float> plasticWheel (20, 375, 800, 225);
    juce::Rectangle <float> metalLogo (730, 312, 175, 50);
    
    juce::Rectangle <float> edgeLayer (20, 0, 960, 300);
    
    //     juce::Rectangle <float> area3 (800, 0, 400, 200);
    //    juce::Rectangle <float> area4 (0, 200, 200, 200);
    Image woodBackground = ImageCache::getFromMemory (BinaryData::wood_png, BinaryData::wood_pngSize);
    Image metalInnerBackground = ImageCache::getFromMemory (BinaryData::metal_jpg, BinaryData::metal_jpgSize);
    Image plasticBackground = ImageCache::getFromMemory (BinaryData::plastic_png, BinaryData::plastic_pngSize);
    Image edgeBackground = ImageCache::getFromMemory (BinaryData::Edge_png, BinaryData::Edge_pngSize);
    Image logoBackground = ImageCache::getFromMemory (BinaryData::ProLogo1_png, BinaryData::ProLogo1_pngSize);
    g.drawImage(woodBackground, woodLeft);
    g.drawImage(woodBackground, woodRight);
    g.drawImage(edgeBackground, edgeLayer);
    g.drawImage(metalInnerBackground, metalInner);
    g.drawImage(edgeBackground, edgeLayer);
    g.drawImage(plasticBackground, plasticStrip);
    g.drawImage(plasticBackground, plasticWheel);
    g.drawImage(logoBackground, metalLogo);
    
    //    g.drawImage(background, area3);
    //    g.drawImage(background, area4);
}

void JuceSynthFrameworkAudioProcessorEditor::resized()
{

    modulationGui.setBounds(25, 5, 150, 285);
    oscGui.setBounds(175, 10 , 275 , 95);
    mixerGui.setBounds( 450, 10 , 200 , 95 );
    filterGui.setBounds( 650, 10 , 250, 185);
    
    osc2Gui.setBounds(175, 100, 330, 95);
    glideGui.setBounds ( 510 , 100 , 125, 95 );
    masterGui.setBounds(910, 95, 70, 280 );
    
    lfoGui.setBounds(175, 190, 165, 95);
    sequencerGui.setBounds(340, 190, 90 , 95);
    arpGui.setBounds(425, 190, 75, 95 );
    modeGui.setBounds( 500, 190, 150, 95 );
    ampGui.setBounds( 650, 190, 250, 95 );
    
    
    scopeComponent.setBounds( 30, 375, 130, 130);
    wheelsGui.setBounds(40, 500, 100, 100);
    keyboardComponent.setBounds(170, 375, 810, 225);
    keyboardComponent.setKeyWidth(35);
    
    
}

void JuceSynthFrameworkAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    
    
}

void JuceSynthFrameworkAudioProcessorEditor::handleNoteOn(MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity)
{
    
}

void JuceSynthFrameworkAudioProcessorEditor::handleNoteOff(MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity)
{
    
}

void JuceSynthFrameworkAudioProcessorEditor::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    
}
