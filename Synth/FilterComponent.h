#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class FilterComponent : public juce::Component
{
public:
	FilterComponent(SynthAudioProcessor& processor);

	void paint(juce::Graphics& g) override;
	void resized() override;

private:
	SynthAudioProcessor& processor;
	juce::Label labelName;
	juce::TextButton buttonLPF;
	juce::TextButton buttonHPF;
	juce::Slider sliderCutoff;
	juce::Slider sliderResonance;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentCutoff;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentResonance;
};



