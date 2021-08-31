#include "DelayComponent.h"

#include "Config.h"
#include "Styles.h"

DelayComponent::DelayComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "Delay", delayEnabledParamId),
	sliderTime(0.01, 4, 0.01, delayInitialTime, delayTimeParamName, delayTimeParamId),
	sliderWetLevel(0.0, 1, 0.01, delayInitialWetLevel, delayWetLevelParamName, delayWetLevelParamId),
	sliderFeedback(0.0, 1, 0.01, delayInitialFeedback, delayFeedbackParamName, delayFeedbackParamId),
	sliderFilter(20, 2000, 1, delayInitialFilter, delayFilterParamName, delayFilterParamId),
	buttonTailoff("Tailoff")
{
	comboboxFilterType.setTextWhenNoChoicesAvailable("No waveform selected :(");
	juce::StringArray waveforms{ "lpf", "hpf" };
	comboboxFilterType.addItemList(waveforms, 1);
	comboboxFilterType.setSelectedItemIndex(0, juce::dontSendNotification);
	comboboxFilterType.addSeparator();
	filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
		processor.tree, delayFilterTypeParamId, comboboxFilterType);
	addAndMakeVisible(comboboxFilterType);

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

	sliderWetLevel.setBounds(juce::Rectangle<int>(0, off, w * 0.25, h - off).reduced(2 * componentElementSpacer));
	sliderFilter.setBounds(juce::Rectangle<int>(w * 0.25, off, w * 0.25, h - off).reduced(2 * componentElementSpacer));
	sliderTime.setBounds(juce::Rectangle<int>(w*0.5, off, w * 0.25, h - off).reduced(2*componentElementSpacer));
	sliderFeedback.setBounds(juce::Rectangle<int>(w*0.75, off, w * 0.25, h - off).reduced(2*componentElementSpacer));
	
	buttonTailoff.setBounds(juce::Rectangle<int>(5, h-20, w*0.25, 15));
	comboboxFilterType.setBounds(juce::Rectangle<int>(sliderFilter.getX(), h - 20, sliderFilter.getWidth(), 15));

	SynthComponent::resized();
}