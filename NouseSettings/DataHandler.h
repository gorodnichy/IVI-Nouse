#pragma once
#include "afx.h"
#include "StringsConstants.h"

#define NOUSE_SETTINGS_EXE_FILENAME _T("NouseSettings.exe")

#define CONSTANTS_ITEMS 37
#define MESSAGE_SETTINGS_SAVED WM_USER + 1000

enum ConstantItemNumbers {
	MAIN_DIALOG_TITLE_NUM = 0,
	ECALIBRAT_NUM,
	ENABLE_NUM,
	DISABLE_NUM,
	EXIT_NUM,
	SETTINGS_NUM,
	PAUSE_NUM,
	UNPAUSE_NUM,
	NOUSEBOARD_NUM,
	COULD_NOT_INITIALIZE_WEBCAM_NUM,
	DWELL_DIALOG_TITLE_NUM,
	LEFT_CLICK_NUM,
	RIGHT_CLICK_NUM,
	DOUBLE_CLICK_BUTTON_NUM,
	DRAG_NUM,
	NOUSEPAD_DIALOG_TITLE_NUM,
	NOUSE_TRIAL_INFO_NUM,
	NOUSE_TRADEMARK_NUM,
	DAYS_LEFT_IN_TRIAL_NUM,
	TRIAL_EXPIRED_NUM,
	NOUSEBOARD_DIALOG_TITLE_NUM,
	NOUSE_CURSOR_NUM,
	CREATION_FAILED_NUM,
	LEAVE_NUM,
	STILL_NUM,
	RESET_NUM,
	CENTER_NUM,
	PAUSED_NUM,
	BOARD_NUM,
	DIRECT_NUM,
	JOYSTICK_NUM,
	MOUSE_NUM,
	DISCRETE_NUM,
	TYPE_NUM,
	CLICK_NUM,
	WARNING_CAPTION_NUM,
	DISABLE_WARNING_NUM,
	EXIT_WARNING_NUM
};


#define SETTINGS_ITEMS 51

enum SettingsItemNumbers {
	BIG_MOTION_DISABLED_IN_CURSOR_STATE_NUM = 0,
	MOTION_SIZE_NUM,
	ACTIVATE_ASSUMES_HEADWIDTH_NUM,
	CONTROL_POINTERCORNER_MOVES_NUM,
	CALIBRATE_AUTOMATIC_NUM,
	CONTROL_NOCHANGE_BACK_TO_RESET_NUM,
	CONTROL_NOMOTION_BACK_TO_RESET_NUM,
	CLOSE_CLICK_FOR_BOARD_NUM,
	PCT_STOP_JOYSTICK_NUM,
	USE_MOUTH_DETECTION_NUM,
	USE_VOICE_COMMANDS_NUM,
	CLICK_ON_COMMAND_NUM,
	LOCK_ON_NUM,
	MOUSELESS_NAV_COMPARISON_TYPE_NUM,
	CountdownConfirmClick_NUM,
	CountdownTime_NUM,
	MinimumMouthClickHeight_NUM,
	ClickBoxSize_NUM,
	CursorShowsFace_NUM,
	MirrorCameraImage_NUM,
	DiscreteDirection_NUM,
	EnableDwellClicking_NUM,
	Lag_NUM,
	AlwaysLeftClick_NUM,
	ProcessLoad_NUM,
	FaceDetectionType_NUM,
	TranslucentCursor_NUM,
	TranslucenceSolidness_NUM,
	WebcamIndex_NUM,
	CursorShowsCountdown_NUM,
	DiscreteNavType_NUM,
	DirectMappingRows_NUM,
	DirectMappingCols_NUM,
	ShowDiscreteNavRects_NUM,
	///Settings dialogs
	CURSOR_SIZE_NUM,
	CURSOR_SPEED_NUM,
	COWNT_CALIB_TIME_NUM,
	COWNT_DWELL_TIME_NUM,
	ENABLE_YELLOW_STATE_NUM,
	NAVIGATION_TYPE_NUM,
	HORZ_RANGE_MOTION_NUM,
	VERT_RANGE_MOTION_NUM,
	RES_PIXELS_NUM,
	RES_SEC_NUM,
	ACTIVATE_USER_FACE_DETEC_NUM,
	LIGHT_NORM_NUM,
	ENABLE_AUTO_RECALIB_NUM,
	ENABLE_SOUNDS_NUM

};
///////////////////////

#define CURRENT_SETTINGS_LOCATION_FILENAME _T("currentSettingsFileLocation.txt")

#define CONSTANTS_FILENAME _T("constants.txt")
#define SETTINGS_FILENAME _T("settings.nouse")

#define TEMP_MARKER_FILENAME _T("temp")
#define TOKEN_STRING _T(" =\t")
/////////////////
class CDataHandler
{
public:
	CDataHandler();
	CDataHandler(CString strFilename);
	virtual ~CDataHandler();

	virtual void updateFromFile();
	virtual void parseFile(CStdioFile* pFile = NULL);
	virtual void writeToFile(CString strFilename = NULL);
	virtual void formatFile(CStdioFile* pFile = NULL) {};
	CString getFileDirectory();
	////
	//buttons strings
	CString m_strMainDialogTitle;
	CString m_strRecalibrate;
	CString m_strEnable;
	CString m_strDisable;
	CString m_strExit;
	CString m_strSettings;
	CString m_strPause;
	CString m_strUnpause;
	CString m_strNouseboard;
	CString m_strCouldNotInitializeWebcam;

	//info strings
	CString m_strExitWarning;
	CString m_strWarningCaption;
	CString m_strDisableWarning;
	CString m_strNouseTrialInfo;
	CString m_strNouseTrademark;
	CString m_strDaysLeftInTrial;
	CString m_strTrialExpired;

	CString m_strDwellDialogTitle;
	CString m_strNouseboardDialogTitle;

	///////////
	//Nouse Cursor strings
	CString m_strDoubleClick;
	CString m_strLeftClick;
	CString m_strRightClick;
	CString m_strDrag;
	CString m_strNousepadDialogTitle;
	CString m_strCreationFailed;
	CString m_strLeave;
	CString m_strStill;
	CString m_strReset;
	CString m_strCenter;
	CString m_strMouse;
	CString m_strPaused;
	CString m_strBoard;
	CString m_strDirect;
	CString m_strJoystick;
	CString m_strType;
	CString m_strDiscrete;
	CString m_strClick;
protected:
	CString getStrValueFromInputLine(CString strLine);

	

	///////////////
	CString m_strFileName;
	
	
};

