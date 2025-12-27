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

#include "IMechanics.h"
#include "IMcDimension.h"
#include "3DCommon.h"

//===========================================================================
struct McDynDimData
{
	enum
	{
		eConstrain   = 0x00000001,
		eActive      = 0x00000002,
		eInvisible   = 0x00000004,
		eHighlighted = 0x00000008,
		eEditable    = 0x00000010,
		eAlignCamera = 0x00000020,

		eNormal    = 0,
	};
	DWORD dwID;
	DWORD dwStyle;
	McsString stDesc;// Будет показано в диалоге редактирования
	COLORREF color;
	COLORREF colorActive;
	IMcDimensionPtr pDim;
	mcsGeomEntArray geom;

	McDynDimData()
	{
		dwID = 0;
		dwStyle = McDynDimData::eNormal;
		color = 0x00000000;
		colorActive = 0x00ff00ff;
	}
};
//===========================================================================
class McDynDimDataArray : public McsArray<McDynDimData, const McDynDimData&>
{
public:
	int FindByID(IN DWORD dwID) const
	{
		int i;
		for(i = m_nSize - 1; i >= 0; i--)
			if(m_pData[i].dwID == dwID)
				break;
		return i;
	}
	void Check() const
	{
		for(int i = 0; i < m_nSize - 1; i++)
			for(int j = i + 1; j < m_nSize; j++)
				MCSASSERT(m_pData[i].dwID != m_pData[j].dwID)
	}
};

//===========================================================================
IMCS_DECL_INTERFACE(IMcDynamicDimensionContainer, "1E6384AB-7DBC-49da-8E6B-F44C88446F35")
struct IMcDynamicDimensionContainer : public virtual IMcObject
{
	IMCS_STD_METHOD_DEFINITION(IMcDynamicDimensionContainer, IMcObject);

	// Устанавливает (либо снимает) флаг McDynDimData::eEditable на все размеры
	virtual void SetJointEdit(IN bool isJointEdit) = 0;

	// В этом режиме размеры не будут удаляться между вызовами GetEntity, а будут существовать
	// до момента уничтожения монитора. Обновление происходит также - в ActiveEnt.
	// По умолчанию выключено.
	virtual void SetStatic(IN bool isStatic) = 0;
	virtual bool IsStatic() = 0;
	// В этом режиме нормаль в аргументах функций не учитывается, вся графика в плоскости xOy,
	// лево слева, верх вверху, z нулевая.
	// По умолчанию выключено.
	virtual void Set2D(IN bool is2D) = 0;
	virtual bool Is2D() = 0;

	virtual HRESULT SetLinear(
		IN DWORD dwID,
		IN const mcsPoint& pntStart,
		IN const mcsPoint& pntEnd,
		IN LPCTSTR stDesc,
		IN const mcsPoint& pntText,
		IN McLinearDimensionType type = kMcDimTypeAligned,
		IN const mcsVector& vecNormal = mcsVector::kZAxis) = 0;
	virtual HRESULT SetTwoLinearChain(
		IN DWORD dwID1,
		IN DWORD dwID2,
		IN const mcsPoint& pntStart,
		IN const mcsPoint& pntEnd,
		IN const mcsPoint& pntMid,
		IN const mcsPoint& pntText1,
		IN const mcsPoint& pntText2,
		IN LPCTSTR stDesc1 = NULL,
		IN LPCTSTR stDesc2 = NULL,
		IN const mcsVector& vecNormal = mcsVector::kZAxis) = 0;
	virtual HRESULT SetAngular(
		IN DWORD dwID,
		IN const mcsPoint& pntStart,
		IN const mcsPoint& pntEnd,
		IN const mcsPoint& pntCenter,
		IN LPCTSTR stDesc,
		IN const mcsPoint& pntText) = 0;
	virtual HRESULT SetArc(
		IN DWORD dwID,
		IN const mcsPoint& ptStart,
		IN const mcsPoint& ptEnd,
		IN const mcsPoint& ptCenter,
		IN LPCTSTR lpszDesc,
		IN const mcsPoint& ptText) = 0;
	virtual HRESULT SetTwoArcChain(
		IN DWORD dwID1,
		IN DWORD dwID2,
		IN const mcsPoint& ptStart,
		IN const mcsPoint& ptEnd,
		IN const mcsPoint& ptMiddle,
		IN const mcsPoint& ptCenter,
		IN const mcsPoint& pntText1,
		IN const mcsPoint& pntText2,
		IN LPCTSTR stDesc1 = NULL,
		IN LPCTSTR stDesc2 = NULL) = 0;

