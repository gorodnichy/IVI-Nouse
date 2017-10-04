// DiscreteNavSystem.h: interface for the CDiscreteNavSystem class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../NouseVisionLibrary/pvi-utility.h"

#define RESET_SIZE 2

enum EJumpDirection {
	WEST = 0,
	NORTH_WEST,
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	NUM_JUMP_DIRECTIONS,
	DO_MAPPING_JUMP
};

enum EDiscreteNavType {
	DECREASING_JUMPS = 0,
	MAPPING_TO_QUADRANTS,
	CHILD_WINDOWS
};

class CDiscreteNavSystem  
{
public:
	void refreshDrawing();
	void drawCurrentRect();
	PVI_POINT updateNoseSelect(PVI_POINT ptNose);
	CDiscreteNavSystem();
	virtual ~CDiscreteNavSystem();

	PVI_RECT m_rectCurrent;
	PVI_RECT m_lastRectCurrentDrawn;
	PVI_RECT m_rectPotential;
	PVI_RECT m_lastRectPotentialDrawn;
	//bool m_bActive;
	PVI_RECT m_rectNoseSelect;
	bool m_bNoseSelectActivated;

	void reset();
	PVI_POINT jump(EJumpDirection eJumpDirection = DO_MAPPING_JUMP);
	EComparisonType m_eComparisonType;

	EDiscreteNavType m_eDiscreteNavType;
	PVI_POINT m_arrPtJumpLocations[NUM_JUMP_DIRECTIONS];
	double m_arrdJumpDistances[NUM_JUMP_DIRECTIONS];

	int m_nDirectMappingRows, m_nDirectMappingCols;
	bool m_bShowRects;

private:
	PVI_POINT recurse(int xMagnitude, int yMagnitude);
	HPEN m_hRectanglePen, m_hPotentialPen, m_hLinePen;
	
	void updateJumpLocations();
	bool shouldDrawJumpLocation(EJumpDirection eJumpDirection);
	void resetJumpLocations();
	void fillInEmptyJumpLocations();
	HWND m_foregroundWnd;
	int m_nJumpLocationsFilled;

	//For MAPPING_TO_QUADRANTS
	PVI_POINT m_szQuadrant;
	PVI_POINT m_ptTopLeft00;
};
