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


#include "McsTempl.h"
#include "MCSTypes.h"
#pragma comment(lib,"COMSUPP.LIB")

#include "DynLoadMacro.h"
#include "IMcErrors.h"

#include "SubentData.h"

// AGL: since 22.07.2005 stream split into two parts: one (basic) part
// implemented in MT.DLL, other (depends on MehcaniCS data types) implemented
// in MCTYP.DLL

// IMtStream can read/write only basic tags, such as numbers, strings and so on;
// IMcsStream can write additionaly complex data: MCSVariant/exValue/geometry data,...;
// Implementation of IMcsStream is derived from implementation of IMtStream so both streams
// can be initialized with the same input data, but basic implementation not able
// to read and write complex tags, but can identify and handle them	if basic stream
// will be initialized with data from IMcsStream

//===========================================================================
#define MCSSTREAM_SEEK_BEGIN -1
#define MCSSTREAM_SEEK_CUR    0
#define MCSSTREAM_SEEK_END    1
#define MCSSTREAM_SEEK_TAG    2
#define MCSSTREAM_SEEK_VEREND 3
//===========================================================================
// Mcs stream contents data tags
// must be within 0-255 range
// !!! DO NOT MODIFY EXISTING VALUES !!! (exclude last - topVal)
// !!! ENUMERATE VALUES CONSEQUENTLY (NEXT = PREV+1) !!! (need to test stream integrity)
enum McsStreamTagTypeEnum
{
	// V4
	kMST_unk           =  0, 
	kMST_Version       =  1, 
	kMST_Byte          =  2, 
	kMST_Dword         =  3, 
	kMST_IntArr        =  4, 
	kMST_I64           =  5, 
	kMST_Double        =  6, 
	kMST_DoubleArr     =  7, 
	kMST_FPoint        =  8, // -- MCTYP.DLL
	kMST_String        =  9, 
	kMST_StringArr     = 10, 
	kMST_Point         = 11, // -- MCTYP.DLL
	kMST_Vector        = 12, // -- MCTYP.DLL
	kMST_WorkID        = 13,
	kMST_WorkIDArr     = 14,
	kMST_GE            = 15, // -- MCTYP.DLL
	kMST_GEArr         = 16, // -- MCTYP.DLL
	kMST_Variant       = 17, // -- MCTYP.DLL
	kMST_VariantArr    = 18, // -- MCTYP.DLL
	kMST_Data          = 19, 
	kMST_PointArr      = 20, // -- MCTYP.DLL
	kMST_VectorArr     = 21, // -- MCTYP.DLL
	kMST_SubStream     = 22, 
	kMST_ExValue	     = 23, // -- MCTYP.DLL
	kMST_ExValueArr    = 24, // -- MCTYP.DLL
	kMST_Bool          = 25, 
	kMST_VBlkEnd       = 26, 
	kMST_Matrix        = 27, // -- MCTYP.DLL
	kMST_GUID          = 28, // only 128-bit data for GUID
	kMST_GUIDArr       = 29, // only 128-bit data for GUID
	kMST_BoundBlock    = 30, // -- MCTYP.DLL

	// V5+
	kMST_Version_MOiB  = 31, // major only in byte
	kMST_Version_MmiW  = 32, // major, minor only in WORD, 1'st byte - major, second - minor
	kMST_Version_MmR   = 33, // major, minor, revision in bytes, in the same order
	kMST_Dword_0       = 34, // 0
	kMST_IntArr_E      = 35, // empty
	kMST_I64_0         = 36, // 0
	kMST_Double_0      = 37, // 0.0
	kMST_Double_Int    = 38, // integer 1-0xFFFFFFFF in double
	kMST_DoubleArr_E   = 39, // empty
	kMST_FPoint_0      = 40, // {0.0; 0.0} -- MCTYP.DLL
	kMST_String_E      = 41, // ""
	kMST_String_Ref    = 42, // A ref to a previously stored string, next dword is a negative packed offset to the kMST_String tag before
	kMST_StringArr_E   = 43, // empty
	kMST_Point_0       = 44, // {0.0; 0.0; 0.0} -- MCTYP.DLL
	kMST_Vector_0      = 45, // {0.0; 0.0; 0.0} -- MCTYP.DLL
	kMST_Vector_X      = 46, // {1.0; 0.0; 0.0} -- MCTYP.DLL
	kMST_Vector_Y      = 47, // {0.0; 1.0; 0.0} -- MCTYP.DLL
	kMST_Vector_Z      = 48, // {0.0; 0.0; 1.0} -- MCTYP.DLL
	kMST_WorkID_0      = 49, // WID_NULL
	kMST_WorkIDArr_E   = 50, // empty
	kMST_GEArr_E       = 51, // empty -- MCTYP.DLL
	kMST_VariantArr_E  = 52, // empty -- MCTYP.DLL
	kMST_PointArr_E    = 53, // empty -- MCTYP.DLL
	kMST_VectorArr_E   = 54, // empty -- MCTYP.DLL
	kMST_ExValueArr_E  = 55, // empty -- MCTYP.DLL
	kMST_Matrix_E      = 56, // identity -- MCTYP.DLL
	kMST_GUID_0        = 57, // GUID_NULL
	kMST_GUIDArr_E     = 58, // empty
	kMST_BoundBlock_E  = 59, // degenerated block -- MCTYP.DLL
	kMST_Point_2d      = 60, 
	kMST_Vector_2d     = 61, 

