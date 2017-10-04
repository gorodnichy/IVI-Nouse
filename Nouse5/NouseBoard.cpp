#include "stdafx.h"
#include "NouseBoard.h"
#include <process.h>


CNouseBoard::CNouseBoard()
{
		// Normal Text
	strcpy( m_Kbd.group[0][0].box[ABOVE_RECT-1].szNormalText , "a\0" );
	strcpy( m_Kbd.group[0][0].box[LEFT_OF_RECT-1].szNormalText , "c\0" );
	strcpy( m_Kbd.group[0][0].box[BELOW_RECT-1].szNormalText , "d\0" );
	strcpy( m_Kbd.group[0][0].box[RIGHT_OF_RECT-1].szNormalText , "b\0" );
	
	strcpy( m_Kbd.group[0][1].box[ABOVE_RECT-1].szNormalText , "e\0" );
	strcpy( m_Kbd.group[0][1].box[LEFT_OF_RECT-1].szNormalText , "g\0" );
	strcpy( m_Kbd.group[0][1].box[BELOW_RECT-1].szNormalText , "h\0" );
	strcpy( m_Kbd.group[0][1].box[RIGHT_OF_RECT-1].szNormalText , "f\0" );	
	
	strcpy( m_Kbd.group[0][2].box[ABOVE_RECT-1].szNormalText , "i\0" );
	strcpy( m_Kbd.group[0][2].box[LEFT_OF_RECT-1].szNormalText , "k\0" );
	strcpy( m_Kbd.group[0][2].box[BELOW_RECT-1].szNormalText , "l\0" );
	strcpy( m_Kbd.group[0][2].box[RIGHT_OF_RECT-1].szNormalText , "j\0" );	
	
	strcpy( m_Kbd.group[0][3].box[ABOVE_RECT-1].szNormalText , "o\0" );
	strcpy( m_Kbd.group[0][3].box[LEFT_OF_RECT-1].szNormalText , "m\0" );
	strcpy( m_Kbd.group[0][3].box[BELOW_RECT-1].szNormalText , "n\0" );
	strcpy( m_Kbd.group[0][3].box[RIGHT_OF_RECT-1].szNormalText , "p\0" );	
	
	strcpy( m_Kbd.group[0][4].box[ABOVE_RECT-1].szNormalText , "q\0" );
	strcpy( m_Kbd.group[0][4].box[LEFT_OF_RECT-1].szNormalText , "s\0" );
	strcpy( m_Kbd.group[0][4].box[BELOW_RECT-1].szNormalText , "t\0" );
	strcpy( m_Kbd.group[0][4].box[RIGHT_OF_RECT-1].szNormalText , "r\0" );	
	
	strcpy( m_Kbd.group[1][0].box[ABOVE_RECT-1].szNormalText , "u\0" );
	strcpy( m_Kbd.group[1][0].box[LEFT_OF_RECT-1].szNormalText , "w\0" );
	strcpy( m_Kbd.group[1][0].box[BELOW_RECT-1].szNormalText , "x\0" );
	strcpy( m_Kbd.group[1][0].box[RIGHT_OF_RECT-1].szNormalText , "v\0" );	
	
	strcpy( m_Kbd.group[1][1].box[ABOVE_RECT-1].szNormalText , "y\0" );
	strcpy( m_Kbd.group[1][1].box[LEFT_OF_RECT-1].szNormalText , "Switch\0" );
	strcpy( m_Kbd.group[1][1].box[BELOW_RECT-1].szNormalText , ".\0" );
	strcpy( m_Kbd.group[1][1].box[RIGHT_OF_RECT-1].szNormalText , "z\0" );	
	
	strcpy( m_Kbd.group[1][2].box[ABOVE_RECT-1].szNormalText , "Space\0" );
	strcpy( m_Kbd.group[1][2].box[LEFT_OF_RECT-1].szNormalText , "\'\0" );
	strcpy( m_Kbd.group[1][2].box[BELOW_RECT-1].szNormalText , "?\0" );
	strcpy( m_Kbd.group[1][2].box[RIGHT_OF_RECT-1].szNormalText , "Enter\0" );	
	
	strcpy( m_Kbd.group[1][3].box[ABOVE_RECT-1].szNormalText , "1\0" );
	strcpy( m_Kbd.group[1][3].box[LEFT_OF_RECT-1].szNormalText , "2\0" );
	strcpy( m_Kbd.group[1][3].box[BELOW_RECT-1].szNormalText , "3\0" );
	strcpy( m_Kbd.group[1][3].box[RIGHT_OF_RECT-1].szNormalText , "4\0" );	
	
	strcpy( m_Kbd.group[1][4].box[ABOVE_RECT-1].szNormalText , "5\0" );
	strcpy( m_Kbd.group[1][4].box[LEFT_OF_RECT-1].szNormalText , "6\0" );
	strcpy( m_Kbd.group[1][4].box[BELOW_RECT-1].szNormalText , "7\0" );
	strcpy( m_Kbd.group[1][4].box[RIGHT_OF_RECT-1].szNormalText , "8\0" );
	
	strcpy( m_Kbd.group[2][0].box[ABOVE_RECT-1].szNormalText , "Up\0" );
	strcpy( m_Kbd.group[2][0].box[LEFT_OF_RECT-1].szNormalText , "Left\0" );
	strcpy( m_Kbd.group[2][0].box[BELOW_RECT-1].szNormalText , "Down\0" );
	strcpy( m_Kbd.group[2][0].box[RIGHT_OF_RECT-1].szNormalText , "Right\0" );
	
	strcpy( m_Kbd.group[2][1].box[ABOVE_RECT-1].szNormalText , "Shift\0" );
	strcpy( m_Kbd.group[2][1].box[LEFT_OF_RECT-1].szNormalText , "[\0" );
	strcpy( m_Kbd.group[2][1].box[BELOW_RECT-1].szNormalText , "Adv\0" );
	strcpy( m_Kbd.group[2][1].box[RIGHT_OF_RECT-1].szNormalText , "]\0" );
	
	strcpy( m_Kbd.group[2][2].box[ABOVE_RECT-1].szNormalText , "Clear\0" );
	strcpy( m_Kbd.group[2][2].box[LEFT_OF_RECT-1].szNormalText , "<-BKSP\0" );
	strcpy( m_Kbd.group[2][2].box[BELOW_RECT-1].szNormalText , "Quit\0" );
	strcpy( m_Kbd.group[2][2].box[RIGHT_OF_RECT-1].szNormalText , "DEL\0" );
	
	strcpy( m_Kbd.group[2][3].box[ABOVE_RECT-1].szNormalText , "ALT\0" );
	strcpy( m_Kbd.group[2][3].box[LEFT_OF_RECT-1].szNormalText , "CTRL\0" );
	strcpy( m_Kbd.group[2][3].box[BELOW_RECT-1].szNormalText , "Tab\0" );
	strcpy( m_Kbd.group[2][3].box[RIGHT_OF_RECT-1].szNormalText , "Pause\0" );
	
	strcpy( m_Kbd.group[2][4].box[ABOVE_RECT-1].szNormalText , "-\0" );
	strcpy( m_Kbd.group[2][4].box[LEFT_OF_RECT-1].szNormalText , "9\0" );
	strcpy( m_Kbd.group[2][4].box[BELOW_RECT-1].szNormalText , "0\0" );
	strcpy( m_Kbd.group[2][4].box[RIGHT_OF_RECT-1].szNormalText , "=\0" );

	//Shift text
	strcpy( m_Kbd.group[0][0].box[ABOVE_RECT-1].szShiftText , "A\0" );
	strcpy( m_Kbd.group[0][0].box[LEFT_OF_RECT-1].szShiftText , "C\0" );
	strcpy( m_Kbd.group[0][0].box[BELOW_RECT-1].szShiftText , "D\0" );
	strcpy( m_Kbd.group[0][0].box[RIGHT_OF_RECT-1].szShiftText , "B\0" );
	
	strcpy( m_Kbd.group[0][1].box[ABOVE_RECT-1].szShiftText , "E\0" );
	strcpy( m_Kbd.group[0][1].box[LEFT_OF_RECT-1].szShiftText , "G\0" );
	strcpy( m_Kbd.group[0][1].box[BELOW_RECT-1].szShiftText , "H\0" );
	strcpy( m_Kbd.group[0][1].box[RIGHT_OF_RECT-1].szShiftText , "F\0" );	
	
	strcpy( m_Kbd.group[0][2].box[ABOVE_RECT-1].szShiftText , "I\0" );
	strcpy( m_Kbd.group[0][2].box[LEFT_OF_RECT-1].szShiftText , "K\0" );
	strcpy( m_Kbd.group[0][2].box[BELOW_RECT-1].szShiftText , "L\0" );
	strcpy( m_Kbd.group[0][2].box[RIGHT_OF_RECT-1].szShiftText , "J\0" );	
	
	strcpy( m_Kbd.group[0][3].box[ABOVE_RECT-1].szShiftText , "O\0" );
	strcpy( m_Kbd.group[0][3].box[LEFT_OF_RECT-1].szShiftText , "M\0" );
	strcpy( m_Kbd.group[0][3].box[BELOW_RECT-1].szShiftText , "N\0" );
	strcpy( m_Kbd.group[0][3].box[RIGHT_OF_RECT-1].szShiftText , "P\0" );	
	
	strcpy( m_Kbd.group[0][4].box[ABOVE_RECT-1].szShiftText , "Q\0" );
	strcpy( m_Kbd.group[0][4].box[LEFT_OF_RECT-1].szShiftText , "S\0" );
	strcpy( m_Kbd.group[0][4].box[BELOW_RECT-1].szShiftText , "T\0" );
	strcpy( m_Kbd.group[0][4].box[RIGHT_OF_RECT-1].szShiftText , "R\0" );	
	
	strcpy( m_Kbd.group[1][0].box[ABOVE_RECT-1].szShiftText , "U\0" );
	strcpy( m_Kbd.group[1][0].box[LEFT_OF_RECT-1].szShiftText , "W\0" );
	strcpy( m_Kbd.group[1][0].box[BELOW_RECT-1].szShiftText , "X\0" );
	strcpy( m_Kbd.group[1][0].box[RIGHT_OF_RECT-1].szShiftText , "V\0" );	
	
	strcpy( m_Kbd.group[1][1].box[ABOVE_RECT-1].szShiftText , "Y\0" );
	strcpy( m_Kbd.group[1][1].box[LEFT_OF_RECT-1].szShiftText , "<\0" );
	strcpy( m_Kbd.group[1][1].box[BELOW_RECT-1].szShiftText , ">\0" );
	strcpy( m_Kbd.group[1][1].box[RIGHT_OF_RECT-1].szShiftText , "Z\0" );	
	
	strcpy( m_Kbd.group[1][2].box[ABOVE_RECT-1].szShiftText , "Space\0" );
	strcpy( m_Kbd.group[1][2].box[LEFT_OF_RECT-1].szShiftText , "\"\0" );
	strcpy( m_Kbd.group[1][2].box[BELOW_RECT-1].szShiftText , "Enter\0" );
	strcpy( m_Kbd.group[1][2].box[RIGHT_OF_RECT-1].szShiftText , "/\0" );	
	
	strcpy( m_Kbd.group[1][3].box[ABOVE_RECT-1].szShiftText , "!\0" );
	strcpy( m_Kbd.group[1][3].box[LEFT_OF_RECT-1].szShiftText , "@\0" );
	strcpy( m_Kbd.group[1][3].box[BELOW_RECT-1].szShiftText , "#\0" );
	strcpy( m_Kbd.group[1][3].box[RIGHT_OF_RECT-1].szShiftText , "$\0" );	
	
	strcpy( m_Kbd.group[1][4].box[ABOVE_RECT-1].szShiftText , "%\0" );
	strcpy( m_Kbd.group[1][4].box[LEFT_OF_RECT-1].szShiftText , "^\0" );
	strcpy( m_Kbd.group[1][4].box[BELOW_RECT-1].szShiftText , "&\0" );
	strcpy( m_Kbd.group[1][4].box[RIGHT_OF_RECT-1].szShiftText , "*\0" );
	
	strcpy( m_Kbd.group[2][0].box[ABOVE_RECT-1].szShiftText , "Up\0" );
	strcpy( m_Kbd.group[2][0].box[LEFT_OF_RECT-1].szShiftText , "Left\0" );
	strcpy( m_Kbd.group[2][0].box[BELOW_RECT-1].szShiftText , "Down\0" );
	strcpy( m_Kbd.group[2][0].box[RIGHT_OF_RECT-1].szShiftText , "Right\0" );
	
	strcpy( m_Kbd.group[2][1].box[ABOVE_RECT-1].szShiftText , "Normal\0" );
	strcpy( m_Kbd.group[2][1].box[LEFT_OF_RECT-1].szShiftText , "{\0" );
	strcpy( m_Kbd.group[2][1].box[BELOW_RECT-1].szShiftText , "Adv\0" );
	strcpy( m_Kbd.group[2][1].box[RIGHT_OF_RECT-1].szShiftText , "}\0" );
	
	strcpy( m_Kbd.group[2][2].box[ABOVE_RECT-1].szShiftText , "Clear\0" );
	strcpy( m_Kbd.group[2][2].box[LEFT_OF_RECT-1].szShiftText , "<-BKSP\0" );
	strcpy( m_Kbd.group[2][2].box[BELOW_RECT-1].szShiftText , "Quit\0" );
	strcpy( m_Kbd.group[2][2].box[RIGHT_OF_RECT-1].szShiftText , "DEL\0" );
	
	strcpy( m_Kbd.group[2][3].box[ABOVE_RECT-1].szShiftText , "ALT\0" );
	strcpy( m_Kbd.group[2][3].box[LEFT_OF_RECT-1].szShiftText , "CTRL\0" );
	strcpy( m_Kbd.group[2][3].box[BELOW_RECT-1].szShiftText , "Tab\0" );
	strcpy( m_Kbd.group[2][3].box[RIGHT_OF_RECT-1].szShiftText , "Pause\0" );
	
	strcpy( m_Kbd.group[2][4].box[ABOVE_RECT-1].szShiftText , "_\0" );
	strcpy( m_Kbd.group[2][4].box[LEFT_OF_RECT-1].szShiftText , "(\0" );
	strcpy( m_Kbd.group[2][4].box[BELOW_RECT-1].szShiftText , ")\0" );
	strcpy( m_Kbd.group[2][4].box[RIGHT_OF_RECT-1].szShiftText , "+\0" );


	//Adv text
	strcpy( m_Kbd.group[0][0].box[ABOVE_RECT-1].szAdvText, "W-RC1\0" );
	strcpy( m_Kbd.group[0][0].box[LEFT_OF_RECT-1].szAdvText , "W-RC2\0" );
	strcpy( m_Kbd.group[0][0].box[BELOW_RECT-1].szAdvText , "W-RC3\0" );
	strcpy( m_Kbd.group[0][0].box[RIGHT_OF_RECT-1].szAdvText , "W-RC4\0" );
	
	strcpy( m_Kbd.group[0][1].box[ABOVE_RECT-1].szAdvText , "W-RC5\0" );
	strcpy( m_Kbd.group[0][1].box[LEFT_OF_RECT-1].szAdvText , "W-R6\0" );
	strcpy( m_Kbd.group[0][1].box[BELOW_RECT-1].szAdvText , "W-RC7\0" );
	strcpy( m_Kbd.group[0][1].box[RIGHT_OF_RECT-1].szAdvText , "W-RC8\0" );	
	
	strcpy( m_Kbd.group[0][2].box[ABOVE_RECT-1].szAdvText , "W-RC9\0" );
	strcpy( m_Kbd.group[0][2].box[LEFT_OF_RECT-1].szAdvText , "W-RC10\0" );
	strcpy( m_Kbd.group[0][2].box[BELOW_RECT-1].szAdvText , "W-CS1\0" );
	strcpy( m_Kbd.group[0][2].box[RIGHT_OF_RECT-1].szAdvText , "W-CS2\0" );	
	
	strcpy( m_Kbd.group[0][3].box[ABOVE_RECT-1].szAdvText , "W-CS3\0" );
	strcpy( m_Kbd.group[0][3].box[LEFT_OF_RECT-1].szAdvText , "W-CS4\0" );
	strcpy( m_Kbd.group[0][3].box[BELOW_RECT-1].szAdvText , "W-CS5\0" );
	strcpy( m_Kbd.group[0][3].box[RIGHT_OF_RECT-1].szAdvText , "W-CS6\0" );	
	
	strcpy( m_Kbd.group[0][4].box[ABOVE_RECT-1].szAdvText , "W-CC7\0" );
	strcpy( m_Kbd.group[0][4].box[LEFT_OF_RECT-1].szAdvText , "W-CC8\0" );
	strcpy( m_Kbd.group[0][4].box[BELOW_RECT-1].szAdvText , "W-CC9\0" );
	strcpy( m_Kbd.group[0][4].box[RIGHT_OF_RECT-1].szAdvText , "W-CC10\0" );	
	
	strcpy( m_Kbd.group[1][0].box[ABOVE_RECT-1].szAdvText , "W-CC1\0" );
	strcpy( m_Kbd.group[1][0].box[LEFT_OF_RECT-1].szAdvText , "W-CC2\0" );
	strcpy( m_Kbd.group[1][0].box[BELOW_RECT-1].szAdvText , "W-CC3\0" );
	strcpy( m_Kbd.group[1][0].box[RIGHT_OF_RECT-1].szAdvText , "W-CC4\0" );	
	
	strcpy( m_Kbd.group[1][1].box[ABOVE_RECT-1].szAdvText , "W-CC5\0" );
	strcpy( m_Kbd.group[1][1].box[LEFT_OF_RECT-1].szAdvText , "W-CC6\0" );
	strcpy( m_Kbd.group[1][1].box[BELOW_RECT-1].szAdvText , "W-CC7\0" );
	strcpy( m_Kbd.group[1][1].box[RIGHT_OF_RECT-1].szAdvText , "W-CC8\0" );	
	
	strcpy( m_Kbd.group[1][2].box[ABOVE_RECT-1].szAdvText , "W-CC9\0" );
	strcpy( m_Kbd.group[1][2].box[LEFT_OF_RECT-1].szAdvText , "W-CC10\0" );
	strcpy( m_Kbd.group[1][2].box[BELOW_RECT-1].szAdvText , "W-RS1\0" );
	strcpy( m_Kbd.group[1][2].box[RIGHT_OF_RECT-1].szAdvText , "W-RS2\0" );	
	
	strcpy( m_Kbd.group[1][3].box[ABOVE_RECT-1].szAdvText , "W-RS3\0" );
	strcpy( m_Kbd.group[1][3].box[LEFT_OF_RECT-1].szAdvText , "W-RS4\0" );
	strcpy( m_Kbd.group[1][3].box[BELOW_RECT-1].szAdvText , "W-RS5\0" );
	strcpy( m_Kbd.group[1][3].box[RIGHT_OF_RECT-1].szAdvText , "W-RS6\0" );	
	
	strcpy( m_Kbd.group[1][4].box[ABOVE_RECT-1].szAdvText , "W-RS7\0" );
	strcpy( m_Kbd.group[1][4].box[LEFT_OF_RECT-1].szAdvText , "W-RS8\0" );
	strcpy( m_Kbd.group[1][4].box[BELOW_RECT-1].szAdvText , "W-RS9\0" );
	strcpy( m_Kbd.group[1][4].box[RIGHT_OF_RECT-1].szAdvText , "W-RS10\0" );
	
	strcpy( m_Kbd.group[2][0].box[ABOVE_RECT-1].szAdvText , "Up\0" );
	strcpy( m_Kbd.group[2][0].box[LEFT_OF_RECT-1].szAdvText , "Left\0" );
	strcpy( m_Kbd.group[2][0].box[BELOW_RECT-1].szAdvText , "Down\0" );
	strcpy( m_Kbd.group[2][0].box[RIGHT_OF_RECT-1].szAdvText , "Right\0" );
	
	strcpy( m_Kbd.group[2][1].box[ABOVE_RECT-1].szAdvText , "Shift\0" );
	strcpy( m_Kbd.group[2][1].box[LEFT_OF_RECT-1].szAdvText , "Space\0" );
	strcpy( m_Kbd.group[2][1].box[BELOW_RECT-1].szAdvText , "Normal\0" );
	strcpy( m_Kbd.group[2][1].box[RIGHT_OF_RECT-1].szAdvText , "Enter\0" );
	
	strcpy( m_Kbd.group[2][2].box[ABOVE_RECT-1].szAdvText , "Clear\0" );
	strcpy( m_Kbd.group[2][2].box[LEFT_OF_RECT-1].szAdvText , "<-BKSP\0" );
	strcpy( m_Kbd.group[2][2].box[BELOW_RECT-1].szAdvText , "Quit\0" );
	strcpy( m_Kbd.group[2][2].box[RIGHT_OF_RECT-1].szAdvText , "DEL\0" );
	
	strcpy( m_Kbd.group[2][3].box[ABOVE_RECT-1].szAdvText , "ALT\0" );
	strcpy( m_Kbd.group[2][3].box[LEFT_OF_RECT-1].szAdvText , "CTRL\0" );
	strcpy( m_Kbd.group[2][3].box[BELOW_RECT-1].szAdvText , "Tab\0" );
	strcpy( m_Kbd.group[2][3].box[RIGHT_OF_RECT-1].szAdvText , "Pause\0" );
	
	strcpy( m_Kbd.group[2][4].box[ABOVE_RECT-1].szAdvText , "\\\0" );
	strcpy( m_Kbd.group[2][4].box[LEFT_OF_RECT-1].szAdvText , "|\0" );
	strcpy( m_Kbd.group[2][4].box[BELOW_RECT-1].szAdvText , "<\0" );
	strcpy( m_Kbd.group[2][4].box[RIGHT_OF_RECT-1].szAdvText , ">\0" );

	//Elan09
	for(int i=0; i<NUMBER_OF_ROWS; ++i)
		for(int j=0; j<NUMBER_OF_COLS; ++j)
			for(int k=0; k<3; ++k)
				m_Kbd.group[i][j].normalColor[k] = cvScalar(255,255,255);
	
	
	
	m_dTextSizeScale = 1;
	m_nJitterThreshold = 3;

	m_layoutMode = EBOARDLAYOUT_MODE_NORMAL;
	
	PVI_POINT ptScreenSize = pvu::getScreenSize();
	m_rectBoard.set(((1-BOARD_WIDTH_PCT_OF_SCREEN)/2)*ptScreenSize.x,
		0,
		BOARD_WIDTH_PCT_OF_SCREEN*ptScreenSize.x,
		BOARD_HEIGHT_PCT_OF_SCREEN*ptScreenSize.y);
	/*Elan10
	m_rectBoard.set(100,0, 1000, 300);
	switch((int)pvu::getScreenSize().x) {
		case 1024:
			m_rectBoard &= 0.9;
			m_rectBoard.c.x -= 100;
			break;
		case 800:
			m_rectBoard &= 0.7;
			m_rectBoard.c -= PVI_POINT(200,100); 
			break;
	}
	*/

	//Elan09
	m_pWordCompletionSystem = new CWordCompletionSystem(DICTIONARY_FILENAME);
	strcpy(m_strCurrentTypedWord, "");

	m_bWaitingToType = false;
	m_bCursorMoved = false;
}

