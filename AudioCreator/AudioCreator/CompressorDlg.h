#pragma once
#include "AudioCore.h"
#include "afxcmn.h"
#include "afxwin.h"

// CCompressorDlg dialog

class CCompressorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCompressorDlg)

public:
	CCompressorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCompressorDlg();

// Dialog Data
	enum { IDD = IDD_COMPRESSOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	bool Test;
	float Gain, Attack, Release, Threshold, Ratio, PreDelay;
	BASS_DX8_COMPRESSOR DX8_Compressor;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_EGain;
	CString m_EAttack;
	CString m_ERelease;
	CString m_EThreshold;
	CString m_ERatio;
	CString m_EPreDelay;
	CSliderCtrl m_SAttack;
	CSliderCtrl m_SGain;
	CSliderCtrl m_SPreDelay;
	CSliderCtrl m_SRatio;
	CSliderCtrl m_SRelease;
	CSliderCtrl m_SThreshold;
	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditGain();
	afx_msg void OnEnChangeEditAttack();
	afx_msg void OnEnChangeEditRelease();
	afx_msg void OnEnChangeEditThreshold();
	afx_msg void OnEnChangeEditRatio();
	afx_msg void OnEnChangeEditPredelay();
	afx_msg void OnBnClickedBtestonoff();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_BTestOnOff;
	afx_msg void OnClose();
};
