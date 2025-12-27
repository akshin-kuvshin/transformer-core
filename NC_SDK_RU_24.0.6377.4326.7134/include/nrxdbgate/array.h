#ifndef __OPENDWG_ARRAY_H__
#define __OPENDWG_ARRAY_H__
#include "hostArray.h"
#include "nrxdbgate_impexp.h"
#define NcArrayMemCopyReallocator     HostMemoryAllocator
#define NcArrayObjectCopyReallocator  HostObjectsAllocator

class NcDbDimData;
class NcDbGripData;
class NcDbEvalVariant;
class NcDbDynBlockReferenceProperty;
class NcDbNurbSurface;
class NcDbField;
template<typename T, bool>
struct NcArrayItemCopierSelector;

template<typename T>
struct NcArrayItemCopierSelector<T, false>
{
	typedef NcArrayObjectCopyReallocator<T> allocator;
};
template<typename T>
struct NcArrayItemCopierSelector<T, true>
{
	typedef NcArrayMemCopyReallocator<T> allocator;
};
class NcGePoint2d;
class NcGePoint3d;
class NcGeVector2d;
class NcGeVector3d;
template < class T, class R = typename NcArrayItemCopierSelector<T, std::is_same<T, NcGePoint2d>::value ||
	std::is_same<T, NcGePoint3d>::value ||
	std::is_same<T, NcGeVector2d>::value ||
	std::is_same<T, NcGeVector3d>::value >::allocator > class NcArray : public HostArray< T, R >
{
public:
	using parent_class = typename HostArray< T, R >;
	inline NcArray(int initPhysicalLength = 0, int initGrowLength = 8) : parent_class(initPhysicalLength,
	                                                                                 initGrowLength) {}
	inline NcArray(const NcArray< T, R >& source) : parent_class(source) {}

public:
	// Copy operator.
	inline NcArray< T, R >& operator=(const NcArray< T, R >& source)
	{
		parent_class::operator=(source);
		return *this;
	}
	inline bool operator==(const NcArray< T, R >& match) const
	{
		return parent_class::operator==(match);
	}

	// Indexing into the array.
public:
	inline T& operator[](int index)
	{
		return parent_class::operator[](index);
	}
	inline const T& operator[](int index) const
	{
		return parent_class::operator[](index);
	}

	// More access to array-elements.
public:
	inline const T& at(int index) const
	{
		return parent_class::at(index);
	}
	inline T& at(int index)
	{
		return parent_class::at(index);
	}

	inline NcArray< T, R >& setAt(int index, const T& value)
	{
		parent_class::setAt(index, value);
		return *this;
	}
	inline NcArray< T, R >& setAll(const T& value)
	{
		parent_class::setAll(value);
		return *this;
	}

	inline T& first()
	{
		return parent_class::first();
	}
	inline const T& first() const
	{
		return parent_class::first();
	}

	inline T& last()
	{
		return parent_class::last();
	}
	inline const T& last() const
	{
		return parent_class::last();
	}

	// Adding array-elements.
public:
	inline int append(const T& value)
	{
		return parent_class::append(value);
	}

	inline NcArray< T, R >& append(const NcArray< T, R >& appendix)
	{
		parent_class::append(appendix);
		return *this;
	}

	inline NcArray< T, R >& insertAt(int index, const T& value)
	{
		parent_class::insertAt(index, value);
		return *this;
	}

	// Removing array-elements.
public:
	inline NcArray< T, R >& removeAt(int index)
	{
		parent_class::removeAt(index);
		return *this;
	}
	inline bool remove(const T& value, int start = 0)
	{
		return parent_class::remove(value, start);
	}
	inline NcArray< T, R >& removeFirst()
	{
		parent_class::removeFirst();
		return *this;
	}
	inline NcArray< T, R >& removeLast()
	{
		if (!parent_class::isEmpty())
			parent_class::removeLast();
		return *this;
	}
	inline NcArray< T, R >& removeAll()
	{
		parent_class::clear();
		return *this;
	}
	inline NcArray< T, R >& removeSubArray(int begin, int end)
	{
		parent_class::removeSubArray(begin, end);
		return *this;
	}

	// Query about array-elements.
public:
	inline bool contains(const T& value, int start = 0) const
	{
		return parent_class::contains(value, start);
	}
	inline bool find(const T& value, int& foundAt, int start = 0) const
	{
		return parent_class::find(value, (size_type&)foundAt, start);
	}
	inline int find(const T& value) const
	{
		size_type index;
		if (parent_class::find(value, index))
			return index;
		else
			return -1;
	}
	inline int findFrom(const T& value, int start) const
	{
		size_type index;
		if (parent_class::find(value, index, start))
			return index;
		else
			return -1;
	}

	// Array length.
public:
	inline int length() const
	{
		return parent_class::length();
	}
	inline bool isEmpty() const
	{
		return parent_class::isEmpty();
	}
	inline int logicalLength() const
	{
		return parent_class::logicalLength();
	}
	inline NcArray< T, R >& setLogicalLength(int length)
	{
		parent_class::setLogicalLength(length);
		return *this;
	}
	inline int physicalLength() const
	{
		return parent_class::physicalLength();
	}
	inline NcArray< T, R >& setPhysicalLength(int length)
	{
		parent_class::setPhysicalLength(length);
		return *this;
	}

	// Automatic resizing.
public:
	inline int growLength() const
	{
		return parent_class::growLength();
	}
	inline NcArray< T, R >& setGrowLength(int length)
	{
		parent_class::setGrowLength(length);
		return *this;
	}

	// Utility.
public:
	inline NcArray< T, R >& reverse()
	{
		parent_class::reverse();
		return *this;
	}
	inline NcArray< T, R >& swap(int i1, int i2)
	{
		parent_class::swap(i1, i2);
		return *this;
	}

	// Treat as simple array of T.
public:
	using HostArray<T, R>::asArrayPtr;
	inline const T* asArrayPtr() const
	{
		return parent_class::asArrayPtr();
	}
	inline T* asArrayPtr()
	{
		return parent_class::asArrayPtr();
	}
};

