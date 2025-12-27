#pragma once
#include "mcsurf.h"

struct mcsSphere;

//==================================================================================================

class MCGEL_API McGeSphere : public McGeSurface
{
public:

	McGeSphere();

	McGeSphere(const McGeSphere& sphere);

	McGeSphere(
		double radius,
		const McGePoint3d& center);

	McGeSphere(
		double radius,
		const McGePoint3d& center,
		const McGeVector3d& northAxis,
		const McGeVector3d& refAxis,
		double startAngleU,
		double endAngleU,
		double startAngleV,
		double endAngleV);

	McGeSphere(const mcsSphere& sphere);

	virtual McGeSphere& set(const mcsSphere& sphere);

	virtual McGeSphere& set(
		double radius,
		const McGePoint3d& center,
		const McGeVector3d& northAxis,
		const McGeVector3d& refAxis,
		double startAngleU,
		double endAngleU,
		double startAngleV,
		double endAngleV);

	virtual McGeSphere& set(double radius, const McGePoint3d& center);

	virtual McGeSphere& setAnglesInU(double start, double end);

	virtual McGeSphere& setAnglesInV(double start, double end);

	virtual McGeSphere& setRadius(double radius);

	virtual McGePoint3d southPole() const;

	virtual McGePoint3d center() const;

	virtual void getAnglesInU(double& start, double& end) const;

	virtual void getAnglesInV(double& start, double& end) const;

	virtual McGeSphere& operator = (const McGeSphere& sphere);

	virtual McGeSphere& operator = (const mcsSphere& sphere);

	virtual bool intersectWith(
		const McGeLinearEnt3d&,
		int& intn,
		McGePoint3d& p1,
		McGePoint3d& p2,
		const McGeTol& tol = McGeContext::gTol) const;

	virtual bool isClosed(const McGeTol& tol = McGeContext::gTol) const;

	virtual bool isOuterNormal() const;

	virtual McGeVector3d northAxis() const;

	virtual McGePoint3d northPole() const;

	virtual double radius() const;

	virtual McGeVector3d refAxis() const;

};
//==================================================================================================
