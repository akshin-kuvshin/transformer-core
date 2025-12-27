
#pragma once

#ifdef _VERBOSEHEADERS_
#pragma message("Use " __FILE__)
#endif

#include "McAPIs.h"

#include "MCSTypes.h"
#include "McsGeometry.h"
#include "IUniEntMon.h"
#include "IMcCutter.h"

#include "3DCommon.h"
#include "3DRefKey.h"

#if _MSC_VER <= 1400
	#pragma warning(disable: 4793) // "'vararg' : causes native code generation for function ... "
#endif

class IMcs3DBuilder;

enum MdPartFeatureOperationEnum;

struct IMcsDocVariablesManager;
typedef IMcsDocVariablesManager          IMcsDocVarsMan;
typedef MObjPtr<IMcsDocVariablesManager> IMcsDocVariablesManagerPtr;
typedef MObjPtr<IMcsDocVarsMan>          IMcsDocVarsManPtr;

typedef McsArray<const McsEntityGeometry*> mcsEntityGeometryCPtrArr;

#define MC_3DPROP_3DDOCTYPE _T("3dDocType")

#ifndef OD3DENTPROJ_DEFINED
	#define OD3DENTPROJ_DEFINED
	struct Od3dEntForProj;
	typedef std::shared_ptr<Od3dEntForProj> Od3dEntForProjPtr;
#endif

typedef McsMapEx<mcsWorkID, const mcsWorkID&, McsEntityGeometry, const McsEntityGeometry&> mapWID2MEG;

//==============================================================================

// Функция сравнивает топологию двух указанных по ID солидов.
// Для сравнения геометрия одного из солидов совмещается с геометрией другого.
// Для совмещения используется матрица, передаваемая в аргументе pTfm_2_to_1.
// Матрица *pTfm_2_to_1 должна задавать перемещение второго солида к первому так, чтобы их геометрия совпала.
// Если матрица не указана, то функция сама пытается вычислить её автоматически.
M3D_API bool m3dCompareSolids(
	IN const mcsWorkID& id1,
	IN const mcsWorkID& id2,
	IN OPTIONAL const mcsMatrix* pTfm_2_to_1 = NULL,
	IN OPTIONAL const mcsTol& tol = mcsGeContext::g3dTol);

MCTYP_API
HRESULT mcsGet3dGeomSnapPoints(
	IN IMcEntity*                pEnt,
	IN McGSMarker                selMarker,
	IN OPTIONAL const mcsMatrix* pXyProjTfm,
	IN const McsEntityGeometry&  geom,
	IN McOsnapMode               osnapMode,
	IN const mcsPoint&           pickPoint,
	IN const mcsPoint&           lastPoint,
	IN OUT mcsPoint3dArray&      snapPoints);


// Для RMCS#40950, ставит изометрию ЮВ-сверху
enum McSetIsometryFlags
{
	kMcIsometryMode_IgnoreOneBref   = 1,
	kMcIsometryMode_IfInRawGCSPlane = 2,
	kMcIsometryMode_ZoomAll         = 4,
	kMcIsometryMode_Force           = 8,
};

extern "C"
MCTYP_API bool mcsSetIsometryIfNo3dObjects(DWORD dwFlags);

//==============================================================================

// Тип функции, которая получает событие построения очередной фичи в 3D-теле.
// Функция вызывается в процессе генерации 3D-тела. Обработчик не должен ничего менять в структуре объекта.
// Настоятельно рекомендована работа callback-функции в режиме "только для чтения".
//
typedef void (*On3dFeatureCreateProc)(const mcsWorkID& idHostSolid, const mcsWorkID& idSubSolid, const GUID& idMdFeature, int idxFtr);

// Добавить функцию-реактор построения очередной 3D-фичи.
// Функция глобальная и получает реакции ото всех тел в системе.
// Функций-реакторов может быть несколько.
// Они вынесены из общих событий для оптимизации.
MCTYP_API
bool mcsAdd3dFeaturesBuildingCallback(On3dFeatureCreateProc sinkProc);

// Добавить функцию-реактор построения очередной 3D-фичи.
MCTYP_API
bool mcsRemove3dFeaturesBuildingCallback(On3dFeatureCreateProc sinkProc);

MCTYP_API
int mcsCallInstalled3dFeaturesBuildingProcs(const mcsWorkID& idHostSolid, const mcsWorkID& idSubSolid, const GUID& idMdFeature, int idxFtr);

//==============================================================================
enum MdPartFeatureOperationEnum
{
	kMdJoinOperation      = 1,
	kMdIntersectOperation = 2,
	kMdCutOperation       = 3,
	kMdSurfaceOperation   = 4, // фича, создающая surface(shell).
	kMdNewBodyOperation   = 5 // ставится на первую фичу, образующую солид.
};
//==============================================================================
enum MdFeatureExtentDirectionEnum
{
	kMdPositiveExtentDirection  = 1,
	kMdNegativeExtentDirection  = 2,
	kMdSymmetricExtentDirection = 3,
	kMdDifferentExtentDirection = 4
};
//==============================================================================
enum m3dFeatureDistDirEnum
{
	kPositiveExtDir,
	kNegativeExtDir
};
//=============================================================================

//=============================================================================
#define M3D_INVALID_CATALOG_HASH -1
//=============================================================================
// anonymous interfaces declarations

