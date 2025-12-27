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

#include "mccurv2d.h"
#include "mcintrvl.h"
#include "mckvec.h"
#include "mcvec2d.h"
#include "mcpnt2d.h"
#include "mcsent2d.h"

//==============================================================================

class McGeEllipArc2d;
class McGeLineSeg2d;
class McGePolyline2d;

//==============================================================================
class MCGEL_API McGeNurbCurve2d : public McGeSplineEnt2d
{
public:
	// Construct spline from control points.
	McGeNurbCurve2d();
	McGeNurbCurve2d(const McGeNurbCurve2d& src);

	McGeNurbCurve2d(
		int degree,
		const McGeKnotVector& knots,
		const McGePoint2dArray& cntrlPnts,
		bool isPeriodic = false);

	McGeNurbCurve2d(
		int degree,
		const McGeKnotVector& knots,
		const McGePoint2dArray& cntrlPnts,
		const McGeDoubleArray&  weights,
		bool isPeriodic = false);

	// Construct spline from interpolation data.
	McGeNurbCurve2d(int degree, const McGePolyline2d& fitPolyline, bool isPeriodic = false);

	McGeNurbCurve2d(
		const McGePoint2dArray& fitPoints,
		const McGeVector2d& startTangent,
		const McGeVector2d& endTangent,
		bool startTangentDefined = true,
		bool endTangentDefined = true,
		const McGeTol& fitTolerance = McGeContext::gTol);

	McGeNurbCurve2d(const McGePoint2dArray& fitPoints, const McGeTol& fitTolerance = McGeContext::gTol);

	McGeNurbCurve2d(
		const McGePoint2dArray& fitPoints,
		const McGeVector2dArray& fitTangents,
		const McGeTol& fitTolerance = McGeContext::gTol,
		bool isPeriodic = false);

	//............................................................................

	// Spline representation of ellipse
	McGeNurbCurve2d(const McGeEllipArc2d&  ellipse);

	// Spline representation of line segment
	McGeNurbCurve2d(const McGeLineSeg2d& linSeg);

	// Query methods.
	virtual int              numFitPoints() const;
	virtual bool  getFitPointAt(int index, McGePoint2d& point) const;
	virtual bool  getFitTolerance(McGeTol& fitTolerance) const;
	virtual bool  getFitTangents(McGeVector2d& startTangent, McGeVector2d& endTangent) const;

	virtual bool getFitTangents(
		McGeVector2d& startTangent,
		McGeVector2d& endTangent,
		bool& startTangentDefined,
		bool& endTangentDefined) const;

	virtual bool getFitData(
		McGePoint2dArray& fitPoints,
		McGeTol& fitTolerance,
		bool& tangentsExist,
		McGeVector2d& startTangent,
		McGeVector2d& endTangent) const;

	virtual void getDefinitionData(
		int& degree,
		bool& rational,
		bool& periodic,
		McGeKnotVector& knots,
		McGePoint2dArray& controlPoints,
		McGeDoubleArray& weights) const;

	virtual int    numWeights() const;
	virtual double weightAt(int idx) const;

	virtual bool evalMode() const;
	virtual bool getParamsOfC1Discontinuity(McGeDoubleArray& params, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool getParamsOfG1Discontinuity(McGeDoubleArray& params, const McGeTol& tol = McGeContext::gTol) const;

	// Modification methods.
	virtual bool   setFitPointAt(int index, const McGePoint2d& point);
	virtual bool   addFitPointAt(int index, const McGePoint2d& point);
	virtual bool   deleteFitPointAt(int index);
	virtual bool   setFitTolerance(const McGeTol& fitTol = McGeContext::gTol);
	virtual bool   setFitTangents(const McGeVector2d& startTangent, const McGeVector2d& endTangent);

	virtual bool setFitTangents(
		const McGeVector2d& startTangent,
		const McGeVector2d& endTangent,
		bool startTangentDefined,
		bool endTangentDefined) const;

	virtual McGeNurbCurve2d& setFitData(
		const McGePoint2dArray& fitPoints,
		const McGeVector2d& startTangent,
		const McGeVector2d& endTangent,
		const McGeTol& fitTol = McGeContext::gTol);

	virtual McGeNurbCurve2d& setFitData(
		const McGeKnotVector& fitKnots,
		const McGePoint2dArray& fitPoints,
		const McGeVector2d& startTangent,
		const McGeVector2d& endTangent,
		const McGeTol& fitTol = McGeContext::gTol,
		bool isPeriodic = false);

	virtual McGeNurbCurve2d&  setFitData(
		int degree,
		const McGePoint2dArray& fitPoints,
		const McGeTol& fitTol = McGeContext::gTol);

	// returns parameters where the 1'st derivative has at least in one coordinate equal to 0
	bool mcs_extremalParams(
		OUT McGeDoubleArray& paramArray,
		IN const McGeTol&    tol) const;

	virtual bool   purgeFitData();
	virtual McGeNurbCurve2d&  addKnot(double newKnot);
	virtual McGeNurbCurve2d&  insertKnot(double newKnot);
	virtual McGeSplineEnt2d&  setWeightAt(int idx, double val);
	virtual McGeNurbCurve2d&  setEvalMode(bool evalMode = false);
	virtual McGeNurbCurve2d&  joinWith(const McGeNurbCurve2d& curve);
	virtual McGeNurbCurve2d&  hardTrimByParams(double newStartParam, double newEndParam);
	virtual McGeNurbCurve2d&  makeRational(double weight = 1.0);
	virtual McGeNurbCurve2d&  makeClosed();
	virtual McGeNurbCurve2d&  makePeriodic();
	virtual McGeNurbCurve2d&  makeNonPeriodic();
	virtual McGeNurbCurve2d&  makeOpen();
	virtual McGeNurbCurve2d&  elevateDegree(int plusDegree);

	virtual McGeNurbCurve2d&  operator = (const McGeNurbCurve2d& spline);

	// Initializes 'trimmedNURBs' by a trimmed version of this-curve using specified parametrization boundaries,
	// is a relatively fast version of the following code:
	//
	//   McGeNurbCurve2d trimmedCopy(originalNurbCurve);
	//   trimmedCopy.hardTrimByParams(from, to);
	//
	virtual void mcs_hardTrimByParams(double newStartParam, double newEndParam, OUT McGeNurbCurve2d& trimmedNURBs) const;

	// Calculates the most exact value of a length of this curve.
	//   In contrast to the base method 'length', it tries to calculate a length using the given tolerance.
	//   However, if 'dTol' us too small, it couldn't be used,
	//   and you can get the real used tolerance value via the 'pdTolUsed' argument.
	// Example, when the given 'dTol' can't be used:
	//   A spline has coordinates in a 10e6 range, but a dTol's value 1e-10.
	//   It's impossible to carry out calculation using the 'double' type with this tolerance.
	//   'dTol' will automatically be degraded to 1e-3 (approximately).
	double mcs_lengthEx(
		double               fromParam,
		double               toParam,
		double               dTol,
		OUT OPTIONAL double* pdTolUsed = NULL) const;
};
//==============================================================================
