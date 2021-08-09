#include "ADSRComponent.h"

#include "Config.h"
#include "Styles.h"

ADSRComponent::ADSRComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "ADSR"),
	sliderAttack(0, 5.0, 0.1, adsrInitialAttack, adsrAttackParamName),
	sliderDecay(0, 2, 0.1, adsrInitialDecay, adsrDecayParamName),
	sliderSustain(0, 1, 0.05, adsrInitialSustain, adsrSustainParamName),
	sliderRelease(0, 2, 0.1, adsrInitialRelease, adsrReleaseParamName)
{
	sliderAttachmentAttack = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, adsrAttackParamId, sliderAttack);
	addAndMakeVisible(sliderAttack);

	sliderAttachmentDecay = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, adsrDecayParamId, sliderDecay);
	addAndMakeVisible(sliderDecay);

	sliderAttachmentSustain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, adsrSustainParamId, sliderSustain);
	addAndMakeVisible(sliderSustain);

	sliderAttachmentRelease = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, adsrReleaseParamId, sliderRelease);
	addAndMakeVisible(sliderRelease);
}

void ADSRComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	int off = (sliderFontSize + sliderSpacer);

	sliderAttack.setBounds(juce::Rectangle<int>(       0,  off, w * 0.25, h-off).reduced(componentElementSpacer));
	sliderDecay.setBounds(juce::Rectangle<int>(w * 0.25,   off, w * 0.25, h-off).reduced(componentElementSpacer));
	sliderSustain.setBounds(juce::Rectangle<int>(w *  0.5, off, w * 0.25, h-off).reduced(componentElementSpacer));
	sliderRelease.setBounds(juce::Rectangle<int>(w * 0.75, off, w * 0.25, h-off).reduced(componentElementSpacer));

	SynthComponent::resized();
}