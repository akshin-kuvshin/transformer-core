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

#include <objbase.h>
#include <atlbase.h>
#include <comutil.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "MCSTypes.h"
#include "McsTempl.h"
#include "McsGeometry.h"
#include "DynLoadMacro.h"
#include "McsVariant.h"
#include "IMcStream.h"
#include "IMcObjects.h"
#include "IMcPainter.h"
#include "MechMath.h"
#include "DynLoadMacro.h"

#pragma comment(lib,"COMSUPP.LIB")


//===========================================================================
// added for easy synchronization of interface <-> implementation 
#ifndef NOTIMPL_ALERT
  #define NOTIMPL_ALERT(str) MESSAGE_FMT_A("Method " str " is not implemented",DBMON_FONT_DEFAULT, RGB(80,0,0)); return E_NOTIMPL;
#endif

#ifndef NOTIMPL_ALERT2
  #define NOTIMPL_ALERT2(str,ret) MESSAGE_FMT_A("Method " str " is not implemented",DBMON_FONT_DEFAULT, RGB(80,0,0)); return ret;
#endif

//===========================================================================
struct McsConstraintData;
struct IMcs3dConstraintsManager;
struct IMcs2dConstraintsManager;
struct IMcsTransactionManager;
struct MCS_Hole;
struct IMcsTTManager;

typedef MObjPtr<IMcs3dConstraintsManager> IMcs3dConstraintsManagerPtr;

enum Mc3dConstraintTypeEnum;
//===========================================================================
enum McsViewRenderModesEnum
{
	kMcsViewRenderMode_Unk              = 0,
	kMcsViewRenderMode_Optimized2d      = 1, // edges
	kMcsViewRenderMode_Wire             = 2, // edges and wire
	kMcsViewRenderMode_FaceDraft        = 3, // draft (fast) faces, no edges
	kMcsViewRenderMode_FaceFine         = 4, // nice faces, no edges
	kMcsViewRenderMode_FaceNEdgeDraft   = 5, // draft (fast) faces and edges
	kMcsViewRenderMode_FaceNEdgeFine    = 6, // nice faces and edges
	kMcsViewRenderMode_NoHiddenLines    = 7, // hidden lines are removed
};
//===========================================================================

struct McCameraData
{
	mcsPoint  eye, target;
	mcsVector upDir;
	bool      bPerspective;
	double    scaleOrAngle; // Для параллельной проекции - масштаб, для перспективной - угол зрения в радианах (Field of view).

	MCTYP_API McCameraData();

	MCTYP_API mcsVector lookDir() const;
};
//===========================================================================

