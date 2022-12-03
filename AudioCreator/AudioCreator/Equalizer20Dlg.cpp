// Equalizer20Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "Equalizer20Dlg.h"
#include "afxdialogex.h"


// CEqualizer20Dlg dialog

IMPLEMENT_DYNAMIC(CEqualizer20Dlg, CDialogEx)

CEqualizer20Dlg::CEqualizer20Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEqualizer20Dlg::IDD, pParent)
	, m_E31Hz(_T("0"))
	, m_E44Hz(_T("0"))
	, m_E63Hz(_T("0"))
	, m_E88Hz(_T("0"))
	, m_E125Hz(_T("0"))
	, m_E180Hz(_T("0"))
	, m_E250Hz(_T("0"))
	, m_E355Hz(_T("0"))
	, m_E500Hz(_T("0"))
	, m_E710Hz(_T("0"))
	, m_E1KHz(_T("0"))
	, m_E1P4KHz(_T("0"))
	, m_E2KHz(_T("0"))
	, m_E2P8KHz(_T("0"))
	, m_E4KHz(_T("0"))
	, m_E5P6KHz(_T("0"))
	, m_E8KHz(_T("0"))
	, m_E11P3KHz(_T("0"))
	, m_E16KHz(_T("0"))
	, m_E22KHz(_T("0"))
{

}

CEqualizer20Dlg::~CEqualizer20Dlg()
{
}

