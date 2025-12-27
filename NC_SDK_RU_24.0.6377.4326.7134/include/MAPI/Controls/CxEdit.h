#pragma once


#include "..\..\..\..\external\microsoft\tom.h"
#include "CxFtRef.h"
#include "IUniEntMon.h"


//////////////////////////////////////////////////////////////////////////
enum RtfTagEnum { kRtfNormal, kRtfUpper, kRtfLower, kRtfDivision, kRtfDivisionRev, kRtfGreek };


struct RtfTag
{
	RtfTagEnum TagType;
	TCHAR cSymbol;
	long nStart;
	long nEnd;
	long nMiddle;
	DWORD dwEffects;

	RtfTag() : nStart(0), nEnd(0), nMiddle(0) {}
	bool operator < (const RtfTag& op) { return nStart < op.nStart || (nStart == op.nStart && nEnd < op.nEnd); }
	bool operator > (const RtfTag& op) { return nStart > op.nStart || (nStart == op.nStart && nEnd > op.nEnd); }
};


// Код курсора
#define CXEDIT_CURSOR       ((TCHAR)(14))


// Информация о строке текста
struct FtLineBound {
	int iStart;          // индекс начала строки
	int iEnd;            // индекс конца строки
	double rLength;      // длина строки на чертеже, мм
};

typedef McsArray<FtLineBound, const FtLineBound&> FtLineBoundArray;


