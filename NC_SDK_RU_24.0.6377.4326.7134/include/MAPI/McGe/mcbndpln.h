#pragma once
#include "mcsurf.h"

//==================================================================================================

class MCGEL_API McGeBoundedPlane : public McGePlane
{
public:
	McGeBoundedPlane();

	McGeBoundedPlane(const McGeBoundedPlane& plane);
	McGeBoundedPlane(const McGePoint3d& origin, const McGeVector3d& uVec, const McGeVector3d& vVec);
	McGeBoundedPlane(const McGePoint3d& p1, const McGePoint3d& origin, const McGePoint3d& p2);

	virtual bool intersectWith(const McGeLinearEnt3d& linEnt, McGePoint3d& resultPnt, const McGeTol& tol = McGeContext::gTol) const override {
		return __super::intersectWith(linEnt, resultPnt, tol);
	}

	virtual bool    intersectWith(const McGePlane& otherPln, McGeLineSeg3d& results, const McGeTol& tol = McGeContext::gTol) const;
	virtual bool    intersectWith(const McGeBoundedPlane& plane, McGeLineSeg3d& resultS, const McGeTol& tol = McGeContext::gTol) const;

	virtual McGeBoundedPlane& operator =    (const McGeBoundedPlane& bplane);

	// blocked methods from McGePlane
private:
	virtual bool intersectWith(const McGePlane& otherPln, McGeLine3d& resultLine, const McGeTol& tol = McGeContext::gTol) const override;
	virtual McGeBoundedPlane& operator = (const McGePlane& bplane) override;
};
//==================================================================================================

