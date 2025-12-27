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

#include "mccurv3d.h"
#include "mcintrvl.h"
#include "mckvec.h"
#include "mcvec3d.h"
#include "mcpnt3d.h"
#include "mcsent3d.h"
#include "mcpline3d.h"

//==============================================================================

class McGeEllipArc3d;
class McGeLineSeg3d;

//==============================================================================
class MCGEL_API McGeNurbCurve3d : public McGeSplineEnt3d
{
public:
	// Construct spline from control points.
	McGeNurbCurve3d();
	McGeNurbCurve3d(const McGeNurbCurve3d& src );

	McGeNurbCurve3d(
		int degree, 
		const McGeKnotVector& knots,
		const McGePoint3dArray& cntrlPnts, 
		bool isPeriodic = false);

	McGeNurbCurve3d(
		int degree, 
		const McGeKnotVector& knots,
		const McGePoint3dArray& cntrlPnts, 
		const McGeDoubleArray&  weights,
		bool isPeriodic = false);

	// Construct spline from interpolation data.
	McGeNurbCurve3d(int degree, const McGePolyline3d& fitPolyline, bool isPeriodic = false);

	McGeNurbCurve3d(
		const McGePoint3dArray& fitPoints, 
		const McGeVector3d& startTangent, 
		const McGeVector3d& endTangent,
		bool startTangentDefined = true,
		bool endTangentDefined = true,
		const McGeTol& fitTolerance = McGeContext::gTol);

	McGeNurbCurve3d(const McGePoint3dArray& fitPoints, const McGeTol& fitTolerance = McGeContext::gTol);

	McGeNurbCurve3d(
		const McGePoint3dArray& fitPoints, 
		const McGeVector3dArray& fitTangents,
		const McGeTol& fitTolerance = McGeContext::gTol,
		bool isPeriodic = false);

	//............................................................................

	// Spline representation of ellipse
	McGeNurbCurve3d (const McGeEllipArc3d&  ellipse);

	// Spline representation of line segment
	McGeNurbCurve3d (const McGeLineSeg3d& linSeg);

	// Query methods.
	virtual int              numFitPoints() const;
	virtual bool  getFitPointAt(int index, McGePoint3d& point) const;
	virtual bool  getFitTolerance(McGeTol& fitTolerance) const;
	virtual bool  getFitTangents(McGeVector3d& startTangent, McGeVector3d& endTangent) const;

	virtual bool getFitTangents(
		McGeVector3d& startTangent,
		McGeVector3d& endTangent,
		bool& startTangentDefined,
		bool& endTangentDefined) const;

	virtual bool getFitData(
		McGePoint3dArray& fitPoints,
		McGeTol& fitTolerance,
		bool& tangentsExist,
		McGeVector3d& startTangent, 
		McGeVector3d& endTangent) const;

	virtual void getDefinitionData(
		int& degree, 
		bool& rational,
		bool& periodic,
		McGeKnotVector& knots,
		McGePoint3dArray& controlPoints,
		McGeDoubleArray& weights) const;

	virtual int    numWeights() const;
	virtual double weightAt(int idx) const;

	virtual bool evalMode() const;
	virtual bool getParamsOfC1Discontinuity (McGeDoubleArray& params, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool getParamsOfG1Discontinuity(McGeDoubleArray& params, const McGeTol& tol = McGeContext::gTol) const;

	// Modification methods.
	virtual bool   setFitPointAt(int index, const McGePoint3d& point);
	virtual bool   addFitPointAt(int index, const McGePoint3d& point);
	virtual bool   deleteFitPointAt(int index);
	virtual bool   setFitTolerance(const McGeTol& fitTol = McGeContext::gTol);
	virtual bool   setFitTangents(const McGeVector3d& startTangent, const McGeVector3d& endTangent);

	virtual bool setFitTangents(
		const McGeVector3d& startTangent, 
		const McGeVector3d& endTangent,
		bool startTangentDefined,
		bool endTangentDefined) const;

	virtual McGeNurbCurve3d& setFitData(
		const McGePoint3dArray& fitPoints,
		const McGeVector3d& startTangent, 
		const McGeVector3d& endTangent,
		const McGeTol& fitTol = McGeContext::gTol);

	virtual McGeNurbCurve3d& setFitData(
		const McGeKnotVector& fitKnots,
		const McGePoint3dArray& fitPoints,
		const McGeVector3d& startTangent,
		const McGeVector3d& endTangent,
		const McGeTol& fitTol = McGeContext::gTol,
		bool isPeriodic = false);

	virtual McGeNurbCurve3d&  setFitData(
		int degree, 
		const McGePoint3dArray& fitPoints, 
		const McGeTol& fitTol = McGeContext::gTol);

		// returns parameters where the 1'st derivative has at least in one coordinate equal to 0
	bool mcs_extremalParams(
		OUT McGeDoubleArray& paramArray,
		IN const McGeTol&    tol) const;

	virtual bool   purgeFitData();
	virtual McGeNurbCurve3d&  addKnot(double newKnot);
	virtual McGeNurbCurve3d&  insertKnot(double newKnot);
	virtual McGeSplineEnt3d&  setWeightAt(int idx, double val);
	virtual McGeNurbCurve3d&  setEvalMode(bool evalMode = false);
	virtual McGeNurbCurve3d&  joinWith(const McGeNurbCurve3d& curve);
	virtual McGeNurbCurve3d&  hardTrimByParams(double newStartParam, double newEndParam);
	virtual McGeNurbCurve3d&  makeRational(double weight = 1.0);
	virtual McGeNurbCurve3d&  makeClosed();
	virtual McGeNurbCurve3d&  makePeriodic();
	virtual McGeNurbCurve3d&  makeNonPeriodic();
	virtual McGeNurbCurve3d&  makeOpen();
	virtual McGeNurbCurve3d&  elevateDegree(int plusDegree);

	virtual McGeNurbCurve3d&  operator = (const McGeNurbCurve3d& spline);

		// Initializes 'trimmedNURBs' by a trimmed version of this-curve using specified parametrization boundaries,
		// is a relatively fast version of the following code:
		//
		//   McGeNurbCurve3d trimmedCopy(originalNurbCurve);
		//   trimmedCopy.hardTrimByParams(from, to);
		//
	virtual void mcs_hardTrimByParams(double newStartParam, double newEndParam, OUT McGeNurbCurve3d& trimmedNURBs) const;

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

	// MCS: internal use
	const McGeMatrix3d& mcs_getTfm() const;
	McGeMatrix3d&       mcs_setTfm();

		// The method tries to simplify this NURBs with the given tolerance.
		// If simplification is successful, the result is returned.
		// Otherwise the method returns NULL.
		// A caller is responsible to delete returning object.
	McGeCurve3d* mcs_getSimplifiedCurve(const McGeTol& tol = McGeContext::gTol) const;

	friend class McGeNurbCurve2d;
};
//==============================================================================
