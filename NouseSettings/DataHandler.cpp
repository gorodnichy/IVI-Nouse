#include "stdafx.h"
#include "DataHandler.h"


CDataHandler::CDataHandler()
{
	m_strFileName = CONSTANTS_FILENAME;
}
CDataHandler::CDataHandler(CString strFilename)
{
	m_strFileName = strFilename;

}

CDataHandler::~CDataHandler()
{
	
}

CString CDataHandler::getFileDirectory()
{ 
	int nPos = m_strFileName.ReverseFind(_T('/'));
	if (nPos < 0)
		nPos = m_strFileName.ReverseFind(_T('\\'));
	if (nPos > 0) nPos++;
		
	return m_strFileName.Left(nPos);
}

void CDataHandler::updateFromFile() {
	
	CFileStatus status;
	if (CFile::GetStatus(m_strFileName, status)) {
		CStdioFile file(m_strFileName, CFile::modeRead);
		parseFile(&file);
		file.Close();
	}

}

void CDataHandler::writeToFile(CString strFilename/* = NULL*/) {

	UINT nOpenFlags = CFile::modeWrite;

	if (!strFilename || strFilename.IsEmpty())// if not internal file
	{
		strFilename = m_strFileName;

	}
	CFileStatus status;
	if (!CFile::GetStatus(strFilename, status))
	{
		nOpenFlags |= CFile::modeCreate;
	}


	//if (CFile::GetStatus(strFilename, status))
	{
		CStdioFile file(strFilename, nOpenFlags);
		formatFile(&file);
		file.Close();
	}
}


CString CDataHandler::getStrValueFromInputLine(CString strLine) {
	int iTok = 0;
	strLine.Tokenize(TOKEN_STRING, iTok);
	return strLine.Tokenize(TOKEN_STRING, iTok);
}