	virtual HRESULT SetLinear(
		IN DWORD dwID,
		IN const mcsPoint& pntStart,
		IN const mcsPoint& pntEnd,
		IN LPCTSTR stDesc,
		IN double H,
		IN McLinearDimensionType type = kMcDimTypeAligned,
		IN const mcsVector& vecNormal = mcsVector::kZAxis) = 0;
	virtual HRESULT SetAngular(
		IN DWORD dwID,
		IN const mcsPoint& pntStart,
		IN const mcsPoint& pntEnd,
		IN const mcsPoint& pntCenter,
		IN LPCTSTR stDesc,
		IN double H) = 0;
	virtual HRESULT SetArc(
		IN DWORD dwID,
		IN const mcsPoint& ptStart,
		IN const mcsPoint& ptEnd,
		IN const mcsPoint& ptCenter,
		IN double H,
		IN LPCTSTR lpszDesc) = 0;

	virtual HRESULT InitDynamicDimension(IN IMcDimension* pDim) = 0;

	virtual IMcDimensionPtr GetDimension(IN DWORD dwID) = 0;
	virtual HRESULT         RemoveDimension(IN DWORD dwID) = 0;

	virtual HRESULT HideDimensionLines(IN DWORD dwID, IN bool exLine1 = true, IN bool exLine2 = true, IN bool dimLine1 = true, IN bool dimLine2 = true) = 0;

	virtual HRESULT SetActive(IN DWORD dwID) = 0;
	virtual HRESULT AddStyle(IN DWORD dwID, IN DWORD dwFlag) = 0;
	virtual HRESULT RemoveStyle(IN DWORD dwID, IN DWORD dwFlag) = 0;
	virtual bool    GetStyle(IN DWORD dwID, IN DWORD dwFlag) = 0;
	virtual HRESULT SetColors(IN DWORD dwID, IN COLORREF color, IN COLORREF colorActive) = 0;
	virtual HRESULT GetColors(IN DWORD dwID, OUT COLORREF& color, OUT COLORREF& colorActive) = 0;

	virtual HRESULT GetUCS(OUT mcsVector& vX, OUT mcsVector& vY) = 0;

	// for interanal use
	virtual McDynDimDataArray* GetDynDimData() = 0;
	virtual HRESULT EditValues(OUT mcsDwordArray& dwIds, OUT mcsDoubleArray& rValues, IN HWND hParent, IN TCHAR chFirst = 0) = 0;
	virtual const mcsGeomEntArray& GetGeometry(IN DWORD dwID) = 0;
};
//===========================================================================
// !!! all distance values should be measured with millimeters and 
// angles values with degrees
struct EM_Entity
{
	EntityGeometryTypeEnum type; // old, now geometry type involved in EntDescr
	McsEntityGeometry      EntDescr;

		// Note: Case of blockref:
		//		idObject = null
		//		idSnappedObject = idBLockRef
		// 3D Face/Edge/Vertex:
		//		idObject = id of face/edge/vertex (FEV)
		//		idSnappedObject = id of host object for FEV
		// In common case:
		//	idObject == idSnappedObject
	mcsWorkID  idObject;
	mcsWorkID  idSnappedObject;

	mcsPoint   pnt;       // point with osnap, snap and other
	mcsPoint   pntRaw;    // raw, real point
	mcsVector  vec;
	mcsVector  normal;    // normal to object in snapped point, (0,0,0) means that field can't be evaluated or has no meaning
	double     rValue;

	// active selection plane (generaly for 3D environments)
	mcsPlane   ViewPlane;

		// Reference parameter for snapped point.
		// Supports links with objects in blockrefs.
	McGeometryParam geomParam;

	bool bPointComputed;// true, если pnt вычислен с наложением каких-либо эфектов типа снапа, орто и т.п.
	//.........................................................................

	EM_Entity(void)
	{
		type = EntDescr.geometryType();
		rValue = 0;
		bPointComputed = false;
	}

	EM_Entity& operator= (const EM_Entity& cf)
	{
		if(this == &cf)
			return *this;

		type      = cf.type;
		EntDescr  = cf.EntDescr;

		idObject  = cf.idObject;
		idSnappedObject = cf.idSnappedObject;
		pnt       = cf.pnt;
		pntRaw    = cf.pntRaw;
		vec       = cf.vec;
		normal    = cf.normal;
		rValue    = cf.rValue;
		ViewPlane = cf.ViewPlane;
		geomParam = cf.geomParam;
		bPointComputed = cf.bPointComputed;

		return *this;
	}