	kMST_DwordPtr_0    = 62, // zero UINT_PTR
	kMST_DwordPtr      = 63,

	// V8+
	kMST_GEArrRaw      = 64, // -- MCTYP.DLL

	// V10+
	kMST_WorkID_SubEnt = 65, // Parent kMST_WorkID + Subent Data
	kMST_WorkIDArr_SubEnt = 66, // array of IDs, one of vals contains SubentID

	// V11+
	kMST_WorkID_def_ref  = 67, // Ссылка на ранее записанный mcsWorkID, при этом опции будут mcsWorkID_DefOption
	kMST_WorkID_obj_ref  = 68, // Ссылка на ранее записанный mcsWorkID, при этом опции будут mcsWorkID_ID_IS_OBJECT_ID
	kMST_WorkID_hard_ref = 69, // Ссылка на ранее записанный mcsWorkID, при этом опции будут mcsWorkID_ID_HardRef
	kMST_WorkID_guid_ref = 70, // Ссылка на ранее записанный mcsWorkID, при этом опции будут mcsWorkID_ID_IS_GUID

	// keep this value at the end of list and it must be greater by 1 than the last valid val
	_kMST_TopVal,
};
#define MS_TOP_V4_TAG kMST_Dword_0
//===========================================================================
enum McsStreamTypeFlagsEnum
{
	// low-level contents types
	kMSType_Uncompressed        = 0x00000000,
	kMSType_LZW                 = 0x00000001,
	kMSType_ZLib                = 0x00000002,

	// будет считать CRC и проверять его при установке данных (только для несжатых данных)
	kMSType_Check_CRC           = 0x00000004,

	// 03.05.2023
	// Флаг указывает использовать оптимизацию записи ID для версии 11 потока.
	// Игнорируется, если указан kMSType_PlatformIndependent.
	kMSType_v11_UseIdOpt        = 0x00000008,

	// contents type flags ..................................................
	kMSType_PlatformDependent   = 0x00000000,
	kMSType_PlatformIndependent = 0x00010000,

	// если этот флаг установлен, то метод IMtStream::getWorkIDArr не будет очищать массив идентификаторов на входе;
	// т.е. указывает на то, нужно ли накапливать идентификаторы в массиве, или нужно просто их возвращать;
	// используется в переносе зависимостей между группами объектов, устанавливается, например, в IMtStream::transferInternalLinks
	// и в VirtualObject.cpp CMCSObject::readConstraintData.
	kMSType_AddonContents       = 0x00020000,

	// 26.01.13
	// если указан, то объект записывается для целей UndoPoint
	kMSType_ForUndoPoint        = 0x00040000,

	// composite values
	kMSType_Default             = kMSType_Uncompressed | kMSType_PlatformDependent, 
	kMSType_PureData            = kMSType_Uncompressed | kMSType_PlatformIndependent, 

	// masks
	kMSType_CompressionMask     = kMSType_LZW | kMSType_ZLib,
	kMSType_LowLevelTypeMask    = 0x000000FF,
	kMSType_ContentsTypeMask    = 0x00FF0000,
};
//===========================================================================
enum McsStreamDwgFilerTypeEnum
{
	kMSDF_Undefined = -1,
	kMSDF_FileFiler = 0,
	kMSDF_CopyFiler = 1,
	kMSDF_UndoFiler = 2,
	kMSDF_BagFiler = 3,
	kMSDF_IdXlateFiler = 4,
	kMSDF_PageFiler = 5,
	kMSDF_DeepCloneFiler = 6,
	kMSDF_IdFiler = 7,
	kMSDF_PurgeFiler = 8,
	kMSDF_WblockCloneFiler = 9
};
//==============================================================================

