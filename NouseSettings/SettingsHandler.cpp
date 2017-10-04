#include "stdafx.h"
#include "SettingsHandler.h"


//handles transferring data from and to verious settings files

CSettingsHandler::CSettingsHandler()
{
	SetDataDefaults();
	
}


CSettingsHandler::~CSettingsHandler()
{
}

void CSettingsHandler::updateFromFile()
{


	CFileStatus status;
	if (!CFile::GetStatus(CURRENT_SETTINGS_LOCATION_FILENAME, status))
	{
		AfxMessageBox(_T("The settings location file is not found\nCheck the application folder.\nNouse Settings will use default values"), MB_OK | MB_ICONERROR);
		return;

	}
	CString strCurrentSettingsFile;
	CStdioFile fCurrentSettingsFileLocation(CURRENT_SETTINGS_LOCATION_FILENAME, CFile::modeRead);
	fCurrentSettingsFileLocation.ReadString(strCurrentSettingsFile);
	fCurrentSettingsFileLocation.Close();

	if (CFile::GetStatus(strCurrentSettingsFile, status)) {
		CStdioFile fileSettings(strCurrentSettingsFile, CFile::modeRead);
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
	while (pFile->ReadString(strLine)) 
	{
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
		//LOCK ON used to be for choosing which half of the screen you want mouse to move.
		//No longer used.
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
		else {//Nouse Board
			parseBoardLine(strLine);
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
	{ 
		parseBoardLine(strLine);
	}
}

void CSettingsHandler::parseBoardLine(CString strLine) {
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
					{
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[0] = b;// cvScalar(b, g, r);
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[1] = g;
						m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[nLevel].val[2] = r;

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
					sprintf_s(szTemp, "Group(%i,%i) =\t%s\t %s\t %s\t%s\t%d\t%d\t%d\n", row + 1, col + 1,
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
					sprintf_s(szTemp, "ShiftGroup(%i,%i) =\t%s\t %s\t %s\t%s\t%d\t%d\t%d\n", row + 1, col + 1,
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
					sprintf_s(szTemp, "AdvGroup(%i,%i) =\t%s\t %s\t %s\t%s\t%d\t%d\t%d\n", row + 1, col + 1,
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
	//File information
	CString strLine(_T(">> Nouse Training Configuration File << \n >> Instructions:\n- Read Nouse User Documentation for further instructions or visit www.nouse.ca.\n\n ========================================================================================\n 	>> Nouse Settings : \n"));
	pFile->WriteString(strLine);

	strLine.Format(_T("BIG_MOTION_DISABLED_IN_CURSOR_STATE\t%i\n"), (m_stateCursor.m_bBigMotionDisabled ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("MOTION_SIZE\t%d\n"), (int)m_stateCursor.m_nBigMotionPercentage);
	pFile->WriteString(strLine);
	strLine.Format(_T("ACTIVATE_ASSUMES_HEADWIDTH\t%d\n"), m_stateReady.m_dHeadWidth);
	pFile->WriteString(strLine);
	strLine.Format(_T("ACTIVATE_USES_FACEDETECTION\t%i\n"), (m_stateReady.m_bActWithFaceDetection ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("CONTROL_POINTERCORNER_MOVES\t%i\n"), (m_stateCursor.m_nouseControl.m_ePointerLocation ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("CALIBRATE_AUTOMATIC\t%i\n"), (m_stateCalibration.m_bQuickCalibrate ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("CONTROL_NOCHANGE_BACK_TO_RESET\t%i\n"), m_stateCursor.m_nTimeNochangeBackReset);
	pFile->WriteString(strLine);
	strLine.Format(_T("CLOSE_CLICK_FOR_BOARD\t%i\n"), m_stateCursor.m_nCloseClickAmount);
	pFile->WriteString(strLine);
	strLine.Format(_T("PCT_STOP_JOYSTICK\t%i\n"), m_stateCursor.m_nouseControl.m_nPctStopJoystick);
	pFile->WriteString(strLine);
	strLine.Format(_T("USE_MOUTH_DETECTION\t%i\n"), (m_stateCursor.m_bUseMouthDetection ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("MinimumMouthClickHeight\t%i\n"), m_stateCursor.m_nMinimumMouthClickHeight);
	pFile->WriteString(strLine);
	strLine.Format(_T("USE_VOICE_COMMANDS\t%i\n"), (m_bUseVoiceCommands ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("CLICK_ON_COMMAND\t%i\n"), (m_stateCursor.m_bClickOnCommand ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("LOCK_ON\t%i\n"), m_stateCursor.m_nLockOn);
	pFile->WriteString(strLine);
	strLine.Format(_T("CountdownConfirmClick\t%i\n"), m_stateCursor.m_nCountConfirm);
	pFile->WriteString(strLine);
	strLine.Format(_T("CountdownTime\t%i\n"), m_stateCalibration.m_nCountConfirm);
	pFile->WriteString(strLine);
	strLine.Format(_T("ClickBoxSize\t%i\n"), m_stateCursor.m_nClickBoxSize);
	pFile->WriteString(strLine);
	strLine.Format(_T("CursorShowsFace\t%i\n"), (m_bCursorShowsFace ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("MirrorCameraImage\t%i\n"), (m_bMirrorCameraImage ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("CountdownConfirmClick\t%i\n"), m_stateCursor.m_nouseControl.m_eDiscreteDirection);
	pFile->WriteString(strLine);
	strLine.Format(_T("CountdownConfirmClick\t%i\n"), m_stateCalibration.m_nCountConfirm);
	pFile->WriteString(strLine);
	strLine.Format(_T("EnableDwellClicking\t%i\n"), (m_stateCursor.m_bEnableDwellClicking ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("Lag\t%i\n"), (m_stateCursor.m_bLag ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("AlwaysLeftClick\t%i\n"), (m_stateCursor.m_bAlwaysLeftClick ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("ProcessLoad\t%i\n"), m_nProcessLoad);
	pFile->WriteString(strLine);
	strLine.Format(_T("CursorSize\t%i\n"), m_nCursorSize);
	pFile->WriteString(strLine);
	strLine.Format(_T("CursorSpeed\t%i\n"), m_stateCursor.m_nouseControl.m_nCursorSpeed);
	pFile->WriteString(strLine);
	strLine.Format(_T("CountdownCalibration\t%i\n"), m_stateCalibration.m_nCountCalibrateSelect);
	pFile->WriteString(strLine);
	strLine.Format(_T("CountdownDwell\t%i\n"), m_stateCursor.m_nCountDwell);
	pFile->WriteString(strLine);
	strLine.Format(_T("EnableYellowState\t%i\n"), (m_stateCursor.m_bEnableYellowState ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("EnableSounds\t%i\n"), (m_bEnableSounds ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("NavigationType\t%i\n"), (m_stateCursor.m_nouseControl.m_eGeneralControlMode ? 1 : 0));
	pFile->WriteString(strLine);
	strLine.Format(_T("MotionRangeHorizontal\t%i\n"), m_stateCursor.m_nouseControl.m_nMotionRangeHorizontal);
	pFile->WriteString(strLine);
	strLine.Format(_T("MotionRangeVertical\t%i\n"), m_stateCursor.m_nouseControl.m_nMotionRangeVertical);
	pFile->WriteString(strLine);
	strLine.Format(_T("ResolutionPixels\t%i\n"), m_stateCursor.m_nResolutionInPixels);
	pFile->WriteString(strLine);
	strLine.Format(_T("ResolutionSeconds\t%i\n"), m_stateCursor.m_nResolutionInSeconds);
	  pFile->WriteString(strLine);
	strLine.Format(_T("LightNormalization\t%i\n"), (m_bUseLightNormalization ? 1 : 0));
	  pFile->WriteString(strLine);
	strLine.Format(_T("TranslucentCursor\t%i\n"), (m_bUseTranslucentCursor ? 1 : 0));
	  pFile->WriteString(strLine);
	strLine.Format(_T("TranslucenceSolidness\t%i\n"), m_nTranslucentSolidness);
	  pFile->WriteString(strLine);
	strLine.Format(_T("WebcamIndex\t%i\n"), m_iWebcamIndex);
	  pFile->WriteString(strLine);
	strLine.Format(_T("EnableAutoRecalibration\t%i\n"), (m_stateCursor.m_bUseAutoRecalibration ? 1 : 0));
	  pFile->WriteString(strLine);
	strLine.Format(_T("EnableSpecialClickst%i\n"), (m_stateCursor.m_bSpecialClicksEnabled ? 1 : 0));
	  pFile->WriteString(strLine);
	strLine.Format(_T("FaceDetectionType\t%i\n"), m_stateCursor.m_nFaceDetectionType);
	  pFile->WriteString(strLine);
	strLine.Format(_T("CursorShowsCountdown\t%i\n"), (m_bCursorShowsCountdown ? 1 : 0));
	 pFile->WriteString(strLine);
	strLine.Format(_T("DiscreteNavType\t%i\n"), m_stateCursor.m_discreteNavSystem.m_eDiscreteNavType);
	 pFile->WriteString(strLine);
	strLine.Format(_T("DirectMappingRows\t%i\n"), m_stateCursor.m_discreteNavSystem.m_nDirectMappingRows);
	 pFile->WriteString(strLine);
	strLine.Format(_T("DirectMappingCols\t%i\n"), m_stateCursor.m_discreteNavSystem.m_nDirectMappingCols);
	  pFile->WriteString(strLine);
	strLine.Format(_T("ShowDiscreteNavRects\t%i\n"), (m_stateCursor.m_discreteNavSystem.m_bShowRects ? 1 : 0));
	pFile->WriteString(strLine);
	///////////////////
	strLine.Format(_T("MOUSELESS_NAV_COMPARISON_TYPE\t%i\n"), m_stateCursor.m_discreteNavSystem.m_eComparisonType);
	  pFile->WriteString(strLine);
	  pFile->WriteString(_T("\n>>Nouse-PVI configuration-registration data<<\n"));
	  pFile->WriteString(_T("=========================================================================================\n"));
	  strLine.Format(_T("JitterThreshold\t%i\n"), m_stateCursor.m_nouseBoard.m_nJitterThreshold);
	  pFile->WriteString(strLine);
	  strLine.Format(_T("NouseCursorInBoard\t%i\n\n"), (m_stateCursor.m_bNouseCursorInBoard ? 1 : 0));
	  pFile->WriteString(strLine);
	  pFile->WriteString(_T(">>>>>>>>>> Pad config\n"));
	  strLine.Format(_T("TextSizeScale\t%i\n"), m_stateCursor.m_nousePad.m_dTextSizeScale);
	  pFile->WriteString(strLine);
	  pFile->WriteString(_T(">> Note: the max BoardCol is 5 && the max BoardRow is 3\n"));
	  strLine.Format(_T("BoardTextScale\t%i\n\n"), m_stateCursor.m_nouseBoard.m_dTextSizeScale);
	  pFile->WriteString(strLine);
	  pFile->WriteString(_T(">> Activation corner\n"));
	  pFile->WriteString(_T(">> name	 column\trow\n"));
	  pFile->WriteString(_T("Activeblock1	=\t1\t1\n"));
	  strLine.Format(_T("Activeblock2	=\t%i\t1\n"), NUMBER_OF_COLS);
	  pFile->WriteString(strLine);
	  strLine.Format(_T("Activeblock3	=\t1\t%i\n"), NUMBER_OF_ROWS);
	  pFile->WriteString(strLine);
	  strLine.Format(_T("Activeblock4	=\t%i\t%i\n"), NUMBER_OF_COLS, NUMBER_OF_ROWS);
	  pFile->WriteString(strLine);
	  pFile->WriteString(_T("\n\n>>>>> Board Config: \n"));
	  formatBoardFile(pFile);

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

void CSettingsHandler::SetDataDefaults()
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
	///Basic Settings
	m_nCursorSize = 2;
	m_stateCursor.m_nouseControl.m_nCursorSpeed = 3;
	m_stateCalibration.m_nCountCalibrateSelect = 3;
	m_stateCursor.m_nCountDwell = 3;
	m_stateCursor.m_bEnableYellowState = FALSE;
	m_stateCursor.m_nouseControl.m_eGeneralControlMode = CONTROL_MODE_DIRECT;
	m_stateCursor.m_nouseControl.m_nMotionRangeHorizontal = 5;
	m_stateCursor.m_nouseControl.m_nMotionRangeVertical = 5;
	m_stateCursor.m_nResolutionInPixels = 3;
	m_stateCursor.m_nResolutionInSeconds = 1;
	m_stateReady.m_bActWithFaceDetection = TRUE;
	m_stateCursor.m_bUseAutoRecalibration = TRUE;
	//Advanced Controls Settings
	m_stateReady.m_dHeadWidth = 0.25;
	m_stateCursor.m_bAlwaysLeftClick = true;
	m_stateCursor.m_bBigMotionDisabled = true;
	m_stateCursor.m_nBigMotionPercentage = 30;
	m_stateCursor.m_nClickBoxSize = 1;
	m_stateCalibration.m_bQuickCalibrate = true;
	m_stateCursor.m_bClickOnCommand = true;
	m_stateCursor.m_nouseControl.m_ePointerLocation = MOVES;
	m_stateCalibration.m_nCountCalibrateSelect = 0;
	m_stateCursor.m_nCountDwell = 0;
	m_stateCursor.m_nouseControl.m_eDiscreteDirection = FOUR_DIRECTIONS_CROSS;
	m_stateCursor.m_bEnableDwellClicking = true;
	m_stateCursor.m_nouseControl.m_nPctStopJoystick = 15;
	m_stateCursor.m_bLag = true;
	m_stateCursor.m_nMinimumMouthClickHeight = 1;
	m_stateCursor.m_nTimeNochangeBackReset = 0;
	m_stateCursor.m_nTimeMotionBackReset = 0;
	m_stateCursor.m_bUseMouthDetection = true;
	m_bUseVoiceCommands = false;
	//Visual Settings
	m_bMirrorCameraImage = false;
	m_bCursorShowsCountdown = true;
	m_stateReady.m_bActWithFaceDetection = true;
	m_bUseTranslucentCursor = true;
	m_nProcessLoad = 1;
	m_stateReady.m_nFaceDetectionType = 0;
	m_nTranslucentSolidness =140;
	m_iWebcamIndex = 1;
	m_nProcessLoad = 1;
	//Board Settings
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[ABOVE_RECT - 1].szNormalText, "a\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[LEFT_OF_RECT - 1].szNormalText, "c\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[BELOW_RECT - 1].szNormalText, "d\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[RIGHT_OF_RECT - 1].szNormalText, "b\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[ABOVE_RECT - 1].szNormalText, "e\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[LEFT_OF_RECT - 1].szNormalText, "g\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[BELOW_RECT - 1].szNormalText, "h\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[RIGHT_OF_RECT - 1].szNormalText, "f\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[ABOVE_RECT - 1].szNormalText, "i\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[LEFT_OF_RECT - 1].szNormalText, "k\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[BELOW_RECT - 1].szNormalText, "l\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[RIGHT_OF_RECT - 1].szNormalText, "j\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[ABOVE_RECT - 1].szNormalText, "o\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[LEFT_OF_RECT - 1].szNormalText, "m\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[BELOW_RECT - 1].szNormalText, "n\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[RIGHT_OF_RECT - 1].szNormalText, "p\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[ABOVE_RECT - 1].szNormalText, "q\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[LEFT_OF_RECT - 1].szNormalText, "s\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[BELOW_RECT - 1].szNormalText, "t\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[RIGHT_OF_RECT - 1].szNormalText, "r\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[ABOVE_RECT - 1].szNormalText, "u\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[LEFT_OF_RECT - 1].szNormalText, "w\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[BELOW_RECT - 1].szNormalText, "x\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[RIGHT_OF_RECT - 1].szNormalText, "v\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[ABOVE_RECT - 1].szNormalText, "y\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[LEFT_OF_RECT - 1].szNormalText, "Switch\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[BELOW_RECT - 1].szNormalText, ".\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[RIGHT_OF_RECT - 1].szNormalText, "z\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[ABOVE_RECT - 1].szNormalText, "Space\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[LEFT_OF_RECT - 1].szNormalText, "\'\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[BELOW_RECT - 1].szNormalText, "?\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[RIGHT_OF_RECT - 1].szNormalText, "Enter\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[ABOVE_RECT - 1].szNormalText, "1\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[LEFT_OF_RECT - 1].szNormalText, "2\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[BELOW_RECT - 1].szNormalText, "3\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[RIGHT_OF_RECT - 1].szNormalText, "4\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[ABOVE_RECT - 1].szNormalText, "5\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[LEFT_OF_RECT - 1].szNormalText, "6\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[BELOW_RECT - 1].szNormalText, "7\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[RIGHT_OF_RECT - 1].szNormalText, "8\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[ABOVE_RECT - 1].szNormalText, "Up\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[LEFT_OF_RECT - 1].szNormalText, "Left\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[BELOW_RECT - 1].szNormalText, "Down\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[RIGHT_OF_RECT - 1].szNormalText, "Right\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[ABOVE_RECT - 1].szNormalText, "Shift\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[LEFT_OF_RECT - 1].szNormalText, "[\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[BELOW_RECT - 1].szNormalText, "Adv\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[RIGHT_OF_RECT - 1].szNormalText, "]\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[ABOVE_RECT - 1].szNormalText, "Clear\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[LEFT_OF_RECT - 1].szNormalText, "<-BKSP\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[BELOW_RECT - 1].szNormalText, "Quit\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[RIGHT_OF_RECT - 1].szNormalText, "DEL\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[ABOVE_RECT - 1].szNormalText, "ALT\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[LEFT_OF_RECT - 1].szNormalText, "CTRL\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[BELOW_RECT - 1].szNormalText, "Tab\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[RIGHT_OF_RECT - 1].szNormalText, "Pause\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[ABOVE_RECT - 1].szNormalText, "-\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[LEFT_OF_RECT - 1].szNormalText, "9\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[BELOW_RECT - 1].szNormalText, "0\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[RIGHT_OF_RECT - 1].szNormalText, "=\0");

	//Shift text
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[ABOVE_RECT - 1].szShiftText, "A\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[LEFT_OF_RECT - 1].szShiftText, "C\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[BELOW_RECT - 1].szShiftText, "D\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[RIGHT_OF_RECT - 1].szShiftText, "B\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[ABOVE_RECT - 1].szShiftText, "E\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[LEFT_OF_RECT - 1].szShiftText, "G\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[BELOW_RECT - 1].szShiftText, "H\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[RIGHT_OF_RECT - 1].szShiftText, "F\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[ABOVE_RECT - 1].szShiftText, "I\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[LEFT_OF_RECT - 1].szShiftText, "K\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[BELOW_RECT - 1].szShiftText, "L\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[RIGHT_OF_RECT - 1].szShiftText, "J\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[ABOVE_RECT - 1].szShiftText, "O\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[LEFT_OF_RECT - 1].szShiftText, "M\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[BELOW_RECT - 1].szShiftText, "N\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[RIGHT_OF_RECT - 1].szShiftText, "P\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[ABOVE_RECT - 1].szShiftText, "Q\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[LEFT_OF_RECT - 1].szShiftText, "S\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[BELOW_RECT - 1].szShiftText, "T\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[RIGHT_OF_RECT - 1].szShiftText, "R\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[ABOVE_RECT - 1].szShiftText, "U\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[LEFT_OF_RECT - 1].szShiftText, "W\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[BELOW_RECT - 1].szShiftText, "X\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[RIGHT_OF_RECT - 1].szShiftText, "V\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[ABOVE_RECT - 1].szShiftText, "Y\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[LEFT_OF_RECT - 1].szShiftText, "<\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[BELOW_RECT - 1].szShiftText, ">\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[RIGHT_OF_RECT - 1].szShiftText, "Z\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[ABOVE_RECT - 1].szShiftText, "Space\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[LEFT_OF_RECT - 1].szShiftText, "\"\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[BELOW_RECT - 1].szShiftText, "Enter\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[RIGHT_OF_RECT - 1].szShiftText, "/\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[ABOVE_RECT - 1].szShiftText, "!\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[LEFT_OF_RECT - 1].szShiftText, "@\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[BELOW_RECT - 1].szShiftText, "#\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[RIGHT_OF_RECT - 1].szShiftText, "$\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[ABOVE_RECT - 1].szShiftText, "%\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[LEFT_OF_RECT - 1].szShiftText, "^\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[BELOW_RECT - 1].szShiftText, "&\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[RIGHT_OF_RECT - 1].szShiftText, "*\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[ABOVE_RECT - 1].szShiftText, "Up\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[LEFT_OF_RECT - 1].szShiftText, "Left\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[BELOW_RECT - 1].szShiftText, "Down\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[RIGHT_OF_RECT - 1].szShiftText, "Right\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[ABOVE_RECT - 1].szShiftText, "Normal\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[LEFT_OF_RECT - 1].szShiftText, "{\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[BELOW_RECT - 1].szShiftText, "Adv\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[RIGHT_OF_RECT - 1].szShiftText, "}\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[ABOVE_RECT - 1].szShiftText, "Clear\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[LEFT_OF_RECT - 1].szShiftText, "<-BKSP\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[BELOW_RECT - 1].szShiftText, "Quit\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[RIGHT_OF_RECT - 1].szShiftText, "DEL\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[ABOVE_RECT - 1].szShiftText, "ALT\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[LEFT_OF_RECT - 1].szShiftText, "CTRL\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[BELOW_RECT - 1].szShiftText, "Tab\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[RIGHT_OF_RECT - 1].szShiftText, "Pause\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[ABOVE_RECT - 1].szShiftText, "_\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[LEFT_OF_RECT - 1].szShiftText, "(\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[BELOW_RECT - 1].szShiftText, ")\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[RIGHT_OF_RECT - 1].szShiftText, "+\0");


	//Adv text
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[ABOVE_RECT - 1].szAdvText, "W-RC1\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[LEFT_OF_RECT - 1].szAdvText, "W-RC2\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[BELOW_RECT - 1].szAdvText, "W-RC3\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][0].box[RIGHT_OF_RECT - 1].szAdvText, "W-RC4\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[ABOVE_RECT - 1].szAdvText, "W-RC5\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[LEFT_OF_RECT - 1].szAdvText, "W-R6\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[BELOW_RECT - 1].szAdvText, "W-RC7\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][1].box[RIGHT_OF_RECT - 1].szAdvText, "W-RC8\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[ABOVE_RECT - 1].szAdvText, "W-RC9\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[LEFT_OF_RECT - 1].szAdvText, "W-RC10\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[BELOW_RECT - 1].szAdvText, "W-CS1\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][2].box[RIGHT_OF_RECT - 1].szAdvText, "W-CS2\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[ABOVE_RECT - 1].szAdvText, "W-CS3\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[LEFT_OF_RECT - 1].szAdvText, "W-CS4\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[BELOW_RECT - 1].szAdvText, "W-CS5\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][3].box[RIGHT_OF_RECT - 1].szAdvText, "W-CS6\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[ABOVE_RECT - 1].szAdvText, "W-CC7\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[LEFT_OF_RECT - 1].szAdvText, "W-CC8\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[BELOW_RECT - 1].szAdvText, "W-CC9\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[0][4].box[RIGHT_OF_RECT - 1].szAdvText, "W-CC10\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[ABOVE_RECT - 1].szAdvText, "W-CC1\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[LEFT_OF_RECT - 1].szAdvText, "W-CC2\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[BELOW_RECT - 1].szAdvText, "W-CC3\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][0].box[RIGHT_OF_RECT - 1].szAdvText, "W-CC4\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[ABOVE_RECT - 1].szAdvText, "W-CC5\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[LEFT_OF_RECT - 1].szAdvText, "W-CC6\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[BELOW_RECT - 1].szAdvText, "W-CC7\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][1].box[RIGHT_OF_RECT - 1].szAdvText, "W-CC8\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[ABOVE_RECT - 1].szAdvText, "W-CC9\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[LEFT_OF_RECT - 1].szAdvText, "W-CC10\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[BELOW_RECT - 1].szAdvText, "W-RS1\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][2].box[RIGHT_OF_RECT - 1].szAdvText, "W-RS2\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[ABOVE_RECT - 1].szAdvText, "W-RS3\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[LEFT_OF_RECT - 1].szAdvText, "W-RS4\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[BELOW_RECT - 1].szAdvText, "W-RS5\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][3].box[RIGHT_OF_RECT - 1].szAdvText, "W-RS6\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[ABOVE_RECT - 1].szAdvText, "W-RS7\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[LEFT_OF_RECT - 1].szAdvText, "W-RS8\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[BELOW_RECT - 1].szAdvText, "W-RS9\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[1][4].box[RIGHT_OF_RECT - 1].szAdvText, "W-RS10\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[ABOVE_RECT - 1].szAdvText, "Up\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[LEFT_OF_RECT - 1].szAdvText, "Left\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[BELOW_RECT - 1].szAdvText, "Down\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][0].box[RIGHT_OF_RECT - 1].szAdvText, "Right\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[ABOVE_RECT - 1].szAdvText, "Shift\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[LEFT_OF_RECT - 1].szAdvText, "Space\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[BELOW_RECT - 1].szAdvText, "Normal\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][1].box[RIGHT_OF_RECT - 1].szAdvText, "Enter\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[ABOVE_RECT - 1].szAdvText, "Clear\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[LEFT_OF_RECT - 1].szAdvText, "<-BKSP\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[BELOW_RECT - 1].szAdvText, "Quit\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][2].box[RIGHT_OF_RECT - 1].szAdvText, "DEL\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[ABOVE_RECT - 1].szAdvText, "ALT\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[LEFT_OF_RECT - 1].szAdvText, "CTRL\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[BELOW_RECT - 1].szAdvText, "Tab\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][3].box[RIGHT_OF_RECT - 1].szAdvText, "Pause\0");

	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[ABOVE_RECT - 1].szAdvText, "\\\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[LEFT_OF_RECT - 1].szAdvText, "|\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[BELOW_RECT - 1].szAdvText, "<\0");
	strcpy(m_stateCursor.m_nouseBoard.m_Kbd.group[2][4].box[RIGHT_OF_RECT - 1].szAdvText, ">\0");

	
	for (int nRow = 0; nRow < NUMBER_OF_ROWS; ++nRow)
		for (int nCol = 0; nCol <NUMBER_OF_COLS; ++nCol)
			for (int nLevel = 0; nLevel < 3; ++nLevel)
			{
				m_stateCursor.m_nouseBoard.m_Kbd.group[nRow][nCol].normalColor[nLevel].val[0] = 255;// cvScalar(b, g, r);
				m_stateCursor.m_nouseBoard.m_Kbd.group[nRow][nCol].normalColor[nLevel].val[1] = 255;
				m_stateCursor.m_nouseBoard.m_Kbd.group[nRow][nCol].normalColor[nLevel].val[2] = 255;
			}

	m_stateCursor.m_nousePad.m_dTextSizeScale = 1;
	m_stateCursor.m_nouseBoard.m_dTextSizeScale = 1;
	m_stateCursor.m_bNouseCursorInBoard = false;
	m_stateCursor.m_nouseBoard.m_nJitterThreshold = 3;
	
}