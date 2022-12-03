
// AudioCreatorDlg.h : header file
//

#pragma once
#include "AudioCore.h"
#include "ChorusDlg.h"
#include "CompressorDlg.h"
#include "DistortionDlg.h"
#include "EchoDlg.h"
#include "Equalizer10Dlg.h"
#include "Equalizer20Dlg.h"
#include "Equalizer30Dlg.h"
#include "FlangerDlg.h"
#include "GargleDlg.h"
#include "I3DL2ReverbDlg.h"
#include "ParameQDlg.h"
#include "ReverbDlg.h"
#include "SaveMP3Dlg.h"
#include "SaveOGGDlg.h"
#include "SaveWAVDlg.h"
#include "RecordDlg.h"
#include "afxcmn.h"
#include "afxwin.h"

// CAudioCreatorDlg dialog
class CAudioCreatorDlg : public CDialogEx
{
// Construction
public:
	CAudioCreatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AUDIOCREATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CMenu m_Menu;
	HACCEL HotKeys;
	INT_PTR nResponse;
	int m_TTime;
	int m_TLevels;
	int m_TPlayHead;
	int PHSpeed;
	bool IsLaunched;
	bool FirstLaunch;
	bool ReverseOn;
	bool Paused;
	bool Cancel;
	bool MustBeDelete;
	CFont *m_TimeFont;
	CString OriginPath;
	CBitmap WaveForm, BG, PH;
	int phpos;
	int type;
	DWORD CurPos;

	void DrawLvLsBG();
	void OnFMenuNew();
	void OnFMenuOpen();
	void OnFMenuClose();
	void OnFMenuSave();
	void OnFMenuExit();
	void OnFMenuUndo();
	void OnFMenuRLC();
	void OnFMenuChorus();
	void OnFMenuCompressor();
	void OnFMenuDistortion();
	void OnFMenuEcho(); 
	void OnFMenuEqualizer10();
	void OnFMenuEqualizer20();
	void OnFMenuEqualizer30();
	void OnFMenuReverb();
	void OnFMenuFlanger();
	void OnFMenuGargle();
	void OnFMenuI3DL2Reverb();
	void OnFMenuParameQ();
	void EnableAll();
	void DisableAll();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_History;
	CListBox m_Info;
	CListBox m_InfoType;
	CTabCtrl m_TabInfo;
	CTabCtrl m_TabHistory;
	CButton m_BPause;
	CButton m_BPlay;
	CButton m_BRecord;
	CButton m_BReverse;
	CButton m_BStop;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBstop();
	afx_msg void OnBnClickedBpause();
	afx_msg void OnBnClickedBplay();
	afx_msg void OnBnClickedBrecord();
	afx_msg void OnBnClickedBreverse();
	CStatic m_CurrentTime;
	CString m_EStartSelection;
	CString m_EEndSelection;
	CString m_EDurSelection;
};
