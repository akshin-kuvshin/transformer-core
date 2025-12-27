
#pragma once

//==============================================================================

// The same values as in enum OdDb/AcDb::SubentType

enum McModSubentType
{
	kMcModSubentType_Null   = 0,
	kMcModSubentType_Face   = 1,
	kMcModSubentType_Edge   = 2,
	kMcModSubentType_Vertex = 3,
};
//==================================================================================================

// an analog for EntityGeometryTypeEnum

enum Mc3dModGeomEntType
{ 
	kMc3dModVertex          = 0x00000002,

	kMc3dModLine            = 0x00000100,
	kMc3dModCircArc         = 0x00000200,
	kMc3dModEllipticArc     = 0x00000400,
	kMc3dModSpline          = 0x00000800,
	kMc3dModPolyline        = 0x00001000,

	kMc3dModPlaneSegment    = 0x00010000,
	kMc3dModCylinderSegment = 0x00020000,
	kMc3dModConeSegment     = 0x00040000,
	kMc3dModTorusSegment    = 0x00080000,
	kMc3dModSphereSegment   = 0x00100000,
	kMc3dModTriangleSegment = 0x00200000,
	kMc3dModBSplineSegment  = 0x00400000,

	// composed values
	kMc3dModCurveEntities   = kMc3dModLine|kMc3dModCircArc|kMc3dModEllipticArc|kMc3dModSpline|kMc3dModPolyline,
	kMc3dModSurfaceEntities = kMc3dModPlaneSegment|kMc3dModCylinderSegment|kMc3dModConeSegment|kMc3dModTorusSegment|kMc3dModSphereSegment|kMc3dModTriangleSegment|kMc3dModBSplineSegment,
	kMc3dModAllEntities     = kMc3dModVertex|kMc3dModCurveEntities|kMc3dModSurfaceEntities,
};
//==================================================================================================

struct mc3dArrIndex
{
	int mIdx1;
	int mIdx2;

	mc3dArrIndex(){
		mIdx1 = 0;
		mIdx2 = 0;
	}

	mc3dArrIndex(int idx){
		mIdx1 = idx;
		mIdx2 = 0;
	}

	mc3dArrIndex(int idx1, int idx2){
		mIdx1 = idx1;
		mIdx2 = idx2;
	}

	bool operator == (const mc3dArrIndex& cw) const{
		return
			mIdx1 == cw.mIdx1 &&
			mIdx2 == cw.mIdx2;
	}

	bool operator != (const mc3dArrIndex& cw) const{
		return ! operator==(cw);
	}

	int getUniIdx1() {
		return mIdx1;
	}

	// нумерация эл-ов:
	// 15 14 13 12
	//  8  7  6 11
	//  3  2  5 10
	//  0  1  4  9 ...
	// Нумерация нужна для случаев, когда построитель массива использует сквозную нумерацию
	// элементов (ACIS, к примеру). В этом случае номер элемента вычисляется по формуле типа
	// n = i1 + i2 * n2
	// Если привязаться к такому номеру, то после изменения размерности номеру будет
	// соответствовать другая пара индексов. Uni-индекс же останется тем же.

	int getUniIdx2()
	{
		// TODO: вариант с "max" не собирается в csdev
		//int imx = max(mIdx1, mIdx2);
		int imx = mIdx1 > mIdx2 ? mIdx1 : mIdx2;

		int ir = imx * imx + mIdx2 + (imx - mIdx1);
		return ir;
	}
};

typedef McsArray<mc3dArrIndex, const mc3dArrIndex&> mc3dArrIndices;
//==============================================================================
