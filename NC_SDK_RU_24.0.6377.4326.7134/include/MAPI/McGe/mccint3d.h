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

#include "mcent3d.h"
#include "mcponc3d.h"
#include "mcintrvl.h"

class McGeCurve3d;

#ifndef CCI_POINT_ARR_DEFINED
	#define CCI_POINT_ARR_DEFINED
	struct cci_point;
	typedef McsArray<cci_point> cci_point_arr;
#endif

//==============================================================================
// Two curves intersection information mcs-helper class,
// some data fields are optional

struct cci_point
{
	McGePoint3d pt;
	double      prm1, prm2;
	double      dist;
	int         iOverlapping; // +1: yes, -1: no, 0: undef

	cci_point() {
		prm1 = UNKNOWNVALUE;
		prm2 = UNKNOWNVALUE;
		dist = UNKNOWNVALUE;
		iOverlapping = 0;
	}

	cci_point(const McGePoint3d& pt_arg){
		pt = pt_arg;
		prm1 = UNKNOWNVALUE;
		prm2 = UNKNOWNVALUE;
		dist = UNKNOWNVALUE;
		iOverlapping = 0;
	}

	cci_point(const McGePoint3d& pt_arg, double prm1_arg, double prm2_arg, double dist_arg = UNKNOWNVALUE) {
		pt = pt_arg;
		prm1 = prm1_arg;
		prm2 = prm2_arg;
		dist = dist_arg;
		iOverlapping = 0;
	}

	void set(const McGePoint3d& pt_arg, double prm1_arg, double prm2_arg, double dist_arg = UNKNOWNVALUE) {
		pt = pt_arg;
		prm1 = prm1_arg;
		prm2 = prm2_arg;
		dist = dist_arg;
		iOverlapping = 0;
	}

	bool operator == (const cci_point& cw) const {
		return pt == cw.pt;
	}
};

//==============================================================================

// Two curves overlapping  information mcs-helper class,
// some data fields are optional

struct cci_overlapping_range
{
	McGeInterval ivl1;
	McGeInterval ivl2;

	cci_overlapping_range() {
	}

	cci_overlapping_range(const McGeInterval& _ivl1, const McGeInterval& _ivl2) {
		ivl1 = _ivl1;
		ivl2 = _ivl2;
	}
};

typedef McsArray<cci_overlapping_range> cci_overlapping_range_arr;

//==============================================================================

//==============================================================================
class MCGEL_API McGeCurveCurveInt3d : public McGeEntity3d
{
public:
		// Constructors.
	McGeCurveCurveInt3d ();

	McGeCurveCurveInt3d (
		const McGeCurve3d& curve1, const McGeCurve3d& curve2,
		const McGeVector3d& planeNormal =
		McGeVector3d::kIdentity,
		const McGeTol& tol = McGeContext::gTol );

	McGeCurveCurveInt3d(
		const McGeCurve3d& curve1, const McGeCurve3d& curve2,
		const McGeInterval& range1, const McGeInterval& range2,
		const McGeVector3d& planeNormal=McGeVector3d::kIdentity,
		const McGeTol& tol = McGeContext::gTol);

	McGeCurveCurveInt3d (const McGeCurveCurveInt3d& src);

		// General query functions.
	virtual const McGeCurve3d  *curve1          () const;
	virtual const McGeCurve3d  *curve2          () const;
	virtual void               getIntRanges     (McGeInterval& range1, McGeInterval& range2) const;
	virtual McGeVector3d	     planeNormal		() const;
	virtual McGeTol            tolerance        () const;

		// Intersection query methods.
	virtual int                numIntPoints     () const;
	virtual McGePoint3d        intPoint         (int intNum) const;
	virtual void               getIntParams     (int intNum, double& param1, double& param2) const;
	virtual void               getPointOnCurve1 (int intNum, McGePointOnCurve3d& pntOnCrv) const;
	virtual void               getPointOnCurve2 (int intNum, McGePointOnCurve3d& pntOnCrv) const;
	virtual void               getIntConfigs    (int intNum, McGe::McGeXConfig& config1wrt2, McGe::McGeXConfig& config2wrt1) const;
	virtual bool               isTangential     (int intNum) const;
	virtual bool               isTransversal    (int intNum) const;
	virtual double             intPointTol      (int intNum) const;
	virtual int                overlapCount     () const;
	virtual bool	             overlapDirection () const;
	virtual void               getOverlapRanges (int overlapNum, McGeInterval& range1, McGeInterval& range2) const;

