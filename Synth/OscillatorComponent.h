#pragma once

#include <JuceHeader.h>

#include "Oscillator.h"
#include "PluginProcessor.h"
#include "SynthComponent.h"
#include "RotarySlider.h"
#include "WaveformButton.h"

class OscillatorComponent : public SynthComponent
{
public:
	OscillatorComponent(SynthAudioProcessor& processor, int identifier);

	void resized() override;

private:
	int id;
	juce::String name;
	WaveformButton btnOscSine;
	WaveformButton btnOscRect;
	WaveformButton btnOscTriangle;
	WaveformButton btnOscSawtooth;
	RotarySlider sliderDetune;
	RotarySlider sliderMix;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderDetuneAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderMixAttachment;
};



