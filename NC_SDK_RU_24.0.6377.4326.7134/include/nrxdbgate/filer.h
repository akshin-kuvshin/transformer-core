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

#ifndef __NANOTHUNK_FILER_H__
#define __NANOTHUNK_FILER_H__

#include <fstream>

#include "nrxdbgate_impexp.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDwgFiler
class OdDbDwgFiler;
class NRXDBGATE_EXPORT NcDbDwgFiler : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbDwgFiler);

	NcDbDwgFiler();
	NcDbDwgFiler(OdRxObject* _object);
	virtual ~NcDbDwgFiler();

public:
	typedef NcDbDwgFiler  wrapper_class;
	typedef OdDbDwgFiler  native_class;

public:

	virtual NcDb::FilerType    filerType() const;
	virtual Nano::ErrorStatus  filerStatus() const;
	virtual void               setFilerStatus(Nano::ErrorStatus es);
	virtual void               resetFilerStatus();

	// version of the drawing file being read or written by this filer
	virtual  Nano::ErrorStatus  dwgVersion(NcDb::NcDbDwgVersion& ver, 
		NcDb::MaintenanceReleaseVersion& maintVer) const;

#pragma region readXxx_and_writeXxx_functions
	virtual Nano::ErrorStatus readHardOwnershipId(NcDbHardOwnershipId* id);
	virtual Nano::ErrorStatus writeHardOwnershipId(const NcDbHardOwnershipId& id);

	virtual Nano::ErrorStatus readSoftOwnershipId(NcDbSoftOwnershipId* id);
	virtual Nano::ErrorStatus writeSoftOwnershipId(const NcDbSoftOwnershipId& id);

	virtual Nano::ErrorStatus readHardPointerId(NcDbHardPointerId* id);
	virtual Nano::ErrorStatus writeHardPointerId(const NcDbHardPointerId& id);

	virtual Nano::ErrorStatus readSoftPointerId(NcDbSoftPointerId* id);
	virtual Nano::ErrorStatus writeSoftPointerId(const NcDbSoftPointerId& id);

	virtual Nano::ErrorStatus readInt8(NRX::Int8* value);
	virtual Nano::ErrorStatus writeInt8(NRX::Int8 value);

	__declspec(deprecated("Method readChar(NRX::Int8*) is deprecated. Use readInt8(NRX::Int8*)"))
	inline  Nano::ErrorStatus readChar(NRX::Int8 *p)
	{
		return this->readInt8(p);
	}
	__declspec(deprecated("Method writeChar(NRX::Int8) is deprecated. Use writeInt8(NRX::Int8)"))
	inline  Nano::ErrorStatus writeChar(NRX::Int8 c)
	{
		return this->writeInt8(c);
	}

	virtual Nano::ErrorStatus readString(NCHAR **);
	virtual Nano::ErrorStatus writeString(const NCHAR *);

	virtual Nano::ErrorStatus readString(NcString &);
	virtual Nano::ErrorStatus writeString(const NcString &);

	virtual Nano::ErrorStatus readBChunk(nds_binary*);
	virtual Nano::ErrorStatus writeBChunk(const nds_binary&);

	virtual Nano::ErrorStatus readNcDbHandle(NcDbHandle* handle);
	virtual Nano::ErrorStatus writeNcDbHandle(const NcDbHandle& handle);

	virtual Nano::ErrorStatus readInt64(NRX::Int64* value);
	virtual Nano::ErrorStatus writeInt64(NRX::Int64 value);

	virtual Nano::ErrorStatus readInt32(NRX::Int32* value);
	virtual Nano::ErrorStatus writeInt32(NRX::Int32 value);

	virtual Nano::ErrorStatus readInt16(NRX::Int16* value);
	virtual Nano::ErrorStatus writeInt16(NRX::Int16 value);

	virtual Nano::ErrorStatus readUInt64(NRX::UInt64* value);
	virtual Nano::ErrorStatus writeUInt64(NRX::UInt64 value);

	virtual Nano::ErrorStatus readUInt32(NRX::UInt32* value);
	virtual Nano::ErrorStatus writeUInt32(NRX::UInt32 value);

	virtual Nano::ErrorStatus readUInt16(NRX::UInt16* value);
	virtual Nano::ErrorStatus writeUInt16(NRX::UInt16 value);

	virtual Nano::ErrorStatus readUInt8(NRX::UInt8* value);
	virtual Nano::ErrorStatus writeUInt8(NRX::UInt8 value);

	virtual Nano::ErrorStatus readBoolean(NRX::Boolean* value);
	virtual Nano::ErrorStatus writeBoolean(NRX::Boolean value);

	virtual Nano::ErrorStatus readBool(bool* value);
	virtual Nano::ErrorStatus writeBool(bool value);

	virtual Nano::ErrorStatus readDouble(double* value);
	virtual Nano::ErrorStatus writeDouble(double value);

	virtual Nano::ErrorStatus readPoint2d(NcGePoint2d* point);
	virtual Nano::ErrorStatus writePoint2d(const NcGePoint2d& point);

	virtual Nano::ErrorStatus readPoint3d(NcGePoint3d* point);
	virtual Nano::ErrorStatus writePoint3d(const NcGePoint3d& point);

	virtual Nano::ErrorStatus readVector2d(NcGeVector2d* vector);
	virtual Nano::ErrorStatus writeVector2d(const NcGeVector2d& vector);

	virtual Nano::ErrorStatus readVector3d(NcGeVector3d* vector);
	virtual Nano::ErrorStatus writeVector3d(const NcGeVector3d& vector);

	virtual Nano::ErrorStatus readScale3d(NcGeScale3d* scale);
	virtual Nano::ErrorStatus writeScale3d(const NcGeScale3d& scale);

	virtual Nano::ErrorStatus readBytes(void* buffer, NRX::UIntPtr size);
	virtual Nano::ErrorStatus writeBytes(const void* buffer, NRX::UIntPtr size);

	virtual Nano::ErrorStatus readAddress(void** address);
	virtual Nano::ErrorStatus writeAddress(const void* address);

#pragma endregion

#pragma region readItem_and_writeItem_functions
	
	Nano::ErrorStatus   readItem(NcDbHardOwnershipId* pId);
	Nano::ErrorStatus   writeItem(const NcDbHardOwnershipId& id);

	Nano::ErrorStatus   readItem(NcDbSoftOwnershipId* pId);
	Nano::ErrorStatus   writeItem(const NcDbSoftOwnershipId& id);

	Nano::ErrorStatus   readItem(NcDbHardPointerId* pId);
	Nano::ErrorStatus   writeItem(const NcDbHardPointerId& id);

	Nano::ErrorStatus   readItem(NcDbSoftPointerId* pId);
	Nano::ErrorStatus   writeItem(const NcDbSoftPointerId& id);

	Nano::ErrorStatus   readItem(NCHAR** pVal);
	Nano::ErrorStatus   writeItem(const NCHAR* val);
#ifndef _MSC_VER
	Nano::ErrorStatus   writeItem(const NcString& val);
	Nano::ErrorStatus   writeItem(const CString& val);
