#include "StdAfx.h"
#include "NouseMaze.h"

void mazeCallback( int event, int x, int y, int flags, void* param ) {
	if(event == CV_EVENT_MOUSEMOVE) {
		CNouseMaze* pNouseMaze = (CNouseMaze*)param;
		CvScalar value = cvGet2D(pNouseMaze->m_pImgMaze, y, x);
		pNouseMaze->m_bTouchingWall = value.val[0] == 0;
	}
}

CNouseMaze::CNouseMaze(void)
{
	m_pImgMaze = NULL;
	m_bTouchingWall = false;
	m_bActivated = false;
}


CNouseMaze::~CNouseMaze(void)
{
	deactivate();
}

bool CNouseMaze::activate(const char* strImageLocation) {
	IplImage* pImgMazeOrig = cvLoadImage(strImageLocation, 0);
	m_bActivated = pImgMazeOrig != NULL;
	if(m_bActivated) {
		m_pImgMaze = cvCreateImage(cvGetSize(pImgMazeOrig), pImgMazeOrig->depth, 1);
		cvThreshold(pImgMazeOrig, m_pImgMaze, 100, 255, CV_THRESH_BINARY);
		cvNamedWindow(NOUSE_MAZE_WINDOW_NAME);
		cvShowImage(NOUSE_MAZE_WINDOW_NAME, m_pImgMaze);
		cvSetMouseCallback(NOUSE_MAZE_WINDOW_NAME, mazeCallback, this);
		cvReleaseImage(&pImgMazeOrig);
	}

	return m_bActivated;
}

void CNouseMaze::deactivate() {
	if(m_pImgMaze)
		cvReleaseImage(&m_pImgMaze);
	m_pImgMaze = NULL;
	cvDestroyWindow(NOUSE_MAZE_WINDOW_NAME);
	m_bActivated = false;
	m_bTouchingWall = false;
}
