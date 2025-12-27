#ifndef __OPENDWG_HOSTARRAY_H__
#define __OPENDWG_HOSTARRAY_H__
#include <utility>
#include "typesDb.h"
#include <iterator>
#include <type_traits>
#include "nrxdbgate_impexp.h"
#include <stdexcept>

// RefCounter
#if defined(_MSC_VER)
#include <windows.h>
#endif
#if defined(_MSC_VER) && defined(_M_IX86) && (_M_IX86 >= 400) && !defined(_WIN32_WCE)
// Intel486 platform with Microsoft compiler
#pragma warning(push)
#pragma warning(disable:4035)
#pragma warning(disable:4793)
inline int HostInternlockedExchange(volatile int* dest, int val)
{
  __asm
  {
    mov edx, dest
    mov eax, val
    lock xchg[edx], eax
  }
}
inline int HostInternlockedExchangeAdd(volatile int* dest, int incr)
{
  __asm
  {
    mov edx, dest
    mov eax, incr
    lock xadd[edx], eax
  }
}

inline int HostInternlockedCompareExchange(volatile int* dest, int x, int compare)
{
  __asm
  {
    mov eax, compare
    mov ecx, x
    mov edx, dest
    lock cmpxchg[edx], ecx
  }
}

#pragma warning(pop)
#elif (defined(_WIN32) || defined(_WIN64)) && /*!defined(_WIN32_WCE) &&*/ /*!defined(_WINRT) && */!defined(ODA_WINDOWS_GCC)
// Windows platform with generic compiler - use interlocked functions from Win32 API
#define HostInternlockedExchange(dest, val) InterlockedExchange((LONG*)(dest), val)
#define HostInternlockedExchangeAdd(dest, incr) InterlockedExchangeAdd((LONG*)(dest), incr)
#define HostInternlockedCompareExchange(dest, x, compare) InterlockedCompareExchange((LONG*)(dest), x, compare)
#define HostInternlockedIncrement(dest) InterlockedIncrement((LONG*)(dest))
#define HostInternlockedDecrement(dest) InterlockedDecrement((LONG*)(dest))
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)) && !defined(ANDROID) && !defined(_APPLE_)
// Intel platform with GCC compiler
inline int HostInternlockedExchange(volatile int* dest, int val)
{
  int ret;
  __asm__ __volatile__(
    "lock; xchgl %0, (%1)"
    : "=r" (ret)
    : "r" (dest), "0" (val)
    : "memory");
  return ret;
}
inline int HostInternlockedCompareExchange(int volatile* dest, int xchg, int compare)
{
  int ret;
  __asm__ __volatile__("lock; cmpxchgl %2,(%1)"
    : "=a" (ret) : "r" (dest), "r" (xchg), "0" (compare) : "memory");
  return ret;
}
#elif defined(__GNUC__) && defined(__POWERPC__)
// Macintosh PowerPC platform with GCC compiler
inline int HostInternlockedExchange(volatile int* dest, int val)
{
  // Assembler code is taken from Wine 0.9.4 sources
  // See http://cvs.winehq.org/cvsweb/wine/libs/port/interlocked.c?rev=1.7&content-type=text/x-cvsweb-markup
  int ret = 0;
  __asm__ __volatile__(
    "0:  lwarx %0, 0, %1\n"
    "    stwcx. %2, 0, %1\n"
    "    bne- 0b\n"
    "    isync\n"
    : "=&r"(ret)
    : "r"(dest), "r"(val)
    : "cr0", "memory", "r0");
  return ret;
}
inline int HostInternlockedExchangeAdd(volatile int* dest, int incr)
{
  // Assembler code is taken from Wine 0.9.4 sources
  // See http://cvs.winehq.org/cvsweb/wine/libs/port/interlocked.c?rev=1.7&content-type=text/x-cvsweb-markup
  int ret = 0;
  int zero = 0;
  __asm__ __volatile__(
    "0:  lwarx %0, %3, %1\n"
    "    add %0, %2, %0\n"
    "    stwcx. %0, %3, %1\n"
    "    bne- 0b\n"
    "    isync\n"
    : "=&r" (ret)
    : "r"(dest), "r"(incr), "r"(zero)
    : "cr0", "memory", "r0");
  return ret - incr;
}

inline int HostInternlockedCompareExchange(volatile int* dest, int xchg, int compare)
{
  int ret = 0;
  int scratch;
  __asm__ __volatile__(
    "0:    lwarx %0,0,%2\n"
    "      xor. %1,%4,%0\n"
    "      bne 1f\n"
    "      stwcx. %3,0,%2\n"
    "      bne- 0b\n"
    "      isync\n"
    "1:    "
    : "=&r"(ret), "=&r"(scratch)
    : "r"(dest), "r"(xchg), "r"(compare)
    : "cr0", "memory", "r0");
  return ret;
}
// Intel platform with GCC compiler
inline int HostInterlockedExchangeAdd(volatile int* dest, int incr)
{
  int ret;
  __asm__ __volatile__(
    "lock; xaddl %0, (%1)"
    : "=r" (ret)
    : "r" (dest), "0" (incr)
    : "memory");
  return ret;
}
inline int HostInterlockedIncrement(volatile int* dest)
{
  return HostInterlockedExchangeAdd(dest, 1) + 1;
}
inline int HostInterlockedDecrement(volatile int* dest)
{
  return HostInterlockedExchangeAdd(dest, -1) - 1;
}
#elif defined(__APPLE__)
// iOS or Mac platform
#include <libkern/OSAtomic.h>
inline int HostInternlockedExchange(volatile int* dest, int val)
{
  int oldValue = *dest;
  while (!OSAtomicCompareAndSwapIntBarrier(oldValue, val, dest))
    oldValue = *dest;
  return oldValue;
}
inline int HostInternlockedExchangeAdd(volatile int* dest, int incr)
{
  return OSAtomicAdd32Barrier(incr, dest) - incr;
}
inline int HostInternlockedCompareExchange(volatile int* dest, int xchg, int compare)
{
  // This is not an exact equivalent of InterlockedCompareExchange but it is enough for atomic arithmetics
  return OSAtomicCompareAndSwapIntBarrier(compare, xchg, dest) ? compare : xchg;
}
#elif defined(ANDROID) //&& defined(ANDROID_GOOGLE)

