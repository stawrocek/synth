#include "ReverbComponent.h"

#include "Config.h"
#include "Styles.h"

ReverbComponent::ReverbComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "Reverb", reverbEnabledParamId),
	sliderRoomSize(0, 1.0, 0.01, reverbInitialRoomSize, reverbRoomSizeParamName),
	sliderDamping(0, 1.0, 0.01, reverbInitialDamping, reverbDampingParamName),
	sliderWetLevel(0, 1.0, 0.01, reverbInitialWetLevel, reverbWetLevelParamName),
	sliderWidth(0, 1.0, 0.01, reverbInitialWidth, reverbWidthParamName),
	sliderFreezeMode(0, 1.0, 0.01, reverbInitialFreezeMode, reverbFreezeModeParamName)

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

	int off = (sliderFontSize + sliderSpacer);

	const float w_ = w / 5.0;
	sliderRoomSize.setBounds(juce::Rectangle<int>  (       0, off, w_, h - off).reduced(componentElementSpacer));
	sliderDamping.setBounds(juce::Rectangle<int>   (      w_, off, w_, h - off).reduced(componentElementSpacer));
	sliderWetLevel.setBounds(juce::Rectangle<int>  (2.f * w_, off, w_, h - off).reduced(componentElementSpacer));
	sliderWidth.setBounds(juce::Rectangle<int>     (3.f * w_, off, w_, h - off).reduced(componentElementSpacer));
	sliderFreezeMode.setBounds(juce::Rectangle<int>(4.f * w_, off, w_, h - off).reduced(componentElementSpacer));

	SynthComponent::resized();
}