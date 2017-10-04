// NouseSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Nouse5.h"
#include "NouseSettingsDlg.h"
#include "BasicSettingsDlg.h"
#include "afxdialogex.h"


// CBasicSettingsDlg dialog

//IMPLEMENT_DYNAMIC(CBasicSettingsDlg, CDialog)

CBasicSettingsDlg::CBasicSettingsDlg(CWnd* pParent)
	: CSettingsTabDlg()//(CBasicSettingsDlg::IDD, pParent)
{
	
	//initialize default values
	m_nCursorSize = 2;
	m_nCursorSpeed = 1;
	m_nCountdownCalibration = 3;
	m_nCountdownDwell = 2;
	m_nEnableYellowState = 1;
	m_nNavigationType = 1;
	m_nMotionRangeHorizontal = 5;
	m_nMotionRangeVertical = 5;
	m_nResolutionPixels = 3;
	m_nResolutionSeconds = 1;
	m_nUserFaceDetection = 1;
	m_nLightNormalization = 0;
	m_nEnableAutoRecalibration = 1;
	m_nEnableSounds = 1;
}

CBasicSettingsDlg::~CBasicSettingsDlg()
{
}



// CNouse5Dlg message handlers
BOOL CBasicSettingsDlg::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
		return FALSE;
	m_sldr_CursorSize.SetRange(1, 10);
	m_sldr_CursorSize.SetTic(1);
	m_sldr_CursorSpeed.SetRange(1, 10);
	m_sldr_CountdownCaliberTime.SetRange(1, 20);
	m_sldr_CountdownDwellTime.SetRange(0, 10);
	m_sldr_VerticalMotionRange.SetRange(1, 15);
	m_sldr_HorizontalMotionRange.SetRange(0, 15);
	m_sldr_ResolitionPixels.SetRange(1, 10);
	m_sldr_ResolitionSeconds.SetRange(1, 3);
	/////////////////////////////
	
	
	return TRUE;

}
void CBasicSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CURSOR_SIZE_SLIDER, m_sldr_CursorSize);
	DDX_Control(pDX, IDC_CURSOR_SPEED_SLIDER, m_sldr_CursorSpeed);
	DDX_Control(pDX, IDC_COWNT_CALIB_TIME_SLIDER, m_sldr_CountdownCaliberTime);
	DDX_Control(pDX, IDC_COWNT_DWELL_TIME_SLIDER, m_sldr_CountdownDwellTime);
	DDX_Control(pDX, IDC_HORZ_RANGE_SLIDER, m_sldr_HorizontalMotionRange);
	DDX_Control(pDX, IDC_VERT_RANGE_SLIDER, m_sldr_VerticalMotionRange);
	DDX_Control(pDX, IDC_RES_PIXELS_SLIDER, m_sldr_ResolitionPixels);
	DDX_Control(pDX, IDC_RES_SEC_SLIDER, m_sldr_ResolitionSeconds);

	DDX_Check(pDX, IDC_ENABLE_Y_STATE_CHECK, m_nEnableYellowState);
	DDX_Check(pDX, IDC_LIGHT_NORM_CHECK, m_nLightNormalization);
	DDX_Check(pDX, IDC_USER_FACE_DETEC_CHECK, m_nUserFaceDetection);
	DDX_Check(pDX, IDC_ENABLE_SOUNDS_CHECK, m_nEnableSounds);
	DDX_Check(pDX, IDC_LIGHT_NORM_CHECK, m_nLightNormalization);

	DDX_Radio(pDX, IDC_JOYSTK_RADIO, m_nNavigationType);
}


BEGIN_MESSAGE_MAP(CBasicSettingsDlg, CDialog)
	ON_BN_CLICKED(IDC_USER_FACE_DETEC_CHECK, &CBasicSettingsDlg::OnBnClickedUserFaceDetecCheck)
END_MESSAGE_MAP()


