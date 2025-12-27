#ifndef __OPENDWG_APPLICATIONDB_H__
#define __OPENDWG_APPLICATIONDB_H__

#include "nrxdbgate_impexp.h"


#ifdef ncedIsDragging
	#undef ncedIsDragging
#endif // ncedIsDragging

class CArchive;
class CMapStringToPtr;
class CMapWordToPtr;
class ClipBoundaryArray;

class HostEditor;
class HostEditorReactor;
class HostEdUIContext;
class HostPlotSettingsValidator;

class NcDbAbstractClipBoundaryDefinition;
class NcDbAppSystemVariables;
class NcDbGlobals;
class NcDbHatch;
class NcDbEntity;
class NcDbPlotSettingsValidator;
class NcDbTransactionManager;
class NcDbLayerStateManagerReactor;
class NcDbUndoController;

class NcRxDictionary;
class NcTransaction;
class NcTransactionReactor;
class NcRxGenHand;
class NcRxDLinkerReactor;

class NcRxVariableReactor;

class NcadInternalServices;
class NcPwdCache;

class NcDbHostApplicationServices;

struct flagmat;

#define ncdbCurDwg   ncdbHostApplicationServices()->workingDatabase

#define  ncdbGetRGB  ncedGetRGB

extern "C" {typedef NcRx::AppRetCode (*DepFuncPtr)(NcRx::AppMsgCode, void*);}

struct NcUt {
	enum QFormatBitFlags {
		kSuppressZeroFeet     = 0x100,
		kSuppressZeroInches   = 0x200,
		kSuppressLeadingZero  = 0x400,
		kSuppressTrailingZero = 0x800,
		kIgnoreUnitMode       = 0x1000,
		kUseAltUnits          = 0x2000
	};
};

typedef struct fchnd {
	struct fchnd *next;
	int fcode;
	int (*fhdl)();
} FunHandList;

enum NcXrefSubCommand {
	kAttach = 0,
	kBind = 1,
	kDetach = 2,
	kOverlay = 3,
	kPath = 4,
	kReload = 5,
	kResolve = 6,
	//kUnload = 7,
	kXBind = 8
};

typedef Nano::ErrorStatus (*SELECTFILEPROC )(/*[out]*/ short *userCancel,
                                             /*[out]*/ NCHAR *& chosenPath,
                                             void* h, // HWND
                                             const int nFlags,
                                             const NCHAR * prompt,
                                             const NCHAR * dir,
                                             const NCHAR * name,
                                             const NCHAR * type,
                                             int* pnChoice,
                                             bool* pbReadOnly,
                                             const NCHAR * pszWSTags,
                                             void* pReserved);

typedef Nano::ErrorStatus (* REMAPPROC) (/*[out]*/ NCHAR *& newName,
                                         const NCHAR * filename,
                                         int context,
                                         void* pReserved);

typedef void (* MAPFILENOTIFYPROC) (const NCHAR * filename,
                                    const NCHAR * newName,
                                    int context,
                                    void* pReserved);

typedef enum {
	CODE_PAGE_UNDEFINED = 0,
	CODE_PAGE_ASCII,
	CODE_PAGE_8859_1,
	CODE_PAGE_8859_2,
	CODE_PAGE_8859_3,
	CODE_PAGE_8859_4,
	CODE_PAGE_8859_5,
	CODE_PAGE_8859_6,
	CODE_PAGE_8859_7,
	CODE_PAGE_8859_8,
	CODE_PAGE_8859_9,
	CODE_PAGE_DOS437,
	CODE_PAGE_DOS850,
	CODE_PAGE_DOS852,
	CODE_PAGE_DOS855,
	CODE_PAGE_DOS857,
	CODE_PAGE_DOS860,
	CODE_PAGE_DOS861,
	CODE_PAGE_DOS863,
	CODE_PAGE_DOS864,
	CODE_PAGE_DOS865,
	CODE_PAGE_DOS869,
	CODE_PAGE_DOS932,
	CODE_PAGE_MACINTOSH,
	CODE_PAGE_BIG5,
	CODE_PAGE_KSC5601,
	CODE_PAGE_JOHAB,
	CODE_PAGE_DOS866,
	CODE_PAGE_ANSI_1250,
	CODE_PAGE_ANSI_1251,
	CODE_PAGE_ANSI_1252,
	CODE_PAGE_GB2312,
	CODE_PAGE_ANSI_1253,
	CODE_PAGE_ANSI_1254,
	CODE_PAGE_ANSI_1255,
	CODE_PAGE_ANSI_1256,
	CODE_PAGE_ANSI_1257,
	CODE_PAGE_ANSI_874,
	CODE_PAGE_ANSI_932,
	CODE_PAGE_ANSI_936,
	CODE_PAGE_ANSI_949,
	CODE_PAGE_ANSI_950,
	CODE_PAGE_ANSI_1361,
	CODE_PAGE_ANSI_1200,
	CODE_PAGE_ANSI_1258,
	CODE_PAGE_CNT
} code_page_id;

enum NcFileSelectFlags {
	kDLFNoType    = 0x0,
	kDLFPut       = 0x1,
	kDLFDwg       = 0x2,
	kDLFPathOnly     = 0x4,
	kDLFNoWarn    = 0x8,
	kDLFNoExistOk = 0x10,
	kDLFAnyExt    = 0x20,
	kDLFRqBox     = 0x40,
	kDLFSaveas    = 0x80,
	kDLFNoLib     = 0x0100,
	kDLFNoXfer    = 0x0200,
	kDLFNoURLs    = 0x0400,
	kDLFDwgDef    = 0x0800,
	kDLFOpenDef   = 0x1000,
	kDLFDvc      = 0x2000,
	kDLFDwt       = 0x4000,
	kDLFOpts      = 0x8000,
	kDLFNoPopup   = 0x10000,
	kDLFFrcWarn   = 0x20000,
	kDLFMulti     = 0x40000,
	kDLFCLI       = 0x80000,
	kDLFRecover   = 0x100000,
	kDLFForceDir  = 0x200000,
	kDLFNoFTP     = 0x400000,
	kDLFNoAnav    = 0x800000,
	kDLFFolders   = 0x1000000,
	kDLFNoExtensions = 0x2000000,
	kDLFNoTemplate = 0x4000000,
	kDLFExport     = 0x8000000
};

namespace NcadInet
{
	const int StatusBase = 20000;
	enum Status
	{
		statusOk    = StatusBase,
		statusInCache,
		statusFileNotFound,
		statusBadPath,
		statusTooManyOpenFiles,
		statusFileAccessDenied,
		statusInvalidFileHandle,
		statusDirectoryFull,
		statusHardwareError,
		statusSharingViolation,
		statusDiskFull,
		statusFileGenericError,

		statusValidURL,
		statusNotAnURL,
		statusNoWinInet,
		statusOldWinInet,
		statusNoNcadInet,
		statusNotImplemented,
		statusProtocolNotSupported,

		statusCreateInternetSessionFailed,
		statusInternetSessionConnectFailed,
		statusInternetSessionOpenFailed,

		statusInvalidAccessType,
		statusFileOpenFailed,
		statusHttpOpenRequestFailed,
		statusUserCancelledTransfer,

		statusHttpBadRequest,
		statusHttpAccessDenied,
		statusHttpPaymentRequired,
		statusHttpRequestForbidden,
		statusHttpObjectNotFound,
		statusHttpBadMethod,
		statusHttpNoAcceptableResponse,
		statusHttpProxyAuthorizationRequired,
		statusHttpTimedOut,
		statusHttpConflict,
		statusHttpResourceGone,
		statusHttpLengthRequired,
		statusHttpPreconditionFailure,
		statusHttpRequestTooLarge,
		statusHttpUriTooLong,
		statusHttpUnsupportedMedia,

		statusHttpServerError,
		statusHttpNotSupported,
		statusHttpBadGateway,
		statusHttpServiceUnavailable,
		statusHttpGatewayTimeout,
		statusHttpVersionNotSupported,

		statusInternetError,

		statusGenericException,

		statusUnknownError
	};
}

//////////////////////////////////////////////////////////////////////////
// NcDbLayoutManagerReactor moved to applicationHost.cpp in NrxHostGate
class NRXDBGATE_EXPORT NcDbLayoutManagerReactor : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbLayoutManagerReactor);

	NcDbLayoutManagerReactor();
	NcDbLayoutManagerReactor(OdRxObject* _object);
	virtual ~NcDbLayoutManagerReactor();

public:
	virtual void layoutCreated(const NCHAR* newLayoutName, const NcDbObjectId& layoutId);
	virtual void layoutToBeRemoved(const NCHAR* layoutName, const NcDbObjectId& layoutId);
	virtual void layoutRemoved(const NCHAR* layoutName, const NcDbObjectId& layoutId);
	virtual void abortLayoutRemoved(const NCHAR* layoutName, const NcDbObjectId& layoutId);
	virtual void layoutToBeCopied(const NCHAR* layoutName, const NcDbObjectId& oldLayoutId);
	virtual void layoutCopied(const NCHAR* oldLayoutName, const NcDbObjectId& oldLayoutId, const NCHAR* newLayoutname, const NcDbObjectId& newLayoutId);
	virtual void abortLayoutCopied(const NCHAR* layoutName, const NcDbObjectId& layoutId);
	virtual void layoutToBeRenamed(const NCHAR* oldName, const NCHAR* newName, const NcDbObjectId& layoutId);
	virtual void layoutRenamed(const NCHAR* oldName, const NCHAR* newName, const NcDbObjectId& layoutId);
	virtual void abortLayoutRename(const NCHAR* oldName, const NCHAR* newName, const NcDbObjectId& layoutId);
	virtual void layoutSwitched(const NCHAR* newLayoutname, const NcDbObjectId& newLayoutId);
	virtual void plotStyleTableChanged(const NCHAR* newTableName, const NcDbObjectId& layoutId);
	virtual void layoutsReordered();
};
///////////////////////////////////////////////////////////////////////////////////////////
// NcDbLayoutManager
class OdDbLayoutManager;
class NRXDBGATE_EXPORT NcDbLayoutManager : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbLayoutManager);

	NcDbLayoutManager(OdRxObject* _object);

public:
	virtual Nano::ErrorStatus setCurrentLayout(const NCHAR* newname,
	                                           NcDbDatabase* database = NULL);
	virtual Nano::ErrorStatus setCurrentLayoutId(NcDbObjectId layout);
	virtual const NCHAR* findActiveLayout(bool allow_model,
	                                      const NcDbDatabase* database = NULL);

	virtual NcDbObjectId getActiveLayoutBTRId(const NcDbDatabase* pDb = NULL);

	virtual NcDbLayout* findLayoutNamed(const NCHAR* name, bool leave_record_open = false,
	                                    const NcDbDatabase* database = NULL);
	virtual Nano::ErrorStatus copyLayout(const NCHAR* copyname, const NCHAR* newname,
	                                     NcDbDatabase* database = NULL);

	virtual Nano::ErrorStatus deleteLayout(const NCHAR* delname,
	                                       NcDbDatabase* database = NULL);

	virtual Nano::ErrorStatus createLayout(const NCHAR* newname, NcDbObjectId& layout, NcDbObjectId& record,
	                                       NcDbDatabase* database = NULL);
	virtual Nano::ErrorStatus renameLayout(const NCHAR* oldname, const NCHAR* newname,
	                                       NcDbDatabase* database = NULL);
	virtual Nano::ErrorStatus cloneLayout(NcDbLayout* layout, const NCHAR* newname, int new_tab_order = 0,
	                                      NcDbDatabase* database = NULL);

	virtual NcDbObjectId getNonRectVPIdFromClipId(NcDbObjectId id);

	virtual bool isVpnumClipped(int index,
	                            const NcDbDatabase* database = NULL);

	virtual int countLayouts(NcDbDatabase* database = NULL);

	virtual void addReactor(NcDbLayoutManagerReactor* reactor);

	virtual void removeReactor(NcDbLayoutManagerReactor* reactor);

