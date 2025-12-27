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

#ifdef _VERBOSEHEADERS_
	#pragma message("Use " __FILE__)
#endif

//==============================================================================

	// счетчики ошибок и предупреждений, которые срабатывают от макросов ниже
extern "C" MT_API int gnErrCount;
extern "C" MT_API int gnWarnCount;

	// сброс счетчиков ошибок и предупреждений
extern "C" MT_API void mtResetTestCounters();
extern "C" MT_API bool mtTestHasErrors();

//==============================================================================
__inline void _LogErrorW(HRESULT hres_in,LPCWSTR ErrMsg,LPCSTR Module,int line)
{
	gnErrCount++;

	McsStringW errmsg = ErrMsg;
	McsStringW strMessage;
	if(hres_in == 0xCCCCCCCC)
		strMessage.Format(L"ERROR '%s'", errmsg);
	else
		strMessage.Format(L"ERROR(%X) '%s'", hres_in, errmsg);

	__IdmMessageFmtW(
		strMessage, 
		DBMON_FONT_MAKE(DBMON_FONT_LUCIDACONSOLE,12),
		DBMON_COLOR_ERROR, 
		Module,
		line);
}
//---------------------------------------------------------------------------
__inline void _LogWarningW(HRESULT hres_in,LPCWSTR WarnMsg,LPCSTR Module,int line)
{
	gnWarnCount++;

	McsStringW warnmsg = WarnMsg;
	McsStringW strMessage;
	if(hres_in == 0xCCCCCCCC)
		strMessage.Format(L"WARNING '%s'",warnmsg);
	else
		strMessage.Format(L"WARNING(%X) '%s'", hres_in, warnmsg);
	
	__IdmMessageFmtW(
		strMessage,
		DBMON_FONT_MAKE(DBMON_FONT_LUCIDACONSOLE,12),
		DBMON_COLOR_WARN,
		Module,
		line);
}
//---------------------------------------------------------------------------
__inline void _LogErrorA(HRESULT hres_in,LPCSTR ErrMsg,LPCSTR Module,int line)
{
	gnErrCount++;

	McsStringA errmsg = ErrMsg;
	McsStringA strMessage;
	if(hres_in == 0xCCCCCCCC)
		strMessage.Format("ERROR '%s'", errmsg);
	else
		strMessage.Format("ERROR(%X) '%s'", hres_in, errmsg);

	__IdmMessageFmtA(
		strMessage, 
		DBMON_FONT_MAKE(DBMON_FONT_LUCIDACONSOLE,12),
		DBMON_COLOR_ERROR, 
		Module,
		line);
}
//---------------------------------------------------------------------------
__inline void _LogWarningA(HRESULT hres_in,LPCSTR WarnMsg,LPCSTR Module,int line)
{
	gnWarnCount++;

	McsStringA warnmsg = WarnMsg;
	McsStringA strMessage;
	if(hres_in == 0xCCCCCCCC)
		strMessage.Format("WARNING '%s'",warnmsg);
	else
		strMessage.Format("WARNING(%X) '%s'", hres_in, warnmsg);

	__IdmMessageFmtA(
		strMessage,
		DBMON_FONT_MAKE(DBMON_FONT_LUCIDACONSOLE,12),
		DBMON_COLOR_WARN,
		Module,
		line);
}
//==============================================================================

#ifdef _UNICODE
	#define _LogError _LogErrorW
	#define _LogWarning _LogWarningW
#else
	#define _LogError _LogErrorA
	#define _LogWarning _LogWarningA
#endif

#define IFBEGIN(cond) if(cond)do
	#define IFELSE while(0); else do
#define IFEND while(0);

#ifndef UNKNULL
	#define UNKNULL (IUnknown*)NULL
#endif

#define DEBUGDOUBLE (double)(__int64)(0xCDCDCDCDCDCDCDCDl)

//==============================================================================

#define ERR(What) {_LogError(0xCCCCCCCC, What, __FILE__, __LINE__);}
#define WARN(What) {_LogWarning(0xCCCCCCCC, What, __FILE__, __LINE__);}
#define ERRIF(cond, What) {if(cond) _LogError(0xCCCCCCCC, What, __FILE__, __LINE__);}
#define WARNIF(cond, What) {if(cond) _LogWarning(0xCCCCCCCC, What, __FILE__, __LINE__);}

