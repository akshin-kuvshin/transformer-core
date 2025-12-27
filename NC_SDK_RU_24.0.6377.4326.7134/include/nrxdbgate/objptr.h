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
#ifdef DEBUG
#ifdef ASSERT
	#define DbObjPtr_Assert  ASSERT
#elif defined assert
	#define DbObjPtr_Assert  assert
#elif defined _ASSERTE
	#define DbObjPtr_Assert  _ASSERTE
#else
	#define DbObjPtr_Assert(T)
#endif
#else
#undef assert
#define assert(e) ((void)0)
#define DbObjPtr_Assert(e) ((void)0)
#endif

#pragma pack (push, 8)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbObjectPointerBase
template < class _Type >
class NcDbObjectPointerBase
{
public:
	NcDbObjectPointerBase() : m_ptr(NULL), m_status(Nano::eNullObjectPointer) {}

	virtual ~NcDbObjectPointerBase()
	{
		if (m_ptr != NULL)
		{
			assert(m_status == Nano::eOk);
			Nano::ErrorStatus status = closeInternal();
			assert(status == Nano::eOk);
		}
	}

	const _Type* object() const
	{
		assert(m_status == Nano::eOk);
		assert(m_ptr != NULL);
		DbObjPtr_Assert(m_ptr == NULL || m_ptr->isReadEnabled());

		return m_ptr;
	}

	_Type* object()
	{
		assert(m_status == Nano::eOk);
		assert(m_ptr != NULL);
		DbObjPtr_Assert(m_ptr == NULL || m_ptr->isReadEnabled());

		return m_ptr;
	}

	const _Type* operator->() const
	{
		return object();
	}
	_Type* operator->()
	{
		return object();
	}

	operator const _Type*() const
	{
		return object();
	}
	operator _Type*()
	{
		return object();
	}

	Nano::ErrorStatus openStatus() const
	{
		return m_status;
	}

	Nano::ErrorStatus open(NcDbObjectId id, NcDb::OpenMode mode, bool open_erased = false)
	{
		if (m_ptr != NULL)
		{
			assert(m_status == Nano::eOk);
			Nano::ErrorStatus status = closeInternal();
			if (status != Nano::eOk)
				return status;
		}

		m_status = ncdbOpenObject(m_ptr, id, mode, open_erased);

		return m_status;
	}

	Nano::ErrorStatus acquire(_Type*& pObjToAcquire)
	{
		if (pObjToAcquire == NULL)
			return Nano::eNullObjectPointer;

		if (m_ptr != NULL)
		{
			assert(m_status == Nano::eOk);
			Nano::ErrorStatus status = closeInternal();
			if (status != Nano::eOk)
				return status;
		}

		m_ptr     = pObjToAcquire;
		m_status      = Nano::eOk;
		pObjToAcquire = NULL;

		return Nano::eOk;
	}

	Nano::ErrorStatus release(_Type*& pReleasedObj)
	{
		if (m_ptr == NULL)
			return Nano::eNullObjectPointer;

		assert(m_status == Nano::eOk);
		pReleasedObj = m_ptr;
		m_ptr    = NULL;
		m_status     = Nano::eNullObjectPointer;

		return Nano::eOk;
	}

	Nano::ErrorStatus close()
	{
		if (m_ptr == NULL)
			return Nano::eNullObjectPointer;

		assert(m_status == Nano::eOk);
		Nano::ErrorStatus status = closeInternal();
		assert(status == Nano::eOk);

		return Nano::eOk;
	}

	Nano::ErrorStatus create()
	{
		_Type* pObject = new _Type;

		if (pObject == NULL)
			return Nano::eNullObjectPointer;

		if (m_ptr != NULL)
		{
			assert(m_status == Nano::eOk);
			Nano::ErrorStatus status = closeInternal();

			if (status != Nano::eOk)
			{
				delete pObject;
				return status;
			}
		}

		m_ptr = pObject;
		m_status  = Nano::eOk;

		return Nano::eOk;
	}


protected:
	NcDbObjectPointerBase(NcDbObjectId id, NcDb::OpenMode mode, bool open_erased) : m_ptr(NULL),
		m_status(ncdbOpenObject(m_ptr, id, mode, open_erased)) {}

