#include "StdAfx.h"
#include "StateCursor.h"
#include <algorithm>

CStateCursor::CStateCursor(void) :
m_bBigMotionDisabled(true),
m_nBigMotionPercentage(30),
m_nTimeNochangeBackReset(99999),
m_nTimeMotionBackReset(99999),
m_nCloseClickAmount(20),
m_bUseMouthDetection(false),
m_bUseVoiceCommands(false),
m_bClickOnCommand(false),
m_nLockOn(0),
m_nCountConfirm(3),
m_nMinimumMouthClickHeight(1),
m_nClickBoxSize(1),
m_bEnableDwellClicking(false),
m_bLag(false),
m_bAlwaysLeftClick(false),
m_bTrialExpired(true),
m_nCountDwell(3),
m_bEnableYellowState(false),
m_nResolutionInPixels(3),
m_nResolutionInSeconds(1),
m_bNeedToResetNose(false),
m_dMaxAbsNoseRel(0),
m_bCloseEnoughForSpecialClick(false),
m_timeCursorStoppedMoving(0),
m_bPauseGlue(false),
m_bInPauseMode(false),
m_bNouseCursorInBoard(true),
m_bUseAutoRecalibration(true),
m_nLastCountdown(3),
m_bInNouseBoard(false),
m_bIsMouthOpen(false),
m_bNoClickSinceClosingNouseBoard(false),
m_bSpecialClicksEnabled(false),
m_nFaceDetectionType(0),
m_bShouldShowContextMenu(false)
{
	m_ptLastClick.set(-1,-1);
	m_eWhoAmI = STATE_CURSOR;
}


CStateCursor::~CStateCursor(void)
{
}

EState CStateCursor::processData(CPVS *pPVS) {
	updateMemberVariables();

	// GENERAL INITIAL STUFF
	updatePointsBuffer(pPVS);
	int nCursorWidth = *m_pnCursorWidth;

	// Timers
	EState handleTimersResult = handleTimers(pPVS);
	if(handleTimersResult != m_eWhoAmI)
		return handleTimersResult;

	if(m_bInNouseBoard) {
		
	} else {
		handleDwellClickingDialog();
	}

	//Deal with events
	if(!m_bBigMotionDisabled && !m_bInPauseMode && isLotsOfMotion(pPVS))
		return STATE_READY;
	if(m_bUseMouthDetection && !m_bInPauseMode && isMouthClick(pPVS)) {
		if(!m_bInNouseBoard && m_nouseControl.m_eControlMode == CONTROL_MODE_DISCRETE && m_discreteNavSystem.m_eDiscreteNavType == MAPPING_TO_QUADRANTS)
			m_discreteNavSystem.jump();
		else
			clickCommand(LEFT_OF_RECT);
	}

	if(m_bInNouseBoard) {
		if (m_eCurrentMode != WAITING_TO_CLICK)	{
			updateCursorLocForNouseBoard();
		}
	} else {
		if(m_eCurrentMode != WAITING_TO_CLICK && !m_bNeedToResetNose) {
			if(/*m_discreteNavSystem.m_bActive || */m_nouseControl.m_eControlMode == CONTROL_MODE_DISCRETE) {
				PVI_POINT ptDiscrete = m_discreteNavSystem.updateNoseSelect(m_ptNoseRel01);
				if(m_nouseControl.m_ePointerLocation == ALWAYS_CENTER)
					ptDiscrete -= PVI_POINT(nCursorWidth / 2, nCursorWidth*3/8);
				m_nouseControl.setPointWinAbs(ptDiscrete);
			}
			else if(m_nouseControl.m_eControlMode != CONTROL_MODE_DIRECT || m_bEnoughNoseMotionOccured) {
				m_nouseControl.computePtAbsScreen(nCursorWidth, m_rectLockArea);
				if(m_bInPauseMode && m_nouseControl.m_eInWhichCorner == BOTTOM_RIGHT_OF_RECT)
					toggleInPauseMode();
			}
			else
				m_nouseControl.m_ptAbsDelta.set(0,0); 
			m_bCloseEnoughForSpecialClick = (m_ptLastClick.x != -1) && (m_nCloseClickAmount >= 0) && (m_nouseControl.m_ptWinAbs.isCloseTo(m_ptLastClick, m_nCloseClickAmount));
		}
	}

	if (m_eCurrentMode == WAITING_TO_CLICK) {
		EPointRectComparison ePointRectComparison = m_rectClickBox.comparePointToMe(m_ptNoseAbs);
		if(ePointRectComparison != INSIDE_RECT) {
			if(m_bInNouseBoard) {
				m_nouseBoard.type(ePointRectComparison);
				/*EState eStateToReturn = handleSpecialSelectedLetters();
				if(eStateToReturn != m_eWhoAmI) {
					toggleInNouseBoard();
					return eStateToReturn;
				}*/
				handleSpecialSelectedLetters();
			} else {
				click(ePointRectComparison);
			}
			setMode(FIND_GENERAL_AREA);
			return m_eWhoAmI;
		} 
	} 

	if(m_nCountDwell) { // No countdown option
		int nDiffTime = (int)difftime(time(0), m_timeTimerStart);
		m_nCountdown = ((m_eCurrentMode == WAITING_TO_CLICK)?m_nCountConfirm:m_nCountDwell) - nDiffTime;
		if(m_nCountdown <= 0)
			goToNextMode();
		else if(*m_pbEnableSounds && !m_bInPauseMode && (m_nCountdown!=((m_eCurrentMode == WAITING_TO_CLICK)?m_nCountConfirm:m_nCountDwell)) && (m_nCountdown != m_nLastCountdown))
			PlaySound(_T("sound/tick.wav"), NULL, SND_ASYNC);
		m_nLastCountdown = m_nCountdown;
	}

	handleGlueCursorBusiness();

	return m_eWhoAmI;
}

