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

#ifndef _HOSTTYPES_H_
#define _HOSTTYPES_H_

#include <limits.h>
#include <float.h>

#if defined(_WINDOWS_) && !defined(WINDOWS)
#define WINDOWS
#endif

// for MFC and Developer Studio definitions
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifndef _WINDOWS_
// issue message when windows.h is not included
#pragma message("Use " __FILE__)

#define CALLBACK __stdcall
#ifndef PURE
#define PURE = 0
#endif

//////////////////////////////////////////////////////////
//
// define some useful data types (windows.h is not included)

typedef void                VOID;
typedef int                 BOOL;

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;

typedef unsigned int        UINT;
typedef signed long         LONG;

#ifndef NULL
#define NULL        0
#endif

#ifndef FALSE
#define FALSE       0
#endif

#ifndef TRUE
#define TRUE        1
#endif

typedef void*           PVOID;
typedef void*           LPVOID;

typedef char*           PSTR;
typedef char*           LPSTR;

typedef const char*     PCSTR;
typedef const char*     LPCSTR;

typedef BYTE*           PBYTE;
typedef BYTE*           LPBYTE;

typedef int*            PINT;
typedef int*            LPINT;

typedef WORD*           PWORD;
typedef WORD*           LPWORD;

typedef long*           PLONG;
typedef long*           LPLONG;

typedef DWORD*          PDWORD;
typedef DWORD*          LPDWORD;

 // Note that we define POINT, RECT and SIZE fields as ints, not longs
 // since MFC classes use int variables in methods
typedef struct tagRECT
{
  int left;
  int top;
  int right;
  int bottom;
} RECT, *PRECT, *LPRECT;

typedef const RECT* PCRECT;
typedef const RECT* LPCRECT;

typedef struct tagPOINT
{
  int x;
  int y;
} POINT, *PPOINT, *LPPOINT;

typedef const POINT* PCPOINT;
typedef const POINT* LPCPOINT;

typedef struct tagSIZE
{
  int cx;
  int cy;
} SIZE, *PSIZE, *LPSIZE;

typedef const SIZE* PCSIZE;
typedef const SIZE* LPCSIZE;

typedef long           LPARAM;
typedef unsigned long  COLORREF;

typedef void* HMODULE;

#endif // _WINDOWS_

// Windows do not define the data types below
typedef UINT*           PUINT;
typedef UINT*           LPUINT;

typedef BOOL*           PBOOL;
typedef BOOL*           LPBOOL;

//////////////////////////////////////////////////
//
// floating-point data types

typedef float           SREAL;
typedef float*          PSREAL;

typedef double          REAL;
typedef double*         PREAL;

typedef long double     LREAL;
typedef long double*    LPREAL;

typedef struct tagRPOINT // rpt
{
  REAL x;
  REAL y;
} RPOINT, *PRPOINT;

typedef const RPOINT* PCRPOINT;
typedef const RPOINT* LPCRPOINT;

typedef struct tagSRPOINT // srpt
{
  SREAL x;
  SREAL y;
} SRPOINT, *PSRPOINT;

typedef const SRPOINT* PCSRPOINT;
typedef const SRPOINT* LPCSRPOINT;

typedef struct tagRSIZE // rsz
{
  REAL cx;
  REAL cy;
} RSIZE, * PRSIZE;

typedef const RSIZE* PCRSIZE;
typedef const RSIZE* LPCRSIZE;

typedef struct tagRRECT // rrc
{
  REAL  left,
        top,
        right,
        bottom;
} RRECT, * PRRECT;

typedef const RRECT* PCRRECT;
typedef const RRECT* LPCRRECT;

////////////////////////////////////////////////////////////
//

#define PALETTE_COLOR(rgb) (0x02000000 | (rgb))

// useful macro for declaration of pointer to function
#define FUNCPTR(type, name) type (CALLBACK *name)
#define FUNCPTR_C(type, name) type (*name)

// define DLL entry point
#define DLLEXPORT           __declspec(dllexport)
#define EXPORTPROC(type)    DLLEXPORT type CALLBACK
#define EXPORTPROC_C(type)  extern "C" DLLEXPORT type 

#define EXPORTMETHOD(type)  EXPORTPROC(type)
#define EXPORTMETHOD_       DLLEXPORT

// define DLL entry point for dlls with dynamic loading - no mangled names, please
#define EXPORTPROC_DYNLOAD(type) extern "C" EXPORTPROC(type)

// standard function to retrieved current instance (implemented in libmain.lib)
extern "C" void* This_GetInstance();

#define OffsetOf(s, m)  ((ptrdiff_t )&( ((s*)0)->m ))

////////////////////////////////////////////////////////////
//
// constants
//
#define REAL_DEFAULT_PRECISION  .001
#define REAL_MAX_VALUE_DECIMAL  100000000000000. // max double digits = 14 see float h

