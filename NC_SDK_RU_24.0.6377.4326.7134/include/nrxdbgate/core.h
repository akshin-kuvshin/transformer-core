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

#ifndef __OPENDWG_CORE_H__
#define __OPENDWG_CORE_H__

#include "nrxdbgate_impexp.h"


#define NRX_NO_VTABLE       __declspec(novtable)
#define NRX_DEPRECATED      __declspec(deprecated)

#ifdef _MSC_EXTENSIONS
	#define NRX_OVERRIDE  override
	#define NRX_SEALED sealed
#else //_MSC_EXTENSIONS
	#define NRX_OVERRIDE
	#define NRX_SEALED
#endif //_MSC_EXTENSIONS
class NcApDocument;
class NcCmComplexColor;
class NcCmEntityColor;
class NcDb3PointAngularDimension;
class NcDbAnnotativeObjectPE;
class NcDbAlignedDimension;
class NcDbArc;
class NcDbArcDimension;
class NcDbAttribute;
class NcDbAuditInfo;
class NcDbBlockReference;
class NcDbBlockTable;
class NcDbCircle;
class NcDbCurve;
class NcDbDatabase;
class NcDbDiametricDimension;
class NcDbDimension;
class NcDbDimStyleTable;
class NcDbDynBlockReference;
class NcDbDwgFiler;
class NcDbDxfFiler;
class NcDbEllipse;
class NcDbEntity;
class NcDbFace;
class NcDbHostApplicationServices;
class NcDbGroup;
class NcDbHatch;
class NcDbImage;
class NcDbLine;
class NcDbLayerTable;
class NcDbLine;
class NcDbLinetypeTable;
class NcDbMPolygon;
class NcDbMText;
class NcDbObject;
class NcDbObjectContextCollection;
class NcDbObjectContextInterface;
class NcDbObjectContextManager;
class NcDbObjectIterator;
class NcDbObjectId;
class NcDbOrdinateDimension;
class NcDbPoint;
class NcDbPolyline;
class NcDbPolyFaceMesh;
class NcDbPolyFaceMeshVertex;
class NcDb3dPolyline;
class NcDb2dPolyline;
class NcDb3dSolid;
class NcDb2dVertex;
class NcDbProxyEntity;
class NcDbProxyObject;
class NcDbSymbolTable;
class NcDbRadialDimension;
class NcDbRadialDimensionLarge;
class NcDbRasterImage;
class NcDbRegAppTable;
class NcDbRay;
class NcDbRegion;
class NcDbRotatedDimension;
class NcDbShape;
class NcDbSolid;
class NcDbSpline;
class NcDbSurface;
class NcDbTable;
class NcDbText;
class NcDbTextStyleTable;
class NcDbVertex;
class NcDb3dPolylineVertex;
class NcDbPolygonMesh;
class NcDbPolygonMeshVertex;
class NcDbViewTable;
class NcDbViewportTable;
class NcDbWipeout;
class NcDbUCSTable;
class NcDbXline;
class NcGiDrawableTraits;
class NcGiGlyph;
class NcGiViewport;
class NcGiViewportDrawNrx;
class NcGiWorldDraw;
class NcRxClass;
class NcRxDictionary;
class NcRxDictionaryIterator;
class NcRxDynamicLinker;
class NcRxObject;
class NcRxService;
class NcRxOverruleIterator;

class OdRxObject;
class OdRxObjectPtr;
class NcRxObjectPtr;
typedef OdRxObjectPtr (*OdRxConsFunc)();
typedef NcRxObjectPtr(*NcOdRxConsFunc)();
typedef NcRxObject* (*NcRxConsFunc)();

typedef void (*ncAppNameChangeFuncPtr)(const NcRxClass* classObj,
                NCHAR *& newAppName, int saveVer);

// Notification of not implemented method or function
enum AssertMessageFormat {
	kDebugPrint,    // Debug log
	kMessageBox     // Message box
};


