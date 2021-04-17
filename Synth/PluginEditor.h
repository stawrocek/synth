#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SynthAudioProcessorEditor  : public juce::AudioProcessorEditor,
								   private juce::Slider::Listener
{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	void sliderValueChanged(juce::Slider* slider) override;

    SynthAudioProcessor& audioProcessor;
	juce::Slider midiVolume;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};
