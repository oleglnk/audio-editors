#pragma once
#include "AudioCore.h"
#include "afxcmn.h"
#include "afxwin.h"

// CGargleDlg dialog

class CGargleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGargleDlg)

public:
	CGargleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGargleDlg();

// Dialog Data
	enum { IDD = IDD_GARGLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	bool Test;
	DWORD RateHz, WaveShape;
	BASS_DX8_GARGLE DX8_Gargle;

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SRate;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditRate();
	CString m_ERate;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedBtestonoff();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	CButton m_BTestOnOff;
};
