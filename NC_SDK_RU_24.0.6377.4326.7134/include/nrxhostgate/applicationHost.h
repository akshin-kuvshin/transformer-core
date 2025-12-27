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

#ifndef __OPENDWG_APPLICATIONHOST_H__
#define __OPENDWG_APPLICATIONHOST_H__
#include "nrxhostgate_impexp.h"


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

class NcEdCommand;
class NcEdCommandReactor;
class NcEdCommandStackReactor;
class NcEdUIContext;
class NcRxDictionary;
class NcTransaction;
class NcTransactionReactor;
class NcRxGenHand;
class NcRxDLinkerReactor;

class NcRxVariableReactor;

class NcadInternalServices;
class NcPwdCache;

struct flagmat;

#define  ncdbGetRGB  ncedGetRGB

extern "C" {typedef NcRx::AppRetCode (*DepFuncPtr)(NcRx::AppMsgCode, void*);}

//struct NcUt moved to applicationDB.cpp in NrxDbGate
//	enum QFormatBitFlags moved to applicationDB.cpp in NrxDbGate

//typedef struct fchnd moved to applicationDB.cpp in NrxDbGate

//enum NcXrefSubCommand moved to applicationDB.cpp in NrxDbGate

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

//typedef enum CODE_PAGE moved to applicationDB.cpp in NrxDbGate

//enum NcFileSelectFlags moved to applicationDB.cpp in NrxDbGate

//namespace NcadInet moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcDbLayoutManagerReactor moved to applicationDB.cpp in NrxDbGate
// 
///////////////////////////////////////////////////////////////////////////////////////////
// NcDbLayoutManager moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcDbPlotSettingsValidator moved to applicationDB.cpp in NrxDbGate

///////////////////////////////////////////////////////////////////////////////////////////
// NcDbHostApplicationProgressMeter moved to applicationDB.cpp in NrxDbGate

//enum NcSDIValues moved to applicationDB.cpp in NrxDbGate

//enum ProdIdCode moved to applicationDB.cpp in NrxDbGate

//enum class NcSDIValues moved to applicationDB.cpp in NrxDbGate


///////////////////////////////////////////////////////////////////////////////////////////
// NcDbHostApplicationServices moved to applicationDB.cpp in NrxDbGate

/////////////////////////////////////////////////////////////////////////////////////////
// NcRxDynamicLinker moved to applicationDB.cpp in NrxDbGate

///////////////////////////////////////////////////////////////////////////////////////////
// NcRxDictionary moved to applicationDB.cpp in NrxDbGate

///////////////////////////////////////////////////////////////////////////////////////////
// NcRxIterator moved to applicationDB.cpp in NrxDbGate

///////////////////////////////////////////////////////////////////////////////////////////
// NcRxDictionaryIterator moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////////////////////////
// OdRxService moved to applicationDB.cpp in NrxDbGate

///////////////////////////////////////////////////////////////////////////////////////////
// NcRxService moved to applicationDB.cpp in NrxDbGate

// Profile names list storage
//typedef NcArray< NCHAR* >  NcApProfileNameArray;

//////////////////////////////////////////////////////////////////////////
// NcApLayoutManager moved to applicationDB.cpp in NrxDbGate

///////////////////////////////////////////////////////////////////////////////////////////
// NcRxIterator
class NRXHOSTGATE_EXPORT NcApProfileManagerReactor
{
public:
	virtual void currentProfileWillChange(const NCHAR* new_profile);
	virtual void currentProfileChanged(const NCHAR* new_profile);
	virtual void currentProfileWillBeReset(const NCHAR* current_profile);
	virtual void currentProfileReset(const NCHAR* current_profile);
	virtual void currentProfileWillBeSaved(const NCHAR* current_profile);
	virtual void currentProfileSaved(const NCHAR* current_profile);
	virtual void profileWillReset(const NCHAR* name);
	virtual void profileReset(const NCHAR* name);
	virtual void profileWillBeSaved(const NCHAR* name);
	virtual void profileSaved(const NCHAR* name);
};

/////////////////////////////////////////////////////////////////////////////////////////////
// NcApProfileStorage
class NRXHOSTGATE_EXPORT NcApProfileStorage
{
public:
	virtual Nano::ErrorStatus CreateNode(const NCHAR* path, IUnknown*& unknown) = 0;
	virtual Nano::ErrorStatus GetNode(const NCHAR* path, IUnknown*& unknown) = 0;
	virtual Nano::ErrorStatus ReplaceNode(const NCHAR* path, IUnknown* unknown) = 0;
	virtual Nano::ErrorStatus DeleteNode(const NCHAR* path) = 0;
	virtual Nano::ErrorStatus GetStorageFile(LPTSTR file) = 0;
	virtual Nano::ErrorStatus Save(void) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////
// NcApProfileManager
class NRXHOSTGATE_EXPORT NcApProfileManager
{
public:
	virtual void ProfileRegistryKey(NCHAR*& key, const NCHAR* name) = 0;

	virtual Nano::ErrorStatus ProfileStorage(NcApProfileStorage*& store, const NCHAR* name,
	                                         BOOL bCreateIfNotExists = TRUE) = 0;
	virtual Nano::ErrorStatus FixedProfileStorage(NcApProfileStorage*& store, BOOL bCreateIfNotExists = TRUE) = 0;

	virtual int ProfileListNames(NcApProfileNameArray& nameList) = 0;

	virtual Nano::ErrorStatus ProfileExport(const NCHAR* name, const NCHAR* export_name) = 0;
	virtual Nano::ErrorStatus ProfileImport(const NCHAR* name, const NCHAR* import_name, const NCHAR* desc,
	                                        NRX::Boolean import_info) = 0;
	virtual Nano::ErrorStatus ProfileDelete(const NCHAR* name) = 0;
	virtual Nano::ErrorStatus ProfileReset(const NCHAR* name) = 0;
	virtual Nano::ErrorStatus ProfileSetCurrent(const NCHAR* mame) = 0;
	virtual Nano::ErrorStatus ProfileCopy(const NCHAR* new_name, const NCHAR* old_name, const NCHAR* new_desc) = 0;
	virtual Nano::ErrorStatus ProfileRename(const NCHAR* new_name, const NCHAR* old_name, const NCHAR* new_desc) = 0;

	virtual void addReactor(NcApProfileManagerReactor* reactor) = 0;
	virtual void removeReactor(NcApProfileManagerReactor* reactor) = 0;

};

NRXHOSTGATE_EXPORT NcApProfileManager* ncProfileManagerPtr();
#define ncProfileManager  ncProfileManagerPtr()

///////////////////////////////////////////////////////////////////////////////////////////
// NcApLongTransactionReactor moved to applicationDB.cpp in NrxDbGate

///////////////////////////////////////////////////////////////////////////////////////////
// NcApLongTransactionManager moved to applicationDB.cpp in NrxDbGate

///////////////////////////////////////////////////////////////////////////////////////////
// NrxAppInfo
class NRXHOSTGATE_EXPORT NrxAppInfo : public NcRxObject
{
public:
	//NCRX_DECLARE_MEMBERS(NrxAppInfo);

NrxAppInfo();
	NrxAppInfo(OdRxObject* _object);

