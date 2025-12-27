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

struct IMcsStream;

#include <comutil.h>
#include <atlbase.h>

#include "McAPIs.h"
#include "McsTempl.h"
#include "DynLoadMacro.h"

//===========================================================================
#define MCSVER_CORE    1
#define MCSVER_PRODUCT 2

/* version words 3-0 coded as:
  MmBR
  |||\--- revision
  ||\---- build number
  |\----- Product Minor version
  \------ Product Major version
*/

// returns version stored in VS_FIXEDFILEINFO block from portable executable (PE) file 
// if error occurred then returns 0
//   pvModule can be:
//     LPC(W)STR         - full path to portable executable (PE) file;
//     HMODULE,HINSTANCE - handle of loaded module in memory
//     NULL value        - version of MT.DLL
extern "C" MT_API __int64 GetModuleVersion(LPVOID pvModule);

// same as function above but can return more detailed information
// NOTE: LPTSTR buffer must must have at least 64 symbols length
extern "C" MT_API __int64 GetModuleVersionEx
(IN           LPVOID     pvModule, 
 IN OPTIONAL  DWORD      verType=MCSVER_CORE,    // valid values are: <MCSVER_CORE> or <MCSVER_PRODUCT>
 OUT OPTIONAL LPTSTR     lpszSimpleVer=NULL,     // in style 5.3.325.32769
 OUT OPTIONAL LPTSTR     lpszDecodedVer=NULL,    // in style 5.3.325
 OUT OPTIONAL LPTSTR     lpszDate=NULL,
 OUT OPTIONAL McsString* pStrSimpleVer=NULL,     // in style 5.3.325.32769
 OUT OPTIONAL McsString* pStrDecodedVer=NULL,    // in style 5.3.325
 OUT OPTIONAL McsString* pStrDate=NULL);         // in format 8.09.2004

extern "C" MT_API void FormatMcsProductVersion(WORD Major, WORD Minor, WORD build, WORD revision, OUT McsString& strver);

// helper macroses which allows to extract subversions from __int64 version
#define VER_MAJOR(ver64)    (((WORD*)(&(ver64)))[3])
#define VER_MINOR(ver64)    (((WORD*)(&(ver64)))[2])
#define VER_BUILD(ver64)    (((WORD*)(&(ver64)))[1])
#define VER_REVISION(ver64) (((WORD*)(&(ver64)))[0])
#define VER_MAKE(major, minor, build, revis) ( (((__int64)((WORD)(major))) << 48) | \
                                               (((__int64)((WORD)(minor))) << 32) | \
                                               (((__int64)((WORD)(build))) << 16) | \
                                               (((__int64)((WORD)(revis))) <<  0) )

//---------------------------------------------------------------------------
MCCORESYMBOLS_API_CPP McsString McShowSpecSymbols(HWND hParent = NULL, LPCTSTR stHelpTopic = NULL, LPCTSTR stPanelName = NULL, bool bMouseCenter = true, int x = 0, int y = 0);
inline McsString DynMcShowSpecSymbols(HWND hParent = NULL, LPCTSTR stHelpTopic = NULL, LPCTSTR stPanelName = NULL, bool bMouseCenter = true, int x = 0, int y = 0)
{
#ifdef WIN64
	FARPROC pFunc = GetProcAddress(GetModuleHandleA("mcCoreSymbols.dll"), "?McShowSpecSymbols@@YA?AVMcsStringW@@PEAUHWND__@@PEB_W1_NHH@Z");
#else//#ifdef WIN64
	FARPROC pFunc = GetProcAddress(GetModuleHandleA("mcCoreSymbols.dll"), "?McShowSpecSymbols@@YA?AVMcsStringW@@PAUHWND__@@PB_W1_NHH@Z");
#endif//#ifdef WIN64
	if(pFunc)
		return ((McsString(*)(HWND, LPCTSTR, LPCTSTR, bool, int, int))pFunc)(hParent, stHelpTopic, stPanelName, bMouseCenter, x, y);
	return _T("");
}

#ifdef UNICODE
	#define mcsLoadPicture					 mcsLoadPictureW
	#define mcsOleLoadPicture				 mcsOleLoadPictureW
	#define mcsForcedCreateDirectory mcsForcedCreateDirectoryW
	#define mcsRemoveDirectory			 mcsRemoveDirectoryW
	#define mcsGetFullPathFromPath	 mcsGetFullPathFromPathW
	#define mcsStoreDialogPosition	 mcsStoreDialogPositionW
	#define mcsRestoreDialogPosition mcsRestoreDialogPositionW
	#define mcsStoreLVColumns				 mcsStoreLVColumnsW
	#define mcsRestoreLVColumns			 mcsRestoreLVColumnsW
	#define mcsGetStrOption					 mcsGetStrOptionW
	#define mcsSetStrOption					 mcsSetStrOptionW
	#define mcsGetIntOption					 mcsGetIntOptionW
	#define mcsSetIntOption					 mcsSetIntOptionW
	#define aglMapFileAsArray				 aglMapFileAsArrayW
#else
	#define mcsLoadPicture					 mcsLoadPictureA
	#define mcsOleLoadPicture				 mcsOleLoadPictureA
	#define mcsForcedCreateDirectory mcsForcedCreateDirectoryA
	#define mcsRemoveDirectory			 mcsRemoveDirectoryA
	#define mcsGetFullPathFromPath	 mcsGetFullPathFromPathA
	#define mcsStoreDialogPosition	 mcsStoreDialogPositionA
	#define mcsRestoreDialogPosition mcsRestoreDialogPositionA
	#define mcsStoreLVColumns				 mcsStoreLVColumnsA
	#define mcsRestoreLVColumns			 mcsRestoreLVColumnsA
	#define mcsGetStrOption					 mcsGetStrOptionA
	#define mcsSetStrOption					 mcsSetStrOptionA
	#define mcsGetIntOption					 mcsGetIntOptionA
	#define mcsSetIntOption					 mcsSetIntOptionA
	#define aglMapFileAsArray				 aglMapFileAsArrayA
#endif

// .................................................................................................

// function loads BMP/GIF/JPG picture from resource of module in memory of from file;
// caller is responsible to delete created clone bitmap;
// If picture data is in memory then specify pointer to data in <hInstance>	parameter
// size of block in <csPictureResourceName> and <csPicFileName> to NULL
extern "C" MT_API 
HBITMAP 
mcsLoadPictureA
(IN LPVOID            hInstance, // module instance
 IN LPCSTR            csPictureResourceName, // RT_RCDATA | RT_BITMAP image resource name
 IN OPTIONAL LPCSTR   csPicFileName=NULL, // picture file
 IN OPTIONAL HRESULT* pErrorCode = NULL); // status error code

extern "C" MT_API 
HBITMAP 
mcsLoadPictureW
(IN LPVOID            hInstance, // module instance
 IN LPCWSTR           csPictureResourceName, // RT_RCDATA | RT_BITMAP image resource name
 IN OPTIONAL LPCWSTR  csPicFileName=NULL, // picture file
 IN OPTIONAL HRESULT* pErrorCode = NULL); // status error code

// function loads BMP/GIF/JPG picture from resource of module in memory of from file;
MT_API 
CComPtr<IPicture>
mcsOleLoadPictureA
(IN LPVOID            hInstance,
 IN LPCSTR            csPictureResourceName,
 IN OPTIONAL LPCSTR   csPicFileName,
 IN OPTIONAL HRESULT* pErrorCode);

MT_API 
CComPtr<IPicture>
mcsOleLoadPictureW
(IN LPVOID            hInstance,
 IN LPCWSTR           csPictureResourceName,
 IN OPTIONAL LPCWSTR  csPicFileName,
 IN OPTIONAL HRESULT* pErrorCode);

// function creates true color DIB section bitmap clone of input bitmap;
// caller is responsible to delete created clone bitmap;
// on error return value is NULL
extern "C" MT_API 
HBITMAP 
mcsCloneBitmap(HBITMAP hBmpSrc, int resizeToWidth = -1, int resizeToHeight = -1);

// determine whether the call is from the main thread
extern "C" MT_API bool mtIsMainThread();

// works as SHCreateDirectoryEx but on NT4+ and Win9x platforms
extern "C" MT_API HRESULT mcsForcedCreateDirectoryW(IN LPCWSTR DirPath);
extern "C" MT_API HRESULT mcsForcedCreateDirectoryA(IN LPCSTR DirPath);

// removes directory and its contents,
// optionally you can remove all subdirectories inside and contained files 
// by specific filter
extern "C" MT_API
HRESULT mcsRemoveDirectoryA
(IN LPCSTR           cstrDirPath, 
 IN OPTIONAL LPCSTR  cstrfilesFilter="*.*", // applies also for directories
 IN OPTIONAL bool    fRemoveAllSubDirs=true, // true to remove subdirectories
 IN OPTIONAL bool    fRemoveDirItself=true); // true to remove specified starting directory

extern "C" MT_API
HRESULT mcsRemoveDirectoryW
(IN LPCWSTR          cstrDirPath, 
 IN OPTIONAL LPCWSTR cstrfilesFilter=L"*.*", // applies also for directories
 IN OPTIONAL bool    fRemoveAllSubDirs=true, // true to remove subdirectories
 IN OPTIONAL bool    fRemoveDirItself=true); // true to remove specified starting directory

