#include "StdAfx.h"
#include "StateReady.h"


CStateReady::CStateReady(void) : 
m_bActWithFaceDetection(true),
m_dHeadWidth(0.25),
m_nFaceDetectionType(0),
m_nFacesInARow(0)
{
	m_eWhoAmI = STATE_READY;
}


CStateReady::~CStateReady(void)
{
}

void CStateReady::onEntrance(CPVS* pPVS) {
	m_nFacesInARow = 0;
	pPVS->m_bRectZoomInSet = false;
	m_rectLastFaceDetected.set(-1,-1,-1,-1);
}

EState CStateReady::processData(CPVS* pPVS) {
	if (!m_bActWithFaceDetection)
	{
		PVI_RECT rectRange = *pPVS->m_fd.m_bufRectFace0.getLast(); 
		rectRange.c = PVI_POINT(160/2,120/2);
		rectRange.s =  PVI_POINT(160*m_dHeadWidth,120*m_dHeadWidth);

		rectRange.adjustToImage(pPVS->m_imcIn.p);
		pPVS->setRectZoomInFromMotionRange(rectRange);
		
		// Set the range
		m_pNouseControl->m_rangeMotion.set(&rectRange, NULL);
		return STATE_CALIBRATION;
	}
	
	
	pPVS->m_fd.m_nFacesDetected = pPVS->m_fd.detectFaces(&pPVS->m_imcOri160, m_nFaceDetectionType);	
	if (pPVS->m_fd.m_nFacesDetected > 0)
	{
		//Elan09: The || part: The user needs to be still
		if ( m_nFacesInARow < NUM_FACES_IN_A_ROW_REQUIRED || (pPVS->m_chanMotion.imb_sumDI.computeNonZeros() > 10))  
		{
			//PVI_RECT r = *pPVS->m_fd.m_bufRectFace0.getLast();
			
			//pPVS->m_tracker[0].learnColour (&pPVS->m_chanColour, &r, NULL, NULL, PVS_OBJECT_SKIN, PVS_COLOUR_HCr);
			//pPVS->m_tracker[0].m_bAccumulate = true; 
			//PVI_RECT rectFace = *pPVS->m_tracker[0].m_bufRectSkin.getLast();
			//if (rectFace.s >= pPVS->m_imcOut.p->width /4)
			PVI_RECT rectFace = *pPVS->m_fd.m_bufRectFace0.getLast();//*pPVS->m_tracker[0].m_bufRectSkin.getLast();
			pvu::drawRectangle(	pPVS->m_imcOut.p, rectFace, cvScalar(200), 1, pvu::i2s(m_nFacesInARow));
			//if((rectFace.s >= pPVS->m_imcOut.p->width /4) && ((m_rectLastFaceDetected.c.x < 0) || (rectFace.comparePointToMe(m_rectLastFaceDetected.c)==INSIDE_RECT)))
			//{
				//TODO: This should be in NouseCursor::redraw
				m_nFacesInARow++;
			//} else {
			//	m_nFacesInARow = 0;
			//}
			m_rectLastFaceDetected = rectFace;
		} 
		else {
			// Calculate range in original
			PVI_RECT rectRange = *pPVS->m_fd.m_bufRectFace0.getLast(); // *pPVS->m_tracker[0].m_bufRectSkin.getLast();

			int iod = (int)rectRange.s.x / 8;
			rectRange.c.y += iod; // 
			
			rectRange.s *= PVI_SIZE(0.6,0.3); //ELAN: THE ONE FOR NOSE				



			rectRange.adjustToImage(pPVS->m_imcIn.p);

			pPVS->setRectZoomInFromMotionRange(rectRange);

			// Calculate new range
			rectRange.c = PVI_POINT(160/2,120/2);// + g.n120_Y*0.20);
			double nOriginalWidthToZoomWidth = pPVS->m_imcOriginal.getWidth() / pPVS->m_rectZoomIn.s.x;
			rectRange.s *=  nOriginalWidthToZoomWidth;

			rectRange.adjustToImage(pPVS->m_imcIn.p);

			// Set the range
			m_pNouseControl->m_rangeMotion.set(&rectRange, NULL);

			return STATE_CALIBRATION;
		}

	}
	
	else {
		//Elan09: Stay in same state but reset the faces count
		m_nFacesInARow = 0;
	}

	return m_eWhoAmI;
}
