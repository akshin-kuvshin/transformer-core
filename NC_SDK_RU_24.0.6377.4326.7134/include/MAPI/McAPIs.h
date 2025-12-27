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

#ifndef MT_API
	#ifndef __COMPILE_MT__
		#define MT_API __declspec(dllimport)
	#else
		#define MT_API __declspec(dllexport)
	#endif
#endif

#ifndef ET_API
  #ifdef ETDLL
   #define ET_API __declspec(dllexport) 
  #else
   #define ET_API __declspec(dllimport)
  #endif
#endif

#ifndef MECHCTL_API
  #ifdef MECHCTL
   #define MECHCTL_API __declspec(dllexport) 
  #else
   #define MECHCTL_API __declspec(dllimport) 
  #endif
#endif

#ifndef MCTYP_API
  #ifdef MCTYP_DLL
   #define MCTYP_API __declspec(dllexport) 
  #else
   #define MCTYP_API __declspec(dllimport) 
  #endif
#endif

#ifndef MCSBROWSER_API
	#ifdef MCSBROWSER_PRJ
		#define MCSBROWSER_API __declspec(dllexport)
	#else
		#define MCSBROWSER_API __declspec(dllimport)
	#endif
#endif

#ifndef DRAWING2D_API
  #ifdef LIB_DRAWING2D
    #define DRAWING2D_API extern "C" _declspec(dllexport)
  #else
    #define DRAWING2D_API extern "C" _declspec(dllimport)
  #endif
#endif

#ifndef M3D_API
  #ifdef M3D
    #define M3D_API __declspec(dllexport)
  #else
    #define M3D_API __declspec(dllimport)
  #endif
#endif

#ifndef PTCORE_EXPIMP
	#ifdef PTCORE_EXPORTS
		#define PTCORE_EXPIMP __declspec(dllexport)
	#else
		#define PTCORE_EXPIMP	__declspec(dllimport)
	#endif
#endif

#ifndef PTOBJECTS_EXPIMP
	#ifdef PTOBJECTS_EXPORTS
		#define PTOBJECTS_EXPIMP __declspec(dllexport)
	#else
		#define PTOBJECTS_EXPIMP __declspec(dllimport)
	#endif
#endif

#ifndef PTDIALOGS_EXPIMP
	#ifdef PTDIALOGS_EXPORTS
		#define PTDIALOGS_EXPIMP __declspec(dllexport)
	#else
		#define PTDIALOGS_EXPIMP __declspec(dllimport)
	#endif
#endif

#ifndef PTCORE_EXPIMP2
	#ifdef PTCORE_EXPORTS
		#define PTCORE_EXPIMP2(type) __declspec(dllexport) type
	#else
		#define PTCORE_EXPIMP2(type) __declspec(dllimport) type
	#endif
#endif

#ifndef DDOT_API
  #ifdef DDOT
    #define DDOT_API extern "C" __declspec(dllexport)
  #else
    #define DDOT_API extern "C" __declspec(dllimport)
  #endif
#endif

#ifndef PTCONTROLS_EXPIMP
	#ifdef PTCONTROLS_EXPORTS
			#define PTCONTROLS_EXPIMP __declspec(dllexport)
		#else
			#define PTCONTROLS_EXPIMP __declspec(dllimport)
	#endif
#endif

#ifndef PTOLE_EXPIMP
	#ifdef PTOLE_EXPORTS
			#define PTOLE_EXPIMP __declspec(dllexport)
		#else
			#define PTOLE_EXPIMP __declspec(dllimport)
	#endif
#endif

#ifndef PTCOMMANDS_EXPIMP
	#ifdef PTCOMMANDS_EXPORTS
			#define PTCOMMANDS_EXPIMP __declspec(dllexport)
		#else
			#define PTCOMMANDS_EXPIMP __declspec(dllimport)
	#endif
#endif

#ifndef MCGEL_API
	#ifndef MCGELDLL
		#define MCGEL_API __declspec(dllimport)
	#else
		#define MCGEL_API __declspec(dllexport)
	#endif
#endif

#ifndef MCFORMS_API
	#ifndef MCFORMSDLL
		#define MCFORMS_API __declspec(dllimport)
	#else
		#define MCFORMS_API __declspec(dllexport)
	#endif
#endif

#ifndef MODELER_API
	#ifndef MODELERDLL
		#define MODELER_API __declspec(dllimport) 
	#else
		#define MODELER_API __declspec(dllexport) 
	#endif
#endif

#ifndef MC_NANO_GATE_API
	#ifndef MC_NANO_GATE
		#define MC_NANO_GATE_API __declspec(dllimport) 
	#else
		#define MC_NANO_GATE_API __declspec(dllexport) 
	#endif
#endif

#ifndef MCCORESYMBOLS_API
	#ifndef MODULE_CORESYMBOLS
		#define MCCORESYMBOLS_API extern "C" __declspec(dllimport) 
		#define MCCORESYMBOLS_API_CPP extern __declspec(dllimport) 
	#else
		#define MCCORESYMBOLS_API extern "C" __declspec(dllexport) 
		#define MCCORESYMBOLS_API_CPP extern __declspec(dllexport) 
	#endif
#endif

#undef MECHWIZARD_API
#ifdef MODULE_MECHWIZARD
  #define MECHWIZARD_API __declspec(dllexport)
#else
  #define MECHWIZARD_API __declspec(dllimport)
#endif

#undef MCFLATTEN_API
#ifdef MCFLATTEN_DLL_EXPORTS
	#define MCFLATTEN_API __declspec(dllexport)
#else
	#define MCFLATTEN_API __declspec(dllimport)
#endif

#undef MCS_DBCONSTRAINTS_API
#ifdef MCS_DBCONSTRAINTS_DLL_EXPORTS
	#define MCS_DBCONSTRAINTS_API __declspec(dllexport)
#else
	#define MCS_DBCONSTRAINTS_API __declspec(dllimport)
#endif

#undef MCSPARSER_API
#ifdef MCSPARCER_PRJ
	#define MCSPARSER_API __declspec(dllexport)
#else
	#define MCSPARSER_API __declspec(dllimport)
#endif

#undef COMMANDS3D_API
#ifdef COMMANDS3D_DLL_EXPORTS
	#define COMMANDS3D_API __declspec(dllexport)
#else
	#define COMMANDS3D_API __declspec(dllimport)
#endif