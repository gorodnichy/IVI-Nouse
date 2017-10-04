#include "StdAfx.h"
#include "RangeMotion.h"



	
	// rect is computed from these 5 points
PVI_RECT CRangeMotion::getRect(int nHorizontalParam, int nVerticalParam) {
	//int nHorizontalParam = 5;//((CPVSContainerApp*)AfxGetApp())->m_nMotionRangeHorizontal;//g.gui.widgetList.getWidget("MOTION RANGE horizontal")->m_arrnCurrentValue[0];
	//int nVerticalParam = 5;//((CPVSContainerApp*)AfxGetApp())->m_nMotionRangeVertical;//g.gui.widgetList.getWidget("MOTION RANGE vertical")->m_arrnCurrentValue[0];
	
	rectRange = PVI_RECT(ptLeft.x, ptTop.y, ptRight.x - ptLeft.x, ptBottom.y - ptTop.y);
	
	rectRange.s.x *= (0.1 * (5 + nHorizontalParam));
	rectRange.s.y *= (0.1 * (5 + nVerticalParam));
	
	///		reset(rectRange);
	return rectRange;
}
	
	
	
// NB: in 160x120 image !!!
CRangeMotion::CRangeMotion() {
	//reset(0, 0, g.n160_X-1, g.n120_Y-1);
	reset(0, 0, 160-1, 120-1);
	bKnown = false;
}
	
void CRangeMotion::reset(PVI_RECT r) {
	PVI_POINT rTop = r.get00();
	reset((int)rTop.x,(int)rTop.y,(int)(rTop.x+r.s.x),(int)(rTop.y+r.s.y));
}
	
// NB: in 160x120 image !!!
void CRangeMotion::reset(int x1, int y1, int x2, int y2) //, int xZero, int yZero)
{
	ptLeft.set(x1,(y2+y1)/2);
	ptTop.set((x1+x2)/2,y1);
	ptRight.set(x2,(y2+y1)/2);
	ptBottom.set((x1+x2)/2,y2);
	ptZero.set((x1+x2)/2,(y2+y1)/2);
}
	
bool CRangeMotion::isPointInRange(PVI_POINT pt) {
	return (pt.x > ptLeft.x) && (pt.x < ptRight.x) && (pt.y > ptTop.y) && (pt.y < ptBottom.y);
}
	
	
void CRangeMotion::set(PVI_RECT *r, PVI_POINT *zero)
{
	ptZero = (zero == NULL) ? r->c : *zero;
	ptLeft = PVI_POINT(pvu::max(0.0,r->getLeft()), r->c.y);
	ptRight = PVI_POINT(pvu::min(160.0,r->getRight()), r->c.y);
	ptTop = PVI_POINT(r->c.x, pvu::max(0.0,r->getTop()));
	ptBottom = PVI_POINT(r->c.x, pvu::min(120.0,r->getBottom()));
}
