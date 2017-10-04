#include "stdafx.h"
#include "RegistrationHandler.h"

#define USE_ACTIVATION_KEY 1
#define ACTIVATION_KEY_FILENAME _T("activation.txt")
#define IS_TRIAL_VERSION 1
#define DAYS_IN_TRIAL 30l

#define SECRET_REGISTRY_LOCATION _T("SOFTWARE\\Primrose")
#define REGISTRY_TIME_VARIABLE_NAME _T("Value")





CRegistrationHandler::CRegistrationHandler()
{
	//create defaults in case the file is missing
	m_strNouseTrialInfo = "Nouse Trial Info";
	m_strNouseTrademark = "Nouse® is a registered trademark of the National Research Council of Canada used under license to IVIM Inc.\n(US Patents : 10 / 201, 957, 10 / 653, 090. Canadian patents : #2, 395, 886, #2, 440, 015).";
	m_strDaysLeftInTrial = "Days left in trial :";
	m_strTrialExpired = "Your evaluation period expired.You may continue running the Nouse software, however the clicking funtionality is now disabled.\nPlease visit Nouse website(www.nouse.ca) to purchase the License Key to activate back the full functionality of the Nouse software.";
}

CRegistrationHandler::~CRegistrationHandler()
{
}


bool CRegistrationHandler::CheckVersion(CString* pMessage)
{
	CDataHandler dataHandler;
	dataHandler.updateFromFile();
	CopyData(&dataHandler);
	pMessage->Append(formatMessage(handleTrialBusiness()));
	return (m_bTrialExpired ? 1 : 0);
}

//Elan10 ->Dmitry2014, instead  of Elan's pvu:: -> CNouse5Dlg::
int CRegistrationHandler::registryTransaction(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, bool bTrueGetFalseSet, char* strVal)
{
	HKEY programKey;
	unsigned long nDisposition;

	// Create the registry key (or open it if it doesn't already exist)
	int nRetVal = RegCreateKeyEx(
		hKey,							// handle to an open key
		lpSubKey,
		0,											// reserved
		NULL,										// address of class string
		REG_OPTION_NON_VOLATILE,					// special options flag
		KEY_ALL_ACCESS,								// desired security access
		NULL,										// address of key security structure
		&programKey,								// address of buffer for opened handle
		&nDisposition								// address of disposition value buffer
	);

	if (nRetVal != 0)
	{
		return nRetVal;
	}

	DWORD dwSize = 256;
	DWORD dwType = REG_SZ;
	if (bTrueGetFalseSet)
		nRetVal = RegQueryValueEx(programKey, lpValueName, 0, &dwType, (LPBYTE)strVal, &dwSize);
	else
		nRetVal = RegSetValueEx(programKey, lpValueName, 0, dwType, (PBYTE)strVal, dwSize);

	RegCloseKey(programKey);

	return nRetVal;

}

int CRegistrationHandler::handleTrialBusiness()
{
	char strDateVal[256];
	time_t timeNow = time(0);
	int nRetVal = registryTransaction(HKEY_LOCAL_MACHINE, SECRET_REGISTRY_LOCATION, REGISTRY_TIME_VARIABLE_NAME, true, strDateVal);
	if (nRetVal != 0) {
		sprintf_s(strDateVal, "%lld", timeNow);
		nRetVal = registryTransaction(HKEY_LOCAL_MACHINE, SECRET_REGISTRY_LOCATION, REGISTRY_TIME_VARIABLE_NAME, false, strDateVal);
		if(nRetVal == ERROR_ACCESS_DENIED || nRetVal == ERROR_INVALID_HANDLE)
		{
			return -1; 
		}
	}
	char* p;
	time_t timeInReg = strtol(strDateVal, &p, 0);
	CTime cTimeInReg(timeInReg);
	CTimeSpan cTimeSpanTrialLength(DAYS_IN_TRIAL, 0, 0, 0);
	CTime cTimeExpiry = cTimeInReg + cTimeSpanTrialLength;
	CTime cTimeNow(timeNow);
	//CTimeSpan cTimeSpanToAddToNow(15, 0, 0, 0);
	//CTimeSpan cTimeSpanLeftInTrial = cTimeExpiry - (cTimeNow + cTimeSpanToAddToNow);
	CTimeSpan cTimeSpanLeftInTrial = cTimeExpiry - cTimeNow;
	LONGLONG lDaysLeftInTrial = cTimeSpanLeftInTrial.GetDays() + 1;
	if (lDaysLeftInTrial == (DAYS_IN_TRIAL + 1))
		lDaysLeftInTrial = DAYS_IN_TRIAL;

	m_bTrialExpired = (lDaysLeftInTrial <= 0);


	if (m_bTrialExpired && !handleActivationKey())
	{
		return -1;
	}
	return lDaysLeftInTrial;

}


 CString CRegistrationHandler::formatMessage(int nDayLeft)
 {
	 CString strMessageBoxHeading = m_strNouseTrialInfo;
	 CString strMessageBoxText;
	 UINT nIcon = MB_OK;

	 if (nDayLeft > 0 && !m_bTrialExpired)
	 {		 
		 strMessageBoxText.Format(_T("%s\n%s%d\n"), m_strNouseTrialInfo, m_strDaysLeftInTrial, nDayLeft);

		 nIcon |= MB_ICONWARNING;
	 }
	 else if (nDayLeft <= 0 && m_bTrialExpired)
	 {
		 strMessageBoxText.Format(_T("%s\n"), m_strTrialExpired);
		 nIcon |= MB_ICONEXCLAMATION;

	 }
	else if(nDayLeft < 0 && !m_bTrialExpired)// registration error
	 {
		strMessageBoxText.Format(_T("%s\n%s%d\n"), m_strNouseTrialInfo, m_strDaysLeftInTrial, nDayLeft);
		strMessageBoxText += m_strNouseTrademark;
		sendMessage(_T("Wrong or absent License Key.\nMake sure Nouse is properly installed and has the administrative permission to run on this machine."));
		nIcon |= MB_ICONERROR;
	 }

	strMessageBoxText += '\n' + m_strNouseTrademark;

	 return strMessageBoxText;
 }


 void CRegistrationHandler::sendMessage(CString strMessage, UINT nIcon)
{

	AfxMessageBox(strMessage, nIcon);

}


