#include "LFOComponent.h"

#include "Config.h"
#include "Styles.h"
#include "Oscillator.h"

LFOComponent::LFOComponent(SynthAudioProcessor& processor_)
	:SynthComponent(processor_, "LFO", lfoEnabledParamId),
	btnOscSine("btn_sin_lfo", OscillatorType::OscSin, 101),
	btnOscRect("btn_rect_lfo", OscillatorType::OscSquare, 101),
	btnOscTriangle("btn_triangle_lfo", OscillatorType::OscTriangle, 101),
	btnOscSawtooth("btn_sawtooth_lfo", OscillatorType::OscSawtooth, 101),
	sliderLFORate(0.1, 10, 0.01, lfoInitialRate, lfoRateParamName, lfoRateParamId),
	sliderLFOIntensity(0.0, 1.0, 0.01, lfoInitialIntensity, lfoIntensityParamName, lfoIntensityParamId),
	lfoTargets("LFO Targets", "Targets"),
	lfoTargetFilterCutoff("Cutoff"),
	lfoTargetDetune("Detune"),
	lfoTargetVolume("Volume")
{
	btnOscSine.triggerClick();

	btnOscSine.onStateChange = [this]() {
		if (btnOscSine.getState() == Button::ButtonState::buttonDown) {
			processor.tree.getParameterAsValue("LFO_WAVEFORM_TYPE").setValue(0);
		}
	};
	btnOscRect.onStateChange = [this]() {
		if (btnOscRect.getState() == Button::ButtonState::buttonDown) {
			processor.tree.getParameterAsValue("LFO_WAVEFORM_TYPE").setValue(1);
		}
	};
	btnOscTriangle.onStateChange = [this]() {
		if (btnOscTriangle.getState() == Button::ButtonState::buttonDown) {
			processor.tree.getParameterAsValue("LFO_WAVEFORM_TYPE").setValue(2);
		}
	};
	btnOscSawtooth.onStateChange = [this]() {
		if (btnOscSawtooth.getState() == Button::ButtonState::buttonDown) {
			processor.tree.getParameterAsValue("LFO_WAVEFORM_TYPE").setValue(3);
		}
	};

	addAndMakeVisible(btnOscSine);
	addAndMakeVisible(btnOscRect);
	addAndMakeVisible(btnOscTriangle);
	addAndMakeVisible(btnOscSawtooth);

	sliderAttachmentRate = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, lfoRateParamId, sliderLFORate);
	addAndMakeVisible(sliderLFORate);

	sliderAttachmentIntensity = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, lfoIntensityParamId, sliderLFOIntensity);
	addAndMakeVisible(sliderLFOIntensity);

	lfoTargetFilterCutoff.setClickingTogglesState(true);
	lfoTargetFilterCutoff.setColour(TextButton::ColourIds::buttonColourId, lfoTargetOff);
	lfoTargetFilterCutoff.setColour(TextButton::ColourIds::buttonOnColourId, lfoTargetOn);
	buttonTarget1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		processor.tree, lfoTarget1ActiveParamId, lfoTargetFilterCutoff);

	lfoTargetDetune.setClickingTogglesState(true);
	lfoTargetDetune.setColour(TextButton::ColourIds::buttonColourId, lfoTargetOff);
	lfoTargetDetune.setColour(TextButton::ColourIds::buttonOnColourId, lfoTargetOn);
	buttonTarget2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		processor.tree, lfoTarget2ActiveParamId, lfoTargetDetune);

	lfoTargetVolume.setClickingTogglesState(true);
	lfoTargetVolume.setColour(TextButton::ColourIds::buttonColourId, lfoTargetOff);
	lfoTargetVolume.setColour(TextButton::ColourIds::buttonOnColourId, lfoTargetOn);
	buttonTarget3Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		processor.tree, lfoTarget3ActiveParamId, lfoTargetVolume);

	lfoTargets.addAndMakeVisible(lfoTargetFilterCutoff);
	lfoTargets.addAndMakeVisible(lfoTargetDetune);
	lfoTargets.addAndMakeVisible(lfoTargetVolume);
	addAndMakeVisible(lfoTargets);
}

void LFOComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	int off = (sliderFontSize + sliderSpacer);

	juce::Rectangle<int> grid(0, 13, w / 2.0, h - 13);
	grid.reduce(componentBorderSize + 8, componentBorderSize + 8);
	if (grid.getWidth() > grid.getHeight())
		grid.setWidth(grid.getHeight());
	else if (grid.getHeight() > grid.getWidth())
		grid.setHeight(grid.getWidth());

	btnOscSine.setBounds(juce::Rectangle<int>(grid.getX(), grid.getY(), grid.getWidth() / 2, grid.getHeight() / 2));
	btnOscRect.setBounds(juce::Rectangle<int>(grid.getX() + grid.getWidth() / 2, grid.getY(), grid.getWidth() / 2, grid.getHeight() / 2));
	btnOscTriangle.setBounds(juce::Rectangle<int>(grid.getX(), grid.getY() + grid.getHeight() / 2, grid.getWidth() / 2, grid.getHeight() / 2));
	btnOscSawtooth.setBounds(juce::Rectangle<int>(grid.getX() + grid.getWidth() / 2, grid.getY() + grid.getHeight() / 2, grid.getWidth() / 2, grid.getHeight() / 2));

	sliderLFORate.setBounds(juce::Rectangle<int>(grid.getRight(), off, w*0.2, h-off));
	sliderLFOIntensity.setBounds(sliderLFORate.getBounds().withX(sliderLFORate.getRight()));

	lfoTargets.setBounds(juce::Rectangle<int>(sliderLFOIntensity.getRight(),
		grid.getY(), w-sliderLFOIntensity.getRight()-grid.getX(), grid.getHeight()));

	lfoTargetFilterCutoff.setBounds(8, 20, lfoTargets.getWidth()-16, 20);
	lfoTargetDetune.setBounds(lfoTargetFilterCutoff.getBounds().translated(0, 25));
	lfoTargetVolume.setBounds(lfoTargetDetune.getBounds().translated(0, 25));

	SynthComponent::resized();
}