NRXDBGATE_EXPORT void SetNotImplMessageFormat(AssertMessageFormat message_format);
NRXDBGATE_EXPORT AssertMessageFormat GetNotImplMessageFormat();

#ifdef _DEBUG
	#define AssertNotImplemented(expr) \
		{ \
			NcString not_impl_msg; \
			not_impl_msg.format(_T("Method/function not implemented: %s\n"), NCRX_T(#expr)); \
			static bool show_again = true; \
			if (show_again && GetNotImplMessageFormat() == kMessageBox) \
			{ \
				not_impl_msg += _T("\n\nBreak: Break to debugger\n\n") \
				                _T("Retry: Assert on next error\n\n") \
				                _T("Skip: Do not assert on this error"); \
				int retval = ::MessageBox(NULL, not_impl_msg, _T("Error"), MB_ICONASTERISK | MB_ABORTRETRYIGNORE); \
				if (retval == IDABORT) \
				{ \
					DebugBreak(); \
				} \
				else if (retval == IDIGNORE) \
				{ \
					show_again = false; \
				} \
			} \
			else if(GetNotImplMessageFormat() == kDebugPrint) \
			{ \
				OutputDebugString((LPCTSTR)not_impl_msg); \
			} \
		}
#else
	#define AssertNotImplemented(expr)
#endif
NRXDBGATE_EXPORT void* nrxGCalloc(size_t s);
NRXDBGATE_EXPORT void nrxGCfree(void*);


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcRxObject
class NRXDBGATE_EXPORT NcRxObject
{
protected:
	NcRxObject();

public:
	NcRxObject(OdRxObject* _object);

public:
	virtual ~NcRxObject();

public:
	typedef OdRxObject  native_class;

public:
	virtual NcRxClass* isA() const;

	bool isKindOf(const NcRxClass* other) const;

	NcRxObject* queryX(const NcRxClass* protocol) const;
	NcRxObject* x(const NcRxClass* protocolClass) const;

	virtual NcRxObject* clone() const;

	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source);

	virtual NRX::Boolean isEqualTo(const NcRxObject* other) const;
	virtual NcRx::Ordering comparedTo(const NcRxObject* other) const;

public:
	static NcRxClass* desc();
	static NcRxObject* cast(const NcRxObject* source)
	{
		return ((source == NULL) || !source->isKindOf(NcRxObject::desc())) ? NULL : (NcRxObject*)source;
	};

public:

	virtual OdRxObject* GetNativeObject() const;

	/*
	Get pointer to platform object
	*/
	OdRxObject* native() const;

	/*
	Disconnect platform object from wrapper
	Return value:
		Pointer to platform object
	*/
	OdRxObjectPtr detach();

public:

	static NcRxObject* attach(const OdRxObject* _object);

protected:

	void AssignNative(OdRxObject* _object) const;

public:
	static NcRxClass* gpDesc;
	void* operator new(size_t, void* p) { return p; }
	void* operator new[](size_t, void* p) { return p; }
	void* operator new  (size_t s) { return nrxGCalloc(s); }
	void* operator new[](size_t s) { return nrxGCalloc(s); }
	void  operator delete(void* p) { nrxGCfree(p); }
	void  operator delete[](void* p) { nrxGCfree(p); }
	void* operator new(size_t s, const char* pFName,int nLine) { return nrxGCalloc(s); }
	void* operator new[](size_t s,const char* pFName, int nLine) { return nrxGCalloc(s); }
	void operator delete(void* p, const char* pFName,int nLine) { nrxGCfree(p); }
	void operator delete[](void* p, const char* pFName, int nLine) { nrxGCfree(p); }
	bool isValid() { 
#ifdef DEBUG
		return m_fvalid;
#else
		return m_pNative;
#endif
	}
	
protected:
	mutable OdRxObject* m_pNative = nullptr;
#ifdef DEBUG
	bool m_fvalid = true;	
#endif
};

#include "ncstring.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcRxClass
class OdRxClass;
class NRXDBGATE_EXPORT NcRxClass : public NcRxObject
{
	NCRX_DECLARE_MEMBERS(NcRxClass);

public:
	NcRxClass(OdRxObject* _object);
	NcRxClass(NCHAR *name, OdRxObject* _object);

public:
	typedef OdRxClass  native_class;

public:
	virtual NcRxObject* queryX(const NcRxClass* protocol) const;

	virtual NcRxObject* clone() const
	{
		return NULL;
	}

	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source)
	{
		AssertNotImplemented(NcRxClass::copyFrom);
		return Nano::eNotImplementedYet;
	}

  virtual NRX::Boolean isEqualTo(const NcRxObject* other) const;
  virtual NcRx::Ordering comparedTo(const NcRxObject* other) const;

public:
	virtual NcRxObject* addX(NcRxClass* protocol, NcRxObject* handler);
	virtual NcRxObject* delX(NcRxClass* protocol);
	virtual NcRxObject* getX(const NcRxClass*); // = 0;

	virtual NcRxObject* create();

	virtual LPCTSTR appName() const;
	virtual ncAppNameChangeFuncPtr appNameCallbackPtr() const; // = 0;
	virtual LPCTSTR dxfName() const;
	virtual LPCTSTR name() const;

	virtual void getClassVersion(int& dwgVer, int& maintVer) const;

	virtual int proxyFlags() const;

	virtual bool isDerivedFrom(const NcRxClass* rxclass) const;

	virtual NcRxClass* myParent() const;

public:

	void AssignConstructor(NcRxConsFunc cons);
	/*
	Remove platform object
	*/
	void remove();

public:
	static NcRxClass* attach(const OdRxClass* _rxclass);
	static NcRxClass* find(LPCTSTR name);

	/*
	Register class in class tree
	Parameters:
		name [in]   - class name
		parent [in] - parent class
		major [in]  - class major version
		minor [in]  - class minor version
		flags [in]  - flags
		_cons [in]  - platform constructor address
		cons [in]   - wrapper constructor address
		dxf [in]    - class dxf name
		app [in]    - module name

	Return value:
		Pointer to RxClass of registered object
	*/
	static NcRxClass* create(const NCHAR* name, const NCHAR* parent, int major, int minor, int flags = 0,
	                         NcOdRxConsFunc _cons = NULL, NcRxConsFunc cons = NULL, const NCHAR* dxf = NULL,
	                         const NCHAR* app = NULL);
	static NcString getNormalizedClassName(const NCHAR* name);

public:
	OdRxClass* native() const;

protected:
	NcRxConsFunc     m_NcRxObjCons;

	mutable NcString m_class_name;
};

