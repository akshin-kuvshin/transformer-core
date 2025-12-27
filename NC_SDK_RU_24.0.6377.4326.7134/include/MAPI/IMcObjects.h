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

#include "MCSTypes.h"
#include "MCSGeometry.h"
#include "MCSVariant.h"
#include "IMcErrors.h"
#include "McAPIs.h"
#include "McsUtils.h"
#include "IMtStream.h"
#include "imccutter.h"
#include "SubentData.h"

#ifndef MFC_DEBUG

#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#define NDEBUG
#endif

#endif//#ifndef MFC_DEBUG

#include <memory>

#ifndef MFC_DEBUG

#ifdef _DEBUG_WAS_DEFINED
#undef NDEBUG
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

#endif//#ifndef MFC_DEBUG

class mcsExValueArray;

//===========================================================================

// Тип требуемой сети 2D-зависимостей
enum McCtrs2dNetType
{
	kMc2dCtrNet_Auto = 0, // определить автоматически по контексту
	kMc2dCtrNet_ACAD,      // ACAD_ASSOCNETWORK, Используется в 2D-зависимостях на простой геометрии, в дин. блоках
	kMc2dCtrNet_MCS,       // NCAD_ASSOCNETWORK, Используется в MCS-параметрическом 3D
	kMc2dCtrNet_Sketch,    // Зависимости планарного эскиза по схеме без DbAssoc-объектов
};
//===========================================================================

IMCS_DECL_INTERFACE(IMcPlacer, "{C364A34E-A7B6-4A81-A79C-1F4D10277AA1}");
interface IMcPlacer : public virtual IMcObject
{
	virtual int MarkObject(const mcsWorkID &target, const McsArray<__int64> &templateIds, mcsWorkIDArray &markers) = 0;
};

//===========================================================================
//объекты поддерживающие данный интерфейс будут автоматически проверятся и освобождатся в конце сессии, 
struct IMcAutoFree : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcAutoFree);
	IMCS_QI_METHOD_DEFINITION(IMcAutoFree, IMcObject);
	virtual HRESULT canFree(){return S_OK;};
};

//===========================================================================
struct IMcWizSymbol : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcWizSymbol);
	IMCS_QI_METHOD_DEFINITION(IMcWizSymbol, IMcObject);

	virtual HRESULT getDataString(McsString& str) = 0;//for stream or any other initializtion
	virtual HRESULT setDataString(LPCTSTR str) = 0;
/*
	предпологаемый (упрощенный) код для getDataString
	IMcEntityPtr pEnt = this;
	if(pEnt){
		IMcStreamPtr pStream;
		mcsCreateStream(pStream);
		pStream->raiseVersionAlert();
		pEnt->onWrite(pStream);
		pStream->saveToString(str,true);
	}
	для set соответственно обратный
	*/

	virtual HRESULT getPoints(mcsPoint3dArray& points) = 0;
	virtual HRESULT setPoints(const mcsPoint3dArray& points) = 0;

//Имена переменных должны быть в {} (это вводит юзер)
	virtual HRESULT getVariables(mcsStringArray& strings) = 0;
	virtual HRESULT setVariables(mcsStringArray& strings) = 0;

	virtual WORD version() = 0;
	virtual HRESULT checkVersion(WORD ver) = 0;
//Формат итоговой команды:
//USymbol(Version, "GUID", Scale, Standard, STRDATA, "строка даты", VALUES, str1,...,strN, POINTS, pnt1, ...,pntN);
};
//===========================================================================

MCTYP_API bool _QI_RCL_contains(const void* ptr, REFIID riid, UINT_PTR callerID);
MCTYP_API bool _QI_RCL_add(const void* ptr, REFIID riid, UINT_PTR callerID);
MCTYP_API bool _QI_RCL_remove(const void* ptr, REFIID riid, UINT_PTR callerID);

//===========================================================================
#define MCS_QI_RCL_START(hres, p, riid) \
	if(0 == ((p)->m__dwLockMask & MC_LOCK_QI)) \
	{ \
		(p)->m__dwLockMask |= MC_LOCK_QI; \
		try { do {
	
/*
// _qi_rcl_id must be static  !!! 
// because every entry to the same function will give different address on the stack
#define MCS_QI_RCL_START(hres,p,riid) \
{ \
	static UINT_PTR _qi_rcl_id=0; \
	(hres)=E_NOINTERFACE; \
	if(!_QI_RCL_contains((const void*)(p), riid, (UINT_PTR)&_qi_rcl_id)) \
	{ \
		_QI_RCL_add((const void*)(p), riid, (UINT_PTR)&_qi_rcl_id); \
		try{do{
*/
//===========================================================================
#define MCS_QI_RCL_END(hres, p, riid) \
		} while(0); } catch (...) { (hres) = E_UNEXPECTED;} \
		(p)->m__dwLockMask &= ~MC_LOCK_QI; \
	}

/*
#define MCS_QI_RCL_END(hres,p,riid) \
		}while(0);}catch(...){(hres)=E_UNEXPECTED;} \
		_QI_RCL_remove((const void*)(p), riid, (UINT_PTR)&_qi_rcl_id); \
	} \
}
*/
//===========================================================================
#define IMCS_SYSTEM_IMPLEMENTATION\
	virtual const GUID&      getClassID() const {return IID_IMcEntity;}\
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj){\
		*ppvobj = NULL;\
		if(S_OK==IMcObject::QueryInterface(riid, ppvobj))\
			return S_OK;\
		if(riid == IID_IMcEntity)\
			{*ppvobj=(IMcEntity*)this;	AddRef();	return S_OK;}\
		if(m_pSink.p && 0 == (m_pSink.p->m__dwLockMask & MC_LOCK_QI)) \
		{ \
			HRESULT hres=E_NOINTERFACE; \
			MCS_QI_RCL_START(hres, this, riid); \
			{ \
				hres=m_pSink.p->QueryInterface(riid, ppvobj);\
			} \
			MCS_QI_RCL_END(hres, this, riid); \
			if(S_OK == hres) \
				 return S_OK; \
		}\
		return E_NOINTERFACE; \
	}\
	virtual const GUID&  getImplementID() {return IID_IMcDbEntity;}\
	virtual const mcsWorkID& ID() const {if(m_pSink) return m_pSink->ID(); else return WID_NULL;}

//==============================================================================
enum mcsDbStatus
{
	MCS_DB_CHANGED              = 0x00000001,
	MCS_DB_UNDO_SAVED           = 0x00000002,
	MCS_DB_ERASED               = 0x00000004,
	MCS_DB_HIGHLIGHTED          = 0x00000010,
	MCS_DB_IN_EDIT              = 0x00000020,
	MCS_DB_3D_DOC               = 0x00000040,
	MCS_REBUILD_BOUND           = 0x00000100,
	MCS_DB_READONLY             = 0x00000200, // full copy from DB object and virtual copy of referenced object
	MCS_DB_IN_REF_TREE_UPDATE   = 0x00000800, // on if reftree is updating from DB::update, used to prevent recursive updates for references with active WCR
	MCS_DB_CUSTOM_PROP_CHANGED  = 0x00001000, // if mcPropCustom id Changed, for Optimizing undo save
	MCS_DB_NECESSARY_OBJ        = 0x00002000, // Объект используется. (для обработки в функции freeUnused, там же подробное описание)
	MCS_DB_EXT_FILE_INCAPSULATE = 0x00004000, // в случае сохранения/восст. объекта, который описывается внешним файлом хранить только файл внутри независимого стрима
	MCS_DB_EX_INDEPENDENT       = 0x00008000, // сохранять/зачитывать расширенный независимый стрим, нужно для сохранения/восст. тел в группах в независимый стрим
	MCS_DB_REACTORS_MODIFIED    = 0x00010000, // список реакторов изменился
	MCS_DB_IN_UPDATE            = 0x00020000, // взведён, если объект обновляется непосредственно в данный момент
	MCS_DB_FORCE_UPDATE         = 0x00040000, // взведён, если объекту требуется обновление, даже если он не имеет статуса changed, используется для обновления в связках родитель-дочерние
	MCS_DB_BLOCK_MENU_EDIT      = 0x00080000, // Убирает пункт "Редактирование" из контекстного меню объекта.
	MCS_DB_HYPERLINK_CHANGED    = 0x00100000, // гиперссылки менялись, будут сохранены в объект.
	MCS_DB_CALL_ONERASE_ALWAYS  = 0x00200000, // всегда вызывать onErase у объекта, не смотря ни на какие исключения.
	MCS_DB_GRAPHICS_ONLY_UPDATE = 0x00400000, // Устанавливается для объектов не хранящих кеш графики (IMcEntityType::kMc_NoCache). При установленном флаге объекту запрещено менять что-либо кроме собственной графики.
};
//==============================================================================
enum McCoverMode
{
	kMcCoverMode_None = 0,
	kMcCoverMode_Cut  = 1,
	kMcCoverMode_Mask = 2,
};
//==============================================================================
//Predefined properties names
#define MCS_PROPERTY_SCALE      _T("Scale")     // Масштаб отображения элементов оформления
#define MCS_PROPERTY_DIMSCALE   _T("DimScale")  // Масштаб измерений
#define MCS_PROPERTY_INFO       _T("Info")
#define MCS_PROPERTY_NAME       _T("Name") // Попытается запросить в объекте, если нет попытается узнать имя под которым зарегестрирован объект
#define MCS_PROPERTY_TEXTSTYLE  _T("Text style")
#define MCS_PROPERTY_DIMSTYLE   _T("Dimension style")
#define MCS_PROPERTY_TTITEM     _T("TT item") // int
#define MCS_PROPERTY_TTINFO     _T("TT info") // string
#define MCS_PROPERTY_SPEC_PARTIITION _T("SpecPartition") //Раздел спецификации
#define MCS_PROPERTY_ZORDER     _T("ZOrder")
#define MCS_PROPERTY_OBJECTID   _T("ObjectID")
#define MCS_PROPERTY_CUT_ACADENTS _T("CutAcElements") // Способ перекрытия
//#define MCS_PROPERTY_WIPEOUT    _T("WipeOut") // Объединено с MCS_PROPERTY_CUT_ACADENTS
#define MCS_PROPERTY_MASK_TEXT  _T("MaskText")    // Вырезать графику под текстом
#define MCS_PROPERTY_FORM       _T("ObjectForm")  // mcPropsCustom. Пользовательская форма для редактирования объекта
#define MCS_PROPERTY_OBJECT_GUID _T("ObjectGUID")
#define MCS_PROPERTY_TEXT       _T("Text")
#define MCS_PROPERTY_NATIVE_MTEXT _T("NativeMText") // Используется для редактирования MText нашим сервисом "Поиск и замена", который умеет работать с форматом MText
#define MCS_PROPERTY_OWNER_EDIT _T("OwnerEdit")// bool, перенаправить редактирование источнику данных, если объект содержит на него ссылку
#define MCS_PROPERTY_SHOW_MCONTOURS  _T("ShowMContours") // bool, Отображать контуры подрезки объекта
#define MCS_PROPERTY_MATERIAL    _T("Material")// Материал

//Специальное свойство, при его установке, объект должен отрисоватся  в виде пригодном для УГО и превью
//т.е. с сохранением типов линий, таги и метки в центр, желательно в квадратных пропорциях, т.е. геометрические свойства можно сбросить.
//устанавливатся будет в копии объектов, поэтому заботится о дальнейшей правильной жизни объекта необязательно, связи - оотключить
#define MCS_PROPERTY_PREVIEW     _T("mcPreview")

//==============================================================================
//System props
#define MCS_PROPERTY_COLOR          _T("Color")
#define MCS_PROPERTY_LAYER          _T("Layer")
#define MCS_PROPERTY_LINETYPE       _T("Linetype")
#define MCS_PROPERTY_LINETYPE_SCALE _T("Linetype Scale")
#define MCS_PROPERTY_LINEWEIGHT     _T("Line Weight")
#define MCS_PROPERTY_TRANSPARENCY   _T("Transparency")
#define MCS_PROPERTY_HYPERLINK      _T("Hyperlink")
#define MCS_PROPERTY_THICKNESS      _T("Thickness")

//Специальное имя свойства, ставится в mcPropsCustom
//var - mcsstrignarray 0 - Имя команды которую надо позвать на редактирование, 1- описание команды которе будет в tooltip
//2 - параметры для команды
// Указатель на этот же вариант будет передан параметром в команду редактирования, при этом в нулевое поле массива будет записан
// mcsWorkID редактируемого объекта в строковом варианте. При штатном выполнении команды параметр будет нулевой.
#define MCS_PROPERTY_CUSTOM_EDIT _T("mcEditRedefine")

// Хранить оси эллипсов, чтобы сохранить параметризацию эллипса. Чтобы точки полуосей не сдвигались в RMCS#29007.
#define MCS_PROPERTY_CUSTOM_AXIS_X _T("mcAxisX")
#define MCS_PROPERTY_CUSTOM_AXIS_Y _T("mcAxisY")

//==============================================================================
enum mcsPropertyType
{
	// IMcEntity
	//Внимание!!!!! одно из этих значений надо возвращять в методе  getPropertyType, и никакие другие!!!!
	mcPropsNone     = 0x0,
	mcPropsReadOnly = 0x1,
	mcPropsInternal = 0x2, // видимо в инспекторе или нет
	mcPropsDisabled = 0x4,//управляет видимостью свойств в окне Properties, для скрытия свойств механиковских продуктах комбинировать с 
	mcPropsInconstantInfo = 0x08,// отключает кеширование McPropertyInfo, инфо будет запрашиваться постоянно, может комбинироваться с другими флагами
	mcPropsNeedUpdateSet  = 0x10,// после изменения данного свойства будет принудительно обновлён весь набор свойств (если платформа позволит), может комбинироваться с другими флагами
	mcPropsNormaCS        = 0x20,// При редактировании данного свойства доступна интеграция с NormaCS
	mcPropsSpecSymbols    = 0x40,// Свойство допускает вставку специальных символов. Доступен диалог вставки спецсимволов.
	mcPropsDisablePreview = 0x80,// Отключает предварительный просмотр во время выбора значения свойства из списка.
	mcPropsNeedUpdate     = 0x100,// после изменения данного свойства будут принудительно обновлены все свойства набора (если платформа позволит), может комбинироваться с другими флагами

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Это только входные значения!!!! Их не надо нигде возврщать!!!!!!!!!
	// IMcDbEntity
	mcPropsSystem    = 0x00001000,
	mcPropsObject    = 0x00002000,
	mcPropsCustom    = 0x00004000,
//	mcPropsAsIndex   = 0x00008000, упразднено
	mcPropsField     = 0x00010000,
	mcPropsFieldData = 0x00020000,
	mcPropsUser      = 0x00040000, // Определяемые пользователем атрибуты, доступные из диалогов свойств
	mcPropsProject   = 0x00080000, //Проектные свойства объектов/свойства групп объектов, могут менятся без изменения объектов, поэтому ставить реакторы на них нельзя
	mcPropsCommand   = 0x00100000, // Только свойства с данным флагом будут видны как свойства команды
	mcPropsTextFieldsPE = 0x00200000, // Специально для поиска и замены. setProperty принимает строку для замены в формате "<индекс начального символа с отсчётом от нуля>:<количество символов>:<строка для замены>"
	mcPropsFieldObjectId = 0x00400000,
	mcPropsCommandOnly = mcPropsCommand | mcPropsInternal,
	mcPropsVisible   = mcPropsObject|mcPropsUser,
	mcPropsVisible2   = mcPropsObject|mcPropsUser|mcPropsSystem,
};

//==============================================================================
enum mcReactorsType
{
	kMcObjNone = 0x0,
	kMcObjChanged,
	kMcObjErased,
	kMcObjAdded,   //system
	kMcObjRemoved, //system

		// system, for ex. generated by 3d-objects when their shape really changed,
		// typycally sent from onUpdate on real changes of model
	kMcObjModelChanged,

		// same as kMcObjModelChanged, but indicates geom changes for the whole part,
		// i.e. if child solid is changed then its host solid generates this event
	kMcPartModelChanged,
	// system, for skip isObjectInContainer(RPair.idFrom) in reactors sender, send from native objectModifyed
	kMcNativeObjChanged,
};
//=============================================================================
#define MCLINK_NAMELEN      50 // in chars
#define MCLINK_MAXARRSIZE   50
#define MCLINK_DEFAULT_NAME TEXT("<noname>")
//===========================================================================
//context menu item  
struct McContextMenuItem
{
	McsString text;
	McsString command;
	UINT nID;
	int iBmpIndex; //index in global image storage
	bool isChecked;
	bool bSingleObject; //show menu item ONLY if single object selected
	mcsCtxMenuItemArray aPopup;

	McContextMenuItem(){
		nID = 0;
		iBmpIndex = -1;
		bSingleObject = false;
		isChecked = false;
	}

	McContextMenuItem(LPCTSTR txt, LPCTSTR cmd, bool bSingle = false, int iBmp = -1){
		nID = 0;
		iBmpIndex = iBmp;
		bSingleObject = bSingle;
		text = txt;
		command = cmd;
		isChecked = false;
	}

	McContextMenuItem(LPCTSTR txt, UINT _nID, int iBmp = -1, bool _isChecked = false){
		nID = _nID;
		iBmpIndex = iBmp;
		bSingleObject = true;
		text = txt;
		isChecked = _isChecked;
	}

	McContextMenuItem(const McContextMenuItem& src){
		*this = src;
	}

	McContextMenuItem& operator=(const McContextMenuItem& src){
		if(this == &src) return *this;
		text = src.text;
		command = src.command;
		nID = src.nID;
		iBmpIndex = src.iBmpIndex;
		bSingleObject = src.bSingleObject;
		aPopup = src.aPopup;
		isChecked = src.isChecked;
		return *this;
	}
};
//===========================================================================
__inline bool operator== (const McContextMenuItem& v1, const McContextMenuItem& v2)
{
	if(v1.bSingleObject != v2.bSingleObject) return false;
	if(v1.command != v2.command) return false;
	if(v1.text != v2.text) return false;
	if(v1.iBmpIndex != v2.iBmpIndex) return false;
	return true;
}
//=============================================================================
struct IMcLC : public IMcObject
{
	TCHAR     name[MCLINK_NAMELEN];
	bool      fNew;
	mcsWorkID val;
	IMcLCs    arr;

	DECLARE_OBJ_NEWDEL;
	IMCS_STD_METHOD_DEFINITION(IMcLC, IMcObject);

	IMcLC(LPCTSTR name_arg = MCLINK_DEFAULT_NAME) {
		lstrcpyn(name, name_arg, STRBUFSIZE(name));
		fNew = true; // value is temporary and generally should not be saved
	}

	void operator = (const mcsWorkID& val_arg) {
		MCSASSERTE(arr.GetSize()!=0); // can't assign value to links array entry
		val = val_arg;
		fNew = false; // value changed: must be taken in account
	}

	bool exist() {
		return !fNew;
	}
};
//=============================================================================
// Links container/manipulator
struct McLinks
{
	IMcLCPtr plcs;

	DECLARE_OBJ_NEWDEL;

	McLinks() {
		plcs.p = new IMcLC;
	}

	McLinks(IMcLC* pE) {
		plcs = pE;
	}

		// query link value through it
	MECHCTL_API operator const mcsWorkID&() const;
		// query named link(s)
	MECHCTL_API McLinks operator [] (LPCTSTR name_arg);
		// query indexed link(s)
	MECHCTL_API McLinks operator [] (int idx);
		// assign/update link value through it
	MECHCTL_API void operator = (const mcsWorkID& val_arg);
		// counts items inside container
	MECHCTL_API int count(bool fSkipTemporaryAndUnused=true);
		// check container whether has valid existing value
	MECHCTL_API bool exist();
		// serialization processing
	MECHCTL_API HRESULT write(IMcsStream* pS);
	MECHCTL_API HRESULT read(IMcsStream* pS);
};
//==============================================================================

//Класс позволяющий сохранить состояние объекта(ов), и вернутся к нему
//Контролирует добавление в ObjectManager и Document, удаление, изменение реакторов (как к этому объекту так и от него)
//Сохраняет состояние объекта в McStream. (в момент вызова команды start, add или writeEnabled(если объект находится в objectmanager))

struct IMcUndoPoint : public virtual IMcObject
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcUndoPoint);
	IMCS_STD_METHOD_DEFINITION(IMcUndoPoint, IMcObject);

	// Сохраняет состояние системы, будет вести мониторинг всех изменяющихся объектов
	virtual HRESULT start() = 0; 

	// Сохраняет состояние объекта, будет вести мониторинг его состояния.
	virtual HRESULT start(IMcDbObject* pObject) = 0;
	virtual HRESULT add(IMcDbObject* pObject) = 0;

	// Восстанавливает состояние системы или объекта(-ов) к состоянию в момент вызова start
	virtual HRESULT restore(bool bUpdate = false) = 0;
	virtual HRESULT stop() = 0;

	// Tools
	// Получить список изменившихся обектов(для функции start())
	virtual HRESULT getModifiedObjects(mcsWorkIDArray& ids) = 0;

	// Вызвать update изменившимся обектам(для функции start())
  // Если указана строка, будет показан прогресс бар со статусом операции
	virtual HRESULT updateModifiedObjects(IN OPTIONAL LPCTSTR strProgressBarString = NULL) = 0;

	// метод позволяет определить, выполняется ли в данный момент времени откат изменений через вызов
	// метода restore у любого из существующих UndoPoint
	MECHCTL_API static bool isInRestoreNow();

protected:
	virtual void onChange(IN const mcsWorkID& objTo, IN const mcsWorkID& objFrom, mcReactorsType action) = 0;

	friend class CMcObjectsManager;
};
//==============================================================================

struct IMcCustomDlgContext : public IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcCustomDlgContext);
	IMCS_STD_METHOD_DEFINITION(IMcCustomDlgContext, IMcObject);
	mcsWorkIDArray ids;
	HWND hParent;
	McsString propertyName;
};
//==============================================================================
typedef HRESULT (*McPropsCustomDialogProc)(IMcCustomDlgContext *pContext);

//==============================================================================
struct McPropertyInfo
{
	DECLARE_OBJ_NEWDEL;
	MCS_CTRL ctrlType;      // Тип контрола
	int propType;           // Набор флагов из mcsPropertyType.
	                        // Указывать можно только те флаги, для которых в описании это явно указано
	MCSVariant values;      // Массив для свойств с фиксированным списком значений
	McsString stLocalName;  // Локализованное имя (это то, что раньше возвращал getPropertyDescription)
	McsString stDescription;// Развернутое описание свойства (а это то, что можно увидеть внизу акдовского окна свойств)
	McsString stCategory;   // Категория. К сожалению AutoCAD не поддерживает вложенные категории свойств.
	                        // Категории будут отображаться в виде <ApplicationName>/<YourPropertyCategoryName> на
	                        // одном уровне с нашей стандартной категорией <ApplicationName>
	int iGsMarker;
	McPropsCustomDialogProc pCustomDialog;// Процедура редактирования (вызовется при нажатии кнопки в инспекторе)
	McUnits::Name units;    // Единицы измерения параметра. Имеют смысл только при назначении соответствующего ctrlType.
	McPropertyInfo()
	{
		ctrlType = MC_NONE;
		propType = mcPropsNone;
		iGsMarker = -1;
		pCustomDialog = NULL;
		units = McUnits::kDefault;
	}

