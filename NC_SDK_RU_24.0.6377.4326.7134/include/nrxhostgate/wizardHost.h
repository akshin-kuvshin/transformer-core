#pragma once


struct _NRXCOMMAND_ENTRY {
	const NCHAR* pszCmdGroupName;
	const NCHAR* pszCmdGlobalName;
	const NCHAR* pszCmdLocalName;
	NRX::Int32 commandFlags;
	NcRxFunctionPtr pCmdFct;
	NcEdUIContext* pUIContext;
	UINT localNameID;
};

#pragma section("NRXCMD$__a", read, shared)
#pragma section("NRXCMD$__z", read, shared)
#pragma section("NRXCMD$__m", read, shared)

extern "C"
{
	__declspec(selectany) __declspec(allocate("NRXCMD$__a")) _NRXCOMMAND_ENTRY* __pNrxCmdMapEntryFirst = NULL;
	__declspec(selectany) __declspec(allocate("NRXCMD$__z")) _NRXCOMMAND_ENTRY* __pNrxCmdMapEntryLast = NULL;
}

#ifdef _WIN64
#define NRXCMD_ENTRY_PRAGMA(group,globCmd) __pragma(comment(linker, "/include:__pNrxCmdMap_" #group #globCmd));
#else
#define NRXCMD_ENTRY_PRAGMA(group,globCmd) __pragma(comment(linker, "/include:___pNrxCmdMap_" #group #globCmd));
#endif

#define NRXCMD_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext) \
	__declspec(selectany) _NRXCOMMAND_ENTRY __NrxCmdMap_##group##globCmd = { _NCRX_T(#group), _NCRX_T(#globCmd), _NCRX_T(#locCmd), cmdFlags, classname::##group ##globCmd, UIContext, 0 }; \
	extern "C" __declspec(allocate("NRXCMD$__m")) __declspec(selectany) _NRXCOMMAND_ENTRY* const __pNrxCmdMap_##group##globCmd = &__NrxCmdMap_##group##globCmd; \
	NRXCMD_ENTRY_PRAGMA(group, globCmd)

#define NRXCMD_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext) \
	__declspec(selectany) _NRXCOMMAND_ENTRY __NrxCmdMap_##group##globCmd = { _NCRX_T(#group), _NCRX_T(#globCmd), NULL, cmdFlags, classname::##group ##globCmd, UIContext, locCmdId }; \
	extern "C" __declspec(allocate("NRXCMD$__m")) __declspec(selectany) _NRXCOMMAND_ENTRY* const __pNrxCmdMap_##group##globCmd = &__NrxCmdMap_##group##globCmd; \
	NRXCMD_ENTRY_PRAGMA(group, globCmd)


class NrxApp : public NrxDbApp
{
public:
	NrxApp() : NrxDbApp() {}

	virtual NcRx::AppRetCode On_kInitAppMsg(void* pkt)
	{
		NcRx::AppRetCode retCode = NrxDbApp::On_kInitAppMsg(pkt);
		_NRXCOMMAND_ENTRY** ppNrxCmdMapEntryFirst = &__pNrxCmdMapEntryFirst + 1;
		_NRXCOMMAND_ENTRY** ppNrxCmdMapEntryLast = &__pNrxCmdMapEntryLast;
		NCHAR buffer[133];
		for (_NRXCOMMAND_ENTRY** ppEntry = ppNrxCmdMapEntryFirst; ppEntry < ppNrxCmdMapEntryLast; ppEntry++)
		{
			if (*ppEntry != NULL)
			{
				if ((*ppEntry)->pszCmdLocalName == NULL)
					::LoadStringW(m_hdllInstance, (*ppEntry)->localNameID, buffer, 132);

				ncedRegCmds->addCommand(
					(*ppEntry)->pszCmdGroupName,
					(*ppEntry)->pszCmdGlobalName,
					(*ppEntry)->pszCmdLocalName == NULL ? buffer : (*ppEntry)->pszCmdLocalName,
					(*ppEntry)->commandFlags,
					(*ppEntry)->pCmdFct,
					(*ppEntry)->pUIContext,
					-1,
					((*ppEntry)->commandFlags & NCRX_CMD_SESSION) ? NULL : m_hdllInstance,
					NULL
				);
			}
		}
		return (retCode);
	}

	virtual NcRx::AppRetCode On_kUnloadAppMsg(void* pkt)
	{
		NcRx::AppRetCode retCode = NrxDbApp::On_kUnloadAppMsg(pkt);
		_NRXCOMMAND_ENTRY** ppNrxCmdMapEntryFirst = &__pNrxCmdMapEntryFirst + 1;
		_NRXCOMMAND_ENTRY** ppNrxCmdMapEntryLast = &__pNrxCmdMapEntryLast;
		for (_NRXCOMMAND_ENTRY** ppEntry = ppNrxCmdMapEntryFirst; ppEntry < ppNrxCmdMapEntryLast; ppEntry++)
		{
			if (*ppEntry != NULL)
			{
				ncedRegCmds->removeCmd(
					(*ppEntry)->pszCmdGroupName,
					(*ppEntry)->pszCmdGlobalName
				);
			}
		}
		return (retCode);
	}

	virtual NcRx::AppRetCode On_kLoadDwgMsg(void* pkt)
	{
		NcRx::AppRetCode retCode = NrxDbApp::On_kLoadDwgMsg(pkt);
		_NDSSYMBOL_ENTRY** ppNdsSymbolMapEntryFirst = &__pNdsSymbolMapEntryFirst + 1;
		_NDSSYMBOL_ENTRY** ppNdsSymbolMapEntryLast = &__pNdsSymbolMapEntryLast;
		NCHAR buffer[133];
		int param = 0;
		for (_NDSSYMBOL_ENTRY** ppEntry = ppNdsSymbolMapEntryFirst; ppEntry < ppNdsSymbolMapEntryLast; ppEntry++)
		{
			if (*ppEntry != NULL)
			{
				if ((*ppEntry)->pszName == NULL)
					::LoadString(m_hdllInstance, (*ppEntry)->nameID, buffer, 132);

				ncedDefun(
					(*ppEntry)->pszName == NULL ? buffer : (*ppEntry)->pszName,
					param
				);
				if ((*ppEntry)->bRegFunc == true)
					ncedRegFunc((*ppEntry)->fptr, param);

				param++;
			}
		}
		return (retCode);
	}

	virtual NcRx::AppRetCode On_kUnloadDwgMsg(void* pkt)
	{
		NcRx::AppRetCode retCode = NrxDbApp::On_kUnloadDwgMsg(pkt);
		return (retCode);
	}

	virtual NcRx::AppRetCode On_kInvkSubrMsg(void* pkt)
	{
		NcRx::AppRetCode retCode = NrxDbApp::On_kInvkSubrMsg(pkt);
		int param = ncedGetFunCode();
		_NDSSYMBOL_ENTRY** ppNdsSymbolMapEntryFirst = &__pNdsSymbolMapEntryFirst + 1;
		_NDSSYMBOL_ENTRY** ppNdsSymbolMapEntryLast = &__pNdsSymbolMapEntryLast;
		int paramIter = 0;
		for (_NDSSYMBOL_ENTRY** ppEntry = ppNdsSymbolMapEntryFirst; ppEntry < ppNdsSymbolMapEntryLast; ppEntry++)
		{
			if (*ppEntry != NULL)
			{
				if (paramIter++ == param)
				{
					(*((*ppEntry)->fptr))();
					break;
				}
			}
		}
		return (retCode);
	}
};
