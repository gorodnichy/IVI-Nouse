#pragma once

#include "../NouseVisionLibrary/pvi-utility.h"

class CRangeMotion
{
public:
	CRangeMotion(void);
	~CRangeMotion(void) {}

	//These 5 points are computed when shown by the user in Calibration
	PVI_POINT ptZero;
	PVI_POINT ptLeft;
	PVI_POINT ptRight;
	PVI_POINT ptTop;
	PVI_POINT ptBottom;
	PVI_RECT rectRange;
	
	// rect is computed from these 5 points
	PVI_RECT getRect(int nHorizontalParam, int nVerticalParam);
	
	bool bKnown;
	
	
	
	void reset(PVI_RECT r);
	
	
	
	void reset(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) ;
	bool isPointInRange(PVI_POINT pt);
	
	
	void set(PVI_RECT *r, PVI_POINT *zero);
};

