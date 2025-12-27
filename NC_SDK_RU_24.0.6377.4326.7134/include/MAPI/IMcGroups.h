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
//группировка объектов
#include "IMcObjects.h"
#include "IMcStream.h"
#include "IDbAccess.h"

class CxImage;
//////////////////////////////////////////////////////////////////////////
class IMcGroupManger
{
public:
	virtual HRESULT getUniqueName(McsString& name, LPCTSTR tag, const mcsWorkID& id, const mcsWorkID& idDoc, bool bInEdit) = 0;
	virtual HRESULT parseName(LPCTSTR fullname, McsString& name, int& index) = 0;	
	virtual HRESULT getDefaultGroupPath(McsString& name) = 0;
	virtual HRESULT SetCxImageHolder(CxImage *pImage) = 0;
	virtual mcsWId2WIdMap* getLastGrMap() = 0;
};

//////////////////////////////////////////////////////////////////////////
extern "C" // force undecorated names
{
  extern MECHCTL_API IMcGroupManger	*gpMcGroupManager;
}


//////////////////////////////////////////////////////////////////////////
enum mcAttributFlags
{
	kMcFeedback				= 0x1,//обратная связь атрибута со свойством включена
	kMcNotInited			= 0x2,
	kMcUniqueInc			= 0x4,//Уникальное id на основе текста + число
	kMcFeedbackEnabled= 0x8,//свойстов не readOnly
	kMcCalculated			= 0x10,	//вычисляемый атрибут
	kMcAutoInc				= 0x20,
	kMcFeedbackBlock		= 0x40,	//Атрибут блокирующий изменение свойств, необходимое значение будет храниться в strObjectName
	kMcFeedBlock_Error	= 0x80,	//флажок устанавливаемый в атрибуте если kMcFeedbackBlock не сработал, также вываливается в нотификатор сообщение и подсвечивается текст красным
	kMcMustUpdate				= 0x100,	//Поле помечено для операции при групповой установке параметров.
	kMcIndirect				= 0x200,	//В поле устанавливаются значения из других параметров
};

#define NAME_VAL_DELIMETER _T("\nMCV")
//////////////////////////////////////////////////////////////////////////
struct McAttribut
{
	McAttribut(){
		iPropType = -1;
		lFlags = lData = 0;
	};
	McAttribut(const McAttribut& src){
		*this = src;
	}
	void reset(){//Сбрасывает значение атрибута до уровня простого поля
		iPropType = -1;
		lFlags = 0;
		idFrom.setNull();
		strObjectName.Empty();
		strPropName.Empty();
	}
	bool canBeIndirect(){
		return !(lFlags & (kMcUniqueInc|kMcAutoInc));
	}
	bool usePropName(){
		return !idFrom.IsNull()/* || canBeIndirect()*/;
	}
	McsString strName, strTag, strValue;
	mcsWorkID idFrom;			//ID объекта с которого взято свойство.
	McsString strPropName, strObjectName;//в strObjectName для присоединяемых полей лежит имя обекта для Promt, в остальных случаях по разному
	int iPropType;			//тип свойства (mcPropObject и т.п.)
	long lData, lFlags;//в lFlags лежат mcAttributFlags, в lData GS Marker
	McsString getObjectName(){
		McsString strName;
		int iIndex = strObjectName.Find(NAME_VAL_DELIMETER);
		if(iIndex >= 0)
			strName = strObjectName.Left(iIndex);
		else
			strName = strObjectName;
		return strName;
	}
	void setObjectName(LPCTSTR name){
		McsString strVal = getStoredValue();
		strObjectName = name;
		strObjectName += NAME_VAL_DELIMETER;
		strObjectName += strVal;
	}
	McsString getStoredValue(){
		McsString strVal;
		int iIndex = strObjectName.Find(NAME_VAL_DELIMETER);
		if(iIndex >=0 ){
			strVal = strObjectName.Right(strObjectName.GetLength()-iIndex-4);
		}
		return strVal;
	}
	void setStoredValue(LPCTSTR value){
		strObjectName = getObjectName();
		strObjectName += NAME_VAL_DELIMETER;
		strObjectName += value;
	}
	McAttribut& operator=(const McAttribut& src){
		if(this == &src) return *this;
		lFlags = src.lFlags;
		strName = src.strName;
		strTag = src.strTag;
		strValue = src.strValue;
		idFrom = src.idFrom;
		iPropType = src.iPropType;
		strPropName = src.strPropName;
		strObjectName = src.strObjectName;
		lData = src.lData;
		return *this;
	}
};