public:
	OdDbLayoutManager* native() const;

protected:
	OdDbDatabase* database() const;
};

#ifndef OD_DBPLOTSETVAL_H
typedef NcDbPlotSettings::PlotPaperUnits PlotPaperUnits;
typedef NcDbPlotSettings::PlotRotation   PlotRotation;
typedef NcDbPlotSettings::PlotType       PlotType;
typedef NcDbPlotSettings::StdScaleType   StdScaleType;
#endif

//////////////////////////////////////////////////////////////////////////
// NcDbPlotSettingsValidator
class OdDbPlotSettingsValidator;
class NRXDBGATE_EXPORT NcDbPlotSettingsValidator
{
public:
	NcDbPlotSettingsValidator(OdDbPlotSettingsValidator* plotSettings);
	virtual ~NcDbPlotSettingsValidator();

	typedef NcDbPlotSettings::PlotRotation PlotRotation;

	virtual Nano::ErrorStatus setPlotCfgName(NcDbPlotSettings* pPlotSet, const NCHAR* plotDeviceName,
	                                         const NCHAR * mediaName = NULL);
	virtual Nano::ErrorStatus setCanonicalMediaName(NcDbPlotSettings* pPlotSet, const NCHAR * mediaName);
	virtual Nano::ErrorStatus setPlotOrigin(NcDbPlotSettings *pPlotSet, const double xCoordinate,
	                                        const double yCoordinate);
	virtual Nano::ErrorStatus setPlotPaperUnits(NcDbPlotSettings* pPlotSet, const NcDbPlotSettings::PlotPaperUnits units);
	virtual Nano::ErrorStatus setPlotRotation(NcDbPlotSettings* pPlotSet, const PlotRotation rotationType);
	virtual Nano::ErrorStatus setPlotCentered(NcDbPlotSettings* pPlotSet, NRX::Boolean isCentered);
	virtual Nano::ErrorStatus setPlotType(NcDbPlotSettings* pPlotSet, const NcDbPlotSettings::PlotType plotAreaType);
	virtual Nano::ErrorStatus setPlotWindowArea(NcDbPlotSettings* pPlotSet, const double xmin, const double ymin,
	                                            const double xmax, const double ymax);
	virtual Nano::ErrorStatus setPlotViewName(NcDbPlotSettings* pPlotSet, const NCHAR * viewName);
	virtual Nano::ErrorStatus setUseStandardScale(NcDbPlotSettings* pPlotSet, NRX::Boolean useStandard);
	virtual Nano::ErrorStatus setCustomPrintScale(NcDbPlotSettings* pPlotSet, const double numerator,
	                                              const double denominator);
	virtual Nano::ErrorStatus setCurrentStyleSheet(NcDbPlotSettings* pPlotSet, const NCHAR * styleSheetName);
	virtual Nano::ErrorStatus setStdScaleType(NcDbPlotSettings* pPlotSet, const NcDbPlotSettings::StdScaleType scaleType);
	virtual Nano::ErrorStatus setStdScale(NcDbPlotSettings* pPlotSet, const double standardScale);
	virtual Nano::ErrorStatus plotDeviceList(NcArray<const NCHAR *> & deviceList);

	virtual Nano::ErrorStatus canonicalMediaNameList(NcDbPlotSettings* pPlotSet, NcArray<const NCHAR *> & mediaList);
	virtual Nano::ErrorStatus getLocaleMediaName(NcDbPlotSettings *pPlotSet, const NCHAR* canonicalName,
	                                             const NCHAR *& localeName);
	virtual Nano::ErrorStatus getLocaleMediaName(NcDbPlotSettings *pPlotSet, int index, const NCHAR *& localeName);
	virtual Nano::ErrorStatus setClosestMediaName(NcDbPlotSettings* pPlotSet, const double paperWidth,
	                                              const double paperHeight, const NcDbPlotSettings::PlotPaperUnits units,
	                                              NRX::Boolean matchPrintableArea);
	virtual Nano::ErrorStatus plotStyleSheetList(NcArray<const NCHAR *> & styleList);

	virtual void refreshLists(NcDbPlotSettings* pPlotSet);
	virtual void setZoomToPaperOnUpdate(NcDbPlotSettings* pPlotSet, NRX::Boolean doZoom);
	virtual Nano::ErrorStatus setDefaultPlotConfig(NcDbPlotSettings* pPlotSet);

	friend NcDbHostApplicationServices;

protected:
	void cleanNames();

	OdDbPlotSettingsValidator* m_pPlotSettings;
	CMapStringToPtr*           m_pCanonicalToLocalNameMap;
	CMapWordToPtr*             m_pMediaIndexToLocalNameMap;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcDbHostApplicationProgressMeter
class OdDbHostAppProgressMeter;
class NRXDBGATE_EXPORT NcDbHostApplicationProgressMeter
{
public:
	NcDbHostApplicationProgressMeter(OdDbHostAppProgressMeter* _object);
	virtual ~NcDbHostApplicationProgressMeter() {}

public:
	virtual void start(const NCHAR* display_string = NULL);
	virtual void stop();

	virtual void meterProgress();

	virtual void setLimit(int max);

public:
	OdDbHostAppProgressMeter* native() const;

protected:
	OdDbHostAppProgressMeter* m_pNative;
};

#ifndef _ODDB_BASEHOSTAPPSERVICES_INCLUDED_
enum NcSDIValues
{
	kMDIEnabled             = 0,
	kSDIUserEnforced        = 1,
	kSDIAppEnforced         = 2,
	kSDIUserAndAppEnforced  = 3
};

enum ProdIdCode
{
	kProd_ACAD = 1, // Plain
	kProd_LT   = 2, // Lite
	kProd_OEM  = 3, // OEM
	kProd_OdDb = 4  // ..
};
#else
enum class NcSDIValues
{
	kMDIEnabled             = 0,
	kSDIUserEnforced        = 1,
	kSDIAppEnforced         = 2,
	kSDIUserAndAppEnforced  = 3
};
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// NcDbHostApplicationServices
class OdDbHostAppServices;
class NRXDBGATE_EXPORT NcDbHostApplicationServices : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbHostApplicationServices);

	NcDbHostApplicationServices(OdRxObject* _object);
	NcDbHostApplicationServices( int createGlobals = 1 );
	virtual ~NcDbHostApplicationServices();

public:
	enum FindFileHint
	{
		kDefault = 0,
		kFontFile,
		kCompiledShapeFile,
		kTrueTypeFontFile,
		kEmbeddedImageFile,
		kXRefDrawing,
		kPatternFile,
		kARXApplication,
		kFontMapFile,
		kUnderlayFile
	};

	enum RemapFileContext
	{
		kDrawingOpen,
		kXrefResolution,
		kRasterResolution,
		kAfterXrefResolution
	};

	virtual Nano::ErrorStatus findFile(NCHAR* path, int bufsz, const NCHAR* file, NcDbDatabase* database = NULL,
	                                   NcDbHostApplicationServices::FindFileHint hint = kDefault);

	virtual Nano::ErrorStatus getRoamableRootFolder(const NCHAR*& folder);
	virtual Nano::ErrorStatus getLocalRootFolder(const NCHAR*& folder);

	virtual Nano::ErrorStatus selectFile(short* userCancel, NCHAR*& chosenPath, void* h, const int nFlags,
	                                     const NCHAR* prompt, const NCHAR* dir, const NCHAR* name, const NCHAR* type,
	                                     int* pnChoice, bool* pbReadOnly, const NCHAR* pszWSTags, void* pReserved);
	virtual Nano::ErrorStatus registerSelectFileCallback(const NCHAR* appName, SELECTFILEPROC proc,
	                                                     bool unRegister = false, bool asPrimary = false);

	virtual const NCHAR* primaryClientForSelectFileCallback();

	virtual Nano::ErrorStatus getRegisteredSelectFileClients(NcArray< const NCHAR* >& clients);

	virtual Nano::ErrorStatus mapFile(/*out*/ NCHAR*& newName, const NCHAR* filename, int context, void* pReserved);
	virtual Nano::ErrorStatus registerMapFileCallback(const NCHAR* appName, REMAPPROC proc, bool unRegister = false,
	                                                  bool asPrimary = false);
	virtual const NCHAR* primaryClientForMapFileCallback();
	virtual bool setMapFlag(bool setIt);
	virtual Nano::ErrorStatus getRegisteredFileMapClients(NcArray< const NCHAR* >& clients);
	virtual Nano::ErrorStatus registerMapFileNotification(const NCHAR* appName, MAPFILENOTIFYPROC,
	                                                      bool unRegister = false);

	virtual void fatalError(const NCHAR* format, ...);

	virtual void reportUnhandledNrxException(const _EXCEPTION_POINTERS* pExcPtrs, const NCHAR* name);

	virtual NRX::Boolean userBreak(bool updCtrlsWhenEnteringIdle = true) const;

	virtual void displayChar(NCHAR c) const;
	virtual void displayString(const NCHAR* string, int count) const;

	virtual NRX::Boolean readyToDisplayMessages();

	virtual void enableMessageDisplay(NRX::Boolean);

	virtual NRX::Boolean doFullCRCCheck();

	virtual unsigned int getTempPath(NRX::UInt32 lBufferSize, NCHAR* pcBuffer);

	virtual const NCHAR* getEnv(const NCHAR* var);
	virtual int          setEnv(const NCHAR* var, const NCHAR* val); // added by Lion007

	virtual NcDbHostApplicationProgressMeter* newProgressMeter();
	void setWorkingProgressMeter(NcDbHostApplicationProgressMeter* pNewMeter);

	virtual NcDbAbstractClipBoundaryDefinition* newClipBoundaryRectangular();
	virtual NcDbAbstractClipBoundaryDefinition* newClipBoundaryPolygonal();
	virtual ClipBoundaryArray* newClipBoundaryArray();

	NcDbDatabase* workingDatabase() const;
	void setWorkingDatabase(NcDbDatabase* database);

	virtual NcDbUndoController* defaultUndoController();
	void setDefaultUndoController(NcDbUndoController* pUndoCtrl);

	virtual NcDbTransactionManager* workingTransactionManager();
	void setWorkingTransactionManager(NcDbTransactionManager* manager);

	virtual NcDbGlobals *createWorkingGlobals();
	NcDbGlobals *workingGlobals() const;
	void setWorkingGlobals(NcDbGlobals *pGlobals);

	NcDbAppSystemVariables *workingAppSysvars() const;
	void setWorkingAppSysvars(NcDbAppSystemVariables* pSysvars);

	virtual const NCHAR* program();
	virtual const NCHAR* product();
	virtual const NCHAR* companyName();
	virtual const ProdIdCode prodcode();

	virtual const NCHAR* releaseMajorMinorString();
	virtual int releaseMajorVersion();
	virtual int releaseMinorVersion();
	virtual const NCHAR* versionString();
	virtual const NCHAR* getRegistryProductRootKey();
	virtual LCID getRegistryProductLCID();
	virtual bool supportsMultiRedo() const;

	enum ModelerFlavor
	{
		kModelerFull        = 0,
		kModelerRegionsOnly = 1,
		kModelerObjectsOnly = 2
	};

	virtual ModelerFlavor getModelerFlavor() const;

	code_page_id getSystemCodePage() const;

	virtual NcadInternalServices* ncadInternalServices();

	void* ncadInternalGetvar(const NCHAR* name);

	virtual NRX::Boolean isURL(const NCHAR* url) const;

	virtual NRX::Boolean isRemoteFile(const NCHAR* local, NCHAR* url) const;

	virtual Nano::ErrorStatus getRemoteFile(const NCHAR* url, NCHAR* local,
	                                        NRX::Boolean ignore_cache = NRX::kFalse) const;
	virtual Nano::ErrorStatus putRemoteFile(const NCHAR* url, const NCHAR* local) const;

	virtual NRX::Boolean launchBrowserDialog(NCHAR* url, const NCHAR* title, const NCHAR* open_button_caption,
	                                         const NCHAR* start, const NCHAR* root_key = 0,
	                                         NRX::Boolean enable_open_button = NRX::kFalse) const;

	virtual void drawOleOwnerDrawItem(COleClientItem* pItem, NRX::LongPtr hdc,
	                                  NRX::Int32 left, NRX::Int32 top, NRX::Int32 right, NRX::Int32 bottom);

	virtual Nano::ErrorStatus getNewOleClientItem(COleClientItem*& pItem);

	virtual Nano::ErrorStatus serializeOleItem(COleClientItem* pItem, CArchive*);

	virtual NRX::Boolean _entToWorldTransform(double normal[3], flagmat *tran);

	virtual void terminateScript();

	virtual NRX::Boolean getSubstituteFont(NCHAR** file_name, NCHAR* prompt, int type, int fontAlt);
	virtual void alert(const NCHAR* string) const;

	virtual void auditPrintReport(NcDbAuditInfo* info, const NCHAR* line, int both) const;

	virtual NCHAR* getAlternateFontName() const;

	virtual NCHAR* getFontMapFileName() const;

	virtual bool cacheSymbolIndices() const;

	virtual NcDbPlotSettingsValidator* plotSettingsValidator() const;
	virtual NcDbLayoutManager* layoutManager() const;
	virtual bool loadApp(const NCHAR* application, NcadApp::LoadReasons why, bool print_it, bool command);
	virtual void getDefaultPlotCfgInfo(NCHAR* device_name, NCHAR* style_name);

	virtual Nano::ErrorStatus signingComplete(Nano::ErrorStatus es, const NCHAR* msg, bool* result);

	enum PasswordOptions
	{
		kPasswordOptionDefault             = 0,
		kPasswordOptionUpperCase           = 1,
		kPasswordOptionIsExternalReference = 2
	};

	virtual bool getPassword(const NCHAR* dwg, PasswordOptions options, wchar_t* password, const size_t bufsz);

	virtual void usedPasswordFromCacheMsg(const NCHAR* dwg);
	virtual void missingCryptoProviderMsg();

	virtual const NCHAR* getColorBookLocation() const;

	NcPwdCache* getPasswordCache() const;
	void ncadInternalSetvar (const NCHAR *name, void * var);
	virtual short getKeyState(int nVirtKey) const { return 0; }

	Nano::ErrorStatus mapInetStatusToNcadStatus(const NcadInet::Status status) const;
	virtual void reportUnhandledArxException(const _EXCEPTION_POINTERS *pExcPtrs,
	                                         const NCHAR *pAppName);
	void setSystemCodePage(code_page_id);

	virtual const NCHAR *getMachineRegistryProductRootKey();
	virtual const NCHAR *getUserRegistryProductRootKey();

