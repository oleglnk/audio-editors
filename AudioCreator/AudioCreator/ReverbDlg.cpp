// ReverbDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "ReverbDlg.h"
#include "afxdialogex.h"


// CReverbDlg dialog

IMPLEMENT_DYNAMIC(CReverbDlg, CDialogEx)

CReverbDlg::CReverbDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReverbDlg::IDD, pParent)
	, m_EGain(_T("0.00"))
	, m_EMix(_T("0.00"))
	, m_ETime(_T("1000.000"))
	, m_ETimeRatio(_T("0.001"))
{

}

CReverbDlg::~CReverbDlg()
{
}

void CReverbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_SLIDER_GAIN, m_SGain);
	DDX_Control(pDX, ID_SLIDER_MIX, m_SMix);
	DDX_Control(pDX, ID_SLIDER_TIME, m_STime);
	DDX_Control(pDX, ID_SLIDER_TIMERATIO, m_STimeRatio);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_EGain);
	DDX_Text(pDX, IDC_EDIT_MIX, m_EMix);
	DDX_Text(pDX, IDC_EDIT_TIME, m_ETime);
	DDX_Text(pDX, IDC_EDIT_TIMERATIO, m_ETimeRatio);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CReverbDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_GAIN, &CReverbDlg::OnEnChangeEditGain)
	ON_EN_CHANGE(IDC_EDIT_MIX, &CReverbDlg::OnEnChangeEditMix)
	ON_EN_CHANGE(IDC_EDIT_TIME, &CReverbDlg::OnEnChangeEditTime)
	ON_EN_CHANGE(IDC_EDIT_TIMERATIO, &CReverbDlg::OnEnChangeEditTimeratio)
	ON_BN_CLICKED(ID_BTESTONOFF, &CReverbDlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CReverbDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CReverbDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CReverbDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DX8_Reverb.fInGain = Gain = 0.00; 
	DX8_Reverb.fReverbMix = Mix = 0.00; 
	DX8_Reverb.fReverbTime = Time = 1000.000; 
	DX8_Reverb.fHighFreqRTRatio = TimeRatio = 0.001;

	m_SGain.SetRange(-9600, 0, TRUE);		m_SGain.SetPos(0);
	m_SMix.SetRange(-9600, 0, TRUE);		m_SMix.SetPos(0);
	m_STime.SetRange(1, 3000000, TRUE);		m_STime.SetPos(1000000);
	m_STimeRatio.SetRange(1, 999, TRUE);	m_STimeRatio.SetPos(1);

	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
	
	DefaultCore.TestOn(_T("reverb"), 1);
	DefaultCore.TestUpdate(DX8_Reverb);
	Test = true;

	UpdateData(false);
	return TRUE;
}

// CReverbDlg message handlers

BOOL CReverbDlg::CheckData(CString Data)
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


void CReverbDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SGain)
	{
		Gain = m_SGain.GetPos() / 100.00;
		DX8_Reverb.fInGain = Gain;
		m_EGain.Empty();
		m_EGain.Format(_T("%.2f"), Gain);
	}
	if (pScrollBar == (CScrollBar *)&m_SMix)
	{
		Mix = m_SMix.GetPos() / 100.00;
		DX8_Reverb.fReverbMix = Mix;
		m_EMix.Empty();
		m_EMix.Format(_T("%.2f"), Mix);
	}
	if (pScrollBar == (CScrollBar *)&m_STime)
	{
		Time = m_STime.GetPos() / 1000.000;
		DX8_Reverb.fReverbTime = Time;
		m_ETime.Empty();
		m_ETime.Format(_T("%.3f"), Time);
	}
	if (pScrollBar == (CScrollBar *)&m_STimeRatio)
	{
		TimeRatio = m_STimeRatio.GetPos() / 1000.000;
		DX8_Reverb.fHighFreqRTRatio = TimeRatio;
		m_ETimeRatio.Empty();
		m_ETimeRatio.Format(_T("%.3f"), TimeRatio);
	}
	if (Test)
		DefaultCore.TestUpdate(DX8_Reverb);
	UpdateData(false);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CReverbDlg::OnEnChangeEditGain()
{
	UpdateData(true);
	if (CheckData(m_EGain))
	{
		Gain = _wtof(m_EGain);
		if (Gain < -96)
		{
			MessageBox(_T("Must be in the range from -96 to 0."), _T("Error"), MB_ICONERROR);
			Gain = -96;
		}
		if (Gain > 0)
		{
			MessageBox(_T("Must be in the range from -96 to 0."), _T("Error"), MB_ICONERROR);
			Gain = 0;
		}
		DX8_Reverb.fInGain = Gain;
		if (Test)
			DefaultCore.TestUpdate(DX8_Reverb);
	}
	m_SGain.SetPos(Gain * 100);
	m_EGain.Empty();
	m_EGain.Format(_T("%.2f"), Gain);
	UpdateData(false);
}


