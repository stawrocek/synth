#include "ADSRComponent.h"

#include "Config.h"
#include "Styles.h"

ADSRComponent::ADSRComponent(SynthAudioProcessor& processor_)
	:processor(processor_)
{
	labelName.setText("ADSR", juce::NotificationType::dontSendNotification);
	labelName.setJustificationType(juce::Justification::centred);
	labelName.setColour(juce::Label::backgroundColourId, componentHeaderColour);
	labelName.setColour(juce::Label::textColourId, componentHeaderFontColour);
	addAndMakeVisible(labelName);

	sliderAttack.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderAttack.setRange(0, 100.0, 1.0);
	sliderAttack.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderAttack.setTooltip("attack");
	sliderAttachmentAttack = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, adsrAttackParamId, sliderAttack);
	addAndMakeVisible(sliderAttack);

	sliderDecay.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderDecay.setRange(0, 100.0, 1.0);
	sliderDecay.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderDecay.setTooltip("decay");
	sliderAttachmentDecay = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, adsrDecayParamId, sliderDecay);
	addAndMakeVisible(sliderDecay);

	sliderSustain.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderSustain.setRange(0, 100.0, 1.0);
	sliderSustain.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderSustain.setTooltip("sustain");
	sliderAttachmentSustain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, adsrSustainParamId, sliderSustain);
	addAndMakeVisible(sliderSustain);

	sliderRelease.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderRelease.setRange(0, 100.0, 1.0);
	sliderRelease.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderRelease.setTooltip("release");
	sliderAttachmentRelease = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, adsrReleaseParamId, sliderRelease);
	addAndMakeVisible(sliderRelease);
}

void ADSRComponent::paint(juce::Graphics& g)
{
	g.setColour(componentBorderColour);

	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	g.drawRect(0, 0, w, h, componentBorderSize);
}

void ADSRComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();
	labelName.setBounds(0, 0, w, h * 0.1);

	sliderAttack.setBounds(juce::Rectangle<int>(       0, h * 0.1, w * 0.25, h * 0.9).reduced(3, 3));
	sliderDecay.setBounds(juce::Rectangle<int>(w * 0.25, h * 0.1, w * 0.25, h * 0.9).reduced(3, 3));
	sliderSustain.setBounds(juce::Rectangle<int>(w *  0.5, h * 0.1, w * 0.25, h * 0.9).reduced(3, 3));
	sliderRelease.setBounds(juce::Rectangle<int>(w * 0.75, h * 0.1, w * 0.25, h * 0.9).reduced(3, 3));
}

void ADSRComponent::buttonClicked(juce::Button* button) {
	
}