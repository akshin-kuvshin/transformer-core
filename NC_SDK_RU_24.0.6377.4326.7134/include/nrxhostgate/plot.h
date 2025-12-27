#pragma once
#include "nrxhostgate_impexp.h"

class NcPlSystemInternals;
class NcPlObjectImp;
class NcPlDSDData;
class NcPlDSDEntry;
class NcPlPlotProgressDialog;
class NcadPlotInternalServices;
class NcPlPlotProgress;
class NcPlPlotInfo;
class NcPlPlotLogger;
class NcPlPlotPageInfo;
class NcPlPrecisionEntry;
class HT_Plot_Config;
class HT_Media_Size;
class HT_Media_Description;
class HT_Thin_Plot_Config_Manager;
class HT_Error_Handler;
class NcViewport;

#define NCPL_DECLARE_MEMBERS(CLASS_NAME) \
public: \
	NRXHOSTGATE_EXPORT virtual NcRxClass* isA() const; \
	NRXHOSTGATE_EXPORT static NcRxClass* desc(); \
	NRXHOSTGATE_EXPORT static CLASS_NAME* cast(const NcRxObject* source) \
	{ \
		return ((source == NULL) || !source->isKindOf(CLASS_NAME::desc())) ? NULL : (CLASS_NAME*)source; \
	}; \
	NRXHOSTGATE_EXPORT static void rxInit(); \
	NRXHOSTGATE_EXPORT static NcRxClass* gpDesc;


// Default media matching weights
#define DEFAULT_MEDIA_GROUP_WEIGHT 50
#define DEFAULT_SHEET_MEDIA_GROUP_WEIGHT 10
#define DEFAULT_MEDIA_BOUNDS_WEIGHT 100
#define DEFAULT_PRINTABLE_BOUNDS_WEIGHT 10
#define DEFAULT_DIMENSIONAL_WEIGHT 50
#define DEFAULT_SHEET_DIMENSIONAL_WEIGHT 10
#define DEFAULT_THRESHOLD 500

enum class PreviewStatus {
	kNormal = 0,
	kPlot,
	kCancel,
	kNext,
	kPrevious
};

struct NCPL_PREVIEWENDPLOT {
	PreviewStatus nStatus;
};

enum DeviceType {
	kSystemPrinter = 0,     // OS printers
	kPC3File = 1,           // pc3 print devices
	kOneOffConfig = 2,      // for internal use only
	kUninitialized = -1,
	kEmbeddedPrinter = 3,   // nanoCAD embedded printers
	kNonePrinter = 4        // printer "None"
};

struct NcPl3dDwfOptions {
	bool bGroupByXrefHierarchy;
	bool bPublishWithMaterials;
};

typedef void (*ncAppNameChangeFuncPtr)(const NcRxClass* classObj,
                NCHAR *& newAppName, int saveVer);

typedef void (*NCPLPLTPRGHELPPROC)(NcPlPlotProgressDialog *pNcPlPlotProgressDialog);

typedef NcArray<NcPlDSDEntry, NcArrayObjectCopyReallocator <NcPlDSDEntry> > NcPlDSDEntries;
typedef NcArray<NcPlPrecisionEntry, NcArrayObjectCopyReallocator <NcPlPrecisionEntry> > NcPlPrecisionEntries;

//////////////////////////////////////////////////////////////////////////
// NcPlObject
class NRX_NO_VTABLE NcPlObject : public NcRxObject, public NcHeapOperators
{
public:
	NCRX_DECLARE_MEMBERS(NcPlObject);

	NRXHOSTGATE_EXPORT virtual ~NcPlObject();

protected:
	NcPlObject();
};

//////////////////////////////////////////////////////////////////////////
// NcPlDSDEntry
class NcPlDSDEntry  : public NcPlObject {
	NCPL_DECLARE_MEMBERS(NcPlDSDEntry)
public:
	enum SheetType {
		kSingleDWF  = 0,
		kMultiDWF = 1,
		kOriginalDevice = 2,
		kSingleDWFx = 3,
		kMultiDWFx = 4,
		kSinglePDF = 5,
		kMultiPDF = 6
	};
	enum SetupType {
		kOriginalPS = 0,
		kNPSSameDWG = 1,
		kNPSOtherDWG = 2,
		k3dDwf = 3,
		kOverridePS = 4,
	};
	NRXHOSTGATE_EXPORT NcPlDSDEntry();
	NRXHOSTGATE_EXPORT virtual ~NcPlDSDEntry();
	NRXHOSTGATE_EXPORT NcPlDSDEntry(const NcPlDSDEntry & src);
	NRXHOSTGATE_EXPORT NcPlDSDEntry& operator= (const NcPlDSDEntry &src);
	NRXHOSTGATE_EXPORT const NCHAR *      dwgName() const;
	NRXHOSTGATE_EXPORT void              setDwgName(const NCHAR * pName);
	NRXHOSTGATE_EXPORT const NCHAR *      layout() const;
	NRXHOSTGATE_EXPORT void              setLayout(const NCHAR * pLayoutName);
	NRXHOSTGATE_EXPORT const NCHAR *      title() const;
	NRXHOSTGATE_EXPORT void              setTitle(const NCHAR * pTitle);
	NRXHOSTGATE_EXPORT const NCHAR *      NPS() const;
	NRXHOSTGATE_EXPORT void              setNPS(const NCHAR * pNPSName);
	NRXHOSTGATE_EXPORT const NCHAR *      NPSSourceDWG() const;
	NRXHOSTGATE_EXPORT void              setNPSSourceDWG(const NCHAR * pNPWDWGName);
	NRXHOSTGATE_EXPORT bool               has3dDwfSetup() const;
	NRXHOSTGATE_EXPORT void              setHas3dDwfSetup(bool b3dDwfSetup);
	NRXHOSTGATE_EXPORT NcPlDSDEntry::SetupType setupType() const;
	NRXHOSTGATE_EXPORT void               setSetupType(NcPlDSDEntry::SetupType eType);
};

