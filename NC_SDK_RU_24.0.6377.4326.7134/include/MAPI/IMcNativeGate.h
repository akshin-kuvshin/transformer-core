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
#include "McsTempl.h"
#include "McsGeometry.h"
#include "McsParams.h"
#include "IMcObjects.h"
#include "imechanics.h"

struct IMcGeometryFilter;
struct IMcTheme;

//===========================================================================
#define mcsPlatformVer_Make(major,minor,sp) (((major&0xFF)<<24) | ((minor&0xFF)<<16) | ((sp&0xFF)<<8))
#define mcsPlatformVer_GetMajor(ver) ((ver&0xFF000000)>>24)
#define mcsPlatformVer_GetMinor(ver) ((ver&0xFF0000)>>16)
#define mcsPlatformVer_GetSP(ver)    ((ver&0xFF00)>>8)

//===========================================================================
struct mcsFilter;
struct mcsEmfParams;
class  CxImage;
struct MCS_Hole;
typedef McsArray<MCS_Hole,const MCS_Hole&> mcsHolesArray;
struct McDeferredOldEntity;
//===========================================================================
IMCS_DECL_INTERFACE(IMcArrayControl, "BB000001-0002-AAAA-AAAA-050B00000000")
struct IMcArrayControl : public virtual IMcObject
{
  IMCS_STD_METHOD_DEFINITION(IMcArrayControl, IMcObject);

  // <objectsIDs> - is set of objects created at first array position
  virtual HRESULT createArray(const mcsWorkIDArray& objectsIDs) = 0;
	virtual HRESULT selectPositions(
		IN OPTIONAL const mcsWorkID& idSample = mcsWorkID(), // временный объект для предпросмотра
		IN OPTIONAL HWND hParent = NULL                      // родительское окно
	) { return E_NOTIMPL; }
};
//===========================================================================
// added for easy synchronization of interface <-> implementation 
#ifndef NOTIMPL_ALERT_V
  #define NOTIMPL_ALERT_V(str) MESSAGE_FMT_A("Method " str " is not implemented",DBMON_FONT_DEFAULT, RGB(80,0,0));
#endif

#ifndef NOTIMPL_ALERT
  #define NOTIMPL_ALERT(str) MESSAGE_FMT_A("Method " str " is not implemented",DBMON_FONT_DEFAULT, RGB(80,0,0)); return E_NOTIMPL;
#endif

#ifndef NOTIMPL_ALERT2
  #define NOTIMPL_ALERT2(str,ret) MESSAGE_FMT_A("Method " str " is not implemented",DBMON_FONT_DEFAULT, RGB(80,0,0)); return ret;
#endif
//===========================================================================
struct McExportFileParams
{
	McsString stFileName;
	McsString stTemplateName;
	double rScale;
	HWND hParent;
	bool bExportAllObjects;
	bool bCreateFormat;
	bool bShowFormatDlg;
	bool bExplode;

	McExportFileParams()
	{
		bExportAllObjects = false;
		bCreateFormat = true;
		bShowFormatDlg = true;
		hParent = NULL;
		rScale = 1.0;
		bExplode = false;
	}
};
//===========================================================================
struct McMTextFragment
{
	mcsPoint location;            // Insertion point.
	mcsVector normal;             // Normal.
	mcsVector direction;          // Direction.
	McsString text;               // Text string.

	McsString font;               // SHX Font.
	McsString bigfont;            // SHX Bigfont.
	mcsPoint2d extents;           // Extents in OCS.
	double capsHeight;            // Height.
	double widthFactor;           // Width factor.
	double obliqueAngle;          // Obliquing angle.
	double trackingFactor;        // Tracking factor.
	bool vertical;                // Text is vertical.
	bool stackTop;                // Text is top of stacked text.
	bool stackBottom;             // Text is bottom of stacked text.

	bool underlined;              // Text is underlined.
	bool overlined;               // Text is overlined.
	mcsPoint underPoints[2];      // Underline endpoints.
	mcsPoint overPoints[2];       // Overline endpoints.

	McsString fontname;           // TrueType font name, or empty string.
	int charset;                  // TrueType character set.
	bool bold;                    // Text is bold.
	bool italic;                  // Text is italic.
	
	int idxAbsPos;                // Position in MText's content
	bool isField;                 // Text is field

	McMTextFragment()
	{
		normal = mcsVector::kZAxis;
		direction = mcsVector::kXAxis;
		capsHeight = widthFactor = obliqueAngle = trackingFactor = 0;
		vertical = stackTop = stackBottom = underlined = overlined = bold = italic = isField =false;
		charset = DEFAULT_CHARSET;
		idxAbsPos = -1;
	}
};
typedef McsArray<McMTextFragment, const McMTextFragment&> McMTextFragmentArray;
//==================================================================================================

#define MC_3D_PART_LIST_N_COL_TYPES 5

enum Mc3dPartListColumnTypeEnum
{
	kMc3dPartListValType_FileName,    // только короткие имена
	kMc3dPartListValType_Position,
	kMc3dPartListValType_Quantity,
	kMc3dPartListValType_Description, // значение всегда отдаётся без суффикса исполнения (даже для групповой спецификации)
	kMc3dPartListValType_PartNumber,
	kMc3dPartListValType_FullPath,
	kMc3dPartListValType_Mass,        // в кг на одну единицу, к которой относится запись в таблице
	kMc3dPartListValType_Notes,       // примечание
	kMc3dPartListValType_ImplNum,     // индекс исполнения, 0, 1,.. - для групповой спецификации; -1 - для спецификации без исполнений
	kMc3dPartListValType_PartNumberSuffix, // суффикс обозначения (исполнение детали) - для групповой спецификации
	kMc3dPartListValType_Format,      // Формат (см. #8811), по аналогии с "примечанием"
	kMc3dPartListValType_PositionZone, // получить зону позиционной выноски
	kMc3dPartListValType_CompRef,     // ссылки компонентов позиции, строки с разделителем ';'
	kMc3dPartListValType_AdditionalPartition, // дополнительный раздел
	kMc3dPartListValType_AlternativeQuantity, // Альтернативное количество
	kMc3dPartListValType_Material, // материал

