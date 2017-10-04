#pragma once
#include "afxwin.h"
#include "SettingsHandler.h"

class CSettingsTabDlg :
	public CDialog
{
public:

	CSettingsTabDlg(CWnd* pParent = NULL) : CDialog(IDD)
	{
	}

	virtual ~CSettingsTabDlg()
	{
	}
	enum { IDD };
	virtual void GetData(CSettingsHandler* p_SettingsHandler) {}
	virtual void SetData(CSettingsHandler* p_SettingsHandler) {}
};