#define LOGERR(hres) {if(FAILED(hres)) {_LogError(hres, _T("LOGERR marco"), __FILE__, __LINE__);}}
#define LOGWARN(hres) {if(FAILED(hres)) {_LogWarning(hres, _T("LOGWARN marco"), __FILE__, __LINE__);}}
#define LOGERRIF(expr, errcode) {if(expr) {_LogError(errcode, _T("LOGERRIF marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__);}}
#define LOGWARNIF(expr, errcode) {if(expr) {_LogWarning(errcode, _T("LOGWARNIF marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__);}}
#define LOGERR2(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogError(hres, _T("LOGERR2 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__);}}}
#define LOGWARN2(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogWarning(hres, _T("LOGWARN2 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__);}}}

// макросы позволяют проверить условие один раз, если выполняется, то бросают
// err/warn в лог; результат макросов есть результат выражения, поэтому
// макросы можно использовать в if(),
// (!) это удобно, если надо сделать точку останова на срабатывание условия

#define LOGERRIF_OPER(expr, errcode) ( (expr) ? (_LogError(errcode, _T("LOGERRIF_OPER marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__), true) : false )
#define LOGWARNIF_OPER(expr, errcode) ( (expr) ? (_LogWarning(errcode, _T("LOGWARNIF_OPER marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__), true) : false )

// то же, что и пара макросов выше, но работают только в DEBUG, в релизе результат
// всегда false, поэтому можно использовать их в качестве полноценной замены ассертам
#ifdef _DEBUG
	#define LOGERRIF_OPER_DBG(expr, errcode) ( (expr) ? (_LogError(errcode, _T("LOGERRIF_OPER_DBG marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__), true) : false )
#else
	#define LOGERRIF_OPER_DBG(expr, errcode) false
#endif

#ifdef _DEBUG
	#define LOGWARNIF_OPER_DBG(expr, errcode) ( (expr) ? (_LogWarning(errcode, _T("LOGWARNIF_OPER_DBG marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__), true) : false )
#else
	#define LOGWARNIF_OPER_DBG(expr, errcode) false
#endif

#define RETERR(hres)  {_LogError(hres, _T("RETERR marco"), __FILE__, __LINE__); return hres;}
#define RETWARN(hres)  {_LogWarning(hres, _T("RETWARN marco"), __FILE__, __LINE__); return hres;}
#define RETERRIF(expr, hres)  {if(expr) {_LogError(hres, _T("RETERRIF marco, expr: ") _T(#expr) _T(" "), __FILE__, __LINE__); return hres;}}
#define RETWARNIF(expr, hres)  {if(expr) {_LogWarning(hres, _T("RETWARNIF marco, expr: ") _T(#expr) _T(" "), __FILE__, __LINE__); return hres;}}
#define RETERRIF3(expr, hres, ret) {if(expr) {_LogError(hres, _T("RETERRIF3 marco, expr: ") _T(#expr) _T(" "), __FILE__, __LINE__); return ret;}}
#define RETWARNIF3(expr, hres, ret) {if(expr) {_LogWarning(hres, _T("RETWARNIF3 marco, expr: ") _T(#expr) _T(" "), __FILE__, __LINE__); return ret;}}
#define RETERRIF3VOID(expr, hres) {if(expr) {_LogError(hres, _T("RETERRIF3VOID marco, expr: ") _T(#expr) _T(" "), __FILE__, __LINE__); return;}}
#define RETWARNIF3VOID(expr, hres) {if(expr) {_LogWarning(hres, _T("RETWARNIF3VOID marco, expr: ") _T(#expr) _T(" "), __FILE__, __LINE__); return;}}

