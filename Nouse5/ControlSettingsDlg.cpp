// CControlSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Nouse5.h"
#include "ControlSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlSettingsDlg dialog


CControlSettingsDlg::CControlSettingsDlg(CWnd* pParent /*=NULL*/)
	: CSettingsTabDlg()//CDialog(CControlSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlSettingsDlg)
	m_strActive_Headwidth = "0";
	m_bAlways_Left_Click = TRUE;
	m_bMotion_Calibr_Check = FALSE;
	m_strBig_Motion_Size = "0";
	m_bCalibr_Automatically = TRUE;
	m_bClick_On_Command = TRUE;
	m_nCursor_Relative_Location = TRUE;
	m_nDiscrete_Direction = TRUE;
	m_bEnable_Dwell_Click = TRUE;
	m_strJoystick_Neutral_Zone = "0";
	m_bLag = TRUE;
	m_strNo_Changeback_Seconds = "0";
	m_strNo_Motion_Back = "0";
	m_bUse_Mouth_Click = TRUE;
	m_bUse_Voice_Commands = FALSE;
	//}}AFX_DATA_INIT
}


void CControlSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlSettingsDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC__ACTIVATE_ASSUMES_HEADWIDTH_EDIT, m_strActive_Headwidth);
	DDX_Check(pDX, IDC_ALWAYS_LEFT_CLICK_CHECK, m_bAlways_Left_Click);
	DDX_Check(pDX, IDC_BIG_MOTION_CALIBRATION_CHECK, m_bMotion_Calibr_Check);
	DDX_Text(pDX, IDC_BIG_MOTION_SIZE_EDIT, m_strBig_Motion_Size);
	DDX_Control(pDX, IDC_BOX_SIZE_SLDR, m_sldr_Box_size);
	DDX_Check(pDX, IDC_CALIBRATE_AUTOMATICALLY_CHECK, m_bCalibr_Automatically);
	DDX_Check(pDX, IDC_CLICK_ON_COMMAND_CHECK, m_bClick_On_Command);
	DDX_CBIndex(pDX, IDC_COMBO_CURS_RELATIVE_LOCATION, m_nCursor_Relative_Location);
	DDX_Control(pDX, IDC_COUNTDOWN_CONFIRM_CALIBRATION_SLD, m_sldrCoundown_Calibration);
	DDX_Control(pDX, IDC_COUNTDOWN_CONFIRM_CLICK_SLD, m_sldrCountdown_Click);
	DDX_CBIndex(pDX, IDC_DISCRETE_DIRECTION_COMBO, m_nDiscrete_Direction);
	DDX_Check(pDX, IDC_ENABLE_DWELL_CLICKING_CHECK, m_bEnable_Dwell_Click);
	DDX_Text(pDX, IDC_JOYSTICK_NEUTRAL_ZONE_EDIT, m_strJoystick_Neutral_Zone);
	DDX_Check(pDX, IDC_LAG_CHECK, m_bLag);
	DDX_Control(pDX, IDC_MAXIMUM_MOUTH_CLICK_HIGHT_SLDR, m_sldrMax_Mouth_Click);
	DDX_Text(pDX, IDC_NO_CHANGEBACK_SECONDS_EDIT, m_strNo_Changeback_Seconds);
	DDX_Text(pDX, IDC_NO_MOTION_BACK_EDIT, m_strNo_Motion_Back);
	DDX_Check(pDX, IDC_USE_MOUTH_CLICK_CHECK, m_bUse_Mouth_Click);
	DDX_Check(pDX, IDC_USE_VOICE_COMMANDS_CHECK, m_bUse_Voice_Commands);
}


