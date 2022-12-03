#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "AudioCore.h"

// CSaveOGGDlg dialog

class CSaveOGGDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveOGGDlg)

public:
	CSaveOGGDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveOGGDlg();

// Dialog Data
	enum { IDD = IDD_SAVEOGG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	int Quality;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString SavePath;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClose();
	CComboBox m_CQuality;
	CString m_EQuality;
	CSliderCtrl m_SFileSize;
	afx_msg void OnEnChangeEditQuality();
	afx_msg void OnCbnSelchangeComboQuality();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
