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
#include "McsUtils.h"

#include "IMcEvents.h"

struct IMcTabManager;

//=============================================================================
#define MAX_KEY 256
//.................................................
__inline mcsCmd::mcsCmd()
{
	Command = NULL;
	lMode = MCS_CMD_REDRAW;
	lApps = 0xFFFFFFFF;// MCS_APPS_ALL;
}
//.................................................
__inline mcsCmd::mcsCmd(mcsCmdFunctionPtr cmd, LPCTSTR stGlobal, long Mode)
{
	Command = cmd;
	stGlobalName = stGlobal;
	stLocalName = stGlobalName;
	lMode = Mode;
	lApps = 0xFFFFFFFF;// MCS_APPS_ALL
}
//.................................................
__inline HRESULT mcsCmd::Execute(MCSVariant* pCustomParams)
{
	if(Command)
	{
		Command(pCustomParams);
		return S_OK;
	}
	return E_NOTIMPL;
}
//.................................................

// (!) Значения не менять

enum mcsDataPaths
{
	MCS_HELP = 0, 
	MCS_CORE_ROOT, 
	MCS_CORE_DIR,
	MCS_APP_ROOT, 
	MCS_START_DIR, 
	MCS_EXAMPLES, 
	MCS_UPDATE,
	MCS_FONTS,
	MCS_DATA_ALL_RO, 
	MCS_DATA_ALL_RW, 
	MCS_DATA_RO, 
	MCS_DATA_USER,        // Это для отдельного пользователя, но для системы
	MCS_DATA_USER_DOC,    // Это тоже для каждого пользователя, но для тех случаев когда он может создавать подобные файлы и выбирать среди них
	MCS_DATA_TEMPLATE,    // здесь лежит прототипы файлов для конкретного юзера
	MCS_DATA_STDPARTS_CATALOG, // пусть к каталогу стандартных компонентов
	MCS_DATA_EMPTY_PATH,  // просто пустая строка, иногда надо :)
	MCS_DATA_LICENSES,    // Путь к хранилищу лицензий (локальный)

//////////////////////////////////////////////////////////////////////////
//Files
	MCS_DATA_FILE_SpecSymb_txt,
	MCS_DATA_FILE_DbTemplate3,
	MCS_DATA_FILE_StdDB,
	MCS_DATA_FILE_DbFavorites,
	MCS_DATA_FILE_Fits_dat,
	MCS_DATA_FILE_Fits_txt,
	MCS_DATA_FILE_Settings_xml,
	MCS_DATA_FILE_tinfo_xml,
	MCS_DATA_FILE_quicksel_dat,
	MCS_DATA_FILE_boms_mdb,
	MCS_DATA_FILE_ArrTempl_vrl,
	MCS_DATA_FILE_spcrec_xls,
	MCS_DATA_FILE_coildata_mdb,
	MCS_DATA_FILE_ShaftCalcTemplate_ctp,
	MCS_DATA_FILE_McsHatchBH_pat,
	MCS_DATA_FILE_McsHatchBG_pat,
	MCS_DATA_FILE_spctmpl_xls,
	MCS_DATA_FILE_spcgroup3_xls,
	MCS_DATA_FILE_spcgroupb_xls,
	MCS_DATA_FILE_stuff_mcm,
	MCS_DATA_FILE_Surf_txt,
	MCS_DATA_FILE_Tolerance_txt,
	MCS_DATA_FILE_SPDS_ntb,
	MCS_DATA_FILE_Default_ntb,
	MCS_DATA_FILE_SpcDocNames_txt,
	MCS_DATA_FILE_sizechain_dat,
	MCS_DATA_FILE_AppOptions_xml,// настройки приложения
	MCS_DATA_FILE_CorpOptions_xml,// корпоративные настройки
	MCS_DATA_FILE_Options_AI_icf,// obsolete
	MCS_DATA_FILE_ObjSettings_AI_cfg,// obsolete
	MCS_DATA_FILE_Options_SPOT_icf,// obsolete
	MCS_DATA_FILE_ObjSettings_SPOT_cfg,// obsolete
	MCS_DATA_FILE_DefaultNtbPage,
	MCS_DATA_FILE_FindTemplates,
	MCS_DATA_FILE_SetupSettings,//настройки задающиеся при сетапе
	MCS_DATA_FILE_boms_xml,//структура классов для менеджера проектов
	MCS_DATA_PARAM_def_profile,//Профиль пользователя по умолчанию
	MCS_DATA_FILE_std_help,//Полное имя основного файла справки
	MCS_DATA_AppPrefix,//Префикс комманд
	MCS_DATA_AppPrefixLocal,//Префикс комманд локализованный
	MCS_DATA_FILE_albums_xml,//файл альбомов
	MCS_DATA_FILE_projects_xml,//файл проектов
	MCS_DATA_FILE_spr_xml,//локальные настройки расчёта пружин
	MCS_DATA_FILE_coils_xml,//параметры витков для расчёта пружин
	MCS_DATA_SPEC_menu_group,//имя группы меню
	MCS_DATA_FILE_rocktypes_xml,//параметры штриховок для ГНБ
	MCS_DATA_FILE_defppr_xml,//(не использовать) шаблон ППР, obsolete 
	MCS_DATA_SPEC_DefStd,//default standard
	MCS_DATA_FILE_defprj,//default prj place
	MCS_DATA_FILE_prjRules,//project rules
	MCS_DATA_FILE_spds_dat,//настройки ПланТрейсера под СПДС
	MCS_DATA_FILE_techfilter,//настройки фильтрации техники для ппр
	MCS_DATA_FILE_spdswalls_xml,//параметры стен  
	MCS_DATA_FILE_spdsrooms_xml,//параметры комнат и отделки
	MCS_DATA_FILE_spdsrooms_flooring_section_dwg, // половые сечения
	MCS_DATA_FILE_gear_analyzer_base_xml, // база материалов для расчетов зубчатых передач
	MCS_DATA_REG_PATH,//Ветка в реестре для сохранения
	MCS_DATA_FILE_menu_cfg_system,// Файл меню, системная константа, для получения используйте IMcContext::GetMenuCfgFileName().
	MCS_DATA_FILE_menu_dll_system,// Ресурсы файла меню, системная константа, для получения используйте IMcContext::GetMenuDllFileName().
	MCS_DATA_ALL_RO_LOC, // Путь к MCS_DATA_ALL_RO с добавлением подпапки локализации
	MCS_DATA_ALL_RW_LOC, // Путь к MCS_DATA_ALL_RW с добавлением подпапки локализации
	MCS_DATA_TEMPLATE_LOC, // Путь к MCS_DATA_TEMPLATE с добавлением подпапки локализации
	MCS_DATA_USER_LOC, // Путь к MCS_DATA_USER с добавлением подпапки локализации
	MCS_DATA_RO_LOC, // Путь к MCS_DATA_RO с добавлением подпапки локализации
	MCS_DATA_FILE_MaterialsDB_xml, // База материалов ППР
	MCS_DATA_FILE_BuildingsDB_xml, // База техники ППР
	MCS_DATA_FILE_ppr2gs_xslt,		// ППР: XSLT для экспорта в GrandSmeta
	MCS_DATA_FILE_ppr3arps_xslt,	// ППР: XSLT для экспорта в ARPS
	MCS_DATA_FILE_ppr3csv_xslt,		// ППР: XSLT для экспорта в CSV
	MCS_DATA_FILE_ppr3gs_xslt,		// ППР: XSLT для экспорта в GrandSmeta
	MCS_DATA_FILE_ppr3mspj_xslt,	// ППР: XSLT для экспорта в MSProject
	MCS_DATA_FILE_RFSpecification_xml, // Спецификатор типов объектов КЖ.
	MCS_DATA_Reports_templates,	//Шаблоны отчетов
	MCS_DATA_Culture_SubDirectory,	// имя подпапки локализации
	MCS_DATA_FILE_ImageList,// ImageList локализованных глобальных иконок
	MCS_DATA_FILE_SpecificationExportXml,// Путь к xml настройки экспорта спецификации в документ
	MCS_DATA_FILE_gear_analyzer_report_template_rtf, // Путь к rtf - шаблону для генерации отчетов по прочностным расчетам зубчатых передач
	MCS_DATA_FILE_gear_analyzer_geom_report_template_rtf, // Путь к rtf - шаблону для генерации отчетов по геометрическим расчетам зубчатых передач
	MCS_DATA_TESTS_DATA,  // Путь к каталогу с даннными для тестов, документы с тесткейсами, таблицы с данными и пр. (r/w)
	MCS_DATA_SMPL_BIM,  // Путь к каталогу с модулями simpleBim
	MCS_DATA_FILE_ScheduleUnits_xml,	// ППР: Календарное планирование. Единицы длительности работ на разных языках
	MCS_DATA_FILE_mspjppr6_xslt,		// ППР: XSLT для импорта из MSProject
	MCS_DATA_FILE_KmCSections_xml,		// КМ: Список составных сечений с параметрами
	MCS_DATA_FILE_KmMaterials_xml,		// КМ: Список материалов в диалогах редактирования колонн\метаобъектов
	MCS_DATA_FILE_spcplaz_xls,			// Спецификация: excel-шаблон для экспорта плазовой спецификации
	MCS_DATA_FILE_ImageListDis,// ImageList серых локализованных глобальных иконок
	MCS_DATA_FILE_SW_SpBlockTitle_S1_slddrt,	// SolidWorks: Подложка для спецификации. Лист1.
	MCS_DATA_FILE_SW_SpBlockTitle_S2_slddrt,	// SolidWorks: Подложка для спецификации. Лист2.
	MCS_DATA_FILE_SW_SpBlockTitle_GTypeB_S1_slddrt,// SolidWorks: Подложка для групповой спецификации Тип Б. Лист1.
	MCS_DATA_FILE_SW_SpBlockTitle_GTypeB_S2_slddrt,// SolidWorks: Подложка для групповой спецификации Тип Б. Лист2.
	MCS_DATA_FILE_SW_SpTable_S1_sw,				// SolidWorks: Таблица для спецификации. Лист1.
	MCS_DATA_FILE_SW_SpTable_S2_sw,				// SolidWorks: Таблица для спецификации. Лист2.
	MCS_DATA_FILE_SW_SpTable_GTypeB_S1_sw,		// SolidWorks: Таблица для групповой спецификации Тип Б. Лист1.
	MCS_DATA_FILE_SW_SpTable_GTypeB_S2_sw,		// SolidWorks: Таблица для групповой спецификации Тип Б. Лист2.
	MCS_DATA_FILE_SW_SpTable_GTypeB_Add_S1_sw,	// SolidWorks: Дополнительная таблица для групповой спецификации Тип Б. Лист1.
	MCS_DATA_FILE_SW_SpBlockTitle_GTypeA_Form5_S1_slddrt,// SolidWorks: Подложка для групповой спецификации Тип А. Форма5. Лист1.
	MCS_DATA_FILE_SW_SpBlockTitle_GTypeA_Form5_S2_slddrt,// SolidWorks: Подложка для групповой спецификации Тип А. Форма5. Лист2.
	MCS_DATA_FILE_SW_SpTable_GTypeA_Form5_S1_sw,		 // SolidWorks: Таблица для групповой спецификации Тип А. Форма5. Лист1.
	MCS_DATA_FILE_SW_SpTable_GTypeA_Form5_S2_sw,		 // SolidWorks: Таблица для групповой спецификации Тип А. Форма5. Лист2.
	MCS_DATA_FILE_SW_SpTable_InventoryStamp_Horz_sw,	 // SolidWorks: Инвентарная надпись в горизонтальной ориентации
	MCS_DATA_FILE_SW_SpTable_InventoryStamp_Vert_sw,	 // SolidWorks: Инвентарная надпись в вертикальной ориентации
	MCS_DATA_FILE_SW_SpTable_ReferenceStamp_Horz_sw,	 // SolidWorks: Справочная надпись в горизонтальной ориентации
	MCS_DATA_FILE_SW_SpTable_ReferenceStamp_Vert_sw,	 // SolidWorks: Справочная надпись в вертикальной ориентации
	MCS_DATA_FILE_SW_SpTable_MainStamp_sw,				 // SolidWorks: Основная надпись
	MCS_DATA_FILE_SW_SpTable_MainSimplifiedStamp_sw,	 // SolidWorks: Основная надпись упрощенная
	MCS_DATA_FILE_IfcImportDefaultSettings_xml, // IFC: Файл настроек по умолчанию импорта IFC документов.
	MCS_DATA_FILE_IfcImportSettings_xml,        // IFC: Файл настроек импорта IFC документов.
	MCS_DATA_FILE_menu_dll_system2,// Ресурсы файла меню, системная константа, для получения используйте IMcContext::GetMenuDllFileName().
	MCS_DATA_FILE_SettingsOverride,// Файл переопределения настроек.
	MCS_DATA_FILE_SpecRecsGroupingNameReplace_txt,	// Спецификация: файл с парами слов для замены наименования при группировке записей во время экспорта в чертеж или Excel
	MCS_DATA_FILE_SW_SpTable_BuiltIn_sw,						// SolidWorks: Таблица для встроенной в чертеж спецификации.
	MCS_DATA_FILE_SW_SpBlockTitle_S1_slddrt_Arial,				// SolidWorks: Подложка для спецификации. Лист1. Шрифт Arial.
	MCS_DATA_FILE_SW_SpBlockTitle_S2_slddrt_Arial,				// SolidWorks: Подложка для спецификации. Лист2. Шрифт Arial.
	MCS_DATA_FILE_SW_SpBlockTitle_GTypeB_S1_slddrt_Arial,		// SolidWorks: Подложка для групповой спецификации Тип Б. Лист1. Шрифт Arial.
	MCS_DATA_FILE_SW_SpBlockTitle_GTypeB_S2_slddrt_Arial,		// SolidWorks: Подложка для групповой спецификации Тип Б. Лист2. Шрифт Arial.
	MCS_DATA_FILE_SW_SpBlockTitle_GTypeA_Form5_S1_slddrt_Arial,	// SolidWorks: Подложка для групповой спецификации Тип А. Форма5. Лист1. Шрифт Arial.
	MCS_DATA_FILE_SW_SpBlockTitle_GTypeA_Form5_S2_slddrt_Arial,	// SolidWorks: Подложка для групповой спецификации Тип А. Форма5. Лист2. Шрифт Arial.
};
//=======================================================================================
struct IMcTheme
{
	enum McThemeElement
	{
		// Добавлять новые константы после First
		kColorUndefinedFirst,

