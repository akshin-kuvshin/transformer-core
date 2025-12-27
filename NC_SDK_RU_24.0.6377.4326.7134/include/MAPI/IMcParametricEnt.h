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

#include "McsTypes.h"
#include "IMcObjects.h"

//=============================================================================
#define MCPAR_PUBLIC  0x00000001
#define MCPAR_PRIVATE 0x00000002
#define MCPAR_CHANGEABLE 0x00000100
#define MCPAR_ALL (MCPAR_PUBLIC|MCPAR_PRIVATE)

//Для корректной работы со скрпитовыми объектами среди параметров должны быть определены следующие параметры
const McsString MCPAR_STD_NAME			= _T("strTheName");
const McsString MCPAR_STD_TYPE			= _T("strTheType");
const McsString MCPAR_STD_SUB_TYPE	= _T("strTheSubType");
//Эти параметры желательны для показа в дереве свойств и запроса при вставке из групп, когда у класса внутри может быть много представлений
const McsString MCPAR_OBJECT_DESC		= _T("ObjectDescription");//Локализованное общее описание объекта (например Гайка, Болт и т.п.)
const McsString MCPAR_PART_DESC			= _T("strPartDescription");//Описание для спецификации
const McsString MCPAR_PART_PARTITION =_T("SpecPartition");//Раздел спецификации
const McsString MCPAR_DESIGN_NAME		=_T("strDesignName");			//Название исполнеиня в стандартных
const McsString MCPAR_PART_MASSA		=_T("massa");

inline bool IsStdScriptParam(const McsString& st)
{
	if(st == MCPAR_STD_NAME)return true;
	if(st == MCPAR_STD_TYPE)return true;
	if(st == MCPAR_STD_SUB_TYPE)return true;
	if(st == MCPAR_OBJECT_DESC)return true;
	if(st == MCPAR_PART_DESC)return true;
	if(st == MCPAR_PART_PARTITION)return true;
	//Эти обычно нужны, поэтому кому надо их фильтровать отдельно
	//if(st == MCPAR_DESIGN_NAME)return true;
	//if(st == MCPAR_PART_MASSA)return true;
	return false;
};
//=============================================================================
struct IMcParametricEnt : public virtual IMcObject
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcParametricEnt);
	IMCS_QI_METHOD_DEFINITION(IMcParametricEnt, IMcObject);

	virtual HRESULT getParams(OUT mcsExValueArray& params, IN OPTIONAL DWORD dwFlags=MCPAR_ALL) = 0;
	virtual HRESULT setParams(IN const mcsExValueArray& params, IN OPTIONAL DWORD dwFlags=MCPAR_ALL) = 0;
	//May be implemented only for PUBLIC params
  virtual LPCTSTR getDescription(LPCTSTR name) {return name;};
};

#define IMcParEntPtr	IMcParametricEntPtr
//===========================================================================
// DESCR. Each references tree has its own UID stored in representatives IMcDbObject::m_RefGroupID member;
// But there may be some independent ref trees in single session with the same ref UID, 
// cause: copy of ref group, usage of catalog of components for STD objects and so on..
// For copies ID of objects will be substituted, but refUID is not object ID and it will not be subst.
// So here defined special RefID structure which can uniquely identify single ref tree group across documents
// during single session

struct McReferenceID
{
  GUID      RefUID;
  mcsWorkID StopNodeID;

  McReferenceID(){
    RefUID = GUID_NULL;
  }

  bool operator==(const McReferenceID& cw) const{
    if(this == &cw) return true;
    if(RefUID!=cw.RefUID) return false;
    if(StopNodeID!=cw.StopNodeID) return false;
    return true;
  }

  bool operator!=(const McReferenceID& cw) const
    {return !(*this == cw);}
};
static const McReferenceID REFID_NULL;
//===========================================================================
template <> __inline UINT __stdcall McsHashKey <const McReferenceID&> (const McReferenceID& key)
{
  UINT hash = 
    (key.StopNodeID.ID.Data1&0xFFFF0000) |
	  ((key.RefUID.Data1>>16)&0x0000FFFF);
  return hash;
};



