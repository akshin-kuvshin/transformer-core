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

#ifndef NANOMCGE
#define NANOMCGE
#endif

#define MCGEL
// Lion007 : CS_FLOAT_COMPARISON now defined in hostTypes.h
//#define CS_FLOAT_COMPARISON
#define NOACGE

#if defined _WIN64 && !defined(WIN64)
	#define WIN64
#endif

#include <hostTypes.h>
#include <McsTypes.h>
// MAPI geometry
#include <McsTempl.h>

#include <McGe\mcarc3d.h>
#include <McGe\mcblok3d.h>
#include <McGe\mccomp3d.h>
#include <McGe\mccurv3d.h>
#include <McGe\mcell3d.h>
#include <McGe\mcent3d.h>
#include <McGe\mcgbl.h>
#include <McGe\mcgblge.h>
#include <McGe\mcintrvl.h>
#include <McGe\mckvec.h>
#include <McGe\mclent3d.h>
#include <McGe\mcline3d.h>
#include <McGe\mclnsg3d.h>
#include <McGe\mcmat2d.h>
#include <McGe\mcmat3d.h>
#include <McGe\mcnurb3d.h>
#include <McGe\mcnurbsf.h>
#include <McGe\mcplane.h>
#include <McGe\mcpnt2d.h>
#include <McGe\mcpnt3d.h>
#include <McGe\mcponc3d.h>
#include <McGe\mcsent3d.h>
#include <McGe\mctol.h>
#include <McGe\mcvec2d.h>
#include <McGe\mcvec3d.h>
#include <McGe\mccint3d.h>
#include <McGe\mcoffc3d.h>
#include <McGe\mcray3d.h>
#include <McGe\mcpos3d.h>

#pragma comment (lib, "mcgel.lib")
//#pragma comment (lib, "mcddgate3.lib")
#pragma comment (lib, "mt.lib")
