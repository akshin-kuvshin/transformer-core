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

#ifndef __OPENDWG_OBJECTID_H__
#define __OPENDWG_OBJECTID_H__

#include "nrxdbgate_impexp.h"

class NcDbStub;

class NcDbDatabase;
class NcDbObjectId;
class NcDbFullSubentPath;
class NcRxClass;

typedef NcArray< NcDbObjectId >                                                            NcDbObjectIdArray;
template class NRXDBGATE_EXPORT NcArray< NcDbObjectId >;
typedef NcArray< NcDbFullSubentPath, NcArrayObjectCopyReallocator< NcDbFullSubentPath > >  NcDbFullSubentPathArray;
template class NRXDBGATE_EXPORT NcArray< NcDbFullSubentPath, NcArrayObjectCopyReallocator< NcDbFullSubentPath > >;
typedef NcDbFullSubentPathArray                                                            NcSubentPathArray;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbObjectId
class NRXDBGATE_EXPORT NcDbObjectId
{
public:
	NcDbObjectId();
	NcDbObjectId(const NcDbStub* pointer);

	bool isNull() const;
	void setNull();

	LONG_PTR asOldId() const;
	NcDbObjectId& setFromOldId(LONG_PTR oldId);

	bool isValid() const;
	bool isResident() const;

	NcDbObjectId& operator=(const NcDbObjectId& id);
	NcDbObjectId& operator=(const NcDbStub* pointer);

	bool operator<(const NcDbObjectId& id) const;
	bool operator>(const NcDbObjectId& id) const;
	bool operator>=(const NcDbObjectId& id) const;
	bool operator<=(const NcDbObjectId& id) const;
	bool operator==(const NcDbObjectId& id) const;
	bool operator!=(const NcDbObjectId& id) const;

	bool operator<(const NcDbStub* pointer) const;
	bool operator>(const NcDbStub* pointer) const;
	bool operator>=(const NcDbStub* pointer) const;
	bool operator<=(const NcDbStub* pointer) const;
	bool operator==(const NcDbStub* pointer) const;
	bool operator!=(const NcDbStub* pointer) const;

	operator NcDbStub*() const;

	NcDbDatabase* database() const;
	NcDbDatabase* originalDatabase() const;
	void convertToRedirectedId();
	bool isErased() const;
	bool isEffectivelyErased() const;
	bool objectLeftOnDisk() const;

	NcDbHandle handle() const;
	NcDbHandle nonForwardedHandle() const;

	NcRxClass* objectClass() const;

	static const NcDbObjectId kNull;
protected:
	NcDbStub*  m_Id;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbHardOwnershipId
class NRXDBGATE_EXPORT NcDbHardOwnershipId : public NcDbObjectId
{
public:
	NcDbHardOwnershipId();
	NcDbHardOwnershipId(const NcDbObjectId& id);
	NcDbHardOwnershipId(const NcDbStub* pointer);

	NcDbHardOwnershipId& operator=(const NcDbHardOwnershipId& id);
	NcDbHardOwnershipId& operator=(const NcDbObjectId& id);
	NcDbHardOwnershipId& operator=(const NcDbStub* pointer);

	bool operator!=(const NcDbObjectId& id) const;
	bool operator!=(const NcDbStub* pointer) const;
	bool operator==(const NcDbObjectId& id) const;
	bool operator==(const NcDbStub* pointer) const;

	operator NcDbStub* () const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSoftOwnershipId
class NRXDBGATE_EXPORT NcDbSoftOwnershipId : public NcDbObjectId
{
public:
	NcDbSoftOwnershipId();
	NcDbSoftOwnershipId(const NcDbObjectId& id);
	NcDbSoftOwnershipId(const NcDbStub* pointer);

	NcDbSoftOwnershipId& operator=(const NcDbSoftOwnershipId& id);
	NcDbSoftOwnershipId& operator=(const NcDbObjectId& id);
	NcDbSoftOwnershipId& operator=(const NcDbStub* pointer);

	bool operator!=(const NcDbObjectId& id) const;
	bool operator!=(const NcDbStub* pointer) const;
	bool operator==(const NcDbObjectId& id) const;
	bool operator==(const NcDbStub* pointer) const;

	operator NcDbStub* () const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbHardPointerId
class NRXDBGATE_EXPORT NcDbHardPointerId : public NcDbObjectId
{
public:
	NcDbHardPointerId();
	NcDbHardPointerId(const NcDbObjectId& id);
	NcDbHardPointerId(const NcDbStub* pointer);

	NcDbHardPointerId& operator=(const NcDbHardPointerId& id);
	NcDbHardPointerId& operator=(const NcDbObjectId& id);
	NcDbHardPointerId& operator=(const NcDbStub* pointer);

