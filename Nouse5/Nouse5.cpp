
// Nouse5.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Nouse5.h"
#include "Nouse5Dlg.h"
#include "StartupScreen.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNouse5App

BEGIN_MESSAGE_MAP(CNouse5App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CNouse5App construction

CNouse5App::CNouse5App()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CNouse5App object

CNouse5App theApp;


// CNouse5App initialization

BOOL CNouse5App::InitInstance()
{

	m_singleInstanceMutex = CreateMutex(NULL, TRUE, L"Nouse");
	if (m_singleInstanceMutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND existingApp = FindWindow(0, L"Nouse");
		if (existingApp) SetForegroundWindow(existingApp);
		{
			return FALSE; // Exit the app. For MFC, return false from InitInstance.
		}

	}
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	/////////


	//if no registered user  - go to trial
	LONG nResult = CheckRegistery();
	if (nResult == ERROR_INVALID_ACCESS)
	{
		AfxMessageBox(_T("Invalid Acess Error!\nMake sure Nouse is properly installed and has the administrative permission to run on this machine."),
			MB_OK | MB_ICONERROR);
		return -1;
	}

	if (nResult != ERROR_SUCCESS)
	{

		CStartupScreen* pSplashscr = new CStartupScreen();
		nResult = pSplashscr->DoModal();
		if (nResult == IDCANCEL)
		{
			delete pSplashscr;
			return FALSE;
		}
		else
			delete pSplashscr;
	}
	else
		nResult = IDOK;// reset for trail

					   // Create the shell manager, in case the dialog contains
					   // any shell tree view or shell list view controls.

	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CNouse5Dlg dlg;

	m_pMainWnd = &dlg;


	dlg.SetTrialStatus(nResult != IDOK);
	INT_PTR nResponse = dlg.DoModal();
	/*if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		 //  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		dlg.exitNouse();
	}*/
								

									  // Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	dlg.exitNouse();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

LONG CNouse5App::CheckRegistery()
{
	DWORD dwSize = 256;
	DWORD dwType = REG_SZ;
	char strDateVal[256];
	HKEY programKey;
	unsigned long nDisposition;
	CString strVal;
	CString lpValueName;

#ifdef _DEBUG	
	int nRet = RegCreateKeyEx(
		HKEY_LOCAL_MACHINE,							// handle to an open key
		SECRET_REGISTRY_LOCATION,
		0,											// reserved
		NULL,										// address of class string
		REG_OPTION_NON_VOLATILE,					// special options flag
		KEY_ALL_ACCESS,								// desired security access
		NULL,										// address of key security structure
		&programKey,								// address of buffer for opened handle
		&nDisposition								// address of disposition value buffer
	);
	nRet = RegDeleteValue(programKey, REGISTRY_USER_VARIABLE_NAME);
	nRet = RegDeleteValue(programKey, REGISTRY_PASS_VARIABLE_NAME);
	//	nRet = RegDeleteValue(programKey, REGISTRY_TIME_VARIABLE_NAME);
#endif 
	LONG nRetVal = RegOpenKeyEx(HKEY_LOCAL_MACHINE, SECRET_REGISTRY_LOCATION, NULL, KEY_ALL_ACCESS, &programKey);
	nRetVal = RegQueryValueEx(programKey, REGISTRY_USER_VARIABLE_NAME, 0, &dwType, (LPBYTE)strDateVal, &dwSize);
	nRetVal += RegQueryValueEx(programKey, REGISTRY_PASS_VARIABLE_NAME, 0, &dwType, (LPBYTE)strDateVal, &dwSize);
	RegCloseKey(programKey);

	return nRetVal;
}

