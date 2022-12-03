// CompressorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "CompressorDlg.h"
#include "afxdialogex.h"


// CCompressorDlg dialog

IMPLEMENT_DYNAMIC(CCompressorDlg, CDialogEx)

CCompressorDlg::CCompressorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompressorDlg::IDD, pParent)
	, m_EGain(_T("0.00"))
	, m_EAttack(_T("10.00"))
	, m_ERelease(_T("200.00"))
	, m_EThreshold(_T("-20.00"))
	, m_ERatio(_T("3.00"))
	, m_EPreDelay(_T("4.00"))
{

}

CCompressorDlg::~CCompressorDlg()
{
}

void CCompressorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_EGain);
	DDX_Text(pDX, IDC_EDIT_ATTACK, m_EAttack);
	DDX_Text(pDX, IDC_EDIT_RELEASE, m_ERelease);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_EThreshold);
	DDX_Text(pDX, IDC_EDIT_RATIO, m_ERatio);
	DDX_Text(pDX, IDC_EDIT_PREDELAY, m_EPreDelay);
	DDX_Control(pDX, ID_SLIDER_ATTACK, m_SAttack);
	DDX_Control(pDX, ID_SLIDER_GAIN, m_SGain);
	DDX_Control(pDX, ID_SLIDER_PREDELAY, m_SPreDelay);
	DDX_Control(pDX, ID_SLIDER_RATIO, m_SRatio);
	DDX_Control(pDX, ID_SLIDER_RELEASE, m_SRelease);
	DDX_Control(pDX, ID_SLIDER_THRESHOLD, m_SThreshold);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CCompressorDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_GAIN, &CCompressorDlg::OnEnChangeEditGain)
	ON_EN_CHANGE(IDC_EDIT_ATTACK, &CCompressorDlg::OnEnChangeEditAttack)
	ON_EN_CHANGE(IDC_EDIT_RELEASE, &CCompressorDlg::OnEnChangeEditRelease)
	ON_EN_CHANGE(IDC_EDIT_THRESHOLD, &CCompressorDlg::OnEnChangeEditThreshold)
	ON_EN_CHANGE(IDC_EDIT_RATIO, &CCompressorDlg::OnEnChangeEditRatio)
	ON_EN_CHANGE(IDC_EDIT_PREDELAY, &CCompressorDlg::OnEnChangeEditPredelay)
	ON_BN_CLICKED(ID_BTESTONOFF, &CCompressorDlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CCompressorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCompressorDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CCompressorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DX8_Compressor.fGain = Gain = 0.00; 
	DX8_Compressor.fAttack = Attack = 10.00;
	DX8_Compressor.fRelease = Release = 200.00;
	DX8_Compressor.fThreshold = Threshold = -20.00;
	DX8_Compressor.fRatio = Ratio = 3.00;
	DX8_Compressor.fPredelay = PreDelay = 4.00;

	m_SGain.SetRange(-6000, 6000, TRUE);		m_SGain.SetPos(0);
	m_SAttack.SetRange(1, 50000, TRUE);		m_SAttack.SetPos(1000);
	m_SRelease.SetRange(5000, 300000, TRUE);	m_SRelease.SetPos(20000);
	m_SThreshold.SetRange(-6000, 0, TRUE);	m_SThreshold.SetPos(-2000);
	m_SRatio.SetRange(100, 10000, TRUE);		m_SRatio.SetPos(300);
	m_SPreDelay.SetRange(0, 400, TRUE);		m_SPreDelay.SetPos(400);

	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));

	DefaultCore.TestOn(_T("compressor"), 1);
	DefaultCore.TestUpdate(DX8_Compressor);
	Test = true;

	UpdateData(false);
	return TRUE;
}

// CCompressorDlg message handlers


BOOL CCompressorDlg::CheckData(CString Data)
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


void CCompressorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SGain)
	{
		Gain = m_SGain.GetPos() / 100.00;
		DX8_Compressor.fGain = Gain;
		m_EGain.Empty();
		m_EGain.Format(_T("%.2f"), Gain);
	}
	if (pScrollBar == (CScrollBar *)&m_SAttack)
	{
		Attack = m_SAttack.GetPos() / 100.00;
		DX8_Compressor.fAttack = Attack;
		m_EAttack.Empty();
		m_EAttack.Format(_T("%.2f"), Attack);
	}
	if (pScrollBar == (CScrollBar *)&m_SRelease)
	{
		Release = m_SRelease.GetPos() / 100.00;
		DX8_Compressor.fRelease = Release;
		m_ERelease.Empty();
		m_ERelease.Format(_T("%.2f"), Release);
	}
	if (pScrollBar == (CScrollBar *)&m_SThreshold)
	{
		Threshold = m_SThreshold.GetPos() / 100.00;
		DX8_Compressor.fThreshold = Threshold;
		m_EThreshold.Empty();
		m_EThreshold.Format(_T("%.2f"), Threshold);
	}
	if (pScrollBar == (CScrollBar *)&m_SRatio)
	{
		Ratio = m_SRatio.GetPos() / 100.00;
		DX8_Compressor.fRatio = Ratio;
		m_ERatio.Empty();
		m_ERatio.Format(_T("%.2f"), Ratio);
	}
	if (pScrollBar == (CScrollBar *)&m_SPreDelay)
	{
		PreDelay = m_SPreDelay.GetPos() / 100.00;
		DX8_Compressor.fPredelay = PreDelay;
		m_EPreDelay.Empty();
		m_EPreDelay.Format(_T("%.2f"), PreDelay);
	}
	if (Test)
		DefaultCore.TestUpdate(DX8_Compressor);
	UpdateData(false);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CCompressorDlg::OnEnChangeEditGain()
{
	UpdateData(true);
	if (CheckData(m_EGain))
	{
		Gain = _wtof(m_EGain);
		if (Gain < -60)
		{
			MessageBox(_T("Must be in the range from -60 to 60."), _T("Error"), MB_ICONERROR);
			Gain = -60;
		}
		if (Gain > 60)
		{
			MessageBox(_T("Must be in the range from -60 to 60."), _T("Error"), MB_ICONERROR);
			Gain = 60;
		}
		DX8_Compressor.fGain = Gain;
		if (Test)
			DefaultCore.TestUpdate(DX8_Compressor);
	}
	m_SGain.SetPos(Gain * 100);
	m_EGain.Empty();
	m_EGain.Format(_T("%.2f"), Gain);
	UpdateData(false);
}


