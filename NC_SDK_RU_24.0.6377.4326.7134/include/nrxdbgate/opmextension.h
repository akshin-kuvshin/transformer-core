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
#if !defined(HOST_IN_QT)
#include "nrxdbgate_impexp.h"

interface IPropertyManager;
interface IDynamicProperty;
interface IPropertySource;

class NRXDBGATE_EXPORT OPMPropertyExtension : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(OPMPropertyExtension);

	OPMPropertyExtension(OdRxObject* object);
	virtual ~OPMPropertyExtension(){}

	virtual IPropertyManager* GetPropertyManager() = 0;
	virtual void SetPropertyManager(IPropertyManager* pPropManager) = 0;
};


class NRXDBGATE_EXPORT OPMPropertyExtensionFactory: public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(OPMPropertyExtensionFactory);

	OPMPropertyExtensionFactory(OdRxObject* object);
	virtual ~OPMPropertyExtensionFactory(){}

	virtual OPMPropertyExtension* CreateOPMObjectProtocol(NcRxClass* pClass, LONG lReserved = NULL) = 0;
	virtual OPMPropertyExtension* CreateOPMCommandProtocol(const NCHAR * pGlobalCommand, LONG lReserved = NULL) = 0;

	virtual BOOL GetOPMManager(const NCHAR * pGlobalCommand, IPropertyManager** pManager) = 0;
	virtual BOOL GetPropertyCount(NcRxClass* pClass, LONG* pPropCount) = 0;
	virtual LONG GetPropertyClassArray(NcRxClass* pClass, IDynamicProperty**  pPropertyArray) = 0;
	virtual BOOL GetPropertyCountEx(NcRxClass* pClass, LONG* pPropCount) = 0;
	virtual LONG GetPropertyClassArray(NcRxClass* pClass, IUnknown**  pPropertyArray) = 0;
};

//////////////////////////////////////////////////////////////////////////
// OPMPerInstancePropertySources
class NRXDBGATE_EXPORT OPMPerInstancePropertySources : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(OPMPerInstancePropertySources);

	OPMPerInstancePropertySources(OdRxObject* object);
	virtual ~OPMPerInstancePropertySources(){};

	virtual bool SetPropertySourceAt(const BSTR* pName, IPropertySource* pSource) = 0;
	virtual IPropertySource* GetPropertySourceAt(const BSTR* pName) = 0;
	virtual bool RemovePropertySourceAt(const BSTR* pName) = 0;
	virtual bool GetPropertySourceNames(VARIANT* pNames) = 0;
};

//////////////////////////////////////////////////////////////////////////
// OPMPerInstancePropertyExtension
class NRXDBGATE_EXPORT OPMPerInstancePropertyExtension : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(OPMPerInstancePropertyExtension);
  
	OPMPerInstancePropertyExtension(OdRxObject* object);
	virtual ~OPMPerInstancePropertyExtension() {};
	
	virtual bool AddObjectPropertySourceName(const BSTR* pName) = 0;
	virtual bool RemoveObjectPropertySourceName(const BSTR* pName) = 0;
	virtual bool GetObjectPropertySourceNames(VARIANT* pNames) = 0;
};

//////////////////////////////////////////////////////////////////////////
// OPMPerInstancePropertyExtensionFactory
class NRXDBGATE_EXPORT OPMPerInstancePropertyExtensionFactory : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(OPMPerInstancePropertyExtensionFactory);
  
	OPMPerInstancePropertyExtensionFactory(OdRxObject* object);
	virtual ~OPMPerInstancePropertyExtensionFactory(){};
	
	virtual OPMPerInstancePropertyExtension* CreateOPMPerInstancePropertyExtension(NcRxClass* pClass) = 0;
};

#define GET_OPMEXTENSION_CREATE_PROTOCOL() \
	((OPMPropertyExtensionFactory*)(NcDbDatabase::desc()->queryX(OPMPropertyExtensionFactory::desc())))

#define GET_OPMPROPERTY_MANAGER(pNcRxClass) \
	(GET_OPMEXTENSION_CREATE_PROTOCOL()->CreateOPMObjectProtocol(pNcRxClass)->GetPropertyManager())

#define GET_OPM_COMMAND_PROPERTY_MANAGER(pCommandName) \
	(GET_OPMEXTENSION_CREATE_PROTOCOL()->CreateOPMCommandProtocol(pCommandName)->GetPropertyManager())

#define GET_OPM_PERINSTANCE_CREATE_PROTOCOL() \
  ((OPMPerInstancePropertyExtensionFactory*)(NcDbDatabase::desc()->queryX(OPMPerInstancePropertyExtensionFactory::desc())))

#define GET_OPM_PERINSTANCE_PROPERTY_SOURCES() \
  ((OPMPerInstancePropertySources*)(NcDbDatabase::desc()->queryX(OPMPerInstancePropertySources::desc())))

#define GET_OPM_PERINSTANCE_EXTENSION_PROTOCOL(pNcRxClass) \
  (GET_OPM_PERINSTANCE_CREATE_PROTOCOL()->CreateOPMPerInstancePropertyExtension(pNcRxClass))
#endif