void CStateCursor::onEntrance(CPVS *pPVS) {
	m_nouseControl.m_eInWhichCorner = INSIDE_RECT; //Elan09: This represents not being in a corner
	m_nouseControl.m_bLeftCorner = true;
	m_nouseControl.m_ptWinAbs = PVI_POINT(pvu::getScreenSize() / 2);

	
	m_timeTimerStart = time(0);

	m_bDragging = false;

	setMode(FIND_GENERAL_AREA);
	
	m_nCountdown = 0;
	m_bNotMoving = false;
	
	//m_discreteNavSystem.reset();
	m_timeWhenANoMotion = time(0);
	m_bInPauseMode = false;

	m_bNeedToResetNose = false;
	m_timeLastClickMouth = time(0);
	m_bNoClickSinceClosingNouseBoard = false;
	//m_nouseMaze.activate("maze.jpg");

	m_timeLastNoseCheck = time(0);
}

void CStateCursor::onExit() {
	if(m_bInNouseBoard)
		toggleInNouseBoard();
	if(m_nouseMaze.m_bActivated)
		m_nouseMaze.deactivate();
}

void CStateCursor::setMode(ECursorMode eMode) {
	
	if(m_bInPauseMode)
		return;

	switch(eMode) {
		case FIND_GENERAL_AREA:
			m_nouseControl.m_ptTranslation = 0;
			m_nouseControl.m_eControlMode = m_nouseControl.m_eGeneralControlMode;
			if(m_nouseControl.m_eControlMode == CONTROL_MODE_DISCRETE)
				m_discreteNavSystem.reset();
			m_nouseBoard.m_bWaitingToType = false;
			break;
		case FIND_EXACT_AREA:
			m_nouseControl.m_ptTranslation = m_nouseControl.m_ptWinAbs - m_nouseControl.m_ptDirectAbs;
			m_nouseControl.m_eControlMode = CONTROL_MODE_MOUSE;
			if(m_nouseControl.m_pptEnteredYellowState) {
				delete m_nouseControl.m_pptEnteredYellowState;
				m_nouseControl.m_pptEnteredYellowState = NULL;
			}
			break;
		case WAITING_TO_CLICK:
			if(*m_pbEnableSounds)
				PlaySound(_T("sound/nousePreClick.wav"), NULL, SND_ASYNC);
			m_rectClickBox.set(*m_nouseControl.m_refImageData.m_bufPtAbs->getLast(), PVI_SIZE(CLICK_BOX_SIZE));
			m_nouseBoard.m_bWaitingToType = true;
			break;
	}
	m_eCurrentMode = eMode;
	m_timeTimerStart = time(0);
}

void CStateCursor::updateMemberVariables()
{
	switch (m_nLockOn) {
		case 0: 
			m_rectLockArea.set(cvPoint(0, 0), cvPoint(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN)));
			break;
		case 1: 
			m_rectLockArea.set(cvPoint(0, ::GetSystemMetrics(SM_CYSCREEN)/2), cvPoint(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN)));
			break;
		
		case 2: 
			m_rectLockArea.set(cvPoint(0, 0), cvPoint(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN)/2));
			break;
		
	}
	m_bEnoughNoseMotionOccured = !m_nouseControl.m_refImageData.m_bufPtAbs->didntChange(1, 5, true);
}