struct IMcsNativeView : public virtual IMcObject
{
	IMCS_QI_METHOD_DEFINITION(IMcsNativeView, IMcObject);
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcsNativeView);

	//.........................................................
	// view transformation methods,
	// each method must be implemented, because any one can't be replaced by another

	// world -> DC (DC has (0,0) at then left-top corner of the window!)
	virtual HRESULT tfmW2DC(IN const mcsPoint& modelPt_mm,OUT POINT& DCPt) {
		DCPt.x = 0; DCPt.y = 0;
		NOTIMPL_ALERT("IMcsNativeView::tfmW2DC");
	}

	// DC ->world 
	virtual HRESULT tfmDC2W(IN const POINT& DCPt, OUT mcsPoint& modelPt_mm) {
		modelPt_mm.set(0,0,0);
		NOTIMPL_ALERT("IMcsNativeView::tfmDC2W");
	}

	// get matrix for orthogonal projection from world to DC 
	// Note: perspective mode has no such, error must be returned
	virtual HRESULT getWorldToDC(OUT mcsMatrix& tfm_Wld2DC_mm) {
		tfm_Wld2DC_mm.setToIdentity();
		NOTIMPL_ALERT("IMcsNativeView::getWorldToDC");
	}

	// get matrix for orthogonal projection from DC to world
	// Note: perspective mode has no such, error will be returned
	virtual HRESULT getDCToWorld(OUT mcsMatrix& tfm_DC2Wld_mm) {
		tfm_DC2Wld_mm.setToIdentity();
		NOTIMPL_ALERT("IMcsNativeView::getDCToWorld");
	}

	// return viewing camera parameters
	virtual HRESULT getCamera(
		OUT mcsPoint&  Eye_mm, 
		OUT mcsPoint&  Target_mm, 
		OUT mcsVector& UpDir,
		OUT bool&      fPerspective,
		OUT double&    scaleOrAngle) // Для параллельной проекции - масштаб, для перспективной - угол зрения в радианах (Field of view).
	{
		NOTIMPL_ALERT("IMcsNativeView::getCamera");
	}

	// Метод устанавливает параметры видовой камеры.
	// scaleOrAngle = угол поля зрения (в радианах) в перспективном режиме и масштаб в ортогональном режиме.
	// Внимание: передавайте scaleOrAngle = 0 при переключении между ортогональным и перспективными режимами
	// в случаях, когда величина угла/масштаба в новом режиме неизвестна.
	virtual HRESULT setCamera(
		IN const mcsPoint&  Eye_mm,
		IN const mcsPoint&  Target_mm,
		IN const mcsVector& UpDir,
		IN bool             fPerspective,
		IN double           scaleOrAngle,
		IN OPTIONAL bool    bZoomAll = false)
	{
		NOTIMPL_ALERT("IMcsNativeView::setCamera");
	}

		// возвращает размер пикселя в единицах измерения документа для указанной точки пространства;
		// точка нужна для центральной (перспективной) проекции, для параллельной проекции
		// размер пикселя одинаков в любой точке пространства
	MCTYP_API virtual double getPixelSize(IN const mcsPoint& pt = mcsPoint::kOrigin);

	virtual double getAperture(IN const mcsPoint& pt = mcsPoint::kOrigin)
		{ return getPixelSize(pt); }

	//.........................................................
	// ensure that specified object will be visible
	// rScale коэффицент от 0 до 1, определяет отношение баунда объекта к размеру видового экрана
	// 0 - без увеличения, 1 - растянуть объект на весь экран
	virtual HRESULT makeObjectVisible(IN const mcsWorkID& id, IN double rScale = 0.4)
		{NOTIMPL_ALERT("IMcsNativeView::makeObjectVisible");}

	//.........................................................
	// ensure that specified object will be visible
	virtual HRESULT makeObjectsVisible(IN const mcsWorkIDArray& ids, IN double rScale = 0.4)
		{NOTIMPL_ALERT("IMcsNativeView::makeObjectsVisible");}

	// ensure that specified object will be visible
	virtual HRESULT makeBoundVisible(IN const mcsBoundBlock& blk, IN double rScale = 0.4)
		{NOTIMPL_ALERT("IMcsNativeView::makeBoundVisible");}

	// rScale > 1 - zoom in, 0 < rScale < 1 - zoom out
	virtual HRESULT zoom(IN double rScale)
		{NOTIMPL_ALERT("IMcsNativeView::zoom");}

	virtual bool    isPerspective() 
		{NOTIMPL_ALERT2("IMcsNativeView::isPerspective", false);}

	virtual HRESULT update()
		{NOTIMPL_ALERT("IMcsNativeView::update");}

	// returns HWND of the window where actual drawing are being
	virtual HWND    getViewHWND() 
		{NOTIMPL_ALERT2("IMcsNativeView::getViewHWND", NULL);}

	virtual COLORREF getBlackWhiteColor()
		{NOTIMPL_ALERT2("IMcsNativeView::getBlackWhiteColor", 0);}

	virtual mcsWorkID getDocID()
		{NOTIMPL_ALERT2("IMcsNativeView::getDocID", WID_NULL);}

	virtual McsViewRenderModesEnum getViewRenderMode()
		{NOTIMPL_ALERT2("IMcsNativeView::getViewRenderMode", kMcsViewRenderMode_Wire);}

	virtual HRESULT setViewRenderMode(McsViewRenderModesEnum newViewMode)
		{NOTIMPL_ALERT("IMcsNativeView::setViewRenderMode");}

	MCTYP_API virtual HRESULT getCamera(OUT McCameraData& camData);
	MCTYP_API virtual HRESULT setCamera(IN const McCameraData& camData, IN OPTIONAL bool bZoomAll = false);

	virtual HRESULT zoomAll()
		{NOTIMPL_ALERT("IMcsNativeView::zoomAll");}
};
//===========================================================================

