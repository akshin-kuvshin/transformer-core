
#pragma once

#include "3DCommon.h"
#include "McsUtils.h"

// Если включен, в данных ключа будет храниться инфа о потоук, в котором была выделена память под ключ
//#define TRACE_RKD_THREAD

// поддержка простых Extrude/Revolve/RectPat/CircPat
#define MCREFKEY_VER_ALPHA1    1

// 18.01.13
#define MCREFKEY_VER_RELEASE1    2

// 04.04.2018, исправлена ошибка формирования тэгов Reuse,Composite,Pattern
#define MCREFKEY_VER_RELEASE2    3

// 26.12.2021, Под C3D исправлена ошибка присвоения тэгов модифицирующих фич
// в postRbiProcessing после операции буления.
// По факту это правка от 31.08.2021, r113160. И версию нужно было поднимать тогда.
#define MCREFKEY_VER_RELEASE3    4

// Получить текущую версию общего генератора ref-ключей.
MCTYP_API int getMcRefKeyCurVer();
#define MCREFKEY_VER_CURRENT getMcRefKeyCurVer()

#define MCREFKEY_PREFIX_LEN 2 // ver:byte seType:byte

struct McFEVRefKeyData;

//==============================================================================

// Структура для хранения данных о наследовании идентификаторов одного тела в другом.
// Используется в булевых фичах.

struct McIdInheritingDataItem
{
	DWORD dwFtrID; // dwID булевой фичи в контексте её непосредственного HostSolid
	int   idx;     // индекс подтела соответствующей булевой фичи, 0 - '1'st item', 1+ - это "индекс + 1" в списке 'otherItems'

	McIdInheritingDataItem() {
		dwFtrID = -1;
		idx = 0;
	}

	McIdInheritingDataItem(DWORD _dw, int _idx) {
		dwFtrID = _dw;
		idx = _idx;
	}

	bool operator == (const McIdInheritingDataItem& cw) const {
		return
			dwFtrID == cw.dwFtrID && 
			idx     == cw.idx;
	}

	bool operator != (const McIdInheritingDataItem& cw) const {
		return
			dwFtrID != cw.dwFtrID ||
			idx     != cw.idx;
	}

};

// следующий тип содержит комплексные данные,
// которые указывают на то, какую часть Face/Edge/Vertex 3D объекта нужно использовать
// при сопоставлении Ref-ключей, или иначе - при поиске Face/Edge/Vertex в теле по ref-ключу.
typedef McsArray<McIdInheritingDataItem> McIdInheritingData;

