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

// (!) DO NOT INCLUDE ANYTHING HERE
// Find line with text "#ifndef __COMPILE_MT__" and do it there

//===========================================================================
#define MC_EVENTS_SINK_DEFAULT_PRIORITY   1
#define MC_EVENTS_SINK_MAPIMNGD_PRIORITY  500
#define MC_EVENTS_SINK_MECHCTL_PRIORITY   1000
#define MC_EVENTS_SINK_PROJECTS_PRIORITY  (MC_EVENTS_SINK_MECHCTL_PRIORITY - 1)// Проекты должны обрабатывать события непосредственно перед ядром!
#define MC_EVENTS_SINK_3DSITE_PRIORITY    2000
// Не использовать приоритет выше MC_EVENTS_SINK_MCSPARAMS_PRIORITY если код использует настройки!
#define MC_EVENTS_SINK_MCSPARAMS_PRIORITY 3000
//===========================================================================
enum McQuitEventSubTypeEnum
{
	kMcQuitEventBegin = 0,
	kMcQuitEventAborted,
	kMcQuitEventWillStart,
};
//===========================================================================
enum McCustomEventType
{
	McCustomEvent_None            = -1,

	McCustomEventDeferredConvert  = 0,// wParam - AcDbDatabase*/OdDbDatabase*, lParam - IMcDocument*
	McCustomEventDeferVSErase     = 1,// wParam - mcsWorkID*
	McCustomEventDeferBaseRemove  = 2,// wParam - LPCTSTR
	
	McCustomEventBeforeUnloadApp  = 3,
	McCustomEventAfterLoadApp     = 4, // всё загружено и проинициализировано, (после McCustomEventAfterMcsInit)
	McCustomEventBeforeUnloadCore = 5, // event: made call for unload core

	McCustomEventUpdateTree       = 6,// wParam - McSessionObjectInfo*

	McCustomEventBeforeUninitApp  = 7, // перед тем как позовётся первый McsUnInit
	McCustomEventAfterUninitApp   = 8, // после того, как позвались все McsUnInit

	McCustomEventTrim             = 9, // зовётся во время команды trim после назначения новой геометрии объекту
	McCustomEventBeginDeepClone   = 10, // начало клонирования

		// конец клонирования,
		//	wParam - const mcsWId2WIdMap* pSrcToClonedMap. В массиве будут только MCS-объекты (так сделано для оптимизации)
		//	lParam - bool bInternal. Если true, то это системное клонирование, и событие transfered для объектов не зовётся в этой фазе
		//		такое событие послысается как парное для McCustomEventBeginDeepClone, т.к. оно посылается всегда
		//		(Почти всегда обрабатывать солучай lParam = true не нужно)
	McCustomEventEndDeepClone     = 11,

	McCustomEvent2dConstrainsApplied = 12, // только что применились 2D зависимости, wParam = mcsWorkID* pConstraintsScopeID

		// Два события ниже посылаются перед и после группового обновления объектов.
		// Отличие от OnUpdateAll в том, что то событие посылается только на общиее
		// обновление и только "перед", а эти при любом (и полном и частичном)
	McCustomEventBeginUpdate      = 13, // wParam = McSessionObjectInfo* на список объектов, подлежащих обновлению
	McCustomEventEndUpdate        = 14,

		//Событие при загрузке сборки референсящей наш модуль, wParam - (LPCTSTR)strAssemblyName
	McCustomEvent_AssemblyProcessed = 15,

		// Сообщение рассылается из стандартного диалога, 
		// предлагает зарегестрировать закладки с помощью функции AddTabInDialogD
		// в wParam содержится указатель на проинициализированный IParser
	McCustomEvent_AddTabInStdDialog = 16,

		// Сообщение рассылается из MechCtl, после завершения рассылки onEvent(kMcEvent_Regenerate)
	McCustomEvent_AfterRegenerate = 17, 

		// NMK_FILTER, Рассылается после загрузки ТКС. Параметров нет
//	McCustomEvent_TCS_Call_NMK_Filter = 18,
	McCustomEvent_TCS_Initialized = 19,