// function searches bytes template entry point in memory block (like <strstr> for strings);
// if <pMask> specified then it's size must be equal to template size and non zero value of 
// i-byte in mask tells to <mcsMemMem> to search exact pTemplate[i] template byte, zero
// value tells to function that i-byte may have any value at the entry point;
// if template will be not found the function will return NULL
extern "C" MT_API
void* mcsMemMem
(IN const void*          pSrc, 
 IN DWORD                dwSourceSize,
 IN const void*          pTemplate,
 IN DWORD                dwTemplateSize,
 IN OPTIONAL const byte* pMask=NULL);

// function returns in <strFullPath> full path of the input file <csPath>;
// <csPath> may be either full path ("C:\TEMP\file.ext") or relative path ("..\..\file.ext") 
// (from specified module instance directory), or short relative path ("subdir\file.ext");
// if file exists and path will be located then function returns S_OK;
extern "C" MT_API
HRESULT mcsGetFullPathFromPathA
(IN  LPCSTR    csPath,
 IN  LPCVOID    pvBaseInstance,
 OUT McsStringA& strFullPath);

extern "C" MT_API
HRESULT mcsGetFullPathFromPathW
(IN  LPCWSTR    csPath,
 IN  LPCVOID    pvBaseInstance,
 OUT McsStringW& strFullPath);

// Low level helper proc. Helps to trace BP-based frame call stack faster by 50 times 
// than std StackWalk functions;
// for WIN32 processes only, for 64-bit will return error
extern "C" MT_API
bool mcsEdsFastBPStackWalk32(
	IN HANDLE hProcess, 
	IN DWORD ProcessID, 
  IN OUT DWORD& EIP,
	IN OUT DWORD& EBP,
	IN OUT DWORD& ESP);

// returns EIP/RIP for next instruction following the "call" instruction
extern "C" MT_API UINT_PTR mtGetEIP(int dummy = 0);

// return 32 for WIN32 process, 64 for 64-bit process, 0 in other cases
extern "C" MT_API int mtGetProcessBits(DWORD pid);

// function returns call stack addresses;
// first address in the list will be address of next instruction after instruction which calls this proc
// NOTE-> Only for current process and for calling thread
// NOTE-> Only BP-Based frame stack gathered
extern "C" MT_API
HRESULT mcsEdsGetCallStack
(IN DWORD           dwMaxEntries,
 OUT mcsUIntPtrArray& addrList,
 IN OPTIONAL bool   fExcludeMTAddressesFromTop = true);

// acts like the 'mcsEdsGetCallStack' but memory allocation is a caller's responsibility
extern "C" MT_API
bool mcsEdsGetCallStackRaw
(IN DWORD         dwMaxEntries,
 OUT DWORD&       dwGotEntries,
 OUT UINT_PTR*    pAddrList,
 IN OPTIONAL bool fExcludeMTAddressesFromTop = true);

// allow to translate call stack addresses,
// can store information in strings list and can drop call stack to IDM (InDebMon)
// (!) NOTE: 
//     Only for current process and for calling thread
extern "C" MT_API
HRESULT mcsEdsFormatCallStack
(IN const mcsUIntPtrArray&    addrList,
 IN OPTIONAL bool             fDropCallStackToIDM = true,
 OUT OPTIONAL McsStringA*     pStrAllInfo = NULL,           // all info into single string
 OUT OPTIONAL mcsStringArrayA*pStrArrCallStackInfo = NULL); 

// returns instance handle for specified pointer, if NULL passed then HANDLE of 
// caller's module will be returned
// NOTE: method uses VirtualQuery function call and 100% guarantees success;
// on error returns INVALID_HANDLE_VALUE
extern "C" MT_API 
HMODULE mcsGetCallerPtrModuleHandle(IN OPTIONAL LPCVOID pSmth=NULL);

// выдает список установленного оборудования, 
// либо в виде одной строки, где каждый элемент оборудования одной подстрокой представлен,
// либо массивом строк; если оба параметра пропущены, то конфикурация будет выдаваться в
// отладчик
extern "C" MT_API 
HRESULT mtGetHardwareConfiguration(
	OUT OPTIONAL McsString* pStrHWConf=NULL, 
	OUT OPTIONAL mcsStringArray* pStrArrHWConf=NULL);

// конвертирует WMF в EMF, результат EMF создается на памяти
// исходный хэндл сохраняется, результат нужно освобождать
// с помощью <DeleteEnhMetaFile>
extern "C" MT_API
HENHMETAFILE mtConvertWMF2EMF(HMETAFILE hWMF);

// проверяет тип входной картинки, если она PICTYPE_METAFILE,
// то конвертирует ее в PICTYPE_ENHMETAFILE и создает новую
// картинку, входная сохраняется;
// если входная картинка не старый метафайл, то выдается 
// входная без изменения;
// если не удалось преобразовать картинку то выходной параметр будет NULL
MT_API
CComPtr<IPicture> mtConvertPictureIfWMF2EMF(IPicture*);

// Verifies digital signature for input PE file;
// S_OK    - if file has signature and it is valid
// S_FALSE - if no signature exists
// E_FAIL  - if signature present but broken or error happened
extern "C" MT_API
HRESULT mtVDS(LPCTSTR cstrFilePath);

//.........................................//
struct mcsStackEntry
{
  UINT_PTR   dwAddress;
  McsStringA strModuleName;
  UINT_PTR   dwModuleOffset;
  McsStringA strSymbolName;
  UINT_PTR   dwSymbolOffset;
  McsStringA srcFileName;
  int        nLine;
  bool       fVerified;

  mcsStackEntry()
  {
    strModuleName="unknown";
    strSymbolName=strModuleName;

    dwAddress=-1;
    dwModuleOffset=-1;
    dwSymbolOffset=-1;
    nLine=-1;
    fVerified=false;
  }
};
typedef McsArray<mcsStackEntry, const mcsStackEntry&> mcsStackEntries;
//.........................................//

#define MTN_START    1 // param = number of points
#define MTN_STOP     2 // 
#define MTN_PROGRESS 3 // param = points done
typedef bool (__stdcall * mcsMadCallStackNotifyProc)(IN int notification, IN DWORD param);

// performs private/alien thread hard stack scanning, which allows to detect 
//   ALL(!) call stack entries, not only for procedures which BP-based stack frames;
//   Tracing method uses smart stack contents filtering with adjusting stack data to call 
//   code templates
// (!) NOTE: In case when specified thread is not current thread, function suspends threads 
//      execution, gathers call stack information and resumes thread again;
// (!) NOTE: function doesn't check IDs correspondence, i.e. you MUST pass ID of thread with 
//     belongs to process with specified ID.
// (!) NOTE: set symbols search path by "mcsInitializeSymbolsInformation" before
#define exp_mt_mcsEdsGetMadCallStack "mcsEdsGetMadCallStack"
extern "C" MT_API 
HRESULT mcsEdsGetMadCallStack
(IN DWORD                      ProcessID,         // process identifier, pass -1 for current
 IN DWORD                      ThreadID,          // thread identifier, pass -2 for current
 IN bool                       fUseBPStackFrames, // if true then function works as <mcsEdsGetCallStack>
 IN OPTIONAL  DWORD            dwMaxEntries,      // forces limitation for number of call stack entries
 IN OPTIONAL  bool             fDropToIdm,        // if true drops call stack to IDM (Independent Debugging Monitor)
 OUT OPTIONAL McsStringA*      pSingleStrStack,   // text formatted call stack data in single string, entries are separated by "\r\n"
 OUT OPTIONAL mcsStringArrayA* pMultipleStrStack, // array of text formatted stack entries 
 OUT OPTIONAL mcsStackEntries* pEntries,          // array of stack entries
 IN OPTIONAL mcsMadCallStackNotifyProc pNotifyProc=NULL); // may be used for progress bar

// reports that MT.DLL was built as Unicode application
extern"C" MT_API bool isUnicodeMt();

// stores in [mcs.ini]/registry [winpos] section position of specified window with the specified name;
// if <fStoreAllChildren> flag is specified then function stores position and state for each 
// children window of the specified window;
// for registry path valid form is "HKCU\<path>" or "HKLM\<path>", in this folder 
// will be created values with position data
extern "C" MT_API HRESULT mcsStoreDialogPositionA
(IN LPCSTR dialogName, 
 IN HWND hWnd, 
 IN OPTIONAL bool fStoreAllChildren=false,
 IN OPTIONAL DWORD resourceCheckSum=0, //	if non 0 then this number stored for controlling that saved data corresponds to contents of dialog
 IN OPTIONAL LPCSTR strRegistryPath=NULL);

extern "C" MT_API HRESULT mcsStoreDialogPositionW
(IN LPCWSTR dialogName, 
 IN HWND hWnd, 
 IN OPTIONAL bool fStoreAllChildren=false,
 IN OPTIONAL DWORD resourceCheckSum=0,
 IN OPTIONAL LPCWSTR strRegistryPath=NULL);

// restores stored position accept children controls position if available and allowed
extern "C" MT_API HRESULT mcsRestoreDialogPositionA
(IN LPCSTR dialogName, 
 IN HWND hWnd, 
 IN OPTIONAL bool fRestoreAllChildrenIfAvailable=false, 
 IN OPTIONAL DWORD resourceCheckSum=0,
 IN OPTIONAL LPCSTR strRegistryPath=NULL);

