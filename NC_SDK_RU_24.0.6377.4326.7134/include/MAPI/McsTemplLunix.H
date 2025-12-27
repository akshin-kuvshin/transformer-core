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

/*
WIN64 ISSUE

All templates and strings accept arguments in 64-bit form to avoid size-warnings.
Length of arrays, maps and strings is still 32-bit.
If any size-ref argument will across 32-bit boundary then 
assert box will appear and nothing will be done.
*/

#ifdef _VERBOSEHEADERS_
	#pragma message("Use " __FILE__)
#endif

#pragma warning(disable: 4786) // identifier was truncated to '255' characters in the debug information

#if !defined(__COMPILE_MT__) && !defined(NO_MTLIB)
	#pragma comment(lib,"MT.LIB") // strings need it
#endif

#include "mcsmem.h" // MCS shared memory management
#include "mcseds.h" // helper debug methods
#include <unknwn.h>

#include "McAPIs.h"

#define MCS_TEMPL_INCLUDED

// MFC compatability for old modules which uses MCArray.h
#ifdef __AFX_H__
	#ifndef __AFXTEMPL_H__
		#include "AfxTempl.h"
	#endif
#endif


#ifndef max
	#define max(a, b) ((a < b) ? (b) : (a))
#endif

#ifndef min
	#define min(a, b) ((a > b) ? (b) : (a))
#endif

//..............................................................................

// 05.04.13
// '&' Использовать нельзя, т.к. начинается вызываться перебитый "operator &"
// на фиктивном объекте
// #define _member_offset(ClassType1,MemberName) \
// 	INT_PTR(&(((ClassType1*)NULL)->MemberName))
#define _member_offset(ClassType1,MemberName) \
	((int)(INT_PTR)( mcsGetObjectAddress(((ClassType1*)NULL)->MemberName) ))

//=============================================================================

#ifndef HIDWORD
	#define HIDWORD(i64) ((DWORD)(((i64)&0xFFFFFFFF00000000L)>>32))
#endif
#ifndef LODWORD
	#define LODWORD(i64) ((DWORD)(((i64)&0x00000000FFFFFFFFL)))
#endif
#define MAKEI64(l32, h32) ((((__int64)(l32))&0x00000000FFFFFFFFL) | ((((__int64)(h32))&0x00000000FFFFFFFFL)<<32))

//=============================================================================
#define _eds_fJumpArrOnAdd    1
#define _eds_fJumpArrOnRemove 2
#define _eds_fDefecateMem     4

#define FECAL_BYTE 0xFC

__inline int _eds_GetArrOptions()
{
	static bool ls_fOptionsGotten = false;
	static int ls_options=0;
	if(ls_fOptionsGotten) 
		return ls_options;
	ls_fOptionsGotten = true;

	MEMORY_BASIC_INFORMATION mbi;
	if(!VirtualQuery(&ls_fOptionsGotten, &mbi, sizeof(mbi)))
		return 0;
	TCHAR thisModulePath[2048]=_T("");
	if(!GetModuleFileName((HMODULE)mbi.AllocationBase, thisModulePath, STRBUFSIZE(thisModulePath)))
		return 0;
	LPTSTR pLS = _tcsrchr(thisModulePath, _T('\\'));
	if(!pLS) 
		return 0;
	lstrcpyn(pLS+1, gstrMcsIniName, (int)(STRBUFSIZE(thisModulePath) - (pLS+1-thisModulePath)));

	if(GetPrivateProfileInt(_T("mt"), _T("JumpArrOnAdd"), 0, thisModulePath))
		ls_options |= _eds_fJumpArrOnAdd;
	if(GetPrivateProfileInt(_T("mt"), _T("JumpArrOnRemove"), 0, thisModulePath))
		ls_options |= _eds_fJumpArrOnRemove;
	if(GetPrivateProfileInt(_T("mt"), _T("DefecateMem"), 0, thisModulePath))
		ls_options |= _eds_fDefecateMem;
	return ls_options;
}
//=============================================================================
static const bool _gf_Enable_JumpArrOnAdd = !!(_eds_GetArrOptions()&_eds_fJumpArrOnAdd);
static const bool _gf_Enable_JumpArrOnRemove = !!(_eds_GetArrOptions()&_eds_fJumpArrOnRemove);
static const bool _gf_Enable_DefecateMem = !!(_eds_GetArrOptions()&_eds_fDefecateMem);
//===========================================================================
// functions below use always '.' as char for decimal point
// for dynamic link on request with DDOT.DLL
extern "C" MT_API double __cdecl strtodD(const char*, char **);
extern "C" MT_API double __cdecl wcstodD(const wchar_t*, wchar_t **);
extern "C" MT_API int __cdecl vsprintfD(char*, const char*, va_list);
extern "C" MT_API int __cdecl vswprintfD(wchar_t*, const wchar_t*, va_list);
extern "C" MT_API int __cdecl sprintfD(char*, const char*, ...);
extern "C" MT_API int __cdecl swprintfD(wchar_t *, const wchar_t *, ...);

// for static link with DDOT.DLL
DDOT_API double __cdecl _strtodD(const char*, char **);
DDOT_API double __cdecl _wcstodD(const wchar_t*, wchar_t **);
DDOT_API int __cdecl _vsprintfD(char*, const char*, va_list);
DDOT_API int __cdecl _vswprintfD(wchar_t*, const wchar_t*, va_list);
DDOT_API int __cdecl _sprintfD(char*, const char*, ...);
DDOT_API int __cdecl _swprintfD(wchar_t *, const wchar_t *, ...);

#if !defined(_UNICODE) && !defined(UNICODE)
	#define _tcstodD strtodD
	#define _vstprintfD vsprintfD
	#define _stprintfD sprintfD
#else
	#define _tcstodD wcstodD
	#define _vstprintfD vswprintfD
	#define _stprintfD swprintfD
#endif

//===========================================================================
#define MCSTEMPL_SPECIAL_ADDR (UINT_PTR)0xFDFD2006
#define MCSTEMPL_INVADDR_AS_TYPE(TYPE)       (*(TYPE*)(MCSTEMPL_SPECIAL_ADDR))
#define MCSTEMPL_INVADDR_AS_TYPEREF(TYPEREF) (*(TYPE*)(MCSTEMPL_SPECIAL_ADDR))
//===========================================================================

#define MCS_GET_OBJ_ADDR(obj) mcsGetObjectAddress(obj)

// 07.11.2018, И вот, 4-я реализация. Предыдущая (ниже, 3-я) рабочая,
// но по результаттам профилирования - очень тормозная.
// Новый вариант работает существенно быстрее, т.к. сюжетно важная строка кода
// сокращяется до двух инструкций процессора