inline int HostInternlockedExchange(volatile int* dest, int val)
{
  int oldVal = *dest;
  __sync_val_compare_and_swap(dest, oldVal, val);
  return oldVal;
}
inline int HostInternlockedExchangeAdd(volatile int* dest, int incr)
{
  int oldVal = *dest;
  __sync_val_compare_and_swap(dest, oldVal, incr + oldVal);
  return oldVal;
}
inline int HostInternlockedCompareExchange(volatile int* dest, int xchg, int compare)
{
  bool bRes = __sync_bool_compare_and_swap(dest, compare, xchg);
  return bRes ? xchg : compare;
}

/**
  <group !!RECORDS_tkernel_apiref>
*/
#else
// here should go other platforms
// synchronization is disabled if no atomic functions are defined
#define TD_SINGLE_THREAD
#endif //architecture
struct HostRefCounter
{
  typedef int RefCounterType;
  volatile RefCounterType _ref_count;
  HostRefCounter& operator = (RefCounterType n) { _ref_count = 0; HostInternlockedExchange(&_ref_count, n); return *this; }
  operator RefCounterType () const { return HostInternlockedExchangeAdd(const_cast<RefCounterType*>(&_ref_count), 0); }
  RefCounterType operator ++ () { return HostInternlockedIncrement(&_ref_count); }
  RefCounterType operator -- () { return HostInternlockedDecrement(&_ref_count); }
  // 1 as default is not correct for all classes 
  // (see for example OdArrayBuffer, CAllocator)
  HostRefCounter() : _ref_count(-1) {} // undefined
  HostRefCounter(int n) : _ref_count(n) {}
};
struct HostVolatile
{
  typedef int VolatileType;
  volatile VolatileType _val;
  HostVolatile& operator = (VolatileType n) { _val = 0; HostInternlockedExchange(&_val, n); return *this; }
  operator VolatileType () const { return HostInternlockedExchangeAdd(const_cast<VolatileType*>(&_val), 0); }
  VolatileType operator|=(VolatileType n) { return HostInternlockedExchange(&_val, _val | n); }
  VolatileType operator&=(VolatileType n) { return HostInternlockedExchange(&_val, _val & n); }
  HostVolatile() : _val(0) {}
  HostVolatile(int n) : _val(n) {}
};

// Heap

NRXDBGATE_EXPORT void* ncrxAlloc(size_t nBytes);
NRXDBGATE_EXPORT void* ncrxRealloc(void* pMemBlock, size_t newSize, size_t oldSize);
NRXDBGATE_EXPORT void  ncrxFree(void* pMemBlock);
#define NCNEW_HANDLER()\
{\
  std::new_handler handler = std::get_new_handler ();\
  if (!handler)\
    throw std::bad_alloc();\
  handler();\
}
#define NCRX_HEAP_OPERATORS() \
void* operator new(size_t s)\
{\
  void* p = ::ncrxAlloc(s);\
  if ( !p ) NCNEW_HANDLER()\
  return p;\
}\
void operator delete(void* p) { ::ncrxFree(p); }\
void* operator new[](size_t s)\
{\
  void* p = ::ncrxAlloc(s);\
  if ( !p ) NCNEW_HANDLER()\
  return p;\
}\
void operator delete[](void* p) { ::ncrxFree(p); }\
void *operator new(size_t, void* p) { return p; }\
void operator delete( void*, void* ) {}\
void *operator new[](size_t, void* p) { return p; }\
void operator delete[]( void*, void* ) {}

// Array

template<class T>
struct host_is_trivially_copyable_pair
{
    static const bool value = false;
};

template <class First, class Second>
struct host_is_trivially_copyable_pair <std::pair<First, Second>>
{
    static const bool value = std::is_trivially_copyable<First>::value && std::is_trivially_copyable<Second>::value;
};
template <class T> class HostMemoryAllocator
{
public:
    typedef unsigned int size_type;

    static inline void copyAssignRangeDisjoint(
        T* pDestination,
        const T* pSource,
        size_type numElements)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        memcpy(pDestination, pSource, numElements * sizeof(T));
    }
    static inline void copyAssignRange(
        T* pDestination,
        const T* pSource,
        size_type numElements)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        memmove(pDestination, pSource, numElements * sizeof(T));
    }
    static inline void moveAssignRange(
        T* pDestination,
        T* pSource,
        size_type numElements)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        memmove(pDestination, pSource, numElements * sizeof(T));
    }
    static inline void defaultConstruct(
        T* pElement)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        *pElement = T();
    }
    static inline void copyConstruct(
        T* pElement,
        const T& value)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        memcpy(pElement, &value, sizeof(value));
    }
    static inline void moveConstruct(
        T* pElement,
        T&& value)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        memmove(pElement, &value, sizeof(value));
    }
    static inline void copyConstructFill(
        T* pDestination,
        size_type numElements,
        const T& value)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        while (numElements--)
        {
            memcpy(pDestination + numElements, &value, sizeof(value));
        }
    }
    static inline void copyConstructRange(
        T* pDestination,
        const T* pSource,
        size_type numElements)
    {
        copyAssignRangeDisjoint(pDestination, pSource, numElements);
    }
    static inline void moveConstructRange(
        T* pDestination,
        T* pSource,
        size_type numElements)
    {
        copyAssignRangeDisjoint(pDestination, pSource, numElements);
    }
    static inline void defaultConstructFill(
        T* pDestination,
        size_type numElements)
    {
        // DOES NOTHING
    }
    static inline void destroy(
        T* pObject)
    {
        // DOES NOTHING
    }
    static inline void destroyRange(
        T* objects,
        size_type numObjects)
    {
        // DOES NOTHING
    }
    static inline bool useRealloc()
    {
        return true;
    }
};

