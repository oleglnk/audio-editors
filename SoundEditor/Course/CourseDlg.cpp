
// CourseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Course.h"
#include "CourseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCourseDlg dialog



CCourseDlg::CCourseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCourseDlg::IDD, pParent)
	, m_Saving(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCourseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_SONGTIME, m_SlidePlayTime);
	DDX_Control(pDX, ID_TOTALTIME2, m_TotalTime);
	DDX_Control(pDX, ID_TIME2, m_CurrentTime);
	DDX_Control(pDX, ID_EQUALIZERLIST, m_EqualizerList);
	DDX_Control(pDX, ID_EQUALIZER125HZ, m_Equlizer125HZ);
	DDX_Control(pDX, ID_EQUALIZER250HZ, m_Equlizer250HZ);
	DDX_Control(pDX, ID_EQUALIZER500HZ, m_Equlizer500HZ);
	DDX_Control(pDX, ID_EQUALIZER1KHZ, m_Equlizer1KHZ);
	DDX_Control(pDX, ID_EQUALIZER2KHZ, m_Equlizer2KHZ);
	DDX_Control(pDX, ID_EQUALIZER4KHZ, m_Equlizer4KHZ);
	DDX_Control(pDX, ID_EQUALIZER8KHZ, m_Equlizer8KHZ);
	DDX_Control(pDX, ID_EQUALIZER16KHZ, m_Equlizer16KHZ);
	DDX_Control(pDX, ID_TABDIFINFO, m_TabCtrlDifInf);
	DDX_Control(pDX, ID_INFO, m_Info);
	DDX_Control(pDX, ID_INFOTYPE, m_InfoType);
	DDX_Control(pDX, ID_HISTORY, m_History);
	DDX_Control(pDX, ID_VOLUME, m_VolumeSlider);
	DDX_Text(pDX, ID_SAVEISSTARTING, m_Saving);
}

BEGIN_MESSAGE_MAP(CCourseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//Файл:
	ON_COMMAND(ID_MENU_OPEN, OnMenuOpen)
	ON_COMMAND(ID_MENU_CLOSE, OnMenuClose)
	ON_COMMAND(ID_MENU_SAVE, OnMenuSave)
	ON_COMMAND(ID_MENU_EXIT, OnMenuExit)
	//Редактирование:
	ON_COMMAND(ID_MENU_UNDO, OnMenuUndo)
	ON_COMMAND(ID_MENU_RLACTION, OnMenuRepeatLastAction)
	//Операции:
	ON_COMMAND(ID_MENU_PLAYPAUSE, OnBnClickedPlayPause)
	ON_COMMAND(ID_MENU_STOP, OnBnClickedStop)
	ON_COMMAND(ID_MENU_REPEAT, OnMenuRepeat)
	//Эффекты:
	ON_COMMAND(ID_MENU_CHORUS, OnMenuChorus)
	ON_COMMAND(ID_MENU_DISTORION, OnMenuDistortion)
	ON_COMMAND(ID_MENU_ECHO, OnMenuEcho)
	ON_COMMAND(ID_MENU_FLANGER, OnMenuFlanger)
	ON_COMMAND(ID_MENU_GARGLE, OnMenuGargle)
	ON_COMMAND(ID_MENU_REVERB, OnMenuReverb)
	ON_COMMAND(ID_MENU_I3DL2REVERB, OnMenuI3DL2Reverb)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_PLAY_PAUSE, &CCourseDlg::OnBnClickedPlayPause)
	ON_BN_CLICKED(ID_STOP, &CCourseDlg::OnBnClickedStop)
	ON_CBN_SELCHANGE(ID_EQUALIZERLIST, &CCourseDlg::OnCbnSelchangeEqualizerlist)
	ON_NOTIFY(TCN_SELCHANGE, ID_TABDIFINFO, &CCourseDlg::OnTcnSelchangeTabdifinfo)
	ON_NOTIFY(TCN_SELCHANGING, ID_TABDIFINFO, &CCourseDlg::OnTcnSelchangingTabdifinfo)
END_MESSAGE_MAP()


// CCourseDlg message handlers

BOOL CCourseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//Menu
	m_Menu.LoadMenuW(IDR_MENU1);
	SetMenu(&m_Menu);

	//Variables:
	AlreadyOpen = false; Repeating = false;
	Playing = false; Paused = false;
	Cancel = false;
	secpos = 0; seconds = 0; minutes = 0;
	srand(time(NULL));

	//Tab Control:
	TC_ITEM TabItem;
	m_TabCtrlDifInf.InsertItem(0, _T("История"));
	m_TabCtrlDifInf.InsertItem(1, _T("Информация"));

	TabItem.mask = TCIF_PARAM;
	TabItem.lParam = (LPARAM)&m_History;
	m_TabCtrlDifInf.SetItem(0, &TabItem);
	TabItem.lParam = (LPARAM)&m_InfoType;
	m_TabCtrlDifInf.SetItem(1, &TabItem);

	//Volume:
	m_VolumeSlider.SetRange(0, 100, TRUE);
	m_VolumeSlider.SetPos(0);

	//Эквалайзер:
	m_EqualizerList.InsertString(0, _T("По Умолчанию"));	m_EqualizerList.InsertString(1, _T("Рок"));
	m_EqualizerList.InsertString(2, _T("Рэп"));				m_EqualizerList.InsertString(3, _T("Гранж"));
	m_EqualizerList.InsertString(4, _T("Металл"));			m_EqualizerList.InsertString(5, _T("Танцевальный"));
	m_EqualizerList.InsertString(6, _T("Техно"));			m_EqualizerList.InsertString(7, _T("Кантри"));
	m_EqualizerList.InsertString(8, _T("Джаз"));			m_EqualizerList.InsertString(9, _T("Акустика"));
	m_EqualizerList.InsertString(10, _T("Фолк"));			m_EqualizerList.InsertString(11, _T("Ньюэйдж"));
	m_EqualizerList.InsertString(12, _T("Классика"));		m_EqualizerList.InsertString(13, _T("Блюз"));
	m_EqualizerList.InsertString(14, _T("Ретро"));			m_EqualizerList.InsertString(15, _T("Регги"));
	m_EqualizerList.InsertString(16, _T("Опера"));			m_EqualizerList.InsertString(17, _T("Свинг"));
	m_EqualizerList.InsertString(18, _T("Речь"));			m_EqualizerList.InsertString(19, _T("Музыка 56K"));
	m_EqualizerList.InsertString(20, _T("Музыка 28K"));		m_EqualizerList.InsertString(21, _T("Особая"));
	m_EqualizerList.SelectString(0, _T("По Умолчанию"));


	m_Equlizer125HZ.SetRange(-15, 15, TRUE);
	m_Equlizer125HZ.SetTic(0);	m_Equlizer125HZ.SetTic(7);
	m_Equlizer125HZ.SetTic(-7);	m_Equlizer125HZ.SetPos(0);
	m_Equlizer250HZ.SetRange(-15, 15, TRUE);
	m_Equlizer250HZ.SetTic(0);	m_Equlizer250HZ.SetTic(7);
	m_Equlizer250HZ.SetTic(-7);	m_Equlizer250HZ.SetPos(0);
	m_Equlizer500HZ.SetRange(-15, 15, TRUE);
	m_Equlizer500HZ.SetTic(0);	m_Equlizer500HZ.SetTic(7);
	m_Equlizer500HZ.SetTic(-7);	m_Equlizer500HZ.SetPos(0);
	m_Equlizer1KHZ.SetRange(-15, 15, TRUE);
	m_Equlizer1KHZ.SetTic(0);	m_Equlizer1KHZ.SetTic(7);
	m_Equlizer1KHZ.SetTic(-7);	m_Equlizer1KHZ.SetPos(0);
	m_Equlizer2KHZ.SetRange(-15, 15, TRUE);
	m_Equlizer2KHZ.SetTic(0);	m_Equlizer2KHZ.SetTic(7);
	m_Equlizer2KHZ.SetTic(-7);	m_Equlizer2KHZ.SetPos(0);
	m_Equlizer4KHZ.SetRange(-15, 15, TRUE);
	m_Equlizer4KHZ.SetTic(0);	m_Equlizer4KHZ.SetTic(7);
	m_Equlizer4KHZ.SetTic(-7);	m_Equlizer4KHZ.SetPos(0);
	m_Equlizer8KHZ.SetRange(-15, 15, TRUE);
	m_Equlizer8KHZ.SetTic(0);	m_Equlizer8KHZ.SetTic(7);
	m_Equlizer8KHZ.SetTic(-7);	m_Equlizer8KHZ.SetPos(0);
	m_Equlizer16KHZ.SetRange(-15, 15, TRUE);
	m_Equlizer16KHZ.SetTic(7);	m_Equlizer16KHZ.SetTic(-7);
	m_Equlizer16KHZ.SetTic(0);	m_Equlizer16KHZ.SetPos(0);

	// BASS device initialization
	BASS_Init(-1, 44100, BASS_DEVICE_3D, 0, NULL);
	m_TSpectrum = SetTimer(2, 80, 0);

	HotKeys = LoadAccelerators(AfxGetResourceHandle(),
		MAKEINTRESOURCE(IDR_ACCELERATOR1));

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCourseDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCourseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCourseDlg::OnBnClickedPlayPause()
{
	if (Playing)
	{
		KillTimer(m_TSlide);
		GetDlgItem(ID_PLAY_PAUSE)->SetWindowText(_T("Play"));
		BASS_ChannelPause(m_MainChannel);
		Playing = false;
		Paused = true;
	}
	else
	{
		if (Paused == false)	//Если Stop
		{
			if (secpos != 0)
			{
				QWORD l;
				l = BASS_ChannelSeconds2Bytes(m_MainChannel, secpos);
				BASS_ChannelSetPosition(m_MainChannel, l, BASS_POS_BYTE);
			}
			else
			{
				secpos = 0;
				m_SlidePlayTime.SetPos(0);
				BASS_ChannelSetPosition(m_MainChannel, 0, BASS_POS_BYTE);
			}
			m_TSlide = SetTimer(1, 1000, 0);
			BASS_ChannelPlay(m_MainChannel, FALSE);
		}
		else					//Если Pause
		{
			m_TSlide = SetTimer(1, 1000, 0);
			BASS_ChannelPlay(m_MainChannel, FALSE);
		}
		Playing = true;
		GetDlgItem(ID_PLAY_PAUSE)->SetWindowText(_T("Pause"));
	}
}