	//...........

	// Блок св-в документа (для SW, #9007)
	kMc3dPartListValType_A_INV_N_PODL,        //_T("а_Инв_№_подл")         // MCS_PROP_DOC_ORIG_INV_N        // Инвентарный номер подлинника
	kMc3dPartListValType_A_P_INV_N_PODL_DATE, //_T("а_п_Инв_№_подл_Дата")  // MCS_PROP_DOC_ORIG_INV_N_DATE   // Дата инвентарного номера подлинника
	kMc3dPartListValType_A_VZAM_INV_N,        //_T("а_Взам_Инв_№")         // MCS_PROP_DOC_ORIG_INV_N_REPL   // Взамен инвентарного номера
	kMc3dPartListValType_A_INV_N_DUBL,        //_T("а_Инв_№_дубл")         // MCS_PROP_DOC_DUP_INV_N         // Инвентарный номер дубликата
	kMc3dPartListValType_A_P_INV_N_DUPL_DATE, //_T("а_п_Инв_№_дубл_Дата")  // MCS_PROP_DOC_DUP_INV_N_DATE    // Дата инвентарного номера дубликата
	kMc3dPartListValType_A_SPRAV_N,           //_T("а_Справ_№")            // MCS_PROP_DOC_REFERENCE         // Справочный номер
	kMc3dPartListValType_PERV_PRIMEN,         //_T("Перв_Примен")          // MCS_PROP_DOC_FIRST_USE         // Первичное применение
	kMc3dPartListValType_OBOZNACHENIE,        //_T("Обозначение")          // MCS_PROP_DOC_DESIGNATION       // Обозначение
	kMc3dPartListValType_NAIMENOVANIE,        //_T("Наименование")         // MCS_PROP_DOC_NAME              // Наименование
	kMc3dPartListValType_PREDPRIYATIE,        //_T("Предприятие")          // MCS_PROP_DOC_ENTERPRISE        // Предприятие
	kMc3dPartListValType_P_RAZRAB,            //_T("п_Разраб")             // MCS_PROP_DOC_AUTHOR            // Разработал
	kMc3dPartListValType_P_RAZRAB_DATE,       //_T("п_Разраб_Дата")        // MCS_PROP_DOC_AUTHOR_DATE       // Дата разработки
	kMc3dPartListValType_P_PROV,              //_T("п_Пров")               // MCS_PROP_DOC_CONTROL           // Проверил
	kMc3dPartListValType_P_PROV_DATE,         //_T("п_Пров_Дата")          // MCS_PROP_DOC_CONTROL_DATE      // Дата проверки
	kMc3dPartListValType_DOP_GRAFA,           //_T("Доп_графа")            // MCS_PROP_DOC_ADD_TEXT          // Доп. текст (Должность дополнительного контроля)
	kMc3dPartListValType_P_DOP_GRAFA,         //_T("п_Доп_графа")          // MCS_PROP_DOC_ADD_CONTROL       // Дополнительный контроль
	kMc3dPartListValType_P_DOP_GRAFA_DATE,    //_T("п_Доп_графа_Дата")     // MCS_PROP_DOC_ADD_CONTROL_DATE  // Дата дополнительного контроля
	kMc3dPartListValType_P_N_CONTR,           //_T("п_Н_контр")            // MCS_PROP_DOC_NORM_CONTROL      // Нормативный контроль
	kMc3dPartListValType_P_N_CONTR_DATE,      //_T("п_Н_контр_Дата")       // MCS_PROP_DOC_NORM_CONTROL_DATE // Дата нормативного контроля
	kMc3dPartListValType_P_UTV,               //_T("п_Утв")                // MCS_PROP_DOC_APPROVE           // Утвердил
	kMc3dPartListValType_P_UTV_DATE,          //_T("п_Утв_Дата")           // MCS_PROP_DOC_APPROVE_DATE      // Дата утверждения
	kMc3dPartListValType_P_T_CONTR,           //_T("п_T_контр")            // MCS_PROP_DOC_TECH_CONTROL      // Технический контроль
	kMc3dPartListValType_P_T_CONTR_DATE,      //_T("п_T_контр_Дата")       // MCS_PROP_DOC_TECH_CONTROL_DATE // Дата технического контроля
};
//==================================================================================================

enum Mc3dPartListRowTypeEnum
{
	kMc3dPartListRowType_Unk      = 0,
	kMc3dPartListRowType_StdPart  = 1,
	kMc3dPartListRowType_Part     = 2,
	kMc3dPartListRowType_Assembly = 3,
};
//==================================================================================================

// мета-индекс для ссылки на документ, для которого получена спецификация через интерфейс IMc3dPartListGate (для #9007)
#define PART_LIST_BOM_MAIN_DOC_IDX -100
//==================================================================================================

IMCS_DECL_INTERFACE(IMc3dPartListGate, "E00E00E0-0003-AAAA-AAAA-050B00000000");
struct IMc3dPartListGate : public virtual IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMc3dPartListGate, IMcObject);

		// для оптимизации звать перед пачкой вызовов Value
	virtual HRESULT   updateStart() { return S_FALSE; }
	virtual HRESULT   updateEnd() { return S_FALSE; }

	virtual HRESULT   get_NumberOfRows(OUT long* pNRows) = 0;
	virtual HRESULT   get_Value(IN int idxRow, IN Mc3dPartListColumnTypeEnum valType, OUT McsString& strVal) = 0;

		// если strSpecPartitionName != "", для определения раздела нужно использовать данное значение вместо rowType
	virtual HRESULT   get_RowType(IN int idxRow, OUT Mc3dPartListRowTypeEnum& rowType, OUT McsString& strSpecPartitionName) = 0;

	virtual HRESULT   put_Value(IN int idxRow, IN Mc3dPartListColumnTypeEnum valType, IN LPCTSTR strNewVal, IN OPTIONAL LPCTSTR strOldVal = NULL) = 0;
	virtual mcsWorkID getViewID() = 0;

		// Кол-во исполнений сборки, для которой построена связанная таблица BOM.
		// Нужно перекрывать реализацию только если код поддерживает групповые спецификации.
	virtual int       getNumImpls() { return 1; }

		// Получить полный путь к элементу спецификации по его ID
	MCTYP_API virtual McsString getBomItemFullPath(const mcsWorkID& idBomItem);

		// Получить ID объектов чертежа, соответствующих строке спецификации с указанным полным путём.
	virtual HRESULT getObjectsByBomItemFullPath(LPCTSTR itemFullPath, OUT mcsWorkIDArray& idsObjects) {
		return E_NOTIMPL;
	}

		// Метод удаляет объекты, связанные с указанной строкой спецификации.
		// Сама строка логически продолжает существовать в таблице до конца жизни объекта, связанного с интерфейсом IMc3dPartListGate
	virtual HRESULT   deleteObjectsLinkedToRow(IN int idxRow) {
		return E_NOTIMPL;
	}
};
//==================================================================================================