	virtual ~NrxAppInfo();

public:
	enum CmdStatus
	{
		kNoAction = 0,
		kRetry    = 1,
		kShowMsg  = 2,
		kNoModule = 3
	};

	typedef NrxAppInfo::CmdStatus (*LoaderFunPtr)(void*);

public:
	const NCHAR* appName() const;
	void setAppName(const NCHAR*);

	const NCHAR* moduleName() const;
	void setModuleName(const NCHAR*);

	const NCHAR* appDesc() const;
	void setAppDesc(const NCHAR*);

	bool appImplements(const NCHAR*) const;

	bool managed() const;
	void setManaged(bool bManaged);

	NcadApp::ErrorStatus writeToRegistry(bool bObjDbx = false, bool skipHKLM = false);

	NcadApp::ErrorStatus readFromRegistry();
	NcadApp::ErrorStatus delFromRegistry(bool bObjDbx = false);

	NrxAppInfo::CmdStatus runAppLoader();
	void setAppLoader(LoaderFunPtr);

	NcadApp::LoadReasons loadReason();
	void setLoadReason(NcadApp::LoadReasons);
	NcadApp::ErrorStatus status() const;

	NcadApp::ErrorStatus writeGroupNameToRegistry(const NCHAR* group);

	NcadApp::ErrorStatus writeCommandNameToRegistry(const NCHAR* globalCmdName, const NCHAR* localCmdName);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Commands
#define NCRX_CMD_MODAL             0x00000000
#define NCRX_CMD_TRANSPARENT       0x00000001
#define NCRX_CMD_USEPICKSET        0x00000002
#define NCRX_CMD_REDRAW            0x00000004
#define NCRX_CMD_NOPERSPECTIVE     0x00000008 /* NOT allowed in perspective views */
#define NCRX_CMD_NOMULTIPLE        0x00000010
#define NCRX_CMD_NOTILEMODE        0x00000020 // NOT allowed with TILEMODE == 1
#define NCRX_CMD_NOPAPERSPACE      0x00000040 // NOT allowed in Paperspace
#define NCRX_CMD_PLOTONLY          0x00000080 // Allowed in plot-only state
#define NCRX_CMD_NOOEM             0x00000100
#define NCRX_CMD_UNDEFINED         0x00000200
#define NCRX_CMD_INPROGRESS        0x00000400
#define NCRX_CMD_DEFUN             0x00000800
#define NCRX_CMD_NONEWSTACK        0x00010000 //For internal use only
#define NCRX_CMD_NOINTERNALLOCK    0x00020000
#define NCRX_CMD_DOCREADLOCK       0x00080000 // not set = DOCWRITELOCK
#define NCRX_CMD_DOCEXCLUSIVELOCK  0x00100000 // not set = DOCSHAREDLOCK
#define NCRX_CMD_SESSION           0x00200000 /* Run cmd handler in the session fiber */
#define NCRX_CMD_INTERRUPTIBLE     0x00400000 // Supports OPM display of command properties
#define NCRX_CMD_NOHISTORY         0x00800000 // Command does not become default
#define NCRX_CMD_NO_UNDO_MARKER    0x01000000 // No Undo or Repeat presence.
#define NCRX_CMD_NOBEDIT           0x02000000 // blocked during a bedit session

#define NCRX_MAX_CMDNAME_LEN       64

#define NCRX_COMMAND_DOCK          NCRX_T("ACAD_REGISTERED_COMMANDS")


typedef void (*NcRxFunctionPtr)();

struct NcEdCommandStruc
{
	NcRxFunctionPtr fcnAddr;
	long            flags;
	void* app;
	HINSTANCE       hResHandle;
	NcEdCommand* cmd;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdCommand
class NRXHOSTGATE_EXPORT NcEdCommand : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcEdCommand);

	NcEdCommand();

public:
	virtual void commandUndef(bool undefIt) = 0;
	virtual NRX::Int32 commandFlags() const = 0;
	virtual NcRxFunctionPtr functionAddr() const = 0;
	virtual void functionAddr(NcRxFunctionPtr fhdl) = 0;
	virtual void* commandApp() const = 0;
	virtual NcEdUIContext* UIContext() const = 0;
	virtual int functionCode() const = 0;
	virtual void functionCode(int fcode) = 0;

	virtual const NCHAR* globalName() const = 0;
	virtual const HINSTANCE resourceHandle() const = 0;

	virtual const NCHAR* localName() const = 0;
	void addReactor(NcEdCommandReactor* pReactor);
	NRX::UInt8 defaultCommandVersion() const;
	void removeReactor(NcEdCommandReactor* pReactor);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdCommandIterator
class NRXHOSTGATE_EXPORT NcEdCommandIterator : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcEdCommandIterator);

	NcEdCommandIterator(OdRxObject* _object);

public:
	virtual bool done() const = 0;
	virtual bool next() = 0;
	virtual const NcEdCommand* command() const = 0;
	virtual const NCHAR* commandGroup() const = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdCommandStack
class OdEdCommandStack;
class NRXHOSTGATE_EXPORT NcEdCommandStack : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcEdCommandStack);

	NcEdCommandStack(OdEdCommandStack* _object);
	~NcEdCommandStack();

public:
	virtual bool atPut(const NCHAR* group, NcRxDictionary*& global, NcRxDictionary* local);

	virtual Nano::ErrorStatus addCommand(const NCHAR* group, const NCHAR* global, const NCHAR* local,
		NRX::Int32 flags, NcRxFunctionPtr func, NcEdUIContext* context = NULL,
		int fcode = -1, HINSTANCE hHandle = NULL, NcEdCommand** ret = NULL);

	virtual NcEdCommandIterator* iterator();

	virtual NcEdCommand* lookupGlobalCmd(const NCHAR* name);
	virtual NcEdCommand* lookupLocalCmd(const NCHAR* name);
	virtual NcEdCommand* lookupCmd(const NCHAR* name, bool global);
	virtual NcEdCommand* lookupCmd(const NCHAR* name, bool global, bool all_groups);
	virtual NcEdCommand* lookupCmd(const NCHAR* name, bool global, bool all_groups, bool skip_undef);
	virtual NcEdCommand* lookupCmd2(const NCHAR* name, bool global, bool all_groups, int skip_flags,
		bool match = false);

	virtual Nano::ErrorStatus popGroupToTop(const NCHAR* group);

	virtual Nano::ErrorStatus removeCmd(const NCHAR* group, const NCHAR* global_name);
	virtual Nano::ErrorStatus removeGroup(const NCHAR* group);

	void addReactor(NcEdCommandStackReactor* pReactor);
	void removeReactor(NcEdCommandStackReactor* pReactor);
public:
	OdEdCommandStack* native();

protected:
	NcArray< NcEdCommand* > m_Commands;
};

