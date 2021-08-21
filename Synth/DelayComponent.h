#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "SynthComponent.h"
#include "RotarySlider.h"

class DelayComponent : public SynthComponent
{
public:
	DelayComponent(SynthAudioProcessor& processor);

	void resized() override;

private:
	RotarySlider sliderTime;
	RotarySlider sliderWetLevel;
	RotarySlider sliderFeedback;
	RotarySlider sliderFilter;
	juce::ToggleButton buttonTailoff;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentTime;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentWetLevel;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentFeedback;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentFilter;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> buttonAttachmentTailoff;
};



