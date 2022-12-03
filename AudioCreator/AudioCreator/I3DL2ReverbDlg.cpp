// I3DL2ReverbDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "I3DL2ReverbDlg.h"
#include "afxdialogex.h"


// CI3DL2ReverbDlg dialog

IMPLEMENT_DYNAMIC(CI3DL2ReverbDlg, CDialogEx)

CI3DL2ReverbDlg::CI3DL2ReverbDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CI3DL2ReverbDlg::IDD, pParent)
	, m_ERolloff(_T("0.00"))
	, m_EDecayTime(_T("1.49"))
	, m_EDecayHFRatio(_T("0.83"))
	, m_EReflectionsDelay(_T("0.007"))
	, m_EReverbDelay(_T("0.011"))
	, m_EDiffusion(_T("100.00"))
	, m_EDensity(_T("100.00"))
	, m_EHFReference(_T("5000.00"))
	, m_ERoom(_T("-1000"))
	, m_ERoomHF(_T("100"))
	, m_EReverb(_T("200"))
	, m_EReflections(_T("-2602"))
{

}

CI3DL2ReverbDlg::~CI3DL2ReverbDlg()
{
}

void CI3DL2ReverbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_SLIDER_ROOM, m_SRoom);
	DDX_Control(pDX, ID_SLIDER_ROOMHF, m_SRoomHF);
	DDX_Control(pDX, ID_SLIDER_ROLLOFF, m_SRolloff);
	DDX_Control(pDX, ID_SLIDER_DECAYTIME, m_SDecayTime);
	DDX_Control(pDX, ID_SLIDER_DECAYHFRATIO, m_SDecayHFRatio);
	DDX_Control(pDX, ID_SLIDER_REFLECTIONS, m_SReflections);
	DDX_Control(pDX, ID_SLIDER_REFLECTIONSDELAY, m_SReflectionsDelay);
	DDX_Control(pDX, ID_SLIDER_REVERB, m_SReverb);
	DDX_Control(pDX, ID_SLIDER_REVERBDELAY, m_SReverbDelay);
	DDX_Control(pDX, ID_SLIDER_DIFFUSION, m_SDiffusion);
	DDX_Control(pDX, ID_SLIDER_DENSITY, m_SDensity);
	DDX_Control(pDX, ID_SLIDER_HFREFERENCE, m_SHFReference);
	DDX_Text(pDX, IDC_EDIT_ROLLOFF, m_ERolloff);
	DDX_Text(pDX, IDC_EDIT_DECAYTIME, m_EDecayTime);
	DDX_Text(pDX, IDC_EDIT_DECAYHFRATIO, m_EDecayHFRatio);
	DDX_Text(pDX, IDC_EDIT_REFLECTIONSDELAY, m_EReflectionsDelay);
	DDX_Text(pDX, IDC_EDIT_REVERBDELAY, m_EReverbDelay);
	DDX_Text(pDX, IDC_EDIT_DIFFUSION, m_EDiffusion);
	DDX_Text(pDX, IDC_EDIT_DENSITY, m_EDensity);
	DDX_Text(pDX, IDC_EDIT_HFREFERENCE, m_EHFReference);
	DDX_Text(pDX, IDC_EDIT_ROOM, m_ERoom);
	DDX_Text(pDX, IDC_EDIT_ROOMHF, m_ERoomHF);
	DDX_Text(pDX, IDC_EDIT_REVERB, m_EReverb);
	DDX_Text(pDX, IDC_EDIT_REFLECTIONS, m_EReflections);
	DDX_Control(pDX, ID_BTESTONOFF, m_BTestOnOff);
}