IMCS_DECL_INTERFACE(I3dCatalogElement,        "00000002-0005-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(m3dIPPDef,                "00000012-0005-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(m3dCircArrIPP,            "00000013-0005-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(m3dRectArrIPP,            "00000014-0005-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(M3DExtCatalogElement,     "00010004-0005-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcsPartTool,             "F0EE0002-0005-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcsFindFeatureTool,      "F0EE0003-0005-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcsPipelineTool,         "F0EE0004-0005-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcsPartScannerTool,      "F0EE0005-0005-AAAA-AAAA-050B00000000");

IMCS_DECL_INTERFACE(IMcs3dThreadDataManager,  "F0EE0006-0005-AAAA-AAAA-050B00000000");

//==============================================================================

// Структура описывает данные замкнутого контура, построенного на основе проекций рёбер
// плоской грани 3D тела. Геометрия замкнутого контура описывается одним геометрическим примитивом:
// окружность/эллипс.
// Используется для сопоставления набора проекций, представляющих собой один и тот же геом. контур
// в теле, независимо от его разбивки на отдельные части.

struct McClosedHomogeneousProjLoopsData
{
		// к какому объекту относится контур
	mcsWorkID mIdPart;

		// данные, идентифицирующие объект, к которому относится контур
		// валидным может быть либо эскизный профиль, либо лофт, т.е. что-то одно
	mcsWorkID mIdSkProf; // ID эскизного профиля
	int       mIdxRegion; // индекс региона эскизного профиля

	mcsWorkID mIdLoft; // ID лофта
	int       mIdxLoftSection; // реальный индекс с учетом первого сечения через эскизный профиль

	int       mIdxContour; // индекс контура в сечении лофта либо в регионе эскизного профиля

	McsEntityGeometry mLoopGeom_wcs;

		// Упорядочены и размеры совпадают, i-й элемент в обоих массивах относится к одной сущности
		// Если ребро используется без проекции, соотв. эл-т mIdsProj есть WID_NULL
	mcsWorkIDArray mIdsProj, mIdsEdges;

		// Найденный новый контур, ГМТ такое же, как в mLoopGeom_wcs, но разбивка новая.
		// Используется для перестроения логической информации для восстановления контура на
		// основе новых рёбер
	McsEntityGeometry mLoopGeomNew_wcs;

	mcsWorkIDArray mIdsEdgesNew; // новый упорядоченный набор рёбер, дающий тот же контур loopGeom_wcs

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	M3D_API McClosedHomogeneousProjLoopsData();

	M3D_API void reset();

		// CallBack-процедура, вызываемая после завершения конвертации исходного контура в новом 3D-теле.
		// В момент вызова первые элементы mIdsProj, mIdsEdges, mIdsEdgesNew соотв. друг другу.
		// Если новых больше, чем исходных, значит нужно добавить новый эл-т в контур;
		// Если новых меньше, просто игнорируем лишние последние элементы в исходном списке.
	M3D_API void OnLoopConvertDone();
};

typedef McsArray<McClosedHomogeneousProjLoopsData> McClosedHomogeneousProjLoopsDataArr;

struct Mc3dBodyState;

//=============================================================================

struct I3dCatalogProvider
{
public:
	// Режим вставки стандартных объектов из каталога компонентов.
	// Не менять, пишется в файл. 
	enum CatalogType
	{
		// Вставка из каталога отключена
		kType_Disabled = 0, // не менять, должно быть строго 0

		// Каталог компонентов внедрен в документ.
		// Вставка выполняется в поддокумент, при редактировании меняется типоразмер через подмену ссылки на другой поддокумент.
		// (DWG: вставка в блок, при редактировании переключать вставку блока на другой блок)
		kType_InDoc,

		// Внешний каталог компонентов.
		// (INV: это единственно поддерживаемый тип)
		// Вставка в отдельный файл, подключение его через вставку.
		// При редактировании вставка переключается на файл с нужным типоразмером.
		// Расположение файлов определяется настройкой M3D_PARAM_CATALOG_PATH.
		// Константа пути MCS_DATA_STDPARTS_CATALOG
		// (DWG: вставка через xref, при редактировании переключать вставку блока на xref другого файла )
		kType_External,
	};

protected:
	DECLARE_OBJ_NEWDEL;

	I3dCatalogProvider() { }

public:
	virtual ~I3dCatalogProvider() { }

	virtual CatalogType catalogType()
		{ return kType_Disabled; }

	virtual HRESULT getExactStorageDir(IN OUT McsString& catalogStorDir)
		{ catalogStorDir.Empty(); return E_NOTIMPL; }

	virtual I3dCatalogElementPtr lookUp(IN IMcStdPart* pStdObj)
		{ return UNKNULL; }

	virtual I3dCatalogElementPtr createElement(IN IMcStdPart* pStdObj, IN const mcsStringArray& filesContentsShortNames, OUT OPTIONAL mcsStringArray* pFilesContentsFullPath)
		{return UNKNULL; }

	virtual I3dCatalogElementPtr createElement(IN IMcStdPart* pStdObj, IN LPCTSTR strFileShortName, OUT OPTIONAL McsString* pFileFullName)
		{ return UNKNULL; }

	virtual void invalidateElement(IN IMcStdPart* pStdObj, bool fEraseLinkedFiles = true)
		{ }
};

typedef std::shared_ptr<I3dCatalogProvider> I3dCatalogProviderPtr;
//=============================================================================

struct m3dServer
{
	virtual MComPtr<IUnknown> getNative3dApp() 
		{return NULL;}

	// Защищает каталог стандартных компонентов по указанному пути от записи.
	// (Если платформа поддерживает эту операцию).
	virtual HRESULT writeProtectCatalog(IN LPCTSTR csCatalogPath)
		{ return E_NOTIMPL; }

	virtual HRESULT dummy01(EMSP_MaterialItemArray&)
		{return E_NOTIMPL;}

	virtual HRESULT dummy02(DWORD)
		{return E_NOTIMPL;}

	virtual HRESULT MapNativeObject(IN IUnknown* pNativeObj,IN IUnknown* pUnkHostDocument,OUT mcsWorkID& ID)
		{ID.setNull(); return E_NOTIMPL;}

	virtual CComPtr<IUnknown> GetNativeObject(const mcsWorkID& MappedID)
		{return NULL;}

	virtual HRESULT GetIDInfo(const mcsWorkID& MappedID, OUT OPTIONAL IMcDocument** pp3dDoc=NULL, OUT OPTIONAL GUID* pNativeObjType=NULL)
		{return E_NOTIMPL;}

	// adds/removes specific painter to synchronize its 3d nodes with native transactions
	virtual HRESULT trans_AddPainter(IN const mcsWorkID& idPainter) 
		{return E_NOTIMPL;}

	virtual HRESULT trans_RemovePainter(IN const mcsWorkID& idPainter) 
		{return E_NOTIMPL;}

	// DEBUG
	virtual void CheckStability() {}

	enum PartObjectType
	{
		kPartType_Err          = -1,
		kPartType_NonMcs       =  0,
		kPartType_OutOfCatalog =  1,
		kPartType_Catalog      =  2,
		kPartType_Inpart       =  3,
	};

		// реализация не должна использовать одноименный метод из <gp3dsite>
	virtual PartObjectType getPartObjectInfo(const mcsWorkID&)
		{ return kPartType_Err; }

	virtual HRESULT getNormalToFace(
		const mcsWorkID& idFace,
		const mcsPoint&  ptNearFace,
		OUT mcsPoint&    ptClosestOnFace,
		OUT mcsVector&   vOuterNormal)
		{ return E_NOTIMPL; }

	virtual HRESULT intersectFaceByRay(
		const mcsWorkID&               idFace,
		const mcsPoint&                ptRayStart,
		const mcsVector&               vRayDir,
		OUT mcsPoint3dArray&           intrPoints, // intersection points
		OUT OPTIONAL mcsVector3dArray* pIntrNormals = NULL, // outer normals
		IN OPTIONAL double             rayRadius = -1)
		{ return E_NOTIMPL; }

		// Пытается получить для указанного объекта изолированное превью в виде проволочной модели.
		// Изолированное превью означает, что указанный объект просто строится без булевых операций
		// с другими солидами или фичами в детали. Если, к примеру, на ребрах выдавливания построена
		// фаска, то изолированное превью выдавливания не будет отражать этот факт.
		// Если изолированное превью получить нельзя, то ожидается получение превью объекта в текущем
		// состоянии. Предполагается, что для криволинейных поверхностей, в дополнение к ограничивающим
		// их рёбрам, в превью будут включены изолинии, описывающие характер кривизны поверхности.
		// Пример: полная сфера вообще не имеет рёбер, её превью можно составить только из изолиний.
	virtual HRESULT getIsolatedWiresForObj(
		IN const mcsWorkID&  idObject, // solid, feature
		IN bool              fDrawWholeSolid, // true = получить превью для всех подсолидов в детали, содержащей указанный подсолид
		OUT mcsGeomEntArray& wiresGeom)
	{
		wiresGeom.RemoveAll();
		return E_NOTIMPL;
	}

	// (!) Режимы получения геометрии методом getFEVGeometry
	// значения IdMatch и Cache - это не флаги, допустимо объединять по OR только
	// одно из IdMatch и одно из Cache

	enum FEVGeomQueryMode
	{
			// Поиск объекта по точному совпадению ID. Без учета изменений (обрезки, склеивания, искажения).
			// Например, если ребро укоротилось после интеграции в тело вырезающей фичи, то требует
			// версию ребра без этой обрезки.
		kIdMatchExact            = 0x01,

			// Поиск объекта по указанному ID игнорируя возможные изменения геометрии элемента в модели
			// в процессе построения (обрезка, склеивание, искажение)
		kIdMatchExactAndModified = 0x02,

			// То же, что kIdMatchExactAndModified, но дополнительно проверяется, есть ли
			// в модели более ранние версии объекта. К примеру, если мы ищем версию укороченного
			// ребра, то по запросу с этим кодом мы можем получить исходную версию ребра
			// без обрезки.
		kIdMatchAnyPossible      = 0x03,
		// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

		kIdMatch_mask            = 0x0F,

		kCacheAuto               = 0x10, // Сначала искать в модели, потом в кэше
		kCacheForce              = 0x20, // Искать только в кэше
		kCacheIgnore             = 0x30, // Искать только в модели
		// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

		kCache_mask              = 0xF0,

			// Требуются точные границы геометрии. Имеет смысл, например, для Surface-геометрии.
			// Конусы, цилиндры и т.п. без этого флага будут давать геометрию без границ
			// по направлениям параметров u,v. Запросы без этого флага выполняются быстрее.
		kEnvelopeExact           = 0x100,

			// Блокировать обновление кэша.
			// Флаг предотвращает любое изменение кэша.
			// Полезно использовать в случаях, когда геометрия запрашивается вне момента, когда
			// можно менять кэш. Например, объект "Резьба" может запрашивать геометрию модели
			// не в момент её перестроения. Сохранение геометрии в этот момент может приводить к
			// лишним обновлениям солида-владельца кэша и сбоям на этапе 3D конверсии.
		kCacheLock               = 0x200,
		// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

			// Значение рекомендовано для получения геометрии Face/Edge/Vertex в интерактивном
			// режиме в процессе пользовательского ввода (в процессе выполнения команд/редактирования)
		kAnyPossible = kIdMatchAnyPossible | kCacheAuto,

			// Значение рекомендовано для доступа к геометрии Face/Edge/Vertex из объектов,
			// которые сохраняют idFEV в своём состоянии.
			// Например, эскизная проекция сохраняет id проецируемого объекта. В этом случае проекция
			// должна работать с геометрией объекта, которая была в момент "до проекции".
		kExactGeom   = kIdMatchExact | kCacheAuto | kEnvelopeExact,
	};

		// получение геометрии Face/Edge/Fertex в координатах ГСК
	virtual HRESULT getFEVGeometry(
		IN const mcsWorkID&    idFEV,
		OUT McsEntityGeometry& geom,
		IN OPTIONAL DWORD dwModeFlags = m3dServer::kExactGeom)
	{
		geom.setNull();
		return E_NOTIMPL;
	}

		// Проверка пересечений 3D тела/грани и луча заданного диаметра;
		// позволяет получить точки и опционально нормали (наружу из тела) в этих точках,
		// Если задан массив pFaceIDs, то для каждой точки заполнит ID грани, к которой она относится
	virtual HRESULT rayTest3dEntity(
		const mcsWorkID&               id3dEnt,
		const mcsPoint&                ptRayStart,
		const mcsVector&               vRayDir,
		double                         rayRadius,
		OUT mcsPoint3dArray&           points,
		OUT OPTIONAL mcsVector3dArray* pNormals = NULL,
		OUT OPTIONAL mcsWorkIDArray*   pFaceIDs = NULL)
	{
		points.RemoveAll();
		if(pNormals)
			pNormals->RemoveAll();
		if(pFaceIDs)
			pFaceIDs->RemoveAll();
		return E_NOTIMPL;
	}

		// Выдаёт экстент для Face/Edge/Vertex в ГСК.
		// Работает быстрее, чем запрос в getFEVGeometry и затем получение bounds по геометрии.
		// К тому же позволяет получить точные границы поверхностей, что невозможно получить через
		// объект McsEntityGeometry
	virtual HRESULT getFEVExtent(IN const mcsWorkID& idFEV, OUT mcsBoundBlock& extent)
	{
		extent.invalidate();
		return E_NOTIMPL;
	}

		// Возвращает только набор Faces/Edges/Vertices связанных с указанным объектом
		// Объект может быть: Face/Edge/Vertex/IMc3dSolid
		// dwFilter:
		//   kMcsSurfaceEntities - возвращает все связанные грани
		//   kMcsCurveEntities   - ... рёбра
		//   kMcsVertex          - ... вершины.
		// Возможно указание типизированного фильтра. Например - только кольцевые рёбра,
		// или только плоские поверхности. (любое значение из допустимого множества).
		// Если fIdDefinesWhole3dObj = true, тогда в качестве исходного объекта
		// будут взяты все подобъекты, входящие в деталь, определяемую подобъектом id3dObjOrFEV.
	virtual HRESULT getLinkedFEVsToObj(
		IN const mcsWorkID& id3dObjOrFEV,
		IN DWORD            dwFilter,
		OUT mcsWorkIDArray& idsLinkedFEVs,
		IN OPTIONAL bool    fIdDefinesWhole3dObj = false)
	{
		idsLinkedFEVs.RemoveAll();
		return E_NOTIMPL;
	}

		// проверяет, доступен ли указанный Face/Edge/Vertex в модели,
		// Опционально может выдать ID для самой последней версии объекта с учетом всех изменений.
		// Также возможно получить все последние версии объекта в случае, когда его текущее
		// соответствие неоднозначно. Например, поверхность была разрезана на несколько частей
		// с момента её первичной идентификации.
	virtual bool isAliveFEV(
		const mcsWorkID&             idFEV,
		OUT OPTIONAL mcsWorkID*      pLatestSingleMatchedID = NULL,
		OUT OPTIONAL mcsWorkIDArray* pLatestMultipleMatchedIDs = NULL)
	{
		if(pLatestSingleMatchedID)
			*pLatestSingleMatchedID = idFEV;

		if(pLatestMultipleMatchedIDs)
		{
			pLatestMultipleMatchedIDs->RemoveAll();
			if(!idFEV.IsNull())
				pLatestMultipleMatchedIDs->Add(idFEV);
		}

		return false;
	}

		// Ожидается, что метод выполнит очистку временных данных на объекте
		// с целью экономии памяти. Если объект в 3d сервере что-то кэширует для себя,
		// то это тот самый момент, когда нужно всё почистить за собой
	virtual HRESULT cleanupObjectDataCache(const mcsWorkID& idObject)
	{
		return E_NOTIMPL;
	}

		// Экспортирует указанные объекты в формат SAT, указанной версии в файл по указанному пути.
	virtual HRESULT exportToSAT(const mcsWorkIDArray& ids, LPCTSTR lpszTargetSAT, int version)
	{
		return E_NOTIMPL;
	}

	// (!) не менять, пишется в файл
	enum ModelerType
	{
		kUnk  = 0,
		kAcad = 1,
		kINV  = 2,
		kACIS = 3,
		kC3D  = 4,
	};

		// возвращает тип активного ядра 3D-моделирования
	virtual ModelerType getModelerType() {
		return kUnk;
	}

	virtual DWORD getModelerVer() {
		return 0;
	}

	struct findFEVresItem
	{
		McFEVRefKeyData         RKD;
		McsEntityGeometry       geom;
		bool                    bReversed;
		McGeomOverlapStatusEnum matchDegree; // степень совпадения

		// Для плоской грани содержит корректирующий сдвиг её локальной СК
		mcsMatrix         planeCorrTfm;

		findFEVresItem() {
			matchDegree = kMcGeomOvl_NotOverlapped;
			bReversed = false;
		}
	};

	typedef McsArray<findFEVresItem> findFEVresItemsArr;

		// Выполняет поиск FEV в теле по геометрии.
		// На выходе даёт список найденных ref-ключей и текущую геометрию.
		// Используется, например, при переключении низкоуровневого моделера.
		// Возвращает кол-во сопоставленных элементов.
		// Если результат не ноль, то массив result на выходе содержит столько же элементов,
		// сколько на входе есть в geomArr.
		// Если какой-то элемент не был сопоставлен, то соответствующая ячейка в result будет null
	virtual int findFEVByGeometry(
		const mcsWorkID&          idPart,
		IN const mcsGeomEntArray& geomArr, // ГСК
		IN const mcsTol&          tol,
		OUT findFEVresItemsArr&   result) // ГСК
	{
		result.SetSize(0);
		return 0;
	}

		// Выполняет поиск цепочек ребер в теле, чья геометрия повторяет
		// с заданной точностью данные замкнутые контуры.
		// Возвращает кол-во успешно найденных контуров
	virtual int findFEVByGeometryLoops(
		const mcsWorkID&                            idPart,
		IN OUT McClosedHomogeneousProjLoopsDataArr& loopsData,
		IN const mcsTol&                            tol)
	{
		return 0;
	}

	virtual bool facetHoledArea(
		IN const CHoledArea& holedArea,
		IN double            dTol,
		OUT mcsPoint3dArray& facets,
		OUT mcsDwordArray&   indices)
	{
		indices.SetSize(0);
		facets.SetSize(0);
		return false;
	}


		/// Возвращает клон тела указанного объекта.
		/// Используется как метод для получения тела с параметрической 3D модели.
	virtual IMc3dSolidPtr clone3dSolidBodyAndPurgeHistory(const IMc3dSolid* pSolid)
	{
		return UNKNULL;
	}

		// Возвращает ключ для FEV по его маркеру
	virtual HRESULT getRefKeyByGsm(const mcsWorkID& id3dEnt, McGSMarker gsm, OUT McFEVRefKeyData& RKD)
	{
		RKD.setNull();
		return E_NOTIMPL;
	}

		// Возвращает для FEV маркер по ключу
	virtual HRESULT getGsmByRefKey(const mcsWorkID& id3dEnt, const McFEVRefKeyData& RKD, OUT McGSMarker& gsm)
	{
		gsm = -1;
		return E_NOTIMPL;
	}

	// Метод устанавливает в указанном солиде низкоуровневую модель 3d ядра.
	// Если bModelInLocalCS == true, переданная модель находится в локальных координатах,
	// В этом случае сохраняется положение объекта, меняется лишь его локальная модель.
	//
	virtual HRESULT set3dModelFor3dEnt(IMc3dSolid* pSolid, INT_PTR p3dModelerObject, bool bModelInLocalCS = false)
	{
		return E_NOTIMPL;
	}

		// метод получает из указанного 3D-объекта низкоуровневую модель 3d ядра
	virtual INT_PTR get3dModelFrom3dEnt(IMcEntity* p3dEnt)
	{
		return 0;
	}

	// Метод получает из указанного 3D-объекта документа низкоуровневую модель 3d ядра.
	// Если объект не является 3D-солидом, то система пытается получить его графических образ в виде 3D-сеток (mesh).
	// Каждая сеть будет преобразована в 3D-солид. И если преобразование будет успешным, то для него будет возвращена 3D-модель.
	// (!) После работы с возвращенными моделями нужно позвать метод release3dModels.
	virtual bool get3dModelsFrom3dEnt(const mcsWorkID& id3dEnt, OUT mcsIntPtrArray& models)
	{
		return false;
	}

	// Метод освобождает модели 3D-ядра. Вызывать для моделей, возвращаемых из метода get3dModelFrom3dEnt(const mcsWorkID&, ...)
	virtual bool release3dModels(const mcsIntPtrArray& models)
	{
		return false;
	}

	/// Указатель на Face/Edge/Vertex объект 3d моделера по данному ID
	virtual INT_PTR getFEVNativePtr(const mcsWorkID& idFEV)
	{
		return 0;
	}

		// преобразует mcs-кривую в кривую 3D-моделера
	virtual INT_PTR convertTo3dModelerCurve(const mcsCurve& mcCurve)
	{
		return 0;
	}

		// преобразует кривую 3D-моделера в mcs-кривую
	virtual mcsCurve* convertFrom3dModelerCurve(INT_PTR p3dModelerCrv)
	{
		return NULL;
	}

		// Метод выполняет комбинирование указанных моделей с использованием АПИ активного 3D-моделера.
		// Внимание! Освобождение возвращаемой модели - ответственность вызывающей стороны.
	virtual INT_PTR booleanOpenNative(INT_PTR model1, INT_PTR model2, MdPartFeatureOperationEnum operType)
	{
		return 0;
	}

	// Блок методов для формирования ref-ключе (ассоциативных привязок к FEV).........................

	// ID текущей строящейся фичи, ID уникален в пределах одного тела
	virtual DWORD rk_currentFeatureID()
	{
		return -1;
	}

	// Создать новый ключ, либо по фиче, либо по элементу фичи
	virtual McFEVRefKeyData* rk_newAndInit(McModSubentType topologyType, DWORD ElemID = -1, DWORD FtrID = 0)
	{
		return NULL;
	}

	// Создать клон ключа
	virtual McFEVRefKeyData* rk_clone(IN const McFEVRefKeyData* pRKD)
	{
		return NULL;
	}

	// Добавить тэг фичи, bModifyMode означает, что фича модифицирует элемент топологии тела, не создаёт
	virtual bool rk_appendFtrID(IN OUT McFEVRefKeyData* pRKD, McModSubentType topologyType, DWORD FtrID, bool bModifyMode = false, int Index = -1)
	{
		return false;
	}

	// Добавить тэг данных, используется для придания уникальности набору данных в ключе
	virtual bool rk_appendData(IN OUT McFEVRefKeyData* pRKD, McModSubentType topologyType, DWORD Data)
	{
		return false;
	}

	// Метод позволяет повторно использовать существующий ключ
	virtual bool rk_reuse(IN OUT McFEVRefKeyData* pRKD, McModSubentType topologyType, IN const McFEVRefKeyData& KeyToReuse, DWORD FtrID = 0)
	{
		return false;
	}

	// Добавление тэга модификации в ключ. Желательно не использовать. Тэги модификации не предназначены для ручного добавления.
	// Метод существует для решения исключительных ситуаций.
	virtual bool rk_appendModify(IN OUT McFEVRefKeyData* pRKD)
	{
		return false;
	}

	// Метод смешивает первый ключ (pRKD) с данными ключа 'KeyMergeFrom'.
	virtual bool rk_mergeFrom(IN OUT McFEVRefKeyData* pRKD, IN const McFEVRefKeyData& KeyMergeFrom, DWORD FtrID = 0)
	{
		return false;
	}

	// Метод выплоняет split-операцию на ключе pRkdOrig, в него добавляется тэг SplitOriginal, в новый - SplitNew
	virtual bool rk_split(IN OUT McFEVRefKeyData* pRkdOrig, OUT McFEVRefKeyData*& pRkdNew, DWORD FtrID = 0)
	{
		pRkdNew = NULL;
		return false;
	}

	// Метод формирует составной ключ из указанного набора, индекс Index играет важную роль, из одного и того же набора ключей
	// можно сформировать разный ключ путём указания другого индекса.
	virtual bool rk_appendComposite(IN OUT McFEVRefKeyData* pRKD, McModSubentType topologyType, int Index, const McFEVRefKeyDataPtrsArray& KeysToCompose, DWORD FtrID = 0)
	{
		return false;
	}

	// Метод возвращает ссылочный ключ ассоциативной привязки для Face/Edge/Vertex
	// Вызывающая сторона отвечает за удаление возвращаемого объекта
	virtual McFEVRefKeyData* rk_getRefKeyFromNativeFEV(INT_PTR pFEV_from)
	{
		return NULL;
	}

	// Метод устанавливает ссылочный ключ ассоциативной привязки на Face/Edge/Vertex
	virtual bool rk_setRefKeyToNativeFEV(INT_PTR pFEV_to, const McFEVRefKeyData& RKD)
	{
		return false;
	}

	// Метод перебирает все поверхности, ребра и вершины указанной модели и пытается сгенерировать значения
	// ключей ассоциативных привязок на основании уже присвоенных ключей в модели.
	// Если в модели нет ни одного присвоенного ключа, метод присваивает каждому FEV индексированный ключ
	// активной фичи.
	virtual bool rk_mcid_assign(INT_PTR pModelTo)
	{
		return false;
	}

	// Метод возвращает геометрию для указанного нативного Face/Edge/Vertex объекта 3d моделера
	virtual HRESULT getGeometryForNativeFEV(INT_PTR pNativeFEV, OUT McsEntityGeometry& geom)
	{
		geom.setNull();
		return E_NOTIMPL;
	}

	// Возвращает точку на указанной грани, ближайшую к данной.
	// Вернёт false, если метод не реализован или возникла ошибка в процессе вычисления.
	virtual bool getClosestPointOnFace(const mcsWorkID& idFace, const mcsPoint& pt, OUT mcsPoint& ptOnFace)
	{
		return false;
	}

	// Вычисляет пересечение кривых, используя активный 3D моделер.
	// Возвращает 0, если метод не реализован, -1: реализован, но точки не обнаружены, +1 всё ок, точки найдены
	virtual int intersect_curve_curve(
		const mcsCurve&      mcCurve1,
		const mcsCurve&      mcCurve2,
		IN double            dTol,
		OUT cci_point_arr&   intPts)
	{
		intPts.SetSize(0);
		return 0;
	}

	// Создаёт с помощью активного 3D моделера кривую-спираль с заданными параметрами
	virtual bool createHelix(
		const mcsPoint&        center,
		const mcsVector&       axisDir,
		double                 radius,
		double                 pitch,  // шаг между витками, измеряется вдоль оси
		double                 height, // длина спирали, измеряется вдоль оси
		bool                   bRH,    // true - "правая" спираль, false - "левая" спираль
		OUT McsEntityGeometry& helixGeom)
	{
		helixGeom.setNull();
		return false;
	}

	/// Установка цвета для нативного Face/Edge/Vertex
	virtual bool setNativeFevColor(INT_PTR pNativeFEV, COLORREF clr)
	{
		return false;
	}

	// Выполняет клонирование указанного эскиза со всеми связанными объектами и наложенными на них 2D-зависимостями.
	// При этом отрезаются все проекции и ассоциативные связи для координатной системы эскиза.
	// idsOldToNew в случае успеха на выходе содержит мап подмены старых ID на новые.
	virtual bool cloneSketchWith2dConstraints(const mcsWorkID& idSketch, OUT mcsWId2WIdMap& idsOldToNew)
	{
		idsOldToNew.RemoveAll();
		return false;
	}

	// Метод возвращает состояние модели чужого солида, пригодное для сохранения его в DB
	// и для последующей вставки в документ.
	// на том же месте в ГСК.
	virtual bool getAlienBodySateForDB(IMc3dAlienSolid* pAlienSolid, OUT Mc3dBodyState& state)
	{
		return false;
	}

	// Получить интервал параметризации указанной грани.
	// В качестве геометрии грани используется данные 3D ядра (не аппроксимация!)
	virtual bool face_getNativeInterval(const mcsWorkID& idFace, OUT McGeInterval& uIvl, OUT McGeInterval& vIvl)
	{
		return false;
	}

	// Получить точку и нормаль по параметрам указанной грани.
	// В качестве геометрии грани используется данные 3D ядра (не аппроксимация!)
	virtual bool face_evalPoint(
		const mcsWorkID& idFace,
		double           u,
		double           v,
		OUT mcsPoint&    pt,
		OUT mcsVector&   vNormal)
	{
		return false;
	}

	// Получить ID переменной, связанной с указанным размером
	virtual mcsWorkID getVarIdByDimId(IN const mcsWorkID& idDim)
	{
		return WID_NULL;
	}

	// Получить ID размера-зависимости для указанной переменной
	virtual mcsWorkID getDimIdByVarId(IN const mcsWorkID& idVar)
	{
		return WID_NULL;
	}

	// Устанавливает новое значение для DbAssoc-переменной
	virtual bool setDbAssocVarValue(IN const mcsWorkID& idDbAssocVarVar, double val)
	{
		return false;
	}

	// Вычисляет пересечение поверхностей, используя активный 3D моделер.
	// Возвращает 0, если метод не реализован, -1: реализован, но пересечения не обнаружены, +1 всё ок, пересечения найдены.
	virtual int intersect_surf_surf(
		const McsEntityGeometry&  surfGeom1,
		const McsEntityGeometry&  surfGeom2,
		OUT mcsGeomEntArray&      intersectionCurvesGeom,
		OUT mcsPoint3dArray&      intersectionPoints,
		IN OPTIONAL const mcsTol& tol = mcsGeContext::g3dTol)
	{
		intersectionCurvesGeom.SetSize(0);
		intersectionPoints.SetSize(0);
		return 0;
	}

	// Вычислить объём указанного 3D солида
	// Объем в м^3
	virtual HRESULT calc3dSolidVolume(IN const mcsWorkID& idSolid, OUT double& vol)
	{
		vol = 0;
		return E_NOTIMPL;
	}

	// Создает пустое непараметрическое тело (AlienSolid) и добавляет его в документ.
	// Возвращается ID созданного тела.
	// Дело в том, что AlienSolid нельзя создать через вызов gpMcObjManager->createObject().
	// По смыслу этот объект создается кем-то, и уже потом мы к нему подключаемся.
	virtual mcsWorkID createAndAppendAlienSolidToDoc(IMcDocument* pDocTo = NULL)
	{
		return WID_NULL;
	}

	// Возвращает для указанной поверхности геометрию контуров.
	// Первый контур в массиве - внешний, остальные - внутренние.
	virtual HRESULT getFaceLoops(IN const mcsWorkID& idFace, OUT mcsPolylineArray& loops)
	{
		return E_NOTIMPL;
	}

	// Установка необходимости писать родные модели активного 3D-ядра в файл.
	// = 0 - автоматически
	// > 0 - да
	// < 0 - нет
	virtual bool setNeedWriteNative3dModelsToFiles(int iWrite)
	{
		return false;
	}

	// Возвращает провайдер каталога компонентов указанного типа
	// Документ используется для внедренного в документ каталога, если NULL, будет взят текущий документ.
	virtual I3dCatalogProviderPtr catalogProvider(I3dCatalogProvider::CatalogType eCatalogType, IMcDocument* pDoc = NULL)
	{
		return NULL;
	}
};
//=============================================================================

// структура содержит информацию, необходимую для синхронизации std-объекта с базой

struct IMcStdPart;
class IDBElement;

struct m3dDbElementSyncData
{
	// значения вроде: MCS_DBMODEL_IPT, MCS_DBMODEL_M3D ...
	DWORD    mDbModelDocType;

	// время последнего обновления связанного стд. объекта в базе, обновляется в момент UpdateModel
	// для всех std-объектов из базы через интерфейс IDBElement
	__int64  mStdDbElementModTime;

	// содержит кол-во документов с типом mDbModelDocType
	int      mnDocsInDB;

	// содержит сумму всех времён последнего обновления документов с типом,
	// соотв. типу объекта
	__int64  mSumDocsModTime;
	//............................................................................

	M3D_API m3dDbElementSyncData();

	M3D_API void setNull();
	M3D_API bool init(IMcStdPart* pSMO, DWORD dbModelsType);

	M3D_API UINT hash() const;

	M3D_API bool isEqualTo (const m3dDbElementSyncData& cw) const;
	M3D_API bool areModelsEqualTo (const m3dDbElementSyncData& cw) const;

	M3D_API bool write(IMcsStream* pS) const;
	M3D_API bool read(IMcsStream* pS);
};
//===========================================================================

struct I3dCatalogElement : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(I3dCatalogElement);
	IMCS_STD_METHOD_DEFINITION(I3dCatalogElement,IMcObject);

	virtual HRESULT getFileContents(OUT mcsStringArray& files) = 0;
	virtual void    invalidate() = 0;
	virtual HRESULT isValid(bool fCheckFileContents) = 0;
};

typedef MComQIPtr<I3dCatalogElement> I3dCatalogElementPtr;
typedef McsArray<I3dCatalogElementPtr, I3dCatalogElement*> I3dCatalogElements;

//=============================================================================

// Интерфейс управления каталогом стандартных компонентов
struct I3dCatalog
{
protected: 
	I3dCatalog() { }

public:
	DECLARE_OBJ_NEWDEL;

	virtual ~I3dCatalog() { }

	MCTYP_API virtual I3dCatalogProvider::CatalogType isEnabled();
	MCTYP_API virtual HRESULT enable(I3dCatalogProvider::CatalogType newCatalogType);

	// не должен возвращать NULL,
	// если провайдера нет, нужно вернуть результат вызова I3dCatalog::provider()
	MCTYP_API virtual I3dCatalogProviderPtr provider();

	// реализация методов ниже по умолчанию перенаправляет вызовы в активный провайдер каталога
	MCTYP_API virtual HRESULT getExactStorageDir(IN OUT McsString& catalogStorDir);
	MCTYP_API virtual I3dCatalogElementPtr lookUp(IN IMcStdPart* pStdObj);
	MCTYP_API virtual I3dCatalogElementPtr createElement(IN IMcStdPart* pStdObj, IN const mcsStringArray& filesContentsShortNames, OUT OPTIONAL mcsStringArray* pFilesContentsFullPath);
	MCTYP_API virtual I3dCatalogElementPtr createElement(IN IMcStdPart* pStdObj, IN LPCTSTR strFileShortName, OUT OPTIONAL McsString* pFileFullName);
	MCTYP_API virtual void invalidateElement(IN IMcStdPart* pStdObj, bool fEraseLinkedFiles = true);
};

extern M3D_API I3dCatalog* gp3dCatalog;
//=============================================================================

// (!) значения не менять, пишутся в файл
enum m3dPartPosDefTypeEnum
{
	kM3DIPPosDef_Unk              = 0,

	kM3DIPPosDef_2Edges           = 1,
	kM3DIPPosDef_2Vertices        = 2,
	kM3DIPPosDef_Concentric       = 3,
	kM3DIPPosDef_Radial           = 4,
	kM3DIPPosDef_Fixed            = 5,

	kM3DIPPosDef_Arr_AlongEdges   = 100, // вдоль ребер
	kM3DIPPosDef_Arr_Circ         = 101, // круговой
	kM3DIPPosDef_Arr_Rect         = 102, // прямоугольный

	kM3DIPPosDef_Dependent        = 200, // dependent projection of parent's origin
	kM3DIPPosDef_PartCS           = 201, // wrapper to Part's coordinate system
};

typedef McsArray<m3dPartPosDefTypeEnum> m3dPartPosDefTypeEnumArr;

//==================================================================================================

extern "C" M3D_API void m3dCreateIPP(m3dPartPosDefTypeEnum ippType, OUT m3dIPPDefPtr& pIPP);

__inline m3dIPPDefPtr m3dCreateIppDyn(m3dPartPosDefTypeEnum ippType)
{
	static FARPROC ls_pCreateProc = (FARPROC)-1;
	if(ls_pCreateProc == (FARPROC)-1)
	{
		ls_pCreateProc = NULL;
		if(HMODULE hM3D = GetModuleHandleA("M3D.DLL"))
			ls_pCreateProc = GetProcAddress(hM3D, "m3dCreateIPP");
	}

	m3dIPPDefPtr pIPP;
	if(ls_pCreateProc)
		( (void(*)(m3dPartPosDefTypeEnum, m3dIPPDefPtr&) ) ls_pCreateProc) (ippType, pIPP);
	return pIPP;
}
//==================================================================================================

struct m3dIPPDef : public virtual IMcObject
{
	IMCS_QI_METHOD_DEFINITION(m3dIPPDef, IMcObject);
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(m3dIPPDef);

	// возвращает ID детали, на которой выполнено размещение
	virtual mcsWorkID get1stPartID() const = 0;

	// возвращает пакет деталей для болтового соединения, либо просто ID детали с опорной плоскостью
	virtual mcsWorkIDArray getPartsIDs() const = 0;

	virtual mcsWorkID getTargetPlaneId() const = 0;
	virtual void      setTargetPlaneId(const mcsWorkID& id) = 0;

	virtual m3dPartPosDefTypeEnum defType() const = 0;

	// Преобразует в тип "точка на плоскости".
	virtual HRESULT setFixedDef(IN OPTIONAL const mcsPoint* pPosition = NULL) = 0;

	// Кол-во позиций для указанной размерности,
	// Для одиночных позиций и Для кругового массива кол-во размерностей = 1
	// Для прямоугольного массива кол-во размерностей = 2
	virtual int  numPositions(int iDim = 0) const = 0;
	virtual bool setNumPositions(int n, int iDim = 0) = 0;

	// матрица вставки для указанной позиции
	// СК матрицы задана так: начало СК совпадает с позицией, оси X,Y лежат в плоскости targetPlane,
	// ось Z - нормаль плоскости targetPlane
	virtual HRESULT getPosition(OUT mcsMatrix& tfmIppToWorld, int idx1, int idx2 = 0) const = 0;

	// глубина детали idxPart в позиции idx1,idx2,
	// Если idxPart < 0, возвращает полную глубину всех деталей в указанной позиции.
	// если значение неизвестно, не посчитано либо указаны неверные данные, возврат = UNKNOWNVALUE
	virtual double  getDepth(int idx1, int idx2 = 0, int idxPart = -1, bool bRecalc = false) const = 0;

	virtual HRESULT save(IMcsStream*) const = 0;
	virtual HRESULT load(IMcsStream*) = 0;

	// Все ассоциативные привязки, использующиеся при образмеривании
	// Параметры по типам размещения:
	// kM3DIPPosDef_2Edges:     edge1, edge2
	// kM3DIPPosDef_2Vertices:  vtx1(pt/curve_w_center), vtx2(pt/curve_w_center)
	// kM3DIPPosDef_Concentric: vtx(pt/curve_w_center)
	// kM3DIPPosDef_Radial:     vtx(pt/curve_w_center), dir((pt/curve_w_center)/curve)
	// kM3DIPPosDef_Fixed       -
	// kM3DIPPosDef_Arr_Circ    (то же, что и для kM3DIPPosDef_Radial)
	// kM3DIPPosDef_Arr_Rect    (то же, что и для kM3DIPPosDef_2Edges);
	//
	virtual HRESULT getAssocParams(OUT McGeometryParamArray& assocLinks) const = 0;
	virtual void    setAssocParams(const McGeometryParam& fParam, const McGeometryParam& sParam) = 0;

	// методы ниже позволяют получить числовые параметры размещения
	// kM3DIPPosDef_2Edges:     dist to edge1, dist to edge2
	// kM3DIPPosDef_2Vertices:  dist to vtx1(pt/curve_w_center), dist to vtx2(pt/curve_w_center)
	// kM3DIPPosDef_Concentric: -
	// kM3DIPPosDef_Radial:     dist to vtx(pt/curve_w_center), angle(radians) from dir((pt/curve_w_center)/curve)
	// kM3DIPPosDef_Fixed       -
	// kM3DIPPosDef_Arr_Circ    (то же, что и для kM3DIPPosDef_Radial)
	// kM3DIPPosDef_Arr_Rect    (то же, что и для kM3DIPPosDef_2Edges);
	virtual double getParam1() const = 0;
	virtual double getParam2() const = 0;

	virtual bool setParam1(double prm) = 0;
	virtual bool setParam2(double prm) = 0;

	virtual M3D_API m3dIPPDefPtr getCopy() const;
};
//==================================================================================================

// образмеривание позиции в 3D-детале - круговой массив
struct m3dCircArrIPP : public virtual m3dIPPDef
{
	IMCS_QI_METHOD_DEFINITION(m3dCircArrIPP, m3dIPPDef);
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(m3dCircArrIPP);

	// получить центр массива, точка в ГКС, на плоскости, где размещаются элементы массива
	virtual mcsPoint getRotationCenter() const = 0;

	// получить угловой шаг между элементами,
	// положительное значение - против часовой стрелки относительно нормали плоскости размещения элементов массива
	virtual double   getStepAng() const = 0;
	virtual bool     setStepAng(double step) = 0;

	// получить параметр привязки, определяющий ось вращения
	virtual McGeometryParam getAxisParam() const = 0;
	virtual bool            setAxisParam(const McGeometryParam& axisPrm) = 0;

	// признак реверса направления оси, заданной параметрической привязкой
	virtual bool isReversed() const = 0;
	virtual void setIsReversed(bool bRev) = 0;
};
//==================================================================================================

// образмеривание позиции в 3D-детале - прямоугольный массив
struct m3dRectArrIPP : public virtual m3dIPPDef
{
	IMCS_QI_METHOD_DEFINITION(m3dRectArrIPP, m3dIPPDef);
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(m3dRectArrIPP);

	// получить первое направление, в ГСК, вектор должен лежать в плоскости размещения элементов массива
	virtual mcsVector getDir1() const = 0;

	// получить второе направление, в ГСК, вектор должен лежать в плоскости размещения элементов массива,
	// если массив линейный, то вектор должен быть нулевой длины
	virtual mcsVector getDir2() const = 0;

	// получить шаг элементов вдоль 1-го направления, положительное значение - по направлению dir1
	virtual double    getStep1() const = 0;
	virtual bool      setStep1(double step) = 0;

	// получить шаг элементов вдоль 2-го направления, положительное значение - по направлению dir2
	// если массив линейный, возвращает 0
	virtual double    getStep2() const = 0;
	virtual bool      setStep2(double step) = 0;

	// получить параметр привязки первого направления
	virtual McGeometryParam getDir1Param() const = 0;
	virtual bool            setDir1Param(const McGeometryParam& dir1Prm) = 0;

	// получить параметр привязки второго направления (может быть isNull(), если массив линейный)
	virtual McGeometryParam getDir2Param() const = 0;
	virtual bool            setDir2Param(const McGeometryParam& dir2Prm) = 0;

	// признак реверса первого направления
	virtual bool isDir1Reversed() const = 0;
	virtual void setIsDir1Reversed(bool bRev) = 0;

	// признак реверса второго направления
	virtual bool isDir2Reversed() const = 0;
	virtual void setIsDir2Reversed(bool bRev) = 0;
};
//==================================================================================================



//=============================================================================
struct McBendSection
{
	mcsLine  cylAxis; // ось цилиндра отвода
	double   Rext;    // внешний радиус цилиндра
	double   thick;   // толщина стенки
	mcsPlane cutPlane1, cutPlane2; // плоскости сечения
	COLORREF color;
};

typedef McsArray<McBendSection> McBendSectionsArray;

//=============================================================================

// Интерфейс управления панелью вставки стандартных объектов

struct IEMStdPanel
{
	virtual ~IEMStdPanel() {}

	// Режим вставки стандартных объектов
	// (!) Значения не менять, сохраняются в настройках
	enum StdPartPlacementMode
	{
		kPlacementMode_Unk     = 0,

		// Вставка объекта вместе с объектами истории построения в активный документ.
		// Под INV используется только для врезных объектов
		kPlacementMode_Inplace,

		// Вставка в поддокумент, при редактировании менять типоразмер подменой на другой поддокумент
		// (DWG: вставка в блок, при редактировании переключать вставку блока на другой блок)
		kPlacementMode_InDocCatalog,

		// Вставка в поддокумент, при редактировании менять типоразмер через изменение переменных в поддокументе
		// (DWG: вставка в блок, при редактировании менять параметры в блоке)
		kPlacementMode_InDocPrivate,

		// Вставка в отдельный файл, подключение его через вставку.
		// При редактировании вставка переключается на файл с нужным типоразмером.
		// Расположение файлов определяется настройкой M3D_PARAM_CATALOG_PATH.
		// Константа пути MCS_DATA_STDPARTS_CATALOG
		// (DWG: вставка через xref, при редактировании переключать вставку блока на xref другого файла )
		// (INV: это единственно поддерживаемый режим)
		kPlacementMode_ExtCatalog,

		// Вставка в отдельный файл, подключение его через вставку.
		// При редактировании меняются параметры во внешнем подключенном файле.
		// Расположение файлов определяется настройкой M3D_PARAM_CATALOG_PATH.
		// Константа пути MCS_DATA_STDPARTS_CATALOG
		// (DWG: вставка через xref, при редактировании меняются параметры модели в подключенном файле)
		kPlacementMode_ExtPrivate,
	};

	// показать/скрыть окно панели
	virtual HRESULT show(bool bShow) = 0;

	// Получить данные текущего выбранного в панели материала
	// Список материалом и их данные берутся из метода IMcNativeGate::getMaterialsList()
	virtual DWORD   getSelectedMaterialData() = 0;

	// Установка строки вставляемого объекта. Она просто отображается в панели для информации.
	virtual HRESULT setObjectString(LPCTSTR) = 0;

	// Управление режимом вставки стандартных объектов
	virtual StdPartPlacementMode getStdPartPlacementMode() = 0;
	virtual HRESULT              setStdPartPlacementMode(StdPartPlacementMode newMode) = 0;

	// Если fEnable = true, показывает в панели флажок управления вставкой объектов в подсборку,
	// при этом флажок включается и режим активируется,
	// Если false, то флажок скрывается из панели, режим вставки в подсборку выключается.
	// Сам же режим вставки в подсборку выставляется через метод gpMcObjManager->setSubAsmMode().
	// Вставкой в подсборку управляет сам менеджер автоматически.
	//
	virtual HRESULT enableSubAsmMode(bool fEnable) = 0;
};

typedef std::shared_ptr<IEMStdPanel> IEMStdPanelPtr;

//=============================================================================

// данные используются для позиционирования M3DH моделей в пространстве.

struct m3dh_cs
{
	// id рабочей точки с исходным именем Origin/WPT01,
	// Если WID_NULL, геометрия точки = mcsPoint::kOrigin
	mcsWorkID idOrigin;

	// id рабочих осей с исходными именами X/WA01, Y/WA02 соответственно.
	// Если WID_NULL. геометрия прямых = mcsLine::kXAxis, mcsLine::kYAxis соответственно
	mcsWorkID idX, idY;

	MCTYP_API void      reset();
	MCTYP_API mcsMatrix getCS() const; // возвращает положение СК в пространстве
};
//=============================================================================

struct IMc3dSite
{
	// 3D parts/assemblies catalog
	virtual INT_PTR dummy01()
		{return 0;}

	virtual HRESULT     dustMan_AcceptDocToErase(IN const mcsWorkID& docID, IN LPCTSTR fullPath)
		{return E_NOTIMPL;}
	virtual HRESULT     dustMan_DeclineErase(IN const mcsWorkID& docID)
		{return E_NOTIMPL;}
	virtual HRESULT     dustMan_AcceptDocToErase(IN IUnknown* pDoc, IN LPCTSTR fullPath) 
		{return E_NOTIMPL;}
	virtual HRESULT     dustMan_DeclineErase(IN IUnknown* pDoc)
		{return E_NOTIMPL;}

	virtual mcsWorkID   dummy02( const mcsWorkID&, IUnknown*)
		{return WID_NULL;}
	virtual CComPtr<IUnknown> dummy03(const mcsWorkID&, IUnknown*)
		{return UNKNULL;}
	virtual HRESULT     dummy04(const mcsWorkID&, IUnknown*)
		{return E_NOTIMPL;}
	virtual HRESULT     dummy05(const mcsWorkID&)
		{return E_NOTIMPL;}

	virtual HRESULT helper_cvtRevCoutourToCones(IN const mcsPolyline& contour,IN const mcsLine& axis,IN COLORREF clr,OUT mcsGeomEntArray& cones)
		{return E_NOTIMPL;}

	virtual bool dummy06(const IMcStdPart*)
		{return false;}
	virtual bool dummy07(const IMcStdPart*)
		{return false;}
	virtual bool dummy08(const IMcStdPart*)
		{return false;}
	virtual bool dummy09(const IMcStdPart*)
		{return false;}
	virtual bool dummy10(IN const IMcStdPart*)
		{return false;}
	virtual bool dummy11(const IMcStdPart*)
		{return false;}
	virtual bool dummy12(const IMcStdPart*)
		{return false;}

	// Определяет, имеет ли указанный объект 3D тело
	virtual bool isPartObject(IN IMcObject* pObject)
		{ return false; }

	// EM std panel
	virtual HRESULT dummy13()
		{return E_NOTIMPL;}
	virtual HRESULT dummy14()
		{return E_NOTIMPL;}
	virtual DWORD dummy15()
		{return -1;}
	virtual HRESULT dummy16(LPCTSTR)
		{return E_NOTIMPL;}
	virtual HRESULT dummy17()
		{return E_NOTIMPL;}
	virtual HRESULT dummy18(bool)
		{return E_NOTIMPL;}

	// common 3D Builder
	virtual IMcs3DBuilder* get3dBuilder()
		{ return NULL; }

	// Access to M3D-tools
	MCTYP_API virtual IMcsPartToolPtr        GetPartTool();
	MCTYP_API virtual IMcsFindFeatureToolPtr GetFindFeatureTool();
	MCTYP_API virtual IMcsPipelineToolPtr    GetPipelineTool();
	MCTYP_API virtual IMcsPartScannerToolPtr GetPartScannerTool();

	virtual HRESULT getBendSectionsPreview(IN const McBendSectionsArray& bsa, IN bool fAxisSection, OUT CxImage& cxi) 
		{return E_NOTIMPL;}

	virtual HRESULT getPipesConnectionPreview
		(IN const mcsGeomEntArray& sketches,
		 IN const mcsLine& axis,
		 IN bool fAsixSection,
		 OUT CxImage& preview,
		 IN double samplePointsTol = 0.2)
		{return E_NOTIMPL;}

		// if you specify 'bShowNoticeIfNot' = true then notice concerning license absence will be shown to user
		// 'false' value means "no any notice" = "quiet mode"
	virtual bool is3dModLicensed(bool bShowNoticeIfNot) {
		return false;
	}

	virtual bool is3dModEnabled() {
		return false;
	}

		// системное, используется для отладочных целей
	virtual void _logMsg(LPCTSTR lpszFormat, DWORD rgbColor = 0, ...) {}
	virtual void _log(int iCode, ...) {}

		// получает список всех зависящих объектов от данного (в дереве построения 3D) и подавляет эти элементы
	virtual HRESULT beginEdit3dItem(const mcsWorkID& itemID) {
		return E_NOTIMPL;
	}

		// восстанавливает элементы, подавленные вызовом m3dBeginEdit3dItem
	virtual HRESULT endEdit3dItem(const mcsWorkID& itemID) {
		return E_NOTIMPL;
	}

	// находит в указанном документе (или активном) редактируемый эскиз
	virtual IMcPlanarSketchPtr getActiveEditSketch(IN OPTIONAL IMcDocument* pDoc = NULL) {
		return UNKNULL;
	}

	virtual mcsWorkID getActiveEditSketchID(IN OPTIONAL IMcDocument* pDoc = NULL) {
		return WID_NULL;
	}

	// находит в указанном документе (или активном) редактируемый эскиз и завершает его редактирование
	virtual HRESULT exitSketchEditMode(IN OPTIONAL IMcDocument* pDoc = NULL)
	{
		return E_NOTIMPL;
	}

		// создаёт планарный эскиз на указанной плоскости (Face, WorkPlane)
	virtual HRESULT createPlanarSketch(
		IN  const mcsWorkID&    idPlanarObject,    // WPL или плоская грань солида
		IN  bool                fProjectFaceEdges, // если idPlanarObject - это плоская грань солида, то может спроецировать все его рёбра на эскиз
		OUT IMcPlanarSketchPtr& pSketch)
	{
		pSketch = UNKNULL;
		return E_NOTIMPL;
	}

		// Реализация интерфейса IMc3dFEVGeomCache должна звать эту функцию в случае успешного
		// выполнения метода IMc3dFEVGeomCache::getGeometryByRefKey. Функция запомнит ключ 
		// сгенерированной геометрии и на конец команды проверит, сохранил ли какой-либо
		// объект на неё ссылку, если такого не будет, то позовётся метод
		// IMc3dFEVGeomCache::dropUnusedGeometry для очистки неиспользуемой геометрии
	virtual HRESULT onCreateSubentGeometry(const mcsWorkID& idParentSolid, const mcsWorkID& idFEV) {
		return E_NOTIMPL;
	}

		// получает список объектов, которые участвовали в образовании указанного элемента FEV
	virtual HRESULT getFEVDependsOn(const mcsWorkID& idFEV, OUT mcsWorkIDSetEx& idsObjects) {
		idsObjects.RemoveAll();
		return E_NOTIMPL;
	}

		// выбирает эскиз и затем элементы профиля
	virtual IMcSketchProfilePtr selectProfile(Mc3dModelingTypeEnum applicable3dMode) {
		return UNKNULL;
	}

		// для редактирования размерных объектов, назначенных на размерные зависимости.
		// (зовётся диалог для редактирования значения)
		// dimID -- ID размерного объекта
	virtual HRESULT editDimensionalConstraint(const mcsWorkID& dimID) {
		return E_NOTIMPL;
	}

		// показать/скрыть геом. зависимости по фильтру типа
	virtual HRESULT showHideGeomConstraints(bool fShow, DWORD dwCtrFilter) {
		return E_NOTIMPL;
	}

		// показать/скрыть геом. указанную по ID зависимость
	virtual HRESULT showHideGeomConstraint(IN const mcsWorkID& idCtr, bool fShow) {
		return E_NOTIMPL;
	}

		// idsResultOrder - выдаёт мап упорядоченных ID для обновления в прямом порядке;
		// Если fDoNotAddNew = false, может добавлять новые 3D элементы в список, 
		// т.к. они всё равно будут обновляться по зависимостям, даже если их нет изначально
		// в списке;
		// Допустимо передавать один и тот же объект в idsInitialOrder и в idsResultOrder
	virtual void reorderObjectsDueToTheirDepends(
		IN  const mcsWorkIDSetEx& idsInitialOrder,
		OUT mcsWorkIDSetEx&       idsResultOrder,
		IN DWORD                  dwOptions, // флаги из IMcObjectsManager::ReorderOptions
		OUT OPTIONAL bool*        pbHasCyclicDepends = NULL)
	{
		if(pbHasCyclicDepends)
			*pbHasCyclicDepends = false;
		idsResultOrder = idsInitialOrder;
	}

	virtual void reorderObjectsDueToTheirDepends(
		IN  const mcsWorkIDArray& idsInitialOrder,
		OUT mcsWorkIDArray&       idsResultOrder,
		IN DWORD                  dwOptions, // флаги из IMcObjectsManager::ReorderOptions
		OUT OPTIONAL bool*        pbHasCyclicDepends = NULL)
	{
		if(pbHasCyclicDepends)
			*pbHasCyclicDepends = false;
		idsResultOrder = idsInitialOrder;
	}

		// Выполняет updateAllPatrial для указанных объектов и всех, от которых
		// они зависят согласно 3D-иерархии
	virtual HRESULT update3dObjsGrpWithAllDependsOn(const mcsWorkIDArray& ids) {
		return E_NOTIMPL;
	}

	virtual HRESULT update3dObjWithAllDependsOn(const mcsWorkID& id) {
		mcsWorkIDArray ids;
		ids.Add(id);
		return update3dObjsGrpWithAllDependsOn(ids);
	}

	virtual IMc3dDocHistoryPtr getDocHistory(const mcsWorkID& idSubDoc, const mcsWId2WIdMap* pOldToNewIds = NULL, bool bGetOnlyExisting = false) {
		return UNKNULL;
	}

		// Выдаёт ID объекта-фичи, который создал указанный элемент топологии солида.
		// Выдаётся ID не родительского солида, а ID врезного объекта, который
		// непосредственно отвечает за существование указанного FEV
	virtual mcsWorkID getFeatureObjId4FEV(IN const mcsWorkID& idFEV)
	{
		LOGERR(E_NOTIMPL);
		return WID_NULL;
	}

		// Сервисный метод. Заменяет идентификаторы поверхностей на актуальные
		// в их текущем состоянии в модели (с учетом всех изменений). Такая подмена
		// ускоряет поиск граней в модели. Выбрасывает из списка недоступные объекты.
		// Если fDropDeadOnly = true, то только выбрасывает недоступные.
	virtual bool actualizeFEVsInList(IN OUT mcsWorkIDArray& idsFaces, bool fDropDeadOnly = false)
		{ return false; }

		// Callback, который зовётся в момент преселекции объекты мышью вне команды.
		// (!) В обработчике не делать ничего "тяжелого". Т.к. событие возникает
		// интерактивно и постоянно.
	virtual void onPreselectObject(const mcsWorkID& idObj)
		{}

		// Выдаёт все объекты-фичи, от которых зависит текущее состояние данного FEV-элемента.
		// Первой в списке идёт фича, которая создала элемент (её возвращает метод getFeatureObjId4FEV),
		// затем в списке идут фичи, которые модифицировали элемент (напр: меняли или резали)
	virtual HRESULT getAllFeaturesObjIds4FEV(IN const mcsWorkID& idFEV, OUT mcsWorkIDArray& idsFtrs)
	{
		idsFtrs.RemoveAll();
		RETERR(E_NOTIMPL);
	}

		// методы ниже позволяют управлять кэшированием запросов в 3d объектам,
		// в сложных операциях обновления это может существенно ускорить процесс
	virtual HRESULT start3dQueriesCaching() {
		return E_NOTIMPL; //RETERR(E_NOTIMPL);
	}

	virtual HRESULT stop3dQueriesCaching() {
		return E_NOTIMPL; //RETERR(E_NOTIMPL);
	}

		// Связывает указанный объект с 3д-реализацией указанного типа
		// через bind-переключатель указанного типа
	virtual HRESULT bindEntityWith3dImpl(
		IMcEntity* pUserEnt,
		REFIID     desired3dImplClass,
		REFIID     desiredSwitcherClass)
	{
		RETERR(E_NOTIMPL);
	}

	virtual HRESULT updateActiveConstraintsIcons()
	{
		return E_NOTIMPL;
	}

		// При некоторых операциях клонирования объектов извещает о том, что указанный набор
		// был склонирован дополнительно к выбранному пользователем
	virtual void OnAppendedToClone(const mcsWorkIDSetEx& clonnedIDs)
	{
	}

		// проверка, включен ли функционал 3D в блоках
	virtual bool is3dInBlocksEnabled()
	{
		return false;
	}

		// Имя модуля-переходника к низкоуровневому 3D-моделеру
	virtual McsString get3dSysModelerGateModuleName()
	{
		return _T("");
	}

	virtual IMcs3dConstraintsManager* Get3dConstraintsManager()
	{
		return NULL;
	}

		// точность выполнение 3D-операций
	virtual const mcsTol& tol()
	{
		return mcsGeContext::gTol;
	}

	// Для первичного выбора образмеренного положения врезного объекта передайте NULL в pResultPos. 
	// Если pResultPos != NULL - это режим редактирования.
	// pBlockedIppTypes - Если указан, то пользователю блокируется возможность выбирать типы размещения из этого массива.
	//
	virtual HRESULT editInPartPosition(
		IN bool              bForBoltFastening,
		IN OUT m3dIPPDefPtr& pResultPos,
		IN OPTIONAL const m3dPartPosDefTypeEnumArr* pBlockedIppTypes = NULL)
	{
		pResultPos = UNKNULL; return E_NOTIMPL;
	}

	// Вызывает диалог со списками используемых и зависимых объектов от pObjEraseIds, которые можно сохранить.
	// Если pObjEraseIds не указан, будут использованы объекты селекции.
	// pObjSaveIds - объекты которые должны быть сохранены.
	// Если никакие из объектов не могут быть сохранены, то диалог вызываться не будет.
	virtual HRESULT showRemoveDialog(
		IN mcsWorkIDArray* pObjEraseIds = NULL,
		OUT OPTIONAL mcsWorkIDArray* pObjSaveIds = NULL)
	{
		return E_NOTIMPL;
	}

		// Сообщает, что были зачитаны некорректные данные конверсии геометрии
		// см. комментарий к методу IMc3dFEVGeomCacheCtl::fixGeomCorrData_oct2019 в "3DCoreInternal.h"
	virtual HRESULT _onLoadWrongGeomCacheCorrDataFrom_oct2019(const mcsWorkID& idHostSolid)
	{
		return E_NOTIMPL;
	}

	enum CvtStageEnum
	{
		kMcCvtStage_None = 0,
		kMcCvtStage_Init,
		kMcCvtStage_Common,
		kMcCvtStage_2dCtrsAcadToNcadMigration,
		kMcCvtStage_2dCtrsToNoDbAssocMigration,
		kMcCvtStage_ErrorsFixation,
		kMcCvtStage_FEVLinksConversion,
		kMcCvtStage_ActualizeFevIds,
		kMcCvtStage_Cleanup,
		kMcCvtStage_cvt3dCtrsV1To2,
		kMcCvtStage_fix3dCtrs,
		kMcCvtStage_fix3dObjectsOrder,
	};

		// Сообщает, находимся ли мы в режиме 3D конверсии.
		// Этот режим включается, например, при открытии чертежа, записанного с ядром C3D,
		// в приложении с ядром ACIS и наоборот.
	virtual CvtStageEnum isIn3dConversion()
	{
		return kMcCvtStage_None;
	}

	// Описание:
	//   Показывает объект типа IMc3dHistoryItem с указанным идентификатором в дереве истории 3D построений.
	// Парамаетры:
	//   idObj - идентификатор объекта типа IMc3dHistoryItem, который нужно показать в дереве истории 3D построений.
	virtual void trackItemInHistoryTree(const mcsWorkID& idObj)
	{
	}

	// Получить интерфейс панели управления вставкой стандартных объектов.
	// Последовательные вызовы будут возвращать указатель на один и тот же хранимый
	// внутри объект (т.к. панель одна на систему).
	virtual IEMStdPanelPtr getEMStdPanel()
		{ return NULL; }

	// Сохраняет объекты из ids и все необходимые объекты для них в платформенно независимый поток.
	// Данные можно сохранить хоть во внешнем файле. Далее из них объекты можно восстановить с помощью метода
	// deserializeFromStream.
	//
	virtual HRESULT s3dh_serializeWithAllDependsOn(const mcsWorkIDArray& ids, OUT IMcsStreamPtr& pStream)
	{
		pStream = UNKNULL;
		return E_NOTIMPL;
	}

	// Метод восстанавливает из потока набор объектов, сохранённых ранее с помощью метода
	// serializeWithAllDependsToStream.
	// Возвращаемые объекты не находятся в глобальном контейнере и в документе.
	// Добавлять их, куда требуется, нужно вручную.
	// 
	// pAddonUserVarsData: данные пользовательских переменных, которые понадобятся для работы созданных объектов,
	// Этот подстрим хранится в данных передаваемого потока.
	// При добавлении в документ этот поток нужно передать вместе с новыми объектами.
	// 
	// csData на выходе определяет объекты, которые задают СК прочитанной модели.
	// 
	virtual HRESULT s3dh_deserialize3dEntitiess(
		IN IMcsStream*     pStream,
		OUT mcEntityArray& newEntities,
		OUT IMcsStreamPtr& pAddonUserVarsData,
		OUT m3dh_cs&       csData) // данные координатной системы
	{
		newEntities.RemoveAll();
		pAddonUserVarsData = UNKNULL;
		csData.reset();
		return E_NOTIMPL;
	}

	// Метод добавляет набор новых объектов с необходимыми для них пользовательскими переменными
	// в указанный документ или объект.
	// Если в качестве (pTarget) цели указан объект, то все элементы модели будут добавлены в объект как дочерние.
	// При этом целевой объект должен сам находиться в документе.
	//
	virtual HRESULT s3dh_addDeserialized3dEntitiesToTarget(
		IN mcEntityArray&      newEntities, // новые объекты из метода deserializeFromStream, должны быть вне документа
		IN IMcsStream*         pAddonUserVarsData, // данные соотв. out-аргумента из метода deserializeFromStream
		IN OPTIONAL LPCTSTR    lpszObjNamesSuffix = NULL, // если не NULL, указанная строка будет добавлена к именам всех объектов модели, в т.ч. и к переменным
		IN OPTIONAL IMcObject* pTarget = NULL) // документ/объект, куда добавлять объекты, NULL = активный поддокумент
	{
		return E_NOTIMPL;
	}

	// Подсветка 2D зависимостей по объекту/точке
	virtual bool higiligh2dConstraint(IN const mcsWorkID& objId, IN const mcsPoint& pt)
	{
		return false;
	}

		// Сообщает, что были зачитаны некорректные данные конверсии геометрии
		// см. комментарий к методу IMc3dFEVGeomCacheCtl::fixGeomCorrData_202203 в "3DCoreInternal.h"
	virtual HRESULT _onLoadWrongGeomCacheCorrDataFrom_202203(const mcsWorkID& idHostSolid)
	{
		return E_NOTIMPL;
	}

	virtual bool is3dBomEnabled() 
	{
		return false;
	}

	// Выбор объектов и параметров их сдвига
	virtual bool selectTranslationData(OUT mcsWorkIDArray& idsToMove, OUT mcsVector& vOfs)
	{
		return false;
	}

	// Выбор объектов и параметров их поворота
	virtual bool selectRotationData(OUT mcsWorkIDArray& idsToRotate, OUT mcsLine& axis, OUT double& angle_rad)
	{
		return false;
	}

	virtual bool edit3dBomItemPropeties(const mcsWorkID& id)
	{
		return false;
	}

		// Управление режимом схемы сборки.
		// Включенный режим схемы сборки отключает вычисление 3D зависимостей, и позволяет перемещать 3D тела/вставки блоков как угодно.
	virtual void setIsAssemblySchemeMode(bool bModeIsOn)
	{
	}

	virtual	bool isAssemblySchemeMode()
	{
		return false;
	}

		// Для системный целей
	virtual void _flushDocHistoryData()
	{
	}

	// Определяет вставку блока для редактирования по месту.
	MCTYP_API virtual mcsComplexWorkID& InplaceEditData();

	virtual HRESULT createFormatAndLinkToPropSource(IMcPropertySource* pPropSourceToLink)
	{
		return E_NOTIMPL;
	}

	// находит в указанном документе (или активном) редактируемую деталь
	virtual IMc3dPartPtr getActiveEditPart(IN OPTIONAL IMcDocument* pDoc = NULL) {
		return UNKNULL;
	}

	virtual mcsWorkID getActiveEditPartID(IN OPTIONAL IMcDocument* pDoc = NULL) {
		return WID_NULL;
	}

	// находит в указанном документе (или активном) редактируемую деталь и завершает её редактирование
	virtual HRESULT exitPartEditMode(IN OPTIONAL IMcDocument* pDoc = NULL) {
		return E_NOTIMPL;
	}

	// Метод определяет, включен ли функционал оптимизированных 3D-деталей.
	virtual bool is3dPartOn() {
		return false;
	}

	// (!) Для системных нужд.
	virtual HRESULT set3dConversionMode(CvtStageEnum) {
		return E_NOTIMPL;
	}

		// Выдаёт все объекты-фичи, от которых зависит текущее состояние данного FEV-элемента.
		// Отдельно возвращаются фичи, создавшие FEV, и модифицировавшие.
	virtual HRESULT getAllFeaturesObjIds4FEV(IN const mcsWorkID& idFEV, OUT mcsWorkIDArray& idsFtrsCreating, OUT mcsWorkIDArray& idsFtrsModifying)
	{
		idsFtrsCreating.RemoveAll();
		idsFtrsModifying.RemoveAll();
		RETERR(E_NOTIMPL);
	}

	virtual bool isModelStudioLoaded(bool bForceRecheck = false) {
		return false;
	}

		// Корректирует время создания на данном наборе объектов, с использованием зависимостей.
		// Для системных целей.
	virtual bool correctCreationTimeUsingDepends(IN mcsWorkIDSet& items_arg)
	{
		return false;
	}
};
//=============================================================================

extern "C"
{
	extern MCTYP_API IMc3dSite* gp3dSite; // Функционал платформенно-независимой части 3D модуля
}
//==============================================================================

struct IMcAssocVariableData;
typedef McsArray<IMcAssocVariableData*, IMcAssocVariableData*> IMcAssocVariableDataPtrsArr;
typedef McsHashset<IMcAssocVariableData*, IMcAssocVariableData*> IMcAssocVariableDataPtrsSet;
typedef McsHashsetEx<IMcAssocVariableData*, IMcAssocVariableData*> IMcAssocVariableDataPtrsSetEX;

// Интерфейс к переменной-параметру.
// Интерфейс используется сугубо для установки/получения данных переменной.
// Все операции с этими данными выполняются через интерфейс IMcsDocVariablesManager.

struct IMcAssocVariableData
{
	enum ToleranceType
	{
		Min,
		Nominal,
		Medium,
		Max,
		Custom,
		Undefined
	};

	// ID переменной
	// Это может быть и GUID, для пользовательских переменных
	virtual mcsWorkID varID() const = 0;

	// ID документа-владельца переменной
	virtual mcsWorkID docID() const = 0;

	// Если для переменной задано выражение, автоматически посчитает его значение.
	// Метод не константный, т.к. при вычислении внутри могут меняться хранимые в файле данные,
	// используемые для оптимизации вычислений.
	virtual double    value()  = 0;

	// Получить выражение, определяющее переменную.
	// Метод не константный, т.к. при запросе выражения выполняется его актуализация.
	virtual McsString expression() = 0;

	virtual McsString name() const = 0;
	virtual McsString description() const = 0;

	virtual bool setExpression(IN LPCTSTR newExpr, OUT OPTIONAL bool* pbTheSame = NULL) = 0;
	virtual bool setName(LPCTSTR newName, OUT OPTIONAL bool* pbTheSame = NULL) = 0;
	virtual bool setDescription(LPCTSTR newDescription, OUT OPTIONAL bool* pbTheSame = NULL) = 0;

	// Верхнее и нижнее предельные отклонения.
	virtual void getTolerance(OUT double& lowTol, OUT double& upTol) const = 0;
	virtual bool setTolerance(IN double lowTol, IN double upTol) = 0;

	virtual McsString getFieldAndQuality() const = 0;
	virtual void setFieldAndQuality(McsString& fieldAndQuality) = 0;

	// Oтклонения.
	virtual double getDeviation() const = 0;
	virtual bool setDeviation(IN double newDev) = 0;

	// Тип предельного отклонения используемый при определении значения переменной.
	virtual ToleranceType getToleranceType() const = 0;
	virtual bool setToleranceType(IN ToleranceType type) = 0;

	virtual DWORD varTypeFlags() const = 0;
	virtual DWORD userVarTypeFlags() const = 0; // неопределено, если 0 == (varTypeFlags() & kMcDocVarType_User)

	// Для будущего использования.
	// Установка значения будет доступна только для ссылочных переменных,
	// чье значение определяется к.л. характеристикой модели
	//
	// Чтобы задать значение не ссылочных переменных, нужно установить требуемое выражение
	// через setExpression.
	//
	//virtual bool setValue(double newVal) = 0;

	// Проверяет указанные имя и/или выражение на валидность.
	virtual bool validateNameAndExpression(
		IN OPTIONAL LPCTSTR lpszName = NULL,
		IN OPTIONAL LPCTSTR lpszExpression = NULL,
		OUT OPTIONAL double* pCalcultedValue = NULL) const = 0;

	virtual DWORD stateCookie() const = 0;

	// Получить список переменных, от которых зависит данная
	virtual bool getVarsDependsOn(OUT IMcAssocVariableDataPtrsArr& varsDataDepOn) const = 0;

	// (!) Для системных целей.
	// Методы назначения/получения связанной DbAssoc-переменной, которая используется
	// в режиме редактирования эскиза.
	virtual void      setDbAssocVar(const mcsWorkID& id) = 0;
	virtual mcsWorkID getDbAssocVar() const = 0;

	// Возвращает время создания переменной
	virtual __int64 getCreationTime() const = 0;

	// Назначает время создания переменной (для системных целей)
	virtual void    setCreationTime(__int64 newTime) = 0;

	// возвращает статус переменной, все ли с ней впорядке или нет. Например для внешних переменных она может потеряться
	virtual bool isValid() const = 0;
};
//==============================================================================

struct CMcExternalVariable;
typedef std::shared_ptr<CMcExternalVariable> CMcExternalVariablePtr;
typedef McsMap<GUID, const GUID&, CMcExternalVariablePtr, CMcExternalVariablePtr> mcsMapGuidToMcExtVarPtr;

struct IMcExtVarsDataProvider
{
	// Возвращает код состояния переменных во внешнем файле.
	// Если код не меняется, значит переменные в файле тоже.
	virtual __int64     stateCookie() const = 0;

	// Путь ко внешнему файлу переменных.
	virtual McsString   path() const = 0;

	virtual __int64     getCreationTime() const = 0;

	virtual mcsWorkID   getIdHostDoc() const = 0;

	// Если результат не NULL, то возвращает позицию итератора переменных для метода getNextVariable().
	virtual MCSPOSITION getVarsIteratorPos() = 0;

	// Метод для перебора переменных внешнего файла.
	virtual bool        getNextVariable(IN OUT MCSPOSITION& iterPos, OUT McsString& strName, OUT McsString& strExpression) = 0;

	virtual McsString   getVarExpression(IN LPCTSTR varName) = 0;

	virtual IMcAssocVariableData* getVarByName(IN LPCTSTR varName) = 0;
	virtual IMcAssocVariableData* getVarByGUID(IN const GUID& id) = 0;

	virtual int getExtVarsIDs(OUT mcsWorkIDArray& idsVars) = 0;

	// отдает / устанавливает кэшированные данные
	virtual void getVarsData(OUT mcsMapGuidToMcExtVarPtr& id2CExtVarDataPtr) = 0;
	virtual void setVarsData(IN const mcsMapGuidToMcExtVarPtr& id2CExtVarDataPtr) = 0;
};

typedef std::shared_ptr<IMcExtVarsDataProvider> IMcExtVarsDataProviderPtr;
//==================================================================================================

// Тип переменной в документе, флаговые значения (!)

enum McsDocVarTypeEnum // 
{
	kMcDocVarType_Unk       = 0,

	kMcDocVarType_User       = 0x01, // непосредственно ничего не определяет, простое значение
	kMcDocVarType_2dCtrDim   = 0x02, // определяет значение для параметрической 2D-зависимости
	kMcDocVarType_3dModel    = 0x04, // определяет геометрию 3D-модели
	kMcDocVarType_Ref        = 0x08, // ссылочная/вычисляемая
	kMcDocVarType_3dCtr      = 0x10, // определяет значение для 3D-зависимости
	kMcDocVarType_External   = 0x20 | kMcDocVarType_User, // внешняя переменная
	kMcDocVarType_CrossBlock = 0x40 | kMcDocVarType_User, // блочная переменная
	kMcDocVarType_XRef       = 0x80 | kMcDocVarType_User, // внешняя ссылка (из другого dwg)

	kMcDocVarType_All       = kMcDocVarType_User | kMcDocVarType_2dCtrDim | kMcDocVarType_3dModel | kMcDocVarType_Ref | kMcDocVarType_3dCtr |
								kMcDocVarType_External | kMcDocVarType_CrossBlock | kMcDocVarType_XRef,
};
//==============================================================================

// Тип пользовательской переменной в документе, флаговые значения (!)

enum McsDocVarExprTypeEnum
{
	kMcDocVarExprType_Simple     = 0, // простое значение/выражение
	kMcDocVarExprType_CrossBlock = 1, // есть ссылка на переменную другого поддокумента
	kMcDocVarExprType_XRef       = 2, // есть ссылка на переменную во внешний топ-документ
	kMcDocVarExprType_External   = 4, // есть ссылка на внешнюю переменную
};
//==============================================================================

// Объект-переменная, задающая к.л. характеристику другого объекта (родителя, в котором она находится).
// Это может быть, например, либо 2D эскиз, либо 3D фича.

struct IMcAssocVariable :
	public virtual IMcEntity,
	public virtual IMcAssocVariableData
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcAssocVariable);

