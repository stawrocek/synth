#include "SynthComponent.h"

#include "Config.h"
#include "Styles.h"
#include "RotarySlider.h"
#include "PluginEditor.h"


SynthComponent::SynthComponent(SynthAudioProcessor& processor_, const juce::String& name_,
	const juce::String& buttonNameParamId)
	:processor(processor_), name(name_), buttonName(name_)
{
	buttonName.setLookAndFeel(&nameButtonLookAndFeel);
	buttonName.setClickingTogglesState(true);
	buttonName.setColour(TextButton::buttonColourId, buttonNameOffColour);
	buttonName.setColour(TextButton::buttonOnColourId, buttonNameOnColour);
	buttonName.setColour(TextButton::textColourOffId, buttonNameOffFontColour);
	buttonName.setColour(TextButton::textColourOnId, buttonNameOnFontColour);
	buttonName.setToggleState(true, juce::NotificationType::dontSendNotification);
	nameButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		processor.tree, buttonNameParamId, buttonName);
	addAndMakeVisible(buttonName);

	setColour(outlineColourId, groupComponentOutlineOnColor);
	setTextLabelPosition(juce::Justification::topLeft);
}

SynthComponent::~SynthComponent() {
}

void SynthComponent::paint(Graphics& g) {
	const float textH = 15.0f;
	const float indent = 3.0f;
	const float textEdgeGap = 4.0f;
	auto cs = 5.0f;

	Font f(textH);

	Path p;
	auto x = indent;
	auto y = f.getAscent() - 3.0f;
	auto w = jmax(0.0f, (float)getWidth() - x * 2.0f);
	auto h = jmax(0.0f, (float)getHeight() - y - indent);
	cs = jmin(cs, w * 0.5f, h * 0.5f);
	auto cs2 = 2.0f * cs;

	auto textW = name.isEmpty() ? 0
		: jlimit(0.0f,
			jmax(0.0f, w - cs2 - textEdgeGap * 2),
			(float)f.getStringWidth(name) + textEdgeGap * 2.0f);
	auto textX = cs + textEdgeGap;

	p.startNewSubPath(x + textX + textW, y);
	p.lineTo(x + w - cs, y);

	p.addArc(x + w - cs2, y, cs2, cs2, 0, MathConstants<float>::halfPi);
	p.lineTo(x + w, y + h - cs);

	p.addArc(x + w - cs2, y + h - cs2, cs2, cs2, MathConstants<float>::halfPi, MathConstants<float>::pi);
	p.lineTo(x + cs, y + h);

	p.addArc(x, y + h - cs2, cs2, cs2, MathConstants<float>::pi, MathConstants<float>::pi * 1.5f);
	p.lineTo(x, y + cs);

	p.addArc(x, y, cs2, cs2, MathConstants<float>::pi * 1.5f, MathConstants<float>::twoPi);
	p.lineTo(x + textX, y);

	auto alpha = isEnabled() ? 1.0f : 0.5f;

	g.setColour(findColour(GroupComponent::outlineColourId)
		.withMultipliedAlpha(alpha));

	g.strokePath(p, PathStrokeType(2.0f));

	buttonName.setBounds(roundToInt(x+textX), 2,
		roundToInt(textW), roundToInt(textH));

	auto children = getChildren();
	for (auto child : children) {
		RotarySlider* slider = dynamic_cast<RotarySlider*>(child);
		if (slider != nullptr) {
			g.setColour(sliderFillColour);
			g.setFont(sliderFontSize);
			const int textHeight = sliderFontSize + sliderSpacer;
			g.drawText(slider->getTooltip(), slider->getX(), slider->getY() - textHeight,
				slider->getWidth(), textHeight, juce::Justification::centredBottom, true);
		}
	}
}

Font SynthComponent::NameButtonLookAndFeel::getTextButtonFont(TextButton&, int buttonHeight) 
{
	return { jmin(16.0f, (float)buttonHeight * 0.8f) };
}

void SynthComponent::squareLayout() {
	auto children = getChildren();
	for (auto child : children) {
		RotarySlider* slider = dynamic_cast<RotarySlider*>(child);
		if (slider != nullptr) {
			slider->squareLayout();
		}
	}
}

void SynthComponent::resized() {
	squareLayout();
}