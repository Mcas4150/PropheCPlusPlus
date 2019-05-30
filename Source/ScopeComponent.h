
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
template <typename SampleType>
class ScopeComponent    : public Component,
private Timer
{
public:
    using Queue = AudioBufferQueue<SampleType>;
    
    //==============================================================================
    ScopeComponent (Queue& queueToUse)
    : audioBufferQueue (queueToUse)
    {
        sampleData.fill (SampleType (0));
        setFramesPerSecond (30);
    }
    
    //==============================================================================
    void setFramesPerSecond (int framesPerSecond)
    {
        jassert (framesPerSecond > 0 && framesPerSecond < 1000);
        startTimerHz (framesPerSecond);
    }
    
    //==============================================================================
    void paint (Graphics& g) override
    {
        g.fillAll (juce::Colours::black);
        g.setColour (juce::Colours::white);
        
        auto area = getLocalBounds();
        auto h = (SampleType) area.getHeight();
        auto w = (SampleType) area.getWidth();
        
        // Oscilloscope
        auto scopeRect = Rectangle<SampleType> { SampleType (0), SampleType (0), w, h / 2 };
        plot (sampleData.data(), sampleData.size(), g, scopeRect, SampleType (1), h / 4);
        
        // Spectrum
        auto spectrumRect = Rectangle<SampleType> { SampleType (0), h / 2, w, h / 2 };
        plot (spectrumData.data(), spectrumData.size() / 4, g, spectrumRect);
    }
    
    //==============================================================================
    void resized() override {}
    
private:
    //==============================================================================
    Queue& audioBufferQueue;
    std::array<SampleType, Queue::bufferSize> sampleData;
    
    juce::dsp::FFT fft { Queue::order };
    using WindowFun = juce::dsp::WindowingFunction<SampleType>;
    WindowFun windowFun { (size_t) fft.getSize(), WindowFun::hann };
    std::array<SampleType, 2 * Queue::bufferSize> spectrumData;
    
    //==============================================================================
    void timerCallback() override
    {
        audioBufferQueue.pop (sampleData.data());
        FloatVectorOperations::copy (spectrumData.data(), sampleData.data(), (int) sampleData.size());
        
        auto fftSize = (size_t) fft.getSize();
        
        jassert (spectrumData.size() == 2 * fftSize);
        windowFun.multiplyWithWindowingTable (spectrumData.data(), fftSize);
        fft.performFrequencyOnlyForwardTransform (spectrumData.data());
        
        static constexpr auto mindB = SampleType (-160);
        static constexpr auto maxdB = SampleType (0);
        
        for (auto& s : spectrumData)
            s = jmap (jlimit (mindB, maxdB, juce::Decibels::gainToDecibels (s) - juce::Decibels::gainToDecibels (SampleType (fftSize))), mindB, maxdB, SampleType (0), SampleType (1));
        
        repaint();
    }
    
    //==============================================================================
    static void plot (const SampleType* data,
                      size_t numSamples,
                      Graphics& g,
                      juce::Rectangle<SampleType> rect,
                      SampleType scaler = SampleType (1),
                      SampleType offset = SampleType (0))
    {
        auto w = rect.getWidth();
        auto h = rect.getHeight();
        auto right = rect.getRight();
        
        auto center = rect.getBottom() - offset;
        auto gain = h * scaler;
        
        for (size_t i = 1; i < numSamples; ++i)
            g.drawLine ({ jmap (SampleType (i - 1), SampleType (0), SampleType (numSamples - 1), SampleType (right - w), SampleType (right)),
                center - gain * data[i - 1],
                jmap (SampleType (i), SampleType (0), SampleType (numSamples - 1), SampleType (right - w), SampleType (right)),
                center - gain * data[i] });
    }
};