extern "C" MT_API HRESULT mcsRestoreDialogPositionW
(IN LPCWSTR dialogName, 
 IN HWND hWnd, 
 IN OPTIONAL bool fRestoreAllChildrenIfAvailable=false, 
 IN OPTIONAL DWORD resourceCheckSum=0,
 IN OPTIONAL LPCWSTR strRegistryPath=NULL);

// stores/restores widths of columns in LV control;	...........................
// Be sure that control has LVS_REPORT style
extern "C" MT_API HRESULT mcsStoreLVColumnsA(IN LPCSTR strWndName, IN HWND hWndListView);
extern "C" MT_API HRESULT mcsStoreLVColumnsW(IN LPCWSTR strWndName, IN HWND hWndListView);
extern "C" MT_API HRESULT mcsRestoreLVColumnsA(IN LPCSTR strWndName, IN HWND hWndListView);
extern "C" MT_API HRESULT mcsRestoreLVColumnsW(IN LPCWSTR strWndName, IN HWND hWndListView);

// this is wrapper to Win32 API "OpenThread" function, wrapper is safe to be used in static 
// module linkage on all windows platforms;
// See more information in MSDN for function "OpenThread"
typedef HANDLE (__stdcall* OpenThreadProc)(DWORD,BOOL,DWORD);
extern "C" MT_API
HANDLE mcsOpenThread
(DWORD ThreadDesiredAccessFlags, 
 BOOL  fHandleIsInheritable,
 DWORD ThreadId);

#define mtOpenThread mcsOpenThread

#ifndef GR_GDIOBJECTS
	#define GR_GDIOBJECTS 0
#endif

#ifndef GR_USEROBJECTS
	#define GR_USEROBJECTS 1
#endif

typedef DWORD (__stdcall* GetGuiResourcesProc)(HANDLE, DWORD);
extern "C" MT_API
DWORD mtGetGuiResources(HANDLE, DWORD);

#ifndef STATUS_UNSUCCESSFUL
	#define STATUS_UNSUCCESSFUL 0xC0000001L
#endif

#ifndef STATUS_INFO_LENGTH_MISMATCH
	#define STATUS_INFO_LENGTH_MISMATCH 0xC0000004L
#endif

#ifndef STATUS_SUCCESS
	#define STATUS_SUCCESS 0L
#endif

typedef DWORD (__stdcall* NtQuerySystemInformationProc)(DWORD, PVOID, ULONG, PLONG);
extern "C" MT_API
DWORD mtNtQuerySystemInformation
(IN DWORD sysInfoClass,
 IN OUT PVOID pSysInfo,
 IN ULONG sysInfoLen,
 OUT OPTIONAL PLONG RetLen);

// function assumes specified symbols search paths with specified process and (re)initializes
// symbols engine (IMAGEHLP.DLL);
// path is directly passed to "IMAGEHLP.DLL!SymSetSearchPath" function, so U can see additional 
// info in MSDN
extern "C" MT_API
HRESULT mcsInitializeSymbolsInformation(DWORD ProcessID, LPCSTR symbolsPath);

extern "C" MT_API
HRESULT mcsResetSymbolsInformation(DWORD ProcessID);

extern "C" MT_API
HRESULT mcsResetAllSymbolsInformation();

// updates list of modules in specified process, need to translate symbols info for specific process;
// ensure <mcsInitializeSymbolsInformation> was called before
extern "C" MT_API
HRESULT mcsRescanModulesList(DWORD ProcessID);

// gets info about specific address in specific process;
// ensure <mcsInitializeSymbolsInformation> and	<mcsRescanModulesList> called before
extern "C" MT_API
HRESULT mcsFormatAddressInfo(
	IN DWORD ProcessID, IN UINT_PTR addr, OUT McsStringA& strInfo, bool fShortModName,
	OUT OPTIONAL McsStringA* pModuleName=NULL, OUT OPTIONAL UINT_PTR* pDwModOffset=NULL,
	OUT OPTIONAL McsStringA* pSymbolName=NULL, OUT OPTIONAL UINT_PTR* pDwSymOffset=NULL,
	OUT OPTIONAL McsStringA* pSrcFileName=NULL, OUT OPTIONAL DWORD* pDwLineNum=NULL);

// will return true if is called from specific module
// NOTE-> Only for current process and for calling thread
// NOTE-> Only BP-Based frame stack gathered
extern "C" MT_API
bool mcsCheckCallIsFrom(IN LPCTSTR cstrModuleName);

extern "C" MT_API
__int64 mcsGetCurrentTime();

// Функция форматирует число с плавающей точкой в строку.
// Если значение числа по модулю находится в пределах 9e12 > dbl > 9e-5,
// то форматирование выполняется по схеме "x.y", где x - это цифры до десятичного
// разделителя, а y - после.
// Иначе используется стандартный формат %f.
// 
// Реализовано так, что функция пытается нивелировать ошибки представления десятичных чисел.
//
MCTYP_API McsString formatDoubleAccurate(double dbl);

#define MCSLDR_FORCE_UNLOAD    1
#define MCSLDR_KEEP_ON_UNLOAD -1

// module information struct
struct mcsModuleInfo
{
	LPCTSTR  csModuleName; // full or short or relative path of the module
	long     lData;        // custom data
	int      iForceUnload; // if >0 then <mcsUnloadApp> will try to kill specified module in memory, 0 - default behavior, and <0 - skip unloading 
	bool     fDisableAlienInstanceCheck; // if true then module with short name can be loaded from another directory
	HMODULE  hModule;      // handle of loaded module
	DWORD    dwSize;       // size in bytes if loaded image in memory

	// при конверсии списков из статического в динамический (это нужно для подгрузки плагинов), 
	// требуется сохранить указатель на статическую структуру данных о модуле
	mcsModuleInfo* pStaticClone;
};

typedef McsArray<mcsModuleInfo, const mcsModuleInfo&> mcsModuleInfoArray;

#define exp_mt_mcsLdrCvtModulesList "mcsLdrCvtModulesList"
extern "C"
MT_API
HRESULT mcsLdrCvtModulesList
(IN const mcsModuleInfo* pStaticModulesList, 
 OUT mcsModuleInfoArray& dynModulesList);

enum mtLdrEventEnum
{
	kMtLdrEvent_BeforeLoad      = 1,
	kMtLdrEvent_AfterLoad       = 2,
	kMtLdrEvent_LoadCopmplete   = 3,

	kMtLdrEvent_BeforeInit      = 4,
	kMtLdrEvent_AfterInit       = 5,
	kMtLdrEvent_InitCopmplete   = 6,

	kMtLdrEvent_BeforeReInit    = 7,
	kMtLdrEvent_AfterReInit     = 8,
	kMtLdrEvent_ReInitCopmplete = 9,

	kMtLdrEvent_BeforeUnInit    = 10,
	kMtLdrEvent_AfterUnInit     = 11,
	kMtLdrEvent_UnInitComplete  = 12,

	kMtLdrEvent_BeforeUnload    = 13,
	kMtLdrEvent_AfterUnload     = 14,
	kMtLdrEvent_UnloadComplete  = 15,
};

#define MTCTL_LDR_APP_LOADED      0x50A0
#define MTCTL_LDR_APP_UNLOADED    0x50A1
#define MTCTL_LDR_CAN_UNLOAD_CORE 0x50A2

typedef void (*McsLdrCallBackProc)(mtLdrEventEnum eventType, LPCTSTR strModuleName, HMODULE hM, mcsModuleInfo* pUserModuleInfo);

//==============================================================================

struct AppInfo
{
	AppInfo() {
		memset(this, 0, sizeof(*this));
		eAssocMcsFtrEnabledByPresence = -1; // kMcFeature_Null
		eAssocMcsFtrEnabledByFlex = -1; // kMcFeature_Null
	}

	TCHAR   szAppNameCfgr[100];       // Internal name od app for Configurator only

	TCHAR   szCfgNameSys[MAX_PATH];   // (Conf-r, Cml) name of record in base MCDATA.DLL list if valid config substitutions
	TCHAR   szAppNameSys[32];         // (Conf-r) System Name Application Name (app id in Configurator)
	TCHAR   szAppNameForUser[100];    // (Conf-r) General Application Name visible for user (Russian-lang implied)
	TCHAR   szAppNameForUserInt[100]; // (Conf-r) International Application Name visible for user
	TCHAR   szCompanyName[100];       // (Conf-r)
	TCHAR   szCompanyNameInt[100];    // (Conf-r) international
	TCHAR   szCompanyNameForPaths[100]; // (Conf-r) Internal company name for integrate it into paths for files on disk
	TCHAR   szSuppEMail[100];         // (Conf-r)
	TCHAR   szCmdPrefix[10];          // (Conf-r) cmd prefix for commands
	TCHAR   szCmdLocalPrefix[10];     // (Conf-r) local cmd prefix for commands
	TCHAR   szProductver[10];         // (Conf-r) format: "major.minor"
	TCHAR   szRegPath[MAX_PATH];      // (Conf-r) If empty autoconstruct by CompanyName\AppName\Version placed in HKCU\Software
	TCHAR   szAppDataPath[MAX_PATH];  // internal use, for addins
	TCHAR   szMenuIconsFileName[50];  // (Conf-r) smth like "mechanics_menu10.dll"
	TCHAR   szMenuCfgFileName[50];    // (Conf-r) smth like "plantracer_menu6.mnu"

