// Equalizer10Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "Equalizer10Dlg.h"
#include "afxdialogex.h"


// CEqualizer10Dlg dialog

IMPLEMENT_DYNAMIC(CEqualizer10Dlg, CDialogEx)

CEqualizer10Dlg::CEqualizer10Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEqualizer10Dlg::IDD, pParent)
	, m_E125Hz(_T("0"))
	, m_E16KHz(_T("0"))
	, m_E1KHz(_T("0"))
	, m_E250Hz(_T("0"))
	, m_E2KHz(_T("0"))
	, m_E31Hz(_T("0"))
	, m_E4KHz(_T("0"))
	, m_E500Hz(_T("0"))
	, m_E63Hz(_T("0"))
	, m_E8KHz(_T("0"))
{

}

CEqualizer10Dlg::~CEqualizer10Dlg()
{
}

void CEqualizer10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_SLIDER_125HZ, m_S125Hz);
	DDX_Control(pDX, ID_SLIDER_16KHZ, m_S16KHz);
	DDX_Control(pDX, ID_SLIDER_1KHZ, m_S1KHz);
	DDX_Control(pDX, ID_SLIDER_250HZ, m_S250Hz);
	DDX_Control(pDX, ID_SLIDER_2KHZ, m_S2KHz);
	DDX_Control(pDX, ID_SLIDER_31HZ, m_S31Hz);
	DDX_Control(pDX, ID_SLIDER_4KHZ, m_S4KHz);
	DDX_Control(pDX, ID_SLIDER_500HZ, m_S500Hz);
	DDX_Control(pDX, ID_SLIDER_63HZ, m_S63Hz);
	DDX_Control(pDX, ID_SLIDER_8KHZ, m_S8KHz);
	DDX_Text(pDX, ID_EDIT_125HZ, m_E125Hz);
	DDX_Text(pDX, ID_EDIT_16KHZ, m_E16KHz);
	DDX_Text(pDX, ID_EDIT_1KHZ, m_E1KHz);
	DDX_Text(pDX, ID_EDIT_250HZ, m_E250Hz);
	DDX_Text(pDX, ID_EDIT_2KHZ, m_E2KHz);
	DDX_Text(pDX, ID_EDIT_31HZ, m_E31Hz);
	DDX_Text(pDX, ID_EDIT_4KHZ, m_E4KHz);
	DDX_Text(pDX, ID_EDIT_500HZ, m_E500Hz);
	DDX_Text(pDX, ID_EDIT_63HZ, m_E63Hz);
	DDX_Text(pDX, ID_EDIT_8KHZ, m_E8KHz);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CEqualizer10Dlg, CDialogEx)
	ON_WM_VSCROLL()
	ON_EN_CHANGE(ID_EDIT_31HZ, &CEqualizer10Dlg::OnEnChangeEdit31hz)
	ON_EN_CHANGE(ID_EDIT_63HZ, &CEqualizer10Dlg::OnEnChangeEdit63hz)
	ON_EN_CHANGE(ID_EDIT_125HZ, &CEqualizer10Dlg::OnEnChangeEdit125hz)
	ON_EN_CHANGE(ID_EDIT_250HZ, &CEqualizer10Dlg::OnEnChangeEdit250hz)
	ON_EN_CHANGE(ID_EDIT_500HZ, &CEqualizer10Dlg::OnEnChangeEdit500hz)
	ON_EN_CHANGE(ID_EDIT_1KHZ, &CEqualizer10Dlg::OnEnChangeEdit1khz)
	ON_EN_CHANGE(ID_EDIT_2KHZ, &CEqualizer10Dlg::OnEnChangeEdit2khz)
	ON_EN_CHANGE(ID_EDIT_4KHZ, &CEqualizer10Dlg::OnEnChangeEdit4khz)
	ON_EN_CHANGE(ID_EDIT_8KHZ, &CEqualizer10Dlg::OnEnChangeEdit8khz)
	ON_EN_CHANGE(ID_EDIT_16KHZ, &CEqualizer10Dlg::OnEnChangeEdit16khz)
	ON_BN_CLICKED(ID_BTESTONOFF, &CEqualizer10Dlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CEqualizer10Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEqualizer10Dlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CEqualizer10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_S125Hz.SetRange(-25, 25, TRUE); m_S125Hz.SetPos(0);
	m_S125Hz.SetTic(-20); m_S125Hz.SetTic(20); m_S125Hz.SetTic(0);
	m_S125Hz.SetTic(-10); m_S125Hz.SetTic(10);
	m_S16KHz.SetRange(-25, 25, TRUE); m_S16KHz.SetPos(0);
	m_S16KHz.SetTic(-20); m_S16KHz.SetTic(20); m_S16KHz.SetTic(0);
	m_S16KHz.SetTic(-10); m_S16KHz.SetTic(10);
	m_S1KHz.SetRange(-25, 25, TRUE); m_S1KHz.SetPos(0);
	m_S1KHz.SetTic(-20); m_S1KHz.SetTic(20); m_S1KHz.SetTic(0);
	m_S1KHz.SetTic(-10); m_S1KHz.SetTic(10);
	m_S250Hz.SetRange(-25, 25, TRUE); m_S250Hz.SetPos(0);
	m_S250Hz.SetTic(-20); m_S250Hz.SetTic(20); m_S250Hz.SetTic(0);
	m_S250Hz.SetTic(-10); m_S250Hz.SetTic(10);
	m_S2KHz.SetRange(-25, 25, TRUE); m_S2KHz.SetPos(0);
	m_S2KHz.SetTic(-20); m_S2KHz.SetTic(20); m_S2KHz.SetTic(0);
	m_S2KHz.SetTic(-10); m_S2KHz.SetTic(10);
	m_S31Hz.SetRange(-25, 25, TRUE); m_S31Hz.SetPos(0);
	m_S31Hz.SetTic(-20); m_S31Hz.SetTic(20); m_S31Hz.SetTic(0);
	m_S31Hz.SetTic(-10); m_S31Hz.SetTic(10);
	m_S4KHz.SetRange(-25, 25, TRUE); m_S4KHz.SetPos(0);
	m_S4KHz.SetTic(-20); m_S4KHz.SetTic(20); m_S4KHz.SetTic(0);
	m_S4KHz.SetTic(-10); m_S4KHz.SetTic(10);
	m_S500Hz.SetRange(-25, 25, TRUE); m_S500Hz.SetPos(0);
	m_S500Hz.SetTic(-20); m_S500Hz.SetTic(20); m_S500Hz.SetTic(0);
	m_S500Hz.SetTic(-10); m_S500Hz.SetTic(10);
	m_S63Hz.SetRange(-25, 25, TRUE); m_S63Hz.SetPos(0);
	m_S63Hz.SetTic(-20); m_S63Hz.SetTic(20); m_S63Hz.SetTic(0);
	m_S63Hz.SetTic(-10); m_S63Hz.SetTic(10);
	m_S8KHz.SetRange(-25, 25, TRUE); m_S8KHz.SetPos(0);
	m_S8KHz.SetTic(-20); m_S8KHz.SetTic(20); m_S8KHz.SetTic(0);
	m_S8KHz.SetTic(-10); m_S8KHz.SetTic(10);

	m_125Hz = m_16KHz = m_1KHz = m_250Hz = m_2KHz = m_31Hz = m_4KHz = m_500Hz = m_63Hz = m_8KHz = 0;
	BFX_Peakeq[0].fCenter = 31;
	BFX_Peakeq[1].fCenter = 63;
	BFX_Peakeq[2].fCenter = 125;
	BFX_Peakeq[3].fCenter = 250;
	BFX_Peakeq[4].fCenter = 500;
	BFX_Peakeq[5].fCenter = 1000;
	BFX_Peakeq[6].fCenter = 2000;
	BFX_Peakeq[7].fCenter = 4000;
	BFX_Peakeq[8].fCenter = 8000;
	BFX_Peakeq[9].fCenter = 16000;
	for (int i = 0; i < 10; i++)
	{
		BFX_Peakeq[i].lBand = 0;
		BFX_Peakeq[i].fBandwidth = 2.5;
		BFX_Peakeq[i].fQ = 0.0;
		BFX_Peakeq[i].fGain = 0;
		BFX_Peakeq[i].lChannel = BASS_BFX_CHANALL;
	}
	DefaultCore.TestOn(_T("peakeq"), 10);
	DefaultCore.TestUpdate(BFX_Peakeq);

	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
	Test = true;
	return TRUE;
}

