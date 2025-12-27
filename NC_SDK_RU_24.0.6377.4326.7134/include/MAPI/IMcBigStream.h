#pragma once

#include "IMcStream.h"
#include <vector>

enum McBigStreamVerEnum
{
	kBVE_unk = 0,
	kBVE_V1  = 1,
};

enum McBigStreamTypeFlagsEnum
{
	// low-level contents types
	kBSType_Uncompressed        = 0x00000000,
	kBSType_Zip                 = 0x00000001,

	// contents type flags
	// ...

	// composite values
	kBSType_Default             = kBSType_Uncompressed,

	// masks
	kBSType_CompressionMask     = kBSType_Zip,
	kBSType_LowLevelTypeMask    = 0x000000FF,
	kBSType_ContentsTypeMask    = 0x00FF0000,
};

//-------------------------------------------------------------------------------------------------
// McBigStream
// Представляет собой переработаный MtStream, у которого:
//  - внутреннее хранилище - std::vector<byte>, размер которого ограничен типом size_t (в Win64 - uint64, в Win32 - uint32).
//  - вырезан функционал ссылок на повторящиеся строки и mcsWorkID-ы.
// Служит для хранения большого количества платформенно независимых данных.
//-------------------------------------------------------------------------------------------------
IMCS_DECL_INTERFACE(IMcBigStream, "5CDF8043-2520-42CD-8CAE-AA2B5090DF68")
struct IMcBigStream : public IUnknown
{
	virtual ~IMcBigStream(){}

	virtual DWORD   getStreamMajorVer() = 0;
	virtual DWORD   getStreamMinorVer() = 0;

		// call it before write anything
		// user version (not stream version)
	virtual HRESULT putVersion(WORD major, WORD minor=0, WORD revision=0) = 0; 
	virtual HRESULT putByte(byte) = 0;
	virtual HRESULT putBool(bool) = 0;

	HRESULT putBoolArr(const mcsBoolArray& bArr)
	{
		return putData(bArr.GetData(), bArr.GetSize());
	}

	virtual HRESULT putDword(DWORD) = 0;
	virtual HRESULT putIntArr(const mcsIntArray&) = 0;
	virtual HRESULT putI64(__int64) = 0;
	virtual HRESULT putDouble(double f) = 0;
	virtual HRESULT putDoubleArr(const mcsDoubleArray&) = 0;

	virtual HRESULT putString(
		LPCSTR pStr,
		int    nChars = -1                 // -1 means detect a length automatically
	) = 0;

	virtual HRESULT putString(
		LPCWSTR pStr,
		int     nChars = -1,                 // -1 means detect a length automatically
		bool    bCheckAnsiInUnicode = true  // if == true, ANSI strings in a UNICODE buffer will be stored as ANSI; slow but keeps space
	) = 0; 

	// if bOptimizeRepeatable == true, repeatable strings will be written once only; slow, but keeps space
	virtual HRESULT putString(const McsStringA& strA) = 0;

	// if bOptimizeRepeatable == true, repeatable strings will be written once only; slow, but keeps space
	// if bCheckAnsiInUnicode == true, ANSI strings in a UNICODE buffer will be stored as ANSI; slow but keeps space
	virtual HRESULT putString(const McsStringW& strW, bool bCheckAnsiInUnicode = true) = 0;

	virtual HRESULT putStringArr(const mcsStringArrayA& strArrA) = 0;

	virtual HRESULT putStringArr(
		const mcsStringArrayW& strArrW,
		bool                   bCheckAnsiInUnicode = true // if == true, ANSI strings in a UNICODE buffer will be stored as ANSI; slow but keeps space
	) = 0;

	// Если указан второй параметр, он подменяет опции в первом параметре.
	virtual HRESULT putWorkID(const mcsWorkID& id, IN OPTIONAL DWORD dwServiceFlags = 0) = 0;

	virtual HRESULT putWorkIDArr(const mcsWorkIDArray&) = 0;
	virtual HRESULT putGUID(const GUID&) = 0;
	virtual HRESULT putGUIDArr(const mcsGUIDArray&) = 0;
	virtual HRESULT putDwordPtr(UINT_PTR) = 0;