#endif
	Nano::ErrorStatus   readItem(nds_binary* pVal);
	Nano::ErrorStatus   writeItem(const nds_binary& val);

	Nano::ErrorStatus   readItem(NcDbHandle* pVal);
	Nano::ErrorStatus   writeItem(const NcDbHandle& val);

	Nano::ErrorStatus   readItem(NRX::Int32* pVal);
	Nano::ErrorStatus   writeItem(NRX::Int32 val);

	Nano::ErrorStatus   readItem(NRX::Int16* pVal);
	Nano::ErrorStatus   writeItem(NRX::Int16 val);

	Nano::ErrorStatus   readItem(NRX::Int8* pVal);
	Nano::ErrorStatus   writeItem(NRX::Int8 val);

	Nano::ErrorStatus   readItem(NRX::UInt32* pVal);
	Nano::ErrorStatus   writeItem(NRX::UInt32 val);

	Nano::ErrorStatus   readItem(NRX::UInt16* pVal);
	Nano::ErrorStatus   writeItem(NRX::UInt16 val);

	Nano::ErrorStatus   readItem(NRX::UInt8* pVal);
	Nano::ErrorStatus   writeItem(NRX::UInt8 val);

	Nano::ErrorStatus   readItem(NRX::Boolean* pVal);
	Nano::ErrorStatus   writeItem(NRX::Boolean val);

#if !defined(Nano_Boolean_is_bool) 
	// Only when Nano_Boolean_is_bool is not defined 
	// since it covered already in the NRX::Boolean overload.
	Nano::ErrorStatus   readItem(bool* pVal);
	Nano::ErrorStatus   writeItem(bool val);
#endif

	Nano::ErrorStatus   readItem(double* pVal);
	Nano::ErrorStatus   writeItem(double val);

	Nano::ErrorStatus   readItem(NcGePoint2d* pVal);
	Nano::ErrorStatus   writeItem(const NcGePoint2d& val);

	Nano::ErrorStatus   readItem(NcGePoint3d* pVal);
	Nano::ErrorStatus   writeItem(const NcGePoint3d& val);

	Nano::ErrorStatus   readItem(NcGeVector2d* pVal);
	Nano::ErrorStatus   writeItem(const NcGeVector2d& val);

	Nano::ErrorStatus   readItem(NcGeVector3d* pVal);
	Nano::ErrorStatus   writeItem(const NcGeVector3d& val);

	Nano::ErrorStatus   readItem(NcGeScale3d* pVal);
	Nano::ErrorStatus   writeItem(const NcGeScale3d& val);

	Nano::ErrorStatus   readItem(void* pDest, NRX::UIntPtr nBytes);
	Nano::ErrorStatus   writeItem(const void* pSrc, NRX::UIntPtr nBytes);

	Nano::ErrorStatus   readItem(void** pp);
	Nano::ErrorStatus   writeItem(const void* p);

	Nano::ErrorStatus   readItem(void* buffer, NRX::UInt32 size);
	Nano::ErrorStatus   writeItem(const void* buffer, NRX::UInt32 size);

#pragma endregion

	virtual Nano::ErrorStatus  seek(NRX::Int64 nOffset, int nMethod);
	virtual NRX::Int64         tell() const;

	// virtual Nano::ErrorStatus   addReferences(NcDbIdRefQueue& /*qToAbsorb*/);   // for internal use only

	virtual bool               usesReferences() const;
	virtual NcDbAuditInfo *    getAuditInfo() const;

	// virtual NcDbFilerController& controller() const;                            // for internal use only

public:
	OdDbDwgFiler* native() const;

protected:
	virtual bool isThunk() const;

protected:
	Nano::ErrorStatus m_filerStatus;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Классы реализации файлеров
class __OdDbDeepCloneFilerImpl;
class __OdDbWblockCloneFilerImpl;

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDeepCloneFiler
class NRXDBGATE_EXPORT NcDbDeepCloneFiler : public NcDbDwgFiler
{
public:
	NCRX_DECLARE_MEMBERS(NcDbDeepCloneFiler);

	NcDbDeepCloneFiler();
	NcDbDeepCloneFiler(OdRxObject* _object);
	virtual ~NcDbDeepCloneFiler();

public:
	typedef NcDbDeepCloneFiler  wrapper_class;
	typedef __OdDbDeepCloneFilerImpl  native_class;

public:
	virtual NcDb::FilerType    filerType() const override;
	virtual Nano::ErrorStatus  seek(NRX::Int64 nOffset, int nMethod) override;
	virtual NRX::Int64         tell() const override;

#pragma region readXxx_and_writeXxx_functions
	virtual Nano::ErrorStatus readHardOwnershipId(NcDbHardOwnershipId* id) override;
	virtual Nano::ErrorStatus writeHardOwnershipId(const NcDbHardOwnershipId& id) override;

	virtual Nano::ErrorStatus readSoftOwnershipId(NcDbSoftOwnershipId* id) override;
	virtual Nano::ErrorStatus writeSoftOwnershipId(const NcDbSoftOwnershipId& id) override;

	virtual Nano::ErrorStatus readHardPointerId(NcDbHardPointerId* id) override;
	virtual Nano::ErrorStatus writeHardPointerId(const NcDbHardPointerId& id) override;

	virtual Nano::ErrorStatus readSoftPointerId(NcDbSoftPointerId* id) override;
	virtual Nano::ErrorStatus writeSoftPointerId(const NcDbSoftPointerId& id) override;

	virtual Nano::ErrorStatus readInt8(NRX::Int8* value) override;
	virtual Nano::ErrorStatus writeInt8(NRX::Int8 value) override;

	__declspec(deprecated("Method readChar(NRX::Int8*) is deprecated. Use readInt8(NRX::Int8*)"))
		inline  Nano::ErrorStatus readChar(NRX::Int8* p)
	{
		return this->readInt8(p);
	}
	__declspec(deprecated("Method writeChar(NRX::Int8) is deprecated. Use writeInt8(NRX::Int8)"))
		inline  Nano::ErrorStatus writeChar(NRX::Int8 c)
	{
		return this->writeInt8(c);
	}

	virtual Nano::ErrorStatus readString(NCHAR**) override;
	virtual Nano::ErrorStatus writeString(const NCHAR*) override;

	virtual Nano::ErrorStatus readString(NcString&) override;
	virtual Nano::ErrorStatus writeString(const NcString&) override;

	virtual Nano::ErrorStatus readBChunk(nds_binary*) override;
	virtual Nano::ErrorStatus writeBChunk(const nds_binary&) override;

	virtual Nano::ErrorStatus readNcDbHandle(NcDbHandle* handle) override;
	virtual Nano::ErrorStatus writeNcDbHandle(const NcDbHandle& handle) override;

	virtual Nano::ErrorStatus readInt64(NRX::Int64* value) override;
	virtual Nano::ErrorStatus writeInt64(NRX::Int64 value) override;

	virtual Nano::ErrorStatus readInt32(NRX::Int32* value) override;
	virtual Nano::ErrorStatus writeInt32(NRX::Int32 value) override;

	virtual Nano::ErrorStatus readInt16(NRX::Int16* value) override;
	virtual Nano::ErrorStatus writeInt16(NRX::Int16 value) override;

	virtual Nano::ErrorStatus readUInt64(NRX::UInt64* value) override;
	virtual Nano::ErrorStatus writeUInt64(NRX::UInt64 value) override;

	virtual Nano::ErrorStatus readUInt32(NRX::UInt32* value) override;
	virtual Nano::ErrorStatus writeUInt32(NRX::UInt32 value) override;

	virtual Nano::ErrorStatus readUInt16(NRX::UInt16* value) override;
	virtual Nano::ErrorStatus writeUInt16(NRX::UInt16 value) override;

	virtual Nano::ErrorStatus readUInt8(NRX::UInt8* value) override;
	virtual Nano::ErrorStatus writeUInt8(NRX::UInt8 value) override;

	virtual Nano::ErrorStatus readBoolean(NRX::Boolean* value) override;
	virtual Nano::ErrorStatus writeBoolean(NRX::Boolean value) override;

	virtual Nano::ErrorStatus readBool(bool* value) override;
	virtual Nano::ErrorStatus writeBool(bool value) override;

	virtual Nano::ErrorStatus readDouble(double* value) override;
	virtual Nano::ErrorStatus writeDouble(double value) override;

