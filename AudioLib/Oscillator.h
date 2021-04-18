#pragma once

#include <cmath>
#include <string>

#ifndef PI
#define PI  3.1415926535897932384626433832795
#endif

class Oscillator {
public:
	Oscillator();
	double generateSinWave(double freq);

	static double sampleRate;

private:
	double phase;
};
