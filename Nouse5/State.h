// State.h: interface for the CState class.
//
//////////////////////////////////////////////////////////////////////


#pragma once


#include "../NouseVisionLibrary/PVS.h"


enum EPVS_NOUSE_EVENT {
	NOUSE_EVENT_NONE,
	NOUSE_EVENT_KEY_PRESS,
	NOUSE_EVENT_PVS_UPDOWN,
	NOUSE_EVENT_PVS_LEFTRIGHT,
	NOUSE_EVENT_PVS_BIG_FACE_MOTION,
	NOUSE_EVENT_PVS_DOUBLE_BLINK,
	NOUSE_EVENT_PVS_BLINK,
	NOUSE_EVENT_PVS_MOUTH, //Elan09
	NOUSE_EVENT_VOICE //Elan09
};

enum EState {
	STATE_READY,
	STATE_CALIBRATION,
	STATE_CURSOR
};

class CState  
{
public:
	
	CState() {}
	virtual ~CState() {}

	EState m_eWhoAmI;

	virtual EState processData(CPVS* pPVS) = 0;
	virtual EState processEvent(EPVS_NOUSE_EVENT eventID, CPVS* pPVS) {return m_eWhoAmI;}
	virtual void onEntrance(CPVS* pPVS) {}
	virtual void onExit() {}
};


