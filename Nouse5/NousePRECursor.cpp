#include "StdAfx.h"
#include "NousePRECursor.h"

CNousePRECursor::CNousePRECursor(void)
{
	m_ptLocation.set(-1,-1);
	m_hwnd = NULL;

	m_hInstance = GetModuleHandle(NULL);
	registerWindowClass(m_hInstance);
}


CNousePRECursor::~CNousePRECursor(void)
{
}


bool CNousePRECursor::create(int nWidth, ETranslucenceType eTranslucenceType) {

	if(m_hwnd) return false;

	m_nWidth = nWidth;

	
	
	int X = GetSystemMetrics(SM_CXSCREEN)/2 - m_nWidth/2;
	int Y = GetSystemMetrics(SM_CYSCREEN)/2 - m_nWidth/2;


	

	DWORD wsStyle =  WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT;

	
	m_hwnd = CreateWindowEx(wsStyle, _T("NouseCursor"), NULL, WS_POPUP, X, Y, m_nWidth, m_nWidth, 0, 0, NULL, NULL);


	SetLayeredWindowAttributes( m_hwnd,     // handle to window to modify
                                0,          // color key (not used when using LWA_ALPHA)
								255,       // "amount of solidness" = 0=transparent, 255=completely solid
                                LWA_ALPHA );// use my alpha value (prev arg)
                                            // to tell how see 'solid' window is.


	if(!m_hwnd) {
		MessageBox(0,_T("X"),_T("X"),MB_OK);
		return false;
	}

	// Ask the window and its children to repaint
	RedrawWindow(m_hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);

	if (m_hwnd) 
	{	
		SetForegroundWindow(m_hwnd); 
		::SetWindowPos(m_hwnd, HWND_TOPMOST, (int)m_ptLocation.x, (int)m_ptLocation.y, 0, 0, SWP_NOSIZE);
	}

	

	return 1;
}

void CNousePRECursor::show() {
	if(m_hwnd == NULL) return;
	ShowWindow(m_hwnd, SW_SHOW);
}

void CNousePRECursor::hide() {
	if(m_hwnd == NULL) return;
	ShowWindow(m_hwnd, SW_HIDE);
}


bool CNousePRECursor::destroy() {
	return false;
}

