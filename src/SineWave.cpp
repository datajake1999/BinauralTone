#include "SineWave.h"

SineWave::SineWave()
{
	SampleRate = 44100;
	Frequency = 440;
	Amplitude = 0.5;
	Phase = 0;
	Angle = 0;
	Step = twopi * Frequency / SampleRate;
}

void SineWave::SetSampleRate(double value)
{
	SampleRate = value;
	Step = twopi * Frequency / SampleRate;
}

void SineWave::SetFrequency(double value)
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

void SineWave::SetAmplitude(double value)
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

void SineWave::SetPhase(double value)
{
	Phase = value * (twopi / 360);
	if (Phase > twopi)
	{
		Phase = twopi;
	}
	else if (Phase < 0)
	{
		Phase = 0;
	}
}

double SineWave::GetSampleRate()
{
	return SampleRate;
}

double SineWave::GetFrequency()
{
	return Frequency;
}

double SineWave::GetAmplitude()
{
	return Amplitude;
}

double SineWave::GetPhase()
{
	return (Phase * 360) / twopi;
}

void SineWave::ResetAngle()
{
	Angle = 0;
}

double SineWave::Generate()
{
	double Waveform = Amplitude * sin(Angle + Phase);
	Angle += Step;
	return Waveform;
}