void CStateCursor::updatePointsBuffer(CPVS* pPVS) {
	int nMotionRangeHoriz = m_nouseControl.m_nMotionRangeHorizontal;
	int nMotionRangeVert = m_nouseControl.m_nMotionRangeVertical;
	PVI_RECT rectSearch = m_nouseControl.m_refImageData.m_pRangeMotion->getRect(nMotionRangeHoriz, nMotionRangeVert);
	m_pNouseTracker->track(pPVS, NULL, &rectSearch); //

	if(m_bUseAutoRecalibration) {
		//Elan10: Re-find nose if its support size decreased or it went out of range
		if(m_pNouseTracker->m_bSupportSizeDecreased || (m_dMaxAbsNoseRel > 1.3)) {
			/*
			if(!m_bNeedToResetNose && *m_pbEnableSounds)
				PlaySound(_T("sound/nouseFaceInCenter.wav"), NULL, SND_ASYNC);
			*/
			m_bNeedToResetNose = true;
		}

		/*
		//Elan10: Only reset once there is no motion
		if(m_bNeedToResetNose && !pPVS->m_chanMotion.imfgMHI.computeNonZeros()) {
				m_pNouseTracker->reset(PVI_POINT(160/2,120/2), pPVS);
				m_bNeedToResetNose = false;
		}
		*/

		if(m_bNeedToResetNose) {
			if(pPVS->m_fd.detectNose(&pPVS->m_imcIn)) {
				m_pNouseTracker->reset(*pPVS->m_fd.m_bufPtNose0.getLast(), pPVS);
				m_bNeedToResetNose = false;
			}
		}

		
		CTime timeNow = time(0);
		if((timeNow - m_timeLastNoseCheck).GetSeconds() >= NOSE_CHECK_INTERVAL_SECONDS) {
			m_timeLastNoseCheck = timeNow;
			if(pPVS->m_fd.detectNose(&pPVS->m_imcIn, false, 30)) {
				if(m_pNouseTracker->m_bufPtNose.getLast()->distanceToPoint(*pPVS->m_fd.m_bufPtNose0.getLast()) > NOSE_DISTANCE_TO_RESET)
					m_pNouseTracker->reset(*pPVS->m_fd.m_bufPtNose0.getLast(), pPVS);
			}
		}
		

	} else {
		m_bNeedToResetNose = false;
	}

	if(m_bLag) 
		m_ptNoseAbs	= m_pNouseTracker->m_bufPtNose.getAveraged(2, 0, true);
	else
		m_ptNoseAbs	= *m_pNouseTracker->m_bufPtNose.getLast();
	m_rectRange = m_nouseControl.m_refImageData.m_pRangeMotion->getRect(nMotionRangeHoriz, nMotionRangeVert);

	double dNotMovingSecs = 0.5 * m_nResolutionInSeconds;
	double dNotMovingInPixels = 0.5 * m_nResolutionInPixels;

	m_bNotMoving = m_pNouseTracker->m_bufPtNose.didntChange(dNotMovingSecs, dNotMovingInPixels, true); //didnt change in 1 sec with allowance of +/- 2 pixels

	if (m_bNotMoving)
		if ( m_pNouseTracker->m_bufPtNose.didntChange(dNotMovingSecs*2, dNotMovingInPixels,true) )
			m_ptNoseAbs	= m_pNouseTracker->m_bufPtNose.getAveraged(2*(dNotMovingSecs+dNotMovingInPixels), 0, false);
		else 
			m_ptNoseAbs	= m_pNouseTracker->m_bufPtNose.getAveraged(dNotMovingSecs+dNotMovingInPixels, 0, false);

	m_nouseControl.m_refImageData.putAbs(m_ptNoseAbs, nMotionRangeHoriz, nMotionRangeVert);
	
	m_ptNoseRel11 = *m_nouseControl.m_refImageData.m_bufPtRel->getLast(); 
	m_ptNoseRel01 = calculatePtCursorPct(); 

	//Elan10
	m_dMaxAbsNoseRel = pvu::max(fabs(m_ptNoseRel11.x),fabs(m_ptNoseRel11.y));

	m_rectClickBox.s.x = m_rectClickBox.s.y = m_rectRange.s.x / 12 * m_nClickBoxSize;
	
	m_ptNoseBlock =  PVI_POINT(
		pvu::discretizeNumber(m_ptNoseRel01.x, (int)NUMBER_OF_COLS, 0, 1), 
		pvu::discretizeNumber(m_ptNoseRel01.y, (int)NUMBER_OF_ROWS, 0, 1));
	int nImgWidth = *m_pnCursorWidth;
	int nImgHeight = nImgWidth * 3 / 4;
	PVI_3DPOINT ptNoseCurrent;
	ptNoseCurrent = (*m_nouseControl.m_refImageData.m_bufPtRel->getLast());
	ptNoseCurrent.x = (ptNoseCurrent.x+1)/2*160;
	ptNoseCurrent.y = (-ptNoseCurrent.y+1)/2*120;
	m_ptNoseBlockHisterethis.x = pvu::min(abs(ptNoseCurrent.x - (m_ptNoseBlock.x+1) * 160/NUMBER_OF_COLS),abs(ptNoseCurrent.x - m_ptNoseBlock.x * 160/NUMBER_OF_COLS));
	m_ptNoseBlockHisterethis.y = pvu::min(abs(ptNoseCurrent.y -(m_ptNoseBlock.y+1) * 120/NUMBER_OF_ROWS),abs(ptNoseCurrent.y -m_ptNoseBlock.y * 120/NUMBER_OF_ROWS));
}