BEGIN_MESSAGE_MAP(CI3DL2ReverbDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_ROOM, &CI3DL2ReverbDlg::OnEnChangeEditRoom)
	ON_EN_CHANGE(IDC_EDIT_ROOMHF, &CI3DL2ReverbDlg::OnEnChangeEditRoomhf)
	ON_EN_CHANGE(IDC_EDIT_ROLLOFF, &CI3DL2ReverbDlg::OnEnChangeEditRolloff)
	ON_EN_CHANGE(IDC_EDIT_DECAYTIME, &CI3DL2ReverbDlg::OnEnChangeEditDecaytime)
	ON_EN_CHANGE(IDC_EDIT_DECAYHFRATIO, &CI3DL2ReverbDlg::OnEnChangeEditDecayhfratio)
	ON_EN_CHANGE(IDC_EDIT_REFLECTIONS, &CI3DL2ReverbDlg::OnEnChangeEditReflections)
	ON_EN_CHANGE(IDC_EDIT_REFLECTIONSDELAY, &CI3DL2ReverbDlg::OnEnChangeEditReflectionsdelay)
	ON_EN_CHANGE(IDC_EDIT_REVERB, &CI3DL2ReverbDlg::OnEnChangeEditReverb)
	ON_EN_CHANGE(IDC_EDIT_REVERBDELAY, &CI3DL2ReverbDlg::OnEnChangeEditReverbdelay)
	ON_EN_CHANGE(IDC_EDIT_DIFFUSION, &CI3DL2ReverbDlg::OnEnChangeEditDiffusion)
	ON_EN_CHANGE(IDC_EDIT_DENSITY, &CI3DL2ReverbDlg::OnEnChangeEditDensity)
	ON_EN_CHANGE(IDC_EDIT_HFREFERENCE, &CI3DL2ReverbDlg::OnEnChangeEditHfreference)
	ON_BN_CLICKED(ID_BTESTONOFF, &CI3DL2ReverbDlg::OnBnClickedBtestonoff)
	ON_BN_CLICKED(IDOK, &CI3DL2ReverbDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CI3DL2ReverbDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CI3DL2ReverbDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DX8_I3DL2Reverb.flRoomRolloffFactor = Rolloff = 0.00; 
	DX8_I3DL2Reverb.flDecayTime = DecayTime = 1.49; 
	DX8_I3DL2Reverb.flDecayHFRatio = DecayHFRatio = 0.83;
	DX8_I3DL2Reverb.flReflectionsDelay = ReflectionsDelay = 0.007; 
	DX8_I3DL2Reverb.flReverbDelay = ReverbDelay = 0.011;
	DX8_I3DL2Reverb.flDiffusion = Diffusion = 100.00; 
	DX8_I3DL2Reverb.flDensity = Density = 100.00; 
	DX8_I3DL2Reverb.flHFReference = HFReference = 5000.00;
	DX8_I3DL2Reverb.lReverb = Reverb = 200; 
	DX8_I3DL2Reverb.lReflections = Reflections = -2602; 
	DX8_I3DL2Reverb.lRoom = Room = -1000; 
	DX8_I3DL2Reverb.lRoomHF = RoomHF = -100;

	m_SRoom.SetRange(-10000, 0, TRUE);	m_SRoom.SetPos(-1000);
	m_SRoomHF.SetRange(-10000, 0, TRUE);	m_SRoomHF.SetPos(-100);
	m_SRolloff.SetRange(0, 1000, TRUE);	m_SRolloff.SetPos(0);
	m_SDecayTime.SetRange(10, 2000, TRUE);	m_SDecayTime.SetPos(149);
	m_SDecayHFRatio.SetRange(10, 200, TRUE);	m_SDecayHFRatio.SetPos(83);
	m_SReflections.SetRange(-10000, 1000, TRUE);	m_SReflections.SetPos(-2602);
	m_SReflectionsDelay.SetRange(0, 300, TRUE);	m_SReflectionsDelay.SetPos(7);
	m_SReverb.SetRange(-10000, 2000, TRUE);	m_SReverb.SetPos(200);
	m_SReverbDelay.SetRange(0, 100, TRUE);	m_SReverbDelay.SetPos(11);
	m_SDiffusion.SetRange(0, 10000, TRUE);	m_SDiffusion.SetPos(10000);
	m_SDensity.SetRange(0, 10000, TRUE);	m_SDensity.SetPos(10000);
	m_SHFReference.SetRange(2000, 2000000, TRUE);	m_SHFReference.SetPos(500000);

	m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
	
	DefaultCore.TestOn(_T("i3dl2reverb"), 1);
	DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	Test = true;

	return TRUE;
}

// CI3DL2ReverbDlg message handlers

BOOL CI3DL2ReverbDlg::CheckData(CString Data)
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

