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
#pragma pack(push, 8)

#include <comdef.h>
#include "McsTypes.h"

//
// Forward references and typedefs
//

struct __declspec(uuid("3f4daca7-160d-11d2-a8e9-00104b365c9f"))
/* LIBID */ __VBScript_RegExp_55;
struct __declspec(uuid("3f4daca0-160d-11d2-a8e9-00104b365c9f"))
/* dual interface */ IRegExp;
struct __declspec(uuid("3f4daca1-160d-11d2-a8e9-00104b365c9f"))
/* dual interface */ IMatch;
struct __declspec(uuid("3f4daca2-160d-11d2-a8e9-00104b365c9f"))
/* dual interface */ IMatchCollection;
struct __declspec(uuid("3f4dacb0-160d-11d2-a8e9-00104b365c9f"))
/* dual interface */ IRegExp2;
struct __declspec(uuid("3f4dacb1-160d-11d2-a8e9-00104b365c9f"))
/* dual interface */ IMatch2;
struct __declspec(uuid("3f4dacb2-160d-11d2-a8e9-00104b365c9f"))
/* dual interface */ IMatchCollection2;
struct __declspec(uuid("3f4dacb3-160d-11d2-a8e9-00104b365c9f"))
/* dual interface */ ISubMatches;
struct /* coclass */ RegExp;
struct /* coclass */ Match;
struct /* coclass */ MatchCollection;
struct /* coclass */ SubMatches;

//
// Smart pointer typedef declarations
//

_COM_SMARTPTR_TYPEDEF(IRegExp, __uuidof(IRegExp));
_COM_SMARTPTR_TYPEDEF(IMatch, __uuidof(IMatch));
_COM_SMARTPTR_TYPEDEF(IMatchCollection, __uuidof(IMatchCollection));
_COM_SMARTPTR_TYPEDEF(IRegExp2, __uuidof(IRegExp2));
_COM_SMARTPTR_TYPEDEF(IMatch2, __uuidof(IMatch2));
_COM_SMARTPTR_TYPEDEF(IMatchCollection2, __uuidof(IMatchCollection2));
_COM_SMARTPTR_TYPEDEF(ISubMatches, __uuidof(ISubMatches));

