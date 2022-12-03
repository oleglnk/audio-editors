#include "stdafx.h"
#include "AudioCore.h"

AudioCore DefaultCore;

AudioCore::AudioCore()
{}

AudioCore::~AudioCore()
{
	if (IsReset == false)
		ResetInformation();
}

void AudioCore::Init()
{
	BASS_Init(-1, 44100, 0, 0, NULL);
	if (HIWORD(BASS_FX_GetVersion()) != BASSVERSION)
	{
	}
	ptail = NULL;
	IsReset = true;
}

BOOL AudioCore::Create(char *recbuf, DWORD reclen)
{
	MainChannel = BASS_StreamCreateFile(TRUE, recbuf, 0, reclen, 0);
	DecChannel = BASS_StreamCreateFile(TRUE, recbuf, 0, reclen, BASS_STREAM_DECODE);
	IsReset = false;
	if ((MainChannel == 0) || (DecChannel == 0))
		return FALSE;
	else
		return TRUE;
}

BOOL AudioCore::Open(CString PathName, CString atype)
{	
	AudioType = atype;
	Path = PathName;
	if (atype == "hstream")
	{
		MainChannel = BASS_StreamCreateFile(FALSE, Path, 0, 0, 0);
		DecChannel = BASS_StreamCreateFile(FALSE, Path, 0, 0, BASS_STREAM_DECODE);	
	}
	if (atype == "hmusic")
	{
		MainChannel = BASS_MusicLoad(FALSE, Path, 
			0, 0, BASS_MUSIC_SINCINTER | BASS_MUSIC_RAMPS, 1);
		DecChannel = BASS_MusicLoad(FALSE, Path, 0, 0, BASS_STREAM_DECODE, 0);
	}
	if (atype == "flac")
	{
		MainChannel = BASS_FLAC_StreamCreateFile(FALSE, Path, 0, 0, 0);
		DecChannel = BASS_FLAC_StreamCreateFile(FALSE, Path, 0, 0, BASS_STREAM_DECODE);
	}
	if (atype == "wma")
	{
		MainChannel = BASS_WMA_StreamCreateFile(FALSE, Path, 0, 0, 0);
		DecChannel = BASS_WMA_StreamCreateFile(FALSE, Path, 0, 0, BASS_STREAM_DECODE);
	}
	if (atype == "wv")
	{
		MainChannel = BASS_WV_StreamCreateFile(FALSE, Path, 0, 0, 0);
		DecChannel = BASS_WV_StreamCreateFile(FALSE, Path, 0, 0, BASS_STREAM_DECODE);
	}
	if (atype == "tta")
	{
		MainChannel = BASS_TTA_StreamCreateFile(FALSE, Path, 0, 0, 0);
		DecChannel = BASS_TTA_StreamCreateFile(FALSE, Path, 0, 0, BASS_STREAM_DECODE);
	}
	if (atype == "mpc")
	{
		MainChannel = BASS_MPC_StreamCreateFile(FALSE, Path, 0, 0, 0);
		DecChannel = BASS_MPC_StreamCreateFile(FALSE, Path, 0, 0, BASS_STREAM_DECODE);
	}
	if (atype == "ape")
	{
		MainChannel = BASS_APE_StreamCreateFile(FALSE, Path, 0, 0, 0);
		DecChannel = BASS_APE_StreamCreateFile(FALSE, Path, 0, 0, BASS_STREAM_DECODE);
	}
	IsReset = false;
	if ((MainChannel == 0) || (DecChannel == 0))
		return FALSE;
	else
		return TRUE;
}

