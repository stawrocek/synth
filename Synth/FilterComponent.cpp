#include "FilterComponent.h"

#include "Config.h"
#include "Styles.h"

FilterComponent::FilterComponent(SynthAudioProcessor& processor_)
	:processor(processor_)
{
	labelName.setText("Filter", juce::NotificationType::dontSendNotification);
	labelName.setJustificationType(juce::Justification::centred);
	labelName.setColour(juce::Label::backgroundColourId, componentHeaderColour);
	labelName.setColour(juce::Label::textColourId, componentHeaderFontColour);
	addAndMakeVisible(labelName);

	comboboxFilterType.setTextWhenNoChoicesAvailable("No waveform selected :(");
	juce::StringArray waveforms{ "lpf", "hpf" };
	comboboxFilterType.addItemList(waveforms, 1);
	comboboxFilterType.setSelectedItemIndex(0, juce::dontSendNotification);
	comboboxFilterType.addSeparator();
	filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
		processor.tree, filterTypeParamId, comboboxFilterType);

	addAndMakeVisible(comboboxFilterType);




	sliderCutoff.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderCutoff.setRange(20, 1000, 1);
	sliderCutoff.setValue(filterInitialCutoff);
	sliderCutoff.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderCutoff.setTooltip("Cutoff");
	sliderCutoff.setNumDecimalPlacesToDisplay(2);
	sliderCutoff.setSkewFactorFromMidPoint(1000.);
	sliderAttachmentCutoff = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, filterCutoffParamId, sliderCutoff);
	
	addAndMakeVisible(sliderCutoff);

	sliderResonance.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderResonance.setRange(0, 10.0, 0.1);
	sliderResonance.setValue(filterInitialResonance);
	sliderResonance.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderResonance.setTooltip("Resonance");
	sliderResonance.setNumDecimalPlacesToDisplay(2);
	sliderAttachmentResonance = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, filterResonanceParamId, sliderResonance);

	addAndMakeVisible(sliderResonance);
}

void FilterComponent::paint(juce::Graphics& g)
{
	g.setColour(componentBorderColour);

	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	g.drawRect(0, 0, w, h, componentBorderSize);
}

void FilterComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();
	labelName.setBounds(0, 0, w, h * 0.1);

	comboboxFilterType.setBounds(juce::Rectangle<int>(0, h * 0.4, w * 0.25, h * 0.2).reduced(3, 3));
	sliderCutoff.setBounds(juce::Rectangle<int>(w * 0.25, h * 0.1, w * 0.5, h * 0.9).reduced(3, 3));
	sliderResonance.setBounds(juce::Rectangle<int>(w * 0.75, h * 0.1, w * 0.25, h * 0.9).reduced(3, 3));
}