NRXHOSTGATE_EXPORT NcEdCommandStack* GetCommandStack(void);
#define ncedRegCmds  GetCommandStack()

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDoubleClickEdit moved to applicationDB.cpp in NrxDbGate

/////////////////////////////////////////////////////////////////////////////////////////////////
// NcRxEventReactor moved to applicationDB.cpp in NrxDbGate

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcEditorReactor
class NRXHOSTGATE_EXPORT NcEditorReactor : public NcRxEventReactor
{
public:
	NCRX_DECLARE_MEMBERS(NcEditorReactor);

	NcEditorReactor();
	NcEditorReactor(OdRxObject *_object);

public:
	virtual ~NcEditorReactor();

public:
	virtual void unknownCommand(const NCHAR* command, NcDbVoidPtrArray* al);
	virtual void commandWillStart(const NCHAR* command);
	virtual void commandEnded(const NCHAR* command);
	virtual void commandCancelled(const NCHAR* command);
	virtual void commandFailed(const NCHAR* command);

	virtual void lispWillStart(const NCHAR* firstLine);
	virtual void lispEnded();
	virtual void lispCancelled();

	virtual void beginClose(NcDbDatabase* database);

	virtual void beginDxfIn(NcDbDatabase* database);
	virtual void abortDxfIn(NcDbDatabase* database);
	virtual void dxfInComplete(NcDbDatabase* database);

	virtual void beginDxfOut(NcDbDatabase* database);
	virtual void abortDxfOut(NcDbDatabase* database);
	virtual void dxfOutComplete(NcDbDatabase* database);

	virtual void beginDwgOpen(NCHAR* name);
	virtual void endDwgOpen(const NCHAR* name, NcDbDatabase* database);
	virtual void initialDwgFileOpenComplete(NcDbDatabase* database);

	virtual void dwgFileOpened(NcDbDatabase* database, NCHAR* name);
	virtual void databaseConstructed(NcDbDatabase* database);
	virtual void databaseToBeDestroyed(NcDbDatabase* database);
	virtual void beginSave(NcDbDatabase* database, const NCHAR* name);
	virtual void saveComplete(NcDbDatabase* database, const NCHAR* name);
	virtual void abortSave(NcDbDatabase* database);

	virtual void beginInsert(NcDbDatabase* to, const NCHAR* block, NcDbDatabase* from);
	virtual void beginInsert(NcDbDatabase* to, const NcGeMatrix3d& xform, NcDbDatabase* from);
	virtual void otherInsert(NcDbDatabase* to, NcDbIdMapping& idMap, NcDbDatabase* from);
	virtual void abortInsert(NcDbDatabase* to);
	virtual void endInsert(NcDbDatabase* to);

	virtual void wblockNotice(NcDbDatabase* database);
	virtual void beginWblock(NcDbDatabase* to, NcDbDatabase* from, const NcGePoint3d*& insertionPoint);
	virtual void beginWblock(NcDbDatabase* to, NcDbDatabase* from, NcDbObjectId blockId);
	virtual void beginWblock(NcDbDatabase* to, NcDbDatabase* from);
	virtual void otherWblock(NcDbDatabase* to, NcDbIdMapping&, NcDbDatabase* from);
	virtual void abortWblock(NcDbDatabase* to);
	virtual void endWblock(NcDbDatabase* to);

	virtual void beginDeepClone(NcDbDatabase* to, NcDbIdMapping&);
	virtual void beginDeepCloneXlation(NcDbIdMapping&, Nano::ErrorStatus*);
	virtual void abortDeepClone(NcDbIdMapping&);
	virtual void endDeepClone(NcDbIdMapping&);

	virtual void sysVarChanged(const NCHAR* varName, NRX::Boolean success);
	virtual void sysVarWillChange(const NCHAR* varName);

	virtual void beginAttach(NcDbDatabase* to, const NCHAR*, NcDbDatabase* from);
	virtual void otherAttach(NcDbDatabase* to, NcDbDatabase* from);
	virtual void abortAttach(NcDbDatabase* from);
	virtual void endAttach(NcDbDatabase* to);
	virtual void redirected(NcDbObjectId newId, NcDbObjectId oldId);
	virtual void comandeered(NcDbDatabase* to, NcDbObjectId id, NcDbDatabase* from);
	virtual void beginRestore(NcDbDatabase* to, const NCHAR*, NcDbDatabase* from);
	virtual void abortRestore(NcDbDatabase* to);
	virtual void endRestore(NcDbDatabase* to);

	virtual void xrefSubcommandBindItem(NcDbDatabase* pHost, int activity, NcDbObjectId blockId);
	virtual void xrefSubcommandAttachItem(NcDbDatabase* pHost, int activity, const NCHAR* path);
	virtual void xrefSubcommandOverlayItem(NcDbDatabase* pHost, int activity, const NCHAR* path);
	virtual void xrefSubcommandDetachItem(NcDbDatabase* pHost, int activity, NcDbObjectId blockId);
	virtual void xrefSubcommandPathItem(int activity, NcDbObjectId blockId, const NCHAR* path);
	virtual void xrefSubcommandReloadItem(NcDbDatabase* pHost, int activity, NcDbObjectId blockId);
	virtual void xrefSubcommandUnloadItem(NcDbDatabase* pHost, int activity, NcDbObjectId blockId);

	virtual void undoSubcommandAuto(int activity, NRX::Boolean state);
	virtual void undoSubcommandControl(int activity, int option);
	virtual void undoSubcommandBegin(int activity);
	virtual void undoSubcommandEnd(int activity);
	virtual void undoSubcommandMark(int activity);
	virtual void undoSubcommandBack(int activity);
	virtual void undoSubcommandNumber(int activity, int num);

	virtual void pickfirstModified();
	virtual void layoutSwitched(const NCHAR* layout);

	virtual void docFrameMovedOrResized(NRX::LongPtr hwndDocFrame, bool bMoved);
	virtual void mainFrameMovedOrResized(NRX::LongPtr hwndMainFrame, bool bMoved);

	virtual void beginDoubleClick(const NcGePoint3d& clickPoint);
	virtual void beginRightClick(const NcGePoint3d& clickPoint);

	virtual void toolbarBitmapSizeWillChange(NRX::Boolean bLarge);
	virtual void toolbarBitmapSizeChanged(NRX::Boolean bLarge);

	virtual void beginWblockObjects(NcDbDatabase* from, NcDbIdMapping& mapping);

	virtual void partialOpenNotice(NcDbDatabase* database);
	virtual void objectsLazyLoaded(const NcDbObjectIdArray& idArray);

	virtual void beginQuit();
	virtual void quitAborted();
	virtual void quitWillStart();

	virtual void modelessOperationWillStart(const NCHAR* context);
	virtual void modelessOperationEnded(const NCHAR* context);

	virtual void cmdIUnkModified(const NCHAR* command);

	virtual Nano::ErrorStatus xrefSubCommandStart(NcXrefSubCommand subcmd, const NcDbObjectIdArray& btrIds,
	                                              const NCHAR *const * btrNames, const NCHAR *const * paths);