//------------------------------------------------------------------------
// Стандартная реализация IMcReferenceItem.
// Можно использовать, если зависимость не редактируется и не удаляется
struct __declspec(uuid("57CB55F8-A02F-42cb-9B6F-F3DC325FE52D")) McReferenceItemDefault;
static const GUID CLSID_McReferenceItemDefault = __uuidof(McReferenceItemDefault);
typedef MComQIPtr<McReferenceItemDefault> McReferenceItemDefaultPtr; 
struct McReferenceItemDefault : public IMcReferenceItem
{
	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void** ppvObj) {
		if (riid == __uuidof(IMcReferenceItem)) { *ppvObj = (IMcReferenceItem*)this; AddRef(); return S_OK; }
		if (riid == __uuidof(McReferenceItemDefault)) { *ppvObj = (McReferenceItemDefault*)this; AddRef(); return S_OK; }
		return IMcReferenceItem::QueryInterface(riid, ppvObj);
	}

	// IMcObject
	virtual const GUID& getClassID() const { return __uuidof(McReferenceItemDefault); }

	// IMcReferenceItem
	virtual mcsWorkID getTarget()                                                 { return m_idTarget; }
	virtual HRESULT getTargetBounds(mcsBoundBlock& bb)                            { if (m_bbTarget.isValid()) { bb = m_bbTarget; return S_OK; } else return S_FALSE; }
	virtual int getTargetGsMarker()                                               { return m_iGsTarget; }
	virtual mcsWorkID getSource()                                                 { return m_idSource; }
	virtual HRESULT getSourceBounds(mcsBoundBlock& bb)                            { if (m_bbSource.isValid()) { bb = m_bbSource; return S_OK; } else return S_FALSE; }
	virtual int getSourceGsMarker()                                               { return m_iGsSource; }
	virtual McReferenceDirection getDirection()                                   { return m_uDirection; }
	virtual McsString getExpression()                                             { return m_msExpression; }

	// McReferenceItemDefault
	virtual HRESULT setTarget(const mcsWorkID& id)                                { m_idTarget = id; return S_OK; }
	virtual HRESULT setTargetBounds(const mcsBoundBlock& bb)                      { m_bbTarget = bb; return S_OK; }
	virtual HRESULT setTargetGsMarker(int igs)                                    { m_iGsTarget = igs; return S_OK; }
	virtual HRESULT setSource(const mcsWorkID& id)                                { m_idSource = id; return S_OK; }
	virtual HRESULT setSourceBounds(const mcsBoundBlock& bb)                      { m_bbSource = bb; return S_OK; }
	virtual HRESULT setSourceGsMarker(int igs)                                    { m_iGsSource = igs; return S_OK; }
	virtual HRESULT setDirection(McReferenceDirection dir)                        { m_uDirection = dir; return S_OK; }
	virtual HRESULT setExpression(McsString str)                                  { m_msExpression = str; return S_OK; }

	McReferenceItemDefault() : m_iGsSource(-1), m_iGsTarget(-1), m_uDirection(kMcRefDirection_Direct) {
		IMCS_REGISTER_CLASS_IID_4KINDOF(McReferenceItemDefault);
		IMCS_REGISTER_CLASS_IID_4KINDOF(IMcReferenceItem);
	}

protected:
	mcsWorkID m_idSource;
	int m_iGsSource;
	mcsBoundBlock m_bbSource;

	mcsWorkID m_idTarget;
	int m_iGsTarget;
	mcsBoundBlock m_bbTarget;

	McsString m_msExpression;
	McReferenceDirection m_uDirection;
};

//------------------------------------------------------------------------
// Объект чертежа, который может взаимодействовать с другими объектами, должен отдавать
// этот интерфейс в QueryInterface.
// Динамические ссылки в тексте полей учитывать не нужно, их обработка встроена в базовый функционал и
// не требует реализации IMcReferenceExtension
//
interface IMcReferenceExtension : public virtual IMcObject
{
  IMCS_STD_METHOD_DEFINITION(IMcReferenceExtension, IMcObject);
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcReferenceExtension);
	// Нужно заполнить массив refs, создав по одному объекту IMcReferenceHandler на каждую зависимость.
	virtual HRESULT GetReferenceItems(OUT IMcReferenceItems& refs) = 0;
};