public:
	IMCS_QI_METHOD_DEFINITION(IMcAssocVariable, IMcEntity);
	virtual const GUID& getImplementID() override { return IID_IMcDbObject; }
	virtual const GUID& getClassID() const override { return IID_IMcAssocVariable; }

	// Если переменная связана с 2D зависимостью, возвращает её идентификатор.
	virtual GUID get2dConstraintId() const = 0;

	// (!) Для системных целей.
	// Связывает переменную с 2D зависимостью
	virtual void set2dConstraintId(const GUID&) = 0;

	// Если переменная хранится в элементе построения 3D солида,
	// то методы отдают о нём информацию
	virtual IMc3dSolidPtr getHostSolid(bool bAllowRetDumbSolid = false) const = 0;
	M3D_API virtual const mcsWorkID& getHostSolidID(bool bAllowRetDumbSolid = false) const;
};
//==============================================================================
// (!) Не менять присвоенные цифры, пишутся в файл

enum Mc3dHistoryItemStatus
{
	kMc3dHistStatus_Unknown     = 0,
	kMc3dHistStatus_Ok          = 1,
	kMc3dHistStatus_Error       = 2,
	kMc3dHistStatus_NeedUpdate  = 3,
	kMc3dHistStatus_Suppressed  = 4,
	kMc3dHistStatus_Erased      = 5,
	kMc3dHistStatus_Warn        = 6,
};
//==============================================================================

// Тип действия, которое пользователь может использовать для фиксации ошибок в дереве истории построения
enum Mc3dHealingActionEnum // Flags
{
	kMc3dHealingAction_Nothing   = 0,
	kMc3dHealingAction_Delete    = 1, // Удалить
	kMc3dHealingAction_Edit      = 2, // Редактировать
	kMc3dHealingAction_Redefine  = 4, // переопределить. Напр., для эскизов - плоскость, для WPT/WA/WPL - способ задания

	kMc3dHealingAction_EditDel = kMc3dHealingAction_Delete | kMc3dHealingAction_Edit,
};
//==============================================================================

// Структура с информацией о доступных действиях, которые можно использовать для устранения возникшей проблемы.

struct Mc3dHealingActionInfo
{
protected:
	// объект, к которому нужно применять действия, если null, то по контексту текущий объект
	mcsWorkID m_idTargetObj;

	// маска с флагами возможных действий
	DWORD     m_dwActionsMask;

public:
	MCTYP_API Mc3dHealingActionInfo();
	MCTYP_API Mc3dHealingActionInfo(const Mc3dHealingActionInfo& cf);
	MCTYP_API Mc3dHealingActionInfo(DWORD dwActionsMask, const mcsWorkID& idObjForActions = WID_NULL);

	DWORD     actions() const { return m_dwActionsMask; }
	mcsWorkID targetObjectId() const { return m_idTargetObj; }

	friend struct Mc3dHistItemErroInfo;
};

typedef McsArray<Mc3dHealingActionInfo> Mc3dHealingActionInfoArr;
//==============================================================================

// Уровень серьёзности ошибки в элементе дерева истории построения
enum Mc3dErrorSeverityEnum
{
	// значения для накопления информации
	kMc3dErrSeverity_Ok        = 0, // добавить простое статусное сообщение
	kMc3dErrSeverity_Warning   = 1, // добавить предупреждение
	kMc3dErrSeverity_Error     = 2, // добавить ошибку
};
//==============================================================================

// флаги для IMc3dHistoryItem::m_dwObjModelChangeData
#define M3D_OBJMODCHANGE_GEOM  1
#define M3D_OBJMODCHANGE_POS   2
#define M3D_OBJMODCHANGE_VALIDMASK  (M3D_OBJMODCHANGE_GEOM | M3D_OBJMODCHANGE_POS)

//==============================================================================

// Структура описывает одну отдельную запись информации о состоянии объекта дерева истории 3D-построения

struct Mc3dHistItemInfoRecord
{
protected:
	Mc3dErrorSeverityEnum    m_severity;
	McsString                m_strInfo;
	Mc3dHealingActionInfoArr m_healingActionsArr;

public:
	MCTYP_API Mc3dHistItemInfoRecord();
	MCTYP_API Mc3dHistItemInfoRecord(Mc3dErrorSeverityEnum severity);
	MCTYP_API Mc3dHistItemInfoRecord(Mc3dErrorSeverityEnum severity, LPCTSTR lpszDescription);
	MCTYP_API Mc3dHistItemInfoRecord(Mc3dErrorSeverityEnum severity, LPCTSTR lpszDescription, DWORD dwHealingActionsMask);
	MCTYP_API Mc3dHistItemInfoRecord(Mc3dErrorSeverityEnum severity, LPCTSTR lpszDescription, const Mc3dHealingActionInfoArr& healingActions);

	MCTYP_API bool operator == (const Mc3dHistItemInfoRecord& cw) const;
	MCTYP_API Mc3dHistItemInfoRecord& operator = (const Mc3dHistItemInfoRecord& cf);

	MCTYP_API Mc3dErrorSeverityEnum           severity() const;
	MCTYP_API McsString                       description() const;
	MCTYP_API const Mc3dHealingActionInfoArr& healingActions() const;

	MCTYP_API void setSeverity(Mc3dErrorSeverityEnum sev);
	MCTYP_API void setDescription(LPCTSTR lpszDescription);
	MCTYP_API void setHealingActions(DWORD dwActionsMask);
	MCTYP_API void setHealingActions(const Mc3dHealingActionInfoArr& actions);

	friend struct Mc3dHistItemErroInfo;
};

typedef McsArray<Mc3dHistItemInfoRecord> Mc3dHistItemInfoRecordArr;
//==============================================================================

// Структура описывает информацию об ошибке в объекте дерева истории 3D-построения

struct Mc3dHistItemErroInfo
{
protected:
	Mc3dHistItemInfoRecordArr m_records;

public:
	MCTYP_API Mc3dHistItemErroInfo();

	MCTYP_API bool clear();

		// очищает только ошибки указанного уровня серьёзности
	MCTYP_API bool clear(Mc3dErrorSeverityEnum thisSeverityOnly);

	bool isOk() const      { return getSeverity() == kMc3dErrSeverity_Ok; }
	bool isError() const   { return getSeverity() == kMc3dErrSeverity_Error; }
	bool isWarning() const { return getSeverity() == kMc3dErrSeverity_Warning; }

	MCTYP_API int                   numRecords() const;
	MCTYP_API McsString             getDescriptionAt(int idxErr) const;
	MCTYP_API Mc3dErrorSeverityEnum getSeverityAt(int idxErr) const;
	MCTYP_API const Mc3dHealingActionInfoArr& getHealingActionsAt(int idxErr) const;
	MCTYP_API const Mc3dHistItemInfoRecord& getRecordAt(int idx) const;

	MCTYP_API Mc3dErrorSeverityEnum getSeverity() const;

		// Добавляет информацию об ошибке.
		// Возвращает true, если была добавлена.
		// Возвращает false, если такая информация уже есть.
		// dwHealingActions - действия, которые доступны для исправления ошибки
		// При добавлении действия аккумулируются.
		// Возвращает индекс добавленной/обновленной записи. Отрицательный индекс в случае ошибки.
	MCTYP_API int addInfo(
		Mc3dErrorSeverityEnum severity,
		IN OPTIONAL LPCTSTR   lpszDetails = NULL,
		IN OPTIONAL DWORD     dwHealingActions = kMc3dHealingAction_Nothing);

		// Этот метод позволяет добавить ошибку, описание и набор действий по "лечению".
		// Возможно указание ссылок на действия с другими объектами.
		// Если ID target объекта не указан (WID_NULL), подразумевается текущий объект по контексту.
		// Возвращает индекс добавленной/обновленной записи. Отрицательный индекс в случае ошибки.
	MCTYP_API int  addInfo(
		Mc3dErrorSeverityEnum severity,
		IN LPCTSTR            lpszDetails,
		IN const Mc3dHealingActionInfoArr& healingActions);

		// Обобщенный метод добавления информации о состоянии объекта.
		// Возвращает индекс добавленной/обновленной записи. Отрицательный индекс в случае ошибки.
	MCTYP_API int  addInfo(const Mc3dHistItemInfoRecord& infoRecord);

		// ctxObjID - ID объекта, к которому относится эта структура данных
		// (!) WID_NULL не передавать! Нужно не пустое значение для предотврaщения
		// ошибки чтения документов с errInfo из сборок 34xx+ в сборках 33xx-.
		// (из-за косяка в коде метода seek в стриме, искать по тэгу 04.06.2020).
	MCTYP_API HRESULT save(IMcsStream* pS, const mcsWorkID& ctxObjID) const;
	MCTYP_API HRESULT load(IMcsStream* pS);
};

//==============================================================================
// Интерфейс используется для следующего сценария.
// Если есть некий класс объектов A, который к 3D изначально не имеет никакого отношения.
// Допустим, мы хотим сделать так, чтобы у объектов класса A появилось 3D-представление (тело).
// Чтобы не переписывать код класса А, используются расширения.
// Создаётся спец класс, Switcher, его надо пронаследовать от McEntBaseBindSwitcher.
// В Switcher нужно объявить те методы IMcEntity, которые могут иметь переопределенное поведение
// в объектах класса А после того, как у них появится 3D исполнение.
// В момент создания расширенного объекта класса А будет создан класс переключатель и класс-расширение,
// в нашем случае это 3D-солид (для 3D представления).
// В момент вызова методов IMcEntity со стороны, управление будет приходить в класс-переключатель.
// Он будет использовать либо базовую реализацию класса А, либо реализацию из расширения, либо обе.
// Как вы сами то пропишете, так переключатель и будет работать. По умолчанию он использует реализацию расширения.
// Так вот..
// Чтобы дать коду класса А возможность появиться в дереве истории построения, нужно объявить явно
// реализацию минимума методов, необходимых для дерева. Для этого нужно класс А пронаследовать от IMc3dHistoryItemExt.
// Прописать там свою реализацию.
// Базовая реализация элемента дерева истории построения опрашивает объект
// на предмет наличия в нём интерфейса IMc3dHistoryItemExt, и если такой есть, зовёт именно эту реализацию
// в первую очередь. Если же вернуть E_NOTIMPL, будет работать реализация кода по умолчанию.

struct IMc3dHistoryItemExt :  public virtual IMcObject
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dHistoryItemExt);

public:
	IMCS_QI_METHOD_DEFINITION(IMc3dHistoryItemExt, IMcObject);

	// описание к методам см. в IMc3dHistoryItem,
	// Если вернуть E_NOTIMPL, то отработает реализация по умолчанию,
	// если вернуть что-то отличное от E_NOTIMPL и bCallDefImpl выставить в false,
	// то реализация по умолчанию выполняться не будет;
	// bCallDefImpl по умолчанию всегда выставлен в true

	virtual HRESULT tree3d_getPartName(OUT McsString& name, IN OUT bool& bCallDefImpl) const { return E_NOTIMPL; }
	virtual HRESULT tree3d_setPartName(LPCTSTR lpszName, IN OUT bool& bCallDefImpl) { return E_NOTIMPL; }
	virtual HRESULT tree3d_getName(OUT McsString& name, IN OUT bool& bCallDefImpl) const { return E_NOTIMPL; }
	virtual HRESULT tree3d_setName(LPCTSTR lpszName, IN OUT bool& bCallDefImpl) { return E_NOTIMPL; }
	virtual HRESULT getStatus(OUT Mc3dHistoryItemStatus& status) const { return E_NOTIMPL; }
	virtual HRESULT suppress(IN OUT bool& bCallDefImpl) { return E_NOTIMPL; }
	virtual HRESULT unsuppress(IN OUT bool& bCallDefImpl) { return E_NOTIMPL; }
	virtual HRESULT setPartFixedFlag(bool newFixed, IN OUT bool& bCallDefImpl) { return E_NOTIMPL; }
};

//==============================================================================
// элемент дерева истории 3D построения;
// если объект наследует этот интерфейс, то автоматически появляется в дереве построения
// (!) наследовать виртуально (нужно для наследования частичной реализации)
struct IMc3dHistoryItem :  public virtual IMcEntity
{
protected:

	IMc3dHistoryItem() {
		IMCS_REGISTER_THIS_IID_4KINDOF;
		m__lSystemFlag |= kMc3dHistoryItem;
	}

public:

	//IMCS_ENT_METHOD_DEFINITION(IMc3dHistoryItem, IMcEntity, IMcDbEntity);
	virtual const GUID& getImplementID() {return __uuidof(IMcDbEntity);}
	virtual const GUID& getClassID() const {return __uuidof(*this);}
	M3D_API virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj);
	//M3D_API virtual bool isKindOf(REFIID riid) const;
	virtual McsString getClassName() const = 0;

		// Возвращает/Устанавливает имя детали, к которой относится элемент
	virtual McsString tree3d_getPartName() const = 0;
	virtual HRESULT   tree3d_setPartName(LPCTSTR lpszName) = 0;

	virtual McsString tree3d_getName() const = 0;
	virtual HRESULT   tree3d_setName(LPCTSTR lpszName) = 0;

		// показывать/нет объект в дереве построения
	virtual bool tree3d_getShowInTree() const {
		return is3d();
	}

	virtual __int64 getCreationTime() const = 0;
	virtual void    setCreationTime(__int64 newTime) = 0;

	virtual Mc3dHistoryItemStatus getStatus(OUT OPTIONAL Mc3dHistItemErroInfo* pInfo = NULL) const = 0;

	virtual HRESULT   suppress(bool bSuppressDependent = true) = 0;
	virtual HRESULT   unsuppress(bool bUnsuppressDependent = true) = 0;

	virtual bool isOk() const
	{
		Mc3dHistoryItemStatus st = getStatus();
		if(st == kMc3dHistStatus_Error
			 || st == kMc3dHistStatus_Unknown
			 || st == kMc3dHistStatus_Erased)
			return false;
		return true;
	}

	virtual bool isSuppressed() const {
		Mc3dHistoryItemStatus st = getStatus();
		return st == kMc3dHistStatus_Suppressed;
	}

		// принудительно устанавливает для объекта статус ошибочности,
		// опционально с детализацией/описанием проблемы и возможными действиями по устранению ошибки
	virtual HRESULT accErrorStatus(
		Mc3dErrorSeverityEnum severity,
		LPCTSTR               lpszDetails = NULL,
		DWORD                 dwHealingActions = kMc3dHealingAction_Nothing) = 0;

		// выдаёт список (неповторяющихся) ID объектов, от которых зависит состояние данного;
		// если fAutoReplaceSubentIdByParentId == true, то все SubEntID заменяет наID родительского объекта;
		// если bRigidGeomDependsOnly = true, то объект не должен добавлять в набор объекты, которые не являются монолитной частью данного объекта,
		// то есть геометрию они определять могут, но при перемещении не должны двигаться вместе с this-объектом.
	virtual HRESULT getDependsOn(OUT mcsWorkIDArray& idsDependsOn, IN OPTIONAL bool fAutoReplaceSubentIdByParentId = true, bool bRigidGeomDependsOnly = false) const override = 0;
	//M3D_API virtual HRESULT getDependsOn(OUT mcsWorkIDSetEx& idsDependsOn, IN OPTIONAL bool fAutoReplaceSubentIdByParentId = true, bool bRigidGeomDependsOnly = false) const override sealed; // работает медленнее, по возможности не звать

		// выдаёт полный список всех объектов, от которых зависит,
		// состояние данного с учетом рекурсии;
		// Если bGetOrdered == true, элементы будут упорядочены в порядке их зависимости: от базовых к производным,
		// (!) установка bGetOrdered в значение true существенно замедляет работу методов
	//M3D_API virtual HRESULT getAllDependsOn(OUT mcsWorkIDArray& idsDependsOn, bool bGetOrdered) const;
	//M3D_API virtual HRESULT getAllDependsOn(OUT mcsWorkIDSetEx& idsDependsOn, bool bGetOrdered) const sealed; // работает медленнее, по возможности не звать
	//M3D_API virtual bool    doesDependOn(IN const mcsWorkID& idObject) const;

		// Выдаёт объекты, непосредственно зависящие от данного.
		// Реализация по умолчанию выдаёт список 3dHistItem-объектов среди реакторов.
	M3D_API virtual HRESULT getDependent(OUT mcsWorkIDSetEx& idsDependent) const override;
	//M3D_API virtual HRESULT getDependent(OUT mcsWorkIDArray& idsDependent) const override sealed; // работает медленнее, по возможности не звать

		// Выдаёт список всех объектов в документе, зависящих прямо или косвенно от этого.
		// Если bGetOrdered == true, элементы будут упорядочены таким образом, что последующие будут зависеть от предыдущих.
		// (!) установка bGetOrdered в значение true существенно замедляет работу методов
		// Реализация по умолчанию использует список реакторов для построения дерева зависимостей.
	//M3D_API virtual HRESULT getAllDependent(OUT mcsWorkIDArray& idsAllDependent, bool bGetOrdered) const;
	//M3D_API virtual HRESULT getAllDependent(OUT mcsWorkIDSetEx& idsAllDependent, bool bGetOrdered) const sealed; // работает медленнее, по возможности не звать

		// Пара методов ниже выполняет почти те же функции, что и getDependsOn и getAllDependsOn, но
		// в возвращаемый список объектов помещается то, без чего объект не сможет существовать.
		// И при удалении одного из перечисленных объектов удалится и этот.
		// Переопределение полезно в случае, когда объект включает в свой состав геометрию другого объекта,
		// и удаление включенного влечет не удаление этого, лишь его перестроение. Примеры таких объектов:
		// эскиз, массивы
	//M3D_API virtual HRESULT getCriticalDependsOn(OUT mcsWorkIDArray& idsDependsOn) const;
	//M3D_API virtual HRESULT getCriticalAllDependsOn(OUT mcsWorkIDArray& idsDependsOnOrdered) const;

		// Выдаёт солид, к которому относится этот элемент.
		// Например, рабочая плоскость, построенная на плоской грани солида и эскиз
		// на этой плоскости будут иметь хозяином этот самый солид.
		// HostSolid - это фактически объект, являющийся деталью.
		// Если 3D-фича является родительским солидом, то она сама для себя есть HostSolid.
		// Если результат NULL, то элемент не относится ни к какой детали.
		// bAllowRetDumbSolid - для системного использования
	virtual IMc3dSolidPtr   getHostSolid(bool bAllowRetDumbSolid = false) const = 0;
	M3D_API virtual const mcsWorkID& getHostSolidID(bool bAllowRetDumbSolid = false) const;

	M3D_API virtual IMc3dDocHistoryPtr  getDocHistory() const;

		// Отвечает, можно ли данный объект двигать непосредственно;
		// Если указан флаг fCheckForDependentTfmMode, то проверяет, может ли быть
		// успешно выполнен метод transformDependent
	virtual bool  canAcceptTfm(bool fCheckForDependentTfmMode = false) const = 0;

		// выдаёт комбинацию флагов M3D_OBJMODCHANGE_xxx, которая сообщает причину посылки 
		// реакции kMcObjModelChanged от этого объекта
	virtual DWORD getObjModChangeCause() const = 0;

		// Проверяет, является ли допустимым указанное значение для данной связанной переменной.
		// Имеет смысл для параметрических объектов, типа выдавливания и т.п.
	virtual bool isValidVarVal4Obj(IN const mcsWorkID& idVar, double rVal) const
		{return true;}

		// Выполняет перемещение объекта. Если объект является зависимым, то выполняет проверку
		// все ли объекты, от которых зависит данный, могут быть перемещены. Если могут,
		// то для них выполняется перемещение и как следствие будет перемещён и данный объект.
		// Если объект ни от чего не зависит, то вызов эквивалентен методу transformBy
	virtual HRESULT transformDependent(const mcsMatrix& relTfm) = 0;

		// сообщает, фиксировано ли положение детали, к которой относится данный элемент
	M3D_API virtual bool isPartFixed() const;

		// Фиксирует или снимает фиксацию с детали, к которой относится данный элемент.
		// Если деталь не может быть перемещаемой, то снять с неё фиксацию не получится
	virtual HRESULT setPartFixedFlag(bool fFixed) = 0;

		// сообщает, фиксировано ли положение этого объекта без учета его вхождения в состав
		// к.л. детали
	M3D_API virtual bool isFixed() const = 0;

		// Фиксирует или снимает фиксацию именно с этого объекта без учета его
		// вхождения в состав к.л. детали
	virtual HRESULT setFixedFlag(bool fFixed) = 0;

		// Возвращает true, если объект может быть дефиксирован, независимо от статуса
		// фиксации в данный момент
	virtual bool canBeUnfixed() const = 0;

		// Если объект подавлен, то проверяет, возможно ли его безопасно восстановить.
		// К примеру, если при восстановлении останутся подавленными объекты, от которых
		// зависит построение данного, то тогда ответ будет false
	M3D_API virtual bool canBeSafelyUnsuppressed() const;

		// Позволяет установить/получить для объекта факт того, что он относится к сборке.
		// В этом случае объект может использоваться в деталях, но при этом не будет входить
		// в их состав.
		// Переключать режим сборочный или нет для объекта можно только в случае, если от
		// объекта ничего не зависит и все объекты, от которых зависит данный - не входят
		// ни в одно тело.
	virtual HRESULT   setIsObjectForcedToAsmCtx(bool fAsmObj) = 0;

		// Возвращает true тогда и только тогда, когда объект явно существует только
		// в контексте сборки. Даже если он временно не имеет тела-хозяина, это не повод
		// ему ответить true. Иначе говоря, вернёт true, если был успешно выполнен вызов
		// setIsObjectForcedToAsmCtx(true)
		// (!) Это не метод для определения - находится объект в сборке или нет.
		// Для нужно проверить флаг IMcEntity::m__lSystemFlag & kMc3dAsmLvl
	virtual bool      getIsObjectForcedToAsmCtx() const = 0;

		// Метод возвращает некий подобъект по его имени в дереве построения внутри этого объекта.
		// То есть указываем то имя, которое возвращает метод tree3d_getName.
		// Пример. Тело. По имени через HostSolid можно получить любой элемент 3д-построения,
		// который структурно входит в тело.
		// Если элементов с одинаковым именем в объекте несколько, то вернётся первый попавшийся, а весь
		// список одноимённых можно будет получить через опциональный аргумент pIdsSameNamedItems
		// Также просматриваются 3D-зависимости, которые присоединены к телу.
	M3D_API virtual IMcEntityPtr getSubItemByName(LPCTSTR szName, OUT OPTIONAL mcsWorkIDArray* pIdsSameNamedItems = NULL);

		// возвращает признак того, что интерфейс ссылается на листовое тело
	M3D_API virtual bool isSheetMetal() const;

		// метод возвращает применимый к объекту метод 3D моделирования
	M3D_API virtual Mc3dModelingTypeEnum getApplicable3dModelingType() const;

		// NO DOC.
		// Для системных целей.
	virtual HRESULT _onReplaceObjDependsOn(const mcsWorkID& idFrom, const mcsWorkID& idTo) = 0;

		// Метод устанавливает конец истории построения для детали, к которой относится данный объект.
		// Все объекты, идущие в теле по порядку после данного, будут подавлены.
		// Возвращает true, если конец построений успешно изменен.
		// Если bTryOnly = true, то только проверяет возможность установки нового конца построений.
	virtual bool setAsLastPartItem(bool bTryOnly) = 0;

		// Возвращает true, если объект находится за маркером конца построения внутри тела,
		// к которому относится данный объект.
	virtual bool isBeyondEndOfPart() const = 0;

		// Задать порядок следования объектов в списке объектов из состава тела:
		//   установить idObjBefore перед this.
		//
		// Метод возвращает true, если:
		// 1) Этот объект входит в состав 3D тела.
		// 2) Объект idObjBefore входит в состав того же тела.
		// 3) Объект idObjBefore и все зависимые от него не зависит от this-объекта.
		// 4) Данный объект и объект idObjBefore находятся перед маркером End-Of-Part.
		// 
		// Если bTryOnly = true, метод лишь проверяет возможность задания желаемого порядка следования.
		// Внимание. Если объект A был данным методом поставлен перед объектом B,
		// и если объект B при этом никак не зависит от объекта A, то данный метод
		// должен позволять задать порядок "В перед А".
	virtual bool setOrderObjBefore(const mcsWorkID& idObjBefore, bool bTryOnly) = 0;

		// Метод возвращает ID объекта, который по порядку следования находится перед данным.
		// Если порядок не задан, результат будет WID_NULL.
		// Возвращаются только те ID, которые были назначены методом setOrderObjBefore.
	virtual mcsWorkID getOrderObjBefore() const = 0;

		// Задать порядок следования объектов в сборке:
		//   установить idAsmObjBefore перед this.
		//
		// Метод возвращает true, если среди зависимостей idAsmObjBefore нет текущего объекта.
		// 
		// Если bTryOnly = true, метод лишь проверяет возможность задания желаемого порядка следования.
		// Режим bOnlySet = true - только для системных целей, метод без проверок задает порядок следования.
		// Внимание. Если объект-деталь A был данным методом поставлен перед объектом B,
		// и если объект-деталь B при этом никак не зависит от объекта A, то данный метод
		// должен позволять задать порядок "В перед А".
	virtual bool setOrderAsmObjBefore(const mcsWorkID& idAsmObjBefore, bool bTryOnly, bool bOnlySet = false) = 0;

		// Метод возвращает ID объекта уровня сборки, который по порядку следования находится перед данным.
		// Для первого объекта результат будет WID_NULL.
	virtual mcsWorkID getOrderAsmObjBefore() const = 0;

	// Метод должен возвращать сохраненную геометрию для указанного F/E/V,
	// idFEV должен быть из списка getDependsOn.
	// Запрос приходит в случае, когда системе на этапе 3D-конверсии ассоциативных привязок не удается
	// найти фактическую геометрию элемента, от которого зависит данный объект.
	// Геометрию не нужно запрашивать из 3D-модели или из кэша геометрии.
	// Нужно вернуть хранимую копию, либо получить её ка-то косвенно.
	// Если таковой нет, то нужно вернуть false и ссылка будет потеряна.
	// 
	// При правильной работе с FEV-объектами из dependsOn запрос в этот метод никогда не придёт.
	// Для гарантии этого нужно в процессе обновления объекта (в методе onUpdatе)
	// Явно запрашивать геометрию из 3D-тела. Её можно не использовать, но запросить нужно.
	// В момент запроса она будет закэширована и затем при необходимости использована при конверсии привязок.
	//
	virtual bool queryStoredGeometryOfFevDependency(const mcsWorkID& idFEV, OUT McsEntityGeometry& geom_wcs) const {
		return false;
	}
};

typedef McsArray<IMc3dHistoryItemPtr, IMc3dHistoryItem*> mc3dHistoryItemsArray;
//==============================================================================
enum Mc3dGCSElementEnum
{
	kMcGCSElem_Unk    = -1,
	kMcGCSElem_WPT_Origin = 0,
	kMcGCSElem_WA_OX  = 1,
	kMcGCSElem_WA_OY  = 2,
	kMcGCSElem_WA_OZ  = 3,
	kMcGCSElem_WPL_XY = 4,
	kMcGCSElem_WPL_YZ = 5,
	kMcGCSElem_WPL_ZX = 6,
};

typedef McsArray<Mc3dGCSElementEnum, Mc3dGCSElementEnum> mc3dGcsElementsArr;
//==============================================================================
struct IMc3dDocHistory : public virtual IMcObject
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dDocHistory);

public:

	IMCS_QI_METHOD_DEFINITION(IMc3dDocHistory, IMcObject);

	virtual mcsWorkID              getDocumentID() const = 0;
	M3D_API virtual IMcDocumentPtr getDocument() const;

	virtual McsString tree3d_getName() const = 0;

		// выдаёт требуемый элемент глобальной координатной системы документа
	virtual IMc3dCoordSysObjectPtr getGCSElement(Mc3dGCSElementEnum) = 0;

		// Элементы ГСК по умолчанию физически не существуют в документе. При первом же
		// обращении к getGCSElement они появляются, если не созданы. Это не всегда надо.
		// Чтобы определить существует ли физически определённый объект ГСК - 
		// можно воспользоваться методом ниже.
	virtual bool doesGCSElementExist(Mc3dGCSElementEnum) const = 0;

		// Возвращает список существующих	элементов глобальной коорд. системы;
		// Либо в виде массивов ID, либо в виде массива типов;
		// Если какой-то массив не нужен, укажите NULL
	virtual void getExistingGCSElements(
		OUT OPTIONAL mcsWorkIDArray*     pGcsObjectsIds,
		OUT OPTIONAL mc3dGcsElementsArr* pGcsObjectTypes) const = 0;

		// Выдаёт непосредственные дочерние элементы данного элемента дерева построения.
		// Если idItem == WID_NULL, выдаст корневые элементы дерева истории 3D-построения.
		// Параметр bInclude3dBlocks учитывается только если idItem ссылается на всю историю построения.
	virtual HRESULT tree3d_getChildren4Item(
		IN const mcsWorkID& idItem,
		OUT mcsWorkIDArray& idsChlidren,
		IN OPTIONAL bool    bInclude3dBlocks = false) const = 0;

	virtual HRESULT getDrawingViews(OUT mcsWorkIDArray& idsDrawingViews) const = 0;
	virtual HRESULT getSections(OUT mcsWorkIDArray& idsSections) const = 0;

		// Выдаёт объект(ы) сборочного контекста по имени
		// Детали (тела) можно получить как по имени самого тела (partName), так и по имени базового родительского объекта
	virtual IMcEntityPtr getSubItemByName(LPCTSTR szName, OUT OPTIONAL mcsWorkIDArray* pIdsSameNamedItems = NULL) const = 0;

		// Возвращает объект, управляющий переменными в документе, к которому относится история построения.
		// Если указан externalVarsFilePath, то возвращает объект, управляющий переменными указанного внешнего файла.
		// В этом случае используется история построения пространства модели top-документа,
		// связанного с this-историей построения.
		// Метод используется в режиме, когда включена реализация кода, не использующая OdDbAssoc-объекты.
	virtual IMcsDocVariablesManager* getDocVarsMan(IN OPTIONAL LPCTSTR externalVarsFilePath = NULL) = 0;
};
//==============================================================================
// объект координатной системы: точка, ось или плоскость
// (!) наследовать виртуально (нужно для наследования частичной реализации)
struct IMc3dCoordSysObject :  public virtual IMc3dHistoryItem,
                              public virtual IMc3dConstraintCompatible
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dCoordSysObject);

public:

	IMCS_STD_METHOD_DEFINITION3(IMc3dCoordSysObject, IMc3dHistoryItem, IMc3dConstraintCompatible);

		// true, если объект является элементов глобальной координатной системы документа
	virtual bool isGCSObject(OUT OPTIONAL Mc3dGCSElementEnum* pGcsItemType = NULL) const = 0;

		// true, если объект ни от чего не зависит, имеет фиксированное построение
	virtual bool isFixedDef() const = 0;

		// Если объект !isFixedDef() то выдаст
		// список параметров, которыми определяется его положение
	virtual HRESULT getDefinitionParams(OUT McGeometryParamArray& params) const = 0;
};
//==============================================================================
enum McWPTDefTypeEnum
{                           // params:
	kMcWPTDef_Unk        = 0,
	kMcWPTDef_Fixed      = 1,
	kMcWPTDef_3Planes    = 2, // planar, planar, planar
	kMcWPTDef_2Curves    = 3, // curve, curve
	kMcWPTDef_CurveNSurf = 4, // curve, surf
	kMcWPTDef_WPTClone   = 5, // pt-ref
	kMcWPTDef_Center     = 6, // pt | CA | EA | sphere | torus
};
//==============================================================================
struct IMc3dWorkPoint : public virtual IMc3dCoordSysObject
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dWorkPoint);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dWorkPoint, IMc3dCoordSysObject);

	virtual McWPTDefTypeEnum getDefinitionType() const = 0;
	virtual mcsPoint         getPosition() const = 0;
	virtual HRESULT          setFixedDef(IN const mcsPoint& pnt) = 0;

		// Устанавливает зависимый тип определения точки.
		// Если объект является частью ГСК, будет ошибка.
		// Если для указанного типа не удастся вычислить положение точки, будет ошибка.
	virtual HRESULT setDefinition(McWPTDefTypeEnum newDefType, IN const McGeometryParamArray& newParams) = 0;
};
//==============================================================================
enum McWADefTypeEnum
{                                // params:
	kMcWADef_Unk              = 0,
	kMcWADef_Fixed            = 4,
	kMcWADef_Axis             = 5, // line|CA|EA|Polyline|Cyl|Cone|Torus - rotation axis, axis of symmetry
	kMcWADef_2Points          = 6, // pt-ref, pt-ref
	kMcWADef_2Planes          = 7, // planar, planar
	kMcWADef_Normal2CurveInPt = 8, // pt-ref, curve
	kMcWADef_Normal2SurfInPt  = 9, // pt-ref, surf
};
//==============================================================================
struct IMc3dWorkAxis : public virtual IMc3dCoordSysObject
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dWorkAxis);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dWorkAxis, IMc3dCoordSysObject);

	virtual McWADefTypeEnum getDefinitionType() const = 0;
	virtual mcsLineSeg      getPositionAsLS() const = 0;
	virtual mcsLine         getPositionAsLine() const = 0;
	virtual mcsVector       getDirection() const = 0;

	virtual HRESULT   setFixedDef(IN const mcsPoint& pntStart, IN const mcsPoint& pntEnd) = 0;

		// Устанавливает зависимый тип определения оси.
		// Если объект является частью ГСК, будет ошибка.
		// Если для указанного типа не удастся вычислить положение оси, будет ошибка.
	virtual HRESULT setDefinition(McWADefTypeEnum newDefType, IN const McGeometryParamArray& newParams) = 0;
};
//==============================================================================
enum McWPLDefTypeEnum
{                                   // params:
	kMcWPLDef_Unk                = 0,
	kMcWPLDef_Fixed              = 1,
	kMcWPLDef_3Points            = 2, // pt-ref, pt-ref, pt-ref
	kMcWPLDef_TwoLines           = 3, // linear, lineear
	kMcWPLDef_NormalToCurveInPt  = 4, // curve | pt-ref, curve
	kMcWPLDef_Normal2SurfInPt    = 5, // pt-ref, surf
	kMcWPLDef_PlaneLineNAngle    = 6, // linear, planar, angle | planar, linear, angle
	kMcWPLDef_PlaneNOffset       = 7, // planar, offset
};
//==============================================================================
struct IMc3dWorkPlane : public virtual IMc3dCoordSysObject
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dWorkPlane);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dWorkPlane, IMc3dCoordSysObject);

	virtual McWPLDefTypeEnum getDefinitionType() const = 0;
	virtual mcsPlane  getPosition() const = 0;
	virtual mcsVector getNormal() const = 0;

		// возвращает точки на плоскости, точки - это противоположные углы прямоугольника 
		// вдоль осей u/v на плоскости, ограничивающие область отрисовки графического примитива
	virtual HRESULT   getBoundedPosition(
		OUT mcsPlane& plane,
		OUT mcsPoint& boundRectCorner1,
		OUT mcsPoint& boundRectCorner2) const = 0;

	virtual HRESULT   setFixedDef(
		IN const mcsPlane& plane,
		IN OPTIONAL const mcsPoint& boundRectCorner1 = *(mcsPoint*)NULL,
		IN OPTIONAL const mcsPoint& boundRectCorner2 = *(mcsPoint*)NULL) = 0;

		// выдаёт угол или расстояние для типов
		// kMcWPLDef_PlaneLineNAngle и kMcWPLDef_PlaneNOffset соотв-но
	virtual HRESULT getParamVal(double& val) const = 0;

		// Устанавливает угол или расстояние для типов
		// kMcWPLDef_PlaneLineNAngle и kMcWPLDef_PlaneNOffset соотв-но
	virtual HRESULT setParamVal(double val) = 0;

		// выдаёт ID переменной, связанной с параметров угла или расстояния,
		// если плоскость имеет соотв. тип определения, WID_NULL иначе
	virtual mcsWorkID getParamVarID() const = 0;

		// Устанавливает зависимый тип определения плоскости.
		// Если объект является частью ГСК, будет ошибка.
		// Если для указанного типа не удастся вычислить положение плоскости, будет ошибка.
	virtual HRESULT setDefinition(McWPLDefTypeEnum newDefType, IN const McGeometryParamArray& newParams) = 0;
};
//==============================================================================