	void reset()
	{
		type = kMcsNull;
		EntDescr.setNull();
		idObject.setNull();
		idSnappedObject.setNull();
		pnt = mcsPoint::kOrigin;
		pntRaw = mcsPoint::kOrigin;
		vec = mcsVector::kIdentity;
		normal = mcsVector::kIdentity;
		ViewPlane = mcsPlane::kXYPlane;
		rValue = 0;
		geomParam.purge();
		bPointComputed = false;
	}
};
//===========================================================================
enum EMExitWayCodeEnum
{
  kEMExitCode_LeftButtonClick      = 0x00000001,
  kEMExitCode_MiddleButtonClick    = 0x00000002,
  kEMExitCode_RightButtonClick     = 0x00000004,
  kEMExitCode_DblLeftButtonClick   = 0x00000008,
  kEMExitCode_DblMiddleButtonClick = 0x00000010,
  kEMExitCode_DblRightButtonClick  = 0x00000020,
  kEMExitCode_Enter                = 0x00000040,
  
  // you should not pass futher codes to IEntityMonitor::Init method;
  // values used only for return status from IEntityMonitor::GetEntity
  kEMExitCode_Unknown               = 0,
  kEMExitCode_TerminatedByEscape    = 0x00010000,
  kEMExitCode_TerminatedByProgram   = 0x00020000,
  kEMExitCode_TerminatedByCommand   = 0x00040000,
  kEMExitCode_TerminatedByCtxMnuCmd = 0x00080000,
};

//===========================================================================
#define OSMODE_NONE                     0x0000
#define OSMODE_ENDPOINT                 0x0001
#define OSMODE_MIDPOINT                 0x0002
#define OSMODE_CENTER                   0x0004
#define OSMODE_NODE                     0x0008
#define OSMODE_QUADRANT                 0x0010
#define OSMODE_INTERSECTION             0x0020
#define OSMODE_INSERTION                0x0040
#define OSMODE_PERPENDICULAR            0x0080
#define OSMODE_TANGENT                  0x0100
#define OSMODE_NEAREST                  0x0200
#define OSMODE_QUICK                    0x0400
#define OSMODE_APPARENT_INTERSECTION    0x0800
#define OSMODE_EXTENSION                0x1000
#define OSMODE_PARALLEL                 0x2000
#define OSMODE_OFF                      0x4000

// 3D snaps
#define _3DOSMODE_NONE       0x0000
#define _3DOSMODE_VERTEX     0x0002
#define _3DOSMODE_EDGEMID    0x0004
#define _3DOSMODE_FACECENTER 0x0008
#define _3DOSMODE_KNOT       0x0010
#define _3DOSMODE_FACEPERP   0x0020
#define _3DOSMODE_FACENEAR   0x0040

// 3D snaps for point clouds
#define _3DOSMODE_PC_NEAR       0x0080
#define _3DOSMODE_PC_SEGNEAR    0x0100
#define _3DOSMODE_PC_SEGPERP    0x0200
#define _3DOSMODE_PC_INTERSECT  0x0400
#define _3DOSMODE_PC_EDGE       0x0800
#define _3DOSMODE_PC_EDGEPERP   0x1000
#define _3DOSMODE_PC_AXIS       0x2000
#define _3DOSMODE_PC_INTERSECT3 0x4000
  
#define AUTOSNAP_NONE                   0x0000
#define AUTOSNAP_MARKER                 0x0001
#define AUTOSNAP_TOOLTIPS               0x0002
#define AUTOSNAP_MAGNET                 0x0004
#define AUTOSNAP_POLAR_TRACKING         0x0008
#define AUTOSNAP_SNAP_TRACKING          0x0010
#define AUTOSNAP_TOOLTIPS_FOR_TRACKING  0x0020

// Насильно выставляется только Magnet и Nearest, после завершения восстанавливаются только эти параметры
// Изменения внесенные во время команды остаются
#define EMPARAMS_OSMODE_NOCHANGE             0x00000000

// Osnap mode будет переопределен, после завершения монитора будут восстановлен предыдущий режим
// Изменения внесенные пользователем во время команды проигнорируются
#define EMPARAMS_OSMODE_OVERRIDE             0x00000001

// Так же как и EMPARAMS_OSMODE_OVERRIDE, но переопределяет только в том случае, если Osnap выключен
#define EMPARAMS_OSMODE_OVERRIDE_IF_EMPTY    0x00000002

// Будет показан тулбар "Направление"
#define EMPARAMS_SHOW_DIRECTION              0x00000004