typedef NcArray< double, HostMemoryAllocator< double > >                      NcGeDoubleArray;
template class NRXDBGATE_EXPORT NcArray< double, HostMemoryAllocator< double > >;
typedef NcArray< int, HostMemoryAllocator< int > >                            NcGeIntArray;
template class NRXDBGATE_EXPORT NcArray< int, HostMemoryAllocator< int > >;
typedef NcArray< NRX::IntPtr, HostMemoryAllocator< NRX::IntPtr > >  NcGeIntPtrArray;
template class NRXDBGATE_EXPORT NcArray< NRX::IntPtr, HostMemoryAllocator< NRX::IntPtr > >;

typedef NcArray< void*, HostMemoryAllocator< void* > >                        NcGeVoidPointerArray;
template class NRXDBGATE_EXPORT NcArray< void*, HostMemoryAllocator< void* > >;

typedef NcArray< NcDbDimData >                                              NcDbDimDataArray;
typedef NcArray< NcDbDimData*, HostMemoryAllocator< NcDbDimData* > >          NcDbDimDataPtrArray;
template class NRXDBGATE_EXPORT NcArray<NcDbDimData*, HostMemoryAllocator< NcDbDimData* > >;

typedef NcArray< NcDbGripData*, HostMemoryAllocator< NcDbGripData* > >        NcDbGripDataPtrArray;
template class NRXDBGATE_EXPORT NcArray<NcDbGripData*, HostMemoryAllocator< NcDbGripData* >>;
typedef NcArray< NcDbGripData, HostMemoryAllocator< NcDbGripData > >          NcDbGripDataArray;

typedef NcArray< NcDbEvalVariant,
                 NcArrayObjectCopyReallocator< NcDbEvalVariant > >                NcDbEvalVariantArray;
template class NRXDBGATE_EXPORT NcArray<NcDbEvalVariant, HostMemoryAllocator< NcDbEvalVariant >>;
typedef NcArray< NcDbDynBlockReferenceProperty,
                 NcArrayObjectCopyReallocator< NcDbDynBlockReferenceProperty > >  NcDbDynBlockReferencePropertyArray;

typedef NcArray < NcDbField, HostMemoryAllocator< NcDbField > >  NcDbFieldArray;

typedef NcGeIntArray           NcDbIntArray;
typedef NcGeIntPtrArray        NcDbIntPtrArray;
typedef NcGeVoidPointerArray   NcDbVoidPtrArray;

typedef NcArray<NcDbNurbSurface*> NcDbNurbSurfaceArray;
template class NRXDBGATE_EXPORT NcArray<NcDbNurbSurface*>;

#endif // __OPENDWG_ARRAY_H__
