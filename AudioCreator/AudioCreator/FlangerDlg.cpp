// FlangerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "FlangerDlg.h"
#include "afxdialogex.h"


// CFlangerDlg dialog

IMPLEMENT_DYNAMIC(CFlangerDlg, CDialogEx)

CFlangerDlg::CFlangerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFlangerDlg::IDD, pParent)
	, m_EWetDryMix(_T("50.00"))
	, m_EDepth(_T("100.00"))
	, m_EFeedback(_T("-50.00"))
	, m_EFrequency(_T("0.25"))
	, m_EDelay(_T("2.00"))
{
	
}

CFlangerDlg::~CFlangerDlg()
{
}

void CFlangerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WETDRYMIX, m_EWetDryMix);
	DDX_Text(pDX, IDC_EDIT_DEPTH, m_EDepth);
	DDX_Text(pDX, IDC_EDIT_FEEDBACK, m_EFeedback);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY, m_EFrequency);
	DDX_Text(pDX, IDC_EDIT_DELAY, m_EDelay);
	DDX_Control(pDX, ID_SLIDER_WETDRYMIX, m_SWetDryMix);
	DDX_Control(pDX, ID_SLIDER_DEPTH, m_SDepth);
	DDX_Control(pDX, IDC_SLIDER_FEEDBACK, m_SFeedback);
	DDX_Control(pDX, IDC_SLIDER_FREQUENCY, m_SFrequency);
	DDX_Control(pDX, ID_SLIDER_DELAY, m_SDelay);
	DDX_Control(pDX, ID_COMBO_PHASE, m_LPhase);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CFlangerDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_WETDRYMIX, &CFlangerDlg::OnEnChangeEditWetdrymix)
	ON_EN_CHANGE(IDC_EDIT_DEPTH, &CFlangerDlg::OnEnChangeEditDepth)
	ON_EN_CHANGE(IDC_EDIT_FEEDBACK, &CFlangerDlg::OnEnChangeEditFeedback)
	ON_EN_CHANGE(IDC_EDIT_FREQUENCY, &CFlangerDlg::OnEnChangeEditFrequency)
	ON_EN_CHANGE(IDC_EDIT_DELAY, &CFlangerDlg::OnEnChangeEditDelay)
	ON_CBN_SELCHANGE(ID_COMBO_PHASE, &CFlangerDlg::OnCbnSelchangeComboPhase)
	ON_BN_CLICKED(ID_RADIO1, &CFlangerDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(ID_RADIO2, &CFlangerDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDOK, &CFlangerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFlangerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_BTESTONOFF, &CFlangerDlg::OnBnClickedBtestonoff)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CFlangerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DX8_Flanger.fWetDryMix = WetDryMix = 50.00; 
	DX8_Flanger.fDepth = Depth = 100.00;
	DX8_Flanger.fFeedback = Feedback = -50.00; 
	DX8_Flanger.fFrequency = Frequency = 0.25; 
	DX8_Flanger.fDelay = Delay = 2.00;
	DX8_Flanger.lWaveform = Waveform = 1;
	DX8_Flanger.lPhase = Phase = BASS_DX8_PHASE_ZERO;

	m_SWetDryMix.SetRange(0, 10000, TRUE);		m_SWetDryMix.SetPos(5000);
	m_SDepth.SetRange(0, 10000, TRUE);			m_SDepth.SetPos(10000);
	m_SFeedback.SetRange(-9900, 9900, TRUE);	m_SFeedback.SetPos(-5000);
	m_SFrequency.SetRange(0, 1000, TRUE);		m_SFrequency.SetPos(25);
	m_SDelay.SetRange(0, 400, TRUE);			m_SDelay.SetPos(200);

	CheckRadioButton(ID_RADIO1, ID_RADIO2, ID_RADIO2);

	m_LPhase.InsertString(0, _T("Phase negative 180"));
	m_LPhase.InsertString(1, _T("Phase negative 90"));
	m_LPhase.InsertString(2, _T("Phase 0"));
	m_LPhase.InsertString(3, _T("Phase 90"));
	m_LPhase.InsertString(4, _T("Phase 180"));
	m_LPhase.SelectString(2, _T("Phase 0"));

	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));

	DefaultCore.TestOn(_T("flanger"), 1);
	DefaultCore.TestUpdate(DX8_Flanger);
	Test = true;

	UpdateData(false);
	return TRUE;
}

