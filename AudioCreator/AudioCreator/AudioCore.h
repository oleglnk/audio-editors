#pragma once
#include <fstream>
#include "bass.h"
#include "bassenc.h"
#include "bass_fx.h"
#include "bass_ape.h"
#include "bass_mpc.h"
#include "bass_tta.h"
#include "basswma.h"
#include "bassflac.h"
#include "basswv.h"

using namespace std;

struct History{
	History *pprev;
	CString Title;
	int n;
	HFX *MainFX;
	HFX *DecFX;
};

class AudioCore
{
private:
	bool IsReset; 
	CString Path;
	DWORD MainChannel, DecChannel;
	CString AudioType;
	HFX *MainTestFX, *DecTestFX;
	int FXN;
	History *ptail, *pcurr;
public:
	AudioCore();
	~AudioCore();
	void Init();
	BOOL Create(char *recbuf, DWORD reclen);
	BOOL Open(CString PathName, CString atype);						//-+
	BOOL ResetInformation();										//-+

	void Play(QWORD pos);											//+-
	DWORD Pause();													//+-
	void Stop();													//-+
	void PlaySelected();											//-

	
	void SaveMP3(CString SavePath, int Quality);			//-+
	void SaveOGG(CString SavePath, int Quality);			//-+
	void SaveWAV(CString SavePath, int Quality);			//-+
	
	
	int PHSpeed(int Width);
	void GetInformation(CListBox *Inf);								//+

	void AddEffect(BASS_DX8_CHORUS Chorus);							//+
	void AddEffect(BASS_DX8_COMPRESSOR Compressor);					//+
	void AddEffect(BASS_DX8_DISTORTION Distortion);					//+
	void AddEffect(BASS_DX8_ECHO Echo);								//+
	void AddEffect(BASS_DX8_FLANGER Flanger);						//+
	void AddEffect(BASS_DX8_GARGLE Gargle);							//+
	void AddEffect(BASS_DX8_I3DL2REVERB I3DL2Reverb);				//+
	void AddEffect(BASS_DX8_REVERB Reverb);							//+
	void AddEffect(BASS_DX8_PARAMEQ *ParameQ, int n);				//+
	void AddEffect(BASS_BFX_PEAKEQ *PeakeQ, int n);					//+
	BOOL RemoveEffect();											//+
	void RepeatLastCommand();										//+

	void TestOn(CString EfType, int n);								//+
	void TestUpdate(BASS_DX8_CHORUS Chorus);						//+
	void TestUpdate(BASS_DX8_COMPRESSOR Compressor);				//+
	void TestUpdate(BASS_DX8_DISTORTION Distortion);				//+
	void TestUpdate(BASS_DX8_ECHO Echo);							//+
	void TestUpdate(BASS_DX8_FLANGER Flanger);						//+
	void TestUpdate(BASS_DX8_GARGLE Gargle);						//+
	void TestUpdate(BASS_DX8_I3DL2REVERB I3DL2Reverb);				//+
	void TestUpdate(BASS_DX8_REVERB Reverb);						//+
	void TestUpdate(BASS_DX8_PARAMEQ *ParameQ);						//+
	void TestUpdate(BASS_BFX_PEAKEQ *PeakeQ);						//+
	void TestOff();													//+
	
	float GetTime(int x);
	CString ShowTime();
	BOOL CheckTime();
	void DrawWaveForm(CDC *pdc, int Width, int Height);				//++-
	void DrawPlayHead();											//-
	void DrawLevels(CDC *pdc, int Width);
};

extern AudioCore DefaultCore;
