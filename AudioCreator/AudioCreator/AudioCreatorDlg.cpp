
// AudioCreatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "AudioCreatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAudioCreatorDlg dialog



CAudioCreatorDlg::CAudioCreatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAudioCreatorDlg::IDD, pParent)
	, m_EStartSelection(_T("00:00"))
	, m_EEndSelection(_T("00:00"))
	, m_EDurSelection(_T("00:00"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAudioCreatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_LIST_HISTORY, m_History);
	DDX_Control(pDX, ID_LIST_INFO, m_Info);
	DDX_Control(pDX, ID_LIST_INFOTYPE, m_InfoType);
	DDX_Control(pDX, ID_TAB_INFORMATION, m_TabInfo);
	DDX_Control(pDX, ID_TAB_HISTORY, m_TabHistory);
	DDX_Control(pDX, ID_BPAUSE, m_BPause);
	DDX_Control(pDX, ID_BPLAY, m_BPlay);
	DDX_Control(pDX, ID_BRECORD, m_BRecord);
	DDX_Control(pDX, ID_BREVERSE, m_BReverse);
	DDX_Control(pDX, ID_BSTOP, m_BStop);
	DDX_Control(pDX, ID_CURTIME, m_CurrentTime);
	DDX_Text(pDX, ID_ESTART, m_EStartSelection);
	DDX_Text(pDX, ID_EEND, m_EEndSelection);
	DDX_Text(pDX, ID_EDURATION, m_EDurSelection);
}

BEGIN_MESSAGE_MAP(CAudioCreatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_COMMAND(ID_MENU_NEW, &CAudioCreatorDlg::OnFMenuNew)
	ON_COMMAND(ID_MENU_OPEN, &CAudioCreatorDlg::OnFMenuOpen)
	ON_COMMAND(ID_MENU_CLOSE, &CAudioCreatorDlg::OnFMenuClose)
	ON_COMMAND(ID_MENU_SAVE, &CAudioCreatorDlg::OnFMenuSave)
	ON_COMMAND(ID_MENU_EXIT, &CAudioCreatorDlg::OnFMenuExit)
	ON_COMMAND(ID_MENU_UNDO, &CAudioCreatorDlg::OnFMenuUndo)
	ON_COMMAND(ID_MENU_REPEATLASTCOMMAND, &CAudioCreatorDlg::OnFMenuRLC)
	ON_COMMAND(ID_MENU_CHORUS, &CAudioCreatorDlg::OnFMenuChorus)
	ON_COMMAND(ID_MENU_COMPRESSOR, &CAudioCreatorDlg::OnFMenuCompressor)
	ON_COMMAND(ID_MENU_DISTORTION, &CAudioCreatorDlg::OnFMenuDistortion)
	ON_COMMAND(ID_MENU_ECHO, &CAudioCreatorDlg::OnFMenuEcho)
	ON_COMMAND(ID_MENU_EQ10, &CAudioCreatorDlg::OnFMenuEqualizer10)
	ON_COMMAND(ID_MENU_EQ20, &CAudioCreatorDlg::OnFMenuEqualizer20)
	ON_COMMAND(ID_MENU_EQ30, &CAudioCreatorDlg::OnFMenuEqualizer30)
	ON_COMMAND(ID_MENU_FLANGER, &CAudioCreatorDlg::OnFMenuFlanger)
	ON_COMMAND(ID_MENU_GARGLE, &CAudioCreatorDlg::OnFMenuGargle)
	ON_COMMAND(ID_MENU_I3DL2REVERB, &CAudioCreatorDlg::OnFMenuI3DL2Reverb)
	ON_COMMAND(ID_MENU_REVERB, &CAudioCreatorDlg::OnFMenuReverb)
	ON_COMMAND(ID_MENU_PARAMEQ, &CAudioCreatorDlg::OnFMenuParameQ)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_BSTOP, &CAudioCreatorDlg::OnBnClickedBstop)
	ON_BN_CLICKED(ID_BPAUSE, &CAudioCreatorDlg::OnBnClickedBpause)
	ON_BN_CLICKED(ID_BPLAY, &CAudioCreatorDlg::OnBnClickedBplay)
	ON_BN_CLICKED(ID_BRECORD, &CAudioCreatorDlg::OnBnClickedBrecord)
	ON_BN_CLICKED(ID_BREVERSE, &CAudioCreatorDlg::OnBnClickedBreverse)
END_MESSAGE_MAP()


// CAudioCreatorDlg message handlers

