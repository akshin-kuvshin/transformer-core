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

#ifndef MCGEL
	#define MCGEL
#endif

#ifndef MCGELDLL
	#pragma comment(lib,"mcgel.lib")
#endif

#include "McGe\csomsk.h"
#include "McGe\mcgblabb.h"
#include "McGe\mcgbl.h"
#include "McGe\mcgblge.h"
#include "McGe\mctol.h"
#include "McGe\mcintrvl.h"
#include "McGe\mckvec.h"

#include "McGe\mcpnt2d.h"
#include "McGe\mcvec2d.h"
#include "McGe\mcmat2d.h"

#include "McGe\mcpnt3d.h"
#include "McGe\mcvec3d.h"

#include "McGe\mcarc3d.h"
#include "McGe\mcblok3d.h"
#include "McGe\mccint3d.h"
#include "McGe\mccomp3d.h"
#include "McGe\mccurv3d.h"
#include "McGe\mcell3d.h"
#include "McGe\mcent3d.h"
#include "McGe\mclent3d.h"
#include "McGe\mcline3d.h"
#include "McGe\mclnsg3d.h"
#include "McGe\mcray3d.h"
#include "McGe\mcmat3d.h"
#include "McGe\mcnurb3d.h"
#include "McGe\mcaugpline3d.h"
#include "McGe\mcpent3d.h"
#include "McGe\mcplanar.h"
#include "McGe\mcplane.h"
#include "McGe\mcbndpln.h"
#include "McGe\mcpnt3d.h"
#include "McGe\mcpent3d.h"
#include "McGe\mcponc3d.h"
#include "McGe\mcsent3d.h"
#include "McGe\mcsurf.h"
#include "McGe\mcvec3d.h"
#include "McGe\mcpos3d.h"
#include "McGe\mccurv3d.h"
#include "McGe\mcpline3d.h"
#include "McGe\mcsurf.h"
#include "McGe\mcnurbsf.h"
#include "McGe\mcoffc3d.h"
#include "McGe\mccone.h"
#include "McGe\mcponsurf.h"
#include "McGe\mcsphere.h"
#include "McGe\mccylinder.h"
#include "McGe\mctorus.h"
#include "McGe\mccurv2d.h"
#include "McGe\mcent2d.h"
#include "McGe\mcponc2d.h"
#include "McGe\mcpent2d.h"
#include "McGe\mclent2d.h"
#include "McGe\mcline2d.h"
#include "McGe\mclnsg2d.h"
#include "McGe\mcray2d.h"
#include "McGe\mcblok2d.h"
#include "McGe\mcarc2d.h"
#include "McGe\mcell2d.h"
#include "McGe\mcpos2d.h"
#include "McGe\mcoffc2d.h"
#include "McGe\mcsent2d.h"
#include "McGe\mcpline2d.h"
#include "McGe\mcnurb2d.h"
#include "McGe\mccomp2d.h"
#include "McGe\mccint2d.h"

// these defines needed by McGeL library in EXE test compilation
#ifndef MCGE_N_ACGE
	#define AC_GEGBLABB_H
	#define AC_GEGBLGE_H
	#define AC_GEDBLAR_H
	#define AC_GEVEC3D_H
	#define AC_GEPNT3D_H
	#define AC_GEVEC2D_H
	#define AC_GEPNT2D_H
	#define AC_GEENT2D_H
	#define _ADESK_H
#endif

#undef mcsEntity
#undef mcsEntity3d
#undef mcsPoint
#undef mcsPoint3d
#undef mcsPoint2d
#undef mcsPointEnt
#undef mcsPointEnt3d
#undef mcsPointEnt2d
#undef mcsVector
#undef mcsVector2d
#undef mcsVector3d
#undef mcsPointsArr
#undef mcsMatrix3d
#undef mcsMatrix2d
#undef mcsLine
#undef mcsLine2d
#undef mcsLine3d
#undef mcsLinearEntity
#undef mcsLineSeg
#undef mcsLineSeg2d
#undef mcsLineSeg3d
#undef mcsRay
#undef mcsRay2d
#undef mcsRay3d
#undef mcsCurve
#undef mcsCurve2d
#undef mcsCurve3d
#undef mcsNurbCurve
#undef mcsNurbCurve3d
#undef mcsNurbCurve2d
#undef mcsCircArc
#undef mcsCircArc2d
#undef mcsCircArc3d
#undef mcsEllipArc
#undef mcsEllipArc2d
#undef mcsEllipArc3d
#undef mcsSpline
#undef mcsSpline2d
#undef mcsSpline3d
#undef mcsSplineEnt
#undef mcsSplineEnt2d
#undef mcsSplineEnt3d
#undef mcsInterval
#undef mcsBounds
#undef mcsBounds3d
#undef mcsPlane
#undef mcsBoundedPlane
#undef mcsPlanarEnt
#undef mcsNurbSurf
#undef mcsTol
#undef mcsInterval
#undef mcsGeContext
#undef mcsOffsetCrvExtType
#undef mcsTrue
#undef mcsFalse
#undef mcsBoolean
#undef mcsCurveCurveInt
#undef mcsCurveCurveInt3d
#undef mcsPointOnCurve
#undef mcsPointOnCurve2d
#undef mcsPointOnCurve3d
#undef mcsPointOnSurf
#undef mcsCompositeCurve
#undef mcsCompositeCurve3d
#undef mcsCompositeCurve2d
#undef mcsOffsetCurve
#undef mcsOffsetCurve2d
#undef mcsOffsetCurve3d
#undef CSOmsk
#undef mcsGe
#undef mcsGeError
#undef mcsGePoints3dArr
#undef mcsGeVectors3dArr
#undef mcsGePoints2dArr
#undef mcsGeVectors2dArr
#undef mcsGeVoidPtrArr
#undef mcsGeDoubleArr
#undef mcsGeIntArr
#undef mcsAugPolyline
#undef mcsAugPolyline3d
#undef mcsPosition
#undef mcsPosition3d
#undef mcsKnotVector

