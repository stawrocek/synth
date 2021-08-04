#pragma once

#include <JuceHeader.h>

#include "Oscillator.h"
#include "PluginProcessor.h"
#include "SynthComponent.h"

class OscillatorComponent : public SynthComponent, juce::Button::Listener,
	private juce::Timer
{
public:
	OscillatorComponent(SynthAudioProcessor& processor, int identifier);

	void resized() override;
	void buttonClicked(juce::Button* button) override;

private:
	int id;
	juce::String name;
	juce::ShapeButton btnOscSine;
	juce::ShapeButton btnOscRect;
	juce::ShapeButton btnOscTriangle;
	juce::ShapeButton btnOscSawtooth;
	juce::Slider sliderDetune;
	juce::Slider sliderMix;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderDetuneAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderMixAttachment;
	void timerCallback() override;
	float offsetSine = 0.0;
	float offsetRect = 0.0;
	float offsetTriangle = 0.0;
	float offsetSaw = 0.0;

	void generateOscillatorSelectionButtonsShapes();
};



