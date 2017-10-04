#include "stdafx.h"
#include "SettingsHandler.h"


CSettingsHandler::CSettingsHandler()
{
	m_strFileName = SETTINGS_FILENAME;
		
	m_bMirrorCameraImage = true;
	m_nProcessLoad = 1;
	m_bUseLightNormalization = false;
	m_iWebcamIndex = 0;
	m_bUseVoiceCommands = false;
	m_bEnableSounds = true;
	m_bUseTranslucentCursor = false;
	m_nTranslucentSolidness = 140;
}


CSettingsHandler::~CSettingsHandler()
{
}

void CSettingsHandler::updateFromFile() {

	CStdioFile fCurrentSettingsFileLocation(CURRENT_SETTINGS_LOCATION_FILENAME, CFile::modeRead);
	fCurrentSettingsFileLocation.ReadString(m_strFileName);
	fCurrentSettingsFileLocation.Close();

	CFileStatus status;
	if (CFile::GetStatus(m_strFileName, status)) {
		CStdioFile fileSettings(m_strFileName, CFile::modeRead);
		parseFile(&fileSettings);
		fileSettings.Close();
	}
	
}

void CSettingsHandler::parseFile(CStdioFile* pFile)
{

	if (pFile == NULL)
	{
		return;
	}
	
	CString strLine, strVal;
	int index = 0;
	while (pFile->ReadString(strLine)) {
		if (strLine.Find(_T("BIG_MOTION_DISABLED_IN_CURSOR_STATE")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bBigMotionDisabled = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("MOTION_SIZE")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nBigMotionPercentage = _ttoi(strVal);
		}
		else if (strLine.Find(_T("ACTIVATE_ASSUMES_HEADWIDTH")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateReady.m_dHeadWidth = _ttof(strVal);
		}
		else if (strLine.Find(_T("ACTIVATE_USES_FACEDETECTION")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateReady.m_bActWithFaceDetection = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("CONTROL_POINTERCORNER_MOVES")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseControl.m_ePointerLocation = (EPointerLocation)_ttoi(strVal);
		}
		else if (strLine.Find(_T("CALIBRATE_AUTOMATIC")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCalibration.m_bQuickCalibrate = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("CONTROL_NOCHANGE_BACK_TO_RESET")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nTimeNochangeBackReset = _ttoi(strVal);
		}
		else if (strLine.Find(_T("CONTROL_NOMOTION_BACK_TO_RESET")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nTimeMotionBackReset = _ttoi(strVal);
		}
		else if (strLine.Find(_T("CLOSE_CLICK_FOR_BOARD")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nCloseClickAmount = _ttoi(strVal);
		}
		else if (strLine.Find(_T("PCT_STOP_JOYSTICK")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseControl.m_nPctStopJoystick = _ttoi(strVal);
		}
		else if (strLine.Find(_T("USE_MOUTH_DETECTION")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bUseMouthDetection = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("MinimumMouthClickHeight")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nMinimumMouthClickHeight = _ttoi(strVal);
		}
		else if (strLine.Find(_T("USE_VOICE_COMMANDS")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bUseVoiceCommands = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("CLICK_ON_COMMAND")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bClickOnCommand = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("LOCK_ON")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nLockOn = _ttoi(strVal);
		}
		else if (strLine.Find(_T("MOUSELESS_NAV_COMPARISON_TYPE")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			index = _ttoi(strVal);
			m_stateCursor.m_discreteNavSystem.m_eComparisonType = index == 0 ? FOUR_DIRECTIONS_CROSS : index == 1 ? FOUR_DIRECTIONS_X : EIGHT_DIRECTIONS;
		}
		else if (strLine.Find(_T("CountdownConfirmClick")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nCountConfirm = _ttoi(strVal);
		}
		else if (strLine.Find(_T("CountdownTime")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCalibration.m_nCountConfirm = _ttoi(strVal);
		}
		else if (strLine.Find(_T("ClickBoxSize")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nClickBoxSize = m_stateCalibration.m_nClickBoxSize = _ttoi(strVal);
		}
		else if (strLine.Find(_T("CursorShowsFace")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bCursorShowsFace = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("MirrorCameraImage")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bMirrorCameraImage = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("DiscreteDirection")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			index = _ttoi(strVal);
			m_stateCursor.m_nouseControl.m_eDiscreteDirection = (index == 0) ? ALL_DIRECTIONS : (index == 1) ?
				EIGHT_DIRECTIONS : FOUR_DIRECTIONS_CROSS;
		}
		else if (strLine.Find(_T("EnableDwellClicking")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bEnableDwellClicking = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("Lag")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bLag = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("AlwaysLeftClick")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bAlwaysLeftClick = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("ProcessLoad")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_nProcessLoad = _ttoi(strVal);
		}
		else if (strLine.Find(_T("CursorSize")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_nCursorSize = _ttoi(strVal);
		}
		else if (strLine.Find(_T("CursorSpeed")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseControl.m_nCursorSpeed = _ttoi(strVal);
		}
		else if (strLine.Find(_T("CountdownCalibration")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCalibration.m_nCountCalibrateSelect = _ttoi(strVal);
		}
		else if (strLine.Find(_T("CountdownDwell")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nCountDwell = _ttoi(strVal);
		}
		else if (strLine.Find(_T("EnableYellowState")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bEnableYellowState = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("EnableSounds")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bEnableSounds = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("NavigationType")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			switch (_ttoi(strVal)) {
			case 1:
				m_stateCursor.m_nouseControl.m_eGeneralControlMode = CONTROL_MODE_JOYSTICK;
				break;
			case 2:
				m_stateCursor.m_nouseControl.m_eGeneralControlMode = CONTROL_MODE_DIRECT;
				break;
			default:
				m_stateCursor.m_nouseControl.m_eGeneralControlMode = CONTROL_MODE_DISCRETE;
			}
		}
		else if (strLine.Find(_T("MotionRangeHorizontal")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseControl.m_nMotionRangeHorizontal = _ttoi(strVal);
		}
		else if (strLine.Find(_T("MotionRangeVertical")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseControl.m_nMotionRangeVertical = _ttoi(strVal);
		}
		else if (strLine.Find(_T("ResolutionPixels")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nResolutionInPixels = _ttoi(strVal);
		}
		else if (strLine.Find(_T("ResolutionSeconds")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nResolutionInSeconds = _ttoi(strVal);
		}
		else if (strLine.Find(_T("LightNormalization")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bUseLightNormalization = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("TranslucentCursor ")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bUseTranslucentCursor = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("TranslucenceSolidness ")) >= 0) { 
			strVal = getStrValueFromInputLine(strLine);
			m_nTranslucentSolidness = _ttoi(strVal);
		}
		else if (strLine.Find(_T("JitterThreshold")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseBoard.m_nJitterThreshold = _ttoi(strVal);
		}
		else if (strLine.Find(_T("NouseCursorInBoard")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bNouseCursorInBoard = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("TextSizeScale")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nousePad.m_dTextSizeScale = _ttof(strVal);
		}
		else if (strLine.Find(_T("BoardTextScale")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseBoard.m_dTextSizeScale = _ttof(strVal);
		}
		else if (strLine.Find(_T("WebcamIndex")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_iWebcamIndex = _ttoi(strVal);
		}
		else if (strLine.Find(_T("EnableAutoRecalibration")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bUseAutoRecalibration = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("EnableSpecialClicks")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bSpecialClicksEnabled = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("FaceDetectionType")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateReady.m_nFaceDetectionType = m_stateCursor.m_nFaceDetectionType = _ttoi(strVal);
		}
		else if (strLine.Find(_T("CursorShowsCountdown")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bCursorShowsCountdown = _ttoi(strVal) != 0;
		}
		else if (strLine.Find(_T("DiscreteNavType")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_discreteNavSystem.m_eDiscreteNavType = (_ttoi(strVal) == 0) ? DECREASING_JUMPS : MAPPING_TO_QUADRANTS;
		}
		else if (strLine.Find(_T("DirectMappingRows")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_discreteNavSystem.m_nDirectMappingRows = _ttoi(strVal);
		}
		else if (strLine.Find(_T("DirectMappingCols")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_discreteNavSystem.m_nDirectMappingCols = _ttoi(strVal);
		}
		else if (strLine.Find(_T("ShowDiscreteNavRects")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_discreteNavSystem.m_bShowRects = _ttoi(strVal) != 0;
		}
		else { //NouseBoard
			parseBoardFile(pFile);
		}
	}
}

void CSettingsHandler::loadBoardFile(CString strFileName)
{
	CFileStatus status;
	if (CFile::GetStatus(strFileName, status)) {
		CStdioFile fileSettings(strFileName, CFile::modeRead);
		parseBoardFile(&fileSettings);
		fileSettings.Close();
	}
}

void CSettingsHandler::saveBoardFile(CString strFileName)
{
	CFileStatus status;
	UINT nOpenFlags = CFile::modeWrite;
	CStdioFile file;// (strFileName, nOpenFlags);

	if (!CFile::GetStatus(strFileName, status))
	{
		nOpenFlags |= CFile::modeCreate;
	}
	if (file.Open(strFileName, nOpenFlags))
	{
		formatBoardFile(&file);
		file.Close();
	}

}

void CSettingsHandler::parseBoardFile(CStdioFile* pFile)
{
	if (pFile == NULL)
	{
		return;
	}

	CString strLine, strVal;
	int index = 0;
	while (pFile->ReadString(strLine))
	{ //NouseBoard
		CString strSearch;
		CString strLevel;
		CStringA strLineA(strLine);
		for (int nLevel = 0; nLevel < 3; ++nLevel) {
			strLevel = (nLevel == 0) ? "Group" : (nLevel == 1) ? "ShiftGroup" : "AdvGroup";
			for (int row = 0; row < 3; ++row) {
				for (int col = 0; col < 5; ++col) {
					strSearch.Format(_T("%s(%d,%d)"), strLevel, row + 1, col + 1);
					if (strLine.Find(strSearch) == 0)
					{
						// Elan09: Put in functionality for reading colour
						int b = -1, g = -1, r = -1;
						if (nLevel == 0)
							sscanf(strLineA, "%*s %*s %s %s %s %s %d %d %d", m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT - 1].szNormalText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT - 1].szNormalText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT - 1].szNormalText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT - 1].szNormalText, &b, &g, &r);
						else if (nLevel == 1)
							sscanf(strLineA, "%*s %*s %s %s %s %s %d %d %d", m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT - 1].szShiftText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT - 1].szShiftText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT - 1].szShiftText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT - 1].szShiftText, &b, &g, &r);
						else
							sscanf(strLineA, "%*s %*s %s %s %s %s %d %d %d", m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT - 1].szAdvText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT - 1].szAdvText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT - 1].szAdvText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT - 1].szAdvText, &b, &g, &r);
						if (b >= 0 && g >= 0 && r >= 0)
							m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel] = cvScalar(b, g, r);
					}
				}
			}
		}
	}

}

void CSettingsHandler::formatBoardFile(CStdioFile* pFile)
{
	if (pFile == NULL)
		return;

	CString strLine;
	 //NouseBoard
	char szTemp[256];

	for (int nLevel = 0; nLevel < 3; ++nLevel)
	{			
		if (nLevel == 0)
		{
			pFile->WriteString(_T("\n- 	Keyboard Groups -  Layer 1 -  Normal Text\n"));
		}
		else if (nLevel == 1)
		{
			pFile->WriteString(_T(" - Layer 2 -	 Shift text\n"));
		}
		else
		{ 
			pFile->WriteString(_T("- Layer 3 -	 Adv text\n"));
		}

		for (int row = 0; row < 3; ++row) 
		{
			for (int col = 0; col < 5; ++col)
			{	
				if (nLevel == 0)
				{
					sprintf_s(szTemp, "Group(%i,%i) = %s %s %s %s  %d %d %d \n", row + 1, col + 1,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT - 1].szNormalText,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT - 1].szNormalText,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT - 1].szNormalText,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT - 1].szNormalText,
						(int)m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[0],
						(int)m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[1],
						(int)m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[2]);
										
				}
				else if (nLevel == 1)
				{
					sprintf_s(szTemp, "ShiftGroup(%i,%i) = %s %s %s %s  %d %d %d \n", row + 1, col + 1,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT - 1].szShiftText,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT - 1].szShiftText,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT - 1].szShiftText,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT - 1].szShiftText,
						(int)m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[0],
						(int)m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[1],
						(int)m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[2]);
				}
				else
				{ 
					sprintf_s(szTemp, "AdvGroup(%i,%i) = %s %s %s %s  %d %d %d\n", row + 1, col + 1,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT - 1].szAdvText,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT - 1].szAdvText,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT - 1].szAdvText,
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT - 1].szAdvText,
						(int)m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[0],
						(int)m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[1],
						(int)m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[2]);
				}	
				strLine = szTemp;

				pFile->WriteString(strLine);
			}//col
		}//row
	}//level
}

void CSettingsHandler::formatFile(CStdioFile* pFile)
{

	if (pFile == NULL)
		return;

	CString strLine;

		strLine.Format(_T("BIG_MOTION_DISABLED_IN_CURSOR_STATE %i \n"), (m_stateCursor.m_bBigMotionDisabled ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("MOTION_SIZE %d \n"), (int)m_stateCursor.m_nBigMotionPercentage);
		pFile->WriteString(strLine);
		strLine.Format(_T("ACTIVATE_ASSUMES_HEADWIDTH %d \n"), m_stateReady.m_dHeadWidth);
		pFile->WriteString(strLine);
		strLine.Format(_T("ACTIVATE_USES_FACEDETECTION %i \n"), (m_stateReady.m_bActWithFaceDetection ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("CONTROL_POINTERCORNER_MOVES %i \n"), (m_stateCursor.m_nouseControl.m_ePointerLocation ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("CALIBRATE_AUTOMATIC %i \n"), (m_stateCalibration.m_bQuickCalibrate ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("CONTROL_NOCHANGE_BACK_TO_RESET %i \n"), m_stateCursor.m_nTimeNochangeBackReset);
		pFile->WriteString(strLine);
		strLine.Format(_T("CLOSE_CLICK_FOR_BOARD %i \n"), m_stateCursor.m_nCloseClickAmount);
		pFile->WriteString(strLine);
		strLine.Format(_T("PCT_STOP_JOYSTICK %i \n"), m_stateCursor.m_nouseControl.m_nPctStopJoystick);
		pFile->WriteString(strLine);
		strLine.Format(_T("USE_MOUTH_DETECTION %i \n"), (m_stateCursor.m_bUseMouthDetection ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("MinimumMouthClickHeight %i \n"), m_stateCursor.m_nMinimumMouthClickHeight);
		pFile->WriteString(strLine);
		strLine.Format(_T("USE_VOICE_COMMANDS %i \n"), (m_bUseVoiceCommands ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("CLICK_ON_COMMAND %i \n"), (m_stateCursor.m_bClickOnCommand ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("LOCK_ON %i \n"), m_stateCursor.m_nLockOn);
		pFile->WriteString(strLine);
		strLine.Format(_T("CountdownConfirmClick %i \n"), m_stateCursor.m_nCountConfirm);
		pFile->WriteString(strLine);
		strLine.Format(_T("CountdownTime %i \n"), m_stateCalibration.m_nCountConfirm);
		pFile->WriteString(strLine);
		strLine.Format(_T("ClickBoxSize %i \n"), m_stateCursor.m_nClickBoxSize);
		pFile->WriteString(strLine);
		strLine.Format(_T("CursorShowsFace %i \n"), (m_bCursorShowsFace ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("MirrorCameraImage %i \n"), (m_bMirrorCameraImage ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("CountdownConfirmClick %i \n"), m_stateCursor.m_nouseControl.m_eDiscreteDirection);
		pFile->WriteString(strLine);
		strLine.Format(_T("CountdownConfirmClick %i \n"), m_stateCalibration.m_nCountConfirm);
		pFile->WriteString(strLine);
		strLine.Format(_T("EnableDwellClicking %i \n"), (m_stateCursor.m_bEnableDwellClicking ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("Lag %i \n"), (m_stateCursor.m_bLag ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("AlwaysLeftClick %i \n"), (m_stateCursor.m_bAlwaysLeftClick ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("ProcessLoad %i \n"), m_nProcessLoad);
		pFile->WriteString(strLine);
		strLine.Format(_T("CursorSize %i \n"), m_nCursorSize);
		pFile->WriteString(strLine);
		strLine.Format(_T("CursorSpeed %i \n"), m_stateCursor.m_nouseControl.m_nCursorSpeed);
		pFile->WriteString(strLine);
		strLine.Format(_T("CountdownCalibration %i \n"), m_stateCalibration.m_nCountCalibrateSelect);
		pFile->WriteString(strLine);
		strLine.Format(_T("CountdownDwell %i \n"), m_stateCursor.m_nCountDwell);
		pFile->WriteString(strLine);
		strLine.Format(_T("EnableYellowState %i \n"), (m_stateCursor.m_bEnableYellowState ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("EnableSounds %i \n"), (m_bEnableSounds ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("NavigationType %i \n"), (m_stateCursor.m_nouseControl.m_eGeneralControlMode ? 1 : 0));
		pFile->WriteString(strLine);
		strLine.Format(_T("MotionRangeHorizontal %i \n"), m_stateCursor.m_nouseControl.m_nMotionRangeHorizontal);
		pFile->WriteString(strLine);
		strLine.Format(_T("MotionRangeVertical %i \n"), m_stateCursor.m_nouseControl.m_nMotionRangeVertical);
		pFile->WriteString(strLine);
		strLine.Format(_T("ResolutionPixels %i \n"), m_stateCursor.m_nResolutionInPixels);
		pFile->WriteString(strLine);
		strLine.Format(_T("ResolutionSeconds %i \n"), m_stateCursor.m_nResolutionInSeconds);
		  pFile->WriteString(strLine);
		strLine.Format(_T("LightNormalization %i \n"), (m_bUseLightNormalization ? 1 : 0));
		  pFile->WriteString(strLine);
		strLine.Format(_T("TranslucentCursor %i \n"), (m_bUseTranslucentCursor ? 1 : 0));
		  pFile->WriteString(strLine);
		strLine.Format(_T("TranslucenceSolidness %i \n"), m_nTranslucentSolidness);
		  pFile->WriteString(strLine);
		strLine.Format(_T("WebcamIndex %i \n"), m_iWebcamIndex);
		  pFile->WriteString(strLine);
		strLine.Format(_T("EnableAutoRecalibration %i \n"), (m_stateCursor.m_bUseAutoRecalibration ? 1 : 0));
		  pFile->WriteString(strLine);
		strLine.Format(_T("EnableSpecialClicks"), (m_stateCursor.m_bSpecialClicksEnabled ? 1 : 0));
		  pFile->WriteString(strLine);
		strLine.Format(_T("FaceDetectionType %i \n"), m_stateCursor.m_nFaceDetectionType);
		  pFile->WriteString(strLine);
		strLine.Format(_T("CursorShowsCountdown %i \n"), (m_bCursorShowsCountdown ? 1 : 0));
		  pFile->WriteString(strLine);
		strLine.Format(_T("DiscreteNavType %i \n"), m_stateCursor.m_discreteNavSystem.m_eDiscreteNavType);
		  pFile->WriteString(strLine);
		strLine.Format(_T("DirectMappingRows %i \n"), m_stateCursor.m_discreteNavSystem.m_nDirectMappingRows);
		  pFile->WriteString(strLine);
		strLine.Format(_T("DirectMappingCols %i \n"), m_stateCursor.m_discreteNavSystem.m_nDirectMappingCols);
		  pFile->WriteString(strLine);
		strLine.Format(_T("ShowDiscreteNavRects %i \n"), (m_stateCursor.m_discreteNavSystem.m_bShowRects ? 1 : 0));
		pFile->WriteString(strLine);
		///////////////////
		strLine.Format(_T("MOUSELESS_NAV_COMPARISON_TYPE %i \n"), m_stateCursor.m_discreteNavSystem.m_eComparisonType);
	   pFile->WriteString(strLine);
	   pFile->WriteString((LPCTSTR)">>Nouse-PVI configuration-registration data<<");
	   pFile->WriteString((LPCTSTR)"=========================================================================================");
	   strLine.Format(_T("JitterThreshold %i \n"), m_stateCursor.m_nouseBoard.m_nJitterThreshold);
	   pFile->WriteString(strLine);
	   strLine.Format(_T("NouseCursorInBoard %i \n\n"), (m_stateCursor.m_bNouseCursorInBoard ? 1 : 0));
	   pFile->WriteString(strLine);
	   pFile->WriteString((LPCTSTR)">>>>>>>>>> Pad config");
	   strLine.Format(_T("TextSizeScale %i \n"), m_stateCursor.m_nousePad.m_dTextSizeScale);
	   pFile->WriteString(strLine);
	   pFile->WriteString((LPCTSTR)">> Note: the max BoardCol is 5 && the max BoardRow is 3");
	   strLine.Format(_T("BoardTextScale %i \n\n"), m_stateCursor.m_nouseBoard.m_dTextSizeScale);
	   pFile->WriteString(strLine);

	   pFile->WriteString(_T(">> Activation corner"));
	   pFile->WriteString(_T(">> name				col row"));
	   pFile->WriteString(_T("Activeblock1	=	1	1"));
	   strLine.Format(_T("Activeblock2	= %i 1"), NUMBER_OF_COLS);
	   pFile->WriteString(strLine);
	   strLine.Format(_T("Activeblock3	= 1	%i"), NUMBER_OF_ROWS);
	   pFile->WriteString(strLine);
	   strLine.Format(_T("Activeblock4	= %i %i"), NUMBER_OF_COLS, NUMBER_OF_ROWS);
	   pFile->WriteString(strLine);
	   pFile->WriteString(_T("\n\n>>>>> Board Config: "));

}

void CSettingsHandler::setBoardText(CString strText, int nLevel, int nRow, int nCol, int nIndex)
{
//	int nPos[] = { ABOVE_RECT,LEFT_OF_RECT,BELOW_RECT,RIGHT_OF_RECT };

	if (nLevel == 0)
	{
		strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[nRow][nCol].box[nIndex].szNormalText, (LPCSTR)(CStringA)strText);
	}
	else if (nLevel == 1)
	{
		strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[nRow][nCol].box[nIndex].szShiftText, (LPCSTR)(CStringA)strText);
	}
	else
	{
		strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[nRow][nCol].box[nIndex].szAdvText, (LPCSTR)(CStringA)strText);
	}
}

