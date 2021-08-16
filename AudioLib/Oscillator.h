#pragma once

#include <cmath>
#include <string>

#ifndef PI
#define PI  3.141592653589793
#endif

enum class OscillatorType {
	OscSin=0,
	OscSquare=1,
	OscTriangle=2,
	OscSawtooth=3
};

class Oscillator {
public:
	Oscillator();
	double generateSinWave(double frequency);
	double generateSquareWave(double frequency);
	double generateTriangleWave(double frequency);
	double generateSawtoothWave(double frequency);

	double generateWave(double frequency);
	static double sampleRate;

	OscillatorType getType();
	void setType(OscillatorType oscType);

	double getPhase();
	void setPhase(double phase_);
	double getDetune();
	void setDetune(double detune_);

private:
	OscillatorType oscillatorType = OscillatorType::OscSin;
	double phase = 0.0;
	double detune = 0.0;
};
