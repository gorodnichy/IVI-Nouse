#pragma once
#include "../NouseVisionLibrary/pvi-utility.h"

#define PAD_WIDTH_PCT_OF_SCREEN 0.3 
#define PAD_HEIGHT_PCT_OF_SCREEN 0.25
#define PAD_TOP_PCT_OF_SCREEN 0.45

// CNousePad dialog

class CNousePad : public CDialog
{
	DECLARE_DYNAMIC(CNousePad)

public:
	CNousePad(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNousePad();

// Dialog Data
	enum { IDD = /*IDD_DIALOG_NOUSEPAD*/135 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strText;
	CString m_strNousepadDialogTitle;

	void deleteLastWord();
	PVI_RECT m_rectBoard;
	double m_dTextSizeScale;
	void clear();
	void copyAndClose();
	//void setLocationUnderBoard();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