	void Empty()
	{
		ctrlType = MC_NONE;
		propType = mcPropsNone;
		values.Clear();
		stLocalName.Empty();
		stDescription.Empty();
		stCategory.Empty();
		pCustomDialog = NULL;
		units = McUnits::kDefault;
	}
};
typedef McsArray<McPropertyInfo> McPropertyInfoArray;

//==============================================================================
// Переопределение глобальных параметров для конкретного объекта
struct IMcParameterRedefinition : public virtual IMcObject
{
	IMCS_QI_METHOD_DEFINITION(IMcParameterRedefinition, IMcObject);

	// Отдают переопределённый параметр, если он есть, либо непереопределённый из настроек
	virtual MCSVariant GetParam(IN int idParam) const = 0;
	virtual int       GetIntParam(IN int idParam) const = 0;
	virtual bool      GetBoolParam(IN int idParam) const = 0;
	virtual double    GetRealParam(IN int idParam) const = 0;
	virtual McsString GetStringParam(IN int idParam) const = 0;

	// Переопределяют параметр
	virtual HRESULT SetParam(IN int idParam, IN const MCSVariant& v) = 0;
	virtual HRESULT SetIntParam(IN int idParam, IN int iValue) = 0;
	virtual HRESULT SetBoolParam(IN int idParam, IN bool bValue) = 0;
	virtual HRESULT SetRealParam(IN int idParam, IN double rValue) = 0;
	virtual HRESULT SetStringParam(IN int idParam, IN LPCTSTR stValue) = 0;

	// Убрать переопределение
	virtual HRESULT RemoveRedefinition(IN int idParam) = 0;

	// Список переопределённых параметров
	virtual HRESULT GetRedefined(OUT mcsIntArray& redefined) const = 0;

	// Копирование свойств
	virtual HRESULT MatchProperties(IN IMcEntity* pFrom, IN OPTIONAL const mcsIntArray* pIgnored = NULL) = 0;
};

//---------------------------------------------------------------------------
#define PRI(IDPARAM) (PR()->GetIntParam(IDPARAM))
#define PRR(IDPARAM) (PR()->GetRealParam(IDPARAM))
#define PRB(IDPARAM) (PR()->GetBoolParam(IDPARAM))
#define PRS(IDPARAM) (PR()->GetStringParam(IDPARAM))
#define PRV(IDPARAM) (PR()->GetParam(IDPARAM))

#define PRI2(ENT, IDPARAM) (ENT->PR()->GetIntParam(IDPARAM))
#define PRR2(ENT, IDPARAM) (ENT->PR()->GetRealParam(IDPARAM))
#define PRB2(ENT, IDPARAM) (ENT->PR()->GetBoolParam(IDPARAM))
#define PRS2(ENT, IDPARAM) (ENT->PR()->GetStringParam(IDPARAM))
#define PRV2(ENT, IDPARAM) (ENT->PR()->GetParam(IDPARAM))

//==============================================================================
struct IMcPropertySource : public virtual IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMcPropertySource, IMcObject);
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcPropertySource);
	//////////////////////////////////////////////////////////////////////////
	//properties
	virtual HRESULT getProperties(mcsStringArray& astNames, mcsPropertyType eType) {astNames.RemoveAll(); return E_NOTIMPL;}
	virtual HRESULT getProperty(const McsString& stName, mcsPropertyType eType, MCSVariant& data) {data.SetType(MCSVariant::kUndefined); return E_NOTIMPL;}
	virtual HRESULT setProperty(const McsString& stName, mcsPropertyType eType, const MCSVariant& data) {return E_NOTIMPL;}
	virtual HRESULT getPropertyInfo(const McsString& stName, McPropertyInfo& info, mcsPropertyType eType) {return E_NOTIMPL;}
	virtual HRESULT deleteProperty(const McsString& stName, mcsPropertyType eType) {return E_NOTIMPL;}
};

//==============================================================================
struct IMcPropertyCarrier: public IMcPropertySource, public IMcAutoFree
{
	IMCS_STD_METHOD_DEFINITION3(IMcPropertyCarrier, IMcPropertySource, IMcAutoFree);
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcPropertyCarrier);

	virtual HRESULT Identify(const mcsWorkID& id, const CLSID& clsid) = 0;
	virtual HRESULT AddProperty(const McsString& stName, mcsPropertyType ptyType, const McPropertyInfo& info, const MCSVariant& value) = 0;
	virtual void RemoveAll() = 0;
	virtual bool IsEmpty() const = 0;
};

//==============================================================================
struct IMcPropertyFindExtension : public virtual IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMcPropertyFindExtension, IMcObject);
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcPropertyFindExtension);

	virtual HRESULT getProperties(mcsStringArray& names, mcsStringArray& values, mcsBoolArray& readonly) = 0;
	virtual HRESULT replace(LPCTSTR stName, LPCTSTR stString, int iStartChar, int iEndChar) = 0;
	virtual HRESULT getFragmentBounds(LPCTSTR stName, int iStartChar, int iEndChar, mcsBoundBlocksArray& bounds) = 0;
};

//==============================================================================
// Панель свойств.
// Отображение свойств одного или нескольких объектов.
// Группировка по категориям.
//
// Типы данных
// MC_EDIT_STRING                Поддерживает как строку, там и массив строк
// MC_STRING_ARRAY               То же, что MC_EDIT_STRING
// MC_COMBOBOX_STRING            Здесь и дальше список для ComboBox берется из getPropertyInfo
// MC_COMBOBOX_STRING_INDEX
// MC_EDIT_INT
// MC_EDIT_COMBOBOX_INT
// MC_COMBOBOX_INT
// MC_EDIT_DOUBLE
// MC_EDIT_COMBOBOX_DOUBLE
// MC_COMBOBOX_DOUBLE
// MC_BOOL_COMBOBOX
// 
// MC_LAYER_COMBOBOX              Зарезервировано для FormDesigner
// MC_OPEN_FILE_DIALOG            Выбор пути к файлу
// MC_OPEN_GLOBAL_DB_DIALOG       Выбор иконки из ghImageList. Результат - номер иконки.
// MC_COLOR_COMBOBOX              Выбор цвета
// MC_TEXTSTYLE_COMBOBOX          Шрифт. Значение - содержимое LOGFONT в виде mcsByteArray
// MC_LINEWEIGHT_COMBOBOX         Редактирование строки с возможностью выбора из setStringList
// MC_DIMSTYLE_COMBOBOX           Выбор списка строк из IMcFmListSource. Хранит имя списка.
//

//==============================================================================
struct IMcPropertyBrowserCallback : public IMcObject
{
	virtual void OnPropertyChanged(IMcPropertySource* pObject, LPCTSTR strPropertyName, const MCSVariant& vPropertyValue) {}
	virtual void OnPropertyChanged(LPCTSTR strPropertyName, const MCSVariant& vPropertyValue) {}
};

//==============================================================================
IMCS_DECL_INTERFACE(IMcPropertyBrowser, "{C238FBD2-5BDA-4bf6-BFB6-12751B719044}");

struct IMcPropertyBrowser : public IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMcPropertyBrowser, IMcObject);
	virtual HWND hwnd() = 0;
	virtual HRESULT Create(IN HWND hParent, IN LPRECT pRect, IN UINT Style, IN UINT xStyle) = 0;
	// Подгоняет размеры окна под содержимое.
	// Перед вызовом нужно выставить приблизительные размеры окна.
	virtual HRESULT AdjustSize() = 0;
	// Управляет видимостью хинта (такой статик с описанием свойства в нижней части окна).
	// По умолчанию хинт включен.
	virtual HRESULT ShowDescription(IN OPTIONAL BOOL fShow = FALSE) = 0;

	virtual HRESULT addObject(IN IMcPropertySource* pObject) = 0;
	virtual HRESULT delObject(IN IMcPropertySource* pObject) = 0;
	virtual HRESULT delObjects() = 0;
	// Очищает список объектов, фильтр свойств, категорий, переопределения категорий
	virtual HRESULT Clear() = 0;
	// Перестраивает список заново.
	virtual HRESULT Update() = 0;

	// Скрыть все свойства из категории. Можно скрыть несколько категорий, вызвав для каждой CategoryHide.
	// NULL - показать все категории
	virtual HRESULT CategoryHide(IN LPCTSTR lpszCategory = NULL) = 0;
	// Поместить свойство в категорию. lpszCategoryName = NULL удаляет переопределение.
	// Если оба параметра нулевые - все переопределение удалятся.
	virtual HRESULT CategoryRedefine(IN LPCTSTR lpszPropName, IN OPTIONAL LPCTSTR lpszCategoryName = NULL) = 0;
	// Показывать только перечисленные свойства.
	// Пустой массив - показать все свойства.
	// mcPropsInternal и mcPropsDisabled не показыватются ни при каких условиях.
	virtual HRESULT ShowOnly(IN const mcsStringArray& msPropNames) = 0;
	// Сортировать свойства по алфавиту в пределах категории.
	virtual HRESULT SortByName(IN BOOL fSort) = 0;

	virtual HRESULT addCallback(IN IMcPropertyBrowserCallback* pCallback) = 0;
	virtual HRESULT delCallback(IN IMcPropertyBrowserCallback* pCallback) = 0;
};

struct IMcAlbums;

//==============================================================================
enum McObjCopyModeEnum
{
		// old default value: bool fFull = false
		// ID and links will be replaced
	kMcObjCopyMode_InexactNoLinks   = 0,

		// old value: bool fFull = true
		// ID and links will be kept
	kMcObjCopyMode_Exact            = 1,

		// ID will be replaced and links will be kept
	kMcObjCopyMode_InexactKeepLinks = 2,
};

//==============================================================================
//Реализация в Gate

struct IMcDbObject : public virtual IMcPropertySource
{
public:

	const GUID& getClassID() const {return IID_IMcDbObject;}
	MECHCTL_API virtual bool isKindOf(REFIID riid) const;
	MECHCTL_API HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj);

//..............................................................................

	MECHCTL_API virtual void invalidate() override;

	// dwChangesFlags - набор флагов из McObjChangesTypeEnum
	virtual HRESULT writeEnabled(DWORD dwChangesFlags = 0) = 0;

	virtual HRESULT erase() = 0;

	//..............................................................................

	virtual HRESULT write(OUT IMcsStream* pStream) const = 0;

		// при записи платформенно независимого стрима может потребоваться запись
		// данных, которые на самом деле зависят от платформы. Нпример файлы IPT для инвентора
		// с целью ускорения вставки групп объектов.
		// по умлочанию ничего не пишется.
		// Mетод вызывается из прототипов CDbEntityPrototype и CDbObjectPrototype, если
		// стрим, в который производится запись является платформенно независимым.
	virtual HRESULT writePLMData4IndependentStream(IN OUT IMcsStream* pStream) const {
		return S_FALSE;
	}

	virtual HRESULT read(IN IMcsStream* pStream) = 0;

		// см. описание <writePLMData4IndependentStream>
		// По умлочанию ничего не читается.
		// Mетод вызывается из прототипов CDbEntityPrototype и CDbObjectPrototype, если
		// стрим, в из которого производится стение является платформенно независимым.
	virtual HRESULT readPLMData4IndependentStream(IN OUT IMcsStream* pStream) {
		return S_FALSE;
	}

	virtual HRESULT update() = 0;//update data|graphics

	virtual IMcDbObjectPtr getCopy(McObjCopyModeEnum copyMode = kMcObjCopyMode_InexactNoLinks) = 0; // by default copy over write/read
	virtual IMcDocumentPtr getDocument() const = 0;
	virtual mcsWorkID getDocumentID() const = 0;

	// AGL: 29.04.2014, отпускание связанных объектов выполнено по новой универсальной схеме
	//MECHCTL_API virtual ULONG STDMETHODCALLTYPE Release();
	MECHCTL_API virtual HRESULT _onResetGrpPtrs() override;
	MECHCTL_API virtual HRESULT _onAppendGrpObjPtrs(IN OUT mcsMapMcObjToInt& ptrsSet, bool bForUnbind) override;
	virtual const mcsWorkID& ID() const {return m_ID;}

		// Методы для работы с флагами, позволяющими определить тип изменений в объекте.
		// Здесь обрабатываются флаги из множества McObjChangesTypeEnum
	MECHCTL_API virtual DWORD getObjChangesFlags();
	MECHCTL_API virtual void  setObjChangesFlags(DWORD dwMask, bool bExclusive = false); // если bExclusive=true, заменит хранимые флаги на указанные

	//..............................................................................
	//Extension

		// Добавить постоянный реактор от этого объекта к idTo.
		// Если bUpdateNow = true, выполнит this->update() - это РЕКОМЕНДОВАННОЕ поведение.
		// Если запрошено обновление, объект должен быть в чертеже.
		// Если указать bUpdateNow = false, возможна ситуация, что до обновления выполнится reload на объекте
		// и установленные реакторы перетрутся данными из документа.
	virtual HRESULT addReactor(const mcsWorkID& idTo, bool bUpdateNow) = 0;

		// Удалить постоянный реактор от this к idTo.
		// Комментарий к bUpdateNow см. выше
	virtual HRESULT removeReactor(const mcsWorkID& idTo, bool bUpdateNow) = 0;

		// Получить список установленных постоянных реакторов от этого объекта
	virtual HRESULT getReactors(mcsWorkIDArray& idsTo) const = 0;

	virtual IMcParameterRedefinition* PR() const
		{ return NULL; }

	virtual MCS_STANDARD getStandard() const
		{ return MCS_STD_GOST; }

	// object must completely remove itself from document where it lives but not set status ERASED!
	// it will not be erased - it only leaves document
	// NANO/ACAD note:  В силу архитектуры DWG физически объект удаляется из
	// документа методом erase. Для пользовательского кода это "прозрачно",
	// т.к. workId объекта остаётся тот же, просто при повторном добавлении
	// создаётся другой физический объект с другим физическим ObjectID в DWG.
	// Если на объект были установлены какие-то реакторы, то все они будут ссылаться
	// на старый физический ObjectId. И просто-напросто перестанут работать. Поэтому
	// ПЕРЕД удалением объект из документа нужно снять все реакторы на него и после
	// повторного добавления установить новые. На уровне гейта операцию
	// автоматической перестановки реакторов выполнить крайне сложно, т.к. DWG не
	// даёт возможности узнать, какие объекты установили реакторы на удаляемый
	// объект. Поэтому перестановка реакторов должна для DWG-based платформ
	// выполняться на стороне пользовательского кода.
	virtual HRESULT removeFromDocument() = 0;

		// AGL
		// return <true> if this object logically can't have root object in references path;
		// by default links and objects manager assigns <true> to all objects which haven't parent reference 
		// and not implements CDbReferenceProto interface;
		// Example of usage: STD objects stored in catalog of components
	virtual bool    isSpecificStopRefNode() {return false;}
		// AGL
		// Returns ID of native reference context, if it's !null then object can have native references;
		// There are may be some objects in the same native ref ctx;
		// INV (this will be ID of ComponentOccurrence object or ID of part document);
		// You can use returned ID in QueryObject as refCtxId
	virtual mcsWorkID getNativeRefCtx() {return WID_NULL;}

	virtual HRESULT reload() = 0;//reload object data for some platform

		// AGL
		// method called for objects which must be reloaded because their state changed on Undo/Redo/Abort transaction command;
		// On this method object can migrate between different documents so must accept new location
	virtual HRESULT OnTransactionChanged(const mcsWorkID& docID) {return E_NOTIMPL;}

		// AGL
		// method called from document loader to initialize object with ID/DocID and flag which will indicate 
		// the need of object's reloading in IMcDbObject::reload method
	virtual HRESULT OnInitialLoad(const mcsWorkID& objectID, const mcsWorkID& docID) {return E_NOTIMPL;}

		// For system use only
	virtual HRESULT onSystemEvent(int evt, WPARAM wParam, LPARAM lParam) { return E_NOTIMPL; }

		// Fields
		// if hParent == NULL then gpMcContext->GetMainWnd() will be used
	virtual HRESULT AddField(IN OPTIONAL HWND hParent = NULL, OUT OPTIONAL McsString* pstName = NULL)
		{ return E_NOTIMPL; }
	virtual HRESULT EditField(IN LPCTSTR stName, IN OPTIONAL HWND hParent = NULL)
		{ return E_NOTIMPL; }
	virtual HRESULT RemoveField(IN LPCTSTR stName)
		{ return E_NOTIMPL; }

	//Check internal reactors from object From
	virtual HRESULT	 canRemove(const mcsWorkID& idFrom){return S_OK;}

	//..............................................................................

	//Object GUIDs
	//Автоматически будет установлен при добавлении в документ
	//для объекта в документе будет произведена проверка уникальности при установке, при добавлении в документ будет перегенерирован
	virtual HRESULT setGUID(const GUID& guid) = 0;
	virtual HRESULT getGUID(GUID& guid) = 0;
	virtual HRESULT getGUID(mcsWorkID& guid) = 0;

	virtual IMcAlbumsPtr MECHCTL_API getAlbums();
	virtual IMcPropertySourcePtr getAlbumsNode() { MCSASSERTE(__FUNCTION__); return UNKNULL; }
	virtual HRESULT setAlbumsNode(IMcPropertySource* pRes) { MCSASSERTE(__FUNCTION__); return E_NOTIMPL; }
	virtual IMcObjectPtr getPrjNode(LPCTSTR nodeName = NULL) const { MCSASSERTE(__FUNCTION__); return UNKNULL; };
	virtual HRESULT setPrjNode(IMcObjNode* pNode, LPCTSTR nodeName = NULL){ MCSASSERTE(__FUNCTION__); return E_NOTIMPL; };
	virtual void getAllPrjNodes(McsArray<IMcObjNodePtr, IMcObjNode*>& nodes, bool bRestoreErased = false){ MCSASSERTE(__FUNCTION__); };
	virtual HRESULT updateProjectData(bool fromObjectToNode){ MCSASSERTE(__FUNCTION__); return E_NOTIMPL; };

	// Уникальный в рамках документа и неизменный в течение всего срока жизни документа идентификатор объекта.
	virtual GUID getHandle() = 0;

	//..............................................................................
	// Подобъекты

		// Добавляет объект в список дочерних к указанному родительскому.
		// ВАЖНО! Родителя нужно устанавливать ДО добавления дочернего объекта в документ.
		// Потому как родитель определяет способ хранения дочернего объекта в чертеже.
		// Реализация по умолчанию получает объект по данному ID и зовёт setParent.
		// так сделано из-за того, что связка дочерний-родитель может образовывать
		// в момент QueryObject для родителя, и в этот момент его ещё нет в контейнере.
	MECHCTL_API virtual HRESULT   setParentID(const mcsWorkID& id);
	virtual HRESULT               setParent(IMcDbObject* pParent) { return E_NOTIMPL; }
	virtual const mcsWorkID&      getParentID() const { return m_idParent; }
	virtual const mcsWorkIDArray& getChildrenIDs() const { return m_idsChildren; }

		// (исп. для системных целей)
		// Выдаёт список дочерних объектов. Дополнительно можно указать спец. фильтр
		// kChildrenSysFilter_All            - выдать всё, работает как getChildrenIDs
		// kChildrenSysFilter_ChildSolids    - выдать список врезных солидов для 3D
		// kChildrenSysFilter_AlienSolidData - выдать спец 3D объект IMc3dAlienSolidData из списка дочерних
		// kChildrenSysFilter_CheckOnly      - вернуть S_OK, если есть дочерние объекты, E_FAIL, если нет
	MECHCTL_API virtual HRESULT getChildrenIDsEx(OUT mcsWorkIDArray& childrenIDs, IN int iSysFilter);

	MECHCTL_API virtual IMcDbObjectPtr  getParent() const;

	// Проверка на возможность удаления объекта
	MECHCTL_API virtual bool canBeErased() const;

	// метод позволяет поменять порядок дочерних элементов.
	// Набор sameOrderedChildren менять нельзя, можно менять только порядок.
	MECHCTL_API virtual HRESULT setChildrenOrder(const mcsWorkIDArray& sameOrderedChildren);

	// Метод должен вернуть true, если для объекта можно использовать оптимизацию записи ID в IMcsStream.
	MECHCTL_API virtual bool supportIdStreamOpt() const;

	//..............................................................................

	//system definition

	IMcEntityPtr m_pSink;

	mcsWorkID m_ID;
	GUID      m_RefGroupUID; // identifies group of all references for this object (default value = GUID_NULL),
	                         // mcsWorkID is not valid for this member because keeps links across many 
	                         // documents accept its copies
	__int64   m_UpdateTime; // its LocalTime in FILETIME representation of the last object update
	long      m_lSesion, m_lStatus;

	// нужно для кэширования состояния объекта например для отрисовки,
	// за одну сессию объект может несколько раз менять свой внешний вид,
	// поэтому m_lSesion для этой цели не подойдет;
	// поле не сохраняется, особого смысла в этом нет
	long      m_lUpdateCounter;

	// AGL 25.12.2004, moved here from IMcDbEntity because abstract DB object
	// in document can have constraints of 'link' type (i.e. neither geometry nor parametric)
	mcsWorkIDArray m_idsConstraints;

	// AGL 11.10.2006, added for ability to keep custom transient data with object;
	// for example 3D modeler data
	IMcObjectPtr m_pExData;

		// Поля для подобъектов и врезных 3D объектов;
		// Первое использование - Врезные тела в 3D. ID родителя - это деталь, на теле которой
		// существуют дочерние врезные объекты
	mcsWorkID      m_idParent;
	mcsWorkIDArray m_idsChildren;

	friend struct IMcEntity;
	friend struct Mc3dnStdEntSwitcher;

		// system use
	mutable DWORD m__dwLockMask; // AGL, используется для блокировки различных циклических вызовов (writeEnabled, isKindOf, ...)

protected:

	DWORD m_dwChangesFlags; // флаги, отражающие причину изменений объекта

protected:

	MECHCTL_API IMcDbObject();
	MECHCTL_API ~IMcDbObject();
};
//==============================================================================
struct McGripData
{
	enum Type
	{
		kgtSimple      = 0x0000,
		kgtPopupMenu   = 0x0001,// не может быть использован с kgtButton, kgtInteractive
		kgtButton      = 0x0002,// не может быть использован с kgtPopupMenu, kgtInteractive
		kgtInteractive = 0x0004,// не может быть использован с kgtPopupMenu, kgtButton
		kgtNoRubber    = 0x0008,// отключает резинку, тянущуюся от базовой точки
		kgtAltBase     = 0x0010,// задана базовая точка (m_pntAlt), отличная от точки ручки
		kgtMovable     = 0x0020,// значок ручки будет двигаться за курсором
		kgtAlignCamera = 0x0040,// Ручка автоматически ориентируется по направлению к пользователю. Тип kgaStandard всегда ориентирована к пользователю.
		kgtUserGraphics = 0x0080,// Ручка с дополнительной графикой, передаваемой через метод GetGraphics.
	};
	enum Appearance
	{
		kgaStandard = 0,
		kgaSquare = 1,
		kgaCircle = 2,
		kgaRotate = kgaCircle,
		kgaPopupMenu = 3,
		kgaTriangle = 4,// направлен острым углом вниз
		kgaSpinTriangle = kgaTriangle,// направлен острым углом вниз
		kgaMirror = 6,// направлен вправо
		kgaPlus = 7,
		kgaTextAlign = 8,
		kgaRectangle = 9,// длинная сторона горизонтальна
		kgaInsertVertex = kgaRectangle,// направление горизонтальное
		kgaRhombus = 10,// вытянут по горизонтали
		kgaMove = kgaRhombus,// направление горизонтальное
		kgaAlignTo = 11,// направлен вправо
		kgaBigSquare = 12,// квадрат большего размера, чем стандартный
		kgaMinus = 13,// минус
		kgaSwitchOn = 14,// переключатель - включено
		kgaSwitchOff = 15,// переключатель - выключено
		kgaCongruence = 16,// конгруэнтность (три горизонтальные линии)
		kgaArrow = 17,// стрелка, направлена вправо
		kgaEdit = 18,// редактирование
		kgaEnter = 19,// ввод, перевод строки
		kgaEmpty = 20,// графика отсутствует, используется для ручек типа kgtUserGraphics
	};
	enum Status
	{
		kgsGripStart = 0,
		kgsGripEnd,
		kgsGripAbort,
		kgsStretch,
		kgsMove,
		kgsRotate,
		kgsScale,
		kgsMirror,
		kgsDimFocusChanged,
		kgsPopUpMenu,
	};

