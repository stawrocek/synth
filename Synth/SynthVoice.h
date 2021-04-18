#pragma once

#include <JuceHeader.h>

#include "SynthSound.h"
#include "Oscillator.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
	bool canPlaySound(juce::SynthesiserSound* sound) override
	{
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}

	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
		int currentPitchWheelPosition) override
	{
		level = velocity;
		frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	}

	void stopNote(float velocity, bool allowTailoff) override
	{
		if (velocity < 0.00001 && allowTailoff == false)
		//if (velocity < 0.00001)
			clearCurrentNote();
		level = 0;
	}

	void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
	{
		for (int sample = 0; sample < numSamples; sample++)
		{
			double signal = 0.0;
			if(oscillatorType == 0)
				signal = osc1.generateSinWave(frequency) * level;
			else if(oscillatorType == 1)
				signal = osc1.generateSquareWave(frequency) * level;
			else if (oscillatorType == 2)
				signal = osc1.generateTriangleWave(frequency) * level;
			else if (oscillatorType == 3)
				signal = osc1.generateSawtoothWave(frequency) * level;

			for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
			{
				outputBuffer.addSample(channel, startSample, signal);
			}

			++startSample;
		}
	}

	void pitchWheelMoved(int newPitchWheel) override
	{

	}

	void controllerMoved(int controllerNumber, int newControllerValue) override
	{

	}

	void setOscillator(int oscillatorIndex) {
		oscillatorType = oscillatorIndex;
	}

private:
	double level;
	double frequency;
	int oscillatorType = 0;
	Oscillator osc1;
};