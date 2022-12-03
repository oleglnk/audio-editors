#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "AudioCore.h"


// CSaveMP3Dlg dialog

class CSaveMP3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveMP3Dlg)

public:
	CSaveMP3Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveMP3Dlg();

// Dialog Data
	enum { IDD = IDD_SAVEMP3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support	
	BOOL CheckData(CString Data);
	int Quality;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString SavePath;
	CComboBox m_CQuality;
	CString m_EQuality;
	CSliderCtrl m_SFileSize;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeComboQuality();
	afx_msg void OnEnChangeEditQuality();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
