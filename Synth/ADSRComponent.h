#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class ADSRComponent : public juce::Component
{
public:
	ADSRComponent(SynthAudioProcessor& processor);

	void paint(juce::Graphics& g) override;
	void resized() override;

private:
	SynthAudioProcessor& processor;
	juce::Label labelName;
	juce::Slider sliderAttack;
	juce::Slider sliderDecay;
	juce::Slider sliderSustain;
	juce::Slider sliderRelease;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentAttack;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentDecay;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentSustain;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachmentRelease;
};



