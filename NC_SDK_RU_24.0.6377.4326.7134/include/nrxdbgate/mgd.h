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

#ifndef _NANOTHUNK_MGD_H__
#define _NANOTHUNK_MGD_H__
#include <vcclr.h>

#define NC_GCHANDLE_TO_VOIDPTR(x) ((GCHandle::operator System::IntPtr(x)).ToPointer())
#define NC_VOIDPTR_TO_GCHANDLE(x) (GCHandle::operator GCHandle(System::IntPtr(x)))
#define NC_NULLPTR nullptr
#define NC_GCNEW gcnew
#define NC_WCHAR_PINNED_GCPTR pin_ptr<const wchar_t>

#ifdef NRXGATEMGD
#define NRXGATEMGD_EXPORT __declspec(dllexport)
#else
#define NRXGATEMGD_EXPORT __declspec(dllimport)
#pragma comment (lib, "NrxGateMgd.lib")
#endif //NRXGATEMGD

namespace Teigha
{
	namespace Runtime
	{
		ref class DisposableWrapper;
	}
}

typedef Teigha::Runtime::DisposableWrapper^ DisposableWrapper_GcPtr;
typedef System::String^ String_GcPtr;
class NcMgObjectFactoryBaseImpl;
class NcMgObjectFactoryBase
{
	NcMgObjectFactoryBaseImpl* impl_;
public:
	NRXGATEMGD_EXPORT NcMgObjectFactoryBase();
	NRXGATEMGD_EXPORT virtual ~NcMgObjectFactoryBase();
	NRXGATEMGD_EXPORT NcMgObjectFactoryBaseImpl* impl();
	virtual DisposableWrapper_GcPtr createRCW(OdRxObject* unmanagedPointer, bool autoDelete) = 0;
};
NRXGATEMGD_EXPORT void addPEMgObject(NcRxClass* rxClass, NcMgObjectFactoryBase* pointer);
NRXGATEMGD_EXPORT void delPEMgObject(NcRxClass* rxClass);
template <typename RCW, typename ImpObj>
class NcMgObjectFactory : public NcMgObjectFactoryBase
{
public:
	virtual DisposableWrapper_GcPtr createRCW(OdRxObject* unmanagedPointer, bool autoDelete) override final
	{
		return gcnew RCW(System::IntPtr(unmanagedPointer), autoDelete);
	}
	NcMgObjectFactory()
	{
		addPEMgObject(ImpObj::desc(), this);
	}
	~NcMgObjectFactory()
	{
		delPEMgObject(ImpObj::desc());
	}
};

class StringToWchar
{
	typedef System::Runtime::InteropServices::GCHandle GCHandle;

	const wchar_t* m_ptr;
	void* m_pinner;

public:

	StringToWchar(String_GcPtr str)
	{
		m_pinner = NC_GCHANDLE_TO_VOIDPTR(GCHandle::Alloc(str, System::Runtime::InteropServices::GCHandleType::Pinned));
		NC_WCHAR_PINNED_GCPTR tmp = PtrToStringChars(str);
		m_ptr = tmp;
	}

	~StringToWchar()
	{
		GCHandle g = NC_VOIDPTR_TO_GCHANDLE(m_pinner);
		g.Free();
		m_pinner = 0;
	}

	operator const wchar_t*()
	{
		return m_ptr;
	}
};

inline String_GcPtr WcharToString(const wchar_t* value)
{
	return NC_GCNEW System::String(value);
}

#undef NC_GCHANDLE_TO_VOIDPTR
#undef NC_VOIDPTR_TO_GCHANDLE
#undef NC_NULLPTR
#undef NC_GCNEW

#define StringToCIF StringToWchar
#define CIFToString WcharToString

#ifndef NRXGATEMGD

#define GETVECTOR3D(vec3d)  (*reinterpret_cast<NcGeVector3d*>(&(vec3d)))
#define GETVECTOR2D(vec2d)  (*reinterpret_cast<NcGeVector2d*>(&(vec2d)))
#define GETMATRIX3D(mat3d)  (*reinterpret_cast<NcGeMatrix3d*>(&(mat3d)))
#define GETMATRIX2D(mat2d)  (*reinterpret_cast<NcGeMatrix2d*>(&(mat2d)))
#define GETPOINT3D(point3d) (*reinterpret_cast<NcGePoint3d*>(&(point3d)))
#define GETPOINT2D(point2d) (*reinterpret_cast<NcGePoint2d*>(&(point2d)))
#define GETSCALE2D(scale2d) (*reinterpret_cast<NcGeScale2d*>(&(scale2d)))
#define GETSCALE3D(scale3d) (*reinterpret_cast<NcGeScale3d*>(&(scale3d)))
#define GETTOL(tol)         (*reinterpret_cast<NcGeTol*>(&(tol)))
#define GETOBJECTID(id)     (*reinterpret_cast<NcDbObjectId*>(&(id)))
#define GETEXTENTS3D(ext3d) (*reinterpret_cast<NcDbExtents*>(&(ext3d)))
#define GETSUBENTITYID(subentityId) (*reinterpret_cast<NcDbSubentId*>(&(subentityId)))

inline Teigha::Geometry::Vector3d ToVector3d(const NcGeVector3d& pt)
{
	Teigha::Geometry::Vector3d ret;
	GETVECTOR3D(ret) = pt;
	return ret;
}

inline Teigha::Geometry::Vector2d ToVector2d(const NcGeVector2d& pt)
{
	Teigha::Geometry::Vector2d ret;
	GETVECTOR2D(ret) = pt;
	return ret;
}

inline Teigha::Geometry::Matrix3d ToMatrix3d(const NcGeMatrix3d& pt)
{
	Teigha::Geometry::Matrix3d ret;
	GETMATRIX3D(ret) = pt;
	return ret;
}

inline Teigha::Geometry::Matrix2d ToMatrix2d(const NcGeMatrix2d& pt)
{
	Teigha::Geometry::Matrix2d ret;
	GETMATRIX2D(ret) = pt;
	return ret;
}

inline Teigha::Geometry::Point3d ToPoint3d(const NcGePoint3d& pt)
{
	Teigha::Geometry::Point3d ret;
	GETPOINT3D(ret) = pt;
	return ret;
}

inline Teigha::Geometry::Point2d ToPoint2d(const NcGePoint2d& pt)
{
	Teigha::Geometry::Point2d ret;
	GETPOINT2D(ret) = pt;
	return ret;
}

inline Teigha::Geometry::Scale2d ToScale2d(const NcGeScale2d& pt)
{
	Teigha::Geometry::Scale2d ret;
	GETSCALE2D(ret) = pt;
	return ret;
}

inline Teigha::Geometry::Scale3d ToScale3d(const NcGeScale3d& pt)
{
	Teigha::Geometry::Scale3d ret;
	GETSCALE3D(ret) = pt;
	return ret;
}

inline Teigha::Geometry::Tolerance ToTolerance(const NcGeTol& pt)
{
	Teigha::Geometry::Tolerance ret;
	GETTOL(ret) = pt;
	return ret;
}

inline Teigha::DatabaseServices::ObjectId ToObjectId(const NcDbObjectId& pt)
{
	Teigha::DatabaseServices::ObjectId ret;
	GETOBJECTID(ret) = pt;
	return ret;
}

inline Teigha::DatabaseServices::Extents3d ToExtents3d(const NcDbExtents& pt)
{
	Teigha::DatabaseServices::Extents3d ret;
	GETEXTENTS3D(ret) = pt;
	return ret;
}

#endif // #ifndef NRXGATEMGD

#endif // _NANOTHUNK_MGD_H__