	HRESULT putByteArr(const mcsByteArray& btArr)
	{
		return putData(btArr.GetData(), btArr.GetSize());
	}

	virtual HRESULT putData(const void* pData, UINT nSize) = 0; // saves size and data

	virtual HRESULT putStream(IMcsStream*) = 0; // used to store sub-stream
	virtual HRESULT addStreamData(IMcBigStream*) = 0; // used to merge streams

		// call it before read anything
		// user version (not stream version)
	virtual HRESULT getVersion(OUT WORD& Major, OUT OPTIONAL WORD* pMinor=NULL, OUT OPTIONAL WORD* pRevision=NULL) = 0;
	virtual HRESULT getByte(OUT byte&) = 0;

	virtual HRESULT getBool(OUT BOOL& bV)
	{
		bool bb = false;
		HRESULT hRes = getBool(bb);
		bV = bb ? TRUE : FALSE;
		return hRes;
	}

	virtual HRESULT getBool(OUT bool&) = 0;

	HRESULT getBoolArr(OUT mcsBoolArray& bArr)
	{
		return getData((mcsByteArray&)bArr);
	}

	virtual HRESULT getDword(OUT DWORD&) = 0;
	virtual HRESULT getDword(OUT int& D) = 0;
	virtual HRESULT getDword(OUT long& D) = 0;
	virtual HRESULT getIntArr(OUT mcsIntArray&) = 0;
	virtual HRESULT getI64(OUT __int64&) = 0;
	virtual HRESULT getDouble(OUT double&) = 0;
	virtual HRESULT getDoubleArr(OUT mcsDoubleArray&) = 0;
	virtual HRESULT getString(OUT McsStringA& mbStr) = 0;
	virtual HRESULT getString(OUT McsStringW& unicodeStr) = 0;
	virtual HRESULT getString(OUT CHAR* strBuffer /*ANSI | MB*/, IN DWORD iBufTotalSize/*in bytes*/) = 0; // can return MCS_E_BUFFER_TOO_SMALL if buffer size is insufficient
	virtual HRESULT getString(OUT WCHAR* strBuffer /*UNICODE*/, IN DWORD iBufTotalSize/*in bytes*/) = 0; // can return MCS_E_BUFFER_TOO_SMALL if buffer size is insufficient
	virtual HRESULT getStringArr(OUT mcsStringArrayA&) = 0;
	virtual HRESULT getStringArr(OUT mcsStringArrayW&) = 0;

		// если pIdOriginal не NULL, вернёт записанное значение (без коррекции)
		// (!) заполняется только если выполнение прошло успешно
	virtual HRESULT getWorkID(OUT mcsWorkID& id, OUT OPTIONAL mcsWorkID* pIdOriginal = NULL) = 0;

	virtual HRESULT getWorkIDArr(OUT mcsWorkIDArray&) = 0; // automatically detects array size
	virtual HRESULT getGUID(OUT GUID&) = 0;
	virtual HRESULT getGUIDArr(OUT mcsGUIDArray&) = 0; // automatically detects array size
	virtual HRESULT getDwordPtr(UINT_PTR& uiPtr) = 0;
	virtual HRESULT getDwordPtr(INT_PTR& uiPtr) {return getDwordPtr((UINT_PTR&)uiPtr);}

	HRESULT getByteArr(OUT mcsByteArray& btArr)
	{
		return getData(btArr);
	}

	virtual HRESULT getData(OUT mcsByteArray&) = 0; // automatically detects data block length

	virtual HRESULT getStream(OUT IMcsStreamPtr& pSubStream) = 0;

	// system only: returns a reference to internally stored data, copy it as soon as possible
	virtual HRESULT _getData(OUT LPCVOID& pData, OUT DWORD& sz) = 0;

		// misc methods
	virtual McsStreamTagTypeEnum getCurrentTagType() = 0;

		// use this method once per complete version block of data;
		// then you can in older version of software safely read new blocks of data
	virtual HRESULT writeVersionBlockEnd() = 0; 
	virtual HRESULT readVersionBlockEnd()
	{
		return seek(0,MCSSTREAM_SEEK_VEREND);
	}; 

		// on this method stream resets internal helper data and further write is impossible
	virtual HRESULT writeComplete() = 0;