PVI_POINT CStateCursor::calculatePtCursorPct()
{
	PVI_3DPOINT ptRel = *m_nouseControl.m_refImageData.m_bufPtRel->getLast();

	PVI_RECT rectMotionRange = m_nouseControl.m_refImageData.m_pRangeMotion->getRect(m_nouseControl.m_nMotionRangeHorizontal,m_nouseControl.m_nMotionRangeVertical );
	PVI_3DPOINT ptNoseImageAbs = *m_nouseControl.m_refImageData.m_bufPtAbs->getLast();


	PVI_POINT  ptRel0(
		(ptNoseImageAbs.x - rectMotionRange.getLeft()) / (rectMotionRange.getRight() - rectMotionRange.getLeft()),
		(ptNoseImageAbs.y - rectMotionRange.getTop()) / (rectMotionRange.getBottom() - rectMotionRange.getTop()));

	return ptRel0;
}

EState CStateCursor::handleTimers(CPVS* pPVS)
{
	if (m_bEnoughNoseMotionOccured)
		m_timeWhenANoMotion = time(0);

	double timeDiffNoChange, timeDiffNoMotion;
		timeDiffNoChange = difftime(time(0), *m_pTimeWhenCursorArrivedAtPos);
		timeDiffNoMotion = difftime(time(0), m_timeWhenANoMotion);
	if  (m_nCountDwell && (( !m_bInNouseBoard && (timeDiffNoChange > m_nTimeNochangeBackReset)) //120) // 2 minutes
		|| (timeDiffNoMotion > m_nTimeMotionBackReset ))) //Elan09: The m_nCountDwell part
		return STATE_READY;

	if((m_nouseControl.m_ptAbsDelta!= 0) || m_bEnoughNoseMotionOccured) {
		m_timeTimerStart = time(0);
	}
	return m_eWhoAmI;
}

void CStateCursor::toggleInPauseMode()
{
	if(!m_bInPauseMode) 
		setMode(FIND_GENERAL_AREA);
	m_bInPauseMode = !m_bInPauseMode;
}

PVI_POINT CStateCursor::getPointToClick() {
	PVI_POINT ptToClick = m_nouseControl.m_ptWinAbs;
	int nCursorWidth = *m_pnCursorWidth;
	if(m_nouseControl.m_nPointingCorner <= 3) {
		ptToClick.x += (m_nouseControl.m_nPointingCorner >= 2) ? nCursorWidth + CLICK_SEPARATION : -1 * CLICK_SEPARATION;
		ptToClick.y += ((m_nouseControl.m_nPointingCorner == 1) || (m_nouseControl.m_nPointingCorner == 2)) ? nCursorWidth + CLICK_SEPARATION : -1 * CLICK_SEPARATION;
	} else { //Elan09: Click in center 
		ptToClick.x += nCursorWidth / 2;
		ptToClick.y += nCursorWidth * 3 / 8; // (1/2 of 3/4)
	}
	ptToClick.normalizeToScreen();
	return ptToClick;
}

