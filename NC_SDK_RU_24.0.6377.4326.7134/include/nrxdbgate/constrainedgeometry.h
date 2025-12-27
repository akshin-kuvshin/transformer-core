#pragma once

#include "nrxdbgate_impexp.h"
class NcConstrainedRigidSet;
class NcConstrainedGeometry;

struct NcDbAssocTransInfo
{
	enum TransType
	{
		kGeneral = 0,
		kScaling,
		kRadius,
		kMajorRadius,
		kMinorRadius,
		kFixedRadius,
		kFixed,
		kFixWhenPossible,
		kNone,
	};
	
	NcDbAssocTransInfo() : mRadius(-1.0), mTransType(kGeneral)
	{}
	
	TransType mTransType;
	
	NcGeMatrix3d mTrans;
	
	double mRadius;
};


struct NcDbAssocSubentTransInfo : NcDbAssocTransInfo
{
	NcDbSubentId mSubentId;
};


enum RigidSetType
{
	kNotRigidSet = 0,
	kScalableRigidSet,
	kNonScalableRigidSet
};


struct NcConstrainedGeometryDraggingInfo : NcDbAssocTransInfo
{
	NcDbFullSubentPathArray maGeomFullSubentPaths;
	NcArray<NcConstrainedGeometry *> maDraggingGeometries;
	NRXDBGATE_EXPORT static const NcString& getKey();
};

//////////////////////////////////////////////////////////////////////////
// NcConstraintGroupNode
class NRXDBGATE_EXPORT NcConstraintGroupNode : public NcRxObject,
                                        public NcHeapOperators {
public:
	NCRX_DECLARE_MEMBERS(NcConstraintGroupNode);
	virtual ~NcConstraintGroupNode();
	enum GroupNodeId
	{
		kNullGroupNodeId = 0
	};
	NcConstraintGroupNodeId nodeId() const;
	NcDbObjectId owningConstraintGroupId()const;
protected:
	NcConstraintGroupNode();
	friend class NcDbAssoc2dConstraintGroupEvalHelper;
	friend class NcDbAssoc2dConstaintGroupCloningHelper;
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedGeometry
class NRXDBGATE_EXPORT NcConstrainedGeometry :  public NcConstraintGroupNode {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedGeometry);
	virtual bool isReadOnly() const;
	NcDbObjectId geomDependencyId() const;
	NcConstrainedRigidSet* getOwningRigidSet() const;
	Nano::ErrorStatus getConnectedConstraints(NcArray<NcGeomConstraint*>& apConstraints) const;
	Nano::ErrorStatus getCommonConstraints(NcConstrainedGeometry* pOtherConsGeom, NcArray<NcGeomConstraint*>& apConstraints) const;
	Nano::ErrorStatus getConnectedGeometries(NcArray<NcConstrainedGeometry*>& apConsGeoms) const;
	Nano::ErrorStatus getFullSubentPaths(NcDbFullSubentPathArray& subentPaths) const;
protected:
	NcConstrainedGeometry(){}
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedPoint
class NRXDBGATE_EXPORT NcConstrainedPoint: public NcConstrainedGeometry {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedPoint);
	explicit NcConstrainedPoint(bool bCreateImp = true);
	NcConstrainedPoint(NcDbObjectId geomDependencyId);
	virtual NcGePoint3d point() const ;
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedImplicitPoint
class NRXDBGATE_EXPORT NcConstrainedImplicitPoint: public NcConstrainedPoint {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedImplicitPoint);
	enum ImplicitPointType
	{
		kStartImplicit = 0,
		kEndImplicit,
		kMidImplicit,
		kCenterImplicit,
		kDefineImplicit
	};
	NcConstrainedImplicitPoint();
	NcConstrainedImplicitPoint(NcConstraintGroupNodeId constrCurvId,ImplicitPointType ptype, int index = -1);
	ImplicitPointType       pointType()  const;
	int                     pointIndex() const;
	NcConstraintGroupNodeId constrainedCurveId() const;
	virtual NcGePoint3d point() const;
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedCurve
class NRXDBGATE_EXPORT NcConstrainedCurve :  public NcConstrainedGeometry {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedCurve);
	virtual bool isBounded() const;
	virtual void getConstrainedImplicitPoints(NcArray<NcConstrainedImplicitPoint*>& apImplicitPoints) const;
protected:
	NcConstrainedCurve(){}
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedLine
class NRXDBGATE_EXPORT NcConstrainedLine: public NcConstrainedCurve {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedLine);
	explicit NcConstrainedLine(bool bCreateImp = true);
	NcConstrainedLine(NcDbObjectId geomDependencyId);
	NcGePoint3d pointOnLine() const;
	NcGeVector3d direction() const;
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedConstructionLine
class NRXDBGATE_EXPORT NcConstrainedConstructionLine: public NcConstrainedLine {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedConstructionLine);
protected:
	NcConstrainedConstructionLine();
};

