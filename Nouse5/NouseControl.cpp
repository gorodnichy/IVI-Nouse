#include "StdAfx.h"
#include "NouseControl.h"


CNouseControl::CNouseControl(void) :
m_nPctStopJoystick(20),
m_nCursorSpeed(3),
m_nMotionRangeHorizontal(5),
m_nMotionRangeVertical(5),
m_pptEnteredYellowState(NULL)
{
	m_ePointerLocation = MOVES;
	m_eDiscreteDirection = ALL_DIRECTIONS;
	m_eControlMode = m_eGeneralControlMode = CONTROL_MODE_JOYSTICK;
}


CNouseControl::~CNouseControl(void)
{
}

void CNouseControl::setPointWinAbs(PVI_POINT pt)
{
	PVI_POINT ptOldWinAbs = m_ptWinAbs;
	m_ptWinAbs = pt;
	m_ptAbsDelta = m_ptWinAbs - ptOldWinAbs;
}

void CNouseControl::computePtAbsScreen(int nCursorWidth, PVI_RECT rectLockArea)
 // takes position in 160x120 image !
{

	if((rectLockArea.c == PVI_POINT(-1, -1)) || (rectLockArea.s == PVI_POINT(-1, -1))) {
		PVI_SIZE vtScreenSize = pvu::getScreenSize();
		rectLockArea.set(0, 0, vtScreenSize.x, vtScreenSize.y);
	}
	if (m_ePointerLocation == ALWAYS_TOPLEFT)
	{
		rectLockArea.c += PVI_POINT(nCursorWidth/2-6,nCursorWidth/2-6);
		rectLockArea.s += PVI_POINT(nCursorWidth-12,nCursorWidth-12);
	} else if(m_ePointerLocation == ALWAYS_CENTER) {
		rectLockArea.set(rectLockArea.getLeft()-nCursorWidth/2, rectLockArea.getTop()-nCursorWidth*3/8, rectLockArea.s.x + nCursorWidth, rectLockArea.s.y + nCursorWidth);
	}
	
	int nLeft = (int)rectLockArea.getLeft();
	int nRight = (int)rectLockArea.getRight();
	int nTop = (int)rectLockArea.getTop();
	int nBottom = (int)rectLockArea.getBottom();
	
	PVI_POINT ptInRelCurrent = (m_eControlMode == CONTROL_MODE_DIRECT) ?
		m_refImageData.m_bufPtRel->getAveraged(3,0, false) : 
		*m_refImageData.m_bufPtRel->getLast();//refImageData.ptNoseRelCurrent;
 
	if (m_eDiscreteDirection == FOUR_DIRECTIONS_CROSS ) // go as Turk 
	{
		if ( fabs(ptInRelCurrent.x) < fabs(ptInRelCurrent.y) )
			ptInRelCurrent.x = 0;
		else 
			ptInRelCurrent.y = 0;
	}
	
	else if (m_eDiscreteDirection == EIGHT_DIRECTIONS) // go as Queen
	{
		if ( fabs(ptInRelCurrent.x) <  fabs(ptInRelCurrent.y)/2 )
			ptInRelCurrent.x = 0;
		else if ( fabs(ptInRelCurrent.y) <  fabs(ptInRelCurrent.x)/2 )
			ptInRelCurrent.y = 0;
		else
			if  ( (ptInRelCurrent.x > 0 && ptInRelCurrent.y > 0) || (ptInRelCurrent.x < 0 && ptInRelCurrent.y < 0) )
				ptInRelCurrent.x = ptInRelCurrent.y;
			else
				ptInRelCurrent.x = - ptInRelCurrent.y;
	}



	PVI_POINT ptOldWinAbs = m_ptWinAbs;

	if (m_eControlMode == CONTROL_MODE_DIRECT)	//Input /// old -> is from 0.0 to +1.0
	{
		m_ptDirectAbs.x = (int)(rectLockArea.c.x  + rectLockArea.s.x/2*ptInRelCurrent.x);
		m_ptDirectAbs.y = (int)(rectLockArea.c.y - rectLockArea.s.y/2*ptInRelCurrent.y);
		//since windows (0,0) is on the top
		m_ptWinAbs = m_ptDirectAbs + m_ptTranslation;
	}
	else if (m_eControlMode == CONTROL_MODE_JOYSTICK) //Input is from -1.0 to +1.0
	{
		m_ptWinAbs += PVI_POINT(delta(ptInRelCurrent.x, 5), -delta(ptInRelCurrent.y, 3));//m_ptDelta;
	}
	
	else // CONTROL_MODE_MOUSE
	{
		PVI_POINT ptInRelLast = *m_refImageData.m_bufPtRel->getLast(5);

		//Elan09
		if(m_pptEnteredYellowState == NULL)
			m_pptEnteredYellowState = new PVI_POINT(ptInRelLast);

		if  ((ptInRelLast.x > m_pptEnteredYellowState->x   &&   ptInRelCurrent.x > ptInRelLast.x) ||
			 (ptInRelLast.x < m_pptEnteredYellowState->x   &&   ptInRelCurrent.x < ptInRelLast.x) )
			m_ptWinAbs.x += (int)delta(ptInRelCurrent.x - ptInRelLast.x); // delta(refIn.currentRel)

		if  ((ptInRelLast.y > m_pptEnteredYellowState->y  &&   ptInRelCurrent.y > ptInRelLast.y) ||
			 (ptInRelLast.y < m_pptEnteredYellowState->y   &&   ptInRelCurrent.y < ptInRelLast.y) )
			m_ptWinAbs.y -= (int)delta(ptInRelCurrent.y - ptInRelLast.y); // delta(refIn.currentRel) //since windows (0,0) is on the top
	}
	
	double dBufferZone = nCursorWidth/2;

	PVI_POINT ptCursorCenter = m_ptWinAbs + dBufferZone;

	if ( m_ptWinAbs.x < nLeft) m_ptWinAbs.x = nLeft;
	if ( m_ptWinAbs.y <nTop) m_ptWinAbs.y = nTop;

	int nEdgeBuffer = nCursorWidth;
	if ( m_ptWinAbs.x > nRight-nEdgeBuffer) m_ptWinAbs.x = nRight  - nEdgeBuffer; // so that you can still see it
	if ( m_ptWinAbs.y > nBottom-nEdgeBuffer ) m_ptWinAbs.y = nBottom - nEdgeBuffer;

	m_ptAbsDelta = m_ptWinAbs - ptOldWinAbs;
	
	bool bStartedInCorner = m_eInWhichCorner != INSIDE_RECT; //Elan09: INSIDE_RECT represents not being in a corner
	if((m_ptWinAbs.x == nLeft) && (m_ptWinAbs.y == nTop))
		m_eInWhichCorner = TOP_LEFT_OF_RECT;
	else if((m_ptWinAbs.x == nLeft) && (m_ptWinAbs.y == nBottom - nCursorWidth))
		m_eInWhichCorner = BOTTOM_LEFT_OF_RECT;
	else if((m_ptWinAbs.x == nRight  - nCursorWidth) && (m_ptWinAbs.y == nTop))
		m_eInWhichCorner = TOP_RIGHT_OF_RECT;
	else if((m_ptWinAbs.x == nRight  - nCursorWidth) && (m_ptWinAbs.y == nBottom - nCursorWidth))
		m_eInWhichCorner = BOTTOM_RIGHT_OF_RECT;
	else
		m_eInWhichCorner = INSIDE_RECT; // Not in corner

	if(bStartedInCorner)
		m_bLeftCorner = m_eInWhichCorner == INSIDE_RECT;

	handlePointingCorner(nCursorWidth, rectLockArea);
}