		kControlBackground,
		kControlActiveText,
		kControlText,
		kControlInactiveText,

		kEditActiveBackground,
		kEditInactiveBackground,
		kEditActiveText,
		kEditInactiveText,

		kActiveCellFrame,

		//Global
		hostGlobalBkColor,
		hostGlobalTextColor,

		//Button
		hostButton,
		hostButtonBkColor,
		hostButtonTextColor,

		//Edit
		hostEdit,
		hostEditBkColor,
		hostEditTextColor,

		//ComboBox
		hostComboBox,
		hostComboBoxBkColor,
		hostComboBoxTextColor,

		//TreeView
		hostTreeView,
		hostTreeViewBkColor,
		hostTreeViewTextColor,

		//ListView
		hostListView,
		hostListViewBkColor,
		hostListViewTextColor,

		//StatusBar
		hostStatusBarButton,
		hostStatusBarButtonTextColor,

		//Inspector
		hostInspCtrl,
		hostInspCtrlBkColor,
		hostInspCtrlTextColor,
		hostInspEditBkColor,
		hostInspEditTextColor,

		//Palettes
		hostPalette,
		hostPaletteBkColor,
		hostPaletteTextColor,
		hostPaletteBorderColor,

		//Tabs
		hostTab,
		hostTabBorderColor,
		hostTabBkColor,
		hostActiveTabBkColor,
		hostActiveTabTextColor,
		hostInactiveTabBkColor,
		hostInactiveTabTextColor,

