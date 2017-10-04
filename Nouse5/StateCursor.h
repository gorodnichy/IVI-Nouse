#pragma once

#define CLICK_BOX_SIZE 40
#define CLICK_SEPARATION 1
#define NOSE_CHECK_INTERVAL_SECONDS 2
#define NOSE_DISTANCE_TO_RESET 5

#include "state.h"
#include "../NouseVisionLibrary/NouseTracker.h"
#include "DiscreteNavSystem.h"
#include "NouseControl.h"
#include "DwellDialog.h"
#include "NouseBoard.h"
#include "NousePad.h"
#include "NouseMaze.h"

enum ECursorMode {
	FIND_GENERAL_AREA,
	FIND_EXACT_AREA,
	WAITING_TO_CLICK
};

class CStateCursor :
	public CState
{
public:
	CStateCursor(void);
	~CStateCursor(void);

	EState processData(CPVS* pPVS);
	void onEntrance(CPVS* pPVS);
	void onExit();

	void toggleInPauseMode();

	CNouseTracker* m_pNouseTracker;
	int* m_pnCursorWidth;
	time_t* m_pTimeWhenCursorArrivedAtPos;
	CNouseControl m_nouseControl;
	CNouseBoard m_nouseBoard;
	CNouseMaze m_nouseMaze;
	CNousePad m_nousePad;

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
	bool m_bTrialExpired;

	time_t m_timeTimerStart;
	bool m_bDragging;
	ECursorMode m_eCurrentMode;
	CDiscreteNavSystem m_discreteNavSystem;
	PVI_RECT m_rectClickBox;
	int m_nCountdown, m_nLastCountdown;
	bool m_bNotMoving;
	time_t m_timeWhenANoMotion;
	PVI_RECT m_rectLockArea;
	bool m_bEnoughNoseMotionOccured;
	bool m_bNeedToResetNose;
	double m_dMaxAbsNoseRel;
	PVI_POINT m_ptNoseAbs;
	PVI_RECT m_rectRange;
	PVI_POINT m_ptNoseRel11;
	PVI_POINT m_ptNoseRel01;
	bool m_bInNouseBoard;
	PVI_POINT m_ptNoseBlock;
	PVI_POINT m_ptNoseBlockHisterethis;
	bool m_bCloseEnoughForSpecialClick;
	PVI_POINT m_ptLastClick;
	//EPointRectComparison m_eLastClickType;
	time_t m_timeCursorStoppedMoving;
	bool m_bPauseGlue;
	PVI_POINT m_ptLastActualCursorPos;
	CTime m_timeLastClickMouth;
	CDwellDialog m_dDwell;
	bool m_bNouseCursorInBoard;
	void toggleInNouseBoard(void);
	bool m_bUseAutoRecalibration;
	bool* m_pbEnableSounds;

private:
	void setMode(ECursorMode eMode);
	void updateMemberVariables();
	void updatePointsBuffer(CPVS* pPVS);
	PVI_POINT calculatePtCursorPct();
	EState handleTimers(CPVS* pPVS);
	void click(EPointRectComparison ePointRectComparison);
	void handleTwoClicksCloseTogether(EPointRectComparison ePointRectComparison);
	void goToNextMode();
	void handleGlueCursorBusiness();
	bool isLotsOfMotion(CPVS* pPVS);
	bool isMouthClick(CPVS* pPVS);
	void clickCommand(EPointRectComparison ePointRectComparison);
	void performDwellClick();
	void handleDwellClickingDialog();
	void handleSpecialSelectedLetters();
	void updateCursorLocForNouseBoard(void);

	bool m_bIsMouthOpen;
	CTime m_timeLastNoseCheck;
	
public:
	void handleVoiceCommand(CString strVoiceCommand);
	bool m_bNoClickSinceClosingNouseBoard;
	PVI_POINT getPointToClick();
	bool m_bShouldShowContextMenu;
	PVI_POINT m_ptDragLocationCursor, m_ptDragLocationNouseCursor;
};