void CEqualizer20Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//Sliders
	DDX_Control(pDX, ID_SLIDER_31HZ20, m_S31Hz);
	DDX_Control(pDX, ID_SLIDER_44HZ20, m_S44Hz);
	DDX_Control(pDX, ID_SLIDER_63HZ20, m_S63Hz);
	DDX_Control(pDX, ID_SLIDER_88HZ20, m_S88Hz);
	DDX_Control(pDX, ID_SLIDER_125HZ20, m_S125Hz);
	DDX_Control(pDX, ID_SLIDER_180HZ20, m_S180Hz);
	DDX_Control(pDX, ID_SLIDER_250HZ20, m_S250Hz);
	DDX_Control(pDX, ID_SLIDER_355HZ20, m_S355Hz);
	DDX_Control(pDX, ID_SLIDER_500HZ20, m_S500Hz);
	DDX_Control(pDX, ID_SLIDER_710HZ20, m_S710Hz);
	DDX_Control(pDX, ID_SLIDER_1KHZ20, m_S1KHz);
	DDX_Control(pDX, ID_SLIDER_1P4KHZ20, m_S1P4KHz);
	DDX_Control(pDX, ID_SLIDER_2KHZ20, m_S2KHz);
	DDX_Control(pDX, ID_SLIDER_2P8KHZ20, m_S2P8KHz);
	DDX_Control(pDX, ID_SLIDER_4KHZ20, m_S4KHz);
	DDX_Control(pDX, ID_SLIDER_5P6KHZ20, m_S5P6KHz);
	DDX_Control(pDX, ID_SLIDER_8KHZ20, m_S8KHz);
	DDX_Control(pDX, ID_SLIDER_11P3KHZ20, m_S11P3KHz);
	DDX_Control(pDX, ID_SLIDER_16KHZ20, m_S16KHz);
	DDX_Control(pDX, ID_SLIDER_22KHZ20, m_S22KHz);
	//Edits
	DDX_Text(pDX, ID_EDIT_31HZ20, m_E31Hz);
	DDX_Text(pDX, ID_EDIT_44HZ20, m_E44Hz);
	DDX_Text(pDX, ID_EDIT_63HZ20, m_E63Hz);
	DDX_Text(pDX, ID_EDIT_88HZ20, m_E88Hz);
	DDX_Text(pDX, ID_EDIT_125HZ20, m_E125Hz);
	DDX_Text(pDX, ID_EDIT_180HZ20, m_E180Hz);
	DDX_Text(pDX, ID_EDIT_250HZ20, m_E250Hz);
	DDX_Text(pDX, ID_EDIT_355HZ20, m_E355Hz);
	DDX_Text(pDX, ID_EDIT_500HZ20, m_E500Hz);
	DDX_Text(pDX, ID_EDIT_710HZ20, m_E710Hz);
	DDX_Text(pDX, ID_EDIT_1KHZ20, m_E1KHz);
	DDX_Text(pDX, ID_EDIT_1P4KHZ20, m_E1P4KHz);
	DDX_Text(pDX, ID_EDIT_2KHZ20, m_E2KHz);
	DDX_Text(pDX, ID_EDIT_2P8KHZ20, m_E2P8KHz);
	DDX_Text(pDX, ID_EDIT_4KHZ20, m_E4KHz);
	DDX_Text(pDX, ID_EDIT_5P6KHZ20, m_E5P6KHz);
	DDX_Text(pDX, ID_EDIT_8KHZ20, m_E8KHz);
	DDX_Text(pDX, ID_EDIT_11P3KHZ20, m_E11P3KHz);
	DDX_Text(pDX, ID_EDIT_16KHZ20, m_E16KHz);
	DDX_Text(pDX, ID_EDIT_22KHZ20, m_E22KHz);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CEqualizer20Dlg, CDialogEx)
	ON_WM_VSCROLL()
	ON_EN_CHANGE(ID_EDIT_31HZ20, &CEqualizer20Dlg::OnEnChangeEdit31hz20)
	ON_EN_CHANGE(ID_EDIT_44HZ20, &CEqualizer20Dlg::OnEnChangeEdit44hz20)
	ON_EN_CHANGE(ID_EDIT_63HZ20, &CEqualizer20Dlg::OnEnChangeEdit63hz20)
	ON_EN_CHANGE(ID_EDIT_88HZ20, &CEqualizer20Dlg::OnEnChangeEdit88hz20)
	ON_EN_CHANGE(ID_EDIT_125HZ20, &CEqualizer20Dlg::OnEnChangeEdit125hz20)
	ON_EN_CHANGE(ID_EDIT_180HZ20, &CEqualizer20Dlg::OnEnChangeEdit180hz20)
	ON_EN_CHANGE(ID_EDIT_250HZ20, &CEqualizer20Dlg::OnEnChangeEdit250hz20)
	ON_EN_CHANGE(ID_EDIT_355HZ20, &CEqualizer20Dlg::OnEnChangeEdit355hz20)
	ON_EN_CHANGE(ID_EDIT_500HZ20, &CEqualizer20Dlg::OnEnChangeEdit500hz20)
	ON_EN_CHANGE(ID_EDIT_710HZ20, &CEqualizer20Dlg::OnEnChangeEdit710hz20)
	ON_EN_CHANGE(ID_EDIT_1KHZ20, &CEqualizer20Dlg::OnEnChangeEdit1khz20)
	ON_EN_CHANGE(ID_EDIT_1P4KHZ20, &CEqualizer20Dlg::OnEnChangeEdit1p4khz20)
	ON_EN_CHANGE(ID_EDIT_2KHZ20, &CEqualizer20Dlg::OnEnChangeEdit2khz20)
	ON_EN_CHANGE(ID_EDIT_2P8KHZ20, &CEqualizer20Dlg::OnEnChangeEdit2p8khz20)
	ON_EN_CHANGE(ID_EDIT_4KHZ20, &CEqualizer20Dlg::OnEnChangeEdit4khz20)
	ON_EN_CHANGE(ID_EDIT_5P6KHZ20, &CEqualizer20Dlg::OnEnChangeEdit5p6khz20)
	ON_EN_CHANGE(ID_EDIT_8KHZ20, &CEqualizer20Dlg::OnEnChangeEdit8khz20)
	ON_EN_CHANGE(ID_EDIT_11P3KHZ20, &CEqualizer20Dlg::OnEnChangeEdit11p3khz20)
	ON_EN_CHANGE(ID_EDIT_16KHZ20, &CEqualizer20Dlg::OnEnChangeEdit16khz20)
	ON_EN_CHANGE(ID_EDIT_22KHZ20, &CEqualizer20Dlg::OnEnChangeEdit22khz20)
	ON_BN_CLICKED(ID_BTESTONOFF, &CEqualizer20Dlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CEqualizer20Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEqualizer20Dlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CEqualizer20Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//31
	m_S31Hz.SetRange(-25, 25, TRUE);	m_S31Hz.SetPos(0);
	m_S31Hz.SetTic(-20); m_S31Hz.SetTic(20); m_S31Hz.SetTic(0);
	m_S31Hz.SetTic(-10); m_S31Hz.SetTic(10);
	//44
	m_S44Hz.SetRange(-25, 25, TRUE);	m_S44Hz.SetPos(0);
	m_S44Hz.SetTic(-20); m_S44Hz.SetTic(20); m_S44Hz.SetTic(0);
	m_S44Hz.SetTic(-10); m_S44Hz.SetTic(10);
	//63
	m_S63Hz.SetRange(-25, 25, TRUE);	m_S63Hz.SetPos(0);
	m_S63Hz.SetTic(-20); m_S63Hz.SetTic(20); m_S63Hz.SetTic(0);
	m_S63Hz.SetTic(-10); m_S63Hz.SetTic(10);
	//88
	m_S88Hz.SetRange(-25, 25, TRUE);	m_S88Hz.SetPos(0);
	m_S88Hz.SetTic(-20); m_S88Hz.SetTic(20); m_S88Hz.SetTic(0);
	m_S88Hz.SetTic(-10); m_S88Hz.SetTic(10);
	//125
	m_S125Hz.SetRange(-25, 25, TRUE);	m_S125Hz.SetPos(0);
	m_S125Hz.SetTic(-20); m_S125Hz.SetTic(20); m_S125Hz.SetTic(0);
	m_S125Hz.SetTic(-10); m_S125Hz.SetTic(10);
	//180
	m_S180Hz.SetRange(-25, 25, TRUE);	m_S180Hz.SetPos(0);
	m_S180Hz.SetTic(-20); m_S180Hz.SetTic(20); m_S180Hz.SetTic(0);
	m_S180Hz.SetTic(-10); m_S180Hz.SetTic(10);
	//250
	m_S250Hz.SetRange(-25, 25, TRUE);	m_S250Hz.SetPos(0);
	m_S250Hz.SetTic(-20); m_S250Hz.SetTic(20); m_S250Hz.SetTic(0);
	m_S250Hz.SetTic(-10); m_S250Hz.SetTic(10);
	//355
	m_S355Hz.SetRange(-25, 25, TRUE);	m_S355Hz.SetPos(0);
	m_S355Hz.SetTic(-20); m_S355Hz.SetTic(20); m_S355Hz.SetTic(0);
	m_S355Hz.SetTic(-10); m_S355Hz.SetTic(10);
	//500
	m_S500Hz.SetRange(-25, 25, TRUE);	m_S500Hz.SetPos(0);
	m_S500Hz.SetTic(-20); m_S500Hz.SetTic(20); m_S500Hz.SetTic(0);
	m_S500Hz.SetTic(-10); m_S500Hz.SetTic(10);
	//710
	m_S710Hz.SetRange(-25, 25, TRUE);	m_S710Hz.SetPos(0);
	m_S710Hz.SetTic(-20); m_S710Hz.SetTic(20); m_S710Hz.SetTic(0);
	m_S710Hz.SetTic(-10); m_S710Hz.SetTic(10);
	//1K
	m_S1KHz.SetRange(-25, 25, TRUE);	m_S1KHz.SetPos(0);
	m_S1KHz.SetTic(-20); m_S1KHz.SetTic(20); m_S1KHz.SetTic(0);
	m_S1KHz.SetTic(-10); m_S1KHz.SetTic(10);
	//1.4K
	m_S1P4KHz.SetRange(-25, 25, TRUE);	m_S1P4KHz.SetPos(0);
	m_S1P4KHz.SetTic(-20); m_S1P4KHz.SetTic(20); m_S1P4KHz.SetTic(0);
	m_S1P4KHz.SetTic(-10); m_S1P4KHz.SetTic(10);
	//2K
	m_S2KHz.SetRange(-25, 25, TRUE);	m_S2KHz.SetPos(0);
	m_S2KHz.SetTic(-20); m_S2KHz.SetTic(20); m_S2KHz.SetTic(0);
	m_S2KHz.SetTic(-10); m_S2KHz.SetTic(10);
	//2.8K
	m_S2P8KHz.SetRange(-25, 25, TRUE);	m_S2P8KHz.SetPos(0);
	m_S2P8KHz.SetTic(-20); m_S2P8KHz.SetTic(20); m_S2P8KHz.SetTic(0);
	m_S2P8KHz.SetTic(-10); m_S2P8KHz.SetTic(10);
	//4K
	m_S4KHz.SetRange(-25, 25, TRUE);	m_S4KHz.SetPos(0);
	m_S4KHz.SetTic(-20); m_S4KHz.SetTic(20); m_S4KHz.SetTic(0);
	m_S4KHz.SetTic(-10); m_S4KHz.SetTic(10);
	//5.6K
	m_S5P6KHz.SetRange(-25, 25, TRUE);	m_S5P6KHz.SetPos(0);
	m_S5P6KHz.SetTic(-20); m_S5P6KHz.SetTic(20); m_S5P6KHz.SetTic(0);
	m_S5P6KHz.SetTic(-10); m_S5P6KHz.SetTic(10);
	//8K
	m_S8KHz.SetRange(-25, 25, TRUE);	m_S8KHz.SetPos(0);
	m_S8KHz.SetTic(-20); m_S8KHz.SetTic(20); m_S8KHz.SetTic(0);
	m_S8KHz.SetTic(-10); m_S8KHz.SetTic(10);
	//11.3K
	m_S11P3KHz.SetRange(-25, 25, TRUE);	m_S11P3KHz.SetPos(0);
	m_S11P3KHz.SetTic(-20); m_S11P3KHz.SetTic(20); m_S11P3KHz.SetTic(0);
	m_S11P3KHz.SetTic(-10); m_S11P3KHz.SetTic(10);
	//16K
	m_S16KHz.SetRange(-25, 25, TRUE);	m_S16KHz.SetPos(0);
	m_S16KHz.SetTic(-20); m_S16KHz.SetTic(20); m_S16KHz.SetTic(0);
	m_S16KHz.SetTic(-10); m_S16KHz.SetTic(10);
	//22K
	m_S22KHz.SetRange(-25, 25, TRUE);	m_S22KHz.SetPos(0);
	m_S22KHz.SetTic(-20); m_S22KHz.SetTic(20); m_S22KHz.SetTic(0);
	m_S22KHz.SetTic(-10); m_S22KHz.SetTic(10);

	BFX_Peakeq[0].fCenter = 31;			BFX_Peakeq[10].fCenter = 1000;
	BFX_Peakeq[1].fCenter = 44;			BFX_Peakeq[11].fCenter = 1400;
	BFX_Peakeq[2].fCenter = 63;			BFX_Peakeq[12].fCenter = 2000;
	BFX_Peakeq[3].fCenter = 80;			BFX_Peakeq[13].fCenter = 2800;
	BFX_Peakeq[4].fCenter = 125;		BFX_Peakeq[14].fCenter = 4000;
	BFX_Peakeq[5].fCenter = 180;		BFX_Peakeq[15].fCenter = 5600;
	BFX_Peakeq[6].fCenter = 250;		BFX_Peakeq[16].fCenter = 8000;
	BFX_Peakeq[7].fCenter = 355;		BFX_Peakeq[17].fCenter = 11300;
	BFX_Peakeq[8].fCenter = 500;		BFX_Peakeq[18].fCenter = 16000;
	BFX_Peakeq[9].fCenter = 710;		BFX_Peakeq[19].fCenter = 22000;
	for (int i = 0; i < 20; i++)
	{
		BFX_Peakeq[i].fGain = Bands[i] = 0;
		BFX_Peakeq[i].lBand = 0;
		BFX_Peakeq[i].fBandwidth = 2.5;
		BFX_Peakeq[i].fQ = 0.0;
		BFX_Peakeq[i].lChannel = BASS_BFX_CHANALL;
	}
	DefaultCore.TestOn(_T("peakeq"), 20);
	DefaultCore.TestUpdate(BFX_Peakeq);

	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
	Test = true;

	return TRUE;
}

