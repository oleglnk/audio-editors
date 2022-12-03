// ChorusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "ChorusDlg.h"
#include "afxdialogex.h"


// CChorusDlg dialog

IMPLEMENT_DYNAMIC(CChorusDlg, CDialogEx)

CChorusDlg::CChorusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChorusDlg::IDD, pParent)
	, m_EWetDryMix(_T("50.00"))
	, m_EDepth(_T("10.00"))
	, m_EFeedback(_T("25.00"))
	, m_EFrequency(_T("1.10"))
	, m_EDelay(_T("16.00"))
{

}

CChorusDlg::~CChorusDlg()
{
}

void CChorusDlg::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CChorusDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_WETDRYMIX, &CChorusDlg::OnEnChangeEditWetdrymix)
	ON_EN_CHANGE(IDC_EDIT_DEPTH, &CChorusDlg::OnEnChangeEditDepth)
	ON_EN_CHANGE(IDC_EDIT_FEEDBACK, &CChorusDlg::OnEnChangeEditFeedback)
	ON_EN_CHANGE(IDC_EDIT_FREQUENCY, &CChorusDlg::OnEnChangeEditFrequency)
	ON_EN_CHANGE(IDC_EDIT_DELAY, &CChorusDlg::OnEnChangeEditDelay)
	ON_CBN_SELCHANGE(ID_COMBO_PHASE, &CChorusDlg::OnCbnSelchangeComboPhase)
	ON_BN_CLICKED(ID_RADIO2, &CChorusDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(ID_RADIO1, &CChorusDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(ID_BTESTONOFF, &CChorusDlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CChorusDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CChorusDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CChorusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DX8_Chorus.fWetDryMix = WetDryMix = 50.00;
	DX8_Chorus.fDepth = Depth = 10.00; 
	DX8_Chorus.fFeedback = Feedback = 25.00;
	DX8_Chorus.fFrequency = Frequency = 1.10; 
	DX8_Chorus.fDelay = Delay = 16.00;
	DX8_Chorus.lWaveform = Waveform = 1;
	DX8_Chorus.lPhase = Phase = BASS_DX8_PHASE_90;

	m_SWetDryMix.SetRange(0, 10000, TRUE);	m_SWetDryMix.SetPos(5000);
	m_SDepth.SetRange(0, 10000, TRUE);		m_SDepth.SetPos(1000);
	m_SFeedback.SetRange(-9900, 9900, TRUE);	m_SFeedback.SetPos(2500);
	m_SFrequency.SetRange(0, 1000, TRUE);		m_SFrequency.SetPos(110);
	m_SDelay.SetRange(0, 2000, TRUE);			m_SDelay.SetPos(1600);
	
	CheckDlgButton(ID_RADIO2, BST_CHECKED);
	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
	
	m_LPhase.InsertString(0, _T("Phase negative 180"));
	m_LPhase.InsertString(1, _T("Phase negative 90"));
	m_LPhase.InsertString(2, _T("Phase 0"));
	m_LPhase.InsertString(3, _T("Phase 90"));
	m_LPhase.InsertString(4, _T("Phase 180"));
	m_LPhase.SelectString(3, _T("Phase 90"));

	DefaultCore.TestOn(_T("chorus"), 1);
	DefaultCore.TestUpdate(DX8_Chorus);
	Test = true;

	UpdateData(false);
	return TRUE;
}

// CChorusDlg message handlers


BOOL CChorusDlg::CheckData(CString Data)
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


void CChorusDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SWetDryMix)
	{
		WetDryMix = m_SWetDryMix.GetPos() / 100.00;
		DX8_Chorus.fWetDryMix = WetDryMix;
		m_EWetDryMix.Empty();
		m_EWetDryMix.Format(_T("%.2f"), WetDryMix);	
	}
	if (pScrollBar == (CScrollBar *)&m_SDepth)
	{
		Depth = m_SDepth.GetPos() / 100.00;
		DX8_Chorus.fDepth = Depth;
		m_EDepth.Empty();
		m_EDepth.Format(_T("%.2f"), Depth);
	}
	if (pScrollBar == (CScrollBar *)&m_SFeedback)
	{
		Feedback = m_SFeedback.GetPos() / 100.00;
		DX8_Chorus.fFeedback = Feedback;
		m_EFeedback.Empty();
		m_EFeedback.Format(_T("%.2f"), Feedback);
	}
	if (pScrollBar == (CScrollBar *)&m_SFrequency)
	{
		Frequency = m_SFrequency.GetPos() / 100.00;
		DX8_Chorus.fFrequency = Frequency;
		m_EFrequency.Empty();
		m_EFrequency.Format(_T("%.2f"), Frequency);
	}
	if (pScrollBar == (CScrollBar *)&m_SDelay)
	{
		Delay = m_SDelay.GetPos() / 100.00;
		DX8_Chorus.fDelay = Delay;
		m_EDelay.Empty();
		m_EDelay.Format(_T("%.2f"), Delay);	
	}
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Chorus);
	UpdateData(false);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CChorusDlg::OnEnChangeEditWetdrymix()
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
		DX8_Chorus.fWetDryMix = WetDryMix;	
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Chorus);
	}
	m_SWetDryMix.SetPos(WetDryMix * 100);
	m_EWetDryMix.Empty();
	m_EWetDryMix.Format(_T("%.2f"), WetDryMix);
	UpdateData(false);
}