void CCompressorDlg::OnEnChangeEditAttack()
{
	UpdateData(true);
	if (CheckData(m_EAttack))
	{
		Attack = _wtof(m_EAttack);
		if (Attack < 0.01)
		{
			MessageBox(_T("Must be in the range from 0.01 to 500."), _T("Error"), MB_ICONERROR);
			Attack = 0.01;
		}
		if (Attack > 500)
		{
			MessageBox(_T("Must be in the range from 0.01 to 500."), _T("Error"), MB_ICONERROR);
			Attack = 500;
		}
		DX8_Compressor.fAttack = Attack;
		if (Test)
			DefaultCore.TestUpdate(DX8_Compressor);
	}
	m_SAttack.SetPos(Attack * 100);
	m_EAttack.Empty();
	m_EAttack.Format(_T("%.2f"), Attack);
	UpdateData(false);
}


void CCompressorDlg::OnEnChangeEditRelease()
{
	UpdateData(true);
	if (CheckData(m_ERelease))
	{
		Release = _wtof(m_ERelease);
		if (Release < 50)
		{
			MessageBox(_T("Must be in the range from 50 to 3000."), _T("Error"), MB_ICONERROR);
			Release = 50;
		}
		if (Release > 3000)
		{
			MessageBox(_T("Must be in the range from 50 to 3000."), _T("Error"), MB_ICONERROR);
			Release = 3000;
		}
		DX8_Compressor.fRelease = Release;
		if (Test)
			DefaultCore.TestUpdate(DX8_Compressor);
	}
	m_SRelease.SetPos(Release * 100);
	m_ERelease.Empty();
	m_ERelease.Format(_T("%.2f"), Release);
	UpdateData(false);
}


void CCompressorDlg::OnEnChangeEditThreshold()
{
	UpdateData(true);
	if (CheckData(m_EThreshold))
	{
		Threshold = _wtof(m_EThreshold);
		if (Threshold < -60)
		{
			MessageBox(_T("Must be in the range from -60 to 0."), _T("Error"), MB_ICONERROR);
			Threshold = -60;
		}
		if (Threshold > 0)
		{
			MessageBox(_T("Must be in the range from -60 to 0."), _T("Error"), MB_ICONERROR);
			Threshold = 0;
		}
		DX8_Compressor.fThreshold = Threshold;
		if (Test)
			DefaultCore.TestUpdate(DX8_Compressor);
	}
	m_SThreshold.SetPos(Threshold * 100);
	m_EThreshold.Empty();
	m_EThreshold.Format(_T("%.2f"), Threshold);
	UpdateData(false);
}


void CCompressorDlg::OnEnChangeEditRatio()
{
	UpdateData(true);
	if (CheckData(m_ERatio))
	{
		Ratio = _wtof(m_ERatio);
		if (Ratio < 1)
		{
			MessageBox(_T("Must be in the range from 1 to 100."), _T("Error"), MB_ICONERROR);
			Ratio = 1;
		}
		if (Ratio > 100)
		{
			MessageBox(_T("Must be in the range from 1 to 100."), _T("Error"), MB_ICONERROR);
			Ratio = 100;
		}
		DX8_Compressor.fRatio = Ratio;
		if (Test)
			DefaultCore.TestUpdate(DX8_Compressor);
	}
	m_SRatio.SetPos(Ratio * 100);
	m_ERatio.Empty();
	m_ERatio.Format(_T("%.2f"), Ratio);
	UpdateData(false);
}


void CCompressorDlg::OnEnChangeEditPredelay()
{
	UpdateData(true);
	if (CheckData(m_EPreDelay))
	{
		PreDelay = _wtof(m_EPreDelay);
		if (PreDelay < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 4."), _T("Error"), MB_ICONERROR);
			PreDelay = 0;
		}
		if (PreDelay > 4)
		{
			MessageBox(_T("Must be in the range from 0 to 4."), _T("Error"), MB_ICONERROR);
			PreDelay = 4;
		}
		DX8_Compressor.fPredelay = PreDelay;
		if (Test)
			DefaultCore.TestUpdate(DX8_Compressor);
	}
	m_SPreDelay.SetPos(PreDelay * 100);
	m_EPreDelay.Empty();
	m_EPreDelay.Format(_T("%.2f"), PreDelay);
	UpdateData(false);
}


void CCompressorDlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		DX8_Compressor.fGain = Gain;
		DX8_Compressor.fAttack = Attack;
		DX8_Compressor.fRelease = Release;
		DX8_Compressor.fThreshold = Threshold;
		DX8_Compressor.fRatio = Ratio;
		DX8_Compressor.fPredelay = PreDelay;

		DefaultCore.TestOn(_T("compressor"), 1);
		DefaultCore.TestUpdate(DX8_Compressor);
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CCompressorDlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(DX8_Compressor);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CCompressorDlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CCompressorDlg::OnClose()
{
	OnBnClickedCancel();
}