BOOL CAudioCreatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	IsLaunched = false;
	FirstLaunch = false;
	MustBeDelete = false;

	BG.LoadBitmapW(ID_BMPBG);
	PH.LoadBitmapW(ID_BMPPH);
	phpos = -5;

	m_Menu.LoadMenuW(IDR_MAINDLG_MENU);
	SetMenu(&m_Menu);

	HotKeys = LoadAccelerators(AfxGetResourceHandle(),
		MAKEINTRESOURCE(IDR_ACCELERATOR1));

	m_BPause.SetIcon(theApp.LoadIcon(ID_PAUSE_OFF));
	m_BPlay.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
	m_BReverse.SetIcon(theApp.LoadIcon(ID_REVERSE_OFF));
	m_BRecord.SetIcon(theApp.LoadIcon(ID_RECORD_ON));
	m_BStop.SetIcon(theApp.LoadIcon(ID_STOP_OFF));

	m_TabHistory.InsertItem(0, _T("History"));
	m_TabInfo.InsertItem(0, _T("Information"));
	
	m_InfoType.AddString(_T("File Path: "));
	m_InfoType.AddString(_T("Sample Rate"));
	m_InfoType.AddString(_T("Channels: "));
	m_InfoType.AddString(_T("Bitrate: "));

	m_TimeFont = new CFont();
	m_TimeFont->CreatePointFont(350, _T("Arial"));
	GetDlgItem(ID_CURTIME)->SetFont(m_TimeFont, TRUE);

	ReverseOn = true;
	GetDlgItem(ID_BREVERSE)->EnableWindow(0);
	m_BReverse.SetIcon(theApp.LoadIcon(ID_REVERSE_ON));
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAudioCreatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawLvLsBG();
		if ((FirstLaunch) || (MustBeDelete))
		{
			WaveForm.DeleteObject();
			MustBeDelete = false;
		}
			

		CClientDC *FullPDC = new CClientDC(this);

		CRect Screen;
		GetClientRect(Screen);
		CRect r_CL(0, 0, Screen.Width() - 300, (Screen.Height() * 2 / 3 - 13));

		CDC FullMDC;
		if (!FullMDC.CreateCompatibleDC(FullPDC))
			return;
		CBitmap* oldBmp;
		CBitmap memBmp;
		if (!memBmp.CreateCompatibleBitmap(FullPDC, r_CL.Width(), r_CL.Height()))
			return;

		oldBmp = FullMDC.SelectObject(&memBmp);
		
		CBrush BGCLR(RGB(0, 0, 0));
		FullMDC.SelectObject(&BGCLR);
		FullMDC.FillRect(r_CL, &BGCLR);
		
		CClientDC *BGPDC = new CClientDC(this);

		CDC BGMDC;
		if (!BGMDC.CreateCompatibleDC(BGPDC))
			return;

		BGMDC.SelectObject(&BG);
		TransparentBlt(FullMDC, 0, 0, r_CL.Width(), r_CL.Height(), BGMDC, 0, 0, r_CL.Width(), r_CL.Height(), RGB(0, 0, 0));

		BGMDC.DeleteDC();
		delete BGPDC;

		if (IsLaunched)
		{
			CClientDC *WFPDC = new CClientDC(this);

			CDC WFMDC;
			if (!WFMDC.CreateCompatibleDC(WFPDC))
				return;
			if (FirstLaunch)
			{
				if (!WaveForm.CreateCompatibleBitmap(WFPDC, r_CL.Width(), r_CL.Height()))
					return;

				WFMDC.SelectObject(&WaveForm);
				DefaultCore.DrawWaveForm(&WFMDC, r_CL.Width(), r_CL.Height());
				PHSpeed = DefaultCore.PHSpeed(r_CL.Width());
				FirstLaunch = false;				
			}
			WFMDC.SelectObject(&WaveForm);
			TransparentBlt(FullMDC, 0, 0, r_CL.Width(), r_CL.Height(), WFMDC, 0, 0, r_CL.Width(), r_CL.Height(), RGB(0, 0, 0));

			WFMDC.DeleteDC();
			delete WFPDC;
		}
		
		CClientDC *PHPDC = new CClientDC(this);

		CDC PHMDC;
		if (!PHMDC.CreateCompatibleDC(PHPDC))
			return;

		PHMDC.SelectObject(&PH);
		TransparentBlt(FullMDC, phpos, 0, 11, r_CL.Height(), PHMDC, 0, 0, 11, r_CL.Height(), RGB(0, 0, 0));
		
		PHMDC.DeleteDC();
		delete PHPDC;

		FullPDC->BitBlt(290, Screen.top + 10, r_CL.Width(), r_CL.Height(), &FullMDC, 0, 0, SRCCOPY);
		FullMDC.SelectObject(oldBmp);
		memBmp.DeleteObject();
		FullMDC.DeleteDC();
		delete FullPDC;
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAudioCreatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CAudioCreatorDlg::PreTranslateMessage(MSG* pMsg)
{
	if (TranslateAccelerator(m_hWnd, HotKeys, pMsg))
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CAudioCreatorDlg::OnClose()
{
	OnFMenuClose();
	delete m_TimeFont;
	CDialogEx::OnClose();
}

void CAudioCreatorDlg::OnFMenuNew()
{
	if (IsLaunched)
	{
		OnFMenuClose();
		if (IsLaunched == false)
		{
			OnFMenuNew();
		}
	}
	else
	{
		CRecordDlg m_Dlg;
		nResponse = m_Dlg.DoModal();
		if (nResponse == 1)
		{
			m_History.AddString(_T("File creating"));
			m_Info.AddString(_T("-"));
			m_Info.AddString(_T("44100 Hz"));
			m_Info.AddString(_T("2 (Stereo)"));
			m_Info.AddString(_T("-"));
			IsLaunched = true;
			FirstLaunch = true;
			Paused = false;
			CurPos = 0;
			EnableAll();
			GetDlgItem(ID_BPLAY)->EnableWindow(1);
			GetDlgItem(ID_BSTOP)->EnableWindow(1);
			GetDlgItem(ID_BREVERSE)->EnableWindow(1);
			GetDlgItem(ID_BRECORD)->EnableWindow(0);
			m_BPlay.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
			m_BStop.SetIcon(theApp.LoadIcon(ID_STOP_ON));
			m_BRecord.SetIcon(theApp.LoadIcon(ID_RECORD_OFF));
			GetDlgItem(ID_BPAUSE)->EnableWindow(1);
			m_BPause.SetIcon(theApp.LoadIcon(ID_PAUSE_ON));
			Invalidate(0);
		}		
	}
}

void CAudioCreatorDlg::OnFMenuOpen()
{
	if (IsLaunched)
	{
		OnFMenuClose();
		if (IsLaunched == false)
		{
			OnFMenuOpen();
		}
	}
	else
	{
		CString TFileFormat;
		CFileDialog OpenDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
			_T("Playable files|*.mp1;*.m1a;*.mp2;*.mp3;*.wav;*.wave;*.ogg;*.oga;*.spx;*.aiff;*.aif;*.aifc;*.xm;*.s3m;*.mod;*.flac;*.wma;*.wmv;*.wv;*.wvc;*.tta;*.mpc;*.mpp;*.ape|MPEG|*.mp1;*.m1a;*.mp2;*.mp3|WAV|*.wav;*.wave|OGG|*.ogg;*.oga;*.spx|AIFF|*.aiff;*.aif;*.aifc|MOD|*.xm;*.s3m;*.mod|FLAC|*.flac|WMA|*.wma;*.wmv|WavPack|*.wv;*wvc|The True Audio(TTA)|*.tta|MusePack|*.mpc;*.mpp|Monkey's Audio|*.ape||"));
		OpenDlg.m_ofn.lpstrTitle = _T("Open audio...");
		if (OpenDlg.DoModal() == IDOK)
		{
			DefaultCore.Init();
			TFileFormat = OpenDlg.GetFileExt();
			OriginPath = OpenDlg.GetPathName();
			TFileFormat.MakeLower();
			if ((TFileFormat == "wav") || (TFileFormat == "wave") || (TFileFormat == "ogg")
				|| (TFileFormat == "oga") || (TFileFormat == "spx") || (TFileFormat == "mp1")
				|| (TFileFormat == "m1p") || (TFileFormat == "mp2") || (TFileFormat == "mp3")
				|| (TFileFormat == "aiff") || (TFileFormat == "aif") || (TFileFormat == "aifc"))
				DefaultCore.Open(OriginPath, _T("hstream"));
			if ((TFileFormat == "xm") || (TFileFormat == "s3m") || (TFileFormat == "mod"))
				DefaultCore.Open(OriginPath, _T("hmusic"));
			if (TFileFormat == "flac")
				DefaultCore.Open(OriginPath, _T("flac"));
			if ((TFileFormat == "wma") || (TFileFormat == "wmv"))
				DefaultCore.Open(OriginPath, _T("wma"));
			if ((TFileFormat == "wv") || (TFileFormat == "wvc"))
				DefaultCore.Open(OriginPath, _T("wv"));
			if (TFileFormat == "tta")
				DefaultCore.Open(OriginPath, _T("tta"));
			if ((TFileFormat == "mpc") || (TFileFormat == "mpp"))
				DefaultCore.Open(OriginPath, _T("mpc"));
			if (TFileFormat == "ape")
				DefaultCore.Open(OriginPath, _T("ape"));
			m_History.AddString(_T("File opening"));
			DefaultCore.GetInformation(&m_Info);
			IsLaunched = true;
			FirstLaunch = true;
			Paused = false;
			CurPos = 0;
			EnableAll();
			GetDlgItem(ID_BPLAY)->EnableWindow(1);
			GetDlgItem(ID_BSTOP)->EnableWindow(1);
			GetDlgItem(ID_BREVERSE)->EnableWindow(1);
			GetDlgItem(ID_BRECORD)->EnableWindow(0);
			m_BPlay.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
			m_BStop.SetIcon(theApp.LoadIcon(ID_STOP_ON));
			GetDlgItem(ID_BPAUSE)->EnableWindow(1);
			m_BPause.SetIcon(theApp.LoadIcon(ID_PAUSE_ON));
			m_BRecord.SetIcon(theApp.LoadIcon(ID_RECORD_OFF));
			
			m_EEndSelection = "00:00";
			CString t;
			int temp;
			temp = DefaultCore.GetTime(806) / 60;
			m_EEndSelection.Format(_T("%02d"), temp);
			m_EEndSelection += ":";
			temp = DefaultCore.GetTime(806) - temp * 60;
			t.Format(_T("%02d"), temp);
			m_EEndSelection += t;	
			m_EDurSelection = m_EEndSelection;
			UpdateData(false);
			Invalidate(0);
		}
	}
}

