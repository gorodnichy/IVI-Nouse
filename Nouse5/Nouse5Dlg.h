
// Nouse5Dlg.h : header file
//
#define TIMER_FREQUENCY 15
#define CURRENT_SETTINGS_LOCATION_FILENAME _T("currentSettingsFileLocation.txt")
#define CONSTANTS_FILENAME _T("constants.txt")
#define TEMP_MARKER_FILENAME _T("temp")
#define TOKEN_STRING _T(" =\t")

#define DMITRY_TESTS 0
#define USE_ACTIVATION_KEY 1
#define ACTIVATION_KEY_FILENAME _T("activation.txt")
#define IS_TRIAL_VERSION 1
//#define IS_TRIAL_VERSION 0
//#define DAYS_IN_TRIAL 90l
#define DAYS_IN_TRIAL 1l  // 30l
#define SECRET_REGISTRY_LOCATION _T("SOFTWARE\\Primrose")
#define REGISTRY_TIME_VARIABLE_NAME _T("Value")

#define VOICE_RECOGNITION_ACTIVATED 1
#if VOICE_RECOGNITION_ACTIVATED
#include <sphelper.h>
#define WM_RECOEVENT    WM_USER+5      // Window message used for recognition events
#define GID_CC   0           // CC grammar has grammar ID 0
#define GID_DICT   1           // CC grammar has grammar ID 0
#endif


#include "../NouseVisionLibrary/DirectShowSource.h"
#include "CamView.h"
#include "../NouseVisionLibrary/PVS.h"
#include "StateReady.h"
#include "StateCalibration.h"
#include "StateCursor.h"
#include "NouseCursor.h"
#include "../NouseVisionLibrary/NouseTracker.h"
#include "../NouseSettings/DataHandler.h"
#pragma once

