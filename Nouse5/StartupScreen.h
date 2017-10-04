#pragma once
#include "afxwin.h"
#include "RegistrationHandler.h"


class CStartupScreen :
	public CDialog
{
public:
	CStartupScreen(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStartupScreen();


	// Dialog Data
	enum { IDD = IDD_FORMVIEW};
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CRegistrationHandler m_RegHdl;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClickedButtonBuy();
	afx_msg void OnClickedButtonTrial();

private:
	CBitmap m_picNouse, m_picTrial;
	CEdit m_ediEmail;
	CEdit m_ediKey;
	bool m_bTrialExpired;

public:
	afx_msg void OnEnChangeEditEmail();
	afx_msg void OnEnChangeEditKey();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnUpdateEditEmail();
	afx_msg void OnBnClickedButtonRegister();
};