//////////////////////////////////////////////////////////////////////////
struct
__declspec(uuid("{7E6DFDF5-CDD0-43b4-AF6B-4A6CBE00E61B}"))
McTextConverter : public IMcTextConverter
{
	// IMcUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvobj);

	// IMcTextConverter
	virtual McsStringA GetTextA();
	virtual McsStringW GetTextW();
	virtual McsStringA GetTextRawA();
	virtual McsStringW GetTextRawW();
	virtual McsStringA GetTextWithSymbolsA();
	virtual HRESULT SetTextA(LPCSTR Value);
	virtual HRESULT SetTextW(LPCWSTR Value);
	virtual HRESULT AddTextExW(LPCWSTR Value);
	virtual HRESULT AddTextExA(LPCSTR Value);	
	virtual HRESULT AddUnderlinedText(LPCTSTR Value);
	virtual HRESULT AddSubscript(LPCTSTR Value);
	virtual HRESULT AddSuperscript(LPCTSTR Value);
	virtual HRESULT AddDivision(LPCTSTR Upper, LPCTSTR Lower, BOOL Divider);
	virtual HRESULT AddSpecSymbol(WCHAR Value);
	virtual HRESULT AddNumber(double rNumber, double rTol = 1e-9);
	virtual HRESULT SetLineSpacing(double);
	virtual HRESULT SetUnderline(bool setul);
	virtual HRESULT SetStriked(bool bStrike);
	virtual HRESULT MakeSingleLine();
	virtual HRESULT SplitA(mcsStringArrayA& Result, LPCSTR lpszDelimiter);
	virtual HRESULT SplitW(mcsStringArrayW& Result, LPCWSTR lpszDelimiter);
	virtual int     FindA(LPCSTR strTextToFind, int nFromPos = 0, bool fMatchCase = true, bool fPattern = false);
	virtual int     FindW(LPCWSTR strTextToFind, int nFromPos = 0, bool fMatchCase = true, bool fPattern = false);
	virtual int     ReplaceA(LPCSTR lpszWhat, LPCSTR lpszWith, bool fCaseSensitive, bool fPattern);
	virtual int     ReplaceW(LPCWSTR mwWhat, LPCWSTR mwWith, bool fCaseSensitive, bool fPattern);
	virtual HRESULT FindFmt(DWORD dwEffect, long nValue = tomTrue, bool fReverse = false);
	virtual HRESULT ExpandFmt(DWORD dwEffect);
	virtual HRESULT Explode(const mcsText& srcText,
													mcsGeomEntArray& Fragments,
													mcsBoundBlock* pBounds = NULL);
	virtual HRESULT ConvertFromNative(MCS_PlatformId plmFrom, long nFlags);
	virtual McsString ConvertToNative(double rScale, DWORD Flags);
	virtual HRESULT SetNativeTextStyleName(LPCTSTR pszTextStyleName);
	virtual McsStringW ToXHTML();
	virtual HRESULT FromXHTML(LPCWSTR swzHypertext);

	virtual HRESULT GetTextHeight(int& ResultPixels, int WidthPixels = 0);
	
	virtual IMcTextRefPtr refGetCurrent(IMcObject* pOwner);
	virtual HRESULT refGetAll(IMcTextRefPtrArray& Result, IMcObject* pOwner);

	virtual HRESULT StartTransaction();
	virtual HRESULT EndTransaction(BOOL fNotify = FALSE);

	virtual HRESULT Attach(HWND hRichEdit);
	virtual IUnknownPtr ole();
	virtual HWND hwnd() { return hwnd(true); }

	// to implement
	virtual HRESULT Explode(const McsEntityGeometry& srcText,
													mcsGeomEntArray& Fragments,
													mcsBoundBlock* pBounds = NULL) { return E_NOTIMPL; }
	virtual HRESULT Draw(HDC hDC, RECT* pBounds);

	// McTextConverter
	virtual HRESULT _Explode(const mcsText& srcText,
		mcsGeomEntArray& Fragments,
		mcsBoundBlock* pBounds = NULL);
	McTextConverter();
	McTextConverter(HWND hEdit);	
	virtual ~McTextConverter();
	void Clear();

	McsStringW SearchForTags(McsArray<RtfTag,const RtfTag&>& Tags);
	void SubExplode(ITextRange* pTR, PCWSTR pwOriginal, double rHeight, double& rW, double& rH,
									mcsPoint& ptCursor, PCWSTR pwStart, PCWSTR pwEnd = NULL);
	void AddTextFragment(PCWSTR pwOriginal, PCWSTR pwText, PCWSTR pwEnd, double& rW, double& rH,
											 mcsPoint& ptCursor);
	int MarkLine(double rWidth, const mcsPoint& ptCursor);
	// Выравниваем строки по горизонтали
	void MoveLines(double rTotalWidth,           // габаритная ширина блока геометрии
								 McsHorizTextAlignEnum Align); // как выравнивать
	// Вписываем все строки в ширину ячейки
	void InsribeLines(double rWidth);
	void OpenCaret(const mcsPoint& ptCursor);
	void CloseCaret(const mcsPoint& ptCursor);
	void AddTextFragment(McsString& str, CHARFORMAT& fmt);
	HRESULT ConvertFromAcad(BOOL fForMText);
	bool IsWrapPosition(double& x, PCWSTR& pwStart, PCWSTR pwEnd, PCWSTR pwLimit);
	HWND hwnd(bool fCreate);
	bool GetSimple();
	void SetSimple(bool Value = true);
	McsString MakeSpecSymbolsUNC(LPCWSTR swStart, LPCWSTR swEnd);
	static IMcTextStylePtr getStyle(McsString msName);

	virtual HRESULT SetFractionTextSize(FractionTextSize eValue) override;
	virtual FractionTextSize GetFractionTextSize() override;

public:
	DWORD m_dwFlags;                    // флажки состояния
		#define TCF_RAGNE_SELECTED        0x00000001    // Выделена область текста (для Explode)
		#define TCF_CARET_OPENED          0x00000002    // Курсор внутри нашей селекции (для Explode)
		#define TCF_CARET_EXISTS          0x00000004    // В тексте есть курсор (для Explode)
		#define TCF_OWNED_CONTROL         0x80000000    // Удалять m_pre в деструкторе
		#define TCF_UNDERLINED            0x40000000    // Курсор в подчеркнутом тексте (для Explode)
		#define TCF_OVERLINED             0x20000000    // Курсор в надчеркнутом тексте (для Explode)
		#define TCF_SPECSYMBOLS           0x10000000    // В тексте есть спецсимволы (для Explode)
		#define TCF_WORDWRAP              0x08000000    // Переносить по словам (для Explode)
		#define TCF_RAWTEXT               0x04000000    // Текст не содержит форматирования
		#define TCF_CUSTOM_FONT           0x02000000    // Гарнитура отличается от установленой в стиле
		#define TCF_HIDDEN                0x01000000    // Курсор внутри скрытого текста (для Explode)
		#define TCF_STYLE_OVERRIDE        0x00800000    // Цвет примитивов после Explode отличается от цвета текста
	HFONT m_Font;                       // шрифт контрола
	McsStringW m_mwContent;             // содержимое, если нет кодов форматирования

	// Заменить одним указателем на структуру
	struct _ExplodeData {
		IMcTextStylePtr m_pStyle;         // стиль текста
		double m_rAngle;                  // угол наклона текста
		mcsGeomEntArray* m_pGeometry;     // результат разбивки
		int m_idxCursor;                  // позиция курсора
		FtLineBoundArray m_Markers;       // маркеры конца строки
		double m_rWidth;                  // ширина колонки
		CxFtRefPtr m_pRef;                // ссылка, в которой стоит курсор (для Explode)
		int m_iPosCorrection;             // количество попавшихся в тексте курсоров

		_ExplodeData() : m_idxCursor(-1), m_rAngle(0), m_pGeometry(NULL), m_rWidth(0), m_iPosCorrection(0) {}
	}* m_pXD;
};