BOOL AudioCore::ResetInformation()
{
	if (IsReset == false)
	{
		while (ptail != NULL)
		{
			pcurr = ptail->pprev;
			for (int i = 0; i < ptail->n; i++)
			{
				BASS_ChannelRemoveFX(MainChannel, ptail->MainFX[i]);
				BASS_ChannelRemoveFX(DecChannel, ptail->DecFX[i]);
			}
			delete[] ptail->MainFX;
			delete[] ptail->DecFX;
			delete ptail;
			ptail = pcurr;
		}
		if ((AudioType == "hstream") || (AudioType == "flac") || (AudioType == "wma") || (AudioType == "wv")
			|| (AudioType == "tta") || (AudioType == "mpc") || (AudioType == "ape"))
		{
			BASS_StreamFree(MainChannel);
			BASS_StreamFree(DecChannel);
		}
		if (AudioType == "hmusic")
		{
			BASS_MusicFree(MainChannel);
			BASS_MusicFree(DecChannel);
		}
		Path.Empty();
		AudioType.Empty();
		IsReset = true;
		return TRUE;
	}
}

void AudioCore::Play(QWORD pos)
{
	BASS_ChannelSetPosition(MainChannel, pos, BASS_POS_BYTE);
	BASS_ChannelPlay(MainChannel, FALSE);
}

DWORD AudioCore::Pause()
{
	BASS_ChannelPause(MainChannel);
	return BASS_ChannelGetPosition(MainChannel, BASS_POS_BYTE);
}

void AudioCore::Stop()
{
	BASS_ChannelStop(MainChannel);
	BASS_ChannelSetPosition(MainChannel, 0, BASS_POS_BYTE);
}

void AudioCore::SaveMP3(CString SavePath, int Quality)
{
	DWORD hencode;
	char *command;
	//Generate command for save
	command = new char[SavePath.GetLength() + 100];
	switch (Quality)
	{
	case 1:
		strcpy(command, "lame --silent -V 2 --noreplaygain - ");
		break;
	case 2:
		strcpy(command, "lame --silent -V 0 --noreplaygain - ");
		break;
	case 3:
		strcpy(command, "lame --silent -b 320 --noreplaygain - ");
		break;
	case 4:
		strcpy(command, "lame --silent -q 2 -b 320 --noreplaygain - ");
		break;
	case 5:
		strcpy(command, "lame --silent -b 320 -q 0 --noreplaygain - ");
		break;
	}
	strcat(command, CT2A(SavePath));
	//Saving
	BASS_ChannelSetPosition(DecChannel, 0, BASS_POS_BYTE);

	hencode = BASS_Encode_Start(DecChannel, command, 0, NULL, 0);
	while (BASS_ChannelIsActive(DecChannel))
	{
		char temp[20000];
		BASS_ChannelGetData(DecChannel, temp, 20000);
		fflush(stdout);
	}

	BASS_Encode_Stop(hencode);
	BASS_ChannelSetPosition(DecChannel, 0, BASS_POS_BYTE);
	
	delete[] command;
}

void AudioCore::SaveOGG(CString SavePath, int Quality)
{
	DWORD hencode;
	char *command;
	//Generate command for save
	command = new char[SavePath.GetLength() + 100];
	switch (Quality)
	{
	case 1:
		strcpy(command, "oggenc2.exe -s %r -Q -q2 - -o ");
		break;
	case 2:
		strcpy(command, "oggenc2.exe -s %r -Q -q4 - -o ");
		break;
	case 3:
		strcpy(command, "oggenc2.exe -s %r -Q -q6 - -o ");
		break;
	case 4:
		strcpy(command, "oggenc2.exe -s %r -Q -q8 - -o ");
		break;
	case 5:
		strcpy(command, "oggenc2.exe -s %r -Q -q10 - -o ");
		break;
	}
	strcat(command, CT2A(SavePath));
	//Saving
	BASS_ChannelSetPosition(DecChannel, 0, BASS_POS_BYTE);

	hencode = BASS_Encode_Start(DecChannel, command, 0, NULL, 0);
	while (BASS_ChannelIsActive(DecChannel))
	{
		char temp[20000];
		BASS_ChannelGetData(DecChannel, temp, 20000);
		fflush(stdout);
	}

	BASS_Encode_Stop(hencode);
	BASS_ChannelSetPosition(DecChannel, 0, BASS_POS_BYTE);

	delete[] command;
}

