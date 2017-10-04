// DiscreteNavSystem.cpp: implementation of the CDiscreteNavSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiscreteNavSystem.h"

EJumpDirection convertPointRectComparisonToJumpDirection(EPointRectComparison ePointRectComparison) {
	switch(ePointRectComparison) {
		case ABOVE_RECT: return NORTH;
		case BELOW_RECT: return SOUTH;
		case BOTTOM_LEFT_OF_RECT: return SOUTH_WEST;
		case BOTTOM_RIGHT_OF_RECT: return SOUTH_EAST;
		case LEFT_OF_RECT: return WEST;
		case RIGHT_OF_RECT: return EAST;
		case TOP_LEFT_OF_RECT: return NORTH_WEST;
		case TOP_RIGHT_OF_RECT: return NORTH_EAST;
		default: return NORTH;
	}
}

// TODO: Add points for 8 sides of screen. If you go to one of those, jump to the parent window.
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
	CDiscreteNavSystem* This = (CDiscreteNavSystem*)lParam;
	RECT r;
	GetWindowRect(hwnd, &r);
	PVI_RECT pviRect(r);
	
	EPointRectComparison ePointRectComparison = This->m_rectCurrent.comparePointToMe(pviRect.c, This->m_eComparisonType, false);
	EJumpDirection eJumpDirection = convertPointRectComparisonToJumpDirection(ePointRectComparison);
	double dDistance = This->m_rectCurrent.c.distanceToPoint(pviRect.c);
	if(dDistance > 1 && dDistance < This->m_arrdJumpDistances[eJumpDirection]) {
		This->m_arrPtJumpLocations[eJumpDirection] = pviRect.c;
		This->m_arrdJumpDistances[eJumpDirection] = dDistance;
	}

    return TRUE; // must return TRUE; If return is FALSE it stops the recursion
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiscreteNavSystem::CDiscreteNavSystem()
{
	PVI_POINT ptNoseSelectCenter(0.5,0.5);
	PVI_SIZE szNoseSelectSize(0.3,0.3);
	m_rectNoseSelect.set(ptNoseSelectCenter, szNoseSelectSize);
	m_hRectanglePen = CreatePen (PS_SOLID, 3, RGB(0, 0, 0));
	m_hPotentialPen = CreatePen (PS_DASH, 1, RGB(0, 0, 0));
	m_hLinePen = CreatePen(PS_SOLID, 2, RGB(255,0,0));
	m_eComparisonType = EIGHT_DIRECTIONS;
	m_eDiscreteNavType = MAPPING_TO_QUADRANTS;//DECREASING_JUMPS;//CHILD_WINDOWS;//
	m_nJumpLocationsFilled = 0;

	m_szQuadrant.set(0,0);
	m_nDirectMappingRows = m_nDirectMappingCols = 5;
	m_bShowRects = true;
}

CDiscreteNavSystem::~CDiscreteNavSystem()
{
	DeleteObject(m_hRectanglePen);
	DeleteObject(m_hPotentialPen);
	DeleteObject(m_hLinePen);
}

void CDiscreteNavSystem::reset() {
	PVI_SIZE szScreen = pvu::getScreenSize();
	m_rectCurrent.set(0,0,szScreen.x, szScreen.y);

	//m_bActive = false;
	m_bNoseSelectActivated = false;
	m_rectPotential.s.set(-1,-1);
	refreshDrawing();
	m_nJumpLocationsFilled = 0;
	if(m_eDiscreteNavType == DECREASING_JUMPS)
		updateJumpLocations();

	m_szQuadrant = PVI_SIZE(szScreen.x / m_nDirectMappingCols, szScreen.y / m_nDirectMappingRows);
	m_ptTopLeft00 = PVI_POINT(0,0);
}

PVI_POINT CDiscreteNavSystem::jump(EJumpDirection eJumpDirection) {
	if(eJumpDirection == DO_MAPPING_JUMP) {
		m_szQuadrant /= PVI_POINT(m_nDirectMappingCols, m_nDirectMappingRows);
		if(m_szQuadrant.x < RESET_SIZE || m_szQuadrant.y < RESET_SIZE)
			reset();
		else 
			m_ptTopLeft00.set(m_rectCurrent.getLeft(), m_rectCurrent.getTop());
		refreshDrawing();
		return m_rectCurrent.c;
	}

	if(m_arrPtJumpLocations[eJumpDirection].x < 0)
		return m_rectCurrent.c;

	m_rectCurrent.c = m_arrPtJumpLocations[eJumpDirection];
	if(m_eDiscreteNavType == DECREASING_JUMPS)
		m_rectCurrent.s /= 2;	
	updateJumpLocations();
	return m_rectCurrent.c;
}

PVI_POINT CDiscreteNavSystem::recurse(int xMagnitude, int yMagnitude) {
//	m_bActive = true;

	PVI_POINT ptNewC(m_rectCurrent.c.x + xMagnitude * m_rectCurrent.s.x / 4, m_rectCurrent.c.y + yMagnitude * m_rectCurrent.s.y / 4);

	if(m_rectCurrent.s.x < 10) {
		reset();
		return m_rectCurrent.c;
	}

	return ptNewC;
}

