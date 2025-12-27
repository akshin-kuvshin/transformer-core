#pragma once

#include "mcsurf.h"

struct mcsTorus;

//==================================================================================================

class MCGEL_API McGeTorus : public McGeSurface
{
public:
	McGeTorus();

	McGeTorus(const McGeTorus& src);

	McGeTorus(
		double major,
		double minor,
		const McGePoint3d& origin,
		const McGeVector3d& axisOfSymmetry
	);

	McGeTorus(
		double major,
		double minor,
		const McGePoint3d& origin,
		const McGeVector3d& axisOfSymmetry,
		const McGeVector3d& refAxis,
		double startAngleU,
		double endAngleU,
		double startAngleV,
		double endAngleV
	);
	McGeTorus(const mcsTorus& torus);

	virtual McGeTorus& operator = (const mcsTorus& torus);

	virtual McGeTorus& set(const mcsTorus& torus);

	virtual McGeTorus& operator = (const McGeTorus& torus);

	virtual McGeTorus& set(
		double major,
		double minor,
		const McGePoint3d& origin,
		const McGeVector3d& axisOfSymmetry
	);

	virtual McGeTorus& set(
		double major,
		double minor,
		const McGePoint3d& origin,
		const McGeVector3d& axisOfSymmetry,
		const McGeVector3d& refAxis,
		double startAngleU,
		double endAngleU,
		double startAngleV,
		double endAngleV
	);

	virtual McGeTorus& setAnglesInU(double start, double end);
	virtual McGeTorus& setAnglesInV(double start, double end);

	virtual McGeTorus& setMajorRadius(double radius);
	virtual McGeTorus& setMinorRadius(double radius);

	virtual McGeVector3d refAxis() const;
	virtual McGeVector3d axisOfSymmetry() const;
	virtual McGePoint3d  center() const;

	virtual void getAnglesInU(double& start, double& end) const;
	virtual void getAnglesInV(double& start, double& end) const;

	virtual bool intersectWith(
		const McGeLinearEnt3d& linEnt,
		int& intn,
		McGePoint3d& p1,
		McGePoint3d& p2,
		McGePoint3d& p3,
		McGePoint3d& p4,
		const McGeTol& tol = McGeContext::gTol)  const;

	virtual bool isApple() const;
	virtual bool isDegenerate() const;
	virtual bool isDoughnut() const;
	virtual bool isHollow() const;
	virtual bool isLemon() const;
	virtual bool isOuterNormal() const;
	virtual bool isVortex() const;

	virtual double majorRadius() const;
	virtual double minorRadius() const;

	virtual bool isClosed(const McGeTol& tol = McGeContext::gTol) const;

};
//==================================================================================================
