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

#include "mtdib.h"

static const POINT    POINT_NULL    = {-12345, -12345};

//==============================================================================
enum McPainterOverlayTypeEnum
{
	kMcPainterOverlayType_Auto           = -1, // detects overlay type according to current platform
	kMcPainterOverlayType_Unknown        = 0,
	kMcPainterOverlayType_OverDCNonBuf   = 1, // host then client directly to DC
	kMcPainterOverlayType_OverDCBuffered = 2, // host then client using memory buffer
	kMcPainterOverlayType_Exclusive      = 3, // only client (bkgnd color used)
	kMcPainterOverlayType_ExclusiveWPF   = 4, // if kMcPainterOverlayType_Exclusive doesn't work and a window relates to WPF, use this value
};
//==============================================================================
enum McPainterDrawingModeEnum
{
	kMcPainterDrawingMode_Auto      = -1, // detects drawing mode type according to current platform
	kMcPainterDrawingMode_Unknown   =  0,
	kMcPainterDrawingMode_GDI       =  1, // draws using GDI functionality (optimal for 2D drawing)
	kMcPainterDrawingMode_OpenGL    =  2, // draws using OpenGL
	kMcPainterDrawingMode_D3D       =  4, // draws using Direct3d
	kMcPainterDrawingMode_for3d     =  kMcPainterDrawingMode_OpenGL|kMcPainterDrawingMode_D3D, // for any available 3d drawing
};
//==============================================================================
IMCS_DECL_INTERFACE(IMc3DGraphicsNode, "10000FFF-0001-AAAA-AAAA-050B00000000")
typedef McsArray<IMc3DGraphicsNodePtr,IMc3DGraphicsNode*> IMc3DGraphicsNodesArray;
//==============================================================================
struct PainterObjGeomData
{
	IMcEntityPtr    mpE;
	bool            mfUseModifiedCache;
	mcsGeomEntArray mModifiedCache;
	IMcPainter*     mpThis;
};
//==============================================================================
// сообщение посылвается пайнтером через колбэк, установленный методом IMcPainter::SetCallBack
// посылается перед тем, как кэш объекта геометрии для рисования будет взят в обработку пайнтером,
// если кэш был модифицирован колбыком, то в структуре PainterObjGeomData нужно взвести флаг mfUseModifiedCache,
// тогда пайнтер будет использовать mModifiedCache вместо mpE->m_DrawCache
#define PM_PROCESS_OBJECT_DRAWCACHE 0x4E00 // fBefore=true; wParam=0; lParam: IN/OUT (PainterObjGeomData*); lResult unused
//==============================================================================
// пример:
// параметр <fBefore> определяет, до (true) или после идет обработка 
// сообщения к окну, с которым ассоциирован Painter;
// <lResult> - это результат обработки сообщения Painter-ом,
// если нужно переопределить обработку, то на вызов "до" нужно указать 
// результат <lResult>, и вернуть <false>, если вызов идет "после", то параметр
// <lResult> содержит код возврата, который приготовил Painter, его можно 
// поменять, код возврата в этом случае не имеет значения
// <exData> используется для передачи дополнительных данных, 
// например указателя на вспомогательный класс/структуру

// Если вернуть false при fBefore == true, то блокируется обработка сообщений самим Painter,
// это позволяет полностью выполнить обработку сообщения в CallBack

typedef bool (__stdcall* PainterNCBProc) (
	IMcPainter* pPainter,
	HWND        hWnd,
	UINT        msgCode,
	WPARAM      wParam,
	LPARAM      lParam,
	bool        fBefore,
	LRESULT&    lResult,
	LPARAM      exData);
	
//=============================================================================
IMCS_DECL_INTERFACE(IMcPainterCallback, "2B570F3E-A0CB-4CEE-9C71-FF00067EA144");
struct IMcPainterCallback : public virtual IMcObject
{
public:
	IMCS_STD_METHOD_DEFINITION(IMcPainterCallback, IMcObject);

	// Если вернуть false при fBefore == true, то блокируется обработка сообщений самим Painter,
	// это позволяет полностью выполнить обработку сообщения в CallBack.
	// Остальное описание см. выше к PainterNCBProc.