void CStateCursor::click(EPointRectComparison ePointRectComparison)
{
	//Elan09
	if(m_bInPauseMode)
		return;

	if (m_bTrialExpired)
		return;


	//Elan10
	if(m_bCloseEnoughForSpecialClick && m_bSpecialClicksEnabled) {
		handleTwoClicksCloseTogether(ePointRectComparison);
		m_ptLastClick.set(-1,-1);
		m_timeTimerStart = time(0);
		m_bCloseEnoughForSpecialClick = false;
		return;
	}

	//Elan10
	if(ePointRectComparison == LEFT_OF_RECT) 
		m_ptLastClick.set(m_nouseControl.m_ptWinAbs);

	if(*m_pbEnableSounds)
		PlaySound(_T("sound/nouseClick.wav"), NULL, SND_ASYNC);

	PVI_POINT ptToClick = getPointToClick();



	if (m_bAlwaysLeftClick)
	{
		mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, (int)ptToClick.x, (int)ptToClick.y, 0, 0);			
		mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, (int)ptToClick.x, (int)ptToClick.y, 0, 0);			
		mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, (int)ptToClick.x, (int)ptToClick.y, 0, 0);
		return;
	}

	if(m_bDragging) {
		mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, (int)ptToClick.x, (int)ptToClick.y, 0, 0);
		m_bDragging = false;
	}
	else if(ePointRectComparison == ABOVE_RECT) {
		m_ptDragLocationCursor = ptToClick;
		m_ptDragLocationNouseCursor = m_nouseControl.m_ptWinAbs;
		m_bShouldShowContextMenu = true;
	}
	else {
		int numClicks = (ePointRectComparison == BELOW_RECT) ? 2 : 1;
		bool bLeftClick = (ePointRectComparison == BELOW_RECT) || (ePointRectComparison == LEFT_OF_RECT);
		int nDownMessage = (bLeftClick) ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN;
		int nUpMessage = (bLeftClick) ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
		mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, (int)ptToClick.x, (int)ptToClick.y, 0, 0);
		for(int i=0; i<numClicks; ++i) {
			mouse_event(MOUSEEVENTF_ABSOLUTE|nDownMessage, (int)ptToClick.x, (int)ptToClick.y, 0, 0);
			mouse_event(MOUSEEVENTF_ABSOLUTE|nUpMessage, (int)ptToClick.x, (int)ptToClick.y, 0, 0);
		}
	}
	TRACE("CLICK\n");

	//Elan09
	if(m_nouseControl.m_eControlMode == CONTROL_MODE_DISCRETE)
		m_discreteNavSystem.reset();	

	//Elan10
	if(m_bNoClickSinceClosingNouseBoard) {
		if(ePointRectComparison == LEFT_OF_RECT || ePointRectComparison == BELOW_RECT) {
			Sleep(100);
			keybd_event(VK_CONTROL,0,0 , 0);
			keybd_event(VkKeyScan('v'),0,0 , 0);
			keybd_event(VkKeyScan('v'),0, KEYEVENTF_KEYUP,0);
			keybd_event(VK_CONTROL,0, KEYEVENTF_KEYUP,0);
		}
		m_bNoClickSinceClosingNouseBoard = false;
	}

	m_timeTimerStart = time(0);
}

void CStateCursor::handleTwoClicksCloseTogether(EPointRectComparison ePointRectComparison)
{
	//If the user does two left clicks in a row very close together then bring up nouse board 
	//If the user does a left click and then a right click then pause mode is enabled
	//If the user does a left click and then an "up" click, Nouse "pastes"
	/*
	if(ePointRectComparison == LEFT_OF_RECT || ePointRectComparison == BELOW_RECT || ePointRectComparison == RIGHT_OF_RECT) {
		if(m_bCloseEnoughForSpecialClick) {
			if(m_eLastClickType == LEFT_OF_RECT) {
				toggleInNouseBoard();
			} else if(m_eLastClickType == RIGHT_OF_RECT && ePointRectComparison == RIGHT_OF_RECT) {
				toggleInPauseMode();
			}
			m_ptLastClick.set(-1,-1);
			m_bCloseEnoughForSpecialClick = false;
		} else if(ePointRectComparison == LEFT_OF_RECT || ePointRectComparison == RIGHT_OF_RECT){
			m_ptLastClick.set(m_nouseControl.m_ptWinAbs);
			m_eLastClickType = ePointRectComparison;
		}
	} else {
		m_ptLastClick.set(-1,-1);
	}
	*/
	switch(ePointRectComparison) {
		case LEFT_OF_RECT:
			toggleInNouseBoard();
			break;
		case RIGHT_OF_RECT:
			toggleInPauseMode();
			break;
		case ABOVE_RECT:
			keybd_event(VK_CONTROL,0,0 , 0);
			keybd_event(VkKeyScan('v'),0,0 , 0);
			keybd_event(VkKeyScan('v'),0, KEYEVENTF_KEYUP,0);
			keybd_event(VK_CONTROL,0, KEYEVENTF_KEYUP,0);
			break;
		case BELOW_RECT:
			keybd_event(VK_RETURN,0,0 , 0);
			keybd_event(VK_RETURN,0, KEYEVENTF_KEYUP,0);
			break;
	}
}