	struct GripMode
	{
		enum CursorType// Строго соответствует AcDbMultiModesGripPE::GripCursorType
		{
			kgctNone = 0,
			kgctCrosshairPlus,
			kgctCrosshairMinus,
			kgctCrosshairCurve,
			kgctCrosshairLine,
		};
		enum ActionType// Строго соответствует AcDbMultiModesGripPE::GripActionType
		{
			/// <summary>
			/// Instructs the grip editor to proceed with dragging. The mode
			/// specific behavior is determined by object's moveGripPointsAt
			/// current mode awareness.
			/// </summary>
			kgatDragOn = 0,
			/// <summary>
			/// Instructs the grip editor to call moveGripPointsAt once and
			/// end dragging sequence.
			/// </summary>
			kgatImmediate,
			/// <summary>
			/// External command, specified as GripMode::stCommandString, is called.
			/// </summary>
			kgatCommand,
		};

		DECLARE_OBJ_NEWDEL;

		/// <summary>
		/// The unique identifier among the collection of modes this PE implements. 
		/// </summary>
		UINT iMode;
		/// <summary>
		/// The display string of this mode in various UI elements (including haver menu and object context menu).
		/// </summary>
		McsString stDisplayString;
		/// <summary>
		/// The command line version of display string for this mode.
		/// </summary>
		McsString stCLIDisplayString;
		/// <summary>
		/// The command line prompt string when this mode is switched as current.
		/// </summary>
		McsString stCLIPromptString;
		/// <summary>
		/// The command line keyword list associated to CLIPromptString.
		/// </summary>
		McsString stCLIKeywordList;
		/// <summary>
		/// The type of cursor this mode uses.
		/// </summary>
		CursorType eCursorType;
		/// <summary>
		/// The action type of this mode uses.
		/// </summary>
		ActionType eActionType;
		/// <summary>
		/// Optional. If the action type is kCommand, the command used for this mode.
		/// </summary>
		McsString stCommandString;
		GripMode()
		{
			iMode = 0;
			eCursorType = kgctNone;
			eActionType = kgatDragOn;
		}
		GripMode(UINT _iMode, const McsString& _stDisplayString, CursorType _eCursorType = kgctNone, ActionType _eActionType = kgatDragOn, const McsString& _stCommandString = McsString())
		{
			iMode = _iMode;
			stDisplayString = _stDisplayString;
			eCursorType = _eCursorType;
			eActionType = _eActionType;
			stCommandString = _stCommandString;
		}
	};
	typedef McsArray<GripMode, const GripMode&> GripModeArray;

	DECLARE_OBJ_NEWDEL;

	mcsPoint m_pnt;
	mcsPoint m_pntAlt;
	HANDLE m_handle; // Идентификатор ручки
	McsString m_stToolTip;
	DWORD m_lFlags;
	Appearance m_appearance;
	COLORREF m_color;
	mcsVector m_vDirection;// Направление. Если не задано, то mcsVector::kXAxis.
	mcsVector m_vNormal;// Нормаль. Если не задана, то mcsVector::kZAxis.
	//для kgtMovable, m_pntDraw - расчитывается автоматически
	mcsPoint m_pntDraw;
	void *pSystemData;// Не использовать. Только для системных целей.

	virtual mcsPoint getDrawPosition()
	{
		return m_pntDraw;
	}
	virtual HRESULT GetMenu(mcsCtxMenuItemArray& menu)
		{ return E_NOTIMPL; }
	virtual HRESULT OnCommand(UINT id)
		{ return E_NOTIMPL; }
	virtual HRESULT ActiveEnt(const EM_Entity& ent)
		{ return E_NOTIMPL; }
	virtual void GripOperationStatus(McGripData::Status status)
		{}

	virtual bool GetGripModes(GripModeArray& modes)// Список режимов ручки
		{ return false; }
	virtual UINT GetGripMode()// Текущий режим
		{ return 0; }
	virtual GripMode GetGripMode(UINT iMode)
		{ return GripMode(); }
	virtual bool SetMode(UINT iMode)// Установить текущий режим
		{ return false; }

	virtual mcsGeomEntArray* GetGraphics()// Пользовательская графика для режима kgtMovable
		{ return NULL; }

	McGripData()
	{
		m_lFlags = kgtSimple;
		m_handle = NULL;
		m_appearance = kgaStandard;
		m_color = MCS_ENTCOLOR_BYCONTEXT;
		m_vNormal = mcsVector::kZAxis;
		m_vDirection = mcsVector::kXAxis;
		pSystemData = NULL;
	}

	// Простая ручка на плоскости XY
	McGripData(const mcsPoint& pnt, HANDLE handle, Appearance appearance = kgaStandard, double rRotation = 0, McGripData::Type type = McGripData::kgtSimple, const mcsPoint* ppntAlt = NULL, LPCTSTR stComment = NULL, COLORREF color = MCS_ENTCOLOR_BYCONTEXT)
	{
		m_lFlags = type;
		m_pnt = pnt;
		m_handle = handle;
		m_vNormal = mcsVector::kZAxis;
		m_vDirection = mcsVector::kXAxis;
		m_vDirection.rotateBy(rRotation, m_vNormal);
		m_appearance = appearance;
		if(ppntAlt)
		{
			m_pntAlt = *ppntAlt;
			m_lFlags = Type(m_lFlags | kgtAltBase);
		}
		if(stComment)
			m_stToolTip = stComment;
		m_color = color;
		pSystemData = NULL;
	}
	// Простая ручка в трёхмере
	McGripData(const mcsPoint& pnt, const mcsVector& vNormal, const mcsVector& vDirection, HANDLE handle, Appearance appearance = kgaStandard, McGripData::Type type = McGripData::kgtSimple, const mcsPoint* ppntAlt = NULL, LPCTSTR stComment = NULL, COLORREF color = MCS_ENTCOLOR_BYCONTEXT)
	{
		m_lFlags = type;
		m_pnt = pnt;
		m_handle = handle;
		m_vNormal = vNormal;
		m_vDirection = vDirection;
		m_appearance = appearance;
		if(ppntAlt)
		{
			m_pntAlt = *ppntAlt;
			m_lFlags = Type(m_lFlags | kgtAltBase);
		}
		if(stComment)
			m_stToolTip = stComment;
		m_color = color;
		pSystemData = NULL;
	}

	virtual ~McGripData()
	{
	}

	virtual HRESULT TransformBy(const mcsMatrix& tfm)
	{
		m_pnt.transformBy(tfm);
		m_pntAlt.transformBy(tfm);
		m_vDirection.transformBy(tfm);
		m_vNormal.transformBy(tfm);
		m_pntDraw.transformBy(tfm);
		return S_OK;
	}
};

//==============================================================================

class McGripDataPtrArray : public McsArray<McGripData*, McGripData*>
{
public:
	bool containsHandle(HANDLE value, INT_PTR start = 0) const
	{
		MCSASSERTx64_EX_32bit(start, return false);
		for(int i = (int)start; i < m_nSize; i++) 
		{
			if(m_pData[i]->m_handle == value) 
				return true;
		}
		return false;
	}

	McGripData* getByHandle(HANDLE value) const
	{
//		MCSASSERTx64_EX_32bit(start, return false);
		for(int i = 0; i < m_nSize; i++) 
		{
			if(m_pData[i]->m_handle == value) 
				return m_pData[i];
		}
		return NULL;
	}
};
typedef McsArray<HANDLE, HANDLE> mcsHandleArray;

//==============================================================================

#define kChildrenSysFilter_All            0
#define kChildrenSysFilter_ChildSolids    1
#define kChildrenSysFilter_AlienSolidData 2
#define kChildrenSysFilter_CheckOnly      3
#define kChildrenSysFilter_AllDeep        4
#define kChildrenSysFilter_ModeMask       0xFF
#define kChildrenSysFilter_UseGetObject   0x100

struct McGeometryParam;

//////////////////////////////////////////////////////////////////////////
// Получение информации о связанных объектах
enum McReferenceDirection {
	// Направление действия зависимости
	kMcRefDirection_None,       // ненаправленная
	kMcRefDirection_Direct,     // от сервера клиенту
	kMcRefDirection_Reverse,    // от клиента серверу
	kMcRefDirection_Both,       // в обоих направлениях
};

//------------------------------------------------------------------------
// Описание единичной зависимости.
//
// Реализовать для каждого класса объектов чертежа, который может зависеть от других объектов
//
interface IMcReferenceItem : public IMcObject
{
	// Объект-клиент
	virtual mcsWorkID getTarget() = 0;
	// Габариты фрагмента геометрии в объекте, показывающего информацию, которая отдаётся клиенту.
	// Если вернёт не S_OK, вычислю на основе getTargetGsMarker. Если и она не реализована,
	// использую габариты всего объекта.
	virtual HRESULT getTargetBounds(OUT mcsBoundBlock& bb) { return E_NOTIMPL; }
	// Графический маркер элемента геометрии, в котором отражена информация, отдаваемая клиенту.
	// Функция не нужна, если реализована getTargetBounds
	virtual int getTargetGsMarker() { return -1; }

	// Объект-сервер
	virtual mcsWorkID getSource() = 0;
	// Габариты фрагмента геометрии в объекте, показывающего принятую клиентом информацию.
	// Если не реализовать, вычислю на основе getSourceGsMarker. Если и она не реализована,
	// использую габариты всего объекта.
	virtual HRESULT getSourceBounds(OUT mcsBoundBlock& bb) { return E_NOTIMPL; }
	// Графический маркер элемента геометрии, показывающий принятую клиентом информацию.
	// Функция не нужна, если реализована getSourceBounds
	virtual int getSourceGsMarker() { return -1; }

	// Направление действия зависимости
	virtual McReferenceDirection getDirection() = 0;
	// Выражение, связывающее информацию сервера и клиента. Например, "Dr = rValDiameter/2"
	virtual McsString getExpression() { return _T(""); }

	// Зависимость можно удалить
	virtual bool Removable() { return false; }
	// Вернуть S_OK, если зависимость удалена
	virtual HRESULT Remove() { return E_NOTIMPL; }

	// Зависимость можно редактировать
	virtual bool Editable() { return false; }
	// Редактирование зависимости в диалоге. Вернуть S_OK, если что-то изменилось
	virtual HRESULT Edit(IN HWND hParent) { return E_NOTIMPL; }
};
typedef McsArray<IMcReferenceItemPtr, IMcReferenceItem*> IMcReferenceItems;

//---------------------------------------------------------------------------
// Гиперссылки объектов dwg формата
struct McHyperlink
{
	McsString stName;
	McsString stLocation;
	McsString stDescription;

	McHyperlink()
		{}
	MECHCTL_API McHyperlink(LPCTSTR stName, LPCTSTR stDescription, LPCTSTR stLocation = NULL);
	MECHCTL_API McsString getDisplayString();
	MECHCTL_API bool operator ==(const McHyperlink& link) const;
	MECHCTL_API bool operator !=(const McHyperlink& link) const;
};

//---------------------------------------------------------------------------
struct McHyperlinkArray : public McsArray <McHyperlink, const McHyperlink&>
{
	MECHCTL_API HRESULT write(IMcsStream* pS) const;
	MECHCTL_API HRESULT read(IMcsStream* pS);
	// Добавляет или перезаписывает существующую ссылку на NormaCS. SetNormacsLink(NULL, ...) - удаляет ссылку.
	MECHCTL_API void SetNormacsLink(LPCTSTR stName, LPCTSTR stDescription);
};

//==============================================================================

//Реализация в Gate

struct IMcDbEntity : public virtual IMcDbObject
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcDbEntity);
	IMCS_STD_METHOD_DEFINITION(IMcDbEntity, IMcDbObject);

	MECHCTL_API virtual void invalidate() override;

	virtual HRESULT  setLayer(LPCTSTR strLayer) = 0;
	virtual LPCTSTR  getLayer() = 0;
	virtual HRESULT  setColor(COLORREF color) = 0;
	virtual COLORREF getColor() = 0;
	virtual HRESULT  setLinetype(int iType) = 0;
	virtual int      getLinetype() = 0;
	virtual HRESULT  setLinetypeName(LPCTSTR stLT) = 0;
	virtual McsString getLinetypeName() = 0;
	virtual HRESULT  setLinetypeScale(double rScale) = 0;
	virtual double   getLinetypeScale() = 0;
	virtual HRESULT  setLineWeight(int iWeight) = 0;
	virtual int      getLineWeight() = 0;
	virtual const McHyperlinkArray& getHyperlinks() const = 0;
	virtual HRESULT setHyperlinks(const McHyperlinkArray& links) = 0;

		// скопировать свойства объекта(linetype, layer and etc.)
		// dwFlags - флаги из McMatchPropEnum
	virtual HRESULT  matchProperties(IMcDbEntity* pEntFrom, DWORD dwFlags = kMcMPropAll){return E_NOTIMPL;};

	virtual void     setScale(double rScale) = 0;
	virtual double   getScale() const = 0;
	virtual void     setDScale(double rScale) = 0;

		//масштаб приведения попугаев в миллиметры
	virtual double   getDScale() const = 0;
	virtual HRESULT  getTransform(OUT mcsMatrix& absTfm) = 0;
	virtual HRESULT  transform(IN const mcsMatrix& tfm) = 0;
	virtual HRESULT  getBoundingBox(OUT mcsBoundBlock &box) const = 0; 
	virtual HRESULT  getBoundingBoxOCS(OUT mcsBoundBlock& box) const = 0;

	virtual HRESULT  getOsnapPoints(
		McOsnapMode       osnapMode,
		const mcsPoint3d& pickPoint,
		const mcsPoint3d& lastPoint,
		mcsPoint3dArray&  snapPoints) const = 0;

	virtual HRESULT  getGripPoints(mcsPoint3dArray& gripPoints, bool bStretch) const {return E_NOTIMPL;}; 
	virtual HRESULT  getContextMenu(mcsCtxMenuItemArray& items) const = 0;
	virtual HRESULT  explode(IN OUT mcsGeomEntArray& geometry) const = 0;

	// opacity = 1 -> visible; = 0 -> invisible
	virtual HRESULT  setVisibility(IN double opacity) = 0;
	virtual double   getVisibility() const = 0;
	
	virtual HRESULT  highlight(bool bHighlight, COLORREF color = MCS_ENTCOLOR_BYDEFAULT) = 0;

	virtual HRESULT  getParamAtPoint(McGeometryParam& param, const mcsPoint& pnt) const
		{ return E_NOTIMPL; }

		// В pSimpleEnt вернется примитив с которого по параметру взята точка
	virtual HRESULT  getPointAtParam(mcsPoint& pnt, const McGeometryParam& param, OUT McsEntityGeometry* pSimpleEnt = NULL) const
		{ return E_NOTIMPL; }
	virtual HRESULT	 getNearestPoint(mcsPoint& pntNearest, const mcsPoint& pnt)
		{ return E_NOTIMPL; }

		//Это метод для обработки вставки объектов с содержащимися референсами в текстах, 
		//вызывать из ActiveEnt даже если селектированное id == WIDNULL, проверяет подходит ли обекn для референса, хайлайтит его
		//в конце вставки вызвать unhighlightAll. S_OK - новый объект и подходит. Если не референсов - E_FAIL, Если тот который был (даже если подходит) S_FALSE
		//Аргумент bool bHighlight добавлен, т.к. метод checkRefObject может применяться не из ActiveEnt, например при автоматической маркировке объектов.
	virtual HRESULT  checkRefObject(const mcsWorkID& id, bool bHighlight = true){return E_FAIL;}

	// Создание ссылок на другие объекты
	// Параметры в strFormat:
	// {{name}} - ссылка на свойство name объекта pFrom
	// {{1+{{name}}/2}} - то же самое, но значение свойства подставляется в формулу, а в текст попадает результат её вычислений.
	//                    На одну формулу - ссылка только на одно свойство, то есть вот так: {{{{D1}}+{{D2}}}} - работать не будет,
	//                    а вот так: {{{{D1}}+{{D1}}/2}} - будет.
	// {{%}}    - внедрить геометрию объекта pFrom
	// {{$}}    - внедрить объект pFrom
	//
	// Например:
	// pDbNote->FormatProperty(_T("McPropNoteString0"), _T("Швеллер {{Designation}} L = {{Ln}}"), pUBeam);
	virtual HRESULT  FormatProperty(LPCTSTR strPropName, LPCTSTR strFormat, IMcPropertySource* pFrom) { return E_NOTIMPL; }

	// хэлпер, выдаёт указатель на нужный интерфейс, управляющий всей идентификацией 
	// элементов топологии тела, если объект является врезным, то информация будет возвращена 
	// для всей группы тел, относящейся к родительскому
	MECHCTL_API virtual IMc3dFEVIDInfoPtr get3dIDInfo();

	//sysytem grips
	virtual HRESULT onGetGripPoints(McGripDataPtrArray& grips, double rViewUnitSize, int iGripSize, const mcsVector& vecViewDir, int iFlags) const
		{ return E_NOTIMPL; }

	virtual HRESULT onMoveGripPointsAt(const McGripDataPtrArray& grips, const mcsVector& offset, int iFlags)
		{ return E_NOTIMPL; }

	virtual HRESULT getCompoundTransform(OUT mcsMatrix& tfm) const {
		tfm.setToIdentity();
		return E_NOTIMPL;
	}

	enum
	{
		GetRef_All = 0x0,
		GetRef_OnlyID = 0x1,
		GetRef_OnlyOuter = 0x2,
	};
	virtual HRESULT GetReferenceItems(OUT IMcReferenceItems& refs, int Type = GetRef_OnlyID|GetRef_OnlyOuter){return E_FAIL;}

	// (isEditable == false) убирает пункт "Редактирование" из контекстного меню объекта.
	virtual HRESULT setEditable(bool isEditable)
		{ return E_NOTIMPL; }

		// DWG: the same meaning as for an invisible object due to ISOLATEOBJECTS command
	virtual bool isObjectHidden()
		{ return getVisibility() < 0.01; }

	// Для системных целей.
	// Требуется реализация в гейте для достижения максимальной скорости работы методов.
	// CID - маркер. Используется для привязок к объектам в блоках через mcsComplexWorkID.
	// Вместо ID объекта mcsComplexWorkID использует маркеры. Только такой способ идентификации
	//  объектов в блоке позволяет сохранить привязку к объекту в любых режимах клонирования.
	// 
	virtual bool _cplxIdMarker_get(OUT GUID& gdMarker) // ret = false | маркер = GUID_NULL -> нет маркера
		{ gdMarker = GUID_NULL; return false; }

	// Если указан pWantedMarker и он не GUID_NULL, то попытается установить указанное значение маркера.
	// Если не указано, сгенерирует новый. Вернет присвоенное значение.
	// В случае ошибки вернётся GUID_NULL.
	//
	virtual GUID _cplxIdMarker_assign(IN OPTIONAL const GUID* pWantedMarker = NULL)
		{ return GUID_NULL; }

	// Удалить маркер с объекта
	virtual bool _cplxIdMarker_delete()
		{ return false; }

	// Получение параметра точки на объекте,
	// если указана матрица проекции, то поиск выполняется с её учетом проекции.
	// Матрица проекции должна быть задана для плоскости XY, т.к. после проекции Z игнорируется.
	// (!) Матрица должна быть обратима.
	virtual HRESULT  getParamAtPoint(McGeometryParam& param, const mcsPoint& pnt, IN OPTIONAL const mcsMatrix* pXyProjTfm) const
		{ return E_NOTIMPL; }

	// Получение точек привязки с выбранной части объекта.
	// gsSelectionMark - идентификатор выбранного подобъекта.
	// pWorldToEyeTfm - матрица преобразования координат от пространства размещения объекта к видовому экрану.
	virtual HRESULT  getOsnapPoints(
		McOsnapMode                  osnapMode,
		IN McGSMarker                gsSelectionMark,
		IN OPTIONAL const mcsMatrix* pWorldToEyeTfm, // NULL
		const mcsPoint3d&            pickPoint,
		const mcsPoint3d&            lastPoint,
		OUT mcsPoint3dArray&         snapPoints) const
	{
		return E_NOTIMPL;
	}

	// Метод возвращает положение плоскости, в которой объект полностью лежит.
	// Если объект не плоский, то возвращается ошибка.
	virtual bool getPlane(OUT mcsPlane& objPlane) const{
		return false;
	}

	// Координатная система объекта
	virtual const mcsMatrix& GetOCS() const
	{
		return mcsMatrix::kIdentity;
	}
	virtual HRESULT SetOCS(const mcsMatrix& ocs)
	{
		return E_NOTIMPL;
	}

	// Метод должен вернуть true, если для объекта можно использовать оптимизацию записи ID в IMcsStream.
	MECHCTL_API virtual bool supportIdStreamOpt() const override;

	virtual HRESULT  setVisualStyleName(LPCTSTR strLayer) {
		return E_NOTIMPL;
	}

	virtual LPCTSTR  getVisualStyleName() const {
		return NULL;
	}

protected:
#ifdef _MCEYE
public:
#endif
	double m_rScale;
	double m_rDScale;//масштаб измерений
};

//==============================================================================
// Общий интерфейс к выноскам.
// Предназначен для упрощения вставки из кода выносок и других элементов оформления.
//
// Например:
// ISpdsLevelPtr pLevel = gpMcObjManager->createObject(IID_ISpdsLevel);
// IMcAnnotationPtr pAnn = pLevel;
// if (pAnn != NULL) {
//   pAnn->setTextEx(_T("L = {{Length}}"), m_pSink);
//   pAnn->setPosition(m_pntOrigin, m_pSink->ID());
// }

struct IMcAnnotation : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcAnnotation);
	IMCS_STD_METHOD_DEFINITION(IMcAnnotation, IMcObject);
	//Самый простой метод для вставки, если объект поддерживает Leader он его создаст, если нет, проигнорирует, добавляет в документ
	virtual HRESULT place(const mcsPoint& pntConnectTo, const mcsWorkID& idConnectTo, const mcsPoint& pntTextPos, LPCTSTR szText = NULL, const mcsWorkID& documentID = mcsWorkID())
		{ return E_NOTIMPL; }

	//Все сложные операции с множеством выносок надо делать через IMcBaseLeader добавив туда упрощенные методы!
	//