struct IMcsMemoryView : virtual IMcObject
{
	IMCS_QI_METHOD_DEFINITION(IMcsMemoryView, IMcObject);
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcsMemoryView);

	// docId - документ, чью модель нужно рисовать.
	// 
	// bUseGsModel - Если true, будет использоваться оптимизация на основе существующей графической модели.
	//    Не использовать для получения единичного кадра. Если true, то после завершения получения кадров
	//    нужно позвать метод Finish().
	//
	// width, height - размер кадра
	//
	virtual HRESULT Init(const mcsWorkID& docId, bool bUseGsModel, DWORD width, DWORD height) = 0;

	// Установка ориентации камеры в виде
	virtual HRESULT SetCamera(const McCameraData& camData) = 0;

	// Получить кадр.
	// При последовательных вызовах будет возвращаться один и тот же bitmap. Вернет NULL в случае ошибки.
	virtual HBITMAP Draw() = 0;

	// В случае, если используется метод Init с флагом bUseGsModel = true, по окончании рисования нужно позвать этот метод,
	// чтобы восстановить графику в основном видовом окне.
	virtual HRESULT Finish() = 0;
};
//===========================================================================


//===========================================================================
// manager supports multilevel transactions;
// manager is permanent so there is no need to AddRef or Release it 
// (like IInventorGate interface)
struct IMcsTransactionManager
{
  virtual HRESULT StartTransaction(IN LPCTSTR pTransactionName = NULL)
    {return E_NOTIMPL;}

  virtual HRESULT AbortTransaction()
    {return E_NOTIMPL;}

  virtual HRESULT EndTransaction()
    {return E_NOTIMPL;}

  virtual HRESULT UpdateGraphics() // flush all objects from transaction without it's ending
    {return E_NOTIMPL;}

  // returns number of opened transaction levels
  // generally need for INV platform to detect whether the out-of command 
  // changes may be applied to document safely
  virtual long getTransactionLevel()
    {return 0;}

  // causes native Abort for all changes on end of command
  virtual HRESULT SetAbortNativeCommand()
    {return E_NOTIMPL;}

	// bNeedUpdate = true, будет применять изменения объектов сразу, не дожидаясь конца транзакции.
	// default = false
	virtual HRESULT SetNeedUpdateGraphics(bool bNeedUpdate)
		{return E_NOTIMPL;}
};
typedef IMcsTransactionManager IMcTransactionManager;
//===========================================================================
enum MCSSelectFilterEnum
{
	sfNull        = 0x00000000,
	sfPoint       = 0x00000001, // 2d/3d point
	sfVector      = 0x00000002, // 2d/3d vector
	sfPlane       = 0x00000004, // 2d/3d plane
	sfPoint3d     = 0x00000008, // force 3d point
	sfVector3d    = 0x00000010, // force 3d vector
	sfPlane3d     = 0x00000020, // force 3d plane
	sfAll         = 0x00FFFFFF,

	//Additional
	sfCursor      = 0x20000000, // 2d/3d cursor
	sfCursor3d    = 0x40000000, // force 3d cursor
	sfNew         = 0x80000000,

	sf3dFilter    = sfPoint3d | sfVector3d | sfPlane3d | sfCursor3d,
};

#define DEFAULT_COLOR_BY_CONTEXT 0x01000000

//===========================================================================
//dwMask set of flags MCSSelectFilterEnum
struct IMcsGraphics : public IMObject
{
  virtual HRESULT HighlightFeatures(IN const mcsWorkID&  ObjectID, 
                                    IN OPTIONAL DWORD    dwMaskToHighlightFeaturesContets=sfAll,
                                    IN OPTIONAL COLORREF color=DEFAULT_COLOR_BY_CONTEXT)
    {return E_NOTIMPL;}