void CDataHandler::parseFile(CStdioFile* pFile)
{

	if (pFile == NULL)
		return;
		
	CString strLine, strVal, strConstant;
	while (pFile->ReadString(strLine)) {
		strConstant = "MAIN_DIALOG_TITLE ";
		if (strLine.Find(strConstant) == 0) {
			m_strMainDialogTitle = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "RECALIBRATE ";
		if (strLine.Find(strConstant) == 0) {
			m_strRecalibrate = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "ENABLE ";
		if (strLine.Find(strConstant) == 0) {
			m_strEnable = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DISABLE ";
		if (strLine.Find(strConstant) == 0) {
			m_strDisable = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "EXIT ";
		if (strLine.Find(strConstant) == 0) {
			m_strExit = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "SETTINGS ";
		if (strLine.Find(strConstant) == 0) {
			m_strSettings = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "PAUSE ";
		if (strLine.Find(strConstant) == 0) {
			m_strPause = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "UNPAUSE ";
		if (strLine.Find(strConstant) == 0) {
			m_strUnpause = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "NOUSEBOARD ";
		if (strLine.Find(strConstant) == 0) {
			m_strNouseboard = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "COULD_NOT_INITIALIZE_WEBCAM ";
		if (strLine.Find(strConstant) == 0) {
			m_strCouldNotInitializeWebcam = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DWELL_DIALOG_TITLE ";
		if (strLine.Find(strConstant) == 0) {
			m_strDwellDialogTitle = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "LEFT_CLICK ";
		if (strLine.Find(strConstant) == 0) {
			m_strLeftClick = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "RIGHT_CLICK ";
		if (strLine.Find(strConstant) == 0) {
			m_strRightClick = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DOUBLE_CLICK_BUTTON ";
		if (strLine.Find(strConstant) == 0) {
			m_strDoubleClick = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DRAG ";
		if (strLine.Find(strConstant) == 0) {
			m_strDrag = m_strDrag = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "NOUSEPAD_DIALOG_TITLE ";
		if (strLine.Find(strConstant) == 0) {
			m_strNousepadDialogTitle = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "NOUSE_TRIAL_INFO ";
		if (strLine.Find(strConstant) == 0) {
			m_strNouseTrialInfo = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "NOUSE_TRADEMARK ";
		if (strLine.Find(strConstant) == 0) {
			m_strNouseTrademark = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DAYS_LEFT_IN_TRIAL ";
		if (strLine.Find(strConstant) == 0) {
			m_strDaysLeftInTrial = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "TRIAL_EXPIRED ";
		if (strLine.Find(strConstant) == 0) {
			m_strTrialExpired = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "NOUSEBOARD_DIALOG_TITLE ";
		if (strLine.Find(strConstant) == 0) {
			CString strNouseboardDialogTitle = strLine.Mid(strConstant.GetLength());
			for (int i = 0; i < strNouseboardDialogTitle.GetLength(); ++i) {
				m_strNouseboardDialogTitle += strNouseboardDialogTitle.GetAt(i);
			}
			m_strNouseboardDialogTitle += '\0';
		}

		strConstant = "CREATION_FAILED ";
		if (strLine.Find(strConstant) == 0) {
			m_strCreationFailed = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "LEAVE ";
		if (strLine.Find(strConstant) == 0) {
			CString strLeave = strLine.Mid(strConstant.GetLength());
			for (int i = 0; i < strLeave.GetLength(); ++i) {
				m_strLeave += strLeave.GetAt(i);
			}
			m_strLeave += '\0';
		}

		strConstant = "STILL ";
		if (strLine.Find(strConstant) == 0) {
			CString strStill = strLine.Mid(strConstant.GetLength());
			for (int i = 0; i < strStill.GetLength(); ++i) {
				m_strStill += strStill.GetAt(i);
			}
			m_strStill += '\0';
		}

		strConstant = "RESET ";
		if (strLine.Find(strConstant) == 0) {
			CString strReset = strLine.Mid(strConstant.GetLength());
			for (int i = 0; i < strReset.GetLength(); ++i) {
				m_strReset += strReset.GetAt(i);
			}
			m_strReset += '\0';
		}

		strConstant = "CENTER ";
		if (strLine.Find(strConstant) == 0) {
			CString strCenter = strLine.Mid(strConstant.GetLength());
			for (int i = 0; i < strCenter.GetLength(); ++i) {
				m_strCenter += strCenter.GetAt(i);
			}
			m_strCenter += '\0';
		}

		strConstant = "PAUSED ";
		if (strLine.Find(strConstant) == 0) {
			CString strPaused = strLine.Mid(strConstant.GetLength());
			for (int i = 0; i < strPaused.GetLength(); ++i) {
				m_strPaused += strPaused.GetAt(i);
			}
			m_strPaused += '\0';

			strConstant = "BOARD ";
			if (strLine.Find(strConstant) == 0) {
				CString strBoard = strLine.Mid(strConstant.GetLength());
				for (int i = 0; i < strBoard.GetLength(); ++i) {
					m_strBoard += strBoard.GetAt(i);
				}
				m_strBoard += '\0';
			}

			strConstant = "DIRECT ";
			if (strLine.Find(strConstant) == 0) {
				CString strDirect = strLine.Mid(strConstant.GetLength());
				for (int i = 0; i < strDirect.GetLength(); ++i) {
					m_strDirect += strDirect.GetAt(i);
				}
				m_strDirect += '\0';
			}

			strConstant = "JOYSTICK ";
			if (strLine.Find(strConstant) == 0) {
				CString strJoystick = strLine.Mid(strConstant.GetLength());
				for (int i = 0; i < strJoystick.GetLength(); ++i) {
					m_strJoystick += strJoystick.GetAt(i);
				}
				m_strJoystick += '\0';
			}

			strConstant = "MOUSE ";
			if (strLine.Find(strConstant) == 0) {
				CString strMouse = strLine.Mid(strConstant.GetLength());
				for (int i = 0; i < strMouse.GetLength(); ++i) {
					m_strMouse += strMouse.GetAt(i);
				}
				m_strMouse += '\0';
			}

			strConstant = "DISCRETE ";
			if (strLine.Find(strConstant) == 0) {
				CString strDiscrete = strLine.Mid(strConstant.GetLength());
				for (int i = 0; i < strDiscrete.GetLength(); ++i) {
					m_strDiscrete += strDiscrete.GetAt(i);
				}
				m_strDiscrete += '\0';
			}

			strConstant = "TYPE ";
			if (strLine.Find(strConstant) == 0) {
				CString strType = strLine.Mid(strConstant.GetLength());
				for (int i = 0; i < strType.GetLength(); ++i) {
					m_strType += strType.GetAt(i);
				}
				m_strType += '\0';
			}

			strConstant = "CLICK ";
			if (strLine.Find(strConstant) == 0) {
				CString strClick = strLine.Mid(strConstant.GetLength());
				for (int i = 0; i < strClick.GetLength(); ++i) {
					m_strClick += strClick.GetAt(i);
				}
				m_strClick += '\0';
			}

			strConstant = "WARNING_CAPTION ";
			if (strLine.Find(strConstant) == 0) {
				m_strWarningCaption = strLine.Mid(strConstant.GetLength());
				continue;
			}

			strConstant = "DISABLE_WARNING ";
			if (strLine.Find(strConstant) == 0) {
				m_strDisableWarning = strLine.Mid(strConstant.GetLength());
				continue;
			}

			strConstant = "EXIT_WARNING ";
			if (strLine.Find(strConstant) == 0) {
				m_strExitWarning = strLine.Mid(strConstant.GetLength());
				continue;
			}
		}
	}
}