#ifndef __POINTCLOUDINSERTION_H__
#define __POINTCLOUDINSERTION_H__

#include "Exports.h"
#include "PointCloudDefs.h"
#include "PointCloudInfo.h"
#include "PointCloudDefinition.h"
#include "VisualizationParams.h"
#include "PointCloudVertexIterator.h"

namespace NPC_API
{
  struct PointCloudInsertionImpl;

  class PointCloudBridge;

  class PointCloudInsertion
  {
    friend struct NPC_API::PointCloudBridgeImpl;
    friend class NPC_API::PointCloudBridge;

  protected:
    PointCloudInsertionImpl*                      m_pImpl;

  protected: 
                                                  PointCloudInsertion();

  public:
    _EXPORT                                       ~PointCloudInsertion();
    _EXPORT PointCloudInsertion&                  operator=(const PointCloudInsertion& rhs);
    _EXPORT                                       PointCloudInsertion(const PointCloudInsertion& rhs);
    //@}
    //! definition
    //@{ 
    _EXPORT PointCloudDefinition                  pointCloudDefinition(NcDb::OpenMode _mode = NcDb::kForRead) const;
    //@}
    //! transforms
    //@{ 
    _EXPORT bool                                  transformBy(const _Matrix3d&);
    //@}
    //! point index
    //@{ 
    _EXPORT bool                                  translateGsMarkerToPointIndex(_GsMarker, _CompositeIndexType&) const;
    //@}
    //! iterators
    //@{ 
    _EXPORT PointCloudVertexIterator              getAllVertexIterator(_ViewportHandle _uViewHandle = _NO_VIEWPORT,
                                                                       bool _bUpdateOnReleasing = true, bool _bProgress = false);
    _EXPORT PointCloudVertexIterator              getHybridVertexIterator(const Clipping& _Clipping,
                                                                          _ViewportHandle _uViewHandle = _NO_VIEWPORT,
                                                                          bool _bUpdateOnReleasing = true, bool _bProgress = false);
    _EXPORT PointCloudVertexIterator              getLevelVertexIterator(_TreeLevelType _level, bool _onlyPointsOfThisLevel,
                                                                         _ViewportHandle _uViewHandle = _NO_VIEWPORT,
                                                                         bool _bUpdateOnReleasing = true, bool _bProgress = false);
    //@}
    //! point cloud information
    //@{ 
    _EXPORT PointCloudInfo                        getCloudInfo(_ViewportHandle uViewHandle = _NO_VIEWPORT) const;
    _EXPORT _TreeLevelType                        getTreeLevelCount() const;
    _EXPORT _TreeLevelType                        getMinLevelToShow() const;
    _EXPORT void                                  setMinLevelToShow(_TreeLevelType);
    _EXPORT _TreeLevelType                        getMaxLevelToShow() const;
    _EXPORT void                                  setMaxLevelToShow(_TreeLevelType);
    //@}
    //! visualization params
    //@{ 
    _EXPORT VisualizationParams                   createVisualizationParamsSet() const;
    _EXPORT VisualizationParams                   createVisualizationParamsSetFrom(_VisualizationParamIndex) const;
    _EXPORT VisualizationParams                   createVisualizationParamsSetFrom(_ViewportHandle) const;
    _EXPORT VisualizationParams                   getVisualizationParamsSet(_VisualizationParamIndex) const;
    _EXPORT VisualizationParams                   getVisualizationParamsSet(_ViewportHandle) const;
    _EXPORT _VisualizationParamIndex              setVisualizationParamsSetToViewport(const VisualizationParams&,
                                                                                      _VisualizationParamIndex);
    _EXPORT bool                                  removeVisualizationParamsSet(_ViewportHandle );
    _EXPORT bool                                  removeVisualizationParamsSet(_VisualizationParamIndex);
    _EXPORT void                                  resetVisualizationParamsStorage();

    _EXPORT bool                                  isClipped(_ViewportHandle) const;
    _EXPORT _VisualizationParamIndex              getVisualizationParamsSetIndex(_ViewportHandle) const;
  };
}

#endif