//==============================================================================
/*

(FEV = Face/Edge/Vertex)

Format:
VerByte SubEntByte 
	// элемент, сформированный указанной фичей, если есть индекс,
	// то история построения элемента неизвестна или не требуется, в этом случае DwID обычно = 0
	FtrIDOpCode DwID [Idx]
		[ OpCode [Oper Params] [OpCode [Oper Params] ...]]

	// элемент с известным происхождением (например, вершина/ребро эскизного профиля)
	ElemIDOpCode DwID
		[ OpCode [Oper Params] [OpCode [Oper Params] ...]]

	// ключ создаётся на этапе оптимизированного создания ключей сразу после генерации
	// фич известных типов (например выдавливание)
	ReuseOpCode RegKeyLen RefKeyBytes
		[ OpCode [Oper Params] [OpCode [Oper Params] ...]]

	// ключ формируется в процессе булевых операций
	Merge RefKey1Len RefKey2Len RefKey1Bytes RefKey2Bytes
		[ OpCode [Oper Params] [OpCode [Oper Params] ...]]

	// ключ формируется в процессе булевых операций
	(Modify|SplitOri|SplitNew)OpCode
		[ OpCode [Oper Params] [OpCode [Oper Params] ...]]

	// ключ формируется в результате работы алгоритма обобщенного присвоения ключей на
	// основе данных о связях между элементами FEV
	Composite RegKeyLen RefKeyBytes ... Composite RegKeyLen RefKeyBytes
		[ OpCode [Oper Params] [OpCode [Oper Params] ...]]

	// код данных, используется для формирования спец. ключей для элементов,
	// чьё происхождение известно заранее
	DataOpCode [DataBytes, 3 max]
		[ OpCode [Oper Params] [OpCode [Oper Params] ...]]

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

Коды операции в ключе McFEVRefKeyData.
Сам по себе ключ - это набор последовательности байтов. В ключе последовательно перечислены
операции, которые производились над FEV-элементом (создание, модификация, склеивание, разделение, ...).
Ключ начинается с байта, который содержит версию и тип McModSubentType. Далее весь ключ делится на 
последовательности записи о фиче, которая породила изменения и перечисление самих этих изменений.
Каждое изменение записано в виде:
OpCode[|args_len_info] Parameters.
Для каждой операции свои параметры и данные.

Обычно первым тэгом в ключе ожидается Dword-идентификатор некоторого объекта, который создал данный элемент.
Если после кода идентификатора следует код merge (слияния) либо код composite (составной ключ),
то это означает, что элемент имеет множественную историю построения.

Код Reuse указывает, что элемент появляется исключительно только благодаря другому, чей ключ указан
сразу после кода операции. Эти коды присваиваются в отдельном порядке для каждой конкретной
3D фичи по-своему.

Код SplitOriginal при добавлении не фиксирует фичу, которая вызывает деление, т.к. 
элемент в этом случае просто теряет часть своей геометрии, остальная же её часть остаётся неизменной.

Составные ключи начинаются с последовательности подключей с префиксами Composite,
после каждого префикс-кода указывается длина подключа и сам подключ, подключи отсортированы
в порядке возрастания. Составные подключи описывают элементы, чьи ключи формируются путём перечисления
ключей присоединённых FEV-элементов определённого типа.

Составные ключи присваиваются многопроходным алгоритмом. на каждом проходе присваиваются
ключи тем элементам, у которых их нет и есть присоединённые элементы с уже присвоенными ключами.
На каждом проходе производится присвоение ключей по следующим направлениям:
E(n-1) > V(n); E(n-1) > F(n); V(n-1) > E(n)
Проходы повторяются до тех пор, пока не будут присвоены ключи всем элементам.

Общая же схема присвоения ключей выглядит так:
1. Первоначальное присвоение ключей через числовые идентификаторы по какому-то правилу
	(к примеру присвоение идентификаторов на элементы Wire-образа эскизного профиля).
2. Выполнение булевых операций над телами и сохранением в присвоенных ключах протокола 
	обработки через операции Modify/Merge/Split с сохранением ID операции.
3. Присвоение ключей Reuse, по некоторому правилу, которое определяется природой 
	проведённой операции. К примеру, при построении выдавливания можно точно сказать, что рёбра,
	образующиеся при движении вершин профиля определяются вершинами и для этих образованных рёбер
	ключ можно сформировать путём повторного использования ключа вершин профиля.
4. Присвоение произвольных составных ключей. Если после проведённых операций остались
	какие-то элементы с неприсвоенными ключами, то для них формируются составные ключи с помощью
	многопроходного алгоритма. Этот тип ключей является самым ненадёжным.

(!)
Максимальное значение DwID = 0xFFFFFF, то есть должно максимум тремя байтами писаться.
Если будет больше, то длину не удастся записать в ключ.
*/

//==============================================================================

enum McModRefKeyOperTypeEnum
{
	kMcRefKeyOp_Unk           = -1,

		// specific feature creates a host of key, index used for feature with code 0,
		// ftr=0 - is alien (imported) body, index is index of vtx, edge, face
	kMcRefKeyOp_FtrID         = (0x0 << 4), // 0x00 // Opcode | (bytes_of_FtrID << 2) | bytes_of_idx

		// tag references to any source geom object which was used to create the host of key
	kMcRefKeyOp_ElemID        = (0x1 << 4), // 0x10 // Opcode | (bytes_for_DwID << 2)

