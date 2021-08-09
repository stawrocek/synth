#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "SynthComponent.h"
#include "RotarySlider.h"

class ReverbComponent : public SynthComponent
{
public:
	ReverbComponent(SynthAudioProcessor& processor);

	void resized() override;

private:
	RotarySlider sliderRoomSize;
	RotarySlider sliderDamping;
	RotarySlider sliderWetLevel;
	RotarySlider sliderWidth;
	RotarySlider sliderFreezeMode;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentRoomSize;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentDamping;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentWetLevel;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentWidth;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentFreezeMode;
};



