#pragma once


// CDwellDialog dialog

class CDwellDialog : public CDialog
{
	DECLARE_DYNAMIC(CDwellDialog)

public:
	CDwellDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDwellDialog();

// Dialog Data
	enum { IDD = 129/*IDD_DIALOG_DWELL*/ };
	int		m_nClickType;

	CButton m_btnLeftClick;
	CButton m_btnRightClick;
	CButton m_btnDoubleClick;
	CButton m_btnDrag;
	CString m_strDwellDialogTitle;
	CString m_strLeftClick;
	CString m_strRightClick;
	CString m_strDoubleClick;
	CString m_strDrag;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