void CStateCursor::goToNextMode()
{
	switch(m_eCurrentMode) {
		case FIND_GENERAL_AREA: {
			if(m_bEnableDwellClicking && !m_bEnableYellowState && !m_bInNouseBoard) 
				performDwellClick();
			else if(!m_bEnableYellowState || m_nouseControl.m_eControlMode == CONTROL_MODE_DISCRETE || m_bInNouseBoard)
				setMode(WAITING_TO_CLICK);
			else
				setMode(FIND_EXACT_AREA);
			break;
		}
		case FIND_EXACT_AREA:
			if(m_bEnableDwellClicking && !m_bInNouseBoard) {
				performDwellClick();
				setMode(FIND_GENERAL_AREA);
			}
			else
				setMode(WAITING_TO_CLICK);
			break;
		case WAITING_TO_CLICK:
			setMode(FIND_GENERAL_AREA);
			break;
	}
}

void CStateCursor::handleGlueCursorBusiness()
{
	// Glue cursor to nouse
	if(!m_bInNouseBoard) {// && m_bGlueCursorToNousor && g.gui.widgetList.getWidget("Enable Glue Cursor")->m_arrnCurrentValue[0]) {
	
		//Elan09: Unglue if cursor is moved by more than 5
		int nSecondsSinceCursorStoppedMoving = (int)difftime(time(0), m_timeCursorStoppedMoving);
		POINT pt;
		GetCursorPos(&pt);
		if((nSecondsSinceCursorStoppedMoving > 3) || (!m_bPauseGlue && m_ptLastActualCursorPos.isCloseTo(PVI_POINT(pt.x, pt.y), 5))) {
			m_bPauseGlue = false;

			int nCursorWidth = *m_pnCursorWidth;

			//Elan09
			if(m_nouseControl.m_eControlMode == CONTROL_MODE_DISCRETE/* || m_discreteNavSystem.m_bActive*/)
				m_nouseControl.handlePointingCorner(nCursorWidth, m_rectLockArea);

			if(m_nouseControl.m_nPointingCorner <=3) {
				SetCursorPos((m_nouseControl.m_nPointingCorner < 2) ? (int)m_nouseControl.m_ptWinAbs.x - CLICK_SEPARATION : (int)m_nouseControl.m_ptWinAbs.x + nCursorWidth + CLICK_SEPARATION, 
					((m_nouseControl.m_nPointingCorner == 0) || (m_nouseControl.m_nPointingCorner == 3)) ? (int)m_nouseControl.m_ptWinAbs.y - CLICK_SEPARATION : (int)m_nouseControl.m_ptWinAbs.y + nCursorWidth + CLICK_SEPARATION);
			}
			else { //Elan09: glue in center (1/2 of 3/4)
				SetCursorPos((int)m_nouseControl.m_ptWinAbs.x + nCursorWidth/2, (int)m_nouseControl.m_ptWinAbs.y + nCursorWidth*3/8);
			}

			GetCursorPos(&pt);
			m_timeCursorStoppedMoving = time(0);
		} else if(m_ptLastActualCursorPos != PVI_POINT(pt.x, pt.y)){
			m_timeCursorStoppedMoving = time(0);
			m_bPauseGlue = true;
		}
		m_ptLastActualCursorPos.set(pt.x, pt.y);
	}

}

bool CStateCursor::isLotsOfMotion(CPVS* pPVS)
{
	int nNonZeros = pPVS->m_chanMotion.imb_dI.computeNonZeros(NULL);
	double dMotionPercentage = 100.0*nNonZeros / (pPVS->m_chanMotion.imb_dI.size.x*pPVS->m_chanMotion.imb_dI.size.y);
	return dMotionPercentage > m_nBigMotionPercentage;
}

