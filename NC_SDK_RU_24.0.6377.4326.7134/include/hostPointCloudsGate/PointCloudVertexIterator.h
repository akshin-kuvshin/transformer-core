#ifndef __POINTCLOUDVERTEXITERATOR_H__
#define __POINTCLOUDVERTEXITERATOR_H__

#include "Exports.h"
#include "PointCloudDefs.h"
#include "PointCloudInfo.h"

namespace NPC_API
{
  struct PointCloudVertexIteratorImpl;

  class PointCloudInsertion;
  class PointCloudDefinition;
  class RandomPointCloudVertexIterator;

  class PointCloudVertexIterator
  {
    friend class NPC_API::PointCloudInsertion;
    friend class NPC_API::PointCloudDefinition;
    friend struct NPC_API::PointCloudBridgeImpl;

  protected:
    PointCloudVertexIteratorImpl*                 m_pImpl;

  protected:
                                                  PointCloudVertexIterator();

  public:
    _EXPORT virtual                               ~PointCloudVertexIterator();
    _EXPORT PointCloudVertexIterator&             operator=(const PointCloudVertexIterator& rhs);
    _EXPORT                                       PointCloudVertexIterator(const PointCloudVertexIterator& rhs);

    _EXPORT bool                                  isRandomIterator() const;
    _EXPORT RandomPointCloudVertexIterator        asRandomIterator() const;

    _EXPORT bool                                  IsReadOnly() const;
    _EXPORT bool                                  IsEmpty() const;
    _EXPORT bool                                  IsEnd() const;
    _EXPORT bool                                  IsFirst() const;
    _EXPORT bool                                  MoveFirst();
    _EXPORT bool                                  MoveLast();
    _EXPORT bool                                  Next();
    _EXPORT bool                                  Prev();
    _EXPORT _CompositeIndexType                   GetSize() const;
    _EXPORT _CompositeIndexType                   GetIndex() const;
    _EXPORT bool                                  IsIndexValid(_CompositeIndexType) const;
    _EXPORT bool                                  SetIteratorTo(_CompositeIndexType);

    _EXPORT double                                getX() const;
    _EXPORT double                                getY() const;
    _EXPORT double                                getZ() const;
    _EXPORT bool                                  setXYZ(double, double, double);
    _EXPORT _Point3d                              getVertex() const;
    _EXPORT _RGBType                              getColor() const;
    _EXPORT bool                                  setVertex(const _Point3d&);

    _EXPORT _Point3d                              getBaseVertex() const;
    _EXPORT PointCloudInfo                        getCloudInfo() const;

    _EXPORT _IntencityType                        getIntensity() const;
    _EXPORT bool                                  setIntensity(_IntencityType);

    _EXPORT _EchoNumberType                       getEchoNumber() const;
    _EXPORT bool                                  setEchoNumber(_EchoNumberType);

    _EXPORT _EchoCountType                        getEchoCount() const;
    _EXPORT bool                                  setEchoCount(_EchoCountType);

    _EXPORT _ScanDirectionType                    getScanDirection() const;
    _EXPORT bool                                  setScanDirection(_ScanDirectionType);

    _EXPORT _EdgeOfFlightLineType                 getEdgeOfFlightLine() const;
    _EXPORT bool                                  setEdgeOfFlightLine(_EdgeOfFlightLineType);

    _EXPORT _ScanAngleRankType                    getScanAngleRank() const;
    _EXPORT bool                                  setScanAngleRank(_ScanAngleRankType);

    _EXPORT _ClassType                            getClass() const;
    _EXPORT bool                                  setClass(_ClassType);

    _EXPORT _TimeType                             getTime() const;
    _EXPORT bool                                  setTime(_TimeType);

    _EXPORT _RGBType                              getColorRGB() const;
    _EXPORT bool                                  setColorRGB(_RGBType);

    _EXPORT _SourceIDType                         getSourceID() const;
    _EXPORT bool                                  setSourceID(_SourceIDType);

    _EXPORT _NormalType                           getNormal() const;
    _EXPORT bool                                  setNormal(const _NormalType&);

    _EXPORT _DeviationType                        getDeviation() const;
    _EXPORT bool                                  setDeviation(_DeviationType);

    _EXPORT _GeometricFeatureType                 getGeometricFeature() const;
  };
}

#endif