void CAudioCreatorDlg::OnFMenuClose()
{
	if (IsLaunched)
	{
		int m_ID = MessageBox(
			L"All unsaved data will be lost.\nSave changes?",
			L"Audio Creator",
			MB_ICONQUESTION | MB_YESNOCANCEL
			);
		switch (m_ID)
		{
		case IDYES:
			OnFMenuSave();
			if (Cancel == false)
			{
				DefaultCore.ResetInformation();
				DisableAll();
				GetDlgItem(ID_BPLAY)->EnableWindow(0);
				GetDlgItem(ID_BSTOP)->EnableWindow(0);
				GetDlgItem(ID_BPAUSE)->EnableWindow(0);
				GetDlgItem(ID_BREVERSE)->EnableWindow(0);
				GetDlgItem(ID_BRECORD)->EnableWindow(1);
				m_BPlay.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
				m_BStop.SetIcon(theApp.LoadIcon(ID_STOP_OFF));
				m_BPause.SetIcon(theApp.LoadIcon(ID_PAUSE_OFF));
				m_BRecord.SetIcon(theApp.LoadIcon(ID_RECORD_ON));

				m_EStartSelection.Empty();	m_EStartSelection = "00:00";
				m_EEndSelection.Empty();	m_EEndSelection = "00:00";
				m_EDurSelection.Empty();	m_EDurSelection = "00:00";

				UpdateData(false);
				
				m_History.ResetContent();
				m_Info.ResetContent();

				IsLaunched = false;
				FirstLaunch = false;
				MustBeDelete = true;
				Invalidate(0);
			}
			break;
		case IDNO:
			OnBnClickedBstop();
			DefaultCore.ResetInformation();
			DisableAll();
			GetDlgItem(ID_BPLAY)->EnableWindow(0);
			GetDlgItem(ID_BSTOP)->EnableWindow(0);
			GetDlgItem(ID_BPAUSE)->EnableWindow(0);
			GetDlgItem(ID_BREVERSE)->EnableWindow(0);
			GetDlgItem(ID_BRECORD)->EnableWindow(1);
			m_BPlay.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
			m_BStop.SetIcon(theApp.LoadIcon(ID_STOP_OFF));
			m_BPause.SetIcon(theApp.LoadIcon(ID_PAUSE_OFF));
			m_BRecord.SetIcon(theApp.LoadIcon(ID_RECORD_ON));

			m_EStartSelection.Empty();	m_EStartSelection = "00:00";
			m_EEndSelection.Empty();	m_EEndSelection = "00:00";
			m_EDurSelection.Empty();	m_EDurSelection = "00:00";
			
			UpdateData(false);

			m_History.ResetContent();
			m_Info.ResetContent();

			IsLaunched = false;
			FirstLaunch = false;
			MustBeDelete = true;
			Invalidate(0);
			break;
		case IDCANCEL:

			break;
		}
	}
	
}