		// Добавлять новые константы перед Last
		kColorUndefinedLast
	};

	enum McThemeElementState
	{
		kStateDontCare = 0,
		kStateDisabled = 1,
		kStateEnabled = 2,
		kStateHighlighted = 4
	};

	virtual void FillThemeBackground(HDC hDC, LPRECT pRect) = 0;
	virtual void DrawThemeHighlightRect(HDC hDC, LPRECT pRect) = 0;

	virtual COLORREF GetColor(McThemeElement element, McThemeElementState state = kStateDontCare) = 0;

	virtual bool isDark() = 0;
};
//=======================================================================================
// NOTE! 
// AGL for MCS5: context object is one and implemented in MECHCTL.DLL, 
// so all methods turned to pure virtual
struct IMcContext
{
	// application
	// main window handle
	virtual HRESULT        SetAppInfo(const AppInfo* pAppInfo) = 0;
	virtual HWND           GetMainWnd() = 0;
	virtual MCS_AppId      ApplicationId() = 0;
	virtual MCS_PlatformId PlatformId() = 0;
	virtual const long&    ConfigurationId() = 0;//Может быть комбинацией флажков
	virtual MCS_LangId     LangId() = 0;//Текущий язык может быть только один. Но теоритически он сможет переключаться.
	virtual LPCTSTR        LangName(MCS_LangId id) = 0;
	virtual long           CodePage(long lLangID = 0) = 0; //lLangID = 0 значит для текущего языка