typedef MComQIPtr<McTextConverter> McTextConverterPtr;
//static const GUID CLSID_McTextConverter = __uuidof(McTextConverter);

struct CxSink : public IUniEntMonitorSink
{
public:
  virtual void ActiveEnt(const EM_Entity& ent_in, bool& fHighlight);
	HRESULT Execute(IMcEntity* pEnt);
protected:
	IMcDbEntityPtr m_pEnt;
	mcsPoint m_ptLast;
};


//////////////////////////////////////////////////////////////////////////
struct __declspec(uuid("{C5BD6568-0738-4e6f-9A75-CE97916D0854}")) McGDIStyle;
static const GUID CLSID_McGDIStyle = __uuidof(McGDIStyle);
typedef MComQIPtr<McGDIStyle> McGDIStylePtr;

struct McGDIStyle : public IMcTextStyle
{
// Base
	DECLARE_OBJ_NEWDEL;
	M_DECLARE_SPY(_T("McGDIStyle"), false);

// IUnknown

// IMcObject
	IMCS_STD_METHOD_DEFINITION(McGDIStyle, IMcTextStyle);

// IMcTextStyle
	virtual LPCTSTR getName()                                                                         { return m_msStyle; }
  virtual LPCTSTR getFontName()                                                                     { return m_lf.lfFaceName; }
	virtual bool    isTrueType()                                                                      { return true; }
	virtual bool    isItalic()                                                                        { return m_lf.lfItalic != 0; }
	virtual bool    isBold()                                                                          { return m_lf.lfWeight > FW_NORMAL; }
	virtual double  getHeight()                                                                       { return m_lf.lfHeight; }
	virtual double  getOblique()                                                                      { return m_lf.lfItalic ? 10 : 0; }
	virtual double  getXScaling();
	virtual int getCharset() { return m_lf.lfCharSet; }
	virtual int getPitchAndFamily() { return m_lf.lfPitchAndFamily; }
	virtual bool isBackward() override
		{ return false; }
	virtual bool isUpsideDown() override
		{ return false; }
	virtual bool isVertical() override
		{ return false; }

	virtual void setHeight(double r);
	virtual void setOblique(double r);
	virtual void setXScaling(double r);

  // Инициализация TrueType текстового стиля
  virtual void set(LPCTSTR stName, LPCTSTR stFontName, bool isItalic, bool isBold, int iCharset, int iPitchAndFamily);
  // Инициализация векторного (shx) текстового стиля
	virtual void set(LPCTSTR stName, LPCTSTR stFontName)                                              { MCSASSERTE(_T("Not implemented")); }

  virtual mcsPoint2d GetMTextBox(LPCTSTR stText, double width = 0);
  virtual double GetDTextLength(LPCTSTR stText, double rDirection = 0);

	virtual double  getRealOblique()                                                                  { return m_lf.lfItalic ? 10 : 0; }
	virtual double  getRealXScaling();

	virtual HRESULT Update()
		{ return E_NOTIMPL; }

// McGDIStyle
	McGDIStyle();
	virtual ~McGDIStyle();

	HRESULT Init(McsString msStyle);
	HRESULT InitIndirect(LPLOGFONT plf);
	HRESULT Validate();

	HDC       m_hDC;
	LOGFONT   m_lf;
	bool      m_fDirty;
	McsString m_msStyle;
};


//////////////////////////////////////////////////////////////////////////
// thread depended HWND storage
struct TlsHWND
{
	HWND get(LPVOID);
	BOOL put(LPVOID, HWND);
	BOOL Init(DWORD dwReason);

	TlsHWND() : m_dwIndex(-1) {}
	
protected:
	DWORD m_dwIndex;
};

extern TlsHWND gTlsHWND;


//////////////////////////////////////////////////////////////////////////
bool IsOurText(LPCSTR str);
bool IsOurText(LPCWSTR str);


