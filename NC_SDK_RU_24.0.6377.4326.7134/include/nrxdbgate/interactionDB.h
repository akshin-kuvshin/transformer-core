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

#ifndef _OPENDWG_INTERACTIONDB_H__
#define _OPENDWG_INTERACTIONDB_H__
#include "nrxdbgate_impexp.h"

class NcEdSubSelectFilter;
class HostEdInputPointManager;
class HostEdInputContextReactor;
class HostEdInputPointFilter;
class HostEdInputPointMonitor;
class NcApDocument;
class NcEdInputContextReactor;
class NcEdInputPoint;
class NcEdInputPointFilter;
class NcEdInputPointFilterResult;
class NcEdInputPointMonitor;
class NcEdInputPointMonitorResult;


// typedef NcArray<NcDbIntArray, NcArrayObjectCopyReallocator<NcDbIntArray> > 
//  NcDbArrayIntArray; 
// moved to interactionHost.h in NrxHostGate
// 
// typedef void (WINAPI* NcEdColorDialogCallbackFunction)(void *pCallbackData, const NcCmColor& newColor);
// moved to interactionHost.h in NrxHostGate
//namespace NcEdSSGet moved to interactionHost.h in NrxHostGate

//namespace NcEdSymbolUtilities moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSymbolUtilities:Services moved to interactionHost.h in NrxHostGate

//enum DimstyleTabSuppressed moved to interactionHost.h in NrxHostGate
 
//enum BlockEditModeFlags moved to interactionHost.h in NrxHostGate
 
//enum NcEdViewCubePart moved to interactionHost.h in NrxHostGate

//enum NcHatchNotifier moved to interactionHost.h in NrxHostGate

//enum NcHatchEdReact moved to interactionHost.h in NrxHostGate

//enum NcEdCommandStatusFlags moved to interactionHost.h in NrxHostGate

//struct PROMPT_MAP_ENTRY  moved to interactionHost.h in NrxHostGate

//struct NcColorSettings moved to interactionHost.h in NrxHostGate

//struct NcColorSettingsEx moved to interactionHost.h in NrxHostGate

//struct NcColorSettingsEx2 moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdJig moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPointManager
class NRXDBGATE_EXPORT NcEdInputPointManager
{
public:
	NcEdInputPointManager(HostEdInputPointManager* _object);
	virtual ~NcEdInputPointManager() {}

public:
	virtual Nano::ErrorStatus registerPointFilter(NcEdInputPointFilter* filter);
	virtual Nano::ErrorStatus revokePointFilter();

	virtual NcEdInputPointFilter* currentPointFilter() const;

	virtual Nano::ErrorStatus addPointMonitor(NcEdInputPointMonitor* monitor);
	virtual Nano::ErrorStatus removePointMonitor(NcEdInputPointMonitor* monitor);

	virtual Nano::ErrorStatus addInputContextReactor(NcEdInputContextReactor* reactor);
	virtual Nano::ErrorStatus removeInputContextReactor(NcEdInputContextReactor* reactor);

	virtual Nano::ErrorStatus disableSystemCursorGraphics();
	virtual Nano::ErrorStatus enableSystemCursorGraphics();

	virtual int systemCursorDisableCount() const;

	virtual Nano::ErrorStatus turnOnForcedPick();
	virtual Nano::ErrorStatus turnOffForcedPick();

	virtual int forcedPickCount() const;

	virtual int mouseHasMoved() const;

	virtual Nano::ErrorStatus turnOnSubentityWindowSelection();
	virtual Nano::ErrorStatus turnOffSubentityWindowSelection();

	virtual Nano::ErrorStatus addSubSelectFilter(NcEdSubSelectFilter* filter);
	virtual Nano::ErrorStatus removeSubSelectFilter(NcEdSubSelectFilter* filter);

public:
	HostEdInputPointManager* native() const
	{
		return (HostEdInputPointManager*)m_pNative;
	}

protected:
	HostEdInputPointManager* m_pNative;
	NcEdInputPointFilter* m_pFilter;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPointFilter
class NRXDBGATE_EXPORT NcEdInputPointFilter : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcEdInputPointFilter);