void CReverbDlg::OnEnChangeEditMix()
{
	UpdateData(true);
	if (CheckData(m_EMix))
	{
		Mix = _wtof(m_EMix);
		if (Mix < -96)
		{
			MessageBox(_T("Must be in the range from -96 to 0."), _T("Error"), MB_ICONERROR);
			Mix = -96;
		}
		if (Mix > 0)
		{
			MessageBox(_T("Must be in the range from -96 to 0."), _T("Error"), MB_ICONERROR);
			Mix = 0;
		}
		DX8_Reverb.fReverbMix = Mix;
		if (Test)
			DefaultCore.TestUpdate(DX8_Reverb);
	}
	m_SMix.SetPos(Mix * 100);
	m_EMix.Empty();
	m_EMix.Format(_T("%.2f"), Mix);
	UpdateData(false);
}


void CReverbDlg::OnEnChangeEditTime()
{
	UpdateData(true);
	if (CheckData(m_ETime))
	{
		Time = _wtof(m_ETime);
		if (Time < 0.001)
		{
			MessageBox(_T("Must be in the range from 0.001 to 3000."), _T("Error"), MB_ICONERROR);
			Time = 0.001;
		}
		if (Time > 3000)
		{
			MessageBox(_T("Must be in the range from 0.001 to 3000."), _T("Error"), MB_ICONERROR);
			Time = 3000;
		}
		DX8_Reverb.fReverbTime = Time;
		if (Test)
			DefaultCore.TestUpdate(DX8_Reverb);
	}
	m_STime.SetPos(Time * 1000);
	m_ETime.Empty();
	m_ETime.Format(_T("%.3f"), Time);
	UpdateData(false);
}


void CReverbDlg::OnEnChangeEditTimeratio()
{
	UpdateData(true);
	if (CheckData(m_ETimeRatio))
	{
		TimeRatio = _wtof(m_ETimeRatio);
		if (TimeRatio < 0.001)
		{
			MessageBox(_T("Must be in the range from 0.001 to 0.999."), _T("Error"), MB_ICONERROR);
			TimeRatio = 0.001;
		}
		if (TimeRatio > 0.999)
		{
			MessageBox(_T("Must be in the range from 0.001 to 0.999."), _T("Error"), MB_ICONERROR);
			TimeRatio = 0.999;
		}
		DX8_Reverb.fHighFreqRTRatio = TimeRatio;
		if (Test)
			DefaultCore.TestUpdate(DX8_Reverb);
	}
	m_STimeRatio.SetPos(TimeRatio * 1000);
	m_ETimeRatio.Empty();
	m_ETimeRatio.Format(_T("%.3f"), TimeRatio);
	UpdateData(false);
}


void CReverbDlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		DX8_Reverb.fInGain = Gain;
		DX8_Reverb.fReverbMix = Mix;
		DX8_Reverb.fReverbTime = Time;
		DX8_Reverb.fHighFreqRTRatio = TimeRatio;

		DefaultCore.TestOn(_T("reverb"), 1);
		DefaultCore.TestUpdate(DX8_Reverb);

		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CReverbDlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(DX8_Reverb);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CReverbDlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CReverbDlg::OnClose()
{
	OnBnClickedCancel();
}
