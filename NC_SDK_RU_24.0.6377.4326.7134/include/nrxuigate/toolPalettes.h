#pragma once

//#ifdef _NCAD_WINDOWS_
//#ifndef NC_DO_NO_IMPORT
//	#pragma warning (push)
//	#pragma warning(disable : 4279)
//	#import "msxml6.dll" named_guids rename_namespace("MSXML") rename("offset", "MSXMLoffset")
//	#pragma warning (pop)
//#else // NC_DO_NO_IMPORT
//	#include "msxml6.tlh"
//#endif
//#endif // _NCAD_WINDOWS_

//using namespace MSXML;

#include <atlcom.h>

class ClipboardInfo;
class InanoCADToolProperties;
class NcTcCatalog;
class NcTcCatalogItem;
class NcTcCatalogItemReactor;
class NcTcCatalogSet;
class NcTcPackage;
class NcTcPalette;
class NcTcScheme;
class NcTcStockTool;
class NcTcTool;
class CNcTcUiImpCatalogView;
class CNcTcUiCatalogView;
class CNcTcUiCatalogViewItem;
class CNcTcUiToolPalette;
class CNcTcUiToolPaletteSet;
class CNcTcUiScheme;
class NcTcUiSystemInternals;
struct PER_PROP_DISP_ENTRY;

typedef CTypedPtrArray<CPtrArray, CNcTcUiCatalogViewItem*> CNcTcUiCatalogViewItemArray;

typedef CTypedPtrArray<CPtrArray, NcTcCatalogItem*> NcTcCatalogItemArray;
BOOL NcTcUiFilterShapesDialog(NcTcCatalogItem* pPackage,
                              NcTcCatalogItemArray* pActiveShapes,
                              NcTcTool*& pCurrentShape,
                              CWnd* pParentWnd);

typedef CTypedPtrArray<CPtrArray, NcTcCatalogItem*> NcTcCatalogItemArray;
typedef CTypedPtrArray<CPtrArray, NcTcStockTool*>   NcTcStockToolArray;
typedef CTypedPtrArray<CPtrArray, NcTcCatalog*>     NcTcCatalogArray;
typedef CTypedPtrArray<CPtrArray, CNcTcUiToolPaletteSet*> NcTcUiToolPaletteSetArray;
typedef CTypedPtrArray<CPtrArray, CNcTcUiToolPalette*> NcTcUiToolPaletteArray;
typedef CTypedPtrArray<CPtrArray, CNcTcUiCatalogView*> NcTcUiCatalogViewArray;

struct PER_PROP_DISP_ENTRY2
{
	DISPID    m_dispid;
	LPCWSTR   m_ProgID;
	LPCWSTR   m_lpLeftIconRes;
	UINT      m_nLeftIconType;
	LPCWSTR   m_lpEllipsisBmpRes;
	UINT      m_nEllipsisBmpType;
	COLORREF  m_TextColor;
	bool      m_bFullView;
	DWORD     m_dwIntegralHeight;
	long      m_nWeight;
};

#define BEGIN_PERPROPDISPLAY_MAP2()                                                            \
    static PER_PROP_DISP_ENTRY2* GetPerPropDisplayArray2()                                    \
    {                                                                                        \
        static PER_PROP_DISP_ENTRY2 pPerPropDisplayArray[] =                                 \
        {
                                                                                            
#define PROP_DISP_ENTRY2(dispid, progid, lpLeftIconRes, lpLeftIconType,                        \
    lpEllipsisBmpRes, lpEllipsisBmpType, textcolor,                                          \
    bFullView, dwIntegralHeight, nWeight)                                                    \
        {dispid, progid, lpLeftIconRes, lpLeftIconType, lpEllipsisBmpRes,                    \
        lpEllipsisBmpType, textcolor, bFullView,                                             \
        dwIntegralHeight, nWeight},                                                            \
                                                                                            
#define END_PERPROPDISPLAY_MAP2()                                                            \
        {-1, NULL, NULL, PICTYPE_UNINITIALIZED, NULL, PICTYPE_UNINITIALIZED, 0x80000008, false, -1, -1}\
        };                                                                                    \
        return pPerPropDisplayArray;                                                        \
    }

struct PER_FLYOUT_ENTRY
{
	DISPID    dispid;
};

#define BEGIN_FLYOUT_SPECIFIC_MAP()\
    static PER_FLYOUT_ENTRY* GetFlyoutMap()\
    {\
        static PER_FLYOUT_ENTRY pFlyoutEntry[]=\
        {

#define FLYOUT_ENTRY(dispid)\
            {dispid},

#define END_FLYOUT_SPECIFIC_MAP()\
            {-1}\
        };\
        return pFlyoutEntry;\
    }

static void *pNcadToolImpl=NULL;

