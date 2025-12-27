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

#pragma warning(disable: 4482) // nonstandard extension used: enum 'xxx::yyy' used in qualified name

#ifdef _VERBOSEHEADERS_
	#pragma message("Use " __FILE__)
#endif

#ifndef __COMPILE_MT__
 //#define _STD_MEM_ // unrem for disable MT.DLL memory allocations
#endif

#include "McAPIs.h"
#include <wtypes.h>

//===========================================================================

#define STRBUFSIZE(strBuffer) (sizeof(strBuffer)/sizeof((strBuffer)[0]))
#define NBUFITEMS(buffer) (sizeof(buffer)/sizeof((buffer)[0]))
#define STR_EMPTY TEXT("")

//===========================================================================
#undef new
#undef delete

struct __MCS_NEW_PLUG{};
#undef __MNP__
#define __MNP__ (__MCS_NEW_PLUG*)NULL

#define gMTWarnMessage  "MT.DLL not loaded, program terminating..."
#define gMTWarnMessageHdr "McsMem"

#define exp_mt_gpMcsMemAllocator "gpMcsMemAllocator"
#define exp_mt_mtMemAlloc4A      "mtMemAlloc4A"
#define exp_mt_mtMemFree4A       "mtMemFree4A"
#define exp_mt_mtRawMemAlloc4A   "mtRawMemAlloc4A"
#define exp_mt_mtRawMemFree4A    "mtRawMemFree4A"

//===========================================================================
#if !defined(_STD_MEM_)
	struct IMcsMemAllocator
	{
		virtual void* McsAlloc(size_t size, LPCSTR FileName = NULL, int LineNum = 0, bool fOperatorNew = false) = 0;
		virtual void* McsReAlloc(void* OldPtr, size_t newsize, LPCSTR FileName=NULL, int LineNum = 0) = 0;
		virtual void  McsFree(void* ptr, LPCSTR FileName = NULL, int LineNum = 0, bool fOperatorDelete = false) = 0;
		virtual bool  IsMTBlock(void* ptr) = 0;
		virtual HRESULT MTControl(DWORD code, void* pBuf = NULL) = 0;

		static IMcsMemAllocator* _get_MMA()
		{
			static IMcsMemAllocator* ls_gpMcsMemAllocator=NULL;
			if(ls_gpMcsMemAllocator==NULL)
			{
				HMODULE hMT=GetModuleHandleA("MT.DLL");
				if(hMT==NULL) {MessageBoxA(NULL,gMTWarnMessage,gMTWarnMessageHdr,MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST|MB_TASKMODAL); TerminateProcess(GetCurrentProcess(),-1);}
				ls_gpMcsMemAllocator = *(IMcsMemAllocator**)::GetProcAddress(hMT, exp_mt_gpMcsMemAllocator);
			}

			return ls_gpMcsMemAllocator;
		}
	};
#else
	// do not use this section in commercial compilations of projects: exists only for test
	struct IMcsMemAllocator
	{
		virtual void* McsAlloc(size_t size, LPCSTR FileName = NULL, int LineNum = 0, bool fOperatorNew = false)
			{return malloc(size);}

		virtual void* McsReAlloc(void* OldPtr, size_t newsize, LPCSTR FileName = NULL, int LineNum = 0)
			{return realloc(OldPtr,newsize);}

		virtual void  McsFree(void* ptr, LPCSTR FileName = NULL, int LineNum = 0, bool fOperatorDelete = false)
			{free(ptr);}

		virtual bool IsMTBlock(void* ptr)
			{return false;}

		virtual HRESULT MTControl(DWORD code, void* pBuf=NULL)
			{return S_FALSE;}

		static IMcsMemAllocator* _get_MMA()
		{
			static IMcsMemAllocator ls_gMcsMemAllocator; 
			return &ls_gMcsMemAllocator;
		}
	};
#endif

#define gpMcsMemAllocator IMcsMemAllocator::_get_MMA()

#if defined(_STD_MEM_)
	__inline int sprintfWrapperA(LPSTR Buffer, LPCSTR* pFmtString_arg)
	{
		static int (*pSW)(LPSTR,LPCSTR*) = NULL;
		if(pSW==NULL)
		{
			HMODULE hMT=GetModuleHandleA("MT.DLL");
			if(hMT==NULL) {
				MessageBoxA(NULL, gMTWarnMessage, gMTWarnMessageHdr, MB_ICONSTOP|MB_SETFOREGROUND|MB_TOPMOST|MB_TASKMODAL); 
				TerminateProcess(GetCurrentProcess(),-1);
			}
			pSW = (int(*)(LPSTR,LPCSTR*))::GetProcAddress(hMT,"sprintfWrapperA");
		}
		return pSW(Buffer, pFmtString_arg);
	}
