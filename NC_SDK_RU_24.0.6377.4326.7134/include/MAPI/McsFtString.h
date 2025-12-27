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

#include "mcstypes.h"
#include <tom.h>
#include "MCSVariant.h"
#include "McsGeometry.h"


// Formating type for fragments of McsFtStringW
enum McsFtTypeEnum { kMcsFtNormal, kMcsFtUpper, kMcsFtLower, kMcsFtDivision };

// Part of McsFtString with the same formatting type
struct McsFtFragment {
	McsFtTypeEnum type;           // type of fragment
	McsStringW text;              // contents of fragment (numerator for divisions)
	McsStringW text_denominator;  // denominator part of division
	WCHAR chDivider;              // divider character of division 0
	  // '^' - no divider, simply stacked text
	  // '/' - horizontal line divides numerator from denominator
	UINT uFormatting;             // additional formmating codes (CFM_XXX combination,
	                              // see ms-help://MS.MSDNQTR.v80.en/MS.MSDN.v80/MS.WIN32COM.v10.en/shellcc/platform/commctls/richedit/richeditcontrols/richeditcontrolreference/richeditstructures/charformat2.htm
};

// Formatted string
struct McsFtStringW;

// Array of formatted strings
typedef McsArray<McsFtStringW, McsFtStringW> mcsFtStringArrayW;

// Dynamic text references manager
IMCS_DECL_INTERFACE(IMcFtLinkManager, "{22A8FDB9-D87D-4ce2-8BD1-9468E0926E29}");

// Array of text fragments
typedef McsArray<McsFtFragment, const McsFtFragment&> mcsFtFragmentArray;


//////////////////////////////////////////////////////////////////////////
struct McsFtStringW
{
	DECLARE_OBJ_NEWDEL;

// Construction
	McsFtStringW() {}
	MCTYP_API McsFtStringW(IN LPCWSTR lpszText, IN OPTIONAL int nLength = -1);
	MCTYP_API McsFtStringW(IN WCHAR ch, IN OPTIONAL int nRepeat = 1);
	// sequence \U+#### threats as wide character with code ####
	MCTYP_API McsFtStringW(IN LPCSTR lpszText);
	MCTYP_API McsFtStringW(const McsStringW& str);
	MCTYP_API ~McsFtStringW();

// Attributes & Operations
	MCTYP_API int   GetLength() const;
	MCTYP_API BOOL  IsEmpty() const;
	MCTYP_API void  Empty();

	MCTYP_API BOOL  IsFormatted() const;

	MCTYP_API WCHAR GetAt(int nIndex) const;
	MCTYP_API const WCHAR operator[](int nIndex) const;
	MCTYP_API void  SetAt(int nIndex, WCHAR ch);

	MCTYP_API McsStringA asFt() const;
	MCTYP_API McsStringW asRawW() const;
	// symbols not from current CP translated in \U+####
	MCTYP_API McsStringA asRawA() const;
	// convert format to platform-dependend
	// set MCS_PLM_UNDEFINED to take HTML
	// for MCS_PLM_ACAD formats MTEXT string
	MCTYP_API McsString  Export(IN MCS_PlatformId plm) const;
	// MCS_PLM_ACAD
	//   nFlags&1 means str is mtext formatted
	MCTYP_API HRESULT Import(IN McsString str, IN MCS_PlatformId plm, IN OPTIONAL long nFlags = 0);

// Operators
	MCTYP_API McsFtStringW& operator = (const McsStringW& stringSrc);
	MCTYP_API McsFtStringW& operator = (const McsFtStringW& stringSrc);
	MCTYP_API McsFtStringW& operator = (WCHAR ch);
	MCTYP_API McsFtStringW& operator = (LPCWSTR lpsz);
	MCTYP_API McsFtStringW& operator = (LPCSTR lpsz);
	MCTYP_API McsFtStringW& operator = (const MCSVariant& v);
	MCTYP_API operator MCSVariant() const;

	MCTYP_API McsFtStringW& operator += (const McsStringW& string);
	MCTYP_API McsFtStringW& operator += (const McsFtStringW& string);
	MCTYP_API McsFtStringW& operator += (WCHAR ch);
	MCTYP_API McsFtStringW& operator += (LPCWSTR lpsz);

