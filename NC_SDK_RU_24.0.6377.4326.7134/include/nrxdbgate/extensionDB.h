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

#ifndef __OPENDWG_AFXEXT_H__
#define __OPENDWG_AFXEXT_H__

#include "interactionDB.h"
#if !defined(HOST_IN_QT)
#include <afxext.h>
#else
#include "windows.h"
#endif
#include "nrxdbgate_impexp.h"


#undef ncedGetWinNum
#undef ncedStartOverrideDropTarget
#undef ncedRevokeCustomDropTarget
#undef ncedEndOverrideDropTarget



class NRXDBGATE_EXPORT CNcExtensionModule
{
public:
	CNcExtensionModule();

public:
	BOOL Attached();

	HINSTANCE DefaultResourceInstance();
	HINSTANCE ModuleResourceInstance();

	BOOL AttachInstance(HINSTANCE hInstance);
	void DetachInstance();

protected:
	BOOL                 m_bAttached;

	HINSTANCE            m_hDefaultResource;
	HINSTANCE            m_hModuleResource;
	//FIXME
#if !defined(HOST_IN_QT)
	AFX_EXTENSION_MODULE m_module;
#endif
};

class CNcModuleResourceOverride
{
public:
	inline CNcModuleResourceOverride::CNcModuleResourceOverride(HINSTANCE hInst = NULL)
	{
#if !defined(HOST_IN_QT)
		m_hinstSave = ::AfxGetResourceHandle();
		if (hInst == NULL)
			hInst = m_Module.ModuleResourceInstance();
		::AfxSetResourceHandle(hInst);
#endif
	}

	inline CNcModuleResourceOverride::~CNcModuleResourceOverride()
	{
#if !defined(HOST_IN_QT)
		::AfxSetResourceHandle(m_hinstSave);
#endif
	}

private:
	static CNcExtensionModule& m_Module;
	HINSTANCE                  m_hinstSave;
};

#define NC_DECLARE_EXTENSION_MODULE(exm) \
        extern CNcExtensionModule exm;

#define NC_IMPLEMENT_EXTENSION_MODULE(exm) \
        CNcExtensionModule exm; \
        CNcExtensionModule& CNcModuleResourceOverride::m_Module = exm;


//typedef struct tagChildFrmSettings
//{
//	NcColorSettings m_ColorSettings;
//	bool            m_bShowLayoutBar;
//	bool            m_bShowScrollBar;
//	CDialogBar*     m_pDialogBar;
//	bool            m_bIsBedit;
//} NcChildFrmSettings;

///////////////////////////////////////////////////////////////////////////////////////////////////////
// typedefs
typedef double  ncedDwgPoint[3];

typedef void (*NcedWatchWinMsgFn)(const MSG*);
typedef BOOL (*NcedFilterWinMsgFn)(MSG*);
typedef void (*NcedOnIdleMsgFn)();

///////////////////////////////////////////////////////////////////////////////////////////////////////
// methods
//from InitNcUiDLL to NcUiRootKey moved to extensionUI.cpp in NrxUiGate

//from ncedGetNcadWinApp to ncedGetNcadDwgView moved to extensionHost.cpp in NrxHostGate
#if !defined(HOST_IN_QT)
NRXDBGATE_EXPORT CMDIFrameWnd* ncedGetNcadFrame();
#endif
//CWnd *ncedGetNcadFrame();

//from ncedGetNcadDockCmdLine to ncedGetWinNum moved to extensionHost.cpp in NrxHostGate

//from ncedSetStatusBarProgressMeter to ncedRemoveDropTarget moved to extensionHost.cpp in NrxHostGate

NRXDBGATE_EXPORT NcDbDatabase* NcApGetDatabase(CView* view);

//from ncedGetRegistryCompany to ncedGetIUnknownForCurrentCommand moved to extensionHost.cpp in NrxHostGate

//ncedShowDrawingStatusBars moved to extensionHost.cpp in NrxHostGate

//ncedDrawingStatusBarsVisible moved to extensionHost.cpp in NrxHostGate

/////////////////////////////////////////////////////////////////////////////
//CNdUiTextTip window moved to extensionUI.cpp in NrxUiGate

/////////////////////////////////////////////////////////////////////////////
//CNdUiTipWindow moved to extensionUI.cpp in NrxUiGate

///////////////////////////////////////////////////////////////////////////////////////////////////
//CNdUiBaseDialog moved to extensionUI.cpp in NrxUiGate

#endif // __OPENDWG_AFXEXT_H__

