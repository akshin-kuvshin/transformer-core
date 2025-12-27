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

#ifndef __OPENDWGDOCMGR_H__
#define __OPENDWGDOCMGR_H__

#include <wtypes.h>  // for HINSTANCE
#include "nrxdbgate_impexp.h"

class CDocument;
class HostApDocManager;
class HostApDocument;
class HostApDocumentIterator;
class NcApPlotReactor;
class NcApStatusBar;
class NcDbDatabase;
class NcEdInputPointManager;
class NcGiTransientManager;
class NcGiTransientManagerImpl;
class NcRxIterator;
class NcTransactionManager;
class hostMDIResponder;
class hostMDISource;

struct NcAp
{
	enum DocLockMode
	{
		kNone               = 0x00,
		kAutoWrite          = 0x01,
		kNotLocked          = 0x02,
		kWrite              = 0x04,
		kProtectedAutoWrite = 0x14,
		kRead               = 0x20,
		kXWrite             = 0x40
	};
};

class NcLispAppInfo
{
public:
	NCHAR appFileName[_MAX_PATH];
	bool  bUnloadable;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcApDocument
class NRXDBGATE_EXPORT NcApDocument : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcApDocument);

	NcApDocument(OdRxObject* _object);
	virtual ~NcApDocument();

public:
	typedef HostApDocument  native_class;

public:
	// Returns the full path and filename of the database
	virtual const NCHAR* fileName() const;

	// Returns the associated MFC CDocument object
	//
	virtual CDocument* cDoc() const;

	virtual NcTransactionManager* transactionManager() const;

	virtual NcDbDatabase* database() const;

	enum SaveFormat
	{
		kUnknown = -1,      // Invalid format
		kR12_dxf = 1,       // AutoCAD R12/LT2 DXF (*.dxf)

		kR13_dwg = 4,       // AutoCAD R13/LT95 Drawing (*.dwg)
		kR13_dxf = 5,       // AutoCAD R13/LT95 DXF (*.dxf)

		kR14_dwg = 8,       // AutoCAD R14/LT97 Drawing (*.dwg)
		kR14_dxf = 9,       // AutoCAD R14/LT97 DXF (*.dxf)

		k2000_dwg = 12,      // AutoCAD 2000 Drawing (*.dwg)
		k2000_dxf = 13,      // AutoCAD 2000 DXF (*.dxf)
		k2000_Template = 14, // 2000 Drawing Template File (*.dwt)
		k2000_Standard = 15, // 2000(+) Drawing Standard File (*.dws)
		k2000_xml = 16,      // 2000(+) = DesignXML v1.0 File (*.xml)

		k2004_dwg = 24,      // AutoCAD 2004 Drawing (*.dwg)
		k2004_dxf = 25,      // AutoCAD 2004 DXF (*.dxf)
		k2004_Template = 26, // AutoCAD 2004 Template File (*.dwt)
		k2004_Standard = 27, // 2004 Drawing Standard File (*.dws)

		k2007_dwg = 36,      // AutoCAD 2007 Drawing (*.dwg)
		k2007_dxf = 37,      // AutoCAD 2007 DXF (*.dxf)
		k2007_Template = 38, // AutoCAD 2007 Template File (*.dwt)
		k2007_Standard = 39, // 2007 Drawing Standard File (*.dws)

		k2010_dwg = 48,      // AutoCAD 2010 Drawing (*.dwg)
		k2010_dxf = 49,      // AutoCAD 2010 DXF (*.dxf)
		k2010_Template = 50, // AutoCAD 2010 Template File (*.dwt)
		k2010_Standard = 51, // 2010 Drawing Standard File (*.dws)

		k2013_dwg = 60,      // AutoCAD 2013 Drawing (*.dwg)
		k2013_dxf = 61,      // AutoCAD 2013 DXF (*.dxf)
		k2013_Template = 62, // AutoCAD 2013 Template File (*.dwt)
		k2013_Standard = 63, // 2013 Drawing Standard File (*.dws)

		k2018_dwg = 64,      // AutoCAD 2018 Drawing (*.dwg)
		k2018_dxf = 65,      // AutoCAD 2018 DXF (*.dxf)
		k2018_Template = 66, // AutoCAD 2018 Template File (*.dwt)
		k2018_Standard = 67, // 2018 Drawing Standard File (*.dws)

		kNative = k2018_dwg,  // Current dwg version is 2018
		kNative_Template = k2018_Template  //Current dwt version is 2018
	};

	virtual SaveFormat formatForSave() const;

	virtual NcAp::DocLockMode lockMode(bool bIncludeMyLocks = false) const;
	virtual NcAp::DocLockMode myLockMode() const;

	virtual bool isQuiescent() const;

	virtual void* contextPtr() const;

	virtual NcEdInputPointManager* inputPointManager();

	virtual const NCHAR* docTitle() const;

	virtual IDispatch* GetIDispatch(bool bAddRef);

	virtual bool isReadOnly() const;

	virtual int GetCountOfLispList() const;
	virtual NcLispAppInfo* GetItemOfLispList(int nIndex) const;

	virtual NcApStatusBar* drawingStatusBar() const;

	void pushDbmod();
	Nano::ErrorStatus popDbmod();

	Nano::ErrorStatus downgradeDocOpen(bool bPromptForSave);
	Nano::ErrorStatus upgradeDocOpen();