//
// Type library items
//
/*
Немного описания (можно смотреть и в MSDN topic Regular Expression, или в доке на Perl или в Inete)
 http://msdn.microsoft.com/library/default.asp?url=/library/en-us/script56/html/vsobjregexp.asp

		сокращения
		* Определяет ни одного или несколько символов, стоящих перед ним. Пример:
		"ab*c" - символ a, затем ни одного или несколько символов b, и символ c  
		\ Показывает, что следующий символ является спецсимволом, константой и т.п. Например, шаблон 'n' ищет символы "n", а '\n' уже ищет символ новой строки. Последовательность '\\' соответствует "\" и "\(" соответствует "("  
		^ Определяет начало входной строки  
		$ Определяет конец входной строки  
		+ Соответствует данному выражению один или более раз. Например, zo+ соответствует "zo" и "zoo", но не "z"  
		. Соответствует любому символу, кроме '\n' (символа новой строки). Чтобы найти любой символ, включая \n, используйте что-нибудь вроде '[.\n]'. Например:
		"a." - символ a, за который следует любой одиночный символ  
		x|y Соответствует одному из вариантов (x или y). Например, 'z|food' соответствует "z" или "food". '(z|f)ood' соответсвует "zood" или "food"  
		\d Соответствует цифре. То же, что и [0-9]  
		\D Не цифра. То же, что и [^0-9]  
		\w Соответствует любому символу слова, включая символ подчеркивания. Эквивалентно выражению '[A-Za-z0-9_]'  
		\s Пробельный символ (space, tab, и т.п.). Эквивалентно выражению "[ \r\t\n\f]"  
		\S Непробельный символ. Эквивалентно выражению "[^ \r\t\n\f]"  
		[a-z] Диапазон символов. Соответствует любому символу в указанном диапазоне. Например, "[1-5]" соответствует числам от 1 до 5  
		[^a-z] Класс отрицания. Например:
		"[^A-Z]" - соответствует любому символу, крому любой заглавной латинской буквы  
		
			
Примеры

	НЕ ЗАБЫВАЙТЕ МЕНЯТЬ в коде \ на \\


Удалить повторяющиеся слова в тексте 
Паттерн: "([a-zа-я]+) \1"
IgnoreCase := True;
Global := True;
Multiline := True; // многострочный текст
Replace("Стоимость стоимость газолина все все растет растет?", "$1"));

Проверка того, что строка является числом 
"[-+]?([0-9]*\.)?[0-9]+([eE][-+]?[0-9]+)?"
IgnoreCase := True;
Global := True;
Проверка валидности даты формата dd.mm.yyyy 
"(0?[1-9]|[12][0-9]|3[01])\.(0?[1-9]|1[012])\.((19|20)?\d\d)"

Удалить из списка повторяющиеся элементы 
"([^,]*)(,\1)+(?=,|$)"
IgnoreCase := True;
Global := True;
Replace("раз,два,три,три,четыре,пять,пять,шесть,семь,,девять", "$1");

Пример
static IRegExpPtr pRegExp = IRegExp::create("([a-zа-я]+) \\1");
pRegExp->setIgnoreCase(true);
pRegExp->setGlobal(true);
McsString out;
pRegExp->Replace(out, "Стоимость стоимость газолина все все растет растет?", "$1");

//проверить введнные значения
pRegExp->setPattern("[a-zа-я]+ \d+");
HRESULT hRes = pRegExp->checkInput("Квартира 15");
Найти все email в строке
pRegExp->setPattern("\\w+([-\\+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*");
mcsStringArray array;
HRESULT hRes = pRegExp->checkInput(array, "Мои емейлы vasya.pupkin@bm.com и vasya.pupkin@mail.ru");
в array - только emailы 

*/
struct __declspec(uuid("3f4daca0-160d-11d2-a8e9-00104b365c9f"))
IRegExp : IDispatch
{
	static IRegExpPtr create(LPCTSTR strPattern);
	HRESULT setPattern(LPCTSTR strPattern);
	HRESULT setIgnoreCase(bool bIgnore);
	//Искать во всей строке - true, первое вхождение - false
	HRESULT setGlobal(bool bGlobal);
	bool getGlobal();
	//S_OK - введнная строка польностью соответствует шабону, S_FALSE - в строке есть подстрока(и) соответствующие условию
	//E_FAIL - нету соответствующих строк, ВНИМАНИЕ делает setGlobal(false);
	HRESULT checkInput(LPCTSTR strInput);
	//S_OK-в строке есть подстрока(и) соответствующие условию, в strMatchRes - подстроки
	HRESULT checkInput(mcsStringArray& strResults, LPCTSTR strInput);

	IDispatchPtr Execute (LPCTSTR sourceString);
	HRESULT Replace (McsString& resOfReplace, LPCTSTR sourceString, LPCTSTR replaceString );

	//////////////////////////////////////////////////////////////////////////
	// Raw methods provided by interface
	virtual HRESULT __stdcall get_Pattern (/*[out,retval]*/ BSTR * pPattern ) = 0;
	virtual HRESULT __stdcall put_Pattern (/*[in]*/ BSTR pPattern ) = 0;
	virtual HRESULT __stdcall get_IgnoreCase (/*[out,retval]*/ VARIANT_BOOL * pIgnoreCase ) = 0;
	virtual HRESULT __stdcall put_IgnoreCase (/*[in]*/ VARIANT_BOOL pIgnoreCase ) = 0;
	virtual HRESULT __stdcall get_Global (/*[out,retval]*/ VARIANT_BOOL * pGlobal ) = 0;
	virtual HRESULT __stdcall put_Global (/*[in]*/ VARIANT_BOOL pGlobal ) = 0;
	virtual HRESULT __stdcall raw_Execute (/*[in]*/ BSTR sourceString,/*[out,retval]*/ IDispatch * * ppMatches ) = 0;
	virtual HRESULT __stdcall raw_Test (/*[in]*/ BSTR sourceString,/*[out,retval]*/ VARIANT_BOOL * pMatch ) = 0;
	virtual HRESULT __stdcall raw_Replace (/*[in]*/ BSTR sourceString,/*[in]*/ BSTR replaceString,/*[out,retval]*/ BSTR * pDestString ) = 0;
};

