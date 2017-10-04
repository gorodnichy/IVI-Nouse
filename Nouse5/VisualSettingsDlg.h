#if !defined(AFX_CVisualSettingsDlg_H__2A26492C_16F2_4C10_9653_6F4942F027CC__INCLUDED_)
#define AFX_CVisualSettingsDlg_H__2A26492C_16F2_4C10_9653_6F4942F027CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CVisualSettingsDlg.h : header file
//
#include "SettingsTabDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CVisualSettingsDlg dialog

class CVisualSettingsDlg : public CSettingsTabDlg
{
// Construction
public:
	CVisualSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVisualSettingsDlg)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	virtual void GetData(CSettingsHandler* p_SettingsHandler);
	virtual void SetData(CSettingsHandler* p_SettingsHandler);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CVisualSettingsDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bMirrorImage_Check;
	BOOL m_bCursor_Count;
	BOOL m_bCursorFace;
	BOOL m_bTranslucent_Cursor;
	CSliderCtrl m_sldrProcess_Load;
	int m_nFace_Detection_Type;
	CString m_strTranslucen_Edit;
	CString m_strWebcam_Index;
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnReleasedcaptureProcessLoadSlider(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVisualSettingsDlg_H__2A26492C_16F2_4C10_9653_6F4942F027CC__INCLUDED_)