	enum McCtxAppNameTypeEnum
	{
		kMcAppName_Full = 0,
		kMcAppName_Main,
		kMcAppName_Mod,
		kMcAppName_Short,
		kMcAppName_SysProductName,
		kMcAppName_SysProxyAppName
	};

	virtual LPCTSTR ApplicationName(McCtxAppNameTypeEnum eType = kMcAppName_Full) = 0;

	enum McCtxCompDevTypeEnum
	{
		kMcCompDevName_Main = 1,
		kMcCompDevName_Mod,
	};

	// Gets the name of the application's developer company
	virtual McsString CompanyDevName(McCtxCompDevTypeEnum eType) = 0;

	// returns numeric version 
	// use VER_MAJOR VER_MINOR VER_BUILD VER_REVISION, macroses to work with returned value
	enum VersionType {kMcVer_Product = 1, kMcVer_Core, kMcVer_Plm};
	virtual __int64 GetMCSVersion(VersionType verInfo) = 0;

	// resources
	virtual HICON Icon(long id) = 0;
	virtual HBITMAP Bitmap(long id) = 0;

	// help
	virtual M_RET Help(LPCTSTR id, CWnd* pWnd = NULL) = 0;
	virtual BOOL NormacsInstalled() = 0;
	virtual HRESULT NormacsShowStandard(LPCTSTR lpszStandard) = 0;