	virtual Nano::ErrorStatus readPoint2d(NcGePoint2d* point) override;
	virtual Nano::ErrorStatus writePoint2d(const NcGePoint2d& point) override;

	virtual Nano::ErrorStatus readPoint3d(NcGePoint3d* point) override;
	virtual Nano::ErrorStatus writePoint3d(const NcGePoint3d& point) override;

	virtual Nano::ErrorStatus readVector2d(NcGeVector2d* vector) override;
	virtual Nano::ErrorStatus writeVector2d(const NcGeVector2d& vector) override;

	virtual Nano::ErrorStatus readVector3d(NcGeVector3d* vector) override;
	virtual Nano::ErrorStatus writeVector3d(const NcGeVector3d& vector) override;

	virtual Nano::ErrorStatus readScale3d(NcGeScale3d* scale) override;
	virtual Nano::ErrorStatus writeScale3d(const NcGeScale3d& scale) override;

	virtual Nano::ErrorStatus readBytes(void* buffer, NRX::UIntPtr size) override;
	virtual Nano::ErrorStatus writeBytes(const void* buffer, NRX::UIntPtr size) override;

	virtual Nano::ErrorStatus readAddress(void** address) override;
	virtual Nano::ErrorStatus writeAddress(const void* address) override;

#pragma endregion

	// Protocol specific to NcDbDeepCloneFiler

	virtual bool               getNextOwnedObject(NcDbObjectId& id);
	virtual bool               moreOwnedObjects() const;

public:
	__OdDbDeepCloneFilerImpl* native() const;

protected:
	virtual bool isThunk() const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbWblockCloneFiler
class NRXDBGATE_EXPORT NcDbWblockCloneFiler : public NcDbDeepCloneFiler
{
public:
	NCRX_DECLARE_MEMBERS(NcDbWblockCloneFiler);

	NcDbWblockCloneFiler();
	NcDbWblockCloneFiler(OdRxObject* _object);
	virtual ~NcDbWblockCloneFiler();

public:
	typedef NcDbWblockCloneFiler  wrapper_class;
	typedef __OdDbWblockCloneFilerImpl  native_class;

public:
	virtual NcDb::FilerType    filerType() const override;
	virtual Nano::ErrorStatus  writeHardOwnershipId(const NcDbHardOwnershipId& id) override;
	virtual Nano::ErrorStatus  writeHardPointerId(const NcDbHardPointerId& id) override;
	virtual Nano::ErrorStatus  writeSoftOwnershipId(const NcDbSoftOwnershipId& id) override;
	virtual bool               getNextOwnedObject(NcDbObjectId& id) override;

	// Protocol specific to NcDbWblockCloneFiler

	virtual bool                  getNextHardObject(NcDbObjectId& id);
	virtual bool                  moreHardObjects() const;

public:
	__OdDbWblockCloneFilerImpl* native() const;

protected:
	virtual bool isThunk() const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDxfFiler
class OdDbDxfFiler;
class NRXDBGATE_EXPORT NcDbDxfFiler : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbDxfFiler);

	NcDbDxfFiler();
	NcDbDxfFiler(OdRxObject* _object);

public:
	typedef OdDbDxfFiler  native_class;

public:
	virtual int rewindFiler();

	virtual Nano::ErrorStatus filerStatus() const;
	virtual void resetFilerStatus();

	virtual Nano::ErrorStatus setError(Nano::ErrorStatus, const NCHAR*, ...);
	virtual Nano::ErrorStatus setError(const NCHAR*, ...);
	virtual const NCHAR* errorMessage() const;

	virtual NcDb::FilerType filerType() const;

	virtual NcDbDatabase* database() const;

	virtual Nano::ErrorStatus dwgVersion(NcDb::NcDbDwgVersion&, NcDb::MaintenanceReleaseVersion&) const;

	virtual int precision() const;
	virtual void setPrecision(int precision);

	// Number of decimal digits printed in ASCII DXF file
	enum { kDfltPrec = -1, kMaxPrec = 16 };

	// readXxx and writeXxx functions
	virtual Nano::ErrorStatus readResBuf(resbuf*);

	virtual Nano::ErrorStatus writeResBuf(const resbuf&);
	virtual Nano::ErrorStatus writeObjectId(NcDb::DxfCode code, const NcDbObjectId& id);
	virtual Nano::ErrorStatus writeInt8(NcDb::DxfCode code, NRX::Int8 value);
	virtual Nano::ErrorStatus writeString(NcDb::DxfCode code, const NCHAR* string);
	virtual Nano::ErrorStatus writeBChunk(NcDb::DxfCode code, const nds_binary& chunk);
	virtual Nano::ErrorStatus writeNcDbHandle(NcDb::DxfCode code, const NcDbHandle& handle);
	virtual Nano::ErrorStatus writeInt32(NcDb::DxfCode code, NRX::Int32 value);
	virtual Nano::ErrorStatus writeInt16(NcDb::DxfCode code, NRX::Int16 value);
	virtual Nano::ErrorStatus writeUInt32(NcDb::DxfCode code, NRX::UInt32 value);
	virtual Nano::ErrorStatus writeUInt16(NcDb::DxfCode code, NRX::UInt16 value);
	virtual Nano::ErrorStatus writeUInt8(NcDb::DxfCode code, NRX::UInt8 value);
	virtual Nano::ErrorStatus writeBoolean(NcDb::DxfCode code, NRX::Boolean value);
	virtual Nano::ErrorStatus writeInt(NcDb::DxfCode, int);

	virtual Nano::ErrorStatus writeBool(NcDb::DxfCode, bool value);
	virtual Nano::ErrorStatus writeDouble(NcDb::DxfCode, double value, int precision = kDfltPrec);
	virtual Nano::ErrorStatus writePoint2d(NcDb::DxfCode, const NcGePoint2d& point, int precision = kDfltPrec);
	virtual Nano::ErrorStatus writePoint3d(NcDb::DxfCode, const NcGePoint3d& point, int precision = kDfltPrec);
	virtual Nano::ErrorStatus writeVector2d(NcDb::DxfCode, const NcGeVector2d& vector, int precision = kDfltPrec);
	virtual Nano::ErrorStatus writeVector3d(NcDb::DxfCode, const NcGeVector3d& vector, int precision = kDfltPrec);
	virtual Nano::ErrorStatus writeScale3d(NcDb::DxfCode, const NcGeScale3d& scale, int precision = kDfltPrec);

	virtual Nano::ErrorStatus writeInt64 (NcDb::DxfCode, NRX::Int64); // = 0;
	virtual Nano::ErrorStatus writeUInt64 (NcDb::DxfCode, NRX::UInt64); // = 0;

	Nano::ErrorStatus readItem(resbuf* rb);

	Nano::ErrorStatus writeItem(const resbuf& rb);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, const NcDbObjectId& id);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, const NCHAR* string);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, const nds_binary& binary);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, const NcDbHandle& handle);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, NRX::Int32 value);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, NRX::Int16 value);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, NRX::Int8 value);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, NRX::UInt32 value);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, NRX::UInt16 value);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, NRX::UInt8 value);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, int value);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, bool value);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, double value, int precision = kDfltPrec);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, const NcGePoint2d& point, int precision = kDfltPrec);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, const NcGePoint3d& point, int precision = kDfltPrec);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, const NcGeVector2d& vector, int precision = kDfltPrec);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, const NcGeVector3d& vector, int precision = kDfltPrec);
	Nano::ErrorStatus writeItem(NcDb::DxfCode code, const NcGeScale3d& scale, int precision = kDfltPrec);
	Nano::ErrorStatus writeChar (NcDb::DxfCode c, NRX::Int8 n);
	virtual Nano::ErrorStatus writeXDataStart();
	virtual bool includesDefaultValues() const;

	virtual Nano::ErrorStatus pushBackItem();
	virtual bool atEOF();
	virtual bool atSubclassData(const NCHAR* data);
	virtual bool atExtendedData();
	virtual bool atEndOfObject();
	virtual void haltAtClassBoundries(bool flag);

	virtual Nano::ErrorStatus writeEmbeddedObjectStart();
	virtual bool atEmbeddedObjectStart();

	virtual double elevation() const;
	virtual double thickness() const;

	virtual bool isModifyingExistingObject() const;

