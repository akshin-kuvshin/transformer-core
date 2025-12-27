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

#pragma once
 
#ifdef _VERBOSEHEADERS_
	#pragma message("Use " __FILE__)
#endif
   
#include "McAPIs.h"
#include "MCSVariant.h"
#include "MCSGeometry.h"
#include "IMcErrors.h"
#include "IMcStream.h"
#include "IMcDocuments.h"
#include "IMcObjects.h"
#include "IMcNativeGate.h"
#include "IMcEvents.h"
#include "IMcStyles.h"
#include "IMechanics.h"
#include "McsParams.h"

// force declare MCS context with some MFC classes, 
// it allows to compile icontext.h with non-MFC projects
class CWnd;
class CStringArray;
#if _MSC_VER < 1300
  class CString;
#else
  #ifndef __AFXSTR_H__
    class CString;
  #endif
#endif
class CListCtrl;

struct IMcContext;

#define IMCS_STD_FUNCTION_DEFINITION(IIDOBJECT)

struct m3dServer;
struct IMc3dSite;
struct ITcsGate;
struct IMcPTGlobals;
struct IMcFormatManager;
class IDBBrowser;

extern "C" // force undecorated names
{
	extern MCTYP_API IMcObjectsManager       *gpMcObjManager;
	extern MCTYP_API IMcDocumentsManager     *gpMcDocManager;
	extern MCTYP_API IMcStyleManager         *gpMcStyleManager;
	extern MCTYP_API IMcTransactionManager   *gpMcTransManager;
	extern MCTYP_API IMcNativeGate           *gpMcNativeGate;
	extern MCTYP_API IMcContext              *gpMcContext;
	extern MCTYP_API IMcNotificator          *gpMcNotificator;
	extern MCTYP_API IMcParamManager         *gpMcDefParamManager;
	extern MCTYP_API IMcFormatManager        *gpMcFormatManager;
	//extern MCTYP_API IMcLinksManager         *gpMcLinksManager;
	extern MCTYP_API ITcsGate                *gpTcsGate;
	extern MCTYP_API IMcSubentIdentification *gpMcSubentIdent;
	extern MCTYP_API IDBBrowser              *gpMcBrowser;

	extern MCTYP_API m3dServer               *gp3dServer; // low-level 3D native gate
	extern MCTYP_API IMc3dSite               *gp3dSite; // common MechaniCS 3D implementations
}

#define gpMcParamManager (gpMcDocManager->getWorkingDocument() ? gpMcDocManager->getWorkingDocument()->params() : gpMcDefParamManager)

#ifndef MCTYP_DLL
  #pragma comment(lib,"mctyp.lib")
#endif
