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
}

void BinauralTone::setParameter (VstInt32 index, float value)
{
	switch(index)
	{
	case kFreqL:
		SineL.SetFrequency(value*1000);
		break;
	case kAmpL:
		SineL.SetAmplitude(value);
		break;
	case kPhaseOffsL:
		SineL.SetPhaseOffset(value*360);
		break;
	case kFreqR:
		SineR.SetFrequency(value*1000);
		break;
	case kAmpR:
		SineR.SetAmplitude(value);
		break;
	case kPhaseOffsR:
		SineR.SetPhaseOffset(value*360);
		break;
	}
}

float BinauralTone::getParameter (VstInt32 index)
{
	float value = 0;
	switch(index)
	{
	case kFreqL:
		value = SineL.GetFrequency()/1000;
		break;
	case kAmpL:
		value = SineL.GetAmplitude();
		break;
	case kPhaseOffsL:
		value = SineL.GetPhaseOffset()/360;
		break;
	case kFreqR:
		value = SineR.GetFrequency()/1000;
		break;
	case kAmpR:
		value = SineR.GetAmplitude();
		break;
	case kPhaseOffsR:
		value = SineR.GetPhaseOffset()/360;
		break;
	}
	return value;
}

void BinauralTone::getParameterDisplay (VstInt32 index, char* text)
{
	switch(index)
	{
	case kFreqL:
		float2string (SineL.GetFrequency(), text, kVstMaxParamStrLen);
		break;
	case kAmpL:
		dB2string (SineL.GetAmplitude(), text, kVstMaxParamStrLen);
		break;
	case kPhaseOffsL:
		float2string (SineL.GetPhaseOffset(), text, kVstMaxParamStrLen);
		break;
	case kFreqR:
		float2string (SineR.GetFrequency(), text, kVstMaxParamStrLen);
		break;
	case kAmpR:
		dB2string (SineR.GetAmplitude(), text, kVstMaxParamStrLen);
		break;
	case kPhaseOffsR:
		float2string (SineR.GetPhaseOffset(), text, kVstMaxParamStrLen);
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
	case kFreqR:
		strcpy (label, "hZ");
		break;
	case kAmpR:
		strcpy (label, "dB");
		break;
	case kPhaseOffsR:
		strcpy (label, "Degrees");
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
	case kFreqR:
		strcpy (text, "FreqR");
		break;
	case kAmpR:
		strcpy (text, "AmpR");
		break;
	case kPhaseOffsR:
		strcpy (text, "PhaseOffsR");
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
	SineL.SetSampleRate(sampleRate);
	SineR.SetSampleRate(sampleRate);
}

void BinauralTone::resume ()
{
	SineL.ResetAngle();
	SineR.ResetAngle();
}

void BinauralTone::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
	float* in1 = inputs[0];
	float* in2 = inputs[1];
	float* out1 = outputs[0];
	float* out2 = outputs[1];
	int i;
	for (i=0; i<sampleFrames; i++)
	{
		*out1 = (float)SineL.Generate();
		*out2 = (float)SineR.Generate();
		*in1++;
		*in2++;
		*out1++;
		*out2++;
	}
}

void BinauralTone::processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames)
{
	double* in1 = inputs[0];
	double* in2 = inputs[1];
	double* out1 = outputs[0];
	double* out2 = outputs[1];
	int i;
	for (i=0; i<sampleFrames; i++)
	{
		*out1 = SineL.Generate();
		*out2 = SineR.Generate();
		*in1++;
		*in2++;
		*out1++;
		*out2++;
	}
}