public:
	OdDbHostAppServices* native() const;

protected:
	NcDbHostApplicationProgressMeter*  m_pMeter;
	NcDbTransactionManager*            m_pTransactionManagerOverride;
	NcDbLayoutManager*                 m_pLayoutManager;
	mutable NcDbPlotSettingsValidator* m_pPlotSettingsValidator;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcRxDynamicLinker
class OdRxDynamicLinker;
class NRXDBGATE_EXPORT NcRxDynamicLinker : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcRxDynamicLinker);

	NcRxDynamicLinker(OdRxDynamicLinker* _object);

public:
	virtual void* getSymbolAddress(const NCHAR* serviceName, const char* symbol) const;

#ifdef _UNICODE
	// Overload it for convenience of callers that want to
	// put _T() around all literals.
	virtual void* getSymbolAddress(const NCHAR* serviceName, const NCHAR* symbol) const;
#endif

	virtual bool initListedModules(const NCHAR* fileName);

	virtual bool loadModule(const NCHAR* fileName, bool printit, bool command = false);
	virtual bool loadApp(const NCHAR* appName, NcadApp::LoadReasons al, bool printit, bool command = false);

	virtual NcRxObject* registerService(const NCHAR* serviceName, NcRxService* serviceObj);

	virtual bool unloadModule(const NCHAR* fileName, bool command = false);
	virtual bool unloadApp(const NCHAR* appName, bool command = false);

	virtual void addReactor(NcRxDLinkerReactor *reactor);

	virtual void removeReactor(NcRxDLinkerReactor *reactor);

	virtual bool isApplicationLocked(const NCHAR* module) const;
	virtual bool lockApplication(void* application) const;
	virtual bool unlockApplication(void* application) const;

	virtual bool isAppMDIAware(const NCHAR* modulename) const;
	virtual bool registerAppMDIAware(void* id) const;
	virtual bool registerAppNotMDIAware(void* id) const;

	virtual bool isAppBusy(const NCHAR* modulename) const;
	virtual void setAppBusy(const NCHAR* modulename, bool bBusyFlag) const;

	virtual const NCHAR* ProductKey() const;
	virtual NRX::UInt32 ProductLcid() const;

public:
	OdRxDynamicLinker* native() const;
};

NRXDBGATE_EXPORT NcRxDynamicLinker* GetDynamicLinker();

NRXDBGATE_EXPORT NcRxDictionary* ncrxSysRegistry();

///////////////////////////////////////////////////////////////////////////////////////////
// NcRxDictionary
class OdRxDictionary;
class NRXDBGATE_EXPORT NcRxDictionary : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcRxDictionary);

	NcRxDictionary(OdRxObject* _object);
	virtual ~NcRxDictionary();

public:
	typedef OdRxDictionary  native_class;

public:
	virtual NcRxObject* at(const NCHAR* key) const;
	virtual NcRxObject* at(NRX::UInt32 id) const;

	NcRxObject* atPut(const NCHAR* key, NcRxObject* object);
	virtual NcRxObject* atPut(const NCHAR* key, NcRxObject* object, NRX::UInt32& id);
	virtual NcRxObject* atPut(NRX::UInt32 id, NcRxObject* object);

	virtual NRX::Boolean resetKey(const NCHAR* oldKey, const NCHAR* newKey);
	virtual NRX::Boolean resetKey(NRX::UInt32 id, const NCHAR* newKey);

	virtual NRX::Boolean atKeyAndIdPut(const NCHAR* newKey, NRX::UInt32 id, NcRxObject* pObject);

	virtual NcRxObject* remove(const NCHAR* key);
	virtual NcRxObject* remove(NRX::UInt32 id);

	virtual NRX::Boolean has(const NCHAR* entryName) const;
	virtual NRX::Boolean has(NRX::UInt32 id) const;

	virtual NRX::UInt32 idAt(const NCHAR* key) const;

	virtual const NCHAR* keyAt(NRX::UInt32 id) const;

	virtual NRX::UInt32 numEntries() const;

	virtual NcRxDictionaryIterator* newIterator(NcRx::DictIterType type = NcRx::kDictSorted);

	virtual NRX::Boolean deletesObjects() const;
	virtual NRX::Boolean isCaseSensitive() const;
	virtual NRX::Boolean isSorted() const;

public:
	OdRxDictionary* native() const;
	mutable McsMap< NRX::UInt32, NRX::UInt32, NcRxObject*, NcRxObject* > m_AttachedByIdObjects;
	mutable McsMap< OdString, LPCTSTR, NcRxObject*, NcRxObject* >                  m_AttachedByKeyObjects;
};

NRXDBGATE_EXPORT NcRxDictionary* GetClassDictionary();
NRXDBGATE_EXPORT NcRxDictionary* GetServiceDictionary();
NRXDBGATE_EXPORT NcDbHostApplicationServices* ncdbHostApplicationServices();
NRXDBGATE_EXPORT NcDbTransactionManager* ncdbTransactionManagerPtr();

///////////////////////////////////////////////////////////////////////////////////////////
// NcRxIterator
class OdRxIterator;
class NRXDBGATE_EXPORT NcRxIterator : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcRxIterator);

	NcRxIterator(OdRxObject* _object);

public:
	typedef OdRxIterator  native_class;

public:
	virtual NRX::Boolean done() const;
	virtual NRX::Boolean next();
	virtual NcRxObject* object() const;

public:
	OdRxIterator* native() const;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcRxDictionaryIterator
class OdRxDictionaryIterator;
class NRXDBGATE_EXPORT NcRxDictionaryIterator : public NcRxIterator
{
public:
	NCRX_DECLARE_MEMBERS(NcRxDictionaryIterator);

	NcRxDictionaryIterator(OdRxObject* _object);

public:
	typedef OdRxDictionaryIterator  native_class;

public:
	virtual const NCHAR* key() const;
	virtual NRX::UInt32 id() const;

public:
	OdRxDictionaryIterator* native() const;
};

///////////////////////////////////////////////////////////////////////////////////////////
 //NcRxService
class OdRxService;
class NRXDBGATE_EXPORT NcRxService : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcRxService);

	NcRxService();
	NcRxService(OdRxObject* _object);

public:
	typedef OdRxService  native_class;

public:
	NcRxObject* getSysInfo() const;
	void setSysInfo(NcRxObject* sysInfoObj);

	void addDependency() {}
	void removeDependency() {}

	NRX::Boolean unloadable() const;

	DepFuncPtr dependencyFunctionPtr();
	void setDependencyFunctionPtr(DepFuncPtr);

public:
	OdRxService* native() const;
};

// Profile names list storage
typedef NcArray< NCHAR* >  NcApProfileNameArray;

//////////////////////////////////////////////////////////////////////////
// NcApLayoutManager
class NRXDBGATE_EXPORT NcApLayoutManager : public NcDbLayoutManager
{
public:

	NcApLayoutManager(OdRxObject* _object) : NcDbLayoutManager(_object) {}