void CCourseDlg::OnBnClickedStop()
{
	KillTimer(m_TSlide);
	m_SlidePlayTime.SetPos(0);
	secpos = 0;
	minutes = 0;
	seconds = 0;

	BASS_ChannelStop(m_MainChannel);
	BASS_ChannelSetPosition(m_MainChannel, 0, BASS_POS_BYTE);

	Playing = false;
	Paused = false;
	GetDlgItem(ID_PLAY_PAUSE)->SetWindowText(_T("Play"));
	m_CurrentTime.SetWindowTextW(_T("00:00"));
}


void CCourseDlg::OnCbnSelchangeEqualizerlist()
{
	int i;
	for (i = 0; i < 8; i++)
		BASS_ChannelRemoveFX(m_MainChannel, EqualFXMain[i]);
	EqualFXMain[0] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXMain[1] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);
	EqualFXMain[2] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXMain[3] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);
	EqualFXMain[4] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXMain[5] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);
	EqualFXMain[6] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXMain[7] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);

	for (i = 0; i < 8; i++)
		BASS_ChannelRemoveFX(m_SaveChannel, EqualFXSave[i]);
	EqualFXSave[0] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXSave[1] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);
	EqualFXSave[2] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXSave[3] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);
	EqualFXSave[4] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXSave[5] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);
	EqualFXSave[6] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXSave[7] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);

	BASS_DX8_PARAMEQ equal;
	equal.fBandwidth = 12;
	switch (m_EqualizerList.GetCurSel())
	{
	case 0: //По умолчанию	
		equal.fGain = 0;
		equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 1:	//Рок
		equal.fGain = 2;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 3;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = -1;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(1);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = -1;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(1);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 4;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 4;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 2:	//Рэп
		equal.fGain = 2;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 2;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = -1;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(1);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = -1;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(1);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 4;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 6;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-6);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 3:	//Гранж
		equal.fGain = 0;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = -2;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(2);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 0;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 0;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 2;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 3;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 0;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = -3;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(3);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 4:	//Металл
		equal.fGain = 0;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 0;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 0;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 0;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 3;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 3;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 1;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-1);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 5:	//Танцевальный
		equal.fGain = 5;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-5);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 1;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(-1);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = -1;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(1);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = -1;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(1);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 4;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 4;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 6:	//Техно
		equal.fGain = 4;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = -1;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(1);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = -1;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(1);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = -2;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(2);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 5;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-5);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 5;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-5);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 7:	//Кантри:
		equal.fGain = 0;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 2;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 2;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 0;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 3;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 3;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 8:	//Джаз
		equal.fGain = 0;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 3;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 3;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 3;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 2;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 4;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 4;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 9:	//Акустика
		equal.fGain = 2;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 0;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 0;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 0;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 2;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 2;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 10://Фолк
		equal.fGain = 1;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-1);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 0;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 2;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 0;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 2;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 0;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 11://Ньюэйдж
		equal.fGain = 3;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 0;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 0;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 0;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 1;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-1);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 1;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-1);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 12://Классика
		equal.fGain = 6;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-6);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 3;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 0;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 0;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 2;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 2;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 13://Блюз
		equal.fGain = 2;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 1;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(-1);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 0;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 0;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = -1;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(1);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = -3;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(3);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 14://Ретро
		equal.fGain = 2;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 1;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(-1);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 0;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 0;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = -2;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(2);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = -5;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(5);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 15://Регги
		equal.fGain = 0;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = -3;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(3);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 0;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 3;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 4;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 3;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 4;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 16://Опера
		equal.fGain = 0;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 3;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 4;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 2;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 5;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(-5);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 2;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 0;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 0;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 17://Свинг
		equal.fGain = 0;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 0;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 3;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 3;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(-3);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 2;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = 4;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 4;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(-4);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 18://Речь
		equal.fGain = 2;	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(-2);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = 1;	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(-1);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = 0;	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = 0;	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = 0;	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = 0;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = -2;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(2);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = -5;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(5);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 19://Музыка 56К
		equal.fGain = 0;
		equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = -2;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(2);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 0;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 20://Музыка 28К
		equal.fGain = 0;
		equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = -2;	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos(2);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = -3;	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos(3);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = 0;	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos(0);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	case 21://Особая
		UserSettings.open("EqualUser.txt", ios::in);
		float sl[8];
		int i;
		for (i = 0; i < 8; i++)
		{
			if (UserSettings.eof())
				break;
			UserSettings >> sl[i];

		}
		UserSettings.close();
		equal.fGain = sl[0];	equal.fCenter = 125;
		BASS_FXSetParameters(EqualFXMain[0], &equal);	m_Equlizer125HZ.SetPos((-1)*sl[0]);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		equal.fGain = sl[1];	equal.fCenter = 250;
		BASS_FXSetParameters(EqualFXMain[1], &equal);	m_Equlizer250HZ.SetPos((-1)*sl[1]);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		equal.fGain = sl[2];	equal.fCenter = 500;
		BASS_FXSetParameters(EqualFXMain[2], &equal);	m_Equlizer500HZ.SetPos((-1)*sl[2]);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		equal.fGain = sl[3];	equal.fCenter = 1000;
		BASS_FXSetParameters(EqualFXMain[3], &equal);	m_Equlizer1KHZ.SetPos((-1)*sl[3]);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		equal.fGain = sl[4];	equal.fCenter = 2000;
		BASS_FXSetParameters(EqualFXMain[4], &equal);	m_Equlizer2KHZ.SetPos((-1)*sl[4]);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		equal.fGain = sl[5];	equal.fCenter = 4000;
		BASS_FXSetParameters(EqualFXMain[5], &equal);	m_Equlizer4KHZ.SetPos((-1)*sl[5]);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		equal.fGain = sl[6];	equal.fCenter = 8000;
		BASS_FXSetParameters(EqualFXMain[6], &equal);	m_Equlizer8KHZ.SetPos((-1)*sl[6]);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		equal.fGain = sl[7];	equal.fCenter = 16000;
		BASS_FXSetParameters(EqualFXMain[7], &equal);	m_Equlizer16KHZ.SetPos((-1)*sl[7]);
		BASS_FXSetParameters(EqualFXSave[7], &equal);
		break;
	}
}


void CCourseDlg::OnTcnSelchangeTabdifinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	TCITEM item = { TCIF_PARAM };
	int nTab = m_TabCtrlDifInf.GetCurSel();
	m_TabCtrlDifInf.GetItem(nTab, &item);
	if (item.lParam)
	{
		if (nTab == 1)
		{
			GetDlgItem(ID_INFO)->ShowWindow(SW_SHOW);
		}
		((CWnd*)item.lParam)->ShowWindow(SW_SHOW);
	}
	*pResult = 0;
}


