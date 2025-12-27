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

#include "mcplanar.h"

class McGeBoundedPlane;
class McGeLine3d;

//==============================================================================
class MCGEL_API McGePlane : public McGePlanarEnt
{
public:
		// Global plane objects.
	static const McGePlane kXYPlane;
	static const McGePlane kYZPlane;
	static const McGePlane kZXPlane;

	McGePlane();
	McGePlane(const McGePlane& src);
	McGePlane(const McGePoint3d& origin, const McGeVector3d& normal);
	McGePlane(const McGePoint3d& pntU, const McGePoint3d& or, const McGePoint3d& pntV);
	McGePlane(const McGePoint3d& or, const McGeVector3d& uAxis, const McGeVector3d& vAxis);
	McGePlane(double a, double b, double c, double d);

		// Signed distance from a point to a plane.
	virtual double signedDistanceTo (const McGePoint3d& pnt) const;

		// Intersection
	virtual bool intersectWith(const McGeLinearEnt3d& linEnt, McGePoint3d& resultPnt, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool intersectWith(const McGePlane& otherPln, McGeLine3d& resultLine, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool intersectWith(const McGeBoundedPlane& bndPln, McGeLineSeg3d& resultLineSeg, const McGeTol& tol = McGeContext::gTol) const;

		// Geometry redefinition.
	virtual McGePlane& set(const McGePoint3d& pnt, const McGeVector3d& normal);
	virtual McGePlane& set(const McGePoint3d& pntU, const McGePoint3d& or, const McGePoint3d& pntV);
	virtual McGePlane& set(double a, double b, double c, double d);
	virtual McGePlane& set(const McGePoint3d& or, const McGeVector3d& uAxis, const McGeVector3d& vAxis);

		// Assignment operator.
	virtual McGePlane& operator = (const McGePlane& src);
};
//==============================================================================