	virtual int pageSetup(NcDbObjectId layoutBTRId = NcDbObjectId::kNull,
	                      void* pParent = NULL, NRX::Boolean isPageSetupDlg = TRUE);
	virtual void updateCurrentPaper(NRX::Boolean zoomToPaper = FALSE);
	virtual void updateLayoutTabs();
	virtual const NCHAR *findActiveTab();
	virtual NRX::Boolean showTabs();
	virtual void setShowTabs(NRX::Boolean showTabs);
	virtual NRX::Boolean showPageSetup();
	virtual void setShowPageSetup(NRX::Boolean showPageSetupDlg);
	virtual NRX::Boolean createViewports();
	virtual void setCreateViewports(NRX::Boolean createViewports);
	virtual NRX::Boolean showPaperBackground();
	virtual void setShowPaperBackground(NRX::Boolean showPaperBackground);
	virtual NRX::Boolean showPaperMargins();
	virtual void setShowPaperMargins(NRX::Boolean showPaperMargins);
	virtual NRX::Boolean showPrintBorder();
	virtual void setShowPrintBorder(NRX::Boolean showPrintBorder);
	virtual NCHAR* getNextNewLayoutName(NcDbDatabase* useDb = NULL);
	virtual void setDefaultPlotConfig(NcDbObjectId layoutBTRId);
	virtual Nano::ErrorStatus getClipBoundaryElaboration(NcDbObjectId clipId,
	                                                     NcGePoint2dArray *&clipBoundary);
	virtual Nano::ErrorStatus  pointInViewports(const NcGePoint3d &pickPt,
	                                            NcDbObjectIdArray &viewports);
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcRxIterator moved to applicationHost.cpp in NrxHostGate

///////////////////////////////////////////////////////////////////////////////////////////
// NcApProfileStorage moved to applicationHost.cpp in NrxHostGate

///////////////////////////////////////////////////////////////////////////////////////////
// NcApProfileManager moved to applicationHost.cpp in NrxHostGate

///////////////////////////////////////////////////////////////////////////////////////////
// NcApLongTransactionReactor
class OdApLongTransactionReactor;
class NRXDBGATE_EXPORT NcApLongTransactionReactor : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcApLongTransactionReactor);

	typedef NcApLongTransactionReactor  wrapper_class;
	typedef OdApLongTransactionReactor  native_class;

public:
	virtual void beginCheckOut(NcDbLongTransaction& transaction, NcDbObjectIdArray& originList);
	virtual void endCheckOut(NcDbLongTransaction& transaction);
	virtual void beginCheckIn(NcDbLongTransaction& transaction);
	virtual void endCheckIn(NcDbLongTransaction& transaction);
	virtual void abortLongTransaction(NcDbLongTransaction& transaction);

protected:
	Nano::ErrorStatus veto();

public:
	OdApLongTransactionReactor* native() const;

private:
	NRX::UInt8 mVeto;
	friend class OdApLongTransactionManagerImpl;
};

///////////////////////////////////////////////////////////////////////////////////////////
// NcApLongTransactionManager
class OdApLongTransactionManager;
class NRXDBGATE_EXPORT NcApLongTransactionManager : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcApLongTransactionManager);

	typedef NcApLongTransactionManager  wrapper_class;
	typedef OdApLongTransactionManager  native_class;

public:
	NcApLongTransactionManager(OdRxObject* _object);

	virtual Nano::ErrorStatus checkOut(NcDbObjectId& id, NcDbObjectIdArray& objects, NcDbObjectId toBlock,
	                                   NcDbIdMapping& errorMap, NcDbObjectId lockBlkRef = NcDbObjectId::kNull);
	virtual Nano::ErrorStatus checkIn(NcDbObjectId id, NcDbIdMapping& errorMap, bool keepObjs = false);

	virtual Nano::ErrorStatus abortLongTransaction(NcDbObjectId id, bool keepObjs = false);
	virtual NcDbObjectId currentLongTransactionFor(const NcApDocument* document) const;
	virtual void addReactor(NcApLongTransactionReactor* reactor);
	virtual void removeReactor(NcApLongTransactionReactor* reactor);
	virtual Nano::ErrorStatus addClassFilter(NcRxClass* rxclass);
	virtual bool isFiltered(NcRxClass* rxclass) const;

public:
	OdApLongTransactionManager* native() const;
};

NRXDBGATE_EXPORT NcApLongTransactionManager* ncapLongTransactionManagerPtr();
#define ncapLongTransactionManager  ncapLongTransactionManagerPtr()

///////////////////////////////////////////////////////////////////////////////////////////
// NrxAppInfo moved to applicationHost.cpp in NrxHostGate

///////////////////////////////////////////////////////////////////////////////////////////////////
// Commands moved to applicationHost.cpp in NrxHostGate

// NcEdCommandStruc moved to applicationHost.cpp in NrxHostGate

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdCommand moved to applicationHost.cpp in NrxHostGate

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdCommandIterator moved to applicationHost.cpp in NrxHostGate

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdCommandStack moved to applicationHost.cpp in NrxHostGate

/////////////////////////////////////////////////////////////////////////////////////////////////////
//NcDbDoubleClickEdit
class NRXDBGATE_EXPORT NcDbDoubleClickEdit : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbDoubleClickEdit);

	virtual void startEdit(NcDbEntity* pEnt, NcGePoint3d pt) = 0;
	virtual void finishEdit(void) = 0;
};
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
// NcRxEventReactor
class NRXDBGATE_EXPORT NcRxEventReactor : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcRxEventReactor);

	NcRxEventReactor();

	NcRxEventReactor(OdRxObject* _object);

public:
	virtual ~NcRxEventReactor();

public:
	// DWG/Save Events.
	virtual void dwgFileOpened(NcDbDatabase* database, NCHAR* name);
	virtual void initialDwgFileOpenComplete(NcDbDatabase* database);
	virtual void databaseConstructed(NcDbDatabase* database);
	virtual void databaseToBeDestroyed(NcDbDatabase* database);

	virtual void beginSave(NcDbDatabase* database, const NCHAR* name);
	virtual void saveComplete(NcDbDatabase* database, const NCHAR* name);
	virtual void abortSave(NcDbDatabase* database);

	// DXF In/Out Events.
	virtual void beginDxfIn(NcDbDatabase* database);
	virtual void abortDxfIn(NcDbDatabase* database);
	virtual void dxfInComplete(NcDbDatabase* database);
	//
	virtual void beginDxfOut(NcDbDatabase* database);
	virtual void abortDxfOut(NcDbDatabase* database);
	virtual void dxfOutComplete(NcDbDatabase* database);

	// Insert Events.
	virtual void beginInsert(NcDbDatabase* to, const NCHAR* pBlockName, NcDbDatabase* from);
	virtual void beginInsert(NcDbDatabase* to, const NcGeMatrix3d& xform, NcDbDatabase* from);
	virtual void otherInsert(NcDbDatabase* to, NcDbIdMapping& idMap, NcDbDatabase* from);
	virtual void abortInsert(NcDbDatabase* to);
	virtual void endInsert(NcDbDatabase* to);

	// Wblock Events.
	virtual void wblockNotice(NcDbDatabase* database);
	virtual void beginWblock(NcDbDatabase* to, NcDbDatabase* from, const NcGePoint3d*& inspnt);
	virtual void beginWblock(NcDbDatabase* to, NcDbDatabase* from, NcDbObjectId blockId);
	virtual void beginWblock(NcDbDatabase* to, NcDbDatabase* from);
	virtual void otherWblock(NcDbDatabase* to, NcDbIdMapping& mapping, NcDbDatabase* from);
	virtual void abortWblock(NcDbDatabase* to);
	virtual void endWblock(NcDbDatabase* to);
	virtual void beginWblockObjects(NcDbDatabase* database, NcDbIdMapping& mapping);

	// Deep Clone Events.
	virtual void beginDeepClone(NcDbDatabase* to, NcDbIdMapping& mapping);
	virtual void beginDeepCloneXlation(NcDbIdMapping& mapping, Nano::ErrorStatus*);
	virtual void abortDeepClone(NcDbIdMapping& mapping);
	virtual void endDeepClone(NcDbIdMapping& mapping);

	// Partial Open Events.
	virtual void partialOpenNotice(NcDbDatabase* database);

	// XREF-related Events
	virtual void beginAttach(NcDbDatabase* to, const NCHAR*, NcDbDatabase* from);
	virtual void otherAttach(NcDbDatabase* to, NcDbDatabase* from);
	virtual void abortAttach(NcDbDatabase* from);
	virtual void endAttach(NcDbDatabase* to);
	virtual void redirected(NcDbObjectId newid, NcDbObjectId prvid);
	virtual void comandeered(NcDbDatabase* to, NcDbObjectId id, NcDbDatabase* from);
	virtual void beginRestore(NcDbDatabase* to, const NCHAR*, NcDbDatabase* from);
	virtual void abortRestore(NcDbDatabase* to);
	virtual void endRestore(NcDbDatabase* to);

	virtual void xrefSubCommandStart(NcDbDatabase* pHostDb, NcXrefSubCommand op, const NcArray< NcDbObjectId >& ids,
	                                 const NCHAR* const* btrNames, const NCHAR* const* paths, bool& vetoOp);

	virtual void xrefSubCommandAborted(NcDbDatabase* pHostDb, NcXrefSubCommand op, const NcArray< NcDbObjectId >& ids,
	                                   const NCHAR* const* btrNames, const NCHAR* const* paths);

	virtual void preXrefLockFile(NcDbDatabase* database, NcDbObjectId id);

public:
	HostEditorReactor* native();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcEditorReactor moved to applicationHost.cpp in NrxHostGate

/////////////////////////////////////////////////////////////////////////////////////////////////
// NcEditorReactor2 moved to applicationHost.cpp in NrxHostGate

/////////////////////////////////////////////////////////////////////////////////////////////////////
// NcRxEvent
class NRXDBGATE_EXPORT NcRxEvent : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcRxEvent);

	NcRxEvent();
	NcRxEvent(OdRxObject* _object);  

public:
	virtual void addReactor(NcRxEventReactor* reactor) {};
	virtual void removeReactor(NcRxEventReactor* reactor) {};
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEditor moved to applicationHost.cpp in NrxHostGate

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdUIContext moved to applicationHost.cpp in NrxHostGate

//////////////////////////////////////////////////////////////////////////////////////////////////////////
 //NcDbTransactionManager
class NRXDBGATE_EXPORT NcDbTransactionManager : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbTransactionManager);

	NcDbTransactionManager(OdDbDatabase* _database);

public:
	~NcDbTransactionManager();

public:
	virtual NcTransaction* startTransaction();
	virtual Nano::ErrorStatus endTransaction();
	virtual Nano::ErrorStatus abortTransaction();

	virtual int numActiveTransactions();
	virtual NcTransaction* topTransaction();
	virtual Nano::ErrorStatus addNewlyCreatedDBRObject(NcDbObject* obj, bool add = true);

	virtual Nano::ErrorStatus getAllObjects(NcDbVoidPtrArray& objs);

	virtual void addReactor(NcTransactionReactor* reactor);
	virtual void removeReactor(NcTransactionReactor* reactor);

	virtual Nano::ErrorStatus getObject(NcDbObject*& obj, NcDbObjectId id, NcDb::OpenMode mode,
	                                    bool openErasedObj = false);

	virtual Nano::ErrorStatus markObjectPageable(NcDbObject* pObject);
	virtual Nano::ErrorStatus queueForGraphicsFlush();

	bool    openedInTransaction(NcDbObjectId id);

