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
	juce::ComboBox comboboxFilterType;
	juce::Slider sliderCutoff;
	juce::Slider sliderResonance;

	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentCutoff;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentResonance;
};



