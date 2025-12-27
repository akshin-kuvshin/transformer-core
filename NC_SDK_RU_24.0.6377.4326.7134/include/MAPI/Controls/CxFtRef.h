#pragma once

#include "mcSystem.h"
#include "IMcStyles.h"
extern CComModule _Module;
#include <atlbase.h>
#include <atlcom.h>

#if _MSC_VER==1200
	#define DWL_MSGRESULT DWLP_MSGRESULT
#endif
#include <atlctl.h>
#if _MSC_VER==1200
	#undef DWL_MSGRESULT
#endif

#if _MFC_VER < 0x0700
// from nt50\richedit.h
/* Flags for the SETEXTEX data structure */
#define ST_DEFAULT		0
#define ST_KEEPUNDO		1
#define ST_SELECTION	2

/* EM_SETTEXTEX info; this struct is passed in the wparam of the message */
typedef struct _settextex
{
	DWORD	flags;			/* flags (see the ST_XXX defines			*/
	UINT	codepage;		/* code page for translation (CP_ACP for sys default;
									 1200 for Unicode, -1 for control default	*/
} SETTEXTEX;

#define EM_SETTEXTEX			(WM_USER + 97)
#endif // _MFC_VER < 0x700


//////////////////////////////////////////////////////////////////////////
#define REF_COLOR RGB(192,193,194)      // Цвет ссылки
#define REF_VALUE (_T('#'))             // Имя переменной в формуле, вместо которой подставится значение поля

#define GEOM_VER_MAJOR            1
#define GEOM_VER_MINOR            0

typedef MComQIPtr<ITextRange>     ITextRangePtr;
typedef MComQIPtr<ITextDocument>  ITextDocumentPtr;
typedef MComQIPtr<ITextFont>      ITextFontPtr;
typedef MComQIPtr<ITextSelection> ITextSelectionPtr;
typedef MComQIPtr<ITextPara>      ITextParaPtr;
#if _MFC_VER >= 0x0700
_COM_SMARTPTR_TYPEDEF(IRichEditOle, IID_IRichEditOle);
#endif

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// CxFtRef
//---------------------------------------------------------------------------
IMCS_DECL_INTERFACE(CxFtRef, "{78BF28DD-2ACE-4d48-87ED-AF060C32BEC5}");
struct CxFtRef: public IMcTextRef
{
	IMCS_STD_METHOD_DEFINITION(CxFtRef, IMcTextRef);

	// IMcTextRef
	virtual HRESULT Purge(bool bLeaveText = true) override;
	virtual HRESULT Update(LPCTSTR stValue = NULL) override;
	virtual HRESULT Select() override;
	virtual McTextRefType getType() override;
	virtual DWORD getKey() override;
	virtual HRESULT setKey(DWORD dwKey) override;
	virtual mcsWorkID getObjectId() override;
	virtual McsString getPropertyName() override;
	virtual mcsPropertyType getPropertyType() override;
	virtual McsString getFormula() override;
	virtual HRESULT setFormula(McsString msText) override;
	virtual McsStringW getValue() override;
	virtual IMcsStreamPtr getData() override;
	virtual HRESULT setData(IMcsStream* pValue) override;
	virtual IMcDbObjectPtr getObject() override;
	virtual HRESULT EditObject(HWND hParent) override;
	virtual CLSID getClass() override;
	virtual bool getZoomed() override;
	virtual HRESULT setZoomed(bool bValue) override;
	virtual McsVertTextAlignEnum getAlign() override;
	virtual HRESULT setAlign(McsVertTextAlignEnum Val) override;
	virtual bool getStyleOverride() override;
	virtual HRESULT setStyleOverride(bool bValue) override;
	virtual McsString getURL() override;
	virtual HRESULT setURL(LPCTSTR stValue) override;
	virtual HRESULT MakeReference(mcsPropertyType type, const mcsWorkID& idSource, LPCTSTR stSource, LPCTSTR stTarget, LPCTSTR stFormula = NULL) override;
	virtual HRESULT MakeObject(IMcEntity* pSource) override;
	virtual HRESULT MakeGeometry(const mcsGeomEntArray& Geom) override;
	virtual HRESULT MakeAnchor(LPCTSTR stUrl) override;
	virtual HRESULT ToTemplate() override;
	virtual HRESULT FromTemplate(LPCTSTR stProperty, IMcEntity* pDataSource = NULL) override;

