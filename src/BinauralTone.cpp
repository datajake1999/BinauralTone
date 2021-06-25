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
		ToneL.SetFrequency(value*1000);
		break;
	case kAmpL:
		ToneL.SetAmplitude(value);
		break;
	case kPhaseOffsL:
		ToneL.SetPhaseOffset(value*360);
		break;
	case kWaveL:
		ToneL.SetWaveType(value*4);
		break;
	case kFreqR:
		ToneR.SetFrequency(value*1000);
		break;
	case kAmpR:
		ToneR.SetAmplitude(value);
		break;
	case kPhaseOffsR:
		ToneR.SetPhaseOffset(value*360);
		break;
	case kWaveR:
		ToneR.SetWaveType(value*4);
		break;
	}
}

float BinauralTone::getParameter (VstInt32 index)
{
	float value = 0;
	switch(index)
	{
	case kFreqL:
		value = ToneL.GetFrequency()/1000;
		break;
	case kAmpL:
		value = ToneL.GetAmplitude();
		break;
	case kPhaseOffsL:
		value = ToneL.GetPhaseOffset()/360;
		break;
	case kWaveL:
		value = (float)ToneL.GetWaveType()/4;
		break;
	case kFreqR:
		value = ToneR.GetFrequency()/1000;
		break;
	case kAmpR:
		value = ToneR.GetAmplitude();
		break;
	case kPhaseOffsR:
		value = ToneR.GetPhaseOffset()/360;
		break;
	case kWaveR:
		value = (float)ToneR.GetWaveType()/4;
		break;
	}
	return value;
}

void BinauralTone::getParameterDisplay (VstInt32 index, char* text)
{
	switch(index)
	{
	case kFreqL:
		float2string (ToneL.GetFrequency(), text, kVstMaxParamStrLen);
		break;
	case kAmpL:
		dB2string (ToneL.GetAmplitude(), text, kVstMaxParamStrLen);
		break;
	case kPhaseOffsL:
		float2string (ToneL.GetPhaseOffset(), text, kVstMaxParamStrLen);
		break;
	case kWaveL:
		if (ToneL.GetWaveType() == Silence)
		{
			strcpy (text, "Silence");
		}
		else if (ToneL.GetWaveType() == Sine)
		{
			strcpy (text, "Sine");
		}
		else if (ToneL.GetWaveType() == Square)
		{
			strcpy (text, "Square");
		}
		else if (ToneL.GetWaveType() == Triangle)
		{
			strcpy (text, "Triangle");
		}
		else if (ToneL.GetWaveType() == Sawtooth)
		{
			strcpy (text, "Sawtooth");
		}
		else if (ToneL.GetWaveType() == Noise)
		{
			strcpy (text, "Noise");
		}
		break;
	case kFreqR:
		float2string (ToneR.GetFrequency(), text, kVstMaxParamStrLen);
		break;
	case kAmpR:
		dB2string (ToneR.GetAmplitude(), text, kVstMaxParamStrLen);
		break;
	case kPhaseOffsR:
		float2string (ToneR.GetPhaseOffset(), text, kVstMaxParamStrLen);
		break;
	case kWaveR:
		if (ToneR.GetWaveType() == Silence)
		{
			strcpy (text, "Silence");
		}
		else if (ToneR.GetWaveType() == Sine)
		{
			strcpy (text, "Sine");
		}
		else if (ToneR.GetWaveType() == Square)
		{
			strcpy (text, "Square");
		}
		else if (ToneR.GetWaveType() == Triangle)
		{
			strcpy (text, "Triangle");
		}
		else if (ToneR.GetWaveType() == Sawtooth)
		{
			strcpy (text, "Sawtooth");
		}
		else if (ToneR.GetWaveType() == Noise)
		{
			strcpy (text, "Noise");
		}
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
	case kWaveL:
		strcpy (text, "WaveL");
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
	case kWaveR:
		strcpy (text, "WaveR");
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
	ToneL.SetSampleRate(sampleRate);
	ToneR.SetSampleRate(sampleRate);
}

void BinauralTone::resume ()
{
	ToneL.ResetAngle();
	ToneR.ResetAngle();
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
		*out1 = (float)ToneL.Generate();
		*out2 = (float)ToneR.Generate();
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
		*out1 = ToneL.Generate();
		*out2 = ToneR.Generate();
		*in1++;
		*in2++;
		*out1++;
		*out2++;
	}
}
