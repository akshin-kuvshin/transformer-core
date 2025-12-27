#ifndef __IMPLS_H__
#define __IMPLS_H__

#include "PointCloudDefs.h"
#include "usingHostDbPointClouds.h"
#include "..\PointCloud\Features\GeometricFeature.h"
//Fake objects for 
class CPlaneFeatureObj
{
public:
  static NPC::PlaneFeature createNULL()
  {
    return NPC::PlaneFeature(&NPC::PlaneFeature::NullFeature);
  }
};
class CPlanes2IntersectionFeatureObj
{
public:
  static NPC::Planes2IntersectionFeature createNULL()
  {
    return NPC::Planes2IntersectionFeature(&NPC::Planes2IntersectionFeature::NullFeature);
  }
};
class CPlanes3IntersectionFeatureObj
{
public:
  static NPC::Planes3IntersectionFeature createNULL()
  {
    return NPC::Planes3IntersectionFeature(&NPC::Planes3IntersectionFeature::NullFeature);
  }
};
class CCylinderFeatureObj
{
public:
  static NPC::CylinderFeature createNULL()
  {
    return NPC::CylinderFeature(&NPC::CylinderFeature::NullFeature);
  }
};
class CPipeFeatureObj
{
public:
  static NPC::PipeFeature createNULL()
  {
    return NPC::PipeFeature(&NPC::PipeFeature::NullFeature);
  }
};
class CSphereFeatureObj
{
public:
  static NPC::SphereFeature createNULL()
  {
    return NPC::SphereFeature(&NPC::SphereFeature::NullFeature);
  }
};
class CAggregateGeometricFeatureObj
{
public:
  static NPC::AggregateGeometricFeature createNULL()
  {
    return NPC::AggregateGeometricFeature(&NPC::AggregateGeometricFeature::NullFeature);
  }
};
class CConstructionGeometricFeatureObj
{
public:
  static NPC::ConstructionGeometricFeature createNULL()
  {
    return NPC::ConstructionGeometricFeature(&NPC::ConstructionGeometricFeature::NullFeature);
  }
};
class CTeeFeatureObj
{
public:
  static NPC::TeeFeature createNULL()
  {
    return NPC::TeeFeature(&NPC::TeeFeature::NullFeature);
  }
};
class CConeFeatureObj
{
public:
  static NPC::ConeFeature createNULL()
  {
    return NPC::ConeFeature(&NPC::ConeFeature::NullFeature);
  }
};
class CTorusFeatureObj
{
public:
  static NPC::TorusFeature createNULL()
  {
    return NPC::TorusFeature(&NPC::TorusFeature::NullFeature);
  }
};
//Impls
namespace NPC_API
{
  template<class T>
    void SafeDeleteImpl(T*& pPointer)
    {
      if (pPointer)
      {
        if (pPointer->numRefs() == 1)
          delete pPointer;
        else
          pPointer->release();
        pPointer = nullptr;
      }
    }

  struct Impl : public OdRxObject
  {
  };

  struct ClippingImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    std::unique_ptr<NPC::Clipping_Element> m_pElement;

    ClippingImpl() {}
    ~ClippingImpl() {}

    ClippingImpl(const NPC::Clipping& _pClipping)
    {
      m_pElement.reset(((NPC::Clipping_Element*)_pClipping)->clone());
      if (m_pElement == nullptr)
        ODA_FAIL_ONCE();
    }
    __forceinline bool operator==(const ClippingImpl& rhs)
    {
      ODA_ASSERT(m_pElement != nullptr);
      ODA_ASSERT(rhs.m_pElement != nullptr);
      return (*m_pElement == *rhs.m_pElement);
    }
    __forceinline bool operator!=(const ClippingImpl& rhs)
    {
      return !operator==(rhs);
    }