		// если в процессе записи возникли сбои, либо в памяти, либо в callback, то этот факт можно обнаружить этим вызовом
	virtual bool    hasWriteErrors() = 0;

		// if seekMode is MCSSTREAM_SEEK_TAG then iOffset is number of tags to move, bytes - otherwise
		// with MCSSTREAM_SEEK_TAG can move only in forward direction (iOffset>0)
	virtual HRESULT seek(intptr_t iOffset, DWORD seekMode) = 0; // on error position is not changed
	
	// 24.01.2011
	HRESULT seekStart()
		{return seek(0, MCSSTREAM_SEEK_BEGIN);}
	HRESULT seekEnd()
		{return seek(0, MCSSTREAM_SEEK_END);}
	HRESULT seekSkipTag()
		{return seek(1, MCSSTREAM_SEEK_TAG);}

	virtual size_t  tell() = 0; // tells internal data pointer position in bytes (from beginning)
	virtual HRESULT reset(IN OPTIONAL DWORD dwTypeFlags = kBSType_Default, bool bKeepBuffer = false) = 0; // clears stream contents, position at the start
	virtual bool    isEmpty() = 0; // returns true if stream doesn't contains any data

		// advanced methods
	virtual HRESULT raiseVersionAlert() = 0; // after call you must read or write version
	virtual size_t  getStreamDataSize(IN OPTIONAL bool fCompressed=false) = 0; // with stream header (used to store stream data)
	virtual LPCVOID getStreamRawData(IN OPTIONAL bool fCompressed=false) = 0; // with stream header (used to restore stream data)

		// if 'pSrcRawData' points to a buffer that was previously returned by getStreamInternalBuffer(),
		// a stream will just initialize itself using a data inside its own buffer
	virtual HRESULT setStreamRawData(LPCVOID pSrcRawData, size_t size) = 0;

	virtual HRESULT check() = 0; // check stream contents (using header and tag records)

		// BigStream Header checking
	virtual bool    isFileWithBigStream(IN LPCTSTR cstrFileName) = 0;
	virtual bool    isRawDataWithBigStream(IN LPCVOID pRawData, IN size_t size) = 0;
	virtual bool    checkCompatibleSizeT(IN LPCTSTR cstrFileName) = 0;
	virtual bool    checkCompatibleSizeT(IN LPCVOID pRawData, IN size_t size) = 0;

		// transfer compatibility
	virtual HRESULT loadFromFile(IN LPCTSTR cstrFileName) = 0;
	virtual HRESULT saveToFile(IN LPCTSTR cstrFileName, IN OPTIONAL bool fCompressed = false) = 0;

		// caller defined tag which describes contents of the stream,
		// this tag can help to identify data in stream before read
	virtual HRESULT setContentTypeTag(IN DWORD tag) = 0;
	virtual HRESULT getContentTypeTag(OUT DWORD& tag) = 0;

		// makes exact copy of data into <pStream>
	virtual HRESULT getCopy(OUT IMcBigStream* pStream) = 0;
};

//-------------------------------------------------------------------------------------------------
#ifndef MCBIMACCESS_API
  #ifdef MCBIMACCESS_EXPORTS
   #define MCBIMACCESS_API __declspec(dllexport) 
  #else
   #define MCBIMACCESS_API __declspec(dllimport) 
  #endif
#endif

extern "C" MCBIMACCESS_API HRESULT mcsCreateMcBigStream(OUT IMcBigStreamPtr&, DWORD dwTypeFlags = kBSType_Default);

//-------------------------------------------------------------------------------------------------
__inline IMcBigStreamPtr mcsCreateMcBigStreamDyn()
{
	IMcBigStreamPtr pBigS;
	FARPROC pProc = GetProcAddress(GetModuleHandleA("McBimAccess.dll"), "mcsCreateMcBigStream");
	if (pProc)
		((HRESULT*(*)(IMcBigStreamPtr&, DWORD))pProc)(pBigS, kBSType_Default);
	return pBigS;
}

//-------------------------------------------------------------------------------------------------
#define MCBIGSTREAM_DICTIONARY_NAME _T("MC_BIGSTREAM_DICT")
