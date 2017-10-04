// CamView.cpp : implementation file
//

#include "stdafx.h"

#include "CamView.h"

/////////////////////////////////////////////////////////////////////////////
// CCamView

CCamView::CCamView  ()
{
	this->m_pImage = NULL;
}

CCamView::~CCamView()
{
	this->m_pImage = NULL;
}


BEGIN_MESSAGE_MAP(CCamView, CWnd)
	//{{AFX_MSG_MAP(CCamView)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamView message handlers



void CCamView::OnPaint() 
{
	
		CPaintDC dc(this); // device context for painting
		
		// Should lock the image.
		//((CPropSheetMain*)(this->GetParent()->GetParent()))->m_imgIn.draw(dc.GetSafeHdc(), &a, 1);
		if (this->m_pImage)
		{
			//TRACE("CCamView::OnPaint() \n");
			//dc.LineTo(30,30);
			RECT a; 
			this->GetClientRect(&a);
			//for (long i=0;i<40;i++) TRACE("%d",this->m_pImage->Get ->m_iplImage.imageData[i] );
			this->m_pImage->draw(dc.GetSafeHdc(), &a, true);
		}
		// Do not call CStatic::OnPaint() for painting messages
	
	
}


void CCamView::SetImage(CIplImage *pImage)
{
	//Elan10
	//if ( ::IsWindow( this->GetSafeHwnd() )) {
	if(m_hWnd) {
		this->m_pImage = pImage;
		
		this->Invalidate(0); // Force a redraw if CamWindow is visible
	}
}

int CCamView::CreateCamWnd(CWnd *pParent, const RECT &r)
{
	DWORD dwStyle = 0;
	dwStyle = dwStyle 
				|	WS_BORDER   /// no effect... 
				&~	WS_CAPTION
				|	WS_CHILD        
			//	|	WS_DISABLED
				|   WS_DLGFRAME
				&~	WS_HSCROLL     
				//WS_CLIPSIBLINGS // Won't display     
				&~	WS_MAXIMIZEBOX  
				&~	WS_MINIMIZEBOX 
				&~	WS_POPUP		 
				//	WS_POPUPWINDOW   // Negates the WS_BORDER when disabled
				&~	WS_SYSMENU     
				&~	WS_TABSTOP  
				//WS_THICKFRAME
				&~  WS_VSCROLL
			; //  Do not use the WS_VISIBLE flag, otherwise, IsWindowVisible always returns true (I think)

	// Now make sure it is 4:3 aspect Ratio always, by taking the biggest part of the width or height
	
	CRect r2(r);

	// The rectangle is not high enough
	if( ((double)(r2.Width()))/((double)(r2.Height())) > 4.0/3.0 )
	{
		r2.bottom = (int)(3.0*((double)(r2.Width()))/4.0) + r2.top;
	}
	// The rectangle is not Wide enough
	if( ((double)(r2.Width()))/((double)(r2.Height())) < 4.0/3.0 )
	{
		r2.right = (int)(4.0*((double)(r2.Height()))/3.0) + r2.left;
	}

	// Here to modify any creation styles in case it stops working in the future...or extend funcitonality
	int ret = this->Create( NULL, NULL, dwStyle, r2, pParent, 0, NULL);
	
	//CRect adjust(0,0,160,120);
	CRect adjust( 0,0,r2.Width(),r2.Height() );
	if (adjust.Width() < 160) 
	{
		adjust.right  = 160;
		adjust.bottom = 120;
	}

	
	this->CalcWindowRect(&adjust, CWnd::adjustBorder);
	this->MoveWindow(r2.left, r2.top, adjust.Width(), adjust.Height());

	this->ShowWindow(SW_SHOW);
	return ret;
}




/*
void CCamView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (this->GetParent() != NULL)
	{
		CPoint * pPoint2Send = new CPoint(point.x, point.y);
		//((CPropertyPage*)this->GetParent())->SendMessage(WM_USER_CAM_IMAGE_WAS_CLICKED, (LPARAM) this, (WPARAM) pPoint2Send );
		//((CPropertyPage*)this->GetParent())->SendMessage(WM_USER_CAM_IMAGE_WAS_CLICKED, (LPARAM) this, MAKELPARAM(point.x,point.y) );
		((CPropertyPage*)this->GetParent())->SendMessage(WM_USER_CAM_IMAGE_WAS_CLICKED, (WPARAM) this, (LPARAM) pPoint2Send);
	}
	CWnd::OnLButtonDown(nFlags, point);
} 


void CCamView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
*/
