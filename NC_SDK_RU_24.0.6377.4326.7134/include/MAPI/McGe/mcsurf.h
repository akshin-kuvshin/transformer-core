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

class McGeCurve3d;
class McGePointOnCurve3d;
class McGePointOnSurface;
class McGePointOnSurfaceData;
class McGeInterval;

//==============================================================================
class MCGEL_API McGeSurface : public McGeEntity3d
{
public:
		// Parameter related.
	virtual McGePoint2d paramOf(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;
	
		// Point containment
	virtual bool isOn(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isOn(const McGePoint3d& pnt, McGePoint2d& paramPoint, const McGeTol& tol = McGeContext::gTol) const;

		// Operations.
	virtual McGePoint3d closestPointTo(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual void getClosestPointTo(const McGePoint3d& pnt, McGePointOnSurface& result, const McGeTol& tol = McGeContext::gTol) const;
	virtual double distanceTo(const McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;

	virtual bool isNormalReversed() const;
	virtual McGeSurface& reverseNormal();

		// Assignment operator.
	virtual McGeSurface& operator = (const McGeSurface& otherSurface);

		// Bounds in parameter space.
	virtual void  getEnvelope(McGeInterval& intrvlX, McGeInterval& intrvlY) const;

		// Geometric inquiry methods.
	virtual bool isClosedInU(const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isClosedInV(const McGeTol& tol = McGeContext::gTol) const;

		// Evaluators.
		// Derivative arrays are indexed partialU, partialV followed by
		// the mixed partial.
	virtual McGePoint3d evalPoint(const McGePoint2d& param) const;
	virtual McGePoint3d evalPoint(const McGePoint2d& param, int derivOrd, McGeVector3dArray& derivatives) const;
	virtual McGePoint3d evalPoint(const McGePoint2d& param, int derivOrd, McGeVector3dArray& derivatives, McGeVector3d& normal) const;

		// McGe only and non-virtual !!!
	bool mcs_intersectWithCurve(
		const McGeCurve3d&         curve, 
		OUT McGePoint3dArray&      points,
		IN OPTIONAL const McGeTol& tol = McGeContext::gTol,
		OUT McGeDoubleArray*       pCurveIntPointsParams = NULL) const;

		// McGe only and non-virtual !!!
		// Is similar to McGeCurve3d::getNormalPoint.
		// 'pntOnSurf' on input contains an initial guess point.
		// NOTE: On success, a returning point is the most closed one to the guess point position.
	bool mcs_getNormalPoint(
		IN const McGePoint3d&          pnt,
		IN OUT McGePointOnSurface&     pntOnSurf,
		OUT OPTIONAL McGePoint3dArray* pAllPointCandidates = NULL,
		IN const McGeTol&              tol = McGeContext::gTol) const;

protected:
	McGeSurface();
};
//==============================================================================