// Указанные параметры будут добавлены, после завершения монитора будут восстановлен предыдущий режим
// Изменения внесенные пользователем во время команды проигнорируются
#define EMPARAMS_OSMODE_ADD                  0x00000008

// Будет возвращать трёхмерные координаты без проекции на xOy
#define EMPARAMS_3D                          0x00000010

// Флаг имеет смысл для DGW-платформ (2D)
// Если взведен, будет в цикле звать ActiveEnt для каждой энтити в апертуре,
// По молчанию сброшен. Присылаться будет тот объект, к которому произошел снап
#define EMPARAMS_CYCLE_ENTS                  0x00000020

// Не вносится никаких изменений в OSMODE и AUTOSNAP.
#define EMPARAMS_OSMODE_IGNORE               0x00000040

// флаг разрешает генерацию привязок к содержимому Xref,
// Или иначе: вызывающий код установкой этого флага как бы говорит, что он умеет работать
// с привязками к содержимому Xref
#define EMPARAMS_XREF_COMPATIBLE             0x00000080

// То же, что и EMCODE_AUTO_SELECTION, который используется в старом коде.
#define EMPARAMS_AUTO_SELECTION              0x00000100

#define EMPARAMS_3DOSMODE_NOCHANGE           0x00000000 // см. EMPARAMS_OSMODE_NOCHANGE, но это для 3D привязок
#define EMPARAMS_3DOSMODE_OVERRIDE           0x00000200 // см. EMPARAMS_OSMODE_OVERRIDE, но это для 3D привязок
#define EMPARAMS_3DOSMODE_OVERRIDE_IF_EMPTY  0x00000400 // см. EMPARAMS_OSMODE_OVERRIDE_IF_EMPTY, но это для 3D привязок
#define EMPARAMS_3DOSMODE_ADD                0x00000800 // см. EMPARAMS_OSMODE_ADD, , но это для 3D привязок

// Использовать рабочую координатную систему EM_Params::tfmCoordSystem. На её плоскость будут спроецированы все точки.
// В ней будут рассчитываться углы и прочее.
#define EMPARAMS_WORK_COORD_SYSTEM           0x00002000

//===========================================================================
struct EM_Params
{
	// TRUE - не цепляться к размерам
	bool  fExcludeDims;

	// automatic object highlighting
	bool  fHighlight;

	// combination of EMPARAMS_XXX macros
	DWORD dwFlags;

	// Osnap mask to override, LOWORD - OSMODE, HIWORD - AUTOSNAP
	// Use as 'MAKELONG(OSMODE, AUTOSNAP)'
	DWORD dwOsMode;

	// OSMODE для 3D-привязок, используется если указаны флаги EMPARAMS_3DOSMODE_xxx
	DWORD dw3dOsMode;

	// mask of mouse buttons on which IEM will return entity
	// !!! Use any combination of EMExitWayCodeEnum values
	DWORD ExitCodeMask;

	// if <true> then IEM will try to identify each highlighted entity as Mcs object
	// if <false> then IEM will work with a greater performance
	bool  fIdentifyMcsObjects;

	// true: независимо от типа снапинга возвращается примитив, к которому "прилипли
	// false: в случае снапа к End, Mid и т.п. (кроме Nearest) монитор будет
	// возвращать точку, а не примитив, к которому "прилипли"
	bool  fIgnorePoints;

	// для Инвентора... включает возможность указания вставки объектов в подсборку
	// пользователем через STD панель, где указывается и цвет вставляемых деталей
	bool  fEnableSubAsmOption; 

	// При отсутствии снапа к объекту, будет произведён поиск площадных объектов в области курсора.
	bool  fAreaSnap;

	// тип допустимых 3D объектов в зависимости от режима 3D моделирования
	// см. флаги из множества Mc3dModelingTypeEnum
	// используются, если поле 'dwFlags' содержит флаг EMPARAMS_3D
	Mc3dModelingTypeEnum e3dModelingModes;

	// Рабочая координатная система. На её плоскость будут спроецированы все точки. В ней будут
	// рассчитываться углы и прочее.
	mcsMatrix tfmCoordSystem;

	EM_Params() 
	{
		fExcludeDims   = false;
		fHighlight     = true;
		fIgnorePoints  = true;
		dwFlags        = EMPARAMS_OSMODE_NOCHANGE | EMPARAMS_3DOSMODE_NOCHANGE;
		dwOsMode       = 0;
		dw3dOsMode     = 0;
		ExitCodeMask   = kEMExitCode_LeftButtonClick; // by default exit by single left mouse button click
		fIdentifyMcsObjects = true; // by default identify each entity to detect that it is a Mcs object
		fEnableSubAsmOption = false;
		fAreaSnap      = false;
		e3dModelingModes = kMc3dModelingType_All;
	}
};