		// tag indicates newly created entity (host of key) which was born from another
		// entity with key on the left side of sequence before this tag
	kMcRefKeyOp_Reuse         = (0x2 << 4), // 0x20 // Opcode | (bytes_of_srouce_key << 2) | srcSubentType, srcKey_len, srcKey_data

		// entity was modified by modeler
	kMcRefKeyOp_Modify        = (0x3 << 4), // 0x30 // Opcode 

		// entity was split and remain live
	kMcRefKeyOp_SplitOriginal = (0x4 << 4), // 0x40 // Opcode 

		// entity was born by split of another entity
	kMcRefKeyOp_SplitNew      = (0x5 << 4), // 0x50 // Opcode 

		// entity was merged from entities with keys kept by this tag
	kMcRefKeyOp_Merge         = (0x6 << 4), // 0x60 // Opcode | (bytes_of_1st_RefKey_len << 2) | bytes_of_2nd_RefKey_len, key1_len, key2_len, refKey1_data, refKey2_data

		// entity was created by composing brep-neighbor entities with keys kept by this tag
	kMcRefKeyOp_Composite     = (0x7 << 4), // 0x70 // Opcode | (bytes_of_RefKey_len << 2) | srcSubentType, subRefKey_len, subRefKey_data

		// any specific data, typically used during primary key assignment during feature creation
	kMcRefKeyOp_Data          = (0x8 << 4), // 0x80 // Opcode | (bytes_of_data << 2) | two_optinal_data_bits [, data_bytes]

		// tag indicates than host entity was created by pattern operation,
		// index of item in pattern is in data of this tag
	kMcRefKeyOp_PatternItem   = (0x9 << 4), // 0x90 // Opcode | (bytes_of_RefKey_len << 2) | bytes_of_pattern_idx, seedRefKey_len, seedRefKey_data, idxPattern

		// feature code, which modifies host entity in any way (13.09.13)
	kMcRefKeyOp_ModFtrID      = (0xA << 4), // 0xA0 // Opcode | (bytes_of_ModFtrID << 2) | bytes_of_idx
};

//==============================================================================

#define kMcRefKey_OpCodeMask  0xF0
#define kMcRefKey_IndicesMask 0x0F

#define MCMOD_REFKEY_IDX_HI(opcode) (((opcode)>>2)&3)
#define MCMOD_REFKEY_IDX_LOW(opcode) ((opcode)&3)
#define MCMOD_REFKEY_IDX(opcode)     ((opcode)&3)

#define MCMOD_REFKEY_PACK_INDICES(idxHi, idxLow)  ( (((idxHi)&3)<<2) | ((idxLow)&3) )
#define MCMOD_REFKEY_PACK_IDX(idx)                ( ((idx)&3) )

extern MT_API int g_McFEVRefKeyDataVer;

//==============================================================================
enum McRefKeyEntranceStatusEnum
{
	kMcRefKeyEntrance_Undef    = 0, // вхождение ключа не определено
	kMcRefKeyEntrance_Exact    = 1, // точное совпадение
	kMcRefKeyEntrance_Modified = 2, // точное совпадение в начале с дополнительным изменением
	kMcRefKeyEntrance_Split    = 3, // ключ совпадает, но после элемент был разделён
};
//==============================================================================

struct _McFEVRefSubKeyData;
typedef McsArray<_McFEVRefSubKeyData, const _McFEVRefSubKeyData&> _McFEVRefSubKeysDataArr;
typedef McsMap<int, int, _McFEVRefSubKeysDataArr, const _McFEVRefSubKeysDataArr& > mapInt2SubKeysDataArr;

//==============================================================================
struct _McFEVRefSubKeyData
{
	McModSubentType seType; // F/E/V

	int idxPos;          // абсолютное смещение начала данных поключа
	int len;             // длина подключа
	int idxParentTagPos; // абсолютное смещение начала родительского тэга в ключе
	int parentTagLen;    // общая длина родительского тэга

		// если структуры лежат в массиве, то это индекс родительского подключа в массиве
	int idxParentSubKey;

