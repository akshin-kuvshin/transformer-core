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

#ifndef MFC_DEBUG
	#ifdef _DEBUG
		#define _DEBUG_WAS_DEFINED
		#undef _DEBUG
		#define NDEBUG
	#endif
#endif//#ifndef MFC_DEBUG

#include <memory>

#ifdef _DEBUG_WAS_DEFINED
	#undef _DEBUG_WAS_DEFINED
	#undef NDEBUG
	#define _DEBUG
#endif

struct CSOmsk
{
	// The types Int8, Int16 and Int32 will be conditionally compiled
	// to guarantee that each one represents an integer type of exactly
	// 8, 16 and 32 bits respectively.    These are to be used only when
	// the EXACT size of the integer is critical.
	//
	typedef char       Int8;
	typedef short      Int16;
	typedef long       Int32;
	//
	// The unsigned versions of the above types.
	//
	typedef unsigned char  UInt8;
	typedef unsigned short UInt16;
	typedef unsigned long  UInt32;

	// Convenient abbreviations (use optionally).
	//
	typedef unsigned char  uchar;
	typedef unsigned short ushort;
	typedef unsigned int   uint;
	typedef unsigned long  ulong;

    // Logical type (Note: never use int when Boolean is intended!)
    //
#ifndef CSOmsk_Boolean_is_bool
    typedef int        Boolean;
    enum           { kFalse = 0, kTrue = 1 };
#else
    typedef bool       Boolean;
    enum           { kFalse = false, kTrue = true };
#endif

#ifdef WIN64
    typedef unsigned __int64    Size_t;
    typedef __int64             SSize_t;
#else
    typedef unsigned long       Size_t;
    typedef long                SSize_t;
#endif

};

#ifndef NULL
#define NULL 0
#endif

//  These are constant definitions: regardless of whether the Unicode 
//  or legacy character system is in use, the legacy character type
//  will always be an 8-bit character.
//
//  Note: use LEGACY_CHAR to represent *textual* information; do not
//  use it for 8-bit binary data; the AC_BYTE type, below, is intended
//  for that use.  Use legacy characters sparingly, where ACHAR is 
//  inappropriate.
typedef          char         LEGACY_CHAR;
typedef          char*        LEGACY_STRING;
typedef const    char*        LEGACY_STRING_CONST;
typedef       unsigned short  WIDE_CHAR;          // UTF-16 format
typedef       unsigned short* WIDE_STRING;        // UTF-16 format
typedef const unsigned short* WIDE_STRING_CONST;  // UTF-16 format

//  One of the (ab)uses of the char type is to point to bytes of memory.
//  The (void*) isn't good for this because the sizeof a void element may
//  not be what one expects.  This type is offered as a generic pointer
//  to memory, but in which sizeof(element) == 1.  We use char instead
//  of byte only because signed/unsigned mismatches will cause a flurry
//  of warnings in the transition; eventually, the type can be anything
//  we want.
typedef          char*   MEMORY_POINTER;
typedef const    char*   MEMORY_POINTER_CONST;

//  Describes an 8-bit numerical quantity, *not* a character.
typedef unsigned char    AC_BYTE;

// Use ADESK_NO_VTABLE on base classes which:
//   1. have virtual methods
//   2. are never instantiated
//   3. have a ctor and/or a dtor
//   4. do not call any virtual methods in the ctor or dtor
// This allows the compiler to avoid assigning a vtable pointer at
// the top of the base class's ctor and dtor.  So the vtable itself
// and any methods it points to which aren't used elsewhere can be
// omitted by the linker and reduce overall space.
//
// Make sure though that the base class is never instantiated.  Making
// the ctor protected or using pure virtual methods can help with this.
//
#define CSOMSK_NO_VTABLE __declspec(novtable)
#define CSOMSK_STDCALL   __stdcall
#define CSOMSK_DEPRECATED __declspec(deprecated)
