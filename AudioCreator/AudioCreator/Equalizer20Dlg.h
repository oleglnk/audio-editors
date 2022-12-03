#pragma once
#include "AudioCore.h"
#include "afxwin.h"

// CEqualizer20Dlg dialog

class CEqualizer20Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEqualizer20Dlg)

public:
	CEqualizer20Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEqualizer20Dlg();

// Dialog Data
	enum { IDD = IDD_EQUALIZER20_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	bool Test;
	int Bands[20];
	BASS_BFX_PEAKEQ BFX_Peakeq[20];

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//Slider
	CSliderCtrl m_S31Hz;
	CSliderCtrl m_S44Hz;
	CSliderCtrl m_S63Hz;
	CSliderCtrl m_S88Hz;
	CSliderCtrl m_S125Hz;
	CSliderCtrl m_S180Hz;
	CSliderCtrl m_S250Hz;
	CSliderCtrl m_S355Hz;
	CSliderCtrl m_S500Hz;
	CSliderCtrl m_S710Hz;
	CSliderCtrl m_S1KHz;
	CSliderCtrl m_S1P4KHz;
	CSliderCtrl m_S2KHz;
	CSliderCtrl m_S2P8KHz;
	CSliderCtrl m_S4KHz;
	CSliderCtrl m_S5P6KHz;
	CSliderCtrl m_S8KHz;
	CSliderCtrl m_S11P3KHz;
	CSliderCtrl m_S16KHz;
	CSliderCtrl m_S22KHz;
	//Edit
	CString m_E31Hz;
	CString m_E44Hz;
	CString m_E63Hz;
	CString m_E88Hz;
	CString m_E125Hz;
	CString m_E180Hz;
	CString m_E250Hz;
	CString m_E355Hz;
	CString m_E500Hz;
	CString m_E710Hz;
	CString m_E1KHz;
	CString m_E1P4KHz;
	CString m_E2KHz;
	CString m_E2P8KHz;
	CString m_E4KHz;
	CString m_E5P6KHz;
	CString m_E8KHz;
	CString m_E11P3KHz;
	CString m_E16KHz;
	CString m_E22KHz;
	afx_msg void OnEnChangeEdit31hz20();
	afx_msg void OnEnChangeEdit44hz20();
	afx_msg void OnEnChangeEdit63hz20();
	afx_msg void OnEnChangeEdit88hz20();
	afx_msg void OnEnChangeEdit125hz20();
	afx_msg void OnEnChangeEdit180hz20();
	afx_msg void OnEnChangeEdit250hz20();
	afx_msg void OnEnChangeEdit355hz20();
	afx_msg void OnEnChangeEdit500hz20();
	afx_msg void OnEnChangeEdit710hz20();
	afx_msg void OnEnChangeEdit1khz20();
	afx_msg void OnEnChangeEdit1p4khz20();
	afx_msg void OnEnChangeEdit2khz20();
	afx_msg void OnEnChangeEdit2p8khz20();
	afx_msg void OnEnChangeEdit4khz20();
	afx_msg void OnEnChangeEdit5p6khz20();
	afx_msg void OnEnChangeEdit8khz20();
	afx_msg void OnEnChangeEdit11p3khz20();
	afx_msg void OnEnChangeEdit16khz20();
	afx_msg void OnEnChangeEdit22khz20();
	CButton m_BTestOnOff;
	afx_msg void OnBnClickedBtestonoff();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
