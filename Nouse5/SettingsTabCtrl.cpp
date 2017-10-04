// CSettingsTabCtrl.cpp : implementation file
//

#include "stdafx.h"
NouseSettings
#include "SettingsTabCtrl.h"
#include "ControlSettingsDlg.h"
#include "VisualSettingsDlg.h"
#include "BoardSettingsDlg.h"
#include "BasicSettingsDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsTabCtrl

CSettingsTabCtrl::CSettingsTabCtrl()
{
	m_DialogID[0] = IDD_BASIC_SETTINGS_DLG;
	m_DialogID[1] =IDD_DIALOG1;
	m_DialogID[2] =IDD_DIALOG2;
	m_DialogID[3] = IDD_DIALOG3;

	m_Dialog[0] = new CBasicSettingsDlg();
	m_Dialog[1] = new CControlSettingsDlg();
	m_Dialog[2] = new CVisualSettingsDlg();
	m_Dialog[3] = new CBoardSettingsDlg();


}

CSettingsTabCtrl::~CSettingsTabCtrl()
{
	for (int nIndex = 0; nIndex < m_nPageCount; nIndex++)
	{
		if (m_Dialog[nIndex])
			delete m_Dialog[nIndex];
	}
}

void CSettingsTabCtrl::InitDialogs()
{
	for (int nIndex = 0; nIndex < m_nPageCount; nIndex++)
	{
		m_Dialog[nIndex]->Create(m_DialogID[nIndex], GetParent());
	}

}

BEGIN_MESSAGE_MAP(CSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CSettingsTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsTabCtrl message handlers

void CSettingsTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ActivateTabDialogs();
	*pResult = 0;
}


void CSettingsTabCtrl::UpdateItems(CSettingsHandler* p_SettingsHandler /* =NULL*/, bool bSet/* = true*/)
{
	
	if (bSet)
	{
		for (int nIndex = 0; nIndex < m_nPageCount; nIndex++)
		{
			m_Dialog[nIndex]->SetData(p_SettingsHandler);
		}
	}
	else
	{
		for (int nIndex = 0; nIndex < m_nPageCount; nIndex++)
		{
			m_Dialog[nIndex]->GetData(p_SettingsHandler);
		}
	}
		
}

void CSettingsTabCtrl::ActivateTabDialogs()
{
	
	int nSel = GetCurSel();
	if (nSel < 0)
		nSel = 0;

	if(m_Dialog[nSel]->m_hWnd)
		m_Dialog[nSel]->ShowWindow(SW_HIDE);

	CRect l_rectClient;
	CRect l_rectWnd;

	GetClientRect(l_rectClient);
	AdjustRect(FALSE,l_rectClient);
	GetWindowRect(l_rectWnd);
	GetParent()->ScreenToClient(l_rectWnd);
	l_rectClient.OffsetRect(l_rectWnd.left,l_rectWnd.top);
	for(int nIndex =0; nIndex < m_nPageCount; nIndex++){
		m_Dialog[nIndex]->SetWindowPos(&wndTop, l_rectClient.left,l_rectClient.top,l_rectClient.Width(),l_rectClient.Height(),SWP_HIDEWINDOW);
	}
	m_Dialog[nSel]->SetWindowPos(&wndTop,l_rectClient.left,l_rectClient.top,l_rectClient.Width(),l_rectClient.Height(),SWP_SHOWWINDOW);

	m_Dialog[nSel]->ShowWindow(SW_SHOW);
}