	MCTYP_API friend McsFtStringW operator + (const McsFtStringW& string1, const McsStringW& string2);
	MCTYP_API friend McsFtStringW operator + (const McsFtStringW& string1, const McsFtStringW& string2);
	MCTYP_API friend McsFtStringW operator + (const McsFtStringW& string, WCHAR ch);
	MCTYP_API friend McsFtStringW operator + (const McsFtStringW& string, LPCWSTR lpsz);
	MCTYP_API friend McsFtStringW operator + (LPCWSTR lpsz, const McsFtStringW& string);

	MCTYP_API bool operator == (const McsFtStringW& op) const;
	MCTYP_API bool operator == (const LPCWSTR op) const;

// Simple sub-string extraction
	MCTYP_API McsFtStringW Mid(IN int nFirst, IN OPTIONAL int nCount = -1) const;
	MCTYP_API McsFtStringW Left(IN int nCount) const;
	MCTYP_API McsFtStringW Right(IN int nCount) const;

// Sub-string removing
	MCTYP_API McsFtStringW& RemoveLeft(IN int nCount);
	MCTYP_API McsFtStringW& RemoveRight(IN int nCount);
	MCTYP_API int Delete(IN int nIndex, IN OPTIONAL int nCount = 1);
// Sub-string insertion
	// functions returning position just after inserted substring
	MCTYP_API int Insert(IN int nIndex, IN WCHAR ch);
	MCTYP_API int Insert(IN int nIndex, IN McsFtStringW pstr);
	MCTYP_API int InsertSubscript(IN int nIndex, IN LPCWSTR lpstr);
	MCTYP_API int InsertSuperscript(IN int nIndex, IN LPCWSTR lpstr);
	MCTYP_API int InsertDivision(IN int nIndex, IN LPCWSTR lpNumerator, IN LPCWSTR lpDenominator, IN BOOL fSlash);

// Searching
	MCTYP_API int Compare(IN const McsFtStringW& str, IN OPTIONAL BOOL fMatchCase = TRUE) const;
	// returns start position of first found ocurrence
	MCTYP_API int Find(IN WCHAR ch, IN OPTIONAL int nStart = 0) const;
	MCTYP_API int Find(IN LPCWSTR strSub,
										 IN OPTIONAL int Mode = tomMatchCase,   // 0, tomMatchWord, tomMatchCase, tomMatchPattern
										 IN OPTIONAL int nStart = 0) const;
	// returns count of ocurrences
	MCTYP_API int Replace(IN WCHAR chOld, IN WCHAR chNew);
	MCTYP_API int Replace(IN LPCWSTR Old, IN McsFtStringW New, IN OPTIONAL int Mode = tomMatchCase);
	// in difference to McsString splits by exact delimiterString
	MCTYP_API int Split(IN LPCWSTR delimitersString, OUT mcsFtStringArrayW& subStrings) const;

// Streaming
	MCTYP_API bool Save(IMcsStream* pStream) const;
	MCTYP_API bool Load(IMcsStream* pStream);

// Advanced manipulation
	MCTYP_API HRESULT Draw(HDC hdc, LPRECT rc, DWORD dwFlags) const;
	MCTYP_API void    GetWindowText(IN HWND hRichOrEdit);
	MCTYP_API void    SetWindowText(IN HWND hRichOrEdit) const;

// Formatting
	IMcFtLinkManagerPtr GetLinks(
		IN OPTIONAL IMcObject* pHost = NULL            // owner of this text
	);
	void Explode(OUT mcsFtFragmentArray& Fragments);

protected:
	friend struct McFtLinkManager;

	void UpdateStrings();

	McsStringW m_str;
	McsStringA m_rtf;
};


//////////////////////////////////////////////////////////////////////////
MCTYP_API HRESULT FtStringExplode(IN const mcsText& strStr,
																	OUT mcsGeomEntArray& Result,
																	OUT OPTIONAL mcsBoundBlock* pBounds);