// CEqualizer10Dlg message handlers


BOOL CEqualizer10Dlg::CheckData(CString Data)
{
	//Проверка каждого введенного символа на разрешенность
	for (int i = 0; i < Data.GetLength(); i++)
	{
		//Проверка является-ли символ: 0 1 2 3 4 5 6 7 8 9 - .
		//Если нет то ошибка, если да то идем дальше по циклу:
		if ((Data.GetAt(i) != '0') && (Data.GetAt(i) != '1') && (Data.GetAt(i) != '2') &&
			(Data.GetAt(i) != '3') && (Data.GetAt(i) != '4') && (Data.GetAt(i) != '5') &&
			(Data.GetAt(i) != '6') && (Data.GetAt(i) != '7') && (Data.GetAt(i) != '8') &&
			(Data.GetAt(i) != '9') && (Data.GetAt(i) != '-'))
		{
			MessageBox(_T("Incorrect Data."), _T("Error"), MB_ICONERROR);
			return FALSE;
		}

	}
	return TRUE;
}


void CEqualizer10Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_S31Hz)
	{
		m_31Hz = (-1)*m_S31Hz.GetPos();
		BFX_Peakeq[0].fGain = m_31Hz;
		m_E31Hz.Format(_T("%d"), m_31Hz);
	}
	if (pScrollBar == (CScrollBar *)&m_S63Hz)
	{
		m_63Hz = (-1)*m_S63Hz.GetPos();
		BFX_Peakeq[1].fGain = m_63Hz;
		m_E63Hz.Format(_T("%d"), m_63Hz);
	}
	if (pScrollBar == (CScrollBar *)&m_S125Hz)
	{
		m_125Hz = (-1)*m_S125Hz.GetPos();
		BFX_Peakeq[2].fGain = m_125Hz;
		m_E125Hz.Format(_T("%d"), m_125Hz);
	}
	if (pScrollBar == (CScrollBar *)&m_S250Hz)
	{
		m_250Hz = (-1)*m_S250Hz.GetPos();
		BFX_Peakeq[3].fGain = m_250Hz;
		m_E250Hz.Format(_T("%d"), m_250Hz);
	}
	if (pScrollBar == (CScrollBar *)&m_S500Hz)
	{
		m_500Hz = (-1)*m_S500Hz.GetPos();
		BFX_Peakeq[4].fGain = m_500Hz;
		m_E500Hz.Format(_T("%d"), m_500Hz);
	}
	if (pScrollBar == (CScrollBar *)&m_S1KHz)
	{
		m_1KHz = (-1)*m_S1KHz.GetPos();
		BFX_Peakeq[5].fGain = m_1KHz;
		m_E1KHz.Format(_T("%d"), m_1KHz);
	}
	if (pScrollBar == (CScrollBar *)&m_S2KHz)
	{
		m_2KHz = (-1)*m_S2KHz.GetPos();
		BFX_Peakeq[6].fGain = m_2KHz;
		m_E2KHz.Format(_T("%d"), m_2KHz);
	}
	if (pScrollBar == (CScrollBar *)&m_S4KHz)
	{
		m_4KHz = (-1)*m_S4KHz.GetPos();
		BFX_Peakeq[7].fGain = m_4KHz;
		m_E4KHz.Format(_T("%d"), m_4KHz);
	}
	if (pScrollBar == (CScrollBar *)&m_S8KHz)
	{
		m_8KHz = (-1)*m_S8KHz.GetPos();
		BFX_Peakeq[8].fGain = m_8KHz;
		m_E8KHz.Format(_T("%d"), m_8KHz);
	}
	if (pScrollBar == (CScrollBar *)&m_S16KHz)
	{
		m_16KHz = (-1)*m_S16KHz.GetPos();
		BFX_Peakeq[9].fGain = m_16KHz;
		m_E16KHz.Format(_T("%d"), m_16KHz);
	}
	if (Test)
		DefaultCore.TestUpdate(BFX_Peakeq);
	UpdateData(false);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}



