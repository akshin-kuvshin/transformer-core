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

// force BP stack framing to improve ET stack trasing capabilities on exceptions
#pragma optimize("y", off)

#ifdef _VERBOSEHEADERS_
#pragma message("Use " __FILE__)
#endif

#if !defined(MFC_DEBUG) && defined(_DEBUG)
	#define _DEBUG_WAS_DEFINED
	#undef _DEBUG
	#define NDEBUG
#endif

#include <comutil.h>
#include <atlbase.h>
#include <ATLDef.h>
#include <memory>

#ifdef _DEBUG_WAS_DEFINED
	#undef NDEBUG
	#define _DEBUG
	#undef _DEBUG_WAS_DEFINED
#endif

/*
#ifdef WIN64
	#include <atlwin.h>
#endif
*/

#pragma comment(lib,"COMSUPP.LIB") 
//#pragma warning(disable: 4800) // forcing value to 'bool': true/false
#pragma warning(disable: 4995) // VS.NET: name "..." marked as deprecated 
#pragma warning(disable: 4250) // virtual base class: XXX inherits YYY via dominance
#pragma warning(disable: 4927) // illegal conversion; more than one user-defined conversion has been implicitly applied


#if (_MSC_VER > 1310)
	#define MCS_SEALED sealed
#else
	#define MCS_SEALED
#endif 

#include "mcseds.h"
#include "mcstempl.h"
#include "mcsconsts.h"
#include "McAPIs.h"

#include <locale.h>
__inline TCHAR _decimal_point()
{
	char* pDP = localeconv()->decimal_point;
	if(pDP)
		return *pDP;
	return _T('.');
}
#define DECMAL_POINT (_decimal_point())

//----------------------------------------
//force OLD and OBSOLETE declarations 
struct IMcRegSaver;
class  IDBBrowser;
class  ITable;
class  IParamManager;
struct IEntityMonitor;
struct IMcsTransactionManager;
struct IMcs3dConstraintsManager;
struct IMcsNativeObjectsManager; 
struct IMcsProgress;
struct IMcsNativeView;
struct IMcsGraphics;
struct IMcTabManager;
struct IMcsTTManager;
struct McFEVRefKeyData;
#define McFEVRefKey McFEVRefKeyData

//=============================================================================

#define MC_LOCK_WA   0x00001 // writeEnable
#define MC_LOCK_KO   0x00002 // kindOf
#define MC_LOCK_GHS  0x00004 // getHostSolid
#define MC_LOCK_CAT  0x00008 // canAcceptTfm
#define MC_LOCK_DPON 0x00010 // getDepOn
#define MC_LOCK_DPNT 0x00020 // getDependent
#define MC_LOCK_QI   0x00040 // QueryInterface

//=============================================================================
#ifndef ASI64
#define ASI64(LargeInteger) (*(__int64*)&(LargeInteger))
#endif

#ifndef ASLI
#define ASLI(i64) (*(LARGE_INTEGER*)&(i64))
#endif

#ifndef I64LOW
#define I64LOW(i64) (ASLI(i64).LowPart)
#endif

#ifndef I64HI
#define I64HI(i64) (ASLI(i64).HighPart)
#endif

//==============================================================================
template <class T> bool _is_valid_interfacePtr4ptr(T* pObj)
{
#ifdef _DEBUG

	// быстрая функция по определнию валидности памяти по данному указателю
	// IsBadReadPtr работает дольше, если же указатель валидный, то выполняется вообще быстро
	if(!pObj)
		return true;
	try
	{
		// из-за виртуального наследования, может упасть уже тут, если указатель ссылается
		// на битый объект
		IMcObject* pIMcObj = (IMcObject*)pObj;
		// при обычном наследовании по нулевому смещению находится указатель на таблицу
		// виртуальных функций; при виртуальном наследовании по 0-му смещению также находится
		// адрес с помощтю которого можно узнать смещение к нужной виртуальной таблице;
		// поэтому тестируем значение по 0-му адресу как указатель на адрес

		// нужно брать указатель из IMcObject, т.к. бывает, что у объекта по нулевому смещению
		// находятся данные, а таблица виртуальных функций из-за виртуального наследования
		// имеет другое смещение
		char* pByte = *(char**)pIMcObj;
		char bt = *pByte;
	} catch(...) {
		return false;
	}

#endif

	return true;
}
//==============================================================================
template <class T> bool _safe_addref4ptr(T* ptr)
{
	if(!ptr)
		return true;

#ifdef _DEBUG

	if(!_is_valid_interfacePtr4ptr(ptr)) {
//		MCSASSERTE("ALERT! _safe_addref4ptr, [pUnk] is invalid");
		MESSAGE_ERR_NOCP(_T("ALERT! _safe_addref4ptr, [pUnk] is invalid"));
		if(IsDebuggerPresent())
			DebugBreak();
		return false;
	}

	try{
		ptr->AddRef();
	}catch(...){
//		MCSASSERTE("ALERT! _safe_addref4ptr, calling [pUnk]->AddRef()");
		MESSAGE_ERR_NOCP(_T("ALERT! _safe_addref4ptr, calling [pUnk]->AddRef()"));
		if(IsDebuggerPresent())
			DebugBreak();
		return false;
	}
	return true;

#else

	ptr->AddRef();
	return true;

#endif
}
//==============================================================================
template <class T> bool _safe_release4ptr(T* ptr)
{
	if(!ptr)
		return true;

#ifdef _DEBUG

	if(!_is_valid_interfacePtr4ptr(ptr)) {
//		MCSASSERTE("ALERT! _safe_release4ptr, [pUnk] is invalid");
		MESSAGE_ERR_NOCP(_T("ALERT! _safe_release4ptr, [pUnk] is invalid"));
		if(IsDebuggerPresent())
			DebugBreak();
		return false;
	}
	try{
		ptr->Release();
	}catch(...){
//		MCSASSERTE("ALERT! _safe_release4ptr, calling [pUnk]->Release()");
		MESSAGE_ERR_NOCP(_T("ALERT! _safe_release4ptr, calling [pUnk]->Release()"));
		if(IsDebuggerPresent())
			DebugBreak();
		return false;
	}
	return true;

#else

	ptr->Release();
	return true;

#endif
}
//==============================================================================
template <class T> void* _safe_qi4ptr(T* ptr, REFIID riid, HRESULT* phres = NULL)
{
	if(!ptr) {
		if(phres)
			*phres = E_POINTER;
		return NULL;
	}

#ifdef _DEBUG

	if(!_is_valid_interfacePtr4ptr(ptr))
	{
		//MCSASSERTE("ALERT! _safe_qi4ptr, can't change type of [ptr] to <IUnknown*>");, разкоментирование этого кусочка приводит к проблемам при вызове mcsInit d mapimgd
		// видимо какой то глюк компиляторв, ручное разворачивание я убрал, были без него, при появлении мессаджа в InDebMon, можно локально ручками включить для поиска ошибки
		//{ // Руками вставленный MCSASSERTE("ALERT! _safe_qi4ptr, [ptr] is invalid");
		//	if((true)) {
		//		static bool ls_f=false;
		//		if(!(false) || !ls_f && (false)){
		//			ls_f = true;
		//			char* msg = new char[2048];
		//			mcs_snprintf_s(msg, 2048 / sizeof(*msg), _TRUNCATE, "McsAssertion failed;\r\nExpression: 'ALERT! _safe_qi4ptr, [ptr] is invalid'\r\nFile: '%s; Line: %d;\nDebug?",__FILE__,__LINE__);
		//			MESSAGE_ERR_A(msg);
		//			if(::MessageBoxA(NULL,msg,"MCSASSERTE",MB_ICONSTOP|MB_YESNO|MB_TASKMODAL|MB_TOPMOST)==IDYES)
		//				mcsHlpDbgBreak();
		//			delete[] msg;
		//		}
		//	}
		//}
		MESSAGE_ERR_NOCP(_T("ALERT! _safe_qi4ptr, [ptr] is invalid"));
		if(IsDebuggerPresent())
			DebugBreak();
		if(phres)
			*phres = E_UNEXPECTED;
		return NULL;
	}

	IUnknown* pUnk = NULL;
	try{
		pUnk = (IUnknown*)ptr;
	}catch(...){
//		MCSASSERTE("ALERT! _safe_qi4ptr, can't change type of [ptr] to <IUnknown*>");
		MESSAGE_ERR_NOCP(_T("ALERT! _safe_qi4ptr, can't change type of [ptr] to <IUnknown*>"));
		if(IsDebuggerPresent())
			DebugBreak();
		if(phres)
			*phres = E_UNEXPECTED;
		return NULL;
	}

	HRESULT hres = E_FAIL;
	void* pV = NULL;
	try{
		hres = pUnk->QueryInterface(riid, &pV);
	}catch(...){
//		MCSASSERTE("ALERT! _safe_qi4ptr, calling [pUnk]->QueryInterface(..)");
		MESSAGE_ERR_NOCP(_T("ALERT! _safe_qi4ptr, calling [pUnk]->QueryInterface(..)"));
		if(IsDebuggerPresent())
			DebugBreak();
		pV = NULL;
		hres = E_UNEXPECTED;
	}
	if(phres)
		*phres = hres;
	return pV;

#else

	IUnknown* pUnk = (IUnknown*)ptr;
	void* pV = NULL;
	HRESULT hres = pUnk->QueryInterface(riid, &pV);
	if(phres)
		*phres = hres;
	return pV;

#endif
}
//==============================================================================
template <class TypeTo, class TypeFrom>
void* MComQIPtrAssign(TypeTo*& pTo, TypeFrom* pFrom, REFIID riid)
{
	if(pTo == pFrom)
		return pTo;

	TypeTo* pTmp = pTo;
	pTo = NULL;

	if(__uuidof(*pTo) == __uuidof(*pFrom)) {
		// тот же тип, прямое приведение через void* допустимо, иначе не соберётся, т.к. код общий и для разных типов
		pTo = (TypeTo*)(void*)pFrom;
		_safe_addref4ptr(pFrom);
	} else {
		pTo = (TypeTo*)_safe_qi4ptr(pFrom, riid);
	}

	_safe_release4ptr(pTmp);
	return pTo;
}
//==============================================================================
#ifdef _DEBUG
	#define DBG_RELEASE_P {p = NULL; if(p) p->Release();}
#else
	#define DBG_RELEASE_P ((void)0);