// Данные местного разреза.
// Хранятся в 2D-эскизе
struct McDrawingViewLocalCutData
{
public:
	mcsWorkID m_idDV; // ID целевого проекционного вида

	// точка, по которой определять начальную плоскость резки
	// в локальных координатах 2D-вида
	mcsPoint  m_depthDefPoint_DvLcs;

	double    m_depth; // глубина выреза, относительно точки m_depthDefPoint_DvLcs
	//...................................

public:
	MCTYP_API McDrawingViewLocalCutData();
	MCTYP_API McDrawingViewLocalCutData(const McDrawingViewLocalCutData& other);

	MCTYP_API bool isNull() const;
	operator bool() const {return !isNull();}

	MCTYP_API bool operator == (const McDrawingViewLocalCutData& other) const;

	bool operator != (const McDrawingViewLocalCutData& other) const {
		return !operator == (other);
	}

	MCTYP_API bool write(IMcsStream* pS) const;
	MCTYP_API bool read(IMcsStream* pS);
};

typedef std::shared_ptr<McDrawingViewLocalCutData> McDrawingViewLocalCutDataPtr;
//==============================================================================

struct IMcPlanarSketch : public virtual IMc3dHistoryItem, public virtual IMc3dConstraintCompatible
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcPlanarSketch);

public:

	IMCS_STD_METHOD_DEFINITION3(IMcPlanarSketch, IMc3dHistoryItem, IMc3dConstraintCompatible);

	virtual mcsWorkID getPlanarEntityID() const = 0;
	virtual HRESULT   setPlanarEntityID(const mcsWorkID& idPlanar) = 0;
	virtual mcsPlane  getPlane() const = 0;

		// Устанавливает новую плоскость эскиза.
		// Недопустимо, если для плоскости методом setPlanarEntityID задан существующий примитив;
		// fAutoAdjustCS позволяет ориентировать коорд систему эскиза по геометрии
		// содержимого эскиза. Пример: если флаг указан и в эскизе есть отрезок, то
		// началом системы координат будет начало отрезка, а направлением OX - направление
		// отрезка. Это позволит инициализировать более адекватную систему координат
		// для эскизов без опорного планарного элемента.
	virtual HRESULT   setPlane(const mcsPlane& newBasePlane, bool fAutoAdjustCS = true) = 0;

		// Метод позволяет устанавливать объекты точка/ось, которые в явной форме будут задавать
		// систему координат эскиза. Т.е. проекция объекта pointRefParm на плоскость эскиза будет определять
		// начало координат. Проекция направления axisRefParm на плоскость эскиза будет определять ось
		// oX, если bAxisIsX есть true, иначе oY.
		// Допустимо указывать пустые идентификаторы, в этом случае СК эскиза будет браться
		// с планарного объекта.
		//
		// NOTE1: Сам планарный объект остаётся тот же. Для его изменения используйте метод setPlanarEntityID.
		//
		// NOTE2: Назначит СК можно только эскизу внутри к.л. тела.
		// Допустимыми объектами являются id Edge/Vertex/WorkPoint/WorkAxis, только из того же тела,
		// в которое входит этот эскиз и не зависящие от самого эскиза.
		// Если bTryOnly = true, происходит только проверка допустимости установки указанной СК
	virtual HRESULT   setCoordSystemOnPlane(
		IN const McGeometryParam& pointRefParam,
		IN const McGeometryParam& axisRefParam,
		IN bool                   bAxisIsX,
		IN OPTIONAL bool          bTryOnly = false,
		IN OPTIONAL bool          bInvertAxis = false) = 0;

		// Получить объекты, определяющие систему координат эскиза на его плоскости
	virtual HRESULT   getCoordSystemOnPlane(
		OUT McGeometryParam& pointRefParam,
		OUT McGeometryParam& axisRefParam,
		OUT bool&            bAxisIsX,
		OUT bool&            bInvertAxis) const = 0;

		// если fGetTrueProjectionTfm == false, то выдаётся матрица, которая содержит поворот и сдвиг,
		// координата Z будет оставаться валидной, но если указать true, то вернётся полноценная матрица проецирования;
		// 3D объекты, типа окружностей и более сложных нужно трансформить матрицей, полученной с параметром
		// fGetTrueProjectionTfm = false
	virtual HRESULT   getWorld2SketchTfm(OUT mcsMatrix3d& W2S, IN OPTIONAL bool fGetTrueProjectionTfm = false) const = 0;
	virtual HRESULT   getSketch2WorldTfm(OUT mcsMatrix3d& S2W) const = 0;
	virtual mcsPoint  tfmPointW2S(const mcsPoint& pt3d) const = 0;
	virtual mcsPoint  tfmPointS2W(const mcsPoint& pt2d) const = 0;

	virtual bool      isInEditMode() const = 0;
	virtual HRESULT   enterEditMode() = 0;
	virtual HRESULT   exitEditMode() = 0;

		// работа с элементами, включенными в эскиз, они должны располагаться 
		// в той же плоскости, что и эскиз
	virtual HRESULT   getContainingObjects(OUT mcsWorkIDArray& ids, bool fInclObjects = true, bool fInclProjections = true) const = 0;
	virtual HRESULT   addObject(const mcsWorkID& id, bool fHideIncludedObject = true) = 0;
	virtual HRESULT   addObjects(const mcsWorkIDArray& ids, bool fHideIncludedObjects = true) = 0;
	virtual HRESULT   removeObject(const mcsWorkID& id) = 0;
	virtual HRESULT   removeObjects(const mcsWorkIDArray& ids) = 0;
	virtual bool      doesContainObject(const mcsWorkID& idObj) const = 0;

	virtual HRESULT   getGeometry(OUT mapWID2MEG& IDs2GeomMap, bool fSketchCS) const = 0;
	virtual HRESULT   getGeometry(OUT mcsGeomEntArray& rawGeometry, bool fSketchCS) const = 0;

		// получить геометрию включенного в состав эскиза эелмента;
		// idItem определяет элемент, в зависимости от режима работы и реализации ID может быть реальным ID объекта в чертежа,
		// может быть ID проекции, а может быть и абстрактным значением (GUID);
		// в последнем случае получить геометрию элемента можно, используя только этот метод
	virtual HRESULT   getGeometry(IN const mcsWorkID& idItem, OUT McsEntityGeometry& geom, bool fSketchCS) const = 0;

	virtual IMcProjSketchEntPtr projectObject(const mcsWorkID& idObj, bool fHideCreatedProjection = true) = 0;

		// если объект спроецирован, позволяет получить ID этой существующей проекции
	virtual mcsWorkID getIdExistingProjectionOf(const mcsWorkID& idObj) const = 0;

		// метод для проецирования части другого объекта
	virtual IMcProjSketchEntPtr projectObject(const McGeometryParam& objExRef, bool fHideCreatedProjection = true) = 0;

		// если объект спроецирован, позволяет получить ID этой существующей проекции
	virtual mcsWorkID getIdExistingProjectionOf(const McGeometryParam& objExRef) const = 0;

		// создаёт профиль и опционально пытается обработать регион эскиза по указанной точке
	virtual IMcSketchProfilePtr createProfile() = 0;
	virtual HRESULT   getProfiles(OUT mcsWorkIDArray& profilesIDs) const = 0;

		// пытается найти элемент эскиза по GS-маркеру данной геометрии;
		// если bGeomInWCS=true, то геометрия дана в мировой СК, иначе в локальной СК эскиза;
		// если маркер на геометрии есть, и нет такого примитива в эскизе, то результат будет WID_NULL;
		// если маркера нет, то попытается найти геометрически совпадающий примитив,
		// при этом будет использована внутренняя точность модели M3D
	virtual mcsWorkID getSketchEntityByGeom(bool bGeomInWCS, const McsEntityGeometry& meg) const = 0;

		// по указанному маркеру находит элемент эскиза, и опционально выдаёт его геометрию;
		// если bGetGeomInWCS = екгу, вернет геометрию в мировой СК, иначе в локальной СК эскиза.
	virtual mcsWorkID getSketchEntityByGsMarker(
		McGSMarker                      gsm,
		IN OPTIONAL bool                bGetGeomInWCS, // = true
		OUT OPTIONAL McsEntityGeometry* pSrcEntGeom) const = 0; // = NULL

		// system use
	virtual mcsWorkID _getConstraintsGroupId() const = 0;
	virtual HRESULT   _setConstraintsGroupId(const mcsWorkID& id2dCGroup) = 0;

	virtual int       getContainingObjectsCount() const = 0;

		// выдает/устанавливает флаг, который определяет, будет ли эскиз удалять объекты
		// при удалении самого себя, по умолчанию включен
	virtual bool      isOnAutoeraseOfInclObject() const = 0;
	virtual HRESULT   setFlagAutoeraseOfInclObjects(bool fAutoeraseIsOn) = 0;

		// применяет все зависимости между примитивами эскиза
	virtual HRESULT   applyConstraints(bool fForceRecalc) = 0;

		// ID точки, которая является точкой Origin системы координат эскиза.
		// Точка используется для наложения 2D-зависимостей.
		// (!) Это НЕ точка, которая задаёт систему координат эскиза, это точка, которая НАХОДИТСЯ в начале СК эскиза и зафиксирована.
		// (!) Может быть WID_NULL, т.к. не является определяющей и по большому счету она опциональна.
		// Например, этой точки может не быть, если эскиз создан через АПИ; и не выполнялось его редактирование пользователем.
		// На эскизах она автоматически создаётся в момент входа в режим редактирования.
	virtual mcsWorkID getBasePointID() const = 0;

		// Метод разрывает все ассоциативные связи у эскиза
		// Если СК эскиза использует какие-то объекты в СК, эскиз сохраняет СК на момент вызова и более не будет зависеть
		// от объектов, вроде плоскости, точки, задающей начало СК и т.д..
		// Если эскиз содержит проекции к.л. элементов, они заменяются на простые геом. примитивы.
		// При этом эскиз старается по возможности сохранить все наложенные 2D-зависимости.
	virtual HRESULT breakAssocLinks() = 0;

		// Метод возвращает менеджер управления 2D зависимостями эскиза.
		// Допустимые значения для ctrsNetType:
		//   kMc2dCtrNet_Auto - вне режима редактирования = kMc2dCtrNet_Sketch, иначе kMc2dCtrNet_MCS
		//   kMc2dCtrNet_MCS - вернёт NCAD-сеть зависимостей, если эскиз в режиме редактирования, иначе NULL
		//   kMc2dCtrNet_Sketch - вернёт внутреннюю псевдо-сеть зависимостей эскиза
		// fForceCreateReqData нужно ставить в true, когда требуется безусловно создать
		// все необходимые структуры данных зависимостей.
		// fForceCreateReqData = false - это случай, когда нужно считать имеющуюся информацию о зависимостях в эскизе.
	virtual IMcs2dConstraintsManager* get2dConstraintsManager(McCtrs2dNetType ctrsNetType, bool fForceCreateReqData) = 0;

	// Возвращает true, если указанная геометрия эскиза полностью определена 2D-зависимостями.
	virtual bool isGeomFullyConstrained(const mcsWorkID& idGeom) const = 0;

	// Возвращает true, если вся геометрия эскиза полностью определена 2D-зависимостями.
	virtual bool isSketchFullyConstrained() const = 0;

		// NO DOC.
		// Для системных целей.
	virtual HRESULT saveSketchToInternalDataCont() = 0;

		// NO DOC.
		// Для системных целей.
	virtual bool isSeparateObjectsMode() const = 0;

		// Добавить в эскиз геометрический примитив и присвоить ему идентификатор с указанным значением 'id'.
		// В качестве геометрического объекта допустимы только точка и кривые всех типов.
		// Если bGeomInWCS = true, геометрия geom дана в мировой СК, иначе в локальной СК эскиза
	virtual HRESULT addGeometry(const mcsWorkID& id, bool bGeomInWCS, const McsEntityGeometry& geom) = 0;

		// NO DOC.
		// Для системных целей.
	virtual HRESULT getGeometryProperty(const mcsWorkID& id, const McsString& name, OUT MCSVariant& data) const = 0;

		// NO DOC.
		// Для системных целей.
	virtual void addAutoCtrId(const mcsWorkID& id) = 0;
	virtual bool isExistNotAutoConstainedIds() const = 0;

		// NO DOC
		// Для системных целей.
	virtual bool _canObjectBeAdded(const mcsWorkID& id, OUT OPTIONAL HRESULT* pHRes = NULL) const = 0;

		// Установить данные местного разреза.
		// Если в новых данных меняется ID вида, то происходит перепривязка эскиза.
	virtual bool setDrawingViewLocalCutData(const McDrawingViewLocalCutData& localCutData) = 0;

		// Получить связанные данные местного разреза.
	virtual const McDrawingViewLocalCutData* getDrawingViewLocalCutData(const McDrawingViewLocalCutData& localCutData) const = 0;
};

typedef McsArray<IMcPlanarSketchPtr, IMcPlanarSketch*> mcPlanarSketchesArray;
//==============================================================================
struct IMcProjSketchEnt : public virtual IMc3dHistoryItem
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcProjSketchEnt);

public:

	IMCS_STD_METHOD_DEFINITION(IMcProjSketchEnt, IMc3dHistoryItem);

	virtual bool showInTree() {
		return false;
	}

		// ID эскиза, на который выполнена проекция
	virtual mcsWorkID                  getHostSketchID() const = 0;

		// Эскиз, на который выполнена проекция
	M3D_API virtual IMcPlanarSketchPtr getHostSketch() const;

		// Возвращает плоскость эскиза, она же есть плоскость проекции
	M3D_API virtual mcsPlane           getPlane() const;

		// ID объекта, который спроецирован на плоскость эскиза
	virtual mcsWorkID                  getSrcObjectID() const = 0;

		// Возвращает информацию об ассоциативной привязке к спроецированному на плоскость эскиза объекту
	virtual McGeometryParam            getSrcObjectRef() const = 0;

		// Возвращает геометрию проекции, флаг определяет систему координат, в которой будет отдаваться геометрия.
		// По умолчанию спроецировання геометрия отдаётся в ГСК
	virtual const McsEntityGeometry&   projectedGeometry(bool bGeomInWCS = true) const = 0;

		// Возвращает ID объекта, определяющего плоскость проекции,
		// по факту это результат вызова getHostSketch()->getPlanarEntityID,
		// (!) может быть == WID_NULL, это для авто-эскизов, созданных по геометрии, без привязки к плоскому обеъкту
	virtual mcsWorkID                  getPlanarObjectID() const = 0;
};
//==============================================================================
struct McsRegionBoundaries {
	McsArray<IMcProfileContourDataPtr, IMcProfileContourData*> maBoundaries;
};
//==============================================================================
struct IMcSketchProfile : public virtual IMc3dHistoryItem
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcSketchProfile);

public:

	IMCS_STD_METHOD_DEFINITION(IMcSketchProfile, IMc3dHistoryItem);

	virtual bool showInTree() {
		return false;
	}
	//............................................................................

	// Возможные типы геометрии профиля
	enum GeomTypeEnum
	{
		kMcProfGeom_Undefined = 0, // В профиле нет геометрии
		kMcProfGeom_SingleOpenCurve = 1, // Одна незамкнутая кривая
		kMcProfGeom_ClosedSimpleRegion = 2, // Одна замкнутая область, без дырок
		kMcProfGeom_ClosedComplexRegion = 4, // Одна замкнутая область с дырками, либо несколько областей; возможно, тоже с дырками

		// значение допустимо как параметр-маска режимов, профиль это значение никогда не отдаёт
		kMcProfGeom_Any = kMcProfGeom_SingleOpenCurve | kMcProfGeom_ClosedSimpleRegion | kMcProfGeom_ClosedComplexRegion,
	};

	virtual mcsWorkID getParentSketchID() const = 0;
	virtual HRESULT   setParentSketchID(const mcsWorkID& idSketch) = 0;
	virtual mcsWorkID getDependent3dFeatureID() const = 0;
	virtual HRESULT   setDependent3dFeatureID(const mcsWorkID& id3dFeature) = 0;

	M3D_API virtual IMcFeatureEntityPtr getDependent3dFeature() const;
	M3D_API virtual IMcPlanarSketchPtr  getParentSketch() const;
	M3D_API virtual mcsPlane            getPlane() const;

		// Пытается создать эскизный профиль, составив из геометрии эскиза одну незамкнутую кривую.
	virtual HRESULT initAsSingleOpenCurveProfile() = 0;

		// Добавляет или удаляет из набора регионов профиля область, которая определяется точкой
		// пересечения плоскости эскиза и указанной линии. Если не удаётся определить замкнутый 
		// регион в полученной точке, возвращается ошибка.
		// Метод применим только для регионов, допускающих тип:
		// kMcProfGeom_ClosedSimpleRegion и/или kMcProfGeom_ClosedComplexRegion.
	virtual HRESULT addOrRemoveRegionByLine(IN const mcsLine& line) = 0;

		// Добавляет или удаляет из набора регионов профиля элементы геометрии эскиза,
		// ссылки на которые заданы указанными маркерами.
		// Метод применим для регионов любого типа (как замкнутых, так и открытых).
		// В первую очередь из указанной геометрии происходит попытка получить замкнутые области и выполнить обработку для них.
		// Если замкнутых областей нет, то набор должен определять последовательную комбинацию не пересекающихся незамкнутых кривых.
	virtual HRESULT addOrRemoveRegionByMarkers(IN const mcsMcGsMarkerArray& sketchMarkers) = 0;

		// Старый синоним для addOrRemoveRegionByLine
	virtual HRESULT processByLine(IN const mcsLine& line) { return addOrRemoveRegionByLine(line); }

	// Тип геометрии профиля
	virtual GeomTypeEnum geomType() const = 0;

	virtual bool    isEmpty() const = 0;
	virtual HRESULT clear() = 0;

		// Методы для получения геометрии замкнутых областей профиля.
		// Для незамкнутого случая вернёт ошибку.
		// Если fLocalCoords=true, геометрия возвращается в системе координат профиля, если
		// false, то в мировой системе координат
	virtual HRESULT getContours(IN bool fLocalCoords, OUT CHoledAreaArray& regions) const = 0;
	virtual HRESULT getContoursInterfaces(OUT McsArray<McsRegionBoundaries, const McsRegionBoundaries&>& regions) = 0;

		// Метод возвращает кривую профиля для незамкнутого случая.
	virtual HRESULT getCurve(IN bool fLocalCoords, OUT mcsPolyline& profileCurve) const = 0;

		// получает некое число, которое ссылается на текущее состояние геометрии контуров;
		// как только происходит изменение геометрии, число меняется
	virtual DWORD   getGeomChangesLevel() const = 0;

	/// Добавляет или удаляет из набора все внешние замкнутые регионы эскиза.
	/// В случае успешного выполнения - true.
	virtual bool autoProcessExternalContours() = 0;
};
//==============================================================================

	// объект для интерактивной селекции профиля
struct m3dProfileSelectionSink : IEM_Sink
{
private:
	IMcObjectPtr          mpData;

public:
	IMcSketchProfilePtr   mpProfile;

	M3D_API m3dProfileSelectionSink();
	M3D_API ~m3dProfileSelectionSink();

	M3D_API virtual void ActiveEnt(const EM_Entity& ent,bool& fHighlight);
	M3D_API HRESULT onGetEntity(const EM_Entity& ent); // позвать на выходе из GetEntity, если нет ошибки

		// если fDenySketchSel=true, то запретит менять эскиз, если профиль станет пустым
	M3D_API HRESULT initSelection(
		IN bool                           fDenySketchSel, // true, если нельзя менять эскиз при выборе, обычно true в режиме редактирования сущ. профиля (pExistingProfile)
		IN IMcSketchProfile::GeomTypeEnum eAllowedGeomType, // тип допустимой геометрии профиля
		IN IEM*                           pEntMon,
		IN Mc3dModelingTypeEnum           applicable3dModlingModes, // режим 3D моделирования, для которого выполняется вызов
		IN OPTIONAL IMcSketchProfile*     pExistingProfile = NULL);

	M3D_API HRESULT reset();
};

//==============================================================================



//==============================================================================
struct IMc3dFEVGeomCache : public virtual IMcObject
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dFEVGeomCache);

public:

	IMCS_QI_METHOD_DEFINITION(IMc3dFEVGeomCache, IMcObject);

	virtual HRESULT save(IMcsStream* pS) const = 0;
	virtual HRESULT load(IMcsStream* pS, const mcsWorkID& idParentSolid) = 0;

		// Выдаёт кэшированную геометрию в СК MAPI.
		// Все особенности СК активного моделера применяются до возврата значения 'FEVGeom'
	virtual HRESULT getFEVGeometry(IN const mcsWorkID& idFEV, OUT McsEntityGeometry& FEVGeom) const = 0;

		// Обновляет геометрию в кэше.
		// Геометрия должна быть в СК MAPI (все особенности СК активного моделера должны быть нивелированы перед вызовом)
	virtual HRESULT setFEVGeometry(IN const mcsWorkID& idFEV, IN const McsEntityGeometry& FEVGeom) = 0;

		// Метод зовётся с целью оставить в кэше геометрии только те элементы FEV,
		// которые реально используются какими-то объектами. Метод желательно регулярно звать,
		// например, на конец команды, чтобы избежать лишних расходов на хранение
		// никому не нужной, но актуальной геометрии FEV.
	virtual HRESULT dropUnusedGeometry(IN const mcsWorkIDArray& unusedFEVIDsArr) = 0;

		// Зовётся построителем тела сразу после завершения построения указанного объекта,
		// по этому событию обновляется внутренний геометрический кэш только для указанного объекта
	virtual HRESULT onEndModify(const mcsWorkID& idSolid) = 0;

		// нужно позвать в момент удаления дочернего (врезного)
		// солида из родительского для очистки геом. кэша
	virtual HRESULT onRemoveChildSolid(const mcsWorkID& idChildSolid) = 0;

		// проверяет, пуст ли кэш
	virtual bool isCacheEmpty() const = 0;

		// возвращает тип моделера, использовавшегося для построения геометрии в кэше
	virtual m3dServer::ModelerType getGeometryCreatorType() const = 0;

		// Возвращает условную версию моделера, использовавшегося для построения геометрии в кэше.
		// NOTE: номер версии привязан к версии кода генератора Ref-ключей ассоциативных привязок
	virtual DWORD getGeometryCreatorVersion() const = 0;

		// Методы позволяют определить, являются ли возвращаемые данные через методы
		// getGeometryCreatorType и getGeometryCreatorVersion
		// теми, которые выставлены по умолчанию.
		// Если возвращаемое значение = false, то данные либо явно взяты с текущего 3D ядра,
		// либо были зачитаны из файла.
	virtual bool  isModelerTypeDefault() const = 0;
	virtual DWORD isModelerVerDefault() const = 0;
};
//==============================================================================
struct m3dFeatureInfo
{
	mcsWorkID idSrcObject; // ID объекта, который содержит данную фичу

	// ID объектов-фич внутри исходного объекта. Уникально в пределах родительского тела.
	GUID      idFeature;

	// Доп. индекс к idFeature, при создании построении через .NET
	// Для mdFtrID берётся клиентский GUID, строится несколько фич и чтобы их отличать, используется iFtrIdx.
	int       idxFeature;

	m3dFeatureInfo(){
		reset();
	}

	void reset() {
		idSrcObject.setNull();
		idFeature = GUID_NULL;
		idxFeature = 0;
	}
};
//==============================================================================
struct IMc3dFEVIDInfo : public virtual IMcObject
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dFEVIDInfo);

public:

	IMCS_QI_METHOD_DEFINITION(IMc3dFEVIDInfo, IMcObject);

	virtual HRESULT save(IMcsStream* pS) const = 0;
	virtual HRESULT load(IMcsStream* pS) = 0;

		// получает информацию о том, какая фича последней участвовала в модификации указанного FEV по его ключу
	MCTYP_API virtual HRESULT getFeatureInfoByRefKey(IN const McFEVRefKeyData& refKeyData, OUT m3dFeatureInfo& info);

		// получает информацию о фиче по указанному DW-идентификатору
	virtual HRESULT getFeatureInfoByDwId(IN DWORD dwID, OUT m3dFeatureInfo& info) = 0;

		// Присваивает или возвращает 32-bit идентификатор для указанной фичи.
		// iFtrIdx - доп. индекс к mdFtrID, при создании построении через .NET 
		// для mdFtrID берётся клиентский GUID, строится несколько фич и чтобы их отличать, используется iFtrIdx.
	virtual HRESULT assignDword4Feature(OUT DWORD& dwID, IN const mcsWorkID& idFtrOwnerObject, IN const GUID& mdFtrID, IN int iFtrIdx = 0) = 0;
		
	// присваивает или возвращает 32-bit идентификатор для указанной вершины в профиле
	virtual HRESULT assignDword4VertexIn2dSketch(OUT DWORD& dwID, IN const mcsWorkID& idProfile, IN DWORD dwVtxInternalID) = 0;

	virtual HRESULT assignDword4VertexInAnonymousProfile(
		OUT DWORD&          dwID,
		IN const mcsWorkID& idFtrOwnerObject, // объект - хозяин фичи
		IN const GUID&      mdFtrID,          // идентификатор фичи
		IN int              idxProfile,       // порядковый индекс профиля в фиче
		IN int              idxVertex) = 0;   // порядковый номер вершины в профиле

		// получает присвоенный 32-bin идентификатор фичи, -1, если не был присвоен;
		// про iFtrIdx см. assignDword4Feature
	virtual HRESULT getDword4Feature(OUT DWORD& dwFtrID, IN const mcsWorkID& idFtrOwnerObject, IN const GUID& mdFtrID, IN int iFtrIdx = 0) = 0;
	
		// получает присвоенный 32-bin идентификатор указанной вершины эскизного профиля
	virtual HRESULT getDword4VertexIn2dSketch(OUT DWORD& dwID, IN const mcsWorkID& idProfile, IN DWORD dwVtxInternalID) = 0;

		// описание параметров см. в assignDword4VertexInAnonymousProfile
	virtual HRESULT getDword4VertexInAnonymousProfile(
		OUT DWORD&          dwID,
		IN const mcsWorkID& idFtrOwnerObject,
		IN const GUID&      mdFtrID,
		IN int              idxProfile,
		IN int              idxVertex) = 0;

		// преобразует список 32-bit идентификаторов в WID объектов, соответствующим этим фичам/профилям
	MCTYP_API virtual HRESULT cvtDwIDs2ObjectIDs(IN const mcsDwordSetEx& dwIDs, OUT mcsWorkIDSetEx& objectIDs);

		// выдаёт список ID объектов-фич, от которых зависит построение элемента с указанным ключом
	MCTYP_API virtual HRESULT getDependsOnObjectsIDs(IN const McFEVRefKeyData& refKeyData, OUT mcsWorkIDSetEx& objectIDs);

		// выдаёт список фич, которые относятся к указанному объекту
	virtual HRESULT getFeaturesRelated2Object(const mcsWorkID& idFtrOwnerObject, OUT mcsDwordSetEx& ftrDwsList) = 0;

		// должен выдать максимальный использованный DWORD-идентификатор
	virtual DWORD   getMaxUsedDwID() const = 0;

		// возвращает множество фич в этом теле, которое выполняет включение в его состав других тел,
		// это либо булевы фичи, либо массив в режиме включения других солидов
	virtual HRESULT getIncludeOtherPartFeatures(OUT mcsDwordSetEx& ftrDwsList) const = 0;
};
//==============================================================================

// Хранит данные тела "после" построения объекта;
// Это поле используется для восстановления тела после удаления объектов.
// Если тело требуется как-то перестроить и есть сохранённое состояние "после", то
// Вместо перестроения будет восстановлено именно это состояние.
// Также тело, чьё построение неизвестно, может быть восстановлено только с помощью этих данных

struct Mc3dBodyState
{
protected:
	mutable mcsByteArray mSatData; // данных модели в SAT-формате
	mutable mcsMatrix    mTfm;     // матрица трансформации, которую нужно наложить на SAT данные
	long                 mSatVer;  // версия SAT потока
	mutable bool         mbPacked; // запакованы данные mSatData или нет
	mutable bool         mbTfmValid;

public:
	MCTYP_API Mc3dBodyState();

	MCTYP_API bool isVerSupportedByAcisBuilder() const;
	MCTYP_API void clear();
	MCTYP_API bool isEmpty() const;
	MCTYP_API bool isValid() const;

	// new get/set, SAT data only

	MCTYP_API bool getSATData(OUT mcsByteArray& satData) const;
	MCTYP_API bool setSATData(IN const void* pSatData, DWORD satDataSize);

	bool setSATData(IN const mcsByteArray& satData) {
		return setSATData(satData.GetData(), satData.GetSize());
	}

	// old get/set, SAT+Tfm

	MCTYP_API bool getSATDataOld(OUT mcsByteArray& satData, IN bool bFileSaveOp) const;
	MCTYP_API bool setSATDataOld(IN const void* pSatData, DWORD satDataSize);

	bool setSATDataOld(IN const mcsByteArray& satData) {
		return setSATDataOld(satData.GetData(), satData.GetSize());
	}

	MCTYP_API const mcsMatrix& tfm() const;
	MCTYP_API mcsMatrix&       setTfm();

	MCTYP_API long  satVer() const;
	MCTYP_API void  setSatVer(long afVer);

protected:
	MCTYP_API void _pack(OUT OPTIONAL mcsByteArray* pPackedData = NULL) const;
	MCTYP_API void _unpack() const;
};
//==============================================================================

struct IMc3dBody :
	public virtual IMc3dFEVIDInfo,
	public virtual IMc3dFEVGeomCache
{
protected:
	mcsWorkID     mID;
	Mc3dBodyState mBodyStateAfter;

protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dBody);

public:

	IMCS_QI_METHOD_DEFINITION3(IMc3dBody, IMc3dFEVIDInfo, IMc3dFEVGeomCache);

	// позволяет утстановить на тело ID связанного с ним объекта
	MCTYP_API virtual HRESULT setID(const mcsWorkID& externalID);
	MCTYP_API virtual const mcsWorkID& ID() const;

		// если установлен ID внешнего объекта, то поднимает его и зовёт ему writeEnabled
	MCTYP_API virtual HRESULT writeEnabled();

	MCTYP_API virtual HRESULT save(IMcsStream* pS) const;
	MCTYP_API virtual HRESULT load(IMcsStream* pS);

	MCTYP_API IMc3dBody& operator=(const IMc3dBody& elem);

	virtual HRESULT transformBy(const mcsMatrix& tfm)
		{ return E_NOTIMPL; }

	// добавляет с указанной операцией указанный солид к текущему
	virtual HRESULT booleanOper(IN const IMc3dBody* pSolid, IN MdPartFeatureOperationEnum operation)
		{ return E_NOTIMPL; }

	enum PreviewModeFlags
	{
		kFaces    = 0x01, // в превью нужны грани
		kEdges    = 0x02, // в превью нужны ребра
		kDetailed = 0x04, // в превью нужна детальная информация: все грани/ребра раздельно, геометрия для граней/ребер

		kFE            = kFaces | kEdges,

		kDetailedFaces = kFaces | kDetailed,
		kDetailedEdges = kEdges | kDetailed,
		kDetailedFE    = kFE    | kDetailed,
	};

	// выдает текущее 3D представление солида, 
	// если точность -1, то будет использоваться точность по умолчанию,
	// если сохраненное представление модели соответствует текущим данным, 
	// то обсчета не будет, возвращен будет кэш
	virtual HRESULT getModelPreview(
		IN OPTIONAL IMcModeler*      pModeler, // NULL для использования моделера по умолчанию
		OUT CxImage&                 image,
		IN OPTIONAL PreviewModeFlags ePreviewTypeFlags, // = PreviewModeFlags::kFaces
		IN OPTIONAL double           accuracy = -1) const
	{
		return E_NOTIMPL;
	}

	virtual HRESULT getModelPreview(
		IN OPTIONAL IMcModeler* pModeler, // NULL для использования моделера по умолчанию
		OUT mcsGeomEntArray&    geArr, // in simplest case expected array of <mcsTriangle>
		IN OPTIONAL bool        fIncludeEdges = false,
		IN OPTIONAL double      approxTol_mm = -1) const
	{
		return E_NOTIMPL;
	}

	/// Возвращает список маркеров Face/Edge/Vertex указанных геометрических типов.
	virtual HRESULT getSubentsByMask(IN DWORD geomTypesMask, OUT mcsMcGsMarkerArray& subentMarkers) const
	{
		subentMarkers.SetSize(0);
		return E_NOTIMPL;
	}

	/// Возвращает геометрию указанного через маркер подобъекта.
	virtual HRESULT getSubentGeometry(IN McGSMarker gsMarker, OUT McsEntityGeometry& subentGeom) const
	{
		subentGeom.setNull();
		return E_NOTIMPL;
	}

// 	virtual HRESULT getFaces(McFaceArray& faces)
// 		{ return E_NOTIMPL; }
// 	virtual HRESULT getEdges(McEdgeArray& edges)
// 		{ return E_NOTIMPL; }

	// ...........................................................................

	MCTYP_API virtual Mc3dBodyState&       _setBodyDataAfter();
	MCTYP_API virtual const Mc3dBodyState& _bodyDataAfter() const;
	MCTYP_API virtual HRESULT              _invalidateStateAfter();

		// Если данное тело закэшировано, вернёт ID модели, ID валидный пока существует сама модель
		// и только в течение активной сессии приложения.
	virtual int getCache3dModelId() const
	{
		return -1;
	}

		// Возвращает ограничивающий параллелепипед для тела
	MCTYP_API virtual HRESULT getBounds(OUT mcsBoundBlock&) const;
};
//==============================================================================

enum Mc3dPartCntQueryMode
{
	// следующие три флага являются взаимоисключающими
	kMc3dContents_noBoolFtrs           = 0x0, // без состава булевых фич
	kMc3dContents_allBoolFtrs          = 0x1, // включить весь состав булевых фич на всех уровнях вложенности
	kMc3dContents_noSuppressedBoolFtrs = 0x2, // включить весь состав не подавленных булевых фич на всех уровнях вложенности
	kMc3dContents_boolFtrsMask         = 0x7, // маска значений для булевых фич

	kMc3dContents_onlyDbEntities       = 0x8,  // только объекты с графикой (без переменных и.т.п.)
	kMc3dContents_onlyRootDbEntities   = 0x18, // только объекты с графикой и те, которые попадают в корень дерева состава тела (без проекций, геометрии, профилей и т.п.)

	kMc3dContents_onlyRigidGeomSet     = 0x20, // только объекты, которые должны жестко перемещаться вместе с host-солидом
	
	kMc3dContents_sortAlgoV3           = 0x100 // в методе reorderObjectsDueToTheirDepends сортируем алгоритмом 3 версии
};
//==============================================================================

// Интерфейс, аналогичный IMcGeometry, но для поверхностей.
// Специфичных интерфейсов для каждого типа поверхности нет,
// поэтому вся работа выполняется через IMcSurfaceGeometry.

struct IMcSurfaceGeometry : public virtual IMcObject
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcSurfaceGeometry);

	//virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvobj) = 0;
	IMCS_QI_METHOD_DEFINITION(IMcSurfaceGeometry, IMcObject);

	virtual const GUID&              getClassID() const { return IID_IMcSurfaceGeometry; }

	virtual const McsEntityGeometry& asEntityGeometry() const = 0;
	virtual IMcDbEntityPtr           DbEntity() = 0;
};
//==============================================================================

