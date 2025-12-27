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

#if _MSC_VER >= 1900

	#undef WINVER
	#define WINVER       0x0601
	#undef _WIN32_WINNT
	#define _WIN32_WINNT 0x0601

#elif defined(WIN64) || defined(_WIN64)
	// compile for Win64 .......................................................

	#ifndef _WIN64
		#define _WIN64
	#endif

	#ifndef WIN64
		#define WIN64
	#endif

	#undef WINVER
	#define WINVER          0x0501

	#undef _WIN32_WINNT
	#define _WIN32_WINNT    0x0501

#else
	// compile for Win32 .......................................................

	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT    0x0501
	#endif 

	#if _WIN32_WINNT < 0x0501
		#pragma message("warning: incompatible _WIN32_WINNT")
		#undef _WIN32_WINNT
		#define _WIN32_WINNT    0x0501
	#endif

	#if !defined(WINVER)
		#define WINVER    0x0501
	#endif

	#if WINVER < 0x0501
		#pragma message("warning: incompatible WINVER")
		#undef WINVER
		#define WINVER    0x0501
	#endif

#endif //WIN64

#ifndef _WIN32_WINDOWS
	#define _WIN32_WINDOWS WINVER
#endif

#if _WIN32_WINDOWS < 0x0501
	#pragma message("warning: incompatible _WIN32_WINDOWS")
	#undef _WIN32_WINDOWS
	#define _WIN32_WINDOWS    0x0501
#endif

// _WIN32_IE .................................................................
#if _MSC_VER >= 1500

	// VS2008, need _WIN32_IE >= 0x0601 (Internet Explorer 6.0 SP1)
	// this is error in headers
	#ifndef _WIN32_IE
		#define _WIN32_IE    0x0601
	#endif
	#if _WIN32_IE < 0x0601
		#undef _WIN32_IE
		#define _WIN32_IE    0x0601  // Change this to the appropriate value to target IE 5.0 or later.
	#endif

#else

	// != VS2008
	#ifndef _WIN32_IE
		#define _WIN32_IE    0x0600
	#endif
	#if _WIN32_IE < 0x0600
		#undef _WIN32_IE
		#define _WIN32_IE    0x0600  // Change this to the appropriate value to target IE 5.0 or later.
	#endif

#endif
