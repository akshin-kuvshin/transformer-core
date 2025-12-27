
#pragma once

#include "IMcObjects.h"
#include "IMcBigStream.h"

IMCS_DECL_INTERFACE(IMcBimAccess, "F2FB85B6-3612-4A81-B24F-1FA71BFC83CD")
IMCS_DECL_INTERFACE(IMcBimGate, "C9E967C2-82C6-417a-8EAF-5D4F48C7132C")

//------------------------------------------------------------------------
// Архитектурный материал
//------------------------------------------------------------------------
struct McArchMaterial
{
	McsStringW m_sName;
	double m_rWidth;
	COLORREF m_Color;

	McArchMaterial()
		: m_rWidth(0), m_Color(0)
	{
	}
	McArchMaterial(LPCWSTR pszName, const double& rWidth, const COLORREF& color)
		: m_sName(pszName), m_rWidth(rWidth), m_Color(color)
	{
	}
};
typedef McsArray<McArchMaterial, const McArchMaterial&> McArchMaterialArray;
typedef McsMap<McsStringW, LPCWSTR, MCSVariant, const MCSVariant&> McArchPropertiesMap;

//------------------------------------------------------------------------
// Структура для передачи архитектурных параметров IfcEntity
//------------------------------------------------------------------------
struct McArchData
{
	McArchPropertiesMap m_mapProjectProperties;
	McArchPropertiesMap m_mapObjectProperties;
	McArchPropertiesMap m_mapPositionProperties;
	McArchPropertiesMap m_mapStyleProperties;
	McArchMaterialArray m_arMaterials;

	McArchData()
	{
	}

	//-----------------------------------------------
	void Reset()
	{
		m_mapProjectProperties.RemoveAll();
		m_mapObjectProperties.RemoveAll();
		m_mapPositionProperties.RemoveAll();
		m_mapStyleProperties.RemoveAll();
		m_arMaterials.RemoveAll();
	}

	//-----------------------------------------------
	bool IsEmpty() const
	{
		return	m_mapProjectProperties.IsEmpty() &&
			m_mapObjectProperties.IsEmpty() &&
			m_mapPositionProperties.IsEmpty() &&
			m_mapStyleProperties.IsEmpty() &&
			m_arMaterials.IsEmpty();
	}
};

//------------------------------------------------------------------------
// Элемент IFC-структуры
//------------------------------------------------------------------------
struct McIfcNode
{
	GUID guid;              // уникальный идентификатор узла (генерируется при импорте IFC)
	McsStringW sIfcType;    // Ifc-свойство "IfcType"
	McsStringW sName;       // Ifc-свойство "Name"
	mcsIntArray arChildren; // индексы дочерних узлов в общем последовательном списке
	__int64 handle;         // дескриптор графического объекта (0, если узел виртуальный и объекта нет)
	McArchData m_ArchData;  // архитектурные параметры

	//-------------------------------------
	McIfcNode()
		: guid(GUID_NULL), handle(0)
	{
	}
};
typedef McsArray<McIfcNode, const McIfcNode&> McIfcNodeArray;

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// McBimEntityProperty - параметры свойства IfcEntity для инспектора свойств
//---------------------------------------------------------------------------
struct McBimEntityProperty
{
	McsString stName;
	McsString stCategory;
	MCS_CTRL eType;
	McUnits::Name eUnits;
	mcsStringArray astValuesList;
	bool isReadOnly;
	__int64 propID;

	McBimEntityProperty()
	{
		eType = MC_EDIT_STRING;
		eUnits = McUnits::kUndefined;
		isReadOnly = false;
		propID = 0;
	}
};
typedef McsArray<McBimEntityProperty, const McBimEntityProperty&> McBimEntityPropertyArray;

//---------------------------------------------------------------------------
// McBimNodeProperty - свойство узла для боковой панели IFC (C#)
//---------------------------------------------------------------------------
struct McBimNodeProperty
{
	McsString sName;
	McsString sCategory;
	MCSVariant value;
	bool isReadOnly;
	__int64 propID;

	McBimNodeProperty()
	{
		isReadOnly = false;
		propID = 0;
	}
};
typedef McsArray<McBimNodeProperty, const McBimNodeProperty&> McBimNodePropertyArray;

