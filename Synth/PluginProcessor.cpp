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
		std::make_unique<juce::AudioParameterFloat>(filterCutoffParamId, filterCutoffParamName, 20, 1000, filterInitialCutoff),
		std::make_unique<juce::AudioParameterFloat>(filterResonanceParamId, filterResonanceParamName, 0.1, 10, filterInitialResonance),
		std::make_unique<juce::AudioParameterInt>(filterTypeParamId, filterTypeParamName, 0, 1, 0),
		std::make_unique<juce::AudioParameterFloat>(reverbRoomSizeParamId, reverbRoomSizeParamName, 0, 1, reverbInitialRoomSize),
		std::make_unique<juce::AudioParameterFloat>(reverbDampingParamId, reverbDampingParamName, 0, 1, reverbInitialDamping),
		std::make_unique<juce::AudioParameterFloat>(reverbWetLevelParamId, reverbWetLevelParamName, 0, 1, reverbInitialWetLevel),
		std::make_unique<juce::AudioParameterFloat>(reverbWidthParamId, reverbWidthParamName, 0, 1, reverbInitialWidth),
		std::make_unique<juce::AudioParameterFloat>(reverbFreezeModeParamId, reverbFreezeModeParamName, 0, 1, reverbInitialFreezeMode),
		std::make_unique<juce::AudioParameterInt>(lfoWaveformTypeParamId, lfoWaveformTypeParamName, 0, 3, 0),
		std::make_unique<juce::AudioParameterFloat>(lfoRateParamId, lfoRateParamName, 0.1, 5, lfoInitialRate),
		std::make_unique<juce::AudioParameterFloat>(lfoIntensityParamId, lfoIntensityParamName, 0.01, 2.0, lfoInitialIntensity),
		std::make_unique<juce::AudioParameterBool>(lfoTarget1ActiveParamId, lfoTarget1ActiveParamName, false),
		std::make_unique<juce::AudioParameterBool>(lfoTarget2ActiveParamId, lfoTarget2ActiveParamName, false),
		std::make_unique<juce::AudioParameterBool>(lfoTarget3ActiveParamId, lfoTarget3ActiveParamName, false),
		std::make_unique<juce::AudioParameterBool>(osc1EnabledParamId, osc1EnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(osc2EnabledParamId, osc2EnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(osc3EnabledParamId, osc3EnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(adsrEnabledParamId, adsrEnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(filterEnabledParamId, filterEnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(reverbEnabledParamId, reverbEnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(lfoEnabledParamId, lfoEnabledParamName, true)
	})
#endif
{
	synth.clearVoices();
	for (int i = 0; i < 5; i++) {
		voices.push_back(new SynthVoice());
		synth.addVoice(voices.back());
	}
	synth.clearSounds();
	synth.addSound(new SynthSound());
}

SynthAudioProcessor::~SynthAudioProcessor() {

}

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

void SynthAudioProcessor::prepareToPlay (double sampleRate_, int samplesPerBlock)
{
	sampleRate = sampleRate_;
	juce::ignoreUnused(samplesPerBlock);

	juce::dsp::ProcessSpec spec;

	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = 1;
	leftReverb.prepare(spec);
	rightReverb.prepare(spec);
	
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
	if (tree.getParameterAsValue(reverbEnabledParamId).getValue()) {
		reverbParams.roomSize = tree.getParameterAsValue(reverbRoomSizeParamId).getValue();
		reverbParams.damping = tree.getParameterAsValue(reverbDampingParamId).getValue();
		reverbParams.wetLevel = tree.getParameterAsValue(reverbWetLevelParamId).getValue();
		reverbParams.dryLevel = 1.0 - (float)tree.getParameterAsValue(reverbWetLevelParamId).getValue();
		reverbParams.width = tree.getParameterAsValue(reverbWidthParamId).getValue();
		reverbParams.freezeMode = tree.getParameterAsValue(reverbFreezeModeParamId).getValue();

		leftReverb.setParameters(reverbParams);
		rightReverb.setParameters(reverbParams);
	}
	if (tree.getParameterAsValue(filterEnabledParamId).getValue()) {
		float filterCutoff = tree.getParameterAsValue(filterCutoffParamId).getValue();
		float filterResonance = tree.getParameterAsValue(filterResonanceParamId).getValue();

		if (((FilterType)(int)tree.getParameterAsValue(filterTypeParamId).getValue() == FilterType::LowPassFilter)) {
			filterCoefficients = IIRCoefficients::makeLowPass(sampleRate, filterCutoff, filterResonance);
		}
		else if (((FilterType)(int)tree.getParameterAsValue(filterTypeParamId).getValue() == FilterType::HighPassFilter)) {
			filterCoefficients = IIRCoefficients::makeHighPass(sampleRate, filterCutoff, filterResonance);
		}

		filterLeft.setCoefficients(filterCoefficients);
		filterRight.setCoefficients(filterCoefficients);
	}
	for(int i = 0; i < synth.getNumVoices(); i++) {
		SynthVoice* synthVoice;
		if ((synthVoice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))) {
			synthVoice->setOscillator(static_cast<OscillatorType>((int)*tree.getRawParameterValue(osc1WaveTypeParamId)), 1);
			synthVoice->setOscillator(static_cast<OscillatorType>((int)*tree.getRawParameterValue(osc2WaveTypeParamId)), 2);
			synthVoice->setOscillator(static_cast<OscillatorType>((int)*tree.getRawParameterValue(osc3WaveTypeParamId)), 3);
			synthVoice->setDetune((int)*tree.getRawParameterValue(osc1DetuneParamId), 1);
			synthVoice->setDetune((int)*tree.getRawParameterValue(osc2DetuneParamId), 2);
			synthVoice->setDetune((int)*tree.getRawParameterValue(osc3DetuneParamId), 3);
			synthVoice->setMix((int)*tree.getRawParameterValue(osc1MixParamId), 1);
			synthVoice->setMix((int)*tree.getRawParameterValue(osc2MixParamId), 2);
			synthVoice->setMix((int)*tree.getRawParameterValue(osc3MixParamId), 3);
			synthVoice->setAdsrAttack(tree.getParameterAsValue(adsrAttackParamId).getValue());
			synthVoice->setAdsrDecay(tree.getParameterAsValue(adsrDecayParamId).getValue());
			synthVoice->setAdsrSustain(tree.getParameterAsValue(adsrSustainParamId).getValue());
			synthVoice->setAdsrRelease(tree.getParameterAsValue(adsrReleaseParamId).getValue());
			synthVoice->setOscEnabled(tree.getParameterAsValue(osc1EnabledParamId).getValue(), 1);
			synthVoice->setOscEnabled(tree.getParameterAsValue(osc2EnabledParamId).getValue(), 2);
			synthVoice->setOscEnabled(tree.getParameterAsValue(osc3EnabledParamId).getValue(), 3);
			synthVoice->setADSREnabled(tree.getParameterAsValue(adsrEnabledParamId).getValue());
		}
	}

	midiMessageCollector.removeNextBlockOfMessages(midiMessages, buffer.getNumSamples());

	buffer.clear();
	int numSamples = buffer.getNumSamples();
	synth.renderNextBlock(buffer, midiMessages, 0, numSamples);

	if (tree.getParameterAsValue(filterEnabledParamId).getValue()) {
		float* dataLeft = buffer.getWritePointer(0);
		float* dataRight = buffer.getWritePointer(1);

		filterLeft.processSamples(dataLeft, numSamples);
		filterRight.processSamples(dataRight, numSamples);
	}

	if (tree.getParameterAsValue(reverbEnabledParamId).getValue()) {
		juce::dsp::AudioBlock<float> block(buffer);

		auto leftBlock = block.getSingleChannelBlock(0);
		auto rightBlock = block.getSingleChannelBlock(1);

		juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
		juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

		leftReverb.process(leftContext);
		rightReverb.process(rightContext);
	}
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

// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}

