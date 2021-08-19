#include "AmpComponent.h"

#include "Config.h"
#include "Styles.h"

AmpComponent::AmpComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "Amp", ampEnabledParamId),
	sliderGain(0.01, 10, 0.1, ampInitialGain, ampGainParamName),
	sliderWetLevel(0.0, 1.0, 0.01, ampInitialWetLevel, ampWetLevelParamName),
	sliderVolume(0, 1.0, 0.01, ampInitialVolume, ampVolumeParamName)
{
	juce::StringArray distortions{ "soft clipping", "hard clipping" };
	distortionType.addItemList(distortions, 1);
	distortionType.setSelectedItemIndex(0, juce::dontSendNotification);
	distortionType.addSeparator();
	ampDistortionTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
		processor.tree, ampDistortionTypeParamId, distortionType);
	addAndMakeVisible(distortionType);

	ampGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, ampGainParamId, sliderGain);
	ampWetLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, ampWetLevelParamId, sliderWetLevel);
	ampVolumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, ampVolumeParamId, sliderVolume);

	addAndMakeVisible(distortionType);
	addAndMakeVisible(sliderGain);
	addAndMakeVisible(sliderWetLevel);
	addAndMakeVisible(sliderVolume);	
}

void AmpComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	int off = (sliderFontSize + sliderSpacer);

	sliderGain.setBounds(juce::Rectangle<int>(0, off, w * 0.25, h-off).reduced(componentElementSpacer));
	sliderWetLevel.setBounds(juce::Rectangle<int>(w*0.25, off, w * 0.25, h-off).reduced(componentElementSpacer));
	sliderVolume.setBounds(juce::Rectangle<int>(w*0.5, off, w * 0.5, h-off).reduced(2*componentElementSpacer));
	distortionType.setBounds(juce::Rectangle<int>(sliderGain.getX(), sliderGain.getBottom()-5
		- abs((sliderGain.getHeight() - sliderGain.getWidth()) / 2),
		sliderWetLevel.getRight() - sliderGain.getX(), h*0.2).reduced(componentElementSpacer));

	SynthComponent::resized();
}