public:
	HostApDocument* native() const;
	HostApDocument* detach();

public:
	static NcApDocument* attach(const HostApDocument* _document);

protected:
	NcTransactionManager  * m_pTransactionManager;
	NcGiTransientManager  * m_pTransientManager;
	NcEdInputPointManager * m_pInputPointManager;

  // Lion007 additions
  NcGsModel             * m_pGsModel;

  NcGsModel * gsModel() { return m_pGsModel; }
  void setGsModel(NcGsModel * pGsModel);

	friend class NcGiTransientManagerImpl;
	friend class NcGsModel;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcApDocManagerReactor
class NRXDBGATE_EXPORT NcApDocManagerReactor : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcApDocManagerReactor);

	NcApDocManagerReactor();
	NcApDocManagerReactor(OdRxObject *object_);

	~NcApDocManagerReactor();

public:
	virtual void documentCreateStarted(NcApDocument* document);
	virtual void documentCreated(NcApDocument* document);
	virtual void documentToBeDestroyed(NcApDocument* document);
	virtual void documentDestroyed(const NCHAR* fileName);
	virtual void documentCreateCanceled(NcApDocument* document);

	virtual void documentLockModeWillChange(NcApDocument* document, NcAp::DocLockMode myCurrentMode,
	                                        NcAp::DocLockMode myNewMode, NcAp::DocLockMode currentMode,
	                                        const NCHAR* pGlobalCmdName);
	virtual void documentLockModeChangeVetoed(NcApDocument* document, const NCHAR* global_command);
	virtual void documentLockModeChanged(NcApDocument* document, NcAp::DocLockMode myPreviousMode,
	                                     NcAp::DocLockMode myCurrentMode, NcAp::DocLockMode currentMode,
	                                     const NCHAR* pGlobalCmdName);

	virtual void documentBecameCurrent(NcApDocument* document);

	virtual void documentToBeActivated(NcApDocument* document);
	virtual void documentToBeDeactivated(NcApDocument* document);
	virtual void documentActivationModified(bool bActivation);
	virtual void documentActivated(NcApDocument* document);
protected:
	Nano::ErrorStatus veto();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcApDocumentIterator
class NRXDBGATE_EXPORT NcApDocumentIterator : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcApDocumentIterator);

	NcApDocumentIterator(OdRxObject* _object);

public:
	virtual bool done() const;
	virtual void step();
	virtual NcApDocument* document();

public:
	HostApDocumentIterator* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcApDocManager
class NRXDBGATE_EXPORT NcApDocManager : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcApDocManager);

	NcApDocManager(OdRxObject* _object);

public:
	virtual ~NcApDocManager();