//===========================================================================

// Флаги используются в методе IEntityMonitor::SetCommands

#define EMCODE_NONULL             0x0001 // Disallow null input (Equivalent to Acad RSG_NONULL code)
#define EMCODE_NOZERO             0x0002 // Disallow zero input (Equivalent to Acad RSG_NOZERO code)
#define EMCODE_NONEG              0x0004 // Disallow negative input (Equivalent to Acad RSG_NEG code)
#define EMCODE_DASH               0x0020 // Draw dash line (Equivalent to Acad RSG_DASH code, but work correctly)
#define EMCODE_OTHER              0x0080 // Return input string if unknown (Equivalent to Acad RSG_OTHER code)
#define EMCODE_AUTO_SELECTION     0x0100 // Автоматически переключается на селекцию, если отключены оснапы
#define EMCODE_FORCE_NUMBER_INPUT 0x0200 // При вводе пользователем числа будет возврат MCS_S_COMMAND, стандартная обработка отключается.
#define EMCODE_KEEP_KEYWORDS      0x0400 // Установленные ключевые слова не будут сброшены после запроса
#define EMCODE_SEL_SINGLE_PASS    0x0800 // В режиме множественного выбора результат возвращается сразу после тычка в объект или выбора рамкой.
#define EMCODE_ALLOW_SPACES       0x1000 // При вводе текста допускаются пробелы

#define EMCODE_INPUT_DISTANCE 0x10000000// Только для внутреннего использования
#define EMCODE_INPUT_ANGLE    0x20000000// Только для внутреннего использования

//===========================================================================
struct McModificatorHint
{
	long lVirtualKey; // Virtual key (VK_MENU, VK_SHIFT, VK_CONTROL)
	McsString stHint; // Hint

	McModificatorHint()
	{
		lVirtualKey = 0;
	}
	McModificatorHint(long _lVirtualKey, LPCTSTR _stHint)
	{
		lVirtualKey = _lVirtualKey;
		stHint = _stHint;
	}
};

//===========================================================================
class McModificatorHintArray : public McsArray<McModificatorHint, const McModificatorHint&>
{
public:
	// lVirtualKey == 0 for common hint
	MECHCTL_API HRESULT GetHint(IN long lVirtualKey, OUT McsString& stHint);
	MECHCTL_API HRESULT GetHint(OUT McsString& stHint);
};

//===========================================================================
// return FALSE if message must be processed further in message loop
typedef BOOL PreTranslateMsgProc(MSG&);
struct IMcsNativeObject;
//===========================================================================
enum EMSpcFlagsEnum
{
		// в Инвенторе на GetEntity ускоряет процесс переключения ввода, если
		// используется ускоренная клиентская графика, связано это с глюками 
		// инвентора и MFC
	kEMSF_NoMFCModalDialogs = 1, 
};
//===========================================================================
struct IEntityMonitor : public IMObject
{
		// <pSink> may be NULL, in this case IEM won't call any sink and will simply get an entity after mouse click.
		// !!! see EM_Params structure for <dwExitClickMask> and <fIdentifyMcsObjects> members.
		// Be sure to use rightclick with a context menu.
	virtual HRESULT Init(IEM_Sink*  pSink,EM_Params* pParams) = 0;

	virtual HRESULT Exclude(const mcsWorkIDArray& ids) = 0;

		// If <fResetHighlightForPrevSelEnts> is true then previously selected entities aren't highlighted.
		// Check 'pExitedBy' to find out the way a monitor completed its task, in success only, (ex: by which mouse click)
		// ...
		// Returns S_OK if a point was successfully retrieved or S_FALSE if an operation was canceled.
		// For Acad, return values mean: S_OK - RTNORM, E_FAIL - RTCANCEL,
		// S_FALSE - RTNONE, MCS_S_COMMAND - RTKWORD
		// ent.EntDescr = pnt; - the first point for angle tracking
	virtual HRESULT GetEntity(
		IN LPCTSTR strPrompt,
		IN DWORD dwPreSelectEntitiesMask,
		IN OUT EM_Entity& ent,
		IN OPTIONAL DWORD dwSpecialFlags = 0,	// mixed set of flags in EMSpcFlagsEnum (see above)
		OUT OPTIONAL EMExitWayCodeEnum* pExitCode=NULL) = 0;

#define MC_GETENTITYAUTO_TRIGGER_ID 6969
#define MC_GETENTITYAUTO_TRIGGER_DEFAULT L"2;6969;-1"
#define MC_GETENTITYAUTO_INVISIBLE_TRIGGER_DEFAULT L"2;-6969;-1"
	// Выбор объекта с переключателем режимов выбор - свободно
	// Для того, чтобы переключатель режимов был параметром по умолчанию, передайте в stCommands макрос MC_GETENTITYAUTO_TRIGGER_DEFAULT
	virtual HRESULT GetEntityAuto(
		IN OUT EM_Entity& ent,
		IN OPTIONAL DWORD dwFilter = kMcsPoint,
		IN OPTIONAL LPCTSTR stPrompt = NULL,
		IN OPTIONAL LPCTSTR stParamSection = NULL,
		IN OPTIONAL DWORD dwCommands = 0,
		IN OPTIONAL LPCTSTR stCommands = NULL,
		IN OPTIONAL bool bStartModeSelection = false,
		OUT OPTIONAL bool* pbGetBySelection = NULL) = 0;

