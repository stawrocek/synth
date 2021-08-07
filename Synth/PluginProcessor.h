#pragma once

#include <JuceHeader.h>

#include "SynthSound.h"
#include "SynthVoice.h"
#include "AudioBufferQueue.h"
#include "ScopeDataCollector.h"

class SynthAudioProcessor  : public juce::AudioProcessor,
							 public AudioProcessorValueTreeState::Listener
{
public:
    SynthAudioProcessor();
    ~SynthAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void parameterChanged(const String& parameterID, float newValue) override;

	AudioProcessorValueTreeState tree;
	juce::MidiMessageCollector midiMessageCollector;
	AudioBufferQueue<float> audioBufferQueue;
	ScopeDataCollector<float> scopeDataCollector{ audioBufferQueue };

private:
	juce::Synthesiser synth;
	
	std::vector<SynthVoice*> voices;

	juce::dsp::Reverb leftReverb;
	juce::dsp::Reverb rightReverb;
	juce::Reverb::Parameters reverbParams;
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessor)
};