struct __declspec(uuid("3f4daca1-160d-11d2-a8e9-00104b365c9f"))
IMatch : IDispatch
{
  HRESULT GetValue (McsString &strValue);
  long GetFirstIndex ( );
  long GetLength ( );

	//////////////////////////////////////////////////////////////////////////
	// Raw methods provided by interface
	virtual HRESULT __stdcall get_Value (/*[out,retval]*/ BSTR * pValue ) = 0;
	virtual HRESULT __stdcall get_FirstIndex (/*[out,retval]*/ long * pFirstIndex ) = 0;
	virtual HRESULT __stdcall get_Length (/*[out,retval]*/ long * pLength ) = 0;
};

struct __declspec(uuid("3f4daca2-160d-11d2-a8e9-00104b365c9f"))
IMatchCollection : IDispatch
{
  IDispatchPtr GetItem (long index );
  long GetCount();

//////////////////////////////////////////////////////////////////////////
// Raw methods provided by interface
	virtual HRESULT __stdcall get_Item (/*[in]*/ long index, /*[out,retval]*/ IDispatch * * ppMatch ) = 0;
	virtual HRESULT __stdcall get_Count (/*[out,retval]*/ long * pCount ) = 0;
	virtual HRESULT __stdcall get__NewEnum (/*[out,retval]*/ IUnknown * * ppEnum ) = 0;
};

//////////////////////////////////////////////////////////////////////////
struct __declspec(uuid("3f4dacb0-160d-11d2-a8e9-00104b365c9f"))
IRegExp2 : IDispatch
{
	HRESULT setPattern(LPCTSTR strPattern);
	HRESULT setIgnoreCase(bool bIgnore);
	HRESULT setGlobal(bool bGlobal);
	HRESULT setMultiline(bool bMultiline);
	IDispatchPtr Execute ( LPCTSTR sourceString );
  _bstr_t Replace (_bstr_t sourceString, const _variant_t & replaceVar);

//////////////////////////////////////////////////////////////////////////
// Raw methods provided by interface
	virtual HRESULT __stdcall get_Pattern (/*[out,retval]*/ BSTR * pPattern ) = 0;
	virtual HRESULT __stdcall put_Pattern (/*[in]*/ BSTR pPattern ) = 0;
	virtual HRESULT __stdcall get_IgnoreCase (/*[out,retval]*/ VARIANT_BOOL * pIgnoreCase ) = 0;
	virtual HRESULT __stdcall put_IgnoreCase (/*[in]*/ VARIANT_BOOL pIgnoreCase ) = 0;
	virtual HRESULT __stdcall get_Global (/*[out,retval]*/ VARIANT_BOOL * pGlobal ) = 0;
	virtual HRESULT __stdcall put_Global (/*[in]*/ VARIANT_BOOL pGlobal ) = 0;
	virtual HRESULT __stdcall get_Multiline (/*[out,retval]*/ VARIANT_BOOL * pMultiline ) = 0;
	virtual HRESULT __stdcall put_Multiline (/*[in]*/ VARIANT_BOOL pMultiline ) = 0;
	virtual HRESULT __stdcall raw_Execute (/*[in]*/ BSTR sourceString,/*[out,retval]*/ IDispatch * * ppMatches ) = 0;
	virtual HRESULT __stdcall raw_Test (/*[in]*/ BSTR sourceString,/*[out,retval]*/ VARIANT_BOOL * pMatch ) = 0;
	virtual HRESULT __stdcall raw_Replace (/*[in]*/ BSTR sourceString,/*[in]*/ VARIANT replaceVar,/*[out,retval]*/ BSTR * pDestString ) = 0;
};

struct __declspec(uuid("3f4dacb1-160d-11d2-a8e9-00104b365c9f"))
IMatch2 : IDispatch
{
	HRESULT GetValue(McsString &strValue);
	long GetFirstIndex();
	long GetLength();
	IDispatchPtr GetSubMatches();

	//////////////////////////////////////////////////////////////////////////
	// Raw methods provided by interface
  virtual HRESULT __stdcall get_Value (/*[out,retval]*/ BSTR * pValue ) = 0;
  virtual HRESULT __stdcall get_FirstIndex (/*[out,retval]*/ long * pFirstIndex ) = 0;
  virtual HRESULT __stdcall get_Length (/*[out,retval]*/ long * pLength ) = 0;
  virtual HRESULT __stdcall get_SubMatches (/*[out,retval]*/ IDispatch * * ppSubMatches ) = 0;
};