public:
	OdDbDxfFiler* native() const;
};

class NRXDBGATE_EXPORT NcGeDwgIO
{
public:
	// Write out to file
	//
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePoint2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeVector2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeMatrix2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeScale2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePoint2dArray&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeVector2dArray&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePoint3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeVector3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeMatrix3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeScale3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePoint3dArray&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeVector3dArray&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeTol&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeInterval&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeKnotVector&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeDoubleArray&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeIntArray&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCurveBoundary&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePosition2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePointOnCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeLine2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeLineSeg2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeRay2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCircArc2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeEllipArc2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeExternalCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCubicSplineCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeNurbCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCompositeCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeOffsetCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePolyline2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePosition3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePointOnCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePointOnSurface&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeLine3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeRay3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeLineSeg3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePlane&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeBoundedPlane&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCircArc3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeEllipArc3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCubicSplineCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeNurbCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCompositeCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeOffsetCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGePolyline3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeAugPolyline3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeExternalCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCone&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCylinder&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeTorus&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeExternalSurface&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeOffsetSurface&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeNurbSurface&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*,const NcGeExternalBoundedSurface&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeSphere&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeBoundBlock2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeBoundBlock3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCurveCurveInt2d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeCurveCurveInt3d&);
	static Nano::ErrorStatus outFields(NcDbDwgFiler*, const NcGeEllipCone&);

	// Read in from file
	//
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePoint2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeVector2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeMatrix2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeScale2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePoint2dArray&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeVector2dArray&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePoint3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeVector3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeMatrix3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeScale3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePoint3dArray&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeVector3dArray&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeTol&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeInterval&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeKnotVector&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeDoubleArray&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeIntArray&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCurveBoundary&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePosition2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePointOnCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeLine2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeLineSeg2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeRay2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCircArc2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeEllipArc2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeExternalCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCubicSplineCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeNurbCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCompositeCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeOffsetCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePolyline2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePosition3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePointOnCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePointOnSurface&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeLine3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeRay3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeLineSeg3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePlane&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeBoundedPlane&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCircArc3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeEllipArc3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCubicSplineCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCompositeCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeOffsetCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeNurbCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGePolyline3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeAugPolyline3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeExternalCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCone&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCylinder&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeTorus&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeExternalSurface&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeOffsetSurface&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeNurbSurface&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeExternalBoundedSurface&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeSphere&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeBoundBlock2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeBoundBlock3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCurveCurveInt2d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeCurveCurveInt3d&);
	static Nano::ErrorStatus inFields(NcDbDwgFiler*, NcGeEllipCone&);
};

class NRXDBGATE_EXPORT NcGeDxfIO
{
public:

	static Nano::ErrorStatus inFields(NcDbDxfFiler* filer, NcGeDoubleArray& arr);
	static Nano::ErrorStatus outFields(NcDbDxfFiler* filer, NcGeDoubleArray& arr);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeAugPolyline3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeBoundBlock2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeBoundBlock3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeBoundedPlane&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCircArc2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCircArc3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCompositeCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCompositeCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCone&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCubicSplineCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCubicSplineCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCurveBoundary&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCurveCurveInt2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCurveCurveInt3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeCylinder&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeEllipArc2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeEllipArc3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeEllipCone&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeExternalBoundedSurface&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeExternalCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeExternalCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeExternalSurface&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeIntArray&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeInterval&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeKnotVector&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeLine2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeLine3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeLineSeg2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeLineSeg3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeMatrix2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeMatrix3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeNurbCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeNurbCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeNurbSurface&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeOffsetCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeOffsetCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeOffsetSurface&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePlane&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePoint2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePoint2dArray&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePoint3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePoint3dArray&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePointOnCurve2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePointOnCurve3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePointOnSurface&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePolyline2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePolyline3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePosition2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGePosition3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeRay2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeRay3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeScale2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeScale3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeSphere&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeTol&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeTorus&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeVector2d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeVector2dArray&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeVector3d&);
	static Nano::ErrorStatus inFields(NcDbDxfFiler*, NcGeVector3dArray&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeAugPolyline3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeBoundBlock2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeBoundBlock3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeBoundedPlane&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCircArc2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCircArc3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCompositeCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCompositeCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCone&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCubicSplineCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCubicSplineCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCurveBoundary&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCurveCurveInt2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCurveCurveInt3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeCylinder&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeDoubleArray&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeEllipArc2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeEllipArc3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeEllipCone&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*,const NcGeExternalBoundedSurface&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeExternalCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeExternalCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeExternalSurface&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeIntArray&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeInterval&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeKnotVector&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeLine2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeLine3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeLineSeg2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeLineSeg3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeMatrix2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeMatrix3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeNurbCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeNurbCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeNurbSurface&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeOffsetCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeOffsetCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeOffsetSurface&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePlane&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePoint2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePoint2dArray&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePoint3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePoint3dArray&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePointOnCurve2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePointOnCurve3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePointOnSurface&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePolyline2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePolyline3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePosition2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGePosition3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeRay2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeRay3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeScale2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeScale3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeSphere&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeTol&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeTorus&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeVector2d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeVector2dArray&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeVector3d&);
	static Nano::ErrorStatus outFields(NcDbDxfFiler*, const NcGeVector3dArray&);
};


//////////////////////////////////////////////////////////////////////////
// INcReadStream
class __declspec(novtable) INcReadStream {
public:
	enum {
		    eOk = 0,
		    eNotSupported = 1,
		    eNotOpen = 2,
		    eInvalidArg = 3,
		    eEndOfFile = 4,
		    eDiskFull = 5,
		    eDisconnected = 6,
		    eJustAnError = 7
	};
	enum {
		    eFromStart = 0,
		    eFromCurrent = 1,
		    eFromEnd = 2
	};
	virtual int  seek(__int64 nDistance, int nMode) { return eNotSupported; }
	virtual __int64 tell() { return -1; }
	virtual int read(void* pDestBuf, size_t nNumBytes,
	                 size_t *pNumRead) = 0;
	virtual int  close() { return eNotSupported; }
	virtual __int64 control(__int64 nArg) { return 0; }
protected:
	virtual ~INcReadStream() {}
};

//////////////////////////////////////////////////////////////////////////
// INcWriteStream
class __declspec(novtable) INcWriteStream : public INcReadStream {
public:
	virtual int write(const void* pSrcBuf, size_t nNumBytes,
	                  size_t *pNumWritten) = 0;
	virtual int flushBuffers() { return eNotSupported; }
	virtual int setEndOfFile() { return eNotSupported; }
protected:
	virtual ~INcWriteStream() {}
};

////////////////////////////////////////////////////////////////////////
// NCFile

#ifdef ASSERT
	#define NdCharFmt_Assert ASSERT
#elif defined assert
	#define NdCharFmt_Assert assert
#elif defined _ASSERTE
	#define NdCharFmt_Assert _ASSERTE
#else
	#define NdCharFmt_Assert(x)
#endif

#ifdef ASSERT
	#define NcFILE_Assert ASSERT
#elif defined assert
	#define NcFILE_Assert assert