void CAudioCreatorDlg::OnFMenuSave()
{
	CString TFileFormat;
	CString NewPath, NewName;
	CFileDialog	SaveDlg(FALSE, _T("mp3"), NULL, OFN_HIDEREADONLY,
		_T("MP3 File|*.mp3|OGG File|*.ogg|WV|*.wv||"));
	SaveDlg.m_ofn.lpstrTitle = _T("Save audio...");

	int result = SaveDlg.DoModal();
	if (result == IDOK)
	{
		OnBnClickedBstop();
		TFileFormat = SaveDlg.GetFileExt();
		NewName = SaveDlg.GetFileName();
		NewName.Replace(' ', '_');
		NewPath = SaveDlg.GetFolderPath() + _T("\\") + NewName;
		if ((TFileFormat == "mp3"))
		{
			CSaveMP3Dlg m_Dlg;
			m_Dlg.SavePath = NewPath;
			nResponse = m_Dlg.DoModal();
			if (nResponse == 1)
				Cancel = false;
			else
				Cancel = true;
		}
		if ((TFileFormat == "ogg"))
		{
			CSaveOGGDlg m_Dlg;
			m_Dlg.SavePath = NewPath;
			nResponse = m_Dlg.DoModal();
			if (nResponse == 1)
				Cancel = false;
			else
				Cancel = true;
		}
		if ((TFileFormat == "wv"))
		{
			CSaveWAVDlg m_Dlg;
			m_Dlg.SavePath = NewPath;
			nResponse = m_Dlg.DoModal();
			if (nResponse == 1)
				Cancel = false;
			else
				Cancel = true;
		}
		Invalidate(0);
	}
	else
		Cancel = true;
}

