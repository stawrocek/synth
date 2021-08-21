#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "SynthComponent.h"

#include "RotarySlider.h"

class FilterComponent : public SynthComponent
{
public:
	FilterComponent(SynthAudioProcessor& processor);

	void resized() override;

private:
	juce::ComboBox comboboxFilterType;

	RotarySlider sliderCutoff;
	RotarySlider sliderResonance;

	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentCutoff;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentResonance;
};



