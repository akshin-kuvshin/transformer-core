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

#ifndef __BOUNDARY_H__
#define __BOUNDARY_H__

#include "nrxdbgate_impexp.h"
class NcBrTraverserData;
class NcBrImpTraverser;
class NcBrHit;
class NcBrBrep;
class NcBrBrepData;
class NcBrImpEntity;
class NcBrEdge;
class NcBrFace;
class NcBrShell;
class NcBrVertex;
class NcBrImpMeshEntity;
class NcBrElement2dData;
class NcBrLoopEdgeTraverser;
class NcBrLoop;
class NcBrVertexEdgeTraverser;
class NcBrMesh2dElement2dTraverser;
class NcBrNode;
class NcBrShellFaceTraverser;
class NcBrHitData;
class NcBrImpHit;
class NcBrVertexLoopTraverser;
class NcBrImpMeshControl;
class NcBrMesh2dControl;
class NcBrEntity;
class NcBrMesh2dData;
class NcBrNodeData;

typedef NcBrHitData NcBrHitPath;

struct NcBr
{
    enum ErrorStatus    { eOk                   = 0,
                          eNotImplementedYet    = Nano::eNotImplementedYet, 
                          eNotApplicable        = Nano::eNotApplicable, 
                          eInvalidInput         = Nano::eInvalidInput, 
                          eOutOfMemory          = Nano::eOutOfMemory, 
                          eNullObjectPointer    = Nano::eUnrecoverableErrors, 
                          eWrongObjectType      = Nano::eWrongObjectType, 
                          eWrongSubentityType   = Nano::eWrongSubentityType,
                          eNullObjectId         = Nano::eNullObjectId, 
                          eNullSubentityId      = Nano::eInvalidIndex, 
                          eObjectIdMismatch     = Nano::eWrongDatabase, 
                          eTopologyMismatch     = Nano::eWrongDatabase, 
                          eUnsuitableGeometry   = Nano::eAmbiguousOutput, 
                          eMissingGeometry      = Nano::eDegenerateGeometry, 
                          eMissingSubentity     = Nano::eNotInDatabase, 
                          eInvalidObject        = Nano::eUnrecoverableErrors, 
                          eAmbiguousOutput      = Nano::eAmbiguousOutput,
                          eBrepChanged          = 3008,
                          eUnsuitableTopology   = 3013,
                          eDegenerateTopology	= 3020,
                          eUninitialisedObject  = 3021
	};

    enum Relation       { kUnknown              = 0,
                          kOutside              = 1,
                          kInside               = 2,
                          kBoundary             = 3,
                          kCoincident           = 4,
                          kTangent              = 5,
                          kIntersect            = 6
                        };

    enum Element2dShape { kDefault              = 0,
                          kAllPolygons          = 1,
                          kAllQuadrilaterals    = 2,
                          kAllTriangles         = 3
	                    };

	enum LoopType       { kUnclassified         = 0,
                          kExterior             = 1,
                           kInterior            = 2,
                          kWinding              = 3,
                          kLoopUnclassified     = kUnclassified,
                          kLoopExterior         = kExterior,
                          kLoopInterior         = kInterior,
                          kLoopWinding          = kWinding
                          };

    enum ValidationLevel { kFullValidation      = 0,
                           kNoValidation        = 1
                         };

    enum ShellType      { kShellUnclassified    = 0,
                          kShellExterior        = 1,
                          kShellInterior        = 2
                        };
};

typedef NcBr::ErrorStatus       NcBrErrorStatus;
typedef NcBr::Relation          NcBrRelation;
typedef NcBr::Element2dShape    NcBrElement2dShape;
typedef NcBr::LoopType          NcBrLoopType;
typedef NcBr::ValidationLevel   NcBrValidationLevel;
typedef NcBr::ShellType         NcBrShellType;

struct NcBrMassProps
{
	double          mVolume;
	double          mMass;
	NcGePoint3d     mCentroid;
	double          mRadiiGyration[3];
	double          mMomInertia[3];
	double          mProdInertia[3];
	double          mPrinMoments[3];
	NcGeVector3d    mPrinAxes[3];
};

//////////////////////////////////////////////////////////////////////////
// NcBrMeshControl
class NRXDBGATE_EXPORT NcBrMeshControl : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcBrMeshControl);
	virtual ~NcBrMeshControl();
	NRX::Boolean      isEqualTo(const NcRxObject* other) const;
	NcBr::ErrorStatus   setMaxSubdivisions(const NRX::UInt32& maxSubs =*(NRX::UInt32*)NULL);
	NcBr::ErrorStatus   getMaxSubdivisions(NRX::UInt32& maxSubs) const;
	NcBr::ErrorStatus   setMaxNodeSpacing(const double& maxNodeSpace =*(double*)NULL);
	NcBr::ErrorStatus   getMaxNodeSpacing(double& maxNodeSpace) const;
	NcBr::ErrorStatus   setAngTol(const double& angTol =*(double*)NULL);
	NcBr::ErrorStatus   getAngTol(double& angTol) const;
	NcBr::ErrorStatus   setDistTol(const double& distTol =*(double*)NULL);
	NcBr::ErrorStatus   getDistTol(double& distTol) const;
