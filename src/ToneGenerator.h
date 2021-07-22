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
	Silence = 0,
	Sine,
	Square,
	Triangle,
	Sawtooth,
	Noise
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
	signed short *LookupTable;
	unsigned int LookupWaveType;
	double LookupSampleRate;
	double LookupFrequency;
	double LookupAmplitude;
	double LookupPhaseOffset;
	unsigned int LookupSize;
	unsigned int LookupPosition;
public:
	ToneGenerator();
	~ToneGenerator();
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
	signed short GenerateShort();
	void CalculateLookup();
	void ClearLookup();
	signed short GenerateLookup();
	unsigned int Millis2Samples(unsigned int Millis);
	void FillBuffer(signed short *buffer, unsigned int length, bool lookup);
	void FillFloatBuffer(float *buffer, unsigned int length);
};

#endif
