
// AudioCreator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AudioCreator.h"
#include "AudioCreatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAudioCreatorApp

BEGIN_MESSAGE_MAP(CAudioCreatorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAudioCreatorApp construction

CAudioCreatorApp::CAudioCreatorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CAudioCreatorApp object

CAudioCreatorApp theApp;


// CAudioCreatorApp initialization

BOOL CAudioCreatorApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	CShellManager *pShellManager = new CShellManager;

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	if (Verification() == FALSE)
	{
		if (pShellManager != NULL)
			delete pShellManager;
		return FALSE;
	}
	CAudioCreatorDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	if (pShellManager != NULL)
		delete pShellManager;

	return FALSE;
}


BOOL CAudioCreatorApp::Verification()
{
	CString files[] = { _T("bass.dll"), _T("bassenc.dll"),_T("bass_fx.dll"),
		_T("bass_ape.dll"), _T("bass_mpc.dll"), _T("bass_tta.dll"), 
		_T("bassflac.dll"), _T("basswma.dll"), _T("basswv.dll"),
		_T("lame.exe"), _T("lame_enc.dll"), _T("wavpack.exe"), _T("oggenc2.exe") };
	CString Path;
	TCHAR buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer), buffer);
	for (int i = 0; i < 7; i++)
	{
		Path.Empty();
		Path = buffer;
		Path += _T("\\");
		Path += files[i];
		if (CFileFind().FindFile(Path) == FALSE)
		{
			MessageBox(NULL, _T("Missing ") + files[i] + _T("\nPlease reinstall the program or contact to support."), _T("Error"), MB_OK | MB_ICONERROR);
			return FALSE;
		}
			
	}
	return TRUE;
}