		// используется для формирования soft-ключа, хранит кол-во байт, которое надо
		// выбросить для всх soft-тэгов
	int nBytesToDrop;

	McModRefKeyOperTypeEnum parentTagType;

	_McFEVRefSubKeyData() {
		clear();
	}

	void clear()
	{
		seType = kMcModSubentType_Null;
		idxPos = -1;
		len = 0;
		idxParentTagPos = -1;
		parentTagLen = 0;
		idxParentSubKey = -1;
		nBytesToDrop = 0;
		parentTagType = kMcRefKeyOp_Unk;
	}

	MT_API void initByRefKey(const McFEVRefKeyData& rk);

	MT_API McRefKeyEntranceStatusEnum getInexactMatchStatus(
		IN const McFEVRefKeyData&              HostThisRefKey,
		IN const McFEVRefKeyData&              HostOtherRefKey,
		IN const _McFEVRefSubKeyData&          otherSK,
		IN OUT OPTIONAL mapInt2SubKeysDataArr* pElementarySubkeysForThisRK = NULL,
		IN OPTIONAL const McIdInheritingData*  pIdInhData = NULL) const;

		// Выдаёт список всех простых подключей, которые имеются в данном,
		// Простые ключи - это ключи, в которых нет ни одного тэга merge или composite.
		// Подключи с тэгом merge выбрасываются, вместо них выдаются составляемые
		// простые подключи; ключи с тэгами composite тоже не выдаются, но на выходе
		// составляющие их подключи не разбиваются, независимо от их содержимого.
		// Если указать в expectedSubKeyTags тип merge, то если в данном ключе встретится
		// composite-подключи, то ничего не вернётся; и наоборот, если указть composite,
		// в встретится merge, то тоже ничего не вернётся. Это можно использовать для
		// оптимизации запросов
	MT_API bool _getElementarySubKeys(
		IN const McFEVRefKeyData&           HostRefKey,
		IN OUT _McFEVRefSubKeysDataArr&     elSubKeys,
		IN OPTIONAL McModRefKeyOperTypeEnum expectedSubKeyTags = kMcRefKeyOp_Unk) const;
};
//==============================================================================

struct _McFEVRefKeyBindData
{
	McRefKeyEntranceStatusEnum bindStatus;
	int     keyLen;
	void*   pModelerEnt;
	int     idxEnt;
	//............................................................................
	_McFEVRefKeyBindData() {
		bindStatus = kMcRefKeyEntrance_Undef;
		keyLen = 0;
		pModelerEnt = NULL;
		idxEnt = -1;
	}
	//............................................................................
	bool operator == (const _McFEVRefKeyBindData& cw) const {
		if(bindStatus != cw.bindStatus)
			return false;
		if(keyLen != cw.keyLen)
			return false;
		return true;
	}
	//............................................................................
	bool operator != (const _McFEVRefKeyBindData& cw) const {
		return ! operator== (cw);
	}
	//............................................................................
	bool operator > (const _McFEVRefKeyBindData& cw) const
	{
		if(bindStatus <= cw.bindStatus)
			return false;
		if(bindStatus > cw.bindStatus)
			return true;
		if(keyLen <= cw.keyLen)
			return false;
		return true;
	}
	//............................................................................
	bool operator < (const _McFEVRefKeyBindData& cw) const
	{
		if(bindStatus >= cw.bindStatus)
			return false;
		if(bindStatus < cw.bindStatus)
			return true;
		if(keyLen >= cw.keyLen)
			return false;
		return true;
	}
};

typedef McsArray<_McFEVRefKeyBindData> _McFEVRefKeyBindDataArr;
//==============================================================================

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)

struct _RKD;
typedef McsHashset<_RKD*> _RKDPtrsSet;
extern MT_API _RKDPtrsSet gRkdPtrsSet;

MT_API void getAllocMemForRkd(OUT DWORD& dwMemNonOpt, DWORD& dwMemOpt, DWORD& nKeys);

#define DECL_RK_PROPERTY(class,name) class m_##name; _declspec(property(get = get_##name, put = set_##name)) class name

