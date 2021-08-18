#pragma once

#include <cmath>

#ifndef PI
#define PI  3.141592653589793
#endif

enum class DistortionType {
	SoftClippingAtan = 0,
	HardClipping = 1
};

class Distortion {
public:
	void setType(DistortionType distortionType);
	void setGain(float gain);
	void setWetLevel(float mix);

	float processSingleSample(float sample);

private:
	DistortionType distortionType = DistortionType::SoftClippingAtan;
	float gain = 0.5, wetLevel = 0.0;
};