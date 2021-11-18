#include "BinauralTone.h"

BinauralTone::BinauralTone (audioMasterCallback audioMaster)
: AudioEffectX (audioMaster, kNumPrograms, kNumParams)
{
	// init
	setNumInputs (2);	// stereo input
	setNumOutputs (2);	// stereo output
	setUniqueID ('BNTN');	// identify
	strcpy (ProgramName, "Default");
	canProcessReplacing ();
	canDoubleReplacing ();
	ToneGeneratorInit(&ToneL);
	ToneGeneratorInit(&ToneR);
}

void BinauralTone::setParameter (VstInt32 index, float value)
{
	switch(index)
	{
	case kFreqL:
		ToneGeneratorSetFrequency(&ToneL, value*1000);
		break;
	case kAmpL:
		ToneGeneratorSetAmplitude(&ToneL, value);
		break;
	case kPhaseOffsL:
		ToneGeneratorSetPhaseOffset(&ToneL, value*360);
		break;
	case kPulseWidthL:
		ToneGeneratorSetPulseWidth(&ToneL, value);
		break;
	case kWaveL:
		ToneGeneratorSetWaveType(&ToneL, value*(WaveTypes-1));
		break;
	case kDigitL:
		ToneGeneratorSetDigit(&ToneL, value*(DTMFTones-1));
		break;
	case kFreqR:
		ToneGeneratorSetFrequency(&ToneR, value*1000);
		break;
	case kAmpR:
		ToneGeneratorSetAmplitude(&ToneR, value);
		break;
	case kPhaseOffsR:
		ToneGeneratorSetPhaseOffset(&ToneR, value*360);
		break;
	case kPulseWidthR:
		ToneGeneratorSetPulseWidth(&ToneR, value);
		break;
	case kWaveR:
		ToneGeneratorSetWaveType(&ToneR, value*(WaveTypes-1));
		break;
	case kDigitR:
		ToneGeneratorSetDigit(&ToneR, value*(DTMFTones-1));
		break;
	}
}

float BinauralTone::getParameter (VstInt32 index)
{
	float value = 0;
	switch(index)
	{
	case kFreqL:
		value = ToneGeneratorGetFrequency(&ToneL)/1000;
		break;
	case kAmpL:
		value = ToneGeneratorGetAmplitude(&ToneL);
		break;
	case kPhaseOffsL:
		value = ToneGeneratorGetPhaseOffset(&ToneL)/360;
		break;
	case kPulseWidthL:
		value = ToneGeneratorGetPulseWidth(&ToneL);
		break;
	case kWaveL:
		value = (float)ToneGeneratorGetWaveType(&ToneL)/(WaveTypes-1);
		break;
	case kDigitL:
		value = (float)ToneGeneratorGetDigit(&ToneL)/(DTMFTones-1);
		break;
	case kFreqR:
		value = ToneGeneratorGetFrequency(&ToneR)/1000;
		break;
	case kAmpR:
		value = ToneGeneratorGetAmplitude(&ToneR);
		break;
	case kPhaseOffsR:
		value = ToneGeneratorGetPhaseOffset(&ToneR)/360;
		break;
	case kPulseWidthR:
		value = ToneGeneratorGetPulseWidth(&ToneR);
		break;
	case kWaveR:
		value = (float)ToneGeneratorGetWaveType(&ToneR)/(WaveTypes-1);
		break;
	case kDigitR:
		value = (float)ToneGeneratorGetDigit(&ToneR)/(DTMFTones-1);
		break;
	}
	return value;
}

void BinauralTone::getParameterDisplay (VstInt32 index, char* text)
{
	switch(index)
	{
	case kFreqL:
		float2string (ToneGeneratorGetFrequency(&ToneL), text, kVstMaxParamStrLen);
		break;
	case kAmpL:
		dB2string (ToneGeneratorGetAmplitude(&ToneL), text, kVstMaxParamStrLen);
		break;
	case kPhaseOffsL:
		float2string (ToneGeneratorGetPhaseOffset(&ToneL), text, kVstMaxParamStrLen);
		break;
	case kPulseWidthL:
		float2string (ToneGeneratorGetPulseWidth(&ToneL), text, kVstMaxParamStrLen);
		break;
	case kWaveL:
		strcpy (text, ToneGeneratorGetCurrentWaveName(&ToneL));
		break;
	case kDigitL:
		strcpy (text, ToneGeneratorGetCurrentDigitName(&ToneL));
		break;
	case kFreqR:
		float2string (ToneGeneratorGetFrequency(&ToneR), text, kVstMaxParamStrLen);
		break;
	case kAmpR:
		dB2string (ToneGeneratorGetAmplitude(&ToneR), text, kVstMaxParamStrLen);
		break;
	case kPhaseOffsR:
		float2string (ToneGeneratorGetPhaseOffset(&ToneR), text, kVstMaxParamStrLen);
		break;
	case kPulseWidthR:
		float2string (ToneGeneratorGetPulseWidth(&ToneR), text, kVstMaxParamStrLen);
		break;
	case kWaveR:
		strcpy (text, ToneGeneratorGetCurrentWaveName(&ToneR));
		break;
	case kDigitR:
		strcpy (text, ToneGeneratorGetCurrentDigitName(&ToneR));
		break;
	}
}

