// GargleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "GargleDlg.h"
#include "afxdialogex.h"


// CGargleDlg dialog

IMPLEMENT_DYNAMIC(CGargleDlg, CDialogEx)

CGargleDlg::CGargleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGargleDlg::IDD, pParent)
	, m_ERate(_T("20"))
{

}

CGargleDlg::~CGargleDlg()
{
}

void CGargleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_SLIDER_RATE, m_SRate);
	DDX_Text(pDX, IDC_EDIT_RATE, m_ERate);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CGargleDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_RATE, &CGargleDlg::OnEnChangeEditRate)
	ON_BN_CLICKED(IDC_RADIO1, &CGargleDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CGargleDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(ID_BTESTONOFF, &CGargleDlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CGargleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGargleDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CGargleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DX8_Gargle.dwRateHz = RateHz = 20;
	DX8_Gargle.dwWaveShape = WaveShape = 0;

	m_SRate.SetRange(1, 1000, TRUE);
	m_SRate.SetPos(20);
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));

	DefaultCore.TestOn(_T("gargle"), 1);
	DefaultCore.TestUpdate(DX8_Gargle);
	Test = true;

	UpdateData(false);
	return TRUE;
}

// CGargleDlg message handlers

BOOL CGargleDlg::CheckData(CString Data)
{
	//Проверка каждого введенного символа на разрешенность
	for (int i = 0; i < Data.GetLength(); i++)
	{
		//Проверка является-ли символ: 0 1 2 3 4 5 6 7 8 9 - .
		//Если нет то ошибка, если да то идем дальше по циклу:
		if ((Data.GetAt(i) != '0') && (Data.GetAt(i) != '1') && (Data.GetAt(i) != '2') &&
			(Data.GetAt(i) != '3') && (Data.GetAt(i) != '4') && (Data.GetAt(i) != '5') &&
			(Data.GetAt(i) != '6') && (Data.GetAt(i) != '7') && (Data.GetAt(i) != '8') &&
			(Data.GetAt(i) != '9'))
		{
			MessageBox(_T("Incorrect Data."), _T("Error"), MB_ICONERROR);
			return FALSE;
		}

	}
	return TRUE;
}

void CGargleDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SRate)
	{
		RateHz = m_SRate.GetPos();
		DX8_Gargle.dwRateHz = RateHz;
		m_ERate.Empty();
		m_ERate.Format(_T("%d"), RateHz);
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Gargle);
		UpdateData(false);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CGargleDlg::OnEnChangeEditRate()
{
	UpdateData(true);
	if (CheckData(m_ERate))
	{
		RateHz = _wtoi(m_ERate);
		if (RateHz < 1)
		{
			MessageBox(_T("Must be in the range from 1 to 1000."), _T("Error"), MB_ICONERROR);
			RateHz = 1;
		}
		if (RateHz > 1000)
		{
			MessageBox(_T("Must be in the range from 1 to 1000."), _T("Error"), MB_ICONERROR);
			RateHz = 1000;
		}
		DX8_Gargle.dwRateHz = RateHz;
		if (Test)
			DefaultCore.TestUpdate(DX8_Gargle);
	}
	m_SRate.SetPos(RateHz);
	m_ERate.Empty();
	m_ERate.Format(_T("%d"), RateHz);
	UpdateData(false);
}


void CGargleDlg::OnBnClickedRadio1()
{
	CheckDlgButton(IDC_RADIO2, BST_UNCHECKED);
	DX8_Gargle.dwWaveShape = WaveShape = 0;
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Gargle);
}


void CGargleDlg::OnBnClickedRadio2()
{
	CheckDlgButton(IDC_RADIO1, BST_UNCHECKED);
	DX8_Gargle.dwWaveShape = WaveShape = 1;
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Gargle);
}


void CGargleDlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		DX8_Gargle.dwRateHz = RateHz;
		DX8_Gargle.dwWaveShape = WaveShape;

		DefaultCore.TestOn(_T("gargle"), 1);
		DefaultCore.TestUpdate(DX8_Gargle);

		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CGargleDlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(DX8_Gargle);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CGargleDlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CGargleDlg::OnClose()
{
	OnBnClickedCancel();
}