// Данные материала для EM-Std панели
struct EMSP_MaterialItem
{
	McsString m_name;
	DWORD     m_gateID;
};

typedef McsArray<EMSP_MaterialItem> EMSP_MaterialItemArray;

//==================================================================================================

struct IMcNativeGate
{
	IMcNativeGate()
	{
	}

	//Old stuff
	virtual HRESULT GetScaleFromPoint(OUT double& rScale, IN const mcsPoint3d& pnt)
		{ rScale = 1.0;return S_OK; }

	virtual HRESULT MCSExportToFile(IN const mcsWorkIDArray& aids, IN OUT McExportFileParams& params)
		{NOTIMPL_ALERT("IMcNativeGate::MCSExportToFile");}

	virtual HRESULT InsertFile(IN LPCTSTR strFileName, LPCTSTR stBlockName)
		{NOTIMPL_ALERT("IMcNativeGate::InsertFile");}

	// opens Bolt fastening placement selection dialog
	virtual HRESULT GetJointPlacement(
		IN OUT mcsHolesArray& Holes, 
		OUT IMcArrayControlPtr& pArrayPlacementControl) // if !=NULL then array placement can be used
	{
		NOTIMPL_ALERT("IMcNativeGate::GetJointPlacement");
	}

	// opens in-part object position selection dialog
	virtual HRESULT SelectInPartPosition(
		OUT MCS_Hole& IPPData, 
		OUT IMcArrayControlPtr& pArrayPlacementControl, // if !=NULL then array placement can be used
		IN OPTIONAL bool fInnerObject=true) 
	{
		NOTIMPL_ALERT("IMcNativeGate::SelectInPartPosition");
	}

	//Используется в Инвенторе, для обновления информации о поверхностях
	virtual HRESULT UpdateData4Holes(IN OUT mcsHolesArray& Holes, OUT IMcArrayControlPtr& pArrayPlacementControl)
		{ NOTIMPL_ALERT("IMcNativeGate::UpdateData4Holes"); }

	// directly calls edit command will all necessary command 'prolog' and 'epilog' actions
	virtual HRESULT DirectEdit(IN const mcsWorkID& objId, mcsPoint pnt = mcsPoint(-10000000, 0, 0))
		{ NOTIMPL_ALERT("IMcNativeGate::DirectEdit"); }

	// returns Inventor's data object which contains general INV application info for
	// INV's working level modules
	// use mcsPlatformVer_... macroses to resolve return value
	virtual DWORD getPlatformVersion()
		{ NOTIMPL_ALERT2("IMcNativeGate::getPlatformVersion",0) }

	virtual MCS_LangId getPlatformLang(OUT OPTIONAL WORD* pSysLangId = NULL)
	{
		if(pSysLangId) 
			*pSysLangId = 1033; 
		NOTIMPL_ALERT2("IMcNativeGate::getPlatformVersion", MCS_LANG_ENGLISH);
	}

	//Perfomance improvement
	// call before set visibility for a big group of objects with <true>
	// and then call with <false> after visibility is seted
	virtual HRESULT SetVisibilityProcessState(IN bool fBeginning)  // added to improve performance 
		{ NOTIMPL_ALERT("IMcNativeGate::SetVisibilityProcessState"); }

	// methods duplicated in IContext
	virtual HWND GetMainWnd() 
		{ NOTIMPL_ALERT2("IMcNativeGate::GetMainWnd",NULL); }

	virtual IEntityMonitor* GetEntityMonitor() 
		{ NOTIMPL_ALERT2("IMcNativeGate::GetEntityMonitor",NULL); }

	virtual IMcs3dConstraintsManager* Get3dConstraintsManager() 
		{ NOTIMPL_ALERT2("IMcNativeGate::Get3dConstraintsManager",NULL); }

	virtual IMcsProgress* GetProgress() 
		{ NOTIMPL_ALERT2("IMcNativeGate::GetProgress",NULL); }

	virtual IMcsGraphics* GetGraphics() 
		{ NOTIMPL_ALERT2("IMcNativeGate::GetGraphics",NULL); }

	virtual IMcTabManager* GetTabManager() 
		{ NOTIMPL_ALERT2("IMcNativeGate::GetTabManager",NULL); }

	virtual HRESULT Measure(
		OUT double&                          value,
		IN OPTIONAL LPCTSTR                  csPrompt,
		IN OPTIONAL McsMeasureTypeFilterEnum measureFilter)
	{
		value = -0.123456789;
		NOTIMPL_ALERT("IMcNativeGate::Measure");
	}

	virtual HRESULT RegisterCommand(IN mcsCmd& cmd) 
		{ NOTIMPL_ALERT("IMcNativeGate::RegisterCommand"); }

	virtual HRESULT ExecuteCommand(
		IN LPCTSTR              strCommand,
		IN OPTIONAL bool        bAutoPrefix = true,
		IN OPTIONAL MCSVariant* pCustomParams = NULL,
		IN OPTIONAL bool        bIsCmdOption = false)
	{
		NOTIMPL_ALERT("IMcNativeGate::ExecuteCommand");
	}

	virtual HRESULT CancelCurCommand() 
		{ NOTIMPL_ALERT("IMcNativeGate::CancelCurCommand"); }

