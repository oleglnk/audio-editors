#pragma once
#include "AudioCore.h"
#include "afxcmn.h"
#include "afxwin.h"

// CI3DL2ReverbDlg dialog

class CI3DL2ReverbDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CI3DL2ReverbDlg)

public:
	CI3DL2ReverbDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CI3DL2ReverbDlg();

// Dialog Data
	enum { IDD = IDD_I3DL2REVERB_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	bool Test;
	int Room, RoomHF, Reflections, Reverb;
	float Rolloff, DecayTime, DecayHFRatio, ReflectionsDelay;
	float ReverbDelay, Diffusion, Density, HFReference;
	BASS_DX8_I3DL2REVERB DX8_I3DL2Reverb;
	
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_SRoom;
	CSliderCtrl m_SRoomHF;
	CSliderCtrl m_SRolloff;
	CSliderCtrl m_SDecayTime;
	CSliderCtrl m_SDecayHFRatio;
	CSliderCtrl m_SReflections;
	CSliderCtrl m_SReflectionsDelay;
	CSliderCtrl m_SReverb;
	CSliderCtrl m_SReverbDelay;
	CSliderCtrl m_SDiffusion;
	CSliderCtrl m_SDensity;
	CSliderCtrl m_SHFReference;
	CString m_ERolloff;
	CString m_EDecayTime;
	CString m_EDecayHFRatio;
	CString m_EReflectionsDelay;
	CString m_EReverbDelay;
	CString m_EDiffusion;
	CString m_EDensity;
	CString m_EHFReference;
	CString m_ERoom;
	CString m_ERoomHF;
	CString m_EReverb;
	CString m_EReflections;
	afx_msg void OnEnChangeEditRoom();
	afx_msg void OnEnChangeEditRoomhf();
	afx_msg void OnEnChangeEditRolloff();
	afx_msg void OnEnChangeEditDecaytime();
	afx_msg void OnEnChangeEditDecayhfratio();
	afx_msg void OnEnChangeEditReflections();
	afx_msg void OnEnChangeEditReflectionsdelay();
	afx_msg void OnEnChangeEditReverb();
	afx_msg void OnEnChangeEditReverbdelay();
	afx_msg void OnEnChangeEditDiffusion();
	afx_msg void OnEnChangeEditDensity();
	afx_msg void OnEnChangeEditHfreference();
	CButton m_BTestOnOff;
	afx_msg void OnBnClickedBtestonoff();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
