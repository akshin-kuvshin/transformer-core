//
// Копирайт (С) 2019, ООО «Нанософт разработка». Все права защищены.
// 
// Данное программное обеспечение, все исключительные права на него, его
// документация и сопроводительные материалы принадлежат ООО «Нанософт разработка».
// Данное программное обеспечение может использоваться при разработке и входить
// в состав разработанных программных продуктов при соблюдении условий
// использования, оговоренных в «Лицензионном договоре присоединения
// на использование программы для ЭВМ «Платформа nanoCAD»».
// 
// Данное программное обеспечение защищено в соответствии с законодательством
// Российской Федерации об интеллектуальной собственности и международными
// правовыми актами.
// 
// Используя данное программное обеспечение,  его документацию и
// сопроводительные материалы вы соглашаетесь с условиями использования,
// указанными выше. 
//

#ifndef _OPENDWG_INTERACTIONHOST_H__
#define _OPENDWG_INTERACTIONHOST_H__
#include "nrxhostgate_impexp.h"

class NcEdSubSelectFilter;
class HostEdInputPointManager;
class HostEdInputContextReactor;
class HostEdInputPointFilter;
class HostEdInputPointMonitor;
class HostEdJig;
class HostEdSSGetFilter;
class NcApDocument;
class NcDbCustomOsnapMode;
class NcEdInputContextReactor;
class NcEdInputPoint;
class NcEdInputPointFilter;
class NcEdInputPointFilterResult;
class NcEdInputPointMonitor;
class NcEdInputPointMonitorResult;

class NcEdSelectedTransientImp;
class NcEdSteeringWheelReactor;
class NcEdViewCubeReactor;
class NdApplicationFrame;
class NcPane;

typedef NcArray<NcDbIntArray, NcArrayObjectCopyReallocator<NcDbIntArray> >
	NcDbArrayIntArray;

typedef void (WINAPI* NcEdColorDialogCallbackFunction)(void *pCallbackData, const NcCmColor& newColor);

namespace NcEdSSGet {

	enum NcEdSSGetFlags {
		kNormal         =   0,
		kPickPoints     =   1,
		kDuplicates     =   2,
		kNestedEntities =   4,
		kSubEntities    =   8,
		kSinglePick     =  16,
		kPickfirstSet   =  32,
		kPreviousSet    =  64,
		kSubSelection   = 128,
		kUndo           = 256,
		kFailedPickAuto = 512
	};

	enum NcEdSSGetModes {
		kWin = 1,   //  (Window spec)
		kCross,     //  (Crossing spec)
		kBox,       //  (Box spec)
		kLast,      //  (Last)
		kEntity,    //  (Explicit entity name)
		kAll,       //  (Select all)
		kFence,     //  (Fence Selection)
		kCPoly,     //  (Crossing Poly)
		kWPoly,     //  (Window Poly)
		kPick,      //  (Single pick)
		kEvery,     //  (every entity on single pick)
		kXten,      //  (ssget "X")
		kGroup,     //  (selection set from "group" specification)
		kPrevious,  //  (previous selectionset)
		kMultiple,  //  (Multiple keyword)
	};
};

#define NCEDSYMUTIL_SERVICES_CURRENT_VERSION 100

namespace NcEdSymbolUtilities
{
	enum CrSpMode {
		kCrEndsInput = true,
		kCrSpEndsInput = false
	};

	enum NameCaseMode {
		kPreserveCase = true,
		kForceToUpper = false
	};

//////////////////////////////////////////////////////////////////////////
// NcEdSymbolUtilities:Services
class Services {
public:
	enum { kCurrentVersion = NCEDSYMUTIL_SERVICES_CURRENT_VERSION };
	virtual unsigned version() const = 0;
	virtual Nano::PromptStatus getCompatibleSymbolString(
	                                  NCHAR*&        pResponse,
	                                  const NCHAR*   prompt,
	                                  NcDbDatabase* pDb) const = 0;
	virtual Nano::PromptStatus getSymbolString(
	                                  NCHAR*&      pResponse,
	                                  const NCHAR* prompt,
	                                  bool         onlyCrEndsInput,
	                                  bool         preserveCase) const = 0;
};
}; // namespace NcEdSymbolUtilities

enum DimstyleTabSuppressed {
	kSymbolsArrowsTabSuppressed   = 0x01,
	kTextTabSuppressed            = 0x02,
	kFitTabSuppressed             = 0x04,
	kPrimaryTabSuppressed         = 0x08,
	kAlternateTabSuppressed       = 0x10,
	kToleranceTabSuppressed       = 0x20
};
enum BlockEditModeFlags {
	kBlkEditModeNone   = 0x0,
	kBlkEditModeActive = 0x01,
	kBlkEditModeOpen   = 0x02,
	kBlkEditModeDirty  = 0x04
};

enum NcEdViewCubePart
{
	FACE_FRONT = 0,
	FACE_BACK,
	FACE_BOTTOM,
	FACE_TOP,
	FACE_LEFT,
	FACE_RIGHT,

	EDGE_FRONT_BOTTOM,
	EDGE_FRONT_TOP,
	EDGE_BACK_BOTTOM,
	EDGE_BACK_TOP,
	EDGE_LEFT_BOTTOM,
	EDGE_RIGHT_BOTTOM,
	EDGE_LEFT_TOP,
	EDGE_RIGHT_TOP,
	EDGE_FRONT_LEFT,
	EDGE_BACK_LEFT,
	EDGE_FRONT_RIGHT,
	EDGE_BACK_RIGHT,

	CORNER_FRONT_LEFT_BOTTOM,
	CORNER_FRONT_RIGHT_BOTTOM,
	CORNER_FRONT_LEFT_TOP,
	CORNER_FRONT_RIGHT_TOP,
	CORNER_BACK_LEFT_BOTTOM,
	CORNER_BACK_RIGHT_BOTTOM,
	CORNER_BACK_LEFT_TOP,
	CORNER_BACK_RIGHT_TOP,

	ARROW_FRONT,
	ARROW_BACK,
	ARROW_BOTTOM,
	ARROW_TOP,
	ARROW_LEFT,
	ARROW_RIGHT,

	BUTTON_ROTATE_CCW,
	BUTTON_ROTATE_CW,
	BUTTON_HOME,
	BUTTON_LOCK,
	BUTTON_MENU,

	COMPASS_EAST,
	COMPASS_WEST,
	COMPASS_SOUTH,
	COMPASS_NORTH,
	COMPASS_RING
};

