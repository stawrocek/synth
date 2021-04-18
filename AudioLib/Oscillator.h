#pragma once

#include <cmath>
#include <string>

#ifndef PI
#define PI  3.1415926535897932384626433832795
#endif

class Oscillator {
public:
	Oscillator();
	double generateSinWave(double frequency);
	double generateSquareWave(double frequency);
	double generateTriangleWave(double frequency);
	double generateSawtoothWave(double frequency);

	static double sampleRate;

private:
	double phase;
};
