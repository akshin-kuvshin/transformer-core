#pragma once
#include "mcsurf.h"

struct mcsCone;

//==================================================================================================

class MCGEL_API McGeCone : public McGeSurface
{
public:
	McGeCone();

	McGeCone(
		double cosineAngle,
		double sineAngle,
		const  McGePoint3d& baseOrigin,
		double baseRadius,
		const  McGeVector3d& axisOfSymmetry);
	
	McGeCone(
		double cosineAngle,
		double sineAngle,
		const  McGePoint3d& baseOrigin,
		double baseRadius,
		const  McGeVector3d& axisOfSymmetry,
		const  McGeVector3d& refAxis,
		const  McGeInterval& height,
		double startAng,
		double endAng);
    
	McGeCone(const McGeCone& cone);

	McGeCone(const mcsCone& cone);

	virtual double baseRadius() const;

	virtual McGePoint3d baseCenter() const;

	virtual void getAngles(double& startAng, double& endAng) const;

	virtual double halfAngle() const;

	virtual void getHalfAngle(double& cosineAngle, double& sineAngle) const;

	virtual void getHeight(McGeInterval& height) const;

	virtual double heightAt(double u) const;

	virtual McGeVector3d axisOfSymmetry() const;

	virtual McGeVector3d refAxis() const;

	virtual McGePoint3d apex() const;

	virtual bool isClosed(const McGeTol& tol = McGeContext::gTol) const;

	virtual bool isOuterNormal() const;

	virtual McGeCone& setBaseRadius(double baseRadius);

	virtual McGeCone& setAngles(double startAng, double endAng);

	virtual McGeCone& setHeight(const McGeInterval& height);

	virtual McGeCone& set(const mcsCone& cone);

	virtual McGeCone& set(
		double cosineAngle,
		double sineAngle,
		const McGePoint3d& baseCenter,
		double baseRadius,
		const McGeVector3d& axisOfSymmetry);

	virtual McGeCone& set(
		double cosineAngle,
		double sineAngle,
		const McGePoint3d& baseCenter,
		double baseRadius,
		const McGeVector3d& axisOfSymmetry,
		const McGeVector3d& refAxis,
		const McGeInterval& height,
		double startAng,
		double endAng);

	virtual McGeCone& operator = (const McGeCone& cone);

	virtual McGeCone& operator = (const mcsCone& cone);

	virtual bool intersectWith(
		const McGeLinearEnt3d& linEnt,
		int& numInt,
		McGePoint3d& p1,
		McGePoint3d& p2,
		const McGeTol& tol = McGeContext::gTol) const;

};
//==================================================================================================
