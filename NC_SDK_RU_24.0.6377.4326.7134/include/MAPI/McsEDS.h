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

#define NO_MCSASSERT_IN_RELEASE

#ifdef _VERBOSEHEADERS_
  #pragma message("Use " __FILE__)
#endif

// force BP stack framing to improve ET stack tracing capabilities on exceptions
#pragma optimize("y", off)

#include <wtypes.h>
#include <tchar.h>
#include <malloc.h>

#include <stdio.h>
#include <string.h>
#pragma warning(push)
#pragma warning(disable:4091) // warning C4091: 'typedef ': ignored on left of '' when no variable is declared
#include <imagehlp.h>
#pragma warning(pop)
#pragma comment(lib,"IMAGEHLP.LIB")

#include "McAPIs.h"
#include "McsMem.h"

#pragma warning(disable:6011) // (Code analysis) Dereferencing NULL pointer
#pragma warning(disable:6255) // (Code analysis) _alloca indicates failure by raising a stack overflow exception. Consider using _malloca instead

#if _MSC_VER<=1200
	typedef DWORD ULONG_PTR;
#endif

#ifdef WIN64
	#define rAX(pCtx) (pCtx)->Rax
	#define rCX(pCtx) (pCtx)->Rcx
	#define rDX(pCtx) (pCtx)->Rdx
	#define rBX(pCtx) (pCtx)->Rbx
	#define rSP(pCtx) (pCtx)->Rsp
	#define rBP(pCtx) (pCtx)->Rbp
	#define rSI(pCtx) (pCtx)->Rsi
	#define rDI(pCtx) (pCtx)->Rdi
	#define rIP(pCtx) (pCtx)->Rip
#else
	#define rAX(pCtx) (pCtx)->Eax
	#define rCX(pCtx) (pCtx)->Ecx
	#define rDX(pCtx) (pCtx)->Edx
	#define rBX(pCtx) (pCtx)->Ebx
	#define rSP(pCtx) (pCtx)->Esp
	#define rBP(pCtx) (pCtx)->Ebp
	#define rSI(pCtx) (pCtx)->Esi
	#define rDI(pCtx) (pCtx)->Edi
	#define rIP(pCtx) (pCtx)->Eip
#endif

#define gstrMcsIniName _T("mt.ini")

