// Equalizer30Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "Equalizer30Dlg.h"
#include "afxdialogex.h"


// CEqualizer30Dlg dialog

IMPLEMENT_DYNAMIC(CEqualizer30Dlg, CDialogEx)

CEqualizer30Dlg::CEqualizer30Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEqualizer30Dlg::IDD, pParent)
	, m_E31Hz(_T("0"))
	, m_E40Hz(_T("0"))
	, m_E50Hz(_T("0"))
	, m_E63Hz(_T("0"))
	, m_E80Hz(_T("0"))
	, m_E100Hz(_T("0"))
	, m_E125Hz(_T("0"))
	, m_E160Hz(_T("0"))
	, m_E200Hz(_T("0"))
	, m_E250Hz(_T("0"))
	, m_E315Hz(_T("0"))
	, m_E400Hz(_T("0"))
	, m_E500Hz(_T("0"))
	, m_E630Hz(_T("0"))
	, m_E800Hz(_T("0"))
	, m_E1KHz(_T("0"))
	, m_E1P25KHz(_T("0"))
	, m_E1P6KHz(_T("0"))
	, m_E2KHz(_T("0"))
	, m_E2P5KHz(_T("0"))
	, m_E3P2KHz(_T("0"))
	, m_E4KHz(_T("0"))
	, m_E5KHz(_T("0"))
	, m_E6P3KHz(_T("0"))
	, m_E8KHz(_T("0"))
	, m_E10KHz(_T("0"))
	, m_E12P5KHz(_T("0"))
	, m_E16KHz(_T("0"))
	, m_E20KHz(_T("0"))
	, m_E25KHz(_T("0"))
{

}

CEqualizer30Dlg::~CEqualizer30Dlg()
{
}

