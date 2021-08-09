#include "FilterComponent.h"

#include "Config.h"
#include "Styles.h"

FilterComponent::FilterComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "Filter"),
	sliderCutoff(20, 1000, 1, filterInitialCutoff, "Cutoff"),
	sliderResonance(0, 10.0, 0.1, filterInitialResonance, "Resonance")
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

	comboboxFilterType.setBounds(juce::Rectangle<int>(0, h * 0.4, w * 0.25, h * 0.2).reduced(componentElementSpacer));
	sliderCutoff.setBounds(juce::Rectangle<int>(w * 0.25, 0.0, w * 0.5, h).reduced(componentElementSpacer));
	sliderResonance.setBounds(juce::Rectangle<int>(w * 0.75, 0.0, w * 0.25, h).reduced(componentElementSpacer));

	SynthComponent::resized();
}