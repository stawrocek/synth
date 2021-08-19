#include "FilterComponent.h"

#include "Config.h"
#include "Styles.h"

FilterComponent::FilterComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "Filter", filterEnabledParamId),
	sliderCutoff(20, 1000, 1, filterInitialCutoff, filterCutoffParamName),
	sliderResonance(0.1, 10.0, 0.1, filterInitialResonance, filterResonanceParamName)
{
	comboboxFilterType.setTextWhenNoChoicesAvailable("No waveform selected :(");
	juce::StringArray waveforms{ "lpf", "hpf" };
	comboboxFilterType.addItemList(waveforms, 1);
	comboboxFilterType.setSelectedItemIndex(0, juce::dontSendNotification);
	comboboxFilterType.addSeparator();
	filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
		processor.tree, filterTypeParamId, comboboxFilterType);
	addAndMakeVisible(comboboxFilterType);

	sliderAttachmentCutoff = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, filterCutoffParamId, sliderCutoff);
	addAndMakeVisible(sliderCutoff);

	sliderAttachmentResonance = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, filterResonanceParamId, sliderResonance);
	addAndMakeVisible(sliderResonance);
}

void FilterComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	int off = (sliderFontSize + sliderSpacer);

	comboboxFilterType.setBounds(juce::Rectangle<int>(0, h * 0.8, w * 0.33, h * 0.2).reduced(componentElementSpacer));
	sliderCutoff.setBounds(juce::Rectangle<int>(w * 0.33, off, w * 0.66, h-off).reduced(componentElementSpacer));
	sliderResonance.setBounds(juce::Rectangle<int>(0, off, w * 0.33, h-off).reduced(componentElementSpacer));

	SynthComponent::resized();
}