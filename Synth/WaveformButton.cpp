#include "WaveformButton.h"

#include "Styles.h"

WaveformButton::WaveformButton(const String& name, OscillatorType oscType_, int radioGroupId)
:ShapeButton(name, oscNormalShapeColour, oscOverShapeColour, oscDownShapeColour), oscType(oscType_)
{
	setOnColours(oscActivatedShapeColour, oscOverShapeColour, oscDownShapeColour);
	shouldUseOnColours(true);
	setClickingTogglesState(true);
	setRadioGroupId(radioGroupId);
	generateShape();
}

void WaveformButton::paint(juce::Graphics& graphics) {
	auto area = getLocalBounds();
	auto h = area.getHeight();
	auto w = area.getWidth();

	graphics.setColour(componentBorderColour);
	graphics.drawRect(area.getX(), area.getY(), w, h, 1);

	ShapeButton::paint(graphics);
}

void WaveformButton::generateShape() {
	float step = 0.025;

	juce::Path path;

	if (oscType == OscillatorType::OscSin) {
		for (double iter = -1.0; iter < 1.0; iter += step) {
			float y1 = sin(iter * 2.0 * PI);
			float y2 = sin((iter + step) * 2.0 * PI);
			path.addLineSegment(juce::Line<float>(iter, y1, iter + step, y2), 0.05);
		}
	}

	if (oscType == OscillatorType::OscSquare) {
		path.addLineSegment(juce::Line<float>(-1, 1, -0.5, 1), 0.05);
		path.addLineSegment(juce::Line<float>(-0.5, 1, -0.5, -1), 0.05);
		path.addLineSegment(juce::Line<float>(-0.5, -1, 0, -1), 0.05);
		path.addLineSegment(juce::Line<float>(0, -1, 0, 1), 0.05);
		path.addLineSegment(juce::Line<float>(0, 1, 0.5, 1), 0.05);
		path.addLineSegment(juce::Line<float>(0.5, 1, 0.5, -1), 0.05);
		path.addLineSegment(juce::Line<float>(0.5, -1, 1, -1), 0.05);
	}
	if (oscType == OscillatorType::OscTriangle) {
		path.addLineSegment(juce::Line<float>(-1, 1, -0.5, -1), 0.05);
		path.addLineSegment(juce::Line<float>(-0.5, -1, 0, 1), 0.05);
		path.addLineSegment(juce::Line<float>(0, 1, 0.5, -1), 0.05);
		path.addLineSegment(juce::Line<float>(0.5, -1, 1, 1), 0.05);
	}

	if (oscType == OscillatorType::OscSawtooth) {
		path.addLineSegment(juce::Line<float>(-1, 1, 0, -1), 0.05);
		path.addLineSegment(juce::Line<float>(0, -1, 0,  1), 0.05);
		path.addLineSegment(juce::Line<float>(0,  1, 1, -1), 0.05);
	}
	setShape(path, false, true, true);
}