struct __declspec(uuid("3f4dacb2-160d-11d2-a8e9-00104b365c9f"))
IMatchCollection2 : IDispatch
{
	IDispatchPtr GetItem (long index);
	long GetCount();

//////////////////////////////////////////////////////////////////////////
// Raw methods provided by interface
  virtual HRESULT __stdcall get_Item (/*[in]*/ long index,/*[out,retval]*/ IDispatch * * ppMatch ) = 0;
  virtual HRESULT __stdcall get_Count (/*[out,retval]*/ long * pCount ) = 0;
	virtual HRESULT __stdcall get__NewEnum (/*[out,retval]*/ IUnknown * * ppEnum ) = 0;
};

struct __declspec(uuid("3f4dacb3-160d-11d2-a8e9-00104b365c9f"))
ISubMatches : IDispatch
{
  _variant_t GetItem (long index );
  long GetCount();

//////////////////////////////////////////////////////////////////////////
// Raw methods provided by interface
  virtual HRESULT __stdcall get_Item (/*[in]*/ long index,/*[out,retval]*/ VARIANT * pSubMatch ) = 0;
  virtual HRESULT __stdcall get_Count (/*[out,retval]*/ long * pCount ) = 0;
  virtual HRESULT __stdcall get__NewEnum (/*[out,retval]*/ IUnknown * * ppEnum ) = 0;
};

struct __declspec(uuid("3f4daca4-160d-11d2-a8e9-00104b365c9f"))
RegExp;
    // [ default ] interface IRegExp2

struct __declspec(uuid("3f4daca5-160d-11d2-a8e9-00104b365c9f"))
Match;
    // [ default ] interface IMatch2

struct __declspec(uuid("3f4daca6-160d-11d2-a8e9-00104b365c9f"))
MatchCollection;
    // [ default ] interface IMatchCollection2

struct __declspec(uuid("3f4dacc0-160d-11d2-a8e9-00104b365c9f"))
SubMatches;
    // [ default ] interface ISubMatches

//////////////////////////////////////////////////////////////////////////
//Implementation
inline HRESULT IRegExp::setPattern(LPCTSTR strPattern){
		return put_Pattern(_bstr_t(strPattern));	
}
inline HRESULT IRegExp::setIgnoreCase(bool bIgnore){
		return put_IgnoreCase(VARIANT_BOOL (bIgnore ? -1:0));
}
inline HRESULT IRegExp::setGlobal(bool bGlobal){
		return put_Global(VARIANT_BOOL (bGlobal ? -1:0));
}

//////////////////////////////////////////////////////////////////////////
inline IRegExpPtr IRegExp::create(LPCTSTR strPattern)
{
	IRegExpPtr ptrOut;
	ptrOut.CreateInstance( __uuidof(RegExp));
	if(ptrOut){
		if(FAILED(ptrOut->setPattern(strPattern))){
			ptrOut = UNKNULL;
		}
	}
	return ptrOut;
}

inline bool IRegExp::getGlobal(){
	VARIANT_BOOL vb;
	if(SUCCEEDED(get_Global(&vb))){
		if(vb == -1) return true;
	}
	return false;
}

inline IDispatchPtr IRegExp::Execute ( LPCTSTR sourceString ) {
		IDispatch * _result = 0;
		HRESULT _hr = raw_Execute(_bstr_t(sourceString), &_result);
		if (FAILED(_hr)) return UNKNULL;
		//_com_issue_errorex(_hr, this, __uuidof(this));
		return IDispatchPtr(_result, false);
}
inline HRESULT IRegExp::Replace (McsString& resOfReplace, LPCTSTR sourceString, LPCTSTR replaceString ) {
		BSTR _result = 0;
		HRESULT _hr = raw_Replace(_bstr_t(sourceString), _bstr_t(replaceString), &_result);
		resOfReplace = _bstr_t(_result, false);
		return _hr;
}

inline HRESULT IRegExp::checkInput(LPCTSTR strInput)
{
	setGlobal(false);
	IMatchCollectionPtr pMatches=Execute(strInput);
	if(pMatches){
		if(pMatches->GetCount() == 1){
			IMatchPtr pMatch = pMatches->GetItem(0);
			if(pMatch){
				McsString strInp = strInput;
				if(pMatch->GetFirstIndex()==0 && pMatch->GetLength() == strInp.GetLength()){
					return S_OK;
				} else {
					return S_FALSE;
				}
			}
		}
  }	
	return E_FAIL;
}

