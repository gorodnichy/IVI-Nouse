#include "stdafx.h"
#include "Nouse5.h"

// regex_match example
#include <iostream>
#include <string>
#include <regex>
#include "StartupScreen.h"


CStartupScreen::CStartupScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CStartupScreen::IDD, pParent)

{

}


CStartupScreen::~CStartupScreen()
{
	DestroyWindow();
}

BOOL CStartupScreen::OnInitDialog() {

	CenterWindow(GetParent());
	m_picNouse.LoadBitmap(IDB_BITMAP_LOGO);
	m_picTrial.LoadBitmap(IDB_BITMAP_TRIAL);

	
	CString m_versionString; 
	m_bTrialExpired = m_RegHdl.CheckVersion(&m_versionString);
	if (m_bTrialExpired)
	{
		CStatic* pIcon = (CStatic*)GetDlgItem(IDC_SPLASH_PIC);
		pIcon->SetBitmap(m_picTrial);

	//	GetDlgItem(IDC_BUTTON_TRIAL)->SetWindowText(_T("Trial is about to end"));

	}
	CStatic * pInfo = (CStatic*)GetDlgItem(IDC_STATIC_INFO);

	/*CDC* pcDC = GetDC();
	HDC hDC = pcDC->GetSafeHdc();
	RECT Rect;
	pInfo->GetWindowRect(&Rect);
	pcDC->DrawText(m_versionString, &Rect, DT_VCENTER | DT_CENTER | DT_CALCRECT | SS_ENDELLIPSIS | SS_PATHELLIPSIS);
	DrawText(hDC, m_versionString, m_versionString.GetLength(), &Rect, DT_VCENTER | DT_CENTER | DT_CALCRECT | SS_ENDELLIPSIS | SS_PATHELLIPSIS); */
	pInfo->ModifyStyle(0, DT_CENTER| SS_EDITCONTROL | SS_ENDELLIPSIS | SS_PATHELLIPSIS);
	
	pInfo->SetWindowText(m_versionString);

	return TRUE;
}

void CStartupScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_EMAIL, m_ediEmail);
	//DDX_Control(pDX, IDC_EDIT_KEY, m_ediKey);
}


BEGIN_MESSAGE_MAP(CStartupScreen, CDialog)
ON_BN_CLICKED(IDC_BUTTON_TRIAL, &CStartupScreen::OnClickedButtonTrial)
ON_EN_CHANGE(IDC_EDIT_EMAIL, &CStartupScreen::OnEnChangeEditEmail)
ON_EN_CHANGE(IDC_EDIT_KEY, &CStartupScreen::OnEnChangeEditKey)
ON_BN_CLICKED(IDCANCEL_NOUSE, &CStartupScreen::OnBnClickedCancel)
ON_EN_UPDATE(IDC_EDIT_EMAIL, &CStartupScreen::OnUpdateEditEmail)
ON_BN_CLICKED(IDC_BUTTON_BUY2, &CStartupScreen::OnClickedButtonBuy)
ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CStartupScreen::OnBnClickedButtonRegister)
END_MESSAGE_MAP()



void CStartupScreen::OnBnClickedButtonRegister()
{
	CString strEmail, strKey;
	GetDlgItemText(IDC_EDIT_EMAIL, strEmail);
	GetDlgItemText(IDC_EDIT_KEY, strKey);


	std::string s = CW2A(strEmail);
	//check email for malformation
	std::string CHA = "^([\\w-]+(?:\\.[\\w-]+)*)@((?:[\\w-]+\\.)*\\w[\\w-]{0,66})\\.([A-Za-z]{2,6}(?:\\.[A-Za-z]{2,6})?)$";
	if (!std::regex_match(s, std::regex(CHA)))
	{
		strEmail = "Invalid e-mail";
		strKey = "Nouse Registration Failure";
		MessageBox(strEmail, strKey, MB_OK | MB_ICONEXCLAMATION);
		GetDlgItem(IDC_EDIT_EMAIL)->SetFocus();
		return;
	}
	
	if (!m_RegHdl.handleActivationKey(strEmail, strKey))
	{
		strEmail = "E-mail and Product key do not match!";
		strKey = "Nouse Registration Failure";
		MessageBox(strEmail, strKey, MB_OK| MB_ICONEXCLAMATION);
		return;
	}
	OnOK();

}

void CStartupScreen::OnClickedButtonTrial()
{
	if(m_bTrialExpired)
		EndDialog(IDNO);
	else
		EndDialog(IDOK);// if not expired - still ok to use
}


void CStartupScreen::OnEnChangeEditEmail()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO:  Add your control notification handler code here
}


void CStartupScreen::OnEnChangeEditKey()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CStartupScreen::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}


void CStartupScreen::OnUpdateEditEmail()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}

void CStartupScreen::OnClickedButtonBuy()
{
	ShellExecute(0, 0, L"http://nouse.ca/purchase.php", 0, 0, SW_SHOW);
}



