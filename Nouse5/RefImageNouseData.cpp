#include "StdAfx.h"
#include "RefImageNouseData.h"

CRefImageNouseData::CRefImageNouseData()
{
	m_nBufLength = NOUSE_POINT_BUFFER;
	
	m_bufPtAbs = new PVI_BUFFER<PVI_3DPOINT>(m_nBufLength);  // do I  really need to store BufAbs ???
	m_bufPtRel = new PVI_BUFFER<PVI_3DPOINT>(m_nBufLength); // for drawing
	
	m_pRangeMotion = NULL;
}

CRefImageNouseData::~CRefImageNouseData() {
	
	delete m_bufPtAbs;
	delete m_bufPtRel;
	
}
	
	
void CRefImageNouseData::putAbs(PVI_3DPOINT ptAbs, int nHorizontalParam, int nVerticalParam) // in 160x120
{
	m_bufPtAbs->put(ptAbs);
	PVI_3DPOINT ptRel = ptAbsImage2ptRelImage(ptAbs, m_pRangeMotion->getRect(nHorizontalParam, nVerticalParam));
	m_bufPtRel->put(ptRel);
}
	
	
	
PVI_3DPOINT CRefImageNouseData::ptAbsImage2ptRelImage(PVI_3DPOINT ptAbs, PVI_RECT rectRange)
{
	PVI_RECT rectMotionRange = rectRange; //m_refImageData.m_pRangeMotion->getRect();
	PVI_3DPOINT ptNoseImageAbs = ptAbs; //*m_refImageData.arBufPtAbs[m_eModalityToUse]->getLast();

	PVI_POINT  ptRel01(
		(ptNoseImageAbs.x - rectMotionRange.getLeft()) / (rectMotionRange.getRight() - rectMotionRange.getLeft()),
	// why not this? ->		
		(ptNoseImageAbs.y - rectMotionRange.getTop()) / (rectMotionRange.getBottom() - rectMotionRange.getTop()));
	
	PVI_POINT  ptRel11(ptRel01.x*2 - 1, 1-ptRel01.y*2);
	return ptRel11;	// <- since in image top is at the bottom

}
	
	