//------------------------------------------------------------------------
// Информация о загруженном файле IFC
// Структура заведена из-за использования двух разных объектов-хранилищ импортированных файов IFC,
// чтобы гарантировать в будущем синхронные изменения в разных классах.
// IMcBimDocStorage   - стандартный Mc-объект с сериализацией в IMcsStream (версия 1)
// mcsDbIfcBigStorage - специальный платформенный объект с сериализацией в IMcBigStream (версия 2)
//------------------------------------------------------------------------
struct McBimStorageInfo
{
public:
	enum
	{
		kUndefined    = 0x00000000,
		kArchitecture = 0x00000001, // McJsSelect::kArchitecture
	};

private:
	IMcsStreamPtr   m__pStream;
	IMcBigStreamPtr m__pBigStream;

public:
	_declspec(property(get = get_McsStream, put = put_McsStream)) IMcsStreamPtr m_pStream;
	_declspec(property(get = get_BigStream, put = put_BigStream)) IMcBigStreamPtr m_pBigStream;

	mcsWorkID  m_idStorage;      // идентификатор объекта типа IMcBimDocStorage, если используется m_pStream
	McsStringW m_sIfcPath;       // путь к импортированному файлу IFC
	DWORD      m_dwImportFlags;  // флаги импорта (см. McBimImportEnum)
	int        m_iImportOrder;   // порядковый номер для сохранения порядка отображения на панели IFC

public:
	//----------------------------------------------
	McBimStorageInfo()
	{
		m_dwImportFlags = 0;
		m_iImportOrder = 0;
	}

	//----------------------------------------------
	void Clear()
	{
		m__pStream = UNKNULL;
		m__pBigStream = UNKNULL;
		m_sIfcPath.Empty();
		m_dwImportFlags = 0;
		m_iImportOrder = 0;
	}

	//----------------------------------------------
	IMcsStreamPtr get_McsStream() const
	{
		return m__pStream;
	}

	//----------------------------------------------
	IMcsStreamPtr put_McsStream(IMcsStreamPtr pStream)
	{
		m__pBigStream = UNKNULL;
		m__pStream = pStream;
		return m__pStream;
	}

	//----------------------------------------------
	IMcBigStreamPtr get_BigStream() const
	{
		return m__pBigStream;
	}

	//----------------------------------------------
	IMcBigStreamPtr put_BigStream(IMcBigStreamPtr pBigStream)
	{
		m__pStream = UNKNULL;
		m__pBigStream = pBigStream;
		return m__pBigStream;
	}

	//----------------------------------------------
	bool IsValid() const
	{
		if (!m_sIfcPath.IsEmpty())
		{
			if ((m__pBigStream && m_idStorage.IsNull()) || (m__pStream && !m_idStorage.IsNull()))
				return true;
		}
		return false;
	}

	//----------------------------------------------
	McsStringW GetIfcPathAsStorageName() const
	{
		McsStringW s = m_sIfcPath;
		s.Remove(':');
		s.Replace(L"\\", L"_");
		return s;
	}
};