void AudioCore::SaveWAV(CString SavePath, int Quality)
{
	DWORD hencode;
	char *command;
	//Generate command for save
	command = new char[SavePath.GetLength() + 100];
	switch (Quality)
	{
	case 1:
		strcpy(command, "wavpack.exe -m -i -q -f - ");
		break;
	case 2:
		strcpy(command, "wavpack.exe -m -i -q -h - ");
		break;
	case 3:
		strcpy(command, "wavpack.exe -m -i -q -hh - ");
		break;
	}
	strcat(command, CT2A(SavePath));
	//Saving
	BASS_ChannelSetPosition(DecChannel, 0, BASS_POS_BYTE);

	hencode = BASS_Encode_Start(DecChannel, command, 0, NULL, 0);
	while (BASS_ChannelIsActive(DecChannel))
	{
		char temp[20000];
		BASS_ChannelGetData(DecChannel, temp, 20000);
		fflush(stdout);
	}

	BASS_Encode_Stop(hencode);
	BASS_ChannelSetPosition(DecChannel, 0, BASS_POS_BYTE);

	delete[] command;
}

void AudioCore::GetInformation(CListBox *Inf)
{
	CString temp;
	BASS_CHANNELINFO ChanInfo;
	int c;

	Inf->InsertString(0, Path);
	BASS_ChannelGetInfo(DecChannel, &ChanInfo);
	c = (int)(ChanInfo.freq);
	temp.Format(_T("%d"), c);
	Inf->InsertString(1, temp + _T(" Hz"));
	temp.Empty();

	c = (int)(ChanInfo.chans);
	if (c == 1)
		temp = "1 (Mono)";
	else if (c == 2)
		temp = "2 (Stereo)";
	else
		temp.Format(_T("%d"), c);
	Inf->InsertString(2, temp);
	temp.Empty();

	c = (int)((BASS_StreamGetFilePosition(DecChannel, BASS_FILEPOS_END) / (125 * BASS_ChannelBytes2Seconds(DecChannel, BASS_ChannelGetLength(DecChannel, BASS_POS_BYTE)))) + 0.5);
	if (c <= 0)
	{
		temp = "Unable to determine Bitrate.";
		Inf->InsertString(3, temp);
	}
	else
	{
		temp.Format(_T("%d"), c);
		Inf->InsertString(3, temp + _T(" Kbps"));
	}
	BASS_ChannelSetPosition(DecChannel, 0, BASS_POS_BYTE);
}

int AudioCore::PHSpeed(int Width)
{
	DWORD len;
	float time;
	len = BASS_ChannelGetLength(DecChannel, BASS_POS_BYTE);
	time = BASS_ChannelBytes2Seconds(MainChannel,len) * 1000;
	int k;
	k = (time / Width) / 200;
	k = k * 3;
	return time / Width + k;
}

void AudioCore::AddEffect(BASS_DX8_CHORUS Chorus)
{
	History *temp = new History;
	temp->pprev = NULL;
	temp->Title = "chorus";
	temp->n = 1;

	temp->MainFX = new HFX[1];
	temp->DecFX = new HFX[1];

	temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_CHORUS, 0);
	temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_CHORUS, 0);
	
	BASS_FXSetParameters(temp->MainFX[0], &Chorus);
	BASS_FXSetParameters(temp->DecFX[0], &Chorus);
	if (ptail == NULL)
	{
		temp->pprev = NULL;
		ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail = temp;
	}
}

void AudioCore::AddEffect(BASS_DX8_COMPRESSOR Compressor)
{
	History *temp = new History;
	temp->pprev = NULL;
	temp->Title = "compressor";
	temp->n = 1;

	temp->MainFX = new HFX[1];
	temp->DecFX = new HFX[1];

	temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_COMPRESSOR, 0);
	temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_COMPRESSOR, 0);
	
	BASS_FXSetParameters(temp->MainFX[0], &Compressor);
	BASS_FXSetParameters(temp->DecFX[0], &Compressor);
	if (ptail == NULL)
	{
		temp->pprev = NULL;
		ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail = temp;
	}
}

