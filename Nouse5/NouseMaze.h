#pragma once
#include "cv.h"
#include "highgui.h"

#define NOUSE_MAZE_WINDOW_NAME "Nouse Maze"

class CNouseMaze
{
public:
	CNouseMaze(void);
	~CNouseMaze(void);
	bool activate(const char* strImageLocation);
	void deactivate();

	IplImage* m_pImgMaze;
	bool m_bTouchingWall;
	bool m_bActivated;
};