protected:
	NcBrMeshControl();
	NcBrMeshControl(const NcBrMeshControl& src);
	NcBrMeshControl& operator = (const NcBrMeshControl& src);
};

//////////////////////////////////////////////////////////////////////////
// NcBrMesh2dControl
class NRXDBGATE_EXPORT NcBrMesh2dControl : public NcBrMeshControl {
public:
	NCRX_DECLARE_MEMBERS(NcBrMesh2dControl);
	NcBrMesh2dControl();
	NcBrMesh2dControl(const NcBrMesh2dControl& src);
	~NcBrMesh2dControl();
	NcBrMesh2dControl& operator = (const NcBrMesh2dControl& src);
	NcBr::ErrorStatus   setMaxAspectRatio(const double& maxAspectRatio =*(double*)NULL);
	NcBr::ErrorStatus   getMaxAspectRatio(double& maxAspectRatio) const;
	NcBr::ErrorStatus   setElementShape (const NcBr::Element2dShape& elementShape =*(NcBr::Element2dShape*)NULL);
	NcBr::ErrorStatus   getElementShape (NcBr::Element2dShape& elementShape) const;
	NcBr::ErrorStatus   setMinSubdivisionsInU(const NRX::UInt32& minSubsU =*(NRX::UInt32*)NULL);
	NcBr::ErrorStatus   getMinSubdivisionsInU(NRX::UInt32& minSubsU) const;
	NcBr::ErrorStatus   setMinSubdivisionsInV(const NRX::UInt32& minSubsV =*(NRX::UInt32*)NULL);
	NcBr::ErrorStatus   getMinSubdivisionsInV(NRX::UInt32& minSubsV) const;
};

struct NRXDBGATE_EXPORT pair {
	NcBrEntity* first;
	NcBrMesh2dControl second;
	pair();
	pair(const NcBrEntity*& a, const NcBrMesh2dControl& b) : first((NcBrEntity*)a), second(b) {}
};

inline ::pair
make_pair(const NcBrEntity*& entity, const NcBrMesh2dControl& control)
{ return ::pair(entity, control); }

typedef ::pair value_type;
typedef void iterator;

//////////////////////////////////////////////////////////////////////////
// NcBrTraverser
class OdBrTraverser;
class NRXDBGATE_EXPORT NcBrTraverser : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcBrTraverser);
	NcBrTraverser(OdBrTraverser* _object);

	virtual ~NcBrTraverser();
	NRX::Boolean      isEqualTo(const NcRxObject* other) const;
	NRX::Boolean      isNull() const;
	NRX::Boolean      done() const;
	NcBr::ErrorStatus next();
	NcBr::ErrorStatus restart();
	NcBr::ErrorStatus setValidationLevel(const NcBr::ValidationLevel& =*(NcBr::ValidationLevel*)NULL);
	NcBr::ErrorStatus getValidationLevel(NcBr::ValidationLevel& validationLevel) const;
	NRX::Boolean      brepChanged() const;
	NcBr::ErrorStatus set(NcBrTraverserData* traverserData);
	NcBr::ErrorStatus get(NcBrTraverserData*& traverserData) const;

public:
	OdBrTraverser* native() const;

protected:
	NcBrTraverser();
	NcBrTraverser(const NcBrTraverser& src);
	NcBrTraverser& operator = (const NcBrTraverser& src);
	OdBrTraverser* m_pOdImpl;
};

//////////////////////////////////////////////////////////////////////////
// NcBrEntity
class OdBrEntity;
class NRXDBGATE_EXPORT NcBrEntity : public NcRxObject {

public:
	NCRX_DECLARE_MEMBERS(NcBrEntity);
	NcBrEntity(OdBrEntity* _object) : NcRxObject(NULL)
	{
		m_pOdImpl = _object;
	}