#define ERRRET(hres) {if(FAILED(hres)) {_LogError(hres, _T("ERRRET marco"), __FILE__, __LINE__); return hres;}}
#define WARNRET(hres) {if(FAILED(hres)) {_LogWarning(hres, _T("WARNRET marco"), __FILE__, __LINE__); return hres;}}
#define ERRRET2(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogError(hres, _T("ERRRET2 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); return hres;}}}
#define WARNRET2(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogWarning(hres, _T("WARNRET2 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); return hres;}}}
#define ERRRET3(hres, expr, ret) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogError(hres, _T("ERRRET3 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); return ret;}}}
#define WARNRET3(hres, expr, ret) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogWarning(hres, _T("WARNRET3 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); return ret;}}}
#define ERRRET3VOID(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogError(hres, _T("ERRRET3 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); return;}}}
#define WARNRET3VOID(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogWarning(hres, _T("WARNRET3VOID marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); return;}}}

#define ERRBREAK(hres) {if(FAILED(hres)) {_LogError(hres, _T("ERRBREAK marco"), __FILE__, __LINE__); break;}}
#define WARNBREAK(hres) {if(FAILED(hres)) {_LogWarning(hres, _T("WARNBREAK marco"), __FILE__, __LINE__); break;}}
#define BREAKERRIF(expr, hres)  {if(expr) {_LogError(hres, _T("BREAKERRIF marco, expr: ") _T(#expr) _T(" "), __FILE__, __LINE__); break;}}
#define BREAKWARNIF(expr, hres)  {if(expr) {_LogWarning(hres, _T("BREAKWARNIF marco, expr: ") _T(#expr) _T(" "), __FILE__, __LINE__); break;}}
#define ERRBREAK2(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogError(hres, _T("ERRBREAK2 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); break;}}}
#define WARNBREAK2(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogWarning(hres, _T("WARNBREAK2 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); break;}}}

#define ERRCONTINUE(hres) {if(FAILED(hres)) {_LogError(hres, _T("ERRCONTINUE marco"), __FILE__, __LINE__); continue;}}
#define WARNCONTINUE(hres) {if(FAILED(hres)) {_LogWarning(hres, _T("WARNCONTINUE marco"), __FILE__, __LINE__); continue;}}
#define CONTINUEERRIF(expr, hres)  {if(expr) {_LogError(hres, _T("CONTINUEERRIF marco, expr: ") _T(#expr) _T(" "), __FILE__, __LINE__); continue;}}
#define CONTINUEWARNIF(expr, hres)  {if(expr) {_LogWarning(hres, _T("CONTINUEWARNIF marco, expr: ") _T(#expr) _T(" "), __FILE__, __LINE__); continue;}}
#define ERRCONTINUE2(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogError(hres, _T("ERRCONTINUE2 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); continue;}}}
#define WARNCONTINUE2(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogWarning(hres, _T("WARNCONTINUE2 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); continue;}}}

#define THROWERR(hres) {_LogError(hres, _T("THROWERR marco"), __FILE__, __LINE__); throw hres;}
#define THROWWARN(hres) {_LogWarning(hres, _T("THROWWARN marco"), __FILE__, __LINE__); throw hres;}
#define THROWERRIF(expr, hres) {if(expr) {_LogError(hres, _T("THROWERRIF marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); throw hres;}}
#define THROWWARNIF(expr, hres) {if(expr) {_LogWarning(hres, _T("THROWWARNIF marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); throw hres;}}
#define ERRTHROW2(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogError(hres, _T("ERRTHROW2 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); throw hres;}}}
#define WARNTHROW2(hres, expr) {hres=(HRESULT)expr; {if(FAILED(hres)) {_LogWarning(hres, _T("WARNTHROW2 marco, expr:") _T(#expr) _T(" "), __FILE__, __LINE__); throw hres;}}}

#define ERRMSG_A(str) _LogErrorA(0xCCCCCCCC, str, __FILE__, __LINE__);
#define ERRMSG_W(str) _LogErrorW(0xCCCCCCCC, str, __FILE__, __LINE__);

//==============================================================================

#ifndef NOTIMPL_ALERT_V
	#define NOTIMPL_ALERT_V(str) MESSAGE_FMT_A("Method " str " is not implemented",DBMON_FONT_DEFAULT, RGB(80,0,0));
#endif

