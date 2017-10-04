#pragma once
#include "RangeMotion.h"
#include "RefImageNouseData.h"

enum EPointerLocation {
	ALWAYS_TOPLEFT = 0,
	MOVES,
	ALWAYS_CENTER
};

enum EControlMode
{
	CONTROL_MODE_DIRECT,
	CONTROL_MODE_JOYSTICK,
	CONTROL_MODE_MOUSE,
	CONTROL_MODE_DISCRETE
};

class CNouseControl
{
public:
	CNouseControl(void);
	~CNouseControl(void);

	CRangeMotion m_rangeMotion;
	CRefImageNouseData m_refImageData;
	EPointerLocation m_ePointerLocation;
	int m_nPctStopJoystick;
	EComparisonType m_eDiscreteDirection;
	int m_nCursorSpeed;
	EControlMode m_eGeneralControlMode;
	EControlMode m_eControlMode;
	int m_nMotionRangeHorizontal;
	int m_nMotionRangeVertical;

	EPointRectComparison m_eInWhichCorner;
	bool m_bLeftCorner;
	PVI_POINT m_ptWinAbs;
	PVI_POINT m_ptAbsDelta;
	PVI_SIZE m_ptTranslation;
	PVI_POINT m_ptDirectAbs;
	PVI_POINT* m_pptEnteredYellowState;

	int m_nPointingCorner, m_nPrePointingCorner; //Elan09: 0-3 is for the 4 corners and 4 is for the center

	void setPointWinAbs(PVI_POINT pt);
	void computePtAbsScreen(int nCursorWidth, PVI_RECT rectLockArea);
	double delta(double x, int nDimensions = 3);
	void handlePointingCorner(int nCursorWidth, PVI_RECT rectLockArea);
};

