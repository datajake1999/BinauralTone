#ifndef TONEGENERATOR_H
#define TONEGENERATOR_H

#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const double twopi = 2 * M_PI;

enum
{
	Sine = 1,
	Square,
	Triangle,
	Sawtooth,
	Noise,
	Silence
};

class ToneGenerator
{
private:
	unsigned int WaveType;
	double SampleRate;
	double Frequency;
	double Amplitude;
	double PhaseOffset;
	double Angle;
	double Step;
public:
	ToneGenerator();
	void SetWaveType(unsigned int value);
	void SetSampleRate(double value);
	void SetFrequency(double value);
	void SetAmplitude(double value);
	void SetPhaseOffset(double value);
	unsigned int GetWaveType();
	double GetSampleRate();
	double GetFrequency();
	double GetAmplitude();
	double GetPhaseOffset();
	void ResetAngle();
	double Generate();
};

#endif
