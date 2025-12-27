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
#include "core.h"
#include "nrxdbgate_impexp.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcString
class OdString;
class NcDbHandle; 
typedef unsigned short NcChar;
typedef unsigned short NcUChar;
class NRXDBGATE_EXPORT NcString
{
public:
	//ODRX_HEAP_OPERATORS();TODO

	const static NcString kEmpty;

public:
	NcString();
	NcString(char ch);
	NcString(wchar_t wch);
	NcString(const char *psz);
	NcString(const wchar_t *pwsz);
	NcString(const NcString & ncs);
	NcString(const OdString& src);

	enum {
		kAppRes   = 0x0001,
		kSigned   = 0x0002,
		kUnSigned = 0x0003,
		kHex      = 0x0004
	};

	NcString(int nCtorFlags, unsigned nArg);
	NcString(const NcDbHandle &h);
	NcString(HINSTANCE hDll, unsigned nId);

	~NcString();

	const    char * kszPtr() const;
	const wchar_t * kwszPtr() const;
	const wchar_t * constPtr() const;
	const wchar_t * kTCharPtr() const;
	const NCHAR * kNCharPtr() const;
	const NcChar* kOdCharPtr() const;

	operator const char * () const;
	operator const wchar_t * () const;

	bool isEmpty() const;
	unsigned length() const;
	unsigned tcharLength() const;
	bool isAscii() const;

	enum {
		kParseZero    = 0,
		kParseMinus1  = 0x01,
		kParseAssert  = 0x02,
		kParseExcept  = 0x04,
		kParseNoEmpty = 0x08,
		kParseDefault = (kParseAssert | kParseZero)
	};

	int asDeci(int nFlags = kParseDefault) const;
	int asHex (int nFlags = kParseDefault) const;
	unsigned int asUDeci(int nFlags = kParseDefault) const;
	unsigned int asUHex (int nFlags = kParseDefault) const;
	__int64 asDeci64(int nFlags = kParseDefault) const;
	__int64 asHex64 (int nFlags = kParseDefault) const;
	NRX::UInt64 asUDeci64(int nFlags = kParseDefault) const;
	NRX::UInt64 asUHex64 (int nFlags = kParseDefault) const;
	NcDbHandle asNcDbHandle(int nFlags = kParseDefault) const;

	int find(NCHAR ch) const;
	int find(const NCHAR *psz) const;
	int find(const NcString & ncs) const;
	int find(NcChar searchChar) const;
	int find(NcChar searchChar, int startIndex) const;
	int find(const NcChar* searchString) const;
	int find(const NcChar* searchString, int startIndex) const;
	int findOneOf(const NCHAR *psz) const;
	int findRev(NCHAR ch) const;
	int findRev(const NCHAR *psz) const;
	int findOneOfRev(const NCHAR *psz) const;
	int findRev(const NcString & ncs) const;
	int reverseFind(NcChar searchChar) const;
	int reverseFind(NcChar searchChar, int startIndex) const;
	int findOneOf(const NcChar* charSet) const;

	NcString mid(int nStart, int nNumChars) const;
	NcString substr(int numChars) const;
	NcString substr(int nStart, int nNumChars) const;
	NcString substrRev(int numChars) const;

	NcString & assign(char ch);
	NcString & assign(wchar_t wch);
	NcString & assign(const char *psz);
	NcString & assign(const wchar_t *pwsz);
	NcString & assign(const NcString & ncs);
	NcString & assign(const NcDbHandle & h);

	NcString & operator = (char ch);
	NcString & operator = (wchar_t wch);
	NcString & operator = (const char *psz);
	NcString & operator = (const wchar_t *pwsz);
	NcString & operator = (const NcString & ncs);
	NcString & operator = (const OdString * ncs);
	NcString & operator = (const NcDbHandle & h);

	NcString & setEmpty();
	bool loadString(unsigned nId);

	bool loadString(HINSTANCE hDll, unsigned nId);

	void format (const NCHAR *pszFmt, ...);
	void formatV(const NCHAR *pszFmt, va_list args);
	NcString & operator += (char ch);
	NcString & operator += (wchar_t wch);
	NcString & operator += (const char * psz);
	NcString & operator += (const wchar_t * pwsz);
	NcString & operator += (const NcString & ncs);
	NcString & append(char ch);
	NcString & append(wchar_t wch);
	NcString & append(const char *psz);
	NcString & append(const wchar_t *pwsz);
	NcString & append(const NcString & ncs);

