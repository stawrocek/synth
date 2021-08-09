//based on https://suzuki-kengo.net/simple-reverb/

#pragma once

#include <JuceHeader.h>
#include "RotarySliderLookAndFeel.h"

class RotarySlider : public juce::Slider
{
public:
	RotarySlider(double minimum, double maximum, double step, double initial, juce::String tooltip);
	~RotarySlider() override;

	void paint(juce::Graphics& g) override;
	//void resized() override;

	void mouseDown(const juce::MouseEvent& event) override;
	void mouseUp(const juce::MouseEvent& event) override;
	

private:
	RotarySliderLookAndFeel rotarySliderLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotarySlider)
};