	virtual bool PainterProc(
		IMcPainter* pPainter,
		HWND        hWnd,
		UINT        msgCode,
		WPARAM      wParam,
		LPARAM      lParam,
		bool        fBefore,
		LRESULT&    lResult) = 0;
};

//==============================================================================
enum PainterPickingCacheEnum;
class CxImage;
//==============================================================================
struct IMcPainter : public virtual IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMcPainter, IMcObject);

	virtual HRESULT Init(
		IN IMcsNativeView* pView,
		IN McPainterOverlayTypeEnum overlay=kMcPainterOverlayType_Auto,
		IN McPainterDrawingModeEnum drawMode=kMcPainterDrawingMode_Auto) = 0;

	virtual HRESULT Init(
		IN HWND hWndTarget,
		IN McPainterOverlayTypeEnum overlay=kMcPainterOverlayType_Auto,
		IN McPainterDrawingModeEnum drawMode=kMcPainterDrawingMode_Auto,
		IN OPTIONAL bool fForceRenderToWnd4GL=false) = 0;

	virtual HRESULT Reset() = 0; // destroys painting context
	virtual HRESULT SetCallBack(IN PainterNCBProc, IN LPARAM exData) = 0;
	virtual HRESULT SetCallBack(IMcPainterCallback* pCallback) = 0;

	virtual HRESULT RemoveObject(IN const mcsWorkID& ObjID) = 0;
	virtual HRESULT RemoveObjects(IN const mcsWorkIDArray ObjIDs) = 0;
	virtual HRESULT RemoveAllCustom() = 0;
	virtual HRESULT RemoveAll3dNodes() = 0;
	virtual HRESULT RemoveAllImages() = 0;
	virtual HRESULT RemoveAll() = 0;

		// удаляет набор пользовательской графики, для которого был назначен ID,
		// или такого набора нет, то ничего не произойдет;
		// если указать WID_NULL, удаляется вся пользовательская графика без,
		// которая задана без идентификации
	virtual HRESULT RemoveCustom(IN const mcsWorkID& CustomGrpID) = 0;

		// объекты могут учавствовать в селекции монитором, 
		// при этом пока селектироваться будет весь объект
	virtual HRESULT AddObject(IN const mcsWorkID& ObjID) = 0;
	virtual HRESULT AddObjects(IN const mcsWorkIDArray& ObjIDs) = 0;
	virtual HRESULT AddCustom(IN const McsEntityGeometry& EntGeom,IN OPTIONAL bool fForceSizeInPixels=false) = 0;
	virtual HRESULT AddCustom(IN const mcsGeomEntArray& entities,IN OPTIONAL bool fForceSizeInPixels=false) = 0;

		// позволяет добавить идертифицируемый набор произвольной графики с 
		// возможностью назначить размер в пикселах относительно указанной точки;
	virtual HRESULT AddCustom(
		IN OPTIONAL const mcsWorkID& geArrAssocID, // may be NULL
		IN const mcsGeomEntArray& entities,
		IN OPTIONAL bool fPixelSize = false,
		IN OPTIONAL const mcsPoint& constSizeScalePt = mcsPoint::kOrigin) = 0;

	virtual HRESULT AddCustom(
		IN OPTIONAL const mcsWorkID& geArrAssocID, // may be NULL
		IN const McsEntityGeometry& EntGeom,
		IN OPTIONAL bool fPixelSize = false,
		IN OPTIONAL const mcsPoint& constSizeScalePt = mcsPoint::kOrigin) = 0;

		// если внутри картинки находятся GL изображения, то 
	virtual HRESULT AddImage(CxImage& Image) = 0;

		// устанавливает размер в пикселах для указанной группы пользовательской графики
	virtual HRESULT SetPixelsSize(IN const mcsWorkID& idCustomGrp, const mcsPoint& scalePt) = 0;

		// устанавливает размер в мировых попугаях для указанной группы пользовательской графики;
		// обратная операция для <SetPixelsSize>
	virtual HRESULT SetWoldParrotSize(IN const mcsWorkID& idCustomGrp) = 0;

		// painter must be initialized for exclusive overlay drawing mode;
		// 3D GL images can be saved/loaded only for OGL initialized painters;
		// also stores current camera position;
		// if scene must be appended to current then camera position will not be loaded;
		// if <fSaveObjectsByIDs> is false then exact geometry and images will be saved 
		// for all objects in painter, otherwise only ID and nothing more
	virtual HRESULT saveScene(IMcsStream* pS, bool fSaveObjectsByIDs = false) = 0;
	virtual HRESULT loadScene(IMcsStream* pS, bool fReplaceCurrentScene = true, bool fCheckContentTag = true) = 0;
	virtual HRESULT saveSceneToFile(LPCTSTR cstrFileName, bool fCompressed = true, bool fSaveObjectsByIDs = false) = 0;
	virtual HRESULT loadSceneFromFile(LPCTSTR cstrFileName, bool fReplaceCurrentScene = true) = 0;

	virtual HRESULT Create3dGraphicsNode(IN EntityGeometryTypeEnum geometryType, OUT IMc3DGraphicsNodePtr& pNode) = 0;
	virtual IMc3DGraphicsNodePtr Get3dGraphicsNodeByID(IN const mcsWorkID& idNode) = 0;
	virtual HRESULT Get3dGraphicsNodesByID(IN const mcsWorkIDArray& idNodes, OUT IMc3DGraphicsNodesArray& nodes) = 0;

		// вызывающая сторона должна гарантировать, что пайнтер будет существовать 
		// все время жизни полученного монитора, т.е. монитор должен быть отпущен
		// раньше, чем уничтожен пайнтер
	virtual HRESULT GetEntityMonitor(OUT IEMPtr&) = 0;

		// выполняет селекцию примитивов (объектов и идентифицированных Mc3dImage 
		// в указанной точке с указанной апертурой;
		// Если оба - pIds или pObjects не указаны, то вызов будет холостым.
		// возможна единичная селекция, в этом случае будет выдан объект, который
		// находится ближе всего к наблюдателю и к указанной точке экрана;
		// если далее нужна коррекция объекта, например Mc3dImage, то можно 
		// "попросить" указатели <pObjects>, и напрямую изменить например цвет 
		// подсветки;
		// Если <pPickingCache> не указан, то будет использован временный кэш типа
		// kPPC_Component. Кэш множо получит явно методом <GetPickingCache>,
		// см. дополнительные комментарии к множеству <PainterPickingCacheEnum>;
		// если выбираемые элементы меняются, то нужно переполучить кэш, иначе 
		// достаточно одного вызова на сеанс селекции.
		// !! возвращаемый EntityMonitor использует кэш без обновления (пока),
		// т.е. при входе в GetEntity кэш формируется, при выходе удаляется;
		// поскольку параметров много и они опциональны, и добавляются по ходу дела, то
		// для определенности умолчания закомментированы для снятия неопределенности уже
		// написанного кода;
	virtual HRESULT GetEntitiesByPoint(
		OUT OPTIONAL mcsWorkIDArray* pIds = NULL,
		OUT OPTIONAL mcObjectsArray* pObjects = NULL,
		IN OPTIONAL  IMcObject*      pPickingCache = NULL,
		IN OPTIONAL  bool            fSingleNearest = true,
		IN OPTIONAL  const POINT&    DCPoint = POINT_NULL, // if missed then current mouse pos will be taken
		IN OPTIONAL  int             apertureRadius_pix = 2) = 0;

		// выдает объект, с помощью которого далее можно выполнять селекцию объектов,
		// см. комментарии к <PainterPickingCacheEnum>
	virtual IMcObjectPtr GetPickingCache(IN PainterPickingCacheEnum selSet) = 0;

		// метод внутри добавляет в кэш фильтр объектов для селекции;
		// использовать нужно примерно так:
		// - получаем предварительно два кэша - один по деталям, а второй 
		//   детализированный, но, во втором должна быть информация о том, к какую
		//   деталь входит конкретное изображение
		// - выполняем селекцию по деталям (по первому кэшу)
		// - по полученному набору деталей вызываем этот метод со вторым кэшкм;
		// весь смысл в ускорении детализированной селекции на больших сценах;
		// <prentSetType> указывает на множество;
		// если указан <pParentPickingCache>, то множество на которое ссылается массив 
		// входных ИД будет выбираться из заданного кэша, это используется совместно
		// с промежуточным кэшем селекции <kPPC_L21>
	virtual HRESULT FilterPickingCache(
		IN const mcsWorkIDArray& idsParentFilter,
		IN OPTIONAL IMcObject*   pParentPickingCache, // = NULL
		IN OUT IMcObject*        pChildrenPickingCache) = 0;

		// удалаяет дополнительный фильтр из кэша селекции
	virtual HRESULT RemoveFilterFromPickingCache(IN OUT IMcObject* pPickingCache) = 0;

		// выдает указатель на объект или Mc3dImage,
		// если таковые зарегистрированы для отрисовки
	virtual IMcObjectPtr getEntityByID(IN const mcsWorkID& ID) = 0;

	virtual HRESULT highlightByID(IN const mcsWorkID& ID) = 0;
	virtual HRESULT unhighlightByID(IN const mcsWorkID& ID) = 0;
	virtual HRESULT unhighlightAll() = 0;

	// query helpers
	virtual IMcsNativeViewPtr getAssocNativeView() = 0; // returns associated native view
	virtual HWND    getAssocWnd() = 0;
	virtual double  getPixelSizeInWorld() = 0; // returns current size of pixel in world space

		// repaints model
		// <fForceUpdate> указывает на то, что нужно принудительно перестроить сцену,
		// даже если ее составляющие не менялись извне (но не картинку в окне);
		// если <fRedrawRightNow> включен, то перерисовка будет выполнена по выходу 
		// из этого метода, если нет, то просто выполняется обычный запрос WM_PAINT
		// в очередь сообщений, перерисовка произойдет в момент, которые определяется
		// правилами обработки сообщений WM_PAINT из очереди сообщений;
	virtual HRESULT Update(IN OPTIONAL bool fForceUpdate=false, bool fRedrawRightNow = true) = 0;

		// gets <true> if model in painter was modified and not updated for preview
	virtual bool    requiresUpdate() = 0;

		// sets "dirty" status of model in preview
	virtual void    setRequiresUpdate(bool fRU) = 0;
		// Draws contents into new metafile, 
		// if no file specified, memory enh will be created.
		// ! NOTE: on success caller is responsible to destroy ENH handle and file

	virtual HRESULT GetEMF(OUT HENHMETAFILE& enh, IN OPTIONAL LPCTSTR enfFilePath=NULL) = 0;

	virtual HRESULT GetCxImage(
		OUT         CxImage& overallImage,
		IN OPTIONAL int      cx = 70,
		IN OPTIONAL int      cy = 70, 
		IN OPTIONAL double   tdImagesTol_mm = -1,
		IN OPTIONAL int      frame_pix = 2 // отступ от краёв
		) = 0;

		// gets/puts internal transformation matrix, only for exclusive overlay type
	virtual HRESULT getWorldToDCTfm(OUT mcsMatrix& tfm_Wld2DC) = 0;
	virtual HRESULT getDCToWorldTfm(OUT mcsMatrix& tfm_DC2Wld) = 0; // only for parallel projections, E_FAIL result will be otherwise

	virtual HRESULT getWorldTfm(OUT mcsMatrix& tfm) = 0; // матрица предварительного поворота, сдвига и масштабирования сцены
	virtual HRESULT putWorldTfm(IN const mcsMatrix& tfm) = 0;

		// единичные преобразования точки из экранных координат в мировые и обратно;
		// методы незаменимы при перспективных проекциях, когда нет возможности выразить 
		// преобразования в виде мтрицы для любой точки пространства
	virtual HRESULT tfmW2DC(IN const mcsPoint& modelPt,OUT POINT& DCPt) = 0;
	virtual HRESULT tfmDC2W(IN const POINT& DCPt, OUT mcsPoint& modelPt) = 0;

		// method sets central projection mode for exclusive painting
	virtual HRESULT setProjectionData(
		double viewAngle_deg, // if angle is 0 then parallel projection will be used
		const mcsPoint& eye, 
		const mcsVector& fwDirection,
		const mcsVector& upDirection) = 0;

	virtual HRESULT getProjectionData(
		OUT double& viewAngle_deg, 
		OUT mcsPoint& eye, 
		OUT mcsVector& fwDirection,
		OUT mcsVector& upDirection) = 0;

	// for exclusive HWND painting
	virtual HRESULT FitAll(IN OPTIONAL int deflateFrameWidth_pixels=2, IN OPTIONAL int frameWidth=-1, IN OPTIONAL int frameHeight=-1) = 0;

	// if second parameter is different to its default value then gradient background 
	// will be applied, but now only for exclusive OpenGL drawing.
	// In this case the preview image from painter will take middle color
	virtual HRESULT SetBkColor(IN COLORREF topOrSingleColor, IN COLORREF bottomColor = COLORREF_SPEC_VAL) = 0;

		// Sets or resets 3D navigation mode, it allows to rotate scene in 3D, 
		// coordsys color triad also will be displayed
	virtual HRESULT Set3DNavMode(bool f3DModeOn)
		{return _ioctl(1008, (LPVOID)f3DModeOn);}

		// GetCxImage will keep weight of lines in EMF, works ONCE per call to GetCxImage
	virtual HRESULT KeepLineweight4EMF()
		{return _ioctl(1013);}

		// Sets height in pixels of mcsText items for GDI mode
	virtual HRESULT SetTextH4GDI(int textH_pix)
		{return _ioctl(1014, (LPVOID)(INT_PTR)textH_pix);}

	// INTERNAL HOLE: do everything without interface changes
	virtual HRESULT _ioctl(IN DWORD idOperation,IN OPTIONAL void* pData=NULL) = 0;

		// 18.02.2011, AGL
		// устанавливает пороги превращения попугайной толщины линии в пиксельную,
		// последний аргумент должен быть 0 !
		// пример вызова setLineWidthThresholds(40, 100, 120, 0);
		// означает, что от 0 до 40 будет 1 пиксель, от 40 до 100 - 2, от 100 до 120 - 3, выше 120 - 4
	virtual HRESULT setLineWidthThresholds(int pix1_threshold, ...) = 0;
		// 03.10.2017, BigAlex
		// Метод, не требующий последнего 0 в списке аргументов.
	virtual HRESULT setLineWidthThresholds(const mcsIntArray& arrPixThresholds) = 0;

		// INTERNAL: used by gate to allow binding nodes to existing graphics
		// pass NULL for pNodes to indicate store all 3d contained 3d nodes
	virtual HRESULT _3dSaveToGraphicsContext(IN OPTIONAL IMc3DGraphicsNodesArray* pNodes, IN OUT IMcsStream* pGraphicsContext) = 0;
	virtual HRESULT _3dLoadFromGraphicsContext(IN IMcsStream* pGraphicsContext, OUT OPTIONAL IMc3DGraphicsNodesArray* pNodes=NULL) = 0;

	// returns <true> if contained graphics is kept between command sessions
	virtual HRESULT setPermanent(bool fPermanent) = 0;
	virtual bool    isPermanent() = 0;

		// painter must be in GDI drawing mode (OGL(+mixed) / BITMAP / metafile not allowed)
		// coordinates of entities is in model space, all system colors applied
	MCTYP_API static HRESULT getEntitiesToDraw(IN HWND hWndView, OUT mcsGeomEntArray& gearr);
		// two methods below can be used only with GDI drawing type
		// while painter is in manual draw; 
		// number of calls to <enter...> must be equal to <exit...> calls
	MCTYP_API static DWORD enterManualDraw(IN HWND hWndView); // increments draw lock counter
	MCTYP_API static DWORD exitManualDraw(IN HWND hWndView); // decrements draw lock counter
};
//=================================================================================

MCTYP_API IMcPainterPtr mcsCreatePainter();

//=================================================================================

#if !defined(_NCAD_BUILD_) && !defined(_MCS_CORE_ONLY)
	#include "IMcPainterInternal.h"
#endif
//===========================================================================