CString CRegistrationHandler::convertEmail2Id(CString strEmail)
{
	// g.str[i]=33+ X % 94;
	int n = strEmail.GetLength();
	char str[256];
	for (int i = 0; i<12; i++)
		str[i] = 33 + (int)strEmail[((int)strEmail[i%n]) * 13 % n] *
		(int)strEmail[(((int)strEmail[(i * 7) % n]) * 31 + 1) % n] * (i*i + n*n + 111111)
		% 94;

	str[12] = '\0';
	return CString(str);
}

bool CRegistrationHandler::handleActivationKey(CString strEmail, CString strKey, CString strName) 
{
	//CString	strNameHelp = _T("dm7");
	/*	if(strEmail.IsEmpty() && strKey.IsEmpty())// if not from a dialog form - try the file
	{ 
		CFileStatus status;
		if (!CFile::GetStatus(ACTIVATION_KEY_FILENAME, status))
			return false;
		CStdioFile fileActivation(ACTIVATION_KEY_FILENAME, CFile::modeRead);
		CString strLineEmail, strLineKey, strLineName;

		fileActivation.ReadString(strLineEmail);
		fileActivation.ReadString(strLineKey);
		fileActivation.ReadString(strLineName);
	
		CString emailStringPrefix = _T("Email: ");
		CString activationKeyStringPrefix = _T("Activation: ");
		CString nameStringPrefix = _T("Name: ");
	

		if (strLineEmail.Find(emailStringPrefix) != 0)
			return false;
		if (strLineKey.Find(activationKeyStringPrefix) != 0)
			return false;
		if (strLineName.Find(nameStringPrefix) != 0)
			return false;

		strEmail = strLineEmail.Mid(emailStringPrefix.GetLength());
		strKey = strLineKey.Mid(activationKeyStringPrefix.GetLength());
		strName = strLineName.Mid(nameStringPrefix.GetLength());
		strNameHelp.Empty();//temp for checking
		
	
	}*/
	if (strEmail.IsEmpty() || strKey.IsEmpty())// no info to work with
		return false;

	CString encodedEmail = convertEmail2Id(strEmail);

	/*
	if (!strcmp(strName, "dm7")) {
	FILE *f; f = fopen("dm7.txt", "a"); Beep(1000,100);
	fprintf(f, "%s \t \t %s\n", strEmail, g.str);
	fclose(f);
	}
	return g.str;
	

	if (strName == strNameHelp)
	{
		FILE *f;
		f = fopen("_activation.txt", "a"); Beep(1000, 100);
		fprintf(f, "%S \t \t %S\n", (LPCTSTR)strEmail, (LPCTSTR)encodedEmail);
		fprintf(f, "%s \t \t %s\n", (LPCTSTR)strEmail, CT2A(encodedEmail));
		fprintf(f, "%S \t \t %S\n", CT2A(strEmail), CT2A(encodedEmail));
		// encodedEmail.GetString();
		fclose(f);
		return true;
	}*/

	if (encodedEmail == strKey)// && !strNameHelp.IsEmpty())// code match and no file info
	{
		Register(strEmail, strKey);
		return true;
	}
	return false;

	/*
	if(strLine.Find(strConstant) == 0) {
	m_strMainDialogTitle = strLine.Mid(strConstant.GetLength());
	continue;
	}
	*/
}
CString CRegistrationHandler::GetVersion()
{
	
	DWORD dwHandle;			// ignored 
	char *buf;				// pointer to buffer to receive file-version info.
	char buf1[1024];				// pointer to buffer to store version string.
	CString strExec = AfxGetApp()->m_pszExeName;
	strExec += ".EXE";
	/* dima
	DWORD verSize = GetFileVersionInfoSize(
		strExec.GetBuffer(),	// pointer to filename string
		&dwHandle		// pointer to variable to receive zero
		);

	if (verSize != 0)
	{
		buf = new char[verSize + 1];

		BOOL res = GetFileVersionInfo(
			strExec.GetBuffer(),	// pointer to filename string
			NULL,			// ignored 
			verSize,		// size of buffer
			buf 			// pointer to buffer to receive file-version info.
		);
		ASSERT(res);
	}*/

			return strExec;
}

int CRegistrationHandler::Register(CString strEmail, CString strKey)
{
	DWORD dwSize = 256;
	DWORD dwType = REG_SZ;
	char strVal[256];
	HKEY programKey;
	unsigned long nDisposition;


	int nRetVal = RegCreateKeyEx(
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
	//ERROR_SUCCESS 0; ERROR_ACCESS_DENIED = 5; ERROR_INVALID_HANDLE = 6;
	strcpy_s(strVal, CStringA(strEmail).GetString());
	nRetVal = RegSetValueEx(programKey, REGISTRY_USER_VARIABLE_NAME, 0, dwType, (PBYTE)strVal, dwSize);
	memset(strVal, 0, 255);
	strcpy_s(strVal, CStringA(strKey).GetString());
	nRetVal = RegSetValueEx(programKey, REGISTRY_PASS_VARIABLE_NAME, 0, dwType, (PBYTE)strVal, dwSize);

	RegCloseKey(programKey);
	
	return nRetVal;
}