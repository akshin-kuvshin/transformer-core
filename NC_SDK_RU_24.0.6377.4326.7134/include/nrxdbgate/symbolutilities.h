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

#ifndef __OPENDWG_SYMBOLUTILITIES_H__
#define __OPENDWG_SYMBOLUTILITIES_H__
#include "nrxdbgate_impexp.h"


namespace NcDbSymbolUtilities
{

	enum CompatibilityMode
	{
		kExtendedNames    = true,
		kPreExtendedNames = false
	};

	enum NameCaseMode
	{
		kPreserveCase = true,
		kForceToUpper = false
	};

	enum NewNameMode
	{
		kAsNewName      = true,
		kAsExistingName = false
	};

	enum VerticalBarMode
	{
		kallow_bar     = true,
		kNoVerticalBar = false
	};

	class Services
	{
	public:
		enum { kCurrentVersion = 106 };
		virtual int version() const;

	public:
		virtual bool isBlockLayoutName(const NCHAR* name) const;
		virtual bool isBlockModelSpaceName(const NCHAR* name) const;
		virtual bool isBlockPaperSpaceName(const NCHAR* name) const;
		virtual bool isLayerDefpointsName(const NCHAR* name) const;
		virtual bool isLayerZeroName(const NCHAR* name) const;
		virtual bool isLinetypeByBlockName(const NCHAR* name) const;
		virtual bool isLinetypeByLayerName(const NCHAR* name) const;
		virtual bool isLinetypeContinuousName(const NCHAR* name) const;
		virtual bool isRegAppNcadName(const NCHAR* name) const;
		virtual bool isTextStyleStandardName(const NCHAR* name) const;
		virtual bool isViewportActiveName(const NCHAR* name) const;

		virtual NcDbObjectId blockModelSpaceId(NcDbDatabase* database) const;
		virtual NcDbObjectId blockPaperSpaceId(NcDbDatabase* database) const;
		virtual NcDbObjectId layerDefpointsId(NcDbDatabase* database) const;
		virtual NcDbObjectId layerZeroId(NcDbDatabase* database) const;
		virtual NcDbObjectId linetypeByBlockId(NcDbDatabase* database) const;
		virtual NcDbObjectId linetypeByLayerId(NcDbDatabase* database) const;
		virtual NcDbObjectId linetypeContinuousId(NcDbDatabase* database) const;
		virtual NcDbObjectId regAppNcadId(NcDbDatabase* database) const;
		virtual NcDbObjectId textStyleStandardId(NcDbDatabase* database) const;

		virtual const NCHAR* blockModelSpaceName() const;
		virtual const NCHAR* blockPaperSpaceName() const;
		virtual const NCHAR* layerDefpointsName() const;
		virtual const NCHAR* layerZeroName() const;
		virtual const NCHAR* linetypeByBlockName() const;
		virtual const NCHAR* linetypeByLayerName() const;
		virtual const NCHAR* linetypeContinuousName() const;
		virtual const NCHAR *regAppNcadName() const;
		virtual const NCHAR* textStyleStandardName() const;
		virtual const NCHAR* viewportActiveName() const;

	public:
		virtual int compareSymbolName(const NCHAR* name1, const NCHAR* name2) const;
		virtual bool hasVerticalBar(const NCHAR* name) const;
		virtual Nano::ErrorStatus makeDependentName(NCHAR*& new_name, const NCHAR* dwg_name,
		                                            const NCHAR* symbol_name) const;
		virtual Nano::ErrorStatus repairPreExtendedSymbolName(NCHAR*& new_name, const NCHAR* old_name,
		                                                      bool allow_bar) const;
		virtual Nano::ErrorStatus repairSymbolName(NCHAR*& new_name, const NCHAR* old_name, bool allow_bar) const;
		virtual bool splitDependentName(size_t& numLeftBytes, const NCHAR*& pRight, const NCHAR* symbol_name) const;
		virtual Nano::ErrorStatus validatePreExtendedSymbolName(const NCHAR* name, bool allow_bar) const;
		virtual Nano::ErrorStatus validateSymbolName(const NCHAR* name, bool allow_bar) const;

