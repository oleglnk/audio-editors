
// CourseDlg.h : header file
//

#pragma once
#include <fstream>
#include "TEffects.h"
#include "afxcmn.h"
#include "afxwin.h"
using namespace std;

// CCourseDlg dialog
class CCourseDlg : public CDialogEx
{
// Construction
public:
	CCourseDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COURSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CMenu m_Menu;						//����
	HSTREAM m_MainChannel;				//������� ����� ���������������
	HSTREAM m_SaveChannel;				//����� ��� ����������
	HENCODE hencode;					//����� ������
	HFX EqualFXMain[8];					//������� ����������� ��� �������� ������
	HFX EqualFXSave[8];					//������� ����������� ��� ������ ����������
	CString PathName;					//���� � �����
	HACCEL HotKeys;						//������� �������

	//Variables:
	bool AlreadyOpen, Playing;			//������-�� ����,
	bool Paused;						//Pause ��� Stop
	bool Repeating;						//�������-�� ������
	double SongLength;					//����� �����
	int secpos, minutes, seconds;		//������� �������
	int m_TSlide;						//������
	int m_TSpectrum;					//������ ��� �������
	bool Cancel;						//������ ������ Ok ��� Cancel ��� ����������
	float fft[1024];					//������ ��� ���������� �������
	TEffects *MyEffects;				//�������
	fstream UserSettings;				//���������������� ��������� �����������

	//Functions:
	void EnabledDisabled(bool enable);	//������� �������� ���������/�����������
	void GetInformation();				//��������� ���������� �� ����������
	//Menu functions:
	void OnMenuOpen();					//������� ����
	void OnMenuClose();					//������� ����
	void OnMenuSave();					//��������� ����
	void OnMenuUndo();					//�������� ��������� ��������
	void OnMenuRepeatLastAction();		//��������� ��������� ��������
	void OnMenuRepeat();				//��������/��������� ������ ���������������
	void OnMenuExit();					//�����
		//Effects:
	void OnMenuChorus();				//���
	void OnMenuDistortion();			//���������
	void OnMenuEcho();					//���
	void OnMenuFlanger();				//�������
	void OnMenuGargle();				//����������� ���������
	void OnMenuI3DL2Reverb();			//I3DL2 ����������
	void OnMenuReverb();				//����������

	virtual BOOL PreTranslateMessage(MSG* pMsg);	//��������� ������� ������

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SlidePlayTime;
	CStatic m_TotalTime;
	CStatic m_CurrentTime;
	CComboBox m_EqualizerList;
	CSliderCtrl m_Equlizer125HZ;
	CSliderCtrl m_Equlizer250HZ;
	CSliderCtrl m_Equlizer500HZ;
	CSliderCtrl m_Equlizer1KHZ;
	CSliderCtrl m_Equlizer2KHZ;
	CSliderCtrl m_Equlizer4KHZ;
	CSliderCtrl m_Equlizer8KHZ;
	CSliderCtrl m_Equlizer16KHZ;
	CTabCtrl m_TabCtrlDifInf;
	CListBox m_Info;
	CListBox m_InfoType;
	CListBox m_History;
	CSliderCtrl m_VolumeSlider;
	afx_msg void OnBnClickedPlayPause();
	afx_msg void OnBnClickedStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCbnSelchangeEqualizerlist();
	afx_msg void OnTcnSelchangeTabdifinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangingTabdifinfo(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_Saving;
};