//////////////////////////////////////////////////////////////////////////
// CxFtEdit command identifiers
#define ID_COPY             40120             // Copy to clipboard
#define ID_CUT              40121             // Cut to clipboard
#define ID_PASTE            40122             // Paste from clipboard
// Special symbols
#define ID_DIAMETER         40123
#define ID_DEGREE           40124
#define ID_PLUSMINUS        40125
#define ID_PARAGRAPH        40126
#define ID_TILDA            40127
#define ID_OPEN_BRACKET     40128
#define ID_CLOSE_BRACKET    40129
#define ID_NUMBER           40130
#define ID_GRADIENT_LEFT    40131
#define ID_GRADIENT_RIGHT   40132
#define ID_TAPER_LEFT       40133
#define ID_TAPER_RIGHT      40134
#define ID_SUBSCRIPT        40135             // Toggle subscipt
#define ID_SUPERSCRIPT      40136             // Toggle superscript
#define ID_SELALL           40137             // Select all
#define ID_HISTORY_CLEAR    40138             // Clear history
#define ID_UNDO             40139             // Undo
#define ID_DELETE           40140             // Delete selection
#define ID_DIVISION         40141             // Insert division
#define ID_RECENT_APPEND    40142             // Append to recent
#define ID_RECENT_CLEAR     40143             // Clear recent list
#define ID_REDO             40144             // Redo
#define ID_MEASURE          40145             // Pick from drawing
#define ID_SYMBOL_TABLE     40146             // Open symbol table
// Field commands
#define ID_FIELD_ADD        40147             // Create new field and insert at cursor
#define ID_FIELD_EDIT       40148             // Edit field at cursor
#define ID_FIELD_APPEND     40149             // Append field to templates
#define ID_TEMPLATE_CLEAR   40150             // Clear templates
#define ID_TEMPLATE_APPEND  40151             // Add template based on current text
// Reference commands
#define ID_REFTXT_UPDATE    40152             // Update reference value
#define ID_REFTXT_DETACH    40153             // Make static text from reference value
#define ID_REF_CODE         40154             // Show/hide reference code
#define ID_REFOBJ_ZOOM      40155             // Zoom object to text height
#define ID_REFOBJ_STYLE_OVERRIDE 40156        // Отображать оригинальные цвет, вес и т.п. геометрии ссылки.
#define ID_REFOBJ_EDIT      40157             // Edit object
#define ID_REF_REMOVE       40158             // Completely remove current reference
#define ID_REFOBJ_INSERT    40159             // Insert object from drawing
#define ID_REFOBJ_EXTRACT   40160             // Copy embedded object into drawing
#define ID_REFTXT_FIND      40161             // Pan to source object
#define ID_RTF2HTML         40162             // Export into html file
#define ID_REFOBJ_TOP       40163
#define ID_REFOBJ_CENTER    40164
#define ID_REFOBJ_BOTTOM    40165
#define ID_REF_FORMULA      40166
#define ID_ANCHOR_GO        40167             // Go to hyperlink
#define ID_ANCHOR_EDIT      40168             // Edit hyperlink address
#define ID_ANCHOR_CREATE    40169             // Create new hyperlink
#define ID_NORMACS_NUMBER   40170             // Search in NormaCS identifiers
#define ID_NORMACS_TITLE    40171             // Search in NormaCS titles
#define ID_NORMACS_TEXT     40172             // Search in NormaCS topics
#define ID_RTFCOPY          40173             // Copy rtf to clipboard (diagnostic)
#define ID_REFPRJ_INSERT   40174              // Create reference to a album node
#define ID_REFPRJ_FIND      40175             // Find property source
#define ID_GET_TEXT         40176             // Pick text from drawing
#define ID_INSERT_BIG_BRACKETS 40177          // Вставить большие скобки
#define ID_MATERIAL_INSERT  40178             // Вставить материал
#define ID_FTS_DEFAULT      40179             // Размер текста индексов и дробей по умолчанию
#define ID_FTS_BASIC        40180             // Размер текста индексов и дробей по умолчанию
#define ID_FTS_ONESTEPLESS  40181             // Размер текста индексов и дробей по умолчанию
#define ID_NORMACS_TERM     40182             // Search in NormaCS terms
// Spell check
#define ID_SPELL            40199

#define ID_HISTORY          40200             // First item of history list
#define ID_RECENT           (ID_HISTORY+100)  // First item of recent list
#define ID_KEYWORDS         (ID_RECENT+100)   // First item of keywords list
#define ID_TEMPLATES        (ID_KEYWORDS+100) // First item of field templates

/*
//------------------------------------------------------------------------
struct McsFtStringW;

struct IMcFtLinkManager : public IUnknown
{
	virtual HRESULT Save(OUT McsFtStringW& ftSaveTo) = 0;
	virtual IMcTextRefPtr GetRefAt(IN int iIndex) = 0;
	virtual HRESULT GetAllRefs(OUT McsArray<IMcTextRefPtr, IMcTextRef*>& Result) = 0;
};
*/
