#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class SynthComponent : public juce::GroupComponent
{
public:
	SynthComponent(SynthAudioProcessor& processor, const juce::String & name);

protected:
	SynthAudioProcessor& processor;
};



