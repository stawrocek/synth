#pragma once 

#include <JuceHeader.h>
#include <Oscillator.h>
#include <chrono>

#include "Styles.h"

class WaveformButton : public juce::ShapeButton
{
public:
	WaveformButton(const String& name, OscillatorType oscType_, int radioGroupId);

	void paint(juce::Graphics& graphics) override;
	void generateShape();
private:
	OscillatorType oscType;
};