//===========================================================================
struct IMcLinksManager : public virtual IMcObject
{
  IMCS_STD_METHOD_DEFINITION(IMcLinksManager, IMcObject);
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcLinksManager);

  // override to prevent occasional destruction
  virtual DWORD __stdcall Release() {return 1;}
  virtual DWORD __stdcall AddRef() {return 1;}

    // looks for all objects ID inside full stream record of given objects inside document
  virtual HRESULT getGroupByLinks(IN IMcDbObject* pObject, OUT mcsWorkIDArray& group, IN OPTIONAL bool f4InputObjOnly=false) = 0;

    // helper: returns RefID for object related to ref tree
  virtual McReferenceID getRefID4Object(IN IMcObject* pObj) = 0;

    // helper: returns root object for related ref tree
  virtual IMcEntityPtr getRoot4RefTree(IN IMcObject* pRefTreeNode) = 0;

    // queries all existing references of specified object inside specific doc
  virtual HRESULT getReferences4RefTreeInDoc(IN IMcObject* pObj, IN const mcsWorkID& docID, OUT mcsWorkIDArray& refs) = 0;

    // you must check parent and references groups correspondence by yourself, no internal check will be performed
  virtual HRESULT matchGroups(IN mcsWorkIDArray& parentGroup, 
                              IN mcsWorkIDArray& referenceGroup, 
                              IN bool            fParentToReference,
                              OUT mcsWId2WIdMap& mapping,
                              IN OPTIONAL const mcsWorkID& specificRefCtx = WID_NULL) = 0;

    // creates new work ref entity copy and links it to reference objects pair 
    // (but ref entity itself will nothing know about this copy)
  virtual HRESULT createRefEntCopy(IN IMcObject* pReference, OUT IMcEntityPtr& pECopy) = 0;

    // updates all available references for spec object;
    // if fForceAll is <true> then searches for all available objects in container which refers to 
    // spec root obj; otherwise filter objects by active doc tree
  virtual HRESULT updateRefTree(IN IMcObject* pRootObject, IN OPTIONAL bool fForceAll=false) = 0;

    // transmits data from work copy ref entity to root entity
  virtual HRESULT updateRootFromRefCopy(IN IMcObject* pCopy) = 0;

    // splits input object to two objects: 
    // root and it's reference;
    // keeps input ID value for new reference;
    // assigns valid refData to both;
    // transfers constraints to reference;
    // both output objects not added to any doc;
    // new reference replaces existing in container input object by itself;
    // new root object will be added to container
    // links data not corrected for root;
    // transformation for root is not changed;
    // input pRefOriginalObject on success becomes RefEntWorkCopy;
    // NOTE: method must be used by NativeGate in impl of method IMcDocument::addObject 
    // (if it is required by native platform)
  virtual HRESULT explodeReference(IN OUT IMcObject*          pRefOriginalObject, 
                                   IN OPTIONAL bool           fRecreateDB=true, // if <false> then only Entity sink will be recreated
                                   OUT OPTIONAL IMcObjectPtr* ppRoot=NULL, 
                                   OUT OPTIONAL IMcObjectPtr* ppReference=NULL) = 0;
    // updates all links (constraints: params, geom, links) for specific object
  virtual HRESULT updateLinks(IN IMcObject* pRefObj, IN bool fParentToRef) = 0;




  // ???????????????????????
    // returns completely linked groups within given doc
  virtual HRESULT getLinkedGroupsFromDocument(IN IMcDocument* pDoc, OUT McsArray<mcsWorkIDArray, const mcsWorkIDArray&>& groups) = 0;

    // reloads full stream record for given object according to reflinks adjustment map
  virtual HRESULT adjustLinks(IN OUT IMcDbObject* pDestObject, IN mcsWId2WIdMap& mapper) = 0;
};
//===========================================================================
/*
// IMcEnt-based interface to handle references;
// has its own DB sink based on IMcDbEntity (even root object implements only IMcDbObject);
// Custom implementation of this interface MUST be virtually derived from 
// CMcReferenceEntityPrototype class (see "mcSystem.h")

// terminology: 
// 'ROOT' object is 'real' object with real Entity implementation and it's placed 
// at the base of references tree;
// 'PARENT' object defines only object to which reference is attached, parent object may be 
// either reference or root.

struct IMcReferenceEntity : public virtual IMcEntity,
                            public virtual IMcParametricEnt
{
protected:
  IMcReferenceEntity() {
    IMCS_REGISTER_THIS_IID_4KINDOF;
    m__lSystemFlag |= kMcRefEnt;
  }

  virtual ~IMcReferenceEntity() {}

public:
	IMCS_ENT_METHOD_DEFINITION(IMcReferenceEntity, IMcEntity, IMcDbEntity);

    // identifies a set of all linked references of root object
  virtual McReferenceID           getRefGroupID() = 0; 
    // returns objects to which reference immediately linked
  virtual mcsWorkID               getParentID(IN OPTIONAL bool bForceForRoot=false) = 0; 
    // if <true> and root(basis) object then will return itself
  virtual mcsWorkID               getRootID(IN OPTIONAL bool bForceForRoot=false) = 0; 
    // if <true> and root(basis) object then will return itself
  virtual IMcEntityPtr            getRoot(IN OPTIONAL bool bForceForRoot=false) = 0; 
  virtual IMcDbEntityPtr          getDbRoot(IN OPTIONAL bool bForceForRoot=false) = 0;
    // traverses references three from this object to the stop root object node,
    // stop node can be either root or 1'st level reference (for some set of std objects)
  virtual HRESULT                 getRefPath(OUT mcsWorkIDArray& idRefs) = 0;

    // <0: cast value to HRESULT: value indicates error
    //  0: it's root object and it is not real reference
    //  1: this reference is actual reference of the root object,
    //  2: it's reference to reference
  virtual long                    getRefLevel() = 0;

    // transformation helpers
  virtual HRESULT                 getRefToRootTfm(OUT mcsMatrix& R2Ptfm) = 0; // reference to root
  virtual HRESULT                 getRootToRefTfm(OUT mcsMatrix& P2Rtfm) = 0; // root to reference
  virtual HRESULT                 absTransform(IN const mcsMatrix& tfmAbs) = 0; 

    // SERVICE method
    // use it to assoc parent/root object to ref after its creation (available only once);
    // input object actually my not be in container (need to more easy initialization)
  virtual HRESULT                 _setParent(IN IMcObject* pParent) = 0; 
};
*/