	virtual ~NcBrEntity();
	NRX::Boolean      isEqualTo(const NcRxObject* other) const;
	NRX::Boolean      isNull() const;
	NcBr::ErrorStatus   setSubentPath(NcDbFullSubentPath& subpath);
	NcBr::ErrorStatus   getSubentPath(NcDbFullSubentPath& subPath) const;
	NRX::Boolean        checkEntity() const;
	void*                getEntity() const;
	NcBr::ErrorStatus    setEntity(void* pData,
	                               NcDbFullSubentPath& subPath =*(NcDbFullSubentPath*)NULL);
	NcBr::ErrorStatus   getBoundBlock(NcGeBoundBlock3d& block) const;
	NcBr::ErrorStatus   getPointContainment(const NcGePoint3d& point,
	                                        NcGe::PointContainment& containment,
	                                        NcBrEntity*& container) const;
	NcBr::ErrorStatus   getLineContainment(const NcGeLinearEnt3d& line,
	                                       const NRX::UInt32& numHitsWanted,
	                                       NRX::UInt32&       numHitsFound,
	                                       NcBrHit*&            hits) const;
	NcBr::ErrorStatus   getBrep(NcBrBrep& brep) const;
	NcBr::ErrorStatus   setValidationLevel(const NcBr::ValidationLevel& level =*(NcBr::ValidationLevel*)NULL);
	NcBr::ErrorStatus   getValidationLevel(NcBr::ValidationLevel& level) const;
	NRX::Boolean        brepChanged() const;
	NcBr::ErrorStatus   set(const NcDbFullSubentPath& path);
	NcBr::ErrorStatus   get(NcDbFullSubentPath& path) const;
	NcBr::ErrorStatus   set(NcBrBrepData* data);
	NcBr::ErrorStatus   get(NcBrBrepData*& data) const;
	NcBr::ErrorStatus   getMassProps(NcBrMassProps& massProps,
	                                 const double& density =*(double*)NULL,
	                                 const double& tolRequired =*(double*)NULL,
	                                 double& tolAchieved =*(double*)NULL) const;
	NcBr::ErrorStatus    getVolume (double& volume,
	                                const double& tolRequired =*(double*)NULL,
	                                double& tolAchieved =*(double*)NULL) const;
	NcBr::ErrorStatus    getSurfaceArea (double& area,
	                                     const double& tolRequired =*(double*)NULL,
	                                     double& tolAchieved =*(double*)NULL) const;
	NcBr::ErrorStatus    getPerimeterLength(double& length,
	                                        const double& tolRequired =*(double*)NULL,
	                                        double& tolAchieved =*(double*)NULL) const;
public:
	OdBrEntity* native() const;

protected:
	NcBrEntity();
	NcBrEntity(const NcBrEntity& src);
	NcBrEntity& operator = (const NcBrEntity& src);
public:
	OdBrEntity* m_pOdImpl;
};

//////////////////////////////////////////////////////////////////////////
// NcBrComplex
class OdBrComplex;
class NRXDBGATE_EXPORT NcBrComplex : public NcBrEntity {
public:
	NCRX_DECLARE_MEMBERS(NcBrComplex);
	NcBrComplex();
	NcBrComplex(OdBrComplex* _object);
	NcBrComplex(const NcBrComplex& src);
	~NcBrComplex();
	NcBrComplex& operator = (const NcBrComplex& src);

	OdBrComplex* native() const
	{
		return (OdBrComplex*)m_pOdImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcBrBrepComplexTraverser
class OdBrBrepComplexTraverser;
class NRXDBGATE_EXPORT NcBrBrepComplexTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrBrepComplexTraverser);
	NcBrBrepComplexTraverser();
	NcBrBrepComplexTraverser(const NcBrBrepComplexTraverser& src);
	~NcBrBrepComplexTraverser();
	NcBrBrepComplexTraverser& operator =(const NcBrBrepComplexTraverser& src);
	NcBr::ErrorStatus   setBrepAndComplex(const NcBrComplex& complex);
	NcBr::ErrorStatus   setBrep         (const NcBrBrep& brep);
	NcBr::ErrorStatus   getBrep         (NcBrBrep& brep) const;
	NcBr::ErrorStatus   setComplex      (const NcBrComplex& complex);
	NcBr::ErrorStatus   getComplex      (NcBrComplex& complex) const;

public:
	OdBrBrepComplexTraverser* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrBrepEdgeTraverser
class OdBrBrepEdgeTraverser;
class NRXDBGATE_EXPORT NcBrBrepEdgeTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrBrepEdgeTraverser);
	NcBrBrepEdgeTraverser();
	NcBrBrepEdgeTraverser(const NcBrBrepEdgeTraverser& src);
	~NcBrBrepEdgeTraverser();
	NcBrBrepEdgeTraverser& operator =   (const NcBrBrepEdgeTraverser& src);
	NcBr::ErrorStatus   setBrepAndEdge  (const NcBrEdge& edge);
	NcBr::ErrorStatus   setBrep         (const NcBrBrep& brep);
	NcBr::ErrorStatus   getBrep         (NcBrBrep& brep) const;
	NcBr::ErrorStatus   setEdge         (const NcBrEdge& edge);
	NcBr::ErrorStatus   getEdge         (NcBrEdge& edge) const;

public:
	OdBrBrepEdgeTraverser* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrBrepFaceTraverser
class OdBrBrepFaceTraverser;
class NRXDBGATE_EXPORT NcBrBrepFaceTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrBrepFaceTraverser);
	NcBrBrepFaceTraverser();
	NcBrBrepFaceTraverser(const NcBrBrepFaceTraverser& src);
	~NcBrBrepFaceTraverser();
	NcBrBrepFaceTraverser& operator =   (const NcBrBrepFaceTraverser& src);
	NcBr::ErrorStatus   setBrep         (NcBrBrep& brep);
	NcBr::ErrorStatus   getBrep         (NcBrBrep& brep) const;
	NcBr::ErrorStatus   setFace         (NcBrFace& face);
	NcBr::ErrorStatus   getFace         (NcBrFace& face) const;
	NcBr::ErrorStatus   setBrepAndFace  (const NcBrFace& face);
	NcBr::ErrorStatus   setBrep         (const NcBrBrep& brep);
	NcBr::ErrorStatus   setFace         (const NcBrFace& face);