template <class OBJECT>
__inline OBJECT* __stdcall mcsGetObjectAddress(OBJECT& objref)
{
	return (OBJECT*)&(DWORD_PTR&)objref;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// 02.03.12
// Это уже как минимум 3-е решение проблемы получения адреса объекта с перебитым оператором "&"
// По тестам работает в VS2005/2008, x32/64, debug/release
// и совместимо с опцией ""Whole program optimization"

template <class OBJECT>
struct _REF_TO_PTR
{
	OBJECT&  ref;

	_REF_TO_PTR(OBJECT& objref_arg) : ref(objref_arg)
	{
	}
};

/*
template <class OBJECT>
__inline OBJECT* __stdcall mcsGetObjectAddress(OBJECT& objref)
{
	_REF_TO_PTR<OBJECT> U(objref);
	DWORD_PTR* pDwa = (DWORD_PTR*)&U;
	return (OBJECT*)*pDwa;
}
*/

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
/*
// работающее "топорное" решение, совместимо со всеми сборками

#define MCS_GET_OBJ_ADDR(obj) mcsGetObjectAddress(0,0,0,0,0,obj)

template <class OBJECT> 
__declspec(noinline) OBJECT* __stdcall mcsGetObjectAddress(
	int a_rcx, int a_rdx, int a_r8, int a_r9, int a_s1, OBJECT& obj)
{
	// для x64 первые 4 аргумента передаются в регистрах;
	// причем должна быть обязательно не инлайновая реализация
	return (OBJECT*) (((UINT_PTR**)&a_s1)[1]);
}
*/
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

/*
// решение не совместимо с VS2005 / Release(32/64) / Link-time code generation
// неверно передаются агрументы в стек, глюк компилятора

#define MCS_GET_OBJ_ADDR(obj) mcsGetObjectAddress(0,obj)

template <class OBJECT> 
__declspec(noinline) OBJECT* __stdcall mcsGetObjectAddress(int dummy, OBJECT& obj, ...)
{
	va_list args;
	va_start(args, dummy);
	OBJECT* pObj = va_arg(args, OBJECT*);

	return pObj;
}
*/

//===========================================================================

template<class _T> 
__inline void _swap(_T& x, _T& y)
{
	if(MCS_GET_OBJ_ADDR(x) == MCS_GET_OBJ_ADDR(y))
		return;
	_T t;
	t=x;
	x=y;
	y=t;
}
//===========================================================================
template<class TYPE>
__inline void __stdcall McsConstructElements(TYPE* pElements, INT_PTR nCount)
{
	//MCSASSERTx64_EX_32bit(nCount, return);
	MCSASSERTE(nCount<0);

	if(nCount <= 0)
		return;

	MCSASSERT(IsValidRange(pElements, nCount * sizeof(TYPE)));

	//if(!_eds_fDefecateMem)
	// commented because by MFC specification arrays of simple types must be initialized with zero
	::memset((void*)pElements, 0, nCount * sizeof(TYPE));	// first do bit-wise zero initialization

	// then call the constructor(s)
	for (; nCount--; pElements++)
		::new((void*)pElements,__MNP__) TYPE;
}
//===========================================================================
template<class TYPE>
__inline void __stdcall McsDestructElements(TYPE* pElements, INT_PTR nCount)
{
	//MCSASSERTx64_EX_32bit(nCount, return);
	MCSASSERTE(nCount < 0);

	if(nCount<=0)
		return;

	MCSASSERT(IsValidRange(pElements, nCount * sizeof(TYPE)));

	// call the destructor(s)
	for (int i=0; i<(int)nCount; i++) 
	{
		try{
			pElements[i].~TYPE();
		}catch(...) {
			MCSASSERTE_EX("FATAL in McsDestructElements", break);
		}
	}

	if(_gf_Enable_DefecateMem)
		memset(pElements, FECAL_BYTE, sizeof(TYPE)*nCount);
}
//===========================================================================
template<class TYPE>
__inline void __stdcall McsCopyElements(TYPE* pDest, const TYPE* pSrc, INT_PTR nCount)
{
	//MCSASSERTx64_EX_32bit(nCount, return);
	MCSASSERTE(nCount < 0);

	if(nCount <= 0)
		return;

	MCSASSERT(IsValidRange(pDest, nCount * sizeof(TYPE)));
	MCSASSERT(IsValidRange(pSrc, nCount * sizeof(TYPE)));

	// default is element-copy using assignment
	while (nCount--)
		*pDest++ = *pSrc++;
}
//===========================================================================
template<class TYPE, class ARG_TYPE>
bool __stdcall McsCompareElements(const TYPE* pElement1, ARG_TYPE pElement2)
{
	MCSASSERT(IsValidRange(pElement1, sizeof(TYPE)));
	MCSASSERT(IsValidRange(pElement2, sizeof(ARG_TYPE)));

	int iCmpRes = *pElement1 == *pElement2;
	return 0 != iCmpRes;
}
//===========================================================================

template <> MT_API void __stdcall McsConstructElements(byte* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsDestructElements(byte* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsCopyElements(byte* pDest, const byte* pSrc, INT_PTR nCount);

template <> MT_API void __stdcall McsConstructElements(int* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsDestructElements(int* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsCopyElements(int* pDest, const int* pSrc, INT_PTR nCount);

template <> MT_API void __stdcall McsConstructElements(DWORD* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsDestructElements(DWORD* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsCopyElements(DWORD* pDest, const DWORD* pSrc, INT_PTR nCount);

template <> MT_API void __stdcall McsConstructElements(double* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsDestructElements(double* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsCopyElements(double* pDest, const double* pSrc, INT_PTR nCount);

struct mcsWorkID;
template <> MT_API void __stdcall McsDestructElements(mcsWorkID* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsCopyElements(mcsWorkID* pDest, const mcsWorkID* pSrc, INT_PTR nCount);

#ifdef WIN64

template <> MT_API void __stdcall McsConstructElements(INT_PTR* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsDestructElements(INT_PTR* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsCopyElements(INT_PTR* pDest, const INT_PTR* pSrc, INT_PTR nCount);

template <> MT_API void __stdcall McsConstructElements(UINT_PTR* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsDestructElements(UINT_PTR* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsCopyElements(UINT_PTR* pDest, const UINT_PTR* pSrc, INT_PTR nCount);

#endif

//=============================================================================

class McsStringA;
class McsStringW;

// Значения получены эмпирически для NxN запроса
template<class TYPE> __inline int _mcsarr_getOptimizeLim(TYPE*) { return 20; }

// simple types
template<> __inline int _mcsarr_getOptimizeLim(char *) { return 150; }
template<> __inline int _mcsarr_getOptimizeLim(unsigned char*) { return 150; }
template<> __inline int _mcsarr_getOptimizeLim(short*) { return 150; }
template<> __inline int _mcsarr_getOptimizeLim(unsigned short*) { return 150; }
template<> __inline int _mcsarr_getOptimizeLim(int*) { return 150; }
template<> __inline int _mcsarr_getOptimizeLim(unsigned int*) { return 150; }
template<> __inline int _mcsarr_getOptimizeLim(__int64*) { return 150; }
template<> __inline int _mcsarr_getOptimizeLim(unsigned __int64*) { return 150; }
template<> __inline int _mcsarr_getOptimizeLim(double*) { return 150; }
template<> __inline int _mcsarr_getOptimizeLim(void**) { return 150; }

template<> __inline int _mcsarr_getOptimizeLim(mcsWorkID*) { return 20; }
template<> __inline int _mcsarr_getOptimizeLim(GUID*) { return 50; }
template<> __inline int _mcsarr_getOptimizeLim(McsStringA*) { return 60; } // TODO: slow McsHashKey
template<> __inline int _mcsarr_getOptimizeLim(McsStringW*) { return 60; } // TODO: slow McsHashKey

//=============================================================================

extern "C" MT_API int mtStrCmpDigA(LPCSTR s1, LPCSTR s2);
extern "C" MT_API int mtStrCmpDigW(LPCWSTR s1, LPCWSTR s2);

extern "C" MT_API int mtStrCmpIDigA(LPCSTR s1, LPCSTR s2);
extern "C" MT_API int mtStrCmpIDigW(LPCWSTR s1, LPCWSTR s2);

#undef mtStrCmpDig
#undef mtStrCmpIDig

#ifdef _UNICODE
	#define mtStrCmpDig  mtStrCmpDigW
	#define mtStrCmpIDig mtStrCmpIDigW
#else
	#define mtStrCmpDig  mtStrCmpDigA
	#define mtStrCmpIDig mtStrCmpIDigA
#endif

//..............................................................................

struct StrDgtCmpA
{
	bool operator() (LPCSTR s1, LPCSTR s2) {
		int ires = mtStrCmpDigA(s1, s2);
		return ires < 0;
	}
};

struct StrDgtCmpW
{
	bool operator() (LPCWSTR s1, LPCWSTR s2) {
		int ires = mtStrCmpDigW(s1, s2);
		return ires < 0;
	}
};

#ifdef _UNICODE
	#define StrDgtCmp StrDgtCmpW
#else
	#define StrDgtCmp StrDgtCmpA
#endif

//=============================================================================

template<class KEY, class ARG_KEY = const KEY&>
class McsHashsetEx;

template<class KEY, class ARG_KEY = const KEY&>
class McsHashset;

/////////////////////////////////////////////////////////////////////////////
///////////////////////// McsArray<TYPE, ARG_TYPE> //////////////////////////
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
template<class TYPE, class ARG_TYPE = const TYPE&>
class McsArray
{
protected:

#ifdef _MCEYE
public:
#endif

	TYPE* m_pData;
	int m_nSize;
	int m_nMaxSize;
	int m_nGrowBy;

public:

	typedef McsHashsetEx<TYPE, ARG_TYPE> ValHashsetEx;
	typedef McsHashset<TYPE, ARG_TYPE> ValHashset;

	McsArray();
	explicit McsArray(INT_PTR iSize);
	McsArray(const McsArray&);
	McsArray(const ValHashset& set);
	McsArray(const ValHashsetEx& set);
	~McsArray();

	DECLARE_OBJ_NEWDEL;

// These are used to get back X and Y from typedefed McsArray, like this:
// typedef McsArray<X, Y> McsXYArray;
// McsXYArray::ElementType will be X and
// McsXYArray::ArgumentType will be Y
	typedef TYPE ElementType;
	typedef ARG_TYPE ArgumentType;
	typedef bool ArgsEqualProc(ARG_TYPE arg1, ARG_TYPE arg2); // should return true if 'arg1' is equal to 'arg2'

// Attributes
	int GetSize() const { return m_nSize; }
	int logicalLength() const { return m_nSize; }
	int physicalLength() const {return m_nMaxSize;}
	int Length() const { return m_nSize; }
	int length() const { return m_nSize; }
	int GetCount() const { return m_nSize; }
	int GetUpperBound() const { return m_nSize - 1; }
	bool isEmpty() const { return m_nSize == 0; }
	bool IsEmpty() const { return m_nSize == 0; }

	void SetSize(INT_PTR nNewSize, INT_PTR nGrowBy = -1);
	void IncreaseSize(INT_PTR nDelta = 1) { SetSize( max(0, m_nSize + nDelta) ); }
	void setLogicalLength(INT_PTR nNewSize) {SetSize(nNewSize);}
	void setPhysicalLength(INT_PTR nNewSize);
	McsArray& setGrowLength(INT_PTR nGrowBy) {SetSize(m_nSize, nGrowBy); return *this;}

	// гарантирует, что физический размер будет включать указанное кол-во элементов;
	// если выделенной памяти уже хватает, ничего не делает
	void reserve(INT_PTR maxPhysicalSize);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();
	void removeAll()
		{ RemoveAll(); }

	// Accessing elements
	TYPE GetAt(INT_PTR nIndex) const;
	void SetAt(INT_PTR nIndex, ARG_TYPE newElement);
	McsArray& setAt(int index, ARG_TYPE value) { SetAt(index, value); return *this; }

	TYPE&       ElementAt(INT_PTR nIndex);
	const TYPE& ElementAt(INT_PTR nIndex) const;
	const TYPE& at(int index) const { return ElementAt(index); }
	TYPE&       at(int index) { return ElementAt(index); }

	TYPE&       First();
	const TYPE& First() const;
	TYPE&       Last();
	const TYPE& Last() const;

	TYPE&       first()       { return First(); }
	const TYPE& first() const { return First(); }
  TYPE&       last()        { return Last(); }
	const TYPE& last() const  { return Last(); }

	// Direct Access to the element data (may return NULL)
	const TYPE* GetData() const;
	TYPE*       GetData();
	const TYPE* asArrayPtr() const {return GetData();}
	TYPE*       asArrayPtr() {return GetData();}

	// Potentially growing the array
	void SetAtGrow(INT_PTR nIndex, ARG_TYPE newElement);
	int  Add(ARG_TYPE newElement);

	void Append(ARG_TYPE newElement) {Add(newElement);}
	void append(ARG_TYPE newElement) {Add(newElement);}
	void Append(const McsArray& arr) {InsertAt(m_nSize, arr);}
	void append(const McsArray& arr) {InsertAt(m_nSize, arr);}
	void Append(const ValHashset& set);
	void Append(const ValHashsetEx& set);
	void Append(INT_PTR nCount, const TYPE* pArr) {InsertAt(m_nSize, nCount, (TYPE*)pArr);}

	McsArray& operator += (ARG_TYPE newElement) { Add(newElement); return *this; }
	McsArray& operator += (const McsArray& arr) { Append(arr); return *this; }
	McsArray& operator += (const ValHashset& set) { Append(set); return *this; }
	McsArray& operator += (const ValHashsetEx& set) { Append(set); return *this; }

	void Copy(const McsArray& src);
	void MoveElements(INT_PTR destIndex, INT_PTR srcIndex, INT_PTR nCount = 1);

	// overloaded operator helpers
	TYPE& operator[](int nIndex) {return ElementAt(nIndex);}
  const TYPE& operator[](int nIndex) const {return ElementAt(nIndex);}

#ifdef WIN64
	TYPE&       operator[] (INT_PTR nIndex);
	const TYPE& operator[] (INT_PTR nIndex) const;
	TYPE&       operator[] (UINT_PTR nIndex);
	const TYPE& operator[] (UINT_PTR nIndex) const;
	TYPE&       operator[] (UINT nIndex) {return ElementAt((int)nIndex);}
	const TYPE& operator[] (UINT nIndex) const {return ElementAt((int)nIndex);}
	TYPE&       operator[] (DWORD nIndex) {return ElementAt(nIndex);}
	const TYPE& operator[] (DWORD nIndex) const {return ElementAt(nIndex);}
#endif

	McsArray& operator = (const McsArray&);
	McsArray& operator = (const ValHashset&);
	McsArray& operator = (const ValHashsetEx&);
	bool operator == (const McsArray&) const;
	bool operator != (const McsArray&) const;

	// Allow adding elements to array by using << operator:
	// Example: McsArray<int, int>() << 1 << 4 << -20;
	McsArray& operator<<(ARG_TYPE arg);

	// Operations that move elements around
	void InsertAt(INT_PTR nIndex, ARG_TYPE newElement, INT_PTR nCount = 1);
	void insertAt(INT_PTR nIndex, ARG_TYPE newElement, INT_PTR nCount = 1) {InsertAt(nIndex, newElement, nCount);}
	void InsertAt(INT_PTR nIdxTo, const McsArray& ArrayFrom);
	void InsertAt(INT_PTR nIdxTo, const McsArray& ArrayFrom, INT_PTR nIdxFrom, INT_PTR nCount);
	void InsertAt(INT_PTR nIdxTo, INT_PTR nCount, const TYPE* pArr);

	void RemoveAt(INT_PTR nIndex, INT_PTR nCount = 1);
	void removeAt(INT_PTR nIndex, INT_PTR nCount = 1) {RemoveAt(nIndex, nCount);}
	void RemoveLast();
	void removeLast() {RemoveLast();}
	McsArray&  removeFirst()
		{ RemoveAt(0); return *this; }

	// MechaniCS extensions
	// sort array using operators "<" and ">" of TYPE
	void QuickSort(bool bAscent = true, INT_PTR iFrom = 0, INT_PTR nItemsToSort = 0);

	// sort array using comparator cmp
	// bool CMP::operator()(const TYPE& arg1, const TYPE& arg2) should return true if arg1 < arg2
	template<class CMP>
	void QuickSortCmp(CMP& cmp, bool bAscent = true, INT_PTR iFrom = 0, INT_PTR nItemsToSort = 0);

	void QuickSortStringsDgtA(bool bAscent = true, INT_PTR iFrom = 0, INT_PTR nItemsToSort = 0);
	void QuickSortStringsDgtW(bool bAscent = true, INT_PTR iFrom = 0, INT_PTR nItemsToSort = 0);
	void QuickSortStringsDgt(bool bAscent = true, INT_PTR iFrom = 0, INT_PTR nItemsToSort = 0);

	int  BinarySearch(ARG_TYPE value,bool bSortedAscent = true) const; // uses std bin search alg, ret <0 if failed; be sure that array wos sorted before
	bool find(ARG_TYPE value, int& foundAt, INT_PTR start = 0, ArgsEqualProc* pComparator = NULL) const;
	int  indexOf(ARG_TYPE value, ArgsEqualProc* pComparator = NULL) const;

	bool contains(ARG_TYPE value, ArgsEqualProc* pComparator = NULL) const;
	bool contains(const McsArray& values, ArgsEqualProc* pComparator = NULL) const; // (!) SLOW
	bool contains(const ValHashset& set) const;
	bool contains(const ValHashsetEx& set) const;
	bool containsAnyOf(const McsArray& values, ArgsEqualProc* pComparator = NULL) const;
	bool containsAnyOf(const ValHashset& set) const;
	bool containsAnyOf(const ValHashsetEx& set) const;

	bool remove(ARG_TYPE item_value, INT_PTR start = 0, ArgsEqualProc* pComparator = NULL);
	McsArray& swap(INT_PTR Item_1_Index, INT_PTR Item_2_Index);
	McsArray& reverse();
	bool AddDistinct(ARG_TYPE newElement, ArgsEqualProc* pComparator = NULL);
	bool AddDistinct(const McsArray& arr, ArgsEqualProc* pComparator = NULL); // (!) SLOW
	bool Replace(ARG_TYPE what, ARG_TYPE by, ArgsEqualProc* pComparator = NULL);

	void getAsHashset(OUT ValHashsetEx& set) const { set = *this; }
	void getAsHashset(OUT ValHashset& set) const { set = *this; }

	// removes elements, which don't exist in ArrayWith
	void Intersect(const McsArray& ArrayWith, ArgsEqualProc* pComparator = NULL); // (!) SLOW
	void Intersect(const ValHashset& set);
	void Intersect(const ValHashsetEx& set);
	McsArray& operator &= (const McsArray& ArrayWith) { Intersect(ArrayWith); return *this; }
	McsArray& operator &= (const ValHashset& set) { Intersect(set); return *this; }
	McsArray& operator &= (const ValHashsetEx& set) { Intersect(set); return *this; }

	// removes elements, which exist in ArraySubtrahend
	void Subtract(const McsArray& ArraySubtrahend, ArgsEqualProc* pComparator = NULL); // (!) SLOW
	void Subtract(const ValHashset& set);
	void Subtract(const ValHashsetEx& set);
	McsArray& operator -= (const McsArray& ArraySubtrahend) { Subtract(ArraySubtrahend); return *this; }
	McsArray& operator -= (const ValHashset& set) { Subtract(set); return *this; }
	McsArray& operator -= (const ValHashsetEx& set) { Subtract(set); return *this; }

	// applies a functor or a function to each element of the array
	// like this: bool func(element);
	// NOTE: a returning value from a 'func' determines whether to continue iterations or to stop them

	template<class FUNC>
	void ForEach(FUNC& func);

	template<class FUNC>
	void ForEach(FUNC& func) const;

	// causes all data in array to jump in memory to new location
	void _dbg_jump();

protected:
	int _getOptimizeLim() const;
};

//==============================================================================
// non-member McsArray functions

// Clears result and than adds to result only those elements,
// which exists in both arr1 and arr2.
template<class TYPE, class ARG_TYPE>
void IntersectArrays
(McsArray<TYPE, ARG_TYPE>&       result,
 const McsArray<TYPE, ARG_TYPE>& arr1,
 const McsArray<TYPE, ARG_TYPE>& arr2)
{
	result.RemoveAll();
	int iCount = arr1.GetCount();
	for(int i = 0; i < iCount; i++) {
		TYPE el = arr1[i];
		if (arr2.contains(el))
			result.Add(el);
	}
}

//==============================================================================

//#define MCGEL
//#define DDGEL
//#define NOACGE

#ifndef NOACGE

	class AcGePoint3d;
	#ifndef mcsPoint
		#define mcsPoint AcGePoint3d
	#endif

	class AcGeVector3d;
	#ifndef mcsVector
		#define mcsVector AcGeVector3d
	#endif

	class AcGeLineSeg3d;
	#ifndef mcsLineSeg
		#define mcsLineSeg AcGeLineSeg3d
	#endif

#elif defined(MCGEL)

	class McGePoint3d;
	#ifndef mcsPoint
		#define mcsPoint McGePoint3d
	#endif

	class McGeVector3d;
	#ifndef mcsVector
		#define mcsVector McGeVector3d
	#endif

	class McGeLineSeg3d;
	#ifndef mcsLineSeg
		#define mcsLineSeg McGeLineSeg3d
	#endif

#elif defined(DDGEL)

	class OdGePoint3d;
	#ifndef mcsPoint
		#define mcsPoint OdGePoint3d
	#endif

	class OdGeVector3d;
	#ifndef mcsVector
		#define mcsVector OdGeVector3d
	#endif

	class OdGeLineSeg3d;
	#ifndef mcsLineSeg
		#define mcsLineSeg OdGeLineSeg3d
	#endif

#endif


class mcsPline3d;
#ifndef mcsPolyline
  #define mcsPolyline mcsPline3d
#endif

typedef McsArray<void*, void*>                  mcsPVoidArray;

// 8-bit std arrays
typedef McsArray <char, char>                   mcsCharArray;
typedef McsArray <byte, byte>                   mcsByteArray;
typedef McsArray <bool, bool>                   mcsBoolArray;

// 16 bit std arrays
typedef McsArray <short, short>                 mcsShortArray;
typedef McsArray <unsigned, unsigned>           mcsUnsignedArray;
typedef McsArray <WCHAR, WCHAR>                 mcsWCharArray;

// 32 bit std arrays 
typedef McsArray <int, int>                     mcsIntArray;
typedef McsArray <INT_PTR, INT_PTR>             mcsIntPtrArray;
typedef McsArray <UINT_PTR, UINT_PTR>           mcsUIntPtrArray;
typedef McsArray <unsigned long, unsigned long> mcsDwordArray;

// 64 bit std arrays
typedef McsArray <__int64, __int64>             mcsI64Array;
typedef McsArray <unsigned __int64, unsigned __int64> mcsUI64Array;

// float-point arrays
typedef McsArray <double, double>               mcsDoubleArray;

// Используйте следующие макросы, чтобы работать со значениями McGSMarker
// в коде, относящимся к 3D:

enum McModSubentType;
#define MCMOD_GSM_2_SETYPE(gsm)      ((McModSubentType)((gsm)&3))
// index is implied to be 1-based
#define MCMOD_GSM_2_IDX(gsm)         (((gsm)>>2))
#define MCMOD_IDX_2_GSM(seType, idx) (((idx))<<2 | ((seType)&3))

typedef INT_PTR McGSMarker;
typedef McsArray<McGSMarker, McGSMarker> mcsMcGsMarkerArray;

typedef McsArray <GUID>                         mcsGUIDArray;

struct MCSVariant;
class McsStringA;
class McsStringW;
#ifndef McsString
	#ifndef _UNICODE
	#define McsString McsStringA
	#else
	#define McsString McsStringW
	#endif
#endif

union MCSUID
{
	double  dbl;
	__int64 i64;

	MCSUID() { i64 = 0; }
	MCSUID(double _dbl) {dbl = _dbl;}
	MCSUID(int iVal) {dbl = iVal;} // int as double
	MCSUID(__int64 _i64) {i64 = _i64;}
	MCSUID(const MCSUID& uid) {i64 = uid.i64;}
	MCSUID(const MCSVariant&);
	MCSUID(LPCTSTR pszUID) { SetStringUID(pszUID); }

	MCSUID& operator = (int iVal) {dbl = iVal; return *this;} // int as double
	MCSUID& operator = (double _dbl) {dbl = _dbl; return *this;}
	MCSUID& operator = (__int64 _i64) {i64 = _i64; return *this;}
	MCSUID& operator = (const MCSUID& uid) {i64 = uid.i64; return *this;}
	MCSUID& operator = (const MCSVariant&);

	bool operator == (int iVal) const {return dbl == iVal;} // int as double
	bool operator == (double _dbl) const {return dbl == _dbl;}
	bool operator == (__int64 _i64) const {return i64 == _i64;}
	bool operator == (const MCSUID& uid) const {return i64 == uid.i64;}

	bool operator != (int iVal) const {return dbl != iVal;} // int as double
	bool operator != (double _dbl) const {return dbl != _dbl;}
	bool operator != (__int64 _i64) const {return i64 != _i64;}
	bool operator != (const MCSUID& uid) const {return i64 != uid.i64;}

	bool operator <= (double d) const {return dbl <= d;}
	bool operator < (double d) const {return dbl < d;}
	bool operator >= (double d) const {return dbl >= d;}
	bool operator > (double d) const {return dbl > d;}

	// int as double
	bool operator <= (int i) const {return dbl <= i;}
	bool operator < (int i) const {return dbl < i;}
	bool operator >= (int i) const {return dbl >= i;}
	bool operator > (int i) const {return dbl > i;}

	bool operator <= (__int64 i) const {return i64 <= i;}
	bool operator < (__int64 i) const {return i64 < i;}
	bool operator >= (__int64 i) const {return i64 >= i;}
	bool operator > (__int64 i) const {return i64 > i;}

	//operator double () const { return dbl; }
	//operator __int64() const { return i64; }
	operator const double&  () const { return dbl; }
	operator const __int64& () const { return i64; }
	operator double&  () { return dbl; }
	operator __int64& () { return i64; }
	operator LPARAM () const { return (LPARAM)dbl; }
	operator DWORD_PTR () const { return (DWORD_PTR)dbl; }

	operator bool () {return 0 != i64;}
	operator bool () const {return 0 != i64;}
	bool operator ! () const {return 0 == i64;}

	// String
	bool SetStringUID(LPCTSTR pszUID)
	{
		i64 = 0;
		if (pszUID != NULL)
#if _MSC_VER >= 1400
			_stscanf_s(pszUID, _T("%I64X"), &i64);
#else
			_stscanf(pszUID, _T("%I64X"), &i64);
#endif
		return (i64 != 0);
	}
	bool SafeSetStringUID(LPCTSTR pszUID)
	{
		if(!pszUID || _tcslen(pszUID) != 16)
			return false;
		for(int a = 0; a < 16; a++)
		{
			if(!(pszUID[a] >= '0' && pszUID[a] <= '9' || pszUID[a] >= 'A' && pszUID[a] <= 'F' || pszUID[a] >= 'a' && pszUID[a] <= 'f'))
				return false;
		}
		return SetStringUID(pszUID);
	}

	McsString GetAsString() const;

	// Форматирование в строку с учетом спец. значений
	MCTYP_API McsString getDbgString() const;
};

__inline bool operator == (double d, const MCSUID& uid) {
	return d == uid.dbl;
}

__inline bool operator != (double d, const MCSUID& uid) {
	return d != uid.dbl;
}

__inline bool operator == (int i, const MCSUID& uid) {
	return i == uid.dbl;
}

__inline bool operator != (int i, const MCSUID& uid) {
	return i != uid.dbl;
}

__inline bool operator == (__int64 i, const MCSUID& uid) {
	return i == uid.i64;
}

__inline bool operator != (__int64 i, const MCSUID& uid) {
	return i != uid.i64;
}

typedef McsArray <MCSUID, MCSUID>               mcsMCSUIDArray;

struct McContextMenuItem;
typedef McsArray <McContextMenuItem>            mcsCtxMenuItemArray;

enum MCS_LangId;
typedef McsArray<MCS_LangId, MCS_LangId>        mcsLangIdArray;

struct mcsWorkID;
struct mcsWorkIDArray;
struct mcsWId2WIdMap;
typedef McsArray <mcsWorkIDArray>               mcsWorkIDArrays;

// string arrays/maps
class McsString;

class McsStringA;
class McsStringW;

typedef McsArray<McsStringA, LPCSTR> mcsStringArrayA;
typedef McsArray<McsStringW, LPCWSTR> mcsStringArrayW;

/////////////////////////////////////////////////////////////////////////////
// McsArray<TYPE, ARG_TYPE> inline functions

//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline void McsArray<TYPE, ARG_TYPE>::RemoveAll()
{
	SetSize(0, -1);
	FreeExtra();
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline TYPE McsArray<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex) const 
{ 
	MCSASSERTx64_EX_32bit(nIndex, MCSTEMPL_INVADDR_AS_TYPE(TYPE));
	MCSASSERT_EX(nIndex >= 0 && nIndex < m_nSize, return MCSTEMPL_INVADDR_AS_TYPE(TYPE));
	return m_pData[nIndex]; 
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline void McsArray<TYPE, ARG_TYPE>::SetAt(INT_PTR nIndex, ARG_TYPE newElement) 
{
	MCSASSERTx64_EX_32bit(nIndex, return);
	MCSASSERT_EX(nIndex >= 0 && nIndex < m_nSize, return);
	if((UINT_PTR)MCS_GET_OBJ_ADDR(newElement) == (UINT_PTR)(m_pData+nIndex))
		return; // self-copying
	m_pData[nIndex] = newElement; 
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline TYPE& McsArray<TYPE, ARG_TYPE>::ElementAt(INT_PTR nIndex) 
{
	MCSASSERTx64_EX_32bit(nIndex, MCSTEMPL_INVADDR_AS_TYPE(TYPE));
	MCSASSERT_EX(nIndex >= 0 && nIndex < m_nSize, return MCSTEMPL_INVADDR_AS_TYPEREF(TYPE));
	return m_pData[nIndex]; 
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline const TYPE& McsArray<TYPE, ARG_TYPE>::ElementAt(INT_PTR nIndex) const
{
	MCSASSERTx64_EX_32bit(nIndex, MCSTEMPL_INVADDR_AS_TYPE(TYPE));
	MCSASSERT_EX(nIndex >= 0 && nIndex < m_nSize, return MCSTEMPL_INVADDR_AS_TYPEREF(TYPE));
	return m_pData[nIndex]; 
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline const TYPE* McsArray<TYPE, ARG_TYPE>::GetData() const
	{ return (const TYPE*)m_pData; }
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline TYPE* McsArray<TYPE, ARG_TYPE>::GetData()
	{ return m_pData; }
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline int McsArray<TYPE, ARG_TYPE>::Add(ARG_TYPE newElement) { 
	int nIndex = m_nSize;
	SetAtGrow(nIndex, newElement);
	return nIndex; 
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline void McsArray<TYPE, ARG_TYPE>::Append(const ValHashset& set)
{
	MCSPOSITION pos = set.GetStartPosition();
	const TYPE* pK = NULL;
	int idx = m_nSize;
	int n = set.GetSize();
	SetSize(m_nSize + n);
	while(pos) {
		set.GetNextKey(pos, pK);
		m_pData[idx++] = *pK;
	}
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline void McsArray<TYPE, ARG_TYPE>::Append(const ValHashsetEx& set)
{
	int iFrom = m_nSize;
	int n = set.GetSize();
	SetSize(m_nSize + n);
	for(mapidx mi=set.FirstIdx(); mi<n; ++mi) {
		m_pData[iFrom + mi.iLogical] = set[mi];
	}
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
__inline bool McsArray<TYPE, ARG_TYPE>::AddDistinct(ARG_TYPE newElement, ArgsEqualProc* pComparator)
{
	if(m_pData){
		UINT_PTR addrArg = (UINT_PTR)MCS_GET_OBJ_ADDR(newElement);
		if(addrArg >= (UINT_PTR)m_pData && addrArg<(UINT_PTR)(m_pData+m_nSize))
			return false; // element is from <this> array
	}
	if(NULL==m_pData || !contains(newElement, pComparator)){
		Add(newElement);
		return true;
	}
	return false;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
__inline bool McsArray<TYPE, ARG_TYPE>::AddDistinct(const McsArray& arr, ArgsEqualProc* pComparator)
{
	if(&arr == this) 
		return false; // self-adding

	//int lim = _mcsarr_getOptimizeLim((TYPE*)NULL);
	int i, nE = arr.GetSize();

	bool bres = false;
	/*
	if(m_nSize > lim && nE > lim)
	{
		// convert this to hashset
		MESSAGE_WARN_NOCP_A("McsArray::AddDistinct(McsArray), Use McsHashsetEx to optimize operation");
		ValHashsetEx thisSet(*this);

		for(i=0; i<nE; i++)
		{
			const TYPE& item = arr.GetData()[i];
			if(thisSet.contains(item, pComparator))
				continue;
			thisSet |= item;
			Add(item);
			bres = true;
		}
	}
	else
	*/
	{
		for(i=0; i<nE; i++) {
			bres |= AddDistinct(arr.GetData()[i], pComparator);
		}
	}
	return bres;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
__inline bool McsArray<TYPE, ARG_TYPE>::Replace(ARG_TYPE what, ARG_TYPE by, ArgsEqualProc* pComparator) 
{
	if((UINT_PTR)MCS_GET_OBJ_ADDR(what) == (UINT_PTR)MCS_GET_OBJ_ADDR(by))
		return false; // null-effect replacement

	int idx = -1;
	if(!find(what, idx, 0, pComparator)) 
		return false;
	ElementAt(idx) = by;
	return true;
}
//...........................................................................

#ifdef WIN64
template<class TYPE, class ARG_TYPE>
__inline TYPE& McsArray<TYPE, ARG_TYPE>::operator[](INT_PTR nIndex)
	{ return ElementAt(nIndex); }
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline const TYPE& McsArray<TYPE, ARG_TYPE>::operator[](INT_PTR nIndex) const
	{ return ElementAt(nIndex); }
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline TYPE& McsArray<TYPE, ARG_TYPE>::operator[](UINT_PTR nIndex)
	{ return ElementAt((INT_PTR)nIndex); }
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline const TYPE& McsArray<TYPE, ARG_TYPE>::operator[](UINT_PTR nIndex) const
	{ return ElementAt((INT_PTR)nIndex); }
#endif
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline TYPE& McsArray<TYPE, ARG_TYPE>::First()
{
	MCSASSERTE_EX(m_nSize<=0, return MCSTEMPL_INVADDR_AS_TYPEREF(TYPE));
	return m_pData[0];
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline const TYPE& McsArray<TYPE, ARG_TYPE>::First() const
{
	MCSASSERTE_EX(m_nSize<=0, return MCSTEMPL_INVADDR_AS_TYPEREF(TYPE));
	return m_pData[0];
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline TYPE& McsArray<TYPE, ARG_TYPE>::Last()
{
	MCSASSERTE_EX(m_nSize<=0, return MCSTEMPL_INVADDR_AS_TYPEREF(TYPE));
	return m_pData[m_nSize-1];
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
__inline const TYPE& McsArray<TYPE, ARG_TYPE>::Last() const
{
	MCSASSERTE_EX(m_nSize<=0, return MCSTEMPL_INVADDR_AS_TYPEREF(TYPE));
	return m_pData[m_nSize-1];
}
/////////////////////////////////////////////////////////////////////////////
// McsArray: non inline functions

template<class TYPE, class ARG_TYPE>
McsArray<TYPE, ARG_TYPE>::McsArray()
{
	m_pData = NULL;
	m_nSize = 0;
	m_nMaxSize = 0;
	m_nGrowBy = 0;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
McsArray<TYPE, ARG_TYPE>::McsArray(INT_PTR iSize)
{
	m_pData = NULL;
	m_nSize = 0;
	m_nMaxSize = 0;
	m_nGrowBy = 0;

	SetSize(iSize);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
McsArray<TYPE, ARG_TYPE>::McsArray(const McsArray& cf)
{
	m_pData = NULL;
	m_nSize = 0;
	m_nMaxSize = 0;
	m_nGrowBy = 0;

	*this=cf;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
McsArray<TYPE, ARG_TYPE>::McsArray(const ValHashset& set)
{
	m_pData = NULL;
	m_nSize = 0;
	m_nMaxSize = 0;
	m_nGrowBy = 0;

	*this = set;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
McsArray<TYPE, ARG_TYPE>::McsArray(const ValHashsetEx& set)
{
	m_pData = NULL;
	m_nSize = 0;
	m_nMaxSize = 0;
	m_nGrowBy = 0;

	*this = set;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
McsArray<TYPE, ARG_TYPE>::~McsArray()
{
	if(m_pData)
	{
		McsDestructElements<TYPE>(m_pData, m_nSize);
		mcsMemFree(m_pData);
		m_pData = NULL;
		m_nSize = 0;
		m_nMaxSize = 0;
		m_nGrowBy = 0;
	}
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE,ARG_TYPE>::operator == (const McsArray<TYPE,ARG_TYPE>& cw) const
{
	if(this == &cw) return true; // self comparison
	if(m_nSize != cw.m_nSize) return false;
	for(int i=0; i<m_nSize; i++) {
		if(m_pData[i] != cw.m_pData[i]) 
			return false;
	}
	return true;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE,ARG_TYPE>::operator != (const McsArray<TYPE,ARG_TYPE>& cw) const
{
	return !(*this == cw);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
McsArray<TYPE,ARG_TYPE>& McsArray<TYPE,ARG_TYPE>::operator = (const McsArray<TYPE,ARG_TYPE>& cf)
{
	if(this == &cf)
		return *this;

	// 17.11.2015, AGL, optimization: avoid extra reallocations of memory
	//this->setPhysicalLength(cf.m_nMaxSize);
	this->SetSize(cf.m_nSize);
	this->m_nGrowBy = cf.m_nGrowBy;
	
	McsCopyElements(m_pData, cf.m_pData, m_nSize);

	return *this;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
McsArray<TYPE,ARG_TYPE>& McsArray<TYPE,ARG_TYPE>::operator = (const ValHashset& set)
{
	int n = set.GetSize();
	SetSize(set.GetSize());

	MCSPOSITION pos = set.GetStartPosition();
	int idx = 0;
	while(pos) {
		set.GetNextKey(pos, m_pData[idx++]);
	}

	return *this;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
McsArray<TYPE,ARG_TYPE>& McsArray<TYPE,ARG_TYPE>::operator = (const ValHashsetEx& set)
{
	int n = set.GetSize();
	SetSize(n);

	for(mapidx mi = set.FirstIdx(); mi < n; ++mi) {
		m_pData[mi.iLogical] = set[mi];
	}

	return *this;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::reserve(INT_PTR maxPhysicalSize)
{
	if(m_nMaxSize >= maxPhysicalSize)
		return;
	setPhysicalLength(maxPhysicalSize);
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::setPhysicalLength(INT_PTR nNewMaxSize)
{
	MCSASSERTx64_EX_32bit(nNewMaxSize, return);
	if(nNewMaxSize == m_nMaxSize)
		return;

	int newLogicalSize = m_nSize;
	int nEToDestroy = m_nSize - (int)nNewMaxSize;
	if(nEToDestroy>0) {
		// размер уменьшается, + есть элементы, для которых нуно позвать деструктор
		McsDestructElements(m_pData + m_nSize - nEToDestroy, nEToDestroy);
		newLogicalSize = (int)nNewMaxSize;
	}
	m_pData = (TYPE*)mcsMemReAlloc(m_pData, nNewMaxSize*sizeof(*m_pData));
	m_nSize = newLogicalSize;
	m_nMaxSize = (int)nNewMaxSize;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::_dbg_jump()
{
	MCSASSERT_EX(m_nMaxSize>=m_nSize, return);
	if(!m_nSize)
		return;

	TYPE* newPtr = (TYPE*)mcsMemAlloc(m_nMaxSize * sizeof(TYPE));
	CHECK_OUT_OF_MEM(!newPtr && m_nMaxSize);
	if(_gf_Enable_DefecateMem)
		memset(newPtr, FECAL_BYTE, m_nMaxSize * sizeof(TYPE));

	McsConstructElements<TYPE>(newPtr, m_nSize);
	McsCopyElements<TYPE>(newPtr, m_pData, m_nSize);
	McsDestructElements<TYPE>(m_pData, m_nSize);
	mcsMemFree(m_pData);
	m_pData = newPtr;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::SetSize(INT_PTR nNewSize, INT_PTR nGrowBy)
{
	MCSASSERTx64_EX_32bit(nNewSize, return);
	MCSASSERTx64_EX_32bit(nGrowBy, return);

	MCSASSERT_EX(nNewSize >= 0, return);

	if (nGrowBy != -1)
		m_nGrowBy = (int)nGrowBy;  // set new size

	if(_gf_Enable_JumpArrOnAdd && nNewSize>m_nMaxSize)
		_dbg_jump();

	if (nNewSize == 0)
	{
		// shrink to nothing
		if (m_pData) {
			McsDestructElements<TYPE>(m_pData, m_nSize);

			// AGL, 30.05.13, по смыслу установка размера не означает очистку памяти,
			// т.к. для этого есть спец методы FreeExtra и RemoveAll

			//mcsMemFree(m_pData);
			//m_pData = NULL;
			//m_nMaxSize = 0;
		}
		m_nSize = 0;
	}
	else if (m_pData == NULL)
	{
		int newMaxSize = (int)nNewSize;
		if(newMaxSize<m_nGrowBy)
			newMaxSize = m_nGrowBy;
		TYPE* ptr = (TYPE*)mcsMemAlloc(newMaxSize * sizeof(TYPE));
		CHECK_OUT_OF_MEM(!ptr && newMaxSize);
		if(_gf_Enable_DefecateMem)
			memset(ptr, FECAL_BYTE, newMaxSize * sizeof(TYPE));
		m_pData = ptr;
		McsConstructElements<TYPE>(m_pData, (int)nNewSize);
		m_nSize = (int)nNewSize;
		m_nMaxSize = (int)newMaxSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements
			McsConstructElements<TYPE>(m_pData+m_nSize, (int)(nNewSize-m_nSize));
		}
		else if (m_nSize > nNewSize)
		{
			// destroy the old elements
			McsDestructElements<TYPE>(m_pData+nNewSize, (int)(m_nSize-nNewSize));
		}
		m_nSize = (int)nNewSize;
	}
	else
	{
		// otherwise, grow array
		int nGrowBy = m_nGrowBy;
		if (nGrowBy == 0)
		{
			// heuristically determine growth when nGrowBy == 0
			//  (this avoids heap fragmentation in many situations)

			int nItemSize = sizeof(TYPE);
			int nMaxGrowBy = 0x100000/nItemSize;
			if(nMaxGrowBy < 10)
				nMaxGrowBy = 10;
			nGrowBy = m_nSize / 2;
			if(nGrowBy < 10)
				nGrowBy = 10;
			nGrowBy = min(nGrowBy, nMaxGrowBy);
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowBy)
			nNewMax = m_nMaxSize + nGrowBy;  // granularity
		else
			nNewMax = (int)nNewSize;  // no slush

		MCSASSERT_EX(nNewMax >= m_nMaxSize, return);  // no wrap around
		TYPE* ptr = (TYPE*)mcsMemReAlloc(m_pData, nNewMax * sizeof(TYPE));
		CHECK_OUT_OF_MEM(!m_pData && nNewMax);
		if(_gf_Enable_DefecateMem)
			memset(ptr+m_nSize, FECAL_BYTE, (nNewMax-m_nSize) * sizeof(TYPE));
		m_pData = ptr;

		// construct remaining elements
		MCSASSERT_EX(nNewSize > m_nSize, return);
		McsConstructElements<TYPE>(m_pData+m_nSize, (int)(nNewSize-m_nSize));

		// get rid of old stuff (note: no destructors called)
		m_nSize = (int)nNewSize;
		m_nMaxSize = (int)nNewMax;
	}
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::Copy(const McsArray& src)
{
	if(this == &src) return; // copy to itself

	SetSize(src.m_nSize);
	McsCopyElements<TYPE>(m_pData, src.m_pData, src.m_nSize);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::FreeExtra()
{
	if (m_nSize != m_nMaxSize)
	{
		TYPE* ptr = (TYPE*)mcsMemReAlloc(m_pData,m_nSize * sizeof(TYPE));
		CHECK_OUT_OF_MEM(!ptr && m_nSize);
		m_pData = ptr;
		m_nMaxSize = m_nSize;
	}
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::SetAtGrow(INT_PTR nIndex, ARG_TYPE newElement)
{
	MCSASSERTx64_EX_32bit(nIndex, return);
	MCSASSERT_EX(nIndex >= 0, return);

	if(m_pData && m_nSize)
	{
		if (nIndex >= m_nSize)
		{
			UINT_PTR argAddr = (UINT_PTR)MCS_GET_OBJ_ADDR(newElement);
			if(argAddr >= (UINT_PTR)m_pData && 
				 argAddr < (UINT_PTR)(m_pData+m_nSize)){
				MESSAGE_WARN_A("McsArray::SetAtGrow --- Self-insert, can cause problems !")
				TYPE copy = newElement;
				SetSize(nIndex+1, -1);
				m_pData[nIndex] = copy;
				return;
			}
		}
	}

	if (nIndex >= m_nSize)
		SetSize(nIndex+1, -1);
	m_pData[nIndex] = newElement;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::RemoveAt(INT_PTR nIndex, INT_PTR nCount)
{
	MCSASSERTx64_EX_32bit(nIndex, return);
	MCSASSERTx64_EX_32bit(nCount, return);

	if(nCount == 0)
		return;

	MCSASSERT_EX(nIndex >= 0, return);
	MCSASSERT_EX(nCount > 0, return);
	MCSASSERT_EX(nIndex + nCount <= m_nSize, return);

	if(_gf_Enable_JumpArrOnRemove)
		_dbg_jump();

	// just remove a range
	int nMoveCount = m_nSize - ((int)nIndex + (int)nCount);
	McsDestructElements<TYPE>(m_pData+nIndex, (int)nCount);
	if (nMoveCount)
		::memmove(m_pData+nIndex, m_pData+nIndex + nCount, nMoveCount * sizeof(TYPE));
	m_nSize -= (int)nCount;
}

//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::RemoveLast()
{
	MCSASSERT_EX(m_nSize > 0, return);

	// just remove a range
	McsDestructElements<TYPE>(m_pData+m_nSize-1,1);
	m_nSize --;

	if(_gf_Enable_JumpArrOnRemove)
		_dbg_jump();
}

//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::InsertAt
(INT_PTR nIndex, ARG_TYPE newElement, INT_PTR nCount)
{
	MCSASSERTx64_EX_32bit(nIndex, return);
	MCSASSERTx64_EX_32bit(nCount, return);

	if(nCount == 0)
		return;

	MCSASSERT_EX(nIndex >= 0, return);    // will expand to meet need
	MCSASSERT_EX(nCount > 0, return);    // zero or negative size not allowed

	bool fInvalidSelfInserting = false;
	if(m_pData)
	{
		UINT_PTR argAddr = (UINT_PTR)MCS_GET_OBJ_ADDR(newElement);
		bool fElementIsInThisArray = argAddr >= (UINT_PTR)m_pData && argAddr < (UINT_PTR)(m_pData + m_nSize);
		if(fElementIsInThisArray)
		{
			// элемент находится в этом же массиве
			bool fReallocNeeded  = m_nSize + nCount>m_nMaxSize; // будет ли зваться realloc
			bool fSelfShit = (UINT_PTR)m_pData + nIndex <= argAddr; // будет сделан предварительный сдвиг элементов, аргумент станет невалидным
			fInvalidSelfInserting = fReallocNeeded || fSelfShit;
			if(fInvalidSelfInserting)
				MESSAGE_WARN_A("McsArray::InsertAt --- Self-insert, can cause problems !")
		}
	}

	TYPE* pNE = NULL;
	if(fInvalidSelfInserting) {
		// need to store argument
		pNE = (TYPE*)_alloca(sizeof(TYPE));
		MCSASSERTE_EX(!pNE, return);
		McsConstructElements(pNE, 1);
		*pNE = newElement;
	}

	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount, -1);   // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount, -1);  // grow it to new size
		// destroy initial data before copying over it
		McsDestructElements<TYPE>(m_pData+nOldSize, (int)nCount);
		// shift old data up to fill gap
		::memmove(m_pData+nIndex+nCount, m_pData+nIndex, (nOldSize-nIndex) * sizeof(TYPE));

		// re-init slots we copied from
		McsConstructElements<TYPE>(m_pData+nIndex, (int)nCount);
	}

	// insert new value in the gap
	MCSASSERT_EX(nIndex + nCount <= m_nSize, return);
	while (nCount--)
		m_pData[nIndex++] = fInvalidSelfInserting ? *pNE : newElement;

	if(fInvalidSelfInserting) {
		McsDestructElements(pNE, 1);
		pNE=NULL;
	}
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::InsertAt(INT_PTR nIdxTo, const McsArray<TYPE,ARG_TYPE>& ArrFrom)
{
	InsertAt(nIdxTo,ArrFrom,0,ArrFrom.GetSize());
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::InsertAt
(INT_PTR nIdxTo, const McsArray<TYPE,ARG_TYPE>& ArrayFrom, INT_PTR nIdxFrom, INT_PTR nCount)
{
	MCSASSERTx64_EX_32bit(nIdxTo, return);
	MCSASSERTx64_EX_32bit(nIdxFrom, return);
	MCSASSERTx64_EX_32bit(nCount, return);

	if(nCount == 0)
		return;

	MCSASSERT_EX(nIdxTo >= 0 && nCount > 0, return);
	MCSASSERTE_EX(IsInvalidPtr(&ArrayFrom), return);
	MCSASSERTE_EX(nIdxFrom<0 || nIdxFrom+nCount > ArrayFrom.GetSize(), return);

	if(m_pData)
	{
		if(this == &ArrayFrom) {
			MESSAGE_WARN_A("McsArray::InsertAt --- Self-insert, can cause problems !")
			McsArray tmpArr; tmpArr.Append(nCount, ArrayFrom.m_pData+nIdxFrom);
			InsertAt(nIdxTo, tmpArr, 0, nCount);
			return;
		}
	}

	// expand size of array
	int nOldSize = m_nSize;
	SetSize(m_nSize + nCount, -1);  // grow it to new size
	McsDestructElements<TYPE>(m_pData+nOldSize, nCount);
	::memmove(m_pData+nIdxTo+nCount, m_pData+nIdxTo, (nOldSize-nIdxTo) * sizeof(TYPE));
	McsConstructElements<TYPE>(m_pData+nIdxTo, nCount);

	for (int i = (int)nIdxFrom+(int)nCount-1; i>=(int)nIdxFrom ; i--)
		m_pData[nIdxTo + i-nIdxFrom] = ArrayFrom[i];
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::InsertAt(INT_PTR nIdxTo, INT_PTR nCount, const TYPE* pArr)
{
	MCSASSERTx64_EX_32bit(nIdxTo, return);
	MCSASSERTx64_EX_32bit(nCount, return);

	if(nCount == 0)
		return;

	MCSASSERT_EX(nIdxTo >= 0 && nCount > 0 && nIdxTo<=m_nSize, return);
	MCSASSERTE_EX(IsInvalidPtr(pArr), return);

	if(m_pData)
	{
		bool fSelfInsert = pArr < m_pData+m_nSize && pArr+nCount > m_pData;
		if(fSelfInsert)
		{
			// вставка части этого зе массива по неявному указанию - проверим выход за границы диапазона
			INT_PTR selfIdxFrom = ((UINT_PTR)pArr - (UINT_PTR)m_pData)/sizeof(*m_pData);
			MCSASSERTE_EX(selfIdxFrom + nCount > m_nSize, return);

			bool fNeedRealloc = m_nSize + nCount > m_nMaxSize;
			bool fSelfShift = pArr+nCount > m_pData + nIdxTo;
			if(fNeedRealloc || fSelfShift) {
				MESSAGE_WARN_A("McsArray::InsertAt --- Self-append, can cause problems !");
				McsArray tmpArr; tmpArr.Append(nCount, pArr);
				InsertAt(nIdxTo, nCount, tmpArr.GetData());
				return;
			}
		}
	}

	if (nIdxTo >= m_nSize)
	{
		SetSize(nIdxTo + nCount, -1);   // grow so nIdxTo is valid
	}
	else
	{
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount, -1);  // grow it to new size
		McsDestructElements<TYPE>(m_pData+nOldSize, nCount);
		::memmove(m_pData+nIdxTo+nCount, m_pData+nIdxTo, (nOldSize-nIdxTo) * sizeof(TYPE));
		McsConstructElements<TYPE>(m_pData+nIdxTo, nCount);
	}

	for(int i=0; i<(int)nCount; i++)
		m_pData[nIdxTo+i] = pArr[i];
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::QuickSortStringsDgtA(bool bAscent, INT_PTR iFrom, INT_PTR nItemsToSort)
{
	StrDgtCmpA cmp_d_a;
	McsArray::QuickSortCmp(cmp_d_a, bAscent, iFrom, nItemsToSort);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::QuickSortStringsDgtW(bool bAscent, INT_PTR iFrom, INT_PTR nItemsToSort)
{
	StrDgtCmpW cmp_d_w;
	McsArray::QuickSortCmp(cmp_d_w, bAscent, iFrom, nItemsToSort);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::QuickSortStringsDgt(bool bAscent, INT_PTR iFrom, INT_PTR nItemsToSort)
{
	StrDgtCmp cmp_d_t;
	McsArray::QuickSortCmp(cmp_d_t, bAscent, iFrom, nItemsToSort);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
template<class CMP>
void McsArray<TYPE, ARG_TYPE>::QuickSortCmp(CMP& cmp, bool fAscent, INT_PTR iFrom, INT_PTR nItems)
{
	MCSASSERTx64_EX_32bit(iFrom, return);
	MCSASSERTx64_EX_32bit(nItems, return);

	if(m_nSize==0) return;
	MCSASSERTE_EX(IsInvalidPtr(m_pData), return);
	MCSASSERTE_EX(iFrom<0 || iFrom>=m_nSize || nItems<0 || nItems>m_nSize, return);

	if(nItems==0) 
		nItems = m_nSize-iFrom;

	if(nItems==1)
		return;

	int iUpTo=(int)(iFrom+nItems-1);
	int Lo=(int)iFrom, Hi=(int)iUpTo;
	TYPE midval; 
	midval = m_pData[(Lo+Hi)/2];
	do 
	{
		if(fAscent) {
			while(cmp(m_pData[Lo], midval)) Lo++;
			while(cmp(midval, m_pData[Hi])) Hi--;
		} else {
			while(cmp(midval, m_pData[Lo])) Lo++;
			while(cmp(m_pData[Hi], midval)) Hi--;
		}

		if(Lo>Hi) 
			break;
		if(Hi==Lo) {
			Lo++; Hi--; break;
		}
		_swap(m_pData[Lo],m_pData[Hi]);
		Lo++; Hi--;
	}while(Lo <= Hi);
	//...
	if(Hi > iFrom)
		QuickSortCmp(cmp, fAscent, iFrom, Hi-iFrom+1);
	if(Lo < iUpTo)
		QuickSortCmp(cmp, fAscent, Lo,    iUpTo-Lo+1);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::QuickSort(bool fAscent, INT_PTR iFrom, INT_PTR nItems)
{
	MCSASSERTx64_EX_32bit(iFrom, return);
	MCSASSERTx64_EX_32bit(nItems, return);

	if(m_nSize==0) return;
	MCSASSERTE_EX(IsInvalidPtr(m_pData), return);
	MCSASSERTE_EX(iFrom<0 || iFrom>=m_nSize || nItems<0 || nItems>m_nSize, return);

	if(nItems==0) 
		nItems = m_nSize-iFrom;

	if(nItems==1)
		return;

	int iUpTo=(int)(iFrom+nItems-1);
	int Lo=(int)iFrom, Hi=(int)iUpTo;
	TYPE midval; 
	midval = m_pData[(Lo+Hi)/2];
	do 
	{
		if(fAscent) {
			while(m_pData[Lo] < midval) Lo++;
			while(m_pData[Hi] > midval) Hi--;
		} else {
			while(m_pData[Lo] > midval) Lo++;
			while(m_pData[Hi] < midval) Hi--;
		}

		if(Lo>Hi) 
			break;
		if(Hi==Lo) {
			Lo++; Hi--; break;
		}
		_swap(m_pData[Lo],m_pData[Hi]);
		Lo++; Hi--;
	}while(Lo <= Hi);
	//...
	if(Hi > iFrom)
		QuickSort(fAscent, iFrom, Hi-iFrom+1);
	if(Lo < iUpTo)
		QuickSort(fAscent, Lo,    iUpTo-Lo+1);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
int McsArray<TYPE, ARG_TYPE>::BinarySearch(ARG_TYPE value,bool fSortedAscent) const
{
	if(m_nSize<=0)
		return -1;
	if(m_nSize<=4) {
		// it's more efficiently to perform std search when number of items is too small
		int idx;
		find(value,idx,0);
		return idx;
	}

	// bsearch
	int iLo=0, iHi=m_nSize-1, iMid=(m_nSize>>1);
	while(iLo<iHi)
	{
		if(m_pData[iMid]==value) return iMid;
		bool f = m_pData[iMid] < value;
		if(!fSortedAscent) f=!f;
		if(f) {
			iLo=iMid+1;
			iMid=(iLo+iHi)/2;
		} else {
			iHi=iMid-1;
			iMid=(iLo+iHi)/2;
		}
	}

	if(m_pData[iLo] == value) 
		return iLo;
	return -1;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE, ARG_TYPE>::find(ARG_TYPE value, int& foundAt, INT_PTR start, ArgsEqualProc* pComparator) const
{
	MCSASSERTx64_EX_32bit(start, return false);
	foundAt = -1;
	for(int i = (int)start; i < m_nSize; ++i)
	{
		if(pComparator ? pComparator(m_pData[i], value) : m_pData[i] == value)
		{
			foundAt = i;
			return true;
		}
	}
	return false;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
int McsArray<TYPE, ARG_TYPE>::indexOf(ARG_TYPE value, ArgsEqualProc* pComparator) const
{
	int idx;
	if(!find(value, idx, 0, pComparator))
		idx = -1;
	return idx;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE, ARG_TYPE>::contains(ARG_TYPE value, ArgsEqualProc* pComparator) const
{
	int dummy; 
	return find(value, dummy, 0, pComparator); 
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE, ARG_TYPE>::contains(const McsArray& values, ArgsEqualProc* pComparator) const
{
	if(this == &values)
		return true;

	if(values.m_nSize > m_nSize)
		return false;
	if(!values.m_nSize || !m_nSize)
		return false;

	int a; // idx in (a)rg
	int t; // idx in (t)his
//	int lim = _mcsarr_getOptimizeLim((TYPE*)NULL);

	/*
	if(m_nSize > lim && values.m_nSize > lim)
	{
		// convert this to hashset
		MESSAGE_WARN_NOCP_A("McsArray::contains(McsArray), Use McsHashsetEx to optimize operation");
		ValHashsetEx thisSet(*this);

		for(a=0; a<values.m_nSize; a++) {
			TYPE& va = values.m_pData[a];
			if(!thisSet.contains(va))
				return false;
		}
	}
	else
	*/
	{
		for(a = 0; a < values.m_nSize; ++a)
		{
			TYPE& va = values.m_pData[a];
			for(t = 0; t < m_nSize; ++t)
			{
				if(pComparator ? pComparator(m_pData[t], va) : m_pData[t] == va)
					break;
			}
			if(t == m_nSize)
				return false;
		}
	}

	return true;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE, ARG_TYPE>::containsAnyOf(const McsArray& values, ArgsEqualProc* pComparator) const
{
	if(this == &values)
		return true;

	if(!values.m_nSize || !m_nSize)
		return false;

	int a; // idx in (a)rg
	int t; // idx in (t)his
	for(a = 0; a < values.m_nSize; ++a)
	{
		TYPE& va = values.m_pData[a];
		for(t = 0; t < m_nSize; ++t)
		{
			if(pComparator ? pComparator(m_pData[t], va) : m_pData[t] == va)
				return true;
		}
	}
	return false;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE, ARG_TYPE>::contains(const ValHashset& set) const
{
	return set.contains(*this);
	/*
	int ns = set.GetSize();
	if(ns > m_nSize)
		return false;
	if(!ns || !m_nSize)
		return false;

	int lim = _mcsarr_getOptimizeLim((TYPE*)NULL);

	if(m_nSize > lim && ns > lim)
	{
		// convert this to hashset
		MESSAGE_WARN_NOCP_A("McsArray::contains(ValHashset), Use McsHashsetEx to optimize operation");
		ValHashsetEx thisSet(*this);
		return thisSet.contains(set);
	}
	else
	{
		MCSPOSITION pos = set.GetStartPosition();
		TYPE* pK = NULL;
		while(pos)
		{
			set.GetNextKey(pos, pK);
			int t;
			for(t=0; t<m_nSize; t++) {
				if(m_pData[t] == *pK)
					break;
			}
			if(t == m_nSize)
				return false;
		}
	}
	return true;
	*/
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE, ARG_TYPE>::contains(const ValHashsetEx& set) const
{
	return set.contains(*this);

	/*
	int ns = set.GetSize();
	if(ns > m_nSize)
		return false;
	if(!ns || !m_nSize)
		return false;

	int lim = _mcsarr_getOptimizeLim((TYPE*)NULL);

	if(m_nSize > lim && ns > lim)
	{
		// convert this to hashset
		MESSAGE_WARN_NOCP_A("McsArray::contains(ValHashset), Use McsHashsetEx to optimize operation");
		ValHashsetEx thisSet(*this);
		return thisSet.contains(set);
	}
	else
	{
		for(mapidx mi=set.FirstIdx(); mi < ns; ++mi)
		{
			const TYPE& va = set[mi];
			int t;
			for(t=0; t<m_nSize; t++) {
				if(m_pData[t] == va)
					break;
			}
			if(t == m_nSize)
				return false;
		}
	}
	return true;
	*/
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE, ARG_TYPE>::containsAnyOf(const ValHashset& set) const
{
	int ns = set.GetSize();
	if(!ns || !m_nSize)
		return false;

	for(int i=0; i<m_nSize; i++) {
		if(set.contains(m_pData[i]))
			return true;
	}

	return false;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE, ARG_TYPE>::containsAnyOf(const ValHashsetEx& set) const
{
	int ns = set.GetSize();
	if(!ns || !m_nSize)
		return false;

	for(int i=0; i<m_nSize; i++) {
		if(set.contains(m_pData[i]))
			return true;
	}

	return false;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
bool McsArray<TYPE, ARG_TYPE>::remove(ARG_TYPE value, INT_PTR start, ArgsEqualProc* pComparator)
{
	int idx = 0;
	if(find(value, idx, start, pComparator)) {
		RemoveAt(idx);
		return true;
	}
	return false;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
McsArray<TYPE,ARG_TYPE>& 
McsArray<TYPE, ARG_TYPE>::swap(INT_PTR idx1, INT_PTR idx2)
{
	MCSASSERTx64_EX_32bit(idx1, return *this);
	MCSASSERTx64_EX_32bit(idx2, return *this);

	MCSASSERTE_EX(idx1<0 || idx2<0 || idx1>=m_nSize || idx2>=m_nSize, return *this);
	if(idx1==idx2)
		return *this;

	byte cnt[sizeof(TYPE)];
	memcpy(cnt, m_pData+idx1, sizeof(TYPE));
	memcpy(m_pData+idx1, m_pData+idx2, sizeof(TYPE));
	memcpy(m_pData+idx2, cnt, sizeof(TYPE));
	return *this;
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
McsArray<TYPE,ARG_TYPE>& 
McsArray<TYPE, ARG_TYPE>::reverse()
{
	if(m_nSize<=0) return *this;
	TYPE* pNewData=(TYPE*)mcsMemAlloc(m_nMaxSize*sizeof(TYPE));
	CHECK_OUT_OF_MEM(!pNewData && m_nMaxSize);

	if(_gf_Enable_DefecateMem)
		memset(pNewData+m_nSize, FECAL_BYTE, (m_nMaxSize-m_nSize) * sizeof(TYPE));

	for(int isrc=m_nSize-1, idest=0; isrc>=0; isrc--, idest++) {
		memcpy(pNewData+idest, m_pData+isrc, sizeof(TYPE));
	}
	mcsMemFree(m_pData);
	m_pData=pNewData;
	return *this;
}
//===========================================================================
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::MoveElements(INT_PTR destIndex, INT_PTR srcIndex, INT_PTR nCount)
{
	MCSASSERTx64_EX_32bit(destIndex, return);
	MCSASSERTx64_EX_32bit(srcIndex, return);
	MCSASSERTx64_EX_32bit(nCount, return);

	if(nCount == 0)
		return;

	int offset = (int)(destIndex - srcIndex);
	if(offset == 0)
		return;

	MCSASSERTE_EX(
		nCount < 0                       ||
		srcIndex < 0                     ||
		srcIndex+nCount > m_nSize        ||
		destIndex < 0                    ||
		destIndex+nCount > m_nSize, 
		return);

	// prepare block pointers and sizes
	TYPE* tmparr;
	TYPE* pBase=m_pData;
	TYPE* pOldBlock=pBase+srcIndex;
	TYPE* pNewBlock=pOldBlock+offset;
	TYPE* pOldOverlappedBlock=offset<0 ? pNewBlock : pOldBlock+nCount;
	TYPE* pNewOverlappedBlock=offset<0 ? pOldOverlappedBlock+nCount : pOldBlock;
	int szblock = (int)(nCount*sizeof(TYPE));
	int szovblock = (int)((offset<0 ? -offset : offset)*sizeof(TYPE));

	if(szblock<=szovblock)
	{
		// blocks are not overlapped...
		// items to move LE than overlapped items to move so store in the temp buffer
		// block with items to move
		tmparr=(TYPE*)mcsMemAlloc(szblock); 
		CHECK_OUT_OF_MEM(!tmparr && szblock);
		memmove(tmparr, pOldBlock, szblock);
		memmove(pNewOverlappedBlock, pOldOverlappedBlock, szovblock);
		// restore items to move to the new position
		memmove(pNewBlock, tmparr, szblock); 
	}
	else //..................................................
	{
		// blocks are overlapped...
		tmparr=(TYPE*)mcsMemAlloc(szblock); 
		CHECK_OUT_OF_MEM(!tmparr && szblock);
		memmove(tmparr, pOldOverlappedBlock, szovblock);
		memmove(pNewBlock, pOldBlock, szblock);
		memmove(pNewOverlappedBlock, tmparr, szovblock);
	}
	// free temp buffer
	mcsMemFree(tmparr);
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::Intersect( const McsArray& ArrayWith, ArgsEqualProc* pComparator )
{
	if(ArrayWith.IsEmpty() || this == &ArrayWith) {
		RemoveAll();
		return;
	}

	//int lim = _mcsarr_getOptimizeLim((TYPE*)NULL);

	int i, nE = ArrayWith.GetSize();

	/*
	if(m_nSize > lim && nE > lim)
	{
		// convert this to hashset
		MESSAGE_WARN_NOCP_A("McsArray::Intersect(McsArray), Use McsHashsetEx to optimize operation");
		ValHashsetEx set(ArrayWith);

		for(i = m_nSize - 1; i >= 0; i--)
			if (!set.contains(m_pData[i]))
				RemoveAt(i);
	}
	else
	*/
	{
		for(i = m_nSize - 1; i >= 0; i--)
			if (!ArrayWith.contains(m_pData[i], pComparator))
				RemoveAt(i);
	}
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::Intersect(const ValHashset& set)
{
	for(int i = m_nSize - 1; i >= 0; i--)
		if (!set.contains(m_pData[i]))
			RemoveAt(i);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::Intersect(const ValHashsetEx& set)
{
	for(int i = m_nSize - 1; i >= 0; i--)
		if (!set.contains(m_pData[i]))
			RemoveAt(i);
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::Subtract( const McsArray& ArraySubtrahend, ArgsEqualProc* pComparator )
{
	if(ArraySubtrahend.IsEmpty())
		return;
	if(this == &ArraySubtrahend) {
		RemoveAll();
		return;
	}

	//int lim = _mcsarr_getOptimizeLim((TYPE*)NULL);
	int i, nE = ArraySubtrahend.GetSize();

	/*
	if(m_nSize > lim && nE > lim)
	{
		// convert this to hashset
		MESSAGE_WARN_NOCP_A("McsArray::Subtract(McsArray), Use McsHashsetEx to optimize operation");
		ValHashset set(ArraySubtrahend);

		for(i = m_nSize - 1; i >= 0; i--)
			if (set.contains(m_pData[i]))
				RemoveAt(i);
	}
	else
	*/
	{
		for(i = m_nSize - 1; i >= 0; i--)
			if (ArraySubtrahend.contains(m_pData[i], pComparator))
				RemoveAt(i);
	}
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::Subtract(const ValHashset& set)
{
	for(int i = m_nSize - 1; i >= 0; i--)
		if (set.contains(m_pData[i]))
			RemoveAt(i);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
void McsArray<TYPE, ARG_TYPE>::Subtract(const ValHashsetEx& set)
{
	for(int i = m_nSize - 1; i >= 0; i--)
		if (set.contains(m_pData[i]))
			RemoveAt(i);
}
//...........................................................................
template<class TYPE, class ARG_TYPE>
McsArray<TYPE, ARG_TYPE>& McsArray<TYPE, ARG_TYPE>::operator<<( ARG_TYPE arg )
{
	Add(arg);
	return *this;
}
//...........................................................................

template<class TYPE, class ARG_TYPE>
template<class FUNC>
void McsArray<TYPE, ARG_TYPE>::ForEach( FUNC& func )
{
	for(int i = 0; i < m_nSize; i++)
	{
		if(!func(m_pData[i]))
			break;
	}
}
//..........................................................................

template<class TYPE, class ARG_TYPE>
template<class FUNC>
void McsArray<TYPE, ARG_TYPE>::ForEach( FUNC& func ) const
{
	for(int i = 0; i < m_nSize; i++)
	{
		if(!func(m_pData[i]))
			break;
	}
}

//===========================================================================
struct McsPlex     // warning variable length structure
{
	McsPlex* pNext;

	void* data() { return this+1; }

	static MT_API McsPlex* PASCAL Create(McsPlex*& head, UINT_PTR nMax, UINT_PTR cbElement);
	MT_API void FreeDataChain();
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
struct mapidxuse
{
	DWORD refCounter;
	bool  fMapAlive;

	mapidxuse(){
		refCounter = 0;
		fMapAlive = false;
	}
};
struct __MCSPOSITION { };
typedef __MCSPOSITION* MCSPOSITION;

//...........................................................................

struct mapidx
{
public:
	int         iLogical;
	mutable int iPhysical;
	int         offset; // >=0: physical index will fly up to real value, <0 - down

	// ptr to ref counter in McsMapEx, while any mapidx object exists then 
	// AutoPack for raw tables in McsMapEx will be blocked
	mapidxuse* pMU;

public:
	mapidx() {iLogical=-1; iPhysical=-1; offset=0; pMU=NULL;}
	mapidx(const mapidx& cf) {pMU=NULL; *this = cf;}
	~mapidx() {
		releaseMU();
	}

	void releaseMU()
	{
		if(pMU) 
		{
			pMU->refCounter--;
			if(pMU->refCounter==0 && !pMU->fMapAlive)
				delete pMU;
		}
		pMU = NULL;
	}

	void addrefMU()
	{
		if(pMU) 
			pMU->refCounter++;
	}

	bool isAttached() {
		return !!pMU;
	}

	operator int() {return iLogical;}

	mapidx& operator =(const mapidx& cf)
	{
		if(this == &cf) return *this;
		iLogical  = cf.iLogical;
		iPhysical = cf.iPhysical;
		offset    = cf.offset;
		if(pMU != cf.pMU) {
			releaseMU();
			pMU = cf.pMU;
			addrefMU();
		}
		return *this;
	}

	bool operator > (int i) const {return iLogical>i;}
	bool operator < (int i) const {return iLogical<i;}
	bool operator <=(int i) const {return iLogical<=i;}
	bool operator >=(int i) const {return iLogical>=i;}
	bool operator ==(int i) const {return iLogical==i;}
	bool operator !=(int i) const {return iLogical!=i;}

	mapidx& operator +=(int ofs)
	{
		if(ofs==0)
			return *this;
		iLogical += ofs;
		iPhysical += ofs;
		if(ofs > 0)
			offset = 1;
		else
			offset = -1;
		return *this;
	}

	mapidx& operator -=(int ofs) {
		operator += (-ofs);
		return *this;
	}

	// prefix
	mapidx& operator++() {iLogical++; iPhysical++; offset=1; return *this;}
	mapidx& operator--() {iLogical--; iPhysical--; offset=-1; return *this;}
	// postfix
	mapidx operator++(int) {mapidx temp=*this; iLogical++; iPhysical++; offset=1; return temp;}
	mapidx operator--(int) {mapidx temp=*this; iLogical--; iPhysical--; offset=-1; return temp;}
};
typedef McsArray<mapidx, const mapidx&> mapIndices;

//=============================================================================

template<class ARG_KEY>
__inline UINT __stdcall McsHashKey(ARG_KEY key)
{
	// default identity hash - works for most primitive values
	//return ((UINT)(void*)(DWORD)key) >> 4;
	return (UINT)(UINT_PTR)key;
}
//=============================================================================
template<> __inline UINT __stdcall McsHashKey(__int64 key)
{
	// 24.12.2008
	// один из способов быстро получить псевдослучайное число,
	// даешь почти равномерно распределенный хэш, 
	// число оптимальны с точки зрения ГПСЧ для 32-х значачих разрядов;
	__int64 rand_m = 714025, rand_a = 4096, rand_c = 150889;

	DWORD iran = (DWORD) ((key*rand_a+rand_c)%rand_m);
	return iran;
}
//template <> MT_API UINT __stdcall McsHashKey(__int64 key); // для тестирования код удобно раскомменрировать код в MT!Tools.cpp
//=============================================================================
template <> __inline UINT __stdcall McsHashKey <const GUID&> (const GUID& key)
{
// 	LPDWORD pdw = (LPDWORD)&key;
// 	return (UINT)(pdw[0] ^ pdw[1] ^ pdw[2] ^ pdw[3]);
	const __int64* pi64 = (const __int64*)&key;
	UINT h = McsHashKey<__int64>(pi64[0]);
	UINT h1 = McsHashKey<__int64>(pi64[1]);
	h ^= h1;
	return h;
};
//=============================================================================
template<> __inline UINT __stdcall McsHashKey(double key)
{
	return ((DWORD*)&key)[0] + ((DWORD*)&key)[1];
	//return McsHashKey<__int64>(*(__int64*)&key);
}
//=============================================================================
// билят, 2002-я и 2005-я матюгаются на это, т.е. видят MCSUID как double, типа дефайн, да?... сволочи
#if _MSC_VER==1200 || _MSC_VER==1310
template<> __inline UINT __stdcall McsHashKey(MCSUID key)
{
	return ((DWORD*)&key)[0] + ((DWORD*)&key)[1];
	//return McsHashKey<__int64>(*(__int64*)&key);
}
#endif
//=============================================================================
template <> __inline UINT __stdcall McsHashKey(void* pV)
{
#ifdef WIN64
	return LODWORD((UINT_PTR)pV) ^ HIDWORD((UINT_PTR)pV);
#else
	return (UINT)(UINT_PTR)pV;
#endif
}
//=============================================================================
template <> __inline UINT __stdcall McsHashKey(const void* pV)
{
#ifdef WIN64
	return LODWORD((UINT_PTR)pV) ^ HIDWORD((UINT_PTR)pV);
#else
	return (UINT)(UINT_PTR)pV;
#endif
}
//=============================================================================
template <> __inline UINT __stdcall McsHashKey(IUnknown* pUnk)
{
  return McsHashKey<void*>((void*)pUnk);
}
//=============================================================================
template<> __inline UINT __stdcall McsHashKey<MCSUID>(MCSUID key)
{
	return McsHashKey<double>((double)key);
}
//=============================================================================
template<> __inline UINT __stdcall McsHashKey<const MCSUID&>(const MCSUID& key)
{
	return McsHashKey<double>((double)key);
}
//=============================================================================

#define MCS_BEFORE_START_POSITION ((MCSPOSITION)-1L)

#define MAP_MAX_COMPARISIONS     5
#define HASHTABLE_GROW_COEFF     2.0
#define MIN_MAP_HASH_TABLE_SIZE  11
#define MAX_MAP_HASH_TABLE_SIZE  1000003

//=============================================================================
extern "C" MT_API bool isSimpleNumber(UINT num);
//=============================================================================
__inline UINT _fitHashTableSizeToSimpleNum(UINT_PTR desiredHTSize)
{
	MCSASSERTx64_EX_32bit(desiredHTSize, desiredHTSize = MIN_MAP_HASH_TABLE_SIZE);

	if(desiredHTSize == 0)
		desiredHTSize = MIN_MAP_HASH_TABLE_SIZE;

	UINT simpleHTS = 0;

	// (!) NOTE: заначение старшей цифры i-й ячейки должно равняться i
	// Смысл требования в том, чтобы выполнялось равенство:
	// _fitHashTableSizeToSimpleNum(x) = _fitHashTableSizeToSimpleNum( _fitHashTableSizeToSimpleNum(x) )
	//
	static const int ls_simpleNumbers10[10] =
		{ 7, 19, 29, 37, 47, 59, 67, 79, 89, 97 };
	static const int ls_simpleNumbers100[10] =
		{ 97, 199, 293, 397, 499, 599, 691, 797, 887, 997 };
	static const int ls_simpleNumbers1000[10] =
		{ 997, 1999, 2999, 3989, 4999, 5987, 6997, 7993, 8999, 9973 };
	static const int ls_simpleNumbers10000[10] =
		{ 9973, 19997, 29989, 39989, 49999, 59999, 69997, 79999, 89989, 99991 };
	static const int ls_simpleNumbers100000[10] =
		{ 99991, 199999, 299993, 399989, 499979, 599999, 699967, 799999, 899981, 999983};

	if(desiredHTSize < MAX_MAP_HASH_TABLE_SIZE)
	{
		if(desiredHTSize < 100)
			simpleHTS = ls_simpleNumbers10[desiredHTSize/10];
		else if(desiredHTSize < 1000)
			simpleHTS = ls_simpleNumbers100[desiredHTSize/100];
		else if(desiredHTSize < 10000)
			simpleHTS = ls_simpleNumbers1000[desiredHTSize/1000];
		else if(desiredHTSize < 100000)
			simpleHTS = ls_simpleNumbers10000[desiredHTSize/10000];
		else
		{
			int idx = (int)(desiredHTSize / 100000);
			int idxMax = _countof(ls_simpleNumbers100000) - 1;
			simpleHTS = ls_simpleNumbers100000[min(idx, idxMax)];
		}
	}
	else
	{
		//if(desiredHTSize > MAP_MAX_COMPARISIONS * MAX_MAP_HASH_TABLE_SIZE)
		//	MESSAGE_WARN_A("_fitHashTableSizeToSimpleNum - A top limit of a hash table size has been reached, optimize your program");
		simpleHTS = MAX_MAP_HASH_TABLE_SIZE;
	}

	return simpleHTS;
}

//=============================================================================

#include "McsMap.H"

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
// McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE> /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#pragma pack(push,1)
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
class McsMapEx
{
protected:

#ifdef _MCEYE
public:
#endif

	// Association
	struct McsAssoc
	{
		McsAssoc* pNext;
		UINT      nHashValue;  // needed for efficient iteration
		KEY       key;   // !!! Keep <value> after <key>
		VALUE     value; // !!! Keep <rawIndex> after <value>
		int       rawIndex; // index of element in table with raw pointers
	};

protected:

#ifdef _MCEYE
public:
#endif

	McsAssoc**      m_pHashTable;
	int             m_nHashTableSize;
	int             m_nCount;
	McsAssoc*       m_pFreeList;
	struct McsPlex* m_pBlocks;
	int             m_nBlockSize;

	int             m_nHolesInRawTable; // number of removed elements in raw table
	bool            m_fRawAccessEnabled; // if true then map will synchronize content of <m_KP> and <m_VP> with hash table
	mapidxuse*      m_pMU; // if ref in struct non 0 then there are some mapidx objects which refers to this map, pack/autopack of raw tables is blocked in this case
	McsArray<KEY*,KEY*>     m_KP;
	McsArray<VALUE*,VALUE*> m_VP;

	bool            m_fStripHTOverflowWarning;
	bool            m_fHashSetMode;

public:

	typedef McsHashsetEx<KEY, ARG_KEY> KeysHashsetEx;
	typedef McsHashset<KEY, ARG_KEY>   KeysHashset;
	typedef McsArray<KEY, ARG_KEY>     KeysArray;
	typedef McsArray<VALUE, ARG_VALUE> ValuesArr;

	DECLARE_OBJ_NEWDEL;
	McsMapEx(INT_PTR nBlockSize = 10, bool fRawAccessEnabled = true);

	McsMapEx(const McsMapEx&);
	~McsMapEx();

// Attributes
	// number of elements
	int  GetCount() const { return m_nCount; }
	int  GetSize() const { return m_nCount; }
	int  Length() const { return m_nCount; }
	bool IsEmpty() const { return m_nCount == 0; }
	bool isEmpty() const { return m_nCount == 0; }

	// Lookup
	bool Lookup(ARG_KEY key, VALUE& rValue) const;
	bool isExist(ARG_KEY) const;
		// синонимы isExist
	bool exist(ARG_KEY key) const {return isExist(key);}
	bool Exist(ARG_KEY key) const {return isExist(key);}
	bool contains(ARG_KEY key) const {return isExist(key);}

		// возвращает индекс ключа, если не находит, то индекс будет <0
	mapidx indexOf(ARG_KEY key) const;
	bool find(ARG_KEY key, OUT mapidx& idx) { idx = indexOf(key); return idx.iLogical>=0; }

// Operations
	// Lookup and add if not there
	VALUE& operator[](ARG_KEY key);
	VALUE& valueAt(ARG_KEY key); //	same as operator []
	const KEY& keyAt(ARG_KEY key) const; //	same as operator [], but return stored key ref in map
	void getAt(ARG_KEY key, const KEY*& pStoredKey, VALUE*& pStoredVal);

	void getAt(ARG_KEY key, const KEY*& pStoredKey, const VALUE*& pStoredVal) const {
		((McsMapEx*)this)->getAt(key, pStoredKey, (VALUE*&)pStoredVal);
	}

	VALUE* getExistingValPtr(ARG_KEY key); // if no such pair exist then will return NULL
	const VALUE* getExistingValPtr(ARG_KEY key) const; // if no such pair exist then will return NULL

	const KEY* getExistingKeyPtr(ARG_KEY key) const; // if no such pair exist then will return NULL

	// Get an existing pair for the given key.
	// If there are no such ones, both pointers will be NULL.
	bool assocAt(ARG_KEY key, const KEY*& pStoredKey, VALUE*& pStoredVal);

	bool assocAt(ARG_KEY key, const KEY*& pStoredKey, const VALUE*& pStoredVal) const {
		return ((McsMapEx*)this)->assocAt(key, pStoredKey, (VALUE*&)pStoredVal);
	}

		// query all keys in an array form, returns number of keys
	int getKeys(OUT KeysArray&) const;

		// query all values an array form, returns number of values
	int getValues(OUT ValuesArr&) const;

	// add a new (key, value) pair
	void SetAt(ARG_KEY key, ARG_VALUE newValue);

	// removing existing (key, ?) pair
	bool RemoveKey(ARG_KEY key);
	McsMapEx& operator -= (ARG_KEY key) { RemoveKey(key); return *this; }
	void RemoveAll();

	bool operator == (const McsMapEx&) const;
	bool operator != (const McsMapEx& cw) const { return !(*this==cw); }

	// iterating all (key, value) pairs
	MCSPOSITION GetStartPosition() const;
	void GetNextAssoc(MCSPOSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;
	void GetNextAssoc(MCSPOSITION& rNextPosition, KEY*& pKey, VALUE*& pValue);

	void GetNextAssoc(MCSPOSITION& rNextPosition, const KEY*& pKey, const VALUE*& pValue) const {
		((McsMapEx*)this)->GetNextAssoc(rNextPosition, (KEY*&)pKey, (VALUE*&)pValue);
	}

	void GetNextKey(MCSPOSITION& rNextPosition, KEY& rKey) const;
	void GetNextKey(MCSPOSITION& rNextPosition, KEY*& pKey);

	void GetNextKey(MCSPOSITION& rNextPosition, const KEY*& pKey) const {
		((McsMapEx*)this)->GetNextKey(rNextPosition, (KEY*&)pKey);
	}

	void GetNextValue(MCSPOSITION& rNextPosition, VALUE& rVal) const;
	void GetNextValue(MCSPOSITION& rNextPosition, VALUE*& pVal);

	void GetNextValue(MCSPOSITION& rNextPosition, const VALUE*& pValue) const {
		((McsMapEx*)this)->GetNextValue(rNextPosition, (VALUE*&)pValue);
	}

		// элементы idxFrom и idxUpTo включительно, если idxUpTo < 0 - выдать всё, до конца,
		// если фича rawAccessEnabled выключена, будет ассерт и будут выданы все элементы
	bool getAsArray(ValuesArr& values, int idxFrom = 0, int idxUpTo = -1) const;
	bool AsArray(ValuesArr& values, int idxFrom = 0, int idxUpTo = -1) const {
		return getAsArray(values, idxFrom, idxUpTo);
	}

		// Выдаёт набор ключей в виде Hashset
	bool getAsHashset(OUT KeysHashsetEx& set) const;
	bool getAsHashset(OUT KeysHashset& set) const;

	McsMapEx& operator = (const McsMapEx&);

		// Intersect by keys
	void intersect(const McsMapEx& map);
	void intersect(const KeysHashsetEx& keySet);
	void intersect(const KeysHashset& keySet);
	void intersect(const KeysArray& keyArr);

	McsMapEx& operator &= (const McsMapEx& map) { intersect(map); return *this; }
	McsMapEx& operator &= (const KeysHashsetEx& keySet) { intersect(keySet); return *this; }
	McsMapEx& operator &= (const KeysHashset& keySet) { intersect(keySet); return *this; }
	McsMapEx& operator &= (const KeysArray& keyArr) { intersect(keyArr); return *this; }

	void removeSubset(const McsMapEx& map);
	void removeSubset(const KeysHashsetEx& keySet);
	void removeSubset(const KeysArray& keyArr);

	bool contains(const McsMapEx& map) const;
	bool contains(const KeysArray& keyArr) const;
	bool contains(const KeysHashsetEx& keySet) const;
	bool contains(const KeysHashset& keySet) const;
	bool containsAnyOf(const McsMapEx& map) const;
	bool containsAnyOf(const KeysArray& keyArr) const;
	bool containsAnyOf(const KeysHashsetEx& keySet) const;
	bool containsAnyOf(const KeysHashset& keySet) const;

	McsMapEx& operator -= (const McsMapEx& map) { removeSubset(map); return *this; }
	McsMapEx& operator -= (const KeysHashsetEx& keySet) { removeSubset(keySet); return *this; }
	McsMapEx& operator -= (const KeysHashset& keySet) { removeSubset(keySet); return *this; }
	McsMapEx& operator -= (const KeysArray& keyArr) { removeSubset(keyArr); return *this; }

	void Append(const McsMapEx& map);
	McsMapEx& operator |= (const McsMapEx& map) { Append(map); return *this; }
	McsMapEx& operator += (const McsMapEx& map) { Append(map); return *this; }

	// !!! USE <false> for <fAutoPack> if you will use more than one raw iteration cycle 
	// !!! one inside other
	mapidx FirstIdx() const; // no autopack inside
	mapidx LastIdx() const; // no autopack inside
	mapidx FirstIdx(bool fAutoPack=true);
	mapidx LastIdx(bool fAutoPack=true);
	int  PackRawTable(bool fForce=true);

		// возвращает список индексов для линейного перебора простым оператором for, пример:
		// mapIndices indices; 
		// map.getMapIndices(indices);
		// for(int i=0; i<indices.GetSize(); i++) {
		//	mapidx& mi = indices[i]
		//	...
		// }
		// ---  вместо ---
		// for(mapidx mi = map.FirstIdx(); i<map.GetSize(); ++mi) {
		//	...
		// }
		// вторая конструкция проще и универсальнее, но первая может использоваться 
		// для распараллеливания с помощью OpenMP
	bool getMapIndices(OUT mapIndices&);

	VALUE& operator[](IN const mapidx&); // same as V()
	VALUE& V(IN const mapidx&);
	KEY&   K(IN const mapidx&);

	const VALUE& operator[](IN const mapidx&) const; // same as V() const
	const VALUE& V(IN const mapidx&) const;
	const KEY&   K(IN const mapidx&) const;

	// advanced features for derived classes
	int GetHashTableSize() const { return m_nHashTableSize; }
	void InitHashTable(UINT_PTR hashSize, bool fAllocNow = true);
		// method which grows size of hash table to the next simple size from <> array if possible
	bool _growHashTableSize();
	void _checkHashTable();

protected:
	McsAssoc* NewAssoc();
	void      FreeAssoc(McsAssoc*);
	McsAssoc* GetAssocAt(ARG_KEY, UINT&, bool fAllowGHT) const;
};
#pragma pack(pop)

//=============================================================================

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
__inline void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::SetAt(ARG_KEY key, ARG_VALUE newValue)
	{ (*this)[key] = newValue; }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
__inline MCSPOSITION McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : MCS_BEFORE_START_POSITION; }

//=============================================================================

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::McsMapEx(INT_PTR nBlockSize,bool fRawAccessEnabled)
{
	MCSASSERTx64_EX_32bit(nBlockSize, nBlockSize=10);
	MCSASSERT_EX(nBlockSize > 0, return);

	m_pHashTable = NULL;
	m_fStripHTOverflowWarning = false;
	m_nHashTableSize = MIN_MAP_HASH_TABLE_SIZE;
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = (int)nBlockSize;

	m_pMU = new mapidxuse;
	m_pMU->fMapAlive = true;

	m_nHolesInRawTable = 0;
	m_fRawAccessEnabled = fRawAccessEnabled;

	m_fHashSetMode = false;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::McsMapEx(const McsMapEx& cf)
{
	m_pHashTable = NULL;
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nHashTableSize = cf.m_nHashTableSize;
	m_nBlockSize = cf.m_nBlockSize;

	m_pMU = new mapidxuse;
	m_pMU->fMapAlive = true;

	m_nHolesInRawTable = 0;
	m_fRawAccessEnabled = true;

	m_fStripHTOverflowWarning = false;
	m_fHashSetMode = cf.m_fHashSetMode;

	*this = cf;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator == (const McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>& cw)const
{
	if(m_nCount != cw.m_nCount)
		return false;
	if(m_nCount==0)
		return true;
	
	for (int nHash = 0; nHash < m_nHashTableSize; nHash++)
	{
		for (McsAssoc* pAssocThis = m_pHashTable[nHash]; pAssocThis; pAssocThis = pAssocThis->pNext)
		{
			UINT nHashCW=0;
			McsAssoc* pAssocCW = cw.GetAssocAt(pAssocThis->key, nHashCW, false);
			if(!pAssocCW)
				return false;
			if(m_fHashSetMode)
				continue;
			if(pAssocCW->value != pAssocThis->value)
				return false;
		}
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>& McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator = (const McsMapEx& cf)
{
	if(this == &cf)
		return *this;

	RemoveAll();

	m_fRawAccessEnabled = cf.m_fRawAccessEnabled;
	m_nBlockSize = cf.m_nBlockSize;
	m_nHashTableSize = cf.m_nHashTableSize;
	m_fStripHTOverflowWarning = cf.m_fStripHTOverflowWarning;

	// initialize hash table without size checking
	if(cf.m_nCount)
		InitHashTable(m_nHashTableSize, true);

	if(m_fRawAccessEnabled)
	{
		for(mapidx mi = cf.FirstIdx(); mi<cf.m_nCount; ++mi)
			SetAt(cf.K(mi), cf.V(mi));
	}
	else
	{
		MCSPOSITION pos = cf.GetStartPosition();
		while(pos) {
			const KEY* pKey; const VALUE* pVal;
			cf.GetNextAssoc(pos, pKey, pVal);
			SetAt(*pKey, *pVal);
		}
	}

	return *this;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::intersect(const McsMapEx& map)
{
	if(0 == map.m_nCount) {
		RemoveAll();
		return;
	}

	// При цепочном переборе нельзя удалять текущий элемент. Можно набрать
	// массив того, что удалять, но это медленно, будем запоминать только
	// один ID и флаг, надо ли его удалять на следующем шаге.

	bool fRemove = false;
	KEY key4remove;

	MCSPOSITION pos = GetStartPosition();
	while(pos)
	{
		if(fRemove) {
			RemoveKey(key4remove);
			fRemove = false;
		}

		KEY* pk = NULL; VALUE* pv = NULL;
		GetNextAssoc(pos, pk, pv);
		if(map.isExist(*pk))
			continue;

		// сразу удалять нельзя, не сработает GetNextAssoc
		key4remove = *pk;
		fRemove = true;
	}
	if(fRemove)
		RemoveKey(key4remove);

	return;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::intersect(const KeysHashsetEx& keySet)
{
	intersect( (McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>&)keySet );
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::intersect(const KeysArray& keyArr)
{
	if(keyArr.isEmpty()) {
		RemoveAll();
		return;
	}

	if(m_nCount == 0)
		return;

	// Формируем множество ключей на основе массива, которое реально может понадобиться
	// для фильтрации мапа. Плюс такого подхода: в множество попадут только те значения
	// которые погут дать положительный результат на isExist запрос.
	KeysHashsetEx keySet;
	int i, n = keyArr.GetSize();
	for(i=0; i<n; i++) {
		const KEY& k = keyArr.GetData()[i];
		if(isExist(k))
			keySet |= k;
	}

	if(keySet.isEmpty()) {
		RemoveAll();
		return;
	}

	// При цепочном переборе нельзя удалять текущий элемент. Можно набрать
	// массив того, что удалять, но это медленно, будем запоминать только
	// один ID и флаг, надо ли его удалять на следующем шаге.

	bool fRemove = false;
	KEY key4remove;

	MCSPOSITION pos = GetStartPosition();
	while(pos)
	{
		if(fRemove) {
			RemoveKey(key4remove);
			fRemove = false;
		}

		KEY* pk = NULL; VALUE* pv = NULL;
		GetNextAssoc(pos, pk, pv);
		if(keySet.isExist(*pk))
			continue;

		// сразу удалять нельзя, не сработает GetNextAssoc
		key4remove = *pk;
		fRemove = true;
	}
	if(fRemove)
		RemoveKey(key4remove);

	return;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::removeSubset(const McsMapEx& map)
{
	for(mapidx mi = map.LastIdx(); mi>=0; --mi) {
		RemoveKey(map.K(mi));
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::removeSubset(const KeysHashsetEx& keySet)
{
	for(mapidx mi = keySet.LastIdx(); mi>=0; --mi) {
		RemoveKey(keySet[mi]);
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::removeSubset(const KeysArray& keyArr)
{
	for(int i=keyArr.GetSize()-1; i>=0; --i) {
		RemoveKey(keyArr.GetData()[i]);
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::Append(const McsMapEx& map)
{
	if(m_fRawAccessEnabled)
	{
		// сохраним порядок
		for(mapidx mi = map.FirstIdx(); mi < map.m_nCount; ++mi) {
			const KEY& k = map.K(mi);
			const VALUE& v = map.V(mi);
			SetAt(k, v);
		}
	}
	else
	{
		MCSPOSITION pos = map.GetStartPosition();
		while(pos)
		{
			const KEY* pk = NULL; const VALUE* pv = NULL;
			map.GetNextAssoc(pos, pk, pv);
			SetAt(*pk, *pv);
		}
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::contains(const McsMapEx& map) const
{
	if(this == &map)
		return true;

	for(mapidx mi = map.LastIdx(); mi>=0; --mi) {
		const KEY& k = map.K(mi);
		if(!isExist(k))
			return false;
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::contains(const KeysArray& keyArr) const
{
	for(int i = keyArr.GetSize()-1; i>=0; i--) {
		const KEY& k = keyArr.GetData()[i];
		if(!isExist(k))
			return false;
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::contains(const KeysHashsetEx& keySet) const
{
	for(mapidx mi = keySet.LastIdx(); mi>=0; --mi) {
		const KEY& k = keySet[mi];
		if(!isExist(k))
			return false;
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::containsAnyOf(const McsMapEx& map) const
{
	if(this == &map)
		return true;

	for(mapidx mi = map.LastIdx(); mi>=0; --mi) {
		const KEY& k = map.K(mi);
		if(isExist(k))
			return true;
	}

	return false;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::containsAnyOf(const KeysArray& keyArr) const
{
	for(int i = keyArr.GetSize()-1; i>=0; i--) {
		const KEY& k = keyArr.GetData()[i];
		if(isExist(k))
			return true;
	}

	return false;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::containsAnyOf(const KeysHashsetEx& keySet) const
{
	for(mapidx mi = keySet.LastIdx(); mi>=0; --mi) {
		const KEY& k = keySet[mi];
		if(isExist(k))
			return true;
	}

	return false;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE& McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::V(const mapidx& idx)
{
	if(m_fHashSetMode)
		return *(VALUE*)NULL;

	MCSASSERTE_EX(!m_fRawAccessEnabled, return *(VALUE*)NULL);
	int nV = m_VP.GetSize();
	MCSASSERTE_EX(idx.iPhysical < 0 || idx.iPhysical >= nV, return *(VALUE*)NULL);

	VALUE** ppV = m_VP.GetData() + idx.iPhysical;
	if(idx.offset>0) {
		for( ; *ppV==NULL && idx.iPhysical < nV-1; ppV++)
			idx.iPhysical++;
	} else {
		for( ; *ppV==NULL && idx.iPhysical > 0; ppV--)
			idx.iPhysical--;
	}

	MCSASSERTE_EX(*ppV==NULL, return *(VALUE*)NULL);
	return **ppV;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
KEY& McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::K(const mapidx& idx)
{
	MCSASSERTE_EX(!m_fRawAccessEnabled, return *(KEY*)NULL);
	int nK = m_KP.GetSize();
	MCSASSERTE_EX(idx.iPhysical < 0 || idx.iPhysical >= nK, return *(KEY*)NULL);

	KEY** ppK = m_KP.GetData() + idx.iPhysical;
	if(idx.offset>0) {
		for( ; *ppK==NULL && idx.iPhysical < nK-1; ppK++)
			idx.iPhysical++;
	} else {
		for( ; *ppK==NULL && idx.iPhysical > 0; ppK--)
			idx.iPhysical--;
	}

	MCSASSERTE_EX(*ppK==NULL, return *(KEY*)NULL);
	return **ppK;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE& McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](const mapidx& idx)
{
  return V(idx);
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const VALUE& McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::V(const mapidx& idx) const
{
	if(m_fHashSetMode)
		return *(const VALUE*)NULL;

	MCSASSERTE_EX(!m_fRawAccessEnabled, return *(VALUE*)NULL);
	int nV = m_VP.GetSize();
	MCSASSERTE_EX(idx.iPhysical < 0 || idx.iPhysical >= nV, return *(VALUE*)NULL);

	const VALUE*const* ppV = m_VP.GetData() + idx.iPhysical;
	if(idx.offset>0) {
		for( ; *ppV==NULL && idx.iPhysical < nV-1; ppV++)
			idx.iPhysical++;
	} else {
		for( ; *ppV==NULL && idx.iPhysical > 0; ppV--)
			idx.iPhysical--;
	}

	MCSASSERTE_EX(*ppV==NULL, return *(VALUE*)NULL);
	return **ppV;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const KEY& McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::K(const mapidx& idx) const
{
	MCSASSERTE_EX(!m_fRawAccessEnabled, return *(KEY*)NULL);
	int nK = m_KP.GetSize();
	MCSASSERTE_EX(idx.iPhysical < 0 || idx.iPhysical >= nK, return *(KEY*)NULL);

	const KEY *const* ppK = m_KP.GetData() + idx.iPhysical;
	if(idx.offset>0) {
		for( ; *ppK==NULL && idx.iPhysical < nK-1; ppK++)
			idx.iPhysical++;
	} else {
		for( ; *ppK==NULL && idx.iPhysical > 0; ppK--)
			idx.iPhysical--;
	}

	MCSASSERTE_EX(*ppK==NULL, return *(KEY*)NULL);
	return **ppK;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const VALUE& McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](const mapidx& idx) const
{
	return V(idx);
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
mapidx McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::FirstIdx() const
{
	mapidx idx;
	MCSASSERTE_EX(!m_fRawAccessEnabled, return idx);
	idx.iLogical = 0;
	idx.iPhysical = 0;
	idx.offset = 1;
	idx.pMU = m_pMU;
	idx.addrefMU();
	return idx;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
mapidx McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::LastIdx() const
{
	mapidx idx;
	MCSASSERTE_EX(!m_fRawAccessEnabled, return idx);
	idx.iLogical = m_nCount-1;
	idx.iPhysical = m_KP.GetSize()-1;
	idx.offset = -1;
	idx.pMU = m_pMU;
	idx.addrefMU();
	return idx;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
mapidx McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::FirstIdx(bool fAutoPack)
{
	mapidx idx;
	MCSASSERTE_EX(!m_fRawAccessEnabled, return idx);
	if(fAutoPack)
		PackRawTable(false);
	idx.iLogical = 0;
	idx.iPhysical = 0;
	idx.offset = 1;
	idx.pMU = m_pMU;
	idx.addrefMU();
	return idx;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
mapidx McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::LastIdx(bool fAutoPack)
{
	mapidx idx;
	MCSASSERTE_EX(!m_fRawAccessEnabled, return idx);
	if(fAutoPack)
		PackRawTable(false);
	idx.iLogical = m_nCount-1;
	idx.iPhysical = m_KP.GetSize()-1;
	idx.offset = -1;
	idx.pMU = m_pMU;
	idx.addrefMU();
	return idx;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::getMapIndices(OUT mapIndices& indices)
{
	if(!m_fRawAccessEnabled) {
		MCSASSERTE(FAILED(E_FAIL));
		indices.RemoveAll();
		return false;
	}

	indices.SetSize(m_nCount);
	mapidx* pMI = indices.GetData();
	for(mapidx mi = FirstIdx(); mi<m_nCount; ++mi) {
		K(mi); // коррекция физического индекса
		pMI[mi.iLogical] = mi;
	}
	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
int McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::PackRawTable(bool fForce)
{
	MCSASSERTE_EX(!m_fRawAccessEnabled, return 0);
	if(m_pMU->refCounter)
		return 0;
	if(!m_nHolesInRawTable)
		return 0;

	int curSize = m_KP.GetSize();
	int nH = m_nHolesInRawTable;
	if(m_nHolesInRawTable != curSize)
	{
		bool fPack = fForce;
		if(!fForce) {
			double kHoles = m_KP.GetSize() == 0 ? 1 : (double)m_nHolesInRawTable / (double)m_KP.GetSize();
			fPack = kHoles > 0.5 && m_KP.GetSize() > 20;
		}
		if(!fPack)
			return 0;

		int idxCorrection = 0;
		int contHoleSize = 0;
		VALUE** pVData = m_VP.GetData();
		KEY** pKData = m_KP.GetData();
		for(int i=0; i<curSize; i++)
		{
			KEY* pK = pKData[i];
			if(!pK)
			{
				idxCorrection--;
				contHoleSize++;

				bool fNeedMove = false;
				if(i == curSize-1)
					fNeedMove = true;
				else
					fNeedMove = pKData[i+1] != NULL;

				if(fNeedMove)
				{
					memmove(pKData + i - contHoleSize + 1, pKData + i + 1, sizeof(KEY*) * (curSize - i - 1));
					if(!m_fHashSetMode)
						memmove(pVData + i - contHoleSize + 1, pVData + i + 1, sizeof(VALUE*) * (curSize - i - 1));
					curSize -= contHoleSize;
					i -= contHoleSize;
					contHoleSize=0;
				}
			} else {
				int ofsFromKeyToIdx = (int)(_member_offset(McsAssoc, rawIndex) - _member_offset(McsAssoc, key));
				int* pIdx = (int*)((LPBYTE)pK + ofsFromKeyToIdx);
				*pIdx += idxCorrection;
			}
		}
	} else {
		curSize = 0;
	}

	m_KP.SetSize(curSize);
	if(!m_fHashSetMode)
		m_VP.SetSize(curSize);

	m_nHolesInRawTable = 0;
	return nH;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::getAsArray(ValuesArr& elements, int idxFrom, int idxUpTo) const
{
	elements.RemoveAll();
	if(m_nCount==0)
		return false;

	int i=0;
	if(m_fRawAccessEnabled)
	{
		MCSASSERTE_EX(idxFrom<0, idxFrom = 0);
		if(idxUpTo<0)
			idxUpTo = m_nCount-1;
		MCSASSERTE_EX(idxUpTo < idxFrom, return false);
		int nCount = idxUpTo - idxFrom + 1;
		elements.SetSize(nCount);

		mapidx mi = FirstIdx();
		mi += idxFrom;
		for(; mi<m_nCount; ++mi)
		{
			if(mi > idxUpTo)
				break;
			elements[i++] = V(mi);
		}
	}
	else
	{
		MCSASSERTE(idxFrom!=0 || idxUpTo!=-1);
		elements.SetSize(m_nCount);

		const VALUE* pVal=NULL;
		MCSPOSITION pos = GetStartPosition();
		while(pos)
		{
			GetNextValue(pos, pVal);
			elements[i++] = *pVal;
		}
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::_checkHashTable()
{
	DWORD nHoles = 0;
	DWORD nMaxValsPerCell = 0;
	DWORD nOverloadedCells = 0;
	double avgValsVerCell = 0;

	for(int iCell = 0; iCell < m_nHashTableSize; ++iCell)
	{
		McsAssoc* pAssoc = NULL;
		DWORD nVals = 0; 
		for (pAssoc = m_pHashTable[iCell]; pAssoc; pAssoc = pAssoc->pNext) {
			nVals++;
		}

		if(nVals == 0)
			nHoles++;

		if(nVals > MAP_MAX_COMPARISIONS)
			nOverloadedCells++;

		if(nVals > nMaxValsPerCell)
			nMaxValsPerCell = nVals;

		avgValsVerCell += nVals;
	}

	avgValsVerCell /= m_nHashTableSize;
	double kHoles = (double)nHoles / m_nHashTableSize;
	double kOverloaded = (double)nOverloadedCells / m_nHashTableSize;

	int check_values_out = 0;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::_growHashTableSize()
{
	if(!m_pHashTable)
		return false;

	int newTableSize = (int)(m_nHashTableSize * HASHTABLE_GROW_COEFF);
	newTableSize = _fitHashTableSizeToSimpleNum(newTableSize);
	if(newTableSize == m_nHashTableSize)
		return false;

	// m_pBlocks, m_nCount, m_pFreeList, m_nHolesInRawTable, m_KP, m_VP MUST stay the same;
	// only one thing will be changed - hash table and used assocs links
	McsAssoc** _pHashTable     = m_pHashTable;
	int        _nHashTableSize = m_nHashTableSize;
	int        nCount          = m_nCount;

	// 1'st we must join all associations in map into single chain
	m_pHashTable = NULL; //	prevent old table from delete
	m_nHashTableSize = 0;
	m_nCount = 0;
	InitHashTable(newTableSize, true);
	m_nCount = nCount;

	for (int oldHTIdx = 0; oldHTIdx<_nHashTableSize; oldHTIdx++)
	{
		for (McsAssoc *pAssoc = _pHashTable[oldHTIdx], *pNextAssocInOldHT = NULL; pAssoc; pAssoc = pNextAssocInOldHT)
		{
			pNextAssocInOldHT = pAssoc->pNext;

			UINT newHTIdx = McsHashKey<ARG_KEY>(pAssoc->key) % newTableSize;

			pAssoc->pNext = m_pHashTable[newHTIdx];
			pAssoc->nHashValue = newHTIdx;
			m_pHashTable[newHTIdx] = pAssoc;
		}
	}

	mcsMemDelete(_pHashTable); _pHashTable = NULL;

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::InitHashTable
(UINT_PTR nHashSize, bool bAllocNow)
{
	if(m_nHashTableSize != (int)nHashSize) {
		MCSASSERT_EX(IsEmpty(), return);
		nHashSize = _fitHashTableSizeToSimpleNum(nHashSize);
	}

	if(m_nHashTableSize == (int)nHashSize) {
		if(!bAllocNow)
			return;
		if(m_pHashTable)
			return;
	}

	m_nHashTableSize = (int)nHashSize;

	if (m_pHashTable) {
		// free hash table
		mcsMemDelete(m_pHashTable);
		m_pHashTable = NULL;
	}

	if (bAllocNow) {
		m_pHashTable = mcsMemNew(McsAssoc*[m_nHashTableSize]);
		CHECK_OUT_OF_MEM(!m_pHashTable);
		memset(m_pHashTable, 0, sizeof(McsAssoc*) * m_nHashTableSize);
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::isExist(ARG_KEY key) const
{
	UINT nHash;
	McsAssoc* pAssoc = GetAssocAt(key, nHash, false);

	if (pAssoc == NULL)
		return false;  // not in map

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
mapidx McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::indexOf(ARG_KEY key) const
{
	mapidx mi;
	MCSASSERTE_EX(!m_fRawAccessEnabled, return mi);

	if(!isExist(key))
		return mi;

	for(mi = LastIdx(); mi >=0 ; --mi) {
		if(K(mi) == key)
			break;
	}

	return mi;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::RemoveAll()
{
	if(!m_pHashTable)
		return;
	McsAssoc** _pHashTable     = m_pHashTable;
	int        _nHashTableSize = m_nHashTableSize;
	McsPlex*   _pBlocks        = m_pBlocks;

	// free hash table
	m_pHashTable = NULL;
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nHolesInRawTable  =0;
	m_KP.RemoveAll();
	m_VP.RemoveAll();

	if(_pHashTable)
	{
		// destroy elements (values and keys)
		for (int nHash = 0; nHash<_nHashTableSize; nHash++)
		{
			for (McsAssoc* pAssoc = _pHashTable[nHash]; pAssoc; pAssoc = pAssoc->pNext)
			{
				if(!m_fHashSetMode)
					McsDestructElements<VALUE>(MCS_GET_OBJ_ADDR(pAssoc->value),1);//(VALUE*)&pAssoc->value, 1);
				McsDestructElements<KEY>(MCS_GET_OBJ_ADDR(pAssoc->key), 1);//(KEY*)&pAssoc->key, 1);
				pAssoc->rawIndex=-1;
			}
		}
		mcsMemDelete(_pHashTable); _pHashTable=NULL;
	}

	if(_pBlocks)
	{
		_pBlocks->FreeDataChain();
		_pBlocks = NULL;
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::~McsMapEx()
{
	if(m_pMU->refCounter == 0)
		delete m_pMU;
	else
		m_pMU->fMapAlive = false;
	m_pMU = NULL;
	RemoveAll();
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::McsAssoc*
McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::NewAssoc()
{
	if (m_pFreeList == NULL)
	{
		// add another block          
		McsPlex* newBlock = McsPlex::Create(m_pBlocks, m_nBlockSize, sizeof(McsMapEx::McsAssoc));
		// chain them into free list
		McsMapEx::McsAssoc* pAssoc = (McsMapEx::McsAssoc*) newBlock->data();
		// free in reverse order to make it easier to debug
		pAssoc += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
		{
			pAssoc->pNext = m_pFreeList;
			m_pFreeList = pAssoc;
		}
	}
	MCSASSERT_EX(m_pFreeList != NULL, return NULL);  // we must have something

	McsMapEx::McsAssoc* pAssoc = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	m_nCount++;
	MCSASSERT(m_nCount > 0);  // make sure we don't overflow
	McsConstructElements<KEY>(MCS_GET_OBJ_ADDR(pAssoc->key),1);//(KEY*)&pAssoc->key, 1);
	if(!m_fHashSetMode)
		McsConstructElements<VALUE>(MCS_GET_OBJ_ADDR(pAssoc->value),1);//(VALUE*)&pAssoc->value, 1);   // special construct values
	pAssoc->rawIndex = -1;

	if(m_fRawAccessEnabled){
		pAssoc->rawIndex = m_KP.GetSize();
		m_KP.Add(MCS_GET_OBJ_ADDR(pAssoc->key));
		if(!m_fHashSetMode)
			m_VP.Add(MCS_GET_OBJ_ADDR(pAssoc->value));
	}

	return pAssoc;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::FreeAssoc(typename McsMapEx::McsAssoc* pAssoc)
{
	if(m_fRawAccessEnabled)do{
		MCSASSERT_EX(pAssoc->rawIndex >= 0 && pAssoc->rawIndex < m_KP.GetSize(), break);
		m_KP.GetData()[pAssoc->rawIndex] = NULL;
		if(!m_fHashSetMode)
			m_VP.GetData()[pAssoc->rawIndex] = NULL;
		m_nHolesInRawTable++;
	}while(0);

	if(!m_fHashSetMode)
		McsDestructElements<VALUE>(MCS_GET_OBJ_ADDR(pAssoc->value),1);//(VALUE*)&pAssoc->value, 1);
	McsDestructElements<KEY>(MCS_GET_OBJ_ADDR(pAssoc->key),1);//(KEY*)&pAssoc->key, 1);
	pAssoc->rawIndex=-1;

	pAssoc->pNext = m_pFreeList;
	pAssoc->nHashValue = -1;
	m_pFreeList = pAssoc;
	m_nCount--;
	MCSASSERT_EX(m_nCount >= 0, return);  // make sure we don't underflow

	// if no more elements, cleanup completely
	if (m_nCount == 0)
		RemoveAll();
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::McsAssoc*
McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetAssocAt(ARG_KEY key, UINT& nHash, bool fAllowGHT) const
// find association (or return NULL)
{
	nHash = McsHashKey<ARG_KEY>(key) % m_nHashTableSize;

	if (m_pHashTable == NULL)
		return NULL;

	// see if it exists
	McsAssoc* pAssoc = NULL;
	int nComparisions = 0; 
	for (pAssoc = m_pHashTable[nHash]; pAssoc; pAssoc = pAssoc->pNext, nComparisions++)
	{
		if(fAllowGHT && nComparisions >= MAP_MAX_COMPARISIONS)
		{
			if(((McsMapEx*)this)->_growHashTableSize())
				return GetAssocAt(key, nHash, true); // recursive

			if(!m_fStripHTOverflowWarning) 
			{
				((McsMapEx*)this)->m_fStripHTOverflowWarning = true;
				#ifdef _DEBUG
					MCSASSERTE("Increase the size of a hash table or optimize a hash function");
				#else
					MESSAGE_ERR_A("Increase the size of a hash table or optimize an McsHashKey function");
				#endif
			}
		}
		if (McsCompareElements(MCS_GET_OBJ_ADDR(pAssoc->key), &key))//(KEY*)&pAssoc->key, &key))
			return pAssoc;
	}
	return NULL;
}
//=============================================================================

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::assocAt(ARG_KEY key, const KEY*& pKey, VALUE*& pValue)
{
	UINT nHash = McsHashKey<ARG_KEY>(key) % m_nHashTableSize;
	McsAssoc* pAssoc = GetAssocAt(key, nHash, false);
	if(pAssoc)
	{
		pKey = MCS_GET_OBJ_ADDR(pAssoc->key);
		pValue = MCS_GET_OBJ_ADDR(pAssoc->value);
		return true;
	}

	pKey = NULL;
	pValue = NULL;
	return false;
}
//=============================================================================

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::Lookup(ARG_KEY key, VALUE& rValue) const
{
	UINT nHash;
	McsAssoc* pAssoc = GetAssocAt(key, nHash, false);
	if (pAssoc == NULL)
		return false;  // not in map

	rValue = pAssoc->value;
	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const VALUE* McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::getExistingValPtr(ARG_KEY key) const
{
	KEY* pStoredKey = NULL;
	VALUE* pStoredVal = NULL;
	
	UINT nHash = 0;
	McsAssoc* pAssoc = NULL;

	if(!(pAssoc = GetAssocAt(key, nHash, false)))
		return NULL;

	//pStoredKey = MCS_GET_OBJ_ADDR(pAssoc->key);
	pStoredVal = MCS_GET_OBJ_ADDR(pAssoc->value);
	return pStoredVal;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const KEY* McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::getExistingKeyPtr(ARG_KEY key) const
{
	KEY* pStoredKey = NULL;
	VALUE* pStoredVal = NULL;
	
	UINT nHash = 0;
	McsAssoc* pAssoc = NULL;

	if(!(pAssoc = GetAssocAt(key, nHash, false)))
		return NULL;

	pStoredKey = MCS_GET_OBJ_ADDR(pAssoc->key);
	return pStoredKey;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE* McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::getExistingValPtr(ARG_KEY key)
{
	KEY* pStoredKey = NULL;
	VALUE* pStoredVal = NULL;
	
	UINT nHash = 0;
	McsAssoc* pAssoc = NULL;

	if(!(pAssoc = GetAssocAt(key, nHash, false)))
		return NULL;

	//pStoredKey = MCS_GET_OBJ_ADDR(pAssoc->key);
	pStoredVal = MCS_GET_OBJ_ADDR(pAssoc->value);
	return pStoredVal;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::getAt(ARG_KEY key, const KEY*& pStoredKey, VALUE*& pStoredVal)
{
	pStoredKey = NULL;
	pStoredVal = NULL;
	
	UINT nHash = 0;
	McsAssoc* pAssoc = NULL;

	if ((pAssoc = GetAssocAt(key, nHash, true)) == NULL)
	{
		if (m_pHashTable == NULL)
			InitHashTable(m_nHashTableSize);

		// it doesn't exist, add a new Association
		pAssoc = NewAssoc();
		pAssoc->nHashValue = nHash;
		pAssoc->key = key;
		// 'pAssoc->value' is a constructed object, nothing more

		// put into hash table
		pAssoc->pNext = m_pHashTable[nHash];
		m_pHashTable[nHash] = pAssoc;
	}

	pStoredKey = MCS_GET_OBJ_ADDR(pAssoc->key);
	pStoredVal = MCS_GET_OBJ_ADDR(pAssoc->value);
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE& McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](ARG_KEY key)
{
	const KEY* pStoredKey = NULL;
	VALUE* pStoredVal = NULL;
	getAt(key, pStoredKey, pStoredVal);
	return *pStoredVal;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE& McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::valueAt(ARG_KEY key)
{
	const KEY* pStoredKey = NULL;
	VALUE* pStoredVal = NULL;
	getAt(key, pStoredKey, pStoredVal);
	return *pStoredVal;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const KEY& McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::keyAt(ARG_KEY key) const
{
	const KEY* pStoredKey = NULL;
	const VALUE* pStoredVal = NULL;
	getAt(key, pStoredKey, pStoredVal);
	return *pStoredKey;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
int McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::getKeys(OUT KeysArray& keys) const
{
	if(keys.physicalLength() < m_nCount)
		keys.setPhysicalLength(m_nCount);
	keys.SetSize(0);
	for(mapidx mi = FirstIdx(); mi < m_nCount; ++mi) {
		keys += (*this).K(mi);
	}
	return m_nCount;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
int McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::getValues(OUT ValuesArr& vals) const
{
	if(vals.physicalLength() < m_nCount)
		vals.setPhysicalLength(m_nCount);
	vals.SetSize(0);
	for(mapidx mi = FirstIdx(); mi < m_nCount; ++mi) {
		vals += (*this).V(mi);
	}
	return m_nCount;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::RemoveKey(ARG_KEY key)
// remove key - return TRUE if removed
{
	if (m_pHashTable == NULL)
		return FALSE;  // nothing in the table

	McsAssoc** ppAssocPrev;
	ppAssocPrev = &m_pHashTable[McsHashKey<ARG_KEY>(key) % m_nHashTableSize];

	McsAssoc* pAssoc;
	for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (McsCompareElements(MCS_GET_OBJ_ADDR(pAssoc->key), &key))//(KEY*)&pAssoc->key, &key))
		{
			// remove it
			*ppAssocPrev = pAssoc->pNext;  // remove from list
			FreeAssoc(pAssoc);
			return TRUE;
		}
		ppAssocPrev = &pAssoc->pNext;
	}
	return FALSE;  // not found
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextAssoc
(MCSPOSITION& rNextPosition, 
 KEY& rKey, 
 VALUE& rValue) const
{
	const KEY* pk = NULL;
	const VALUE* pv = NULL;
	GetNextAssoc(rNextPosition, pk, pv);
	if(pk || pv) {
		rKey = *pk;
		rValue = *pv;
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextAssoc
(MCSPOSITION& rNextPosition, 
 KEY*&        pKey, 
 VALUE*&      pValue)
{
	pKey = NULL;
	pValue = NULL;
	MCSASSERT_EX(m_pHashTable != NULL, return);  // never call on empty map

	McsAssoc* pAssocRet = (McsAssoc*)rNextPosition;
	MCSASSERT_EX(pAssocRet != NULL, return);

	if (pAssocRet == (McsAssoc*) MCS_BEFORE_START_POSITION)
	{
		// find the first association
		for (int nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
				break;
		MCSASSERT_EX(pAssocRet != NULL, return);  // must find something
	}

	// find next association
	//MCSASSERT(McsIsValidAddress(pAssocRet, sizeof(McsAssoc)));
	McsAssoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL)
	{
		// go to next bucket
		for (int nBucket = pAssocRet->nHashValue + 1;
			nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
				break;
	}

	rNextPosition = (MCSPOSITION) pAssocNext;

	// fill in return data
	pKey = MCS_GET_OBJ_ADDR(pAssocRet->key); // (KEY*)&pAssocRet->key;
	pValue = MCS_GET_OBJ_ADDR(pAssocRet->value); // (VALUE*)&pAssocRet->value;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextKey(MCSPOSITION& rNextPosition, KEY& rKey) const
{
	VALUE Val;
	GetNextAssoc(rNextPosition, rKey, Val);
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextKey(MCSPOSITION& rNextPosition, KEY*& pKey)
{
	VALUE* pVal;
	GetNextAssoc(rNextPosition, pKey, pVal);
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextValue(MCSPOSITION& rNextPosition, VALUE& rVal) const
{
	KEY Key;
	GetNextAssoc(rNextPosition, Key, rVal);
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextValue(MCSPOSITION& rNextPosition, VALUE*& pVal)
{
	KEY* pKey;
	GetNextAssoc(rNextPosition, pKey, pVal);
}
//=============================================================================



///////////////////////////////////////////////////////////////////////////////
//=============================================================================
// McsList
//=============================================================================
template<class TYPE, class ARG_TYPE = const TYPE&>
class McsList
{
protected:
	struct McsNode
	{
		McsNode* pNext;
		McsNode* pPrev;
		TYPE data;
	};

	McsNode* m_pNodeHead;
	McsNode* m_pNodeTail;
	INT_PTR m_nCount;
	McsNode* m_pNodeFree;
	struct McsPlex* m_pBlocks;
	INT_PTR m_nBlockSize;

	McsNode* NewNode(McsNode*, McsNode*);
	void FreeNode(McsNode*);

public:
	McsList(INT_PTR nBlockSize = 10);
	~McsList();

	// count of elements
	INT_PTR GetCount() const;
	INT_PTR GetSize() const;
	bool IsEmpty() const;

	McsList& operator = (const McsList& other);

	// peek at head or tail
	TYPE& GetHead();
	const TYPE& GetHead() const;
	TYPE& GetTail();
	const TYPE& GetTail() const;

	// Operations
	// get head or tail (and remove it) - don't call on empty list !
	TYPE RemoveHead();
	TYPE RemoveTail();

	// add before head or after tail
	MCSPOSITION AddHead(ARG_TYPE newElement);
	MCSPOSITION AddTail(ARG_TYPE newElement);

	// add another list of elements before head or after tail
	void AddHead(const McsList* pNewList);
	void AddTail(const McsList* pNewList);

	// remove all elements
	void RemoveAll();

	// iteration
	MCSPOSITION GetHeadPosition() const;
	MCSPOSITION GetTailPosition() const;
	MCSPOSITION GetNextPosition(MCSPOSITION position);
	MCSPOSITION GetPrevPosition(MCSPOSITION position);
	TYPE& GetNext(MCSPOSITION& position); // return *position++
	const TYPE& GetNext(MCSPOSITION& position) const; // return *position++
	TYPE& GetPrev(MCSPOSITION& position); // return *position--
	const TYPE& GetPrev(MCSPOSITION& position) const; // return *position--

	// getting/modifying an element at a given position
	TYPE& GetAt(MCSPOSITION position);
	const TYPE& GetAt(MCSPOSITION position) const;
	void SetAt(MCSPOSITION pos, ARG_TYPE newElement);
	void RemoveAt(MCSPOSITION position);

	// inserting before or after a given position
	MCSPOSITION InsertBefore(MCSPOSITION position, ARG_TYPE newElement);
	MCSPOSITION InsertAfter(MCSPOSITION position, ARG_TYPE newElement);

	// moving before or after a given position
	void MovePositionBefore(MCSPOSITION position, MCSPOSITION fromPosition);
	void MovePositionAfter(MCSPOSITION position, MCSPOSITION fromPosition);

	// helper functions (note: O(n) speed)
	// defaults to starting at the HEAD, return NULL if not found
	MCSPOSITION Find(ARG_TYPE searchValue, MCSPOSITION startAfter = NULL) const;

	// get the 'nIndex'th element (may return NULL)
	MCSPOSITION FindIndex(INT_PTR nIndex) const;
};
//=============================================================================
template<class TYPE, class ARG_TYPE>
__inline INT_PTR McsList<TYPE, ARG_TYPE>::GetCount() const
	{ return m_nCount; }
template<class TYPE, class ARG_TYPE>
__inline INT_PTR McsList<TYPE, ARG_TYPE>::GetSize() const
	{ return m_nCount; }
template<class TYPE, class ARG_TYPE>
__inline bool McsList<TYPE, ARG_TYPE>::IsEmpty() const
	{ return m_nCount == 0; }
template<class TYPE, class ARG_TYPE>
__inline TYPE& McsList<TYPE, ARG_TYPE>::GetHead()
	{ MCSASSERT(m_pNodeHead != NULL); return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
__inline const TYPE& McsList<TYPE, ARG_TYPE>::GetHead() const
	{ MCSASSERT(m_pNodeHead != NULL); return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
__inline TYPE& McsList<TYPE, ARG_TYPE>::GetTail()
	{ MCSASSERT(m_pNodeTail != NULL); return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
__inline const TYPE& McsList<TYPE, ARG_TYPE>::GetTail() const
	{ MCSASSERT(m_pNodeTail != NULL); return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
__inline MCSPOSITION McsList<TYPE, ARG_TYPE>::GetHeadPosition() const
	{ return (MCSPOSITION)m_pNodeHead; }
template<class TYPE, class ARG_TYPE>
__inline MCSPOSITION McsList<TYPE, ARG_TYPE>::GetTailPosition() const
	{ return (MCSPOSITION)m_pNodeTail; }
//=============================================================================
template<class TYPE, class ARG_TYPE>
__inline MCSPOSITION McsList<TYPE, ARG_TYPE>::GetNextPosition(MCSPOSITION position)
{
	if(position == NULL)
		return (MCSPOSITION)m_pNodeHead;
	McsNode* pNode = (McsNode*)position;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	return (MCSPOSITION)pNode->pNext;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
__inline MCSPOSITION McsList<TYPE, ARG_TYPE>::GetPrevPosition(MCSPOSITION position)
{
	if(position == NULL)
		return (MCSPOSITION)m_pNodeTail;
	McsNode* pNode = (McsNode*)position;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	return (MCSPOSITION)pNode->pPrev;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
__inline TYPE& McsList<TYPE, ARG_TYPE>::GetNext(MCSPOSITION& position) // return *Position++
{
	McsNode* pNode = (McsNode*)position;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	position = (MCSPOSITION)pNode->pNext;
	return pNode->data;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
__inline const TYPE& McsList<TYPE, ARG_TYPE>::GetNext(MCSPOSITION& position) const // return *Position++
{
	McsNode* pNode = (McsNode*)position;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	position = (MCSPOSITION)pNode->pNext;
	return pNode->data;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
__inline TYPE& McsList<TYPE, ARG_TYPE>::GetPrev(MCSPOSITION& position) // return *Position--
{
	McsNode* pNode = (McsNode*)position;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	position = (MCSPOSITION)pNode->pPrev;
	return pNode->data;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
__inline const TYPE& McsList<TYPE, ARG_TYPE>::GetPrev(MCSPOSITION& position) const // return *Position--
{
	McsNode* pNode = (McsNode*)position;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	position = (MCSPOSITION)pNode->pPrev;
	return pNode->data;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
__inline TYPE& McsList<TYPE, ARG_TYPE>::GetAt(MCSPOSITION position)
{
	McsNode* pNode = (McsNode*)position;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	return pNode->data;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
__inline const TYPE& McsList<TYPE, ARG_TYPE>::GetAt(MCSPOSITION position) const
{
	McsNode* pNode = (McsNode*)position;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	return pNode->data;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
__inline void McsList<TYPE, ARG_TYPE>::SetAt(MCSPOSITION pos, ARG_TYPE newElement)
{
	McsNode* pNode = (McsNode*)pos;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	pNode->data = newElement;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
McsList<TYPE, ARG_TYPE>::McsList(INT_PTR nBlockSize)
{
	MCSASSERT(nBlockSize > 0);
	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
void McsList<TYPE, ARG_TYPE>::RemoveAll()
{
	McsNode* pNode;
	for(pNode = m_pNodeHead; pNode != NULL; pNode = pNode->pNext)
		pNode->data.~TYPE();
	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}
//=============================================================================

template<class TYPE, class ARG_TYPE>
McsList<TYPE, ARG_TYPE>& McsList<TYPE, ARG_TYPE>::operator = (const McsList<TYPE, ARG_TYPE>& other)
{
	if(this == &other)
		return *this;
	RemoveAll();
	AddTail(&other);
	return *this;
}
//=============================================================================

template<class TYPE, class ARG_TYPE>
McsList<TYPE, ARG_TYPE>::~McsList()
{
	RemoveAll();
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
typename McsList<TYPE, ARG_TYPE>::McsNode* McsList<TYPE, ARG_TYPE>::NewNode(McsNode* pPrev, McsNode* pNext)
{
	if(m_pNodeFree == NULL)
	{
		// add another block
		McsPlex *pNewBlock = McsPlex::Create(m_pBlocks, m_nBlockSize, sizeof(McsNode));
		// chain them into free list
		McsNode *pNode = (McsNode*)pNewBlock->data();
		// free in reverse order to make it easier to debug
		pNode += m_nBlockSize - 1;
		for(INT_PTR i = m_nBlockSize-1; i >= 0; i--, pNode--)
		{
			pNode->pNext = m_pNodeFree;
			m_pNodeFree = pNode;
		}
	}
	MCSASSERT(m_pNodeFree != NULL);  // we must have something
	McsList::McsNode *pNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNode->pPrev = pPrev;
	pNode->pNext = pNext;
	m_nCount++;
	MCSASSERT(m_nCount > 0);  // make sure we don't overflow
	McsConstructElements<TYPE>(MCS_GET_OBJ_ADDR(pNode->data), 1);
	return pNode;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
void McsList<TYPE, ARG_TYPE>::FreeNode(McsNode* pNode)
{
	McsDestructElements<TYPE>(MCS_GET_OBJ_ADDR(pNode->data), 1);
	pNode->pNext = m_pNodeFree;
	m_pNodeFree = pNode;
	m_nCount--;
	MCSASSERT(m_nCount >= 0);  // make sure we don't underflow
	// if no more elements, cleanup completely
	if(m_nCount == 0)
		RemoveAll();
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
MCSPOSITION McsList<TYPE, ARG_TYPE>::AddHead(ARG_TYPE newElement)
{
	McsNode *pNewNode = NewNode(NULL, m_pNodeHead);
	pNewNode->data = newElement;
	if(m_pNodeHead != NULL)
		m_pNodeHead->pPrev = pNewNode;
	else
		m_pNodeTail = pNewNode;
	m_pNodeHead = pNewNode;
	return (MCSPOSITION)pNewNode;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
MCSPOSITION McsList<TYPE, ARG_TYPE>::AddTail(ARG_TYPE newElement)
{
	McsNode *pNewNode = NewNode(m_pNodeTail, NULL);
	pNewNode->data = newElement;
	if(m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;
	m_pNodeTail = pNewNode;
	return (MCSPOSITION)pNewNode;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
void McsList<TYPE, ARG_TYPE>::AddHead(const McsList* pNewList)
{
	MCSASSERT(pNewList != NULL);
	// add a list of same elements to head (maintain order)
	MCSPOSITION pos = pNewList->GetTailPosition();
	while(pos != NULL)
		AddHead(pNewList->GetPrev(pos));
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
void McsList<TYPE, ARG_TYPE>::AddTail(const McsList* pNewList)
{
	MCSASSERT(pNewList != NULL);
	// add a list of same elements
	MCSPOSITION pos = pNewList->GetHeadPosition();
	while(pos != NULL)
		AddTail(pNewList->GetNext(pos));
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
TYPE McsList<TYPE, ARG_TYPE>::RemoveHead()
{
	MCSASSERT(McsIsValidAddress(m_pNodeHead, sizeof(McsNode)));
	McsNode *pOldNode = m_pNodeHead;
	TYPE returnValue = pOldNode->data;
	m_pNodeHead = pOldNode->pNext;
	if(m_pNodeHead != NULL)
		m_pNodeHead->pPrev = NULL;
	else
		m_pNodeTail = NULL;
	FreeNode(pOldNode);
	return returnValue;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
TYPE McsList<TYPE, ARG_TYPE>::RemoveTail()
{
	MCSASSERT(McsIsValidAddress(m_pNodeTail, sizeof(McsNode)));
	McsNode *pOldNode = m_pNodeTail;
	TYPE returnValue = pOldNode->data;
	m_pNodeTail = pOldNode->pPrev;
	if(m_pNodeTail != NULL)
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;
	FreeNode(pOldNode);
	return returnValue;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
MCSPOSITION McsList<TYPE, ARG_TYPE>::InsertBefore(MCSPOSITION position, ARG_TYPE newElement)
{
	if(position == NULL)
		return AddHead(newElement); // insert before nothing -> head of the list
	// Insert it before position
	McsNode *pOldNode = (McsNode*)position;
	McsNode *pNewNode = NewNode(pOldNode->pPrev, pOldNode);
	pNewNode->data = newElement;
	if(pOldNode->pPrev != NULL)
	{
		MCSASSERT(McsIsValidAddress(pOldNode->pPrev, sizeof(McsNode)));
		pOldNode->pPrev->pNext = pNewNode;
	}
	else
	{
		MCSASSERT(pOldNode == m_pNodeHead);
		m_pNodeHead = pNewNode;
	}
	pOldNode->pPrev = pNewNode;
	return (MCSPOSITION)pNewNode;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
MCSPOSITION McsList<TYPE, ARG_TYPE>::InsertAfter(MCSPOSITION position, ARG_TYPE newElement)
{
	if(position == NULL)
		return AddTail(newElement); // insert after nothing -> tail of the list

	// Insert it before position
	McsNode *pOldNode = (McsNode*)position;
	MCSASSERT(McsIsValidAddress(pOldNode, sizeof(McsNode)));
	McsNode *pNewNode = NewNode(pOldNode, pOldNode->pNext);
	pNewNode->data = newElement;
	if(pOldNode->pNext != NULL)
	{
		MCSASSERT(McsIsValidAddress(pOldNode->pNext, sizeof(McsNode)));
		pOldNode->pNext->pPrev = pNewNode;
	}
	else
	{
		MCSASSERT(pOldNode == m_pNodeTail);
		m_pNodeTail = pNewNode;
	}
	pOldNode->pNext = pNewNode;
	return (MCSPOSITION)pNewNode;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
void McsList<TYPE, ARG_TYPE>::MovePositionBefore(MCSPOSITION position, MCSPOSITION fromPosition)
{
	if(position == fromPosition)
		return;
	McsNode *pNode = (McsNode*)fromPosition;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	// remove pNode from list
	if(pNode == m_pNodeHead)
	{
		m_pNodeHead = pNode->pNext;
	}
	else
	{
		MCSASSERT(McsIsValidAddress(pNode->pPrev, sizeof(McsNode)));
		pNode->pPrev->pNext = pNode->pNext;
	}
	if(pNode == m_pNodeTail)
	{
		m_pNodeTail = pNode->pPrev;
	}
	else
	{
		MCSASSERT(McsIsValidAddress(pNode->pNext, sizeof(McsNode)));
		pNode->pNext->pPrev = pNode->pPrev;
	}

	if(position == NULL)
	{
		if(m_pNodeHead != NULL)
			m_pNodeHead->pPrev = pNode;
		else
			m_pNodeTail = pNode;
		m_pNodeHead = pNode;
	}
	else
	{
		McsNode *pOldNode = (McsNode*)position;
		pNode->pPrev = pOldNode->pPrev;
		pNode->pNext = pOldNode;
		if(pOldNode->pPrev != NULL)
		{
			MCSASSERT(McsIsValidAddress(pOldNode->pPrev, sizeof(McsNode)));
			pOldNode->pPrev->pNext = pNode;
		}
		else
		{
			MCSASSERT(pOldNode == m_pNodeHead);
			m_pNodeHead = pNode;
		}
		pOldNode->pPrev = pNode;
	}
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
void McsList<TYPE, ARG_TYPE>::MovePositionAfter(MCSPOSITION position, MCSPOSITION fromPosition)
{
	if(position == fromPosition)
		return;
	McsNode *pNode = (McsNode*)fromPosition;
	MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
	// remove pNode from list
	if(pNode == m_pNodeHead)
	{
		m_pNodeHead = pNode->pNext;
	}
	else
	{
		MCSASSERT(McsIsValidAddress(pNode->pPrev, sizeof(McsNode)));
		pNode->pPrev->pNext = pNode->pNext;
	}
	if(pNode == m_pNodeTail)
	{
		m_pNodeTail = pNode->pPrev;
	}
	else
	{
		MCSASSERT(McsIsValidAddress(pNode->pNext, sizeof(McsNode)));
		pNode->pNext->pPrev = pNode->pPrev;
	}

	if(position == NULL)
	{
		if(m_pNodeTail != NULL)
			m_pNodeTail->pNext = pNode;
		else
			m_pNodeHead = pNode;
		m_pNodeTail = pNode;
	}
	else
	{
		McsNode *pOldNode = (McsNode*)position;
		pNode->pPrev = pOldNode;
		pNode->pNext = pOldNode->pNext;
		if(pOldNode->pNext != NULL)
		{
			MCSASSERT(McsIsValidAddress(pOldNode->pNext, sizeof(McsNode)));
			pOldNode->pNext->pPrev = pNode;
		}
		else
		{
			MCSASSERT(pOldNode == m_pNodeTail);
			m_pNodeTail = pNode;
		}
		pOldNode->pNext = pNode;
	}
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
void McsList<TYPE, ARG_TYPE>::RemoveAt(MCSPOSITION position)
{
	McsNode *pOldNode = (McsNode*)position;
	MCSASSERT(McsIsValidAddress(pOldNode, sizeof(McsNode)));
	// remove pOldNode from list
	if(pOldNode == m_pNodeHead)
	{
		m_pNodeHead = pOldNode->pNext;
	}
	else
	{
		MCSASSERT(McsIsValidAddress(pOldNode->pPrev, sizeof(McsNode)));
		pOldNode->pPrev->pNext = pOldNode->pNext;
	}
	if(pOldNode == m_pNodeTail)
	{
		m_pNodeTail = pOldNode->pPrev;
	}
	else
	{
		MCSASSERT(McsIsValidAddress(pOldNode->pNext, sizeof(McsNode)));
		pOldNode->pNext->pPrev = pOldNode->pPrev;
	}
	FreeNode(pOldNode);
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
MCSPOSITION McsList<TYPE, ARG_TYPE>::FindIndex(INT_PTR nIndex) const
{
	if(nIndex >= m_nCount || nIndex < 0)
		return NULL;  // went too far
	McsNode *pNode = m_pNodeHead;
	while(nIndex--)
	{
		MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
		pNode = pNode->pNext;
	}
	return (MCSPOSITION)pNode;
}
//=============================================================================
template<class TYPE, class ARG_TYPE>
MCSPOSITION McsList<TYPE, ARG_TYPE>::Find(ARG_TYPE searchValue, MCSPOSITION startAfter) const
{
	McsNode *pNode = (McsNode*)startAfter;
	if(pNode == NULL)
	{
		pNode = m_pNodeHead;  // start at head
	}
	else
	{
		MCSASSERT(McsIsValidAddress(pNode, sizeof(McsNode)));
		pNode = pNode->pNext;  // start after the one specified
	}
	for(; pNode != NULL; pNode = pNode->pNext)
		if(CompareElements<TYPE>(&pNode->data, &searchValue))
			return (MCSPOSITION)pNode;
	return NULL;
}
//=============================================================================



//=============================================================================
__inline bool McsIsValidAddress(const void* lp, UINT_PTR nBytes, bool bReadWrite = true)
{
	return NULL != lp;

	//// simple version using Win-32 APIs for pointer validation.
	//return (lp != NULL && !IsBadReadPtr(lp, nBytes) &&
	//	      (!bReadWrite || !IsBadWritePtr((LPVOID)lp, nBytes)));
}
//=============================================================================


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// STRINGS //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#ifdef _MT_STR_ORDINAL
  #undef MT_API
  #define MT_API
#endif

//=============================================================================
// Globals
extern MT_API char mcsChNil;
MT_API const McsStringA& McsGetEmptyStringA();
MT_API const McsStringW& McsGetEmptyStringW();
#define mcsEmptyStringA McsGetEmptyStringA()
#define mcsEmptyStringW McsGetEmptyStringW()
struct McsStringDataA;
struct McsStringDataW;
struct McsStringData;

#ifndef _UNICODE
	#define McsString         McsStringA
	#define McsGetEmptyString McsGetEmptyStringA
	#define mcsEmptyString    mcsEmptyStringA
	#define McsStringData     McsStringDataA
#else
	#define McsString         McsStringW
	#define McsGetEmptyString McsGetEmptyStringW
	#define mcsEmptyString    mcsEmptyStringW
	#define McsStringData     McsStringDataW
#endif

template <> MT_API UINT __stdcall McsHashKey(LPCWSTR key);
template <> MT_API UINT __stdcall McsHashKey(LPCSTR key);
template <> MT_API void __stdcall McsConstructElements(McsStringA* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsConstructElements(McsStringW* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsDestructElements(McsStringA* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsDestructElements(McsStringW* pElements, INT_PTR nCount);
template <> MT_API void __stdcall McsCopyElements(McsStringA* pDest, const McsStringA* pSrc, INT_PTR nCount);
template <> MT_API void __stdcall McsCopyElements(McsStringW* pDest, const McsStringW* pSrc, INT_PTR nCount);

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// ANSI McsString ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//=============================================================================
MT_API bool isPtrAnMcsStringA(LPCSTR);
MT_API bool isPtrAnMcsStringW(LPCWSTR);

//=============================================================================
#pragma pack(push, 1)
struct McsStringDataA
{
	//DECLARE_OBJ_NEWDEL;
	long  nRefs;          // reference count
	int   nDataLength;    // length of data (including terminator)
	int   nAllocLength;   // length of allocation
	// char data[nAllocLength]

	char* data()           // CHAR* to managed data
		{ return (char*)(this+1); }
};
#pragma pack(pop)

class _bstr_t;
class _variant_t;
//=============================================================================
class McsStringA
{
public:
// Constructors

	DECLARE_OBJ_NEWDEL;

	McsStringA();
	MT_API McsStringA(const McsStringA& stringSrc);
	explicit MT_API McsStringA(CHAR ch, INT_PTR nRepeat = 1); // explicit is required to prevent implicit strings creation from 'bool'
	MT_API McsStringA(LPCSTR lpsz, HINSTANCE hInst = NULL);
	MT_API McsStringA(LPCSTR lpch, INT_PTR nLength);

#if defined(_AFX) && !defined(_UNICODE)
	McsStringA& operator = (const CString& str);
	bool operator == (const CString& str) const;
	bool operator != (const CString& str) const;
#endif
// Attributes & Operations

	// get data length
	MT_API int GetLength() const;
	// TRUE if zero length
	bool IsEmpty() const;
	// clear contents to empty
	MT_API void Empty();

	// return single character at zero-based index
	CHAR GetAt(INT_PTR nIndex) const;
	CHAR& CharAt(INT_PTR nIndex);

	// return single character at zero-based index
	CHAR operator[](long nIndex) const {return GetAt(nIndex);}
	CHAR& operator[](long nIndex) {return CharAt(nIndex);}
	CHAR operator[](int nIndex) const {return GetAt(nIndex);}
	CHAR& operator[](int nIndex) {return CharAt(nIndex);}

#ifdef WIN64
	CHAR operator[](INT_PTR nIndex) const;
	CHAR& operator[](INT_PTR nIndex);
	CHAR operator[](DWORD nIndex) const {return GetAt(nIndex);}
	CHAR& operator[](DWORD nIndex) {return CharAt(nIndex);}
#endif

	// set a single character at zero-based index
	MT_API void SetAt(INT_PTR nIndex, char ch);
	// return pointer to const string
	MT_API operator LPCSTR() const;

	// overloaded assignment

	// ref-counted copy from another McsStringA
	MT_API const McsStringA& operator=(const McsStringA& stringSrc);
	MT_API const McsStringA& operator=(char ch);
	// copy string content from ANSI string (converts to char)
	MT_API const McsStringA& operator=(LPCSTR lpsz);

	MT_API operator _bstr_t() const;
	MT_API operator _variant_t() const;
	//MT_API const McsStringA& operator=(BSTR bstr);
	MT_API const McsStringA& operator=(const _bstr_t& bstrt);
	//MT_API const McsStringA& operator=(const VARIANT& variant);
	//MT_API const McsStringA& operator=(const _variant_t& variantt);

	// string concatenation

	// concatenate from another McsStringA
	MT_API const McsStringA& operator+=(const McsStringA& string);
	// concatenate an ANSI character after converting it to char
	MT_API const McsStringA& operator+=(char ch);
	// concatenate a UNICODE character after converting it to char
	MT_API const McsStringA& operator+=(LPCSTR lpsz);

	friend McsStringA MT_API operator+(const McsStringA& string1, const McsStringA& string2);
	friend McsStringA MT_API operator+(const McsStringA& string, char ch);
	friend McsStringA MT_API operator+(char ch, const McsStringA& string);
	friend McsStringA MT_API operator+(const McsStringA& string, LPCSTR lpsz);
	friend McsStringA MT_API operator+(LPCSTR lpsz, const McsStringA& string);

	// string comparison

	// straight character comparison
	int Compare(LPCSTR lpsz) const;
	bool IsEqual(const McsStringA& str) const;
	// compare ignoring case
	int CompareNoCase(LPCSTR lpsz) const;
	// NLS aware comparison, case sensitive
	int Collate(LPCSTR lpsz) const;
	// NLS aware comparison, case insensitive
	int CollateNoCase(LPCSTR lpsz) const;

	// simple sub-string extraction

	// return nCount characters starting at zero-based nFirst
	MT_API McsStringA Mid(INT_PTR nFirst, INT_PTR nCount) const;
	// return all characters starting at zero-based nFirst
	MT_API McsStringA Mid(INT_PTR nFirst) const;
	// return first nCount characters in string
	MT_API McsStringA Left(INT_PTR nCount) const;
	// return nCount characters from end of string
	MT_API McsStringA Right(INT_PTR nCount) const;

	MT_API McsStringA& RemoveLeft(INT_PTR nCount); // removes first nCount characters in string
	MT_API McsStringA& RemoveRight(INT_PTR nCount); // removes last nCount characters in string
	MT_API long       asLong() const;
	MT_API INT_PTR    asLongPtr() const;
	MT_API double     asDouble() const;
	MT_API double     asDoubleEx(LPCSTR decimalSeparators = ".,") const; // slow
	MT_API bool       isaLong() const;
	MT_API bool       isaLongPtr() const;
	MT_API bool       isaDouble() const;
	MT_API int        ComparePart(LPCSTR str,INT_PTR nChars) const;
	MT_API int        ComparePartNoCase(LPCSTR str,INT_PTR nChars) const;
	MT_API int        CompareDgt(LPCSTR lpsz) const;
	MT_API int        CompareDgtNoCase(LPCSTR lpsz) const;

		// (!) internally not uses "strtok" function so you can safely use it 
		// returns number of extracted strings 
	MT_API int        Split(IN LPCSTR cstrDelimitersChars, OUT mcsStringArrayA& subStrings) const;

		// this version can split string with substrings enclosed into brackets with
		// <bracketsChar> char.
		// Ex: McsString("aaa 'qwe 222' '44'").SplitEx(" ", "'", ...); will give
		// 3 strings: "aaa" "qwe 222" and "44"
	MT_API int SplitEx(
		IN LPCSTR cstrDelimitersChars, 
		IN OPTIONAL char bracketsChar, 
		OUT mcsStringArrayA& subStrings, 
		IN OPTIONAL bool fRemoveBrackets = true,
		IN OPTIONAL char escapeSqwChar = 0, // most frequently used - '\\' 
		IN OPTIONAL bool fRemoveSqwChars = false) const;

		// returns number of total removed characters
	MT_API int        Trim(IN LPCSTR charactersToTrim);
	MT_API McsStringW asUnicode(UINT CodePage=GetACP()) const;
	       McsStringA asMB(UINT CodePage=GetACP()) const {return *this;}

	#ifndef _UNICODE
		McsString  asT(UINT CodePage=GetACP()) const{return *this;}
	#else
		McsString  asT(UINT CodePage=GetACP()) const;
	#endif
	//......................................................................................

	//  characters from beginning that are also in passed string
	MT_API McsStringA SpanIncluding(LPCSTR lpszCharSet) const;
	// characters from beginning that are not also in passed string
	MT_API McsStringA SpanExcluding(LPCSTR lpszCharSet) const;

	// upper/lower/reverse conversion

	// NLS aware conversion to uppercase
	MT_API void MakeUpper();
	// NLS aware conversion to lowercase
	MT_API void MakeLower();
	// reverse string right-to-left
	MT_API void MakeReverse();

	// trimming whitespace (either side)

	// remove whitespace starting from right edge
	MT_API void TrimRight();
	// remove whitespace starting from left side
	MT_API void TrimLeft();

	// trimming anything (either side)

	// remove continuous occurrences of chTarget starting from right
	MT_API void TrimRight(char chTarget);
	// remove continuous occurrences of characters in passed string,
	// starting from right
	MT_API void TrimRight(LPCSTR lpszTargets);
	// remove continuous occurrences of chTarget starting from left
	MT_API void TrimLeft(char chTarget);
	// remove continuous occurrences of characters in
	// passed string, starting from left
	MT_API void TrimLeft(LPCSTR lpszTargets);

	// advanced manipulation

	// replace occurrences of chOld with chNew
	MT_API int Replace(char chOld, char chNew);
	// replace occurrences of substring lpszOld with lpszNew;
	// empty lpszNew removes instances of lpszOld
	MT_API int Replace(LPCSTR lpszOld, LPCSTR lpszNew);
	MT_API int Replace(LPCSTR lpszOld, LPCSTR lpszNew, void* pStringsComparator);
	MT_API int ReplaceNoCase(LPCSTR lpszOld, LPCSTR lpszNew);
	// remove occurrences of chRemove
	MT_API int Remove(char chRemove);
	// insert character at zero-based index; concatenates
	// if index is past end of string
	MT_API int Insert(INT_PTR nIndex, char ch);
	// insert substring at zero-based index; concatenates
	// if index is past end of string
	MT_API int Insert(INT_PTR nIndex, LPCSTR pstr);
	// delete nCount characters starting at zero-based index
	MT_API int Delete(INT_PTR nIndex, INT_PTR nCount = 1);

	// searching

	// find character starting at left, -1 if not found
	MT_API int Find(char ch) const;
	// find character starting at right
	MT_API int ReverseFind(char ch) const;
	// find character starting at zero-based index and going right
	MT_API int Find(char ch, INT_PTR nStart) const;
	// find first instance of any character in passed string
	MT_API int FindOneOf(LPCSTR lpszCharSet) const;
	// find first instance of substring starting at zero-based index
	MT_API int Find(LPCSTR lpszSub) const;
	MT_API int Find(LPCSTR lpszSub, INT_PTR nStart) const;
	MT_API int Find(LPCSTR lpszSub, INT_PTR nStart, void* pStringsComparator) const;
	MT_API int FindNoCase(LPCSTR lpszSub, INT_PTR nStart=0) const;

	// simple formatting

	// printf-like formatting using passed string
	MT_API McsStringA& __cdecl Format(LPCSTR lpszFormat, ...);
	MT_API McsStringA& __cdecl FormatD(LPCSTR lpszFormat, ...); // use '.' as decimal delimiter
	// printf-like formatting using referenced string resource
	MT_API McsStringA& __cdecl Format(HINSTANCE hInst,UINT nFormatID, ...);
	MT_API McsStringA& __cdecl FormatD(HINSTANCE hInst,UINT nFormatID, ...); // use '.' as decimal delimiter
	// printf-like formatting using variable arguments parameter
	MT_API McsStringA& FormatV(LPCSTR lpszFormat, va_list argList);
	MT_API McsStringA& FormatVD(LPCSTR lpszFormat, va_list argList); // use '.' as decimal delimiter
	// printf-like formatting using variable arguments parameter
	MT_API McsStringA& FormatVEx(LPCSTR lpszFormat, bool fForceDot, va_list argList);

	// formatting for localization (uses FormatMessage API)

	// format using FormatMessage API on passed string
	MT_API void __cdecl FormatMessage(LPCSTR lpszFormat, ...);
	// format using FormatMessage API on referenced string resource
	MT_API void __cdecl FormatMessage(HINSTANCE hInst,UINT nFormatID, ...);

	// load from string resource
	MT_API bool LoadString(HINSTANCE hInst,UINT nID);
// #ifdef UNICODE
// 	MT_API bool LoadStringA(HINSTANCE hInst,UINT nID)
// 		{return LoadStringW(hInst, nID);}
// 	MT_API bool LoadString(HINSTANCE hInst,UINT nID); // в LIB будет LoadStringW
// #else
// 	MT_API bool LoadStringW(HINSTANCE hInst,UINT nID)
// 		{return LoadStringA(hInst, nID);}
// 	MT_API bool LoadString(HINSTANCE hInst,UINT nID); // в LIB будет LoadStringA
// #endif

	// Access to string implementation buffer as "C" character array

	// get pointer to modifiable buffer at least as long as nMinBufLength
	MT_API LPSTR GetBuffer(INT_PTR nMinBufLength);
	// release buffer, setting length to nNewLength (or to first null if -1)
	MT_API void ReleaseBuffer(INT_PTR nNewLength = -1);
	// get pointer to modifiable buffer exactly as long as nNewLength
	MT_API LPSTR GetBufferSetLength(INT_PTR nNewLength);
	
	// release memory allocated to but unused by string
	void FreeExtra();

	// Use LockBuffer/UnlockBuffer to turn ref counting off

	// turn ref counting back on
	MT_API LPSTR LockBuffer();
	// turn ref counting off
	MT_API void UnlockBuffer();

  void Duplicate(const McsStringA& str);

// Implementation
public:
	MT_API ~McsStringA();
	int GetAllocLength() const;

protected:

#ifdef _MCEYE
public:
#endif

	LPSTR m_pchData;   // pointer to ref counted string data

	// implementation helpers
	McsStringDataA* GetData() const;
	void Init();
	MT_API void AllocCopy(McsStringA& dest, INT_PTR nCopyLen, INT_PTR nCopyIndex, INT_PTR nExtraLen) const;
	MT_API void AllocBuffer(INT_PTR nLen);
	MT_API void AssignCopy(INT_PTR nSrcLen, LPCSTR lpszSrcData);
	MT_API void ConcatCopy(INT_PTR nSrc1Len, LPCSTR lpszSrc1Data, INT_PTR nSrc2Len, LPCSTR lpszSrc2Data);
	MT_API void ConcatInPlace(INT_PTR nSrcLen, LPCSTR lpszSrcData);
	MT_API void CopyBeforeWrite();
	MT_API void AllocBeforeWrite(INT_PTR nLen);
	MT_API void Release();
	MT_API static void Release(McsStringDataA* pData);
	static int SafeStrlen(LPCSTR lpsz);
	MT_API static void FreeData(McsStringDataA* pData);
};
//=============================================================================
// Compare helpers

// Запретил сравнение с CHAR, т.к. к нему автоматически приводится сравнение строки с целым числом
// __inline bool operator==(const McsStringA& s, CHAR c)
// {
// 	int len = s.GetLength();
// 	if(len <= 1 && ((LPCSTR)s)[0]==c)
// 		return true;
// 	return false;
// }
// __inline bool operator==(CHAR c, const McsStringA& s)
// {
// 	int len = s.GetLength();
// 	if(len <= 1 && ((LPCSTR)s)[0]==c)
// 		return true;
// 	return false;
// }
// __inline bool operator!=(const McsStringA& s, CHAR c)
// 	{ return !(s == c); }
// __inline bool operator!=(CHAR c, const McsStringA& s)
// 	{ return !(c == s); }

__inline bool operator==(const McsStringA& s1, const McsStringA& s2)
	{ return s1.IsEqual(s2); }
__inline bool operator==(const McsStringA& s1, LPCSTR s2)
	{ return s1.Compare(s2) == 0; }
__inline bool operator==(LPCSTR s1, const McsStringA& s2)
	{ return s2.Compare(s1) == 0; }
__inline bool operator!=(const McsStringA& s1, const McsStringA& s2)
	{ return !s1.IsEqual(s2); }
__inline bool operator!=(const McsStringA& s1, LPCSTR s2)
	{ return s1.Compare(s2) != 0; }
__inline bool operator!=(LPCSTR s1, const McsStringA& s2)
	{ return s2.Compare(s1) != 0; }
__inline bool operator<(const McsStringA& s1, const McsStringA& s2)
	{ return s1.Compare(s2) < 0; }
__inline bool operator<(const McsStringA& s1, LPCSTR s2)
	{ return s1.Compare(s2) < 0; }
__inline bool operator<(LPCSTR s1, const McsStringA& s2)
	{ return s2.Compare(s1) > 0; }
__inline bool operator>(const McsStringA& s1, const McsStringA& s2)
	{ return s1.Compare(s2) > 0; }
__inline bool operator>(const McsStringA& s1, LPCSTR s2)
	{ return s1.Compare(s2) > 0; }
__inline bool operator>(LPCSTR s1, const McsStringA& s2)
	{ return s2.Compare(s1) < 0; }
__inline bool operator<=(const McsStringA& s1, const McsStringA& s2)
	{ return s1.Compare(s2) <= 0; }
__inline bool operator<=(const McsStringA& s1, LPCSTR s2)
	{ return s1.Compare(s2) <= 0; }
__inline bool operator<=(LPCSTR s1, const McsStringA& s2)
	{ return s2.Compare(s1) >= 0; }
__inline bool operator>=(const McsStringA& s1, const McsStringA& s2)
	{ return s1.Compare(s2) >= 0; }
__inline bool operator>=(const McsStringA& s1, LPCSTR s2)
	{ return s1.Compare(s2) >= 0; }
__inline bool operator>=(LPCSTR s1, const McsStringA& s2)
	{ return s2.Compare(s1) <= 0; }
//=============================================================================
#if defined(_AFX) && !defined(_UNICODE)
__inline McsStringA& McsStringA::operator = (const CString& str)
{
	*this = (LPCSTR)str;
	return *this;
}
//..............................................................................
__inline bool McsStringA::operator == (const CString& str) const
{
	int thisLen = GetLength();
	int otherLen = str.GetLength();
	if(thisLen != otherLen)
		return false;
	if(lstrcmpA(m_pchData, (LPCSTR)str))
		return false;
	return true;
}
//..............................................................................
__inline bool McsStringA::operator != (const CString& str) const 
{
	return !operator==(str);
}
#endif
//=============================================================================
__inline McsStringA::McsStringA(){
	Init();
}
//=============================================================================
__inline McsStringDataA* McsStringA::GetData() const
	{ MCSASSERT_EX(m_pchData != NULL, return NULL); return ((McsStringDataA*)m_pchData)-1; }
//=============================================================================
__inline void McsStringA::Duplicate(const McsStringA& str)
{
	Init();
	int L=str.GetLength();
	if(L==0) return;
	LPSTR pdest = GetBufferSetLength(L);
	lstrcpynA(pdest, str, L+1);
}
//=============================================================================
MT_API McsStringA operator+(const McsStringA& string, CHAR ch);
//=============================================================================
MT_API McsStringA operator+(CHAR ch, const McsStringA& string);
//=============================================================================
__inline void McsStringA::Init()
	{ m_pchData = mcsEmptyStringA.m_pchData; }
//=============================================================================
__inline int McsStringA::GetAllocLength() const
	{ return GetData()->nAllocLength; }
//=============================================================================
__inline bool McsStringA::IsEmpty() const
	{ return GetData()->nDataLength == 0; }
//=============================================================================
__inline int McsStringA::SafeStrlen(LPCSTR lpsz)
	{ return (lpsz == NULL) ? 0 : lstrlenA(lpsz); }
//=============================================================================
__inline bool McsStringA::IsEqual(const McsStringA& str) const
{
	if(m_pchData == str.m_pchData)
		return true;
	if(GetData()->nDataLength != str.GetData()->nDataLength)
		return false;
	if(lstrcmpA(m_pchData, str.m_pchData))
		return false;
	return true;
}
//=============================================================================
// McsStringA support (windows specific)
__inline int McsStringA::Compare(LPCSTR lpsz) const
{ 
	if(m_pchData == lpsz)
		return 0;
	if(!lpsz)
		lpsz="";
	return lstrcmpA(m_pchData, lpsz); 
}
//=============================================================================
__inline int McsStringA::CompareNoCase(LPCSTR lpsz) const
{
	if(m_pchData == lpsz)
		return 0;
	if(!lpsz)
		lpsz="";
	return lstrcmpiA(m_pchData, lpsz); 
}
//=============================================================================
// McsStringA::Collate is often slower than Compare but is MBSC/Unicode
//  aware as well as locale-sensitive with respect to sort order.
__inline int McsStringA::Collate(LPCSTR lpsz) const
{
	if(!lpsz)
		lpsz="";
	return strcoll(m_pchData, lpsz); 
}   // locale sensitive
//=============================================================================
__inline int McsStringA::CollateNoCase(LPCSTR lpsz) const
{
	if(!lpsz)
		lpsz="";
	return _stricoll(m_pchData, lpsz); 
}   // locale sensitive
//=============================================================================
__inline char McsStringA::GetAt(INT_PTR nIndex) const
{
	MCSASSERTx64_EX_32bit(nIndex, return 0);
	MCSASSERT_EX(nIndex >= 0, return 0);
	MCSASSERT_EX(nIndex <= GetData()->nDataLength, return 0);
	return m_pchData[nIndex];
}
//=============================================================================
__inline char& McsStringA::CharAt(INT_PTR nIndex)
{
	MCSASSERTx64_EX_32bit(nIndex, return *(char*)0);
	MCSASSERT_EX(nIndex >= 0, return *(char*)0);
	MCSASSERT_EX(nIndex <= GetData()->nDataLength, return *(char*)0);
	return m_pchData[nIndex];
}
//=============================================================================
#if defined(WIN64)
__inline char McsStringA::operator[](INT_PTR nIndex) const
{
	// same as GetAt
	MCSASSERTx64_EX_32bit(nIndex, return 0);
	MCSASSERT_EX(nIndex >= 0, return 0);
	MCSASSERT_EX(nIndex <= GetData()->nDataLength, return 0);
	return m_pchData[nIndex];
}
//=============================================================================
__inline char& McsStringA::operator[](INT_PTR nIndex)
{
	// same as GetAt
	MCSASSERTx64_EX_32bit(nIndex, return *(char*)NULL);
	MCSASSERT_EX(nIndex >= 0, return *(char*)NULL);
	MCSASSERT_EX(nIndex <= GetData()->nDataLength, return *(char*)NULL);
	return m_pchData[nIndex];
}
#endif
//=============================================================================


///////////////////////////////////////////////////////////////////////////////
////////////////////////////// UNICODE McsStringW //////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//=============================================================================
#pragma pack(push,1)
struct McsStringDataW
{
	//DECLARE_OBJ_NEWDEL;
	long  nRefs;          // reference count
	int   nDataLength;    // length of data (including terminator)
	int   nAllocLength;   // length of allocation
	// WCHAR data[nAllocLength]

	WCHAR* data()           // WCHAR* to managed data
		{ return (WCHAR*)(this+1); }
};
#pragma pack(pop)

//=============================================================================
class McsStringW
{
public:
// Constructors

	DECLARE_OBJ_NEWDEL;

	McsStringW();
	// copy constructor
	MT_API McsStringW(const McsStringW& stringSrc);
	explicit MT_API McsStringW(WCHAR ch, INT_PTR nRepeat = 1); // explicit is required to prevent implicit strings creation from 'bool'
	MT_API McsStringW(LPCWSTR lpsz, HINSTANCE hInst=NULL);
	MT_API McsStringW(LPCWSTR lpch, INT_PTR nLength);

#if defined(_AFX) && defined(_UNICODE)
	McsStringW& operator = (const CString& str);
	bool operator == (const CString& str) const;
	bool operator != (const CString& str) const;
#endif

// Attributes & Operations

	// get data length
	MT_API int GetLength() const;
	// TRUE if zero length
	bool IsEmpty() const;
	// clear contents to empty
	MT_API void Empty();

	// return single character at zero-based index
	WCHAR GetAt(INT_PTR nIndex) const;
	WCHAR& CharAt(INT_PTR nIndex);

	// return single character at zero-based index
	WCHAR operator[](long nIndex) const {return GetAt(nIndex);}
	WCHAR& operator[](long nIndex) {return CharAt(nIndex);}
	WCHAR operator[](int nIndex) const {return GetAt(nIndex);}
	WCHAR& operator[](int nIndex) {return CharAt(nIndex);}

#ifdef WIN64
	WCHAR operator[](INT_PTR nIndex) const;
	WCHAR& operator[](INT_PTR nIndex);
	WCHAR operator[](DWORD nIndex) const {return GetAt(nIndex);}
	WCHAR& operator[](DWORD nIndex) {return CharAt(nIndex);}
#endif

	// set a single character at zero-based index
	MT_API void SetAt(INT_PTR nIndex, WCHAR ch);
	// return pointer to const string
	MT_API operator LPCWSTR() const;

	// overloaded assignment

	// ref-counted copy from another McsStringW
	MT_API const McsStringW& operator=(const McsStringW& stringSrc);
	// set string content to single character
	MT_API const McsStringW& operator=(WCHAR ch);
	// copy string content from UNICODE string
	MT_API const McsStringW& operator=(LPCWSTR lpsz);

	MT_API operator _bstr_t() const;
	MT_API operator _variant_t() const;
	//MT_API const McsStringA& operator=(BSTR bstr);
	MT_API const McsStringW& operator=(const _bstr_t& bstrt);
	//MT_API const McsStringA& operator=(const VARIANT& variant);
	//MT_API const McsStringW& operator=(const _variant_t& variantt);

	// string concatenation

	// concatenate from another McsStringW
	MT_API const McsStringW& operator+=(const McsStringW& string);

	MT_API const McsStringW& operator+=(WCHAR ch);
	MT_API const McsStringW& operator+=(LPCWSTR lpsz);

	friend McsStringW MT_API operator+(const McsStringW& string1, const McsStringW& string2);
	friend McsStringW MT_API operator+(const McsStringW& string, WCHAR ch);
	friend McsStringW MT_API operator+(WCHAR ch, const McsStringW& string);
	friend McsStringW MT_API operator+(const McsStringW& string, LPCWSTR lpsz);
	friend McsStringW MT_API operator+(LPCWSTR lpsz, const McsStringW& string);

	// string comparison

	// straight character comparison
	int Compare(LPCWSTR lpsz) const;
	bool IsEqual(const McsStringW& str) const;
	// compare ignoring case
	int CompareNoCase(LPCWSTR lpsz) const;
	// NLS aware comparison, case sensitive
	int Collate(LPCWSTR lpsz) const;
	// NLS aware comparison, case insensitive
	int CollateNoCase(LPCWSTR lpsz) const;

	// simple sub-string extraction

	// return nCount characters starting at zero-based nFirst
	MT_API McsStringW Mid(INT_PTR nFirst, INT_PTR nCount) const;
	// return all characters starting at zero-based nFirst
	MT_API McsStringW Mid(INT_PTR nFirst) const;
	// return first nCount characters in string
	MT_API McsStringW Left(INT_PTR nCount) const;
	// return nCount characters from end of string
	MT_API McsStringW Right(INT_PTR nCount) const;

	MT_API McsStringW& RemoveLeft(INT_PTR nCount); // removes first nCount characters in string
	MT_API McsStringW& RemoveRight(INT_PTR nCount); // removes last nCount characters in string
	MT_API long       asLong() const;
	MT_API INT_PTR    asLongPtr() const;
	MT_API double     asDouble() const;
	MT_API double     asDoubleEx(LPCWSTR decimalSeparators = L".,") const; // slow
	MT_API bool       isaLong() const;
	MT_API bool       isaLongPtr() const;
	MT_API bool       isaDouble() const;
	MT_API int        ComparePart(LPCWSTR str,INT_PTR nChars) const;
	MT_API int        ComparePartNoCase(LPCWSTR str, INT_PTR nChars) const;
	MT_API int        CompareDgt(LPCWSTR lpsz) const;
	MT_API int        CompareDgtNoCase(LPCWSTR lpsz) const;

		// (!) internally not uses "strtok" function so you can safely use it 
		// returns number of extracted strings 
	MT_API int        Split(IN LPCWSTR delimitersString, OUT mcsStringArrayW& subStrings) const;

		// this version can split string with substrings enclosed into brackets with
		// <bracketsChar> char.
		// Ex: McsString("aaa 'qwe 222' '44'").SplitEx(" ", "'", ...); will give
		// 3 strings: "aaa" "qwe 222" and "44"
	MT_API int SplitEx(
		IN LPCWSTR cstrDelimitersChars, 
		IN OPTIONAL WCHAR bracketsChar, 
		OUT mcsStringArrayW& subStrings, 
		IN OPTIONAL bool fRemoveBrackets = true,
		IN OPTIONAL WCHAR escapeSqwChar = 0, // most frequently used - '\\' 
		IN OPTIONAL bool fRemoveSqwChars = false) const;

	// returns number of total removed characters
	MT_API int        Trim(IN LPCWSTR charactersToTrim);
	MT_API McsStringA	asMB(UINT CodePage=GetACP()) const;
	       McsStringW	asUnicode(UINT CodePage=GetACP()) const {return *this;}
#ifdef	_UNICODE
				 McsString	asT(UINT CodePage=GetACP()) const{return *this;}
#else
				 McsString	asT(UINT CodePage=GetACP()) const{return asMB(CodePage);}
#endif
	//......................................................................................

	//  characters from beginning that are also in passed string
	MT_API McsStringW SpanIncluding(LPCWSTR lpszCharSet) const;
	// characters from beginning that are not also in passed string
	MT_API McsStringW SpanExcluding(LPCWSTR lpszCharSet) const;

	// upper/lower/reverse conversion

	// NLS aware conversion to uppercase
	MT_API void MakeUpper();
	// NLS aware conversion to lowercase
	MT_API void MakeLower();
	// reverse string right-to-left
	MT_API void MakeReverse();

	// trimming whitespace (either side)

	// remove whitespace starting from right edge
	MT_API void TrimRight();
	// remove whitespace starting from left side
	MT_API void TrimLeft();

	// trimming anything (either side)

	// remove continuous occurrences of chTarget starting from right
	MT_API void TrimRight(WCHAR chTarget);
	// remove continuous occurrences of characters in passed string,
	// starting from right
	MT_API void TrimRight(LPCWSTR lpszTargets);
	// remove continuous occurrences of chTarget starting from left
	MT_API void TrimLeft(WCHAR chTarget);
	// remove continuous occurrences of characters in
	// passed string, starting from left
	MT_API void TrimLeft(LPCWSTR lpszTargets);

	// advanced manipulation

	// replace occurrences of chOld with chNew
	MT_API int Replace(WCHAR chOld, WCHAR chNew);
	// replace occurrences of substring lpszOld with lpszNew;
	// empty lpszNew removes instances of lpszOld
	MT_API int Replace(LPCWSTR lpszOld, LPCWSTR lpszNew);
	MT_API int Replace(LPCWSTR lpszOld, LPCWSTR lpszNew, void* pStringsComparator);
	MT_API int ReplaceNoCase(LPCWSTR lpszOld, LPCWSTR lpszNew);
	// remove occurrences of chRemove
	MT_API int Remove(WCHAR chRemove);
	// insert character at zero-based index; concatenates
	// if index is past end of string
	MT_API int Insert(INT_PTR nIndex, WCHAR ch);
	// insert substring at zero-based index; concatenates
	// if index is past end of string
	MT_API int Insert(INT_PTR nIndex, LPCWSTR pstr);
	// delete nCount characters starting at zero-based index
	MT_API int Delete(INT_PTR nIndex, INT_PTR nCount = 1);

	// searching

	// find character starting at left, -1 if not found
	MT_API int Find(WCHAR ch) const;
	// find character starting at right
	MT_API int ReverseFind(WCHAR ch) const;
	// find character starting at zero-based index and going right
	MT_API int Find(WCHAR ch, INT_PTR nStart) const;
	// find first instance of any character in passed string
	MT_API int FindOneOf(LPCWSTR lpszCharSet) const;
	// find first instance of substring starting at zero-based index
	MT_API int Find(LPCWSTR lpszSub) const;
	MT_API int Find(LPCWSTR lpszSub, INT_PTR nStart) const;
	MT_API int Find(LPCWSTR lpszSub, INT_PTR nStart, void* pStringsComparator) const;
	MT_API int FindNoCase(LPCWSTR lpszSub, INT_PTR nStart=0) const;

	// simple formatting

	// printf-like formatting using passed string
	MT_API McsStringW& __cdecl Format(LPCWSTR lpszFormat, ...);
	MT_API McsStringW& __cdecl FormatD(LPCWSTR lpszFormat, ...);
	// printf-like formatting using referenced string resource
	MT_API McsStringW& __cdecl Format(HINSTANCE hInst,UINT nFormatID, ...);
	MT_API McsStringW& __cdecl FormatD(HINSTANCE hInst,UINT nFormatID, ...);
	// printf-like formatting using variable arguments parameter
	MT_API McsStringW& FormatV(LPCWSTR lpszFormat, va_list argList);
	MT_API McsStringW& FormatVD(LPCWSTR lpszFormat, va_list argList);
	MT_API McsStringW& FormatVEx(LPCWSTR lpszFormat, bool fForceDot, va_list argList);

	// formatting for localization (uses FormatMessage API)

	// format using FormatMessage API on passed string
	MT_API void __cdecl FormatMessage(LPCWSTR lpszFormat, ...);
	// format using FormatMessage API on referenced string resource
	MT_API void __cdecl FormatMessage(HINSTANCE hInst,UINT nFormatID, ...);

	// load from string resource
	MT_API bool LoadString(HINSTANCE hInst,UINT nID);
// #ifdef UNICODE
// 	MT_API bool LoadStringA(HINSTANCE hInst,UINT nID)
// 		{return LoadStringW(hInst, nID);}
// 	MT_API bool LoadString(HINSTANCE hInst,UINT nID); // в LIB будет LoadStringW
// #else
// 	MT_API bool LoadStringW(HINSTANCE hInst,UINT nID)
// 		{return LoadStringA(hInst, nID);}
// 	MT_API bool LoadString(HINSTANCE hInst,UINT nID); // в LIB будет LoadStringA
// #endif

	// Access to string implementation buffer as "C" character array

	// get pointer to modifiable buffer at least as long as nMinBufLength
	MT_API LPWSTR GetBuffer(INT_PTR nMinBufLength);
	// release buffer, setting length to nNewLength (or to first null if -1)
	MT_API void ReleaseBuffer(INT_PTR nNewLength = -1);
	// get pointer to modifiable buffer exactly as long as nNewLength
	MT_API LPWSTR GetBufferSetLength(INT_PTR nNewLength);
	
	// release memory allocated to but unused by string
	void FreeExtra();

	// Use LockBuffer/UnlockBuffer to turn ref counting off

	// turn ref counting back on
	MT_API LPWSTR LockBuffer();
	// turn ref counting off
	MT_API void UnlockBuffer();

	void Duplicate(const McsStringW& str);

// Implementation
public:
	MT_API ~McsStringW();
	int GetAllocLength() const;

protected:

#ifdef _MCEYE
public:
#endif

	LPWSTR m_pchData;   // pointer to ref counted string data

	// implementation helpers
	McsStringDataW* GetData() const;
	void Init();
	MT_API void AllocCopy(McsStringW& dest, INT_PTR nCopyLen, INT_PTR nCopyIndex, INT_PTR nExtraLen) const;
	MT_API void AllocBuffer(INT_PTR nLen);
	MT_API void AssignCopy(INT_PTR nSrcLen, LPCWSTR lpszSrcData);
	MT_API void ConcatCopy(INT_PTR nSrc1Len, LPCWSTR lpszSrc1Data, INT_PTR nSrc2Len, LPCWSTR lpszSrc2Data);
	MT_API void ConcatInPlace(INT_PTR nSrcLen, LPCWSTR lpszSrcData);
	MT_API void CopyBeforeWrite();
	MT_API void AllocBeforeWrite(INT_PTR nLen);
	MT_API void Release();
	MT_API static void Release(McsStringDataW* pData);
	static int SafeStrlen(LPCWSTR lpsz);
	MT_API static void FreeData(McsStringDataW* pData);
};
//=============================================================================
// Compare helpers

// Запретил сравнение с WCHAR, т.к. к нему автоматически приводится сравнение строки с целым числом
// __inline bool operator==(const McsStringW& s, WCHAR wc)
// {
// 	int len = s.GetLength();
// 	if(len <= 1 && ((LPCWSTR)s)[0]==wc)
// 		return true;
// 	return false;
// }
// __inline bool operator==(WCHAR wc, const McsStringW& s)
// {
// 	int len = s.GetLength();
// 	if(len <= 1 && ((LPCWSTR)s)[0]==wc)
// 		return true;
// 	return false;
// }
// __inline bool operator!=(const McsStringW& s, WCHAR wc)
// 	{ return !(s == wc); }
// __inline bool operator!=(WCHAR wc, const McsStringW& s)
// 	{ return !(wc == s); }

__inline bool operator==(const McsStringW& s1, const McsStringW& s2)
	{ return s1.IsEqual(s2); }
__inline bool operator==(const McsStringW& s1, LPCWSTR s2)
	{ return s1.Compare(s2) == 0; }
__inline bool operator==(LPCWSTR s1, const McsStringW& s2)
	{ return s2.Compare(s1) == 0; }
__inline bool operator!=(const McsStringW& s1, const McsStringW& s2)
	{ return !s1.IsEqual(s2); }
__inline bool operator!=(const McsStringW& s1, LPCWSTR s2)
	{ return s1.Compare(s2) != 0; }
__inline bool operator!=(LPCWSTR s1, const McsStringW& s2)
	{ return s2.Compare(s1) != 0; }
__inline bool operator<(const McsStringW& s1, const McsStringW& s2)
	{ return s1.Compare(s2) < 0; }
__inline bool operator<(const McsStringW& s1, LPCWSTR s2)
	{ return s1.Compare(s2) < 0; }
__inline bool operator<(LPCWSTR s1, const McsStringW& s2)
	{ return s2.Compare(s1) > 0; }
__inline bool operator>(const McsStringW& s1, const McsStringW& s2)
	{ return s1.Compare(s2) > 0; }
__inline bool operator>(const McsStringW& s1, LPCWSTR s2)
	{ return s1.Compare(s2) > 0; }
__inline bool operator>(LPCWSTR s1, const McsStringW& s2)
	{ return s2.Compare(s1) < 0; }
__inline bool operator<=(const McsStringW& s1, const McsStringW& s2)
	{ return s1.Compare(s2) <= 0; }
__inline bool operator<=(const McsStringW& s1, LPCWSTR s2)
	{ return s1.Compare(s2) <= 0; }
__inline bool operator<=(LPCWSTR s1, const McsStringW& s2)
	{ return s2.Compare(s1) >= 0; }
__inline bool operator>=(const McsStringW& s1, const McsStringW& s2)
	{ return s1.Compare(s2) >= 0; }
__inline bool operator>=(const McsStringW& s1, LPCWSTR s2)
	{ return s1.Compare(s2) >= 0; }
__inline bool operator>=(LPCWSTR s1, const McsStringW& s2)
	{ return s2.Compare(s1) <= 0; }
//=============================================================================
#if defined(_AFX) && defined(_UNICODE)
__inline McsStringW& McsStringW::operator = (const CString& str)
{
	*this = (LPCWSTR)str;
	return *this;
}
//..............................................................................
__inline bool McsStringW::operator == (const CString& str) const
{
	int thisLen = GetLength();
	int otherLen = str.GetLength();
	if(thisLen != otherLen)
		return false;
	if(lstrcmpW(m_pchData, (LPCWSTR)str))
		return false;
	return true;
}
//..............................................................................
__inline bool McsStringW::operator != (const CString& str) const 
{
	return !operator==(str);
}
#endif
//=============================================================================
__inline McsStringW::McsStringW(){
	Init();
}
//=============================================================================
__inline McsStringDataW* McsStringW::GetData() const
	{ MCSASSERT_EX(m_pchData != NULL, return NULL); return ((McsStringDataW*)m_pchData)-1; }
//=============================================================================
__inline void McsStringW::Duplicate(const McsStringW& str)
{
  Init();
  int L=str.GetLength();
  if(L==0) return;
  LPWSTR pdest = GetBufferSetLength(L);
  lstrcpynW(pdest, str, L+1);
}
//=============================================================================
__inline void McsStringW::Init()
	{ m_pchData = mcsEmptyStringW.m_pchData; }
//=============================================================================
MT_API McsStringW operator+(const McsStringW& string, WCHAR ch);
//=============================================================================
MT_API McsStringW operator+(WCHAR ch, const McsStringW& string);
//=============================================================================
__inline int McsStringW::GetAllocLength() const
	{ return GetData()->nAllocLength; }
//=============================================================================
__inline bool McsStringW::IsEmpty() const
	{ return GetData()->nDataLength == 0; }
//=============================================================================
__inline int McsStringW::SafeStrlen(LPCWSTR lpsz)
	{ return (lpsz == NULL) ? 0 : lstrlenW(lpsz); }
//=============================================================================
__inline bool McsStringW::IsEqual(const McsStringW& str) const
{
	if(m_pchData == str.m_pchData)
		return true;
	if(GetData()->nDataLength != str.GetData()->nDataLength)
		return false;
	if(lstrcmpW(m_pchData, str.m_pchData))
		return false;
	return true;
}
//=============================================================================
// McsStringW support (windows specific)
__inline int McsStringW::Compare(LPCWSTR lpsz) const
{ 
	if(m_pchData == lpsz)
		return 0;
	if(!lpsz)
		lpsz=L"";
	return lstrcmpW(m_pchData, lpsz); 
}
//=============================================================================
__inline int McsStringW::CompareNoCase(LPCWSTR lpsz) const
{ 
	if(m_pchData == lpsz)
		return 0;
	if(!lpsz)
		lpsz=L"";
	return lstrcmpiW(m_pchData, lpsz);
}
//=============================================================================
// McsStringW::Collate is often slower than Compare but is MBSC/Unicode
//  aware as well as locale-sensitive with respect to sort order.
__inline int McsStringW::Collate(LPCWSTR lpsz) const
{ 
	if(!lpsz)
		lpsz=L"";
	return wcscoll(m_pchData, lpsz); 
}
//=============================================================================
__inline int McsStringW::CollateNoCase(LPCWSTR lpsz) const
{ 
	if(!lpsz)
		lpsz=L"";
	return _wcsicoll(m_pchData, lpsz); 
}
//=============================================================================
__inline WCHAR McsStringW::GetAt(INT_PTR nIndex) const
{
	MCSASSERTx64_EX_32bit(nIndex, return 0);
	MCSASSERT_EX(nIndex >= 0, return 0);
	MCSASSERT_EX(nIndex <= GetData()->nDataLength, return 0);
	return m_pchData[nIndex];
}
//=============================================================================
__inline WCHAR& McsStringW::CharAt(INT_PTR nIndex)
{
	MCSASSERTx64_EX_32bit(nIndex, return *(WCHAR*)0);
	MCSASSERT_EX(nIndex >= 0, return *(WCHAR*)0);
	MCSASSERT_EX(nIndex <= GetData()->nDataLength, return *(WCHAR*)0);
	return m_pchData[nIndex];
}
//=============================================================================
#if defined(WIN64)
__inline WCHAR McsStringW::operator[](INT_PTR nIndex) const
{
	// same as GetAt
	MCSASSERTx64_EX_32bit(nIndex, return 0);
	MCSASSERT_EX(nIndex >= 0, return 0);
	MCSASSERT_EX(nIndex <= GetData()->nDataLength, return 0);
	return m_pchData[nIndex];
}
//=============================================================================
__inline WCHAR& McsStringW::operator[](INT_PTR nIndex)
{
	// same as GetAt
	MCSASSERTx64_EX_32bit(nIndex, return *(WCHAR*)NULL);
	MCSASSERT_EX(nIndex >= 0, return *(WCHAR*)NULL);
	MCSASSERT_EX(nIndex <= GetData()->nDataLength, return *(WCHAR*)NULL);
	return m_pchData[nIndex];
}
#endif
//=============================================================================

#ifdef	_UNICODE
	__inline McsString	McsStringA::asT(UINT CodePage) const{return asUnicode(CodePage);}
#endif

//===========================================================================
template <> __inline UINT __stdcall McsHashKey(const McsStringW& st)
{
	return McsHashKey((LPCWSTR)st);
}
//===========================================================================
template <> __inline UINT __stdcall McsHashKey(const McsStringA& st)
{
	return McsHashKey((LPCSTR)st);
}

//=============================================================================
__inline McsString MCSUID::GetAsString() const
{
	McsString sUID;
	sUID.Format(_T("%I64X"), i64);
	return sUID;
};
//=============================================================================

// Ordered Hashset

template<class KEY, class ARG_KEY>
class McsHashsetEx : protected McsMapEx<KEY, ARG_KEY, _nulltype, const _nulltype&>
{
public:

	DECLARE_OBJ_NEWDEL;

	typedef McsArray<KEY, ARG_KEY> KeysArr;

	McsHashsetEx() { m_fHashSetMode = true; }
	McsHashsetEx(const McsHashsetEx& copyFrom) { m_fHashSetMode = true; *this = copyFrom; }
	McsHashsetEx(const KeysArr& values) { m_fHashSetMode = true; *this = values; }

	int  GetCount() const { return m_nCount; }
	int  GetSize() const { return m_nCount; }
	int  Length() const { return m_nCount; }
	bool IsEmpty() const { return m_nCount == 0; }
	bool isEmpty() const { return m_nCount == 0; }

	McsHashsetEx& operator = (const KeysArr& values)
	{
		RemoveAll();
		InitHashTable(values.GetSize());
		Add(values);
		return *this;
	}

	McsHashsetEx& operator = (const McsHashsetEx& copyFrom) {
		(McsMapEx&)(*this) = (const McsMapEx&)copyFrom;
		return *this;
	}

	bool isExist(ARG_KEY key) const { return McsMapEx::isExist(key); }
	bool exist(ARG_KEY key) const { return McsMapEx::isExist(key); }
	bool Exist(ARG_KEY key) const { return McsMapEx::isExist(key); }
	bool contains(ARG_KEY key) const { return McsMapEx::isExist(key); }

		// возвращает индекс ключа, если не находит, то индекс будет <0
	mapidx indexOf(ARG_KEY key) const { return McsMapEx::indexOf(key); }

	bool Add(ARG_KEY key)
	{
		int n1 = GetSize();
		McsMapEx::SetAt(key, NULLTYPE);
		return GetSize() > n1;
	}
	McsHashsetEx& operator |= (ARG_KEY key) { Add(key); return *this; }
	McsHashsetEx& operator += (ARG_KEY key) { Add(key); return *this; }
	McsHashsetEx operator | (ARG_KEY key) const { McsHashsetEx res(*this); res.Add(key); return res; }
	McsHashsetEx operator + (ARG_KEY key) const { McsHashsetEx res(*this); res.Add(key); return res; }

	void Add(const KeysArr& values)
	{
		for(int i=0; i<values.GetSize(); i++)
			Add(values[i]);
	}

	McsHashsetEx& operator |= (const KeysArr& values) { Add(values); return *this; }
	McsHashsetEx& operator += (const KeysArr& values) { Add(values); return *this; }
	McsHashsetEx operator | (const KeysArr& values) const { McsHashsetEx res(*this); res.Add(values); return res; }
	McsHashsetEx operator + (const KeysArr& values) const { McsHashsetEx res(*this); res.Add(values); return res; }

	void Add(const McsHashsetEx& set)
	{
		for(mapidx mi = set.FirstIdx(); mi < set.GetSize(); ++mi)
			Add(set[mi]);
	}

	McsHashsetEx& operator |= (const McsHashsetEx& set) { Add(set); return *this; }
	McsHashsetEx& operator += (const McsHashsetEx& set) { Add(set); return *this; }
	McsHashsetEx operator | (const McsHashsetEx& set) const { McsHashsetEx res(*this); res.Add(set); return res; }
	McsHashsetEx operator + (const McsHashsetEx& set) const { McsHashsetEx res(*this); res.Add(set); return res; }

	bool RemoveKey(ARG_KEY key) { return McsMapEx::RemoveKey(key); }
	bool Remove(ARG_KEY key) { return McsMapEx::RemoveKey(key); }
	McsHashsetEx& operator -= (ARG_KEY key) { Remove(key); return *this; }
	McsHashsetEx operator - (ARG_KEY key) const { McsHashsetEx res(*this); res.Remove(key); return res; }

	int Remove(const KeysArr& values)
	{
		int nr = 0;
		for(int i=0; i<values.GetSize(); i++) {
			if(Remove(values[i]))
				nr++;
		}
		return nr;
	}

	int removeSubset(const KeysArr& values) { return Remove(values); }
	McsHashsetEx& operator -= (const KeysArr& values) { Remove(values); return *this; }
	McsHashsetEx operator - (const KeysArr& values) const { McsHashsetEx res(*this); res.Remove(values); return res; }

	int Remove(const McsHashsetEx& set)
	{
		int nr = 0;
		for(mapidx mi = set.FirstIdx(); mi < set.GetSize(); ++mi) {
			if(Remove(set[mi]))
				nr++;
		}
		return nr;
	}

	int removeSubset(const McsHashsetEx& set) { return Remove(set); }
	McsHashsetEx& operator -= (const McsHashsetEx& set) { Remove(set); return *this; }
	McsHashsetEx operator - (const McsHashsetEx& set) const { McsHashsetEx res(*this); res.Remove(set); return res; }

	void RemoveAll() { McsMapEx::RemoveAll(); }

	bool operator == (const McsHashsetEx& cmpWith) const { return McsMapEx::operator == ((const McsMapEx&)cmpWith); }
	bool operator != (const McsHashsetEx& cmpWith)const { return McsMapEx::operator != ((const McsMapEx&)cmpWith); }

	// iterating all (key, value) pairs
	MCSPOSITION GetStartPosition() const { return McsMapEx::GetStartPosition(); }
	void GetNextKey(MCSPOSITION& rNextPosition, KEY& rKey) const { McsMapEx::GetNextKey(rNextPosition, rKey); }
	void GetNextKey(MCSPOSITION& rNextPosition, KEY*& pKey) { McsMapEx::GetNextKey(rNextPosition, pKey); }
	void GetNextKey(MCSPOSITION& rNextPosition, const KEY*& pKey) const { McsMapEx::GetNextKey(rNextPosition, pKey); }

	void getAsArray(OUT KeysArr& arr, int idxFrom = 0, int idxUpTo = -1) const
	{
		arr.SetSize(0); // не использовать RemoveAll, SetSize вохраняет выделенную память, экономит время
		if(m_nCount == 0)
			return;

		MCSASSERTE_EX(idxFrom < 0, idxFrom = 0);
		if(idxUpTo < 0)
			idxUpTo = m_nCount-1;
		MCSASSERTE_EX(idxUpTo < idxFrom, return);
		int i = 0, nCount = idxUpTo - idxFrom + 1;
		arr.SetSize(nCount);

		mapidx mi = FirstIdx();
		mi += idxFrom;
		for(; mi<m_nCount; ++mi)
		{
			if(mi > idxUpTo)
				break;
			arr[i++] = K(mi);
		}
	}

	void AsArray(OUT KeysArr& arr, int idxFrom = 0, int idxUpTo = -1) const {
		getAsArray(arr, idxFrom, idxUpTo);
	}

		// for compatibility with old maps used as hashsets
		// returns symmetric KEY->KEY map
	void _getAsMap(OUT McsMapEx<KEY, ARG_KEY, KEY, ARG_KEY>& map) const {
		for(mapidx mi = FirstIdx(); mi<m_nCount; ++mi) {
			const KEY& key = K(mi);
			map.SetAt(key, key);
		}
	}

	// !!! USE <false> for <fAutoPack> if you will use more than one raw iteration cycle 
	// !!! one inside other

		// no autopack inside
	mapidx FirstIdx() const { return McsMapEx::FirstIdx(); }
	// no autopack inside
	mapidx LastIdx() const {return McsMapEx::LastIdx(); }

	mapidx FirstIdx(bool fAutoPack = true) { return McsMapEx::FirstIdx(fAutoPack); }
	mapidx LastIdx(bool fAutoPack = true) { return McsMapEx::LastIdx(fAutoPack); }

	KEY&   K(IN const mapidx& mi) { return McsMapEx::K(mi); }
	const KEY&   K(IN const mapidx& mi) const { return McsMapEx::K(mi); }

	const KEY& operator[] (IN const mapidx& mi) const { return McsMapEx::K(mi); }
	KEY& operator[] (IN const mapidx& mi) { return McsMapEx::K(mi); }

	// advanced features for derived classes
	int GetHashTableSize() const { return m_nHashTableSize; }

		// flag _fCalledFromGrowHT used for internal purposes (for <_growHashTableSize> method)
	void InitHashTable(UINT_PTR hashSize, bool fAllocNow = true) {
		McsMapEx::InitHashTable(hashSize, fAllocNow);
	}

	int PackRawTable(bool fForce = true) { return McsMapEx::PackRawTable(fForce); }

	bool contains(const KeysArr& values) const {
		for(int i=0; i<values.GetSize(); i++) {
			if(!contains(values[i]))
				return false;
		}
		return true;
	}

	bool contains(const McsHashsetEx& set) const {
		for(mapidx mi=set.FirstIdx(); mi<set.GetSize(); ++mi) {
			if(!contains(set[mi]))
				return false;
		}
		return true;
	}

	bool containsAnyOf(const KeysArr& values) const {
		for(int i=0; i<values.GetSize(); i++) {
			if(contains(values[i]))
				return true;
		}
		return false;
	}

	bool containsAnyOf(const McsHashsetEx& set) const {
		for(mapidx mi=set.FirstIdx(); mi<set.GetSize(); ++mi) {
			if(contains(set[mi]))
				return true;
		}
		return false;
	}

	const KEY* getExistingKeyPtr(ARG_KEY key) const {
		const KEY* pKey;
		const _nulltype* pVal;
		McsMapEx::assocAt(key, pKey, pVal);
		return pKey;
	}

	// same as operator [], but return stored key ref in map
	const KEY& keyAt(ARG_KEY key) const {
		return McsMapEx::keyAt(key);
	}

		// removes elements, which don't exist in values
	void Intersect(const KeysArr& values)
	{
		if(values.isEmpty()) {
			RemoveAll();
			return;
		}

		for(mapidx mi=FirstIdx(); mi<m_nCount; ++mi) {
			const KEY& key = K(mi);
			if(values.contains(key))
				continue;
			RemoveKey(key);
			--mi;
		}
	}

	McsHashsetEx& operator &= (const KeysArr& values) { Intersect(values); return *this; }

		// removes elements, which don't exist in values
	void Intersect(const McsHashsetEx& set)
	{
		if(set.isEmpty()) {
			RemoveAll();
			return;
		}

		for(mapidx mi=FirstIdx(); mi<m_nCount; ++mi) {
			const KEY& key = K(mi);
			if(set.contains(key))
				continue;
			RemoveKey(key);
			--mi;
		}
	}
	McsHashsetEx& operator &= (const McsHashsetEx& set) { Intersect(set); return *this; }
};
//=============================================================================

typedef McsHashsetEx<int, int>               mcsIntSetEx;
typedef McsHashsetEx<INT_PTR, INT_PTR>       mcsIntptrSetEx;
typedef McsHashsetEx<__int64, __int64>       mcsI64SetEx;
typedef McsHashsetEx<DWORD, DWORD>           mcsDwordSetEx;
typedef McsHashsetEx<DWORD_PTR, DWORD_PTR>   mcsDwordptrSetEx;
typedef McsHashsetEx<double, double>         mcsDblSetEx;
typedef McsHashsetEx<void*, void*>           mcsPVoidSetEx;

typedef McsHashsetEx<McGSMarker, McGSMarker> mcsMcGsMarkerSetEx;
typedef McsHashsetEx<GUID>                   mcsGUIDSetEx;
typedef McsHashsetEx<MCSUID, MCSUID>         mcsMCSUIDSetEx;
typedef McsHashsetEx<mcsWorkID>              mcsWorkIDSetEx;
typedef McsHashsetEx<mcsComplexWorkID>       mcsComplexWorkIDSetEx;
typedef McsHashsetEx<McsStringA, LPCSTR>     mcsStringSetExA;
typedef McsHashsetEx<McsStringW, LPCWSTR>    mcsStringSetExW;

//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::getAsHashset(KeysHashsetEx& set) const
{
	set.RemoveAll();
	if(m_nCount==0)
		return false;

	set.InitHashTable(m_nCount, true);

	int i=0;
	if(m_fRawAccessEnabled)
	{
		for(mapidx mi = FirstIdx(); mi<m_nCount; ++mi)
			set |= K(mi);
	}
	else
	{
		const KEY* pKey=NULL;
		MCSPOSITION pos = GetStartPosition();
		while(pos) {
			GetNextKey(pos, pKey);
			set |= *pKey;
		}
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMapEx<KEY, ARG_KEY, VALUE, ARG_VALUE>::getAsHashset(KeysHashset& set) const
{
	set.RemoveAll();
	if(m_nCount==0)
		return false;

	set.InitHashTable(m_nCount, true);

	int i=0;
	if(m_fRawAccessEnabled)
	{
		for(mapidx mi = FirstIdx(); mi<m_nCount; ++mi)
			set |= K(mi);
	}
	else
	{
		const KEY* pKey = NULL;
		MCSPOSITION pos = GetStartPosition();
		while(pos) {
			GetNextKey(pos, pKey);
			set |= *pKey;
		}
	}

	return true;
}
//=============================================================================

typedef McsMapEx <McsStringA, LPCSTR, McsStringA, LPCSTR>   McsMapStringToStringExA;
typedef McsMapEx <McsStringW, LPCWSTR, McsStringW, LPCWSTR> McsMapStringToStringExW;

typedef McsMapEx <McsStringA, LPCSTR, McsStringA, LPCSTR>   mcsMapStringToStringExA;
typedef McsMapEx <McsStringW, LPCWSTR, McsStringW, LPCWSTR> mcsMapStringToStringExW;

typedef McsMapEx <int, int, int, int>          mcsMapInt2IntEx;
typedef McsMapEx<McsString, LPCTSTR, int, int> mcsMapStr2IntEx;

#ifndef _UNICODE
	#define McsString                                           McsStringA
	typedef McsMapEx <McsStringA, LPCSTR, McsStringA, LPCSTR>   mcsMapStringToStringEx;
	typedef McsMapEx <McsStringA, LPCSTR, McsStringA, LPCSTR>   McsMapStringToStringEx;
	typedef McsArray<McsStringA, LPCSTR>                        mcsStringArray;
	typedef McsHashsetEx<McsStringA, LPCSTR>                    mcsStringSetEx;
#else
	#define McsString                                           McsStringW
	typedef McsMapEx <McsStringW, LPCWSTR, McsStringW, LPCWSTR> mcsMapStringToStringEx;
	typedef McsMapEx <McsStringW, LPCWSTR, McsStringW, LPCWSTR> McsMapStringToStringEx;
	typedef McsArray<McsStringW, LPCWSTR>                       mcsStringArray;
	typedef McsHashsetEx<McsStringW, LPCWSTR>                   mcsStringSetEx;
#endif

//=============================================================================