enum McsStreamVerEnum
{
	kMVE_unk   = 0,
	kMVE_MCS4  = 1,
	kMVE_MCS5  = 2,
	kMVE_MCS5c = 3, // kMVE_MCS5 + support for ZLib compression and base 64 encoding for strings
	kMVE_MCS7  = 4, // used header from V5 but added some new tags
	kMVE_MCS8  = 5, // v7 + optimized tag for GEArr
	kMVE_MCS10 = 6, // SubentID support

	// Запись дубликатов WorkID как ссылок (по аналогии со строками)
	// При этом ссылки пишутся как оптимизированный DWORD
	// Для этих ссылок на ID не зовется OnWriteID, OnReadID, только для оригинала, на который сохранена ссылка
	// для WID_NULL не зовется OnWriteID, OnReadID
	// Массивы WorkID пишутся теперь не блоком, а отдельными WorkID, чтобы можно было использовать оптимизацию записи WorkID.
	kMVE_MCS11 = 7,
};
//===========================================================================

typedef void (__cdecl* mtstrCorrProcA)(IN OUT McsStringA&);
typedef void (__cdecl* mtstrCorrProcW)(IN OUT McsStringW&);
//===========================================================================

// Базовый класс наблюдателя за ID при работе со стримами;
// Обеспечивает только функционал подключения/отключения

struct MtStreamIdsWatcher
{
protected:
	MtStreamIdsWatcher* m_pPrevWatcher;
	MtStreamIdsWatcher* m_pNextWatcher;

	MT_API static MtStreamIdsWatcher* s_pActiveWatcher;

public:
	MT_API MtStreamIdsWatcher();
	MT_API virtual ~MtStreamIdsWatcher();

	MT_API virtual bool attach();
	MT_API virtual bool detach();
	MT_API virtual bool isAttached();
	MT_API virtual bool isActive();

	__inline static MtStreamIdsWatcher* getActive() {
		return s_pActiveWatcher;
	}

	MT_API virtual HRESULT OnWriteID(IN const mcsWorkID&);
	MT_API virtual HRESULT OnReadID(IN OUT mcsWorkID&);
};
//===========================================================================
#include "objidl.h" // std IStream

// Implementation in MT.DLL
struct IMtStream : public IUnknown
{
	virtual ~IMtStream(){}

	virtual DWORD   getStreamMajorVer() = 0;
	virtual DWORD   getStreamMinorVer() = 0;

		// call it before write anything
		// user version (not stream version)
	virtual HRESULT putVersion(WORD major, WORD minor=0, WORD revision=0) = 0; 
	virtual HRESULT putByte(byte) = 0;
	virtual HRESULT putBool(bool) = 0;

	HRESULT putBoolArr(const mcsBoolArray& bArr) {
		return putData(bArr.GetData(), bArr.GetSize());
	}

	virtual HRESULT putDword(DWORD) = 0;
	virtual HRESULT putIntArr(const mcsIntArray&) = 0;
	virtual HRESULT putI64(__int64) = 0;
	virtual HRESULT putDouble(double f) = 0;
	virtual HRESULT putDoubleArr(const mcsDoubleArray&) = 0;

	virtual HRESULT putString(
		LPCSTR pStr,
		int    nChars = -1,                 // -1 means detect a length automatically
		bool   bOptimizeRepeatable = false  // if == true, repeatable strings will be written once only; slow, but keeps space
	) = 0;

	virtual HRESULT putString(
		LPCWSTR pStr,
		int     nChars = -1,                 // -1 means detect a length automatically
		bool    bOptimizeRepeatable = false, // if == true, repeatable strings will be written once only; slow, but keeps space
		bool    bCheckAnsiInUnicode = true  // if == true, ANSI strings in a UNICODE buffer will be stored as ANSI; slow but keeps space
	) = 0; 

	// if bOptimizeRepeatable == true, repeatable strings will be written once only; slow, but keeps space
	virtual HRESULT putString(const McsStringA& strA, bool bOptimizeRepeatable = false) = 0;

	// if bOptimizeRepeatable == true, repeatable strings will be written once only; slow, but keeps space
	// if bCheckAnsiInUnicode == true, ANSI strings in a UNICODE buffer will be stored as ANSI; slow but keeps space
	virtual HRESULT putString(const McsStringW& strW, bool bOptimizeRepeatable = false, bool bCheckAnsiInUnicode = true) = 0;