  virtual HRESULT UnHighlightFeatures(IN const mcsWorkID& ObjectID)
    {return E_NOTIMPL;}

  virtual HRESULT HighlightFeatureByName(IN const mcsWorkID&  ObjectID, 
                                         IN LPCTSTR           cstrFeatureName,
                                         IN OPTIONAL DWORD    dwMaskToHighlightFeatureContets=sfAll,
                                         IN OPTIONAL COLORREF color=DEFAULT_COLOR_BY_CONTEXT)
    {return E_NOTIMPL;}

  virtual HRESULT UnHighlightFeatureByName(IN const mcsWorkID& idObject, 
                                           IN LPCTSTR          stName)
    {return E_NOTIMPL;}

	//if(idHighlight == sfNew) creates new highlight, else move existing highlight with id == idHighlight
	virtual HRESULT Highlight(
		IN const mcsPoint& pntOrigin,
		IN const mcsVector& vecDirection,
		IN const mcsVector& vecNormal,
		IN DWORD dwFlags,
		IN OUT DWORD& idHighlight,
		IN OPTIONAL COLORREF color = DEFAULT_COLOR_BY_CONTEXT)
	{
		return E_NOTIMPL;
	}

  virtual HRESULT UnHighlight(IN DWORD idHighlight)
  {return E_NOTIMPL;}

  virtual HRESULT UnHighlightAll()
	  {return E_NOTIMPL;}
	
  //return NULL if failed or canceled
  virtual LPCTSTR SelectFeature(IN const mcsWorkID&  idObjectToSelectFrom, 
		IN DWORD             dwObjectFeaturesMask, 
		IN LPCTSTR           stPrompt,
		IN OPTIONAL COLORREF OverhighlightColor=DEFAULT_COLOR_BY_CONTEXT)
	  {return NULL;}
	
  // upDirVertor and rightDirVector both defines preview plane and it's orientation
  virtual HRESULT CreatePreview(HENHMETAFILE& hEmf, 
                                const mcsWorkIDArray &arr, 
                                mcsVector upDirVertor=mcsVector::kYAxis,
                                mcsVector rightDirVector=mcsVector::kXAxis)
	  {return E_NOTIMPL;}

  virtual HRESULT DrawRevolvedGraphicsContour(const mcsPolyline&   countour,
                                              const mcsLine&       revolveAxis,
                                              IN const mcsWorkID&  idNativeObjHL,
                                              IN OPTIONAL COLORREF color=DEFAULT_COLOR_BY_CONTEXT)
    {return E_NOTIMPL;}

  virtual HRESULT UnhighlightByWorkId(IN const mcsWorkID& idNativeObjHL)
    {return E_NOTIMPL;}

	virtual HRESULT ShowGraphics(IN OUT HANDLE& hID, IN const mcsGeomEntArray& ents)
		{ return E_NOTIMPL; }
	virtual HRESULT HideGraphics(IN HANDLE hID)
		{ return E_NOTIMPL; }

	virtual HRESULT getGeometry(OUT mcsGeomEntArray& geometry)
		{ return E_NOTIMPL; }
};
typedef MObjPtr<IMcsGraphics> IMcsGraphicsPtr;

//===========================================================================

enum McsEventsEnum
{
  kMcsEvent_OnActivateDoc   = 1, // param1 is 'LPVOID' document pointer
  kMcsEvent_OnDeactivateDoc = 2, // param1 is 'LPVOID' document pointer
  kMcsEvent_OnUpdateDoc     = 3, // param1 is 'LPVOID' document pointer;
                                 // param2 is 'bool', (true if before update called, false if after)
	kMcsEvent_OnTabActivate   = 4, // param1 TRUE for Activate or FALSE for Deactivate
	kMcsEvent_OnHelpCall			= 5, // param2 - HWND parent
	kMcsEvent_OnCommand				= 6, // param1 - command id, param2 - HWND parent
	kMcsEvent_OnApply					= 7, // param1 - command id, param2 - HWND parent
	kMcsEvent_OnCancel				= 8, // param1 - command id, param2 - HWND parent
};

