#include "bass.h"
#include "bassenc.h"

#pragma once

struct EffectsHistory{
	EffectsHistory *pnext, *pprev;
	CString EfName;
	HFX EffFXMain;
	HFX EffFXSave;
};

class TEffects
{
private:
	EffectsHistory *phead, *ptail;
public:
	TEffects();
	~TEffects();
	void AddToHistory(CString ef, HSTREAM *MainChan, HSTREAM *SaveChan);
	void RemoveFromHistory(HSTREAM *MainChan, HSTREAM *SaveChan);
	void RLAction(CString *ef, HSTREAM *MainChan, HSTREAM *SaveChan);
	BOOL IsEmpty();
};