void CCourseDlg::OnTcnSelchangingTabdifinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	TCITEM item = { TCIF_PARAM };
	int nTab = m_TabCtrlDifInf.GetCurSel();
	m_TabCtrlDifInf.GetItem(nTab, &item);
	if (item.lParam)
	{
		if (nTab == 0)
		{
			GetDlgItem(ID_INFO)->ShowWindow(SW_HIDE);
		}
		((CWnd*)item.lParam)->ShowWindow(SW_HIDE);
	}
	*pResult = 0;
}

void CCourseDlg::OnClose()
{
	if (AlreadyOpen)
	{
		int m_ID = MessageBox(
			L"Все несохраненные данные будут потеряны\nСохранить изменения?",
			L"Course RPZ-412",
			MB_ICONQUESTION | MB_YESNOCANCEL
			);
		switch (m_ID)
		{
		case IDYES:
			OnMenuSave();
			if (Cancel == false)
			{
				UserSettings.close();

				if (MyEffects != NULL)
					delete MyEffects;

				KillTimer(m_TSpectrum);
				KillTimer(m_TSlide);
				BASS_ChannelStop(m_MainChannel);
				BASS_StreamFree(m_MainChannel);

				BASS_StreamFree(m_SaveChannel);
				CWnd::OnClose();
			}
			break;
		case IDNO:
			if (MyEffects != NULL)
				delete MyEffects;

			UserSettings.close();

			KillTimer(m_TSpectrum);
			KillTimer(m_TSlide);
			BASS_ChannelStop(m_MainChannel);
			BASS_StreamFree(m_MainChannel);

			BASS_StreamFree(m_SaveChannel);
			CWnd::OnClose();
			break;
		case IDCANCEL:
			// nu i ladno
			break;
		}
	}
	else
	{
		CWnd::OnClose();
	}
}

void CCourseDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_VolumeSlider)
	{
		float pos, vol;
		pos = m_VolumeSlider.GetPos();
		vol = 1 - (pos / 100);
		BASS_ChannelSetAttribute(m_MainChannel, BASS_ATTRIB_VOL, vol);
	}
	if (pScrollBar == (CScrollBar *)&m_Equlizer125HZ)
	{
		BASS_ChannelRemoveFX(m_MainChannel, EqualFXMain[0]);
		EqualFXMain[0] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_ChannelRemoveFX(m_SaveChannel, EqualFXSave[0]);
		EqualFXSave[0] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_DX8_PARAMEQ equal;
		equal.fBandwidth = 12;//
		equal.fCenter = 125;
		equal.fGain = (-1.0)*m_Equlizer125HZ.GetPos();

		UserSettings.open("EqualUser.txt", ios::out);
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				UserSettings << (-1.0)*m_Equlizer125HZ.GetPos() << endl;
				break;
			case 1:
				UserSettings << (-1.0)*m_Equlizer250HZ.GetPos() << endl;
				break;
			case 2:
				UserSettings << (-1.0)*m_Equlizer500HZ.GetPos() << endl;
				break;
			case 3:
				UserSettings << (-1.0)*m_Equlizer1KHZ.GetPos() << endl;
				break;
			case 4:
				UserSettings << (-1.0)*m_Equlizer2KHZ.GetPos() << endl;
				break;
			case 5:
				UserSettings << (-1.0)*m_Equlizer4KHZ.GetPos() << endl;
				break;
			case 6:
				UserSettings << (-1.0)*m_Equlizer8KHZ.GetPos() << endl;
				break;
			case 7:
				UserSettings << (-1.0)*m_Equlizer16KHZ.GetPos() << endl;
				break;
			}
		}
		UserSettings.close();

		BASS_FXSetParameters(EqualFXMain[0], &equal);
		BASS_FXSetParameters(EqualFXSave[0], &equal);

		m_EqualizerList.SelectString(21, _T("Особая"));
	}
	if (pScrollBar == (CScrollBar *)&m_Equlizer250HZ)
	{
		BASS_ChannelRemoveFX(m_MainChannel, EqualFXMain[1]);
		EqualFXMain[1] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_ChannelRemoveFX(m_SaveChannel, EqualFXSave[1]);
		EqualFXSave[1] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_DX8_PARAMEQ equal;
		equal.fBandwidth = 12;
		equal.fCenter = 250;
		equal.fGain = (-1.0)*m_Equlizer250HZ.GetPos();

		UserSettings.open("EqualUser.txt", ios::out);
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				UserSettings << (-1.0)*m_Equlizer125HZ.GetPos() << endl;
				break;
			case 1:
				UserSettings << (-1.0)*m_Equlizer250HZ.GetPos() << endl;
				break;
			case 2:
				UserSettings << (-1.0)*m_Equlizer500HZ.GetPos() << endl;
				break;
			case 3:
				UserSettings << (-1.0)*m_Equlizer1KHZ.GetPos() << endl;
				break;
			case 4:
				UserSettings << (-1.0)*m_Equlizer2KHZ.GetPos() << endl;
				break;
			case 5:
				UserSettings << (-1.0)*m_Equlizer4KHZ.GetPos() << endl;
				break;
			case 6:
				UserSettings << (-1.0)*m_Equlizer8KHZ.GetPos() << endl;
				break;
			case 7:
				UserSettings << (-1.0)*m_Equlizer16KHZ.GetPos() << endl;
				break;
			}
		}
		UserSettings.close();

		BASS_FXSetParameters(EqualFXMain[1], &equal);
		BASS_FXSetParameters(EqualFXSave[1], &equal);

		m_EqualizerList.SelectString(21, _T("Особая"));
	}
	if (pScrollBar == (CScrollBar *)&m_Equlizer500HZ)
	{
		BASS_ChannelRemoveFX(m_MainChannel, EqualFXMain[2]);
		EqualFXMain[2] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_ChannelRemoveFX(m_SaveChannel, EqualFXSave[2]);
		EqualFXSave[2] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_DX8_PARAMEQ equal;
		equal.fBandwidth = 12;
		equal.fCenter = 500;
		equal.fGain = (-1.0)*m_Equlizer500HZ.GetPos();

		UserSettings.open("EqualUser.txt", ios::out);
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				UserSettings << (-1.0)*m_Equlizer125HZ.GetPos() << endl;
				break;
			case 1:
				UserSettings << (-1.0)*m_Equlizer250HZ.GetPos() << endl;
				break;
			case 2:
				UserSettings << (-1.0)*m_Equlizer500HZ.GetPos() << endl;
				break;
			case 3:
				UserSettings << (-1.0)*m_Equlizer1KHZ.GetPos() << endl;
				break;
			case 4:
				UserSettings << (-1.0)*m_Equlizer2KHZ.GetPos() << endl;
				break;
			case 5:
				UserSettings << (-1.0)*m_Equlizer4KHZ.GetPos() << endl;
				break;
			case 6:
				UserSettings << (-1.0)*m_Equlizer8KHZ.GetPos() << endl;
				break;
			case 7:
				UserSettings << (-1.0)*m_Equlizer16KHZ.GetPos() << endl;
				break;
			}
		}
		UserSettings.close();

		BASS_FXSetParameters(EqualFXMain[2], &equal);
		BASS_FXSetParameters(EqualFXSave[2], &equal);

		m_EqualizerList.SelectString(21, _T("Особая"));
	}
	if (pScrollBar == (CScrollBar *)&m_Equlizer1KHZ)
	{
		BASS_ChannelRemoveFX(m_MainChannel, EqualFXMain[3]);
		EqualFXMain[3] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_ChannelRemoveFX(m_SaveChannel, EqualFXSave[3]);
		EqualFXSave[3] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_DX8_PARAMEQ equal;
		equal.fBandwidth = 12;
		equal.fCenter = 1000;
		equal.fGain = (-1.0)*m_Equlizer1KHZ.GetPos();

		UserSettings.open("EqualUser.txt", ios::out);
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				UserSettings << (-1.0)*m_Equlizer125HZ.GetPos() << endl;
				break;
			case 1:
				UserSettings << (-1.0)*m_Equlizer250HZ.GetPos() << endl;
				break;
			case 2:
				UserSettings << (-1.0)*m_Equlizer500HZ.GetPos() << endl;
				break;
			case 3:
				UserSettings << (-1.0)*m_Equlizer1KHZ.GetPos() << endl;
				break;
			case 4:
				UserSettings << (-1.0)*m_Equlizer2KHZ.GetPos() << endl;
				break;
			case 5:
				UserSettings << (-1.0)*m_Equlizer4KHZ.GetPos() << endl;
				break;
			case 6:
				UserSettings << (-1.0)*m_Equlizer8KHZ.GetPos() << endl;
				break;
			case 7:
				UserSettings << (-1.0)*m_Equlizer16KHZ.GetPos() << endl;
				break;
			}
		}
		UserSettings.close();

		BASS_FXSetParameters(EqualFXMain[3], &equal);
		BASS_FXSetParameters(EqualFXSave[3], &equal);

		m_EqualizerList.SelectString(21, _T("Особая"));
	}
	if (pScrollBar == (CScrollBar *)&m_Equlizer2KHZ)
	{
		BASS_ChannelRemoveFX(m_MainChannel, EqualFXMain[4]);
		EqualFXMain[4] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_ChannelRemoveFX(m_SaveChannel, EqualFXSave[4]);
		EqualFXSave[4] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_DX8_PARAMEQ equal;
		equal.fBandwidth = 12;
		equal.fCenter = 2000;
		equal.fGain = (-1.0)*m_Equlizer2KHZ.GetPos();

		UserSettings.open("EqualUser.txt", ios::out);
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				UserSettings << (-1.0)*m_Equlizer125HZ.GetPos() << endl;
				break;
			case 1:
				UserSettings << (-1.0)*m_Equlizer250HZ.GetPos() << endl;
				break;
			case 2:
				UserSettings << (-1.0)*m_Equlizer500HZ.GetPos() << endl;
				break;
			case 3:
				UserSettings << (-1.0)*m_Equlizer1KHZ.GetPos() << endl;
				break;
			case 4:
				UserSettings << (-1.0)*m_Equlizer2KHZ.GetPos() << endl;
				break;
			case 5:
				UserSettings << (-1.0)*m_Equlizer4KHZ.GetPos() << endl;
				break;
			case 6:
				UserSettings << (-1.0)*m_Equlizer8KHZ.GetPos() << endl;
				break;
			case 7:
				UserSettings << (-1.0)*m_Equlizer16KHZ.GetPos() << endl;
				break;
			}
		}
		UserSettings.close();

		BASS_FXSetParameters(EqualFXMain[4], &equal);
		BASS_FXSetParameters(EqualFXSave[4], &equal);

		m_EqualizerList.SelectString(21, _T("Особая"));
	}
	if (pScrollBar == (CScrollBar *)&m_Equlizer4KHZ)
	{
		BASS_ChannelRemoveFX(m_MainChannel, EqualFXMain[5]);
		EqualFXMain[5] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_ChannelRemoveFX(m_SaveChannel, EqualFXSave[5]);
		EqualFXSave[5] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_DX8_PARAMEQ equal;
		equal.fBandwidth = 12;
		equal.fCenter = 4000;
		equal.fGain = (-1.0)*m_Equlizer4KHZ.GetPos();

		UserSettings.open("EqualUser.txt", ios::out);
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				UserSettings << (-1.0)*m_Equlizer125HZ.GetPos() << endl;
				break;
			case 1:
				UserSettings << (-1.0)*m_Equlizer250HZ.GetPos() << endl;
				break;
			case 2:
				UserSettings << (-1.0)*m_Equlizer500HZ.GetPos() << endl;
				break;
			case 3:
				UserSettings << (-1.0)*m_Equlizer1KHZ.GetPos() << endl;
				break;
			case 4:
				UserSettings << (-1.0)*m_Equlizer2KHZ.GetPos() << endl;
				break;
			case 5:
				UserSettings << (-1.0)*m_Equlizer4KHZ.GetPos() << endl;
				break;
			case 6:
				UserSettings << (-1.0)*m_Equlizer8KHZ.GetPos() << endl;
				break;
			case 7:
				UserSettings << (-1.0)*m_Equlizer16KHZ.GetPos() << endl;
				break;
			}
		}
		UserSettings.close();

		BASS_FXSetParameters(EqualFXMain[5], &equal);
		BASS_FXSetParameters(EqualFXSave[5], &equal);

		m_EqualizerList.SelectString(21, _T("Особая"));
	}
	if (pScrollBar == (CScrollBar *)&m_Equlizer8KHZ)
	{
		BASS_ChannelRemoveFX(m_MainChannel, EqualFXMain[6]);
		EqualFXMain[6] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_ChannelRemoveFX(m_SaveChannel, EqualFXSave[6]);
		EqualFXSave[6] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_DX8_PARAMEQ equal;
		equal.fBandwidth = 12;
		equal.fCenter = 8000;
		equal.fGain = (-1.0)*m_Equlizer8KHZ.GetPos();

		UserSettings.open("EqualUser.txt", ios::out);
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				UserSettings << (-1.0)*m_Equlizer125HZ.GetPos() << endl;
				break;
			case 1:
				UserSettings << (-1.0)*m_Equlizer250HZ.GetPos() << endl;
				break;
			case 2:
				UserSettings << (-1.0)*m_Equlizer500HZ.GetPos() << endl;
				break;
			case 3:
				UserSettings << (-1.0)*m_Equlizer1KHZ.GetPos() << endl;
				break;
			case 4:
				UserSettings << (-1.0)*m_Equlizer2KHZ.GetPos() << endl;
				break;
			case 5:
				UserSettings << (-1.0)*m_Equlizer4KHZ.GetPos() << endl;
				break;
			case 6:
				UserSettings << (-1.0)*m_Equlizer8KHZ.GetPos() << endl;
				break;
			case 7:
				UserSettings << (-1.0)*m_Equlizer16KHZ.GetPos() << endl;
				break;
			}
		}
		UserSettings.close();

		BASS_FXSetParameters(EqualFXMain[6], &equal);
		BASS_FXSetParameters(EqualFXSave[6], &equal);

		m_EqualizerList.SelectString(21, _T("Особая"));
	}
	if (pScrollBar == (CScrollBar *)&m_Equlizer16KHZ)
	{
		BASS_ChannelRemoveFX(m_MainChannel, EqualFXMain[7]);
		EqualFXMain[7] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_ChannelRemoveFX(m_SaveChannel, EqualFXSave[7]);
		EqualFXSave[7] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);

		BASS_DX8_PARAMEQ equal;
		equal.fBandwidth = 12;
		equal.fCenter = 16000;
		equal.fGain = (-1.0)*m_Equlizer16KHZ.GetPos();

		UserSettings.open("EqualUser.txt", ios::out);
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				UserSettings << (-1.0)*m_Equlizer125HZ.GetPos() << endl;
				break;
			case 1:
				UserSettings << (-1.0)*m_Equlizer250HZ.GetPos() << endl;
				break;
			case 2:
				UserSettings << (-1.0)*m_Equlizer500HZ.GetPos() << endl;
				break;
			case 3:
				UserSettings << (-1.0)*m_Equlizer1KHZ.GetPos() << endl;
				break;
			case 4:
				UserSettings << (-1.0)*m_Equlizer2KHZ.GetPos() << endl;
				break;
			case 5:
				UserSettings << (-1.0)*m_Equlizer4KHZ.GetPos() << endl;
				break;
			case 6:
				UserSettings << (-1.0)*m_Equlizer8KHZ.GetPos() << endl;
				break;
			case 7:
				UserSettings << (-1.0)*m_Equlizer16KHZ.GetPos() << endl;
				break;
			}
		}
		UserSettings.close();

		BASS_FXSetParameters(EqualFXMain[7], &equal);
		BASS_FXSetParameters(EqualFXSave[7], &equal);

		m_EqualizerList.SelectString(21, _T("Особая"));
	}
	else
	{
		CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
	}
}

void CCourseDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SlidePlayTime)
	{
		CString m, s;
		KillTimer(m_TSlide);
		BASS_ChannelStop(m_MainChannel);
		QWORD l;
		double pos = m_SlidePlayTime.GetPos();
		l = BASS_ChannelSeconds2Bytes(m_MainChannel, pos);

		secpos = pos;
		if (secpos == (int)SongLength)
		{
			minutes = 0;
			seconds = 0;
			m_SlidePlayTime.SetPos(0);
			BASS_ChannelStop(m_MainChannel);
			BASS_ChannelSetPosition(m_MainChannel, 0, BASS_POS_BYTE);
		}
		else
		{
			minutes = pos / 60;
			seconds = pos - minutes * 60;
			BASS_ChannelSetPosition(m_MainChannel, l, BASS_POS_BYTE);
		}

		m.Format(_T("%d"), minutes);
		s.Format(_T("%d"), seconds);
		if (minutes < 10)
		{
			if (seconds < 10)
			{
				m_CurrentTime.SetWindowTextW(_T("0") + m + _T(":0") + s);
			}
			else
			{
				m_CurrentTime.SetWindowTextW(_T("0") + m + _T(":") + s);
			}
		}
		else
		{
			if (seconds < 10)
			{
				m_CurrentTime.SetWindowTextW(m + _T(":0") + s);
			}
			else
			{
				m_CurrentTime.SetWindowTextW(m + _T(":") + s);
			}
		}
		if (Playing)
		{
			m_TSlide = SetTimer(1, 1000, 0);
			BASS_ChannelPlay(m_MainChannel, FALSE);
		}
	}
	else
	{
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void CCourseDlg::OnMenuOpen()
{
	if (AlreadyOpen)
	{
		OnMenuClose();
		if (AlreadyOpen == false)
		{
			OnMenuOpen();
		}
	}
	else
	{
		CFileDialog openDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
			_T("Аудио Файлы|*.mp3||"));
		CString s, m;

		int result = openDialog.DoModal();
		if (result == IDOK)
		{
			PathName = openDialog.GetPathName();

			m_MainChannel = BASS_StreamCreateFile(FALSE, PathName, 0, 0, 0);
			EqualFXMain[0] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXMain[1] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);
			EqualFXMain[2] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXMain[3] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);
			EqualFXMain[4] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXMain[5] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);
			EqualFXMain[6] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXMain[7] = BASS_ChannelSetFX(m_MainChannel, BASS_FX_DX8_PARAMEQ, 0);

			m_SaveChannel = BASS_StreamCreateFile(FALSE, PathName, 0, 0, BASS_STREAM_DECODE);
			EqualFXSave[0] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXSave[1] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);
			EqualFXSave[2] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXSave[3] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);
			EqualFXSave[4] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXSave[5] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);
			EqualFXSave[6] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);	EqualFXSave[7] = BASS_ChannelSetFX(m_SaveChannel, BASS_FX_DX8_PARAMEQ, 0);

			QWORD len;

			len = BASS_ChannelGetLength(m_MainChannel, BASS_POS_BYTE); // the length in bytes
			SongLength = BASS_ChannelBytes2Seconds(m_MainChannel, len);

			secpos = 0;
			minutes = SongLength / 60;
			seconds = ((int)SongLength % 60);
			m.Format(_T("%d"), minutes);
			s.Format(_T("%d"), seconds);
			m_TotalTime.SetWindowTextW(m + s);
			if (minutes < 10)
			{
				if (seconds < 10)
				{
					m_TotalTime.SetWindowTextW(_T("0") + m + _T(":0") + s);
				}
				else
				{
					m_TotalTime.SetWindowTextW(_T("0") + m + _T(":") + s);
				}
			}
			else
			{
				if (seconds < 10)
				{
					m_TotalTime.SetWindowTextW(m + _T(":0") + s);
				}
				else
				{
					m_TotalTime.SetWindowTextW(m + _T(":") + s);
				}
			}
			minutes = 0;
			seconds = 0;
			m_SlidePlayTime.SetRange(0, SongLength, TRUE);

			GetInformation();
			m_History.AddString(_T("Открытие файла"));
			MyEffects = new TEffects;

			EnabledDisabled(true);
			AlreadyOpen = true;
			UpdateData(false);
		}
	}
}

void CCourseDlg::OnMenuSave()
{
	BASS_CHANNELINFO ChanInfo;
	CString Path, BpS;
	int c;
	char *command;

	CFileDialog	SaveDialog(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		_T("MP3 Файл|*.mp3||"));
	SaveDialog.m_ofn.lpstrTitle = _T("Сохранить аудиофайл");

	int result = SaveDialog.DoModal();
	if (result == IDOK)
	{	
		m_Saving = "Идет сохранение.\nПодождите пожайлуста...";
		UpdateData(false);
		OnBnClickedStop();
		KillTimer(m_TSpectrum);
		m_Menu.EnableMenuItem(ID_MENU_CLOSE, MF_DISABLED);	//Закрыть файл
		m_Menu.EnableMenuItem(ID_MENU_SAVE, MF_DISABLED);	//Сохранить
		//Редактирование:
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_DISABLED);	//Отменить последнее действие
		m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_DISABLED);	//Повторить последнее действие
		//Операции:
		m_Menu.EnableMenuItem(ID_MENU_PLAYPAUSE, MF_DISABLED);	//Воспроизвести/приостановить
		m_Menu.EnableMenuItem(ID_MENU_STOP, MF_DISABLED);	//Остановить
		m_Menu.EnableMenuItem(ID_MENU_REPEAT, MF_DISABLED);	//Повтор
		m_Menu.CheckMenuItem(ID_MENU_REPEAT, MF_UNCHECKED);
		//Эффекты:
		m_Menu.EnableMenuItem(ID_MENU_CHORUS, MF_DISABLED);	//Хор
		m_Menu.EnableMenuItem(ID_MENU_DISTORION, MF_DISABLED);	//Искажение
		m_Menu.EnableMenuItem(ID_MENU_ECHO, MF_DISABLED);	//Эхо
		m_Menu.EnableMenuItem(ID_MENU_FLANGER, MF_DISABLED);	//Фланжер
		m_Menu.EnableMenuItem(ID_MENU_GARGLE, MF_DISABLED);	//Амплитудная модуляция
		m_Menu.EnableMenuItem(ID_MENU_REVERB, MF_DISABLED);	//Реверберация
		m_Menu.EnableMenuItem(ID_MENU_I3DL2REVERB, MF_DISABLED);	//I3DL2 Реверберация
		//Window:
		GetDlgItem(ID_PLAY_PAUSE)->EnableWindow(0);		//Play || Pause
		GetDlgItem(ID_STOP)->EnableWindow(0);			//Stop
		GetDlgItem(ID_SONGTIME)->EnableWindow(0);		//Полоса прокрутки песни
		GetDlgItem(ID_VOLUME)->EnableWindow(0);			//Регулятор громкости
		GetDlgItem(ID_HISTORY)->EnableWindow(0);		//История
		GetDlgItem(ID_INFOTYPE)->EnableWindow(0);		//Тип информации
		GetDlgItem(ID_INFO)->EnableWindow(0);			//Информация
		GetDlgItem(ID_EQUALIZERLIST)->EnableWindow(0);	//Готовые настройки эквалайзера
		//Графический эквалайзер:
		GetDlgItem(ID_EQUALIZER125HZ)->EnableWindow(0);	//125Гц
		GetDlgItem(ID_EQUALIZER250HZ)->EnableWindow(0);	//250Гц
		GetDlgItem(ID_EQUALIZER500HZ)->EnableWindow(0);	//500Гц
		GetDlgItem(ID_EQUALIZER1KHZ)->EnableWindow(0);	//1КГц
		GetDlgItem(ID_EQUALIZER2KHZ)->EnableWindow(0);	//2КГц
		GetDlgItem(ID_EQUALIZER4KHZ)->EnableWindow(0);	//4КГц
		GetDlgItem(ID_EQUALIZER8KHZ)->EnableWindow(0);	//8КГц
		GetDlgItem(ID_EQUALIZER16KHZ)->EnableWindow(0);	//16КГц

		int m_ID = MessageBox(
			L"Применить эквалайзер к сохраняемому файлу?",
			L"Course RPZ-412",
			MB_ICONQUESTION | MB_YESNO
			);
		if (m_ID == IDNO)
		{
			for (int i = 0; i < 8; i++)
			{
				BASS_ChannelRemoveFX(m_SaveChannel, EqualFXSave[i]);
				BASS_ChannelRemoveFX(m_MainChannel, EqualFXSave[i]);
			}
			m_EqualizerList.SelectString(0, _T("По Умолчанию"));
			//Графический эквалайзер:
			m_Equlizer125HZ.SetPos(0);
			m_Equlizer250HZ.SetPos(0);
			m_Equlizer500HZ.SetPos(0);
			m_Equlizer1KHZ.SetPos(0);
			m_Equlizer2KHZ.SetPos(0);
			m_Equlizer4KHZ.SetPos(0);
			m_Equlizer8KHZ.SetPos(0);
			m_Equlizer16KHZ.SetPos(0);
		}

		Path = SaveDialog.GetPathName();
		command = new char[Path.GetLength() + 100];
		c = (int)((BASS_StreamGetFilePosition(m_SaveChannel, BASS_FILEPOS_END) / (125 * BASS_ChannelBytes2Seconds(m_SaveChannel, BASS_ChannelGetLength(m_SaveChannel, BASS_POS_BYTE)))) + 0.5);
		BpS.Format(_T("%d"), c);
		strcpy(command, "lame --silent -b ");
		strcat(command, CT2A(BpS));
		strcat(command, " -q 0 - ");
		if (Path == PathName)
		{
			PathName.Delete(PathName.GetLength() - 4, 4);
			strcat(command, CT2A(PathName));
			strcat(command, "-Copy.mp3");
		}
		else
		{
			strcat(command, CT2A(Path));
			strcat(command, ".mp3");
		}
		hencode = BASS_Encode_Start(m_SaveChannel, command, 0, NULL, 0);
		while (BASS_ChannelIsActive(m_SaveChannel))
		{
			char temp[20000];
			BASS_ChannelGetData(m_SaveChannel, temp, 20000);
			fflush(stdout);
		}
		BASS_Encode_Stop(hencode);
		Cancel = false;

		BASS_ChannelSetPosition(m_SaveChannel, 0, BASS_POS_BYTE);
		delete[]command;

		m_TSpectrum = SetTimer(2, 80, 0);
		EnabledDisabled(true);
		
		if (!MyEffects->IsEmpty())
		{
			m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
			m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_ENABLED);
		}
		m_Saving = "";
		UpdateData(false);
		MessageBox(_T("Сохранение прошло успешно."), _T("Выполнено"), MB_ICONINFORMATION);
	}
	if (result == IDCANCEL)
	{
		Cancel = true;
	}
}