NRXDBGATE_EXPORT void ncrxBuildClassHierarchy();

NRXDBGATE_EXPORT NcRxClass* NewRxClass(const NCHAR* name, const NCHAR* parent, int major, int minor, int flags = 0,
                                       NcOdRxConsFunc _cons = NULL, NcRxConsFunc cons = NULL, const NCHAR* dxf = NULL,
                                       const NCHAR* app = NULL);
NRXDBGATE_EXPORT void deleteNcRxClass(NcRxClass* rxclass);

////////////////////////////////////////////////////////////////////////////////////////////////////
// NcCmEntityColor
class OdCmEntityColor;
class NRXDBGATE_EXPORT NcCmEntityColor
{
public:
	enum Color { kRed,
	             kGreen,
	             kBlue
	};

	// Color Method.
	enum ColorMethod {   kByLayer =0xC0, 
	                     kByBlock,
	                     kByColor,
	                     kByACI,
	                     kByPen,
	                     kForeground,
	                     kLayerOff,
	                     // Run-time states
	                     kLayerFrozen,
	                     kNone
	};

	enum ACIcolorMethod {kACIbyBlock    = 0,
	                     kACIforeground = 7,
	                     kACIbyLayer    = 256,
	                     // Run-time states
	                     kACIclear      = 0,    
	                     kACIstandard   = 7,
	                     kACImaximum    = 255,
	                     kACInone       = 257,
	                     kACIminimum    = -255,
	                     kACIfrozenLayer= -32700
	};

