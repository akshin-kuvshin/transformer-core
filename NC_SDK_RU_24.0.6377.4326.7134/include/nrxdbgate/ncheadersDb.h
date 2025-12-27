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

#ifndef __NCDBHEADERS_H__
#define __NCDBHEADERS_H__

#ifndef _NCAD_BUILD_
#define _NCAD_BUILD_
#endif

#ifdef _ODA_COMMON_INCLUDED_
#error Must not include Teigha headers before ncheaders.h
#endif

#include <assert.h>
#include <crtdbg.h>
#include <float.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <share.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <comdef.h> // include comdef.h before initguid.h to avoid 'GUID_NULL' : undeclared identifier errors
#include <initguid.h>
#include <ocidl.h>

#ifdef __ATLCOM_H__
	#define REDEFINE_INTERFACE_IN_NRXGATE
#endif
#ifdef USE_TD_HEADERS
#include "tdheaders.h"
#else
#ifdef __ATLCOM_H__
#include "OdaX.h"
#endif //__ATLCOM_H__
#endif //USE_TD_HEADERS
#include "mcheaders.h"

#ifdef __ATLCOM_H__
	//#include <afxole.h>
#ifdef USE_TD_HEADERS
	#include <hostopm.h>
	#pragma comment (lib, "hostopm.lib")
#endif
#endif // __ATLCOM_H__

#ifdef NRXGATE_BUILD
#include <HostGsManager.h>
#pragma comment (lib, "hostgsmanager.lib")
#endif

////////////////////////////////////////////////////////////////////////////////
//
#include "typesDb.h"
#include "array.h"
#include "core.h"
#include "ncstring.h"
#include "nc64BitHelpers.h"
#include "geometry.h"
#include "objectid.h"
#include "filer.h"
#include "graphics.h"
#include "objptr.h"
#include "document.h"
#include "idmapping.h"
#include "database.h"
#include "applicationDb.h"
#include "interactionDb.h"
#include "symbolutilities.h"
#include "image.h"
#include "boundary.h"
#include "hiddenLines.h"

#include "wizardDb.h"


#ifdef __ATLCOM_H__
#include "opm.h"
#include "axutils.h"
#include "axtempl.h"
#include "opmextension.h"
#endif

#define put_Color  put_color

#ifdef __AFXEXT_H__ //_AFXEXT
#include "extensionDb.h"
#endif // _AFXEXT

#if !defined(HOST_IN_QT)
#pragma comment (lib, "NrxDbGate.lib")
#endif

#endif // __NCDBHEADERS_H__