	virtual HRESULT SelectObjects(
		OUT mcsWorkIDArray&    objects,
		IN  bool               bSingle,  // true if single object required
		IN  LPCTSTR            strPromt = NULL,
		OUT mcsPoint*          pPnt = NULL, // Для одиночной селекции - точка куда ткнули
		OUT McsEntityGeometry* pSimpleEnt = NULL) // Для одиночной селекции. Простая геометрия из объекта в месте тычка.
	{
		NOTIMPL_ALERT("IMcNativeGate::SelectObjects");
	}

	MCTYP_API virtual HRESULT SelectObjects(
		OUT mcsWorkIDArray& objects,
		IN  LPCTSTR         strPromt,
		IN const mcsWId2WIdMap& selectionSet);

	// Try to get an object from a gate
	// case 1 (old way): <refCtxObjId> is NULL: 
	//   try to locate an object with ID=<id>;
	// case 2 (AGL: a way for references): <refCtxObjId> is not NULL: 
	//   try lo locate (reference) of an object <id> in a context of existing 
	//   (reference) object <refCtxObjId>, if object is created/located, 
	//   its ptr will be returned
	//
	virtual IMcObjectPtr QueryObject(
		IN const mcsWorkID&          id,
		IN OPTIONAL const mcsWorkID& refCtxObjId = WID_NULL)
	{
		NOTIMPL_ALERT2("IMcNativeGate::QueryObject",UNKNULL);
	}

	//Try to get UCS system
	virtual HRESULT getUCSMatrix(mcsMatrix& ucs)
	{
		ucs.setToIdentity(); 
		return S_OK;
	}

	// create emf from native object
	virtual HRESULT createEmf(OUT HENHMETAFILE &hEmf, IN const mcsWorkID& id/*AcDbBlockReference*/, IN mcsEmfParams *pParams)
		{ NOTIMPL_ALERT("IMcNativeGate::createEmf"); }

	virtual HRESULT createEmf(OUT HENHMETAFILE &hEmf, IN const mcsWorkIDArray &ObjId, IN mcsEmfParams *pParams)
		{ NOTIMPL_ALERT("IMcNativeGate::createEmf"); }

	virtual HRESULT createEmf(OUT HENHMETAFILE &hEmf, IN mcsEmfParams *pParams)
		{ NOTIMPL_ALERT("IMcNativeGate::createEmf"); }

	virtual HRESULT crossedObject(IN const mcsWorkID& id)
		{ NOTIMPL_ALERT("IMcNativeGate::crossedObject"); }

	// used by IMcPainter for creating 3dGraphicsNodes
	virtual HRESULT create3dNode4Painter(
		IN const mcsWorkID&          idHostPainter,
		IN EntityGeometryTypeEnum    geometryType,
		OUT IMc3DGraphicsNodePtr&    pNode,
		IN OPTIONAL const mcsWorkID& idHostDocument = WID_NULL)
	{
		NOTIMPL_ALERT("IMcNativeGate::create3dNode4Painter"); 
	}

	// used by IMcPainter for connecting existing 3dGraphicsNodes
	virtual HRESULT bind3dNode4Painter(
		IN const mcsWorkID&       idHostPainter,
		IN IMcsStream*            pGraphicsContext,
		OUT IMc3DGraphicsNodePtr& pNode)
	{
		NOTIMPL_ALERT("IMcNativeGate::bind3dNode4Painter");
	}

	virtual HRESULT AddToSelectionSet(IN const mcsWorkIDArray& ids, IN OPTIONAL bool bNew = true)
		{ NOTIMPL_ALERT("IMcNativeGate::AddToSelectionSet(ids)"); }

	// use this method for selecting true subentities
	virtual HRESULT AddToSelectionSet(IN const mcsComplexWorkIDArray& ids, IN OPTIONAL bool bNew = true)
		{ NOTIMPL_ALERT("IMcNativeGate::AddToSelectionSet(complexIds)"); }

	// deletes object or/and objects
	virtual HRESULT DoDirectDelete(
		IN OPTIONAL const mcsWorkID& idObject = WID_NULL, 
		IN OPTIONAL mcsWorkIDArray* pIdsObjects = NULL)
	{
		NOTIMPL_ALERT("IMcNativeGate::DoDirectDelete");
	}

	virtual HRESULT RequeryObjects()
		{ return E_NOTIMPL; }
  
	virtual HRESULT CreateViewport(IN const mcsPolyline& contour, IN const mcsPoint& pntViewCenter, IN double rScale, IN OPTIONAL mcsWorkID* pidViewport = NULL, IN OPTIONAL IMcDocument* pDoc = NULL)
		{return E_NOTIMPL;}

	// Создаёт видовой экран.
	// S_FALSE - находимся в модели.
	// E_HANDLE - видовой экран источник не найден.
	virtual HRESULT CreateViewport(mcsWorkID& idViewport, const mcsPolyline& pline, double rScale, bool onlyInsert, LPCTSTR stLayer)
		{return E_NOTIMPL;}

	// rScale == 0 - не менять масштаб
	// ppline - контур, ставится до применения масштаба
	virtual HRESULT UpdateViewport(IN const mcsWorkID& idViewport, IN OPTIONAL double rScale, IN OPTIONAL mcsPolyline* ppline = NULL)
		{ return E_NOTIMPL; }

	virtual double GetDistanceToHatch(const mcsHatch& hatch, const mcsPoint& pnt)
		{ return MAX_REAL; }

	// Значения dwFlags в NativeUpdate()
	#define MCS_NUF_REDRAW_NOW 1

	virtual HRESULT NativeUpdate(IN const mcsWorkID& idObject, IN OPTIONAL DWORD dwFlags = 0)
		{ return E_NOTIMPL; }

	virtual HRESULT getMcsIdByNative(OUT mcsWorkID& id, IN LONG_PTR SomeId, bool bAddPairIfNotExist = true)
		{ return E_NOTIMPL; }

	virtual HRESULT getNativeIdByMcs(OUT LONG_PTR& SomeId, IN const mcsWorkID& id)
		{ return E_NOTIMPL; }

	virtual bool GetAcadIndexByRGB(IN COLORREF rgb, OUT USHORT& index)
		{ return false; }
	