//===========================================================================
struct IMcWindow: public IMObject 
{
	//window referenced by hwnd() must be able to resize
	virtual HWND hwnd() = 0;
	
  virtual void OnEvent(McsEventsEnum EventCode, WPARAM EventDependentParam1, LPARAM EventDependentParam2) {}
  //.......................................
  // non virtual methods
  void MoveIWindow(RECT& rect, BOOL bRepaint = TRUE){
		::MoveWindow(hwnd(), rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, bRepaint);
	}

  void GetIWindowRect(RECT& rect){
		::GetWindowRect(hwnd(), &rect);
	}
	
  void ShowIWindow(int nCmdShow){
		::ShowWindow(hwnd(), nCmdShow);
	}
};
typedef MObjPtr<IMcWindow> IMcWindowPtr;

//===========================================================================
struct IMcWindowContainer : public IMcWindow
{
	/// <summary>
	/// Получает окно с пользовательским содержимым. Пользователь должен создать это окно отдельно, а затем
	/// задать его с помощью метода SetContentWindow.
	/// </summary>
	/// <returns>Указатель на интерфейс IMcWindow, если пользовательское окно было задано, или NULL.</returns>
	virtual IMcWindow* GetContentWindow() = 0;

	/// <summary>
	/// Задаёт окно с пользовательским содержимым. Пользователь должен создать это окно отдельно.
	/// </summary>
	/// <param name="window">Окно с пользовательским содержимым.</param>
	virtual void SetContentWindow(IMcWindow *window) = 0;
};
typedef MObjPtr<IMcWindowContainer> IMcWindowContainerPtr;

//===========================================================================
struct IMcsProgress : public IMObject
{
	virtual bool SetPosition(double valAbsPos) = 0; // absolute position
	virtual bool Processed(double valRelativeDone) = 0; // relative 
	virtual void SetRange(double valFrom = 0, double valUpTo = 100) = 0;
	virtual void SetText(LPCTSTR csText) = 0;
	virtual void Stop() {}; //Акутально для прячущихся и появляющихся прогрессов, что бы поинтер не отпускать
	//Start автоматический
};
typedef MObjPtr<IMcsProgress> IMcsProgressPtr;
//===========================================================================
struct IMcTabManager: public IMObject 
{
	// strName - локализованное имя вкладки.
	// strSystemName - системное имя вкладки латиницей.
	// В конфигураторе должна быть зарегистрирована и включена в соответствующие продукты команда с именем "ShowTab<strSystemName>". Реализовывать эту команду не надо.
	virtual HRESULT Add(IMcWindow* pSheet, LPCTSTR strName, LPCTSTR strSystemName, HICON hImage) = 0;
	virtual HRESULT Add(IMcWindow* pSheet, LPCTSTR strName, LPCTSTR strSystemName, HBITMAP hImage, COLORREF clMask)
	{
		return Add(pSheet, strName, strSystemName, (HICON)NULL);
	}
	virtual HRESULT Remove(IMcWindow* pSheet) { return E_NOTIMPL; }

	virtual HRESULT Activate(IMcWindow* pSheet) { return E_NOTIMPL; }

	// Включить/выключить вкладку.
	// Пришлось добавить для панели свойств, которую нужно показывать только пока активна хозяйская вкладка.
	//
	// Если fShow == TRUE, действует аналогично Activate.
	virtual HRESULT Show(IN IMcWindow* pSheet, IN OPTIONAL BOOL fShow = TRUE) { return E_NOTIMPL; }
};
typedef MObjPtr<IMcTabManager> IMcTabManagerPtr;
//===========================================================================
// Тип сообщения
enum NotificationEnum { npSimple = -1,    // без иконки
												npUsual = 0,      // "страница"
												npWarning = 1,    // "воскл. знак"
												npCure = 2,       // "крест"
												npHint = 3,       // "лампа"
												npError = 4,      // "ошибка"
												npHelp = 5,       // "справка"
											};

