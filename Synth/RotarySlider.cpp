//based on https://suzuki-kengo.net/simple-reverb/

#include <JuceHeader.h>
#include "RotarySlider.h"

#include "Styles.h"
#include "SynthComponent.h"
#include "Config.h"
#include "PluginEditor.h"

RotarySlider::RotarySlider(double minimum, double maximum, double step, double initial, juce::String tooltip, juce::String paramID_)
	:paramID(paramID_)
{
	setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	setTextBoxStyle(juce::Slider::TextBoxBelow, false, 0, 0);
	setLookAndFeel(&rotarySliderLookAndFeel);
	setVelocityBasedMode(true);
	setVelocityModeParameters(0.5, 1, 0.09, false);
	setRange(minimum, maximum, step);
	setValue(initial, juce::NotificationType::dontSendNotification);
	setRotaryParameters(juce::MathConstants<float>::pi * 1.25f,
		juce::MathConstants<float>::pi * 2.75f,
		true);
	setTooltip(tooltip);
	setWantsKeyboardFocus(true);
	onValueChange = [&]()
	{
		if (getValue() < 10)
			setNumDecimalPlacesToDisplay(2);
		else if (getValue() >= 10 && getValue() < 100)
			setNumDecimalPlacesToDisplay(1);
		else
			setNumDecimalPlacesToDisplay(0);
	};

	setBounds(getX(), getY(), getWidth(), getHeight());
}

RotarySlider::~RotarySlider()
{

}

void RotarySlider::paint(juce::Graphics& g)
{
	juce::Slider::paint(g);

	if (hasKeyboardFocus(false))
	{
		float width = getWidth();
		float height = getHeight();
		float x = 0;
		float y = 0;
		auto length = getHeight() > 15 ? 5.0f : 4.0f;
		auto thick = getHeight() > 15 ? 2.0f : 1.5f;
		
		auto b = juce::Rectangle<float>(x, y + (height - width) / 2, width, width).reduced(6.0f);
		if (width > height)
			b = juce::Rectangle<float>(x + (width - height) / 2, y, height, height).reduced(6.0f);

		g.setColour(sliderBorderColour);

		x = b.getX();
		y = b.getY();

		//         fromX           fromY            toX                      toY
		g.drawLine(x,              y,               x,                       y+length,                 thick);
		g.drawLine(x,              y,               x+length,                y,                        thick);
		g.drawLine(x,              y+b.getHeight(), x,                       y+b.getHeight() - length, thick);
		g.drawLine(x,              y+b.getHeight(), x+length,                y+b.getHeight(),          thick);
		g.drawLine(x+b.getWidth(), y+b.getHeight(), x+b.getWidth() - length, y+b.getHeight(),          thick);
		g.drawLine(x+b.getWidth(), y+b.getHeight(), x+b.getWidth(),          y+b.getHeight() - length, thick);
		g.drawLine(x+b.getWidth(), y,               x+b.getWidth() - length, y,                        thick);
		g.drawLine(x+b.getWidth(), y,               x+b.getWidth(),          y+length,                 thick);
	}
}

void RotarySlider::mouseDown(const juce::MouseEvent& event)
{
	juce::Slider::mouseDown(event);
	if (juce::ModifierKeys::currentModifiers.isRightButtonDown()) {
		if (SynthAudioProcessorEditor* editor =
			findParentComponentOfClass<SynthAudioProcessorEditor>()) {
			editor->showHostMenuForParam(event, paramID);
		}
	}
	setMouseCursor(juce::MouseCursor::NoCursor);
}

void RotarySlider::mouseUp(const juce::MouseEvent& event)
{
	juce::Slider::mouseUp(event);

	juce::Desktop::getInstance().getMainMouseSource().setScreenPosition(event.source.getLastMouseDownPosition());
	setMouseCursor(juce::MouseCursor::NormalCursor);
}

void RotarySlider::squareLayout() {
	int x = getX();
	int y = getY();
	int w = getWidth();
	int h = getHeight();

	if (h > w) {
		float newH = w;
		float newY = y + (h-newH)/2.0;
		setBounds(x, newY, w, newH);
	}
}