//////////////////////////////////////////////////////////////////////////
// NcConstrained2PointsConstructionLine
class NRXDBGATE_EXPORT NcConstrained2PointsConstructionLine: public NcConstrainedConstructionLine {
public:
	NCRX_DECLARE_MEMBERS(NcConstrained2PointsConstructionLine);
	NcConstrained2PointsConstructionLine();
	NcConstrained2PointsConstructionLine(const NcGePoint3d& point1, const NcGePoint3d& point2);
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedDatumLine
class NRXDBGATE_EXPORT NcConstrainedDatumLine: public NcConstrainedConstructionLine {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedDatumLine);
	NcConstrainedDatumLine();
	NcConstrainedDatumLine(const NcGePoint3d& pointOnLine, const NcGeVector3d& direction);
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedBoundedLine
class NRXDBGATE_EXPORT NcConstrainedBoundedLine: public NcConstrainedLine {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedBoundedLine);
	NcConstrainedBoundedLine();
	NcConstrainedBoundedLine(NcDbObjectId geomDependencyId, bool bRay);
	bool isRay() const;
	NcGePoint3d startPoint() const;
	NcGePoint3d endPoint() const;
	NcGePoint3d midPoint() const;
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedCircle
class NRXDBGATE_EXPORT NcConstrainedCircle: public NcConstrainedCurve {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedCircle);
	explicit NcConstrainedCircle(bool bCreateImp = true);
	NcConstrainedCircle(NcDbObjectId geomDependencyId);
	double radius() const;
	NcGePoint3d centerPoint() const;
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedArc
class NRXDBGATE_EXPORT NcConstrainedArc: public NcConstrainedCircle {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedArc);
	NcConstrainedArc();
	NcConstrainedArc(NcDbObjectId geomDependencyId);
	NcGePoint3d startPoint() const;
	NcGePoint3d endPoint() const;
	NcGePoint3d midPoint() const;
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedEllipse
class NRXDBGATE_EXPORT NcConstrainedEllipse: public NcConstrainedCurve {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedEllipse);
	NcConstrainedEllipse(bool bCreateImp = true);
	NcConstrainedEllipse(NcDbObjectId geomDependencyId);
	NcGeVector3d direction() const;
	double majorRadius() const;
	double minorRadius() const;
	NcGePoint3d centerPoint() const;
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedBoundedEllipse
class NRXDBGATE_EXPORT NcConstrainedBoundedEllipse : public NcConstrainedEllipse {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedBoundedEllipse);
	NcConstrainedBoundedEllipse();
	NcConstrainedBoundedEllipse(NcDbObjectId geomDependencyId);
	NcGePoint3d startPoint() const;
	NcGePoint3d endPoint() const;
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedSpline
class NRXDBGATE_EXPORT NcConstrainedSpline: public NcConstrainedCurve {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedSpline);
	NcConstrainedSpline();
	NcConstrainedSpline(NcDbObjectId geomDependencyId, const NcGeNurbCurve3d& spline);
	const NcGeNurbCurve3d nurbSpline() const;
	int numOfDefinePoints() const;
	NcGePoint3d definePointAt(int index) const;
};

//////////////////////////////////////////////////////////////////////////
// NcConstrainedRigidSet
class NRXDBGATE_EXPORT NcConstrainedRigidSet : public NcConstrainedGeometry {
public:
	NCRX_DECLARE_MEMBERS(NcConstrainedRigidSet);
	NcConstrainedRigidSet();
	NcConstrainedRigidSet(bool bScalable, const NcGeMatrix3d& trans);
	int                      numOfConstrainedGeoms() const;
	NcConstrainedGeometry*   getConstrainedGeomAt(int index) const;
	NcGeMatrix3d             transform() const;
};