	virtual HRESULT GetAngle(IN LPCTSTR strPrompt, double& rAngle, const mcsPoint& pntBase)
		{ NOTIMPL_ALERT("IEntityMonitor::GetAngle"); }
	virtual HRESULT GetAngle(IN LPCTSTR strPrompt, double& rAngle)
		{ NOTIMPL_ALERT("IEntityMonitor::GetAngle"); }
	virtual HRESULT GetDistance(IN LPCTSTR strPrompt, double& rDistance, const mcsPoint& pntBase)
		{ NOTIMPL_ALERT("IEntityMonitor::GetDistance"); }
	virtual HRESULT GetDistance(IN LPCTSTR strPrompt, double& rDistance)
		{ NOTIMPL_ALERT("IEntityMonitor::GetDistance"); }

	virtual HRESULT SetTooltip(LPCTSTR strTooltip) = 0;
  
		// Used to support non MFC dialogs.
		// Need to support modeless dialogs while a <GetEntity> call is processed;
		// The "support" means: typical processing of TAB, ESC, ENTER keys and so on for WinForms / Win API dialogs;
		// You may call the method so many times as you need for different dialogs. They all will be examined before
		// the messages translation occurs, in the order they were registered.
		// If the second parameter is true, then the specified dialog is removed from the chain and the order
		// of the rest of dialogs will be kept
	virtual HRESULT SetCmdModelessDialog(HWND hWndDlg,bool fRemoveFromChain = false) = 0;

		// Returns a native object for preselected entity passed to ActiveEnt sink
	virtual CComPtr<IUnknown> GetNativeObject() {return UNKNULL;}
	virtual HRESULT GetNativeObject(IMcsNativeObject** ppNativeObj) = 0; // OLD MCS4 stuff, do not use

	virtual HRESULT GetApertureEntities(OUT mcsWorkIDArray& Entities) = 0; 
  
		// Returns 'true' if specified key is pressed (ForEx: VK_SHIFT or any other)
	virtual bool    IsKeyPressed(int VirtualKeyCode) = 0;
  
		// Forces a monitor to terminate it's job
	virtual HRESULT Terminate(void) = 0;

		// dwFlags - set of EMCODE_XXX flags
		// Version 1
		// Command string format
		// 1;idDefaultCommand;id1\nName1\nEngName1\n;...;id10\nName10\nEngName10\n;...
		// idDefaultCommand - id default command, this command must be defined in this string
		// id - unsigned integer number, this id will be returned in 
		//      IUniEntMonitorSink::OnContextMenuCommand and IEntityMonitor::GetCommand methods.
		//      If id == 0, then this command is ignored
		// Name - name, that will be displayed to user, will be returned in
		//        IUniEntMonitorSink::OnContextMenuCommand and IEntityMonitor::GetCommand methods
		// EngName - for Acad compatibility
		//...
		// Version 2
		// Command string format:
		// 2;idDefaultCommand;idCurrentCommand;id1/LocalName1/LatinAbbreviation1;...;idNN/LocalNameNN/LatinAbbreviationNN;...
		// idDefaultCommand - default command identifier, this command must be defined in this string.
		//     Will be visible in <> section.
		// idCurrentCommand - the current command identifier, this command must be defined in this string.
		//     This command will be visible in () section only.
		// id - integer number, command identifier, will be returned in 
		//     IUniEntMonitorSink::OnContextMenuCommand and IEntityMonitor::GetCommand methods.
		//     Only commands with positive id will be visible in [] section of command line.
		//     Id of default command may be anything and will be visible in <> section.
		//     -1 - reserved value.
		// LocalName - localized readable command name, may contain localized command abbreviation.
		//     Abbreviation - continuous sequence of uppercase letters. This sequence should be only one.
		//     LocalName can contain letters, digits, spaces and '-'. Words in keyword should be separated by spaces.
		// LatinAbbreviation - latin command abbreviation. For English is not necessary or should match
		//     with uppercase sequence in localized name.
		//
		// Version 2.1
		// Формат тот же, но теперь вместо латинской аббревиатуры следует писать полное ключевое слово, например:
		// "2;-1;-1;1/Object"
		// перевод:
		// "2;-1;-1;1/Объект/Object"
		// Аббревиатура по прежнему выделяется заглавными буквами. Все заглавные буквы в ключевом слове должны
		// идти подряд и, очень желательно, сначала ключевого слова.
	virtual HRESULT SetCommands(const DWORD dwFlags, LPCTSTR stCommands)
		{return E_NOTIMPL;}