template <class TT,class T,const CLSID* pclsid,LPCWSTR szToolName,LPCWSTR szToolImage,const IID* piid = &__uuidof(T),const GUID* plibid = &CAtlModule::m_libid>
class ATL_NO_VTABLE NcadToolImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<T, piid, plibid, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	//public InanoCADTool,
	//public InanoCADTool2,
	//public InanoCADStockTool,
	public IDropTarget,
	//public IPropertyUnspecified,
	//public IPerPropertyDisplayImpl<NcadToolImpl<TT,T,pclsid,szToolName,szToolImage,piid,plibid> >,
	public IOPMPropertyExtension,
	//public InanoCADToolContextMenu,
	public IPerPropertyBrowsing,
	public IOPMPropertyDialog
	//public InanoCADToolFlyoutShape
{
public:

	NcadToolImpl()
	{
		//ReportNotImplementedByNrx3Gate(NcadToolImpl::NcadToolImpl);
	}
	~NcadToolImpl()
	{
		//ReportNotImplementedByNrx3Gate(NcadToolImpl::~NcadToolImpl);
	}

	static PER_PROP_DISP_ENTRY* GetPerPropDisplayArray()
	{
		ReportNotImplementedByNrx3Gate(NcadToolImpl::GetPerPropDisplayArray);
		return NULL;
	}

BEGIN_COM_MAP(NcadToolImpl)
	COM_INTERFACE_ENTRY(T)
	COM_INTERFACE_ENTRY(IDispatch)
	//COM_INTERFACE_ENTRY(InanoCADTool)
	//COM_INTERFACE_ENTRY(InanoCADStockTool)
	COM_INTERFACE_ENTRY(IDropTarget)
	//COM_INTERFACE_ENTRY(IPropertyUnspecified)
	//COM_INTERFACE_ENTRY(IPerPropertyDisplay)
	//COM_INTERFACE_ENTRY(IOPMPropertyExtension)
	//COM_INTERFACE_ENTRY(InanoCADToolContextMenu)
	//COM_INTERFACE_ENTRY(IPerPropertyBrowsing)
	//COM_INTERFACE_ENTRY(IOPMPropertyDialog)
	//COM_INTERFACE_ENTRY(InanoCADToolFlyoutShape)
END_COM_MAP()

protected:
	//HWND m_hPreviewWnd;
	//BOOL m_bColorUnspecified,m_bLayerUnspecified;

	struct TOOL_MAP_ENTRY
	{
		WCHAR szDesc[512];
		DISPID dispId;
	};
	//NcArray<TOOL_MAP_ENTRY> m_ToolMap;
	//CLIPFORMAT mcfAutoCAD;

public:

public:
	STDMETHOD(CreateTool) (/*[out, retval]*/ IUnknown** ppTool)
	{
		return E_NOTIMPL;
	}

public:
	STDMETHOD(get_EditMode) (/*[out, retval]*/ long* pVal)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetStockTool) (/*[out, retval]*/ IUnknown** ppToolClass)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Load) (/*[in]*/ IUnknown* pXmlElement)
	{
		return E_NOTIMPL;
	} 

	STDMETHOD(LoadFromFlyout)(IUnknown* pXmlElement)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Save) (/*[in]*/ IUnknown* pXmlElement)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(executeCallback)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(dropCallback)(NcDbEntity *pEntity)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Execute) (/*[in]*/ LONG_PTR lFlag, /*[in]*/ DWORD_PTR /*HWND*/ hWnd, /*[in]*/ DWORD point, /*[in]*/ DWORD dwKeyState)
	{
		return E_NOTIMPL;
	}

	BOOL GetFlyoutTool(NcTcTool*& pFlyoutTool)
	{
		ReportNotImplementedAPI(L"GetFlyoutTool");
		return TRUE;
	}

	STDMETHOD(GetData) (/*[in]*/ VARIANT *pObjUnkArray, /*[in]*/ VARIANT *pDynUnkArray)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(BeginEdit) ()
	{
		return E_NOTIMPL;
	}
	STDMETHOD (Edit) (/*[in]*/ IUnknown* pProp,/*[in]*/ LONG_PTR /*HWND*/ hWndParent, /*[out]*/ VARIANT_BOOL* pRet) 
	{
		return E_NOTIMPL;
	}
	STDMETHOD (EndEdit)(/*[in]*/ VARIANT_BOOL bEditCancelled)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (Dropped)(/*[in]*/ BSTR bstrUrl)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetDropTarget) (/*[out, retval]*/ IUnknown** ppDropTarget)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (Refreshed)(/*[in]*/ BSTR bstrUrl)
	{
		return E_NOTIMPL;
	}
	STDMETHOD (SetEditorWindow)(/*[in]*/ LONG_PTR /*HWND*/ hWndEditor, /*[in]*/ IUnknown*    pPropInspector)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (ValidateEditChanges)()
	{
		return E_NOTIMPL;
	}

	STDMETHOD(SetToolProperties) (/*[in]*/ IUnknown* pProp)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (GetToolProperties)(/*[out, retval]*/ IUnknown** pToolProp)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(New) ()
	{
		return E_NOTIMPL;
	}

	STDMETHOD(UpdateImage)(void)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetContextMenu) (/*[in]*/ INT_PTR nContextFlag, /*[in]*/ DWORD_PTR /*HMENU*/ hMenu, /*[in]*/ UINT idCmdFirst,/*[in]*/  UINT idCmdLast, /*[out, retval]*/ DWORD_PTR* pFlag)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetCommandString) (/*[in]*/ UINT idCmd, /*[out, retval]*/BSTR* pbstrHelpText)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(InvokeCommand) (/*[in]*/ UINT idCmd, /*[in]*/ DWORD_PTR /*HWND*/ hWnd)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetDragDropContextInfo) (/*[in]*/ IUnknown*    pIUnknown, /*[out]*/BSTR* pbstrText, /*[out]*/ DWORD* pFlag)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(BeginMultipleEdit) (/*[in]*/ VARIANT tools, 
	                              /*[in]*/ VARIANT stockToolIds)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(EndMultipleEdit) (/*[in]*/ VARIANT tools, 
	                            /*[in]*/ VARIANT stockToolIds,
	                            /*[in]*/ VARIANT_BOOL bEditCancelled)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (MultipleEdit) (/*[in]*/ VARIANT tools,
	                          /*[in]*/ VARIANT stockToolIds, 
	                          /*[in]*/ LONG_PTR /*HWND*/ hWndParent, 
	                          /*[out]*/ VARIANT_BOOL* pRet)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Customize)(/* [in] */ int nContextFlag,
	                        /* [in] */ DWORD_PTR hMenu,
	                        /* [in] */ UINT idCmdFirst,
	                    /* [in] */ UINT idCmdLast,
	                    /* [in] */ GUID *pPaletteId,
	                    /* [retval][out] */ DWORD *pFlag)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetMenuHelp)( /* [in] */ UINT idCmd,
	                        /* [retval][out] */ BSTR *pbstrHelpText)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(InvokeMenuCommand)(/* [in] */ UINT idCmd,
	                             /* [in] */ GUID *pPaletteId,
	                             /* [in] */ DWORD_PTR hWnd,
	                             /* [retval][out] */ DWORD *pFlag)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(DragEnter) (/*[unique][in]*/ IDataObject __RPC_FAR *pDataObj, /*[in]*/ DWORD grfKeyState, /*[in]*/ POINTL pt, /*[out][in]*/ DWORD __RPC_FAR *pdwEffect)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(DragOver) (/*[in]*/ DWORD grfKeyState, /*[in]*/ POINTL pt, /*[out][in]*/ DWORD __RPC_FAR *pdwEffect)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(DragLeave) (void)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(Drop) (/*[unique][in]*/ IDataObject __RPC_FAR *pDataObj, /*[in]*/ DWORD grfKeyState, /*[in]*/ POINTL pt, /*[out][in]*/ DWORD __RPC_FAR *pdwEffect)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (IsValueUnspecified)(/*[in]*/ VARIANT varId, /*[out]*/ VARIANT_BOOL *pVal)
	{
		return E_NOTIMPL;
	}
	STDMETHOD (SetUnspecified)(/*[in]*/ VARIANT varId, /*[in]*/ VARIANT_BOOL bIsUnspecified)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (IsUnspecifiedAllowed)(/*[in]*/ VARIANT varId, /*[out]*/ VARIANT_BOOL *pVal)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (GetUnspecifiedString)(VARIANT,BSTR *str)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetEllipsisBitMap) ( 
	    /* [in] */ VARIANT varId,
	    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *pBitMap)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetPropHelpProc) ( 
	    /* [in] */ VARIANT varId,
	    /* [out] */ LONG __RPC_FAR *pHelpProc)
	{
		return E_NOTIMPL;
	}

	BOOL GetClipInfo(COleDataObject* pDataObject, ClipboardInfo* pClipboardInfo)
	{
		ReportNotImplementedAPI(L"GetClipInfo");
		return FALSE;
	}

	virtual HRESULT GetPropertyTypeInfo()
	{
		ReportNotImplementedAPI(L"GetPropertyTypeInfo");
		return E_NOTIMPL;
	}

	HRESULT PutToolProperty(int index,VARIANT vValue)
	{
		ReportNotImplementedAPI(L"PutToolProperty");
		return E_NOTIMPL;
	}

	HRESULT GetToolProperty(int index,VARIANT& vValue)
	{
		ReportNotImplementedAPI(L"GetToolProperty");
		return E_NOTIMPL;
	}

	STDMETHOD(GetDisplayString)(DISPID dispID,BSTR *pbstr)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(MapPropertyToPage)(DISPID dispID,CLSID *pCLSID)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetPredefinedStrings)(DISPID dispID,CALPOLESTR *pcaStringsOut,CADWORD *pcaCookiesOut)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetPredefinedValue)(DISPID dispID,DWORD dwCookie,VARIANT *pVarOut)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(DoModal)(BSTR* propValueString,NcDbObjectIdArray* ObjectIdArray)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(SetFlyoutTools) (/* [in] */ VARIANT* pFlyoutToolIds)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Editable)(DISPID dispID,BOOL __RPC_FAR * bEditable)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetDisplayName)(DISPID dispID,BSTR * propName)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(ShowProperty)(DISPID dispID,BOOL * pShow)
	{
		return E_NOTIMPL;
	}

	BOOL GuidFromString(LPWSTR pszGuid, GUID& id)
	{
		ReportNotImplementedAPI(L"GuidFromString");
		return FALSE;
	}

	CComBSTR StringFromGuid(const GUID& id)
	{
		ReportNotImplementedAPI(L"StringFromGuid");
		return L"";
	}

	STDMETHOD (get_Color)(VARIANT *pVar)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (put_Color)(VARIANT pVar)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (get_Layer)(BSTR* pVal)
	{
		return E_NOTIMPL;
	}

	STDMETHOD (put_Layer)(BSTR newVal)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(put_Flyout)(BSTR var)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(get_Flyout)(BSTR *pVar)
	{
		return E_NOTIMPL;
	}

	BOOL GetUnknownArrays(int nCount, 
	                    IUnknown** pObjUnkArray, 
	                    VARIANT* pStatUnkArray, 
	                    VARIANT* pDynPMUnkArrays)
	{
		ReportNotImplementedAPI(L"GetUnknownArrays");
		return FALSE;
	}

	//BOOL GetAttribute(MSXML::IXMLDOMNode* pNode, 
	//                LPCWSTR pszAttName, 
	//                MSXML::IXMLDOMAttribute** ppChild)
	//{
	//    ReportNotImplementedAPI(L"GetAttribute");
	//    return FALSE;
	//}

	//BOOL GetChildNode(MSXML::IXMLDOMNode* pNode, 
	//                LPCWSTR pszNodeName, 
	//                MSXML::IXMLDOMNode** ppChild)
	//{
	//    ReportNotImplementedAPI(L"GetChildNode");
	//    return FALSE;
	//}

	//BOOL GetChildNodeValue(MSXML::IXMLDOMNode* pNode, 
	//                    LPCWSTR pszNodeName, 
	//                    LPWSTR pszValue)
	//{
	//    ReportNotImplementedAPI(L"GetChildNodeValue");
	//    return FALSE;
	//}

	//BOOL AddChildNode(MSXML::IXMLDOMNode* pNode, 
	//            LPCWSTR pszChildNodeName,
	//            short nNodeType,
	//            MSXML::IXMLDOMNode** ppChild
	//            )
	//{
	//    ReportNotImplementedAPI(L"AddChildNode");
	//    return FALSE;
	//}

	//BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode,
	                         //                    LPCWSTR pszAttName,
	                         //                    VARIANT& var)
	//{
	//    ReportNotImplementedAPI(L"GetAttributeValue");
	//    return FALSE;
	//}

	//BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
	//                    LPCWSTR pszAttName, 
	//                    long& lValue)
	//{
	//    ReportNotImplementedAPI(L"GetAttributeValue");
	//    return FALSE;
	//}

	//BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
	//                    LPCWSTR pszAttName, 
	//                    LPWSTR pszValue)
	//{
	//    ReportNotImplementedAPI(L"GetAttributeValue");
	//    return FALSE;
	//}

	//BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
	//                    LPCWSTR pszAttName, 
	//    short& sValue)
	//{
	//    ReportNotImplementedAPI(L"GetAttributeValue");
	//    return FALSE;
	//}

	//BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
	//    LPCWSTR pszAttName, 
	//                    double& fValue)
	//{
	//    ReportNotImplementedAPI(L"GetAttributeValue");
	//    return FALSE;
	//}

	//inline BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
	//                            LPCWSTR pszAttName, 
	//                            double fValue)
	//{
	//    ReportNotImplementedAPI(L"SetAttributeValue");
	//    return FALSE;
	//}

	//virtual BOOL LoadPropertyValue(MSXML::IXMLDOMNode* pNode, 
	//                            int index)
	//{
	//    ReportNotImplementedAPI(L"LoadPropertyValue");
	//    return FALSE;
	//}

	//virtual BOOL SavePropertyValue(MSXML::IXMLDOMNode* pNode,
	                                 //                            int index)
	//{
	//	ReportNotImplementedAPI(L"SavePropertyValue");
	//	return FALSE;
	//}

	//BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
	//                            LPCWSTR pszAttName, 
	//                            long lValue)
	//{
	//    ReportNotImplementedAPI(L"SetAttributeValue");
	//    return FALSE;
	//}

	//BOOL SetAttributeValue(MSXML::IXMLDOMNode *pNode,
	                         //                            LPCWSTR pszAttName,
	                         //                            VARIANT& var)
	//{
	//    ReportNotImplementedAPI(L"SetAttributeValue");
	//    return FALSE;
	//}

	//BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
	//                            LPCWSTR pszAttName, 
	//                            LPWSTR pszValue)
	//{
	//    ReportNotImplementedAPI(L"SetAttributeValue");
	//    return FALSE;
	//}

	//BOOL RemoveChildren(MSXML::IXMLDOMNode* pNode)
	//{
	//    ReportNotImplementedAPI(L"RemoveChildren");
	//    return FALSE;
	//}

	NcTcPalette *CreatePaletteATC(NcTcCatalog *pCatalog,LPWSTR szPaletteName)
	{
		ReportNotImplementedAPI(L"CreatePaletteATC");
		return NULL;
	}

	NcTcTool *CreateToolATC(NcTcPackage *pPalette, LPCWSTR szToolNameOverride=NULL, 
	    LPCWSTR szToolImageOverride=NULL,
	    BOOL bImageFile=FALSE)
	{
		ReportNotImplementedAPI(L"CreateToolATC");
		return NULL;
	}

	NcTcTool *CreateFlyoutToolATC(NcTcPackage *pPalette, NcTcPackage *pShapePackage, LPCWSTR szToolNameOverride=NULL)
	{
		ReportNotImplementedAPI(L"CreateFlyoutToolATC");
		return NULL;
	}

	NcTcTool *CreateCommandToolATC(NcTcPackage *pPalette,LPWSTR szToolName,LPCWSTR szBitmapName, LPWSTR macroString)
	{
		ReportNotImplementedAPI(L"CreateCommandToolATC");
		return NULL;
	}

	NcTcCatalog *CreateStockToolATC(LPWSTR szCatalogName)
	{
		ReportNotImplementedAPI(L"CreateStockToolATC");
		return NULL;
	}

	NcTcPackage *CreateShapeCatalogATC(LPWSTR szShapeName)
	{
		ReportNotImplementedAPI(L"CreateShapeCatalogATC");
		return NULL;
	}

	InanoCADToolProperties* GetThisToolsProperties()
	{
		ReportNotImplementedAPI(L"GetThisToolsProperties");
		return NULL;
	}

	NcTcPackage* GetCustomShapePackage(NcTcCatalog *pCatalog, LPCWSTR szPackageName)
	{
		ReportNotImplementedAPI(L"GetCustomShapePackage");
		return NULL;
	}
	NcTcPackage* GetCustomShapePackage(NcTcCatalog *pCatalog, GUID szPackageID)
	{
		ReportNotImplementedAPI(L"GetCustomShapePackage");
		return NULL;
	}
};

