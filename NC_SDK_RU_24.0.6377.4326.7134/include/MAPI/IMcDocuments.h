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
#include "IMcObjects.h"
#include "cmnmacro.h"

struct IMcs2dConstraintsManager;

//===========================================================================
// for selectFileDlg method in document manager
enum mcsDlgItemAccess
{
	kItemNotVisible = 0,
	kItemReadOnly,
	kItemDisabled,
	kItemEnabled
};

//===========================================================================
struct mcsFileDlgParams
{
	mcsFileDlgParams() 
	{
		itemRelativePath = kItemNotVisible;
		bRelativePath = TRUE;
		bSaveAsDialog = FALSE;
		hParent = NULL;
	}
	mcsFileDlgParams(HWND _hParent, BOOL _bSaveAsDialog, BOOL _bRelativePath, mcsDlgItemAccess _itemRelativePath)
	{
		hParent = _hParent;
		bSaveAsDialog = _bSaveAsDialog;
		bRelativePath = _bRelativePath;
		itemRelativePath = _itemRelativePath;
	}
	HWND hParent;
	BOOL bSaveAsDialog;
	BOOL bRelativePath;
	mcsDlgItemAccess itemRelativePath;
}; 
//===========================================================================

//////////////////////////////////////////////////////////////////////////
//Реализация в Gate

const McsString MCS_PROP_DOC_NAME                = _T("DrawingName");        // Наименование документа
#define         MCS_PROP_DOC_PARTNUMBER          MCS_PROP_DOC_NAME
const McsString MCS_PROP_DOC_DESIGNATION         = _T("Designation");        // Обозначение документа
const McsString MCS_PROP_DOC_FORMAT              = _T("Format");             // Обозначение формата
const McsString MCS_PROP_DOC_SHEET_NUM           = _T("Sheet");              // Kист
const McsString MCS_PROP_DOC_SHEET_COUNT         = _T("SheetCount");         // Kистов
const McsString MCS_PROP_DOC_AUTHOR              = _T("Author");             // Разработал
const McsString MCS_PROP_DOC_CONTROL             = _T("Control");            // Проверил
const McsString MCS_PROP_DOC_TECH_CONTROL        = _T("TechControl");        // Технический контроль
const McsString MCS_PROP_DOC_NORM_CONTROL        = _T("NormControl");        // Нормативный контроль
const McsString MCS_PROP_DOC_ADD_CONTROL         = _T("Add.subject");        // Дополнительный контроль
const McsString MCS_PROP_DOC_APPROVE             = _T("Approve");            // Утвердил
const McsString MCS_PROP_DOC_ADD_TEXT            = _T("Add.text");           // Доп. текст (Должность дополнительного контроля)
const McsString MCS_PROP_DOC_AUTHOR_DATE         = _T("Author(date)");       // Дата разработки
const McsString MCS_PROP_DOC_CONTROL_DATE        = _T("Control(date)");      // Дата проверки
const McsString MCS_PROP_DOC_TECH_CONTROL_DATE   = _T("TechControl(date)");  // Дата технического контроля
const McsString MCS_PROP_DOC_NORM_CONTROL_DATE   = _T("NormControl(date)");  // Дата нормативного контроля
const McsString MCS_PROP_DOC_ADD_CONTROL_DATE    = _T("Add.subject(date)");  // Дата дополнительного контроля
const McsString MCS_PROP_DOC_APPROVE_DATE        = _T("Approve(date)");      // Дата утверждения
const McsString MCS_PROP_DOC_ENTERPRISE          = _T("Enterprise");         // Предприятие
const McsString MCS_PROP_MASS                    = _T("Mass");               // Масса
const McsString MCS_PROP_MATERIAL                = _T("Material");           // Материал
const McsString MCS_PROP_VOLUME                  = _T("Volume");             // Объем
const McsString MCS_PROP_DOC_PARTITION           = _T("Partition");          // Раздел спецификации
const McsString MCS_PROP_DENSITY                 = _T("Density");            // Плотность
const McsString MCS_PROP_DOC_COUNT               = _T("Count");              // Количество
const McsString MCS_PROP_DOC_REMARCS             = _T("Remarcs");            // Примечание
#define         MCS_PROP_DOC_SCALE               MCS_PROPERTY_DIMSCALE       // не изменять! используется кнопкой масштаба
const McsString MCS_PROP_DOC_FIRST_USE           = _T("First use");          // первичное применение
const McsString MCS_PROP_DOC_REFERENCE           = _T("Reference#");         // справочный номер

