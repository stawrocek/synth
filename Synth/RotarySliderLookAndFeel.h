// based on https://suzuki-kengo.net/simple-reverb/

#pragma once

#include <JuceHeader.h>

class RotarySliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
	RotarySliderLookAndFeel();
	~RotarySliderLookAndFeel();

	juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;

	void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle,
		float rotaryEndAngle, juce::Slider&) override;

	juce::Label* createSliderTextBox(juce::Slider& slider) override;

	juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotarySliderLookAndFeel)
};