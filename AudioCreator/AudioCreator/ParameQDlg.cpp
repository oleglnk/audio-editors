// ParameQDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "ParameQDlg.h"
#include "afxdialogex.h"


// CParameQDlg dialog

IMPLEMENT_DYNAMIC(CParameQDlg, CDialogEx)

CParameQDlg::CParameQDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParameQDlg::IDD, pParent)
	, m_ECenter1(_T("80"))
	, m_ECenter2(_T("250"))
	, m_ECenter3(_T("1000"))
	, m_ECenter4(_T("4000"))
	, m_ECenter5(_T("16000"))
	, m_EWidth1(_T("12"))
	, m_EWidth2(_T("12"))
	, m_EWidth3(_T("12"))
	, m_EWidth4(_T("12"))
	, m_EWidth5(_T("12"))
{

}

CParameQDlg::~CParameQDlg()
{
}

void CParameQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_SLIDER_GAIN1, m_SGain1);
	DDX_Control(pDX, ID_SLIDER_GAIN2, m_SGain2);
	DDX_Control(pDX, ID_SLIDER_GAIN3, m_SGain3);
	DDX_Control(pDX, ID_SLIDER_GAIN4, m_SGain4);
	DDX_Control(pDX, ID_SLIDER_GAIN5, m_SGain5);
	DDX_Text(pDX, ID_EDIT_CENTER1, m_ECenter1);
	DDX_Text(pDX, ID_EDIT_CENTER2, m_ECenter2);
	DDX_Text(pDX, ID_EDIT_CENTER3, m_ECenter3);
	DDX_Text(pDX, ID_EDIT_CENTER4, m_ECenter4);
	DDX_Text(pDX, ID_EDIT_CENTER5, m_ECenter5);
	DDX_Text(pDX, ID_EDIT_WIDTH1, m_EWidth1);
	DDX_Text(pDX, ID_EDIT_WIDTH2, m_EWidth2);
	DDX_Text(pDX, ID_EDIT_WIDTH3, m_EWidth3);
	DDX_Text(pDX, ID_EDIT_WIDTH4, m_EWidth4);
	DDX_Text(pDX, ID_EDIT_WIDTH5, m_EWidth5);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CParameQDlg, CDialogEx)
	ON_WM_VSCROLL()
	ON_EN_CHANGE(ID_EDIT_CENTER1, &CParameQDlg::OnEnChangeEditCenter1)
	ON_EN_CHANGE(ID_EDIT_CENTER2, &CParameQDlg::OnEnChangeEditCenter2)
	ON_EN_CHANGE(ID_EDIT_CENTER3, &CParameQDlg::OnEnChangeEditCenter3)
	ON_EN_CHANGE(ID_EDIT_CENTER4, &CParameQDlg::OnEnChangeEditCenter4)
	ON_EN_CHANGE(ID_EDIT_CENTER5, &CParameQDlg::OnEnChangeEditCenter5)
	ON_EN_CHANGE(ID_EDIT_WIDTH1, &CParameQDlg::OnEnChangeEditWidth1)
	ON_EN_CHANGE(ID_EDIT_WIDTH2, &CParameQDlg::OnEnChangeEditWidth2)
	ON_EN_CHANGE(ID_EDIT_WIDTH3, &CParameQDlg::OnEnChangeEditWidth3)
	ON_EN_CHANGE(ID_EDIT_WIDTH4, &CParameQDlg::OnEnChangeEditWidth4)
	ON_EN_CHANGE(ID_EDIT_WIDTH5, &CParameQDlg::OnEnChangeEditWidth5)
	ON_BN_CLICKED(ID_BTESTONOFF, &CParameQDlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CParameQDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CParameQDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CParameQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DX8_ParameQ[0].fCenter = Center[0] = 80; 
	DX8_ParameQ[1].fCenter = Center[1] = 250; 
	DX8_ParameQ[2].fCenter = Center[2] = 1000; 
	DX8_ParameQ[3].fCenter = Center[3] = 4000; 
	DX8_ParameQ[4].fCenter = Center[4] = 16000;
	for (int i = 0; i < 5; i++)
	{
		DX8_ParameQ[i].fGain = Gain[i] = 0;
		DX8_ParameQ[i].fBandwidth = Bandwidth[i] = 12;
	}

	m_SGain1.SetRange(-15, 15, TRUE); m_SGain1.SetPos(0); 
	m_SGain1.SetTic(0); m_SGain1.SetTic(-7); m_SGain1.SetTic(7);
	m_SGain2.SetRange(-15, 15, TRUE); m_SGain2.SetPos(0); 
	m_SGain2.SetTic(0); m_SGain2.SetTic(-7); m_SGain2.SetTic(7);
	m_SGain3.SetRange(-15, 15, TRUE); m_SGain3.SetPos(0); 
	m_SGain3.SetTic(0); m_SGain3.SetTic(-7); m_SGain3.SetTic(7);
	m_SGain4.SetRange(-15, 15, TRUE); m_SGain4.SetPos(0); 
	m_SGain4.SetTic(0); m_SGain4.SetTic(-7); m_SGain4.SetTic(7);
	m_SGain5.SetRange(-15, 15, TRUE); m_SGain5.SetPos(0); 
	m_SGain5.SetTic(0); m_SGain5.SetTic(-7); m_SGain5.SetTic(7);
	
	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));

	DefaultCore.TestOn(_T("parameq"), 5);
	DefaultCore.TestUpdate(DX8_ParameQ);
	Test = true;

	UpdateData(false);
	return TRUE;
}

