#pragma once

#define CURSOR_INCR_SIZE 32
#define NUM_BUTTONS 4
#define LINE_COLOUR CV_RGB(0,0,0)

#include "../NouseVisionLibrary/IplImage.h"
#include "../NouseVisionLibrary/pvu_types.h"
#include "State.h"
#include "StateReady.h"
#include "StateCalibration.h"
#include "StateCursor.h"
#include "../NouseVisionLibrary/pvs.h"

enum ETranslucenceType {
	SOLID,
	TRANSLUCENT,
	INVISIBLE
};

class CNouseCursor
{
public:
	CNouseCursor(void);
	~CNouseCursor(void);
	void show();
	void hide();

	void redraw(CState* pState, CPVS* pPVS);
	HWND m_hwnd;
	int m_nCursorSize;
	bool m_bCursorShowsFace, m_bCursorShowsCountdown;
	time_t m_timeWhenArrivedAtPos;
	int m_nWidth;
	PVI_POINT m_ptLocation;


	int m_nTranslucentSolidness;
	bool m_bUseTranslucentCursor;
	CString m_strCreationFailed;

	char m_strLeave[256];
	char m_strStill[256];
	char m_strReset[256];
	char m_strCenter[256];
	char m_strPaused[256];
	char m_strBoard[256];
	char m_strDirect[256];
	char m_strJoystick[256];
	char m_strMouse[256];
	char m_strDiscrete[256];
	char m_strType[256];
	char m_strClick[256];


private:
	int m_nColor[3] = { 255, 255, 50 };// for click scalar colors
	bool create(int nWidth, ETranslucenceType eTranslucenceType = SOLID);
	ETranslucenceType m_eCurrentTranslucenceType;
	int m_nCurrentTranslucentSolidness;


	bool destroy();

	HMODULE	m_hInstance;
	
	int m_nWidthThreeQuarters;
	CIplImage	m_cameraImage32x24, m_image;
	
	bool m_bCursorVisible;
	IplImage * m_pImc, *m_pImcNow;
	
	CvScalar m_arrClrBtn[NUM_BUTTONS];

	char m_strHelpLine[256];
	char m_strCountdown[256];
	char m_strDragging[256];
	char m_strCursorCloseEnoughForBoard[256];

	void setPos(PVI_POINT pt);
	void drawButtons();

protected:
	ATOM registerWindowClass(HMODULE hInstance);
	static LRESULT CALLBACK customWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	void clearStrings(void);
};