//////////////////////////////////////////////////////////////////////////
// NcPlDSDData
class NcPlDSDData  : public NcPlObject {
	NCPL_DECLARE_MEMBERS(NcPlDSDData)
public:
	NRXHOSTGATE_EXPORT NcPlDSDData();
	NRXHOSTGATE_EXPORT virtual ~NcPlDSDData();
	NRXHOSTGATE_EXPORT NcPlDSDData(const NcPlDSDData & src);
	NRXHOSTGATE_EXPORT NcPlDSDData& operator= (const NcPlDSDData &src);
	NRXHOSTGATE_EXPORT const NCHAR *      projectPath() const;
	NRXHOSTGATE_EXPORT void              setProjectPath(const NCHAR * pVal);
	NRXHOSTGATE_EXPORT const NCHAR *      destinationName() const;
	NRXHOSTGATE_EXPORT void              setDestinationName(const NCHAR * pVal);
	NRXHOSTGATE_EXPORT void              getDSDEntries(NcPlDSDEntries &val) const;
	NRXHOSTGATE_EXPORT void              setDSDEntries(const NcPlDSDEntries &val);
	NRXHOSTGATE_EXPORT void              getPrecisionEntries(NcPlPrecisionEntries &val) const;
	NRXHOSTGATE_EXPORT void              setPrecisionEntries(const NcPlPrecisionEntries &val);
	NRXHOSTGATE_EXPORT int               numberOfDSDEntries() const;
	NRXHOSTGATE_EXPORT NcPlDSDEntry&     DSDEntryAt(int idx);
	NRXHOSTGATE_EXPORT NcPlDSDEntry::SheetType sheetType() const;
	NRXHOSTGATE_EXPORT void                    setSheetType(NcPlDSDEntry::SheetType val);
	NRXHOSTGATE_EXPORT const NCHAR *     password() const;
	NRXHOSTGATE_EXPORT void              setPassword(const NCHAR * pVal);
	NRXHOSTGATE_EXPORT void              getUnrecognizedData(
	                                NcArray<NCHAR*> &sectionArray,
	                                NcArray<NCHAR*> &dataArray) const;
	NRXHOSTGATE_EXPORT void              setUnrecognizedData(
	                                const NcArray<NCHAR*> &sectionArray,
	                                const NcArray<NCHAR*> &dataArray);
	NRXHOSTGATE_EXPORT void              setUnrecognizedData(
	                                const NCHAR * pSectionName,
	                                const NCHAR * pSectionData);
	NRXHOSTGATE_EXPORT void              setUnrecognizedData(
	    const NcStringArray& sectionArray,
	    const NcStringArray& dataArray);
	NRXHOSTGATE_EXPORT void              getUnrecognizedData(
	    NcStringArray& sectionArray,
	    NcStringArray& dataArray) const;
	NRXHOSTGATE_EXPORT unsigned int      majorVersion() const;
	NRXHOSTGATE_EXPORT void              setMajorVersion(unsigned int majorVersion);
	NRXHOSTGATE_EXPORT unsigned int      minorVersion() const;
	NRXHOSTGATE_EXPORT void              setMinorVersion(unsigned int minorVersion);
	NRXHOSTGATE_EXPORT const NCHAR *     sheetSetName() const;
	NRXHOSTGATE_EXPORT void              setSheetSetName(const NCHAR * pSheetSetName);
	NRXHOSTGATE_EXPORT unsigned int      noOfCopies() const;
	NRXHOSTGATE_EXPORT void              setNoOfCopies(unsigned int copies);
	NRXHOSTGATE_EXPORT void              setIsSheetSet(bool bSheetSet);
	NRXHOSTGATE_EXPORT bool              isSheetSet() const;
	NRXHOSTGATE_EXPORT bool              isHomogeneous() const;
	NRXHOSTGATE_EXPORT void              setIsHomogeneous(bool bHomogeneous);
	NRXHOSTGATE_EXPORT bool              plotStampOn() const;
	NRXHOSTGATE_EXPORT void              setPlotStampOn(bool bOn);
	NRXHOSTGATE_EXPORT bool              viewFile() const;
	NRXHOSTGATE_EXPORT void              setViewFile(bool bViewFile);
	NRXHOSTGATE_EXPORT const NCHAR *     selectionSetName() const;
	NRXHOSTGATE_EXPORT void              setSelectionSetName(const NCHAR * pSelSetName);
	NRXHOSTGATE_EXPORT const NCHAR *     categoryName() const;
	NRXHOSTGATE_EXPORT void              setCategoryName(const NCHAR * pCategoryName);
	NRXHOSTGATE_EXPORT const NCHAR *     logFilePath() const;
	NRXHOSTGATE_EXPORT void              setLogFilePath(const NCHAR * pLogFilePath);
	NRXHOSTGATE_EXPORT const NcPl3dDwfOptions&   get3dDwfOptions() const;
	NRXHOSTGATE_EXPORT void              set3dDwfOptions(const NcPl3dDwfOptions &val);
	NRXHOSTGATE_EXPORT bool              readDSD(const NCHAR *pName);
	NRXHOSTGATE_EXPORT bool              writeDSD(const NCHAR *pName);
	NRXHOSTGATE_EXPORT bool              includeLayerInfo() const;
	NRXHOSTGATE_EXPORT void              setIncludeLayerInfo(bool bOn);
	NRXHOSTGATE_EXPORT bool              lineMerge() const;
	NRXHOSTGATE_EXPORT void              setLineMerge(bool bOn);
	NRXHOSTGATE_EXPORT const NCHAR *     currentPrecision() const;
	NRXHOSTGATE_EXPORT void              setCurrentPrecision(const NCHAR * pCurrentPrecision);
	NRXHOSTGATE_EXPORT bool              promptForDwfName() const;
	NRXHOSTGATE_EXPORT void              setPromptForDwfName(bool bPromptForDwfName);
	NRXHOSTGATE_EXPORT bool              pwdProtectPublishedDWF() const;
	NRXHOSTGATE_EXPORT void              setPwdProtectPublishedDWF(
	                            bool bPwdProtectPublishedDWF);
	NRXHOSTGATE_EXPORT bool              promptForPassword() const;
	NRXHOSTGATE_EXPORT void              setPromptForPassword(bool bPromptForPassword);
};

