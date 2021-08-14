#include "OscillatorComponent.h"
#include "Styles.h"
#include "Config.h"

OscillatorComponent::OscillatorComponent(SynthAudioProcessor& processor_, int identifier)
	:SynthComponent(processor_, "Oscillator " + std::to_string(identifier), 
		"OSC" + std::to_string(identifier)+"ENABLED"), id(identifier),
	name("osc"+std::to_string(id)),
	btnOscSine("btn_sin_"+name, OscillatorType::OscSin, identifier),
	btnOscRect("btn_rect_" + name, OscillatorType::OscSquare, identifier),
	btnOscTriangle("btn_triangle_" + name, OscillatorType::OscTriangle, identifier),
	btnOscSawtooth("btn_sawtooth_" + name, OscillatorType::OscSawtooth, identifier),
	sliderDetune(-100, 100, 1.0, 0, osc1DetuneParamName),
	sliderMix(0, 100, 1.0, 100, osc1MixParamName)
{
	btnOscSine.triggerClick();

	btnOscSine.onStateChange = [this]() {
		if (btnOscSine.getState() == Button::ButtonState::buttonDown) {
			processor.tree.getParameterAsValue("WAVEFORM" + std::to_string(id)).setValue(0);
		}
	};
	btnOscRect.onStateChange = [this]() {
		if (btnOscRect.getState() == Button::ButtonState::buttonDown) {
			processor.tree.getParameterAsValue("WAVEFORM" + std::to_string(id)).setValue(1);
		}
	};
	btnOscTriangle.onStateChange = [this]() {
		if (btnOscTriangle.getState() == Button::ButtonState::buttonDown) {
			processor.tree.getParameterAsValue("WAVEFORM" + std::to_string(id)).setValue(2);
		}
	};
	btnOscSawtooth.onStateChange = [this]() {
		if (btnOscSawtooth.getState() == Button::ButtonState::buttonDown) {
			processor.tree.getParameterAsValue("WAVEFORM" + std::to_string(id)).setValue(3);
		}
	};

	addAndMakeVisible(btnOscSine);
	addAndMakeVisible(btnOscRect);
	addAndMakeVisible(btnOscTriangle);
	addAndMakeVisible(btnOscSawtooth);

	sliderDetuneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "OSC"+std::to_string(id)+"DETUNE", sliderDetune);
	addAndMakeVisible(sliderDetune);

	sliderMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "OSC" + std::to_string(id) + "MIX", sliderMix);
	addAndMakeVisible(sliderMix);
}

void OscillatorComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	int off = (sliderFontSize + sliderSpacer);

	btnOscSine.setBorderSize(juce::BorderSize<int>(1));
	btnOscRect.setBorderSize(juce::BorderSize<int>(1));
	btnOscTriangle.setBorderSize(juce::BorderSize<int>(1));
	btnOscSawtooth.setBorderSize(juce::BorderSize<int>(1));

	juce::Rectangle<int> grid(0, 13, w / 2.0, h - 13);
	grid.reduce(componentBorderSize + 8, componentBorderSize + 8);
	if (grid.getWidth() > grid.getHeight())
		grid.setWidth(grid.getHeight());
	else if (grid.getHeight() > grid.getWidth())
		grid.setHeight(grid.getWidth());

	btnOscSine.setBounds    (juce::Rectangle<int>(grid.getX(), grid.getY(), grid.getWidth() / 2, grid.getHeight() / 2));
	btnOscRect.setBounds    (juce::Rectangle<int>(grid.getX() + grid.getWidth() / 2, grid.getY(), grid.getWidth() / 2, grid.getHeight() / 2));
	btnOscTriangle.setBounds(juce::Rectangle<int>(grid.getX(), grid.getY()+grid.getHeight() / 2, grid.getWidth() / 2, grid.getHeight() / 2));
	btnOscSawtooth.setBounds(juce::Rectangle<int>(grid.getX()+ grid.getWidth() / 2, grid.getY() + grid.getHeight() / 2, grid.getWidth() / 2, grid.getHeight() / 2));

	sliderDetune.setBounds(juce::Rectangle<int>(w*0.5, off, w*0.25, h-off).reduced(componentElementSpacer));
	sliderMix.setBounds(juce::Rectangle<int>(w*0.75, off, w*0.25, h-off).reduced(componentElementSpacer));
}