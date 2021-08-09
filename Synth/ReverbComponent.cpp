#include "ReverbComponent.h"

#include "Config.h"
#include "Styles.h"

ReverbComponent::ReverbComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "Reverb"),
	sliderRoomSize(0, 1.0, 0.01, reverbInitialRoomSize, "Room Size"),
	sliderDamping(0, 1.0, 0.01, reverbInitialDamping, "Damping"),
	sliderWetLevel(0, 1.0, 0.01, reverbInitialWetLevel, "Wet/Dry"),
	sliderWidth(0, 1.0, 0.01, reverbInitialWidth, "Width"),
	sliderFreezeMode(0, 1.0, 0.01, reverbInitialFreezeMode, "Freeze")

{
	sliderAttachmentRoomSize = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, reverbRoomSizeParamId, sliderRoomSize);
	addAndMakeVisible(sliderRoomSize);

	sliderAttachmentDamping = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, reverbDampingParamId, sliderDamping);
	addAndMakeVisible(sliderDamping);

	sliderAttachmentWetLevel = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, reverbWetLevelParamId, sliderWetLevel);
	addAndMakeVisible(sliderWetLevel);

	sliderAttachmentWidth = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, reverbWidthParamId, sliderWidth);
	addAndMakeVisible(sliderWidth);

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