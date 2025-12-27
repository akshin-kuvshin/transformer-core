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

#pragma once

template <> __inline UINT __stdcall McsHashKey <const McFEVRefKey&> (const McFEVRefKey&);

//==============================================================================
// (!) Не менять, пишется в стрим
enum McSubentTypeEnum
{
	kMcSubent_Null         = 0,  // = AcDb:kNullSubentType
	kMcSubent_FEV          = 3,  // Face/Edge/Vertex, used in MAPI3D
	kMcSubent_Face         = 10, // = AcDb::kFaceSubentType
	kMcSubent_Edge         = 11, // = AcDb::kEdgeSubentType
	kMcSubent_Vertex       = 12, // = AcDb::kVertexSubentType
	kMcSubent_MlineSeCache = 13, // = AcDb::kMlineSubentCache
	kMcSubent_Class        = 14, // = AcDb::kClassSubentType
};
//==================================================================================================

// данные, однозначно идентифицирующие Subentity в контексте родительского объекта
struct McSubentIdData
{
	McSubentTypeEnum mSeType;
	McGSMarker       miGSMarker;
	McFEVRefKey*     mpFEVRefKey;

	DECLARE_OBJ_NEWDEL;

	//............................................................................
	MT_API McSubentIdData();
	MT_API McSubentIdData(const McSubentIdData& cf);
	MT_API McSubentIdData(McGSMarker _iGSMarker, McSubentTypeEnum _eType);
	MT_API McSubentIdData(const McFEVRefKey& RefKey);
	//MT_API McSubentIdData(const byte* pRKData, int RKLen);

	MT_API ~McSubentIdData();

	MT_API void setNull();
	MT_API bool isNull() const;

	MT_API void setRefKey(const McFEVRefKeyData&);

	MT_API McSubentIdData& operator = (const McSubentIdData& cf);
	MT_API bool operator == (const McSubentIdData& cw) const;

	bool operator != (const McSubentIdData& cw) const {
		return !operator == (cw);
	}

	MT_API HRESULT write(IMtStream*) const;
	MT_API HRESULT read(IMtStream*);
};
//==================================================================================================

template <> __inline UINT __stdcall McsHashKey <const McSubentIdData&> (const McSubentIdData& seIDData)
{
	UINT hash = 0;
	if(seIDData.mSeType != kMcSubent_FEV) {
		hash = McsHashKey(seIDData.miGSMarker);
	} else if (seIDData.mpFEVRefKey) {
		hash = McsHashKey<const McFEVRefKey&>(*seIDData.mpFEVRefKey);
	}
	return hash;
}
//==================================================================================================

// составной идентификатор Subentity.
// Через IMcSubentIdentification динамически отображается на mcsWorkID, который можно
// безопасно сохранять/читать в стримах версии v10+
struct McSubentId
{
	mcsWorkID      mIdParent;
	McSubentIdData mSubentIdData;

	MT_API McSubentId();
	MT_API McSubentId(const mcsWorkID& idParent, McGSMarker gsMarker, McSubentTypeEnum seType);
	MT_API McSubentId(const mcsWorkID& idParent, const McFEVRefKey& RK);
	//MT_API McSubentId(const mcsWorkID& idParent, const byte* pRKData, int RKLen);
	MT_API McSubentId(const mcsWorkID& idParent, const McSubentIdData& seData);
	MT_API McSubentId(const McSubentId& cf);

	MT_API McSubentId& operator = (const McSubentId& cf);
	MT_API bool operator == (const McSubentId& cw) const;

	bool operator != (const McSubentId& cw) const {
		return !operator == (cw);
	}

	McSubentTypeEnum subentType() const {
		return mSubentIdData.mSeType;
	}

	MT_API bool isNull() const;
	MT_API void setNull();
};
//==================================================================================================

template <> __inline UINT __stdcall McsHashKey <const McSubentId&> (const McSubentId& seID)
{
	UINT hash = McsHashKey<const mcsWorkID&>(seID.mIdParent);
	UINT hash2 = McsHashKey<const McSubentIdData&>(seID.mSubentIdData);
	hash ^= hash2;
	return hash;
}
//==================================================================================================