void AudioCore::AddEffect(BASS_DX8_DISTORTION Distortion)
{
	History *temp = new History;
	temp->pprev = NULL;
	temp->Title = "distortion";
	temp->n = 1;

	temp->MainFX = new HFX[1];
	temp->DecFX = new HFX[1];
	
	temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_DISTORTION, 0);
	temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_DISTORTION, 0);

	BASS_FXSetParameters(temp->MainFX[0], &Distortion);
	BASS_FXSetParameters(temp->DecFX[0], &Distortion);
	if (ptail == NULL)
	{
		temp->pprev = NULL;
		ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail = temp;
	}
}

void AudioCore::AddEffect(BASS_DX8_ECHO Echo)
{
	History *temp = new History;
	temp->pprev = NULL;
	temp->Title = "echo";
	temp->n = 1;

	temp->MainFX = new HFX[1];
	temp->DecFX = new HFX[1];
	
	temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_ECHO, 0);
	temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_ECHO, 0);

	BASS_FXSetParameters(temp->MainFX[0], &Echo);
	BASS_FXSetParameters(temp->DecFX[0], &Echo);
	if (ptail == NULL)
	{
		temp->pprev = NULL;
		ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail = temp;
	}
}

void AudioCore::AddEffect(BASS_DX8_FLANGER Flanger)
{
	History *temp = new History;
	temp->pprev = NULL;
	temp->Title = "flanger";
	temp->n = 1;

	temp->MainFX = new HFX[1];
	temp->DecFX = new HFX[1];

	temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_FLANGER, 0);
	temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_FLANGER, 0);

	BASS_FXSetParameters(temp->MainFX[0], &Flanger);
	BASS_FXSetParameters(temp->DecFX[0], &Flanger);
	if (ptail == NULL)
	{
		temp->pprev = NULL;
		ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail = temp;
	}
}

void AudioCore::AddEffect(BASS_DX8_GARGLE Gargle)
{
	History *temp = new History;
	temp->pprev = NULL;
	temp->Title = "gargle";
	temp->n = 1;

	temp->MainFX = new HFX[1];
	temp->DecFX = new HFX[1];
	
	temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_GARGLE, 0);
	temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_GARGLE, 0);

	BASS_FXSetParameters(temp->MainFX[0], &Gargle);
	BASS_FXSetParameters(temp->DecFX[0], &Gargle);
	if (ptail == NULL)
	{
		temp->pprev = NULL;
		ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail = temp;
	}
}

void AudioCore::AddEffect(BASS_DX8_I3DL2REVERB I3DL2Reverb)
{
	History *temp = new History;
	temp->pprev = NULL;
	temp->Title = "i3dl2reverb";
	temp->n = 1;

	temp->MainFX = new HFX[1];
	temp->DecFX = new HFX[1];
	
	temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_I3DL2REVERB, 0);
	temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_I3DL2REVERB, 0);

	BASS_FXSetParameters(temp->MainFX[0], &I3DL2Reverb);
	BASS_FXSetParameters(temp->DecFX[0], &I3DL2Reverb);
	if (ptail == NULL)
	{
		temp->pprev = NULL;
		ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail = temp;
	}
}

void AudioCore::AddEffect(BASS_DX8_REVERB Reverb)
{
	History *temp = new History;
	temp->pprev = NULL;
	temp->Title = "reverb";
	temp->n = 1;

	temp->MainFX = new HFX[1];
	temp->DecFX = new HFX[1];
	
	temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_REVERB, 0);
	temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_REVERB, 0);

	BASS_FXSetParameters(temp->MainFX[0], &Reverb);
	BASS_FXSetParameters(temp->DecFX[0], &Reverb);
	if (ptail == NULL)
	{
		temp->pprev = NULL;
		ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail = temp;
	}
}

