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
#include "nrxdbgate_impexp.h"

struct REGISTER_NRXOBJ_ENTRY
{
	NcRxClass* (*desc) ();
	void (*rxInit) ();
	bool bRegistered;
};

#pragma section("NRXOBJ$__a", read, shared)
#pragma section("NRXOBJ$__z", read, shared)
#pragma section("NRXOBJ$__m", read, shared)

extern "C"
{
	__declspec(selectany) __declspec(allocate("NRXOBJ$__a")) REGISTER_NRXOBJ_ENTRY* __pNrxObjMapEntryFirst =NULL;
	__declspec(selectany) __declspec(allocate("NRXOBJ$__z")) REGISTER_NRXOBJ_ENTRY* __pNrxObjMapEntryLast  =NULL;
}

#ifdef _WIN64
	#define REGISTER_NRXOBJ_ENTRY_PRAGMA(classname) __pragma(comment(linker, "/include:__pNrxObjMap_" #classname));
#else
	#define REGISTER_NRXOBJ_ENTRY_PRAGMA(classname) __pragma(comment(linker, "/include:___pNrxObjMap_" #classname));
#endif

#define REGISTER_NRXOBJ_ENTRY_AUTO(classname) \
	__declspec(selectany) REGISTER_NRXOBJ_ENTRY __NrxObjMap_##classname = { classname::desc, classname::rxInit }; \
	extern "C" __declspec(allocate("NRXOBJ$__m")) __declspec(selectany) REGISTER_NRXOBJ_ENTRY* const __pNrxObjMap_##classname = &__NrxObjMap_##classname; \
	REGISTER_NRXOBJ_ENTRY_PRAGMA(classname)

#define DISPATCH_PKTMSG(pktmsg) case NcRx::pktmsg: return (On_ ##pktmsg (pkt))

extern HINSTANCE _hdllInstance;

class NrxDbApp
{
protected:
	HINSTANCE m_hdllInstance;
	bool m_bUnlocked;
	bool m_bMDIAware;

public:
	NrxDbApp () : m_hdllInstance(NULL), m_bUnlocked(true), m_bMDIAware(true) 
	{}

	virtual NcRx::AppRetCode On_kInitAppMsg (void *pkt)
	{
		m_hdllInstance =_hdllInstance;
		RegisterServerComponents ();
		int nNrxObjCount =0;
		REGISTER_NRXOBJ_ENTRY **ppNrxObjMapEntryFirst =&__pNrxObjMapEntryFirst + 1;
		REGISTER_NRXOBJ_ENTRY **ppNrxObjMapEntryLast =&__pNrxObjMapEntryLast;
		for (REGISTER_NRXOBJ_ENTRY **ppEntry =ppNrxObjMapEntryFirst; ppEntry < ppNrxObjMapEntryLast; ppEntry++)
		{
			if (*ppEntry != NULL)
			{
				nNrxObjCount++;
				(*ppEntry)->rxInit ();
				(*ppEntry)->bRegistered =true;
			}
		}

		if (nNrxObjCount > 0)
			ncrxBuildClassHierarchy();

		return (NcRx::kRetOK);
	}
	virtual NcRx::AppRetCode On_kUnloadAppMsg (void *pkt)
	{
		REGISTER_NRXOBJ_ENTRY **ppNrxObjMapEntryFirst =&__pNrxObjMapEntryFirst + 1;
		REGISTER_NRXOBJ_ENTRY **ppNrxObjMapEntryLast =&__pNrxObjMapEntryLast;
		for (REGISTER_NRXOBJ_ENTRY **ppEntry =ppNrxObjMapEntryFirst; ppEntry < ppNrxObjMapEntryLast; ppEntry++)
		{
			if (*ppEntry != NULL && (*ppEntry)->bRegistered == true)
				DeleteClassAndDescendant (ppEntry);
		}
		return (NcRx::kRetOK);
	}
	virtual NcRx::AppRetCode On_kLoadDwgMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kUnloadDwgMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kInvkSubrMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kCfgMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kEndMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kQuitMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kSaveMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kDependencyMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kNoDependencyMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kOleUnloadAppMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kPreQuitMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kInitDialogMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kEndDialogMsg (void *pkt) { return (NcRx::kRetOK); }
	virtual NcRx::AppRetCode On_kNullMsg (void *pkt) { return (NcRx::kRetOK); }

	NcRx::AppRetCode ncrxEntryPoint (NcRx::AppMsgCode msg, void *pkt)
	{
		switch ( msg )
		{
			DISPATCH_PKTMSG (kInitAppMsg);
			DISPATCH_PKTMSG (kUnloadAppMsg);
			DISPATCH_PKTMSG (kLoadDwgMsg);
			DISPATCH_PKTMSG (kUnloadDwgMsg);
			DISPATCH_PKTMSG (kInvkSubrMsg);
			DISPATCH_PKTMSG (kCfgMsg);
			DISPATCH_PKTMSG (kEndMsg);
			DISPATCH_PKTMSG (kQuitMsg);
			DISPATCH_PKTMSG (kSaveMsg);
			DISPATCH_PKTMSG (kDependencyMsg);
			DISPATCH_PKTMSG (kNoDependencyMsg);
			DISPATCH_PKTMSG (kOleUnloadAppMsg);
			DISPATCH_PKTMSG (kPreQuitMsg);
			DISPATCH_PKTMSG (kInitDialogMsg);
			DISPATCH_PKTMSG (kEndDialogMsg);
			DISPATCH_PKTMSG (kNullMsg);
		}
		return (NcRx::kRetOK);
	}