void CEqualizer30Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//Sliders
	DDX_Control(pDX, ID_SLIDER_31HZ30, m_S31Hz);
	DDX_Control(pDX, ID_SLIDER_40HZ30, m_S40Hz);
	DDX_Control(pDX, ID_SLIDER_50HZ30, m_S50Hz);
	DDX_Control(pDX, ID_SLIDER_63HZ30, m_S63Hz);
	DDX_Control(pDX, ID_SLIDER_80HZ30, m_S80Hz);
	DDX_Control(pDX, ID_SLIDER_100HZ30, m_S100Hz);
	DDX_Control(pDX, ID_SLIDER_125HZ30, m_S125Hz);
	DDX_Control(pDX, ID_SLIDER_160HZ30, m_S160Hz);
	DDX_Control(pDX, ID_SLIDER_200HZ30, m_S200Hz);
	DDX_Control(pDX, ID_SLIDER_250HZ30, m_S250Hz);
	DDX_Control(pDX, ID_SLIDER_315HZ30, m_S315Hz);
	DDX_Control(pDX, ID_SLIDER_400HZ30, m_S400Hz);
	DDX_Control(pDX, ID_SLIDER_500HZ30, m_S500Hz);
	DDX_Control(pDX, ID_SLIDER_630HZ30, m_S630Hz);
	DDX_Control(pDX, ID_SLIDER_800HZ30, m_S800Hz);
	DDX_Control(pDX, ID_SLIDER_1KHZ30, m_S1KHz);
	DDX_Control(pDX, ID_SLIDER_1P25KHZ30, m_S1P25KHz);
	DDX_Control(pDX, ID_SLIDER_1P6KHZ30, m_S1P6KHz);
	DDX_Control(pDX, ID_SLIDER_2KHZ30, m_S2KHz);
	DDX_Control(pDX, ID_SLIDER_2P5KHZ30, m_S2P5KHz);
	DDX_Control(pDX, ID_SLIDER_3P2KHZ30, m_S3P2KHz);
	DDX_Control(pDX, ID_SLIDER_4KHZ30, m_S4KHz);
	DDX_Control(pDX, ID_SLIDER_5KHZ30, m_S5KHz);
	DDX_Control(pDX, ID_SLIDER_6P3KHZ30, m_S6P3KHz);
	DDX_Control(pDX, ID_SLIDER_8KHZ30, m_S8KHz);
	DDX_Control(pDX, ID_SLIDER_10KHZ30, m_S10KHz);
	DDX_Control(pDX, ID_SLIDER_12P5KHZ30, m_S12P5KHz);
	DDX_Control(pDX, ID_SLIDER_16KHZ30, m_S16KHz);
	DDX_Control(pDX, ID_SLIDER_20KHZ30, m_S20KHz);
	DDX_Control(pDX, ID_SLIDER_25KHZ30, m_S25KHz);
	//Edits
	DDX_Text(pDX, ID_EDIT_31HZ30, m_E31Hz);
	DDX_Text(pDX, ID_EDIT_40HZ30, m_E40Hz);
	DDX_Text(pDX, ID_EDIT_50HZ30, m_E50Hz);
	DDX_Text(pDX, ID_EDIT_63HZ30, m_E63Hz);
	DDX_Text(pDX, ID_EDIT_80HZ30, m_E80Hz);
	DDX_Text(pDX, ID_EDIT_100HZ30, m_E100Hz);
	DDX_Text(pDX, ID_EDIT_125HZ30, m_E125Hz);
	DDX_Text(pDX, ID_EDIT_160HZ30, m_E160Hz);
	DDX_Text(pDX, ID_EDIT_200HZ30, m_E200Hz);
	DDX_Text(pDX, ID_EDIT_250HZ30, m_E250Hz);
	DDX_Text(pDX, ID_EDIT_315HZ30, m_E315Hz);
	DDX_Text(pDX, ID_EDIT_400HZ30, m_E400Hz);
	DDX_Text(pDX, ID_EDIT_500HZ30, m_E500Hz);
	DDX_Text(pDX, ID_EDIT_630HZ30, m_E630Hz);
	DDX_Text(pDX, ID_EDIT_800HZ30, m_E800Hz);
	DDX_Text(pDX, ID_EDIT_1KHZ30, m_E1KHz);
	DDX_Text(pDX, ID_EDIT_1P25KHZ30, m_E1P25KHz);
	DDX_Text(pDX, ID_EDIT_1P6KHZ30, m_E1P6KHz);
	DDX_Text(pDX, ID_EDIT_2KHZ30, m_E2KHz);
	DDX_Text(pDX, ID_EDIT_2P5KHZ30, m_E2P5KHz);
	DDX_Text(pDX, ID_EDIT_3P2KHZ30, m_E3P2KHz);
	DDX_Text(pDX, ID_EDIT_4KHZ30, m_E4KHz);
	DDX_Text(pDX, ID_EDIT_5KHZ30, m_E5KHz);
	DDX_Text(pDX, ID_EDIT_6P3KHZ30, m_E6P3KHz);
	DDX_Text(pDX, ID_EDIT_8KHZ30, m_E8KHz);
	DDX_Text(pDX, ID_EDIT_10KHZ30, m_E10KHz);
	DDX_Text(pDX, ID_EDIT_12P5KHZ30, m_E12P5KHz);
	DDX_Text(pDX, ID_EDIT_16KHZ30, m_E16KHz);
	DDX_Text(pDX, ID_EDIT_20KHZ30, m_E20KHz);
	DDX_Text(pDX, ID_EDIT_25KHZ30, m_E25KHz);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CEqualizer30Dlg, CDialogEx)
	ON_WM_VSCROLL()
	ON_EN_CHANGE(ID_EDIT_31HZ30, &CEqualizer30Dlg::OnEnChangeEdit31hz30)
	ON_EN_CHANGE(ID_EDIT_40HZ30, &CEqualizer30Dlg::OnEnChangeEdit40hz30)
	ON_EN_CHANGE(ID_EDIT_50HZ30, &CEqualizer30Dlg::OnEnChangeEdit50hz30)
	ON_EN_CHANGE(ID_EDIT_63HZ30, &CEqualizer30Dlg::OnEnChangeEdit63hz30)
	ON_EN_CHANGE(ID_EDIT_80HZ30, &CEqualizer30Dlg::OnEnChangeEdit80hz30)
	ON_EN_CHANGE(ID_EDIT_100HZ30, &CEqualizer30Dlg::OnEnChangeEdit100hz30)
	ON_EN_CHANGE(ID_EDIT_125HZ30, &CEqualizer30Dlg::OnEnChangeEdit125hz30)
	ON_EN_CHANGE(ID_EDIT_160HZ30, &CEqualizer30Dlg::OnEnChangeEdit160hz30)
	ON_EN_CHANGE(ID_EDIT_200HZ30, &CEqualizer30Dlg::OnEnChangeEdit200hz30)
	ON_EN_CHANGE(ID_EDIT_250HZ30, &CEqualizer30Dlg::OnEnChangeEdit250hz30)
	ON_EN_CHANGE(ID_EDIT_315HZ30, &CEqualizer30Dlg::OnEnChangeEdit315hz30)
	ON_EN_CHANGE(ID_EDIT_400HZ30, &CEqualizer30Dlg::OnEnChangeEdit400hz30)
	ON_EN_CHANGE(ID_EDIT_500HZ30, &CEqualizer30Dlg::OnEnChangeEdit500hz30)
	ON_EN_CHANGE(ID_EDIT_630HZ30, &CEqualizer30Dlg::OnEnChangeEdit630hz30)
	ON_EN_CHANGE(ID_EDIT_800HZ30, &CEqualizer30Dlg::OnEnChangeEdit800hz30)
	ON_EN_CHANGE(ID_EDIT_1KHZ30, &CEqualizer30Dlg::OnEnChangeEdit1khz30)
	ON_EN_CHANGE(ID_EDIT_1P25KHZ30, &CEqualizer30Dlg::OnEnChangeEdit1p25khz30)
	ON_EN_CHANGE(ID_EDIT_1P6KHZ30, &CEqualizer30Dlg::OnEnChangeEdit1p6khz30)
	ON_EN_CHANGE(ID_EDIT_2KHZ30, &CEqualizer30Dlg::OnEnChangeEdit2khz30)
	ON_EN_CHANGE(ID_EDIT_2P5KHZ30, &CEqualizer30Dlg::OnEnChangeEdit2p5khz30)
	ON_EN_CHANGE(ID_EDIT_3P2KHZ30, &CEqualizer30Dlg::OnEnChangeEdit3p2khz30)
	ON_EN_CHANGE(ID_EDIT_4KHZ30, &CEqualizer30Dlg::OnEnChangeEdit4khz30)
	ON_EN_CHANGE(ID_EDIT_5KHZ30, &CEqualizer30Dlg::OnEnChangeEdit5khz30)
	ON_EN_CHANGE(ID_EDIT_6P3KHZ30, &CEqualizer30Dlg::OnEnChangeEdit6p3khz30)
	ON_EN_CHANGE(ID_EDIT_8KHZ30, &CEqualizer30Dlg::OnEnChangeEdit8khz30)
	ON_EN_CHANGE(ID_EDIT_10KHZ30, &CEqualizer30Dlg::OnEnChangeEdit10khz30)
	ON_EN_CHANGE(ID_EDIT_12P5KHZ30, &CEqualizer30Dlg::OnEnChangeEdit12p5khz30)
	ON_EN_CHANGE(ID_EDIT_16KHZ30, &CEqualizer30Dlg::OnEnChangeEdit16khz30)
	ON_EN_CHANGE(ID_EDIT_20KHZ30, &CEqualizer30Dlg::OnEnChangeEdit20khz30)
	ON_EN_CHANGE(ID_EDIT_25KHZ30, &CEqualizer30Dlg::OnEnChangeEdit25khz30)
	ON_BN_CLICKED(ID_BTESTONOFF, &CEqualizer30Dlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CEqualizer30Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEqualizer30Dlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CEqualizer30Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//31
	m_S31Hz.SetRange(-25, 25, TRUE);	m_S31Hz.SetPos(0);
	m_S31Hz.SetTic(-20); m_S31Hz.SetTic(20); m_S31Hz.SetTic(0);
	m_S31Hz.SetTic(-10); m_S31Hz.SetTic(10);
	//40
	m_S40Hz.SetRange(-25, 25, TRUE);	m_S40Hz.SetPos(0);
	m_S40Hz.SetTic(-20); m_S40Hz.SetTic(20); m_S40Hz.SetTic(0);
	m_S40Hz.SetTic(-10); m_S40Hz.SetTic(10);
	//50
	m_S50Hz.SetRange(-25, 25, TRUE);	m_S50Hz.SetPos(0);
	m_S50Hz.SetTic(-20); m_S50Hz.SetTic(20); m_S50Hz.SetTic(0);
	m_S50Hz.SetTic(-10); m_S50Hz.SetTic(10);
	//63
	m_S63Hz.SetRange(-25, 25, TRUE);	m_S63Hz.SetPos(0);
	m_S63Hz.SetTic(-20); m_S63Hz.SetTic(20); m_S63Hz.SetTic(0);
	m_S63Hz.SetTic(-10); m_S63Hz.SetTic(10);
	//80
	m_S80Hz.SetRange(-25, 25, TRUE);	m_S80Hz.SetPos(0);
	m_S80Hz.SetTic(-20); m_S80Hz.SetTic(20); m_S80Hz.SetTic(0);
	m_S80Hz.SetTic(-10); m_S80Hz.SetTic(10);
	//100
	m_S100Hz.SetRange(-25, 25, TRUE);	m_S100Hz.SetPos(0);
	m_S100Hz.SetTic(-20); m_S100Hz.SetTic(20); m_S100Hz.SetTic(0);
	m_S100Hz.SetTic(-10); m_S100Hz.SetTic(10);
	//125
	m_S125Hz.SetRange(-25, 25, TRUE);	m_S125Hz.SetPos(0);
	m_S125Hz.SetTic(-20); m_S125Hz.SetTic(20); m_S125Hz.SetTic(0);
	m_S125Hz.SetTic(-10); m_S125Hz.SetTic(10);
	//160
	m_S160Hz.SetRange(-25, 25, TRUE);	m_S160Hz.SetPos(0);
	m_S160Hz.SetTic(-20); m_S160Hz.SetTic(20); m_S160Hz.SetTic(0);
	m_S160Hz.SetTic(-10); m_S160Hz.SetTic(10);
	//200
	m_S200Hz.SetRange(-25, 25, TRUE);	m_S200Hz.SetPos(0);
	m_S200Hz.SetTic(-20); m_S200Hz.SetTic(20); m_S200Hz.SetTic(0);
	m_S200Hz.SetTic(-10); m_S200Hz.SetTic(10);
	//250
	m_S250Hz.SetRange(-25, 25, TRUE);	m_S250Hz.SetPos(0);
	m_S250Hz.SetTic(-20); m_S250Hz.SetTic(20); m_S250Hz.SetTic(0);
	m_S250Hz.SetTic(-10); m_S250Hz.SetTic(10);
	//315
	m_S315Hz.SetRange(-25, 25, TRUE);	m_S315Hz.SetPos(0);
	m_S315Hz.SetTic(-20); m_S315Hz.SetTic(20); m_S315Hz.SetTic(0);
	m_S315Hz.SetTic(-10); m_S315Hz.SetTic(10);
	//400
	m_S400Hz.SetRange(-25, 25, TRUE);	m_S400Hz.SetPos(0);
	m_S400Hz.SetTic(-20); m_S400Hz.SetTic(20); m_S400Hz.SetTic(0);
	m_S400Hz.SetTic(-10); m_S400Hz.SetTic(10);
	//500
	m_S500Hz.SetRange(-25, 25, TRUE);	m_S500Hz.SetPos(0);
	m_S500Hz.SetTic(-20); m_S500Hz.SetTic(20); m_S500Hz.SetTic(0);
	m_S500Hz.SetTic(-10); m_S500Hz.SetTic(10);
	//630
	m_S630Hz.SetRange(-25, 25, TRUE);	m_S630Hz.SetPos(0);
	m_S630Hz.SetTic(-20); m_S630Hz.SetTic(20); m_S630Hz.SetTic(0);
	m_S630Hz.SetTic(-10); m_S630Hz.SetTic(10);
	//800
	m_S800Hz.SetRange(-25, 25, TRUE);	m_S800Hz.SetPos(0);
	m_S800Hz.SetTic(-20); m_S800Hz.SetTic(20); m_S800Hz.SetTic(0);
	m_S800Hz.SetTic(-10); m_S800Hz.SetTic(10);
	//1K
	m_S1KHz.SetRange(-25, 25, TRUE);	m_S1KHz.SetPos(0);
	m_S1KHz.SetTic(-20); m_S1KHz.SetTic(20); m_S1KHz.SetTic(0);
	m_S1KHz.SetTic(-10); m_S1KHz.SetTic(10);
	//1.25K
	m_S1P25KHz.SetRange(-25, 25, TRUE);	m_S1P25KHz.SetPos(0);
	m_S1P25KHz.SetTic(-20); m_S1P25KHz.SetTic(20); m_S1P25KHz.SetTic(0);
	m_S1P25KHz.SetTic(-10); m_S1P25KHz.SetTic(10);
	//1.6K
	m_S1P6KHz.SetRange(-25, 25, TRUE);	m_S1P6KHz.SetPos(0);
	m_S1P6KHz.SetTic(-20); m_S1P6KHz.SetTic(20); m_S1P6KHz.SetTic(0);
	m_S1P6KHz.SetTic(-10); m_S1P6KHz.SetTic(10);
	//2K
	m_S2KHz.SetRange(-25, 25, TRUE);	m_S2KHz.SetPos(0);
	m_S2KHz.SetTic(-20); m_S2KHz.SetTic(20); m_S2KHz.SetTic(0);
	m_S2KHz.SetTic(-10); m_S2KHz.SetTic(10);
	//2.5K
	m_S2P5KHz.SetRange(-25, 25, TRUE);	m_S2P5KHz.SetPos(0);
	m_S2P5KHz.SetTic(-20); m_S2P5KHz.SetTic(20); m_S2P5KHz.SetTic(0);
	m_S2P5KHz.SetTic(-10); m_S2P5KHz.SetTic(10);
	//3.2K
	m_S3P2KHz.SetRange(-25, 25, TRUE);	m_S3P2KHz.SetPos(0);
	m_S3P2KHz.SetTic(-20); m_S3P2KHz.SetTic(20); m_S3P2KHz.SetTic(0);
	m_S3P2KHz.SetTic(-10); m_S3P2KHz.SetTic(10);
	//4K
	m_S4KHz.SetRange(-25, 25, TRUE);	m_S4KHz.SetPos(0);
	m_S4KHz.SetTic(-20); m_S4KHz.SetTic(20); m_S4KHz.SetTic(0);
	m_S4KHz.SetTic(-10); m_S4KHz.SetTic(10);
	//5K
	m_S5KHz.SetRange(-25, 25, TRUE);	m_S5KHz.SetPos(0);
	m_S5KHz.SetTic(-20); m_S5KHz.SetTic(20); m_S5KHz.SetTic(0);
	m_S5KHz.SetTic(-10); m_S5KHz.SetTic(10);
	//6.3K
	m_S6P3KHz.SetRange(-25, 25, TRUE);	m_S6P3KHz.SetPos(0);
	m_S6P3KHz.SetTic(-20); m_S6P3KHz.SetTic(20); m_S6P3KHz.SetTic(0);
	m_S6P3KHz.SetTic(-10); m_S6P3KHz.SetTic(10);
	//8K
	m_S8KHz.SetRange(-25, 25, TRUE);	m_S8KHz.SetPos(0);
	m_S8KHz.SetTic(-20); m_S8KHz.SetTic(20); m_S8KHz.SetTic(0);
	m_S8KHz.SetTic(-10); m_S8KHz.SetTic(10);
	//10K
	m_S10KHz.SetRange(-25, 25, TRUE);	m_S10KHz.SetPos(0);
	m_S10KHz.SetTic(-20); m_S10KHz.SetTic(20); m_S10KHz.SetTic(0);
	m_S10KHz.SetTic(-10); m_S10KHz.SetTic(10);
	//12.5K
	m_S12P5KHz.SetRange(-25, 25, TRUE);	m_S12P5KHz.SetPos(0);
	m_S12P5KHz.SetTic(-20); m_S12P5KHz.SetTic(20); m_S12P5KHz.SetTic(0);
	m_S12P5KHz.SetTic(-10); m_S12P5KHz.SetTic(10);
	//16K
	m_S16KHz.SetRange(-25, 25, TRUE);	m_S16KHz.SetPos(0);
	m_S16KHz.SetTic(-20); m_S16KHz.SetTic(20); m_S16KHz.SetTic(0);
	m_S16KHz.SetTic(-10); m_S16KHz.SetTic(10);
	//20K
	m_S20KHz.SetRange(-25, 25, TRUE);	m_S20KHz.SetPos(0);
	m_S20KHz.SetTic(-20); m_S20KHz.SetTic(20); m_S20KHz.SetTic(0);
	m_S20KHz.SetTic(-10); m_S20KHz.SetTic(10);
	//25K
	m_S25KHz.SetRange(-25, 25, TRUE);	m_S25KHz.SetPos(0);
	m_S25KHz.SetTic(-20); m_S25KHz.SetTic(20); m_S25KHz.SetTic(0);
	m_S25KHz.SetTic(-10); m_S25KHz.SetTic(10);

	BFX_Peakeq[0].fCenter = 31;			BFX_Peakeq[15].fCenter = 1000;
	BFX_Peakeq[1].fCenter = 40;			BFX_Peakeq[16].fCenter = 1250;
	BFX_Peakeq[2].fCenter = 50;			BFX_Peakeq[17].fCenter = 1600;
	BFX_Peakeq[3].fCenter = 63;			BFX_Peakeq[18].fCenter = 2000;
	BFX_Peakeq[4].fCenter = 80;			BFX_Peakeq[19].fCenter = 2500;
	BFX_Peakeq[5].fCenter = 100;		BFX_Peakeq[20].fCenter = 3200;
	BFX_Peakeq[6].fCenter = 125;		BFX_Peakeq[21].fCenter = 4000;
	BFX_Peakeq[7].fCenter = 160;		BFX_Peakeq[22].fCenter = 5000;
	BFX_Peakeq[8].fCenter = 200;		BFX_Peakeq[23].fCenter = 6300;
	BFX_Peakeq[9].fCenter = 250;		BFX_Peakeq[24].fCenter = 8000;
	BFX_Peakeq[10].fCenter = 315;		BFX_Peakeq[25].fCenter = 10000;
	BFX_Peakeq[11].fCenter = 400;		BFX_Peakeq[26].fCenter = 12500;
	BFX_Peakeq[12].fCenter = 500;		BFX_Peakeq[27].fCenter = 16000;
	BFX_Peakeq[13].fCenter = 630;		BFX_Peakeq[28].fCenter = 20000;
	BFX_Peakeq[14].fCenter = 800;		BFX_Peakeq[29].fCenter = 25000;
	for (int i = 0; i < 30; i++)
	{
		BFX_Peakeq[i].fGain = Bands[i] = 0;
		BFX_Peakeq[i].lBand = 0;
		BFX_Peakeq[i].fBandwidth = 2.5;
		BFX_Peakeq[i].fQ = 0.0;
		BFX_Peakeq[i].lChannel = BASS_BFX_CHANALL;
	}
	DefaultCore.TestOn(_T("peakeq"), 30);
	DefaultCore.TestUpdate(BFX_Peakeq);

	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
	Test = true;

	return TRUE;
}