	// Blue, green, red, and Color Method (byBlock, byLayer, byColor).
	// Is stored that way for better performance. 
	union RGBM {
	    NRX::UInt32    whole;
	    NRX::Int16     indirect;
	    struct {
	       NRX::UInt8 blue, 
	                  green, 
	                  red, 
	                  colorMethod;
	   };
	};

	NcCmEntityColor();
	NcCmEntityColor(const NcCmEntityColor& color);
	NcCmEntityColor(const ColorMethod method);
	NcCmEntityColor(const NRX::UInt8 red, const NRX::UInt8 green, const NRX::UInt8 blue);

	explicit NcCmEntityColor(const OdCmEntityColor& color);
	~NcCmEntityColor();

public:
	operator OdCmEntityColor() const;

	NcCmEntityColor& operator=(const NcCmEntityColor& color);
	NcCmEntityColor& operator=(const OdCmEntityColor& color);

	bool operator==(const NcCmEntityColor& color) const;
	bool operator!=(const NcCmEntityColor& color) const;

public:
	Nano::ErrorStatus setColorMethod(const ColorMethod method);
	ColorMethod colorMethod() const;

	Nano::ErrorStatus setColor(const NRX::UInt32 color);
	NRX::UInt32 color() const;

	Nano::ErrorStatus setColorIndex(const NRX::Int16 index);
	NRX::Int16 colorIndex() const;

	Nano::ErrorStatus setLayerIndex(const NRX::Int16 index);
	NRX::Int16 layerIndex() const;

	Nano::ErrorStatus setPenIndex(const NRX::UInt16 index);
	NRX::UInt16 penIndex() const;

public:
	Nano::ErrorStatus setRGB(const NRX::UInt8 red, const NRX::UInt8 green, const NRX::UInt8 blue);
	Nano::ErrorStatus setRed(const NRX::UInt8 red);
	Nano::ErrorStatus setGreen(const NRX::UInt8 green);
	Nano::ErrorStatus setBlue(const NRX::UInt8 blue);

	NRX::UInt8 red() const;
	NRX::UInt8 green() const;
	NRX::UInt8 blue() const;

public:
	bool isByColor() const;
	bool isByLayer() const;
	bool isByBlock() const;
	bool isByACI() const;
	bool isByPen() const;
	bool isForeground() const;
	bool isLayerOff() const;

public:
	bool isLayerFrozen() const;
	bool isNone() const;
	bool isLayerFrozenOrOff() const;

public:
	NRX::UInt32 trueColor() const;
	NRX::UInt8 trueColorMethod() const;
	Nano::ErrorStatus setTrueColor();
	Nano::ErrorStatus setTrueColorMethod();

public:
	static Nano::ErrorStatus setColorMethod(RGBM* rgbm, const ColorMethod method);
	static ColorMethod colorMethod(const RGBM* rgbm);

	static Nano::ErrorStatus setColor(RGBM* rgbm, const NRX::UInt32 color);
	static NRX::UInt32 color(const RGBM* rgbm);

	static Nano::ErrorStatus setColorIndex(RGBM* rgbm, const NRX::Int16 index);
	static NRX::Int16 colorIndex(const RGBM* rgbm);

	static Nano::ErrorStatus setLayerIndex(RGBM* rgbm, const NRX::Int16 index);
	static NRX::Int16 layerIndex(const RGBM* rgbm);