CNouseBoard::~CNouseBoard()
{
	cvDestroyWindow(m_strNouseboardDialogTitle);
	delete m_pWordCompletionSystem;
}


BEGIN_MESSAGE_MAP(CNouseBoard, CWnd)
END_MESSAGE_MAP()

void CNouseBoard::putCellText(char *szTxt, int nColGroup, int nRowGroup, int nWhichAreaInGroup, CIplImage *img)
{	
	//Elan09
	char szTxtActual[MAX_LABEL_LENGTH];
	if(strstr(szTxt, "Predict")) {
		int index;
		sscanf(szTxt, "Predict%d", &index);
		strcpy(szTxtActual, (index <= m_pWordCompletionSystem->m_nWordsFound) ? m_pWordCompletionSystem->m_strQueryResults[index-1] : "");
	} else if(!strcmp(szTxt, "Blank")) {
		strcpy(szTxtActual, "");
	} else {
		strcpy(szTxtActual, szTxt);
	}
	
	int nWidthOfABox  = img->getWidth () / (  NUMBER_OF_COLS * 2);
	int nHeightOfABox = img->getHeight() / ( NUMBER_OF_ROWS * 2);
	
	// Calculates the rectangle of the box to place the text in
	int nColPixel = nWidthOfABox  * 2 * nColGroup;
	int nRowPixel = nHeightOfABox * 2 * nRowGroup;

	
	switch (nWhichAreaInGroup)
	{
		case(0): 
			nColPixel += nWidthOfABox/2;
			break;
		case(1): 
			nRowPixel += nHeightOfABox; 
			nRowPixel -= nHeightOfABox/2;
			break;
		case(2): 
			nColPixel += nWidthOfABox ; 
			nRowPixel += nHeightOfABox; 
			nColPixel -= nWidthOfABox/2; 
			break;
		case(3): 
			nColPixel += nWidthOfABox ; 
			nRowPixel += nHeightOfABox/2; 
			break;
		default: assert(0); break; // Wrong input.
	}

	CvRect rect = cvRect( nColPixel, nRowPixel, nWidthOfABox, nHeightOfABox);
	
	CvPoint ptBtmLeft;
	
	// Initilize the font to something resonable
	CvFont cvFont;
	int nSize = (int)((double)rect.height * 1.5 * m_dTextSizeScale); 

	cvInitFont( &cvFont, CV_FONT_HERSHEY_SIMPLEX, (double)nSize/100.0, (double)nSize/100.0, 0.0, 2);
	
	
	CvSize textSize; int yBaseline;
	cvGetTextSize( szTxtActual, &cvFont, &textSize, &yBaseline );	
	int nTextWidth  = textSize.width;
	int nTextHeight = textSize.height;
	
	
	double dShrinkFactor = 0.95;
	while (nTextWidth > rect.width) // Initilize a new font if it's too big
	{
		// Shrink factor
		int nSize = (int)( (double)(rect.height) * 1.5 * dShrinkFactor); //nSize = nSize < 10 ? 10 : nSize;
		dShrinkFactor = dShrinkFactor * dShrinkFactor;
		//cvInitFont( &cvFont, CV_FONT_VECTOR0 , (double)nSize/100.0, (double)nSize/100.0, 0.0, 1 );
		cvInitFont( &cvFont, CV_FONT_HERSHEY_SIMPLEX, (double)nSize/100.0, (double)nSize/100.0, 0.0, 1 );
		cvGetTextSize( szTxtActual, &cvFont, &textSize, &yBaseline );	
		nTextWidth  = textSize.width;
		nTextHeight = textSize.height;

	}		
	
	switch (nWhichAreaInGroup)
	{
	case(0): 
		{
		ptBtmLeft.x = rect.x + (int) ( rect.width  - nTextWidth )/2;
		ptBtmLeft.y = rect.y + nTextHeight +3;
		break;
		}
	case(3):
		{
		ptBtmLeft.x = rect.x + rect.width - nTextWidth -3;
		ptBtmLeft.y = rect.y + (int) ( rect.height - nTextHeight)/2 + nTextHeight;
		break;
		}
	case(1): 
		{
		ptBtmLeft.x = rect.x+3 ;
		ptBtmLeft.y = rect.y + (int) ( rect.height - nTextHeight)/2 + nTextHeight;
		break;
		}

	case(2): 
		{
		ptBtmLeft.x = rect.x + (int) ( rect.width  - nTextWidth )/2;
		ptBtmLeft.y = rect.y + rect.height -3;
		break;
		}

	default: assert(0); break; // Wrong input.
	}
		
	
	cvPutText( img->getIplImage(), szTxtActual, ptBtmLeft, &cvFont, CV_RGB(0,0,0) );	
}