bool CStateCursor::isMouthClick(CPVS* pPVS)
{
	double dMouthTop = 99999;
	double dMouthBottom = -1;
	for(int i=0; i<pPVS->m_chanMotion.m_frameContent.nObjects; ++i) {
		PVI_RECT rectBlob = pPVS->m_chanMotion.m_frameContent.blobs[i].rBounding;
		if (rectBlob.comparePointToMe(m_ptNoseAbs) == ABOVE_RECT) {
			double dBlobTop = rectBlob.getTop();
			double dBlobBottom = rectBlob.getBottom();
			if(dBlobTop < dMouthTop)
				dMouthTop = dBlobTop;
			if(dBlobBottom > dMouthBottom)
				dMouthBottom = dBlobBottom;
		} else {
			return false;
		}
	}
	double dMouthBlobSize = dMouthBottom - dMouthTop;
	if(dMouthBlobSize >= m_nMinimumMouthClickHeight ) {
		CTime timeNow = time(0);
		CTimeSpan timeSinceLastMouthClick = timeNow - m_timeLastClickMouth;
		if(m_bIsMouthOpen || (timeSinceLastMouthClick.GetSeconds() < 1))
			return false;
		else {
			m_bIsMouthOpen = true;
			m_timeLastClickMouth = timeNow;
			return true;
		}
	}
	m_bIsMouthOpen = false;
	return false;
}

void CStateCursor::clickCommand(EPointRectComparison ePointRectComparison) {
	switch(m_eCurrentMode) {
		case FIND_EXACT_AREA:
		case FIND_GENERAL_AREA:
			if(m_bClickOnCommand && !m_bInNouseBoard) {
				click(ePointRectComparison);
				setMode(FIND_GENERAL_AREA);
			} else {
				setMode(WAITING_TO_CLICK); 
				m_nouseControl.m_ptAbsDelta = 0;
			}
			break;
		case WAITING_TO_CLICK:
			setMode(FIND_GENERAL_AREA);
			break;
	}
}

void CStateCursor::performDwellClick()
{
	m_dDwell.UpdateData(TRUE);
	int nClickTypeFromDialog = m_dDwell.m_nClickType;
	EPointRectComparison ePointRectComparison;
	switch(nClickTypeFromDialog) {
		case 0: ePointRectComparison = LEFT_OF_RECT; break;
		case 1: ePointRectComparison = RIGHT_OF_RECT; break;
		case 2: ePointRectComparison = BELOW_RECT; break;
		case 3: ePointRectComparison = ABOVE_RECT; break;
	}
	click(ePointRectComparison);
	m_dDwell.m_nClickType = 0;
	m_dDwell.UpdateData(FALSE);
}

void CStateCursor::handleDwellClickingDialog()
{
	if(m_bEnableDwellClicking && (!m_dDwell)) {
		m_dDwell.Create(129, CWnd::FromHandle(GetDesktopWindow()));
		m_dDwell.ShowWindow(SW_SHOW);
	}
	else if(!m_bEnableDwellClicking && m_dDwell)
		m_dDwell.DestroyWindow();
}

void CStateCursor::toggleInNouseBoard(void)
{
	if(m_bInNouseBoard) {
		m_nouseBoard.hide();
		m_nousePad.copyAndClose();
		if(m_nousePad.m_strText.GetLength())
			m_bNoClickSinceClosingNouseBoard = true;
	} else {
		m_nouseBoard.show();
		m_nousePad.m_rectBoard.set(m_nouseBoard.m_rectBoard);
		m_nousePad.Create(135, CWnd::FromHandle(GetDesktopWindow()));
		m_nousePad.ShowWindow(SW_SHOW);
		//toggleInPauseMode();
		m_nouseControl.m_nPointingCorner = 0;
	}
	m_bInNouseBoard = !m_bInNouseBoard;
}

void CStateCursor::handleSpecialSelectedLetters()
{
	/*if(!strcmp(m_nouseBoard.m_strToType, "Recalibrate")) {
		return STATE_READY;
	}
	else */if(!strcmp(m_nouseBoard.m_strToType,"Quit")) {
		toggleInNouseBoard();
	}
	else if(!strcmp(m_nouseBoard.m_strToType,"Clear")) {
		m_nousePad.clear();
	}
	else if(!strcmp(m_nouseBoard.m_strToType,"Pause")) {
		toggleInPauseMode();
	}
	//return m_eWhoAmI;
}