// Реактор на события в окне сообщений
struct IMcNotifyReactor : public IMObject
// Если функция возвращает false, после неё выполняется стандартный обработчик действия
{
	// Перед удалением сообщения
	virtual bool OnErasing(UINT_PTR idMessage, bool& bCanDelete) { bCanDelete = true; return true; }
	// Двойной щелчок мышкой или Enter
	virtual bool OnActivate(UINT_PTR idMessage) { return false; }
	// Щелчок правой кнопкой
	virtual bool OnMenu(UINT_PTR idMessage, POINT ptMouse, HWND hMsgWindow) { return false; }
	// Добавлен зависимый элемент
	virtual bool OnChildCreated(UINT_PTR idParent, UINT_PTR idChild) { return false; }
	// Удаляется зависимый элемент
	virtual bool OnChildErasing(UINT_PTR idParent, UINT_PTR idChild, bool& bCanDelete) { bCanDelete = true; return true; }
	// Создан элемент
	virtual bool OnCreated(UINT_PTR idMessage, UINT_PTR idCreated) { return false; }
	// Элемент селектирован
	virtual bool OnSelected(UINT_PTR idMessage, bool fSelection) { return false; }
	// Сообщение генерируется окошком, привязанным к элементу
	virtual bool OnClickSubwindow(UINT_PTR idMessage, int iCode) { return false; }
};

//===========================================================================
struct IMcNotificator
{
	// Создать новое сообщение. Возвращает идентификатор сообщения.
	virtual UINT_PTR CreateMessage(LPCTSTR lpszMessageText,              // текст сообщения
	                               NotificationEnum type = npSimple,    // иконка
	                               UINT_PTR idParent = 0,               // идентификатор родительского сообщения
	                               IMcNotifyReactor* pReactor = NULL,		// callback
	                               IMcWindow* pSubWindow = NULL) = 0;   // окошко, привязанное к сообщению.
	                                                                    // Появится прямо под текстом
	// Удалить сообщение и все сообщения, которые от него зависят
	virtual BOOL DeleteMessage(UINT_PTR idMessage) = 0;
	// Получить идентификатор сообщения-хозяина
	virtual UINT_PTR GetMessageParent(UINT_PTR idMessage) = 0;
	virtual UINT_PTR GetSelection() = 0;
	virtual UINT_PTR SetSelection(UINT_PTR idMessage) = 0;
	virtual HWND GetWindowHandle() = 0;
	virtual void Clear() = 0;
	//
	virtual McsString GetMessageText(UINT_PTR idMessage) = 0;
	virtual BOOL SetMessageText(UINT_PTR idMessage, LPCTSTR lpszText) = 0;

	virtual BOOL SetShortView(BOOL fShort) = 0;
};

//===========================================================================
/////////////////////////////////////////////////////////////////////////////
// Предопределенные реакторы для сообщений //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Кнопка "Редактировать объект" после текста сообщения
struct IMcEditObjectButton : public IMcWindow
{
	// Идентификатор сообщения, котороые будет удалено после нажатия на кнопку
	virtual void setMessageID(UINT_PTR id) = 0;
};
typedef MObjPtr<IMcEditObjectButton> IMcEditObjectButtonPtr;
IMcEditObjectButtonPtr MECHCTL_API NW_EditObjectButton(const mcsWorkID& idObject);
IMcWindowPtr MECHCTL_API NW_HelpButton(long/*McsHelpIDEnum*/ idTopic);
IMcWindowPtr MECHCTL_API NW_SysLink(LPCTSTR strText);


//===========================================================================
/////////////////////////////////////////////////////////////////////////////
// Список последних введенных значений и шаблонных значений /////////////////
/////////////////////////////////////////////////////////////////////////////