//////////////////////////////////////////////////////////////////////////
// NcGeomConstraint
class NRXDBGATE_EXPORT NcGeomConstraint : public NcConstraintGroupNode {
public:
	NCRX_DECLARE_MEMBERS(NcGeomConstraint);
	enum GeomConstraintType
	{
		kHorizontal    = 0,
		kVertical         ,
		kParallel         ,
		kPerpendicular    ,
		kNormal           ,
		kColinear         ,
		kCoincident       ,
		kConcentric       ,
		kTangent          ,
		kEqualRadius      ,
		kEqualLength      ,
		kSymmetric            ,
		kG2Smooth         ,
		kFix
	};
	virtual Nano::ErrorStatus getConnectedGeometries(NcArray<NcConstrainedGeometry*>& apConsGeoms) const;
	virtual Nano::ErrorStatus getConnectedHelpParameters(NcArray<NcHelpParameter*>& apHelpParameters) const;
	virtual NcHelpParameter*  getConnectedHelpParameterFor(const NcConstrainedGeometry* pConsGeom) const;
	NcCompositeConstraint*    getOwningCompositeConstraint() const;
	Nano::ErrorStatus deactivate();
	Nano::ErrorStatus reactivate();
	bool isActive() const;
	bool isImplied() const;
	void setIsImplied(bool yesNo);
	bool isInternal() const;
	bool isEnabled() const;
protected:
	NcGeomConstraint(){};
};

//////////////////////////////////////////////////////////////////////////
// NcExplicitConstraint
class NRXDBGATE_EXPORT NcExplicitConstraint : public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcExplicitConstraint);
	NcDbObjectId valueDependencyId() const;
	NcDbObjectId dimDependencyId() const;
	Nano::ErrorStatus setDimDependencyId(const NcDbObjectId& dimDependencyId);
	Nano::ErrorStatus getMeasuredValue(double&) const;
protected:
	NcExplicitConstraint(){};
};

//////////////////////////////////////////////////////////////////////////
// NcDistanceConstraint
class NRXDBGATE_EXPORT NcDistanceConstraint: public NcExplicitConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcDistanceConstraint);
	enum DirectionType
	{
		kNotDirected         = 0,
		kFixedDirection         ,
		kPerpendicularToLine    ,
		kParallelToLine
	};
	NcDistanceConstraint();
	NcDistanceConstraint(const NcGeVector3d& direction);
	NcDistanceConstraint(const NcConstraintGroupNodeId consLineId, DirectionType type = kPerpendicularToLine);
	DirectionType directionType() const;
	NcGeVector3d                    direction()           const;
	NcConstraintGroupNodeId         constrainedLineId()   const;
};

//////////////////////////////////////////////////////////////////////////
// NcAngleConstraint
class NRXDBGATE_EXPORT NcAngleConstraint: public NcExplicitConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcAngleConstraint);
	enum SectorType
	{
		kParallelAntiClockwise = 0,
		kAntiParallelClockwise    ,
		kParallelClockwise        ,
		kAntiParallelAntiClockwise
	};
	NcAngleConstraint();
	NcAngleConstraint(NcAngleConstraint::SectorType type);
	SectorType sectorType() const;
	static void setAngleMultiplier(double multiplier);
	static double angleMultiplier();
};

//////////////////////////////////////////////////////////////////////////
// Nc3PointAngleConstraint
class NRXDBGATE_EXPORT Nc3PointAngleConstraint: public NcAngleConstraint {
public:
	NCRX_DECLARE_MEMBERS(Nc3PointAngleConstraint);
	Nc3PointAngleConstraint();
	Nc3PointAngleConstraint(NcAngleConstraint::SectorType type);
};

//////////////////////////////////////////////////////////////////////////
// NcRadiusDiameterConstraint
class NRXDBGATE_EXPORT NcRadiusDiameterConstraint : public NcExplicitConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcRadiusDiameterConstraint);
	enum RadiusDiameterConstrType
	{
		kCircleRadius   = 0,
		kCircleDiameter    ,
		kMinorRadius       ,
		kMajorRadius
	};
	NcRadiusDiameterConstraint();
	NcRadiusDiameterConstraint(RadiusDiameterConstrType type);
	RadiusDiameterConstrType constrType() const;
};

//////////////////////////////////////////////////////////////////////////
// NcHelpParameter
class NRXDBGATE_EXPORT NcHelpParameter : public NcConstraintGroupNode {
public:
	NCRX_DECLARE_MEMBERS(NcHelpParameter);
	NcHelpParameter();
	Nano::ErrorStatus getConnectedGeometry(NcConstrainedGeometry*& pGeometry) const;
	Nano::ErrorStatus getConnectedConstraint(NcGeomConstraint*& pConstraint) const;
	Nano::ErrorStatus getConnectedEqualparamConstraints(NcArray<NcEqualHelpParameterConstraint*>& apEqualParamConstrs) const;
	double getValue() const;
};

