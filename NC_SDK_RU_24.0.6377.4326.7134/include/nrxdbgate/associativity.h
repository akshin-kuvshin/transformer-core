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

#ifndef __ASSOCIATIVITY_H__
#define __ASSOCIATIVITY_H__
#include "nrxdbgate_impexp.h"
class NcDbAssocAction;
class NcDbAssocActionBody;
class NcDbAssocNetwork;
class NcDbAssocDependency;
class NcDbAssocDependencyBody;
class NcDbAssocGeomDependency;
class NcDbAssoc2dConstraintGroup;
class NcDbAssocPersSubentId;
class NcDbAssocSimplePersSubentId;
class NcDbAssocSingleEdgePersSubentId;
class NcDbAssocPersSubentIdPE;
class NcDbAssocVariable;
class NcDbAssocValueDependency;
class NcDbAssocValueProviderPE;
class NcDbEvalContext;
class NcDbAssocPersSubentManager;
class NcDbAssocPersSubentManagerPE;
class NcDbAssocPersSubentManagerCloner;
class NcDbAssocNotificationData;

class NcDbAssocEvaluationCallback;

namespace PersSubentNaming
{
	class AnnotationData;
	class PersSubentManager;
}

class ENTITY;
class COEDGE;
class EDGE;
class LOOP;
class FACE;
class SHELL;
class LUMP;
class BODY;
typedef NcArray<BODY*>            NcDbAsmBodyArray;
typedef NcArray<ENTITY*>          NcDbAsmEntityArray;
typedef NcArray<EDGE*>            NcDbAsmEdgeArray;
typedef NcArray<FACE*>            NcDbAsmFaceArray;
typedef NcArray<NcDbAsmEdgeArray> NcDbAsmEdgeArray2d;

enum NcDbAssocStatus
{
	kIsUpToDateAssocStatus = 0,
	kChangedDirectlyAssocStatus,
	kChangedTransitivelyAssocStatus,
	kChangedNoDifferenceAssocStatus,
	kFailedToEvaluateAssocStatus,
	kErasedAssocStatus,
	kSuppressedAssocStatus,
};

NRXDBGATE_EXPORT int evaluationRequestSeverityLevel(NcDbAssocStatus status);
NRXDBGATE_EXPORT bool isEvaluationRequest(NcDbAssocStatus status);
NRXDBGATE_EXPORT bool isToBeSkipped(NcDbAssocStatus status);

enum NcDbAssocEvaluationPriority
{
	kCannotBeEvaluatedAssocEvaluationPriority = -1000,
	kCannotDermineAssocEvaluationPriority = 0,
	kCanBeEvaluatedAssocEvaluationPriority = 1000,
};

enum NcDbAssocEvaluationMode
{
	kModifyObjectsAssocEvaluationMode,
	kModifyActionAssocEvaluationMode,
};

enum NcDbAssocDraggingState
{
	kNotDraggingAssocDraggingState,
	kFirstSampleAssocDraggingState,
	kIntermediateSampleAssocDraggingState,
	kLastSampleAssocDraggingState,
};

enum NcDbAssocTransformationType
{
	kNotSpecified,
	kStretch,
	kRotate,
	kMove,
};

enum NRXDBGATE_EXPORT NcDbAssocCreateImpObject
{
	kNcDbAssocCreateImpObject = 0,
	kNcDbAssocDoNotCreateImpObject = 1,
};

enum NcDbAssocConstraintType
{
	kNoneAssocConstraintType = 0,
	kDistanceAssocConstraintType,
	kHorizontalDistanceAssocConstraintType,
	kVerticalDistanceAssocConstraintType,
	kAngle0AssocConstraintType, 
	kAngle1AssocConstraintType,
	kAngle2AssocConstraintType,
	kAngle3AssocConstraintType,
	kRadiusAssocConstraintType,
	kDiameterAssocConstraintType,
};

typedef unsigned                       NcDbPersElemId;
typedef NcDbPersElemId                 NcDbPersStepId;
typedef NcDbPersElemId                 NcDbPersSubentId;
typedef NcArray<NcDbPersElemId>        NcDbPersElemIdArray;
typedef NcArray<NcDbPersStepId>        NcDbPersStepIdArray;
typedef NcArray<NcDbPersSubentId>      NcDbPersSubentIdArray;
typedef NcArray<NcDbPersElemIdArray>   NcDbPersElemIdArray2d;

const NcDbPersElemId kNcDbPersNullId = 0;

NRXDBGATE_EXPORT NcString& dummyString();
NRXDBGATE_EXPORT void stringDefaultArgumentTest(NcString& str = dummyString());

//////////////////////////////////////////////////////////////////////////
// NcDbActionsToEvaluateCallback
class NRXDBGATE_EXPORT NcDbActionsToEvaluateCallback {
public:
	NcDbActionsToEvaluateCallback() {}
	virtual ~NcDbActionsToEvaluateCallback() {}
	virtual void needsToEvaluate(const NcDbObjectId& objectId,
	                             NcDbAssocStatus     newStatus,
	                             bool                ownedActionsAlso = true) = NULL;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocAction
class NRXDBGATE_EXPORT NcDbAssocAction : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocAction);
	explicit NcDbAssocAction(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	NcDbObjectId actionBody() const;
	static NcDbObjectId actionBody(const NcDbObjectId& actionId);
	Nano::ErrorStatus setActionBody(const NcDbObjectId& actionBodyId);
	bool isActionBodyAProxy() const;
	NcDbAssocStatus status() const;
	Nano::ErrorStatus setStatus(NcDbAssocStatus newStatus,
	                            bool            notifyOwningNetwork = true,
	                            bool            setInOwnedActions   = false);
	NcDbObjectId owningNetwork() const;
	Nano::ErrorStatus setOwningNetwork(const NcDbObjectId& networkId, bool alsoSetAsDatabaseOwner);
	Nano::ErrorStatus getDependencies(bool readDependenciesWanted,
	                                  bool writeDependenciesWanted,
	                                  NcDbObjectIdArray& dependencyIds) const;
	Nano::ErrorStatus addDependency(const NcDbObjectId& dependencyId,
	                                bool                setThisActionAsOwningAction = true);
	Nano::ErrorStatus removeDependency(const NcDbObjectId& dependencyId,
	                                   bool                alsoEraseIt);
	Nano::ErrorStatus removeAllDependencies(bool alsoEraseThem);
	Nano::ErrorStatus getDependentObjects(bool readDependenciesWanted,
	                                      bool writeDependenciesWanted,
	                                      NcDbObjectIdArray& objectIds) const;
	bool isOwnedDependency(const NcDbAssocDependency* pDependency) const;
	bool isExternalDependency(const NcDbAssocDependency* pDependency) const;
	bool isRelevantDependencyChange(const NcDbAssocDependency* pDependency) const;
	bool hasDependencyCachedValue(const NcDbAssocDependency* pDependency) const;
	bool areDependenciesOnTheSameThing(const NcDbAssocDependency* pDependency1,
	                                   const NcDbAssocDependency* pDependency2) const;
	bool areDependenciesEqual(const NcDbAssocDependency* pDependency1,
	                          const NcDbAssocDependency* pDependency2) const;
	Nano::ErrorStatus notification(NcDbAssocNotificationData* pNotifData);
	void dependentObjectCloned(const NcDbAssocDependency* pDependency,
	                           const NcDbObject*          pDbObj,
	                           const NcDbObject*          pNewObj);
	Nano::ErrorStatus addMoreObjectsToDeepClone(NcDbIdMapping& idMap,
	                                            NcDbObjectIdArray& additionalObjectsToClone) const;
	Nano::ErrorStatus postProcessAfterDeepClone(NcDbIdMapping& idMap);
	Nano::ErrorStatus postProcessAfterDeepCloneCancel(NcDbIdMapping& idMap);
	bool isActionEvaluationInProgress() const;
	NcDbAssocEvaluationCallback* currentEvaluationCallback() const;
	Nano::ErrorStatus evaluateDependencies();
	void evaluateDependency(NcDbAssocDependency* pDependency);
	Nano::ErrorStatus ownedDependencyStatusChanged(NcDbAssocDependency* pOwnedDependency,
	                                               NcDbAssocStatus      previousStatus);
	Nano::ErrorStatus transformActionBy(const NcGeMatrix3d& transform);
	bool isEqualTo(const NcDbAssocAction* pOtherAction) const;
	NcDbAssocEvaluationPriority evaluationPriority() const;
	void getDependentActionsToEvaluate(NcDbActionsToEvaluateCallback* pActionsToEvaluateCallback) const;
	void evaluate(NcDbAssocEvaluationCallback* pEvaluationCallback);
	NcDbObjectId objectThatOwnsNetworkInstance() const;
	void dragStatus(const NcDb::DragStat status);
	static Nano::ErrorStatus getActionsDependentOnObject(const NcDbObject* pObject,
	                                                     bool readDependenciesWanted,
	                                                     bool writeDependenciesWanted,
	                                                     NcDbObjectIdArray& actionIds);
	static Nano::ErrorStatus removeActionsControllingObject(
	    const NcDbObjectId& objectToRemoveActionsFrom,
	    int                 readOnlyDependencyHandling = 0,
	    const NcDbObjectId& objectToRedirectReadOnlyDependenciesTo = NcDbObjectId::kNull);
	static Nano::ErrorStatus markDependentActionsToEvaluate(const NcDbObjectId& actionId);
	static bool doesObjectHaveActiveActions(const NcDbObject* pObject);
};


