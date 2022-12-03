#pragma once
#include "AudioCore.h"
#include "afxcmn.h"
#include "afxwin.h"

// CReverbDlg dialog

class CReverbDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReverbDlg)

public:
	CReverbDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReverbDlg();

// Dialog Data
	enum { IDD = IDD_REVERB_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	bool Test;
	float Gain, Mix, Time, TimeRatio;
	BASS_DX8_REVERB DX8_Reverb;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_SGain;
	CSliderCtrl m_SMix;
	CSliderCtrl m_STime;
	CSliderCtrl m_STimeRatio;
	CString m_EGain;
	CString m_EMix;
	CString m_ETime;
	CString m_ETimeRatio;
	afx_msg void OnEnChangeEditGain();
	afx_msg void OnEnChangeEditMix();
	afx_msg void OnEnChangeEditTime();
	afx_msg void OnEnChangeEditTimeratio();
	CButton m_BTestOnOff;
	afx_msg void OnBnClickedBtestonoff();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