struct IMc3dSolid :
		public virtual IMc3dHistoryItem,
		public virtual IMc3dConstraintCompatible
{
public:
	IMc3dBodyPtr   m_pBody;

protected:
	int            mRefKeyVer;

protected:
	M3D_API IMc3dSolid();

public:
	//IMCS_STD_METHOD_DEFINITION(IMc3dSolid, IMc3dHistoryItem);
	virtual const GUID& getClassID() const {return __uuidof(IMc3dSolid);}
	M3D_API virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj);
	//M3D_API virtual bool isKindOf(REFIID riid) const;

	M3D_API virtual void invalidate() override;

		// сохраняет/считывает связанное с солидом тело
	M3D_API virtual HRESULT onWrite(OUT IMcsStream* pStream) const;
	M3D_API virtual HRESULT onRead(IN IMcsStream* pStream);

	virtual HRESULT getVolume(OUT double& vol) const = 0;
	virtual HRESULT setVolume(IN double vol) = 0;

		// возвращает true, если модель объекта была изменена и при обновлении тело
		// может при этом послать реакторам событие kMcObjModelChanged
		// (проверяется именно изменённость объекта, а не присоединенного к нему тела)
	M3D_API virtual bool isObjModelChanged(bool fCheckPosChanges = false) const;
	M3D_API virtual bool isPartModelChanged(bool fCheckPosChanges = false) const;

	M3D_API virtual IMc3dSolidPtr getHostSolid(bool bAllowRetDumbSolid = false) const override;
	M3D_API virtual HRESULT getDependent(OUT mcsWorkIDSetEx& idsDependent) const override;

		// получить состав детали.
		// по умолчанию тела, включенный в булеву фичу не входят в состав детали,
		// чтобы нивелировать это расхождение, укажите нужный режим eIncludeBooleanFeaturesMode;
		// (!) установка bGetOrdered в значение true существенно замедляет работу методов
	virtual bool getPartContents(
		OUT mcsWorkIDArray&  ids,
		bool                 bGetOrdered,
		DWORD                dwFlags = kMc3dContents_noBoolFtrs) = 0; // enum Mc3dPartCntQueryMode

		// Позволяет узнать, какой булевой фичей использовано данное тело
		// Если bGetTopmostUnsuppressedBoolFtr = true, будет подниматься иерархически вверх по
		// дереву включений булевых фич до тех пор, пока не будет найден первый самостоятельный солид,
		// не включенный в неподавленную булеву фичу. Подавленные булевы фичи игнорируются.
		// Если нужен просто факт наличия булевой фичи, указывайте false.
	virtual mcsWorkID getHost3dBooleanFeature(bool bGetTopmostUnsuppressedBoolFtr) const = 0;

		// Метод возвращает все резьбы детали, к которой относится данный солид.
		// Если bLookInBooleanFeatures = true, вернет все резьбы с учетом всех вложенных тел в булевых фичах.
		// NOTE: Если bLookInBooleanFeatures = true и булева фича включает в себя блок с резьбами,
		//       то idsThreadFeatures будет содержать составные ID.
	M3D_API virtual HRESULT getThreadsInPart(OUT mcsComplexWorkIDArray& idsThreadFeatures, bool bLookInBooleanFeatures) const;

		// Метод возвращает все резьбы стандартной детали, ID которой задаётся в аргументе idStdObject.
		// Если idStdObject == WID_NULL, то считается, что ID самого host-солида есть стандартный объект,
		// и если это действительно так, что будут возвращены его резьбы.
	M3D_API virtual HRESULT getStdThreadsInPart(OUT mcsWorkIDArray& idsStdThreadFeatures, IN const mcsWorkID& idStdObject = WID_NULL) const;

		// Метод возвращает признак наличия врезных 3D стандартных в теле.
		// Если сам солид является дочерним, то перенаправит запрос в родительское тело.
	M3D_API virtual  bool has3dStdInPart() const;

		// Возвращает набор curve-геометрии проволочной модели тела солида без учета
		// вхождения его в родительскую деталь,
		// и без учета операции его интеграции с род. телом (без учета booleanOper)
	virtual HRESULT getIsolatedWires(OUT mcsGeomEntArray& wiresGeom) = 0;

		// Метод позволяет получить счетчик изменений топологии модели солида.
		// Если некий объект отслеживает геометрию граней, ребер, вершин, можно гарантировать, что
		// если значение счетчика перестроений не изменилось, то элементы топологии имеют
		// абсолютно ту же геометрию.
		// Можно использовать для оптимизации перестроений и реакций между объектами в модели.
	virtual DWORD getBrepChangesCounter() const = 0;

		// Метод возвращает ID последнего объекта в детали, к которой относится этот солид
		// После этого объекта подразумевается элемент дерева истории построения End-of-Part.
		// Возвращаемый ID должен быть в цепочке идентификаторов, которую отдаёт метод getPartContents.
		// Задать такой конечный элемент построения в теле можно через вызов метода IMc3dHistoryItem.setAsLastPartItem.
		// Если указан pbIsRealEOP, значение флага будет true, если конец построения находится
		// в конце всего состава объектов тела, т.е. строится всё.
	M3D_API virtual mcsWorkID getLastPartItem(OUT OPTIONAL bool* pbIsRealEOP = NULL) const;

		// Получение/установка материала тела.
	virtual IMcEntityPtr getMaterial() const = 0;
	virtual bool         setMaterial(IMcEntity* pNewMaterial) = 0;

		// Получить ID отверстия, либо реального, либо в режиме "существующее" для указанного Face/Edge/Vertex.
		// Если указан bForceCreate, то будет пытаться создать отверстие-заместитель, если это возможно.
		// Метод реализует функционал распознавания существующих отверстий в деталях.
		// Если отверстия не существует и указан bForceCreate, то параметр pDesiredHoleAxisDir используется
		// для предпочтительной ориентации нового отверстия-заместителя.
	virtual mcsWorkID getHoleByFEV(
		const mcsWorkID& idFEV,
		bool             bForceCreate = false,
		const mcsVector* pDesiredHoleAxisDir = NULL) = 0;

		// Метод инициирует перестроение всего 3D-тела.
	M3D_API virtual bool rebuildPart();
};

//==============================================================================

// Вспомогательный интерфейс для управления параметрическими 3D-объектами,
// у которых имеется история 3D-построений.

struct IMc3dPartsManipulator : public virtual IMcObject
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dPartsManipulator);

public:
	IMCS_QI_METHOD_DEFINITION(IMc3dPartsManipulator, IMcObject);

	// Метод возвращает ID 3D-детали по ID одной из её составляющих
	virtual mcsWorkID getPartIdByItemId(const mcsWorkID& idPart3dItem) = 0;

	// Метод возвращает ID 3D-детали по ID её состава
	virtual mcsWorkID getPartIdByContents(const mcsWorkIDArray& ids3dPartCnt) = 0;

	// Метод позволяет получить ID элемента 3D-детали по её имени
	virtual mcsWorkID getPartItemByName(const mcsWorkID& idPart3dItem, LPCTSTR stItemName) = 0;

	// Метод возвращает все объекты, входящие в состав указанного 3D-тела.
	// Если bVarsOnly = true, то возвращаемый массив будет содержать только ID переменных (параметров) тела.
	//
	virtual bool      getPartContents(
		IN const mcsWorkID& idPart3dItem,
		OUT mcsWorkIDArray& idsCnt,
		IN OPTIONAL bool    bVarsOnly = false) = 0;

	// Метод сохраняет указанное 3D-тело в "черный ящик" в виде байтового массива.
	// Если bCompressed = true, данные будут сжаты.
	//
	virtual bool save3dPartToBytes(
		IN const mcsWorkID& idPart3dItem,
		OUT mcsByteArray&   rawData,
		IN OPTIONAL bool    bCompressed = true) = 0;

	// Метод восстанавливает ранее сохранённые объекты из байтового массива в указанный документ (idDocTo).
	// Если idDocTo = WID_NULL, объекты вставляются в активный поддокумент.
	// В массиве idsContents на выходе будут содержаться ID восстановленных объектов.
	//
	virtual bool restore3dPartFromBytes(
		IN const mcsByteArray&       rawData,
		OUT mcsWorkIDArray&          idsContents,
		IN OPTIONAL const mcsWorkID& idDocTo = WID_NULL) = 0;
};
//==============================================================================

struct IMc3dPart : public virtual IMc3dSolid
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dPart);

public:
	IMCS_QI_METHOD_DEFINITION(IMc3dPart, IMc3dSolid);

	virtual bool      isInEditMode() const = 0;
	virtual HRESULT   enterEditMode() = 0;
	virtual HRESULT   exitEditMode() = 0;

	// Возвращает виртуальный документ, представляющий состав детали
	virtual IMcDocumentPtr getModelDoc() = 0;
};
//==============================================================================

struct IMc3dAlienSolidData : public virtual IMc3dSolid
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dAlienSolidData);

public:

	IMCS_QI_METHOD_DEFINITION(IMc3dAlienSolidData, IMc3dSolid);

	virtual const GUID& getImplementID() {return IID_IMcDbEntity;}
	virtual const GUID& getClassID() const {return IID_IMc3dAlienSolidData;}

		// запоминает указанную матрицу трансформации в качестве новой обсолютной матрицы трансформации;
		// не инициирует события по факту изменения матрицы
	virtual HRESULT setTransform(const mcsMatrix3d& absTfm) { return E_NOTIMPL; }
};
//==============================================================================
struct IMc3dAlienSolid : public virtual IMc3dSolid
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dAlienSolid);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dAlienSolid, IMc3dSolid);

		// находит данные, ассоциированные с чужим солидом
	M3D_API virtual IMc3dAlienSolidDataPtr lokupAlienSolidData();

		// связывает с чужим солидом указанные данные
	virtual void setAlienSolidData(IMc3dAlienSolidData*) = 0;

		// создать объект-контейнер с данными для чужого солида
	virtual IMc3dAlienSolidDataPtr createAlienSolidData() = 0;

		// запоминает указанную матрицу трансформации в качестве новой обсолютной матрицы трансформации;
		// инициирует события по факту изменения матрицы
	virtual HRESULT setTransform(const mcsMatrix3d& absTfm) = 0;

		// Если это тело было построено как развертка листового тела, то позволяет узнать ID
		// соответствующей 3D фичи-создателя.
	virtual mcsWorkID getHostSmFlattenFeature() const = 0;

		// Метод устанавливает ID 3D фичи-развертки листового тела, создавшей это тело.
	virtual HRESULT setHostSmFlattenFeature(const mcsWorkID& idSmFlattenCreatorFeature) = 0;
};
//==============================================================================
// интерфейс наследуют все 3D объекты-фичи, которые позволяют пользователям работать с ними
// IMcFeatureEntity (пользовательский интерфейс) <-> IMdFeature (программный интерфейс)
struct IMcFeatureEntity : public virtual IMc3dSolid
{
public:
	mcsWorkID m_mdFeatureID; // идентификатор фичи в IMc3dBodyConstructor

protected:
	IMcFeatureEntity() {
		IMCS_REGISTER_THIS_IID_4KINDOF;
		m_mdFeatureID.setNull();
	}

public:

	virtual const GUID& getClassID() const {return __uuidof(IMcFeatureEntity);}
	IMCS_QI_METHOD_DEFINITION3(IMcFeatureEntity, IMc3dHistoryItem, IMc3dSolid);

	M3D_API virtual IMdFeaturePtr getBaseFeatureConstructor() const;

		// Выдаёт Faces/Edges/Vertices с фичи по указанному фильтру.
		// Фильтр тот же, что и в EntityMonitor
	virtual HRESULT       getFEV(OUT mcsWorkIDArray& idsFEV, DWORD dwFEVFilter = kMcsAllEntities) const = 0;

		// true, если фича является первой в цепочке фич солида. Т.е. независимо от
		// ассоциативных связей она задаёт начало новому телу;
		// если указан pBasePartSolid, то вернёт ID тела, к которому привязано данное
		// операцией NewBody
	virtual bool          doesStartNewBody(OUT OPTIONAL mcsWorkID* pBasePartSolid = NULL) const = 0;

		// Методы позволяют установить и получить солид, в который 
		// встраивается принудительно эта фича.
		// Выдаётся ID HostSolid, если при установке указать на вход дочерний солид,
		// то из него будет автоматически взят HostSolid
	virtual mcsWorkID     getTargetSolidID() const = 0;
	virtual HRESULT       setTargetSolidID(const mcsWorkID& idSolid) = 0;

		// Возвращает true, если фича модифицирует тело.
		// Есть фичи, которые фактически не меняют тело, а имеют лишь графическое отображение.
		// Например, резьба в упрощенном режиме построения.
	virtual bool doesChangeBody() const {
		return true;
	}

		// Если true, это значит, что изменился алгоритм генерации ref-ключей для Face/Edge/Vetex,
		// которые фича создаёт/меняет.
	virtual bool isRefKeyGenAlgoChanged() const
	{
		return false;
	}
};
//==============================================================================
enum m3dExtrudeParamExtTypeEnum
{
	kExtrudePrmExtType_PrmExtDist   = 40,
	//kExtrudePrmExtType_PrmExtTo     = 42,
	//kExtrudePrmExtType_PrmExtFromTo = 43,
	kExtrudePrmExtType_PrmExtAll    = 44,
	kExtrudePrmExtType_PrmExtSurf   = 45
};
//==============================================================================
struct IMc3dExtrudeFeature : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dExtrudeFeature);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dExtrudeFeature, IMcFeatureEntity);

	M3D_API virtual IMdExtrudeFeaturePtr getFeatureConstructor() const;
	M3D_API virtual IMcSketchProfilePtr  getProfile() const;

	virtual HRESULT   setProfileID(const mcsWorkID& idProfile) = 0;
	virtual mcsWorkID getProfileID() const = 0;

	virtual mcsWorkID getDist1ParamVarID() const = 0;
	virtual mcsWorkID getDist2ParamVarID() const = 0;
	virtual mcsWorkID getTaperAng1ParamVarID() const = 0;
	virtual mcsWorkID getTaperAng2ParamVarID() const = 0;

	virtual HRESULT   setEntToId(const mcsComplexWorkID& idSurface, m3dFeatureDistDirEnum distDir = kPositiveExtDir) = 0;
	virtual mcsComplexWorkID getEntToId(m3dFeatureDistDirEnum distDir = kPositiveExtDir) const = 0;

	virtual HRESULT getStartFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;
	virtual HRESULT getEndFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;
	virtual HRESULT getSideFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;

	virtual HRESULT setExtent(m3dExtrudeParamExtTypeEnum newExt, m3dFeatureDistDirEnum distDir = kPositiveExtDir) = 0;
	virtual m3dExtrudeParamExtTypeEnum  getExtent(m3dFeatureDistDirEnum distDir = kPositiveExtDir) const = 0;
};
//==============================================================================
enum m3dRevolveParamExtTypeEnum
{
	kRevolvePrmExtType_PrmExtFull = 40,
	kRevolvePrmExtType_PrmExtAngle = 41,
	//kRevolvePrmExtType_PrmExtTo = 42,
	//kRevolvePrmExtType_PrmExtFromTo = 43,
	kRevolvePrmExtType_PrmExtToSurf = 44,
};
//==============================================================================
struct IMc3dRevolveFeature : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dRevolveFeature);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dRevolveFeature, IMcFeatureEntity);

	M3D_API virtual IMdRevolveFeaturePtr getFeatureConstructor() const;
	M3D_API virtual IMcSketchProfilePtr  getProfile() const;

	virtual HRESULT   setProfileID(const mcsWorkID& idProfile) = 0;
	virtual mcsWorkID getProfileID() const = 0;

		// Устанавливает ось. Осью может быть рабочая ось, линия, ось окружности/эллипса,
		// линейное ребро солида, ось кольцевого ребра солида. Во всех этих случаях
		// из axisParam используется только поле id. Если ось задаёт сегмент полилинии,
		// то тогда поле rParam, определяет этот сегмент
	virtual HRESULT         setAxisParam(const McGeometryParam& axisParam) = 0;
	virtual McGeometryParam getAxisParam() const = 0;

	virtual mcsWorkID getRotAngParamVarID() const = 0;
	virtual mcsWorkID getRotAng2ParamVarID() const = 0;

	virtual HRESULT getStartFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;
	virtual HRESULT getEndFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;
	virtual HRESULT getSideFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;

	virtual HRESULT   setEntToId(const mcsComplexWorkID& idSurface, m3dFeatureDistDirEnum distDir = kPositiveExtDir) = 0;
	virtual mcsComplexWorkID getEntToId(m3dFeatureDistDirEnum distDir = kPositiveExtDir) const = 0;

	virtual m3dRevolveParamExtTypeEnum getExtent(m3dFeatureDistDirEnum distDir = kPositiveExtDir) const = 0;
	virtual HRESULT setExtent(m3dRevolveParamExtTypeEnum newExt, m3dFeatureDistDirEnum distDir = kPositiveExtDir) = 0;
};
//==============================================================================
enum Mc3dArrGetObjListModeEnum
{
	kMc3dArr_WholeSolidsOnly          = 0x01,
	kMc3dArr_ChildrenForWholeSolids   = 0x02,
	kMc3dArr_FeaturesOnly             = 0x04,

	kMc3dArr_WholeSolidsAndTheirChildren = kMc3dArr_WholeSolidsOnly | kMc3dArr_ChildrenForWholeSolids,
	kMc3dArr_WholeSolidsAndFeatures      = kMc3dArr_WholeSolidsOnly | kMc3dArr_FeaturesOnly,
	kMc3dArr_All                         = kMc3dArr_WholeSolidsOnly | kMc3dArr_ChildrenForWholeSolids | kMc3dArr_FeaturesOnly,
};
//==============================================================================
struct IMc3dArrFeatureType : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dArrFeatureType);

public:

	IMCS_QI_METHOD_DEFINITION(IMc3dArrFeatureType, IMcFeatureEntity);

		// Интерфейс позволяет управлять списком солидов-объектов
		// (наследников от IMc3dSolid), которые целиком включены, как элементы массива;
	virtual HRESULT arr_getObjectList(OUT mcsWorkIDArray& idsObjs, IN Mc3dArrGetObjListModeEnum mode) const = 0;
	virtual HRESULT arr_addObj(IN const mcsWorkID& idObj, bool fAddAsWholeSolid) = 0;
	virtual HRESULT arr_removeObj(IN const mcsWorkID& idObj, bool fLookupOnlyInWholeSolids) = 0;
	virtual HRESULT arr_clear(bool fClearWholeSolidsOnly) = 0;

		// возвращает true, если объект содержит в качестве элементов массива фичи из других объектов
	virtual bool arr_hasSubFeatureItems() const = 0;

		// возвращает true, если объект содержит в качестве элементов массива врезные 3D-стандартные объекты
	virtual bool arr_hasStdInpartItems() const = 0;

		// возвращает true, если объект содержит в качестве элементов массива целые солиды
	virtual bool arr_hasWholeSolidItems() const = 0;

		// Если указан pObj, то idObj не используется. Используется системно, не рекомендуется
		// для штатного использования
	virtual bool    arr_doesContainObj(IN const mcsWorkID& idObj, IN OPTIONAL IMcObject* pObj = NULL) const = 0;

		// методы позволяют получить объекты, которые используются в качестве источников элементов
		// массива; в дополнение к методам IMdCircPatFtr, IMdRectPatFtr и IMdMirrorFeature, позволяет
		// получить ID объектов, которые полностью включены как элемент массива (whole solid),
		// для таких элементов getSrcItem в параметре idMdFeature вернёт WID_NULL
	virtual int  arr_getSrcItemsCount() const = 0;
	virtual bool arr_getSrcItem(int idx, OUT mcsWorkID& idObj, OUT mcsWorkID& idMdFeature) const = 0;

		// Метод отдает параметрическую привязку к объекту, задающему i-ю размерность массива.
	virtual McGeometryParam arr_getDir(int iDim) const = 0;

		// Метод устанавливает параметрическую привязку к объекту, задающему i-ю размерность массива.
		//
		// Прямоугольный массив:
		//    Линейный примитив. WA, линейное ребро тела.
		//
		// Круговой массив:
		//    Устанавливает ось. Осью может быть рабочая ось, линия, ось окружности/эллипса,
		//    линейное ребро солида, ось кольцевого ребра солида. Во всех этих случаях
		//    из axisParam используется только поле id. Если ось задаёт сегмент полилинии,
		//    то тогда поле rParam, определяет этот сегмент
		//
		// Зеркальное отображение:
		//    Плоскость отражения. WPL, плоская грань тела
	virtual HRESULT arr_setDir(int iDim, const McGeometryParam& gp) = 0;

		// Устанавливает кол-во элементов вдоль i-й размерности массива.
	virtual HRESULT arr_setSize(int iDim, int n) = 0;

		// Возвращает кол-во элементов i-й размерности массива
	virtual int arr_getSize(int iDim) const = 0;

		// тип параметра массива
		// (1) не менять, пишется в файл
	enum SpacingMode
	{
		kFit   = 50, // диапазон
		kStep  = 51, // шаг
	};

		// Тип параметра i-й размерности массива - шаг/диапазон
	virtual SpacingMode arr_getFillingMode(int iDim) const = 0;

		// Устанавливает тип параметра i-й размерности массива - шаг/диапазон
	virtual HRESULT arr_setFillingMode(int iDim, SpacingMode newPrm1Mode, bool bRecalcParam) = 0;

		// Возвращает значение параметра i-й размерности массива.
		// Угловой массив - угол (только первое направление), "зеркало" - не применимо
	virtual double arr_getParam(int iDim) const = 0;

		// Устанавливает значение параметра i-й размерности массива.
		// Параметр ставится с учетом текущего режима - шаг/диапазон.
		// Угловой массив - угол (только первое направление), "зеркало" - не применимо
	virtual HRESULT arr_setParam(int iDim, double prm) = 0;

		// Возвращает признак инверсии направления i-й размерности массива относительно параметрической привязки
	virtual bool arr_isDirReversed(int iDim) const = 0;

		// Устанавливает признак инверсии направления i-й размерности массива относительно параметрической привязки
	virtual HRESULT arr_setDirReversed(int iDim, bool bRev) = 0;

		// ID переменной со значением параметра (шага/диапазона) i-й размерности массива
	virtual mcsWorkID arr_getParam_VarID(int iDim) const = 0;

		// ID переменной со значением кол-ва элементов вдоль i-й размерности массива
	virtual mcsWorkID arr_getCount_VarID(int iDim) const = 0;

		// Устанавливает ID переменной со значением параметра (шага/диапазона) i-й размерности массива
	virtual HRESULT arr_setParam_VarID(int iDim, const mcsWorkID& idVar) = 0;

		// Устанавливает ID переменной со значением кол-ва элементов i-й размерности массива
	virtual HRESULT arr_setCount_VarID(int iDim, const mcsWorkID& idVar) = 0;

		// Форсирует подсветку элемента массива с указанными индексами
		// Одновременно можно подсветить несколько элементов.
		// после установки подсветки элементов общий метод highlight(true) подразумевает
		// подсветку желаемых элементов, но не всего объекта целиком.
	virtual HRESULT arr_highlightElement(const mc3dArrIndex& idx) = 0;

		// Снимает подсветку всех элементов массива. Аналогично будет работать
		// общий метод highlight(false). После снятия подсветки со всех элементов
		// highlight(true) будет подсвечивать весь массив.
	virtual HRESULT arr_unhighlightAllElements() = 0;

	virtual bool    arr_getHighlightedElements(OUT mc3dArrIndices& indices) const = 0;

		// набор методов для управления подавлением отдельных элементов массива;
		// прим.: элемент (0,0) подавить нельзя
	virtual HRESULT arr_suppressElement(const mc3dArrIndex& idx) = 0;
	virtual HRESULT arr_unsuppressElement(const mc3dArrIndex& idx) = 0;
	virtual HRESULT arr_unsuppressAllElements() = 0;
	virtual bool    arr_isElementSuppressed(const mc3dArrIndex& idx) const = 0;
	virtual bool    arr_getSuppressedElements(OUT mc3dArrIndices& indices) const = 0;

		// Получить матрицу вставки указанного элемента
		// Матрица задана таким образом, чтобы исходный объект переместить в указанную позицию массива
	virtual bool arr_getItemTfm(const mc3dArrIndex& idx, OUT mcsMatrix& tfm) const = 0;
};

typedef IMc3dArrFeatureType IMc3dArrFeature;
//==============================================================================
struct IMc3dCircPatFeature : public virtual IMc3dArrFeatureType
{
	// dir1 - ось вращения
	// реверс первого направления - реверс оси
	// первый параметр - угол, в радианах

protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dCircPatFeature);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dCircPatFeature, IMc3dArrFeatureType);

	M3D_API virtual IMdCircularPatternFeaturePtr getFeatureConstructor() const;
};
//==============================================================================
struct IMc3dRectPatFeature : public virtual IMc3dArrFeatureType
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dRectPatFeature);

public:
	IMCS_STD_METHOD_DEFINITION(IMc3dRectPatFeature, IMc3dArrFeatureType);
	M3D_API virtual IMdRectangularPatternFeaturePtr getFeatureConstructor() const;
};
//==============================================================================
struct IMc3dMirrorFeature : public virtual IMc3dArrFeatureType
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dMirrorFeature);

public:
	IMCS_STD_METHOD_DEFINITION(IMc3dMirrorFeature, IMc3dArrFeatureType);
	M3D_API virtual IMdMirrorFeaturePtr getFeatureConstructor() const;

	virtual SpacingMode arr_getFillingMode(int iDim) const override                    { return kFit; }
	virtual HRESULT     arr_setFillingMode(int iDim, SpacingMode newPrm1Mode, bool bRecalcParam) override { return E_FAIL; }
	virtual double      arr_getParam(int iDim) const override                          { return UNKNOWNVALUE; }
	virtual HRESULT     arr_setParam(int iDim, double prm) override                    { return E_FAIL; }
	virtual mcsWorkID   arr_getParam_VarID(int iDim) const override                    { return WID_NULL; }
	virtual mcsWorkID   arr_getCount_VarID(int iDim) const override                    { return WID_NULL; }
	virtual HRESULT     arr_setParam_VarID(int iDim, const mcsWorkID& id) override     { return E_FAIL; }
	virtual HRESULT     arr_setCount_VarID(int iDim, const mcsWorkID& id) override     { return E_FAIL; }
	virtual bool        arr_isDirReversed(int iDim) const override                     { return false; }
	virtual HRESULT     arr_setDirReversed(int iDim, bool bRev) override               { return E_FAIL; }
};
//==============================================================================
enum m3dChamferTypeEnum
{
	kChamferType_None = 0,
	kChamferType_Distance,         // иногда по коду и комментариям проходит как DD
	kChamferType_DistanceAndAngle, // иногда по коду и комментариям проходит как DA
	kChamferType_TwoDistances,     // иногда по коду и комментариям проходит как D1D
	kChamferType_END // для проверки валидности диапазона
};
//..............................................................................
enum m3dChamferSetbackTypeEnum
{
	kChamferSetbackType_None = 0,
	kChamferSetbackType_Flat,
	kChamferSetbackType_END
};
//==============================================================================
struct IMc3dEdgeFeatureType : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dEdgeFeatureType);

public:
	IMCS_STD_METHOD_DEFINITION(IMc3dEdgeFeatureType, IMcFeatureEntity);

	// рёбра, на которых построена фаска
	virtual HRESULT setEdges(IN const mcsWorkIDArray& idsEdges) = 0;
	virtual HRESULT getEdges(OUT mcsWorkIDArray& idsEdges) const = 0;

	virtual HRESULT getEdgesStoredGeometry(OUT mapWID2MEG& edgeToGeom_wcs) const = 0;
};
//==============================================================================
struct IMc3dChamferFeature : public virtual IMc3dEdgeFeatureType
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dChamferFeature);
	IMCS_STD_METHOD_DEFINITION(IMc3dChamferFeature, IMc3dEdgeFeatureType);

	M3D_API virtual IMdChamferFeaturePtr getFeatureConstructor() const;
	
		// этот же метод зовётся для случая kChamferType_Distance
	virtual mcsWorkID getParamVarID_Dist1() const = 0;
	virtual mcsWorkID getParamVarID_Dist2() const = 0;
	virtual mcsWorkID getParamVarID_Angle() const = 0;

		// дистанция первая (она же единственная для DD)
	virtual HRESULT setDistance(const double rVal) = 0;
	virtual double  getDistance() const = 0;

		// дистанция вторая (только D1D)
	virtual HRESULT setDistance2(const double rVal) = 0;
	virtual double  getDistance2() const = 0;

		// угол фаски (только DA) (радианы)
	virtual HRESULT setAngle(const double rValRadians) = 0;
	virtual double  getAngle() const = 0;

		// тип фаски (см. выше)
	virtual HRESULT            setChamferType(m3dChamferTypeEnum eType) = 0;
	virtual m3dChamferTypeEnum getChamferType() const = 0;

		// тип сопряжения фасок (где сходится больше 2 рёбер с фасками)
	virtual HRESULT setChamferSetbackType(m3dChamferSetbackTypeEnum eType) = 0;
	virtual m3dChamferSetbackTypeEnum getChamferSetbackType() const = 0;

		// грань, от которой меряется угол
	virtual HRESULT   setFace(const mcsWorkID& idFace) = 0; // DA and D1D only
	virtual mcsWorkID getFace() const = 0; // DA and D1D only
};
//==============================================================================
struct IMc3dFilletFeature : public virtual IMc3dEdgeFeatureType
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dFilletFeature);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dFilletFeature, IMc3dEdgeFeatureType);

	M3D_API virtual IMdFilletFeaturePtr getFeatureConstructor() const;

		// переменная, содержащая радиус скругления
	virtual mcsWorkID getParamVarID_Radius() const = 0;

		// радиус скругления
	virtual HRESULT setRadius(const double rVal) = 0;
	virtual double  getRadius() const = 0;
};
//==============================================================================
struct IMc3dCoilFeature : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dCoilFeature);
public:
	IMCS_STD_METHOD_DEFINITION(IMc3dCoilFeature, IMcFeatureEntity);

	//M3D_API virtual IMdFeaturePtr getFeatureConstructor() const;
};
//==============================================================================
struct IMc3dRibFeature : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dRibFeature);
public:
	IMCS_STD_METHOD_DEFINITION(IMc3dRibFeature, IMcFeatureEntity);

	//M3D_API virtual IMdFeaturePtr getFeatureConstructor() const;
};
//==============================================================================
struct IMc3dShellFeature : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dShellFeature);
public:
	IMCS_STD_METHOD_DEFINITION(IMc3dShellFeature, IMcFeatureEntity);

	//M3D_API virtual IMdFeaturePtr getFeatureConstructor() const;
};
//==================================================================================================

enum McSweepProfileOrientationEnum
{
	kMcNormalToPath              = 0,
	kMcParallelToOriginalProfile = 1,

	kMcSweepProfileOrientationEnum_min = kMcNormalToPath,
	kMcSweepProfileOrientationEnum_max = kMcParallelToOriginalProfile,
};
//==================================================================================================

struct IMc3dSweepFeature : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSweepFeature);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dSweepFeature, IMcFeatureEntity);

	M3D_API virtual IMdExtrudeAlongPathFeaturePtr getFeatureConstructor() const;
	M3D_API virtual IMcSketchProfilePtr  getProfile() const;

	virtual HRESULT   setProfileID(const mcsWorkID& idProfile) = 0;
	virtual mcsWorkID getProfileID() const = 0;

	virtual mcsWorkID getTaperAngParamVarID() const = 0;

	// path global coords
	virtual HRESULT   setPath(IN const McGeometryParamArray& paramsGeoms) = 0;
	virtual HRESULT   getPath(OUT McsEntityGeometry* pGeomPathLocal = NULL, OUT McGeometryParamArray* pParamsGeoms = NULL) const = 0;

	virtual McSweepProfileOrientationEnum getProfileOrientation() const = 0;
	virtual HRESULT setProfileOrientation(const McSweepProfileOrientationEnum type) = 0;

	virtual HRESULT highlightPath() = 0;
	virtual HRESULT unhighlightPath() const = 0;

	virtual HRESULT getStartFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;
	virtual HRESULT getEndFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;
	virtual HRESULT getSideFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;
};
//==================================================================================================

enum McLoftConditionEnum
{
	kMcFreeLoftCondition,
	kMcMinLoftCondition = kMcFreeLoftCondition,
	kMcTangentLoftCondition,
	kMcSmoothLoftCondition,
	kMcSharpPointLoftCondition,
	kMcTangentToPlaneLoftCondition,
	kMcDirectionLoftCondition,
	kMcMaxLoftCondition = kMcDirectionLoftCondition
};
//--------------------------------------------------------------------------------------------------

enum McLoftTypeEnum
{
	kMcLoftTypeRegular,
	kMcLoftType_min = kMcLoftTypeRegular,
	kMcLoftTypeWithRails,
	kMcLoftTypeWithCenterLine,
	kMcLoftTypeWithAreaGraphSections, // на 2013-05-22 нет поддержки в моделере, так что не реализовано
	kMcLoftType_max = kMcLoftTypeWithAreaGraphSections,
};
//==================================================================================================

struct IMc3dLoftFeature : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dLoftFeature);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dLoftFeature, IMcFeatureEntity);

	M3D_API virtual IMdLoftFeaturePtr getFeatureConstructor() const;

		// базовый профиль лофта
	M3D_API virtual IMcSketchProfilePtr  getProfile() const;

		// установка и получение базового профиля
	virtual HRESULT   setProfileID(const mcsWorkID& idProfile) = 0;
	virtual mcsWorkID getProfileID() const = 0;

		// Количество сечений, включая базовый профиль
	virtual int       getSectionsCount() const = 0;

		// Удаляет сечение с указанным индексом, кроме первого его удалить нельзя,
		// оно является определяющим и управляется методами setProfileID/getProfileID
	virtual HRESULT   removeSection(int iSection) = 0;

		// Удаляет все сечения кроме первого, сбросить первое сечение можно методом setProfileID(WID_NULL).
	virtual HRESULT   removeSections() = 0;

		// Добавление сечения, начиная со второго, первое сечение задаётся методом setProfileID
	virtual HRESULT addSection(const mcsWorkID& idSketchProfile) = 0;

		// Установка i-го сечения. Вызов допустим для сечений, начиная со второго.
		// Для первого (нидекс 0) нужно исопльзовать метод setProfileID().
		// idSketchProfile не должен быть WID_NULL. Для удаления сечения используйте removeSection.
		// Устанавливаемый эскизный профиль должен быть в том же теле, что и Loft.
	virtual HRESULT setSection(IN int iSection, const mcsWorkID& idSketchProfile) = 0;

	virtual mcsWorkID getSection(IN int iSection) const = 0;

		// установка пути для типа kMcLoftTypeWithCenterLine
	virtual HRESULT         setPathParam(const McGeometryParam& pathParam) = 0;
	virtual McGeometryParam getPathParam() const = 0;

		// подсветки
	virtual HRESULT   highlightPath() = 0;
	virtual HRESULT   unhighlightPath() const = 0;

	virtual HRESULT   getHighlightedGuideRailIndices(OUT mcsIntArray& indices) = 0;
	virtual HRESULT   highlightGuideRail(IN const int idx) = 0;
	virtual HRESULT   unhighlightGuideRails() const = 0;

	virtual HRESULT   getHighlightedSectionIndices(OUT mcsIntArray& indices) = 0;
	virtual HRESULT   highlightSection(IN const int idx) = 0;
	virtual HRESULT   unhighlightSections() const = 0;

		// переменные для кондиции kMcDirectionLoftCondition
	virtual mcsWorkID getSectionFirstAngParamVarID() const = 0;
	virtual mcsWorkID getSectionLastAngParamVarID()  const = 0;

	virtual McLoftConditionEnum getLastSectionCondition() const = 0;
	virtual McLoftConditionEnum getFirstSectionCondition() const = 0;
	virtual HRESULT   setLastSectionCondition(IN const McLoftConditionEnum type) = 0;
	virtual HRESULT   setFirstSectionCondition(IN const McLoftConditionEnum type) = 0;

	// Углы при первом и последнем сечении.
	// Поддерживается не всеми ядрами (C3D не поддерживает)
	virtual double  getFirstSectionAngle() const = 0;
	virtual double  getLastSectionAngle() const = 0;
	virtual HRESULT setFirstSectionAngle(double dRadians) = 0;
	virtual HRESULT setLastSectionAngle(double dRadians) = 0;

	// Веса первого и последнего сечений.
	// Поддерживается не всеми ядрами (C3D не поддерживает)
	virtual double  getFirstSectionWeight() const = 0;
	virtual double  getLastSectionWeight() const = 0;
	virtual HRESULT setFirstSectionWeight(double dWeight) = 0;
	virtual HRESULT setLastSectionWeight(double dWeight) = 0;

	virtual bool      isClosed() const = 0;
	virtual HRESULT   setClosed(IN const bool bClosed) = 0;

	// Направляющие кривые для типа kMcLoftTypeWithRails
	virtual int       getGuideRailsCount() const = 0;
	virtual HRESULT   getGuideRailsParams(OUT McGeometryParamArray& paramsRails, IN int iRail) const = 0;

	// Установка набора геометрий (через геометрические привязки) в качестве направляющей кривой с индексом idx.
	// Если idx вне диапазона индексов массива (например отрицательный), то paramsRails добавляются
	// в конец в качестве новой направляющей кривой, иначе перетирают существующую.
	// Если массив paramsRails пустой, а idx попадает в диапазон индексов массива имеющихся
	// направляющих кривых, направляющая кривая с этим индексом удаляется.
	virtual HRESULT   setGuideRailsParams(IN const McGeometryParamArray& paramsRails, IN int iRail = -1) = 0;

	virtual HRESULT   removeGuideRails() = 0;
	virtual HRESULT   removeGuideRail(int iRail) = 0;

	virtual McLoftTypeEnum getLoftType() const = 0;

	// для типа kMcLoftTypeWithRails не нужен путь, так что при установке этого типа путь будет сброшен.
	// для типа kMcLoftTypeWithCenterLine не нужны направляющие кривые, будут сброшены
	virtual HRESULT   setLoftType(IN const McLoftTypeEnum loftType) = 0;

	virtual HRESULT   getStartFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;
	virtual HRESULT   getEndFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;
	virtual HRESULT   getSideFEV(OUT mcsWorkIDArray& idsStartFEV, DWORD dwFEVFilter = kMcsSurfaceEntities) const = 0;
};
//==================================================================================================

struct IMc3dBooleanFeature : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dBooleanFeature);

