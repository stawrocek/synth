#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <vector>
#include <memory>

#include "Config.h"

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
		std::make_unique<juce::AudioParameterInt>(osc1WaveTypeParamId, osc1WaveTypeParamName, 0, 3, 0),
		std::make_unique<juce::AudioParameterInt>(osc2WaveTypeParamId, osc2WaveTypeParamName, 0, 3, 0),
		std::make_unique<juce::AudioParameterInt>(osc3WaveTypeParamId, osc3WaveTypeParamName, 0, 3, 0),
		std::make_unique<juce::AudioParameterInt>(osc1DetuneParamId, osc1DetuneParamName, -100, 100, 0),
		std::make_unique<juce::AudioParameterInt>(osc2DetuneParamId, osc2DetuneParamName, -100, 100, 0),
		std::make_unique<juce::AudioParameterInt>(osc3DetuneParamId, osc3DetuneParamName, -100, 100, 0),
		std::make_unique<juce::AudioParameterInt>(osc1MixParamId, osc1MixParamName, 0, 100, 100),
		std::make_unique<juce::AudioParameterInt>(osc2MixParamId, osc2MixParamName, 0, 100, 100),
		std::make_unique<juce::AudioParameterInt>(osc3MixParamId, osc3MixParamName, 0, 100, 100),
		std::make_unique<juce::AudioParameterFloat>(adsrAttackParamId, adsrAttackParamName, 0, 5, adsrInitialAttack),
		std::make_unique<juce::AudioParameterFloat>(adsrDecayParamId, adsrDecayParamName, 0, 2, adsrInitialDecay),
		std::make_unique<juce::AudioParameterFloat>(adsrSustainParamId, adsrSustainParamName, 0, 1, adsrInitialSustain),
		std::make_unique<juce::AudioParameterFloat>(adsrReleaseParamId, adsrReleaseParamName, 0, 2, adsrInitialRelease),
		std::make_unique<juce::AudioParameterFloat>(filterCutoffParamId, filterCutoffParamName, 0, 2, filterInitialCutoff),
		std::make_unique<juce::AudioParameterFloat>(filterResonanceParamId, filterResonanceParamName, 0, 2, filterInitialResonance)
		
	})
#endif
{
	tree.addParameterListener(osc1WaveTypeParamId, this);
	tree.addParameterListener(osc2WaveTypeParamId, this);
	tree.addParameterListener(osc3WaveTypeParamId, this);
	tree.addParameterListener(osc1DetuneParamId, this);
	tree.addParameterListener(osc2DetuneParamId, this);
	tree.addParameterListener(osc3DetuneParamId, this);
	tree.addParameterListener(osc1MixParamId, this);
	tree.addParameterListener(osc2MixParamId, this);
	tree.addParameterListener(osc3MixParamId, this);
	tree.addParameterListener(adsrAttackParamId, this);
	tree.addParameterListener(adsrDecayParamId, this);
	tree.addParameterListener(adsrSustainParamId, this);
	tree.addParameterListener(adsrReleaseParamId, this);

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
	synth.setCurrentPlaybackSampleRate(sampleRate);
	midiMessageCollector.reset(sampleRate);
	for (SynthVoice* synthVoice : voices)
		synthVoice->setSampleRate(sampleRate);
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
	//for (SynthVoice* synthVoice : voices) {
	for(int i = 0; i < synth.getNumVoices(); i++) {
		SynthVoice* synthVoice;
		if ((synthVoice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))) {
			synthVoice->setAdsrAttack(tree.getParameterAsValue(adsrAttackParamId).getValue());
				synthVoice->setAdsrDecay(tree.getParameterAsValue(adsrDecayParamId).getValue());
				synthVoice->setAdsrSustain(tree.getParameterAsValue(adsrSustainParamId).getValue());
				synthVoice->setAdsrRelease(tree.getParameterAsValue(adsrReleaseParamId).getValue());
				synthVoice->setDetune((int)*tree.getRawParameterValue(osc1DetuneParamId), 1);
				synthVoice->setDetune((int)*tree.getRawParameterValue(osc2DetuneParamId), 2);
				synthVoice->setDetune((int)*tree.getRawParameterValue(osc3DetuneParamId), 3);
				synthVoice->setMix((int)*tree.getRawParameterValue(osc1MixParamId), 1);
				synthVoice->setMix((int)*tree.getRawParameterValue(osc2MixParamId), 2);
				synthVoice->setMix((int)*tree.getRawParameterValue(osc3MixParamId), 3);
		}
	}

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
		if (parameterID == osc1WaveTypeParamId)
			synthVoice->setOscillator(static_cast<OscillatorType>((int)*tree.getRawParameterValue(osc1WaveTypeParamId)), 1);
		else if (parameterID == osc2WaveTypeParamId)
			synthVoice->setOscillator(static_cast<OscillatorType>((int)*tree.getRawParameterValue(osc2WaveTypeParamId)), 2);
		else if (parameterID == osc3WaveTypeParamId)
			synthVoice->setOscillator(static_cast<OscillatorType>((int)*tree.getRawParameterValue(osc3WaveTypeParamId)), 3);
		/*else if (parameterID == osc1DetuneParamId)
			synthVoice->setDetune((int)*tree.getRawParameterValue(osc1DetuneParamId), 1);
		else if (parameterID == osc2DetuneParamId)
			synthVoice->setDetune((int)*tree.getRawParameterValue(osc2DetuneParamId), 2);
		else if (parameterID == osc3DetuneParamId)
			synthVoice->setDetune((int)*tree.getRawParameterValue(osc3DetuneParamId), 3);
		else if (parameterID == osc1MixParamId)
			synthVoice->setMix((int)*tree.getRawParameterValue(osc1MixParamId), 1);
		else if (parameterID == osc2MixParamId)
			synthVoice->setMix((int)*tree.getRawParameterValue(osc2MixParamId), 2);
		else if (parameterID == osc3MixParamId)
			synthVoice->setMix((int)*tree.getRawParameterValue(osc3MixParamId), 3);
		
		else if (parameterID == adsrAttackParamId)
			synthVoice->setAdsrAttack(tree.getParameterAsValue(adsrAttackParamId).getValue());
		else if (parameterID == adsrDecayParamId)
			synthVoice->setAdsrDecay(tree.getParameterAsValue(adsrDecayParamId).getValue());
		else if (parameterID == adsrSustainParamId)
			synthVoice->setAdsrSustain(tree.getParameterAsValue(adsrSustainParamId).getValue());
		else if (parameterID == adsrReleaseParamId)
			synthVoice->setAdsrRelease(tree.getParameterAsValue(adsrReleaseParamId).getValue());
			*/
	}
}

// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}

