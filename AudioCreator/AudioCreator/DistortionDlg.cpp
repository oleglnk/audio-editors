// DistortionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "DistortionDlg.h"
#include "afxdialogex.h"


// CDistortionDlg dialog

IMPLEMENT_DYNAMIC(CDistortionDlg, CDialogEx)

CDistortionDlg::CDistortionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDistortionDlg::IDD, pParent)
	, m_EGain(_T("-18.00"))
	, m_EEdge(_T("15.00"))
	, m_EFrequency(_T("2400.00"))
	, m_EBandwidth(_T("2400.00"))
	, m_ECutoff(_T("8000.00"))
{

}

CDistortionDlg::~CDistortionDlg()
{
}

void CDistortionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_SLIDER_BANDWIDTH, m_SBandwidth);
	DDX_Control(pDX, ID_SLIDER_CUTOFF, m_SCutoff);
	DDX_Control(pDX, ID_SLIDER_EDGE, m_SEdge);
	DDX_Control(pDX, ID_SLIDER_FREQUENCY, m_SFrequency);
	DDX_Control(pDX, ID_SLIDER_GAIN, m_SGain);
	DDX_Text(pDX, IDC_EDIT_BANDWIDTH, m_EBandwidth);
	DDX_Text(pDX, IDC_EDIT_CUTOFF, m_ECutoff);
	DDX_Text(pDX, IDC_EDIT_EDGE, m_EEdge);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY, m_EFrequency);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_EGain);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CDistortionDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_GAIN, &CDistortionDlg::OnEnChangeEditGain)
	ON_EN_CHANGE(IDC_EDIT_EDGE, &CDistortionDlg::OnEnChangeEditEdge)
	ON_EN_CHANGE(IDC_EDIT_FREQUENCY, &CDistortionDlg::OnEnChangeEditFrequency)
	ON_EN_CHANGE(IDC_EDIT_BANDWIDTH, &CDistortionDlg::OnEnChangeEditBandwidth)
	ON_EN_CHANGE(IDC_EDIT_CUTOFF, &CDistortionDlg::OnEnChangeEditCutoff)
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_BTESTONOFF, &CDistortionDlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CDistortionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDistortionDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


BOOL CDistortionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DX8_Distortion.fGain = Gain = -18.00; 
	DX8_Distortion.fEdge = Edge = 15.00;
	DX8_Distortion.fPostEQCenterFrequency = Frequency = 2400.00;
	DX8_Distortion.fPostEQBandwidth = Bandwidth = 2400.00; 
	DX8_Distortion.fPreLowpassCutoff = Cutoff = 8000.00;
	
	m_SGain.SetRange(-6000, 0, TRUE);				m_SGain.SetPos(-1800);
	m_SEdge.SetRange(0, 10000, TRUE);				m_SEdge.SetPos(1500);
	m_SFrequency.SetRange(10000, 800000, TRUE);		m_SFrequency.SetPos(240000);
	m_SBandwidth.SetRange(10000, 800000, TRUE);		m_SBandwidth.SetPos(240000);
	m_SCutoff.SetRange(10000, 800000, TRUE);		m_SCutoff.SetPos(800000);

	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));

	DefaultCore.TestOn(_T("distortion"), 1);
	DefaultCore.TestUpdate(DX8_Distortion);
	Test = true;
	
	UpdateData(false);
	return TRUE;
}

// CDistortionDlg message handlers

BOOL CDistortionDlg::CheckData(CString Data)
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

void CDistortionDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SGain)
	{
		Gain = m_SGain.GetPos() / 100.00;
		DX8_Distortion.fGain = Gain;
		m_EGain.Empty();
		m_EGain.Format(_T("%.2f"), Gain);
	}
	if (pScrollBar == (CScrollBar *)&m_SEdge)
	{
		Edge = m_SEdge.GetPos() / 100.00;
		DX8_Distortion.fEdge = Edge;
		m_EEdge.Empty();
		m_EEdge.Format(_T("%.2f"), Edge);
	}
	if (pScrollBar == (CScrollBar *)&m_SFrequency)
	{
		Frequency = m_SFrequency.GetPos() / 100.00;
		DX8_Distortion.fPostEQCenterFrequency = Frequency;
		m_EFrequency.Empty();
		m_EFrequency.Format(_T("%.2f"), Frequency);
	}
	if (pScrollBar == (CScrollBar *)&m_SBandwidth)
	{
		Bandwidth = m_SBandwidth.GetPos() / 100.00;
		DX8_Distortion.fPostEQBandwidth = Bandwidth;
		m_EBandwidth.Empty();
		m_EBandwidth.Format(_T("%.2f"), Bandwidth);
	}
	if (pScrollBar == (CScrollBar *)&m_SCutoff)
	{
		Cutoff = m_SCutoff.GetPos() / 100.00;
		DX8_Distortion.fPreLowpassCutoff = Cutoff;
		m_ECutoff.Empty();
		m_ECutoff.Format(_T("%.2f"), Cutoff);	
	}
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Distortion);
	UpdateData(false);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



