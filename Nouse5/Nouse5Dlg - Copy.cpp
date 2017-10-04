
// Nouse5Dlg.cpp : implementation file
//

#include "stdafx.h"
//#include "vld.h"

#include "Nouse5.h"
#include "Nouse5Dlg.h"

#include <highgui.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CNouse5Dlg dialog
CNouse5Dlg::CNouse5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNouse5Dlg::IDD, pParent),
	m_bMirrorCameraImage(true),
	m_nProcessLoad(1),
	m_bUseLightNormalization(false),
	m_bNouseEnabled(true),
	m_iWebcamIndex(0),
	m_iCurrentWebcamIndex(0),
	m_bUseVoiceCommands(false),
	m_bEnableSounds(true),
	m_pPopupMenu(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_stateCalibration.m_pNouseTracker = m_stateCursor.m_pNouseTracker = &m_nouseTracker;
	m_stateCalibration.m_pNouseControl = m_stateReady.m_pNouseControl = &m_stateCursor.m_nouseControl;
	m_stateCursor.m_pnCursorWidth = &m_nouseCursor.m_nWidth;
	m_stateCursor.m_pTimeWhenCursorArrivedAtPos = &m_nouseCursor.m_timeWhenArrivedAtPos;
	m_strCurrentVoiceCommand = "";
	m_stateCalibration.m_pbEnableSounds = m_stateCursor.m_pbEnableSounds = &m_bEnableSounds;
}

void CNouse5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE_BOX, m_pictureBoxCamPlaceholder);
	DDX_Control(pDX, IDC_BUTTON_DISABLE, m_btnDisableEnable);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_btnPauseUnpause);
	DDX_Control(pDX, IDC_BUTTON_RECALIBRATE, m_btnRecalibrate);
	DDX_Control(pDX, IDCANCEL, m_btnExit);
	DDX_Control(pDX, IDC_BUTTON_SETTINGS, m_btnSettings);
	DDX_Control(pDX, IDC_BUTTON_NOUSEBOARD, m_btnNouseboard);
}

BEGIN_MESSAGE_MAP(CNouse5Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_THREAD_MESSAGE(WM_TIMER, OnTimer)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_DISABLE, &CNouse5Dlg::OnBnClickedButtonDisable)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS, &CNouse5Dlg::OnBnClickedButtonSettings)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CNouse5Dlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_RECALIBRATE, &CNouse5Dlg::OnBnClickedButtonRecalibrate)
	ON_BN_CLICKED(IDC_BUTTON_NOUSEBOARD, &CNouse5Dlg::OnBnClickedButtonNouseboard)
#if VOICE_RECOGNITION_ACTIVATED
	ON_MESSAGE(WM_RECOEVENT,OnRecoEvent)
#endif
	ON_COMMAND(ID_UP_EXIT, &CNouse5Dlg::OnUpExit)
	ON_COMMAND(ID_UP_DISABLE, &CNouse5Dlg::OnUpDisable)
	ON_COMMAND(ID_UP_SETTINGS, &CNouse5Dlg::OnUpSettings)
	ON_COMMAND(ID_UP_RECALIBRATE, &CNouse5Dlg::OnUpRecalibrate)
	ON_COMMAND(ID_UP_NOUSEBOARD, &CNouse5Dlg::OnUpNouseboard)
	ON_COMMAND(ID_UP_DRAG, &CNouse5Dlg::OnUpDrag)
	ON_COMMAND(ID_UP_PAUSE, &CNouse5Dlg::OnUpPause)
	ON_COMMAND(ID_UP_PASTE, &CNouse5Dlg::OnUpPaste)
	ON_COMMAND(ID_UP_ENTER, &CNouse5Dlg::OnUpEnter)
	ON_UPDATE_COMMAND_UI(ID_UP_DRAG, &CNouse5Dlg::OnUpdateUpDrag)
	ON_UPDATE_COMMAND_UI(ID_UP_PAUSE, &CNouse5Dlg::OnUpdateUpPause)
	ON_UPDATE_COMMAND_UI(ID_UP_NOUSEBOARD, &CNouse5Dlg::OnUpdateUpNouseboard)
	ON_UPDATE_COMMAND_UI(ID_UP_RECALIBRATE, &CNouse5Dlg::OnUpdateUpRecalibrate)
	ON_UPDATE_COMMAND_UI(ID_UP_SETTINGS, &CNouse5Dlg::OnUpdateUpSettings)
	ON_UPDATE_COMMAND_UI(ID_UP_DISABLE, &CNouse5Dlg::OnUpdateUpDisable)
	ON_UPDATE_COMMAND_UI(ID_UP_EXIT, &CNouse5Dlg::OnUpdateUpExit)
END_MESSAGE_MAP()


// CNouse5Dlg message handlers
BOOL CNouse5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CStdioFile fileConstants(CONSTANTS_FILENAME, CFile::modeRead);
	loadConstants(&fileConstants);

#if IS_TRIAL_VERSION
	handleTrialBusiness();
#endif

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	RECT a;
	m_pictureBoxCamPlaceholder.GetWindowRect(&a);
	ScreenToClient(&a);
	a.right  = a.left + 320;
	a.bottom = a.top  + 240;

