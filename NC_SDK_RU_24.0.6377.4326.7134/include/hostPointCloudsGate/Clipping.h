#ifndef __CLIPPING_H__
#define __CLIPPING_H__

#include "Exports.h"
#include "PointCloudDefs.h"

namespace NPC_API
{
  struct ClippingImpl;
  class PointCloudInfo;
  class GeometricFeature;
  class VisualizationParams;
  class PointCloudInsertion;
  class PointCloudDefinition;

  class GeometryClippingElement;
  class GeometryClippingStack;
  class AttributeClippingByFeature;
  class AttributeClippingByFeatureType;
  class AttributeClippingByDeviation;
  class AttributeClippingByEchoNumber;
  class AttributeClippingByCode;
  class AttributeClippingByFeature;
  class AttributeClippingBySourceId;
  class AttributeClippingByDeviation;
  class AttributeClippingByFeatureType;
  class AttributeClippingStack;
  class ClippingStack;
  //@}
  //! base wrapper
  //@{ 
  class Clipping
  {
    friend class NPC_API::GeometryClippingElement;
    friend class NPC_API::GeometryClippingStack;
    friend class NPC_API::AttributeClippingByFeature;
    friend class NPC_API::AttributeClippingByFeatureType;
    friend class NPC_API::AttributeClippingByDeviation;
    friend class NPC_API::AttributeClippingByEchoNumber;
    friend class NPC_API::AttributeClippingByCode;
    friend class NPC_API::AttributeClippingByFeature;
    friend class NPC_API::AttributeClippingBySourceId;
    friend class NPC_API::AttributeClippingByDeviation;
    friend class NPC_API::AttributeClippingByFeatureType;
    friend class NPC_API::AttributeClippingStack;
    friend class NPC_API::ClippingStack;

    friend class NPC_API::GeometricFeature;
    friend class NPC_API::VisualizationParams;
    friend class NPC_API::PointCloudInsertion;
    friend class NPC_API::PointCloudDefinition;
    friend struct NPC_API::PointCloudBridgeImpl;

  protected:
    ClippingImpl*                                 m_pImpl;

  public:
    _EXPORT                                       Clipping();
    _EXPORT virtual                               ~Clipping();

    _EXPORT bool                                  operator==(const Clipping& rhs);
    __forceinline bool                            operator!=(const Clipping& rhs)
    {
      return !this->operator==(rhs);
    }
    _EXPORT Clipping&                             operator=(const Clipping& rhs);
    _EXPORT                                       Clipping(const Clipping& rhs);

    enum class _ClippingElementType  : unsigned __int32
    {
      ZERO = 1,
      IDENTITY = 2,
      GEOMETRY = 3,
      GEOMETRY_STACK = 4,
      ATTRIBUTE_BY_ECHO = 5,
      ATTRIBUTE_BY_CODE = 6,
      ATTRIBUTE_STACK = 7,
      STACK = 8,
      ATTRIBUTE_BY_DEVIATION = 9,
      ATTRIBUTE_BY_FEATURE = 10,
      ATTRIBUTE_BY_FEATURE_TYPE
      = 11,
      ATTRIBUTE_BY_SOURCE_ID = 12,
    };

    _EXPORT _ClippingElementType                  getType() const;

    _EXPORT bool                                  isInverted() const;
    _EXPORT bool                                  canBeInverted() const;
    _EXPORT void                                  setInverted(bool);

    _EXPORT Clipping&                             operator+=(const Clipping& rhs);
    __forceinline Clipping                        operator+(const Clipping& rhs) const
    {
      Clipping temp(rhs);
      return temp += rhs;
    }
    _EXPORT Clipping&                             operator*=(const Clipping& rhs);
    __forceinline Clipping                        operator*(const Clipping& rhs) const
    {
      Clipping temp(rhs);
      return temp *= rhs;
    }
    _EXPORT Clipping&                             operator-=(const Clipping& rhs);
    __forceinline Clipping                        operator-(const Clipping& rhs) const
    {
      Clipping temp(rhs);
      return temp -= rhs;
    }

    _EXPORT void                                  transformBy(const _Matrix3d&);
    _EXPORT void                                  setCoordinateSystem(const _Point3d&,
                                                                      const _Vector3d&,
                                                                      const _Vector3d&,
                                                                      const _Vector3d&);

