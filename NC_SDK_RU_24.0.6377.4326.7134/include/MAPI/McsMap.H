
#pragma once

//==================================================================================================

#pragma pack(push,1)
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
class McsMap
{
protected:

#ifdef _MCEYE
public:
#endif

	// Association
	struct McsAssoc
	{
		McsAssoc* pNext;
		UINT      nHashValue;  // needed for efficient iteration
		KEY       key;   // !!! Keep <value> after <key>
		VALUE     value; // !!! Keep <rawIndex> after <value>
	};

protected:

#ifdef _MCEYE
public:
#endif

	McsAssoc**      m_pHashTable;
	int             m_nHashTableSize;
	int             m_nCount;
	McsAssoc*       m_pFreeList;
	struct McsPlex* m_pBlocks;
	int             m_nBlockSize;

	bool            m_fStripHTOverflowWarning;
	bool            m_fHashSetMode;

public:

	typedef McsHashset<KEY, ARG_KEY>   KeysHashset;
	typedef McsArray<KEY, ARG_KEY>     KeysArray;
	typedef McsArray<VALUE, ARG_VALUE> ValuesArr;

	DECLARE_OBJ_NEWDEL;
	McsMap(INT_PTR nBlockSize = 10);

	McsMap(const McsMap&);
	~McsMap();

// Attributes
	// number of elements
	int  GetCount() const { return m_nCount; }
	int  GetSize() const { return m_nCount; }
	int  Length() const { return m_nCount; }
	bool IsEmpty() const { return m_nCount == 0; }
	bool isEmpty() const { return m_nCount == 0; }

	// Lookup
	bool Lookup(ARG_KEY key, VALUE& rValue) const;
	bool isExist(ARG_KEY) const;
		// синонимы isExist
	bool exist(ARG_KEY key) const {return isExist(key);}
	bool Exist(ARG_KEY key) const {return isExist(key);}
	bool contains(ARG_KEY key) const {return isExist(key);}

// Operations
	// Lookup and add if not there
	VALUE& operator[](ARG_KEY key);
	VALUE& valueAt(ARG_KEY key); //	same as operator []
	const KEY& keyAt(ARG_KEY key) const; //	same as operator [], but returns stored key ref in the map
	void getAt(ARG_KEY key, const KEY*& pStoredKey, VALUE*& pStoredVal);

	void getAt(ARG_KEY key, const KEY*& pStoredKey, const VALUE*& pStoredVal) const {
		((McsMap*)this)->getAt(key, pStoredKey, (VALUE*&)pStoredVal);
	}

	VALUE* getExistingValPtr(ARG_KEY key); // if no such pair exists then will return NULL
	const VALUE* getExistingValPtr(ARG_KEY key) const; // if no such pair exists then will return NULL

	// Get an existing pair for the given key.
	// If there are no such ones, both pointers will be NULL.
	bool assocAt(ARG_KEY key, const KEY*& pStoredKey, VALUE*& pStoredVal);

	bool assocAt(ARG_KEY key, const KEY*& pStoredKey, const VALUE*& pStoredVal) const {
		return ((McsMap*)this)->assocAt(key, pStoredKey, (VALUE*&)pStoredVal);
	}

		// query all keys in an array form, returns number of keys
	int getKeys(OUT KeysArray&) const;

		// query all values an array form, returns number of values
	int getValues(OUT ValuesArr&) const;

	// add a new (key, value) pair
	void SetAt(ARG_KEY key, ARG_VALUE newValue);

	// removing existing (key, ?) pair
	bool RemoveKey(ARG_KEY key);
	McsMap& operator -= (ARG_KEY key) { RemoveKey(key); return *this; }
	void RemoveAll();

	bool operator == (const McsMap&) const;
	bool operator != (const McsMap& cw) const { return !(*this==cw); }

