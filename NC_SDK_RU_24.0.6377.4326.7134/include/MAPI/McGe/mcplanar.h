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

#include "mcsurf.h"

class McGeLineSeg3d;
class McGeLinearEnt3d;
class McGeCircArc3d;

//==============================================================================
class MCGEL_API McGePlanarEnt : public McGeSurface
{
public:
		// Intersection
	virtual bool intersectWith(const McGeLinearEnt3d& linEnt, McGePoint3d& pnt, const McGeTol& tol = McGeContext::gTol) const;

		// Closest point
	virtual McGePoint3d closestPointToLinearEnt(
		const McGeLinearEnt3d& line,
		McGePoint3d& pointOnLine,
		const McGeTol& tol= McGeContext::gTol) const;

	virtual McGePoint3d closestPointToPlanarEnt(
		const McGePlanarEnt& otherPln,
		McGePoint3d& pointOnOtherPln,
		const McGeTol& tol= McGeContext::gTol) const;

		// Direction tests.
	virtual bool isParallelTo(const McGeLinearEnt3d& linEnt,const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isParallelTo(const McGePlanarEnt& otherPlnEnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isPerpendicularTo (const McGeLinearEnt3d& linEnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool isPerpendicularTo (const McGePlanarEnt& linEnt, const McGeTol& tol = McGeContext::gTol) const;

		// Point set equality.
	virtual bool isCoplanarTo(const McGePlanarEnt& otherPlnEnt, const McGeTol& tol = McGeContext::gTol) const;

		// Get methods.
	virtual void get(McGePoint3d&, McGeVector3d& uVec, McGeVector3d& vVec) const;
	virtual void get(McGePoint3d&, McGePoint3d& origin, McGePoint3d&) const;

		// Geometric properties.
	virtual McGePoint3d  pointOnPlane() const;
	virtual McGeVector3d normal() const;
	virtual void         getCoefficients(double& a, double& b, double& c, double& d) const;
	virtual void         getCoordSystem(McGePoint3d& origin, McGeVector3d& axis1, McGeVector3d& axis2) const;

		// Assignment operator.
	virtual McGePlanarEnt& operator = (const McGePlanarEnt& src);

protected:
	McGePlanarEnt();
};
//==============================================================================