void AudioCore::AddEffect(BASS_DX8_PARAMEQ *ParameQ, int n)
{
	History *temp = new History;
	temp->pprev = NULL;
	temp->Title = "parameq";
	temp->n = n;

	temp->MainFX = new HFX[temp->n];
	temp->DecFX = new HFX[temp->n];
	for (int i = 0; i < temp->n; i++)
	{
		temp->MainFX[i] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_PARAMEQ, 0);
		temp->DecFX[i] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_FXSetParameters(temp->MainFX[i], &ParameQ[i]);
		BASS_FXSetParameters(temp->DecFX[i], &ParameQ[i]);
	}
	
	if (ptail == NULL)
	{
		temp->pprev = NULL;
		ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail = temp;
	}
}

void AudioCore::AddEffect(BASS_BFX_PEAKEQ *PeakeQ, int n)
{
	History *temp = new History;
	temp->pprev = NULL;
	temp->Title = "peakeq";
	temp->n = n;

	temp->MainFX = new HFX[temp->n];
	temp->DecFX = new HFX[temp->n];
	for (int i = 0; i < temp->n; i++)
	{
		temp->MainFX[i] = BASS_ChannelSetFX(MainChannel, BASS_FX_BFX_PEAKEQ, 0);
		temp->DecFX[i] = BASS_ChannelSetFX(DecChannel, BASS_FX_BFX_PEAKEQ, 0);

		BASS_FXSetParameters(temp->MainFX[i], &PeakeQ[i]);
		BASS_FXSetParameters(temp->DecFX[i], &PeakeQ[i]);
	}

	if (ptail == NULL)
	{
		temp->pprev = NULL;
		ptail = temp;
	}
	else
	{
		temp->pprev = ptail;
		ptail = temp;
	}
}

BOOL AudioCore::RemoveEffect()
{
	if (ptail->pprev != NULL)
	{	
		pcurr = ptail;
		for (int i = 0; i < pcurr->n; i++)
		{
			BASS_ChannelRemoveFX(MainChannel, pcurr->MainFX[i]);
			BASS_ChannelRemoveFX(DecChannel, pcurr->DecFX[i]);
		}
		delete[] pcurr->MainFX;
		delete[] pcurr->DecFX;

		pcurr = ptail->pprev;
		delete ptail;
		ptail = pcurr;
		return FALSE;
	}
	else
	{
		for (int i = 0; i < ptail->n; i++)
		{
			BASS_ChannelRemoveFX(MainChannel, ptail->MainFX[i]);
			BASS_ChannelRemoveFX(DecChannel, ptail->DecFX[i]);
		}
		delete[] ptail->MainFX;
		delete[] ptail->DecFX;
		delete ptail;
		ptail = NULL;
		return TRUE;
	}
}