/*
	// Точки, на которые указывает выноска. В этих точках могут быть стрелки.
	// Менять тип стрелок нужно через интерфейс IMcArrowsExtension.
	virtual int getPositionCount() { return 1; }
	virtual HRESULT getPosition(
		OUT mcsPoint& pt,
		IN OPTIONAL int Index = 0                     // индекс выносной линии, от 0
	) = 0;

	// Некоторые объекты позволяют добавить выносную линию, указав Index = getPositionCount
	virtual HRESULT setPosition(
		IN const mcsPoint& pt,
		IN OPTIONAL int Index = 0,                    // индекс выносной линии, от 0
		// Если передать идентификатор объекта, выноска попытается создать геометрическую зависимость
		// своей выносной линии Index от точки pt на объекте idSnapTo.
		IN OPTIONAL const mcsWorkID& idSnapTo = mcsWorkID()
	) = 0;*/

	// Точка, определяющая положение тела выноски. Как именно определяется положение,
	// зависит от реализации.
	virtual mcsPoint getTextPos()
		{ return mcsPoint::kOrigin; }
	virtual HRESULT  setTextPos(IN const mcsPoint& pt)
		{ return E_NOTIMPL; }

	// Текст на полке
	virtual McsString getText() { return _T(""); }
	virtual void   setText(IN LPCTSTR str) { }

	// Аналог IMcDbEntity::FormatProperty для текста на полке. Позволяет не запоминать, как называется свойство.
	virtual HRESULT setTextEx(IN LPCTSTR strFormat, IN IMcDbEntity* pFrom) { return S_FALSE; }
	
	// Область покрытия объекта. То есть область, в которой не должно располагаться другой графики. Как правило
	// это зона под текстами, знаками и т.п. Первым будет вызван метод getCoverageArea(mcsPolylineArray&, mcsPolylineArray&).
	// В случае ошибки более простой метод - getCoverageArea(mcsBoundBlocksArray&).
	// Первый метод следует реализовывать, если область покрытия объекта отличается от его габаритов
	// (IMcEntity::getBoundingBox). Второй, если нужно учитывать непрямоугольные области покрытия или пустоты в покрытии.
	virtual HRESULT getCoverageArea(OUT mcsBoundBlocksArray& areas)
		{ return E_NOTIMPL; }
	virtual HRESULT getCoverageArea(OUT mcsPolylineArray& areas, OUT mcsPolylineArray& holes)
		{ return E_NOTIMPL; }
};

//=============================================================================

// Тип режима 3D моделирования
enum Mc3dModelingTypeEnum
{
	kMc3dModelingType_None =  0x00,
	kMc3dModelingType_Solid = 0x01, // твердотельное моделирование
	kMc3dModelingType_Sheet = 0x02, // листовое моделирование

	kMc3dModelingType_All = kMc3dModelingType_Solid | kMc3dModelingType_Sheet,
};
//==============================================================================

enum IMcEntityType
{
	kMcSimpleEnt =                0x00,
	kMcCoverEnt =                 0x01, // your entity can cover object, but cant be covered //fill m_DrawCache and m_aContoturs
	kMcCoveringEnt =              0x02, // your entity can cover object and can be covered //fill m_2dOriginalCache and m_aContoturs
	kMcCoveredEnt =               0x04, // your entity cant cover object, but can be covered //fill m_2dOriginalCache
	//kMcRefEnt =                 0x08, // entity is reference to another entity
	//kMcWorkCopyEnt =            0x10, // entity is work copy of another object, i.e. it's not the original but you can change it
	kMc_NoCache =                 0x20, // don't save m_DrawCache, call onDraw after reading
	kMc_AlienCd =                 0x40, // for custom objects without cache, updateCovering will called in updateGeometry
	//kMc_uGUID =                 0x80, // for custom objects without cache, updateCovering will called in updateGeometry
	kMc_UseViewDraw =            0x100, // don't save m_DrawCache, call onDraw after reading
	kMc3dHistoryItem =           0x200, // объект поддерживает интерфейс IMc3dHistoryItem, является элементом дерева 3D построений
	kMc3dSolid =                 0x400, // объект поддерживает IMc3dSolid, нужно для ускорения опроса объектов
	kMc3dPart =                  0x800, // объект является HostSolid в модели 3d-построения, при этом тоже должен быть флаг kMc3dSolid | kMc3dHistoryItem
	kMc3dAsmLvl =               0x1000, // в дополнение к kMc3dHistoryItem сообщает о том, что объект относится к сборочному контексту документа
	kMc3dConstr =               0x2000, // объект является 3D зависимостью, поддерживает IMc3dConstraint
	kMcDetailed3dMesh =         0x4000, // Графика объекта представлена идентифицируемыми mesh-примитивами в обертках Mc3dImage
	kMc3dSheetMetal =           0x8000, // Объект относится к листовым 3D-телам
	kMcSelectedGraphics =      0x10000, // Объект обладает дополнительной графикой, которая отображается при выделении объекта. Не сохраняется. Получение графики через IMcEntity::onSelectedDraw().
	kMcIsAssocVar =            0x20000, // Объект есть IMcAssocVariable, используется для оптимизации обсчета переменных для параметрического 3D
	kMcAddDrawCacheFor3dPart = 0x40000, // для 3D-солидов при отрисовке добавлять графику из DrawCache

	kMcCoveringMask = kMcCoverEnt | kMcCoveringEnt | kMcCoveredEnt,
};

//==============================================================================
// Флаги, отражающие причины изменения объекта.
// В файл не пишутся, значения можно менять.

enum McObjChangesTypeEnum
{
	// Флаги, отражающие общие типовые причины изменения объекта.
	// Значения, общие для всех объектов.

	kMcDbChanges__AddedForReset = 0x01, // системное значение, используется при сбросе данных флагов после рассылки ректоров

	kMcDbChangesType_Geom       = 0x02, // изменилась геометрия объекта
	kMcDbChangesType_Position   = 0x04, // изменилось положение объекта
	kMcDbChangesType_Reactors   = 0x08, // изменились реакторы
	kMcDbChangesType_Erasing    = 0x10, // удаление

	// Флаги, отражающие причины изменения объекта, в контексте приложения
	// разные типы объектов могут использовать одинаковые значения флагов.
	// (!) Не должны перекрываться с kMcDbChangesType_...

	// Variables
	kMcDbChangesType_Var_Value = 0x00000100,

	// KM View
	kMcEntChangesType_KM_View_ObjCnt                = 0x00000100,
	kMcEntChangesType_KM_View_DesignObjCnt          = 0x00000200,
	kMcEntChangesType_KM_CS                         = 0x00000400,
	kMcEntChangesType_KM_View_AsmNameChanged        = 0x00000800,

	// KM ObjInst
	kMcEntChangesType_KM_ObjInst_MarkNoteContents   = 0x00000100,

	// KM PlateInst
	kMcEntChangesType_KM_PlateInst_MarkNoteContents = 0x00000100,
};
//==============================================================================

enum IMcEventType
{
	kMcEvent_Regenerate    = 0x0001, //Если объект изменется(будет вызвано WriteEnabled, то будет вызвано onUpdate, onDraw)
	kMcEvent_ScaleChanged  = 0x0002, //Изменение масштаба в параметре "OldScale" старое значение мастаба
//	kMcEvent_AfterCreate   = 0x0004, //Вызывается сразу после создания пары объектов IMcXXX и IMcDbXXX. Объединён с kMcEvent_Def_Init
	kMcEvent_BeforeAdd     = 0x0008, //Вызывается до добавления в документ, для удобства
	kMcEvent_Duplicated    = 0x0010, //Вызывается для копии в методе getCopy, т.е одиночное копирование НЕ групповое, без сохранения связей (при копировании в среде или составе группы не приходит)
	kMcEvent_InPlace_Begin = 0x0020, //Начало in-place редактирования. В pAdditionalParameters параметр "rMarker" содержит gs-маркер редактируемого свойства
	kMcEvent_InPlace_End   = 0x0040, //Конец in-place редактирования. В pAdditionalParameters параметр "rMarker" содержит gs-маркер редактируемого свойства
	kMcEvent_Rebuild       = 0x0080, //Безусловно перестроить геометрию и т.п. Необходимо например после загрузки из шаблона группы. (для перестроения геометрии в стандартных, поскольку для них массив геометрии не сохраняется (много места занимает), т.е необходимо взвести флаги перестройки объекта)
	kMcEvent_Def_Init      = 0x0100, //Вызывается сразу после создания пары объектов IMcXXX и IMcDbXXX. Проинициализировать объект слоем, масштабом и прочими умолчаниями.
	kMcEvent_BeforeDelete  = 0x0200, //Перед удалением, ДО зануления синка! ничего важного тут не делать, очень аккуратно
	kMcEvent_InPlace_End_BeforeSet = kMcEvent_InPlace_End, //Конец in-place редактирования, до финального setProperty(). В pAdditionalParameters параметр "rMarker" содержит gs-маркер редактируемого свойства
	kMcEvent_InPlace_End_AfterSet  = 0x0400, //Конец in-place редактирования, после финального setProperty(). В pAdditionalParameters параметр "rMarker" содержит gs-маркер редактируемого свойства
	//kMcEvent_Transfered    = 0x0800,
	kMcEvent_ProjectChanged= 0x1000, //Изменился узел проекта, к которому присоединён объект.
	kMcEvent_DScaleChanged = 0x2000, //Изменение масштаба измерения в параметре "OldScale" старое значение мастаба
	kMcEvent_ConvertedFrom = 0x4000, //Подменён нативный класс объекта, в параметре "OldClass" старое имя нативного класса
	kMcEvent_AfterAdd      = 0x8000, //Вызывается сразу после добавления в документ
	kMcEvent_BeforeRemove  = 0x10000, // Вызывается перед изъятием из документа методом removeFromDocument
	kMcEvent_Custom        = 0x20000, // Специфические для объекта события
	kMcEvent_HandOverTo    = 0x40000, // Подмена объекта с сохранением идентификатора. В параметре "newobject" новый объект
	                                  // IMcEntity *pNewEnt = (IMcEntity*)(void*)*((LONG_PTR*)&value.val.m_num);
	kMcEvent_OCSChanged    = 0x80000, // ОСК изменилась.

	// (!) добавлять новые события в McEventExTypeEnum,
	// обрабатывать в onEventEx
};

//==============================================================================

enum McEventExTypeEnum
{
	// Событие вызывается после изменения ядром модифицирующих контуров объекта.
	// Необходимо обрабатывать в объектах, графика которых изменяется только при необходимости.
	// При получении события нужно привести объект в состояние, при котором на onDraw выполнится полное обновление графики.
	kMcEventEx_ModifyContoursChanged,

	// Cобытие вызывается после копирования объекта платформой (команда "copy", CtrlC+CtrlV).
	// При копировании через документ (CtrlC+CtrlV) событие вызывается после взрыва
	// блок референса, когда копия объекта переезжает в основной документ.
	// Дергать другие объекты в этом событии не желательно, лучше установить флажки и
	// потом обрабатывать в onUpdate.
	//
	// Параметры:
	//   wParam: const mcsWID2WIDMap* pOld2NewIds;
	//   lParam: const mcsWorkID* pOldID; (см описание "oldobjectid" выше)
	//
	kMcEventEx_Transfered,

	// Событие генерирутеся в момент подсветки объекта, либо в момент её снятия.
	//   wParam: bool     bHighlight;
	//   lParam: COLORREF color;
	kMcEventEx_onHighlight,

	// объект удален из глобального контейнера
	// wParam = 0, lParam = 0, не используются
	kMcEventEx_RemovedFromContainer,

	// Метод зовется в момент выполнения метода IMcDbObject::reload.
	// Используется для случаев, когда платформенно независимая часть объекта также обновляет часть своих данных из чертежа.
	kMcEventEx_Reload,

	// Вызывается для копии в методе getCopy, т.е одиночное копирование, НЕ групповое, без сохранения связей
	// (при копировании в среде или составе группы не приходит)
	// То же, что и событие kMcEvent_Duplicated, но с возможностью узнать, из какого объекта была создана копия.
	// lParam = IMcEntity* pSrcEnt
	kMcEventEx_Copied,
};

//==============================================================================
//аналогичный енум описан в src/OleServer/OleServer.idl
//называется McCOMPlaceObjectFlags
enum IMcPlaceObjectFlags //могут быть заданы несколько флажков
{
	kMcPlace_Normal         = 0x0,
	kMcPlace_Wout_Position  = 0x01,//Wout select position
	kMcPlace_Silent         = 0x02,//Wout dilogs
	kMcPlace_Wout_Params    = 0x04,//Wout select params
};

//==============================================================================
//аналогичный енум описан в src/OleServer/OleServer.idl
//называется McCOMEditObjectFlags
enum IMcEditFlags //могут быть заданы несколько флажков
{
	//флажки используются в методе getPropertyNameByGSMarker
	kMcInPlaceDefault        = 0x00,
	kMcInPlaceAllowRTF       = 0x01, // Объект поддерживает текст в rtf формате
	kMcInPlaceAllowMultiline = 0x02, // Объект поддерживает многострочный текст

	//флажки используются в методе onEdit
	kMcEditByDialog          = 0x100,
	kMcEditByPoint           = 0x200,//параметр pnt в onEdit валидный
	kMcEditOwnProcedure      = 0x400,//использовать собственную процедуру редактирования, игнорируя все переопределения
	// Users flags здесь каждый может разместить какой нить флажок или отдельно у себя
	kMcCustomizeAble         = 0x010000,//разрешает настройку диалога
	kMcHideSave              = 0x020000,//скрыть кнопку сохранения
	kMcPTSimpleEdit          = 0x040000,//упрощенный диалог редактирования без навигации
	kMcPTTemplateEdit        = 0x080000,//редактируем только шаблонные свойства объекта
	kMcEditCreating          = 0x100000,// Редактирование вызвано во время создания объекта.
};

//==============================================================================
struct ViewPortDraw
{
	mcsGeomEntArray  *pResult;
	__int64          iViewPortID;
	double           rViewPortScale;
	mcsVector        cameraView;
	bool             isViewport;
	mcsMatrix        tfm;
};
//==============================================================================
struct _McEntityBindDataBlock
{
	DECLARE_OBJ_NEWDEL;

	MECHCTL_API _McEntityBindDataBlock();

	IMcEntityPtr    mpTrgEnt; // Исходный Ent-объект (Target), заполнено для Ent-переключателя
	IMcEntityPtr    mpExtEnt; // Ent-расширение (Extension), заполнено для Ent-переключателя
	IMcEntityPtr    mpSwEnt;  // Ent-переключатель между расширением и основным объектом
	IMcEntityPtr    mpWrpEnt; // Ent-переадресатор с исходного Ent-объекта или Ent-расширения на Ent-переключатель

		// кол-ва бит должно быть >=, чем кол-во виртуальных методов в  IMcEntity
		// Если бит установлен но Wrapper вызывает оригинальный метод объекта из чего родной VTable
	mutable BYTE    mEntMethLockMask[8];
	DWORD_PTR*      mpOrigVT; // указатель на исходную VTable IMcEntity объекта
	DWORD_PTR*      mpWrpVT;  // указатель на VTable от Wrapper, нужен для освобождения памяти в деструкторе

	bool            mbIsWrapper;  // true, если mpParentEnt является Wrapper-ом, флаг для простоты дифференциации Wrp-данных
	bool            mbIsSwitcher; // true, если mpParentEnt является Switch-ром, флаг для простоты дифференциации Sw-данных

	struct Kinds
	{
		McKindOfDataOptArrPtr pKindOfDatas_beforeMerge; // поддерживаемые типы до последнего связывания
		Kinds*                pPrevKinds; // указатель на предыдущий набор поддерживаемых типов, используется при многоуровневом расширении
	} mKindsBeforeMerge;

	struct DataRefs
	{
		DWORD_PTR drawCache_ref_addr;
		DWORD_PTR lSysFlg_ref_addr;
		DataRefs* pPrevDataRefs;
	} mDataRefsBeforeBind;
};
//==============================================================================
struct _McEntityBindData
{
	DECLARE_OBJ_NEWDEL;

	// AGL: данные структуры сугубо системные, но открыты для доступа они для удобства отладки,
	// иначе если сделать Read-методы для защищенных полей, то для "хождения" по методам объекта
	// придётся утонуть в куче методов-хелперов, которые к тому же зовутся через макросы

	IMcEntity*      mpParentEnt; // указатель на родительскую IMcEntity
	bool            mbDbePtrInitialized; // true, если поле IMcEntity::m_pSinkDBE было проинициализировано

	mcsGeomEntArray m_DrawCache;    // ссылка mpParentEnt->m_DrawCache инициализируется этим полем
	mutable long    m__lSystemFlag; // ссылка mpParentEnt->m__lSystemFlag инициализируется этим полем

	// флаги до связывания на Entity, к которой расшириением цепляется mpParentEnt
	long m__lSystemFlag_dstBeforeBinding;

	_McEntityBindDataBlock* m_pData;

	MECHCTL_API static const int sOfsEntVT;

	MECHCTL_API _McEntityBindData(IMcEntity* pParentEnt);
	MECHCTL_API ~_McEntityBindData();

#define m__BD_isMethLocked(pEnt, idx) ( \
		(pEnt)->m__BD.m_pData->mpSwEnt.p && !(pEnt)->m__BD.m_pData->mbIsSwitcher ? \
			0 != ((pEnt)->m__BD.m_pData->mpSwEnt.p->m__BD.m_pData->mEntMethLockMask[(idx) / 8] & ( 1 << ( (idx) % 8 ))) : \
			0 != ((pEnt)->m__BD.m_pData->mEntMethLockMask[(idx) / 8] & ( 1 << ( (idx) % 8 ))) \
	)

#define m__BD_LockMeth(pEnt, idx) ( \
		(pEnt)->m__BD.m_pData->mpSwEnt.p && !(pEnt)->m__BD.m_pData->mbIsSwitcher ? \
			(pEnt)->m__BD.m_pData->mpSwEnt.p->m__BD.m_pData->mEntMethLockMask[(idx) / 8] |= ( 1 << ( (idx) % 8 )) : \
			(pEnt)->m__BD.m_pData->mEntMethLockMask[(idx) / 8] |= ( 1 << ( (idx) % 8 )) \
	)

#define m__BD_UnlockMeth(pEnt, idx) ( \
		(pEnt)->m__BD.m_pData->mpSwEnt.p && !(pEnt)->m__BD.m_pData->mbIsSwitcher ? \
			(pEnt)->m__BD.m_pData->mpSwEnt.p->m__BD.m_pData->mEntMethLockMask[(idx) / 8] &= ~( 1 << ( (idx) % 8 )) : \
			(pEnt)->m__BD.m_pData->mEntMethLockMask[(idx) / 8] &= ~( 1 << ( (idx) % 8 )) \
	)

// #define m__BD_isMethLocked(idx) \
// 	0 != (m__BD.mEntMethLockMask[(idx) / 8] & ( 1 << ( (idx) % 8 )))
// 
// #define m__BD_LockMeth(idx) \
// 	m__BD.mEntMethLockMask[(idx) / 8] |= ( 1 << ( (idx) % 8 ))
// 
// #define m__BD_UnlockMeth(idx) \
// 	m__BD.mEntMethLockMask[(idx) / 8] &= ~( 1 << ( (idx) % 8 ))

// #define m__BD_isMethLocked_s(idx) \
// 	0 != (m__BD.mpSwEnt.p->m__BD.m_pData->mEntMethLockMask[(idx) / 8] & ( 1 << ( (idx) % 8 )))
// 
// #define m__BD_LockMeth_s(idx) \
// 	m__BD.mpSwEnt.p->m__BD.m_pData->mEntMethLockMask[(idx) / 8] |= ( 1 << ( (idx) % 8 ))
// 
// #define m__BD_UnlockMeth_s(idx) \
// 	m__BD.mpSwEnt.p->m__BD.m_pData->mEntMethLockMask[(idx) / 8] &= ~( 1 << ( (idx) % 8 ))

	MECHCTL_API bool LockMethod(int idxMeth); // возвращает состояние блокировки "до"
	MECHCTL_API void UnlockMethod(int idxMeth);
	MECHCTL_API bool IsMethodLocked(int idxMeth) const;

	MECHCTL_API void PopMergedKinds(bool bAlsoRestoreInParent);
	MECHCTL_API void PushMergedKinds();

		// привязывает ссылочные данные this-объекта к данным объекта pEntTo
		// речь о m_DrawCache, m__lSystemFlag
	MECHCTL_API bool BindData(IMcEntity* pEntTo);
	MECHCTL_API bool UnbindData();

		// Освобождает память, использованную для связки объектов для расширения функционала
	MECHCTL_API void FreeBindData();

		// Добавляет в список поддерживаемый типов this-объекта все типы из объекта pFrom,
		// Если указать overwriteOffsets = true, то при совпадении типов будут обновлены смещения
		// в this на те, что в pFrom.
		// Если установлен флаг bNewLevel, то текущий набор типов будет сохранён в цепочке
	MECHCTL_API void MergeKindsFrom(IMcObject* pFrom, bool overwriteOffsets, bool bNewLevel);

	//................................................................................................

	MECHCTL_API static const int idx_writeEnabled;
	MECHCTL_API static const int idx_onDraw;
	MECHCTL_API static const int idx_onViewDraw;
	MECHCTL_API static const int idx_onWrite;
	MECHCTL_API static const int idx_onRead;
	MECHCTL_API static const int idx_onTransform;
	MECHCTL_API static const int idx_matchProperties;
	MECHCTL_API static const int idx_onEdit;
	MECHCTL_API static const int idx_placeObject;
	MECHCTL_API static const int idx_onErase;
	MECHCTL_API static const int idx_onExplode;
	MECHCTL_API static const int idx_onModifed;
	MECHCTL_API static const int idx_onUpdate;
	MECHCTL_API static const int idx_onReactor;
	MECHCTL_API static const int idx_onEvent;
	MECHCTL_API static const int idx_onEventEx;
	MECHCTL_API static const int idx_getTfm;
	MECHCTL_API static const int idx_getBoundingBoxOCS;
	MECHCTL_API static const int idx_onGetGripPoints_s;
	MECHCTL_API static const int idx_onMoveGripPointsAt_s;
	MECHCTL_API static const int idx_onGetGripPoints;
	MECHCTL_API static const int idx_onMoveGripPointsAt;
	MECHCTL_API static const int idx_onGetOsnapPoints;
	MECHCTL_API static const int idx_onGetContextMenu;
	MECHCTL_API static const int idx_getProperties;
	MECHCTL_API static const int idx_getProperty;
	MECHCTL_API static const int idx_setProperty;
	MECHCTL_API static const int idx_getPropertyInfo;
	MECHCTL_API static const int idx_deleteProperty;
	MECHCTL_API static const int idx_PR;
	MECHCTL_API static const int idx_GetRedefinitionSet;
	MECHCTL_API static const int idx_getStandard;
	MECHCTL_API static const int idx_getPropertyNameByGSMarker;
	MECHCTL_API static const int idx_canHaveReference;
	MECHCTL_API static const int idx_isFlexible;
	MECHCTL_API static const int idx_setScale;
	MECHCTL_API static const int idx_getScale;
	MECHCTL_API static const int idx_setDScale;
	MECHCTL_API static const int idx_getDScale;
	MECHCTL_API static const int idx_getAsPrimitive;
	MECHCTL_API static const int idx_setAsPrimitive;
	MECHCTL_API static const int idx_updateQueryLevel;
	MECHCTL_API static const int idx_getHighlightGeometry;
	MECHCTL_API static const int idx_getParamAtPoint;
	MECHCTL_API static const int idx_getPointAtParam;
	MECHCTL_API static const int idx_is3d;
	MECHCTL_API static const int idx_hasTextStyle;
	MECHCTL_API static const int idx_replaceTextStyle;

	MECHCTL_API static const int idx_getDependsOnArr;
	//MECHCTL_API static const int idx_getDependsOnSet;
	MECHCTL_API static const int idx_getAllDependsOnArr;
	//MECHCTL_API static const int idx_getAllDependsOnSet;
	MECHCTL_API static const int idx_doesDependOn;
	MECHCTL_API static const int idx_getDependentSet;
	//MECHCTL_API static const int idx_getDependentArr;
	MECHCTL_API static const int idx_getAllDependentArr;
	//MECHCTL_API static const int idx_getAllDependentSet;
	MECHCTL_API static const int idx_getCriticalDependsOn;
	MECHCTL_API static const int idx_getCriticalAllDependsOn;
	MECHCTL_API static const int idx_onGetExplodedGeometry;
	MECHCTL_API static const int idx_IsOCSSupported;
	MECHCTL_API static const int idx_supportIdStreamOpt;
};