	// registry
	virtual IMcRegSaver* GetRegSaver(LPCTSTR strKey = NULL) = 0;

	// keyboard layout
	virtual M_RET SetKeyboardLayout(MCS_Layout layout = MCS_LAYOUT_AUTO) = 0;
	virtual M_RET RestoreKeyboardLayout() = 0;

	// last values
	virtual M_RET GetValues(LPCTSTR strKey, LPCTSTR strItem, mcsStringArray& array) = 0;
	virtual M_RET AddValue(LPCTSTR strKey, LPCTSTR strItem, LPCTSTR str, BOOL fRemoveDuplicate = TRUE, int iMaxSize = 15) = 0;

	// data folder
	virtual LPCTSTR GetDataPath(mcsDataPaths pathType) = 0;

	// error handling
	virtual void SymbolLoadError(LPCTSTR strSymbolName, int iSymbolVersion) = 0;

	// input monitor
	virtual IEntityMonitor* GetEntityMonitor() = 0; // GATE WRAPPER

	// returns addref-ed object
	virtual IMcs3dConstraintsManager* Get3dConstraintsManager() = 0; // GATE WRAPPER

	// hWndProgress - handle of ProgressBar(CommCtl)if hWndProgress==NULL - system progressBar
	// hWndText - text of the progress
	virtual IMcsProgress* GetProgress(HWND hWndProgress = NULL, HWND hWndText = NULL) = 0; // GATE WRAPPER
	virtual void SendDebugMessage(LPCTSTR strMessage) = 0;
	virtual void SendDebugMessageEx(LPCTSTR strMessageFormat,...) = 0;
	virtual IMcsGraphics* GetGraphics() = 0; // GATE WRAPPER
	virtual HRESULT GetPainter(OUT IMcPainterPtr& painter) = 0;
	virtual IMcTabManager* GetTabManager() = 0; // GATE WRAPPER

