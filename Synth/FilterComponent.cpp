#include "FilterComponent.h"

#include "Config.h"
#include "Styles.h"

FilterComponent::FilterComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "Filter", filterEnabledParamId),
	sliderCutoff(20, 1000, 1, filterInitialCutoff, filterCutoffParamName, filterCutoffParamId),
	sliderResonance(0.1, 10.0, 0.1, filterInitialResonance, filterResonanceParamName, filterResonanceParamId)
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

	sliderCutoff.setBounds(juce::Rectangle<int>(w * 0.33, off, w * 0.66, h-off).reduced(2*componentElementSpacer));
	sliderResonance.setBounds(juce::Rectangle<int>(0, off, w * 0.33, h-off).reduced(componentElementSpacer));
	comboboxFilterType.setBounds(juce::Rectangle<int>(5, h - 20, w * 0.33, 15));

	SynthComponent::resized();
}