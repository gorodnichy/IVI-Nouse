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

class CNousePRECursor
{
public:
	CNousePRECursor(void);
	~CNousePRECursor(void);
	void show();
	void hide();

	void redraw(CState* pState, CPVS* pPVS);
	HWND m_hwnd;
	int m_nCursorSize;
	int m_nWidth;
	PVI_POINT m_ptLocation;




private:


	bool create(int nWidth, ETranslucenceType eTranslucenceType = SOLID);


	bool destroy();

	HMODULE	m_hInstance;
	

	void setPos(PVI_POINT pt);

protected:
	ATOM registerWindowClass(HMODULE hInstance);
	static LRESULT CALLBACK customWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