#if DMITRY_TESTS
class CUser
{
// Construction
public:
	CUser()
	{

		CStdioFile fUser("korystuvach.dan", CFile::modeRead); 
		fUser.ReadString(strCurrentSettingsFile); 
		fUser.Close();
	
		FILE *f; f = fopen("korystuvach.dan", "rb"); 
		if (!f) {
			f = fopen("korystuvach.dan", "wb"); 
			writef(f, sizeof(CUser), CUser(initiate));
            fprintf(f, "%S \t \t %S\n", (LPCTSTR)strEmail, (LPCTSTR)encodedEmail);
            fprintf(f, "%s \t \t %s\n", (LPCTSTR)strEmail, CT2A(encodedEmail));
            fprintf(f, "%S \t \t %S\n", CT2A(strEmail), CT2A(encodedEmail));
			// encodedEmail.GetString();
             fclose(f);

	CFileStatus status;
	if(CFile::GetStatus(strCurrentSettingsFile, status)) {
		CStdioFile fileSettings(strCurrentSettingsFile, CFile::modeRead);
		loadSettings(&fileSettings);
		fileSettings.Close();
	}
	}


	time_t timeInReg = strtol(strDateVal,&p,0);
	CTime cTimeInReg(timeInReg);
	CTimeSpan cTimeSpanTrialLength(DAYS_IN_TRIAL, 0, 0, 0);
	CTime cTimeExpiry = cTimeInReg + cTimeSpanTrialLength;
	CTime cTimeNow(timeNow);
	//CTimeSpan cTimeSpanToAddToNow(15, 0, 0, 0);
	//CTimeSpan cTimeSpanLeftInTrial = cTimeExpiry - (cTimeNow + cTimeSpanToAddToNow);
	CTimeSpan cTimeSpanLeftInTrial = cTimeExpiry - cTimeNow;
	long lDaysLeftInTrial = cTimeSpanLeftInTrial.GetDays() + 1;
	if(lDaysLeftInTrial == (DAYS_IN_TRIAL+1))
		lDaysLeftInTrial = DAYS_IN_TRIAL;
	
	CString strName, strEmail, 	CString strLicenseKey, strPC;
	char strDateFirstUse[256], strDateLastUse[256];
	long lTimesUsed;
	time_t timeNow = time(0);
	int nRetVal = pvu::registryTransaction(HKEY_LOCAL_MACHINE,SECRET_REGISTRY_LOCATION, REGISTRY_TIME_VARIABLE_NAME, true, strDateVal); 
	if(nRetVal != 0) {
		sprintf(strDateVal, "%d", timeNow);

}
#endif

// CNouse5Dlg dialog
class CNouse5Dlg : public CDialog
{
// Construction
public:
	CNouse5Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NOUSE5_DIALOG };
	CStatic	m_pictureBoxCamPlaceholder;
	void CNouse5Dlg::SetTrialStatus(bool bTrial) { m_stateCursor.m_bTrialExpired = bTrial; }
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
#if VOICE_RECOGNITION_ACTIVATED
	//afx_msg void OnRecoEvent();
	afx_msg LRESULT OnRecoEvent(WPARAM wp, LPARAM lp);
#endif
	DECLARE_MESSAGE_MAP()

	

private:
	CDirectShowSource m_directShowSource;
	CCamView m_camView;
	//CIplImage m_cIplImage;
	CPVS m_pvs;
	bool m_bUseLightNormalization;
	int m_nProcessLoad;
	CStateReady m_stateReady;
	CStateCalibration m_stateCalibration;
	CStateCursor m_stateCursor;
	CState* m_pCurrentState;

	CState* getStateFromName(EState eState);
	void updateFromSettingsFile();
	void loadSettings(CStdioFile* pSettingsFile);
	void loadConstants(CStdioFile* pConstantsFile);
	CNouseTracker m_nouseTracker;
	CNouseCursor m_nouseCursor;
	
	bool m_bMirrorCameraImage;
	bool m_bNouseEnabled;
	int m_iWebcamIndex;
	int m_iCurrentWebcamIndex;
	bool m_bUseVoiceCommands;

	bool setWebcam();

	bool m_bEnableSounds;

	void showContextMenu();
	CMFCPopupMenu* m_pPopupMenu;

	//Constants
	CString m_strMainDialogTitle;
	CString m_strRecalibrate;
	CString m_strEnable;
	CString m_strDisable;
	CString m_strExit;
	CString m_strSettings;
	CString m_strPause;
	CString m_strUnpause;
	CString m_strNouseboard;
	CString m_strCouldNotInitializeWebcam;
	CString m_strDrag;
	CString m_strNouseTrialInfo;
	CString m_strNouseTrademark;
	CString m_strDaysLeftInTrial;
	CString m_strTrialExpired;
	CString m_strExitWarning;
	CString m_strWarningCaption;
	CString m_strDisableWarning;
/*
#if IS_TRIAL_VERSION
	void handleTrialBusiness();
	bool CNouse5Dlg::handleActivationKey();
int CNouse5Dlg::registryTransaction(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, bool bTrueGetFalseSet, char* strVal);

#endif
*/
	bool m_bTrialExpired; // =false;
//	CSettingsHandler m_SettingsHandler;

public:
	//void OnTimer(UINT nIDEvent);//32 bits
	afx_msg void OnTimer(UINT_PTR nIDEvent); //Fixed for 64
	void exitNouse();
	void preparePVS(IplImage* img);
	bool handleStates(EState eStartState, EState eNewState);
	afx_msg void OnBnClickedButtonDisable();
	CButton m_btnDisableEnable;
	afx_msg void OnBnClickedButtonSettings();
	afx_msg void OnBnClickedButtonPause();
	CButton m_btnPauseUnpause;
	CButton m_btnNouseboard;
	afx_msg void OnBnClickedButtonRecalibrate();
	afx_msg void OnBnClickedButtonNouseboard();
	CButton m_btnRecalibrate;
	CButton m_btnExit;
	CButton m_btnSettings;

#if VOICE_RECOGNITION_ACTIVATED
	//Boolean variables
	BOOL m_bReco;
	BOOL m_bSound;
	//Initialize the Recognizer
	CComPtr<ISpRecognizer> cpRecoEngine;

	//The ISpRecoContext interface enables applications to create 
	//different functional views or contexts of the SR engine
	CComPtr<ISpRecoContext>     m_cpRecoCtxt;

	//The ISpRecoGrammar interface enables applications to manage 
	//the words and phrases that the SR engine will recognize.
	CComPtr<ISpRecoGrammar>		m_cpCCGrammar;
	CComPtr<ISpRecoGrammar>		m_cpDictGrammar;
	void handleVoiceCommands();
#endif
	CString m_strCurrentVoiceCommand;
	afx_msg void OnUpExit();
	afx_msg void OnUpDisable();
	afx_msg void OnUpSettings();
	afx_msg void OnUpRecalibrate();
	afx_msg void OnUpNouseboard();
	afx_msg void OnUpDrag();
	afx_msg void OnUpPause();
	afx_msg void OnUpPaste();
	afx_msg void OnUpEnter();
	afx_msg void OnUpdateUpDrag(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUpPause(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUpNouseboard(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUpRecalibrate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUpSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUpDisable(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUpExit(CCmdUI *pCmdUI);

	afx_msg LRESULT OnNouseSettingsUpdate(WPARAM wParam, LPARAM lParam);
};