BEGIN_MESSAGE_MAP(CControlSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CControlSettingsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlSettingsDlg message handlers

void CControlSettingsDlg::OnOK() 
{
	// TODO: Add extra validation here
//	MessageBox("Tab 1");
	
}

void CControlSettingsDlg::SetData(CSettingsHandler* p_SettingsHandler)
{
	if (!p_SettingsHandler)
		return; 
	m_strActive_Headwidth.Format(_T("%d \n"), p_SettingsHandler->m_stateReady.m_dHeadWidth);
	m_bAlways_Left_Click = p_SettingsHandler->m_stateCursor.m_bAlwaysLeftClick;
	m_bMotion_Calibr_Check = p_SettingsHandler->m_stateCursor.m_bBigMotionDisabled;
	m_strBig_Motion_Size.Format(_T("%d \n"), p_SettingsHandler->m_stateCursor.m_nBigMotionPercentage);
	m_sldr_Box_size.SetPos(p_SettingsHandler->m_stateCursor.m_nClickBoxSize);
	m_bCalibr_Automatically = p_SettingsHandler->m_stateCalibration.m_bQuickCalibrate;
	m_bClick_On_Command = p_SettingsHandler->m_stateCursor.m_bClickOnCommand;
	m_nCursor_Relative_Location = p_SettingsHandler->m_stateCursor.m_nouseControl.m_ePointerLocation;
	m_sldrCoundown_Calibration.SetPos(p_SettingsHandler->m_stateCalibration.m_nCountCalibrateSelect);
	m_sldrCountdown_Click.SetPos(p_SettingsHandler->m_stateCursor.m_nCountDwell);
	m_nDiscrete_Direction = p_SettingsHandler->m_stateCursor.m_nouseControl.m_eDiscreteDirection;
	m_bEnable_Dwell_Click = p_SettingsHandler->m_stateCursor.m_bEnableDwellClicking;
	m_strJoystick_Neutral_Zone.Format(_T("%d \n"),p_SettingsHandler->m_stateCursor.m_nouseControl.m_nPctStopJoystick);
	m_bLag = p_SettingsHandler->m_stateCursor.m_bLag;
	m_sldrMax_Mouth_Click.SetPos(p_SettingsHandler->m_stateCursor.m_nMinimumMouthClickHeight);
	m_strNo_Changeback_Seconds.Format(_T("%d \n"), p_SettingsHandler->m_stateCursor.m_nTimeNochangeBackReset);
	m_strNo_Motion_Back.Format(_T("%d \n"), p_SettingsHandler->m_stateCursor.m_nTimeMotionBackReset);
	m_bUse_Mouth_Click = p_SettingsHandler->m_stateCursor.m_bUseMouthDetection;
	m_bUse_Voice_Commands = p_SettingsHandler->m_bUseVoiceCommands;

	UpdateData(TRUE);
}

void CControlSettingsDlg::GetData(CSettingsHandler* p_SettingsHandler)
{
	if (!p_SettingsHandler)
		return;
	UpdateData(TRUE);
	p_SettingsHandler->m_stateReady.m_dHeadWidth = _ttof(m_strActive_Headwidth);
	p_SettingsHandler->m_stateCursor.m_bAlwaysLeftClick = (m_bAlways_Left_Click == TRUE ? true : false);
	p_SettingsHandler->m_stateCursor.m_bBigMotionDisabled = (m_bMotion_Calibr_Check == TRUE ? true : false);
	p_SettingsHandler->m_stateCursor.m_nBigMotionPercentage = _ttoi(m_strBig_Motion_Size);
	p_SettingsHandler->m_stateCursor.m_nClickBoxSize = m_sldr_Box_size.GetPos();
	p_SettingsHandler->m_stateCalibration.m_bQuickCalibrate = (m_bCalibr_Automatically == TRUE ? true : false);
	p_SettingsHandler->m_stateCursor.m_bClickOnCommand = (m_bClick_On_Command == TRUE ? true : false);
	p_SettingsHandler->m_stateCursor.m_nouseControl.m_ePointerLocation = (EPointerLocation)m_nCursor_Relative_Location;
	p_SettingsHandler->m_stateCalibration.m_nCountCalibrateSelect = m_sldrCoundown_Calibration.GetPos();
	p_SettingsHandler->m_stateCursor.m_nCountDwell = m_sldrCountdown_Click.GetPos();
	p_SettingsHandler->m_stateCursor.m_nouseControl.m_eDiscreteDirection = (m_nDiscrete_Direction == 0) ? ALL_DIRECTIONS : (m_nDiscrete_Direction == 1) ?
		EIGHT_DIRECTIONS : FOUR_DIRECTIONS_CROSS;
	p_SettingsHandler->m_stateCursor.m_bEnableDwellClicking = (m_bEnable_Dwell_Click == TRUE ? true : false);
	p_SettingsHandler->m_stateCursor.m_nouseControl.m_nPctStopJoystick =_ttoi(m_strJoystick_Neutral_Zone);
	p_SettingsHandler->m_stateCursor.m_bLag = (m_bLag == TRUE ? true : false);
	p_SettingsHandler->m_stateCursor.m_nMinimumMouthClickHeight = m_sldrMax_Mouth_Click.GetPos();
	p_SettingsHandler->m_stateCursor.m_nTimeNochangeBackReset = _ttoi(m_strNo_Changeback_Seconds);
	p_SettingsHandler->m_stateCursor.m_nTimeMotionBackReset = _ttoi(m_strNo_Motion_Back);
	p_SettingsHandler->m_stateCursor.m_bUseMouthDetection = (m_bUse_Mouth_Click == TRUE? true:false);
	p_SettingsHandler->m_bUseVoiceCommands = (m_bUse_Voice_Commands == TRUE ? true : false);
}


BOOL CControlSettingsDlg::OnInitDialog()
{
	CSettingsTabDlg::OnInitDialog();

	m_sldrCoundown_Calibration.SetRange(0, 10);
	m_sldrCountdown_Click.SetRange(1, 5);
	m_sldrMax_Mouth_Click.SetRange(1, 20);
	m_sldr_Box_size.SetRange(1, 4);
	
	CEdit* pNumericText = (CEdit*)GetDlgItem(IDC__ACTIVATE_ASSUMES_HEADWIDTH_EDIT);
	pNumericText->SetLimitText(4);
	pNumericText = (CEdit*)GetDlgItem(IDC_NO_CHANGEBACK_SECONDS_EDIT);
	pNumericText->SetLimitText(3);
	pNumericText = (CEdit*)GetDlgItem(IDC_BIG_MOTION_SIZE_EDIT);
	pNumericText->SetLimitText(3);
	pNumericText = (CEdit*)GetDlgItem(IDC_NO_MOTION_BACK_EDIT);
	pNumericText->SetLimitText(3);
	pNumericText = (CEdit*)GetDlgItem(IDC_JOYSTICK_NEUTRAL_ZONE_EDIT);
	pNumericText->SetLimitText(3);

	pNumericText = NULL;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
