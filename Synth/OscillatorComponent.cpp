#include "OscillatorComponent.h"
#include "Styles.h"

OscillatorComponent::OscillatorComponent(SynthAudioProcessor& processor_, int identifier)
	:SynthComponent(processor_, "Oscillator " + std::to_string(identifier)), id(identifier),
	name("osc"+std::to_string(id)),
	btnOscSine("btn_sin_"+name, oscNormalShapeColour, oscOverShapeColour, oscDownShapeColour),
	btnOscRect("btn_rect_" + name, oscNormalShapeColour, oscOverShapeColour, oscDownShapeColour),
	btnOscTriangle("btn_triangle_" + name, oscNormalShapeColour, oscOverShapeColour, oscDownShapeColour),
	btnOscSawtooth("btn_sawtooth_" + name, oscNormalShapeColour, oscOverShapeColour, oscDownShapeColour)
{
	btnOscSine.addListener(this);
	btnOscRect.addListener(this);
	btnOscTriangle.addListener(this);
	btnOscSawtooth.addListener(this);
	generateOscillatorSelectionButtonsShapes();
	addAndMakeVisible(btnOscSine);
	addAndMakeVisible(btnOscRect);
	addAndMakeVisible(btnOscTriangle);
	addAndMakeVisible(btnOscSawtooth);

	sliderDetune.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderDetune.setRange(-100, 100.0, 1.0);
	sliderDetune.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderDetune.setTooltip("detune");
    sliderDetuneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "OSC"+std::to_string(id)+"DETUNE", sliderDetune);
	addAndMakeVisible(sliderDetune);

	sliderMix.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	sliderMix.setRange(0, 100.0, 1.0);
	sliderMix.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	sliderMix.setTooltip("mix");
	sliderMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "OSC" + std::to_string(id) + "MIX", sliderMix);
	addAndMakeVisible(sliderMix);

	startTimer(100);
}

void OscillatorComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	btnOscSine.setBorderSize(juce::BorderSize<int>(1));
	btnOscRect.setBorderSize(juce::BorderSize<int>(1));
	btnOscTriangle.setBorderSize(juce::BorderSize<int>(1));
	btnOscSawtooth.setBorderSize(juce::BorderSize<int>(1));

	juce::Grid gridWaves;
	
	using Track = juce::Grid::TrackInfo;
	using Fr = juce::Grid::Fr;

	gridWaves.templateRows = { Track(Fr(1)), Track(Fr(1)) };
	gridWaves.templateColumns = { Track(Fr(1)), Track(Fr(1)) };

	gridWaves.items = { juce::GridItem(btnOscSine), juce::GridItem(btnOscRect), 
		juce::GridItem(btnOscTriangle), juce::GridItem(btnOscSawtooth) };

	gridWaves.performLayout(juce::Rectangle<int>(0, 0, w*0.25, h));

	sliderDetune.setBounds(juce::Rectangle<int>(w*0.25, 0, w*0.25, h).reduced(3, 3));
	sliderMix.setBounds(juce::Rectangle<int>(w*0.5, 0, w*0.25, h).reduced(3, 3));
}

void OscillatorComponent::buttonClicked(juce::Button* button) {
	if (button == &btnOscSine) {
		processor.tree.getParameterAsValue("WAVEFORM"+std::to_string(id)).setValue(0);
	}
	else if (button == &btnOscRect) {
		processor.tree.getParameterAsValue("WAVEFORM"+std::to_string(id)).setValue(1);
	}
	else if (button == &btnOscTriangle) {
		processor.tree.getParameterAsValue("WAVEFORM"+std::to_string(id)).setValue(2);
	}
	else if (button == &btnOscSawtooth) {
		processor.tree.getParameterAsValue("WAVEFORM"+std::to_string(id)).setValue(3);
	}
}

void OscillatorComponent::generateOscillatorSelectionButtonsShapes() {
	float step = 0.025;

	juce::Path pSine;
	for (float iter = -1.0; iter < 1.0; iter += step) {
		float y1 = sin((iter + offsetSine) * 2.0 * PI);
		float y2 = sin((iter + step + offsetSine) * 2.0 * PI);
		pSine.addLineSegment(juce::Line<float>(iter, y1, iter+step, y2), 0.05);
	}
	btnOscSine.setShape(pSine, false, true, true);

	juce::Path pRect;
	for (float iter = -1.0; iter < 1.0; iter += step) {
		float x1 = iter;
		float x2 = iter + step;
		float y1 = -1.0;
		float y2 = -1.0;

		if (int(x1 + offsetRect) % 2 == 1 || int(x1 + offsetRect) % 2 == 0) {
			y1 = 1.0;
		}
		if (int(x2 + offsetRect) % 2 == 1 || int(x2 + offsetRect) % 2 == 0) {
			y2 = 1.0;
		}


		pRect.addLineSegment(juce::Line<float>(x1, y1, x2, y2), 0.05);
	}
	btnOscRect.setShape(pRect, false, true, true);
	
	juce::Path pTriangle;
	for (float iter = -1.0 + offsetTriangle; iter < 1.0 + offsetTriangle; iter += step) {
		float x = iter, x2 = iter+step;
		float y = -4.0 * x - 3.0;
		float y2 = -4.0 * x2 - 3.0;
		if (iter >= -0.5 && iter < 0.0) {
			y = 4.0 * x + 1.0;
			y2 = 4.0 * x2 + 1.0;
		}
		else if (iter >= 0 && iter < 0.5) {
			y = -4.0 * x + 1.0;
			y2 = -4.0 * x2 + 1.0;
		}
		else if (iter >= 0.5 && iter <= 1.0) {
			y = 4.0 * x - 3.0;
			y2 = 4.0 * x2 - 3.0;
		}
		pTriangle.addLineSegment(juce::Line<float>(x, y, x2, y2), 0.05);
	}
	btnOscTriangle.setShape(pTriangle, false, true, true);

	juce::Path pSaw;
	for (float iter = -1.0 + offsetSaw; iter < 1.0 + offsetSaw; iter += step) {
		float y1 = 2.0 * iter + 1.0;
		if(iter >= 0.0) 
			y1 = 2.0 * iter - 1.0;
		float i2 = iter + step;
		float y2 = 2.0 * i2 + 1.0;
		if (i2 >= 0.0) 
			y2 = 2.0*i2 - 1.0;
		pSaw.addLineSegment(juce::Line<float>(iter, y1, i2, y2), 0.05);
	}
	btnOscSawtooth.setShape(pSaw, false, true, true);
}


void OscillatorComponent::timerCallback()
{
	offsetSine += 0.1;
	offsetRect += 0.1;
	//offsetTriangle += 0.1;
	//offsetSaw += 0.1;
	if (offsetSine > 1.0) offsetSine -= 2.0;
	if (offsetRect > 1.0) offsetRect -= 2.0;
	if (offsetTriangle > 1.0) offsetTriangle -= 2.0;
	if (offsetSaw > 1.0) offsetSaw -= 2.0;
	generateOscillatorSelectionButtonsShapes();
}