#pragma once
#include "AudioCore.h"
#include "afxcmn.h"
#include "afxwin.h"

// CDistortionDlg dialog

class CDistortionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDistortionDlg)

public:
	CDistortionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDistortionDlg();

// Dialog Data
	enum { IDD = IDD_DISTORTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	bool Test;
	float Gain, Edge, Frequency, Bandwidth, Cutoff;
	BASS_DX8_DISTORTION DX8_Distortion;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SBandwidth;
	CSliderCtrl m_SCutoff;
	CSliderCtrl m_SEdge;
	CSliderCtrl m_SFrequency;
	CSliderCtrl m_SGain;
	CString m_EBandwidth;
	CString m_ECutoff;
	CString m_EEdge;
	CString m_EFrequency;
	CString m_EGain;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	afx_msg void OnEnChangeEditGain();
	afx_msg void OnEnChangeEditEdge();
	afx_msg void OnEnChangeEditFrequency();
	afx_msg void OnEnChangeEditBandwidth();
	afx_msg void OnEnChangeEditCutoff();
	CButton m_BTestOnOff;
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtestonoff();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