public:
	OdBrBrepFaceTraverser* native() const;
};


//////////////////////////////////////////////////////////////////////////
// NcBrBrep
class OdBrBrep;
class NRXDBGATE_EXPORT NcBrBrep : public NcBrEntity {

public:
	using NcBrEntity::set;
	using NcBrEntity::get;
	NCRX_DECLARE_MEMBERS(NcBrBrep);

	NcBrBrep();
	NcBrBrep(OdBrEntity* _object);

	NcBrBrep(const NcBrBrep& src);
	~NcBrBrep();
	NcBrBrep&           operator = (const NcBrBrep& src);
	NcBr::ErrorStatus   getPointRelationToBrep(const NcGePoint3d& point, NcBr::Relation& relation) const;
	NcBr::ErrorStatus   getCurveRelationToBrep(const NcGeCurve3d& curve, NcBr::Relation& relation) const;
	NcBr::ErrorStatus    set(const NcDbEntity& entity);
	NcBr::ErrorStatus    get(NcDb3dSolid*& pSolid) const;
	NcBr::ErrorStatus    get(NcDbSurface*& pSurface) const;

public:
	OdBrBrep* native() const
	{
		return (OdBrBrep*)m_pOdImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcBrBrepShellTraverser
class NRXDBGATE_EXPORT NcBrBrepShellTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrBrepShellTraverser);
	NcBrBrepShellTraverser();
	NcBrBrepShellTraverser(const NcBrBrepShellTraverser& src);
	~NcBrBrepShellTraverser();
	NcBrBrepShellTraverser& operator = (const NcBrBrepShellTraverser& src);
	NcBr::ErrorStatus   setBrepAndShell(const NcBrShell& shell);
	NcBr::ErrorStatus   setBrep(const NcBrBrep& brep);
	NcBr::ErrorStatus   getBrep(NcBrBrep& brep) const;
	NcBr::ErrorStatus   setShell(const NcBrShell& shell);
	NcBr::ErrorStatus   getShell(NcBrShell& shell) const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrBrepVertexTraverser
class NRXDBGATE_EXPORT NcBrBrepVertexTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrBrepVertexTraverser);
	NcBrBrepVertexTraverser();
	NcBrBrepVertexTraverser(const NcBrBrepVertexTraverser& src);
	~NcBrBrepVertexTraverser();
	NcBrBrepVertexTraverser& operator = (const NcBrBrepVertexTraverser& src);
	NcBr::ErrorStatus   setBrepAndVertex(const NcBrVertex& vertex);
	NcBr::ErrorStatus   setBrep         (const NcBrBrep& brep);
	NcBr::ErrorStatus   getBrep         (NcBrBrep& brep) const;
	NcBr::ErrorStatus   setVertex       (const NcBrVertex& vertex);
	NcBr::ErrorStatus   getVertex       (NcBrVertex& vertex) const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrComplexShellTraverser
class OdBrComplexShellTraverser;
class NRXDBGATE_EXPORT NcBrComplexShellTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrComplexShellTraverser);
	NcBrComplexShellTraverser();
	NcBrComplexShellTraverser(const NcBrComplexShellTraverser& src);
	~NcBrComplexShellTraverser();
	NcBrComplexShellTraverser& operator =(const NcBrComplexShellTraverser& src);
	NcBr::ErrorStatus   setComplexAndShell(const NcBrShell& shell);
	NcBr::ErrorStatus   setComplex(const NcBrBrepComplexTraverser& brepcompshell);
	NcBr::ErrorStatus   setComplex(const NcBrComplex& complex);
	NcBr::ErrorStatus   getComplex(NcBrComplex& complex) const;
	NcBr::ErrorStatus   setShell(const NcBrShell& shell);
	NcBr::ErrorStatus   getShell(NcBrShell& shell) const;
public:
	OdBrComplexShellTraverser* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrEdge
class OdBrEdge;
class NRXDBGATE_EXPORT NcBrEdge : public NcBrEntity {
public:
	NCRX_DECLARE_MEMBERS(NcBrEdge);
	NcBrEdge(OdBrEntity* _object);
	NcBrEdge();
	NcBrEdge(const NcBrEdge& src);
	~NcBrEdge();
	NcBrEdge&           operator =      (const NcBrEdge& src);
	NcBr::ErrorStatus   getCurveType    (NcGe::EntityId& type) const;
	NcBr::ErrorStatus   getCurve        (NcGeCurve3d*& curve) const;
	NcBr::ErrorStatus   getOrientToCurve(NRX::Boolean& bOrientToCurve) const;
	NcBr::ErrorStatus   getVertex1      (NcBrVertex& vertex) const;
	NcBr::ErrorStatus   getVertex2      (NcBrVertex& vertex) const;
	NcBr::ErrorStatus   getPointRelationToEdge(const NcGePoint3d& point, NcBr::Relation& relation) const;
	NcBr::ErrorStatus   getCurveRelationToEdge(const NcGeCurve3d& curve, NcBr::Relation& relation) const;
	NcBr::ErrorStatus   getCurveAsNurb(NcGeNurbCurve3d& nurb,
	                                   const double& fitTolRequired =*(double*)NULL,
	                                   double& fitTolAchieved =*(double*)NULL) const;
public:
	OdBrEdge* native() const
	{
		return (OdBrEdge*)m_pOdImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcBrMeshEntity
class NRXDBGATE_EXPORT NcBrMeshEntity : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcBrMeshEntity);
	virtual ~NcBrMeshEntity();
	NRX::Boolean      isEqualTo(const NcRxObject* other) const;
	NRX::Boolean      isNull() const;
	NcBr::ErrorStatus   getEntityAssociated(NcBrEntity*& entity) const;
	NcBr::ErrorStatus   setValidationLevel(const NcBr::ValidationLevel& =*(NcBr::ValidationLevel*)NULL);
	NcBr::ErrorStatus   getValidationLevel(NcBr::ValidationLevel& validationLevel) const;
	NRX::Boolean        brepChanged() const;
protected:
	NcBrMeshEntity();
	NcBrMeshEntity(const NcBrMeshEntity&);
	NcBrMeshEntity& operator = (const NcBrMeshEntity&);
};