	McCustomEventBeforeMcsInit    = 20, // зовется до самого первого вызова MCSInit (но при каждом вызове IMcAppLoader::LoadApp)
	McCustomEventAfterMcsInit     = 21, // зовется после последнего вызова MCSInit на App (перед McCustomEventAfterLoadApp)

		// wParam - McParamEvent*, lParam - HWND диалога настроек
	McCustomEvent_OnParamPushStringButton = 22, // Нажатие на кнопку в контроле MC_STRING_BUTTON
	McCustomEvent_OnParamGetStringList = 23,    // Запрос на получение специального списка строк для MC_STRING_ARRAY

		// system purposes only
	McCustomEventUpdateIsAboutToEnd = 24, // wParam = bool* pbRunUpdateAgain, *pbRunUpdateAgain is false by default, lParam = McSessionObjectInfo*

		// wParam = IMcDocument*, планируемый к закрытию документ
		// lParam = bool* pbVeto, по умолчанию false
		// Расылается до фактического закрытия документа и рассылки соответствующих реакторов. Установка pbVeto в true прервёт закрытие документа.
		// Особенность реализации: pbVeto выставлять в false нельзя, если pbVeto уже true, то немедленно выходим.
	McCustomEventBeginDocClose = 25,

		// Рассылается сразу после того, как инициализация 3D полностью завершилась.
		// wParam - не используется.
		// lParam - не используется.
	McCustomEvent3DInitialized = 26,

		// Событие приходит в конце операций с блоками
		// Желательно ничего не менять в документе в этот момент,
		// событие подразумевает ReadOnly-поведение
	McCustomEventBlockOpEnded = 27,

		// wParam = IMcProject*, только что загруженный проект по запросу getProject()
		// lParam = IMcDocument*, документ либо переданный в getProject() либо активный
		//   Расылается в конце успешной загрузки проекта из getProject.
		//   В обработчике можно выполнять конверсию проекта, которая не затрагивает изменения в объектах на чертеже.
		//   Если же конверсия затрагивает объекты, то необходимо(!) вызывать getProject из обработчика события McCustomEventDeferredConvert
	McCustomEvent_ProjectLoaded = 28,

		// Параметров нет.
		// Расылается после:
		//  - изменения состояния элемента/папки в текущей БД
		//  - копирования элемента/папки в текущей БД
		//  - удаления элемента/папки в текущей БД
		//  - переключения самой БД
	McCustomEvent_DbContentChanged = 29,

		// Приходит при изменении темы интерфейса
	McCustomEvent_ThemeChanged = 30,

		// wParam - const mcsWorkID*
		// lParam - bool, visibility
		// Изменение статуса изоляции объекта
	McCustomEvent_OnIsolate = 31,

		// В указанном виде изменились параметры камеры
		// wParam - IMcNativeView* pView
	McCustomEvent_ViewCameraChanged = 32,

		// Посылается на конец работы метода IMcUndoPoint::restore
		// wParam = const McSessionObjectInfo* - данные, которые были изменены в процессе восстановления состояния
	McCustomEvent_UndoPointRestore = 33,

		// Посылается на конец операции внедрения документа внешней ссылки.
		// wParam - const mcsWorkID*, ID поддокумента, для которого было выполнено внедрение (был xref, стал обычным блоком).
	McCustomEvent_OnXrefBindingComplete = 34,

		// Посылается на конец операции загрузки внешней ссылки, (!) но не при открытии документа.
		// wParam - const mcsWorkID*, ID подгруженного поддокумента.
	McCustomEvent_OnXrefAttachComplete = 35,
};
//===========================================================================

#ifndef __COMPILE_MT__

#include "MCSTypes.h"
#include "MCSParams.h"
#include "McAPIs.h"

/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// must be implemented in CLIENT modules

