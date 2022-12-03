// SaveWAVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "SaveWAVDlg.h"
#include "afxdialogex.h"


// CSaveWAVDlg dialog

IMPLEMENT_DYNAMIC(CSaveWAVDlg, CDialogEx)

CSaveWAVDlg::CSaveWAVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSaveWAVDlg::IDD, pParent)
{

}

CSaveWAVDlg::~CSaveWAVDlg()
{
}

void CSaveWAVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveWAVDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &CSaveWAVDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSaveWAVDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_RADIO1, &CSaveWAVDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(ID_RADIO2, &CSaveWAVDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(ID_RADIO3, &CSaveWAVDlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


BOOL CSaveWAVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

// CSaveWAVDlg message handlers


void CSaveWAVDlg::OnClose()
{
	OnBnClickedCancel();
}


void CSaveWAVDlg::OnBnClickedOk()
{
	DefaultCore.SaveWAV(SavePath, Quality);
	CDialogEx::OnOK();
}


void CSaveWAVDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void CSaveWAVDlg::OnBnClickedRadio1()
{
	Quality = 1;
	CheckDlgButton(ID_RADIO2, BST_UNCHECKED);
	CheckDlgButton(ID_RADIO3, BST_UNCHECKED);
}


void CSaveWAVDlg::OnBnClickedRadio2()
{
	CheckDlgButton(ID_RADIO1, BST_UNCHECKED);
	Quality = 2;
	CheckDlgButton(ID_RADIO3, BST_UNCHECKED);
}


void CSaveWAVDlg::OnBnClickedRadio3()
{
	CheckDlgButton(ID_RADIO1, BST_UNCHECKED);
	CheckDlgButton(ID_RADIO2, BST_UNCHECKED);
	Quality = 3;
}
