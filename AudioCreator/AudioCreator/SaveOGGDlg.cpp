// SaveOGGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "SaveOGGDlg.h"
#include "afxdialogex.h"


// CSaveOGGDlg dialog

IMPLEMENT_DYNAMIC(CSaveOGGDlg, CDialogEx)

CSaveOGGDlg::CSaveOGGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSaveOGGDlg::IDD, pParent)
	, m_EQuality(_T(""))
{

}

CSaveOGGDlg::~CSaveOGGDlg()
{
}

void CSaveOGGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_COMBO_QUALITY, m_CQuality);
	DDX_Text(pDX, ID_EDIT_QUALITY, m_EQuality);
	DDX_Control(pDX, ID_SLIDER_FILESIZE, m_SFileSize);
}


BEGIN_MESSAGE_MAP(CSaveOGGDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_CLOSE()
	ON_EN_CHANGE(ID_EDIT_QUALITY, &CSaveOGGDlg::OnEnChangeEditQuality)
	ON_CBN_SELCHANGE(ID_COMBO_QUALITY, &CSaveOGGDlg::OnCbnSelchangeComboQuality)
	ON_BN_CLICKED(IDOK, &CSaveOGGDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSaveOGGDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CSaveOGGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_SFileSize.SetRange(1, 5);
	m_SFileSize.SetPos(3);
	m_CQuality.InsertString(0, _T("Economic"));
	m_CQuality.InsertString(1, _T("Standart"));
	m_CQuality.InsertString(2, _T("High"));
	m_CQuality.InsertString(3, _T("Extreme"));
	m_CQuality.InsertString(4, _T("Insane"));
	m_CQuality.SelectString(2, _T("High"));
	m_EQuality = "3";
	Quality = 3;

	UpdateData(false);
	return TRUE;
}

// CSaveOGGDlg message handlers


BOOL CSaveOGGDlg::CheckData(CString Data)
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


void CSaveOGGDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SFileSize)
	{
		m_EQuality.Empty();
		switch (m_SFileSize.GetPos())
		{
		case 1:
			m_EQuality = "1";	Quality = 1;
			m_CQuality.SelectString(0, _T("Economic"));
			break;
		case 2:
			m_EQuality = "2";	Quality = 2;
			m_CQuality.SelectString(1, _T("Standard"));
			break;
		case 3:
			m_EQuality = "3";	Quality = 3;
			m_CQuality.SelectString(2, _T("High"));
			break;
		case 4:
			m_EQuality = "4";	Quality = 4;
			m_CQuality.SelectString(3, _T("Extreme"));
			break;
		case 5:
			m_EQuality = "5";	Quality = 5;
			m_CQuality.SelectString(4, _T("Insane"));
			break;
		}
		UpdateData(false);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSaveOGGDlg::OnClose()
{
	OnBnClickedCancel();
}

void CSaveOGGDlg::OnCbnSelchangeComboQuality()
{
	m_EQuality.Empty();
	switch (m_CQuality.GetCurSel())
	{
	case 0:
		m_EQuality = "1";
		m_SFileSize.SetPos(1);
		break;
	case 1:
		m_EQuality = "2";
		m_SFileSize.SetPos(2);
		break;
	case 2:
		m_EQuality = "3";
		m_SFileSize.SetPos(3);
		break;
	case 3:
		m_EQuality = "4";
		m_SFileSize.SetPos(4);
		break;
	case 4:
		m_EQuality = "5";
		m_SFileSize.SetPos(5);
		break;
	}
}

void CSaveOGGDlg::OnEnChangeEditQuality()
{
	UpdateData(true);
	if (CheckData(m_EQuality))
	{
		Quality = _wtoi(m_EQuality);
		if (Quality < 1)
			Quality = 1;
		if (Quality > 5)
			Quality = 5;
	}
	switch (Quality)
	{
	case 1:
		m_CQuality.SelectString(0, _T("Economic"));
		break;
	case 2:
		m_CQuality.SelectString(1, _T("Standart"));
		break;
	case 3:
		m_CQuality.SelectString(2, _T("High"));
		break;
	case 4:
		m_CQuality.SelectString(3, _T("Extreme"));
		break;
	case 5:
		m_CQuality.SelectString(4, _T("Insane"));
		break;
	}
	m_SFileSize.SetPos(Quality);
	m_EQuality.Empty();
	m_EQuality.Format(_T("%d"), Quality);
	UpdateData(false);
}


void CSaveOGGDlg::OnBnClickedOk()
{
	DefaultCore.SaveOGG(SavePath, Quality);
	CDialogEx::OnOK();
}


void CSaveOGGDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