double CNouseControl::delta(double x, int nDimensions)
{
	double abs = fabs(x);
	double sign = x > 0 ? +1 : -1;

	double y;
	if(m_eControlMode == CONTROL_MODE_JOYSTICK) {
		double pct = m_nPctStopJoystick / 100.00;
		double intervalSize = (1-pct) / 6;
		y = (abs < pct) ? 0 : sign*pow(2,(abs - pct)/intervalSize);
	}
	else { //CONTROL_MODE_MOUSE 
		y = 
			abs > 0.9 ? 8*sign :
			abs > 0.5 ? 4*sign:
			abs > 0.1 ? 2*sign:
			abs > 0.07 ? 1 *sign:
			0;
	}

	//Elan09: Put in hard coded number for non-joystick mode. Why should the "cursor speed" have anything to do with the yellow state movement?
	int nCursorSpeed = (m_eControlMode == CONTROL_MODE_JOYSTICK)?m_nCursorSpeed:3;
	return y * nCursorSpeed / 3;	
}

void CNouseControl::handlePointingCorner(int nCursorWidth, PVI_RECT rectLockArea)
{
	bool bPosOnLeft, bPosOnTop;
	double dBufferZone = nCursorWidth/2;
	PVI_POINT ptCursorCenter = m_ptWinAbs + dBufferZone;
	int nRight = (int)rectLockArea.getRight();
	int nBottom = (int)rectLockArea.getBottom();

	if (m_ePointerLocation == ALWAYS_TOPLEFT)
		m_nPrePointingCorner = m_nPointingCorner = 0;		// if corner change is not allowed, lock the pointer to left-top corner
	else if(m_ePointerLocation == MOVES)
	{
		if(ptCursorCenter.x < (nRight - 2* nCursorWidth))		// an cache area of nCursorWidth/2 is used to avoid jitter
			bPosOnLeft = true;
		else if(ptCursorCenter.x >= (nRight - dBufferZone))
			bPosOnLeft = false;
		else
			bPosOnLeft = (m_nPrePointingCorner <= 1)?  true: false;

		if(ptCursorCenter.y < (nBottom - 2*nCursorWidth))
			bPosOnTop = true;
		else if(ptCursorCenter.y >= (nBottom - dBufferZone))
			bPosOnTop = false;
		else
			bPosOnTop = (m_nPrePointingCorner <= 2 && m_nPrePointingCorner >= 1)?  false: true;
		m_nPointingCorner = (bPosOnLeft) ? ((bPosOnTop) ? 0 : 1) : ((bPosOnTop) ? 3 : 2);
		m_nPrePointingCorner = m_nPointingCorner;
	} else {// Elan09: ALWAYS_CENTER
		m_nPrePointingCorner = m_nPointingCorner = 4;
	}
}