inline HRESULT IRegExp::checkInput(mcsStringArray& strResults, LPCTSTR strInput)
{
	IMatchCollectionPtr pMatches=Execute(strInput);
	if(pMatches){
		for(int i = 0; i < pMatches->GetCount(); i++){
			IMatchPtr pMatch = pMatches->GetItem(i);
			if(pMatch){
				McsString str;
				if(SUCCEEDED(pMatch->GetValue(str))){
					strResults.Add(str);
				}
			}
		}
		if(strResults.GetSize())
			return S_OK;
  }	
	return E_FAIL;
}

//
// interface IMatch wrapper method implementations
//
inline HRESULT IMatch::GetValue (McsString &strValue){
    BSTR _result = 0;
    HRESULT _hr = get_Value(&_result);
    strValue = _bstr_t(_result, false);
		return _hr;
}

inline long IMatch::GetFirstIndex ( ) {
    long _result = 0;
    HRESULT _hr = get_FirstIndex(&_result);
    if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
    return _result;
}

inline long IMatch::GetLength ( ) {
    long _result = 0;
    HRESULT _hr = get_Length(&_result);
    if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
    return _result;
}

//
// interface IMatchCollection wrapper method implementations
//

inline IDispatchPtr IMatchCollection::GetItem ( long index ) {
    IDispatch * _result = 0;
    HRESULT _hr = get_Item(index, &_result);
    if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
    return IDispatchPtr(_result, false);
}

inline long IMatchCollection::GetCount ( ) {
    long _result = 0;
    HRESULT _hr = get_Count(&_result);
    if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
    return _result;
}

//
// interface IRegExp2 wrapper method implementations
//

inline HRESULT IRegExp2::setPattern(LPCTSTR strPattern){
		return put_Pattern(_bstr_t(strPattern));	
}
inline HRESULT IRegExp2::setIgnoreCase(bool bIgnore){
		return put_IgnoreCase(VARIANT_BOOL (bIgnore ? -1:0));
}
inline HRESULT IRegExp2::setGlobal(bool bGlobal){
		return put_Global(VARIANT_BOOL (bGlobal ? -1:0));
}
inline IDispatchPtr IRegExp2::Execute ( LPCTSTR sourceString ) {
		IDispatch * _result = 0;
		HRESULT _hr = raw_Execute(_bstr_t(sourceString), &_result);
		if (FAILED(_hr)) return UNKNULL;
		//_com_issue_errorex(_hr, this, __uuidof(this));
		return IDispatchPtr(_result, false);
}
inline HRESULT IRegExp2::setMultiline(bool bMultiline){
		return put_Multiline(VARIANT_BOOL (bMultiline ? -1:0));
}

inline HRESULT IMatch2::GetValue (McsString &strValue){
	BSTR _result = 0;
	HRESULT _hr = get_Value(&_result);
	strValue = _bstr_t(_result, false);
		return _hr;
}

inline long IMatch2::GetFirstIndex ( ) {
	long _result = 0;
	HRESULT _hr = get_FirstIndex(&_result);
	if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
	return _result;
}

inline long IMatch2::GetLength ( ) {
	long _result = 0;
	HRESULT _hr = get_Length(&_result);
	if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
	return _result;
}

inline IDispatchPtr IMatch2::GetSubMatches ( ) {
	IDispatch * _result = 0;
	HRESULT _hr = get_SubMatches(&_result);
	if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
	return IDispatchPtr(_result, false);
}

//
// interface IMatchCollection2 wrapper method implementations
//

inline IDispatchPtr IMatchCollection2::GetItem ( long index ) {
	IDispatch * _result = 0;
	HRESULT _hr = get_Item(index, &_result);
	if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
	return IDispatchPtr(_result, false);
}

inline long IMatchCollection2::GetCount ( ) {
	long _result = 0;
	HRESULT _hr = get_Count(&_result);
	if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
	return _result;
}

//
// interface ISubMatches wrapper method implementations
//

inline _variant_t ISubMatches::GetItem ( long index ) {
	VARIANT _result;
	VariantInit(&_result);
	HRESULT _hr = get_Item(index, &_result);
	if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
	return _variant_t(_result, false);
}

inline long ISubMatches::GetCount ( ) {
	long _result = 0;
	HRESULT _hr = get_Count(&_result);
	if (FAILED(_hr)) _com_issue_errorex(_hr, this, __uuidof(this));
	return _result;
}


#pragma pack(pop)
