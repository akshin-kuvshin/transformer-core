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

#include <math.h>
#include "MCSTypes.h"
#include "McsMem.h"
#include "McsTempl.h"

#ifndef MCTYP_DLL
 #pragma comment(lib,"mctyp.lib")
#endif

class MCSUnknownData;
class MCSIntArray;
class MCSDoubleArray;
class MCSStringArray;

#define MCSUnknownData mcsByteArray
#define MCSIntArray    mcsIntArray
#define MCSDoubleArray mcsDoubleArray
#define MCSStringArray mcsStringArray
#include "McAPIs.h"

//=============================================================================
// helper string ptr wrapper
// added to minimize changes risk
struct MCTYP_API _MV_STRPTR
{
  McsString* pStr;

  _MV_STRPTR()
  {
    pStr=NULL;
  }

  ~_MV_STRPTR()
  {
    if(IsValidPtr(pStr))
      mcsMemDelete(pStr);
    pStr=(McsString*)(UINT_PTR)(UINT64)0xFEFEFEFEFEFEFEFE;
  }

  McsString& MSTR()
  {
    if(IsInvalidPtr(pStr)) 
      pStr = mcsMemNew(McsString);
    return *pStr;
  }

  const McsString& MSTR() const
  {
    if(IsInvalidPtr(pStr)) 
      *((McsString**)&pStr) = mcsMemNew(McsString);
    return *pStr;
  }
};
//=============================================================================

#pragma pack(push,1) // byte alignment

union __union_sz_MCSVariantCnt
{
	byte sz_workid[sizeof(mcsWorkID)];
	byte sz_intarr[sizeof(MCSIntArray)];
	byte sz_dblarr[sizeof(MCSDoubleArray)];
	byte sz_strarr[sizeof(MCSStringArray)];
	byte sz_unkdata[sizeof(MCSUnknownData)];
	byte sz_i64Arr[sizeof(mcsI64Array)];
	byte sz_workidArr[sizeof(mcsWorkIDArray)];
};
//=============================================================================

struct IMcsStream;

struct MCTYP_API MCSVariant
{
	// !!! Значения не изменять, потому что сохраняются в файл.
	enum Type
	{
		kUndefined	 = 0,  // пусто и не инициализировано.
		kInt         = 1,  // int32
		kDouble      = 3,  // double
		kBool        = 8,  // bool(1 байт)
		kString      = 9,  // string
		kIntArray    = 5,  // MCSIntArray
		kDoubleArray = 6,  // MCSDoubleArray
		kStringArray = 7,  // MCSStringArray
		kUnknown     = 11, // MCSUnknown
		kMCSWorkID   = 20, // mcsWorkID
		kMcsPoint    = 21, // mcsPoint, хранится как MCSDoubleArray
		kMcsVector   = 22, // mcsVector, хранится как MCSDoubleArray
		kInt64       = 23, // int64
		kInt64Array  = 24, // int64 array
		kWorkIDArray = 25, // mcsWorkIDArray
	};
	//....................................................................

protected:
#ifdef _MCEYE
public:
#endif
	Type        m_type;

	union 
	{
		int       m_iVal;     // kInt
		__int64   m_iVal64;   // kInt64
		double    m_rVal;     // kDouble
		char      m_chVal;    // kChar
		bool      m_bVal;     // kBool
		byte      m_arrdata[sizeof(__union_sz_MCSVariantCnt)]; // intArr dblArr strArr unkData mcsWorkID mcsWorkIDArray
	};

	_MV_STRPTR  m_StrFace; // used by GetAsString() and for kString value
	//....................................................................

public:
	MCSVariant();
	MCSVariant(const MCSVariant& rhs);
	MCSVariant(Type type);
	MCSVariant(int iVal);
	MCSVariant(__int64 iVal);
	MCSVariant(const MCSUID& uid);
	MCSVariant(DWORD iVal);
	MCSVariant(double rVal);
	MCSVariant(bool bVal);
	MCSVariant(LPCTSTR szVal);
	MCSVariant(const McsString& stVal);
	MCSVariant(const mcsPoint& pnt);
	MCSVariant(const mcsVector& vec);

	MCSVariant(const MCSIntArray& var);
	MCSVariant(const MCSDoubleArray& var);
	MCSVariant(const MCSStringArray& var);
	MCSVariant(const struct mcsWorkID& workId);
	MCSVariant(const mcsI64Array&);
	MCSVariant(const mcsWorkIDArray&);