//==============================================================================

// System only. 
// указатель на VTable IMcEntity, тип выражения - DWORD_PTR*&
#define mcEntVT(pEnt) (*(DWORD_PTR**)((LPBYTE)((IMcEntity*)pEnt) + _McEntityBindData::sOfsEntVT))

//==============================================================================
//Реализация в пользовательских модулях

struct IMcEntity : public virtual IMcObject
{
	//............................................................................
	// AGL, 24.04.2014
	// {{ Ent-Binding stuff
public:
	_McEntityBindData m__BD; // данные для связывания

		// Связывает this-объект с объектом-расширением pEntExtention через объект-переключатель pEntSwitcher,
		// Опционально позовёт onEvent(defInit) для расширения.
		// Объект-расширение позволяет доопределить функционал this-объекта без вмешательства в исходный код.
		// Что и как переопределять задаёт объект-переключатель. В общем случае для каждой пары this-ext
		// должен быть свой специфический переключатель.
		// Расширение работает только на множестве виртуальных методов интерфейса IMcEntity
	MECHCTL_API bool _bindExtention(IMcEntity* pEntExtention, IMcEntity* pEntSwitcher, bool bCallDefInitForExt);

		// выполняет процедуру, обратную _bindExtention, позвать можно для любого из объектов, участвующих в связке
	MECHCTL_API bool _unbindExtention();

		// Сообщает, участвует ли этот объект в расширении функционала
	MECHCTL_API bool _isBound() const;
	// }} Ent-Binding stuff
	//............................................................................

public:
	mcsGeomEntArray&  m_DrawCache;
	IMcDbObjectPtr    m_pSink;
	long&             m__lSystemFlag;

	// вспомогательный указатель;
	// если m_pSink поддерживает интерфейс IMcDbEntity, указатель будет не пуст;
	// инициализируется в IMcEntity::_onAppendGrpObjPtrs, сбрасывается в IMcEntity::_onResetGrpPtrs
	IMcDbEntity*      m_pSinkDBE;

public:

	IMCS_SYSTEM_IMPLEMENTATION;

	MECHCTL_API virtual void invalidate() override;

	// AGL: 29.04.2014, отпускание связанных объектов выполнено по новой универсальной схеме
	//MECHCTL_API virtual ULONG STDMETHODCALLTYPE Release();
	MECHCTL_API virtual HRESULT _onResetGrpPtrs() override;
	MECHCTL_API virtual HRESULT _onAppendGrpObjPtrs(IN OUT mcsMapMcObjToInt& ptrsSet, bool bForUnbind) override;

	MECHCTL_API virtual bool isKindOf(REFIID riid) const;

	// dwChangesFlags - набор флагов из McObjChangesTypeEnum
	MECHCTL_API virtual void writeEnabled(DWORD dwChangesFlags = 0);

	//вызывается на update для  заполнения кэша, в IMcDbObject, на завершение команды, на вызов UpdateAll в IMcObjectsManager
	virtual HRESULT onDraw(IMcGeometryBuilder *pGeometry){return E_NOTIMPL;};
	virtual HRESULT onViewDraw(ViewPortDraw& viewDraw){return E_NOTIMPL;};

	// Метод onWrite() должен всегда формировать валидный стрим,
	// который в дальнейшем сможет прочитаться методом onRead().
	// Код возврата метода onWrite() игнорируется платформой.
	virtual HRESULT onWrite(OUT IMcsStream* pStream) const = 0;
	virtual HRESULT onRead(IN IMcsStream* pStream) = 0;

	// (!) Методы для системных целей. Зовутся ДО и ПОСЛЕ записи данных только IMcEntity и её потомков.
	// Основное назначение: корректировать данные базовых классов вроде IMcEntity/IMcCdEntity перед записью.
	// Нужно, например, для обеспечения обратной совместимости данных объекта после рефакторинга его кода.
	virtual HRESULT _onWrite_before() const { return E_NOTIMPL; }
	virtual HRESULT _onWrite_after() const { return E_NOTIMPL; }

	//............................................................................
	//actions
	virtual HRESULT onTransform(IN const mcsMatrix& tfm) {return E_NOTIMPL;}; // трансформировать объект
	virtual HRESULT matchProperties(IMcEntity* pEntFrom, DWORD dwFlags) // скопировать свойства объекта, кроме местоположения
		{return E_NOTIMPL;} // dwFlags - флаги из McMatchPropEnum

		// вызов объекта на редактирование,
		//редактирование может быть выполнено через реактор 
	MECHCTL_API virtual HRESULT onEdit(IN const mcsPoint3d& pnt, long lFlag = 0);

		//в текущий документ, lInsertType - флажки для определения типа вставки, определяються для каждого типа объекта самостоятельно
		//например без диалогов и т.п., 0 - полная вставка
	virtual HRESULT placeObject(long lInsertType = kMcPlace_Normal, mcsExValueArray *pAdditionalParameters = NULL) {return E_NOTIMPL;}; // Вызываеться процедура вставки ЭТОГО объекта

	/// Событие на удаление объекта.
	/// (!) Если требуется удалить связанные объекты (от которых есть реакторы либо есть другая алгоритмическая связь),
	///    то удалять их можно двумя способами:
	///    1) прямо из из этого метода, но только если проверка McObjectManager.InGroupOperation(ID) == false;
	///       (будет true, например, если это удаление группы объектов с чертежа разом через команду Erase, Ctrl+X)
	///    2) отложенно на конец команды, в методе onErase надо в глобальной очереди запомнить объект для удаления
	///       и на конец команды (событие IMcEventsSink::OnCommand() или IMcEventsSink::OnCustomEvent(McCustomEventBeginUpdate) (приходит чуть позже))
	///       удалить пачкой все накопленные в очереди объекты.
	/// Если этим правилам не полседовать, то возможны несколько негативных сценариев:
	///    1) исключение на вложенный системный OnErase и отмена всей операции, как результат;
	///    2) зацикливание кода UpdateAll (10 проходов, затем блокировка с подвисшим недообновлённым состоянием);
	///    3) конфликт обновления реакторов на объектах в документе, как результат - сломанные persistent-реакторы.
	virtual HRESULT onErase(){return E_NOTIMPL;}; //реактор на удаление

	// вызывается в ответ на разбивку объекта командой EXPLODE.
	// Если вернуть E_ABORT, разбивка будет заблокирована.
	virtual HRESULT onExplode(IN OUT mcDbEntityArray& ents) { return E_NOTIMPL; }

	virtual HRESULT onModifed(bool isNew){return E_NOTIMPL;}; //реактор на изменение объекта

		//вызывается на update в IMcDbObject, на завершение команды, на вызов UpdateAll в IMcObjectsManager
	virtual HRESULT onUpdate(){return E_NOTIMPL;}; 

	virtual HRESULT onReactor(IMcDbObject *pObj, mcReactorsType action){return E_NOTIMPL;}; //реактор на срабатывание реактора
	virtual HRESULT onEvent(IMcEventType event, mcsExValueArray *pAdditionalParameters = NULL){return E_NOTIMPL;}; //реактор на различные события, например regenerate
	virtual HRESULT onEventEx(McEventExTypeEnum eventType, WPARAM wParam, LPARAM lParam) { return E_NOTIMPL; } // новый реактор на различные события, значение параметров зависят от типа события

	//get common info
	virtual HRESULT getTfm(mcsMatrix& tfm) const {return E_NOTIMPL;}; 
	virtual HRESULT getBoundingBoxOCS(OUT mcsBoundBlock &box) const {return E_NOTIMPL;}

	//grips
	virtual HRESULT onGetGripPoints(mcsPoint3dArray& gripPoints, bool bStretch) const {return E_NOTIMPL;}; 
	virtual HRESULT onMoveGripPointsAt(const mcsIntArray& indices, const mcsVector3d& offset, bool bStretch){return E_NOTIMPL;};
	virtual HRESULT onGetGripPoints(McGripDataPtrArray& grips, double rViewUnitSize, int iGripSize, const mcsVector& vecViewDir, int iFlags) const
		{ return E_NOTIMPL; }
	virtual HRESULT onMoveGripPointsAt(const McGripDataPtrArray& grips, const mcsVector& offset, int iFlags)
		{ return E_NOTIMPL; }

	//osnap
	virtual HRESULT onGetOsnapPoints(McOsnapMode osnapMode,  const mcsPoint3d& pickPoint, const mcsPoint3d& lastPoint,  mcsPoint3dArray& snapPoints) const {return E_NOTIMPL;}; 

	//context menu, bmpIndexes is optional
	virtual HRESULT onGetContextMenu(mcsCtxMenuItemArray& items) const {return E_NOTIMPL;}; 

	//............................................................................
	//properties
	virtual HRESULT getProperties(mcsStringArray& props) {props.RemoveAll(); return E_NOTIMPL;}
	virtual HRESULT getProperty(const McsString& stName, MCSVariant& data) {data.SetType(MCSVariant::kUndefined); return E_NOTIMPL;}
	virtual HRESULT setProperty(const McsString& stName, const MCSVariant& data) {return E_NOTIMPL;}
	virtual HRESULT getPropertyInfo(const McsString& stName, McPropertyInfo& info) {return E_NOTIMPL;}
	virtual HRESULT deleteProperty(const McsString& stName) {return E_NOTIMPL;}

	// Возвращает интерфейс для работы с параметрами, которые могут быть переопределены на объекте
	virtual IMcParameterRedefinition* PR() const
	{
		if(m_pSink.p)
			return m_pSink.p->PR(); 
		return NULL;
	}

	// Возвращает список идентификаторов параметров, которые потенциально могут быть переопределены на объекте
	virtual HRESULT GetRedefinitionSet(OUT mcsIntArray& paramIDs)
	{
		paramIDs.SetSize(0);
		return E_NOTIMPL;
	}

	// getStandard helper
	virtual MCS_STANDARD getStandard() const
		{ if(m_pSink.p) return m_pSink.p->getStandard(); return MCS_STD_GOST; }

	virtual HRESULT getPropertyNameByGSMarker(IN int iGSMarker, OUT McsString& name, OUT DWORD& dwFlags) { dwFlags = kMcInPlaceDefault; return E_NOTIMPL; }

	// Не нужно переопределять эти методы
	virtual void setScale(double rScale) {
		if(m_pSink.p) {
			IMcDbEntityPtr pDb = m_pSink;
			if(pDb.p)
				pDb.p->setScale(rScale);
		}
	}

	virtual double getScale() const {
		if(m_pSink.p) {
			IMcDbEntityPtr pDb = m_pSink;
			if(pDb.p)
				return pDb.p->getScale();
		}
		return 1;//gpMcStyleManager->GetCurrentScale();
	}

	virtual void setDScale(double rScale) {
		if(m_pSink.p) {
			IMcDbEntityPtr pDb = m_pSink;
			if(pDb.p)
				pDb.p->setDScale(rScale);
		}
	}

	virtual double getDScale() const {
		if(m_pSink.p) {
			IMcDbEntityPtr pDb = m_pSink;
			if(pDb.p)
				return pDb.p->getDScale();
		}
		return 1;//gpMcStyleManager->GetCurrentScale();
	}

	// Данные методы используются в командах trim и extend
	// get должен вернуть линию, дугу или полилинию
	// в set приходит тот же тип геометрии, который отдан в get, и
	// все изменения сводятся только к тому, что примитив удлиннён или укорочен с одного или обоих концов
	// pidsOnPrimitive - объекты лежащие на кривой. В setAsPrimitive придёт тот же масиив, который отдал getAsPrimitive().
	virtual HRESULT getAsPrimitive(OUT McsEntityGeometry& primitive, OUT mcsWorkIDArray* pidsOnPrimitive = NULL)
		{ return E_NOTIMPL; }
	virtual HRESULT setAsPrimitive(IN const McsEntityGeometry& primitive, IN const mcsWorkIDArray* pidsOnPrimitive = NULL)
		{ return E_NOTIMPL; }

	virtual long updateQueryLevel(){return 0;};

	virtual HRESULT getHighlightGeometry(OUT mcsGeomEntArray& ents)
		{ return E_NOTIMPL; }

	// При реализации этих методов имейте ввиду, что сторонние объекты будут хранить параметр
	// у себя. Поэтому однажды выданный параметр должен будет корректно отрабатываться на
	// протяжении всей дальнейшей жизни объекта.
	virtual HRESULT  getParamAtPoint(OUT McGeometryParam& param, IN const mcsPoint& pnt) const
		{ return E_NOTIMPL; }
	// В pSimpleEnt вернется примитив с которого по параметру взята точка
	virtual HRESULT  getPointAtParam(OUT mcsPoint& pnt, IN const McGeometryParam& param, OUT OPTIONAL McsEntityGeometry* pSimpleEnt = NULL) const
		{ return E_NOTIMPL; }

	virtual bool is3d() const {
		return 0 != (m__lSystemFlag & kMc3dHistoryItem);
	}

	// Проверяет, можно ли удалять реактор от объекта idFrom
	virtual bool canRemoveReactor(const mcsWorkID& idFrom)
		{ return true; }

	// Поддержка проверки стандартов (checkstandards)
	virtual bool hasTextStyle(const McsString& st) const
		{ return false; }
	virtual HRESULT replaceTextStyle(const McsString& stOld, const McsString& stNew)
		{ return E_NOTIMPL; }

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

		// Выдаёт список (неповторяющихся) ID объектов, от которых зависит состояние данного;
		// если fAutoReplaceSubentIdByParentId == true, то все SubEntID заменяет на
		// ID родительского объекта.
		// Если bRigidGeomDependsOnly = true, то объект не должен добавлять в набор объекты, которые не являются монолитной частью данного объекта,
		// то есть геометрию они определять могут, но при перемещении не должны двигаться вместе с this-объектом.
		// Реализация по умолчанию ничего ничего не делает.
	MECHCTL_API virtual HRESULT getDependsOn(OUT mcsWorkIDArray& idsDependsOn, IN OPTIONAL bool fAutoReplaceSubentIdByParentId = true, bool bRigidGeomDependsOnly = false) const;
	MECHCTL_API /*virtual*/ HRESULT getDependsOn(OUT mcsWorkIDSetEx& idsDependsOn, IN OPTIONAL bool fAutoReplaceSubentIdByParentId = true, bool bRigidGeomDependsOnly = false) const /*MCS_SEALED*/; // работает медленнее, по возможности не звать

		// выдаёт полный список всех объектов, от которых зависит,
		// состояние данного с учетом рекурсии;
		// Если bGetOrdered == true, элементы будут упорядочены в порядке их зависимости: от базовых к производным,
		// (!) установка bGetOrdered в значение true существенно замедляет работу методов.
		// Если bRigidGeomDependsOnly = true, то объект не должен добавлять в набор объекты, которые не являются монолитной частью данного объекта,
		// то есть геометрию они определять могут, но при перемещении не должны двигаться вместе с this-объектом.
	MECHCTL_API virtual HRESULT getAllDependsOn(OUT mcsWorkIDArray& idsDependsOn, bool bGetOrdered, bool bRigidGeomDependsOnly = false) const;
	MECHCTL_API /*virtual*/ HRESULT getAllDependsOn(OUT mcsWorkIDSetEx& idsDependsOn, bool bGetOrdered, bool bRigidGeomDependsOnly = false) const /*MCS_SEALED*/; // работает медленнее, по возможности не звать
	MECHCTL_API virtual bool    doesDependOn(IN const mcsWorkID& idObject) const;
	MECHCTL_API virtual bool    doesDependOn(IN const mcsWorkIDArray& idsObjects, OUT OPTIONAL mcsWorkID* pIdDepOn = NULL) const;

		// Выдаёт объекты, непосредственно зависящие от данного.
		// Реализация по умолчанию ничего ничего не делает
	MECHCTL_API virtual HRESULT getDependent(OUT mcsWorkIDSetEx& idsDependent) const;
	MECHCTL_API /*virtual*/ HRESULT getDependent(OUT mcsWorkIDArray& idsDependent) const /*MCS_SEALED*/; // работает медленнее, по возможности не звать

		// Выдаёт список всех объектов в документе, зависящих прямо или косвенно от этого.
		// Если bGetOrdered == true, элементы будут упорядочены таким образом, что последующие будут зависеть от предыдущих.
		// (!) установка bGetOrdered в значение true существенно замедляет работу методов
		// Реализация по умолчанию использует список реакторов для построения дерева зависимостей.
	MECHCTL_API virtual HRESULT getAllDependent(OUT mcsWorkIDArray& idsAllDependent, bool bGetOrdered) const;
	MECHCTL_API /*virtual*/ HRESULT getAllDependent(OUT mcsWorkIDSetEx& idsAllDependent, bool bGetOrdered) const /*MCS_SEALED*/; // работает медленнее, по возможности не звать

		// Пара методов ниже выполняет почти те же функции, что и getDependsOn и getAllDependsOn, но
		// в возвращаемый список объектов помещается то, без чего объект не сможет существовать.
		// И при удалении одного из перечисленных объектов удалится и этот.
		// Переопределение полезно в случае, когда объект включает в свой состав геометрию другого объекта,
		// и удаление включенного влечет не удаление этого, лишь его перестроение. Примеры таких объектов:
		// эскиз, массивы
	MECHCTL_API virtual HRESULT getCriticalDependsOn(OUT mcsWorkIDArray& idsDependsOn) const;
	MECHCTL_API virtual HRESULT getCriticalAllDependsOn(OUT mcsWorkIDArray& idsDependsOnOrdered) const;

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	// Дополнительная графика, выводимая при выделении объекта. Для объектов с флагом (m__lSystemFlag & kMcSelectedGraphics).
	// Возвращает S_OK, если pGeometryBuilder содержит всю необходимую графику объекта
	// Возвращает S_FALSE, если pGeometryBuilder содержит дополнительную графику объекта
	virtual HRESULT onSelectedDraw(IMcGeometryBuilder* pGeometryBuilder) { return E_NOTIMPL; }

	// Вызывается в ответ на вызов метода explode у IMcDbEntity, связанного через m_pSink
	virtual HRESULT onGetExplodedGeometry(IN OUT mcsGeomEntArray& geometry) const { return E_NOTIMPL; }

	// Метод зовется непосредственно перед выполнением процедуры удаления объекта,
	// Если по каким-то причинам объект нельзя удалять - это можно заблокировать, вернув 'false'.
	MECHCTL_API virtual bool onCanBeErased() const;

	// Метод возвращает, какие действия могут быть выполнены с объектом, если он R/O.
	// роезультат - комбинация флагов из McObjChangesTypeEnum
	virtual DWORD allowedActionsForReadonly() const { return 0; }

	// Координатная система объекта
	virtual bool IsOCSSupported() const
	{
		return false;
	}

	// Метод должен вернуть true, если для объекта можно использовать оптимизацию записи ID в IMcsStream.
	virtual bool supportIdStreamOpt() const {
		return false;
	}

	const mcsMatrix& GetOCS() const
	{
		IMcDbEntityPtr pDbEnt = m_pSink;
		if(pDbEnt)
			return pDbEnt->GetOCS();
		return mcsMatrix::kIdentity;
	}

	HRESULT SetOCS(const mcsMatrix& ocs)
	{
		IMcDbEntityPtr pDbEnt = m_pSink;
		if(pDbEnt)
			return pDbEnt->SetOCS(ocs);
		return E_FAIL;
	}

	friend struct IMcDbObject;
	friend class CDbObjectPrototype;

protected:
	MECHCTL_API IMcEntity();
	MECHCTL_API ~IMcEntity();
};
//==============================================================================
struct IMc3dConstraintCompatible : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dConstraintCompatible);
	IMCS_QI_METHOD_DEFINITION(IMc3dConstraintCompatible, IMcObject);

		// само наличие данного интерфейса у объекта не достаточно, для определения факта того, что на объект
		// допустимо накладывать 3D ограничения, нужно использовать данный метод.
		// Если вернёт false, объект не годится для наложения 3D-зависимостей
	virtual bool    canBeConstrained() const = 0;

		// Получить все наложенные на деталь 3D-зависимости
	virtual HRESULT getAttached3dConstraints(OUT mcsWorkIDArray& ids3dCtrs) const = 0;
};
//===========================================================================

#define CALL_ORIG_VIRT_METH_PROLOG(pSwEnt, idxMeth) \
{ \
	int __im = idxMeth; \
	IMcEntity* __pSwEnt = (IMcEntity*)(pSwEnt); \
	bool bMethWasLocked = m__BD_isMethLocked(__pSwEnt, __im); \
	if(!bMethWasLocked) \
		m__BD_LockMeth(__pSwEnt, __im); \
	_CALL_ORIG_VIRT_METH_PROLOG(__pSwEnt->m__BD.m_pData->mpTrgEnt.p, __im); \
	_CALL_ORIG_VIRT_METH_PROLOG(__pSwEnt->m__BD.m_pData->mpExtEnt.p, __im);

#define CALL_ORIG_VIRT_METH_EPILOG(actionOnFatal) \
	_CALL_ORIG_VIRT_METH_EPILOG(__pSwEnt->m__BD.m_pData->mpExtEnt.p, actionOnFatal); \
	_CALL_ORIG_VIRT_METH_EPILOG(__pSwEnt->m__BD.m_pData->mpTrgEnt.p, actionOnFatal); \
	if(!bMethWasLocked) \
		m__BD_UnlockMeth(__pSwEnt, __im); \
}

#define CALL_ORIG_VIRT_METH_EPILOG_V() \
	_CALL_ORIG_VIRT_METH_EPILOG_V(__pSwEnt->m__BD.m_pData->mpExtEnt.p); \
	_CALL_ORIG_VIRT_METH_EPILOG_V(__pSwEnt->m__BD.m_pData->mpTrgEnt.p); \
	if(!bMethWasLocked) \
		m__BD_UnlockMeth(__pSwEnt, __im); \
}

#define _CALL_ORIG_VIRT_METH_PROLOG(pEnt, idxMeth) \
	{ \
		int __idxMeth = idxMeth; \
		DWORD_PTR *pThisMeth = NULL, pPrevMeth = NULL; \
		if(pEnt && pEnt->m__BD.m_pData->mpOrigVT) { \
			pThisMeth = mcEntVT(pEnt) + __idxMeth; \
			DWORD_PTR* pOrigMeth = (pEnt)->m__BD.m_pData->mpOrigVT + __idxMeth; \
			pPrevMeth = *pThisMeth; \
			*pThisMeth = *pOrigMeth; \
		} \
		try{

#define _CALL_ORIG_VIRT_METH_EPILOG(pEnt, actionOnFatal) \
		} catch(...) {actionOnFatal;} \
		if(pThisMeth) { \
			pThisMeth = mcEntVT(pEnt) + __idxMeth; \
			*pThisMeth = pPrevMeth; \
		} \
	}

