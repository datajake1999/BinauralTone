#ifndef BinauralTone_H
#define BinauralTone_H

#include "ToneGenerator.h"
#include "public.sdk/source/vst2.x/audioeffectx.h"

enum
{
	// Global
	kNumPrograms = 1,

	// Parameters Tags
	kFreqL = 0,
	kAmpL,
	kPhaseOffsL,
	kWaveL,
	kFreqR,
	kAmpR,
	kPhaseOffsR,
	kWaveR,

	kNumParams
};

class BinauralTone : public AudioEffectX
{
public:
	BinauralTone (audioMasterCallback audioMaster);
	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterName (VstInt32 index, char* text);
	virtual void setProgramName (char* name);
	virtual void getProgramName (char* name);
	virtual bool getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text);
	virtual bool getEffectName (char* name);
	virtual bool getProductString (char* text);
	virtual bool getVendorString (char* text);
	virtual VstInt32 getVendorVersion ();
	virtual VstPlugCategory getPlugCategory ();
	virtual void setSampleRate (float sampleRate);
	virtual void resume ();
	virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
	virtual void processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames);
private:
	ToneGenerator ToneL;
	ToneGenerator ToneR;
	char ProgramName[32];
};

#endif