	virtual void RegisterServerComponents () = 0;
	HINSTANCE &GetModuleInstance () { return (m_hdllInstance); }

private:
	void DeleteClassAndDescendant (REGISTER_NRXOBJ_ENTRY **ppEntry)
	{
		REGISTER_NRXOBJ_ENTRY **ppNrxObjMapEntryFirst =&__pNrxObjMapEntryFirst + 1;
		REGISTER_NRXOBJ_ENTRY **ppNrxObjMapEntryLast =&__pNrxObjMapEntryLast;
		for (REGISTER_NRXOBJ_ENTRY **ppEntry2 =ppNrxObjMapEntryFirst; ppEntry2 < ppNrxObjMapEntryLast; ppEntry2++)
		{
			if (*ppEntry2 != NULL && *ppEntry2 != *ppEntry && (*ppEntry2)->bRegistered == true)
			{
				if ((*ppEntry2)->desc ()->myParent () == (*ppEntry)->desc ())
					DeleteClassAndDescendant (ppEntry2);
			}
		}
		deleteNcRxClass ((*ppEntry)->desc ());
		(*ppEntry)->bRegistered =false;
	}
};

NrxDbApp *ncrxGetApp ();

#define IMPLEMENT_NRX_ENTRYPOINT_STD(classname) \
	HINSTANCE _hdllInstance =NULL; \
	class classname entryPointObject; \
	NrxDbApp *ncrxGetApp () { return (&entryPointObject); } \
	extern "C" NcRx::AppRetCode __declspec(dllexport) ncrxEntryPoint (NcRx::AppMsgCode msg, void *pkt) { \
		return (entryPointObject.ncrxEntryPoint (msg, pkt)); \
	}

#define IMPLEMENT_NRX_ENTRYPOINT_CLR(classname) IMPLEMENT_NRX_ENTRYPOINT_STD(classname)
#define IMPLEMENT_NRX_ENTRYPOINT(classname) IMPLEMENT_NRX_ENTRYPOINT_STD(classname)

struct _NDSSYMBOL_ENTRY
{
	const NCHAR *pszName;
	int (*fptr) ();
	bool bRegFunc;
	UINT nameID;
};

#pragma section("NDSSYMBOL$__a", read, shared)
#pragma section("NDSSYMBOL$__z", read, shared)
#pragma section("NDSSYMBOL$__m", read, shared)

extern "C"
{
	__declspec(selectany) __declspec(allocate("NDSSYMBOL$__a")) _NDSSYMBOL_ENTRY* __pNdsSymbolMapEntryFirst =NULL ;
	__declspec(selectany) __declspec(allocate("NDSSYMBOL$__z")) _NDSSYMBOL_ENTRY* __pNdsSymbolMapEntryLast =NULL ;
}

#ifdef _WIN64
	#define NDSSYMBOL_ENTRY_PRAGMA(name) __pragma(comment(linker, "/include:__pNdsSymbolMap_" #name)) ;
#else
	#define NDSSYMBOL_ENTRY_PRAGMA(name) __pragma(comment(linker, "/include:___pNdsSymbolMap_" #name)) ;
#endif

#define NDSSYMBOL_ENTRY_AUTO(classname, name, regFunc) \
	__declspec(selectany) _NDSSYMBOL_ENTRY __NdsSymbolMap_##name = { _NCRX_T(#name), classname::ads_ ##name, regFunc, -1 } ; \
	extern "C" __declspec(allocate("NDSSYMBOL$__m")) __declspec(selectany) _NDSSYMBOL_ENTRY* const __pNdsSymbolMap_##name = &__NdsSymbolMap_##name ; \
	NDSSYMBOL_ENTRY_PRAGMA(name)

#define NDSCOMMAND_ENTRY_AUTO(classname, name, regFunc) \
	__declspec(selectany) _NDSSYMBOL_ENTRY __NdsSymbolMap_##name = { _NCRX_T("c:") _NCRX_T(#name), classname::ads_ ##name, regFunc, -1 } ; \
	extern "C" __declspec(allocate("NDSSYMBOL$__m")) __declspec(selectany) _NDSSYMBOL_ENTRY* const __pNdsSymbolMap_##name = &__NdsSymbolMap_##name ; \
	NDSSYMBOL_ENTRY_PRAGMA(name)

#define NDSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) \
	__declspec(selectany) _NDSSYMBOL_ENTRY __NdsSymbolMap_##name = { NULL, classname::ads_ ##name, regFunc, nameId } ; \
	extern "C" __declspec(allocate("NDSSYMBOL$__m")) __declspec(selectany) _NDSSYMBOL_ENTRY* const __pNdsSymbolMap_##name = &__NdsSymbolMap_##name ; \
	NDSSYMBOL_ENTRY_PRAGMA(name)

#define NDSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) \
	NDSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc)