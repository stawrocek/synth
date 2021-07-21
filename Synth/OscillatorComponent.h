#pragma once

#include <JuceHeader.h>

#include "Oscillator.h"
#include "PluginProcessor.h"

class OscillatorComponent : public juce::Component, juce::Button::Listener,
	private juce::Timer
{
public:
	OscillatorComponent(SynthAudioProcessor& processor, int identifier);

	void paint(juce::Graphics& g) override;
	void resized() override;
	void buttonClicked(juce::Button* button) override;

private:
	SynthAudioProcessor& processor;
	juce::Label labelName;
	int id;
	juce::String name;
	juce::ShapeButton btnOscSine;
	juce::ShapeButton btnOscRect;
	juce::ShapeButton btnOscTriangle;
	juce::ShapeButton btnOscSawtooth;
	void timerCallback() override;
	float offsetSine = 0.0;
	float offsetRect = 0.0;
	float offsetTriangle = 0.0;
	float offsetSaw = 0.0;

	void generateOscillatorSelectionButtonsShapes();
};