public:
	IMCS_STD_METHOD_DEFINITION(IMc3dBooleanFeature, IMcFeatureEntity);

	M3D_API virtual IMdBooleanFeaturePtr getFeatureConstructor() const;

	virtual HRESULT setOperation(MdPartFeatureOperationEnum operType) = 0;
	virtual MdPartFeatureOperationEnum getOperation() const = 0;

		// Первый элемент - это тело, к которому будет что-то добавляться
		// ..из которого что-то будет вычитаться
		// .. с которым будет что-то пересекаться
		// Допустимо устанавливать только 3D тело либо вставку блока с 3D-телами внутри.
		// Если булевой фиче назначается 3D тело, то операция может быть выполнена только при условии,
		// что от этой булевой фичи ничего не зависит (ничего не привязано к её геометрии).

	virtual HRESULT   set1stItem(IN const mcsWorkID& id1stItem, bool bTryOnly) = 0;
	virtual mcsWorkID get1stItem() const = 0;

		// Работа с элементами булевой фичи.
		// элементами могут быть тела уроаня сборки, блоки с телами

	virtual HRESULT getOtherItems(OUT mcsWorkIDArray& idsItems) const = 0;
	virtual HRESULT setOtherItems(IN const mcsWorkIDArray& idsItems) = 0;

	virtual HRESULT addOtherItem(IN const mcsWorkID& idItem, bool bTryOnly) = 0;
	virtual HRESULT removeOtherItem(IN const mcsWorkID& idItem) = 0;
	virtual bool    hasOtherItem(IN const mcsWorkID& idItem) = 0;

		// Метод позволяет определить факт наличия циклической зависимости между объектами в случае,
		// если будет создана булева с указанным первым и другими элементами.
		// Если указан pProblematicOtherId, то в случае наличия циклической зависимости 
		// поместит туда ID одного из элементов в idsOtherItems, для которого такая зависимость
		// имеет место быть.
	MCTYP_API static bool hasCylicDependencyFor1stAndOtherItems(
		const mcsWorkID&        id1stItem,
		const mcsWorkIDArray&   idsOtherItems,
		OUT OPTIONAL mcsWorkID* pProblematicOtherId = NULL);
};
//==================================================================================================

enum MCS_THREAD_STANDARD
{
	TS_ANSI = 0,
	TS_ISO = 1,
	TS_GOST_METRIC = 2,    // Метрическая
	TS_GOST_PIPE = 3,      // Трубная
	TS_GOST_TRAPEZE = 4,   // Трапецеидальная
	TS_GOST_BUTTRESS = 5,   // Упорная
	TS_OST_METRIC_RADIUS = 6   // Метрическая радиусная
};
//==================================================================================================
struct IMc3dThreadFeature : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dThreadFeature);

public:
	IMCS_STD_METHOD_DEFINITION(IMc3dThreadFeature, IMcFeatureEntity);

	M3D_API virtual IMdThreadFeaturePtr getFeatureConstructor() const;

		// ID цилиндрической поверхности, на которую ставится резьба
	virtual mcsWorkID getThreadFaceId() const = 0;

		// Метод устанавливает поверхность, на которой будет размещаться резьба.
		// (!) NOTE: Резьба автоматически добавляется в документ к нужному объекту-телу.
		// Если новая устанавливаемая грань относится к другому телу,
		// резьба автоматически будет перенесена в документе в нужное тело.
		//
		// pThreadFaceIds - id граней на которых строится резьба.
		// bJustSetID - если true, просто обновляет поле ID внутри, для системных целей
		// bAddToDocument - если false, резьба вне документа
	virtual HRESULT   setThreadFaceId(
		IN const mcsWorkID& id,
		IN OPTIONAL mcsWorkIDArray* pThreadFaceIds = NULL,
		IN OPTIONAL bool bJustSetID = false,
		IN OPTIONAL bool bAddToDocument = true) = 0;

		// ID ребра, от которой измеряется длина/глубина резьбы.
	virtual mcsWorkID getFrontEdgeId() const = 0;
	virtual HRESULT   setFrontEdgeId(IN const mcsWorkID& id) = 0;

		// ID конических фасок-поверхностей в начале и конце резьбы соответственно
	virtual mcsWorkID getChamferFaceIdAtStart() const = 0;
	virtual mcsWorkID getChamferFaceIdAtEnd() const = 0;

	virtual MCS_THREAD_STANDARD getThreadStandard() const = 0;
	virtual void setThreadStandard(IN MCS_THREAD_STANDARD newTs) = 0;

		// Обозначение, вроде M15x1.5
	virtual McsString getDesignation() const = 0;

		// Шаг резьбы
	virtual double    getPitch() const = 0;
	virtual McsString getPitchString() const = 0;

		// Метод устанавливает шаг резьбы.
		// Если bCheckValidLimits = true, выполняется проверка допустимости значения.
		// И если оно не совпадает с допустимыми табличными данными для текущего стандарта и размера,
		// оно будет автоматически заменено на ближайшее допустимое значение.
	virtual bool setPitch(IN double pitch, bool bCheckValidLimits = true) = 0;

		// Длина резьбы
	virtual double getLength(bool bCheckValidLimits = true) const = 0;

		// Метод устанавливает длину резьбы.
		// Если bCheckValidLimits = true, выполняется проверка границ допустимого значения длины.
		// И если новое значение выходит за границы, оно будет автоматически приведено
		// в допустимый диапазон.
	virtual bool   setLength(IN double value, bool bCheckValidLimits = true) = 0;

		// если true, резьба полностью покрывает поверхность ThreadFaceId
	virtual bool isFullLength() const = 0;
	virtual void setIsFullLength(IN bool value) = 0;

		// Метод позволяет определить направление витков резьбы
	virtual bool isRight() const = 0;
	virtual void setIsRight(IN bool value) = 0;

		// Внутренняя/внешняя резьба
	virtual bool isInternal() const = 0;
	virtual void setIsInternal(IN bool value) = 0;

		// min/max диаметры витков резьбы
	virtual double getMinDiameter() const = 0;
	virtual double getMaxDiameter() const = 0;

		// Начальная и конечная точка, лежащие в основаниях цилиндра, на котором строится резьба.
		// Ось цилиндра проходит через эти точки.
		// Если bResInGCS = true, результат возвращается в ГСК.
	virtual mcsPoint getStartPoint(bool bResInGCS = true) const = 0;
	virtual mcsPoint getEndPoint(bool bResInGCS = true) const = 0;

		// результат true, если резьба относится к 3D-детали, вставленной из DB (3D-болт, например)
	M3D_API virtual bool relatesToStdPart() const;

		// ID переменной, задающей длину резьбы
	virtual mcsWorkID getLengthVarID() const = 0;

		// ID переменной, задающей шаг резьбы
	virtual mcsWorkID getPitchVarID() const = 0;
};
//==================================================================================================

// Фича, с пользовательской низкоуровневой реализацией.
// Используется для подключения фич, реализованных в C# коде.

struct IMcCustomExternalFeature : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcCustomExternalFeature);

public:
	IMCS_STD_METHOD_DEFINITION(IMcCustomExternalFeature, IMcFeatureEntity);

	M3D_API virtual IMdCustomExternalFeaturePtr getFeatureConstructor() const;

		// Метод должен построить тело фичи в указанной модели.
		// В момент построения модель находится в ГСК.
		// К локальным построениям нужно применять матрицу трансформации объекта.
		// pTarget3dModel_wcs - Модель, куда нужно выполнить построение фичи.
		// pRes3dModel_wcs - Модель-результат, может совпадать с pTarget3dModel_wcs, это зависит от типа фичи.
	virtual HRESULT   buildFeature3dModel(IN INT_PTR pTarget3dModel_wcs, OUT INT_PTR& pRes3dModel_wcs) = 0;

		// Метод должен вернуть системное имя фичи. Используется, например, в системных логах
	virtual McsString _getSystemName() = 0;
};
//==================================================================================================

// Сторона объема сечения
// Значения не менять, пишутся в файл (!).
// Значения есть индексы в массиве плоскостей, которые возвращает функция
// mcGate_getBoundarySectionPlanes для объекта-сечения.

enum Mc3dSectionVolumeSideEnum
{
	kMc3dSecSide_Unknown = -1,
	kMc3dSecSide_Front   =  0,
	kMc3dSecSide_Right   =  1,
	kMc3dSecSide_Back    =  2,
	kMc3dSecSide_Left    =  3,
	kMc3dSecSide_Top     =  4,
	kMc3dSecSide_Bottom  =  5
};
//==================================================================================================

// Контур дополнительной выемки для объемных сечений
struct Mc3dSectionNotchContour
{
	Mc3dSectionVolumeSideEnum mSide;     // сторона выреза
	mcsPolyline               mLoop_wcs; // замкнутый контур выреза
	double                    mDepth;    // глубина выреза (положительно внутрь объема сечения)

	Mc3dSectionNotchContour()
	{
		mSide = kMc3dSecSide_Unknown;
		mDepth = 0;
	}

	MCFLATTEN_API bool operator == (const Mc3dSectionNotchContour&) const;

	bool operator != (const Mc3dSectionNotchContour& other) const
		{ return !operator== (other); }

	MCFLATTEN_API void transformBy(const mcsMatrix& tfm);

	MCFLATTEN_API HRESULT write(IMcsStream* pS) const;
	MCFLATTEN_API HRESULT read(IMcsStream* pS);
};
//==================================================================================================

struct Mc3dSectionNotchContoursArr : McsArray<Mc3dSectionNotchContour>
{
	MCFLATTEN_API void transformBy(const mcsMatrix& tfm);
	MCFLATTEN_API HRESULT write(IMcsStream* pS) const;
	MCFLATTEN_API HRESULT read(IMcsStream* pS);
};
//==================================================================================================

struct IMc3dSection : public virtual IMc3dHistoryItem
{
	enum SectionState
	{
		kUndefined = 0x00,
		kPlane =     0x01,
		kBoundary =  0x02,
		kVolume =    0x04
	};

	enum HeightType
	{
		kHeightAboveSectionLine = 0x01,
		kHeightBelowSectionLine = 0x02
	};

protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSection);

public:

	IMCS_STD_METHOD_DEFINITION(IMc3dSection, IMc3dHistoryItem);

		// ID рабочей плоскости, задающей фронтальную (первую) плоскость отреза.
	virtual mcsWorkID getAssocPlanarObject() const = 0;

		// Устанавливает планарный объект, определяющий фронтальную (первую) плоскость отреза.
	virtual HRESULT setAssocPlanarObject(IN const mcsWorkID& assocObjectId) = 0;

		// Возвращает связанные с сечением виды
	virtual HRESULT getViews(OUT mcsWorkIDArray& idsViews) const = 0;

		// Тип сечения (одна плоскость/4 плоскости/объём (6 плоскостей)).
	virtual SectionState state() const = 0;
	virtual HRESULT      setState(IN SectionState state) = 0;

		// Высоту и глубину до верхней и нижней плоскости отреза, для объемного типа.
		// kHeightAboveSectionLine - от линии сечения до верхней плоскости сечения (выше линии сечения).
		// kHeightBelowSectionLine - от линии сечения до нижней плоскости сечения (ниже линии сечения).
	virtual double  height(IN HeightType heightType) const = 0;
	virtual HRESULT setHeight(IN HeightType heightType, IN double height) = 0;

		// Расстояние отсечения - до дальней плоскости отреза(для типа по 4 и 6 плоскостям).
	virtual double  depth() const = 0;
	virtual HRESULT setDepth(IN double depth) = 0;

		// Точки, определяющие боковые плоскости сечения.
		// Для типа kPlane должно быть две точки. Они определяют линию плоскости отреза с нормалью -viewingDirection().
		// Для типов kBoundary и kVolume точек должно быть 4. Точки определяют прямоугольник, чьи стороны задают
		// линии боковые отреза. В частности точки 0 и 1 - определяют фронтальную/первую плоскость отреза, точки
		// 2 и 3-я точки определяют заднюю плоскость отреза (параллельную фронтальной) с нормалью viewingDirection().
		// В случае 4-х точек, направление от точки 1 к точке 2 задает направление viewingDirection().
		// А плоскость, в которой лежат эти 4 точки при обходе против часовой стрелке от 0 к 3-й задают
		// вертикальное направление (нормаль плоскости, в которой лежит сечение).
		// Важно! Для корректной инициализации сечения нужно задать сначала вершины, затем соответствующие им
		// направление viewingDirection, а также вертикальное направление verticalDirection.
	virtual void    getVertices(OUT mcsPoint3dArray& pts) const = 0;
	virtual HRESULT setVertices(IN const mcsPoint3dArray& pts) = 0;

		// Направление сечения (нормаль фронтальной (первой) плоскости отреза)
	virtual mcsVector viewingDirection() const = 0;
	virtual HRESULT   setViewingDirection(IN const mcsVector& vDir) = 0;

		// Вертикальное направление.
		// Это нормаль плоскости, в которой лежат точки сечения, возвращаемые getVertices().
		// Если сечение лежит в плоскости XY, вертикальное направление - это ось Z.
	virtual mcsVector verticalDirection() const = 0;
	virtual HRESULT   setVerticalDirection(IN const mcsVector& vUpDir) = 0;

		// Включение/выключение псевдоразреза.
		// В документе может быть только один включенный псевдоразрез.
		// Все 3D объекты будут отображаться так, будто они порезаны этим сечением.
	virtual void enableLiveSection(IN bool bEnable) = 0;
	virtual bool isLiveSectionEnabled() const = 0;

		// Метод устанавливает точки ломаной линии, задающей ломаную фронтальную плоскость сечения.
		// Точки должны лежать в плоскости, перпендикулярной базовой фронтальной плоскости сечения.
		// Первая и последняя точки массива pts должны совпадать с первой и второй точкой (соответственно)
		// массива, возвращаемого методом getVertices.
		// Все точки должны быть упорядочены и задавать ломаную линию.
		// (проекцию ломаной плоскости на плоскость контура точек из getVertices).
	virtual bool setFrontSectionLinePoints(IN const mcsPoint3dArray& pts_wcs) = 0;
	virtual bool getFrontSectionLinePoints(OUT mcsPoint3dArray& pts_wcs) const = 0;
	virtual int  numAdditionalPointsOnFrontLine() const = 0;

		// Методы управления контурами дополнительных вырезов
		// Контур размещается на стороне сечения. Если соответствующая грань сечения существует,
		// то вырез будет применяться.
	virtual bool addNotchContour(const Mc3dSectionNotchContour& contour_wcs) = 0;
	virtual bool getNotchContours(OUT Mc3dSectionNotchContoursArr& contours_wcs) const = 0;
	virtual int  setNotchContours(IN const Mc3dSectionNotchContoursArr& contours_wcs) = 0; // возвращает кол-во успешно добавленных контуров
	virtual int  numNotchContours() const = 0;

		// Возвращает массив объектов для сечения/проецирования.
		// Набор зависит от текущей конфигурации сечения.
	virtual bool get3dEntsForProcessing(OUT mcsComplexWorkIDArray& cids) = 0;
};
//==================================================================================================

struct IMcProjViewExDataProvider
{
	// Метод позволяет выполнить запрос тела для объекта перед построением проекции.
	// Возвращаемый солид должен лежать в той же системе координат, что и исходный объект 'pvOdDbStub_objFor'.
	// Возвращаемый солид изменению не подлежит.
	// 
	// Пример вызова:
	// 
	//   OdDbObjectId idObjToProj;
	//   const OdDb3dSolid* pSustSolid = NULL;
	//   IMcProjViewExDataProvider* pDP = getProvider();
	//   pDP->queryObjectSolid((OdDbStub*)idObjToProj, (void**)&pSustSolid);
	//
	virtual bool queryObjectSolid(void* pvOdDbStub_objFor, OUT void** ppvOdDb3dSolid_lcs) = 0;
};
//==================================================================================================

struct IMc3dDrawingView : public virtual IMc3dHistoryItem
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dDrawingView);

public:

	// (!) значения менять нельзя, пишутся в файл
	enum ViewDirectionType
	{
		kViewNone = -1,
		kViewFront = 0,
		kViewCurrent,
		kViewTop,
		kViewBottom,
		kViewLeft,
		kViewRight,
		kViewBack,
		kViewIsoTopRight,
		kViewIsoTopLeft,
		kViewIsoBottomRight,
		kViewIsoBottomLeft 
	};

	IMCS_STD_METHOD_DEFINITION(IMc3dDrawingView, IMc3dHistoryItem);

		// если вид связан с сечением, то его можно получить тут
	virtual mcsWorkID getSectionID() const = 0;
	virtual HRESULT   setSectionID(const mcsWorkID& idSection) = 0;

		// Возвращает документ, из пространства которого выполняется проекция объектов.
	virtual mcsWorkID getProjectingSpaceDocID() const = 0;

		// Получить/установить список объектов (IDs), участвующих в проекции/резке:
		// 3D солиды; поверхности; сети; вставки блоков; кривые; любой объект, рисующийся с помощью mesh/shell.
	virtual HRESULT   get3dEntsInView(OUT mcsComplexWorkIDArray& ids3dEnts) const = 0;
	virtual void      set3dEntsIds(IN const mcsComplexWorkIDArray& ents3dIds, bool bUpdateReactorsNow = true) = 0;

		// Возвращает список ID тел, попавших в разрез (без повторения).
		// Одно тело может попадать в разрез несколько раз через разные вставки блоков.
	virtual HRESULT  getSliced3dEntsIds(OUT mcsWorkIDArray& sliced3dEntsIds) const = 0;

		// Плоскость расположения вида.
		// Эта плоскость в сумме с собственным углом поворота определяет матрицу, возвращаемую методом getTfm().
		// Например, для видов, расположенных в мировой плоскости XY эта плоскость должна быть =
		// = XY со смещением в нужную точку.
	virtual void            setViewPlane(IN const mcsPlane& newPlane_wcs) = 0;
	virtual const mcsPlane& getViewPlane_wcs() const = 0;

		// Логическая ориентация вида относительно плоскости проекции, которую возвращает метод getProjPlane().
		// Если ориентация фронтальная, то реальная плоскость проецирования совпадает getProjPlane().
	virtual ViewDirectionType getDirectionType() const = 0;
	virtual void              setDirectionType(IN ViewDirectionType direction) = 0;

		// Получить родительский вид
	virtual const mcsWorkID& getParentViewId() const = 0;

		// Установка родительского вида.
		// NOTE: к родительскому при этом нужно явно добавить вид, как дочерний
	virtual void setParentViewId(IN const mcsWorkID& idParentView) = 0;

		// Возвращает ID самого первого родительского вида для этого
	virtual mcsWorkID rootViewID() const = 0;

		// список дочерних видов
	virtual const mcsWorkIDArray& getChildViews() const = 0;

		// Добавить дочерний вид.
		// При этом дочернему нужно явно выставить родителя
	virtual void appendChild(IN const mcsWorkID& childId) = 0;

		// Удалить дочерний вид.
		// При этом у дочернего нужно явно убрать родителя
	virtual void removeChild(IN const mcsWorkID& childId) = 0;

		// признак того, что положение этого вида должно выравниваться относительно родительского.
	virtual void setAlignOnParent(IN bool alignOnParent) = 0;
	virtual bool isAlignOnParent() const = 0;

		// Положение плоскости проекции/разреза в пространстве.
		// Именно на эту плоскость в сумме с ориентацией getDirectionType() выполняется проецирование.
		// Для разрезов этой плоскостью выполняется резка.
	virtual bool     setProjPlane(IN const mcsPlane& projPlane) = 0;
	virtual mcsPlane getProjPlane() const = 0;

		// Установка признака того, что вид является разрезом
	virtual void setSection(bool section) = 0;

		// true, если объект есть именно разрез, не сечение
	virtual bool isSlice() const = 0;

		// true, если вид построен от сечения (как родительский, так и его потомки, но не разрезы)
	virtual bool isBasedOnSection() const = 0;

		// true, если вид зависит от разреза
	virtual bool dependsOnSlice() const = 0;

		// Имеет смысл только если вид зависит от разреза, dependsOnSlice() = true
		// true = использовать результат родительского разреза,
		// false = использовать оригинальные 3D объекты.
	virtual bool useSectionedModels() const = 0;
	virtual void setUseSectionedModels(bool bUseSec3dObjects) = 0;

		// true, если это родительский вид от сечения
	virtual bool isRootSectionView() const = 0;

		// Признак автоматического обновления вида.
	virtual bool isAutoUpdateEnabled() const = 0;
	virtual void setEnableAutoUpdate(IN bool bEnableAutoUpdate) = 0;

		// Метод позволяет ID спроецированного объекта по маркеру на спроецированной геометрии
	virtual mcsComplexWorkID getProjectedObjectByGsm(IN McGSMarker gsm) const = 0;

		// Работа с 2D-обрывами
	virtual bool attach2dBreakObject(const mcsWorkID& idBreak) = 0;
	virtual bool detach2dBreakObject(const mcsWorkID& idBreak) = 0;
	virtual void getAttached2dBreakObjects(OUT mcsWorkIDArray& idsBreaks) const = 0;

		// Возвращает геометрию вида с возможностью указания,
		// сколько присоединённых 2D-обрывов применить (INT_MAX - все).
		// Если bApplyViewTfm = true, результат будет в ГСК, иначе в ЛСК вида.
	virtual bool getViewGeometry(OUT mcsGeomEntArray& geArr, bool bApplyViewTfm, int n2dBreaksToApply) = 0;

		// Признак видимости невидимых линий
	virtual bool showInvisibleLines() const = 0;
	virtual void setShowInvisibleLines(bool bShow) = 0;

		// Признак видимости штриховок на сечениях
	virtual bool showHatches() const = 0;
	virtual void setShowHatches(bool bShow) = 0;

		// центральная точка ограничивающего параллелепипеда для пересекаемых 3D примитивов.
	virtual const mcsPoint& get3dEntsCenterPoint() const = 0;

		// Работа с местными разрезами
	virtual bool attachLocalCut(const mcsWorkID& idSketch) = 0;
	virtual bool detachLocalCut(const mcsWorkID& idSketch) = 0;
	virtual void getAttachedLocalCuts(OUT mcsWorkIDArray& idSketches) const = 0;
	virtual bool hasLocalCuts() const = 0;

		// Метод возвращает плоскость проекции для указанного направления относительно плоскости проекции this-вида.
	virtual void getProjPlaneForSpecDirection(ViewDirectionType eDir, OUT mcsPlane& dirProjPlane) const = 0;

		// При включенном режиме предпросмотра вид показывает только рамку, ограничивающую проекцию
	virtual void setPreviewMode(bool bPreviewModeOn) = 0;
	virtual bool isPreviewModeOn() const = 0;

		// Признак того, что плоскость проекции будет вычисляться автоматически на основании направления проекции.
		// Применимо только к дочерним вспомогательным видам, которые не являются разрезами.
		// По умолчанию включено.
	virtual void setAutoCalcProjPlaneByViewDirection(bool bAutoCalcProjPlane) = 0;
	virtual bool isOnAutoCalcProjPlaneByViewDirection() const = 0;
};
//==================================================================================================

// Интерфейс для работы с проекциями на multiview-технологии
struct IMcHlrEngine2 : public IMc3dDrawingView
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcHlrEngine2);
	IMCS_QI_METHOD_DEFINITION(IMcHlrEngine2, IMc3dDrawingView);

public:
	// Установка режима использования в multiview-проекциях.
	// Нужно инициализировать сразу после создания, и затем не менять его.
	// По умолчанию выключен.
	virtual bool setMultiviewMode(bool bOn) = 0;
	virtual bool multiviewMode() const = 0;

	// Методы для сериализации объекта в DWG-поток.
	// Типы данных указаны в именах аргументов, использованы имена типов данных под Нанокадом
	virtual void dwgOutFields(void* pvOdDbDwgFiler) const = 0;
	virtual bool dwgInFields(void* pvOdDbObject_readingObj, void* pvOdDbDwgFiler) = 0;

	// Методы управления дополнительными пользовательскими примитивами для проецирования.
	// Объекты не сериализуются "проектором".
	virtual bool addCustomProjEnt(const mcsWorkID& id, Od3dEntForProjPtr pProjEnt) = 0;
	virtual bool removeCustomProjEnt(const mcsWorkID& id) = 0;
	virtual bool removeAllCustomProjEnts() = 0;
	virtual void setShowCustomObjectsProj(bool bShow) = 0;
	virtual bool showCustomObjectsProj() const = 0;

	// Добавить/удалить объекты для проекции.
	virtual bool add3dEnt(IN const mcsComplexWorkID& id3dEnt) = 0;
	virtual int  add3dEnts(IN const mcsComplexWorkIDArray& id3dEnts) = 0;
	virtual bool remove3dEnt(IN const mcsComplexWorkID& id3dEnt) = 0;
	virtual int  remove3dEnts(IN const mcsComplexWorkIDArray& id3dEnts) = 0;

	// Проверяет, включен ли указанный объект в проекцию.
	virtual bool contains3dEnt(IN const mcsComplexWorkID& id3dEnt) const = 0;

	// Установка положения передней и задней секущих плоскостей.
	// Знаковое расстояние отсчитывается от getProjPlane().
	// Фронтальная плоскость находится на положительной стороне проекционной плоскости.
	// значения по умолчанию отключают секущие плоскости.
	//
	virtual bool   setFrontSectionPlane(double dist = DBL_MAX) = 0;
	virtual bool   setBackSectionPlane(double dist = -DBL_MAX) = 0;
	virtual double getFrontSectionPlaneDist() const = 0;
	virtual double getBackSectionPlaneDist() const = 0;

	// Установка/получение солида, задающего объём сечения.
	// Если нужны какие-то вырезы особой формы, то это нужно делать как раз в этом солиде.
	// Для применения, например, сечения:
	// - визуальной призмой,
	// - с ломаной фронтальной плоскостью,
	// - с доп. вырезами на сторонах секущего объёма.
	//
	// Солид должен быть задан по месту в мировых координатах.
	// Если проекционная плоскость меняет своё положение, вызывающая сторона должна сама
	// скорректировать положение солида-сечения.
	// Тип данных: Нанокад - OdDb3dSolid
	//
	virtual bool  setCustomSectionVolume(void* pvXx3dSectionSolid_wcs) = 0;
	virtual void* getCustomSectionVolume() const = 0;

	// Метод отдаёт минимальную/максимальную точки ортогонального ограничивающего бокса для
	// всех проецируемых примитивов, в т.ч. пользовательских (тех, что вне документа).
	// Может быть полезно при подготовке солида, задающего пользовательский объем сечения,
	// чтобы можно было с нужных сторон оставить такой отступ, чтобы не было отсечения.
	// Координаты возвращаются в ГСК.
	virtual bool getContaningEntsOrthoBounds(OUT mcsPoint& minPt_wcs, OUT mcsPoint& maxPt_wcs) const = 0;

	// Метод возвращает проекционную геометрию указанного объекта (в СК вида).
	// Если указан ID вставки блока, вернёт всю спроецированную графику вставки блока.
	virtual bool getProjectedGeometry(
		const mcsComplexWorkID&                id,
		OUT mcsMatrix&                         tfmV2W, // матрица преобразования геометрии из СК вида в ГСК
		OUT OPTIONAL mcsEntityGeometryCPtrArr* pProjGeomPtrs_visible_vcs = NULL,
		OUT OPTIONAL mcsEntityGeometryCPtrArr* pProjGeomPtrs_invisible_vcs = NULL) const = 0;

	// Вспомогательный метод для рисования mcs-геометрии в OgGi-контекст (объект типа OdGiWorldDraw*).
	// Метод выполняет только рисование геометрии, никакие атрибуты вроде цвета и т.п. не выставляет.
	virtual bool drawMcsGeom(
		const McsEntityGeometry* pGeom,
		void*                    pvOdGiWorldDraw, 
		void*                    pvOdDbDatabase,
		int                      gsMarker = -1) const = 0; // -1 = взять маркер с геометрии pGeom

	// Методы получения доп. данных для построения проекций.
	// Провайдер не сериализуется "проектором".
	virtual bool                       setProjExDataProvider(IMcProjViewExDataProvider* pEDP) = 0;
	virtual IMcProjViewExDataProvider* getProjExDataProvider() const = 0;

	// Метод возвращает геометрию указанного маркером спроецированного примитива.
	// Геометрия возвращается в локальных координатах вида.
	virtual const McsEntityGeometry* getGeomByGsm_lcs(McGSMarker gsm) const = 0;

	// Метод возвращает исходный маркер спроецированного примитива по маркеру его проекции.
	virtual McGSMarker getSrcGsm(McGSMarker gsm) const = 0;

	// Метод возвращает ID исходного объекта по маркеру его проекции.
	virtual mcsComplexWorkID getProjectedObjectByGsm(IN McGSMarker gsm) const = 0;

	// Метод возвращает ref-ключ для Face/Edge/Vertex, на чью проекцию ссылается данный маркер.
	virtual const McFEVRefKey* getRefKeyByGsm(McGSMarker gsm) const = 0;
};
//==================================================================================================

enum BreakTypes : int
{
	Linear = 0,
	Curved = 1
};

struct IMc3dDrawingViewBreak : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dDrawingViewBreak);
	IMCS_QI_METHOD_DEFINITION(IMc3dDrawingViewBreak, IMcObject);//IMcFeatureEntity);

	virtual BreakTypes	getBreakType() const = 0;
	virtual mcsWorkID	getTargetDrawingView() const = 0;
	virtual double		getGapBetweenLines() const = 0;
	virtual bool		setTargetDrawingView(const mcsWorkID& idDV) = 0;
	virtual bool		setGapBetweenLines(const double& gapBetweenLines) = 0;
	virtual bool		setBreakType(const BreakTypes& brType) = 0;
	virtual bool		setPointsBreakLines(const mcsPoint3dArray& points) = 0;
};
//==================================================================================================

__inline bool mcsCutGeometryByDrawingViewBreaks_dyn(
	const mcsWorkID*        pIdsDvBreaks,
	int                     nBreaks,
	IN OUT mcsGeomEntArray& geArr)
{
	static FARPROC ls_proc = (FARPROC)-1;
	if(ls_proc == (FARPROC)-1)
	{
		ls_proc = NULL;
		if(HMODULE hMgd = GetModuleHandleA("mapimgd.dll"))
			ls_proc = GetProcAddress(hMgd, "mcsCutGeometryByDrawingViewBreaks");
	}

	if(!ls_proc)
		return false;

	if(((bool(*)(const mcsWorkID*, int, mcsGeomEntArray&))ls_proc) (pIdsDvBreaks, nBreaks, geArr))
		return true;
	return false;
}
//==================================================================================================

struct McsProfileEntity
{
	mcsWorkID m_idCurve;
	mcsWorkID m_idStartPoint;
	mcsWorkID m_idEndPoint;
	bool      m_bOpposed;
};
//==================================================================================================

struct McsCrossPoint
{
	mcsPoint  pt;
	mcsWorkID idPoint;
	mcsWorkID idCurve1;
	mcsWorkID idCurve2;
};
//==================================================================================================

struct IMcProfileContourData  : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcProfileContourData);
	IMCS_STD_METHOD_DEFINITION(IMcProfileContourData, IMcObject);

	virtual bool    storeContour(const mapWID2MEG& geStuff2d, const mcsPolyline& srcContour, const mcsTol& tol = gp3dSite->tol()) = 0;
	virtual bool    restoreContour(const mapWID2MEG& geStuff2d, const mcsTol& tol = gp3dSite->tol()) = 0;

	virtual HRESULT save(IMcsStream* pStream) const = 0;
	virtual HRESULT load(IMcsStream* pStream, const mcsTol& tol = gp3dSite->tol()) = 0;

	virtual void    getContour(OUT mcsPolyline& contour) const = 0;

	virtual HRESULT asListProfileEntities(
		const mapWID2MEG&               IDs2GeomMap,
		OUT McsArray<McsProfileEntity>& aEntities,
		OUT McsArray<McsCrossPoint>&    aPoints) const = 0;

		// выдаёт последовательность проекций, каждая из которых полностью использована в контуре,
		// все проекции лежат на одной базовой геом. кривой (т.е., напр., являются частью одной окружности/эллипса)
	virtual bool getClosedHomogeneousProjLoop(
		IN OUT McClosedHomogeneousProjLoopsData& loopData,
		OUT McsEntityGeometry&                   loopGeom) const = 0;
};
//==================================================================================================

typedef McsMapEx<int, int, int, int> mapIntToIntEx;

struct McFltn_grid_to_solids_data_base
{
	int           faceClusterSeed;
	int           nFaces;
	//int           nClusters;

	mapIntToIntEx vtxIdxSubst;
	mcsIntArray   vtxFaceClusters; // [i] is a cluster number the i-vertex belongs to
	mcsIntArray   faceClusters; // [i] item is a logical face cluster number for i-Face

	MCTYP_API McFltn_grid_to_solids_data_base();
};
//==================================================================================================

bool MCTYP_API mcComposeFaceClusters
(int        nVertices,
 int        nFaceIndices,
 const int* pFaceIndices,
 IN OUT McFltn_grid_to_solids_data_base& data);

//==================================================================================================

// (!) значения не менять, пишутся в файл
enum Mc3dConstraintTypeEnum
{
	kMc3dConstr_Unk           = 0,

	// standard assembly constraints
	kMc3dConstr_Insert        = 1,
	kMc3dConstr_Mate          = 2,
	kMc3dConstr_Angle         = 3,
	kMc3dConstr_Fixation      = 4,
	kMc3dConstr_Tangent       = 5,
	kMc3dConstr_Symmetry      = 6,

	kMc3dConstr_LinearPattern = 100, // аргументы: солид, направление. Для задания rectangle размером n*m надо создать n linear паттернов, каждый будет длином m. dblValue - смещение между соседними элементами. maPatternElements - остальные солиды
	kMc3dConstr_CircPattern   , // аргументы: mIdGeom1 - первый солид, mIdGeom2 - ось вращения. dblValue - угол поворота между соседними элементами.maPatternElements - остальные солиды.
	kMc3dConstr_MirrorPattern , // аргументы: mIdGeom1 - первый солид, mIdGeom2 - плоскость для зеркалирования. maPatternElements[0] - отражение
};
//==================================================================================================

// (!) значения не менять, пишутся в файл
enum McsWorkPlaneReferenceType
{
	kMcsWPLRef_Full   = 0,
	kMcsWPLRef_Point  = 1,
	kMcsWPLRef_Axis   = 2,
	kMcsWPLRef_Plane  = 3
};
//==================================================================================================
struct Mc3dConstraintInfo;
//==================================================================================================
struct Mc3dCtrSolvingStatus
{
	HRESULT   m_hSolvingRes;
	bool      m_bPredefinedError; // позволяет принудительно установить статус ошибки
	Mc3dConstraintInfo* m_pParent; // необходима дополнительная информация для вывода описания ошибки.

	Mc3dCtrSolvingStatus()
	{
		m_bPredefinedError = false;
		m_hSolvingRes = S_OK;
		m_pParent = NULL;
	}

	void setError(HRESULT res) {
		m_bPredefinedError = FAILED(res);
		m_hSolvingRes = res;
	}

	void setOk() {
		m_bPredefinedError = false;
		m_hSolvingRes = S_OK;
	}

	bool isOk() const {
		return SUCCEEDED(m_hSolvingRes);
	}

	operator HRESULT () const {
		return m_hSolvingRes;
	}

	MCTYP_API LPCTSTR description() const;

	bool operator == (const Mc3dCtrSolvingStatus& cw) const {
		return m_hSolvingRes == cw.m_hSolvingRes;
	}

	bool operator != (const Mc3dCtrSolvingStatus& cw) const {
		return m_hSolvingRes != cw.m_hSolvingRes;
	}
};
//==============================================================================

enum Mc3dTangentCtrAlignment
{
	// Константы не менять.
	kTan3dCtrAlignmentClosest = 0,
	kTan3dCtrAlignmentCooriented = 1,
	kTan3dCtrAlignmentOpposite = -1,
};

//==============================================================================

enum Mc3dTangentCtrAreaType
{
	// Константы не менять.
	kTan3dCtrAreaPoint = 0x00,
	kTan3dCtrAreaLine = 0x01,
	kTan3dCtrAreaCircle = 0x02
};

//==================================================================================================

struct Mc3dConstraintInfo
{
	Mc3dConstraintTypeEnum mType;

		// Объекты, к которым привязана зависимость.
		// Если mIdGeomXXX есть ID стандартного объекта,
		// соответствующее поле mStrStdPartWplNameXXX должно содержать корректное имя плоскости.
	mcsComplexWorkID mIdGeom1, mIdGeom2;

	// Используется для зависимости типа "симметрия" (плоскость отражения),
	// для стд. объектов она не применяется, поэтому поля mStrStdPartWplName для него нет.
	// Для угловой зависимости может использоваться для ID оси вращения (если она задана).
	mcsComplexWorkID mIdGeom3;

		// Имена плоскостей стандартного объекта (IMcStdPart), на которые наложена зависимость.
		// Не используются если объекты не являются стандартными (IMcStdPart)
	McsString mStrStdPartWplName1, mStrStdPartWplName2;

	bool   mbCoDirect; // используется, для зависимостей типа: insert/mate(plane_plane,axis_axis)
	double mDblValue;   // расстояние в мм, угол в радианах, тип касания
	McsString mValExpr; // выражение задающее mDblValue, актуальное значение будет после обновления зависимости.

		// Если входная геометрия есть плоскость и...
		// MATE:
		//   эти поля показывают, как ссылаться на данные плоскости (точка/ось/плоскость)
		//   так что возможно задать вледющие виды совмещения: PT-PT, PT-AXIS, PT-PLN, AXIS-AXIS, AXIS-PLN и PLN-PLN;
		// INSERT:
		//   оба должны быть kMcsWPLRef_Full, это значит, что place.pointOnPlane
		//   определяет ось с направлением plane.normal()
		// ANGLE, FIXATION:
		//   не используется
	McsWorkPlaneReferenceType mePlaneRefType1, mePlaneRefType2;

		// Заполняется после вычисления зависимости.
		// Содержит статус процесса вычисления.
	mutable Mc3dCtrSolvingStatus mSolvingStatus;

		// Временный ID, используется внутри
	mutable mcsWorkID _id;

	// TODO
	mcsWorkIDArray   mIdsPatternElements; // элементы массива, не включая начальный элемент mIdGeom1.

	// Если по идентификатору(например mIdGeom1) не удастся вычислить геометрию,
	// в этих полях можно посмотреть последние использованные геометрии.
	mutable McsEntityGeometry mGeometry1Cache, mGeometry2Cache, mGeometry3Cache;

	// тип касания. Например цилиндры могут касаться только одной точкой, а могут иметь общую прямую линию.
	Mc3dTangentCtrAreaType mTangentArea;

	//..............................................................................................

	MCTYP_API Mc3dConstraintInfo();
	MCTYP_API Mc3dConstraintInfo(const Mc3dConstraintInfo& cf);