	// Создается копия данных. data не освобождается и не изменяется.
	MCSVariant(const int* data, int length);
	MCSVariant(const double* data, int length);
	MCSVariant(const TCHAR* const* data, int length);
	MCSVariant(const MCSUnknownData& var);
	MCSVariant(const VARIANT& var);

	~MCSVariant();

	BOOL IsNull() const { return m_type == MCSVariant::kUndefined; }

	bool operator==(const MCSVariant& rhs) const;
	bool operator!=(const MCSVariant& rhs) const;

	MCSVariant& operator=(const MCSVariant& rhs);
	MCSVariant& operator=(int rhs);
	MCSVariant& operator=(__int64 rhs);
	MCSVariant& operator=(const MCSUID& uid);
	MCSVariant& operator=(DWORD rhs);
	MCSVariant& operator=(double rhs);
	MCSVariant& operator=(bool rhs);
	MCSVariant& operator=(LPCTSTR rhs);
	MCSVariant& operator=(const McsString& rhs);

	// AGL: need to trap UNICODE compilation errors
private:
#ifdef _UNICODE
	void operator=(LPCSTR)const{
	}
#else
	void operator=(LPCWSTR)const{
	}
#endif
public:

	MCSVariant& operator=(const mcsPoint& pnt);
	MCSVariant& operator=(const mcsVector& pnt);

	MCSVariant& operator=(const MCSUnknownData& arr);

	MCSVariant& operator=(const mcsWorkID& workId);
	MCSVariant& operator=(const VARIANT&);

	// Создается копия.
	MCSVariant& operator=(const MCSIntArray& arr);
	MCSVariant& operator=(const MCSDoubleArray& arr);
	MCSVariant& operator=(const MCSStringArray& arr);
	MCSVariant& operator=(const mcsI64Array&);
	MCSVariant& operator=(const mcsWorkIDArray&);
	
	// По возможности преобразовывает типы.
	// Чтобы узнать настоящий тип GetType().
	operator int() const;
	operator __int64() const;
	operator DWORD() const;
	operator double() const;
	operator bool() const;
	operator LPCTSTR() const;
	operator _variant_t() const;
	operator mcsPoint() const;
	operator mcsVector() const;
	operator MCSUID() const;

	operator const struct mcsWorkID() const;

	const MCSIntArray&    IntArray() const;
	const mcsI64Array&    Int64Array() const;
	const MCSDoubleArray& DoubleArray() const;
	const MCSStringArray& StringArray() const;
	const MCSUnknownData& UnknownData() const;
	const mcsWorkID&      WorkID() const;
	const mcsWorkIDArray& WorkIDArray() const;

	MCSIntArray&    IntArray();
	mcsI64Array&    Int64Array();
	MCSDoubleArray& DoubleArray();
	MCSStringArray& StringArray();
	MCSUnknownData& UnknownData();
	mcsWorkID&      WorkID();
	mcsWorkIDArray& WorkIDArray();

	Type GetType() const {return m_type;}
	void SetType(Type type);

	// Преобразовать к типу
	HRESULT ChangeType(Type type);

	void Clear();

	const McsString& GetAsString() const;
	BOOL SetFromString(LPCTSTR strVal);

	McsString getDbgString(LPCTSTR pfx = _T("")) const;

	// Пишет только данные
	BOOL MCSVariant::WriteBufferDataOnly(void*& buffer, int& iWritedSize) const;

	// following methods used to save data to/from the stream
	bool save(IMcsStream*) const;
	bool load(IMcsStream*);

	//..............................................................
protected:
#ifdef _MCEYE
public:
#endif
	// internal helpers
	MCSIntArray&    _intArr();
	mcsI64Array&    _int64Arr();
	MCSDoubleArray& _dblArr();
	MCSStringArray& _strArr();
	MCSUnknownData& _unkData();
	mcsWorkID&      _workID();
	mcsWorkIDArray& _workIDArray();

	const MCSIntArray&    _intArr() const;
	const mcsI64Array&    _int64Arr() const;
	const MCSDoubleArray& _dblArr() const;
	const MCSStringArray& _strArr() const;
	const MCSUnknownData& _unkData() const;
	const mcsWorkID&      _workID() const;
	const mcsWorkIDArray& _workIDArray() const;
};
#pragma pack(pop)
//=============================================================================

__inline MCSUID::MCSUID(const MCSVariant& var)
{
	dbl = (double)var;
}
//=============================================================================

__inline MCSUID& MCSUID::operator = (const MCSVariant& var)
{
	dbl = (double)var;
	return *this;
}
//=============================================================================

typedef MCSVariant::Type MCSVarType;

typedef McsArray <MCSVariant, const MCSVariant&> mcsVariantArray;
//=============================================================================