bool CNouseBoard::redrawWindow()
{
	//Elan09: Nouseboard always on top
	::SetForegroundWindow(m_wndNouseBoard);
	
	RECT wndRect;
	::GetClientRect(m_wndNouseBoard, &wndRect);
	
	//If NouseBoard has been closed
	if(wndRect.left != 0) 
		return false;
	
	CIplImage img; img.initialize(wndRect.right - wndRect.left, wndRect.bottom - wndRect.top , 24);
	
	int nWidthOfASquare  = img.getWidth()  / (2*NUMBER_OF_COLS);
	int nHeightOfASquare = img.getHeight() / (2*NUMBER_OF_ROWS );
	
	cvRectangle( img.getIplImage(), cvPoint(0,0), cvPoint(img.getWidth(), img.getHeight() ), CV_RGB(255,255,255), CV_FILLED, 8, 0 );
		
	CvScalar clrSuggestionBk = CV_RGB(0,255,0);

	//Elan09
	for(int row= 0; row < NUMBER_OF_ROWS; ++row) {
		for(int col=0; col < NUMBER_OF_COLS; ++col) {
			// Filling
			cvRectangle(img.getIplImage(), cvPoint(col*nWidthOfASquare*2+1, row*nHeightOfASquare*2+1), 
				cvPoint((col+1)*nWidthOfASquare*2-1, (row+1)*nHeightOfASquare*2-1), 
				m_Kbd.group[row][col].normalColor[m_layoutMode], CV_FILLED);
			// Outline
			cvRectangle(img.getIplImage(), cvPoint(col*nWidthOfASquare*2, row*nHeightOfASquare*2), 
				cvPoint((col+1)*nWidthOfASquare*2, (row+1)*nHeightOfASquare*2), cvScalar(0), 2);
		}
	}
	

	///------SELECTION RECTANGLE ----------- Show the selection Rectangle
	CvScalar clrSelectionRectangleColor = CV_RGB(255, 0, 255);

	int nPixelRow = m_nSelectedRow * nHeightOfASquare * 2 + 1;
	int nPixelCol = m_nSelectedCol * nWidthOfASquare  * 2 + 1;
	CvPoint ptTopRight = cvPoint( nPixelCol, nPixelRow);
	
	nPixelRow = (m_nSelectedRow + 1) * nHeightOfASquare * 2 - 1 ;
	nPixelCol = (m_nSelectedCol + 1) * nWidthOfASquare  * 2 - 1 ;
	CvPoint ptBotmLeft = cvPoint( nPixelCol, nPixelRow);
	
	cvRectangle( img.getIplImage(), ptTopRight, ptBotmLeft, clrSelectionRectangleColor, 6);
	if (m_bWaitingToType)
		cvRectangle( img.getIplImage(), ptTopRight, ptBotmLeft, clrSuggestionBk, CV_FILLED, 8, 0);
	
	for(int nGrpRow = 0 ; nGrpRow < NUMBER_OF_ROWS; nGrpRow ++)
	{
		for(int nGrpCol = 0 ; nGrpCol < NUMBER_OF_COLS ; nGrpCol ++)
		{
			switch(m_layoutMode)
			{
				case(EBOARDLAYOUT_MODE_SHIFT):
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[ABOVE_RECT-1].szShiftText, nGrpCol,nGrpRow,0, &img);
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[LEFT_OF_RECT-1].szShiftText, nGrpCol,nGrpRow,1, &img );
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[BELOW_RECT-1].szShiftText , nGrpCol,nGrpRow,2, &img);
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[RIGHT_OF_RECT-1].szShiftText, nGrpCol,nGrpRow,3, &img);
					break;
				case(EBOARDLAYOUT_MODE_ADV):
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[ABOVE_RECT-1].szAdvText, nGrpCol,nGrpRow,0, &img );
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[LEFT_OF_RECT-1].szAdvText, nGrpCol,nGrpRow,1, &img );
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[BELOW_RECT-1].szAdvText, nGrpCol,nGrpRow,2, &img );
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[RIGHT_OF_RECT-1].szAdvText, nGrpCol,nGrpRow,3, &img );
					break;
				default:
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[ABOVE_RECT-1].szNormalText, nGrpCol,nGrpRow,0, &img );
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[LEFT_OF_RECT-1].szNormalText, nGrpCol,nGrpRow,1, &img );
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[BELOW_RECT-1].szNormalText, nGrpCol,nGrpRow,2, &img );
					putCellText(m_Kbd.group[nGrpRow][nGrpCol].box[RIGHT_OF_RECT-1].szNormalText, nGrpCol,nGrpRow,3, &img );
					break;
			}

		}
	}	
	cvShowImage(m_strNouseboardDialogTitle, img.getIplImage() );

	return true;
}
	