	MCTYP_API Mc3dConstraintInfo& operator= (const Mc3dConstraintInfo& cf);
	MCTYP_API void setNull();

	bool isNull() const {
		return mType == kMc3dConstr_Unk;
	}

	MCTYP_API bool isParametric() const;

	MCTYP_API bool isEqualTo(const Mc3dConstraintInfo& cmpWith, double tol) const;

		// проверяет, ссылаются ли this и cmpWith зависимости на одни и те же геом. объекты
	MCTYP_API bool doReferToSameObjects(const Mc3dConstraintInfo& cmpWith) const;

		// проверяет, относится ли зависимость к стандартным объектам
	MCTYP_API bool isStdConstraint() const;

		// ID документа, на который ссылаются данные зависимости
	MCTYP_API mcsWorkID getDocID() const;

		// Методы возвращают ID деталей (кластеров), привязанных к зависимости
	MCTYP_API mcsWorkID getIdPart1() const;
	MCTYP_API mcsWorkID getIdPart2() const;
	MCTYP_API mcsWorkID getIdPart3() const;
	MCTYP_API mcsWorkID getIdPart(int iPart) const;
	MCTYP_API mcsComplexWorkID getIdGeom(int iPart) const;

		// Методы возвращают IDs объектов, создавших геометрию, на которую наложена зависимость
	MCTYP_API mcsWorkID getIdOfRecalcReactorFrom1() const;
	MCTYP_API mcsWorkID getIdOfRecalcReactorFrom2() const;
	MCTYP_API mcsWorkID getIdOfRecalcReactorFrom3() const;
	MCTYP_API mcsWorkID getIdOfRecalcReactorFrom(int iPart) const;

	MCTYP_API HRESULT getGeometry1(OUT McsEntityGeometry& geom) const;
	MCTYP_API HRESULT getGeometry2(OUT McsEntityGeometry& geom) const;
	MCTYP_API HRESULT getGeometry3(OUT McsEntityGeometry& geom) const;
	MCTYP_API HRESULT getGeometry(int iPart, OUT McsEntityGeometry& geom) const;

	// количество элементов геометрии, связываемое зависимостью
	MCTYP_API int getNumConstrainedItems() const;

	MCTYP_API HRESULT write(IMcsStream* pS) const;
	MCTYP_API HRESULT read(IMcsStream* pS);

		// хэлперы, для не платформенной реализации зависимостей
	MCTYP_API bool addReactors(const mcsWorkID& idTo, bool fApplyNow = true) const;
	MCTYP_API bool removeReactors(const mcsWorkID& idTo, bool fApplyNow = true) const;

	MCTYP_API Mc3dTangentCtrAlignment getTangentAlignment() const;
	MCTYP_API void setTangentAlignment(Mc3dTangentCtrAlignment alignment);

	MCTYP_API Mc3dTangentCtrAreaType getTangentArea() const;
	MCTYP_API void setTangentArea(Mc3dTangentCtrAreaType areaType);

	MCTYP_API mcsComplexWorkID rotationAxis() const;
	MCTYP_API void setRotationAxis(const mcsComplexWorkID& id);
};

typedef McsArray<Mc3dConstraintInfo> Mc3dConstraintInfoArray;
//==================================================================================================

// Объект этого интерфейса можно создать через вызов 'createObject'

struct IMc3dConstraint : public virtual IMcObject
{
	IMCS_QI_METHOD_DEFINITION(IMc3dConstraint, IMcObject);
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dConstraint);

		// Sets data for a constraint or initializes a newly created constraint;
		// objects from a new data must reside in the same document as the constraint is currently in
	virtual HRESULT setInfo(IN const Mc3dConstraintInfo& ctrInfo) = 0;

		// queries information about a constraint object
	virtual HRESULT getInfo(OUT Mc3dConstraintInfo& ctrInfo) const = 0;

		// ID of the 1'st directly constrained object (the top ID in a complexIDs chain)
	virtual mcsWorkID getIdPart1() const = 0;

		// ID of the 2'nd directly constrained object (the top ID in a complexIDs chain)
	virtual mcsWorkID getIdPart2() const = 0;

		// ID of the 2'nd directly constrained object (the top ID in a complexIDs chain)
	virtual mcsWorkID getIdPart3() const = 0;

		// gets the variable that controls the parametric value of the constraint
	virtual mcsWorkID getIdVar() const = 0;

		// true if a constraint is alive 
	virtual bool isOk() const = 0;

		// true if a constraint has modifications that must be applied to the system
	virtual bool isModified() const = 0;

		// suppresses the constraint; while it's suppressed, it's not evaluated
	virtual bool suppress() = 0;

		// unsuppresses the constraint
	virtual bool unsuppress() = 0;

		// reports whether the sonctraint object is suppressed and may be unsuppressed by a call to the unsuppress() method
	virtual bool canBeUnsuppressed() const = 0;

		// a status of this constraint
	virtual Mc3dHistoryItemStatus status() const = 0;

		// the name of the constraint object
		// this name may be displayed to a user
	virtual McsString getName() const = 0;

		// the method updates the constraint's name visible to a user
	virtual bool setName(LPCTSTR lpszNewName) = 0;

		// if any of the constrained objects was changed and then initiated the update,
		// this method should inform the caller about such parts caused recalculations;
		// if no such information exists, just returns an empty list;
		// this method has the meaning only in M3D implementation, not in the PLM's one
	virtual void getIdsOfAlteredParts(OUT mcsWorkIDArray& idsAlteredParts) const = 0;

		// method overrides the internally stored IDs of parts causing constraints recalculation;
		// mostly used as a reset-method after constraints are calculated
	virtual void setIdsOfAlteredParts(const mcsWorkIDArray& newIdsOfAlteredParts) = 0;

		// Подсветка примитивов, на которые наложена зависимость,
		// дополнительно позволяет показать графику с указанной в 'additionalTfm' трансформацией
	virtual HRESULT highlightGeometry(bool bHL, const mcsMatrix& additionalTfm = mcsMatrix::kIdentity) = 0;

		// system use only
	virtual void _processEndCloningEvent(const mcsWId2WIdMap& old2new, bool bEndBlkEdit) {};
};
//==================================================================================================

// interface for natively implemented constraint

struct IMcDb3dConstraint : public virtual IMcDbObject
{
	IMCS_STD_METHOD_DEFINITION(IMcDb3dConstraint, IMcDbObject);
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcDb3dConstraint);

		// see desriptions in IMc3dConstraint;
		// signatures and the meaning is the same

	virtual HRESULT   setInfo(IN const Mc3dConstraintInfo& ctrInfo) = 0;
	virtual HRESULT   getInfo(OUT Mc3dConstraintInfo& ctrInfo) const = 0;
	virtual mcsWorkID getIdPart1() const = 0;
	virtual mcsWorkID getIdPart2() const = 0;
	virtual mcsWorkID getIdPart3() const = 0;
	virtual mcsWorkID getIdVar() const = 0;
	virtual bool      isOk() const = 0;
	virtual bool      isModified() const = 0;
	virtual McsString getName() const = 0;
	virtual bool      setName(LPCTSTR lpszNewName) = 0;
	virtual bool      suppress() = 0;
	virtual bool      unsuppress() = 0;
	virtual bool      canBeUnsuppressed() const = 0;

	virtual Mc3dHistoryItemStatus status() const = 0;
};
//==================================================================================================

struct IMcs3dConstraintsManager : public IMObject
{
		// if true, all methods in IMc3dConstraint are completely supported by a platform,
		// M3D emulation code will be switched off in this case
	virtual bool isImplementedByPlatform() {
		return false;
	}

		// creates new or updates an existing constraint
		// if a constraint object with ID==idConstraint exists, method tries to updates its data,
		// otherwise tries to create the one with the specified id;
		// 'idConstraint' must not be null
	M3D_API virtual HRESULT _createOrUpdateConstraintOld(IN const Mc3dConstraintInfo& ctrInfo, IN const mcsWorkID& idConstraint, bool bUpdateNow = true);

		// creates a new constraint object
	M3D_API virtual HRESULT createConstraint(IN const Mc3dConstraintInfo& ctrInfo, OUT mcsWorkID& idConstraint, bool bUpdateNow = true);
	M3D_API virtual HRESULT deleteConstraint(IN const mcsWorkID& ctrID);
	M3D_API virtual HRESULT getConstraintInfo(IN const mcsWorkID& ctrID, OUT Mc3dConstraintInfo& ctrInfo);

		// method calculated the specified set of constraints,
		// NLUL for pIdsConstraints means update all constraints in the current doc.
	virtual HRESULT applyConstraints(IN OPTIONAL const mcsWorkIDArray* pIdsConstraints = NULL, IN OPTIONAL bool bForceCalc = false) {
		return E_NOTIMPL;
	}

	virtual void setLastConstraintsEvaluationResult(HRESULT hres) {
	}

	virtual HRESULT getLastConstraintsEvaluationResult() {
		return E_NOTIMPL;
	}
};
//==================================================================================================

typedef McsMapEx<mcsWorkID, const mcsWorkID&, mcsMatrix, const mcsMatrix&> mcsMapId2Mtx;

struct IMc3dConstraintsEvaluator : public virtual IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dConstraintsEvaluator);
	IMCS_QI_METHOD_DEFINITION(IMc3dConstraintsEvaluator, IMcObject);

	virtual HRESULT evaluate(
		IN const Mc3dConstraintInfoArray& constraintsInfoArray,
		OUT mcsMapId2Mtx&                 idPartToRelTfm) = 0;
};
//==================================================================================================

// сводная информация о переменной
struct McsDocVariableInfo
{
	DWORD      dwTypeFlags; // флаги из McsDocVarTypeEnum

	McsString  strName;
	MCSVariant vValue;
	McsString  strExpression;
	McsString  strDescription;
	McsString  strFieldAndQuality;

	double dDeviation;
	double dLowTol;
	double dUpTol;
	IMcAssocVariableData::ToleranceType tolType;

	bool isValid;

	McsDocVariableInfo(){
		setNull();
	}

	bool isExternal() { 
		return kMcDocVarType_External == (dwTypeFlags & kMcDocVarType_External); 
	}

	bool isCrossBlock() { 
		return kMcDocVarType_CrossBlock == (dwTypeFlags & kMcDocVarType_CrossBlock); 
	}

	bool isXRef() { 
		return kMcDocVarType_XRef == (dwTypeFlags & kMcDocVarType_XRef); 
	}

	bool isSimpleUserVar() {
		if (isExternal())
			return false;
		if (isCrossBlock())
			return false;
		if (isXRef())
			return false;
		return true;
	}

	void setNull()
	{
		dwTypeFlags = kMcDocVarType_Unk;
		strName.Empty();
		vValue.Clear();
		strExpression.Empty();
		strDescription.Empty();
		strFieldAndQuality.Empty();

		dDeviation = 0.0;
		dLowTol = 0.0;
		dUpTol = 0.0;
		tolType = IMcAssocVariableData::Nominal;

		// допускаем, что по умолчанию с переменной проблем нет.
		// в ином случае она сама даст о себе знать
		isValid = true;
	}
};
//==================================================================================================

// Является значением, хранимым в параметре M3D_PARAM_DIMENSIONAL_NAME_FORMAT.
enum DimensionConstraintNameFormatEnum
{
	kDCNFName           = 0, // dimText: "d1"
	kDCNFValue          = 1, // dimText: "2.3"
	kDCNFNameExpression = 2, // dimText: "d1 = 2.3"
};
//==================================================================================================

// Интерфейс управления переменными в документе

struct IMcsDocVariablesManager : public IMObject
{
		// выдаёт ассоциированный с данным объектом документ
	virtual mcsWorkID  getDocID() = 0;

	virtual HRESULT    getAllVariables(OUT mcsWorkIDArray& idsVars, IN OPTIONAL DWORD filter = kMcDocVarType_All) = 0;
	virtual mcsWorkID  getVarIdByName(IN LPCTSTR lpszName) = 0;

	virtual McsString  getVarName(IN const mcsWorkID& idVar) = 0;
	virtual McsString  getVarExpression(IN const mcsWorkID& idVar) = 0;
	virtual McsString  getVarDescription(IN const mcsWorkID& idVar) = 0;
	virtual MCSVariant getVarValue(IN const mcsWorkID& idVar) = 0;
	virtual HRESULT    getVarInfo(IN const mcsWorkID& idVar, OUT McsDocVariableInfo& varInfo) = 0;
	virtual DWORD      getVarType(IN const mcsWorkID& idVar) = 0; // см. флаги из McsDocVarTypeEnum

	virtual HRESULT    setVarName(IN const mcsWorkID& idVar, IN LPCTSTR lpszNewName) = 0;
	virtual HRESULT    setVarExpression(IN const mcsWorkID& idVar, IN LPCTSTR lpszNewExpression) = 0;
	virtual HRESULT    setVarDescription(IN const mcsWorkID& idVar, IN LPCTSTR lpszNewDescription) = 0;

		// Если fAutoCheckType == true, то перед установкой проверит тип переменной, если она вычисляемая,
		// то метод вернёт ошибку, если проверка отключена, то значение будет присвоено в любом случае.
	virtual HRESULT    setVarValue(
		IN const mcsWorkID& idVar,
		IN const MCSVariant& vNewVal,
		IN OPTIONAL bool fAutoCheckType = true,
		IN OPTIONAL bool fAlsoReplaceExpression = false) = 0;

		// Проверяет, допустимо ли данное имя и/или выражение для переменной.
		// Можно проверять одновременно и имя и выражение, либо только имя или выражение,
		// значение строки "" приравнивается к =NULL;
		// Если вернёт E_INVALIDARG, значит связанный с переменной объект не допускает
		// результирующего значения;
		// Если задано выражение и pEvaluatedVal, то в *pEvaluatedVal будет записано
		// вычисленное значение выражения
	virtual HRESULT    validateNameAndExpression(
		IN const mcsWorkID&  idVar,
		IN OPTIONAL LPCTSTR  lpszNewVarName = NULL,
		IN OPTIONAL LPCTSTR  lpszNewExpression = NULL,
		OUT OPTIONAL double* pEvaluatedVal = NULL) = 0;

	enum VarValType
	{
		kVarValTypeUser,
		kVarValTypeAngular,
		kVarValTypeDist,
		kVarValTypeCount,
		kVarValTypeRadius,
		kVarValTypeThickness,
	};

		// Добавляет переменную с возможностью задать для неё имя, значение и выражение,
		// Если имя не указано или оно пустое, то имя сгенерируется автоматически
		// с использование типа varType;
		// Если не указано значение, то подразумевается 0.0
		// Если выражение содержит ошибку или ссылку на неизвестную переменную, то
		// переменная не создастся;
		// Если добавляется пользовательская переменная (varValType = kVarValTypeUser)
		// и указан параметр pVarID, то метод пытается присвоить переменной указанный ID.
		// pVarID Используется для системных целей.
	virtual mcsWorkID  addVar(
		IN OPTIONAL LPCTSTR          lpszVarName = NULL,
		IN OPTIONAL MCSVariant*      pVal = NULL,
		IN OPTIONAL LPCTSTR          lpszExpression = NULL,
		IN OPTIONAL VarValType       varValType = kVarValTypeUser,
		IN OPTIONAL const mcsWorkID* pVarID = NULL) = 0;

		// возвращает true, если от переменной ничего не зависит и она может быть удалена
	virtual bool       canVarBeDeleted(IN const mcsWorkID& idVar) = 0;

	enum DelMethod
	{
			// удаляет переменную только если от неё ничего не зависит
		kDelMeth_EraseIfUnused           = 0,

			// Удаляет переменную, если от неё зависит только одна размерная 2D-зависимость
			// или один 3D объект. При этом удаляется связанная зависимость / 3D-объект.
		kDelMeth_EraseWithObject         = 1,

			// -> Режим рекомендован для диалога по работе с переменныи документа.
			// Удаляет переменную, связанные с ней зависимость/3D-объект и во всех выражениях,
			// где используется она для вычисления, заменяется на её текущее значение
		kDelMeth_EraseObjAndReplaceByVal = 2,

			// Удаляет переменную и все связанные с ней зависимости, 3D-объекты и выражения.
			// При удалении выражения процесс выполняется рекурсивно
		kDelMeth_EraseAllDependent       = 3,

			// -> Режим рекомендован для удаления переменных из кода в случае, когда
			//    объекты отвязываются от этой переменной.
			// Удаляет переменную, связанные с ней зависимость во всех выражениях,
			// где используется она для вычисления, заменяется на её текущее значение.
			// Все объекты, которые зависели от этой переменной сохраняются.
		kDelMeth_KeepObjAndReplaceByVal  = 4,
	};

		// Пытается удалить переменную
	virtual HRESULT    deleteVar(IN const mcsWorkID& idVar, DelMethod = kDelMeth_EraseWithObject) = 0;

	// #10506: В новой модели этот метод в таком виде невозможно реализовать, по факту его пока никто не использует.
	//// выдаёт список переменных, от которых зависит значение данной
	//virtual HRESULT    getVarDependencies(IN const mcsWorkID& idVar, OUT mcsWorkIDArray& idsSourceVars) = 0;

		// выдаёт список объектов, которые зависят от данной переменной
	virtual HRESULT    getDependentOnVarObjects(
		IN const mcsWorkID&          idVar,
		OUT OPTIONAL mcsWorkIDArray* pIdsVars = NULL,
		OUT OPTIONAL mcsWorkIDArray*   pIds2dConstraints = NULL,
		OUT OPTIONAL mcsWorkIDArray* pIds3dObjects = NULL) = 0;

		// позволяет получить переменную, связанную с размером,
		// если он связан с размерной зависимостью
	virtual mcsWorkID getVarIdByDimId(IN const mcsWorkID& idDim) = 0;

		// позволяет получить размер, связанный с переменной,
		// если он связан с размерной зависимостью
	virtual mcsWorkID getDimIdByVarId(IN const mcsWorkID& idVar) = 0;

		// пересчитывает все переменные в документе, не трогая зависимости
	virtual HRESULT   evaluateAllVars(bool fForceRecalculate = false) = 0;

		// выдаёт данные объекта, владеющего данной переменной;
		// либо эскиз, либо WPL, либо 3d-фича либо др.
	virtual HRESULT getVarHostObjectInfo(
		IN const mcsWorkID&     idVar,
		OUT OPTIONAL mcsWorkID* pIdHostObj = NULL,
		OUT OPTIONAL McsString* pStrHostObjName = NULL) = 0;

		// определяет, содержит ли указанная переменная значение угла
	virtual bool isAngularValue(IN const mcsWorkID& idVar) = 0;

		// тип сети зависимостей, для которой получен менеджер переменных
	virtual McCtrs2dNetType constraintNetworkType() = 0;

	virtual IMcAssocVariableData* getVarData(const mcsWorkID& id) = 0;

		// Метод возвращает имя для новой переменной со значением указанного типа.
	virtual McsString generateNewVarName(VarValType varValType) = 0;
};
//==================================================================================================

// Хэлперы для работы с переменными

MCTYP_API HRESULT m3dDeleteObjVar(
	IN IMcDbObject*                                pOwnerDBO,
	IN const mcsWorkID&                            idVar,
	IN OPTIONAL IMcsDocVariablesManager::DelMethod delMeth = IMcsDocVariablesManager::kDelMeth_KeepObjAndReplaceByVal);

MCTYP_API HRESULT m3dSetObjVarVal(
	IN const mcsWorkID& idVar,
	IN double           rNewVal);

// NOTE: Если нужно за раз создать несколько переменных,
// крайне желательно указывать порядковый индекс создаваемой переменной в группе idxVar.
// Для McAssoc переменных этот индекс используется для коррекции времени создания переменной.
MCTYP_API HRESULT m3dCreateObjVar(
	IMcDbObject*                         pOwnerDBO,
	IMcsDocVariablesManager::VarValType  varValType,
	double                               rPrmVal,
	OUT mcsWorkID&                       idNewVar,
	IN OPTIONAL McCtrs2dNetType          ctrsNetType = kMc2dCtrNet_MCS,
	int                                  idxVar = -1); // -1 = не используется

MCTYP_API HRESULT m3dGetObjVarVal(
	IN const mcsWorkID& idVar,
	OUT double&         rVal);

MCTYP_API HRESULT m3dSetObjVarExpr(
	IN const mcsWorkID& idVar,
	IN LPCTSTR          strNewExpression);

MCTYP_API HRESULT m3dGetObjVarExpr(
	IN const mcsWorkID& idVar,
	OUT McsString&      strExpression);

//==================================================================================================

struct Mcs3dThreadData
{
	Mcs3dThreadData()
	{
		m_strNearestSizeArr.SetSize(2);
	}

	McsString m_strSize;
	McsString m_strExternalSize;
	mcsStringArray m_strAllExternalSizesList;
	mcsStringArray m_strInternalSizeList;
	mcsStringArray m_strDesignationList;
	mcsStringArray m_strPitchList;
	mcsStringArray m_strNearestSizeArr;
	mcsStringArray m_strNearestDesignArr;
};

//==================================================================================================

struct IMcs3dThreadDataManager : public virtual IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMcs3dThreadDataManager, IMcObject)

	// Возвращает внутренний указатель на Mcs3dThreadData
	virtual const Mcs3dThreadData* getData(IN LPCTSTR threadDataKey) = 0;

	virtual McsString getDataKey(IN bool bIsInternal, IN double diam, IN MCS_THREAD_STANDARD ts = TS_GOST_METRIC) = 0;
};
//==================================================================================================

enum Mc3dHoleSeatType
{
	k3dHoleSeatType_No = 0,
	k3dHoleSeatType_Counterbore = 1,
	k3dHoleSeatType_Countersink = 2
};
//==================================================================================================

enum Mc3dHoleType
{
	kHoleType_Simple = 0,
	kHoleType_Standard,
	kHoleType_Existing,
	kHoleType_Threaded
};
//==================================================================================================
struct IMc3dHole : public virtual IMcFeatureEntity
{
protected:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dHole);

public:
	IMCS_STD_METHOD_DEFINITION(IMc3dHole, IMcObject);

	M3D_API virtual IMdHoleFeaturePtr getFeatureConstructor() const;

	virtual Mc3dHoleType getHoleType() const = 0;
	virtual void setHoleType(Mc3dHoleType type) = 0;

	virtual m3dIPPDefPtr getPlacement() const = 0;
	virtual HRESULT setPlacement(m3dIPPDef* pPlacement) = 0;

	// Идентификатор цилиндрической поверхности.
	virtual mcsWorkID getFaceId() const = 0;
	virtual HRESULT setFaceId(const mcsWorkID& id, IN OPTIONAL const mcsVector* pDirAxis = NULL) = 0;

	// Идентификатор плоскости завершения отверстия.
	virtual mcsWorkID getTermFaceId() const = 0;
	virtual HRESULT setTermFaceId(const mcsWorkID& id) = 0;

	// Отверстие построено насквозь.
	virtual bool isFullDepth() const = 0;
	virtual HRESULT setIsFullDepth(bool value) = 0;

	// Резьба отверстия. Должна быть вне документа.
	virtual IMc3dThreadFeaturePtr getThread() const = 0;
	virtual HRESULT setThread(IMc3dThreadFeature* pThread) = 0;

	// Параметры отверстия стандартного типа.
	virtual IMcStdPartPtr getStdHolePart() = 0;
	virtual HRESULT setStdHolePart(IMcStdPart* pStdPart) = 0;

	// Диаметр отверстия.
	virtual double getDiameter() const = 0;
	virtual HRESULT setDiameter(double value) = 0;

	// Глубина отверстия.
	virtual double getDepth() const = 0;
	virtual HRESULT setDepth(double value) = 0;

	// Тип посадочного места.
	virtual Mc3dHoleSeatType getSeatType() const = 0;
	virtual HRESULT setSeatType(Mc3dHoleSeatType type) = 0;

	// Угол конусности дна.
	virtual double getBottomAngle() const = 0;
	virtual HRESULT setBottomAngle(double angle_rad) = 0;

	// Плоское дно.
	virtual bool isFlatBottom() const = 0;
	virtual HRESULT setFlatBottom(bool bFlat) = 0;

	// Диаметр посадочного места.
	virtual double getSeatDiameter() const = 0;
	virtual HRESULT setSeatDiameter(double value) = 0;

	// Глубина посадочного места.
	virtual double getSeatDepth() const = 0;
	virtual HRESULT setSeatDepth(double value) = 0;

	// Угол конусности посадочного места.
	virtual double getSeatAngle() const = 0;
	virtual HRESULT setSeatAngle(double angle_rad) = 0;

	// Проверка возможности создания отверстия типа "Существующее".
	static bool canGetHoleByFEV(IN const mcsWorkID& id);
};
//==================================================================================================

#pragma region Sheet metal features

// IMcFeatureEntity можно получить через QueryInterface, но прямого наследования нет.
// Это связано с тем, что SM-классы реализованы не на C++.

struct IMc3dSmFeature : public virtual IMcObject// IMcFeatureEntity
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmFeature);
	IMCS_QI_METHOD_DEFINITION(IMc3dSmFeature, IMcObject);//IMcFeatureEntity);
};
//==================================================================================================

// Задает направление выдавливания листового тела
// Значения не менять, пишутся в файл
enum m3dSmExtTypeEnum
{
	kSmExtType_PositiveDist  = 0, // одно расстояние, прямое направление
	kSmExtType_NegativeDist  = 1, // одно расстояние, обратное направление
	kSmExtType_TwoDists      = 2, // два расстояния
	kSmExtType_SymmetryDists = 3, // одно расстояние, симметрично, по половине расстояния в обе стороны
};
//==================================================================================================

// Листовое тело. Базовая (первая) фича любого листового тела.

struct IMc3dSmSheetSolid : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmSheetSolid);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmSheetSolid, IMc3dSmFeature);

	// Допускается профиль двух типов: kMcProfGeom_SingleOpenCurve, kMcProfGeom_ClosedSimpleRegion (множество IMcSketchProfile::GeomTypeEnum)
	// Установка эскизного профиля.
	virtual HRESULT   SetProfileID(const mcsWorkID& idProfile) = 0;

	// Получение эскизного профиля.
	virtual mcsWorkID GetProfileID() const = 0;

	// переменная, определяющая единственное или первое из двух расстояний
	virtual mcsWorkID GetDist1VarID() const = 0;

	// переменная, определяющая второе из двух расстояний
	virtual mcsWorkID GetDist2VarID() const = 0;

	// переменная, определяющая толщину листового тела
	virtual mcsWorkID GetThicknessVarID() const = 0;

	// переменная, определяющая радиус сгибов
	virtual mcsWorkID GetRadiusVarID() const = 0;

	// задание направления построения листового тела относительно эскизного профиля
	virtual HRESULT          SetExtrutionType(m3dSmExtTypeEnum newExt) = 0;

	// получение направления построения листового тела относительно эскизного профиля
	virtual m3dSmExtTypeEnum GetExtrusionType() const = 0;
};
//==================================================================================================

// Режим смещения сгиба
// Значения не менять, пишутся в файл
enum m3dSmBendLocTypeEnum
{
	kSmBendLocType_AllLength    = 0, // По всей длине.
	kSmBendLocType_Center       = 1, // По центру.
	kSmBendLocType_TwoIndent    = 2, // Отступ слева и справа.
	kSmBendLocType_LeftOffset   = 3, // Смещение слева.
	kSmBendLocType_RightOffset  = 4, // Смещение справа.
};
//==================================================================================================

// Режим длины продолжения сгиба.
// Значения не менять, пишутся в файл
enum m3dSmLengthTypeEnum
{
	kSmLengthType_Bend        = 0, // Длина от конца сгиба.
	kSmLengthType_ContourOut  = 1, // Длина по наружному контуру.
	kSmLengthType_ContourIn   = 2, // Длина по внутреннему контуру.
	kSmLengthType_TangetOut   = 3, // Длина по внешней касательной сгиба.
	kSmLengthType_TangetIn    = 4, // Длина по внутренней касательной сгиба.
};
//==================================================================================================

// Режим длины продолжения сгиба.
// Значения не менять, пишутся в файл
enum m3dSmDispEdgeTypeEnum
{
	kSmDispEdgeType_BendLineInside    = 0, // Линия сгиба внутри.
	kSmDispEdgeType_BendLineOutside   = 1, // Линия сгиба снаружи.
	kSmDispEdgeType_ByProjection      = 2, // По касательной.
	kSmDispEdgeType_OffsetInside      = 3, // Смещение внутрь.
	kSmDispEdgeType_OffsetOutside     = 4, // Смещение наружу.
};
//==================================================================================================

// Режим перекрытия загибов.
// Значения не менять, пишутся в файл
enum m3dSmOverlapProcessTypeEnum
{
	kSmOverlapProcessType_noProcessing            = 0, // без обработки.
	kSmOverlapProcessType_automaticAnglesCutting  = 1, // автоматическое вычисление угла, величина зазора также определяется автоматически.
	kSmOverlapProcessType_automaticCuttingByWidth = 2, // Внутренний контур.
	kSmOverlapProcessType_offset                  = 3, // Ручной режим задания отступа, показываем поле ввода, никакой автоматики.
};
//==================================================================================================

// Режим перекрытия загибов.
// Значения не менять, пишутся в файл
enum m3dSmReleaseTypeEnum
{
	kSmReleaseType_No   = 0, // Нет.
	kSmReleaseType_Only = 1, // Только сгиб.
	kSmReleaseType_Bend = 2, // Сгиб и его продолжение.
	kSmReleaseType_All  = 3, // Все сгибы.
};
//==================================================================================================

// Тип радиуса.
// Значения не менять, пишутся в файл
enum m3dSmRadiusTypeEnum
{
	kSmRadiusType_Internal = 0, // Внутренний.
	kSmRadiusType_External = 1, // Внешний.
};
//==================================================================================================

// Тип угла.
// Значения не менять, пишутся в файл
enum m3dSmAngleTypeEnum
{
	kSmAngleType_AngleBend          = 0, // Угол сгиба.
	kSmAngleType_ComplementaryAngle = 1, // Дополняющий угол.
};
//==================================================================================================

// Режим обработки угла в части сгиба.
// Значения не менять, пишутся в файл
enum m3dSmCloseBendsTypeEnum
{
	kSmCloseBendsType_None  = 0, // Угол сгиба.
	kSmCloseBendsType_Chord = 1, // По хорде.
	kSmCloseBendsType_Edge  = 2, // По кромке.
	kSmCloseBendsType_cbCircle = 3, // 
};
//==================================================================================================

/// Режим замыкания угла.
// Значения не менять, пишутся в файл
enum m3dSmCloseCornerTypeEnum
{
	kSmCloseCornerType_Rip     = 0, // Замыкание встык.
	kSmCloseCornerType_Overlap = 1, // Перекрытие.
	kSmCloseCornerType_Tight   = 2, // Плотное замыкание.
};
//==============================================================================================	
struct IMc3dSmCornerProcessing : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmCornerProcessing);
	IMCS_QI_METHOD_DEFINITION(IMc3dSmCornerProcessing, IMc3dSmFeature);

	// Возвращает флаг замыкания в начале.
	virtual bool GetProcessStartingCornersClosure() const = 0;

	// Задает флаг замыкания в начале.
	virtual void SetProcessStartingCornersClosure(bool value) = 0;

	// Возвращает угол в начале.
	virtual double GetStartingCornersClosureAngle() const = 0;

	// Задает угол в начале.
	virtual void SetStartingCornersClosureAngle(double value) = 0;

	// Задает режим замыкания углов в начале.
	virtual void SetStartingCornersClosureCornerType(m3dSmCloseCornerTypeEnum enumElement) = 0;

	// Возвращает режим замыкания углов в начале.
	virtual m3dSmCloseCornerTypeEnum GetStartingCornersClosureCornerType() const = 0;

	// Задает режим обработки углов в начале.
	virtual void SetStartingCornersClosureBendsType(m3dSmCloseBendsTypeEnum enumElement) = 0;

	// Возвращает режим обработки углов в начале.
	virtual m3dSmCloseBendsTypeEnum GetStartingCornersClosureBendsType() const = 0;

	// Возвращает отступ в начале.
	virtual double GetStartingCornersClosureGap() const = 0;

	// Задает отступ в начале.
	virtual void SetStartingCornersClosureGap(double value) = 0;


	// Возвращает флаг замыкания смежных углов.
	virtual bool GetProcessMiddleCornersClosure() const = 0;

	// Задает флаг замыкания смежных углов.
	virtual void SetProcessMiddleCornersClosure(bool value) = 0;

	// Задает режим замыкания смежных углов.
	virtual void SetMiddleCornersClosureCornerType(m3dSmCloseCornerTypeEnum enumElement) = 0;

	// Возвращает режим замыкания смежных углов.
	virtual m3dSmCloseCornerTypeEnum GetMiddleCornersClosureCornerType() const = 0;

	// Задает режим обработки смежных углов.
	virtual void SetMiddleCornersClosureBendsType(m3dSmCloseBendsTypeEnum enumElement) = 0;

	// Возвращает режим обработки смежных углов.
	virtual m3dSmCloseBendsTypeEnum GetMiddleCornersClosureBendsType() const = 0;

	// Возвращает зазор по середине.
	virtual double GetMiddleCornersClosureGap() const = 0;

	// Задает зазор по середине.
	virtual void SetMiddleCornersClosureGap(double value) = 0;


	// Возвращает флаг замыкания в конце.
	virtual bool GetProcessEndingCornersClosure() const = 0;

	// Задает флаг замыкания в конце.
	virtual void SetProcessEndingCornersClosure(bool value) = 0;

	// Возвращает угол в конце.
	virtual double GetEndingCornersClosureAngle() const = 0;

	// Задает угол в конце.
	virtual void SetEndingCornersClosureAngle(double value) = 0;

	// Задает режим замыкания углов в конце.
	virtual void SetEndingCornersClosureCornerType(m3dSmCloseCornerTypeEnum enumElement) = 0;

	// Возвращает режим замыкания углов в конце.
	virtual m3dSmCloseCornerTypeEnum GetEndingCornersClosureCornerType() const = 0;

	// Задает режим обработки углов в конце.
	virtual void SetEndingCornersClosureBendsType(m3dSmCloseBendsTypeEnum enumElement) = 0;

	// Возвращает режим обработки углов в конце.
	virtual m3dSmCloseBendsTypeEnum GetEndingCornersClosureBendsType() const = 0;

	// Возвращает отступ в конце.
	virtual double GetEndingCornersClosureGap() const = 0;

	// Задает отступ в конце.
	virtual void SetEndingCornersClosureGap(double value) = 0;
};
//==============================================================================================	

struct IMc3dSmBendRelease : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmBendRelease);
	IMCS_QI_METHOD_DEFINITION(IMc3dSmBendRelease, IMc3dSmFeature);

	// Возвращает флаг освобождения сгиба.
	virtual bool GetBendRelease() const = 0;
	
	// Задает флаг освобождения сгиба.
	virtual void SetBendRelease(bool value) = 0;

	// Возвращает флаг скругления.
	virtual bool GetRoundedFoldRelease() const = 0;
	
	// Задает флаг скругления.
	virtual void SetRoundedFoldRelease(bool value) = 0;

	// Возвращает ширину зазора.
	virtual double GetWidthSlot() const = 0;
	
	// Задает ширину зазора.
	virtual void SetWidthSlot(double value) = 0;

	// Возвращает глубину зазора.
	virtual double GetDepthSlot() const = 0;
	
	// Задает глубину зазора.
	virtual void SetDepthSlot(double value) = 0;

	// Возвращает флаг влючения ширины сгиба.
	virtual bool GetIncludeBendWidth() const = 0;
	
	// Задает флаг влючения ширины сгиба.
	virtual void SetIncludeBendWidth(bool value) = 0;

	// Задает режим освобождение угла.
	virtual void SetReleaseType(m3dSmReleaseTypeEnum newExt) = 0;
	
	// Возвращает режим освобождение угла.
	virtual m3dSmReleaseTypeEnum GetReleaseType() const = 0;
};
//==============================================================================================	

struct IMc3dSmEdgeCommon : public virtual IMc3dSmCornerProcessing, virtual IMc3dSmBendRelease
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmEdgeCommon);
	IMCS_QI_METHOD_DEFINITION3(IMc3dSmEdgeCommon, IMc3dSmCornerProcessing, IMc3dSmBendRelease);
	
	// Возвращает список ребер, по которым выполнен сгиб
	virtual bool GetEdgesIds(OUT mcsWorkIDArray& idsEdges) const = 0;

	// Задает список рёбер, по которым нужно выполнить сгиб
	virtual void SetEdgesIds(IN const mcsWorkIDArray& idsEdges) = 0;

	// Задает направление построения листового тела относительно эскизного профиля
	virtual void SetBendLocationType(m3dSmBendLocTypeEnum newExt) = 0;

	// Задает направление построения листового тела относительно эскизного профиля
	virtual m3dSmBendLocTypeEnum GetBendLocationType() const = 0;

	// Возвращает ширину сгиба.
	virtual double GetBendWidth() const = 0;
	
	// Задает ширину сгиба.
	virtual void SetBendWidth(double direction) = 0;

	// Возвращает отступ слева.
	virtual double GetLeftDistance() const = 0;
	
	// Задает отступ слева.
	virtual void SetLeftDistance(double direction) = 0;

	// Возвращает отступ справа.
	virtual double GetRightDistance() const = 0;
	
	// Задает отступ справа.
	virtual void SetRightDistance(double direction) = 0;

	// Возвращает направление загиба.
	virtual bool IsReversedDirection() const = 0;
	
	// Задает направление загиба.
	virtual void SetDirection(bool direction) = 0;

	// Возвращает коеффициент положения нейтрального слоя.
	virtual double GetCoefficient() const = 0;
	
	// Задает коеффициент положения нейтрального слоя.
	virtual void SetCoefficient(double coefficient) = 0;

	// Задает режим продолжения длины сгиба.
	virtual void SetLengthType(m3dSmLengthTypeEnum newExt) = 0;
	
	// Возвращает режим продолжения длины сгиба.
	virtual m3dSmLengthTypeEnum GetLengthType() const = 0;

	// переменная, определяющая длину сгиба.
	virtual mcsWorkID GetLengthVarID() const = 0;

	// Задает режим радиуса.
	virtual void SetRadiusType(m3dSmRadiusTypeEnum radiusType) = 0;
	
	// Возвращает режим радиуса.
	virtual m3dSmRadiusTypeEnum GetRadiusType()const = 0;

	// Переменная, определяющая радиус сгиба.
	virtual mcsWorkID GetRadiusVarID() const = 0;

	// Задает режим угла.
	virtual void SetAngleType(m3dSmAngleTypeEnum angleType) = 0;
	
	// Возвращает режим угла.
	virtual m3dSmAngleTypeEnum GetAngleType() const = 0;

	// Переменная, определяющая угол сгиба.
	virtual mcsWorkID GetAngleVarID() const = 0;

	// Задает режим смещения сгиба для сгиба по ребру.
	virtual void SetDiplacementEdgeType(m3dSmDispEdgeTypeEnum newExt) = 0;
	
	// Возвращает режим смещения сгиба для сгиба по ребру.
	virtual m3dSmDispEdgeTypeEnum GetDiplacementEdgeType() const = 0;

	// Переменная, определяющая смещение сгиба.
	virtual mcsWorkID GetDisplacementVarID() const = 0;


	// Возвращает флаг расширения сгиба слева.
	virtual bool GetLeftBendExtension() const = 0;
	
	// Задает флаг расширения сгиба слева.
	virtual void SetLeftBendExtension(bool check) = 0;

	// Переменная, определяющая угол уклона сгиба слева.
	virtual mcsWorkID GetBendSlopeLeftVarID() const = 0;

	// Переменная, определяющая угол уклона слева.
	virtual mcsWorkID GetSlopeLeftVarID() const = 0;

	// Возвращает расширение слева.
	virtual double GetLeftWidening() const = 0;
	
	// Задает расширение слева.
	virtual void SetLeftWidening(double distance) = 0;


	// Возвращает флаг расширения сгиба справа.
	virtual bool GetRightBendExtension() const = 0;
	
	// Задает флаг расширения сгиба справа.
	virtual void SetRightBendExtension(bool check) = 0;

	// Переменная, определяющая  угол уклона сгиба справа.
	virtual mcsWorkID GetBendSlopeRightVarID() const = 0;

	// Переменная, определяющая угол уклона справа.
	virtual mcsWorkID GetSlopeRightVarID() const = 0;

	// Возвращает расширение справа.
	virtual double GetRightWidening() const = 0;
	
	// Задает расширение справа.
	virtual void SetRightWidening(double distance) = 0;
};
//==================================================================================================

