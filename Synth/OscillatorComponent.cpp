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
	sliderDetuneCents(-100, 100, 1.0, 0, osc1DetuneParamName, "OSC" + std::to_string(id) + "DETUNE"),
	sliderDetuneSteps(-12, 12, 1.0, 0, osc1DetuneStepsParamName, "OSC" + std::to_string(id) + "DETUNESTEPS"),
	sliderMix(0, 100, 1.0, 100, osc1MixParamName, "OSC" + std::to_string(id) + "MIX")
{
	addAndMakeVisible(btnOscSine);
	addAndMakeVisible(btnOscRect);
	addAndMakeVisible(btnOscTriangle);
	addAndMakeVisible(btnOscSawtooth);

	sliderDetuneStepsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "OSC" + std::to_string(id) + "DETUNESTEPS", sliderDetuneSteps);
	addAndMakeVisible(sliderDetuneSteps);

	sliderDetuneCentsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "OSC"+std::to_string(id)+"DETUNE", sliderDetuneCents);
	addAndMakeVisible(sliderDetuneCents);

	sliderMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "OSC" + std::to_string(id) + "MIX", sliderMix);
	addAndMakeVisible(sliderMix);

	buttonWaveformSineAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		processor.tree, "OSC"+ std::to_string(id) +"_WAVEFORM_SINE", btnOscSine);
	buttonWaveformSquareAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		processor.tree, "OSC" + std::to_string(id) + "_WAVEFORM_SQUARE", btnOscRect);
	buttonWaveformTriangleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		processor.tree, "OSC" + std::to_string(id) + "_WAVEFORM_TRIANGLE", btnOscTriangle);
	buttonWaveformSawtoothAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		processor.tree, "OSC" + std::to_string(id) + "_WAVEFORM_SAWTOOTH", btnOscSawtooth);
}

void OscillatorComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	int off = (sliderFontSize + sliderSpacer);

	juce::Rectangle<int> grid(0, 13, w / 3, h - 8);
	grid.reduce(componentBorderSize + 8, componentBorderSize + 8);
	if (grid.getWidth() > grid.getHeight())
		grid.setWidth(grid.getHeight());
	else if (grid.getHeight() > grid.getWidth())
		grid.setHeight(grid.getWidth());

	btnOscSine.setBounds    (juce::Rectangle<int>(grid.getX(), grid.getY(), grid.getWidth() / 2, grid.getHeight() / 2));
	btnOscRect.setBounds    (juce::Rectangle<int>(grid.getX() + grid.getWidth() / 2, grid.getY(), grid.getWidth() / 2, grid.getHeight() / 2));
	btnOscTriangle.setBounds(juce::Rectangle<int>(grid.getX(), grid.getY()+grid.getHeight() / 2, grid.getWidth() / 2, grid.getHeight() / 2));
	btnOscSawtooth.setBounds(juce::Rectangle<int>(grid.getX()+ grid.getWidth() / 2, grid.getY() + grid.getHeight() / 2, grid.getWidth() / 2, grid.getHeight() / 2));

	float w2 = (w - grid.getRight()) - 10;

	sliderDetuneSteps.setBounds(juce::Rectangle<int>(grid.getRight()+5, off, w2/3.0, h-off).reduced(componentElementSpacer));
	sliderDetuneCents.setBounds(juce::Rectangle<int>(grid.getRight()+5+w2 / 3.0, off, w2/3.0, h-off).reduced(componentElementSpacer));
	sliderMix.setBounds(juce::Rectangle<int>(grid.getRight() + 5 + 2.0*w2 / 3.0, off, w2/3.0, h-off).reduced(componentElementSpacer));

	SynthComponent::resized();
}