#include "BinauralTone.h"

AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new BinauralTone (audioMaster);
}
