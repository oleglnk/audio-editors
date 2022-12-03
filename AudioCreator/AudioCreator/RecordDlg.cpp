// RecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "RecordDlg.h"
#include "afxdialogex.h"

#define BUFSTEP 200000
char *recbuf = NULL;
DWORD reclen;
DWORD rchan;

// CRecordDlg dialog

IMPLEMENT_DYNAMIC(CRecordDlg, CDialogEx)

CRecordDlg::CRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRecordDlg::IDD, pParent)
{

}

CRecordDlg::~CRecordDlg()
{
}

void CRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_DEVICE, m_CDevice);
	DDX_Control(pDX, ID_FREQ, m_CFreq);
}


BEGIN_MESSAGE_MAP(CRecordDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_START, &CRecordDlg::OnBnClickedStart)
	ON_BN_CLICKED(ID_PAUSE, &CRecordDlg::OnBnClickedPause)
	ON_BN_CLICKED(ID_FINISH, &CRecordDlg::OnBnClickedFinish)
END_MESSAGE_MAP()

BOOL CRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	BASS_DEVICEINFO device;
	for (int c = 0; BASS_RecordGetDeviceInfo(c, &device); c++)
	{
		if (device.flags&BASS_DEVICE_DEFAULT) 
		{
			m_CDevice.InsertString(0, CString(device.name));
			def = c;
			break;
		}
	}
	islaunched = false;
	m_CDevice.SelectString(0, CString(device.name));
	BASS_RecordInit(def);
	m_CFreq.InsertString(0, _T("44100 Hz"));
	m_CFreq.SelectString(0, _T("44100 Hz"));
	return TRUE;
}

BOOL CALLBACK RecordingCallback(HRECORD handle, const void *buffer, DWORD length, void *user)
{
	// increase buffer size if needed
	if ((reclen%BUFSTEP) + length >= BUFSTEP) {
		recbuf = (char*)realloc(recbuf, ((reclen + length) / BUFSTEP + 1)*BUFSTEP);
	}
	// buffer the data
	memcpy(recbuf + reclen, buffer, length);
	reclen += length;
	return TRUE; // continue recording
}

// CRecordDlg message handlers

void CRecordDlg::OnClose()
{
	OnBnClickedFinish();
}


void CRecordDlg::OnBnClickedStart()
{
	paused = false;
	islaunched = true;
	WAVEFORMATEX *wf;
	recbuf = (char*)malloc(BUFSTEP);
	reclen = 44;
	memcpy(recbuf, "RIFF\0\0\0\0WAVEfmt \20\0\0\0", 20);
	memcpy(recbuf + 36, "data\0\0\0\0", 8);
	wf = (WAVEFORMATEX*)(recbuf + 20);
	wf->wFormatTag = 1;
	wf->nChannels = 2;
	wf->wBitsPerSample = 16;
	wf->nSamplesPerSec = 44100;
	wf->nBlockAlign = wf->nChannels*wf->wBitsPerSample / 8;
	wf->nAvgBytesPerSec = wf->nSamplesPerSec*wf->nBlockAlign;

	rchan = BASS_RecordStart(44100, 2, 0, RecordingCallback, 0);
	GetDlgItem(ID_START)->EnableWindow(0);
	GetDlgItem(ID_FINISH)->EnableWindow(1);
	GetDlgItem(ID_PAUSE)->EnableWindow(1);
}


void CRecordDlg::OnBnClickedPause()
{
	if (paused)
	{
		GetDlgItem(ID_PAUSE)->SetWindowTextW(_T("Pause"));
		BASS_ChannelPlay(rchan, FALSE);
		paused = false;
	}
	else
	{
		GetDlgItem(ID_PAUSE)->SetWindowTextW(_T("Play"));
		paused = true;
		BASS_ChannelPause(rchan);
	}
}


void CRecordDlg::OnBnClickedFinish()
{
	if (islaunched)
	{
		BASS_ChannelStop(rchan);
		rchan = 0;
		*(DWORD*)(recbuf + 4) = reclen - 8;
		*(DWORD*)(recbuf + 40) = reclen - 44;
		DefaultCore.Init();
		DefaultCore.Create(recbuf, reclen);
		CDialogEx::OnOK();
	}
	else
	{
		CDialogEx::OnCancel();
	}
}