	virtual void preXrefLockFile(NcDbObjectId btrId);

	virtual void viewChanged();

protected:
	Nano::ErrorStatus veto();

};

///////////////////////////////////////////////////////////////////////////////////////////////////
// NcEditorReactor2
class NRXHOSTGATE_EXPORT NcEditorReactor2 : public NcEditorReactor
{
public:
	NCRX_DECLARE_MEMBERS(NcEditorReactor2);

	virtual void beginDocClose(NcDbDatabase* pDwg) {}
	virtual void docCloseAborted(NcDbDatabase* pDwg) {}
	virtual void docCloseWillStart(NcDbDatabase* database) {}

	virtual void layoutToBeSwitched(const NCHAR* oldLayoutName, const NCHAR* newLayoutName) {}

	virtual void dwgViewResized(long hwndDwgView) {}
};


#define NCRX_EVENT_OBJ NCRX_T("OdRxEvent")
#define ncrxEvent NcRxEvent::cast(ncrxSysRegistry()->at(NCRX_EVENT_OBJ))

/////////////////////////////////////////////////////////////////////////////////////////////////
// NcRxEvent moved to applicationDB.cpp in NrxDbGate


////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEditor
class NRXHOSTGATE_EXPORT NcEditor : public NcRxEvent
{
public:
	NCRX_DECLARE_MEMBERS(NcEditor);
	NcEditor();
	NcEditor(OdRxObject* _object);

public:
	virtual void addReactor(NcRxEventReactor* reactor);
	virtual void removeReactor(NcRxEventReactor* reactor);

public:
	static NcEditor* instance();

public:
	HostEditor* native() const;
};

#define ncedEditor  NcEditor::instance()
 
////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdUIContext

class NRXHOSTGATE_EXPORT NcEdUIContext : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcEdUIContext);

	NcEdUIContext();

public:
	virtual ~NcEdUIContext();

public:
	typedef NcEdUIContext    wrapper_class;
	typedef HostEdUIContext  native_class;

public:
	virtual void* getMenuContext(const NcRxClass*, const NcDbObjectIdArray&) = 0;
	virtual void* getMenuContext(const NcRxClass*, const NcDbObjectIdArray&,
		const NcArray< NcDbFullSubentPathArray >& subentIds);
	virtual void* getMenuContext(const NcRxClass*, const NcDbObjectIdArray&,
		const NcArray<NcDbFullSubentPathArray,
		NcArrayMemCopyReallocator<NcDbFullSubentPathArray> >& subentIds);

	virtual void onCommand(NRX::UInt32) = 0;
	virtual void OnUpdateMenu();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbTransactionManager moved to applicationDB.cpp in NrxDbGate

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcTransaction moved to applicationDB.cpp in NrxDbGate

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcTransactionReactor moved to applicationDB.cpp in NrxDbGate

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcTransactionManager moved to applicationDB.cpp in NrxDbGate

///////////////////////////////////////////////////////////////////////////////////////////
// ncdbWcs2Ucs moved to applicationDB.cpp in NrxDbGate
// ncdbWcs2Ecs moved to applicationDB.cpp in NrxDbGate
// ncdbUcs2Wcs moved to applicationDB.cpp in NrxDbGate
// ncdbUcs2Ecs moved to applicationDB.cpp in NrxDbGate
// ncdbEcs2Wcs moved to applicationDB.cpp in NrxDbGate
// ncdbEcs2Ucs moved to applicationDB.cpp in NrxDbGate

NRXHOSTGATE_EXPORT NcGeVector3d ucsXDir();
NRXHOSTGATE_EXPORT NcGeVector3d ucsYDir();
NRXHOSTGATE_EXPORT void ucsNormalVector(NcGeVector3d& vector);


///////////////////////////////////////////////////////////////////////////////////////////////////
//
#define nds_name_set(from, to)        (*(to) = *(from), (to)[1] = (from)[1])
#define nds_point_set(from, to)       (*(to) = *(from), (to)[1] = (from)[1], (to)[2] = (from)[2])
#define nds_name_clear(name)          (name[0] = name[1] = 0)
#define nds_name_nil(name)            (name[0] == 0 && name[1] == 0)
#define nds_name_equal(name1, name2)  (name1[0] == name2[0] && name1[1] == name2[1])

#define ncad_malloc       malloc
#define ncad_free         free


// ncutNewBuffer moved to applicationDB.cpp in NrxDbGate
// ncdbFree moved to applicationDB.cpp in NrxDbGate

NRXHOSTGATE_EXPORT int ncutWcMatch(const NCHAR* string, const NCHAR* pattern);
NRXHOSTGATE_EXPORT bool ncutWcMatchEx(const NCHAR* string, const NCHAR* pattern, bool ignore_case);

// ncdbGetAdsName moved to applicationDB.cpp in NrxDbGate
// ncdbGetObjectId moved to applicationDB.cpp in NrxDbGate

// ncutDelString moved to applicationDB.cpp in NrxDbGate

// ncdbAlloc moved to applicationDB.cpp in NrxDbGate

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncutNewString(const NCHAR* source, NCHAR*& clone);
NRXHOSTGATE_EXPORT Nano::ErrorStatus ncutNewString(NCHAR*& clone, int nNumChars);
NRXHOSTGATE_EXPORT Nano::ErrorStatus ncutUpdString(const NCHAR* input, NCHAR*& output);

// ncdbRealloc moved to applicationDb.cpp in NrxDBGate

NRXHOSTGATE_EXPORT void ncrx_abort(const NCHAR* format, ...);

NRXHOSTGATE_EXPORT NCHAR* ncedGetAppName();
NRXHOSTGATE_EXPORT int ncedUpdate(int vport, nds_point p1, nds_point p2);

extern "C" {
NRXHOSTGATE_EXPORT HWND ndsw_ncadMainWnd();
}
NRXHOSTGATE_EXPORT HWND ndsw_ncadDocWnd();

NRXHOSTGATE_EXPORT int ncedCommand(int rtype, ...);
NRXHOSTGATE_EXPORT int ncedCmd(const resbuf* rbp);
NRXHOSTGATE_EXPORT int ncedRegFunc(int (* fhdl)(void), int fcode);
NRXHOSTGATE_EXPORT int ncedUsrBrk(void);
NRXHOSTGATE_EXPORT int ncedDefun(const NCHAR* sname, short funcno);
NRXHOSTGATE_EXPORT int ncedSetFunHelp(const NCHAR* pszFunctionName, const NCHAR* pszHelpfile, const NCHAR* pszTopic,
                                    int iCmd);
