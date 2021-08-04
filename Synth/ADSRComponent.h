#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "SynthComponent.h"

class ADSRComponent : public SynthComponent
{
public:
	ADSRComponent(SynthAudioProcessor& processor);

	void resized() override;

private:
	juce::Slider sliderAttack;
	juce::Slider sliderDecay;
	juce::Slider sliderSustain;
	juce::Slider sliderRelease;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentAttack;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentDecay;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentSustain;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentRelease;
};