enum NcHatchNotifier {
	kNobody           = 0x00,
	kImpHatch         = 0x01,
	kBoundary         = 0x02,
	kHatchAndBoundary = (kImpHatch | kBoundary),
	kAddScale         = 0x04
};

enum NcHatchEdReact
{
	kStartHatchWatcher = 1,
	kSwapHatchId,
	kUpRootHatchWatcher,
	kDestroyHatchWatcher,
	kDisableNextStart,
	kRecomputeBoundary
};

enum NcEdCommandStatusFlags
{
	kCmdStatusNone   = 0x00000,
	kCmdStatusCancel = 0x00001,
	kCmdStatusFailed = 0x00002,
};

struct PROMPT_MAP_ENTRY {
	LPCWSTR m_szDesc ;
	DISPID m_dispId ;
	int m_promptType ;
	int m_cronly ;
	int m_nInitget ;
	UINT m_nKeywords ;
	UINT m_nDefaultValue ;
	UINT m_nPrompt ;
	bool m_bJigThisProperty ;
	bool m_bGotThisProperty ;
	VARTYPE m_paramType ;
	VARIANT m_vValue ;
};
struct NcColorSettings {
	DWORD dwGfxModelBkColor;    
	DWORD dwGfxLayoutBkColor;
	DWORD dwParallelBkColor;
	DWORD dwBEditBkColor;
	DWORD dwCmdLineBkColor;
	DWORD dwPlotPrevBkColor;

	DWORD dwSkyGradientZenithColor;
	DWORD dwSkyGradientHorizonColor;
	DWORD dwGroundGradientOriginColor;
	DWORD dwGroundGradientHorizonColor;
	DWORD dwEarthGradientAzimuthColor; 
	DWORD dwEarthGradientHorizonColor;

	DWORD dwModelCrossHairColor;
	DWORD dwLayoutCrossHairColor;
	DWORD dwParallelCrossHairColor;
	DWORD dwPerspectiveCrossHairColor;
	DWORD dwBEditCrossHairColor;

	DWORD dwParallelGridMajorLines;
	DWORD dwPerspectiveGridMajorLines;

	DWORD dwParallelGridMinorLines;
	DWORD dwPerspectiveGridMinorLines;

	DWORD dwParallelGridAxisLines;
	DWORD dwPerspectiveGridAxisLines;

	DWORD dwTextForeColor, dwTextBkColor;

	DWORD dwCmdLineForeColor;

	DWORD dwAutoTrackingVecColor;
	DWORD dwLayoutATrackVecColor;
	DWORD dwParallelATrackVecColor;
	DWORD dwPerspectiveATrackVecColor;
	DWORD dwBEditATrackVecColor;

	DWORD dwModelASnapMarkerColor;
	DWORD dwLayoutASnapMarkerColor;
	DWORD dwParallelASnapMarkerColor;
	DWORD dwPerspectiveASnapMarkerColor;
	DWORD dwBEditASnapMarkerColor;

	DWORD dwModelDftingTooltipColor;
	DWORD dwLayoutDftingTooltipColor;
	DWORD dwParallelDftingTooltipColor;
	DWORD dwPerspectiveDftingTooltipColor;
	DWORD dwBEditDftingTooltipColor;

	DWORD dwModelDftingTooltipBkColor;
	DWORD dwLayoutDftingTooltipBkColor;
	DWORD dwParallelDftingTooltipBkColor;
	DWORD dwPerspectiveDftingTooltipBkColor;
	DWORD dwBEditDftingTooltipBkColor;

	DWORD dwModelLightGlyphs;
	DWORD dwLayoutLightGlyphs;
	DWORD dwParallelLightGlyphs;
	DWORD dwPerspectiveLightGlyphs;
	DWORD dwBEditLightGlyphs;

	DWORD dwModelLightHotspot;
	DWORD dwLayoutLightHotspot;
	DWORD dwParallelLightHotspot;
	DWORD dwPerspectiveLightHotspot;
	DWORD dwBEditLightHotspot;

	DWORD dwModelLightFalloff;
	DWORD dwLayoutLightFalloff;
	DWORD dwParallelLightFalloff;
	DWORD dwPerspectiveLightFalloff;
	DWORD dwBEditLightFalloff;

	DWORD dwModelLightStartLimit;
	DWORD dwLayoutLightStartLimit;
	DWORD dwParallelLightStartLimit;
	DWORD dwPerspectiveLightStartLimit;
	DWORD dwBEditLightStartLimit;

	DWORD dwModelLightEndLimit;
	DWORD dwLayoutLightEndLimit;
	DWORD dwParallelLightEndLimit;
	DWORD dwPerspectiveLightEndLimit;
	DWORD dwBEditLightEndLimit;

	DWORD dwModelCameraGlyphs;
	DWORD dwLayoutCameraGlyphs;
	DWORD dwParallelCameraGlyphs;
	DWORD dwPerspectiveCameraGlyphs;

	DWORD dwModelCameraFrustrum;
	DWORD dwLayoutCameraFrustrum;
	DWORD dwParallelCameraFrustrum;
	DWORD dwPerspectiveCameraFrustrum;

	DWORD dwModelCameraClipping;
	DWORD dwLayoutCameraClipping;
	DWORD dwParallelCameraClipping;
	DWORD dwPerspectiveCameraClipping;

	int nModelCrosshairUseTintXYZ;
	int nLayoutCrosshairUseTintXYZ;
	int nParallelCrosshairUseTintXYZ;
	int nPerspectiveCrosshairUseTintXYZ;
	int nBEditCrossHairUseTintXYZ;

	int nModelATrackVecUseTintXYZ;
	int nLayoutATrackVecUseTintXYZ;
	int nParallelATrackVecUseTintXYZ;
	int nPerspectiveATrackVecUseTintXYZ;
	int nBEditATrackVecUseTintXYZ;

	int nModelDftingTooltipBkUseTintXYZ;
	int nLayoutDftingTooltipBkUseTintXYZ;
	int nParallelDftingTooltipBkUseTintXYZ;
	int nPerspectiveDftingTooltipBkUseTintXYZ;
	int nBEditDftingTooltipBkUseTintXYZ;

	int nParallelGridMajorLineTintXYZ;
	int nPerspectiveGridMajorLineTintXYZ;

	int nParallelGridMinorLineTintXYZ;
	int nPerspectiveGridMinorLineTintXYZ;

	int nParallelGridAxisLineTintXYZ;
	int nPerspectiveGridAxisLineTintXYZ;
};

