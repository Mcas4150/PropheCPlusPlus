

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(JuceSynthFrameworkAudioProcessor& p)
: processor(p)
, filterCutoff(8.3f, 8500.0f, "hz")
, labeledFilterCutoff("CUTOFF", filterCutoff)
, filterRes(1, 10, "")
, labeledFilterRes("RESONANCE", filterRes)
, envAmt(0, 1, "")
, labeledEnvAmt("ENV AMT", envAmt)
, keyAmt(0, 1, "")
, labeledKeyAmt("KEY AMT", keyAmt)
, filterAttack(1.5f, 7400.0f, "ms")
, labeledFilterAttack("ATTACK", filterAttack)
, filterDecay(0.5f, 11000.0f, "ms")
, labeledFilterDecay("DECAY", filterDecay)
, filterSustain(0.1f, 1.0f, "ms")
, labeledFilterSustain("SUSTAIN", filterSustain)
, filterRelease(0.5f, 11000.0f, "ms")
, labeledFilterRelease("RELEASE", filterRelease)

{
    setSize(250, 185);
    setLookAndFeel(lookAndFeel);
    mainGroup.setText("FILTER");
    mainGroup.setTextLabelPosition(juce::Justification::centredTop);
    mainGroup.setLookAndFeel(&groupLookAndFeel);
    addAndMakeVisible(&mainGroup);
    
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);
    filterMenu.setJustificationType(Justification::centred);
    //    addAndMakeVisible(&filterMenu);
    filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "filterType", filterMenu);
    
    filterCutoff.setRange(8.3, 8500.0);
    filterCutoff.setValue (3000.0);
    filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(labeledFilterCutoff);
    filterVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterCutoff", filterCutoff);
    filterCutoff.setSkewFactorFromMidPoint(1000.0);
    
    filterRes.setRange(1, 10);
    filterRes.setValue(1);
    addAndMakeVisible(labeledFilterRes);
    resVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterRes", filterRes);
    
    
    envAmt.setRange(0, 1);
    envAmt.setValue(1);
    envAmt.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(labeledEnvAmt);
    envAmtVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "envAmt", envAmt);
    
    keyAmt.setRange(0, 1);
    keyAmt.setValue(0);
    keyAmt.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(labeledKeyAmt);
    keyAmtVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "keyAmt", keyAmt);
    
    filterAttack.setRange(1.5, 7400.0f);
    filterAttack.setValue(0.1);
    addAndMakeVisible(labeledFilterAttack);
    filterAttackVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterAttack", filterAttack);
    
    filterDecay.setRange(0.5f, 11000.0f);
    filterDecay.setValue(1.0f);
    addAndMakeVisible(labeledFilterDecay);
    filterDecayVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterDecay", filterDecay);
    
    filterSustain.setRange(0.1f, 1.0f);
    filterSustain.setValue(0.8f);
    addAndMakeVisible(labeledFilterSustain);
    filterSustainVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterSustain", filterSustain);
    
    filterRelease.setRange(0.5f, 11000.0f);
    filterRelease.setValue(0.8f);
    addAndMakeVisible(labeledFilterRelease);
    filterReleaseVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterRelease", filterRelease);
    //
    //
    //
    //
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    //background ui stuff
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    //    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    
}

void Filter::resized()
{
    //need to come back and dynamically set these...ok for now
    juce::Rectangle<int> area = getLocalBounds().reduced(5);
    
    auto bounds = getLocalBounds().reduced(5);
    
    mainGroup.setBounds(area);
    mainGroup.setColour(0, Colours::white);
    auto widgetsArea = bounds.reduced(10);
    auto bottomWidgetsArea = bounds.reduced(10);
    widgetsArea.removeFromTop(5);
    widgetsArea.removeFromBottom(80);
    bottomWidgetsArea.removeFromBottom(5);
    bottomWidgetsArea.removeFromTop(80);
    int width = (widgetsArea.getWidth() - (4 - 1) * 10) / 4;
    int height = (widgetsArea.getHeight());
    labeledFilterCutoff.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    labeledFilterRes.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    labeledEnvAmt.setBounds(widgetsArea.removeFromLeft(width));
    widgetsArea.removeFromLeft(10);
    labeledKeyAmt.setBounds(widgetsArea.removeFromLeft(width));
    labeledFilterAttack.setBounds(bottomWidgetsArea.removeFromLeft(width));
    bottomWidgetsArea.removeFromLeft(10);
    labeledFilterDecay.setBounds(bottomWidgetsArea.removeFromLeft(width));
    bottomWidgetsArea.removeFromLeft(10);
    labeledFilterSustain.setBounds(bottomWidgetsArea.removeFromLeft(width));
    bottomWidgetsArea.removeFromLeft(10);
    labeledFilterRelease.setBounds(bottomWidgetsArea.removeFromLeft(width));
    
    //    filterCutoff.setBounds (40, 65, 25, 100);
    //    filterRes.setBounds (70, 65, 25, 100);
}



void Filter::sliderValueChanged(Slider* slider)
{
    
}
