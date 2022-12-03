
// AudioCreator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAudioCreatorApp:
// See AudioCreator.cpp for the implementation of this class
//

class CAudioCreatorApp : public CWinApp
{
public:
	CAudioCreatorApp();

// Overrides
public:
	virtual BOOL InitInstance();
	BOOL Verification();
// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAudioCreatorApp theApp;