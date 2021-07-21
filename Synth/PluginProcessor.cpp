#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <vector>
#include <memory>

SynthAudioProcessor::SynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	), tree(*this, nullptr, "SynthAudioProcessorParameters", {
		std::make_unique<juce::AudioParameterInt>("WAVEFORM1", "waveform1", 0, 3, 0),
		std::make_unique<juce::AudioParameterInt>("WAVEFORM2", "waveform2", 0, 3, 0),
		std::make_unique<juce::AudioParameterInt>("WAVEFORM3", "waveform3", 0, 3, 0),
		std::make_unique<juce::AudioParameterInt>("OSC1DETUNE", "osc1detune", -100, 100, 0),
		std::make_unique<juce::AudioParameterInt>("OSC2DETUNE", "osc2detune", -100, 100, 0),
		std::make_unique<juce::AudioParameterInt>("OSC3DETUNE", "osc3detune", -100, 100, 0)
		
	})
#endif
{
	tree.addParameterListener("WAVEFORM1", this);
	tree.addParameterListener("WAVEFORM2", this);
	tree.addParameterListener("WAVEFORM3", this);
	tree.addParameterListener("OSC1DETUNE", this);
	tree.addParameterListener("OSC2DETUNE", this);
	tree.addParameterListener("OSC3DETUNE", this);

	synth.clearVoices();
	for (int i = 0; i < 5; i++) {
		voices.push_back(new SynthVoice());
		synth.addVoice(voices.back());
	}
	synth.clearSounds();
	synth.addSound(new SynthSound());
}

SynthAudioProcessor::~SynthAudioProcessor() {}

const juce::String SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void SynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	juce::ignoreUnused(samplesPerBlock);
	lastSampleRate = sampleRate;
	synth.setCurrentPlaybackSampleRate(lastSampleRate);
	midiMessageCollector.reset(sampleRate);
}

void SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	midiMessageCollector.removeNextBlockOfMessages(midiMessages, buffer.getNumSamples());

	buffer.clear();
	int numSamples = buffer.getNumSamples();
	synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
	scopeDataCollector.process(buffer.getReadPointer(0), (size_t)buffer.getNumSamples());
}

bool SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthAudioProcessor::createEditor()
{
    return new SynthAudioProcessorEditor (*this);
}

void SynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void SynthAudioProcessor::parameterChanged(const String& parameterID, float newValue) {
	for (SynthVoice* synthVoice : voices) {
		if (parameterID == "WAVEFORM1")
			synthVoice->setOscillator(static_cast<OscillatorType>((int)*tree.getRawParameterValue("WAVEFORM1")), 1);
		else if (parameterID == "WAVEFORM2")
			synthVoice->setOscillator(static_cast<OscillatorType>((int)*tree.getRawParameterValue("WAVEFORM2")), 2);
		else if (parameterID == "WAVEFORM3")
			synthVoice->setOscillator(static_cast<OscillatorType>((int)*tree.getRawParameterValue("WAVEFORM3")), 3);
		else if (parameterID == "OSC1DETUNE")
			synthVoice->setDetune((int)*tree.getRawParameterValue("OSC1DETUNE"), 1);
		else if (parameterID == "OSC2DETUNE")
			synthVoice->setDetune((int)*tree.getRawParameterValue("OSC2DETUNE"), 2);
		else if (parameterID == "OSC3DETUNE")
			synthVoice->setDetune((int)*tree.getRawParameterValue("OSC3DETUNE"), 3);
	}
}

// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}