void CAudioCreatorDlg::OnFMenuExit()
{
	OnClose();
}

void CAudioCreatorDlg::OnFMenuUndo()
{
	if (DefaultCore.RemoveEffect() == TRUE)
	{
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_DISABLED);
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_DISABLED);
	}
	m_History.DeleteString(m_History.GetCount() - 1);
	type = 0;
}

void CAudioCreatorDlg::OnFMenuRLC()
{
	if (type == 0)
	{
		OnFMenuUndo();
	}
	else if (type == 1)
	{
		DefaultCore.RepeatLastCommand();
		CString temp;
		m_History.GetText(m_History.GetCount() - 1, temp);
		m_History.AddString(temp);
	}
}

void CAudioCreatorDlg::OnFMenuChorus()
{
	CChorusDlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Chorus"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuCompressor()
{
	CCompressorDlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Compressor"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuDistortion()
{
	CDistortionDlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Distortion"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuEcho()
{
	CEchoDlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Echo"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuEqualizer10()
{
	CEqualizer10Dlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Graphic Equalizer (10 bands)"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuEqualizer20()
{
	CEqualizer20Dlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Graphic Equalizer (20 bands)"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuEqualizer30()
{
	CEqualizer30Dlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Graphic Equalizer (30 bands)"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuFlanger()
{
	CFlangerDlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Flanger"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuGargle()
{
	CGargleDlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Amplitude modulation"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuI3DL2Reverb()
{
	CI3DL2ReverbDlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("I3DL2 Reverb"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuReverb()
{
	CReverbDlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Reverb"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}

void CAudioCreatorDlg::OnFMenuParameQ()
{
	CParameQDlg m_Dlg;
	nResponse = m_Dlg.DoModal();
	if (nResponse == 1)
	{
		m_History.AddString(_T("Parametric Equalizer"));
		m_Menu.EnableMenuItem(ID_MENU_REPEATLASTCOMMAND, MF_ENABLED);
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
		type = 1;
	}
}


void CAudioCreatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		m_CurrentTime.SetWindowTextW(DefaultCore.ShowTime());
		if (DefaultCore.CheckTime())
		{
			OnBnClickedBstop();
			if (ReverseOn)
			{
				OnBnClickedBplay();
			}
		}
	}
	if (nIDEvent == 2)
	{
		CClientDC *pdc = new CClientDC(this);
		CRect temp;
		GetClientRect(temp);
		CRect r_CL(0, 0, temp.Width()-50, 47);

		CDC memDC;
		if (!memDC.CreateCompatibleDC(pdc))
			return;
		CBitmap* oldBmp;
		CBitmap memBmp;
		if (!memBmp.CreateCompatibleBitmap(pdc, r_CL.Width(), r_CL.Height()))
			return;
		oldBmp = memDC.SelectObject(&memBmp);

		DefaultCore.DrawLevels(&memDC, r_CL.Width());

		pdc->BitBlt(14, temp.bottom-63, r_CL.Width(), r_CL.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(oldBmp);
		memBmp.DeleteObject();
		memDC.DeleteDC();

		delete pdc;
	}
	if (nIDEvent == 3)
	{
		phpos++;
		Invalidate(0);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CAudioCreatorDlg::EnableAll()
{
	//Menu
		//File
	m_Menu.EnableMenuItem(ID_MENU_CLOSE, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_SAVE, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_SAVEAS, MF_ENABLED);
		//Effects
	m_Menu.EnableMenuItem(ID_MENU_CHORUS, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_FLANGER, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_COMPRESSOR, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_DISTORTION, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_ECHO, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_GARGLE, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_EQ10, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_EQ20, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_EQ30, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_PARAMEQ, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_I3DL2REVERB, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_REVERB, MF_ENABLED);
}

void CAudioCreatorDlg::DisableAll()
{
	//Menu
		//File
	m_Menu.EnableMenuItem(ID_MENU_CLOSE, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_SAVE, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_SAVEAS, MF_DISABLED);
		//Effects
	m_Menu.EnableMenuItem(ID_MENU_CHORUS, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_FLANGER, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_COMPRESSOR, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_DISTORTION, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_ECHO, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_GARGLE, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_EQ10, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_EQ20, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_EQ30, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_PARAMEQ, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_I3DL2REVERB, MF_DISABLED);
	m_Menu.EnableMenuItem(ID_MENU_REVERB, MF_DISABLED);
}

void CAudioCreatorDlg::OnBnClickedBstop()
{
	DefaultCore.Stop();
	phpos = -5;
	CurPos = 0;
	Paused = false;
	KillTimer(m_TTime);
	KillTimer(m_TLevels);
	KillTimer(m_TPlayHead);
	m_CurrentTime.SetWindowTextW(DefaultCore.ShowTime());
	Invalidate(0);
}


void CAudioCreatorDlg::OnBnClickedBpause()
{
	CurPos = DefaultCore.Pause();
	KillTimer(m_TTime);
	KillTimer(m_TLevels);
	KillTimer(m_TPlayHead);
	Paused = true;
}


void CAudioCreatorDlg::OnBnClickedBplay()
{
	if (Paused == false)
		OnBnClickedBstop();
	DefaultCore.Play(CurPos);	
	m_TTime = SetTimer(1, 1, 0);
	m_TLevels = SetTimer(2, 100, 0);
	m_TPlayHead = SetTimer(3, PHSpeed, 0);
}


void CAudioCreatorDlg::OnBnClickedBrecord()
{
	OnFMenuNew();
}


void CAudioCreatorDlg::OnBnClickedBreverse()
{
	if (ReverseOn)
	{
		m_BReverse.SetIcon(theApp.LoadIcon(ID_REVERSE_OFF));
		ReverseOn = false;
	}
	else
	{
		m_BReverse.SetIcon(theApp.LoadIcon(ID_REVERSE_ON));
		ReverseOn = true;
	}
}

void CAudioCreatorDlg::DrawLvLsBG()
{
	CClientDC *pdc = new CClientDC(this);
	CRect temp;
	GetClientRect(temp);
	CRect r_CL(0, 0, temp.Width() - 50, 47);

	CDC memDC;
	if (!memDC.CreateCompatibleDC(pdc))
		return;
	CBitmap* oldBmp;
	CBitmap memBmp;
	if (!memBmp.CreateCompatibleBitmap(pdc, r_CL.Width(), r_CL.Height()))
		return;
	oldBmp = memDC.SelectObject(&memBmp);
	CBrush pbr(RGB(0, 0, 0));
	memDC.SelectObject(&pbr);
	memDC.FillRect(r_CL, &pbr);

	pdc->BitBlt(14, temp.bottom - 63, r_CL.Width(), r_CL.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBmp);
	memBmp.DeleteObject();
	memDC.DeleteDC();

	delete pdc;
}