void CDistortionDlg::OnEnChangeEditGain()
{
	UpdateData(true);
	if (CheckData(m_EGain))
	{
		Gain = _wtof(m_EGain);
		if (Gain < -60)
		{
			MessageBox(_T("Must be in the range from -60 to 0."), _T("Error"), MB_ICONERROR);
			Gain = -60;
		}
		if (Gain > 0)
		{
			MessageBox(_T("Must be in the range from -60 to 0."), _T("Error"), MB_ICONERROR);
			Gain = 0;
		}
		DX8_Distortion.fGain = Gain;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Distortion);
	}
	m_SGain.SetPos(Gain * 100);
	m_EGain.Empty();
	m_EGain.Format(_T("%.2f"), Gain);
	UpdateData(false);
}


void CDistortionDlg::OnEnChangeEditEdge()
{
	UpdateData(true);
	if (CheckData(m_EEdge))
	{
		Edge = _wtof(m_EEdge);
		if (Edge < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			Edge = 0;
		}
		if (Edge > 100)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			Edge = 100;
		}
		DX8_Distortion.fEdge = Edge;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Distortion);
	}
	m_SEdge.SetPos(Edge * 100);
	m_EEdge.Empty();
	m_EEdge.Format(_T("%.2f"), Edge);
	UpdateData(false);
}


void CDistortionDlg::OnEnChangeEditFrequency()
{
	UpdateData(true);
	if (CheckData(m_EFrequency))
	{
		Frequency = _wtof(m_EFrequency);
		if (Frequency < 100)
		{
			MessageBox(_T("Must be in the range from 100 to 8000."), _T("Error"), MB_ICONERROR);
			Frequency = 100;
		}
		if (Frequency > 8000)
		{
			MessageBox(_T("Must be in the range from 100 to 8000."), _T("Error"), MB_ICONERROR);
			Frequency = 8000;
		}
		DX8_Distortion.fPostEQCenterFrequency = Frequency;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Distortion);
	}
	m_SFrequency.SetPos(Frequency * 100);
	m_EFrequency.Empty();
	m_EFrequency.Format(_T("%.2f"), Frequency);
	UpdateData(false);
}


void CDistortionDlg::OnEnChangeEditBandwidth()
{
	UpdateData(true);
	if (CheckData(m_EBandwidth))
	{
		Bandwidth = _wtof(m_EBandwidth);
		if (Bandwidth < 100)
		{
			MessageBox(_T("Must be in the range from 100 to 8000."), _T("Error"), MB_ICONERROR);
			Bandwidth = 100;
		}
		if (Bandwidth > 8000)
		{
			MessageBox(_T("Must be in the range from 100 to 8000."), _T("Error"), MB_ICONERROR);
			Bandwidth = 8000;
		}
		DX8_Distortion.fPostEQBandwidth = Bandwidth;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Distortion);
	}
	m_SBandwidth.SetPos(Bandwidth * 100);
	m_EBandwidth.Empty();
	m_EBandwidth.Format(_T("%.2f"), Bandwidth);
	UpdateData(false);
}


void CDistortionDlg::OnEnChangeEditCutoff()
{
	UpdateData(true);
	if (CheckData(m_ECutoff))
	{
		Cutoff = _wtof(m_ECutoff);
		if (Cutoff < 100)
		{
			MessageBox(_T("Must be in the range from 100 to 8000."), _T("Error"), MB_ICONERROR);
			Cutoff = 100;
		}
		if (Cutoff > 8000)
		{
			MessageBox(_T("Must be in the range from 100 to 8000."), _T("Error"), MB_ICONERROR);
			Cutoff = 8000;
		}
		DX8_Distortion.fPreLowpassCutoff = Cutoff;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Distortion);
	}
	m_SCutoff.SetPos(Cutoff * 100);
	m_ECutoff.Empty();
	m_ECutoff.Format(_T("%.2f"), Cutoff);
	UpdateData(false);
}


void CDistortionDlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		DX8_Distortion.fGain = Gain;
		DX8_Distortion.fEdge = Edge;
		DX8_Distortion.fPostEQCenterFrequency = Frequency;
		DX8_Distortion.fPostEQBandwidth = Bandwidth;
		DX8_Distortion.fPreLowpassCutoff = Cutoff;

		DefaultCore.TestOn(_T("distortion"), 1);
		DefaultCore.TestUpdate(DX8_Distortion);
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CDistortionDlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(DX8_Distortion);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CDistortionDlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CDistortionDlg::OnClose()
{
	OnBnClickedCancel();
}