//////////////////////////////////////////////////////////////////////////
// NcCompositeConstraint
class NRXDBGATE_EXPORT NcCompositeConstraint : public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcCompositeConstraint);
	Nano::ErrorStatus getOwnedConstraints(NcArray<NcGeomConstraint*>& apSubConstraints) const;
protected:
	NcCompositeConstraint(){}
};

//////////////////////////////////////////////////////////////////////////
// NcPerpendicularConstraint
class NRXDBGATE_EXPORT NcPerpendicularConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcPerpendicularConstraint);
	NcPerpendicularConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcNormalConstraint
class NRXDBGATE_EXPORT NcNormalConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcNormalConstraint);
	NcNormalConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcPointCurveConstraint
class NRXDBGATE_EXPORT NcPointCurveConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcPointCurveConstraint);
	NcPointCurveConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcColinearConstraint
class NRXDBGATE_EXPORT NcColinearConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcColinearConstraint);
	NcColinearConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcPointCoincidenceConstraint
class NRXDBGATE_EXPORT NcPointCoincidenceConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcPointCoincidenceConstraint);
	NcPointCoincidenceConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcConcentricConstraint
class NRXDBGATE_EXPORT NcConcentricConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcConcentricConstraint);
	NcConcentricConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcCenterPointConstraint
class NRXDBGATE_EXPORT NcCenterPointConstraint: public NcConcentricConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcCenterPointConstraint);
};

//////////////////////////////////////////////////////////////////////////
// NcTangentConstraint
class NRXDBGATE_EXPORT NcTangentConstraint : public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcTangentConstraint);
	NcTangentConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcEqualRadiusConstraint
class NRXDBGATE_EXPORT NcEqualRadiusConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcEqualRadiusConstraint);
	NcEqualRadiusConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcEqualDistanceConstraint
class NRXDBGATE_EXPORT NcEqualDistanceConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcEqualDistanceConstraint);
	NcEqualDistanceConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcEqualLengthConstraint
class NRXDBGATE_EXPORT NcEqualLengthConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcEqualLengthConstraint);
	NcEqualLengthConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcParallelConstraint
class NRXDBGATE_EXPORT NcParallelConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcParallelConstraint);
	NcParallelConstraint(bool bCreateImp = true);
};

//////////////////////////////////////////////////////////////////////////
// NcHorizontalConstraint
class NRXDBGATE_EXPORT NcHorizontalConstraint: public NcParallelConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcHorizontalConstraint);
	NcHorizontalConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcVerticalConstraint
class NRXDBGATE_EXPORT NcVerticalConstraint: public NcParallelConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcVerticalConstraint);
	NcVerticalConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcEqualCurvatureConstraint
class NRXDBGATE_EXPORT NcEqualCurvatureConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcEqualCurvatureConstraint);
	NcEqualCurvatureConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcSymmetricConstraint
class NRXDBGATE_EXPORT NcSymmetricConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcSymmetricConstraint);
	NcSymmetricConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcMidPointConstraint
class NRXDBGATE_EXPORT NcMidPointConstraint: public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcMidPointConstraint);
	NcMidPointConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcFixedConstraint
class NRXDBGATE_EXPORT NcFixedConstraint : public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcFixedConstraint);
	NcFixedConstraint();
};

//////////////////////////////////////////////////////////////////////////
// NcEqualHelpParameterConstraint
class NRXDBGATE_EXPORT NcEqualHelpParameterConstraint : public NcGeomConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcEqualHelpParameterConstraint);
	NcEqualHelpParameterConstraint();
	Nano::ErrorStatus getEqualHelpParameters(NcHelpParameter*& pHelpParameter1, NcHelpParameter*& pHelpParameter2) const;
};

//////////////////////////////////////////////////////////////////////////
// NcG2SmoothConstraint
class NRXDBGATE_EXPORT NcG2SmoothConstraint : public NcCompositeConstraint {
public:
	NCRX_DECLARE_MEMBERS(NcG2SmoothConstraint);
	NcG2SmoothConstraint();
};
