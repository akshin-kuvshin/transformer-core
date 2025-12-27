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

#ifndef BITSET_H
#define BITSET_H

#include <set>

namespace BITSET
{
template <class T> class BitSet
{};

#pragma pack(push,1)
template<> class  BitSet<unsigned __int8>
{
public:
  typedef unsigned __int8                             FLAG_TYPE;
  typedef unsigned __int16                            WORD_TYPE;
  typedef unsigned __int32                            DWORD_TYPE;
  typedef unsigned __int64                            BLOCK_TYPE;
  static const int                                    BLOCK_SIZE = sizeof(BLOCK_TYPE);  
  static const int                                    NOT_ELEMENT = UCHAR_MAX;
  static const unsigned __int8                        RADIX = 8*BLOCK_SIZE;  
  static const int                                    DIMENSION = NOT_ELEMENT/RADIX+1;  
  static const int                                    MEMORY_SIZE = DIMENSION*BLOCK_SIZE;  

public:
  BitSet()
  : m_uSize(0)
  , m_uFirst(NOT_ELEMENT)
  {
    m_bitSet[0] = 0;
    m_bitSet[1] = 0;
    m_bitSet[2] = 0;
    m_bitSet[3] = 0;
  }
  ~BitSet()
  {}
  BitSet(const BitSet& rhs)
  : m_uSize(rhs.m_uSize)
  , m_uFirst(rhs.m_uFirst)
  {
    m_bitSet[0] = rhs.m_bitSet[0];
    m_bitSet[1] = rhs.m_bitSet[1];
    m_bitSet[2] = rhs.m_bitSet[2];
    m_bitSet[3] = rhs.m_bitSet[3];
  }
  BitSet& operator=(const BitSet& rhs)
  { 
    if(this != &rhs)
    {
      m_uSize  = rhs.m_uSize;
      m_uFirst = rhs.m_uFirst;
      m_bitSet[0] = rhs.m_bitSet[0];
      m_bitSet[1] = rhs.m_bitSet[1];
      m_bitSet[2] = rhs.m_bitSet[2];
      m_bitSet[3] = rhs.m_bitSet[3];
    }
    return *this; 
  }
  bool operator<(const BitSet& rhs) const 
  { 
    if(m_uSize < rhs.m_uSize)
      return true;
    else if(m_uSize > rhs.m_uSize)
      return false;

    FLAG_TYPE diffSize = 0;
    BLOCK_TYPE diff[DIMENSION];
    if((diffSize = __intersect(m_bitSet, rhs.m_bitSet, diff)) != 0)
    {
      BLOCK_TYPE diff_diff[DIMENSION];
      FLAG_TYPE diff_diffSize = __intersect(m_bitSet, diff, diff_diff);

      if(diffSize < diff_diffSize)
        return true;
      else if(diffSize > diff_diffSize)
        return false;

      if(__first(diff) <  __first(diff_diff))
        return true;
    }
    return false; 
  }
  bool operator==(const BitSet& rhs) const 
  { 
    if(m_uSize != rhs.m_uSize ||
       m_uFirst != rhs.m_uFirst ||
       m_bitSet[0] != rhs.m_bitSet[0] ||
       m_bitSet[1] != rhs.m_bitSet[1] ||
       m_bitSet[2] != rhs.m_bitSet[2] ||
       m_bitSet[3] != rhs.m_bitSet[3])
      return false;
    //const FLAG_TYPE *p1 = (const FLAG_TYPE*)m_bitSet, *p2 = (const FLAG_TYPE*)rhs.m_bitSet;
    //const FLAG_TYPE *x1 = p1, *x2 = p2;
    //int l = MEMORY_SIZE;
    //for(int i = 0; i < l / 8; i++, x1 += 8, x2 += 8)
    //    if(*((long*) x1) != *((long*) x2))
    //      return false;
    //if((l & 4) != 0)
    //{
    //  if(*((int*) x1) != *((int*) x2)) 
    //    return false;
    //  x1 += 4;
    //  x2 += 4;
    //}
    //if((l & 2) != 0)
    //{
    //  if (*((short*) x1) != *((short*) x2)) 
    //    return false;
    //  x1 += 2;
    //  x2 += 2;
    //}
    //if((l & 1) != 0)
    //{
    //  if(*((byte*) x1) != *((byte*) x2))
    //    return false;
    //}
    return true;
  }
  __forceinline bool operator!=(const BitSet& rhs) const
  {
    return !operator==(rhs);
  }

  __forceinline bool empty()                                                        const { return (m_uSize == 0); } 
  __forceinline WORD_TYPE size()                                                    const { return m_uSize; }  
  __forceinline BLOCK_TYPE& block(FLAG_TYPE _c)                                           { ASSERT(_c < NOT_ELEMENT); return __block(m_bitSet, _c); }
  __forceinline const BLOCK_TYPE& block(FLAG_TYPE _c)                               const { ASSERT(_c < NOT_ELEMENT); return __block(m_bitSet, _c); }
  __forceinline bool check(FLAG_TYPE _c)                                            const { ASSERT(_c < NOT_ELEMENT); return __check(m_bitSet, _c); }

  __forceinline void insert(FLAG_TYPE _c)                                                 
  { 
    ASSERT(_c < NOT_ELEMENT); 
    if(!check(_c))
    {
      __block(m_bitSet, _c) |= __flag(_c); 
      if(_c < m_uFirst)
        m_uFirst = _c;
      m_uSize++;
    }
  }
  void __fastcall    insert(const BitSet& rhs)
  {
    m_bitSet[0] |= rhs.m_bitSet[0];
    m_bitSet[1] |= rhs.m_bitSet[1];
    m_bitSet[2] |= rhs.m_bitSet[2];
    m_bitSet[3] |= rhs.m_bitSet[3];  
    m_uSize = __count_bits(m_bitSet[0]) + __count_bits(m_bitSet[1]) + __count_bits(m_bitSet[2]) + __count_bits(m_bitSet[3]);
    m_uFirst = __first(m_bitSet);    
  }
  void __fastcall    insert(const std::set<FLAG_TYPE>::const_iterator _b,
                            const std::set<FLAG_TYPE>::const_iterator _e)
  {
    if(_b == _e)
      return;
    std::set<FLAG_TYPE>::const_iterator it = _b;
    m_uFirst = *_b;
    for(; it != _e; it++)
    {
      m_uSize++;
      __block(m_bitSet, *it) |= __flag(*it);
    }   
  }
  __forceinline void erase(FLAG_TYPE _c)                                                  
  { 
    ASSERT(_c < NOT_ELEMENT); 
    if(check(_c))
    {
      __block(m_bitSet, _c) &= ~__flag(_c); 
      if(_c == m_uFirst)
        m_uFirst = __next(m_bitSet, _c);
      m_uSize--;
    }
  }
  __forceinline void clear()
  {
    m_uSize = 0;
    m_uFirst = NOT_ELEMENT;
    m_bitSet[0] = 0;
    m_bitSet[1] = 0;
    m_bitSet[2] = 0;
    m_bitSet[3] = 0;
  }

  __forceinline FLAG_TYPE first()                                                   const { return empty() ? NOT_ELEMENT : m_uFirst; }
  __forceinline FLAG_TYPE next(FLAG_TYPE _c)                                        const { ASSERT(_c < NOT_ELEMENT); return empty() ? NOT_ELEMENT : __next(m_bitSet, _c); }   

  __forceinline bool contains(const BitSet& rhs) const  
  {
    if((m_bitSet[0] & rhs.m_bitSet[0]) != rhs.m_bitSet[0])
      return false;
    if((m_bitSet[1] & rhs.m_bitSet[1]) != rhs.m_bitSet[1])
      return false;
    if((m_bitSet[2] & rhs.m_bitSet[2]) != rhs.m_bitSet[2])
      return false;
    if((m_bitSet[3] & rhs.m_bitSet[3]) != rhs.m_bitSet[3])
      return false;
    return true;
  }
  __forceinline bool intersects(const BitSet& rhs) const
  {
    if((m_bitSet[0] & rhs.m_bitSet[0]) != 0)
      return true;
    if((m_bitSet[1] & rhs.m_bitSet[1]) != 0)
      return true;
    if((m_bitSet[2] & rhs.m_bitSet[2]) != 0)
      return true;
    if((m_bitSet[3] & rhs.m_bitSet[3]) != 0)
      return true;
    return false;
  }

  __forceinline void exclude(const BitSet& rhs)
  {
    m_bitSet[0] &= ~rhs.m_bitSet[0];
    m_bitSet[1] &= ~rhs.m_bitSet[1];
    m_bitSet[2] &= ~rhs.m_bitSet[2];
    m_bitSet[3] &= ~rhs.m_bitSet[3];
    m_uSize = __count_bits(m_bitSet[0]) + __count_bits(m_bitSet[1]) + __count_bits(m_bitSet[2]) + __count_bits(m_bitSet[3]);
    m_uFirst = __first(m_bitSet);
  }
  __forceinline void intersect(const BitSet& rhs)
  {
    m_bitSet[0] &= rhs.m_bitSet[0];
    m_bitSet[1] &= rhs.m_bitSet[1];
    m_bitSet[2] &= rhs.m_bitSet[2];
    m_bitSet[3] &= rhs.m_bitSet[3];  
    m_uSize = __count_bits(m_bitSet[0]) + __count_bits(m_bitSet[1]) + __count_bits(m_bitSet[2]) + __count_bits(m_bitSet[3]);
    m_uFirst = __first(m_bitSet);
  }

protected:
  __forceinline static BLOCK_TYPE&  __block(BLOCK_TYPE (& _blocks)[DIMENSION], 
                                            FLAG_TYPE _c)                                 { return _blocks[_c/RADIX]; }
  __forceinline static const BLOCK_TYPE&  __block(const BLOCK_TYPE (& _blocks)[DIMENSION], 
                                                  FLAG_TYPE _c)                           { return _blocks[_c/RADIX]; }
  __forceinline static BLOCK_TYPE   __flag(FLAG_TYPE _c)                                  { return ((BLOCK_TYPE)1 << _c%RADIX); }
  __forceinline static bool         __check(const BLOCK_TYPE (& _blocks)[DIMENSION],
                                            FLAG_TYPE _c)                                 { return (__block(_blocks, _c) & __flag(_c)) != 0; }
  __forceinline static FLAG_TYPE    __count_bits(BLOCK_TYPE _block)             
  {
    _block = _block - ((_block >> 1) & 0x5555555555555555UL);
    _block = (_block & 0x3333333333333333UL) + ((_block >> 2) & 0x3333333333333333UL);
    return (unsigned __int8)((((_block + (_block >> 4)) & 0xF0F0F0F0F0F0F0FUL) * 0x101010101010101UL) >> 56);
  }
  __forceinline static FLAG_TYPE    __intersect(const BLOCK_TYPE (& _set1)[DIMENSION], 
                                                const BLOCK_TYPE (& _set2)[DIMENSION],
                                                BLOCK_TYPE (& _res)[DIMENSION])              
  {
    _res[0] = _set1[0] & _set2[0];
    _res[1] = _set1[1] & _set2[1];
    _res[2] = _set1[2] & _set2[2];
    _res[3] = _set1[3] & _set2[3];
    return __count_bits(_res[0]) + __count_bits(_res[1]) + __count_bits(_res[2]) + __count_bits(_res[3]);
  }
  // __first
  __forceinline static FLAG_TYPE    __clamp(FLAG_TYPE _value)
  {
    return _value >= 64 ? 63 : _value;
  }
  __forceinline static FLAG_TYPE    __first(const BLOCK_TYPE* _set, FLAG_TYPE _start_block = 0)
  {
    ASSERT(_start_block < 4);
    if(_start_block == 0 && _set[0] != 0) 
      return __first((DWORD_TYPE*)_set);
    if(_start_block <= 1 && _set[1] != 0) 
      return __first((DWORD_TYPE*)(_set+1)) + (1-_start_block)*64;
    if(_start_block <= 2 && _set[2] != 0) 
      return __first((DWORD_TYPE*)(_set+2)) + (2-_start_block)*64;
    return __clamp(__first((DWORD_TYPE*)(_set+3))) + (3-_start_block)*64;
  }
  __forceinline static FLAG_TYPE    __first(const DWORD_TYPE* _set)
  {
    return _set[0] != 0 ? __first((WORD_TYPE*)_set) : __first((WORD_TYPE*)(_set+1)) + 32;
  }
  __forceinline static FLAG_TYPE    __first(const WORD_TYPE* _set)
  {
    return _set[0] != 0 ? __first((FLAG_TYPE*)_set) : __first((FLAG_TYPE*)(_set+1)) + 16;
  }
  __forceinline static FLAG_TYPE    __first(const FLAG_TYPE* _set)
  {
    return _set[0] != 0 ? __bit(_set[0]) : __bit(_set[1]) + 8;
  }
  __forceinline static FLAG_TYPE    __bit(FLAG_TYPE _block)                         
  {
    if(_block & 0x1) return 0;
    if(_block & 0x2) return 1;
    if(_block & 0x4) return 2;
    if(_block & 0x8) return 3;
    if(_block & 0x10) return 4;
    if(_block & 0x20) return 5;
    if(_block & 0x40) return 6;
    if(_block & 0x80) return 7;
    return 8;
  }
  // __next
  static FLAG_TYPE __fastcall       __next(const BLOCK_TYPE* _set, FLAG_TYPE _c)                         
  {
    FLAG_TYPE res = 255;
    switch(_c/64)
    {
      case 0:
        res = __next((DWORD_TYPE*)_set, _c%64);
        if(res == 64)
          res = __first(_set, 1) + 64;
      break;
      case 1:
        res = __next((DWORD_TYPE*)(_set + 1), _c%64) + 64;
        if(res == 128)
          res = __first(_set, 2) + 128;
      break;
      case 2:
        res = __next((DWORD_TYPE*)(_set + 2), _c%64) + 128;
        if(res == 192)
          res = __first(_set, 3) + 192;
      break;
      case 3:
        res = __clamp(__next((DWORD_TYPE*)(_set + 3), _c%64)) + 192;
      break;
    }
    return res;
  }
  static FLAG_TYPE __fastcall       __next(const DWORD_TYPE* _set, FLAG_TYPE _c)                         
  {
    FLAG_TYPE res = 64;
    if(_c/32 == 0)
    {
      res = __next((WORD_TYPE*)_set, _c%32);
      if(res == 32)
        res = __first((WORD_TYPE*)(_set + 1)) + 32;
    }
    else
      res = __next((WORD_TYPE*)(_set + 1), _c%32) + 32;
    return res;
  }
  static FLAG_TYPE __fastcall       __next(const WORD_TYPE* _set, FLAG_TYPE _c)                         
  {
    FLAG_TYPE res = 32;
    if(_c/16 == 0)
    {
      res = __next((FLAG_TYPE*)_set, _c%16);
      if(res == 16)
        res = __first((FLAG_TYPE*)(_set + 1)) + 16;
    }
    else
      res = __next((FLAG_TYPE*)(_set + 1), _c%16) + 16;
    return res;
  }
  static FLAG_TYPE __fastcall       __next(const FLAG_TYPE* _set, FLAG_TYPE _c)                         
  {
    FLAG_TYPE res = 16;
    if(_c/8 == 0)
    {
      res = __next_bit(*_set, _c%8);
      if(res == 8)
        res = __bit(*(_set + 1)) + 8;
    }
    else
      res = __next_bit(*(_set + 1), _c%8) + 8;
    return res;
  }
  __forceinline static FLAG_TYPE    __next_bit(FLAG_TYPE _block, FLAG_TYPE _c) 
  {
    ASSERT(_c < 8);
    if(_c == 0) _block &= ~0x1;
    if(_c == 1) _block &= ~0x3;
    if(_c == 2) _block &= ~0x7;
    if(_c == 3) _block &= ~0xF;
    if(_c == 4) _block &= ~0x1F;
    if(_c == 5) _block &= ~0x3F;
    if(_c == 6) _block &= ~0x7F;
    if(_c == 7) _block &= ~0xFF;
    return __bit(_block);
  }

protected:
  BLOCK_TYPE m_bitSet[DIMENSION]; //256 bits     
  WORD_TYPE m_uSize;
  FLAG_TYPE m_uFirst;
};
#pragma pack(pop)

template <class T> class BitSet2
{};

template<> class BitSet2<unsigned __int8>
{
public:
  typedef unsigned __int8                             FLAG_TYPE;
protected:
  typedef unsigned __int16                            WORD_TYPE;
  typedef unsigned __int32                            DWORD_TYPE;
  typedef unsigned __int64                            BLOCK_TYPE;
  static const int                                    BLOCK_SIZE = sizeof(BLOCK_TYPE);
  static const int                                    NOT_ELEMENT = UCHAR_MAX;
  static const unsigned __int8                        RADIX = 8 * BLOCK_SIZE;
  static const int                                    DIMENSION = NOT_ELEMENT / RADIX + 1;
  //static const int                                    MEMORY_SIZE = DIMENSION * BLOCK_SIZE;

public:
  BitSet2() : m_uSize(0)
  {
    m_bitSet[0] = 0;
    m_bitSet[1] = 0;
    m_bitSet[2] = 0;
    m_bitSet[3] = 0;
  }
  ~BitSet2()
  {}
  BitSet2(const BitSet2& rhs) : m_uSize(rhs.m_uSize)
  {
    m_bitSet[0] = rhs.m_bitSet[0];
    m_bitSet[1] = rhs.m_bitSet[1];
    m_bitSet[2] = rhs.m_bitSet[2];
    m_bitSet[3] = rhs.m_bitSet[3];
  }
  BitSet2& operator=(const BitSet2& rhs)
  {
    if (this != &rhs)
    {
      m_uSize = rhs.m_uSize;
      m_bitSet[0] = rhs.m_bitSet[0];
      m_bitSet[1] = rhs.m_bitSet[1];
      m_bitSet[2] = rhs.m_bitSet[2];
      m_bitSet[3] = rhs.m_bitSet[3];
    }
    return *this;
  }
  bool operator<(const BitSet2& rhs) const
  {
    if (m_uSize < rhs.m_uSize)
      return true;
    if (m_uSize > rhs.m_uSize)
      return false;

    WORD_TYPE diffSize;
    BLOCK_TYPE diff[DIMENSION];
    if ((diffSize = __intersect(m_bitSet, rhs.m_bitSet, diff)) != 0)
    {
      BLOCK_TYPE diff_diff[DIMENSION];
      const WORD_TYPE diff_diffSize = __intersect(m_bitSet, diff, diff_diff);

      if (diffSize < diff_diffSize)
        return true;
      if (diffSize > diff_diffSize)
        return false;

      if (__first(diff) < __first(diff_diff))
        return true;
    }
    return false;
  }
  bool operator==(const BitSet2& rhs) const
  {
    if (m_uSize != rhs.m_uSize ||
      m_bitSet[0] != rhs.m_bitSet[0] ||
      m_bitSet[1] != rhs.m_bitSet[1] ||
      m_bitSet[2] != rhs.m_bitSet[2] ||
      m_bitSet[3] != rhs.m_bitSet[3])
      return false;
    return true;
  }
  __forceinline bool operator!=(const BitSet2& rhs) const
  {
    return !operator==(rhs);
  }
  __forceinline bool empty()                                                        const { return m_uSize == 0; }
  __forceinline WORD_TYPE size()                                                    const { return m_uSize; }
  __forceinline BLOCK_TYPE& block(FLAG_TYPE _c)                                           { return __block(m_bitSet, _c); }
  __forceinline const BLOCK_TYPE& block(FLAG_TYPE _c)                               const { return __block(m_bitSet, _c); }
  __forceinline bool check(FLAG_TYPE _c)                                            const { return __check(m_bitSet, _c); }

  __forceinline void insert(FLAG_TYPE _c)
  {
    if (!check(_c))
    {
      __block(m_bitSet, _c) |= __flag(_c);
      m_uSize++;
    }
  }
  void __fastcall    insert(const BitSet2& rhs)
  {
    m_bitSet[0] |= rhs.m_bitSet[0];
    m_bitSet[1] |= rhs.m_bitSet[1];
    m_bitSet[2] |= rhs.m_bitSet[2];
    m_bitSet[3] |= rhs.m_bitSet[3];
    m_uSize = _size();
  }
  void __fastcall    insert(std::set<FLAG_TYPE>::const_iterator _b, std::set<FLAG_TYPE>::const_iterator _e)
  {
    if (_b == _e)
      return;
    for ( std::set<FLAG_TYPE>::const_iterator it = _b; it != _e; it++)
    {
      m_uSize++;
      __block(m_bitSet, *it) |= __flag(*it);
    }
  }
  __forceinline void erase(FLAG_TYPE _c)
  {
    if (check(_c))
    {
      __block(m_bitSet, _c) &= ~__flag(_c);
      m_uSize--;
    }
  }
  __forceinline void clear()
  {
    m_uSize = 0;
    m_bitSet[0] = 0;
    m_bitSet[1] = 0;
    m_bitSet[2] = 0;
    m_bitSet[3] = 0;
  }

  class BitSet2Iter
  {
    const BitSet2& m_set;
    WORD_TYPE _c;
    BitSet2Iter(const BitSet2& set, WORD_TYPE _c) : m_set(set), _c(_c) {}
  public:
    BitSet2Iter& operator=(const BitSet2Iter& rhs)
    {
      if (m_set == rhs.m_set)
        _c = rhs._c;
      return *this;
    }
    FLAG_TYPE operator*() const
    {
      return FLAG_TYPE(_c);
    }
    const BitSet2Iter& operator++()
    {
      _c = m_set.__next(m_set.m_bitSet, FLAG_TYPE(_c));
      return *this;
    }
    bool operator==(const BitSet2Iter& rhs) const
    {
      return this==&rhs || (&m_set == &rhs.m_set && _c == rhs._c);
    }
    __forceinline bool operator!=(const BitSet2Iter& rhs) const
    {
      return !operator==(rhs);
    }

    friend class BitSet2; 
  };
  BitSet2Iter begin() const
  {
    return empty() ? end() : BitSet2Iter(*this, __first(m_bitSet));
  }
  BitSet2Iter end() const
  {
    return BitSet2Iter(*this, NOT_ELEMENT+1);
  }
  //__forceinline FLAG_TYPE first()                                                   const { return empty() ? NOT_ELEMENT : __first(m_bitSet); }
  //__forceinline FLAG_TYPE next(FLAG_TYPE _c)                                        const { ASSERT(_c < NOT_ELEMENT); return empty() ? NOT_ELEMENT : __next(m_bitSet, _c); }

  __forceinline bool contains(const BitSet2& rhs) const
  {
    if ((m_bitSet[0] & rhs.m_bitSet[0]) != rhs.m_bitSet[0])
      return false;
    if ((m_bitSet[1] & rhs.m_bitSet[1]) != rhs.m_bitSet[1])
      return false;
    if ((m_bitSet[2] & rhs.m_bitSet[2]) != rhs.m_bitSet[2])
      return false;
    if ((m_bitSet[3] & rhs.m_bitSet[3]) != rhs.m_bitSet[3])
      return false;
    return true;
  }
  __forceinline bool intersects(const BitSet2& rhs) const
  {
    if ((m_bitSet[0] & rhs.m_bitSet[0]) != 0)
      return true;
    if ((m_bitSet[1] & rhs.m_bitSet[1]) != 0)
      return true;
    if ((m_bitSet[2] & rhs.m_bitSet[2]) != 0)
      return true;
    if ((m_bitSet[3] & rhs.m_bitSet[3]) != 0)
      return true;
    return false;
  }

  __forceinline void exclude(const BitSet2& rhs)
  {
    m_bitSet[0] &= ~rhs.m_bitSet[0];
    m_bitSet[1] &= ~rhs.m_bitSet[1];
    m_bitSet[2] &= ~rhs.m_bitSet[2];
    m_bitSet[3] &= ~rhs.m_bitSet[3];
    m_uSize = _size();
  }

  __forceinline void intersect(const BitSet2& rhs)
  {
    m_bitSet[0] &= rhs.m_bitSet[0];
    m_bitSet[1] &= rhs.m_bitSet[1];
    m_bitSet[2] &= rhs.m_bitSet[2];
    m_bitSet[3] &= rhs.m_bitSet[3];
    m_uSize = _size();
  }

protected:
  __forceinline WORD_TYPE _size()
  {
    return WORD_TYPE(__count_bits(m_bitSet[0])) + __count_bits(m_bitSet[1]) + __count_bits(m_bitSet[2]) + __count_bits(m_bitSet[3]);
  }
  __forceinline static BLOCK_TYPE&  __block(BLOCK_TYPE(&_blocks)[DIMENSION], FLAG_TYPE _c)
  {
    return _blocks[_c / RADIX];
  }
  __forceinline static const BLOCK_TYPE&  __block(const BLOCK_TYPE(&_blocks)[DIMENSION], FLAG_TYPE _c)
  {
    return _blocks[_c / RADIX];
  }
  __forceinline static BLOCK_TYPE   __flag(FLAG_TYPE _c) { return BLOCK_TYPE(1) << _c % RADIX; }
  __forceinline static bool         __check(const BLOCK_TYPE(&_blocks)[DIMENSION], FLAG_TYPE _c)
  {
    return (__block(_blocks, _c) & __flag(_c)) != 0;
  }
  __forceinline static FLAG_TYPE    __count_bits(BLOCK_TYPE _block)
  {
    _block = _block - ((_block >> 1) & 0x5555555555555555UL);
    _block = (_block & 0x3333333333333333UL) + ((_block >> 2) & 0x3333333333333333UL);
    return static_cast<unsigned __int8>((((_block + (_block >> 4)) & 0xF0F0F0F0F0F0F0FUL) * 0x101010101010101UL) >> 56);
  }
  __forceinline static WORD_TYPE __intersect(const BLOCK_TYPE(&_set1)[DIMENSION], const BLOCK_TYPE(&_set2)[DIMENSION], BLOCK_TYPE(&_res)[DIMENSION])
  {
    _res[0] = _set1[0] & _set2[0];
    _res[1] = _set1[1] & _set2[1];
    _res[2] = _set1[2] & _set2[2];
    _res[3] = _set1[3] & _set2[3];
    return WORD_TYPE(__count_bits(_res[0])) + __count_bits(_res[1]) + __count_bits(_res[2]) + __count_bits(_res[3]);
  }
  // __first
   __forceinline static WORD_TYPE __first(const BLOCK_TYPE* _set, FLAG_TYPE _start_block = 0)
  {
    ASSERT(_start_block < 4);
    if (_start_block == 0 && _set[0] != 0)
      return __first((DWORD_TYPE*)_set);
    if (_start_block <= 1 && _set[1] != 0)
      return __first((DWORD_TYPE*)(_set + 1)) + (1 - _start_block) * 64;
    if (_start_block <= 2 && _set[2] != 0)
      return __first((DWORD_TYPE*)(_set + 2)) + (2 - _start_block) * 64;
    return WORD_TYPE(__first((DWORD_TYPE*)(_set + 3))) + (3 - _start_block) * 64;
  }
  __forceinline static FLAG_TYPE __first(const DWORD_TYPE* _set)
  {
    return _set[0] != 0 ? __first((WORD_TYPE*)_set) : __first((WORD_TYPE*)(_set + 1)) + 32;
  }
  __forceinline static FLAG_TYPE __first(const WORD_TYPE* _set)
  {
    return _set[0] != 0 ? __first((FLAG_TYPE*)_set) : __first((FLAG_TYPE*)(_set + 1)) + 16;
  }
  __forceinline static FLAG_TYPE __first(const FLAG_TYPE* _set)
  {
    return _set[0] != 0 ? __bit(_set[0]) : __bit(_set[1]) + 8;
  }
  __forceinline static FLAG_TYPE __bit(FLAG_TYPE _block)
  {
    if (_block & 0x1) return 0;
    if (_block & 0x2) return 1;
    if (_block & 0x4) return 2;
    if (_block & 0x8) return 3;
    if (_block & 0x10) return 4;
    if (_block & 0x20) return 5;
    if (_block & 0x40) return 6;
    if (_block & 0x80) return 7;
    return 8;
  }
  // __next
  static WORD_TYPE __fastcall __next(const BLOCK_TYPE* _set, FLAG_TYPE _c)
  {
    WORD_TYPE res = 256;
    switch (_c / 64)
    {
    case 0:
      res = __next((DWORD_TYPE*)_set, _c % 64);
      if (res == 64)
        res += __first(_set, 1);
      break;
    case 1:
      res = __next((DWORD_TYPE*)(_set + 1), _c % 64) + 64;
      if (res == 128)
        res += __first(_set, 2);
      break;
    case 2:
      res = __next((DWORD_TYPE*)(_set + 2), _c % 64) + 128;
      if (res == 192)
        res += __first(_set, 3);
      break;
    case 3:
      res = __next((DWORD_TYPE*)(_set + 3), _c % 64);
      res += 192;
      break;
    }
    return res;
  }
  static FLAG_TYPE __fastcall __next(const DWORD_TYPE* _set, FLAG_TYPE _c)
  {
    FLAG_TYPE res = 64;
    if (_c / 32 == 0)
    {
      res = __next((WORD_TYPE*)_set, _c % 32);
      if (res == 32)
        res = __first((WORD_TYPE*)(_set + 1)) + 32;
    }
    else
      res = __next((WORD_TYPE*)(_set + 1), _c % 32) + 32;
    return res;
  }
  static FLAG_TYPE __fastcall __next(const WORD_TYPE* _set, FLAG_TYPE _c)
  {
    FLAG_TYPE res = 32;
    if (_c / 16 == 0)
    {
      res = __next((FLAG_TYPE*)_set, _c % 16);
      if (res == 16)
        res = __first((FLAG_TYPE*)(_set + 1)) + 16;
    }
    else
      res = __next((FLAG_TYPE*)(_set + 1), _c % 16) + 16;
    return res;
  }
  static FLAG_TYPE __fastcall __next(const FLAG_TYPE* _set, FLAG_TYPE _c)
  {
    FLAG_TYPE res = 16;
    if (_c / 8 == 0)
    {
      res = __next_bit(*_set, _c % 8);
      if (res == 8)
        res = __bit(*(_set + 1)) + 8;
    }
    else
      res = __next_bit(*(_set + 1), _c % 8) + 8;
    return res;
  }
  __forceinline static FLAG_TYPE __next_bit(FLAG_TYPE _block, FLAG_TYPE _c)
  {
    ASSERT(_c < 8);
    if (_c == 0) _block &= ~0x1;
    if (_c == 1) _block &= ~0x3;
    if (_c == 2) _block &= ~0x7;
    if (_c == 3) _block &= ~0xF;
    if (_c == 4) _block &= ~0x1F;
    if (_c == 5) _block &= ~0x3F;
    if (_c == 6) _block &= ~0x7F;
    if (_c == 7) _block &= ~0xFF;
    return __bit(_block);
  }

protected:
  WORD_TYPE m_uSize;
  BLOCK_TYPE m_bitSet[DIMENSION]; //256 bits     
};

}

#endif