void CBasicSettingsDlg::GetData(CSettingsHandler* p_SettingsHandler)
{
	if (!p_SettingsHandler)
		return;
	UpdateData(TRUE);
	
	p_SettingsHandler->m_nCursorSize = m_sldr_CursorSize.GetPos();
	p_SettingsHandler->m_stateCursor.m_nouseControl.m_nCursorSpeed = m_sldr_CursorSpeed.GetPos();
	p_SettingsHandler->m_stateCalibration.m_nCountCalibrateSelect = m_sldr_CountdownCaliberTime.GetPos();
	p_SettingsHandler->m_stateCursor.m_nCountDwell = m_sldr_CountdownDwellTime.GetPos();
	p_SettingsHandler->m_stateCursor.m_bEnableYellowState = (m_nEnableYellowState == TRUE ? true : false);
	p_SettingsHandler->m_stateCursor.m_nouseControl.m_eGeneralControlMode = (EControlMode)(m_nNavigationType == 1 ? CONTROL_MODE_DIRECT : CONTROL_MODE_JOYSTICK);
	p_SettingsHandler->m_stateCursor.m_nouseControl.m_nMotionRangeHorizontal = m_sldr_HorizontalMotionRange.GetPos();
	p_SettingsHandler->m_stateCursor.m_nouseControl.m_nMotionRangeVertical = m_sldr_VerticalMotionRange.GetPos();
	p_SettingsHandler->m_stateCursor.m_nResolutionInPixels = m_sldr_ResolitionPixels.GetPos();
	p_SettingsHandler->m_stateCursor.m_nResolutionInSeconds = m_sldr_ResolitionSeconds.GetPos();
	p_SettingsHandler->m_stateReady.m_bActWithFaceDetection = (m_nUserFaceDetection == TRUE ? true : false);
	p_SettingsHandler->m_bUseLightNormalization = (m_nLightNormalization == TRUE ? true : false);
	p_SettingsHandler->m_stateCursor.m_bUseAutoRecalibration = (m_nEnableAutoRecalibration == TRUE ? true : false);
	p_SettingsHandler->m_bEnableSounds = (m_nEnableSounds == TRUE ? true : false);

}

void CBasicSettingsDlg::SetData(CSettingsHandler* p_SettingsHandler)
{
	if (!p_SettingsHandler)
		return;
	m_nCursorSize = p_SettingsHandler->m_nCursorSize;
	m_nCursorSpeed = p_SettingsHandler->m_stateCursor.m_nouseControl.m_nCursorSpeed;
	m_nCountdownCalibration = p_SettingsHandler->m_stateCalibration.m_nCountCalibrateSelect;
	m_nCountdownDwell = p_SettingsHandler->m_stateCursor.m_nCountDwell;
	m_nEnableYellowState = p_SettingsHandler->m_stateCursor.m_bEnableYellowState;
	m_nNavigationType = p_SettingsHandler->m_stateCursor.m_nouseControl.m_eGeneralControlMode;
	m_nMotionRangeHorizontal = p_SettingsHandler->m_stateCursor.m_nouseControl.m_nMotionRangeHorizontal;
	m_nMotionRangeVertical = p_SettingsHandler->m_stateCursor.m_nouseControl.m_nMotionRangeVertical;
	m_nResolutionPixels = p_SettingsHandler->m_stateCursor.m_nResolutionInPixels;
	m_nResolutionSeconds = p_SettingsHandler->m_stateCursor.m_nResolutionInSeconds;
	m_nUserFaceDetection = p_SettingsHandler->m_stateReady.m_bActWithFaceDetection;
	m_nLightNormalization = p_SettingsHandler->m_bUseLightNormalization;
	m_nEnableAutoRecalibration = p_SettingsHandler->m_stateCursor.m_bUseAutoRecalibration;
	m_nEnableSounds = p_SettingsHandler->m_bEnableSounds;

	m_sldr_CursorSize.SetPos(m_nCursorSize);
	m_sldr_CursorSpeed.SetPos(m_nCursorSpeed);
	m_sldr_CountdownCaliberTime.SetPos(m_nCountdownCalibration);
	m_sldr_CountdownDwellTime.SetPos(m_nCountdownDwell);
	m_sldr_VerticalMotionRange.SetPos(m_nMotionRangeVertical);
	m_sldr_HorizontalMotionRange.SetPos(m_nMotionRangeHorizontal);
	m_sldr_ResolitionPixels.SetPos(m_nResolutionPixels);
	m_sldr_ResolitionSeconds.SetPos(m_nResolutionSeconds);
	UpdateData();

}


void CBasicSettingsDlg::OnBnClickedUserFaceDetecCheck()
{
	// TODO: Add your control notification handler code here
}