//------------------------------------------------------------------------
// Инструмент для взаимодействия с McBimService/IFC
//------------------------------------------------------------------------
struct IMcBimAccess : public virtual IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMcBimAccess, IMcObject);

	//----------------------------------------------
	// Методы для боковой панели IFC
	//----------------------------------------------
	
	// Импортировать заданный IFC в активный документ
	virtual HRESULT ImportIFC(IN LPCWSTR pszIfcPath, bool bArchData) { return E_NOTIMPL; }

	// Удалить из активного документа импортированный IFC
	virtual HRESULT RemoveIFC(IN LPCWSTR pszIfcPath) { return E_NOTIMPL; }

	// Получение списка путей к импортированным в документ файлам IFC
	virtual HRESULT GetImportedIfcPaths(IN const mcsWorkID& idDoc, OUT mcsStringArrayW& arIfcPaths) { return E_NOTIMPL; }

	// Получение списка узлов IFC
	virtual HRESULT GetIfcNodes(IN const mcsWorkID& idDoc, IN LPCWSTR pszIfcPath, OUT McIfcNodeArray& arNodes) { return E_NOTIMPL; }

	// Получение флага импорта архитектурных данных IFC
	virtual HRESULT GetIfcArchitectureFlag(IN const mcsWorkID& idDoc, IN LPCWSTR pszIfcPath, OUT bool& bArchitecture) { return E_NOTIMPL; }

	// Управление видимостью
	virtual HRESULT GetNodeVisibility(IN const mcsWorkID& idDoc, IN LPCWSTR pszIfcPath, IN const GUID& idNode, OUT bool& bVisible) { return E_NOTIMPL; }
	virtual HRESULT SetNodesVisibility(IN const mcsWorkID& idDoc, IN LPCWSTR pszIfcPath, IN const mcsGUIDArray& idsNodes, bool bVisible) { return E_NOTIMPL; }

	// Свойства узла
	virtual HRESULT GetNodeProperties(IN const mcsWorkID& idDoc, IN LPCWSTR pszIfcPath, IN const GUID& idNode, OUT McBimNodePropertyArray& properties) { return E_NOTIMPL; }
	virtual HRESULT SetNodeProperty(IN const mcsWorkID& idDoc, IN LPCWSTR pszIfcPath, IN const GUID& idNode, IN __int64 propID, IN const MCSVariant& data) { return E_NOTIMPL; }

	// Экспорт/импорт скрипта с настройками совмещения/отображения всех импортированных в документ файлов IFC
	virtual HRESULT ExportModelParameters(IN const mcsWorkID& idDoc) { return E_NOTIMPL; }
	virtual HRESULT ImportModelParameters(IN const mcsWorkID& idDoc) { return E_NOTIMPL; }

	// Получить текстовый объект модели
	virtual IMcEntityPtr GetIfcProjectEntity(const mcsWorkID& idDoc, IN LPCWSTR pszIfcPath) { return UNKNULL; }

	// Получить габариты IFC-объекта
	virtual HRESULT GetIfcObjectBound(const mcsWorkID& idDoc, IN __int64 handle, OUT mcsBoundBlock& bound) { return E_NOTIMPL; }

	//----------------------------------------------
	// Методы для боковой панели IFC/BCF
	//----------------------------------------------

	// Удаление объектов
	virtual HRESULT EraseObjects(IN const mcsWorkID& idDoc, IN const mcsI64Array& handles) { return E_NOTIMPL; }

	// Селекция объектов
	virtual HRESULT SelectObjects(IN const mcsWorkID& idDoc, IN const mcsI64Array& handles, bool bNew = true) { return E_NOTIMPL; }

	// Получение списков удаленных/восстановленных/показанных/скрытых объектов и измененных узлов во время работы команды
	virtual HRESULT GetCommandErasedObjects(OUT mcsI64Array& handles) { return E_NOTIMPL; }
	virtual HRESULT GetCommandRestoredObjects(OUT mcsI64Array& handles) { return E_NOTIMPL; }
	virtual HRESULT GetCommandShownObjects(OUT mcsI64Array& handles) { return E_NOTIMPL; }
	virtual HRESULT GetCommandHiddenObjects(OUT mcsI64Array& handles) { return E_NOTIMPL; }
	virtual HRESULT GetCommandChangedNodes(OUT mcsGUIDArray& guids) { return E_NOTIMPL; }

	//----------------------------------------------
	// Методы для IfcEntity
	//----------------------------------------------

	// Возвращает указатели на массив геометрии и матрицу трансформации объекта handle из документа pDoc
	virtual HRESULT GetGeometry(IN IMcDocument* pDoc, IN __int64 handle, OUT mcsGeomEntArray*& pGeometry, OUT mcsMatrix*& pTfm, OUT COLORREF*& pCustomColor) { return E_NOTIMPL; }

	// Реакторы объекта handle из документа pDoc
	// на трансформацию/удаление/...
	virtual HRESULT OnTransform(IN IMcDocument* pDoc, IN __int64 handle, IN const mcsMatrix& tfm) { return E_NOTIMPL; }
	virtual HRESULT OnErase(IN IMcDocument* pDoc, IN __int64 handle) { return E_NOTIMPL; }

	// Получение свойств набора объектов
	virtual HRESULT GetProperties(IN IMcDocument* pDoc, IN mcsI64Array& handles, OUT McBimEntityPropertyArray& properties) { return E_NOTIMPL; }
	virtual HRESULT GetProperty(IN IMcDocument* pDoc, IN __int64 handle, IN __int64 propID, OUT MCSVariant& data) { return E_NOTIMPL; }
	virtual HRESULT SetProperty(IN IMcDocument* pDoc, IN __int64 handle, IN __int64 propID, IN const MCSVariant& data) { return E_NOTIMPL; }

	//----------------------------------------------
	// Системные методы
	//----------------------------------------------

	// Сброс флага выполненного чтения ППР-цветов для раскраски импортированных файлов IFC
	virtual HRESULT ResetPPRColors(IN IMcDocument* pDoc) { return E_NOTIMPL; }

	// Получение шаблона правил проверки модели
	virtual HRESULT GetCheckingRulesTemplate(OUT McsStringW& sRulesScript) { return E_NOTIMPL; }

	// Проверка модели
	virtual HRESULT CheckModel(IN LPCWSTR pszModelScript, IN LPCWSTR pszRulesScript, OUT McsStringW& sReportScript) { return E_NOTIMPL; }

	// Получение хеш-суммы файла IFC
	virtual HRESULT GetImportedIfcHash(IN const mcsWorkID& idDoc, IN LPCWSTR pszIfcPath, OUT McsStringW& sHash) { return E_NOTIMPL; }
	// Проверка файлов IFC на изменение посредством сравнения сохраненной и текущей хеш-сумм
	virtual HRESULT CheckIfcHashs(IN LPCWSTR pszCheckHashJson, OUT McsStringW& sCheckHashJsonResult) { return E_NOTIMPL; }

	// IfcBigStream
	virtual HRESULT onReadIfcBigStreamAfter(IN IMcDocument* pDoc, const McBimStorageInfo& info) { return E_NOTIMPL; }
	virtual HRESULT onWriteIfcBigStreamBefore(IN IMcDocument* pDoc, IN OUT McBimStorageInfo& info) { return E_NOTIMPL; }

	// Получение количества объектов типа mcsDbIfcBigStorage в требуемом документе
	virtual HRESULT GetIfcBigStorageCount(IMcDocument* pDoc, OUT DWORD& dwBigStorageCount) { return E_NOTIMPL; }
};

