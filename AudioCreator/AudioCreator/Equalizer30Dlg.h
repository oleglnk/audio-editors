#pragma once
#include "AudioCore.h"
#include "afxwin.h"

// CEqualizer30Dlg dialog

class CEqualizer30Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEqualizer30Dlg)

public:
	CEqualizer30Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEqualizer30Dlg();

// Dialog Data
	enum { IDD = IDD_EQUALIZER30_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL CheckData(CString Data);
	bool Test;
	int Bands[30];
	BASS_BFX_PEAKEQ BFX_Peakeq[30];

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	//Sliders:
	CSliderCtrl m_S31Hz;
	CSliderCtrl m_S40Hz;
	CSliderCtrl m_S50Hz;
	CSliderCtrl m_S63Hz;
	CSliderCtrl m_S80Hz;
	CSliderCtrl m_S100Hz;
	CSliderCtrl m_S125Hz;
	CSliderCtrl m_S160Hz;
	CSliderCtrl m_S200Hz;
	CSliderCtrl m_S250Hz;
	CSliderCtrl m_S315Hz;
	CSliderCtrl m_S400Hz;
	CSliderCtrl m_S500Hz;
	CSliderCtrl m_S630Hz;
	CSliderCtrl m_S800Hz;
	CSliderCtrl m_S1KHz;
	CSliderCtrl m_S1P25KHz;
	CSliderCtrl m_S1P6KHz;
	CSliderCtrl m_S2KHz;
	CSliderCtrl m_S2P5KHz;
	CSliderCtrl m_S3P2KHz;
	CSliderCtrl m_S4KHz;
	CSliderCtrl m_S5KHz;
	CSliderCtrl m_S6P3KHz;
	CSliderCtrl m_S8KHz;
	CSliderCtrl m_S10KHz;
	CSliderCtrl m_S12P5KHz;
	CSliderCtrl m_S16KHz;
	CSliderCtrl m_S20KHz;
	CSliderCtrl m_S25KHz;
	//Edits:
	CString m_E31Hz;
	CString m_E40Hz;
	CString m_E50Hz;
	CString m_E63Hz;
	CString m_E80Hz;
	CString m_E100Hz;
	CString m_E125Hz;
	CString m_E160Hz;
	CString m_E200Hz;
	CString m_E250Hz;
	CString m_E315Hz;
	CString m_E400Hz;
	CString m_E500Hz;
	CString m_E630Hz;
	CString m_E800Hz;
	CString m_E1KHz;
	CString m_E1P25KHz;
	CString m_E1P6KHz;
	CString m_E2KHz;
	CString m_E2P5KHz;
	CString m_E3P2KHz;
	CString m_E4KHz;
	CString m_E5KHz;
	CString m_E6P3KHz;
	CString m_E8KHz;
	CString m_E10KHz;
	CString m_E12P5KHz;
	CString m_E16KHz;
	CString m_E20KHz;
	CString m_E25KHz;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	afx_msg void OnEnChangeEdit31hz30();
	afx_msg void OnEnChangeEdit40hz30();
	afx_msg void OnEnChangeEdit50hz30();
	afx_msg void OnEnChangeEdit63hz30();
	afx_msg void OnEnChangeEdit80hz30();
	afx_msg void OnEnChangeEdit100hz30();
	afx_msg void OnEnChangeEdit125hz30();
	afx_msg void OnEnChangeEdit160hz30();
	afx_msg void OnEnChangeEdit200hz30();
	afx_msg void OnEnChangeEdit250hz30();
	afx_msg void OnEnChangeEdit315hz30();
	afx_msg void OnEnChangeEdit400hz30();
	afx_msg void OnEnChangeEdit500hz30();
	afx_msg void OnEnChangeEdit630hz30();
	afx_msg void OnEnChangeEdit800hz30();
	afx_msg void OnEnChangeEdit1khz30();
	afx_msg void OnEnChangeEdit1p25khz30();
	afx_msg void OnEnChangeEdit1p6khz30();
	afx_msg void OnEnChangeEdit2khz30();
	afx_msg void OnEnChangeEdit2p5khz30();
	afx_msg void OnEnChangeEdit3p2khz30();
	afx_msg void OnEnChangeEdit4khz30();
	afx_msg void OnEnChangeEdit5khz30();
	afx_msg void OnEnChangeEdit6p3khz30();
	afx_msg void OnEnChangeEdit8khz30();
	afx_msg void OnEnChangeEdit10khz30();
	afx_msg void OnEnChangeEdit12p5khz30();
	afx_msg void OnEnChangeEdit16khz30();
	afx_msg void OnEnChangeEdit20khz30();
	afx_msg void OnEnChangeEdit25khz30();
	CButton m_BTestOnOff;
	afx_msg void OnBnClickedBtestonoff();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