//==============================================================================

struct _RKDPtr;

struct _RKD
{
	volatile WORD mnRefCount; // max 65535

	mutable UINT mHash;

	int   miInCache:1;
	int   mDataLen:31;

	byte* mpData;

#ifdef TRACE_RKD_THREAD
	DWORD mHostTID;
#endif

	_RKD();
	~_RKD();
	bool operator == (const _RKD&) const;
};

//==============================================================================
struct _RKDPtr
{
	_RKD* p;

	MT_API _RKDPtr();
	MT_API _RKDPtr(const _RKDPtr& copyFrom);
	MT_API _RKDPtr(_RKD* pRKD);
	MT_API ~_RKDPtr();

	MT_API _RKDPtr& operator = (const _RKDPtr& copyFrom);
	MT_API _RKDPtr& operator = (_RKD* copyFrom);

	MT_API const _RKD* operator ->() const;
	MT_API _RKD* operator ->();

	_RKD& operator *() {
		return *p;
	}

	const _RKD& operator *() const {
		return *p;
	}

	MT_API bool operator == (const _RKDPtr& cmpWith) const;
	MT_API bool operator == (const _RKD* cmpWith) const;
	MT_API bool operator != (const _RKDPtr& cmpWith) const;
	MT_API bool operator != (const _RKD* cmpWith) const;

	MT_API void addRef();
	MT_API void release();
};

//==============================================================================

// В файл не пишется
enum RkTypeEnum
{
	kRkType_Unknown          = 0x66, // значение отличное от 0 и мусора в Debug-режиме
	kRkType_McFEVRefKeyData,
	kRkType_McFEVRefKey_T,
	kRkType_Mc3dModFEVRefKey,
};
//==============================================================================

typedef void (*McFEVRefKeyData_dtorProc)(McFEVRefKeyData*);

struct McSpaFEVRefKey;
struct McC3dFEVRefKey;
//==============================================================================

struct McFEVRefKeyData
{
protected:
	_RKDPtr mpRKD;
	byte    mType; // RkTypeEnum

	MT_API static McFEVRefKeyData_dtorProc s_RKT_dtor;
	MT_API static McFEVRefKeyData_dtorProc s_RKM_dtor;

protected:
	struct FtrTagData
	{
		DWORD dwID;
		int   offset;
		int   len;

		FtrTagData() {
			dwID = 0;
			offset = 0;
			len = 0;
		}
	};

protected:
	McFEVRefKeyData(_RKD* pRKD);
	static void _sDtor(McFEVRefKeyData*);

	MT_API void _commonDtor(RkTypeEnum stopAtType);

public:
	MT_API McFEVRefKeyData();
	MT_API McFEVRefKeyData(const McFEVRefKeyData& cf);
	MT_API McFEVRefKeyData(const byte* pData, int len);

	MT_API //virtual // на каждый ключ съедает sizeof(DWORD_PTR), заменили на поле mType, размер 1 байт
		~McFEVRefKeyData();

	MT_API void* cast(RkTypeEnum typeTo);

	const void* cast(RkTypeEnum typeTo) const {
		return ((McFEVRefKeyData*)this)->cast(typeTo);
	}

	RkTypeEnum type() const {
		if(!this)
			return kRkType_Unknown;
		return (RkTypeEnum)mType;
	}

	MT_API const byte* dataPtr() const;
	MT_API int         dataLen() const;
	MT_API UINT        hash() const;
	MT_API void        resetHash() const;

	MT_API DWORD size() const;

	MT_API bool isInCache() const;
	MT_API bool addToCache() const;
	MT_API bool removeFromCache() const;
	MT_API void copyOnWrite();

	MT_API bool check(bool bSilent) const;

	MT_API McFEVRefKeyData& operator = (const McFEVRefKeyData& cf);

	MT_API int  compare (const McFEVRefKeyData& cw, bool bForEquality) const;
	MT_API bool operator == (const McFEVRefKeyData& cw) const;
	MT_API bool operator != (const McFEVRefKeyData& cw) const;

