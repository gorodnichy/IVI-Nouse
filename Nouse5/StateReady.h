#pragma once
#include "state.h"
#include "NouseControl.h"

#define NUM_FACES_IN_A_ROW_REQUIRED 2

class CStateReady :
	public CState
{
public:
	CStateReady(void);
	~CStateReady(void);

	EState processData(CPVS* pPVS);
	void onEntrance(CPVS* pPVS);

	bool m_bActWithFaceDetection;
	double m_dHeadWidth;
	int m_nFaceDetectionType;
	CNouseControl* m_pNouseControl;
	int m_nFacesInARow;
	PVI_RECT m_rectLastFaceDetected;

	
};