//////////////////////////////////////////////////////////////////////////
struct IMcCtrDriver : public virtual IMcObject
{
public:
  IMCS_STD_METHOD_DEFINITION(IMcCtrDriver, IMcObject);
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcCtrDriver);

	virtual HRESULT applyConstriants() = 0;//Применяет зависимости к объекту
	virtual HRESULT updateConstriants(bool bFull) = 0;//Вызывает обновление зависимостей от объекта
	virtual HRESULT installConstraints() = 0;	//Устанавливает в окончательное состояние зависимости кторые были в Setup фазе
	virtual HRESULT eraseSetupConstraints() = 0;//Удаляет все зависимости находящиеся в фазе Setup
	virtual HRESULT eraseAll() = 0;
	//Helpers
	//возвращает список объектов соедененных зависимостью с переменной var, ctr - тип зависимости, по умолчанию любой, 
	enum{kMcCtrDrv_From = 0x1, kMcCtrDrv_To = 0x2, kMcCtrDrv_FwdOnly = 0x1000, kMcCtrDrv_ReturnCtrsID = 0x2000, kMcCtrDrv_Any = (kMcCtrDrv_From|kMcCtrDrv_To)};
	//kMcCtrDrv_FwdOnly - этот модификатор исключает из списка обратные зависимости срабатывающие по признаку isBiDirect
	virtual HRESULT getObjectsConnectedTo(mcsWorkIDArray& ids, LPCTSTR var, int ctr = ctUndefined, int iAny = kMcCtrDrv_Any) = 0;
};

//Вобщем введеине, idTo и idFrom это условности на самом деле. но idTo считаем текущим объектом
//Т.е. в случае линка одного ко многим один - это To, много это From
//=============================================================================
struct IMcStdPartConstraint : public IMcEntity
{
public:
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcStdPartConstraint);
	IMCS_ENT_METHOD_DEFINITION(IMcStdPartConstraint, IMcEntity, IMcDbObject);
	
	enum{ 
		kMcCtr_New = 0x1,					//Зависимость только что создана или очищена
		kMcCtr_InSetup = 0x2,			//Данные установлены но применена только к одному объекты(промежуточное состояние в момент вставки объекта) 
		kMcCtr_VirtualSeted = 0x4,//Полностью установлена, но не добавлена в документ (например один из объектов пока еще не добавлен в документ)
//////////////////////////////////////////////////////////////////////////
//это еще под вопросом
		kMcCtr_SetToNative = 0x8,	//во время апдейта попытаться установить нативную зависимость
		kMcCtr_Native = 0x10,			//можно не вычислять, выполение будет идти по нативным связям
//////////////////////////////////////////////////////////////////////////
//Системные, наружу не отдаеются
		kMcCtr_Expression	=	0x20,
		kMcCtr_RemoveIt = 0x40,	//на update удалится, это для зависимостей которые зачитались и упс, оказывается умерли
		kMcCtr_Bidirect		=	0x80,
	};

	virtual int getState() = 0;

	virtual bool isEqu(IMcStdPartConstraint* pCtr) = 0;

	virtual HRESULT getObjectsFrom(mcsWorkIDArray& ids) = 0;
	virtual const mcsWorkID& getIdTo() = 0;

	virtual int getConstraintType() = 0;

	//Chek only this constraint, dont chek compatibility with other constraint on this object
	virtual bool isValid() = 0;
	
	//////////////////////////////////////////////////////////////////////////
	// if(bCanSelectPlane == true) if user want Parent will hidden and select fature on obj1 or obj2 
	// will called
	virtual IMcWindow *GetEditCtl(bool bCanSelectPlane) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual HRESULT addAsSetup() = 0; //переходит в фазу setup, добавляется в один объект
	//завершение команды такие зависимости не переживут
	virtual HRESULT install() = 0;//Переход в нормальную фазу
};
//=============================================================================