void CI3DL2ReverbDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar *)&m_SRoom)
	{
		Room = m_SRoom.GetPos();
		DX8_I3DL2Reverb.lRoom = Room;
		m_ERoom.Empty();
		m_ERoom.Format(_T("%d"), Room);
	}
	if (pScrollBar == (CScrollBar *)&m_SRoomHF)
	{
		RoomHF = m_SRoomHF.GetPos();
		DX8_I3DL2Reverb.lRoomHF = RoomHF;
		m_ERoomHF.Empty();
		m_ERoomHF.Format(_T("%d"), RoomHF);
	}
	if (pScrollBar == (CScrollBar *)&m_SRolloff)
	{
		Rolloff = m_SRolloff.GetPos() / 100.00;
		DX8_I3DL2Reverb.flRoomRolloffFactor = Rolloff;
		m_ERolloff.Empty();
		m_ERolloff.Format(_T("%.2f"), Rolloff);
	}
	if (pScrollBar == (CScrollBar *)&m_SDecayTime)
	{
		DecayTime = m_SDecayTime.GetPos() / 100.00;
		DX8_I3DL2Reverb.flDecayTime = DecayTime;
		m_EDecayTime.Empty();
		m_EDecayTime.Format(_T("%.2f"), DecayTime);
	}
	if (pScrollBar == (CScrollBar *)&m_SDecayHFRatio)
	{
		DecayHFRatio = m_SDecayHFRatio.GetPos() / 100.00;
		DX8_I3DL2Reverb.flDecayHFRatio = DecayHFRatio;
		m_EDecayHFRatio.Empty();
		m_EDecayHFRatio.Format(_T("%.2f"), DecayHFRatio);
	}
	if (pScrollBar == (CScrollBar *)&m_SReflections)
	{
		Reflections = m_SReflections.GetPos();
		DX8_I3DL2Reverb.lReflections = Reflections;
		m_EReflections.Empty();
		m_EReflections.Format(_T("%d"), Reflections);
	}
	if (pScrollBar == (CScrollBar *)&m_SReflectionsDelay)
	{
		ReflectionsDelay = m_SReflectionsDelay.GetPos() / 1000.000;
		DX8_I3DL2Reverb.flReflectionsDelay = ReflectionsDelay;
		m_EReflectionsDelay.Empty();
		m_EReflectionsDelay.Format(_T("%.3f"), ReflectionsDelay);
	}
	if (pScrollBar == (CScrollBar *)&m_SReverb)
	{
		Reverb = m_SReverb.GetPos();
		DX8_I3DL2Reverb.lReverb = Reverb;
		m_EReverb.Empty();
		m_EReverb.Format(_T("%d"), Reverb);
	}
	if (pScrollBar == (CScrollBar *)&m_SReverbDelay)
	{
		ReverbDelay = m_SReverbDelay.GetPos() / 1000.000;
		DX8_I3DL2Reverb.flReverbDelay = ReverbDelay;
		m_EReverbDelay.Empty();
		m_EReverbDelay.Format(_T("%.3f"), ReverbDelay);
	}
	if (pScrollBar == (CScrollBar *)&m_SDiffusion)
	{
		Diffusion = m_SDiffusion.GetPos() / 100.00;
		DX8_I3DL2Reverb.flDiffusion = Diffusion;
		m_EDiffusion.Empty();
		m_EDiffusion.Format(_T("%.2f"), Diffusion);
	}
	if (pScrollBar == (CScrollBar *)&m_SDensity)
	{
		Density = m_SDensity.GetPos() / 100.00;
		DX8_I3DL2Reverb.flDensity = Density;
		m_EDensity.Empty();
		m_EDensity.Format(_T("%.2f"), Density);
	}
	if (pScrollBar == (CScrollBar *)&m_SHFReference)
	{
		HFReference = m_SHFReference.GetPos() / 100.00;
		DX8_I3DL2Reverb.flHFReference = HFReference;
		m_EHFReference.Empty();
		m_EHFReference.Format(_T("%.2f"), HFReference);
	}
	if (Test == true)
		DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	UpdateData(false);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