		// Returns the last command`s data. idCommand == 0xFFFFFFFF means that a user has typed
		// a command manually (it wasn't registered with SetCommands)
		// stUserInput - the name of an entered command or, if possible, something from user
	virtual HRESULT GetCommand(OUT UINT& idCommand, OUT OPTIONAL McsString* pstUserInput = NULL)
		{return E_NOTIMPL;}

		// Выбор одной из командных опции (ключевых слов), установленных через SetCommands.
		// Допускается пользовательский ввод
		// Если вернет S_OK, результат выбора можно получить через метод  GetCommand.
	virtual HRESULT SelectKeyword(LPCTSTR strPromt)
		{return E_NOTIMPL;}

	virtual HRESULT SetModificatorsHint(IN const McModificatorHint* pHints, IN int iCount = 1)
		{return E_NOTIMPL;}

		// Выбор объектов.
		// Используется платформенная селекция (апертурой "квадратиком" вместо "прицела", без подсветки подобъектов).
		// ActiveEnt в этом случае не зовётся.
		// Работает выбор опций, установленных через SetCommands.
	virtual HRESULT SelectObject(IN LPCTSTR strPrompt, OUT mcsWorkID& id, OUT mcsPoint* pPnt = NULL, OUT McsEntityGeometry* pSimpleEnt = NULL, OUT McGeometryParam* pParam = NULL)
		{return E_NOTIMPL;}

		// Если bAllowModifyPreselection = true, предустановленная селекция не будет автоматически взята,
		// пользователь сможет её поменять.
	virtual HRESULT SelectObjects(IN LPCTSTR strPrompt, OUT mcsWorkIDArray& objects, bool bAllowModifyPreselection = false)
		{return E_NOTIMPL;}

		// Если монитор находится в режиме ввода (loop в GetEntity), то симулирует событие,
		// когда выбирается указанный объект/subent. Монитор должен обработать вызов так, будто
		// селекция происходит на самом деле. В качестве точки монитор выбирает точку на объекте
		// по любому правилу. Если fExitLoop = false, то событие равноценно простому движению мыши,
		// Если же fExitLoop = true, то после обработки указанного объекта loop в GetEinity,
		// должен разорваться и ввод должен быть прекращён, т.е. событие равноценно клику мыши.
		//
		// 16.09.2016: Параметр заменён на complexID, для поддержки селекции примитивов в блоках
		//
		// 10.06.2019: Добавлен параметр pPt, если указан, и точка проходит проверку isPointKnown,
		// то для указанного объекта будет использована данная точка.
		// никаких внутренних вычислений и валидации производиться не будет. Поэтому точка априори должна быть на объекте.
		// Если по указателю лежит неизвестная точка (isPointUnknown), то на выходе по указателю будет 
		// положена вычисленная точка.
		//
		// 18.06.2019: Добавлен параметр dwGetEntFilter, если значение отличается от дефолтного, фильтр будет использован как
		// тот, который указывается как фильтр примитивов при вызове GetEntity.
		// Параметр обязателен в случае, если симулируется ввод в монитор без вызова GetEntity.
		//
	virtual HRESULT customInput(const mcsComplexWorkID& id, bool fExitLoop, IN OUT mcsPoint* pPt = NULL, DWORD dwGetEntFilter = 0) {
		return E_NOTIMPL;
	}
	virtual HRESULT SetCursor(HCURSOR hCursor)
		{ return E_NOTIMPL; }
};
//===========================================================================
struct IUniEntMonitorSink
{
		// The second parameter allows to perform additional entities filtering.
		// Put <true> (default value) to keep entity selected (highlighted) or
		// put <false> if entity must be ignored
	virtual void ActiveEnt(const EM_Entity& ent_in,bool& fHighlight)
		{}

