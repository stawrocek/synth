//based on https://suzuki-kengo.net/simple-reverb/

#include <JuceHeader.h>
#include "RotarySliderLookAndFeel.h"

#include "Styles.h"

RotarySliderLookAndFeel::RotarySliderLookAndFeel() {}
RotarySliderLookAndFeel::~RotarySliderLookAndFeel() {}

juce::Slider::SliderLayout RotarySliderLookAndFeel::getSliderLayout(juce::Slider& slider)
{
	auto localBounds = slider.getLocalBounds();

	juce::Slider::SliderLayout layout;

	layout.textBoxBounds = localBounds;
	layout.sliderBounds = localBounds;

	return layout;
}

void RotarySliderLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
	auto bounds = juce::Rectangle<float>(x, y + (height - width) / 2, width, width).reduced(2.0f);
	if (width > height)
		bounds = juce::Rectangle<float>(x + (width - height) / 2, y, height, height).reduced(2.0f);
	float radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.f;
	float arcWidth = radius * 0.1;
	float arcRadius = radius - arcWidth;
	float valueAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

	juce::Path backgroundArc;
	backgroundArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 
		0.0f, rotaryStartAngle, rotaryEndAngle, true);
	g.setColour(sliderArcColour);
	g.strokePath(backgroundArc, juce::PathStrokeType(arcWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

	juce::Path valueArc;
	valueArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius,
		0.0f, rotaryStartAngle, valueAngle, true);

	float sliderRatio = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());

	float alpha = 0.1f + sliderRatio * 0.9f;
	float brightness = 0.4f + sliderRatio * 0.6f;
	g.setColour(sliderArcColour.withAlpha(alpha).withBrightness(brightness));
	g.strokePath(valueArc, juce::PathStrokeType(arcWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

	float thumbWidth = arcWidth * 2;
	juce::Path thumb;
	thumb.addRectangle(-thumbWidth / 2, -thumbWidth / 2, thumbWidth, radius + arcWidth * 0.5);
	g.setColour(sliderFillColour);
	g.fillPath(thumb, juce::AffineTransform::rotation(valueAngle + 3.14159f).translated(bounds.getCentre()));
	
	g.fillEllipse(bounds.reduced(8.0f));
}

juce::Label* RotarySliderLookAndFeel::createSliderTextBox(juce::Slider& slider)
{
	auto* l = new juce::Label();
	l->setJustificationType(juce::Justification::centred);
	l->setColour(juce::Label::textColourId, sliderTextBoxTextColour);
	l->setColour(juce::Label::textWhenEditingColourId, sliderTextBoxTextColour);
	l->setColour(juce::Label::outlineWhenEditingColourId, juce::Colours::grey);
	l->setInterceptsMouseClicks(false, false);
	l->setFont(12);

	return l;
}

juce::Font RotarySliderLookAndFeel::getTextButtonFont(juce::TextButton&, int buttonHeight)
{
	juce::Font font("Avenir Next Medium", 20, 0);
	return { font };
}