void CCourseDlg::OnMenuClose()
{
	int m_ID = MessageBox(
		L"Все несохраненные данные будут потеряны\nСохранить изменения?",
		L"Course RPZ-412",
		MB_ICONQUESTION | MB_YESNOCANCEL
		);
	switch (m_ID)
	{
	case IDYES:
		OnMenuSave();
		if (Cancel == false)
		{
			AlreadyOpen = false; Repeating = false;
			Playing = false; Paused = false;
			secpos = 0; seconds = 0; minutes = 0;
			GetDlgItem(ID_PLAY_PAUSE)->SetWindowText(_T("Play"));
			m_TotalTime.SetWindowTextW(_T("00:00"));
			m_CurrentTime.SetWindowTextW(_T("00:00"));

			if (MyEffects != NULL)
				delete MyEffects;

			m_SlidePlayTime.SetRange(0, 0, TRUE);
			m_SlidePlayTime.SetPos(0);

			EnabledDisabled(false);
			KillTimer(m_TSlide);
			BASS_FXReset(m_MainChannel);
			BASS_FXReset(m_SaveChannel);

			BASS_ChannelStop(m_MainChannel);
			BASS_StreamFree(m_MainChannel);
			BASS_StreamFree(m_SaveChannel);
		}
		break;
	case IDNO:
		AlreadyOpen = false; Repeating = false;
		Playing = false; Paused = false;
		secpos = 0; seconds = 0; minutes = 0;

		GetDlgItem(ID_PLAY_PAUSE)->SetWindowText(_T("Play"));
		m_TotalTime.SetWindowTextW(_T("00:00"));
		m_CurrentTime.SetWindowTextW(_T("00:00"));

		if (MyEffects != NULL)
			delete MyEffects;

		m_SlidePlayTime.SetRange(0, 0, TRUE);
		m_SlidePlayTime.SetPos(0);

		EnabledDisabled(false);
		KillTimer(m_TSlide);
		BASS_FXReset(m_MainChannel);
		BASS_FXReset(m_SaveChannel);

		BASS_ChannelStop(m_MainChannel);
		BASS_StreamFree(m_MainChannel);
		BASS_StreamFree(m_SaveChannel);
		break;
	case IDCANCEL:
		
		break;
	}
}

void CCourseDlg::OnMenuUndo()
{
	MyEffects->RemoveFromHistory(&m_MainChannel, &m_SaveChannel);
	m_History.DeleteString(m_History.GetCount() - 1);
	if (MyEffects->IsEmpty())
	{
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_DISABLED);
		m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_DISABLED);
	}
}

void CCourseDlg::OnMenuRepeatLastAction()
{
	CString ef;
	MyEffects->RLAction(&ef, &m_MainChannel, &m_SaveChannel);
	if (ef == "chorus")
		m_History.AddString(_T("Добавлен эффект: Хор"));
	if (ef == "distortion")
		m_History.AddString(_T("Добавлен эффект: Искажение"));
	if (ef == "echo")
		m_History.AddString(_T("Добавлен эффект: Эхо"));
	if (ef == "flanger")
		m_History.AddString(_T("Добавлен эффект: Фланжер"));
	if (ef == "gargle")
		m_History.AddString(_T("Добавлен эффект: Амплитудная модуляция"));
	if (ef == "i3dl2reverb")
		m_History.AddString(_T("Добавлен эффект: I3DL2 Реверберация"));
	if (ef == "reverb")
		m_History.AddString(_T("Добавлен эффект: Реверберация"));
}

void CCourseDlg::OnMenuRepeat()
{
	if (m_Menu.CheckMenuItem(ID_MENU_REPEAT, MF_CHECKED))
	{
		Repeating = false;
		m_Menu.CheckMenuItem(ID_MENU_REPEAT, MF_UNCHECKED);
	}
	else
	{
		m_Menu.CheckMenuItem(ID_MENU_REPEAT, MF_CHECKED);
		Repeating = true;
	}
}

