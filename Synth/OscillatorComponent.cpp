#include "OscillatorComponent.h"
#include "PluginEditor.h"

OscillatorComponent::OscillatorComponent(SynthAudioProcessor& processor_, int identifier)
	:processor(processor_), id(identifier),
	name("osc"+std::to_string(id)),
	btnOscSine("btn_sin_"+name, juce::Colours::orange, juce::Colours::yellow, juce::Colours::grey),
	btnOscRect("btn_rect_" + name, juce::Colours::orange, juce::Colours::yellow, juce::Colours::grey),
	btnOscTriangle("btn_triangle_" + name, juce::Colours::orange, juce::Colours::yellow, juce::Colours::grey),
	btnOscSawtooth("btn_sawtooth_" + name, juce::Colours::orange, juce::Colours::yellow, juce::Colours::grey)
{
	labelName.setText("osc"+std::to_string(id), juce::NotificationType::dontSendNotification);
	labelName.setJustificationType(juce::Justification::centred);
	labelName.setColour(juce::Label::backgroundColourId, juce::Colours::black);
	labelName.setColour(juce::Label::textColourId, juce::Colours::white);
	addAndMakeVisible(labelName);

	btnOscSine.addListener(this);
	btnOscRect.addListener(this);
	btnOscTriangle.addListener(this);
	btnOscSawtooth.addListener(this);
	generateOscillatorSelectionButtonsShapes();
	//btnOscSine.setOutline(juce::Colours::green, 1);
	addAndMakeVisible(btnOscSine);
	addAndMakeVisible(btnOscRect);
	addAndMakeVisible(btnOscTriangle);
	addAndMakeVisible(btnOscSawtooth);

	startTimer(100);
}

void OscillatorComponent::paint(juce::Graphics& g)
{
	g.setColour(juce::Colours::black);

	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	g.drawRect(0, 0, w, h, 2);
}

void OscillatorComponent::resized() {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();
	labelName.setBounds(0, 0, w, h * 0.1);

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

	gridWaves.performLayout(juce::Rectangle<int>(0, h*0.1, w*0.25, h*0.9));
}

void OscillatorComponent::buttonClicked(juce::Button* button) {
	if (button == &btnOscSine) {
		//processor.tree.getParameterAsValue("WAVEFORM"+std::to_string(id)).setValue(0);
		*processor.waveform_types[id - 1] = 0;
	}
	else if (button == &btnOscRect) {
		//processor.tree.getParameterAsValue("WAVEFORM"+std::to_string(id)).setValue(1);
		*processor.waveform_types[id - 1] = 1;
	}
	else if (button == &btnOscTriangle) {
		//processor.tree.getParameterAsValue("WAVEFORM"+std::to_string(id)).setValue(2);
		*processor.waveform_types[id - 1] = 2;
	}
	else if (button == &btnOscSawtooth) {
		//processor.tree.getParameterAsValue("WAVEFORM"+std::to_string(id)).setValue(3);
		*processor.waveform_types[id - 1] = 3;
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