void BinauralTone::getParameterLabel (VstInt32 index, char* label)
{
	switch(index)
	{
	case kFreqL:
		strcpy (label, "hZ");
		break;
	case kAmpL:
		strcpy (label, "dB");
		break;
	case kPhaseOffsL:
		strcpy (label, "Degrees");
		break;
	case kPulseWidthL:
		strcpy (label, "F");
		break;
	case kFreqR:
		strcpy (label, "hZ");
		break;
	case kAmpR:
		strcpy (label, "dB");
		break;
	case kPhaseOffsR:
		strcpy (label, "Degrees");
		break;
	case kPulseWidthR:
		strcpy (label, "F");
		break;
	}
}

void BinauralTone::getParameterName (VstInt32 index, char* text)
{
	switch(index)
	{
	case kFreqL:
		strcpy (text, "FreqL");
		break;
	case kAmpL:
		strcpy (text, "AmpL");
		break;
	case kPhaseOffsL:
		strcpy (text, "PhaseOffsL");
		break;
	case kPulseWidthL:
		strcpy (text, "PulseWidthL");
		break;
	case kWaveL:
		strcpy (text, "WaveL");
		break;
	case kDigitL:
		strcpy (text, "DigitL");
		break;
	case kFreqR:
		strcpy (text, "FreqR");
		break;
	case kAmpR:
		strcpy (text, "AmpR");
		break;
	case kPhaseOffsR:
		strcpy (text, "PhaseOffsR");
		break;
	case kPulseWidthR:
		strcpy (text, "PulseWidthR");
		break;
	case kWaveR:
		strcpy (text, "WaveR");
		break;
	case kDigitR:
		strcpy (text, "DigitR");
		break;
	}
}

void BinauralTone::setProgramName (char *name)
{
	strcpy (ProgramName, name);
}

void BinauralTone::getProgramName (char *name)
{
	strcpy (name, ProgramName);
}

bool BinauralTone::getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text)
{
	if (index == 0)
	{
		strcpy (text, ProgramName);
		return true;
	}
	return false;
}

bool BinauralTone::getEffectName (char* name)
{
	strcpy (name, "BinauralTone");
	return true;
}

bool BinauralTone::getProductString (char* text)
{
	strcpy (text, "BinauralTone");
	return true;
}

bool BinauralTone::getVendorString (char* text)
{
	strcpy (text, "Datajake");
	return true;
}

VstInt32 BinauralTone::getVendorVersion ()
{
	return 1000;
}

VstPlugCategory BinauralTone::getPlugCategory ()
{
	return kPlugCategGenerator;
}

void BinauralTone::setSampleRate (float sampleRate)
{
	ToneGeneratorSetSampleRate(&ToneL, sampleRate);
	ToneGeneratorSetSampleRate(&ToneR, sampleRate);
}

void BinauralTone::resume ()
{
	ToneGeneratorResetAngle(&ToneL);
	ToneGeneratorResetAngle(&ToneR);
}

void BinauralTone::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
	float* in1 = inputs[0];
	float* in2 = inputs[1];
	float* out1 = outputs[0];
	float* out2 = outputs[1];
	ToneGeneratorFillFloatBuffer(&ToneL, out1, sampleFrames);
	ToneGeneratorFillFloatBuffer(&ToneR, out2, sampleFrames);
}

void BinauralTone::processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames)
{
	double* in1 = inputs[0];
	double* in2 = inputs[1];
	double* out1 = outputs[0];
	double* out2 = outputs[1];
	ToneGeneratorFillDoubleBuffer(&ToneL, out1, sampleFrames);
	ToneGeneratorFillDoubleBuffer(&ToneR, out2, sampleFrames);
}
