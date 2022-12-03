// EchoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "EchoDlg.h"
#include "afxdialogex.h"


// CEchoDlg dialog

IMPLEMENT_DYNAMIC(CEchoDlg, CDialogEx)

CEchoDlg::CEchoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEchoDlg::IDD, pParent)
	, m_EWetDryMix(_T("50.00"))
	, m_EFeedback(_T("50.00"))
	, m_ELDelay(_T("500.00"))
	, m_ERDelay(_T("500.00"))
{

}

CEchoDlg::~CEchoDlg()
{
}

void CEchoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_SLIDER_FEEDBACK, m_SFeedback);
	DDX_Control(pDX, ID_SLIDER_LDELAY, m_SLDelay);
	DDX_Control(pDX, ID_SLIDER_RDELAY, m_SRDelay);
	DDX_Control(pDX, ID_SLIDER_WETDRYMIX, m_SWetDryMix);
	DDX_Text(pDX, IDC_EDIT_FEEDBACK, m_EFeedback);
	DDX_Text(pDX, IDC_EDIT_LDELAY, m_ELDelay);
	DDX_Text(pDX, IDC_EDIT_RDELAY, m_ERDelay);
	DDX_Text(pDX, IDC_EDIT_WETDRYMIX, m_EWetDryMix);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CEchoDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_WETDRYMIX, &CEchoDlg::OnEnChangeEditWetdrymix)
	ON_EN_CHANGE(IDC_EDIT_FEEDBACK, &CEchoDlg::OnEnChangeEditFeedback)
	ON_EN_CHANGE(IDC_EDIT_LDELAY, &CEchoDlg::OnEnChangeEditLdelay)
	ON_EN_CHANGE(IDC_EDIT_RDELAY, &CEchoDlg::OnEnChangeEditRdelay)
	ON_BN_CLICKED(ID_BTESTONOFF, &CEchoDlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CEchoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEchoDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CEchoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DX8_Echo.fWetDryMix = WetDryMix = 50.00; 
	DX8_Echo.fFeedback = Feedback = 50.00;
	DX8_Echo.fLeftDelay = LDelay = 500.00; 
	DX8_Echo.fRightDelay = RDelay = 500.00;
	DX8_Echo.lPanDelay = FALSE;

	m_SWetDryMix.SetRange(0, 10000, TRUE); m_SWetDryMix.SetPos(5000);
	m_SFeedback.SetRange(0, 10000, TRUE);  m_SFeedback.SetPos(5000);
	m_SLDelay.SetRange(100, 200000, TRUE); m_SLDelay.SetPos(50000);
	m_SRDelay.SetRange(100, 200000, TRUE); m_SRDelay.SetPos(50000);

	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));

	DefaultCore.TestOn(_T("echo"), 1);
	DefaultCore.TestUpdate(DX8_Echo);
	Test = true;

	UpdateData(false);
	return TRUE;
}

// CEchoDlg message handlers


BOOL CEchoDlg::CheckData(CString Data)
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

void CEchoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SWetDryMix)
	{
		WetDryMix = m_SWetDryMix.GetPos() / 100.00;
		DX8_Echo.fWetDryMix = WetDryMix;
		m_EWetDryMix.Empty();
		m_EWetDryMix.Format(_T("%.2f"), WetDryMix);
	}
	if (pScrollBar == (CScrollBar *)&m_SFeedback)
	{
		Feedback = m_SFeedback.GetPos() / 100.00;
		DX8_Echo.fFeedback = Feedback;
		m_EFeedback.Empty();
		m_EFeedback.Format(_T("%.2f"), Feedback);
	}
	if (pScrollBar == (CScrollBar *)&m_SLDelay)
	{
		LDelay = m_SLDelay.GetPos() / 100.00;
		DX8_Echo.fLeftDelay = LDelay;
		m_ELDelay.Empty();
		m_ELDelay.Format(_T("%.2f"), LDelay);
	}
	if (pScrollBar == (CScrollBar *)&m_SRDelay)
	{
		RDelay = m_SRDelay.GetPos() / 100.00;
		DX8_Echo.fRightDelay = RDelay;
		m_ERDelay.Empty();
		m_ERDelay.Format(_T("%.2f"), RDelay);
	}
	if (Test == true)
		DefaultCore.TestUpdate(DX8_Echo);
	UpdateData(false);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



void CEchoDlg::OnEnChangeEditWetdrymix()
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
		DX8_Echo.fWetDryMix = WetDryMix;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Echo);
	}
	m_SWetDryMix.SetPos(WetDryMix * 100);
	m_EWetDryMix.Empty();
	m_EWetDryMix.Format(_T("%.2f"), WetDryMix);
	UpdateData(false);
}


void CEchoDlg::OnEnChangeEditFeedback()
{
	UpdateData(true);
	if (CheckData(m_EFeedback))
	{
		Feedback = _wtof(m_EFeedback);
		if (Feedback < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			Feedback = 0;
		}
		if (Feedback > 100)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			Feedback = 100;
		}
		DX8_Echo.fFeedback = Feedback;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Echo);
	}
	m_SFeedback.SetPos(Feedback * 100);
	m_EFeedback.Empty();
	m_EFeedback.Format(_T("%.2f"), Feedback);
	UpdateData(false);
}


void CEchoDlg::OnEnChangeEditLdelay()
{
	UpdateData(true);
	if (CheckData(m_ELDelay))
	{
		LDelay = _wtof(m_ELDelay);
		if (LDelay < 1)
		{
			MessageBox(_T("Must be in the range from 1 to 2000."), _T("Error"), MB_ICONERROR);
			LDelay = 1;
		}
		if (LDelay > 2000)
		{
			MessageBox(_T("Must be in the range from 1 to 2000."), _T("Error"), MB_ICONERROR);
			LDelay = 2000;
		}
		DX8_Echo.fLeftDelay = LDelay;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Echo);
	}
	m_SLDelay.SetPos(LDelay * 100);
	m_ELDelay.Empty();
	m_ELDelay.Format(_T("%.2f"), LDelay);
	UpdateData(false);
}


void CEchoDlg::OnEnChangeEditRdelay()
{
	UpdateData(true);
	if (CheckData(m_ERDelay))
	{
		RDelay = _wtof(m_ERDelay);
		if (RDelay < 1)
		{
			MessageBox(_T("Must be in the range from 1 to 2000."), _T("Error"), MB_ICONERROR);
			RDelay = 1;
		}
		if (RDelay > 2000)
		{
			MessageBox(_T("Must be in the range from 1 to 2000."), _T("Error"), MB_ICONERROR);
			RDelay = 2000;
		}
		DX8_Echo.fRightDelay = RDelay;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_Echo);
	}
	m_SRDelay.SetPos(RDelay * 100);
	m_ERDelay.Empty();
	m_ERDelay.Format(_T("%.2f"), RDelay);
	UpdateData(false);
}


void CEchoDlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		DX8_Echo.fWetDryMix = WetDryMix;
		DX8_Echo.fFeedback = Feedback;
		DX8_Echo.fLeftDelay = LDelay;
		DX8_Echo.fRightDelay = RDelay;
		DX8_Echo.lPanDelay = FALSE;

		DefaultCore.TestOn(_T("echo"), 1);
		DefaultCore.TestUpdate(DX8_Echo);

		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CEchoDlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(DX8_Echo);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CEchoDlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CEchoDlg::OnClose()
{
	OnBnClickedCancel();
}
