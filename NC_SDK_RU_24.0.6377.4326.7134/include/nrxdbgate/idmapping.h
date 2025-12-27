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

#ifndef __OPENDWG_IDMAPPING_H__
#define __OPENDWG_IDMAPPING_H__
#include "nrxdbgate_impexp.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbIdPair
class OdDbIdPair;
class NRXDBGATE_EXPORT NcDbIdPair
{
public:
	typedef NcDbIdPair  wrapper_class;
	typedef OdDbIdPair  native_class;
	NcDbIdPair();
	NcDbIdPair(const NcDbIdPair& pair);
	NcDbIdPair(NcDbObjectId key, NcDbObjectId value, bool cloned, bool primary = false, bool isOwnerXlated = true);
	virtual ~NcDbIdPair();

	NcDbIdPair &operator = (const NcDbIdPair& pair);
	NcDbIdPair &operator = (const OdDbIdPair& pair);

public:
	NcDbObjectId key() const;
	void setKey(NcDbObjectId id);

	NcDbObjectId value() const;
	void setValue(NcDbObjectId id);

	bool isCloned() const;
	void setIsCloned(bool cloned);

	bool isPrimary() const;
	void setIsPrimary(bool isPrimary);

	bool isOwnerXlated() const;
	void setIsOwnerXlated(bool isOwnerXlated);

public:
	OdDbIdPair* native() const;

protected:
	OdDbIdPair* m_pNative;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbIdMapping
class OdDbIdMapping;
class NRXDBGATE_EXPORT NcDbIdMapping : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbIdMapping);

	NcDbIdMapping();
	NcDbIdMapping(OdRxObject* _object);

public:
	typedef OdDbIdMapping  native_class;

public:
	virtual Nano::ErrorStatus assign(const NcDbIdPair& pair);
	virtual bool compute(NcDbIdPair& pair) const;
	virtual bool change(const NcDbIdPair& pair);
	virtual bool del(NcDbObjectId key);

	Nano::ErrorStatus destDb(NcDbDatabase*& db) const;
	Nano::ErrorStatus setDestDb(NcDbDatabase* db);

	Nano::ErrorStatus origDb(NcDbDatabase*& db) const;

	NcDb::DeepCloneType deepCloneContext() const;
	NcDb::DuplicateRecordCloning duplicateRecordCloning() const;

	virtual Nano::ErrorStatus copyFrom(const NcRxObject* other);

public:
	OdDbIdMapping* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
// class NcDbIdMappingIter
class OdDbIdMappingIter;
class NRXDBGATE_EXPORT NcDbIdMappingIter : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbIdMappingIter);

public:
	NcDbIdMappingIter(const NcDbIdMapping& mapping);

public:
	virtual Nano::ErrorStatus iterateOn(const NcDbIdMapping& mapping);

	virtual void start();
	virtual bool getMap(NcDbIdPair& pair);
	virtual bool next();
	virtual bool done();

public:
	inline OdDbIdMappingIter* native() const;
private:
	NRX::UInt64   _position;
	void        * _internal;
};

#endif // opendwg_idmapping.h