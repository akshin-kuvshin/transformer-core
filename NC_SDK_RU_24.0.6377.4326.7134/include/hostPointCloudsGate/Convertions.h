#ifndef __CONVERTIONS_H__
#define __CONVERTIONS_H__

#include "PointCloudDefs.h"
#include "iProgressBar.h"
#include "Exports.h"

#include <map>
#include "Bitset.h"

#include "usingHostDbPointClouds.h"

using namespace NPC_API;

__forceinline const OdGeMatrix3d& asOdGeMatrix3d(const _Matrix3d& _data)
{
  return reinterpret_cast<const OdGeMatrix3d&>(_data);
}
__forceinline const _Matrix3d& as_Matrix3d(const OdGeMatrix3d& _data)
{
  return reinterpret_cast<const _Matrix3d&>(_data);
}
_EXPORT_STATIC static const _Matrix3d IDENTITY_MATRIX;

__forceinline const OdGePoint3d& asOdGePoint3d(const _Point3d& _data)
{
  return reinterpret_cast<const OdGePoint3d&>(_data);
}
__forceinline const _Point3d& as_Point3d(const OdGePoint3d& _data)
{
  return reinterpret_cast<const _Point3d&>(_data);
}

__forceinline const OdGeVector3d& asOdGeVector3d(const _Vector3d& _data)
{
  return reinterpret_cast<const OdGeVector3d&>(_data);
}
__forceinline const _Vector3d& as_Vector3d(const OdGeVector3d& _data)
{
  return reinterpret_cast<const _Vector3d&>(_data);
}

__forceinline const OdGePoint2d& asOdGePoint2d(const _Point2d& _data)
{
  return reinterpret_cast<const OdGePoint2d&>(_data);
}
__forceinline const _Point2d& as_Point2d(const OdGePoint2d& _data)
{
  return reinterpret_cast<const _Point2d&>(_data);
}

__forceinline const OdGePoint3dArray& asOdGePoint3dArray(const _Point3dArray& _data)
{
  return reinterpret_cast<const OdGePoint3dArray&>(_data);
}
__forceinline const _Point3dArray& as_Point3dArray(const OdGePoint3dArray& _data)
{
  return reinterpret_cast<const _Point3dArray&>(_data);
}

__forceinline const OdGePoint2dArray& asOdGePoint2dArray(const _Point2dArray& _data)
{
  return reinterpret_cast<const OdGePoint2dArray&>(_data);
}
__forceinline const _Point2dArray& as_Point2dArray(const OdGePoint2dArray& _data)
{
  return reinterpret_cast<const _Point2dArray&>(_data);
}
_EXPORT_STATIC static const _Point2dArray EMPTY_POINT2D_ARRAY;

__forceinline std::map<TTreeTraits::TT_LEVEL_TYPE, TTreeTraits::TT_NODE_INDEX_TYPE>& toLevelsHistogram(std::map<_TreeLevelType, _NodeIndexType>& _data)
{
  return reinterpret_cast<std::map<TTreeTraits::TT_LEVEL_TYPE, TTreeTraits::TT_NODE_INDEX_TYPE>&>(_data);
}

__forceinline std::map<TTreeTraits::TT_POINT_INDEX_TYPE, TTreeTraits::TT_NODE_INDEX_TYPE>& toNodesHistogram(std::map<_PointIndexType, _NodeIndexType>& _data)
{
  return reinterpret_cast<std::map<TTreeTraits::TT_POINT_INDEX_TYPE, TTreeTraits::TT_NODE_INDEX_TYPE>&>(_data);
}

__forceinline const BITSET::BitSet<_ClassType>& fromClassBitSet(const BITSET::BitSet<TDataScheme::TD_CLASS_TYPE>& _data)
{
  return *(const BITSET::BitSet<_ClassType>*)&_data;
}

__forceinline const BITSET::BitSet<_EchoNumberType>& fromEchoNumberBitSet(const BITSET::BitSet<TDataScheme::TD_ECHO_NUMBER_TYPE>& _data)
{
  return *(const BITSET::BitSet<_EchoNumberType>*)&_data;
}

__forceinline const std::map<_IntencityType, _CompositeIndexType>& fromIntencityHistogram(const std::map<TDataScheme::TD_INTENSITY_TYPE, TTreeTraits::TT_COMPOSITE_INDEX_TYPE>& _data)
{
  return *(const std::map<_IntencityType, _CompositeIndexType>*)&_data;
}

__forceinline const std::map<_ClassType, _CompositeIndexType>& fromClassHistogram(const std::map<TDataScheme::TD_CLASS_TYPE, TTreeTraits::TT_COMPOSITE_INDEX_TYPE>& _data)
{
  return *(const std::map<_ClassType, _CompositeIndexType>*)&_data;
}

__forceinline const std::map<_EchoNumberType, _CompositeIndexType>& fromEchoNumberHistogram(const std::map<TDataScheme::TD_ECHO_NUMBER_TYPE, TTreeTraits::TT_COMPOSITE_INDEX_TYPE>& _data)
{
  return *(const std::map<_EchoNumberType, _CompositeIndexType>*) & _data;
}
#endif