//////////////////////////////////////////////////////////////////////////
class mcsAttributArray : public McsArray<McAttribut, McAttribut&> 
{
public:
	bool findByName(OUT int& iIndex,IN LPCTSTR name){
	  MCSASSERT(name);
		iIndex = -1;
    for(int i=m_nSize-1; i>=0; i--) {
			if(m_pData[i].strName == name){
				iIndex = i;
				return true;
			}
    }
		return false;
	}
	bool findByTag(OUT int& iIndex,IN LPCTSTR name){
	  MCSASSERT(name);
		iIndex = -1;
    for(int i=m_nSize-1; i>=0; i--) {
			if(m_pData[i].strTag == name){
				iIndex = i;
				return true;
			}
    }
		return false;
	}
	bool findByGsMarker(OUT int& iIndex,IN int iGsMarker){
		iIndex = -1;
    for(int i=m_nSize-1; i>=0; i--) {
			if(m_pData[i].lData == iGsMarker){
				iIndex = i;
				return true;
			}
    }
		return false;
	}
	bool getIdsFrom(mcsWorkIDArray& ids){
		bool bRet = false;
    for(int i=m_nSize-1; i>=0; i--) {
			if(!m_pData[i].idFrom.IsNull() ){
				ids.AddDistinct(m_pData[i].idFrom);
				bRet = true;
			}
    }
		return bRet;
	}
	//////////////////////////////////////////////////////////////////////////
	//директива экспорта не написана потому что ненадо это никому, если надо будет то впишу
	bool updateCalcField();
	bool updateUniqueNames(const mcsWorkID& objId, const mcsWorkID& docId, bool bInEdit);
	bool updateAutoInc(bool bFirstTime = false);
	bool setParamToPaser();
	bool updateFeedBlocks();//Оптом обновляет поля с признаками FeedBlock
	bool setPresetValues(long lParamkod, IDBTable* pTable);//Установка preseta целиком
};

#define MARKER_TYPE_TAG	_T("MarkerType")
#define MCS_GROUP_NAME_TAG	_T("Group Name")
//////////////////////////////////////////////////////////////////////////
//Универсальный маркер
struct IMcUMarker : public IMcEntity
{
public:
	IMCS_ENT_METHOD_DEFINITION(IMcUMarker, IMcEntity, IMcDbEntity); 
	virtual HRESULT init(MCSUID uid) = 0; // from db
	virtual MCSUID getUID() = 0;
	virtual HRESULT createNewMarker() = 0;
	virtual HRESULT initMaker(LPCTSTR szMarkerType) = 0;
	virtual HRESULT addTag(LPCTSTR szTag, LPCTSTR szDesc, bool bCreateText) = 0;
	virtual HRESULT setFeedBackAtribute(LPCTSTR szTag, const mcsWorkID& id, LPCTSTR szProp, int iPtyType, int iFeedType) = 0;
	virtual HRESULT removeTag(LPCTSTR szTag) = 0;
	virtual HRESULT highLightObjects(bool bHighlight, COLORREF color = MCS_ENTCOLOR_BYDEFAULT) = 0;
	virtual const mcsAttributArray& getAtributesStore() = 0;
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcUMarker);
};


