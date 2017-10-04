#pragma once
#include "DataHandler.h"



#define NUMBER_OF_COLS 5
#define NUMBER_OF_ROWS 3
#define NUMBER_OF_BOXES_PER_GROUP 4

// Elan10: Percentages are based on having a board at (100,0) -> (1100,300) on a screen with resolution of 1280x800
#define BOARD_WIDTH_PCT_OF_SCREEN 0.8//0.78125
#define BOARD_HEIGHT_PCT_OF_SCREEN 0.4//0.375

//Elan09
#define DICTIONARY_FILENAME "wordlist.txt"

#define MAX_LABEL_LENGTH 256

enum EPointRectComparison {
	INSIDE_RECT,
	LEFT_OF_RECT,
	ABOVE_RECT,
	BELOW_RECT,
	RIGHT_OF_RECT,
	TOP_RIGHT_OF_RECT,
	BOTTOM_RIGHT_OF_RECT,
	TOP_LEFT_OF_RECT,
	BOTTOM_LEFT_OF_RECT
};
enum EControlMode
{
	CONTROL_MODE_DIRECT,
	CONTROL_MODE_JOYSTICK,
	CONTROL_MODE_MOUSE,
	CONTROL_MODE_DISCRETE
};
enum EJumpDirection {
	WEST = 0,
	NORTH_WEST,
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	NUM_JUMP_DIRECTIONS,
	DO_MAPPING_JUMP
};

enum EDiscreteNavType {
	DECREASING_JUMPS = 0,
	MAPPING_TO_QUADRANTS,
	CHILD_WINDOWS
};

enum EPointerLocation {
	ALWAYS_TOPLEFT = 0,
	MOVES,
	ALWAYS_CENTER
};

enum EComparisonType {
	FOUR_DIRECTIONS_CROSS,
	FOUR_DIRECTIONS_X,
	EIGHT_DIRECTIONS,
	ALL_DIRECTIONS
};

typedef struct CvScalar
{
	double val[4];
}CvScalar;

class CSettingsHandler :
	public CDataHandler
{
public:
	CSettingsHandler();
	virtual ~CSettingsHandler();
	///////////
	struct sStateReadyData
	{
		bool m_bActWithFaceDetection;
		double m_dHeadWidth;
		int m_nFaceDetectionType;
		/*CNouseControl* m_pNouseControl;
		int m_nFacesInARow;
		PVI_RECT m_rectLastFaceDetected;*/
	} m_stateReady;
	struct sStateCalibrationData
	{
		int m_nCountConfirm;
		int m_nCountdown;
		bool m_bQuickCalibrate;
		int m_nClickBoxSize;
		int m_nCountCalibrateSelect;
	/*	bool* m_pbEnableSounds;
		PVI_RECT m_rectConfirm;
	
		CNouseTracker* m_pNouseTracker;
		CNouseControl* m_pNouseControl;
		bool m_bInConfirmingStage;*/
		
	} m_stateCalibration;

	enum EBoardLayout {
		EBOARDLAYOUT_MODE_NORMAL = 0,
		EBOARDLAYOUT_MODE_SHIFT,
		EBOARDLAYOUT_MODE_ADV
	};
	
	struct sStateCursorData
	{
		bool m_bBigMotionDisabled;
		int m_nBigMotionPercentage;
		int m_nTimeNochangeBackReset;
		int m_nTimeMotionBackReset;
		int m_nCloseClickAmount;
		bool m_bUseMouthDetection;
		bool m_bUseVoiceCommands;
		bool m_bClickOnCommand;
		int m_nLockOn;
		int m_nCountConfirm;
		int m_nMinimumMouthClickHeight;
		int m_nClickBoxSize;
		bool m_bEnableDwellClicking;
		bool m_bLag;
		bool m_bAlwaysLeftClick;
		int m_nCountDwell;
		bool m_bEnableYellowState;
		int m_nResolutionInPixels;
		int m_nResolutionInSeconds;
		bool m_bInPauseMode;
		bool m_bSpecialClicksEnabled;
		int m_nFaceDetectionType;
		struct strol;
		/////////////
		
		struct sNouseBoard {
			struct sKbd
			{
				struct sGroup
				{
					struct sBoxElement
					{
						char szNormalText[MAX_LABEL_LENGTH];
						char szAdvText[MAX_LABEL_LENGTH];
						char szShiftText[MAX_LABEL_LENGTH];
					} box[NUMBER_OF_BOXES_PER_GROUP];
					//Elan09
					CvScalar normalColor[3]; // One color for each level (normal, shift, adv)
				} group[NUMBER_OF_ROWS][NUMBER_OF_COLS];
			} m_Kbd;

		//	CRefImageNouseData m_refImageData;
			EPointerLocation m_ePointerLocation;
			int m_nPctStopJoystick;
			EComparisonType m_eDiscreteDirection;
			int m_nCursorSpeed;
			EControlMode m_eGeneralControlMode;
			EControlMode m_eControlMode;
			int m_nMotionRangeHorizontal;
			int m_nMotionRangeVertical;
			double m_dTextSizeScale;
			int m_nJitterThreshold;

		}m_nouseBoard;
		//////////////////
		struct sNouseControl {
			
			EControlMode m_eGeneralControlMode;
			EControlMode m_eControlMode;
			int m_nMotionRangeHorizontal;
			int m_nMotionRangeVertical;
			EPointerLocation m_ePointerLocation;
			int m_nPctStopJoystick;
			EComparisonType m_eDiscreteDirection;
			int m_nCursorSpeed;

		}m_nouseControl;
		struct sNousePad {
			double m_dTextSizeScale;
		}m_nousePad;

		struct sDiscreteNavSystem{

			EDiscreteNavType m_eDiscreteNavType;
			int m_nDirectMappingRows;
			int m_nDirectMappingCols;
			bool m_bShowRects;
			EComparisonType m_eComparisonType;
		
		}m_discreteNavSystem;
		///////////////
		EBoardLayout m_layoutMode;
		double m_dTextSizeScale;
		int m_nSelectedRow, m_nSelectedCol;
	//	PVI_RECT m_rectBoard;
		//CWordCompletionSystem* m_pWordCompletionSystem;
		char m_strCurrentTypedWord[MAX_LABEL_LENGTH];
		HWND m_wndNouseBoard;
		bool m_bWaitingToType;
	
		char m_strToType[256];
		bool m_bCursorMoved;
		bool m_bUseAutoRecalibration;
		bool m_bNouseCursorInBoard;


	}m_stateCursor;

	void updateFromFile();

	void loadBoardFile(CString strFileName);
	void saveBoardFile(CString strFileName);
	void formatBoardFile(CStdioFile* pFile = NULL);
	void parseFile(CStdioFile* pFile = NULL);
	void parseBoardFile(CStdioFile* pFile = NULL);
	
	void formatFile(CStdioFile* pFile = NULL);
	void setBoardText(CString strText, int nLevel, int nRow, int nCol, int nIndex);

	
	int m_nCursorSize;
	bool m_bCursorShowsFace, m_bCursorShowsCountdown;
	bool m_bUseLightNormalization;
	bool m_bMirrorCameraImage;
	int m_nProcessLoad;
	bool m_bUseTranslucentCursor;
	int m_nTranslucentSolidness;
	int m_iWebcamIndex;
	bool m_bEnableSounds;
	/////
	bool m_bUseVoiceCommands;
	private:
	void SetDataDefaults();
	void parseBoardLine(CString strLine);
};