	virtual HRESULT putStringArr(
		const mcsStringArrayA& strArrA,
		bool                   bOptimizeRepeatable = false // if == true, repeatable strings will be written once only; slow, but keeps space
	) = 0;

	virtual HRESULT putStringArr(
		const mcsStringArrayW& strArrW,
		bool                   bOptimizeRepeatable = false, // if == true, repeatable strings will be written once only; slow, but keeps space
		bool                   bCheckAnsiInUnicode = true // if == true, ANSI strings in a UNICODE buffer will be stored as ANSI; slow but keeps space
	) = 0;

	// Если указан второй параметр, он подменяет опции в первом параметре.
	virtual HRESULT putWorkID(const mcsWorkID& id, IN OPTIONAL DWORD dwServiceFlags = 0) = 0;

	virtual HRESULT putWorkIDArr(const mcsWorkIDArray&) = 0;
	virtual HRESULT putGUID(const GUID&) = 0;
	virtual HRESULT putGUIDArr(const mcsGUIDArray&) = 0;
	virtual HRESULT putDwordPtr(UINT_PTR) = 0;

	HRESULT putByteArr(const mcsByteArray& btArr) {
		return putData(btArr.GetData(), btArr.GetSize());
	}

	virtual HRESULT putData(const void* pData, UINT nSize) = 0; // saves size and data

		// Creates a child substream using a buffer of this (parent) stream
		// 'pSubStream' may be NULL, a stream object will be created automatically in this case
		// (!) THE NEXT CALL MUST BE putSubStreamEnd(...)
		// (!) DO NOT KEEP a pointer to 'pSubStream' if this-stream is dead
	virtual HRESULT putSubStreamBegin(IN OUT IMtStreamPtr& pSubStream) = 0;
	virtual HRESULT putSubStreamEnd(IN IMtStream* pSubStream) = 0;

	virtual HRESULT putStream(IMtStream*) = 0; // used to store sub-stream
	virtual HRESULT addStreamData(IMtStream*) = 0; // used to merge streams

		// call it before read anything
		// user version (not stream version)
	virtual HRESULT getVersion(OUT WORD& Major, OUT OPTIONAL WORD* pMinor=NULL, OUT OPTIONAL WORD* pRevision=NULL) = 0;
	virtual HRESULT getByte(OUT byte&) = 0;

	virtual HRESULT getBool(OUT BOOL& bV){
		bool bb = false;
		HRESULT hRes = getBool(bb);
		bV = bb ? TRUE : FALSE;
		return hRes;
	}

	virtual HRESULT getBool(OUT bool&) = 0;