class
__declspec(uuid("{3C20CAB2-5FEA-4b89-B81D-87D331DF823E}"))
IMcRecentValues : public IMcObject
{
public:
	// Открыть список. lpszKey может быть иерархическим (разделитель - \)
	virtual HRESULT Open(LPCTSTR lpszApp, LPCTSTR lpszKey) = 0;
	
	// Добавить строку в историю. lpszName - имя подключа, добавляемого к lpszKey.
	// Если не указано, выбираются все подключи.
	// Может быть иерархическим. Например, "values\field1" выберет все значения с ключами
	// lpszKey"\values\field1" и lpszKey"\values\field1\*"
	virtual HRESULT Add(LPCTSTR Value, LPCTSTR lpszName = NULL) = 0;
	// Получить nCount последних значений. Если nCount = -1, будут выбраны все значения
	virtual HRESULT Get(mcsStringArray& Values, int nCount = -1, LPCTSTR lpszName = NULL) = 0;
	// Удалить значение
	virtual HRESULT Remove(LPCTSTR Value, LPCTSTR Name = NULL) = 0;
	// Очистить список
	virtual HRESULT Clear(LPCTSTR lpszName = NULL) = 0;
	// Получить значения с именами. Values.GetSize() = Names.GetSize()*nCount
	// Если значений меньше, чем nCount, массив будет дополнен пустыми строками
	virtual HRESULT GetNamed(mcsStringArray& Names, mcsStringArray& Values,
													 int nCount = 1, LPCTSTR lpszName = NULL) = 0;
};
//===========================================================================

// ppMaterial - материал для редактирования. Через этот же параметр будет возвращён новый или этот же отредактированный материал.
// Вернуться может совершенно другой объект с иным MCSUID.
inline HRESULT McCreateMaterialDyn(IMcEntity** ppMaterial, HWND hParent)
{
	FARPROC pProc = GetProcAddress(GetModuleHandleA("mcsparser.dll"), "McCreateMaterial");
	if(pProc)
		return ((HRESULT(*)(IMcEntity**, HWND))pProc)(ppMaterial, hParent);
	return E_FAIL;
}

//---------------------------------------------------------------------------
inline McsString McParseMaterialDyn(LPCTSTR stMaterial)
{
	FARPROC pProc = GetProcAddress(GetModuleHandleA("mcsparser.dll"), "McParseMaterial");
	if(pProc)
		return ((McsString(*)(LPCTSTR))pProc)(stMaterial);
	return mcsEmptyString;
}
//===========================================================================

namespace MSXML2
{
	struct IXMLDOMElement;
}

// Хэлперы для зачитывания атрибутов с XML узлов
HRESULT MCTYP_API xmlReadAttribute(IN MSXML2::IXMLDOMElement* pElement, IN LPCTSTR stName, OUT int& iValue, IN OPTIONAL int iDefault = 0);
HRESULT MCTYP_API xmlReadAttribute(IN MSXML2::IXMLDOMElement* pElement, IN LPCTSTR stName, OUT DWORD& dwValue, IN OPTIONAL DWORD dwDefault = 0);
HRESULT MCTYP_API xmlReadAttribute(IN MSXML2::IXMLDOMElement* pElement, IN LPCTSTR stName, OUT bool& bValue, IN OPTIONAL bool bDefault = false);
HRESULT MCTYP_API xmlReadAttribute(IN MSXML2::IXMLDOMElement* pElement, IN LPCTSTR stName, OUT double& rValue, IN OPTIONAL double rDefault = 0);
HRESULT MCTYP_API xmlReadAttribute(IN MSXML2::IXMLDOMElement* pElement, IN LPCTSTR stName, OUT McsString& stValue, IN OPTIONAL LPCTSTR stDefault = _T(""));

//===========================================================================

typedef MComQIPtr<IMcRecentValues> IMcRecentValuesPtr;
static const GUID IID_IMcRecentValues = { 0x3c20cab2, 0x5fea, 0x4b89, { 0xb8, 0x1d, 0x87, 0xd3, 0x31, 0xdf, 0x82, 0x3e } };

//===========================================================================

#if !defined(_MCS_CORE_ONLY)
	#include "IMechanicsInternal.h"
#endif

//===========================================================================