void AudioCore::RepeatLastCommand()
{
	if (ptail != NULL)
	{
		History *temp = new History;
		temp->pprev = ptail;
		temp->Title = ptail->Title;
		temp->n = ptail->n;
		temp->MainFX = new HFX[temp->n];
		temp->DecFX = new HFX[temp->n];
		if (temp->Title == "chorus")
		{
			BASS_DX8_CHORUS DX8;
			temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_CHORUS, 0);
			temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_CHORUS, 0);

			BASS_FXGetParameters(ptail->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->DecFX[0], &DX8);
		}
		if (temp->Title == "compressor")
		{
			BASS_DX8_COMPRESSOR DX8;
			temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_COMPRESSOR, 0);
			temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_COMPRESSOR, 0);

			BASS_FXGetParameters(ptail->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->DecFX[0], &DX8);
		}
		if (temp->Title == "distortion")
		{
			BASS_DX8_DISTORTION DX8;
			temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_DISTORTION, 0);
			temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_DISTORTION, 0);

			BASS_FXGetParameters(ptail->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->DecFX[0], &DX8);
		}
		if (temp->Title == "echo")
		{
			BASS_DX8_ECHO DX8;
			temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_ECHO, 0);
			temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_ECHO, 0);

			BASS_FXGetParameters(ptail->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->DecFX[0], &DX8);
		}
		if (temp->Title == "flanger")
		{
			BASS_DX8_FLANGER DX8;
			temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_FLANGER, 0);
			temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_FLANGER, 0);

			BASS_FXGetParameters(ptail->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->DecFX[0], &DX8);
		}
		if (temp->Title == "gargle")
		{
			BASS_DX8_GARGLE DX8;
			temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_GARGLE, 0);
			temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_GARGLE, 0);

			BASS_FXGetParameters(ptail->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->DecFX[0], &DX8);
		}
		if (temp->Title == "i3dl2reverb")
		{
			BASS_DX8_I3DL2REVERB DX8;
			temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_I3DL2REVERB, 0);
			temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_I3DL2REVERB, 0);

			BASS_FXGetParameters(ptail->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->DecFX[0], &DX8);
		}
		if (temp->Title == "reverb")
		{
			BASS_DX8_REVERB DX8;
			temp->MainFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_REVERB, 0);
			temp->DecFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_REVERB, 0);

			BASS_FXGetParameters(ptail->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->MainFX[0], &DX8);
			BASS_FXSetParameters(temp->DecFX[0], &DX8);
		}
		if (temp->Title == "parameq")
		{
			BASS_DX8_PARAMEQ DX8;
			for (int i = 0; i < temp->n; i++)
			{
				temp->MainFX[i] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_PARAMEQ, 0);
				temp->DecFX[i] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_PARAMEQ, 0);

				BASS_FXGetParameters(ptail->MainFX[i], &DX8);
				BASS_FXSetParameters(temp->MainFX[i], &DX8);
				BASS_FXSetParameters(temp->DecFX[i], &DX8);
			}
		}
		if (temp->Title == "peakeq")
		{
			BASS_BFX_PEAKEQ DX8;
			for (int i = 0; i < temp->n; i++)
			{
				temp->MainFX[i] = BASS_ChannelSetFX(MainChannel, BASS_FX_BFX_PEAKEQ, 0);
				temp->DecFX[i] = BASS_ChannelSetFX(DecChannel, BASS_FX_BFX_PEAKEQ, 0);

				BASS_FXGetParameters(ptail->MainFX[i], &DX8);
				BASS_FXSetParameters(temp->MainFX[i], &DX8);
				BASS_FXSetParameters(temp->DecFX[i], &DX8);
			}
		}
		temp->pprev = ptail;
		ptail = temp;
	}	
}

void AudioCore::TestOn(CString EfType, int n)
{
	FXN = n;
	MainTestFX = new HFX[FXN];
	DecTestFX = new HFX[FXN];
	if (EfType == "chorus")
	{
		MainTestFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_CHORUS, 0);
		DecTestFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_CHORUS, 0);
	}
	if (EfType == "compressor")
	{
		MainTestFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_COMPRESSOR, 0);
		DecTestFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_COMPRESSOR, 0);
	}
	if (EfType == "distortion")
	{
		MainTestFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_DISTORTION, 0);
		DecTestFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_DISTORTION, 0);
	}
	if (EfType == "echo")
	{
		MainTestFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_ECHO, 0);
		DecTestFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_ECHO, 0);
	}
	if (EfType == "flanger")
	{
		MainTestFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_FLANGER, 0);
		DecTestFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_FLANGER, 0);
	}
	if (EfType == "gargle")
	{
		MainTestFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_GARGLE, 0);
		DecTestFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_GARGLE, 0);
	}
	if (EfType == "i3dl2reverb")
	{
		MainTestFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_I3DL2REVERB, 0);
		DecTestFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_I3DL2REVERB, 0);
	}
	if (EfType == "reverb")
	{
		MainTestFX[0] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_REVERB, 0);
		DecTestFX[0] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_REVERB, 0);
	}
	if (EfType == "parameq")
	{
		for (int i = 0; i < FXN; i++)
		{
			MainTestFX[i] = BASS_ChannelSetFX(MainChannel, BASS_FX_DX8_PARAMEQ, 0);
			DecTestFX[i] = BASS_ChannelSetFX(DecChannel, BASS_FX_DX8_PARAMEQ, 0);
		}
	}
	if (EfType == "peakeq")
	{
		for (int i = 0; i < FXN; i++)
		{
			MainTestFX[i] = BASS_ChannelSetFX(MainChannel, BASS_FX_BFX_PEAKEQ, 0);
			DecTestFX[i] = BASS_ChannelSetFX(DecChannel, BASS_FX_BFX_PEAKEQ, 0);
		}
	}
}

