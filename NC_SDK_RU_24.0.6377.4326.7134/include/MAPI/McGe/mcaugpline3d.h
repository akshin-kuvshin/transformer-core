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
#include "mckvec.h"
#include "mcvec3d.h"
#include "mcpnt3d.h"
#include "mcpline3d.h"

//==============================================================================
class MCGEL_API McGeAugPolyline3d : public McGePolyline3d
{
public:
	McGeAugPolyline3d();
	McGeAugPolyline3d(const McGeAugPolyline3d& apline);
	McGeAugPolyline3d(const McGeKnotVector& knots, const McGePoint3dArray& cntrlPnts, const McGeVector3dArray& vecBundle);
	McGeAugPolyline3d(const McGePoint3dArray& cntrlPnts, const McGeVector3dArray& vecBundle);

	// Approximation constructor
	McGeAugPolyline3d(const McGeCurve3d& curve, double fromParam, double toParam, double apprEps);

	McGeAugPolyline3d& operator = (const McGeAugPolyline3d& apline);

	virtual McGePoint3d        getPoint(int idx) const;
	virtual McGeAugPolyline3d& setPoint(int idx, const McGePoint3d& pnt);
	virtual void               getPoints(McGePoint3dArray& pnts) const;

	virtual McGeVector3d       getVector(int idx) const;
	virtual McGeAugPolyline3d& setVector(int idx, const McGeVector3d& vec);
	virtual void               getD1Vectors(McGeVector3dArray& tangents) const;

	virtual McGeVector3d       getD2Vector(int idx) const;
	virtual McGeAugPolyline3d& setD2Vector(int idx, const McGeVector3d& vec);
	virtual void               getD2Vectors(McGeVector3dArray& d2Vectors) const;

	virtual double             approxTol      () const;
	virtual McGeAugPolyline3d& setApproxTol   (double approxTol);
};
//==============================================================================