NRXHOSTGATE_EXPORT int ncedUndef(const NCHAR* sname, short funcno);
NRXHOSTGATE_EXPORT int ncedGetFunCode(void);
NRXHOSTGATE_EXPORT resbuf* ncedGetArgs(void);
NRXHOSTGATE_EXPORT int ncedRetList(const resbuf* rbuf);
NRXHOSTGATE_EXPORT int ncedRetVal(const resbuf* rbuf);
NRXHOSTGATE_EXPORT int ncedRetPoint(const nds_point pt);
NRXHOSTGATE_EXPORT int ncedRetStr(const NCHAR* s);
NRXHOSTGATE_EXPORT int ncedRetName(const nds_name aname, int type);
NRXHOSTGATE_EXPORT int ncedRetInt(int ival);
NRXHOSTGATE_EXPORT int ncedRetReal(nds_real rval);
NRXHOSTGATE_EXPORT int ncedRetT(void);
NRXHOSTGATE_EXPORT int ncedRetNil(void);
NRXHOSTGATE_EXPORT int ncedRetVoid(void);
NRXHOSTGATE_EXPORT int ncedEntSel(const NCHAR* str, nds_name entres, nds_point ptres);
NRXHOSTGATE_EXPORT int ncedNEntSel(const NCHAR * str, nds_name entres, nds_point ptres, nds_point xformres[4],
                                 resbuf * *refstkres);
NRXHOSTGATE_EXPORT int ncedNEntSelP(const NCHAR* str, nds_name entres, nds_point ptres, int pickflag, nds_matrix xformres,
                                  resbuf** refstkres);
NRXHOSTGATE_EXPORT int ncedSSGet(const NCHAR* str, const void* pt1, const void* pt2, const resbuf* filter, nds_name ss);
NRXHOSTGATE_EXPORT int ncedSSGetFirst(resbuf** gset, resbuf** pset);
NRXHOSTGATE_EXPORT int ncedSSSetFirst(const nds_name pset, const nds_name unused);
NRXHOSTGATE_EXPORT int ncedSSFree(const nds_name sname);
NRXHOSTGATE_EXPORT int ncedSSLength(const nds_name sname, long* len);
NRXHOSTGATE_EXPORT int ncedSSAdd(const nds_name ename, const nds_name sname, nds_name result);
NRXHOSTGATE_EXPORT int ncedSSDel(const nds_name ename, const nds_name ss);
NRXHOSTGATE_EXPORT int ncedSSMemb(const nds_name ename, const nds_name ss);
NRXHOSTGATE_EXPORT int ncedSSName(const nds_name ss, long i, nds_name entres);
NRXHOSTGATE_EXPORT int ncedSSNameX(resbuf** rbpp, const nds_name ss, const long i);
NRXHOSTGATE_EXPORT int ncedSSSubentAdd(const NcDbFullSubentPath& subentity, const nds_name sname, nds_name result);
NRXHOSTGATE_EXPORT int ncedSSGetKwordCallbackPtr(resbuf * (**pFunc)(const NCHAR*));
NRXHOSTGATE_EXPORT int ncedSSSetKwordCallbackPtr(resbuf * (*pFunc)(const NCHAR*));
NRXHOSTGATE_EXPORT int ncedSSGetOtherCallbackPtr(resbuf * (**pFunc)(const NCHAR*));
NRXHOSTGATE_EXPORT int ncedSSSetOtherCallbackPtr(resbuf * (*pFunc)(const NCHAR*));
NRXHOSTGATE_EXPORT int ncedTrans(const nds_point pt, const resbuf* from, const resbuf* to, int disp, nds_point result);
NRXHOSTGATE_EXPORT int ncedSetVar(const NCHAR* sym, const resbuf* val);
NRXHOSTGATE_EXPORT int ncedInitGet(int val, const NCHAR* kwl);
NRXHOSTGATE_EXPORT int ncedGetSym(const NCHAR* sname, resbuf** value);
NRXHOSTGATE_EXPORT int ncedPutSym(const NCHAR* sname, resbuf* value);
NRXHOSTGATE_EXPORT int ncedHelp(const NCHAR* szFilename, const NCHAR* szTopic, int iCmd);
NRXHOSTGATE_EXPORT int ncedFNSplit(const NCHAR* pathToSplit, NCHAR* prebuf, NCHAR* namebuf, NCHAR* extbuf);
NRXHOSTGATE_EXPORT resbuf* ncedNrxLoaded(void);
NRXHOSTGATE_EXPORT int ncedNrxLoad(const NCHAR* app);
NRXHOSTGATE_EXPORT int ncedNrxUnload(const NCHAR* app);
NRXHOSTGATE_EXPORT int ncedInvoke(const resbuf* args, resbuf** result);
NRXHOSTGATE_EXPORT int ncedGetVar(const NCHAR* sym, resbuf* result);
NRXHOSTGATE_EXPORT int ncedFindFile(const NCHAR* fname, NCHAR* result);
NRXHOSTGATE_EXPORT int ncedGetEnv(const NCHAR* sym, NCHAR* var);
NRXHOSTGATE_EXPORT int ncedSetEnv(const NCHAR* sym, const NCHAR* val);
NRXHOSTGATE_EXPORT int ncedGetCfg(const NCHAR* sym, NCHAR* var, int len);
NRXHOSTGATE_EXPORT int ncedSetCfg(const NCHAR* sym, const NCHAR* val);
NRXHOSTGATE_EXPORT int ncedGetString(int cronly, const NCHAR* prompt, NCHAR* result);
NRXHOSTGATE_EXPORT int ncedGetStringB(int cronly, const NCHAR* prompt, NCHAR* result, int bufsize);
NRXHOSTGATE_EXPORT int ncedMenuCmd(const NCHAR* str);
NRXHOSTGATE_EXPORT int ncedPrompt(const NCHAR* str);
NRXHOSTGATE_EXPORT int ncedAlert(const NCHAR* str);
NRXHOSTGATE_EXPORT int ncedGetAngle(const nds_point pt, const NCHAR* prompt, nds_real* result);
NRXHOSTGATE_EXPORT int ncedGetCorner(const nds_point pt, const NCHAR* prompt, nds_point result);
NRXHOSTGATE_EXPORT int ncedGetDist(const nds_point pt, const NCHAR* prompt, nds_real* result);
NRXHOSTGATE_EXPORT int ncedGetOrient(const nds_point pt, const NCHAR* prompt, nds_real* result);
NRXHOSTGATE_EXPORT int ncedGetPoint(const nds_point pt, const NCHAR* prompt, nds_point result);
NRXHOSTGATE_EXPORT int ncedGetInt(const NCHAR* prompt, int* result);
NRXHOSTGATE_EXPORT int ncedGetKword(const NCHAR *prompt, NCHAR *result);
NRXHOSTGATE_EXPORT int ncedGetKword(const NCHAR* prompt, NCHAR* result, size_t nBufLen);
NRXHOSTGATE_EXPORT int ncedGetReal(const NCHAR* prompt, nds_real* result);
NRXHOSTGATE_EXPORT int ncedGetInput(NCHAR *str);
NRXHOSTGATE_EXPORT int ncedGetInput(NCHAR* str, size_t nBufLen);
NRXHOSTGATE_EXPORT int ncedVports(resbuf** vlist);
NRXHOSTGATE_EXPORT int ncedTextScr(void);
NRXHOSTGATE_EXPORT int ncedGraphScr(void);
NRXHOSTGATE_EXPORT int ncedTextPage(void);
NRXHOSTGATE_EXPORT int ncedRedraw(const nds_name ent, int mode);
NRXHOSTGATE_EXPORT int ncedOsnap(const nds_point pt, const NCHAR* mode, nds_point result);
NRXHOSTGATE_EXPORT int ncedGrRead(int track, int* type, resbuf* result);
NRXHOSTGATE_EXPORT int ncedGrText(int box, const NCHAR* text, int hl);
NRXHOSTGATE_EXPORT int ncedGrDraw(const nds_point from, const nds_point to, int color, int hl);
NRXHOSTGATE_EXPORT int ncedGrVecs(const resbuf* vlist, nds_matrix mat);
NRXHOSTGATE_EXPORT int ncedXformSS(const nds_name ssname, nds_matrix genmat);
NRXHOSTGATE_EXPORT int ncedDragGen(const nds_name ss, const NCHAR* pmt, int cursor,
                                 int (* scnf)(nds_point pt, nds_matrix mt), nds_point p);