protected:
	OdDbDatabase*             m_pDatabase;

	NcArray< NcTransaction* > m_ActiveTransactions;
};

#define ncdbTransactionManager  ncdbTransactionManagerPtr()
typedef std::map<NcDbObject*,int> transObjects;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcTransaction
class NRXDBGATE_EXPORT NcTransaction : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcTransaction);

	NcTransaction();
	~NcTransaction();

public:
	virtual Nano::ErrorStatus getObject(NcDbObject*& obj, NcDbObjectId objectId, NcDb::OpenMode mode,
	                                    bool open_erased = false);

	virtual Nano::ErrorStatus markObjectPageable(NcDbObject* pObject);

	virtual Nano::ErrorStatus getAllObjects(NcDbVoidPtrArray& objs);

	bool    openedInTransaction(NcDbObjectId id);
protected:
	transObjects           m_objs;
	friend class NcDbTransactionManager;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
 //NcTransactionReactor
class NRXDBGATE_EXPORT NcTransactionReactor : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcTransactionReactor);

	NcTransactionReactor();

	virtual void transactionAboutToStart(int& numTransactions, NcDbTransactionManager* manager);
	virtual void transactionStarted(int& numTransactions, NcDbTransactionManager* manager);
	virtual void transactionAboutToEnd(int& numTransactions, NcDbTransactionManager* manager);
	virtual void transactionEnded(int& numTransactions, NcDbTransactionManager* manager);
	virtual void transactionAboutToAbort(int& numTransactions, NcDbTransactionManager* manager);
	virtual void transactionAborted(int& numTransactions, NcDbTransactionManager* manager);
	virtual void endCalledOnOutermostTransaction(int& numTransactions, NcDbTransactionManager* manager);
	virtual void objectIdSwapped(const NcDbObject* pTransResObj, const NcDbObject* pOtherObj,
	                             NcDbTransactionManager* manager);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcTransactionManager
class NRXDBGATE_EXPORT NcTransactionManager : public NcDbTransactionManager
{
public:
	NCRX_DECLARE_MEMBERS(NcTransactionManager);

	NcTransactionManager(OdDbDatabase* _database);

public:
	virtual Nano::ErrorStatus enableGraphicsFlush(bool enable);
	virtual void flushGraphics();
};

NRXDBGATE_EXPORT NcTransactionManager* ncTransactionManagerPtr();
#define nctrTransactionManager  ncTransactionManagerPtr()


///////////////////////////////////////////////////////////////////////////////////////////
NRXDBGATE_EXPORT bool ncdbWcs2Ucs(nds_point p, nds_point q, bool vec);
NRXDBGATE_EXPORT bool ncdbWcs2Ecs(nds_point p, nds_point q, nds_point norm, bool vec);
NRXDBGATE_EXPORT bool ncdbUcs2Wcs(nds_point p, nds_point q, bool vec);
NRXDBGATE_EXPORT bool ncdbUcs2Ecs(nds_point p, nds_point q, nds_point norm, bool vec);
NRXDBGATE_EXPORT bool ncdbEcs2Wcs(nds_point p, nds_point q, nds_point norm, bool vec);
NRXDBGATE_EXPORT bool ncdbEcs2Ucs(nds_point p, nds_point q, nds_point norm, bool vec);

// ucsXDir moved to applicationHost.cpp in NrxHostGate
// ucsYDir moved to applicationHost.cpp in NrxHostGate
// ucsNormalVector moved to applicationHost.cpp in NrxHostGate


///////////////////////////////////////////////////////////////////////////////////////////////////

NRXDBGATE_EXPORT Nano::ErrorStatus ncutNewBuffer(void*& output, size_t size);
NRXDBGATE_EXPORT void ncdbFree(void* pointer);

// ncutWcMatch moved to applicationHost.cpp in NrxHostGate
// ncutWcMatchEx moved to applicationHost.cpp in NrxHostGate

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbGetAdsName(nds_name& name, NcDbObjectId id);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbGetObjectId(NcDbObjectId& id, const nds_name name);
//
NRXDBGATE_EXPORT void ncutDelString(TCHAR*& _string);
//
NRXDBGATE_EXPORT void* ncdbAlloc(size_t size);

// ncutNewString moved to applicationHost.cpp in NrxHostGate

// ncutNewString moved to applicationHost.cpp in NrxHostGate
// ncutUpdString moved to applicationHost.cpp in NrxHostGate

NRXDBGATE_EXPORT void* ncdbRealloc(void*, size_t);

// ncrx_abort moved to applicationHost.cpp in NrxHostGate
// ncedGetAppName moved to applicationHost.cpp in NrxHostGate
// ncedUpdate moved to applicationHost.cpp in NrxHostGate

// ndsw_ncadMainWnd moved to applicationHost.cpp in NrxHostGate
// ndsw_ncadDocWnd moved to applicationHost.cpp in NrxHostGate

// ncedCommand moved to applicationHost.cpp in NrxHostGate
// ncedCmd moved to applicationHost.cpp in NrxHostGate
//
// ncedRegFunc moved to applicationHost.cpp in NrxHostGate
// ncedUsrBrk moved to applicationHost.cpp in NrxHostGate
// ncedDefun moved to applicationHost.cpp in NrxHostGate
// ncedSetFunHelp moved to applicationHost.cpp in NrxHostGate
// ncedUndef moved to applicationHost.cpp in NrxHostGate
// ncedGetFunCode moved to applicationHost.cpp in NrxHostGate
//ncedGetArgs moved to applicationHost.cpp in NrxHostGate

// ncedRetList moved to applicationHost.cpp in NrxHostGate
// ncedRetVal moved to applicationHost.cpp in NrxHostGate
// ncedRetPoint moved to applicationHost.cpp in NrxHostGate
// ncedRetStr moved to applicationHost.cpp in NrxHostGate
// ncedRetName moved to applicationHost.cpp in NrxHostGate
// ncedRetInt moved to applicationHost.cpp in NrxHostGate
// ncedRetReal moved to applicationHost.cpp in NrxHostGate
// ncedRetT moved to applicationHost.cpp in NrxHostGate
// ncedRetNil moved to applicationHost.cpp in NrxHostGate
// ncedRetVoid moved to applicationHost.cpp in NrxHostGate
// ncedEntSel moved to applicationHost.cpp in NrxHostGate
// ncedNEntSel moved to applicationHost.cpp in NrxHostGate
// ncedNEntSel moved to applicationHost.cpp in NrxHostGate
// ncedSSGet moved to applicationHost.cpp in NrxHostGate
// ncedSSGetFirst moved to applicationHost.cpp in NrxHostGate
// ncedSSSetFirst moved to applicationHost.cpp in NrxHostGate
// ncedSSFree moved to applicationHost.cpp in NrxHostGate
// ncedSSLength moved to applicationHost.cpp in NrxHostGate
// ncedSSAdd moved to applicationHost.cpp in NrxHostGate
// ncedSSDel moved to applicationHost.cpp in NrxHostGate
// ncedSSMemb moved to applicationHost.cpp in NrxHostGate
// ncedSSName moved to applicationHost.cpp in NrxHostGate
// ncedSSNameX moved to applicationHost.cpp in NrxHostGate
// ncedSSSubentAdd moved to applicationHost.cpp in NrxHostGate
// ncedSSGetKwordCallbackPtr moved to applicationHost.cpp in NrxHostGate
// ncedSSSetKwordCallbackPtr moved to applicationHost.cpp in NrxHostGate
// ncedSSGetOtherCallbackPtr moved to applicationHost.cpp in NrxHostGate
// ncedSSSetOtherCallbackPtr moved to applicationHost.cpp in NrxHostGate
//  ncedTrans moved to applicationHost.cpp in NrxHostGate
//  ncedSetVar moved to applicationHost.cpp in NrxHostGate
//  ncedInitGet moved to applicationHost.cpp in NrxHostGate
//  ncedGetSym moved to applicationHost.cpp in NrxHostGate
//  ncedPutSym moved to applicationHost.cpp in NrxHostGate
//  ncedHelp moved to applicationHost.cpp in NrxHostGate
//  ncedFNSplit moved to applicationHost.cpp in NrxHostGate
//  ncedNrxLoaded moved to applicationHost.cpp in NrxHostGate
//  ncedNrxLoad moved to applicationHost.cpp in NrxHostGate
//  ncedNrxUnload moved to applicationHost.cpp in NrxHostGate
//  ncedInvoke moved to applicationHost.cpp in NrxHostGate
//  ncedGetVar moved to applicationHost.cpp in NrxHostGate
//  ncedFindFile moved to applicationHost.cpp in NrxHostGate
//  ncedGetEnv moved to applicationHost.cpp in NrxHostGate
//  ncedSetEnv moved to applicationHost.cpp in NrxHostGate
//  ncedGetCfg moved to applicationHost.cpp in NrxHostGate
//  ncedSetCfg moved to applicationHost.cpp in NrxHostGate
//  ncedGetString moved to applicationHost.cpp in NrxHostGate
//  ncedGetStringB( moved to applicationHost.cpp in NrxHostGate
//  ncedMenuCmd moved to applicationHost.cpp in NrxHostGate
//  ncedPrompt moved to applicationHost.cpp in NrxHostGate
//  ncedAlert moved to applicationHost.h in NrxHostGate
//  ncedGetAngle moved to applicationHost.cpp in NrxHostGate
//  ncedGetCorner moved to applicationHost.cpp in NrxHostGate
//  ncedGetDist moved to applicationHost.cpp in NrxHostGate
//  ncedGetOrient moved to applicationHost.cpp in NrxHostGate
//  ncedGetPoint moved to applicationHost.cpp in NrxHostGate
//  ncedGetInt moved to applicationHost.cpp in NrxHostGate
//  ncedGetKword moved to applicationHost.cpp in NrxHostGate
//  ncedGetKword moved to applicationHost.cpp in NrxHostGate
//  ncedGetReal moved to applicationHost.cpp in NrxHostGate
//  ncedGetInput moved to applicationHost.cpp in NrxHostGate
//  ncedGetInput moved to applicationHost.cpp in NrxHostGate
//  ncedVports moved to applicationHost.cpp in NrxHostGate
//  ncedTextScr moved to applicationHost.cpp in NrxHostGate
//  ncedGraphScr moved to applicationHost.cpp in NrxHostGate
//  ncedTextPage moved to applicationHost.cpp in NrxHostGate
//  ncedRedraw moved to applicationHost.cpp in NrxHostGate
//  ncedOsnap moved to applicationHost.cpp in NrxHostGate
//  ncedGrRead moved to applicationHost.cpp in NrxHostGate
//  ncedGrText moved to applicationHost.cpp in NrxHostGate
//  ncedGrDraw moved to applicationHost.cpp in NrxHostGate
//  ncedGrVecs moved to applicationHost.cpp in NrxHostGate
//  ncedXformSS moved to applicationHost.cpp in NrxHostGate
//  ncedDragGen moved to applicationHost.cpp in NrxHostGate
//  ncedSetView moved to applicationHost.cpp in NrxHostGate
//  ncedGetFileD moved to applicationHost.cpp in NrxHostGate
//  ncedGetFileNavDialog moved to applicationHost.cpp in NrxHostGate
//  ncedTextBox moved to applicationHost.cpp in NrxHostGate
//  ncedTablet moved to applicationHost.cpp in NrxHostGate
//  ncedGetCName moved to applicationHost.cpp in NrxHostGate
//  ncdbEntDel moved to applicationHost.cpp in NrxHostGate
NRXDBGATE_EXPORT resbuf* ncdbEntGetX(const nds_name ent, const resbuf* args);
NRXDBGATE_EXPORT resbuf* ncdbEntGet(const nds_name ent);
//  ncdbEntLast moved to applicationHost.cpp in NrxHostGate
//  ncdbEntNext moved to applicationHost.cpp in NrxHostGate
//  ncdbEntUpd moved to applicationHost.cpp in NrxHostGate
//  ncdbEntMod moved to applicationHost.cpp in NrxHostGate
//  ncdbEntMake moved to applicationHost.cpp in NrxHostGate
//  ncdbEntMakeX moved to applicationHost.cpp in NrxHostGate
NRXDBGATE_EXPORT int ncdbRegApp(const NCHAR* appname);
// ncdbTblNext moved to applicationHost.cpp in NrxHostGate
// ncdbTblSearch moved to applicationHost.cpp in NrxHostGate
// ncdbNamedObjDict moved to applicationHost.cpp in NrxHostGate
// ncdbDictSearch moved to applicationHost.cpp in NrxHostGate
// ncdbDictNext moved to applicationHost.cpp in NrxHostGate
// ncdbDictRename moved to applicationHost.cpp in NrxHostGate
// ncdbDictRemove moved to applicationHost.cpp in NrxHostGate
// ncdbDictAdd moved to applicationHost.cpp in NrxHostGate
// ncdbTblObjName moved to applicationHost.cpp in NrxHostGate
// ncdbAngToS moved to applicationHost.cpp in NrxHostGate
// ncdbRToS moved to applicationHost.cpp in NrxHostGate
// ncdbAngToF moved to applicationHost.cpp in NrxHostGate
// ncdbDisToF moved to applicationHost.cpp in NrxHostGate
// ncdbInters moved to applicationHost.cpp in NrxHostGate
// ncdbSNValid moved to applicationHost.cpp in NrxHostGate
// ncdbFreeResBufContents moved to applicationHost.cpp in NrxHostGate
// ncdbFail moved to applicationHost.cpp in NrxHostGate
// ncdbHandEnt moved to applicationHost.cpp in NrxHostGate