#define _CALL_ORIG_VIRT_METH_EPILOG_V(pEnt) \
		} catch(...) {} \
		if(pThisMeth) { \
			pThisMeth = mcEntVT(pEnt) + __idxMeth; \
			*pThisMeth = pPrevMeth; \
		} \
	}

//===========================================================================

// System use only, IMcEntity binding
// Объект-переходник. Его таблица виртуальных функций от IMcEntity подставляется в объекты,
// связываемые для расширения функционала. Каждый метод переадресовывает вызов в ent-переключатель, либо
// зовёт оригинальную функцию, в зависимости от вложенности вызова

// (!) Наследование НЕ виртуальное.
// Т.к. вызов в методы этого объекта приходит в контексте Ext или Target Entity,
// т.е. this указывает на IMcEntity расширения или целевого расширяемого объекта
// Если сделать наследование вируальным, то данные m__BD "расползутся".
// В данном же случае при обращении через this->m__BD мы получаем доступ к данным
// Ext/Target Entity, без искажений

struct _CMcEntBindWrapper : IMcEntity 
{
	_CMcEntBindWrapper() {
		m__BD.m_pData = new _McEntityBindDataBlock;
		m__BD.m_pData->mbIsWrapper = true;
	}

	MECHCTL_API virtual void    writeEnabled(DWORD dwChangesFlags = 0) override;
	MECHCTL_API virtual HRESULT onDraw(IMcGeometryBuilder *pGeometry) override;
	MECHCTL_API virtual HRESULT onViewDraw(ViewPortDraw& viewDraw) override;
	MECHCTL_API virtual HRESULT onWrite(OUT IMcsStream* pStream) const override;
	MECHCTL_API virtual HRESULT onRead(IN IMcsStream* pStream) override;
	MECHCTL_API virtual HRESULT onTransform(IN const mcsMatrix& tfm) override;
	MECHCTL_API virtual HRESULT matchProperties(IMcEntity* pEntFrom, DWORD dwFlags) override;
	MECHCTL_API virtual HRESULT onEdit(IN const mcsPoint3d& pnt, long lFlag) override;
	MECHCTL_API virtual HRESULT placeObject(long lInsertType, mcsExValueArray *pAdditionalParameters) override;
	MECHCTL_API virtual HRESULT onErase() override;
	MECHCTL_API virtual HRESULT onExplode(mcDbEntityArray& ents) override;
	MECHCTL_API virtual HRESULT onModifed(bool isNew) override;
	MECHCTL_API virtual HRESULT onUpdate() override;
	MECHCTL_API virtual HRESULT onReactor(IMcDbObject *pObj, mcReactorsType action) override;
	MECHCTL_API virtual HRESULT onEvent(IMcEventType event, mcsExValueArray *pAdditionalParameters) override;
	MECHCTL_API virtual HRESULT onEventEx(McEventExTypeEnum eventType, WPARAM, LPARAM) override;
	MECHCTL_API virtual HRESULT getTfm(mcsMatrix& tfm) const override;
	MECHCTL_API virtual HRESULT getBoundingBoxOCS(OUT mcsBoundBlock& box) const override;
	MECHCTL_API virtual HRESULT onGetGripPoints(mcsPoint3dArray& gripPoints, bool bStretch) const override;
	MECHCTL_API virtual HRESULT onMoveGripPointsAt(const mcsIntArray& indices, const mcsVector3d& offset, bool bStretch) override;
	MECHCTL_API virtual HRESULT onGetGripPoints(McGripDataPtrArray& grips, double rViewUnitSize, int iGripSize, const mcsVector& vecViewDir, int iFlags) const override;
	MECHCTL_API virtual HRESULT onMoveGripPointsAt(const McGripDataPtrArray& grips, const mcsVector& offset, int iFlags) override;
	MECHCTL_API virtual HRESULT onGetOsnapPoints(McOsnapMode osnapMode,  const mcsPoint3d& pickPoint, const mcsPoint3d& lastPoint,  mcsPoint3dArray& snapPoints) const override;
	MECHCTL_API virtual HRESULT onGetContextMenu(mcsCtxMenuItemArray& items) const override;
	MECHCTL_API virtual HRESULT getProperties(OUT MCSStringArray& props) override;
	MECHCTL_API virtual HRESULT getProperty(const McsString& stName, OUT MCSVariant& data) override;
	MECHCTL_API virtual HRESULT setProperty(const McsString& stName, IN const MCSVariant& data) override;
	MECHCTL_API virtual HRESULT getPropertyInfo(const McsString& stName, OUT McPropertyInfo& info) override;
	MECHCTL_API virtual HRESULT deleteProperty(const McsString& stName) override;
	MECHCTL_API virtual IMcParameterRedefinition* PR() const override;
	MECHCTL_API virtual HRESULT GetRedefinitionSet(OUT mcsIntArray& paramIDs) override;
	MECHCTL_API virtual MCS_STANDARD getStandard() const override;
	MECHCTL_API virtual HRESULT getPropertyNameByGSMarker(IN int iGSMarker, OUT McsString& name, OUT DWORD& dwFlags) override;
	MECHCTL_API virtual void    setScale(double rScale) override;
	MECHCTL_API virtual double  getScale() const override;
	MECHCTL_API virtual void    setDScale(double rScale) override;
	MECHCTL_API virtual double  getDScale() const override;
	MECHCTL_API virtual HRESULT getAsPrimitive(OUT McsEntityGeometry& primitive, OUT mcsWorkIDArray* pidsOnPrimitive) override;
	MECHCTL_API virtual HRESULT setAsPrimitive(IN const McsEntityGeometry& primitive, IN const mcsWorkIDArray* pidsOnPrimitive) override;
	MECHCTL_API virtual long    updateQueryLevel() override;
	MECHCTL_API virtual HRESULT getHighlightGeometry(OUT mcsGeomEntArray& ents) override;
	MECHCTL_API virtual HRESULT getParamAtPoint(OUT McGeometryParam& param, IN const mcsPoint& pnt) const override;
	MECHCTL_API virtual HRESULT getPointAtParam(OUT mcsPoint& pnt, IN const McGeometryParam& param, OUT OPTIONAL McsEntityGeometry* pSimpleEnt) const override;
	MECHCTL_API virtual bool    is3d() const override;
	MECHCTL_API virtual bool    hasTextStyle(const McsString& st) const override;
	MECHCTL_API virtual HRESULT replaceTextStyle(const McsString& stOld, const McsString& stNew) override;

	MECHCTL_API virtual HRESULT getDependsOn(OUT mcsWorkIDArray& idsDependsOn, IN OPTIONAL bool fAutoReplaceSubentIdByParentId = true, bool bRigidGeomDependsOnly = false) const override;
	//MECHCTL_API virtual HRESULT getDependsOn(OUT mcsWorkIDSetEx& idsDependsOn, IN OPTIONAL bool fAutoReplaceSubentIdByParentId = true, bool bRigidGeomDependsOnly = false) const override;
	MECHCTL_API virtual HRESULT getAllDependsOn(OUT mcsWorkIDArray& idsDependsOn, bool bGetOrdered, bool bRigidGeomDependsOnly = false) const override;
	//MECHCTL_API virtual HRESULT getAllDependsOn(OUT mcsWorkIDSetEx& idsDependsOn, bool bGetOrdered, bool bRigidGeomDependsOnly = false) const override;
	MECHCTL_API virtual bool    doesDependOn(IN const mcsWorkID& idObject) const override;
	MECHCTL_API virtual HRESULT getDependent(OUT mcsWorkIDSetEx& idsDependent) const override;
	//MECHCTL_API virtual HRESULT getDependent(OUT mcsWorkIDArray& idsDependent) const override;
	MECHCTL_API virtual HRESULT getAllDependent(OUT mcsWorkIDArray& idsAllDependent, bool bGetOrdered) const override;
	//MECHCTL_API virtual HRESULT getAllDependent(OUT mcsWorkIDSetEx& idsAllDependent, bool bGetOrdered) const override;
	MECHCTL_API virtual HRESULT getCriticalDependsOn(OUT mcsWorkIDArray& idsDependsOn) const override;
	MECHCTL_API virtual HRESULT getCriticalAllDependsOn(OUT mcsWorkIDArray& idsDependsOnOrdered) const override;

	MECHCTL_API virtual HRESULT onGetExplodedGeometry(IN OUT mcsGeomEntArray& geometry) const override;

	MECHCTL_API virtual bool IsOCSSupported() const override;

	MECHCTL_API virtual bool supportIdStreamOpt() const override;
};

//==============================================================================

// Entity-переключатель по-умолчанию. Все вызовы перенаправляет в Target-Entity,
// в обход Entity-расширения. Для расширения избирательных методов нужно пронаследоваться от
// этого объекта и описать те методы, которые должно отрабатывать расширение на Target-объекте

struct McEntBaseBindSwitcher : virtual IMcEntity
{
	McEntBaseBindSwitcher() {
		m__BD.m_pData = new _McEntityBindDataBlock;
		m__BD.m_pData->mbIsSwitcher = true;
	}

	MECHCTL_API virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvobj) override;
	MECHCTL_API virtual REFGUID getClassID() const override;
	//MECHCTL_API virtual bool    isKindOf(REFIID riid) const override;
	MECHCTL_API virtual REFGUID getImplementID() override;

	MECHCTL_API virtual void    writeEnabled(DWORD dwChangesFlags = 0) override;
	MECHCTL_API virtual HRESULT onDraw(IMcGeometryBuilder *pGeometry) override;
	MECHCTL_API virtual HRESULT onViewDraw(ViewPortDraw& viewDraw) override;
	MECHCTL_API virtual HRESULT onWrite(OUT IMcsStream* pStream) const override;
	MECHCTL_API virtual HRESULT onRead(IN IMcsStream* pStream) override;
	MECHCTL_API virtual HRESULT onTransform(IN const mcsMatrix& tfm) override;
	MECHCTL_API virtual HRESULT matchProperties(IMcEntity* pEntFrom, DWORD dwFlags) override;
	MECHCTL_API virtual HRESULT onEdit(IN const mcsPoint3d& pnt, long lFlag) override;
	MECHCTL_API virtual HRESULT placeObject(long lInsertType, mcsExValueArray *pAdditionalParameters) override;
	MECHCTL_API virtual HRESULT onErase() override;
	MECHCTL_API virtual HRESULT onExplode(mcDbEntityArray& ents) override;
	MECHCTL_API virtual HRESULT onModifed(bool isNew) override;
	MECHCTL_API virtual HRESULT onUpdate() override;
	MECHCTL_API virtual HRESULT onReactor(IMcDbObject *pObj, mcReactorsType action) override;
	MECHCTL_API virtual HRESULT onEvent(IMcEventType event, mcsExValueArray *pAdditionalParameters) override;
	MECHCTL_API virtual HRESULT onEventEx(McEventExTypeEnum eventType, WPARAM, LPARAM) override;
	MECHCTL_API virtual HRESULT getTfm(mcsMatrix& tfm) const override;
	MECHCTL_API virtual HRESULT getBoundingBoxOCS(OUT mcsBoundBlock &box) const override;
	MECHCTL_API virtual HRESULT onGetGripPoints(mcsPoint3dArray& gripPoints, bool bStretch) const override;
	MECHCTL_API virtual HRESULT onMoveGripPointsAt(const mcsIntArray& indices, const mcsVector3d& offset, bool bStretch) override;
	MECHCTL_API virtual HRESULT onGetGripPoints(McGripDataPtrArray& grips, double rViewUnitSize, int iGripSize, const mcsVector& vecViewDir, int iFlags) const override;
	MECHCTL_API virtual HRESULT onMoveGripPointsAt(const McGripDataPtrArray& grips, const mcsVector& offset, int iFlags) override;
	MECHCTL_API virtual HRESULT onGetOsnapPoints(McOsnapMode osnapMode,  const mcsPoint3d& pickPoint, const mcsPoint3d& lastPoint,  mcsPoint3dArray& snapPoints) const override;
	MECHCTL_API virtual HRESULT onGetContextMenu(mcsCtxMenuItemArray& items) const override;
	MECHCTL_API virtual HRESULT getProperties(OUT MCSStringArray& props) override;
	MECHCTL_API virtual HRESULT getProperty(const McsString& stName, OUT MCSVariant& data) override;
	MECHCTL_API virtual HRESULT setProperty(const McsString& stName, IN const MCSVariant& data) override;
	MECHCTL_API virtual HRESULT getPropertyInfo(const McsString& stName, OUT McPropertyInfo& info) override;
	MECHCTL_API virtual HRESULT deleteProperty(const McsString& stName) override;
	MECHCTL_API virtual IMcParameterRedefinition* PR() const override;
	MECHCTL_API virtual HRESULT GetRedefinitionSet(OUT mcsIntArray& paramIDs) override;
	MECHCTL_API virtual MCS_STANDARD getStandard() const override;
	MECHCTL_API virtual HRESULT getPropertyNameByGSMarker(IN int iGSMarker, OUT McsString& name, OUT DWORD& dwFlags) override;
	MECHCTL_API virtual void    setScale(double rScale) override;
	MECHCTL_API virtual double  getScale() const override;
	MECHCTL_API virtual void    setDScale(double rScale) override;
	MECHCTL_API virtual double  getDScale() const override;
	MECHCTL_API virtual HRESULT getAsPrimitive(OUT McsEntityGeometry& primitive, OUT mcsWorkIDArray* pidsOnPrimitive) override;
	MECHCTL_API virtual HRESULT setAsPrimitive(IN const McsEntityGeometry& primitive, IN const mcsWorkIDArray* pidsOnPrimitive) override;
	MECHCTL_API virtual long    updateQueryLevel() override;
	MECHCTL_API virtual HRESULT getHighlightGeometry(OUT mcsGeomEntArray& ents) override;
	MECHCTL_API virtual HRESULT getParamAtPoint(OUT McGeometryParam& param, IN const mcsPoint& pnt) const override;
	MECHCTL_API virtual HRESULT getPointAtParam(OUT mcsPoint& pnt, IN const McGeometryParam& param, OUT OPTIONAL McsEntityGeometry* pSimpleEnt) const override;
	MECHCTL_API virtual bool    is3d() const override;
	MECHCTL_API virtual bool    hasTextStyle(const McsString& st) const override;
	MECHCTL_API virtual HRESULT replaceTextStyle(const McsString& stOld, const McsString& stNew) override;

	MECHCTL_API virtual HRESULT getDependsOn(OUT mcsWorkIDArray& idsDependsOn, IN OPTIONAL bool fAutoReplaceSubentIdByParentId = true, bool bRigidGeomDependsOnly = false) const override;
	//MECHCTL_API virtual HRESULT getDependsOn(OUT mcsWorkIDSetEx& idsDependsOn, IN OPTIONAL bool fAutoReplaceSubentIdByParentId = true, bool bRigidGeomDependsOnly = false) const override;
	MECHCTL_API virtual HRESULT getAllDependsOn(OUT mcsWorkIDArray& idsDependsOn, bool bGetOrdered, bool bRigidGeomDependsOnly = false) const override;
	//MECHCTL_API virtual HRESULT getAllDependsOn(OUT mcsWorkIDSetEx& idsDependsOn, bool bGetOrdered, bool bRigidGeomDependsOnly = false) const override;
	MECHCTL_API virtual bool    doesDependOn(IN const mcsWorkID& idObject) const override;
	MECHCTL_API virtual HRESULT getDependent(OUT mcsWorkIDSetEx& idsDependent) const override;
	//MECHCTL_API virtual HRESULT getDependent(OUT mcsWorkIDArray& idsDependent) const override;
	MECHCTL_API virtual HRESULT getAllDependent(OUT mcsWorkIDArray& idsAllDependent, bool bGetOrdered) const override;
	//MECHCTL_API virtual HRESULT getAllDependent(OUT mcsWorkIDSetEx& idsAllDependent, bool bGetOrdered) const override;
	MECHCTL_API virtual HRESULT getCriticalDependsOn(OUT mcsWorkIDArray& idsDependsOn) const override;
	MECHCTL_API virtual HRESULT getCriticalAllDependsOn(OUT mcsWorkIDArray& idsDependsOnOrdered) const override;

	MECHCTL_API virtual HRESULT onGetExplodedGeometry(IN OUT mcsGeomEntArray& geometry) const override;

	MECHCTL_API virtual bool IsOCSSupported() const override;

	MECHCTL_API virtual bool supportIdStreamOpt() const override;
};

//==============================================================================

//Сегменты m_rZOrder, если объекты лежат в разных сегментах то, они вообще не пересекаются
//Сегменты от 0 через каждые 2000
#define SEGMENT_STEP         2000.0
#define NOT_CROSSED            -0.12345 // С таким значением не участвуют в пересечении
#define CROSS_ALL_SEGVENT  100000.0     // Объект со значением больше этого пересекают все за исключением NOT_CROSSED
#define LOWEST_SEGMENT    -100000.0     // Объект с этим значением ниже всех
#define HIGH_SEGMENT_BASE   20000.0     // Объект с значением больше этого выше всех нижележащих

#define kMcGeomExPropZOrder kMcGeomExPropLinetypeScale
//==============================================================================
//Contour type
#define CUT_CONTOURS                  1
#define HATCH_CONTOURS                5
#define SYS_CONTOUR_START_VAL        20
#define MODIFY_CUT_CONTOURS          25 // вырезание объектной графики и контуров подавления внутри контура
#define MODIFY_CUT_OUTSIDE_CONTOURS  30 // вырезание объектной графики и контуров подавления снаружи контура
#define ALL_SYS_CONTOURS            555

struct CHoledAreaArray;
//==============================================================================
//Covered Entity Sink
struct IMcCdEntity : public virtual IMcEntity
{
public:

	MECHCTL_API virtual void invalidate() override;

	//for custom cover update, you dont need to implement this method
	virtual HRESULT updateCovering(){return E_NOTIMPL;}

	//this method need for special objects, that not contain geometry in 2dDrawCache
	virtual HRESULT prepareToCover(){return E_NOTIMPL;};

	//is a Helper for multi contour actions
	bool isCutContour(int iContour)
	{
		return (iContour >= 0 && iContour < m_aContours.GetSize() && (m_aContours[iContour].color == CUT_CONTOURS || m_aContours[iContour].color == 0));
	}

	//получение контуров любых типов
	virtual HRESULT getContours(mcsGeomEntArray& arContours, int iContourType, mcsMatrix *pTfm = NULL)
	{
		HRESULT hRes = S_FALSE;
		for (int i = 0; i < m_aContours.GetSize(); i++)
		{
			const McsEntityGeometry& ent = m_aContours[i];

			if (ent.color == (unsigned int)iContourType || (iContourType == CUT_CONTOURS && ent.color == 0) ||
				(iContourType == ALL_SYS_CONTOURS && ent.color > SYS_CONTOUR_START_VAL))//Все системные
			{
				arContours.Add(ent);
				if (pTfm)
					arContours.Last().transformBy(*pTfm);
				hRes = S_OK;
			}
		}
		return hRes;
	}

	// удаление контуров любых типов
	virtual HRESULT clearContours(int iContourType = -1)
	{ //-1 - все несистемные
		//По умолчанию удаляем контура с цветом меньше 20 - контура для программистов, контура с более выскоми значениями - контура ядра
		unsigned int iCType2 = 537;//От потолка значение
		if (iContourType == 1)
			iCType2 = 0;

		for (int i = m_aContours.GetSize()-1; i >=0; i--)
		{
			if (iContourType == -1)
			{
				if (m_aContours[i].color < SYS_CONTOUR_START_VAL)
					m_aContours.removeAt(i);
			}
			else
			{
				if (m_aContours[i].color == (unsigned int)iContourType || m_aContours[i].color == iCType2)
					m_aContours.removeAt(i);
			}
		}
		return S_OK;
	}

	//............................................................................
	IMCS_STD_METHOD_DEFINITION(IMcCdEntity, IMcEntity);

	mcsGeomEntArray   m_2dOriginalCache,m_aContours;
	mcsWorkIDArray    m_aCrossed;
	
	// У объектов хранятся полилинии в m_aContours с меткой CUT_CONTOURS - внешние границы объекта,
	// и полилинии с меткой MODIFY_CUT_CONTOURS - полилинии, подрезающие графику объекта(команда trim).
	// Для реализации задачи #4486. "Показывать профиль через отверстие в пластине" завёл поле m_aObjectArea, 
	// которое хранит более подробную информацию о границах объекта.
	// Также исправится работа команды trim.
	// m_aObjectArea - это области объекта, которые не пересекаются, получены из полилиний m_aContours.
	// Не пишется в стрим.
	// m_aObjectArea вычисляется в applyModifyContours и используется при вычислении перекрытий объектов в CMcObjectsManager::updateCoveredGeometry().
	CHoledAreaArray m_aObjectArea;

	enum CoverType {
		kMcTransparent        = 0x1,   //Скрытые участки отображаются пунктиром
		kMcZContours          = 0x2,   //Контура имеют собственный ZOrder
		kMcDelCoincident      = 0x04,  //Резать наложившиеся линии
		kMcDontCutGeomObjects = 0x08,  //Не резать примитивы 
		kMcUseZLevel          = 0x10,  //Использовать ZLevel между деталями у которых включен этот флаг
		kMcDrawAsHidden       = 0x20,  //отображаются пунктиром
		kMcUseZ4Cover         = 0x40,  //Использовать ZOrder для kMcCoverEnt, по умолчанию не используется
		kMcUseEnableCross     = 0x80,  //Использовать 
		kMcWipeOut            = 0x100, //Отрисовывать растр цветом фона по контурам обрезания (как wipeout)
		kMcShowMContours      = 0x200, //Отображать контуры подрезки (MODIFY_CUT_CONTOURS/MODIFY_CUT_OUTSIDE_CONTOURS)
	};

	long           m_lCdModes;
	double         m_rZOrder, m_rZLevel;
	mcsDoubleArray m_rZOrders;

		//разрешить текущему объекту перекрыть pCrossed, и дать нужные контура для этого объекта
	virtual HRESULT chekEnableCross(IMcCdEntity* pCrossed, mcsGeomEntArray& contours){return E_NOTIMPL;};
	virtual HRESULT getCompoundBounds(mcsBoundBlocksArray& blocks) const {return E_NOTIMPL;};

protected:
	IMcCdEntity()
	{
		IMCS_REGISTER_THIS_IID_4KINDOF;
		m__lSystemFlag |= kMcCoverEnt;
		m_lCdModes = 0;
		m_rZOrder = m_rZLevel = 0;
	}
};
//===========================================================================

struct IMcZombie : public IMcEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcZombie);
};
//===========================================================================

