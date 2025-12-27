
#pragma once

//---------------------------------------------------------------------------
#undef safeDDCallEx
#undef safeDDCall
#define safeDDCallEx(es, func)\
{\
	try\
	{\
		func;\
		es = eOk;\
	}\
	catch(OdError e)\
	{\
		es = e.code();\
		ERRMSG_A(McsStringA(#func) + " - " + McsStringA(e.description()));\
	}\
	catch(...)\
	{\
		es = eInvalidContext;\
		ERRMSG_A(McsStringA(#func) + " - Unknown exception");\
	}\
}
#define safeDDCall(func) safeDDCallEx(es, func)
#define safeDDResCallEx(es, func)\
{\
	try\
	{\
		es = func;\
	}\
	catch(OdError e)\
	{\
		es = e.code();\
		ERRMSG_A(McsStringA(#func) + " - " + McsStringA(e.description()));\
	}\
}
#define safeDDResCall(func) safeDDResCallEx(es, func)

#ifndef _DEBUG

typedef OdDbObjectId OdDbSafeObjectId;
#define  ODSTUB(safeId) ((OdDbStub*)(safeId))

#else

#define  ODSTUB(safeId) ((safeId).stub())

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// OdDbSafeObjectId
//---------------------------------------------------------------------------
class OdDbSafeObjectId
{
public:
	OdDbSafeObjectId()
		{}
	OdDbSafeObjectId(OdDbStub* objectId)
		{ m_id = objectId; }
	OdDbSafeObjectId(const OdDbObjectId& objectId)
		{ m_id = objectId; }

	static const OdDbSafeObjectId kNull;

	bool isNull() const
		{ return m_id.isNull(); }
	void setNull()
		{ m_id.setNull(); }

	bool isValid() const
	{
		// AGL: внутри checkValidity() выполняется проверка m_id.isValid()
		return checkValidity();
		//return m_id.isValid();
	}

	OdDbSafeObjectId& operator =(const OdDbSafeObjectId& objectId)
		{ m_id = objectId.m_id; return *this; }
	OdDbSafeObjectId& operator =(const OdDbObjectId& objectId)
		{ m_id = objectId; return *this; }

	bool operator <(const OdDbSafeObjectId& objectId) const;
	bool operator >(const OdDbSafeObjectId& objectId) const;
	bool operator >=(const OdDbSafeObjectId& objectId) const;
	bool operator <=(const OdDbSafeObjectId& objectId) const;
	bool operator ==(const OdDbSafeObjectId& objectId) const
	{
		if(!checkValidity() || !objectId.checkValidity())
			return (OdDbStub*)((OdDbSafeObjectId*)this)->m_id == (OdDbStub*)((OdDbSafeObjectId&)objectId).m_id;
		try
		{
			return m_id == objectId.m_id;
		}
		catch(...)
		{
			MESSAGE_ERR_A("OdDbObjectId compare failed");
			MCSASSERTE("Invalid OdDbObjectId");
			return false;
		}
	}
	bool operator !=(const OdDbSafeObjectId& objectId) const
	{
		return !(*this == objectId);
	}
	bool operator !() const
		{ return isNull(); }

	inline operator OdDbObjectId&()
		{ return m_id; }
	inline operator const OdDbObjectId&() const
		{ return m_id; }
	inline operator const OdDbHardPointerId() const
		{ return m_id; }

	OdDbDatabase* database() const
	{
		if(!checkValidity())
			return NULL;
		try
		{
			return m_id.database();
		}
		catch(...)
		{
			MESSAGE_ERR_A("Invalid OdDbObjectId");
			MCSASSERTE("Invalid OdDbObjectId");
			return NULL;
		}
	}
	OdDbDatabase* originalDatabase() const
	{
		if(!checkValidity())
			return NULL;
		try
		{
			return m_id.originalDatabase();
		}
		catch(...)
		{
			MESSAGE_ERR_A("Invalid OdDbObjectId");
			MCSASSERTE("Invalid OdDbObjectId");
			return NULL;
		}
	}
	void convertToRedirectedId();

	bool isErased() const {
		if(!checkValidity())
			return true;
		return m_id.isErased();
	}

	bool isEffectivelyErased() const;
	bool objectLeftOnDisk() const;
	const OdDbHandle& getHandle() const
	{
		static OdDbHandle nullHandle;
		if(!checkValidity())
			return nullHandle;
		return m_id.getHandle();
	}
	const OdDbHandle& getNonForwardedHandle() const;
	OdResult openObject(OdDbObjectPtr& pObj, OdDb::OpenMode openMode = OdDb::kForRead, bool openErasedOne = false) const;
	OdDbObjectPtr openObject(OdDb::OpenMode openMode = OdDb::kForRead, bool openErasedOne = false) const
	{
		OdDbObjectPtr pObj;
		if(!checkValidity())
			return pObj;
		OdResult es = eOk;
		safeDDCall(pObj = m_id.openObject(openMode, openErasedOne));
		if(es == eWasOpenForWrite || es == eWasOpenForRead || es == eWasOpenForNotify)
		{
			MESSAGE_ERR(L"Attempting to open an already open object.");
			MCSASSERTE(es == eWasOpenForWrite || es == eWasOpenForRead || es == eWasOpenForNotify);
		}
		return pObj;
	}
	void bindObject(OdDbObject* pObj);

	OdRxClass* objectClass() const
	{
		if(checkValidity())
			return m_id.objectClass();
		return NULL;
	}

	OdDbStub* stub() const
	{
		return (OdDbStub*)m_id;
	}

protected:
	bool checkValidity() const
	{
#if 0
		if(m_id.isNull())
			return true;
		try
		{
			return m_id.isValid();
		}
		catch(...)
		{
			return false;
		}
#else
		//YAL: more complex way:
		//m_id.isValid() иногда возвращяет true даже если объект был удалён - там просто проверка на нулевой пойнтер.
		//Я нашёл единственный способ - это OdDbDatabase* originalDatabase () const; оно сейчас возвращяет пойнтер минуя все проверки.
		//пойнтер находится довольно далеко и в случае если область памяти была разрушена, а потом кем-то занята попасть туда же сложно!
		if(m_id.isNull())
			return true;
		try
		{
			//--- *ptest - vtable
			OdDbStub *ptest1 = m_id;
			if(::IsBadReadPtr(ptest1, sizeof(PVOID)))
			{
				MESSAGE_ERR_A("Invalid OdDbObjectId");
				MCSASSERTE("Invalid OdDbObjectId");
				return false;
			}
			FARPROC **ptest2 = (FARPROC**)m_id.originalDatabase();
			if(!ptest2)
				return true;
			if(::IsBadReadPtr(ptest2, sizeof(PVOID)) || ::IsBadCodePtr((FARPROC)(*ptest2)))
			{
				MESSAGE_ERR_A("Invalid OdDbObjectId");
				MCSASSERTE("Invalid OdDbObjectId");
				return false;
			}
			return m_id.isValid();
		}
		catch(...)
		{
			MESSAGE_ERR_A("Invalid OdDbObjectId");
			MCSASSERTE("Invalid OdDbObjectId");
			return false;
		}
#endif
	}
	OdDbObjectId m_id;
};

//---------------------------------------------------------------------------
template <> __inline UINT McsHashKey <const OdDbSafeObjectId&>(const OdDbSafeObjectId& key)
{
	__int64 addr = (__int64)(void*)(OdDbStub*)(const OdDbObjectId&)key;
	addr >>= 3; // suppress alignment, gives better hash value
	return McsHashKey<__int64>(addr);
}

#endif

typedef McsArray<OdDbSafeObjectId, const OdDbSafeObjectId&> OdDbSafeObjectIdArray;