#undef mcsSurface
#undef mcsGeSphere
#undef mcsGeCone
#undef mcsGeCylinder
#undef mcsGeTorus

#define mcsEntity            McGeEntity3d
#define mcsEntity3d          McGeEntity3d
#define mcsPoint             McGePoint3d
#define mcsPoint3d           McGePoint3d
#define mcsPoint2d           McGePoint2d
#define mcsPointEnt          McGePointEnt3d
#define mcsPointEnt3d        McGePointEnt3d
//#define mcsPointEnt2d        McGePointEnt2d
#define mcsVector            McGeVector3d
#define mcsVector2d          McGeVector2d
#define mcsVector3d          McGeVector3d
#define mcsPointsArr         McGePoint3dArray
#define mcsMatrix2d          McGeMatrix2d
#define mcsMatrix3d          McGeMatrix3d
#define mcsLine              McGeLine3d
#define mcsLine2d            McGeLine2d
#define mcsLine3d            McGeLine3d
#define mcsRay               McGeRay3d
#define mcsRay2d             McGeRay2d
#define mcsRay3d             McGeRay3d
#define mcsLinearEntity      McGeLinearEnt3d
#define mcsLineSeg           McGeLineSeg3d
#define mcsLineSeg2d         McGeLineSeg2d
#define mcsLineSeg3d         McGeLineSeg3d
#define mcsCurve             McGeCurve3d
#define mcsCurve2d           McGeCurve2d
#define mcsCurve3d           McGeCurve3d
#define mcsCircArc2d         McGeCircArc2d
#define mcsCircArc3d         McGeCircArc3d
#define mcsCircArc           McGeCircArc3d
#define mcsEllipArc          McGeEllipArc3d
#define mcsEllipArc2d        McGeEllipArc2d
#define mcsEllipArc3d        McGeEllipArc3d
#define mcsNurbCurve         McGeNurbCurve3d
#define mcsNurbCurve3d       McGeNurbCurve3d
#define mcsNurbCurve2d       McGeNurbCurve2d
#define mcsSpline            McGeNurbCurve3d
#define mcsSpline3d          McGeNurbCurve3d
#define mcsSpline2d          McGeNurbCurve2d
#define mcsSplineEnt         McGeSplineEnt3d
#define mcsSplineEnt3d       McGeSplineEnt3d
#define mcsSplineEnt2d       McGeSplineEnt2d
#define mcsInterval          McGeInterval
#define mcsBounds            McGeBoundBlock3d
#define mcsBounds3d          McGeBoundBlock3d
#define mcsPlane             McGePlane
#define mcsBoundedPlane      McGeBoundedPlane
#define mcsPlanarEnt         McGePlanarEnt
#define mcsNurbSurf          McGeNurbSurface
#define mcsTol               McGeTol
#define mcsPointOnCurve3d    McGePointOnCurve3d
#define mcsPointOnCurve2d    McGePointOnCurve2d
#define mcsPointOnSurf       McGePointOnSurface
#define mcsInterval          McGeInterval
#define mcsGeContext         McGeContext
#define mcsOffsetCrvExtType  McGe::OffsetCrvExtType
#define mcsTrue              true
#define mcsFalse             false
#define mcsBoolean           bool
#define mcsCurveCurveInt     McGeCurveCurveInt3d
#define mcsCurveCurveInt3d   McGeCurveCurveInt3d
#define mcsPointOnCurve      McGePointOnCurve3d
#define mcsCompositeCurve    McGeCompositeCurve3d
#define mcsCompositeCurve3d  McGeCompositeCurve3d
//#define mcsCompositeCurve2d  McGeCompositeCurve2d
#define mcsOffsetCurve       McGeOffsetCurve3d
#define mcsOffsetCurve3d     McGeOffsetCurve3d
//#define mcsOffsetCurve2d     McGeOffsetCurve2d
#define mcsGe                McGe
#define mcsGeError           McGeError
#define mcsGePoints3dArr     McGePoint3dArray
#define mcsGeVectors3dArr    McGeVector3dArray
#define mcsGePoints2dArr     McGePoint2dArray
#define mcsGeVectors2dArr    McGeVector2dArray
#define mcsGeVoidPtrArr      McGePVoidArray
#define mcsGeDoubleArr       McGeDoubleArray
#define mcsGeIntArr          McGeIntArray
#define mcsAugPolyline       McGeAugPolyline3d
#define mcsAugPolyline3d     McGeAugPolyline3d
#define mcsPosition          McGePosition3d
#define mcsPosition3d        McGePosition3d
#define mcsKnotVector        McGeKnotVector

#define mcsSurface           McGeSurface
#define mcsGeSphere          McGeSphere
#define mcsGeCone            McGeCone
#define mcsGeCylinder        McGeCylinder
#define mcsGeTorus           McGeTorus