#endif // _STD_MEM_

//...........................................................................
__inline void* __cdecl operator new(size_t, void* ptr,__MCS_NEW_PLUG*)
	{return ptr;}

// special form for mcsMemNew macro
__inline void* operator new(size_t size, LPCSTR fn, int ln, __MCS_NEW_PLUG*)
	{return gpMcsMemAllocator->McsAlloc(size, fn, ln, true);}

__inline void __cdecl operator delete(void* ptr, LPCSTR fn, int ln, __MCS_NEW_PLUG*)
	{return;}

__inline void __cdecl operator delete(void* ptr, void*, __MCS_NEW_PLUG*)
	{return;}

//===========================================================================
template <class TYPE>
__inline void _mcsDelete(TYPE* ptr,LPCSTR cpfn,int cpln)
{
	if(ptr==NULL) 
		return;
	ptr->~TYPE();
	gpMcsMemAllocator->McsFree(ptr, cpfn, cpln, true);
}
//===========================================================================
struct __MCS_NEW_PLUG2{};
__inline void* operator new(size_t size, LPCSTR, int, __MCS_NEW_PLUG2* p_arg) {
	__int64* p = (__int64*)p_arg;
	p[1] = size;
	return (void*)p_arg;
}
__inline void __cdecl operator delete(void* ptr, LPCSTR fn, int ln, __MCS_NEW_PLUG2*)
	{return;}
__inline void __cdecl operator delete(void* ptr, void*, __MCS_NEW_PLUG2*)
	{return;}
//===========================================================================
template <class TYPE>
__inline void _mcsDeleteArr(TYPE* arrptr,LPCSTR cpfn,int cpln)
{
	if(arrptr==NULL) 
		return;

	__int64 dummy[2] = {0, 0};
	::new(__FILE__, __LINE__, (__MCS_NEW_PLUG2*)dummy) TYPE[0];
	DWORD szCountField = (DWORD)dummy[1];
	DWORD* pCount = (DWORD*) ((byte*)arrptr - szCountField);
	DWORD nE = *pCount;

	for(DWORD i=0; i<nE; i++)
		arrptr[i].~TYPE();

	gpMcsMemAllocator->McsFree(pCount, cpfn, cpln, true);
}
//===========================================================================

#define mcsMemIsMTBlock(ptr)       gpMcsMemAllocator->IsMTBlock(ptr)
#define mcsMemAlloc(size)          gpMcsMemAllocator->McsAlloc(size, __FILE__, __LINE__, false)
#define mcsMemReAlloc(ptr,newsize) gpMcsMemAllocator->McsReAlloc(ptr, newsize, __FILE__, __LINE__)
#define mcsMemFree(ptr)            gpMcsMemAllocator->McsFree(ptr,  __FILE__,  __LINE__, false)
#define mcsMemNew(Constructor)     ::new(__FILE__, __LINE__, __MNP__) Constructor
#define mcsMemDelete(ptr)          _mcsDelete(ptr, __FILE__, __LINE__)
#define mcsMemDeleteArr(ptr)       _mcsDeleteArr(ptr, __FILE__, __LINE__)

#define DECLARE_OBJ_NEWDEL \
	static void* operator new(size_t size) {return mcsMemAlloc(size);} \
	static void operator delete(void* ptr) {mcsMemFree(ptr);} \
	static void* operator new[](size_t size) {return mcsMemAlloc(size);} \
	static void operator delete[](void* ptr) {mcsMemFree(ptr);} \
	static void* operator new(size_t _Count, void* _Ptr) {return _Ptr;}\
	static void operator delete(void*, void*) {} \
	/* 10.03.2009, two lines below need for compile with debug MFC*/ \
	void* PASCAL operator new(size_t nSize, LPCSTR lpszFileName, int nLine) {return mcsMemAlloc(nSize);} \
	void  PASCAL operator delete(void* ptr, LPCSTR lpszFileName, int nLine) {mcsMemFree(ptr);}

//===========================================================================
#ifdef STATICLINK_MT_DLL
	#pragma comment(lib,"mt.lib")
	extern "C" void __declspec(dllimport) InitAGLMemMan();
#endif
//===========================================================================

#if !defined(_NCAD_BUILD_) && !defined(_MCS_CORE_ONLY)
	#include "McsMemInternal.h"
#endif