void CNousePRECursor::redraw(CState* pState, CPVS* pPVS) {
	pState->m_eWhoAmI == STATE_READY
	CStateReady* pStateReady = NULL;
	CStateCalibration* pStateCalibration = NULL;
	CStateCursor* pStateCursor = NULL;
	ECursorMode eCursorMode;
	switch(pState->m_eWhoAmI) {
		case STATE_READY:
			pStateReady = (CStateReady*)pState;
			break;
		case STATE_CALIBRATION:
			pStateCalibration = (CStateCalibration*)pState;
			break;
		case STATE_CURSOR:
			pStateCursor = (CStateCursor*)pState;
			eCursorMode = pStateCursor->m_eCurrentMode;
			break;
	}

	clearStrings();

	::BitBlt(m_image.getDC(), 0, 0, m_cameraImage32x24.getWidth(), m_cameraImage32x24.getHeight(), m_cameraImage32x24.getDC(), 0, 0, SRCCOPY);
	m_pImc = m_cameraImage32x24.getIplImage(); 
	m_pImcNow = m_image.getIplImage();

	int nCursorSize = CURSOR_INCR_SIZE * ((pState->m_eWhoAmI == STATE_CALIBRATION || pState->m_eWhoAmI == STATE_READY)?10:m_nCursorSize);

	bool bInCursorStateAndNeedToResetNose = (pState->m_eWhoAmI == STATE_CURSOR) && (pStateCursor->m_bNeedToResetNose);
	bool bTranslucentSolidnessAmountChanged = m_nCurrentTranslucentSolidness != m_nTranslucentSolidness;
	bool bNeedsToChangeToSolid = (m_eCurrentTranslucenceType != SOLID) && ((pState->m_eWhoAmI != STATE_CURSOR)||!m_bUseTranslucentCursor);//||bInCursorStateAndNeedToResetNose);
	bool bNeedsToChangeToTranslucent = (m_eCurrentTranslucenceType != TRANSLUCENT) && pState->m_eWhoAmI == STATE_CURSOR && m_bUseTranslucentCursor && !bInCursorStateAndNeedToResetNose;
	bool bNeedsToChangeToInvisible = (m_eCurrentTranslucenceType != INVISIBLE) && pState->m_eWhoAmI == STATE_CURSOR && pStateCursor->m_bInPauseMode;
	bool bNeedToChangeTranslucency = bTranslucentSolidnessAmountChanged || bNeedsToChangeToSolid || bNeedsToChangeToTranslucent || bNeedsToChangeToInvisible;
	if(!m_hwnd || (m_nWidth != nCursorSize) || bNeedToChangeTranslucency) {
		destroy();
		ETranslucenceType eTranslucenceType;
		if(pState->m_eWhoAmI == STATE_CURSOR && pStateCursor->m_bInPauseMode)
			eTranslucenceType = INVISIBLE;
		else if(pState->m_eWhoAmI == STATE_CURSOR && m_bUseTranslucentCursor && !bInCursorStateAndNeedToResetNose)
			eTranslucenceType = TRANSLUCENT;
		else 
			eTranslucenceType = SOLID;
		create(nCursorSize, eTranslucenceType);
		show();
		return;
	}


	CvPoint pt1, pt2;
	pt1.x = 0 ;	pt1.y = 0;
	pt2.x = m_nWidth-1; pt2.y = m_nWidthThreeQuarters - 1;
	CvScalar clrMainCur = CV_RGB(0,0,0);
	cvRectangle( m_pImc, pt1, pt2, clrMainCur, 1);

	if(pState->m_eWhoAmI == STATE_CURSOR) {
		if ( pStateCursor->m_bNeedToResetNose) {
			IplImage* pImageIn = pPVS->m_imcIn.p; 
			pStateCursor->m_rectRange.adjustToImage(pImageIn);
			cvSetImageROI( pImageIn, pStateCursor->m_rectRange.rect() );
			cvResize(pImageIn, m_pImc, CV_INTER_LINEAR);
			cvResetImageROI(pImageIn);
		}
		else {// show grey	
			cvSet (m_pImc, cvScalar(200,200,200));
		}
	} else 
		cvResize(pPVS->m_imcOut.p, m_pImc, CV_INTER_LINEAR);

	PVI_POINT ptScreenSize = pvu::getScreenSize();
	PVI_POINT ptTopMiddle = PVI_POINT(ptScreenSize.x/2 - m_nWidth/2, 0);
	PVI_POINT ptCenter = (ptScreenSize / 2) - (m_nWidth/2);

	setPos(pState->m_eWhoAmI == STATE_READY ? ptTopMiddle : pState->m_eWhoAmI == STATE_CALIBRATION ? ptCenter : pStateCursor->m_nouseControl.m_ptWinAbs);

	PVI_POINT ptZero;
	ptZero.x = m_nWidth / 2;
	ptZero.y = m_nWidthThreeQuarters / 2;

	if(pState->m_eWhoAmI != STATE_READY) {
		CvScalar crossColor = (pStateCursor && pStateCursor->m_nouseControl.m_ePointerLocation == ALWAYS_CENTER && eCursorMode == WAITING_TO_CLICK)?cvScalar(0,255,0):cvScalar(0);
		pvu::drawPoint(m_pImc, ptZero, PVI_PLUS, crossColor ,20);
	}

	if(pState->m_eWhoAmI == STATE_READY) {
	} else if(pState->m_eWhoAmI == STATE_CALIBRATION) {


		if (pStateCalibration->m_bInConfirmingStage) {
			
			// draw Nose:	
			pvu::drawPoint(m_pImc, *(pStateCalibration->m_pNouseTracker->m_bufPtNose.getLast()) * ((double)m_nWidth/160),PVI_O, cvScalar(0, 0,255), 10,-1);			
							
			PVI_RECT rectConfirm;
			rectConfirm.c = ptZero;
			rectConfirm.s = PVI_POINT(pStateCalibration->m_rectConfirm.s.x * m_nWidth / 160, pStateCalibration->m_rectConfirm.s.y * m_nWidthThreeQuarters / 120);
			CvScalar colorBlue = cvScalar(200);
			pvu::drawRectangle(m_pImc, rectConfirm, colorBlue, 2);
		}
		else {
			cvLine(m_pImc, cvPoint(0, (int)ptZero.y), cvPoint(m_nWidth, (int)ptZero.y), CV_RGB(0,200,0), 4);
			cvLine(m_pImc, cvPoint((int)ptZero.x, 0), cvPoint((int)ptZero.x, m_nWidth*3/4), CV_RGB(0,200,0), 4);
		}
	} else if(pState->m_eWhoAmI == STATE_CURSOR) {
		if(pStateCursor->m_bInNouseBoard) {
			if(!pStateCursor->m_nouseBoard.redrawWindow()) {
				//Elan10: Todo: This should probably be done in the CStateCursor class
				pStateCursor->toggleInNouseBoard();
			}
		}
		else {
			//Elan09
			if (/*pStateCursor->m_discreteNavSystem.m_bActive || */(!pStateCursor->m_bInNouseBoard && pStateCursor->m_nouseControl.m_eControlMode == CONTROL_MODE_DISCRETE)) {
				pStateCursor->m_discreteNavSystem.drawCurrentRect();
			}
		}

		CvScalar colour; 
		// Pointing corner 
		if (eCursorMode == WAITING_TO_CLICK)
			colour = CV_RGB(0,255,0);		// Green
		else
			colour = CV_RGB(160,32,240);		// purple
		int nWidth = (20*m_nWidth) / 160;
		PVI_RECT rectClickCorner;
		rectClickCorner.s = PVI_POINT(m_nWidth / 2 - 2, m_nWidthThreeQuarters / 2 - 2);
		switch (pStateCursor->m_nouseControl.m_nPointingCorner) {
			case 0: 
				cvLine(m_pImc, cvPoint(0,0), cvPoint(m_nWidth/2,0), colour, nWidth);
				cvLine(m_pImc, cvPoint(0,0), cvPoint(0, m_nWidth/2), colour, nWidth);
				break;
			case 1: 
				cvLine(m_pImcNow, cvPoint(0,m_nWidth), cvPoint(m_nWidth/2,m_nWidth), colour, nWidth);
				cvLine(m_pImcNow, cvPoint(0,m_nWidth), cvPoint(0, m_nWidth/2), colour, nWidth);
				break;
			case 2: 
				cvLine(m_pImcNow, cvPoint(m_nWidth,m_nWidth), cvPoint(m_nWidth/2,m_nWidth), colour, nWidth);
				cvLine(m_pImcNow, cvPoint(m_nWidth,m_nWidth), cvPoint(m_nWidth, m_nWidth/2), colour, nWidth);
				break;
			case 3: 
				cvLine(m_pImcNow, cvPoint(m_nWidth,0), cvPoint(m_nWidth/2,0), colour, nWidth);
				cvLine(m_pImcNow, cvPoint(m_nWidth,0), cvPoint(m_nWidth, m_nWidth/2), colour, nWidth);
				break;
		}
		
		//Red circle around nose
		int size = m_nWidth / 32  * pStateCursor->m_nResolutionInPixels; 
		nWidth = int(1.5 * m_nWidth / 32); 
		PVI_3DPOINT ptNose(pStateCursor->m_ptNoseRel01.x*m_nWidth, pStateCursor->m_ptNoseRel01.y*m_nWidthThreeQuarters);
		colour = cvScalar(0, 0,185);
		if (pStateCursor->m_bNotMoving) 
			colour = cvScalar(0, 0,255);
		int nShape = PVI_O; 
		if(pStateCursor->m_dMaxAbsNoseRel >=1) {
			colour = cvScalar(0,  120,215);
			nWidth = 2 * m_nWidth / 32;
		}
		pvu::drawPoint(m_pImc, ptNose, 	nShape, colour, 	size,	nWidth);	

		if(eCursorMode == WAITING_TO_CLICK) {
			PVI_RECT rectClick;
			int nX, nY;			// map the abs position to the output image
			nX =  int(m_nWidth*(pStateCursor->m_rectClickBox.c.x - pStateCursor->m_rectRange.getLeft()) / (pStateCursor->m_rectRange.getRight() - pStateCursor->m_rectRange.getLeft()));
			nY =  int(m_nWidthThreeQuarters*(pStateCursor->m_rectClickBox.c.y - pStateCursor->m_rectRange.getTop()) / (pStateCursor->m_rectRange.getBottom() - pStateCursor->m_rectRange.getTop()));
			rectClick.c = PVI_POINT(nX, nY);
			rectClick.s = pStateCursor->m_rectClickBox.s *m_nWidth / pStateCursor->m_rectRange.s.x;		//*m_nWidth/g.n160_X;
			pvu::drawRectangle(m_pImc, rectClick, cvScalar(255, 255, 55), 4);
		}

	}


/*vScalar colorText = cvScalar(0, 255, 255);
	int size0 = int(0.6 * m_nWidth / 32);
	int width0 = m_nWidth / 32;
	pvu::drawText(m_pImcNow, m_strHelpLine, 6,  colorText, size0, width0);
	pvu::drawText(m_pImc, m_strCountdown, cvPoint(-2,0),  cvScalar(0,0,250), size0*2, width0);
	pvu::drawText(m_pImcNow, m_strDragging, 1,  colorText, size0, width0);
	pvu::drawText(m_pImcNow, m_strCursorCloseEnoughForBoard, 1,  colorText, size0, width0);
	*/
	::BitBlt( ::GetDCEx(m_hwnd, NULL ,DCX_WINDOW),
			0,
			0, 
			300,
			300,
			m_image.getDC(), 
			0, 0, SRCCOPY);

	if((pState->m_eWhoAmI == STATE_CURSOR) && (pStateCursor->m_bInNouseBoard) && (pStateCursor->m_nouseBoard.m_bCursorMoved)) {		
		pStateCursor->m_nousePad.RedrawWindow();
	}
}






void CNousePRECursor::setPos(PVI_POINT pt) {
	if(m_hwnd == NULL) return;
	if(pt == m_ptLocation) return;
	m_ptLocation = pt;

	::SetWindowPos(m_hwnd, HWND_TOPMOST, (int)m_ptLocation.x, (int)m_ptLocation.y, 0, 0, SWP_NOSIZE);
}


ATOM CNousePRECursor::registerWindowClass(HMODULE hInstance) {
	WNDCLASSA wc;
 	wc.style         = CS_DBLCLKS | CS_OWNDC; 
	wc.lpfnWndProc   = (WNDPROC)customWinProc;
	wc.cbClsExtra    = 0; 
	wc.cbWndExtra    = 0; 
	wc.hInstance     = hInstance; 
	wc.hIcon         = NULL; 
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW); 
	wc.hbrBackground = NULL; 
	wc.lpszMenuName  = NULL; 
	wc.lpszClassName = "NouseCursor"; 
	return RegisterClassA(&wc);
}

LRESULT CALLBACK CNousePRECursor::customWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		case WM_PAINT:
			//m_pObj->redraw();
			break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