	// Resolves object mcsWorkID by native object handle.
	// Handle must be unique and constant within document file.
	// For AutoCAD this handle is GUID where low 8 bytes is object's AcDbHandle.
	// Used by dimension chain calculations.
	virtual HRESULT GetWorkIdFromHandle(
		IN IMcDocument* pDoc,
		IN const GUID& Handle,
		OUT mcsWorkID& Result)
	{
		Result.setNull();
		return E_NOTIMPL;
	}

	virtual HRESULT GetHandleFromWorkId(
		IN const mcsWorkID& idObject,
		OUT IMcDocumentPtr& pDoc,
		OUT GUID&           Handle)
	{
		memset(&Handle, 0, sizeof(Handle));
		return E_NOTIMPL;
	}

	// returns native R/O paths
	virtual HRESULT GetLibraries(OUT mcsStringArray& libPaths) 
		{ libPaths.RemoveAll(); return E_NOTIMPL; }

	// получение визуального представления объекта;
	// <Image> содержит оптимизированный сгрупированный вид;
	// <tolerance_mm> указывает степень детализации картинки,
	//   если указано -1, то будет попытка получения картинки
	//   с существующим уровнем детализации;
	// <pDetailedImage> если указан, то объект будет разбит 
	//   на подкртинки, каждая из которых будет ссылаться на определенную 
	//   часть объекта, например ребра, поверхности;
	// <fIncludeIDInfo> если взведен, то в изображение будет включена 
	//   информация об идентификации объекта и его частей
	// <fLocalCS> (01.10.2015, AGL) определяет пространство координат, в котором будет отдано
	//   изображение; если true, то картинка будет отдана в локальных координатах объекта
	//
	virtual HRESULT GetImageForObject(
			const mcsWorkID&      idObject, 
			OUT CxImage&          Image,
			IN OPTIONAL double    tolerance_mm = -1,
			OUT OPTIONAL CxImage* pDetailedImage = NULL,
			IN OPTIONAL bool      fIncludeIDInfo = false,
			IN OPTIONAL bool      fLocalCS = false)
	{
		return E_NOTIMPL;
	}

	// Для спота. Вызывается чтобы поснимать реакторы с объектов, которые уже не перекрываются
	virtual HRESULT RemoveCrossed(IN const mcsWorkID& idFrom, IN const mcsWorkIDArray& ids)
		{ return E_NOTIMPL; }

	// Конвертация ТТ из 2.0
	virtual HRESULT Get20TT(OUT mcsWorkIDArray& ids, OUT McsString& st, OUT mcsPoint3dArray &pnts)
		{ return E_NOTIMPL; }

	//Для чтения шаблонов PT
	virtual COLORREF GetRGBColorByACADIndex(int nColorIndex)
		{ return 0; }

	// Назначает источник свойств для текущей команды
	virtual HRESULT SetCommandPropertiesSource(IN IMcPropertySource* pPS)
		{ return E_NOTIMPL; }

	// Инициирует перечитывание свойствa systemName, если systemName не указан - перечитывается всё
	virtual HRESULT CommandPropertyChanged(IN OPTIONAL LPCTSTR systemName = NULL)
		{ return E_NOTIMPL; }

	// Обновляет инспектор свойств
	virtual HRESULT RefreshPropertyInspector()
		{ return CommandPropertyChanged(NULL); }

	// Показывает или скрывает тулбар
	virtual HRESULT ShowToolbar(IN LPCTSTR stName, IN bool bShow = true, IN bool bByName = true, bool bMakeFloating = false)
		{ return E_NOTIMPL; }

	// Перемещает объекты на верх списка отрисовки, последний в массиве будет выше всех
	// Если задан idBaseObject, то перемещает выше данного объекта
	// Вниз Аналогично
	// Работает с активным документом
	virtual HRESULT SetDrawOrder(IN const mcsWorkIDArray& ids, IN bool moveToTop, IN OPTIONAL const mcsWorkID& idBaseObject = WID_NULL)
		{ return E_NOTIMPL; }

	// Сортирует массив в порядке отрисовки
	virtual HRESULT SortByDrawOrder(IN OUT mcsWorkIDArray& ids)
		{ return E_NOTIMPL; }

	// конвертация XData в McsProperty  - прописывайте кому что нужно поднимать
	virtual HRESULT XData2McsProperty(const mcsWorkID& idKey, bool bResetXData)
		{ return E_NOTIMPL; }

	// вернуть цвет фона в документе;
	// если заливка градиентная, то цвета будут разные, иначе одинаковые
	virtual HRESULT getDocViewBkColor(OUT COLORREF& bkColorTop, OUT COLORREF& bkColorBottom)
		{ bkColorTop=RGB(52, 99, 150); bkColorBottom=RGB(192,192,192); return S_OK;}

	// Возвращает цвет текста, который будет видим на фоне с цветом из getDocViewBkColor().
	MCTYP_API static COLORREF getTextColorForBkColor();

	// Добавляет кнопку на тулбар в нашей меню группе
	// По умолчанию на тулбар "Custom toolbar" и без описания
	virtual HRESULT AddToolbarButton(LPCTSTR stButtonName, LPCTSTR stCommand, bool bAutoPrefix = true, LPCTSTR stToolbarName = NULL, LPCTSTR stButtonDescription = NULL)
		{ NOTIMPL_ALERT("IMcNativeGate::AddToolbarButton"); }
	
	// Позволяет получить/установить переменную среды
	enum McSystemVariable
	{
		kShowLineWeight = 1,// bool
		kOrthoMode = 2,// bool
		kDynMode = 3,// DWORD
		kPolarTrack = 4,// bool
		kHPGapTol = 5,// double
		kTempOverrides = 6,// bool
		kProxyNotice = 7,// bool

		// int, some values:
		// 0 - point
		// 1 - invisible
		// 2 - ortho-cross
		// 3 - cross, rotated by 45 deg
		// 4 - upward stroke
		// see other values in ACAD end-user help
		kPtDrawMode = 8,