	static Nano::ErrorStatus setPenIndex(RGBM* rgbm, const NRX::UInt16 index);
	static NRX::UInt16 penIndex(const RGBM* rgbm);

public:
	static Nano::ErrorStatus setRGB(RGBM* rgbm, const NRX::UInt8 red, const NRX::UInt8 green,
	                                const NRX::UInt8 blue);
	static Nano::ErrorStatus setRed(RGBM* rgbm, const NRX::UInt8 red);
	static Nano::ErrorStatus setGreen(RGBM* rgbm, const NRX::UInt8 green);
	static Nano::ErrorStatus setBlue(RGBM* rgbm, const NRX::UInt8 blue);

	static NRX::UInt8 red(const RGBM* rgbm);
	static NRX::UInt8 green(const RGBM* rgbm);
	static NRX::UInt8 blue(const RGBM* rgbm);

public:
	static bool isByColor(const RGBM* rgbm);
	static bool isByLayer(const RGBM* rgbm);
	static bool isByBlock(const RGBM* rgbm);
	static bool isByACI(const RGBM* rgbm);
	static bool isByPen(const RGBM* rgbm);
	static bool isForeground(const RGBM* rgbm);
	static bool isLayerOff(const RGBM* rgbm);

public:
	static bool isLayerFrozen(const RGBM* rgbm);
	static bool isNone(const RGBM* rgbm);

public:
	static NRX::UInt32 trueColor(const RGBM* rgbm);
	static NRX::UInt8 trueColorMethod(const NRX::Int16);
	static Nano::ErrorStatus setTrueColor(RGBM* rgbm);
	static Nano::ErrorStatus setTrueColorMethod(RGBM* rgbm);

	static NRX::UInt32 lookUpRGB(const NRX::UInt8 colorIndex);
	static NRX::UInt8 lookUpACI(const NRX::UInt8 red, const NRX::UInt8 green,
	                            const NRX::UInt8 blue);

protected:
	RGBM m_rgbm;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// NcCmColorBase
class OdCmColorBase;
class NRXDBGATE_EXPORT NcCmColorBase
{
public:
	NcCmColorBase(OdCmColorBase* _object);

public:
	virtual ~NcCmColorBase();

public:
	virtual NcCmEntityColor::ColorMethod colorMethod() const;
	virtual Nano::ErrorStatus setColorMethod(NcCmEntityColor::ColorMethod method);

	virtual bool isByColor() const;
	virtual bool isByLayer() const;
	virtual bool isByBlock() const;
	virtual bool isByACI() const;
	virtual bool isByPen() const;
	virtual bool isForeground() const;

	virtual NRX::UInt32 color() const;
	virtual Nano::ErrorStatus setColor(NRX::UInt32 color);

	virtual Nano::ErrorStatus setRGB(NRX::UInt8 red, NRX::UInt8 green, NRX::UInt8 blue);
	virtual Nano::ErrorStatus setRed(NRX::UInt8 red);
	virtual Nano::ErrorStatus setGreen(NRX::UInt8 green);
	virtual Nano::ErrorStatus setBlue(NRX::UInt8 blue);
	virtual NRX::UInt8 red() const;
	virtual NRX::UInt8 green() const;
	virtual NRX::UInt8 blue() const;

	virtual NRX::UInt16 colorIndex() const;
	virtual Nano::ErrorStatus setColorIndex(NRX::UInt16 index);
	virtual NRX::UInt16 penIndex() const;
	virtual Nano::ErrorStatus setPenIndex(NRX::UInt16 index);

	virtual Nano::ErrorStatus setNames(const NCHAR* color, const NCHAR* book = NULL);
	virtual const NCHAR* colorName() const;
	virtual const NCHAR* bookName() const;
	virtual const NCHAR* colorNameForDisplay();
	virtual bool hasColorName() const;
	virtual bool hasBookName() const;

public:
	OdCmColorBase* native() const;

protected:
	OdCmColorBase* m_pNative;