// CParameQDlg message handlers
BOOL CParameQDlg::CheckData(CString Data)
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


void CParameQDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SGain1)
	{
		Gain[0] = (-1)*m_SGain1.GetPos();
		DX8_ParameQ[0].fGain = Gain[0];
	}
	if (pScrollBar == (CScrollBar *)&m_SGain2)
	{
		Gain[1] = (-1)*m_SGain2.GetPos();
		DX8_ParameQ[1].fGain = Gain[1];
	}
	if (pScrollBar == (CScrollBar *)&m_SGain3)
	{
		Gain[2] = (-1)*m_SGain3.GetPos();
		DX8_ParameQ[2].fGain = Gain[2];
	}
	if (pScrollBar == (CScrollBar *)&m_SGain4)
	{
		Gain[3] = (-1)*m_SGain4.GetPos();
		DX8_ParameQ[3].fGain = Gain[3];
	}
	if (pScrollBar == (CScrollBar *)&m_SGain5)
	{
		Gain[4] = (-1)*m_SGain5.GetPos();
		DX8_ParameQ[4].fGain = Gain[4];
	}
	if (Test)
		DefaultCore.TestUpdate(DX8_ParameQ);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CParameQDlg::OnEnChangeEditCenter1()
{
	UpdateData(true);
	if (CheckData(m_ECenter1))
	{
		Center[0] = _wtoi(m_ECenter1);
		if (Center[0] < 80)
		{
			MessageBox(_T("Must be in the range from 80 to 16000."), _T("Error"), MB_ICONERROR);
			Center[0] = 80;
		}
		if (Center[0] > 16000)
		{
			MessageBox(_T("Must be in the range from 80 to 16000."), _T("Error"), MB_ICONERROR);
			Center[0] = 16000;
		}
		DX8_ParameQ[0].fCenter = Center[0];
		if (Test)
			DefaultCore.TestUpdate(DX8_ParameQ);
	}
	m_ECenter1.Empty();
	m_ECenter1.Format(_T("%d"), Center[0]);
	UpdateData(false);
}


void CParameQDlg::OnEnChangeEditCenter2()
{
	UpdateData(true);
	if (CheckData(m_ECenter2))
	{
		Center[1] = _wtoi(m_ECenter2);
		if (Center[1] < 80)
		{
			MessageBox(_T("Must be in the range from 80 to 16000."), _T("Error"), MB_ICONERROR);
			Center[1] = 80;
		}
		if (Center[1] > 16000)
		{
			MessageBox(_T("Must be in the range from 80 to 16000."), _T("Error"), MB_ICONERROR);
			Center[1] = 16000;
		}
		DX8_ParameQ[1].fCenter = Center[1];
		if (Test)
			DefaultCore.TestUpdate(DX8_ParameQ);
	}
	m_ECenter2.Empty();
	m_ECenter2.Format(_T("%d"), Center[1]);
	UpdateData(false);
}