		// Units support. See description in AutoCAD end-user help.
		kMeasurement = 9, // "MEASUREMENT", int, 0 - imperial, 1 - metric
		kLUNITS      = 10,// "LUNITS", int
		kAUNITS      = 11,// "AUNITS", int
		kUNITMODE    = 12,// "UNITMODE", int
		kDIMZIN      = 13,// "DIMZIN", int
		kDIMAZIN     = 14,// "DIMAZIN", int
		kANGBASE     = 15,// "ANGBASE", double
		kANGDIR      = 16,// "ANGDIR", int
		kLUPREC      = 17,// "LUPREC", int
		kAUPREC      = 18,// "AUPREC", int
		kINSUNITS    = 19,// "INSUNITS", int

		kGripSize = 20,// "GRIPSIZE", int
		kDELOBJ = 21,// "DELOBJ", int
		kLOFTNORMALS = 22,// "LOFTNORMALS", int
		kTHICKNESS = 23,// "THICKNESS", double
		kDIMSCALE = 24,// "DIMSCALE", double
		kGRIPOBJLIMIT = 25,// "GRIPOBJLIMIT", int

		kFixedFacetRes = 26, // "FIXEDFACETRES", bool
		kCurConfigurationName = 27,// Название стартовой конфигурации nanoCAD, ключ командной строки "-r", IAppInterior::GetCurConfigurationName().
		kUcsDetect = 28, // "UCSDETECT", bool
		kFILEDIA = 29, // FILEDIA, bool, показывать/нет диалог запроса имени фалов
		kDwgCheck = 30, // DWGCHECK, int, 0 = вообще ничего не показывать, остальные значения: см. справку Автокада
		k3dDraftingMode = 31, // 3DDRAFTINGMODE, int, 1 - режим редактирования эскиза, 0 - нет
		kOSMODE = 32, // OSMODE, int
		kAUTOSNAP = 33, // AUTOSNAP, int
		kCONSTRAINTINFER = 34, // CONSTRAINTINFER, int, 1 - режим автоналожения зависимостей включен
		k3DOSMODE = 35, // 3DOSMODE, int
	};

	virtual HRESULT GetSystemVariable(IN McSystemVariable type, OUT MCSVariant& value, IN OPTIONAL IMcDocument* pDoc = NULL)
		{ return E_NOTIMPL; }

	virtual HRESULT SetSystemVariable(IN McSystemVariable type, IN const MCSVariant& value, IN OPTIONAL IMcDocument* pDoc = NULL)
		{ return E_NOTIMPL; }

	// Используется при поиске и замене
	virtual HRESULT GetNativeRawText(IN const mcsWorkID& idText, OUT McsString& stText)
		{ return E_NOTIMPL; }

	virtual HRESULT SetNativeRawText(IN const mcsWorkID& idText, IN LPCTSTR stText)
		{ return E_NOTIMPL; }

	virtual HRESULT InitRecognizer(/*IVectorStorage**/void* pVS, /*IVectorStorage**/void* pTVS)
		{ return E_NOTIMPL; }

	virtual HRESULT GetHatchPatternNames(IN mcsHatch::PatternType patternType, OUT mcsStringArray& names)
		{ return E_NOTIMPL; }

	//сохранят обекты через файл в стрим. первая запись в стриме ДО версии - PlatformId
	//ну и соответственно каждая платформа решает может ли она это вставить
	//потому что версии могут различатся, так что ReadVersionAllert вызывать не надо
	//
	virtual HRESULT SaveUnkObjectsToStream(IMcsStreamPtr &pStream, mcsWorkIDArray& ids)
		{	return E_NOTIMPL;}

	virtual HRESULT LoadUnkObjectsFromStream(mcsWorkIDArray& ids, IMcsStreamPtr pStream)
		{	return E_NOTIMPL;}

	// Для редактирования по месту
	typedef BOOL (*McMessageFilterFunk)(const MSG* pMsg, LPARAM lParam);

	virtual HRESULT SetMessageFilter(HANDLE& hMFHandle, McMessageFilterFunk mfproc, LPARAM lParam)
		{ NOTIMPL_ALERT("IMcNativeGate::SetMessageFilter"); }

	virtual HRESULT RemoveMessageFilter(HANDLE hMFHandle)
		{ NOTIMPL_ALERT("IMcNativeGate::RemoveMessageFilter"); }

	// S_OK - proxy, S_FALSE not proxy, либо ошибка
	virtual HRESULT CheckOnProxy(const mcsWorkID& id)
		{ return E_NOTIMPL; }

	// Converter
	virtual HRESULT AddDeferredOldEnt(IN const McDeferredOldEntity& defdata)
		{ return E_NOTIMPL; }

	virtual HRESULT CreateDbEntity(OUT LPVOID pEnt, IN const IID& iid, IN FARPROC pConvertProc, IN FARPROC pAfterConvertProc, IN bool bCallAcDbEntityDwgIn)// pEnt==AcRxObject** || pEnt==OdRxObjectPtr*
		{ return E_NOTIMPL; }

	virtual HRESULT InsertConvertedEntity(IN LPVOID pID, IN IMcEntity* pEnt, bool useHandOverTo)
		{ return E_NOTIMPL; }

	virtual HRESULT RegisterClass(IN const IID& iid, IN LPCTSTR stDatabaseClassName, IN OPTIONAL LPCTSTR stDatabaseClassNamePrefix = NULL)
		{ return E_NOTIMPL; }

	virtual HRESULT BuildClassHierarchy()// System, internal, only for AutoCAD - acrxBuildClassHierarchy()
		{ return E_NOTIMPL; }

	// Возвращает геометрию подобъекта по его ID
	virtual HRESULT GetSubentGeometry(
		IN const mcsWorkID&    idSubEnt,
		OUT McsEntityGeometry& geom_lcs) // геометрия в координатах объекта, к которому относится idSubEnt
	{
		geom_lcs.setNull();
		return E_NOTIMPL;
	}

	virtual HRESULT GetSubentBox(IN const mcsWorkID& id, OUT mcsBoundBlock& box)
	{
		box.invalidate();
		return E_NOTIMPL;
	}