#elif defined _ASSERTE
	#define NcFILE_Assert _ASSERTE
#else
	#define NcFILE_Assert(T)
#endif

// AutoGen:

//////////////////////////////////////////////////////////////////////////
// NdCharFormatter
class NdCharFormatter {
public:
	enum {
		kUnknown = 0,
		kAnsi,
		kUtf8,
		kUtf16LE,
		kUtf16BE,
		kUtf32LE,
		kUtf32BE
	};
	enum {
#if defined(WINVER) && (WINVER >= 0x0500)
		kNoBestFitFlag = WC_NO_BEST_FIT_CHARS,
#else
		kNoBestFitFlag = 0x0400,
#endif
		kCIFLen = 7,
		kMIFLen = 8
	};
	NdCharFormatter(unsigned nFormat, bool bUseCIF, bool bExpandLF) :
	            mnFormat(nFormat), mbUseCIF(bUseCIF),
	            mbExpandLF(bExpandLF)
	{
		NdCharFmt_Assert(this->mbUseCIF == false || this->mnFormat == kAnsi);
	}
	NdCharFormatter() : mnFormat(kAnsi), mbUseCIF(false),
	                    mbExpandLF(true) {}
	unsigned static lookupBOM(unsigned nBom)
	{
		if ((nBom & 0x00ffffff) == 0xbfbbef)
			return kUtf8;
		if ((nBom & 0x0000ffff) == 0xfeff)
			return kUtf16LE;
		if ((nBom & 0x0000ffff) == 0xfffe)
			return kUtf16BE;
		if (nBom == 0x0000feff)
			return kUtf32LE;
		if (nBom == 0xfffe0000)
			return kUtf32BE;
		return kUnknown;
	}
	int static getBOM(unsigned &nBom, unsigned nFmt)
	{
		if (nFmt == kUtf8) {
			nBom = 0xbfbbef;
			return 3;
		}
		else if (nFmt == kUtf16LE) {
			nBom = 0xfeff;
			return 2;
		}
		else if (nFmt == kUtf16BE) {
			nBom = 0xfffe;
			return 2;
		}
		else if (nFmt == kUtf32LE) {
			nBom = 0x0000feff;
			return 4;
		}
		else if (nFmt == kUtf32BE) {
			nBom = 0xfffe0000;
			return 4;
		}
		else {
			NdCharFmt_Assert(nFmt == kUnknown || nFmt == kAnsi);
			return 0;
		}
	}
	template <class ChType> static void putCIF(wchar_t wch, ChType *pDest)
	{
		pDest[0] = '\\';
		pDest[1] = 'U';
		pDest[2] = '+';
		for (int i = 0; i < 4; i++) {
			const ChType n = (ChType)(wch & 0xf);
			pDest[6 - i] = (n <= 9) ? ('0' + n) : ('A' - 10 + n);
			wch >>= 4;
		}
	}
	bool getUseCIF() const { return this->mbUseCIF; }
	bool getExpandLF() const { return this->mbExpandLF; }
	unsigned getFormat() const { return this->mnFormat; }
	bool setUseCIF(bool bUseCIF) {
		const bool bOldUseCIF = this->mbUseCIF;
		this->mbUseCIF = bUseCIF;
		return bOldUseCIF;
	}
	bool setExpandLF(bool bExpandLF) {
		const bool bOldExpandLF = this->mbExpandLF;
		this->mbExpandLF = bExpandLF;
		return bOldExpandLF;
	}
	unsigned setFormat(unsigned nFormat) {
		const unsigned nOldFormat = this->mnFormat;
		this->mnFormat = nFormat;
		return nOldFormat;
	}
	static unsigned wcsLength(const wchar_t * pStr)
	{
		unsigned nLen = 0;
		while (*pStr != L'\0') {
			nLen++;
			pStr++;
		}
		return nLen;
	}
	static unsigned wcharToAnsiOrUtf8(wchar_t wch, char *pDestBuf,
	                                  unsigned nDestBufSize,
	                                  bool bToAnsi,
	                                  bool bUseCIF, bool bExpandLF)
	{
		NdCharFmt_Assert(bToAnsi || !bUseCIF);
		NdCharFmt_Assert(nDestBufSize >= 2);
		if (nDestBufSize < 2)
			return 0;
		NdCharFmt_Assert(!bUseCIF || nDestBufSize >= 7);
		NdCharFmt_Assert(bToAnsi || nDestBufSize >= 4);
		if (wch >= 0 && wch <= 0x7f) {
			if (wch == L'\n' && bExpandLF) {
				pDestBuf[0] = '\r';
				pDestBuf[1] = '\n';
				return 2;
			}
			pDestBuf[0] = (char)wch;
			NdCharFmt_Assert(pDestBuf[0] == wch);
			return 1;
		}
		BOOL bUsedDefaultChar = false;
		const unsigned nCvted = ::WideCharToMultiByte(
		            bToAnsi ?  CP_ACP : CP_UTF8,
		            (bToAnsi && bUseCIF) ?  kNoBestFitFlag : 0,
		            &wch,
		            1,
		            pDestBuf,
		            bToAnsi ?  2 : 4,
		            NULL,
		            bToAnsi ?  &bUsedDefaultChar : NULL);
		NdCharFmt_Assert(nCvted >= 1);
		NdCharFmt_Assert(nCvted <= 4);
		NdCharFmt_Assert(nCvted <= 2 || !bToAnsi);
		NdCharFmt_Assert(!bUsedDefaultChar || bToAnsi);
		if (bToAnsi && bUsedDefaultChar && bUseCIF) {
			putCIF<char>(wch, pDestBuf);
			return 7;
		}
		else
		    return nCvted;
	}
	static unsigned wcharToUtf16(wchar_t wch, char * pDestBuf,
	                             unsigned nDestBufSize,
	                             bool bLittleEndian, bool bExpandLF)
	{
		NdCharFmt_Assert(nDestBufSize >= 2);
		if (nDestBufSize < 2)
			return 0;
		unsigned short *pShortDest = (unsigned short *)pDestBuf;
		unsigned nBytes = 2;
		if (wch == L'\n' && bExpandLF) {
			NdCharFmt_Assert(nDestBufSize >= 4);
			*pShortDest = bLittleEndian ? 0x000d : 0x0d00;
			nBytes += 2;
			pShortDest++;
		}
		if (bLittleEndian)
			*pShortDest = wch;
		else
		    *pShortDest = ((wch >> 8) & 0xff) | ((wch << 8) & 0xff00);
		return nBytes;
	}
	unsigned wcharToBytes(wchar_t wch, char *pDestBuf,
	                      unsigned nDestBufSize) const
	{
		if (this->mnFormat == kAnsi || this->mnFormat == kUtf8)
			return wcharToAnsiOrUtf8(wch, pDestBuf, nDestBufSize,
		                             this->mnFormat == kAnsi,
		                             this->mbUseCIF, this->mbExpandLF);
		else if (this->mnFormat == kUtf16LE || this->mnFormat == kUtf16BE) {
			NdCharFmt_Assert(!this->mbUseCIF);
			return wcharToUtf16(wch, pDestBuf, nDestBufSize,
			                    this->mnFormat == kUtf16LE,
			                    this->mbExpandLF);
		}
		else {
			NdCharFmt_Assert(!this->mbUseCIF);
			NdCharFmt_Assert(nDestBufSize >= 4);
			NdCharFmt_Assert(this->mnFormat == kUtf32LE ||
			                 this->mnFormat == kUtf32BE);
			NdCharFmt_Assert(this->mnFormat != kUtf32LE);
			NdCharFmt_Assert(this->mnFormat != kUtf32BE);
			return 0;
		}
	}
	template <class ChType> static bool isHex(ChType ch)
	{
		return (ch >= '0' && ch <= '9') ||
		       (ch >= 'A' && ch <= 'F') ||
		       (ch >= 'a' && ch <= 'f');
	}
	template <class ChType> static bool isHex(ChType ch, unsigned &uVal)
	{
		if (ch >= '0' && ch <= '9') {
			uVal = ch - '0';
			NdCharFmt_Assert(uVal <= 9);
			return true;
		}
		if (ch >= 'A' && ch <= 'F') {
			uVal = ch - 'A' + 10;
			NdCharFmt_Assert(uVal >= 10);
			NdCharFmt_Assert(uVal <= 15);
			return true;
		}
		if (ch >= 'a' && ch <= 'f') {
			uVal = ch - 'a' + 10;
			NdCharFmt_Assert(uVal >= 10);
			NdCharFmt_Assert(uVal <= 15);
			return true;
		}
		return false;
	}
	template <class ChType> static bool isCIFString(const ChType *pSrcBuf)
	{
		NdCharFmt_Assert(pSrcBuf != NULL);
		if (pSrcBuf[0] == '\\' &&
		        (pSrcBuf[1] == 'U' || pSrcBuf[1] == 'u') &&
		        pSrcBuf[2] == '+' &&
		        isHex<ChType>(pSrcBuf[3])  &&
		        isHex<ChType>(pSrcBuf[4])  &&
		        isHex<ChType>(pSrcBuf[5])  &&
		        isHex<ChType>(pSrcBuf[6]))
		    return true;
		return false;
	}
	template <class ChType> static bool isCIFString(
	                const ChType *pSrcBuf, unsigned nSrcBufSize)
	{
		NdCharFmt_Assert(pSrcBuf != NULL);
		NdCharFmt_Assert(nSrcBufSize > 0);
		if(nSrcBufSize < 7)
			return false;
		return isCIFString<ChType>(pSrcBuf);
	}
	template <class ChType> static bool parseCIF(
	                    const ChType *pSrcBuf, wchar_t &wch)
	{
		NdCharFmt_Assert(pSrcBuf != NULL);
		if(pSrcBuf == NULL)
			return false;
		if (pSrcBuf[0] != '\\' || (pSrcBuf[1] != 'U' && pSrcBuf[1] != 'u') || pSrcBuf[2] != '+')
			return false;
		unsigned uVal;
		if (!isHex<ChType>(pSrcBuf[3], uVal))
			return false;
		wch = (wchar_t)(uVal << 12);
		if (!isHex<ChType>(pSrcBuf[4], uVal))
			return false;
		wch |= (wchar_t)(uVal << 8);
		if (!isHex<ChType>(pSrcBuf[5], uVal))
			return false;
		wch |= (wchar_t)(uVal << 4);
		if (!isHex<ChType>(pSrcBuf[6], uVal))
			return false;
		wch |= (wchar_t)uVal;
		return true;
	}
	template <class ChType> static bool isMIFString(const ChType *pSrcBuf)
	{
		NdCharFmt_Assert(pSrcBuf != NULL);
		if (pSrcBuf[0] == '\\' &&
		        (pSrcBuf[1] == 'M' || pSrcBuf[1] == 'm')  &&
		        pSrcBuf[2] == '+'  &&
		        pSrcBuf[3] >= '1'  &&
		        pSrcBuf[3] <= '5'  &&
		        isHex<ChType>(pSrcBuf[4])  &&
		        isHex<ChType>(pSrcBuf[5])  &&
		        isHex<ChType>(pSrcBuf[6])  &&
		        isHex<ChType>(pSrcBuf[7]))
		    return true;
		return false;
	}
	template <class ChType> static bool isMIFString(const ChType *pSrcBuf,
	                                                unsigned nSrcBufSize)
	{
		NdCharFmt_Assert(pSrcBuf != NULL);
		NdCharFmt_Assert(nSrcBufSize > 0);
		if(nSrcBufSize < 8)
			return false;
		return isMIFString<ChType>(pSrcBuf);
	}
	static unsigned winCodePageFromMIFIndex(unsigned nIdx)
	{
		return nIdx == 1 ? 932 :
		       nIdx == 2 ? 950 :
		       nIdx == 3 ? 949 :
		       nIdx == 4 ? 1361 :
		       nIdx == 5 ? 936 : 0;
	}
	static unsigned char MIFIndexFromWinCodePage(unsigned nCodePage)
	{
		return nCodePage == 932 ? 1 :
		       nCodePage == 950 ? 2 :
		       nCodePage == 949 ? 3 :
		       nCodePage == 1361 ? 4 :
		       nCodePage == 936 ? 5 : 0;
	}
	template <class ChType> static bool putMIF(wchar_t wch,
	                                           ChType *pMbOut, unsigned nWinCodePage)
	{
		const unsigned char nMIFIndex = MIFIndexFromWinCodePage(nWinCodePage);
		if (nMIFIndex == 0)
			return false;
		NdCharFmt_Assert(nMIFIndex >= 1);
		NdCharFmt_Assert(nMIFIndex <= 5);
		char mbBuf[2];
		const int nMbChars = isNativeToCodePage(wch, nWinCodePage, mbBuf);
		if (nMbChars == 0)
			return false;
		if (nMbChars == 1) {
			mbBuf[1] = mbBuf[0];
			mbBuf[0] = 0;
		}
		NdCharFmt_Assert(nMbChars <= 2);
		pMbOut[0] = '\\';
		pMbOut[1] = 'M';
		pMbOut[2] = '+';
		pMbOut[3] = '0' + nMIFIndex;
		unsigned nNibs[4];
		nNibs[0] = mbBuf[0] >> 4;
		nNibs[1] = mbBuf[0];
		nNibs[2] = mbBuf[1] >> 4;
		nNibs[3] = mbBuf[1];
		for (int i = 0; i < 4; i++) {
			const ChType n = (ChType)(nNibs[i] & 0xf);
			pMbOut[4 + i] = (n <= 9) ? ('0' + n) : ('A' - 10 + n);
		}
		return true;
	}
	template <class ChType> static unsigned getMIFCodePage(ChType ch)
	{
		return
		        ch == '1' ?  932  :
		        ch == '2' ?  950  :
		        ch == '3' ?  949  :
		        ch == '4' ? 1361  :
		        ch == '5' ?  936  :
		        0;
	}
	template <class ChType> static bool parseMIF(const ChType *pSrcBuf,
	                                             wchar_t &wch)
	{
		NdCharFmt_Assert(pSrcBuf != NULL);
		if (pSrcBuf == NULL)
			return false;
		if (pSrcBuf[0] != '\\' || (pSrcBuf[1] != 'M' && pSrcBuf[1] != 'm') || pSrcBuf[2] != '+')
			return false;
		const unsigned nCodePage = getMIFCodePage<ChType>(pSrcBuf[3]);
		if (nCodePage == 0)
			return false;
		char mbBuf[2];
		unsigned uVal;
		if (!isHex<ChType>(pSrcBuf[4], uVal))
			return false;
		mbBuf[0] = (char)(uVal << 4);
		if (!isHex<ChType>(pSrcBuf[5], uVal))
			return false;
		mbBuf[0] |= (char)uVal;
		if (!isHex<ChType>(pSrcBuf[6], uVal))
			return false;
		mbBuf[1] = (char)(uVal << 4);
		if (!isHex<ChType>(pSrcBuf[7], uVal))
			return false;
		mbBuf[1] |= (char)(uVal);
		if (mbBuf[0] == 0) {
			mbBuf[0] = mbBuf[1];
			mbBuf[1] = 0;
		}
		const int nCvted = MultiByteToWideChar(
		    nCodePage,
		    MB_ERR_INVALID_CHARS,
		    mbBuf,
		    mbBuf[1] == 0 ? 1 : 2,
		    &wch,
		    1);
		NdCharFmt_Assert(nCvted >= 0);
		NdCharFmt_Assert(nCvted <= 1);
		if(nCvted != 1)
			return false;
		return true;
	}
	static int isNativeToCodePage(wchar_t wch,
	                              unsigned nCodePage,
	                              char *pChNative = NULL)
	{
		if (wch >= 0 && wch <= 0x7f)
			{
			if (pChNative != NULL) {
				*pChNative = (char)wch;
				NdCharFmt_Assert(*pChNative == (char)wch);
			}
			return 1;
		}
		BOOL bDefaultUsed = FALSE;
		char chNative[2];
		if (pChNative == NULL)
			pChNative = chNative;
		const int nCvted = WideCharToMultiByte(nCodePage,
		                                       kNoBestFitFlag,
		                                       &wch, 1,
		                                       pChNative, 2,
		                                       NULL, &bDefaultUsed);
		if (nCvted <= 0 || bDefaultUsed != FALSE)
			return 0;
		return nCvted;
	}
	static int wcharNonNativeToCIF(
	    const wchar_t *szSrc,
	    wchar_t *szDst,
	    int cchDstSize)
	{

		NdCharFmt_Assert(szSrc != NULL);
		NdCharFmt_Assert(szDst == NULL || cchDstSize > 0);
		if (szSrc == NULL || (szDst != NULL && cchDstSize <= 0))
			return 0;
		int cchWritten = 0;
		wchar_t *lpReadPtr = ((wchar_t *) szSrc);
		while(*lpReadPtr)
		{
			if (szDst && (cchWritten >= cchDstSize - 1))
				break;
			const wchar_t wch = *lpReadPtr;
			if (isNativeToCodePage(wch, CP_ACP))
				{
				if (szDst != NULL)
					*szDst++ = wch;
				cchWritten++;
			}
			else
			{
				if (szDst != NULL)
					{
					NdCharFmt_Assert(cchDstSize - cchWritten >= 8);
					if(cchDstSize - cchWritten < 8)
						break;
					putCIF<wchar_t>(wch, szDst);
					szDst = szDst + 7;
				}
				cchWritten += 7;
			}
			lpReadPtr++;
		}
		if (szDst != NULL)
			*szDst = L'\0';
		return cchWritten + 1;
	}
	static int wcharFromCIFMIF(
	    const wchar_t *szSrc,
	    wchar_t *szDst,
	    int cchDstSize)
	{
		NdCharFmt_Assert(szSrc != NULL);
		NdCharFmt_Assert(szDst == NULL || cchDstSize > 0);
		NdCharFmt_Assert(szDst != NULL || cchDstSize <= 0);
		if (szSrc == NULL)
			return 0;
		if (szDst != NULL && cchDstSize <= 0)
			return 0;
		if (szDst == NULL && cchDstSize > 0)
			return 0;
		int cchWritten = 0;
		const wchar_t *lpReadPtr  = szSrc;
		wchar_t *lpWritePtr = szDst;
		wchar_t *lpWriteEnd = szDst + NcCastIntToSize_t(cchDstSize);
		if (szDst == NULL && cchDstSize < 0)
			{
			lpWritePtr = const_cast<wchar_t *>(szSrc);
			lpWriteEnd = NULL;
		}
		for (;;) {
			if (lpWritePtr && lpWriteEnd && lpWritePtr >= lpWriteEnd)
				break;
			const wchar_t wch = *lpReadPtr;
			wchar_t wchOut;
			if (parseCIF<wchar_t>(lpReadPtr, wchOut))
				lpReadPtr += 7;
			else if (parseMIF<wchar_t>(lpReadPtr, wchOut))
			    lpReadPtr += 8;
			else {
				wchOut = wch;
				lpReadPtr++;
			}
			if (lpWritePtr != NULL)
				*lpWritePtr++ = wchOut;
			cchWritten++;
			if (wch == 0)
				break;
		}
		return cchWritten;
	}
	static int wcharNonNativeToRTF(
	    unsigned nCodePage,
	    const wchar_t *szSrc,
	    int cchSrcLen,
	    char *szDst,
	    int *pcbDstSize)
	{
		NdCharFmt_Assert(szSrc != NULL);
		NdCharFmt_Assert(pcbDstSize != NULL);
		NdCharFmt_Assert(cchSrcLen >= -1);
		NdCharFmt_Assert(cchSrcLen < 0x1000000);
		if (szSrc == NULL || pcbDstSize == NULL)
			return 0;
		if (cchSrcLen < -1)
			return 0;
		NdCharFmt_Assert(szDst == NULL || *pcbDstSize > 0);
		if (szDst != NULL && *pcbDstSize <= 0)
			return 0;
		int cbWritten = 0;
		int cchProcessed = 0;
		for (;;) {
			if (cchSrcLen >= 0) {
				NdCharFmt_Assert(cchProcessed <= cchSrcLen);
				if (cchProcessed >= cchSrcLen)
					break;
			}
			char szAnsiBuf[2];
			const wchar_t wch = szSrc[cchProcessed];
			if (wch == L'\0') {
				if (cchSrcLen < 0)
					break;
			}
			const int cbAnsiSize = isNativeToCodePage(
			    wch, nCodePage, szAnsiBuf);
			NdCharFmt_Assert(cbAnsiSize >= 0);
			NdCharFmt_Assert(cbAnsiSize <= 2);
			if (cbAnsiSize > 0) {
				if (szDst) {
					if (cbWritten + cbAnsiSize >= *pcbDstSize)
						break;
					szDst[cbWritten] = szAnsiBuf[0];
					if (cbAnsiSize > 1)
						szDst[cbWritten+1] = szAnsiBuf[1];
				}
				cbWritten += cbAnsiSize;
			}
			else {
				unsigned short nValue = wch;
				NdCharFmt_Assert(nValue >= 128);
				int nDigits = 3;
				if (nValue < 1000)       nDigits += 3;
				else if (nValue < 10000) nDigits += 4;
				else                     nDigits += 5;
				if (szDst) {
					if (cbWritten + nDigits >= *pcbDstSize)
						break;
					szDst[cbWritten + 0] = '\\';
					szDst[cbWritten + 1] = 'u';
					int i = cbWritten + nDigits - 1;
					szDst[i] = '?';
					do {
						NdCharFmt_Assert(i > cbWritten + 1);
						i--;
						szDst[i] = (char)((nValue % 10) + '0');
						nValue /= 10;
					} while (nValue != 0);
					NdCharFmt_Assert(i == cbWritten + 2);
				}
				cbWritten += nDigits;
			}
			cchProcessed++;
		}
		*pcbDstSize = cbWritten;
		if (cchSrcLen < 0) {
			if (szDst) szDst[cbWritten] = 0;
			*pcbDstSize = cbWritten + 1;
		}
		return cchProcessed;
	}
private:
	unsigned mnFormat;
	bool mbUseCIF;
	bool mbExpandLF;
};