enum mcsFilterEnum
{
	kMcsFilter_ByCLSID          = 0x1, // incompatible with kMcsFilter_ByKindOf
	kMcsFilter_ByBounds         = 0x2,
	kMcsFilter_ByDocs           = 0x4,
	kMcsFilter_ByKindOf         = 0x8, // incompatible with kMcsFilter_ByCLSID
	kMcsFilter_ByCurentDoc      = 0x10,//Curent Top Document
	kMcsFilter_ByCurentSheet    = 0x20,//Curent space (Modal_space, and etc)
	kMcsFilter_ByLayers         = 0x40,
	kMcsFilter_BySysFlags       = 0x80,
	kMcsFilter_IncludeInvisible = 0x100,
	kMcsFilter_IncludeUnsupported = 0x200, //include unsuported objects in objectids (for some special purposes)
	kMcsFilter_ByAlbumNodes			= 0x400,//По узлам альбома(раньше проекта) 
	kMcsFilter_ByProjectNodes   = 0x800,//Вернет все объекты имеющие ссылку на узел проекта
	kMcsFilter_GetCLSIDList			= 0x1000,//Специальный системный запрос, возвращает просто список CLSID объектов документа
	kMcsFilter_AllObjects       = 0x2000,//Все объекты документа.
	kMcsFilter_IncludeChilds    = 0x4000,// Включает в выборку дочерние объекты, не имеющие собственного тела.
	kMcsFilter_IncludeChildren = kMcsFilter_IncludeChilds,
	kMcsFilter_IsolatedOnly     = 0x8000,// Выборка только среди изолированных объектов
	kMcsFilter_FirstObjectOnly  = 0x10000,//Первый попавшийся объект в документе, удовлетворяющий условиям поиска.
	kMcsFilter_IgnoreWorkingSet = 0x20000,//Игнорировать набор объектов активного редактора вхождений (REFEDIT)
	kMcsFilter_ByPlane          = 0x40000,// Объект полностью лежит в заданной плоскости
	kMcsFilter_Force3DBounds    = 0x80000,// Сравнение по трёхмерных баундам
};

//==============================================================================
//Структура предназанчена для создания кэша выборок по боундбоксу.
//В дальнейшем getObjectByFilter будет учитывать ее наличие и искать в ней по боунду если она заполнена
//пока этого нет, в любом случае это потребует тщательного подхода и необходима для оптимизации большого числа запраосов
struct CBBoxUnit : public IMcObject
{
	CBBoxUnit(){
		bChanged = bBroken = false;
	}

	~CBBoxUnit(){//это будте только если вызывался метод init, НЕ НАДО его вызывать.
		//финальная зачистка, так эти флаги сбрасываются в updateCoveredGeometry, но в непересекшихся и до этого непересекавшихся объектах
		//они зависают
		if(pEnt)
			pEnt->m_pSink->m_lStatus &= ~(MCS_DB_CHANGED|MCS_DB_UNDO_SAVED);
	}

	DECLARE_OBJ_NEWDEL;

	mcsWorkID           id;
	mcsPoint            minPt, maxPt;
	CLSID               kindof;//Класс на который отозвался объект при фильтре isKindOf

	//Эти 2 поля инициалзируются вместе, если pEnt == NULL то и blk не валидный
	mcsBoundBlock       blk;//Это должен быть именно бблок,
	mcsBoundBlocksArray componoudBlocks;
	bool                bChanged;

private:
	IMcCdEntityPtr      pEnt;
	bool                bBroken;
	mcsWId2WIdMap       m_prev;

	friend class CMcObjectsManager;

	HRESULT init(bool bExist); //не надо это вызывать
	HRESULT getDiff(mcsWorkIDArray& away, mcsWorkIDArray* pCome);//не надо это вызывать
};

typedef MComPtr <CBBoxUnit> CBBoxUnitPtr;
//==============================================================================

struct CBBoxUnits : public McsArray <CBBoxUnitPtr, CBBoxUnit*>
{
	CBBoxUnits(){
		SetSize(0,200);
		m_bInted = false;
	}

	bool         m_bInted;

		//для систем котрые используют какой то временный контейнер, что бы освободить его по окончанию использования кэша
	IMcObjectPtr m_pTemp;
};

//==============================================================================
__inline bool operator > (CBBoxUnitPtr p1, CBBoxUnitPtr p2) {
	return (p1->minPt.x > p2->minPt.x);
}

//==============================================================================
__inline bool operator < (CBBoxUnitPtr p1, CBBoxUnitPtr p2) {
	return (p1->minPt.x < p2->minPt.x);
}

//==============================================================================
struct mcsFilter
{
	long           lMask;
	mcsGUIDArray   objClasses;
	bool           bExcludeIgnoredLayers; // dont found on ignored layers (MCS_LAYER_INVISIBLE and from parameters)
	bool           bExcludeInvisibleLayers; 
	long           lSysFlag;
	mcsBoundBlock  bounds;
	mcsWorkIDArray docsID;
	mcsStringArray layers;
	CBBoxUnits*    pBBoxes;
	mcsGUIDArray   nodesID;      // if empty, kMcsFilter_ByProjectNodes returns all objects attached to a project node
	mcsPlane       plane;// Используется в режиме kMcsFilter_ByPlane

	mcsFilter()
	{
		bExcludeIgnoredLayers = true;
		//[17:19:56] Michael V. Gladkikh: выключенные и замороженные слои должны игнорироваться всегда
		//поэтому по умолчанию делаем эту опцию включенной
		bExcludeInvisibleLayers = true;
		lMask = kMcsFilter_ByCurentSheet;
		pBBoxes = NULL;
	}
};
//==============================================================================

//Расширяя этот список добавляйте значения в McObjectManager::CommandMode в mapimgd
#define MC_GRIP_POPUP   0x1
#define MC_GRIP_STRETCH 0x2
#define MC_ERASE        0x4
#define MC_EXPLODE      0x8
#define MC_UNDO         0x10
#define MC_OPEN         0x20
#define MC_PASTE        0x40
#define MC_MOVECOPY     0x80
#define MC_COPY         0x100 // Копирование и вырезание в буфер
#define MC_TRIM         0x200
#define MC_DROPGEOM     0x400 // drag-перетаскивание объекта мышью
#define MC_SAVE         0x800
#define MC_QUICK_SELECT 0x1000
#define MC_BLOCK_OP     0x2000 // операции с внутренними блоками: NEWBLOCK / BEDIT / BCLOSE / BSAVE / INSERTBLOCK / PASTEBLOCK / WBLOCK
#define MC_QUIT         0x4000 // Выход из приложения
#define MC_XREF_OP      0x8000 // операции с внешними ссылками: REFEDIT / REFCLOSE / REFCLOSES / REFCLOSED
#define MC_CLONING_CMD  0x10000 // Команды, клонирующие объекты: MIRROR, ARRAY и т.д. Кроме перечисленных отдельно типа MC_COPY.
#define MC_CHANGE_SPACE 0x20000 // Команда смены пространства "chspace".
#define MC_ABORT        0x40000 // Отмена (abort) транзакции
#define MC_PUBLISH      0x80000// Пакетная печать
#define MC_BLK_OPS_MASK (MC_BLOCK_OP | MC_XREF_OP)

//==============================================================================
/// Множество флагов, индицирующих состояние объекта в очереди на обновление
enum McObjUpdQueStatus
{
	kMcObjUpdQueStatus_None    = 0,
	kMcObjUpdQueStatus_Added   = 1,
	kMcObjUpdQueStatus_Erased  = 2,
	kMcObjUpdQueStatus_Changed = 4,
	kMcObjUpdQueStatus_Covered = 8,
	kMcObjUpdQueStatus_InQUery = 16,
};
//==============================================================================
// Основной контейнер объектов.
// 
// Все операции надо объектами через этот интерфейс.
struct IMcObjectsManager
{
public:
//Objects registration
	// !!! stDatabaseClassName - имя dwg класса объекта, должно быть удобочитаемым и содержать только латинские
	// !!! буквы и цифры. Задаётся один раз и навсегда, то есть поддерживать однажды зарегистрированный
	// !!! dwg класс придётся всё время существования продукта. Будьте внимательнее с именами.
	// !!! stDatabaseClassNamePrefix - "PtDb" для объектов PlanTracer, для остальных задавать не надо.
#define PT_ARXCLASS_PREFIX _T("PtDb")
	virtual HRESULT registerClass(IN const GUID& classID, IN McsCreateClassObjectProc proc, LPCTSTR name = NULL, int iBmp = -1, LPCTSTR stDatabaseClassName = NULL, IN OPTIONAL LPCTSTR stDatabaseClassNamePrefix = NULL) = 0;
	virtual HRESULT unregisterClass(IN const GUID& classID) = 0;
	virtual HRESULT getClassName(OUT McsString& name, IN const GUID& classID) = 0;
	virtual HRESULT getClassByName(OUT GUID& classID, IN LPCTSTR szName) = 0;
	virtual int     getClassBmpIndex(IN const GUID& classID) = 0;

	//Objects creation
	//bSimpleCreate = true для создания обектов в момент загрузки, т.е. что бы никаких эвентов не посылалсь объекту и никаких дополнитлеьных действий не было
	virtual HRESULT createObject(IN const GUID& classID, OUT IMcObject** ppMcObj, bool bSimpleCreate = false) = 0;
	virtual IMcObjectPtr createObject(IN const GUID& classID, bool bSimpleCreate = false) = 0;

	//Container
	virtual HRESULT addObject(IMcObject* pMO) = 0;
	virtual HRESULT removeObject(const mcsWorkID& id) = 0;
	virtual HRESULT removeObject(const IMcObject* pMO) = 0;

	virtual HRESULT getObject(
		IN const mcsWorkID&     ObjId, 
		OUT void**              ppvObj, 
		IN OPTIONAL const GUID* pWishfulClassID=NULL) = 0;

	virtual IMcObjectPtr getObject(IN const mcsWorkID& ObjId) = 0;

	// (!) Для системных целей, не использовать безумно (!)
	// (!) возвращаемая ссылка НЕ имеет поднятый refCount (!)
	// очень быстрый метод получения объекта из контейнера;
	// не зовется ни одного QueryInterface, и никаких 
	// дополнительных проверок объекта не выполняется;
	// желательно использовать только для системных целей
	virtual IMcObject* _getObjectFast(const mcsWorkID& id) = 0;

		//Document operations
	virtual HRESULT addToDocument(IMcObject* pMDO, IMcDocument* pDoc = NULL) = 0; //by default in current document
	virtual HRESULT removeFromDocument(IMcObject* pMDO) = 0; // ..see IMcDbObject::removeFromDocument for more info

		//Operation on object by ID
	virtual HRESULT erase(IN const mcsWorkID& objID) = 0;
	virtual HRESULT highlightObject(IN const mcsWorkID& objID, COLORREF color = MCS_ENTCOLOR_BYDEFAULT) = 0;
	virtual HRESULT unHighlightObject(IN const mcsWorkID& objID) = 0;

	virtual HRESULT unHighlightAll() = 0;

		//highlight objIds, unhighlight previous
	virtual HRESULT highlightAuto(IN const mcsWorkIDArray& objIds, COLORREF color = MCS_ENTCOLOR_BYDEFAULT) = 0;

	virtual HRESULT ShowContours(const mcsPolylineArray& contours, HANDLE* pHandle = NULL, COLORREF color = MCS_ENTCOLOR_BYCONTEXT, int iWidthInPixels = 1)
		{ return E_NOTIMPL; }
	virtual HRESULT HideContours(HANDLE* pHandle = NULL)
		{ return E_NOTIMPL; }

	// opacity = 1 -> visible; = 0 -> invisible
	virtual HRESULT setVisibility(IN const mcsWorkID& objID, IN double opacity) = 0;
	virtual double getVisibility(IN const mcsWorkID& objID) = 0;

		//Notifications from Object (System )
	virtual void objectAppended(IN const mcsWorkID& objID, bool isMcObject = true) = 0;
	virtual void objectChanged(IN const mcsWorkID& objID, int iStatus = 0) = 0;
	virtual void objectErased(IN const mcsWorkID& objID, bool isMcObject = true) = 0;

		//callReactor(WID_NULL, id, kMcObjChanged); - будет транслировано на глобальный OnObjectChaged(WID_NULL в начале)
	virtual void callReactor(IN const mcsWorkID& objTo, IN const mcsWorkID& objFrom, mcReactorsType action) = 0;
	
	//............................................................................
	virtual HRESULT updateAll() = 0;
	virtual HRESULT cancelAll() = 0;

		//Selections
		// returns all avaluable objects in system by specific filter
	virtual HRESULT getObjectsByFilter(OUT mcsWorkIDArray& objects, IN  const mcsFilter& filter) = 0;

		// Format spec.: 
		// AS - active sheet
		// AD - active document
		// D - [mcsWorkID] - document/sheet id
		// C - [GUID] - implementation class GUID
		// K - [GUID] - supported interface kind
		// R - [McReferenceId] - refGroup ID
		// O - [GUID(output interface type), McsArray<typePtr,type*>* 
		//     (objects array of requested type)] -
		//     output is array of objects of specific type,
		//     NOTE! array must be empty before call
		// I - [mcsWorkIDArray*] - output is array of objects identifiers
		// N - pointers for objects will be received from internal container, not via 
		//     call to <getObject> (it will ensure that object will not be reloaded)
		// V - Only visible
		// CH - Include children objects
		// SF - [DWORD] filter by system flags (see IMcEntityType enum)
		// Example:
		// all leaders from specific document accept their DB interfaces
		//
		// McsArray<IMcLeaderPtr,IMcLeader*> leaders;
		// McsArray<IMcDbObjectPtr,IMcDbObject*> dbobjects;
		// getObjectsByFilter("DKOO", docID, IID_IMcLeader, 
		//                    IID_IMcLeader, &leaders, 
		//                    IID_IMcDbObject, &dbobjects);
	virtual HRESULT getObjectsByFilter(IN LPCTSTR format,...) = 0;

		// uses IMcObject::isKindOf interfaces filter if such is specified
	virtual HRESULT selectObjects(
		OUT mcsWorkIDArray& objects, 
		IN  bool            bSingle,  // true if single object required
		IN  LPCTSTR         strPromt = NULL,
		IN	const GUID*     pClsUID = NULL,
		// Для одиночной селекции - точка куда ткнули.
		// Не факт что лежит точно на объекте
		OUT mcsPoint*       pPnt = NULL,
		// Для одиночной селекции. Простая геометрия из объекта в месте тычка.
		OUT McsEntityGeometry* pSimpleEnt = NULL) = 0;

		// выбор объектов среди указанного множества.
		// в акаде по умолчанию работает через множественный выбор старым способом с последующей фильтрацией.
		// добавлено для множественной селекции рамкой в инвенторе, 
		// т.к. она возможна только по указанному множеству
	virtual HRESULT selectObjects(
		OUT mcsWorkIDArray& objects,
		IN  LPCTSTR         strPromt,
		IN const mcsWId2WIdMap& selectionSet) = 0; 

	virtual HRESULT getCurrentSelection(OUT mcsWorkIDArray &idsSelection) = 0;
	virtual long getCurrentCmdMode() = 0;

	// OperationGroup: Последний набор выбранных объектов.
	// Системно устанавливается только при изменении набора выбранных объектов (на событие SelectionChanged),
	// то есть при пользовательском выборе или любом другом программном изменении выбранного набора.
	// Например, после вызова AddToSelectionSet набор  OperationGroup будет содержать новую установленую селекцию.
	// Системно сбрасывается на конец команды, если селекция тоже была очищена, иначе остаётся "висеть".
	// Вручную программно можно устанавливать и сбрасывать методом setOperationGroup().
	//
	// При копировании/вставке считается, что группа глобальная и включает все объекты. Потому что операция копирования
	// сама выполняет все необходимые преобразования и нужно блокировать всю "самодеятельность" объектов.

	// Проверка, Участвует ли объект в групповой операции (erase/move/transform и т.д.)
	// (!) Проверять вхождение в группу нужно только этим методом, т.к. помимо факта попадания
	// в множество, дополнительно учитываются другие факоры, в зависимости от контекста выполняемого кода.
	//
	// Установка параметра bAlsoCheckSpecModes в false означает, что нужно игнорировать проверки
	// всяких особых режимов вроде копирования, блочных операций, и означает:
	// единственное, что надо проверить - это только факт вхождения данного ID в множество текуей группы объектов.
	//
	virtual bool inGroupOperation(const mcsWorkID& id, bool bAlsoCheckSpecModes = true) = 0;
	virtual void setOperationGroup(const mcsWorkIDArray& ids){};

	// (!) Метод использовать для получения набора объектов с целью его изменения.
	// (!) Для проверки, есть ли объект в наборе - использовать вызов inGroupOperation(id)
	virtual void getOperationGroupForModify(OUT mcsWorkIDArray& ids){};

	//Helpers

		//возвращает коллекцию обьектов по массиву ID
	virtual HRESULT getObjectsByIds(OUT mcObjectsArray& objects,  IN const mcsWorkIDArray&  ids) = 0;

		//копирует группу объектов с сохранением связей, скопированные обекты добавляются в objManager
	virtual HRESULT copyObjectsGroup(OUT mcsWorkIDArray&  idsOut, IN const mcsWorkIDArray&  idsIn) = 0;	
	
		// Helper
	virtual long getCurentSession() = 0; //return id of curent command
	virtual bool inCommandNow() = 0; 
	virtual bool crossingEnabled() = 0;

	virtual void Regenerate() = 0;
	virtual long raiseCurrentSession() = 0;
	virtual void setCurrentCmdMode(long cmd) = 0;
	virtual __int64 setUpdateTimeForObject(IN OPTIONAL IMcObject* pObj=NULL) = 0;
	virtual HRESULT addToCross(const mcsWorkIDArray&  objects, const mcsWorkID &idDoc) {return E_NOTIMPL;}	

		//Implementation, called from different modules
	virtual HRESULT setAndApplyModifyContours(IMcCdEntity* pCdEnt, const mcsGeomEntArray& arrNewMContours) {return E_NOTIMPL;}
	virtual HRESULT applyModifyContours(mcsGeomEntArray& arr, IMcCdEntity* pObjectWithContours) {return E_NOTIMPL;}	
	virtual HRESULT explodeCrossedEnts(IMcCdEntity* pCdEnt) {return E_NOTIMPL;}	

		// For system use only, for ex. from native gates
	virtual long lockReload() {return 0;}
	virtual long unlockReload() {return 0;}
	virtual long isReloadLocked() {return 0;}
	virtual long lockChanged(){return 0;}
	virtual long unlockChanged(){return 0;}

	// это для реализации вставки объектов в подсборку вместо активного по умолчанию;
	// добавлено для инвентора, но может еще гден-ть пригодится;
	// при каждом переключении false->true вызывает диалог выбора имени подсборки и после создания
	// все объекты будут "падать" в подсборку до следующего вызова true->false
	virtual HRESULT setSubAsmMode(bool fAddDefToSubasm, LPCTSTR cstrPredefinedSubAsmName = NULL) {return E_NOTIMPL;}

		// System. For internal use only.
	virtual HRESULT AddPropPair(LPCTSTR stSystem, LPCTSTR stLocal) {return E_NOTIMPL;}

		//Unique GUID support
	virtual IMcDbEntityPtr getObjectByGUID(const GUID& guid, IMcDocument* pDoc = NULL) = 0;//by default in current Top document
	virtual mcsWorkID getObjectIDByGUID(const GUID& guid, IMcDocument* pDoc = NULL){return WID_NULL;};//by default in current Top document

		// System. For internal use only.
	virtual HRESULT registerNativeObjectGUID(const GUID& guid) {return E_NOTIMPL;}

		// System. Renaming localized property names.
	virtual HRESULT NameLocalToSystem(McsString msLocal, McsString& msSystem) {msSystem = msLocal; return E_NOTIMPL;}
	virtual bool QuickKindOf(const mcsWorkID& id, const mcsGUIDArray& clsIds, const mcsWorkID* pDocumentId = NULL){return false;}
	virtual bool QuickKindOf(const mcsWorkID& id, const CLSID& cls, const mcsWorkID* pDocumentId = NULL){return false;}

	// регистрация рассылки реакторов указанного типа от указанного объекта
	virtual void callReactors(IN const mcsWorkID& objFrom, mcReactorsType action) = 0;

		// (!) Для системных целей, не использовать безумно (!)
		// (!) возвращаемая ссылка НЕ имеет поднятый refCount, т.к. в общем случае не известно, как её поднимать (!)
		// Методы выдают напрямую из контейнера, минуя все QueryInterface/reload
		// getDbObjFast - возвращает указатели из DB части объекта;
		// getEntObjFast - возвращает указатели из ENT части объекта;
		// Возвращаемый указатель имеет тип указанного во втором параметре интерфейса/класса;
		// (!) После получения указатель с типом отличным от возвращаемого преобразовывать
		// ОБЯЗАТЕЛЬНО только так:
		// ITypePtr pT = (IType*)(void*)_getEntObjFast(id, __uuidof(IType));
	virtual IMcDbObject* _getDbObjFast(const mcsWorkID& id, IN OPTIONAL const GUID& requiredPtrType = IID_IMcDbObject) = 0;
	virtual IMcEntity* _getEntObjFast(const mcsWorkID& id, IN OPTIONAL const GUID& requiredPtrType = IID_IMcEntity) = 0;

		// Копирует группу объектов с возможностью deep-clone, т.е. вытягивает за собой
		// все связанные через hard-ref-ID объекты.
		// если fDeepCopy == false, то работает как copyObjectsGroup;
		// если fDeepCopy == true, то в мэп pSrcToCloneMap (если указан)
		// заполнит отображение всех исходных объектов на их соответствующие клоны
	virtual HRESULT copyObjectsGroup2(
		OUT mcsWorkIDArray&          idsOut,
		IN const mcsWorkIDArray&     idsIn,
		IN OPTIONAL bool             fDeepCopy = true,
		OUT OPTIONAL mcsWId2WIdMap*  pSrcToCloneMap = NULL) = 0;

	virtual HRESULT registerClass(IN const GUID& classID, IN IMcObjFactory* pFactory) = 0;

	virtual bool isObjectInContainer(const mcsWorkID& objectID) = 0;

		// То же, что и updateAll, но обновляются только указанные объекты.
		// Реакторы посылаются только от них. Все остальные объекты остаются
		// в очереди на обносление в том же порядке, в каком и были;
		// Если указан lpszProcessName, то появится ProgressPar с этой подписью
	virtual HRESULT updateAllPartial(const mcsWorkIDSet& theseObjectsOnly, LPCTSTR lpszProcessName = NULL) = 0;

		// выдаёт список объектов, находящихся в режиме редактирования в данный момент
	virtual HRESULT getEditingObjects(OUT mcsWorkIDArray& idsEditingNow) = 0;
	virtual bool inUpdateProcess() = 0;

		/// Метод возволяет получить множество флагов, описывающих текущее состояние объекта,
		/// находящегося в очереди на обновление.
		/// Возвращается комбинация флагов множества McObjUpdQueStatus.
		/// Объект попадает в очередь на обновление при создании/удалении/изменении.
		/// ОБъект уходит из очереди после вызова метода McObjectManager.UpdateAll()
	virtual DWORD getObjStatusInUpdateQueue(const mcsWorkID& idObj) = 0;

		// выдаёт упорядоченный список объектов, находящихся в данынй момент на обновлении
	virtual HRESULT getUpdaingObjects(OUT mcsWorkIDArray& idsUpdatingNow) = 0;

	enum ReorderOptions
	{
		kReorderOp_None = 0,

		// если указан, то выходной список не будет содержать того,
		// чего не было во входном
		// Default: не назначено, нужно в каждом месте использования решать, нужен или нет.
		kReorderOp_DoNotAddNew               = 1,

