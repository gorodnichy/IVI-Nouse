#pragma once
#include "DataHandler.h"
#include "StateCursor.h"



class CSettingsHandler :
	public CDataHandler
{
public:
	CSettingsHandler();
	virtual ~CSettingsHandler();

	///////////
	struct sStateReadyData
	{
		bool m_bActWithFaceDetection;
		double m_dHeadWidth;
		int m_nFaceDetectionType;
		/*CNouseControl* m_pNouseControl;
		int m_nFacesInARow;
		PVI_RECT m_rectLastFaceDetected;*/
	} m_stateReady;
	struct sStateCalibrationData
	{
		int m_nCountConfirm;
		int m_nCountdown;
		bool m_bQuickCalibrate;
		int m_nClickBoxSize;
		int m_nCountCalibrateSelect;
	/*	bool* m_pbEnableSounds;
		PVI_RECT m_rectConfirm;
	
		CNouseTracker* m_pNouseTracker;
		CNouseControl* m_pNouseControl;
		bool m_bInConfirmingStage;*/
		
	} m_stateCalibration;

	/*
	struct sStateCursorData
	{
		bool m_bBigMotionDisabled;
		int m_nBigMotionPercentage;
		int m_nTimeNochangeBackReset;
		int m_nTimeMotionBackReset;
		int m_nCloseClickAmount;
		bool m_bUseMouthDetection;
		bool m_bUseVoiceCommands;
		bool m_bClickOnCommand;
		int m_nLockOn;
		int m_nCountConfirm;
		int m_nMinimumMouthClickHeight;
		int m_nClickBoxSize;
		bool m_bEnableDwellClicking;
		bool m_bLag;
		bool m_bAlwaysLeftClick;
		int m_nCountDwell;
		bool m_bEnableYellowState;
		int m_nResolutionInPixels;
		int m_nResolutionInSeconds;
		bool m_bInPauseMode;
		bool m_bSpecialClicksEnabled;
		int m_nFaceDetectionType;
	}m_stateCursor;*/
//	CStateReady m_stateReady;
//	CStateCalibration m_stateCalibration;

	CStateCursor m_stateCursor;
	//CState* m_pCurrentState;

	void updateFromFile();

	void loadBoardFile(CString strFileName);
	void saveBoardFile(CString strFileName);
	void formatBoardFile(CStdioFile* pFile = NULL);
	void parseFile(CStdioFile* pFile = NULL);
	void parseBoardFile(CStdioFile* pFile = NULL);
	void formatFile(CStdioFile* pFile = NULL);
	void setBoardText(CString strText, int nLevel, int nRow, int nCol, int nIndex);

	
	int m_nCursorSize;
	int m_nCursorSpeed;
	bool m_bCursorShowsFace, m_bCursorShowsCountdown;
	bool m_bUseLightNormalization;
	bool m_bMirrorCameraImage;
	int m_nProcessLoad;
	bool m_bUseTranslucentCursor;
	int m_nTranslucentSolidness;
	int m_iWebcamIndex;
	bool m_bEnableSounds;
	/////
	bool m_bUseVoiceCommands;
};