public:
	NcEdInputPointFilter();
	virtual ~NcEdInputPointFilter();

public:
	virtual Nano::ErrorStatus processInputPoint(bool& is_point_changed, NcGePoint3d& point, bool& display_osnap,
	                                            bool& is_tooltip_changed, NCHAR*& tooltip, bool& retry,
	                                            NcGiViewportDrawNrx* context, NcApDocument* document,
	                                            bool is_point_computed, int history,const NcGePoint3d& last,
	                                            const NcGePoint3d& raw, const NcGePoint3d& gripped,
	                                            const NcGePoint3d& snapped, const NcGePoint3d& osnapped,
	                                            NcDb::OsnapMask mask,
	                                            const NcArray< NcDbCustomOsnapMode* >& custom_osnap,
	                                            NcDb::OsnapMask custom_mask,
	                                            const NcArray< NcDbCustomOsnapMode* >& osnap_overrides,
	                                            const NcArray< NcDbObjectId >& entities,
	                                            const NcArray< NcDbObjectIdArray,
	                                                           NcArrayObjectCopyReallocator< NcDbObjectIdArray > >& nested_entities,
	                                            const NcArray< NRX::GsMarker >& marker,
	                                            const NcArray< NcDbObjectId >& key_point_entities,
	                                            const NcArray< NcDbObjectIdArray,
	                                                           NcArrayObjectCopyReallocator< NcDbObjectIdArray > >& nested_key_point_entities,
	                                            const NcArray< NRX::GsMarker >& key_point_markers,
	                                            const NcArray< NcGeCurve3d* >& alignment_paths,
	                                            const NcGePoint3d& effective_point, const NCHAR* default_tooltip);

	virtual Nano::ErrorStatus processInputPoint(const NcEdInputPoint& input, NcEdInputPointFilterResult& output);

	virtual NcEdInputPointFilter* revokeInputFilter(NcEdInputPointFilter* revokedFilter)
	{
		return this;
	}

public:
	inline HostEdInputPointFilter* native() const
	{
		return (HostEdInputPointFilter*)m_pNative;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPointMonitor
class NRXDBGATE_EXPORT NcEdInputPointMonitor : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcEdInputPointMonitor);

public:
	NcEdInputPointMonitor();

public:
	virtual ~NcEdInputPointMonitor();

public:
	virtual Nano::ErrorStatus monitorInputPoint(bool& append_tooltip, NCHAR*& tooltip, NcGiViewportDrawNrx* context,
	                                            NcApDocument* document, bool is_computed, int history,
	                                            const NcGePoint3d& last, const NcGePoint3d& raw,
	                                            const NcGePoint3d& gripped, const NcGePoint3d& snapped,
	                                            const NcGePoint3d& osnapped, NcDb::OsnapMask mask,
	                                            const NcArray< NcDbCustomOsnapMode* >& custom_osnap,
	                                            NcDb::OsnapMask osnap_overrides,
	                                            const NcArray< NcDbCustomOsnapMode* >& custom_osnap_overrides,
	                                            const NcArray< NcDbObjectId >& aperture_entities,
	                                            const NcArray< NcDbObjectIdArray,
	                                                           NcArrayObjectCopyReallocator< NcDbObjectIdArray > >& nested_aperture_entities,
	                                            const NcArray< NRX::GsMarker >& markers,
	                                            const NcArray< NcDbObjectId >& key_point_entities,
	                                            const NcArray< NcDbObjectIdArray,
	                                                           NcArrayObjectCopyReallocator< NcDbObjectIdArray > >& nested_key_point_entities,
	                                            const NcArray< NRX::GsMarker >& keyPointGsSelectionMark,
	                                            const NcArray< NcGeCurve3d* >& alignmentPaths,
	                                            const NcGePoint3d& computed, const NCHAR* default_tooltip);

	virtual Nano::ErrorStatus monitorInputPoint(const NcEdInputPoint& input, NcEdInputPointMonitorResult& output);

	virtual bool excludeFromOsnapCalculation(const NcArray< NcDbObjectId >& nested_entity, int marker)
	{
		return false;
	}

