#if !defined(AFX_MYDLG1_H__AC00C759_8BAC_44D1_9D3D_CBD118D24C11__INCLUDED_)
#define AFX_MYDLG1_H__AC00C759_8BAC_44D1_9D3D_CBD118D24C11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SettingsTabDlg.h"
// CControlSettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CControlSettingsDlg dialog

class CControlSettingsDlg : public 	CSettingsTabDlg

{
// Construction
public:
	CControlSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CControlSettingsDlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	virtual void GetData(CSettingsHandler* p_SettingsHandler);
	virtual void SetData(CSettingsHandler* p_SettingsHandler);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CControlSettingsDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUpdateActiveHeadwidth();
public:
//	afx_msg void OnBnClickedCheck1();
private:
	CString m_strActive_Headwidth;
	BOOL m_bAlways_Left_Click;
	BOOL m_bMotion_Calibr_Check;
	CString m_strBig_Motion_Size;
	CSliderCtrl m_sldr_Box_size;
	BOOL m_bCalibr_Automatically;
	BOOL m_bClick_On_Command;
	int m_nCursor_Relative_Location;
	CSliderCtrl m_sldrCoundown_Calibration;
	CSliderCtrl m_sldrCountdown_Click;
	int m_nDiscrete_Direction;
	BOOL m_bEnable_Dwell_Click;
	CString m_strJoystick_Neutral_Zone;
	BOOL m_bLag;
	CSliderCtrl m_sldrMax_Mouth_Click;
	CString m_strNo_Changeback_Seconds;
	CString m_strNo_Motion_Back;
	BOOL m_bUse_Mouth_Click;
	BOOL m_bUse_Voice_Commands;
public:
	virtual BOOL OnInitDialog();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLG1_H__AC00C759_8BAC_44D1_9D3D_CBD118D24C11__INCLUDED_)
