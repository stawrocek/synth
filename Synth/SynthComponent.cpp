#include "SynthComponent.h"

#include "Config.h"
#include "Styles.h"

SynthComponent::SynthComponent(SynthAudioProcessor& processor_, const juce::String& name)
	:processor(processor_)
{
	setText(name);
	setTextLabelPosition(juce::Justification::topLeft);
}