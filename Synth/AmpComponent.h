#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "SynthComponent.h"

#include "RotarySlider.h"

class AmpComponent : public SynthComponent
{
public:
	AmpComponent(SynthAudioProcessor& processor);

	void resized() override;

private:
	juce::ComboBox distortionType;

	RotarySlider sliderGain;
	RotarySlider sliderWetLevel;
	RotarySlider sliderVolume;

	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> ampDistortionTypeAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampGainAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampWetLevelAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampVolumeAttachment;
};



