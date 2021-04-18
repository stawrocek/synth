#include "Oscillator.h"

Oscillator::Oscillator()
	:phase(0)
{

}

double Oscillator::sampleRate = 44100;

double Oscillator::generateSinWave(double frequency) {
	double output = sin(phase * PI);
	if (phase >= 1.0) {
		phase -= 1.0;
	}
	phase += frequency / sampleRate;
	return output;
}


