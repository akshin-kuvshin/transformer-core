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

#include <memory>

// AGL: не подключать! ломается сборка Нанокада в CSDev
//#include "IMcObjects.h"

class Mc2dCtrsKeeper
{
public:
	enum Mode
	{
		ePassive = 0,
		eActive  = 1,
	};

	Mc2dCtrsKeeper(Mode mode = eActive)
	{
		if(HMODULE _hMcGate = GetModuleHandleA("mcDDGate3.dll"))
			if(FARPROC pfStart = GetProcAddress(_hMcGate, "mcsStartGeomModTracking"))
				( (void(*)(Mode)) pfStart) (mode);
	}

	~Mc2dCtrsKeeper()
	{
		if(HMODULE _hMcGate = GetModuleHandleA("mcDDGate3.dll"))
			if(FARPROC pfStop = GetProcAddress(_hMcGate, "mcsStopGeomModTracking"))
				pfStop();
	}

#if defined(TD_VERSION_DEFINED) || _TEIGHA == 1
	static void TrackObjectChanges(OdDbEntity* pEnt)
	{
		if(HMODULE _hMcGate = GetModuleHandleA("mcDDGate3.dll"))
			if(FARPROC pfTrack = GetProcAddress(_hMcGate, "mcsTrackGeomMod"))
				( (void(*)(OdDbEntity*)) pfTrack) (pEnt);
	}
#endif
};
//==================================================================================================

#if defined(TD_VERSION_DEFINED) || _TEIGHA == 1

//==================================================================================================

inline HRESULT McExplodeAllObjects(OdDbDatabase* pDb, bool isSilent)
{
	FARPROC pProc = GetProcAddress(GetModuleHandleA("mcDDGate3.dll"), "McExplodeAll");
	if(pProc)
		return ((HRESULT(*)(OdDbDatabase*, bool))pProc)(pDb, isSilent);
	return E_FAIL;
}

//==================================================================================================

struct McPropertyInfo;
#include "MCSVariant.h"

class MC_NANO_GATE_API McRxObjectExtension : public OdRxObject
{
public:
	ODRX_DECLARE_MEMBERS(McRxObjectExtension);

	McRxObjectExtension()
	{}
	virtual ~McRxObjectExtension()
	{}

	// Привязка к объектам
	virtual OdResult getPointAtParam(OdDbEntity* pEnt, double rParam, __int64 iData, OdGePoint3d& pnt) const
		{ return eNotApplicable; }
	virtual OdResult getParamAtPoint(OdDbEntity* pEnt, const OdGePoint3d& pnt, double& rParam, __int64& iData) const
		{ return eNotApplicable; }
	// Перекрытия
	virtual bool canCovering(OdDbEntity* pEnt) const
		{ return false; }
	virtual bool getCrossed(OdDbEntity* pEnt, OdDbObjectIdArray& ids) const
		{ return false; }
	virtual bool setCrossed(OdDbEntity* pEnt, const OdDbObjectIdArray& ids)
		{ return false; }
	// Управление масштабом
	virtual bool isScalable(OdDbEntity* pEnt)
		{ return false; }
	virtual double getScale(OdDbEntity* pEnt)
		{ return 1; }
	virtual void setScale(OdDbEntity* pEnt, double rScale)
		{}
	// Пользовательские свойства
	virtual HRESULT getProperties(OdDbEntity* pEnt, mcsStringArray& props)
		{ props.RemoveAll(); return E_NOTIMPL; }
	virtual HRESULT getProperty(OdDbEntity* pEnt, const McsString& stName, MCSVariant& data)
		{ data.SetType(MCSVariant::kUndefined); return E_NOTIMPL; }
	virtual HRESULT setProperty(OdDbEntity* pEnt, const McsString& stName, const MCSVariant& data)
		{ return E_NOTIMPL; }
	virtual HRESULT getPropertyInfo(OdDbEntity* pEnt, const McsString& stName, McPropertyInfo& info)
		{ return E_NOTIMPL; }
	virtual bool hasProperties(OdDbEntity* pEnt)
		{ return false; }
};
typedef OdSmartPtr<McRxObjectExtension> McRxObjectExtensionPtr;
//==================================================================================================

#elif defined(AD_ACDB_H) || defined(BCAD_APP) || defined(_ZCDB_H) // #if defined(TD_VERSION_DEFINED) || _TEIGHA == 1

//==================================================================================================

class
#if defined(BCAD_APP) && defined(MODULE_MCSACADGATE)
__declspec(dllexport)
#endif
__declspec(novtable) McRxObjectExtension : public AcRxObject
{
public:
	ACRX_DECLARE_MEMBERS(McRxObjectExtension);

	// Привязка к объектам
	virtual Acad::ErrorStatus getPointAtParam(AcDbEntity* pEnt, double rParam, __int64 iData, AcGePoint3d& pnt) const
		{ return Acad::eNotApplicable; }
	virtual Acad::ErrorStatus getParamAtPoint(AcDbEntity* pEnt, const AcGePoint3d& pnt, double& rParam, __int64& iData) const
		{ return Acad::eNotApplicable; }
	// Перекрытия
	virtual bool canCovering(AcDbEntity* pEnt) const
		{ return false; }
	virtual bool getCrossed(AcDbEntity* pEnt, AcDbObjectIdArray& ids) const
		{ return false; }
	virtual bool setCrossed(AcDbEntity* pEnt, const AcDbObjectIdArray& ids)
		{ return false; }
	// Управление масштабом
	virtual bool isScalable(AcDbEntity* pEnt)
		{ return false; }
	virtual double getScale(AcDbEntity* pEnt)
		{ return 1; }
	virtual void setScale(AcDbEntity* pEnt, double rScale)
		{}
	// Пользовательские свойства
	virtual HRESULT getProperties(AcDbEntity* pEnt, mcsStringArray& props)
		{ props.RemoveAll(); return E_NOTIMPL; }
	virtual HRESULT getProperty(AcDbEntity* pEnt, const McsString& stName, MCSVariant& data)
		{ data.SetType(MCSVariant::kUndefined); return E_NOTIMPL; }
	virtual HRESULT setProperty(AcDbEntity* pEnt, const McsString& stName, const MCSVariant& data)
		{ return E_NOTIMPL; }
	virtual HRESULT getPropertyInfo(AcDbEntity* pEnt, const McsString& stName, McPropertyInfo& info)
		{ return E_NOTIMPL; }
	virtual bool hasProperties(AcDbEntity* pEnt)
		{ return false; }
};

//==================================================================================================

#endif // #if defined(TD_VERSION_DEFINED) || _TEIGHA == 1