	virtual HRESULT CreateMText(
		OUT mcsWorkID& id,
		IN LPCTSTR st,
		IN const mcsPoint& pntAttach,
		IN const mcsVector& vecDirection,
		IN double rHeight,
		IN McsHorizTextAlignEnum hzalign,
		IN McsVertTextAlignEnum vtalign,
		IN double rBoxWidth,
		IN OPTIONAL IMcDocument* pDoc)
	{
		return E_NOTIMPL;
	}

	virtual HRESULT Message(LPCTSTR stMessage)
		{ NOTIMPL_ALERT("IMcNativeGate::Message"); }

	virtual HRESULT QuickKindOf(const mcsWorkID& id, const mcsGUIDArray& clsIds, const mcsWorkID* pDocumentId = NULL)
		{ NOTIMPL_ALERT("IMcNativeGate::QuikKindOf"); }

	HRESULT QuickKindOf(const mcsWorkID& id, const GUID& clsId, const mcsWorkID* pDocumentId = NULL)
		{ return QuickKindOf(id, mcsGUIDArray() << clsId, pDocumentId); }

		// Выдаёт управляющий интерфейс для набора плоских геом/парам-зависимостей в указанной области видимости;
		// По умолчанию в текущем поддокументe.
		// - Допустимо передавать в качестве idScope идентификатор плоского эскиза, в этом случае
		//   управляющий интерфейс будет работать только с зависимостями эскиза.
		// - Если указан документ, то выдаст управляющий интерфейс группы зависимостей для текущей UCS-плоскости
		//   указанного документа.
		// - Можно указывать ID существующей зависимости, тогда будет использовать его группа зависимостей.
		// - Также допускается указывать ScopeID, который возвращает сам манагер зависимостей.
		// Не доускается указывать ID top-level документа, только поддокумент !
		// Если idScope никак не указывает на плоский эскиз, то в pConstraintsPlane можно
		// передать желаемую плоскость для зависимостей, по умолчанию подразумевается XY текущей UCS
	virtual IMcs2dConstraintsManager* Get2dConstraintsManager(
		IN OPTIONAL const mcsWorkID& idScope = WID_NULL,
		IN OPTIONAL const mcsPlane*  pConstraintsPlane = NULL)
	{
		NOTIMPL_ALERT2("IMcNativeGate::Get2dConstraintsManager",NULL);
	}

	virtual IEM* getActiveEntityMonitor()
		{ NOTIMPL_ALERT2("IMcNativeGate::getActiveEntityMonitor",NULL); }

	virtual HRESULT GetMTextFragments(IN const mcsWorkID& id, OUT McMTextFragmentArray& fragments, OUT OPTIONAL McsString* psFieldContent = NULL)
		{ NOTIMPL_ALERT("IMcNativeGate::GetMTextFragments"); }
	virtual double GetMTextFragmentTextLength(IN const McMTextFragment& fragment, IN LPCTSTR st)
		{ NOTIMPL_ALERT2("IMcNativeGate::GetMTextFragmentTextLength", -1); }

	// Функционал и аргументы соответствуют IMechWizard::GetContoursByPickPoint().
	virtual HRESULT GetContoursByPickPoint(IN const mcsPoint& pnt,
		IN bool bOnlyExternLoop,
		OUT mcsPolylineArray& contours,
		IN OPTIONAL double rTol,
		OUT OPTIONAL mcsWorkIDArray* pexarr,
		IN bool bUseEllipses = false,
		IN IMcGeometryFilter* pGeomFilter = NULL)
	{
		return E_NOTIMPL;
	}

	virtual HRESULT GetInternalContour(mcsPolyline& contour, const mcsGeomEntArray& ents, const mcsPoint3d& pnt, double rTol, mcsIntArray* parSkipLineGost = NULL)
	{
		return E_NOTIMPL;
	}

	virtual IMcTheme* GetTheme()
		{ return NULL; }

	virtual bool isInXrefEditMode()
		{ return false; }

	// получить тип реализации объекта
	virtual GUID QueryObjectClassID(const mcsWorkID& id, const mcsWorkID* pDocumentId = NULL)
		{ NOTIMPL_ALERT2("IMcNativeGate::QueryObjectClassID", GUID_NULL); }

	// returns the first available part list in the active drawing document
	virtual HRESULT Get3dPartList(OUT IMc3dPartListGatePtr& pPartList, IN OPTIONAL mcsWorkID drawingViewID = WID_NULL)
		{ NOTIMPL_ALERT("IMcNativeGate::Get3dPartList"); }

		// выдает ИД документа, для которого была открыта последняя спецификация
	virtual mcsWorkID get3dPartListTopDocID()
		{ NOTIMPL_ALERT2("IMcNativeGate::QueryObjectClassID", WID_NULL); }

	virtual HRESULT SubHandOverTo(const mcsWorkID& idOldEntity, IMcEntity* pNewEntity)
		{ NOTIMPL_ALERT("IMcNativeGate::SubHandOverTo"); }

	enum ExtEditorMode
	{
		kPlmEditMode_Normal = 0,
		kPlmEditMode_BEdit,
		kPlmEditMode_RefEdit_SameDb,
		kPlmEditMode_RefEdit_AnotherDb,
		kPlmEditMode_NewBlock, // WBLOCK, BLOCK
	};

	// метод сообщает, активен ли в текущем документе внешний редактор (блока или внешней ссылки, например);
	// опционально выдаёт рабочий набор редактируемого вхождения блока
	// pEditingBlock - если возможно, то вернет ID редактируемого блока
	virtual ExtEditorMode isExternalEditorActive(
		OUT OPTIONAL mcsWorkIDSetEx* pXrefWorkset = NULL,
		OUT OPTIONAL mcsWorkID*      pIdEditingBlock = NULL,
		OUT OPTIONAL bool*           pb3dEditor = NULL)
	{
		NOTIMPL_ALERT2("IMcNativeGate::isExternalEditorEctive", kPlmEditMode_Normal);
	}

	// Метод проверяет объект на вхождение в текущий рабочий набор
	virtual bool isInWorkingSet(const mcsWorkID& id)
		{ NOTIMPL_ALERT2("IMcNativeGate::isInWorkingSet", true); }