///////////////////////////////////////////////////////////////////////////////
////////////////// DEFINITIONS WHICH ARE OFTEN NEEDED /////////////////////////
///////////////////////////////////////////////////////////////////////////////
//=============================================================================
__inline void mcsHlpDbgBreak() {
  DebugBreak();
}
//=============================================================================
__inline bool _eds_GetMcsAssertInRelease()
{
	MEMORY_BASIC_INFORMATION mbi;
	static int ls_fAIR=0;
	if(ls_fAIR<0) return false;
	if(ls_fAIR>0) return true;

	ls_fAIR=-1; // disabled by default
	if(!FindWindowW(L"_indebmon",NULL))
		return false; // no IDM so no reason to trace asserts
	// IDM present, try to get INI option
	if(!VirtualQuery(&ls_fAIR, &mbi, sizeof(mbi)))
		return false;
	const int szbc = 2048;
	TCHAR* thisModulePath = new TCHAR[szbc]; thisModulePath[0] = 0;
	if(!GetModuleFileName((HMODULE)mbi.AllocationBase, thisModulePath, szbc)) {
		delete[] thisModulePath;
		return false;
	}
	LPTSTR pLS = _tcsrchr(thisModulePath, _T('\\'));
	if(!pLS) {
		delete[] thisModulePath;
		return false;
	}
	lstrcpyn(pLS+1, gstrMcsIniName, (int)(szbc - (pLS+1-thisModulePath)));
	if(GetPrivateProfileInt(_T("mt"), _T("mcsassert"), 0, thisModulePath)) {
		delete[] thisModulePath;
		ls_fAIR=1;
		return true;
	}
	delete[] thisModulePath;
	return false;
}
static const bool _gf_Enable_MCSASSERT_InRelease = _eds_GetMcsAssertInRelease();
//=============================================================================
#ifdef _DEBUG
	#define MCSASSERT2(expr,once) \
	{ \
		if(!(expr)) { \
			static bool ls_f=false; \
			if(!(once) || !ls_f && (once)){ \
				ls_f = true; \
				char* msg = new char[2048]; \
				_snprintf_s(msg, 2048 / sizeof(*msg), _TRUNCATE, "McsAssertion failed;\r\nExpression: ' %s '\r\nFile: '%s; Line: %d;\nDebug?",#expr,__FILE__,__LINE__); \
				MESSAGE_ERR_A(msg); \
				if(::MessageBoxA(NULL,msg,"MCSASSERT",MB_ICONSTOP|MB_YESNO|MB_TASKMODAL|MB_TOPMOST)==IDYES) \
					mcsHlpDbgBreak(); \
				delete[] msg; \
			} \
		} \
	}
#else
	#ifdef NO_MCSASSERT_IN_RELEASE
		#define MCSASSERT2(expr,once) ((void)0);
	#else
		#define MCSASSERT2(expr,once) \
		if(_gf_Enable_MCSASSERT_InRelease) \
		{ \
			if(!(expr)) { \
				static bool ls_f=false; \
				if(!(once) || !ls_f && (once)){ \
					ls_f = true; \
					char* msg = new char[2048]; \
					_snprintf_s(msg, 2048 / sizeof(*msg), _TRUNCATE, "McsAssertion failed;\r\nExpression: ' %s '\r\nFile: '%s; Line: %d;\nDebug?",#expr,__FILE__,__LINE__); \
					MESSAGE_ERR_A(msg); \
					delete[] msg; \
				} \
			} \
		}
	#endif
#endif
//===========================================================================
#ifdef _DEBUG
	#define MCSASSERTE2(expr,once) \
	{ \
		if((expr)) { \
			static bool ls_f=false; \
			if(!(once) || !ls_f && (once)){ \
				ls_f = true; \
				char* msg = new char[2048]; \
				_snprintf_s(msg, 2048 / sizeof(*msg), _TRUNCATE, "McsAssertion failed;\r\nExpression: ' %s '\r\nFile: '%s; Line: %d;\nDebug?",#expr,__FILE__,__LINE__); \
				MESSAGE_ERR_A(msg); \
				if(::MessageBoxA(NULL,msg,"MCSASSERTE",MB_ICONSTOP|MB_YESNO|MB_TASKMODAL|MB_TOPMOST)==IDYES) \
					mcsHlpDbgBreak(); \
				delete[] msg; \
			} \
		} \
	}
#else
	#ifdef NO_MCSASSERT_IN_RELEASE
		#define MCSASSERTE2(expr,once) ((void)0);
	#else
		#define MCSASSERTE2(expr,once) \
		if(_gf_Enable_MCSASSERT_InRelease) \
		{ \
			if((expr)) { \
				static bool ls_f=false; \
				if(!(once) || !ls_f && (once)){ \
					ls_f = true; \
					char* msg = new char[2048]; \
					_snprintf_s(msg, 2048 / sizeof(*msg), _TRUNCATE, "McsAssertion failed;\r\nExpression: ' %s '\r\nFile: '%s; Line: %d;\nDebug?",#expr,__FILE__,__LINE__); \
					MESSAGE_ERR_A(msg); \
					delete[] msg; \
				} \
			} \
		}
	#endif
#endif
                                    
//===========================================================================
#define MCSASSERT2_EX(expr,actionExpression,once) {MCSASSERT2(expr,once); if(!(expr)) {actionExpression;}}
#define MCSASSERTE2_EX(expr,actionExpression,once) {MCSASSERTE2(expr,once); if(expr) {actionExpression;}}
//===========================================================================
#define MCSASSERT(expr) MCSASSERT2((expr),false)
#define MCSASSERTE(expr) MCSASSERTE2((expr),false)
#define MCSASSERT_EX(expr,actionExpression) MCSASSERT2_EX((expr),actionExpression,false)
#define MCSASSERTE_EX(expr,actionExpression) MCSASSERTE2_EX((expr),actionExpression,false)

// set of macros "x64" compiled only in WIN64, in WIN32 they replaced by "void"

#ifdef WIN64
	#define MCSASSERTx64(expr) MCSASSERT2((expr),false)
	#define MCSASSERTEx64(expr) MCSASSERTE2((expr),false)
	#define MCSASSERTx64_EX(expr,actionExpression) MCSASSERT2_EX((expr),actionExpression,false)
	#define MCSASSERTEx64_EX(expr,actionExpression) MCSASSERTE2_EX((expr),actionExpression,false)

	#define MCSASSERTx64_32bit(val) MCSASSERT2((val)<0x100000000L,false)
	#define MCSASSERTx64_EX_32bit(val, actionExpression) MCSASSERT2_EX((val)<0x100000000L,actionExpression,false)
#else
	#define MCSASSERTx64(expr) ((void)0)
	#define MCSASSERTEx64(expr) ((void)0)
	#define MCSASSERTx64_EX(expr,actionExpression) ((void)0)
	#define MCSASSERTEx64_EX(expr,actionExpression) ((void)0)

	#define MCSASSERTx64_32bit(val) ((void)0)
	#define MCSASSERTx64_EX_32bit(val, actionExpression) ((void)0)
#endif

#define MCSASSERT_ONCE(expr) MCSASSERT2((expr),true)
#define MCSASSERTE_ONCE(expr) MCSASSERTE2((expr),true)
#define MCSASSERT_ONCE_EX(expr,actionExpression) MCSASSERT2_EX((expr),actionExpression,true)
#define MCSASSERTE_ONCE_EX(expr,actionExpression) MCSASSERTE2_EX((expr),actionExpression,true)
//===========================================================================

#ifdef _DEBUG

	#define IsValidPtr(ptr) (!IsBadReadPtr((const void*)(ptr),1))
	#define IsInvalidPtr(ptr) (IsBadReadPtr((const void*)(ptr),1))
	#define IsValidRange(ptr,size) (!IsBadReadPtr((const void*)(ptr), size))
	#define IsInvalidRange(ptr,size) (IsBadReadPtr((const void*)(ptr), size))

#else

	#define IsValidPtr(ptr) ((ptr) != NULL)
	#define IsInvalidPtr(ptr) ((ptr) == NULL)
	#define IsValidRange(ptr, size) ((ptr) != NULL)
	#define IsInvalidRange(ptr, size) ((ptr) == NULL)

#endif
//===========================================================================
#define CHECK_OUT_OF_MEM(condition) {if(condition) {MESSAGE_ERR_A("E_CHECK_OUT_OF_MEMORY"); throw E_OUTOFMEMORY;} }
//===========================================================================





//////////////////////////////////////////////////////////////////////////////
///////////////////// OFF-PROCESS DEBUG MESSAGES SUPPORT /////////////////////
//////////////////////////////////////////////////////////////////////////////
//===========================================================================
// some definitions that allow to change face of message
#define DBMON_COLOR_ERROR        RGB(190,0,0)
#define DBMON_COLOR_WARN         RGB(190,100,0)

#define DBMON_MSG_SEPARATOR_A       "_IDB_SEPARATOR" // this message is displayed by IDM as horizontal delimiter
#define _DBMON_MSG_PROC_SEPARATOR_A "_IDB_PROC_SEPARATOR" // InDebMon internal: automatically added when client process exits/terminates
#define DBMON_MSG_SEPARATOR_W       L"_IDB_SEPARATOR" // this message is displayed by IDM as horizontal delimiter
#define _DBMON_MSG_PROC_SEPARATOR_W L"_IDB_PROC_SEPARATOR" // InDebMon internal: automatically added when client process exits/terminates

#define DBMON_FONT_ARIAL         0x00010000
#define DBMON_FONT_TIMESNR       0x00020000
#define DBMON_FONT_COURIER       0x00030000
#define DBMON_FONT_MSSERIF       0x00040000
#define DBMON_FONT_LUCIDACONSOLE 0x00080000
#define DBMON_FONT_NORMAL        0x00000000
#define DBMON_FONT_BOLD          0x00000001
#define DBMON_FONT_ITALIC        0x00000002
#define DBMON_FONT_MAKE(style,size) (style&0x00FFFFFF)|(((size)&0xFF)<<24)
#define DBMON_FONT_DEFAULT       0x08040000 // default font - "MS Sans Serif" size:8 pt

#define DBMON_SPF_V2             0x00000100	// version 2, supports version of compiler in InvMsg struct

#define DBMON_32OLD_CP_STRING    0x80000000
//===========================================================================
// ALL pointers declared via unsigned int32 types because this structure used in x64 compilations
// and must represent pointers as valid in x32 notation
struct _IdmMsgW32
{
	DWORD    m_dwClientProcessId; // calling process id
	DWORD    m_dwClientThreadId;  // calling thread id
	DWORD    m_dwMsgLen;          // length of input message in characters
	DWORD    m_wcsMsg;            // (LPCWSTR) client process pointer to the message
	DWORD    m_dwFileNameLen;     // length of calling module file name, in characters
	DWORD    m_csFileName;        // (LPCSTR) client process pointer to the calling module file name
	DWORD    m_dwLineNum;         // calling module line number
	DWORD    m_dwFontFormat;      // type of font, it's size and other format flags
	COLORREF m_dwColor;           // color of the font

	DWORD    m_csClientExeName;   // (LPCWSTR) client's main executable module name
	DWORD    m_dwExeNameLen;      // length in symbols of string pointed by m_csClientExeName
};
//...........................................................................
//v2+
struct _IdmMsg2W32 : public _IdmMsgW32
{
	DWORD    m_mscVer;            // version of compiler on the sender side
};
//===========================================================================
// x64
// ALL pointers declared via unsigned int64 types because this structure used in x64 compilations
// and must represent pointers as valid in x64 notation
struct _IdmMsgW64
{
	DWORD    m_dwClientProcessId; // calling process id
	DWORD    m_dwClientThreadId;  // calling thread id
	DWORD    m_dwMsgLen;          // length of input message in characters
	__int64  m_wcsMsg;            // (LPCWSTR) client process pointer to the message
	DWORD    m_dwFileNameLen;     // length of calling module file name, in characters
	__int64  m_csFileName;        // (LPCSTR) client process pointer to the calling module file name
	DWORD    m_dwLineNum;         // calling module line number
	DWORD    m_dwFontFormat;      // type of font, it's size and other format flags
	COLORREF m_dwColor;           // color of the font
	DWORD    m_mscVer;            // version of compiler on the sender side
	__int64  m_csClientExeName;   // (LPCWSTR) client's main executable module name
	DWORD    m_dwExeNameLen;      // length in symbols of string pointed by m_csClientExeName
};
//===========================================================================
#define IDM_SENDMESSAGE_A_X32  0x5000 // DEPRECATED and not supported since 12.02.2007
#define IDM_SENDMESSAGE_W_X32  0x5001 // Unicode version x32: S, W: _IdmMsg2W32*, L:DWORD dwClientProcessID, R: BOOL fOk
#define IDM_SENDMESSAGE_W_X64  0x5002 // Unicode version x64: S, W: _IdmMsgW64*, L:DWORD dwClientProcessID, R: BOOL fOk
#define IDM_POPQMSG            0x5100 // P; !!! InDebMon posts this to itself, do not post from client process
//===========================================================================
// Wrapper template class for sending messages to InDebMon
// Code for methods will be generated by compiler in-place for each type of 
// source object
// Object must have redefined 'operator LPCSTR()'

template <class T>
class IdmGate
{
private:
	DWORD  m_dwThisProcessID;
	WCHAR  m_sFullExeName[256];
	LPWSTR m_sExeName;
	DWORD  m_dwExeNameLen;
public:
	HWND   m_hWndMonitorWindow;
	//........................
private:
	static void __stdcall _init(IdmGate* pIDMG)
	{
		// perform connection
		pIDMG->m_hWndMonitorWindow = ::FindWindowW(L"_indebmon",NULL);
		pIDMG->m_dwThisProcessID = ::GetCurrentProcessId();
		pIDMG->m_sFullExeName[0]=0;
		pIDMG->m_sExeName = NULL;
		GetModuleFileNameW(NULL, pIDMG->m_sFullExeName, STRBUFSIZE(pIDMG->m_sFullExeName));
		pIDMG->m_sExeName = wcsrchr(pIDMG->m_sFullExeName,L'\\')+1;
		pIDMG->m_dwExeNameLen=lstrlenW(pIDMG->m_sExeName);
	}
	//..........................................................
public:  
	IdmGate()
	{
		_init(this);
	}
	//..........................................................
	static bool __stdcall _internalMessageA
		(IdmGate* pIDMG,
		 LPCSTR   strMessage,
		 LPCSTR   FileName,
		 int      Line,
		 DWORD    format, 
		 COLORREF color)
	{
		LPWSTR wstrMessage = NULL;
		int n = MultiByteToWideChar(0, 0, strMessage, -1, wstrMessage, 0);
		if(n<=0) return false;
		wstrMessage = (LPWSTR)_alloca(sizeof(WCHAR)*n);
		int ires = MultiByteToWideChar(0, 0, strMessage, -1, wstrMessage, n);
		if(ires<=0) return false;
		return _internalMessageW(pIDMG, wstrMessage, FileName, Line, format, color);
	}
	//..........................................................
	static bool __stdcall _internalMessageW
		(IdmGate* pIDMG,
		 LPCWSTR  wstrMessage,
		 LPCSTR   FileName,
		 int      Line,
		 DWORD    format, 
		 COLORREF color)
	{
		if(pIDMG->m_hWndMonitorWindow==NULL)  
			return false; // messages monitor not connected

		// check monitor window is valid
		if(IsWindow(pIDMG->m_hWndMonitorWindow)==FALSE)
		{
			// try to reconnect
			pIDMG->m_hWndMonitorWindow=::FindWindowA("_indebmon",NULL);
			if(pIDMG->m_hWndMonitorWindow==NULL)
				return false;
		}

#ifdef WIN64
		_IdmMsgW64 msg;
#else
		_IdmMsg2W32 msg;
#endif
		msg.m_dwClientProcessId = pIDMG->m_dwThisProcessID;
		msg.m_dwClientThreadId = GetCurrentThreadId();
		msg.m_dwMsgLen = lstrlenW(wstrMessage);
		msg.m_wcsMsg = (UINT_PTR)wstrMessage;
#ifdef WIN64
		LPCSTR csFileName = FileName;
#else
		LPCSTR csFileName = LPCSTR(DWORD(FileName)&(~DBMON_32OLD_CP_STRING));
#endif
		if(IsValidPtr(csFileName))
		{
			msg.m_dwFileNameLen = lstrlenA(csFileName);
			msg.m_csFileName = (UINT_PTR)FileName;
			msg.m_dwLineNum = Line;
		} 
		else
		{
			msg.m_dwFileNameLen = 0;
			msg.m_csFileName = NULL;
			msg.m_dwLineNum = 0;
		}
		msg.m_dwFontFormat = format|DBMON_SPF_V2;
		msg.m_dwColor = color&0xFFFFFF;

		msg.m_csClientExeName = (UINT_PTR)pIDMG->m_sExeName;
		msg.m_dwExeNameLen = pIDMG->m_dwExeNameLen;
		
		msg.m_mscVer = _MSC_VER;

#ifdef WIN64
		::SendMessage(pIDMG->m_hWndMonitorWindow, IDM_SENDMESSAGE_W_X64, (WPARAM)&msg, msg.m_dwClientProcessId);
#else
		::SendMessage(pIDMG->m_hWndMonitorWindow, IDM_SENDMESSAGE_W_X32, (WPARAM)&msg, msg.m_dwClientProcessId);
#endif
		return true;
	}
	//..........................................................
	bool messageA
		(LPCSTR   strMessage,
		 LPCSTR   FileName=NULL,
		 int      Line=0,
		 DWORD    format=DBMON_FONT_DEFAULT, 
		 COLORREF color=RGB(0,0,0))
	{
		return _internalMessageA(this, strMessage, FileName, Line, format, color);
	}
	//..........................................................
	bool messageW
		(LPCWSTR  wstrMessage,
		 LPCSTR   FileName=NULL,
		 int      Line=0,
		 DWORD    format=DBMON_FONT_DEFAULT, 
		 COLORREF color=RGB(0,0,0))
	{
		return _internalMessageW(this, wstrMessage, FileName, Line, format, color);
	}
};
//===========================================================================
// inline template wrapper to static message sender, for each type of source object
template <class T> 
__inline bool __IdmMessageFmtA
(T        strMessage,
 DWORD    Format,
 COLORREF Color,
 LPCSTR   FileName,
 int      Line)
{
	static IdmGate<T> s_IG;
	if(NULL == s_IG.m_hWndMonitorWindow)
		return false; // speed up messages transfer
	return 
		s_IG.messageA(strMessage,FileName,Line,Format,Color);
}
//===========================================================================
// inline template wrapper to static message sender, for each type of source object
template <class T> 
__inline bool __IdmMessageA
(T        strMessage,
 LPCSTR   FileName,
 int      Line)
{
	static IdmGate<T> s_IG;
	if(NULL == s_IG.m_hWndMonitorWindow)
		return false; // speed up messages transfer
	return 
		s_IG.messageA(strMessage,FileName,Line);
}
//===========================================================================
// macroses for sending messages to InDebMon process
#define MESSAGE_NOCP_A(msg) \
	__IdmMessageA(msg,NULL,0);

#define MESSAGE_A(msg) \
	__IdmMessageA(msg,__FILE__,__LINE__);

#define MESSAGEIF_A(expr,msg) \
	if(expr) \
		__IdmMessageA(msg,__FILE__,__LINE__);

#define MESSAGE_FMT_NOCP_A(msg,dwFormat,color) \
		__IdmMessageFmtA(msg,dwFormat,color,NULL,0);

#define MESSAGE_FMT_A(msg,dwFormat,color) \
		__IdmMessageFmtA(msg,dwFormat,color,__FILE__,__LINE__);

#define MESSAGEIF_FMT_A(expr,msg,dwFormat,color) \
	if(expr) \
		__IdmMessageFmtA(msg,dwFormat,color,__FILE__,__LINE__);

// helper forms
#define MESSAGE_ERR_A(msg) MESSAGE_FMT_A((msg),DBMON_FONT_DEFAULT,DBMON_COLOR_ERROR)
#define MESSAGE_WARN_A(msg) MESSAGE_FMT_A((msg),DBMON_FONT_DEFAULT,DBMON_COLOR_WARN)
#define MESSAGE_ERR_NOCP_A(msg) MESSAGE_FMT_NOCP_A((msg),DBMON_FONT_DEFAULT,DBMON_COLOR_ERROR)
#define MESSAGE_WARN_NOCP_A(msg) MESSAGE_FMT_NOCP_A((msg),DBMON_FONT_DEFAULT,DBMON_COLOR_WARN)
//===========================================================================
// inline template wrapper to static message sender, for each type of source object
template <class T> 
__inline bool __IdmMessageFmtW
(T        wstrMessage,
 DWORD    Format,
 COLORREF Color,
 LPCSTR   FileName,
 int      Line)
{
	static IdmGate<T> s_IG;
	if(NULL == s_IG.m_hWndMonitorWindow)
		return false; // speed up messages transfer
	return 
		s_IG.messageW(wstrMessage,FileName,Line,Format,Color);
}
//===========================================================================
// inline template wrapper to static message sender, for each type of source object
template <class T> 
__inline bool __IdmMessageW
(T        wstrMessage,
 LPCSTR   FileName,
 int      Line)
{
	static IdmGate<T> s_IG;
	if(NULL == s_IG.m_hWndMonitorWindow)
		return false; // speed up messages transfer
	return 
		s_IG.messageW(wstrMessage,FileName,Line);
}
//===========================================================================
// macroses for sending messages to InDebMon process
#define MESSAGE_NOCP_W(msg) \
	__IdmMessageW(msg,NULL,0);

#define MESSAGE_W(msg) \
	__IdmMessageW(msg,__FILE__,__LINE__);

#define MESSAGEIF_W(expr,msg) \
	if(expr) \
		__IdmMessageW(msg,__FILE__,__LINE__);

#define MESSAGE_FMT_NOCP_W(msg,dwFormat,color) \
	__IdmMessageFmtW(msg,dwFormat,color,NULL,0);

#define MESSAGE_FMT_W(msg,dwFormat,color) \
	__IdmMessageFmtW(msg,dwFormat,color,__FILE__,__LINE__);

#define MESSAGEIF_FMT_W(expr,msg,dwFormat,color) \
	if(expr) \
		__IdmMessageFmtW(msg,dwFormat,color,__FILE__,__LINE__);

// helper forms
#define MESSAGE_ERR_W(msg) MESSAGE_FMT_W((msg),DBMON_FONT_DEFAULT,DBMON_COLOR_ERROR)
#define MESSAGE_WARN_W(msg) MESSAGE_FMT_W((msg),DBMON_FONT_DEFAULT,DBMON_COLOR_WARN)
#define MESSAGE_ERR_NOCP_W(msg) MESSAGE_FMT_NOCP_W((msg),DBMON_FONT_DEFAULT,DBMON_COLOR_ERROR)
#define MESSAGE_WARN_NOCP_W(msg) MESSAGE_FMT_NOCP_W((msg),DBMON_FONT_DEFAULT,DBMON_COLOR_WARN)
//===========================================================================
#ifdef _UNICODE
	#define MESSAGE_NOCP              MESSAGE_NOCP_W      
	#define MESSAGE                   MESSAGE_W           
	#define MESSAGEIF                 MESSAGEIF_W         
	#define MESSAGE_FMT_NOCP          MESSAGE_FMT_NOCP_W  
	#define MESSAGE_FMT               MESSAGE_FMT_W       
	#define MESSAGEIF_FMT             MESSAGEIF_FMT_W     
	#define MESSAGE_ERR               MESSAGE_ERR_W       
	#define MESSAGE_WARN              MESSAGE_WARN_W      
	#define MESSAGE_ERR_NOCP          MESSAGE_ERR_NOCP_W  
	#define MESSAGE_WARN_NOCP         MESSAGE_WARN_NOCP_W 
	#define DBMON_MSG_SEPARATOR       DBMON_MSG_SEPARATOR_W
	#define _DBMON_MSG_PROC_SEPARATOR _DBMON_MSG_PROC_SEPARATOR_W
	#define __IdmMessage              __IdmMessageW
	#define __IdmMessageFmt           __IdmMessageFmtW
#else
	#define MESSAGE_NOCP              MESSAGE_NOCP_A
	#define MESSAGE                   MESSAGE_A           
	#define MESSAGEIF                 MESSAGEIF_A         
	#define MESSAGE_FMT_NOCP          MESSAGE_FMT_NOCP_A
	#define MESSAGE_FMT               MESSAGE_FMT_A
	#define MESSAGEIF_FMT             MESSAGEIF_FMT_A
	#define MESSAGE_ERR               MESSAGE_ERR_A
	#define MESSAGE_WARN              MESSAGE_WARN_A
	#define MESSAGE_ERR_NOCP          MESSAGE_ERR_NOCP_A
	#define MESSAGE_WARN_NOCP         MESSAGE_WARN_NOCP_A
	#define DBMON_MSG_SEPARATOR       DBMON_MSG_SEPARATOR_A
	#define _DBMON_MSG_PROC_SEPARATOR _DBMON_MSG_PROC_SEPARATOR_A
	#define __IdmMessage              __IdmMessageA
	#define __IdmMessageFmt           __IdmMessageFmtA
#endif
//===========================================================================

#define IDM McsString().Format
//===========================================================================

//---YAL: keep it 
#if !defined(_NCAD_BUILD_) && !defined(_MCS_CORE_ONLY)
	#include "McsEDSInternal.h"
#endif

//===========================================================================