	// iterating all (key, value) pairs
	MCSPOSITION GetStartPosition() const;
	void GetNextAssoc(MCSPOSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;
	void GetNextAssoc(MCSPOSITION& rNextPosition, KEY*& pKey, VALUE*& pValue);

	void GetNextAssoc(MCSPOSITION& rNextPosition, const KEY*& pKey, const VALUE*& pValue) const {
		((McsMap*)this)->GetNextAssoc(rNextPosition, (KEY*&)pKey, (VALUE*&)pValue);
	}

	void GetNextKey(MCSPOSITION& rNextPosition, KEY& rKey) const;
	void GetNextKey(MCSPOSITION& rNextPosition, KEY*& pKey);

	void GetNextKey(MCSPOSITION& rNextPosition, const KEY*& pKey) const {
		((McsMap*)this)->GetNextKey(rNextPosition, (KEY*&)pKey);
	}

	void GetNextValue(MCSPOSITION& rNextPosition, VALUE& rValue) const;
	void GetNextValue(MCSPOSITION& rNextPosition, VALUE*& pValue);

	void GetNextValue(MCSPOSITION& rNextPosition, const VALUE*& pValue) const {
		((McsMap*)this)->GetNextValue(rNextPosition, (VALUE*&)pValue);
	}

	bool getAsArray(ValuesArr& values) const;
	bool AsArray(ValuesArr& values) const { return getAsArray(values); }

		// ¬ыдаЄт набор ключей в виде Hashset
	bool getAsHashset(OUT KeysHashset& set) const;

	McsMap& operator = (const McsMap&);

		// Intersect by keys
	void intersect(const McsMap& map);
	void intersect(const KeysHashset& keySet);
	void intersect(const KeysArray& keyArr);

	McsMap& operator &= (const McsMap& map) { intersect(map); return *this; }
	McsMap& operator &= (const KeysHashset& keySet) { intersect(keySet); return *this; }
	McsMap& operator &= (const KeysArray& keyArr) { intersect(keyArr); return *this; }

	void removeSubset(const McsMap& map);
	void removeSubset(const KeysHashset& keySet);
	void removeSubset(const KeysArray& keyArr);

	bool contains(const McsMap& map) const;
	bool contains(const KeysArray& keyArr) const;
	bool contains(const KeysHashset& keySet) const;
	bool containsAnyOf(const McsMap& map) const;
	bool containsAnyOf(const KeysArray& keyArr) const;
	bool containsAnyOf(const KeysHashset& keySet) const;

	McsMap& operator -= (const McsMap& map) { removeSubset(map); return *this; }
	McsMap& operator -= (const KeysHashset& keySet) { removeSubset(keySet); return *this; }
	McsMap& operator -= (const KeysArray& keyArr) { removeSubset(keyArr); return *this; }

	void Append(const McsMap& map);
	McsMap& operator |= (const McsMap& map) { Append(map); return *this; }
	McsMap& operator += (const McsMap& map) { Append(map); return *this; }

	// advanced features for derived classes
	int GetHashTableSize() const { return m_nHashTableSize; }
	void InitHashTable(UINT_PTR hashSize, bool fAllocNow = true);
		// method which grows size of hash table to the next simple size from <> array if possible
	bool _growHashTableSize();

protected:
	McsAssoc* NewAssoc();
	void      FreeAssoc(McsAssoc*);
	McsAssoc* GetAssocAt(ARG_KEY, UINT&, bool fAllowGHT) const;
};
#pragma pack(pop)

//=============================================================================

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
__inline void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::SetAt(ARG_KEY key, ARG_VALUE newValue)
	{ (*this)[key] = newValue; }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
__inline MCSPOSITION McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : MCS_BEFORE_START_POSITION; }

//=============================================================================

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::McsMap(INT_PTR nBlockSize)
{
	MCSASSERTx64_EX_32bit(nBlockSize, nBlockSize=10);
	MCSASSERT_EX(nBlockSize > 0, return);

	m_pHashTable = NULL;
	m_fStripHTOverflowWarning = false;
	m_nHashTableSize = MIN_MAP_HASH_TABLE_SIZE;
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = (int)nBlockSize;
	m_fHashSetMode = false;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::McsMap(const McsMap& cf)
{
	m_pHashTable = NULL;
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nHashTableSize = cf.m_nHashTableSize;
	m_nBlockSize = cf.m_nBlockSize;

	m_fStripHTOverflowWarning = false;
	m_fHashSetMode = false;

	*this = cf;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator == (const McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>& cw)const
{
	if(m_nCount != cw.m_nCount)
		return false;
	if(m_nCount==0)
		return true;
	
	for (int nHash = 0; nHash < m_nHashTableSize; nHash++)
	{
		for (McsAssoc* pAssocThis = m_pHashTable[nHash]; pAssocThis; pAssocThis = pAssocThis->pNext)
		{
			UINT nHashCW=0;
			McsAssoc* pAssocCW = cw.GetAssocAt(pAssocThis->key, nHashCW, false);
			if(!pAssocCW)
				return false;
			if(m_fHashSetMode)
				continue;
			if(pAssocCW->value != pAssocThis->value)
				return false;
		}
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>& McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator = (const McsMap& cf)
{
	if(this == &cf)
		return *this;

	RemoveAll();

	// initialize hash table without size checking
	if(cf.m_nCount)
		InitHashTable(m_nHashTableSize, true);

	MCSPOSITION pos = cf.GetStartPosition();
	const KEY* pKey = NULL; const VALUE* pVal = NULL;
	while(pos) {
		cf.GetNextAssoc(pos, pKey, pVal);
		SetAt(*pKey, *pVal);
	}

	return *this;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::intersect(const McsMap& map)
{
	if(0 == map.m_nCount) {
		RemoveAll();
		return;
	}

	// ѕри цепочном переборе нельз€ удал€ть текущий элемент. ћожно набрать
	// массив того, что удал€ть, но это медленно, будем запоминать только
	// один ID и флаг, надо ли его удал€ть на следующем шаге.

	bool fRemove = false;
	KEY key4remove;

	MCSPOSITION pos = GetStartPosition();
	KEY* pk = NULL; VALUE* pv = NULL;
	while(pos)
	{
		if(fRemove) {
			RemoveKey(key4remove);
			fRemove = false;
		}

		GetNextAssoc(pos, pk, pv);
		if(map.isExist(*pk))
			continue;

		// сразу удал€ть нельз€, не сработает GetNextAssoc
		key4remove = *pk;
		fRemove = true;
	}
	if(fRemove)
		RemoveKey(key4remove);

	return;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::intersect(const KeysArray& keyArr)
{
	if(keyArr.isEmpty()) {
		RemoveAll();
		return;
	}

	if(m_nCount == 0)
		return;

	// ‘ормируем множество ключей на основе массива, которое реально может понадобитьс€
	// дл€ фильтрации мапа. ѕлюс такого подхода: в множество попадут только те значени€
	// которые погут дать положительный результат на isExist запрос.
	KeysHashset keySet;
	int i, n = keyArr.GetSize();
	for(i=0; i<n; i++) {
		const KEY& k = keyArr.GetData()[i];
		if(isExist(k))
			keySet |= k;
	}

	if(keySet.isEmpty()) {
		RemoveAll();
		return;
	}

	// ѕри цепочном переборе нельз€ удал€ть текущий элемент. ћожно набрать
	// массив того, что удал€ть, но это медленно, будем запоминать только
	// один ID и флаг, надо ли его удал€ть на следующем шаге.

	bool fRemove = false;
	KEY key4remove;

	MCSPOSITION pos = GetStartPosition();
	KEY* pk = NULL; VALUE* pv = NULL;
	while(pos)
	{
		if(fRemove) {
			RemoveKey(key4remove);
			fRemove = false;
		}

		GetNextAssoc(pos, pk, pv);
		if(keySet.isExist(*pk))
			continue;

		// сразу удал€ть нельз€, не сработает GetNextAssoc
		key4remove = *pk;
		fRemove = true;
	}
	if(fRemove)
		RemoveKey(key4remove);

	return;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::removeSubset(const McsMap& map)
{
	MCSPOSITION pos = map.GetStartPosition();
	const KEY* pK = NULL;
	while(pos) {
		map.GetNextKey(pos, pK);
		RemoveKey(*pK);
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::removeSubset(const KeysHashset& keySet)
{
	MCSPOSITION pos = keySet.GetStartPosition();
	const KEY* pK = NULL;
	while(pos) {
		keySet.GetNextKey(pos, pK);
		RemoveKey(*pK);
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::removeSubset(const KeysArray& keyArr)
{
	for(int i=keyArr.GetSize()-1; i>=0; --i) {
		RemoveKey(keyArr.GetData()[i]);
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::Append(const McsMap& map)
{
	MCSPOSITION pos = map.GetStartPosition();
	const KEY* pk = NULL; const VALUE* pv = NULL;
	while(pos) {
		map.GetNextAssoc(pos, pk, pv);
		SetAt(*pk, *pv);
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::contains(const McsMap& map) const
{
	if(this == &map)
		return true;

	MCSPOSITION pos = map.GetStartPosition();
	const KEY* pk = NULL;
	while(pos) {
		map.GetNextKey(pos, pk);
		if(!isExist(*pk))
			return false;
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::contains(const KeysArray& keyArr) const
{
	for(int i = keyArr.GetSize()-1; i>=0; i--) {
		const KEY& k = keyArr.GetData()[i];
		if(!isExist(k))
			return false;
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::contains(const KeysHashset& keySet) const
{
	MCSPOSITION pos = keySet.GetStartPosition();
	const KEY* pk = NULL;
	while(pos) {
		keySet.GetNextKey(pos, pk);
		if(!isExist(*pk))
			return false;
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::containsAnyOf(const McsMap& map) const
{
	if(this == &map)
		return true;

	MCSPOSITION pos = map.GetStartPosition();
	const KEY* pk = NULL;
	while(pos) {
		map.GetNextKey(pos, pk);
		if(isExist(*pk))
			return true;
	}

	return false;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::containsAnyOf(const KeysArray& keyArr) const
{
	for(int i = keyArr.GetSize()-1; i>=0; i--) {
		const KEY& k = keyArr.GetData()[i];
		if(isExist(k))
			return true;
	}

	return false;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::containsAnyOf(const KeysHashset& keySet) const
{
	MCSPOSITION pos = keySet.GetStartPosition();
	const KEY* pk = NULL;
	while(pos) {
		keySet.GetNextKey(pos, pk);
		if(isExist(*pk))
			return true;
	}

	return false;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getAsArray(ValuesArr& elements) const
{
	elements.RemoveAll();
	if(m_nCount ==0 )
		return false;

	int i=0;

	elements.SetSize(m_nCount);

	const VALUE* pVal=NULL;
	MCSPOSITION pos = GetStartPosition();
	while(pos) {
		GetNextValue(pos, pVal);
		elements[i++] = *pVal;
	}

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::_growHashTableSize()
{
	if(!m_pHashTable)
		return false;

	int newTableSize = m_nHashTableSize * 10;
	newTableSize = _fitHashTableSizeToSimpleNum(newTableSize);
	if(newTableSize == m_nHashTableSize)
		return false;

	// m_pBlocks, m_nCount, m_pFreeList, m_nHolesInRawTable, m_KP, m_VP MUST stay the same;
	// only one thing will be changed - hash table and used assocs links
	McsAssoc** _pHashTable     = m_pHashTable;
	int        _nHashTableSize = m_nHashTableSize;
	int        nCount          = m_nCount;

	// 1'st we must join all associations in map into single chain
	m_pHashTable = NULL; //	prevent old table from delete
	m_nHashTableSize = 0;
	m_nCount = 0;
	InitHashTable(newTableSize, true);
	m_nCount = nCount;

	for (int oldHTIdx = 0; oldHTIdx<_nHashTableSize; oldHTIdx++)
	{
		for (McsAssoc *pAssoc = _pHashTable[oldHTIdx], *pNextAssocInOldHT = NULL; pAssoc; pAssoc = pNextAssocInOldHT)
		{
			pNextAssocInOldHT = pAssoc->pNext;

			UINT newHTIdx = McsHashKey<ARG_KEY>(pAssoc->key) % newTableSize;

			pAssoc->pNext = m_pHashTable[newHTIdx];
			pAssoc->nHashValue = newHTIdx;
			m_pHashTable[newHTIdx] = pAssoc;
		}
	}

	mcsMemDelete(_pHashTable); _pHashTable = NULL;

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::InitHashTable
(UINT_PTR nHashSize, bool bAllocNow)
{
	if(m_nHashTableSize != (int)nHashSize) {
		MCSASSERT_EX(IsEmpty(), return);
		nHashSize = _fitHashTableSizeToSimpleNum(nHashSize);
	}

	if(m_nHashTableSize == (int)nHashSize) {
		if(!bAllocNow)
			return;
		if(m_pHashTable)
			return;
	}

	m_nHashTableSize = (int)nHashSize;

	if (m_pHashTable) {
		// free hash table
		mcsMemDelete(m_pHashTable);
		m_pHashTable = NULL;
	}

	if (bAllocNow) {
		m_pHashTable = mcsMemNew(McsAssoc*[m_nHashTableSize]);
		CHECK_OUT_OF_MEM(!m_pHashTable);
		memset(m_pHashTable, 0, sizeof(McsAssoc*) * m_nHashTableSize);
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::isExist(ARG_KEY key) const
{
	UINT nHash;
	McsAssoc* pAssoc = GetAssocAt(key, nHash, false);
	if (pAssoc == NULL)
		return false;  // not in map

	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::RemoveAll()
{
	if(!m_pHashTable)
		return;
	McsAssoc** _pHashTable     = m_pHashTable;
	int        _nHashTableSize = m_nHashTableSize;
	McsPlex*   _pBlocks        = m_pBlocks;

	// free hash table
	m_pHashTable = NULL;
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;

	if(_pHashTable)
	{
		// destroy elements (values and keys)
		for (int nHash = 0; nHash<_nHashTableSize; nHash++)
		{
			for (McsAssoc* pAssoc = _pHashTable[nHash]; pAssoc; pAssoc = pAssoc->pNext)
			{
				if(!m_fHashSetMode)
					McsDestructElements<VALUE>(MCS_GET_OBJ_ADDR(pAssoc->value),1);//(VALUE*)&pAssoc->value, 1);
				McsDestructElements<KEY>(MCS_GET_OBJ_ADDR(pAssoc->key), 1);//(KEY*)&pAssoc->key, 1);
			}
		}
		mcsMemDelete(_pHashTable); _pHashTable=NULL;
	}

	if(_pBlocks) {
		_pBlocks->FreeDataChain();
		_pBlocks = NULL;
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::~McsMap()
{
	RemoveAll();
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::McsAssoc*
McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::NewAssoc()
{
	if (m_pFreeList == NULL)
	{
		// add another block          
		McsPlex* newBlock = McsPlex::Create(m_pBlocks, m_nBlockSize, sizeof(McsMap::McsAssoc));
		// chain them into free list
		McsMap::McsAssoc* pAssoc = (McsMap::McsAssoc*) newBlock->data();
		// free in reverse order to make it easier to debug
		pAssoc += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
		{
			pAssoc->pNext = m_pFreeList;
			m_pFreeList = pAssoc;
		}
	}
	MCSASSERT_EX(m_pFreeList != NULL, return NULL);  // we must have something

	McsMap::McsAssoc* pAssoc = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	m_nCount++;
	MCSASSERT(m_nCount > 0);  // make sure we don't overflow
	McsConstructElements<KEY>(MCS_GET_OBJ_ADDR(pAssoc->key),1);//(KEY*)&pAssoc->key, 1);
	if(!m_fHashSetMode)
		McsConstructElements<VALUE>(MCS_GET_OBJ_ADDR(pAssoc->value),1);//(VALUE*)&pAssoc->value, 1);   // special construct values

	return pAssoc;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::FreeAssoc(typename McsMap::McsAssoc* pAssoc)
{
	if(!m_fHashSetMode)
		McsDestructElements<VALUE>(MCS_GET_OBJ_ADDR(pAssoc->value),1);//(VALUE*)&pAssoc->value, 1);
	McsDestructElements<KEY>(MCS_GET_OBJ_ADDR(pAssoc->key),1);//(KEY*)&pAssoc->key, 1);

	pAssoc->pNext = m_pFreeList;
	pAssoc->nHashValue = -1;
	m_pFreeList = pAssoc;
	m_nCount--;
	MCSASSERT_EX(m_nCount >= 0, return);  // make sure we don't underflow

	// if no more elements, cleanup completely
	if (m_nCount == 0)
		RemoveAll();
}
//=============================================================================

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::assocAt(ARG_KEY key, const KEY*& pKey, VALUE*& pValue)
{
	UINT nHash = McsHashKey<ARG_KEY>(key) % m_nHashTableSize;
	McsAssoc* pAssoc = GetAssocAt(key, nHash, false);
	if(pAssoc)
	{
		pKey = MCS_GET_OBJ_ADDR(pAssoc->key);
		pValue = MCS_GET_OBJ_ADDR(pAssoc->value);
		return true;
	}

	pKey = NULL;
	pValue = NULL;
	return false;
}
//=============================================================================

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::McsAssoc*
McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetAssocAt(ARG_KEY key, UINT& nHash, bool fAllowGHT) const
// find association (or return NULL)
{
	nHash = McsHashKey<ARG_KEY>(key) % m_nHashTableSize;

	if (m_pHashTable == NULL)
		return NULL;

	// see if it exists
	McsAssoc* pAssoc = NULL;
	int nComparisions = 0; 
	for (pAssoc = m_pHashTable[nHash]; pAssoc; pAssoc = pAssoc->pNext, nComparisions++)
	{
		if(fAllowGHT && nComparisions >= MAP_MAX_COMPARISIONS)
		{
			if(((McsMap*)this)->_growHashTableSize())
				return GetAssocAt(key, nHash, true); // recursive

			if(!m_fStripHTOverflowWarning) 
			{
				((McsMap*)this)->m_fStripHTOverflowWarning = true;
				#ifdef _DEBUG
					MCSASSERTE("Increase size of hash table or optimize hash function");
				#else
					MESSAGE_ERR_A("Increase size of hash table or optimize McsHashKey function");
				#endif
			}
		}
		if (McsCompareElements(MCS_GET_OBJ_ADDR(pAssoc->key), &key))//(KEY*)&pAssoc->key, &key))
			return pAssoc;
	}
	return NULL;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::Lookup(ARG_KEY key, VALUE& rValue) const
{
	UINT nHash;
	McsAssoc* pAssoc = GetAssocAt(key, nHash, false);
	if (pAssoc == NULL)
		return false;  // not in map

	rValue = pAssoc->value;
	return true;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const VALUE* McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getExistingValPtr(ARG_KEY key) const
{
	KEY* pStoredKey = NULL;
	VALUE* pStoredVal = NULL;
	
	UINT nHash = 0;
	McsAssoc* pAssoc = NULL;

	if(!(pAssoc = GetAssocAt(key, nHash, false)))
		return NULL;

	//pStoredKey = MCS_GET_OBJ_ADDR(pAssoc->key);
	pStoredVal = MCS_GET_OBJ_ADDR(pAssoc->value);
	return pStoredVal;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE* McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getExistingValPtr(ARG_KEY key)
{
	KEY* pStoredKey = NULL;
	VALUE* pStoredVal = NULL;
	
	UINT nHash = 0;
	McsAssoc* pAssoc = NULL;

	if(!(pAssoc = GetAssocAt(key, nHash, false)))
		return NULL;

	//pStoredKey = MCS_GET_OBJ_ADDR(pAssoc->key);
	pStoredVal = MCS_GET_OBJ_ADDR(pAssoc->value);
	return pStoredVal;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getAt(ARG_KEY key, const KEY*& pStoredKey, VALUE*& pStoredVal)
{
	pStoredKey = NULL;
	pStoredVal = NULL;
	
	UINT nHash = 0;
	McsAssoc* pAssoc = NULL;

	if ((pAssoc = GetAssocAt(key, nHash, true)) == NULL)
	{
		if (m_pHashTable == NULL)
			InitHashTable(m_nHashTableSize);

		// it doesn't exist, add a new Association
		pAssoc = NewAssoc();
		pAssoc->nHashValue = nHash;
		pAssoc->key = key;
		// 'pAssoc->value' is a constructed object, nothing more

		// put into hash table
		pAssoc->pNext = m_pHashTable[nHash];
		m_pHashTable[nHash] = pAssoc;
	}

	pStoredKey = MCS_GET_OBJ_ADDR(pAssoc->key);
	pStoredVal = MCS_GET_OBJ_ADDR(pAssoc->value);
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE& McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](ARG_KEY key)
{
	const KEY* pStoredKey = NULL;
	VALUE* pStoredVal = NULL;
	getAt(key, pStoredKey, pStoredVal);
	return *pStoredVal;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE& McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::valueAt(ARG_KEY key)
{
	const KEY* pStoredKey = NULL;
	VALUE* pStoredVal = NULL;
	getAt(key, pStoredKey, pStoredVal);
	return *pStoredVal;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const KEY& McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::keyAt(ARG_KEY key) const
{
	const KEY* pStoredKey = NULL;
	const VALUE* pStoredVal = NULL;
	getAt(key, pStoredKey, pStoredVal);
	return *pStoredKey;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
int McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getKeys(OUT KeysArray& keys) const
{
	keys.setPhysicalLength(m_nCount);
	keys.SetSize(0);
	const KEY* pKey=NULL;
	MCSPOSITION pos = GetStartPosition();
	while(pos) {
		GetNextKey(pos, pKey);
		keys += *pKey;
	}
	return m_nCount;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
int McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getValues(OUT ValuesArr& vals) const
{
	vals.setPhysicalLength(m_nCount);
	vals.SetSize(0);
	const VALUE* pVal=NULL;
	MCSPOSITION pos = GetStartPosition();
	while(pos) {
		GetNextValue(pos, pVal);
		vals += *pVal;
	}
	return m_nCount;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::RemoveKey(ARG_KEY key)
// remove key - return TRUE if removed
{
	if (m_pHashTable == NULL)
		return FALSE;  // nothing in the table

	McsAssoc** ppAssocPrev;
	ppAssocPrev = &m_pHashTable[McsHashKey<ARG_KEY>(key) % m_nHashTableSize];

	McsAssoc* pAssoc;
	for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (McsCompareElements(MCS_GET_OBJ_ADDR(pAssoc->key), &key))//(KEY*)&pAssoc->key, &key))
		{
			// remove it
			*ppAssocPrev = pAssoc->pNext;  // remove from list
			FreeAssoc(pAssoc);
			return TRUE;
		}
		ppAssocPrev = &pAssoc->pNext;
	}
	return FALSE;  // not found
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextAssoc
(MCSPOSITION& rNextPosition, 
 KEY& rKey, 
 VALUE& rValue) const
{
	const KEY* pk = NULL;
	const VALUE* pv = NULL;
	GetNextAssoc(rNextPosition, pk, pv);
	if(pk || pv)
	{
		rKey = *pk;
		rValue = *pv;
	}
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextAssoc
(MCSPOSITION& rNextPosition, 
 KEY*&        pKey, 
 VALUE*&      pValue)
{
	pKey = NULL;
	pValue = NULL;
	MCSASSERT_EX(m_pHashTable != NULL, return);  // never call on empty map

	McsAssoc* pAssocRet = (McsAssoc*)rNextPosition;
	MCSASSERT_EX(pAssocRet != NULL, return);

	if (pAssocRet == (McsAssoc*) MCS_BEFORE_START_POSITION)
	{
		// find the first association
		for (int nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
				break;
		MCSASSERT_EX(pAssocRet != NULL, return);  // must find something
	}

	// find next association
	//MCSASSERT(McsIsValidAddress(pAssocRet, sizeof(McsAssoc)));
	McsAssoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL)
	{
		// go to next bucket
		for (int nBucket = pAssocRet->nHashValue + 1;
			nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
				break;
	}

	rNextPosition = (MCSPOSITION) pAssocNext;

	// fill in return data
	pKey = MCS_GET_OBJ_ADDR(pAssocRet->key); // (KEY*)&pAssocRet->key;
	pValue = MCS_GET_OBJ_ADDR(pAssocRet->value); // (VALUE*)&pAssocRet->value;
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextKey(MCSPOSITION& rNextPosition, KEY& rKey) const
{
	VALUE Val;
	GetNextAssoc(rNextPosition, rKey, Val);
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextKey(MCSPOSITION& rNextPosition, KEY*& pKey)
{
	VALUE* pVal;
	GetNextAssoc(rNextPosition, pKey, pVal);
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextValue(MCSPOSITION& rNextPosition, VALUE& rVal) const
{
	KEY Key;
	GetNextAssoc(rNextPosition, Key, rVal);
}
//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextValue(MCSPOSITION& rNextPosition, VALUE*& pVal)
{
	KEY* pKey;
	GetNextAssoc(rNextPosition, pKey, pVal);
}
//=============================================================================



///////////////////////////////////////////////////////////////////////////////
//=============================================================================
struct _nulltype
{
	bool operator == (const _nulltype&) {
		MCSASSERTE(FAILED(E_UNEXPECTED));
		return false;
	}

	bool operator != (const _nulltype&) {
		MCSASSERTE(FAILED(E_UNEXPECTED));
		return false;
	}
};

static const _nulltype NULLTYPE;

//=============================================================================

// Ordered Hashset

template<class KEY, class ARG_KEY>
class McsHashset : protected McsMap<KEY, ARG_KEY, _nulltype, const _nulltype&>
{
public:

	DECLARE_OBJ_NEWDEL;

	typedef McsArray<KEY, ARG_KEY> KeysArr;

	McsHashset() { m_fHashSetMode = true; }
	McsHashset(const McsHashset& copyFrom) { m_fHashSetMode = true; *this = copyFrom; }
	McsHashset(const KeysArr& values) { m_fHashSetMode = true; *this = values; }

	int  GetCount() const { return m_nCount; }
	int  GetSize() const { return m_nCount; }
	int  Length() const { return m_nCount; }
	bool IsEmpty() const { return m_nCount == 0; }
	bool isEmpty() const { return m_nCount == 0; }

	McsHashset& operator = (const KeysArr& values) {
		RemoveAll();
		InitHashTable(values.GetSize());
		Add(values);
		return *this;
	}

	McsHashset& operator = (const McsHashset& copyFrom) {
		(McsMap&)(*this) = (const McsMap&)copyFrom;
		return *this;
	}

	bool isExist(ARG_KEY key) const { return McsMap::isExist(key); }
	bool exist(ARG_KEY key) const { return McsMap::isExist(key); }
	bool Exist(ARG_KEY key) const { return McsMap::isExist(key); }
	bool contains(ARG_KEY key) const { return McsMap::isExist(key); }

	const KEY* getExistingKeyPtr(ARG_KEY key) const {
		const KEY* pKey;
		const _nulltype* pVal;
		McsMap::assocAt(key, pKey, pVal);
		return pKey;
	}

	bool Add(ARG_KEY key) 
	{
		int n1 = GetSize();
		McsMap::SetAt(key, NULLTYPE);
		return GetSize() > n1;
	}

	McsHashset& operator |= (ARG_KEY key) { Add(key); return *this; }
	McsHashset& operator += (ARG_KEY key) { Add(key); return *this; }
	McsHashset operator | (ARG_KEY key) const { McsHashset res(*this); res.Add(key); return res; }
	McsHashset operator + (ARG_KEY key) const { McsHashset res(*this); res.Add(key); return res; }

	void Add(const KeysArr& values) {
		for(int i=0; i<values.GetSize(); i++)
			Add(values[i]);
	}

	McsHashset& operator |= (const KeysArr& values) { Add(values); return *this; }
	McsHashset& operator += (const KeysArr& values) { Add(values); return *this; }
	McsHashset operator | (const KeysArr& values) const { McsHashset res(*this); res.Add(values); return res; }
	McsHashset operator + (const KeysArr& values) const { McsHashset res(*this); res.Add(values); return res; }

	void Add(const McsHashset& set)
	{
		MCSPOSITION pos = set.GetStartPosition();
		const KEY* pk = NULL;
		while(pos) {
			set.GetNextKey(pos, pk);
			Add(*pk);
		}
	}

	McsHashset& operator |= (const McsHashset& set) { Add(set); return *this; }
	McsHashset& operator += (const McsHashset& set) { Add(set); return *this; }
	McsHashset operator | (const McsHashset& set) const { McsHashset res(*this); res.Add(set); return res; }
	McsHashset operator + (const McsHashset& set) const { McsHashset res(*this); res.Add(set); return res; }

	bool RemoveKey(ARG_KEY key) { return McsMap::RemoveKey(key); }
	bool Remove(ARG_KEY key) { return McsMap::RemoveKey(key); }
	McsHashset& operator -= (ARG_KEY key) { Remove(key); return *this; }
	McsHashset operator - (ARG_KEY key) const { McsHashset res(*this); res.Remove(key); return res; }

	int Remove(const KeysArr& values)
	{
		int nr = 0;
		for(int i=0; i<values.GetSize(); i++) {
			if(Remove(values[i]))
				nr++;
		}
		return nr;
	}

	int removeSubset(const KeysArr& values) { return Remove(values); }
	McsHashset& operator -= (const KeysArr& values) { Remove(values); return *this; }
	McsHashset operator - (const KeysArr& values) const { McsHashset res(*this); res.Remove(values); return res; }

	int Remove(const McsHashset& set)
	{
		int nr = 0;
		MCSPOSITION pos = set.GetStartPosition();
		const KEY* pK;
		while(pos) {
			set.GetNextKey(pos, pK);
			if(Remove(*pK))
				nr++;
		}
		return nr;
	}

	int removeSubset(const McsHashset& set) { return Remove(set); }
	McsHashset& operator -= (const McsHashset& set) { Remove(set); return *this; }
	McsHashset operator - (const McsHashset& set) const { McsHashset res(*this); res.Remove(set); return res; }

	void RemoveAll() { McsMap::RemoveAll(); }

	bool operator == (const McsHashset& cmpWith) const { return McsMap::operator == ((const McsMap&)cmpWith); }
	bool operator != (const McsHashset& cmpWith)const { return McsMap::operator != ((const McsMap&)cmpWith); }

	// iterating all (key, value) pairs
	MCSPOSITION GetStartPosition() const { return McsMap::GetStartPosition(); }
	void GetNextKey(MCSPOSITION& rNextPosition, KEY& rKey) const { McsMap::GetNextKey(rNextPosition, rKey); }
	void GetNextKey(MCSPOSITION& rNextPosition, KEY*& pKey) { McsMap::GetNextKey(rNextPosition, pKey); }
	void GetNextKey(MCSPOSITION& rNextPosition, const KEY*& pKey) const { McsMap::GetNextKey(rNextPosition, pKey); }

	void getAsArray(OUT KeysArr& arr) const
	{
		arr.RemoveAll();
		if(m_nCount == 0)
			return;

		int i = 0;
		arr.SetSize(m_nCount);

		MCSPOSITION pos = GetStartPosition();
		const KEY* pK = NULL;
		while(pos) {
			GetNextKey(pos, pK);
			arr[i++] = *pK;
		}
	}

	void AsArray(OUT KeysArr& arr) const {
		getAsArray(arr);
	}

		// for compatibility with old maps used as hashsets
		// returns symmetric KEY->KEY map
	void _getAsMap(OUT McsMap<KEY, ARG_KEY, KEY, ARG_KEY>& map) const
	{
		map.RemoveAll();
		MCSPOSITION pos = GetStartPosition();
		const KEY* pK = NULL;
		while(pos) {
			GetNextKey(pos, pK);
			map.SetAt(*pK, *pK);
		}
	}

	// advanced features for derived classes
	int GetHashTableSize() const { return m_nHashTableSize; }

		// flag _fCalledFromGrowHT used for internal purposes (for <_growHashTableSize> method)
	void InitHashTable(UINT_PTR hashSize, bool fAllocNow = true) {
		McsMap::InitHashTable(hashSize, fAllocNow);
	}

	bool contains(const KeysArr& values) const {
		for(int i=0; i<values.GetSize(); i++) {
			if(!contains(values[i]))
				return false;
		}
		return true;
	}

	bool contains(const McsHashset& set) const
	{
		MCSPOSITION pos = set.GetStartPosition();
		const KEY* pK = NULL;
		while(pos) {
			set.GetNextKey(pos, pK);
			if(!contains(*pK))
				return false;
		}
		return true;
	}

	bool containsAnyOf(const KeysArr& values) const {
		for(int i=0; i<values.GetSize(); i++) {
			if(contains(values[i]))
				return true;
		}
		return false;
	}

	bool containsAnyOf(const McsHashset& set) const
	{
		MCSPOSITION pos = set.GetStartPosition();
		const KEY* pK = NULL;
		while(pos) {
			set.GetNextKey(pos, pK);
			if(contains(*pK))
				return true;
		}
		return false;
	}

		// removes elements, which don't exist in values
	void Intersect(const KeysArr& values)
	{
		if(values.isEmpty()) {
			RemoveAll();
			return;
		}

		bool fRemove = false;
		KEY key4remove;
		MCSPOSITION pos = GetStartPosition();
		while(pos)
		{
			if(fRemove) {
				RemoveKey(key4remove);
				fRemove = false;
			}

			KEY* pk = NULL;
			GetNextKey(pos, pk);
			if(values.contains(*pk))
				continue;

			// сразу удал€ть нельз€, не сработает GetNextAssoc, удалим на след шаге или в конце
			key4remove = *pk;
			fRemove = true;
		}
		if(fRemove)
			RemoveKey(key4remove);
	}

	McsHashset& operator &= (const KeysArr& values) { Intersect(values); return *this; }

		// removes elements, which don't exist in values
	void Intersect(const McsHashset& set)
	{
		if(set.isEmpty()) {
			RemoveAll();
			return;
		}

		bool fRemove = false;
		KEY key4remove;
		MCSPOSITION pos = GetStartPosition();
		while(pos)
		{
			if(fRemove) {
				RemoveKey(key4remove);
				fRemove = false;
			}

			KEY* pk = NULL;
			GetNextKey(pos, pk);
			if(set.contains(*pk))
				continue;

			// сразу удал€ть нельз€, не сработает GetNextAssoc, удалим на след шаге или в конце
			key4remove = *pk;
			fRemove = true;
		}
		if(fRemove)
			RemoveKey(key4remove);
	}
	McsHashset& operator &= (const McsHashset& set) { Intersect(set); return *this; }
};
//=============================================================================

struct mcsComplexWorkID;

typedef McsHashset<int, int>               mcsIntSet;
typedef McsHashset<INT_PTR, INT_PTR>       mcsIntptrSet;
typedef McsHashset<__int64, __int64>       mcsI64Set;
typedef McsHashset<DWORD, DWORD>           mcsDwordSet;
typedef McsHashset<DWORD_PTR, DWORD_PTR>   mcsDwordptrSet;
typedef McsHashset<double, double>         mcsDblSet;
typedef McsHashset<void*, void*>           mcsPVoidSet;

typedef McsHashset<McGSMarker, McGSMarker> mcsMcGsMarkerSet;
typedef McsHashset<GUID>                   mcsGUIDSet;
typedef McsHashset<MCSUID, MCSUID>         mcsMCSUIDSet;
typedef McsHashset<mcsWorkID>              mcsWorkIDSet;
typedef McsHashset<mcsComplexWorkID>       mcsComplexWorkIDSet;
typedef McsHashset<McsStringA, LPCSTR>     mcsStringSetA;
typedef McsHashset<McsStringW, LPCWSTR>    mcsStringSetW;

//=============================================================================
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
bool McsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>::getAsHashset(KeysHashset& set) const
{
	set.RemoveAll();
	if(m_nCount==0)
		return false;

	set.InitHashTable(m_nCount, true);

	const KEY* pKey = NULL;
	MCSPOSITION pos = GetStartPosition();
	while(pos) {
		GetNextKey(pos, pKey);
		set |= *pKey;
	}

	return true;
}
//=============================================================================

typedef McsMap <McsStringA, LPCSTR, McsStringA, LPCSTR>     McsMapStringToStringA;
typedef McsMap <McsStringW, LPCWSTR, McsStringW, LPCWSTR>   McsMapStringToStringW;

typedef McsMap <McsStringA, LPCSTR, McsStringA, LPCSTR>     mcsMapStringToStringA;
typedef McsMap <McsStringW, LPCWSTR, McsStringW, LPCWSTR>   mcsMapStringToStringW;

typedef McsMap <int, int, int, int>                         mcsMapInt2Int;
typedef McsMap<McsString, LPCTSTR, int, int>                mcsMapStr2Int;

#ifndef _UNICODE
	#define McsString                                         McsStringA
	typedef McsMap <McsStringA, LPCSTR, McsStringA, LPCSTR>   mcsMapStringToString;
	typedef McsMap <McsStringA, LPCSTR, McsStringA, LPCSTR>   McsMapStringToString;
	typedef McsArray<McsStringA, LPCSTR>                      mcsStringArray;
	typedef McsHashset<McsStringA, LPCSTR>                    mcsStringSet;
#else
	#define McsString                                         McsStringW
	typedef McsMap <McsStringW, LPCWSTR, McsStringW, LPCWSTR> mcsMapStringToString;
	typedef McsMap <McsStringW, LPCWSTR, McsStringW, LPCWSTR> McsMapStringToString;
	typedef McsArray<McsStringW, LPCWSTR>                     mcsStringArray;
	typedef McsHashset<McsStringW, LPCWSTR>                   mcsStringSet;
#endif

//=============================================================================
