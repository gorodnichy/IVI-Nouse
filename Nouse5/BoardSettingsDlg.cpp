// CBoardSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "BoardSettingsDlg.h"
#include "Nouse5.h"
#include "NouseSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoardSettingsDlg dialog


CBoardSettingsDlg::CBoardSettingsDlg(CWnd* pParent /*=NULL*/)
	: CSettingsTabDlg()//	(CBoardSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBoardSettingsDlg)
	m_strText_Size_Scale = "0";
	m_strBoard_Text_Scale = "0";
	m_nCurrent_Level = 0;//not save in a file - always default
	m_bCursor_Inboard = FALSE;
	m_nJitter_Threshhold = 1;
//	m_nouseControl.m_nPointingCorner = 0;

	//}}AFX_DATA_INIT
}


void CBoardSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoardSettingsDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_TEXT_SIZE_SCALE_EDIT, m_strText_Size_Scale);
	DDX_Text(pDX, IDC_BOARD_TEXT_SCALE_EDIT, m_strBoard_Text_Scale);
	DDX_CBIndex(pDX, IDC_CURRENT_LEVEL_COMBO, m_nCurrent_Level);
	DDX_Check(pDX, IDC_NOUSE_CURSOR_INBOARD_CHECK, m_bCursor_Inboard);
	DDX_CBIndex(pDX, IDC_JITTER_THRESHOLD_COMBO, m_nJitter_Threshhold);
//	DDX_Text(pDX, IDC_EDIT_GRID_1, strGrid_1);
}


BEGIN_MESSAGE_MAP(CBoardSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CBoardSettingsDlg)
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_CURRENT_LEVEL_COMBO, &CBoardSettingsDlg::OnSelchangeCurrentLevelCombo)
	ON_BN_CLICKED(IDC_LOAD_BOARD_BUTTON, &CBoardSettingsDlg::OnClickedLoadBoardButton)
	ON_BN_CLICKED(IDC_SAVE_BOARD_BUTTON, &CBoardSettingsDlg::OnClickedSaveBoardButton)
	ON_EN_UPDATE(IDC_EDIT_GRID_1_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_1_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_1_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_1_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_2_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_2_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_2_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_2_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_3_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_3_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_3_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_3_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_4_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_4_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_4_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_4_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_5_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_5_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_5_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_5_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_6_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_6_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_6_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_6_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_7_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_7_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_7_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_7_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_8_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_8_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_8_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_8_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_9_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_9_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_9_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_9_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_10_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_10_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_10_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_10_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_11_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_11_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_11_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_11_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_12_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_12_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_12_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_12_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_13_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_13_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_13_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_13_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_14_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_14_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_14_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_14_5, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_15_1, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_15_2, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_15_4, &CBoardSettingsDlg::OnUpdateEditGrid)
	ON_EN_UPDATE(IDC_EDIT_GRID_15_5, &CBoardSettingsDlg::OnUpdateEditGrid)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoardSettingsDlg message handlers
BOOL CBoardSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CBoardSettingsDlg::GetData(CSettingsHandler* p_SettingsHandler)
{
	UpdateData();
	p_SettingsHandler->m_stateCursor.m_nousePad.m_dTextSizeScale = _ttof(m_strText_Size_Scale);
	p_SettingsHandler->m_stateCursor.m_nouseBoard.m_dTextSizeScale = _ttof(m_strBoard_Text_Scale);
	p_SettingsHandler->m_stateCursor.m_bNouseCursorInBoard = (m_bCursor_Inboard == TRUE ? true : false);
	p_SettingsHandler->m_stateCursor.m_nouseBoard.m_nJitterThreshold = m_nJitter_Threshhold;
	//the Board changes are already saved directly into the settings handler 

}
void CBoardSettingsDlg::SetData(CSettingsHandler* p_SettingsHandler)
{
	m_strText_Size_Scale.Format(_T("%d"),p_SettingsHandler->m_stateCursor.m_nousePad.m_dTextSizeScale);
	m_strBoard_Text_Scale.Format(_T("%d"), p_SettingsHandler->m_stateCursor.m_nouseBoard.m_dTextSizeScale);
	m_bCursor_Inboard = p_SettingsHandler->m_stateCursor.m_bNouseCursorInBoard;
	m_nJitter_Threshhold = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_nJitterThreshold;

	SetBoardData(p_SettingsHandler);
	UpdateData();

	UpdateData();

}