#define NCTC_IMAGE_NORMAL                   (0x1 << 0)
#define NCTC_IMAGE_SELECTED                 (0x1 << 1)
#define NCTC_IMAGE_HALO                     (0x1 << 2)
#define NCTC_IMAGE_SHADOW                   (0x1 << 3)

#define NCTC_MAX_CATALOG_ITEM_NAME          256
#define NCTC_MAX_CATALOG_ITEM_DESCRIPTION   2048
#define NCTC_MAX_CATALOG_ITEM_KEYWORDS      1024
#define NCTC_MAX_CATALOG_ITEM_TOOLTIP_TEXT  1024
#define NCTC_MAX_CATALOG_ITEM_LINK_NAME     256
#define NCTC_MAX_SCHEME_NAME                256
#define NCTC_MAX_TOOL_NAME                  NCTC_MAX_CATALOG_ITEM_NAME
#define NCTC_MAX_STOCKTOOL_NAME             NCTC_MAX_CATALOG_ITEM_NAME
#define NCTC_MAX_PALETTE_NAME               NCTC_MAX_CATALOG_ITEM_NAME
#define NCTC_MAX_PACKAGE_NAME               NCTC_MAX_CATALOG_ITEM_NAME
#define NCTC_MAX_CATEGORY_NAME              NCTC_MAX_CATALOG_ITEM_NAME
#define NCTC_MAX_CATALOG_NAME               NCTC_MAX_CATALOG_ITEM_NAME
#define NCTC_MAX_URL                        1024
#define NCTC_MAX_PATH                       MAX_PATH
#define NCTC_MAX_COMMAND_NAME               256
#define NCTC_MAX_COMMAND_ARGS               1024
#define NCTC_MAX_HELPINFO_FILE              NCTC_MAX_URL
#define NCTC_MAX_HELPINFO_COMMAND           256
#define NCTC_MAX_HELPINFO_DATA              NCTC_MAX_URL
#define NCTC_MAX_PARENT_DOCUMENT_NAME       256
#define NCTC_MAX_PUBLISHER_NAME             256
#define NCTC_MAX_PRODUCT_NAME               256
#define NCTC_MAX_LOCALE                     512

#define NCTC_POSTDOWNLOADCMD_EXECUTE        ACRX_T(/*MSGO*/"Execute")

#define NCTC_DEFAULTDIR_IMAGE               ACRX_T(/*MSGO*/"Images")
#define NCTC_DEFAULTFILE_IMAGE              ACRX_T(/*MSGO*/"Image")

namespace NcTc
{
	enum AccessRight {
		kAccessRead             = (0x1 << 0),
		kAccessReadWrite        = (0x1 << 1),
		kAccessReadOnlyFile     = (0x1 << 2),
		kAccessMultiple         = (0x1 << 3),
		kAccessNewerVersion     = (0x1 << 4),
	};
	enum CatalogItemType {
		kItemUnknown            = 0,
		kItemTool               = (0x1 << 0),
		kItemPackage            = (0x1 << 1),
		kItemPalette            = (0x1 << 2),
		kItemCategory           = (0x1 << 3),
		kItemCatalog            = (0x1 << 4),
		kItemStockTool          = (0x1 << 5),
	};
	enum ReferencePath {
		kLoadRefPath            = 1,
		kSaveRefPath            = 2,
	};
	enum ImageType {
		kImageTypeUninitialized = -1,
		kImageTypeBitmap        = 1,
		kImageTypeMetaFile      = 2,
		kImageTypeIcon          = 3,
		kImageTypeEnhMetaFile   = 4,
		kImageTypeJpeg          = 5,
		kImageTypePng           = 6,
		kImageTypeGif           = 7,
		kImageTypeTif           = 8
	};
	enum ImageOption {
		kImageOptionNone                = 0x0,
		kImageOptionRenderBitmapOpaque  = (0x1 << 0),
		kImageOptionUserOverride        = (0x1 << 1),
	};
	enum LoadOption {
		kLoadLinks              = (0x1 << 0),
		kLoadImages             = (0x1 << 1),
		kLoadOverlayImages      = (0x1 << 2),
		kDoNotNotifyReactor     = (0x1 << 3),
	};
	enum SaveOption {
		kSaveLinksAsLinks       = (0x1 << 0),
		kSaveLinksAsEmbedded    = (0x1 << 1),
		kSaveImages             = (0x1 << 2),
		kSaveAs                 = (0x1 << 3),
		kSaveOverlayImages      = (0x1 << 4),
		kSaveAnsi               = (0x1 << 5),
	};
	enum DownloadOption {
		kDownloadItem           = (0x1 << 0),
		kDownloadLinkedItem     = (0x1 << 1),
		kDownloadImage          = (0x1 << 2),
		kDownloadStockTool      = (0x1 << 3),
		kDownloadChildren       = (0x1 << 4),
		kDownloadAll            = kDownloadItem | kDownloadLinkedItem |
		                          kDownloadImage | kDownloadStockTool |
		                          kDownloadChildren,
		kDownloadCleanDownloadDir = (0x1 << 5),
		kDownloadShowProgress   = (0x1 << 6),
		kDownloadUseNewIds      = (0x1 << 7),
		kDownloadNotifyTool     = (0x1 << 12)
	};
	enum RefreshOption {
		kRefreshItem            = kDownloadItem,
		kRefreshLinkedItem      = kDownloadLinkedItem,
		kRefreshImage           = kDownloadImage,
		kRefreshStockTool       = kDownloadStockTool,
		kRefreshChildren        = kDownloadChildren,
		kRefreshAll             = kDownloadAll,
		kRefreshShowProgress    = kDownloadShowProgress,
		kRefreshNotifyTool      = (0x1 << 16)
	};
	enum CatalogType {
		kCatalog                = (0x1 << 0),
		kStockToolCatalog       = (0x1 << 1),
		kShapeCatalog           = (0x1 << 2)
	};
	enum ToolType {
		kToolNormal             = 1,
		kToolFlyout             = 2,
		kToolText               = 3,
		kToolSeparator          = 4,
	};
	enum SortOption {
		kSortByName             = (0x1 << 0),
		kSortByStockTool        = (0x1 << 1),
		kSortByCustom           = (0x1 << 2),
		kAscending              = (0x1 << 3),
		kDescending             = (0x1 << 4),
	};
	enum ItemOption {
		kItemOptionNone                 = 0x0,
		kItemOptionSupportsAutoImage    = (0x1 << 0),
		kItemOptionSupportsUserImage    = (0x1 << 1),
		kItemOptionMenuUpdateImage      = (0x1 << 2),
		kItemOptionMenuSetImage         = (0x1 << 3),
		kItemOptionMenuRemoveImage      = (0x1 << 4),
	};
}; // namespace NcTc

struct NCTC_IMAGE_INFO {
	SIZE                mSize;
	NCHAR               mszResourceName[MAX_PATH];
	NCHAR               mszSourceFile[MAX_PATH];
};

using namespace NcTc;

struct NCTC_TARGET_PRODUCT_INFO {
	NCHAR               mszProductName[NCTC_MAX_PRODUCT_NAME];
	NCHAR               mszLocaleIds[NCTC_MAX_LOCALE];
	DWORD               mdwMinVersion;
	DWORD               mdwMaxVersion;
};