	// measures distance/diameter/angle in a document model;
	// returns distance/diameter in mm units and
	// angle in radians;
	// Values of i3dMode:
	//   0 - measure mode will depend on the type of running up;
	//   +1 - 3d measurement mode only,
	//   -1 - 2d measurement mode only
	virtual HRESULT Measure(
		OUT double& value,
		IN OPTIONAL LPCTSTR csPrompt,
		IN OPTIONAL McsMeasureTypeFilterEnum measureFilter,
		IN OPTIONAL int i3dMode = -1) = 0;// GATE WRAPPER

	virtual int MessageBox( LPCTSTR lpszText, UINT nType = MB_OK ) = 0;
	virtual int MessageBox(UINT nType, LPCTSTR strMessageFormat,...) = 0;

	//Show notification message
	enum NotificationMode
	{
		knmDefault = 0x0000,
		knmPopup   = 0x0001,
		knmNative  = 0x0002,
	};
	virtual HRESULT ShowNotification(LPCTSTR strMessage, NotificationMode mode = knmDefault) = 0;

	//Command registration, all command in try...catch, on errors will call abortTransaction
	virtual HRESULT RegisterCommand(mcsCmd& cmd) = 0; // GATE WRAPPER
	virtual HRESULT ExecuteCommand(LPCTSTR strCommand, bool bAutoPrefix = true, MCSVariant* pCustomParams = NULL, bool bIsCmdOption = false, bool IgnoreQueue = false) = 0; // GATE WRAPPER
	virtual HRESULT TestExecuteCommand(LPCTSTR strCommand, LPCTSTR lpszInput) = 0; // выполнение команд в режиме тестирования, звать внутри команды
	virtual HRESULT CancelCurCommand() = 0; // GATE WRAPPER	

	// <hWnd> parameters is used in case <pClientSink> represents <IMcWndHook> sink (subcluss for windows)
	virtual HRESULT AttachEventsSink(IMcEventsSink* pClientSink, HWND hWnd = NULL, HMODULE pModCaller = mcsGetCallerPtrModuleHandle()) = 0;
	virtual HRESULT DetachEventsSink(IMcEventsSink* pClientSink, HWND hWnd = NULL) = 0;

	virtual LPCTSTR SystemApplicationName() = 0;
	virtual bool    IsCommandEnabled(LPCTSTR strCmdName) {return false;}

		// returns full path to file containing UI configuration for current APP and PLM
	virtual McsString GetMenuCfgFileName() = 0;
		// returns full path to file containing UI icons for current APP and PLM
	virtual McsString GetMenuDllFileName() = 0;