//////////////////////////////////////////////////////////////////////////
// NcBrElement
class NRXDBGATE_EXPORT NcBrElement : public NcBrMeshEntity {
public:
	NCRX_DECLARE_MEMBERS(NcBrElement);
	virtual ~NcBrElement();
protected:
	NcBrElement();
	NcBrElement(const NcBrElement& src);
	NcBrElement& operator = (const NcBrElement& src);
};

//////////////////////////////////////////////////////////////////////////
// NcBrElement2d
class NRXDBGATE_EXPORT NcBrElement2d : public NcBrElement {
public:
	NCRX_DECLARE_MEMBERS(NcBrElement2d);
	NcBrElement2d();
	NcBrElement2d(const NcBrElement2d& src);
	~NcBrElement2d();
	NcBrElement2d&      operator = (const NcBrElement2d& src);
	NcBr::ErrorStatus   set(NcBrElement2dData* data);
	NcBr::ErrorStatus   get(NcBrElement2dData*& data) const;
	NcBr::ErrorStatus   getNormal(NcGeVector3d& normal) const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrEdgeLoopTraverser
class OdBrEdgeLoopTraverser;
class NRXDBGATE_EXPORT NcBrEdgeLoopTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrEdgeLoopTraverser);
	NcBrEdgeLoopTraverser();
	NcBrEdgeLoopTraverser(const NcBrEdgeLoopTraverser& src);
	~NcBrEdgeLoopTraverser();
	NcBrEdgeLoopTraverser& operator = (const NcBrEdgeLoopTraverser& src);
	NcBr::ErrorStatus   setEdgeAndLoop(NcBrLoopEdgeTraverser& loopEdge);
	NcBr::ErrorStatus   setEdge(NcBrEdge& edge);
	NcBr::ErrorStatus   getEdge(NcBrEdge& edge) const;
	NcBr::ErrorStatus   getLoop(NcBrLoop& loop) const;
	NcBr::ErrorStatus   setEdgeAndLoop(const NcBrLoopEdgeTraverser& loopEdge);
	NcBr::ErrorStatus   setEdge(const NcBrVertexEdgeTraverser& vertexEdge);
	NcBr::ErrorStatus   setEdge(const NcBrEdge& edge);
	NcBr::ErrorStatus   setLoop(const NcBrLoop& loop);
public:
	OdBrEdgeLoopTraverser* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrElement2dNodeTraverser
class NRXDBGATE_EXPORT NcBrElement2dNodeTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrElement2dNodeTraverser);
	NcBrElement2dNodeTraverser();
	NcBrElement2dNodeTraverser(const NcBrElement2dNodeTraverser& src);
	~NcBrElement2dNodeTraverser();
	NcBrElement2dNodeTraverser& operator =(const NcBrElement2dNodeTraverser& src);
	NcBr::ErrorStatus   setElement(const NcBrMesh2dElement2dTraverser& mesh2dElement2dTraverser);
	NcBr::ErrorStatus   setElement(const NcBrElement2d& element);
	NcBr::ErrorStatus   getElement(NcBrElement2d& element) const;
	NcBr::ErrorStatus   setNode(const NcBrNode& node);
	NcBr::ErrorStatus   getNode(NcBrNode& node) const;
	NcBr::ErrorStatus   getSurfaceNormal(NcGeVector3d& vector) const;
	NcBr::ErrorStatus   getParamPoint(NcGePoint2d& point) const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrFace
class OdBrFace;
class NRXDBGATE_EXPORT NcBrFace : public NcBrEntity {
public:
	NCRX_DECLARE_MEMBERS(NcBrFace);
	NcBrFace(OdBrEntity* _object);
	NcBrFace();
	NcBrFace(const NcBrFace& src);
	~NcBrFace();
	NcBrFace& operator = (const NcBrFace& src);
	NcBr::ErrorStatus   getSurfaceType (NcGe::EntityId& type) const;
	NcBr::ErrorStatus   getSurface(NcGeSurface*& surface) const;
	NcBr::ErrorStatus   getOrientToSurface(NRX::Boolean& bOrientToSurface) const;
	NcBr::ErrorStatus   getArea(double& area,
	                            const double& tolRequired =*(double*)NULL,
	                            double& tolAchieved =*(double*)NULL) const;
	NcBr::ErrorStatus   getPointRelationToFace(const NcGePoint3d& point, NcBr::Relation& relation) const;
	NcBr::ErrorStatus   getCurveRelationToFace(const NcGeCurve3d& curve, NcBr::Relation& relation) const;
	NcBr::ErrorStatus   getSurfaceAsNurb(NcGeNurbSurface& nurb,
	                                     const double&    fitTolRequired =*(double*)NULL,
	                                     double&          fitTolAchieved =*(double*)NULL) const;
	NcBr::ErrorStatus   getSurfaceAsTrimmedNurbs(NRX::UInt32&                numNurbs,
	                                             NcGeExternalBoundedSurface**& ppNurbs) const;
	NcBr::ErrorStatus   getShell(NcBrShell& shell) const;

public:
	OdBrFace* native() const
	{
		return (OdBrFace*)m_pOdImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcBrFaceLoopTraverser
class OdBrFaceLoopTraverser;
class NRXDBGATE_EXPORT NcBrFaceLoopTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrFaceLoopTraverser);
	NcBrFaceLoopTraverser();
	NcBrFaceLoopTraverser(const NcBrFaceLoopTraverser& src);
	~NcBrFaceLoopTraverser();
	NcBrFaceLoopTraverser& operator = (const NcBrFaceLoopTraverser& src);
	NcBr::ErrorStatus   setFace(NcBrFace& face);
	NcBr::ErrorStatus   getFace(NcBrFace& face) const;
	NcBr::ErrorStatus   setLoop(NcBrLoop& loop);
	NcBr::ErrorStatus   getLoop(NcBrLoop& loop) const;
	NcBr::ErrorStatus   setFaceAndLoop(const NcBrLoop& loop);
	NcBr::ErrorStatus   setFace(const NcBrFace& face);
	NcBr::ErrorStatus   setLoop(const NcBrLoop& loop);
	NcBr::ErrorStatus   setFace(const NcBrShellFaceTraverser& shellFaceTrav);
public:
	OdBrFaceLoopTraverser* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrHit
class NRXDBGATE_EXPORT NcBrHit : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcBrHit);
	NcBrHit();
	NcBrHit(const NcBrHit& src);
	~NcBrHit();
	NcBrHit&          operator = (const NcBrHit& src);
	NRX::Boolean      isEqualTo(const NcRxObject* other) const;
	NRX::Boolean      isNull() const;
	NcBr::ErrorStatus setHitPath(NcBrHitPath& hitPath);
	NcBr::ErrorStatus getPoint(NcGePoint3d*& point) const;
	NcBr::ErrorStatus getEntityHit(NcBrEntity*& entityHit) const;
	NcBr::ErrorStatus getEntityEntered(NcBrEntity*& entityEntered) const;
	NcBr::ErrorStatus getEntityAssociated(NcBrEntity*& entity) const;
	NcBr::ErrorStatus getPoint(NcGePoint3d& point) const;
	NcBr::ErrorStatus setValidationLevel(const NcBr::ValidationLevel& validationLevel =*(NcBr::ValidationLevel*)NULL);
	NcBr::ErrorStatus getValidationLevel(NcBr::ValidationLevel& validationLevel) const;
	NRX::Boolean      brepChanged() const;
	NcBr::ErrorStatus set(NcBrHitData* hitData);
	NcBr::ErrorStatus get(NcBrHitData*& hitData) const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrLoopEdgeTraverser
class OdBrLoopEdgeTraverser;
class NRXDBGATE_EXPORT NcBrLoopEdgeTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrLoopEdgeTraverser);
	NcBrLoopEdgeTraverser();
	NcBrLoopEdgeTraverser(const NcBrLoopEdgeTraverser& src);
	~NcBrLoopEdgeTraverser();
	NcBrLoopEdgeTraverser& operator =   (const NcBrLoopEdgeTraverser& src);
	NcBr::ErrorStatus   setLoopAndEdge  (NcBrEdgeLoopTraverser& edgeLoop);
	NcBr::ErrorStatus   setLoop         (NcBrFaceLoopTraverser& loop);
	NcBr::ErrorStatus   getLoop         (NcBrLoop& loop) const;
	NcBr::ErrorStatus   setEdge         (NcBrEdge& edge);
	NcBr::ErrorStatus   getEdge         (NcBrEdge& edge) const;
	NcBr::ErrorStatus   getEdgeOrientToLoop(NRX::Boolean& orient) const;
	NcBr::ErrorStatus   getParamCurve   (NcGeCurve2d*& pcurve) const;
	NcBr::ErrorStatus   getOrientedCurve(NcGeCurve3d*& curve) const;
	NcBr::ErrorStatus   getParamCurveAsNurb(NcGeNurbCurve2d& nurb,
	                                     const double&    fitTolRequired =*(double*)NULL,
	                                     double&          fitTolAchieved =*(double*)NULL) const;
	NcBr::ErrorStatus   getOrientedCurveAsNurb(NcGeNurbCurve3d& nurb,
	                                     const double&    fitTolRequired =*(double*)NULL,
	                                     double&          fitTolAchieved =*(double*)NULL) const;
	NcBr::ErrorStatus   setLoopAndEdge  (const NcBrEdgeLoopTraverser& edgeLoop);
	NcBr::ErrorStatus   setLoop         (const NcBrFaceLoopTraverser& faceLoop);
	NcBr::ErrorStatus   setLoop         (const NcBrLoop& loop);
	NcBr::ErrorStatus   setEdge         (const NcBrEdge& edge);