#endif
//==============================================================================
/*
17.02.12, AGL
MComPtr, MComQIPtr, MObjPtr добавил проверку валидности указателя и обернул
обращение к указателям в ловушки. Проверку валидности выполняем в два этапа:
Сначала просто проверяем факт того, что по ненулевому указателю можно что-то прочитать,
затем пытаемся обратиться к методам по указателю, на этом этапе тоже может упасть.
*/
//..............................................................................
template <class T>
class MComPtr
{
public:
	T* p;

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MComPtr() {
		p = NULL;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MComPtr(T* lp)
	{
		p = NULL;
		DBG_RELEASE_P;
		if(_safe_addref4ptr(lp))
			p = lp;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MComPtr(const MComPtr<T>& lp)
	{
		p = NULL;
		DBG_RELEASE_P;
		if(_safe_addref4ptr(lp.p))
			p = lp.p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	~MComPtr() {
		_safe_release4ptr(p);
		p = NULL;
		DBG_RELEASE_P;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	void Release() {
		_safe_release4ptr(p);
		p = NULL;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	operator T*() const
	{
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MComPtr::operator T*(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return NULL;
		}
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T& operator*() const
	{
		MCSASSERT(p != NULL);
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MComPtr::operator *(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return *(T*)NULL;
		}
		return *p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T** operator&() {
		MCSASSERT(p==NULL);
		return &p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* operator->() const
	{
		MCSASSERT(p!=NULL);
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MComPtr::operator ->(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return NULL;
		}
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* operator = (T* lp)
	{
		_safe_release4ptr(p);
		p = NULL;
		if(_safe_addref4ptr(lp))
			p = lp;
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* operator = (const MComPtr<T>& lp)
	{
		_safe_release4ptr(p);
		p = NULL;
		if(_safe_addref4ptr(lp.p))
			p = lp.p;
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	bool operator ! () const {
		if(!p)
			return true;
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MComPtr::operator bool(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return true;
		}
		return false;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	bool operator < (T* pT) const {
		return p < pT;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	bool operator == (T* pT) const {
		return p == pT;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	// Compare two objects for equivalence
	bool IsEqualObject(IUnknown* pOther)
	{
		if (!p && !pOther)
			return true; // They are both NULL objects

		if (!p || !pOther)
			return false; // One is NULL the other is not

		MComPtr<IUnknown> punk1, punk2;
		punk1.p = (IUnknown*)_safe_qi4ptr(p, IID_IUnknown);
		punk2.p = (IUnknown*)_safe_qi4ptr(pOther, IID_IUnknown);
		if(punk1.p == punk2.p)
			return true;
		return false;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	void Attach(T* p2)
	{
		_safe_release4ptr(p);
		p = NULL;
		if(!_is_valid_interfacePtr4ptr(p2)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MComPtr::Attach(ptr), [ptr] is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return;
		}
		p = p2;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* Detach() {
		T* pt = p;
		p = NULL;
		return pt;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	template <class Q>
	HRESULT QueryInterface(Q** pp) const
	{
		MCSASSERT_EX(pp != NULL, return E_POINTER);
		MCSASSERT(*pp == NULL); // bug, receiver must be empty
		HRESULT hres = S_OK;
		*pp = (Q*)_safe_qi4ptr(p, __uuidof(Q), &hres);
		return hres;
	}
};
//===================================================================

//===================================================================
template <class T, const IID* piid = &__uuidof(T)>
class MComQIPtr
{
public:
	T* p;

	// SEA 15.08.2008
	// Во всех конструкторах, кроме пустого, добавил для дебага такой вот холостой код.
	// Единственное его назначение генерить в дебаге ошибку компилятора в одной очень
	// неприятной ситуации. Пример:
	// <code begin>
	//	IMCS_DECL_INTERFACE(IMcXXX, "00000015-0001-AAAA-AAAA-050B00000000")
	//	void function(const mcsWorkID& id)
	//	{
	//		IMcXXXPtr ptr = gpMcObjManager->getObject(id);
	//	}
	// <code end>
	// В данном случае, класс IMcXXX не определён вообще нигде в этой части проекта, определён
	// только шаблонный указатель, а другой стороне IMcXXX известен и возвращается ненулевой указатель.
	// При этом компилятор не выдаёт никакой ошибки и генерит какой-то код. В итоге завалится 
	// при попытке обращения к методам IMcXXX. К примеру release() у ptr будет выполняться как будто
	// IMcXXX унаследован от IUnknown, а такого наследования, по большому счёту, может вообще не быть.

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MComQIPtr() {
		p=NULL;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MComQIPtr(T* lp) {
		p = NULL;
		DBG_RELEASE_P; // Комментарий выше
		if(_safe_addref4ptr(lp))
			p = lp;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MComQIPtr(const MComQIPtr<T, piid>& lp) {
		p = NULL;
		DBG_RELEASE_P; // Комментарий выше
		if(_safe_addref4ptr(lp.p))
			p = lp.p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MComQIPtr(IUnknown* lp) {
		p = NULL;
		DBG_RELEASE_P; // Комментарий выше
		p = (T*)_safe_qi4ptr(lp, *piid);
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	~MComQIPtr() {
		_safe_release4ptr(p);
		p = NULL;
		DBG_RELEASE_P; // Комментарий выше
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	void Release()
	{
		if (p)
			((IUnknown*)p)->Release();
		p = NULL;
		DBG_RELEASE_P; // Комментарий выше
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	operator T* () const {
#ifdef _DEBUG
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MComQIPtr::operator T*(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return NULL;
		}
#endif
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T& operator * () const {
#ifdef _DEBUG
		MCSASSERT(p != NULL);
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MComQIPtr::operator *(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return *(T*)NULL;
		}
#endif
		return *p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	//The assert on operator& usually indicates a bug.  If this is really
	//what is needed, however, take the address of the p member explicitly.
	T** operator & () {
#ifdef _DEBUG
		MCSASSERT(p == NULL);
#endif
		return &p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* operator -> () const {
#ifdef _DEBUG
		MCSASSERT(p!=NULL);
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MComQIPtr::operator ->(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return NULL;
		}
#endif
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* operator = (T* lp) {
		MComQIPtrAssign(p, lp, *piid);
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* operator = (const MComQIPtr<T, piid>& lp) {
		MComQIPtrAssign(p, lp.p, *piid);
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* operator = (IUnknown* lp) {
		MComQIPtrAssign(p, lp, *piid);
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	bool operator ! () const {
		if(!p)
			return true;
#ifdef _DEBUG
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MComQIPtr::operator bool(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return true;
		}
#endif
		return false;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	bool operator < (T* pT) const {
		return p < pT;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	bool operator == (T* pT) const {
		return p == pT;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	// Compare two objects for equivalence
	bool IsEqualObject(IUnknown* pOther)
	{
		if (!p && !pOther)
			return true; // They are both NULL objects

		if (!p || !pOther)
			return false; // One is NULL the other is not

		MComPtr<IUnknown> punk1, punk2;
		punk1.p = (IUnknown*)_safe_qi4ptr(p, IID_IUnknown);
		punk2.p = (IUnknown*)_safe_qi4ptr(pOther, IID_IUnknown);
		if(punk1.p == punk2.p)
			return true;
		return false;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	void Attach(T* p2)
	{
		_safe_release4ptr(p);
#ifdef _DEBUG
		p = NULL;
		if(!_is_valid_interfacePtr4ptr(p2)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MComQIPtr::Attach(ptr), [ptr] is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return;
		}
#endif
		p = p2;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* Detach() {
		T* pt = p;
		p = NULL;
		return pt;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	template <class Q>
	HRESULT QueryInterface(Q** pp)
	{
		MCSASSERT_EX(pp != NULL, return E_POINTER);
		MCSASSERT(*pp == NULL); // bug, receiver must be empty
		HRESULT hres = S_OK;
		*pp = (Q*)_safe_qi4ptr(p, __uuidof(Q), &hres);
		return hres;
	}
};
//==============================================================================
// declares IID_, uuid and ptr for interface
// use following form for strid:
// "<32bit_id>-<category>-AAAA-AAAA-050B00000000" for example:
// #define gstr_IID_IMcObject "00000001-0001-AAAA-AAAA-050B00000000"
// IMCS_DECL_INTERFACE(IMcObject,gstr__IID_IMcObject)

#ifndef _MCEYE
  #define IMCS_DECL_INTERFACE(name,strid) \
  struct __declspec(uuid(strid)) name; \
  static const GUID IID_##name = __uuidof(name); \
  typedef MComQIPtr<name> name##Ptr;
#else
  #define IMCS_DECL_INTERFACE(name,strid) \
  struct __declspec(uuid(strid)) name; \
  static const GUID IID_##name = mceAddGuidName(__uuidof(name), #name); \
  typedef MComQIPtr<name> name##Ptr; 
#endif

//.............................................
// add here interfaces category for your module
#define IMCS_MECHCTL_COMMON_IID_category "0001"
#define IMCS_MECHCTL_IID_category        "0002"
#define IMCS_MCS4I_IID_category          "0003"
#define IMCS_SYMBOLS_IID_category        "0004"
#define IMCS_M3D_IID_category            "0005"
#define IMCS_DIMENSIONS_IID_category     "0006"
#define IMCS_STYLES_IID_category         "0007"
#define IMCS_SPDSGRID_IID_category       "0008"
#define IMCS_MCCUTTER_IID_category       "0009"
#define IMCS_GEARS_IID_category          "000A"
#define IMCS_ACADGATE_IID_category       "000B"
#define IMCS_MCWIZARD_IID_category       "0010"
#define IMCS_FORMATS_IID_category        "0011"
#define IMCS_SPC_IID_category            "0012"
#define IMCS_TT_IID_category             "0013"
#define IMCS_PARSER_IID_category         "0014"
#define IMCS_ROUTE_IID_category          "0015"
#define IMCS_PT_IID_category             "0016"
#define IMCS_VESSEL_IID_category         "0017"
#define IMCS_MODELER_IID_category        "0018" // "3D3D" туда же
#define IMCS_FORMS_IID_category          "0019"
#define IMCS_BROWSER_IID_category        "0020"
#define IMCS_CONSTRUCTIONS_IID_category  "0021"
#define IMCS_COMPLEX_IID_category        "0022"
#define IMCS_GNB_IID_category            "0023"
#define IMCS_PRJ_IID_category            "0024"
#define IMCS_M4SW_IID_category           "0025"

#define IMCS_SPOTGATE_IID_category       "1000"


IMCS_DECL_INTERFACE(IMcObject,              "00000001-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDbObject,            "00000002-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDbEntity,            "00000003-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(CDbEntityPrototype,     "10100003-0001-AAAA-AAAA-050B00000000")
//IMCS_DECL_INTERFACE(IMcDbReferenceEntity,   "00000004-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEntity,              "00000005-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcCdEntity,            "00000006-0001-AAAA-AAAA-050B00000000")
//IMCS_DECL_INTERFACE(IMcReferenceEntity,     "00000007-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcObjectsManager,      "00000008-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDocument,            "00000009-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDocumentsManager,    "0000000A-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcGeometryBuilder,     "0000000B-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcsStream,             "0000000C-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcsNativeView,         "0000000D-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPainter,             "0000000E-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcParametricEnt,       "0000000F-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcStdPartConstraint,   "00000010-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(McDbDimension,          "00000011-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcGroup,               "00000012-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcUndoPoint,           "00000013-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcGeometry,            "00000014-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcBlockRef,            "00000015-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSelectionSet,        "00000016-0001-AAAA-AAAA-050B00000000")
//IMCS_DECL_INTERFACE(IMcReferenceContext,    "00000017-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcLinksManager,        "00000018-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcLC,                  "00000019-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcGesture,             "0000001A-0001-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcCtrDriver,           "00000020-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPConstraint,         "00000021-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcLConstraint,         "00000022-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcWizSymbol,           "00000023-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMtStream,              "00000024-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcImageRef,            "00000025-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSearchEngine,        "00000026-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSearchResult,        "00000027-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSearcher,            "00000028-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDBHeaderSearcher,    "00000029-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDBHSearchResult,     "00000030-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcObjPropertySearcher, "00000031-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcObjPropSearchResult, "00000032-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcZombie,              "00000035-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcParameterRedefinition,"00000036-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPropertySource,      "00000037-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcAutoFree,            "00000038-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNativeLineTypeMaker, "00000039-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNativePointTypeMaker,"0000003A-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNativeLongObject,    "0000003B-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNativePointObject,   "0000003C-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcBaseLongObjectAssistant,"0000003D-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcBasePointObjectAssistant,"0000003E-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSubentIdentification, "0000003F-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcCustomSignDbManager, "00000040-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNetMcEntity,         "00000041-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcObjFactory,          "00000042-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcCustomDlgContext,    "00000043-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcLowLevelGate,        "00000044-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNetBase,             "00000045-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNetMcCdEntity,       "00000046-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNetLeaderEntity,     "00000047-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPropertyCarrier,     "00000048-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcParamManager,        "00000049-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDocParamManager,     "00000050-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcAreaEntity,          "00000051-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcAreaObjectsManager,  "00000052-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNetPropertySource,   "00000053-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcAnnotation,          "00000054-0001-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcPropertyFindExtension, "00000055-0001-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcInObjectPainter,     "00000056-0001-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcMaterialLibrary,     "00000057-0001-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcProjectDwgStorage,   "00000058-0001-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcProjectDwgRunTime,   "00000059-0001-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcNet3dFeatureEntity,  "0000005A-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSurfaceGeometry,     "0000005B-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcObjMvRedefinition,   "0000005C-0001-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcsMemoryView,         "0000005D-0001-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(Mc3dImage,              "00080002-0002-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcDb3dConstraint,      "0000000C-0003-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcAlienEntity,         "00000001-FEFE-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcHatch,               "00000002-FEFE-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcCurve,               "B0839725-30AA-4b02-91C5-E41E563C48DC")
IMCS_DECL_INTERFACE(IMcLine,                "1B450530-75C5-4c54-BB69-C244746DDA70")
IMCS_DECL_INTERFACE(IMcArc,                 "7EF301D4-FF0E-445f-B4C4-41FD26ABBA72")
IMCS_DECL_INTERFACE(IMcCircle,              "98C0470A-2CCB-49ce-8D14-89A7B27577B7")
IMCS_DECL_INTERFACE(IMcPolyline,            "3B5F4969-F4B5-4ddd-A45B-583D7CC6AB6D")
IMCS_DECL_INTERFACE(IMcPoint,               "AA2BC701-3E1A-4da8-B5FF-A4AC6E04E2C3")
IMCS_DECL_INTERFACE(IMcText,                "AF762C19-98EB-4347-B038-FCEC3DEBFE00")
IMCS_DECL_INTERFACE(IMcMText,               "A3126AF9-F1C7-4DC6-8B49-E10616251A8C")
IMCS_DECL_INTERFACE(IMcEllipticArc,         "00000003-FEFE-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcExtBlockRef,         "94A8E67A-8D8D-4D16-B94D-F37485801C05")

//Абстрактный GUID для поиска перекрывающейся геометрии (исключая текст, точки, 
//ну и то что не можем перекрыть но используем)
//так же для вызова гарантированного нативного поиска
IMCS_DECL_INTERFACE(IMcCdGeometry,          "00000004-FEFE-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcSpline,              "00000005-FEFE-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMc3DPolyline,          "E3F735B6-2BDA-4EA5-B9AF-2A48BD66F940")
IMCS_DECL_INTERFACE(IMcMLine,               "F095511F-FB76-4DEC-A5E6-37957124C55A")
IMCS_DECL_INTERFACE(IMcAttribute,           "F0E8B9E9-D660-4F0B-BD1D-90C0BA151D54")
IMCS_DECL_INTERFACE(IMcViewport,            "B787E54C-6CB5-47B5-9CDD-0F47689D9AE3")
IMCS_DECL_INTERFACE(IMcXLine,               "9AAA9904-4C4D-4381-9D81-D89B9190F271")
IMCS_DECL_INTERFACE(IMcRay,                 "6307E289-2CFE-481A-8B91-CFAE97AC2E54")

IMCS_DECL_INTERFACE(IMcRegion,              "367557C8-A9E5-4255-B71C-57CD6988347A")
IMCS_DECL_INTERFACE(IMcSurface,             "33334444-A9E5-4255-B71C-57CD6988347A")

IMCS_DECL_INTERFACE(IMcPolygonMesh,         "8248DF60-B56D-4C29-8C36-453F68C2C177")
IMCS_DECL_INTERFACE(IMcSubDMesh,            "DE31BBD8-AE6D-4AAD-9192-5D27D0DA4B1C")
IMCS_DECL_INTERFACE(IMcPolyFaceMesh,        "08EB225B-FA46-4FED-8F7D-429B7282A4AC")
IMCS_DECL_INTERFACE(IMcFaceMesh,            "5F5BC813-D33C-4FDB-B81A-7193039BC565") // AcDbFace/OdDbFace
IMCS_DECL_INTERFACE(IMcBimIfcEntity,        "CE302BC4-E6AB-4611-9266-1291B4104DD8") // mcsDbIFCEntity

IMCS_DECL_INTERFACE(IMcLeader,              "ECD5AAFA-E94F-4b1c-8D8F-AF70E2582963")
IMCS_DECL_INTERFACE(IMcShape,               "9C927E8F-5AC2-478D-B399-FF274FE01DE2")
IMCS_DECL_INTERFACE(IMcSolid,               "E02CECA0-2E91-4B7D-9A69-E3E9EBD027C6")
IMCS_DECL_INTERFACE(IMcWipeout,             "F1333420-904E-4A2F-BD73-22FF2A15859A")
IMCS_DECL_INTERFACE(IMc2DPolyline,          "3930C846-7826-42C8-BB55-B8486AAC3575")
IMCS_DECL_INTERFACE(IMcProxyEntity,         "49B348EC-1CFE-4EAA-82A9-FCDF37437D94")
IMCS_DECL_INTERFACE(IMcMLeader,             "0FA40B4D-18ED-4616-8042-3FA0235974F9")
IMCS_DECL_INTERFACE(IMcDWGTable,            "7E42E1F2-9D0B-4EA9-BE1C-51E5FBC05270")

IMCS_DECL_INTERFACE(IMcDimension,           "00000000-0006-AAAA-AAAA-050B00000000")     // базовый интерфейс размера
IMCS_DECL_INTERFACE(IMcLinearDimension,     "00000001-0006-AAAA-AAAA-050B00000000")     // линейный размер
IMCS_DECL_INTERFACE(IMcRadialDimension,     "00000002-0006-AAAA-AAAA-050B00000000")     // радиальный размер
IMCS_DECL_INTERFACE(IMcHugeRadialDimension, "00000003-0006-AAAA-AAAA-050B00000000")     // радиальный размер с условным центром
IMCS_DECL_INTERFACE(IMcDiametralDimension,  "00000004-0006-AAAA-AAAA-050B00000000")     // диаметральный размер
IMCS_DECL_INTERFACE(IMcAngularDimension,    "00000005-0006-AAAA-AAAA-050B00000000")     // угловой размер
IMCS_DECL_INTERFACE(IMcArcDimension,        "00000006-0006-AAAA-AAAA-050B00000000")     // длина дуги
IMCS_DECL_INTERFACE(IMcOrdinateDimension,   "00000007-0006-AAAA-AAAA-050B00000000")     // ординатный размер (линейный направленный)
IMCS_DECL_INTERFACE(IMcOrdinateBase,        "00000008-0006-AAAA-AAAA-050B00000000")     // начало отчёта ординатных размеров
IMCS_DECL_INTERFACE(IMcAlignedDimension,    "00000009-0006-AAAA-AAAA-050B00000000")     // Параллельный размер
IMCS_DECL_INTERFACE(IMcOffsetDimension,     "0000000A-0006-AAAA-AAAA-050B00000000")     // Размер-подобие

IMCS_DECL_INTERFACE(ICutter,                "00000001-0009-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcWizard,              "00000001-0010-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSpcLeader,           "00000001-0012-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSpecificationObject, "54126939-D289-4148-91A6-9A04DA071315")      // Объект, содержащий в себе спецификацию
IMCS_DECL_INTERFACE(IMcSpecObjectsTreeControl_NativePart,"C1C8690B-23C7-4d58-BC74-B4A77AED9195")    // WinForm-контрол, отображающий дерево объектов спецификаций
IMCS_DECL_INTERFACE(IMcSpecProjectInteract, "780380E0-05FC-4f48-B0BC-100CE8BE0CBA")      // Взаимодествие с проектом "Спецификация" из нейправляемого кода
IMCS_DECL_INTERFACE(IMcSpecNativeCodeUtilities, "CF4A0C7D-316F-4387-9CE7-EF6D6CBFB578")  // Интерфейс для доступа к вспомогательным функциям, лежащим в нативном(C++) модуле - SpecificationDlg
IMCS_DECL_INTERFACE(IMcTText,               "00000001-0013-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IDictionaryCallback,    "00000002-0013-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDigiCalculator,      "00000003-0013-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNotebook,            "00000004-0013-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcTTRichEditControl,   "00000005-0013-AAAA-AAAA-050B00000000")     //Интерфейс .net контрола TT RichEdit для работы из неуправляемого кода
IMCS_DECL_INTERFACE(IMcNotebookTableControl,"00000006-0013-AAAA-AAAA-050B00000000")		//Интерфейс .net контрола таблиц записной книжки 

IMCS_DECL_INTERFACE(IMcUMarker,             "00000001-0014-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDBTableFiltrator,    "00000002-0014-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcJoint,               "00000003-0014-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(CSelecter,              "00000004-0014-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcScriptObject,        "00000005-0014-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(CDBOldTemplateContainer,"00000006-0014-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(ISpdsLevel,             "A9B900A6-1B65-4f9c-BEE9-D5751A9C4484")     // отметка уровня
IMCS_DECL_INTERFACE(ISpdsNode,              "A367610B-0E4C-4246-B91D-B3008537716C")     // обозначение узла
IMCS_DECL_INTERFACE(ISpdsCorrectionMarker,  "2A2FEF23-C19E-43e5-A76D-EFAED01975C9")     // маркер изменений
IMCS_DECL_INTERFACE(ISpdsPolymorphMarker,   "C8F9CA7B-35E1-44a8-9F1A-7E9C56CE4F32")     // позиционный маркер
IMCS_DECL_INTERFACE(ISpdsPlaneLevel,        "36BBD15D-DA23-4502-A53F-62655DDE2F40")     // отметка уровня на плане
IMCS_DECL_INTERFACE(ISpdsFragment,          "46FF36DF-6E71-4ae9-9884-C589790DA25D")     // обозначение фрагмента
IMCS_DECL_INTERFACE(ISpdsPosition,          "8D00C5CB-23E3-4bda-96BF-CCC35E1784EF")     // обозначение позиции
IMCS_DECL_INTERFACE(ISpdsAnker,             "592B8316-9DC5-4c8a-98BE-6AAEF93747A1")     // якорь привязки отметок уровня
IMCS_DECL_INTERFACE(IMcPolylineBasedEntity, "9A692596-BA69-4565-AD43-2D2CCB3C87B5")     // базовый класс для объектов-на-полилинии
IMCS_DECL_INTERFACE(IMcBoundForm,           "659B92B6-4A9D-4138-B19C-DDEACA2B8018")     // граничные формы
IMCS_DECL_INTERFACE(IMcWeld,                "5E6DE5BF-EC43-49d2-989D-5C5F72005FD2")     // сварные швы
IMCS_DECL_INTERFACE(IMcMAnchor,             "7B2037AB-F244-4d19-9A74-27B3C25CD563")     // конечные маркеры
IMCS_DECL_INTERFACE(IMcRange,               "06C915A9-D1F3-4f81-BA6E-56EB2E54199F")     // диапазон распределения
IMCS_DECL_INTERFACE(ISpdsEntitySquare,      "00000004-0008-AAAA-AAAA-050B00000000")     // площадь
IMCS_DECL_INTERFACE(ISpdsEntityQuarters,    "00000005-0008-AAAA-AAAA-050B00000000")     // форма помещения
IMCS_DECL_INTERFACE(IMcStationing,          "00000030-0004-AAAA-AAAA-050B00000000")     // пикетаж
IMCS_DECL_INTERFACE(IMcRoom,                "00000031-0004-AAAA-AAAA-050B00000000")     // Помещение
IMCS_DECL_INTERFACE(IMcBrokenOutSection,    "8B56E7B4-458B-4ba2-B730-B38269C71680")// Местный разрез

IMCS_DECL_INTERFACE(IMcTable2,              "0002001D-0004-AAAA-AAAA-050B00000000")     // таблица

IMCS_DECL_INTERFACE(IMcRouteEntity,         "00000001-0015-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPipelineCommander,   "00000002-0015-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcCalculator,          "00000001-000A-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcGearCalculator,      "00000002-000A-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcReportManager,       "00000003-000A-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcGearMaterialManager, "00000004-000A-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcCalculatorManager,   "00000005-000A-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcBevelGearCalc,       "00000006-000A-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcBevelGearGeom,       "00000007-000A-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSpurGearCalc,        "00000008-000A-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSpurGearTest,        "00000009-000A-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNetCalculator,       "00000010-000A-AAAA-AAAA-050B00000000")		// базоваый интерфейс для связки .net объектов со скриптами
IMCS_DECL_INTERFACE(IMcGearGOSTCalculator,  "00000011-000A-AAAA-AAAA-050B00000000")		// расчет цилиндрических, зубчатых, эвольвентных передач согласно ГОСТ (Mc-serialization)
IMCS_DECL_INTERFACE(IMcGearGOSTCalculatorNS,"00000012-000A-AAAA-AAAA-050B00000000")		// расчет цилиндрических, зубчатых, эвольвентных передач согласно ГОСТ (Net-serialization)
IMCS_DECL_INTERFACE(McSprCompressionCalc,   "97CD4039-24B2-4b6d-A196-B71934CEE78F")
IMCS_DECL_INTERFACE(McSprTensionCalc,       "22A9A42A-CE62-4191-A454-FA0F2AC9F5A6")

IMCS_DECL_INTERFACE(IMcPPRDBAccess,         "D2FE705E-00F7-4477-9EB7-C9A742EDA29A")
IMCS_DECL_INTERFACE(IMcPPRBArea,            "00000001-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRLArea,            "00000002-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRSArea,            "00000003-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRRArea,            "00000004-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRPArea,            "00000005-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRDZone,            "00000006-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRWZone,            "00000007-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRGraphic,          "00000008-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRProject,          "00000009-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRTempBuilding,     "00000010-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRUCBuilding,       "00000011-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRExistingBuilding, "00000012-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRBreakingBuilding, "00000013-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRStorageItem,      "00000014-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRWheelWashing,     "00000015-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRSlope,            "00000016-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRGeneralRoad,      "00000017-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRRoadSection,      "00000018-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRLinearObject,     "00000019-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRPointObject,      "0000001A-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNewPPRProject,       "0000001B-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcAlbums,              "001C0429-26D1-47da-9529-2C9F0DC9B8D9")
IMCS_DECL_INTERFACE(IMcAlbumsNode,          "91A335F3-7CAA-48d8-A272-B8AEFFC2981F")
IMCS_DECL_INTERFACE(IMcPPRRoadCross,        "0000001C-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRComplexSign,      "0000001D-0021-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPPRMovementScheme,   "0000001E-0021-AAAA-AAAA-050B00000000")
//объявляется в IPPR.h
//IMCS_DECL_INTERFACE(IMcPPRManagerDlg,          "")
IMCS_DECL_INTERFACE(IMcFormat,              "F000001C-0004-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcFormatStamp,         "B6D73FE8-F6A5-4fb4-9800-B5C8BEF68F18")
IMCS_DECL_INTERFACE(IMcSubObject,           "A88E7F39-0923-4534-A505-B41E3F30CE52")         // IMcSymbols.h


//////////////////////////////////////////////////////////////////////////
//PT
IMCS_DECL_INTERFACE(IMcPTBaseWall,          "00000011-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTWall,              "00000001-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTPolyWall,          "00000002-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTColumn,            "00000003-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTWindow,            "00000004-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTRoom,              "00000005-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTFlat,              "00000006-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTFloor,             "00000007-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTStair,             "00000008-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTObject,            "00000009-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcConjuncter,          "00000010-0016-AAAA-AAAA-050B00000000")//Пока абстрактный объект
IMCS_DECL_INTERFACE(IMcComplex,             "0000000A-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTWallModifier,      "0000000B-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTDoor,              "0000000C-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTWallObject,        "0000000D-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTUserObject,        "0000000E-0016-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcPTAreaObject,        "0000000F-0016-AAAA-AAAA-050B00000000")//Базовый площадной объект
IMCS_DECL_INTERFACE(IMcPTCadastralObject,   "0000002B-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTLand,              "00000012-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTLandPart,          "00000013-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTBuilding,          "00000014-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTBuildingPart,      "00000015-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTBorder,            "00000017-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTInfoPoint,         "00000018-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTGeoPointLoader,    "00000019-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTBorderObject,      "0000001A-0016-AAAA-AAAA-050B00000000")

	// AGL: дублировался с IMcDimGraph, заменил категорию с 4 на 16, так правильнее,
	// конвертация GUID прописана
IMCS_DECL_INTERFACE(IMcPTLineObject,        "0000001B-0016-AAAA-AAAA-050B00000000")

	// AGL: категория должна быть 16, а не 4,
	// дублировался с IMcFormat, на IMcFormat уже другой GUID
IMCS_DECL_INTERFACE(IMcPTPointObject,       "0000001C-0004-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcPTServicePrintArea,  "0000001D-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTDirectionIndicator,"0000001E-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTSheetsArrangeScheme, "0000001F-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTTag,               "00000020-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTPrintManager,      "00000021-0016-AAAA-AAAA-050B00000000")
//complex extensions
IMCS_DECL_INTERFACE(IMcPTComplexPart,       "00000022-0016-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcPTComplexContour,    "00000023-0016-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcPTComplexContourConverter, "00000024-0016-AAAA-AAAA-050B00000000");

IMCS_DECL_INTERFACE(IDBObjectContainerWall, "00000025-0016-AAAA-AAAA-050B00000000");

IMCS_DECL_INTERFACE(IMcPTCheckPlanTool,     "00000026-0016-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcPTFlatPart,          "00000027-0016-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcPTRightObject,          "00000028-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTRightObjectOriginal,  "00000029-0016-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPTRightObjectSecondary, "0000002A-0016-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcPTParkingPlace,         "0000002C-0016-AAAA-AAAA-050B00000000")

//////////////////////////////////////////////////////////////////////////
/// Составные контура второй версии
//контур
IMCS_DECL_INTERFACE(IMcComplexContour,                  "00000001-0022-AAAA-AAAA-050B00000000");

//рисователь контуров
IMCS_DECL_INTERFACE(IMcComplexContourDrawer,            "00000002-0022-AAAA-AAAA-050B00000000");
//построитель контуров
IMCS_DECL_INTERFACE(IMcComplexContourBuilder,           "00000003-0022-AAAA-AAAA-050B00000000");
//инструмент для редактирования контура за ручки (грипы)
IMCS_DECL_INTERFACE(IMcComplexContourGripsManager,      "00000005-0022-AAAA-AAAA-050B00000000")

//entity "Составной контур"
IMCS_DECL_INTERFACE(IMcComplexSymbol,                   "00000004-0022-AAAA-AAAA-050B00000000");

//зависимость
IMCS_DECL_INTERFACE(IMcComplexConstraint,               "00000006-0022-AAAA-AAAA-050B00000000");

//фигуры-части
IMCS_DECL_INTERFACE(IMcComplexPart,                     "00000200-0022-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcComplexPartGhost,                "00000210-0022-AAAA-AAAA-050B00000000"); //часть-призрак, для обратной совместимости (см. документацию)

IMCS_DECL_INTERFACE(IMcComplexPartRectangle,            "00000201-0022-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcComplexPartTriangle,             "00000202-0022-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcComplexPartRectangularTriangle,  "00000203-0022-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcComplexPartLineSeg,              "00000204-0022-AAAA-AAAA-050B00000000"); //используется для отсчётов
IMCS_DECL_INTERFACE(IMcComplexPartTrapezium,            "00000205-0022-AAAA-AAAA-050B00000000"); //трапеция
IMCS_DECL_INTERFACE(IMcComplexPartRegularTrapezium,     "00000206-0022-AAAA-AAAA-050B00000000"); //правильная трапеция (боковые стороны всегда наклонены друг к другу)
IMCS_DECL_INTERFACE(IMcComplexPartRectangularTrapezium, "00000207-0022-AAAA-AAAA-050B00000000"); //прямоугольная трапеция
IMCS_DECL_INTERFACE(IMcComplexPartCircle,               "00000208-0022-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcComplexPartArcSegment,           "00000209-0022-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcComplexPartOrtoContour,          "00000211-0022-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcComplexPartPolyline,             "00000212-0022-AAAA-AAAA-050B00000000"); //обёртка вокруг обычной полилинии, только для чтения
IMCS_DECL_INTERFACE(IMcComplexPartFreeContour,          "00000213-0022-AAAA-AAAA-050B00000000"); //только линейные сегменты!
IMCS_DECL_INTERFACE(IMcComplexPartComplexContour,       "00000214-0022-AAAA-AAAA-050B00000000"); //позволяет добавлять в контур другие контура в качестве частей

//конвертер старых контуров в новые
IMCS_DECL_INTERFACE(IMcComplexConverter,    "00000007-0022-AAAA-AAAA-050B00000000");


//////////////////////////////////////////////////////////////////////////
// References
IMCS_DECL_INTERFACE(IMcReferenceItem,       "00000027-0004-AAAA-AAAA-050B00000000")     // ссылка на объект для IMcReferenceExtension
IMCS_DECL_INTERFACE(IMcReferenceExtension,  "00000028-0004-AAAA-AAAA-050B00000000")     // выдаёт зависимости от других объектов
IMCS_DECL_INTERFACE(IMcCellExtension,       "0000001F-0004-AAAA-AAAA-050B00000000")     // выдаёт координаты полей

//////////////////////////////////////////////////////////////////////////
// GNB
IMCS_DECL_INTERFACE(IMcGNBGrid,             "00000001-0023-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcGNBProfile,          "00000002-0023-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcGNBTrace,            "00000003-0023-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcGNBUtilityLines,     "00000004-0023-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcGNBEditController,   "00000005-0023-AAAA-AAAA-050B00000000");



//////////////////////////////////////////////////////////////////////////
// Modeler, other particular interfaces of modeler are in IMcModeler.h
IMCS_DECL_INTERFACE(IMcModeler,              "00000001-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdWorkPoint,            "00000002-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdWorkAxis,             "00000003-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdWorkPlane,            "00000004-0018-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMdPlanarSketch,         "00000005-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdSketchEntity,         "00000006-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdSketchPoint,          "00000007-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdSketchLine,           "00000008-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdSketchCircArc,        "00000009-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdSketchEllipArc,       "0000000A-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdGeomConstraint,       "0000000B-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdDimConstraint,        "0000000C-0018-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMdProfile,              "0000000D-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdProfilePath,          "0000000E-0018-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMdFeature,              "0000000F-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdExtrudeFeature,       "00000010-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdRevolveFeature,       "00000011-0018-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMdFace,                 "00000012-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdEdge,                 "00000013-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdVertex,               "00000014-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdParameter,            "00000015-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dBodyConstructor,    "00000016-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdExtrudeAlongPathFeature,   "00000018-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdRectangularPatternFeature, "00000019-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdCircularPatternFeature,    "00000020-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdMirrorFeature,        "00000021-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdOffsetFeature,        "00000022-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdTubingFeature,        "00000023-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdSeparateFeature,      "00000024-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdSeparateByPartFeature,"00000025-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdChamferFeature,       "00000026-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdFilletFeature,        "00000027-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdLoftFeature,          "00000028-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdCoilFeature,          "00000029-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdBooleanFeature,       "0000002A-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dNativeBodyConstructor, "0000002B-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdThreadFeature,        "0000002C-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdCustomExternalFeature, "0000002D-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdAlienFeature,          "0000002E-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdHoleFeature,          "0000002F-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMdPlanarSliceFeature,   "00000030-0018-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMc3dWorkPoint,          "00000001-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dWorkAxis,           "00000002-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dWorkPlane,          "00000003-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dBody,               "00000004-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dSolid,              "00000005-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dAlienSolid,         "00000006-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcFeatureEntity,        "00000007-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dDocHistory,         "00000008-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dCoordSysObject,     "00000009-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPlanarSketch,         "0000000A-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSketchProfile,        "0000000B-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcProjSketchEnt,        "0000000C-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dHistoryItem,        "0000000D-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dExtrudeFeature,     "0000000E-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dRevolveFeature,     "0000000F-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dChamferFeature,     "00000010-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dCircPatFeature,     "00000011-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dRectPatFeature,     "00000012-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dCoilFeature,        "00000013-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dMirrorFeature,      "00000014-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dRibFeature,         "00000015-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dShellFeature,       "00000016-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dSweepFeature,       "00000017-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dGSBasedBRepIDInfoOld, "00000018-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dFEVGeomCache,       "00000019-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dFEVIDInfo,          "0000001A-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dAlienSolidData,     "0000001B-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dArrFeatureType,     "0000001C-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dFilletFeature,      "0000001D-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dEdgeFeatureType,    "0000001E-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dLoftFeature,        "0000001F-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dSection,            "00000020-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dDrawingView,        "00000021-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcProfileContourData,   "00000022-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dHistoryItemExt,     "00000023-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(McEntBaseBindSwitcher,   "00000024-3D3D-AAAA-AAAA-050B00000000") // default ent-binding switched
IMCS_DECL_INTERFACE(Mc3dnStdEntSwitcher,     "00000025-3D3D-AAAA-AAAA-050B00000000") // 3dSolid + StdPart ent-binding switcher
IMCS_DECL_INTERFACE(Mc3dNetEntSwitcher,      "00000026-3D3D-AAAA-AAAA-050B00000000") // 3dSolid + StdPart ent-binding switcher
IMCS_DECL_INTERFACE(IMc3dConstraint,         "00000027-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dConstraintCompatible, "00000028-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dConstraintsEvaluator, "00000029-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dBooleanFeature,     "0000002A-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dNativeSolid,        "0000002B-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dThreadFeature,      "0000002C-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc2dCtrsGroup,          "0000002D-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcCustomExternalFeature, "0000002E-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcAssocVariable,        "0000002F-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dHole,               "00000030-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dPart,               "00000031-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcHlrEngine2,           "00000032-3D3D-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3dPartsManipulator,   "00000033-3D3D-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMc3dDrawingViewBreak,   "B1667CD2-2245-44F2-A9F5-A861417A0285") // Mapinet.Break2d  - 3D-обрыв

IMCS_DECL_INTERFACE(IMc3dSmFeature,          "00000034-3D3D-AAAA-AAAA-050B00000000") // Mc3dSheetMetal:SmSheetMetalFeature - базовый функционал листовых тел
IMCS_DECL_INTERFACE(IMc3dSmSheetSolid,       "B83C9FC5-A446-40A6-996B-526B145EEA36") // Mc3dSheetMetal:SmSheetSolid        - листовое тело
IMCS_DECL_INTERFACE(IMc3dSmPlate,            "074E06C1-0285-4B72-8C26-9680D380089A") // Mc3dSheetMetal:SmPlate             - пластина листового тела
IMCS_DECL_INTERFACE(IMc3dSmHole,             "15DF541D-C38B-44A9-8781-6E0879AEF503") // Mc3dSheetMetal:SmHole              - вырез в листовом теле
IMCS_DECL_INTERFACE(IMc3dSmEdge,             "F92C3688-91E1-436F-8266-9119A3625D71") // Mc3dSheetMetal:SmEdge              - сгиб листового тела по ребру
IMCS_DECL_INTERFACE(IMc3dSmFlanging,         "28AB4E79-A432-4002-BD92-96A984CE79B3") // Mc3dSheetMetal:SmFlanging          - отбортовка листового тела
IMCS_DECL_INTERFACE(IMc3dSmBendOverSeg,      "AA490B14-2759-41BE-966C-2D6EE43D5257") // Mc3dSheetMetal:SmBendOverSegment   - сгиб по линии листового тела
IMCS_DECL_INTERFACE(IMc3dSmJointBend,        "43B8C985-DD0F-4B0D-8768-3C11BCA8CA0A") // Mc3dSheetMetal:SmJointBend         - сгиб по эскизу листового тела
IMCS_DECL_INTERFACE(IMc3dSmJog,              "CBC0B76A-4392-4182-A25E-370329DC76C0") // Mc3dSheetMetal:SmJog               - подсечка листового тела
IMCS_DECL_INTERFACE(IMc3dSmBead,             "AD1EC8C9-6A95-4847-805A-8EC2F1ABE55D") // Mc3dSheetMetal:SmBead              - буртик листового тела
IMCS_DECL_INTERFACE(IMc3dSmCorner,           "4333DD31-7FAE-4545-8243-F63F1A215C27") // Mc3dSheetMetal:SmCorner            - замыкание углов листового тела
IMCS_DECL_INTERFACE(IMc3dSmRib,              "A2EF9E89-C816-450E-8FA1-8FDC4A4232AC") // Mc3dSheetMetal:SmRib               - ребро жесткости листового тела
IMCS_DECL_INTERFACE(IMc3dSmStamp,            "4284EB88-2F1E-429C-A37C-BD7A4CDCF644") // Mc3dSheetMetal:SmStamp             - штамповка листового тела
IMCS_DECL_INTERFACE(IMc3dSmJalousie,         "DE7C93F3-70B3-4263-B467-84B1A2C218F3") // Mc3dSheetMetal:SmJalousie          - жалюзи листового тела
IMCS_DECL_INTERFACE(IMc3dSmRuledBase,        "00000035-3D3D-AAAA-AAAA-050B00000000") // Mc3dSheetMetal:SmRuledBase         - базовый функционал для обечайки
IMCS_DECL_INTERFACE(IMc3dSmRuledSolid,       "BB9FB028-C476-4635-A066-0E2EBCAFF54C") // Mc3dSheetMetal:SmRuledSolid        - листовое тело в виде обечайки
IMCS_DECL_INTERFACE(IMc3dSmRuledLine,        "A88CD61F-771C-488E-8DCD-ADE170432E3B") // Mc3dSheetMetal:SmRuledLine         - листовое тело в виде линейчатой обечайки
IMCS_DECL_INTERFACE(IMc3dSmBend,             "EEDF7452-1458-492F-AEFD-FCCCFBFBDB2B") // Mc3dSheetMetal:SmBend              - сгиб листового тела
IMCS_DECL_INTERFACE(IMc3dSmUnbend,           "E9477B11-D0FB-4F43-9BD5-8D7CDC510ED9") // Mc3dSheetMetal:SmUnbend            - разгиб листового тела
IMCS_DECL_INTERFACE(IMc3dSmFlatten,          "B120690A-3832-482F-A550-D7A0012D105A") // Mc3dSheetMetal:SmReamer            - развертка листового тела
IMCS_DECL_INTERFACE(IMc3dSmCurling,          "8BBF4254-6197-4CF8-82B8-D76492394A39") // Mc3dSheetMetal:SmCurling           - завальцовка на листовом теле
IMCS_DECL_INTERFACE(IMc3dSmJumping,          "3B7EFBE2-8041-4007-A0C0-C357EB07DFB1") // Mc3dSheetMetal:SmJumping           - перемычка между листовыми телами
IMCS_DECL_INTERFACE(IMc3dSmEdgeCommon,       "207385DE-7D86-4B73-96D9-9A8F85B38FFB") // Mc3dSheetMetal:none                - Общий интерфейс между SmEdge и SmFlanging
IMCS_DECL_INTERFACE(IMc3dSmOverSegCommon,    "AD607B63-55AD-464F-9A01-97BDBBBB26EC") // Mc3dSheetMetal:none                - Общий интерфейс между SmBendOverSeg и SmJog
IMCS_DECL_INTERFACE(IMc3dSmRulidBase,        "3721018D-F8A4-4F64-AF5B-5EA6EF938F09") // Mc3dSheetMetal:SmRuledBase         - Общий интерфейс между SmRuledLine и SmRuledSolid
IMCS_DECL_INTERFACE(IMc3dSmBendCommon,       "C25B8B5D-ABBB-4304-BDFE-0E66E5AC185D") // Mc3dSheetMetal:none                - Общий интерфейс между SmBend и SmUnbend
IMCS_DECL_INTERFACE(IMc3dSmCornerProcessing, "C25B7EDA-61F6-4F45-AA6E-52E3B2B43495") // Mc3dSheetMetal:none                - Общий интерфейс между SmEdge, SmFlanging, SmJointBend
IMCS_DECL_INTERFACE(IMc3dSmBendRelease,      "E57967DC-A209-4BF9-9E91-F6E8E87AEFDA") // Mc3dSheetMetal:none                - Общий интерфейс между SmEdge, SmFlanging, SmJointBend

IMCS_DECL_INTERFACE(IMc3dDocHistDataContainer, "11000011-3D3D-AAAA-AAAA-050B00000000")

// нумерация как в моделер, раньше лежало в imcsurfacebody.h, IMcFace, IMcEdge реализовано в McTyp.
IMCS_DECL_INTERFACE(IMcFace,                "10000200-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcEdge,                "10000201-0018-AAAA-AAAA-050B00000000")
//IMCS_DECL_INTERFACE(IMcSurfaceBody,         "10000202-0018-AAAA-AAAA-050B00000000")
//IMCS_DECL_INTERFACE(McAcisSurfaceBodyImpl,  "10000203-0018-AAAA-AAAA-050B00000000")
//IMCS_DECL_INTERFACE(McAcadSurfaceBodyImpl,  "10000204-0018-AAAA-AAAA-050B00000000")
// работала нестабильно.
//IMCS_DECL_INTERFACE(McOccSurfaceBodyImpl,   "10000205-0018-AAAA-AAAA-050B00000000")
// недореализован в modeler.
//IMCS_DECL_INTERFACE(McSurfaceBodyImpl,      "10000206-0018-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcPlane,               "10000207-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcCone,                "10000208-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcTorus,               "10000209-0018-AAAA-AAAA-050B00000000")
//IMCS_DECL_INTERFACE(IMcVertex,              "10000210-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcBodyInt,             "10000211-0018-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcBodyRef,             "10000212-0018-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcDBManager,           "00000001-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcFoundedWindow,       "00000002-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcNMKFilter,           "00000003-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDBElementFilterCtrl, "00000004-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDBElementFilter,     "00000005-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcSimpleXMLPropertySrc,"00000006-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcMgdXmlPropertySrc,   "00000007-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IDBObjectContainer,     "00000008-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IDBTemplateList,        "00000009-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcMgdCaller,           "0000000A-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcXmlPropertyContainer,"0000000B-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcPropertyTree,        "0000000D-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcGanttBase,           "0000000E-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcGanttChart,          "0000000F-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcGanttCalendar,       "00000010-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcDotNetObject,        "00000011-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcRtfFilter,           "00000012-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcRtfWriter,           "00000013-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcRtfEmbedding,        "00000014-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcRtfEmbeddedHyperlink,"00000015-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcRtfEmbeddedObject,   "00000016-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcRtfEmbeddedReference,"00000017-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcRtfEmbeddedSpecPositionReference, "00000018-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMc3DHistoryPanel,      "00000019-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcBimTreeView,         "0000001A-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcBimDirectoryTool,    "0000001B-0020-AAAA-AAAA-050B00000000")
IMCS_DECL_INTERFACE(IMcRtfUtils,            "00000020-0020-AAAA-AAAA-050B00000000")

IMCS_DECL_INTERFACE(IMcProject,             "00000001-0024-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcPrjNode,             "00000002-0024-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcInsertionNode,       "00000003-0024-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcObjNode,             "00000004-0024-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcObjectAdapter,       "00000005-0024-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcBasePrjNode,         "00000006-0024-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcZone,                "00000007-0024-AAAA-AAAA-050B00000000");
//IMCS_DECL_INTERFACE(IMcProjectTransaction,  "00000008-0024-AAAA-AAAA-050B00000000");
//IMCS_DECL_INTERFACE(IMcProjectObjectTransaction, "00000009-0024-AAAA-AAAA-050B00000000");
//IMCS_DECL_INTERFACE(IMcProjectUndoRedoController, "00000010-0024-AAAA-AAAA-050B00000000");
IMCS_DECL_INTERFACE(IMcNodeGroup,           "00000011-0024-AAAA-AAAA-050B00000000");

IMCS_DECL_INTERFACE(KmObjectInstance, "3310a23f-3487-4774-ac8d-2f74609f0868"); // колонна, балка
IMCS_DECL_INTERFACE(KmPlateInstance,  "f9b9530a-887c-4a3f-afb5-31fe5cf21d8b"); // пластина
IMCS_DECL_INTERFACE(KmViewInst,       "5F8B3973-CD79-4cb3-9C9F-9F74BC96EEC8"); // Вид КМ
IMCS_DECL_INTERFACE(KmJointInst,      "147BEAAB-3628-4D36-AC80-ED9821D3A59B"); // Узел КМ

IMCS_DECL_INTERFACE(McSlab, "b03bab08-646b-4a8e-9d8f-6d1afd315570");
IMCS_DECL_INTERFACE(McRoof, "c8f759b2-4df4-4441-acf7-98ee8410d9a2");

IMCS_DECL_INTERFACE(McDefaultObjectAdapter, "318386F4-E8CD-47d6-B1F7-97211A2E0AFE");
static const GUID CLSID_McDefaultObjectAdapter = IID_McDefaultObjectAdapter;

IMCS_DECL_INTERFACE(DesignElement, "C628FA55-4679-4e5d-A6C5-DEEFD66D400F");

IMCS_DECL_INTERFACE(IMcStdPart, "EB98CA4F-8D76-4d9c-B792-C7A589D93EC5");
static const GUID CLSID_IMcStdPart = IID_IMcStdPart;

IMCS_DECL_INTERFACE(IMcStdPart2d, "EDDDD002-8D76-4d9c-B792-C7A589D93EC5");
IMCS_DECL_INTERFACE(IMcStdPart3d, "EDDDD003-8D76-4d9c-B792-C7A589D93EC5");

IMCS_DECL_INTERFACE(Net_Connector, "27B6929F-070C-4A90-AE48-4698239D81E9"); // Инженерные сети: коннектор
IMCS_DECL_INTERFACE(Net_Equipment, "839D2BD9-7957-4D82-9BD3-5B696FBD4B40"); // Инженерные сети: оборудование
IMCS_DECL_INTERFACE(Net_Trace,     "00DB649A-633B-43CF-9C45-D29D6E5FDF2C"); // Инженерные сети: трасса

struct IMcNativeEventsInput;
struct McBaseEventsSink;
struct IMcEventsSink;
struct IMcInputEventsSink;
struct IMcWndHook;

template<class TYPE, class ARG_TYPE> class McsArray;

typedef McsArray<MComPtr<IUnknown>,   IUnknown*>    mcsIUnknownArray; 
typedef McsArray<IMcObjectPtr,        IMcObject*>   mcObjectsArray;
typedef McsArray<IMcEntityPtr,        IMcEntity*>   mcEntityArray;
typedef McsArray<IMcDbObjectPtr,      IMcDbObject*> mcDbObjectArray;
typedef McsArray<IMcDbEntityPtr,      IMcDbEntity*> mcDbEntityArray;
typedef McsArray<IMcDocumentPtr,      IMcDocument*> mcDocumentsArray;

//typedef McsArray<IMcDbReferenceEntityPtr,IMcDbReferenceEntity*> IMcDbReferenceEntities;
//typedef McsArray<IMcReferenceEntityPtr,IMcReferenceEntity*> mcReferenceEntities;

typedef McsArray<IMcEventsSink*,      IMcEventsSink*>      mcEventsSinkArray;
typedef McsArray<IMcInputEventsSink*, IMcInputEventsSink*> mcInputEventsSinkArray;
typedef McsArray<IMcWndHook*,         IMcWndHook*>         mcWndHookArray;
typedef McsArray<IMcUndoPoint*,       IMcUndoPoint*>       mcUndoPointArray;
typedef McsArray<IMcLCPtr,            IMcLC*>              IMcLCs;

//=============================================================================
//Тип команды для регистрации
struct MCSVariant;
typedef void (*mcsCmdFunctionPtr)(MCSVariant* pCustomParams);

//структура регистрации команды
struct mcsCmd
{
	DECLARE_OBJ_NEWDEL;

	mcsCmd();
	mcsCmd(mcsCmdFunctionPtr cmd, LPCTSTR stGlobalName, long Mode = MCS_CMD_REDRAW);
	virtual ~mcsCmd() {}

	virtual HRESULT Execute(MCSVariant* pCustomParams = NULL);
	virtual bool IsChecked()
		{ return false; }
	virtual bool IsEnabled()
		{ return true; }

	McsString stImg16;        // ID картинки в общей ресурсной библиотеке для меню
	McsString stLocalName;    // Local name
	McsString stGlobalName;   // Global name
	McsString stHelpID;       // Help ID
	McsString stToolTip;      // Comment
	long lMode;               // For AutoCAD now
	long lApps;               // Applications см MCS_AppId
	mcsCmdFunctionPtr Command;// Указатель на команду
};

//----------------------------------------
// base
#ifndef REAL 
typedef double REAL;
#endif

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef UNKNULL
#define UNKNULL ((IUnknown*)NULL)
#endif

#ifndef M_RET
typedef int M_RET;
#endif

#ifndef M_HANDLE
typedef __int64 M_HANDLE;
#endif

#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec( dllexport ) 
#endif


//////////////////////////////////////////
//----------------------------------------
// IMObject - базовый интерфейс
//----------------------------------------
#ifndef IMOBJECTDEFINED
	#define IMOBJECTDEFINED

	class IMObject
	{
		protected:
			volatile ULONG m__dwRefCnt;

		public:
			DECLARE_OBJ_NEWDEL;

			IMObject() {
				m__dwRefCnt = 1;
			}

			virtual ~IMObject() {
			}

			// __stdcall is added to catch out all usage cases
			MT_API virtual ULONG __stdcall AddRef();
			MT_API virtual ULONG __stdcall Release();
	};

	#define M_STUB_STANDARD_METHODS \
		virtual ULONG __stdcall AddRef() override { return 1; } \
		virtual ULONG __stdcall Release() override { return 1; }

	#define M_STANDARD_METHODS you_dont_need_to_declare_M_STANDARD_METHODS_anymore
// 	#define M_STANDARD_METHODS(m_dwNumRef) \
// 		virtual DWORD AddRef() { return ++m_dwNumRef; }; \
// 		virtual void Release() { --m_dwNumRef;  if (m_dwNumRef == 0) delete this; };

#endif // IMOBJECTDEFINED

//==============================================================================
// added by AGL
template <class T>
class MObjPtr
{
public:
	T* p;

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MObjPtr() {
		p = NULL;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	template<class F>
	MObjPtr(F* lp, bool bAddRef = true)
	{
		p = NULL;
		if(bAddRef) {
			if(_safe_addref4ptr(lp))
				p = dynamic_cast<T*>(lp);
		} else {
			Attach(dynamic_cast<T*>(lp));
		}
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MObjPtr(const MObjPtr<T>& lp)
	{
		p = NULL;
		DBG_RELEASE_P;
		if(_safe_addref4ptr(lp.p))
			p = lp.p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	template<class F>
	MObjPtr(const MObjPtr<F>& lp)
	{
		p = NULL;
		DBG_RELEASE_P;
		if(_safe_addref4ptr(lp.p))
			p = dynamic_cast<T*>(lp.p);
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	~MObjPtr() {
		_safe_release4ptr(p);
		p = NULL;
		DBG_RELEASE_P;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	void Release() {
		_safe_release4ptr(p);
		p = NULL;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	operator T*() const
	{
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MObjPtr::operator T*(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return NULL;
		}
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T& operator*() const
	{
		MCSASSERT(p != NULL);
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MObjPtr::operator *(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return *(T*)NULL;
		}
		return *p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T** operator&() {
		MCSASSERT(p==NULL);
		return &p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* operator->() const
	{
		MCSASSERT(p!=NULL);
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MObjPtr::operator ->(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return NULL;
		}
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	template<class F>
	T* operator = (F* lp)
	{
		_safe_release4ptr(p);
		p = NULL;
		if(_safe_addref4ptr(lp))
			p = dynamic_cast<T*>(lp);
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* operator = (const MObjPtr<T>& lp)
	{
		_safe_release4ptr(p);
		p = NULL;
		if(_safe_addref4ptr(lp.p))
			p = lp.p;
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	template<class F>
	T* operator = (const MObjPtr<F>& lp)
	{
		_safe_release4ptr(p);
		p = NULL;
		if(_safe_addref4ptr(lp.p))
			p = dynamic_cast<T*>(lp.p);
		return p;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	bool operator ! () const
	{
		if(!p)
			return true;
		if(!_is_valid_interfacePtr4ptr(p)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MObjPtr::operator bool(), this->p is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return true;
		}
		return false;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	bool operator < (T* pT) const {
		return p < pT;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	bool operator == (T* pT) const {
		return p == pT;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	void Attach(T* p2)
	{
		_safe_release4ptr(p);
		p = NULL;
		if(!_is_valid_interfacePtr4ptr(p2)) {
			MESSAGE_ERR_NOCP(_T("ALERT! MObjPtr::Attach(ptr), [ptr] is invalid"));
			if(IsDebuggerPresent())
				DebugBreak();
			return;
		}
		p = p2;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	T* Detach() {
		T* pt = p;
		p = NULL;
		return pt;
	}
};
typedef MObjPtr<IMObject> IMObjectPtr;

//=============================================================================
// (!) Значения не менять, пишутся в файл
enum mcsWorkIDOptionsEnum
{
	mcsWorkID_DefOption         = 0xFFFFFFFF,
	mcsWorkID_FORCE_CONVERT_ID  = 0x1, // in transferLinks tells to subst source ID in any case to new value
	mcsWorkID_ID_CAN_RESET      = 0x2, // indicates for transferLinks that this ID refers to links pair and can be reset when need
	mcsWorkID_ID_IS_OBJECT_ID   = 0x4, // force this ID is object ID
	mcsWorkID_ID_IS_GUID        = 0x8, // ID is not refers to any object, i.e. is GUID in mcsWorkID form
	mcsWorkID_ID_HardRef        = 0x10|mcsWorkID_ID_IS_OBJECT_ID, // Hard-Reference, also this is object ID by definition
	mcsWorkID_ID_IS_Subent      = 0x20, // refers to subentity, for debug & info purposes only
	mcsWorkID_ID_PartOfCompound = 0x40|mcsWorkID_ID_IS_OBJECT_ID, // id is part of ids path in compound id (mcsComplexWorkID)
	mcsWorkID_ID_KeepRefOnCopy  = 0x80,// Ссылка на объект, по возможности будет сохранена даже в случае, когда не попадёт в копируемую группу.

	mcsWorkID_referencedInStream = 0x100, // системное, не применять в пользовательском коде

	mcsWorkID_InexactFEV        = 0x200, // используется на Face/Edge/Vertex как признак того, что FEV по этому ID нужно искать неточно.
};
//===========================================================================
struct mcsWorkID
{
public:
	GUID  ID;
	DWORD options;
	//......................

public:
	mcsWorkID() { setNull(); }
	mcsWorkID(const mcsWorkID& SrcID) { *this = SrcID; }
	//......................
	mcsWorkID(const GUID& guid) { ID = guid; options = mcsWorkID_DefOption; }
	//......................
	bool getStrID(char* pDestStrID, const int BufSize) const
	{
		LPOLESTR tmpstr; if (FAILED(StringFromCLSID(ID, &tmpstr))) return false;
		_bstr_t tstr(tmpstr); lstrcpynA(pDestStrID, tstr, BufSize);
		CoTaskMemFree(tmpstr);
		return true;
	}
	//......................
	McsString asString() const
	{
		McsString str;
		getStrID(str);
		return str;
	}
	//......................
	MCTYP_API McsString asStringShort() const;
	//......................
	bool getStrID(OUT McsStringA& str) const
	{
		str.Empty();
		LPOLESTR tmpstr;
		if (FAILED(StringFromCLSID(ID, &tmpstr))) return false;
		McsStringW wstr = tmpstr;
		str = wstr.asMB();
		CoTaskMemFree(tmpstr);
		return true;
	}
	//......................
	bool getStrID(OUT McsStringW& str) const
	{
		str.Empty();
		LPOLESTR tmpstr;
		if (FAILED(StringFromCLSID(ID, &tmpstr))) return false;
		str = tmpstr;
		CoTaskMemFree(tmpstr);
		return true;
	}
	//......................
	bool getStrID(OLECHAR* pDestStrID, const int BufSize) const
	{
		LPOLESTR tmpstr; if (FAILED(StringFromCLSID(ID, &tmpstr))) return false;
		lstrcpynW(pDestStrID, tmpstr, BufSize);
		CoTaskMemFree(tmpstr);
		return true;
	}
	//......................
	bool setStrID(const char* pSrcStrID)
	{
		if (pSrcStrID == NULL)
		{
			setNull(); return true;
		}
		options = mcsWorkID_DefOption;
		_bstr_t tstr(pSrcStrID);
		if (FAILED(CLSIDFromString(tstr, &ID))) return false;
		return true;
	}
	//......................
	bool setStrID(const OLECHAR* pSrcStrID)
	{
		if (pSrcStrID == NULL)
		{
			setNull(); return true;
		}
		options = mcsWorkID_DefOption;
		if (FAILED(CLSIDFromString((OLECHAR*)pSrcStrID, &ID))) return false;
		return true;
	}
	//......................

	// Если ID относится к объекту, то по возможности возвращает имя его класса
	MCTYP_API McsString getClassString() const;

	// Возвращает строку с отладочной информацией, касающейся данного ID
	MCTYP_API  McsString getDbgString(LPCTSTR pfx = _T("")) const;
	//......................

	bool IsNull(void) const;
	bool isNull(void) const;
	//......................

	void setNull(void) {
		ID = GUID_NULL;
		options = mcsWorkID_DefOption;
	}
	//......................
	mcsWorkID& GenerateNewValue() {
		CoCreateGuid(&ID);
		options = mcsWorkID_DefOption;
		return *this;
	}
	//......................
	// use flags from mcsWorkIDOptionsEnum
	bool getOptions(DWORD optionsToCheck) const
	{
		if(0 == optionsToCheck)
			return false;
		if (options == mcsWorkID_DefOption)
			return false;
		return (options & optionsToCheck) != 0;
	}
	//......................
	// check ID contains ALL of given options
	bool hasOptions(DWORD optionsToCheck) const
	{
		if(0 == optionsToCheck)
			return false;
		if (options == mcsWorkID_DefOption)
			return false;
		return (options & optionsToCheck) == optionsToCheck;
	}
	//......................
	// use flags from mcsWorkIDOptionsEnum
	void setOptions(DWORD optionsToSet)
	{
		if(optionsToSet) {
			if (options == mcsWorkID_DefOption)
				options = 0;
			options |= optionsToSet;
		}
	}
	//......................

	// сброс указанных опций-флагов
	void resetOptions(DWORD optionsToReset)
	{
		if (optionsToReset && options != mcsWorkID_DefOption)
		{
			options &= ~optionsToReset;
			if (0 == options)
				options = mcsWorkID_DefOption;
		}
	}
	//......................
	// Если ID относится к объекту в документе, возвращает ID документа
	MCTYP_API mcsWorkID hostDocID() const;

	// То же, что и hostDocID но возвращает ID документа верхнего уровня
	MCTYP_API mcsWorkID hostTopDocID() const;

	// Если ID относится к объекту в документе, возвращает его хэндл, и опционально ID документа
	MCTYP_API __int64 handle(OUT OPTIONAL mcsWorkID* pDocID = NULL) const;

	// Возвращает ID объекта в документе по его хэндлу, если документ не указан, подразумевается активный
	MCTYP_API static mcsWorkID fromHandle(__int64 handle, IN OPTIONAL const mcsWorkID& docID = mcsWorkID());

	/// Если true, то это явное указание того, что идентификатор относится к объекту чертежа
	bool isObject() const {
		return hasOptions(mcsWorkID_ID_IS_OBJECT_ID);
	}

	/// Если true, то идентификатор по сути является Guid-ом,
	/// и к объекту скорее всего не имеет никакого отношения
	bool isGUID() const {
		return hasOptions(mcsWorkID_ID_IS_GUID);
	}

	/// Метод позволяет узнать, ссылается ли ID на поверхность 3D тела
	MCTYP_API bool isFace() const;

	/// Метод позволяет узнать, ссылается ли ID на ребро 3D тела
	MCTYP_API bool isEdge() const;

	/// Метод позволяет узнать, ссылается ли ID на вершину 3D тела
	MCTYP_API bool isVertex() const;

	/// Метод позволяет узнать, ссылается ли ID на поверхность/ребро/вершину 3D тела
	MCTYP_API bool isFEV() const;

	/// Метод позволяет узнать, ссылается ли ID на подобъект
	MCTYP_API bool isSubentity() const;

	/// Метод отдаёт соответствующий подобъекту маркер, если таковой возможно получить.
	/// (FYI: маркер не является постоянной ссылкой на элемент объекта)
	MCTYP_API McGSMarker gsMarker() const;

	/// Метод пытается вернуть идентификатор подобъекта по его маркеру и ID родителя
	MCTYP_API static mcsWorkID fromGsMarker(const mcsWorkID& idParent, McGSMarker gsm);

	/// Метод возвращает ID родительского объекта, если this-ID есть подобъект (subentity).
	/// Если ID не относится к подобъекту, то возвращает сам себя, если bRetThisIdIfNotSubent = true
	/// и WID_NULL, если bRetThisIdIfNotSubent = false
	MCTYP_API mcsWorkID parentID(bool bRetThisIdIfNotSubent = true) const;

	/// Если this ID ссылается на Face/Edge/Vertex, то возвращает ID фичи, которая создала этот FEV.
	/// Если host-фичу определить не получается, либо если ID не относится к FEV,
	/// то дальше поведение аналогично методу parentID.
	MCTYP_API mcsWorkID hostFeatureOrParentID(bool bRetThisIdIfNotSubent = true) const;

	/// Если this ID ссылается на Face/Edge/Vertex, то возвращает список всех ID фич, который создали этот FEV.
	/// Первой в списке идёт фича, которая создала элемент (её возвращает метод hostFeatureOrParentID),
	/// затем в списке идут фичи, которые модифицировали элемент (напр: меняли или резали).
	MCTYP_API bool hostFeaturesIDs(OUT mcsWorkIDArray& idsHostFeatures) const;

	/// Если this ID ссылается на Face/Edge/Vertex, то возвращает список всех ID фич, который создали и модифицировали этот FEV.
	MCTYP_API bool hostFeaturesIDs(OUT mcsWorkIDArray& idsCreatingHostFeatures, OUT mcsWorkIDArray& idsModifyingHostFeatures) const;

	/// Если this ID ссылается на Face/Edge/Vertex, то возвращает ассоциированный с ними ref-ключ.
	MCTYP_API const McFEVRefKey* fevRefKey() const;

	/// Метод пытается вернуть идентификатор подобъекта по его ref-ключу и ID родителя
	MCTYP_API static mcsWorkID fromRefKey(const mcsWorkID& idParent, const McFEVRefKey& rk);

	// Если this ID относится к 3D фиче, возвращает ассоциированный с ней уникальный
	// в пределах её host-тела DWORD
	MCTYP_API DWORD get3dFeatureDword() const;

	// Если this ID относится к 3D-построениям, возвращает DWORD-идентификаторы всех фич, относящихся к нему.
	MCTYP_API bool getAll3dFeaturesDwordsRelatedToObject(OUT mcsDwordSetEx& ftrIDs) const;

	//......................

	mcsWorkID& operator=(const mcsWorkID& SrcID) {
		ID = SrcID.ID;
		options = SrcID.options;
		return *this;
	}
	//......................
	mcsWorkID& operator=(const GUID& SrcGUID) {
		ID = SrcGUID;
		options = mcsWorkID_DefOption;
		return *this;
	}
	//......................
	mcsWorkID& operator=(const char* SrcStrID) {
		setStrID(SrcStrID);
		options = mcsWorkID_DefOption;
		return *this;
	}
	//......................
	mcsWorkID& operator=(const OLECHAR* SrcStrID) {
		setStrID(SrcStrID);
		options = mcsWorkID_DefOption;
		return *this;
	}
	//......................

	bool operator==(const mcsWorkID& ID2) const
	{
		return
			((__int64*)&ID)[0] == ((__int64*)&ID2.ID)[0] &&
			((__int64*)&ID)[1] == ((__int64*)&ID2.ID)[1];
		// Неоправданно медленно при частых вызовах (RMCS17676)
		//return (this->ID == ID2.ID)!=0;
	}
	//......................

	bool operator==(const GUID& ID2) const
	{
		return
			((__int64*)&ID)[0] == ((__int64*)&ID2)[0] &&
			((__int64*)&ID)[1] == ((__int64*)&ID2)[1];
		// Неоправданно медленно при частых вызовах (RMCS17676)
		//return (this->ID == ID2)!=0;
	}
	//......................

	bool operator!=(const mcsWorkID& ID2) const { return !(*this == ID2); }
	bool operator!=(const GUID& ID2) const { return !(*this == ID2); }
	bool operator < (const mcsWorkID& ID2) const { return (memcmp(&this->ID, &ID2.ID, sizeof(ID)) < 0); }
	bool operator > (const mcsWorkID& ID2) const { return (memcmp(&this->ID, &ID2.ID, sizeof(ID)) > 0); }
	bool operator <= (const mcsWorkID& ID2) const { return (memcmp(&this->ID, &ID2.ID, sizeof(ID)) <= 0); }
	bool operator >= (const mcsWorkID& ID2) const { return (memcmp(&this->ID, &ID2.ID, sizeof(ID)) >= 0); }
	operator const GUID& (void) const { return ID; }

	operator bool() const {
		return !isNull();
	}

	bool operator ! () const {
		return isNull();
	}

	// helpers, MCTYP.DLL is needed
	// Adds/removes reactor from the referenced objects to the given obj,
	MCTYP_API bool addReactor(const mcsWorkID& idTo, bool fApplyNow = true) const;
	MCTYP_API bool removeReactor(const mcsWorkID& idTo, bool fApplyNow = true) const;

private:
	// Блок операторов для блокировки бессмысленных неявных преобразований
	operator char() const { return 0; }
	operator short() const { return 0; }
	operator int() const { return 0; }
	operator unsigned() const { return 0; }
	operator __int64() const { return 0; }
};
//===========================================================================
template <> __inline UINT __stdcall McsHashKey <const mcsWorkID&> (const mcsWorkID& key)
{
	LPDWORD pdw = (LPDWORD)&key.ID;
	return (UINT)(pdw[0] ^ pdw[1] ^ pdw[2] ^ pdw[3]);
	// workID-ы содержащие GUID из gate->GetHandleFromWorkId, дают плохой хэш
	//UINT hash = McsHashKey<const GUID&>(key.ID);
	//return hash;
};
//===========================================================================
struct mcsWId2WIdMap;

struct mcsWorkIDArray : public McsArray <mcsWorkID>
{
	mcsWorkIDArray() : McsArray() {}
	mcsWorkIDArray(const mcsWorkIDArray& cf) : McsArray(cf) {}
	mcsWorkIDArray(const mcsWorkIDSetEx& cf) : McsArray(cf) {}
	mcsWorkIDArray(const mcsWorkIDSet& cf) : McsArray(cf) {}
	mcsWorkIDArray(const mcsWId2WIdMap& cf);

	void AsMap(OUT mcsWId2WIdMap& idmap, IN OPTIONAL UINT hashTableSize = -1) const;
	void operator &= (const mcsWId2WIdMap& idsMapFilter); // IDs sets intersection operation
	void operator &= (const mcsWorkIDSet& idsSet) { McsArray::Intersect(idsSet); }
	void operator &= (const mcsWorkIDSetEx& idsSet) { McsArray::Intersect(idsSet); }
	mcsWorkIDArray& operator << (const mcsWorkID& id) { McsArray::Add(id); return *this; }
	void setOptions(DWORD idOptions);
	bool containsAnyOf(const mcsWId2WIdMap& idsMap);
	bool containsAnyOf(const mcsWorkIDArray& ids) { return McsArray::containsAnyOf( (McsArray<mcsWorkID>&)ids); }
	bool containsAnyOf(const mcsWorkIDSet& idsSet) { return McsArray::containsAnyOf(idsSet); }
	bool containsAnyOf(const mcsWorkIDSetEx& idsSet) { return McsArray::containsAnyOf(idsSet); }
};
//===========================================================================
struct mcsWId2WIdMap : public McsMapEx<mcsWorkID,const mcsWorkID&,mcsWorkID,const mcsWorkID&>
{
  // inverts mapping left and right sides
  // ret:
  // S_OK:    all pairs inverted unambiguously
  // S_FALSE: pairs inverted but there are some unambiguous mapping (more than one for one left key) 
  HRESULT Inverse(OUT mcsWId2WIdMap& invertedMap, IN OPTIONAL UINT hashTableSize=0 /* 0: do not change size*/) const; 

  void operator |= (const mcsWorkIDArray& idarr); // IDs area unification
  void operator |= (const mcsWorkID& id); // unite ID
  void add(const mcsWorkID& id) { SetAt(id, id); }
};
//===========================================================================
__inline mcsWorkIDArray::mcsWorkIDArray(const mcsWId2WIdMap& cf)
{
	mcsWorkIDSet idSet;
	cf.getAsHashset(idSet);
	*this = idSet;
}
//===========================================================================
__inline HRESULT mcsWId2WIdMap::Inverse(OUT mcsWId2WIdMap& invertedMap,UINT hashTableSize) const 
{
	HRESULT hres=S_OK;
	invertedMap.RemoveAll();
	if(hashTableSize && hashTableSize != -1)
		invertedMap.InitHashTable(hashTableSize);

	if(m_fRawAccessEnabled)
	{
		for(mapidx mi = FirstIdx(); mi<m_nCount; ++mi)
		{
			const mcsWorkID& id1 = K(mi);
			const mcsWorkID& id2 = V(mi);
			mcsWorkID* pid1n = invertedMap.getExistingValPtr(id2);
			if(pid1n)
				hres = S_FALSE;
			invertedMap.SetAt(id2, id1);
		}
	}
	else
	{
		MCSPOSITION pos = GetStartPosition();
		while(pos)
		{
			mcsWorkID id1,id2;
			GetNextAssoc(pos, id1, id2);
			mcsWorkID id1n;
			if(invertedMap.Lookup(id2, id1n))
				hres = S_FALSE;
			invertedMap.SetAt(id2, id1);
		}
	}
	return hres;
}
//===========================================================================
__inline void mcsWorkIDArray::setOptions(DWORD idOptions)
{
	for(int i=0; i<m_nSize; i++) {
		m_pData[i].options = idOptions;
	}
}
//===========================================================================
__inline void mcsWorkIDArray::AsMap(OUT mcsWId2WIdMap& idmap, IN OPTIONAL UINT hashTableSize) const 
{
	idmap.RemoveAll();
	if(hashTableSize != -1 && hashTableSize)
		idmap.InitHashTable(hashTableSize);
	for(int i=0; i<m_nSize; i++)
		idmap.SetAt(m_pData[i], m_pData[i]);
}
//===========================================================================
__inline void mcsWorkIDArray::operator &= (const mcsWId2WIdMap& idsMapFilter)
{
	for(int i=m_nSize-1; i>=0; i--)
	{
		mcsWorkID tmpid;
		if(idsMapFilter.Lookup(m_pData[i], tmpid))
			continue;
		RemoveAt(i);
	}
}
//===========================================================================
__inline void mcsWId2WIdMap::operator |= (const mcsWorkIDArray& idarr)
{
	for(int i=0; i<idarr.GetSize(); i++) {
		const mcsWorkID& id = idarr.GetData()[i];
		SetAt(id, id);
	}
}
//===========================================================================
__inline void mcsWId2WIdMap::operator |= (const mcsWorkID& id)
{
	SetAt(id, id);
}
//===========================================================================

static const mcsWorkID WID_NULL;

//===========================================================================

__inline bool mcsWorkID::IsNull(void) const
{
	return *this == WID_NULL; // так быстрее
	//return !!(ID == GUID_NULL);
}
//===========================================================================

__inline bool mcsWorkID::isNull(void) const
{
	return *this == WID_NULL; // так быстрее
	//return !!(ID == GUID_NULL);
}
//===========================================================================


//---------------------------------------------------------
// IMCS_QI_METHOD_DEFINITION произвольной глубины вложенности
//---------------------------------------------------------
#define IMCS_QI_METHOD_DEFINITION_BEGIN(OBJECTTYPE) \
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvobj) { \
		*ppvobj = NULL; \
		if(riid == __uuidof(OBJECTTYPE)) { \
			*ppvobj=(OBJECTTYPE*)this; AddRef(); \
			return S_OK; \
		} \
		HRESULT hres = E_FAIL;

#define IMCS_QI_METHOD_DEFINITION_PROXY() \
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvobj) { \
		*ppvobj = NULL; \
		HRESULT hres = E_FAIL;

#define IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE) \
		hres = PARENTTYPE::QueryInterface(riid, ppvobj); \
		if(SUCCEEDED(hres)) \
			return hres;

#define IMCS_QI_METHOD_DEFINITION_END() \
		return hres; \
	}

//////////////////////////////////////////////////////////////////////////

#define IMCS_QI_METHOD_DEFINITION(OBJECTTYPE, PARENTTYPE) \
	IMCS_QI_METHOD_DEFINITION_BEGIN(OBJECTTYPE) \
		IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE) \
	IMCS_QI_METHOD_DEFINITION_END()

//..............................................................................

#define IMCS_QI_METHOD_DEFINITION3(OBJECTTYPE, PARENTTYPE1, PARENTTYPE2) \
	IMCS_QI_METHOD_DEFINITION_BEGIN(OBJECTTYPE) \
		IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE1) \
		IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE2) \
	IMCS_QI_METHOD_DEFINITION_END()
//..............................................................................

#define IMCS_QI_METHOD_DEFINITION4(OBJECTTYPE, PARENTTYPE1, PARENTTYPE2, PARENTTYPE3) \
	IMCS_QI_METHOD_DEFINITION_BEGIN(OBJECTTYPE) \
		IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE1) \
		IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE2) \
		IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE3) \
	IMCS_QI_METHOD_DEFINITION_END()
//..............................................................................

#define IMCS_QI_METHOD_DEFINITION5(OBJECTTYPE, PARENTTYPE1, PARENTTYPE2, PARENTTYPE3, PARENTTYPE4) \
	IMCS_QI_METHOD_DEFINITION_BEGIN(OBJECTTYPE) \
		IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE1) \
		IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE2) \
		IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE3) \
		IMCS_QI_METHOD_DEFINITION_PARENT(PARENTTYPE4) \
	IMCS_QI_METHOD_DEFINITION_END()

//..............................................................................

#define IMCS_STD_METHOD_DEFINITION(OBJECTTYPE, PARENTTYPE) \
	virtual const GUID& getClassID() const {return __uuidof(OBJECTTYPE);} \
	IMCS_QI_METHOD_DEFINITION(OBJECTTYPE, PARENTTYPE)

#define IMCS_STD_METHOD_DEFINITION3(OBJECTTYPE, PARENTTYPE1, PARENTTYPE2) \
	virtual const GUID& getClassID() const {return __uuidof(OBJECTTYPE);} \
	IMCS_QI_METHOD_DEFINITION3(OBJECTTYPE, PARENTTYPE1, PARENTTYPE2)

#define IMCS_ENT_METHOD_DEFINITION(OBJECTTYPE, PARENTTYPE, DBPARENTTYPE) \
	virtual const GUID&  getImplementID() {return __uuidof(DBPARENTTYPE);} \
	IMCS_STD_METHOD_DEFINITION(OBJECTTYPE, PARENTTYPE)

#define IMCS_ENT_METHOD_DEFINITION4(OBJECTTYPE, PARENTTYPE1, DBPARENTTYPE, PARENTTYPE2)\
	virtual const GUID&  getImplementID() {return __uuidof(DBPARENTTYPE);}\
	virtual const GUID& getClassID() const {return __uuidof(OBJECTTYPE);}\
	IMCS_QI_METHOD_DEFINITION3(OBJECTTYPE, PARENTTYPE1, PARENTTYPE2)

#define IMCS_ENT_METHOD_DEFINITION5(OBJECTTYPE, PARENTTYPE1, DBPARENTTYPE, PARENTTYPE2, PARENTTYPE3)\
	virtual const GUID&  getImplementID() {return __uuidof(DBPARENTTYPE);}\
	virtual const GUID& getClassID() const {return __uuidof(OBJECTTYPE);}\
	IMCS_QI_METHOD_DEFINITION4(OBJECTTYPE, PARENTTYPE1, PARENTTYPE2, PARENTTYPE3)

//==========================================================================
struct McKindOfData
{
	GUID    iid;
	INT_PTR offset;
	bool    bOfsValid; // is 'true' if field 'offset' has meaning

	MT_API McKindOfData();
	MT_API McKindOfData(const McKindOfData& cf);
	MT_API McKindOfData(REFIID riid, INT_PTR ofs);

		// Adds abstract GUID which doesn't refer to any physically existing interface
	MT_API McKindOfData(REFIID riid);

	MT_API bool operator == (const McKindOfData& cw) const;
	MT_API bool operator != (const McKindOfData& cw) const;
};

typedef McsArray<McKindOfData> McKindOfDataArr;

//==========================================================================

template <>
__inline UINT __stdcall McsHashKey(const McKindOfData& kind)
{
	UINT h1 = McsHashKey<const GUID&>(kind.iid);
	UINT h2 = McsHashKey<__int64>((__int64)kind.offset);
	__int64 i64 = MAKEI64(h1, h2);
	UINT h = McsHashKey<__int64>(i64);
	return h;
}

//==========================================================================

struct McKindOfDataOptArr
{
	int* mpIndices;
	int  mnKinds;
	bool mbGlobal; // лежит в глобальном мапе, нужно для защиты от изменения

	DECLARE_OBJ_NEWDEL;

	MT_API McKindOfDataOptArr();
	MT_API McKindOfDataOptArr(const McKindOfDataOptArr& cf);
	MT_API ~McKindOfDataOptArr();

	MT_API const McKindOfDataOptArr& operator = (const McKindOfDataOptArr& cf);

	MT_API void clear();

	MT_API bool find(int idxToFind, int& idxAt) const;
	MT_API bool find(const GUID& riid, int& idxAt) const;
	MT_API void add(int idx);
	MT_API void removeAt(int idxAt);

	MT_API static const McKindOfData& asKind(int index);
	MT_API static int asIndex(const McKindOfData& kind);
};

//==========================================================================

struct McKindOfDataOptArrPtr : std::shared_ptr<McKindOfDataOptArr>
{
public:
	MT_API McKindOfDataOptArrPtr(const std::shared_ptr<McKindOfDataOptArr>& pKindsData);
	MT_API McKindOfDataOptArrPtr();
	MT_API ~McKindOfDataOptArrPtr();

	MT_API bool operator == (const McKindOfDataOptArrPtr& other) const;

	//McKindOfDataOptArrPtr& operator = (std::shared_ptr<McKindOfDataOptArr> other) {
	//	*(std::shared_ptr<McKindOfDataOptArr>*)this = other;
	//	return *this;
	//}

	MT_API void addDataToGlobalKindsSet();
	MT_API McKindOfDataOptArrPtr getCopy(); // отдает копию со сброшенным флагом mbGlobal
	MT_API void copyOnModify();
};
//==========================================================================

#define IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF_EX(INTERFACE_NAME, bFinal) \
	INTERFACE_NAME() { \
		addKind2( McKindOfData( \
			__uuidof(INTERFACE_NAME), \
			((INT_PTR)(INTERFACE_NAME*)this) - ((INT_PTR)((IMcObject*)this)) ), \
			bFinal); \
	}

#define IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2_EX(INTERFACE_NAME, INTERFACE_IID2, bFinal) \
	INTERFACE_NAME() { \
		addKind2( McKindOfData( \
			__uuidof(INTERFACE_NAME), \
			((INT_PTR)(INTERFACE_NAME*)this) - ((INT_PTR)((IMcObject*)this)) ), \
			bFinal); \
		addKind_guidOnly2(INTERFACE_IID2, bFinal); \
	}

#define IMCS_REGISTER_CLASS_IID_4KINDOF_EX(INTERFACE_NAME, bFinal) \
	addKind2( McKindOfData( \
		__uuidof(INTERFACE_NAME), \
		((INT_PTR)(INTERFACE_NAME*)this) - ((INT_PTR)((IMcObject*)this)) ), \
		bFinal);

#define IMCS_REGISTER_THIS_IID_4KINDOF_EX(bFinal) \
	addKind2( McKindOfData( \
		__uuidof(*this), \
		((INT_PTR)this) - ((INT_PTR)((IMcObject*)this)) ), \
		bFinal);

#define IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(INTERFACE_NAME) \
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF_EX(INTERFACE_NAME, false)

#define IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2(INTERFACE_NAME, INTERFACE_IID2) \
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF2_EX(INTERFACE_NAME, INTERFACE_IID2, false)

#define IMCS_REGISTER_CLASS_IID_4KINDOF(INTERFACE_NAME) \
	IMCS_REGISTER_CLASS_IID_4KINDOF_EX(INTERFACE_NAME, false)

#define IMCS_REGISTER_THIS_IID_4KINDOF \
	IMCS_REGISTER_THIS_IID_4KINDOF_EX(false)

//==========================================================================

typedef HRESULT (*McsCreateClassObjectProc)(OUT IMcObject** ppvObject);

class CMcObjectsManager;
//==========================================================================
typedef McsMapEx<IMcObject*, IMcObject*, int, int> mcsMapMcObjToInt;

struct IMcObject : public IUnknown
{
public:
	DECLARE_OBJ_NEWDEL;	// force new/delete to work through MT.DLL

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	virtual const GUID& getClassID() const {
		return IID_IMcObject;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppvobj)
	{
		*ppvobj = NULL;
		if(riid == IID_IMcObject) {
			*ppvobj=(IMcObject*)this; AddRef();
			return S_OK;
		}
		if(riid == IID_IUnknown) {
			*ppvobj = (IUnknown*)this; AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	MT_API virtual ULONG STDMETHODCALLTYPE AddRef() override;
	MT_API virtual ULONG STDMETHODCALLTYPE Release() override;

protected:
	// Управление группировкой комплексов объектов, она позволяет управлять уничтожением
	// по Release сразу целого комплекса связанных объектов, ссылающихся друг на друга.

		// Синк-метод. В ответ нужно занулить без сброса ссылок все указатели между
		// этим объектом и другими объектами комплекса,
		// (!) Важно, чтобы указатели занулялись напрямую, без Release (!)
	virtual HRESULT _onResetGrpPtrs() { return E_NOTIMPL; }

		// Синк-метод. В ответ нужно добавить в переданный мап указатели на связанные
		// с этим объектом другие объекты комплекса сгруппированных объектов.
		// Добавлять так: ptrsSetToRefs[ptr]++;
		// Если установлен флаг bForUnbind, то не нужно выдавать объекты по связям для
		// вложенной группировки
	virtual HRESULT _onAppendGrpObjPtrs(IN OUT mcsMapMcObjToInt& ptrsSetToRefs, bool bForUnbind) { return E_NOTIMPL; }

public:

	// 29.04.2014, AGL
	// Поддержка Addref-Release для сгруппированных объектов.
	// Как это использовать.
	// Есть n объектов, которые указывают друг на друга таким образом, что образуют граф,
	// из каждого узла которого, можно по связям попать в любой другой его узел.
	// 1. Нужно проинициализировать все связи (указатели) в объектах.
	// 2. На каждом объекте реализовать методы _onAppendGrpObjPtrs и _onResetGrpPtrs.
	//    Первый позволит системе получить всю группу связанных объектов с кол-вом
	//    внутренних ссылок на каждый из объектов группы. Второй должен занулять все
	//    межгрупповые указатели без понижения ссылок (это нужно для уничтожения группы в памяти).
	// 3. Позвать на одном из объектов группы метод _groupPtrs. В случае успешной группировки
	//    на this-объекте будет проинициализирован счетчик ссылок на всю группу объектов целиком.
	//    Далее при получении любого объекта группы будет повышаться счетчик ссылок всей группы.
	//    При отпускании отдельного объекта будет понижаться счетчик на всей группе. Если групповой
	//    счетчик ссылок обнулится, то вся группа будет автоматически уничтожена
	// 4. Если объекты нужно перегруппировать, то позовите сначала метод _ungroupPtrs,
	//    объекты при этом продолжат существовать. Позвать разгруппировку надо ДО того, как будут
	//    удаленны межобъектные ссылки. После разгруппировки можно проинициализировать межобъектные связи
	//    по-новому и позвать _groupPtrs снова.

		// Метод группирует указанное мн-во объектов. this->объект множества становится
		// главным (в нём будет храниться кол-во ref-ссылок на всю группу целиком, но это принципиально
		// не важно, на каком объекте будет счетчик ссылок на группу, т.к. при его обнулении все объекты
		// группы будут уничтожены и пока существует один из них, существуют другие)
	MT_API virtual HRESULT _groupPtrs();

		// Метод разгруппировки объектов. Удаляется только информация о ссылках на группу,
		// связи между объектами сохраняются
	MT_API virtual HRESULT _ungroupPtrs();

		// Возвращает множество свзяанных в группе объектов, каждый указатель отображен на
		// количество ссылок, которое треюуется для его удержания в группе.
		// Если установлен флаг bForUnbind, то будут получены только объекты текущего уровня вложенности
		// группировки.
	MT_API virtual HRESULT _getGroupPtrs(OUT mcsMapMcObjToInt& ptrsSetToRefs, bool bForUnbind = false);

	MT_API virtual IMcObject* _getGroupPtr() const;
	MT_API virtual ULONG _getRefCount() const;
	MT_API virtual ULONG _getGrpRefCount() const;

public:
	virtual const mcsWorkID& ID() const {
		return WID_NULL;
	}

	MT_API virtual bool isKindOf(REFIID riid) const;
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

		// метод выдает абстрактный адрес начала объекта с указанным типом;
		// поскольку не известна структура выдаваемого объекта, то все дальнейшие
		// действия должны выполняться на вызывающей стороне;
		// пример использования - исключение лишних операций QueryInterface, если
		// сам известно, что этот тип для конкретного объекта можно получить простым 
		// приведением указателей
	MT_API virtual void* getSpecificKindPtr(REFIID riid);

	const void* getSpecificKindPtr(REFIID riid) const {
		return ((IMcObject*)this)->getSpecificKindPtr(riid);
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

protected:

	MT_API void addKind(const McKindOfData& kd);
	MT_API void addKind2(const McKindOfData& kd, bool bFinal);
	MT_API void removeKind(REFIID riid);

		// register only abstract GUID, not physically existing interface
	MT_API void addKind_guidOnly(REFIID riid);
	MT_API void addKind_guidOnly2(REFIID riid, bool bFinal);

public:
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	// AGL: every good objects implementation should have implementation for this method:
	// object must safely destroy all internal data and return in most methods 
	// code MCS_E_OBJECT_IS_INVALIDATED
	MT_API virtual void  invalidate();

	// метод позволяет определить, заваля ли для объекта метод invalidate(),
	// если результат есть true, объект "неживой",
	// (работать с таким объектом бессмысленно, просто удерживается кем-то через AddRef)
	MT_API bool isInvalidated();
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

		// (!) avoid usage of this method, SLOW!
	MT_API McKindOfDataArr kinds() const;
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

protected:
	// копирование через "=" разрешено в случае, когда наследник IMcObject не пользуется ссылками для удержания объекта
	MT_API IMcObject& operator = (const IMcObject& cf);

	// использование копирующего конструктора разрешено только если наследник IMcObject не пользуется ссылками для удержания объекта
	MT_API IMcObject(const IMcObject& cf);

protected:
	MT_API IMcObject();

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	virtual ~IMcObject() {
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

#ifdef _MCEYE
public:
#endif
	volatile ULONG m_iRefCount;

		// кол-во ссылок на группу объектов,
		// (!) не может быть меньше, чем m_iRefCount
	volatile ULONG m_iRefCountGrp;
		// без поднятой ссылки, т.к. объекты и так связаны внутренними указателями со ссылками
	IMcObject*     m_pGrp;

	friend CMcObjectsManager;
	friend struct IMcEntity;
	friend struct _McEntityBindData;

#ifdef _MCEYE
public:
#endif
	McKindOfDataOptArrPtr m_pKindOfDataOpt;
public:
		// system use
		// используется для блокировки различных циклических вызовов (writeEnabled, isKindOf, QueryInterface, ...)
	mutable DWORD m__dwLockMask;
};
//===========================================================================

struct IMcObjFactory :public IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcObjFactory);
	IMCS_STD_METHOD_DEFINITION(IMcObjFactory, IMcObject);
	virtual HRESULT create(IMcObject** ppvObject, const GUID& clsId, bool bSimple) = 0;
	virtual LPCTSTR name(){return NULL;}
	virtual int image(){return -1;}
	virtual LPCTSTR databaseName(){return NULL;}
	virtual LPCTSTR databasePrefix(){return NULL;}
};

//===========================================================================
typedef void (*AcadCmdFunctionPtr)();
//===========================================================================

struct IEntityMonitor; 
typedef struct IEntityMonitor IEM; // short form
typedef MObjPtr<IEM> IEMPtr;
typedef MObjPtr<IEntityMonitor> IEntityMonitorPtr;

struct IUniEntMonitorSink; 
typedef struct IUniEntMonitorSink IEM_Sink; // short form

struct EM_Entity;

//===========================================================================

typedef enum
{
	ctUndefined   = 0x0,
	ctMate        = 0x1,
	ctInsert      = 0x2,
	//ctAngle       =0x4,//теперь ctDirection
	ctParams      = 0x8,
	ctAxis        = 0x10,
	ctReflection  = 0x20,
	ctDirection   = 0x40,
	ctLinks       = 0x80
} ConstraintTypeEnum;
//===========================================================================

//Это было до 220 билда
typedef enum {_ctMate = 0, _ctInsert, _ctAngle, _ctParams, _ctAxis, _ctReflection, _ctDirection, _ctUndefined, _ctLinks} ConstraintTypeEnum_OLD;

_inline ConstraintTypeEnum correctOldCtrType(ConstraintTypeEnum_OLD iOld)
{
	switch(iOld)
	{
		case _ctMate: return ctMate;
		case _ctInsert: return ctInsert;
	//	case _ctAngle: return ctAngle;
		case _ctParams: return ctParams;
		case _ctAxis: return ctAxis;
		case _ctReflection: return ctReflection;
		case _ctDirection: return ctDirection;
		case _ctUndefined: return ctUndefined;
		case _ctLinks: return ctLinks;
		default:;
	}
	return ctUndefined;
}
//===========================================================================
#ifndef WIN64

	typedef unsigned long DWORD_PTR;
	typedef long LONG_PTR;

	// force use GWLP_xxxx for compatibility with WIN64
	#undef GWL_WNDPROC
	#undef GWL_HINSTANCE
	#undef GWL_HWNDPARENT
	#undef GWL_USERDATA
	
	#ifndef GWLP_WNDPROC
		#define GWLP_WNDPROC        (-4)
	#endif

	#ifndef GWLP_HINSTANCE
		#define GWLP_HINSTANCE      (-6)
	#endif

	#ifndef GWLP_HWNDPARENT
		#define GWLP_HWNDPARENT     (-8)
	#endif

	#ifndef GWLP_USERDATA
		#define GWLP_USERDATA       (-21)
	#endif

	// force use xxxP_xxxx for compatibility with WIN64
	#undef DWL_MSGRESULT
	#undef DWL_DLGPROC
	#undef DWL_USER
	#undef GCL_MENUNAME
	#undef GCL_HBRBACKGROUND
	#undef GCL_HCURSOR
	#undef GCL_HICON
	#undef GCL_HMODULE
	#undef GCL_WNDPROC
	#undef GCL_HICONSM

	#ifndef DWLP_MSGRESULT
		#define DWLP_MSGRESULT      0
	#endif
	#ifndef DWLP_DLGPROC
		#define DWLP_DLGPROC        (DWLP_MSGRESULT + sizeof(LRESULT))
	#endif
	#ifndef DWLP_USER
		#define DWLP_USER           (DWLP_DLGPROC + sizeof(DLGPROC))
	#endif

	#ifndef GCLP_MENUNAME
		#define GCLP_MENUNAME       (-8)
	#endif
	#ifndef GCLP_HBRBACKGROUND
		#define GCLP_HBRBACKGROUND  (-10)
	#endif
	#ifndef GCLP_HCURSOR
		#define GCLP_HCURSOR        (-12)
	#endif
	#ifndef GCLP_HICON
		#define GCLP_HICON          (-14)
	#endif
	#ifndef GCLP_HMODULE
		#define GCLP_HMODULE        (-16)
	#endif
	#ifndef GCLP_WNDPROC
		#define GCLP_WNDPROC        (-24)
	#endif
	#ifndef GCLP_HICONSM
		#define GCLP_HICONSM        (-34)
	#endif

#endif

#ifdef WIN64
	#define SX_32to64(a32) ( (((DWORD)(a32))&0x80000000) ? (__int64)(((DWORD)(a32))|0xFFFFFFFF00000000L) : (__int64)(a32) )
#else
	#define SX_32to64(a32) ( a32 )
#endif
