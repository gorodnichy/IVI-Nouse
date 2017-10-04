// CVisualSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NouseSettings.h"
#include "VisualSettingsDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisualSettingsDlg dialog


CVisualSettingsDlg::CVisualSettingsDlg(CWnd* pParent /*=NULL*/)
	: CSettingsTabDlg()//(CVisualSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVisualSettingsDlg)
	m_bMirrorImage_Check = FALSE;
	m_bCursor_Count = TRUE;
	m_bCursorFace = TRUE;
	m_bTranslucent_Cursor = TRUE;
	m_nFace_Detection_Type = 0;
	m_strTranslucen_Edit = "140";
	m_strWebcam_Index = "1";

	//}}AFX_DATA_INIT
}


void CVisualSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisualSettingsDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_MIRROR_CAMERA_IMAGE_CHK, m_bMirrorImage_Check);
	DDX_Check(pDX, IDC_CURSOR_SHOWS_COUNTDOWN_CHK, m_bCursor_Count);
	DDX_Check(pDX, IDC_CURSOR_SHOWS_FACE_CHK, m_bCursorFace);
	DDX_Check(pDX, IDC_TRANSLUCENT_CURSOR_CHK, m_bTranslucent_Cursor);
	DDX_Control(pDX, IDC_PROCESS_LOAD_SLIDER, m_sldrProcess_Load);
	DDX_CBIndex(pDX, IDC_FACE_DETECTION_TYPE_COMBO, m_nFace_Detection_Type);
	DDX_Text(pDX, IDC_TRANSLUCENCE_EDIT, m_strTranslucen_Edit);
	DDX_Text(pDX, IDC_WEBCAM_INDEX_EDIT, m_strWebcam_Index);

};


BEGIN_MESSAGE_MAP(CVisualSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CVisualSettingsDlg)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PROCESS_LOAD_SLIDER, &CVisualSettingsDlg::OnReleasedcaptureProcessLoadSlider)
	ON_EN_UPDATE(IDC_TRANSLUCENCE_EDIT, &CVisualSettingsDlg::OnUpdateTranslucentEdit)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualSettingsDlg message handlers

void CVisualSettingsDlg::OnOK() 
{
	// TODO: Add extra validation here
	
}

void CVisualSettingsDlg::SetData(CSettingsHandler* p_SettingsHandler)
{
	if (!p_SettingsHandler)
		return;
	m_sldrProcess_Load.SetPos(p_SettingsHandler->m_nProcessLoad);
	m_strTranslucen_Edit.Format(_T("%i"), p_SettingsHandler->m_nTranslucentSolidness);
	m_strWebcam_Index.Format(_T("%i"), p_SettingsHandler->m_iWebcamIndex);
	m_bMirrorImage_Check = p_SettingsHandler->m_bMirrorCameraImage;
	m_bCursor_Count = p_SettingsHandler->m_bCursorShowsCountdown;
	m_bCursorFace = p_SettingsHandler->m_stateReady.m_bActWithFaceDetection;
	m_bTranslucent_Cursor = p_SettingsHandler->m_bUseTranslucentCursor;
	m_nFace_Detection_Type = p_SettingsHandler->m_stateReady.m_nFaceDetectionType;
		
	UpdateData(FALSE);

}

void CVisualSettingsDlg::GetData(CSettingsHandler* p_SettingsHandler)
{
	if (!p_SettingsHandler)
		return;
	UpdateData(TRUE);
	p_SettingsHandler->m_bMirrorCameraImage = (m_bMirrorImage_Check == TRUE ? true : false);
	p_SettingsHandler->m_bCursorShowsCountdown = (m_bCursor_Count == TRUE ? true : false);
	p_SettingsHandler->m_stateReady.m_bActWithFaceDetection = (m_bCursorFace == TRUE ? true : false); 
	p_SettingsHandler->m_bUseTranslucentCursor = (m_bTranslucent_Cursor == TRUE ? true : false);
	p_SettingsHandler->m_nProcessLoad = m_sldrProcess_Load.GetPos();
	p_SettingsHandler->m_stateReady.m_nFaceDetectionType = m_nFace_Detection_Type;
	p_SettingsHandler->m_nTranslucentSolidness = _ttoi(m_strTranslucen_Edit);
	p_SettingsHandler->m_iWebcamIndex = _ttoi(m_strWebcam_Index);
	p_SettingsHandler->m_nProcessLoad = m_sldrProcess_Load.GetPos();
}

BOOL CVisualSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (!m_ToolTip)
		m_ToolTip.Create(this);

	m_sldrProcess_Load.SetRange(1, 3);
	CEdit* pNumericText = (CEdit*)GetDlgItem(IDC_TRANSLUCENCE_EDIT);
	pNumericText->SetLimitText(3);
	m_ToolTip.AddTool(pNumericText, TRANSLUCENCE_SOLIDNESS_TOOL_TIP);

	pNumericText = (CEdit*)GetDlgItem(IDC_WEBCAM_INDEX_EDIT);
	pNumericText->SetLimitText(3);

	m_ToolTip.AddTool(GetDlgItem(IDC_TRANSLUCENT_CURSOR_CHK), TRANSLUCENT_CURSOR_TOOL_TIP);
	
	pNumericText = NULL;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CVisualSettingsDlg::OnReleasedcaptureProcessLoadSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
}

void CVisualSettingsDlg::OnUpdateTranslucentEdit()
{
	CEdit* pNumericText = (CEdit*)GetDlgItem(IDC_TRANSLUCENCE_EDIT);
	pNumericText->GetWindowText(m_strTranslucen_Edit);

	int nTranslucent = _ttoi(m_strTranslucen_Edit);
	if (nTranslucent > 255 )
	{
		nTranslucent = 140;
		m_strTranslucen_Edit.Format(_T("%i"), nTranslucent);
		pNumericText->SetWindowText(m_strTranslucen_Edit);
	}

}