	MT_API bool operator < (const McFEVRefKeyData& cw) const;
	MT_API bool operator > (const McFEVRefKeyData& cw) const;

	MT_API bool isNull() const;
	MT_API void setNull();

		// выдаёт тип тэга (opcode only) в указанной позиции,
		// вернёт kMcRefKeyOp_Unk, если ошибка
	MT_API McModRefKeyOperTypeEnum getTagTypeAtPos(int idxTagPos) const;
	MT_API McModSubentType         subEntType() const;
	MT_API int                     version() const;

		// возвращает длину тэга в указанной позиции,
		// вернёт 0, если ошибка
	MT_API int   getTagLenAtPos(int idxTagPos, OUT OPTIONAL bool* pbErr = NULL) const;

		// выдаёт код фичи в указанной позиции,
		// вернёт -1, если ошибка
	MT_API DWORD getDwIDAtPos(int idxTagPos, OUT OPTIONAL int* pIdx2 = NULL) const;

	MT_API bool  getDataAtPos(int idxTagPos, OUT DWORD& data) const;

		// Возвращает индекс элемента массива для тэга pattern в указанной позиции
	MT_API bool  getPatternIdxAtPos(int idxTagPos, OUT int& idxPatternItem) const;

	// выдаёт код фичи, к которой относится ключ,
	// вернёт -1, если ошибка
	//
	// Описание аргумента pIdInheritingData см. в методе getFtrIDEx.
	//
	MT_API DWORD getFtrID(IN OPTIONAL const McIdInheritingData* pIdInheritingData) const;

		// выдаёт код элемента, к которому относится ключ,
		// вернёт -1, если ошибка
	MT_API DWORD getElemID() const;

	// выдаёт код фичи, к которой относится ключ,
	// idxFtrIDPos - индекс позиции, в которой обнаружен код,
	// iAtStartTagLocation > 0: тэг в начале ключа
	// iAtStartTagLocation == 0: тэг в середине ключа
	// iAtStartTagLocation < 0: тэг в конце ключа
	//
	// В аргументе pIdInheritingData передается информация о включении одного тела в другое.
	// Код фичи будет возвращен только если после него есть информация о включении в другое тело,
	// аналогичная указанной в аргументе 'pIdInheritingData'.
	// NOTE: Данные pIdInheritingData нужно указывать при поиске FEV по ключу в модели.
	// В операциях получения информации из ключа эти данные не нужны, и надо передавать NULL.
	//
	MT_API DWORD getFtrIDEx(
		OUT int&                              idxFtrIDPos,
		OUT int&                              iAtStartTagLocation,
		IN OPTIONAL const McIdInheritingData* pIdInheritingData) const;

	// выдаёт коды фич, к которым относится ключ,
	// сканирование списка выполняется без учета вложенности подключей, только линейный поиск.
		// ftrIds - список фич в порядке от начала к концу
		// ftrsIndices - соответствующие индексы для фич списка ftrIds
	MT_API void getRawFtrsIDEx(OUT mcsDwordArray& ftrIds, OUT mcsIntArray& ftrsIndices) const;

		// выдаёт параметры подключей в указнной позиции, если они там есть;
		// вернёт кол-во полученных подключей - 0/1/2
	MT_API int getOpSubKeysInfoAtPos(
		int idxTagPos,
		OUT _McFEVRefSubKeyData& subKey1,
		OUT _McFEVRefSubKeyData& subKey2) const;

		// выдаёт список всех фич, участвовавших в образовании ключа.
		// В случае сбоя отдаёт, что удалось вычитать, но кода ошибки не будет.
		// pInclOthrPartFtrIDs - если указан,
		//   то в нём должны быть указаны ID фич, включающих другие тела;
		//   и на выходе в dwIDs выбрасываются  все ID, относящиеся к другим телам
	MT_API bool  getDwIDsList(
		OUT OPTIONAL mcsDwordSetEx&       dwIDs,              // (*(mcsDwordSetEx*)NULL)
		IN OPTIONAL  const mcsDwordSetEx* pInclOthrPartFtrIDs // NULL
	) const;