PVI_POINT CDiscreteNavSystem::updateNoseSelect(PVI_POINT ptNose)
{
	if(m_eDiscreteNavType == MAPPING_TO_QUADRANTS) {
		PVI_POINT ptCurrentQuadrant = PVI_POINT(pvu::discretizeNumber(ptNose.x, m_nDirectMappingCols, 0, 1), pvu::discretizeNumber(ptNose.y, m_nDirectMappingRows, 0, 1));
		m_rectCurrent.set((ptCurrentQuadrant*m_szQuadrant) + (m_szQuadrant/2) + m_ptTopLeft00, m_szQuadrant);
		return m_rectCurrent.c;
	}
	if(m_eDiscreteNavType == CHILD_WINDOWS) {
		if(m_nJumpLocationsFilled == 0) {
			m_foregroundWnd = GetForegroundWindow();
			updateJumpLocations();
		}
	}

	EPointRectComparison ePointRectComparison = m_rectNoseSelect.comparePointToMe(ptNose, m_eComparisonType);
	bool bIsInsideRect = ePointRectComparison == INSIDE_RECT;
	PVI_POINT ptToReturn(m_rectCurrent.c);
	if(m_bNoseSelectActivated) {
		m_bNoseSelectActivated = bIsInsideRect;
		if(bIsInsideRect)
			ePointRectComparison = m_rectNoseSelect.comparePointToMe(ptNose, m_eComparisonType, false);
		EJumpDirection eJumpDirection = convertPointRectComparisonToJumpDirection(ePointRectComparison);
		if(bIsInsideRect) {
			ptToReturn.set(m_arrPtJumpLocations[eJumpDirection]);
			if(m_eDiscreteNavType == DECREASING_JUMPS)
				m_rectPotential.set(ptToReturn, m_rectCurrent.s/2);
			else
				m_rectPotential.set(ptToReturn, ptToReturn);
		} else {//if(m_arrPtJumpLocations[eJumpDirection].x >= 0){
			ptToReturn.set(jump(eJumpDirection));
		}
	} else {
		m_bNoseSelectActivated = bIsInsideRect;
	}
	return m_rectCurrent.c;
}

void CDiscreteNavSystem::drawCurrentRect()
{
	if(m_eDiscreteNavType != MAPPING_TO_QUADRANTS)
		if(!(m_lastRectCurrentDrawn == m_rectCurrent) || !(m_lastRectPotentialDrawn == m_rectPotential))
			refreshDrawing();

	HDC		hWindowDC = NULL;  // The DC of the found window.
	HGDIOBJ	hPrevPen = NULL;   // Handle of the existing pen in the DC of the found window.
	HGDIOBJ	hPrevBrush = NULL; // Handle of the existing brush in the DC of the found window.
	long		lRet = 0;

	// Get the window DC of the found window.
	hWindowDC = GetWindowDC (NULL);

	if (hWindowDC)
	{
		// Select our created pen into the DC and backup the previous pen.
		hPrevPen = SelectObject (hWindowDC, m_hRectanglePen);

		// Select a transparent brush into the DC and backup the previous brush.
		hPrevBrush = SelectObject (hWindowDC, GetStockObject(HOLLOW_BRUSH));

		m_lastRectCurrentDrawn.set(m_rectCurrent);

		if(m_eDiscreteNavType == MAPPING_TO_QUADRANTS && m_bShowRects) {
			SelectObject(hWindowDC, m_hPotentialPen);
			for(int i=0; i<m_nDirectMappingCols; ++i) {
				for(int j=0; j<m_nDirectMappingRows; ++j) {
					PVI_RECT rect = PVI_RECT(m_szQuadrant*PVI_POINT(i,j) + m_szQuadrant/2 + m_ptTopLeft00, m_szQuadrant); 
					Rectangle (hWindowDC, (int)rect.getLeft(), (int)rect.getTop(), (int)rect.getRight(), (int)rect.getBottom());
				}
			}
		} else {
			// Draw a rectangle in the DC covering the entire window area of the found window.
			if(m_bShowRects) {
				if(m_eDiscreteNavType == DECREASING_JUMPS) {
					Rectangle (hWindowDC, (int)m_rectCurrent.getLeft(), (int)m_rectCurrent.getTop(), (int)m_rectCurrent.getRight(), (int)m_rectCurrent.getBottom());
				}
			
				//Draw the potential jump locations
				const int SIZE = 4;
				for(int i=0; i<NUM_JUMP_DIRECTIONS; ++i) {
					if(shouldDrawJumpLocation((EJumpDirection)i)) {
						PVI_POINT ptJumpLocation = m_arrPtJumpLocations[i];
						Rectangle (hWindowDC, (int)ptJumpLocation.x-SIZE/2, (int)ptJumpLocation.y-SIZE/2, (int)ptJumpLocation.x+SIZE/2, (int)ptJumpLocation.y+SIZE/2);
					}
				}
			}

			m_lastRectPotentialDrawn.set(m_rectPotential);
			if(m_rectPotential.s.x >= 0) {
				SelectObject(hWindowDC, m_hLinePen);
				MoveToEx(hWindowDC, (int)m_rectCurrent.c.x, (int)m_rectCurrent.c.y, NULL);
				LineTo(hWindowDC, (int)m_rectPotential.c.x, (int)m_rectPotential.c.y);
				if(m_eDiscreteNavType == DECREASING_JUMPS && m_bShowRects) {
					SelectObject(hWindowDC, m_hPotentialPen);
					Rectangle (hWindowDC, (int)m_rectPotential.getLeft(), (int)m_rectPotential.getTop(), (int)m_rectPotential.getRight(), (int)m_rectPotential.getBottom());
				}
			}
		}

		// Reinsert the previous pen and brush into the found window's DC.
		SelectObject (hWindowDC, hPrevPen);

		SelectObject (hWindowDC, hPrevBrush);

		// Finally release the DC.
		ReleaseDC (NULL, hWindowDC);
	}

}