//////////////////////////////////////////////////////////////////////////
// NcPlHostAppServices
class NRX_NO_VTABLE NcPlHostAppServices {
public:
	enum PlotStatus {
		kSheetIdxAndName = -5, kDisableCancelSheet = -4, kDwfFilePlotted = -3, kPlottingMsg = -2,
		kNoPlotYet = -1, kPlotStart = 0, kViewPlotLog = 1, kPlotSuccessful = 2,
		kPlotHadErrors = 3, kPlotHadSystemError = 4, kViewPlottedFile = 5, kViewFileWhenSuccessful = 6
	};
	virtual NcPlPlotLogger * getPlotLogger(void) = 0;
	virtual const NcadPlotInternalServices* ncadInternalServices() = 0;
	virtual void updatePlotJobStatus(enum NcPlHostAppServices::PlotStatus nStatus, const NCHAR *szPlotMsg) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotConfig
class NcPlPlotConfig : public NcPlObject
{
	NCPL_DECLARE_MEMBERS(NcPlPlotConfig);

public:
	enum PlotToFileCapability
	{
		kNoPlotToFile       = 0,
		kPlotToFileAllowed  = 1,
		kMustPlotToFile     = 2
	};

	NRXHOSTGATE_EXPORT virtual ~NcPlPlotConfig();

	NRXHOSTGATE_EXPORT virtual Nano::ErrorStatus copyFrom(const NcRxObject* pSrc);

	NRXHOSTGATE_EXPORT virtual void getDescriptionFields(NCHAR*& pDriverName,
	                                                   NCHAR*& pLocationName,
	                                                   NCHAR*& pComment,
	                                                   NCHAR*& pPortName,
	                                                   NCHAR*& pServerName,
	                                                   NCHAR*& pTagLine) const;
	NRXHOSTGATE_EXPORT virtual const NCHAR* deviceName() const;
	NRXHOSTGATE_EXPORT virtual const NCHAR* fullPath() const;
	NRXHOSTGATE_EXPORT virtual unsigned int maxDeviceDPI() const;
	NRXHOSTGATE_EXPORT virtual unsigned long deviceType() const;

	NRXHOSTGATE_EXPORT virtual void getCanonicalMediaNameList(NcArray<NCHAR*> &mediaList) const;
	NRXHOSTGATE_EXPORT virtual void getLocalMediaName(const NCHAR* pCanonicalMediaName,
	                                                NCHAR* &pLocalMediaName) const;
	NRXHOSTGATE_EXPORT virtual void getMediaBounds(const NCHAR* pCanonicalMediaName,
	                                             NcGePoint2d &pageSize,
	                                             NcGeBoundBlock2d &printableArea) const;
	NRXHOSTGATE_EXPORT virtual void refreshMediaNameList();

	NRXHOSTGATE_EXPORT virtual bool isPlotToFile() const;
	NRXHOSTGATE_EXPORT virtual Nano::ErrorStatus setPlotToFile(bool bPlotToFile);

	NRXHOSTGATE_EXPORT virtual Nano::ErrorStatus getDefaultFileExtension(const NCHAR*& pDefaultExtension) const;
	NRXHOSTGATE_EXPORT virtual PlotToFileCapability plotToFileCapability() const;

	NRXHOSTGATE_EXPORT virtual bool saveToPC3(const NCHAR* pPC3Name);

	NRXHOSTGATE_EXPORT virtual HT_Plot_Config* plotConfig() const;

	NRXHOSTGATE_EXPORT virtual unsigned long isCustomPossible(double width, double height,
	                                                        bool bIsDimensional, bool bIsSheet, int dpi, const
	                                                        NCHAR * pPC3Dir) const;
	NRXHOSTGATE_EXPORT virtual bool matchMediaSize(double page_x, double page_y,
	                                             double printable_w, double printable_h,
	                                             NcDbLayout::PlotPaperUnits units,
	                                             bool bIsSheet, int dpi,
	                                             const NCHAR * pTargetCanonicalName,
	                                             NCHAR *& pNearestSizeName,
	                                             NCHAR *& pLocalizedName,
	                                             double & scaleFactor);
	NRXHOSTGATE_EXPORT virtual Nano::ErrorStatus makeCustomMediaFromSizeDesc(
	    HT_Media_Size * pSize, HT_Media_Description * pDesc,
	    bool bSameDriver, bool bSavePC3,
	    const NCHAR * pSourceEntry, const NCHAR * pSourceName,
	    NCHAR *& pCanonicalSizeName, NCHAR *& pLocalizedSizeName,
	    NCHAR *& pPMPPath, NCHAR *& pPC3Path, int dpi, double & scaleFactor);
protected:
	NcPlPlotConfig(HT_Plot_Config* pConfig, const NCHAR* pDevName,
	               const NCHAR* pFullPath, unsigned long nDevType);
	NcPlPlotConfig(const NcPlPlotConfig* pOther);

private:
	NcPlPlotConfig();
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotConfigInfo
class NcPlPlotConfigInfo : public NcPlObject
{
public:
	NCPL_DECLARE_MEMBERS(NcPlPlotConfigInfo);

	NRXHOSTGATE_EXPORT NcPlPlotConfigInfo();
	NRXHOSTGATE_EXPORT NcPlPlotConfigInfo(const NCHAR * pDevName,
	                                    const NCHAR * pFullPath,
	                                    DeviceType devType);
	NRXHOSTGATE_EXPORT NcPlPlotConfigInfo(const NcPlPlotConfigInfo &copy);
	NRXHOSTGATE_EXPORT virtual ~NcPlPlotConfigInfo();