		// Если указан, то дополнительно отсортирует
		// объекты в порядке времени создания, порядок не-3d элементов сохранится.
		// Default: не используется
		kReorderOp_AlsoSortByCreationTime    = 2,

		// Если указан, то родительский объект будет предшествовать дочернему,
		// при этом если родительский по логике связей зависит дочернего,
		// то такая связь будет игнорирована.
		// Пример: эскиз логически зависит от переменных на размерах его геометрии,
		// но переменная является дочерней для эскиза.
		// Default: не используется
		kReorderOp_ForceParentChildRelation  = 4,

		// в месте установки порядка элементов нужен прежний алгоритм сортировки
		kReorderOp_SortAlgoV3                = 8
	};

		// idsResultOrder - выдаёт мап упорядоченных ID для обновления в прямом порядке;
		// Если fDoNotAddNew = false, может добавлять новые 3D элементы в список, 
		// т.к. они всё равно будут обновляться по зависимостям, даже если их нет изначально
		// в списке;
		// Допустимо передавать один и тот же объект в idsInitialOrder и в idsResultOrder
	virtual void reorderObjectsDueToTheirDepends(
		IN  const mcsWorkIDSetEx& idsInitialOrder,
		OUT mcsWorkIDSetEx&       idsResultOrder,
		IN DWORD                  dwOptions) // флаги из ReorderOptions
	{
		idsResultOrder = idsInitialOrder;
	}

	virtual void reorderObjectsDueToTheirDepends(
		IN  const mcsWorkIDArray& idsInitialOrder,
		OUT mcsWorkIDArray&       idsResultOrder,
		IN DWORD                  dwOptions) // флаги из ReorderOptions
	{
		idsResultOrder = idsInitialOrder;
	}

		// Метод отдаёт флаги всех текущих командных режимов.
		// Если, например, по время вставки из буфера выполняется чтение файла, то получим комбинацию режимов
		// MC_PASTE|MC_OPEN
		// Метод getCurrentCmdMode в отличие от этого возвращает лишь последний установленный режим.
		// в нашем примере это будет только MC_OPEN.
	virtual DWORD getAllCurrentCmdModes() = 0;

	// признак того, что в контейнер были добавлены объекты типа IMcAssocVariable
	// после старта или после последнего вызова setModelAssocVarsAdded(, false).
	virtual bool areModelAssocVarsAdded(const mcsWorkID& docID) = 0;
	virtual void setModelAssocVarsAdded(const mcsWorkID& docID, bool bNewVal) = 0;
};
//===========================================================================
struct McSessionObjectInfo
{
	//Стурктура для отслеживания изменения над всеми обектами - обжект менджерами и т.п.
	mcsWorkIDSetEx idsChanged, idsAppended, idsErased, idsChangedProjects;

	// false, если в ближайшем будущем ожидается как минимум ещё одно событие
	// McCustomEventUpdateTree (при этом, содержимое массивов с идентификаторами
	// может отличаться)
	// Такое может случаться, например, при выполнении updateAll() внутри команды.
	// Тогда после updateAll(), вызванных внутри команды, будет приходить событие
	// McCustomEventUpdateTree с флагом bIsFinal = false, а с флагом bIsFinal = true
	// оно придет после updateAll(), который вызовется на конец команды.
	bool bIsFinal;

	// true, если выполняется частичное обновление только указанных в idsChanged объектов
	// никакие другие в этот момент обновлены быть не могут через updateAll
	bool bPartialUpdate;

	McSessionObjectInfo()
		: bIsFinal(true)
		, bPartialUpdate(false)
	{
	}

	void reset()
	{
		idsChanged.RemoveAll();
		idsAppended.RemoveAll();
		idsErased.RemoveAll();
		idsChangedProjects.RemoveAll();
	}

	void appendInfo(const McSessionObjectInfo& from)
	{
		idsChanged |= from.idsChanged;
		idsAppended |= from.idsAppended;
		idsErased |= from.idsErased;
		idsChangedProjects |= from.idsChangedProjects;
	}
};

//==============================================================================
struct mcsComplexWorkID
{
	// AGL. 08.06.2018, вторая причина закрытия - #4960, необходимость актуализации перед доступом к 'mIdsObjects'
	// AGL: 24.10.2016, закрыто с целью обеспечения контроля за кэшированием targetId.
	// Причина закрытия: см. BT24428 и код в M3D по этой метке.
	//
protected:

		// (!) перед обращением звать _actualize()
	mutable mcsWorkIDArray mIdsObjects;

	// cid-маркеры для объектов внутри блоков. Кол-во элементов на 1 меньше чем mIdsObjects.
	// Для первого объекта в цепочке маркер не нужен, т.к. его ID всегда корректный.
	// Заполняется/меняется в методе syncBindingByMarkers.
	mutable mcsGUIDArray mMarkers;
	mutable long         mlSessionForMarkers;

		// сохраняется в стрим, v2.0
		// используется, если в пути есть ссылки внутрь Xref, иначе пуст
		// кол-во элементов меньше mIdsObjects.GetSize() на один.
		// каждый элемент - это хэндл объект в документа, который определяется предыдущим элементом (вставкой блока);
	mutable std::shared_ptr<mcsI64Array> mpXrefHandles; // заполняется в isXref() и в read()

		// если mIdsObjects_validationData не пуст и тут true, то данные mIdsObjects актуализированы;
		// если mIdsObjects_validationData пуст, значение 'mbActualizedForXref' не используется
		// в стрим НЕ пишется
	mutable bool mbActualizedForXref;

	// тип ссылки
	enum RefType
	{
		kUnexplored = 0,
		kNull,
		kSimple,
		kBref,
		kXref,
	};
	mutable RefType mRefType : 8; // "утоптать" в один байт

	McSubentIdData mSubentIdData;
	__int64        mTime; // время, когда было сохранено поле mSubentIdData, нужно для подмены ref-ключей

private:
		// закэшированный ID оконечного объекта / подобъекта(subent)
		// на запись в стрим принудительно приводится в актуальное состояние, чтобы на зачитывании
		// сохранить последнее корректное значение
		// (сделано для BT24428)
	mutable mcsWorkID m__TargetId;

public:
	MCTYP_API mcsComplexWorkID();
	MCTYP_API mcsComplexWorkID(const mcsComplexWorkID&);
	MCTYP_API mcsComplexWorkID(const mcsWorkID& idObject, McSubentTypeEnum seType, McGSMarker gsMarker);
	MCTYP_API mcsComplexWorkID(const mcsWorkIDArray& idsObjects, McSubentTypeEnum seType, McGSMarker gsMarker);
	MCTYP_API mcsComplexWorkID(const McSubentId& seidSimple);

		// Метод устанавливает оконечный объект в цепочке (если bAlsoSetParentObjId = true) и данные subent из seidSimple
	MCTYP_API void setSubentPart(const McSubentId& seidSimple, bool bAlsoSetParentObjId = true);
	MCTYP_API void setSubentPart(const McSubentIdData& seData);

		// Объявлен с "explicit" для того, чтобы видеть, где используется полный ID, иначе неявные преобразования
		// будут скрывать потенциальные проблемные места при работе с блоками
	MCTYP_API explicit mcsComplexWorkID(const mcsWorkID& idSimple);

	MCTYP_API void setNull();
	MCTYP_API bool isNull() const;
	operator bool () const { return !isNull(); }
	bool IsNull() const { return isNull(); }
	MCTYP_API bool isSubent() const; // true if target is subentity, false if object
	MCTYP_API bool isSimple() const; // true if null or path contains only target object itself
	MCTYP_API bool isXref() const; // true if the path of IDs contains objects from various documents
	MCTYP_API bool isGUID() const;
	MCTYP_API McSubentTypeEnum subentType() const;

	MCTYP_API McsString getPathAsString() const; // composes and returns the sequence of IDs in the ID's path as a string

	MCTYP_API mcsComplexWorkID& operator = (const mcsComplexWorkID& cf);

		// initializes from object which is not in blockref
	MCTYP_API mcsComplexWorkID& operator = (mcsWorkID idSimple); // (!) специально без ссылки, чтобы можно было дать ID изнутри самого cplID
	MCTYP_API mcsComplexWorkID& operator = (const McSubentId& seidSimple);

	MCTYP_API const mcsWorkIDArray& objects() const;
	MCTYP_API mcsWorkIDArray& objects(); // сбрасывает закэшированный targetId()

	MCTYP_API const McSubentIdData& subentData() const;
	MCTYP_API McSubentIdData& setSubentData(bool bSetCurrentTimeMark = true); // сбрасывает закэшированный targetId()

		// returns id of last object/>Subent< in chain
	MCTYP_API mcsWorkID getTargetId() const; 

		// returns id of last >Object< in chain (not subent!)
	MCTYP_API mcsWorkID leafId() const;

		// returns id of 1'st object/subent in chain
	MCTYP_API mcsWorkID topId() const;

	MCTYP_API bool operator == (const mcsComplexWorkID& cw) const;
	MCTYP_API bool operator == (const mcsWorkID& cw) const;

	bool operator != (const mcsComplexWorkID& cw) const {
		return !operator==(cw);
	}

	bool operator != (const mcsWorkID& cw) const {
		return !operator==(cw);
	}

		// calculates overall transform for target object according to ids chain
		// Target obj space -> World space
	MCTYP_API bool getOverallTfm(OUT mcsMatrix& tgObj2WldTfm) const;

		// returns true if top blockId of one path present inside another path,
		// i.e. result is true if one complexId contains whole another or its part
		// Example 1:
		//   cplxId1: id1 id2 id3
		//   cplxId2: id2 id4
		//   result: true
		// Example 2:
		//   cplxId1: id1 id2 id3
		//   cplxId2: id5 id2 id4
		//   result: false
	MCTYP_API bool doesOneInvolveSomeOfOther(IN const mcsComplexWorkID& idFullOther) const;

		// returns true if both complexIds are complex and refers to the same top block
	MCTYP_API bool doesReferToTheSameBlock(IN const mcsComplexWorkID& idFullOther) const;

	MCTYP_API HRESULT write(IMtStream*) const;
	MCTYP_API HRESULT _write_v1(IMtStream* pS, WORD minor, const McSubentIdData* pSeDataToWrite) const;

	MCTYP_API HRESULT read(IMtStream*);
	MCTYP_API HRESULT _read_v1(IMtStream*, WORD minor);

		// Adds/removes reactor from all objects in the contained chain to the given obj,
	MCTYP_API bool addReactor(const mcsWorkID& idTo, bool fApplyNow = true) const;
	MCTYP_API bool removeReactor(const mcsWorkID& idTo, bool fApplyNow = true) const;
	MCTYP_API bool isYourReactor(const mcsWorkID& idFrom) const;

		// Находит idFrom в цепочке идентификаторов и заменяется его на idTo.
		// Если idFrom нет в цепочке - вернёт false
	MCTYP_API bool replaceIdInChain(const mcsWorkID& idFrom, const mcsWorkID& idTo);

	// Если id ссылается на объект во внешней ссылке,
	// Выполняет обновление в цепочке всех ID, которые относятся ко внешнему документу.
	// Если bForce = false, актуализация выполняется один раз после зачитывания данных.
	// Если bForce = false, актуализация выполняется принудительно,
	// Это может быть полезно в случае обновления данных загруженной внешней ссылки для
	// хранимого в памяти ID.
	// Возвращает true. если актуализация применима и была выполнена.
	//
	MCTYP_API bool actualizeForXref(bool bForce = false) const;

	// Выполняет синхронизацию маркеров привязок и ID объектов в цепочке.
	// Использовать нужно в двух сценариях.
	// 1. Для первичной привязки к объектам в блоках через маркеры.
	//    Для этих целей метод нужно обязательно звать один раз в момент инициализации привязки.
	//    В этом случае вставкам блоков в цепочке ID и целевому объекту присваиваются cid-маркеры,
	//    если они еще не были присвоены.
	// 2. Обязательно к вызову в точках кода, где выполняется обработка событий окончания
	//    копирования объектов с привязками к объектам в блоках.
	// 
	// Параметр pDbObjForWA - это объект, для которого нужно будет вызвать writeEnabled перед
	// тем, как будут изменены данные привязок/маркеров. По смыслу это объект, который хранит в себе
	// mcsComplexWorkID, для которого выполняется вызов данного метода.
	//
	MCTYP_API bool syncBindingByMarkers(IN OPTIONAL IMcDbObject* pDbObjForWA = NULL) const;

	// Вычисляет хэш для использования объекта в качестве ключа в хэщированных множествах.
	MCTYP_API UINT hash() const;

protected:
		// Выполняет актуализацию ссылок внутри блоков (через хэндлы, добавлено для #8481, #8567)
	MCTYP_API bool _actualize(bool bClearAtualizationData = false, bool bForce = false) const;
	MCTYP_API bool _actualize(bool bClearAtualizationData = true, bool bForce = false);
};
//==============================================================================

struct mcsComplexWorkIDArray : McsArray<mcsComplexWorkID>
{
	MCTYP_API HRESULT write(IMtStream*) const;
	MCTYP_API HRESULT read(IMtStream*);
	MCTYP_API void    getTopIds(OUT mcsWorkIDArray& topIds) const;
};
//==============================================================================

template <> __inline UINT __stdcall McsHashKey <const mcsComplexWorkID&> (const mcsComplexWorkID& cid)
{
	return cid.hash();
}
//==============================================================================


//==============================================================================
struct IMcSubentIdentification : public virtual IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMcSubentIdentification, IMcObject);

		// выдаёт существующее, если нет, то создаёт новое отображение
		// указанных данных Subentity на mcsWorkID
	virtual mcsWorkID GetSubentId(
		IN const mcsWorkID& idParent,
		IN McGSMarker       iGSMarker,
		IN McSubentTypeEnum eType) = 0;

	virtual mcsWorkID GetSubentId(
		IN const mcsWorkID&      idParent,
		IN const McSubentIdData& seData) = 0;

		// выдаёт существующее, если нет, то создаёт новое 
		// отображение указанных данных Subentity на mcsWorkID;
		// метод для FEV-subentities (Solid + Face/Edge/Vertex)
	virtual mcsWorkID GetFEVId(
		IN const mcsWorkID&   idSolid,
		IN const McFEVRefKey& FEVRefKey) = 0;

		// выдаёт существующее отображение указанного idSubent на данные subentity
	virtual mcsWorkID GetParentId(
		IN const mcsWorkID&              idSubent,
		OUT OPTIONAL McGSMarker*         piGSMarker = NULL,
		OUT OPTIONAL const McFEVRefKey** ppFEVRefKey = NULL,
		OUT OPTIONAL McSubentTypeEnum*   peType = NULL) = 0;

		// если указанная subentity является FEV-subentity, выдаёт RefKey для неё
	virtual mcsWorkID GetFEVParentId(
		IN const mcsWorkID&     idSubent,
		OUT const McFEVRefKey*& pFEVRefKey) = 0;

		// заменяет все subEntID в списке на ID IMcSolid, от которого непосредственно
		// зависит возникновение subEnt ID;
		// возвращает кол-во подменённых ID
	virtual int replaceSubentIDsByParentIDs(IN OUT mcsWorkIDArray& ids) = 0;
	virtual int replaceSubentIDsByParentIDs(IN OUT mcsWorkIDSetEx& ids) = 0; // то же, но для хэш-множества
	virtual int replaceSubentIDsByParentIDs(IN OUT mcsComplexWorkIDArray& ids) = 0;

		// выполняет очистку на уничтожение указанного документа
	virtual bool onDestroyDoc(IN const mcsWorkID& idDoc) = 0;

		// проверяет, является ли указанный ID subent
	virtual bool isSubent(const mcsWorkID& id) = 0;

		// если указанный ID есть subent, то выдает его системный составной идентификатор
	virtual bool getSubentDataByID(const mcsWorkID& id, OUT McSubentId& seid) = 0;

		// по указанному составному идентификатору выдаёт существующий ID для subent
	virtual bool getIDBySubentData(const McSubentId& seid, OUT mcsWorkID& id) = 0;

		// пытается выполнить замену ключа FEV для указанного идентификатора
	virtual bool setRefKeyForFEVId(
		const mcsWorkID&       idParent, // используется, если idFEV не присвоен
		const mcsWorkID&       idFEV,
		const McFEVRefKeyData& newRKD) = 0;
};

//==============================================================================
//////////////////////////////////////////////////////////////////////////

// Параметр для привязки к различным объектам. Позволяет однозначно
// получить по параметру точку и наоборот

struct McGeometryParam
{
protected:
		// if target is blockref then = WID_NULL
		// it's needed to prevent old code to work with blockrefs
	mcsWorkID        _id;

		// Used for geom-reference inside blockrefs.
		// If target is not in blockref then idComplex.mIdsObjects[0] ==id
	mcsComplexWorkID _idComplex;

public:
	__declspec(property(get = get_id)) const mcsWorkID id;
	MCTYP_API const mcsWorkID get_id() const { return _id; }

	__declspec(property(get = get_idComplex)) const mcsComplexWorkID idComplex;
	MCTYP_API const mcsComplexWorkID get_idComplex() const { return _idComplex; }

		// id of viewport, if object is in Paper Space,
	mcsWorkID        idViewport;

		// contains both: relative parameter on subgeometry and curve-inference type
	double           rParam;

		// User data. Db-impl doesn't use these. Always fills new with 0
	union {
		double  rData;
		__int64 iData;
	};

		// Used only as identifier for mcs-object's geometry (ex: in draw cache).
		// If target (ether in blockref or without it) refers to non-mcs object
		// then field is not used.
	int iGSMarker;

	//............................................................................

public:

		// type of coord system
		// (!) do not change order and relative values
	enum CoordSys
	{
		kTargetSpace, // if object is in block then coords in block's CS
		kModelSpace,
		kPaperSpace,  // the same as kModelSpace if there is no viewport
	};

	McGeometryParam() { purge(); }
	void setNull() { purge(); }
	MCTYP_API void purge();

	// См. комментарий к mcsComplexWorkID::syncBindingByMarkers.
	MCTYP_API bool syncBindingByMarkers(IN OPTIONAL IMcDbObject* pDbObjForWA = NULL) const;

	MCTYP_API bool operator == (const McGeometryParam&) const;
	bool operator != (const McGeometryParam& cw) const { return !operator==(cw); }

	MCTYP_API bool isEqualTo(const McGeometryParam& cw, double dtol = DEF_TOL) const;
	MCTYP_API bool isNull() const;
	bool isInViewport() const { return !idViewport.isNull(); }

	MCTYP_API McSubentTypeEnum getTargetSubentType() const;
	MCTYP_API bool isTargetSubent() const;

	MCTYP_API HRESULT write(IMcsStream* pStream) const;
	MCTYP_API HRESULT read(IMcsStream* pStream);

		// calculates point on target obj
	MCTYP_API HRESULT getPoint(
		OUT mcsPoint&          pnt,
		OUT McsEntityGeometry* pSimpleEnt = NULL,
		IN OPTIONAL CoordSys   csType = kPaperSpace) const;

		// helper, similar to getPoint(), on error drops message to IDM
	MCTYP_API mcsPoint point(CoordSys  csResType = kPaperSpace) const;

		// query simple target geometry (ex: specific segment of polyline will be returned instead of whole curve)
		// geom returned in World space coords
	MCTYP_API HRESULT getGeometry(
		OUT McsEntityGeometry& simpleGeomEnt,
		IN OPTIONAL CoordSys   csResType = kPaperSpace) const;

		// helper sinonym for getGeometry;
		// (!) try to avoid its usage to prevent numerous geom copying between temporary McsEntityGeometry objects
	MCTYP_API McsEntityGeometry _geometry(IN OPTIONAL CoordSys csResType = kPaperSpace) const;

		// returns id of target object/>Subent<
	MCTYP_API mcsWorkID targetId() const;

		// returns id of target object (not subent, parent will be ret for subent)
	MCTYP_API mcsWorkID leafId() const;

		// returns id of 1'st object/subent in chain
	MCTYP_API mcsWorkID topId() const;

	MCTYP_API void setId(const mcsWorkID&);
	MCTYP_API void setId(const mcsComplexWorkID&);

	MCTYP_API HRESULT init(
		IN const mcsComplexWorkID&   idObjComplex,
		IN const mcsPoint&           pt,
		IN OPTIONAL const mcsWorkID& idViewport = WID_NULL,
		IN OPTIONAL CoordSys         csPtType = kPaperSpace); // coord space for point

	MCTYP_API HRESULT init(
		IN const mcsWorkID&          idObj,
		IN const mcsPoint&           pt,
		IN OPTIONAL const mcsWorkID& idViewport = WID_NULL,
		IN OPTIONAL CoordSys         csPtType = kPaperSpace); // coord space for point

		// re-sets ref-point on the same target
	MCTYP_API HRESULT setPoint(
		const mcsPoint& pt,
		CoordSys        csPtType = kPaperSpace); // coord space for point

		// queries transformations W->T, T->W including compound and viewport transfoms
	MCTYP_API bool getTfm_WorldToTarget(OUT mcsMatrix& W2T) const;
	MCTYP_API bool getTfm_TargetToWorld(OUT mcsMatrix& T2W) const;

		// queries transform from one coord space to another
	MCTYP_API bool getRelTfm(OUT mcsMatrix& tfm, CoordSys csFrom, CoordSys csTo) const;

		// Adds/removes reactor from target to given obj,
		// supports block references
	MCTYP_API bool addReactor(const mcsWorkID& idTo, bool fApplyNow = true) const;
	MCTYP_API bool removeReactor(const mcsWorkID& idTo, bool fApplyNow = true) const;

		// helper allows to check reaction sender is from ids path;
		// use it in OnReactor callbacks if you set reactor to 'this'
	MCTYP_API bool doesReferToIdsPath(IMcDbObject* pReactorFrom) const;
};

typedef McsArray<McGeometryParam> McGeometryParamArray;

//==============================================================================
//В отчётах подсчет объектов, поддерживающих данный интерфейс, будет учитывать множители по ширине/длине/высоте
IMCS_DECL_INTERFACE(IMcMultiplicable, "{B1A531BA-F8E5-413D-BBF0-82A0739DDF93}");
struct IMcMultiplicable : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcMultiplicable);
	IMCS_QI_METHOD_DEFINITION(IMcMultiplicable, IMcObject);

	virtual int GetWidthRatio()  const { return 1; }
	virtual int GetLengthRatio() const { return 1; }
	virtual int GetHeightRatio() const { return 1; }
};

//==============================================================================
IMCS_DECL_INTERFACE(IMcXLSX, "{77BBBC3E-7F8A-4b74-8C5F-760CAC072716}");
struct IMcXLSX : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcXLSX);
	IMCS_QI_METHOD_DEFINITION(IMcXLSX, IMcObject);

	virtual HRESULT Open(LPCWSTR stXLSX) = 0;
	virtual McsString GetLastError() = 0;
	virtual HRESULT GetSheetDescriptions(mcsStringArray& stSheetDescriptions) = 0;
	virtual HRESULT Import(IMcTable2* pTable, LPCWSTR stXLSX) = 0;
};

//===========================================================================
MECHCTL_API bool McIsTransparentForHatchBoundary(IMcDbEntity* pEnt);

//===========================================================================
MECHCTL_API bool McUseOCS(IMcEntity* pEnt);

//===========================================================================
#if !defined(_NCAD_BUILD_) && !defined(_MCS_CORE_ONLY)
	#include "IMcObjectsInternal.h"
#endif
//===========================================================================