		// This meth is called when user clicks right mouse button.
		// If you want to show a specific context menu - pass its handle in the <hContextMenu> parameter.
		// By default, there is <NULL>, it means that a default context menu will be shown
	virtual void OnGetContextMenu(HMENU& hContextMenu) {return;}

		// Is called when a monitor has an attached context menu and a user selects any command from it.
		// If 'false' is returned, a monitor terminates, otherwise continues its work.
		// CmdId == 0xFFFFFFFF means that a user has typed a command manually
		// (it wasn't registered with SetCommands)
		// stUserInput - the name of entered command or, if possible, something from user
	virtual bool OnContextMenuCommand(UINT CmdId, LPCTSTR stUserInput) {return false;}

	virtual IMcDynamicDimensionContainer* GetDimData()
		{ return NULL; }
	virtual HRESULT SetDimValues(IN DWORD* pdwIDs, IN double* prValues, IN DWORD dwCount)
		{ return E_NOTIMPL; }
	virtual void SwitchDynDimMode()
		{}

	virtual bool SelectionAddFilter(const mcsWorkID& idToAdd)
		{ return true; }
	virtual bool SelectionRemoveFilter(const mcsWorkID& idToRemove)
		{ return true; }
};
//==================================================================================================

struct mcHitBase
{
	mcsPoint3d         pt;
	mcsVector3d        dir;
	double             dist;
	mcsMatrix          tfmW2L; // World -> Local
	mcsMatrix          tfmL2W; // Local -> World

	IMcEntityPtr       p3dMeshedEnt;

	mcsComplexWorkID   mcPath;
	McGSMarker         marker;
	McModSubentType    seType;
	int                seIndex;

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	// используются для сравнения в сортировке
	MCTYP_API static double      s_HitTol;
	MCTYP_API static mcsVector3d s_LookDir;

	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	MCTYP_API mcHitBase();
	MCTYP_API void setNull();

	MCTYP_API bool init(IMcEntity* pMeshedEnt, McGSMarker selMarker, const mcsPoint& lookPt, const mcsVector& lookDir);

	MCTYP_API bool operator == (const mcHitBase& cw) const;
	MCTYP_API bool operator > (const mcHitBase& cw) const;
	MCTYP_API bool operator < (const mcHitBase& cw) const;
};
//==================================================================================================

MCTYP_API Mc3dImagePtr mcsGet3dImageFrom3dHit(const mcHitBase& hit);

MCTYP_API const McsEntityGeometry* mcsGetGeomFor3dMeshBasedObj_ocs(
	const mcsWorkID&                idObj,
	McGSMarker                      gsm,
	OUT OPTIONAL McsEntityGeometry* pGeom_wcs = NULL);

MCTYP_API bool mcsIntersectLineAnd3dMeshEnt(
	const mcHitBase&          hit,
	const mcsLine&            viewLine_wcs,
	OUT mcsPoint3d&           intPt_wcs,
	OUT mcsVector3d&          vNormalAtIntPt_wcs,
	IN OPTIONAL const mcsTol& tol = mcsGeContext::g3dTol);

MCTYP_API bool mcsRayTest3dMeshEntity(
	IMcEntity*                     p3dMeshEnt,
	const mcsPoint&                ptRayStart,
	const mcsVector&               vRayDir,
	double                         rayRadius,
	OUT mcsPoint3dArray&           points_out,
	OUT OPTIONAL mcsVector3dArray* pNormals_out,
	OUT OPTIONAL mcsWorkIDArray*   pFaceIDs_out);

//==================================================================================================

struct mcsRayTestData
{
	MCTYP_API static mcsPoint  s_ptRayFrom;
	MCTYP_API static mcsVector s_vRayDir;

	mcsPoint  pt;
	mcsVector vec;
	mcsWorkID faceID;

	MCTYP_API double distance() const;
	MCTYP_API bool operator < (const mcsRayTestData& cw) const;
	MCTYP_API bool operator > (const mcsRayTestData& cw) const;
};
//==================================================================================================

struct mcsRayTestDataArr : McsArray<mcsRayTestData>
{
	MCTYP_API void sortAndCopyToOut(
		const mcsPoint&                ptRayStart,
		const mcsVector&               vRayDir,
		OUT mcsPoint3dArray&           points_out,
		OUT OPTIONAL mcsVector3dArray* pNormals_out,
		OUT OPTIONAL mcsWorkIDArray*   pFaceIDs_out);
};
//==================================================================================================
