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

#ifndef __NCHOSTHEADERS_H__
#define __NCHOSTHEADERS_H__

#include "nrxdbgate/ncheadersDb.h"
#ifndef HOST_IN_QT
#pragma comment (lib, "docbar.lib")
#endif
///////////////////////////////////////////////////////////////////////////////
#include "typesHost.h"

#include "applicationHost.h"
#include "plot.h"
#include "publish.h"
#include "nrxdbgate/boundary.h"
#include "interactionHost.h"
// #include "internalHost.h" // ISL: TODO: No internals in public headers!

#ifdef __AFXEXT_H__ //_AFXEXT
#include "extensionHost.h"
#endif // _AFXEXT

#include "nrxdbgate/wizardDb.h"
#include "wizardHost.h"

#ifdef _AFX
#include "hostStatusBar.h"
#endif
#ifndef HOST_IN_QT
#pragma comment (lib, "NrxHostGate.lib")
#else
#pragma comment (lib, "NrxHostGate_csd.lib")
#endif
#endif // __NCHOSTHEADERS_H__