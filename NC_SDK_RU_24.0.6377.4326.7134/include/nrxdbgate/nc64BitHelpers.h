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

#ifndef __NC64BITHELPERS_H__
#define __NC64BITHELPERS_H__
#include "typesDb.h"

#define Nc64Assert NcTcsLen_Assert

#ifndef _WIN64

#ifdef GetWindowLongPtr
#undef GetWindowLongPtr
#endif

inline LONG_PTR __stdcall GetWindowLongPtr(HWND h, int n)
{
	return static_cast<LONG_PTR>(::GetWindowLong(h, n));
}

#ifdef SetWindowLongPtr
#undef SetWindowLongPtr
#endif
inline LONG_PTR __stdcall SetWindowLongPtr(HWND h, int n, LONG_PTR v)
{
	const long nLongV = static_cast<long>(v);
	return static_cast<LONG_PTR>(::SetWindowLong(h, n, nLongV));
}

inline LONG_PTR __stdcall SetWindowLongPtr(HWND h, int n, void * v)
{
	const LONG_PTR vPtr = reinterpret_cast<LONG_PTR>(v);
	return ::SetWindowLongPtr(h, n, vPtr);  // call above overload
}

#ifdef GetClassLongPtr
#undef GetClassLongPtr
#endif

inline ULONG_PTR __stdcall GetClassLongPtr(HWND h, int n)
{
	return static_cast<ULONG_PTR>(::GetClassLong(h, n));
}

#ifdef SetClassLongPtr
#undef SetClassLongPtr
#endif

inline ULONG_PTR __stdcall SetClassLongPtr(HWND h, int n, LONG_PTR v)
{
	const long vLong = static_cast<long>(v);
	return static_cast<ULONG_PTR>(::SetClassLong(h, n, vLong));
}

inline ULONG_PTR __stdcall SetClassLongPtr(HWND h, int n, void * v)
{
	const ULONG_PTR vPtr = reinterpret_cast<ULONG_PTR>(v);
	return ::SetClassLongPtr(h, n, vPtr);  // call above overload
}

#ifdef offsetof
#undef offsetof
#endif

#define offsetof(s,m) static_cast<unsigned>( \
             reinterpret_cast<UINT_PTR> (\
                 &reinterpret_cast<const volatile char&>( \
                     reinterpret_cast<const s *>(0)->m )))

#else  // !_WIN64

#ifdef HIWORD
#undef HIWORD
#endif
#define HIWORD(v) (static_cast<WORD>((((DWORD_PTR)(v) >> 16) & 0xFFFF)))

#endif // _WIN64

#ifdef  HIBYTE
#undef HIBYTE
#endif
#define HIBYTE(w)           LOBYTE((DWORD_PTR)(w) >> 8)

#pragma warning(push)
#pragma warning(disable:4100)//disable unreferenced formal parameter warning
inline int NcIntPtrToInt(NRX::LongPtr nVal, NRX::LongPtr nLimit = /*16M*/0x1000000)
{
	Nc64Assert(nVal < nLimit);
	Nc64Assert(nVal > -nLimit);
	const int nRet = static_cast<int>(nVal);
	Nc64Assert(nRet == nVal);
	return nRet;
}

inline unsigned int NcUIntPtrToUInt(NRX::ULongPtr nVal, NRX::ULongPtr nLimit = /*16M*/0x1000000)
{
	Nc64Assert(nVal < nLimit);
	const unsigned int nRet = static_cast<unsigned int>(nVal);
	Nc64Assert(nRet == nVal);
	return nRet;
}
#pragma warning(pop)

inline int NcCastUINT_PTRToInt(UINT_PTR pVal)
{
	Nc64Assert(pVal <= UINT_MAX );
	Nc64Assert(pVal >= 0);
	const int nRet = static_cast<int>(pVal);
	if( pVal )
		Nc64Assert(nRet == pVal);
	return nRet;
}

inline int NcCastLONG_PTRToInt(LONG_PTR pVal)
{
	Nc64Assert(pVal <= INT_MAX );
	Nc64Assert(pVal <= INT_MIN );
	const int nRet = static_cast<int>(pVal);
	if( pVal )
		Nc64Assert(nRet == pVal);
	return nRet;
}

inline int NcCastPtrDiffToInt(ptrdiff_t nVal)
{
	Nc64Assert(nVal <= INT_MAX );
	Nc64Assert(nVal >= (ptrdiff_t)INT_MIN );
	const int nRet = static_cast<int>(nVal);
	Nc64Assert(nRet == nVal);
	return nRet;
}
inline NRX::UInt32 NcCastUIntPtrToOdUInt32(NRX::UIntPtr pVal)
{
#ifdef _WIN64
	Nc64Assert(pVal <= ULONG_MAX );
#else
	Nc64Assert(pVal <= UINT_MAX );
#endif
	Nc64Assert(pVal >= 0);
	const NRX::UInt32 nRet = static_cast<NRX::UInt32>(pVal);
	if( pVal )
		Nc64Assert(nRet == pVal);
	return nRet;
}

inline NRX::UInt32 NcCastInt64ToOdUInt32(NRX::Int64 nVal)
{
#ifdef _WIN64
	Nc64Assert(nVal <= ULONG_MAX );
#else
	Nc64Assert(nVal <= UINT_MAX );
#endif
	Nc64Assert(nVal >= 0);
	const NRX::UInt32 nRet = static_cast<NRX::UInt32>(nVal);
	Nc64Assert(nRet == nVal);
	return nRet;
}