void CCourseDlg::OnMenuExit()
{
	ASSERT(AfxGetMainWnd() != NULL);
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

void CCourseDlg::EnabledDisabled(bool enable)
{
	if (enable)
	{
		//Menu:
		//Файл:
		m_Menu.EnableMenuItem(ID_MENU_CLOSE, MF_ENABLED);	//Закрыть файл
		m_Menu.EnableMenuItem(ID_MENU_SAVE, MF_ENABLED);	//Сохранить
		//Операции:
		m_Menu.EnableMenuItem(ID_MENU_PLAYPAUSE, MF_ENABLED);	//Воспроизвести/приостановить
		m_Menu.EnableMenuItem(ID_MENU_STOP, MF_ENABLED);	//Остановить
		m_Menu.EnableMenuItem(ID_MENU_REPEAT, MF_ENABLED);	//Повтор
		//Эффекты:
		m_Menu.EnableMenuItem(ID_MENU_CHORUS, MF_ENABLED);	//Хор
		m_Menu.EnableMenuItem(ID_MENU_DISTORION, MF_ENABLED);	//Искажение
		m_Menu.EnableMenuItem(ID_MENU_ECHO, MF_ENABLED);	//Эхо
		m_Menu.EnableMenuItem(ID_MENU_FLANGER, MF_ENABLED);	//Фланжер
		m_Menu.EnableMenuItem(ID_MENU_GARGLE, MF_ENABLED);	//Амплитудная модуляция
		m_Menu.EnableMenuItem(ID_MENU_REVERB, MF_ENABLED);	//Реверберация
		m_Menu.EnableMenuItem(ID_MENU_I3DL2REVERB, MF_ENABLED);	//I3DL2 Реверберация
		//Window:
		GetDlgItem(ID_PLAY_PAUSE)->EnableWindow(1);		//Play || Pause
		GetDlgItem(ID_STOP)->EnableWindow(1);			//Stop
		GetDlgItem(ID_SONGTIME)->EnableWindow(1);		//Полоса прокрутки песни
		GetDlgItem(ID_VOLUME)->EnableWindow(1);			//Регулятор громкости
		GetDlgItem(ID_HISTORY)->EnableWindow(1);		//История
		GetDlgItem(ID_INFOTYPE)->EnableWindow(1);		//Тип информации
		GetDlgItem(ID_INFO)->EnableWindow(1);			//Информация
		GetDlgItem(ID_EQUALIZERLIST)->EnableWindow(1);	//Готовые настройки эквалайзера
		//Графический эквалайзер:
		GetDlgItem(ID_EQUALIZER125HZ)->EnableWindow(1);	//125Гц
		GetDlgItem(ID_EQUALIZER250HZ)->EnableWindow(1);	//250Гц
		GetDlgItem(ID_EQUALIZER500HZ)->EnableWindow(1);	//500Гц
		GetDlgItem(ID_EQUALIZER1KHZ)->EnableWindow(1);	//1КГц
		GetDlgItem(ID_EQUALIZER2KHZ)->EnableWindow(1);	//2КГц
		GetDlgItem(ID_EQUALIZER4KHZ)->EnableWindow(1);	//4КГц
		GetDlgItem(ID_EQUALIZER8KHZ)->EnableWindow(1);	//8КГц
		GetDlgItem(ID_EQUALIZER16KHZ)->EnableWindow(1);	//16КГц

	}
	else
	{
		//Menu:
		//Файл:
		m_Menu.EnableMenuItem(ID_MENU_CLOSE, MF_DISABLED);	//Закрыть файл
		m_Menu.EnableMenuItem(ID_MENU_SAVE, MF_DISABLED);	//Сохранить
		//Редактирование:
		m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_DISABLED);	//Отменить последнее действие
		m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_DISABLED);	//Повторить последнее действие
		//Операции:
		m_Menu.EnableMenuItem(ID_MENU_PLAYPAUSE, MF_DISABLED);	//Воспроизвести/приостановить
		m_Menu.EnableMenuItem(ID_MENU_STOP, MF_DISABLED);	//Остановить
		m_Menu.EnableMenuItem(ID_MENU_REPEAT, MF_DISABLED);	//Повтор
		m_Menu.CheckMenuItem(ID_MENU_REPEAT, MF_UNCHECKED);
		//Эффекты:
		m_Menu.EnableMenuItem(ID_MENU_CHORUS, MF_DISABLED);	//Хор
		m_Menu.EnableMenuItem(ID_MENU_DISTORION, MF_DISABLED);	//Искажение
		m_Menu.EnableMenuItem(ID_MENU_ECHO, MF_DISABLED);	//Эхо
		m_Menu.EnableMenuItem(ID_MENU_FLANGER, MF_DISABLED);	//Фланжер
		m_Menu.EnableMenuItem(ID_MENU_GARGLE, MF_DISABLED);	//Амплитудная модуляция
		m_Menu.EnableMenuItem(ID_MENU_REVERB, MF_DISABLED);	//Реверберация
		m_Menu.EnableMenuItem(ID_MENU_I3DL2REVERB, MF_DISABLED);	//I3DL2 Реверберация

		//Window:
		GetDlgItem(ID_PLAY_PAUSE)->EnableWindow(0);		//Play || Pause
		GetDlgItem(ID_STOP)->EnableWindow(0);			//Stop
		GetDlgItem(ID_SONGTIME)->EnableWindow(0);		//Полоса прокрутки песни
		GetDlgItem(ID_VOLUME)->EnableWindow(0);			//Регулятор громкости
		m_VolumeSlider.SetPos(0);
		GetDlgItem(ID_HISTORY)->EnableWindow(0);		//История
		m_History.ResetContent();
		GetDlgItem(ID_INFOTYPE)->EnableWindow(0);		//Тип информации
		m_InfoType.ResetContent();
		GetDlgItem(ID_INFO)->EnableWindow(0);			//Информация
		m_Info.ResetContent();
		GetDlgItem(ID_EQUALIZERLIST)->EnableWindow(0);	//Готовые настройки эквалайзера
		m_EqualizerList.SelectString(0, _T("По Умолчанию"));
		//Графический эквалайзер:
		GetDlgItem(ID_EQUALIZER125HZ)->EnableWindow(0);	//125Гц
		m_Equlizer125HZ.SetPos(0);
		GetDlgItem(ID_EQUALIZER250HZ)->EnableWindow(0);	//250Гц
		m_Equlizer250HZ.SetPos(0);
		GetDlgItem(ID_EQUALIZER500HZ)->EnableWindow(0);	//500Гц
		m_Equlizer500HZ.SetPos(0);
		GetDlgItem(ID_EQUALIZER1KHZ)->EnableWindow(0);	//1КГц
		m_Equlizer1KHZ.SetPos(0);
		GetDlgItem(ID_EQUALIZER2KHZ)->EnableWindow(0);	//2КГц
		m_Equlizer2KHZ.SetPos(0);
		GetDlgItem(ID_EQUALIZER4KHZ)->EnableWindow(0);	//4КГц
		m_Equlizer4KHZ.SetPos(0);
		GetDlgItem(ID_EQUALIZER8KHZ)->EnableWindow(0);	//8КГц
		m_Equlizer8KHZ.SetPos(0);
		GetDlgItem(ID_EQUALIZER16KHZ)->EnableWindow(0);	//16КГц
		m_Equlizer16KHZ.SetPos(0);
	}
}

void CCourseDlg::GetInformation()
{
	CString HZ, Ch, BpS;
	int c;
	BASS_CHANNELINFO ChanInfo;
	BASS_ChannelGetInfo(m_SaveChannel, &ChanInfo);

	m_InfoType.AddString(_T("Путь к файлу"));
	m_Info.AddString(PathName);

	c = (int)(ChanInfo.freq);
	HZ.Format(_T("%d"), c);
	m_InfoType.AddString(_T("Частота"));
	m_InfoType.AddString(_T("дискретизации"));
	m_Info.AddString(HZ + _T(" Гц"));
	m_Info.AddString(_T(""));

	c = (int)(ChanInfo.chans);
	if (c == 1)
	{
		Ch = "Моно";
	}
	if (c == 2)
	{
		Ch = "Стерео";
	}
	m_InfoType.AddString(_T("Каналы"));
	m_Info.AddString(Ch);

	c = (int)((BASS_StreamGetFilePosition(m_SaveChannel, BASS_FILEPOS_END) / (125 * BASS_ChannelBytes2Seconds(m_SaveChannel, BASS_ChannelGetLength(m_SaveChannel, BASS_POS_BYTE)))) + 0.5);
	BpS.Format(_T("%d"), c);
	m_InfoType.AddString(_T("Скорость потока"));
	m_Info.AddString(BpS + _T("кбит в сек"));
}

void CCourseDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		CString s, m;
		m_SlidePlayTime.SetPos(secpos);
		secpos++;
		seconds++;
		if ((seconds % 60) == 0)
		{
			minutes++;
			m.Format(_T("%d"), minutes);
			seconds = 0;
			s.Format(_T("%d"), seconds);
			if (minutes < 10)
			{
				if (seconds < 10)
				{
					m_CurrentTime.SetWindowTextW(_T("0") + m + _T(":0") + s);
				}
				else
				{
					m_CurrentTime.SetWindowTextW(_T("0") + m + _T(":") + s);
				}
			}
			else
			{
				if (seconds < 10)
				{
					m_CurrentTime.SetWindowTextW(m + _T(":0") + s);
				}
				else
				{
					m_CurrentTime.SetWindowTextW(m + _T(":") + s);
				}
			}
		}
		else
		{
			m.Format(_T("%d"), minutes);
			s.Format(_T("%d"), seconds);
			if (minutes < 10)
			{

				if (seconds < 10)
				{
					m_CurrentTime.SetWindowTextW(_T("0") + m + _T(":0") + s);
				}
				else
				{
					m_CurrentTime.SetWindowTextW(_T("0") + m + _T(":") + s);
				}
			}
			else
			{
				if (seconds < 10)
				{
					m_CurrentTime.SetWindowTextW(m + _T(":0") + s);
				}
				else
				{
					m_CurrentTime.SetWindowTextW(m + _T(":") + s);
				}
			}
		}
		if (secpos == (int)SongLength)
		{
			seconds = 0;
			minutes = 0;
			m_CurrentTime.SetWindowTextW(_T("00:00"));
			BASS_ChannelStop(m_MainChannel);
			BASS_ChannelSetPosition(m_MainChannel, 0, BASS_POS_BYTE);
			if (Repeating == false)
			{
				GetDlgItem(ID_PLAY_PAUSE)->SetWindowText(_T("Play"));
				KillTimer(m_TSlide);
				Playing = false;
				Paused = false;
			}
			else
			{
				BASS_ChannelPlay(m_MainChannel, FALSE);
			}
			secpos = 0;
			m_SlidePlayTime.SetPos(0);
		}
	}
	if (nIDEvent == 2)
	{
		CClientDC *pdc = new CClientDC(this);
		CBrush *pbr;

		CRect r_CL(5, 5, 385, 270);

		CDC memDC;
		if (!memDC.CreateCompatibleDC(pdc))
			return;
		CBitmap* oldBmp;
		CBitmap memBmp;
		if (!memBmp.CreateCompatibleBitmap(pdc, r_CL.Width(), r_CL.Height()))
			return;

		oldBmp = memDC.SelectObject(&memBmp);
		pbr = new CBrush(RGB(0, 0, 0));
		memDC.SelectObject(pbr);
		memDC.FillRect(r_CL, pbr);

		if (AlreadyOpen)
		{
			BASS_ChannelGetData(m_MainChannel, fft, BASS_DATA_FFT2048);
			int b0 = 0;

			for (int x = 0; x < 28; x++)
			{
				CPen *Pen0, *Pen1, *Pen2, *Pen3, *Pen4, *Pen5, *Pen6, *Pen7, *Pen8;
				CBrush *Brush0, *Brush1, *Brush2, *Brush3, *Brush4, *Brush5, *Brush6, *Brush7, *Brush8;
				float peak = 0;
				int b1 = pow(2, x*10.0 / (28 - 1));
				if (b1 <= b0) b1 = b0 + 1; // make sure it uses at least 1 FFT bin
				if (b1>1023) b1 = 1023;
				for (; b0<b1; b0++)
					if (peak<fft[1 + b0])
						peak = fft[1 + b0];
				int y = sqrt(peak) * 3 * 270 - 4; // scale it (sqrt to make low values more visible)
				if (y > 270)
				{
					y = 270;
				}
				Pen0 = new CPen(PS_SOLID, 1, RGB(0, 255, 0));
				Brush0 = new CBrush(RGB(0, 255, 0));
				//1
				Pen1 = new CPen(PS_SOLID, 1, RGB(31, 223, 0));
				Brush1 = new CBrush(RGB(31, 223, 0));
				//2
				Pen2 = new CPen(PS_SOLID, 1, RGB(63, 191, 0));
				Brush2 = new CBrush(RGB(63, 191, 0));
				//3
				Pen3 = new CPen(PS_SOLID, 1, RGB(95, 159, 0));
				Brush3 = new CBrush(RGB(95, 159, 0));
				//4
				Pen4 = new CPen(PS_SOLID, 1, RGB(127, 127, 0));
				Brush4 = new CBrush(RGB(127, 127, 0));
				//5
				Pen5 = new CPen(PS_SOLID, 1, RGB(159, 95, 0));
				Brush5 = new CBrush(RGB(159, 95, 0));
				//6
				Pen6 = new CPen(PS_SOLID, 1, RGB(191, 63, 0));
				Brush6 = new CBrush(RGB(191, 63, 0));
				//7
				Pen7 = new CPen(PS_SOLID, 1, RGB(223, 31, 0));
				Brush7 = new CBrush(RGB(223, 31, 0));
				//8
				Pen8 = new CPen(PS_SOLID, 1, RGB(255, 0, 0));
				Brush8 = new CBrush(RGB(255, 0, 0));

				memDC.SelectObject(Pen0);
				memDC.SelectObject(Brush0);
				int y1 = 270 - y;
				if (y > (270 * 0.1))
				{
					memDC.Rectangle(x*(385 / 28), 270 - (270 * 0.1), x*(385 / 28) + (int)(385 / 28) - 1, 270);
					memDC.SelectObject(Pen1);
					memDC.SelectObject(Brush1);
					if (y > (270 * 0.2))
					{
						memDC.Rectangle(x*(385 / 28), 270 - (270 * 0.2), x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.1));
						memDC.SelectObject(Pen2);
						memDC.SelectObject(Brush2);
						if (y > (270 * 0.3))
						{
							memDC.Rectangle(x*(385 / 28), 270 - (270 * 0.3), x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.2));
							memDC.SelectObject(Pen3);
							memDC.SelectObject(Brush3);
							if (y > (270 * 0.4))
							{
								memDC.Rectangle(x*(385 / 28), 270 - (270 * 0.4), x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.3));
								memDC.SelectObject(Pen4);
								memDC.SelectObject(Brush4);
								if (y > (270 * 0.5))
								{
									memDC.Rectangle(x*(385 / 28), 270 - (270 * 0.5), x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.4));
									memDC.SelectObject(Pen5);
									memDC.SelectObject(Brush5);
									if (y > (270 * 0.6))
									{
										memDC.Rectangle(x*(385 / 28), 270 - (270 * 0.6), x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.5));
										memDC.SelectObject(Pen6);
										memDC.SelectObject(Brush6);
										if (y > (270 * 0.7))
										{
											memDC.Rectangle(x*(385 / 28), 270 - (270 * 0.7), x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.6));
											memDC.SelectObject(Pen7);
											memDC.SelectObject(Brush7);
											if (y > (270 * 0.8))
											{
												memDC.Rectangle(x*(385 / 28), 270 - (270 * 0.8), x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.7));
												memDC.SelectObject(Pen8);
												memDC.SelectObject(Brush8);
												memDC.Rectangle(x*(385 / 28), y1, x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.8));
											}
											else
											{
												memDC.Rectangle(x*(385 / 28), y1, x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.6));
											}
										}
										else
										{
											memDC.Rectangle(x*(385 / 28), y1, x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.6));
										}
									}
									else
									{
										memDC.Rectangle(x*(385 / 28), y1, x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.5));
									}
								}
								else
								{
									memDC.Rectangle(x*(385 / 28), y1, x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.4));
								}
							}
							else
							{
								memDC.Rectangle(x*(385 / 28), y1, x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.3));
							}
						}
						else
						{
							memDC.Rectangle(x*(385 / 28), y1, x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.2));
						}
					}
					else
					{
						memDC.Rectangle(x*(385 / 28), y1, x*(385 / 28) + (int)(385 / 28) - 1, 270 - (270 * 0.1));
					}
				}
				else
				{
					memDC.Rectangle(x*(385 / 28), y1, x*(385 / 28) + (int)(385 / 28) - 1, 270);
				}
				delete Pen0; delete Pen1; delete Pen2; delete Pen3; delete Pen4;
				delete Pen5; delete Pen6; delete Pen7; delete Pen8;
				delete Brush0; delete Brush1;  delete Brush2; delete Brush3;
				delete Brush4; delete Brush5;  delete Brush6; delete Brush7;
				delete Brush8;
			}
		}

		pdc->BitBlt(r_CL.left, r_CL.top, r_CL.Width(), r_CL.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(oldBmp);
		memBmp.DeleteObject();
		memDC.DeleteDC();

		delete pbr;
		delete pdc;
	}
	else
	{
		CDialogEx::OnTimer(nIDEvent);
	}
}

void CCourseDlg::OnMenuChorus()
{
	MyEffects->AddToHistory(_T("chorus"), &m_MainChannel, &m_SaveChannel);
	m_History.AddString(_T("Добавлен эффект: Хор"));
	m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_ENABLED);
}

void CCourseDlg::OnMenuDistortion()
{
	MyEffects->AddToHistory(_T("distortion"), &m_MainChannel, &m_SaveChannel);
	m_History.AddString(_T("Добавлен эффект: Искажение"));
	m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_ENABLED);
}

void CCourseDlg::OnMenuEcho()
{
	MyEffects->AddToHistory(_T("echo"), &m_MainChannel, &m_SaveChannel);
	m_History.AddString(_T("Добавлен эффект: Эхо"));
	m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_ENABLED);
}

void CCourseDlg::OnMenuFlanger()
{
	MyEffects->AddToHistory(_T("flanger"), &m_MainChannel, &m_SaveChannel);
	m_History.AddString(_T("Добавлен эффект: Фланжер"));
	m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_ENABLED);
}

void CCourseDlg::OnMenuGargle()
{
	MyEffects->AddToHistory(_T("gargle"), &m_MainChannel, &m_SaveChannel);
	m_History.AddString(_T("Добавлен эффект: Амплитудная модуляция"));
	m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_ENABLED);
}

void CCourseDlg::OnMenuI3DL2Reverb()
{
	MyEffects->AddToHistory(_T("i3dl2reverb"), &m_MainChannel, &m_SaveChannel);
	m_History.AddString(_T("Добавлен эффект: I3DL2 Реверберация"));
	m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_ENABLED);
}

void CCourseDlg::OnMenuReverb()
{
	MyEffects->AddToHistory(_T("reverb"), &m_MainChannel, &m_SaveChannel);
	m_History.AddString(_T("Добавлен эффект: Реверберация"));
	m_Menu.EnableMenuItem(ID_MENU_UNDO, MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_RLACTION, MF_ENABLED);
}

BOOL CCourseDlg::PreTranslateMessage(MSG* pMsg)
{
	if (TranslateAccelerator(m_hWnd, HotKeys, pMsg))
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}