const McsString MCS_PROP_DOC_ORIG_INV_N          = _T("Original#");          // Инвентарный номер подлинника
const McsString MCS_PROP_DOC_ORIG_INV_N_DATE     = _T("Sign&date 1");        // Дата инвентарного номера подлинника
const McsString MCS_PROP_DOC_ORIG_INV_N_REPL     = _T("Instead#");           // Взамен инвентарного номера
const McsString MCS_PROP_DOC_DUP_INV_N           = _T("Duplicate#");         // Инвентарный номер дубликата
const McsString MCS_PROP_DOC_DUP_INV_N_DATE      = _T("Sign&date 2");        // Дата инвентарного номера дубликата

//===========================================================================

enum McFormatEnum {
	kMcFormat_Unknown  = -2,
	kMcFormat_Custom   = -1,
	kMcFormat_A0       =  0,   // 841x1189
	kMcFormat_A1       =  1,   // 594x841
	kMcFormat_A2       =  2,   // 420x594
	kMcFormat_A3       =  3,   // 297x420
	kMcFormat_A4       =  4,   // 210x297
	kMcFormat_A5       =  5,   // 148x210
};

enum McDocTypeEnum
{
	kMcDocTyp_Undefined = 0x0000,

	// возвращалось только в 3D платформах для чертежных документов
	// сейчас для полноценного рисования 2D в 3D платформе используется пара kMcDocTyp_DWG + kMcDoc3dType_Drawing
	// Если же это чертежный документ в 3D платформе, то это пара kMcDocTyp_3d + kMcDoc3dType_Drawing
	//kMcDocTyp_Drawing   = 0x0001,

	// возвращалось только в 3D платформах для чертежных документов
	// сейчас вместо него kMcDocTyp_3d и отдельно метод IMcDocument::get3dType
	//kMcDocTyp_3dPart    = 0x0002,
	//kMcDocTyp_3dAsm     = 0x0004,

	// используется для НЕ-DWG платформ
	// уточненный тип 3D получать через метод IMcDocument::get3dType
	kMcDocTyp_3d        = 0x0002,

	kMcDocTyp_DWG       = 0x0008,
	kMcDocTyp_Sub       = 0x0010,
	kMcDocTyp_Layout    = 0x0020,
	kMcDocTyp_Model     = 0x0040,
	kMcDocTyp_XRef      = 0x0080,
	kMcDocTyp_DynBlock  = 0x0100,
};

// не менять, пишется в документ
enum Mc3dDocTypeEnum
{
	kMcDoc3dType_Unk      = 0, // не 3D документ
	kMcDoc3dType_Auto     = 1, // определить тип, используя содержимое документа
	kMcDoc3dType_Drawing  = 2, // не 3D документ, 2D в 3D платформе
	kMcDoc3dType_Part     = 3,
	kMcDoc3dType_Asm      = 4,
	kMcDoc3dType_Std      = 5,
};

//===========================================================================

struct IMcAlbums;
struct IMcsDocVariablesManager;

//===========================================================================

struct McDocumentVersionData
{
	__int64             iVerCreated;
	__int64             iVerCoreCreated;
	MCS_AppId           appCreated;
	MCS_PlatformId      plmCreated;
	MCS_ConfigurationId cfgCreated;
	McsString           stAppNameCreated;
	__int64             iVerModified;
	__int64             iVerCoreModified;
	MCS_AppId           appModified;
	MCS_PlatformId      plmModified;
	MCS_ConfigurationId cfgModified;
	McsString           stAppNameModified;

	McDocumentVersionData()
	{
		iVerCreated = 0;
		iVerCoreCreated = 0;
		appCreated = (MCS_AppId)0;
		plmCreated = (MCS_PlatformId)0;
		cfgCreated = (MCS_ConfigurationId)0;

		iVerModified = 0;
		iVerCoreModified = 0;
		appModified = (MCS_AppId)0;
		plmModified = (MCS_PlatformId)0;
		cfgModified = (MCS_ConfigurationId)0;
	}
};

//===========================================================================
enum McFixSubDocNameMode
{
	/// Фиксировать имя, если блок с исправленным именем уже есть, то скорректировать имя еще раз,
	/// чтобы сделать его уникальным. Никаких уведомлений.
	kMcFixSubDocNameMode_Silent              = 0,