	HRESULT getBoolArr(OUT mcsBoolArray& bArr) {
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

	HRESULT getByteArr(OUT mcsByteArray& btArr) {
		return getData(btArr);
	}

	virtual HRESULT getData(OUT mcsByteArray&) = 0; // automatically detects data block length

		// if bUseParentStreamBuffer == true, pSubStream will use a memory of this->stream,
		// (!) NOTE: The parent stream MUST BE alive while reading from 'pSubStream'
	virtual HRESULT getStream(OUT IMtStreamPtr& pSubStream, IN OPTIONAL bool bUseParentStreamBuffer = false) = 0;

	// system only: returns a reference to internally stored data, copy it as soon as possible
	virtual HRESULT _getData(OUT LPCVOID& pData, OUT DWORD& sz) = 0;

		// misc methods
	virtual McsStreamTagTypeEnum getCurrentTagType() = 0;

		// use this method once per complete version block of data;
		// then you can in older version of software safely read new blocks of data
	virtual HRESULT writeVersionBlockEnd() = 0; 
	virtual HRESULT readVersionBlockEnd(){
		return seek(0,MCSSTREAM_SEEK_VEREND);
	}; 

		// on this method stream resets internal helper data and further write is impossible
	virtual HRESULT writeComplete() = 0;

		// если в процессе записи возникли сбои, либо в памяти, либо в callback, то этот факт можно обнаружить этим вызовом
	virtual bool    hasWriteErrors() = 0;

		// 1) replaceIDs(); - generates new WID substitution for EVERY WID in stream
		// 3) replaceIDs(NULL,false); - nothing to do (do not use)
		// 4) replaceIDs(pCustom,false); - substitute all WIDs in stream for which substitution is defined in your custom map
		// 5) replaceIDs(pCustom,true); - substitute all WIDs in stream for which substitution is defined in your custom map,
		//                                if for any WID subst is not defined in custom map then new WID will be generated and used 
	virtual HRESULT replaceIDs(
		IN OUT OPTIONAL mcsWId2WIdMap*  pReplacementMap=NULL, 
		IN OPTIONAL bool                fAutoFillReplacementMap=true,
		IN OPTIONAL bool                fResetNonObjectIDs=false) = 0;

		// Обнуляет все ID, которых нет в множестве idsSetToLeave.
		// (Операция также выполняется во всех подстримах)
	virtual HRESULT resetSpecificIDs(IN const mcsWorkIDSet& idsSetToLeave) = 0;

		// prepares <this> and <pAddon> streams to transfer links inside one group of objects to another;
		// <this> stream will contain substituted links to target group with excluded external links; 
		// <pAddon> will contain target group's specific information with it's own external links
	virtual HRESULT transferInternalLinks(IN OUT IMtStream* pAddon,IN OUT mcsWId2WIdMap& Links) = 0;

		// if seekMode is MCSSTREAM_SEEK_TAG then iOffset is number of tags to move, bytes - otherwise
		// with MCSSTREAM_SEEK_TAG can move only in forward direction (iOffset>0)
	virtual HRESULT seek(int iOffset, DWORD seekMode) = 0; // on error position is not changed
	
	// 24.01.2011
	HRESULT seekStart()
		{return seek(0, MCSSTREAM_SEEK_BEGIN);}
	HRESULT seekEnd()
		{return seek(0, MCSSTREAM_SEEK_END);}
	HRESULT seekSkipTag()
		{return seek(1, MCSSTREAM_SEEK_TAG);}

	virtual DWORD   tell() = 0; // tells internal data pointer position in bytes (from beginning)
	virtual HRESULT reset(IN OPTIONAL DWORD dwTypeFalgs = kMSType_Default) = 0; // clears stream contents, position at the start
	virtual bool    isEmpty() = 0; // returns true if stream doesn't contains any data

		// advanced methods
	virtual HRESULT raiseVersionAlert() = 0; // after call you must read or write version
	virtual DWORD   getStreamDataSize(IN OPTIONAL bool fCompressed=false) = 0; // with stream header (used to store stream data)
	virtual LPCVOID getStreamRawData(IN OPTIONAL bool fCompressed=false) = 0; // with stream header (used to restore stream data)

		// if 'pSrcRawData' points to a buffer that was previously returned by getStreamInternalBuffer(),
		// a stream will just initialize itself using a data inside its own buffer
	virtual HRESULT setStreamRawData(LPCVOID pSrcRawData, DWORD dwSize) = 0;

		// Returns a pointer to an internally kept buffer
		// (!) Don't modify this buffer when a stream is initialized
		// (!) A NULL may be returned, for example, if a stream is initialized using an external buffer
	virtual HRESULT getStreamInternalBuffer(OUT mcsByteArray*& pBuffer) = 0;

	virtual HRESULT check() = 0; // check stream contents (using header and tag records)

		// transfer compatibility
	virtual HRESULT loadFromIStream(IN IStream*) = 0; // loads input std stream contents in our stream
	virtual HRESULT saveToIStream(OUT IStream*,IN OPTIONAL bool fCompressed=false) = 0; // makes copy of our data into std stream
	virtual HRESULT loadFromString(IN LPCTSTR csStringRawData) = 0; // loads stream from string data representation
	virtual HRESULT saveToString(OUT McsString& strRawData,IN OPTIONAL bool fCompressed=false) = 0; // stored stream's data in string format
	virtual HRESULT loadFromFile(IN LPCTSTR cstrFileName) = 0;
	virtual HRESULT saveToFile(IN LPCTSTR cstrFileName, IN OPTIONAL bool fCompressed = false) = 0;

		// if stream is platform dependent then allows to get/put platform specific data
	virtual HRESULT getPlatformData(OUT UINT_PTR& data) = 0; 
	virtual HRESULT putPlatformData(IN UINT_PTR data) = 0; 

		// caller defined tag which describes contents of the stream,
		// this tag can help to identify data in stream before read
	virtual HRESULT setContentTypeTag(IN DWORD tag) = 0;
	virtual HRESULT getContentTypeTag(OUT DWORD& tag) = 0;

		// these methods can determine stream data content type before stream will be initialized
	MT_API static HRESULT sGetStreamDataContentTypeTag(OUT DWORD& tag, IN LPCVOID pData, IN DWORD sz);
	MT_API static HRESULT sGetStreamFileContentTypeTag(OUT DWORD& tag, IN LPCTSTR cstrFileName);

		// returns list of unique IDs of stored objects in stream data, used in links transfer procedures
	virtual HRESULT getObjectIds(OUT mcsWorkIDArray& linkedObjects) = 0;

		// makes exact copy of data into <pStream>
	virtual HRESULT getCopy(OUT IMtStream* pStream) = 0;

		// changes internal data type, for System purposes only !
	virtual HRESULT _setDataType(IN DWORD dwTypeFalgs) = 0;

		// sets proc ptr which will be called for every string which will be read from stream
	virtual HRESULT setStringCorrectionProcA(mtstrCorrProcA pProcA) = 0;
	virtual HRESULT setStringCorrectionProcW(mtstrCorrProcW pProcW) = 0;

		// Получение флагов, характеризующих тип содержимого стрима.
	virtual DWORD dataTypeFlags() const = 0;

	bool isPlatformDependent () const {
		return 0 == (dataTypeFlags() & kMSType_PlatformIndependent);
	}

	bool isPlatformIndependent () const {
		return 0 != (dataTypeFlags() & kMSType_PlatformIndependent);
	}

	virtual HRESULT putWorkIdSet(const mcsWorkIDSet& set) {
		mcsWorkIDArray arr(set);
		return putWorkIDArr(arr);
	}

	virtual HRESULT getWorkIdSet(OUT mcsWorkIDSet& set) {
		mcsWorkIDArray arr;
		HRESULT hres = getWorkIDArr(arr);
		set = arr;
		return hres;
	}

	virtual HRESULT putWorkIdSet(const mcsWorkIDSetEx& set) {
		mcsWorkIDArray arr(set);
		return putWorkIDArr(arr);
	}

	virtual HRESULT getWorkIdSet(OUT mcsWorkIDSetEx& set) {
		mcsWorkIDArray arr;
		HRESULT hres = getWorkIDArr(arr);
		set = arr;
		return hres;
	}

	virtual McsStreamDwgFilerTypeEnum getDwgFilerType() = 0;
	virtual void setDwgFilerType(McsStreamDwgFilerTypeEnum value) = 0;

	// (!) Для системных целей
	virtual HRESULT _getListOfIds(OUT McsArray<mcsWorkID*, mcsWorkID*>& pWIDs) = 0;
};
//===========================================================================

extern "C" MT_API bool gfReadingNewInOld;
extern "C" MT_API bool gfStreamWriteErrors;

// Creates stream only with ability ti read/write basic types
MT_API HRESULT mcsCreateStream(OUT IMtStreamPtr&, DWORD dwTypeFalgs = kMSType_Default);

typedef HRESULT (__cdecl* ChangeCPProc)(IN OUT McsStringA& Buffer, IN UINT cpSource, IN OPTIONAL UINT cpTarget);
extern "C" MT_API ChangeCPProc gpChangeCP;

//typedef HRESULT (__cdecl* OnWriteIDProc)(IN const mcsWorkID&);
//extern "C" MT_API OnWriteIDProc gpOnWriteID;
//
//typedef HRESULT (__cdecl* OnReadIDProc)(IN OUT mcsWorkID&);
//extern "C" MT_API OnReadIDProc gpOnReadID;

typedef McsStringA (__cdecl* Unicode2AcadProc)(const McsStringW& st);
extern "C" MT_API Unicode2AcadProc gpUnicode2Acad;

typedef McsStringW (__cdecl* Acad2UnicodeProc)(const McsStringA& st);
extern "C" MT_API Acad2UnicodeProc gpAcad2Unicode;

//==============================================================================

typedef HRESULT (__cdecl* OnWriteSeIDProc)(IN const mcsWorkID& wid, OUT McSubentId& seid);
extern "C" MT_API OnWriteSeIDProc gpOnWriteSeID;

typedef HRESULT (__cdecl* OnReadSeIDProc)(IN OUT McSubentId& seid, IN OUT mcsWorkID& seWId);
extern "C" MT_API OnReadSeIDProc gpOnReadSeID;

typedef HRESULT (__cdecl* OnWriteIDsArrProc)(IN const mcsWorkIDArray& ids, OUT mcsIntArray& seIndices, OUT mcsWorkIDArray& filteredIDsList);
extern "C" MT_API OnWriteIDsArrProc gpOnWriteIDsArr;

//==============================================================================