	public:
		virtual bool compatibilityMode(NcDbDatabase* database) const;
		virtual Nano::ErrorStatus getBlockNameFromInsertPathName(NCHAR*& block_name, const NCHAR* path_name) const;
		virtual Nano::ErrorStatus getInsertPathNameFromBlockName(NCHAR*& path, const NCHAR* block_name) const;
		virtual bool getMaxSymbolNameLength(size_t& maxLength, size_t& max_size, bool isnew,
		                                    bool compatibilityMode) const;
		virtual Nano::ErrorStatus getPathNameFromSymbolName(NCHAR*& path, const NCHAR* symbol_name,
		                                                    const NCHAR* extensions) const;
		virtual Nano::ErrorStatus getSymbolNameFromPathName(NCHAR*& symbol_name, const NCHAR* path_name,
		                                                    const NCHAR* extensions) const;
		virtual Nano::ErrorStatus preValidateSymbolName(NCHAR*& symbol_name, bool preserve_case) const;
		virtual Nano::ErrorStatus validateCompatibleSymbolName(const NCHAR* name, bool isnew, bool allow_bar,
		                                                       bool compatibilityMode) const;
	};

	NRXDBGATE_EXPORT Nano::ErrorStatus getSymbolName(NCHAR*& name, NcDbObjectId id);

#define DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(_Table) \
	inline Nano::ErrorStatus \
	get##_Table##Id(NcDbObjectId& id, const NCHAR* name, NcDbDatabase* database) \
	{ \
		_ASSERT(name && *name != _T('\0')); \
		_ASSERT(database); \
		NcDb##_Table##Table* table = NULL; \
		Nano::ErrorStatus es; \
		if ((es = database->getSymbolTable(table, NcDb::kForRead)) == Nano::eOk) \
		{ \
			es = table->getAt(name, id); \
			table->close(); \
		} \
		return es; \
	}
	DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(Block)
	DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(DimStyle)
	DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(Layer)
	DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(Linetype)
	DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(RegApp)

	NRXDBGATE_EXPORT Nano::ErrorStatus getTextStyleId(NcDbObjectId& id, const NCHAR* name, NcDbDatabase* database);

	DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(UCS)
	DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(View)
	#undef DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION

#define DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(_Table) \
	inline bool has##_Table(NcDbObjectId id, NcDbDatabase* database) \
	{ \
		_ASSERT(!id.isNull()); \
		_ASSERT(database); \
		bool found = false; \
		NcDb##_Table##Table* table = NULL; \
		Nano::ErrorStatus es; \
		if ((es = database->getSymbolTable(table, NcDb::kForRead)) == Nano::eOk) \
		{ \
			found = table->has(id); \
			table->close(); \
		} \
		return found; \
	}

	DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Block)
	DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(DimStyle)
	DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Layer)
	DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Linetype)
	DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(RegApp)
	DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(TextStyle)
	DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(UCS)
	DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(View)
	DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Viewport)
	#undef DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION

#define DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(_Table) \
	inline bool has##_Table(const NCHAR* name, NcDbDatabase* database) \
	{ \
		_ASSERT(name && *name != _T('\0')); \
		_ASSERT(database); \
		bool found = false; \
		NcDb##_Table##Table* table = NULL; \
		Nano::ErrorStatus es; \
		if ((es = database->getSymbolTable(table, NcDb::kForRead)) == Nano::eOk) \
		{ \
			found = table->has(name); \
			table->close(); \
		} \
		return found; \
	}
	DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Block)
	DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(DimStyle)
	DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Layer)
	DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Linetype)
	DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(RegApp)
	DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(TextStyle)
	DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(UCS)
	DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(View)
	DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Viewport)
	#undef DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION

} // end NcDbSymboUtilities

namespace NcDbSymUtil = NcDbSymbolUtilities;

typedef NcDbSymbolUtilities::Services  NcDbSymUtilServices;

/*
Get pointer to class NcDbSymbolUtilities::Services
Return value:
    pointer to NcDbSymbolUtilities::Services
*/
NRXDBGATE_EXPORT const NcDbSymUtilServices* ncdbSymUtil();

#endif // __OPENDWG_SYMBOLUTILITIES_H__