struct IMcEventsSink
{
public:
  bool        m_fEnabled;      // if <false> then sink manager will not call methods from sink object

protected:
	IMcEventsSink() {
		m_fEnabled = true;
	}

public:
  virtual long    getSinkPriority() { return MC_EVENTS_SINK_DEFAULT_PRIORITY; }
	// document events ........................................................
	virtual HRESULT OnOpenDocument(IN IMcDocument* pMcDoc, IN bool fNew, bool fHidden) {return E_NOTIMPL;} // after
	virtual HRESULT OnCloseDocument(IN IMcDocument* pMcDoc, bool fHidden) {return E_NOTIMPL;} // before
	virtual HRESULT OnActivateDocument(IN IMcDocument* pMcDoc) {return E_NOTIMPL;} // after
	virtual HRESULT OnDeactivateDocument(IN IMcDocument* pMcDoc) {return E_NOTIMPL;} // before
	virtual HRESULT OnSaveDocument(IN IMcDocument* pMcDoc, LPCTSTR strSavePath) {return E_NOTIMPL;} // before
	virtual HRESULT OnCommand(IN LPCTSTR csCmdName,IN bool fBefore) {return E_NOTIMPL;}
	virtual HRESULT OnSelchanged(IN mcsWorkIDArray& selObjects) {return E_NOTIMPL;} // after
	virtual HRESULT OnRegenerate() {return E_NOTIMPL;}
	virtual HRESULT OnUndo() {return E_NOTIMPL;} // after
	virtual HRESULT OnRedo() {return E_NOTIMPL;} // after
	virtual HRESULT OnAddObject(IN const mcsWorkID& id) {return E_NOTIMPL;}
	virtual HRESULT OnObjectChanged(IN const mcsWorkID& id) {return E_NOTIMPL;}
	virtual HRESULT OnEraseObject(IN const mcsWorkID& id) {return E_NOTIMPL;}
	virtual HRESULT OnResolvePath(IN OUT McsString& Value) {return E_NOTIMPL;}
	virtual HRESULT OnDocumentClosed(IN LPCTSTR lpszPath) {return E_NOTIMPL;}  // after
	virtual HRESULT OnSavedDocument(IN IMcDocument* pMcDoc, IN LPCTSTR strSaveTo) {return E_NOTIMPL;} // after
	virtual HRESULT OnSheetRemove(IN IMcDocument* pMcDoc) {return E_NOTIMPL;} // before
	virtual HRESULT OnCustomEvent(IN McCustomEventType type, IN WPARAM wParam, IN LPARAM lParam) {return E_NOTIMPL;}
	virtual HRESULT OnQuit(IN McQuitEventSubTypeEnum type) {return E_NOTIMPL;}
	virtual HRESULT OnUpdateAll() {return E_NOTIMPL;}
	virtual HRESULT OnEditObject(IMcEntity* pEnt, const mcsPoint& pnt, long lFlag) {return E_NOTIMPL;}
	virtual HRESULT OnEditObjects(const mcsWorkIDArray& ids, const mcsPoint& pnt, long lFlag) {return E_NOTIMPL;}
	virtual HRESULT OnParamChanging(IN IMcDocument* pMcDoc, IN const McParamId& parId, HWND hwndParamDlg, HRESULT& hresChanging, IN OUT MCSVariant& varNew) {return E_NOTIMPL;}
	virtual HRESULT OnParamChanged(IN IMcDocument* pMcDoc, IN const McParamId& parId, IN const MCSVariant& varNew) {return E_NOTIMPL;}
	// Следующие три реактора приходят для ВСЕХ объектов, а не только наших. Без явной нужды не использовать!
	virtual HRESULT OnAddObjectInternal(IN const mcsWorkID& id) { return E_NOTIMPL; }
	virtual HRESULT OnObjectChangedInternal(IN const mcsWorkID& id) { return E_NOTIMPL; }
	virtual HRESULT OnEraseObjectInternal(IN const mcsWorkID& id) { return E_NOTIMPL; }
	virtual HRESULT OnPreselectObject(IN const mcsWorkID& id) { return E_NOTIMPL; }
	virtual HRESULT OnActivateSheet(IN IMcDocument* pNewActiveSheet) {return E_NOTIMPL;} // after
};
//===========================================================================

/////////////////////////////////////////////////////////////////////////////
// !!! INTERNAL
// MECHCTL events dispatcher must be derived from this interface
// NATIVEGATE accepts this interface to pass native events to CTL dispatcher
// use function from gate 
// extern "C" __declspec(dllexport) IMcNativeEventsInput* GetNativeEventsDispatcher()
// to get dispatcher input events interface