#ifndef NOTIMPL_ALERT
	#define NOTIMPL_ALERT(str) MESSAGE_FMT_A("Method " str " is not implemented",DBMON_FONT_DEFAULT, RGB(80,0,0)); return E_NOTIMPL;
#endif

#ifndef NOTIMPL_ALERT2
	#define NOTIMPL_ALERT2(str,ret) MESSAGE_FMT_A("Method " str " is not implemented",DBMON_FONT_DEFAULT, RGB(80,0,0)); return ret;
#endif

#define _QI(riid,VarFrom,VarTo) (VarFrom)->QueryInterface(riid,(void**)&(VarTo));

#define DECLRES \
HRESULT hres=S_OK; bool bres=true; BOOL Bres=TRUE;

#define FOREACH_IRX_START(item,set) \
{ \
	set->Reset(); \
	while(item=NULL, set->Next(1,&item,NULL), item) \
	{

#define FOREACH_IRX_NEXT }}

#define FOREACH_START_COM(item,set) \
{ \
	HRESULT hres; \
	long nElementsInCollection; \
	hres=(set)->get_Count(&nElementsInCollection); \
	for(long i=1; i<=nElementsInCollection; i++) \
	{ \
		item=NULL; \
		hres=(set)->get_Item(_variant_t(i),&item); if(FAILED(hres)) continue;

#define FOREACH_NEXT_COM \
	} \
}

#define GET_IRXENUM_COUNT(enumerator,count,interfacename) \
{ \
	CComPtr<interfacename> pUnk; \
	count=0; \
	enumerator->Reset(); \
	while(pUnk=NULL, enumerator->Next(1,&pUnk,NULL), pUnk) count++; \
}

#define ASSERT_THIS_PTR MCSASSERTE(IsInvalidPtr(this))

#define IsObjectSignaled(hobj) (WaitForSingleObject(hobj,0)==WAIT_OBJECT_0)

#define RECT_W(rect) ((rect).right-(rect).left)
#define RECT_H(rect) ((rect).bottom-(rect).top)
#define RECT_WM(rect) (((rect).right+(rect).left)/2)
#define RECT_HM(rect) (((rect).bottom+(rect).top)/2)

#define IsStylePresent(hwnd,style)  (bool)((GetWindowLongPtr(hwnd,GWL_STYLE)&style)!=0) 

#define IsExStylePresent(hwnd,exstyle)  (bool)((GetWindowLongPtr(hwnd,GWL_EXSTYLE)&exstyle)!=0) 
#define GEN_DWORD_ID(ID) {LARGE_INTEGER li; QueryPerformanceCounter(&li); ID=li.LowPart;}

#define BLK_BEGIN do
#define BLK_END   while(0);

extern HINSTANCE ghInstance;
__inline McsString STR_RES(UINT id) {
	McsString str;
	str.LoadString(ghInstance,id);
	return str;
}

#define MSGBOX_RES(id,flags) MessageBox(gpMcContext->GetMainWnd(), STR_RES(id), gpMcContext->ApplicationName(), flags)
#define MSGBOX_RES_APP(id,flags) MessageBox(gpMcContext->GetMainWnd(), STR_RES_APP(id), gpMcContext->ApplicationName(), flags)

#ifdef _DEBUG
	#define DBGTRAP {MESSAGE_FMT(_T("DEBUG TRAP"), DBMON_FONT_DEFAULT|DBMON_FONT_BOLD, RGB(190,0,0)); DebugBreak();}
#else
	#define DBGTRAP {MESSAGE_FMT(_T("DEBUG TRAP"), DBMON_FONT_DEFAULT|DBMON_FONT_BOLD, RGB(190,0,0));}
#endif

#ifdef _UNICODE
	#define ERRMSG ERRMSG_W
#else
	#define ERRMSG ERRMSG_A
#endif

#define BYTE1(expr) ((expr)&0xFF)
#define BYTE2(expr) (((expr)&0xFF00)>>8)
#define BYTE3(expr) (((expr)&0xFF0000)>>16)
#define BYTE4(expr) (((expr)&0xFF000000)>>24)

//==============================================================================