	NRXHOSTGATE_EXPORT Nano::ErrorStatus copyFrom(const NcRxObject* pSrc);
	NRXHOSTGATE_EXPORT const NcPlPlotConfigInfo& operator=(const NcPlPlotConfigInfo& src);

	NRXHOSTGATE_EXPORT const NCHAR * fullPath() const;
	NRXHOSTGATE_EXPORT void setFullPath(const NCHAR * pPath);
	
	NRXHOSTGATE_EXPORT const NCHAR * deviceName() const;
	NRXHOSTGATE_EXPORT void setDeviceName(const NCHAR * pDevName);
	
	NRXHOSTGATE_EXPORT DeviceType deviceType() const;
	NRXHOSTGATE_EXPORT void setDeviceType(DeviceType devType);
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotConfigManager
class NRX_NO_VTABLE NcPlPlotConfigManager
{
public:
	enum RefreshCode
	{
		kAll,
		kRefreshDevicesList,
		kRefreshStyleList,
		kRefreshSystemDevicesList,
		kRefreshPC3DevicesList
	};

	enum StyTypes
	{
		kUndefined      = 0,
		kRegular        = 0x01,
		kTranslation    = 0x02,
		kColorDep       = 0x04,
		kAllTypes       = 0x07
	};

	enum StdConfigs
	{
		kNoneDevice,
		kDefaultWindowsSysPrinter,
		kDWF6ePlot,
		kDWFePlotOptForPlotting,
		kDWFePlotOptForViewing,
		kPublishToWebDWF,
		kPublishToWebJPG,
		kPublishToWebPNG,
		kDWFxePlot,
		kPublishToWebDWFx,
		kPDFePlot
	};

	virtual bool getDevicesList(NcArray<NcPlPlotConfigInfo,
	                            NcArrayObjectCopyReallocator <NcPlPlotConfigInfo> > &deviceList);
	virtual bool getStyleList(NcArray<NCHAR *> &list,
	                          long styType = kAllTypes);
	virtual void refreshList(RefreshCode refreshCode = kAll);

	virtual Nano::ErrorStatus getCurrentConfig(NcPlPlotConfig*& pConfig);
	virtual Nano::ErrorStatus setCurrentConfig(NcPlPlotConfig*& pConfig,
	                                           const NCHAR * pDeviceName);

	virtual const NCHAR * getStdConfigName(StdConfigs stdConfig);

