#pragma once
#include "mcsurf.h"

struct mcsCylinder;

//==================================================================================================

class MCGEL_API McGeCylinder : public McGeSurface
{
public:
	McGeCylinder();

	McGeCylinder(double radius, const McGePoint3d& origin, const McGeVector3d& axisOfSymmetry);

	McGeCylinder(
		double radius,
		const McGePoint3d& origin,
		const McGeVector3d& axisOfSymmetry,
		const McGeVector3d& refAxis,
		const McGeInterval& height,
		double startAngle,
		double endAngle);

	McGeCylinder(const McGeCylinder& src);

	McGeCylinder(const mcsCylinder& src);

	virtual McGeCylinder& operator = (const McGeCylinder& cylinder);

	virtual McGeCylinder& operator = (const mcsCylinder& cylinder);

	virtual McGeCylinder& set(const mcsCylinder& cylinder);

	virtual McGeCylinder& set(double radius, const McGePoint3d& origin, const McGeVector3d& axisOfSym);

	virtual McGeCylinder& set(
		double radius,
		const McGePoint3d& origin,
		const McGeVector3d& axisOfSym,
		const McGeVector3d& refAxis,
		const McGeInterval& height,
		double startAngle,
		double endAngle);

	virtual McGeCylinder& setAngles(double start, double end);
	virtual McGeCylinder& setHeight(const McGeInterval& height);
	virtual McGeCylinder& setRadius(double radius);

	virtual McGeVector3d  refAxis() const;
	virtual double        radius() const;
	virtual McGePoint3d   origin() const;
	virtual McGeVector3d  axisOfSymmetry() const;

	virtual void    getAngles(double& start, double& end) const;
	virtual void    getHeight(McGeInterval& height) const;
	virtual double  heightAt(double u) const;

	virtual bool    isClosed(const McGeTol& tol = McGeContext::gTol) const;
	virtual bool    isOuterNormal() const;
	
	virtual bool intersectWith(
		const McGeLinearEnt3d& linEnt,
		int& intn,
		McGePoint3d& p1,
		McGePoint3d& p2,
		const McGeTol& tol = McGeContext::gTol) const;

};
//==================================================================================================
