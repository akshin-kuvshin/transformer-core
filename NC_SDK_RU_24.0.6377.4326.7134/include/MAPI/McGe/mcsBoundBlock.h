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

#include <math.h>
#include <float.h>

#include "McsTypes.h"
#include "McsTempl.h"
#include "mcsutils.h"

#include "McAPIs.h"

#include "McGe\mcgbl.h"
#include "McGe\mcpnt3d.h"
#include "McGe\mcmat2d.h"
#include "McGe\mcmat3d.h"

struct mcsSphere;
class mcsGeomEntArray;
class McGeBoundBlock3d;

#define _MCS_BND_INVALIDVAL_V1 (double)(__int64)0xBAAAF000BAAAF000L // blocks v1
#define _MCS_BND_INVALIDVAL    1.010101010101e-11 // blocks v2
#define _MCS_BND_ZERO          1e-5
#define _MCS_BND_MINLEN        (2*_MCS_BND_ZERO)

//==================================================================================================

enum mcsBBLK_TypeEnum
{
	kMBBT_Empty = 0,
	kMBBT_Pt    = 1,
	kMBBT_Line  = 2,
	kMBBT_Plane = 3,
	kMBBT_Full  = 4
};

//==================================================================================================

#pragma pack(push, 1)
class mcsBoundBlock
{
protected:

#ifdef _MCEYE
public:
#endif
	bool             m_fOrtogonal;
	McGePoint3dArray m__points; // used for geometry optimizations in extendTo method
	bool             m_fNeedMerge; // state of block have valid data only in <m__points>	member and needs merge operation

	McGePoint3d        m__base;
	McGeVector3d       m__dir[3];

	mutable bool         m_tfmValid; // валидна ли матрица m_wldToBlkTfm
	mutable McGeMatrix3d m_wldToBlkTfm; // преобразование координат из мировой в локальную СК блока, длины dir векторов сохранены (нет нормирования по m_dir[i])

public:

	__declspec(property(get = get_m_base, put = put_m_base)) McGePoint3d m_base;
	__declspec(property(get = get_m_dir, put = put_m_dir)) McGeVector3d m_dir[];

	MCGEL_API  const McGePoint3d& get_m_base() const;
	MCGEL_API  McGePoint3d& get_m_base();
	MCGEL_API  McGePoint3d& put_m_base(const McGePoint3d& pt);
	MCGEL_API  const McGeVector3d& get_m_dir(int idx) const;
	MCGEL_API  McGeVector3d& get_m_dir(int idx);
	MCGEL_API  McGeVector3d& put_m_dir(int idx, const McGeVector3d& iDir);

public:

	MCGEL_API  mcsBoundBlock(bool fOrtogonal=false);
	MCGEL_API  mcsBoundBlock(IN const McGeBoundBlock3d&); // AcGe conversion
	MCGEL_API  ~mcsBoundBlock();

	DECLARE_OBJ_NEWDEL;

	// edit methods
	// !!! set for orthogonal blocks will automatically
	// !!! extracts and stores orthogonal equivalent from input data
	MCGEL_API mcsBoundBlock& set(
		IN const McGePoint3d&  newBase,
		IN const McGeVector3d& newDir1,
		IN const McGeVector3d& newDir2,
		IN const McGeVector3d& newDir3 = McGeVector3d(0,0,0));

	MCGEL_API  mcsBoundBlock& extendTo(IN const McGePoint3d& pt);
	MCGEL_API  mcsBoundBlock& mergeWith(IN const mcsBoundBlock&);
	MCGEL_API  mcsBoundBlock& swell(IN double distance);
	MCGEL_API  mcsBoundBlock& mirror(IN const McGePlane& mirrorPlane);
	MCGEL_API  mcsBoundBlock& invalidate();
	MCGEL_API  mcsBoundBlock& operator =(IN const mcsBoundBlock& copyFrom);
	MCGEL_API  mcsBoundBlock& operator =(IN const McGeBoundBlock3d& copyFrom); // AcGe conversion
	MCGEL_API  static mcsBoundBlock merge(IN const mcsBoundBlock* pBlocks,IN int nBlocks,IN OPTIONAL bool fForceOrtogonalMerge=false);
	MCGEL_API  static mcsBoundBlock merge(IN const McGePoint3d* pPoints, IN int nPoints, IN OPTIONAL bool fForceOrtogonalMerge=false);
	MCGEL_API  static mcsBoundBlock mergePointsWithTol(IN const McGePoint3d* pPoints, IN int nPoints, IN OPTIONAL double tol = -1);

	// метод строит блок по точкам с заданной точностью
	// в отличие от метода без точности не делает блок ортогональным, даже если он будет меньшего объёма
	MCGEL_API  static mcsBoundBlock mergeEx(
		IN const McGePoint3d* pPoints,
		IN int             nPoints,
		IN OPTIONAL bool   bMakeOrtogonal = false,
		IN OPTIONAL double tol = -1);

	// scaling
	MCGEL_API  mcsBoundBlock   operator *(double scale) const;
	MCGEL_API  mcsBoundBlock   operator /(double scale) const;
	MCGEL_API  mcsBoundBlock&  operator *=(double scale);
	MCGEL_API  mcsBoundBlock&  operator /=(double scale);

