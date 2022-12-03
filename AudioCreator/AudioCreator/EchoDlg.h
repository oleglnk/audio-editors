#pragma once
#include "AudioCore.h"
#include "afxcmn.h"
#include "afxwin.h"

// CEchoDlg dialog

class CEchoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEchoDlg)

public:
	CEchoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEchoDlg();

// Dialog Data
	enum { IDD = IDD_ECHO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	bool Test;
	float WetDryMix, Feedback, LDelay, RDelay;
	BASS_DX8_ECHO DX8_Echo;

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SFeedback;
	CSliderCtrl m_SLDelay;
	CSliderCtrl m_SRDelay;
	CSliderCtrl m_SWetDryMix;
	CString m_EFeedback;
	CString m_ELDelay;
	CString m_ERDelay;
	CString m_EWetDryMix;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditWetdrymix();
	afx_msg void OnEnChangeEditFeedback();
	afx_msg void OnEnChangeEditLdelay();
	afx_msg void OnEnChangeEditRdelay();
	afx_msg void OnBnClickedBtestonoff();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	CButton m_BTestOnOff;
};