#define GMC_REAL_MAX_COORD    (REAL)  (REAL_MAX_VALUE_DECIMAL * REAL_DEFAULT_PRECISION)
#define GMC_REAL_MIN_COORD    (REAL) -(REAL_MAX_VALUE_DECIMAL * REAL_DEFAULT_PRECISION)

#define GMC_REAL_MAX    (REAL) (INT_MAX)
#define GMC_REAL_MIN    (REAL) (INT_MIN)

#define GMC_PI       (3.14159265359)
#define GMC_PI_3     (GMC_PI/3)
#define GMC_PI_2     (GMC_PI/2)
#define GMC_2PI_3    ((GMC_PI * 2)/3)
#define GMC_3PI_2    ((GMC_PI * 3)/2)
#define GMC_2PI      (2*GMC_PI)
#define GMC_0        (0.)

#define GMC_MM_IN_INCH  (25.4)

//
// Floating point comparison
//

#ifndef CS_FLOAT_COMPARISON
#define CS_FLOAT_COMPARISON

__inline BOOL FEQ(const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
  {
    return a-e <= b && b <= a+e;
  }

__inline BOOL FNE(const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
  { return !FEQ(a, b, e); }

__inline BOOL FGT(const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
  { return a-e > b; }

__inline BOOL FGE(const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
  { return a >= b-e; }

__inline BOOL FLT(const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
  { return !FGE(a, b, e); }

__inline BOOL FLE(const double a, const double b, const double e = REAL_DEFAULT_PRECISION)
  { return !FGT(a, b, e); }

#endif // CS_FLOAT_COMPARISON

/////////////////////////////////////////////////////////////////////////
//

// C++ safe replacement for min/max macros
#if __DISABLE__

#ifdef max
  #undef max
#endif

#ifdef min
  #undef min
#endif

inline int max(const int a, const int b)
  { return a > b ? a : b; }

inline unsigned max(const unsigned a, const unsigned b)
  { return a > b ? a : b; }

inline unsigned long max(const unsigned long a, const unsigned long b)
  { return a > b ? a : b; }

inline long max(const long a, const long b)
  { return a > b ? a : b; }

inline double max(const double a, const double b)
  { return a > b ? a : b; }

inline float max(const float a, const float b)
  { return a > b ? a : b; }


inline int min(const int a, const int b)
  { return a < b ? a : b; }

inline unsigned min(const unsigned a, const unsigned b)
  { return a < b ? a : b; }

inline unsigned long min(const unsigned long a, const unsigned long b)
  { return a < b ? a : b; }

inline long min(const long a, const long b)
  { return a < b ? a : b; }

inline double min(const double a, const double b)
  { return a < b ? a : b; }

inline float min(const float a, const float b)
  { return a < b ? a : b; }
#else

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif

#define CS_DLL_EXT ".dll"
#define CS_MODULE(s) s##".dll"

#define CS_DLL_EXTW L".dll"
#define CS_MODULEW(s) s##L".dll"

#define CS_DIR_TREE_ENVVAL "CS_WI_DIR_TREE"

#define CS_ADD_PATH_ENV "CS_ADD_PATH"

#ifndef WINDOWS

typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character

typedef WCHAR *PWCHAR, *LPWCH, *PWCH;
typedef const WCHAR *LPCWCH, *PCWCH;
typedef __nullterminated WCHAR *NWPSTR, *LPWSTR, *PWSTR;
typedef __nullterminated PWSTR *PZPWSTR;
typedef __nullterminated const PWSTR *PCZPWSTR;
#ifdef UNALIGNED
typedef __nullterminated WCHAR UNALIGNED *LPUWSTR, *PUWSTR;
#endif
typedef __nullterminated const WCHAR *LPCWSTR, *PCWSTR;
typedef __nullterminated PCWSTR *PZPCWSTR;
#ifdef UNALIGNED
typedef __nullterminated const WCHAR UNALIGNED *LPCUWSTR, *PCUWSTR;
#endif


#ifdef  UNICODE                     // r_winnt
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TBYTE , *PTBYTE ;
typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR PCTSTR, LPCTSTR;
//typedef LPUWSTR PUTSTR, LPUTSTR;
//typedef LPCUWSTR PCUTSTR, LPCUTSTR;
typedef LPWSTR LP;
#define __TEXT(quote) L##quote      // r_winnt
#else   /* UNICODE */               // r_winnt
typedef char TCHAR, *PTCHAR;
typedef unsigned char TBYTE , *PTBYTE ;
typedef LPSTR LPTCH, PTCH;
typedef LPSTR PTSTR, LPTSTR, PUTSTR, LPUTSTR;
typedef LPCSTR PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;
#define __TEXT(quote) quote         // r_winnt
#endif /* UNICODE */ 
#endif

#ifdef WINDOWS
#undef  OutputDebugString
inline void __OutputDebugString(LPCSTR lpOut){
  OutputDebugStringA(lpOut);
}  
inline void __OutputDebugString(LPCWSTR lpOut){
  OutputDebugStringW(lpOut);
}  
#define OutputDebugString __OutputDebugString
#endif


#endif // _HOSTTYPES_H_