		// выдаёт список всех фич, участвовавших в образовании ключа.
		// В случае сбоя отдаёт, что удалось вычитать, но кода ошибки не будет.
		// pInclOthrPartFtrIDs - если указан,
		//   то в нём должны быть указаны ID фич, включающих другие тела;
		//   и на выходе в dwIDs выбрасываются  все ID, относящиеся к другим телам
	MT_API bool  getDwIDsList2(
		OUT OPTIONAL mcsDwordSetEx&       dwIDsCreating,  // (*(mcsDwordSetEx*)NULL), только создающие фичи
		OUT OPTIONAL mcsDwordSetEx&       dwIDsModifying, // (*(mcsDwordSetEx*)NULL), только модифицирующие фичи
		IN OPTIONAL  const mcsDwordSetEx* pInclOthrPartFtrIDs // NULL
	) const;

	MT_API McsString formatKeyBytes() const;

		// Выдаёт индекс элемента массива, к которому относится этот ключ
		// Возвращает -1, если ошибка, или этот ключ не относится к элементу массива.
		// >=0 - raw - индекс элемента. 0 - это именно первый построенный элемент массива,
		// а не исходный материал для клонирования, исходный материал к массивам не относится.
	MT_API int getPatternIndex() const;

		// Определяет тип вхождения указанного ключа в данный.
		// Если fCheckEquOnly = true, то требуется точно совпадение.
		// Если указать параметр pElementarySubkeysCacheForThisRK, то для неточного режима
		// можно сократить время сопоставления. Набор по указателю pElementarySubkeysForThisRK
		// можно получить методом this->_getElementarySubKeys. Если указать пустой объект,
		// то он заполнится автоматически внутри метода. Параметр желательно
		// указывать в случае конвейерных сопоставлений одного и того же ключа с некоторым
		// множеством других ключей.
	MT_API McRefKeyEntranceStatusEnum checkKeyEntranceStatus(
		IN const McFEVRefKeyData&              refKeyData,
		IN bool                                fCheckEquOnly,
		IN OUT OPTIONAL mapInt2SubKeysDataArr* pElementarySubkeysCacheForThisRK = NULL,
		IN OPTIONAL const McIdInheritingData*  pIdInhData = NULL) const;

		// Определяет тип неточного вхождения указанного ключа в данный.
		// См. комментарий про параметр pElementarySubkeysCacheForThisRK в комментарии к методу
		// checkKeyEntranceStatus
	MT_API McRefKeyEntranceStatusEnum checkKeyInexactEntranceStatus(
		IN const McFEVRefKeyData&              refKeyData,
		IN OUT OPTIONAL mapInt2SubKeysDataArr* pElementarySubkeysCacheForThisRK = NULL,
		IN OPTIONAL const McIdInheritingData*  pIdInhData = NULL) const;

		// Служебный метод. Зовётся из checkKeyEntranceStatus
	MT_API McRefKeyEntranceStatusEnum _checkSubKeyTailEntranceStatus(
		IN int                                iOfsInSubKey,
		IN const _McFEVRefSubKeyData&         subKey,
		IN OPTIONAL const byte*               pKeyData = NULL,
		IN OPTIONAL const McIdInheritingData* pIdInhData = NULL,
		OUT OPTIONAL int*                     piIdInhDataFound = NULL) const;

		// Если в ключе есть тэги, которые не влияют на нежесткое сопоставление ключей,
		// то результат true и в softRK будут данные для облегченного ключа.
		// Пример. Ключ: Ftr, Reuse, Mod, Split, Data
		// Результат: Ключ: Ftr, Reuse, Data.
		// Смысл: из ключа выбрасываются тэги, которые деформируют объект, но при этом
		// он продолжает существовать. Soft ключ как раз и нужен чтобы получить
		// существующий объект в любом модифицированном состоянии
	MT_API bool getRefKeyForSoftMatch(
		OUT McFEVRefKeyData& softRK,
		IN OPTIONAL DWORD    dwOnlyAfterSpecificFtr = -1) const;

