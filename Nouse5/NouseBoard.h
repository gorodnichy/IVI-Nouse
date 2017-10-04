#pragma once

#include "../NouseVisionLibrary/pvi-utility.h"
#include "NousePad.h"	
#include "WordCompletionSystem.h"



#define NUMBER_OF_COLS 5
#define NUMBER_OF_ROWS 3
#define NUMBER_OF_BOXES_PER_GROUP 4

// Elan10: Percentages are based on having a board at (100,0) -> (1100,300) on a screen with resolution of 1280x800
#define BOARD_WIDTH_PCT_OF_SCREEN 0.8//0.78125
#define BOARD_HEIGHT_PCT_OF_SCREEN 0.4//0.375

//Elan09
#define DICTIONARY_FILENAME "wordlist.txt"
#define MAX_LABEL_LENGTH 256

enum EBoardLayout {
	EBOARDLAYOUT_MODE_NORMAL = 0,
	EBOARDLAYOUT_MODE_SHIFT,
	EBOARDLAYOUT_MODE_ADV
};

class CNouseBoard : public CFrameWnd
{
// Construction
public:
	CNouseBoard();
	virtual ~CNouseBoard();

	struct sKbd
	{		
		struct sGroup
		{			
			struct sBoxElement
			{
				char szNormalText[MAX_LABEL_LENGTH];
				char szAdvText  [MAX_LABEL_LENGTH];
				char szShiftText [MAX_LABEL_LENGTH];
			} box[NUMBER_OF_BOXES_PER_GROUP];
			//Elan09

			
			CvScalar normalColor[3]; // One color for each level (normal, shift, adv)
		} group[NUMBER_OF_ROWS][NUMBER_OF_COLS];
	} m_Kbd;


	EBoardLayout m_layoutMode;
	double m_dTextSizeScale;
	int m_nSelectedRow, m_nSelectedCol;
	PVI_RECT m_rectBoard;
	CWordCompletionSystem* m_pWordCompletionSystem;
	char m_strCurrentTypedWord[MAX_LABEL_LENGTH];
	HWND m_wndNouseBoard;
	bool m_bWaitingToType;
	int m_nJitterThreshold;
	char m_strToType[256];
	bool m_bCursorMoved;

	bool redrawWindow();
	void show();
	void hide();
	PVI_POINT getCenterOfSelectedSquare();
	PVI_VECTOR getSquareWidthHeight();
	void type(EPointRectComparison ePointRectComparison);

	char m_strNouseboardDialogTitle[256];

protected:

	DECLARE_MESSAGE_MAP()

private:
	void putCellText(char *szTxt, int nColGroup, int nRowGroup, int nWhichAreaInGroup, CIplImage *img);
};