		// Curves change their places
	virtual void               changeCurveOrder (); 

		// Order with respect to parameter on the first/second curve.
	virtual McGeCurveCurveInt3d& orderWrt1  ();    
	virtual McGeCurveCurveInt3d& orderWrt2  ();

		// Set functions.
	virtual McGeCurveCurveInt3d& set(
		const McGeCurve3d& curve1,
		const McGeCurve3d& curve2,
		const McGeVector3d& planeNormal = 
		McGeVector3d::kIdentity,
		const McGeTol& tol = McGeContext::gTol);

	virtual McGeCurveCurveInt3d& set(
		const McGeCurve3d& curve1,
		const McGeCurve3d& curve2,
		const McGeInterval& range1,
		const McGeInterval& range2,
		const McGeVector3d& planeNormal = 
		McGeVector3d::kIdentity,
		const McGeTol& tol = McGeContext::gTol);

		// Assignment operator.
	virtual McGeCurveCurveInt3d& operator = (const McGeCurveCurveInt3d& src);

		// additional intersection info mcs-helpers
		// if bNeedAllFields is true, prepares and fills all data fields of the cci_point struct
	const cci_point&                 mcs_getIntPoint(int intNum, bool bNeedAllFields = false) const; // NOTE: NULL_REF if out of range
	const cci_point_arr&             mcs_getIntPoints(bool bNeedAllFields = false) const;

	const cci_overlapping_range&     mcs_getOverlapRange(int overlapNum) const; // NOTE: NULL_REF if out of range
	const cci_overlapping_range_arr& mcs_getOverlapRanges() const;
	friend class McGeCurveCurveInt2d;
};
//==============================================================================

struct IMcGeLocateIntersectionPointTool
{
	virtual ~IMcGeLocateIntersectionPointTool()
	{
	}

	virtual HRESULT intersect(
		const McGeCurve3d*    pCrv1,
		const McGeCurve3d*    pCrv2,
		OUT McGePoint3dArray& aPoints,
		const McGeTol&        tol) = 0;

	virtual HRESULT intersect(
		const McGeCurve3d*    pCrv1,
		const McGeCurve3d*    pCrv2,
		const McGeInterval&   ivl1,
		const McGeInterval&   ivl2,
		OUT McGePoint3dArray& aPoints,
		const McGeTol&        tol) = 0;

	virtual void viewSkippedPoints(const McGePoint3dArray& aPoints) = 0;

	MCGEL_API static IMcGeLocateIntersectionPointTool* createInstance();
};
//==============================================================================

struct McGePairOfPts : cci_point
{
	bool        bIntersection;
	McGePoint3d ptOn2;
};
typedef McsArray<McGePairOfPts> McGePairOfPtsArr;

//==============================================================================

// a wrapper to nsSplineHelpers::intersect_3d_curves

MCGEL_API bool mcge_intersect_3d_curves(
	const McGeCurve3d*  pCurve1,
	const McGeCurve3d*  pCurve2,
	OUT cci_point_arr&  cci_pts,
	const McGeInterval* pIvl1 = NULL,
	const McGeInterval* pIvl2 = NULL,
	const McGeTol&      tol = McGeContext::gTol);

MCGEL_API bool mcge_cci2d_FindLocalClosesPointsOnCurves(
	const McGeCurve3d*    pCrv1,
	const McGeCurve3d*    pCrv2,
	const McGeInterval&   ivl1,
	const McGeInterval&   ivl2,
	OUT McGePairOfPtsArr& closestPoints,
	bool                  bCalledForIntersections,
	const McGeTol&        tol);