// CFlangerDlg message handlers

BOOL CFlangerDlg::CheckData(CString Data)
{
	//Проверка каждого введенного символа на разрешенность
	for (int i = 0; i < Data.GetLength(); i++)
	{
		//Проверка является-ли символ: 0 1 2 3 4 5 6 7 8 9 - .
		//Если нет то ошибка, если да то идем дальше по циклу:
		if ((Data.GetAt(i) != '0') && (Data.GetAt(i) != '1') && (Data.GetAt(i) != '2') &&
			(Data.GetAt(i) != '3') && (Data.GetAt(i) != '4') && (Data.GetAt(i) != '5') &&
			(Data.GetAt(i) != '6') && (Data.GetAt(i) != '7') && (Data.GetAt(i) != '8') &&
			(Data.GetAt(i) != '9') && (Data.GetAt(i) != '-') && (Data.GetAt(i) != '.'))
		{
			MessageBox(_T("Incorrect Data."), _T("Error"), MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;
}

void CFlangerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SWetDryMix)
	{
		WetDryMix = m_SWetDryMix.GetPos() / 100.00;
		DX8_Flanger.fWetDryMix = WetDryMix;
		m_EWetDryMix.Empty();
		m_EWetDryMix.Format(_T("%.2f"), WetDryMix);
	}
	if (pScrollBar == (CScrollBar *)&m_SDepth)
	{
		Depth = m_SDepth.GetPos() / 100.00;
		DX8_Flanger.fDepth = Depth;
		m_EDepth.Empty();
		m_EDepth.Format(_T("%.2f"), Depth);
	}
	if (pScrollBar == (CScrollBar *)&m_SFeedback)
	{
		Feedback = m_SFeedback.GetPos() / 100.00;
		DX8_Flanger.fFeedback = Feedback;
		m_EFeedback.Empty();
		m_EFeedback.Format(_T("%.2f"), Feedback);
	}
	if (pScrollBar == (CScrollBar *)&m_SFrequency)
	{
		Frequency = m_SFrequency.GetPos() / 100.00;
		DX8_Flanger.fFrequency = Frequency;
		m_EFrequency.Empty();
		m_EFrequency.Format(_T("%.2f"), Frequency);
	}
	if (pScrollBar == (CScrollBar *)&m_SDelay)
	{
		Delay = m_SDelay.GetPos() / 100.00;
		DX8_Flanger.fDelay = Delay;
		m_EDelay.Empty();
		m_EDelay.Format(_T("%.2f"), Delay);
	}
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Flanger);
	UpdateData(false);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CFlangerDlg::OnEnChangeEditWetdrymix()
{
	UpdateData(true);
	if (CheckData(m_EWetDryMix))
	{
		WetDryMix = _wtof(m_EWetDryMix);
		if (WetDryMix < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			WetDryMix = 0;
		}
		if (WetDryMix > 100)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			WetDryMix = 100;
		}
		DX8_Flanger.fWetDryMix = WetDryMix;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Flanger);
	}
	m_SWetDryMix.SetPos(WetDryMix * 100);
	m_EWetDryMix.Empty();
	m_EWetDryMix.Format(_T("%.2f"), WetDryMix);
	UpdateData(false);
}


void CFlangerDlg::OnEnChangeEditDepth()
{
	UpdateData(true);
	if (CheckData(m_EDepth))
	{
		Depth = _wtof(m_EDepth);
		if (Depth < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			Depth = 0;
		}
		if (Depth > 100)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			Depth = 100;
		}
		DX8_Flanger.fDepth = Depth;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Flanger);
	}
	m_SDepth.SetPos(Depth * 100);
	m_EDepth.Empty();
	m_EDepth.Format(_T("%.2f"), Depth);
	UpdateData(false);
}