void CParameQDlg::OnEnChangeEditCenter3()
{
	UpdateData(true);
	if (CheckData(m_ECenter3))
	{
		Center[2] = _wtoi(m_ECenter3);
		if (Center[2] < 80)
		{
			MessageBox(_T("Must be in the range from 80 to 16000."), _T("Error"), MB_ICONERROR);
			Center[2] = 80;
		}
		if (Center[2] > 16000)
		{
			MessageBox(_T("Must be in the range from 80 to 16000."), _T("Error"), MB_ICONERROR);
			Center[2] = 16000;
		}
		DX8_ParameQ[2].fCenter = Center[2];
		if (Test)
			DefaultCore.TestUpdate(DX8_ParameQ);
	}
	m_ECenter3.Empty();
	m_ECenter3.Format(_T("%d"), Center[2]);
	UpdateData(false);
}


void CParameQDlg::OnEnChangeEditCenter4()
{
	UpdateData(true);
	if (CheckData(m_ECenter4))
	{
		Center[3] = _wtoi(m_ECenter4);
		if (Center[3] < 80)
		{
			MessageBox(_T("Must be in the range from 80 to 16000."), _T("Error"), MB_ICONERROR);
			Center[3] = 80;
		}
		if (Center[3] > 16000)
		{
			MessageBox(_T("Must be in the range from 80 to 16000."), _T("Error"), MB_ICONERROR);
			Center[3] = 16000;
		}
		DX8_ParameQ[3].fCenter = Center[3];
		if (Test)
			DefaultCore.TestUpdate(DX8_ParameQ);
	}
	m_ECenter4.Empty();
	m_ECenter4.Format(_T("%d"), Center[3]);
	UpdateData(false);
}


void CParameQDlg::OnEnChangeEditCenter5()
{
	UpdateData(true);
	if (CheckData(m_ECenter5))
	{
		Center[4] = _wtoi(m_ECenter5);
		if (Center[4] < 80)
		{
			MessageBox(_T("Must be in the range from 80 to 16000."), _T("Error"), MB_ICONERROR);
			Center[4] = 80;
		}
		if (Center[4] > 16000)
		{
			MessageBox(_T("Must be in the range from 80 to 16000."), _T("Error"), MB_ICONERROR);
			Center[4] = 16000;
		}
		DX8_ParameQ[4].fCenter = Center[4];
		if (Test)
			DefaultCore.TestUpdate(DX8_ParameQ);
	}
	m_ECenter5.Empty();
	m_ECenter5.Format(_T("%d"), Center[4]);
	UpdateData(false);
}


void CParameQDlg::OnEnChangeEditWidth1()
{
	UpdateData(true);
	if (CheckData(m_EWidth1))
	{
		Bandwidth[0] = _wtoi(m_EWidth1);
		if (Bandwidth[0] < 1)
		{
			MessageBox(_T("Must be in the range from 1 to 36."), _T("Error"), MB_ICONERROR);
			Bandwidth[0] = 1;
		}
		if (Bandwidth[0] > 36)
		{
			MessageBox(_T("Must be in the range from 1 to 36."), _T("Error"), MB_ICONERROR);
			Bandwidth[0] = 36;
		}
		DX8_ParameQ[0].fBandwidth = Bandwidth[0];
		if (Test)
			DefaultCore.TestUpdate(DX8_ParameQ);
	}
	m_EWidth1.Empty();
	m_EWidth1.Format(_T("%d"), Bandwidth[0]);
	UpdateData(false);
}