	/// Фиксировать имя. Если блок с таким именем уже есть, то скорректировать имя еще раз,
	/// и показать пользователю уведомление о том, что имя было изменено.
	kMcFixSubDocNameMode_ShowInfoNotice      = 1,

	/// Фиксировать имя. Далее, если блок с таким именем уже есть,
	/// то спросить, использовать ли существующий блок вместо нового или скорректировать имя еще раз,
	kMcFixSubDocNameMode_AskForReuseExisting = 2,
};

//===========================================================================
struct IMcDocument : public virtual IMcPropertySource
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcDocument);
	IMCS_STD_METHOD_DEFINITION(IMcDocument, IMcPropertySource)

	virtual HRESULT getName(OUT McsString&) = 0;
	virtual HRESULT getPath(OUT McsString&) = 0;

	// задаёт путь к внешнему файлу, связанному с документом (xref)
	virtual HRESULT setPath(IN LPCTSTR Value) 
		{ return E_NOTIMPL; }

	//sub documents function

		//return Top document
	virtual IMcDocumentPtr getTopDoc() = 0;
	virtual mcsWorkID getTopDocID() = 0;

		//true if is a Sheet
	virtual bool isSub() = 0;

	virtual bool isNew() {
		McsString st;
		HRESULT hRes = this->getPath(st);
		return (FAILED(hRes) || st.Find(_T('\\')) < 0);
	}

	virtual bool isLayout() = 0;
	virtual bool isHidden() = 0;

	virtual bool is3D()
		{return false;}

	virtual bool isModel()
		{return false;}

	virtual DWORD getType()
		{return kMcDocTyp_DWG;}

	// returns all available objects in document by specific filter
	virtual HRESULT getObjectsByFilter(OUT mcsWorkIDArray&  objects, IN  const mcsFilter& filter) = 0;
	virtual HRESULT activate() = 0;
	virtual HRESULT save(LPCTSTR saveAs = NULL) = 0;//adjust to top document
	virtual HRESULT close() = 0;

		//subdocuments
	virtual IMcDocumentPtr getActiveSubDocument() = 0;
	virtual HRESULT createSheet(OUT IMcDocument** ppSheetSubDoc,IN OPTIONAL LPCTSTR cstrSheetName=NULL) = 0;
	virtual HRESULT deleteSheet(IN IMcDocument* pSheetSubDoc)
		{ return E_NOTIMPL; }

		//Создает поддокумент! не layout, если bAutoNameIndex == true то при совпадении имени будет добавлять цифровой индекс автоматически
	virtual HRESULT createSubDocument(OUT IMcDocument** ppSubDoc,IN LPCTSTR cstrBlockName,IN  bool bAutoNameIndex) = 0;

		// returns all available subdocuments
	virtual HRESULT getSubDocuments(OUT mcDocumentsArray& documents, bool bLayout = true) = 0;//adjust to top document
	virtual HRESULT getSubDocuments(OUT mcsWorkIDArray& idsDocs, bool bLayout = true) = 0;//adjust to top document

		// return id of AcDbBlockTableRecord, copy it's from pSrcDoc if need
	virtual mcsWorkID getSubDocumentID(LPCTSTR strSubBlock, IMcDocument* pSrcDoc = NULL ) = 0;

	//Удалить блок или лист
	virtual HRESULT deleteSubDocument(IN IMcDocument* pSubDoc)
		{ return E_NOTIMPL;};
	virtual HRESULT getReferencedDocs(mcDocumentsArray& pDocs)
		{return E_NOTIMPL;}
	virtual HRESULT replaceReferencedDoc(LPCTSTR oldPath, LPCTSTR newPath)
		{return E_NOTIMPL;}

		// closes current native document and opens new one in the same IMcDocument
	virtual HRESULT attachXRef(IN LPCTSTR stFileName, IN LPCTSTR stBlockName, OUT OPTIONAL mcsWorkID* pidBlock = NULL)
		{ return E_NOTIMPL; }
	virtual HRESULT reloadXRef()
		{ return E_NOTIMPL; }
	virtual HRESULT bindXRef(IN bool bInsert)
		{ return E_NOTIMPL; }

	virtual HRESULT writeCustomData(IN LPCTSTR csStreamName,IN IMcsStream*,IN OPTIONAL bool fAdjustToTop = true) = 0;
	virtual HRESULT readCustomData(IN LPCTSTR csStreamName,OUT IMcsStream*,IN OPTIONAL bool fAdjustToTop = true) = 0;
	virtual HRESULT writeCustomData(LPCTSTR stName, LPCVOID pData, DWORD dwSize) = 0;
	virtual HRESULT readCustomData(LPCTSTR stName, mcsByteArray& data) = 0;
	virtual HRESULT getCustomDataList(mcsStringArray& names, bool fTop) = 0;

	virtual bool isDocumentLocked(LPCTSTR stLayer) = 0;

	virtual IMcsNativeViewPtr getActiveView() = 0;

	virtual HRESULT setSize(
		IN McFormatEnum eSize, IN bool fHorizontal,
		IN OPTIONAL double rWidth = 0, IN OPTIONAL double rHeight = 0) 
		{return E_NOTIMPL;}