struct CMcGroupReflecton 
{
	mcsWorkIDArray idsWorkID;//группа связанных объектов
	mcsStringArray aIncludedParams;
	mcsIntArray aiParamTypes;
	CLSID id;
	HRESULT getParamsByType(mcsStringArray& aNames, int iPtyType)	{
		aNames.RemoveAll();
		for(int i = 0; i < aIncludedParams.GetSize(); i++){
			if(aiParamTypes[i] == iPtyType){
				aNames.Add(aIncludedParams[i]);
			}
		}
		return S_OK;
	}
	HRESULT addDistinct(McsString stName, int iPtyType){
		for(int i = 0; i < aIncludedParams.GetSize(); i++){
			if(stName == aIncludedParams[i] && aiParamTypes[i] == iPtyType){
				return S_FALSE;
			}
		}
		aIncludedParams.Add(stName);
		aiParamTypes.Add(iPtyType);
		return S_OK;
	}
	HRESULT remove(McsString stName, int iPtyType){
		for(int i = 0; i < aIncludedParams.GetSize(); i++){
			if(stName == aIncludedParams[i] && aiParamTypes[i] == iPtyType){
				aIncludedParams.removeAt(i);
				aiParamTypes.removeAt(i);
				return S_OK;
			}
		}
		return S_FALSE;
	}
	bool contains(McsString stName, int iPtyType){
		for(int i = 0; i < aIncludedParams.GetSize(); i++){
			if(stName == aIncludedParams[i] && aiParamTypes[i] == iPtyType){
				return true;
			}
		}
		return false;
	}
protected:
	HRESULT onWrite(OUT IMcsStream* pStream) const;
	HRESULT onRead(IN IMcsStream* pStream);
	friend class CMcGroup;
};
#define kMcPlaceCustom_Virtual 0x100000//не добавлять в документ (используется для опреации с группами обектов)
//////////////////////////////////////////////////////////////////////////
struct IMcGroup : public virtual IMcUMarker
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcGroup);
	IMCS_ENT_METHOD_DEFINITION(IMcGroup, IMcUMarker, IMcDbEntity);

	virtual LPCTSTR groupName() = 0;

	virtual HRESULT saveGroup(IMcsStream *pStream) = 0;
	virtual HRESULT saveGroup(IDBElement* pElement, CxImage* pImage = NULL, bool bOutAuto = true) = 0;
	virtual HRESULT init(IDBElement* pElement) = 0;
	virtual HRESULT init(MCSUID uid) = 0;
	virtual HRESULT loadGroup(IMcsStream *pStream) = 0;
	virtual HRESULT createGroup(LPCTSTR name = NULL) = 0;
	virtual HRESULT initGroupAttributes(LPCTSTR name) = 0;

	virtual HRESULT transformGroup(const mcsMatrix& tfm, bool bUpdateNow = false) = 0;
	virtual HRESULT copyGroup(IMcGroupPtr& ptr) = 0;

	enum {leftBottom, leftTop, center, rightTop, rightBottom, custom, getCurentPosition};
	virtual HRESULT setInsPoint(int iPntType, mcsPoint pnt = mcsPoint()) = 0;
	virtual HRESULT claculateInsPoint(mcsPoint& pnt, int iPntType = -1) = 0;//-1 - initiated value

	virtual HRESULT setObjects(const mcsWorkIDArray& ids) = 0;
	virtual HRESULT getObjects(mcsWorkIDArray& ids) = 0;
	virtual HRESULT removeObjects(const mcsWorkIDArray& ids) = 0;//удалять объекты лучше через этот метод, будут сниматся реакторы если были
//////////////////////////////////////////////////////////////////////////
// for GroupReflection
	virtual HRESULT getOriginalGroup(mcsWorkIDArray& ids) = 0; 
	virtual HRESULT addGroupReflectionRow(const mcsWorkIDArray& ids, bool bSetReactors = true) = 0; 
	//idsOriginal.GetSize==0 - может быть для пустой группы или если на объекты уже бывшие в группе связть не устанавливается
	virtual HRESULT addGroupReflectionCol(const mcsWorkIDArray& ids, const mcsWorkIDArray& idsOrigignal, bool bSetReactors = true) = 0; 

	virtual long getRowsCount() = 0;
	virtual HRESULT getReflectionRow(CMcGroupReflecton& Row, int iRow) = 0;
	virtual HRESULT setReflectionRow(CMcGroupReflecton& Row, int iRow) = 0;
	virtual HRESULT showPtyFilterDlg(HWND hwnd) = 0;
	//if S_OK объектв этой группе,  Type == 1 - in reflection, 0 - simple
	virtual HRESULT objectInGroup(const mcsWorkID& id, int& iType) = 0;
};