//------------------------------------------------------------------------
__inline IMcBimAccessPtr GetBimAccessDyn()
{
	IMcBimAccessPtr pAccess;
	FARPROC pProc = GetProcAddress(GetModuleHandleA("McBimAccess.dll"), "GetAccess");
	if (pProc)
		pAccess = ((IMcBimAccess*(*)())pProc)();
	return pAccess;
}

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// IMcBimGate
//---------------------------------------------------------------------------
interface IMcBimGate : public virtual IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMcBimGate, IMcObject);

	// IfcEntity
	virtual HRESULT AddIFCEntity(IN IMcDocument* pDoc, OUT __int64& handle, IN COLORREF color, IN bool bVisibility, IN double rAlpha = -1, IN LPCTSTR pszLayerName = NULL) { return E_NOTIMPL; }
	virtual HRESULT SetVisibility(IN IMcDocument* pDoc, IN __int64 handle, IN bool bVisibility) { return E_NOTIMPL; }
	virtual HRESULT GetViewParameters(IN IMcDocument* pDoc, IN __int64 handle, OUT bool& bVisibility, OUT COLORREF& clrRGB, OUT double& rAlpha) { return E_NOTIMPL; }
	virtual HRESULT Erase(IN IMcDocument* pDoc, IN const mcsI64Array& handles) { return E_NOTIMPL; }
	virtual HRESULT AddToSelectionSet(IN IMcDocument* pDoc, IN const mcsI64Array& handles, IN bool bNew = true) { return E_NOTIMPL; }
	virtual HRESULT Invalidate(IN IMcDocument* pDoc, IN const mcsI64Array& handles) { return E_NOTIMPL; }

	// IfcBigStorage
	virtual HRESULT AddIfcBigStorage(IN IMcDocument* pDoc, IN const McBimStorageInfo& info) { return E_NOTIMPL; }
	virtual HRESULT EraseIfcBigStorage(IN IMcDocument* pDoc, LPCTSTR pszStorageName) { return E_NOTIMPL; }
	virtual HRESULT ForceReadIfcBigStorages(IN IMcDocument* pDoc) { return E_NOTIMPL; }
};