		// true if config must be used as base AppInfo
		// there must be specifies valid FlexLM feature for szCfgNameSys in base MCDATA.DLL
	bool    bUseAsBaseConfig;        // (Conf-r, Cml)

		// assoc feature from McFeatures_enum, kMcFeature_Null (-1) if no such exists
		// feature is enabled if CFG file with it will be found
	DWORD   eAssocMcsFtrEnabledByPresence; // (Conf-r)

		// assoc feature from McFeatures_enum, kMcFeature_Null (-1) if no such exists
		// feature is enabled if there is valid license for FlexLM feature
	DWORD   eAssocMcsFtrEnabledByFlex;  // (Conf-r)

		// required !
	DWORD   dwAppID; // (Conf-r)
	DWORD   dwCfgID; // (Conf-r)

		// if true then assoc config will be used only in international (langid != 1049) builds
	bool    bInternational; // (Conf-r, Cml)

	__declspec(property(get = _get_AppNameForUser, put = _put_AppNameForUser)) LPCTSTR AppNameForUser;
	__declspec(property(get = _get_CompanyName, put = _put_CompanyName))       LPCTSTR CompanyName;
	__declspec(property(get = _get_CompanyName4p, put = _put_CompanyName4p))   LPCTSTR CompanyNameForPaths;
	__declspec(property(get = _get_ProdVer, put = _put_ProdVer))               LPCTSTR ProdVer;

	LPCTSTR _get_AppNameForUser() {
		return bInternational ? szAppNameForUserInt : szAppNameForUser; 
	}

	void _put_AppNameForUser(LPCTSTR sz) {
		if(!sz)
			sz = _T("");
		if(bInternational)
			_tcsncpy_s(szAppNameForUserInt, sz, _TRUNCATE);
		else
			_tcsncpy_s(szAppNameForUser, sz, _TRUNCATE);
	}

	LPCTSTR _get_CompanyName() {
		return bInternational ? szCompanyNameInt : szCompanyName;
	}

	void _put_CompanyName(LPCTSTR sz) {
		if(!sz)
			sz = _T("");
		if(bInternational)
			_tcsncpy_s(szCompanyNameInt, sz, _TRUNCATE);
		else
			_tcsncpy_s(szCompanyName, sz, _TRUNCATE);
	}

	LPCTSTR _get_CompanyName4p() {
		return szCompanyNameForPaths;
	}

	void _put_CompanyName4p(LPCTSTR sz) {
		if(!sz)
			sz = _T("");
		_tcsncpy_s(szCompanyNameForPaths, sz, _TRUNCATE);
	}

	LPCTSTR _get_ProdVer() {
		return szProductver; 
	}

	void _put_ProdVer(LPCTSTR sz) {
		if(!sz)
			sz = _T("");
		_tcsncpy_s(szProductver, sz, _TRUNCATE);
	}
};

typedef McsMapEx<DWORD, DWORD, AppInfo, const AppInfo&> mcsMapDw2AppInfo;

struct IMtStream;

extern "C" {
	MT_API bool mtSavePlmsAppInfo(
		IN const mcsMapDw2AppInfo& PlmToAppInfo,
		IN LPCTSTR                 lpszSysCfgName,
		IN bool                    bUseAsBaseCfg,
		IN bool                    bInternational,
		IN OUT IMtStream*          pS);

	MT_API bool mtLoadPlmsAppInfo(IN IMtStream* pS, OUT mcsMapDw2AppInfo& PlmToAppInfo);
}

//==============================================================================

struct IMcAppLoader
{
	virtual HRESULT  InitAppProfle(IN const AppInfo* pProfle, IN const GUID* pAppID) = 0;

	virtual const AppInfo* GetAppProfile() = 0;

	virtual HRESULT  LoadApp(
		OUT DWORD_PTR& dwpLdrHandle,
		IN OUT mcsModuleInfo* pModules,
		IN LPCTSTR strPath,
		IN bool bEnabler,
		IN OPTIONAL McsLdrCallBackProc pCallBack = NULL,
		IN OPTIONAL bool fAutoLoadMCX = true,
		IN OPTIONAL bool fMAPIMode = false) = 0;

	virtual HRESULT  UninitApp(
		IN DWORD_PTR dwpLdrHandle,
		IN OPTIONAL McsLdrCallBackProc pCallBack = NULL,
		IN OPTIONAL bool fMAPIMode = false) = 0;

	// when returned handle <dwpLdrHandle> will be invalid
	virtual HRESULT  UnloadApp(
		IN DWORD_PTR dwpLdrHandle,
		IN OUT OPTIONAL mcsModuleInfo *pModules = NULL,
		IN OPTIONAL bool fSkipUninit = false,
		IN OPTIONAL McsLdrCallBackProc pCallBack = NULL,
		IN OPTIONAL bool fMAPIMode = false) = 0;
};

	// f4MAPIModules
#define exp_mt_mtGetAppLoader "mtGetAppLoader"
extern "C" MT_API IMcAppLoader* mtGetAppLoader();
typedef IMcAppLoader* (__cdecl * MtAppLoaderProc)();

/*
Function loads specified set of modules into memory with their statically linked modules in 
correspondent order. This function locks modules in memory and guarantees that every imported module
will be in memory until dependent on them modules are in memory.
You can pass to function module which already is loaded to lock its static dependent modules in memory.

<pLoaction> parameter determines current directory for loading. By default it is the directory from where
MT.DLL is loaded. You can pass full directory path or handle of another module.
Pass "" for load modules using all paths in %PATH% environment's variable.

<fAutoLoadMCX>, if "true" then loader tries to find *.mcx files in given location, loads list of
MAPI modules from them, and tries to load them too.

returns S_OK if all specified modules are successfully loaded.
S_FALSE if any module from the list is not loaded.
*/

extern "C"
MT_API
HRESULT mcsLoadModules
(OUT DWORD_PTR& dwpLdrHandle,
 IN OUT mcsModuleInfoArray& modules,
 IN OPTIONAL LPCVOID pLocation = NULL,
 IN OPTIONAL McsLdrCallBackProc pCallBack = NULL,
 IN OPTIONAL bool fAutoLoadMCX = true);

// function unloads modules previously loaded by function <mcsLoadApp>
// list of modules to unload is identified by < dwpLdrHandle >
extern "C"
MT_API
HRESULT mcsUnloadModules
(IN DWORD_PTR dwpLdrHandle, 
 IN OPTIONAL McsLdrCallBackProc pCallBack = NULL);

extern "C"
MT_API
bool mtLdrGetAllLoadedModules(OUT mcsModuleInfoArray& modules);

// function determines class of memory object.
// generally it may be useful do detect that object is constant or created on the stack
enum MemoryClassEnum
{
  kMemCLass_Unknown,
  kMemCLass_Auto,
  kMemCLass_Static,
  kMemCLass_ConstStatic,
  kMemCLass_Dynamic,
};

extern "C"
MT_API
MemoryClassEnum GetMemoryClass(LPCVOID ptr);

// Queries type info information  from IDispatch interface;
// If any DISP member will be not found in interface then MemberID will be 0

extern "C"
MT_API
HRESULT mcsGetDispatchInfo
(IN IDispatch*            pDisp, 
 IN OPTIONAL LPCTSTR*     pcsMemberNames=NULL,
 IN OPTIONAL DWORD        uNNames=0,
 OUT OPTIONAL MEMBERID*   pDispMemberIds=NULL,
 OUT OPTIONAL GUID*       pDispImplType=NULL,
 OUT OPTIONAL McsString*  pTypeName=NULL); /// associated Name with GUID of ImplType


extern "C" MT_API bool mcsCS(LPCSTR str,byte* data);
extern "C" MT_API bool mcsDS(const byte* data,int size,LPSTR str);

// if default value leaved for <SectionName> then MT stores options in [MT] section
// if default value leaved for <IniFileName> then <gstrMcsIniName> macro will be used and
// ini file itself will be places near binary modules
extern "C" MT_API long       mcsGetIntOptionA(LPCSTR cstrOptionName, long defaultValue, LPCSTR SectionName=NULL, LPCSTR IniFileName = NULL);
extern "C" MT_API HRESULT    mcsSetIntOptionA(LPCSTR cstrOptionName, long Value, LPCSTR SectionName=NULL, LPCSTR IniFileName = NULL);
           MT_API McsStringA mcsGetStrOptionA(LPCSTR cstrOptionName, LPCSTR strDefaultValue=NULL, LPCSTR SectionName=NULL, LPCSTR IniFileName = NULL);
extern "C" MT_API HRESULT    mcsSetStrOptionA(LPCSTR cstrOptionName, LPCSTR strValue, LPCSTR SectionName=NULL, LPCSTR IniFileName = NULL);

