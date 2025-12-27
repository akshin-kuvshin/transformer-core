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

#include "MCSTypes.h"
#include "MCSVariant.h"
#include "McsUtils.h"
#ifndef _MCS_CORE_ONLY
	#include "McImages.h"
#endif

//----------------------------------------
// dwFlags/pdwFlags формируются из флагов McHatchFieldEnum
enum McHatchFieldEnum;
struct McsEntityGeometry;
extern "C" MECHCTL_API HRESULT McHatchParamGet(LPCTSTR stHatchParam, McsEntityGeometry& hatch, LPDWORD pdwFlags = NULL);
extern "C" MECHCTL_API HRESULT McHatchParamSet(McsString& stHatchParam, const McsEntityGeometry& hatch, DWORD dwFlags = 0);
extern "C" MECHCTL_API HRESULT McHatchParamEdit(McsString& stHatchParam, HWND hParent);
extern "C" MECHCTL_API HRESULT McHatchParamGetInfoString(LPCTSTR  stHatchParam, McsString& stInfo);
extern "C" MECHCTL_API HRESULT McHatchEntityGetInfoString(const McsEntityGeometry& hatch, McsString& stInfo);

#define MCS_PARAMS_XDATA_NAME TEXT("MCS_PARAMS_DATA")

//----------------------------------------
struct McsLayerData
{
	COLORREF color;
	int      lineweight;
	McsString stLinetype;
	McsString stComment;
	bool isPlottable;

	McsLayerData()
	{
		color      = RGB(255,255,255); // BlackWhite
		lineweight = -5; // MCS_ENTWEIGHT_BYDEFAULT;
		isPlottable = true;
	}

	bool operator == (const McsLayerData& ld) const
	{
		bool bEquColors = (color == ld.color);
		if (!bEquColors) {
			if ((color == 0 && ld.color == RGB(255,255,255)) || (ld.color == 0 && color == RGB(255,255,255)))
				bEquColors = true;
		}
		return (bEquColors
			&& (lineweight == ld.lineweight)
			&& (stLinetype.CompareNoCase(ld.stLinetype) == 0)
			&& (stComment == ld.stComment)
			&& (isPlottable == ld.isPlottable));
	}

	bool operator != (const McsLayerData& ld) const
	{
		return !(*this == ld);
	}
};

//----------------------------------------
struct McParamId
{
	int id;
	McsString sid;
	
	McParamId()
	{
		id = -1;
	}
	McParamId(int _id)
	{
		id = _id;
	}
	McParamId(LPCTSTR pszSID)
	{
		id  = -1;
		sid = pszSID;
	}
	McParamId(McsString _sid)
	{
		id  = -1;
		sid = _sid;
	}
	McParamId(const McParamId& parId)
	{
		*this = parId;
	}
	McParamId& operator = (const McParamId& parId)
	{
		if (this == &parId)
			return *this;
		id  = parId.id;
		sid = parId.sid;
		return *this;
	}
	bool operator == (const McParamId& parId) const
	{
		return id == parId.id && sid == parId.sid;
	}
	bool operator == (int _id) const
	{
		return id == _id;
	}
	bool operator == (LPCTSTR pszSID) const
	{
		return sid == pszSID;
	}
	operator int()     const { return id; }
	operator LPCTSTR() const { return sid; }
	
	bool IsNull() const { return id < 0 && sid.IsEmpty(); }
};

//----------------------------------------
struct McParamEvent
{
	McParamId  parId;
	MCSVariant vData; // Значение параметра/любые данные в зависимости от события
	HRESULT    hres;
	
	McParamEvent()
	{
		hres = E_NOTIMPL;
	}
	
	bool IsOk() const
	{
		return hres == E_NOTIMPL || hres == S_OK;
	}
};

