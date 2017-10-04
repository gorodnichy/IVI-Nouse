// NousePad.cpp : implementation file
//

#include "stdafx.h"
#include "Nouse5.h"
#include "NousePad.h"

// CNousePad dialog

IMPLEMENT_DYNAMIC(CNousePad, CDialog)

CNousePad::CNousePad(CWnd* pParent /*=NULL*/)
	: CDialog(CNousePad::IDD, pParent)
{

	m_strText = _T("");
}

CNousePad::~CNousePad()
{
}

void CNousePad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strText);
}


BEGIN_MESSAGE_MAP(CNousePad, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CNousePad message handlers
BOOL CNousePad::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//setLocationUnderBoard();
	PVI_POINT ptScreenSize = pvu::getScreenSize();
	WINDOWPLACEMENT windowPlacement;
	GetWindowPlacement(&windowPlacement);
	windowPlacement.rcNormalPosition.left = ((1-PAD_WIDTH_PCT_OF_SCREEN) / 2) * ptScreenSize.x;
	windowPlacement.rcNormalPosition.top = PAD_TOP_PCT_OF_SCREEN * ptScreenSize.y;
	windowPlacement.rcNormalPosition.right = windowPlacement.rcNormalPosition.left + PAD_WIDTH_PCT_OF_SCREEN * ptScreenSize.x;
	windowPlacement.rcNormalPosition.bottom = windowPlacement.rcNormalPosition.top + PAD_HEIGHT_PCT_OF_SCREEN * ptScreenSize.y;
	SetWindowPlacement(&windowPlacement);

	// Set font, -removed by huiqiong. the font is not good for display. the blow half of any character is always cut
	CFont* pFont = GetDlgItem(IDC_EDIT1)->GetFont();
	if (pFont) {
		LOGFONT log;
		pFont->GetLogFont(&log);
		log.lfHeight = (int) (m_dTextSizeScale*10);
		pFont->Detach();  
		pFont->CreateFontIndirect(&log);
		GetDlgItem(IDC_EDIT1)->SetFont(pFont);
	   pFont->Detach();  
	}

	clear();

	SetWindowText(m_strNousepadDialogTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
void CNousePad::setLocationUnderBoard() {
	WINDOWPLACEMENT windowPlacement;
	GetWindowPlacement(&windowPlacement);
	
	int height = int((windowPlacement.rcNormalPosition.bottom - windowPlacement.rcNormalPosition.top));// * m_fPadHeightScale);
	int width = int((windowPlacement.rcNormalPosition.right - windowPlacement.rcNormalPosition.left));// * m_fPadWidthScale);
	
	windowPlacement.rcNormalPosition.top = (int)m_rectBoard.getBottom() + 40;
	windowPlacement.rcNormalPosition.bottom = windowPlacement.rcNormalPosition.top + height;
	windowPlacement.rcNormalPosition.left = (int)m_rectBoard.c.x - width/2;
	windowPlacement.rcNormalPosition.right = windowPlacement.rcNormalPosition.left + width;

	SetWindowPlacement(&windowPlacement);
}
*/

void CNousePad::deleteLastWord()
{
	UpdateData(TRUE);
	
	int nLength = m_strText.GetLength();
	bool bSpaceAtEnd = m_strText[nLength-1]==' ';
	
	if(bSpaceAtEnd)
		m_strText.SetAt(nLength-1, '\0');
	int nLastSpaceIndex = m_strText.ReverseFind(' ');
	if(nLastSpaceIndex > -1) {
		m_strText.SetAt((bSpaceAtEnd)?nLastSpaceIndex+1:nLastSpaceIndex, '\0');
	} else {
		m_strText = "";
	}
	
	UpdateData(FALSE);
}

void CNousePad::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_EDIT1);
	if (pWnd)
	pWnd->MoveWindow(0, 0, cx, cy, TRUE);
}

void CNousePad::clear()
{
	m_strText = "";
	UpdateData(FALSE);
}

void CNousePad::copyAndClose()
{
	UpdateData(TRUE);
	
	CStringA strTextA(m_strText);

	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, m_strText.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, strTextA);
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}

	DestroyWindow();
}