void CStateCursor::updateCursorLocForNouseBoard(void)
{
	if ((m_nouseBoard.m_nSelectedCol != m_ptNoseBlock.x) || (m_nouseBoard.m_nSelectedRow != m_ptNoseBlock.y))
	{
		if ((m_ptNoseBlockHisterethis.x > m_nouseBoard.m_nJitterThreshold) && (m_ptNoseBlockHisterethis.y > m_nouseBoard.m_nJitterThreshold))
		{
			m_nouseBoard.m_nSelectedCol = (int)m_ptNoseBlock.x;
			m_nouseBoard.m_nSelectedRow = (int)m_ptNoseBlock.y;
			m_nouseBoard.m_bCursorMoved = true;
			if((m_nouseBoard.m_nSelectedCol == 4) && (m_nouseBoard.m_nSelectedRow == 2) && m_bInPauseMode)
				toggleInPauseMode();
		}
	}
	if(m_bNouseCursorInBoard) {
		int nCursorWidth = *m_pnCursorWidth;
		PVI_POINT ptCursorInBoard = m_nouseBoard.getCenterOfSelectedSquare();
		ptCursorInBoard.x -= nCursorWidth/2;
		m_nouseControl.setPointWinAbs(ptCursorInBoard);// - PVI_POINT(nCursorWidth / 2, nCursorWidth * 3 / 8));
	}
	else {
		RECT rectWindow;
		CWnd* pEditBox = m_nousePad.GetDlgItem(/*IDC_EDIT1*/1009);
		pEditBox->GetWindowRect(&rectWindow);
		m_nouseControl.setPointWinAbs(PVI_POINT(m_nousePad.GetCaretPos()) + PVI_POINT(10,25) + PVI_POINT(rectWindow.left, rectWindow.top));
	}
}

void CStateCursor::handleVoiceCommand(CString strVoiceCommand)
{
	if(strVoiceCommand == "board") {
		toggleInNouseBoard();
	} else if(strVoiceCommand == "pause") {
		toggleInPauseMode();
	} else if(m_bInNouseBoard && !m_bInPauseMode) {
		bool bTypedSomething = true;
		if(strVoiceCommand == "up") {
			m_nouseBoard.type(ABOVE_RECT);
		} else if(strVoiceCommand == "down") {
			m_nouseBoard.type(BELOW_RECT);
		} else if(strVoiceCommand == "left") {
			m_nouseBoard.type(LEFT_OF_RECT);
		} else if(strVoiceCommand == "right") {
			m_nouseBoard.type(RIGHT_OF_RECT);
		} else {
			bTypedSomething = false;
		}
		if(bTypedSomething)
			handleSpecialSelectedLetters();
	} else {
		if(strVoiceCommand == "click") {
			clickCommand(LEFT_OF_RECT);
		} else if(strVoiceCommand == "right") {
			clickCommand(RIGHT_OF_RECT);
		} else if(strVoiceCommand == "double") {
			clickCommand(BELOW_RECT);
		} else if(strVoiceCommand == "drag") {
			clickCommand(ABOVE_RECT);
		} else if(m_nouseControl.m_eControlMode == CONTROL_MODE_DISCRETE) {
			if(strVoiceCommand == "northwest") {
				m_nouseControl.setPointWinAbs(m_discreteNavSystem.jump(NORTH_WEST));
			} else if(strVoiceCommand == "northeast") {
				m_nouseControl.setPointWinAbs(m_discreteNavSystem.jump(NORTH_EAST));
			} else if(strVoiceCommand == "southwest") {
				m_nouseControl.setPointWinAbs(m_discreteNavSystem.jump(SOUTH_WEST));
			} else if(strVoiceCommand == "southeast") {
				m_nouseControl.setPointWinAbs(m_discreteNavSystem.jump(SOUTH_EAST));
			} else if(strVoiceCommand == "north") {
				m_nouseControl.setPointWinAbs(m_discreteNavSystem.jump(NORTH));
			} else if(strVoiceCommand == "south") {
				m_nouseControl.setPointWinAbs(m_discreteNavSystem.jump(SOUTH));
			} else if(strVoiceCommand == "west") {
				m_nouseControl.setPointWinAbs(m_discreteNavSystem.jump(WEST));
			} else if(strVoiceCommand == "east") {
				m_nouseControl.setPointWinAbs(m_discreteNavSystem.jump(EAST));
			} else if(strVoiceCommand == "reset") {
				m_discreteNavSystem.reset();
			} else if(strVoiceCommand == "jump" && m_discreteNavSystem.m_eDiscreteNavType == MAPPING_TO_QUADRANTS) {
				m_discreteNavSystem.jump();
			}
		}  
	}
}