/*
		// Даты передаются в формате DATE (который есть double)
		// Для работы удобно использовать обертку COleDateTime
	virtual HRESULT getProperties(OUT mcsStringArray& props)
		{props.RemoveAll(); return E_NOTIMPL;}
	virtual HRESULT getProperty(IN LPCTSTR name, OUT MCSVariant& data)
		{data.SetType(MCSVariant::kUndefined); return E_NOTIMPL;}
	virtual HRESULT setProperty(IN LPCTSTR name, IN const MCSVariant& data)
		{ return E_NOTIMPL;}
*/

	virtual mcsPoint getBlockInsertionPoint()
		{return mcsPoint::kOrigin;}
	virtual HRESULT getBoundingBox(mcsBoundBlock& bound)
		{ return E_NOTIMPL; }

		//protected:
		// AGL limitation removed // you must use call gpMcObjManager->addToDocument(...) instead
	virtual HRESULT addObject(IN IMcDbObject* pMDBO) = 0; //in TopDocument insert in Active sheet

	virtual HRESULT MECHCTL_API getAlbums(IMcAlbumsPtr& pRes);
	virtual HRESULT setAlbums(IMcAlbums* pVal)
		{ return E_NOTIMPL; }

	virtual HRESULT disableUndoRecording(bool bDisable)
		{ return E_NOTIMPL; }

	MECHCTL_API virtual IMc3dDocHistoryPtr get3dHistory();

	virtual HRESULT GetUCS(OUT mcsMatrix& ucs)
		{ NOTIMPL_ALERT("IMcDocument::GetUCS"); }

	virtual HRESULT SetUCS(IN const mcsMatrix& ucs)
		{ NOTIMPL_ALERT("IMcDocument::SetUCS"); }

	// Возвращает менеджер для работы с переменными сети зависимостей
	virtual IMcsDocVariablesManager* getDocVariablesManager()
		{ return NULL; }

	//работает только для isSub() == true, экспортирует объекты, если имя блока не задано то в ModalSpace
	//Если не задана tfm, то левый нижний угол боунда всех объектов в 0.0.0
	virtual HRESULT copyObjects(mcsWorkIDArray& ids, IMcDocument* pTarget, LPCTSTR szBlockName = NULL, mcsMatrix* tfm = NULL){return E_FAIL;};

	//работает только для isSub() == true, экспортирует все целиком, если имя блока не задано то в ModalSpace
	virtual HRESULT copyObjects(IMcDocument* pTarget, LPCTSTR szBlockName = NULL, mcsMatrix* tfm = NULL){return E_FAIL;};
	virtual HRESULT MECHCTL_API GetPreviewBlocksOfDocument(IN OUT McsString& blockName, OUT mcsWorkID& idBlock, HWND m_hWnd);

	virtual IMcDocParamManager* params()
		{ NOTIMPL_ALERT2("IMcDocument::params()", NULL); }

	// Создает поддокумент (блок)
	virtual IMcDocumentPtr createSubDocument(
		IN const mcsWorkIDArray&  idObjects, // объекты, на основе которых будет создаваться блок, после создания объекты будут удалены
		IN LPCTSTR                cstrBlockName, // имя блока
		IN bool                   bAutoNameIndex, // если true и блок с таким именем уже есть, к имени блока для уникальности будет добавлен цифровой суффикс
		IN const mcsPoint&        basePt, // базовая точка вставки блока
		IN bool                   bCreateBlockRef) // если true, создаст вставку блока вместо переданных объектов
	{
		NOTIMPL_ALERT2("IMcDocument::createSubDocument", UNKNULL);
	}

	// То же, что и метод 'getDocVariablesManager', но позволяет указать ещё и тип сети зависимостей.
	// Если указан аргумент externalVarsFilePath, то отдаёт менеджер переменных для указанного внешнего файла,
	// причем в этом случае этот файл внешних переменных будет привязан к документу.
	// Аргумент externalVarsFilePath используется только если ctrsNetType = kMc2dCtrNet_MCS.
	//
	virtual IMcsDocVariablesManager* getDocVariablesManager2(
		IN OPTIONAL McCtrs2dNetType ctrsNetType = kMc2dCtrNet_Auto,
		IN OPTIONAL LPCTSTR         externalVarsFilePath = NULL)
	{
		return NULL;
	}

	// Закрывает документ, имеется возможность подавить запрос на сохранение.
	// Подобное поведение нужно, например, для целей тестирования.
	virtual HRESULT close(bool bNoPromptForSave) 
	{
		return close();
	}

	// Возвращает менеджер управления 2D зависимостями с учетем указанных параметров.
	// См. также IMcNativeGate::Get2dConstraintsManager2.
	virtual IMcs2dConstraintsManager* get2dConstraintsManager(
		IN OPTIONAL McCtrs2dNetType  ctrsNetType = kMc2dCtrNet_Auto,
		IN OPTIONAL const mcsWorkID& idSketch = WID_NULL,
		IN OPTIONAL const mcsPlane*  pConstraintsPlane = NULL)
	{
		return NULL;
	}

	// Метод позволяет определить тип содержимого документа для 3D.
	// Если тип документа явно не задан и текущий режим опредления типа = автоматический,
	// то при bResolveAutoType = false, не будет выполняться вычисление типа документа по его содержимому.
	virtual Mc3dDocTypeEnum get3dType(bool bResolveAutoType = true)
		{return kMcDoc3dType_Unk;}

	// Принудительно установить указанный тип 3D документа.
	// Если указан kMcDoc3dType_Unk, документ логически перестаёт иметь отношение к 3D.
	// Если указан kMcDoc3dType_Auto, при последующем запросе типа он будет определяться
	// на основании содержимого документа.
	virtual HRESULT set3dType(Mc3dDocTypeEnum e3dType) {
		return E_NOTIMPL;
	}

	// Метод выполняет коррекцию желаемого имени поддокумента.
	// Платформа проверяет свои ограничения и вместо некорректных символов подставляет символ substChar.
	// Если желаемое имя подходит, то repairedName будет = lpszDesiredName и код возврата будет S_FALSE.
	// Если имя было исправлено, код возврата будет S_OK и repairedName будет содержать новое допустимое имя.
	// Для режима kMcFixSubDocNameMode_AskForReuseExisting, код возврата MCS_S_REUSE_EXISTING_DOC
	// означает, что repairedName относится к существующему поддокументу, и вызывающий код должен использовать
	// именно его.
	//
	virtual HRESULT repairSubDocumentName(
		IN LPCTSTR          lpszDesiredName,
		OUT McsString&      repairedName,
		IN OPTIONAL TCHAR   substChar = _T('_'),
		IN OPTIONAL __int64 hObjInBlock = 0, // handle объекта в поддокументе; если не 0, он будет использован в имени, если блок с таким именем уже есть
		IN OPTIONAL McFixSubDocNameMode mode = kMcFixSubDocNameMode_Silent)
	{
		repairedName = lpszDesiredName;
		return S_FALSE;
	}

	// true = данный поддокумент является вставкой внешнего поддокумента.
	virtual bool isXRef() = 0;

	// если isXrefDoc() == true, вернет оригиинальный (внешний) поддокумент
	virtual IMcDocumentPtr getXrefOriginalDoc() = 0;
	virtual mcsWorkID      getXrefOriginalDocID() = 0;

	// возвращает границы пространства документа, если оно ограничено.
	// имеет смысл для поддокументов-листов, используемых для оформления.
	virtual mcsBoundBlock getSpaceBounds() const
	{
		return mcsBoundBlock();
	}

	// Ищет в документе объект по cid-маркеру
	virtual mcsWorkID findEntityByCidMarker(const GUID& cidMarker) const
	{
		return WID_NULL;
	}

	// Присвоение имени документу/поддокументу.
	virtual HRESULT setName(IN LPCTSTR lpszName)
	{
		return E_NOTIMPL;
	}

	// Листы, отсортированные в порядке отображения вкладок в интерфейсе.
	virtual HRESULT getLayouts(OUT mcsWorkIDArray& idsDocs)
	{
		return E_NOTIMPL;
	}

	// Возвращает ID поддокумента-модели.
	// Если сам документ уже есть модель, то вернёт свой ID.
	// Если вызов выполняется для поддокумента, то он будет переадресован к документу верхнего уровня.
	virtual mcsWorkID getModelSubDocID() {
		return WID_NULL;
	}

	// true, если запрещен вызов set3dType()
	virtual bool is3dDocTypeLocked() const {
		return false;
	}
};
//===========================================================================
struct IMcDocumentsManager : public virtual IMcObject
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcDocumentsManager);
	IMCS_STD_METHOD_DEFINITION(IMcDocumentsManager, IMcObject)

	virtual IMcDocumentPtr getActiveDoc() = 0;

	inline virtual IMcDocumentPtr getActiveSheet() {
		IMcDocumentPtr pDoc(getActiveDoc());
		if (pDoc && !pDoc->isSub())
			pDoc = pDoc->getActiveSubDocument();
		return pDoc;
	}

	virtual HRESULT setWorkingDocument(IMcDocument* pDoc) = 0;
	virtual IMcDocumentPtr getWorkingDocument() = 0;

	virtual IMcDocumentPtr getDocument(IN const mcsWorkID& id) = 0;
	virtual IMcDocumentPtr getDocument(IN LPCTSTR lpszFilename) = 0;
	virtual HRESULT        getDocuments(OUT mcDocumentsArray& documents) = 0;
	virtual HRESULT        selectFileDlg(McsString &file, mcsFileDlgParams *params) { return E_NOTIMPL; }
	virtual HRESULT        openDocument(OUT IMcDocument** ppDO, IN LPCTSTR cstrFileName, IN bool bActivate, IN OPTIONAL bool isHidden = false) = 0;
	virtual HRESULT        createDocument(OUT IMcDocument** ppDO, IN OPTIONAL LPCTSTR cstrFileName = NULL, IN OPTIONAL bool bActivate = false) = 0;

	// creates a hidden document
	virtual IMcDocumentPtr createDocument() = 0;
};
//===========================================================================