//----------------------------------------
struct IMcDocParamManager : public virtual IMcObject
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcDocParamManager);
	IMCS_STD_METHOD_DEFINITION(IMcDocParamManager, IMcObject)

	// Установка связи с документом
	virtual HRESULT SetDocument(IN IMcDocument* pMcDoc) = 0;

	// работа с параметрами
	virtual HRESULT SetParam(const McParamId& parId, const MCSVariant& var, MCS_STANDARD std = MCS_STD_CUSTOM) = 0;
	virtual HRESULT GetParam(MCSVariant& var, const McParamId& parId, MCS_STANDARD std = MCS_STD_CUSTOM) const = 0;

	// упрощенный доступ к параметрам
	virtual int GetIntParam(const McParamId& parId, MCS_STANDARD std = MCS_STD_CUSTOM) const = 0;
	virtual bool GetBoolParam(const McParamId& parId, MCS_STANDARD std = MCS_STD_CUSTOM) const = 0;
	virtual double GetRealParam(const McParamId& parId, MCS_STANDARD std = MCS_STD_CUSTOM) const = 0;
	virtual McsString GetStringParam(const McParamId& parId, MCS_STANDARD std = MCS_STD_CUSTOM) const = 0;

	// работа со слоями
	virtual HRESULT GetLayers(mcsStringArray& arrLayers) const = 0;
	virtual HRESULT GetLayerData(LPCTSTR pszLayerName, McsLayerData& data) const = 0;

	// Получение имени слоя, начинающегося с префикса текущего профиля.
	// Если переданное имя слоя уже начинается с одного из префиксов, то оно не изменится.
	virtual McsString GetProfiledLayer(LPCTSTR pszLayerName) const = 0;

	// Экспорт параметров в другой документ
	virtual HRESULT ExportParamsToDoc(IN IMcDocument* pMcDoc) const = 0;

	// Вызов диалогов настроек
	virtual int DoQuickDialog(HWND hwndMainWindow = NULL) = 0;
	virtual int DoMainDialog(HWND hwndMainWindow, LPCTSTR pszSIDOpenSection = NULL) = 0;
	virtual int EditParameterRedefinitions(IN const mcsWorkIDArray& ids, IN HWND hParent) = 0;

	// Встроенный диалог настроек
	virtual HWND CreateEmbeddedMcsParams(HWND hwndParent) = 0;
	virtual int  EraseEmbeddedMcsParams() = 0;
	
	// Единицы измерения параметра
	virtual HRESULT GetParamUnits(const McParamId& parId, McUnits::Name& units, McUnits::MeasureCategory& category, MCS_STANDARD std = MCS_STD_CUSTOM) const = 0;
};

//----------------------------------------
struct IMcParamManager : public virtual IMcDocParamManager
{
public:
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcParamManager);
	IMCS_STD_METHOD_DEFINITION(IMcParamManager, IMcDocParamManager)

	// Загрузка/Сохранение настроек в файл
	virtual HRESULT LoadSettings(LPCTSTR pszPath = NULL) = 0;
	virtual HRESULT SaveSettings(LPCTSTR pszPath = NULL) = 0;

	// Слияние XML настроек
	virtual HRESULT MergeSettings(LPCTSTR pszNewSettingsPath, LPCTSTR pszOldSettingsPath) = 0;

	//----------------------------------------
	// Системный доступ
	virtual HRESULT system_SetDefaultDocument(IMcDocument* pDoc) { return E_NOTIMPL; }
	virtual bool system_HasDefaultDocument() { return false; }

	virtual HRESULT system_SetParam(int idParam, const MCSVariant& var, MCS_STANDARD std, IMcDocument* pDoc) { return E_NOTIMPL; }
	virtual HRESULT system_GetParam(MCSVariant& var, int idParam, MCS_STANDARD std, IMcDocument* pDoc) const { return E_NOTIMPL; }

	virtual int system_GetIntParam(int idParam, MCS_STANDARD std, IMcDocument* pDoc) const { return 0; }
	virtual bool system_GetBoolParam(int idParam, MCS_STANDARD std, IMcDocument* pDoc) const { return false; }
	virtual double system_GetRealParam(int idParam, MCS_STANDARD std, IMcDocument* pDoc) const { return E_NOTIMPL; }
	virtual McsString system_GetStringParam(int idParam, MCS_STANDARD std, IMcDocument* pDoc) const { return McsString(); }

	virtual int system_OpenParamDialog(HWND hwndMainWindow, LPCTSTR pszSIDOpenSection, IMcDocument* pDoc) { return 0; }
};

extern "C" MCTYP_API IMcParamManager *gpMcDefParamManager;

//----------------------------------------
__inline int McGetIntParam(int idParam, MCS_STANDARD std = MCS_STD_CUSTOM, IMcDocument* pDoc = NULL)
{
	return gpMcDefParamManager->system_GetIntParam(idParam, std, pDoc);
}