NRXDBGATE_EXPORT int ncutPrintf(LPCWSTR format, ...);

// ncedGetFullInput moved to applicationHost.cpp in NrxHostGate
// ncedGetFullKword moved to applicationHost.cpp in NrxHostGate
// ncedGetFullString moved to applicationHost.cpp in NrxHostGate
// ncedSSNameXEx moved to applicationHost.cpp in NrxHostGate
//
//
// ncrxLoadModule moved to applicationHost.cpp in NrxHostGate
// ncrxLoadApp moved to applicationHost.cpp in NrxHostGate
// ncrxUnloadModule moved to applicationHost.cpp in NrxHostGate
// ncrxUnloadApp moved to applicationHost.cpp in NrxHostGate
// ncrxLoadedApps moved to applicationHost.cpp in NrxHostGate
// ncrxAppIsLoaded moved to applicationHost.cpp in NrxHostGate
// ncrxProductKey moved to applicationHost.cpp in NrxHostGate
// ncrxObjectDBXRegistryKey moved to applicationHost.cpp in NrxHostGate
// ncrxProductLCID moved to applicationHost.cpp in NrxHostGate
// ncrxRegisterApp moved to applicationHost.cpp in NrxHostGate
// ncrxUnregisterApp moved to applicationHost.cpp in NrxHostGate
// ncrxGetServiceSymbolAddr moved to applicationHost.cpp in NrxHostGate
// ncrxRegisterService moved to applicationHost.cpp in NrxHostGate
// ncrxServiceIsRegistered moved to applicationHost.cpp in NrxHostGate
// ncrxUnlockApplication moved to applicationHost.cpp in NrxHostGate
// ncrxApplicationIsLocked moved to applicationHost.cpp in NrxHostGate
// ncrxLockApplication moved to applicationHost.cpp in NrxHostGate
// ncrxIsAppMDIAware moved to applicationHost.cpp in NrxHostGate
// ncrxRegisterAppMDIAware moved to applicationHost.cpp in NrxHostGate
// ncrxRegisterAppNotMDIAware moved to applicationHost.cpp in NrxHostGate
//
// ncedCmdLookup moved to applicationHost.cpp in NrxHostGate
// ncedCmdLookup2 moved to applicationHost.cpp in NrxHostGate
// ncedCmdUndefine moved to applicationHost.cpp in NrxHostGate
// ncedPopCommandDirectory moved to applicationHost.cpp in NrxHostGate
// ncedGetCommandForDocument moved to applicationHost.cpp in NrxHostGate
// ncedSetOLELock moved to applicationHost.cpp in NrxHostGate
// ncedClearOLELock moved to applicationHost.cpp in NrxHostGate
// ncedPostCommandPrompt moved to applicationHost.cpp in NrxHostGate
//
// ncedAddObjectContextMenu moved to applicationHost.cpp in NrxHostGate
// ncedRemoveObjectContextMenu moved to applicationHost.cpp in NrxHostGate
//
// ncedAddDefaultContextMenu moved to applicationHost.cpp in NrxHostGate
// ncedRemoveDefaultContextMenu moved to applicationHost.cpp in NrxHostGate
//
// ncedSetCMBaseAlias moved to applicationHost.cpp in NrxHostGate
// ncedGetCMBaseAlias moved to applicationHost.cpp in NrxHostGate
//
// ncedMspace moved to applicationHost.cpp in NrxHostGate
// ncedPspace moved to applicationHost.cpp in NrxHostGate
// ncedSetCurrentVPort moved to applicationHost.cpp in NrxHostGate
// ncedSetCurrentVPort moved to applicationHost.cpp in NrxHostGate
//
// ncedIsDragging moved to applicationHost.cpp in NrxHostGate
//
// ncedSetCurrentView moved to applicationHost.cpp in NrxHostGate
//
// ncedRestoreCurrentView moved to applicationHost.cpp in NrxHostGate

NRXDBGATE_EXPORT bool ncdbUcsMatrix(NcGeMatrix3d& mat, NcDbDatabase* database = NULL);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbGetExtnames(bool &value, NcDbDatabase *pDb);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSetExtnames(NcDbDatabase *pDb, bool value);

// ncedSetCurrentUCS moved to applicationHost.cpp in NrxHostGate
// ncedGetCurrentUCS moved to applicationHost.cpp in NrxHostGate
// ncedRestorePreviousUCS moved to applicationHost.cpp in NrxHostGate

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbDoSetupForLayouts(NcDbDatabase* database, unsigned int& context);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbDoSetupForLayouts(NcDbDatabase* pDatabase, NRX::ULongPtr& contextHandle);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbClearSetupForLayouts(unsigned int context);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbClearSetupForLayouts(NRX::ULongPtr contextHandle);

// ncedEditToleranceInteractive moved to applicationHost.cpp in NrxHostGate
//
// ncedEditMTextInteractive moved to applicationHost.cpp in NrxHostGate
//
// ncedGetRGB moved to applicationHost.cpp in NrxHostGate
//
// ncedGetCurrentSelectionSet moved to applicationHost.cpp in NrxHostGate
//
// ncedGetFullSubentPathsForCurrentSelection moved to applicationHost.cpp in NrxHostGate
//
// ncedGetIDispatch moved to applicationHost.cpp in NrxHostGate

// ncedActiveViewportId moved to applicationHost.cpp in NrxHostGate

// ncedViewportIdFromNumber moved to applicationHost.cpp in NrxHostGate

// ncedNumberOfViewports moved to applicationHost.cpp in NrxHostGate

// ncedGetCurViewportObjectId moved to applicationHost.cpp in NrxHostGate

// ncedConvertEntityToHatch moved to applicationHost.cpp in NrxHostGate
//
// ncedHatchPalletteDialog moved to applicationHost.cpp in NrxHostGate
//
// ncedDrawOrderInherit moved to applicationHost.cpp in NrxHostGate
//
// ncedCreateViewportByView moved to applicationHost.cpp in NrxHostGate
//
// ncedCreateEnhancedViewportOnDrop moved to applicationHost.cpp in NrxHostGate
// ncedCreateEnhancedViewportOnDropDWG moved to applicationHost.cpp in NrxHostGate
//
// ncedGetUnitsValueString moved to applicationHost.cpp in NrxHostGate

NRXDBGATE_EXPORT bool ncdbCanonicalToSystemRange(int units, const NcString& in, NcString& out);
NRXDBGATE_EXPORT bool ncdbSystemRangeToCanonical(int units, const NcString& in, NcString& out);

// nccmGetColorFromACIName moved to applicationHost.cpp in NrxHostGate
// nccmGetColorFromRGBName moved to applicationHost.cpp in NrxHostGate
// nccmGetColorFromColorBookName moved to applicationHost.cpp in NrxHostGate

// nccmGetLocalizedColorNames moved to applicationHost.cpp in NrxHostGate

// nds_queueexpr moved to applicationHost.cpp in NrxHostGate
// ncedSyncFileOpen moved to applicationHost.cpp in NrxHostGate
//
// ncedSetColorDialog moved to applicationHost.cpp in NrxHostGate
// ncedSetColorDialogTrueColor moved to applicationHost.cpp in NrxHostGate
// ncedSetColorPrompt moved to applicationHost.cpp in NrxHostGate
//
// ncedIsMenuGroupLoaded moved to applicationHost.cpp in NrxHostGate
// ncedSendModelessOperationStart moved to applicationHost.cpp in NrxHostGate
// ncedSendModelessOperationEnded moved to applicationHost.cpp in NrxHostGate
// ncedUpdateDisplay moved to applicationHost.cpp in NrxHostGate
// ncedUpdateDisplayPause moved to applicationHost.cpp in NrxHostGate
// ncedIsUpdateDisplayPaused moved to applicationHost.cpp in NrxHostGate

// applyCurDwgLayerTableChanges moved to applicationHost.cpp in NrxHostGate

// ncedVportTableRecords2Vports moved to applicationHost.cpp in NrxHostGate
// ncedVports2VportTableRecords moved to applicationHost.cpp in NrxHostGate

NRXDBGATE_EXPORT nds_real ncutAngle(const nds_point pt1, const nds_point pt2);
NRXDBGATE_EXPORT nds_real ncutDistance(const nds_point pt1, const nds_point pt2);
NRXDBGATE_EXPORT void ncutPolar(const nds_point pt, nds_real angle, nds_real dist, nds_point ptres);

//  NCHAR* ncadErrorStatusText moved to applicationHost.cpp in NrxHostGate
//  ncdbDisplayPreviewFromDwg moved to applicationHost.cpp in NrxHostGate

NRXDBGATE_EXPORT bool ncdbIsCustomObject(const NcDbObjectId& id);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbLoadLineTypeFile(const NCHAR* ltname, const NCHAR* fname, NcDbDatabase* pDb);

