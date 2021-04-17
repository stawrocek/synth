#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {

public:
	bool appliesToNote(int /*midi*/) override {
		return true;
	}

	bool appliesToChannel(int /*midi_channel*/) override {
		return true;
	}
};