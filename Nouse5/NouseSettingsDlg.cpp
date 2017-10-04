#include "stdafx.h"
#include "NouseSettingsDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*CNouseSettingsDlg::CNouseSettingsDlg(CWnd* pParent = NULL, CStateCursor* p_stateCursor = NULL)
	: CDialog(CNouseSettingsDlg::IDD, pParent)
{
}*/
/////////////////////////////////////////////////////////////////////////////
// CNouseSettingsDlg dialog

CNouseSettingsDlg::CNouseSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNouseSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNouseSettingsDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CNouseSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNouseSettingsDlg)
	DDX_Control(pDX, IDC_TAB, m_tabCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNouseSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CNouseSettingsDlg)
	ON_BN_CLICKED(IDOK, &CNouseSettingsDlg::OnClickedSaveSettingsButton)
	ON_BN_CLICKED(IDCANCEL, &CNouseSettingsDlg::OnClickedExitButton)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNouseSettingsDlg message handlers

BOOL CNouseSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_SettingsHandler.updateFromFile();
	m_tabCtrl.InitDialogs();
	m_tabCtrl.UpdateItems(&m_SettingsHandler);
	
	m_tabCtrl.InsertItem(0, _T("Basic Control Settings"));
	m_tabCtrl.InsertItem(1, _T("Advanced Control Settings"));
	m_tabCtrl.InsertItem(2, _T("Visual Settings"));
	m_tabCtrl.InsertItem(3, _T("Board Settings"));
		
	m_tabCtrl.ActivateTabDialogs();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNouseSettingsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
		CDialog::OnSysCommand(nID, lParam);

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNouseSettingsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNouseSettingsDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}
// CBasicSettingsDlg message handlers
void CNouseSettingsDlg::OnClickedExitButton()
{
	CDialog::OnCancel();
}

void CNouseSettingsDlg::OnClickedSaveSettingsButton()
{
	m_tabCtrl.UpdateItems(&m_SettingsHandler, false);// retrieve date from the tab pages
	m_SettingsHandler.writeToFile();
}