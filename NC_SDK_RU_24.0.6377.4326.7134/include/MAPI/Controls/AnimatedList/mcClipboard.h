#pragma once


#define CF_CXAL_CONTROL   _T("CXAL Control")          // HWND of source CxAnimatedListSimple
#define CF_CXAL_DATA		  _T("CXAL Items and Nodes")  // xml string with node and items being dragged
#define CF_ACAD_FILENAME  _T("AutoCAD.r17")
#define CF_NANO_FILENAME  _T("F04DEAEF-0ECC-4d35-B05D-1790ABFFB4BC")


struct AFX_DATACACHE_ENTRY
{
	FORMATETC m_formatEtc;
	STGMEDIUM m_stgMedium;
	DATADIR m_nDataDir;
};



//////////////////////////////////////////////////////////////////////////
struct McDataObject : public IDataObject
{
	// IUnknown
	STDMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();

	// IDataObject
	STDMETHOD(GetData)(/* [unique][in] */ FORMATETC *pformatetcIn, /* [out] */ STGMEDIUM *pmedium);
	STDMETHOD(GetDataHere)(/* [unique][in] */ FORMATETC *pformatetc, /* [out][in] */ STGMEDIUM *pmedium);
	STDMETHOD(QueryGetData)(/* [unique][in] */ FORMATETC *pformatetc);
	STDMETHOD(GetCanonicalFormatEtc)(/* [unique][in] */ FORMATETC *pformatectIn, /* [out] */ FORMATETC *pformatetcOut);
	STDMETHOD(SetData)(/* [unique][in] */ FORMATETC *pformatetc, /* [unique][in] */ STGMEDIUM *pmedium, /* [in] */ BOOL fRelease);
	STDMETHOD(EnumFormatEtc)(/* [in] */ DWORD dwDirection, /* [out] */ IEnumFORMATETC **ppenumFormatEtc);
	STDMETHOD(DAdvise)(/* [in] */ FORMATETC *pformatetc, /* [in] */ DWORD advf, /* [unique][in] */ IAdviseSink *pAdvSink, /* [out] */ DWORD *pdwConnection);
	STDMETHOD(DUnadvise)(/* [in] */ DWORD dwConnection);
	STDMETHOD(EnumDAdvise)(/* [out] */ IEnumSTATDATA **ppenumAdvise);

	// McDataSource
	HRESULT CopyToClipboard();
	HRESULT AttachClipboard();
	HRESULT Empty();
	HRESULT SetGlobalData(CLIPFORMAT cf, LPVOID lpvData, size_t cbSize);
	static HRESULT GetGlobalData(IDataObject* pData, CLIPFORMAT cf, LPVOID lpbRes, IN OUT size_t* pcbSize);
	static HRESULT GetGlobalData(IDataObject* pData, CLIPFORMAT cf, mcsByteArray& ba);

	McDataObject();
	virtual ~McDataObject() { Empty(); }

	// CxAnimationList specific helpers
/*
	static HRESULT    CXAL_IsValid();
*/
	static HWND       CXAL_GetWindow(IDataObject* pData);
	HRESULT           CXAL_SetWindow(HWND hwnd);
	static McsStringW CXAL_GetData(IDataObject* pData);
	HRESULT           CXAL_SetData(McsStringW swXml);
	static HRESULT    CXAL_GetFiles(IDataObject* pData, mcsStringArray& msRes);

private:
	ULONG m_lRefCount;
	McsArray<AFX_DATACACHE_ENTRY, const AFX_DATACACHE_ENTRY&> m_pDataCache;

	AFX_DATACACHE_ENTRY* Lookup(LPFORMATETC lpFormatEtc, DATADIR nDataDir);
	AFX_DATACACHE_ENTRY* GetCacheEntry(LPFORMATETC lpFormatEtc, DATADIR nDataDir);

	BOOL OnRenderData(LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium);
};


/*
struct DragDropHelper
{
	HRESULT DoDragDrop(HWND hSource, McsStringW swXml, IDropTarget* pdt = NULL);
	HRESULT DragEnter();

	DWORD m_dwAllowedEffects;
	bool m_fSameWindow;
	HWND m_hWnd;
};
*/


//////////////////////////////////////////////////////////////////////////
struct CxAnimatedListSimple;
struct CxListDropTarget : public IDropTarget
{
	// IUnknown
	ULONG STDMETHODCALLTYPE AddRef() { return 2; }
	ULONG STDMETHODCALLTYPE Release() { return 1; }
	STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

	// IDropTarget
	STDMETHOD(DragEnter)(IN IDataObject* pData, IN DWORD dwKeyState, IN POINTL pt, IN OUT DWORD* pdwEffects);
	STDMETHOD(DragOver)(IN DWORD grfKeyState, IN POINTL pt, IN OUT DWORD* pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IN IDataObject* pDataObj, IN DWORD grfKeyState, IN POINTL pt, IN OUT DWORD* pdwEffect);

	// CxListDropTarget
	CxListDropTarget() : m_pWnd(NULL), m_dfxEnabled(DROPEFFECT_COPY), m_fSameWindow(false), m_fNode(false) {}

	HRESULT ReadFromXML(DWORD dwEffects);
	HRESULT ReadItems(MSXML2::IXMLDOMDocumentPtr pxDoc, int iIns, mcsIntArray* pImages);
	HRESULT ReadSingleNode(MSXML2::IXMLDOMElementPtr &pxNode, mcsIntArray* pImages);

	CxAnimatedListSimple* m_pWnd;        // drag-drop client

	DROPEFFECT m_dfxEnabled;       // allowed drop effects depending on data type

	// data containers
	McsStringW m_swXML;            // xml items
	mcsStringArray m_msFiles;      // paths to files being dragged
	bool m_fSameWindow;            // drag source is m_pWnd
	bool m_fNode;                  // drop data is a node
	
#ifdef DI_GETDRAGIMAGE
	CComQIPtr<IDropTargetHelper, &IID_IDropTargetHelper> m_pDropPainter;
#endif

	void SetDropEffect(DWORD dwKeys, LPDWORD lpdw);
	static int XmlReplaceIDs(MSXML2::IXMLDOMNode* pxNode);
};


//////////////////////////////////////////////////////////////////////////
struct CxListDropSource : public IDropSource
{
	// IUnknown
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	STDMETHOD(QueryInterface)(REFIID riid, void** ppv);

	// IDropSource
	STDMETHOD(QueryContinueDrag)(IN BOOL fEscapePressed, IN DWORD dwKeyState);
	STDMETHOD(GiveFeedback)(IN DWORD dwEffects);

	// CxListDropSource
	CxListDropSource() : m_ulCount(1), m_hWnd(NULL), m_dw(0) {}

	HWND m_hWnd;

private:
	ULONG m_ulCount;
	DWORD m_dw;
};