	//mutable OdString m_colorNameForDisplay;
	//mutable OdString m_colorName;
	//mutable OdString m_bookName;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// NcCmColor
class OdCmColor;
class NRXDBGATE_EXPORT NcCmColor : public NcCmColorBase
{
public:
	NcCmColor();
	NcCmColor(const NcCmColor& color);
	NcCmColor(const NcCmColorBase& color);

	NcCmColor(const OdCmColor* _color);

	NRX::UInt16 colorIndex() const;   // +Overload

public:
	typedef OdCmColor  native_class;

public:
	NcCmColor& operator=(const NcCmColor& color);
	NcCmColor& operator=(const NcCmColorBase& color);

	bool operator==(const NcCmColor& color) const;
	bool operator!=(const NcCmColor& color) const;
	bool operator==(const NcCmColorBase& color) const;
	bool operator!=(const NcCmColorBase& color) const;

	Nano::ErrorStatus getDescription(NCHAR*& description) const;
	Nano::ErrorStatus getExplanation(NCHAR*& explanation) const;

	bool isNone() const;

	NcCmEntityColor entityColor() const;
	int dictionaryKeyLength() const;
	void getDictionaryKey(NCHAR* key) const;
	void getDictionaryKey(NCHAR* key, size_t nLen) const;
	Nano::ErrorStatus setNamesFromDictionaryKey(const NCHAR* key);

public:
	Nano::ErrorStatus dwgIn(NcDbDwgFiler* filer);
	Nano::ErrorStatus dwgOut(NcDbDwgFiler* filer) const;

	Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer, int offset);
	Nano::ErrorStatus dxfOut(NcDbDxfFiler* filer, int offset) const;

	Nano::ErrorStatus audit(NcDbAuditInfo* audit_info);

	Nano::ErrorStatus serializeOut(void* pBuff, int* pBuflen, NcDb::NcDbDwgVersion ver = NcDb::kDHL_CURRENT) const;
	Nano::ErrorStatus serializeIn(const void* pBuff, int* pBuflen);

	NcCmComplexColor* complexColor() const;
	void setComplexColor(NcCmComplexColor* complex);

	Nano::ErrorStatus dwgInAsTrueColor(NcDbDwgFiler* filer);
	Nano::ErrorStatus dwgOutAsTrueColor(NcDbDwgFiler* filer) const;

	static const NRX::UInt16 MaxColorIndex;

public:
	static NcCmColorBase* attach(OdCmColorBase* _object);

public:
	OdCmColor* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbHandle
class OdDbHandle;
class NRXDBGATE_EXPORT NcDbHandle
{
public:
	NcDbHandle();
	explicit NcDbHandle(const NcDbHandle& src);
	NcDbHandle(int lo, int hi);
	explicit NcDbHandle(const NCHAR* value);
	explicit NcDbHandle(const NRX::UInt64* val);
	NcDbHandle(const NRX::UInt64 &value);

	NcDbHandle(const OdDbHandle* value);

public:
	NcDbHandle& operator=(const NcDbHandle& value);
	NcDbHandle& operator=(const NCHAR* value);
	NcDbHandle& operator=(NRX::UInt64);
	
	__declspec(deprecated("use more secure version getIntoAsciiBuffer(NCHAR* pBuf, size_t nBufLen)"))
		void getIntoAsciiBuffer(NCHAR* pBuf) const;
	bool getIntoAsciiBuffer(NCHAR* pBuf, size_t nBufLen) const;

	bool operator==(const NcDbHandle& value) const;
	bool operator!=(const NcDbHandle& value) const;

	void setNull();

	NRX::UInt32 low() const;
	NRX::UInt32 high() const;

	void setLow(NRX::UInt32 low);
	void setHigh(NRX::UInt32 high);

	bool isOne(void) const;

	int byte(NRX::UInt32 i) const;
	int compare(const NcDbHandle&) const;
	void copyFromOldType(const NRX::UInt8 hand[8]);
	void copyToOldType(NRX::UInt8 hand[8]) const;
	void decrement(void);
	void getValueBytes(NRX::UInt8*, NRX::UInt8*) const;
	void increment(void);
	bool isNull() const;

