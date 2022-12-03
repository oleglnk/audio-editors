#include "stdafx.h"
#include "TEffects.h"


TEffects::TEffects()
{
	phead = NULL;
	ptail = NULL;
}


TEffects::~TEffects()
{
	while (phead != NULL)
	{
		ptail = phead->pnext;
		delete phead;
		phead = ptail;
	}
}

void TEffects::AddToHistory(CString ef, HSTREAM *MainChan, HSTREAM *SaveChan)
{
	EffectsHistory *temp = new EffectsHistory;
	temp->pnext = NULL;
	temp->EfName = ef;
	if (ef == "chorus")
	{
		temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_CHORUS, 10);
		temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_CHORUS, 10);
	}
	if (ef == "distortion")
	{
		temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_DISTORTION, 10);
		temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_DISTORTION, 10);
	}
	if (ef == "echo")
	{
		temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_ECHO, 10);
		temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_ECHO, 10);
	}
	if (ef == "flanger")
	{
		temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_FLANGER, 10);
		temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_FLANGER, 10);
	}
	if (ef == "gargle")
	{
		temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_GARGLE, 10);
		temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_GARGLE, 10);
	}
	if (ef == "i3dl2reverb")
	{
		temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_I3DL2REVERB, 10);
		temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_I3DL2REVERB, 10);
	}
	if (ef == "reverb")
	{
		temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_REVERB, 10);
		temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_REVERB, 10);
	}
	if (phead == NULL)
	{
		temp->pprev = NULL;
		phead = ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail->pnext = temp;
		ptail = temp;
	}
}

void TEffects::RemoveFromHistory(HSTREAM *MainChan, HSTREAM *SaveChan)
{
	if (ptail != phead)
	{
		EffectsHistory *temp = ptail;
		BASS_ChannelRemoveFX(*MainChan, temp->EffFXMain);
		BASS_ChannelRemoveFX(*SaveChan, temp->EffFXSave);
		temp = ptail->pprev;
		delete ptail;
		temp->pnext = NULL;
		ptail = temp;
	}
	else
	{
		BASS_ChannelRemoveFX(*MainChan, ptail->EffFXMain);
		BASS_ChannelRemoveFX(*SaveChan, ptail->EffFXSave);
		phead = ptail->pnext;
		delete ptail;
		ptail = phead;
	}
}

void TEffects::RLAction(CString *ef, HSTREAM *MainChan, HSTREAM *SaveChan)
{
	if ((phead != NULL) && (ptail != NULL))
	{
		EffectsHistory *temp = new EffectsHistory;
		temp->pnext = NULL;
		*ef = temp->EfName = ptail->EfName;
		if (ptail->EfName == "chorus")
		{
			temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_CHORUS, 10);
			temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_CHORUS, 10);
		}
		if (ptail->EfName == "distortion")
		{
			temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_DISTORTION, 10);
			temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_DISTORTION, 10);
		}
		if (ptail->EfName == "echo")
		{
			temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_ECHO, 10);
			temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_ECHO, 10);
		}
		if (ptail->EfName == "flanger")
		{
			temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_FLANGER, 10);
			temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_FLANGER, 10);
		}
		if (ptail->EfName == "gargle")
		{
			temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_GARGLE, 10);
			temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_GARGLE, 10);
		}
		if (ptail->EfName == "i3dl2reverb")
		{
			temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_I3DL2REVERB, 10);
			temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_I3DL2REVERB, 10);
		}
		if (ptail->EfName == "reverb")
		{
			temp->EffFXMain = BASS_ChannelSetFX(*MainChan, BASS_FX_DX8_REVERB, 10);
			temp->EffFXSave = BASS_ChannelSetFX(*SaveChan, BASS_FX_DX8_REVERB, 10);
		}
		temp->pprev = ptail;
		ptail->pnext = temp;
		ptail = temp;
	}

}

BOOL TEffects::IsEmpty()
{
	if ((ptail == NULL) && (phead == NULL))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}