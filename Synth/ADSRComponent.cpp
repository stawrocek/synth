#include "ADSRComponent.h"

#include "Config.h"
#include "Styles.h"

ADSRComponent::ADSRComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "ADSR"),
	sliderAttack(0, 5.0, 0.1, adsrInitialAttack, "attack"),
	sliderDecay(0, 2, 0.1, adsrInitialDecay, "decay"),
	sliderSustain(0, 1, 0.05, adsrInitialSustain, "sustain"),
	sliderRelease(0, 2, 0.1, adsrInitialRelease, "release")
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

	sliderAttack.setBounds(juce::Rectangle<int>(       0,  0, w * 0.25, h).reduced(3, 3));
	sliderDecay.setBounds(juce::Rectangle<int>(w * 0.25,   0, w * 0.25, h).reduced(3, 3));
	sliderSustain.setBounds(juce::Rectangle<int>(w *  0.5, 0, w * 0.25, h).reduced(3, 3));
	sliderRelease.setBounds(juce::Rectangle<int>(w * 0.75, 0, w * 0.25, h).reduced(3, 3));

	SynthComponent::resized();
}