void CFlangerDlg::OnEnChangeEditFeedback()
{
	UpdateData(true);
	if (CheckData(m_EFeedback))
	{
		Feedback = _wtof(m_EFeedback);
		if (Feedback < -99)
		{
			MessageBox(_T("Must be in the range from -99 to 99."), _T("Error"), MB_ICONERROR);
			Feedback = -99;
		}
		if (Feedback > 99)
		{
			MessageBox(_T("Must be in the range from -99 to 99."), _T("Error"), MB_ICONERROR);
			Feedback = 99;
		}
		DX8_Flanger.fFeedback = Feedback;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Flanger);
	}
	m_SFeedback.SetPos(Feedback * 100);
	m_EFeedback.Empty();
	m_EFeedback.Format(_T("%.2f"), Feedback);
	UpdateData(false);
}


void CFlangerDlg::OnEnChangeEditFrequency()
{
	UpdateData(true);
	if (CheckData(m_EFrequency))
	{
		Frequency = _wtof(m_EFrequency);
		if (Frequency < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 10."), _T("Error"), MB_ICONERROR);
			Frequency = 0;
		}
		if (Frequency > 10)
		{
			MessageBox(_T("Must be in the range from 0 to 10."), _T("Error"), MB_ICONERROR);
			Frequency = 10;
		}
		DX8_Flanger.fFrequency = Frequency;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Flanger);
	}
	m_SFrequency.SetPos(Frequency * 100);
	m_EFrequency.Empty();
	m_EFrequency.Format(_T("%.2f"), Frequency);
	UpdateData(false);
}


void CFlangerDlg::OnEnChangeEditDelay()
{
	UpdateData(true);
	if (CheckData(m_EDelay))
	{
		Delay = _wtof(m_EDelay);
		if (Delay < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 4."), _T("Error"), MB_ICONERROR);
			Delay = 0;
		}
		if (Delay > 20)
		{
			MessageBox(_T("Must be in the range from 0 to 4."), _T("Error"), MB_ICONERROR);
			Delay = 20;
		}
		DX8_Flanger.fDelay = Delay;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Flanger);
	}
	m_SDelay.SetPos(Delay * 100);
	m_EDelay.Empty();
	m_EDelay.Format(_T("%.2f"), Delay);
	UpdateData(false);
}


void CFlangerDlg::OnBnClickedRadio1()
{
	CheckDlgButton(ID_RADIO2, BST_UNCHECKED);
	DX8_Flanger.lWaveform = Waveform = 0;
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Flanger);
}


void CFlangerDlg::OnBnClickedRadio2()
{
	CheckDlgButton(ID_RADIO1, BST_UNCHECKED);
	DX8_Flanger.lWaveform = Waveform = 1;
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Flanger);
}


void CFlangerDlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(DX8_Flanger);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CFlangerDlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CFlangerDlg::OnClose()
{
	OnBnClickedCancel();
}


void CFlangerDlg::OnCbnSelchangeComboPhase()
{
	switch (m_LPhase.GetCurSel())
	{
	case 0:
		Phase = BASS_DX8_PHASE_NEG_180;
		break;
	case 1:
		Phase = BASS_DX8_PHASE_NEG_90;
		break;
	case 2:
		Phase = BASS_DX8_PHASE_ZERO;
		break;
	case 3:
		Phase = BASS_DX8_PHASE_90;
		break;
	case 4:
		Phase = BASS_DX8_PHASE_180;
		break;
	}
	DX8_Flanger.lPhase = Phase;
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Flanger);
}


void CFlangerDlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		DX8_Flanger.fDelay = Delay;
		DX8_Flanger.fDepth = Depth;
		DX8_Flanger.fFeedback = Feedback;
		DX8_Flanger.fFrequency = Frequency;
		DX8_Flanger.fWetDryMix = WetDryMix;
		DX8_Flanger.lPhase = Phase;
		DX8_Flanger.lWaveform = Waveform;

		DefaultCore.TestOn(_T("flanger"), 1);
		DefaultCore.TestUpdate(DX8_Flanger);

		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}