	// CxFtRef
	CxFtRef();
	HRESULT IsValid();
	HRESULT Create(HWND hControl, IMcObject* pOwner);
	HRESULT Get(HWND hControl, IMcObject* pOwner);
	HRESULT Get(HWND hControl, ITextRange* pTR, IMcObject* pOwner);
	void SetLink(BOOL fLink);
	bool getDetailed();
	HRESULT setDetailed(bool bValue);
	HRESULT EditFormula();
	HRESULT _FromTemplate(LPCTSTR stProperty, IMcEntity* pSource, bool* pbSelect, HWND hControl);
	HRESULT ConvertOldReference(McRefEntry& ref, DWORD dwKey);

	friend struct CxFtRefs;

	ITextRangePtr m_pRange;
	CDbEntityPrototypePtr m_pHost;
	MSXML2::IXMLDOMDocumentPtr m_pXml;

protected:
	McTextRefType m_type;
	McsStringW m_msText;
	HWND m_hControl;
	DWORD m_dwKey;
	bool m_bDetailed;
};

//////////////////////////////////////////////////////////////////////////
struct CxFtRefs : public McsArray<CxFtRefPtr, CxFtRef*>
{
	HRESULT Load(IN HWND hControl, IN IMcObject* pOwner);
	int Find(IN DWORD wKey, IN OPTIONAL int nFrom = 0);

	// array helpers
	HRESULT ToTemplate();
	HRESULT FromTemplate(HWND hControl, LPCTSTR stProperty, IMcEntity* pDataSource = NULL);
	HRESULT Purge();
};

//////////////////////////////////////////////////////////////////////////
struct CxEnumFORMATETC
: public CComEnumImpl
	<
		IEnumFORMATETC,
		&IID_IEnumFORMATETC,
		FORMATETC,
		_Copy<FORMATETC>
	>
/*
	,
		public CComObject<CComObjectRoot>
*/
{};

struct CxEnumSTATDATA
: public CComEnumImpl
<
	IEnumSTATDATA,
	&IID_IEnumSTATDATA,
	STATDATA,
	_Copy<STATDATA>
>
{};

struct CxDataObject
: public IDataObjectImpl<CxDataObject>
{
	// IUnknown
	virtual ULONG STDMETHODCALLTYPE AddRef() { return ++m_dwCount; }
	virtual ULONG STDMETHODCALLTYPE Release() { DWORD dw = --m_dwCount; if (!m_dwCount) delete this; return dw; }
	STDMETHOD(QueryInterface)(REFIID riid,  void** ppvObject);

	// IDataObject
	STDMETHOD(GetDataHere)(FORMATETC* pFormatetc, STGMEDIUM* pmedium);
	STDMETHOD(QueryGetData)(FORMATETC* pFormatetc);
	STDMETHOD(GetCanonicalFormatEtc)(FORMATETC* pFormatetcIn, FORMATETC* pFormatetcOut);
	STDMETHOD(SetData)(FORMATETC* pformatetc,  STGMEDIUM* pmedium, BOOL fRelease);
	STDMETHOD(EnumFormatEtc)(DWORD dwDirection, IEnumFORMATETC** ppenumFormatEtc);

	// IDataObjectImpl
	HRESULT IDataObject_GetData(FORMATETC* pFormatetc, STGMEDIUM* pmedium);

	// CxDataObject
	CxDataObject() : m_dwCount(1) { m_Data.SetSize(0,1); }

	CLIPFORMAT GetFormat();
	HRESULT SetText(_bstr_t bstrText);
	// Insert text fragment from this object into text range and remove extra CR
	HRESULT Paste(ITextRange* pTR);

	CComPtr<IDataAdviseHolder> m_spDataAdviseHolder;
	struct _Data {
		CLIPFORMAT cf;
		mcsByteArray dt;
	};
	McsArray<_Data, const _Data&> m_Data;
	DWORD m_dwCount;
};


//////////////////////////////////////////////////////////////////////////
HRESULT IsOurText(ITextRange* pTR);
HRESULT rtfPaste(ITextRange* pTR, LPCWSTR lpszText, HWND hRich);