extern "C" MT_API long       mcsGetIntOptionW(LPCWSTR cstrOptionName, long defaultValue, LPCWSTR SectionName=NULL, LPCWSTR IniFileName = NULL);
extern "C" MT_API HRESULT    mcsSetIntOptionW(LPCWSTR cstrOptionName, long Value, LPCWSTR SectionName=NULL, LPCWSTR IniFileName = NULL);
           MT_API McsStringW mcsGetStrOptionW(LPCWSTR cstrOptionName, LPCWSTR strDefaultValue=NULL, LPCWSTR SectionName=NULL, LPCWSTR IniFileName = NULL);
extern "C" MT_API HRESULT    mcsSetStrOptionW(LPCWSTR cstrOptionName, LPCWSTR strValue, LPCWSTR SectionName=NULL, LPCWSTR IniFileName = NULL);

// helper: for ListView controls returns first selected item index or value<0 if no such
MT_API int     mcsLVGetFirstSel(HWND hListView);
// helper: for ListView selects specified item and deselects all other
MT_API HRESULT mcsLVSelectSingleItem(HWND hListView, int iItem);

// Helpers: stores/restores window state for current process session only;
// Now implemented only for TreeView controls;
// for them function stores state of items(text,expansion,selection);
// on restore function compares texts and if them are equal it restores expansion and selection
// (NOTE: works fine both for ANSI and UNICODE windows)
//		20.05.2011...............
// mcsStoreWindowState(hw1, 1);
// mcsStoreWindowState(hw2, 1);
// this example will copy state of hw1 to windows hw2
MT_API HRESULT mcsStoreWindowState(HWND hWnd, DWORD_PTR dwStateID = 0);
MT_API HRESULT mcsRestoreWindowState(HWND hWnd, DWORD_PTR dwStateID = 0);

MT_API HRESULT mcsAdjustMaximumProcessPrivileges();

MT_API bool mcsIsRunAsAdmin();

// <dwCreationDisposition> will be passed to appropriate arg CreateFile
MT_API PVOID aglMapFileAsArrayA
(IN LPCSTR cstrFileName, 
 IN bool fWriteAcccess, 
 IN DWORD dwCreationDisposition, 
 OUT DWORD& fileSize);

MT_API PVOID aglMapFileAsArrayW
(IN LPCWSTR cstrFileName, 
 IN bool fWriteAcccess, 
 IN DWORD dwCreationDisposition, 
 OUT DWORD& fileSize);

// closes and flushes file to disk (in write mode), pointer must be gotten by <aglMapFileAsArray>
MT_API HRESULT aglUnmapFileArray(IN LPCVOID pMappedData);

	// opens the specified file at the specified line in the specified Visual Studio;
	// mscVer is a value of _MSC_VER build-in marco variable of a MSVC compiler;
	// 1200 - VS 1998 - 6.0
	// 1300 - VS 2002 - 7.0
	// 1310 - VS 2003 - 7.1
	// 1400 - VS 2005 - 8.0
	// 1500 - VS 2008 - 9.0
	// 1600 - VS 2010 - 10.0
	// 1700 - VS 2012 - 11.0
	// 1800 - VS 2013 - 12.0
	// 1900 - VS 2015 - 14.0
	// 1913 - VS 2017 - 14.1

extern "C" MT_API HRESULT mtDevEnvGotoFileLineA(LPCSTR pathA, long line, int mscVer);
extern "C" MT_API HRESULT mtDevEnvGotoFileLineW(LPCWSTR path, long line, int mscVer);
#ifdef UNICODE
	#define mtDevEnvGotoFileLine mtDevEnvGotoFileLineW
#else
	#define mtDevEnvGotoFileLine mtDevEnvGotoFileLineA
#endif

#define ATL_BASE64_FLAG_NONE   0
#define ATL_BASE64_FLAG_NOPAD  1
#define ATL_BASE64_FLAG_NOCRLF 2

// length in chars
MT_API int mtBase64EncodeGetRequiredLength(int nSrcLen, DWORD dwFlags = ATL_BASE64_FLAG_NONE);
MT_API int mtBase64DecodeGetRequiredLength(int nSrcLen);

MT_API BOOL mtBase64EncodeW
(const BYTE* pbSrcData,
 int         nSrcLen,
 LPWSTR      szDestW,
 int*        pnDestLen,
 DWORD       dwFlags = ATL_BASE64_FLAG_NONE);

MT_API BOOL mtBase64EncodeA
(const BYTE* pbSrcData,
 int         nSrcLen,
 LPSTR       szDestA,
 int*        pnDestLen,
 DWORD       dwFlags = ATL_BASE64_FLAG_NONE);

MT_API BOOL mtBase64DecodeW(LPCWSTR szSrcW, int nSrcLen, BYTE *pbDest, int *pnDestLen);
MT_API BOOL mtBase64DecodeA(LPCSTR szSrcA, int nSrcLen, BYTE *pbDest, int *pnDestLen);

#ifdef UNICODE
	#define mtBase64Encode mtBase64EncodeW
	#define mtBase64Decode mtBase64DecodeW
#else
	#define mtBase64Encode mtBase64EncodeA
	#define mtBase64Decode mtBase64DecodeA
#endif

MT_API HRESULT mtPackData(const byte* pInput, DWORD inputSz, OUT mcsByteArray& compressed);
MT_API HRESULT mtUnpackData(const byte* pInput, DWORD inputSz, OUT mcsByteArray& uncompressed);

MT_API UINT mtCalcHash(LPCVOID pData, size_t len);

// находит шлюз вызова процедуры <lpszProcNameA> из модуля <lpszModuleNameFrom> в модуль <lpszModuleNameTo>
MT_API DWORD_PTR* mtGetImportThunk(IN LPCSTR lpszProcNameA, IN LPCSTR lpszModuleNameFromA, IN LPCSTR lpszModuleNameToA);

MT_API bool mtMapAndLoadA(IN LPCSTR lpszImagePathA, IN bool fReadOnly, OUT LOADED_IMAGE* pLoadedImage);
MT_API bool mtMapAndLoadW(IN LPCWSTR lpszImagePathW, IN bool fReadOnly, OUT LOADED_IMAGE* pLoadedImage);

MT_API bool mtUnMapAndLoad(IN OUT LOADED_IMAGE* pLoadedImage);

#ifdef UNICODE
	#define mtMapAndLoad                  mtMapAndLoadW
#else
	#define mtMapAndLoad                  mtMapAndLoadA
#endif

// получает список модулей, прописанных в секции импорта модуля lpszImagePathA
// при ошибке вернет false
extern "C" MT_API bool mtGetModuleDependenciesA(IN LPCSTR lpszImagePathA, OUT mcsStringArrayA& dependenciesA);
extern "C" MT_API bool mtGetModuleDependenciesW(IN LPCWSTR lpszImagePathW, OUT mcsStringArrayW& dependenciesW);

#ifdef UNICODE
	#define mtGetModuleDependencies       mtGetModuleDependenciesW
#else
	#define mtGetModuleDependencies       mtGetModuleDependenciesA
#endif

// Returns size of dialog units for given window in pixels.
// du_x_pix - size in pixels of horizontal dialog unit
// du_y_pix - size in pixels of vertical dialog unit
extern "C" MT_API bool mtGetDlgUnitsSize(HWND hDlg, double& du_x_pix, double& du_y_pix);

//==============================================================================
// initializes genrand64 with a seed
extern "C" MT_API void mt_init_genrand64(unsigned __int64 seed);

// generates a random number on [0, 2^64-1]-interval
extern "C" MT_API unsigned __int64 mt_genrand64_int64(void);

// generates a random number on [0, 2^63-1]-interval
extern "C" MT_API __int64 mt_genrand64_int63(void);

// generates a random number on [0,1]-real-interval
extern "C" MT_API double mt_genrand64_real1(void);

// generates a random number on [0,1)-real-interval
extern "C" MT_API double mt_genrand64_real2(void);

// generates a random number on (0,1)-real-interval
extern "C" MT_API double mt_genrand64_real3(void);
//==============================================================================
// initializes genrand32 with a seed
extern "C" MT_API void mt_init_genrand32(unsigned long s);

// generates a random number on [0,0xffffffff]-interval
extern "C" MT_API unsigned long mt_genrand32_int32(void);

// generates a random number on [0,0x7fffffff]-interval
extern "C" MT_API long mt_genrand32_int31(void);

// generates a random number on [0,1]-real-interval
extern "C" MT_API double mt_genrand32_real1(void);

// generates a random number on [0,1)-real-interval
extern "C" MT_API double mt_genrand32_real2(void);

// generates a random number on (0,1)-real-interval
extern "C" MT_API double mt_genrand32_real3(void);
//===========================================================================
struct PerformanceStatus
{
	TCHAR     strName[256];
	DWORD_PTR WorkingSet; // bytes
	DWORD_PTR VirtualSize; // bytes
	int       GDIObjects;
	int       UserObjects;
	int       Handles;
	double    time; // mcs

	PerformanceStatus(){
		empty();
	}

	bool isEmpty() const {
		return !WorkingSet && !VirtualSize && !GDIObjects && !UserObjects && !Handles &&!time;
	}

	void empty(){
		strName[0]=0;
		WorkingSet = 0;
		VirtualSize = 0;
		GDIObjects = 0;
		UserObjects = 0;
		Handles = 0;
		time = 0;
	}

	PerformanceStatus& operator += (const PerformanceStatus& s)
	{
		WorkingSet += s.WorkingSet;
		VirtualSize += s.VirtualSize;
		GDIObjects += s.GDIObjects;
		UserObjects += s.UserObjects;
		Handles += s.Handles;
		time += s.time;
		return *this;
	}