//////////////////////////////////////////////////////////////////////////
// Печать документов
//
// Печать от первого вызова Plot до CancelPlot или до освобождения интерфейса
// идёт в одну задачу. Функция Plot медленная, поэтому, если документов много,
// между Plot лучше вызывать из очереди оконных сообщений.
IMCS_DECL_INTERFACE(IMcDocPlotter, "3A1B6A23-8D11-4e44-B96A-55D03E44E8BB");
struct IMcDocPlotter : public virtual IMcObject
{
	// Список устройств печати по именам. Имена можно передавать в SelectDevice
	virtual HRESULT EnumerateDevices(OUT mcsStringArray& Result) = 0;

	// Выбираем устройство печати из списка, сформированного функцией EnumerateDevices
	virtual HRESULT SelectDevice(IN McsString msName) = 0;

	// Реальное (S_OK) или виртуальное (S_FALSE) устройство выбрано
	virtual HRESULT IsPhysicalDevice() = 0;

	// Расширение файла по умолчанию для печати в файл. Вернёт пустую строку,
	// если устройство не поддерживает вывод в файл.
	virtual McsString DefaultFileExtension() = 0;

	// Выбираем путь к файлу, в который печатать. Пустая строка - печатать прямо в устройство.
	// При печати к заданному имени файла добавляется четырёхзначный номер страницы.
	virtual HRESULT SetPath(IN OPTIONAL McsString msPath = McsString()) = 0;