public:
	OdBrLoopEdgeTraverser* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrLoop
class OdBrLoop;
class NRXDBGATE_EXPORT NcBrLoop : public NcBrEntity {
public:
	NCRX_DECLARE_MEMBERS(NcBrLoop);
	NcBrLoop(OdBrEntity* _object);
	NcBrLoop();
	NcBrLoop(const NcBrLoop& src);
	~NcBrLoop();
	NcBrLoop&           operator = (const NcBrLoop& src);
	NcBr::ErrorStatus   getFace(NcBrFace& face) const;
	NcBr::ErrorStatus   getType(NcBr::LoopType& type) const;
public:
	OdBrLoop* native() const
	{
		return (OdBrLoop*)m_pOdImpl;
	}
};

//////////////////////////////////////////////////////////////////////////
// NcBrLoopVertexTraverser
class OdBrLoopVertexTraverser;
class NRXDBGATE_EXPORT NcBrLoopVertexTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrLoopVertexTraverser);
	NcBrLoopVertexTraverser();
	NcBrLoopVertexTraverser(const NcBrLoopVertexTraverser& src);
	~NcBrLoopVertexTraverser();
	NcBrLoopVertexTraverser& operator = (const NcBrLoopVertexTraverser& src);
	NcBr::ErrorStatus   setLoop(NcBrFaceLoopTraverser& faceLoop);
	NcBr::ErrorStatus   getLoop(NcBrLoop& loop) const;
	NcBr::ErrorStatus   getVertex(NcBrVertex& vertex) const;
	NcBr::ErrorStatus   getParamPoint(NcGePoint2d*& ppoint) const;
	NcBr::ErrorStatus   getParamPoint(NcGePoint2d& ppoint) const;
	NcBr::ErrorStatus   setLoopAndVertex(const NcBrVertexLoopTraverser& vertexLoop);
	NcBr::ErrorStatus   setLoop(const NcBrFaceLoopTraverser& faceLoop);
	NcBr::ErrorStatus   setLoop(const NcBrLoop& loop);
	NcBr::ErrorStatus   setVertex(const NcBrVertex& vertex);
public:
	OdBrLoopVertexTraverser* native() const;
};


//////////////////////////////////////////////////////////////////////////
// NcBrMesh
class NRXDBGATE_EXPORT NcBrMesh : public NcBrMeshEntity {
public:
	NCRX_DECLARE_MEMBERS(NcBrMesh);
	virtual ~NcBrMesh();
protected:
	NcBrMesh();
	NcBrMesh(const NcBrMesh&);
	NcBrMesh& operator = (const NcBrMesh&);
};

//////////////////////////////////////////////////////////////////////////
// NcBrMesh2dFilter
class NRXDBGATE_EXPORT NcBrMesh2dFilter {
public:
	NcBrMesh2dFilter();
	~NcBrMesh2dFilter();
	::iterator insert(const value_type& x);
private:
	NcBrMesh2dFilter(const NcBrMesh2dFilter& src);
	NcBrMesh2dFilter& operator = (const NcBrMesh2dFilter& src);
	value_type        mKeyValuePair;
};

//////////////////////////////////////////////////////////////////////////
// NcBrMesh2d
class NRXDBGATE_EXPORT NcBrMesh2d : public NcBrMesh {
public:
	NCRX_DECLARE_MEMBERS(NcBrMesh2d);
	NcBrMesh2d();
	NcBrMesh2d(const NcBrMesh2d& src);
	~NcBrMesh2d();
	NcBrMesh2d&         operator = (const NcBrMesh2d& src);
	NcBr::ErrorStatus   set(NcBrMesh2dData* mesh2d);
	NcBr::ErrorStatus    get(NcBrMesh2dData*& mesh2d) const;
	NcBr::ErrorStatus   generate(const NcBrMesh2dFilter& meshFilter);
};

//////////////////////////////////////////////////////////////////////////
// NcBrMesh2dElement2dTraverser
class NRXDBGATE_EXPORT NcBrMesh2dElement2dTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrMesh2dElement2dTraverser);
	NcBrMesh2dElement2dTraverser();
	NcBrMesh2dElement2dTraverser(const NcBrMesh2dElement2dTraverser& src);
	~NcBrMesh2dElement2dTraverser();
	NcBrMesh2dElement2dTraverser& operator =(const NcBrMesh2dElement2dTraverser& src);
	NcBr::ErrorStatus   setMeshAndElement(const NcBrElement2d& element2d);
	NcBr::ErrorStatus   setMesh(const NcBrMesh2d& mesh2d);
	NcBr::ErrorStatus   getMesh(NcBrMesh2d& mesh2d) const;
	NcBr::ErrorStatus   setElement(const NcBrElement2d& element2d);
	NcBr::ErrorStatus   getElement(NcBrElement2d& element2d) const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrNode
class NRXDBGATE_EXPORT NcBrNode : public NcBrMeshEntity {
public:
	NCRX_DECLARE_MEMBERS(NcBrNode);
	NcBrNode();
	NcBrNode(const NcBrNode& src);
	~NcBrNode();
	NcBrNode& operator = (const NcBrNode& src);
	NcBr::ErrorStatus   set(NcBrNodeData* nodeData);
	NcBr::ErrorStatus   get(NcBrNodeData*& nodeData) const;
	NcBr::ErrorStatus   getPoint(NcGePoint3d& point) const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrShellFaceTraverser
class OdBrShellFaceTraverser;
class NRXDBGATE_EXPORT NcBrShellFaceTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrShellFaceTraverser);
	NcBrShellFaceTraverser();
	NcBrShellFaceTraverser(const NcBrShellFaceTraverser& src);
	~NcBrShellFaceTraverser();
	NcBrShellFaceTraverser& operator = (const NcBrShellFaceTraverser& src);
	NcBr::ErrorStatus   setShellAndFace(const NcBrFace& face);
	NcBr::ErrorStatus   setShell(const NcBrComplexShellTraverser& complexShellTraverser);
	NcBr::ErrorStatus   setShell(const NcBrShell& shell);
	NcBr::ErrorStatus   getShell(NcBrShell& shell) const;
	NcBr::ErrorStatus   setFace(const NcBrFace& face);
	NcBr::ErrorStatus   getFace(NcBrFace& face) const;
public:
	OdBrShellFaceTraverser* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrShell
class OdBrShell;
class NRXDBGATE_EXPORT NcBrShell : public NcBrEntity {
public:
	NCRX_DECLARE_MEMBERS(NcBrShell);
	NcBrShell(OdBrEntity* _object);
	NcBrShell();
	NcBrShell(const NcBrShell& src);
	~NcBrShell();
	NcBrShell&          operator = (const NcBrShell& src);
	NcBr::ErrorStatus   getComplex(NcBrComplex& complex) const;
	NcBr::ErrorStatus   getType(NcBr::ShellType& shellType) const;

	OdBrShell* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrVertexEdgeTraverser
class NRXDBGATE_EXPORT NcBrVertexEdgeTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrVertexEdgeTraverser);
	NcBrVertexEdgeTraverser();
	NcBrVertexEdgeTraverser(const NcBrVertexEdgeTraverser& src);
	~NcBrVertexEdgeTraverser();
	NcBrVertexEdgeTraverser& operator = (const NcBrVertexEdgeTraverser& src);
	NcBr::ErrorStatus   setVertex(const NcBrVertex& vertex);
	NcBr::ErrorStatus   getVertex(NcBrVertex& vertex) const;
	NcBr::ErrorStatus   setEdge(const NcBrEdge& edge);
	NcBr::ErrorStatus   getEdge(NcBrEdge& edge) const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrVertexLoopTraverser
class NRXDBGATE_EXPORT NcBrVertexLoopTraverser : public NcBrTraverser {
public:
	NCRX_DECLARE_MEMBERS(NcBrVertexLoopTraverser);
	NcBrVertexLoopTraverser();
	NcBrVertexLoopTraverser(const NcBrVertexLoopTraverser& src);
	~NcBrVertexLoopTraverser();
	NcBrVertexLoopTraverser& operator = (const NcBrVertexLoopTraverser& src);
	NcBr::ErrorStatus   setVertexAndLoop(const NcBrLoopVertexTraverser& LoopVertexTraverser);
	NcBr::ErrorStatus   setVertex(const NcBrVertex& vertex);
	NcBr::ErrorStatus   getVertex(NcBrVertex& vertex) const;
	NcBr::ErrorStatus   setLoop(const NcBrLoop& loop);
	NcBr::ErrorStatus   getLoop(NcBrLoop& loop) const;
};

//////////////////////////////////////////////////////////////////////////
// NcBrVertex
class NRXDBGATE_EXPORT NcBrVertex : public NcBrEntity {
public:
	NCRX_DECLARE_MEMBERS(NcBrVertex);
	NcBrVertex();
	NcBrVertex(const NcBrVertex& src);
	~NcBrVertex();
	NcBrVertex&         operator = (const NcBrVertex& src);
	NcBr::ErrorStatus   getPoint(NcGePoint3d*& point) const;
	NcBr::ErrorStatus   getPointRelationToVertex(const NcGePoint3d& point, NcBr::Relation& relation) const;
	NcBr::ErrorStatus   getCurveRelationToVertex(const NcGeCurve3d& curve, NcBr::Relation& relation) const;
	NcBr::ErrorStatus   getPoint(NcGePoint3d& point) const;
};

#endif // __BOUNDARY_H__
