#include "StdAfx.h"
#include "StateCalibration.h"


CStateCalibration::CStateCalibration(void) :
m_nCountConfirm(3),
m_bQuickCalibrate(false),
m_nClickBoxSize(1),
m_nCountCalibrateSelect(5)
{
	m_eWhoAmI = STATE_CALIBRATION;
}


CStateCalibration::~CStateCalibration(void)
{
}

void CStateCalibration::onEntrance(CPVS* pPVS) {
	m_timeTimerStart = time(0);
	m_bInConfirmingStage = false;
	m_nCountdown = 0;
	m_pNouseControl->m_refImageData.m_pRangeMotion = &m_pNouseControl->m_rangeMotion;
	if(*m_pbEnableSounds)
		PlaySound(_T("sound/nouseShowNose.wav"), NULL, SND_ASYNC);
}

EState CStateCalibration::processData(CPVS* pPVS) {
	int nTimerSeconds = int(difftime(time(0), m_timeTimerStart));
	
	if(m_bQuickCalibrate) {
		if(pPVS->m_fd.detectNose(&pPVS->m_imcIn)) {
			PVI_POINT ptNose = *pPVS->m_fd.m_bufPtNose0.getLast();//m_pNouseControl->m_rangeMotion.ptZero;
			PVI_RECT rectFace = *pPVS->m_fd.m_bufRectFace0.getLast();
			m_pNouseTracker->learn(ptNose, rectFace, pPVS, NULL); 
			return STATE_CURSOR;
		}	
	} else if(m_bInConfirmingStage) {
		//TRACE("CONFIRMING\n");
		
		PVI_BUFFER<PVI_3DPOINT>* bufPts = m_pNouseControl->m_refImageData.m_bufPtAbs;
		
		m_nCountdown = m_nCountConfirm - nTimerSeconds;
		
		PVI_RECT rectSearch = m_pNouseControl->m_refImageData.m_pRangeMotion->getRect(m_pNouseControl->m_nMotionRangeHorizontal, m_pNouseControl->m_nMotionRangeVertical);
		m_pNouseTracker->track(pPVS, NULL, &rectSearch);
		m_pNouseControl->m_refImageData.putAbs(*m_pNouseTracker->m_bufPtNose.getLast(), m_pNouseControl->m_nMotionRangeHorizontal, m_pNouseControl->m_nMotionRangeVertical);
		

		//Elan09
		bool bEnoughPointsInBuffer = bufPts->m_nNumElements > 5;
		if(!m_nCountConfirm)
			return bEnoughPointsInBuffer ? STATE_CURSOR : m_eWhoAmI;

		
		//Elan09
		m_rectConfirm.c = PVI_POINT(160/2, 120/2);
		m_rectConfirm.s = PVI_POINT(160 * m_nClickBoxSize / 10.0, 120 * m_nClickBoxSize / 10.0);
		

		EPointRectComparison ePointRectComparison = m_rectConfirm.comparePointToMe(*bufPts->getLast());
		
		//Elan09: Put in 2nd half of and so it will work correctly when the buffer starts empty
		if(ePointRectComparison != INSIDE_RECT && bEnoughPointsInBuffer) 
			return STATE_CURSOR;
		
		
	
		if(m_nCountdown <= 0) 
			return STATE_READY;
	} else {
		//TRACE("COUNTDOWN\n");
		m_nCountdown = m_nCountCalibrateSelect - nTimerSeconds;
		
		/*
		// Elan09
		if (m_bQuickCalibrate) {
			m_nCountdown = 0;
		}	
		*/

		if(m_nCountdown <= 0) {
			PVI_POINT ptNose = m_pNouseControl->m_rangeMotion.ptZero;
			PVI_RECT rectFace = *pPVS->m_fd.m_bufRectFace0.getLast();

			m_pNouseTracker->learn(ptNose, rectFace, pPVS, NULL); 

			m_timeTimerStart = time(0);
			m_bInConfirmingStage = true;
			if(*m_pbEnableSounds)
				PlaySound(_T("sound/nouseConfirm.wav"), NULL, SND_ASYNC);
		}
	}
	
	return m_eWhoAmI;
}