		// загрузка/выгрузка MAPI-модулей
	virtual HRESULT LoadModule(LPCTSTR lpszPath) = 0;
	virtual HRESULT UnloadModule(LPCTSTR lpszPath) = 0;

	virtual IMcNativeEventsInput::McEventTypeEnum getCurrentEventType() = 0;
	virtual McCustomEventType                     getCurrentCustomEventType() = 0;

		// returns all currently executing commands in order of nesting
	virtual HRESULT getExecutingCommands(OUT mcsStringArray& cmdNames) = 0;

	// Existed image path. Find in Culture SubDirectory at first. Find in root images at last.
	virtual LPCTSTR GetImagePath(LPCTSTR pszFileName) = 0;

	virtual IMcTheme* GetTheme() = 0;

	virtual McsString GetCultureSubdir() = 0;

	// Возвращает текущий машстаб для монитора, к которому относится окно hWnd.
	// Если передано значение NULL, используется главное окно приложения GetMainWnd().
	virtual double getMonitorScalingFactor(HWND hWnd = NULL) = 0;
};
//=============================================================================

class CGridCtrl;
class CxTreeListCtrl;
class CListCtrl;
//=============================================================================
struct IMcRegSaver : IMObject
{
	virtual M_RET InitApp(LPCTSTR strApp) = 0;
	virtual M_RET InitKey(LPCTSTR strKey) = 0;

	virtual M_RET Put(LPCTSTR strItem, const CString& str) = 0;
	virtual M_RET Get(LPCTSTR strItem, CString& str) = 0;

	virtual M_RET Put(LPCTSTR strItem, const McsString& str) = 0;
	virtual M_RET Get(LPCTSTR strItem, McsString& str) = 0;


	virtual M_RET Put(LPCTSTR strItem, DWORD dwData) = 0;
	virtual M_RET Get(LPCTSTR strItem, DWORD& dwData) = 0;

	virtual M_RET Put(LPCTSTR strItem, REAL rValue) = 0;
	virtual M_RET Get(LPCTSTR strItem, REAL& rValue) = 0;

	virtual M_RET Put(LPCTSTR strItem, MCSUID) = 0;
	virtual M_RET Get(LPCTSTR strItem, MCSUID& uid) = 0;

	// if <pWnd> parameter will be passed with setted high order bit (i.e. | 0x80000000)
  // then parameter will be accepted with HWND type
	virtual M_RET Put(LPCTSTR strItem, CWnd* pWnd) = 0;
	virtual M_RET Get(LPCTSTR strItem, CWnd* pWnd) = 0;

	// if <pWnd> parameter will be passed with setted high order bit (i.e. | 0x80000000)
  // then parameter will be accepted with HWND type
	virtual M_RET Put(LPCTSTR strItem, CListCtrl* pList) = 0;
	virtual M_RET Get(LPCTSTR strItem, CListCtrl* pList) = 0;

	virtual M_RET Put(LPCTSTR strItem, CxTreeListCtrl* pList) = 0;
	virtual M_RET Get(LPCTSTR strItem, CxTreeListCtrl* pList) = 0;

	virtual M_RET Put(LPCTSTR strItem, CGridCtrl* pGrid) = 0;
	virtual M_RET Get(LPCTSTR strItem, CGridCtrl* pGrid) = 0;

	virtual M_RET Put(LPCTSTR strItem, const CStringArray& array) = 0;
	virtual M_RET Get(LPCTSTR strItem, CStringArray& array) = 0;

	virtual M_RET Put(LPCTSTR strItem, const mcsStringArray& array) = 0;
	virtual M_RET Get(LPCTSTR strItem, mcsStringArray& array) = 0;

	virtual M_RET AddFirst(LPCTSTR strItem, LPCTSTR str, BOOL fRemoveDuplicate = TRUE, int iMaxSize = 15) = 0;