struct IMcNativeEventsInput
{
	enum McEventTypeEnum
	{
		kMcEvent_None = 0,
		kMcEvent_OpenDocument,
		kMcEvent_CloseDocument,
		kMcEvent_ActivateDocument,
		kMcEvent_DeactivateDocument,
		kMcEvent_SaveDocument,
		kMcEvent_Command,
		kMcEvent_Selchanged,
		kMcEvent_Regenerate,
		kMcEvent_Undo,
		kMcEvent_Redo,
		kMcEvent_AddObject,
		kMcEvent_ObjectChanged,
		kMcEvent_EraseObject,
		kMcEvent_ResolvePath,
		kMcEvent_DocumentClosed,
		kMcEvent_SavedDocument,
		kMcEvent_SheetRemove,
		kMcEvent_Custom,
		kMcEvent_QuitBegin,
		kMcEvent_QuitAborted,
		kMcEvent_QuitWillStart,
		kMcEvent_UpdateAll,
		kMcEvent_EditObject,
		kMcEvent_EditObjects,
		kMcEvent_ParamChanging,
		kMcEvent_ParamChanged,
		kMcEvent_AddObjectInternal,
		kMcEvent_ObjectChangedInternal,
		kMcEvent_EraseObjectInternal,
		kMcEvent_PreselectObject,
		kMcEvent_ActivateSheet,
	};

	virtual void OnCommand(IN LPCTSTR csCmdName,IN bool fBefore) {}
	virtual void OnOpenDocument(IN IMcDocument* pMcDoc, IN bool fNew) {}
	virtual void OnCloseDocument(IN IMcDocument* pMcDoc) {}
	virtual void OnActivateDocument(IN IMcDocument* pMcDoc) {}
	virtual void OnDeactivateDocument(IN IMcDocument* pMcDoc) {}
	virtual void OnSaveDocument(IN IMcDocument* pMcDoc, LPCTSTR strSavePath) {}
	virtual void OnSavedDocument(IN IMcDocument* pMcDoc, LPCTSTR strSavePath) {}
	virtual void OnSelchanged(IN mcsWorkIDArray& selObjects) {}
	virtual void OnRegenerate() {}
	virtual void OnAddObject(const mcsWorkID& id) {}
	virtual void OnObjectChanged(const mcsWorkID& id) {}
	virtual void OnEraseObject(const mcsWorkID& id) {}
	virtual void OnUndo() {}
	virtual void OnRedo() {}
	virtual HRESULT OnResolvePath(IN OUT McsString& Value) { return E_NOTIMPL; }
	virtual void OnDocumentClosed(IN LPCTSTR lpszPath) {}
	virtual void OnSheetRemove(IN IMcDocument* pMcDoc) {}
	virtual void OnCustomEvent(IN McCustomEventType type, IN WPARAM wParam, IN LPARAM lParam) {}
	virtual void OnQuit(IN McQuitEventSubTypeEnum type) {}
	virtual void OnUpdateAll() {}
	virtual HRESULT OnEditObject(IMcEntity* pEnt, const mcsPoint& pnt, long lFlag) { return E_NOTIMPL; }
	virtual HRESULT OnEditObjects(const mcsWorkIDArray& ids, const mcsPoint& pnt, long lFlag) { return E_NOTIMPL; }
	virtual void OnParamChanging(IN IMcDocument* pMcDoc, IN const McParamId& parId, HWND hwndParamDlg, HRESULT& hresChanging, IN OUT MCSVariant& varNew) {}
	virtual void OnParamChanged(IN IMcDocument* pMcDoc, IN const McParamId& parId, IN const MCSVariant& varNew) {}
	virtual void OnAddObjectInternal(IN const mcsWorkID& id) {}
	virtual void OnObjectChangedInternal(IN const mcsWorkID& id) {}
	virtual void OnEraseObjectInternal(IN const mcsWorkID& id) {}
	virtual void OnPreselectObject(IN const mcsWorkID& id) {}
	virtual void OnActivateSheet(IN IMcDocument* pNewActiveSheet) {}
};
//===========================================================================

extern "C" MECHCTL_API IMcNativeEventsInput::McEventTypeEnum gMcCurrentEvent; // contains current event code

extern "C" MECHCTL_API void McFireCustomEvent(IN McCustomEventType type, IN WPARAM wParam, IN LPARAM lParam);

//===========================================================================

#endif // __COMPILE_MT__