NRXDBGATE_EXPORT bool ncdbGetPreviewBitmapFromDwg(const NCHAR* pszDwgfilename, HBITMAP* pPreviewBmp, HPALETTE* pRetPal);

NRXDBGATE_EXPORT const NCHAR* ncdbGetReservedString(NcDb::reservedStringEnumType type_, bool localized_ = true);

NRXDBGATE_EXPORT const NCHAR* ncdbXlateReservedString(const NCHAR *string_, bool localized_ = true);
NRXDBGATE_EXPORT bool ncdbIsReservedString(const NCHAR *string_, NcDb::reservedStringEnumType type_);

NRXDBGATE_EXPORT resbuf* ncutBuildList(int rtype, ...);
NRXDBGATE_EXPORT resbuf* ncutNewRb(int rtype);
NRXDBGATE_EXPORT resbuf* ncutCloneRb(const resbuf* source, resbuf** lstnd);
NRXDBGATE_EXPORT int ncutRelRb(resbuf* chain);

NRXDBGATE_EXPORT bool ncdbIsPersistentReactor(void *pSomething);
NRXDBGATE_EXPORT NcDbObjectId ncdbPersistentReactorObjectId(void *pSomething);

// AutoGen:

//////////////////////////////////////////////////////////////////////////
// NcDbAppSystemVariables
class NRXDBGATE_EXPORT NcDbAppSystemVariables {
public:
	NcDbAppSystemVariables();
	~NcDbAppSystemVariables();
	Nano::ErrorStatus setAttdia(bool value, bool bUndo = false);
	bool attdia() const;
	Nano::ErrorStatus setAttreq(bool, bool bUndo = false);
	bool attreq() const;
	Nano::ErrorStatus setBlipmode(bool, bool bUndo = false);
	bool blipmode() const;
	Nano::ErrorStatus setCoords(NRX::Int16 value, bool bUndo = false);
	NRX::Int16 coords() const;
	Nano::ErrorStatus setStatusbar(NRX::Int16 value, bool bUndo = false);
	NRX::Int16 statusbar() const;
	Nano::ErrorStatus setMenubar(bool value, bool bUndo = false);
	bool menubar() const;
	Nano::ErrorStatus setAppStatusBarUseIcons(bool value, bool bUndo = false);
	bool appstatusbaruseicons() const;
	Nano::ErrorStatus setDelUsedObj(NRX::Int16, bool bUndo = false);
	NRX::Int16 delUsedObj() const;
	Nano::ErrorStatus setDragmode(NRX::Int16, bool bUndo = false);
	NRX::Int16 dragmode() const;
	Nano::ErrorStatus setOsmode(NRX::Int16 value, bool bUndo = false);
	NRX::Int16 osmode() const;
	Nano::ErrorStatus setPickstyle(NRX::Int16 value, bool bUndo = false);
	NRX::Int16 pickstyle() const;
	Nano::ErrorStatus setLwdefault(NcDb::LineWeight value, bool bUndo = false);
	NcDb::LineWeight lwdefault() const;
	Nano::ErrorStatus setHpassoc(bool value, bool bUndo = false);
	bool hpassoc() const;
private:
	bool  m_attdia;
	bool  m_attreq;
	bool  m_blipmode;
	short m_delobj;
	short m_coords;
	short m_statusbar;
	bool  m_menubar;
	bool  m_appstatusbaruseicons;
	short m_dragmode;
	short m_osmode;
	short m_pkstyle;
	NcDb::LineWeight  m_lwdefault;
	bool  m_hpassoc;
};

//////////////////////////////////////////////////////////////////////////
// NdHostImageAppServices
class __declspec(novtable) NdHostImageAppServices {
public:
	virtual const NCHAR* imageFileExtensions (bool bRefresh = false) = 0;
	virtual const NCHAR* imageFilterString (bool bRefresh = false) = 0;
	virtual bool registerFormatCodec (Ntil::ImageFormatCodec& codec) = 0;
	virtual bool formatCodecRegistered (Ntil::ImageFormatCodec& codec) = 0;
	virtual bool reRegisterFormatCodec (Ntil::ImageFormatCodec& codec) = 0;
	virtual bool unRegisterFormatCodec (Ntil::ImageFormatCodec& codec) = 0;
	virtual Ntil::ProgressCallbackInterface* registerProgressCallback (Ntil::ProgressCallbackInterface* pCallback ) = 0;
};

//////////////////////////////////////////////////////////////////////////
// RxNDSAppTableEntryType
class RxNDSAppTableEntryType {
public:
	int    lflag;
	NCHAR* appname;
	LONG_PTR  apphandle;
	int    nds_fcode;
	int    nds_invkcnt;
	struct resbuf* nds_argl;
	FunHandList* nds_fhdl;
	NcRxGenHand * modhandle;
	resbuf *nds_ret;
	int    nds_rettype;
};

//////////////////////////////////////////////////////////////////////////
// NcDbManagedHost
class NcDbManagedHost {
public:
	virtual int version() { return 1;}
	virtual Nano::ErrorStatus load(const NCHAR * fname)=0;
};

//////////////////////////////////////////////////////////////////////////
// NcRxDLinkerReactor
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcRxDLinkerReactor: public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcRxDLinkerReactor);
	virtual void rxAppWillBeLoaded(const NCHAR  * moduleName);
	virtual void rxAppLoaded(const NCHAR  * moduleName);
	virtual void rxAppLoadAborted(const NCHAR  * moduleName);
	virtual void rxAppWillBeUnloaded(const NCHAR  * moduleName);
	virtual void rxAppUnloaded(const NCHAR  * moduleName);
	virtual void rxAppUnloadAborted(const NCHAR  * moduleName);
};

//////////////////////////////////////////////////////////////////////////
// NcRxKernel
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcRxKernel : public NcRxService {
public:
	NCRX_DECLARE_MEMBERS(NcRxKernel);
	NcRxKernel();
	virtual ~NcRxKernel();
	virtual
	NcRxDictionary* newNcRxDictionary(NRX::Boolean sorted = NRX::kTrue,
	                                  NRX::Boolean ignoreCase = NRX::kFalse) = 0;
	virtual
	NcRxDictionary* newNcRxDictionary(NRX::UInt32 length,
	                                  NRX::Boolean delObjects,
	                                  NRX::Boolean sorted = NRX::kTrue,
	                                  NRX::Boolean ignoreCase = NRX::kFalse) = 0;
	virtual
	NcRxDictionary* newNcRxDictionary(const NcRxClass * filter) = 0;
};


//////////////////////////////////////////////////////////////////////////
//// NcRxProtocolReactorIterator
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcRxProtocolReactorIterator : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcRxProtocolReactorIterator);
	virtual NcRxClass* reactorClass () const = 0;
	virtual void start() = 0;
	virtual bool next () = 0;
	virtual bool done () const = 0;
	virtual NcRxProtocolReactor* object () const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcRxProtocolReactorList
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcRxProtocolReactorList : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcRxProtocolReactorList);
	virtual NcRxClass* reactorClass() const = 0;
	virtual Nano::ErrorStatus addReactor   (NcRxProtocolReactor* pReactor) = 0;
	virtual void              removeReactor(NcRxProtocolReactor* pReactor) = 0;
	virtual NcRxProtocolReactorIterator* newIterator () const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcRxProtocolReactorListIterator
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcRxProtocolReactorListIterator : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcRxProtocolReactorListIterator);
	virtual void start() = 0;
	virtual bool next () = 0;
	virtual bool done () const = 0;
	virtual NcRxProtocolReactorList* object () const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcRxProtocolReactorManager
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcRxProtocolReactorManager: public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcRxProtocolReactorManager);
	virtual NcRxProtocolReactorList* createReactorList (
	                                     NcRxClass* pReactorClass) = 0;
	virtual NcRxProtocolReactorListIterator* newIterator () const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcRxProtocolReactorManagerFactory
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcRxProtocolReactorManagerFactory : public NcRxService {
public:
	NCRX_DECLARE_MEMBERS(NcRxProtocolReactorManagerFactory);
	virtual NcRxProtocolReactorManager* createReactorManager (
	                                    NcRxClass* pRxClass) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbPasswordedFile
class NRX_NO_VTABLE NcDbPasswordedFile {
protected:
	virtual Nano::ErrorStatus tryPassword(const wchar_t* wzPassword) = 0;
	virtual const NCHAR* getFullPath() = 0;
public:
	Nano::ErrorStatus open(const wchar_t* wszPassword, NcDbHostApplicationServices::PasswordOptions options);
};

//////////////////////////////////////////////////////////////////////////
 //NcDbServices
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcDbServices: public NcRxService {
public:
	NCRX_DECLARE_MEMBERS(NcDbServices);
};

//////////////////////////////////////////////////////////////////////////
// NcDbRasterImageDefTransReactor
class NRXDBGATE_EXPORT NcDbRasterImageDefTransReactor : public NcDbObjectReactor {
public:
	NCRX_DECLARE_MEMBERS(NcDbRasterImageDefTransReactor);
	virtual     ~NcDbRasterImageDefTransReactor();
	virtual NRX::Boolean      onDeleteImage(const NcDbRasterImageDef* pImageDef,
	                                        Ntil::Image* pImage,
	                                        NcDbRasterImageDefReactor::DeleteImageEvent event,
	                                        NRX::Boolean cancelAllowed) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbLayerStateManager
class NRXDBGATE_EXPORT NcDbLayerStateManager: public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbLayerStateManager);
	NcDbLayerStateManager();
	NcDbLayerStateManager(NcDbDatabase *pHostDb);
	virtual ~NcDbLayerStateManager();
	enum LayerStateMask {
		kNone           = 0x0000,
		kOn             = 0x0001,
		kFrozen         = 0x0002,
		kLocked         = 0x0004,
		kPlot           = 0x0008,
		kNewViewport    = 0x0010,
		kColor          = 0x0020,
		kLineType       = 0x0040,
		kLineWeight     = 0x0080,
		kPlotStyle      = 0x0100,
		kCurrentViewport = 0x0200,
		kTransparency   = 0x0400,
		kAll            = kOn | kFrozen | kLocked | kPlot | kNewViewport |
		                  kColor | kLineType | kLineWeight | kPlotStyle |
		                  kCurrentViewport | kTransparency,
		kStateIsHidden  = 0x8000,
		kLastRestored   = 0x10000,
		kDecomposition  = kAll | 0x20000
	};
	enum {
		kUndefDoNothing = 0,
		kUndefTurnOff = 1,
		kUndefFreeze = 2,
		kRestoreAsOverrides = 4
	};
	bool                addReactor(NcDbLayerStateManagerReactor * pReactor);
	bool                removeReactor(NcDbLayerStateManagerReactor * pReactor);
	NcDbObjectId        layerStatesDictionaryId(bool bCreateIfNotPresent=false);
	bool                hasLayerState(const NCHAR *sName);
	Nano::ErrorStatus   saveLayerState(const NCHAR *sName, LayerStateMask mask);
	Nano::ErrorStatus   restoreLayerState(const NCHAR *sName);
	Nano::ErrorStatus   setLayerStateMask(const NCHAR *sName,
	                                      LayerStateMask mask);
	Nano::ErrorStatus   getLayerStateMask(const NCHAR *sName,
	                                      LayerStateMask &returnMask);
	Nano::ErrorStatus   deleteLayerState(const NCHAR *sName);
	Nano::ErrorStatus   renameLayerState(const NCHAR *sName,
	                                     const NCHAR *sNewName);
	Nano::ErrorStatus   importLayerState(const NCHAR *sFilename);
	Nano::ErrorStatus   importLayerState(const NCHAR *sFilename, NcString & sName);
	Nano::ErrorStatus   exportLayerState(const NCHAR *sNameToExport,
	                                     const NCHAR *sFilename);
	Nano::ErrorStatus   saveLayerState(const NCHAR *sName, LayerStateMask mask, const NcDbObjectId& idVp);
	Nano::ErrorStatus   restoreLayerState(const NCHAR *sName, const NcDbObjectId& idVp, int nRestoreFlags = 0, const LayerStateMask* pClientMask = NULL);
	Nano::ErrorStatus   setLayerStateDescription(const NCHAR* sName,
	                                             const NCHAR* sDesc);
	Nano::ErrorStatus   getLayerStateDescription(const NCHAR* sName, NCHAR*& sDesc);
	bool                layerStateHasViewportData(const NCHAR* sName);
	Nano::ErrorStatus   importLayerStateFromDb(const NCHAR *pStateName, NcDbDatabase* pDb);
	Nano::ErrorStatus   getLayerStateNames(NcStringArray& lsArray, bool bIncludeHidden = true, bool bIncludeXref = true);
	Nano::ErrorStatus   getLastRestoredLayerState(NcString & sName, NcDbObjectId &restoredLSId);
	Nano::ErrorStatus   getLayerStateLayers(NcStringArray& layerArray, const NCHAR* sName, bool bInvert = false);
	bool                compareLayerStateToDb(const NCHAR* sName, const NcDbObjectId& idVp);
	Nano::ErrorStatus   addLayerStateLayers(const NCHAR *sName, const NcDbObjectIdArray& layerIds);
	Nano::ErrorStatus   removeLayerStateLayers(const NCHAR *sName, const NcStringArray& layerNames);
	bool                isDependentLayerState(const NCHAR *sName);
	NcDbDatabase *      getDatabase() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbLayerStateManagerReactor
class NRXDBGATE_EXPORT NcDbLayerStateManagerReactor : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbLayerStateManagerReactor);
	virtual void layerStateCreated(const NCHAR * layerStateName,
	                               const NcDbObjectId& layerStateId);
	virtual void layerStateCompareFailed(const NCHAR * layerStateName,
	                                     const NcDbObjectId& layerStateId);
	virtual void layerStateToBeRestored(const NCHAR * layerStateName,
	                                    const NcDbObjectId& layerStateId);
	virtual void layerStateRestored(const NCHAR * layerStateName,
	                                const NcDbObjectId& layerStateId);
	virtual void abortLayerStateRestore(const NCHAR * layerStateName,
	                                    const NcDbObjectId& layerStateId);
	virtual void layerStateToBeDeleted(const NCHAR * layerStateName,
	                                   const NcDbObjectId& layerStateId);
	virtual void layerStateDeleted(const NCHAR * layerStateName);
	virtual void abortLayerStateDelete(const NCHAR * layerStateName,
	                                   const NcDbObjectId& layerStateId);
	virtual void layerStateToBeRenamed(const NCHAR * oldLayerStateName,
	                                   const NCHAR * newLayerStateName);
	virtual void layerStateRenamed(const NCHAR * oldLayerStateName,
	                               const NCHAR * newLayerStateName);
	virtual void abortLayerStateRename(const NCHAR * oldLayerStateName,
	                                   const NCHAR * newLayerStateName);
};