	PerformanceStatus& operator -= (const PerformanceStatus& s)
	{
		WorkingSet -= s.WorkingSet;
		VirtualSize -= s.VirtualSize;
		GDIObjects -= s.GDIObjects;
		UserObjects -= s.UserObjects;
		Handles -= s.Handles;
		time -= s.time;
		return *this;
	}
};
typedef McsArray<PerformanceStatus, const PerformanceStatus&> PerformanceStatusArray;
//=============================================================================
__inline PerformanceStatus operator + (const PerformanceStatus& s1, const PerformanceStatus& s2)
{
	PerformanceStatus res = s1;
	res += s2;
	return res;
}
//=============================================================================
__inline PerformanceStatus operator - (const PerformanceStatus& s1, const PerformanceStatus& s2)
{
	PerformanceStatus res = s1;
	res -= s2;
	return res;
}
//=============================================================================
struct PerformanceStatusMulty : public PerformanceStatusArray
{
};
//=============================================================================
#define exp_mt_mtGetCurrentPerformanceStatus "mtGetCurrentPerformanceStatus"
extern "C" MT_API HRESULT mtGetCurrentPerformanceStatus(IN OPTIONAL LPCTSTR name, OUT PerformanceStatus& status);

#define exp_mt_mtFormatPerfStatus "mtFormatPerfStatus"
extern "C" MT_API HRESULT mtFormatPerfStatus(
	IN const PerformanceStatus& status,
	OUT OPTIONAL McsString* pStrResult = NULL,
	IN OPTIONAL bool fDropToIDM = true,
	IN OPTIONAL bool fAppendHeader = false,
	IN OPTIONAL int nCharsColName = 25);

#define exp_mt_mtFormatPerfStatusMulty "mtFormatPerfStatusMulty"
extern "C" MT_API HRESULT mtFormatPerfStatusMulty(
	IN const PerformanceStatusMulty& statusMulty,
	IN OPTIONAL LPCTSTR cstrDumpName = NULL,
	OUT OPTIONAL McsString* pStrResult = NULL,
	IN OPTIONAL bool fDropToIDM = true,
	IN OPTIONAL int nCharsColName = 25);
//=============================================================================
__inline HRESULT mtGetCurrentPerformanceStatusDyn(IN OPTIONAL LPCTSTR name, OUT PerformanceStatus& status, HINSTANCE hCoInstance)
{
	status.empty();
	FARPROC pProc = NULL;
	DYN_GET_PROC_ADDRESS(pProc, _T("MT.DLL"), exp_mt_mtGetCurrentPerformanceStatus, hCoInstance);
	if(!pProc)
		return E_FAIL;
	return ((HRESULT(*)(LPCTSTR, PerformanceStatus&))pProc) (name, status);
}
//===========================================================================
__inline HRESULT mtFormatPerfStatusDyn(
	IN OPTIONAL HINSTANCE hCoInstance, // may be NULL, but if MT.DLL is not loaded proc can fail
	IN const PerformanceStatus& status,
	OUT OPTIONAL McsString* pStrResult = NULL,
	IN OPTIONAL bool fDropToIDM = true,
	IN OPTIONAL bool fAppendHeader = false,
	IN OPTIONAL int nCharsColName = 25)
{
	//if(pStrResult)
	//	pStrResult->Empty(); // causes static link to MT.DLL
	FARPROC pProc = NULL;
	DYN_GET_PROC_ADDRESS(pProc, _T("MT.DLL"), exp_mt_mtFormatPerfStatus, hCoInstance);
	if(!pProc)
		return E_FAIL;
	return 
		((HRESULT(*)(const PerformanceStatus&, McsString*, bool, bool, int)) pProc)
			(status, pStrResult, fDropToIDM, fAppendHeader, nCharsColName);
}
//===========================================================================
__inline HRESULT mtFormatPerfStatusMultyDyn(
	IN OPTIONAL HINSTANCE hCoInstance, // may be NULL, but if MT.DLL is not loaded proc can fail
	IN const PerformanceStatusMulty& statusMulty,
	IN OPTIONAL LPCTSTR cstrDumpName = NULL,
	OUT OPTIONAL McsString* pStrResult = NULL,
	IN OPTIONAL bool fDropToIDM = true,
	IN OPTIONAL int nCharsColName = 25)
{
	//if(pStrResult)
	//	pStrResult->Empty(); // causes static link to MT.DLL
	FARPROC pProc = NULL;
	DYN_GET_PROC_ADDRESS(pProc, _T("MT.DLL"), exp_mt_mtFormatPerfStatusMulty, hCoInstance);
	if(!pProc)
		return E_FAIL;
	return 
		((HRESULT(*)(const PerformanceStatusMulty&, LPCTSTR, McsString*, bool, int)) pProc)
			(statusMulty, cstrDumpName, pStrResult, fDropToIDM, nCharsColName);
}
//===========================================================================


#define _cmp_via_type(type) ((type*)NULL)

#define GetKeyMember_InArr(ArrPtr,Idx,KeyMemberOffset,KeyValType) \
  *((KeyValType*)(LPBYTE((ArrPtr)+(Idx))+(KeyMemberOffset)))

#define GetKeyMember_InRefsArr(ArrPtr,Idx,KeyMemberOffset,KeyValType) \
  *((KeyValType*)(LPBYTE((ArrPtr)[Idx])+(KeyMemberOffset)))

