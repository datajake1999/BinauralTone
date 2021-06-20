#ifndef SINEWAVE_H
#define SINEWAVE_H

#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const double twopi = 2 * M_PI;

class SineWave
{
private:
	double SampleRate;
	double Frequency;
	double Amplitude;
	double Phase;
	double Angle;
	double Step;
public:
	SineWave();
	void SetSampleRate(double value);
	void SetFrequency(double value);
	void SetAmplitude(double value);
	void SetPhase(double value);
	double GetSampleRate();
	double GetFrequency();
	double GetAmplitude();
	double GetPhase();
	void ResetAngle();
	double Generate();
};

#endif