struct NcColorSettingsEx
{
	DWORD dwModelLightWeb;
	DWORD dwLayoutLightWeb;
	DWORD dwParallelLightWeb;
	DWORD dwPerspectiveLightWeb;
	DWORD dwBEditLightWeb;

	DWORD dwModelLightWebMissingFile;
	DWORD dwLayoutLightWebMissingFile;
	DWORD dwParallelLightWebMissingFile;
	DWORD dwPerspectiveLightWebMissingFile;
	DWORD dwBEditLightWebMissingFile;

	DWORD dwModelLightWebShape;
	DWORD dwLayoutLightWebShape;
	DWORD dwParallelLightWebShape;
	DWORD dwPerspectiveLightWebShape;
	DWORD dwBEditLightWebShape;

	DWORD dwModelLightWebLuxAtDist;
	DWORD dwLayoutLightWebLuxAtDist;
	DWORD dwParallelLightWebLuxAtDist;
	DWORD dwPerspectiveLightWebLuxAtDist;
	DWORD dwBEditLightWebLuxAtDist;

	DWORD dwBEditUnconstrainedColor;
	DWORD dwBEditPartiallyConstrainedColor;
	DWORD dwBEditFullyConstrainedColor;
	DWORD dwBEditOverConstrainedColor;
};

struct NcColorSettingsEx2
{
	DWORD dw2DModelGridMajorLines;
	DWORD dwLayoutGridMajorLines;
	DWORD dwBEditGridMajorLines;

	DWORD dw2DModelGridMinorLines;
	DWORD dwLayoutGridMinorLines;
	DWORD dwBEditGridMinorLines;

	DWORD dw2DModelGridAxisLines;
	DWORD dwLayoutGridAxisLines;
	DWORD dwBEditGridAxisLines;

	DWORD dwModelDynamicDimensionLineColor;
	DWORD dwLayoutDynamicDimensionLineColor;
	DWORD dwParallelDynamicDimensionLineColor;
	DWORD dwPerspectiveDynamicDimensionLineColor;
	DWORD dwBEditDynamicDimensionLineColor;

	DWORD dwModelDftingTooltipContourColor;
	DWORD dwLayoutDftingTooltipContourColor;
	DWORD dwParallelDftingTooltipContourColor;
	DWORD dwPerspectiveDftingTooltipContourColor;
	DWORD dwBEditDftingTooltipContourColor;

	int n2DModelGridMajorLineTintXYZ;
	int nLayoutGridMajorLineTintXYZ;
	int nBEditGridMajorLineTintXYZ;

	int n2DModelGridMinorLineTintXYZ;
	int nLayoutGridMinorLineTintXYZ;
	int nBEditGridMinorLineTintXYZ;

	int n2DModelGridAxisLineTintXYZ;
	int nLayoutGridAxisLineTintXYZ;
	int nBEditGridAxisLineTintXYZ;

	DWORD dwControlVerticesHullColor;
};

typedef BOOL (* NcedPreTranslateMsgFn)(MSG*);
typedef void (* NcedWatchWinMsgFn)(const MSG*);
typedef BOOL (* NcedFilterWinMsgFn)(MSG*);
typedef void (* NcedOnIdleMsgFn) ();
typedef void (* NcedOnModalFn) (bool bModal);

#ifndef NCAD_PORT
#ifdef NCAD_API
	#define NCAD_PORT _declspec(dllexport)
#else
	#define NCAD_PORT
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdJig
class NRXHOSTGATE_EXPORT NcEdJig : public NcRxObject
{
	NCRX_DECLARE_MEMBERS(NcEdJig);

	enum  UserInputControls
	{
		kGovernedByOrthoMode         = 0x0001,
		kNullResponseAccepted        = 0x0002,
		kDontEchoCancelForCtrlC      = 0x0004,
		kDontUpdateLastPoint         = 0x0008,
		kNoDwgLimitsChecking         = 0x0010,
		kNoZeroResponseAccepted      = 0x0020,
		kNoNegativeResponseAccepted  = 0x0040,
		kAccept3dCoordinates         = 0x0080,
		kAcceptMouseUpAsPoint        = 0x0100,
		kAnyBlankTerminatesInput     = 0x0200,
		kInitialBlankTerminatesInput = 0x0400,
		kAcceptOtherInputString      = 0x0800,
		kGovernedByUCSDetect         = 0x1000,
		kNoZDirectionOrtho           = 0x2000
	};

	enum  DragStatus
	{
		kModeless = -17,
		kNoChange = -6,
		kCancel   = -4,
		kOther    = -3,
		kNull     = -1,
		kNormal   = 0,
		kKW1,
		kKW2,
		kKW3,
		kKW4,
		kKW5,
		kKW6,
		kKW7,
		kKW8,
		kKW9
	};

	enum  CursorType
	{
		kNoSpecialCursor = -1,
		kCrosshair       = 0,
		kRectCursor,
		kRubberBand,
		kNotRotated,
		kTargetBox,
		kRotatedCrosshair,
		kCrosshairNoRotate,
		kInvisible,
		kEntitySelect,
		kParallelogram,
		kEntitySelectNoPersp,
		kPkfirstOrGrips,
		kCrosshairDashed
	};

public:
	NcEdJig();
	virtual ~NcEdJig();

public:
	DragStatus drag();
	virtual DragStatus sampler();
	virtual NRX::Boolean update();
	NcDbObjectId append();

	const NCHAR* keywordList();
	void setKeywordList(const NCHAR*);

	const NCHAR* dispPrompt();
	void setDispPrompt(const NCHAR*, ...);

	DragStatus acquireString(NCHAR* string);
	DragStatus acquireAngle(double& angle);
	DragStatus acquireAngle(double& angle, const NcGePoint3d& base);
	DragStatus acquireDist(double& distance);
	DragStatus acquireDist(double& distance, const NcGePoint3d& base);
	DragStatus acquirePoint(NcGePoint3d& point);
	DragStatus acquirePoint(NcGePoint3d& point, const NcGePoint3d& base);

	NcEdJig::CursorType specialCursorType();
	void setSpecialCursorType(CursorType);

	NcEdJig::UserInputControls userInputControls();
	void setUserInputControls(NcEdJig::UserInputControls);