void  CBoardSettingsDlg::SetBoardData(CSettingsHandler* p_SettingsHandler, int nLevel/* = 0*/)
{
	CString strGrid;
	int nItem = IDC_EDIT_GRID_1_1;
	//fill in cell using CEdit boxes IDS - must be in the consequentual order in "Resource.h"
	for (int row = 0; row <NUMBER_OF_ROWS; ++row)
	{ 
		for (int col = 0; col <NUMBER_OF_COLS; ++col)// do the square
		{							
			if(nLevel == 0 )
			{ 
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT - 1].szNormalText;//b
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT - 1].szNormalText;//a
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				//center - just a reference for the nouse
				strGrid = "*";
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT - 1].szNormalText;//d
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT - 1].szNormalText;//c
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
						
			}
			else if (nLevel == 1)
			{
			
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT - 1].szShiftText;//b
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT - 1].szShiftText;//a
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = "*";
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT - 1].szShiftText;//d
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT - 1].szShiftText;//c
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				
			}
			else
			{
				
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT - 1].szAdvText;//b
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT - 1].szAdvText;//a
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = "*";
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT - 1].szAdvText;//d
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				strGrid = p_SettingsHandler->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT - 1].szAdvText;//c
				GetDlgItem(nItem)->SetWindowText((LPCTSTR)strGrid);
				nItem++;
				
			}
				
		
		}
	}
}

void CBoardSettingsDlg::OnSelchangeCurrentLevelCombo()
{
	UpdateData();
	CNouseSettingsDlg* pParentWnd = (CNouseSettingsDlg*)GetParent();
	SetBoardData(pParentWnd->GetSettingsHandler(), m_nCurrent_Level);
}


void  CBoardSettingsDlg::GetBoardData(CSettingsHandler* p_SettingsHandler, int nLevel/* = 0*/)
{
/*	CString strGrid;
	int nItem = IDC_EDIT_GRID_1_1;
	CEdit *pEditGrid;
	//fill in cell using CEdit boxes IDS - must be in the consequentual order in "Resource.h"
	for (int row = 0; row <NUMBER_OF_ROWS; ++row)
	{
		for (int col = 0; col <NUMBER_OF_COLS; ++col)// do the square
		{
			
		}
	}*/
}


void CBoardSettingsDlg::OnClickedLoadBoardButton()
{
	// szFilters is a text string that includes two file name filters:
	// "*.board" for "Nouse board Files"
	TCHAR szFilters[] = _T("Nouse Board files (*.board)|*.board|");

	// Create an Open dialog; the default file name extension is ".board".
	CFileDialog fileDlg(TRUE, _T("board"), _T("*.board"),
		OFN_FILEMUSTEXIST, szFilters);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if (fileDlg.DoModal() == IDOK)
	{
		CNouseSettingsDlg* pParentWnd = (CNouseSettingsDlg*)GetParent();
		CSettingsHandler* p_SettingsHandler = pParentWnd->GetSettingsHandler();
		p_SettingsHandler->loadBoardFile(fileDlg.GetPathName());
		SetBoardData(p_SettingsHandler, m_nCurrent_Level);
		UpdateData();

	}

}


void CBoardSettingsDlg::OnClickedSaveBoardButton()
{
	// szFilters is a text string that includes two file name filters:
	// "*.board" for "Nouse board Files".
	TCHAR szFilters[] = _T("Nouse Board files (*.board)|*.board|");

	// Create a Save dialog; the default file name extension is ".board".
	CFileDialog fileDlg(FALSE, _T("board"), _T("*.board"),
		OFN_FILEMUSTEXIST, szFilters);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if (fileDlg.DoModal() == IDOK)
	{
		UpdateData();
		CNouseSettingsDlg* pParentWnd = (CNouseSettingsDlg*)GetParent();
		CSettingsHandler* p_SettingsHandler = pParentWnd->GetSettingsHandler();
		GetData(p_SettingsHandler);
		p_SettingsHandler->saveBoardFile(fileDlg.GetPathName());
	}
}


void CBoardSettingsDlg::OnUpdateEditGrid()
{
	//Because only the third of the Board is visible and avialabe tot he user
	//we need to save the changes right away into the settings
	CString strGrid;
	CEdit* pEditGrid = (CEdit*)GetFocus();
	UINT nId = pEditGrid->GetDlgCtrlID() - IDC_EDIT_GRID_1_1;
	if (nId > 75)// if not the proper edit box
		return;

	pEditGrid->GetWindowText(strGrid);

	CNouseSettingsDlg* pParentWnd = (CNouseSettingsDlg*)GetParent();

	int nRow = nId / 25;
	int nCol = (nId / 5) % 5;
	
	int nIndex = nId % 5;
	
	//int row = (nIndex < 5) ? 0 : 1;
	//int nCol = (nIndex > 3) ? nIndex - 1 : nIndex;//ajust for the empty center

	pParentWnd->GetSettingsHandler()->setBoardText(strGrid, m_nCurrent_Level, nRow, nCol, ((nIndex > 2) ? nIndex - 1 : nIndex));
	/*
	if (m_nCurrent_Level == 0)
	{
		strcpy(pParentWnd->GetSettingsHandler()->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[nIndex + 1].szNormalText, (LPCSTR)(CStringA)strGrid);
	}
	else if (m_nCurrent_Level == 1)
	{
		strcpy(pParentWnd->GetSettingsHandler()->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[nIndex + 1].szShiftText, (LPCSTR)(CStringA)strGrid);
	}
	else
	{
		strcpy(pParentWnd->GetSettingsHandler()->m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[nIndex + 1].szAdvText, (LPCSTR)(CStringA)strGrid);
	}*/	
	// TODO:  Add your control notification handler code here
}