#if VOICE_RECOGNITION_ACTIVATED
	HRESULT hr=S_OK;

	hr=cpRecoEngine.CoCreateInstance(CLSID_SpInprocRecognizer);

	if( SUCCEEDED(hr) )
	{
		hr = cpRecoEngine->CreateRecoContext(&m_cpRecoCtxt);
	}

	if( SUCCEEDED(hr) )
	{
		hr=m_cpRecoCtxt->SetNotifyWindowMessage(m_hWnd,WM_RECOEVENT, 0, 0 );
	}
	
	if (SUCCEEDED(hr))
    {
        // This specifies which of the recognition events are going 
		//to trigger notifications.Here, all we are interested in 
		//is the beginning and ends of sounds, as well as
        // when the engine has recognized something
		//using ISpRecoContext
        const ULONGLONG ullInterest = SPFEI(SPEI_RECOGNITION);
        hr = m_cpRecoCtxt->SetInterest(ullInterest, ullInterest);
    }

	 // create default audio object
    CComPtr<ISpAudio> cpAudio;
    hr = SpCreateDefaultObjectFromCategoryId(SPCAT_AUDIOIN, &cpAudio);

    // set the input for the engine
    hr = cpRecoEngine->SetInput(cpAudio, TRUE);
    hr = cpRecoEngine->SetRecoState( SPRST_ACTIVE );
 
	bool bShouldContinue = true;

	if (SUCCEEDED(hr))
    {
        // Specifies that the grammar we want is a dictation grammar.
        // Initializes the grammar (m_cpDictationGrammar)
		// using ISpRecoContext
		if(m_cpRecoCtxt)
        	hr = m_cpRecoCtxt->CreateGrammar( GID_CC, &m_cpCCGrammar );
		else
			bShouldContinue = false;
		if  (SUCCEEDED(hr) && bShouldContinue)
			hr = m_cpRecoCtxt->CreateGrammar( GID_DICT, &m_cpDictGrammar );
		
    }
    
	if  (SUCCEEDED(hr) && bShouldContinue)
    {
        //Load the dictation tool for the grammar specified
		//using ISpRecoGrammar
		if(m_cpCCGrammar)
			hr = m_cpCCGrammar->LoadCmdFromResource(NULL, (const WCHAR*)MAKEINTRESOURCE( IDR_SRGRAMMAR1 ),
                                                    _T("SRGRAMMAR"), 0,//langid,
                                                    SPLO_STATIC);
		else
			bShouldContinue = false;
		if  (SUCCEEDED(hr) && bShouldContinue) {
			if(m_cpDictGrammar)
				hr = m_cpDictGrammar->LoadDictation(NULL, SPLO_STATIC);
			else 
				bShouldContinue = false;
		}
    }
    
	if (SUCCEEDED(hr) && bShouldContinue)
    {
        //After loading the Dictation set the dictation state to 
		//active using ISpRecoGrammar 
		hr = m_cpCCGrammar->SetRuleState(NULL, NULL, SPRS_ACTIVE);
		if  (SUCCEEDED(hr) && bShouldContinue)
			hr = m_cpDictGrammar->SetDictationState( SPRS_INACTIVE );
    }
 
	if (FAILED(hr) || !bShouldContinue)
    {
        //Release the grammar using ISpRecoGrammar
		m_cpCCGrammar.Release();
		m_cpDictGrammar.Release();
    }
#endif

	updateFromSettingsFile();

	m_camView.CreateCamWnd(this, a);
	m_pCurrentState = &m_stateReady;
	
	if(setWebcam())
		SetTimer(0, TIMER_FREQUENCY, NULL);
	else
		MessageBox(m_strCouldNotInitializeWebcam);

	SetWindowText(m_strMainDialogTitle);
	m_btnRecalibrate.SetWindowText(m_strRecalibrate);
	m_btnDisableEnable.SetWindowText(m_strDisable);
	m_btnPauseUnpause.SetWindowText(m_strPause);
	m_btnExit.SetWindowText(m_strExit);
	m_btnSettings.SetWindowText(m_strSettings);
	m_btnNouseboard.SetWindowText(m_strNouseboard);
/*
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CMenu* pSumMenu = menu.GetSubMenu(0);
	pSumMenu->ModifyMenu(ID_UP_DRAG, MF_POPUP, IDR_MENU1, _T("Hello"));
	*/
	ShowWindow(SW_MINIMIZE);
	return TRUE; // return TRUE  unless you set the focus to a control
}