	virtual NcDbEntity* entity() const;
	virtual NcDbDimDataPtrArray *dimData(const double dimScale);
	virtual Nano::ErrorStatus setDimValue(const NcDbDimData *dimData, const double dimValue);

public:
	HostEdJig* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPointManager moved to interactionDb.h in NrxDBGate

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPointFilter moved to interactionDb.h in NrxDBGate

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPointMonitor moved to interactionDb.h in NrxDBGate

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputContextReactor moved to interactionDb.h in NrxDBGate

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPoint moved to interactionDb.h in NrxDBGate

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPointMonitorResult moved to interactionDb.h in NrxDBGate

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPointFilterResult moved to interactionDb.h in NrxDBGate

// AutoGen:

//////////////////////////////////////////////////////////////////////////
// NcEdCommandEventArgs
class NcEdCommandEventArgs {
public:
	const NCHAR* groupName() const;
	NcEdCommandStatusFlags status() const;
	void setStatus(NcEdCommandStatusFlags flags);
protected:
	NcEdCommandEventArgs(const NcEdCommandEventArgs& other);
	NcEdCommandEventArgs& operator=(const NcEdCommandEventArgs& other);
};

//////////////////////////////////////////////////////////////////////////
// NcEdCommandReactor
class NcEdCommandReactor : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcEdCommandReactor);
	virtual void commandWillStart(NcEdCommand* pCmd, NcEdCommandEventArgs* data);
	virtual void     commandEnded(NcEdCommand* pCmd, NcEdCommandEventArgs* data);
	virtual void          goodbye(NcEdCommand* pCmd, NcEdCommandEventArgs* data);
};

//////////////////////////////////////////////////////////////////////////
// NcEdCommandStackReactor
class NcEdCommandStackReactor: public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcEdCommandStackReactor);
	virtual void commandAdded(    NcEdCommand* pCmd, NcEdCommandEventArgs* data);
	virtual void commandRemoved(  NcEdCommand* pCmd, NcEdCommandEventArgs* data);
	virtual void commandWillStart(NcEdCommand* pCmd, NcEdCommandEventArgs* data);
	virtual void commandEnded(    NcEdCommand* pCmd, NcEdCommandEventArgs* data);
};