//===========================================================================
template <class IT,class ITSort> 
void _qsort
(IT*     pArr,
 int     iFrom,
 int     iUpTo,
 bool    fAscent,
 int     KeyMemberOffset,
 ITSort* _KeyTypePtr,
 bool    fDontSwapEqual = false)
{
	if(IsInvalidPtr(pArr)) 
		return;
	if(iFrom==iUpTo) 
		return;

	int Lo=iFrom, Hi=iUpTo;
	ITSort midval = GetKeyMember_InArr(pArr, (Lo+Hi)/2, KeyMemberOffset, ITSort);
	do 
	{
		if(fAscent)  {
			while(GetKeyMember_InArr(pArr, Lo, KeyMemberOffset, ITSort) < midval) 
				Lo++;
			while(GetKeyMember_InArr(pArr, Hi, KeyMemberOffset, ITSort) > midval) 
				Hi--;
		} else {
			while(GetKeyMember_InArr(pArr, Lo, KeyMemberOffset, ITSort) > midval) 
				Lo++;
			while(GetKeyMember_InArr(pArr, Hi, KeyMemberOffset, ITSort) < midval) 
				Hi--;
		}
		if(Lo>Hi) 
			break;
		if(Hi==Lo) {
			Lo++; Hi--; 
			break;
		}
		if(fDontSwapEqual) 
		{
			// 30.07.2008, AGL
			// если поля элементов для сортировки совпадают, то не нужно выполнять 
			// обмен элементов Hi, Lo;
			// нужно для сохранения порядка элементов в случае поочередной сортировки 
			// по разным полям, 
			// например: структуры в массиве сначала сортируем по одному полю, 
			// а потом а некотором диапазоне под другому полю, и если поля для второй 
			// сортировки одинаковы, то нарушается порядок элементов после первой сортировки
			if(GetKeyMember_InArr(pArr, Lo, KeyMemberOffset, ITSort) != GetKeyMember_InArr(pArr, Hi, KeyMemberOffset, ITSort))
				_swap(pArr[Lo], pArr[Hi]);
		} else {
			_swap(pArr[Lo], pArr[Hi]);
		}
		Lo++; Hi--;
	}while(Lo <= Hi);

	if(Hi > iFrom) 
		_qsort(pArr, iFrom, Hi, fAscent, KeyMemberOffset, _KeyTypePtr, fDontSwapEqual);
	if(Lo < iUpTo) 
		_qsort(pArr, Lo, iUpTo, fAscent, KeyMemberOffset, _KeyTypePtr, fDontSwapEqual);
}
//===========================================================================
template <class IT,class ITSort> 
void _qsort_refs
(IT**    pArr,
 int     iFrom,
 int     iUpTo,
 bool    fAscent,
 int     KeyMemberOffset,
 ITSort* _KeyTypePtr,
 bool    fDontSwapEqual = false)
{
	if(IsInvalidPtr(pArr)) 
		return;
	if(iFrom==iUpTo) 
		return;

	int Lo=iFrom, Hi=iUpTo;
	ITSort midval = GetKeyMember_InRefsArr(pArr, (Lo+Hi)/2, KeyMemberOffset, ITSort);
	do 
	{
		if(fAscent) {
			while(GetKeyMember_InRefsArr(pArr, Lo, KeyMemberOffset, ITSort) < midval) 
				Lo++;
			while(GetKeyMember_InRefsArr(pArr, Hi, KeyMemberOffset, ITSort) > midval) 
				Hi--;
		} else {
			while(GetKeyMember_InRefsArr(pArr, Lo, KeyMemberOffset, ITSort) > midval) 
				Lo++;
			while(GetKeyMember_InRefsArr(pArr, Hi, KeyMemberOffset, ITSort) < midval) 
				Hi--;
		}
		if(Lo>Hi) 
			break;
		if(Hi==Lo) {
			Lo++; Hi--; break;
		}
		if(fDontSwapEqual) 
		{
			// 30.07.2008, AGL
			// см. комментарий в _qsort выше
			if(GetKeyMember_InRefsArr(pArr, Lo, KeyMemberOffset, ITSort) != GetKeyMember_InRefsArr(pArr, Hi, KeyMemberOffset, ITSort))
				_swap(pArr[Lo], pArr[Hi]);
		} else {
			_swap(pArr[Lo], pArr[Hi]);
		}
		Lo++; Hi--;
	}while(Lo <= Hi);

	if(Hi > iFrom) 
		_qsort_refs(pArr, iFrom, Hi, fAscent, KeyMemberOffset, _KeyTypePtr, fDontSwapEqual);
	if(Lo < iUpTo) 
		_qsort_refs(pArr, Lo, iUpTo, fAscent, KeyMemberOffset, _KeyTypePtr, fDontSwapEqual);
}
//===========================================================================
template <class IT,class ITCmp> 
HRESULT _check_order(IT*    pArr,
                     int    nItems,
                     bool   fAscent,
                     int    KeyMemberOffset,
                     ITCmp* _KeyTypePtr)
{
  if(nItems<0) return S_FALSE;
  if(nItems==1) return S_OK;
  ITCmp* pPC=&GetKeyMember_InArr(pArr,0,KeyMemberOffset,ITCmp);
  for(int i=1; i<nItems; i++)
  {
    ITCmp* pPC2=&GetKeyMember_InArr(pArr,i,KeyMemberOffset,ITCmp);
    if(fAscent)
    {
      if(*pPC>*pPC2) 
        return S_FALSE;
    }
    else
    {
      if(*pPC<*pPC2) 
        return S_FALSE;
    }
    pPC=pPC2;
  }
  return S_OK;
}
//===========================================================================
template <class IT,class ITCmp> 
HRESULT _check_order_ref(IT**    pArr,
                         int     nItems,
                         bool    fAscent,
                         int     KeyMemberOffset,
                         ITCmp*  _KeyTypePtr)
{
  if(nItems<0) return S_FALSE;
  if(nItems==1) return S_OK;
  ITCmp* pPC=&GetKeyMember_InRefsArr(pArr,0,KeyMemberOffset,ITCmp);
  for(int i=1; i<nItems; i++)
  {
    ITCmp* pPC2=&GetKeyMember_InRefsArr(pArr,i,KeyMemberOffset,ITCmp);
    if(fAscent)
    {
      if(*pPC>*pPC2) 
        return S_FALSE;
    }
    else
    {
      if(*pPC<*pPC2) 
        return S_FALSE;
    }
    pPC=pPC2;
  }
  return S_OK;
}
//===========================================================================
template <class IT,class ITCmp> 
int _bsearch_idx(IT*    pArr,
                 int    nItems,
                 bool   fSortedAscent,
                 int    KeyMemberOffset,
                 ITCmp& SearchTemplate)
{
  if(nItems<=0) return -1;
  if(nItems<=4)
  {
    if(GetKeyMember_InArr(pArr,0,KeyMemberOffset,ITCmp)==SearchTemplate) return 0;
    if(nItems==1) return -1;
    if(GetKeyMember_InArr(pArr,1,KeyMemberOffset,ITCmp)==SearchTemplate) return 1;
    if(nItems==2) return -1;
    if(GetKeyMember_InArr(pArr,2,KeyMemberOffset,ITCmp)==SearchTemplate) return 2;
    if(nItems==3) return -1;
    if(GetKeyMember_InArr(pArr,3,KeyMemberOffset,ITCmp)==SearchTemplate) return 3;
    return -1;
  }
  int iLo=0, iHi=nItems-1, iMid=(nItems>>1);
  while(iLo<iHi)
  {
    if(GetKeyMember_InArr(pArr,iMid,KeyMemberOffset,ITCmp)==SearchTemplate) return iMid;
    bool f=GetKeyMember_InArr(pArr,iMid,KeyMemberOffset,ITCmp)<SearchTemplate;
    if(!fSortedAscent) f=!f;
    if(f)
    {
      iLo=iMid+1;
      iMid=(iLo+iHi)/2;
      continue;
    }
    iHi=iMid-1;
    iMid=(iLo+iHi)/2;
  }
  //...
  if(GetKeyMember_InArr(pArr,iLo,KeyMemberOffset,ITCmp)==SearchTemplate) 
    return iLo;
  return -1;
}
//===========================================================================
template <class IT,class ITCmp> 
int _bsearch_idx_ref(IT**   pArr,
                     int    nItems,
                     bool   fSortedAscent,
                     int    KeyMemberOffset,
                     ITCmp& SearchTemplate)
{
  if(nItems<=0) return -1;
  if(nItems<=4)
  {
    if(GetKeyMember_InRefsArr(pArr,0,KeyMemberOffset,ITCmp)==SearchTemplate) return 0;
    if(nItems==1) return -1;
    if(GetKeyMember_InRefsArr(pArr,1,KeyMemberOffset,ITCmp)==SearchTemplate) return 1;
    if(nItems==2) return -1;
    if(GetKeyMember_InRefsArr(pArr,2,KeyMemberOffset,ITCmp)==SearchTemplate) return 2;
    if(nItems==3) return -1;
    if(GetKeyMember_InRefsArr(pArr,3,KeyMemberOffset,ITCmp)==SearchTemplate) return 3;
    return -1;
  }
  int iLo=0, iHi=nItems-1, iMid=(nItems>>1);
  while(iLo<iHi)
  {
    if(GetKeyMember_InRefsArr(pArr,iMid,KeyMemberOffset,ITCmp)==SearchTemplate) return iMid;
    bool f=GetKeyMember_InRefsArr(pArr,iMid,KeyMemberOffset,ITCmp)<SearchTemplate;
    if(!fSortedAscent) f=!f;
    if(f)
    {
      iLo=iMid+1;
      iMid=(iLo+iHi)/2;
      continue;
    }
    iHi=iMid-1;
    iMid=(iLo+iHi)/2;
  }
  //...
  if(GetKeyMember_InRefsArr(pArr,iLo,KeyMemberOffset,ITCmp)==SearchTemplate) return iLo;
  return -1;
}
//===========================================================================

#undef GetKeyMember_InArr
#undef GetKeyMember_InRefsArr


//===========================================================================
template <class IT,class ITCmp> 
int _bsearch_idx2(IT*    pArr,
                  int    nItems,
                  bool   fSortedAscent,
                  int    KeyMemberOffset,
                  ITCmp& SearchTemplate)
{
  if(nItems<=0) return -1;
  if(nItems<=4)
  {
    if(pArr[0] == SearchTemplate) return 0;
    if(nItems==1) return -1;
    if(pArr[1] == SearchTemplate) return 1;
    if(nItems==2) return -1;
    if(pArr[2] == SearchTemplate) return 2;
    if(nItems==3) return -1;
    if(pArr[3] == SearchTemplate) return 3;
    return -1;
  }
  int iLo=0, iHi=nItems-1, iMid=(nItems>>1);
  while(iLo<iHi)
  {
    if(pArr[iMid] == SearchTemplate) return iMid;
    bool f = pArr[iMid] < SearchTemplate;
    if(!fSortedAscent) f=!f;
    if(f)
    {
      iLo=iMid+1;
      iMid=(iLo+iHi)/2;
      continue;
    }
    iHi=iMid-1;
    iMid=(iLo+iHi)/2;
  }
  //...
  if(pArr[iLo] == SearchTemplate) 
    return iLo;
  return -1;
}
//=============================================================================

#include "McsTempl.h"
#include <float.h>

struct _TimeIntervalData
{
  double m_SumTime_mcs;
  long   m_count;

  _TimeIntervalData()
  {
    m_SumTime_mcs=0;
    m_count=0;
  }
};
typedef McsArray<_TimeIntervalData, const _TimeIntervalData&> _TimeIntervalDataArray;
//===========================================================================
class McsStopWatch
{
public:
	_TimeIntervalDataArray m_Intervals, m_IntervalsPure;
	mcsDoubleArray m_percentage, m_percentagePure;
	mcsDoubleArray m_avgTimePerInterval_mcs, m_avgTimePerIntervalPure_mcs;
	double         m_LastTime_mcs;   // <reset> and <beginMeasure> don't clear this time
	int            m_iNextInterval;
	double         m_TotalTime_mcs, m_TotalTimePure_mcs;
	int            m_TotalCount;
	bool           m_fLocked;
	double         m_FreqDelim;
	double         m_mti;

