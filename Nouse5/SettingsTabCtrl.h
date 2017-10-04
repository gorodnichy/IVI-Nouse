#if !defined(AFX_CSettingsTabCtrl_H__BAF69081_1BBC_476D_A303_7660CCB9A9B7__INCLUDED_)
#define AFX_CSettingsTabCtrl_H__BAF69081_1BBC_476D_A303_7660CCB9A9B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CSettingsTabCtrl.h : header file
//
#define TABS_NUMBER 4
#include "SettingsTabDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CSettingsTabCtrl window

class CSettingsTabCtrl : public CTabCtrl
{
// Construction
public:
	CSettingsTabCtrl();

// Attributes
public:
	int m_DialogID[TABS_NUMBER];
	CSettingsTabDlg *m_Dialog[TABS_NUMBER];
	
	int m_nPageCount = TABS_NUMBER;

	void ActivateTabDialogs();
	void UpdateItems(CSettingsHandler* p_SettingsHandler = NULL, bool bSet = true);
	void InitDialogs();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSettingsTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSettingsTabCtrl)
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSettingsTabCtrl_H__BAF69081_1BBC_476D_A303_7660CCB9A9B7__INCLUDED_)