NRXHOSTGATE_EXPORT int ncedSetView(const resbuf* view, int vport);
NRXHOSTGATE_EXPORT int ncedGetFileD(const NCHAR* title, const NCHAR* defawlt, const NCHAR* ext, int flags,
                                  resbuf* result);
NRXHOSTGATE_EXPORT int ncedGetFileNavDialog(const NCHAR* title, const NCHAR* defawlt, const NCHAR* ext,
                                          const NCHAR* dlgname, int flags, resbuf** result);
NRXHOSTGATE_EXPORT int ncedTextBox(const resbuf* args, nds_point pt1, nds_point pt2);
NRXHOSTGATE_EXPORT int ncedTablet(const resbuf* args, resbuf** result);
NRXHOSTGATE_EXPORT int ncedGetCName(const NCHAR* cmd, NCHAR** result);
NRXHOSTGATE_EXPORT int ncdbEntDel(const nds_name ent);
NRXHOSTGATE_EXPORT int ncdbEntLast(nds_name result);
NRXHOSTGATE_EXPORT int ncdbEntNext(const nds_name ent, nds_name result);
NRXHOSTGATE_EXPORT int ncdbEntUpd(const nds_name ent);
NRXHOSTGATE_EXPORT int ncdbEntMod(const resbuf* ent);
NRXHOSTGATE_EXPORT int ncdbEntMake(const resbuf* ent);
NRXHOSTGATE_EXPORT int ncdbEntMakeX(const resbuf* entm, nds_name result);

// ncdbEntGetX moved to applicationDB.cpp in NrxDbGate
// ncdbEntGet moved to applicationDB.cpp in NrxDbGate

// ncdbRegApp moved to applicationDB.cpp in NrxDbGate
NRXHOSTGATE_EXPORT resbuf* ncdbTblNext(const NCHAR* tblname, int rewind);
NRXHOSTGATE_EXPORT resbuf* ncdbTblSearch(const NCHAR* tblname, const NCHAR* sym, int setnext);
NRXHOSTGATE_EXPORT int ncdbNamedObjDict(nds_name result);
NRXHOSTGATE_EXPORT resbuf* ncdbDictSearch(const nds_name dict, const NCHAR* sym, int setnext);
NRXHOSTGATE_EXPORT resbuf* ncdbDictNext(const nds_name dict, int rewind);
NRXHOSTGATE_EXPORT int ncdbDictRename(const nds_name dictname, const NCHAR* oldsym, const NCHAR* newsym);
NRXHOSTGATE_EXPORT int ncdbDictRemove(const nds_name dictname, const NCHAR* symname);
NRXHOSTGATE_EXPORT int ncdbDictAdd(const nds_name dictname, const NCHAR* symname, const nds_name newobj);
NRXHOSTGATE_EXPORT int ncdbTblObjName(const NCHAR* tblname, const NCHAR* sym, nds_name result);
NRXHOSTGATE_EXPORT int ncdbAngToS(nds_real v, int unit, int prec, NCHAR* str);
NRXHOSTGATE_EXPORT int ncdbRToS(nds_real val, int unit, int prec, NCHAR* str);
NRXHOSTGATE_EXPORT int ncdbAngToF(const NCHAR* str, int unit, nds_real* v);
NRXHOSTGATE_EXPORT int ncdbDisToF(const NCHAR* str, int unit, nds_real* v);
NRXHOSTGATE_EXPORT int ncdbInters(const nds_point from1, const nds_point to1, const nds_point from2, const nds_point to2,
	int teston, nds_point result);
NRXHOSTGATE_EXPORT int ncdbSNValid(const NCHAR* tbstr, int pipetest);
NRXHOSTGATE_EXPORT void ncdbFreeResBufContents(resbuf* pField);
NRXHOSTGATE_EXPORT void ncdbFail(const NCHAR* str);

NRXHOSTGATE_EXPORT int ncdbHandEnt(const NCHAR* handle, nds_name entres);

// ncutPrintf moved to applicationDB.cpp in NrxDbGate

NRXHOSTGATE_EXPORT int ncedGetFullInput(NCHAR*& pStr);
NRXHOSTGATE_EXPORT int ncedGetFullKword(const NCHAR* pString, NCHAR*& pStr);
NRXHOSTGATE_EXPORT int ncedGetFullString(int cronly, const NCHAR* pString, NCHAR*& pResult);
NRXHOSTGATE_EXPORT int ncedSSNameXEx(resbuf** rbpp, const nds_name ss, const long i, unsigned int flags = 0);


NRXHOSTGATE_EXPORT bool ncrxLoadModule(const NCHAR* moduleName, bool printit, bool command = false);
NRXHOSTGATE_EXPORT bool ncrxLoadApp(const NCHAR* appname, bool command = false);
NRXHOSTGATE_EXPORT bool ncrxUnloadModule(const NCHAR* moduleName, bool command = false);
NRXHOSTGATE_EXPORT bool ncrxUnloadApp(const NCHAR* appName, bool command = false);
NRXHOSTGATE_EXPORT void* ncrxLoadedApps();
NRXHOSTGATE_EXPORT bool ncrxAppIsLoaded(const NCHAR* name);
NRXHOSTGATE_EXPORT const NCHAR* ncrxProductKey();
NRXHOSTGATE_EXPORT const NCHAR* ncrxObjectDBXRegistryKey();
NRXHOSTGATE_EXPORT unsigned long ncrxProductLCID();
NRXHOSTGATE_EXPORT NcadApp::ErrorStatus ncrxRegisterApp(NcadApp::LoadReasons alr, const NCHAR* name, bool bDwgU = false);
NRXHOSTGATE_EXPORT NcadApp::ErrorStatus ncrxUnregisterApp(const NCHAR* name, bool bDwgU = false);
NRXHOSTGATE_EXPORT void* ncrxGetServiceSymbolAddr(const NCHAR* name, const NCHAR* symbol);
NRXHOSTGATE_EXPORT void* ncrxRegisterService(const NCHAR* name);
NRXHOSTGATE_EXPORT bool ncrxServiceIsRegistered(const NCHAR* name);
NRXHOSTGATE_EXPORT bool ncrxUnlockApplication(void* application);
NRXHOSTGATE_EXPORT bool ncrxApplicationIsLocked(const NCHAR* name);
NRXHOSTGATE_EXPORT bool ncrxLockApplication(void* id);
NRXHOSTGATE_EXPORT bool ncrxIsAppMDIAware(const NCHAR* name);
NRXHOSTGATE_EXPORT bool ncrxRegisterAppMDIAware(void* id);
NRXHOSTGATE_EXPORT bool ncrxRegisterAppNotMDIAware(void* id);

NRXHOSTGATE_EXPORT int ncedCmdLookup(const NCHAR* command, int globalLookup, NcEdCommandStruc* retStruc,
                                   int skipUndef = FALSE);
NRXHOSTGATE_EXPORT int ncedCmdLookup2(const NCHAR* command, int globalLookup, NcEdCommandStruc* retStruc,
                                    int sf = NCRX_CMD_DEFUN);
NRXHOSTGATE_EXPORT int ncedCmdUndefine(const NCHAR* command, int undefIt);
NRXHOSTGATE_EXPORT int ncedPopCommandDirectory(const NCHAR* cmdDirName);
NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedGetCommandForDocument(NcApDocument* document, NCHAR*& pGlobalCmdName);
NRXHOSTGATE_EXPORT NRX::Boolean ncedSetOLELock(int handle, int flags = 0);
NRXHOSTGATE_EXPORT NRX::Boolean ncedClearOLELock(int handle);
NRXHOSTGATE_EXPORT void ncedPostCommandPrompt();

NRXHOSTGATE_EXPORT NRX::Boolean ncedAddObjectContextMenu(const NcRxClass* rxclass, NcEdUIContext* context,
                                                       const void* id);
NRXHOSTGATE_EXPORT NRX::Boolean ncedRemoveObjectContextMenu(const NcRxClass* rxclass, NcEdUIContext* context);

NRXHOSTGATE_EXPORT NRX::Boolean ncedAddDefaultContextMenu(NcEdUIContext* context, const void* id,
                                                        const NCHAR* application = NULL);
NRXHOSTGATE_EXPORT NRX::Boolean ncedRemoveDefaultContextMenu(NcEdUIContext* context);

NRXHOSTGATE_EXPORT bool ncedSetCMBaseAlias(LPCTSTR alias, NcadContextMenuMode mode);
NRXHOSTGATE_EXPORT LPCTSTR ncedGetCMBaseAlias(NcadContextMenuMode mode);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedMspace();
NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedPspace();
NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedSetCurrentVPort(int vpnumber);
NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedSetCurrentVPort(const NcDbViewport* viewport);

NRXHOSTGATE_EXPORT int ncedIsDragging(void);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedSetCurrentView(NcDbViewTableRecord* record, NcDbViewport* viewport);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedRestoreCurrentView(const NcDbObjectId& named_view);

// ncdbUcsMatrix moved to applicationDB.cpp in NrxDbGate

// ncdbGetExtnames moved to applicationDB.cpp in NrxDbGate
// ncdbSetExtnames moved to applicationDB.cpp in NrxDbGate

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedSetCurrentUCS(const NcGeMatrix3d& mat);
NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedGetCurrentUCS(NcGeMatrix3d& mat);
NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedRestorePreviousUCS();

// ncdbDoSetupForLayouts moved to applicationDB.cpp in NrxDbGate
// ncdbDoSetupForLayouts moved to applicationDB.cpp in NrxDbGate
// ncdbClearSetupForLayouts moved to applicationDB.cpp in NrxDbGate
// ncdbClearSetupForLayouts moved to applicationDB.cpp in NrxDbGate

NRXHOSTGATE_EXPORT void ncedEditToleranceInteractive(NcDbFcf *pTol);

NRXHOSTGATE_EXPORT int ncedEditMTextInteractive(NcDbMText* text, bool useNewUI = false, bool allowTabs = false);

NRXHOSTGATE_EXPORT unsigned long ncedGetRGB(int color);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedGetCurrentSelectionSet(NcDbObjectIdArray& selset);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedGetFullSubentPathsForCurrentSelection(const NcDbObjectId& selobjs,
                                                                             NcDbFullSubentPathArray& selsubents);

NRXHOSTGATE_EXPORT IDispatch* ncedGetIDispatch(BOOL bAddRef);

NRXHOSTGATE_EXPORT NcDbObjectId ncedActiveViewportId();

NRXHOSTGATE_EXPORT NcDbObjectId ncedViewportIdFromNumber(int index);

NRXHOSTGATE_EXPORT int ncedNumberOfViewports();

NRXHOSTGATE_EXPORT NcDbObjectId ncedGetCurViewportObjectId();

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedConvertEntityToHatch(NcDbHatch* hatch, NcDbEntity*& entity, bool transfer_id);

NRXHOSTGATE_EXPORT bool ncedHatchPalletteDialog(NcString const & currentPattern, bool showCustoms, NcString & newPattern); // newPattern can be same ref as currentPattern

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedDrawOrderInherit(NcDbObjectId parent, NcDbObjectIdArray& children,
                                                        NcEdDrawOrderCmdType cmd);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedCreateViewportByView(NcDbDatabase* pDb, const NcDbObjectId& view,
                                                            const NcGePoint2d& location, double scale,
                                                            NcDbObjectId& viewportId);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedCreateEnhancedViewportOnDrop(const NCHAR* filename, const NCHAR* view,
                                                                    const NcGePoint2d location, double scale,
                                                                    NcDbObjectId label, NcDbObjectId& sheet_view,
                                                                    NcDbObjectId& viewport);
NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedCreateEnhancedViewportOnDropDWG(const NCHAR* filename, NcDbExtents* extents,
                                                                       const NcGePoint2d location, double scale,
                                                                       NcDbObjectId label, NcDbObjectId& sheet_view,
                                                                       NcDbObjectId& viewport);

const NcString *ncedGetUnitsValueString(NcDb::UnitsValue units);

// ncdbCanonicalToSystemRange moved to applicationDB.cpp in NrxDbGate
// ncdbSystemRangeToCanonical moved to applicationDB.cpp in NrxDbGate

NRXHOSTGATE_EXPORT Nano::ErrorStatus nccmGetColorFromACIName(NcCmColor& color, const NCHAR* input);
NRXHOSTGATE_EXPORT Nano::ErrorStatus nccmGetColorFromRGBName(NcCmColor& color, const NCHAR* input);
NRXHOSTGATE_EXPORT Nano::ErrorStatus nccmGetColorFromColorBookName(NcCmColor& color, const NCHAR* book_name,
                                                                 const NCHAR* color_name);

NRXHOSTGATE_EXPORT void nccmGetLocalizedColorNames(const NCHAR* colors[9]);

