#include "ToneGenerator.h"

ToneGenerator::ToneGenerator()
{
	WaveType = Sine;
	SampleRate = 44100;
	Frequency = 440;
	Amplitude = 0.5;
	PhaseOffset = 0;
	Angle = 0;
	Step = twopi * Frequency / SampleRate;
}

void ToneGenerator::SetWaveType(unsigned int value)
{
	WaveType = value;
	if (WaveType > Silence)
	{
		WaveType = Silence;
	}
	else if (WaveType < Sine)
	{
		WaveType = Sine;
	}
}

void ToneGenerator::SetSampleRate(double value)
{
	SampleRate = value;
	Step = twopi * Frequency / SampleRate;
}

void ToneGenerator::SetFrequency(double value)
{
	Frequency = value;
	if (Frequency > SampleRate / 2)
	{
		Frequency = SampleRate / 2;
	}
	else if (Frequency < 0)
	{
		Frequency = 0;
	}
	Step = twopi * Frequency / SampleRate;
}

void ToneGenerator::SetAmplitude(double value)
{
	Amplitude = value;
	if (Amplitude > 1)
	{
		Amplitude = 1;
	}
	else if (Amplitude < 0)
	{
		Amplitude = 0;
	}
}

void ToneGenerator::SetPhaseOffset(double value)
{
	PhaseOffset = value * (twopi / 360);
	if (PhaseOffset > twopi)
	{
		PhaseOffset = twopi;
	}
	else if (PhaseOffset < 0)
	{
		PhaseOffset = 0;
	}
}

unsigned int ToneGenerator::GetWaveType()
{
	return WaveType;
}

double ToneGenerator::GetSampleRate()
{
	return SampleRate;
}

double ToneGenerator::GetFrequency()
{
	return Frequency;
}

double ToneGenerator::GetAmplitude()
{
	return Amplitude;
}

double ToneGenerator::GetPhaseOffset()
{
	return (PhaseOffset * 360) / twopi;
}

void ToneGenerator::ResetAngle()
{
	Angle = 0;
}

double ToneGenerator::Generate()
{
	double Waveform = 0;
	switch(WaveType)
	{
	case Sine:
		Waveform = sin(Angle + PhaseOffset);
		break;
	case Square:
		Waveform = sin(Angle + PhaseOffset);
		if (Waveform >= 0)
		{
			Waveform = 1;
		}
		else
		{
			Waveform = -1;
		}
		break;
	case Triangle:
		Waveform = 2.0 * Angle / M_PI - 1.0;
		if (Waveform > 1.0)
		{
			Waveform = 2.0 - Waveform;
		}
		break;
	case Sawtooth:
		Waveform = 1.0 - Angle / M_PI;
		break;
	case Noise:
		Waveform = rand() / (double)RAND_MAX;
		break;
	case Silence:
		break;
	}
	Waveform = Amplitude * Waveform;
	Angle += Step;
	if (Angle >= twopi)
	{
		Angle -= twopi;
	}
	return Waveform;
}

signed short ToneGenerator::GenerateShort()
{
	double Sample = Generate() * 32768;
	if (Sample >= 0)
	{
		Sample = floor(Sample + 0.5);
	}
	else
	{
		Sample = ceil(Sample - 0.5);
	}
	if (Sample > 32767)
	{
		Sample = 32767;
	}
	else if (Sample < -32768)
	{
		Sample = -32768;
	}
	return (signed short)Sample;
}
