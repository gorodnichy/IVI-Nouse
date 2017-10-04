#pragma once
#define REGISTRY_USER_VARIABLE_NAME _T("User")
#define REGISTRY_PASS_VARIABLE_NAME _T("Pass")

#include "../NouseSettings/DataHandler.h"
//#include "DataHandler.h"

class CRegistrationHandler
{
public:

	CRegistrationHandler();
	~CRegistrationHandler();

	bool CheckVersion(CString* pMessage);
	void CopyData(CDataHandler* pData) {
		 m_strNouseTrialInfo = pData->m_strNouseTrialInfo;
		 m_strNouseTrademark = pData->m_strNouseTrademark;
		 m_strDaysLeftInTrial = pData->m_strDaysLeftInTrial;
		 m_strTrialExpired = pData->m_strTrialExpired;
		 m_strDisableWarning = pData->m_strDisableWarning;

	};

	int handleTrialBusiness();
	bool handleActivationKey(CString strEmail = _T(""), CString strKey = _T(""), CString strName = _T(""));

private:
	CString formatMessage(int nDayLeft = -1);
	int Register(CString strEmail = _T(""), CString strKey = _T(""));
	CString GetVersion();
	void sendMessage(CString strMessage, UINT nIcon = MB_OK);
	
	int registryTransaction(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, bool bTrueGetFalseSet, char* strVal);

	bool m_bTrialExpired; // =false;
	CString convertEmail2Id(CString strEmail);
	/////////////////////////////
	CString m_strNouseTrialInfo;
	CString m_strNouseTrademark;
	CString m_strDaysLeftInTrial;
	CString m_strTrialExpired;
	CString m_strDisableWarning;	

};

