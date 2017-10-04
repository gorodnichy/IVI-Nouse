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

	CToolTipCtrl m_ToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if (NULL != m_ToolTip)
			m_ToolTip.RelayEvent(pMsg);
		return CDialog::PreTranslateMessage(pMsg);
	}
	BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();
		//create a tool tip control
		m_ToolTip.Create(this);
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX Property Pages should return FALSE
	}
};