	bool operator!=(const NcDbObjectId& id) const;
	bool operator!=(const NcDbStub* pointer) const;
	bool operator==(const NcDbObjectId& id) const;
	bool operator==(const NcDbStub* pointer) const;

	operator NcDbStub* () const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSoftPointerId
class NRXDBGATE_EXPORT NcDbSoftPointerId : public NcDbObjectId
{
public:
	NcDbSoftPointerId();
	NcDbSoftPointerId(const NcDbObjectId& id);
	NcDbSoftPointerId(const NcDbStub* pointer);

	NcDbSoftPointerId& operator=(const NcDbSoftPointerId& id);
	NcDbSoftPointerId& operator=(const NcDbObjectId& id);
	NcDbSoftPointerId& operator=(const NcDbStub* pointer);

	bool operator!=(const NcDbObjectId& id) const;
	bool operator!=(const NcDbStub* pointer) const;
	bool operator==(const NcDbObjectId& id) const;
	bool operator==(const NcDbStub* pointer) const;

	operator NcDbStub*() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbXrefObjectId
class NRXDBGATE_EXPORT NcDbXrefObjectId
{
public:
	NcDbXrefObjectId();
	NcDbXrefObjectId(const NcDbXrefObjectId& other);

public:
	NcDbXrefObjectId& operator=(const NcDbXrefObjectId& other);
	bool operator==(const NcDbXrefObjectId& other) const;
	bool operator!=(const NcDbXrefObjectId& other) const;

public:
	bool isValid() const;
	bool isXref() const
	{
		return !m_handle.isNull();
	}
	bool isNull() const
	{
		return m_localId.isNull();
	}

public:
	Nano::ErrorStatus setNull(void);

	Nano::ErrorStatus setXrefId(NcDbObjectId xrefBlkId, const NcDbHandle& handle);
	Nano::ErrorStatus getXrefId(NcDbObjectId& xrefBlkId, NcDbHandle& handle) const;

	Nano::ErrorStatus setLocalId(NcDbObjectId id);
	Nano::ErrorStatus getLocalId(NcDbObjectId& id) const;

	Nano::ErrorStatus resolveObjectId(NcDbObjectId& id) const;

	Nano::ErrorStatus serializeToResbuf(resbuf*& chain, resbuf*& end) const;
	Nano::ErrorStatus serializeFromResbuf(const resbuf* chain, resbuf*& next);

private:
	NcDbObjectId m_localId;
	NcDbHandle   m_handle;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSubentId
class NRXDBGATE_EXPORT NcDbSubentId
{
public:
	NcDbSubentId();
	NcDbSubentId(NcDb::SubentType type, NRX::GsMarker index);
	NcDbSubentId(NcRxClass* type_class, NRX::GsMarker index);

	bool operator==(const NcDbSubentId& id) const;
	bool operator!=(const NcDbSubentId& id) const;

	NcDb::SubentType type() const;
	void setType(NcDb::SubentType type);

	NcRxClass* typeClass() const;
	void setTypeClass(NcRxClass* type_class);

	NRX::GsMarker index() const;
	void setIndex(NRX::GsMarker index);
private:
	NcDb::SubentType m_Type;
	NRX::GsMarker    m_Index;
	//NcRxClass*       m_pTypeClass;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbFullSubentPath
class NRXDBGATE_EXPORT NcDbFullSubentPath
{
public:
	NcDbFullSubentPath();
	NcDbFullSubentPath(NcDb::SubentType type, NRX::GsMarker index);
	NcDbFullSubentPath(NcDbObjectId id, NcDb::SubentType type, NRX::GsMarker index);
	NcDbFullSubentPath(NcDbObjectId id, NcDbSubentId subid);
	NcDbFullSubentPath(NcDbObjectIdArray ids, NcDbSubentId subid);
	NcDbFullSubentPath(const NcDbFullSubentPath& path);
	~NcDbFullSubentPath();

	NcDbFullSubentPath& operator=(const NcDbFullSubentPath& path);

	bool operator==(const NcDbFullSubentPath& path) const;
	bool operator!=(const NcDbFullSubentPath& path) const;

	void objectIds(NcDbObjectIdArray& ids) const;
	NcDbObjectIdArray& objectIds();
	const NcDbObjectIdArray& objectIds() const;
	const NcDbSubentId subentId() const;
	NcDbSubentId& subentId();

private:                            
	NcDbObjectIdArray m_ObjectIds;
	NcDbSubentId      m_SubentId;
};

extern const NRXDBGATE_EXPORT NcDbFullSubentPath kNullSubent;

#endif // __OPENDWG_OBJECTID_H__