struct MCSConstraintData;
typedef McsArray<IMcStdPartConstraintPtr,  IMcStdPartConstraint*>   mcConstraintArray;

struct IMcPConstraint : public virtual IMcStdPartConstraint
{
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcPConstraint);
	IMCS_ENT_METHOD_DEFINITION(IMcPConstraint, IMcStdPartConstraint, IMcDbObject);
	//Объекты From и To это условность, To это просто вставляющийся объект
	//При двусторонней зависимости это соответсвенно инициатор установки зависимости
	virtual HRESULT setObjectTo(const mcsWorkID& id, LPCTSTR var) = 0;
		//в случае формульной зависимости от чего естественно может и не быть
	virtual HRESULT setObjectFrom(const mcsWorkID& id, LPCTSTR var = NULL) = 0;
	virtual HRESULT setConstraint(ConstraintTypeEnum iConstraintType, bool bCoDirect, bool bBiDirection, double rVal) = 0;
	//Формула задаеться в виде "obj1.a + obj2.b/2" например. 
	//Detect is the expression or constant and set constraint 
	virtual HRESULT setConstraintAsText(ConstraintTypeEnum iConstraintType, bool bCoDirect, bool bBiDirection, LPCTSTR strText) = 0;
	
	virtual HRESULT getObjectsFrom(mcsWorkIDArray& ids)
	{
		ids.RemoveAll();
		ids.Add(getIdFrom());
		return S_OK;
	};	
	virtual const mcsWorkID& getIdFrom() = 0;
	virtual LPCTSTR getVarTo() = 0;
	virtual LPCTSTR getVarFrom() = 0;

	virtual bool isExpression() = 0;
	virtual bool isCodirect() = 0;
	virtual bool isBiDirectional() = 0;
	virtual LPCTSTR getText() = 0;
	virtual double getDistance() = 0;	

	//для конверсии и использования в старых методах, автопроверка дублирования ид зависимостей
	virtual HRESULT set(MCSConstraintData& data) = 0;
	//Ограниченная функциональность, возвращает только прямую зависиомость, инвертированная не создается
	virtual HRESULT get(MCSConstraintData& data) = 0;
	//////////////////////////////////////////////////////////////////////////
	//Helpers
	virtual HRESULT transferConstraint(mcsWorkID& idTo, const mcsWorkID& idFrom) = 0;
};

struct IMcLConstraint : public virtual IMcStdPartConstraint
{
  IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcLConstraint);
	IMCS_ENT_METHOD_DEFINITION(IMcLConstraint, IMcStdPartConstraint, IMcDbObject);
	enum{	kMcLink_Simple = 0x0, 
				kMcLink_OwnerToChilds = 0x1, 
				kMcLink_OneDirection = 0x2};
	virtual HRESULT setLinkType(int iLinkType) = 0;
	virtual int getLinkType() = 0;

	virtual HRESULT setObjectTo(const mcsWorkID& id) = 0;
	virtual HRESULT setObjectsFrom(const mcsWorkIDArray& ids) = 0;
	virtual HRESULT setObjectFrom(const mcsWorkID& id) = 0;//Helper

	//Helper
	virtual HRESULT getLinks(mcsWorkIDArray& idsTo, const mcsWorkID& idThis) = 0;
};
//===========================================================================

// return:
// S_OK               - object transformed
// S_FALSE            - nothing to do
// MCS_S_NO_TRANSFORM - all ok, but can't set planes by transform, 
//                      object must handle situation by itself
MECHCTL_API HRESULT mcsSetPlanes4ParametricByTransform
(IN IMcParametricEnt*      pPE, 
 IN const mcsExValueArray& varsNew);