	operator NRX::UInt32() const;
	operator NRX::UInt64() const;
	operator OdDbHandle() const;

	NcDbHandle operator - (const NcDbHandle&) const;
	NcDbHandle operator + (const NcDbHandle&) const;
	NcDbHandle operator + (NRX::ULongPtr) const;
	NcDbHandle& operator++();
	NcDbHandle operator++(int);
	bool operator < (const NcDbHandle&) const;
	bool operator <= (const NcDbHandle&) const;
	bool operator > (const NcDbHandle&) const;
	bool operator >= (const NcDbHandle&) const;
	void print() const;
	int restZeros(int i) const;
	void setValueBytes(NRX::UInt8, const NRX::UInt8*);
	NcDbHandle slowOperatorPlus(const NcDbHandle&) const;

protected:
	NRX::UInt64 m_handle;
};


//////////////////////////////////////////////////////////////////////////
// NcHeapOperators
class NRXDBGATE_EXPORT NcHeapOperators {
};

//////////////////////////////////////////////////////////////////////////
// NcRxProtocolReactor
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcRxProtocolReactor : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcRxProtocolReactor);
};

//////////////////////////////////////////////////////////////////////////
// NcRxOverrule
class OdRxOverrule;
class NRXDBGATE_EXPORT NcRxOverrule : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcRxOverrule);
	
	typedef NcRxOverrule  wrapper_class;
	typedef OdRxOverrule  native_class;

public:
	NcRxOverrule();
	NcRxOverrule(OdRxObject* _object);
	virtual ~NcRxOverrule();

	virtual bool isApplicable(const NcRxObject* pOverruledSubject) const; //= 0;
	static Nano::ErrorStatus addOverrule(NcRxClass* pClass, NcRxOverrule* pOverrule, bool bAddAtLast = false);
	static Nano::ErrorStatus removeOverrule(NcRxClass* pClass, NcRxOverrule* pOverrule);
	static void setIsOverruling(bool bIsOverruling);
	static bool isOverruling(void);
	static bool hasOverrule(const NcRxObject* pSubject, NcRxClass* pOverruleClass);

public:
	OdRxOverrule* native() const;
};

#ifdef _tcslen
#undef _tcslen
#endif

#ifdef UNICODE
#define _tcslen nc_wcslen
#else
#define _tcslen nc_strlen
#endif

#define wcslen nc_wcslen
#define strlen nc_strlen

#if defined ASSERT
#define NcTcsLen_Assert ASSERT
#elif defined(assert)
#define NcTcsLen_Assert assert
#elif defined(_ASSERTE)
#define NcTcsLen_Assert _ASSERTE
#elif defined ATLASSERT
#define NcTcsLen_Assert ATLASSERT
#else
#define NcTcsLen_Assert(x)
#endif

__declspec(noinline) inline unsigned __stdcall nc_wcslen(const wchar_t * s)
{
	unsigned n = 0;
	while (*s != L'\0') {
		s++;
		n++;
		NcTcsLen_Assert(n < 0x7FFFFFFE);  // 2G-1 sanity check
	}
	return n;
}

__declspec(noinline) inline unsigned __stdcall nc_strlen(const char * s)
{
	unsigned n = 0;
	while (*s != '\0') {
		s++;
		n++;
		NcTcsLen_Assert(n < 0x7FFFFFFE);
	}
	return n;
}

#define NRX_START_ERRORSTATUS_WRAPPER()                     \
  try {

#define NRX_END_ERRORSTATUS_WRAPPER()                       \
  }                                                         \
  catch(const OdError& e){                                  \
    return (Nano::ErrorStatus)e.code();                     \
  }                                                         \
  return Nano::eOk;

#endif // __OPENDWG_CORE_H__

