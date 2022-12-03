#pragma once
#include "AudioCore.h"
#include "afxcmn.h"
#include "afxwin.h"

// CParameQDlg dialog

class CParameQDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParameQDlg)

public:
	CParameQDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CParameQDlg();

// Dialog Data
	enum { IDD = IDD_PARAMEQ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	int Center[5];
	int Gain[5];
	int Bandwidth[5];
	bool Test;
	BASS_DX8_PARAMEQ DX8_ParameQ[5];

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SGain1;
	CSliderCtrl m_SGain2;
	CSliderCtrl m_SGain3;
	CSliderCtrl m_SGain4;
	CSliderCtrl m_SGain5;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CString m_ECenter1;
	CString m_ECenter2;
	CString m_ECenter3;
	CString m_ECenter4;
	CString m_ECenter5;
	CString m_EWidth1;
	CString m_EWidth2;
	CString m_EWidth3;
	CString m_EWidth4;
	CString m_EWidth5;
	afx_msg void OnEnChangeEditCenter1();
	afx_msg void OnEnChangeEditCenter2();
	afx_msg void OnEnChangeEditCenter3();
	afx_msg void OnEnChangeEditCenter4();
	afx_msg void OnEnChangeEditCenter5();
	afx_msg void OnEnChangeEditWidth1();
	afx_msg void OnEnChangeEditWidth2();
	afx_msg void OnEnChangeEditWidth3();
	afx_msg void OnEnChangeEditWidth4();
	afx_msg void OnEnChangeEditWidth5();	
	afx_msg void OnBnClickedBtestonoff();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	CButton m_BTestOnOff;
};
