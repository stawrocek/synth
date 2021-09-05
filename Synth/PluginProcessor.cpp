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
		std::make_unique<juce::AudioParameterInt>(osc1DetuneStepsParamId, osc1DetuneStepsParamName, -12, 12, 0),
		std::make_unique<juce::AudioParameterInt>(osc2DetuneStepsParamId, osc2DetuneStepsParamName, -12, 12, 0),
		std::make_unique<juce::AudioParameterInt>(osc3DetuneStepsParamId, osc3DetuneStepsParamName, -12, 12, 0),
		std::make_unique<juce::AudioParameterInt>(osc1MixParamId, osc1MixParamName, 0, 100, 100),
		std::make_unique<juce::AudioParameterInt>(osc2MixParamId, osc2MixParamName, 0, 100, 100),
		std::make_unique<juce::AudioParameterInt>(osc3MixParamId, osc3MixParamName, 0, 100, 100),
		
		std::make_unique<juce::AudioParameterFloat>(adsrAttackParamId, adsrAttackParamName, 0, 5, adsrInitialAttack),
		std::make_unique<juce::AudioParameterFloat>(adsrDecayParamId, adsrDecayParamName, 0, 2, adsrInitialDecay),
		std::make_unique<juce::AudioParameterFloat>(adsrSustainParamId, adsrSustainParamName, 0, 1, adsrInitialSustain),
		std::make_unique<juce::AudioParameterFloat>(adsrReleaseParamId, adsrReleaseParamName, 0, 2, adsrInitialRelease),
		
		std::make_unique<juce::AudioParameterFloat>(filterCutoffParamId, filterCutoffParamName, 20, 1000, filterInitialCutoff),
		std::make_unique<juce::AudioParameterFloat>(filterResonanceParamId, filterResonanceParamName, 0.1, 10, filterInitialResonance),
		std::make_unique<juce::AudioParameterInt>(filterTypeParamId, filterTypeParamName, 0, 1, (int)filterInitialType),
		
		std::make_unique<juce::AudioParameterFloat>(ampGainParamId, ampGainParamName, 0.01, 10, ampInitialGain),
		std::make_unique<juce::AudioParameterFloat>(ampWetLevelParamId, ampWetLevelParamName, 0, 1, ampInitialWetLevel),
		std::make_unique<juce::AudioParameterFloat>(ampVolumeParamId, ampVolumeParamName, 0, 1, ampInitialVolume),
		std::make_unique<juce::AudioParameterInt>(ampDistortionTypeParamId, ampDistortionTypeParamName, 0, 1, 0),
		
		std::make_unique<juce::AudioParameterFloat>(delayTimeParamId, delayTimeParamName, 0.01, 4.0, delayInitialTime),
		std::make_unique<juce::AudioParameterFloat>(delayWetLevelParamId, delayWetLevelParamName, 0.0, 1.0, delayInitialWetLevel),
		std::make_unique<juce::AudioParameterFloat>(delayFeedbackParamId, delayFeedbackParamName, 0.0, 1.0, delayInitialFeedback),
		std::make_unique<juce::AudioParameterFloat>(delayFilterParamId, delayFilterParamName, 20.0, 2000.0, delayInitialFilter),
		std::make_unique<juce::AudioParameterBool>(delayTailoffParamId, delayTailoffParamName, delayInitialTailoff),
		std::make_unique<juce::AudioParameterInt>(delayFilterTypeParamId, delayFilterTypeParamName, 0, 1, (int)delayFilterInitialType),

		std::make_unique<juce::AudioParameterFloat>(reverbRoomSizeParamId, reverbRoomSizeParamName, 0, 1, reverbInitialRoomSize),
		std::make_unique<juce::AudioParameterFloat>(reverbDampingParamId, reverbDampingParamName, 0, 1, reverbInitialDamping),
		std::make_unique<juce::AudioParameterFloat>(reverbWetLevelParamId, reverbWetLevelParamName, 0, 1, reverbInitialWetLevel),
		std::make_unique<juce::AudioParameterFloat>(reverbWidthParamId, reverbWidthParamName, 0, 1, reverbInitialWidth),
		std::make_unique<juce::AudioParameterBool>(reverbFreezeModeParamId, reverbFreezeModeParamName, reverbInitialFreezeMode),
		
		std::make_unique<juce::AudioParameterInt>(lfoWaveformTypeParamId, lfoWaveformTypeParamName, 0, 3, 0),
		std::make_unique<juce::AudioParameterFloat>(lfoRateParamId, lfoRateParamName, 0.1, 10, lfoInitialRate),
		std::make_unique<juce::AudioParameterFloat>(lfoIntensityParamId, lfoIntensityParamName, 0.01, 1.0, lfoInitialIntensity),
		std::make_unique<juce::AudioParameterBool>(lfoTarget1ActiveParamId, lfoTarget1ActiveParamName, false),
		std::make_unique<juce::AudioParameterBool>(lfoTarget2ActiveParamId, lfoTarget2ActiveParamName, false),
		std::make_unique<juce::AudioParameterBool>(lfoTarget3ActiveParamId, lfoTarget3ActiveParamName, false),
		
		std::make_unique<juce::AudioParameterBool>(osc1EnabledParamId, osc1EnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(osc2EnabledParamId, osc2EnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(osc3EnabledParamId, osc3EnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(adsrEnabledParamId, adsrEnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(filterEnabledParamId, filterEnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(reverbEnabledParamId, reverbEnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(lfoEnabledParamId, lfoEnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(ampEnabledParamId, ampEnabledParamName, true),
		std::make_unique<juce::AudioParameterBool>(delayEnabledParamId, delayEnabledParamName, true)
	})
#endif
{
	synth.clearVoices();
	for (int i = 0; i < 16; i++) {
		voices.push_back(new SynthVoice());
		synth.addVoice(voices.back());
	}
	synth.clearSounds();
	synth.addSound(new SynthSound());
}

SynthAudioProcessor::~SynthAudioProcessor() {

}

const juce::String SynthAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool SynthAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::isMidiEffect() const {
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms() {
    return 1;
}

int SynthAudioProcessor::getCurrentProgram() {
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index) {
}

const juce::String SynthAudioProcessor::getProgramName (int index) {
    return {};
}

void SynthAudioProcessor::changeProgramName (int index, const juce::String& newName) {
}

void SynthAudioProcessor::prepareToPlay (double sampleRate_, int samplesPerBlock) {
	sampleRate = sampleRate_;
	Oscillator::sampleRate = sampleRate;

	juce::dsp::ProcessSpec specDelay;
	specDelay.sampleRate = sampleRate;
	specDelay.maximumBlockSize = samplesPerBlock;
	specDelay.numChannels = 2;
	delay.prepare(specDelay);
	if (tree.getParameterAsValue(reverbEnabledParamId).getValue()) {
		juce::dsp::ProcessSpec specReverb;
		specReverb.sampleRate = sampleRate;
		specReverb.maximumBlockSize = samplesPerBlock;
		specReverb.numChannels = 1;

		leftReverb.prepare(specReverb);
		rightReverb.prepare(specReverb);
	}
	synth.setCurrentPlaybackSampleRate(sampleRate);
	midiMessageCollector.reset(sampleRate);
	for (SynthVoice* synthVoice : voices)
		synthVoice->setSampleRate(sampleRate);
}

void SynthAudioProcessor::releaseResources() {

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
	if (tree.getParameterAsValue(reverbEnabledParamId).getValue()) {
		reverbParams.roomSize = tree.getParameterAsValue(reverbRoomSizeParamId).getValue();
		reverbParams.damping = tree.getParameterAsValue(reverbDampingParamId).getValue();
		reverbParams.wetLevel = tree.getParameterAsValue(reverbWetLevelParamId).getValue();
		reverbParams.dryLevel = 1.0 - (float)tree.getParameterAsValue(reverbWetLevelParamId).getValue();
		reverbParams.width = tree.getParameterAsValue(reverbWidthParamId).getValue();
		reverbParams.freezeMode = (float)tree.getParameterAsValue(reverbFreezeModeParamId).getValue();

		leftReverb.setParameters(reverbParams);
		rightReverb.setParameters(reverbParams);
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
			synthVoice->setSemitone((int)*tree.getRawParameterValue(osc1DetuneStepsParamId), 1);
			synthVoice->setSemitone((int)*tree.getRawParameterValue(osc2DetuneStepsParamId), 2);
			synthVoice->setSemitone((int)*tree.getRawParameterValue(osc3DetuneStepsParamId), 3);
			synthVoice->setMix((int)*tree.getRawParameterValue(osc1MixParamId), 1);
			synthVoice->setMix((int)*tree.getRawParameterValue(osc2MixParamId), 2);
			synthVoice->setMix((int)*tree.getRawParameterValue(osc3MixParamId), 3);
			synthVoice->setAdsrAttack(tree.getParameterAsValue(adsrAttackParamId).getValue());
			synthVoice->setAdsrDecay(tree.getParameterAsValue(adsrDecayParamId).getValue());
			synthVoice->setAdsrSustain(tree.getParameterAsValue(adsrSustainParamId).getValue());
			synthVoice->setAdsrRelease(tree.getParameterAsValue(adsrReleaseParamId).getValue());
			synthVoice->setFilterCutoff(tree.getParameterAsValue(filterCutoffParamId).getValue());
			synthVoice->setFilterResonance(tree.getParameterAsValue(filterResonanceParamId).getValue());
			synthVoice->setFilterType((FilterType)(int)tree.getParameterAsValue(filterTypeParamId).getValue());
			synthVoice->setDistortionGain(tree.getParameterAsValue(ampGainParamId).getValue());
			synthVoice->setDistortionWetLevel(tree.getParameterAsValue(ampWetLevelParamId).getValue());
			synthVoice->setDistortionType((DistortionType)(int)tree.getParameterAsValue(ampDistortionTypeParamId).getValue());
			synthVoice->setLFORate(tree.getParameterAsValue(lfoRateParamId).getValue());
			synthVoice->setLFOIntensity(tree.getParameterAsValue(lfoIntensityParamId).getValue());
			synthVoice->setLFOWavetype(static_cast<OscillatorType>((int)*tree.getRawParameterValue(lfoWaveformTypeParamId)));
			synthVoice->setLFOTargetCutoff(tree.getParameterAsValue(lfoTarget1ActiveParamId).getValue());
			synthVoice->setLFOTargetDetune(tree.getParameterAsValue(lfoTarget2ActiveParamId).getValue());
			synthVoice->setLFOTargetVolume(tree.getParameterAsValue(lfoTarget3ActiveParamId).getValue());
			synthVoice->setOscEnabled(tree.getParameterAsValue(osc1EnabledParamId).getValue(), 1);
			synthVoice->setOscEnabled(tree.getParameterAsValue(osc2EnabledParamId).getValue(), 2);
			synthVoice->setOscEnabled(tree.getParameterAsValue(osc3EnabledParamId).getValue(), 3);
			synthVoice->setADSREnabled(tree.getParameterAsValue(adsrEnabledParamId).getValue());
			synthVoice->setLFOEnabled(tree.getParameterAsValue(lfoEnabledParamId).getValue());
			synthVoice->setFilterEnabled(tree.getParameterAsValue(filterEnabledParamId).getValue());
			synthVoice->setAmpEnabled(tree.getParameterAsValue(ampEnabledParamId).getValue());
		}
	}

	midiMessageCollector.removeNextBlockOfMessages(midiMessages, buffer.getNumSamples());

	buffer.clear();
	int numSamples = buffer.getNumSamples();
	synth.renderNextBlock(buffer, midiMessages, 0, numSamples);

	delay.setDelayTime(tree.getParameterAsValue(delayTimeParamId).getValue());
	delay.setFeedback(tree.getParameterAsValue(delayFeedbackParamId).getValue());
	delay.setFilter((float)tree.getParameterAsValue(delayFilterParamId).getValue(),
		(FilterType)(int)tree.getParameterAsValue(delayFilterTypeParamId).getValue());
	delay.setWetLevel(tree.getParameterAsValue(delayWetLevelParamId).getValue());
	delay.setTailoff(tree.getParameterAsValue(delayTailoffParamId).getValue());
	delay.setEnabled(tree.getParameterAsValue(delayEnabledParamId).getValue());

	juce::dsp::AudioBlock<float> block(buffer);
	juce::dsp::ProcessContextReplacing<float> ctx(block);
	delay.process(ctx);

	if (tree.getParameterAsValue(reverbEnabledParamId).getValue()) {
		auto leftBlock = block.getSingleChannelBlock(0);
		auto rightBlock = block.getSingleChannelBlock(1);

		juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
		juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

		leftReverb.process(leftContext);
		rightReverb.process(rightContext);
	}
	if (tree.getParameterAsValue(ampEnabledParamId).getValue())
		buffer.applyGain(tree.getParameterAsValue(ampVolumeParamId).getValue());
	scopeDataCollector.process(buffer.getReadPointer(0), (size_t)buffer.getNumSamples());
}

bool SynthAudioProcessor::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor* SynthAudioProcessor::createEditor() {
    return new SynthAudioProcessorEditor (*this);
}

void SynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
	auto state = tree.copyState();
	std::unique_ptr<juce::XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
	std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(tree.state.getType()))
			tree.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new SynthAudioProcessor();
}