void AudioCore::TestUpdate(BASS_DX8_CHORUS Chorus)
{
	BASS_FXSetParameters(MainTestFX[0], &Chorus);
	BASS_FXSetParameters(DecTestFX[0], &Chorus);
}

void AudioCore::TestUpdate(BASS_DX8_COMPRESSOR Compressor)
{
	BASS_FXSetParameters(MainTestFX[0], &Compressor);
	BASS_FXSetParameters(DecTestFX[0], &Compressor);
}

void AudioCore::TestUpdate(BASS_DX8_DISTORTION Distortion)
{
	BASS_FXSetParameters(MainTestFX[0], &Distortion);
	BASS_FXSetParameters(DecTestFX[0], &Distortion);
}

void AudioCore::TestUpdate(BASS_DX8_ECHO Echo)
{
	BASS_FXSetParameters(MainTestFX[0], &Echo);
	BASS_FXSetParameters(DecTestFX[0], &Echo);
}

void AudioCore::TestUpdate(BASS_DX8_FLANGER Flanger)
{
	BASS_FXSetParameters(MainTestFX[0], &Flanger);
	BASS_FXSetParameters(DecTestFX[0], &Flanger);
}

void AudioCore::TestUpdate(BASS_DX8_GARGLE Gargle)
{
	BASS_FXSetParameters(MainTestFX[0], &Gargle);
	BASS_FXSetParameters(DecTestFX[0], &Gargle);
}

void AudioCore::TestUpdate(BASS_DX8_I3DL2REVERB I3DL2Reverb)
{
	BASS_FXSetParameters(MainTestFX[0], &I3DL2Reverb);
	BASS_FXSetParameters(DecTestFX[0], &I3DL2Reverb);
}

void AudioCore::TestUpdate(BASS_DX8_REVERB Reverb)
{
	BASS_FXSetParameters(MainTestFX[0], &Reverb);
	BASS_FXSetParameters(DecTestFX[0], &Reverb);
}

void AudioCore::TestUpdate(BASS_DX8_PARAMEQ *ParameQ)
{
	for (int i = 0; i < FXN; i++)
	{
		BASS_FXSetParameters(MainTestFX[i], &ParameQ[i]);
		BASS_FXSetParameters(DecTestFX[i], &ParameQ[i]);
	}
}

void AudioCore::TestUpdate(BASS_BFX_PEAKEQ *PeakeQ)
{
	for (int i = 0; i < FXN; i++)
	{
		BASS_FXSetParameters(MainTestFX[i], &PeakeQ[i]);
		BASS_FXSetParameters(DecTestFX[i], &PeakeQ[i]);
	}
}

void AudioCore::TestOff()
{
	for (int i = 0; i < FXN; i++)
	{
		BASS_ChannelRemoveFX(MainChannel, MainTestFX[i]);
		BASS_ChannelRemoveFX(DecChannel, DecTestFX[i]);
	}
	delete[] MainTestFX;
	delete[] DecTestFX;
	FXN = -1;
}

float AudioCore::GetTime(int x)
{
	DWORD len;
	float time;
	len = BASS_ChannelGetLength(DecChannel, BASS_POS_BYTE);
	time = BASS_ChannelBytes2Seconds(MainChannel, len) * 1000;
	return ((time / 806)*x) / 1000;
}

