#include "ReverbComponent.h"

#include "Config.h"
#include "Styles.h"

ReverbComponent::ReverbComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "Reverb")
{
	sliderRoomSize.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderRoomSize.setRange(0, 1.0, 0.01);
	sliderRoomSize.setValue(reverbInitialRoomSize);
	sliderRoomSize.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderRoomSize.setTooltip("Room Size");
	sliderRoomSize.setNumDecimalPlacesToDisplay(2);
	sliderAttachmentRoomSize = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, reverbRoomSizeParamId, sliderRoomSize);
	
	addAndMakeVisible(sliderRoomSize);

	sliderDamping.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderDamping.setRange(0, 1.0, 0.01);
	sliderDamping.setValue(reverbInitialDamping);
	sliderDamping.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderDamping.setTooltip("Damping");
	sliderDamping.setNumDecimalPlacesToDisplay(2);
	sliderAttachmentDamping = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, reverbDampingParamId, sliderDamping);

	addAndMakeVisible(sliderDamping);

	sliderWetLevel.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderWetLevel.setRange(0, 1.0, 0.01);
	sliderWetLevel.setValue(reverbInitialWetLevel);
	sliderWetLevel.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderWetLevel.setTooltip("Wet/Dry Level");
	sliderWetLevel.setNumDecimalPlacesToDisplay(2);
	sliderAttachmentWetLevel = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, reverbWetLevelParamId, sliderWetLevel);

	addAndMakeVisible(sliderWetLevel);

	sliderWidth.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderWidth.setRange(0, 1.0, 0.01);
	sliderWidth.setValue(reverbInitialWidth);
	sliderWidth.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderWidth.setTooltip("Width");
	sliderWidth.setNumDecimalPlacesToDisplay(2);
	sliderAttachmentWidth = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, reverbWidthParamId, sliderWidth);

	addAndMakeVisible(sliderWidth);

	sliderFreezeMode.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderFreezeMode.setRange(0, 1.0, 0.01);
	sliderFreezeMode.setValue(reverbInitialFreezeMode);
	sliderFreezeMode.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderFreezeMode.setTooltip("Freeze Mode");
	sliderFreezeMode.setNumDecimalPlacesToDisplay(2);
	sliderAttachmentFreezeMode = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, reverbFreezeModeParamId, sliderFreezeMode);

	addAndMakeVisible(sliderFreezeMode);
}

void ReverbComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	const float w_ = w / 5.0;
	sliderRoomSize.setBounds(juce::Rectangle<int>  (       0, 0, w_, h).reduced(3, 3));
	sliderDamping.setBounds(juce::Rectangle<int>   (      w_, 0, w_, h).reduced(3, 3));
	sliderWetLevel.setBounds(juce::Rectangle<int>  (2.f * w_, 0, w_, h).reduced(3, 3));
	sliderWidth.setBounds(juce::Rectangle<int>     (3.f * w_, 0, w_, h).reduced(3, 3));
	sliderFreezeMode.setBounds(juce::Rectangle<int>(4.f * w_, 0, w_, h).reduced(3, 3));

	SynthComponent::resized();
}