//////////////////////////////////////////////////////////////////////////
// NcFILE
class NcFILE {
public:
	NcFILE()
	    : mpFILE(NULL),
	      mChFmtr(NdCharFormatter::kAnsi,
	              false,
	              false)
	{}
	NcFILE(FILE *pFILE)
	    : mpFILE(pFILE),
	      mChFmtr(NdCharFormatter::kAnsi,
	              false,
	              false)
	{}
	~NcFILE() {
		NcFILE_Assert(this->mpFILE == NULL);
	}
	FILE * fopen(const TCHAR *pName, const TCHAR *pMode);
	FILE * fsopen(const TCHAR *pName, const TCHAR *pMode, int shflag);
	void attach(FILE *pFILE);
	FILE * detach();
	int fclose();
	int fputs(const TCHAR *pStr);
	TCHAR * fgets(TCHAR *pBuf, int nChars);
	int fprintf(const TCHAR *pFmtStr, ...);
	int vfprintf(const TCHAR *pFmtStr, va_list va);
	int fscanf(const TCHAR *pFmtStr, ...);
	int fputc(TCHAR c);
	int ungetc(TCHAR c);
	int fgetc();
	bool isOpen() const { return this->mpFILE != NULL; }
	FILE * pFILE() const { return this->mpFILE; }
	unsigned getCharFormat() const { return this->mChFmtr.getFormat(); }
	unsigned setCharFormat(unsigned nFmt) {
		return this->mChFmtr.setFormat(nFmt); }
	bool getUseCIF() const { return this->mChFmtr.getUseCIF(); }
	bool setUseCIF(bool bUseCIF) {
		return this->mChFmtr.setUseCIF(bUseCIF); }
	bool getExpandLF() const { return this->mChFmtr.getExpandLF(); }
	bool setExpandLF(bool bExpandLF) {
		return this->mChFmtr.setExpandLF(bExpandLF); }
	bool readBOM();
	bool writeBOM();
private:
	#ifdef UNICODE
	  bool parseAnsiOrCIF(wchar_t &wch);
	  bool parseUtf8(wchar_t &wch);
	  bool parseUtf16(wchar_t &wch);
	  int  fputsWorker(const wchar_t* pSrc, int nOptions);
	#endif
	FILE *mpFILE;
	NdCharFormatter mChFmtr;
};



