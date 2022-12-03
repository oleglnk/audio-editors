#pragma once
#include "AudioCore.h"
#include "afxcmn.h"
#include "afxwin.h"

// CEqualizer10Dlg dialog

class CEqualizer10Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEqualizer10Dlg)

public:
	CEqualizer10Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEqualizer10Dlg();

// Dialog Data
	enum { IDD = IDD_EQUALIZER10_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support	
	BOOL CheckData(CString Data);
	bool Test;
	int m_125Hz, m_16KHz, m_1KHz, m_250Hz, m_2KHz, m_31Hz, m_4KHz, m_500Hz, m_63Hz, m_8KHz;
	BASS_BFX_PEAKEQ BFX_Peakeq[10];

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_S125Hz;
	CSliderCtrl m_S16KHz;
	CSliderCtrl m_S1KHz;
	CSliderCtrl m_S250Hz;
	CSliderCtrl m_S2KHz;
	CSliderCtrl m_S31Hz;
	CSliderCtrl m_S4KHz;
	CSliderCtrl m_S500Hz;
	CSliderCtrl m_S63Hz;
	CSliderCtrl m_S8KHz;
	CString m_E125Hz;
	CString m_E16KHz;
	CString m_E1KHz;
	CString m_E250Hz;
	CString m_E2KHz;
	CString m_E31Hz;
	CString m_E4KHz;
	CString m_E500Hz;
	CString m_E63Hz;
	CString m_E8KHz;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	afx_msg void OnEnChangeEdit31hz();
	afx_msg void OnEnChangeEdit63hz();
	afx_msg void OnEnChangeEdit125hz();
	afx_msg void OnEnChangeEdit250hz();
	afx_msg void OnEnChangeEdit500hz();
	afx_msg void OnEnChangeEdit1khz();
	afx_msg void OnEnChangeEdit2khz();
	afx_msg void OnEnChangeEdit4khz();
	afx_msg void OnEnChangeEdit8khz();
	afx_msg void OnEnChangeEdit16khz();
	CButton m_BTestOnOff;
	afx_msg void OnBnClickedBtestonoff();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