	virtual M_RET Put(LPCTSTR strItem, const int* pData, int iNumItems) = 0;
	virtual M_RET Get(LPCTSTR strItem, int* array, int& iNumItems) = 0;  // передается максимальный размер массива, возвращается количество реально прочитанных
	virtual M_RET Get(LPCTSTR strItem, mcsIntArray& array) = 0;

  virtual M_RET Put(LPCTSTR strItem,LPCTSTR strToStore) = 0;
  virtual M_RET Get(LPCTSTR strItem,LPTSTR pStrBuffer,int maxBufferSize) = 0;

	virtual M_RET Put(LPCTSTR strItem, HWND hWnd) = 0;
	virtual M_RET Get(LPCTSTR strItem, HWND hWnd) = 0;

	virtual M_RET Put(LPCTSTR strItem, const double* pData, int nItems) = 0;
	virtual M_RET Get(LPCTSTR strItem, mcsDoubleArray& dblArr) = 0;

	virtual M_RET Put(LPCTSTR strItem, bool bData)
	{
		return Put(strItem, (DWORD)bData);
	};
	virtual M_RET Get(LPCTSTR strItem, bool& bData)
	{
		DWORD dw = 0;
		M_RET ret = Get(strItem, dw);
		if(ret == mOk){
			if(dw)
				bData = true;
			else
				bData = false;
		}
		return ret;
	};
};
typedef MObjPtr<IMcRegSaver> IMcRegSaverPtr;

//=============================================================================
extern "C" MECHCTL_API IMcContext* MCS_GetContext();
__inline IMcContext* MCS_GetContextDyn();
extern "C" MECHCTL_API void MCS_InitContext(IMcContext* pContext);
//=============================================================================
// примеры
//=============================================================================
/*
  // использование Context'а
	IMcContext* pContext = MCS_GetContext();
	if (pContext) {
		hIcon = pContext->Icon(MCS_ICON_APP);
		pContext->Release();
	}

	// пример записи значений; обычно вызывается в CDialog::OnOK()
	IMcRegSaver* pReg = gpMcContext->GetRegSaver();
	if (pReg) {
		pReg->Put("Dialog", this); // записать размеры и положение диалога
		pReg->Release();
	}

	// пример чтения значений; обычно вызывается в CDialog::OnInitDialog()
	IMcRegSaver* pReg = gpMcContext->GetRegSaver();
	if (pReg) {
		pReg->Get("Dialog", this); // прочитать размеры и положение диалога
		pReg->Release();
	}

	// пример инициализации; вызывается один раз при загрузке приложения
	IMcRegSaver* pReg = gpMcContext->GetRegSaver();
	if (pReg) {
		pReg->InitApp("MechaniCS");
		pReg->Release();
	}
*/


//=============================================================================
// Resources
//=============================================================================
#define MCS_ICON_APP 101       // application (MechaniCS)
#define MCS_ICON_MEASURE 102   // линейка для замера расстояний
#define MCS_ICON_DIM 103       // размер
#define MCS_ICON_HELP 104      // help



//=============================================================================
// inlines
//=============================================================================
typedef IMcContext* (*MCS_GetContextDynFunc)();
inline IMcContext* MCS_GetContextDyn()
{
	IMcContext* pContext = NULL;
	HINSTANCE hInst = GetModuleHandleA("MechCtl.dll");
/*
	if (!hInst) hInst = LoadLibraryA("MechCtl.dll");
*/
	if (!hInst) return NULL;
	MCS_GetContextDynFunc pFunc = (MCS_GetContextDynFunc)GetProcAddress(hInst, "MCS_GetContext");
	if (pFunc) pContext = pFunc();
	return pContext;
}
//=============================================================================

#define ER_LOADED_NUM 14444//temp

//=============================================================================
extern "C" MECHCTL_API bool McIsOnlineHelp();

//=============================================================================

#if !defined(_NCAD_BUILD_) && !defined(_MCS_CORE_ONLY)
	#include "MCSHelp.h"
#endif

//=============================================================================
