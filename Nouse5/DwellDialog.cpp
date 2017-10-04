// DwellDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Nouse5.h"
#include "DwellDialog.h"

// CDwellDialog dialog

IMPLEMENT_DYNAMIC(CDwellDialog, CDialog)

CDwellDialog::CDwellDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDwellDialog::IDD, pParent)
{
	m_nClickType = 0;
}

CDwellDialog::~CDwellDialog()
{
}

void CDwellDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nClickType);
	DDX_Control(pDX, IDC_RADIO1, m_btnLeftClick);
	DDX_Control(pDX, IDC_RADIO2, m_btnRightClick);
	DDX_Control(pDX, IDC_RADIO3, m_btnDoubleClick);
	DDX_Control(pDX, IDC_RADIO4, m_btnDrag);
}


BEGIN_MESSAGE_MAP(CDwellDialog, CDialog)
END_MESSAGE_MAP()


// CDwellDialog message handlers
BOOL CDwellDialog::OnInitDialog() {
	BOOL toReturn = CDialog::OnInitDialog();
	SetWindowText(m_strDwellDialogTitle);
	m_btnLeftClick.SetWindowText(m_strLeftClick);
	m_btnRightClick.SetWindowText(m_strRightClick);
	m_btnDoubleClick.SetWindowText(m_strDoubleClick);
	m_btnDrag.SetWindowText(m_strDrag);
	return toReturn;
}