void CNouseBoard::hide()
{
	cvDestroyWindow(m_strNouseboardDialogTitle);
}


PVI_POINT CNouseBoard::getCenterOfSelectedSquare()
{
	//Elan09: Use getBoardRect() instead of m_rectBoard
	PVI_VECTOR squareWidthHeight = getSquareWidthHeight();
	int x = m_rectBoard.getLeft() + (squareWidthHeight.x * m_nSelectedCol) + (squareWidthHeight.x / 2);
	int y = m_rectBoard.getTop() + (squareWidthHeight.y * m_nSelectedRow) + (squareWidthHeight.y / 2);
	return PVI_POINT(x,y);
}

void CNouseBoard::show()
{
	cvNamedWindow (m_strNouseboardDialogTitle, 0);
	cvResizeWindow(m_strNouseboardDialogTitle, m_rectBoard.s.x, m_rectBoard.s.y );
	cvMoveWindow(m_strNouseboardDialogTitle, m_rectBoard.getLeft(), m_rectBoard.getTop());
	
	m_wndNouseBoard = (HWND) cvGetWindowHandle( m_strNouseboardDialogTitle );
	::SetForegroundWindow(m_wndNouseBoard);
}

void CNouseBoard::type(EPointRectComparison ePointRectComparison)
{
	switch(m_layoutMode)
	{
		case(EBOARDLAYOUT_MODE_SHIFT):
			strcpy(m_strToType, m_Kbd.group[m_nSelectedRow][m_nSelectedCol].box[ePointRectComparison -1 ].szShiftText);
			break;
		case(EBOARDLAYOUT_MODE_ADV):
			strcpy(m_strToType, m_Kbd.group[m_nSelectedRow][m_nSelectedCol].box[ePointRectComparison - 1].szAdvText);
			break;
		default:
			strcpy(m_strToType, m_Kbd.group[m_nSelectedRow][m_nSelectedCol].box[ePointRectComparison - 1].szNormalText);
			break;
	}

	if(!strcmp(m_strToType, "Shift")) {
		m_layoutMode = EBOARDLAYOUT_MODE_SHIFT;
		return;
	}
	else if(!strcmp(m_strToType, "Adv")) {
		m_layoutMode = EBOARDLAYOUT_MODE_ADV;
		return;
	}
	else if(!strcmp(m_strToType, "Normal")) {
		m_layoutMode = EBOARDLAYOUT_MODE_NORMAL;
		return;
	}


	char arrStrDontType[3][20];
	//strcpy(arrStrDontType[0], "Recalibrate");
	strcpy(arrStrDontType[0], "Quit");
	strcpy(arrStrDontType[1], "Clear");
	strcpy(arrStrDontType[2], "Pause");
	bool bPressSomething = true;
	int i;
	for(i=0; i<3; ++i) {
		if(strcmp(m_strToType, arrStrDontType[i]) == 0) {
			bPressSomething = false;
			break;
		}
	}		

	int nKeyCode;

	//Elan09
	int nSleepLength = 100;
	if(strstr(m_strToType, "Predict") || !strcmp(m_strToType, "<-BKSP.")) {

		if(strstr(m_strToType, "Predict")) {
			int index;
			sscanf(m_strToType, "Predict%d", &index);
			index--;
			for(i = strlen(m_strCurrentTypedWord); i < strlen(m_pWordCompletionSystem->m_strQueryResults[index]); ++i) {
				nKeyCode = VkKeyScan(m_pWordCompletionSystem->m_strQueryResults[index][i]);
				keybd_event(nKeyCode,0,0 , 0);
				keybd_event(nKeyCode,0, KEYEVENTF_KEYUP,0);
			}
			keybd_event(VK_SPACE,0,0 , 0);
			keybd_event(VK_SPACE,0, KEYEVENTF_KEYUP,0);
		} else {
			keybd_event(VK_BACK,0,0 , 0);
			keybd_event(VK_BACK,0, KEYEVENTF_KEYUP,0);
			keybd_event(VkKeyScan('.'),0,0 , 0);
			keybd_event(VkKeyScan('.'),0, KEYEVENTF_KEYUP,0);
			keybd_event(VK_SPACE,0,0 , 0);
			keybd_event(VK_SPACE,0, KEYEVENTF_KEYUP,0);
		}
		bPressSomething = false;
	} else if(!strcmp(m_strToType, "Blank")) {
		bPressSomething = false;
	}

	if(bPressSomething) {
		bool bTypeChar = false;
		bool bTypeLetter = false;
			
			
		if(strcmp(m_strToType, "Space") == 0) 
			nKeyCode = VK_SPACE;
		else if(strcmp(m_strToType, "Enter") == 0) 
			nKeyCode = VK_RETURN;
		else if(strcmp(m_strToType, "Up") == 0)  //TODO: Left, right, up and down don't work correctly
			nKeyCode = VK_UP;
		else if(strcmp(m_strToType, "Down") == 0) 
			nKeyCode = VK_DOWN;
		else if(strcmp(m_strToType, "Left") == 0) 
			nKeyCode = VK_LEFT;
		else if(strcmp(m_strToType, "Right") == 0) 
			nKeyCode = VK_RIGHT;
		else if(strcmp(m_strToType, "<-BKSP") == 0) 
			nKeyCode = VK_BACK;
		else if(strcmp(m_strToType, "Tab") == 0) 
			nKeyCode = VK_TAB;
		else if(strcmp(m_strToType, "DEL") == 0) 
			nKeyCode = VK_DELETE;
			
		
		else  {
			nKeyCode = m_strToType[0];
			bTypeChar = true;
			bTypeLetter = pvu::isLetter(m_strToType[0]);
		}

			

		bool bPressShift = bTypeChar && (m_layoutMode == EBOARDLAYOUT_MODE_SHIFT);
		if(bTypeChar) nKeyCode = VkKeyScan(nKeyCode);
		int nKeyComb = div(nKeyCode, 16*16).quot;		// if the high bit hex(nKeyCode) = 1,  SHIFT key is pressed; 2	Either CTRL key is pressed. 4	Either ALT key is pressed.
		if((bPressShift) || (nKeyComb == 1) )
			keybd_event(VK_LSHIFT,0,0 , 0);
		
		keybd_event(nKeyCode,0,0 , 0);
		keybd_event(nKeyCode,0, KEYEVENTF_KEYUP,0);
		
				
		if ((bPressShift) || (nKeyComb == 1) )
			keybd_event(VK_LSHIFT,0,KEYEVENTF_KEYUP , 0);

			
		if(bTypeChar) {//Letter) {
			char typedLetter[2];
			typedLetter[0] = m_strToType[0];
			typedLetter[1] = '\0';
			strcat(m_strCurrentTypedWord, typedLetter);
		} else if(nKeyCode == VK_BACK) { 
			int nLength = strlen(m_strCurrentTypedWord);
			if(nLength)
				m_strCurrentTypedWord[nLength-1] = '\0';
		} else {
			strcpy(m_strCurrentTypedWord,"");
			m_pWordCompletionSystem->clearQuery();
		}
		m_pWordCompletionSystem->queryPrefix(m_strCurrentTypedWord);
	} else {
		//Elan09
		if(strcmp(m_strToType, "Blank")) {
			strcpy(m_strCurrentTypedWord,"");
			m_pWordCompletionSystem->clearQuery();
		}
	}
}


PVI_VECTOR CNouseBoard::getSquareWidthHeight()
{
	return PVI_VECTOR(m_rectBoard.s.x / NUMBER_OF_COLS, m_rectBoard.s.y / NUMBER_OF_ROWS);	
}