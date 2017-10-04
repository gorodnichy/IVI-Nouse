#pragma once

	// CNouseSettingsDlg dialog
	
	//
#include "SettingsTabCtrl.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

	/////////////////////////////////////////////////////////////////////////////
	// CNouseSettingsDlg dialog

class CNouseSettingsDlg : public CDialog
{
	// Construction
public:
	CNouseSettingsDlg(CWnd* pParent = NULL);	// standard constructor

											//	MyTabCtrl m_tbCtrl;

											// Dialog Data
											//{{AFX_DATA(CNouseSettingsDlg)
	enum { IDD = IDD_NOUSE_SETTINGS_DLG};
	CSettingsHandler* GetSettingsHandler() { return &m_SettingsHandler; }
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNouseSettingsDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
														//}}AFX_VIRTUA
														// Implementation
protected:
	HICON m_hIcon;
	CSettingsHandler m_SettingsHandler;
	CSettingsTabCtrl m_tabCtrl;
	// Generated message map functions
	//{{AFX_MSG(CNouseSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		afx_msg void OnClickedSaveSettingsButton();
		afx_msg void OnClickedExitButton();
public:
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedApply();
};