//////////////////////////////////////////////////////////////////////////
// NcTcImage
class THUNK_NATIVE_API NcTcImage {
public:
	NcTcImage();
	NcTcImage(const NcTcImage& srcImage);
	virtual ~NcTcImage();
	NcTcImage&          operator=           (const NcTcImage& ncTcImage);
	BOOL                Load                (LPCTSTR pszFile);
	BOOL                Load                (HBITMAP hBitmap);
	BOOL                Load                (IStream* pStream);
	BOOL                Save                (LPCTSTR pszFile);
	BOOL                Save                (LPCTSTR sFileName,
	                                         NcTc::ImageType nSaveAsType);
	BOOL                Save                (IStream* pStream);
	BOOL                Render              (HDC hDC,
	                                         int xPos,
	                                         int yPos,
	                                         int nWidth,
	                                         int nHeight,
	                                         UINT nStyle = NCTC_IMAGE_NORMAL,
	                                         BOOL bTransparentBitmap = TRUE);
	BOOL                GetSize             (LPSIZE pSize) const;
	NcTc::ImageType     GetType             (void) const;
	BOOL                IsImageLoaded       (void) const;
	BOOL                GetHICON            (HICON &hIcon);
	BOOL                GetHBITMAP          (COLORREF cBackGroundColor,
	                                         HBITMAP& hBitmap);
	NcTc::ImageType     GetSaveType         (void) const;
	BOOL                SetSaveType         (NcTc::ImageType nSaveType);
	BOOL                ConvertTo           (NcTc::ImageType nToImageType,
	                                         BOOL bTransparent);
private:
	friend class NcTcSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcTcImageList
class THUNK_NATIVE_API NcTcImageList {
public:
	virtual ~NcTcImageList();
	NcTcImageList&      operator=           (const NcTcImageList& ncTcImageList);
	INT_PTR             GetImageCount       (void) const;
	BOOL                GetImageInfo        (INT_PTR iIndex,
	                                         NCTC_IMAGE_INFO* pImageInfo) const;
	BOOL                SetImageInfo        (INT_PTR iIndex,
	                                         const NCTC_IMAGE_INFO* pImageInfo);
	NcTcImage*          GetImage            (INT_PTR iIndex);
	INT_PTR             SetImage            (INT_PTR iIndex,
	                                         const NcTcImage* pImage);
	INT_PTR             Add                 (const NcTcImage* pImage);
	INT_PTR             Add                 (const NCTC_IMAGE_INFO* pImageInfo);
	INT_PTR             UpdateImage         (const NcTcImage* pImage);
	BOOL                Delete              (INT_PTR iIndex);
	BOOL                DeleteAllImages     (void);
	BOOL                LoadImage           (INT_PTR iIndex);
	INT_PTR             GetImageIndex       (const SIZE* pSize,
	                                         BOOL bExactMatch = FALSE);
	NcTc::ImageOption   GetOption           (void) const;
	BOOL                SetOption           (NcTc::ImageOption nOption);
protected:
	NcTcImageList(NcTcCatalogItem* pCatalogItem);
private:
	friend class NcTcSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcTcManager
class THUNK_NATIVE_API NcTcManager {
public:
	NcTcManager();
	virtual ~NcTcManager();
	INT_PTR             GetStockToolCatalogCount(void) const;
	NcTcCatalogItem*   GetStockToolCatalog (int nIndex) const;
	NcTcStockTool*   FindStockTool       (const GUID& id) const;
	INT_PTR             GetCatalogCount     (void) const;
	NcTcCatalogItem*   GetCatalog          (int nIndex) const;
	NcTcCatalogItem*   FindItem            (const GUID& id) const;
	int                 GetCatalogPath      (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetCatalogPath      (LPCTSTR pszPath);
	int                 GetStockToolCatalogPath(LPTSTR pszString,
	                                            int cchSize) const;
	BOOL                SetStockToolCatalogPath(LPCTSTR pszPath);
	int                 GetShapeCatalogFile (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetShapeCatalogFile (LPCTSTR pszFile);
	INT_PTR             AddStockToolCatalog (NcTcCatalogItem* pCatalogItem);
	INT_PTR             AddCatalog          (NcTcCatalogItem* pCatalogItem);
	BOOL                LoadCatalogs        (DWORD dwCatalogType= kCatalog | kStockToolCatalog,
	                                         DWORD dwLoadOption = kLoadLinks);
	BOOL                UnloadCatalogs      (DWORD dwCatalogType= kCatalog | kStockToolCatalog);
	BOOL                SaveCatalogs        (DWORD dwCatalogType= kCatalog | kStockToolCatalog,
	                                         DWORD dwSaveOption = kSaveLinksAsLinks);
	NcTcCatalogItem*    GetShapeCatalog     (void);
	NcTcCatalogItem*   GetShapePackage     (LPCTSTR lpszName = NULL) const;
	INT_PTR             InsertStockToolCatalog(INT_PTR nIndex,
	                                           NcTcCatalogItem* pCatalog);
	NcTcCatalogItem*    RemoveStockToolCatalog(int nIndex);
	INT_PTR             GetSchemeCount      (void) const;
	NcTcScheme*   GetScheme           (int nIndex) const;
	NcTcScheme*   GetScheme           (LPCTSTR pszSchemeName) const;
	INT_PTR             AddScheme           (NcTcScheme* pScheme);
	BOOL                RemoveScheme        (NcTcScheme* pScheme);
private:
	friend class NcTcSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcTcScheme
class THUNK_NATIVE_API NcTcScheme {
public:
	NcTcScheme(LPCTSTR pszSchemeName);
	virtual ~NcTcScheme();
	int                 GetName             (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetName             (LPCTSTR pszString);
	NcTcCatalogSet*   GetCatalogSet       (DWORD dwCatalogType) const;
	NcTcCatalogItem*   FindItem            (const GUID& id) const;
	NcTcCatalogItem*   FindItem            (const GUID& id,
	                                        DWORD dwCatalogType) const;
	BOOL                LoadCatalogs        (void);
	BOOL                LoadCatalogs        (DWORD dwCatalogType,
	                                         DWORD dwLoadOption);
	BOOL                UnloadCatalogs      (void);
	BOOL                UnloadCatalogs      (DWORD dwCatalogType);
	BOOL                SaveCatalogs        (void);
	BOOL                SaveCatalogs        (DWORD dwCatalogType,
	                                         DWORD dwSaveOption);
private:
	friend class NcTcSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcTcCatalogSet
class THUNK_NATIVE_API NcTcCatalogSet {
public:
	virtual ~NcTcCatalogSet();
	NcTcScheme*   GetScheme           (void) const;
	INT_PTR             GetCatalogCount     (void) const;
	NcTcCatalogItem*   GetCatalog          (int nIndex) const;
	NcTcCatalogItem*   FindItem            (const GUID& id) const;
	int                 GetCatalogPath      (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetCatalogPath      (LPCTSTR pszPath);
	INT_PTR             AddCatalog          (NcTcCatalogItem* pCatalog);
	INT_PTR             InsertCatalog       (INT_PTR nIndex,
	                                         NcTcCatalogItem* pCatalog);
	NcTcCatalogItem*    RemoveCatalog       (int nIndex);
	BOOL                LoadCatalogs        (void);
	BOOL                LoadCatalogs        (DWORD dwLoadOption);
	BOOL                UnloadCatalogs      (void);
	BOOL                SaveCatalogs        (void);
	BOOL                SaveCatalogs        (DWORD dwSaveOption);
protected:
	NcTcCatalogSet(DWORD dwCatalogType);
private:
	friend class NcTcSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcTcCatalogItem
class THUNK_NATIVE_API NcTcCatalogItem {
public:
	static NcTcCatalogItem* FromFile       (LPCTSTR pszFile,
	                                        BOOL bLoad         = FALSE,
	                                        DWORD dwLoadOption = kLoadLinks);
	static CatalogItemType   GetType        (LPCTSTR pszFile);
public:
	virtual ~NcTcCatalogItem();
	BOOL                Load                (LPCTSTR pszUrl,
	                                         DWORD dwLoadOption = kLoadLinks);
	BOOL                LoadLink            (void);
	BOOL                Save                (LPCTSTR pszUrl,
	                                         DWORD dwSaveOption = kSaveLinksAsLinks);
	INT_PTR             AddChild            (NcTcCatalogItem* pNewItem);
	INT_PTR             InsertChild         (INT_PTR iIndex,
	                                         NcTcCatalogItem* pNewItem);
	BOOL                DeleteChild         (NcTcCatalogItem* pItem);
	BOOL                DetachChild         (NcTcCatalogItem* pItem);
	INT_PTR             GetChildCount       (void) const;
	INT_PTR             GetChildCount       (CatalogItemType nType) const;
	NcTcCatalogItem*   GetChild            (INT_PTR iIndex) const;
	NcTcCatalogItem*   GetNextChild        (int iIndex,
	                                        CatalogItemType nType) const;
	BOOL                DeleteAllChildren   (void);
	BOOL                HasChildren         (void) const;
	BOOL                GetID               (GUID* pId) const;
	BOOL                SetID               (const GUID* pId);
	NcTc::AccessRight   GetAccessRight      (void) const;
	BOOL                SetAccessRight      (NcTc::AccessRight nAccessRight);
	BOOL                IsReadOnly          (void) const;
	int                 GetName             (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetName             (LPCTSTR pszString);
	int                 GetDescription      (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetDescription      (LPCTSTR pszString);
	int                 GetToolTipText      (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetToolTipText      (LPCTSTR pszString);
	INT_PTR             GetImageFilePath    (INT_PTR iIndex,
	                                         LPTSTR pszString,
	                                         size_t cchSize) const;
	BOOL                GetHelpInfo         (LPTSTR pszFile,
	                                         LPTSTR pszCommand,
	                                         LPTSTR pszData) const;
	BOOL                SetHelpInfo         (LPCTSTR pszFile,
	                                         LPCTSTR pszCommand,
	                                         LPCTSTR pszData);
	int                 GetKeywords         (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetKeywords         (LPCTSTR pszString);
	int                 GetLinkUrl          (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetLinkUrl          (LPCTSTR pszString);
	int                 GetSourceUrl        (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetSourceUrl        (LPCTSTR pszString);
	int                 GetParentDocumentName(LPTSTR pszString,
	                                          int cchSize) const;
	BOOL                SetParentDocumentName(LPCTSTR pszString);
	int                 GetParentDocumentDescription(LPTSTR pszString,
	                                                 int cchSize) const;
	BOOL                SetParentDocumentDescription(LPCTSTR pszString);
	int                 GetParentDocumentUrl(LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetParentDocumentUrl(LPCTSTR pszString);
	int                 GetPublisherName    (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetPublisherName    (LPCTSTR pszString);
	int                 GetPublisherDescription(LPTSTR pszString,
	                                            int cchSize) const;
	BOOL                SetPublisherDescription(LPCTSTR pszString);
	int                 GetPublisherCountry (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetPublisherCountry (LPCTSTR pszString);
	int                 GetPublisherEmail   (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetPublisherEmail   (LPCTSTR pszString);
	int                 GetPublisherUrl     (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetPublisherUrl     (LPCTSTR pszString);
	int                 GetUrl              (LPTSTR pszString,
	                                         int cchSize) const;
	int                 GetLocalFile        (LPTSTR pszString,
	                                         int cchSize) const;
	NcTcCatalogItem*   GetRoot             (void) const;
	NcTcScheme*   GetScheme           (void) const;
	NcTcCatalogItem*   GetParent           (void) const;
	BOOL                SetParent           (NcTcCatalogItem* pParent);
	BOOL                IsRoot              (void) const;
	BOOL                IsLink              (void) const;
	BOOL                IsLinkLoaded        (void) const;
	NcTcImageList*   GetImageList        (void) const;
	NcTcImage*   GetImage            (const SIZE* pSize);
	int                 GetXml              (LPTSTR pszString,
	                                         int cchSize,
	                                         DWORD dwSaveOption = kSaveLinksAsLinks);
	virtual NcTcCatalogItem* FindInChildren (const GUID& id,
	                                         BOOL bRecursive = TRUE);
	NcTcCatalogItem*   FindInChildren      (LPCTSTR pszName);
	NcTcCatalogItem*   FindInChildren      (LPCTSTR pszName,
	                                        BOOL bRecursive);
	BOOL                GetTime             (time_t* pCreated,
	                                         time_t* pLastModified,
	                                         time_t* pLastRefreshed) const;
	BOOL                SetTime             (const time_t* pCreated,
	                                         const time_t* pLastModified,
	                                         const time_t* pLastRefreshed);
	BOOL                CanRefresh          (void) const;
	BOOL                SetRefresh          (BOOL bRefresh);
	BOOL                GetRefresh          (void) const;
	virtual BOOL        Refresh             (DWORD dwRefreshFlag    = kRefreshAll);
	virtual BOOL        Download            (LPCTSTR pszUrl,
	                                         DWORD dwDownloadFlag  = kDownloadAll,
	                                         LPCTSTR pszDownloadPath        = NULL);
	BOOL                SetAutoRefresh       (BOOL bAutoRefresh);
	BOOL                GetAutoRefresh      (void) const;
	int                 GetReferencePath    (LPTSTR pszString,
	                                         int cchSize,
	                                         int nFlag) const;
	BOOL                SetReferencePath    (LPCTSTR pszString,
	                                         int nFlag);
	BOOL                GetCustomData       (IUnknown** ppCustomData);
	BOOL                SetNewID            (BOOL bRecursive = FALSE);
	BOOL                DeleteImageFile     (BOOL bRecursive = FALSE);
	int                 GetLinkFilePath     (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                DeleteLinkFile      (BOOL bRecursive = FALSE);
	BOOL                GetSourceID         (GUID* pId) const;
	BOOL                SetSourceID         (const GUID* pId);
	NcTcImage*   GetOverlayImage     (void) const;
	BOOL                SetOverlayImage     (const NcTcImage* pImage);
	BOOL                GetOverlayImageInfo (NCTC_IMAGE_INFO* pImageInfo) const;
	BOOL                SetOverlayImageInfo (const NCTC_IMAGE_INFO* pImageInfo);
	INT_PTR             GetOverlayImageFilePath(LPTSTR pszString,
	                                            size_t cchSize) const;
	BOOL                DeleteOverlayImageFile(BOOL bRecursive = FALSE);
	INT_PTR             GetTargetProductCount(void) const;
	BOOL                GetTargetProduct    (INT_PTR iIndex,
	                                         NCTC_TARGET_PRODUCT_INFO* pProductInfo) const;
	INT_PTR             AddTargetProduct    (const NCTC_TARGET_PRODUCT_INFO* pProductInfo);
	BOOL                DeleteTargetProduct (int iIndex);
	BOOL                IsValidForProduct   (LPCTSTR pszProductName,
	                                         int nMajorVersion,
	                                         int nMinorVersion,
	                                         DWORD dwLocaleId = 0);
	BOOL                AddReactor          (NcTcCatalogItemReactor* pReactor);
	BOOL                RemoveReactor       (NcTcCatalogItemReactor* pReactor);
	BOOL                Sort                (int nSortOption,
	                                         BOOL bRecursive);
	BOOL                SetItemOrder        (NcTcCatalogItem** pItems,
	                                         INT_PTR nNumItems);
	NcTc::ItemOption    GetOption           (void) const;
	BOOL                SetOption           (NcTc::ItemOption nOption);
	BOOL                GetFileRevision     (long& lMajorVersion,
	                                         long& lMinorVersion) const;
	BOOL                GetRevision         (long& lMajorVersion,
	                                         long& lMinorVersion,
	                                         long& lUserVersion) const;
	BOOL                IsUserModified      (void) const;
public:
	virtual NcTcCatalogItem&    operator=   (const NcTcCatalogItem& srcItem);
	virtual BOOL        Reset               (void);
	virtual CatalogItemType GetType         (void) const;
	virtual int         GetTypeString       (LPTSTR pszString,
	                                         int cchSize,
	                                         BOOL bLocalized    = FALSE,
	                                         BOOL bPluralForm   = FALSE) const;
	virtual int         GetTagName          (LPTSTR pszString,
	                                         int cchSize) const;
	virtual BOOL        Load                (IUnknown* pUnknown,
	                                         DWORD dwLoadOption = kLoadLinks);
	virtual BOOL        Load                (IStream* pStream,
	                                         DWORD dwLoadOption = kLoadLinks);
	virtual BOOL        Save                (IUnknown* pUnknown,
	                                         DWORD dwSaveOption = kSaveLinksAsLinks);
	virtual BOOL        Save                (IStream* pStream,
	                                         DWORD dwSaveOption = kSaveLinksAsLinks);
	virtual BOOL        Clone               (BOOL bDeep,
	                                         NcTcCatalogItem*& pClone,
	                                         BOOL bCopyId = FALSE) const;
	virtual BOOL        CopyFrom            (const NcTcCatalogItem* pSrcItem,
	                                         BOOL bCopyId = FALSE);
	virtual BOOL        IsValidChild        (const CatalogItemType nType) const;
protected:
	virtual NcTcCatalogItem* CreateObject  (void) const;
protected:
	NcTcCatalogItem(NcTcSystemInternals*);
private:
	friend class NcTcSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcTcCategory
class THUNK_NATIVE_API NcTcCategory : public NcTcCatalogItem {
public:
	NcTcCategory();
	NcTcCategory(const NcTcCategory& srcItem);
	virtual ~NcTcCategory();
protected:
	NcTcCategory(NcTcSystemInternals*);
};

//////////////////////////////////////////////////////////////////////////
// NcTcCatalog
class THUNK_NATIVE_API NcTcCatalog : public NcTcCategory {
public:
	NcTcCatalog();
	NcTcCatalog(const NcTcCatalog& srcItem);
	virtual ~NcTcCatalog();
protected:
	NcTcCatalog(NcTcSystemInternals*);
};

//////////////////////////////////////////////////////////////////////////
// NcTcStockTool
class THUNK_NATIVE_API NcTcStockTool : public NcTcCatalogItem {
public:
	NcTcStockTool();
	NcTcStockTool(const NcTcStockTool& srcItem);
	virtual ~NcTcStockTool();
	NcTcTool*   CreateTool          (BOOL bSetDefaults = TRUE);
	BOOL                CreateNcadStockTool (IUnknown** ppStockTool);
	BOOL                CreateNcadTool      (IUnknown** ppUnknown);
	BOOL                GetComClassID       (CLSID& clsid) const;
	BOOL                SetComClassID       (const  CLSID& clsid);
	int                 GetModuleFileName   (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetModuleFileName   (LPCTSTR pszString);
	int                 GetModuleInstallUrl (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetModuleInstallUrl (LPCTSTR pszString);
	int                 GetModuleInstallArguments(LPTSTR pszString,
	                                              int cchSize) const;
	BOOL                SetModuleInstallArguments(LPCTSTR pszString);
protected:
	NcTcStockTool(NcTcSystemInternals*);
private:
	friend class NcTcSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcTcTool
class THUNK_NATIVE_API NcTcTool : public NcTcCatalogItem {
public:
	NcTcTool();
	NcTcTool(const NcTcTool& srcItem);
	virtual ~NcTcTool();
	virtual BOOL        Execute             (int nFlag,
	                                         HWND hWnd,
	                                         POINT point,
	                                         DWORD dwKeyState);
	BOOL                GetToolData         (IUnknown** ppUnknown);
	NcTcStockTool*     GetStockTool        (void) const;
	BOOL                CreateNcadTool      (IUnknown** ppTool,
	                                         BOOL bLoadData = TRUE);
	BOOL                GetStockToolID      (GUID* pId) const;
	BOOL                SetStockToolID      (const GUID* pId);
	int                 GetStockToolFileUrl (LPTSTR pszString,
	                                         int cchSize) const;
	BOOL                SetStockToolFileUrl (LPCTSTR pszString);
	ToolType            GetToolType         (void) const;
	BOOL                SetToolType         (ToolType nToolType);
	BOOL                IsFlyoutEnabled     (void) const;
	BOOL                EnableFlyout        (BOOL bUseFlyout);
	NcTcCatalogItem*    GetShapePackage     (void) const;
	BOOL                SetShapePackage     (NcTcCatalogItem* pPackage);
	NcTcTool*           GetCurrentShape     (void) const;
	BOOL                SetCurrentShape     (NcTcTool* pTool);
	BOOL                SetCurrentShape     (const GUID& id);
	BOOL                GetActiveShapes     (NcTcCatalogItem** pItems,
	                                         INT_PTR & nNumItems);
	BOOL                SetActiveShapes     (NcTcCatalogItem** pItems,
	                                         int nNumItems);
protected:
	NcTcTool(NcTcSystemInternals*);
};

//////////////////////////////////////////////////////////////////////////
// NcTcPackage
class THUNK_NATIVE_API NcTcPackage : public NcTcCatalogItem {
public:
	NcTcPackage();
	NcTcPackage(const NcTcPackage& srcItem);
	virtual ~NcTcPackage();
protected:
	NcTcPackage(NcTcSystemInternals*);
};

//////////////////////////////////////////////////////////////////////////
// NcTcPalette
class THUNK_NATIVE_API NcTcPalette : public NcTcPackage {
public:
	NcTcPalette();
	NcTcPalette(const NcTcPalette& srcItem);
	virtual ~NcTcPalette();
protected:
	NcTcPalette(NcTcSystemInternals*);
};

//////////////////////////////////////////////////////////////////////////
// NcTcCatalogItemReactor
class THUNK_NATIVE_API NcTcCatalogItemReactor {
public:
	virtual ~NcTcCatalogItemReactor(void);
	BOOL                Enable              (BOOL bEnable);
	BOOL                IsEnabled           (void) const;
	virtual void        ChildAdded          (NcTcCatalogItem* pChild);
	virtual void        ChildDeleted        (NcTcCatalogItem* pChild);
	virtual void        ChildDetached       (NcTcCatalogItem* pChild);
protected:
	NcTcCatalogItemReactor();
private:
	friend class NcTcSystemInternals;
};

typedef struct NCTCUI_DRAG_HEADER {
	DWORD               mdwDragFormat;
#ifdef _NDESK_WINDOWS_
	CLIPFORMAT          mcfClipFormat;
#endif
	BOOL                mbAutoCADSource;
	DWORD               mdwSourceProcessId;
	GUID                mRootId;
	GUID                mParentId;
	BOOL                mbReadOnlySource;
	int                 mnCount;
	int                 mnStockTools;
	DWORD               mdwItemTypes;
} NCTCUI_DRAG_HEADER;

#define NCTCUI_IDW_CATALOGVIEW              0xFFFF
#define NCTCUI_CVSTYLE_SHOWTEXT             NCTCUI_CVISTYLE_SHOWTEXT
#define NCTCUI_CVSTYLE_SAVE_ORDER_IN_CATALOG (0x1 << 11)
#define NCTCUI_CVSTYLE_NO_QSL               (0x1 << 12)
#define NCTCUI_CVSTYLE_NO_SELECTION         (0x1 << 13)
#define NCTCUI_CVSTYLE_NO_VIEW_BUTTON       (0x1 << 14)
#define NCTCUI_CVSTYLE_LISTVIEW             (0x1 << 15)
#define NCTCUI_CVSTYLE_TOOLTIPS             (0x1 << 16)
#define NCTCUI_CVSTYLE_MULTISELECT          (0x1 << 17)
#define NCTCUI_CVSTYLE_EDITLABELS           (0x1 << 18)
#define NCTCUI_CVSTYLE_HOVERSELECT          (0x1 << 19)
#define NCTCUI_CVSTYLE_NO_DRAGDROP          (0x1 << 20)
#define NCTCUI_CVSTYLE_NO_CUT               (0x1 << 21)
#define NCTCUI_CVSTYLE_NO_COPY              (0x1 << 22)
#define NCTCUI_CVSTYLE_NO_PASTE             (0x1 << 23)
#define NCTCUI_CVSTYLE_NO_REFRESH           (0x1 << 24)
#define NCTCUI_CVSTYLE_NO_REMOVE            (0x1 << 25)
#define NCTCUI_CVSTYLE_NO_RENAME            (0x1 << 26)
#define NCTCUI_CVSTYLE_NO_PROPERTIES        (0x1 << 27)
#define NCTCUI_CVSTYLE_NO_HELP              (0x1 << 28)
#define NCTCUI_CVSTYLE_NO_VIEWOPTIONS       (0x1 << 29)
#define NCTCUI_CVSTYLE_NO_OPERATIONS        (NCTCUI_CVSTYLE_NO_CUT        | \
                                             NCTCUI_CVSTYLE_NO_COPY       | \
                                             NCTCUI_CVSTYLE_NO_PASTE      | \
                                             NCTCUI_CVSTYLE_NO_REFRESH    | \
                                             NCTCUI_CVSTYLE_NO_REMOVE     | \
                                             NCTCUI_CVSTYLE_NO_RENAME     | \
                                             NCTCUI_CVSTYLE_NO_PROPERTIES | \
                                             NCTCUI_CVSTYLE_NO_HELP       | \
                                             NCTCUI_CVSTYLE_NO_VIEWOPTIONS)
#define NCTCUI_CVSTYLE_NO_FLYOUT            (0x1 << 30)
#define NCTCUI_CVSTYLE_NO_SCROLLBAR         (0x1 << 31)

#define NCTCUI_DDO_ACCEPT_TOOL              (0x1 << 0)
#define NCTCUI_DDO_ACCEPT_PALETTE           (0x1 << 1)
#define NCTCUI_DDO_ACCEPT_PACKAGE           (0x1 << 2)
#define NCTCUI_DDO_ACCEPT_CATEGORY          (0x1 << 3)
#define NCTCUI_DDO_ACCEPT_CATALOG           (0x1 << 4)
#define NCTCUI_DDO_ACCEPT_STOCKTOOL         (0x1 << 5)
#define NCTCUI_DDO_ACCEPT_FILES             (0x1 << 6)
#define NCTCUI_DDO_ACCEPT_ALL_ITEMS         (NCTCUI_DDO_ACCEPT_TOOL     | \
                                             NCTCUI_DDO_ACCEPT_STOCKTOOL| \
                                             NCTCUI_DDO_ACCEPT_PALETTE  | \
                                             NCTCUI_DDO_ACCEPT_PACKAGE  | \
                                             NCTCUI_DDO_ACCEPT_CATEGORY | \
                                             NCTCUI_DDO_ACCEPT_CATALOG  | \
                                             NCTCUI_DDO_ACCEPT_FILES)

#define NCTCUI_CVHT_NOWHERE                 (0x0)
#define NCTCUI_CVHT_ITEM                    (0x1 << 0)
#define NCTCUI_CVHT_ITEMIMAGE               (0x1 << 1)
#define NCTCUI_CVHT_ITEMLABEL               (0x1 << 2)
#define NCTCUI_CVHT_BACKGROUND              (0x1 << 3)
#define NCTCUI_CVHT_ABOVE                   (0x1 << 4)
#define NCTCUI_CVHT_BELOW                   (0x1 << 5)
#define NCTCUI_CVHT_LEFT                    (0x1 << 6)
#define NCTCUI_CVHT_RIGHT                   (0x1 << 7)
#define NCTCUI_CVHT_ITEMTRIGGER             (0x1 << 8)

#define NCTCUI_OVERLAY_ALIGN_TOPLEFT        1
#define NCTCUI_OVERLAY_ALIGN_TOPRIGHT       2
#define NCTCUI_OVERLAY_ALIGN_BOTTOMLEFT     3
#define NCTCUI_OVERLAY_ALIGN_BOTTOMRIGHT    4

//////////////////////////////////////////////////////////////////////////
// CNcTcUiCatalogView
class THUNK_NATIVE_API CNcTcUiCatalogView : public CWnd {
	friend CNcTcUiImpCatalogView;
public:
	CNcTcUiCatalogView();
	CNcTcUiCatalogView(NcTcCatalogItem* pCatalogItem);
	virtual ~CNcTcUiCatalogView();
	BOOL                Create              (DWORD dwWndStyle,
	                                         DWORD dwCatalogViewStyle,
	                                         const RECT& rect,
	                                         CWnd* pParent,
	                                         UINT nID = NCTCUI_IDW_CATALOGVIEW);
	NcTcCatalogItem*   GetCatalogItem      (void) const;
	BOOL                SetCatalogItem      (NcTcCatalogItem* pCatalogItem);
	DWORD               GetCatalogViewStyle (void) const;
	BOOL                SetCatalogViewStyle (DWORD dwStyle);
	DWORD               GetDragDropOption   (void) const;
	BOOL                SetDragDropOption   (DWORD dwOption);
	int                 GetItemCount        (void) const;
	CNcTcUiCatalogViewItem* GetItem         (int iIndex) const;
	DWORD               GetItemData         (int iIndex) const;
	BOOL                SetItemData         (int iIndex, DWORD dwData);
	BOOL                GetImageSize        (LPSIZE lpSize) const;
	BOOL                SetImageSize        (const SIZE& size);
	BOOL                Update              (BOOL bRedraw = TRUE);
	int                 GetRowsInPage       (BOOL bIncludePartialRows) const;
	int                 GetColumnsInPage    (void) const;
	BOOL                Scroll              (CSize sizeScroll);
	BOOL                EnsureVisible       (int nIndex,
	                                         BOOL bPartialOk);
	BOOL                GetInsertMark       (int& nIndex,
	                                         BOOL& bAfter) const;
	BOOL                SetInsertMark       (int nIndex,
	                                         BOOL bAfter = FALSE);
	int                 GetFirstVisibleItemIndex(BOOL bPartialOk = TRUE) const;
	int                 GetLastVisibleItemIndex(BOOL bPartialOk = TRUE) const;
	CEdit*   EditLabel           (int nIndex);
	BOOL                IsLabelEditing      (void) const;
	BOOL                EndLabelEdit        (BOOL bCancel = FALSE);
	BOOL                Load                (IUnknown* pUnk);
	BOOL                Save                (IUnknown* pUnk);
	BOOL                SelectItem          (int nIndex,
	                                         BOOL bSelect = TRUE);
	BOOL                SelectItemRange     (int nStartIndex,
	                                         int nEndIndex,
	                                         BOOL bSelect = TRUE);
	int                 GetSelectedCount    (void) const;
	CNcTcUiCatalogViewItem* GetSelectedItem(void) const;
	POSITION            GetFirstSelectedItemPosition(void) const;
	CNcTcUiCatalogViewItem* GetNextSelectedItem(POSITION& pos) const;
	BOOL                GetItemRect         (int iIndex, LPRECT lpRect, int nCode) const;
	CNcTcUiCatalogViewItem* GetItemFromPoint(const CPoint& pt);
	BOOL                GetViewRect         (LPRECT lpRect) const;
	int                 GetItemIndex        (CNcTcUiCatalogViewItem* pItem) const;
	int                 HitTest             (const CPoint& pt,
	                                         UINT* pHitFlags) const;
	CNcTcUiCatalogViewItem* GetCurrentItem (void) const;
	virtual BOOL        GetMinimumSize      (CSize& size);
	virtual BOOL        PreTranslateMessage (MSG* pMsg);
	virtual BOOL        Copy                (const CNcTcUiCatalogViewItemArray& itemsCopied,
	                                         IDataObject* pDataObject);
	virtual BOOL        Paste               (IDataObject* pDataObject,
	                                         int iIndex = -1,
	                                         NcTcCatalogItemArray* pNewTools = NULL);
	virtual BOOL        CanPaste            (IDataObject* pDataObject);
	BOOL                GetOverlayImageSize (LPSIZE lpSize) const;
	BOOL                SetOverlayImageSize (const SIZE& size);
	int                 GetOverlayImageAlignment(void) const;
	BOOL                SetOverlayImageAlignment(int nAlignment);
	BOOL                GetItemOrder        (NcTcCatalogItemArray& items) const;
	BOOL                SetItemOrder        (const NcTcCatalogItemArray& items);
	BOOL                ResetItemOrder      (void);
	CNcTcUiScheme*      GetScheme           (void) const;
	BOOL                Sort                (int nSortOption);
protected:
	virtual void        OnLButtonClicked    (UINT nFlags,
	                                         CPoint point);
	virtual void        OnLButtonDblClicked (UINT nFlags,
	                                         CPoint point);
	virtual BOOL        AddContextMenuItems (CMenu*pMenu,
	                                         int nHitFlag);
	virtual void        OnItemCopy          (void);
	virtual void        OnItemCut           (void);
	virtual void        OnItemPaste         (void);
	virtual void        OnItemRemove        (void);
	virtual void        OnItemRename        (void);
	virtual void        OnItemRefresh       (void);
	virtual void        OnItemProperties    (void);
	virtual void        OnItemInstallTool   (void);
	virtual void        OnItemHelp          (void);
	virtual DROPEFFECT  DragEnter           (NDUI_DRAGDATA* pDragData);
	virtual void        DragLeave           (NDUI_DRAGDATA* pDragData);
	virtual DROPEFFECT  DragOver            (NDUI_DRAGDATA* pDragData);
	virtual DROPEFFECT  Drop                (NDUI_DRAGDATA* pDragData);
	virtual DROPEFFECT  DropEx              (NDUI_DRAGDATA* pDragData);
	virtual void        OnBeginDrag         (const CNcTcUiCatalogViewItemArray& itemsDragged,
	                                         IDataObject* pDataObject,
	                                         DWORD dwKeyState);
	virtual HRESULT     OnDragInProgress    (DROPEFFECT dropEffect);
	virtual void        OnEndDrag           (DROPEFFECT dropEffect);
	virtual LONG        OnBeginNcadDrop     (BOOL* pCancelDrop);
	virtual LONG        OnEndNcadDrop       (BOOL bSuccess);
protected:
protected:
	BOOL OnToolTipGetDispInfo(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnCatalogItemCut();
	afx_msg void OnCatalogItemCopy();
	afx_msg void OnCatalogItemRemove();
	afx_msg void OnCatalogItemRename();
	afx_msg void OnCatalogItemHelp();
	afx_msg void OnCatalogItemProperties();
	afx_msg void OnCatalogItemInstallTool();
	afx_msg void OnCatalogItemRefresh();
	afx_msg void OnCatalogItemPaste();
	afx_msg void OnSortByName();
	afx_msg void OnSortByType();
	afx_msg void OnAddText();
	afx_msg void OnAddSeparator();
	afx_msg void OnViewOptions();
	afx_msg void OnCatalogParentProperties();
	afx_msg void OnCatalogParentRefresh();
	afx_msg void OnViewButton();
	afx_msg void OnCatalogParentRename();
	afx_msg void OnAllowDocking();
	afx_msg void OnAutoHide();
	afx_msg void OnTransparency();
	afx_msg void OnNewPalette();
	afx_msg void OnCustomize();
	afx_msg void OnCustomizeCUI();
	afx_msg void OnSearchWithSeek();
	afx_msg UINT OnGetDlgCode();
	afx_msg LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDragScroll(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBeginLabelEdit(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEndLabelEdit(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGiveFeedback(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBeginNcadDrop(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEndNcadDrop(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRenderData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDragEnterToolbarItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDragOverToolbarItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDragLeaveToolbarItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDropToolbarItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChildAdded(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChildDeleted(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChildDetached(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCloseShapePalette(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetItemCount(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT  OnGetText(WPARAM wParam,LPARAM  lParam);
	afx_msg LRESULT OnGetItemTextLen(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGetItemRect(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
protected:
	CNcTcUiCatalogView(NcTcUiSystemInternals*);
private:
	friend class NcTcUiSystemInternals;
};

#define NCTCUI_CVISTYLE_PUSHBUTTON      0x0
#define NCTCUI_CVISTYLE_SHOWTEXT        (0x1 << 1)
#define NCTCUI_CVISTYLE_RIGHTTEXT       (0x1 << 2)
#define NCTCUI_CVISTYLE_FLYOUT          (0x1 << 3)
#define NCTCUI_CVISTYLE_FULLROW         (0x1 << 4)
#define NCTCUI_CVISTYLE_HIDEIMAGE       (0x1 << 5)
#define NCTCUI_CVISTYLE_TEXT            (0x1 << 6)
#define NCTCUI_CVISTYLE_SEPARATOR       (0x1 << 7)

#define NCTCUI_CVISTATE_HIGHLIGHTED     (0x1 << 0)
#define NCTCUI_CVISTATE_SELECTED        (0x1 << 1)
#define NCTCUI_CVISTATE_HALO            (0x1 << 2)
#define NCTCUI_CVISTATE_FOCUSED         (0x1 << 3)

#define NCTCUI_CVIR_BOUNDS              (0x1 << 0)
#define NCTCUI_CVIR_IMAGE               (0x1 << 1)
#define NCTCUI_CVIR_LABEL               (0x1 << 2)
#define NCTCUI_CVIR_USEFULLLABEL        (0x1 << 3)
#define NCTCUI_CVIR_TRIGGER             (0x1 << 4)
#define NCTCUI_CVIR_WORLDRECT           (0x1 << 5)

//////////////////////////////////////////////////////////////////////////
// CNcTcUiCatalogViewItem
class THUNK_NATIVE_API CNcTcUiCatalogViewItem : public CObject {
public:
	virtual ~CNcTcUiCatalogViewItem();
	BOOL                Render              (BOOL bEraseBackground = FALSE);
	BOOL                Render              (CDC* pDC,
	                                         int x,
	                                         int y);
	BOOL                GetRect             (LPRECT lpRect,
	                                         int nCode) const;
	NcTcCatalogItem*   GetCatalogItem      (void) const;
	BOOL                SetCatalogItem      (NcTcCatalogItem* pCatalogItem);
	DWORD               GetStyle            (void) const;
	DWORD               GetState            (void) const;
	BOOL                SetState            (DWORD dwState);
	BOOL                GetPosition         (LPPOINT lpPoint) const;
	DWORD               GetData             (void) const;
	BOOL                SetData             (DWORD dwData);
	BOOL                Highlight           (BOOL bHighlight = TRUE);
	BOOL                Select              (BOOL bSelect = TRUE);
	BOOL                Halo                (BOOL bHalo = TRUE);
protected:
	CNcTcUiCatalogViewItem(CNcTcUiCatalogView* pCatalogView);
	CNcTcUiCatalogViewItem(CNcTcUiCatalogView* pCatalogView,
	                       NcTcCatalogItem* pCatalogItem, const CSize& sizeImage,
	                       DWORD dwStyle = NCTCUI_CVISTYLE_PUSHBUTTON);
private:
	friend class NcTcUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNcTcUiManager
class THUNK_NATIVE_API CNcTcUiManager {
public:
	CNcTcUiManager();
	virtual ~CNcTcUiManager();
	CNcTcUiToolPaletteSet* GetToolPaletteWindow(void);
	BOOL                Load                (IUnknown* pUnknown);
	BOOL                Save                (IUnknown* pUnknown);
	BOOL                SetApplicationWindow(HWND hWndApp);
	HWND                GetApplicationWindow(void);
	COleDropTarget*     GetDropTarget       (void);
	CNcTcUiToolPalette* CreatePalette       (LPCTSTR pszPalName = NULL,
	                                         DWORD dwFlags = 0);
	BOOL                Export              (LPCTSTR pszFile,
	                                         const NcTcUiToolPaletteArray* palettes = NULL);
	BOOL                Import              (LPCTSTR pszFile);
	BOOL                FindPalette         (const NcTcCatalogItem* pItem,
	                                         CNcTcUiToolPalette** ppToolPalette) const;
	BOOL                FindPalette         (const GUID& itemId,
	                                         CNcTcUiToolPalette** ppToolPalette) const;
	BOOL                ShowToolPaletteWindow(BOOL bShow = TRUE);
	BOOL                IsToolPaletteWindowVisible(void) const;
	int                 GetToolFilterCount  (void) const;
	int                 AddToolFilter       (LPCTSTR pszProductName,
	                                         int nMajorVersion,
	                                         int nMinorVersion,
	                                         DWORD dwLocaleId);
	BOOL                GetToolFilter       (int iIndex,
	                                         LPTSTR pszProductName,
	                                         int* pMajorVersion,
	                                         int* pMinorVersion,
	                                         DWORD* pLocaleId) const;
	BOOL                DeleteToolFilter    (int iIndex);
	CNcTcUiScheme*      GetScheme           (LPCTSTR pszName) const;
	CNcTcUiScheme*      GetScheme           (int nIndex);
	int                 GetSchemeCount      (void);
	int                 AddScheme           (CNcTcUiScheme* pUiScheme);
	BOOL                RemoveScheme        (CNcTcUiScheme* pUiScheme);
	void                NotifyDropPoint     (const NcGePoint3d& point);
private:
	friend class NcTcUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNcTcUiPaletteView
class THUNK_NATIVE_API CNcTcUiPaletteView : public CNcTcUiCatalogView {
public:
	CNcTcUiPaletteView();
	virtual ~CNcTcUiPaletteView();
protected:
	virtual DROPEFFECT  DragEnter           (NDUI_DRAGDATA* pDragData);
	virtual DROPEFFECT  DragOver            (NDUI_DRAGDATA* pDragData);
	virtual void        DragLeave           (NDUI_DRAGDATA* pDragData);
	virtual DROPEFFECT  Drop                (NDUI_DRAGDATA* pDragData);
	virtual DROPEFFECT  DropEx              (NDUI_DRAGDATA* pDragData);
protected:
protected:
	CNcTcUiPaletteView(NcTcUiSystemInternals*);
protected:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnInvokeCommand(UINT nID);
	afx_msg void OnPaletteRemove();
	afx_msg void OnCatalogItemSpecifyImage();
	afx_msg void OnCatalogItemRemoveImage();
	afx_msg void OnCatalogItemUpdateImage();
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CNcTcUiScheme
class THUNK_NATIVE_API CNcTcUiScheme : public CObject {
public:
	enum RefreshScope {
		kAllPalettes                    = (0x1 << 0),
		kRefreshEnabledPalettes         = (0x1 << 1),
		kAutoRefreshEnabledPalettes     = (0x1 << 2),
	};
	enum ShowOption {
		kShow                           = (0x1 << 0),
		kHide                           = (0x1 << 1),
		kSaveState                        = (0x1 << 2),
		kRestoreState                   = (0x1 << 3),
	};
	CNcTcUiScheme(NcTcScheme* pScheme);
	virtual ~CNcTcUiScheme();
	BOOL                Load                (IUnknown* pUnknown);
	BOOL                Save                (IUnknown* pUnknown);
	BOOL                Unload              (void);
	CNcTcUiToolPaletteSet* CreatePaletteSet (LPCTSTR pszPalSetName);
	CNcTcUiToolPaletteSet* GetPaletteSet    (void);
	BOOL                FindPalette         (const NcTcCatalogItem* pItem,
	                                         CNcTcUiToolPalette** ppToolPalette) const;
	BOOL                FindPalette         (const NcTcCatalogItem* pItem,
	                                         CNcTcUiToolPalette** ppToolPalette,
	                                         CNcTcUiToolPaletteSet** ppToolPaletteSet) const;
	BOOL                FindPalette         (const GUID& itemId,
	                                         CNcTcUiToolPalette** ppToolPalette) const;
	BOOL                FindPalette         (const GUID& itemId,
	                                         CNcTcUiToolPalette** ppToolPalette,
	                                         CNcTcUiToolPaletteSet** ppToolPaletteSet) const;
	BOOL                Export              (LPCTSTR pszFile);
	BOOL                Export              (LPCTSTR pszFile,
	                                         const NcTcUiToolPaletteArray* palettes);
	BOOL                Import              (LPCTSTR pszFile);
	BOOL                Refresh             (RefreshScope nScope);
	BOOL                Refresh             (RefreshScope nScope,
	                                         DWORD dwRefreshFlag);
	BOOL                Show                (ShowOption nOption,
	                                         LONG_PTR lKey);
private:
	friend class NcTcUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNcTcUiToolPalette
class THUNK_NATIVE_API CNcTcUiToolPalette : public hostUiPalette {
	//friend CNcTcUiImpToolPalette;
	DECLARE_DYNCREATE(CNcTcUiToolPalette);
public:
	CNcTcUiToolPalette();
	virtual ~CNcTcUiToolPalette();
	CNcTcUiPaletteView* GetView             (void);
public:
	virtual BOOL        Create              (CNdUiPaletteSet* pParent);
	BOOL                Create              (DWORD dwStyle,
	                                         LPCTSTR pszName,
	                                         CNdUiPaletteSet* pParent,
	                                         DWORD dwPaletteStyle = 0);
	virtual BOOL        Load                (IUnknown* pUnk);
	virtual bool        CanFrameworkTakeFocus();
	virtual BOOL        Save                (IUnknown* pUnk);
	virtual BOOL        Import              (IUnknown* pUnk, LPCTSTR pszRefPath);
	virtual BOOL        Export              (IUnknown* pUnk, LPCTSTR pszRefPath);
	virtual BOOL        OnKillActive        (void);
	virtual BOOL        GetMinimumSize      (CSize& size);
	virtual void        OnSetActive         (void);
	virtual BOOL        NameEditValidation  (CEdit* pEdit);
	virtual BOOL        Paste               (IDataObject* pDataObject,
	                                         int iIndex = -1,
	                                         NcTcCatalogItemArray* pNewTools = NULL);
	virtual BOOL        CanPaste            (IDataObject* pDataObject);
	BOOL                SetView             (CNcTcUiPaletteView* pView);
	CNcTcUiScheme*      GetScheme           (void) const;
protected:
protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEndNameEdit(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	friend class NcTcUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNcTcUiToolPaletteGroup
class THUNK_NATIVE_API CNcTcUiToolPaletteGroup : public CObject {
	DECLARE_DYNAMIC(CNcTcUiToolPaletteGroup);
public:
	CNcTcUiToolPaletteGroup();
	virtual ~CNcTcUiToolPaletteGroup();
	BOOL            Reset                   (void);
	CString         GetName                 (void) const;
	BOOL            SetName                 (LPCTSTR pszName);
	CString         GetDescription          (void) const;
	BOOL            SetDescription          (LPCTSTR pszDesc);
	BOOL            IsItemPalette           (int iIndex) const;
	int             AddItem                 (CNcTcUiToolPalette* pPalette);
	int             AddItem                 (CNcTcUiToolPaletteGroup* pGroup);
	int             InsertItem              (int iIndex,
	                                         CNcTcUiToolPalette* pPalette);
	int             InsertItem              (int iIndex,
	                                         CNcTcUiToolPaletteGroup* pGroup);
	int             GetItemCount            (void) const;
	BOOL            GetItem                 (int iIndex,
	                                         CNcTcUiToolPalette*& pPalette) const;
	BOOL            GetItem                 (int iIndex,
	                                         CNcTcUiToolPaletteGroup*& pGroup) const;
	BOOL            DeleteItem              (CNcTcUiToolPalette* pPalette,
	                                         BOOL bRecursive = FALSE);
	BOOL            DeleteItem              (CNcTcUiToolPaletteGroup* pGroup);
	BOOL            RemoveItem              (CNcTcUiToolPalette* pPalette,
	                                         BOOL bRecursive = FALSE);
	BOOL            RemoveItem              (CNcTcUiToolPaletteGroup* pGroup);
	BOOL            DeleteAllPalettes       (void);
	BOOL            DeleteAllItems          (void);
	int             GetActivePalette        (void) const;
	BOOL            SetActivePalette        (int nIndex);
	BOOL            GetCustomData           (IUnknown** ppUnknown);
	virtual BOOL    Load                    (IUnknown* pUnk);
	virtual BOOL    Save                    (IUnknown* pUnk);
	virtual BOOL    Clone                   (CNcTcUiToolPaletteGroup*& pClone);
	CNcTcUiToolPaletteGroup* FindGroup      (LPCTSTR pszGroup,
	                                         BOOL bRecursive = TRUE);
	CNcTcUiToolPalette* FindPalette         (LPCTSTR pszPalName,
	                                         CNcTcUiToolPaletteGroup** ppGroup,
	                                         BOOL bRecursive = TRUE) const;
private:
	friend class NcTcUiSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// CNcTcUiToolPaletteSet
class THUNK_NATIVE_API CNcTcUiToolPaletteSet : public CNdUiPaletteSet {
	//friend CNcTcUiImpToolPaletteSet;
	DECLARE_DYNCREATE(CNcTcUiToolPaletteSet);
public:
	virtual ~CNcTcUiToolPaletteSet();
	virtual BOOL        Load                (IUnknown* pUnk);
	virtual BOOL        Save                (IUnknown* pUnk);
	virtual BOOL        Import              (IUnknown* pUnk, LPCTSTR pszRefPath);
	virtual BOOL        Export              (IUnknown* pUnk, LPCTSTR pszRefPath);
	virtual BOOL        HitTest             (CPoint pt, UINT& nFlag,
	                                         DWORD& dwData);
	int                 AddPalette          (hostUiPalette* pPalette);
	int                 InsertPalette       (int iIndex, hostUiPalette* pPalette);
	BOOL                RemovePalette       (hostUiPalette* pPalette);
	BOOL                RemovePalette       (int iIndex);
	virtual void        TitleBarLocationUpdated(NdUiTitleBarLocation newLoc);
	CNcTcUiToolPaletteGroup* GetToolPaletteGroup(BOOL bCreate = FALSE);
	CNcTcUiToolPaletteGroup* GetAllPalettesGroup(void);
	CNcTcUiToolPaletteGroup* GetActivePaletteGroup(void);
	BOOL                GetActivePaletteGroup(LPTSTR pszGroup,
	                                          int cbSize) const;
	BOOL                SetActivePaletteGroup(CNcTcUiToolPaletteGroup* pGroup);
	BOOL                SetActivePaletteGroup(LPCTSTR pszGroup);
	CNcTcUiScheme*      GetScheme           (void) const;
	BOOL                Show                (void);
	BOOL                Show                (BOOL bShow);
	BOOL                SetActivePalette    (hostUiPalette* pPalette);
	BOOL                SetActivePalette    (int nPaletteIndex);
	BOOL                SetActivePalette    (LPCTSTR pszPalName,
	                                         BOOL bSearchOnlyCurrentGroup) const;
	CNcTcUiToolPalette* FindPalette         (LPCTSTR pszPalName,
	                                         CNcTcUiToolPaletteGroup** ppGroup,
	                                         BOOL bSearchOnlyCurrentGroup) const;
protected:
	CNcTcUiToolPaletteSet();
protected:
	virtual BOOL        AddContextMenuItems (CMenu*pMenu,
	                                         int nHitFlag,
	                                         int nRightClkTab = 0);
	virtual void        ThemeModified       (NdUiThemeElement element);
	virtual void        OnTabDrag           (CPtrArray & arrayPalettes);
	virtual BOOL        OnBeginDrag         (COleDataSource* pDataSource,
	                                         CPtrArray & arrayPalettes);
	virtual void        OnEndDrag           (DROPEFFECT dropEffect);
	virtual BOOL        OnBeginMove         (COleDataSource* pDataSource,
	                                         CPtrArray & arrayPalettes);
	virtual void        OnEndMove           (DROPEFFECT dropEffect);
	virtual BOOL        OnRenderData        (LPFORMATETC lpFormatEtc,
	                                         LPSTGMEDIUM lpStgMedium);
	virtual void        OnTearOff           (CNdUiPaletteSet* pSet);
	virtual void        DestroyStackedPaletteSet(void);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnRemovePaletteSet();
	afx_msg void OnRemoveActivePalette();
	afx_msg void OnRemovePalette();
	afx_msg void OnViewOptions();
	afx_msg void OnSelectPaletteGroup( UINT nID );
	afx_msg void OnShowCustomizeDialog();
	afx_msg void OnShowCustomizeDialogCUI();
	afx_msg void OnNewPalette();
	afx_msg void OnPaste();
	afx_msg void OnPaletteProperties();
	afx_msg void OnRefreshPaletteSet();
	afx_msg void OnRefreshActivePalette();
	afx_msg void OnClose();
	afx_msg void OnMoveUp();
	afx_msg void OnMoveDown();
	afx_msg void OnInvokeCommand(UINT nID);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRenderData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	friend class NcTcUiSystemInternals;
};

THUNK_NATIVE_API BOOL NcTcInitialize   (void);
THUNK_NATIVE_API BOOL NcTcUninitialize (void);
THUNK_NATIVE_API NcTcManager* NcTcGetManager(void);
THUNK_NATIVE_API BOOL NcTcDownloadItem (LPCTSTR pszUrl,
                                        NcTcCatalogItem*& pNewItem, 
                                        DWORD dwItemTypes      = -1,
                                        DWORD dwDownloadFlag   = kDownloadAll,
                                        LPCTSTR pszDownloadPath= NULL);
THUNK_NATIVE_API int NcTcDownloadItem  (LPTSTR* pUrls,
                                        int nNumUrls, 
                                        NcTcCatalogItem** pItems, 
                                        DWORD dwItemTypes      = -1,
                                        DWORD dwDownloadFlag   = kDownloadAll, 
                                        LPCTSTR pszDownloadPath= NULL);
THUNK_NATIVE_API BOOL NcTcRefreshItem  (NcTcCatalogItem** pItems,
                                        int nNumItems,
                                        DWORD dwItemTypes      = -1,
                                        DWORD dwRefreshFlag    = kRefreshAll);
THUNK_NATIVE_API BOOL NcTcSort         (NcTcCatalogItem** pItems,
                                        int nNumItems,
                                        int nSortOption);
THUNK_NATIVE_API BOOL NcTcSetHostInfo  (long lCurrentMajorVersion,
                                        long lCurrentMinorVersion,
                                        bool bBldEnv);

#define NCTCUI_PI_SHOW_PROGRESS         (0x1 << 0)

THUNK_NATIVE_API BOOL NcTcUiCopyItems(COleDataSource* pDataSource,
                                      const NcTcCatalogItemArray* pItems,
                                      BOOL bAutoCADSource);
THUNK_NATIVE_API BOOL NcTcUiGetDragInfo(IDataObject* pDataObject,
                                        NCTCUI_DRAG_HEADER* pHeader);
THUNK_NATIVE_API CNcTcUiManager* NcTcUiGetManager(void);
THUNK_NATIVE_API CNcTcUiToolPaletteSet* NcTcUiGetToolPaletteWindow(void);
THUNK_NATIVE_API BOOL NcTcUiPasteItems(IDataObject* pDataObject,
                                       NcTcCatalogItemArray* pItems,
                                       NcTcCatalogItemArray* pStockTools,
                                       DWORD dwFlag = NCTCUI_PI_SHOW_PROGRESS);