    _EXPORT bool                                  isZero() const;
    _EXPORT bool                                  isIdentity() const;
    _EXPORT bool                                  isZeroBy(const PointCloudInfo&) const;
    _EXPORT bool                                  isIdentityBy(const PointCloudInfo&) const;
  };
  //@}
  //! empty clipping
  //@{ 
  class ZeroClipping : public Clipping
  {
  public:
    _EXPORT                                       ZeroClipping();
    _EXPORT virtual                               ~ZeroClipping() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::ZERO);
    }
    static _EXPORT ZeroClipping                   asType(const Clipping& rhs);// throws PointCloudException
  };
  //@}
  //! identity clipping
  //@{ 
  class IdentityClipping : public Clipping
  {
  public:
    _EXPORT                                       IdentityClipping();
    _EXPORT virtual                               ~IdentityClipping() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::IDENTITY);
    }
    static _EXPORT IdentityClipping               asType(const Clipping& rhs);// throws PointCloudException
  };
  //@}
  //! geometry clipping
  //@{ 
  class GeometryClippingElement : public Clipping
  {
  public:
    _EXPORT                                       GeometryClippingElement();
    _EXPORT virtual                               ~GeometryClippingElement() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::GEOMETRY);
    }
    static _EXPORT GeometryClippingElement        asType(const Clipping& rhs);// throws PointCloudException

    _EXPORT const _Matrix3d&                      getCoordinateSystem() const;

    _EXPORT bool                                  isValid() const;
    _EXPORT void                                  setBox(const _Point3d&, const _Point3d&);
    _EXPORT void                                  setSphere(const _Point3d&, double);
    _EXPORT void                                  setCylinder(const _Point3d&, double, double);
    _EXPORT void                                  setRectangle(const _Point2d&, const _Point2d&);
    _EXPORT void                                  setBoundary(const _Point2dArray&);
     
    _EXPORT void                                  setZMax(double);
    _EXPORT void                                  setZMin(double);
    _EXPORT double                                getZMin() const;
    _EXPORT double                                getZMax() const;

    _EXPORT const _Point2dArray&                  getVertices() const;

    enum class _GeometryClippingType : unsigned __int32
    {
      UNKNOWN = 0,
      BOX = 1,
      RECTANGLE = 2,
      POLYLINE = 3,
      SPHERE = 4,
      CYLINDER = 5,
    };
    _EXPORT _GeometryClippingType                 getGeometryType() const;
  };
  //@}
  //! geometry clipping stack
  //@{ 
  class GeometryClippingStack : public Clipping
  {
  public:
    _EXPORT                                       GeometryClippingStack();
    _EXPORT virtual                               ~GeometryClippingStack() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::GEOMETRY_STACK);
    }
    static _EXPORT GeometryClippingStack          asType(const Clipping& rhs);// throws PointCloudException

    _EXPORT unsigned                              getStackDepth() const;
    _EXPORT Clipping                              getElement(unsigned) const;
    _EXPORT void                                  changeElement(unsigned, const Clipping&);
    _EXPORT bool                                  pushElement(const Clipping&);
    _EXPORT bool                                  removeElement(unsigned);
    _EXPORT Clipping                              lastElement();
    _EXPORT bool                                  popElement();
    _EXPORT void                                  resetStack();
  };
  //@}
  //! feature clipping
  //@{ 
  class AttributeClippingByFeature : public Clipping
  {
  public:
    _EXPORT                                       AttributeClippingByFeature();
    _EXPORT virtual                               ~AttributeClippingByFeature() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::ATTRIBUTE_BY_FEATURE);
    }
    static _EXPORT AttributeClippingByFeature     asType(const Clipping& rhs);// throws PointCloudException

    _EXPORT bool                                  isEmpty() const;
    _EXPORT void                                  addFeature(_GeometricFeatureType);
    _EXPORT void                                  removeFeature(_GeometricFeatureType);
    _EXPORT bool                                  containsFeature(_GeometricFeatureType) const;
  };
  //@}
  //! feature type clipping
  //@{ 
  class AttributeClippingByFeatureType : public Clipping
  {
  public:
    _EXPORT                                       AttributeClippingByFeatureType();
    _EXPORT virtual                               ~AttributeClippingByFeatureType() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::ATTRIBUTE_BY_FEATURE_TYPE);
    }
    static _EXPORT AttributeClippingByFeatureType asType(const Clipping& rhs);// throws PointCloudException

    _EXPORT bool                                  isEmpty() const;
    _EXPORT void                                  addType(_TypeOfGeometricFeature);
    _EXPORT void                                  removeType(_TypeOfGeometricFeature);
    _EXPORT bool                                  containsType(_TypeOfGeometricFeature) const;
  };
  //@}
  //! deviation clipping
  //@{ 
  class AttributeClippingByDeviation : public Clipping
  {
  public:
    _EXPORT                                       AttributeClippingByDeviation();
    _EXPORT virtual                               ~AttributeClippingByDeviation() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::ATTRIBUTE_BY_DEVIATION);
    }
    static _EXPORT AttributeClippingByDeviation   asType(const Clipping& rhs);// throws PointCloudException

    _EXPORT bool                                  isEmpty() const;
    _EXPORT _DeviationType                        getMinDist() const;
    _EXPORT _DeviationType                        getMaxDist() const;
    _EXPORT void                                  setMinDist(_DeviationType);
    _EXPORT void                                  setMaxDist(_DeviationType);
  };
  //@}
  //! echo clipping
  //@{ 
  class AttributeClippingByEchoNumber : public Clipping
  {
  public:
    _EXPORT                                       AttributeClippingByEchoNumber();
    _EXPORT virtual                               ~AttributeClippingByEchoNumber() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::ATTRIBUTE_BY_ECHO);
    }
    static _EXPORT AttributeClippingByEchoNumber  asType(const Clipping& rhs);// throws PointCloudException

    _EXPORT bool                                  isEmpty() const;
    _EXPORT void                                  addEchoNumber(_EchoNumberType);
    _EXPORT void                                  removeEchoNumber(_EchoNumberType);
    _EXPORT bool                                  containsEchoNumber(_EchoNumberType) const;
  };
  //@}
  //! code clipping
  //@{ 
  class AttributeClippingByCode : public Clipping
  {
  public:
    _EXPORT                                       AttributeClippingByCode();
    _EXPORT virtual                               ~AttributeClippingByCode() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::ATTRIBUTE_BY_CODE);
    }
    static _EXPORT AttributeClippingByCode        asType(const Clipping& rhs);// throws PointCloudException

    _EXPORT bool                                  isEmpty() const;
    _EXPORT void                                  addCode(_ClassType);
    _EXPORT void                                  removeCode(_ClassType);
    _EXPORT bool                                  containsCode(_ClassType) const;
  };
  //@}
  //! source id clipping
  //@{ 
  class AttributeClippingBySourceId : public Clipping
  {
  public:
    _EXPORT                                       AttributeClippingBySourceId();
    _EXPORT virtual                               ~AttributeClippingBySourceId() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::ATTRIBUTE_BY_SOURCE_ID);
    }
    static _EXPORT AttributeClippingBySourceId    asType(const Clipping& rhs);// throws PointCloudException

    _EXPORT bool                                  isEmpty() const;
    _EXPORT void                                  addSourceId(_SourceIDType);
    _EXPORT void                                  removeSourceId(_SourceIDType);
    _EXPORT bool                                  containsSourceId(_SourceIDType) const;
  };
  //@}
  //! attribute clipping stack
  //@{ 
  class AttributeClippingStack : public Clipping
  {
  public:
    _EXPORT                                       AttributeClippingStack();
    _EXPORT virtual                               ~AttributeClippingStack() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::ATTRIBUTE_STACK);
    }
    static _EXPORT AttributeClippingStack         asType(const Clipping& rhs);// throws PointCloudException

    _EXPORT unsigned                              getStackDepth() const;
    _EXPORT Clipping                              getElement(unsigned) const;
    _EXPORT void                                  changeElement(unsigned, const Clipping&);
    _EXPORT bool                                  pushElement(const Clipping&);
    _EXPORT bool                                  removeElement(unsigned);
    _EXPORT bool                                  popElement();
    _EXPORT void                                  resetStack();
  };
  //@}
  //! general clipping stack
  //@{ 
  class ClippingStack : public Clipping
  {
  public:
    _EXPORT                                       ClippingStack();
    _EXPORT virtual                               ~ClippingStack() {}

    __forceinline static bool                     isA(const Clipping& rhs)
    {
      return (rhs.getType() == Clipping::_ClippingElementType::STACK);
    }
    static _EXPORT ClippingStack                  asType(const Clipping& rhs);// throws PointCloudException

    _EXPORT bool                                  isGeometryClipping() const;
    _EXPORT bool                                  isAttributeClipping() const;
    _EXPORT Clipping                              getGeometryClipping() const;
    _EXPORT void                                  changeGeometryClipping(const Clipping&);
    _EXPORT Clipping                              getAttributeClipping() const;
    _EXPORT void                                  changeAttributeClipping(const Clipping&);
    _EXPORT bool                                  removeGeometryClipping();
    _EXPORT bool                                  removeAttributeClipping();
    _EXPORT void                                  resetStack();
  };
}
#endif