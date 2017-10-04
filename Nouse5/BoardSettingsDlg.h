
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoardSettingsDlg.h : header file
//

#include "SettingsTabDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CBoardSettingsDlg dialog

class CBoardSettingsDlg : public CSettingsTabDlg
{
// Construction
public:
	CBoardSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBoardSettingsDlg)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	virtual void GetData(CSettingsHandler* p_SettingsHandler);
	virtual void SetData(CSettingsHandler* p_SettingsHandler);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoardSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	CNouseBoard m_nouseBoard;
//	CNousePad m_nousePad;
	// Generated message map functions
	//{{AFX_MSG(CBoardSettingsDlg)
	
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
protected:
	void SetBoardData(CSettingsHandler* p_SettingsHandler, int nLevel = 0);
	void GetBoardData(CSettingsHandler* p_SettingsHandler, int nLevel = 0);
public:
	
private:
	CString m_strText_Size_Scale;
	CString  m_strBoard_Text_Scale;
	int m_nCurrent_Level;
	BOOL m_bCursor_Inboard;
	int m_nJitter_Threshhold;
	CString m_strGrid[75];
public:
	afx_msg void OnSelchangeCurrentLevelCombo();
	afx_msg void OnClickedLoadBoardButton();
	afx_msg void OnClickedSaveBoardButton();
	afx_msg void OnUpdateEditGrid();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