// CEqualizer30Dlg message handlers

BOOL CEqualizer30Dlg::CheckData(CString Data)
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

void CEqualizer30Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//0
	if (pScrollBar == (CScrollBar *)&m_S31Hz)
	{
		Bands[0] = (-1)*m_S31Hz.GetPos();
		BFX_Peakeq[0].fGain = Bands[0];
		m_E31Hz.Format(_T("%d"), Bands[0]);
	}
	//1
	if (pScrollBar == (CScrollBar *)&m_S40Hz)
	{
		Bands[1] = (-1)*m_S40Hz.GetPos();
		BFX_Peakeq[1].fGain = Bands[1];
		m_E40Hz.Format(_T("%d"), Bands[1]);
	}
	//2
	if (pScrollBar == (CScrollBar *)&m_S50Hz)
	{
		Bands[2] = (-1)*m_S50Hz.GetPos();
		BFX_Peakeq[2].fGain = Bands[2];
		m_E50Hz.Format(_T("%d"), Bands[2]);
	}
	//3
	if (pScrollBar == (CScrollBar *)&m_S63Hz)
	{
		Bands[3] = (-1)*m_S63Hz.GetPos();
		BFX_Peakeq[3].fGain = Bands[3];
		m_E63Hz.Format(_T("%d"), Bands[3]);
	}
	//4
	if (pScrollBar == (CScrollBar *)&m_S80Hz)
	{
		Bands[4] = (-1)*m_S80Hz.GetPos();
		BFX_Peakeq[4].fGain = Bands[4];
		m_E80Hz.Format(_T("%d"), Bands[4]);
	}
	//5
	if (pScrollBar == (CScrollBar *)&m_S100Hz)
	{
		Bands[5] = (-1)*m_S100Hz.GetPos();
		BFX_Peakeq[5].fGain = Bands[5];
		m_E100Hz.Format(_T("%d"), Bands[5]);
	}
	//6
	if (pScrollBar == (CScrollBar *)&m_S125Hz)
	{
		Bands[6] = (-1)*m_S125Hz.GetPos();
		BFX_Peakeq[6].fGain = Bands[6];
		m_E125Hz.Format(_T("%d"), Bands[6]);
	}
	//7
	if (pScrollBar == (CScrollBar *)&m_S160Hz)
	{
		Bands[7] = (-1)*m_S160Hz.GetPos();
		BFX_Peakeq[7].fGain = Bands[7];
		m_E160Hz.Format(_T("%d"), Bands[7]);
	}
	//8
	if (pScrollBar == (CScrollBar *)&m_S200Hz)
	{
		Bands[8] = (-1)*m_S200Hz.GetPos();
		BFX_Peakeq[8].fGain = Bands[8];
		m_E200Hz.Format(_T("%d"), Bands[8]);
	}
	//9
	if (pScrollBar == (CScrollBar *)&m_S250Hz)
	{
		Bands[9] = (-1)*m_S250Hz.GetPos();
		BFX_Peakeq[9].fGain = Bands[9];
		m_E250Hz.Format(_T("%d"), Bands[9]);
	}
	//10
	if (pScrollBar == (CScrollBar *)&m_S315Hz)
	{
		Bands[10] = (-1)*m_S315Hz.GetPos();
		BFX_Peakeq[10].fGain = Bands[10];
		m_E315Hz.Format(_T("%d"), Bands[10]);
	}
	//11
	if (pScrollBar == (CScrollBar *)&m_S400Hz)
	{
		Bands[11] = (-1)*m_S400Hz.GetPos();
		BFX_Peakeq[11].fGain = Bands[11];
		m_E400Hz.Format(_T("%d"), Bands[11]);
	}
	//12
	if (pScrollBar == (CScrollBar *)&m_S500Hz)
	{
		Bands[12] = (-1)*m_S500Hz.GetPos();
		BFX_Peakeq[12].fGain = Bands[12];
		m_E500Hz.Format(_T("%d"), Bands[12]);
	}
	//13
	if (pScrollBar == (CScrollBar *)&m_S630Hz)
	{
		Bands[13] = (-1)*m_S630Hz.GetPos();
		BFX_Peakeq[13].fGain = Bands[13];
		m_E630Hz.Format(_T("%d"), Bands[13]);
	}
	//14
	if (pScrollBar == (CScrollBar *)&m_S800Hz)
	{
		Bands[14] = (-1)*m_S800Hz.GetPos();
		BFX_Peakeq[14].fGain = Bands[14];
		m_E800Hz.Format(_T("%d"), Bands[14]);
	}
	//15
	if (pScrollBar == (CScrollBar *)&m_S1KHz)
	{
		Bands[15] = (-1)*m_S1KHz.GetPos();
		BFX_Peakeq[15].fGain = Bands[15];
		m_E1KHz.Format(_T("%d"), Bands[15]);
	}
	//16
	if (pScrollBar == (CScrollBar *)&m_S1P25KHz)
	{
		Bands[16] = (-1)*m_S1P25KHz.GetPos();
		BFX_Peakeq[16].fGain = Bands[16];
		m_E1P25KHz.Format(_T("%d"), Bands[16]);
	}
	//17
	if (pScrollBar == (CScrollBar *)&m_S1P6KHz)
	{
		Bands[17] = (-1)*m_S1P6KHz.GetPos();
		BFX_Peakeq[17].fGain = Bands[17];
		m_E1P6KHz.Format(_T("%d"), Bands[17]);
	}
	//18
	if (pScrollBar == (CScrollBar *)&m_S2KHz)
	{
		Bands[18] = (-1)*m_S2KHz.GetPos();
		BFX_Peakeq[18].fGain = Bands[18];
		m_E2KHz.Format(_T("%d"), Bands[18]);
	}
	//19
	if (pScrollBar == (CScrollBar *)&m_S2P5KHz)
	{
		Bands[19] = (-1)*m_S2P5KHz.GetPos();
		BFX_Peakeq[19].fGain = Bands[19];
		m_E2P5KHz.Format(_T("%d"), Bands[19]);
	}
	//20
	if (pScrollBar == (CScrollBar *)&m_S3P2KHz)
	{
		Bands[20] = (-1)*m_S3P2KHz.GetPos();
		BFX_Peakeq[20].fGain = Bands[20];
		m_E3P2KHz.Format(_T("%d"), Bands[20]);
	}
	//21
	if (pScrollBar == (CScrollBar *)&m_S4KHz)
	{
		Bands[21] = (-1)*m_S4KHz.GetPos();
		BFX_Peakeq[21].fGain = Bands[21];
		m_E4KHz.Format(_T("%d"), Bands[21]);
	}
	//22
	if (pScrollBar == (CScrollBar *)&m_S5KHz)
	{
		Bands[22] = (-1)*m_S5KHz.GetPos();
		BFX_Peakeq[22].fGain = Bands[22];
		m_E5KHz.Format(_T("%d"), Bands[22]);
	}
	//23
	if (pScrollBar == (CScrollBar *)&m_S6P3KHz)
	{
		Bands[23] = (-1)*m_S6P3KHz.GetPos();
		BFX_Peakeq[23].fGain = Bands[23];
		m_E6P3KHz.Format(_T("%d"), Bands[23]);
	}
	//24
	if (pScrollBar == (CScrollBar *)&m_S8KHz)
	{
		Bands[24] = (-1)*m_S8KHz.GetPos();
		BFX_Peakeq[24].fGain = Bands[24];
		m_E8KHz.Format(_T("%d"), Bands[24]);
	}
	//25
	if (pScrollBar == (CScrollBar *)&m_S10KHz)
	{
		Bands[25] = (-1)*m_S10KHz.GetPos();
		BFX_Peakeq[25].fGain = Bands[25];
		m_E10KHz.Format(_T("%d"), Bands[25]);
	}
	//26
	if (pScrollBar == (CScrollBar *)&m_S12P5KHz)
	{
		Bands[26] = (-1)*m_S12P5KHz.GetPos();
		BFX_Peakeq[26].fGain = Bands[26];
		m_E12P5KHz.Format(_T("%d"), Bands[26]);
	}
	//27
	if (pScrollBar == (CScrollBar *)&m_S16KHz)
	{
		Bands[27] = (-1)*m_S16KHz.GetPos();
		BFX_Peakeq[27].fGain = Bands[27];
		m_E16KHz.Format(_T("%d"), Bands[27]);
	}
	//28
	if (pScrollBar == (CScrollBar *)&m_S20KHz)
	{
		Bands[28] = (-1)*m_S20KHz.GetPos();
		BFX_Peakeq[28].fGain = Bands[28];
		m_E20KHz.Format(_T("%d"), Bands[28]);
	}
	//29
	if (pScrollBar == (CScrollBar *)&m_S25KHz)
	{
		Bands[29] = (-1)*m_S25KHz.GetPos();
		BFX_Peakeq[29].fGain = Bands[29];
		m_E25KHz.Format(_T("%d"), Bands[29]);
	}
	if (Test)
		DefaultCore.TestUpdate(BFX_Peakeq);
	UpdateData(false);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}