void CEqualizer10Dlg::OnEnChangeEdit31hz()
{
	UpdateData(true);
	if (CheckData(m_E31Hz))
	{
		m_31Hz = _wtof(m_E31Hz);
		if (m_31Hz < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_31Hz = -25;
		}
		if (m_31Hz > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_31Hz = 25;
		}
		BFX_Peakeq[0].fGain = m_31Hz;
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S31Hz.SetPos((-1)*m_31Hz);
	m_E31Hz.Empty();
	m_E31Hz.Format(_T("%d"), m_31Hz);
	UpdateData(false);
}


void CEqualizer10Dlg::OnEnChangeEdit63hz()
{
	UpdateData(true);
	if (CheckData(m_E63Hz))
	{
		m_63Hz = _wtof(m_E63Hz);
		if (m_63Hz < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_63Hz = -25;
		}
		if (m_63Hz > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_63Hz = 25;
		}
		BFX_Peakeq[1].fGain = m_63Hz;
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S63Hz.SetPos((-1)*m_63Hz);
	m_E63Hz.Empty();
	m_E63Hz.Format(_T("%d"), m_63Hz);
	UpdateData(false);
}


void CEqualizer10Dlg::OnEnChangeEdit125hz()
{
	UpdateData(true);
	if (CheckData(m_E125Hz))
	{
		m_125Hz = _wtof(m_E125Hz);
		if (m_125Hz < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_125Hz = -25;
		}
		if (m_125Hz > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_125Hz = 25;
		}
		BFX_Peakeq[2].fGain = m_125Hz;
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S125Hz.SetPos((-1)*m_125Hz);
	m_E125Hz.Empty();
	m_E125Hz.Format(_T("%d"), m_125Hz);
	UpdateData(false);
}


void CEqualizer10Dlg::OnEnChangeEdit250hz()
{
	UpdateData(true);
	if (CheckData(m_E250Hz))
	{
		m_250Hz = _wtof(m_E250Hz);
		if (m_250Hz < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_250Hz = -25;
		}
		if (m_250Hz > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_250Hz = 25;
		}
		BFX_Peakeq[3].fGain = m_250Hz;
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S250Hz.SetPos((-1)*m_250Hz);
	m_E250Hz.Empty();
	m_E250Hz.Format(_T("%d"), m_250Hz);
	UpdateData(false);
}


void CEqualizer10Dlg::OnEnChangeEdit500hz()
{
	UpdateData(true);
	if (CheckData(m_E500Hz))
	{
		m_500Hz = _wtof(m_E500Hz);
		if (m_500Hz < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_500Hz = -25;
		}
		if (m_500Hz > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_500Hz = 25;
		}
		BFX_Peakeq[4].fGain = m_500Hz;
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S500Hz.SetPos((-1)*m_500Hz);
	m_E500Hz.Empty();
	m_E500Hz.Format(_T("%d"), m_500Hz);
	UpdateData(false);
}


void CEqualizer10Dlg::OnEnChangeEdit1khz()
{
	UpdateData(true);
	if (CheckData(m_E1KHz))
	{
		m_1KHz = _wtof(m_E1KHz);
		if (m_1KHz < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_1KHz = -25;
		}
		if (m_1KHz > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_1KHz = 25;
		}
		BFX_Peakeq[5].fGain = m_1KHz;
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S1KHz.SetPos((-1)*m_1KHz);
	m_E1KHz.Empty();
	m_E1KHz.Format(_T("%d"), m_1KHz);
	UpdateData(false);
}


void CEqualizer10Dlg::OnEnChangeEdit2khz()
{
	UpdateData(true);
	if (CheckData(m_E2KHz))
	{
		m_2KHz = _wtof(m_E2KHz);
		if (m_2KHz < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_2KHz = -25;
		}
		if (m_2KHz > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_2KHz = 25;
		}
		BFX_Peakeq[6].fGain = m_2KHz;
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S2KHz.SetPos((-1)*m_2KHz);
	m_E2KHz.Empty();
	m_E2KHz.Format(_T("%d"), m_2KHz);
	UpdateData(false);
}


void CEqualizer10Dlg::OnEnChangeEdit4khz()
{
	UpdateData(true);
	if (CheckData(m_E4KHz))
	{
		m_4KHz = _wtof(m_E4KHz);
		if (m_4KHz < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_4KHz = -25;
		}
		if (m_4KHz > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_4KHz = 25;
		}
		BFX_Peakeq[7].fGain = m_4KHz;
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S4KHz.SetPos((-1)*m_4KHz);
	m_E4KHz.Empty();
	m_E4KHz.Format(_T("%d"), m_4KHz);
	UpdateData(false);
}


void CEqualizer10Dlg::OnEnChangeEdit8khz()
{
	UpdateData(true);
	if (CheckData(m_E8KHz))
	{
		m_8KHz = _wtof(m_E8KHz);
		if (m_8KHz < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_8KHz = -25;
		}
		if (m_8KHz > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_8KHz = 25;
		}
		BFX_Peakeq[8].fGain = m_8KHz;
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S8KHz.SetPos((-1)*m_8KHz);
	m_E8KHz.Empty();
	m_E8KHz.Format(_T("%d"), m_8KHz);
	UpdateData(false);
}


void CEqualizer10Dlg::OnEnChangeEdit16khz()
{
	UpdateData(true);
	if (CheckData(m_E16KHz))
	{
		m_16KHz = _wtof(m_E16KHz);
		if (m_16KHz < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_16KHz = -25;
		}
		if (m_16KHz > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			m_16KHz = 25;
		}
		BFX_Peakeq[9].fGain = m_16KHz;
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S16KHz.SetPos((-1)*m_16KHz);
	m_E16KHz.Empty();
	m_E16KHz.Format(_T("%d"), m_16KHz);
	UpdateData(false);
}


void CEqualizer10Dlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		BFX_Peakeq[0].fGain = m_31Hz;
		BFX_Peakeq[1].fGain = m_63Hz;
		BFX_Peakeq[2].fGain = m_125Hz;
		BFX_Peakeq[3].fGain = m_250Hz;
		BFX_Peakeq[4].fGain = m_500Hz;
		BFX_Peakeq[5].fGain = m_1KHz;
		BFX_Peakeq[6].fGain = m_2KHz;
		BFX_Peakeq[7].fGain = m_4KHz;
		BFX_Peakeq[8].fGain = m_8KHz;
		BFX_Peakeq[9].fGain = m_16KHz;

		DefaultCore.TestOn(_T("peakeq"), 10);
		DefaultCore.TestUpdate(BFX_Peakeq);

		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CEqualizer10Dlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(BFX_Peakeq, 10);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CEqualizer10Dlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CEqualizer10Dlg::OnClose()
{
	OnBnClickedCancel();
}