inline intptr_t* NcCastResvalRlnameToPtr(nds_u_val& resval)
{
	intptr_t* pRet;
	pRet = (intptr_t*)resval.rlname;
	//Nc64Assert(pRet == resval.rlname);
	return pRet;
}

inline intptr_t NcCastResvalRlnameItemToPtr(nds_u_val resval, unsigned int index)
{
	intptr_t pRet;
	pRet = (intptr_t)resval.rlname[index];
	Nc64Assert(pRet == resval.rlname[index]);
	return pRet;
}

inline int NcCastSize_tToInt(size_t nVal)
{
	Nc64Assert(nVal <= INT_MAX );
	const int nRet = static_cast<int>(nVal);
	Nc64Assert(nRet == nVal);
	return nRet;
}

inline intptr_t NcCastLongToPtr(long nVal)
{
	Nc64Assert(nVal >= 0);
	intptr_t pRet = (intptr_t)(nVal);
	Nc64Assert(pRet == nVal);
	return pRet;
}

inline NRX::LongPtr NcCastPtrToLongPtr(intptr_t pVal)
{
	NRX::LongPtr pRet = static_cast<NRX::LongPtr>(pVal);
	
	if (pVal)
		Nc64Assert(pRet == pVal);

	return pRet;
}

inline NRX::LongPtr* NcCastPtrPtrToLongPtr(intptr_t *pVal)
{
	NRX::LongPtr* pRet = (NRX::LongPtr*)pVal;
	
	if (pVal)
		Nc64Assert(*pRet == *pVal);

	return pRet;
}

inline NRX::UIntPtr NcCastPtrToUIntPtr(intptr_t pVal)
{
	NRX::UIntPtr pRet = static_cast<NRX::UIntPtr>(pVal);
	
	if (pVal)
		Nc64Assert(pRet == pVal);

	return pRet;
}

inline INT_PTR NcCastPtrToINT_PTR(intptr_t pVal)
{
	Nc64Assert(pVal >= 0);
	INT_PTR pRet = static_cast<INT_PTR>(pVal);
	
	Nc64Assert(pRet == pVal);
	return pRet;
}

inline int NcCastPtrToInt(intptr_t pVal)
{
	Nc64Assert(pVal <= INT_MAX );
	Nc64Assert(pVal >= INT_MIN);
	int nRet = static_cast<int>(pVal);
	
	if (pVal)
		Nc64Assert(nRet == pVal);

	return nRet;
}

inline INT_PTR NcCastIntToINT_PTR(int nVal)
{
	Nc64Assert(nVal >= 0);
	INT_PTR nRet = static_cast<INT_PTR>(nVal);
	
	Nc64Assert(nRet == nVal);
	return nRet;
}

inline INT_PTR NcCastUIntPtrToINT_PTR(NRX::UIntPtr pVal)
{
	INT_PTR pRet = static_cast<INT_PTR>(pVal);
	
	Nc64Assert(pRet == pVal);
	return pRet;
}

inline size_t NcCastUINTToSize_t(UINT nVal)
{
	size_t nRet = static_cast<size_t>(nVal);
	
	Nc64Assert(nRet == nVal);
	return nRet;
}

inline size_t NcCastIntToSize_t(int nVal)
{
	Nc64Assert(nVal >= 0);
	size_t nRet = (size_t)nVal;
	
	Nc64Assert(nRet == nVal);
	return nRet;
}

inline size_t NcCastUIntToSize_t(unsigned int nVal)
{
	size_t nRet = (size_t)nVal;
	
	Nc64Assert(nRet == nVal);
	return nRet;
}

inline size_t NcCastDWORDToSize_t(DWORD nVal)
{
	size_t nRet = (size_t)nVal;
	
	Nc64Assert(nRet == nVal);
	return nRet;
}

inline size_t NcCastOdInt32ToSize_t(NRX::UInt32 nVal)
{
	Nc64Assert(nVal >= 0);
	size_t nRet = (size_t)nVal;
	
	Nc64Assert(nRet == nVal);
	return nRet;
}

inline size_t NcCastOdUInt32ToSize_t(NRX::UInt32 nVal)
{
	size_t nRet = (size_t)nVal;
	
	Nc64Assert(nRet == nVal);
	return nRet;
}
typedef ptrdiff_t HostGsMarker/*OdGsMarker*/;
inline const HostGsMarker* NcCastLongPtrToOdGsMarker(const NRX::LongPtr *pVal)
{
	const HostGsMarker* pRet = (HostGsMarker*)(pVal);
	
	if (pVal)
		Nc64Assert(*pRet == *pVal);

	return pRet;
}

inline NRX::LongPtr NcCastOdGsMarkerToLongPtr(HostGsMarker val)
{
	NRX::LongPtr retVal = (NRX::LongPtr)(val);
	Nc64Assert(retVal == val);
	return retVal;
}

inline NRX::LongPtr __stdcall NcStrToIntPtr(const wchar_t * s)
{
#ifdef _WIN64
	return _wtoi64(s);
#else
	return _wtoi(s);
#endif
}

#endif //__NC64BITHELPERS_H__