void CChorusDlg::OnEnChangeEditDepth()
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
		DX8_Chorus.fDepth = Depth;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Chorus);
	}
	m_SDepth.SetPos(Depth * 100);
	m_EDepth.Empty();
	m_EDepth.Format(_T("%.2f"), Depth);
	UpdateData(false);
}


void CChorusDlg::OnEnChangeEditFeedback()
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
		DX8_Chorus.fFeedback = Feedback;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Chorus);
	}
	m_SFeedback.SetPos(Feedback * 100);
	m_EFeedback.Empty();
	m_EFeedback.Format(_T("%.2f"), Feedback);
	UpdateData(false);
}


void CChorusDlg::OnEnChangeEditFrequency()
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
		DX8_Chorus.fFrequency = Frequency;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Chorus);
	}
	m_SFrequency.SetPos(Frequency * 100);
	m_EFrequency.Empty();
	m_EFrequency.Format(_T("%.2f"), Frequency);
	UpdateData(false);
}


void CChorusDlg::OnEnChangeEditDelay()
{
	UpdateData(true);
	if (CheckData(m_EDelay))
	{
		Delay = _wtof(m_EDelay);
		if (Delay < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 20."), _T("Error"), MB_ICONERROR);
			Delay = 0;
		}
		if (Delay > 20)
		{
			MessageBox(_T("Must be in the range from 0 to 20."), _T("Error"), MB_ICONERROR);
			Delay = 20;
		}
		DX8_Chorus.fDelay = Delay;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Chorus);
	}
	m_SDelay.SetPos(Delay * 100);
	m_EDelay.Empty();
	m_EDelay.Format(_T("%.2f"), Delay);
	UpdateData(false);
}


void CChorusDlg::OnCbnSelchangeComboPhase()
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
	DX8_Chorus.lPhase = Phase;
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Chorus);
}


void CChorusDlg::OnBnClickedRadio2()
{
	CheckDlgButton(ID_RADIO1, BST_UNCHECKED);
	DX8_Chorus.lWaveform = Waveform = 1;
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Chorus);
}


void CChorusDlg::OnBnClickedRadio1()
{
	CheckDlgButton(ID_RADIO2, BST_UNCHECKED);
	DX8_Chorus.lWaveform = Waveform = 0;
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Chorus);
}


void CChorusDlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		DX8_Chorus.fDelay = Delay;
		DX8_Chorus.fDepth = Depth;
		DX8_Chorus.fFeedback = Feedback;
		DX8_Chorus.fFrequency = Frequency;
		DX8_Chorus.fWetDryMix = WetDryMix;
		DX8_Chorus.lPhase = Phase;
		DX8_Chorus.lWaveform = Waveform;

		DefaultCore.TestOn(_T("chorus"), 1);
		DefaultCore.TestUpdate(DX8_Chorus);
		
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CChorusDlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(DX8_Chorus);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CChorusDlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CChorusDlg::OnClose()
{
	OnBnClickedCancel();
}