//----------------------------------------
__inline bool McGetBoolParam(int idParam, MCS_STANDARD std = MCS_STD_CUSTOM, IMcDocument* pDoc = NULL)
{
	return gpMcDefParamManager->system_GetBoolParam(idParam, std, pDoc);
}

//----------------------------------------
__inline double McGetRealParam(int idParam, MCS_STANDARD std = MCS_STD_CUSTOM, IMcDocument* pDoc = NULL)
{
	return gpMcDefParamManager->system_GetRealParam(idParam, std, pDoc);
}

//----------------------------------------
__inline McsString McGetStringParam(int idParam, MCS_STANDARD std = MCS_STD_CUSTOM, IMcDocument* pDoc = NULL)
{
	return gpMcDefParamManager->system_GetStringParam(idParam, std, pDoc);
}

//----------------------------------------
__inline MCSVariant McGetVariantParam(int idParam, MCS_STANDARD std = MCS_STD_CUSTOM, IMcDocument* pDoc = NULL)
{
	MCSVariant var;
	gpMcDefParamManager->system_GetParam(var, idParam, std, pDoc);
	return var;
}

//----------------------------------------
__inline HRESULT McGetParam(MCSVariant& var, int idParam, MCS_STANDARD std = MCS_STD_CUSTOM, IMcDocument* pDoc = NULL)
{
	return gpMcDefParamManager->system_GetParam(var, idParam, std, pDoc);
}

//----------------------------------------
__inline HRESULT McSetParam(IN int idParam, const MCSVariant& var, MCS_STANDARD std = MCS_STD_CUSTOM, IMcDocument* pDoc = NULL)
{
	return gpMcDefParamManager->system_SetParam(idParam, var, std, pDoc);
}

//----------------------------------------
__inline int McOpenParamDialog(HWND hwndMainWindow, LPCTSTR pszSIDOpenSection = NULL, IMcDocument* pDoc = NULL)
{
	return gpMcDefParamManager->system_OpenParamDialog(hwndMainWindow, pszSIDOpenSection, pDoc);
}

//----------------------------------------
#define PMI(IDPARAM) (McGetIntParam(IDPARAM))
#define PMR(IDPARAM) (McGetRealParam(IDPARAM))
#define PMB(IDPARAM) (McGetBoolParam(IDPARAM))
#define PMS(IDPARAM) (McGetStringParam(IDPARAM))
#define PMV(IDPARAM) (McGetVariantParam(IDPARAM))

#define PMI2(IDPARAM, STD) (McGetIntParam(IDPARAM, STD))
#define PMR2(IDPARAM, STD) (McGetRealParam(IDPARAM, STD))
#define PMB2(IDPARAM, STD) (McGetBoolParam(IDPARAM, STD))
#define PMS2(IDPARAM, STD) (McGetStringParam(IDPARAM, STD))
#define PMV2(IDPARAM, STD) (McGetVariantParam(IDPARAM, STD))

//----------------------------------------
struct McSystemSetPMDocument
{
	McSystemSetPMDocument(IMcDocument* pDoc)
	{
		gpMcDefParamManager->system_SetDefaultDocument(pDoc);
	}
	~McSystemSetPMDocument()
	{
		gpMcDefParamManager->system_SetDefaultDocument(NULL);
	}
};

//----------------------------------------
// Define COLOR constants
//----------------------------------------
#define MCS_COLOR_RED		1
#define MCS_COLOR_YELLOW	2
#define MCS_COLOR_GREEN		3
#define MCS_COLOR_CYAN		4
#define MCS_COLOR_BLUE		5
#define MCS_COLOR_MAGENTA	6
#define MCS_COLOR_BLACK		7
#define MCS_COLOR_BYLAYER	256
#define MCS_COLOR_BYBLOCK	0

//----------------------------------------
// Define LINE WEIGHT constants
//----------------------------------------
#define MCS_LW_THIN 25
#define MCS_LW_THICK 60
#define MCS_LW0 25
#define MCS_LW1 60

//----------------------------------------
// McsParams-Dialog-messages
//----------------------------------------
#define MCS_PARMSG_DLG_APPLY_CHANGES	(WM_USER + 0x0408)	// Применить параметры в текущей сессии диалога настроек
#define MCS_PARMSG_DLG_MODIFIIED		(WM_USER + 0x0409)	// Сообщение об изменившемся состоянии диалога настроек после каких-либо изменений пользователем

//----------------------------------------