public:
	virtual NcApDocument* curDocument() const;
	virtual NcApDocument* mdiActiveDocument() const;

	virtual bool isApplicationContext() const;

	virtual NcApDocument* document(const NcDbDatabase*) const;

	virtual Nano::ErrorStatus lockDocument(NcApDocument* document, NcAp::DocLockMode lockMode = NcAp::kWrite,
	                                       const NCHAR* pGlobalCmdName = NULL, const NCHAR* pLocalCmdName = NULL,
	                                       bool prompt = true);
	virtual Nano::ErrorStatus unlockDocument(NcApDocument* document);

	virtual NcApDocumentIterator* newNcApDocumentIterator();

	virtual void addReactor(NcApDocManagerReactor*);
	virtual void removeReactor(NcApDocManagerReactor*);

	virtual Nano::ErrorStatus setDefaultFormatForSave(NcApDocument::SaveFormat format);

	virtual Nano::ErrorStatus setCurDocument(NcApDocument* document, NcAp::DocLockMode = NcAp::kNone,
	                                         bool activate = false);

	virtual Nano::ErrorStatus activateDocument(NcApDocument* document, bool bPassScript = false);

	virtual Nano::ErrorStatus sendStringToExecute(NcApDocument* document, const NCHAR* pszExecute, bool bActivate = true,
	                                              bool wrap = false, bool echo = true);

	// These two member functions allow synchronous access to NEW OPEN
	// They may only be called from the application context
	// See also executeInApplicationContext() These APIs only
	// function in MDI mode.
	virtual Nano::ErrorStatus appContextNewDocument(const NCHAR* name);
	virtual Nano::ErrorStatus appContextOpenDocument(const NCHAR* name);

	// Open a drawing and switch to the layout or view specified, if any.
	// This will become a pure virtual method in a future release.
	struct DocOpenParams
	{
		union
		{
			// drawing file name
			const NCHAR*   mpszFileName;
			const wchar_t* mpwszFileName;
		};

		union
		{
			// layout or view name, or handle string
			const NCHAR*   mpszViewName;
			const wchar_t* mpwszViewName;
			const double*  mpCoords; // or world coords to zoom to
		};

		enum
		{
			kUnknown         = 0, // not used
			kDefaultView     = 1, // open in last saved view
			kLayoutName      = 2, // specify layout by name
			kViewName        = 3, // specify view by name
			kLayoutHandle    = 4, // specify layout by ncdb handle
			kViewHandle      = 5, // specify view by ncdb handle
			kViewWorldCoords = 6
		};

		BYTE mnInitialViewType;

		enum
		{
			kDisallowReadOnly     = 0x01,
			kRequireReadOnly      = 0x02,
			kFileNameArgIsUnicode = 0x04,
			kViewNameArgIsUnicode = 0x08,
			kUseUIOnErrors        = 0x10
		};

		int            mnFlags;  // open it as readonly, etc
		const wchar_t* mpwszPassword;
		void*          mpUnused;
		int            mnUnused;
	};

	virtual Nano::ErrorStatus newDocument();
	virtual Nano::ErrorStatus openDocument();
	virtual Nano::ErrorStatus closeDocument(NcApDocument* document);

	virtual int inputPending(NcApDocument* document);

	virtual Nano::ErrorStatus disableDocumentActivation();
	virtual Nano::ErrorStatus enableDocumentActivation();
	virtual bool isDocumentActivationEnabled();

	virtual void executeInApplicationContext(void (*proc)(void*), void* pData) const;

	virtual int documentCount() const;

	virtual void pushResourceHandle(HINSTANCE hNewResourceHandle);
	virtual void pushNcadResourceHandle();
	virtual void popResourceHandle();

	virtual Nano::ErrorStatus sendModelessInterrupt(NcApDocument* document);

public:
	inline HostApDocManager* native() const
	{
		return (HostApDocManager*)m_pNative;
	}

protected:
	NcArray< HINSTANCE > m_PushRHandles;
	mutable bool m_bFakeAppContextMark;
};

NRXDBGATE_EXPORT NcApDocManager* ncDocManagerPtr();
#define ncDocManager  ncDocManagerPtr()

inline NcApDocument* curDoc()
{
	return ::ncDocManager->curDocument();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// NcAxDocLock
class NRXDBGATE_EXPORT NcAxDocLock
{
public:
	enum DocLockType
	{
		kNormal       = 0,
		kCurDocSwitch = 1
	};

public:
	NcAxDocLock();
	NcAxDocLock(const NcDbObjectId& id, DocLockType type = kNormal);
	NcAxDocLock(NcDbDatabase* database, DocLockType type = kNormal);

	~NcAxDocLock();

public:
	Nano::ErrorStatus lockStatus() const;

protected:
	Nano::ErrorStatus lock();
	Nano::ErrorStatus lock(NcDbDatabase* database, DocLockType type);

protected:
	Nano::ErrorStatus m_LockStatus;

	void*             m_pLockedDocument;
	void*             m_pDocumentToRestore;

	bool              m_Restore;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
// NcApDataManager
template < class T > class NcApDataManager : public NcApDocManagerReactor
{

public:
	NcApDataManager()
	{
		ncDocManager->addReactor(this);
	}
	~NcApDataManager()
	{
		if (ncDocManager != NULL)
			ncDocManager->removeReactor(this);
	}
	virtual void documentToBeDestroyed(NcApDocument* pDoc)
	{
		m_dataMap.erase(pDoc);
	}

	T& docData(NcApDocument* pDoc)
	{
		std::map< NcApDocument*, T >::iterator i = m_dataMap.find(pDoc);
		if (i == m_dataMap.end())
			return (m_dataMap[pDoc]);

		return ((*i).second);
	}
	T& docData()
	{
		return (docData(ncDocManager->curDocument()));
	}

private:
	std::map< NcApDocument*, T > m_dataMap;
};


#endif // __OPENDWGDOCMGR_H__


