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

#ifndef _EXTENSION_HOST_H_
#define _EXTENSION_HOST_H_

#ifndef HOST_IN_QT
#include <afxext.h>
#else
#include <windows.h>
#endif

#include "nrxhostgate_impexp.h"

#ifdef ncedGetWinNum
#undef ncedGetWinNum
#endif
#ifdef ncedStartOverrideDropTarget
#undef ncedStartOverrideDropTarget
#endif
#ifdef ncedRevokeCustomDropTarget
#undef ncedRevokeCustomDropTarget
#endif
#ifdef ncedEndOverrideDropTarget
#undef ncedEndOverrideDropTarget
#endif


//CNcExtensionModule moved to extensionDb.cpp in NrxDbGate

typedef struct tagChildFrmSettings
{
	NcColorSettings m_ColorSettings;
	bool            m_bShowLayoutBar;
	bool            m_bShowScrollBar;
#ifndef HOST_IN_QT //FIXME maybe need move to UI
	CDialogBar*     m_pDialogBar;
#endif
	bool            m_bIsBedit;
} NcChildFrmSettings;

///////////////////////////////////////////////////////////////////////////////////////////////////////
// typedefs
typedef double  ncedDwgPoint[3];

typedef void (*NcedWatchWinMsgFn)(const MSG*);
typedef BOOL (*NcedFilterWinMsgFn)(MSG*);
typedef void (*NcedOnIdleMsgFn)();

///////////////////////////////////////////////////////////////////////////////////////////////////////
// methods
//from InitNcUiDLL to NcUiRootKey moved to extensionUI.cpp in NrxUiGate
#ifndef HOST_IN_QT
NRXHOSTGATE_EXPORT CWinApp* ncedGetNcadWinApp();

NRXHOSTGATE_EXPORT CDocument* ncedGetNcadDoc();

NRXHOSTGATE_EXPORT CView* ncedGetNcadDwgView(); // Warning. CWnd* is returned

//ncedGetNcadFrame moved to extensionDb.cpp in NrxDbGate
//CWnd *ncedGetNcadFrame();

NRXHOSTGATE_EXPORT CWnd* ncedGetNcadDockCmdLine();

NRXHOSTGATE_EXPORT CWnd* ncedGetNcadTextCmdLine();
#endif
NRXHOSTGATE_EXPORT HINSTANCE ncedGetNcadResourceInstance();
#ifndef HOST_IN_QT
NRXHOSTGATE_EXPORT void ncedCoordFromPixelToWorld(const CPoint& ptIn, ncedDwgPoint ptOut);
NRXHOSTGATE_EXPORT BOOL ncedCoordFromPixelToWorld(int windnum, CPoint ptIn, ncedDwgPoint ptOut);
NRXHOSTGATE_EXPORT BOOL ncedCoordFromWorldToPixel(int windnum, const ncedDwgPoint ptIn, CPoint& ptOut);
#endif
NRXHOSTGATE_EXPORT int ncedGetWinNum(int ptx, int pty);

NRXHOSTGATE_EXPORT int ncedSetStatusBarProgressMeter(const NCHAR* pszLabel, int nMinPos, int nMaxPos);
NRXHOSTGATE_EXPORT int ncedSetStatusBarProgressMeterPos(int nPos);

NRXHOSTGATE_EXPORT void ncedRestoreStatusBar();

NRXHOSTGATE_EXPORT BOOL ncedRegisterFilterWinMsg(const NcedFilterWinMsgFn pfn);
NRXHOSTGATE_EXPORT BOOL ncedRemoveFilterWinMsg(const NcedFilterWinMsgFn pfn);

NRXHOSTGATE_EXPORT BOOL ncedRegisterWatchWinMsg(const NcedWatchWinMsgFn pfn);
NRXHOSTGATE_EXPORT BOOL ncedRemoveWatchWinMsg(const NcedWatchWinMsgFn pfn);

NRXHOSTGATE_EXPORT BOOL ncedRegisterOnIdleWinMsg(const NcedOnIdleMsgFn pfn);
NRXHOSTGATE_EXPORT BOOL ncedRemoveOnIdleWinMsg(const NcedOnIdleMsgFn pfn);

NRXHOSTGATE_EXPORT BOOL ncedGetCurrentColors(NcColorSettings* pColorSettings);
NRXHOSTGATE_EXPORT BOOL ncedSetCurrentColors(NcColorSettings* pColorSettings);
NRXHOSTGATE_EXPORT BOOL ncedGetSystemColors(NcColorSettings* pColorSettings);
#ifndef HOST_IN_QT
NRXHOSTGATE_EXPORT BOOL ncedGetChildFrameSettings(NcChildFrmSettings* pChildFrmSettings, CMDIChildWnd* pWnd);
NRXHOSTGATE_EXPORT BOOL ncedSetChildFrameSettings(NcChildFrmSettings* pChildFrmSettings, CMDIChildWnd* pWnd);
#endif
NRXHOSTGATE_EXPORT BOOL ncedRegisterCustomDropTarget(IDropTarget* pItarget);
NRXHOSTGATE_EXPORT BOOL ncedRevokeCustomDropTarget();
#ifndef HOST_IN_QT
NRXHOSTGATE_EXPORT BOOL ncedStartOverrideDropTarget(COleDropTarget* pTarget);

NRXHOSTGATE_EXPORT BOOL ncedEndOverrideDropTarget(COleDropTarget* pTarget);

NRXHOSTGATE_EXPORT BOOL ncedAddDropTarget(COleDropTarget* pTarget);

NRXHOSTGATE_EXPORT BOOL ncedRemoveDropTarget(COleDropTarget* pTarget);
#endif
//NcApGetDatabase moved to extensionDb.cpp in NrxDbGate
#ifndef HOST_IN_QT
NRXHOSTGATE_EXPORT const CString& ncedGetRegistryCompany();
#else
NRXHOSTGATE_EXPORT const OdString& ncedGetRegistryCompany();
#endif
NRXHOSTGATE_EXPORT BOOL ncedRegisterExtendedTab(LPCTSTR szAppName, LPCTSTR szDialogName);

NRXHOSTGATE_EXPORT HMENU ncedGetMenu(LPCTSTR pszAlias);

NRXHOSTGATE_EXPORT BOOL ncedIsInputPending();

NRXHOSTGATE_EXPORT BOOL ncedSetIUnknownForCurrentCommand(const LPUNKNOWN);
NRXHOSTGATE_EXPORT BOOL ncedGetIUnknownForCurrentCommand(LPUNKNOWN& pUnk);


NRXHOSTGATE_EXPORT BOOL ncedShowDrawingStatusBars(BOOL bShow = TRUE);

NRXHOSTGATE_EXPORT BOOL ncedDrawingStatusBarsVisible();

/////////////////////////////////////////////////////////////////////////////
// CNdUiTipWindow moved to extensionUI.cpp in NrxUiGate

/////////////////////////////////////////////////////////////////////////////
// CNdUiTextTip window moved to extensionUI.cpp in NrxUiGate

///////////////////////////////////////////////////////////////////////////////////////////////////
// CNdUiBaseDialog moved to extensionUI.cpp in NrxUiGate

#endif // _EXTENSION_HOST_H_

