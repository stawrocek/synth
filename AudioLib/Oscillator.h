#pragma once

#include <cmath>
#include <string>

#ifndef PI
#define PI  3.1415926535897932384626433832795
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

private:
	OscillatorType oscillatorType = OscillatorType::OscSin;
	double phase=0.0;
};