	// Поддержка изоляции объектов
	virtual HRESULT SetVisiblilityByIsolation(const mcsWorkID& id, bool bVisible)
		{ NOTIMPL_ALERT("IMcNativeGate::SetVisiblilityByIsolation"); }
	virtual HRESULT GetVisiblilityByIsolation(const mcsWorkID& id, bool& bVisible)
		{ NOTIMPL_ALERT("IMcNativeGate::GetVisiblilityByIsolation"); }

	// Коррекция размеров, прочитанных в dwgInFields.
	virtual HRESULT GetReadDimIDs(OUT mcsWorkIDArray& arDimIDs)
		{ NOTIMPL_ALERT("IMcNativeGate::GetReadDimIDs"); }
	virtual HRESULT ClearReadDimIDs()
		{ NOTIMPL_ALERT("IMcNativeGate::ClearReadDimIDs"); }

	// См. описание к методу 'Get2dConstraintsManager'
	// Дополнительно к нему есть возможность указать конкретный требуемый тип сети зависимостей
	virtual IMcs2dConstraintsManager* Get2dConstraintsManager2(
		IN OPTIONAL McCtrs2dNetType  ctrsNetType,         // = kMc2dCtrNet_Auto,
		IN OPTIONAL const mcsWorkID& idScope,             // = WID_NULL,
		IN OPTIONAL const mcsPlane*  pConstraintsPlane,   // = NULL
		IN OPTIONAL bool             fForceCreateReqData) // = false
	{
		NOTIMPL_ALERT2("IMcNativeGate::Get2dConstraintsManager3",NULL);
	}

	// true, если текущая команда - операция создания нового блока
	MCTYP_API bool isNewBlockMode();

	// true, если это операция входа/выхода в режим BEDIT/REFEDIT
	MCTYP_API bool isBlockCloningOperation();

	// Список масштабов документа
	virtual HRESULT GetScales(IN IMcDocument* pDoc, OUT mcsStringArray& names, OUT mcsDoubleArray& values)
		{ NOTIMPL_ALERT("IMcNativeGate::GetScales"); }

	// Получить список материалов
	virtual HRESULT getMaterialsList(OUT EMSP_MaterialItemArray& gateMaterials)
	{
		gateMaterials.RemoveAll();
		return E_NOTIMPL;
	}

	// Установить указанный материал текущим
	virtual HRESULT setCurrentMaterial(IN DWORD newMaterialGateID)
		{ return E_NOTIMPL; }
	
	// для двух фланцев - <idFlange1> <idFlange2> пытается сформировать 
	// структуры данных, необходимые для соединения фланцев массивом болтовых
	virtual HRESULT getFlangeConnectionData(
		IN const mcsWorkID&     idFlange1,
		IN const mcsWorkID&     idFlange2,
		OUT mcsHolesArray&      Holes,
		OUT IMcArrayControlPtr& pArrayPlacementControl)
	{
		return E_NOTIMPL;
	}

	// Список видовых экранов в заданной точке. Последний в списке - верхний.
	virtual HRESULT GetViewportsByPoint(const mcsPoint& pnt, OUT mcsWorkIDArray& ids)
		{ NOTIMPL_ALERT("IMcNativeGate::GetViewportsByPoint"); }

	MCTYP_API virtual IMcObjMvRedefinitionPtr queryObjMvRedefinition(
		IN const mcsWorkID&          idObj,
		IN OPTIONAL const mcsWorkID& idVP = WID_NULL);

	// Возвращает геометрию подобъекта по его ID с учетом возможного переопределения в видовом экране
	MCTYP_API virtual HRESULT GetSubentGeometry(
		IN const mcsWorkID&        idViewport,
		IN const mcsComplexWorkID& cidSubEnt,
		OUT McsEntityGeometry&     geom_lcs); // в координатах целевого объекта (последнего в цепочке)

	// Метод проверяет, относится ли данный ID к внешнему блоку.
	// ID может быть вставкой блока, или самим блоком.
	// Внутри не выполняется никаких лишних действий, нкаких reload и т.п..
	virtual bool isXrefBlock(const mcsWorkID& id)
		{ NOTIMPL_ALERT2("IMcNativeGate::isXrefBlock", false); }

	virtual HRESULT correctIdOnLoad(IN OUT mcsWorkID& idTo, IN LONG_PTR SomeIdFrom)
		{ NOTIMPL_ALERT("IMcNativeGate::correctIdOnLoad"); }

	// Internal
	virtual HRESULT internal_SetGraphics(IN OUT int& iID, IN const mcsGeomEntArray& ents)
	{
		NOTIMPL_ALERT("IMcNativeGate::internal_SetGraphics");
	}
	virtual HRESULT internal_SetGraphics(IN OUT int& iID, IN IMcsGraphics* pG)
	{
		NOTIMPL_ALERT("IMcNativeGate::internal_SetGraphics");
	}
	virtual HRESULT internal_RemoveGraphics(IN int iID)
	{
		NOTIMPL_ALERT("IMcNativeGate::internal_RemoveGraphics");
	}
	//...
};
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Временный интерфейс для работы с акадовским лучом и прямой
//---------------------------------------------------------------------------
IMCS_DECL_INTERFACE(IMcConstructionLine, "00000001-000B-AAAA-AAAA-050B00000000")
struct IMcConstructionLine : public IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcConstructionLine);

	virtual HRESULT addToCurrentDocument(OUT mcsWorkID& id, IN const mcsPoint& pnt, IN const mcsVector& direction, IN bool isRay, IN LPCTSTR stLayer, IN COLORREF color, IN int iLineWeight) = 0;

	virtual HRESULT set(IN const mcsWorkID& id, IN const mcsPoint& pnt, IN const mcsVector& direction) = 0;
	virtual HRESULT get(IN const mcsWorkID& id, OUT mcsPoint& pnt, OUT mcsVector& direction, OUT bool& isRay) = 0;

	virtual HRESULT erase(IN const mcsWorkID& id) = 0;
	virtual HRESULT eraseAll(LPCTSTR stLayerName) = 0;
};
//===========================================================================

#if !defined(_NCAD_BUILD_) && !defined(_MCS_CORE_ONLY)
	#include "IMcNativeGateInternal.h"
#endif
//===========================================================================
