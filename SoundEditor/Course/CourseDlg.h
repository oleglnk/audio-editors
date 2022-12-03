
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
	CMenu m_Menu;						//Меню
	HSTREAM m_MainChannel;				//Главный канал воспроизведения
	HSTREAM m_SaveChannel;				//Канал для сохранения
	HENCODE hencode;					//Канал записи
	HFX EqualFXMain[8];					//Эффекты эквалайзера для главного канала
	HFX EqualFXSave[8];					//Эффекты эквалайзера для канала сохранения
	CString PathName;					//Путь к файлу
	HACCEL HotKeys;						//Горячие клавиши

	//Variables:
	bool AlreadyOpen, Playing;			//Открыт-ли файл,
	bool Paused;						//Pause или Stop
	bool Repeating;						//Включен-ли повтор
	double SongLength;					//Длина песни
	int secpos, minutes, seconds;		//Текущая позиция
	int m_TSlide;						//Таймер
	int m_TSpectrum;					//Таймер для спектра
	bool Cancel;						//Нажата кнопка Ok или Cancel при сохранении
	float fft[1024];					//Данные для прорисовки спектра
	TEffects *MyEffects;				//Эффекты
	fstream UserSettings;				//Пользовательская настройка эквалайзера

	//Functions:
	void EnabledDisabled(bool enable);	//Сделать элементы активными/неактивными
	void GetInformation();				//Получение информации об аудиофайле
	//Menu functions:
	void OnMenuOpen();					//Открыть Файл
	void OnMenuClose();					//Закрыть файл
	void OnMenuSave();					//Сохранить файл
	void OnMenuUndo();					//Отменить Последнее Действие
	void OnMenuRepeatLastAction();		//Повторить Последнее Действие
	void OnMenuRepeat();				//Включить/Выключить Повтор Воспроизведения
	void OnMenuExit();					//Выход
		//Effects:
	void OnMenuChorus();				//Хор
	void OnMenuDistortion();			//Искажение
	void OnMenuEcho();					//Эхо
	void OnMenuFlanger();				//Фланжер
	void OnMenuGargle();				//Амплитудная модуляция
	void OnMenuI3DL2Reverb();			//I3DL2 Ревербация
	void OnMenuReverb();				//Ревербация

	virtual BOOL PreTranslateMessage(MSG* pMsg);	//Обработка горячих клавиш

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