	// Список форматов бумаги для выбранного устройства.
	// Result - значения, которые можно передавать в SelectMedia.
	// pLocale - соответствующие им локализованные названия, чтобы показывать в диалоге.
	virtual HRESULT EnumerateMedia(OUT mcsStringArray& Result, OUT OPTIONAL mcsStringArray* pLocale = NULL) = 0;

	// Выбираем размер печатного листа из тех, которые вернула EnumerateMedia
	virtual HRESULT SelectMedia(IN McsString msName) = 0;


	// Список установленных стилей печати
	virtual HRESULT EnumerateStyles(OUT mcsStringArray& Result) = 0;

	// Установить стиль печати
	virtual HRESULT SelectStyle(IN McsString msStyle) = 0;

	// Делит область печати на несколько страниц
	// Действие параметров fFit и fCut
	// =====+======+============================================================
	// fFit | fCut | Эффект
	// =====+======+============================================================
	//   -  |   -  | Печатается в масштабе rScale. Все, что не влезло, отрезается.
	//   +  |   -  | Изображение пропорционально уменьшается, чтобы поместилось на одной странице
	//   -  |   +  | Печатается в масштабе rScale. Если не поместилось, остаток печатается на следующих страницах
	//   +  |   +  | Изображение разрезается на страницы. Масштаб получается < rScale, потому что не учитываются
	//      |      | поля принтера. Расход бумаги меньше, чем в предыдущем случае.
	// =====+======+============================================================
	virtual HRESULT Cut(OUT mcsBoundBlocksArray& bbRes,                     // Построенные прямоугольники, которые можно отправить на печать
	                    IN OPTIONAL mcsBoundBlock* pbb = NULL,              // Область печати в pLayout или NULL, чтобы напечатать весь лист
	                    IN OPTIONAL IMcDocument* pLayout = NULL,            // Поддокумент, который нужно напечатать (IsLayout() == true). NULL = текущий лист
	                    IN OPTIONAL BOOL fFit = FALSE,                      // Не учитывать поля принтера в размерах страницы
	                    IN OPTIONAL double rScale = 0) = 0;                 // Масштаб отображения. 0 - взять глобальный масштаб