	// transformation
	MCGEL_API mcsBoundBlock& rotateBy(
		IN double angle_rad,
		IN const McGeVector3d& axis,
		IN OPTIONAL const McGePoint3d& wrtPoint = McGePoint3d::kOrigin);

	MCGEL_API  mcsBoundBlock& translateBy(IN const McGeVector3d& offsetVector);
	MCGEL_API  mcsBoundBlock& transformBy(IN const McGeMatrix3d& tfm);

	// query methods
	MCGEL_API  bool   isValid() const;
	MCGEL_API  bool   getMinMaxPoints(OUT McGePoint3d& minPt, OUT McGePoint3d& maxPt) const;

		//          5------4
		//         /|     /|   Dirs legend:
		//        3------6 |     -- dir0
		//        | |    | |     /  dir1
		//        | 2----|-7     |  dir2
		//        |/     |/
		// (base) 0------1
		//
		// sides (нормаль направлена наружу):
		//   0: bottom
		//   1: front
		//   2: left
		//   3: top
		//   4: back
		//   5: right
	MCGEL_API  bool   getCorners(OUT McGePoint3d cornerPts[8]) const;

		//        Y (dir1)
		//        ^
		//        3----2
		//        |    |
		// (base) 0----1 -> X (dir0)
	MCGEL_API  bool   get2dCorners(OUT McGePoint3d cornerPts[4]) const;

	MCGEL_API  bool   contains(IN const McGePoint3d& pt, IN OPTIONAL double PV_TOLERANCE = DEF_TOL) const;
	MCGEL_API  bool   contains(IN const mcsBoundBlock& pt, IN OPTIONAL double PV_TOLERANCE = DEF_TOL) const;
	MCGEL_API  double distanceTo(IN const McGePoint3d& pt) const;
	MCGEL_API  double distanceTo(IN const mcsBoundBlock& otherBlock, IN OPTIONAL double PV_TOLERANCE = DEF_TOL, OUT OPTIONAL bool* pbIntersects = NULL) const;
	MCGEL_API  bool   isDisjoint(IN const mcsBoundBlock& otherBlock, IN OPTIONAL double PV_TOLERANCE = DEF_TOL) const;

		// helpers
	MCGEL_API  double    getDx() const;
	MCGEL_API  double    getDy() const;
	MCGEL_API  double    getDz() const;
	MCGEL_API  McGeVector3d getDxyz() const; // координаты - это dx,dy,dz
	MCGEL_API  McGePoint3d  getCenter() const;

	// 10.11.2010, AGL, упрощенный алгоритм для плоских блоков в плоскости XOY;
	// Проверки на "z" нет вообще!
	// Использовать только если гарантированно блоки в XOY!
	// Сохранена проверка на вырожденность блоков в линию и точку;
	// Ускорение в дебаге до 4 раз, в релизе до 3х по сравнению с полной версией
	MCGEL_API  bool             isDisjoint_XOY(IN const mcsBoundBlock& otherBlock, IN OPTIONAL double PV_TOLERANCE = DEF_TOL) const;

	MCGEL_API  mcsBoundBlock    getOrthogonal() const;
	MCGEL_API  mcsBoundBlock&   makeOrthogonal();

	MCGEL_API  operator McGeBoundBlock3d () const;

	MCGEL_API  bool asSphere(OUT mcsSphere& s) const;

	// comparison
	MCGEL_API  bool isEqualTo(IN const mcsBoundBlock& cmpWith, IN OPTIONAL double PV_TOLERANCE = DEF_TOL) const;
	MCGEL_API  bool operator == (IN const mcsBoundBlock& cmpWith) const;
	MCGEL_API  bool operator != (IN const mcsBoundBlock& cmpWith) const;

	MCTYP_API  HRESULT save(IMcsStream* pS) const;
	MCTYP_API  HRESULT load(IMcsStream* pS);

	MCGEL_API  bool isOrthogonal() const;

	MCGEL_API  mcsBBLK_TypeEnum getMBBType() const;

		// для отладки: получить графику предпросмотра
	MCTYP_API void _getPreview(OUT mcsGeomEntArray& geom) const;

	MCGEL_API double volume() const;

	MCGEL_API bool is2D(double dTol = McGeContext::gTol.equalPoint()) const;

	friend class McGeBoundBlock3d;

	MCGEL_API void getHelperInfo(
		OUT McGePoint3d                vertices[8],
		OUT OPTIONAL McGePlane         sides[6] = NULL,
		OUT OPTIONAL mcsBBLK_TypeEnum* pBlockType = NULL,
		IN OPTIONAL bool               bFillAllData = false) const;

protected:
	MCGEL_API static mcsBoundBlock _orthogonalMerge(IN const McGePoint3d*, IN int, IN OPTIONAL bool);
	MCGEL_API void _updateMerge() const;
	MCGEL_API bool _normalizeBlock(double tol = -1, bool bAdjustToGCS = false);
};
#pragma pack(pop)

typedef McsArray<mcsBoundBlock> mcsBoundBlocksArray;
//==================================================================================================
