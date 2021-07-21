#pragma once

#include <JuceHeader.h>
#include "OscillatorComponent.h"
#include "PluginProcessor.h"
#include "ScopeComponent.h"

class SynthAudioProcessorEditor  : public juce::AudioProcessorEditor,
								   private juce::Slider::Listener
{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	void sliderValueChanged(juce::Slider* slider) override;

    SynthAudioProcessor& audioProcessor;
	//juce::Slider midiVolume;
	//juce::ComboBox waveformBox;
	juce::MidiKeyboardState midiKeyboardState;
	juce::MidiKeyboardComponent midiKeyboardComponent{ midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard };
	ScopeComponent<float> scopeComponent;
	OscillatorComponent osc1Component;
	OscillatorComponent osc2Component;
	OscillatorComponent osc3Component;

	//std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveformBoxAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};