	// Plot будет не печатать, а показывать окно просмотра печати.
	virtual HRESULT SetPreview(IN BOOL fPreview) = 0;

	// Печатаем фрагмент листа или весь лист, если pRect не указывать.
	// Вернёт E_ACCESDENIED, если драйвер печати ещё не закончил предыдущее задание.
	// Можно вызывать Plot, например, из таймера, пока он не вернёт что-нибудь другое.
	//
	virtual HRESULT Plot(IN IMcDocument* pLayout = NULL,                    // Поддокумент, который нужно напечатать (IsLayout() == true). NULL = текущий лист
	                     IN OPTIONAL const mcsBoundBlock* pRect = NULL,     // Область печати в pLayout или NULL, чтобы напечатать весь лист
	                     IN OPTIONAL double rScale = 0,                     // Масштаб отображения. 0 - вписать в страницу
	                     IN OPTIONAL bool bOffMargins = false,              // Угол области печати будет совпадать с углом бумаги. Актуально для печати 1:1
	                     IN OPTIONAL LPCTSTR pszSheetName = NULL) = 0;      // Предпочтительное название листа

	// Остановка печати.
	// Для Автокада не имеет смысла, потому что он не умеет прерывать фоновую печать.
	// Отменой будет прекращение цикла вызовов Plot.
	virtual HRESULT CancelPlot() = 0;

	// Получение границ печати выбранного устройства
	virtual HRESULT GetPlotPaperMargins(double& rLeft, double& rBottom, double& rRight, double& rTop) = 0;

	// Получение размеров выбранной бумаги выбранного устройства
	virtual HRESULT GetPlotPaperSize(double& rWidth, double& rHeight) = 0;

	// Получение всех доступных бумаг и их размеров выбранного устройства
	virtual HRESULT GetPlotPaperSizes(mcsStringArray& arrMediaSysNames, mcsVector3dArray& arrMediaSizes) = 0;

	// Установка ближайшей по размеру бумаги в PAPER_SPACE по заданным габаритам
	virtual HRESULT SetLayoutBounds(
		IN IMcDocument* pLayout, 
		LPCTSTR pszDevice, 
		const mcsStringArray& arrMediaSysNames, 
		const mcsVector3dArray& arrMediaSizes, 
		const mcsBoundBlock& bb) = 0;

	// Генерация нового листа с заданным именем с созданием видового экрана по заданной области в исходном поддокументе.
	virtual HRESULT MakeSheetView(IMcDocument* pLayout, const mcsBoundBlock* pFrameBox, double rScale, LPCTSTR pszSheetName) = 0;
};
//==============================================================================
