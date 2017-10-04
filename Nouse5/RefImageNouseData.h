#pragma once
#define NOUSE_POINT_BUFFER 500

#include "RangeMotion.h"
class CRefImageNouseData
{
public:
	CRefImageNouseData(void);
	~CRefImageNouseData(void);

	
	CRangeMotion* m_pRangeMotion;
	int m_nBufLength; 
	
	PVI_BUFFER <PVI_3DPOINT>* m_bufPtAbs; // NOUSE_MAX_MODALITIES = 10 
	PVI_BUFFER <PVI_3DPOINT>* m_bufPtRel;
	
	void putAbs(PVI_3DPOINT ptAbs, int nHorizontalParam, int nVerticalParam);
	PVI_3DPOINT ptAbsImage2ptRelImage(PVI_3DPOINT ptAbs, PVI_RECT rectRange);
};