NRXHOSTGATE_EXPORT int nds_queueexpr(LPTSTR);

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedSyncFileOpen(const NCHAR* pszFileToOpen, const NCHAR* password = NULL);

NRXHOSTGATE_EXPORT NRX::Boolean ncedSetColorDialog(int& color, NRX::Boolean allow_meta_color,
                                                 int current_layer_color);
NRXHOSTGATE_EXPORT NRX::Boolean ncedSetColorDialogTrueColor(NcCmColor& color, NRX::Boolean allow_meta_color,
                                                          const NcCmColor& current_layer_color,
                                                          NcCm::DialogTabs tabs = (NcCm::DialogTabs)(NcCm::kACITab |
                                                                                        NcCm::kTrueColorTab |
                                                                                        NcCm::kColorBookTab));
NRXHOSTGATE_EXPORT NRX::Boolean ncedSetColorPrompt(NCHAR* prompt, NcCmColor& color,
                                                 NRX::Boolean allow_meta_color);

NRXHOSTGATE_EXPORT NRX::Boolean ncedIsMenuGroupLoaded(const NCHAR* group);
NRXHOSTGATE_EXPORT void ncedSendModelessOperationStart(const NCHAR* context);
NRXHOSTGATE_EXPORT void ncedSendModelessOperationEnded(const NCHAR* context);
NRXHOSTGATE_EXPORT void ncedUpdateDisplay();
NRXHOSTGATE_EXPORT void ncedUpdateDisplayPause(bool enable);
NRXHOSTGATE_EXPORT bool ncedIsUpdateDisplayPaused(void);

NRXHOSTGATE_EXPORT Nano::ErrorStatus applyCurDwgLayerTableChanges();

NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedVportTableRecords2Vports();
NRXHOSTGATE_EXPORT Nano::ErrorStatus ncedVports2VportTableRecords();

// ncutAngle moved to applicationDB.cpp in NrxDbGate
// ncutDistance moved to applicationDB.cpp in NrxDbGate
// ncutPolar moved to applicationDB.cpp in NrxDbGate

NRXHOSTGATE_EXPORT const NCHAR* ncadErrorStatusText(Nano::ErrorStatus es);

// ncdbGetPreviewBitmapFromDwg moved to applicationDB.cpp in NrxDbGate

// ncdbGetReservedString moved to applicationDB.cpp in NrxDbGate

// ncdbXlateReservedString moved to applicationDB.cpp in NrxDbGate
// ncdbIsReservedString moved to applicationDB.cpp in NrxDbGate

// ncutBuildList moved to applicationDB.cpp in NrxDbGate
// ncutNewRb moved to applicationDB.cpp in NrxDbGate
// ncutCloneRb moved to applicationDB.cpp in NrxDbGate
// ncutRelRb moved to applicationDB.cpp in NrxDbGate

// ncdbIsPersistentReactor moved to applicationDB.cpp in NrxDbGate
// ncdbPersistentReactorObjectId moved to applicationDB.cpp in NrxDbGate

NRXHOSTGATE_EXPORT bool ncdbDisplayPreviewFromDwg(const NCHAR* pszDwgfilename, void* pPreviewWnd,
	const NRX::UInt32* pBgColor = NULL);

//  ncdbIsCustomObject moved to applicationDB.cpp in NrxDbGate
//  ncdbLoadLineTypeFile moved to applicationDB.cpp in NrxDbGate

// AutoGen:

//////////////////////////////////////////////////////////////////////////
// NcDbAppSystemVariables moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NdHostImageAppServices moved to applicationDB.cpp in NrxDbGate


////////////////////////////////////////////////////////////////////////
// RxNDSAppTableEntryType moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcDbManagedHost moved to applicationDB.cpp in NrxDbGate

////////////////////////////////////////////////////////////////////////
// NcRxDLinkerReactor moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcRxKernelmoved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcRxProtocolReactorIterator moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcRxProtocolReactorList moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcRxProtocolReactorListIterator moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcRxProtocolReactorManager moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcRxProtocolReactorManagerFactory moved to applicationDB.cpp in NrxDbGate

////////////////////////////////////////////////////////////////////////
// NcDbPasswordedFile moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcDbServices moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcDbRasterImageDefTransReactor moved to applicationDB.cpp in NrxDbGate

////////////////////////////////////////////////////////////////////////
// NcDbLayerStateManager moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcDbLayerStateManagerReactor moved to applicationDB.cpp in NrxDbGate

////////////////////////////////////////////////////////////////////////
// NcRxVariable moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcRxVariablesDictionary moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcRxVariableChangedEventArgs moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcRxVariableChangingEventArgs moved to applicationDB.cpp in NrxDbGate

//////////////////////////////////////////////////////////////////////////
// NcRxVariableReactor moved to applicationDB.cpp in NrxDbGate

// ncdbGetManagedHost moved to applicationDB.cpp in NrxDbGate
// ncdbInitializeManagedLayer moved to applicationDB.cpp in NrxDbGate
// ncdbSetManagedHost moved to applicationDB.cpp in NrxDbGate
// ncdbTerminateManagedLayer moved to applicationDB.cpp in NrxDbGate
// ncutDelBuffer moved to applicationDB.cpp in NrxDbGate
// ncutNewBuffer moved to applicationDB.cpp in NrxDbGate
// ncutTrimWhiteSpace moved to applicationDB.cpp in NrxDbGate
// ncutXStrLength moved to applicationDB.cpp in NrxDbGate
// ncutXStrNormalize moved to applicationDB.cpp in NrxDbGate
// ncutXStrUppercase moved to applicationDB.cpp in NrxDbGate

// delBuffer moved to applicationDB.cpp in NrxDbGate
// delString moved to applicationDB.cpp in NrxDbGate

// getAdHostImageAppServices moved to applicationDB.cpp in NrxDbGate

// newString moved to applicationDB.cpp in NrxDbGate
// newString moved to applicationDB.cpp in NrxDbGate
// updString moved to applicationDB.cpp in NrxDbGate

// ncedSuppressFileMRU moved to applicationDB.cpp in NrxDbGate
// ncutAssertMessage moved to applicationDB.cpp in NrxDbGate
// ncutSplitString moved to applicationDB.cpp in NrxDbGate
// getNdHostImageAppServices moved to applicationDB.cpp in NrxDbGate
// newNcRxClass moved to applicationDB.cpp in NrxDbGate
// newNcRxClass moved to applicationDB.cpp in NrxDbGate

// isValidCodePageId moved to applicationDB.cpp in NrxDbGate
// getDefaultGlobals moved to applicationDB.cpp in NrxDbGate

// ncdbXdRoom moved to applicationDB.cpp in NrxDbGate
// ncdbXdSize moved to applicationDB.cpp in NrxDbGate
NRXHOSTGATE_EXPORT int ncdbXdRoom(const nds_name ent, NRX::Int32* result);
NRXHOSTGATE_EXPORT int ncdbXdSize(const resbuf* rb, NRX::Int32* result);
// AutoGen.


#endif // __OPENDWG_APPLICATIONHOST_H__