struct IMc3dSmEdge : public virtual IMc3dSmEdgeCommon
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmEdge);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmEdge, IMc3dSmEdgeCommon);

	// Задает режим обработки перекрытия загибов.
	virtual void SetOverlapingsProcessingType(m3dSmOverlapProcessTypeEnum newExt) = 0;
	
	// Возвращает режим обработки перекрытия загибов.
	virtual m3dSmOverlapProcessTypeEnum GetOverlapingsProcessingType() const = 0;

	// Возвращает ширину зазора.
	virtual double GetGapWidth() const = 0;

	// Задает ширину задора.
	virtual void SetGapWidth(double value) = 0;
};
//==================================================================================================

struct IMc3dSmFlanging : public virtual IMc3dSmEdgeCommon
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmFlanging);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmFlanging, IMc3dSmEdgeCommon);
};
//==================================================================================================

/// Режим завальцовки.
// Значения не менять, пишутся в файл
enum m3dSmCurlingTypeEnum
{
	kSmCurlingType_Closed           = 0, // Закрытая.
	kSmCurlingType_Opened           = 1, // Открытая.
	kSmCurlingType_SType            = 2, // S-тип.
	kSmCurlingType_Double           = 3, // Двойная.
	kSmCurlingType_OpenLoop         = 4, // Открытая петля.
	kSmCurlingType_ClosedLoop       = 5, // Закрытая петля.
	kSmCurlingType_CenteredContour  = 6, // Центрированный контур.
};
//==============================================================================================	

struct IMc3dSmCurling : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmCurling);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmCurling, IMc3dSmFeature);

	// Возвращает список ребер, по которым выполнен сгиб
	virtual bool GetEdgesIds(OUT mcsWorkIDArray& idsEdges) const = 0;

	// Задает список рёбер, по которым нужно выполнить сгиб
	virtual void SetEdgesIds(IN const mcsWorkIDArray& idsEdges) = 0;

	// Задает режим освобождение угла.
	virtual void SetCurlingType(m3dSmCurlingTypeEnum newExt) = 0;
	
	// Возвращает режим освобождение угла.
	virtual m3dSmCurlingTypeEnum GetCurlingType() const = 0;

	// Возвращает коеффициент положения нейтрального слоя.
	virtual double GetCoefficient() const = 0;

	// Задает коеффициент положения нейтрального слоя.
	virtual void SetCoefficient(double value) = 0;

	// Возвращает длину сгиба.
	virtual double GetBendLength() const = 0;

	// Задает длину сгиба.
	virtual void SetBendLength(double value) = 0;

	// Возвращает длину второго сгиба.
	virtual double GetBendLength2() const = 0;

	// Задает длину второго сгиба.
	virtual void SetBendLength2(double value) = 0;

	// Возвращает направление загиба.
	virtual bool IsReversedDirection() const = 0;
	
	// Задает направление загиба.
	virtual void SetDirection(bool direction) = 0;

	// Возвращает флаг разделки углов.
	virtual bool IsCuttingCorners() const = 0;
	
	// Задает флаг разделки углов.
	virtual void SetCuttingCorners(bool direction) = 0;

	// Возвращает флаг эквивалентных радиусов.
	virtual bool IsEqualRadius() const = 0;
	
	// Задает эквивалентность радиусов.
	virtual void SetEqualRadius(bool direction) = 0;

	// Возвращает угол разделки.
	virtual double GetCuttingAngle() const = 0;

	// Задает угол разделки.
	virtual void SetCuttingAngle(double value) = 0;

	// Возвращает угол заметания.
	virtual double GetSweepingAngle() const = 0;

	// Задает угол заметания.
	virtual void SetSweepingAngle(double value) = 0;

	// Возвращает значение для первого радиуса.
	virtual double GetRadius1() const = 0;
			
	// Задает значение для первого радиуса.
	virtual void SetRadius1(double value) = 0;

	// Возвращает значение для второго радиуса.
	virtual double GetRadius2() const = 0;

	// Задает значение для второго радиуса.
	virtual void SetRadius2(double value) = 0;
};
//==================================================================================================

/// Режим формирования сгиба.
// Значения не менять, пишутся в файл
enum m3dSmDisplacementTypeEnum
{
	kSmDisplacementType_BendLineInside    = 0, // Линия сгиба внутри.
	kSmDisplacementType_BendLineOutside   = 1, // Линия сгиба снаружи.
	kSmDisplacementType_ByProjection      = 2, // По касательной.
	kSmDisplacementType_AlongFoldLine     = 3, // Вдоль линии сгиба.
};
//==============================================================================================	

struct IMc3dSmOverSegCommon : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmOverSegCommon);
	IMCS_QI_METHOD_DEFINITION(IMc3dSmOverSegCommon, IMc3dSmFeature);

	// Устанавливает профиль.
	virtual void SetProfileID(const mcsWorkID& profileId) = 0;

	// Возвращает профиль.
	virtual mcsWorkID GetProfileID() const = 0;

	// Задает режим угла.
	virtual void SetAngleType(m3dSmAngleTypeEnum value) = 0;
	
	// Возвращает режим угла.
	virtual m3dSmAngleTypeEnum GetAngleType() const = 0;

	// Переменная, определяющая угол сгиба.
	virtual mcsWorkID GetAngleVarID() const = 0;

	// Возвращает коеффициент положения нейтрального слоя.
	virtual double GetCoefficient() const = 0;
	
	// Задает коеффициент положения нейтрального слоя.
	virtual void SetCoefficient(double value) = 0;

	// Задает режим радиуса.
	virtual void SetRadiusType(m3dSmRadiusTypeEnum value) = 0;
	
	// Возвращает режим радиуса.
	virtual m3dSmRadiusTypeEnum GetRadiusType()const = 0;

	// Переменная, определяющая радиус сгиба.
	virtual mcsWorkID GetRadiusVarID() const = 0;

	// Возвращает направление загиба.
	virtual bool IsReversedDirection() const = 0;
	
	// Задает направление загиба.
	virtual void SetDirection(bool direction) = 0;

	// Задает режим освобождение угла.
	virtual void SetReleaseType(m3dSmReleaseTypeEnum value) = 0;
	
	// Возвращает режим освобождение угла.
	virtual m3dSmReleaseTypeEnum GetReleaseType() const = 0;

	// Задает режим смещения сгиба.
	virtual void SetDisplacementType(m3dSmDisplacementTypeEnum value) = 0;
	
	// Возвращает режим смещения сгиба.
	virtual m3dSmDisplacementTypeEnum GetDisplacementType() const = 0;	

	// Возвращает флаг, что построение выполняется по длине сегмента.
	virtual bool IsBySegmentLength() const = 0;
	
	// Задает флаг построения сгиба по длине сегмента.
	virtual void SetBySegmentLength(bool value) = 0;

	// Возвращает скругление зазора.
	virtual bool IsGapRound() const = 0;
	
	// Задает скругление зазора.
	virtual void SetGapRound(bool value) = 0;

	// Возвращает глубину зазора.
	virtual double GetGapDepth() const = 0;
	
	// Задает глубину зазора.
	virtual void SetGapDepth(double value) = 0;
	
	// Возвращает ширину зазора.
	virtual double GetGapWidth() const = 0;
	
	// Задает ширину зазора.
	virtual void SetGapWidth(double value) = 0;

};
//==================================================================================================

struct IMc3dSmBendOverSeg : public virtual IMc3dSmOverSegCommon
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmBendOverSeg);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmBendOverSeg, IMc3dSmOverSegCommon);
};	
//==============================================================================================	

/// Режим построения высоты.
// Значения не менять, пишутся в файл
enum m3dSmHeightTypeEnum
{
	kSmHeightType_Full     = 0, // Полная высота.
	kSmHeightType_Outside  = 1, // Высота от грани.
	kSmHeightType_Inside   = 2, // Внутренняя высота.
};
//==============================================================================================	

struct IMc3dSmJog : public virtual IMc3dSmOverSegCommon
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmJog);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmJog, IMc3dSmOverSegCommon);

	// Задает режим смещения сгиба.
	virtual void SetHeightType(m3dSmHeightTypeEnum value) = 0;
	
	// Возвращает режим смещения сгиба.
	virtual m3dSmHeightTypeEnum GetHeightType() const = 0;	

	// Возвращает флаг добавления материала при построении.
	virtual bool AddedMaterial() const = 0;
	
	// Задает флаг добавления материала при построении.
	virtual void SetAddedMaterial(bool value) = 0;	

	// Переменная, определяющая высоту подсечки.
	virtual mcsWorkID GetElevationVarID() const = 0;
};	
//==============================================================================================	

struct IMc3dSmJalousie : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmJalousie);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmJalousie, IMc3dSmFeature);

	// Устанавливает эскиз
	virtual void SetSketchID(const mcsWorkID& profileId) = 0;

	// Возвращает эскиз
	virtual mcsWorkID GetSketchID() const = 0;

	// Переменная, определяющая ширину жалюзи.
	virtual mcsWorkID GetWidthVarID() const = 0;

	// Переменная, определяющая высоту жалюзи.
	virtual mcsWorkID GetHeightVarID() const = 0;

	// Переменная, определяющая радиус жалюзи.
	virtual mcsWorkID GetRadiusVarID() const = 0;

	// Возвращает коеффициент положения нейтрального слоя.
	virtual double GetCoefficient() const = 0;
	
	// Задает коеффициент положения нейтрального слоя.
	virtual void SetCoefficient(double value) = 0;

	// Возвращает направление выдавливание жалюзи.
	virtual bool IsReversedDirection() const = 0;
	
	// Задает направление загиба.
	virtual void SetDirection(bool direction) = 0;

	// Возвращает флаг стороны отрезка, по которой строятся жалюзи.
	virtual bool IsOppositeSide() const = 0;
	
	// Задает сторону отрезка, по которой строятся жалюзи.
	virtual void SetOppositeSide(bool direction) = 0;

	// Возвращает значение указывающее на то, что построение должно выполняться по нормали.
	virtual bool IsNormToThick() const = 0;
	
	// Задает значение указывающее на то, что построение должно выполняться по нормали.
	virtual void SetNormToThick(bool direction) = 0;

	// Возвращает наличие вытяжки.
	virtual bool IsStretching() const = 0;
	
	// Задает флаг наличия вытяжки.
	virtual void SetStretching(bool direction) = 0;

	// Задает режим смещения сгиба.
	virtual void SetHeightType(m3dSmHeightTypeEnum value) = 0;
	
	// Возвращает режим смещения сгиба.
	virtual m3dSmHeightTypeEnum GetHeightType() const = 0;	
};
//==================================================================================================

// Режим высоты открытой штамповки.
// Значения не менять, пишутся в файл
enum m3dSmOpenStampHeightTypeEnum
{
	kSmOpenStampHeightType_Inside   = 0, // Внутри.
	kSmOpenStampHeightType_Outside  = 1, // Снаружи.
};
//==============================================================================================	

struct IMc3dSmStamp : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmStamp);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmStamp, IMc3dSmFeature);

	// Устанавливает профиль.
	virtual void SetProfileID(const mcsWorkID& profileId) = 0;

	// Возвращает профиль, по которым выполняется отбортовка.
	virtual mcsWorkID GetProfileID() const = 0;

	// Переменная, определяющая высоту штамповки.
	virtual mcsWorkID GetHeightVarID() const = 0;

	// Переменная, определяющая угол штамповки.
	virtual mcsWorkID GetAngleVarID() const = 0;

	// Переменная, определяющая радиус скругления эскиза.
	virtual mcsWorkID GetRadiusSketchVarID() const = 0;

	// Переменная, определяющая базовый радиус скругления.
	virtual mcsWorkID GetRadiusBaseVarID() const = 0;

	// Переменная, определяющая нижний радиус скругления.
	virtual mcsWorkID GetRadiusBottomVarID() const = 0;

	// Задает режим высоты открытой штамповки.
	virtual void SetOpenStampHeightType(m3dSmOpenStampHeightTypeEnum value) = 0;
	
	// Возвращает режим высоты открытой штамповки.
	virtual m3dSmOpenStampHeightTypeEnum GetOpenStampHeightType() const = 0;	

	// Возвращает направление выдавливание жалюзи.
	virtual bool IsReversedDirection() const = 0;
	
	// Задает направление загиба.
	virtual void SetDirection(bool direction) = 0;
	
	// Возвращает направление выдавливание жалюзи.
	virtual bool IsOpen() const = 0;
	
	// Задает направление загиба.
	virtual void SetIsOpen(bool direction) = 0;	
	
	// Возвращает флаг включения толщины.
	virtual bool IsWallInside() const = 0;
	
	// Задает флаг включения толщины.
	virtual void SetWallInside(bool direction) = 0;
};
//==================================================================================================

// Режим выдавливания обечайки.
// Значения не менять, пишутся в файл
enum m3dSmRuledExtrusionTypeEnum
{
	kSmRuledExtrusionType_Distance  = 2, // Расстояние.
	kSmRuledExtrusionType_Surface   = 3, // Поверхность.
};
//==================================================================================================

// Режим сегментирования обечайки.
// Значения не менять, пишутся в файл
enum m3dSmRuledSegmentationTypeEnum
{
	kSmRuledSegmentationType_Quantity = 0, // По количеству сегментов.
	kSmRuledSegmentationType_Length   = 1, // По длине сегментов.
	kSmRuledSegmentationType_Angle    = 2, // По углу сегмента.
	kSmRuledSegmentationType_Height   = 3, // По линейному отклонению сегмента.
};
//==================================================================================================

// Задает режим смещения зазора обечайки.
// Значения не менять, пишутся в файл
enum m3dSmGapShiftTypeEnum
{
	kSmGapShiftType_Angle        = 0, // По количеству сегментов.
	kSmGapShiftType_Length       = 1, // По длине сегментов.
	kSmGapShiftType_Ratio        = 2, // По углу сегмента.
	kSmGapShiftType_SegmentRatio = 3, // По линейному отклонению сегмента.
};
//==============================================================================================	

struct IMc3dSmRuledBase : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmRuledBase);
	IMCS_QI_METHOD_DEFINITION(IMc3dSmRuledBase, IMc3dSmFeature);

	// Устанавливает профиль.
	virtual void SetProfileID(const mcsWorkID& profileId) = 0;

	// Возвращает профиль.
	virtual mcsWorkID GetProfileID() const = 0;

	// Возвращает направления выдавливание обечайки..
	virtual bool IsOppositeDirection() const = 0;
	
	// Задает направления выдавливание обечайки..
	virtual void SetOppositeDirection(bool value) = 0;

	// Возвращает расстояние до указанной поверхности выдавливания.
	virtual double GetDistanceSurface() const = 0;
	
	// Задает расстояние до указанной поверхности выдавливания.
	virtual void SetDistanceSurface(double value) = 0;

	// Переменная, задающая толщину обейчатки.	
	virtual mcsWorkID GetThicknessVarID() const = 0;

	// Переменная, задающая радиус обейчатки.		
	virtual mcsWorkID GetRadiusVarID() const = 0;

	// Возвращает флаг направляющих боковин по нормали к линейчатой поверхности.
	virtual bool IsGuideByNorm() const = 0;
	
	// Задает  флаг направляющих боковин по нормали к линейчатой поверхности.
	virtual void SetGuideByNorm(bool value) = 0;
		
	// Возвращает флаг образующих боковин по нормали к линейчатой поверхности.
	virtual bool IsGenerByNorm() const = 0;
	
	// Задает флаг образующих боковин по нормали к линейчатой поверхности.
	virtual void SetGenerByNorm(bool value) = 0;		
	
	// Возращает режим смещения зазора обейчатки.
	virtual m3dSmGapShiftTypeEnum GetGapShiftType()  const = 0;;

	// Задает режим смещения зазора обейчатки.
	virtual void SetGapShiftType(m3dSmGapShiftTypeEnum enumElement)  = 0;;

	// Возвращает значение смещения зазора.
	virtual double GetShiftValue() const = 0;
	
	// Задает значение смещения зазора.
	virtual void SetShiftValue(double value) = 0;	
	
	// Возвращает длину контура обечайки.
	virtual double GetContourLength() const = 0;
	
	// Задает  длину контура обечайки.
	virtual void SetContourLength(double value) = 0;	
	
	// Возвращает  флаг постоянного радиуса обейчатки.
	virtual bool IsCylindricBends() const = 0;
	
	// Задает  флаг постоянного радиуса обейчатки.
	virtual void SetCylindricBends(bool value) = 0;		
	
	// Возвращает  флаг, что контура будут соединяться через вершины.
	virtual bool IsJoinByVertm() const = 0;
	
	// Задает  флаг, что контура будут соединяться через вершины.
	virtual void SetJoinByVertm(bool value) = 0;	
			
	// Возвращает значение разбиения контура обейчатки.
	virtual double GetSegmentValue() const = 0;
	
	// Задает значение разбиения контура обейчатки.
	virtual void SetSegmentValue(double value) = 0;	

	// Возращает режим сегментации обейчатки.
	virtual m3dSmRuledSegmentationTypeEnum GetSegmentationMethod() const = 0;

	// Задает режим сегментации обейчатки.
	virtual void SetSegmentationMethod(m3dSmRuledSegmentationTypeEnum enumElement) = 0;

	// Возвращает коэффициент обейчатки.
	virtual double GetCoefficient() const = 0;
	
	// Задает коэффициент обейчатки.
	virtual void SetCoefficient(double value) = 0;	

	// Возвращает  флаг сегментации обейчатки.
	virtual bool IsAllowSegmentation() const = 0;
	
	// Задает  флаг сегментации обейчатки.
	virtual void SetAllowSegmentation(bool value) = 0;

};
//==================================================================================================

struct IMc3dSmRuledSolid : public virtual IMc3dSmRuledBase
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmRuledSolid);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmRuledSolid, IMc3dSmRuledBase);

	// Возращает режим построения высоты.
	virtual m3dSmRuledExtrusionTypeEnum GetExtrusionType() const = 0;

	// Задает режим построения высоты.
	virtual void SetExtrusionType(m3dSmRuledExtrusionTypeEnum enumElement) = 0;

	// Переменная, определяющая угол обейчатки.		
	virtual mcsWorkID GetAngleVarID() const = 0;

	// Переменная, задающая высоту обейчатки.		
	virtual mcsWorkID GetHeightVarID() const = 0;

	// Возвращает зазор уклона.
	virtual double GetGapValue() const = 0;
	
	// Задает зазор уклона.
	virtual void SetGapValue(double value) = 0;
};	
//==============================================================================================	

struct IMc3dSmRuledLine : public virtual IMc3dSmRuledBase
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmRuledLine);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmRuledLine, IMc3dSmRuledBase);

	// Устанавливает второй профиль.
	virtual void SetSecondProfileID(const mcsWorkID& profileId) = 0;

	// Возвращает второй профиль.
	virtual mcsWorkID GetSecondProfileID() const = 0;

	// Переменная, задающая зазор обейчатки.		
	virtual mcsWorkID GetGapVarID() const = 0;

	// Возвращает высоту обечайки.
	virtual double GetHeight() const = 0;
	
	// Задает высоту обечайки.
	virtual void SetHeight(double value) = 0;

	// Возвращает  угол уклона.
	virtual double GetConeAngle() const = 0;
	
	// Задает  угол уклона.
	virtual void SetConeAngle(double value) = 0;
};	
//==============================================================================================	

// Задает режим создания ребра жесткости.
// Значения не менять, пишутся в файл
enum m3dSmCreateRibTypeEnum
{
	kSmCreateRibType_ByTwoSides        = 0, // По двум сторонам.
	kSmCreateRibType_BySideAndAngle    = 1, // По стороне и углу.
	kSmCreateRibType_ByDepthAndAngle   = 2, // По глубине и углу.
};
//==================================================================================================

struct IMc3dSmRib : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmRib);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmRib, IMc3dSmFeature);

	// Задает ребро для построения.
	virtual void SetEdgeID(const mcsWorkID& edgeId) = 0;

	// Возвращает ребро для построения.
	virtual mcsWorkID GetEdgeID() const = 0;

	// Переменная, определяющая позицию начала построения ребра жесткости (от 0 до 1).
	virtual mcsWorkID GetPositionVarID() const = 0;

	// Переменная, определяющая расстояние от первого ребра сгиба.
	virtual mcsWorkID GetLength1VarID() const = 0;

	// Переменная, определяющая расстояние от второго ребра сгиба.
	virtual mcsWorkID GetLength2VarID() const = 0;

	// Переменная, определяющая угол наклона профиля.
	virtual mcsWorkID GetAngleProfileVarID() const = 0;

	// Переменная, определяющая глубину профиля ребра.
	virtual mcsWorkID GetDepthProfileVarID() const = 0;

	// Переменная, определяющая глубину прогиба профиля ребра.
	virtual mcsWorkID GetDepthOfDeflectionVarID() const = 0;

	// Переменная, определяющая радиус прогиба профиля ребра.
	virtual mcsWorkID GetRadiusOfDeflectionVarID() const = 0;

	// Переменная, определяющая ширину ребра жесткости.
	virtual mcsWorkID GetThicknessVarID() const = 0;

	// Переменная, определяющая угол уклона боковых плоскостей.
	virtual mcsWorkID GetAngleVarID() const = 0;

	// Возвращает флаг направления первой стороны угла профиля.
	virtual bool IsReversedDirection() const = 0;
	
	// Задает флаг направления первой стороны угла профиля.
	virtual void SetReversedDirection(bool value) = 0;	

	// Возвращает флаг скругления выпуклой части ребра. 
	virtual bool IsAllowRibConvex() const = 0;
	
	// Задает флаг скругления выпуклой части ребра.
	virtual void SetAllowRibConvex(bool value) = 0;	

	// Возвращает флаг скругления выпуклой стороны ребра.
	virtual bool IsAllowSideConcave() const = 0;
	
	// Задает флаг скругления выпуклой стороны ребра.
	virtual void SetAllowSideConcave(bool value) = 0;	

	// Возвращает флаг прогиба профиля.
	virtual bool IsAllowProfileDeflection() const = 0;
	
	// Задает  флаг прогиба профиля.
	virtual void SetAllowProfileDeflection(bool value) = 0;
			
	// Возвращает радиус скругления выпуклой части ребра жесткости.
	virtual double GetRadiusRibConvex() const = 0;
	
	// Задает радиус скругления выпуклой части ребра жесткости.
	virtual void SetRadiusRibConvex(double value) = 0;	

	// Возвращает радиус скругления примыкания вогнутой части ребра жесткости к листовому телу.
	virtual double GetRadiusSideConcave() const = 0;
	
	// Задает радиус скругления примыкания вогнутой части ребра жесткости к листовому телу.
	virtual void SetRadiusSideConcave(double value) = 0;	

	// Возращает режим создания ребра жесткости.
	virtual m3dSmCreateRibTypeEnum GetCreateRibType() const = 0;

	// Задает режим создания ребра жесткости.
	virtual void SetCreateRibType(m3dSmCreateRibTypeEnum enumElement) = 0;			
};
//==================================================================================================

struct IMc3dSmPlate : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmPlate);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmPlate, IMc3dSmFeature);

	// Задает профиль для построения.
	virtual void SetProfileID(const mcsWorkID& edgeId) = 0;

	// Возвращает профиль для построения.
	virtual mcsWorkID GetProfileID() const = 0;

	// Переменная, определяющая ширину ребра жесткости.
	virtual mcsWorkID GetThicknessVarID() const = 0;

	// Возвращает флаг что толщина пластины совпадает с толщиной тела.
	virtual bool IsInThickness() const = 0;
	
	// Задает флаг совпадения толщины пластины с толщиной тела.
	virtual void SetInThickness(bool value) = 0;	
};
//==================================================================================================

struct IMc3dSmHole : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmHole);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmHole, IMc3dSmFeature);

	// Задает профиль для построения.
	virtual void SetProfileID(const mcsWorkID& edgeId) = 0;

	// Возвращает профиль для построения.
	virtual mcsWorkID GetProfileID() const = 0;

	// Возвращает флаг что толщина выреза совпадает с толщиной тела.
	virtual bool IsInThickness() const = 0;
	
	// Задает флаг совпадения толщины выреза с толщиной тела.
	virtual void SetInThickness(bool value) = 0;

	// Возвращает режим выреза (true - отверстие, false - пересечение).
	virtual bool IsCutting() const = 0;
	
	// Задает режим выреза (true - отверстие, false - пересечение).
	virtual void SetIsCutting(bool value) = 0;

	// Возвращает флаг обратного направление выреза.
	virtual bool IsOppositeDirection() const = 0;
	
	// Задает флаг обратного направление выреза.
	virtual void SetOppositeDirection(bool value) = 0;

	// Возвращает толщину выреза.
	virtual double GetThickness() const = 0;
	
	// Задает толщину выреза.
	virtual void SetThickness(double value) = 0;

};
//==================================================================================================

// Задает режим сечения буртика.
// Значения не менять, пишутся в файл
enum m3dSmBeadTypeEnum
{
	kSmBeadType_btRound    = 0, // Круглый.
	kSmBeadType_btVType    = 1, // V - тип.
	kSmBeadType_btUType    = 2, // U - тип.
};
//==============================================================================================	

// Задает режим окончания буртика.
// Значения не менять, пишутся в файл
enum m3dSmBeadEndTypeEnum
{
	kSmBeadEndType_betClosed    = 0, // Закрытый.
	kSmBeadEndType_betChopped   = 1, // Рубленный.
};
//==============================================================================================	

struct IMc3dSmBead : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmBead);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmBead, IMc3dSmFeature);

	// Задает эскиз для построения.
	virtual void SetSketchID(const mcsWorkID& edgeId) = 0;

	// Возвращает эскиз для построения.
	virtual mcsWorkID GetSketchID() const = 0;

	// Возвращает направление построения брутика.
	virtual bool IsReverse() const = 0;
	
	// Задает направление буртика.
	virtual void SetReverse(bool value) = 0;

	// Возвращает ширину выпуклой части буртика.
	virtual double GetBottomWidth() const = 0;
	
	// Задает  ширину выпуклой части буртика.
	virtual void SetBottomWidth(double value) = 0;

	// Возращает создания буртика.
	virtual m3dSmBeadTypeEnum GetBeadType() const = 0;

	// Задает создания буртика.
	virtual void SetBeadType(m3dSmBeadTypeEnum enumElement) = 0;

	// Возращает режим законцовки буртика.
	virtual m3dSmBeadEndTypeEnum GetEndType() const = 0;

	// Задает режим законцовки буртика.
	virtual void SetEndType(m3dSmBeadEndTypeEnum enumElement) = 0;

	// Переменная, определяющая высоту буртика.	
	virtual mcsWorkID GetHeightVarID() const = 0;

	// Переменная, определяющая радиус скругления основания буртика.
	virtual mcsWorkID GetRadiusBaseVarID() const = 0;

	// Переменная, определяющая радиус скругления дна буртика.
	virtual mcsWorkID GetRadiusBottomVarID() const = 0;

	// Переменная, определяющая угол наклона боковых стенок буртика.	
	virtual mcsWorkID GetAngleVarID() const = 0;

	// Переменная, определяющая зазор рубленой законцовки буртика.	
	virtual mcsWorkID GetGapVarID() const = 0;

};
//==================================================================================================

struct IMc3dSmFlatten : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmFlatten);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmFlatten, IMc3dSmFeature);

	// Задает грань для построения.
	virtual void SetFaceID(const mcsWorkID& edgeId) = 0;

	// Возвращает грань для построения.
	virtual mcsWorkID GetFaceID() const = 0;

	// Возвращает флаг - разогнуть тело.
	virtual bool IsUnbended() const = 0;
	
	// Задает флаг - разогнуть тело.
	virtual void SetUnbended(bool value) = 0;

	// Возвращает флаг - результат развертки  - новое тело.
	virtual bool IsBuildToSeparatePart() const = 0;
	
	// Задает флаг - результат развертки  - новое тело.
	virtual void SetBuildToSeparatePart(bool value) = 0;

	// Возвращает флаг - исключить из проекций.
	virtual bool IsExcludeFromProjections() const = 0;
	
	// Задает флаг - исключить из проекций.
	virtual void SetExcludeFromProjections(bool value) = 0;
};
//==================================================================================================

struct IMc3dSmBendCommon : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmBendCommon);
	IMCS_QI_METHOD_DEFINITION(IMc3dSmBendCommon, IMc3dSmFeature);

	// Задает неподвижную грань для построения.
	virtual void SetFaceID(const mcsWorkID& edgeId) = 0;

	// Возвращает неподвижную грань для построения.
	virtual mcsWorkID GetFaceID() const = 0;	
	
	// Возвращает грани сгиба.
	virtual bool GetBendFaceIDs(OUT mcsWorkIDArray& ids) const = 0;

	// Задает грани сгиба.
	virtual void SetBendFaceIDs(IN const mcsWorkIDArray& ids) = 0;
};
//==================================================================================================

struct IMc3dSmBend : public virtual IMc3dSmBendCommon
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmBend);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmBend, IMc3dSmBendCommon);
};
//==================================================================================================

struct IMc3dSmUnbend : public virtual IMc3dSmBendCommon
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmUnbend);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmUnbend, IMc3dSmBendCommon);
};
//==================================================================================================

// Задает режим направления построения сгиба по эскизу.
// Значения не менять, пишутся в файл
enum m3dSmJointDirectionBuildTypeEnum
{
	kSmJointDirectionBuildType_Forward      = 0, // Прямое направление.
	kSmJointDirectionBuildType_Opposite     = 1, // Обратное направление.
	kSmJointDirectionBuildType_TwoDirection = 2, // Два направления.
	kSmJointDirectionBuildType_MedianPlane  = 3, // Средняя плоскость.
};
//==============================================================================================	

// Задает режим построения сгиба по эскизу.
// Значения не менять, пишутся в файл
enum m3dSmJointConstructionTypeEnum
{
	kSmJointConstructionType_cmByWidth     = 1, // Прямое направление.
	kSmJointConstructionType_cmByManyEdges = 2, // Обратное направление.
};
//==============================================================================================	

struct IMc3dSmJointBend : public virtual IMc3dSmCornerProcessing, virtual IMc3dSmBendRelease
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmJointBend);
	IMCS_QI_METHOD_DEFINITION3(IMc3dSmJointBend, IMc3dSmCornerProcessing, IMc3dSmBendRelease);

	virtual const GUID& getClassID() const {return __uuidof(IMc3dSmJointBend);}

	// Устанавливает эскиз
	virtual void SetSketchID(const mcsWorkID& profileId) = 0;

	// Возвращает эскиз
	virtual mcsWorkID GetSketchID() const = 0;

	// Задает список рёбер, по которым нужно выполнить сгиб
	virtual void SetSequenceEdgesIDs(IN const mcsWorkIDArray& idsEdges) = 0;

	// Возвращает список ребер, по которым выполнен сгиб
	virtual bool GetSequenceEdgesIDs(OUT mcsWorkIDArray& idsEdges) const = 0;

	// Возвращает коеффициент положения нейтрального слоя.
	virtual double GetCoefficient() const = 0;

	// Задает коеффициент положения нейтрального слоя.
	virtual void SetCoefficient(double value) = 0;

	// переменная, определяющая радиус сгибов
	virtual mcsWorkID GetRadiusVarID() const = 0;

	// Задает режим радиуса.
	virtual void SetRadiusType(m3dSmRadiusTypeEnum radiusType) = 0;
	
	// Возвращает режим радиуса.
	virtual m3dSmRadiusTypeEnum GetRadiusType()const = 0;

	// Задает режим построения сгиба.
	virtual void SetDirectionBuildType(m3dSmJointDirectionBuildTypeEnum radiusType) = 0;
	
	// Возвращает режим построения сгиба.
	virtual m3dSmJointDirectionBuildTypeEnum GetDirectionBuildType()const = 0;

	// Задает режим направления сгиба.
	virtual void SetConstructionType(m3dSmJointConstructionTypeEnum value) = 0;
	
	// Возвращает режим направления сгиба.
	virtual m3dSmJointConstructionTypeEnum GetConstructionType()const = 0;	
	
	// Возвращает расстояние смещения сгиба в начале.
	virtual double GetDistanceBegin() const = 0;

	// Задает расстояние смещения сгиба в начале.
	virtual void SetDistanceBegin(double value) = 0;
	
	// Возвращает расстояние смещения сгиба в конце.
	virtual double GetDistanceEnd() const = 0;

	// Задает расстояние смещения сгиба в конце.
	virtual void SetDistanceEnd(double value) = 0;	
};
//==================================================================================================

struct IMc3dSmCorner : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmCorner);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmCorner, IMc3dSmFeature);
	
	// Задает список рёбер, по которым нужно выполнить замыкание углов
	virtual void SetEdgeIDs(IN const mcsWorkIDArray& idsEdges) = 0;

	// Возвращает список ребер, по которым выполнено замыкание углов
	virtual bool GetEdgeIDs(OUT mcsWorkIDArray& idsEdges) const = 0;

	// Возвращает флаг - замыкание с продолжением.
	virtual bool IsProlong() const = 0;
	
	// Задает флаг - замыкание с продолжением.
	virtual void SetProlong(bool value) = 0;

	// Возвращает флаг - перекрывающая сторона.
	virtual bool IsOverlapSide() const = 0;
	
	// Задает флаг - перекрывающая сторона.
	virtual void SetOverlapSide(bool value) = 0;

	// Переменная, задающая зазор обейчатки.		
	virtual mcsWorkID GetGapVarID() const = 0;

	// Задает режим замыкания углов в начале.
	virtual void SetCornerType(m3dSmCloseCornerTypeEnum enumElement) = 0;

	// Возвращает режим замыкания углов в начале.
	virtual m3dSmCloseCornerTypeEnum GetCornerType() const = 0;

	// Задает режим обработки углов в начале.
	virtual void SetBendsType(m3dSmCloseBendsTypeEnum enumElement) = 0;

	// Возвращает режим обработки углов в начале.
	virtual m3dSmCloseBendsTypeEnum GetBendsType() const = 0;
};
//==================================================================================================

// Задает режим окончания буртика.
// Значения не менять, пишутся в файл
enum m3dSmJumpingTypeEnum
{
	kSmJumpingType_Final             = 0, // Конечный.
	kSmJumpingType_Symmetric         = 1, // Симметрично.
	kSmJumpingType_FullInitialEdge   = 2, // Полное начальное ребро.
	kSmJumpingType_FullFinalEdge     = 3, // Полное конечное ребро.
	kSmJumpingType_FullBothEdges     = 4, // Полные оба ребра.
};
//==============================================================================================	

struct IMc3dSmJumping : public virtual IMc3dSmFeature
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMc3dSmJumping);
	IMCS_STD_METHOD_DEFINITION(IMc3dSmJumping, IMc3dSmFeature);
	
	// Задает список рёбер, по которым нужно построить перемычку
	virtual void SetEdgeIDs(IN const mcsWorkIDArray& idsEdges) = 0;

	// Возвращает список рёбер, по которым нужно построить перемычку
	virtual bool GetEdgeIDs(OUT mcsWorkIDArray& idsEdges) const = 0;

	// Возвращает коеффициент положения нейтрального слоя.
	virtual double GetCoefficient() const = 0;

	// Задает коеффициент положения нейтрального слоя.
	virtual void SetCoefficient(double value) = 0;
	
	// Возвращает длину добавочной пластины от ребра до сгиба.
	virtual double GetLength() const = 0;

	// Задает длину добавочной пластины от ребра до сгиба.
	virtual void SetLength(double value) = 0;

	// Возвращает ширину перемычки.
	virtual double GetWidth() const = 0;

	// Задает ширину перемычки.
	virtual void SetWidth(double value) = 0;

	// Возвращает сдвиг.
	virtual double GetShift() const = 0;

	// Задает сдвиг.
	virtual void SetShift(double value) = 0;

	// Возвращает радиус загибов.
	virtual double GetRadius() const = 0;

	// Задает радиус загибов.
	virtual void SetRadius(double value) = 0;

	// Возвращает флаг изменения направления построения
	virtual bool IsReversedDirection() const = 0;
	
	// Задает флаг изменения направления построения
	virtual void SetDirection(bool direction) = 0;

	// Задает режим построения перемычки.
	virtual void SetJumpingType(m3dSmJumpingTypeEnum enumElement) = 0;

	// Возвращает построения перемычки.
	virtual m3dSmJumpingTypeEnum GetJumpingType() const = 0;
};
//==================================================================================================

#pragma endregion // SM features
//==================================================================================================

#if !defined(_NCAD_BUILD_) && !defined(_MCS_CORE_ONLY)
	#include "3DCoreInternal.h"
#endif