public:
	inline HostEdInputPointMonitor* native() const
	{
		return (HostEdInputPointMonitor*)m_pNative;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputContextReactor
class NRXDBGATE_EXPORT NcEdInputContextReactor
{
public:
	NcEdInputContextReactor();
	virtual ~NcEdInputContextReactor();

	virtual void beginGetPoint(const NcGePoint3d* in, const NCHAR* prompt, int initGetFlags, const NCHAR* keywords) {}
	virtual void endGetPoint(Nano::PromptStatus returnStatus, const NcGePoint3d& pointOut, const NCHAR*& keyword) {}

	virtual void beginGetAngle(const NcGePoint3d* in, const NCHAR* prompt, int initGetFlags, const NCHAR* keywords) {}
	virtual void endGetAngle(Nano::PromptStatus returnStatus, double& angle, const NCHAR*& keyword) {}

	virtual void beginGetDistance(const NcGePoint3d* in, const NCHAR* prompt, int initGetFlags,
	                              const NCHAR* keywords) {}
	virtual void endGetDistance(Nano::PromptStatus returnStatus, double& distance, const NCHAR*& keyword) {}

	virtual void beginGetOrientation(const NcGePoint3d* in, const NCHAR* prompt, int initGetFlags,
	                                 const NCHAR* keywords) {}
	virtual void endGetOrientation(Nano::PromptStatus returnStatus, double& angle, const NCHAR*& keyword) {}

	virtual void beginGetCorner(const NcGePoint3d* firstCorner, const NCHAR* prompt, int initGetFlags,
	                            const NCHAR* keywords) {}
	virtual void endGetCorner(Nano::PromptStatus returnStatus, NcGePoint3d& secondCorner, const NCHAR*& keyword) {}

	virtual void beginGetScaleFactor(const NcGePoint3d* in, const NCHAR* prompt, int initGetFlags,
	                                 const NCHAR* keywords) {}
	virtual void endGetScaleFactor(Nano::PromptStatus returnStatus, double& distance, const NCHAR*& keyword) {}

	virtual void beginGetString(const NCHAR* prompt, int initGetFlags) {}
	virtual void endGetString(Nano::PromptStatus returnStatus, NCHAR* pString) {}

	virtual void beginGetKeyword(const NCHAR* prompt, int initGetFlags, const NCHAR* keywords) {}
	virtual void endGetKeyword(Nano::PromptStatus returnStatus, const NCHAR*& keyword) {}

	virtual void beginGetInteger(const int* default, const NCHAR* prompt, int initGetFlags, const NCHAR* keywords) {}

	virtual void endGetInteger(Nano::PromptStatus returnStatus, int& retValue, const NCHAR*& keyword) {}

	virtual void beginGetColor(const int* dfault, const NCHAR* prompt, int initGetFlags, const NCHAR* keywords) {}
	virtual void endGetColor(Nano::PromptStatus returnStatus, int& retValue, const NCHAR*& keyword) {}

	virtual void beginGetReal(const double* dfault, const NCHAR* prompt, int initGetFlags, const NCHAR* keywords) {}
	virtual void endGetReal(Nano::PromptStatus returnStatus, double& returnValue, const NCHAR*& keyword) {}

	virtual void beginEntsel(const NCHAR* prompt, int initGetFlags, const NCHAR* keywords) {}
	virtual void endEntsel(Nano::PromptStatus returnStatus, NcDbObjectId& entity, NcGePoint3d& pick,
	                       const NCHAR* keyword) {}

	virtual void beginNentsel(const NCHAR* prompt, NRX::Boolean pickFlag, int initGetFlags,
	                          const NCHAR* keywords) {}
	virtual void endNentsel(Nano::PromptStatus returnStatus, NcDbObjectId entity, const NcGePoint3d& pick,
	                        const NcGeMatrix3d& xform, const resbuf* reference_stack, const NCHAR* keyword) {}

	virtual void beginSSGet(const NCHAR* prompt, int initGetFlags, const NCHAR* keywords, const NCHAR* controls,
	                        const NcArray< NcGePoint3d >& points, const resbuf* mask) {}
	virtual void endSSGet(Nano::PromptStatus returnStatus, const NcArray< NcDbObjectId >& selection_set) {}

	virtual void beginDragSequence(const NCHAR* prompt) {}
	virtual void endDragSequence(Nano::PromptStatus returnStatus, NcGePoint3d& pick, NcGeVector3d& vector) {}

	virtual void beginQuiescentState() {}
	virtual void endQuiescentState() {}

public:
	NcEdInputContextReactor(HostEdInputContextReactor*);

	inline HostEdInputContextReactor* native() const
	{
		return (HostEdInputContextReactor*)m_pNative;
	}

public:
	HostEdInputContextReactor* m_pNative;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPoint
class NRXDBGATE_EXPORT NcEdInputPoint
{
public:
	NcApDocument* document() const;
	bool pointComputed() const;
	int history() const;
	const NcGePoint3d& lastPoint() const;
	const NcGePoint3d& rawPoint() const;
	const NcGePoint3d& grippedPoint() const;
	const NcGePoint3d& cartesianSnappedPoint() const;
	const NcGePoint3d& osnappedPoint() const;
	const NcDb::OsnapMask osnapMask() const;
	const NcArray< NcDbCustomOsnapMode* >& customOsnapModes() const;
	const NcDb::OsnapMask osnapOverrides() const;
	const NcArray< NcDbCustomOsnapMode* >& customOsnapOverrides() const;
	const NcArray< NcDbObjectId >& pickedEntities() const;
	const NcArray< NcDbObjectIdArray, NcArrayObjectCopyReallocator<NcDbObjectIdArray>>& nestedPickedEntities() const;
	const NcArray< NRX::GsMarker >& gsSelectionMark() const;
	const NcArray< NcDbObjectId >& keyPointEntities() const;

	const NcArray< NcDbObjectIdArray, NcArrayObjectCopyReallocator< NcDbObjectIdArray > >& nestedKeyPointEntities() const;

	const NcArray< NRX::GsMarker >& keyPointGsSelectionMark() const;
	const NcArray< NcGeCurve3d* >& alignmentPaths() const;
	const NcGePoint3d& computedPoint() const;
	const NCHAR* tooltipString() const;
	NcGiViewportDrawNrx* drawContext() const;

	void setParameters(NcGiViewportDrawNrx* context, NcApDocument* document, bool is_computed,
	                   int history, const NcGePoint3d& last, const NcGePoint3d& raw, const NcGePoint3d& gripped,
	                   const NcGePoint3d& snapped, const NcGePoint3d& osnapped, NcDb::OsnapMask mask,
	                   const NcArray< NcDbCustomOsnapMode* >& custom_osnap, NcDb::OsnapMask osnap_overrides,
	                   const NcArray< NcDbCustomOsnapMode* >& custom_osnap_overrides,
	                   const NcArray< NcDbObjectId >& aperture_entities,
	                   const NcArray< NcDbObjectIdArray,
	                                  NcArrayObjectCopyReallocator< NcDbObjectIdArray > >& nested_aperture_entities,
	                   const NcArray< NRX::GsMarker >& markers, const NcArray< NcDbObjectId >& key_point_entities,
	                   const NcArray< NcDbObjectIdArray,
	                                  NcArrayObjectCopyReallocator< NcDbObjectIdArray > >& nested_key_point_entities,
	                   const NcArray< NRX::GsMarker >& keyPointGsSelectionMark, const NcArray< NcGeCurve3d* >& alignmentPaths,
	                   const NcGePoint3d& computed, const NCHAR* default_tooltip);


private:

	NcApDocument*                   m_pDocument;
	bool                            m_bPointComputed;
	int                             m_nHistory;
	NcGePoint3d                     m_pntLastPoint;
	NcGePoint3d                     m_pntRawPoint;
	NcGePoint3d                     m_pntGrippedPoint;
	NcGePoint3d                     m_pntCartesianSnappedPoint;
	NcGePoint3d                     m_pntOsnappedPoint;

	NcDb::OsnapMask                 m_eOsnapMask;
	NcArray< NcDbCustomOsnapMode* > m_arrCustomOsnapModes;
	NcDb::OsnapMask                 m_eOsnapOverrides;
	NcArray< NcDbCustomOsnapMode* > m_arrCustomOsnapOverrides;
	NcArray< NcDbObjectId >         m_arrPickedEntities;
	NcArray< NcDbObjectIdArray, NcArrayObjectCopyReallocator< NcDbObjectIdArray > > m_arrNestedPickedEntities;

	NcArray< NRX::GsMarker >   m_eGsSelectionMark;
	NcArray< NcDbObjectId >         m_arrKeyPointEntities;

	NcArray< NcDbObjectIdArray, NcArrayObjectCopyReallocator< NcDbObjectIdArray > > m_arrNestedKeyPointEntities;

	NcArray< NRX::GsMarker >   m_arrKeyPointGsSelectionMark;

	NcArray< NcGeCurve3d* >         m_arrAlignmentPaths;

	NcGePoint3d                     m_pntComputedPoint;
	NcString                        m_strTooltipString;
	NcGiViewportDrawNrx*            m_pDrawContext;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPointMonitorResult
class NRXDBGATE_EXPORT NcEdInputPointMonitorResult
{
public:
	NcEdInputPointMonitorResult();

	void setAdditionalTooltipString(const NCHAR* strTooltipString);

	bool appendToTooltipStr() const;
	const NCHAR* additionalTooltipString() const;

private:
	NcString m_strAdditionalTooltipString;
	bool     m_bAppendToTooltipStr;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcEdInputPointFilterResult
class NRXDBGATE_EXPORT NcEdInputPointFilterResult
{
public:
	NcEdInputPointFilterResult();

	void setNewPoint(const NcGePoint3d& newValue);
	void setDisplayOsnapGlyph(bool newValue);
	void setNewTooltipString(const NCHAR* newValue);
	void setRetry(bool newValue);

	const NcGePoint3d& newPoint() const;
	bool displayOsnapGlyph() const;
	const NCHAR* newTooltipString() const;
	bool retry() const;

	bool isPointChanged() const;
	bool isTooltipChanged() const;

private:
	NcGePoint3d m_pntNewPoint;
	bool        m_bDisplayOsnapGlyph;
	NcString    m_strNewTooltipString;
	bool        m_bRetry;
	bool        m_bIsPointChanged;
	bool        m_bIsTooltipChanged;
};
// AutoGen:

//////////////////////////////////////////////////////////////////////////
// NcEdCommandEventArgs moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdCommandReactor moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdCommandStackReactor moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdServices moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSolidSubentitySelector moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSelectedTransient moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSteeringWheel moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSteeringWheelReactor moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdViewCube moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdViewCubeReactor moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcLyRelExpr
class NcLyRelExpr {
public:
	virtual const NCHAR * getVariable() const = 0;
	virtual const NCHAR * getConstant() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcLyAndExpr
class NcLyAndExpr {
public:
	virtual ~NcLyAndExpr() { }
	virtual const NcArray<NcLyRelExpr*>& getRelExprs() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcLyBoolExpr
class NcLyBoolExpr {
public:
	virtual ~NcLyBoolExpr() { }
	virtual const NcArray<NcLyAndExpr*>& getAndExprs() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcEdSelectionSetService moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSSGetFilter moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSSGetFilter2 moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSSGetFilter3 moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSSGetFilter4 moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSubSelectFilterService moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSSGetSubSelectFilter moved to interactionHost.h in NrxHostGate

//////////////////////////////////////////////////////////////////////////
// NcEdSubSelectFilter
class NcEdSubSelectFilter {
public:
	enum SubSelectStatus
	{
		kSubSelectionNone = 0,
		kSubSelectionAugment,
		kSubSelectionExclusive,
		kSubSelectAll
	};
	virtual Nano::ErrorStatus subSelectClassList(NcArray<NcRxClass*>& clsIds)
	{ return Nano::eOk; }
	virtual bool selectEntity(
	        const NcGePoint3d&  wvpt,
	        const NcGeVector3d& wvwdir,
	        const NcGeVector3d& wvwxdir,
	        double              wxaper,
	        double              wyaper,
	        long                flags,
	        const NcGiViewport* pCurVp,
	        NcDbEntity*         pEnt) const
	{ return false; }
	virtual SubSelectStatus subSelectEntity(
	        const NcGePoint3d&        wpt1,
	        const NcGePoint3d&        wpt2,
	        const NcGeVector3d&       wvwdir,
	        const NcGeVector3d&       wvwxdir,
	        double                    wxaper,
	        double                    wyaper,
	        NcDb::SelectType          seltype,
	        bool                      bAugment,
	        bool                      bIsInPickfirstSet,
	        bool                      bEvery,
	        const NcGiViewport*       pCurVP,
	        NcDbEntity*               pEnt,
	        NcDbFullSubentPathArray&  paths)
	{ return kSubSelectionNone; }
	virtual SubSelectStatus subSelectEntity(
	        const resbuf*             pResbuf,
	        bool                      bAugment,
	        bool                      bIsInPickfirstSet,
	        bool                      bEvery,
	        const NcGiViewport*       pCurVP,
	        NcDbEntity*               pEnt,
	        NcDbFullSubentPathArray&  paths)
	{ return kSubSelectionNone; }
	virtual bool reSubSelectEntity(NcDbEntity* pEnt,
	                               NcDbFullSubentPathArray& paths)
	{ return false; }
	virtual bool cancelSubSelect(NcDbEntity* pEnt)
	{ return false; }
	virtual bool cancelAllSubSelect()
	{ return false; }
	virtual bool onKey(unsigned long wMsg, unsigned int nChar,
	                   unsigned int rptCnt, unsigned int flags)
	{ return false; }
	virtual bool isSubSelected(NcDbEntity* pEnt) const
	{ return false; }
};

////////////////////////////////////////////////////////////////////////
// NcEdXrefFileLock  moved to interactionHost.h in NrxHostGate


// AutoGen.

// ncedCompareToCurrentViewport moved to interactionHost.h in NrxHostGate

//ncedCreateInternetShortcut moved to interactionHost.h in NrxHostGate

// ncedCreateSteeringWheel moved to interactionHost.h in NrxHostGate

// ncedCreateViewCube moved to interactionHost.h in NrxHostGate
// ncedDestroySteeringWheel moved to interactionHost.h in NrxHostGate
// ncedDestroyViewCube moved to interactionHost.h in NrxHostGate
// ncedDisableDefaultARXExceptionHandler moved to interactionHost.h in NrxHostGate
// ncedDisableUsrbrk moved to interactionHost.h in NrxHostGate
// ncedEditDimstyleInteractiveEx moved to interactionHost.h in NrxHostGate
// ncedEnableUsrbrk moved to interactionHost.h in NrxHostGate
 
// ncedGetAnimationFrameId moved to interactionHost.h in NrxHostGate
// ncedGetBlockEditMode moved to interactionHost.h in NrxHostGate

// ncedGetCommandVersion moved to interactionHost.h in NrxHostGate
// ncedGetCurVportCircleSides( moved to interactionHost.h in NrxHostGate
// ncedGetCurVportPixelToDisplay moved to interactionHost.h in NrxHostGate
// ncedGetCurVportScreenToDisplay moved to interactionHost.h in NrxHostGate
// ncedGetUnitsConversion moved to interactionHost.h in NrxHostGate

// ncedGetUserFavoritesDir moved to interactionHost.h in NrxHostGate

// ncedHideConstraintBar moved to interactionHost.h in NrxHostGate

// ncedInitCommandVersion moved to interactionHost.h in NrxHostGate

// ncedInitDialog moved to interactionHost.h in NrxHostGate
// ncedIsInBackgroundMode moved to interactionHost.h in NrxHostGate
// ncedIsUsrbrkDisabled moved to interactionHost.h in NrxHostGate

// ncedManageHatchEditorReactor moved to interactionHost.h in NrxHostGate

// ncedOpenDocWindowsMinimized moved to interactionHost.h in NrxHostGate

// ncedResolveInternetShortcut moved to interactionHost.h in NrxHostGate

// ncedResolveShortcut moved to interactionHost.h in NrxHostGate

// ncedSelectTransients moved to interactionHost.h in NrxHostGate

// ncedSetXrefResolvedWithUpdateStatus moved to interactionHost.h in NrxHostGate

// ncedShowConstraintBar moved to interactionHost.h in NrxHostGate

// ncedShowConstraintBarForAll moved to interactionHost.h in NrxHostGate

// ncedSkipXrefNotification moved to interactionHost.h in NrxHostGate
// ncedSSSetSubentTypes moved to interactionHost.h in NrxHostGate
// ncedSSSubentDel moved to interactionHost.h in NrxHostGate
// ncedSSSubentMemb moved to interactionHost.h in NrxHostGate
// ncedSSSubentName moved to interactionHost.h in NrxHostGate
// ncedSSSubentNameX moved to interactionHost.h in NrxHostGate

// ncedSSSubentLength moved to interactionHost.h in NrxHostGate

// ncedTraceBoundary moved to interactionHost.h in NrxHostGate

// ncedVPLayer moved to interactionHost.h in NrxHostGate

// ncedXrefNotifyCheckFileChanged moved to interactionHost.h in NrxHostGate

// ncedGetCurrentColorsEx moved to interactionHost.h in NrxHostGate
// ncedGetCurrentColorsEx2 moved to interactionHost.h in NrxHostGate
// ncedGetSystemColorsEx moved to interactionHost.h in NrxHostGate
// ncedGetSystemColorsEx2 moved to interactionHost.h in NrxHostGate
// ncedSetCurrentColorsEx moved to interactionHost.h in NrxHostGate
// ncedSetCurrentColorsEx2 moved to interactionHost.h in NrxHostGate

// ncedGetApplicationFrame moved to interactionHost.h in NrxHostGate
// ncedRegisterMainFramePreTranslateObserver moved to interactionHost.h in NrxHostGate
// ncedRegisterOnModal moved to interactionHost.h in NrxHostGate
// ncedRemoveMainFramePreTranslateObserver moved to interactionHost.h in NrxHostGate
// ncedRemoveOnModal moved to interactionHost.h in NrxHostGate

// addSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// duplicateSelectionsAllowed moved to interactionHost.h in NrxHostGate

// setAllowDuplicateSelection moved to interactionHost.h in NrxHostGate

// ncedCreateInternetShortcut moved to interactionHost.h in NrxHostGate
// ncedGetUserFavoritesDir moved to interactionHost.h in NrxHostGate
// ncedResolveInternetShortcut moved to interactionHost.h in NrxHostGate
// ncedResolveShortcut moved to interactionHost.h in NrxHostGate

// ncedCreateShortcut moved to interactionHost.h in NrxHostGate
// ncedSetColorDialogTrueColorWithCallback moved to interactionHost.h in NrxHostGate
// addSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// addSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// addSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// addSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// addSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// removeSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// removeSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// removeSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// removeSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// removeSSgetFilterInputContextReactor moved to interactionHost.h in NrxHostGate
// typedef NcEdSymbolUtilities::Services NcEdSymUtilServices moved to interactionHost.h in NrxHostGate
// ncedSymUtil moved to interactionHost.h in NrxHostGate
#endif // _OPENDWG_INTERACTIONDB_H__
