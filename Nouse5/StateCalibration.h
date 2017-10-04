#pragma once
#include "state.h"
#include "../NouseVisionLibrary/NouseTracker.h"
#include "NouseControl.h"
class CStateCalibration :
	public CState
{
public:
	CStateCalibration(void);
	~CStateCalibration(void);

	EState processData(CPVS* pPVS);
	void onEntrance(CPVS* pPVS);

	int m_nCountConfirm;
	int m_nCountdown;
	PVI_RECT m_rectConfirm;
	bool m_bQuickCalibrate;
	CNouseTracker* m_pNouseTracker;
	CNouseControl* m_pNouseControl;
	bool m_bInConfirmingStage;
	int m_nClickBoxSize;
	int m_nCountCalibrateSelect;
	bool* m_pbEnableSounds;
private:
	time_t m_timeTimerStart;
};