//////////////////////////////////////////////////////////////////////////
// NcRxVariable
class NcRxVariable {
public:
	enum StorageType
	{
		kStoragePerSession = 0,
		kStoragePerUser = 1,
		kStoragePerProfile = 2,
		kStoragePerDatabase = 3
	};
	enum SecondaryType
	{
		kSecondaryTypeNone = 0,
		kSecondaryTypeBoolean = 1,
		kSecondaryTypeSymbolName = 2,
		kSecondaryTypeArea = 3,
		kSecondaryTypeDistance = 4,
		kSecondaryTypeLast = 4,
	};
	enum TypeFlags
	{
		kTypeFlagsNone = 0,
		kTypeFlagSpacesAllowed = 1,
		kTypeFlagDotMeansEmpty = 2,
		kTypeFlagNoUndo = 4,
		kTypeFlagsChatty = 8
	};
	struct Range
	{
		Range():lowerBound(0), upperBound(0) {}
		Range(int lb, int ub):lowerBound(lb), upperBound(ub) {}
		int lowerBound;
		int upperBound;
	};
	NRXDBGATE_EXPORT const NCHAR* name() const;
	NRXDBGATE_EXPORT short primaryType() const;
	NRXDBGATE_EXPORT NcRxVariable::SecondaryType secondaryType() const;
	NRXDBGATE_EXPORT NcRxVariable::StorageType storageType() const;
	NRXDBGATE_EXPORT short typeFlags() const;
	NRXDBGATE_EXPORT const Range* range() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setValue(const resbuf& value, void* ownerId = NULL, NcString* failReason=NULL);
	NRXDBGATE_EXPORT Nano::ErrorStatus getValue(resbuf& value) const;
	NRXDBGATE_EXPORT bool isReadOnly(NcString* reason=NULL) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setIsReadOnly(bool value, void* ownerId, const NcString* reason=NULL);
	NRXDBGATE_EXPORT void addReactor(NcRxVariableReactor* reactor);
	NRXDBGATE_EXPORT void removeReactor(NcRxVariableReactor* reactor);
	NRXDBGATE_EXPORT Nano::ErrorStatus reset();
	~NcRxVariable();
};

//////////////////////////////////////////////////////////////////////////
// NcRxVariablesDictionary
class NcRxVariablesDictionary {
public:
	~NcRxVariablesDictionary();
	NRXDBGATE_EXPORT void addReactor(NcRxVariableReactor* reactor);
	NRXDBGATE_EXPORT void removeReactor(NcRxVariableReactor* reactor);
	NRXDBGATE_EXPORT const NcArray<NcString>& getAllNames() const;
	NRXDBGATE_EXPORT NcRxVariable* getVariable(const NCHAR* name) const;
	NRXDBGATE_EXPORT static NcRxVariablesDictionary* get();
	NRXDBGATE_EXPORT Nano::ErrorStatus reset(NcRxVariable::StorageType filter);
	NRXDBGATE_EXPORT static bool getBool(const NCHAR* name, bool def);
	NRXDBGATE_EXPORT static Nano::ErrorStatus setBool(const NCHAR* name, bool val);
	NRXDBGATE_EXPORT static short getInt16(const NCHAR* name, short def);
	NRXDBGATE_EXPORT static Nano::ErrorStatus setInt16(const NCHAR* name, short val);
	NRXDBGATE_EXPORT static double getDouble(const NCHAR* name, double def);
	NRXDBGATE_EXPORT static Nano::ErrorStatus setDouble(const NCHAR* name, double val);
	NRXDBGATE_EXPORT static NcString getString(const NCHAR* name);
	NRXDBGATE_EXPORT static Nano::ErrorStatus setString(const NCHAR* name, const NCHAR* val);
};

////////////////////////////////////////////////////////////////////////////
// NcRxVariableChangedEventArgs
class NcRxVariableChangedEventArgs {
public:
	NRXDBGATE_EXPORT const resbuf& oldValue() const;
	NRXDBGATE_EXPORT const resbuf& newValue() const;
};

////////////////////////////////////////////////////////////////////////////
// NcRxVariableChangingEventArgs
class NcRxVariableChangingEventArgs : public NcRxVariableChangedEventArgs {
public:
	NRXDBGATE_EXPORT Nano::ErrorStatus setNewValue(const resbuf& value, void* ownerId = NULL);
	NRXDBGATE_EXPORT void veto(const NCHAR* failReason);
	NRXDBGATE_EXPORT bool isResetting() const;
};

////////////////////////////////////////////////////////////////////////////
// NcRxVariableReactor
class NRX_NO_VTABLE NcRxVariableReactor : public NcRxObject {
public:
	virtual void changing(const NcRxVariable* sender, NcRxVariableChangingEventArgs& args) {}
	virtual void changed(const NcRxVariable* sender, const NcRxVariableChangedEventArgs& args) {}
};

NcDbManagedHost* CS_STDCALL ncdbGetManagedHost();
NRXDBGATE_EXPORT HRESULT CS_STDCALL ncdbInitializeManagedLayer();
Nano::ErrorStatus CS_STDCALL ncdbSetManagedHost(NcDbManagedHost* pHost);
NRXDBGATE_EXPORT HRESULT CS_STDCALL ncdbTerminateManagedLayer();
NRXDBGATE_EXPORT void ncutDelBuffer(void *& pBuffer);
NRXDBGATE_EXPORT Nano::ErrorStatus ncutNewBuffer(char *&pOutput, size_t size);
void ncutTrimWhiteSpace(NCHAR * pStr);
size_t ncutXStrLength(const NCHAR * str);
Nano::ErrorStatus ncutXStrNormalize(
                  NCHAR *& pStr,
                  bool preserveCase);
NRXDBGATE_EXPORT Nano::ErrorStatus ncutXStrUppercase(NCHAR *& pStr);

//void delBuffer(char*& pString);
NRXDBGATE_EXPORT void delString(NCHAR*& pString);

NdHostImageAppServices* getAdHostImageAppServices();

NRXDBGATE_EXPORT Nano::ErrorStatus newString(const NCHAR* pInput, NCHAR*& pOutput);
NRXDBGATE_EXPORT Nano::ErrorStatus newString(NCHAR*& pOutput, int nNumChars);
NRXDBGATE_EXPORT Nano::ErrorStatus updString(const NCHAR* pInput, NCHAR*& pOutput);

void ncedSuppressFileMRU(bool bSuppress);
void ncutAssertMessage(const NCHAR*condition, const NCHAR*filename,
                       int lineNumber, const NCHAR*status);
bool ncutSplitString( size_t & numLeftBytes,
                      const NCHAR*& pRight,
                      const NCHAR* source,
                      unsigned int delimiter);
NdHostImageAppServices* getNdHostImageAppServices();
NcRxClass* newNcRxClass(const NCHAR* className, const NCHAR* parentClassName,
                        int proxyFlags = 0, NcRxObject* (*pseudoConstructor)() = NULL,
                        const NCHAR* dxfName = NULL, const NCHAR* appName = NULL);
NcRxClass* newNcRxClass(const NCHAR* className, const NCHAR* parentClassName,
                        int dwgVer, int  maintVer, int proxyFlags = 0,
                        NcRxObject* (*pseudoConstructor)() = NULL, const NCHAR* dxfName = NULL,
                        const NCHAR* appName = NULL, ncAppNameChangeFuncPtr func = NULL);

NRXDBGATE_EXPORT bool isValidCodePageId(code_page_id value);
NRXDBGATE_EXPORT NcDbGlobals* getDefaultGlobals();

// ncdbXdRoom moved to applicationHost.cpp in NrxHostGate
// ncdbXdSize moved to applicationHost.cpp in NrxHostGate

// AutoGen.


#endif // __OPENDWG_APPLICATIONDB_H__