bool CDiscreteNavSystem::shouldDrawJumpLocation(EJumpDirection eJumpDirection) {
	if(m_eComparisonType == EIGHT_DIRECTIONS) return true;
	
	if(eJumpDirection == NORTH || eJumpDirection == SOUTH || eJumpDirection == EAST || eJumpDirection == WEST)
		return m_eComparisonType == FOUR_DIRECTIONS_X;
	
	return m_eComparisonType == FOUR_DIRECTIONS_CROSS;
}

void CDiscreteNavSystem::refreshDrawing()
{
	//Refresh
	InvalidateRect (NULL, NULL, TRUE);
	UpdateWindow (NULL);
	RedrawWindow (NULL, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
}

void CDiscreteNavSystem::updateJumpLocations() {
	if(m_eDiscreteNavType == DECREASING_JUMPS) {
		m_arrPtJumpLocations[NORTH_WEST] = recurse(-1, -1);
		m_arrPtJumpLocations[NORTH_EAST] = recurse(1, -1);
		m_arrPtJumpLocations[SOUTH_WEST] = recurse(-1, 1);
		m_arrPtJumpLocations[SOUTH_EAST] = recurse(1, 1);
		m_arrPtJumpLocations[NORTH] = recurse(0, -1);
		m_arrPtJumpLocations[SOUTH] = recurse(0, 1);
		m_arrPtJumpLocations[EAST] = recurse(1, 0);
		m_arrPtJumpLocations[WEST] = recurse(-1, 0);
	} else { //m_eDiscreteNavType == CHILD_WINDOWS
		resetJumpLocations();
		EnumChildWindows(m_foregroundWnd, EnumChildProc, (LPARAM)this);
		fillInEmptyJumpLocations();
	}
}

void CDiscreteNavSystem::fillInEmptyJumpLocations() {
	for(int i=0; i<NUM_JUMP_DIRECTIONS; ++i) {
		if(m_arrPtJumpLocations[i].x >= 0)
			m_nJumpLocationsFilled++;
	}
	if(m_nJumpLocationsFilled == NUM_JUMP_DIRECTIONS || m_nJumpLocationsFilled == 0)
		return;

	int iCurrentJumpDirection = 0;
	while(m_nJumpLocationsFilled < NUM_JUMP_DIRECTIONS) {
		if(m_arrPtJumpLocations[iCurrentJumpDirection].x < 0) {
			int iLeftDirection = (iCurrentJumpDirection == 0) ? NUM_JUMP_DIRECTIONS - 1 : iCurrentJumpDirection - 1;
			int iRightDirection = (iCurrentJumpDirection == (NUM_JUMP_DIRECTIONS - 1)) ? 0 : iCurrentJumpDirection + 1;
			m_nJumpLocationsFilled++;
			if(m_arrPtJumpLocations[iLeftDirection].x < 0 && m_arrPtJumpLocations[iRightDirection].x >= 0) {
				m_arrPtJumpLocations[iCurrentJumpDirection] = m_arrPtJumpLocations[iRightDirection];
			} else if(m_arrPtJumpLocations[iLeftDirection].x >= 0 && m_arrPtJumpLocations[iRightDirection].x < 0) {
				m_arrPtJumpLocations[iCurrentJumpDirection] = m_arrPtJumpLocations[iLeftDirection];
			} else if(m_arrPtJumpLocations[iLeftDirection].x >= 0 && m_arrPtJumpLocations[iRightDirection].x >= 0) {
				m_arrPtJumpLocations[iCurrentJumpDirection] = (m_arrdJumpDistances[iLeftDirection] < m_arrdJumpDistances[iRightDirection]) ? m_arrPtJumpLocations[iLeftDirection] : m_arrPtJumpLocations[iRightDirection];
			} else {
				m_nJumpLocationsFilled--;
			}
		}
		iCurrentJumpDirection = (iCurrentJumpDirection + 1) % NUM_JUMP_DIRECTIONS;
	}
}

void CDiscreteNavSystem::resetJumpLocations() {
	for(int i=0; i<NUM_JUMP_DIRECTIONS; ++i) {
		m_arrPtJumpLocations[i].set(-1,-1);
		m_arrdJumpDistances[i] = 9999999;
	}
	m_nJumpLocationsFilled = 0;
}