	NcString operator + (char ch) const;
	NcString operator + (wchar_t wch) const;
	NcString operator + (const char * psz) const;
	NcString operator + (const wchar_t * pwsz) const;
	NcString operator + (const NcString & ncs) const;
	NcString concat(char ch) const;
	NcString concat(wchar_t wch) const;
	NcString concat(const char * psz) const;
	NcString concat(const wchar_t * pwsz) const;
	NcString concat(const NcString & ncs) const;
	NcString precat(NCHAR ch) const;
	NcString precat(const char * psz) const;
	NcString precat(const wchar_t * psz) const;
	int  compare(wchar_t wch) const;
	int  compare(const char *psz) const;
	int  compare(const wchar_t *pwsz) const;
	int  compare(const NcString & ncs) const;
	int  compare(const NcChar* otherString) const;
	int  compareNoCase(wchar_t wch) const;
	int  compareNoCase(const char *psz) const;
	int  compareNoCase(const wchar_t *pwsz) const;
	int  compareNoCase(const NcString & ncs) const;
	bool operator == (wchar_t wch) const;
	bool operator == (const char *psz) const;
	bool operator == (const wchar_t *pwsz) const;
	bool operator == (const NcString & ncs) const;
	bool operator != (wchar_t wch) const;
	bool operator != (const char *psz) const;
	bool operator != (const wchar_t *pwsz) const;
	bool operator != (const NcString & ncs) const;
	bool operator >  (wchar_t wch) const;
	bool operator >  (const char *psz) const;
	bool operator >  (const wchar_t *pwsz) const;
	bool operator >  (const NcString & ncs) const;
	bool operator >= (wchar_t wch) const;
	bool operator >= (const char *psz) const;
	bool operator >= (const wchar_t *pwsz) const;
	bool operator >= (const NcString & ncs) const;
	bool operator <  (wchar_t wch) const;
	bool operator <  (const char *psz) const;
	bool operator <  (const wchar_t *pwsz) const;
	bool operator <  (const NcString & ncs) const;
	bool operator <= (const char ch) const;
	bool operator <= (const wchar_t wch) const;
	bool operator <= (const char *psz) const;
	bool operator <= (const wchar_t *pwsz) const;
	bool operator <= (const NcString & ncs) const;

	int  match(const char *psz) const;
	int  match(const wchar_t *pwsz) const;
	int  match(const NcString & ncs) const;
	int  matchNoCase(const char *psz) const;
	int  matchNoCase(const wchar_t *pwsz) const;
	int  matchNoCase(const NcString & ncs) const;

#ifdef _AFX
	NcString(const CStringW &csw);
	NcString & operator =  (const CStringW &csw);
	NcString & operator += (const CStringW &csw);
	int  compare(const CStringW & csw) const;
	int  compareNoCase(const CStringW & csw) const;
	bool operator == (const CStringW & ) const;
	bool operator != (const CStringW & ) const;
	bool operator <  (const CStringW & ) const;
	bool operator <= (const CStringW & ) const;
	bool operator >  (const CStringW & ) const;
	bool operator >= (const CStringW & ) const;
	int  match(const CStringW & csw) const;
	int  matchNoCase(const CStringW & csw) const;
#else
	NcString& operator = (const OdString& ncs);
	NcString& operator += (const OdString& ods);
	int  compare(const OdString& ods) const;
	int  compareNoCase(const OdString& ods) const;
	bool operator == (const OdString& ods) const;
	bool operator != (const OdString& ods) const;
	bool operator >  (const OdString& ods) const;
	bool operator >= (const OdString& ods) const;
	bool operator <  (const OdString& ods) const;
	bool operator <= (const OdString& ods) const;
	int  match(const OdString& ods) const;
	int  matchNoCase(const OdString& ncs) const;
#endif


	int getLength() const;
	int getLengthA() const;
	void empty();

	NcChar getAt(int charIndex) const;
	NcChar operator[](int charIndex) const;

	void setAt(int charIndex, NcChar ch);

	const NcChar* c_str() const;
	operator const NcChar* () const;

	NcString& makeUpper();
	NcString& makeLower();
	NcString& makeReverse();

	NcString& trimRight();
	NcString& trimRight(NcChar whiteChar);
	NcString& trimRight(const NcChar* whiteChars);
	NcString& trimRight(const NcString& whiteChars);
	NcString& trimRight(const __wchar_t* whiteChars);

	NcString& trimLeft();
	NcString& trimLeft(NcChar whiteChar);
	NcString& trimLeft(const NcChar* whiteChars);
	NcString& trimLeft(const NcString& whiteChars);
	NcString& trimLeft(const __wchar_t* whiteChars);

	NcString mid(int startIndex) const;
	NcString left(int length) const;
	NcString right(int length) const;

	NcString spanIncluding(const NcChar* charSet) const;
	NcString spanIncluding(const NcString& charSet) const;
	NcString spanIncluding(const __wchar_t* charSet) const;

	NcString spanExcluding(const NcChar* charSet) const;
	NcString spanExcluding(const NcString& charSet) const;
	NcString spanExcluding(const __wchar_t* charSet) const;

	int replace(NcChar oldChar, NcChar newChar);
	int replace(const NcChar* oldString, const NcChar* newString);
	int replace(const NcString& oldString, const NcString& newString);
	int replace(const __wchar_t* oldString, const __wchar_t* newString);

	int remove(NcChar chRemove);
	int insert(int insertIndex, NcChar insertChar);
	int insert(int insertIndex, const NcChar* insertString);
	int insert(int insertIndex, const NcString& insertString);
	int insert(int insertIndex, const __wchar_t* insertString);

	int deleteChars(int deleteIndex, int count = 1);
	private:

#ifndef _WIN64
	enum {
		kObjSize    = 8,
		kMbArrSize  = 7,
		kUCArrSize  = 3,
		kPadArrSize = 3
	};
#else
	enum {
		kObjSize    = 16,
		kMbArrSize  = 15,
		kUCArrSize  = 7,
		kPadArrSize = 7
	};
#endif
	void clearAll();
private:
#ifdef _AFX
	int  match(const CString & str, const CString & strChars) const;
	int  matchMe(const CString & strChars) const;
	int  matchNoCaseMe(CString & strChars) const;
#else
	int  match(const OdString& str, const OdString& strChars) const;
	int  matchMe(const OdString& strChars) const;
	int  matchNoCaseMe(OdString& strChars) const;
#endif

public:
	OdString* native() const;
	OdString* native();

protected:
	OdString* m_pNative;
};

typedef NcArray<NcString, HostMemoryAllocator<NcString>> NcStringArray;