bool CNouse5Dlg::setWebcam() {
	bool bWebcamOK = m_directShowSource.initializeCamCapture(m_iWebcamIndex);
	m_btnDisableEnable.EnableWindow(bWebcamOK);
	m_iCurrentWebcamIndex = m_iWebcamIndex;
	/*
	if(m_bNouseEnabled && !bWebcamOK)
		OnBnClickedButtonDisable();
	*/
	return bWebcamOK;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNouse5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNouse5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNouse5Dlg::OnTimer(UINT nIDEvent) {
	CFileStatus status;
	if(CFile::GetStatus(TEMP_MARKER_FILENAME, status)) {
		updateFromSettingsFile();
		CFile::Remove(TEMP_MARKER_FILENAME);
	}	

	/*
	if(m_iCurrentWebcamIndex != m_iWebcamIndex) 
		setWebcam();
	*/

	
	IplImage* img = m_directShowSource.captureImage();
	if(!img)
		return;
	preparePVS(img);
	
#if VOICE_RECOGNITION_ACTIVATED
	handleVoiceCommands();
#endif

	if(m_bNouseEnabled) {
		handleStates(m_pCurrentState->m_eWhoAmI, m_pCurrentState->processData(&m_pvs));
		if(m_stateCursor.m_bShouldShowContextMenu) {
			showContextMenu();
			m_stateCursor.m_bShouldShowContextMenu = false;
		}
		m_nouseCursor.redraw(m_pCurrentState, &m_pvs);
		m_btnPauseUnpause.SetWindowText((m_pCurrentState->m_eWhoAmI==STATE_CURSOR && m_stateCursor.m_bInPauseMode) ? m_strUnpause : m_strPause);
	}
	m_camView.SetImage(&m_pvs.m_imcOut.getCIplImage());
}

void CNouse5Dlg::exitNouse() {
	//exit(0);
	//KillTimer(0);
	m_stateCursor.m_discreteNavSystem.refreshDrawing();
}


void CNouse5Dlg::preparePVS(IplImage* img)
{
	m_pvs.capture(img, m_bMirrorCameraImage, false);
	m_pvs.initNextFrame(m_bUseLightNormalization);

	bool bRemoveNoiseIn_dI= m_nProcessLoad > 1; // false;
	bool bComputeBG=true; // if not used - change blobdetection 
	bool bRemoveNoiseIn_FG= m_nProcessLoad > 2; // false
	bool bComputeMHI=true;

	m_pvs.m_chanMotion.updateImages(m_pvs.m_imgBW.p, // cIn.p, 
		 bRemoveNoiseIn_dI,  bComputeBG,  bRemoveNoiseIn_FG,  bComputeMHI);
	m_pvs.m_chanColour.updateImages(m_pvs.m_imcIn.p, (m_nProcessLoad==1)?-1:0);

	int 
		nMinHeight=2,//+g.gui.slider[4], // 4+ // DO11
		nMinWidth=2, //+g.gui.slider[4], // 2+
		nMinConsistentVelocity=0,// + g.gui.slider[3], 
		nDilations = 0; // for faster work; //1; // 3;
	bool bMerge=true;

	m_pvs.m_chanMotion.detectBlobs(nMinWidth, nMinHeight, nMinConsistentVelocity, nDilations, bMerge);
}

CState* CNouse5Dlg::getStateFromName(EState eState) {
	switch(eState) {
		case STATE_READY:
			return &m_stateReady;
		case STATE_CALIBRATION:
			return &m_stateCalibration;
		case STATE_CURSOR:
			return &m_stateCursor;
		default:
			return m_pCurrentState;
	}
}


bool CNouse5Dlg::handleStates(EState eStartState, EState eNewState)
{
	if(eStartState != eNewState) {
		m_pCurrentState->onExit();
		m_pCurrentState = getStateFromName(eNewState);
		m_pCurrentState->onEntrance(&m_pvs);
		m_btnRecalibrate.EnableWindow(eNewState == STATE_CURSOR);
		m_btnPauseUnpause.EnableWindow(eNewState == STATE_CURSOR);
		m_btnNouseboard.EnableWindow(eNewState==STATE_CURSOR);
		m_nouseCursor.m_timeWhenArrivedAtPos = time(0);
		return true;
	}
	return false;
}

void CNouse5Dlg::OnCancel() {
	if(MessageBox(m_strExitWarning, m_strWarningCaption, MB_YESNO) == IDYES) 
		CDialog::OnCancel();
}

void CNouse5Dlg::OnBnClickedButtonDisable()
{
	if(m_bNouseEnabled) {
		if(MessageBox(m_strDisableWarning, m_strWarningCaption, MB_YESNO) == IDYES) {
			handleStates(m_pCurrentState->m_eWhoAmI, STATE_READY);
			m_nouseCursor.hide();
			m_btnDisableEnable.SetWindowTextW(m_strEnable);
			m_stateCursor.m_discreteNavSystem.refreshDrawing();
			m_bNouseEnabled = false;
		} 
	}
	else {
		m_btnDisableEnable.SetWindowTextW(m_strDisable);
		m_nouseCursor.show();
		m_bNouseEnabled = true;
	}
	
}


void CNouse5Dlg::OnBnClickedButtonSettings()
{
	::ShellExecute(NULL,_T("open"),_T("SettingsGUI.jar"),NULL,NULL,SW_HIDE);
}

void CNouse5Dlg::OnBnClickedButtonNouseboard()
{
	m_stateCursor.toggleInNouseBoard();
}


void CNouse5Dlg::OnBnClickedButtonPause()
{
	m_stateCursor.toggleInPauseMode();
}


void CNouse5Dlg::OnBnClickedButtonRecalibrate()
{
	handleStates(m_pCurrentState->m_eWhoAmI, STATE_READY);
}

void CNouse5Dlg::updateFromSettingsFile() {
	CString strCurrentSettingsFile; 
	CStdioFile fCurrentSettingsFileLocation(CURRENT_SETTINGS_LOCATION_FILENAME, CFile::modeRead); 
	fCurrentSettingsFileLocation.ReadString(strCurrentSettingsFile); 
	fCurrentSettingsFileLocation.Close();
	
	CFileStatus status;
	if(CFile::GetStatus(strCurrentSettingsFile, status)) {
		CStdioFile fileSettings(strCurrentSettingsFile, CFile::modeRead);
		loadSettings(&fileSettings);
		fileSettings.Close();
	}
}

CString getStrValueFromInputLine(CString strLine) {
	int iTok = 0;
	strLine.Tokenize(TOKEN_STRING, iTok);
	return strLine.Tokenize(TOKEN_STRING, iTok);
}

void CNouse5Dlg::loadConstants(CStdioFile* pSettingsFile) {
	CString strLine, strVal, strConstant;
	while(pSettingsFile->ReadString(strLine)) {
		strConstant = "MAIN_DIALOG_TITLE ";
		if(strLine.Find(strConstant) == 0) {
			m_strMainDialogTitle = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "RECALIBRATE ";
		if(strLine.Find(strConstant) == 0) {
			m_strRecalibrate = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "ENABLE ";
		if(strLine.Find(strConstant) == 0) {
			m_strEnable = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DISABLE ";
		if(strLine.Find(strConstant) == 0) {
			m_strDisable = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "EXIT ";
		if(strLine.Find(strConstant) == 0) {
			m_strExit = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "SETTINGS ";
		if(strLine.Find(strConstant) == 0) {
			m_strSettings = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "PAUSE ";
		if(strLine.Find(strConstant) == 0) {
			m_strPause = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "UNPAUSE ";
		if(strLine.Find(strConstant) == 0) {
			m_strUnpause = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "NOUSEBOARD ";
		if(strLine.Find(strConstant) == 0) {
			m_strNouseboard = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "COULD_NOT_INITIALIZE_WEBCAM ";
		if(strLine.Find(strConstant) == 0) {
			m_strCouldNotInitializeWebcam = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DWELL_DIALOG_TITLE ";
		if(strLine.Find(strConstant) == 0) {
			m_stateCursor.m_dDwell.m_strDwellDialogTitle = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "LEFT_CLICK ";
		if(strLine.Find(strConstant) == 0) {
			m_stateCursor.m_dDwell.m_strLeftClick = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "RIGHT_CLICK ";
		if(strLine.Find(strConstant) == 0) {
			m_stateCursor.m_dDwell.m_strRightClick = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DOUBLE_CLICK_BUTTON ";
		if(strLine.Find(strConstant) == 0) {
			m_stateCursor.m_dDwell.m_strDoubleClick = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DRAG ";
		if(strLine.Find(strConstant) == 0) {
			m_strDrag = m_stateCursor.m_dDwell.m_strDrag = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "NOUSEPAD_DIALOG_TITLE ";
		if(strLine.Find(strConstant) == 0) {
			m_stateCursor.m_nousePad.m_strNousepadDialogTitle = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "NOUSE_TRIAL_INFO ";
		if(strLine.Find(strConstant) == 0) {
			m_strNouseTrialInfo = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "NOUSE_TRADEMARK ";
		if(strLine.Find(strConstant) == 0) {
			m_strNouseTrademark = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DAYS_LEFT_IN_TRIAL ";
		if(strLine.Find(strConstant) == 0) {
			m_strDaysLeftInTrial = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "TRIAL_EXPIRED ";
		if(strLine.Find(strConstant) == 0) {
			m_strTrialExpired = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "NOUSEBOARD_DIALOG_TITLE ";
		if(strLine.Find(strConstant) == 0) {
			CString strNouseboardDialogTitle = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strNouseboardDialogTitle.GetLength();++i) {
				m_stateCursor.m_nouseBoard.m_strNouseboardDialogTitle[i] = strNouseboardDialogTitle.GetAt(i);
			}
			m_stateCursor.m_nouseBoard.m_strNouseboardDialogTitle[strNouseboardDialogTitle.GetLength()] = '\0';
		}

		strConstant = "CREATION_FAILED ";
		if(strLine.Find(strConstant) == 0) {
			m_nouseCursor.m_strCreationFailed = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "LEAVE ";
		if(strLine.Find(strConstant) == 0) {
			CString strLeave = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strLeave.GetLength();++i) {
				m_nouseCursor.m_strLeave[i] = strLeave.GetAt(i);
			}
			m_nouseCursor.m_strLeave[strLeave.GetLength()] = '\0';
		}

		strConstant = "STILL ";
		if(strLine.Find(strConstant) == 0) {
			CString strStill = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strStill.GetLength();++i) {
				m_nouseCursor.m_strStill[i] = strStill.GetAt(i);
			}
			m_nouseCursor.m_strStill[strStill.GetLength()] = '\0';
		}

		strConstant = "RESET ";
		if(strLine.Find(strConstant) == 0) {
			CString strReset = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strReset.GetLength();++i) {
				m_nouseCursor.m_strReset[i] = strReset.GetAt(i);
			}
			m_nouseCursor.m_strReset[strReset.GetLength()] = '\0';
		}

		strConstant = "CENTER ";
		if(strLine.Find(strConstant) == 0) {
			CString strCenter = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strCenter.GetLength();++i) {
				m_nouseCursor.m_strCenter[i] = strCenter.GetAt(i);
			}
			m_nouseCursor.m_strCenter[strCenter.GetLength()] = '\0';
		}

		strConstant = "PAUSED ";
		if(strLine.Find(strConstant) == 0) {
			CString strPaused = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strPaused.GetLength();++i) {
				m_nouseCursor.m_strPaused[i] = strPaused.GetAt(i);
			}
			m_nouseCursor.m_strPaused[strPaused.GetLength()] = '\0';
		}

		strConstant = "BOARD ";
		if(strLine.Find(strConstant) == 0) {
			CString strBoard = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strBoard.GetLength();++i) {
				m_nouseCursor.m_strBoard[i] = strBoard.GetAt(i);
			}
			m_nouseCursor.m_strBoard[strBoard.GetLength()] = '\0';
		}

		strConstant = "DIRECT ";
		if(strLine.Find(strConstant) == 0) {
			CString strDirect = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strDirect.GetLength();++i) {
				m_nouseCursor.m_strDirect[i] = strDirect.GetAt(i);
			}
			m_nouseCursor.m_strDirect[strDirect.GetLength()] = '\0';
		}

		strConstant = "JOYSTICK ";
		if(strLine.Find(strConstant) == 0) {
			CString strJoystick = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strJoystick.GetLength();++i) {
				m_nouseCursor.m_strJoystick[i] = strJoystick.GetAt(i);
			}
			m_nouseCursor.m_strJoystick[strJoystick.GetLength()] = '\0';
		}

		strConstant = "MOUSE ";
		if(strLine.Find(strConstant) == 0) {
			CString strMouse = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strMouse.GetLength();++i) {
				m_nouseCursor.m_strMouse[i] = strMouse.GetAt(i);
			}
			m_nouseCursor.m_strMouse[strMouse.GetLength()] = '\0';
		}

		strConstant = "DISCRETE ";
		if(strLine.Find(strConstant) == 0) {
			CString strDiscrete = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strDiscrete.GetLength();++i) {
				m_nouseCursor.m_strDiscrete[i] = strDiscrete.GetAt(i);
			}
			m_nouseCursor.m_strDiscrete[strDiscrete.GetLength()] = '\0';
		}

		strConstant = "TYPE ";
		if(strLine.Find(strConstant) == 0) {
			CString strType = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strType.GetLength();++i) {
				m_nouseCursor.m_strType[i] = strType.GetAt(i);
			}
			m_nouseCursor.m_strType[strType.GetLength()] = '\0';
		}

		strConstant = "CLICK ";
		if(strLine.Find(strConstant) == 0) {
			CString strClick = strLine.Mid(strConstant.GetLength());
			for(int i=0; i<strClick.GetLength();++i) {
				m_nouseCursor.m_strClick[i] = strClick.GetAt(i);
			}
			m_nouseCursor.m_strClick[strClick.GetLength()] = '\0';
		}

		strConstant = "WARNING_CAPTION ";
		if(strLine.Find(strConstant) == 0) {
			m_strWarningCaption = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "DISABLE_WARNING ";
		if(strLine.Find(strConstant) == 0) {
			m_strDisableWarning = strLine.Mid(strConstant.GetLength());
			continue;
		}

		strConstant = "EXIT_WARNING ";
		if(strLine.Find(strConstant) == 0) {
			m_strExitWarning = strLine.Mid(strConstant.GetLength());
			continue;
		}
	}
}

void CNouse5Dlg::loadSettings(CStdioFile* pSettingsFile) {
	CString strLine, strVal;
	int index = 0;
	while(pSettingsFile->ReadString(strLine)) {
		if(strLine.Find(_T("BIG_MOTION_DISABLED_IN_CURSOR_STATE")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bBigMotionDisabled = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("MOTION_SIZE")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nBigMotionPercentage = _ttoi(strVal);
		} else if(strLine.Find(_T("ACTIVATE_ASSUMES_HEADWIDTH")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateReady.m_dHeadWidth = _ttof(strVal);
		} else if(strLine.Find(_T("ACTIVATE_USES_FACEDETECTION")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateReady.m_bActWithFaceDetection = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("CONTROL_POINTERCORNER_MOVES")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseControl.m_ePointerLocation = (EPointerLocation)_ttoi(strVal);
		} else if(strLine.Find(_T("CALIBRATE_AUTOMATIC")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCalibration.m_bQuickCalibrate = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("CONTROL_NOCHANGE_BACK_TO_RESET")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nTimeNochangeBackReset = _ttoi(strVal);
		} else if(strLine.Find(_T("CONTROL_NOMOTION_BACK_TO_RESET")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nTimeMotionBackReset = _ttoi(strVal);
		} else if(strLine.Find(_T("CLOSE_CLICK_FOR_BOARD")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nCloseClickAmount = _ttoi(strVal);
		} else if(strLine.Find(_T("PCT_STOP_JOYSTICK")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseControl.m_nPctStopJoystick = _ttoi(strVal);
		} else if(strLine.Find(_T("USE_MOUTH_DETECTION")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bUseMouthDetection = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("MinimumMouthClickHeight")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nMinimumMouthClickHeight = _ttoi(strVal);
		} else if(strLine.Find(_T("USE_VOICE_COMMANDS")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bUseVoiceCommands = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("CLICK_ON_COMMAND")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bClickOnCommand = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("LOCK_ON")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nLockOn = _ttoi(strVal);
		} else if(strLine.Find(_T("MOUSELESS_NAV_COMPARISON_TYPE")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			index = _ttoi(strVal);
			m_stateCursor.m_discreteNavSystem.m_eComparisonType = index == 0 ? FOUR_DIRECTIONS_CROSS : index == 1 ? FOUR_DIRECTIONS_X : EIGHT_DIRECTIONS;
		} else if(strLine.Find(_T("CountdownConfirmClick")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nCountConfirm = _ttoi(strVal);
		} else if(strLine.Find(_T("CountdownTime")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCalibration.m_nCountConfirm = _ttoi(strVal);
		} else if(strLine.Find(_T("ClickBoxSize")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nClickBoxSize = m_stateCalibration.m_nClickBoxSize = _ttoi(strVal);
		} else if(strLine.Find(_T("CursorShowsFace")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_nouseCursor.m_bCursorShowsFace = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("MirrorCameraImage")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bMirrorCameraImage = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("DiscreteDirection")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			index = _ttoi(strVal);
			m_stateCursor.m_nouseControl.m_eDiscreteDirection = (index == 0) ? ALL_DIRECTIONS : (index == 1) ? 
				EIGHT_DIRECTIONS : FOUR_DIRECTIONS_CROSS;
		} else if(strLine.Find(_T("EnableDwellClicking")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bEnableDwellClicking = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("Lag")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bLag = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("AlwaysLeftClick")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bAlwaysLeftClick = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("ProcessLoad")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_nProcessLoad = _ttoi(strVal);
		} else if(strLine.Find(_T("CursorSize")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_nouseCursor.m_nCursorSize = _ttoi(strVal);
		} else if(strLine.Find(_T("CursorSpeed")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseControl.m_nCursorSpeed = _ttoi(strVal);
		} else if(strLine.Find(_T("CountdownCalibration")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCalibration.m_nCountCalibrateSelect = _ttoi(strVal);
		} else if(strLine.Find(_T("CountdownDwell")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nCountDwell = _ttoi(strVal);
		} else if(strLine.Find(_T("EnableYellowState")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bEnableYellowState = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("EnableSounds")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bEnableSounds = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("NavigationType")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			switch(_ttoi(strVal)) {
				case 1:
					m_stateCursor.m_nouseControl.m_eGeneralControlMode = CONTROL_MODE_JOYSTICK;
					break;
				case 2:
					m_stateCursor.m_nouseControl.m_eGeneralControlMode = CONTROL_MODE_DIRECT;
					break;
				default:
					m_stateCursor.m_nouseControl.m_eGeneralControlMode = CONTROL_MODE_DISCRETE;
			}
		} else if(strLine.Find(_T("MotionRangeHorizontal")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseControl.m_nMotionRangeHorizontal = _ttoi(strVal);
		} else if(strLine.Find(_T("MotionRangeVertical")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseControl.m_nMotionRangeVertical = _ttoi(strVal);
		} else if(strLine.Find(_T("ResolutionPixels")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nResolutionInPixels = _ttoi(strVal);
		} else if(strLine.Find(_T("ResolutionSeconds")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nResolutionInSeconds = _ttoi(strVal);
		} else if(strLine.Find(_T("LightNormalization")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_bUseLightNormalization = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("TranslucentCursor")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_nouseCursor.m_bUseTranslucentCursor = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("TranslucenceSolidness")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_nouseCursor.m_nTranslucentSolidness = _ttoi(strVal);
		} else if(strLine.Find(_T("JitterThreshold")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseBoard.m_nJitterThreshold = _ttoi(strVal);
		} else if(strLine.Find(_T("NouseCursorInBoard")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bNouseCursorInBoard = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("TextSizeScale")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nousePad.m_dTextSizeScale = _ttof(strVal);
		} else if(strLine.Find(_T("BoardTextScale")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_nouseBoard.m_dTextSizeScale = _ttof(strVal);
		} else if(strLine.Find(_T("WebcamIndex")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_iWebcamIndex = _ttoi(strVal);
		} else if(strLine.Find(_T("EnableAutoRecalibration")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bUseAutoRecalibration = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("EnableSpecialClicks")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_bSpecialClicksEnabled = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("FaceDetectionType")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateReady.m_nFaceDetectionType = m_stateCursor.m_nFaceDetectionType = _ttoi(strVal);
		} else if(strLine.Find(_T("CursorShowsCountdown")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_nouseCursor.m_bCursorShowsCountdown = _ttoi(strVal) != 0;
		} else if(strLine.Find(_T("DiscreteNavType")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_discreteNavSystem.m_eDiscreteNavType = (_ttoi(strVal)==0) ? DECREASING_JUMPS : MAPPING_TO_QUADRANTS;
		} else if(strLine.Find(_T("DirectMappingRows")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_discreteNavSystem.m_nDirectMappingRows = _ttoi(strVal);
		} else if(strLine.Find(_T("DirectMappingCols")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_discreteNavSystem.m_nDirectMappingCols = _ttoi(strVal);
		} else if(strLine.Find(_T("ShowDiscreteNavRects")) >= 0) {
			strVal = getStrValueFromInputLine(strLine);
			m_stateCursor.m_discreteNavSystem.m_bShowRects = _ttoi(strVal) != 0;
		} else { //NouseBoard
			CString strSearch;
			CString strLevel;
			CStringA strLineA(strLine);
			for(int level = 0; level < 3; ++level) {
				strLevel = (level==0)?"Group":(level==1)?"ShiftGroup":"AdvGroup";
				for(int row = 0; row < 3; ++row) {
					for(int col = 0; col < 5; ++col) {
						strSearch.Format(_T("%s(%d,%d)"), strLevel, row+1, col+1);
						if(strLine.Find(strSearch) ==0)
						{
							// Elan09: Put in functionality for reading colour
							int b = -1, g = -1,r=-1;
							if(level==0)
								sscanf(strLineA, "%*s %*s %s %s %s %s %d %d %d", m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT-1].szNormalText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT-1].szNormalText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT-1].szNormalText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT-1].szNormalText, &b, &g, &r);
							else if(level==1)
								sscanf(strLineA, "%*s %*s %s %s %s %s %d %d %d", m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT-1].szShiftText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT-1].szShiftText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT-1].szShiftText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT-1].szShiftText, &b, &g , &r);
							else
								sscanf(strLineA, "%*s %*s %s %s %s %s %d %d %d", m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[ABOVE_RECT-1].szAdvText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[LEFT_OF_RECT-1].szAdvText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[BELOW_RECT-1].szAdvText, m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].box[RIGHT_OF_RECT-1].szAdvText, &b ,&g, &r);
							if(b>=0 && g>=0 && r>=0)
								m_stateCursor.m_nouseBoard.m_Kbd.group[row][col].normalColor[level] = cvScalar(b,g,r);
						}
					}
				}
			}
		}
	}
}
#if IS_TRIAL_VERSION

//Elan10 ->Dmitry2014, instead  of Elan's pvu:: -> CNouse5Dlg::
int CNouse5Dlg::registryTransaction(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, bool bTrueGetFalseSet, char* strVal)
{
	HKEY programKey;
	unsigned long nDisposition;
	
	// Create the registry key (or open it if it doesn't already exist)
	int nRetVal = RegCreateKeyEx(
		hKey,							// handle to an open key
		lpSubKey,
		0,											// reserved
		NULL,										// address of class string
		REG_OPTION_NON_VOLATILE,					// special options flag
		KEY_ALL_ACCESS,								// desired security access
		NULL,										// address of key security structure
		&programKey,								// address of buffer for opened handle
		&nDisposition								// address of disposition value buffer
	);
	
	if(nRetVal != 0)
		return nRetVal;

	DWORD dwSize = 256;
	DWORD dwType = REG_SZ;
	if(bTrueGetFalseSet) 
		nRetVal = RegQueryValueEx(programKey, lpValueName, 0, &dwType, (LPBYTE)strVal, &dwSize);
	else
		nRetVal = RegSetValueEx(programKey, lpValueName, 0, dwType, (PBYTE)strVal, dwSize);

	RegCloseKey(programKey);

	return nRetVal;
	
}



void CNouse5Dlg::handleTrialBusiness()
{
	char strDateVal[256];
	time_t timeNow = time(0);
	int nRetVal = registryTransaction(HKEY_LOCAL_MACHINE,SECRET_REGISTRY_LOCATION, REGISTRY_TIME_VARIABLE_NAME, true, strDateVal); 
	if(nRetVal != 0) {
		sprintf(strDateVal, "%d", timeNow);
		nRetVal = registryTransaction(HKEY_LOCAL_MACHINE,SECRET_REGISTRY_LOCATION, REGISTRY_TIME_VARIABLE_NAME, false, strDateVal); 
	}
	char* p;
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
	
	CString strMessageBoxHeading = m_strNouseTrialInfo;
	CString strMessageBoxEnd = m_strNouseTrademark;
	CString strMessageBoxText;
	if(lDaysLeftInTrial > 0 && lDaysLeftInTrial <= DAYS_IN_TRIAL) {
		strMessageBoxText.Format(_T("%s%d\n%s"),m_strDaysLeftInTrial, lDaysLeftInTrial, strMessageBoxEnd);
		MessageBox(strMessageBoxText, strMessageBoxHeading);
		m_bTrialExpired=false;
		m_stateCursor.m_bTrialExpired = m_bTrialExpired;
	} else {
		strMessageBoxText.Format(_T("%s%s"),m_strTrialExpired, strMessageBoxEnd);
		MessageBox(strMessageBoxText, strMessageBoxHeading);
//		exit(0);
		m_bTrialExpired=true;
		m_stateCursor.m_bTrialExpired = m_bTrialExpired;
	}

#if USE_ACTIVATION_KEY	
	if (1) //m_bTrialExpired)
		if(!handleActivationKey()) {
//			MessageBox(m_strActivationErrorMsg, m_strActivationErrorCaption);
			CString strMessageBoxText;
			strMessageBoxText.Format(_T("Wrong or absent License Key"));
			MessageBox(strMessageBoxText, m_strNouseTrialInfo); // m_strNouseTrialInfo
			m_bTrialExpired=m_bTrialExpired;
//			m_bTrialExpired=false;
	//		m_bLicenseKeyEntered1=true;
		}

#endif


	
}
#endif


#if USE_ACTIVATION_KEY

CString convertEmail2Id(CString strEmail)
{
        // g.str[i]=33+ X % 94;
	int n=strEmail.GetLength();
	char str[256];
    for (int i=0;i<12;i++)
		str[i]=33+ (int)strEmail[ ((int)strEmail[i%n])*13 % n ]*
    (int)strEmail[ (((int)strEmail[(i*7)%n])*31+1) %n ] * (i*i+n*n+111111)
    % 94;

    str[12] = '\0';
	return CString(str);
}

bool CNouse5Dlg::handleActivationKey() {
	CFileStatus status;
	if(!CFile::GetStatus(ACTIVATION_KEY_FILENAME, status))
		return false;
	CStdioFile fileActivation(ACTIVATION_KEY_FILENAME, CFile::modeRead);
	CString strLineEmail, strLineKey, strLineName;

	fileActivation.ReadString(strLineEmail);
	fileActivation.ReadString(strLineKey);
	fileActivation.ReadString(strLineName);
	CString emailStringPrefix = _T("Email: ");
	CString activationKeyStringPrefix = _T("Activation: ");
	CString nameStringPrefix = _T("Name: ");

	if(strLineEmail.Find(emailStringPrefix) != 0)
		return false;
	if(strLineKey.Find(activationKeyStringPrefix) != 0)
		return false;
	if(strLineName.Find(nameStringPrefix) != 0)
		return false;

	CString strEmail = strLineEmail.Mid(emailStringPrefix.GetLength());
	CString strKey = strLineKey.Mid(activationKeyStringPrefix.GetLength());
	CString strName = strLineName.Mid(nameStringPrefix.GetLength()),
		strNameHelp = _T("dm7");

	CString encodedEmail = convertEmail2Id(strEmail);

		/*
    if (!strcmp(strName, "dm7")) {
            FILE *f; f = fopen("dm7.txt", "a"); Beep(1000,100);
            fprintf(f, "%s \t \t %s\n", strEmail, g.str);
            fclose(f);
    }
    return g.str;
	*/
	
	if (strName == strNameHelp)
	{
            FILE *f; f = fopen("_activation.txt", "a"); Beep(1000,100);
            fprintf(f, "%S \t \t %S\n", (LPCTSTR)strEmail, (LPCTSTR)encodedEmail);
            fprintf(f, "%s \t \t %s\n", (LPCTSTR)strEmail, CT2A(encodedEmail));
            fprintf(f, "%S \t \t %S\n", CT2A(strEmail), CT2A(encodedEmail));
			// encodedEmail.GetString();
             fclose(f);
		return true;
	}

	if(encodedEmail == strKey)
		return true;
	return false;

	/*
		if(strLine.Find(strConstant) == 0) {
			m_strMainDialogTitle = strLine.Mid(strConstant.GetLength());
			continue;
		}
	*/
}
#endif

#if VOICE_RECOGNITION_ACTIVATED
//void CNouse5Dlg::OnRecoEvent()
LRESULT CNouse5Dlg::OnRecoEvent(WPARAM wp, LPARAM lp)
{
	USES_CONVERSION;
    CSpEvent event;

    // Process all of the recognition events
    while (event.GetFrom(m_cpRecoCtxt) == S_OK)
    {
        switch (event.eEventId)
        {
            case SPEI_SOUND_START:
                m_bSound = TRUE;
                break;

            case SPEI_SOUND_END:
                if (m_bSound)
                {
                    m_bSound = FALSE;
                    
                    m_bReco = FALSE;
                }
                break;

            case SPEI_RECOGNITION:
                // There may be multiple recognition results, so get all of them
                {
                    m_bReco = TRUE;
                    static const WCHAR wszUnrecognized[] = L"<Unrecognized>";

                    CSpDynamicString dstrText;
                    if (FAILED(event.RecoResult()->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, 
                                                            &dstrText, NULL)))
                    {
                        dstrText = wszUnrecognized;
                    }

					/*
					((CPVSContainerApp*)AfxGetApp())->m_eCurrentEvent = NOUSE_EVENT_VOICE;
					strcpy(m_strCurrentVoiceCommand, W2T(dstrText));
					//Convert to lowercase
					for(int i=0; i<strlen(m_strCurrentVoiceCommand); ++i)
						m_strCurrentVoiceCommand[i] = tolower(m_strCurrentVoiceCommand[i]);
					*/
					m_strCurrentVoiceCommand = dstrText;
					m_strCurrentVoiceCommand.MakeLower();
                }
                break;

        }
    }
	return 0;
	
}

void CNouse5Dlg::handleVoiceCommands() {
	if(m_strCurrentVoiceCommand.GetLength() == 0) return;
	
	if(m_bUseVoiceCommands) {
		if((m_bNouseEnabled && m_strCurrentVoiceCommand == "disable") || (!m_bNouseEnabled && m_strCurrentVoiceCommand == "enable"))
			OnBnClickedButtonDisable();
		else if(m_strCurrentVoiceCommand == "settings")
			OnBnClickedButtonSettings();
		else if(m_bNouseEnabled && m_pCurrentState->m_eWhoAmI == STATE_CURSOR)
			m_stateCursor.handleVoiceCommand(m_strCurrentVoiceCommand);
	}

	m_strCurrentVoiceCommand = "";
}

#endif

void CNouse5Dlg::showContextMenu() {
	SetForegroundWindow();
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CMenu* pSumMenu = menu.GetSubMenu(0);
	m_pPopupMenu = new CMFCPopupMenu();
	POINT ptCursor;
	GetCursorPos(&ptCursor);
	m_pPopupMenu->Create(this, ptCursor.x, ptCursor.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE);
}

void CNouse5Dlg::OnUpExit()
{
	OnCancel();
}


void CNouse5Dlg::OnUpDisable()
{
	OnBnClickedButtonDisable();
}


void CNouse5Dlg::OnUpSettings()
{
	OnBnClickedButtonSettings();
}


void CNouse5Dlg::OnUpRecalibrate()
{
	OnBnClickedButtonRecalibrate();
}


void CNouse5Dlg::OnUpNouseboard()
{
	OnBnClickedButtonNouseboard();
}


void CNouse5Dlg::OnUpDrag()
{
	m_stateCursor.m_bDragging = true;
	
	//Move actual and Nouse cursor to correct locations
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, (int)m_stateCursor.m_ptDragLocationCursor.x, (int)m_stateCursor.m_ptDragLocationCursor.y, 0, 0);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, (int)m_stateCursor.m_ptDragLocationCursor.x, (int)m_stateCursor.m_ptDragLocationCursor.y, 0, 0);
	m_stateCursor.m_nouseControl.setPointWinAbs(m_stateCursor.m_ptDragLocationNouseCursor);

	//Make it so cursor will still glue to NouseCursor even though it moved
	m_stateCursor.m_timeCursorStoppedMoving = 0;
}


void CNouse5Dlg::OnUpPause()
{
	OnBnClickedButtonPause();
}


void CNouse5Dlg::OnUpPaste()
{
	keybd_event(VK_CONTROL,0,0 , 0);
	keybd_event(VkKeyScan('v'),0,0 , 0);
	keybd_event(VkKeyScan('v'),0, KEYEVENTF_KEYUP,0);
	keybd_event(VK_CONTROL,0, KEYEVENTF_KEYUP,0);
}


void CNouse5Dlg::OnUpEnter()
{
	keybd_event(VK_RETURN,0,0 , 0);
	keybd_event(VK_RETURN,0, KEYEVENTF_KEYUP,0);
}


void CNouse5Dlg::OnUpdateUpDrag(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(m_strDrag);
}


void CNouse5Dlg::OnUpdateUpPause(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(m_strPause);
}


void CNouse5Dlg::OnUpdateUpNouseboard(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(m_strNouseboard);
}


void CNouse5Dlg::OnUpdateUpRecalibrate(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(m_strRecalibrate);
}


void CNouse5Dlg::OnUpdateUpSettings(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(m_strSettings);
}


void CNouse5Dlg::OnUpdateUpDisable(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(m_strDisable);
}


void CNouse5Dlg::OnUpdateUpExit(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(m_strExit);
}