// CEqualizer20Dlg message handlers


BOOL CEqualizer20Dlg::CheckData(CString Data)
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
			return FALSE;
	}
	return TRUE;
}

void CEqualizer20Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//0
	if (pScrollBar == (CScrollBar *)&m_S31Hz)
	{
		Bands[0] = (-1)*m_S31Hz.GetPos();
		BFX_Peakeq[0].fGain = Bands[0];
		m_E31Hz.Format(_T("%d"), Bands[0]);
	}
	//1
	if (pScrollBar == (CScrollBar *)&m_S44Hz)
	{
		Bands[1] = (-1)*m_S44Hz.GetPos();
		BFX_Peakeq[1].fGain = Bands[1];
		m_E44Hz.Format(_T("%d"), Bands[1]);
	}
	//2
	if (pScrollBar == (CScrollBar *)&m_S63Hz)
	{
		Bands[2] = (-1)*m_S63Hz.GetPos();
		BFX_Peakeq[2].fGain = Bands[2];
		m_E63Hz.Format(_T("%d"), Bands[2]);
	}
	//3
	if (pScrollBar == (CScrollBar *)&m_S88Hz)
	{
		Bands[3] = (-1)*m_S88Hz.GetPos();
		BFX_Peakeq[3].fGain = Bands[3];
		m_E88Hz.Format(_T("%d"), Bands[3]);
	}
	//4
	if (pScrollBar == (CScrollBar *)&m_S125Hz)
	{
		Bands[4] = (-1)*m_S125Hz.GetPos();
		BFX_Peakeq[4].fGain = Bands[4];
		m_E125Hz.Format(_T("%d"), Bands[4]);
	}
	//5
	if (pScrollBar == (CScrollBar *)&m_S180Hz)
	{
		Bands[5] = (-1)*m_S180Hz.GetPos();
		BFX_Peakeq[5].fGain = Bands[5];
		m_E180Hz.Format(_T("%d"), Bands[5]);
	}
	//6
	if (pScrollBar == (CScrollBar *)&m_S250Hz)
	{
		Bands[6] = (-1)*m_S250Hz.GetPos();
		BFX_Peakeq[6].fGain = Bands[6];
		m_E250Hz.Format(_T("%d"), Bands[6]);
	}
	//7
	if (pScrollBar == (CScrollBar *)&m_S355Hz)
	{
		Bands[7] = (-1)*m_S355Hz.GetPos();
		BFX_Peakeq[7].fGain = Bands[7];
		m_E355Hz.Format(_T("%d"), Bands[7]);
	}
	//8
	if (pScrollBar == (CScrollBar *)&m_S500Hz)
	{
		Bands[8] = (-1)*m_S500Hz.GetPos();
		BFX_Peakeq[8].fGain = Bands[8];
		m_E500Hz.Format(_T("%d"), Bands[8]);
	}
	//9
	if (pScrollBar == (CScrollBar *)&m_S710Hz)
	{
		Bands[9] = (-1)*m_S710Hz.GetPos();
		BFX_Peakeq[9].fGain = Bands[9];
		m_E710Hz.Format(_T("%d"), Bands[9]);
	}
	//10
	if (pScrollBar == (CScrollBar *)&m_S1KHz)
	{
		Bands[10] = (-1)*m_S1KHz.GetPos();
		BFX_Peakeq[10].fGain = Bands[10];
		m_E1KHz.Format(_T("%d"), Bands[10]);
	}
	//11
	if (pScrollBar == (CScrollBar *)&m_S1P4KHz)
	{
		Bands[11] = (-1)*m_S1P4KHz.GetPos();
		BFX_Peakeq[11].fGain = Bands[11];
		m_E1P4KHz.Format(_T("%d"), Bands[11]);
	}
	//12
	if (pScrollBar == (CScrollBar *)&m_S2KHz)
	{
		Bands[12] = (-1)*m_S2KHz.GetPos();
		BFX_Peakeq[12].fGain = Bands[12];
		m_E2KHz.Format(_T("%d"), Bands[12]);
	}
	//13
	if (pScrollBar == (CScrollBar *)&m_S2P8KHz)
	{
		Bands[13] = (-1)*m_S2P8KHz.GetPos();
		BFX_Peakeq[13].fGain = Bands[13];
		m_E2P8KHz.Format(_T("%d"), Bands[13]);
	}
	//14
	if (pScrollBar == (CScrollBar *)&m_S4KHz)
	{
		Bands[14] = (-1)*m_S4KHz.GetPos();
		BFX_Peakeq[14].fGain = Bands[14];
		m_E4KHz.Format(_T("%d"), Bands[14]);
	}
	//15
	if (pScrollBar == (CScrollBar *)&m_S5P6KHz)
	{
		Bands[15] = (-1)*m_S5P6KHz.GetPos();
		BFX_Peakeq[15].fGain = Bands[15];
		m_E5P6KHz.Format(_T("%d"), Bands[15]);
	}
	//16
	if (pScrollBar == (CScrollBar *)&m_S8KHz)
	{
		Bands[16] = (-1)*m_S8KHz.GetPos();
		BFX_Peakeq[16].fGain = Bands[16];
		m_E8KHz.Format(_T("%d"), Bands[16]);
	}
	//17
	if (pScrollBar == (CScrollBar *)&m_S11P3KHz)
	{
		Bands[17] = (-1)*m_S11P3KHz.GetPos();
		BFX_Peakeq[17].fGain = Bands[17];
		m_E11P3KHz.Format(_T("%d"), Bands[17]);
	}
	//18
	if (pScrollBar == (CScrollBar *)&m_S16KHz)
	{
		Bands[18] = (-1)*m_S16KHz.GetPos();
		BFX_Peakeq[18].fGain = Bands[18];
		m_E16KHz.Format(_T("%d"), Bands[18]);
	}
	//19
	if (pScrollBar == (CScrollBar *)&m_S22KHz)
	{
		Bands[19] = (-1)*m_S22KHz.GetPos();
		BFX_Peakeq[19].fGain = Bands[19];
		m_E22KHz.Format(_T("%d"), Bands[19]);
	}
	if (Test)
		DefaultCore.TestUpdate(BFX_Peakeq);
	UpdateData(false);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}