//////////////////////////////////////////////////////////////////////////
// NcAutoConstrainEvaluationCallback
class NRXDBGATE_EXPORT NcAutoConstrainEvaluationCallback {
	friend class NcAutoConstraintEvalManager;
public:
	virtual void getConstraintPriorityOverride(NcGeomConstraint::GeomConstraintType type,
	                                           const NcArray<const NcConstrainedGeometry*>& geometries, int& priority) const
	{
		return;
	}
	virtual void getAutoConstrainPriority(NcArray<NcGeomConstraint::GeomConstraintType>& constraintList) const
	{
		constraintList.setLogicalLength(0);
		for(int type = (int)NcGeomConstraint::kHorizontal;
		    type < (int)NcGeomConstraint::kEqualRadius; ++type)
		{
			constraintList.append((NcGeomConstraint::GeomConstraintType)type);
		}
	}
	virtual bool isEvaluationCancelled() { return false; }
	int getTotalConstraints(NcArray<NcGeomConstraint*>* pConstraints) const;
private:
	int getAutoConstraintMask() const;
	void validate(void* pData);
	bool isValidConstraintType(NcGeomConstraint::GeomConstraintType type,
	                           const NcGeomConstraint* pConstraint) const;
	void constraintAdded(NcGeomConstraint* pNewCons);
private:
	NcArray<NcGeomConstraint*> mConstraints;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssoc2dConstraintGroup
class NRXDBGATE_EXPORT NcDbAssoc2dConstraintGroup : public NcDbAssocAction {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssoc2dConstraintGroup);
	enum SolutionStatus
	{
		kWellDefined = 0,
		kUnderConstrained,
		kOverConstrained,
		kInconsistent,
		kNotEvaluated,
		kNotAvailable,
		kRejectedByClient,
	};
	NcDbAssoc2dConstraintGroup(const NcGePlane& plane = NcGePlane::kXYPlane);
	const NcGePlane getWorkPlane() const;
	Nano::ErrorStatus transformActionBy(const NcGeMatrix3d& transform);
	int getDOF() const;
	SolutionStatus solutionStatus(bool bAlsoCheckForConstraints = true) const;
	SolutionStatus geometryStatus(const NcConstrainedGeometry* pConsGeom) const;
	SolutionStatus constraintStatus(const NcGeomConstraint* pConstraint) const;
	Nano::ErrorStatus addConstrainedGeometry(const NcDbFullSubentPath& subentPath, NcConstrainedGeometry*& pConsGeom);
	Nano::ErrorStatus deleteConstrainedGeometry(const NcDbObjectId& geomDependencyId);
	Nano::ErrorStatus getConstrainedGeometry(const NcDbFullSubentPath& fullSubentPath,
	                                         NcConstrainedGeometry*&   pConsGeom,
	                                         bool bCreateArcLineMid = false);
	Nano::ErrorStatus getConstrainedGeometry(const NcDbAssocGeomDependency* pGeomDependency,
	                                         NcConstrainedGeometry*&   pConsGeom,
	                                         NcConstrainedImplicitPoint::ImplicitPointType* pPtType = NULL,
	                                         int defPtIndex = -1,
	                                         bool bCreateArcLineMid = false);
	Nano::ErrorStatus getConstrainedGeometries(NcArray<NcConstrainedGeometry*>& aConstGeom) const;
	Nano::ErrorStatus addGeometricalConstraint(NcGeomConstraint::GeomConstraintType type,
	                                           const NcDbFullSubentPathArray& aPaths,
	                                           NcGeomConstraint** ppNewConstraint  = NULL);
	Nano::ErrorStatus addGeometricalConstraint(NcGeomConstraint::GeomConstraintType type,
	                                           const NcArray<NcConstrainedGeometry*>& apConsGeoms,
	                                           NcGeomConstraint** ppNewConstraint  = NULL);
	Nano::ErrorStatus addDistanceConstraint(NcConstrainedGeometry* pConsGeom1,
	                                        NcConstrainedGeometry* pConsGeom2,
	                                        NcDistanceConstraint::DirectionType directionType,
	                                        NcDbObjectId valueDependencyId,
	                                        NcDbObjectId dimDependencyId,
	                                        const NcGeVector3d* pFixedDirection = NULL,
	                                        const NcConstrainedLine* pDirectionLine = NULL,
	                                        NcDistanceConstraint** ppNewDisConstraint = NULL);
	Nano::ErrorStatus addAngleConstraint(NcConstrainedLine* pConsLine1,
	                                     NcConstrainedLine* pConsLine2,
	                                     NcAngleConstraint::SectorType sectorType,
	                                     NcDbObjectId valueDependencyId,
	                                     NcDbObjectId dimDependencyId,
	                                     NcAngleConstraint** ppNewAngConstraint = NULL);
	Nano::ErrorStatus add3PointAngleConstraint(NcConstrainedPoint* pConsPoint1,
	                                           NcConstrainedPoint* pConsPoint2,
	                                           NcConstrainedPoint* pConsPoint3,
	                                           NcAngleConstraint::SectorType sectorType,
	                                           NcDbObjectId valueDependencyId,
	                                           NcDbObjectId dimDependencyId,
	                                           Nc3PointAngleConstraint** ppNewAngConstraint = NULL);
	Nano::ErrorStatus addRadiusDiameterConstraint(NcConstrainedGeometry* pConsGeom,
	                                              NcRadiusDiameterConstraint::RadiusDiameterConstrType type,
	                                              NcDbObjectId valueDependencyId,
	                                              NcDbObjectId dimDependencyId,
	                                              NcRadiusDiameterConstraint** ppNewRadDiaConstraint = NULL);
	Nano::ErrorStatus deleteConstraint(NcGeomConstraint* pGeomConst);
	Nano::ErrorStatus getConstraints(NcArray<NcGeomConstraint*>& apConstraints) const;
	Nano::ErrorStatus autoConstrain(const NcDbFullSubentPathArray& aPaths,
	                                const NcGeTol& tol,
	                                NcAutoConstrainEvaluationCallback* pCallback);
	Nano::ErrorStatus getAllConnectedGeomDependencies(const NcDbObjectIdArray& srcGeomDependencyIds,
	                                                  NcDbObjectIdArray& allConnectedGeomDependencyIds) const;
	NcConstraintGroupNode* getGroupNodePtr(const NcConstraintGroupNodeId nodeId) const;
	void regenDimensionSystem();
	Nano::ErrorStatus geometryMirrored(NcDbAssocGeomDependency* pGeomDependency);
	static void addGlobalCallback(class NcDbAssoc2dConstraintCallback* pCallback);
	static void removeGlobalCallback(class NcDbAssoc2dConstraintCallback* pCallback);
	static class NcDbAssoc2dConstraintCallback* globalCallback();
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssoc2dConstraintCallback
class NcDbAssoc2dConstraintCallback {
public:
	NcDbAssoc2dConstraintCallback() {}
	virtual ~NcDbAssoc2dConstraintCallback() {}
	virtual bool canBeRelaxed(const class NcExplicitConstraint* pConstraint)
	{
		return false;
	}
	virtual void constraintDeactivated(const NcExplicitConstraint *pConstraint,
	                                   bool bDeactivated = true) {}
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocActionBody
class NRXDBGATE_EXPORT NcDbAssocActionBody : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocActionBody);
	explicit NcDbAssocActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	virtual ~NcDbAssocActionBody();
	NcDbObjectId parentAction() const { return ownerId(); }
	static NcDbObjectId parentAction(const NcDbObjectId& actionBodyId);
	NcDbAssocStatus status() const;
	Nano::ErrorStatus setStatus(NcDbAssocStatus newStatus,
	                            bool            notifyOwningNetwork = true,
	                            bool            setInOwnedActions   = false);
	NcDbObjectId owningNetwork() const;
	Nano::ErrorStatus getDependencies(bool readDependenciesWanted,
	                                  bool writeDependenciesWanted,
	                                  NcDbObjectIdArray& dependencyIds) const;
	Nano::ErrorStatus addDependency(const NcDbObjectId& dependencyId,
	                                bool                setThisActionAsOwningAction = true);
	Nano::ErrorStatus removeDependency(const NcDbObjectId& dependencyId,
	                                   bool                alsoEraseIt);
	Nano::ErrorStatus removeAllDependencies(bool alsoEraseThem);
	Nano::ErrorStatus evaluateDependencies();
	bool isActionEvaluationInProgress() const;
	NcDbAssocEvaluationCallback* currentEvaluationCallback() const;
	bool hasAnyErasedOrBrokenDependencies() const;
	static Nano::ErrorStatus createActionAndActionBodyAndPostToDatabase(
	    NcRxClass*          pActionBodyClass,
	    const NcDbObjectId& objectId,
	    NcDbObjectId&       createdActionId,
	    NcDbObjectId&       createdActionBodyId);
	static Nano::ErrorStatus getActionBodiesOnObject(const NcDbObject*  pObject,
	                                                 bool               ignoreInternalActions,
	                                                 bool               ignoreSuppressedActions,
	                                                 NcDbObjectId*      pWriteOnlyActionBodyId,
	                                                 NcDbObjectIdArray* pReadWriteActionBodyIds,
	                                                 NcDbObjectIdArray* pReadOnlyActionBodyIds = NULL);
public:
	virtual void evaluateOverride() = NULL;
	Nano::ErrorStatus getDependenciesOverride(bool readDependenciesWanted,
	                                          bool writeDependenciesWanted,
	                                          NcDbObjectIdArray& dependencyIds) const
	{ return Nano::eNotImplementedYet; }
	Nano::ErrorStatus getDependentObjectsOverride(bool readDependenciesWanted,
	                                              bool writeDependenciesWanted,
	                                              NcDbObjectIdArray& objectIds) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus removeAllDependenciesOverride(bool alsoEraseThem)
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus isOwnedDependencyOverride(const NcDbAssocDependency* pDependency,
	                                                    bool& isOwnedDependency) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus isExternalDependencyOverride(const NcDbAssocDependency* pDependency,
	                                                       bool& isExternalDependency) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus hasDependencyCachedValueOverride(const NcDbAssocDependency* pDependency,
	                                                           bool& hasDepCachedValue) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus isRelevantDependencyChangeOverride(const NcDbAssocDependency* pDependency,
	                                                             bool& isRelevantDepChange) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus areDependenciesOnTheSameThingOverride(const NcDbAssocDependency* pDependency1,
	                                                                const NcDbAssocDependency* pDependency2,
	                                                                bool& areDependentOnSameThing) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus areDependenciesEqualOverride(const NcDbAssocDependency* pDependency1,
	                                                       const NcDbAssocDependency* pDependency2,
	                                                       bool& areEqual) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus evaluateDependencyOverride(NcDbAssocDependency* pDependency)
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus dependentObjectClonedOverride(const NcDbAssocDependency* pDependency,
	                                                        const NcDbObject*          pDbObj,
	                                                        const NcDbObject*          pNewObj)
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus addMoreObjectsToDeepCloneOverride(NcDbIdMapping& idMap,
	                                                            NcDbObjectIdArray& additionalObjectsToClone) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus postProcessAfterDeepCloneOverride(NcDbIdMapping& idMap)
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus postProcessAfterDeepCloneCancelOverride(NcDbIdMapping& idMap)
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus ownedDependencyStatusChangedOverride(NcDbAssocDependency* pOwnedDependency,
	                                                               NcDbAssocStatus      previousStatus)
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus isEqualToOverride(const NcDbAssocAction* pOtherAction, bool& isEqual) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus evaluationPriorityOverride(NcDbAssocEvaluationPriority& priority) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus getDependentActionsToEvaluateOverride(NcDbActionsToEvaluateCallback* pActionsToEvaluateCallback) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus transformActionByOverride(const NcGeMatrix3d&)
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus dragStatusOverride(const NcDb::DragStat status)
	{ return Nano::eNotImplementedYet; }
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocActionParam
class NRXDBGATE_EXPORT NcDbAssocActionParam : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocActionParam);
	NcDbAssocActionParam(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	const NcString& name() const;
	virtual Nano::ErrorStatus setName(const NcString& newName);
	virtual Nano::ErrorStatus makeParamEmpty(bool alsoEraseOwnedObjects);
	virtual Nano::ErrorStatus detachDependencies();
	virtual Nano::ErrorStatus makeParamConstant();
	virtual Nano::ErrorStatus transformConstantGeometry(const NcGeMatrix3d& transform);
	NcDbObjectId parentAction() const;
	virtual Nano::ErrorStatus getDependencies(bool readDependenciesWanted,
	                                          bool writeDependenciesWanted,
	                                          NcDbObjectIdArray& dependencyIds) const;
	virtual void collectPersSubentNamingDataOverride(NcDbPersStepIdArray&   stepIds,
	                                                 NcDbPersSubentIdArray& persSubentIds) const;
	virtual void clonePersSubentNamingDataOverride(NcDbAssocPersSubentManagerCloner* pCloner);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocAsmBodyActionParam
class NRXDBGATE_EXPORT NcDbAssocAsmBodyActionParam : public NcDbAssocActionParam {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocAsmBodyActionParam);
	explicit NcDbAssocAsmBodyActionParam(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	virtual Nano::ErrorStatus setBody(const NcDbEntity* pAsmEntity, bool isReadDependency, bool isWriteDependency);
	virtual Nano::ErrorStatus setBody(NcDbObjectId asmEntityId, bool isReadDependency, bool isWriteDependency);
	virtual Nano::ErrorStatus setBody(void* pAsmBody, bool makeCopy);
	virtual void* body(bool makeCopy) const;
	Nano::ErrorStatus getDependentOnCompoundObject(NcDbCompoundObjectId& compoundId) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocParamBasedActionBody
class NRXDBGATE_EXPORT NcDbAssocParamBasedActionBody : public NcDbAssocActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocParamBasedActionBody);
	explicit NcDbAssocParamBasedActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	virtual Nano::ErrorStatus removeAllParams(bool alsoEraseThem);
	int paramCount() const;
	const NcDbObjectIdArray& ownedParams() const;
	Nano::ErrorStatus addParam(const NcDbObjectId& paramId, int& paramIndex);
	Nano::ErrorStatus removeParam(const NcDbObjectId& paramId, bool alsoEraseIt);
	const NcDbObjectIdArray& paramsAtName(const NcString& paramName) const;
	NcDbObjectId paramAtName(const NcString& paramName, int index = 0) const;
	NcDbObjectId paramAtIndex(int paramIndex) const;
	void ownedValueParamNames(NcArray<NcString>& paramNames) const;
	Nano::ErrorStatus getValueParamArray(const NcString&           paramName,
	                                     NcArray<NcDbEvalVariant>& values,
	                                     NcArray<NcString>&        expressions,
	                                     NcArray<NcString>&        evaluatorIds) const;
	Nano::ErrorStatus getValueParam(const NcString&  paramName,
	                                NcDbEvalVariant& value,
	                                NcString&        expression,
	                                NcString&        evaluatorId,
	                                int              valueIndex = 0) const;
	Nano::ErrorStatus setValueParamArray(const NcString&                 paramName,
	                                     const NcArray<NcDbEvalVariant>& values,
	                                     const NcArray<NcString>&        expressions,
	                                     const NcArray<NcString>&        evaluatorIds,
	                                     NcArray<NcString>&              errorMessages,
	                                     bool                            silentMode);
	Nano::ErrorStatus setValueParam(const NcString&        paramName,
	                                const NcDbEvalVariant& value,
	                                const NcString&        expression,
	                                const NcString&        evaluatorId,
	                                NcString&              errorMessage,
	                                bool                   silentMode,
	                                int                    valueIndex = 0);
	NcValue::UnitType valueParamUnitType(const NcString& paramName) const;
	Nano::ErrorStatus setValueParamUnitType(const NcString& paramName, NcValue::UnitType unitType);
	Nano::ErrorStatus removeValueParam(const NcString& paramName);
	Nano::ErrorStatus valueParamInputVariables(const NcString& paramName, NcDbObjectIdArray& variableIds) const;
	Nano::ErrorStatus setValueParamControlledObjectDep(const NcString& paramName, const NcDbObjectId& controlledObjectDepId);
	Nano::ErrorStatus updateValueParamControlledObject(const NcString& paramName) const;
	Nano::ErrorStatus updateValueParamFromControlledObject(const NcString& paramName);
	Nano::ErrorStatus updateAllObjectsControlledByValueParams() const;
	Nano::ErrorStatus transformAllConstantGeometryParams(const NcGeMatrix3d& transform);
	Nano::ErrorStatus scaleAllDistanceValueParams(double scaleFactor);
	virtual Nano::ErrorStatus removeActionsControllingObjectOverride(NcDbObject* pControlledObject)
	{ return Nano::eNotImplementedYet; }
	virtual void evaluateOverride();
	virtual Nano::ErrorStatus collectPersSubentNamingDataOverride(NcDbPersStepIdArray&   stepIds,
	                                                              NcDbPersSubentIdArray& persSubentIds) const;
	virtual Nano::ErrorStatus clonePersSubentNamingDataOverride(class NcDbAssocPersSubentManagerCloner* pCloner);
	virtual Nano::ErrorStatus notificationOverride(class NcDbAssocNotificationData* pNotificationData);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocSurfaceActionBody : public NcDbAssocParamBasedActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocSurfaceActionBody);
	explicit NcDbAssocSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	NcDbObjectId resultingSurfaceDep(bool createIfDoesNotExist, bool isWriteOnlyDependency = true);
	NcDbObjectId resultingSurface() const;
	Nano::ErrorStatus setResultingSurface(const NcDbObjectId& surfaceId, bool isWriteOnlyDependency = true);
	bool isSemiAssociative() const;
	virtual bool isSemiAssociativitySatisfiedOverride() const;
	virtual void evaluateOverride();
	virtual Nano::ErrorStatus getDependentActionsToEvaluateOverride(NcDbActionsToEvaluateCallback*) const;
	virtual Nano::ErrorStatus addMoreObjectsToDeepCloneOverride(
	    NcDbIdMapping&, NcDbObjectIdArray& additionalObjectsToClone) const;
	virtual Nano::ErrorStatus dragStatusOverride(const NcDb::DragStat);
	static Nano::ErrorStatus findActionsThatAffectedTopologicalSubentity(
	    const NcDbEntity*  pAsmBasedEntity,
	    const NcDbSubentId&,
	    NcDbObjectIdArray& actionIds);
	static Nano::ErrorStatus getTopologicalSubentitiesForActionsOnEntity(
	    const NcDbEntity*                pAsmBasedEntity,
	    bool                             alsoUseAdjacentTopology,
	    NcDbObjectIdArray&               actionIds,
	    NcArray<NcArray<NcDbSubentId> >& actionSubentIds);
	static Nano::ErrorStatus getSurfacesDirectlyDependentOnObject(
	    const NcDbObject*,
	    NcDbObjectIdArray& dependentSurfaceIds);
	virtual Nano::ErrorStatus getGripPoints(
	    NcGePoint3dArray& gripPoints,
	    NcDbIntArray&     osnapModes,
	    NcDbIntArray&     geomIds) const;
	virtual Nano::ErrorStatus getGripPoints(
	    NcDbGripDataPtrArray& grips,
	    const double          curViewUnitSize,
	    const int             gripSize,
	    const NcGeVector3d&   curViewDir,
	    const int             bitflags) const;
	virtual Nano::ErrorStatus moveGripPoints(
	    const NcDbIntArray& indices,
	    const NcGeVector3d& offset);
	virtual Nano::ErrorStatus moveGripPoints(
	    const NcDbVoidPtrArray& gripAppData,
	    const NcGeVector3d&     offset,
	    const int               bitflags);
	virtual Nano::ErrorStatus moveStretchPoints(
	    const NcDbIntArray& indices,
	    const NcGeVector3d& offset);
	virtual void gripStatus(const NcDb::GripStat status);
	virtual Nano::ErrorStatus getGripEntityUCS(
	    const void*   pGripAppData,
	    NcGeVector3d& normalVec,
	    NcGePoint3d&  origin,
	    NcGeVector3d& xAxis) const;
	virtual void list() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocPathBasedSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocPathBasedSurfaceActionBody : public NcDbAssocSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocPathBasedSurfaceActionBody);
	explicit NcDbAssocPathBasedSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus removeAllPathParams();
	Nano::ErrorStatus getInputPathParams(NcDbObjectIdArray& pathParamIds) const;
	Nano::ErrorStatus getInputPaths(NcArray<NcArray<NcArray<NcDbEdgeRef> > >&) const;
	Nano::ErrorStatus setInputPaths(const NcArray<NcArray<NcDbEdgeRef> >&);
	Nano::ErrorStatus setInputPaths(const NcArray<NcDbPathRef>&);
	Nano::ErrorStatus updateInputPath(int pathIndex, const NcDbPathRef&);
	Nano::ErrorStatus removeAllVertexParams();
	Nano::ErrorStatus getInputVertexParams(NcDbObjectIdArray& vertexParamIds) const;
	Nano::ErrorStatus setInputPoints(const NcArray<NcDbVertexRef>&);
	Nano::ErrorStatus getInputPoints(NcArray<NcDbVertexRef>&) const;
	Nano::ErrorStatus makeInputPathsDrawOnTopOfResultingSurface() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocBlendSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocBlendSurfaceActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocBlendSurfaceActionBody);
	explicit NcDbAssocBlendSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	NRX::Int16       startEdgeContinuity(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	Nano::ErrorStatus  setStartEdgeContinuity (NRX::Int16 value, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	NRX::Int16       endEdgeContinuity(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	Nano::ErrorStatus  setEndEdgeContinuity (NRX::Int16 value, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	double             startEdgeBulge(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	Nano::ErrorStatus  setStartEdgeBulge(double value, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	double             endEdgeBulge(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	Nano::ErrorStatus  setEndEdgeBulge(double value, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	Nano::ErrorStatus  getContinuityGripPoints(NcGePoint3d& startEdgePt,
	                                           NcGePoint3d& endEdgePt) const;
	Nano::ErrorStatus  getProfiles(NcDbLoftProfile* & pStartProfile,
	                               NcDbLoftProfile* & pEndProfile) const;
	Nano::ErrorStatus  getBlendOptions( NcDbBlendOptions& blendOptions ) const;
	Nano::ErrorStatus  setBlendOptions (const NcDbBlendOptions& blendOptions );
	static Nano::ErrorStatus createInstance(const NcDbObjectId& resultingSurfaceId,
	                                        const NcDbLoftProfile* startProfile,
	                                        const NcDbLoftProfile* endProfile,
	                                        const NcDbBlendOptions& blendOptions,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocCompoundActionParam
class NRXDBGATE_EXPORT NcDbAssocCompoundActionParam : public NcDbAssocActionParam {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocCompoundActionParam);
	explicit NcDbAssocCompoundActionParam(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	virtual Nano::ErrorStatus removeAllParams(bool alsoEraseThem);
	int paramCount() const;
	const NcDbObjectIdArray& ownedParams() const;
	Nano::ErrorStatus addParam(const NcDbObjectId& paramId, int& paramIndex);
	Nano::ErrorStatus removeParam(const NcDbObjectId& paramId, bool alsoEraseIt);
	const NcDbObjectIdArray& paramsAtName(const NcString& paramName) const;
	NcDbObjectId paramAtName(const NcString& paramName, int index = 0) const;
	NcDbObjectId paramAtIndex(int paramIndex) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocDependency
class NRXDBGATE_EXPORT NcDbAssocDependency : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocDependency);
	explicit NcDbAssocDependency(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	NcDbObjectId dependencyBody() const;
	Nano::ErrorStatus setDependencyBody(const NcDbObjectId& dependencyBodyId);
	NcDbAssocStatus status() const;
	Nano::ErrorStatus setStatus(NcDbAssocStatus newStatus,
	                            bool            notifyOwningAction = true);
	bool isReadDependency() const;
	bool isWriteDependency() const;
	void setIsReadDependency(bool yesNo);
	void setIsWriteDependency(bool yesNo);
	bool isObjectStateDependent() const;
	void setIsObjectStateDependent(bool yesNo);
	int order() const;
	void setOrder(int newOrder);
	NcDbObjectId owningAction() const { return ownerId(); }
	Nano::ErrorStatus setOwningAction(const NcDbObjectId& actionId);
	NcDbObjectId dependentOnObject() const;
	Nano::ErrorStatus getDependentOnCompoundObject(NcDbCompoundObjectId& compoundId) const;
	bool isDependentOnCompoundObject() const;
	NcDbObjectId prevDependencyOnObject() const;
	NcDbObjectId nextDependencyOnObject() const;
	bool isAttachedToObject() const { return !dependentOnObject().isNull(); }
	Nano::ErrorStatus attachToObject(const NcDbCompoundObjectId& compoundId);
	Nano::ErrorStatus dependentOnObjectStatus() const;
	Nano::ErrorStatus detachFromObject();
	Nano::ErrorStatus updateDependentOnObject();
	void setDependentOnObject(const NcDbCompoundObjectId& compoundId);
	static Nano::ErrorStatus getFirstDependencyOnObject(const NcDbObject* pObject,
	                                                    NcDbObjectId& firstDependencyId);
	static Nano::ErrorStatus getDependenciesOnObject(const NcDbObject* pObject,
	                                                 bool readDependenciesWanted,
	                                                 bool writeDependenciesWanted,
	                                                 NcDbObjectIdArray& dependencyIds);
	static Nano::ErrorStatus notifyDependenciesOnObject(const NcDbObject* pObject,
	                                                    NcDbAssocStatus   newStatus);
	bool isDelegatingToOwningAction() const;
	void setIsDelegatingToOwningAction(bool yesNo);
	bool hasCachedValue() const;
	bool isRelevantChange() const;
	Nano::ErrorStatus notification(NcDbAssocNotificationData* pNotifData);
	bool isDependentOnTheSameThingAs(const NcDbAssocDependency* pOtherDependency) const;
	bool isDependentOnObjectReadOnly() const;
	bool isEqualTo(const NcDbAssocDependency* pOtherDependency) const;
	bool isActionEvaluationInProgress() const;
	NcDbAssocEvaluationCallback* currentEvaluationCallback() const;
	void evaluate();
	virtual void erased(const NcDbObject* dbObj, NRX::Boolean isErasing = true);
	virtual void modified(const NcDbObject* dbObj);
	virtual void copied(const NcDbObject* pDbObj, const NcDbObject* pNewObj);
private:
	void setPrevDependencyOnObject(const NcDbObjectId& depId);
	void setNextDependencyOnObject(const NcDbObjectId& depId);
	friend class NcDbAssocDeepCloneRxEventReactor;
	friend class NcDbAssocDeepCloneData;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocDependencyNotificationDisabler
class NRXDBGATE_EXPORT NcDbAssocDependencyNotificationDisabler {
public:
	explicit NcDbAssocDependencyNotificationDisabler(bool disableIt = true);
	~NcDbAssocDependencyNotificationDisabler();
	static bool isDisabled();
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocDependencyBody
class NRXDBGATE_EXPORT NcDbAssocDependencyBody : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocDependencyBody);
	explicit NcDbAssocDependencyBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	virtual ~NcDbAssocDependencyBody();
	NcDbObjectId parentDependency() const { return ownerId(); }
	NcDbAssocStatus status() const;
	Nano::ErrorStatus setStatus(NcDbAssocStatus newStatus,
	                            bool notifyOwningAction = true);
	NcDbObjectId owningAction() const;
	NcDbObjectId dependentOnObject() const;
	bool isAttachedToObject() const { return !dependentOnObject().isNull(); }
	bool isActionEvaluationInProgress() const;
	NcDbAssocEvaluationCallback* currentEvaluationCallback() const;
public:
	virtual void evaluateOverride() = NULL;
	virtual Nano::ErrorStatus updateDependentOnObjectOverride()
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus hasCachedValueOverride(bool& hasCachedVal) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus isRelevantChangeOverride(bool& isRelevChange) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus isDependentOnTheSameThingAsOverride(const NcDbAssocDependency* pOtherDependency,
	                                                              bool& isDependentOnSameThing) const
	{ return Nano::eNotImplementedYet; }
	virtual Nano::ErrorStatus isEqualToOverride(const NcDbAssocDependency* pOtherDependency, bool& isEqual) const
	{ return Nano::eNotImplementedYet; }
	virtual void erasedOverride(const NcDbObject* pDbObj, NRX::Boolean isErasing)
	{}
	virtual void modifiedOverride(const NcDbObject* pDbObj)
	{}
	virtual void clonedOverride(const NcDbObject* pDbObj, const NcDbObject* pNewObj)
	{}
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocDependencyPE
class NRXDBGATE_EXPORT NcDbAssocDependencyPE : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocDependencyPE);
	virtual bool allowsDependencies(const NcDbObject* pObject, bool isWriteDependency) const
	{ return false; }
};

//////////////////////////////////////////////////////////////////////////
// NcDbSubentGeometry
class NRXDBGATE_EXPORT NcDbSubentGeometry {
public:
	NcDbSubentGeometry() : mSubentType(NcDb::kNullSubentType), mpCurve(NULL) {}
	NcDbSubentGeometry(const NcGePoint3d& pnt)
	    : mSubentType(NcDb::kVertexSubentType), mPoint(pnt), mpCurve(NULL) {}
	NcDbSubentGeometry(NcGeCurve3d* pCurve)
	    : mSubentType(NcDb::kEdgeSubentType), mpCurve(pCurve) {}
	NcDb::SubentType type() const { return mSubentType; }
	NcGePoint3d point() const { return mPoint; }
	NcGeCurve3d* curve() const { return mpCurve; }
private:
	NcDb::SubentType mSubentType;
	NcGePoint3d      mPoint;
	NcGeCurve3d*     mpCurve;
};


//////////////////////////////////////////////////////////////////////////
// NcDbAssocDimDependencyBodyBase
class NRXDBGATE_EXPORT NcDbAssocDimDependencyBodyBase : public NcDbAssocDependencyBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocDimDependencyBodyBase);
	explicit NcDbAssocDimDependencyBodyBase(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	virtual ~NcDbAssocDimDependencyBodyBase();
	virtual NcString getEntityTextOverride() const = NULL;
	virtual Nano::ErrorStatus setEntityTextOverride(const NcString& newText) = NULL;
	virtual double getEntityMeasurementOverride() const = NULL;
	virtual bool isEntityAttachmentChangedOverride() const = NULL;
	virtual Nano::ErrorStatus updateDependentOnObjectOverride();
	class NcExplicitConstraint* constraint() const;
	NcDbObjectId variable() const;
	Nano::ErrorStatus getConstrainedGeoms(NcArray<NcConstrainedGeometry*>& geoms) const;
	Nano::ErrorStatus getConstrainedGeoms(NcArray<NcDbFullSubentPath>& geoms) const;
	Nano::ErrorStatus getConstrainedGeoms(NcArray<NcDbSubentGeometry>& geoms,
	                                      NcGeVector3d&                distanceDirection) const;
	Nano::ErrorStatus getVariableNameAndExpression(NcString& name, NcString& expression, NcString& value) const;
	Nano::ErrorStatus getEntityNameAndExpression(NcString& name, NcString& expression) const;
	Nano::ErrorStatus setVariableNameAndExpression(const NcString& name, const NcString& expression);
	Nano::ErrorStatus setEntityNameAndExpression(const NcString& name, const NcString& expression, const NcString& value);
	Nano::ErrorStatus setNameAndExpression(const NcString& name, const NcString& expression);
	Nano::ErrorStatus validateEntityText(const NcString& entityTextToValidate,
	                                     NcString&       errorMessage) const;
	NcString composeEntityText(int requiredNameFormat = -1) const;
	Nano::ErrorStatus setVariableValueToMeasuredValue() const;
	Nano::ErrorStatus deactivateConstraint() const;
	Nano::ErrorStatus reactivateConstraint() const;
	bool isConstraintActive() const;
	Nano::ErrorStatus getMeasuredValue(double& measurement) const;
	Nano::ErrorStatus setIsReferenceOnly(bool yesNo);
	static Nano::ErrorStatus
	getNameAndExpressionFromEntityText(const NcString& entityText,
	                                   bool            useMeasurementIfNoText,
	                                   double          measurement,
	                                   bool            isAngular,
	                                   NcString&       name,
	                                   NcString&       expression);
	int getCurrentlyUsedEntityNameFormat() const;
	void dragStatus(const NcDb::DragStat status);
	static Nano::ErrorStatus getFromEntity(const NcDbObjectId& entityId, NcDbObjectId& dimDepBodyId);
	Nano::ErrorStatus entityAttachmentPointMoved(const NcArray<NcDbSubentGeometry>& newAttachedGeometries,
	                                             double measurement = 0.0);
	virtual Nano::ErrorStatus isRelevantChangeOverride(bool& isRelevChange) const;
	virtual void evaluateOverride();
	virtual void modifiedOverride(const NcDbObject* pDbObj);
	virtual void erasedOverride(const NcDbObject* pDbObj, NRX::Boolean isErasing);
	virtual Nano::ErrorStatus subErase(NRX::Boolean erasing);
	static NcString formatToCurrentPrecision(const NcString& expression, bool isAngular);
	static bool setEraseDimensionIfDependencyIsErased(bool yesNo);
	static bool getEraseDimensionIfDependencyIsErased();
	class NRXDBGATE_EXPORT NotificationIgnorer
	{
	public:
		NotificationIgnorer();
		~NotificationIgnorer();
		static bool isIgnoringNotifications();
	private:
		const bool mPrevIsIgnoringNotifications;
		static bool smIsIgnoringNotifications;
	};
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocDimDependencyBody
class NRXDBGATE_EXPORT NcDbAssocDimDependencyBody : public NcDbAssocDimDependencyBodyBase {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocDimDependencyBody);
	NcDbAssocDimDependencyBody();
	virtual ~NcDbAssocDimDependencyBody();
	virtual NcString getEntityTextOverride() const;
	virtual Nano::ErrorStatus setEntityTextOverride(const NcString& newText);
	virtual double getEntityMeasurementOverride() const;
	virtual bool isEntityAttachmentChangedOverride() const;
	virtual Nano::ErrorStatus updateDependentOnObjectOverride();
	static Nano::ErrorStatus
	            createAndPostToDatabase(const NcDbObjectId& dimId,
	                                    NcDbObjectId&       dimDepId,
	                                    NcDbObjectId&       dimDepBodyId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocEdgeActionParam
class NRXDBGATE_EXPORT NcDbAssocEdgeActionParam : public NcDbAssocActionParam {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocEdgeActionParam);
	explicit NcDbAssocEdgeActionParam(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	virtual Nano::ErrorStatus setEdgeRef(const NcDbEdgeRef& edgeRef, bool isReadDependency = true, bool isWriteDependency = false);
	virtual Nano::ErrorStatus getEdgeRef(NcArray<NcDbEdgeRef>& edgeRefs) const;
	Nano::ErrorStatus getDependentOnCompoundObject(NcDbCompoundObjectId& compoundId) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocEdgeChamferActionBody
class NRXDBGATE_EXPORT NcDbAssocEdgeChamferActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocEdgeChamferActionBody);
	explicit NcDbAssocEdgeChamferActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus setInput(const NcDbFullSubentPathArray& chamferEdges, const NcDbSubentId& baseFace);
	Nano::ErrorStatus setBaseDistance(double baseDistance, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	Nano::ErrorStatus setOtherDistance(double otherDistance, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	double baseDistance(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	double otherDistance(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	virtual void evaluateOverride();
	static Nano::ErrorStatus createInstance(const NcDbFullSubentPathArray& chamferEdges,
	                                        const NcDbSubentId& baseFace,
	                                        double baseDistance,
	                                        double otherDistance,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocEdgeFilletActionBody
class NRXDBGATE_EXPORT NcDbAssocEdgeFilletActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocEdgeFilletActionBody);
	explicit NcDbAssocEdgeFilletActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus setInputEdges(const NcDbFullSubentPathArray& filletEdges);
	Nano::ErrorStatus setRadius(double radius, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	double radius(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	virtual void evaluateOverride();
	static Nano::ErrorStatus createInstance(const NcDbFullSubentPathArray& filletEdges,
	                                        double radius,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocPersSubentId
class NRXDBGATE_EXPORT NcDbAssocPersSubentId : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocPersSubentId);
	NcDbAssocPersSubentId() {}
	virtual ~NcDbAssocPersSubentId() {}
	virtual Nano::ErrorStatus getTransientSubentIds(const NcDbEntity*      pEntity,
	                                                NcArray<NcDbSubentId>& subents) const;
	virtual NcDb::SubentType subentType(const NcDbEntity* pEntity) const = NULL;
	virtual int transientSubentCount(const NcDbEntity* pEntity) const;
	virtual bool isNull() const = NULL;
	virtual bool isEqualTo(const NcDbEntity* pEntity, const NcDbAssocPersSubentId* pOther) const
	{
		return this == pOther || pEntity != NULL && pOther != NULL && isA() == pOther->isA();
	}
	virtual Nano::ErrorStatus mirror(const NcDbEntity* pMirroredEntity);
	static Nano::ErrorStatus
	createObjectAndDwgInFields(NcDbDwgFiler*           pFiler,
	                           NcDbAssocPersSubentId*& pCreatedPersSubentId);
	static Nano::ErrorStatus
	createObjectAndDxfInFields(NcDbDxfFiler*           pFiler,
	                           NcDbAssocPersSubentId*& pCreatedPersSubentId);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo) { return Nano::eOk; }
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocEdgePersSubentId
class NRXDBGATE_EXPORT NcDbAssocEdgePersSubentId : public NcDbAssocPersSubentId {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocEdgePersSubentId);
	NcDbAssocEdgePersSubentId();
	explicit NcDbAssocEdgePersSubentId(NRX::Int32 vertexIdentifier1,
	                                   NRX::Int32 vertexIdentifier2);
	virtual int transientSubentCount(const NcDbEntity* pEntity) const { return !isNull() ? 1 : 0; }
	virtual NcDb::SubentType subentType(const NcDbEntity* pEntity) const;
	virtual bool isNull() const { return mIndex1 == 0; }
	virtual bool isEqualTo(const NcDbEntity* pEntity, const NcDbAssocPersSubentId* pOther) const;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo);
	NRX::GsMarker index1() const { return mIndex1; }
	NRX::GsMarker index2() const { return mIndex2; }
private:
	NRX::GsMarker  mIndex1;
	NRX::GsMarker  mIndex2;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocExtendSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocExtendSurfaceActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocExtendSurfaceActionBody);
	explicit NcDbAssocExtendSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus setDistance(double distance, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	double distance(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	static Nano::ErrorStatus createInstance(const NcDbObjectId& resultingSurfaceId,
	                                        const NcArray<NcDbEdgeRef>& extendEdges,
	                                        double distance,
	                                        NcDbSurface::EdgeExtensionType option,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId );
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocExtrudedSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocExtrudedSurfaceActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocExtrudedSurfaceActionBody);
	explicit NcDbAssocExtrudedSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus setTaperAngle( double dTaperAngle, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	double            taperAngle(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	Nano::ErrorStatus setHeight( double dHeight, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	double            height(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	static Nano::ErrorStatus createInstance(const NcDbObjectId& resultingSurfaceId,
	                                        const NcDbPathRef& inputPath,
	                                        const NcGeVector3d& directionVec,
	                                        const NcDbSweepOptions& sweptOptions,
	                                        bool  bEnabled,
	                                        NcDbObjectId& createdActionId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocFaceActionParam
class NRXDBGATE_EXPORT NcDbAssocFaceActionParam : public NcDbAssocActionParam {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocFaceActionParam);
	explicit NcDbAssocFaceActionParam(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	virtual Nano::ErrorStatus setFaceRef(const NcDbFaceRef& faceRef, bool isReadDependency = true, bool isWriteDependency = false);
	virtual Nano::ErrorStatus getFaceRef(NcArray<NcDbFaceRef>& faceRefs) const;
	Nano::ErrorStatus getDependentOnCompoundObject(NcDbCompoundObjectId& compoundId) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocGeomDependency
class NRXDBGATE_EXPORT NcDbAssocGeomDependency : public NcDbAssocDependency {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocGeomDependency);
	explicit NcDbAssocGeomDependency(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	const NcDbAssocPersSubentId* persistentSubentId() const;
	Nano::ErrorStatus getTransientSubentIds(NcArray<NcDbSubentId>& transientSubentIds) const;
	Nano::ErrorStatus setSubentity(const NcDbSubentId& transientSubentId);
	NcDb::SubentType subentType() const;
	int transientSubentCount() const;
	bool isCachingSubentityGeometry() const;
	void setCachingSubentityGeometry(bool yesNo);
	Nano::ErrorStatus getVertexSubentityGeometry(NcGePoint3dArray& vertexPositions) const;
	Nano::ErrorStatus getEdgeSubentityGeometry(NcArray<NcGeCurve3d*>& edgeCurves) const;
	Nano::ErrorStatus getFaceSubentityGeometry(NcArray<NcGeSurface*>& faceSurfaces) const;
	Nano::ErrorStatus setVertexSubentityGeometry(const NcGePoint3dArray& newVertexPositions);
	Nano::ErrorStatus setEdgeSubentityGeometry(const NcArray<const NcGeCurve3d*>& newEdgeCurves);
	Nano::ErrorStatus setFaceSubentityGeometry(const NcArray<const NcGeSurface*>& newFaceSurfaces);
	Nano::ErrorStatus dependentOnObjectMirrored();
	static Nano::ErrorStatus redirectToAnotherSubentity(const NcDbObjectId& oldObjectId,
	                                                    const NcDbSubentId& oldSubentId,
	                                                    const NcDbObjectId& newObjectId,
	                                                    const NcDbSubentId& newSubentId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocEvaluationCallback
class NRXDBGATE_EXPORT NcDbAssocEvaluationCallback {
public:
	NcDbAssocEvaluationCallback() {}
	virtual ~NcDbAssocEvaluationCallback() {}
	virtual NcDbAssocEvaluationMode evaluationMode() const { return kModifyObjectsAssocEvaluationMode; }
	virtual void beginActionEvaluation(NcDbAssocAction* pAction) = NULL;
	virtual void endActionEvaluation(NcDbAssocAction* pAction) = NULL;
	virtual void setActionEvaluationErrorStatus(NcDbAssocAction*    pAction,
	                                            Nano::ErrorStatus   errorStatus,
	                                            const NcDbObjectId& objectId   = NcDbObjectId::kNull,
	                                            NcDbObject*         pObject    = NULL,
	                                            void*               pErrorInfo = NULL) = NULL;
	virtual void
	beginActionEvaluationUsingObject(NcDbAssocAction*    pAction,
	                                 const NcDbObjectId& objectId,
	                                 bool                objectIsGoingToBeUsed,
	                                 bool                objectIsGoingToBeModified,
	                                 NcDbObject*&        pSubstituteObject) = NULL;
	virtual void endActionEvaluationUsingObject(NcDbAssocAction*    pAction,
	                                            const NcDbObjectId& objectId,
	                                            NcDbObject*         pObject) = NULL;
	virtual NcDbAssocDraggingState draggingState() const { return kNotDraggingAssocDraggingState; }
	virtual bool cancelActionEvaluation() = NULL;
	virtual NcDbEvalContext* getAdditionalData() const { return NULL; }
	virtual NcDbAssocTransformationType getTransformationType() const { return kNotSpecified; }
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocLoftedSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocLoftedSurfaceActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	enum ProfileType {
		kStartCrossSection  = 0x01,
		kEndCrossSection    = 0x02,
		kStartGuide         = 0x04,
		kEndGuide           = 0x08
	};
	NCRX_DECLARE_MEMBERS(NcDbAssocLoftedSurfaceActionBody);
	explicit NcDbAssocLoftedSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus getContinuity( ProfileType type, int &continuity, NcString& expression = dummyString(),
	    NcString& evaluatorId = dummyString() ) const;
	Nano::ErrorStatus setContinuity( ProfileType type, int continuity, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString() );
	Nano::ErrorStatus getBulge( ProfileType type, double &bulge, NcString& expression = dummyString(),
	    NcString& evaluatorId = dummyString() ) const;
	Nano::ErrorStatus setBulge( ProfileType type, double bulge, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString() );
	static Nano::ErrorStatus createInstance(const NcDbObjectId& resultingSurfaceId,
	                                        const NcArray<NcDbGeomRef *>& crossSections,
	                                        const NcArray<NcDbPathRef>& guideCurves,
	                                        const NcDbPathRef& pathCurve,
	                                        const NcDbLoftOptions& loftOptions,
	                                        const NcArray<int>& continuityArray,
	                                        const NcArray<double>& bulgeArray,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocManager
class NRXDBGATE_EXPORT NcDbAssocManager : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocManager);
	NcDbAssocManager();
	static bool evaluateTopLevelNetwork(NcDbDatabase*                pDatabase,
	                                    NcDbAssocEvaluationCallback* pCallback     = NULL,
	                                    int                          callbackOrder = 0);
	static NcDbAssocEvaluationCallback* globalEvaluationMultiCallback();
	static Nano::ErrorStatus addGlobalEvaluationCallback(NcDbAssocEvaluationCallback* pCallback, int order);
	static Nano::ErrorStatus removeGlobalEvaluationCallback(NcDbAssocEvaluationCallback* pCallback);
	static void getGlobalEvaluationCallbacks(NcArray<NcDbAssocEvaluationCallback*>& callbacks,
	                                         NcArray<int>&                          orders);
	static bool isActionEvaluationInProgress(const NcDbDatabase*);
	static NcDbAssocEvaluationCallback* getCurrentEvaluationCallback(const NcDbDatabase*);
	static bool hasAssocNetwork(const NcDbDatabase* pDatabase);
	static Nano::ErrorStatus auditAssociativeData(NcDbDatabase* pDatabase, bool traverseWholeDatabase);
	static Nano::ErrorStatus initialize();
	static void uninitialize();
	static void  enableProgressMeter(bool enableIt, const NcString& progressLabel = NcString());
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocNetworkEvaluationDisabler
class NRXDBGATE_EXPORT NcDbAssocNetworkEvaluationDisabler {
public:
	explicit NcDbAssocNetworkEvaluationDisabler(NcDbDatabase*, bool disableIt = true);
	~NcDbAssocNetworkEvaluationDisabler();
	static bool isDisabled(NcDbDatabase*);
private:
	NcDbDatabase* mpDatabase;
	bool          mPreviouslyDisabled;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocNetwork
class NRXDBGATE_EXPORT NcDbAssocNetwork : public NcDbAssocAction {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocNetwork);
	explicit NcDbAssocNetwork(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	const NcDbObjectIdArray& getActions() const;
	const NcDbObjectIdArray& getActionsToEvaluate() const;
	Nano::ErrorStatus addAction(const NcDbObjectId& actionId, bool alsoSetAsDatabaseOwner);
	Nano::ErrorStatus removeAction(const NcDbObjectId& actionId, bool alsoEraseIt);
	Nano::ErrorStatus addActions(const NcDbObjectIdArray& actionIds, bool alsoSetAsDatabaseOwner);
	Nano::ErrorStatus removeAllActions(bool alsoEraseThem);
	Nano::ErrorStatus ownedActionStatusChanged(NcDbAssocAction* pOwnedAction,
	                                           NcDbAssocStatus  previousStatus);
	static NcDbObjectId getInstanceFromDatabase(NcDbDatabase*   pDatabase,
	                                            bool            createIfDoesNotExist,
	                                            const NcString& dictionaryKey = _T(""));
	static NcDbObjectId getInstanceFromObject(const NcDbObjectId& owningObjectId,
	                                          bool                createIfDoesNotExist,
	                                          bool                addToTopLevelNetwork = true,
	                                          const NcString&     dictionaryKey        = _T(""));
	static Nano::ErrorStatus removeInstanceFromObject(const NcDbObjectId& owningObjectId,
	                                                  bool                alsoEraseIt,
	                                                  const NcString&     dictionaryKey = _T(""));
	static Nano::ErrorStatus removeInstanceFromDatabase(NcDbDatabase*   pDatabase,
	                                                    bool            alsoEraseIt,
	                                                    const NcString& dictionaryKey = _T(""));
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocNetworkIterator
class NRXDBGATE_EXPORT NcDbAssocNetworkIterator {
public:
	explicit NcDbAssocNetworkIterator(const NcDbAssocNetwork* pNetwork)
	    : mpNetwork(pNetwork), mIndex(-1)
	{
#ifdef ASSERT
		ASSERT(mpNetwork != NULL);
#endif
	}
	NcDbObjectId current() const
	{
		if (mpNetwork != NULL && 0 <= mIndex && mIndex < mpNetwork->getActions().length())
		{
			return mpNetwork->getActions()[mIndex];
		}
		else
		{
#ifdef ASSERT
			ASSERT(false);
#endif
			return NcDbObjectId::kNull;
		}
	}
	bool moveNext()
	{
		return mpNetwork != NULL ? ++mIndex < mpNetwork->getActions().length() : false;
	}
	void reset() { mIndex = -1; }
private:
	const NcDbAssocNetwork* const mpNetwork;
	int                           mIndex;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocNetworkSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocNetworkSurfaceActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocNetworkSurfaceActionBody);
	explicit NcDbAssocNetworkSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus getContinuity(NcDbAssocLoftedSurfaceActionBody::ProfileType type,
	                                int &continuity, NcString& expression = dummyString(),
	                                NcString& evaluatorId = dummyString() ) const;
	Nano::ErrorStatus setContinuity(NcDbAssocLoftedSurfaceActionBody::ProfileType type,
	                                int continuity, const NcString& expression = NcString(),
	                                const NcString& evaluatorId = NcString() );
	Nano::ErrorStatus getBulge(NcDbAssocLoftedSurfaceActionBody::ProfileType type,
	                           double &bulge, NcString& expression = dummyString(),
	                           NcString& evaluatorId = dummyString() ) const;
	Nano::ErrorStatus setBulge(NcDbAssocLoftedSurfaceActionBody::ProfileType type,
	                           double bulge, const NcString& expression = NcString(),
	                           const NcString& evaluatorId = NcString() );
	static Nano::ErrorStatus createInstance(const NcDbObjectId& resultingSurfaceId,
	                                        const NcArray<NcDbPathRef>& crossSections,
	                                        const NcArray<NcDbPathRef>& guideCurves,
	                                        const NcArray<int>& continuityArray,
	                                        const NcArray<double>& bulgeArray,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocOffsetSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocOffsetSurfaceActionBody : public NcDbAssocSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocOffsetSurfaceActionBody);
	explicit NcDbAssocOffsetSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus setDistance(double distance, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	double distance(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	static Nano::ErrorStatus createInstance(const NcDbObjectId& resultingSurfaceId,
	                                        const NcDbObjectId& inputSurfaceId,
	                                        double distance,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocPatchSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocPatchSurfaceActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocPatchSurfaceActionBody);
	explicit NcDbAssocPatchSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus setConstraintPoints( const NcArray<NcDbVertexRef> & constraintPoints);
	Nano::ErrorStatus setConstraintCurves( const NcArray<NcDbEdgeRef> & constraintCurves );
	Nano::ErrorStatus setContinuity(int continuity, const NcString& expression = NcString(),
	    const NcString& evaluatorId = NcString());
	int continuity(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	Nano::ErrorStatus getContinuityGripPoint ( NcGePoint3d&  gripPt) const;
	Nano::ErrorStatus setBulge(double bulge, const NcString& expression = NcString(),
	                           const NcString& evaluatorId = NcString());
	double bulge(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	static Nano::ErrorStatus createInstance(const NcDbObjectId& patchSurfaceId,
	                                        const NcArray<NcDbEdgeRef>& profileCurves,
	                                        const NcArray<NcDbEdgeRef>& constraintCurves,
	                                        const NcArray<NcDbVertexRef>&constraintPoints,
	                                        int nContinuity,
	                                        double dBulge,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId);
	static Nano::ErrorStatus createInstance(const NcDbObjectId& patchSurfaceId,
	                                        const NcArray<NcDbEdgeRef>& profileCurves,
	                                        const NcArray<NcDbEdgeRef>& constraintCurves,
	                                        const NcArray<NcDbVertexRef>&constraintPoints,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocPathActionParam
class NRXDBGATE_EXPORT NcDbAssocPathActionParam : public NcDbAssocCompoundActionParam {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocPathActionParam);
	explicit NcDbAssocPathActionParam(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	virtual Nano::ErrorStatus setEdgeRefArray(const NcArray<NcDbEdgeRef>& edgeRefs);
	virtual Nano::ErrorStatus updateEdgeRef(int edgeRefIndex, const NcDbEdgeRef& edgeRef);
	virtual Nano::ErrorStatus getEdgeRefArray(NcArray<NcArray<NcDbEdgeRef> >& edgeRefs) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocSimplePersSubentId
class NRXDBGATE_EXPORT NcDbAssocSimplePersSubentId : public NcDbAssocPersSubentId {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocSimplePersSubentId);
	explicit NcDbAssocSimplePersSubentId(NcDbSubentId subentId = kNullSubentId) : mSubentId(subentId) {}
	virtual int transientSubentCount(const NcDbEntity* pEntity) const { return !isNull() ? 1 : 0; }
	virtual NcDb::SubentType subentType(const NcDbEntity* pEntity) const { return mSubentId.type(); }
	virtual NcDbSubentId subentId(const NcDbEntity* pEntity) const { return mSubentId; }
	virtual bool isNull() const
	{
		return mSubentId.type() == NcDb::kNullSubentType;
	}
	virtual bool isEqualTo(const NcDbEntity* pEntity, const NcDbAssocPersSubentId* pOther) const
	{
		if (NcDbAssocPersSubentId::isEqualTo(pEntity, pOther))
			return false;
		const NcDbAssocSimplePersSubentId* const pOtherSimple = dynamic_cast<const NcDbAssocSimplePersSubentId*>(pOther);
		return mSubentId == pOtherSimple->mSubentId;
	}
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo);
private:
	NcDbSubentId mSubentId;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocPersSubentIdPE
class NRXDBGATE_EXPORT NcDbAssocPersSubentIdPE : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocPersSubentIdPE);
	virtual NcDbAssocPersSubentId* createNewPersSubent(NcDbEntity* pEntity,
	                                                   const class NcDbCompoundObjectId& compId,
	                                                   const NcDbSubentId& subentId)
	{
		return new NcDbAssocSimplePersSubentId(subentId);
	}
	virtual Nano::ErrorStatus getTransientSubentIds(const NcDbEntity*            pEntity,
	                                                const NcDbAssocPersSubentId* pPerSubentId,
	                                                NcArray<NcDbSubentId>&       subents) const;
	virtual Nano::ErrorStatus getAllSubentities(const NcDbEntity*      pEntity,
	                                            NcDb::SubentType       subentType,
	                                            NcArray<NcDbSubentId>& allSubentIds)
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus getEdgeVertexSubentities(const NcDbEntity*      pEntity,
	                                                   const NcDbSubentId&    edgeSubentId,
	                                                   NcDbSubentId&          startVertexSubentId,
	                                                   NcDbSubentId&          endVertexSubentId,
	                                                   NcArray<NcDbSubentId>& otherVertexSubentIds)
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus getSplineEdgeVertexSubentities(const NcDbEntity*      pEntity,
	                                                         const NcDbSubentId&    edgeSubentId,
	                                                         NcDbSubentId&          startVertexSubentId,
	                                                         NcDbSubentId&          endVertexSubentId,
	                                                         NcArray<NcDbSubentId>& controlPointSubentIds,
	                                                         NcArray<NcDbSubentId>& fitPointSubentIds)
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus getVertexSubentityGeometry(const NcDbEntity*   pEntity,
	                                                     const NcDbSubentId& vertexSubentId,
	                                                     NcGePoint3d&        vertexPosition)
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus getEdgeSubentityGeometry(const NcDbEntity*   pEntity,
	                                                   const NcDbSubentId& edgeSubentId,
	                                                   NcGeCurve3d*&       pEdgeCurve)
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus getFaceSubentityGeometry(const NcDbEntity*   pEntity,
	                                                   const NcDbSubentId& faceSubentId,
	                                                   NcGeSurface*&       pFaceSurface)
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus setVertexSubentityGeometry(NcDbEntity*         pEntity,
	                                                     const NcDbSubentId& vertexSubentId,
	                                                     const NcGePoint3d&  newVertexPosition)
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus setEdgeSubentityGeometry(NcDbEntity*         pEntity,
	                                                   const NcDbSubentId& edgeSubentId,
	                                                   const NcGeCurve3d*  pNewEdgeCurve)
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus setFaceSubentityGeometry(NcDbEntity*         pEntity,
	                                                   const NcDbSubentId& faceSubentId,
	                                                   const NcGeSurface*  pNewFaceSurface)
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus setSubentityGeometry(NcDbEntity*         pEntity,
	                                               const NcDbSubentId& subentId,
	                                               const NcDbEntity*   pNewSubentityGeometry)
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus getSubentTransFromStretchPoints(const NcDbEntity*   pEntity,
	                                                          const NcDbIntArray& indices,
	                                                          const NcGeVector3d& offset,
	                                                          NcArray<NcDbAssocSubentTransInfo>& aSubentTransInfos) const
	{
		  return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus getSubentTransFromGripPoints(const NcDbEntity*   pEntity,
	                                                       const NcDbIntArray& indices,
	                                                       const NcGeVector3d& offset,
	                                                       NcArray<NcDbAssocSubentTransInfo>& aSubentTransInfos) const
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus getSubentTransFromGripPoints(const NcDbEntity*       pEntity,
	                                                       const NcDbVoidPtrArray& gripAppData,
	                                                       const NcGeVector3d&     offset,
	                                                       NcArray<NcDbAssocSubentTransInfo>& aSubentTransInfos) const
	{
		return Nano::eNotImplementedYet;
	}
	virtual Nano::ErrorStatus getSubentGeometryXform(const NcDbEntity*        pEntity,
	                                                 const NcDbObjectIdArray& fullSubentPath,
	                                                 NcGeMatrix3d&            trans) const
	{
		trans.setToIdentity();
		return Nano::eOk;
	}
	virtual Nano::ErrorStatus mirrorPersSubent(const NcDbEntity*      pMirroredEntity,
	                                           NcDbAssocPersSubentId& persSubentIdToMirror)
	{
		return Nano::eOk;
	}
	virtual int getRigidSetState(const NcDbEntity* pEntity) { return kNotRigidSet; }
	virtual Nano::ErrorStatus getRigidSetTransform(const NcDbEntity* pEntity,
	                                               NcGeMatrix3d&     trans)
	{
		return Nano::eNotApplicable;
	}
	virtual Nano::ErrorStatus setRigidSetTransform(NcDbEntity*         pEntity,
	                                               const NcGeMatrix3d& trans)
	{
		return Nano::eNotApplicable;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocPlaneSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocPlaneSurfaceActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocPlaneSurfaceActionBody);
	explicit NcDbAssocPlaneSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	static Nano::ErrorStatus createInstance(const NcDbObjectId& resultingSurfaceId,
	                                        const NcDbPathRef& inputPath,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocRevolvedSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocRevolvedSurfaceActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocRevolvedSurfaceActionBody);
	explicit NcDbAssocRevolvedSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus setRevolveAngle(double angle, const NcString& expression = NcString(),
	                                  const NcString& evaluatorId = NcString());
	double revolveAngle(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	static Nano::ErrorStatus createInstance(const NcDbObjectId& resultingSurfaceId,
	                                        const NcDbPathRef& revolvePath,
	                                        const NcDbPathRef& axisPath,
	                                        double dAngle,
	                                        double dStartAngle,
	                                        const NcDbRevolveOptions& revolveOptions,
	                                        bool bFlipAxisDirection,
	                                        bool bEnabled,
	                                        NcDbObjectId& createdActionId);
};


//////////////////////////////////////////////////////////////////////////
// NcDbAssocSingleEdgePersSubentId
class NRXDBGATE_EXPORT NcDbAssocSingleEdgePersSubentId : public NcDbAssocPersSubentId {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocSingleEdgePersSubentId);
	virtual int transientSubentCount(const NcDbEntity* pEntity) const { return 1; }
	virtual NcDb::SubentType subentType(const NcDbEntity* pEntity) const { return NcDb::kEdgeSubentType; }
	virtual bool isNull() const { return false; }
	virtual bool isEqualTo(const NcDbEntity* pEntity, const NcDbAssocPersSubentId* pOther) const
	{
		return NcDbAssocPersSubentId::isEqualTo(pEntity, pOther);
	}
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocSweptSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocSweptSurfaceActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocSweptSurfaceActionBody);
	explicit NcDbAssocSweptSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus setScaleFactor(double scale, const NcString& expression = NcString(),
	                                 const NcString& evaluatorId = NcString());
	double scaleFactor(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	Nano::ErrorStatus setAlignAngle(double angle, const NcString& expression = NcString(),
	                                const NcString& evaluatorId = NcString());
	double alignAngle(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	Nano::ErrorStatus setTwistAngle(double angle, const NcString& expression = NcString(),
	                                const NcString& evaluatorId = NcString());
	double twistAngle(NcString& expression = dummyString(), NcString& evaluatorId = dummyString()) const;
	static Nano::ErrorStatus createInstance(const NcDbObjectId& resultingSurfaceId,
	                                        const NcDbPathRef& sweepProfile,
	                                        const NcDbPathRef& sweepPathProfile,
	                                        const NcDbSweepOptions& sweptOptions,
	                                        bool  bEnabled,
	                                        NcDbObjectId& createdActionId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocTrimSurfaceActionBody
class NRXDBGATE_EXPORT NcDbAssocTrimSurfaceActionBody : public NcDbAssocPathBasedSurfaceActionBody {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocTrimSurfaceActionBody);
	explicit NcDbAssocTrimSurfaceActionBody(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	Nano::ErrorStatus setTrimInfo(const NcArray<NcDbSurfaceTrimInfo> trimInfoArray, bool bAutoExtend);
	Nano::ErrorStatus makeTrimPermanent();
	Nano::ErrorStatus untrim();
	double getTrimmedArea() const;
	static Nano::ErrorStatus createInstance(const NcDbObjectId& resultingSurfaceId,
	                                        const NcArray<NcDbSurfaceTrimInfo>& trimInfo,
	                                        bool bAutoExtend,
	                                        bool bEnabled,
	                                        NcDbObjectIdArray& createdActionIds);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocValueDependency
class NRXDBGATE_EXPORT NcDbAssocValueDependency : public NcDbAssocDependency {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocValueDependency);
	explicit NcDbAssocValueDependency(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	const NcString& valueName() const;
	Nano::ErrorStatus setValueName(const NcString& newValueName);
	Nano::ErrorStatus getDependentOnObjectValue(NcDbEvalVariant& objectValue) const;
	Nano::ErrorStatus setDependentOnObjectValue(const NcDbEvalVariant& newObjectValue);
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocValueProviderPE
class NRXDBGATE_EXPORT NcDbAssocValueProviderPE : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocValueProviderPE);
	virtual bool canGetValue(const NcDbObject* pObject, const NcString& valueName) { return true; }
	virtual bool canSetValue(const NcDbObject* pObject, const NcString& valueName) { return false; }
	virtual Nano::ErrorStatus getValue(const NcDbObject* pObject,
	                                   const NcString&   valueName,
	                                   NcDbEvalVariant&  value) = NULL;
	virtual Nano::ErrorStatus setValue(NcDbObject*            pObject,
	                                   const NcString&        valueName,
	                                   const NcDbEvalVariant& newValue)
	{
		return Nano::eNotHandled;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocVariable
class NRXDBGATE_EXPORT NcDbAssocVariable : public NcDbAssocAction {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocVariable);
	explicit NcDbAssocVariable(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	const NcString& name() const;
	const NcString& expression() const;
	const NcDbEvalVariant& value() const;
	const NcString& description() const;
	Nano::ErrorStatus setName(const NcString& newName, bool updateReferencingExpressions);
	bool isAnonymous() const;
	NcDbObjectId findObjectByName(const NcString&  objectName,
	                              const NcRxClass* pObjectClass) const;
	Nano::ErrorStatus validateNameAndExpression(const NcString& nameToValidate,
	                                            const NcString& expressionToValidate,
	                                            NcString&       errorMessage) const;
	Nano::ErrorStatus setExpression(const NcString& newExpression,
	                                const NcString& evaluatorId,
	                                bool checkForCyclicalDependencies,
	                                bool updateDependenciesOnReferencedSymbols,
	                                NcString& errorMessage = NcString(),
	                                bool silentMode = false);
	const NcString& evaluatorId() const;
	Nano::ErrorStatus setEvaluatorId(const NcString& evalId);
	Nano::ErrorStatus setValue(const NcDbEvalVariant& newValue);
	Nano::ErrorStatus setDescription(const NcString& newDescription);
	bool     isMergeable          () const;
	bool     mustMerge            () const;
	NcString mergeableVariableName() const;
	void setIsMergeable(bool isMerg, bool mustMerg = false, const NcString& mergeableVariableName = NcString());
	Nano::ErrorStatus evaluateExpression(NcDbEvalVariant& evaluatedExpressionValue,
	                                     NcString&        errorMessage = NcString()) const;
	Nano::ErrorStatus evaluateExpression(NcDbObjectIdArray&        objectIds,
	                                     NcArray<NcDbEvalVariant>& objectValues,
	                                     NcDbEvalVariant&          evaluatedExpressionValue,
	                                     NcString&                 errorMessage = NcString()) const;
	static Nano::ErrorStatus evaluateExpression(const NcString&     expression,
	                                            const NcString&     evaluatorId,
	                                            const NcDbObjectId& networkId,
	                                            NcDbEvalVariant&    evaluatedExpressionValue,
	                                            NcString&           assignedToSymbolName,
	                                            NcString&           errorMessage = NcString());
	static void addGlobalCallback(class NcDbAssocVariableCallback* pCallback);
	static void removeGlobalCallback(class NcDbAssocVariableCallback* pCallback);
	static class NcDbAssocVariableCallback* globalCallback();
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocVariableCallback
class NcDbAssocVariableCallback {
public:
	NcDbAssocVariableCallback() {}
	virtual ~NcDbAssocVariableCallback() {}
	virtual bool canBeErased(const NcDbAssocVariable* pVariable) = NULL;
	virtual Nano::ErrorStatus validateNameAndExpression(const NcDbAssocVariable* pVariable,
	                                                    const NcString&          nameToValidate,
	                                                    const NcString&          expressionToValidate,
	                                                    NcString&                errorMessage) = NULL;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAssocVertexActionParam
class NRXDBGATE_EXPORT NcDbAssocVertexActionParam : public NcDbAssocActionParam {
public:
	NCRX_DECLARE_MEMBERS(NcDbAssocVertexActionParam);
	explicit NcDbAssocVertexActionParam(NcDbAssocCreateImpObject createImpObject = kNcDbAssocCreateImpObject);
	virtual Nano::ErrorStatus setVertexRef(const NcDbVertexRef &vertexRef, bool isReadDep, bool isWriteDep);
	virtual Nano::ErrorStatus getVertexRef ( NcDbVertexRef &vertexRef ) const;
	Nano::ErrorStatus getDependentOnCompoundObject(NcDbCompoundObjectId& compoundId) const;
};

NRXDBGATE_EXPORT NcDbAssocAction* ncdbAssocGetCurrentlyEvaluatedActionPointer(const NcDbDatabase*);
Nano::ErrorStatus ncdbGetDimAssocId(NcDbObjectId dimId, NcDbObjectId& dimAssocId);
Nano::ErrorStatus ncdbGetDimAssocIds(NcDbObjectId entId, NcDbObjectIdArray& dimAssocIds);
bool ncdbIsTransSpatial(const NcDbFullSubentPath& idPath);
Nano::ErrorStatus ncdbPostDimAssoc(NcDbObjectId dimId, NcDbDimAssoc* pDimAssoc,
                                   NcDbObjectId& dimAssocId, bool isActive = true);
Nano::ErrorStatus ncdbUpdateAllDimensions(NcDbDatabase* pDb);
Nano::ErrorStatus ncdbUpdateDimension(NcDbObjectId dimId);

//////////////////////////////////////////////////////////////////////////
// NcDbAssocObjectPointer
template<class NCDB_CLASS> class NcDbAssocObjectPointer {
public:
	NcDbAssocObjectPointer(
	    NcDbObjectId                   objectId,
	    NcDb::OpenMode                 openMode,
	    bool                           openErased = false,
	    bool                           openOnLockedLayer = false);
	NcDbAssocObjectPointer(
	    NcDbAssocAction*               pActionBeingEvaluated,
	    NcDbObjectId                   objectId,
	    NcDb::OpenMode                 openMode,
	    bool                           openErased = false,
	    bool                           openOnLockedLayer = false);
	NcDbAssocObjectPointer(
	    const NcDbAssocActionBody*     pActionBodyBeingEvaluated,
	    NcDbObjectId                   objectId,
	    NcDb::OpenMode                 openMode,
	    bool                           openErased = false,
	    bool                           openOnLockedLayer = false);
	NcDbAssocObjectPointer(
	    const NcDbAssocDependency*     pDependencyBeingEvaluated,
	    NcDbObjectId                   objectId,
	    NcDb::OpenMode                 openMode,
	    bool                           openErased = false,
	    bool                           openOnLockedLayer = false);
	NcDbAssocObjectPointer(
	    const NcDbAssocDependencyBody* pDependencyBodyBeingEvaluated,
	    NcDbObjectId                   objectId,
	    NcDb::OpenMode                 openMode,
	    bool                           openErased = false,
	    bool                           openOnLockedLayer = false);
	NcDbAssocObjectPointer(
	    NcDbAssocAction*               pActionBeingEvaluated,
	    NCDB_CLASS*                    pObject);
	NcDbAssocObjectPointer(
	    const NcDbAssocActionBody*     pActionBodyBeingEvaluated,
	    NCDB_CLASS*                    pObject);
	~NcDbAssocObjectPointer();
	Nano::ErrorStatus openStatus() const;
	bool isSubstituteObject() const { return mpSubstituteObject != NULL; }
	const NCDB_CLASS* operator->() const { return mpObject; }
	NCDB_CLASS* operator->() { return mpObject; }
	operator const NCDB_CLASS*() const { return mpObject; }
	operator NCDB_CLASS*() { return mpObject; }
private:
	NcDbAssocAction* const               mpActionBeingEvaluated;
	const NcDbAssocActionBody* const     mpActionBodyBeingEvaluated;
	const NcDbAssocDependency* const     mpDependencyBeingEvaluated;
	const NcDbAssocDependencyBody* const mpDependencyBodyBeingEvaluated;
	const NcDbObjectId                   mObjectId;
	NcDbSmartObjectPointer<NCDB_CLASS>   mObjectPtr;
	NCDB_CLASS*                          mpObject;
	NcDbObject*                          mpSubstituteObject;
	Nano::ErrorStatus                    mSubstituteObjectErrorStatus;
private:
	void setup(NcDbAssocAction* pActionBeingEvaluated,
	           NcDb::OpenMode   openMode,
	           bool             openErased,
	           bool             openOnLockedLayer);
	NcDbAssocObjectPointer();
	NcDbAssocObjectPointer(const NcDbAssocObjectPointer&);
	NcDbAssocObjectPointer& operator = (const NcDbAssocObjectPointer&);
};

NRXDBGATE_EXPORT bool isDraggingProvidingSubstituteObjects(const NcDbAssocEvaluationCallback* pEvaluationCallback);

#endif // __ASSOCIATIVITY_H__