	//............................................................................
	McsStopWatch()
	{
		m_fLocked = false;

		LARGE_INTEGER li; QueryPerformanceFrequency(&li);
		m_FreqDelim = 1.0/(__int64&)li;
		m_iNextInterval = 0;
		m_TotalTime_mcs = 0; m_TotalTimePure_mcs = 0;
		m_TotalCount = 0;
		m_mti = _sGetMTIDuration();
		m_Intervals.SetSize(0, 100); m_IntervalsPure.SetSize(0, 100);
		beginMeasure();
	}
	//............................................................................
	~McsStopWatch()
	{
	}
	//............................................................................
	void reset(void)
	{
		m_TotalCount=0;
		m_TotalTime_mcs=0; m_TotalTimePure_mcs=0;
		m_iNextInterval = 0;

		m_Intervals.SetSize(0, 100); m_IntervalsPure.SetSize(0, 100);
		m_avgTimePerInterval_mcs.RemoveAll();
		m_IntervalsPure.RemoveAll();
		m_percentagePure.RemoveAll();
		m_avgTimePerIntervalPure_mcs.RemoveAll();

		m_fLocked = false;
		beginMeasure();
	}
	//............................................................................
	void beginMeasure(void)
	{
		m_LastTime_mcs = _getMcs();
	}
	//............................................................................
	void Lock() // blocks measurement
	{
		m_fLocked = true;
	}
	//............................................................................
	// unlocks measurement and drops time interval between calls to <Lock> <Unlock>
	void Unlock() 
	{
		if(!m_fLocked)
			return;
		m_fLocked = false;
		beginMeasure();
	}
	//............................................................................
	int getNextAutoInterval()
	{
		return m_iNextInterval;
	}
	//............................................................................
	void setNextAutoInterval(int iNextAutoInterval)
	{
		if(iNextAutoInterval<0)
			return;
		m_iNextInterval = iNextAutoInterval;
	}
	//............................................................................
	void setNumberOfIntervals(int nNewSize)
	{
		m_Intervals.SetSize(nNewSize);
	}
	//............................................................................
	// returns immediately measured time interval in microseconds (mcs)
	double markTimeInterval(int a_iInterval=-1)
	{
		if(m_fLocked)
			return 0;
		
		int iTargetInterval = a_iInterval < 0 ? m_iNextInterval : a_iInterval;
		if(iTargetInterval >= m_Intervals.GetSize()) {
			int nExtraIntervals = iTargetInterval - m_Intervals.GetSize() + 1;
			m_Intervals.SetSize(m_Intervals.GetSize() + nExtraIntervals, 50);
			m_IntervalsPure.SetSize(m_IntervalsPure.GetSize() + nExtraIntervals, 50);
		}

		// accumulate measure data for desired interval
		double cur_mcs = _getMcs();
		double interval_time_mcs = cur_mcs - m_LastTime_mcs;
		double interval_time_pure_mcs = interval_time_mcs - m_mti;
		if(interval_time_pure_mcs < 0)
			interval_time_pure_mcs = 0;

		m_Intervals.GetData()[iTargetInterval].m_SumTime_mcs += interval_time_mcs;
		m_Intervals.GetData()[iTargetInterval].m_count++;

		m_IntervalsPure.GetData()[iTargetInterval].m_SumTime_mcs += interval_time_pure_mcs;
		m_IntervalsPure.GetData()[iTargetInterval].m_count++;

		m_TotalTime_mcs += interval_time_mcs; m_TotalTimePure_mcs += interval_time_pure_mcs; 
		m_TotalCount++;
		m_LastTime_mcs = cur_mcs;

		// prepare to measure next interval
		m_iNextInterval = iTargetInterval + 1;
		return interval_time_mcs;
	}
	//............................................................................
	double getInterval_mcs_avg(int iInterval)
	{
		if(iInterval < 0 || iInterval >= m_Intervals.GetSize()) 
			return 0;
		int count=m_Intervals[iInterval].m_count; 
		if(count<=0) 
			return 0;
		return m_Intervals[iInterval].m_SumTime_mcs / count;
	}
	//............................................................................
	double getInterval_mcs_avg_pure(int iInterval)
	{
		if(iInterval < 0 || iInterval >= m_IntervalsPure.GetSize()) 
			return 0;
		int count = m_IntervalsPure[iInterval].m_count; 
		if(count<=0) 
			return 0;
		double res = m_IntervalsPure[iInterval].m_SumTime_mcs / count;
		return res;
	}
	//............................................................................
	double getInterval_mcs_sum(int iInterval)
	{
		if(iInterval < 0 || iInterval >= m_Intervals.GetSize()) 
			return 0;
		return m_Intervals[iInterval].m_SumTime_mcs;
	}
	//............................................................................
	double getInterval_mcs_sum_pure(int iInterval)
	{
		if(iInterval < 0 || iInterval >= m_IntervalsPure.GetSize()) 
			return 0;
		return m_IntervalsPure[iInterval].m_SumTime_mcs;
	}
	//............................................................................
	double getTotal_mcs()
	{
		return m_TotalTime_mcs;
	}
	//............................................................................
	double getTotal_mcs_pure()
	{
		return m_TotalTimePure_mcs;
	}
	//............................................................................
	int getIntervalMeasureCount(int iInterval)
	{
		if(iInterval < 0 || iInterval >= m_Intervals.GetSize()) 
			return 0;
		return m_Intervals[iInterval].m_count;
	}
	//............................................................................
	void calcPercentage()
	{
		int nIntervals = m_Intervals.GetSize();
		m_percentage.SetSize(nIntervals);
		m_percentagePure.SetSize(nIntervals);
		if(!nIntervals)
			return;
		// if total time will be 0.0 then +INF will be placed into percentage
		for(int i=0; i<nIntervals; i++) {
			m_percentage[i]     = 100.0 * m_Intervals[i].m_SumTime_mcs / m_TotalTime_mcs;
			m_percentagePure[i] = 100.0 * m_IntervalsPure[i].m_SumTime_mcs / m_TotalTimePure_mcs;
		}
	}
	//............................................................................
	void calcAvgTime4Intervals()
	{
		int nIntervals = m_Intervals.GetSize();
		m_avgTimePerInterval_mcs.SetSize(nIntervals);
		m_avgTimePerIntervalPure_mcs.SetSize(nIntervals);
		if(!nIntervals)
			return;
		// if total time will be 0.0 then +INF will be placed into percentage
		for(int i=0; i<nIntervals; i++) {
			m_avgTimePerInterval_mcs[i]     = m_Intervals[i].m_SumTime_mcs / m_Intervals[i].m_count;
			m_avgTimePerIntervalPure_mcs[i] = m_IntervalsPure[i].m_SumTime_mcs / m_IntervalsPure[i].m_count;
		}
	}
	//............................................................................
	double _getMcs(void)
	{
		LARGE_INTEGER li; QueryPerformanceCounter(&li);
		return 1000000.0*(__int64&)li*m_FreqDelim;
	}
	//............................................................................

private:

	static double _sGetMTIDuration(void)
	{
		static double ls_mti = 0;
		if(ls_mti)
			return ls_mti;
		static bool fInProc=false;
		// !!! prevent from recursive calls to this procedure
		if(fInProc)
			return 0;

		fInProc = true;

		HANDLE hProc=GetCurrentProcess(); DWORD CurPC=GetPriorityClass(hProc);  SetPriorityClass(hProc,REALTIME_PRIORITY_CLASS);
		HANDLE hThrd=GetCurrentThread();  int   CurTP=GetThreadPriority(hThrd); SetThreadPriority(hThrd,THREAD_PRIORITY_TIME_CRITICAL);

		McsStopWatch MSW; MSW.markTimeInterval(3); // ensure memory presence for intervals during measurement
		double duration = 0;
		for(int cycle=1000; cycle>0; cycle--)
		{
			MSW.m_Intervals[0].m_count=0; MSW.m_Intervals[0].m_SumTime_mcs=0;
			MSW.m_Intervals[1].m_count=0; MSW.m_Intervals[1].m_SumTime_mcs=0;
			MSW.m_Intervals[2].m_count=0; MSW.m_Intervals[2].m_SumTime_mcs=0;
			//...
			MSW.markTimeInterval(0); MSW.markTimeInterval(1); MSW.markTimeInterval(2);
			//if(MSW.m_Intervals[1].m_SumTime_mcs < duration) duration = MSW.m_Intervals[1].m_SumTime_mcs;
			//if(MSW.m_Intervals[2].m_SumTime_mcs < duration) duration = MSW.m_Intervals[2].m_SumTime_mcs;
			duration += MSW.m_Intervals[1].m_SumTime_mcs;
			duration += MSW.m_Intervals[2].m_SumTime_mcs;
		}

		duration /= 2000.0;

		// restore priorities
		SetThreadPriority(hThrd,CurTP); SetPriorityClass(hProc,CurPC);

		fInProc = false;
		ls_mti = duration;
		return duration;
	}
};
//==============================================================================

// GLobal set of named stopwatches, for ANSI and Unicode names;
// these can be browsed by off-process tool - McEye

// Example of use: gMtSW[_T("my stop watch")].markTimeInterval(0);

typedef McsMapEx<McsStringA, LPCSTR, McsStopWatch, const McsStopWatch&> mapStrA2SW;
typedef McsMapEx<McsStringW, LPCWSTR, McsStopWatch, const McsStopWatch&> mapStrW2SW;
typedef McsMapEx<McsString, LPCTSTR, McsStopWatch, const McsStopWatch&> mapStr2SW;

#define exp_mt_gMtSWA "gMtSWA"
extern "C" MT_API mapStrA2SW gMtSWA;

#define exp_mt_gMtSWW "gMtSWW"
extern "C" MT_API mapStrW2SW gMtSWW;

#define exp_mt_gIndex2Kind "gIndex2Kind"

#ifdef UNICODE
	#define gMtSW gMtSWW
#else
	#define gMtSW gMtSWA
#endif

#include "IMcUnitConverter.h"