template <class T> class HostClrMemAllocator : public HostMemoryAllocator<T>
{
public:
    typedef unsigned int size_type;

    static inline void copyConstructFill(
        T* pDestination,
        size_type numElements,
        const T& value)
    {
        HostMemoryAllocator<T>::copyConstructFill(pDestination, numElements, value);
    }
    static inline void copyConstructRange(
        T* pDestination,
        const T* pSource,
        size_type numElements)
    {
        HostMemoryAllocator<T>::copyConstructRange(pDestination, pSource, numElements);
    }
    static inline void defaultConstructFill(
        T* pDestination,
        size_type numElements)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        memset(pDestination, 0, numElements * sizeof(T));
    }
};

template <class T> class HostObjectsAllocator
{
public:
    typedef unsigned int size_type;

    static inline void copyAssignRangeDisjoint(
        T* pDestination,
        const T* pSource,
        size_type numElements)
    {
        while (numElements--)
        {
            *pDestination = *pSource;
            pDestination++;
            pSource++;
        }
    }
    static inline void copyAssignRange(
        T* pDestination,
        const T* pSource,
        size_type numElements)
    {
        if (pDestination <= pSource || pDestination >= pSource + numElements)
        {
            copyAssignRangeDisjoint(pDestination, pSource, numElements);
        }
        else
        {
            while (numElements--)
            {
                pDestination[numElements] = pSource[numElements];
            }
        }
    }
    static inline void moveAssignRange(
        T* pDestination,
        T* pSource,
        size_type numElements)
    {
        if (pDestination <= pSource || pDestination >= pSource + numElements)
        {
            while (numElements--)
            {
                *pDestination = std::move(*pSource);
                pDestination++;
                pSource++;
            }
        }
        else
        {
            while (numElements--)
            {
                pDestination[numElements] = std::move(pSource[numElements]);
            }
        }
    }
    static inline void defaultConstruct(
        T* pElement)
    {
#ifdef new
#undef new
#endif
        ::new (pElement) T;
    }
    static inline void copyConstruct(
        T* pElement,
        const T& value)
    {
#ifdef new
#undef new
#endif
        ::new (pElement) T(value);
    }
    static inline void moveConstruct(
        T* pElement,
        T&& value)
    {
#ifdef new
#undef new
#endif
        ::new (pElement) T(std::move(value));
    }
    static inline void copyConstructFill(
        T* pDestination,
        size_type numElements,
        const T& value)
    {
        while (numElements--)
        {
            copyConstruct(pDestination + numElements, value);
        }
    }
    static inline void defaultConstructFill(
        T* pDestination,
        size_type numElements)
    {
        while (numElements--)
        {
            defaultConstruct(pDestination + numElements);
        }
    }
    static inline void copyConstructRange(
        T* pDestination,
        const T* pSource,
        size_type numElements)
    {
        while (numElements--)
        {
            copyConstruct(pDestination, *pSource);
            pDestination++;
            pSource++;
        }
    }
    static inline void moveConstructRange(
        T* pDestination,
        T* pSource,
        size_type numElements)
    {
        while (numElements--)
        {
            moveConstruct(pDestination, std::move(*pSource));
            pDestination++;
            pSource++;
        }
    }
    static inline void destroy(
        T* pObject)
    {
        pObject->~T();
        pObject = 0;
    }
    static inline void destroyRange(
        T* objects,
        size_type numObjects)
    {
        while (numObjects--)
        {
            destroy(objects + numObjects);
        }
    }
    static inline bool useRealloc()
    {
        return false;
    }
};
template <class T> class HostPlainObjectsAllocator : public HostObjectsAllocator<T>
{
public:
    typedef unsigned int size_type;

    static inline void copyAssignRangeDisjoint(
        T* pDestination,
        const T* pSource,
        size_type numElements)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        memcpy(pDestination, pSource, numElements * sizeof(T));
    }
    static inline void copyAssignRange(
        T* pDestination,
        const T* pSource,
        size_type numElements)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        memmove(pDestination, pSource, numElements * sizeof(T));
    }
    static inline void moveAssignRange(
        T* pDestination,
        T* pSource,
        size_type numElements)
    {
        //_ASSERT(std::is_trivially_copyable<T>::value || host_is_trivially_copyable_pair<T>::value);
        memmove(pDestination, pSource, numElements * sizeof(T));
    }
    static inline bool useRealloc()
    {
        return true;
    }
};
struct HostArrayBuffer
{
    typedef unsigned int size_type;

    mutable HostRefCounter m_nRefCounter;
    int               m_nGrowBy;
    size_type         m_nAllocated;
    size_type         m_nLength;