	_Type*            m_ptr;
	Nano::ErrorStatus m_status;

private:
	NcDbObjectPointerBase(NcDbObjectPointerBase& pObject);
	NcDbObjectPointerBase& operator=(NcDbObjectPointerBase& pObject);

	Nano::ErrorStatus closeInternal()
	{
		if (m_ptr == NULL)
			return Nano::eOk;

		Nano::ErrorStatus es = Nano::eOk;

		if (m_ptr->objectId().isNull())
		{
			delete m_ptr;
			es = Nano::eOk;
		}
		else
		{
			es = m_ptr->close();
		}

		m_ptr = NULL;
		m_status  = Nano::eNullObjectPointer;

		return es;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbObjectPointer
template < class _Type >
class NcDbObjectPointer : public NcDbObjectPointerBase< _Type >
{
public:
	NcDbObjectPointer() : NcDbObjectPointerBase< _Type >() {}
	NcDbObjectPointer(NcDbObjectId id, NcDb::OpenMode mode, bool open_erased = false) :
		NcDbObjectPointerBase< _Type >(id, mode, open_erased) {}

	Nano::ErrorStatus open(NcDbObjectId id, NcDb::OpenMode mode, bool open_erased = false)
	{
		return NcDbObjectPointerBase< _Type >::open(id, mode, open_erased);
	}

private:
	NcDbObjectPointer(NcDbObjectPointer& pObject);
	NcDbObjectPointer& operator=(NcDbObjectPointer& pObject);
};

typedef NcDbObjectPointer< NcDbDictionary >  NcDbDictionaryPointer;
typedef NcDbObjectPointer< NcDbEntity >      NcDbEntityPointer;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSymbolTablePointer
template < class _Type >
class NcDbSymbolTablePointer : public NcDbObjectPointerBase< _Type >
{
public:
	NcDbSymbolTablePointer() : NcDbObjectPointerBase() {}
	NcDbSymbolTablePointer(NcDbObjectId id, NcDb::OpenMode mode) : NcDbObjectPointerBase< _Type >(id, mode, false) {}
	NcDbSymbolTablePointer(NcDbDatabase* database, NcDb::OpenMode mode) : NcDbObjectPointerBase< _Type >()
	{
		m_status = (database == NULL) ? Nano::eNullObjectPointer : database->getSymbolTable(m_ptr, mode);
	}

	inline Nano::ErrorStatus open(NcDbObjectId id, NcDb::OpenMode mode)
	{
		return NcDbObjectPointerBase< _Type >::open(id, mode, false);
	}
	inline Nano::ErrorStatus open(NcDbDatabase* database, NcDb::OpenMode mode)
	{
		if (database == NULL)
			return Nano::eInvalidInput;

		Nano::ErrorStatus es = Nano::eOk;

		if (m_ptr != NULL)
			es = close();

		if (es == Nano::eOk)
		{
			es       = database->getSymbolTable(m_ptr, mode);
			m_status = es;
		}

		return es;
	}

private:
	NcDbSymbolTablePointer(NcDbSymbolTablePointer& pObject);
	NcDbSymbolTablePointer& operator=(NcDbSymbolTablePointer& pObject);

	typedef typename _Type::RecordType  T2;
};

typedef NcDbSymbolTablePointer< NcDbBlockTable >      NcDbBlockTablePointer;
typedef NcDbSymbolTablePointer< NcDbDimStyleTable >   NcDbDimStyleTablePointer;
typedef NcDbSymbolTablePointer< NcDbLayerTable >      NcDbLayerTablePointer;
typedef NcDbSymbolTablePointer< NcDbLinetypeTable >   NcDbLinetypeTablePointer;
typedef NcDbSymbolTablePointer< NcDbRegAppTable >     NcDbRegAppTablePointer;
typedef NcDbSymbolTablePointer< NcDbTextStyleTable >  NcDbTextStyleTablePointer;
typedef NcDbSymbolTablePointer< NcDbUCSTable >        NcDbUCSTablePointer;
typedef NcDbSymbolTablePointer< NcDbViewTable >       NcDbViewTablePointer;
typedef NcDbSymbolTablePointer< NcDbViewportTable >   NcDbViewportTablePointer;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSymbolTableRecordPointer
template < class _Type >
class NcDbSymbolTableRecordPointer : public NcDbObjectPointerBase< _Type >
{
public:
	NcDbSymbolTableRecordPointer() : NcDbObjectPointerBase< _Type >() {}
	NcDbSymbolTableRecordPointer(NcDbObjectId id, NcDb::OpenMode mode, bool open_erased = false) :
		NcDbObjectPointerBase< _Type >(id, mode, open_erased) {}
	NcDbSymbolTableRecordPointer(const NCHAR* name, NcDbDatabase* database, NcDb::OpenMode mode,
	                             bool open_erased = false) : NcDbObjectPointerBase< _Type >()
	{
		if (name == NULL)
			m_status = Nano::eInvalidInput;
		else
		{
			NcDbSymbolTablePointer< _Type::TableType > table(database, NcDb::kForRead);

			m_status = table.openStatus();

			if (m_status == Nano::eOk)
				m_status = table->getAt(name, m_ptr, mode, open_erased);
		}
	}

	Nano::ErrorStatus open(NcDbObjectId id, NcDb::OpenMode mode, bool open_erased = false)
	{
		return NcDbObjectPointerBase< _Type >::open(id, mode, open_erased);
	}

	Nano::ErrorStatus open(const NCHAR* name, NcDbDatabase* database, NcDb::OpenMode mode, bool open_erased = false)
	{
		if (name == NULL)
			return Nano::eInvalidInput;
		else
		{
			NcDbSymbolTablePointer< _Type::TableType > table(database, NcDb::kForRead);

			Nano::ErrorStatus es = table.openStatus();

			if (es == Nano::eOk)
			{
				if (m_ptr != NULL)
					es = close();

				if (es == Nano::eOk)
				{
					es       = table->getAt(name, m_ptr, mode, open_erased);
					m_status = es;
				}
			}
			return es;
		}
	}

private:
	NcDbSymbolTableRecordPointer(NcDbSymbolTableRecordPointer& pObject);
	NcDbSymbolTableRecordPointer& operator=(NcDbSymbolTableRecordPointer& pObject);

	typedef typename _Type::TableType  T2;
};

typedef NcDbSymbolTableRecordPointer< NcDbBlockTableRecord >      NcDbBlockTableRecordPointer;
typedef NcDbSymbolTableRecordPointer< NcDbDimStyleTableRecord >   NcDbDimStyleTableRecordPointer;
typedef NcDbSymbolTableRecordPointer< NcDbLayerTableRecord >      NcDbLayerTableRecordPointer;
typedef NcDbSymbolTableRecordPointer< NcDbLinetypeTableRecord >   NcDbLinetypeTableRecordPointer;
typedef NcDbSymbolTableRecordPointer< NcDbRegAppTableRecord >     NcDbRegAppTableRecordPointer;
typedef NcDbSymbolTableRecordPointer< NcDbTextStyleTableRecord >  NcDbTextStyleTableRecordPointer;
typedef NcDbSymbolTableRecordPointer< NcDbUCSTableRecord >        NcDbUCSTableRecordPointer;
typedef NcDbSymbolTableRecordPointer< NcDbViewTableRecord >       NcDbViewTableRecordPointer;
typedef NcDbSymbolTableRecordPointer< NcDbViewportTableRecord >   NcDbViewportTableRecordPointer;

#pragma pack (pop)

