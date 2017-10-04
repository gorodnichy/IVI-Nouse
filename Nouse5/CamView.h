#pragma once
// CamView.h : header file
//
#include "../NouseVisionLibrary/IplImage.h"
/////////////////////////////////////////////////////////////////////////////
// CCamView window

class CCamView : public CWnd
{
// Construction
public:
	CCamView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamView)
	//}}AFX_VIRTUAL

// Implementation
public:
	int CreateCamWnd(CWnd* pParent, const RECT& r);
	CIplImage * m_pImage;
	void SetImage(CIplImage *pImage);
	virtual ~CCamView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCamView)
	afx_msg void OnPaint();
	//afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};