CString AudioCore::ShowTime()
{
	CString s, m, ms;
	int millisec, seconds, minutes;
	double time;
	time = BASS_ChannelBytes2Seconds(MainChannel, BASS_ChannelGetPosition(MainChannel, BASS_POS_BYTE));
	seconds = (int)time;
	
	millisec = (int)((time - floor(time)) * pow(10, 3));
	ms.Format(_T("%03d"), millisec);
	
	minutes = seconds / 60;
	m.Format(_T("%d"), minutes);
	
	seconds -= (minutes * 60);
	s.Format(_T("%02d"), seconds);
	
	return m + _T(":") + s + _T(".") + ms;
}

BOOL AudioCore::CheckTime()
{
	if (BASS_ChannelIsActive(MainChannel) != BASS_ACTIVE_PLAYING)
		return TRUE;
	else
		return FALSE;
}

void AudioCore::DrawWaveForm(CDC *pdc, int Width, int Height)
{
	CPen MyPen(NULL, 1, RGB(24, 243, 173));
	pdc->SelectObject(MyPen);

	BASS_ChannelSetPosition(DecChannel, 0, BASS_POS_BYTE);
	DWORD fBPP, level, left, right, position, cpos;
	bool fl;
	int x, y;
	cpos = 0; left = 0; right = 0;
	fl = false;
	x = 1;
	
	fBPP = BASS_ChannelGetLength(DecChannel, BASS_POS_BYTE) / (Width - 15);
	if (fBPP < BASS_ChannelSeconds2Bytes(DecChannel, 0.02))
		fBPP = BASS_ChannelSeconds2Bytes(DecChannel, 0.02);
	
	while (!fl)
	{
		level = BASS_ChannelGetLevel(DecChannel);
		left = LOWORD(level);
		right = HIWORD(level);
		if (BASS_ChannelIsActive(DecChannel) != BASS_ACTIVE_PLAYING)
			position = BASS_ChannelGetLength(DecChannel, BASS_POS_BYTE);
		else
			position = BASS_ChannelGetPosition(DecChannel, BASS_POS_BYTE) / fBPP;
		if (position > cpos)
		{
			y = (int)(left * (150.0 / 65535.0));
			pdc->MoveTo(x, (Height / 4) - y);
			pdc->LineTo(x, y + (Height / 4));

			y = (int)(right * (150.0 / 65535.0));
			pdc->MoveTo(x, ((Height * 3 / 4)) - y);
			pdc->LineTo(x, y + ((Height * 3 / 4)));
			x++;
			if (position >= DWORD(Width))
				fl = true;
			cpos = position;
		}
		left = 0;
		right = 0;
	}
}

void AudioCore::DrawLevels(CDC *pdc, int Width)
{
	DWORD level, left, right;
	level = BASS_ChannelGetLevel(MainChannel);
	left = LOWORD(level);
	right = HIWORD(level);
	int r, g;
	g = 255;
	r = 0;
	left = left * Width / 32768;
	right = right * Width / 32768;
	int x, i, h;
	x = 0; i = 0; h = Width / 255;
	while(x < left)
	{
		CPen MyPen(NULL, 1, RGB(r + i, g - i, 0));
		CBrush MyBrush(RGB(r + i, g - i, 0));
		pdc->SelectObject(MyPen);
		pdc->SelectObject(MyBrush);

		pdc->Rectangle(x, 0, x + h, 22);
		x += h;
		i++;
		if (i > 255)
			i = 255;
	}
	x = 0; i = 0;
	while (x < right)
	{
		CPen MyPen(NULL, 1, RGB(r + i, g - i, 0));
		CBrush MyBrush(RGB(r + i, g - i, 0));
		pdc->SelectObject(MyPen);
		pdc->SelectObject(MyBrush);
		pdc->Rectangle(x, 25, x + h, 47);
		x += h;
		i++;
		if (i > 255)
			i = 255;
	}
}