void CEqualizer30Dlg::OnEnChangeEdit31hz30()
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


void CEqualizer30Dlg::OnEnChangeEdit40hz30()
{
	UpdateData(true);
	if (CheckData(m_E40Hz))
	{
		Bands[1] = _wtof(m_E40Hz);
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
	m_S40Hz.SetPos((-1)*Bands[1]);
	m_E40Hz.Empty();
	m_E40Hz.Format(_T("%d"), Bands[1]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit50hz30()
{
	UpdateData(true);
	if (CheckData(m_E50Hz))
	{
		Bands[2] = _wtof(m_E50Hz);
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
	m_S50Hz.SetPos((-1)*Bands[2]);
	m_E50Hz.Empty();
	m_E50Hz.Format(_T("%d"), Bands[2]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit63hz30()
{
	UpdateData(true);
	if (CheckData(m_E63Hz))
	{
		Bands[3] = _wtof(m_E63Hz);
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
	m_S63Hz.SetPos((-1)*Bands[3]);
	m_E63Hz.Empty();
	m_E63Hz.Format(_T("%d"), Bands[3]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit80hz30()
{
	UpdateData(true);
	if (CheckData(m_E80Hz))
	{
		Bands[4] = _wtof(m_E80Hz);
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
	m_S80Hz.SetPos((-1)*Bands[4]);
	m_E80Hz.Empty();
	m_E80Hz.Format(_T("%d"), Bands[4]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit100hz30()
{
	UpdateData(true);
	if (CheckData(m_E100Hz))
	{
		Bands[5] = _wtof(m_E100Hz);
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
	m_S100Hz.SetPos((-1)*Bands[5]);
	m_E100Hz.Empty();
	m_E100Hz.Format(_T("%d"), Bands[5]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit125hz30()
{
	UpdateData(true);
	if (CheckData(m_E125Hz))
	{
		Bands[6] = _wtof(m_E125Hz);
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
	m_S125Hz.SetPos((-1)*Bands[6]);
	m_E125Hz.Empty();
	m_E125Hz.Format(_T("%d"), Bands[6]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit160hz30()
{
	UpdateData(true);
	if (CheckData(m_E160Hz))
	{
		Bands[7] = _wtof(m_E160Hz);
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
	m_S160Hz.SetPos((-1)*Bands[7]);
	m_E160Hz.Empty();
	m_E160Hz.Format(_T("%d"), Bands[7]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit200hz30()
{
	UpdateData(true);
	if (CheckData(m_E200Hz))
	{
		Bands[8] = _wtof(m_E200Hz);
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
	m_S200Hz.SetPos((-1)*Bands[8]);
	m_E200Hz.Empty();
	m_E200Hz.Format(_T("%d"), Bands[8]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit250hz30()
{
	UpdateData(true);
	if (CheckData(m_E250Hz))
	{
		Bands[9] = _wtof(m_E250Hz);
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
	m_S250Hz.SetPos((-1)*Bands[9]);
	m_E250Hz.Empty();
	m_E250Hz.Format(_T("%d"), Bands[9]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit315hz30()
{
	UpdateData(true);
	if (CheckData(m_E315Hz))
	{
		Bands[10] = _wtof(m_E315Hz);
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
	m_S315Hz.SetPos((-1)*Bands[10]);
	m_E315Hz.Empty();
	m_E315Hz.Format(_T("%d"), Bands[10]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit400hz30()
{
	UpdateData(true);
	if (CheckData(m_E400Hz))
	{
		Bands[11] = _wtof(m_E400Hz);
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
	m_S400Hz.SetPos((-1)*Bands[11]);
	m_E400Hz.Empty();
	m_E400Hz.Format(_T("%d"), Bands[11]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit500hz30()
{
	UpdateData(true);
	if (CheckData(m_E500Hz))
	{
		Bands[12] = _wtof(m_E500Hz);
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
	m_S500Hz.SetPos((-1)*Bands[12]);
	m_E500Hz.Empty();
	m_E500Hz.Format(_T("%d"), Bands[12]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit630hz30()
{
	UpdateData(true);
	if (CheckData(m_E630Hz))
	{
		Bands[13] = _wtof(m_E630Hz);
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
	m_S630Hz.SetPos((-1)*Bands[13]);
	m_E630Hz.Empty();
	m_E630Hz.Format(_T("%d"), Bands[13]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit800hz30()
{
	UpdateData(true);
	if (CheckData(m_E800Hz))
	{
		Bands[14] = _wtof(m_E800Hz);
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
	m_S800Hz.SetPos((-1)*Bands[14]);
	m_E800Hz.Empty();
	m_E800Hz.Format(_T("%d"), Bands[14]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit1khz30()
{
	UpdateData(true);
	if (CheckData(m_E1KHz))
	{
		Bands[15] = _wtof(m_E1KHz);
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
	m_S1KHz.SetPos((-1)*Bands[15]);
	m_E1KHz.Empty();
	m_E1KHz.Format(_T("%d"), Bands[15]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit1p25khz30()
{
	UpdateData(true);
	if (CheckData(m_E1P25KHz))
	{
		Bands[16] = _wtof(m_E1P25KHz);
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
	m_S1P25KHz.SetPos((-1)*Bands[16]);
	m_E1P25KHz.Empty();
	m_E1P25KHz.Format(_T("%d"), Bands[16]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit1p6khz30()
{
	UpdateData(true);
	if (CheckData(m_E1P6KHz))
	{
		Bands[17] = _wtof(m_E1P6KHz);
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
	m_S1P6KHz.SetPos((-1)*Bands[17]);
	m_E1P6KHz.Empty();
	m_E1P6KHz.Format(_T("%d"), Bands[17]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit2khz30()
{
	UpdateData(true);
	if (CheckData(m_E2KHz))
	{
		Bands[18] = _wtof(m_E2KHz);
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
	m_S2KHz.SetPos((-1)*Bands[18]);
	m_E2KHz.Empty();
	m_E2KHz.Format(_T("%d"), Bands[18]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit2p5khz30()
{
	UpdateData(true);
	if (CheckData(m_E2P5KHz))
	{
		Bands[19] = _wtof(m_E2P5KHz);
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
	m_S2P5KHz.SetPos((-1)*Bands[19]);
	m_E2P5KHz.Empty();
	m_E2P5KHz.Format(_T("%d"), Bands[19]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit3p2khz30()
{
	UpdateData(true);
	if (CheckData(m_E3P2KHz))
	{
		Bands[20] = _wtof(m_E3P2KHz);
		if (Bands[20] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[20] = -25;
		}
		if (Bands[20] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[20] = 25;
		}
		BFX_Peakeq[20].fGain = Bands[20];	
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S3P2KHz.SetPos((-1)*Bands[20]);
	m_E3P2KHz.Empty();
	m_E3P2KHz.Format(_T("%d"), Bands[20]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit4khz30()
{
	UpdateData(true);
	if (CheckData(m_E4KHz))
	{
		Bands[21] = _wtof(m_E4KHz);
		if (Bands[21] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[21] = -25;
		}
		if (Bands[21] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[21] = 25;
		}
		BFX_Peakeq[21].fGain = Bands[21];	
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S4KHz.SetPos((-1)*Bands[21]);
	m_E4KHz.Empty();
	m_E4KHz.Format(_T("%d"), Bands[21]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit5khz30()
{
	UpdateData(true);
	if (CheckData(m_E5KHz))
	{
		Bands[22] = _wtof(m_E5KHz);
		if (Bands[22] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[22] = -25;
		}
		if (Bands[22] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[22] = 25;
		}
		BFX_Peakeq[22].fGain = Bands[22];	
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S5KHz.SetPos((-1)*Bands[22]);
	m_E5KHz.Empty();
	m_E5KHz.Format(_T("%d"), Bands[22]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit6p3khz30()
{
	UpdateData(true);
	if (CheckData(m_E6P3KHz))
	{
		Bands[23] = _wtof(m_E6P3KHz);
		if (Bands[23] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[23] = -25;
		}
		if (Bands[23] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[23] = 25;
		}
		BFX_Peakeq[23].fGain = Bands[23];	
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S6P3KHz.SetPos((-1)*Bands[23]);
	m_E6P3KHz.Empty();
	m_E6P3KHz.Format(_T("%d"), Bands[23]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit8khz30()
{
	UpdateData(true);
	if (CheckData(m_E8KHz))
	{
		Bands[24] = _wtof(m_E8KHz);
		if (Bands[24] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[24] = -25;
		}
		if (Bands[24] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[24] = 25;
		}
		BFX_Peakeq[24].fGain = Bands[24];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S8KHz.SetPos((-1)*Bands[24]);
	m_E8KHz.Empty();
	m_E8KHz.Format(_T("%d"), Bands[24]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit10khz30()
{
	UpdateData(true);
	if (CheckData(m_E10KHz))
	{
		Bands[25] = _wtof(m_E10KHz);
		if (Bands[25] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[25] = -25;
		}
		if (Bands[25] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[25] = 25;
		}
		BFX_Peakeq[25].fGain = Bands[25];	
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S10KHz.SetPos((-1)*Bands[25]);
	m_E10KHz.Empty();
	m_E10KHz.Format(_T("%d"), Bands[25]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit12p5khz30()
{
	UpdateData(true);
	if (CheckData(m_E12P5KHz))
	{
		Bands[26] = _wtof(m_E12P5KHz);
		if (Bands[26] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[26] = -25;
		}
		if (Bands[26] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[26] = 25;
		}
		BFX_Peakeq[26].fGain = Bands[26];	
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S12P5KHz.SetPos((-1)*Bands[26]);
	m_E12P5KHz.Empty();
	m_E12P5KHz.Format(_T("%d"), Bands[26]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit16khz30()
{
	UpdateData(true);
	if (CheckData(m_E16KHz))
	{
		Bands[27] = _wtof(m_E16KHz);
		if (Bands[27] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[27] = -25;
		}
		if (Bands[27] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[27] = 25;
		}
		BFX_Peakeq[27].fGain = Bands[27];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S16KHz.SetPos((-1)*Bands[27]);
	m_E16KHz.Empty();
	m_E16KHz.Format(_T("%d"), Bands[27]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit20khz30()
{
	UpdateData(true);
	if (CheckData(m_E20KHz))
	{
		Bands[28] = _wtof(m_E20KHz);
		if (Bands[28] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[28] = -25;
		}
		if (Bands[28] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[28] = 25;
		}
		BFX_Peakeq[28].fGain = Bands[28];	
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S20KHz.SetPos((-1)*Bands[28]);
	m_E20KHz.Empty();
	m_E20KHz.Format(_T("%d"), Bands[28]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnEnChangeEdit25khz30()
{
	UpdateData(true);
	if (CheckData(m_E25KHz))
	{
		Bands[29] = _wtof(m_E25KHz);
		if (Bands[29] < -25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[29] = -25;
		}
		if (Bands[29] > 25)
		{
			MessageBox(_T("Must be in the range from -25 to 25."), _T("Error"), MB_ICONERROR);
			Bands[29] = 25;
		}
		BFX_Peakeq[29].fGain = Bands[29];
		if (Test)
			DefaultCore.TestUpdate(BFX_Peakeq);
	}
	m_S25KHz.SetPos((-1)*Bands[29]);
	m_E25KHz.Empty();
	m_E25KHz.Format(_T("%d"), Bands[29]);
	UpdateData(false);
}


void CEqualizer30Dlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		for (int i = 0; i < 30; i++)
			BFX_Peakeq[i].fGain = Bands[i];

		DefaultCore.TestOn(_T("peakeq"), 30);
		DefaultCore.TestUpdate(BFX_Peakeq);

		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CEqualizer30Dlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(BFX_Peakeq, 30);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CEqualizer30Dlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CEqualizer30Dlg::OnClose()
{
	OnBnClickedCancel();
}