    NRXDBGATE_EXPORT static HostArrayBuffer g_empty_array_buffer;
};
template <class T, class A> class HostArray
{
public:
    using size_type = typename A::size_type;
    using iterator = T*;
    using const_iterator = const T*;
    using value_type = T;
    using const_reference = const T&;
    using reference = T&;
    using ConstForPtrT = typename std::conditional<std::is_pointer<T>::value,
        typename std::add_const<typename std::remove_pointer<T>::type>::type*, T>::type;
private:
    struct  Buffer : HostArrayBuffer
    {
        T* data() const { return (T*)(this + 1); }

        static Buffer* allocate(size_type nLength2Allocate, int nGrowBy)
        {
            NRX::UInt64 nBytes2Allocate = (NRX::UInt64)sizeof(Buffer) + nLength2Allocate * sizeof(T);
            _ASSERT(nBytes2Allocate > nLength2Allocate); // size_type overflow
            size_t nBytes2AllocateSize_t = (size_t)nBytes2Allocate;//size_t overflow on x32
            if (nBytes2Allocate > nLength2Allocate && (NRX::UInt64)nBytes2AllocateSize_t == nBytes2Allocate)
            {
                Buffer* pBuffer = (Buffer*)::ncrxAlloc(nBytes2AllocateSize_t);
                if (pBuffer)
                {
                    pBuffer->m_nRefCounter = 1;
                    pBuffer->m_nGrowBy = nGrowBy;
                    pBuffer->m_nAllocated = nLength2Allocate;
                    pBuffer->m_nLength = 0;
                    return pBuffer;
                }
            }
            throw std::bad_alloc();
            return nullptr;
        }
        static Buffer* _default()
        {
            return (Buffer*)&g_empty_array_buffer;
        }
        void release()
        {
            _ASSERT(m_nRefCounter);
            if ((--m_nRefCounter) == 0 && this != _default())
            {
                A::destroyRange(data(), m_nLength);
                ::ncrxFree(this);
            }
        }
        void addref() const { ++m_nRefCounter; }
    };
#if defined(_MSC_VER)
#pragma warning(disable : 4127) //  conditional expression is constant
#pragma warning(push)
#endif
    class reallocator
    {
        bool _may_use_realloc;
        Buffer* m_pBuffer;
    public:
        inline reallocator(bool may_use_realloc = false) : _may_use_realloc(may_use_realloc), m_pBuffer(NULL) {}
        inline void reallocate(HostArray* pArray, size_type nNewLen)
        {
            if (!pArray->referenced())
            {
                if (nNewLen > pArray->physicalLength())
                {
                    if (!_may_use_realloc)
                    {
                        if (m_pBuffer)
                            m_pBuffer->release();
                        {
                            static_assert(std::is_copy_constructible<T>::value, "Trying to copy buffer for non-copyable T");
                        }
                        m_pBuffer = pArray->buffer();
                        m_pBuffer->addref(); // save buffer to ensure copy from itself would work (e.g insertAt)
                    }
                    pArray->copy_buffer(nNewLen, _may_use_realloc);
                }
            }
            else
            {
                pArray->copy_buffer(nNewLen);
            }
        }
        inline ~reallocator()
        {
            if (m_pBuffer)
                m_pBuffer->release();
        }
    };
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
    friend class reallocator;
    const_iterator begin_const() const { return begin(); }
    iterator begin_non_const() { return begin(); }
    const_iterator end_const() { return end(); }
    iterator end_non_const() { return end(); }
    void copy_before_write(size_type len, bool may_use_realloc = false)
    {
        if (referenced())
            copy_buffer(len);
        else if (len > physicalLength())
            copy_buffer(len, may_use_realloc);
    }
    void copy_if_referenced() { if (referenced()) { copy_buffer(physicalLength()); } }
#if !defined(SWIG)
    template<typename U = T,
        typename std::enable_if<std::is_same<U, T>::value&& std::is_copy_constructible<U>::value, bool>::type = true>
    inline void copyConstructRangeChecked(T* dest, T* source, size_type len)
    {
        A::copyConstructRange(dest, source, len);
    }
    template<typename U = T,
        typename std::enable_if<std::is_same<U, T>::value && !std::is_copy_constructible<U>::value, bool>::type = true>
    inline void copyConstructRangeChecked(T* dest, T* source, size_type len)
    {
        if (len != 0)
        {
            static_assert(false, "Trying to copy buffer for non-copyable T");
            return;
         }
    }
#endif
    void copy_buffer(size_type len, bool may_use_realloc = false, bool force_size = false, bool releaseOldBufAfterCopy = true)
    {
        Buffer* pOldBuffer = buffer();
        int nGrowBy = pOldBuffer->m_nGrowBy;
        size_type len2 = len;
        if (!force_size)
        {
            if (nGrowBy > 0)
            {
                len2 += nGrowBy;
                len2 = ((len2 - 1) / nGrowBy) * nGrowBy;
            }
            else
            {
                len2 = pOldBuffer->m_nLength;
                len2 = len2 + -nGrowBy * len2 / 100;
                if (len2 < len)
                {
                    len2 = len;
                }
            }
        }
        if (may_use_realloc && A::useRealloc() && !empty())
        {
            Buffer* pNewBuffer = reinterpret_cast<Buffer*>(::ncrxRealloc(
                pOldBuffer, len2 * sizeof(T) + sizeof(Buffer), pOldBuffer->m_nAllocated * sizeof(T) + sizeof(Buffer)));
            if (!pNewBuffer)
            {
                throw std::bad_alloc();
                return;
            }
            pNewBuffer->m_nAllocated = len2;
            pNewBuffer->m_nLength = min(pNewBuffer->m_nLength, len);
            m_pData = pNewBuffer->data();
        }
        else
        {
            Buffer* pNewBuffer = Buffer::allocate(len2, nGrowBy);
            if (!pNewBuffer)
            {
                throw std::bad_alloc();
                return;
            }
            len = min(pOldBuffer->m_nLength, len);
            if (may_use_realloc)
                A::moveConstructRange(pNewBuffer->data(), pOldBuffer->data(), len);
            else
                copyConstructRangeChecked(pNewBuffer->data(), pOldBuffer->data(), len);
            pNewBuffer->m_nLength = len;
            m_pData = pNewBuffer->data();
            if (releaseOldBufAfterCopy)
                pOldBuffer->release();
        }
    }
    inline void assertValid(size_type index) const
    {
        if (!isValid(index))
        {
            _ASSERT("Invalid Execution.");
        }
    }
    static inline void rise_error(Nano::ErrorStatus e)
    {
        throw std::out_of_range("index is out of range");
    }
public:
    // STL-like interface

    iterator begin()
    {
        if (!empty())
        {
            copy_if_referenced();
            return data();
        }
        return 0;
    }
    const_iterator begin() const
    {
        if (!empty())
        {
            return data();
        }
        return 0;
    }
    iterator end()
    {
        if (!empty())
        {
            copy_if_referenced();
            return data() + length();
        }
        return 0;
    }
    const_iterator end() const
    {
        if (!empty())
        {
            return data() + length();
        }
        return 0;
    }
    std::reverse_iterator<iterator> rbegin()
    {
        return std::reverse_iterator<iterator>(end());
    }
    std::reverse_iterator<const_iterator> rbegin() const
    {
        return std::reverse_iterator<const_iterator>(end());
    }
    std::reverse_iterator<iterator> rend()
    {
        return std::reverse_iterator<iterator>(begin());
    }
    std::reverse_iterator<const_iterator> rend() const
    {
        return std::reverse_iterator<const_iterator>(begin());
    }
    void insert(
        iterator before,
        const_iterator first,
        const_iterator afterLast)
    {
        if (first >= begin_const() && first < end_const() && before < afterLast)
        {
            throw std::out_of_range("Inserted iterator range will become invalid while inserting.");
            return;
        }
        size_type len = length();
        size_type index = (size_type)(before - begin_const());
        if (index <= len && afterLast >= first)
        {
            if (afterLast > first)
            {
                size_type num2copy = (size_type)(afterLast - first);
                reallocator r(first < begin() || first >= end());
                r.reallocate(this, len + num2copy);
                A::defaultConstructFill(m_pData + len, num2copy);
                buffer()->m_nLength = len + num2copy;
                T* pDestination = m_pData + index;
                if (index != len)
                {
                    A::moveAssignRange(pDestination + num2copy, pDestination, len - index);
                }
                A::copyAssignRangeDisjoint(pDestination, first, (size_type)(afterLast - first));
            }
        }
        else
        {
            rise_error(Nano::eInvalidInput);
        }
    }
    void insertMove(
        iterator before,
        iterator first,
        iterator afterLast)
    {
        if (first >= begin_const() && first < end_const() && before < afterLast)
        {
            throw std::out_of_range("Inserted iterator range will become invalid while inserting.");
            return;
        }
        size_type len = length();
        size_type index = (size_type)(before - begin_const());
        if (index <= len && afterLast >= first)
        {
            if (afterLast > first)
            {
                size_type num2copy = (size_type)(afterLast - first);
                reallocator r(first < begin() || first >= end());
                r.reallocate(this, len + num2copy);
                A::defaultConstructFill(m_pData + len, num2copy);
                buffer()->m_nLength = len + num2copy;
                T* pDestination = m_pData + index;
                if (index != len)
                {
                    A::moveAssignRange(pDestination + num2copy, pDestination, len - index);
                }
                A::moveAssignRange(pDestination, first, (size_type)(afterLast - first));
            }
        }
        else
        {
            rise_error(Nano::eInvalidInput);
        }
    }
    void resize(
        size_type logicalLength,
        const T& value)
    {
        size_type len = length();
        int d = logicalLength - len;
        if (d > 0)
        {
            increaseLogicalLength(logicalLength, len, d, value);
        }
        else if (d < 0)
        {
            d = -d;
            if (!referenced())
            {
                A::destroyRange(m_pData + logicalLength, d);
            }
            else
            {
                copy_buffer(logicalLength);
            }
        }
        buffer()->m_nLength = logicalLength;
    }
    void resize(
        size_type logicalLength)
    {
        size_type len = length();
        int d = logicalLength - len;
        if (d > 0)
        {
            increaseLogicalLength(logicalLength, len, d);
        }
        else if (d < 0)
        {
            d = -d;
            if (!referenced())
            {
                A::destroyRange(m_pData + logicalLength, d);
            }
            else
            {
                copy_buffer(logicalLength);
            }
        }
        buffer()->m_nLength = logicalLength;
    }
    size_type size() const
    {
        return buffer()->m_nLength;
    }
    bool empty() const
    {
        return size() == 0;
    }
    size_type capacity() const
    {
        return buffer()->m_nAllocated;
    }
    void reserve(
        size_type reserveLength)
    {
        if (physicalLength() < reserveLength)
        {
            setPhysicalLength(reserveLength);
        }
    }
    void assign(
        const_iterator first,
        const_iterator afterLast)
    {
        if (first >= begin_const() && first < end_const())
        {
            throw std::out_of_range("Assignment of a subrange from self is not allowed.");
            return;
        }
        clear();
        if (afterLast < first)
        {
            rise_error(Nano::eInvalidInput);
        }
        if (afterLast > first)
        {
            size_type num2copy = (size_type)(afterLast - first);
            copy_buffer(num2copy, true);
            buffer()->m_nLength = num2copy;
            A::copyConstructRange(m_pData, first, (size_type)(afterLast - first));
        }
    }
    void assignMove(
        iterator first,
        iterator afterLast)
    {
        if (first >= begin_const() && first < end_const())
        {
            throw std::out_of_range("Assignment of a subrange from self is not allowed.");
            return;
        }
        clear();
        if (afterLast < first)
        {
            rise_error(Nano::eInvalidInput);
        }
        if (afterLast > first)
        {
            size_type num2move = (size_type)(afterLast - first);
            copy_buffer(num2move, true);
            buffer()->m_nLength = num2move;
            A::moveConstructRange(m_pData, first, (size_type)(afterLast - first));
        }
    }
    iterator erase(
        iterator first,
        iterator afterLast)
    {
        size_type i = (size_type)(first - begin_const());
        if (first != afterLast)
        {
            removeSubArray(i, (size_type)(afterLast - begin_const() - 1));
        }
        return begin_non_const() + i;
    }
    iterator erase(
        iterator where)
    {
        size_type i = (size_type)(where - begin_const());
        removeAt(i);
        return begin_non_const() + i;
    }
    void clear()
    {
        copy_if_referenced();
        size_type len = length();
        A::destroyRange(m_pData, len);
        buffer()->m_nLength -= len;
    }
    void push_back(
        const T& value)
    {
        size_type len = length();
        size_type newLen = len + 1;
        bool ref = referenced();

        if (ref || len == physicalLength())
        {
            T valueCopy(value);
            copy_buffer(newLen, !ref);
            A::moveConstruct(m_pData + len, std::move(valueCopy));
        }
        else
        {
            A::copyConstruct(m_pData + len, value);
        }
        buffer()->m_nLength = newLen;
    }
    void push_back(
        T&& value)
    {
        size_type len = length();
        size_type newLen = len + 1;
        bool ref = referenced();

        if (ref || len == physicalLength())
        {
            T valueMoved(std::move(value));
            copy_buffer(newLen, !ref);
            A::moveConstruct(m_pData + len, std::move(valueMoved));
        }
        else
        {
            A::moveConstruct(m_pData + len, std::move(value));
        }
        buffer()->m_nLength = newLen;
    }
    iterator insert(
        iterator before,
        size_type numElements,
        const T& value)
    {
        if (numElements == 0)
        {
            return before;
        }
        size_type len = length();
        size_type index = (size_type)(before - begin_const());
        T tmpval(value);
        reallocator r(true);
        r.reallocate(this, len + numElements);
        A::defaultConstructFill(m_pData + len, numElements);
        buffer()->m_nLength = len + numElements;
        T* pData = data();
        pData += index;
        if (index != len)
        {
            A::moveAssignRange(pData + numElements, pData, len - index);
        }
        while (numElements-- > 1)
        {
            pData[numElements] = tmpval;
        }
        pData[0] = std::move(tmpval);
        return begin_non_const() + index;
    }
    iterator insert(
        iterator before,
        const T& value = T())
    {
        size_type index = (size_type)(before - begin_const());
        insertAt(index, value);
        return (begin_non_const() + index);
    }
    iterator insert(
        iterator before,
        T&& value)
    {
        size_type index = (size_type)(before - begin_const());
        insertAtMove(index, value);
        return (begin_non_const() + index);
    }
    bool contains(
        const ConstForPtrT& value,
        size_type start = 0) const
    {
        size_type dummy;
        return find(value, dummy, start);
    }
    size_type length() const
    {
        return buffer()->m_nLength;
    }
    bool isEmpty() const
    {
        return length() == 0;
    }
    size_type logicalLength() const
    {
        return length();
    }
    size_type physicalLength() const
    {
        return buffer()->m_nAllocated;
    }
    int growLength() const
    {
        return buffer()->m_nGrowBy;
    }
    const T* asArrayPtr() const
    {
        return data();
    }
    const T* getPtr() const
    {
        return data();
    }
    T* asArrayPtr()
    {
        copy_if_referenced();
        return data();
    }
    const T& operator [](
        size_type index) const
    {
        assertValid(index);
        return m_pData[index];
    }
    T& operator [](
        size_type index)
    {
        assertValid(index);
        copy_if_referenced();
        return m_pData[index];
    }
    T& at(size_type arrayIndex)
    {
        assertValid(arrayIndex);
        copy_if_referenced();
        return *(data() + arrayIndex);
    }
    const T& at(size_type arrayIndex) const
    {
        assertValid(arrayIndex);
        return *(data() + arrayIndex);
    }
    HostArray& setAt(
        size_type arrayIndex,
        const T& value)
    {
        assertValid(arrayIndex);
        copy_if_referenced();
        m_pData[arrayIndex] = value;
        return *this;
    }
    const T& getAt(
        size_type arrayIndex) const
    {
        assertValid(arrayIndex);
        return *(data() + arrayIndex);
    }
    T& first()
    {
        return *begin();
    }
    const T& first() const
    {
        return *begin();
    }
    T& last()
    {
        return at(length() - 1);
    }
    const T& last() const
    {
        return at(length() - 1);
    }
    size_type append(
        const T& value)
    {
        push_back(value);
        return length() - 1;
    }
    size_type append(
        T&& value)
    {
        return appendMove(value);
    }
    HostArray& insertAtMove(
        size_type index,
        T& value)
    {
        _ASSERT(index <= logicalLength());
        if (index > logicalLength())
            return *this;
        size_type oldLen = logicalLength();
        size_type newLen = oldLen + 1;

        T tmp(std::move(value));
        reallocator r(true);
        r.reallocate(this, newLen);
        A::moveConstruct(m_pData + oldLen, std::move(tmp));
        ++(buffer()->m_nLength);
        if (index != oldLen) {
            tmp = std::move(*(m_pData + oldLen));
            A::moveAssignRange(m_pData + index + 1, m_pData + index, oldLen - index);
            *(m_pData + index) = std::move(tmp);
        }
        return *this;
    }
    size_type appendMove(T& value)
    {
        push_back(std::move(value));
        return logicalLength() - 1;
    }
    HostArray& appendMove(
        HostArray& otherArray)
    {
        insertMove(end_non_const(), otherArray.begin(), otherArray.end());
        return *this;
    }
    HostArray& appendRep(
        const T& value,
        size_type nCount
    )
    {
        if (nCount <= 0)
            return *this;
        size_type oldLen = logicalLength();
        T tmp(value);
        reallocator r(true);
        r.reallocate(this, oldLen + nCount);
        A::copyConstructFill(m_pData + oldLen, nCount, tmp);
        (buffer()->m_nLength) += nCount;
        return *this;
    }
    template<typename... Args>
    HostArray& appendList(
        const Args&... args
    )
    {
        const auto count_elements = sizeof...(Args);
        if (count_elements == 0)
        {
            return *this;
        }
        size_type oldLen = logicalLength();
        Buffer* oldBuf = buffer();

        // to support appending values from this array. 
        // we should release old buffer only after variadicAssignHelper call, 
        // otherwise default reallocation will cause args to become garbage.
        copy_buffer(oldLen + count_elements, false, false, false);   // important only last flag 
        A::defaultConstructFill(m_pData + oldLen, count_elements);

        variadicAssignHelper(oldLen, args...);
        oldBuf->release();
        return *this;
    }
    iterator append()
    {
        size_type i = append(T());
        return begin_non_const() + i;
    }
    HostArray& removeFirst()
    {
        return removeAt(0);
    }
    HostArray& removeLast()
    {
        resize(length() - 1);
        return *this;
    }
    HostArray& setGrowLength(
        int growLength)
    {
        if (growLength != 0)
        {
            copy_if_referenced();
            buffer()->m_nGrowBy = growLength;
        }
        else
        {
            _ASSERT("Invalid Execution.");
        }
        return *this;
    }
    explicit HostArray(
        size_type physicalLength,
        int growLength = 8) : m_pData(0)
    {
        if (growLength == 0)
        {
            growLength = 8;
        }
        m_pData = Buffer::allocate(physicalLength, growLength)->data();
    }

    HostArray() : m_pData(Buffer::_default()->data())
    {
        buffer()->addref();
    }

    HostArray(const HostArray& source) : m_pData(const_cast<T*>(source.data()))
    {
        static_assert(std::is_copy_constructible<T>::value, "Can not copy array with non-copyable argument");
        buffer()->addref();
    }

    HostArray(HostArray&& source) : m_pData(source.m_pData)
    {
        source.m_pData = Buffer::_default()->data();
        source.buffer()->addref();
    }

    static HostArray<T, A> create(T* sourceArray, int sourceLength)
    {
        HostArray<T, A> res(sourceLength);
        res.assign(sourceArray, sourceArray + sourceLength);
        return res;
    }
    ~HostArray()
    {
        buffer()->release();
    }

    HostArray& operator =(
        const HostArray& source)
    {
        static_assert(std::is_copy_constructible<T>::value, "Can not copy array with non-copyable argument");
        source.buffer()->addref();
        buffer()->release();
        m_pData = source.m_pData;
        return *this;
    }

    HostArray& operator =(
        HostArray&& source)
    {
        buffer()->release();
        m_pData = source.m_pData;
        source.m_pData = Buffer::_default()->data();
        source.buffer()->addref();
        return *this;
    }

    bool operator ==(
        const HostArray& array) const
    {
        if (length() == array.length())
        {
            for (size_type i = 0; i < length(); i++)
            {
                if (at(i) != array[i])
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool operator !=(
        const HostArray& array) const
    {
        return !operator == (array);
    }
    HostArray& setAll(
        const T& value)
    {
        copy_if_referenced();
        T* pData = data();
        size_type n = length();
        while (n)
        {
            pData[--n] = value;
        }
        return *this;
    }
    HostArray& append(
        const HostArray& otherArray)
    {
        insert(end_non_const(), otherArray.begin(), otherArray.end());
        return *this;
    }
    HostArray& append(
        HostArray&& otherArray)
    {
        appendMove(otherArray);
        return *this;
    }
    HostArray& insertAt(
        size_type arrayIndex,
        const T& value)
    {
        size_type len = length();
        if (arrayIndex == len)
        {
            push_back(value);
        }
        else if (arrayIndex < len)
        {
            T tmpval(value);
            reallocator r(true);
            r.reallocate(this, len + 1);
            A::defaultConstruct(m_pData + len);
            ++(buffer()->m_nLength);
            A::moveAssignRange(m_pData + arrayIndex + 1, m_pData + arrayIndex, len - arrayIndex);
            m_pData[arrayIndex] = std::move(tmpval);
        }
        else
        {
            rise_error(Nano::eInvalidIndex);
        }
        return *this;
    }
    HostArray& insertAt(
        size_type index,
        T&& val
    )
    {
        return insertAtMove(index, val);
    }
    HostArray& removeAt(
        size_type arrayIndex)
    {
        assertValid(arrayIndex);
        size_type len = length();
        if (arrayIndex < --len)
        {
            copy_if_referenced();
            T* pData = data();
            A::moveAssignRange(pData + arrayIndex, pData + arrayIndex + 1, len - arrayIndex);
        }
        resize(len);
        return *this;
    }
    HostArray& removeSubArray(
        size_type startIndex,
        size_type endIndex)
    {
        if (!isValid(startIndex) || startIndex > endIndex)
        {
            rise_error(Nano::eInvalidIndex);
        }
        size_type len = length();
        copy_if_referenced();
        T* pData = data();
        ++endIndex;
        size_type n2remove = endIndex - startIndex;
        A::moveAssignRange(pData + startIndex, pData + endIndex, len - endIndex);
        A::destroyRange(pData + len - n2remove, n2remove);
        buffer()->m_nLength -= n2remove;
        return *this;
    }
    bool find(
        const ConstForPtrT& value,
        size_type& findIndex,
        size_type start = 0) const
    {
        if (!empty())
        {
            assertValid(start);
            size_type len = length();
            const T* pData = data();
            for (size_type i = start; i < len; ++i)
            {
                if (pData[i] == value)
                {
                    findIndex = i;
                    return true;
                }
            }
        }
        return false;
    }
    HostArray& setLogicalLength(
        size_type logLength)
    {
        resize(logLength);
        return *this;
    }
    HostArray& setPhysicalLength(
        size_type physLength)
    {
        if (physLength == 0)
        {
            *this = HostArray<T, A>();
        }
        else if (physLength != physicalLength())
        {
            copy_buffer(physLength, !referenced(), true);
        }
        return *this;
    }
    HostArray& reverse()
    {
        if (!empty())
        {
            copy_if_referenced();
            T tmp;
            iterator iter1 = begin_non_const();
            iterator iter2 = end_non_const();
            --iter2;
            while (iter1 < iter2)
            {
                tmp = *iter1;
                *iter1 = *iter2;
                *iter2 = tmp;
                ++iter1;
                --iter2;
            }
        }
        return *this;
    }
    HostArray& swap(
        size_type firstIndex,
        size_type secondIndex)
    {
        if (!isValid(firstIndex) || !isValid(secondIndex))
        {
            rise_error(Nano::eInvalidIndex);
        }
        if (firstIndex != secondIndex)
        {
            T tmp = std::move(at(firstIndex));
            at(firstIndex) = std::move(at(secondIndex));
            at(secondIndex) = std::move(tmp);
        }
        return *this;
    }
    void swap(
        HostArray& other)
    {
        T* temp = m_pData;
        m_pData = other.m_pData;
        other.m_pData = temp;
    }
    bool remove(
        const T& value,
        size_type start = 0)
    {
        size_type i = 0;
        if (find(value, i, start))
        {
            removeAt(i);
            return true;
        }
        return false;
    }
private:

    T* m_pData;

    bool isValid(size_type i) const
    {
        return (i < length());
    }

    T* data()
    {
        return (length() ? m_pData : 0);
    }

    const T* data() const
    {
        return m_pData;
    }

    Buffer* buffer() const
    {
        return (reinterpret_cast<Buffer*>(const_cast<HostArray*>(this)->m_pData) - 1);
    }
    bool referenced() const
    {
        return (buffer()->m_nRefCounter > 1);
    }
    HostArray& variadicAssignHelper(
        size_type
    )
    {
        return *this;
    } 
    HostArray& variadicAssignHelper(
        size_type index,
        const T& value
    )
    {
        m_pData[index] = value;
        ++(buffer()->m_nLength);
        return *this;
    }

    template<typename... Args>
    HostArray& variadicAssignHelper(
        size_type index,
        const T& value,
        const Args&... args
    )
    {
        variadicAssignHelper(index, value);
        return variadicAssignHelper(index + 1, args...);
    }

#if !defined(SWIG)
    template<typename U = T,
        typename std::enable_if<std::is_same<U, T>::value && !std::is_move_assignable<U>::value, bool>::type = true>
    void increaseLogicalLength(
        size_type,
        size_type,
        int,
        const T&)
    {
        static_assert(false, "method not implemented. Class has no move constructor");
    }

    template<typename U = T,
        typename std::enable_if<std::is_same<U, T>::value&& std::is_move_assignable<U>::value, bool>::type = true>
    void increaseLogicalLength(
        size_type logicalLength,
        size_type len,
        int d,
        const T& value)
    {
        reallocator r(m_pData > &value || &value > (m_pData + len));
        r.reallocate(this, logicalLength);
        A::copyConstructFill(m_pData + len, d, value);
    }

    template<typename U = T,
        typename std::enable_if<std::is_same<U, T>::value && !std::is_default_constructible<U>::value, bool>::type = true>
    void increaseLogicalLength(
        size_type,
        size_type,
        int)
    {
        static_assert(false, "method not implemented. Class has no default constructor");
    }

    template<typename U = T,
        typename std::enable_if<std::is_same<U, T>::value&& std::is_default_constructible<U>::value, bool>::type = true>
    void increaseLogicalLength(
        size_type logicalLength,
        size_type len,
        int d)
    {
        copy_before_write(len + d, true);
        A::defaultConstructFill(m_pData + len, d);
    }
#endif
};
#endif // __OPENDWG_HOSTARRAY_H__