//////////////////////////////////////////////////////////////////////////
// NcOutputBufMgr
class NcOutputBufMgr {
public:
	NcOutputBufMgr();
	~NcOutputBufMgr();
	bool attachBuffer(void *pBuffer, unsigned nBufSize);
	bool detachBuffer();
	bool hasBuffer() const;
	unsigned byteCount() const;
	void * pointer() const;
	void * requestBytes(unsigned nBytesNeeded);
	unsigned takeBytes(unsigned nBytesUsed);
	bool     reset();
private:
	void * mpBuffer;
	unsigned mnBufSize;
	unsigned mnByteCount;
	unsigned mnBytesRequested;
};

#ifdef _AFX
	//////////////////////////////////////////////////////////////////////////
	// NcCFile
	class NcCFile : public CFile {
	public:
		NcCFile();
		NcCFile(HANDLE hFile);
		NcCFile(LPCTSTR lpszFileName, UINT nOpenFlags);
		virtual ~NcCFile();
		virtual UINT Read(void *lpBuf, UINT nCount);
		virtual void Write(const void *lpBuf, UINT nCount);
		virtual UINT Read(LPTSTR lpBuf, UINT nCount);
		virtual void Write(LPCTSTR pString, UINT nCount);
		virtual void Write(LPCTSTR pString);
		unsigned getCharFormat() const { return this->mChFmtr.getFormat(); }
		unsigned setCharFormat(unsigned nFmt) {
			return this->mChFmtr.setFormat(nFmt); }
		bool getUseCIF() const { return this->mChFmtr.getUseCIF(); }
		bool setUseCIF(bool bUseCIF) {
			return this->mChFmtr.setUseCIF(bUseCIF); }
		bool getExpandLF() const { return this->mChFmtr.getExpandLF(); }
		bool setExpandLF(bool bExpandLF) {
			return this->mChFmtr.setExpandLF(bExpandLF); }
		bool readBOM();
		bool writeBOM();
		bool attachBuffer(void *pBuffer, unsigned nBufSize);
		bool detachBuffer();
		bool flushBytes();
		bool hasBuffer() const;
	private:
		NdCharFormatter mChFmtr;
		NcOutputBufMgr mOutputBufMgr;
	};

	//////////////////////////////////////////////////////////////////////////
	// NcCStdioFile
	class NcCStdioFile : public CStdioFile {
	public:
		NcCStdioFile();
		NcCStdioFile(FILE* pOpenStream);
		NcCStdioFile(LPCTSTR lpszFileName, UINT nOpenFlags);
		virtual ~NcCStdioFile();
		virtual void WriteString(LPCTSTR lpsz);
		virtual LPTSTR ReadString(LPTSTR lpsz, UINT nMax);
		virtual BOOL ReadString(CString& rString);
		unsigned getCharFormat() const { return this->mChFmtr.getFormat(); }
		unsigned setCharFormat(unsigned nFmt) {
				return this->mChFmtr.setFormat(nFmt); }
		bool getUseCIF() const { return this->mChFmtr.getUseCIF(); }
		bool setUseCIF(bool bUseCIF) {
			return this->mChFmtr.setUseCIF(bUseCIF); }
		bool getExpandLF() const { return this->mChFmtr.getExpandLF(); }
		bool setExpandLF(bool bExpandLF) {
			return this->mChFmtr.setExpandLF(bExpandLF); }
		bool readBOM();
		bool writeBOM();
		bool attachBuffer(void *pBuffer, unsigned nBufSize);
		bool detachBuffer();
		bool flushBytes();
		bool hasBuffer() const;
	private:
		NdCharFormatter mChFmtr;
		NcOutputBufMgr mOutputBufMgr;
	};
