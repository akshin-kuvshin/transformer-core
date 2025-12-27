#ifndef __VISUALIZATIONPARAMS_H__
#define __VISUALIZATIONPARAMS_H__

#include "Exports.h"
#include "PointCloudDefs.h"
#include "PointCloudInfo.h"
#include "Clipping.h"
#include "Coloring.h"

namespace NPC_API
{
  struct VisualizationParamsImpl;

  class PointCloudInsertion;

  class VisualizationParams
  {
    friend struct NPC_API::PointCloudBridgeImpl;
    friend class NPC_API::PointCloudInsertion;

  protected:
   VisualizationParamsImpl*                       m_pImpl;

  protected:
                                                  VisualizationParams();

  public:
    _EXPORT                                       ~VisualizationParams();
    _EXPORT VisualizationParams&                  operator=(const VisualizationParams& rhs);
    _EXPORT                                       VisualizationParams(const VisualizationParams& rhs);

    _EXPORT Coloring                              getColoringParams() const;
    _EXPORT bool                                  setColoringParams(const Coloring&);

    _EXPORT _PointSize                            getPointSize() const;
    _EXPORT bool                                  setPointSize(_PointSize in_uPointSize);

    _EXPORT Clipping                              getClipping() const;
    _EXPORT void                                  changeClipping(const Clipping&);
    _EXPORT void                                  resetClipping();

    _EXPORT bool                                  isImplemented() const;
    _EXPORT bool                                  isEmpty() const;
    _EXPORT bool                                  isFullCloud() const;
    _EXPORT PointCloudInfo                        getCloudInfo() const;
  };
}

#endif