    __forceinline NPC::Clipping_Element* asClippingElement()
    {
      return m_pElement.get();
    }
    __forceinline NPC::GeometryClipping_Element* asGeometryClippingElement()
    {
      return static_cast<NPC::GeometryClipping_Element*>(m_pElement.get());
    }
    __forceinline NPC::GeometryClipping_Stack* asGeometryClippingStack()
    {
      return static_cast<NPC::GeometryClipping_Stack*>(m_pElement.get());
    }
    __forceinline NPC::AttributeClippingByFeature* asAttributeClippingByFeature()
    {
      return static_cast<NPC::AttributeClippingByFeature*>(m_pElement.get());
    }
    __forceinline NPC::AttributeClippingByFeatureType* asAttributeClippingByFeatureType()
    {
      return static_cast<NPC::AttributeClippingByFeatureType*>(m_pElement.get());
    }
    __forceinline NPC::AttributeClippingByDeviation* asAttributeClippingByDeviation()
    {
      return static_cast<NPC::AttributeClippingByDeviation*>(m_pElement.get());
    }
    __forceinline NPC::AttributeClippingByEchoNumber* asAttributeClippingByEchoNumber()
    {
      return static_cast<NPC::AttributeClippingByEchoNumber*>(m_pElement.get());
    }
    __forceinline NPC::AttributeClippingByCode* asAttributeClippingByCode()
    {
      return static_cast<NPC::AttributeClippingByCode*>(m_pElement.get());
    }
    __forceinline NPC::AttributeClippingBySourceId* asAttributeClippingBySourceId()
    {
      return static_cast<NPC::AttributeClippingBySourceId*>(m_pElement.get());
    }
    __forceinline NPC::AttributeClipping_Stack* asAttributeClippingStack()
    {
      return static_cast<NPC::AttributeClipping_Stack*>(m_pElement.get());
    }
    __forceinline NPC::ClippingStack* asClippingStack()
    {
      return static_cast<NPC::ClippingStack*>(m_pElement.get());
    }
  };

  struct ColoringImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    std::unique_ptr<NPC::Coloring> m_pColoring;

    ColoringImpl() {}
    ~ColoringImpl() {}

    ColoringImpl(const NPC::Coloring* _pColoring)
    {
      m_pColoring.reset(_pColoring->clone());
      if (m_pColoring == nullptr)
        ODA_FAIL_ONCE();
    }
    __forceinline bool operator==(const ColoringImpl& rhs)
    {
      ODA_ASSERT(m_pColoring != nullptr);
      ODA_ASSERT(rhs.m_pColoring != nullptr);
      return (*m_pColoring == *rhs.m_pColoring);
    }
    __forceinline bool operator!=(const ColoringImpl& rhs)
    {
      return !operator==(rhs);
    }

    __forceinline NPC::Coloring* asColoring()
    {
      return m_pColoring.get();
    }
    __forceinline NPC::ColoringWithColor* asColoringWithColor()
    {
      return static_cast<NPC::ColoringWithColor*>(m_pColoring.get());
    }
    __forceinline NPC::ColoringByElevation* asColoringByElevation()
    {
      return static_cast<NPC::ColoringByElevation*>(m_pColoring.get());
    }
    __forceinline NPC::ColoringByIntensity* asColoringByIntensity()
    {
      return static_cast<NPC::ColoringByIntensity*>(m_pColoring.get());
    }
    __forceinline NPC::ColoringByEchoNumber* asColoringByEchoNumber()
    {
      return static_cast<NPC::ColoringByEchoNumber*>(m_pColoring.get());
    }
    __forceinline NPC::ColoringByCode* asColoringByCode()
    {
      return static_cast<NPC::ColoringByCode*>(m_pColoring.get());
    }
    __forceinline NPC::ColoringWithDefaultColor* asColoringWithDefaultColor()
    {
      return static_cast<NPC::ColoringWithDefaultColor*>(m_pColoring.get());
    }
    __forceinline NPC::ColoringBySourceId* asColoringBySourceId()
    {
      return static_cast<NPC::ColoringBySourceId*>(m_pColoring.get());
    }
    __forceinline NPC::ColoringByDeviation* asColoringByDeviation()
    {
      return static_cast<NPC::ColoringByDeviation*>(m_pColoring.get());
    }
    __forceinline NPC::ColoringByNormals* asColoringByNormals()
    {
      return static_cast<NPC::ColoringByNormals*>(m_pColoring.get());
    }
    __forceinline NPC::ColoringByFeatures* asColoringByFeatures()
    {
      return static_cast<NPC::ColoringByFeatures*>(m_pColoring.get());
    }
    __forceinline NPC::ColoringByFeatureTypes* asColoringByFeatureTypes()
    {
      return static_cast<NPC::ColoringByFeatureTypes*>(m_pColoring.get());
    }

  private:
    ColoringImpl(const ColoringImpl& rhs)
    {}
    ColoringImpl& operator=(const ColoringImpl& rhs)
    {
      return *this;
    }
  };

  struct PointCloudInfoImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    InsertionPointCloudInfo m_Info;

    PointCloudInfoImpl(const InsertionPointCloudInfo& _Info)
    : m_Info(_Info)
    {}
    ~PointCloudInfoImpl()
    {}

  private:
    class _FakePointCloudinfo : public iPointCloudInfo
    {
      BITSET::BitSet<TDataScheme::TD_CLASS_TYPE> s1;
      BITSET::BitSet<TDataScheme::TD_ECHO_NUMBER_TYPE> s2;
      std::map<TDataScheme::TD_INTENSITY_TYPE, TTreeTraits::TT_COMPOSITE_INDEX_TYPE> m1;
      std::map<TDataScheme::TD_CLASS_TYPE, TTreeTraits::TT_COMPOSITE_INDEX_TYPE> m2;
      std::map<TDataScheme::TD_ECHO_NUMBER_TYPE, TTreeTraits::TT_COMPOSITE_INDEX_TYPE> m3;

    public:
      _FakePointCloudinfo() {}

      virtual const OdGeMatrix3d& getTransformation()                     const { return OdGeMatrix3d::kIdentity; }
      virtual const OdGeMatrix3d& getBackTransformation()                 const { return OdGeMatrix3d::kIdentity; }
      //Информация о границах облака
      virtual OdGeVector3d                                    getMainAxisX()                          const { return OdGeVector3d::kXAxis; }
      virtual OdGeVector3d                                    getMainAxisY()                          const { return OdGeVector3d::kYAxis; }
      virtual OdGeVector3d                                    getMainAxisZ()                          const { return OdGeVector3d::kZAxis; }
      virtual OdGePoint3d                                     getMinPoint()                           const { return OdGePoint3d::kOrigin; }
      virtual OdGePoint3d                                     getMaxPoint()                           const { return OdGePoint3d::kOrigin; }
      virtual OdGeExtents3d                                   getExtents()                            const { return OdGeExtents3d(); }

      //Признаки наличия конкретной метаинформации о точках
      virtual bool                                            isDataValid(TDataScheme::TD_DATA_TYPE)  const { return false; }
      virtual TDataScheme::TD_DATA_TYPE                       getDataScheme()                         const { return TDataScheme::TD_NO_DATA; }
      virtual TDataEncoder::TD_DATA_ENCODER_STATE_TYPE        getDataEncoderState()                   const { return TDataEncoder::TD_DEFAULT_DATA; }

      //Статистика
      virtual TTreeTraits::TT_COMPOSITE_INDEX_TYPE            getPointsCount()                        const { return 0; }
      virtual TTreeTraits::TT_NODE_INDEX_TYPE                 getNodesCount()                         const { return 0; }
      virtual TTreeTraits::TT_NODE_INDEX_TYPE                 getMaxNodeID()                          const { return 0; }
      virtual TTreeTraits::TT_LEVEL_TYPE                      getTreeDepth()                          const { return 0; }
      virtual TTreeTraits::TT_POINT_INDEX_TYPE                getDesignationPointsInNode()            const { return 0; }
      virtual void                                            calcTreeHistograms(std::map<TTreeTraits::TT_LEVEL_TYPE, TTreeTraits::TT_NODE_INDEX_TYPE>& levelsHistogram,
        std::map<TTreeTraits::TT_POINT_INDEX_TYPE, TTreeTraits::TT_NODE_INDEX_TYPE>& nodesHistogram) const {}
      //Множества
      virtual const BITSET::BitSet<TDataScheme::TD_CLASS_TYPE>& getUsedClasses()                      const { return s1; }
      virtual const BITSET::BitSet<TDataScheme::TD_ECHO_NUMBER_TYPE>& getUsedEchoNumber()             const { return s2; }
      //Гистограммы ассоциативных свойств
      virtual const std::map<TDataScheme::TD_INTENSITY_TYPE, TTreeTraits::TT_COMPOSITE_INDEX_TYPE>& getIntensityHistogram()  const { return m1; }
      virtual const std::map<TDataScheme::TD_CLASS_TYPE, TTreeTraits::TT_COMPOSITE_INDEX_TYPE>& getClassHistogram()      const { return m2; }
      virtual const std::map<TDataScheme::TD_ECHO_NUMBER_TYPE, TTreeTraits::TT_COMPOSITE_INDEX_TYPE>& getEchoNumberHistogram() const { return m3; }
      //Геометрические фичи
      virtual bool                                            isGeometricFeatureValid(TDataScheme::TD_GEOMETRIC_FEATURE_TYPE feature)
        const {
        return false;
      }
      virtual UINT                                            getGeometricFeaturesCount(TDataScheme::GeometricFeatureContext::FeatureType type
        = TDataScheme::GeometricFeatureContext::FeatureType::AnyType) const {
        return 0;
      }
      virtual TDataScheme::TD_GEOMETRIC_FEATURE_TYPE          getFirstGeometricFeature(TDataScheme::GeometricFeatureContext::FeatureType type
        = TDataScheme::GeometricFeatureContext::FeatureType::AnyType) const {
        return TDataScheme::NULL_FEATURE;
      }
      virtual TDataScheme::TD_GEOMETRIC_FEATURE_TYPE          getNextGeometricFeature(TDataScheme::TD_GEOMETRIC_FEATURE_TYPE feature)
        const {
        return TDataScheme::NULL_FEATURE;
      }
      virtual NPC::GeometricFeature                           getGeometricFeature(TDataScheme::TD_GEOMETRIC_FEATURE_TYPE feature)
        const {
        return NPC::GeometricFeature::NullFeature;
      }
      virtual CXStringW                                       getGeometricFeatureName(TDataScheme::TD_GEOMETRIC_FEATURE_TYPE feature)
        const {
        return CXStringW(L"");
      }


    protected:
      virtual Point3f                                         getLocalMinPoint()                      const { return Point3f::kOrigin; }
      virtual Point3f                                         getLocalMaxPoint()                      const { return Point3f::kOrigin; }
    };
    static const _FakePointCloudinfo _FakeInfo;
    PointCloudInfoImpl(const PointCloudInfoImpl& rhs)
    : m_Info((const iPointCloudInfo&)_FakeInfo, OdGeMatrix3d::kIdentity)
    {}
    PointCloudInfoImpl& operator=(const PointCloudInfoImpl& rhs)
    {
      return *this;
    }
  };

  struct GeometricFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::GeometricFeature m_Feature;

    GeometricFeatureImpl(const NPC::GeometricFeature& _Feature)
    : m_Feature(_Feature)
    {}
    ~GeometricFeatureImpl()
    {}

  private:
    GeometricFeatureImpl(const GeometricFeatureImpl& rhs)
    : m_Feature(&GeometricFeatureInternal::NullFeature)
    {}
    GeometricFeatureImpl& operator=(const GeometricFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct PlaneFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::PlaneFeature m_PlaneFeature;

    PlaneFeatureImpl(const NPC::PlaneFeature& _PlaneFeature)
      : m_PlaneFeature(_PlaneFeature)
    {}
    ~PlaneFeatureImpl()
    {}

  private:
    PlaneFeatureImpl(const PlaneFeatureImpl& rhs)
      : m_PlaneFeature(CPlaneFeatureObj::createNULL())
    {}
    PlaneFeatureImpl& operator=(const PlaneFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct Planes2IntersectionFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::Planes2IntersectionFeature m_Planes2IntersectionFeature;

    Planes2IntersectionFeatureImpl(const NPC::Planes2IntersectionFeature& _Planes2IntersectionFeature)
      : m_Planes2IntersectionFeature(_Planes2IntersectionFeature)
    {}
    ~Planes2IntersectionFeatureImpl()
    {}

  private:
    Planes2IntersectionFeatureImpl(const Planes2IntersectionFeatureImpl& rhs)
      : m_Planes2IntersectionFeature(CPlanes2IntersectionFeatureObj::createNULL())
    {}
    Planes2IntersectionFeatureImpl& operator=(const Planes2IntersectionFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct Planes3IntersectionFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::Planes3IntersectionFeature m_Planes3IntersectionFeature;

    Planes3IntersectionFeatureImpl(const NPC::Planes3IntersectionFeature& _Planes3IntersectionFeature)
      : m_Planes3IntersectionFeature(_Planes3IntersectionFeature)
    {}
    ~Planes3IntersectionFeatureImpl()
    {}

  private:
    Planes3IntersectionFeatureImpl(const Planes3IntersectionFeatureImpl& rhs)
      : m_Planes3IntersectionFeature(CPlanes3IntersectionFeatureObj::createNULL())
    {}
    Planes3IntersectionFeatureImpl& operator=(const Planes3IntersectionFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct CylinderFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::CylinderFeature m_CylinderFeature;

    CylinderFeatureImpl(const NPC::CylinderFeature& _CylinderFeature)
      : m_CylinderFeature(_CylinderFeature)
    {}
    ~CylinderFeatureImpl()
    {}

  private:
    CylinderFeatureImpl(const CylinderFeatureImpl& rhs)
      : m_CylinderFeature(CCylinderFeatureObj::createNULL())
    {}
    CylinderFeatureImpl& operator=(const CylinderFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct PipeFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::PipeFeature m_PipeFeature;

    PipeFeatureImpl(const NPC::PipeFeature& _PipeFeature)
      : m_PipeFeature(_PipeFeature)
    {}
    ~PipeFeatureImpl()
    {}

  private:
    PipeFeatureImpl(const PipeFeatureImpl& rhs)
      : m_PipeFeature(CPipeFeatureObj::createNULL())
    {}
    PipeFeatureImpl& operator=(const PipeFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct SphereFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::SphereFeature m_SphereFeature;

    SphereFeatureImpl(const NPC::SphereFeature& _SphereFeature)
      : m_SphereFeature(_SphereFeature)
    {}
    ~SphereFeatureImpl()
    {}

  private:
    SphereFeatureImpl(const SphereFeatureImpl& rhs)
      : m_SphereFeature(CSphereFeatureObj::createNULL())
    {}
    SphereFeatureImpl& operator=(const SphereFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct AggregateGeometricFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::AggregateGeometricFeature m_AggregateGeometricFeature;

    AggregateGeometricFeatureImpl(const NPC::AggregateGeometricFeature& _AggregateGeometricFeature)
      : m_AggregateGeometricFeature(_AggregateGeometricFeature)
    {}
    ~AggregateGeometricFeatureImpl()
    {}

  private:
    AggregateGeometricFeatureImpl(const AggregateGeometricFeatureImpl& rhs)
      : m_AggregateGeometricFeature(CAggregateGeometricFeatureObj::createNULL())
    {}
    AggregateGeometricFeatureImpl& operator=(const AggregateGeometricFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct ConstructionGeometricFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::ConstructionGeometricFeature m_ConstructionGeometricFeature;

    ConstructionGeometricFeatureImpl(const NPC::ConstructionGeometricFeature& _ConstructionGeometricFeature)
      : m_ConstructionGeometricFeature(_ConstructionGeometricFeature)
    {}
    ~ConstructionGeometricFeatureImpl()
    {}

  private:
    ConstructionGeometricFeatureImpl(const ConstructionGeometricFeatureImpl& rhs)
      : m_ConstructionGeometricFeature(CConstructionGeometricFeatureObj::createNULL())
    {}
    ConstructionGeometricFeatureImpl& operator=(const ConstructionGeometricFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct TeeFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::TeeFeature m_TeeFeature;

    TeeFeatureImpl(const NPC::TeeFeature& _TeeFeature)
      : m_TeeFeature(_TeeFeature)
    {
    }
    ~TeeFeatureImpl()
    {
    }

  private:
    TeeFeatureImpl(const TeeFeatureImpl& rhs)
      : m_TeeFeature(CTeeFeatureObj::createNULL())
    {
    }
    TeeFeatureImpl& operator=(const TeeFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct ConeFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::ConeFeature m_ConeFeature;

    ConeFeatureImpl(const NPC::ConeFeature& _ConeFeature)
      : m_ConeFeature(_ConeFeature)
    {
    }
    ~ConeFeatureImpl()
    {
    }

  private:
    ConeFeatureImpl(const ConeFeatureImpl& rhs)
      : m_ConeFeature(CConeFeatureObj::createNULL())
    {
    }
    ConeFeatureImpl& operator=(const ConeFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct TorusFeatureImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::TorusFeature m_TorusFeature;

    TorusFeatureImpl(const NPC::TorusFeature& _TorusFeature)
      : m_TorusFeature(_TorusFeature)
    {
    }
    ~TorusFeatureImpl()
    {
    }

  private:
    TorusFeatureImpl(const TorusFeatureImpl& rhs)
      : m_TorusFeature(CTorusFeatureObj::createNULL())
    {
    }
    TorusFeatureImpl& operator=(const TorusFeatureImpl& rhs)
    {
      return *this;
    }
  };

  struct VisualizationParamsImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::VisualizationParamsWrapper m_Params;

    VisualizationParamsImpl(const NPC::VisualizationParamsWrapper& _Params)
    {
      m_Params = _Params;
    }
    ~VisualizationParamsImpl()
    {}

  private:
    VisualizationParamsImpl& operator=(const VisualizationParamsImpl& rhs)
    {
      return *this;
    }
    VisualizationParamsImpl(const VisualizationParamsImpl& rhs)
    {}
  };

  struct PointCloudVertexIteratorImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::PointCloudVertexIterator m_Iter;

    PointCloudVertexIteratorImpl(const NPC::PointCloudVertexIterator& _Iter)
    : m_Iter(_Iter)
    {}
    ~PointCloudVertexIteratorImpl()
    {}

  private:
    class _FakePointCloudVertexIterator : public NPC::PointCloudVertexIterator
    {
    public:
      const OdGeMatrix3d& getTransform() const { return m_mTransform; }
      const OdGeMatrix3d& getBackTransform() const { return m_mBackTransform; }
    };
    static const _FakePointCloudVertexIterator _FakeIter;
    PointCloudVertexIteratorImpl(const PointCloudVertexIteratorImpl& rhs)
    : m_Iter(_FakeIter)
    {}
    PointCloudVertexIteratorImpl& operator=(const PointCloudVertexIteratorImpl& rhs)
    {
      return *this;
    }
  };

  struct RandomPointCloudVertexIteratorImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    NPC::RandomPointCloudVertexIterator m_Iter;

    RandomPointCloudVertexIteratorImpl(const NPC::RandomPointCloudVertexIterator& _Iter) 
    : m_Iter(_Iter)
    {}
    ~RandomPointCloudVertexIteratorImpl()
    {}

  private:
    class _FakeRandomPointCloudVertexIterator : public NPC::RandomPointCloudVertexIterator
    {
    public:
      const OdGeMatrix3d& getTransform() const { return m_mTransform; }
      const OdGeMatrix3d& getBackTransform() const { return m_mBackTransform; }
    };
    static const _FakeRandomPointCloudVertexIterator _FakeIter;
    RandomPointCloudVertexIteratorImpl(const RandomPointCloudVertexIteratorImpl& rhs)
    : m_Iter(_FakeIter)
    {}
    RandomPointCloudVertexIteratorImpl& operator=(const RandomPointCloudVertexIteratorImpl& rhs)
    {
      return *this;
    }
  };

  struct PointCloudInsertionImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    hostDbPointCloudInsertionPtr m_pInsertion;

    PointCloudInsertionImpl(hostDbPointCloudInsertion* pInsertion)
    : m_pInsertion(pInsertion)
    {}
    ~PointCloudInsertionImpl()
    {}

  private:
    PointCloudInsertionImpl(const PointCloudInsertionImpl& rhs)
    {}
    PointCloudInsertionImpl& operator=(const PointCloudInsertionImpl& rhs)
    {
      return *this;
    }
  };

  struct PointCloudDefinitionImpl : public OdRxObjectImpl<Impl>
  {
    ODRX_HEAP_OPERATORS();

    hostDbPointCloudDefinitionPtr m_pDefinition;

    PointCloudDefinitionImpl(hostDbPointCloudDefinition* pDefinition)
    : m_pDefinition(pDefinition)
    {}
    ~PointCloudDefinitionImpl()
    {}

  private:
    PointCloudDefinitionImpl(const PointCloudDefinitionImpl& rhs)
    {}
    PointCloudDefinitionImpl& operator=(const PointCloudDefinitionImpl& rhs)
    {
      return *this;
    }
  };

  //Creators
  class Clipping;
  class Coloring;
  class PointCloudInfo;
  class GeometricFeature;
  class VisualizationParams;
  class PointCloudInsertion;
  class PointCloudDefinition;
  class PointCloudVertexIterator;
  class RandomPointCloudVertexIterator;
  struct PointCloudBridgeImpl
  {
    static RandomPointCloudVertexIterator create(const NPC::RandomPointCloudVertexIterator&);
    static PointCloudVertexIterator create(const NPC::PointCloudVertexIterator&);
    static VisualizationParams create(const NPC::VisualizationParamsWrapper&);
    static PointCloudDefinition create(hostDbPointCloudDefinition*);
    static PointCloudInsertion create(hostDbPointCloudInsertion*);
    static PointCloudInfo create(const InsertionPointCloudInfo&);
    static GeometricFeature create(const NPC::GeometricFeature&);
    static Clipping create(const NPC::Clipping& _Clipping);
    static Coloring create(const NPC::Coloring* _Coloring);
  };
}

#endif