//////////////////////////////////////////////////////////////////////////
// NcEdServices
class NRXHOSTGATE_EXPORT NcEdServices: public NcRxService {
public:
	NCRX_DECLARE_MEMBERS(NcEdServices);
	virtual NcEdCommand* newAcEdCommand(NcRxFunctionPtr cmdFcnAddr,
	                                    NRX::Int32 cmdFlags) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcEdSolidSubentitySelector
class NRXHOSTGATE_EXPORT NcEdSolidSubentitySelector {
public:
	NcEdSolidSubentitySelector();
	~NcEdSolidSubentitySelector();
	Nano::ErrorStatus selectFaces(NcDbObjectId& selectedSolidId,
	                              NcArray<NcDbSubentId *>& faceSet);
};

//////////////////////////////////////////////////////////////////////////
// NcEdSelectedTransient
class NRXHOSTGATE_EXPORT NcEdSelectedTransient {
public:
	NcEdSelectedTransient();
	NcEdSelectedTransient(const NcEdSelectedTransient& source);
	NcEdSelectedTransient& operator=(const NcEdSelectedTransient& source);
	~NcEdSelectedTransient();
	NcGiDrawable* parent();
	NcGiDrawable* drawable();
	NRX::GsMarker marker();
	NcGiTransientDrawingMode mode();
	int subDrawingMode();
protected:
	NcEdSelectedTransientImp* mImp;
	friend class NcEdTransientSelectionInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcEdSteeringWheel
class NcEdSteeringWheel {
public:
	enum WheelType
	{
		kExterior = 0,
		kInterior,
		kFull,
		k2D,
		kMini,
		kMiniOther,
		kMiniEight,
		kTotalCount,
		kWheelNone
	};
	enum MenuType
	{
		kMenuNone = 0,
		kMenuInterior,
		kMenuExterior,
		kMenuFull,
		kMenu2D
	};
	virtual void    onKeyDown     (UINT nChar, UINT nRepCount, UINT nFlags) = 0;
	virtual void    onKeyUp       (UINT nChar, UINT nRepCount, UINT nFlags) = 0;
	virtual bool    onMouseWheel  (UINT nFlags, short zDelta, POINT pt) = 0;
	virtual void    onMouseMove   (UINT nFlags, POINT pt) = 0;
	virtual void    onLButtonUp   (UINT nFlags, POINT pt) = 0;
	virtual void    onLButtonDown (UINT nFlags, POINT pt) = 0;
	virtual void    onRButtonUp   (UINT nFlags, POINT pt) = 0;
	virtual void    onRButtonDown (UINT nFlags, POINT pt) = 0;
	virtual void    onMButtonDown (UINT nFlags, POINT pt) = 0;
	virtual void    onMButtonUp (UINT nFlags, POINT pt) = 0;
	virtual void    setHomeCamera (const NcDbHomeView& home) = 0;
	virtual bool    setLargeWheelOpacity  (int nOpacity) = 0;
	virtual int     getLargeWheelOpacity  () = 0;
	virtual bool    setMiniWheelOpacity  (int nOpacity) = 0;
	virtual int     getMiniWheelOpacity  () = 0;
	virtual bool    setWalkSpeed(double speed) = 0;
	virtual double  getWalkSpeed() = 0;
	virtual bool    setActiveWheel(WheelType type) = 0;
	virtual WheelType   getActiveWheel() = 0;
	virtual void    enableWheel (bool enable) = 0;
	virtual bool    isWheelEnabled() = 0;
	virtual NcGsModel * getModel() = 0;
	virtual NcGsView *  getView()  = 0;
	virtual HWND        getDeviceHandle() = 0;
	virtual bool    attachView      (HWND hDevice, NcGsView* pGsView) = 0;
	virtual void    detachView      () = 0;
	virtual void    addReactor  (NcEdSteeringWheelReactor* pReactor) = 0;
	virtual void    removeReactor(NcEdSteeringWheelReactor* pReactor) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcEdSteeringWheelReactor
class NcEdSteeringWheelReactor {
public:
	virtual void    modifyContextMenu(HMENU hMenu) = 0;
	virtual void    onSetCursor(HCURSOR hCursor) = 0;
	virtual void    onBeginOperation() = 0;
	virtual void    onEndOperation() = 0;
	virtual void    onBeginShot() = 0;
	virtual void    onEndShot() = 0;
	virtual void    onClose() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcEdViewCube
class NcEdViewCube {
public:
	virtual NcGiDrawable*       getDrawable             () const                        = 0;
	virtual NcGsView*           getView                 () const                        = 0;
	virtual NcGsModel*          getModel                () const                        = 0;
	virtual void                redraw                  () const                        = 0;
	virtual bool                isMouseInRegion         () const                        = 0;
	virtual HWND                getDeviceHandle         () const                        = 0;
	virtual bool                isVisible               () const                        = 0;
	virtual bool                isEnable                () const                        = 0;
	virtual bool                isOverride              () const                        = 0;
	virtual int                 getLocation             () const                        = 0;
	virtual int                 getSize                 () const                        = 0;
	virtual int                 getMinOpacity           () const                        = 0;
	virtual int                 getTransitionDuration   () const                        = 0;
	virtual bool                getOrientToUCS          () const                        = 0;
	virtual bool                getDragSnap             () const                        = 0;
	virtual bool                getZoomToFitScene       () const                        = 0;
	virtual bool                getPreserveSceneUp      () const                        = 0;
	virtual bool                getDrawCompass          () const                        = 0;
	virtual bool                getDrawUCSMenu          () const                        = 0;
	virtual bool                getPerspWithOrtho       () const                        = 0;
	virtual const NcDbHomeView& getHomeCamera           () const                        = 0;
	virtual const NcGeVector3d& getSceneUpDirection     () const                        = 0;
	virtual const NcGeVector3d& getSceneFrontDirection  () const                        = 0;
	virtual const NcDbUcsPlane& getUCSPlane             () const                        = 0;
	virtual void                setDeviceHandle         (HWND hDevice)                  = 0;
	virtual void                setVisible              (bool bVisible)                 = 0;
	virtual void                setEnable               (bool bEnable)                  = 0;
	virtual void                setOverride             (bool bOverride)                = 0;
	virtual void                setLocation             (int nLocation)                 = 0;
	virtual void                setSize                 (int nSize)                     = 0;
	virtual void                setMinOpacity           (int nMinOpacity)               = 0;
	virtual void                setTransitionDuration   (int nTransitionDuration)       = 0;
	virtual void                setOrientToUCS          (bool bOrientToUCS)             = 0;
	virtual void                setDragSnap             (bool bDragSnap)                = 0;
	virtual void                setZoomToFitScene       (bool bZoomToFitScene)          = 0;
	virtual void                setPreserveSceneUp      (bool bPreserveSceneUp)         = 0;
	virtual void                setDrawCompass          (bool bDrawCompass)             = 0;
	virtual void                setDrawUCSMenu          (bool bDrawUCSMenu)             = 0;
	virtual void                setPerspWithOrtho       (bool bPerspWithOrtho)          = 0;
	virtual void                setHomeCamera           (const NcDbHomeView& home)      = 0;
	virtual void                setSceneUpDirection     (const NcGeVector3d& up)        = 0;
	virtual void                setSceneFrontDirection  (const NcGeVector3d& front)     = 0;
	virtual void                setUCSPlane             (const NcDbUcsPlane& ucs)       = 0;
	virtual void                onLButtonDown           (UINT nFlags, POINT pt)         = 0;
	virtual void                onLButtonUp             (UINT nFlags, POINT pt)         = 0;
	virtual void                onMouseMove             (UINT nFlags, POINT pt)         = 0;
	virtual bool                attachView              (NcGsView* pGsView)             = 0;
	virtual NcGsView*           detachView              ()                              = 0;
	virtual void                addReactor              (NcEdViewCubeReactor* pReactor) = 0;
	virtual void                removeReactor           (NcEdViewCubeReactor* pReactor) = 0;
	virtual void                goToHomeView            ()                              = 0;
	virtual NcEdViewCubePart    getActivePart           () const                        = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcEdViewCubeReactor
class NcEdViewCubeReactor {
public:
	virtual void                onClicked               (NcEdViewCube* pCube, NcEdViewCubePart part) = 0;
	virtual void                onDragBegin             (NcEdViewCube* pCube, NcEdViewCubePart part) = 0;
	virtual void                onDragEnd               (NcEdViewCube* pCube)           = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcLyRelExpr moved to interactionDb.h in NrxDBGate

//////////////////////////////////////////////////////////////////////////
// NcLyAndExpr moved to interactionDb.h in NrxDBGate

//////////////////////////////////////////////////////////////////////////
// NcLyBoolExpr moved to interactionDb.h in NrxDBGate

//////////////////////////////////////////////////////////////////////////
// NcEdSelectionSetService
class NcEdSelectionSetService {
public:
	virtual Nano::ErrorStatus ssNameX(
	    bool bIsSubSelectionIndex,
	    int index,
	    resbuf*& result) = 0;
	virtual Nano::ErrorStatus ssNameSubentityX(
	    bool bIsSubSelectionIndex,
	    int index,
	    int subentityIndex,
	    resbuf*& result) = 0;
	virtual Nano::ErrorStatus ssNameSubentities(
	    bool bIsSubSelectionIndex,
	    int index,
	    NcDbFullSubentPathArray& subEntities) = 0;
	virtual Nano::ErrorStatus add(
	    resbuf *ssnameXList,
	    const NcDbFullSubentPath *pPath = NULL,
	    const NcDbObjectId* pEntselSubent = NULL) = 0;
	virtual Nano::ErrorStatus addSubentity(
	    resbuf *ssnameXList,
	    const NcDbFullSubentPath& subEntity) = 0;
	virtual Nano::ErrorStatus remove(
	    int index) = 0;
	virtual Nano::ErrorStatus removeSubentity(
	    int entityIndex,
	    int subEntityIndex) = 0;
	virtual Nano::ErrorStatus highlight(
	    int subSelectionIndex,
	    const NcDbFullSubentPath& path) = 0;
	virtual int subSelectionMode() = 0;
	virtual Nano::ErrorStatus getSubSelectionPoints(
	    NcGePoint3dArray& points) = 0;
	virtual Nano::ErrorStatus add(
	    const NcArray<resbuf *>& ssnameXList,
	    const NcArray<NcDbFullSubentPath *> *pPath,
	    bool bAddsAreUnique) = 0;
	virtual Nano::ErrorStatus addSubentities(
	    resbuf * ssnameXList,
	    const NcArray<NcDbFullSubentPath>& subEntities,
	    bool bAddsAreUnique) = 0;
	virtual Nano::ErrorStatus remove(
	    const NcArray<int>& indices) = 0;
	virtual Nano::ErrorStatus removeSubentities(
	    int entityIndex,
	    const NcArray<int>& subEntityIndices) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcEdSSGetFilter
class NRXHOSTGATE_EXPORT NcEdSSGetFilter: public NcEdInputContextReactor {
public:
	NcEdSSGetFilter();
	~NcEdSSGetFilter();

