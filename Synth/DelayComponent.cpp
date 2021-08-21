#include "DelayComponent.h"

#include "Config.h"
#include "Styles.h"

DelayComponent::DelayComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "Delay", delayEnabledParamId),
	sliderTime(0.01, 4, 0.01, delayInitialTime, delayTimeParamName),
	sliderWetLevel(0.0, 1, 0.01, delayInitialWetLevel, delayWetLevelParamName),
	sliderFeedback(0.0, 1, 0.01, delayInitialFeedback, delayFeedbackParamName),
	sliderFilter(20, 2000, 1, delayInitialFilter, delayFilterParamName),
	buttonTailoff("Tailoff")
{
	sliderAttachmentTime = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, delayTimeParamId, sliderTime);
	addAndMakeVisible(sliderTime);

	sliderAttachmentWetLevel = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, delayWetLevelParamId, sliderWetLevel);
	addAndMakeVisible(sliderWetLevel);

	sliderAttachmentFeedback = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, delayFeedbackParamId, sliderFeedback);
	addAndMakeVisible(sliderFeedback);

	sliderAttachmentFilter = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, delayFilterParamId, sliderFilter);
	addAndMakeVisible(sliderFilter);

	buttonAttachmentTailoff = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		processor.tree, delayTailoffParamId, buttonTailoff);

	buttonTailoff.setToggleState(delayInitialTailoff, juce::NotificationType::dontSendNotification);
	addAndMakeVisible(buttonTailoff);
}

void DelayComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	int off = (sliderFontSize + sliderSpacer);

	sliderTime.setBounds(juce::Rectangle<int>(0, off, w * 0.25, h - off).reduced(componentElementSpacer));
	sliderFeedback.setBounds(juce::Rectangle<int>(w*0.25, off, w * 0.25, h - off).reduced(componentElementSpacer));
	sliderFilter.setBounds(juce::Rectangle<int>(w*0.5, off, w * 0.25, h - off).reduced(componentElementSpacer));
	sliderWetLevel.setBounds(juce::Rectangle<int>(w*0.75, off, w * 0.25, h - off).reduced(componentElementSpacer));
	
	buttonTailoff.setBounds(juce::Rectangle<int>(5, h-20, w*0.25, 15));

	SynthComponent::resized();
}