
// NouseSettings.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CNouseSettingsApp:
// See NouseSettings.cpp for the implementation of this class
//

class CNouseSettingsApp : public CWinApp
{
public:
	CNouseSettingsApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	HANDLE m_singleInstanceMutex;
};

extern CNouseSettingsApp theApp;