#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "SynthComponent.h"
#include "RotarySlider.h"

class ADSRComponent : public SynthComponent
{
public:
	ADSRComponent(SynthAudioProcessor& processor);

	void resized() override;

private:
	RotarySlider sliderAttack;
	RotarySlider sliderDecay;
	RotarySlider sliderSustain;
	RotarySlider sliderRelease;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentAttack;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentDecay;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentSustain;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentRelease;
};