	virtual HT_Thin_Plot_Config_Manager* thinPltCfgMgr();
	virtual HT_Error_Handler* errorHandler();
	virtual HT_Error_Handler* ncadErrorHandler();
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotPageInfo
class NcPlPlotPageInfo : public NcPlObject {
	NCPL_DECLARE_MEMBERS(NcPlPlotPageInfo);
public:
	NRXHOSTGATE_EXPORT NcPlPlotPageInfo();
	NRXHOSTGATE_EXPORT virtual ~NcPlPlotPageInfo();
	NRXHOSTGATE_EXPORT NRX::Int32 entityCount() const;
	NRXHOSTGATE_EXPORT NRX::Int32 rasterCount() const;
	NRXHOSTGATE_EXPORT NRX::Int32 oleObjectCount() const;
	NRXHOSTGATE_EXPORT NRX::Int32 gradientCount() const;
	NRXHOSTGATE_EXPORT NRX::Int32 shadedViewportType() const;
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotEngine
class NRX_NO_VTABLE NcPlPlotEngine {
public:
	virtual Nano::ErrorStatus beginPlot(NcPlPlotProgress* pPlotProgress, void* pParams = NULL);
	virtual Nano::ErrorStatus endPlot(void* pParams = NULL);
	virtual Nano::ErrorStatus beginDocument(NcPlPlotInfo& plotInfo,
	                                        const NCHAR * pDocname,
	                                        void *pParams = NULL,
	                                        NRX::Int32 nCopies = 1,
	                                        bool bPlotToFile = false,
	                                        const NCHAR * pFileName = NULL);
	virtual Nano::ErrorStatus endDocument(void* pParams = NULL);
	virtual Nano::ErrorStatus beginPage(NcPlPlotPageInfo& pageInfo,
	                                    NcPlPlotInfo& plotInfo,
	                                    bool bLastPage,
	                                    void* pParams = NULL);
	virtual Nano::ErrorStatus endPage(void* pParams = NULL);
	virtual Nano::ErrorStatus beginGenerateGraphics(void* pParams = NULL);
	virtual Nano::ErrorStatus beginGenerateGraphics(NcViewport*& pViewport, void* pParams = NULL);
	virtual Nano::ErrorStatus endGenerateGraphics(void* pParams = NULL);
	virtual void destroy();
	virtual bool isBackgroundPackaging() const;
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotErrorHandler
class NcPlPlotErrorHandler : public NcPlObject {
public:
	enum ErrorResult {
		kAbort,
		kRetry,
		kIgnore
	};
	enum Handler {
		kInfo,
		kWarning,
		kError,
		kARI,
		kSevere,
		kTerminal,
		kNone
	};
	NRXHOSTGATE_EXPORT NcPlPlotErrorHandler();
	NRXHOSTGATE_EXPORT ~NcPlPlotErrorHandler();
	NCPL_DECLARE_MEMBERS(NcPlPlotErrorHandler);
public:
	NRXHOSTGATE_EXPORT virtual void infoMessage(const NCHAR *pMessage);
	NRXHOSTGATE_EXPORT virtual int messageBox(const NCHAR *pText,
	                                        const NCHAR *pCaption,
	                                        unsigned int uType,
	                                        int defaultReturn);
	NRXHOSTGATE_EXPORT virtual void info(ULONG_PTR category,
	                                   const unsigned int specific,
	                                   const NCHAR *pLocation,
	                                   const NCHAR *pContextData,
	                                   const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual ErrorResult warning(ULONG_PTR category,
	                                             const unsigned int specific,
	                                             const NCHAR *pLocation,
	                                             const NCHAR *pContextData,
	                                             const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual void severeError(ULONG_PTR category,
	                                          const unsigned int specific,
	                                          const NCHAR *pLocation,
	                                          const NCHAR *pContextData,
	                                          const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual ErrorResult error(ULONG_PTR category,
	                                           const unsigned int specific,
	                                           const NCHAR *pLocation,
	                                           const NCHAR *pContextData,
	                                           const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual ErrorResult ariError(ULONG_PTR category,
	                                              const unsigned int specific,
	                                              const NCHAR *pLocation,
	                                              const NCHAR *pContextData,
	                                              const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual void terminalError(ULONG_PTR category,
	                                            const unsigned int specific,
	                                            const NCHAR *pLocation,
	                                            const NCHAR *pContextData,
	                                            const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual void logMessage(const NCHAR *pTitle, const NCHAR *pMsg);
	NRXHOSTGATE_EXPORT virtual bool takeResponsibility(Handler kind) ;
	NRXHOSTGATE_EXPORT virtual bool setLogHandle(const NCHAR *pFilePathName) ;
	NRXHOSTGATE_EXPORT virtual void setQuietMode(bool bQuiet);
	NRXHOSTGATE_EXPORT virtual void setLogMode(bool bLog);
	NRXHOSTGATE_EXPORT virtual bool quietMode() const;
	NRXHOSTGATE_EXPORT virtual bool logMode() const;
	NRXHOSTGATE_EXPORT void getProductString(NCHAR*& pProductString) const;
	NRXHOSTGATE_EXPORT void getProgramString(NCHAR*& pProgramString) const;
	NRXHOSTGATE_EXPORT void getCompanyString(NCHAR*& pCompanyString) const;
	NRXHOSTGATE_EXPORT virtual const NCHAR* warningTitle() const;
	NRXHOSTGATE_EXPORT virtual const NCHAR* severeTitle() const;
	NRXHOSTGATE_EXPORT virtual const NCHAR* errorTitle() const;
	NRXHOSTGATE_EXPORT virtual const NCHAR* ariTitle() const;
	NRXHOSTGATE_EXPORT virtual const NCHAR* terminalTitle() const;
	NRXHOSTGATE_EXPORT virtual const NCHAR* infoTitle() const;
protected:
	NRXHOSTGATE_EXPORT void appInfoMessage(const NCHAR *pMessage);
	NRXHOSTGATE_EXPORT int appMessageBox(const NCHAR *pText,
	                                   const NCHAR *pCaption,
	                                   unsigned int uType,
	                                   int defaultReturn);
	NRXHOSTGATE_EXPORT void appInfo(ULONG_PTR category,
	                              const unsigned int specific,
	                              const NCHAR *pLocation,
	                              const NCHAR *pContextData,
	                              const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT ErrorResult appWarning(ULONG_PTR category,
	                                        const unsigned int specific,
	                                        const NCHAR *pLocation,
	                                        const NCHAR *pContextData,
	                                        const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT void appSevereError(ULONG_PTR category,
	                                     const unsigned int specific,
	                                     const NCHAR *pLocation,
	                                     const NCHAR *pContextData,
	                                     const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT ErrorResult appError(ULONG_PTR category,
	                                      const unsigned int specific,
	                                      const NCHAR *pLocation,
	                                      const NCHAR *pContextData,
	                                      const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT ErrorResult appARIError(ULONG_PTR category,
	                                         const unsigned int specific,
	                                         const NCHAR *pLocation,
	                                         const NCHAR *pContextData,
	                                         const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT void appTerminalError(ULONG_PTR category,
	                                       const unsigned int specific,
	                                       const NCHAR *pLocation,
	                                       const NCHAR *pContextData,
	                                       const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT void appLogMessage(const NCHAR *pTitle, const NCHAR *pMsg);
	NRXHOSTGATE_EXPORT bool appSetLogHandle(const NCHAR *pFilePathName);
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotErrorHandlerLock
class NcPlPlotErrorHandlerLock : public NcPlObject {
	NCPL_DECLARE_MEMBERS(NcPlPlotErrorHandlerLock);
public:
	enum LockStatus {
		kLocked,
		kUnLocked
	};
	NRXHOSTGATE_EXPORT NcPlPlotErrorHandlerLock();
	NRXHOSTGATE_EXPORT NcPlPlotErrorHandlerLock(NcPlPlotErrorHandler* pAppErrHandler,
	                                          const NCHAR * pAppName);
	NRXHOSTGATE_EXPORT LockStatus status() const;
	NRXHOSTGATE_EXPORT bool lock(NcPlPlotErrorHandler* pAppErrHandler, const NCHAR * pAppName);
	NRXHOSTGATE_EXPORT bool unLock(NcPlPlotErrorHandler* pAppErrHandler);
	NRXHOSTGATE_EXPORT void getErrorHandler(NcPlPlotErrorHandler*& pAppErrHandler) const;
	NRXHOSTGATE_EXPORT const NCHAR * appName() const;
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotFactory
class NcPlPlotFactory {
public:
	enum PreviewEngineFlags {
		kShowPlot            = 0x0001,
		kShowNextSheet       = 0x0002,
		kShowPreviousSheet   = 0x0004
	};
	static NRXHOSTGATE_EXPORT Nano::ErrorStatus createPublishEngine(NcPlPlotEngine *& pEngine);
	static NRXHOSTGATE_EXPORT Nano::ErrorStatus createPreviewEngine(NcPlPlotEngine *& pPreview,
	                                                              long nPreviewFlags = kShowPlot);
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotInfo
class NcPlPlotInfo : public NcPlObject {
public:
	NRXHOSTGATE_EXPORT NcPlPlotInfo();
	NRXHOSTGATE_EXPORT virtual ~NcPlPlotInfo();
	NCPL_DECLARE_MEMBERS(NcPlPlotInfo);
public:
	enum MergeStatus {
		kNoChanges              = 0x00000000,
		kPlotCfgName            = 0x00000001,
		kPlotPaperMargins       = 0x00000002,
		kPlotPaperSize          = 0x00000004,
		kCanonicalMediaName     = 0x00000008,
		kPlotOrigin             = 0x00000010,
		kPlotPaperUnits         = 0x00000020,
		kPlotViewportBorders    = 0x00000040,
		kPlotPlotStyles         = 0x00000080,
		kShowPlotStyles         = 0x00000100,
		kPlotRotation           = 0x00000200,
		kPlotCentered           = 0x00000400,
		kPlotHidden             = 0x00000800,
		kShadePlot              = 0x00001000,
		kShadePlotResLevel      = 0x00002000,
		kShadePlotCustomDPI     = 0x00004000,
		kPlotType               = 0x00008000,
		kPlotWindowArea         = 0x00010000,
		kPlotViewName           = 0x00020000,
		kScale                  = 0x00040000,
		kCurrentStlyeSheet      = 0x00080000,
		kScaleLineWeights       = 0x00100000,
		kPrintLineWeights       = 0x00200000,
		kDrawViewportsFirst     = 0x00400000,
		kPlotTransparency       = 0x00800000
	};
	NRXHOSTGATE_EXPORT Nano::ErrorStatus copyFrom(const NcRxObject* pOther);
	NRXHOSTGATE_EXPORT void setLayout(NcDbObjectId& layoutId);
	NRXHOSTGATE_EXPORT NcDbObjectId layout() const;
	NRXHOSTGATE_EXPORT void setOverrideSettings(const NcDbPlotSettings* pOverrides);
	NRXHOSTGATE_EXPORT const NcDbPlotSettings* overrideSettings() const;
	NRXHOSTGATE_EXPORT void setDeviceOverride(const NcPlPlotConfig* pconf);
	NRXHOSTGATE_EXPORT const NcDbPlotSettings* validatedSettings() const;
	NRXHOSTGATE_EXPORT Nano::ErrorStatus setValidatedSettings(const NcDbPlotSettings* pValidatedSettings);
	NRXHOSTGATE_EXPORT const NcPlPlotConfig* validatedConfig() const;
	NRXHOSTGATE_EXPORT void setValidatedConfig(const NcPlPlotConfig* pConfig);
	NRXHOSTGATE_EXPORT const NcPlPlotConfig* deviceOverride() const;
	NRXHOSTGATE_EXPORT bool isValidated() const;
	NRXHOSTGATE_EXPORT unsigned long mergeStatus() const;
	NRXHOSTGATE_EXPORT bool isCompatibleDocument(const NcPlPlotInfo* pOtherInfo) const;
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotInfoValidator
class NcPlPlotInfoValidator : public NcPlObject {
public:
	NRXHOSTGATE_EXPORT NcPlPlotInfoValidator();
	NRXHOSTGATE_EXPORT virtual ~NcPlPlotInfoValidator();
	NCPL_DECLARE_MEMBERS(NcPlPlotInfoValidator);
public:
	enum MatchingPolicy {
		kMatchDisabled = 1,
		kMatchEnabled,
		kMatchEnabledCustom,
		kMatchEnabledTmpCustom
	};
	enum eCustomSizeResult {
		ePossible           = 0x0000,
		eMustCreatePC3      = 0x0001,
		eRotationRequired   = 0x0002,
		ePC3DirReadOnly     = 0x0004,
		ePMPDirReadOnly     = 0x0008,
		ePMPDirMissing      = 0x0010,
		eUnknownErrPMPDir   = 0x0020,
		ePC3FileReadOnly    = 0x0040,
		eSizeTooBig         = 0x0080,
		eException          = 0x0100,
		eUnknownErrPC3File  = 0x0200,
		eUnknownErrPMPFile  = 0x0400,
		ePMPFileReadOnly    = 0x0800,
		eWidthAndHeightMustBePositive = 0x1000,
		eDeviceLoadFailed   = 0x2000
	};
	NRXHOSTGATE_EXPORT virtual Nano::ErrorStatus validate(NcPlPlotInfo& info);
	NRXHOSTGATE_EXPORT virtual unsigned long isCustomPossible(NcPlPlotInfo& info) const;
	NRXHOSTGATE_EXPORT void setMediaMatchingPolicy(MatchingPolicy policy);
	NRXHOSTGATE_EXPORT MatchingPolicy matchingPolicy() const;
	NRXHOSTGATE_EXPORT void setMediaGroupWeight(unsigned int weight = DEFAULT_MEDIA_GROUP_WEIGHT);
	NRXHOSTGATE_EXPORT unsigned int mediaGroupWeight() const;
	NRXHOSTGATE_EXPORT void setSheetMediaGroupWeight(unsigned int weight = DEFAULT_SHEET_MEDIA_GROUP_WEIGHT);
	NRXHOSTGATE_EXPORT unsigned int sheetMediaGroupWeight() const;
	NRXHOSTGATE_EXPORT void setMediaBoundsWeight(unsigned int weight = DEFAULT_MEDIA_BOUNDS_WEIGHT);
	NRXHOSTGATE_EXPORT unsigned int mediaBoundsWeight() const;
	NRXHOSTGATE_EXPORT void setPrintableBoundsWeight(unsigned int weight = DEFAULT_PRINTABLE_BOUNDS_WEIGHT);
	NRXHOSTGATE_EXPORT unsigned int printableBoundsWeight() const;
	NRXHOSTGATE_EXPORT void setDimensionalWeight(unsigned int weight = DEFAULT_DIMENSIONAL_WEIGHT);
	NRXHOSTGATE_EXPORT unsigned int dimensionalWeight() const;
	NRXHOSTGATE_EXPORT void setSheetDimensionalWeight(unsigned int weight = DEFAULT_SHEET_DIMENSIONAL_WEIGHT);
	NRXHOSTGATE_EXPORT unsigned int sheetDimensionalWeight() const;
	NRXHOSTGATE_EXPORT void setMediaMatchingThreshold(unsigned int threshold = DEFAULT_THRESHOLD);
	NRXHOSTGATE_EXPORT unsigned int mediaMatchingThreshold() const;
protected:
	unsigned int m_mediaBoundsWeight;
	unsigned int m_dimensionalWeight;
	unsigned int m_mediaGroupWeight;
	unsigned int m_printableBoundsWeight;
	unsigned int m_sheetDimensionalWeight;
	unsigned int m_sheetMediaGroupWeight;
	unsigned int m_matchingThreshold;
	MatchingPolicy m_matchingPolicy;
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotLogger
class NRX_NO_VTABLE NcPlPlotLogger {
public:
	NcPlPlotLogger(){};
	virtual ~NcPlPlotLogger(){};
	virtual Nano::ErrorStatus startJob(void) = 0;
	virtual Nano::ErrorStatus startSheet(void) = 0;
	virtual Nano::ErrorStatus logTerminalError(const NCHAR *pErrorString) = 0;
	virtual Nano::ErrorStatus logARIError(const NCHAR *pErrorString) = 0;
	virtual Nano::ErrorStatus logSevereError(const NCHAR *pErrorString) = 0;
	virtual Nano::ErrorStatus logError(const NCHAR *pErrorString) = 0;
	virtual Nano::ErrorStatus logWarning(const NCHAR *pWarningString) = 0;
	virtual Nano::ErrorStatus logMessage(const NCHAR *pMessageString) = 0;
	virtual Nano::ErrorStatus logInformation(const NCHAR *pMessageString) = 0;
	virtual Nano::ErrorStatus endSheet(void) = 0;
	virtual bool errorHasHappenedInSheet(void) const = 0;
	virtual bool warningHasHappenedInSheet(void) const = 0;
	virtual Nano::ErrorStatus endJob(void) = 0;
	virtual bool errorHasHappenedInJob(void) const = 0;
	virtual bool warningHasHappenedInJob(void) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotLoggingErrorHandler
class NcPlPlotLoggingErrorHandler : public NcPlPlotErrorHandler {
public:
	NRXHOSTGATE_EXPORT NcPlPlotLoggingErrorHandler();
	NRXHOSTGATE_EXPORT NcPlPlotLoggingErrorHandler(NcPlPlotLogger *);
	NRXHOSTGATE_EXPORT virtual ~NcPlPlotLoggingErrorHandler();
	NCPL_DECLARE_MEMBERS(NcPlPlotLoggingErrorHandler);
public:
	NRXHOSTGATE_EXPORT virtual void infoMessage(const NCHAR *pMessage);
	NRXHOSTGATE_EXPORT virtual int messageBox(const NCHAR *pText,
	                                        const NCHAR *pCaption,
	                                        unsigned int uType,
	                                        int defaultReturn);
	NRXHOSTGATE_EXPORT virtual void info(ULONG_PTR category,
	                                   const unsigned int specific,
	                                   const NCHAR *pLocation,
	                                   const NCHAR *pContextData,
	                                   const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual ErrorResult warning(ULONG_PTR category,
	                                             const unsigned int specific,
	                                             const NCHAR *pLocation,
	                                             const NCHAR *pContextData,
	                                             const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual void severeError(ULONG_PTR category,
	                                          const unsigned int specific,
	                                          const NCHAR *pLocation,
	                                          const NCHAR *pContextData,
	                                          const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual ErrorResult error(ULONG_PTR category,
	                                           const unsigned int specific,
	                                           const NCHAR *pLocation,
	                                           const NCHAR *pContextData,
	                                           const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual ErrorResult ariError(ULONG_PTR category,
	                                              const unsigned int specific,
	                                              const NCHAR *pLocation,
	                                              const NCHAR *pContextData,
	                                              const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual void terminalError(ULONG_PTR category,
	                                            const unsigned int specific,
	                                            const NCHAR *pLocation,
	                                            const NCHAR *pContextData,
	                                            const NCHAR *pRevision);
	NRXHOSTGATE_EXPORT virtual void logMessage(const NCHAR *pTitle, const NCHAR *pMsg);
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotProgress
class NRX_NO_VTABLE NcPlPlotProgress {
public:
	enum SheetCancelStatus {
		kSheetContinue,
		kSheetCanceledByCancelButton,
		kSheetCanceledByCancelAllButton,
		kSheetCanceledByCaller,
		kSheetCancelStatusCount
	};
	enum PlotCancelStatus {
		kPlotContinue,
		kPlotCanceledByCaller,
		kPlotCanceledByCancelAllButton,
		kPlotCancelStatusCount
	};
	virtual bool isPlotCancelled() const = 0;
	virtual void setPlotCancelStatus(PlotCancelStatus Cancel) = 0;
	virtual PlotCancelStatus plotCancelStatus() const = 0;
	virtual void setPlotProgressRange(int nLower, int nUpper) = 0;
	virtual void getPlotProgressRange(int &nLower, int &nUpper) const = 0;
	virtual void setPlotProgressPos(int nPos) = 0;
	virtual int  plotProgressPos() const = 0;
	virtual bool isSheetCancelled() const = 0;
	virtual void setSheetCancelStatus(SheetCancelStatus Cancel) = 0;
	virtual SheetCancelStatus sheetCancelStatus() const = 0;
	virtual void setSheetProgressRange(int nLower, int nUpper) = 0;
	virtual void getSheetProgressRange(int &nLower, int &nUpper) const = 0;
	virtual void setSheetProgressPos(int nPos) = 0;
	virtual int  sheetProgressPos() const = 0;
	virtual bool setIsVisible(bool bVisible) = 0;
	virtual bool isVisible() const = 0;
	virtual bool setStatusMsgString(const NCHAR *pMsg) = 0;
	virtual bool getStatusMsgString(NCHAR *& pMsg) const = 0;
	virtual void heartbeat(void) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotProgressDialog
class NcPlPlotProgressDialog : public NcPlPlotProgress {
public:
	enum PlotMSGIndex {
		kDialogTitle,
		kSheetName,
		kSheetNameToolTip,
		kStatus,
		kSheetProgressCaption,
		kSheetSetProgressCaption,
		kMsgCancelling,
		kMsgCancellingCurrent,
		kCancelSheetBtnMsg,
		kCancelJobBtnMsg,
		kMsgCount
	};
	virtual bool onBeginPlot() = 0;
	virtual bool onEndPlot() = 0;
	virtual bool onBeginSheet() = 0;
	virtual bool onEndSheet() = 0;
	virtual bool setPlotMsgString(PlotMSGIndex index, const NCHAR *pMsg) = 0;
	virtual bool getPlotMsgString(PlotMSGIndex index, NCHAR *& pMsg) const = 0;
	virtual bool isSingleSheetPlot() const = 0;
	virtual void destroy() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotReactor
class NcPlPlotReactor : public NcRxObject {
public:
	enum PlotType {
		kPlot,
		kPreview,
		kBackgroundPackaging,
		kBackgroundPlot
	};
	NRXHOSTGATE_EXPORT virtual void beginPlot(NcPlPlotProgress* pPlotProgress, PlotType type);
	NRXHOSTGATE_EXPORT virtual void beginDocument(NcPlPlotInfo& plotInfo,
	                                            const NCHAR * pDocname,
	                                            NRX::Int32 nCopies = 1,
	                                            bool bPlotToFile = false,
	                                            const NCHAR * pFilename = NULL);
	NRXHOSTGATE_EXPORT virtual void beginPage(NcPlPlotPageInfo& pageInfo, NcPlPlotInfo& plotInfo,
	                                        bool bLastPage);
	NRXHOSTGATE_EXPORT virtual void endPage(NcPlPlotProgress::SheetCancelStatus status);
	NRXHOSTGATE_EXPORT virtual void endDocument(NcPlPlotProgress::PlotCancelStatus status);
	NRXHOSTGATE_EXPORT virtual void endPlot(NcPlPlotProgress::PlotCancelStatus status);
	NRXHOSTGATE_EXPORT virtual void plotCancelled();
	NRXHOSTGATE_EXPORT virtual void pageCancelled();
	NRXHOSTGATE_EXPORT virtual ~NcPlPlotReactor();
protected:
	NRXHOSTGATE_EXPORT NcPlPlotReactor();
};

//////////////////////////////////////////////////////////////////////////
// NcPlPlotReactorMgr
class NRX_NO_VTABLE NcPlPlotReactorMgr {
public:
	NRXHOSTGATE_EXPORT void addReactor(NcPlPlotReactor* pReactor);
	NRXHOSTGATE_EXPORT void removeReactor(NcPlPlotReactor* pReactor);
};

//////////////////////////////////////////////////////////////////////////
// NcPlPrecisionEntry
class NcPlPrecisionEntry  : public NcPlObject {
	NCPL_DECLARE_MEMBERS(NcPlPrecisionEntry)
public:
	NRXHOSTGATE_EXPORT NcPlPrecisionEntry();
	NRXHOSTGATE_EXPORT virtual ~NcPlPrecisionEntry();
	NRXHOSTGATE_EXPORT NcPlPrecisionEntry(const NcPlPrecisionEntry & src);
	NRXHOSTGATE_EXPORT NcPlPrecisionEntry& operator= (const NcPlPrecisionEntry &src);
	NRXHOSTGATE_EXPORT const NCHAR *     title() const;
	NRXHOSTGATE_EXPORT void              setTitle(const NCHAR * pTitle);
	NRXHOSTGATE_EXPORT const NCHAR *     description() const;
	NRXHOSTGATE_EXPORT void              setDescription(const NCHAR * pDescription);
	NRXHOSTGATE_EXPORT const NCHAR *     unitType() const;
	NRXHOSTGATE_EXPORT void              setUnitType(const NCHAR * pUnitType);
	NRXHOSTGATE_EXPORT const NCHAR *     unitScale() const;
	NRXHOSTGATE_EXPORT void              setUnitScale(const NCHAR * pUnitScale);
	NRXHOSTGATE_EXPORT const double      desiredPrecision() const;
	NRXHOSTGATE_EXPORT void              setDesiredPrecision(double dDesiredPrecision);
	NRXHOSTGATE_EXPORT const int         gradientResolution() const;
	NRXHOSTGATE_EXPORT void              setGradientResolution(int nGradientResolution);
	NRXHOSTGATE_EXPORT const int         colorResolution() const;
	NRXHOSTGATE_EXPORT void              setColorResolution(int nColorResolution);
	NRXHOSTGATE_EXPORT const int         monoResolution() const;
	NRXHOSTGATE_EXPORT void              setMonoResolution(int nMonoResolution);
};

NRXHOSTGATE_EXPORT NcPlPlotProgressDialog* __stdcall
ncplCreatePlotProgressDialog( HWND hParent,
                             bool bPreview = false,
                             int nSheets = 1,
                             NCPLPLTPRGHELPPROC hlpProc = NULL,
                             bool bShowCancelSheetButton = true);
NRXHOSTGATE_EXPORT NcPlHostAppServices *NcPlGetHostAppServices();
NRXHOSTGATE_EXPORT NcPlPlotConfigManager* __stdcall ncplPlotConfigManagerPtr();
NRXHOSTGATE_EXPORT NcPlPlotReactorMgr* __stdcall ncplPlotReactorMgrPtr();

// Possible plotting system states
enum ProcessPlotState
{
	kNotPlotting = 0,       // No plot in progress
	kForegroundPlotting,    // Plot is in progress in the current process
	kBackgroundPlotting     // Plot is in progress in a background process,
	                        // this process is the foreground process.
};

NRXHOSTGATE_EXPORT ProcessPlotState __stdcall ncplProcessPlotState();
void ncplPublishExecute(NcPlDSDData dsdDataObj, NcPlPlotConfig* pConfig,
                        bool bShowPlotProgress);
NRXHOSTGATE_EXPORT Nano::ErrorStatus NcPlSetHostAppServices(NcPlHostAppServices *pHostServices);
