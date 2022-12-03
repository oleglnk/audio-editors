#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "AudioCore.h"


// CSaveWAVDlg dialog

class CSaveWAVDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveWAVDlg)

public:
	CSaveWAVDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveWAVDlg();

// Dialog Data
	enum { IDD = IDD_SAVEWAV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	int Quality;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString SavePath;
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
};