#endif // _AFX

//////////////////////////////////////////////////////////////////////////
// NcFileDependencyInfo
class NcFileDependencyInfo {
public:
	const NCHAR *mpFullFileName;
	const NCHAR *mpFileName;
	const NCHAR *mpFoundPath;
	const NCHAR *mpFingerprintGuid;
	const NCHAR *mpVersionGuid;
	const NCHAR *mpFeature;
	bool        mIsModified;
	bool        mAffectsGraphics;
	NRX::Int32        mIndex;
	NRX::Int32        mTimeStamp;
	NRX::Int32        mFileSize;
	NRX::Int32        mReferenceCount;
};

//////////////////////////////////////////////////////////////////////////
// NcIfstream
class NcIfstream : public
#ifndef UNICODE
                        std::ifstream {
#else
                        std::wifstream {
#endif
public:
	NcIfstream() {};
	NcIfstream(const NCHAR *pName);
#ifdef UNICODE
	void open(const wchar_t *pName);
	void open(const wchar_t *pName, ios_base::openmode nMode);
#endif
};

//////////////////////////////////////////////////////////////////////////
// NcOfstream
class NcOfstream : public
#ifndef UNICODE
	std::ofstream {
#else
	std::wofstream {
#endif
public:
	NcOfstream() {};
	NcOfstream(const NCHAR *pName);
#ifdef UNICODE
	void open(const wchar_t *pName);
	void open(const wchar_t *pName, ios_base::openmode nMode);
#endif
};

#ifdef UNICODE
void ncByteSwap(wchar_t &wch);
#endif

#ifdef _AFX
unsigned ncCheckCFileCharFormat(CFile *pCFile);
bool ncReadAnsiCharFromCFile(CFile *pCFile, wchar_t &wch, NdCharFormatter *pChFmtr);
bool ncReadCIFFromCFile(CFile *pCFile, wchar_t &wch);
bool ncReadUtf16CharFromCFile(CFile *pCFile, wchar_t &wch, NdCharFormatter *pChFmtr);
bool ncReadUtf8CharFromCFile(CFile *pCFile, wchar_t &wch, NdCharFormatter *pChFmtr);
void ncWriteWCharToCFile(wchar_t wch, CFile *pFile, unsigned nFmt, bool bUseCIF);
#endif

std::locale NcFStream_curLocale();
int NcFStream_wideToMulti(const wchar_t*pSrc, int nSrcSize,
                                 char*pDest, int nDestSize);

#endif // __NANOTHUNK_FILER_H__
