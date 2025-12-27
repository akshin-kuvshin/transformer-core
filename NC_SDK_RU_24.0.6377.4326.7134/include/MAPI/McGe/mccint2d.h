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

#include "mcent2d.h"
#include "mcponc2d.h"
#include "mcintrvl.h"

class McGeCurve2d;


//==============================================================================
// Two curves intersection information mcs-helper class,
// some data fields are optional

struct cci_point2d
{
	McGePoint2d pt;
	double      prm1, prm2;
	double      dist;
	int         iOverlapping; // +1: yes, -1: no, 0: undef

	cci_point2d() {
		prm1 = UNKNOWNVALUE;
		prm2 = UNKNOWNVALUE;
		dist = UNKNOWNVALUE;
		iOverlapping = 0;
	}

	cci_point2d(const McGePoint2d& pt_arg) {
		pt = pt_arg;
		prm1 = UNKNOWNVALUE;
		prm2 = UNKNOWNVALUE;
		dist = UNKNOWNVALUE;
		iOverlapping = 0;
	}

	cci_point2d(const McGePoint2d& pt_arg, double prm1_arg, double prm2_arg, double dist_arg = UNKNOWNVALUE) {
		pt = pt_arg;
		prm1 = prm1_arg;
		prm2 = prm2_arg;
		dist = dist_arg;
		iOverlapping = 0;
	}

	void set(const McGePoint2d& pt_arg, double prm1_arg, double prm2_arg, double dist_arg = UNKNOWNVALUE) {
		pt = pt_arg;
		prm1 = prm1_arg;
		prm2 = prm2_arg;
		dist = dist_arg;
		iOverlapping = 0;
	}
};

typedef McsArray<cci_point2d> cci_point2d_arr;

//==============================================================================

//==============================================================================
class MCGEL_API McGeCurveCurveInt2d : public McGeEntity2d
{
protected:
	McGeCurveCurveInt3d mBase3d;
	McGeCurve3d *mCrv3d1, *mCrv3d2;

public:
	// Constructors.
	McGeCurveCurveInt2d();

	McGeCurveCurveInt2d(
		const McGeCurve2d& curve1, const McGeCurve2d& curve2,
		const McGeTol& tol = McGeContext::gTol);

	McGeCurveCurveInt2d(
		const McGeCurve2d& curve1, const McGeCurve2d& curve2,
		const McGeInterval& range1, const McGeInterval& range2,
		const McGeTol& tol = McGeContext::gTol);

	McGeCurveCurveInt2d(const McGeCurveCurveInt2d& src);

	// General query functions.
	virtual const McGeCurve2d  *curve1() const;
	virtual const McGeCurve2d  *curve2() const;
	virtual void               getIntRanges(McGeInterval& range1, McGeInterval& range2) const;
	virtual McGeTol            tolerance() const;

	// Intersection query methods.
	virtual int                numIntPoints() const;
	virtual McGePoint2d        intPoint(int intNum) const;
	virtual void               getIntParams(int intNum, double& param1, double& param2) const;
	virtual void               getPointOnCurve1(int intNum, McGePointOnCurve2d& pntOnCrv) const;
	virtual void               getPointOnCurve2(int intNum, McGePointOnCurve2d& pntOnCrv) const;
	virtual void               getIntConfigs(int intNum, McGe::McGeXConfig& config1wrt2, McGe::McGeXConfig& config2wrt1) const;
	virtual bool               isTangential(int intNum) const;
	virtual bool               isTransversal(int intNum) const;
	virtual double             intPointTol(int intNum) const;
	virtual int                overlapCount() const;
	virtual bool	             overlapDirection() const;
	virtual void               getOverlapRanges(int overlapNum, McGeInterval& range1, McGeInterval& range2) const;

	// Curves change their places
	virtual void               changeCurveOrder();

	// Order with respect to parameter on the first/second curve.
	virtual McGeCurveCurveInt2d& orderWrt1();
	virtual McGeCurveCurveInt2d& orderWrt2();

	// Set functions.
	virtual McGeCurveCurveInt2d& set(
		const McGeCurve2d& curve1,
		const McGeCurve2d& curve2,
		const McGeTol& tol = McGeContext::gTol);

	virtual McGeCurveCurveInt2d& set(
		const McGeCurve2d& curve1,
		const McGeCurve2d& curve2,
		const McGeInterval& range1,
		const McGeInterval& range2,
		const McGeTol& tol = McGeContext::gTol);

	// Assignment operator.
	virtual McGeCurveCurveInt2d& operator = (const McGeCurveCurveInt2d& src);

	// additional intersection info mcs-helpers
	// if bNeedAllFields is true, prepares and fills all data fields of the cci_point struct
	const cci_point2d&                 mcs_getIntPoint(int intNum, bool bNeedAllFields = false) const; // NOTE: NULL_REF if out of range
	const cci_point2d_arr&             mcs_getIntPoints(bool bNeedAllFields = false) const;

	const cci_overlapping_range&     mcs_getOverlapRange(int overlapNum) const; // NOTE: NULL_REF if out of range
	const cci_overlapping_range_arr& mcs_getOverlapRanges() const;
};
//==============================================================================