void CEqualizer20Dlg::OnEnChangeEdit31hz20()
{
	UpdateData(true);
	if (CheckData(m_E31Hz))
	{
		Bands[0] = _wtof(m_E31Hz);
		if (Bands[0] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[0] = -25;
		}
		if (Bands[0] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[0] = 25;
		}
		BFX_Peakeq[0].fGain = Bands[0];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S31Hz.SetPos((-1)*Bands[0]);
	m_E31Hz.Empty();
	m_E31Hz.Format(_T("%d"), Bands[0]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit44hz20()
{
	UpdateData(true);
	if (CheckData(m_E44Hz))
	{
		Bands[1] = _wtof(m_E44Hz);
		if (Bands[1] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[1] = -25;
		}
		if (Bands[1] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[1] = 25;
		}
		BFX_Peakeq[1].fGain = Bands[1];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S44Hz.SetPos((-1)*Bands[1]);
	m_E44Hz.Empty();
	m_E44Hz.Format(_T("%d"), Bands[1]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit63hz20()
{
	UpdateData(true);
	if (CheckData(m_E63Hz))
	{
		Bands[2] = _wtof(m_E63Hz);
		if (Bands[2] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[2] = -25;
		}
		if (Bands[2] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[2] = 25;
		}
		BFX_Peakeq[2].fGain = Bands[2];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S63Hz.SetPos((-1)*Bands[2]);
	m_E63Hz.Empty();
	m_E63Hz.Format(_T("%d"), Bands[2]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit88hz20()
{
	UpdateData(true);
	if (CheckData(m_E88Hz))
	{
		Bands[3] = _wtof(m_E88Hz);
		if (Bands[3] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[3] = -25;
		}
		if (Bands[3] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[3] = 25;
		}
		BFX_Peakeq[3].fGain = Bands[3];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S88Hz.SetPos((-1)*Bands[3]);
	m_E88Hz.Empty();
	m_E88Hz.Format(_T("%d"), Bands[3]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit125hz20()
{
	UpdateData(true);
	if (CheckData(m_E125Hz))
	{
		Bands[4] = _wtof(m_E125Hz);
		if (Bands[4] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[4] = -25;
		}
		if (Bands[4] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[4] = 25;
		}
		BFX_Peakeq[4].fGain = Bands[4];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S125Hz.SetPos((-1)*Bands[4]);
	m_E125Hz.Empty();
	m_E125Hz.Format(_T("%d"), Bands[4]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit180hz20()
{
	UpdateData(true);
	if (CheckData(m_E180Hz))
	{
		Bands[5] = _wtof(m_E180Hz);
		if (Bands[5] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[5] = -25;
		}
		if (Bands[5] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[5] = 25;
		}
		BFX_Peakeq[5].fGain = Bands[5];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S180Hz.SetPos((-1)*Bands[5]);
	m_E180Hz.Empty();
	m_E180Hz.Format(_T("%d"), Bands[5]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit250hz20()
{
	UpdateData(true);
	if (CheckData(m_E250Hz))
	{
		Bands[6] = _wtof(m_E250Hz);
		if (Bands[6] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[6] = -25;
		}
		if (Bands[6] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[6] = 25;
		}
		BFX_Peakeq[6].fGain = Bands[6];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S250Hz.SetPos((-1)*Bands[6]);
	m_E250Hz.Empty();
	m_E250Hz.Format(_T("%d"), Bands[6]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit355hz20()
{
	UpdateData(true);
	if (CheckData(m_E355Hz))
	{
		Bands[7] = _wtof(m_E355Hz);
		if (Bands[7] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[7] = -25;
		}
		if (Bands[7] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[7] = 25;
		}
		BFX_Peakeq[7].fGain = Bands[7];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S355Hz.SetPos((-1)*Bands[7]);
	m_E355Hz.Empty();
	m_E355Hz.Format(_T("%d"), Bands[7]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit500hz20()
{
	UpdateData(true);
	if (CheckData(m_E500Hz))
	{
		Bands[8] = _wtof(m_E500Hz);
		if (Bands[8] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[8] = -25;
		}
		if (Bands[8] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[8] = 25;
		}
		BFX_Peakeq[8].fGain = Bands[8];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S500Hz.SetPos((-1)*Bands[8]);
	m_E500Hz.Empty();
	m_E500Hz.Format(_T("%d"), Bands[8]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit710hz20()
{
	UpdateData(true);
	if (CheckData(m_E710Hz))
	{
		Bands[9] = _wtof(m_E710Hz);
		if (Bands[9] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[9] = -25;
		}
		if (Bands[9] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[9] = 25;
		}
		BFX_Peakeq[9].fGain = Bands[9];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S710Hz.SetPos((-1)*Bands[9]);
	m_E710Hz.Empty();
	m_E710Hz.Format(_T("%d"), Bands[9]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit1khz20()
{
	UpdateData(true);
	if (CheckData(m_E1KHz))
	{
		Bands[10] = _wtof(m_E1KHz);
		if (Bands[10] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[10] = -25;
		}
		if (Bands[10] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[10] = 25;
		}
		BFX_Peakeq[10].fGain = Bands[10];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S1KHz.SetPos((-1)*Bands[10]);
	m_E1KHz.Empty();
	m_E1KHz.Format(_T("%d"), Bands[10]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit1p4khz20()
{
	UpdateData(true);
	if (CheckData(m_E1P4KHz))
	{
		Bands[11] = _wtof(m_E1P4KHz);
		if (Bands[11] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[11] = -25;
		}
		if (Bands[11] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[11] = 25;
		}
		BFX_Peakeq[11].fGain = Bands[11];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S1P4KHz.SetPos((-1)*Bands[11]);
	m_E1P4KHz.Empty();
	m_E1P4KHz.Format(_T("%d"), Bands[11]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit2khz20()
{
	UpdateData(true);
	if (CheckData(m_E2KHz))
	{
		Bands[12] = _wtof(m_E2KHz);
		if (Bands[12] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[12] = -25;
		}
		if (Bands[12] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[12] = 25;
		}
		BFX_Peakeq[12].fGain = Bands[12];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S2KHz.SetPos((-1)*Bands[12]);
	m_E2KHz.Empty();
	m_E2KHz.Format(_T("%d"), Bands[12]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit2p8khz20()
{
	UpdateData(true);
	if (CheckData(m_E2P8KHz))
	{
		Bands[13] = _wtof(m_E2P8KHz);
		if (Bands[13] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[13] = -25;
		}
		if (Bands[13] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[13] = 25;
		}
		BFX_Peakeq[13].fGain = Bands[13];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S2P8KHz.SetPos((-1)*Bands[13]);
	m_E2P8KHz.Empty();
	m_E2P8KHz.Format(_T("%d"), Bands[13]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit4khz20()
{
	UpdateData(true);
	if (CheckData(m_E4KHz))
	{
		Bands[14] = _wtof(m_E4KHz);
		if (Bands[14] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[14] = -25;
		}
		if (Bands[14] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[14] = 25;
		}
		BFX_Peakeq[14].fGain = Bands[14];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S4KHz.SetPos((-1)*Bands[14]);
	m_E4KHz.Empty();
	m_E4KHz.Format(_T("%d"), Bands[14]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit5p6khz20()
{
	UpdateData(true);
	if (CheckData(m_E5P6KHz))
	{
		Bands[15] = _wtof(m_E5P6KHz);
		if (Bands[15] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[15] = -25;
		}
		if (Bands[15] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[15] = 25;
		}
		BFX_Peakeq[15].fGain = Bands[15];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S5P6KHz.SetPos((-1)*Bands[15]);
	m_E5P6KHz.Empty();
	m_E5P6KHz.Format(_T("%d"), Bands[15]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit8khz20()
{
	UpdateData(true);
	if (CheckData(m_E8KHz))
	{
		Bands[16] = _wtof(m_E8KHz);
		if (Bands[16] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[16] = -25;
		}
		if (Bands[16] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[16] = 25;
		}
		BFX_Peakeq[16].fGain = Bands[16];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S8KHz.SetPos((-1)*Bands[16]);
	m_E8KHz.Empty();
	m_E8KHz.Format(_T("%d"), Bands[16]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit11p3khz20()
{
	UpdateData(true);
	if (CheckData(m_E11P3KHz))
	{
		Bands[17] = _wtof(m_E11P3KHz);
		if (Bands[17] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[17] = -25;
		}
		if (Bands[17] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[17] = 25;
		}
		BFX_Peakeq[17].fGain = Bands[17];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S11P3KHz.SetPos((-1)*Bands[17]);
	m_E11P3KHz.Empty();
	m_E11P3KHz.Format(_T("%d"), Bands[17]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit16khz20()
{
	UpdateData(true);
	if (CheckData(m_E16KHz))
	{
		Bands[18] = _wtof(m_E16KHz);
		if (Bands[18] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[18] = -25;
		}
		if (Bands[18] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[18] = 25;
		}
		BFX_Peakeq[18].fGain = Bands[18];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S16KHz.SetPos((-1)*Bands[18]);
	m_E16KHz.Empty();
	m_E16KHz.Format(_T("%d"), Bands[18]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnEnChangeEdit22khz20()
{
	UpdateData(true);
	if (CheckData(m_E22KHz))
	{
		Bands[19] = _wtof(m_E22KHz);
		if (Bands[19] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[19] = -25;
		}
		if (Bands[19] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[19] = 25;
		}
		BFX_Peakeq[19].fGain = Bands[19];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S22KHz.SetPos((-1)*Bands[19]);
	m_E22KHz.Empty();
	m_E22KHz.Format(_T("%d"), Bands[19]);
	UpdateData(false);
}


void CEqualizer20Dlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		for (int i = 0; i < 20; i++)
			BFX_Peakeq[i].fGain = Bands[i];

		DefaultCore.TestOn(_T("peakeq"), 20);
		DefaultCore.TestUpdate(BFX_Peakeq);

		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CEqualizer20Dlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(BFX_Peakeq, 20);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CEqualizer20Dlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CEqualizer20Dlg::OnClose()
{
	OnBnClickedCancel();
}