	virtual void
	ssgetAddFilter(
	    int ssgetFlags,
	    NcEdSelectionSetService &service,
	    const NcDbObjectIdArray& selectionSet,
	    const NcDbObjectIdArray& subSelectionSet)
	{  }
	virtual void
	ssgetRemoveFilter(
	    int ssgetFlags,
	    NcEdSelectionSetService &service,
	    const NcDbObjectIdArray& selectionSet,
	    const NcDbObjectIdArray& subSelectionSet,
	    NcDbIntArray& removeIndexes,
	    NcDbArrayIntArray& removeSubentIndexes)
	{  }
	virtual void
	ssgetAddFailed(
	    int ssgetFlags,
	    int ssgetMode,
	    NcEdSelectionSetService &service,
	    const NcDbObjectIdArray& selectionSet,
	    resbuf *rbPoints)
	{  }
	virtual void
	ssgetRemoveFailed(
	    int ssgetFlags,
	    int ssgetMode,
	    NcEdSelectionSetService &service,
	    const NcDbObjectIdArray& selectionSet,
	    resbuf *rbPoints,
	    NcDbIntArray& removeIndexes,
	    NcDbArrayIntArray& removeSubentIndexes)
	{  }
	virtual void
	endSSGet(
	    Nano::PromptStatus returnStatus,
	    int ssgetFlags,
	    NcEdSelectionSetService &service,
	    const NcDbObjectIdArray& selectionSet)
	{  }
	virtual void
	endEntsel(
	    Nano::PromptStatus       returnStatus,
	    const NcDbObjectId&      pickedEntity,
	    const NcGePoint3d&       pickedPoint,
	    NcEdSelectionSetService& service)
	{ }