		// Форматирует данные ключа в текстовой форме, удобной для визуального анализа,
		// Для отладочных целей
	MT_API McsString translateToText(LPCTSTR szLeftSpace = _T("")) const;

		// выдаёт ключ для данных подключа, данные копируются из основного ключа;
		// idxPosParentTag - позиция в родительском ключе для тэга, содержащего подключ
		// idxPosSubKeyData - обсолютное положение данных подключа в родительском ключе
		// len - длина данных подключа
	MT_API bool getSubKey(
		OUT McFEVRefKeyData& subKey,
		IN int               idxPosParentTag,
		IN int               idxPosSubKeyData,
		IN int               len) const;

		// упаковывает два данных подключа в тэг merge по адресу pDest;
		// возвращает кол-во записаннх байт;
		// вызывающая сторона отвечает за достаточный размер буфера;
		// если pDest == NULL, то функция вычисляет кол-во байт в буфере, необходимое для
		// записи тэга с подключами, pSubKeyData1 и pSubKeyData2 в этом случае не используются;
		// метод использует memmove, поэтому безопасно давать перекрывающиеся адреса
	MT_API static int _sPackSubkeysByMerge(
		OUT byte*      pDest,
		IN int         lenSubKey1,
		IN int         lenSubKey2,
		IN const byte* pSubKeyData1,
		IN const byte* pSubKeyData2);

		// упаковывает данный подключ в тэг composite по адресу pDest;
		// возвращает кол-во записаннх байт;
		// вызывающая сторона отвечает за достаточный размер буфера;
		// если pDest == NULL, то функция вычисляет кол-во байт в буфере, необходимое для
		// записи тэга с подключом, pSubKeyData в этом случае не используются;
		// метод использует memmove, поэтому безопасно давать перекрывающиеся адреса
	MT_API static int _sPackSubkeyByComposite(
		OUT byte*      pDest,
		IN int         subentType,
		IN int         lenSubKey,
		IN const byte* pSubKeyData);

		// Инициализирует ключ указанными данными. Если указать fCopyData = true,
		// то данные скопируются, если false, то указанный буфер будет установлен в
		// качестве буфера данных ключа. Буфер должен быть выделен через mcsMemAlloc.
	MT_API void setData(const byte* pData, int len, bool fCopyData = true);

	MT_API HRESULT write(IMtStream* pS) const;
	MT_API HRESULT read(IMtStream* pS);

protected:
	MT_API void _setData(const byte* pData, int len, bool fCopyData, bool bCopyOnWrite);

		// аргументы не проверяются
	MT_API bool _readLenNum(int idxPos, OUT int& num, int nBytes) const;
	MT_API int  _getSubKeysCount4Op(byte opCode) const;

		// возвращает кол-во байт, необходимое для записи поля данной длины
	MT_API static int _sGetBytesLen(int num);

		// записывает по указанному адресу значение num в кол-ве байт
		// nBytes (его получать из _sGetBytesLen);
		// вызывающая сторона отвечает за достаточный размер буфера
	MT_API static void _sWriteLenNum(
		OUT byte* pDest, int num, int nBytes);

	friend class CMc3dRefKeysCache;
};

#pragma pack(pop)

typedef McsArray<const McFEVRefKeyData*, const McFEVRefKeyData*> McFEVRefKeyDataPtrsArray;
typedef McsArray<McFEVRefKeyData> McFEVRefKeyDataArray;

//==============================================================================
template <> __inline UINT __stdcall McsHashKey <const McFEVRefKeyData&> (const McFEVRefKeyData& rkd)
{
	return rkd.hash();
}
//==============================================================================

struct IMc3dRefKeysCache
{
	virtual bool add(const McFEVRefKeyData& rk) = 0;
	virtual bool remove(const McFEVRefKeyData& rk) = 0;
	virtual bool isInCache(IN const McFEVRefKeyData& rk) const = 0;
};

extern MT_API IMc3dRefKeysCache* gp3dRefKeysCache;