void CParameQDlg::OnEnChangeEditWidth2()
{
	UpdateData(true);
	if (CheckData(m_EWidth2))
	{
		Bandwidth[1] = _wtoi(m_EWidth2);
		if (Bandwidth[1] < 1)
		{
			MessageBox(_T("Must be in the range from 1 to 36."), _T("Error"), MB_ICONERROR);
			Bandwidth[1] = 1;
		}
		if (Bandwidth[1] > 36)
		{
			MessageBox(_T("Must be in the range from 1 to 36."), _T("Error"), MB_ICONERROR);
			Bandwidth[1] = 36;
		}
		DX8_ParameQ[1].fBandwidth = Bandwidth[1];
		if (Test)
			DefaultCore.TestUpdate(DX8_ParameQ);
	}
	m_EWidth2.Empty();
	m_EWidth2.Format(_T("%d"), Bandwidth[1]);
	UpdateData(false);
}


void CParameQDlg::OnEnChangeEditWidth3()
{
	UpdateData(true);
	if (CheckData(m_EWidth3))
	{
		Bandwidth[2] = _wtoi(m_EWidth3);
		if (Bandwidth[2] < 1)
		{
			MessageBox(_T("Must be in the range from 1 to 36."), _T("Error"), MB_ICONERROR);
			Bandwidth[2] = 1;
		}
		if (Bandwidth[2] > 36)
		{
			MessageBox(_T("Must be in the range from 1 to 36."), _T("Error"), MB_ICONERROR);
			Bandwidth[2] = 36;
		}
		DX8_ParameQ[2].fBandwidth = Bandwidth[2];
		if (Test)
			DefaultCore.TestUpdate(DX8_ParameQ);
	}
	m_EWidth3.Empty();
	m_EWidth3.Format(_T("%d"), Bandwidth[2]);
	UpdateData(false);
}


void CParameQDlg::OnEnChangeEditWidth4()
{
	UpdateData(true);
	if (CheckData(m_EWidth4))
	{
		Bandwidth[3] = _wtoi(m_EWidth4);
		if (Bandwidth[3] < 1)
		{
			MessageBox(_T("Must be in the range from 1 to 36."), _T("Error"), MB_ICONERROR);
			Bandwidth[3] = 1;
		}
		if (Bandwidth[3] > 36)
		{
			MessageBox(_T("Must be in the range from 1 to 36."), _T("Error"), MB_ICONERROR);
			Bandwidth[3] = 36;
		}
		DX8_ParameQ[3].fBandwidth = Bandwidth[3];
		if (Test)
			DefaultCore.TestUpdate(DX8_ParameQ);
	}
	m_EWidth4.Empty();
	m_EWidth4.Format(_T("%d"), Bandwidth[3]);
	UpdateData(false);
}


void CParameQDlg::OnEnChangeEditWidth5()
{
	UpdateData(true);
	if (CheckData(m_EWidth5))
	{
		Bandwidth[4] = _wtoi(m_EWidth5);
		if (Bandwidth[4] < 1)
		{
			MessageBox(_T("Must be in the range from 1 to 36."), _T("Error"), MB_ICONERROR);
			Bandwidth[4] = 1;
		}
		if (Bandwidth[4] > 36)
		{
			MessageBox(_T("Must be in the range from 1 to 36."), _T("Error"), MB_ICONERROR);
			Bandwidth[4] = 36;
		}
		DX8_ParameQ[4].fBandwidth = Bandwidth[4];
		if (Test)
			DefaultCore.TestUpdate(DX8_ParameQ);
	}
	m_EWidth5.Empty();
	m_EWidth5.Format(_T("%d"), Bandwidth[4]);
	UpdateData(false);
}


void CParameQDlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			DX8_ParameQ[i].fCenter = Center[i];
			DX8_ParameQ[i].fGain = Gain[i];
			DX8_ParameQ[i].fBandwidth = Bandwidth[i];
		}

		DefaultCore.TestOn(_T("parameq"), 5);
		DefaultCore.TestUpdate(DX8_ParameQ);

		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CParameQDlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(DX8_ParameQ, 5);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CParameQDlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CParameQDlg::OnClose()
{
	OnBnClickedCancel();
}