	inline HostEdSSGetFilter* native() const
	{
		return (HostEdSSGetFilter*)m_pNative;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcEdSSGetFilter2
class NRXHOSTGATE_EXPORT NcEdSSGetFilter2 : public NcEdSSGetFilter {
public:
	virtual void
	ssgetRolloverFilter(
	    const NcDbFullSubentPath &subEntityPath,
	    NcDbFullSubentPath &highlightPath)
	{  }
};

//////////////////////////////////////////////////////////////////////////
// NcEdSSGetFilter3
class NRXHOSTGATE_EXPORT NcEdSSGetFilter3 : public NcEdSSGetFilter {
public:
	virtual void
	ssgetRolloverFilter(
	    const NcDbFullSubentPath &subEntityPath,
	    NcDbFullSubentPathArray &highlightPaths)
	{  }
};

//////////////////////////////////////////////////////////////////////////
// NcEdSSGetFilter4
class NRXHOSTGATE_EXPORT NcEdSSGetFilter4 : public NcEdSSGetFilter {
public:
	virtual void
	endNEntsel(
	    Nano::PromptStatus       returnStatus,
	    const NcDbObjectId&      pickedEntity,
	    const NcGePoint3d&       pickedPoint,
	    nds_point                xformres[4],
	    struct resbuf **         refstkres,
	    NcEdSelectionSetService& service)
	{ }
	virtual void beginSSGetCustomKeywordCallback(const NCHAR* pKeyword) {};
	virtual void endSSGetCustomKeywordCallback(const NCHAR* pKeyword) {};
};

//////////////////////////////////////////////////////////////////////////
// NcEdSubSelectFilterService
class NRXHOSTGATE_EXPORT NcEdSubSelectFilterService {
public:
	virtual Nano::ErrorStatus ssNameX(
	    bool bIsSubSelectionIndex,
	    int index,
	    resbuf*& result) = 0;
	virtual Nano::ErrorStatus add(
	    resbuf *ssnameXList,
	    const NcDbFullSubentPath& path) = 0;
	virtual Nano::ErrorStatus remove(
	    bool bIsSubSelectionIndex,
	    int index) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcEdSSGetSubSelectFilter
class NRXHOSTGATE_EXPORT NcEdSSGetSubSelectFilter : public NcEdInputContextReactor {
public:
	virtual Nano::ErrorStatus
		getSubentPathsAtGsMarker(
			NcDbEntity*                    pEnt,
			bool                           bAdding,
			const NcDbFullSubentPathArray& selectedPaths,
			NcDb::SubentType               type,
			NRX::GsMarker                  gsMark,
			const NcGePoint3d&             pickPoint,
			const NcGeMatrix3d&            viewXForm,
			int&                           numPaths,
			NcDbFullSubentPath*&           subentPaths,
			int                            numInserts,
			NcDbObjectId*                  entAndInsertStack) = 0;
	virtual Nano::ErrorStatus
		subSelectClassList(NcArray<NcRxClass*>& classes) = 0;
	virtual void
		ssgetAddFilter(
			int                            ssgetFlags,
			NcEdSubSelectFilterService&    service,
			const NcDbObjectId&            object,
			const NcDbFullSubentPathArray& selectedPaths,
			const NcDbFullSubentPathArray& addedPaths) = 0;
	virtual void
		ssgetRemoveFilter(
			int                            ssgetFlags,
			NcEdSubSelectFilterService&    service,
			const NcDbObjectId&            object,
			const NcDbFullSubentPathArray& selectedPaths,
			const NcDbFullSubentPathArray& removedPaths) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcEdSubSelectFilter moved to interactionDb.h in NrxDBGate

//////////////////////////////////////////////////////////////////////////
// NcEdXrefFileLock

class NRXHOSTGATE_EXPORT NcEdXrefFileLock {
public:
	NcEdXrefFileLock();
	~NcEdXrefFileLock();
	Nano::ErrorStatus lockFile(
		int& retstatus,
		const NcDbObjectId& selectedBTRid);
	Nano::ErrorStatus releaseFile(
		int& retstatus,
		bool bSkipSaveback = false,
		bool bReload = true);
	Nano::ErrorStatus consistencyCheck(
		int& retstatus,
		const NcDbObjectId& selectedBTRid,
		NcDbObjectIdArray& outofSyncBTRids);
	Nano::ErrorStatus consistencyCheck(
		int& retstatus,
		const NcDbObjectId& selectedBTRid);
	Nano::ErrorStatus consistencyChecklocal(
		int& retstatus,
		const NcDbObjectId& selectedBTRid);
	Nano::ErrorStatus xloadctlType(
		int& retstatus,
		const NcDbObjectId& selectedBTRid);
	int               getlockxloadctlType() const { return mXldctltype; }
	const NcDbObjectIdArray& getoutofSyncIdArray() const { return mXBTRidArray; }
	Nano::ErrorStatus reloadFile(
		int& retstatus,
		const NcDbObjectIdArray& BTRids,
		const int xldctltype = -1);
	Nano::ErrorStatus reloadFile(
		int& retstatus,
		const int xldctltype = -1);
	void              setInternalTNmgmt(bool bTNmgmt);
	NcDbObjectId      getLockBtrId() { return mXBTRid; }
private:
	NcDwgFileHandle* mdwgfile;
	NcDbDatabase* mpXDB;
	NcDbDatabase* mpXDBlockFile;
	int                 mXldctltype;
	NcDbObjectId        mXBTRid;
	NcDbObjectIdArray   mXBTRidArray;
	bool                mbIntTNmgmt;
};

// AutoGen.

NRXHOSTGATE_EXPORT bool ncedCompareToCurrentViewport(const NcDbViewTableRecord *pVwRec);
//extern NRX::Boolean
//ncedCreateInternetShortcut(const NCHAR* szURL, const NCHAR* szShortcutPath);

NRXHOSTGATE_EXPORT NcEdSteeringWheel* ncedCreateSteeringWheel ();

NRXHOSTGATE_EXPORT NcEdViewCube* ncedCreateViewCube(NcGsView* pGsView);
NRXHOSTGATE_EXPORT void ncedDestroySteeringWheel(NcEdSteeringWheel* pWheel);
NRXHOSTGATE_EXPORT void ncedDestroyViewCube(NcEdViewCube* pCube);
NRXHOSTGATE_EXPORT void ncedDisableDefaultARXExceptionHandler(NRX::Boolean disable = NRX::kTrue);
NRXHOSTGATE_EXPORT void ncedDisableUsrbrk();
NRXHOSTGATE_EXPORT int ncedEditDimstyleInteractiveEx(NcDbDatabase * pDb,
                                  NcDbDimStyleTableRecord * pRec,
                                  int familyType,
                                  const NCHAR* title = NULL,
                                  int tabCtrlFlags = 0);
NRXHOSTGATE_EXPORT void ncedEnableUsrbrk();

NRXHOSTGATE_EXPORT NRX::UInt32 ncedGetAnimationFrameId(void);
NRXHOSTGATE_EXPORT unsigned int ncedGetBlockEditMode();

NRXHOSTGATE_EXPORT NRX::UInt8 ncedGetCommandVersion();
NRXHOSTGATE_EXPORT short ncedGetCurVportCircleSides();
NRXHOSTGATE_EXPORT void ncedGetCurVportPixelToDisplay(double& xFactor, double& yFactor);
NRXHOSTGATE_EXPORT void ncedGetCurVportScreenToDisplay(double& xFactor, double& yFactor);
NRXHOSTGATE_EXPORT bool ncedGetUnitsConversion(NcDb::UnitsValue blkInsunits, double& conversionFactor);
//extern NRX::Boolean
//ncedGetUserFavoritesDir(NCHAR* szFavoritesDir);

NRXHOSTGATE_EXPORT bool ncedHideConstraintBar(NcDbFullSubentPathArray &subentPaths);

NRXHOSTGATE_EXPORT NRX::UInt8 ncedInitCommandVersion(NRX::UInt8 nVersion = 0);

NRXHOSTGATE_EXPORT NRX::Boolean ncedInitDialog(NRX::Boolean useDialog = NRX::kTrue);
NRXHOSTGATE_EXPORT bool ncedIsInBackgroundMode();
NRXHOSTGATE_EXPORT bool ncedIsUsrbrkDisabled();

NRXHOSTGATE_EXPORT Nano::ErrorStatus
ncedManageHatchEditorReactor(NcDbObjectId hatchId,
                             NcHatchEdReact action,
                             NcDbObjectId boundaryId = NcDbObjectId::kNull,
                             NcHatchNotifier notifyType = kNobody,
                             bool transformed = false);
NRXHOSTGATE_EXPORT void ncedOpenDocWindowsMinimized( bool bMinimized );
//extern NRX::Boolean
//ncedResolveInternetShortcut(const NCHAR* szLinkFile, NCHAR* szUrl);
//extern NRX::Boolean
//ncedResolveShortcut(void* pvHwndParent, const NCHAR* szLinkPath,
//                    NCHAR* szObjectPath);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedSelectTransients(const NcGsDCRect& rect,
                                       int viewportNumber,
                                       NcArray<NcEdSelectedTransient>& result);

NRXHOSTGATE_EXPORT Nano::ErrorStatus
ncedSetXrefResolvedWithUpdateStatus(NcDbBlockTableRecord* pBTR);

NRXHOSTGATE_EXPORT bool ncedShowConstraintBar(NcDbFullSubentPathArray &subentPaths);

NRXHOSTGATE_EXPORT bool ncedShowConstraintBarForAll(bool bToShow);

NRXHOSTGATE_EXPORT Nano::ErrorStatus
ncedSkipXrefNotification(NcDbDatabase* pHostDb, const NCHAR* xrefName);
NRXHOSTGATE_EXPORT int            ncedSSSetSubentTypes(const NcArray<NcDb::SubentType>& types);
NRXHOSTGATE_EXPORT int            ncedSSSubentDel    (const NcDbFullSubentPath& subentity,
                                                    const nds_name ss);
NRXHOSTGATE_EXPORT int            ncedSSSubentMemb   (const NcDbFullSubentPath& subentity,
                                                    const nds_name ss);
NRXHOSTGATE_EXPORT int            ncedSSSubentName   (const nds_name sname,
                                   NRX::Int32 entIndex,
                                   NRX::Int32 subentIndex,
                                   NcDbFullSubentPath& subentity);
NRXHOSTGATE_EXPORT int            ncedSSSubentNameX  (struct resbuf** rbpp,
                                   const nds_name ss,
                                   const NRX::Int32 entIndex,
                                   const NRX::Int32 subentIndex,
                                   unsigned int flags);
NRXHOSTGATE_EXPORT int ncedSSSubentLength (const nds_name sname, NRX::Int32 index, NRX::Int32* len);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedTraceBoundary(const NcGePoint3d& seedPoint,
                                    bool detectIslands,
                                    NcDbVoidPtrArray& resultingBoundarySet);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedVPLayer(const NcDbObjectId& vpId, const NcDbObjectIdArray& layerIds,
                              NcDb::VpFreezeOps operation);

NRXHOSTGATE_EXPORT Nano::ErrorStatus
ncedXrefNotifyCheckFileChanged(NcDbObjectId btrId, bool& hasChanged);

NRXHOSTGATE_EXPORT BOOL ncedGetCurrentColorsEx(NcColorSettings* pColorSettings,
                            NcColorSettingsEx* pColorSettingsEx);
NRXHOSTGATE_EXPORT BOOL ncedGetCurrentColorsEx2(NcColorSettings* pColorSettings,
                             NcColorSettingsEx* pColorSettingsEx,
                             NcColorSettingsEx2* pColorSettingsEx2);
NRXHOSTGATE_EXPORT BOOL ncedGetSystemColorsEx(NcColorSettings* pColorSettings,
                           NcColorSettingsEx* pColorSettingsEx);
NRXHOSTGATE_EXPORT BOOL ncedGetSystemColorsEx2(NcColorSettings* pColorSettings,
                            NcColorSettingsEx* pColorSettingsEx,
                            NcColorSettingsEx2* pColorSettingsEx2);
NRXHOSTGATE_EXPORT BOOL ncedSetCurrentColorsEx(NcColorSettings* pColorSettings,
                            NcColorSettingsEx* pColorSettingsEx);
NRXHOSTGATE_EXPORT BOOL ncedSetCurrentColorsEx2(NcColorSettings* pColorSettings,
                             NcColorSettingsEx* pColorSettingsEx,
                             NcColorSettingsEx2* pColorSettingsEx2);

NRXHOSTGATE_EXPORT NdApplicationFrame* ncedGetApplicationFrame();
NRXHOSTGATE_EXPORT BOOL ncedRegisterMainFramePreTranslateObserver(const NcedPreTranslateMsgFn pfn);
NRXHOSTGATE_EXPORT BOOL ncedRegisterOnModal(const NcedOnModalFn pfn);
NRXHOSTGATE_EXPORT BOOL ncedRemoveMainFramePreTranslateObserver(const NcedPreTranslateMsgFn pfn);
NRXHOSTGATE_EXPORT BOOL ncedRemoveOnModal(const NcedOnModalFn pfn);

NRXHOSTGATE_EXPORT Nano::ErrorStatus addSSgetFilterInputContextReactor(NcApDocument *pDoc, NcEdSSGetFilter *pFilter);
NRXHOSTGATE_EXPORT bool duplicateSelectionsAllowed(NcApDocument *pDoc);

NRXHOSTGATE_EXPORT NcEdCommandStatusFlags& operator&=(NcEdCommandStatusFlags& f, int i);
NRXHOSTGATE_EXPORT NcEdCommandStatusFlags& operator|=(NcEdCommandStatusFlags& f, int i);

NRXHOSTGATE_EXPORT Nano::ErrorStatus setAllowDuplicateSelection(
                        NcApDocument *pDoc, boolean flag);

NRXHOSTGATE_EXPORT NRX::Boolean ncedCreateInternetShortcut(const NCHAR* szURL, const NCHAR* szShortcutPath);
NRXHOSTGATE_EXPORT NRX::Boolean ncedGetUserFavoritesDir(NCHAR* szFavoritesDir);
NRXHOSTGATE_EXPORT NRX::Boolean ncedResolveInternetShortcut(const NCHAR* szLinkFile, NCHAR* szUrl);
NRXHOSTGATE_EXPORT NRX::Boolean ncedResolveShortcut(void* pvHwndParent, const NCHAR* szLinkPath,
                                NCHAR* szObjectPath);

NRXHOSTGATE_EXPORT NRX::Boolean ncedCreateShortcut(void* pvHwndParent, const NCHAR* szLinkPath,
                                const NCHAR* szObjectPath, const NCHAR* szDesc);
NRXHOSTGATE_EXPORT NRX::Boolean ncedSetColorDialogTrueColorWithCallback(NcCmColor& color,
                                                     NRX::Boolean bAllowMetaColor,
                                                     const NcCmColor& curLayerColor,
                                                     NcCm::DialogTabs tabs = (NcCm::DialogTabs)(NcCm::kACITab | NcCm::kTrueColorTab  | NcCm::kColorBookTab),
                                                     NcEdColorDialogCallbackFunction callback = NULL,
                                                     void* pCallbackData = NULL);
NRXHOSTGATE_EXPORT Nano::ErrorStatus addSSgetFilterInputContextReactor(NcApDocument*pDoc, NcEdSSGetFilter*pFilter);
NRXHOSTGATE_EXPORT Nano::ErrorStatus addSSgetFilterInputContextReactor(NcApDocument*pDoc, NcEdSSGetFilter2*pFilter);
NRXHOSTGATE_EXPORT Nano::ErrorStatus addSSgetFilterInputContextReactor(NcApDocument*pDoc, NcEdSSGetFilter3*pFilter);
NRXHOSTGATE_EXPORT Nano::ErrorStatus addSSgetFilterInputContextReactor(NcApDocument*pDoc, NcEdSSGetFilter4*pFilter);
NRXHOSTGATE_EXPORT Nano::ErrorStatus addSSgetFilterInputContextReactor(NcApDocument*pDoc, NcEdSSGetSubSelectFilter*pFilter);
NRXHOSTGATE_EXPORT Nano::ErrorStatus removeSSgetFilterInputContextReactor(NcApDocument *pDoc, NcEdSSGetFilter *pFilter);
NRXHOSTGATE_EXPORT Nano::ErrorStatus removeSSgetFilterInputContextReactor(NcApDocument*pDoc, NcEdSSGetFilter2*pFilter);
NRXHOSTGATE_EXPORT Nano::ErrorStatus removeSSgetFilterInputContextReactor(NcApDocument*pDoc, NcEdSSGetFilter3*pFilter);
NRXHOSTGATE_EXPORT Nano::ErrorStatus removeSSgetFilterInputContextReactor(NcApDocument*pDoc, NcEdSSGetFilter4*pFilter);
NRXHOSTGATE_EXPORT Nano::ErrorStatus removeSSgetFilterInputContextReactor(NcApDocument*pDoc, NcEdSSGetSubSelectFilter*pFilter);
typedef NcEdSymbolUtilities::Services NcEdSymUtilServices;
NRXHOSTGATE_EXPORT const NcEdSymUtilServices* ncedSymUtil();
#endif // _OPENDWG_INTERACTIONHOST_H__
