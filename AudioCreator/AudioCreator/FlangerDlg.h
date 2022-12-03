#pragma once
#include "AudioCore.h"
#include "afxwin.h"

// CFlangerDlg dialog

class CFlangerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFlangerDlg)

public:
	CFlangerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFlangerDlg();

// Dialog Data
	enum { IDD = IDD_FLANGER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	bool Test;
	float WetDryMix, Depth, Feedback, Frequency, Delay;
	DWORD Waveform, Phase;
	BASS_DX8_FLANGER DX8_Flanger;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_EWetDryMix;
	CString m_EDepth;
	CString m_EFeedback;
	CString m_EFrequency;
	CString m_EDelay;
	CSliderCtrl m_SWetDryMix;
	CSliderCtrl m_SDepth;
	CSliderCtrl m_SFeedback;
	CSliderCtrl m_SFrequency;
	CSliderCtrl m_SDelay;
	CComboBox m_LPhase;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditWetdrymix();
	afx_msg void OnEnChangeEditDepth();
	afx_msg void OnEnChangeEditFeedback();
	afx_msg void OnEnChangeEditFrequency();
	afx_msg void OnEnChangeEditDelay();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CButton m_BTestOnOff;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeComboPhase();
	afx_msg void OnBnClickedBtestonoff();
};