void CI3DL2ReverbDlg::OnEnChangeEditRoom()
{
	UpdateData(true);
	if (CheckData(m_ERoom))
	{
		Room = _wtoi(m_ERoom);
		if (Room < -10000)
		{
			MessageBox(_T("Must be in the range from -10000 to 0."), _T("Error"), MB_ICONERROR);
			Room = -10000;
		}
		if (Room > 0)
		{
			MessageBox(_T("Must be in the range from -10000 to 0."), _T("Error"), MB_ICONERROR);
			Room = 0;
		}
		DX8_I3DL2Reverb.lRoom = Room;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SRoom.SetPos(Room);
	m_ERoom.Empty();
	m_ERoom.Format(_T("%d"), Room);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditRoomhf()
{
	UpdateData(true);
	if (CheckData(m_ERoomHF))
	{
		RoomHF = _wtoi(m_ERoomHF);
		if (RoomHF < -10000)
		{
			MessageBox(_T("Must be in the range from -10000 to 0."), _T("Error"), MB_ICONERROR);
			RoomHF = -10000;
		}
		if (RoomHF > 0)
		{
			MessageBox(_T("Must be in the range from -10000 to 0."), _T("Error"), MB_ICONERROR);
			RoomHF = 0;
		}
		DX8_I3DL2Reverb.lRoomHF = RoomHF;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SRoomHF.SetPos(RoomHF);
	m_ERoomHF.Empty();
	m_ERoomHF.Format(_T("%d"), RoomHF);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditRolloff()
{
	UpdateData(true);
	if (CheckData(m_ERolloff))
	{
		Rolloff = _wtof(m_ERolloff);
		if (Rolloff < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 10."), _T("Error"), MB_ICONERROR);
			Rolloff = 0;
		}
		if (Rolloff > 10)
		{
			MessageBox(_T("Must be in the range from 0 to 10."), _T("Error"), MB_ICONERROR);
			Rolloff = 10;
		}
		DX8_I3DL2Reverb.flRoomRolloffFactor = Rolloff;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SRolloff.SetPos(Rolloff * 100);
	m_ERolloff.Empty();
	m_ERolloff.Format(_T("%.2f"), Rolloff);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditDecaytime()
{
	UpdateData(true);
	if (CheckData(m_EDecayTime))
	{
		DecayTime = _wtof(m_EDecayTime);
		if (DecayTime < 0.1)
		{
			MessageBox(_T("Must be in the range from 0.1 to 20."), _T("Error"), MB_ICONERROR);
			DecayTime = 0.1;
		}
		if (DecayTime > 20)
		{
			MessageBox(_T("Must be in the range from 0.1 to 20."), _T("Error"), MB_ICONERROR);
			DecayTime = 20;
		}
		DX8_I3DL2Reverb.flDecayTime = DecayTime;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SDecayTime.SetPos(DecayTime * 100);
	m_EDecayTime.Empty();
	m_EDecayTime.Format(_T("%.2f"), DecayTime);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditDecayhfratio()
{
	UpdateData(true);
	if (CheckData(m_EDecayHFRatio))
	{
		DecayHFRatio = _wtof(m_EDecayHFRatio);
		if (DecayHFRatio < 0.1)
		{
			MessageBox(_T("Must be in the range from 0.1 to 2."), _T("Error"), MB_ICONERROR);
			DecayHFRatio = 0.1;
		}
		if (DecayHFRatio > 2)
		{
			MessageBox(_T("Must be in the range from 0.1 to 2."), _T("Error"), MB_ICONERROR);
			DecayHFRatio = 2;
		}
		DX8_I3DL2Reverb.flDecayHFRatio = DecayHFRatio;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SDecayHFRatio.SetPos(DecayHFRatio * 100);
	m_EDecayHFRatio.Empty();
	m_EDecayHFRatio.Format(_T("%.2f"), DecayHFRatio);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditReflections()
{
	UpdateData(true);
	if (CheckData(m_EReflections))
	{
		Reflections = _wtoi(m_EReflections);
		if (Reflections < -10000)
		{
			MessageBox(_T("Must be in the range from -10000 to 1000."), _T("Error"), MB_ICONERROR);
			Reflections = -10000;
		}
		if (Reflections > 1000)
		{
			MessageBox(_T("Must be in the range from -10000 to 1000."), _T("Error"), MB_ICONERROR);
			Reflections = 1000;
		}
		DX8_I3DL2Reverb.lReflections = Reflections;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SReflections.SetPos(Reflections);
	m_EReflections.Empty();
	m_EReflections.Format(_T("%d"), Reflections);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditReflectionsdelay()
{
	UpdateData(true);
	if (CheckData(m_EReflectionsDelay))
	{
		ReflectionsDelay = _wtof(m_EReflectionsDelay);
		if (ReflectionsDelay < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 0.3."), _T("Error"), MB_ICONERROR);
			ReflectionsDelay = 0;
		}
		if (ReflectionsDelay > 0.3)
		{
			MessageBox(_T("Must be in the range from 0 to 0.3."), _T("Error"), MB_ICONERROR);
			ReflectionsDelay = 0.3;
		}
		DX8_I3DL2Reverb.flReflectionsDelay = ReflectionsDelay;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SReflectionsDelay.SetPos(ReflectionsDelay * 1000);
	m_EReflectionsDelay.Empty();
	m_EReflectionsDelay.Format(_T("%.3f"), ReflectionsDelay);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditReverb()
{
	UpdateData(true);
	if (CheckData(m_EReverb))
	{
		Reverb = _wtoi(m_EReverb);
		if (Reverb < -10000)
		{
			MessageBox(_T("Must be in the range from -10000 to 2000."), _T("Error"), MB_ICONERROR);
			Reverb = -10000;
		}
		if (Reverb > 2000)
		{
			MessageBox(_T("Must be in the range from -10000 to 2000."), _T("Error"), MB_ICONERROR);
			Reverb = 2000;
		}
		DX8_I3DL2Reverb.lReverb = Reverb;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SReverb.SetPos(Reverb);
	m_EReverb.Empty();
	m_EReverb.Format(_T("%d"), Reverb);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditReverbdelay()
{
	UpdateData(true);
	if (CheckData(m_EReverbDelay))
	{
		ReverbDelay = _wtof(m_EReverbDelay);
		if (ReverbDelay < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 0.1."), _T("Error"), MB_ICONERROR);
			ReverbDelay = 0;
		}
		if (ReverbDelay > 0.1)
		{
			MessageBox(_T("Must be in the range from 0 to 0.1."), _T("Error"), MB_ICONERROR);
			ReverbDelay = 0.1;
		}
		DX8_I3DL2Reverb.flReverbDelay = ReverbDelay;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SReverbDelay.SetPos(ReverbDelay * 1000);
	m_EReverbDelay.Empty();
	m_EReverbDelay.Format(_T("%.3f"), ReverbDelay);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditDiffusion()
{
	UpdateData(true);
	if (CheckData(m_EDiffusion))
	{
		Diffusion = _wtof(m_EDiffusion);
		if (Diffusion < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			Diffusion = 0;
		}
		if (Diffusion > 100)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			Diffusion = 100;
		}
		DX8_I3DL2Reverb.flDiffusion = Diffusion;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SDiffusion.SetPos(Diffusion * 100);
	m_EDiffusion.Empty();
	m_EDiffusion.Format(_T("%.2f"), Diffusion);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditDensity()
{
	UpdateData(true);
	if (CheckData(m_EDensity))
	{
		Density = _wtof(m_EDensity);
		if (Density < 0)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			Density = 0;
		}
		if (Density > 100)
		{
			MessageBox(_T("Must be in the range from 0 to 100."), _T("Error"), MB_ICONERROR);
			Density = 100;
		}
		DX8_I3DL2Reverb.flDensity = Density;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SDensity.SetPos(Density * 100);
	m_EDensity.Empty();
	m_EDensity.Format(_T("%.2f"), Density);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnEnChangeEditHfreference()
{
	UpdateData(true);
	if (CheckData(m_EHFReference))
	{
		HFReference = _wtof(m_EHFReference);
		if (HFReference < 20)
		{
			MessageBox(_T("Must be in the range from 20 to 20000."), _T("Error"), MB_ICONERROR);
			HFReference = 20;
		}
		if (HFReference > 20000)
		{
			MessageBox(_T("Must be in the range from 20 to 20000."), _T("Error"), MB_ICONERROR);
			HFReference = 20000;
		}
		DX8_I3DL2Reverb.flHFReference = HFReference;
		if (Test == true)
			DefaultCore.TestUpdate(DX8_I3DL2Reverb);
	}
	m_SHFReference.SetPos(HFReference * 100);
	m_EHFReference.Empty();
	m_EHFReference.Format(_T("%.2f"), HFReference);
	UpdateData(false);
}


void CI3DL2ReverbDlg::OnBnClickedBtestonoff()
{
	if (Test)
	{
		DefaultCore.TestOff();
		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_OFF));
		Test = false;
	}
	else
	{
		DX8_I3DL2Reverb.flRoomRolloffFactor = Rolloff;
		DX8_I3DL2Reverb.flDecayTime = DecayTime;
		DX8_I3DL2Reverb.flDecayHFRatio = DecayHFRatio;
		DX8_I3DL2Reverb.flReflectionsDelay = ReflectionsDelay;
		DX8_I3DL2Reverb.flReverbDelay = ReverbDelay;
		DX8_I3DL2Reverb.flDiffusion = Diffusion;
		DX8_I3DL2Reverb.flDensity = Density;
		DX8_I3DL2Reverb.flHFReference = HFReference;
		DX8_I3DL2Reverb.lReverb = Reverb;
		DX8_I3DL2Reverb.lReflections = Reflections;
		DX8_I3DL2Reverb.lRoom = Room;
		DX8_I3DL2Reverb.lRoomHF = RoomHF;

		DefaultCore.TestOn(_T("i3dl2reverb"), 1);
		DefaultCore.TestUpdate(DX8_I3DL2Reverb);

		m_BTestOnOff.SetIcon(theApp.LoadIcon(ID_PLAY_ON));
		Test = true;
	}
}


void CI3DL2ReverbDlg::OnBnClickedOk()
{
	DefaultCore.AddEffect(DX8_I3DL2Reverb);
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnOK();
}


void CI3DL2ReverbDlg::OnBnClickedCancel()
{
	if (Test)
		DefaultCore.TestOff();
	CDialogEx::OnCancel();
}


void CI3DL2ReverbDlg::OnClose()
{
	OnBnClickedCancel();
}
