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

#ifndef __OPENDWG_DATABASE_H__
#define __OPENDWG_DATABASE_H__

#include "nrxdbgate_impexp.h"

#ifndef CS_STDCALL
	#define CS_STDCALL   __stdcall
#endif

#if !defined(NANOTHUNK_SEALED) && (TD_MAJOR_VERSION >= 3)
	#define NANOTHUNK_SEALED  sealed
#else
	#define NANOTHUNK_SEALED
#endif

#ifndef HIMAGELIST
struct _IMAGELIST;
typedef struct _IMAGELIST* HIMAGELIST;
#endif

class COleClientItem;
class INcReadStream;

class NcDbSubentId;
NRXDBGATE_EXPORT extern NcDbSubentId kNullSubentId;

typedef NcArray <NcDbEvalNodeId> NcDbEvalNodeIdArray;


struct NcGridProperty
{
	NcDb::GridProperty  mnPropMask;
	NcDb::GridLineStyle mnLineStyle;
	NcDb::LineWeight    mnLineWeight;
	NcDbHardPointerId   mLinetype;
	NcCmColor           mColor;
	NcDb::Visibility    mnVisibility;
	double              mfDoubleLineSpacing;
};

struct NcConstrainedGeometryDraggingInfo;

class NcDbDataCellImpl;

class NcDb2dPolyline;
class NcDb3dPolyline;
class NcDb3dProfile;
class NcDb3dSolid;
class NcDbAbstractViewTable;
class NcDbAbstractViewTableRecord;
class NcDbAbstractViewTableIterator;
class NcDbAnnotationScale;
class NcDbBlendOptions;
class NcDbBlockBegin;
class NcDbBlockChangeIterator;
class NcDbBlockEnd;
class NcDbBlockReferenceIdIterator;
class NcDbBlockTable;
class NcDbBlockTableIterator;
class NcDbBlockTableRecordIterator;
class NcDbBlockTableRecord;
class NcDbBreakPointRef;
class NcDbCurve;
class NcDbDatabase;
class NcDbDataColumn;
class NcDbDataLinkManager;
class NcDbDatabaseReactor;
class NcDbDimStyleTable;
class NcDbDimStyleTableIterator;
class NcDbDimStyleTableRecord;
class NcDbDictionary;
class NcDbDictionaryWithDefault;
class NcDbDgnRefFileData;
class NcDbDxfFiler;
class NcDbDwgFiler;
class NcDbEntity;
class NcDbExtents;
class NcDbFaceRecord;
class NcDbField;
class NcDbEvalGraph;
class NcDbEvalEdgeInfo;
class NcDbEvalExpr;
class NcDbEvalConnectable;
class NcDbEvalContext;
class NcDbEvalContextPair;
class NcDbEvalContextIterator;
class NcDbEvalEdgeInfoArray;
class NcDbEvalVariant;
class NcDbExtrudedSurface;

class NcDbFaceterSettings;
class NcDbFilteredBlockIterator;
class NcDbIndexUpdateData;
class NcDbGripData;
class NcDbGroupIterator;
class NcDbHandleTable;
class NcDbHandleTableIterator;
class NcDbHomeView;
class NcDbIdMapping;

class NcDbLayerStateManager;
class NcDbLeader;
class NcDbLayerFilter;
class NcDbLayerTable;
class NcDbLayerTableIterator;
class NcDbLayerTableRecord;
class NcDbLinetypeTable;
class NcDbLinetypeTableIterator;
class NcDbLinetypeTableRecord;
class NcDbLinkedTableData;
class NcDbLoftOptions;
class NcDbLoftProfile;
class NcDbMatchProperties;
class NcDbMLeader;
class NcDbMLeaderStyle;
class NcDbMLeaderObjectContextData;
class NcDbMText;
class NcDbObject;
class NcDbObjectContextCollectionIterator;
class NcDbObjectContextManager;
class NcDbObjectIdGraph;
class NcDbObjectReactor;
class NcDbOle2Frame;
class NcDbPolyFaceMeshVertex;
class NcDbPolyline;
class NcDbRasterVariables;
class NcDbRegAppTable;
class NcDbRegAppTableRecord;
class NcDbRegion;
class NcDbRevolvedSurface;
class NcDbRevolveOptions;
class NcDbSectionSettings;
class NcDbSectionManager;
class NcDbSectionManagerIterator;
class NcDbSequenceEnd;
class NcDbServices;
class NcDbSortentsTable;
class NcDbSpatialFilter;
class NcDbSpline;
class NcDbSweepOptions;
class NcDbSweptSurface;
class NcDbSymbolTable;
class NcDbSymbolTableIterator;
class NcDbSymbolTableRecord;
class NcDbTableIterator;
class NcDbTableTemplate;
class NcDbTextStyleTable;
class NcDbTextStyleTableIterator;
class NcDbTextStyleTableRecord;
class NcDbTransactionManager;
class NcDbUcsPlane;
class NcDbUCSTable;
class NcDbUnderlayItem;
class NcDbUnderlayHost;
struct NcDbUnderlayDrawContext;
class NcDbUndoController;
class NcDbViewport;
class NcDbViewportTable;
class NcDbViewTable;

class NcDwgFileHandle;
class NcValue;
class NcCmColor;
class NcImpUnderlayLayer;
class NcFdFieldEngine;
class NcFdFieldResult;
class NcLyBoolExpr;

class NcFileDependencyManager;

class OdDbDate;

class ENTITY;
class RasterImageDefImp;
class RasterImageImp;

interface INcSmDatabase;
interface INcSmSheetSet;
interface INcSmComponent;

NRXDBGATE_EXPORT Nano::ErrorStatus CS_STDCALL
accessNcDbObjectForRead(NcDbObject * & pObj,
                        NcDbObjectId id,
                        const NcRxClass *pClass,
                        bool &bWasOpened,
                        bool bOpenErased);

template<class NCDB_CLASS> inline Nano::ErrorStatus
accessNcDbObjectForRead(NCDB_CLASS * & pObj,
                        NcDbObjectId id,
                        bool &bWasOpened,
                        bool bOpenErased = false)
{
	return ::accessNcDbObjectForRead((NcDbObject * &)pObj,
	                                 id,
	                                 NCDB_CLASS::desc(),
	                                 bWasOpened, bOpenErased);
};

NRXDBGATE_EXPORT Nano::ErrorStatus CS_STDCALL
accessNcDbObjectForWrite(NcDbObject *pObj,
                         bool &bWasNotifyEnabled,
                         bool &bWasWriteEnabled,
                         int  &readCountClosed,
                         bool openOnLockedLayer);

NRXDBGATE_EXPORT Nano::ErrorStatus CS_STDCALL
revertNcDbObjectFromWrite(NcDbObject *pObj,
                          Nano::ErrorStatus accessStatus,
                          bool bWasNotifyEnabled,
                          bool bWasWriteEnabled,
                          int  readCountClosed);

template<class NCDB_CLASS>
class NcDbSmartObjectPointer;

typedef bool (*NCDBGEODATA_VALIDATE_CS)(const NCHAR* coordinateSystem);

enum ClassVersion
{
	kVersion1   = 0,
	kVersion2   = 1,
	kVersion3   = 2
};

struct MeshFaceterSettings
{
	double faceterDevSurface;
	double faceterDevNormal;
	double faceterGridRatio;
	double faceterMaxEdgeLength;
	NRX::UInt16 faceterMaxGrid;
	NRX::UInt16 faceterMinUGrid;
	NRX::UInt16 faceterMinVGrid;
	NRX::Int16 faceterMeshType;
};

enum FileType{
	kDgnFile   = 1,
	kDwgFile   = 2,
	kImageFile = 3,
	kOtherFile = 4
};

typedef enum NcFilterablePropertyContext
{
	acQuickPropertiesContext = 0,
	acTooltipContext         = 1
} NcFilterablePropertyContext;

typedef struct NcCell
{
	int     mnRow;
	int     mnColumn;
} NcCell;

typedef struct NcCellRange
{
	int  mnTopRow;
	int  mnLeftColumn;
	int  mnBottomRow;
	int  mnRightColumn;

	bool operator==(const NcCellRange& other) const
	{
		return (mnTopRow == other.mnTopRow &&
			mnLeftColumn == other.mnLeftColumn &&
			mnBottomRow == other.mnBottomRow &&
			mnRightColumn == other.mnRightColumn );
	}
} NcCellRange;

typedef NcArray<NcCellRange> NcCellRangeArray;

typedef struct NcFd
{
	enum EvalFields
	{
		kEvalRecursive      = (0x1 << 0),
	};

	enum ConvertFieldToText
	{
		kConvertFieldToTextNone         = 0,
		kEvaluateBeforeConversion       = (0x1 << 0),
		kExcludeEvaluatorsInList        = (0x1 << 1),
		kIgnoreEvaluatorVersion         = (0x1 << 2),
	};

} NcFd;

typedef UINT64    NcDgnRefFileId;

class NRXDBGATE_EXPORT NcDbDgnRefFileData {
	enum FileType{
		kDgnFile   = 1,
		kDwgFile   = 2,
		kImageFile = 3,
		kOtherFile = 4
	};
	FileType type;
	NcString savedPathAndName;
	NcString foundPathAndName;
	NcDgnRefFileId refId;
};
typedef NcArray<NcDbDgnRefFileData*> NcDbRefFileDataPtrArray;
typedef NcArray<NcDgnRefFileId>     NcDbDgnRefFileIdArray;

NRXDBGATE_EXPORT NcDbVoidPtrArray* ncdbActiveDatabaseArray();

struct SecurityParams
{
	unsigned long cbSize;
	unsigned long ulFlags;

	wchar_t*      wszPassword;
	unsigned long ulProvType;
	wchar_t*      wszProvName;
	unsigned long ulAlgId;
	unsigned long ulKeyLength;

	wchar_t*      wszCertSubject;
	wchar_t*      wszCertIssuer;
	wchar_t*      wszCertSerialNum;
	wchar_t*      wszComment;
	wchar_t*      wszTimeServer;
};

namespace NcFdEval
{
	enum ObjectFieldOption
	{
		kObjFieldNone                   = 0,
		kObjFieldUnresolvedBlockRef     = (0x1 << 0),
		kObjFieldApplyBlockTransform    = (0x1 << 1),
		kObjFieldUnresolvedObjectRef    = (0x1 << 2),
	};

	enum SheetSetFieldOption
	{
		kSheetSetNone                   = 0,
		kSheetSetHyperlink              = (0x1 << 0),
		kSheetSetUnresolvedComponent    = (0x1 << 1),
	};

	enum ExpressionFieldOption
	{
		kExprFieldNone                  = 0,
		kExprFieldSum                   = (0x1 << 0),
		kExprFieldAverage               = (0x1 << 1),
		kExprFieldCount                 = (0x1 << 2),
		kExprFieldCell                  = (0x1 << 3),
		kExprFieldEquation              = (0x1 << 4),
	};
};

typedef struct NcHyperlink
{
	NcString                msUrl;
	NcString                msSubLocation;
	NcString                msDescription;
	NRX::Int32            mlFlag;
} NcHyperlink;
#if 0 //YAL: now in ODA 20.12 
static const unsigned int kPlineVerticesThrehold = 10000;
#endif
namespace nc_constants
{
	static const unsigned int kPlineVerticesThrehold = 10000U;
}
//////////////////////////////////////////////////////////////////////////
// NcDbDate
class OdDbDate;
class NRXDBGATE_EXPORT NcDbDate
{
public:
	typedef NcDbDate  wrapper_class;
	typedef OdDbDate  native_class;
	enum InitialValue {
		kInitZero          = 1,
		kInitLocalTime     = 2,
		kInitUniversalTime = 3
	};

	NcDbDate();
	NcDbDate(InitialValue i);
	NcDbDate(const OdDbDate* src);
	NcDbDate(const NcDbDate& date);
	~NcDbDate();
	
public:
	const NcDbDate& operator=(const OdDbDate*src);

	// Dwg in and out.
	Nano::ErrorStatus dwgOut(NcDbDwgFiler* outFiler) const;
	Nano::ErrorStatus dwgIn(NcDbDwgFiler* inFiler);

public:
	const NcDbDate& add(const NcDbDate &date);
	short day() const;
	void  getDate(short& month, short& day, short& year) const;
	void  getLocalTime();
	void  getTime(short& hour, short& min, short& sec, short& msec) const;
	void  getTime(SYSTEMTIME &st) const;
	void  getUniversalTime();
	short hour() const;
	NRX::Int32 julianDay() const;
	double julianFraction() const;
	void localToUniversal();
	short millisecond() const;
	short minute() const;
	short month() const;
	NRX::Int32   msecsPastMidnight() const;
	const NcDbDate operator - (const NcDbDate &date) const;
	const NcDbDate operator + (const NcDbDate &date) const;
	bool operator < (const NcDbDate&) const;
	bool operator <= (const NcDbDate&) const;
	const NcDbDate& operator= (const NcDbDate&);
	bool operator== (const NcDbDate&) const;
	bool operator > (const NcDbDate&) const;
	bool operator >= (const NcDbDate&) const;
	short second() const;
	void  setDate(short month, short day, short year);
	void  setDay(short);
	void  setHour(short);
	void  setJulianDate(NRX::Int32 julianDay, NRX::Int32 msec);
	void  setJulianDay(NRX::Int32 julianDay);
	void  setJulianFraction(double);
	void  setMillisecond(short);
	void  setMinute(short);
	void  setMonth(short);
	void  setMsecsPastMidnight(NRX::Int32 msec);
	void  setSecond(short);
	void  setTime(const SYSTEMTIME &st);
	void  setTime(short hour, short min, short sec, short msec);
	void  setToZero();
	void  setYear (short);
	const NcDbDate& subtract(const NcDbDate &date);
	void universalToLocal();
	short year() const;

public:
	OdDbDate* native() const;

private:
	OdDbDate* m_pNative;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDatabase
class OdDbDatabase;
class NRXDBGATE_EXPORT NcDbDatabase : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbDatabase);

	//NcDbDatabase();
	NcDbDatabase(bool default_document = true, bool no_doc = false);

	NcDbDatabase(OdRxObject* _object);

public:
	~NcDbDatabase();


public:
	typedef NcDbDatabase  wrapper_class;
	typedef OdDbDatabase  native_class;

	virtual double dimtxt(void) ; //+Overload
	virtual double dimtvp(void) ; //+Overload
	virtual double dimtsz(void) ; //+Overload
	virtual double dimtp(void) ; //+Overload
	virtual double dimtm(void) ; //+Overload
	virtual double dimtfac(void) ; //+Overload
	virtual double dimscale(void) ; //+Overload
	virtual double dimrnd(void) ; //+Overload
	virtual double dimmzf(void) ; //+Overload
	virtual double dimlfac(void) ; //+Overload
	virtual double dimjogang(void) ; //+Overload
	virtual double dimgap(void) ; //+Overload
	virtual double dimexo(void) ; //+Overload
	virtual double dimexe(void) ; //+Overload
	virtual double dimdli(void) ; //+Overload
	virtual double dimdle(void) ; //+Overload
	virtual double dimcen(void) ; //+Overload
	virtual double dimasz(void) ; //+Overload
	virtual double dimaltrnd(void) ; //+Overload
	virtual double dimaltmzf(void) ; //+Overload
	virtual double dimaltf(void) ; //+Overload
	virtual bool dimupt(void) ; //+Overload
	virtual bool dimtxtdirection(void) ; //+Overload
	virtual bool dimtol(void) ; //+Overload
	virtual bool dimtoh(void) ; //+Overload
	virtual bool dimtofl(void) ; //+Overload
	virtual bool dimtix(void) ; //+Overload
	virtual bool dimtih(void) ; //+Overload
	virtual NcCmColor dimtfillclr(void) ; //+Overload
	virtual bool dimsoxd(void) ; //+Overload
	virtual bool dimse2(void) ; //+Overload
	virtual bool dimse1(void) ; //+Overload
	virtual bool dimsd2(void) ; //+Overload
	virtual bool dimsd1(void) ; //+Overload
	virtual bool dimsah(void) ; //+Overload
	virtual NcDb::LineWeight dimlwe(void) ; //+Overload
	virtual NcDb::LineWeight dimlwd(void) ; //+Overload
	virtual bool dimlim(void) ; //+Overload
	virtual NcCmColor dimclrt(void) ; //+Overload
	virtual NcCmColor dimclre(void) ; //+Overload
	virtual NcCmColor dimclrd(void) ; //+Overload
	virtual bool dimalt(void) ; //+Overload

	virtual int              dimadec  () const;
	virtual int              dimaltd  () const;

	virtual const NCHAR *    dimaltmzs() const;

	virtual int              dimalttd () const;
	virtual int              dimalttz () const;
	virtual int              dimaltu  () const;
	virtual int              dimaltz  () const;
	virtual const NCHAR *    dimapost () const;
	virtual int              dimarcsym() const;
	virtual int              dimatfit () const;

	virtual int              dimaunit () const;
	virtual int              dimazin  () const;

	virtual NcDbObjectId     dimblk   () const;
	virtual NcDbObjectId     dimblk1  () const;
	virtual NcDbObjectId     dimblk2  () const;
	virtual int              dimdec   () const;
	virtual NCHAR            dimdsep  () const;
	int dimfit() const;
	virtual int              dimfrac  () const;

	virtual double           dimfxlen    () const;
	virtual bool             dimfxlenOn  () const;

	virtual int              dimjust  () const;
	virtual NcDbObjectId     dimldrblk() const;
	virtual NcDbObjectId     dimltex1 () const;

	virtual NcDbObjectId     dimltex2 () const;

	virtual NcDbObjectId     dimltype () const;

	virtual int              dimlunit () const;

	virtual const NCHAR *    dimmzs   () const;

	virtual const NCHAR *    dimpost  () const;
	virtual int              dimtad   () const;
	virtual int              dimtdec  () const;
	virtual int              dimtfill () const;
	virtual int              dimtmove () const;
	virtual int              dimtolj  () const;
	virtual NcDbObjectId     dimtxsty () const;
	virtual int              dimtzin  () const;
	int dimunit() const;
	virtual int              dimzin   () const;

	virtual NcDbDwgFiler* undoFiler() ; //+Overload2
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload2
public:
	// Add objects(but not entities) to database

	Nano::ErrorStatus addNcDbObject(NcDbObject* object);
	Nano::ErrorStatus addNcDbObject(NcDbObjectId& id, NcDbObject* object);

	Nano::ErrorStatus getBlockTable(NcDbSymbolTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getLayerTable(NcDbSymbolTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getTextStyleTable(NcDbSymbolTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getLinetypeTable(NcDbSymbolTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getViewTable(NcDbSymbolTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getUCSTable(NcDbSymbolTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getViewportTable(NcDbSymbolTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getRegAppTable(NcDbSymbolTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getDimStyleTable(NcDbSymbolTable*& table, NcDb::OpenMode mode);

	Nano::ErrorStatus getSymbolTable(NcDbBlockTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getSymbolTable(NcDbLayerTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getSymbolTable(NcDbTextStyleTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getSymbolTable(NcDbLinetypeTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getSymbolTable(NcDbViewTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getSymbolTable(NcDbUCSTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getSymbolTable(NcDbViewportTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getSymbolTable(NcDbRegAppTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getSymbolTable(NcDbDimStyleTable*& table, NcDb::OpenMode mode);

	Nano::ErrorStatus getBlockTable(NcDbBlockTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getLayerTable(NcDbLayerTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getTextStyleTable(NcDbTextStyleTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getLinetypeTable(NcDbLinetypeTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getViewTable(NcDbViewTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getUCSTable(NcDbUCSTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getViewportTable(NcDbViewportTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getRegAppTable(NcDbRegAppTable*& table, NcDb::OpenMode mode);
	Nano::ErrorStatus getDimStyleTable(NcDbDimStyleTable*& table, NcDb::OpenMode mode);

	Nano::ErrorStatus getDictionary(NcDbDictionary*& dictionary, NcDbObjectId id, NcDb::OpenMode mode);
	Nano::ErrorStatus getGroupDictionary(NcDbDictionary*& dictionary, NcDb::OpenMode mode);
	Nano::ErrorStatus getMLStyleDictionary(NcDbDictionary*& dictionary, NcDb::OpenMode mode);
	Nano::ErrorStatus getLayoutDictionary(NcDbDictionary*& dictionary, NcDb::OpenMode mode);
	Nano::ErrorStatus getPlotStyleNameDictionary(NcDbDictionaryWithDefault*& pDict, NcDb::OpenMode mode);
	Nano::ErrorStatus getMaterialDictionary(NcDbDictionary*& dictionary, NcDb::OpenMode mode);
	Nano::ErrorStatus getVisualStyleDictionary(NcDbDictionary*& dictionary, NcDb::OpenMode mode);
	Nano::ErrorStatus getColorDictionary(NcDbDictionary*& dictionary, NcDb::OpenMode mode);
	Nano::ErrorStatus getNamedObjectsDictionary(NcDbDictionary*& dictionary, NcDb::OpenMode mode);
	Nano::ErrorStatus getTableStyleDictionary(NcDbDictionary*& dictionary, NcDb::OpenMode mode);

	// Todo: change all these xxxTableId() and xxxDictionaryId()
	// methods to const.
	//
	NcDbObjectId blockTableId();
	NcDbObjectId layerTableId();
	NcDbObjectId textStyleTableId();
	NcDbObjectId linetypeTableId();
	NcDbObjectId viewTableId();
	NcDbObjectId UCSTableId();
	NcDbObjectId viewportTableId();
	NcDbObjectId regAppTableId();
	NcDbObjectId dimStyleTableId();
	NcDbObjectId mLStyleDictionaryId();
	NcDbObjectId groupDictionaryId();
	NcDbObjectId layoutDictionaryId();
	NcDbObjectId plotStyleNameDictionaryId();
	NcDbObjectId materialDictionaryId();
	NcDbObjectId visualStyleDictionaryId();
	NcDbObjectId colorDictionaryId();
	NcDbObjectId namedObjectsDictionaryId();
	NcDbObjectId plotSettingsDictionaryId();
	NcDbObjectId tableStyleDictionaryId() const;

	NcDbObjectId layerZero() const;
	NcDbObjectId continuousLinetype() const;
	NcDbObjectId byLayerLinetype() const;
	NcDbObjectId byBlockLinetype() const;

	NcDbObjectId globalMaterial() const;
	NcDbObjectId byLayerMaterial() const;
	NcDbObjectId byBlockMaterial() const;

	NcDbObjectId paperSpaceVportId() const;
	NcDbObjectId currentSpaceId() const;

	// Traverse the db and remove non-purgeable ids from the array
	Nano::ErrorStatus purge(NcDbObjectIdArray& ids);
	Nano::ErrorStatus purge(NcDbObjectIdGraph& idGraph);
	Nano::ErrorStatus countHardReferences(const NcDbObjectIdArray& ids, NRX::UInt32* count);

	Nano::ErrorStatus getNcDbObjectId(NcDbObjectId& id, bool create, const NcDbHandle& handle,
	                                  NRX::UInt32 ref = 0);

	enum OpenMode
	{
		kForReadAndReadShare    = 1,
		kForReadAndWriteNoShare = 2,
		kForReadAndAllShare     = 3,
		kTryForReadShare        = 4
	};

	Nano::ErrorStatus readDwgFile(const NCHAR* file, OpenMode shmode, bool bAllowCPConversion = false,
	                              const wchar_t* wszPassword = NULL);
	Nano::ErrorStatus readDwgFile(const NCHAR* file, const int shmode = _SH_DENYWR, bool bAllowCPConversion = false,
	                              const wchar_t* wszPassword = NULL);
	Nano::ErrorStatus readDwgFile(NcDwgFileHandle* pDwgFile, bool bAllowCPConversion = false,
	                              const wchar_t* wszPassword = NULL);

	Nano::ErrorStatus saveAs(const NCHAR* file, const SecurityParams* pSecParams = 0);
	Nano::ErrorStatus saveAs(const NCHAR* file, const bool bBakAndRename, const NcDb::NcDbDwgVersion version =
	                         NcDb::kDHL_CURRENT, const SecurityParams* security = 0);
	Nano::ErrorStatus saveAs(NcDwgFileHandle* pOutputFiler, const SecurityParams* pSecParams = 0,
	                         bool crashing = false);
	Nano::ErrorStatus save();

	Nano::ErrorStatus dxfIn(const NCHAR* file, const NCHAR* log = NULL);
	Nano::ErrorStatus dxfIn(INcReadStream* pInputStream, const NCHAR* logFilename = NULL);
	Nano::ErrorStatus dxfOut(const NCHAR* file, int precision = 16, NcDb::NcDbDwgVersion dwgVer = NcDb::kDHL_CURRENT,
	                         bool save_thumbnail = false);

	Nano::ErrorStatus closeInput(bool close = false);

	int approxNumObjects() const;
	NRX::Int32 numberOfSaves() const;
	const NCHAR* originalFileName() const;
	NcDb::NcDbDwgVersion lastSavedAsVersion() const;
	NcDb::NcDbDwgVersion originalFileVersion() const;
	NcDb::NcDbDwgVersion originalFileSavedByVersion() const;
	NcDb::MaintenanceReleaseVersion lastSavedAsMaintenanceVersion() const;
	NcDb::MaintenanceReleaseVersion originalFileMaintenanceVersion() const;
	NcDb::MaintenanceReleaseVersion originalFileSavedByMaintenanceVersion() const;

	NcDwgFileHandle* inputFiler() const;

	Nano::ErrorStatus wblock(NcDbDatabase*& output, const NcDbObjectIdArray& ids, const NcGePoint3d& base);
	Nano::ErrorStatus wblock(NcDbDatabase* output, const NcDbObjectIdArray& ids, const NcGePoint3d& base,
	                         NcDb::DuplicateRecordCloning drc);
	Nano::ErrorStatus wblock(NcDbDatabase*& output, NcDbObjectId block);
	Nano::ErrorStatus wblock(NcDbDatabase*& output);

	void forceWblockDatabaseCopy();

	Nano::ErrorStatus insert(NcDbObjectId& id, const NCHAR* block, NcDbDatabase* database, bool preserve = true);
	Nano::ErrorStatus insert(const NcGeMatrix3d& xform, NcDbDatabase* database, bool preserve = true);
	Nano::ErrorStatus insert(NcDbObjectId& id, const NCHAR* source, const NCHAR* destination, NcDbDatabase* database,
	                         bool preserve = true);

	Nano::ErrorStatus deepCloneObjects(NcDbObjectIdArray& ids, NcDbObjectId& owner, NcDbIdMapping& map,
	                                   bool defer = false);
	Nano::ErrorStatus wblockCloneObjects(NcDbObjectIdArray& ids, NcDbObjectId& owner, NcDbIdMapping& map,
	                                     NcDb::DuplicateRecordCloning drc, bool defer = false);

	void abortDeepClone(NcDbIdMapping& map);

	void addReactor(NcDbDatabaseReactor* reactor) const;
	void removeReactor(NcDbDatabaseReactor* reactor) const;

	Nano::ErrorStatus audit(NcDbAuditInfo* info);
	Nano::ErrorStatus auditXData(NcDbAuditInfo* info);

	NcDbUndoController* undoController() const;

	void disableUndoRecording(bool disable);
	bool undoRecording() const;

	NcDbTransactionManager* transactionManager() const;

	NcFileDependencyManager* fileDependencyManager() const;

	NRX::UInt8 maintenanceReleaseVersion() const;

	Nano::ErrorStatus restoreOriginalXrefSymbols();
	Nano::ErrorStatus restoreForwardingXrefSymbols();

	NcDbObjectId xrefBlockId() const;

	// Access to ThumbnailImage(preview)
	// These functions take a windows BITMAPINFO*
	//
	void* thumbnailBitmap() const;
	Nano::ErrorStatus setThumbnailBitmap(void* pBmp);
	bool retainOriginalThumbnailBitmap() const;
	void setRetainOriginalThumbnailBitmap(bool retain);
	bool isEMR() const;

	// methods to set and retrieve security-related information
	bool setSecurityParams(const SecurityParams* pSecParams, bool bSetDbMod = true);
	const SecurityParams* cloneSecurityParams();
	static void disposeSecurityParams(const SecurityParams* pSecParams);

	// Header variables exposed via DXF and/or SETVAR
	//
	bool dimaso() const;
	Nano::ErrorStatus setDimaso(bool aso);

	bool dimsho() const;
	Nano::ErrorStatus setDimsho(bool sho);

	bool plinegen() const;
	Nano::ErrorStatus setPlinegen(bool gen);

	bool orthomode() const;
	Nano::ErrorStatus setOrthomode(bool mode);

	bool regenmode() const;
	Nano::ErrorStatus setRegenmode(bool mode);

	bool fillmode() const;
	Nano::ErrorStatus setFillmode(bool mode);

	bool qtextmode() const;
	Nano::ErrorStatus setQtextmode(bool mode);

	bool psltscale() const;
	Nano::ErrorStatus setPsltscale(bool scale);

	bool limcheck() const;
	Nano::ErrorStatus setLimcheck(bool check);

	bool blipmode() const;
	Nano::ErrorStatus setBlipmode(bool mode);

	NRX::Int16 saveproxygraphics() const;
	Nano::ErrorStatus setSaveproxygraphics(NRX::Int16 saveimg);

	NRX::Int16 delUsedObj() const;
	Nano::ErrorStatus setDelUsedObj(NRX::Int16 deleteObj);

	bool dispSilh() const;
	Nano::ErrorStatus setDispSilh(bool silh);

	bool plineEllipse() const;
	Nano::ErrorStatus setPlineEllipse(bool pline);

	bool usrtimer() const;
	Nano::ErrorStatus setUsrtimer(bool timer);

	bool skpoly() const;
	Nano::ErrorStatus setSkpoly(bool as_poly);

	bool angdir() const;
	Nano::ErrorStatus setAngdir(bool dir);

	bool splframe() const;
	Nano::ErrorStatus setSplframe(bool disp);

	bool attreq() const;
	Nano::ErrorStatus setAttreq(bool req);

	bool attdia() const;
	Nano::ErrorStatus setAttdia(bool dia);

	bool mirrtext() const;
	Nano::ErrorStatus setMirrtext(bool mirror);

	bool worldview() const;
	Nano::ErrorStatus setWorldview(bool view);

	bool tilemode() const;
	Nano::ErrorStatus setTilemode(bool mode);

	bool plimcheck() const;
	Nano::ErrorStatus setPlimcheck(bool check);

	bool visretain() const;
	Nano::ErrorStatus setVisretain(bool retain);

	NRX::Int16 dragmode() const;
	Nano::ErrorStatus setDragmode(NRX::Int16 mode);

	NRX::Int16 treedepth() const;
	Nano::ErrorStatus setTreedepth(NRX::Int16 depth);

	NRX::Int16 lunits() const;
	Nano::ErrorStatus setLunits(NRX::Int16 lunits);

	NRX::Int16 luprec() const;
	Nano::ErrorStatus setLuprec(NRX::Int16 prec);

	NRX::Int16 aunits() const;
	Nano::ErrorStatus setAunits(NRX::Int16 aunits);

	NRX::Int16 auprec() const;
	Nano::ErrorStatus setAuprec(NRX::Int16 auprec);

	NRX::Int16 attmode() const;
	Nano::ErrorStatus setAttmode(NRX::Int16 mode);

	NRX::Int16 coords() const;
	Nano::ErrorStatus setCoords(NRX::Int16 coords);

	NRX::Int16 pdmode() const;
	Nano::ErrorStatus setPdmode(NRX::Int16 mode);

	NRX::Int16 pickstyle() const;
	Nano::ErrorStatus setPickstyle(NRX::Int16 style);

	NRX::Int16 useri1() const;
	Nano::ErrorStatus setUseri1(NRX::Int16 val);

	NRX::Int16 useri2() const;
	Nano::ErrorStatus setUseri2(NRX::Int16 val);

	NRX::Int16 useri3() const;
	Nano::ErrorStatus setUseri3(NRX::Int16 val);

	NRX::Int16 useri4() const;
	Nano::ErrorStatus setUseri4(NRX::Int16 val);

	NRX::Int16 useri5() const;
	Nano::ErrorStatus setUseri5(NRX::Int16 val);

	NRX::Int16 splinesegs() const;
	Nano::ErrorStatus setSplinesegs(NRX::Int16 segs);

	NRX::Int16 surfu() const;
	Nano::ErrorStatus setSurfu(NRX::Int16 u);

	NRX::Int16 surfv() const;
	Nano::ErrorStatus setSurfv(NRX::Int16 v);

	NRX::Int16 surftype() const;
	Nano::ErrorStatus setSurftype(NRX::Int16 type);

	NRX::Int16 surftab1() const;
	Nano::ErrorStatus setSurftab1(NRX::Int16 tab1);

	NRX::Int16 surftab2() const;
	Nano::ErrorStatus setSurftab2(NRX::Int16 tab2);

	NRX::Int16 splinetype() const;
	Nano::ErrorStatus setSplinetype(NRX::Int16 type);

	NRX::Int16 shadedge() const;
	Nano::ErrorStatus setShadedge(NRX::Int16 mode);

	NRX::Int16 shadedif() const;
	Nano::ErrorStatus setShadedif(NRX::Int16 dif);

	NcDb::MeasurementValue measurement() const;
	Nano::ErrorStatus setMeasurement(NcDb::MeasurementValue type);

	NRX::Int16 unitmode() const;
	Nano::ErrorStatus setUnitmode(NRX::Int16 mode);

	NRX::Int16 maxactvp() const;
	Nano::ErrorStatus setMaxactvp(NRX::Int16 max);

	NRX::Int16 isolines() const;
	Nano::ErrorStatus setIsolines(NRX::Int16 isolines);

	NRX::UInt8 dwfframe() const;
	Nano::ErrorStatus setDwfframe(NRX::UInt8 frame);

	NRX::UInt8 dgnframe() const;
	Nano::ErrorStatus setDgnframe(NRX::UInt8 frame);

	double ltscale() const;
	Nano::ErrorStatus setLtscale(double scale);

	double textsize() const;
	Nano::ErrorStatus setTextsize(double size);

	double tracewid() const;
	Nano::ErrorStatus setTracewid(double width);

	double sketchinc() const;
	Nano::ErrorStatus setSketchinc(double inc);

	double filletrad() const;
	Nano::ErrorStatus setFilletrad(double radius);

	double thickness() const;
	Nano::ErrorStatus setThickness(double thickness);

	NcDb::LineWeight celweight() const;
	Nano::ErrorStatus setCelweight(NcDb::LineWeight weight);

	static bool isValidLineWeight(int weight);
	static NcDb::LineWeight getNearestLineWeight(int weight);

	NcDb::EndCaps endCaps() const;
	Nano::ErrorStatus setEndCaps(NcDb::EndCaps type);

	NcDb::JoinStyle joinStyle() const;
	Nano::ErrorStatus setJoinStyle(NcDb::JoinStyle style);

	bool lineWeightDisplay() const;
	Nano::ErrorStatus setLineWeightDisplay(bool display);

	bool xrefEditEnabled() const;
	Nano::ErrorStatus setXrefEditEnabled(bool enable);

	bool oleStartUp() const;
	Nano::ErrorStatus setOleStartUp(bool val);

	double angbase() const;
	Nano::ErrorStatus setAngbase(double angle);

	double pdsize() const;
	Nano::ErrorStatus setPdsize(double size);

	double plinewid() const;
	Nano::ErrorStatus setPlinewid(double width);

	double userr1() const;
	Nano::ErrorStatus setUserr1(double val);

	double userr2() const;
	Nano::ErrorStatus setUserr2(double val);

	double userr3() const;
	Nano::ErrorStatus setUserr3(double val);

	double userr4() const;
	Nano::ErrorStatus setUserr4(double val);

	double userr5() const;
	Nano::ErrorStatus setUserr5(double val);

	double chamfera() const;
	Nano::ErrorStatus setChamfera(double val);

	double chamferb() const;
	Nano::ErrorStatus setChamferb(double val);

	double chamferc() const;
	Nano::ErrorStatus setChamferc(double val);

	double chamferd() const;
	Nano::ErrorStatus setChamferd(double val);

	double facetres() const;
	Nano::ErrorStatus setFacetres(double facetres);

	double get3dDwfPrec() const;
	Nano::ErrorStatus set3dDwfPrec(double prec);

	Nano::ErrorStatus getMenu(NCHAR*& name) const;

	bool hpInherit() const;
	Nano::ErrorStatus setHpInherit(const bool inherit);

	NcGePoint2d hpOrigin() const;
	Nano::ErrorStatus setHpOrigin(const NcGePoint2d& origin);

	const NcDbDate tdcreate() const;
	const NcDbDate tdupdate() const;

	const NcDbDate tducreate() const;
	const NcDbDate tduupdate() const;

	const NcDbDate tdindwg() const;
	const NcDbDate tdusrtimer() const;

	NcCmColor cecolor() const;
	Nano::ErrorStatus setCecolor(const NcCmColor& color);

	NcDbHandle handseed() const;
	Nano::ErrorStatus setHandseed(const NcDbHandle& handle);

	NcDbObjectId clayer() const;
	Nano::ErrorStatus setClayer(NcDbObjectId id);

	NcDb::PlotStyleNameType getCePlotStyleNameId(NcDbObjectId& id) const;
	Nano::ErrorStatus setCePlotStyleName(NcDb::PlotStyleNameType, NcDbObjectId newId = NcDbObjectId::kNull);

	NcDbObjectId textstyle() const;
	Nano::ErrorStatus setTextstyle(NcDbObjectId id);

	NcDbObjectId celtype() const;
	Nano::ErrorStatus setCeltype(NcDbObjectId id);

	NcDbObjectId cmaterial() const;
	Nano::ErrorStatus setCmaterial(NcDbObjectId id);

	NcDbObjectId dimstyle() const;
	Nano::ErrorStatus setDimstyle(NcDbObjectId id);

	Nano::ErrorStatus getDimstyleData(NcDbDimStyleTableRecord*& record) const;
	Nano::ErrorStatus getDimstyleChildData(const NcRxClass* pDimClass, NcDbDimStyleTableRecord*& record,
	                                       NcDbObjectId& style) const;

	NcDbObjectId getDimstyleChildId(const NcRxClass* pDimClass, NcDbObjectId& parentStyle) const;

	NcDbObjectId getDimstyleParentId(NcDbObjectId& childStyle) const;

	Nano::ErrorStatus setDimstyleData(NcDbDimStyleTableRecord* record);
	Nano::ErrorStatus setDimstyleData(NcDbObjectId id);

	NcDbObjectId cmlstyleID() const;
	Nano::ErrorStatus setCmlstyleID(NcDbObjectId id);

	NRX::Int16 cmljust() const;
	Nano::ErrorStatus setCmljust(NRX::Int16 just);

	double cmlscale() const;
	Nano::ErrorStatus setCmlscale(double scale);

	double celtscale() const;
	Nano::ErrorStatus setCeltscale(double scale);

	NcGePoint3d pinsbase() const;
	Nano::ErrorStatus setPinsbase(const NcGePoint3d& base);

	NcGePoint3d pextmin() const;
	NcGePoint3d pextmax() const;

	Nano::ErrorStatus setPextmin(const NcGePoint3d& min);
	Nano::ErrorStatus setPextmax(const NcGePoint3d& max);

	NcGePoint2d plimmin() const;
	Nano::ErrorStatus setPlimmin(const NcGePoint2d& min);

	NcGePoint2d plimmax() const;
	Nano::ErrorStatus setPlimmax(const NcGePoint2d& max);

	double pelevation() const;
	Nano::ErrorStatus setPelevation(double elevation);

	NcGePoint3d pucsorg() const;

	NcGeVector3d pucsxdir() const;
	NcGeVector3d pucsydir() const;

	NcDbObjectId pucsname() const;

	NcDbObjectId pucsBase() const;
	Nano::ErrorStatus setPucsBase(const NcDbObjectId& ucsid);

	NcGePoint3d worldPucsBaseOrigin(NcDb::OrthographicView view) const;
	Nano::ErrorStatus setWorldPucsBaseOrigin(const NcGePoint3d& origin, NcDb::OrthographicView view);

	bool isPucsOrthographic(NcDb::OrthographicView& view) const;

	double cameraHeight() const;
	Nano::ErrorStatus setCameraHeight(const double height);

	double lensLength() const;
	Nano::ErrorStatus setLensLength(const double length);

	bool cameraDisplay() const;
	Nano::ErrorStatus setCameraDisplay(const bool display);

	double stepsPerSec() const;
	Nano::ErrorStatus setStepsPerSec(double sps);

	double stepSize() const;
	Nano::ErrorStatus setStepSize(double size);

	bool realWorldScale() const;
	Nano::ErrorStatus setRealWorldScale(const bool scale);

	NcGePoint3d insbase() const;
	Nano::ErrorStatus setInsbase(const NcGePoint3d& base);

	NcGePoint3d extmin() const;

	NcGePoint3d extmax() const;

	Nano::ErrorStatus updateExt(bool best_fit = FALSE);

	Nano::ErrorStatus setExtmin(const NcGePoint3d& min);
	Nano::ErrorStatus setExtmax(const NcGePoint3d& max);

	NcGePoint2d limmin() const;
	Nano::ErrorStatus setLimmin(const NcGePoint2d& min);

	NcGePoint2d limmax() const;
	Nano::ErrorStatus setLimmax(const NcGePoint2d& max);

	double elevation() const;

	Nano::ErrorStatus setElevation(double elevation);

	NcGePoint3d ucsorg() const;

	NcGeVector3d ucsxdir() const;
	NcGeVector3d ucsydir() const;

	NcDbObjectId ucsname() const;

	NcDbObjectId ucsBase() const;
	Nano::ErrorStatus setUcsBase(NcDbObjectId ucsid);

	NcGePoint3d worldUcsBaseOrigin(NcDb::OrthographicView view) const;
	Nano::ErrorStatus setWorldUcsBaseOrigin(const NcGePoint3d& origin, NcDb::OrthographicView view);

	bool isUcsOrthographic(NcDb::OrthographicView& orthoView) const;

	Nano::ErrorStatus getDimRecentStyleList(NcDbObjectIdArray& objIds) const;

	Nano::ErrorStatus loadLineTypeFile(const NCHAR* linetype, const NCHAR* file);

	Nano::ErrorStatus getProjectName(NCHAR*& pOutput) const;
	Nano::ErrorStatus setProjectName(const NCHAR*);
	Nano::ErrorStatus getHyperlinkBase(NCHAR*& pOutput) const;
	Nano::ErrorStatus setHyperlinkBase(const NCHAR*);
	Nano::ErrorStatus getStyleSheet(NCHAR*& pOutput) const;
	Nano::ErrorStatus setStyleSheet(const NCHAR*);
	Nano::ErrorStatus getFilename(const NCHAR*& pOutput) const;

	bool isPartiallyOpened() const;
	Nano::ErrorStatus applyPartialOpenFilters(const NcDbSpatialFilter* spatial_filter,
	                                          const NcDbLayerFilter* layer_filter);
	void disablePartialOpen();

	Nano::ErrorStatus getFingerprintGuid(NCHAR*& guidString) const;
	Nano::ErrorStatus setFingerprintGuid(const NCHAR* pNewGuid);

	Nano::ErrorStatus getVersionGuid(NCHAR*& guidString) const;
	Nano::ErrorStatus setVersionGuid(const NCHAR* pNewGuid);

	int tstackalign() const;
	Nano::ErrorStatus setTStackAlign(int val);

	int tstacksize() const;
	Nano::ErrorStatus setTStackSize(int val);

	NcDb::UnitsValue insunits() const;
	Nano::ErrorStatus setInsunits(const NcDb::UnitsValue units);

	bool plotStyleMode() const;

	// Default paperspace viewport scale
	double viewportScaleDefault() const;
	Nano::ErrorStatus setViewportScaleDefault(double scale);

	// dwg watermark
	bool dwgFileWasSavedByAutodeskSoftware() const;

	// Layer state manager API
	NcDbLayerStateManager* getLayerStateManager() const;

	// Object context manager API
	NcDbObjectContextManager* objectContextManager() const;

	NRX::UInt8 sortEnts() const;
	Nano::ErrorStatus setSortEnts(NRX::UInt8 sortEnts);

	NRX::UInt8 drawOrderCtl() const;
	Nano::ErrorStatus setDrawOrderCtl(NRX::UInt8 val);

	NRX::UInt8 dimAssoc() const;
	Nano::ErrorStatus setDimAssoc(NRX::UInt8 val);

	NRX::UInt8 hideText() const;
	Nano::ErrorStatus setHideText(NRX::UInt8 val);

	NRX::UInt8 haloGap() const;
	Nano::ErrorStatus setHaloGap(NRX::UInt8 val);

	NRX::UInt16 obscuredColor() const;
	Nano::ErrorStatus setObscuredColor(NRX::UInt16 val);

	NRX::UInt8 obscuredLineType() const;
	Nano::ErrorStatus setObscuredLineType(NRX::UInt8 val);

	NRX::UInt8 intersectDisplay() const;
	Nano::ErrorStatus setIntersectDisplay(NRX::UInt8 val);

	NRX::UInt16 intersectColor() const;
	Nano::ErrorStatus setIntersectColor(NRX::UInt16 val);

	NcDbObjectId tablestyle() const;
	Nano::ErrorStatus setTablestyle(NcDbObjectId id);

	Nano::ErrorStatus evaluateFields(int nContext, const NCHAR* name= NULL, NcDbDatabase* database = NULL,
	                                 int* pNumFound = NULL, int* pNumEvaluated = NULL);

	Nano::ErrorStatus getViewportArray(NcDbObjectIdArray& ids, bool bGetPaperspaceVports = true) const;

	Nano::ErrorStatus getVisualStyleList(NcArray< const NCHAR* > &styles_);

	NRX::UInt8 solidHist() const; // 0 or 1(default)
	Nano::ErrorStatus setSolidHist(NRX::UInt8 val);

	NRX::UInt8 showHist() const; // 0, 1(default) or 2
	Nano::ErrorStatus setShowHist(NRX::UInt8 val);

	double psolWidth() const;
	Nano::ErrorStatus setPsolWidth(double width);
	double psolHeight() const;
	Nano::ErrorStatus setPsolHeight(double height);

	NRX::UInt16 loftParam() const;
	Nano::ErrorStatus setLoftParam(NRX::UInt16 flags);
	NRX::UInt8 loftNormals() const;
	Nano::ErrorStatus setLoftNormals(NRX::UInt8 value);
	double loftAng1() const;
	Nano::ErrorStatus setLoftAng1(double ang1);
	double loftAng2() const;
	Nano::ErrorStatus setLoftAng2(double ang2);
	double loftMag1() const;
	Nano::ErrorStatus setLoftMag1(double mag1);
	double loftMag2() const;
	Nano::ErrorStatus setLoftMag2(double mag2);

	double latitude() const;
	Nano::ErrorStatus setLatitude(double lat);
	double longitude() const;
	Nano::ErrorStatus setLongitude(double lng);
	double northDirection() const;
	Nano::ErrorStatus setNorthDirection(double northdir);
	NcDb::TimeZone timeZone() const;
	Nano::ErrorStatus setTimeZone(NcDb::TimeZone tz);
	Nano::ErrorStatus getTimeZoneInfo(NcDb::TimeZone tz, double& offset, NcString& desc) const;
	Nano::ErrorStatus setTimeZoneAsUtcOffset(double offset);

	NRX::UInt8 lightGlyphDisplay() const; // 0 or 1(default)
	Nano::ErrorStatus setLightGlyphDisplay(NRX::UInt8 val);
	NRX::UInt8 tileModeLightSynch() const; // 0 or 1(default)
	Nano::ErrorStatus setTileModeLightSynch(NRX::UInt8 val);

	NcCmColor interfereColor() const;
	Nano::ErrorStatus setInterfereColor(const NcCmColor& color);

	NcDbObjectId interfereObjVisStyle() const;
	Nano::ErrorStatus setInterfereObjVisStyle(NcDbObjectId id);

	NcDbObjectId interfereVpVisStyle() const;
	Nano::ErrorStatus setInterfereVpVisStyle(NcDbObjectId id);

	NcDbObjectId dragVisStyle() const;
	Nano::ErrorStatus setDragVisStyle(NcDbObjectId id);

	NRX::UInt8 cshadow() const;
	Nano::ErrorStatus setCshadow(NRX::UInt8 val);

	double shadowPlaneLocation() const;
	Nano::ErrorStatus setShadowPlaneLocation(double val);

	bool annoAllVisible() const;
	bool annotativeDwg() const;
	NcDbAnnotationScale* cannoscale() const;
	NRX::Int16 cDynDisplayMode() const;
	NcCmTransparency cetransparency() const;
	const NCHAR* classDxfName(const NcRxClass* pClass);
	NRX::UInt32 countEmptyObjects(const NRX::UInt32 flags);
	NcDbObjectId    dataLinkDictionaryId(void) const;
	NRX::Int16 dxeVal() const;
	NRX::UInt32 eraseEmptyObjects(const NRX::UInt32 flags);
	bool geoMarkerVisibility() const;
	Nano::ErrorStatus getDataLinkDictionary(NcDbDictionary*& pDict,
	                                        NcDb::OpenMode mode);
	NcDbDataLinkManager* getDataLinkManager(void) const;
	Nano::ErrorStatus getDimapost(NCHAR*& pOutput) const;
	Nano::ErrorStatus getDimblk(NCHAR*& pOutput) const;
	Nano::ErrorStatus getDimblk1(NCHAR*& pOutput) const;
	Nano::ErrorStatus getDimblk2(NCHAR*& pOutput) const;
	Nano::ErrorStatus getDimpost(NCHAR*& pOutput) const;
	Nano::ErrorStatus getMLeaderStyleDictionary(NcDbDictionary*& pDict,
	                                            NcDb::OpenMode mode);
	Nano::ErrorStatus getPlotSettingsDictionary(NcDbDictionary*& pTable,
	                                            NcDb::OpenMode    mode);
	Nano::ErrorStatus getScaleListDictionary(NcDbDictionary*& pDict,
	                                         NcDb::OpenMode mode);
	NcDbObjectId      getSectionManager (void) const;
	Nano::ErrorStatus getSectionManager (NcDbSectionManager*& pMgr,
	                                     NcDb::OpenMode mode) const;
	NcGsModel*          gsHighlightModel() const;
	NcGsModel*          gsModel() const;
	bool hasClass(const NcRxClass* pClass) const;
	NRX::UInt8 indexctl() const;
	static bool isObjectNonPersistent(NcDbObjectId id);
	NRX::UInt8 layerEval() const;
	NRX::Int16 layerNotify() const;
	NRX::UInt8 lightingUnits() const;
	bool lightsInBlocks() const;
	static Nano::ErrorStatus markObjectNonPersistent(NcDbObjectId id, bool value);
	double mleaderscale() const;
	NcDbObjectId mleaderstyle() const;
	NcDbObjectId  mleaderStyleDictionaryId() const;
	bool msltscale() const;
	double msOleScale() const;
	NRX::Int8 pdfframe() const;
	NRX::Int16 previewType() const;
	Nano::ErrorStatus reclaimMemoryFromErasedObjects(const NcDbObjectIdArray& erasedObjects);
	NcDbObjectId  scaleListDictionaryId();
	Nano::ErrorStatus setAnnoAllVisible(bool allvis);
	Nano::ErrorStatus setAnnotativeDwg(bool anno);
	Nano::ErrorStatus setCannoscale(NcDbAnnotationScale*);
	Nano::ErrorStatus setCDynDisplayMode(NRX::Int16 val);
	Nano::ErrorStatus setCetransparency(const NcCmTransparency& transparency);

	virtual Nano::ErrorStatus setDimadec  (int              v);

	virtual Nano::ErrorStatus setDimalt   (bool             v);
	virtual Nano::ErrorStatus setDimaltd  (int              v);
	virtual Nano::ErrorStatus setDimaltf  (double           v);
	virtual Nano::ErrorStatus setDimaltmzf(double           v);

	virtual Nano::ErrorStatus setDimaltmzs(const NCHAR *    v);

	virtual Nano::ErrorStatus setDimaltrnd(double           v);

	virtual Nano::ErrorStatus setDimalttd (int              v);
	virtual Nano::ErrorStatus setDimalttz (int              v);
	virtual Nano::ErrorStatus setDimaltu  (int              v);
	virtual Nano::ErrorStatus setDimaltz  (int              v);
	virtual Nano::ErrorStatus setDimapost (const NCHAR *    v);
	virtual Nano::ErrorStatus setDimarcsym(int              v);

	virtual Nano::ErrorStatus setDimasz   (double           v);
	virtual Nano::ErrorStatus setDimatfit (int              v);

	virtual Nano::ErrorStatus setDimaunit (int              v);
	virtual Nano::ErrorStatus setDimazin  (int              v);

	virtual Nano::ErrorStatus setDimblk   (NcDbObjectId     v);
	virtual Nano::ErrorStatus setDimblk1  (NcDbObjectId     v);
	virtual Nano::ErrorStatus setDimblk2  (NcDbObjectId     v);

	virtual Nano::ErrorStatus setDimblk   (const NCHAR*    v);
	virtual Nano::ErrorStatus setDimblk1  (const NCHAR*    v);
	virtual Nano::ErrorStatus setDimblk2  (const NCHAR*    v);
	virtual Nano::ErrorStatus setDimldrblk(const NCHAR*    v);

	virtual Nano::ErrorStatus setDimcen   (double           v);
	virtual Nano::ErrorStatus setDimclrd  (const NcCmColor& v);
	virtual Nano::ErrorStatus setDimclre  (const NcCmColor& v);
	virtual Nano::ErrorStatus setDimclrt  (const NcCmColor& v);
	virtual Nano::ErrorStatus setDimdec   (int              v);
	virtual Nano::ErrorStatus setDimdle   (double           v);
	virtual Nano::ErrorStatus setDimdli   (double           v);
	virtual Nano::ErrorStatus setDimdsep  (NCHAR            v);

	virtual Nano::ErrorStatus setDimexe   (double           v);
	virtual Nano::ErrorStatus setDimexo   (double           v);
	Nano::ErrorStatus setDimfit(int fit);
	virtual Nano::ErrorStatus setDimfrac  (int              v);

	virtual Nano::ErrorStatus setDimfxlen (double           v);

	virtual Nano::ErrorStatus setDimfxlenOn (bool           v);

	virtual Nano::ErrorStatus setDimgap   (double           v);
	virtual Nano::ErrorStatus setDimjogang(double           v);

	virtual Nano::ErrorStatus setDimjust  (int              v);
	virtual Nano::ErrorStatus setDimldrblk(NcDbObjectId     v);

	virtual Nano::ErrorStatus setDimlfac  (double           v);
	virtual Nano::ErrorStatus setDimlim   (bool             v);
	virtual Nano::ErrorStatus setDimltex1 (NcDbObjectId     v);

	virtual Nano::ErrorStatus setDimltex2 (NcDbObjectId     v);

	virtual Nano::ErrorStatus setDimltype (NcDbObjectId     v);

	virtual Nano::ErrorStatus setDimlunit (int              v);

	virtual Nano::ErrorStatus setDimlwd   (NcDb::LineWeight v);

	virtual Nano::ErrorStatus setDimlwe   (NcDb::LineWeight v);

	virtual Nano::ErrorStatus setDimmzf   (double           v);

	virtual Nano::ErrorStatus setDimmzs   (const NCHAR *    v);

	virtual Nano::ErrorStatus setDimpost  (const NCHAR *    v);
	virtual Nano::ErrorStatus setDimrnd   (double           v);
	virtual Nano::ErrorStatus setDimsah   (bool             v);
	virtual Nano::ErrorStatus setDimscale (double           v);
	virtual Nano::ErrorStatus setDimsd1   (bool             v);
	virtual Nano::ErrorStatus setDimsd2   (bool             v);
	virtual Nano::ErrorStatus setDimse1   (bool             v);
	virtual Nano::ErrorStatus setDimse2   (bool             v);
	virtual Nano::ErrorStatus setDimsoxd  (bool             v);
	virtual Nano::ErrorStatus setDimtad   (int              v);
	virtual Nano::ErrorStatus setDimtdec  (int              v);
	virtual Nano::ErrorStatus setDimtfac  (double           v);
	virtual Nano::ErrorStatus setDimtfill (int              v);

	virtual Nano::ErrorStatus setDimtfillclr(const NcCmColor& v);

	virtual Nano::ErrorStatus setDimtih   (bool             v);
	virtual Nano::ErrorStatus setDimtix   (bool             v);
	virtual Nano::ErrorStatus setDimtm    (double           v);
	virtual Nano::ErrorStatus setDimtmove (int              v);

	virtual Nano::ErrorStatus setDimtofl  (bool             v);
	virtual Nano::ErrorStatus setDimtoh   (bool             v);
	virtual Nano::ErrorStatus setDimtol   (bool             v);
	virtual Nano::ErrorStatus setDimtolj  (int              v);
	virtual Nano::ErrorStatus setDimtp    (double           v);
	virtual Nano::ErrorStatus setDimtsz   (double           v);
	virtual Nano::ErrorStatus setDimtvp   (double           v);
	virtual Nano::ErrorStatus setDimtxsty (NcDbObjectId     v);
	virtual Nano::ErrorStatus setDimtxt   (double           v);
	virtual Nano::ErrorStatus setDimtxtdirection (bool      v);

	virtual Nano::ErrorStatus setDimtzin  (int              v);
	Nano::ErrorStatus setDimunit(int unit);
	virtual Nano::ErrorStatus setDimupt   (bool             v);
	virtual Nano::ErrorStatus setDimzin   (int              v);
	Nano::ErrorStatus setDxeVal(NRX::Int16 val);
	Nano::ErrorStatus setGeoMarkerVisibility(bool value);
	void                setGsHighlightModel(NcGsModel*);
	void                setGsModel(NcGsModel*);
	Nano::ErrorStatus setIndexctl(NRX::UInt8 val);
	Nano::ErrorStatus setLayerEval(NRX::UInt8 val);
	Nano::ErrorStatus setLayerNotify(NRX::Int16 val);
	Nano::ErrorStatus setLightingUnits(NRX::UInt8 val);
	Nano::ErrorStatus setLightsInBlocks(bool val);
	Nano::ErrorStatus setMLeaderscale(double scale);
	Nano::ErrorStatus setMLeaderstyle(NcDbObjectId objId);
	Nano::ErrorStatus setMsltscale(bool val);
	Nano::ErrorStatus setMsOleScale(double val);
	Nano::ErrorStatus setPdfframe(NRX::Int8 val);
	Nano::ErrorStatus setPreviewType(NRX::Int16 val);
	Nano::ErrorStatus setUpdateThumbnail(NRX::UInt8 val);
	Nano::ErrorStatus setXclipFrame(NRX::UInt8 disp);
	Nano::ErrorStatus updateDataLink    (NcDb::UpdateDirection nDir,
	                                     NcDb::UpdateOption nOption);
	NRX::UInt8 updateThumbnail() const;
	NRX::UInt8 xclipFrame() const;

public:
	OdDbDatabase* native() const;
	OdDbDatabase* detach();

public:
	static NcDbDatabase* attach(const OdDbDatabase* _database);

private:
	// Set platform object ownership
	// Used in methods that return newly created database (e.g. wblock())

	void setToNativeOwner();

protected:
	mutable NcTransactionManager* m_pTransactionManager;
	mutable NcFileDependencyManager* m_pFileDependencyManager;

private:
	bool m_owner;
};

//////////////////////////////////////////////////////////////////////////
//
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSaveAs2004(NcDbDatabase* database_, const NCHAR* file_);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSaveAs2000(NcDbDatabase* database_, const NCHAR* file_);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSaveAsR14(NcDbDatabase* database_, const NCHAR* file_);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbDxfOutAs2004(NcDbDatabase* database_, const NCHAR* file_,
                                                    const int precision = 16);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbDxfOutAs2000(NcDbDatabase* database_, const NCHAR* file_,
                                                    const int precision = 16);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbDxfOutAsR12(NcDbDatabase* database_, const NCHAR* file_,
                                                   const int precision = 16);

///////////////////////////////////////////////////////////////////////////////////////////////////
// xref functionality
NRXDBGATE_EXPORT Nano::ErrorStatus ncedXrefAttach(const NCHAR* path, const NCHAR* name, NcDbObjectId* btrid = NULL,
                                                  NcDbObjectId* refid = NULL, const NcGePoint3d* insert = NULL,
                                                  const NcGeScale3d* scale = NULL, const double* angle = NULL,
                                                  const bool quiet = true, NcDbDatabase* database = NULL,
                                                  const wchar_t* password = NULL);
NRXDBGATE_EXPORT Nano::ErrorStatus ncedXrefOverlay(const NCHAR* path, const NCHAR* name, NcDbObjectId* btrid = NULL,
                                                   NcDbObjectId* refid = NULL, const NcGePoint3d* insert = NULL,
                                                   const NcGeScale3d* scale = NULL, const double* angle = NULL,
                                                   const bool quiet = true, NcDbDatabase* database = NULL,
                                                   const wchar_t* password = NULL);
NRXDBGATE_EXPORT Nano::ErrorStatus ncedXrefUnload(const NCHAR* name, const bool quiet = true,
                                                  NcDbDatabase* database = NULL);
NRXDBGATE_EXPORT Nano::ErrorStatus ncedXrefDetach(const NCHAR* name, const bool quiet = true,
                                                  NcDbDatabase* database = NULL);
NRXDBGATE_EXPORT Nano::ErrorStatus ncedXrefReload(const NCHAR* name, const bool quiet = true,
                                                  NcDbDatabase* database = NULL);
NRXDBGATE_EXPORT Nano::ErrorStatus ncedXrefBind(const NCHAR* name, const bool bind = false, const bool quiet = true,
                                                NcDbDatabase* database = NULL);
NRXDBGATE_EXPORT Nano::ErrorStatus ncedXrefCreateBlockname(const NCHAR* path, NCHAR*& name);
NRXDBGATE_EXPORT Nano::ErrorStatus ncedXrefReload(const NcDbObjectIdArray& ids, bool quiet = true,
                                                  NcDbDatabase* database = NULL);
NRXDBGATE_EXPORT Nano::ErrorStatus ncedXrefXBind(const NcDbObjectIdArray symbolIds, const bool quiet = true,
                                                 NcDbDatabase* database = NULL);
NRXDBGATE_EXPORT Nano::ErrorStatus ncedXrefResolve(NcDbDatabase* database, const bool quiet = true);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbObject
class OdDbObject;
class OdRxObjectPtr;
class NRXDBGATE_EXPORT NcDbObject : public NcGiDrawable
{
public:
	NCRX_DECLARE_MEMBERS(NcDbObject);

protected:
	NcDbObject();

public:
	NcDbObject(OdRxObject* _object);

public:
	~NcDbObject();

public:
	typedef NcDbObject  wrapper_class;
	typedef OdDbObject  native_class;

	// NcRxObject
public:
	virtual NcRxObject* clone() const override;
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source) override;

	// NcGiDrawable interface
public:
	virtual NRX::Boolean isPersistent() const override;
	virtual NcDbObjectId id() const override;
	virtual void setGsNode(NcGsNode* node) override;
	virtual NcGsNode* gsNode() const override;

public:
	NcDbObjectId objectId() const;
	NcDbObjectId ownerId() const;

	virtual Nano::ErrorStatus setOwnerId(NcDbObjectId id);

	void getNcDbHandle(NcDbHandle& handle) const;

	NcDbDatabase* database() const;

	Nano::ErrorStatus createExtensionDictionary();
	NcDbObjectId extensionDictionary() const;
	Nano::ErrorStatus releaseExtensionDictionary();

	Nano::ErrorStatus upgradeOpen();
	Nano::ErrorStatus upgradeFromNotify(NRX::Boolean& writable);
	Nano::ErrorStatus downgradeOpen();
	Nano::ErrorStatus downgradeToNotify(NRX::Boolean writable);
	virtual Nano::ErrorStatus subOpen(NcDb::OpenMode mode);

	Nano::ErrorStatus cancel();
	virtual Nano::ErrorStatus subCancel();

	Nano::ErrorStatus close();
	Nano::ErrorStatus closeAndPage(NRX::Boolean onlyWhenClean = true);
	virtual Nano::ErrorStatus subClose();

	Nano::ErrorStatus erase(NRX::Boolean erasing = true);
	virtual Nano::ErrorStatus subErase(NRX::Boolean erasing);

	Nano::ErrorStatus handOverTo(NcDbObject* newObject, NRX::Boolean keepXData = true,
	                             NRX::Boolean keepExtDict = true);
	virtual Nano::ErrorStatus subHandOverTo(NcDbObject* newObject);

	Nano::ErrorStatus swapIdWith(NcDbObjectId otherId, NRX::Boolean swapXdata = false,
	                             NRX::Boolean swapExtDict = false);
	virtual Nano::ErrorStatus subSwapIdWith(NcDbObjectId otherId, NRX::Boolean swapXdata = false,
	                                        NRX::Boolean swapExtDict = false);

	virtual Nano::ErrorStatus swapReferences(const NcDbIdMapping& map);

	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo);

	Nano::ErrorStatus dwgIn(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);

	Nano::ErrorStatus dwgOut(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;

	Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	Nano::ErrorStatus dxfOut(NcDbDxfFiler* filer, NRX::Boolean allXdFlag, NRX::uchar* regAppTable) const;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;

	virtual NcDb::DuplicateRecordCloning mergeStyle() const;

	virtual resbuf* xData(const NCHAR* application = NULL) const;
	virtual Nano::ErrorStatus setXData(const resbuf* xdata);
	Nano::ErrorStatus xDataTransformBy(const NcGeMatrix3d& xform);

	Nano::ErrorStatus setBinaryData(const NCHAR* key, long size, const char* data);
	Nano::ErrorStatus getBinaryData(const NCHAR* key, long& size, char*& data) const;

	NRX::Boolean isEraseStatusToggled() const;
	NRX::Boolean isErased() const;
	NRX::Boolean isReadEnabled() const;
	NRX::Boolean isWriteEnabled() const;
	NRX::Boolean isNotifyEnabled() const;
	NRX::Boolean isModified() const;
	NRX::Boolean isModifiedXData() const;
	NRX::Boolean isModifiedGraphics() const;
	NRX::Boolean isNewObject() const;
	NRX::Boolean isNotifying() const;
	NRX::Boolean isUndoing() const;
	NRX::Boolean isCancelling() const;
	NRX::Boolean isReallyClosing() const;
	NRX::Boolean isTransactionResident() const;

	NRX::Boolean isAProxy() const;

	void assertReadEnabled() const;
	void assertWriteEnabled(NRX::Boolean autoUndo = true, NRX::Boolean recordModified = true);
	void assertNotifyEnabled() const;

	bool isUndoRecordingDisabled() const;
	void disableUndoRecording(NRX::Boolean disable);
	NcDbDwgFiler* undoFiler();
	virtual Nano::ErrorStatus applyPartialUndo(NcDbDwgFiler* filer, NcRxClass* rxclass);

	void addReactor(NcDbObjectReactor* reactor) const;
	void removeReactor(NcDbObjectReactor* reactor) const;
	virtual void addPersistentReactor(NcDbObjectId id);
	virtual Nano::ErrorStatus removePersistentReactor(NcDbObjectId id);
	bool hasPersistentReactor(NcDbObjectId id) const;
	NcDbVoidPtrArray* reactors();
	const NcDbVoidPtrArray* reactors() const;

	virtual void recvPropagateModify(const NcDbObject* object);
	virtual void xmitPropagateModify() const;

	virtual Nano::ErrorStatus deepClone(NcDbObject* owner, NcDbObject*& lone, NcDbIdMapping& map,
	                                    NRX::Boolean primary = true) const sealed;
	virtual Nano::ErrorStatus wblockClone(NcRxObject* owner, NcDbObject*& lone, NcDbIdMapping& map,
	                                      NRX::Boolean primary = true) const sealed;

	void setNcDbObjectIdsInFlux();
	NRX::Boolean isNcDbObjectIdsInFlux() const;

	virtual void cancelled(const NcDbObject* object);
	virtual void copied(const NcDbObject* object, const NcDbObject* newObj);
	virtual void erased(const NcDbObject* object, NRX::Boolean pErasing = true);
	virtual void goodbye(const NcDbObject* object);
	virtual void openedForModify(const NcDbObject* object);
	virtual void modified(const NcDbObject* object);
	virtual void subObjModified(const NcDbObject* object, const NcDbObject* sub);
	virtual void modifyUndone(const NcDbObject* object);
	virtual void modifiedXData(const NcDbObject* object);
	virtual void unappended(const NcDbObject* object);
	virtual void reappended(const NcDbObject* object);
	virtual void objectClosed(const NcDbObjectId id);
	virtual void modifiedGraphics(const NcDbEntity* entity);

	bool hasSaveVersionOverride();
	void setHasSaveVersionOverride(bool set);

	virtual Nano::ErrorStatus getObjectSaveVersion(const NcDbDwgFiler* filer, NcDb::NcDbDwgVersion& major,
	                                               NcDb::MaintenanceReleaseVersion& minor);
	virtual Nano::ErrorStatus getObjectSaveVersion(const NcDbDxfFiler* filer, NcDb::NcDbDwgVersion& major,
	                                               NcDb::MaintenanceReleaseVersion& minor);
	Nano::ErrorStatus getObjectBirthVersion(NcDb::NcDbDwgVersion& major, NcDb::MaintenanceReleaseVersion& minor);

	virtual Nano::ErrorStatus decomposeForSave(NcDb::NcDbDwgVersion major, NcDbObject*& replaceObj,
	                                           NcDbObjectId& replaceId, NRX::Boolean& exchangeXData);

	virtual NcGiDrawable* drawable();

	virtual Nano::ErrorStatus getClassID(CLSID* clsid) const sealed;

	bool hasFields(void) const;
	Nano::ErrorStatus getField(const NCHAR* name, NcDbObjectId& id) const;
	Nano::ErrorStatus getField(const NCHAR* name, NcDbField*& field, NcDb::OpenMode mode) const;

	virtual Nano::ErrorStatus setField(const NCHAR* name, NcDbField* field, NcDbObjectId& id);

	virtual Nano::ErrorStatus removeField(NcDbObjectId id);
	virtual Nano::ErrorStatus removeField(const NCHAR* name, NcDbObjectId& id);
	virtual Nano::ErrorStatus removeField(const NCHAR* name);
	NcDbObjectId getFieldDictionary(void) const;
	Nano::ErrorStatus getFieldDictionary(NcDbDictionary*& dict, NcDb::OpenMode mode) const;

	// NcGiDrawable interface
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	virtual Nano::ErrorStatus subDeepClone(NcDbObject* owner, NcDbObject*& lone, NcDbIdMapping& map,
	                                       NRX::Boolean primary = true) const;
	virtual Nano::ErrorStatus subWblockClone(NcRxObject* owner, NcDbObject*& lone, NcDbIdMapping& map,
	                                         NRX::Boolean primary = true) const;

protected:
	virtual OdRxObject* GetNativeObject() const;

public:
	OdDbObject* native() const;

public:
	static NcDbObject* attach(const OdDbObject* _object);

protected:
	struct NcDbObjectData;
	NcDbObjectData* _data;
	NcDbVoidPtrArray*     _reactors();
	OdRxObjectPtr& _cdptr();
	int& _trancount();

	friend class NcTransaction;
	friend class NcDbTransactionManager;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ncdbOpenNcDbObject
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOpenNcDbObject(NcDbObject*& object, NcDbObjectId id, NcDb::OpenMode mode,
                                                      const NcRxClass* rxclass, bool open_erased = false);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOpenNcDbObject(NcDbObject*& object, NcDbObjectId id, NcDb::OpenMode mode,
                                                      bool open_erased = false);
NRXDBGATE_EXPORT Nano::ErrorStatus ncutSetDatabase(NcDbObject* object, const NcDbDatabase* database);
template < class _DBOBJ >
inline Nano::ErrorStatus ncdbOpenObject(_DBOBJ*& object, NcDbObjectId id, NcDb::OpenMode mode, bool open_erased = false)
{
	return ncdbOpenNcDbObject((NcDbObject*&)object, id, mode, _DBOBJ::desc(), open_erased);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbXrecord
class OdDbXrecord;
class NRXDBGATE_EXPORT NcDbXrecord : public NcDbObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbXrecord);

	typedef NcDbXrecord  wrapper_class;
	typedef OdDbXrecord  native_class;

public:
	NcDbXrecord();

	NcDbXrecord(OdRxObject* _object);

	virtual void setMergeStyle(NcDb::DuplicateRecordCloning style) ; // +Overload
	virtual NcDb::DuplicateRecordCloning mergeStyle() const; // +Overload

// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

public:
	Nano::ErrorStatus rbChain(resbuf** rb, NcDbDatabase* db = NULL) const;
	Nano::ErrorStatus setFromRbChain(const resbuf& rb, NcDbDatabase* db = NULL);

	bool isXlateReferences() const;
	void setXlateReferences(bool translate);
	virtual Nano::ErrorStatus subClose();

public:
	OdDbXrecord* native() const;

protected:
	virtual OdRxObject* GetNativeObject() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDictionaryIterator
class OdDbDictionaryIterator;
class NRXDBGATE_EXPORT NcDbDictionaryIterator : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbDictionaryIterator);

	NcDbDictionaryIterator(OdRxObject* _object);

public:
	typedef NcDbDictionaryIterator  wrapper_class;
	typedef OdDbDictionaryIterator  native_class;

public:
	virtual const NCHAR* name() const;

	virtual Nano::ErrorStatus getObject(NcDbObject*& object, NcDb::OpenMode mode);
	virtual NcDbObjectId objectId() const;

	virtual bool done() const;
	virtual bool next();
	virtual bool setPosition(NcDbObjectId id);

public:
	OdDbDictionaryIterator* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDictionary
class OdDbDictionary;
class NRXDBGATE_EXPORT NcDbDictionary : public NcDbObject
{
	NCDB_DECLARE_MEMBERS(NcDbDictionary);

public:
	NcDbDictionary();

	NcDbDictionary(OdRxObject* _object);

public:
	typedef NcDbDictionary  wrapper_class;
	typedef OdDbDictionary  native_class;

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;

	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual void goodbye(const NcDbObject* object) override;
	virtual void erased(const NcDbObject* object, NRX::Boolean pErasing = NRX::kTrue) override;

	virtual NcDb::DuplicateRecordCloning mergeStyle() const override;

	virtual Nano::ErrorStatus applyPartialUndo(NcDbDwgFiler* filer, NcRxClass* rxclass) override;

	virtual Nano::ErrorStatus decomposeForSave(NcDb::NcDbDwgVersion ver, NcDbObject*& replaceObj,
	                                           NcDbObjectId& replaceId, NRX::Boolean& exchangeXData) override;

public:
	virtual void setMergeStyle(NcDb::DuplicateRecordCloning style);

	Nano::ErrorStatus getAt(const NCHAR* entryName, NcDbObject*& entryObj, NcDb::OpenMode mode) const;
	Nano::ErrorStatus getAt(const NCHAR* entryName, NcDbObjectId& entryObj) const;

	Nano::ErrorStatus nameAt(NcDbObjectId objId, NCHAR*& name) const;
	Nano::ErrorStatus nameAt(NcDbObjectId objId, NcString& name) const;

	bool has(const NCHAR* entryName) const;
	bool has(NcDbObjectId objId) const;
	NRX::UInt32 numEntries() const;

	Nano::ErrorStatus remove(const NCHAR* key);
	Nano::ErrorStatus remove(const NCHAR* key, NcDbObjectId& returnId);
	Nano::ErrorStatus remove(NcDbObjectId objId);

	bool setName(const NCHAR* oldName, const NCHAR* newName);
	Nano::ErrorStatus setAt(const NCHAR* srchKey, NcDbObject* newValue, NcDbObjectId& retObjId);

	bool isTreatElementsAsHard() const;
	void setTreatElementsAsHard(bool doIt);

	NcDbDictionaryIterator* newIterator() const;

public:
	OdDbDictionary* native() const;

	// NcDbObject Protocol
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

protected:
	virtual OdRxObject* GetNativeObject() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDictionaryWithDefault
class OdDbDictionaryWithDefault;
class NRXDBGATE_EXPORT NcDbDictionaryWithDefault : public NcDbDictionary
{
	NCDB_DECLARE_MEMBERS(NcDbDictionaryWithDefault);

public:
	NcDbDictionaryWithDefault();

	NcDbDictionaryWithDefault(OdRxObject* _object);

public:
	typedef NcDbDictionaryWithDefault  wrapper_class;
	typedef OdDbDictionaryWithDefault  native_class;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

public:
	Nano::ErrorStatus setDefaultId(const NcDbObjectId& id);
	NcDbObjectId defaultId() const;

public:
	OdDbDictionaryWithDefault* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSymbolTable
class OdDbSymbolTable;
class NRXDBGATE_EXPORT NcDbSymbolTable : public NcDbObject
{
	NCDB_DECLARE_MEMBERS(NcDbSymbolTable);

public:
	typedef NcDbSymbolTable        wrapper_class;
	typedef OdDbSymbolTable        native_class;

	typedef NcDbSymbolTableRecord  RecordType;

public:
	NcDbSymbolTable();

	NcDbSymbolTable(OdRxObject* _object);

	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbSymbolTableRecord*& record, NcDb::OpenMode mode,
	                        bool open_erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& recid, bool open_erased = false) const;

	bool has(const NCHAR* name) const;
	bool has(NcDbObjectId recid) const;

	Nano::ErrorStatus newIterator(NcDbSymbolTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbSymbolTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbSymbolTableRecord* record);

public:
	OdDbSymbolTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbBlockTable
class OdDbBlockTable;
class NRXDBGATE_EXPORT NcDbBlockTable : public NcDbSymbolTable
{
	NCDB_DECLARE_MEMBERS(NcDbBlockTable);

public:
	typedef OdDbBlockTable        wrapper_class;
	typedef OdDbBlockTable        native_class;

	typedef NcDbBlockTableRecord  RecordType;

	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload

public:
	NcDbBlockTable();

	NcDbBlockTable(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbBlockTableRecord*& record, NcDb::OpenMode mode,
	                        bool erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& recid, bool erased = false) const;

	bool has(const NCHAR* name) const;
	bool has(NcDbObjectId id) const;

	Nano::ErrorStatus newIterator(NcDbBlockTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbBlockTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbBlockTableRecord* record);

public:
	OdDbBlockTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbLayerTable
class OdDbLayerTable;
class NRXDBGATE_EXPORT NcDbLayerTable : public NcDbSymbolTable
{
public:
	NCRX_DECLARE_MEMBERS(NcDbLayerTable);

	typedef NcDbLayerTable        wrapper_class;
	typedef OdDbLayerTable        native_class;

	typedef NcDbLayerTableRecord  RecordType;

public:
	NcDbLayerTable();

	NcDbLayerTable(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbLayerTableRecord*& record, NcDb::OpenMode mode,
	                        bool open_erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& recid, bool getErased = false) const;

	Nano::ErrorStatus newIterator(NcDbLayerTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbLayerTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbLayerTableRecord* record);

	void generateUsageData();
	Nano::ErrorStatus getUnreconciledLayers(NcDbObjectIdArray& idArray) const;
	//bool has  (const NCHAR* name) const;
	bool hasUnreconciledLayers() const;

public:
	OdDbLayerTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbLinetypeTable
class OdDbLinetypeTable;
class NRXDBGATE_EXPORT NcDbLinetypeTable : public NcDbSymbolTable
{
public:
	NCRX_DECLARE_MEMBERS(NcDbLinetypeTable);

	typedef NcDbLinetypeTable        wrapper_class;
	typedef OdDbLinetypeTable        native_class;

	typedef NcDbLinetypeTableRecord  RecordType;

public:
	NcDbLinetypeTable();

	NcDbLinetypeTable(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbLinetypeTableRecord*& record, NcDb::OpenMode mode,
	                        bool erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& recid, bool erased = false) const;

	Nano::ErrorStatus newIterator(NcDbLinetypeTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbLinetypeTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbLinetypeTableRecord* record);

public:
	OdDbLinetypeTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbViewTable
class OdDbViewTable;
class NRXDBGATE_EXPORT NcDbViewTable : public NcDbSymbolTable
{
public:
	NCRX_DECLARE_MEMBERS(NcDbViewTable);

	typedef NcDbViewTable        wrapper_class;
	typedef OdDbViewTable        native_class;

	typedef NcDbViewTableRecord  RecordType;

public:
	NcDbViewTable();

	NcDbViewTable(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbViewTableRecord*& record, NcDb::OpenMode mode,
	                        bool open_erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& recid, bool getErased = false) const;

	Nano::ErrorStatus newIterator(NcDbViewTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbViewTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbViewTableRecord* record);

public:
	OdDbViewTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbUCSTable
class OdDbUCSTable;
class NRXDBGATE_EXPORT NcDbUCSTable : public NcDbSymbolTable
{
public:
	NCRX_DECLARE_MEMBERS(NcDbUCSTable);

	typedef NcDbUCSTable        wrapper_class;
	typedef OdDbUCSTable        native_class;

	typedef NcDbUCSTableRecord  RecordType;

public:
	NcDbUCSTable();

	NcDbUCSTable(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbUCSTableRecord*& record, NcDb::OpenMode mode,
	                        bool open_erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& recid, bool getErased = false) const;

	Nano::ErrorStatus newIterator(NcDbUCSTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbUCSTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbUCSTableRecord* record);

public:
	OdDbUCSTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDimStyleTable
class OdDbDimStyleTable;
class NRXDBGATE_EXPORT NcDbDimStyleTable : public NcDbSymbolTable
{
public:
	NCRX_DECLARE_MEMBERS(NcDbDimStyleTable);

	typedef NcDbDimStyleTable        wrapper_class;
	typedef OdDbDimStyleTable        native_class;

	typedef NcDbDimStyleTableRecord  RecordType;

public:
	NcDbDimStyleTable(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbDimStyleTableRecord*& record, NcDb::OpenMode mode,
	                        bool erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& recid, bool erased = false) const;

	Nano::ErrorStatus newIterator(NcDbDimStyleTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbDimStyleTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbDimStyleTableRecord* record);

public:
	OdDbDimStyleTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbTextStyleTable
class OdDbTextStyleTable;
class NRXDBGATE_EXPORT NcDbTextStyleTable : public NcDbSymbolTable
{
public:
	NCRX_DECLARE_MEMBERS(NcDbTextStyleTable);

	typedef NcDbTextStyleTable        wrapper_class;
	typedef OdDbTextStyleTable        native_class;

	typedef NcDbTextStyleTableRecord  RecordType;

public:
	NcDbTextStyleTable();
	NcDbTextStyleTable(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbTextStyleTableRecord*& record, NcDb::OpenMode mode,
	                        bool open_erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& recid, bool getErased = false) const;

	Nano::ErrorStatus newIterator(NcDbTextStyleTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbTextStyleTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbTextStyleTableRecord* record);

public:
	OdDbTextStyleTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbAbstractViewTable
class OdDbAbstractViewTable;
class NRXDBGATE_EXPORT NcDbAbstractViewTable : public NcDbSymbolTable
{
public:
	NCRX_DECLARE_MEMBERS(NcDbAbstractViewTable);

	typedef NcDbAbstractViewTable        wrapper_class;
	typedef OdDbAbstractViewTable        native_class;

	typedef NcDbAbstractViewTableRecord  RecordType;

public:
	NcDbAbstractViewTable(OdRxObject* _object);

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbAbstractViewTableRecord*& record, NcDb::OpenMode mode,
	                        bool erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& id, bool erased = false) const;

	Nano::ErrorStatus newIterator(NcDbAbstractViewTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbAbstractViewTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbAbstractViewTableRecord* record);

public:
	OdDbAbstractViewTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbViewportTable
class OdDbViewportTable;
class NRXDBGATE_EXPORT NcDbViewportTable : public NcDbAbstractViewTable
{
public:
	NCRX_DECLARE_MEMBERS(NcDbViewportTable);

	typedef NcDbViewportTable        wrapper_class;
	typedef OdDbViewportTable        native_class;

	typedef NcDbViewportTableRecord  RecordType;

public:
	NcDbViewportTable(OdRxObject* _object);

	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subClose() override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbViewportTableRecord*& record, NcDb::OpenMode mode,
	                        bool open_erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& recid, bool getErased = false) const;

	Nano::ErrorStatus newIterator(NcDbViewportTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbViewportTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbViewportTableRecord* record);

public:
	OdDbViewportTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbRegAppTable
class OdDbRegAppTable;
class NRXDBGATE_EXPORT NcDbRegAppTable : public NcDbSymbolTable
{
public:
	NCRX_DECLARE_MEMBERS(NcDbRegAppTable);

	typedef NcDbRegAppTable        wrapper_class;
	typedef OdDbRegAppTable        native_class;

	typedef NcDbRegAppTableRecord  RecordType;

public:
	NcDbRegAppTable(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbRegAppTableRecord*& record, NcDb::OpenMode mode,
	                        bool open_erased = false) const;
	Nano::ErrorStatus getAt(const NCHAR* name, NcDbObjectId& recid, bool getErased = false) const;

	Nano::ErrorStatus newIterator(NcDbRegAppTableIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus add(NcDbRegAppTableRecord* record);
	Nano::ErrorStatus add(NcDbObjectId& id, NcDbRegAppTableRecord* record);

public:
	OdDbRegAppTable* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSymbolTableRecord
class OdDbSymbolTableRecord;
class NRXDBGATE_EXPORT NcDbSymbolTableRecord : public NcDbObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbSymbolTableRecord);

	typedef NcDbSymbolTableRecord  wrapper_class;
	typedef OdDbSymbolTableRecord  native_class;

	typedef NcDbSymbolTable        TableType;

public:
	NcDbSymbolTableRecord();

	NcDbSymbolTableRecord(OdRxObject* _object);

	// NcRxObject
public:
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;
	virtual Nano::ErrorStatus subSwapIdWith(NcDbObjectId otherId, NRX::Boolean swapXdata = false,
	                                        NRX::Boolean swapExtDict = false) override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus getName(NCHAR*& name) const;
	Nano::ErrorStatus getName(const NCHAR*& name) const;
	Nano::ErrorStatus getName(NcString & sName) const;

	Nano::ErrorStatus setName(const NCHAR* name);

	bool isDependent() const;

	bool isResolved() const;

public:
	OdDbSymbolTableRecord* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbBlockTableRecord
class OdDbBlockTableRecord;
class OdBinaryData;
class OdDbEntity;
template class NRXDBGATE_EXPORT NcArray< OdDbEntity* >;
class NRXDBGATE_EXPORT NcDbBlockTableRecord : public NcDbSymbolTableRecord
{
	NCDB_DECLARE_MEMBERS(NcDbBlockTableRecord);

public:
	typedef NcDbBlockTableRecord  wrapper_class;
	typedef OdDbBlockTableRecord  native_class;

	typedef NcDbBlockTable        TableType;
	typedef OdBinaryData          PreviewIcon;

public:
	NcDbBlockTableRecord();

	NcDbBlockTableRecord(OdRxObject* _object);

	virtual ~NcDbBlockTableRecord();

	// OdRxObject
public:
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source) override;

	// NcGiDrawable interface
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus applyPartialUndo(NcDbDwgFiler* filer, NcRxClass* rxclass) override;

	virtual NcGiDrawable* drawable() override;

	virtual Nano::ErrorStatus subClose() override;
	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;
	virtual Nano::ErrorStatus subHandOverTo(NcDbObject* newObject) override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	virtual Nano::ErrorStatus assumeOwnershipOf(NcArray< NcDbObjectId >& ents);

	Nano::ErrorStatus appendNcDbEntity(NcDbEntity* entity);
	Nano::ErrorStatus appendNcDbEntity(NcDbObjectId& output, NcDbEntity* entity);

	Nano::ErrorStatus newIterator(NcDbBlockTableRecordIterator*& iterator, bool at_beginning = true,
	                              bool skip_deleted = true) const;

	Nano::ErrorStatus comments(NCHAR*& comments) const;
	Nano::ErrorStatus comments(const NCHAR*& string) const;
	Nano::ErrorStatus setComments(const NCHAR* comments);

	Nano::ErrorStatus pathName(NCHAR*& path) const;
	Nano::ErrorStatus pathName(const NCHAR*& path) const;
	Nano::ErrorStatus setPathName(const NCHAR* path);

	NcGePoint3d origin() const;
	Nano::ErrorStatus setOrigin(const NcGePoint3d& point);

	Nano::ErrorStatus openBlockBegin(NcDbBlockBegin*& begin, NcDb::OpenMode mode);
	Nano::ErrorStatus openBlockEnd(NcDbBlockEnd*& end, NcDb::OpenMode mode);

	bool hasAttributeDefinitions() const;

	bool hasPreviewIcon() const;
	Nano::ErrorStatus getPreviewIcon(PreviewIcon& previewIcon) const;
	Nano::ErrorStatus setPreviewIcon(const PreviewIcon& previewIcon);

	bool isAnonymous() const;

	bool isFromExternalReference() const;

	bool isFromOverlayReference() const;

	bool isLayout() const;

	NcDbObjectId getLayoutId() const;
	Nano::ErrorStatus setLayoutId(NcDbObjectId id);

	Nano::ErrorStatus getBlockReferenceIds(NcDbObjectIdArray& ids, bool direct = true, bool force = false) const;

	Nano::ErrorStatus getErasedBlockReferenceIds(NcDbObjectIdArray& ids);

	Nano::ErrorStatus getSortentsTable(NcDbSortentsTable*& pSortents, NcDb::OpenMode openMode,
	                                   bool createIfNecessary = false);

	NcDbDatabase* xrefDatabase(bool inc = false) const;

	bool isUnloaded() const;
	Nano::ErrorStatus setIsUnloaded(bool unloaded);

	NcDb::XrefStatus xrefStatus() const;

	// Block scaling and exploding control

	enum BlockScaling
	{
		kAny,
		kUniform
	};

	NcDbBlockTableRecord::BlockScaling blockScaling() const;
	Nano::ErrorStatus setBlockScaling(NcDbBlockTableRecord::BlockScaling scaling);

	Nano::ErrorStatus setExplodable(bool explodable);
	bool explodable() const;

	Nano::ErrorStatus setBlockInsertUnits(NcDb::UnitsValue units);
	NcDb::UnitsValue blockInsertUnits() const;

	Nano::ErrorStatus addAnnoScalestoBlkRefs(const bool bScale = false);
	virtual Nano::ErrorStatus decomposeForSave(NcDb::NcDbDwgVersion ver,
	                                           NcDbObject*& replaceObj,
	                                           NcDbObjectId& replaceId,
	                                           NRX::Boolean& exchangeXData);
	NcGsNode*         gsNode() const;
	Nano::ErrorStatus newBlockReferenceIdIterator(
	    NcDbBlockReferenceIdIterator*& pIter) const;
	Nano::ErrorStatus postProcessAnnotativeBTR(int& stripCnt, const bool bqueryOnly = false,
	                                           const bool bScale = true);
	void              setGsNode(NcGsNode* pNode);

public:
	OdDbBlockTableRecord* native() const;

protected:
	mutable NcString *m_pathName;
	NcArray< OdDbEntity* > m_arrEntities;        // массив указателей на не полностью обработанные объекты
	friend class NcDbBlockTable;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcFileDependencyManager
class NRXDBGATE_EXPORT NcFileDependencyManager {
public:
	virtual ~NcFileDependencyManager() {};
	virtual NRX::Int32 createEntry(const NCHAR *feature,
		const NCHAR *fullFileName,
		const bool affectsGraphics = false,
		const bool noIncrement = false) = 0;


	virtual Nano::ErrorStatus getEntry(const NCHAR *feature,
		const NCHAR *fullFileName,
		NcFileDependencyInfo *&fileInfo, 
		const bool useCachedInfo = false) = 0;

	virtual Nano::ErrorStatus getEntry(const NRX::Int32 index,
		NcFileDependencyInfo *&fileInfo, 
		const bool useCachedInfo = false) = 0;

	virtual Nano::ErrorStatus updateEntry(const NCHAR *feature,
		const NCHAR *fullFileName) = 0;

	virtual Nano::ErrorStatus updateEntry(const NRX::Int32 index) = 0;

	virtual Nano::ErrorStatus eraseEntry(const NCHAR *feature,
		const NCHAR *fullFileName,
		const bool forceRemove=false) = 0;

	virtual Nano::ErrorStatus eraseEntry(const NRX::Int32 index,
		const bool forceRemove=false) = 0;

	virtual NRX::Int32 countEntries() = 0;

	virtual void iteratorInitialize(const NCHAR *feature = NULL, 
		const bool modifiedOnly = false,
		const bool affectsGraphicsOnly = false,
		const bool walkXRefTree = false) = 0;

	virtual NRX::Int32 iteratorNext() = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbLayerTableRecord
class OdDbLayerTableRecord;
class NRXDBGATE_EXPORT NcDbLayerTableRecord : public NcDbSymbolTableRecord
{
	NCDB_DECLARE_MEMBERS(NcDbLayerTableRecord);

public:
	typedef NcDbLayerTableRecord  wrapper_class;
	typedef OdDbLayerTableRecord  native_class;

	typedef NcDbLayerTable        TableType;

public:
	NcDbLayerTableRecord();

	NcDbLayerTableRecord(OdRxObject* _object);

	// NcGiDrawable interface
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual NcGiDrawable* drawable() override;

	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	bool isFrozen() const;
	Nano::ErrorStatus setIsFrozen(bool frozen);

	bool isOff() const;
	void setIsOff(bool off);

	bool VPDFLT() const;
	void setVPDFLT(bool flag);

	bool isLocked() const;
	void setIsLocked(bool locked);

	NcCmColor color() const;
	void setColor(const NcCmColor& color);

	NcCmEntityColor entityColor(void) const;

	NcCmTransparency transparency(void) const;
	Nano::ErrorStatus setTransparency(const NcCmTransparency& transparency);

	NcDbObjectId linetypeObjectId() const;

	void setLinetypeObjectId(NcDbObjectId id);

	NcDbObjectId materialId() const;
	Nano::ErrorStatus setMaterialId(NcDbObjectId id);

	enum { kDxfLayerPlotBit = NcDb::kDxfBool };

	bool isPlottable() const;
	Nano::ErrorStatus setIsPlottable(bool plot);

	NcDb::LineWeight lineWeight() const;
	Nano::ErrorStatus setLineWeight(NcDb::LineWeight weight);

	NCHAR* plotStyleName() const;
	NcDbObjectId plotStyleNameId() const;

	Nano::ErrorStatus setPlotStyleName(const NCHAR* name);
	Nano::ErrorStatus setPlotStyleName(const NcDbObjectId& id);

	bool isInUse() const;

	NCHAR* description() const;
	Nano::ErrorStatus setDescription(const NCHAR* description);

	bool isHidden() const;
	Nano::ErrorStatus setIsHidden(bool on);

	static bool isHidden(NcDbObjectId id);

	NcGsNode*         gsNode() const;
	bool              hasAnyOverrides() const;
	bool              hasOverrides(const NcDbObjectId& viewportId) const;
	bool              isReconciled() const;
	Nano::ErrorStatus removeAllOverrides();
	Nano::ErrorStatus removeColorOverride(const NcDbObjectId& viewportId);
	Nano::ErrorStatus removeLinetypeOverride(const NcDbObjectId& viewportId);
	Nano::ErrorStatus removeLineWeightOverride(const NcDbObjectId& viewportId);
	Nano::ErrorStatus removePlotStyleOverride(const NcDbObjectId& viewportId);
	Nano::ErrorStatus removeTransparencyOverride(const NcDbObjectId& viewportId);
	Nano::ErrorStatus removeViewportOverrides(const NcDbObjectId& viewportId);
	void              setGsNode(NcGsNode* pNode);
	Nano::ErrorStatus setIsReconciled(bool bReconcile = true);

	NcCmColor         color(const NcDbObjectId& viewportId, bool& isOverride) const;
	static bool       isReconciled(const NcDbObjectId& id);
	NcDbObjectId      linetypeObjectId(const NcDbObjectId& viewportId, bool& isOverride) const;
	NcDb::LineWeight  lineWeight(const NcDbObjectId& viewportId, bool& isOverride) const;
	NCHAR*            plotStyleName(const NcDbObjectId& viewportId, bool& isOverride) const;
	NcDbObjectId      plotStyleNameId(const NcDbObjectId& viewportId, bool& isOverride) const;
	Nano::ErrorStatus setColor(const NcCmColor& color,
	                           const NcDbObjectId& viewportId);
	Nano::ErrorStatus setLinetypeObjectId(const NcDbObjectId& id,
	                                      const NcDbObjectId& viewportId);
	Nano::ErrorStatus setLineWeight(NcDb::LineWeight weight,
	                                const NcDbObjectId& viewportId);
	Nano::ErrorStatus setPlotStyleName(const NcDbObjectId& newId,
	                                   const NcDbObjectId& viewportId);
	Nano::ErrorStatus setPlotStyleName(const NCHAR* newName,
	                                   const NcDbObjectId& viewportId);
	Nano::ErrorStatus setTransparency(const NcCmTransparency& trans,
	                                  const NcDbObjectId& viewportId);
	NcCmTransparency  transparency(const NcDbObjectId& viewportId, bool& isOvr) const;

public:
	OdDbLayerTableRecord* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbTextStyleTableRecord
class OdDbTextStyleTableRecord;
class NRXDBGATE_EXPORT NcDbTextStyleTableRecord : public NcDbSymbolTableRecord
{
	NCDB_DECLARE_MEMBERS(NcDbTextStyleTableRecord);

public:
	typedef NcDbTextStyleTableRecord  wrapper_class;
	typedef OdDbTextStyleTableRecord  native_class;

	typedef NcDbTextStyleTable        TableType;

public:
	NcDbTextStyleTableRecord();

	NcDbTextStyleTableRecord(OdRxObject* _object);

	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload

	// NcGiDrawable interface
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus applyPartialUndo(NcDbDwgFiler* filer, NcRxClass* rxclass) override;

	virtual Nano::ErrorStatus subClose() override;
	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;
	virtual Nano::ErrorStatus subHandOverTo(NcDbObject* newObject) override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	NRX::Boolean isShapeFile() const;
	void setIsShapeFile(NRX::Boolean shape);

	NRX::Boolean isVertical() const;
	void setIsVertical(NRX::Boolean vertical);

	double textSize() const;
	Nano::ErrorStatus setTextSize(double size);

	double xScale() const;
	Nano::ErrorStatus setXScale(double xScale);

	double obliquingAngle() const;
	Nano::ErrorStatus setObliquingAngle(double angle);

	NRX::UInt8 flagBits() const;
	void setFlagBits(NRX::UInt8 flagBits);

	double priorSize() const;
	Nano::ErrorStatus setPriorSize(double size);

	Nano::ErrorStatus fileName(NCHAR*& name) const;
	Nano::ErrorStatus fileName(const NCHAR*& name) const;
	Nano::ErrorStatus setFileName(const NCHAR* name);

	Nano::ErrorStatus bigFontFileName(NCHAR*& name) const;
	Nano::ErrorStatus bigFontFileName(const NCHAR*& name) const;
	Nano::ErrorStatus setBigFontFileName(const NCHAR* name);

	Nano::ErrorStatus setFont(const NCHAR* typeface, NRX::Boolean bold, NRX::Boolean italic, int charset,
	                          int pitchAndFamily);
	Nano::ErrorStatus font(NCHAR*& typeface, NRX::Boolean& bold, NRX::Boolean& italic, int& charset,
	                       int& pitchAndFamily) const;

public:
	OdDbTextStyleTableRecord* native() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDimStyleTableRecord
class OdDbDimStyleTableRecord;
class NRXDBGATE_EXPORT NcDbDimStyleTableRecord : public NcDbSymbolTableRecord
{
	NCDB_DECLARE_MEMBERS(NcDbDimStyleTableRecord);
	virtual double dimmzf(void) ; //+Overload
	virtual double dimaltmzf(void) ; //+Overload
	virtual bool dimtxtdirection(void) ; //+Overload

public:
	typedef NcDbDimStyleTableRecord  wrapper_class;
	typedef OdDbDimStyleTableRecord  native_class;

	typedef NcDbDimStyleTable        TableType;

public:
	NcDbDimStyleTableRecord();
	NcDbDimStyleTableRecord(OdRxObject* native);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	NcDbObjectId arrowId(NcDb::DimArrowFlags whichArrow) const;

	virtual int dimadec() const;
	virtual bool dimalt() const;
	virtual int dimaltd() const;
	virtual double dimaltf() const;
	virtual double dimaltrnd() const;
	virtual int dimalttd() const;
	virtual int dimalttz() const;
	virtual int dimaltu() const;
	virtual int dimaltz() const;
	virtual const NCHAR* dimapost() const;
	virtual int dimarcsym() const;
	virtual double dimasz() const;
	virtual int dimatfit() const;
	virtual int dimaunit() const;
	virtual int dimazin() const;
	virtual NcDbObjectId dimblk() const;
	virtual NcDbObjectId dimblk1() const;
	virtual NcDbObjectId dimblk2() const;
	virtual double dimcen() const;
	virtual NcCmColor dimclrd() const;
	virtual NcCmColor dimclre() const;
	virtual NcCmColor dimclrt() const;
	virtual int dimdec() const;
	virtual double dimdle() const;
	virtual double dimdli() const;
	virtual NCHAR dimdsep() const;
	virtual double dimexe() const;
	virtual double dimexo() const;
	virtual int dimfrac() const;
	virtual double dimgap() const;
	virtual double dimjogang() const;
	virtual int dimjust() const;
	virtual NcDbObjectId dimldrblk() const;
	virtual double dimlfac() const;
	virtual bool dimlim() const;
	virtual NcDbObjectId dimltex1() const;
	virtual NcDbObjectId dimltex2() const;
	virtual NcDbObjectId dimltype() const;
	virtual int dimlunit() const;
	virtual NcDb::LineWeight dimlwd() const;
	virtual NcDb::LineWeight dimlwe() const;
	virtual const NCHAR* dimpost() const;
	virtual double dimrnd() const;
	virtual bool dimsah() const;
	virtual double dimscale() const;
	virtual bool dimsd1() const;
	virtual bool dimsd2() const;
	virtual bool dimse1() const;
	virtual bool dimse2() const;
	virtual bool dimsoxd() const;
	virtual int dimtad() const;
	virtual int dimtdec() const;
	virtual double dimtfac() const;
	virtual int dimtfill() const;
	virtual NcCmColor dimtfillclr() const;
	virtual bool dimtih() const;
	virtual bool dimtix() const;
	virtual double dimtm() const;
	virtual int dimtmove() const;
	virtual bool dimtofl() const;
	virtual bool dimtoh() const;
	virtual bool dimtol() const;
	virtual int dimtolj() const;
	virtual double dimtp() const;
	virtual double dimtsz() const;
	virtual double dimtvp() const;
	virtual NcDbObjectId dimtxsty() const;
	virtual double dimtxt() const;
	virtual int dimtzin() const;
	virtual bool dimupt() const;
	virtual int dimzin() const;

	virtual bool dimfxlenOn() const;
	virtual double dimfxlen() const;

	virtual Nano::ErrorStatus setDimadec(int value);
	virtual Nano::ErrorStatus setDimalt(bool value);
	virtual Nano::ErrorStatus setDimaltd(int value);
	virtual Nano::ErrorStatus setDimaltf(double value);
	virtual Nano::ErrorStatus setDimaltrnd(double value);
	virtual Nano::ErrorStatus setDimalttd(int value);
	virtual Nano::ErrorStatus setDimalttz(int value);
	virtual Nano::ErrorStatus setDimaltu(int value);
	virtual Nano::ErrorStatus setDimaltz(int value);
	virtual Nano::ErrorStatus setDimapost(const NCHAR* value);
	virtual Nano::ErrorStatus setDimarcsym(int value);
	virtual Nano::ErrorStatus setDimasz(double value);
	virtual Nano::ErrorStatus setDimatfit(int value);
	virtual Nano::ErrorStatus setDimaunit(int value);
	virtual Nano::ErrorStatus setDimazin(int value);
	virtual Nano::ErrorStatus setDimblk(NcDbObjectId value);
	virtual Nano::ErrorStatus setDimblk1(NcDbObjectId value);
	virtual Nano::ErrorStatus setDimblk2(NcDbObjectId value);
	virtual Nano::ErrorStatus setDimcen(double value);
	virtual Nano::ErrorStatus setDimclrd(const NcCmColor& color);
	virtual Nano::ErrorStatus setDimclre(const NcCmColor& color);
	virtual Nano::ErrorStatus setDimclrt(const NcCmColor& color);
	virtual Nano::ErrorStatus setDimdec(int value);
	virtual Nano::ErrorStatus setDimdle(double value);
	virtual Nano::ErrorStatus setDimdli(double value);
	virtual Nano::ErrorStatus setDimdsep(NCHAR value);
	virtual Nano::ErrorStatus setDimexe(double value);
	virtual Nano::ErrorStatus setDimexo(double value);
	virtual Nano::ErrorStatus setDimfrac(int value);
	virtual Nano::ErrorStatus setDimgap(double value);
	virtual Nano::ErrorStatus setDimjogang(double value);
	virtual Nano::ErrorStatus setDimjust(int value);
	virtual Nano::ErrorStatus setDimldrblk(NcDbObjectId value);
	virtual Nano::ErrorStatus setDimlfac(double value);
	virtual Nano::ErrorStatus setDimlim(bool value);
	virtual Nano::ErrorStatus setDimltex1(NcDbObjectId value);
	virtual Nano::ErrorStatus setDimltex2(NcDbObjectId value);
	virtual Nano::ErrorStatus setDimltype(NcDbObjectId value);
	virtual Nano::ErrorStatus setDimlunit(int value);
	virtual Nano::ErrorStatus setDimlwd(NcDb::LineWeight value);
	virtual Nano::ErrorStatus setDimlwe(NcDb::LineWeight value);
	virtual Nano::ErrorStatus setDimpost(const NCHAR* value);
	virtual Nano::ErrorStatus setDimrnd(double value);
	virtual Nano::ErrorStatus setDimsah(bool value);
	virtual Nano::ErrorStatus setDimscale(double value);
	virtual Nano::ErrorStatus setDimsd1(bool value);
	virtual Nano::ErrorStatus setDimsd2(bool value);
	virtual Nano::ErrorStatus setDimse1(bool value);
	virtual Nano::ErrorStatus setDimse2(bool value);
	virtual Nano::ErrorStatus setDimsoxd(bool value);
	virtual Nano::ErrorStatus setDimtad(int value);
	virtual Nano::ErrorStatus setDimtdec(int value);
	virtual Nano::ErrorStatus setDimtfac(double value);
	virtual Nano::ErrorStatus setDimtfill(int value);
	virtual Nano::ErrorStatus setDimtfillclr(const NcCmColor& color);
	virtual Nano::ErrorStatus setDimtih(bool value);
	virtual Nano::ErrorStatus setDimtix(bool value);
	virtual Nano::ErrorStatus setDimtm(double value);
	virtual Nano::ErrorStatus setDimtmove(int value);
	virtual Nano::ErrorStatus setDimtofl(bool value);
	virtual Nano::ErrorStatus setDimtoh(bool value);
	virtual Nano::ErrorStatus setDimtol(bool value);
	virtual Nano::ErrorStatus setDimtolj(int value);
	virtual Nano::ErrorStatus setDimtp(double value);
	virtual Nano::ErrorStatus setDimtsz(double value);
	virtual Nano::ErrorStatus setDimtvp(double value);
	virtual Nano::ErrorStatus setDimtxsty(NcDbObjectId value);
	virtual Nano::ErrorStatus setDimtxt(double value);
	virtual Nano::ErrorStatus setDimtzin(int value);
	virtual Nano::ErrorStatus setDimupt(bool value);
	virtual Nano::ErrorStatus setDimzin(int value);

	virtual Nano::ErrorStatus setDimblk(const NCHAR* value);
	virtual Nano::ErrorStatus setDimblk1(const NCHAR* value);
	virtual Nano::ErrorStatus setDimblk2(const NCHAR* value);
	virtual Nano::ErrorStatus setDimldrblk(const NCHAR* value);

	virtual Nano::ErrorStatus setDimfxlenOn(bool value);
	virtual Nano::ErrorStatus setDimfxlen(double value);

	bool isModifiedForRecompute() const;

	virtual const NCHAR *    dimaltmzs() const;

	virtual const NCHAR *    dimmzs   () const;
	Nano::ErrorStatus getDimapost(NCHAR*& pOutput) const;
	Nano::ErrorStatus getDimblk(NCHAR*& pOutput) const;
	Nano::ErrorStatus getDimblk1(NCHAR*& pOutput) const;
	Nano::ErrorStatus getDimblk2(NCHAR*& pOutput) const;
	Nano::ErrorStatus getDimpost(NCHAR*& pOutput) const;
	virtual Nano::ErrorStatus setDimaltmzf(double           v);

	virtual Nano::ErrorStatus setDimaltmzs(const NCHAR *    v);
	Nano::ErrorStatus setDimfit(int fit);

	virtual Nano::ErrorStatus setDimmzf   (double           v);

	virtual Nano::ErrorStatus setDimmzs   (const NCHAR *    v);
	virtual Nano::ErrorStatus setDimtxtdirection (bool      v);
	Nano::ErrorStatus setDimunit(int unit);

	// DEPRECATED METHODS!
	// These are supported but will be removed in future releases:
	//
	int dimfit() const;
	int dimunit() const;
	//
	// end DEPRECATED METHODS!

public:
	OdDbDimStyleTableRecord* native() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbLinetypeTableRecord
class OdDbLinetypeTableRecord;
class NRXDBGATE_EXPORT NcDbLinetypeTableRecord : public NcDbSymbolTableRecord
{
	NCDB_DECLARE_MEMBERS(NcDbLinetypeTableRecord);

public:
	typedef NcDbLinetypeTableRecord  wrapper_class;
	typedef OdDbLinetypeTableRecord  native_class;

	typedef NcDbLinetypeTable  TableType;

public:
	NcDbLinetypeTableRecord();

	NcDbLinetypeTableRecord(OdRxObject* _object);

	virtual NcGiDrawable* drawable() ; // +Overload

	// NcGiDrawable interface
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus comments(NCHAR*& string) const;
	Nano::ErrorStatus comments(const NCHAR*& string) const;
	Nano::ErrorStatus setComments(const NCHAR* string);

	Nano::ErrorStatus asciiDescription(NCHAR*& pString) const;
	Nano::ErrorStatus asciiDescription(const NCHAR*& pString) const;
	Nano::ErrorStatus setAsciiDescription(const NCHAR* pString);

	double patternLength() const;
	void setPatternLength(double length);

	int numDashes() const;
	void setNumDashes(int count);

	double dashLengthAt(int index) const;
	void setDashLengthAt(int index, double value);

	NcDbObjectId shapeStyleAt(int index) const;
	void setShapeStyleAt(int index, NcDbObjectId id);

	int shapeNumberAt(int index) const;
	void setShapeNumberAt(int index, int number);

	NcGeVector2d shapeOffsetAt(int index) const;
	void setShapeOffsetAt(int index, const NcGeVector2d& offset);

	double shapeScaleAt(int index) const;
	void setShapeScaleAt(int index, double scale);

	bool isScaledToFit() const;
	void setIsScaledToFit(bool set);

	bool shapeIsUcsOrientedAt(int index) const;
	void setShapeIsUcsOrientedAt(int index, bool set);

	double shapeRotationAt(int index) const;
	void setShapeRotationAt(int index, double angle);

	Nano::ErrorStatus textAt(int index, NCHAR*& text) const;
	Nano::ErrorStatus textAt(int index, const NCHAR*& text) const;
	Nano::ErrorStatus setTextAt(int index, const NCHAR* text);

	NcGsNode* gsNode() const;
	void setGsNode(NcGsNode* pNode);
	void setShapeIsUprightAt(int index, bool isUpright);
	bool shapeIsUprightAt(int index) const;

public:
	OdDbLinetypeTableRecord* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbRegAppTableRecord
class OdDbRegAppTableRecord;
class NRXDBGATE_EXPORT NcDbRegAppTableRecord : public NcDbSymbolTableRecord
{
	NCDB_DECLARE_MEMBERS(NcDbRegAppTableRecord);

public:
	typedef NcDbRegAppTableRecord  wrapper_class;
	typedef OdDbRegAppTableRecord  native_class;

	typedef NcDbRegAppTable        TableType;

public:
	NcDbRegAppTableRecord();

	NcDbRegAppTableRecord(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

public:
	OdDbRegAppTableRecord* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbUCSTableRecord
class OdDbUCSTableRecord;
class NRXDBGATE_EXPORT NcDbUCSTableRecord : public NcDbSymbolTableRecord
{
	NCDB_DECLARE_MEMBERS(NcDbUCSTableRecord);

public:
	typedef NcDbUCSTableRecord  wrapper_class;
	typedef OdDbUCSTableRecord  native_class;

	typedef NcDbUCSTable        TableType;

public:
	NcDbUCSTableRecord();

	NcDbUCSTableRecord(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	NcGePoint3d origin() const;
	void setOrigin(const NcGePoint3d& origin);

	NcGeVector3d xAxis() const;
	void setXAxis(const NcGeVector3d& direction);

	NcGeVector3d yAxis() const;
	void setYAxis(const NcGeVector3d& direction);

	NcGePoint3d ucsBaseOrigin(NcDb::OrthographicView view) const;
	Nano::ErrorStatus setUcsBaseOrigin(const NcGePoint3d& origin, NcDb::OrthographicView view);

public:
	OdDbUCSTableRecord* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbAbstractViewTableRecord
class OdDbAbstractViewTableRecord;
class NRXDBGATE_EXPORT NcDbAbstractViewTableRecord : public NcDbSymbolTableRecord
{
	NCDB_DECLARE_MEMBERS(NcDbAbstractViewTableRecord);

public:
	typedef NcDbAbstractViewTableRecord  wrapper_class;
	typedef OdDbAbstractViewTableRecord  native_class;

	typedef NcDbAbstractViewTable        TableType;

	enum RenderMode
	{
		k2DOptimized,
		kWireframe,
		kHiddenLine,
		kFlatShaded,
		kGouraudShaded,
		kFlatShadedWithWireframe,
		kGouraudShadedWithWireframe
	};

public:
	NcDbAbstractViewTableRecord(OdRxObject* _object);
	//virtual ~NcDbAbstractViewTableRecord();

	// NcRxObject
public:
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source) override;

	// NcGiDrawable interface
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual NcGiDrawable* drawable() override;

public:
	NcGePoint2d centerPoint() const;
	void setCenterPoint(const NcGePoint2d&);

	double height() const;
	void setHeight(double height);

	double width() const;
	void setWidth(double width);

	NcGePoint3d target() const;
	void setTarget(const NcGePoint3d& target);

	NcGeVector3d viewDirection() const;
	void setViewDirection(const NcGeVector3d& viewDirection);

	double viewTwist() const;
	void setViewTwist(double angle);

	double lensLength() const;
	void setLensLength(double length);

	double frontClipDistance() const;
	void setFrontClipDistance(double distance);

	double backClipDistance() const;
	void setBackClipDistance(double distance);

	bool perspectiveEnabled() const;
	void setPerspectiveEnabled(bool enabled);

	bool frontClipEnabled() const;
	void setFrontClipEnabled(bool enabled);

	bool backClipEnabled() const;
	void setBackClipEnabled(bool enabled);

	bool frontClipAtEye() const;
	void setFrontClipAtEye(bool atEye);

	void setRenderMode(RenderMode mode);
	RenderMode renderMode() const;

	const NcDbObjectId& background() const;
	NcDbObjectId&       background();
	Nano::ErrorStatus setBackground(const NcDbObjectId& id);

	NcDbObjectId visualStyle() const;
	Nano::ErrorStatus setVisualStyle(const NcDbObjectId& id);

	bool isDefaultLightingOn() const;
	Nano::ErrorStatus setDefaultLightingOn(bool on);
	NcGiViewportTraits::DefaultLightingType defaultLightingType() const;
	Nano::ErrorStatus setDefaultLightingType(NcGiViewportTraits::DefaultLightingType type);

	double brightness() const;
	Nano::ErrorStatus setBrightness(double);

	double contrast() const;
	Nano::ErrorStatus setContrast(double);

	NcCmColor ambientLightColor() const;
	Nano::ErrorStatus setAmbientLightColor(const NcCmColor& clr);

	NcDbObjectId sunId() const;
	Nano::ErrorStatus setSun(NcDbObjectId& id, NcDbObject* sun);
	Nano::ErrorStatus setSun(NcDbObjectId& id, NcDbObject* sun, bool erase_old);

	Nano::ErrorStatus toneOperatorParameters(NcGiToneOperatorParameters& params) const;
	Nano::ErrorStatus setToneOperatorParameters(const NcGiToneOperatorParameters& params);

	Nano::ErrorStatus getUcs(NcGePoint3d& origin, NcGeVector3d& xAxis, NcGeVector3d& yAxis) const;
	bool isUcsOrthographic(NcDb::OrthographicView& view) const;
	NcDbObjectId ucsName() const;
	double elevation() const;

	Nano::ErrorStatus setUcs(const NcGePoint3d& origin, const NcGeVector3d& xAxis, const NcGeVector3d& yAxis);
	Nano::ErrorStatus setUcs(NcDb::OrthographicView view);
	Nano::ErrorStatus setUcs(const NcDbObjectId& ucsId);
	Nano::ErrorStatus setUcsToWorld();
	Nano::ErrorStatus setElevation(double elev);

	bool isViewOrthographic(NcDb::OrthographicView& view) const;
	Nano::ErrorStatus setViewDirection(NcDb::OrthographicView view);

public:
	OdDbAbstractViewTableRecord* native() const;
private:
	mutable NcDbObjectId m_backgroundId;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbViewTableRecord
class OdDbViewTableRecord;
class NRXDBGATE_EXPORT NcDbViewTableRecord : public NcDbAbstractViewTableRecord
{
	NCDB_DECLARE_MEMBERS(NcDbViewTableRecord);

public:
	typedef NcDbViewTableRecord  wrapper_class;
	typedef OdDbViewTableRecord  native_class;

	typedef NcDbViewTable        TableType;

public:
	NcDbViewTableRecord();

	NcDbViewTableRecord(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	Nano::ErrorStatus setParametersFromViewport(NcDbObjectId objId);

	bool isPaperspaceView() const;
	void setIsPaperspaceView(bool pspace);

	bool isUcsAssociatedToView() const;
	Nano::ErrorStatus disassociateUcsFromView();

	Nano::ErrorStatus getCategoryName(NCHAR*& category) const;
	Nano::ErrorStatus setCategoryName(const NCHAR* category);

	Nano::ErrorStatus getLayerState(NCHAR*& layer) const;
	Nano::ErrorStatus setLayerState(const NCHAR* layer);

	Nano::ErrorStatus getLayout(NcDbObjectId& id) const;
	Nano::ErrorStatus setLayout(NcDbObjectId id);

	bool isViewAssociatedToViewport() const;
	Nano::ErrorStatus setViewAssociatedToViewport(bool bVPflag);

	bool isCameraPlottable() const;
	Nano::ErrorStatus setIsCameraPlottable(bool plottable);

	// Live Section
	NcDbObjectId liveSection() const;
	Nano::ErrorStatus setLiveSection(const NcDbObjectId& liveSectionId);

#ifdef _WINDOWS_
	Nano::ErrorStatus getThumbnail(BITMAPINFO*& thumbnail) const;
	Nano::ErrorStatus setThumbnail(const BITMAPINFO* thumbnail);
#endif

	// Camera methods
	NcDbObjectId camera() const;
	Nano::ErrorStatus setCamera(NcDbObjectId cameraId);

	NcDbAnnotationScale* annotationScale() const;
	Nano::ErrorStatus setAnnotationScale(const NcDbAnnotationScale* scale);

	NcDbObjectId sunId() const;
	Nano::ErrorStatus setSun(NcDbObjectId& id, NcDbObject* sun);
	Nano::ErrorStatus setSun(NcDbObjectId& id, NcDbObject* sun, bool erase_old);

public:
	OdDbViewTableRecord* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbViewportTableRecord
class OdDbViewportTableRecord;
class NRXDBGATE_EXPORT NcDbViewportTableRecord : public NcDbAbstractViewTableRecord
{
	NCDB_DECLARE_MEMBERS(NcDbViewportTableRecord);

public:
	typedef NcDbViewportTableRecord  wrapper_class;
	typedef OdDbViewportTableRecord  native_class;

	typedef NcDbViewportTable        TableType;

public:
	NcDbViewportTableRecord();

	NcDbViewportTableRecord(OdRxObject* _object);

	// NcRxObject
public:
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subClose() override;

	virtual NcGiDrawable* drawable();

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

public:
	NRX::Int16 number() const;

	NcGePoint2d lowerLeftCorner() const;
	void setLowerLeftCorner(const NcGePoint2d& point);

	NcGePoint2d upperRightCorner() const;
	void setUpperRightCorner(const NcGePoint2d& point);

	bool ucsFollowMode() const;
	void setUcsFollowMode(bool enabled);

	NRX::UInt16 circleSides() const;
	void setCircleSides(NRX::UInt16 sides);

	bool fastZoomsEnabled() const;
	void setFastZoomsEnabled(bool enabled);

	bool iconEnabled() const;
	void setIconEnabled(bool enabled);

	bool iconAtOrigin() const;
	void setIconAtOrigin(bool enabled);

	bool gridEnabled() const;
	void setGridEnabled(bool enabled);

	NcGePoint2d gridIncrements() const;
	void setGridIncrements(const NcGePoint2d& base);

	bool snapEnabled() const;
	void setSnapEnabled(bool enabled);

	bool isometricSnapEnabled() const;
	void setIsometricSnapEnabled(bool enabled);

	NRX::Int16 snapPair() const;
	void setSnapPair(NRX::Int16 type);

	double snapAngle() const;
	void setSnapAngle(double angle);

	NcGePoint2d snapBase() const;
	void setSnapBase(const NcGePoint2d& base);

	NcGePoint2d snapIncrements() const;
	void setSnapIncrements(const NcGePoint2d& base);

	void setGsView(NcGsView* view);
	NcGsView* gsView() const;

	bool isUcsSavedWithViewport() const;
	void setUcsPerViewport(bool enabled);

public:
	bool isGridBoundToLimits() const;
	void setGridBoundToLimits(bool enabled);

	bool isGridAdaptive() const;
	void setGridAdaptive(bool enabled);

	bool isGridSubdivisionRestricted() const;
	void setGridSubdivisionRestricted(bool enabled);

	bool isGridFollow() const;
	void setGridFollow(bool enabled);

	NRX::Int16 gridMajor() const;
	void setGridMajor(NRX::Int16 value);

	void zoomExtents();

	NcDbObjectId previousBackground(NcGiDrawable::DrawableType type= NcGiDrawable::kGeometry) const;
	bool previousBackgroundForcedSwitch (void) const;
	Nano::ErrorStatus setPreviousBackground(NcDbObjectId backgroundId,
	                                        NcGiDrawable::DrawableType type= NcGiDrawable::kGeometry);
	Nano::ErrorStatus setPreviousBackground(NcDbObjectId backgroundId,
	                                        NcGiDrawable::DrawableType type,
	                                        bool bForcedSwitch);

	NcGsNode* gsNode() const;
	Nano::ErrorStatus setBackground(const NcDbObjectId& backgroundId);

public:
	OdDbViewportTableRecord* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSymbolTableIterator
class OdDbSymbolTableIterator;
class NRXDBGATE_EXPORT NcDbSymbolTableIterator
{
public:
	typedef NcDbSymbolTableIterator  wrapper_class;
	typedef OdDbSymbolTableIterator  native_class;

protected:
	NcDbSymbolTableIterator() {}

public:
	NcDbSymbolTableIterator(OdDbSymbolTableIterator* _object);

	virtual ~NcDbSymbolTableIterator();

public:
	void start(bool at_beginning = true, bool skip_deleted = true);
	bool done() const;

	Nano::ErrorStatus getRecordId(NcDbObjectId& id) const;

	Nano::ErrorStatus getRecord(NcDbSymbolTableRecord*& record, NcDb::OpenMode mode, bool open_erased = false) const;

	void step(bool forward = true, bool skip_deleted = true);

	Nano::ErrorStatus seek(NcDbObjectId id);
	Nano::ErrorStatus seek(const NcDbSymbolTableRecord* record);

public:
	OdDbSymbolTableIterator* native() const;

protected:
	OdRxObject* m_pNative;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbBlockTableIterator
class OdDbBlockTableIterator;
class NRXDBGATE_EXPORT NcDbBlockTableIterator : public NcDbSymbolTableIterator
{
public:
	typedef NcDbBlockTableIterator  wrapper_class;
	typedef OdDbBlockTableIterator  native_class;

public:
	NcDbBlockTableIterator(OdDbSymbolTableIterator* _object);

	Nano::ErrorStatus seek(const NcDbBlockTableRecord* record);
	Nano::ErrorStatus seek(NcDbObjectId id);

	Nano::ErrorStatus getRecord(NcDbBlockTableRecord*& record, NcDb::OpenMode mode, bool open_erased = false) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDimStyleTableIterator
class OdDbSymbolTableIterator;
class NRXDBGATE_EXPORT NcDbDimStyleTableIterator : public NcDbSymbolTableIterator
{
public:
	typedef NcDbDimStyleTableIterator  wrapper_class;
	typedef OdDbSymbolTableIterator    native_class;

public:
	Nano::ErrorStatus seek(const NcDbDimStyleTableRecord* record);
	Nano::ErrorStatus seek(NcDbObjectId id);

	Nano::ErrorStatus getRecord(NcDbDimStyleTableRecord*& record, NcDb::OpenMode mode, bool open_erased = false) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbTextStyleTableIterator
class OdDbSymbolTableIterator;
class NRXDBGATE_EXPORT NcDbTextStyleTableIterator : public NcDbSymbolTableIterator
{
public:
	typedef NcDbTextStyleTableIterator  wrapper_class;
	typedef OdDbSymbolTableIterator     native_class;

public:
	Nano::ErrorStatus seek(const NcDbTextStyleTableRecord* record);
	Nano::ErrorStatus seek(NcDbObjectId id);

	Nano::ErrorStatus getRecord(NcDbTextStyleTableRecord*& record, NcDb::OpenMode mode, bool open_erased =
	                            false) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbLinetypeTableIterator
class OdDbLinetypeTableIterator;
class NRXDBGATE_EXPORT NcDbLinetypeTableIterator : public NcDbSymbolTableIterator
{
public:
	typedef NcDbLinetypeTableIterator  wrapper_class;
	typedef OdDbLinetypeTableIterator  native_class;

public:
	Nano::ErrorStatus seek(const NcDbLinetypeTableRecord* record);
	Nano::ErrorStatus seek(NcDbObjectId id);

	Nano::ErrorStatus getRecord(NcDbLinetypeTableRecord*& record, NcDb::OpenMode mode, bool open_erased = false) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbAbstractViewTableIterator
class OdDbSymbolTableIterator;
class NRXDBGATE_EXPORT NcDbAbstractViewTableIterator : public NcDbSymbolTableIterator
{
public:
	typedef NcDbAbstractViewTableIterator  wrapper_class;
	typedef OdDbSymbolTableIterator        native_class;

public:
	Nano::ErrorStatus seek(NcDbObjectId id);
	Nano::ErrorStatus seek(const NcDbAbstractViewTableRecord* record);

	Nano::ErrorStatus getRecord(NcDbAbstractViewTableRecord*& record, NcDb::OpenMode mode, bool open_erased =
	                            false) const;
};

class OdDbLayerTableIterator;
//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbLayerTableIterator
class NRXDBGATE_EXPORT NcDbLayerTableIterator : public NcDbSymbolTableIterator
{
public:
	typedef NcDbLayerTableIterator  wrapper_class;
	typedef OdDbSymbolTableIterator  native_class;

public:
	Nano::ErrorStatus seek(const NcDbLayerTableRecord* record);
	Nano::ErrorStatus seek(NcDbObjectId id);

	Nano::ErrorStatus getRecord(NcDbLayerTableRecord*& record, NcDb::OpenMode mode, bool open_erased = false) const;

	bool getSkipHidden() const;
	void setSkipHidden(bool value);
	bool getSkipReconciled() const;
	void setSkipReconciled(bool value);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbUCSTableIterator
class NRXDBGATE_EXPORT NcDbUCSTableIterator : public NcDbSymbolTableIterator
{
public:
	typedef NcDbUCSTableIterator     wrapper_class;
	typedef OdDbSymbolTableIterator  native_class;

public:
	Nano::ErrorStatus seek(const NcDbUCSTableRecord* record);
	Nano::ErrorStatus seek(NcDbObjectId id);

	Nano::ErrorStatus getRecord(NcDbUCSTableRecord*& record, NcDb::OpenMode mode, bool open_erased = false) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbBlockTableRecordIterator
class OdDbObjectIterator;
class NRXDBGATE_EXPORT NcDbBlockTableRecordIterator
{
public:
	typedef NcDbBlockTableRecordIterator  wrapper_class;
	typedef OdDbObjectIterator            native_class;

public:
	NcDbBlockTableRecordIterator(OdDbObjectIterator* _object);

public:
	virtual ~NcDbBlockTableRecordIterator();

public:
	void start(bool at_beginning = true, bool skip_deleted = true);

	bool done() const;

	Nano::ErrorStatus getEntityId(NcDbObjectId& id) const;
	Nano::ErrorStatus getEntity(NcDbEntity*& entity, NcDb::OpenMode mode, bool open_erased = false) const;

	NcDbBlockTableRecord* blockTableRecord() const;

	void step(bool forward = true, bool skip_deleted = true);

	Nano::ErrorStatus seek(NcDbObjectId id);
	Nano::ErrorStatus seek(const NcDbEntity* entity);

public:
	OdDbObjectIterator* native() const;

protected:
	OdDbObjectIterator* m_pNative;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbViewTableIterator
class OdDbSymbolTableIterator;
class NRXDBGATE_EXPORT NcDbViewTableIterator : public NcDbSymbolTableIterator
{
public:
	typedef NcDbViewTableIterator    wrapper_class;
	typedef OdDbSymbolTableIterator  native_class;

public:
	Nano::ErrorStatus seek(const NcDbViewTableRecord* record);
	Nano::ErrorStatus seek(NcDbObjectId id);

	Nano::ErrorStatus getRecord(NcDbViewTableRecord*& record, NcDb::OpenMode mode, bool open_erased = false) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbViewportTableIterator
class OdDbSymbolTableIterator;
class NRXDBGATE_EXPORT NcDbViewportTableIterator : public NcDbSymbolTableIterator
{
public:
	typedef NcDbViewportTableIterator  wrapper_class;
	typedef OdDbSymbolTableIterator    native_class;

protected:
	NcDbViewportTableIterator();

public:
	Nano::ErrorStatus seek(const NcDbViewportTableRecord* record);
	Nano::ErrorStatus seek(NcDbObjectId id);

	Nano::ErrorStatus getRecord(NcDbViewportTableRecord*& record, NcDb::OpenMode mode, bool open_erased = false) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbRegAppTableIterator
class OdDbSymbolTableIterator;
class NRXDBGATE_EXPORT NcDbRegAppTableIterator : public NcDbSymbolTableIterator
{
public:
	typedef NcDbRegAppTableIterator  wrapper_class;
	typedef OdDbSymbolTableIterator  native_class;

public:
	Nano::ErrorStatus seek(const NcDbRegAppTableRecord* record);
	Nano::ErrorStatus seek(NcDbObjectId id);

	Nano::ErrorStatus getRecord(NcDbRegAppTableRecord*& record, NcDb::OpenMode mode, bool open_erased = false) const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbPlotSettings
class OdDbPlotSettings;
class NRXDBGATE_EXPORT NcDbPlotSettings : public NcDbObject
{
	NCDB_DECLARE_MEMBERS(NcDbPlotSettings);

public:
	typedef NcDbPlotSettings  wrapper_class;
	typedef OdDbPlotSettings  native_class;

	enum PlotPaperUnits
	{
		kInches         = 0,   // Inches
		kMillimeters    = 1,   // Millimeters
		kPixels         = 2    // Pixels
	};

	enum PlotRotation
	{
		k0degrees       = 0,   // No rotation
		k90degrees      = 1,   // 90° CCW
		k180degrees     = 2,   // Inverted
		k270degrees     = 3    // 90° CW
	};

	enum PlotType
	{
		kDisplay        = 0,   // Display
		kExtents        = 1,   // Extents
		kLimits         = 2,   // Limits
		kView           = 3,   // View
		kWindow         = 4,   // Window
		kLayout         = 5    // Layout
	};

	enum StdScaleType
	{
		kScaleToFit     = 0,   // Scaled to Fit
		k1_128in_1ft    = 1,   // 1/128" = 1'
		k1_64in_1ft     = 2,   // 1/64" = 1'
		k1_32in_1ft     = 3,   // 1/32" = 1'
		k1_16in_1ft     = 4,   // 1/16" = 1'
		k3_32in_1ft     = 5,   // 3/32" = 1'
		k1_8in_1ft      = 6,   // 1/8" = 1'
		k3_16in_1ft     = 7,   // 3/16" = 1'
		k1_4in_1ft      = 8,   // 1/4" = 1'
		k3_8in_1ft      = 9,   // 3/8" = 1'
		k1_2in_1ft      = 10,  // 1/2" = 1'
		k3_4in_1ft      = 11,  // 3/4" = 1'
		k1in_1ft        = 12,  // 1" = 1'
		k3in_1ft        = 13,  // 3" = 1'
		k6in_1ft        = 14,  // 6" = 1'
		k1ft_1ft        = 15,  // 1' = 1'
		k1_1            = 16,  // 1:1
		k1_2            = 17,  // 1:2
		k1_4            = 18,  // 1:4
		k1_5            = 19,  // 1:5
		k1_8            = 20,  // 1:8
		k1_10           = 21,  // 1:10
		k1_16           = 22,  // 1:16
		k1_20           = 23,  // 1:20
		k1_30           = 24,  // 1:30
		k1_40           = 25,  // 1:40
		k1_50           = 26,  // 1:50
		k1_100          = 27,  // 1:100
		k2_1            = 28,  // 2:1
		k4_1            = 29,  // 4:1
		k8_1            = 30,  // 8:1
		k10_1           = 31,  // 10:1
		k100_1          = 32,  // 100:1
		k1000_1         = 33,  // 1000:1
		k1and1_2in_1ft  = 34  // 1.5"= 1' 
	};

	enum ShadePlotType 
	{
		kAsDisplayed    = 0, // As displayed
		kWireframe      = 1, // Wireframe
		kHidden         = 2, // Hidden lines removed
		kRendered       = 3, // Rendered
		kVisualStyle    = 4, // Visual style
		kRenderPreset   = 5  // Render preset
	};

	enum ShadePlotResLevel
	{
		kDraft          = 0, // Draft
		kPreview        = 1, // Preview
		kNormal         = 2, // Normal
		kPresentation   = 3, // Presentation
		kMaximum        = 4, // Maximum
		kCustom         = 5  // Custom
	};

public:
	NcDbPlotSettings(bool model = true);

	NcDbPlotSettings(OdRxObject* _object);

	// OdRxObject
public:
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source) override;

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subClose() override;
	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;
	virtual Nano::ErrorStatus subHandOverTo(NcDbObject* newObject);

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

public:
	Nano::ErrorStatus addToPlotSettingsDict(NcDbDatabase* database);

	Nano::ErrorStatus getname(const NCHAR*& name) const;
	Nano::ErrorStatus getname(NCHAR*& name) const;
	Nano::ErrorStatus setname(const NCHAR* name);

	Nano::ErrorStatus getPlotCfgName(const NCHAR*& plotCfgName) const;

	Nano::ErrorStatus getPlotPaperMargins(double& xmin, double& ymin, double& xmax, double& ymax) const;
	Nano::ErrorStatus getPlotPaperSize(double& width, double& height) const;
	Nano::ErrorStatus getPlotPaperSize(NcGePoint2d &paperSize) const;

	Nano::ErrorStatus getCanonicalMediaName(const NCHAR*& name) const;

	Nano::ErrorStatus getPlotOrigin(double& x, double& y) const;
	Nano::ErrorStatus getPlotOrigin(NcGePoint2d &origin) const;

	PlotPaperUnits plotPaperUnits() const;

	NRX::Boolean plotViewportBorders() const;
	void setPlotViewportBorders(NRX::Boolean plot_borders);

	NRX::Boolean plotPlotStyles() const;
	void setPlotPlotStyles(NRX::Boolean plot_styles);

	NRX::Boolean showPlotStyles() const;
	void setShowPlotStyles(NRX::Boolean show_styles);

	PlotRotation plotRotation() const;

	NRX::Boolean plotCentered() const;

	NRX::Boolean plotHidden() const;
	void setPlotHidden(NRX::Boolean plot_hidden);

	ShadePlotType shadePlot() const;
	NcDbObjectId shadePlotId() const;
	Nano::ErrorStatus setShadePlot(ShadePlotType shade_plot);
	Nano::ErrorStatus setShadePlot(const ShadePlotType type, const NcDbObjectId id);


	ShadePlotResLevel shadePlotResLevel() const;

	Nano::ErrorStatus setShadePlotResLevel(ShadePlotResLevel level);

	NRX::Int16 shadePlotCustomDPI() const;
	Nano::ErrorStatus setShadePlotCustomDPI(NRX::Int16 value);

	PlotType plotType() const;
	Nano::ErrorStatus getPlotWindowArea(double& xmin, double& ymin, double& xmax, double& ymax) const;
	Nano::ErrorStatus getPlotViewName(const NCHAR*& name) const;

	NRX::Boolean useStandardScale() const;
	Nano::ErrorStatus getCustomPrintScale(double& numerator, double& denominator) const;
	Nano::ErrorStatus getCurrentStyleSheet(const NCHAR*& sheet) const;

	StdScaleType stdScaleType() const;
	Nano::ErrorStatus getStdScale(double& scale) const;

	NRX::Boolean scaleLineweights() const;
	void setScaleLineweights(NRX::Boolean scale);

	NRX::Boolean printLineweights() const;
	void setPrintLineweights(NRX::Boolean print_lineweights);

	NRX::Boolean drawViewportsFirst() const;
	void setDrawViewportsFirst(NRX::Boolean draw_viewports_first);

	NRX::Boolean modelType() const;

	bool plotWireframe() const;
	bool plotAsRaster() const;

	Nano::ErrorStatus getPlotSettingsName(const NCHAR *& plotSettingsName) const;
	Nano::ErrorStatus getPlotSettingsName (NCHAR*& plotSettingsName) const;
	INcReadStream* getStyleSheetReadStream();
	NRX::Boolean plotTransparency() const;
	Nano::ErrorStatus setPlotSettingsName(const NCHAR * plotSettingsName);
	void setPlotTransparency(NRX::Boolean plotTransparency);

public:
	OdDbPlotSettings* native() const;

protected:
	mutable NcString m_PlotViewName;
	mutable NcString m_PlotCfgName;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbLayout
class OdDbLayout;
class NRXDBGATE_EXPORT NcDbLayout : public NcDbPlotSettings
{
	NCDB_DECLARE_MEMBERS(NcDbLayout);

public:
	typedef NcDbLayout  wrapper_class;
	typedef OdDbLayout  native_class;

public:
	NcDbLayout();

	NcDbLayout(OdRxObject* _object);

	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) ; //+Overload

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subClose() override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

public:
	NcDbObjectId getBlockTableRecordId() const;

	virtual Nano::ErrorStatus setBlockTableRecordId(NcDbObjectId BlockTableRecordId);

	virtual Nano::ErrorStatus addToLayoutDict(NcDbDatabase* towhichDb, NcDbObjectId BlockTableRecordId);

	Nano::ErrorStatus getLayoutName(const NCHAR*& name) const;
	Nano::ErrorStatus getLayoutName(NCHAR*& name) const;
	virtual Nano::ErrorStatus setLayoutName(const NCHAR* name);

	int getTabOrder() const;
	virtual void setTabOrder(int order);

	bool getTabSelected() const;

	virtual void setTabSelected(NRX::Boolean tab);

	NcDbObjectIdArray getViewportArray() const;

#ifdef _WINDOWS_
	Nano::ErrorStatus getThumbnail(BITMAPINFO*& thumbnail) const;
	Nano::ErrorStatus setThumbnail(const BITMAPINFO* thumbnail);
#endif

	void getLimits(NcGePoint2d& limMin, NcGePoint2d& limMax) const;
	void getExtents(NcGePoint3d& extMin, NcGePoint3d& extMax) const;
	Nano::ErrorStatus initialize(NcDbObjectId* paper_space = NULL);
	bool annoAllVisible() const;
	Nano::ErrorStatus setAnnoAllVisible(bool newVal);

public:
	OdDbLayout* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbVisualStyle

// Legacy (shademode) styles
#include "Tchar.h"
const NCHAR kszVSFlat[]                 = L"Flat";
const NCHAR kszVSFlatWithEdges[]        = L"FlatWithEdges";
const NCHAR kszVSGouraud[]              = L"Gouraud";
const NCHAR kszVSGouraudWithEdges[]     = L"GouraudWithEdges";

// Visual Styles
const NCHAR kszVS2DWireframe[]   = L"2dWireframe";
const NCHAR kszVS3DWireframe[]   = L"3dWireframe";
const NCHAR kszVSBasic[]         = L"Basic";
const NCHAR kszVSHidden[]        = L"3D Hidden";
const NCHAR kszVSRealistic[]     = L"Realistic";
const NCHAR kszVSConceptual[]    = L"Conceptual";
const NCHAR kszVSCustom[]        = L"Custom";

// Highlight Visual Styles (internal use only)
const NCHAR kszVSDim[]           = L"Dim";
const NCHAR kszVSBrighten[]      = L"Brighten";
const NCHAR kszVSThicken[]       = L"Thicken";
const NCHAR kszVSTransparent[]   = L"Transparent";
const NCHAR kszVSLinePattern[]   = L"Linepattern";
const NCHAR kszVSFacePattern[]   = L"Facepattern";
const NCHAR kszVSColorChange[]   = L"ColorChange";

// Edge Style Override Visual Styles (internal use only)
const NCHAR kszVSJitterOff[]     = L"JitterOff";
const NCHAR kszVSOverhangOff[]   = L"OverhangOff";
const NCHAR kszVSEdgeColorOff[]  = L"EdgeColorOff";

class OdDbVisualStyle;
class NRXDBGATE_EXPORT NcDbVisualStyle : public NcDbObject
{
public:
	NCDB_DECLARE_MEMBERS(NcDbVisualStyle);

public:
	typedef NcDbVisualStyle wrapper_class;
	typedef OdDbVisualStyle native_class;

public:
	NcDbVisualStyle();
	NcDbVisualStyle(OdRxObject* _object);

	virtual ~NcDbVisualStyle();

	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) ; //+Overload

public:
	Nano::ErrorStatus setDescription(const NCHAR *description_);
	const NCHAR *description(void) const;

	Nano::ErrorStatus setType(NcGiVisualStyle::Type type);
	NcGiVisualStyle::Type type() const;

	void setFaceStyle(const NcGiFaceStyle &style_);
	const NcGiFaceStyle &faceStyle() const;

	void setEdgeStyle(const NcGiEdgeStyle &style_);
	const NcGiEdgeStyle &edgeStyle() const;

	Nano::ErrorStatus setDisplayStyle(const NcGiDisplayStyle &style_);
	const NcGiDisplayStyle &displayStyle() const;

	Nano::ErrorStatus setTrait(NcGiVisualStyleProperties::Property peroperty_, const NcGiVariant *variant_, NcGiVisualStyleOperations::Operation operation_ = NcGiVisualStyleOperations::kSet);
	Nano::ErrorStatus setTrait(NcGiVisualStyleProperties::Property peroperty_, int val_, NcGiVisualStyleOperations::Operation operation_ = NcGiVisualStyleOperations::kSet);
	Nano::ErrorStatus setTrait(NcGiVisualStyleProperties::Property peroperty_, bool val_, NcGiVisualStyleOperations::Operation operation_ = NcGiVisualStyleOperations::kSet);
	Nano::ErrorStatus setTrait(NcGiVisualStyleProperties::Property peroperty_, double val_, NcGiVisualStyleOperations::Operation operation_ = NcGiVisualStyleOperations::kSet);
	Nano::ErrorStatus setTrait(NcGiVisualStyleProperties::Property peroperty_, double red, double green, double blue, NcGiVisualStyleOperations::Operation operation_ = NcGiVisualStyleOperations::kSet);
	Nano::ErrorStatus setTrait(NcGiVisualStyleProperties::Property peroperty_, const NcCmColor *color_, NcGiVisualStyleOperations::Operation operation_ = NcGiVisualStyleOperations::kSet);

	const NcGiVariant& trait(NcGiVisualStyleProperties::Property peroperty_, NcGiVisualStyleOperations::Operation *operation_ = NULL) const;

	Nano::ErrorStatus setTraitFlag(NcGiVisualStyleProperties::Property peroperty_, unsigned long value_, bool bEnable = true);
	bool traitFlag(NcGiVisualStyleProperties::Property peroperty_, unsigned long value_) const;


public:
	virtual bool isInternalUseOnly() const;
	virtual void setInternalUseOnly(bool internal_);

	virtual Nano::ErrorStatus copyTo(NcGiVisualStyle *to_) const;
	virtual Nano::ErrorStatus copyFrom(const NcGiVisualStyle *from_);

// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual NcGiDrawable* drawable() override;

	virtual void setGsNode(NcGsNode* node) override;
	virtual NcGsNode* gsNode() const override;

	virtual Nano::ErrorStatus decomposeForSave(NcDb::NcDbDwgVersion ver, NcDbObject*& replaceObj,
	                                           NcDbObjectId& replaceId, NRX::Boolean& exchangeXData) override;

public:
	OdDbVisualStyle *native() const;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbCustomOsnapInfo
class NRXDBGATE_EXPORT NcDbCustomOsnapInfo : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbCustomOsnapInfo);

	virtual Nano::ErrorStatus getOsnapInfo(NcDbEntity* pickedObject, NRX::GsMarker gsSelectionMark,
	                                       const NcGePoint3d& pickPoint, const NcGePoint3d& lastPoint,
	                                       const NcGeMatrix3d& viewXform, NcArray<NcGePoint3d>& snapPoints,
	                                       NcDbIntArray & geomIdsForPts, NcArray<NcGeCurve3d*>& snapCurves,
	                                       NcDbIntArray & geomIdsForLines) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbCustomOsnapMode
class NRXDBGATE_EXPORT NcDbCustomOsnapMode
{
public:
	virtual ~NcDbCustomOsnapMode() {}

public:
	virtual const NCHAR* localModeString() const
	{
		return NULL;
	}
	virtual const NCHAR* globalModeString() const
	{
		return NULL;
	}

	virtual const NcRxClass* entityOsnapClass() const
	{
		return NULL;
	}

	virtual NcGiGlyph* glyph() const
	{
		return NULL;
	}

	virtual const NCHAR* tooltipString() const
	{
		return NULL;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbGripData
typedef NcDbGripOperations::ReturnValue (*NcGripOperationPtr)(NcDbGripData* grip, const NcDbObjectId& id, int flags); // cast
typedef void (*ContextMenuItemIndexPtr)(unsigned int index); // cast
typedef NcDbGripOperations::ReturnValue (*NcGripRtClkHandler)(NcDbGripDataArray& hot_grips, const NcDbObjectIdArray& ents,
                                                            NCHAR*& menu_name, HMENU& menu, ContextMenuItemIndexPtr& cb); // cast

typedef bool (*NcGripWorldDrawPtr)(NcDbGripData* grip, NcGiWorldDraw* wd, const NcDbObjectId& id,
                                 NcDbGripOperations::DrawType type, NcGePoint3d* image, double grip_size); // need to convert
typedef void (*NcGripViewportDrawPtr)(NcDbGripData* grip, NcGiViewportDrawNrx* pWd, const NcDbObjectId& id,
                                    NcDbGripOperations::DrawType type, NcGePoint3d* image, int grip_size); // need to convert

typedef void (*NcGripOpStatusPtr)(NcDbGripData* grip, const NcDbObjectId& id, NcDbGripOperations::GripStatus stat); // cast
typedef const NCHAR*(*NcGripToolTipPtr)(NcDbGripData* grip); // cast
typedef void (*NcGripDimensionPtr)(NcDbGripData* grip, const NcDbObjectId& id, double scale, NcDbDimDataPtrArray& data); // cast

typedef NcDbGripOperations::ReturnValue (*NcGripInputPointPtr)(NcDbGripData* grip, const NcDbObjectId& id, bool& is_changed,
                                                             NcGePoint3d& custom, const NcGiViewport& context,
                                                             const NcDbObjectId& viewport, bool is_computed, int history,
                                                             const NcGePoint3d& last, const NcGePoint3d& raw,
                                                             const NcGePoint3d& gripped,
                                                             const NcGePoint3d& cartesian_snapped,
                                                             const NcGePoint3d& osnapped, NcDb::OsnapMask osnap_mask,
                                                             const NcArray< NcDbCustomOsnapMode* >& custom_osnap_modes,
                                                             NcDb::OsnapMask osnap_overrides,
                                                             const NcArray< NcDbCustomOsnapMode* >& custom_osnap_overrides,
                                                             const NcArray< NcDbObjectId >& picked,
                                                             const NcArray< NcDbObjectIdArray,
                                                             NcArrayObjectCopyReallocator< NcDbObjectIdArray > >& nested_picked,
                                                             const NcArray< NRX::GsMarker >& markers,
                                                             const NcArray< NcDbObjectId >& key_point_entities,
                                                             const NcArray< NcDbObjectIdArray,
                                                             NcArrayObjectCopyReallocator< NcDbObjectIdArray > >& nested_key_point_entities,
                                                             const NcArray< NRX::GsMarker >& key_point_markers,
                                                             const NcArray< NcGeCurve3d* >& alignment_paths,
                                                             const NcGePoint3d& computed);
class OdDbGripData;
class NcDbGripDataImpl;
class NRXDBGATE_EXPORT NcDbGripData
{
	NcDbGripDataImpl* impl;
public:
	NcDbGripData();
	NcDbGripData(const NcGePoint3d& point, void* data, NcGripOperationPtr hot_grip = NULL,
		         NcGripOperationPtr hover_grip = NULL, NcGripRtClkHandler right_click = NULL, NcGripWorldDrawPtr wd = NULL,
		         NcGripViewportDrawPtr vd = NULL, NcGripOpStatusPtr stat = NULL, NcGripToolTipPtr tt = NULL,
	             NcGripDimensionPtr hover_dim = NULL, NcGripDimensionPtr hot_dim = NULL, unsigned int flags = 0,
	             NcGePoint3d* alt_base = NULL, NcGripInputPointPtr input_point = NULL);
	NcDbGripData(const NcGePoint3d& point, void* data, NcRxClass* rxclass, NcGripOperationPtr hot_grip = NULL,
		         NcGripOperationPtr hover_grip = NULL, NcGripRtClkHandler right_click = NULL, NcGripWorldDrawPtr wd = NULL,
		         NcGripViewportDrawPtr vd = NULL, NcGripOpStatusPtr stat = NULL, NcGripToolTipPtr tt = NULL,
	             NcGripDimensionPtr hoverDim = NULL, NcGripDimensionPtr hot_dim = NULL, unsigned int flags = 0,
	             NcGePoint3d* alt_base = NULL, NcGripInputPointPtr input_point = NULL);

	explicit NcDbGripData(const OdDbGripData& source);
	NcDbGripData(const NcDbGripData& source);
	~NcDbGripData();
public:
	typedef OdDbGripData  native_class;

public:
	NcDbGripData& operator=(const NcDbGripData& source);

	void setAllData(const NcGePoint3d& point, void*, NcGripOperationPtr hot_grip = NULL,
		            NcGripOperationPtr hover_grip = NULL, NcGripRtClkHandler right_click = NULL, NcGripWorldDrawPtr wd = NULL,
		            NcGripViewportDrawPtr vd = NULL, NcGripOpStatusPtr stat = NULL, NcGripToolTipPtr tt = NULL,
	                NcGripDimensionPtr hoverDim = NULL, NcGripDimensionPtr hot_dim = NULL, unsigned int flags = 0,
	                NcGePoint3d* alt_base = NULL, NcGripInputPointPtr input_point = NULL, NcRxClass* rxclass = NULL);

public:
	const NcGePoint3d& gripPoint() const;
	void setGripPoint(const NcGePoint3d& point);

	void* appData() const;
	void setAppData(void* data);

	NcRxClass* appDataNcRxClass() const;
	void setAppDataNcRxClass(NcRxClass* rxclass);

	NcGripOperationPtr hotGripFunc() const;
	void setHotGripFunc(NcGripOperationPtr func);

	NcGripOperationPtr hoverFunc() const;
	void setHoverFunc(NcGripOperationPtr func);

	NcGripRtClkHandler rtClk() const;
	void setRtClk(NcGripRtClkHandler func);

	NcGripWorldDrawPtr worldDraw() const;
	void setWorldDraw(NcGripWorldDrawPtr func);

	NcGripViewportDrawPtr viewportDraw() const;
	void setViewportDraw(NcGripViewportDrawPtr func);

	NcGripOpStatusPtr gripOpStatFunc() const;
	void setGripOpStatFunc(NcGripOpStatusPtr func);

	NcGripToolTipPtr toolTipFunc() const;
	void setToolTipFunc(NcGripToolTipPtr func);

	NcGripDimensionPtr hoverDimensionFunc() const;
	void setHoverDimensionFunc(NcGripDimensionPtr func);

	NcGripDimensionPtr hotGripDimensionFunc() const;
	void setHotGripDimensionFunc(NcGripDimensionPtr func);

	NcGePoint3d* alternateBasePoint() const;
	void setAlternateBasePoint(NcGePoint3d* point);

	unsigned int bitFlags() const;
	void setBitFlags(unsigned int flags);

public:
	bool skipWhenShared() const;
	void setSkipWhenShared(bool skip);

	bool isRubberBandLineDisabled() const;
	void disableRubberBandLine(bool disable);

	bool areModeKeywordsDisabled() const;
	void disableModeKeywords(bool disable);

	bool drawAtDragImageGripPoint() const;
	void setDrawAtDragImageGripPoint(bool on);

	bool triggerGrip() const;
	void setTriggerGrip(bool trigger);

	NcGripInputPointPtr inputPointFunc() const;
	void setInputPointFunc(NcGripInputPointPtr func);

	bool forcedPickOn() const;
	void setForcedPickOn(bool on);

	bool mapGripHotToRtClk() const;
	void setMapGripHotToRtClk(bool on);

	bool gizmosEnabled() const;
	void setGizmosEnabled(bool on);

public:
	OdDbGripData* native() const;

protected:
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbEntity
class NRXDBGATE_EXPORT NcDbEntity : public NcDbObject
{
	NCDB_DECLARE_MEMBERS(NcDbEntity);

protected:
	NcDbEntity();

public:
	NcDbEntity(OdRxObject* _object);
	virtual ~NcDbEntity();

	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) ; //+Overload
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) ; //+Overload

public:
	typedef NcDbEntity  wrapper_class;
	typedef OdDbEntity  native_class;

	enum VisualStyleType
	{
		kFullVisualStyle,
		kFaceVisualStyle,
		kEdgeVisualStyle
	};


	// NcGiDrawable interface
public:
	virtual void setGsNode(NcGsNode* node) override;
	virtual NcGsNode* gsNode() const override;

	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;

public:
	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo) override;

	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;

	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual NcGiDrawable* drawable() override;

	virtual Nano::ErrorStatus applyPartialUndo(NcDbDwgFiler* filer, NcRxClass* rxclass) override;

public:
	NcDbObjectId blockId() const;

	NcCmColor color() const;
	virtual Nano::ErrorStatus setColor(const NcCmColor& color, NRX::Boolean subents = true);
	NRX::UInt16 colorIndex() const;
	virtual Nano::ErrorStatus setColorIndex(NRX::UInt16 color, NRX::Boolean subents = true);
	NcCmEntityColor entityColor() const;

	NcCmTransparency transparency() const;
	virtual Nano::ErrorStatus setTransparency(const NcCmTransparency& trans, NRX::Boolean subents = true);

	NCHAR* plotStyleName() const;
	NcDb::PlotStyleNameType getPlotStyleNameId(NcDbObjectId& id) const;
	virtual Nano::ErrorStatus setPlotStyleName(const NCHAR* name, NRX::Boolean subents = true);
	virtual Nano::ErrorStatus setPlotStyleName(NcDb::PlotStyleNameType, NcDbObjectId newId = NcDbObjectId::kNull,
	                                           NRX::Boolean subents = true);

	NCHAR* layer() const;
	NcDbObjectId layerId() const;
	virtual Nano::ErrorStatus setLayer(const NCHAR* name, NRX::Boolean subents = true,
	                                   bool allowHiddenLayer = false);
	virtual Nano::ErrorStatus setLayer(NcDbObjectId id, NRX::Boolean subents = true,
	                                   bool allowHiddenLayer = false);

	NCHAR* linetype() const;
	NcDbObjectId linetypeId() const;
	virtual Nano::ErrorStatus setLinetype(const NCHAR* linetype, NRX::Boolean subents = true);
	virtual Nano::ErrorStatus setLinetype(NcDbObjectId linetype, NRX::Boolean subents = true);

	NCHAR* material() const;
	NcDbObjectId materialId() const;
	virtual Nano::ErrorStatus setMaterial(const NCHAR* material, NRX::Boolean subents = true);
	virtual Nano::ErrorStatus setMaterial(NcDbObjectId material, NRX::Boolean subents = true);

	virtual Nano::ErrorStatus setVisualStyle(NcDbObjectId id, VisualStyleType type = kFullVisualStyle,
	                                         NRX::Boolean subents = true);

	NcDbObjectId visualStyleId(VisualStyleType type = kFullVisualStyle) const;

	virtual Nano::ErrorStatus getMaterialMapper(NcGiMapper& mapper) const;
	virtual Nano::ErrorStatus setMaterialMapper(const NcGiMapper& mapper, NRX::Boolean subents = true);

	double linetypeScale() const;
	virtual Nano::ErrorStatus setLinetypeScale(double scale, NRX::Boolean subents = true);

	NcDb::Visibility visibility() const;
	virtual Nano::ErrorStatus setVisibility(NcDb::Visibility visible, NRX::Boolean subents = true); //  sealed !!!
	virtual Nano::ErrorStatus subSetVisibility(NcDb::Visibility visible, NRX::Boolean subents = true);

	NcDb::LineWeight lineWeight() const;
	virtual Nano::ErrorStatus setLineWeight(NcDb::LineWeight lw, NRX::Boolean subents = true);

	virtual NcDb::CollisionType collisionType() const;

	virtual bool castShadows() const;
	virtual void setCastShadows(bool flag);
	virtual bool receiveShadows() const;
	virtual void setReceiveShadows(bool flag);

	Nano::ErrorStatus setPropertiesFrom(const NcDbEntity* pEntity, NRX::Boolean subents = true);

	virtual NRX::Boolean isPlanar() const;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const;

	virtual void getEcs(NcGeMatrix3d& matrix) const;

	virtual Nano::ErrorStatus getGeomExtents(NcDbExtents& extents) const sealed;

	virtual Nano::ErrorStatus addSubentPaths(const NcDbFullSubentPathArray& newPaths) sealed;
	virtual Nano::ErrorStatus deleteSubentPaths(const NcDbFullSubentPathArray& paths) sealed;
	virtual Nano::ErrorStatus getSubentClassId(const NcDbFullSubentPath& path, CLSID* clsid) const sealed;
	virtual Nano::ErrorStatus transformSubentPathsBy(const NcDbFullSubentPathArray& paths,
	                                                 const NcGeMatrix3d& xform) sealed;

	virtual Nano::ErrorStatus getGripPointsAtSubentPath(const NcDbFullSubentPath& path, NcDbGripDataPtrArray& grips,
	                                                    const double curViewUnitSize, const int gripSize,
	                                                    const NcGeVector3d& curViewDir,
	                                                    const int bitflags) const sealed;
	virtual Nano::ErrorStatus moveGripPointsAtSubentPaths(const NcDbFullSubentPathArray& paths,
	                                                      const NcDbVoidPtrArray& gripAppData,
	                                                      const NcGeVector3d& offset,
	                                                      const int bitflags) sealed;

	virtual Nano::ErrorStatus getSubentPathGeomExtents(const NcDbFullSubentPath& path,
	                                                   NcDbExtents& extents) const sealed;

	virtual Nano::ErrorStatus getSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                   const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                   int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                   int numInserts = 0,
	                                                   NcDbObjectId* entAndInsertStack = NULL) const sealed;

	virtual Nano::ErrorStatus getGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                   NcArray< NRX::GsMarker >& markers) const sealed;

	virtual Nano::ErrorStatus highlight(const NcDbFullSubentPath& subId = kNullSubent,
	                                    const NRX::Boolean all = false) const sealed;
	virtual Nano::ErrorStatus unhighlight(const NcDbFullSubentPath& subId = kNullSubent,
	                                      const NRX::Boolean all = false) const sealed;
	virtual NcDbEntity* subentPtr(const NcDbFullSubentPath& id) const sealed;

	virtual Nano::ErrorStatus getOsnapPoints(NcDb::OsnapMode osnapMode, NRX::GsMarker marker,
	                                         const NcGePoint3d& pick, const NcGePoint3d& last,
	                                         const NcGeMatrix3d& xform, NcGePoint3dArray& snaps,
	                                         NcDbIntArray& markers) const sealed;
	virtual Nano::ErrorStatus getOsnapPoints(NcDb::OsnapMode osnapMode, NRX::GsMarker marker,
	                                         const NcGePoint3d& pick, const NcGePoint3d& last,
	                                         const NcGeMatrix3d& xform, NcGePoint3dArray& snaps,
	                                         NcDbIntArray& markers,
	                                         const NcGeMatrix3d& insertionMat) const sealed;

	virtual bool isContentSnappable() const sealed;

	virtual Nano::ErrorStatus getGripPoints(NcGePoint3dArray& grips, NcDbIntArray& osnapModes,
	                                        NcDbIntArray& markers) const sealed;
	virtual Nano::ErrorStatus moveGripPointsAt(const NcDbIntArray& indices, const NcGeVector3d& offset) sealed;

	virtual Nano::ErrorStatus getGripPoints(NcDbGripDataPtrArray& grips, const double curViewUnitSize,
	                                        const int gripSize, const NcGeVector3d& curViewDir,
	                                        const int bitflags) const sealed;
	virtual Nano::ErrorStatus moveGripPointsAt(const NcDbVoidPtrArray& gripAppData, const NcGeVector3d& offset,
	                                           const int bitflags) sealed;

	virtual Nano::ErrorStatus getStretchPoints(NcGePoint3dArray& stretchPoints) const sealed;
	virtual Nano::ErrorStatus moveStretchPointsAt(const NcDbIntArray& indices, const NcGeVector3d& offset) sealed;

	virtual Nano::ErrorStatus intersectWith(const NcDbEntity* entity, NcDb::Intersect intType,
	                                        NcGePoint3dArray& points, NRX::GsMarker this_marker = 0,
	                                        NRX::GsMarker other_marker = 0) const sealed;
	virtual Nano::ErrorStatus intersectWith(const NcDbEntity* entity, NcDb::Intersect intType, const NcGePlane& plane,
	                                        NcGePoint3dArray& points, NRX::GsMarker this_marker = 0,
	                                        NRX::GsMarker other_marker = 0) const sealed;

	Nano::ErrorStatus boundingBoxIntersectWith(const NcDbEntity* entity, NcDb::Intersect intType,
	                                           NcGePoint3dArray& points, NRX::GsMarker this_marker,
	                                           NRX::GsMarker other_marker) const;
	Nano::ErrorStatus boundingBoxIntersectWith(const NcDbEntity* entity, NcDb::Intersect intType,
	                                           const NcGePlane& plane, NcGePoint3dArray& points,
	                                           NRX::GsMarker this_marker,
	                                           NRX::GsMarker other_marker) const;

	virtual void list() const sealed;

	virtual Nano::ErrorStatus transformBy(const NcGeMatrix3d& xform) sealed;
	virtual Nano::ErrorStatus getTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const sealed;
	virtual Nano::ErrorStatus explode(NcDbVoidPtrArray& set) const sealed;

	void recordGraphicsModified(NRX::Boolean modified = true);

	Nano::ErrorStatus draw();
	virtual void saveAs(NcGiWorldDraw* mode, NcDb::SaveType st);

	virtual Nano::ErrorStatus getCompoundObjectTransform(NcGeMatrix3d& xMat) const sealed;

	void setDatabaseDefaults();
	void setDatabaseDefaults(NcDbDatabase* database);
	virtual void subSetDatabaseDefaults(NcDbDatabase* database);

	virtual NRX::Boolean cloneMeForDragging() sealed;
	virtual bool hideMeForDragging() const sealed;

	virtual void dragStatus(const NcDb::DragStat status);
	virtual void gripStatus(const NcDb::GripStat status) sealed;
	virtual void subentGripStatus(const NcDb::GripStat status, const NcDbFullSubentPath& subentity) sealed;

	virtual Nano::ErrorStatus getGripEntityUCS(const void* pGripAppData, NcGeVector3d& normal, NcGePoint3d& origin,
	                                           NcGeVector3d& xAxis) const sealed;

	virtual bool bounds(NcDbExtents& bounds) const;

	NcGiHighlightStyle highlightState (const NcDbFullSubentPath& subId);
	Nano::ErrorStatus  popHighlight      (const NcDbFullSubentPath& subId);

	Nano::ErrorStatus  pushHighlight     (const NcDbFullSubentPath& subId,NcGiHighlightStyle highlightStyle);
	NcGiHighlightStyle subHighlightState (const NcDbFullSubentPath& subId);
	Nano::ErrorStatus  subPopHighlight   (const NcDbFullSubentPath& subId);

	Nano::ErrorStatus  subPushHighlight  (const NcDbFullSubentPath& subId,NcGiHighlightStyle highlightStyle);
	NcDb::Visibility  subVisibility() const;

	virtual Nano::ErrorStatus copyFrom(const NcRxObject*);

protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;
	virtual void subList() const;

	virtual Nano::ErrorStatus subGetOsnapPoints(NcDb::OsnapMode osnapMode, NRX::GsMarker marker,
	                                            const NcGePoint3d& pick, const NcGePoint3d& last,
	                                            const NcGeMatrix3d& xform, NcGePoint3dArray& snaps,
	                                            NcDbIntArray& markers) const;
	virtual Nano::ErrorStatus subGetOsnapPoints(NcDb::OsnapMode osnapMode, NRX::GsMarker marker,
	                                            const NcGePoint3d& pick, const NcGePoint3d& last,
	                                            const NcGeMatrix3d& xform, NcGePoint3dArray& snaps,
	                                            NcDbIntArray& markers,
	                                            const NcGeMatrix3d& insertionMat) const;

	virtual bool subIsContentSnappable() const;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform);
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const;
	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const;
	virtual NRX::Boolean subCloneMeForDragging();
	virtual bool subHideMeForDragging() const;

	virtual Nano::ErrorStatus subGetGripPoints(NcGePoint3dArray& grips, NcDbIntArray& osnapModes,
	                                           NcDbIntArray& markers) const;

	virtual Nano::ErrorStatus subGetGripPoints(NcDbGripDataPtrArray& grips, const double curViewUnitSize,
	                                           const int gripSize, const NcGeVector3d& curViewDir,
	                                           const int bitflags) const;

	virtual Nano::ErrorStatus subMoveGripPointsAt(const NcDbIntArray& indices, const NcGeVector3d& offset);
	virtual Nano::ErrorStatus subMoveGripPointsAt(const NcDbVoidPtrArray& gripAppData, const NcGeVector3d& offset,
	                                              const int bits);

	virtual Nano::ErrorStatus subGetStretchPoints(NcGePoint3dArray& points) const;

	virtual Nano::ErrorStatus subMoveStretchPointsAt(const NcDbIntArray& indices, const NcGeVector3d& offset);

	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const;

	virtual Nano::ErrorStatus subGetSubentClassId(const NcDbFullSubentPath& path, CLSID* clsid) const;

	virtual Nano::ErrorStatus subAddSubentPaths(const NcDbFullSubentPathArray& paths);
	virtual Nano::ErrorStatus subDeleteSubentPaths(const NcDbFullSubentPathArray& paths);
	virtual Nano::ErrorStatus subTransformSubentPathsBy(const NcDbFullSubentPathArray& paths,
	                                                    const NcGeMatrix3d& xform);

	virtual Nano::ErrorStatus subGetGripPointsAtSubentPath(const NcDbFullSubentPath& path, NcDbGripDataPtrArray& grips,
	                                                       const double curViewUnitSize, const int gripSize,
	                                                       const NcGeVector3d& curViewDir,
	                                                       const int bitflags) const;
	virtual Nano::ErrorStatus subMoveGripPointsAtSubentPaths(const NcDbFullSubentPathArray& paths,
	                                                         const NcDbVoidPtrArray& gripAppData,
	                                                         const NcGeVector3d& offset,
	                                                         const int bitflags);

	virtual Nano::ErrorStatus subGetSubentPathGeomExtents(const NcDbFullSubentPath& path, NcDbExtents& extents) const;

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                      const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const;

	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& markers) const;

	virtual NcDbEntity* subSubentPtr(const NcDbFullSubentPath& id) const;

	virtual void subGripStatus(const NcDb::GripStat status);
	virtual void subSubentGripStatus(const NcDb::GripStat status, const NcDbFullSubentPath& subentity);

	virtual Nano::ErrorStatus subHighlight(const NcDbFullSubentPath& subId = kNullSubent,
	                                       const NRX::Boolean all = false) const;
	virtual Nano::ErrorStatus subUnhighlight(const NcDbFullSubentPath& subId = kNullSubent,
	                                         const NRX::Boolean all = false) const;

	virtual Nano::ErrorStatus subIntersectWith(const NcDbEntity* entity, NcDb::Intersect intType,
	                                           NcGePoint3dArray& points, NRX::GsMarker this_marker = 0,
	                                           NRX::GsMarker other_marker = 0) const;
	virtual Nano::ErrorStatus subIntersectWith(const NcDbEntity* entity, NcDb::Intersect intType,
	                                           const NcGePlane& plane, NcGePoint3dArray& points,
	                                           NRX::GsMarker this_marker = 0,
	                                           NRX::GsMarker other_marker = 0) const;

	virtual Nano::ErrorStatus subGetGripEntityUCS(const void* pGripAppData, NcGeVector3d& normal, NcGePoint3d& origin,
	                                              NcGeVector3d& xAxis) const;
	virtual Nano::ErrorStatus subGetCompoundObjectTransform(NcGeMatrix3d& matrix) const;

	virtual Nano::ErrorStatus subWblockClone(NcRxObject* pOwnerObject,NcDbObject*& pClonedObject,NcDbIdMapping& idMap,
	                                         NRX::Boolean isPrimary = true) const;

	virtual Nano::ErrorStatus subErase(NRX::Boolean erasing);

	virtual Nano::ErrorStatus subDeepClone(NcDbObject* pOwnerObject, NcDbObject*& pClonedObject,
	                                       NcDbIdMapping& idMap, NRX::Boolean isPrimary = NRX::kTrue) const;

public:
	OdDbEntity* native() const;

protected:
	virtual OdRxObject* GetNativeObject() const;

public:
	static NcDbEntity* attach(const OdDbEntity* _entity);
};

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOpenNcDbEntity(NcDbEntity*& entity, NcDbObjectId id, NcDb::OpenMode mode,
                                                      bool open_erased = false);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbObjectIterator
class OdDbObjectIterator;
class NRXDBGATE_EXPORT NcDbObjectIterator : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbObjectIterator);

	NcDbObjectIterator(OdRxObject* _object);
	virtual ~NcDbObjectIterator();

public:
	typedef OdDbObjectIterator  native_class;

public:
	bool done() const;

	void step(bool backwards = false, bool skip_deleted = true);

	void setPosition(NcDbEntity* entity);
	void setPosition(NcDbObjectId id);

	void start(bool at_end = false);

	NcDbEntity* entity();
	NcDbObjectId objectId();

public:
	OdDbObjectIterator* native() const;
private:
	NcArray< NcDbEntity* > m_arrEntity;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbBlockReference
class OdDbBlockReference;
class NRXDBGATE_EXPORT NcDbBlockReference : public NcDbEntity
{
public:
	NCDB_DECLARE_MEMBERS(NcDbBlockReference);

public:
	NcDbBlockReference();
	NcDbBlockReference(const NcGePoint3d& pos, NcDbObjectId id);

	NcDbBlockReference(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) ; //+Overload
	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subClose() override;

	virtual Nano::ErrorStatus subHandOverTo(NcDbObject* newObject);

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;
	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const override;

	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const override;

	virtual Nano::ErrorStatus subGetCompoundObjectTransform(NcGeMatrix3d& matrix) const sealed;

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                      const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const sealed;

	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& markers) const sealed;

public:
	typedef NcDbBlockReference  wrapper_class;
	typedef OdDbBlockReference  native_class;

	NcDbObjectId blockTableRecord() const;
	virtual Nano::ErrorStatus setBlockTableRecord(NcDbObjectId);

	NcGePoint3d position() const;
	virtual Nano::ErrorStatus setPosition(const NcGePoint3d&);

	NcGeScale3d scaleFactors() const;
	NcGeScale3d nonAnnotationScaleFactors() const;
	virtual Nano::ErrorStatus setScaleFactors(const NcGeScale3d& scale);

	double rotation() const;
	virtual Nano::ErrorStatus setRotation(double newVal);

	NcGeVector3d normal() const;
	virtual Nano::ErrorStatus setNormal(const NcGeVector3d& newVal);

	NcGeMatrix3d blockTransform() const;
	NcGeMatrix3d nonAnnotationBlockTransform() const;
	virtual Nano::ErrorStatus setBlockTransform(const NcGeMatrix3d&);

	Nano::ErrorStatus appendAttribute(NcDbAttribute* attribute);
	Nano::ErrorStatus appendAttribute(NcDbObjectId& id, NcDbAttribute* attribute);

	Nano::ErrorStatus openAttribute(NcDbAttribute*& attribute, NcDbObjectId id, NcDb::OpenMode mode,
	                                bool open_erased = false);
	Nano::ErrorStatus openSequenceEnd(NcDbSequenceEnd*& end, NcDb::OpenMode mode);

	NcDbObjectIterator* attributeIterator() const;

	virtual NRX::Boolean treatAsNcDbBlockRefForExplode() const;

	Nano::ErrorStatus geomExtentsBestFit(NcDbExtents& extents,
	                                     const NcGeMatrix3d& xform = NcGeMatrix3d::kIdentity) const;

	virtual Nano::ErrorStatus explodeToOwnerSpace() const;

public:
	OdDbBlockReference* native() const;

	virtual OdRxObject* GetNativeObject() const override;
};

#define DimDataSetValueFuncPtr odtDimDataSetValueFuncPtr

typedef NcGeVector3d (*odtDimDataSetValueFuncPtr)(NcDbDimData* pThis, NcDbEntity* pEnt, double newValue,
                                                  const NcGeVector3d& offset);
typedef NcGeVector3d (*odtDimDataSetCustomStringFuncPtr)(NcDbDimData* pThis, NcDbEntity* pEnt,
                                                         const NCHAR* pCustomString, const NcGeVector3d& offset);

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbMText

struct NcDbMTextFragment
{
	NcGePoint3d     location;
	NcGeVector3d    normal;
	NcGeVector3d    direction;

	NCHAR*          text;

	NCHAR*          font;
	NCHAR*          bigfont;

	NcGePoint2d     extents;
	double          capsHeight;
	double          widthFactor;
	double          obliqueAngle;
	double          trackingFactor;
	NcCmEntityColor color;

	unsigned        stackTop:1;
	unsigned        stackBottom:1;

	unsigned        underlined:1;
	unsigned        overlined:1;
	NcGePoint3d     underPoints[2];
	NcGePoint3d     overPoints[2];

	NCHAR*          fontname;
	bool            bold;
	bool            italic;
};


typedef int (*NcDbMTextEnum)(NcDbMTextFragment*, void*);

class OdDbMText;
class NRXDBGATE_EXPORT NcDbMText : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbMText);

public:
	typedef NcDbMText  wrapper_class;
	typedef OdDbMText  native_class;

public:
	NcDbMText();

	NcDbMText(OdRxObject* _object);

	virtual Nano::ErrorStatus removeField(NcDbObjectId id) ; // +Overload
	Nano::ErrorStatus removeField(const NCHAR* pszPropName);
	Nano::ErrorStatus removeField(const NCHAR* pszPropName, NcDbObjectId& returnId);
	virtual NcDb::TextVertMode verticalMode() const; //+Overload2
	virtual NcDb::TextHorzMode horizontalMode() const; //+Overload2

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subClose() override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;
	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const override;

	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const override;

public:
	// Insertion point
	NcGePoint3d location() const;
	Nano::ErrorStatus setLocation(const NcGePoint3d& location);

	// Normal vector
	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

	// Direction vector
	NcGeVector3d direction() const;
	Nano::ErrorStatus setDirection(const NcGeVector3d& direction);

	// Rotation angle(radians)
	double rotation() const;
	Nano::ErrorStatus setRotation(double rotation);

	double height() const;
	Nano::ErrorStatus setHeight(double height);

	// Entity width(constraining value)
	double width() const;
	Nano::ErrorStatus setWidth(double width);

	// Descent/Ascent
	double ascent() const;
	double descent() const;

	// Text Style(sets initial font)
	NcDbObjectId textStyle() const;
	Nano::ErrorStatus setTextStyle(NcDbObjectId style);

	// Initial text height(caps height)
	double textHeight() const;
	Nano::ErrorStatus setTextHeight(double height);

	enum AttachmentPoint
	{
		kTopLeft        = 1,    // Top Left
		kTopCenter      = 2,    // Top Center
		kTopRight       = 3,    // Top Right
		kMiddleLeft     = 4,    // Middle Left
		kMiddleCenter   = 5,    // Middle Center
		kMiddleRight    = 6,    // Middle Right
		kBottomLeft     = 7,    // Bottom Left
		kBottomCenter   = 8,    // Bottom Center
		kBottomRight    = 9,    // Bottom Right
		kBaseLeft       = 10,   // Baseline Left /reserved for future use/
		kBaseCenter     = 11,   // Baseline Center /reserved for future use/
		kBaseRight      = 12,   // Baseline Right /reserved for future use/
		kBaseAlign      = 13,   // Baseline Aligned /reserved for future use/
		kBottomAlign    = 14,   // Bottom Aligned /reserved for future use/
		kMiddleAlign    = 15,   // Middle Aligned /reserved for future use/
		kTopAlign       = 16,   // Top Aligned /reserved for future use/
		kBaseFit        = 17,   // Baseline Fit /reserved for future use/
		kBottomFit      = 18,   // Bottom Fit /reserved for future use/
		kMiddleFit      = 19,   // Middle Fit /reserved for future use/
		kTopFit         = 20,   // Top Fit /reserved for future use/
		kBaseMid        = 21,   // Baseline Middled /reserved for future use/
		kBottomMid      = 22,   // Bottom Middled /reserved for future use/
		kMiddleMid      = 23,   // Middle Middled /reserved for future use/
		kTopMid         = 24    // Top Middled /reserved for future use/
	};

	AttachmentPoint attachment() const;
	Nano::ErrorStatus setAttachment(AttachmentPoint anchor);
	Nano::ErrorStatus setAttachmentMovingLocation(AttachmentPoint anchor);

	enum FlowDirection
	{
		kLtoR     = 1,  // Left to Right
		kRtoL     = 2,  // Right to Left
		kTtoB     = 3,  // Top to Bottom
		kBtoT     = 4,  // Bottom to Top
		kByStyle  = 5   // By Style
	};

	FlowDirection flowDirection() const;
	Nano::ErrorStatus setFlowDirection(FlowDirection direction);

	NCHAR* contents() const;
	int setContents(const NCHAR* contents);
	int setContentsRTF(const NCHAR* contents);

	double actualHeight(NcGiWorldDraw* context = NULL) const;
	double actualWidth() const;

	int correctSpelling();

	void getBoundingPoints(NcGePoint3dArray& points) const;

	void explodeFragments(NcDbMTextEnum func, void* params, NcGiWorldDraw* ctxt = NULL) const;

	NCHAR* NcDbMText::text() const;

	static const NCHAR* const nonBreakSpace();
	static const NCHAR* const overlineOn();
	static const NCHAR* const overlineOff();
	static const NCHAR* const underlineOn();
	static const NCHAR* const underlineOff();
	static const NCHAR* const colorChange();
	static const NCHAR* const fontChange();
	static const NCHAR* const heightChange();
	static const NCHAR* const widthChange();
	static const NCHAR* const obliqueChange();
	static const NCHAR* const trackChange();
	static const NCHAR* const lineBreak();
	static const NCHAR* const paragraphBreak();
	static const NCHAR* const stackStart();
	static const NCHAR* const alignChange();
	static const NCHAR* const blockBegin();
	static const NCHAR* const blockEnd();
	static const NCHAR* const strikethroughOn();
	static const NCHAR* const strikethroughOff();

	Nano::ErrorStatus setLineSpacingStyle(NcDb::LineSpacingStyle style);
	NcDb::LineSpacingStyle lineSpacingStyle() const;

	Nano::ErrorStatus setLineSpacingFactor(double factor);

	double lineSpacingFactor() const;

	bool backgroundFillOn() const;
	Nano::ErrorStatus setBackgroundFill(bool enable);

	Nano::ErrorStatus getBackgroundFillColor(NcCmColor& color) const;
	Nano::ErrorStatus setBackgroundFillColor(const NcCmColor& color);

	Nano::ErrorStatus getBackgroundScaleFactor(double& scale) const;
	Nano::ErrorStatus setBackgroundScaleFactor(const double scale);

	Nano::ErrorStatus getBackgroundTransparency(NcCmTransparency& transparency) const;
	Nano::ErrorStatus setBackgroundTransparency(const NcCmTransparency& transparency);

	bool useBackgroundColorOn() const;
	Nano::ErrorStatus setUseBackgroundColor(bool enable);

	Nano::ErrorStatus convertFieldToText();

	enum ColumnType 
	{
		kNoColumns,
		kStaticColumns,
		kDynamicColumns
	};

	Nano::ErrorStatus getColumnType(ColumnType& type) const;

	Nano::ErrorStatus getColumnAutoHeight(bool&) const;
	Nano::ErrorStatus getColumnCount(int&) const;
	Nano::ErrorStatus getColumnFlowReversed(bool&) const;
	Nano::ErrorStatus getColumnGutterWidth(double&) const;
	Nano::ErrorStatus getColumnHeight(int, double&) const;
	Nano::ErrorStatus getColumnWidth(double&) const;
	//void getEcs(NcGeMatrix3d& retVal) const;
	Nano::ErrorStatus setColumnAutoHeight(bool);
	Nano::ErrorStatus setColumnCount(int);
	Nano::ErrorStatus setColumnFlowReversed(bool);
	Nano::ErrorStatus setColumnGutterWidth(double);
	Nano::ErrorStatus setColumnHeight(int, double);
	Nano::ErrorStatus setColumnType(ColumnType);
	Nano::ErrorStatus setColumnWidth(double);
	Nano::ErrorStatus setDynamicColumns(double width, double gutter, bool auto_height);
	Nano::ErrorStatus   setField(const NCHAR* pszPropName,NcDbField* pField,NcDbObjectId& fieldId);
	Nano::ErrorStatus setStaticColumns(double width, double gutter, int count);
	Nano::ErrorStatus   setUseWordBreak(bool bEnable);
	bool useWordBreak() const;


public:
	OdDbMText* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDimension
class OdDbDimension;
class NRXDBGATE_EXPORT NcDbDimension : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbDimension);

public:
	typedef NcDbDimension  wrapper_class;
	typedef OdDbDimension  native_class;

	enum DimInspect
	{
		kShapeRemove  = 0x00,     // No inspection label displays.
		kShapeRound   = 0x01,     // Inspection label displays with a rounded end (this is the default).
		kShapeAngular = 0x02,     // Inspection label displays with an angular end.
		kShapeNone    = 0x04,     // Inspection label displays without a bounding shape.
		kShapeLabel   = 0x10,     // Inspection label displays with a prefix, including a separator and alpha field.
		kShapeRate    = 0x20      // Inspection label displays at a specified frequency.
	};

public:
	NcDbDimension();
	NcDbDimension(OdRxObject* _object);

	//~NcDbDimension(){};

	// NcGiDrawable interface
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subClose() override;
	virtual void modified(const NcDbObject* object) override;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;
	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const override;

	virtual void subSetDatabaseDefaults(NcDbDatabase* database) override;

	virtual Nano::ErrorStatus subGetCompoundObjectTransform(NcGeMatrix3d& matrix) const override;

public:
	virtual int dimadec() const;
	virtual bool dimalt() const;
	virtual int dimaltd() const;
	virtual double dimaltf() const;
	virtual double dimaltrnd() const;
	virtual int dimalttd() const;
	virtual int dimalttz() const;
	virtual int dimaltu() const;
	virtual int dimaltz() const;
	virtual const NCHAR* dimapost() const;
	virtual int dimarcsym() const;
	virtual double dimasz() const;
	virtual int dimatfit() const;
	virtual int dimaunit() const;
	virtual int dimazin() const;
	virtual NcDbObjectId dimblk() const;
	virtual NcDbObjectId dimblk1() const;
	virtual NcDbObjectId dimblk2() const;
	virtual double dimcen() const;
	virtual NcCmColor dimclrd() const;
	virtual NcCmColor dimclre() const;
	virtual NcCmColor dimclrt() const;
	virtual int dimdec() const;
	virtual double dimdle() const;
	virtual double dimdli() const;
	virtual NCHAR dimdsep() const;
	virtual double dimexe() const;
	virtual double dimexo() const;
	virtual int dimfrac() const;
	virtual double dimgap() const;
	virtual double dimjogang() const;
	virtual int dimjust() const;
	virtual NcDbObjectId dimldrblk() const;
	virtual double dimlfac() const;
	virtual bool dimlim() const;
	virtual NcDbObjectId dimltex1() const;
	virtual NcDbObjectId dimltex2() const;
	virtual NcDbObjectId dimltype() const;
	virtual int dimlunit() const;
	virtual NcDb::LineWeight dimlwd() const;
	virtual NcDb::LineWeight dimlwe() const;
	virtual const NCHAR* dimpost() const;
	virtual double dimrnd() const;
	virtual bool dimsah() const;
	virtual double dimscale() const;
	virtual bool dimsd1() const;
	virtual bool dimsd2() const;
	virtual bool dimse1() const;
	virtual bool dimse2() const;
	virtual bool dimsoxd() const;
	virtual int dimtad() const;
	virtual int dimtdec() const;
	virtual double dimtfac() const;
	virtual int dimtfill() const;
	virtual NcCmColor dimtfillclr() const;
	virtual bool dimtih() const;
	virtual bool dimtix() const;
	virtual double dimtm() const;
	virtual int dimtmove() const;
	virtual bool dimtofl() const;
	virtual bool dimtoh() const;
	virtual bool dimtol() const;
	virtual int dimtolj() const;
	virtual double dimtp() const;
	virtual double dimtsz() const;
	virtual double dimtvp() const;
	virtual NcDbObjectId dimtxsty() const;
	virtual double dimtxt() const;
	virtual int dimtzin() const;
	virtual bool dimupt() const;
	virtual int dimzin() const;

	virtual bool dimtxtdirection() const;
	virtual double dimmzf() const;
	virtual const NCHAR* dimmzs() const;
	virtual double dimaltmzf() const;
	virtual const NCHAR* dimaltmzs() const;

	virtual Nano::ErrorStatus setDimadec(int v);
	virtual Nano::ErrorStatus setDimalt(bool v);
	virtual Nano::ErrorStatus setDimaltd(int v);
	virtual Nano::ErrorStatus setDimaltf(double v);
	virtual Nano::ErrorStatus setDimaltmzf(double v);
	virtual Nano::ErrorStatus setDimaltmzs(const NCHAR* v);
	virtual Nano::ErrorStatus setDimaltrnd(double v);
	virtual Nano::ErrorStatus setDimalttd(int v);
	virtual Nano::ErrorStatus setDimalttz(int v);
	virtual Nano::ErrorStatus setDimaltu(int v);
	virtual Nano::ErrorStatus setDimaltz(int v);
	virtual Nano::ErrorStatus setDimapost(const NCHAR* v);
	virtual Nano::ErrorStatus setDimarcsym(int v);
	virtual Nano::ErrorStatus setDimasz(double v);
	virtual Nano::ErrorStatus setDimatfit(int v);
	virtual Nano::ErrorStatus setDimaunit(int v);
	virtual Nano::ErrorStatus setDimazin(int v);
	virtual Nano::ErrorStatus setDimblk(NcDbObjectId v);
	virtual Nano::ErrorStatus setDimblk1(NcDbObjectId v);
	virtual Nano::ErrorStatus setDimblk2(NcDbObjectId v);
	virtual Nano::ErrorStatus setDimcen(double v);
	virtual Nano::ErrorStatus setDimclrd(const NcCmColor& v);
	virtual Nano::ErrorStatus setDimclre(const NcCmColor& v);
	virtual Nano::ErrorStatus setDimclrt(const NcCmColor& v);
	virtual Nano::ErrorStatus setDimdec(int v);
	virtual Nano::ErrorStatus setDimdle(double v);
	virtual Nano::ErrorStatus setDimdli(double v);
	virtual Nano::ErrorStatus setDimdsep(NCHAR v);
	virtual Nano::ErrorStatus setDimexe(double v);
	virtual Nano::ErrorStatus setDimexo(double v);
	virtual Nano::ErrorStatus setDimfrac(int v);
	virtual Nano::ErrorStatus setDimgap(double v);
	virtual Nano::ErrorStatus setDimjogang(double v);
	virtual Nano::ErrorStatus setDimjust(int v);
	virtual Nano::ErrorStatus setDimldrblk(NcDbObjectId v);
	virtual Nano::ErrorStatus setDimlfac(double v);
	virtual Nano::ErrorStatus setDimlim(bool v);
	virtual Nano::ErrorStatus setDimltex1(NcDbObjectId v);
	virtual Nano::ErrorStatus setDimltex2(NcDbObjectId v);
	virtual Nano::ErrorStatus setDimltype(NcDbObjectId v);
	virtual Nano::ErrorStatus setDimlunit(int v);
	virtual Nano::ErrorStatus setDimlwd(NcDb::LineWeight v);
	virtual Nano::ErrorStatus setDimlwe(NcDb::LineWeight v);
	virtual Nano::ErrorStatus setDimmzf(double v);
	virtual Nano::ErrorStatus setDimmzs(const NCHAR* v);
	virtual Nano::ErrorStatus setDimpost(const NCHAR* v);
	virtual Nano::ErrorStatus setDimrnd(double v);
	virtual Nano::ErrorStatus setDimsah(bool v);
	virtual Nano::ErrorStatus setDimscale(double v);
	virtual Nano::ErrorStatus setDimsd1(bool v);
	virtual Nano::ErrorStatus setDimsd2(bool v);
	virtual Nano::ErrorStatus setDimse1(bool v);
	virtual Nano::ErrorStatus setDimse2(bool v);
	virtual Nano::ErrorStatus setDimsoxd(bool v);
	virtual Nano::ErrorStatus setDimtad(int v);
	virtual Nano::ErrorStatus setDimtdec(int v);
	virtual Nano::ErrorStatus setDimtfac(double v);
	virtual Nano::ErrorStatus setDimtfill(int v);
	virtual Nano::ErrorStatus setDimtfillclr(const NcCmColor& v);
	virtual Nano::ErrorStatus setDimtih(bool v);
	virtual Nano::ErrorStatus setDimtix(bool v);
	virtual Nano::ErrorStatus setDimtm(double v);
	virtual Nano::ErrorStatus setDimtmove(int v);
	virtual Nano::ErrorStatus setDimtofl(bool v);
	virtual Nano::ErrorStatus setDimtoh(bool v);
	virtual Nano::ErrorStatus setDimtol(bool v);
	virtual Nano::ErrorStatus setDimtolj(int v);
	virtual Nano::ErrorStatus setDimtp(double v);
	virtual Nano::ErrorStatus setDimtsz(double v);
	virtual Nano::ErrorStatus setDimtvp(double v);
	virtual Nano::ErrorStatus setDimtxsty(NcDbObjectId v);
	virtual Nano::ErrorStatus setDimtxt(double v);
	virtual Nano::ErrorStatus setDimtxtdirection(bool v);
	virtual Nano::ErrorStatus setDimtzin(int v);
	virtual Nano::ErrorStatus setDimupt(bool v);
	virtual Nano::ErrorStatus setDimzin(int v);

	virtual Nano::ErrorStatus setDimblk(const NCHAR* v);
	virtual Nano::ErrorStatus setDimblk1(const NCHAR* v);
	virtual Nano::ErrorStatus setDimblk2(const NCHAR* v);
	virtual Nano::ErrorStatus setDimldrblk(const NCHAR* v);

public:
	NcGePoint3d textPosition() const;
	Nano::ErrorStatus setTextPosition(const NcGePoint3d& point);

	NRX::Boolean isUsingDefaultTextPosition() const;
	Nano::ErrorStatus useSetTextPosition();

	Nano::ErrorStatus useDefaultTextPosition();

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

	double elevation() const;
	Nano::ErrorStatus setElevation(double value);

	NCHAR* dimensionText() const;

	Nano::ErrorStatus setDimensionText(const NCHAR* text);

	double textRotation() const;
	Nano::ErrorStatus setTextRotation(double angle);

	NcDbObjectId dimensionStyle() const;
	Nano::ErrorStatus setDimensionStyle(NcDbObjectId id);

	NcDbMText::AttachmentPoint textAttachment() const;
	Nano::ErrorStatus setTextAttachment(NcDbMText::AttachmentPoint eAtt);

	NcDb::LineSpacingStyle textLineSpacingStyle() const;

	Nano::ErrorStatus setTextLineSpacingStyle(NcDb::LineSpacingStyle style);

	double textLineSpacingFactor() const;

	Nano::ErrorStatus setTextLineSpacingFactor(double dFactor);

	Nano::ErrorStatus getDimstyleData(NcDbDimStyleTableRecord*& record) const;
	Nano::ErrorStatus setDimstyleData(NcDbDimStyleTableRecord* pNewData);
	Nano::ErrorStatus setDimstyleData(NcDbObjectId newDataId);

	double horizontalRotation() const;

	Nano::ErrorStatus setHorizontalRotation(double newVal);

	NcDbObjectId dimBlockId() const;
	Nano::ErrorStatus setDimBlockId(const NcDbObjectId& id);

	NcGePoint3d dimBlockPosition() const;
	Nano::ErrorStatus setDimBlockPosition(const NcGePoint3d& point);

	Nano::ErrorStatus recomputeDimBlock(bool forceUpdate = true);

	Nano::ErrorStatus generateLayout();

	Nano::ErrorStatus measurement(double& val);
	Nano::ErrorStatus formatMeasurement(NCHAR* out, double value, NCHAR* text);

	bool isDynamicDimension() const;
	Nano::ErrorStatus setDynamicDimension(bool newVal);

	NcDbObjectId dimLineLinetype() const;
	Nano::ErrorStatus setDimLineLinetype(const NcDbObjectId linetype);

	NcDbObjectId dimExt1Linetype() const;
	Nano::ErrorStatus setDimExt1Linetype(const NcDbObjectId linetype);

	NcDbObjectId dimExt2Linetype() const;
	Nano::ErrorStatus setDimExt2Linetype(const NcDbObjectId linetype);

	Nano::ErrorStatus removeTextField();
	Nano::ErrorStatus fieldToMText(NcDbMText* text);
	Nano::ErrorStatus fieldFromMText(NcDbMText* text);

	int dimfit() const;
	Nano::ErrorStatus setDimfit(int value);

	int dimunit() const;
	Nano::ErrorStatus setDimunit(int value);

	NcGeMatrix3d blockTransform() const;

	// Functions for internal use only
public:
	bool isHorizontalRefTextRotation() const;
	Nano::ErrorStatus setHorizontalRefTextRotation(bool angle);

	bool getArrowFirstIsFlipped() const;
	bool getArrowSecondIsFlipped() const;
	Nano::ErrorStatus setArrowFirstIsFlipped(bool bIsFlipped);
	Nano::ErrorStatus setArrowSecondIsFlipped(bool bIsFlipped);

	virtual void        erased(NcDbObject* dbObj, NRX::Boolean bErasing);
	Nano::ErrorStatus   getOsnapPointsAtSubentPath(NcDb::OsnapMode osnapMode,
	                                               const NcDbFullSubentPath& subentId,
	                                               const NcGePoint3d&  pickPoint,
	                                               const NcGePoint3d&  lastPoint,
	                                               const NcGeMatrix3d& viewXform,
	                                               NcGePoint3dArray&   snapPoints,
	                                               NcDbIntArray &   geomIds) const;
	bool inspection() const;
	int inspectionFrame() const;
	const NCHAR* inspectionLabel() const;
	const NCHAR* inspectionRate() const;
	bool  isConstraintDynamic(void) const;
	bool  isConstraintObject() const;
	bool  isConstraintObject(bool &hasExpression,
	                         bool &isReferenceConstraint) const;
	virtual void        objectClosed(const NcDbObjectId dbObj);
	Nano::ErrorStatus  setConstraintDynamic(bool bDynamic);
	Nano::ErrorStatus setInspection(bool val);
	Nano::ErrorStatus setInspectionFrame(int frame);
	Nano::ErrorStatus setInspectionLabel(const NCHAR* label);
	Nano::ErrorStatus setInspectionRate(const NCHAR* label);
	void  setShouldParticipateInOPM(bool bShouldParticipate);
	bool  shouldParticipateInOPM(void) const;

	NcDbObjectId        subDimensionStyle() const;
	Nano::ErrorStatus   subGetDimstyleData(NcDbDimStyleTableRecord*& pRecord) const;
	Nano::ErrorStatus   subSetDimensionStyle(NcDbObjectId dimStyleId);
	Nano::ErrorStatus   subSetDimstyleData(NcDbDimStyleTableRecord* pNewData);


public:
	OdDbDimension* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbRotatedDimension
class OdDbRotatedDimension;
class NRXDBGATE_EXPORT NcDbRotatedDimension : public NcDbDimension
{
	NCDB_DECLARE_MEMBERS(NcDbRotatedDimension);

public:
	typedef NcDbRotatedDimension  wrapper_class;
	typedef OdDbRotatedDimension  native_class;

public:
	NcDbRotatedDimension();
	NcDbRotatedDimension(double rotation, const NcGePoint3d& xpnt1, const NcGePoint3d& xpnt2, const NcGePoint3d& lpnt,
	                     const NCHAR* text = NULL, NcDbObjectId style = NcDbObjectId::kNull);
	NcDbRotatedDimension(OdRxObject* _object);

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	NcGePoint3d xLine1Point() const;
	Nano::ErrorStatus setXLine1Point(const NcGePoint3d& point);

	NcGePoint3d xLine2Point() const;
	Nano::ErrorStatus setXLine2Point(const NcGePoint3d& point);

	NcGePoint3d dimLinePoint() const;
	Nano::ErrorStatus setDimLinePoint(const NcGePoint3d& point);

	double oblique() const;
	Nano::ErrorStatus setOblique(double oblique);

	double rotation() const;
	Nano::ErrorStatus setRotation(double angle);

	bool jogSymbolOn() const;
	NcGePoint3d jogSymbolPosition() const;
	Nano::ErrorStatus setJogSymbolOn(bool value);
	Nano::ErrorStatus setJogSymbolPosition(const NcGePoint3d& pt);

public:
	OdDbRotatedDimension* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbAlignedDimension
class OdDbAlignedDimension;
class NRXDBGATE_EXPORT NcDbAlignedDimension : public NcDbDimension
{
	NCDB_DECLARE_MEMBERS(NcDbAlignedDimension);

public:
	typedef NcDbAlignedDimension  wrapper_class;
	typedef OdDbAlignedDimension  native_class;

public:
	NcDbAlignedDimension();
	NcDbAlignedDimension(const NcGePoint3d& xpnt1, const NcGePoint3d& xpnt2, const NcGePoint3d& lpnt,
	                     const NCHAR* text = NULL, NcDbObjectId style = NcDbObjectId::kNull);
	NcDbAlignedDimension(OdRxObject* _object);

	virtual double oblique() const; // +Overload

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	NcGePoint3d xLine1Point() const;
	Nano::ErrorStatus setXLine1Point(const NcGePoint3d& point);

	NcGePoint3d xLine2Point() const;
	Nano::ErrorStatus setXLine2Point(const NcGePoint3d& point);

	NcGePoint3d dimLinePoint() const;
	Nano::ErrorStatus setDimLinePoint(const NcGePoint3d& point);

	bool jogSymbolOn() const;
	NcGePoint3d jogSymbolPosition() const;
	Nano::ErrorStatus setJogSymbolOn(bool value);
	Nano::ErrorStatus setJogSymbolPosition(const NcGePoint3d& pt);
	Nano::ErrorStatus   setOblique(double);

public:
	OdDbAlignedDimension* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDb3PointAngularDimension
class OdDb3PointAngularDimension;
class NRXDBGATE_EXPORT NcDb3PointAngularDimension : public NcDbDimension
{
	NCDB_DECLARE_MEMBERS(NcDb3PointAngularDimension);

public:
	typedef NcDb3PointAngularDimension  wrapper_class;
	typedef OdDb3PointAngularDimension  native_class;

public:
	NcDb3PointAngularDimension();
	NcDb3PointAngularDimension(const NcGePoint3d& center, const NcGePoint3d& xpnt1, const NcGePoint3d& xpnt2,
	                           const NcGePoint3d& arcpnt, const NCHAR* text = NULL,
	                           NcDbObjectId style = NcDbObjectId::kNull);
	NcDb3PointAngularDimension(OdRxObject* _object);

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	NcGePoint3d arcPoint() const;
	Nano::ErrorStatus setArcPoint(const NcGePoint3d& point);

	NcGePoint3d xLine1Point() const;
	Nano::ErrorStatus setXLine1Point(const NcGePoint3d& point);

	NcGePoint3d xLine2Point() const;
	Nano::ErrorStatus setXLine2Point(const NcGePoint3d& point);

	NcGePoint3d centerPoint() const;
	Nano::ErrorStatus setCenterPoint(const NcGePoint3d& point);

	bool extArcOn() const;
	Nano::ErrorStatus setExtArcOn(bool value);

public:
	OdDb3PointAngularDimension* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDb2LineAngularDimension
class OdDb2LineAngularDimension;
class NRXDBGATE_EXPORT NcDb2LineAngularDimension : public NcDbDimension
{
	NCDB_DECLARE_MEMBERS(NcDb2LineAngularDimension);

public:
	typedef NcDb2LineAngularDimension  wrapper_class;
	typedef OdDb2LineAngularDimension  native_class;

public:
	NcDb2LineAngularDimension();
	NcDb2LineAngularDimension(const NcGePoint3d& xstart1, const NcGePoint3d& xend1, const NcGePoint3d& xstart2,
	                          const NcGePoint3d& xend2, const NcGePoint3d& arcpnt, const NCHAR* text = NULL,
	                          NcDbObjectId style = NcDbObjectId::kNull);

	NcDb2LineAngularDimension(OdRxObject* _object);

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	NcGePoint3d arcPoint() const;
	Nano::ErrorStatus setArcPoint(const NcGePoint3d& point);

	NcGePoint3d xLine1Start() const;
	Nano::ErrorStatus setXLine1Start(const NcGePoint3d& point);

	NcGePoint3d xLine1End() const;
	Nano::ErrorStatus setXLine1End(const NcGePoint3d& point);

	NcGePoint3d xLine2Start() const;
	Nano::ErrorStatus setXLine2Start(const NcGePoint3d& point);

	NcGePoint3d xLine2End() const;
	Nano::ErrorStatus setXLine2End(const NcGePoint3d& point);

	bool extArcOn() const;
	Nano::ErrorStatus setExtArcOn(bool value);

public:
	OdDb2LineAngularDimension* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbRadialDimension
class OdDbRadialDimension;
class NRXDBGATE_EXPORT NcDbRadialDimension : public NcDbDimension
{
	NCDB_DECLARE_MEMBERS(NcDbRadialDimension);

public:
	typedef NcDbRadialDimension  wrapper_class;
	typedef OdDbRadialDimension  native_class;

public:
	NcDbRadialDimension();
	NcDbRadialDimension(const NcGePoint3d& center, const NcGePoint3d& crdpnt, double ldrlen,
	                    const NCHAR* text = NULL, NcDbObjectId style = NcDbObjectId::kNull);

	NcDbRadialDimension(OdRxObject* _object);

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	double leaderLength() const;
	Nano::ErrorStatus setLeaderLength(double length);

	NcGePoint3d center() const;
	Nano::ErrorStatus setCenter(const NcGePoint3d& point);

	NcGePoint3d chordPoint() const;
	Nano::ErrorStatus setChordPoint(const NcGePoint3d& point);

	double extArcEndAngle() const;
	double extArcStartAngle() const;
	Nano::ErrorStatus setExtArcEndAngle(double newAngle);
	Nano::ErrorStatus setExtArcStartAngle(double newAngle);

public:
	OdDbRadialDimension* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDiametricDimension
class OdDbDiametricDimension;
class NRXDBGATE_EXPORT NcDbDiametricDimension : public NcDbDimension
{
	NCDB_DECLARE_MEMBERS(NcDbDiametricDimension);

public:
	typedef NcDbDiametricDimension  wrapper_class;
	typedef OdDbDiametricDimension  native_class;

public:
	NcDbDiametricDimension();
	NcDbDiametricDimension(const NcGePoint3d& crdpnt, const NcGePoint3d& crdpnt1, double ldrlen,
	                       const NCHAR* text = NULL, NcDbObjectId style = NcDbObjectId::kNull);

	NcDbDiametricDimension(OdRxObject* _object);

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	double leaderLength() const;
	Nano::ErrorStatus setLeaderLength(double length);

	NcGePoint3d chordPoint() const;
	Nano::ErrorStatus setChordPoint(const NcGePoint3d& point);

	NcGePoint3d farChordPoint() const;
	Nano::ErrorStatus setFarChordPoint(const NcGePoint3d& point);

	double extArcEndAngle() const;
	double extArcStartAngle() const;
	Nano::ErrorStatus setExtArcEndAngle(double newAngle);
	Nano::ErrorStatus setExtArcStartAngle(double newAngle);

public:
	OdDbDiametricDimension* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDiametricDimension
class OdDbArcDimension;
class NRXDBGATE_EXPORT NcDbArcDimension : public NcDbDimension
{
	NCDB_DECLARE_MEMBERS(NcDbArcDimension);

public:
	typedef NcDbArcDimension  wrapper_class;
	typedef OdDbArcDimension  native_class;

public:
	NcDbArcDimension();
	NcDbArcDimension(const NcGePoint3d& center, const NcGePoint3d& xpnt1, const NcGePoint3d& xpnt2,
	                 const NcGePoint3d& arcpnt, const NCHAR* text = NULL,
	                 NcDbObjectId style = NcDbObjectId::kNull);

	NcDbArcDimension(OdRxObject* _object);

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	NcGePoint3d arcPoint() const;
	Nano::ErrorStatus setArcPoint(const NcGePoint3d& point);

	NcGePoint3d xLine1Point() const;
	Nano::ErrorStatus setXLine1Point(const NcGePoint3d& point);

	NcGePoint3d xLine2Point() const;
	Nano::ErrorStatus setXLine2Point(const NcGePoint3d& point);

	NcGePoint3d centerPoint() const;
	Nano::ErrorStatus setCenterPoint(const NcGePoint3d& point);

	bool isPartial() const;
	Nano::ErrorStatus setIsPartial(const bool& partial);

	double arcStartParam() const;
	Nano::ErrorStatus setArcStartParam(const double& param);

	double arcEndParam() const;
	Nano::ErrorStatus setArcEndParam(const double& param);

	bool hasLeader() const;
	Nano::ErrorStatus setHasLeader(const bool& turn_on);

	NcGePoint3d leader1Point() const;
	Nano::ErrorStatus setLeader1Point(const NcGePoint3d& point);

	NcGePoint3d leader2Point() const;
	Nano::ErrorStatus setLeader2Point(const NcGePoint3d& point);

	int arcSymbolType() const;
	Nano::ErrorStatus setArcSymbolType(const int symbol);

public:
	OdDbArcDimension* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDiametricDimension
class OdDbRadialDimensionLarge;
class NRXDBGATE_EXPORT NcDbRadialDimensionLarge : public NcDbDimension
{
	NCDB_DECLARE_MEMBERS(NcDbRadialDimensionLarge);

public:
	typedef NcDbRadialDimensionLarge  wrapper_class;
	typedef OdDbRadialDimensionLarge  native_class;

public:
	NcDbRadialDimensionLarge();
	NcDbRadialDimensionLarge(const NcGePoint3d& center, const NcGePoint3d& crdpnt, const NcGePoint3d& override_center,
	                         const NcGePoint3d& jog_point, double jog_angle, const NCHAR* text = NULL,
	                         NcDbObjectId style = NcDbObjectId::kNull);

	NcDbRadialDimensionLarge(OdRxObject* _object);

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

public:
	NcGePoint3d center() const;
	Nano::ErrorStatus setCenter(const NcGePoint3d& point);

	NcGePoint3d chordPoint() const;
	Nano::ErrorStatus setChordPoint(const NcGePoint3d& point);

	NcGePoint3d overrideCenter() const;
	Nano::ErrorStatus setOverrideCenter(const NcGePoint3d& point);

	NcGePoint3d jogPoint() const;
	Nano::ErrorStatus setJogPoint(const NcGePoint3d& point);

	double jogAngle() const;
	Nano::ErrorStatus setJogAngle(double angle);

	Nano::ErrorStatus setOverrideCenterPP(const NcGePoint3d& point);
	Nano::ErrorStatus setJogPointPP(const NcGePoint3d& point);
	Nano::ErrorStatus setTextPositionPP(const NcGePoint3d& point);

	double extArcEndAngle() const;
	double extArcStartAngle() const;
	Nano::ErrorStatus setExtArcEndAngle(double newAngle);
	Nano::ErrorStatus setExtArcStartAngle(double newAngle);

public:
	OdDbRadialDimensionLarge* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbOrdinateDimension
class OdDbOrdinateDimension;
class NRXDBGATE_EXPORT NcDbOrdinateDimension: public NcDbDimension
{
  NCDB_DECLARE_MEMBERS(NcDbOrdinateDimension);

public:
  typedef NcDbOrdinateDimension  wrapper_class;
  typedef OdDbOrdinateDimension  native_class;

public:
  NcDbOrdinateDimension();
  NcDbOrdinateDimension(NRX::Boolean useXAxis, const NcGePoint3d& definingPoint,
                        const NcGePoint3d& leaderEndPoint, const NCHAR* dimText = NULL,
                        NcDbObjectId dimStyle  = NcDbObjectId::kNull);
  NcDbOrdinateDimension(OdRxObject* _object);

  // NcDbObject Protocol
public:
  virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
  virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
  virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
  virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

  virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

  NRX::Boolean      isUsingXAxis() const;
  NRX::Boolean      isUsingYAxis() const;
  Nano::ErrorStatus   useXAxis();
  Nano::ErrorStatus   useYAxis();
  NcGePoint3d         origin() const;
  Nano::ErrorStatus   setOrigin(const NcGePoint3d&);
  NcGePoint3d         definingPoint() const;
  Nano::ErrorStatus   setDefiningPoint(const NcGePoint3d&);
  NcGePoint3d         leaderEndPoint() const;
  Nano::ErrorStatus   setLeaderEndPoint(const NcGePoint3d&);

public:
  OdDbOrdinateDimension* native() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDimData
class NRXDBGATE_EXPORT NcDbDimData
{
public:
	enum DimDataFlags
	{
		kDimEditable          = 0x1,
		kDimInvisible         = 0x2,
		kDimFocal             = 0x4,
		kDimHideIfValueIsZero = 0x8,
		kDimEmptyData         = 0x10,
		kDimResultantLength   = 0x20,
		kDimDeltaLength       = 0x40,
		kDimResultantAngle    = 0x80,
		kDimDeltaAngle        = 0x100,
		kDimRadius            = 0x200,
		kDimCustomValue       = 0x400,
		kDimConstrained       = 0x800,
		kDimCustomString      = 0x1000
	};

public:
	NcDbDimData();
	NcDbDimData(NcDbDimension* pDim, odtDimDataSetValueFuncPtr setDimFunc = NULL, unsigned int bitFlags = 0,
	            void* appData = NULL, odtDimDataSetCustomStringFuncPtr setCustomStringFunc = NULL);
	NcDbDimData(const NcDbDimData&);

	~NcDbDimData();

public:
	NcDbDimData& operator = (const NcDbDimData&);
	NcDbDimension* dimension() const;
	Nano::ErrorStatus setDimension(NcDbDimension* pDim);
	NcDbObjectId ownerId() const;
	Nano::ErrorStatus setOwnerId(const NcDbObjectId& objId);
	unsigned int bitFlags() const;
	Nano::ErrorStatus setBitFlags(unsigned int flags);
	bool isDimFocal() const;
	Nano::ErrorStatus setDimFocal(bool focal);
	bool isDimEditable() const;
	Nano::ErrorStatus setDimEditable(bool editable);
	bool isDimInvisible() const;
	Nano::ErrorStatus setDimInvisible(bool invisible);
	bool isDimHideIfValueIsZero() const;
	Nano::ErrorStatus setDimHideIfValueIsZero(bool hide);
	void* appData() const;
	Nano::ErrorStatus setAppData(void* appData);
	odtDimDataSetValueFuncPtr dimValueFunc() const;
	Nano::ErrorStatus setDimValueFunc(odtDimDataSetValueFuncPtr funcPtr);
	odtDimDataSetCustomStringFuncPtr customStringFunc() const;
	Nano::ErrorStatus setCustomStringFunc(odtDimDataSetCustomStringFuncPtr funcPtr);
	bool isDimResultantLength() const;
	Nano::ErrorStatus setDimResultantLength(bool bValue);
	bool isDimDeltaLength() const;
	Nano::ErrorStatus setDimDeltaLength(bool bValue);
	bool isDimResultantAngle() const;
	Nano::ErrorStatus setDimResultantAngle(bool bValue);
	bool isDimDeltaAngle() const;
	Nano::ErrorStatus setDimDeltaAngle(bool bValue);
	bool isDimRadius() const;
	Nano::ErrorStatus setDimRadius(bool bValue);
	bool isCustomDimValue() const;
	Nano::ErrorStatus setCustomDimValue(bool custom);
	bool isConstrained() const;
	Nano::ErrorStatus setConstrain(bool bValue);
	bool isCustomString() const;
	Nano::ErrorStatus setCustomString(bool bValue);

private:
	NcDbDimension*                   mpDim;
	NcDbObjectId                     mOwnerId;
	unsigned int                     mBitFlags;
	void*                            mpAppData;
	odtDimDataSetValueFuncPtr        mpSetDimValueFunc;
	odtDimDataSetCustomStringFuncPtr mpSetCustomStringFunc;
};

NRXDBGATE_EXPORT NcDbObjectId ncdbGetDynDimStyleId(NcDbDatabase* database = NULL);

//////////////////////////////////////////////////////////////////////////
// NcDbPointRef
class OdDbPointRef;
typedef NcArray<NcDbHandle, NcArrayObjectCopyReallocator<NcDbHandle> > NcDbHandleArrayPtRef;

class NRXDBGATE_EXPORT NcDbPointRef : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbPointRef);

	NcDbPointRef();
	NcDbPointRef(OdRxObject* _object);

	typedef NcDbPointRef  wrapper_class;
	typedef OdDbPointRef  native_class;

	enum OsnapType {
		kOsnapNone         = 0,
		kOsnapEnd          = 1,
		kOsnapMid          = 2,
		kOsnapCen          = 3,
		kOsnapNode         = 4,
		kOsnapQuad         = 5,
		kOsnapInt          = 6,
		kOsnapIns          = 7,
		kOsnapPerp         = 8,
		kOsnapTan          = 9,
		kOsnapNear         = 10,
		kOsnapApint        = 11,
		kOsnapStart        = 13
	};

	virtual NcDbPointRef& operator=(const NcDbPointRef& src);
	virtual Nano::ErrorStatus evalPoint(NcGePoint3d& pnt_wcs);
	virtual Nano::ErrorStatus getEntities(NcDbFullSubentPathArray& ents, bool getLastPtRef = true) const;
	virtual bool isGeomErased() const;
	virtual bool isXrefObj(NcDbObjectIdArray& ids1, NcDbObjectIdArray& ids2, bool isMainObj = true) const;
	virtual Nano::ErrorStatus updateXrefSubentPath();

	virtual Nano::ErrorStatus updateSubentPath(NcDbIdMapping& idMap);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer, NcDbDatabase* pDb) const;
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer, NcDbDatabase* pDb);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer, NcDbDatabase* pDb) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer, NcDbDatabase* pDb);

	virtual Nano::ErrorStatus subErase(NRX::Boolean erasing);
	virtual Nano::ErrorStatus wblockClone(NcRxObject* pOwnerObject, NcDbObject*& pClonedObject,
	                                      NcDbIdMapping& idMap, NRX::Boolean isPrimary = NRX::kTrue) const;
	virtual Nano::ErrorStatus deepClone(NcRxObject* pOwnerObject, NcDbObject*& pClonedObject,
	                                    NcDbIdMapping& idMap, NRX::Boolean isPrimary = NRX::kTrue) const;
	virtual void updateDueToMirror(bool inMirror = false);

	static Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer, NcDbDatabase* pDb, NcDbPointRef*& pPointRef);
	static Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer, NcDbDatabase* pDb, const NcDbPointRef* pPointRef);
	static Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer, NcDbDatabase* pDb, NcDbPointRef*& pPointRef);
	static Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer, NcDbDatabase* pDb, const NcDbPointRef* pPointRef);
	static NcDbEntity* subentPtr(const NcDbFullSubentPath& objPath, bool& isCloned, bool& reverseArc, bool& isStandAloneArc);
	static bool calcTransform(const NcDbObjectIdArray& ids, NcGeMatrix3d& A_Ecs2Wcs);
	static NcGeMatrix3d wcsToDcsMatrix(const NcDbViewport* pVPort);
	static NcGeMatrix3d mswcsToPswcs(const NcDbViewport* pVPort);

public:
	OdDbPointRef* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbOsnapPointRef
class OdDbOsnapPointRef;
class NRXDBGATE_EXPORT NcDbOsnapPointRef : public NcDbPointRef
{
public:
	NCRX_DECLARE_MEMBERS(NcDbOsnapPointRef);

	typedef NcDbOsnapPointRef  wrapper_class;
	typedef OdDbOsnapPointRef  native_class;

	NcDbOsnapPointRef();
	NcDbOsnapPointRef(const NcGePoint3d& refPt);
	NcDbOsnapPointRef(NcDbPointRef::OsnapType osnapType, const NcDbFullSubentPath *objPath,
	                  const NcDbFullSubentPath *intObjPath = NULL, const NcGePoint3d *refPt = NULL,
	                  NcDbPointRef* lastPtRef = NULL);
	NcDbOsnapPointRef(const NcDbOsnapPointRef& src);
	NcDbOsnapPointRef(OdRxObject* object);
	virtual ~NcDbOsnapPointRef();

	virtual NcDbPointRef& operator= (const NcDbPointRef& src);
	NcDbOsnapPointRef& operator= (const NcDbOsnapPointRef& src);

	NcDbPointRef::OsnapType osnapType() const;
	Nano::ErrorStatus setOsnapType(NcDbPointRef::OsnapType osnType);

	Nano::ErrorStatus getIdPath(NcDbFullSubentPath& idPath) const;
	Nano::ErrorStatus setIdPath(const NcDbFullSubentPath& idPath);

	Nano::ErrorStatus getIntIdPath(NcDbFullSubentPath& intIdPath) const;
	Nano::ErrorStatus setIntIdPath(const NcDbFullSubentPath& intIdPath);

	Nano::ErrorStatus setLastPointRef(NcDbPointRef *ptRef);
	NcDbPointRef* lastPointRef() const;

	Nano::ErrorStatus setPoint(const NcGePoint3d& pt);
	NcGePoint3d point() const;

	double nearPointParam() const;
	Nano::ErrorStatus setNearPointParam(double newVal);

	virtual bool isGeomErased() const;
	virtual bool isXrefObj(NcDbObjectIdArray& ids1, NcDbObjectIdArray& ids2,
	                       bool isMainObj = true) const;
	virtual Nano::ErrorStatus updateXrefSubentPath();
	virtual Nano::ErrorStatus updateSubentPath(NcDbIdMapping& idMap);
	virtual Nano::ErrorStatus evalPoint(NcGePoint3d &pt);

	virtual Nano::ErrorStatus getEntities(NcDbFullSubentPathArray& ents,
	                                      bool getLastPtRef = true) const;
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* pSrc);
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer, NcDbDatabase* pDb);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer, NcDbDatabase* pDb) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer, NcDbDatabase *pDb);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer, NcDbDatabase *pDb) const;
	virtual void updateDueToMirror(bool inMirror = false);

	Nano::ErrorStatus getXrefHandles(NcDbHandleArrayPtRef& xrefHandles) const;
	Nano::ErrorStatus setXrefHandles(const NcDbHandleArrayPtRef& xrefHandles);

	Nano::ErrorStatus getXrefIntHandles(NcDbHandleArrayPtRef& xrefHandles) const;
	Nano::ErrorStatus setXrefIntHandles(const NcDbHandleArrayPtRef& xrefHandles);


protected:
	NcGePoint3d nearPoint();
	double findNearPointParam(const NcGePoint3d& pt) const;
	bool getEllipseParams(double& sP, double& eP) const;
	bool isTransSpatial(bool isMainObj = true) const;

	Nano::ErrorStatus evalPointGuts(NcDbPointRef::OsnapType ospType, const NcGePoint3d& pickPt,
	                                const NcGePoint3d& lastPt, NcGePoint3d &pt);
	Nano::ErrorStatus getIntPoints(const NcDbEntity* pEnt, const NcDbEntity* pIntEnt,
	                               NcDb::Intersect intType, NcGePoint3dArray& intPts,
	                               int gsMarker1 = 0, int gsMarker2 = 0) const;
	Nano::ErrorStatus updateSubentPathGuts(NcDbFullSubentPath& path, NcDbIdMapping& idMap);

public:
	OdDbOsnapPointRef* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDimAssoc
class OdDbDimAssoc;
class NRXDBGATE_EXPORT NcDbDimAssoc : public NcDbObject
{
public:
	NCDB_DECLARE_MEMBERS(NcDbDimAssoc);

	typedef NcDbDimAssoc  wrapper_class;
	typedef OdDbDimAssoc  native_class;

	enum { kMaxPointRefs = 4 };

	enum PointType {
		kXline1Point      = 0,
		kXline2Point      = 1,
		kOriginPoint      = 0,
		kDefiningPoint    = 1,
		kXline1Start      = 0,
		kXline1End        = 1,
		kXline2Start      = 2,
		kXline2End        = 3,
		kVertexPoint      = 2,
		kChordPoint       = 0,
		kCenterPoint      = 1,
		kFarChordPoint    = 1,
		kOverrideCenterPoint   = 2,
		kAngLineStart     = 2,
		kJogPoint         = 3,
		kAngLineEnd       = 3,
		kLeaderPoint      = 0
	};

	enum AssocFlags {
		kFirstPointRef     = 1,
		kSecondPointRef    = 2,
		kThirdPointRef     = 4,
		kFourthPointRef    = 8
	};

	enum RotatedDimType {
		kUnknown       = 0,
		kParallel      = 1,
		kPerpendicular = 2
	};

	NcDbDimAssoc();
	NcDbDimAssoc(OdRxObject* _object);
	virtual ~NcDbDimAssoc();

	NcDbObjectId dimObjId() const;
	Nano::ErrorStatus setDimObjId(const NcDbObjectId& dimId);
	Nano::ErrorStatus setAssocFlag(int ptType, bool value);
	void setAssocFlag(int assocFlg);
	bool assocFlag(int ptType) const;
	int assocFlag(void);
	Nano::ErrorStatus setPointRef(int ptType, NcDbPointRef* ptRef);
	const NcDbPointRef *pointRef(int ptType) const;
	Nano::ErrorStatus setRotatedDimType(RotatedDimType dimType);
	RotatedDimType rotatedDimType() const;
	Nano::ErrorStatus addToPointRefReactor();
	Nano::ErrorStatus addToDimensionReactor(bool isAdd = true);
	Nano::ErrorStatus removePointRef(int ptType);
	Nano::ErrorStatus updateDimension(bool update = true, bool skipReactors = false);
	Nano::ErrorStatus removeAssociativity(bool force = true);
	bool isTransSpatial() const;
	Nano::ErrorStatus setTransSpatial(bool value);
	Nano::ErrorStatus startCmdWatcher();

	Nano::ErrorStatus startOopsWatcher(bool bAddAll = true);
	void removeOopsWatcher(void);
	Nano::ErrorStatus restoreAssocFromOopsWatcher(void);
	bool hasOopsWatcher(void) const;
	Nano::ErrorStatus post(NcDbObjectId dimId,  NcDbObjectId& dimAssocId,  bool isActive = true);
	Nano::ErrorStatus getDimAssocGeomIds(NcDbObjectIdArray& geomIds) const;
	bool isAllGeomErased() const;

	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler*);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler*) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler*);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler*) const;
	virtual void modifiedGraphics(const NcDbEntity* pObj);

	virtual Nano::ErrorStatus swapReferences (const NcDbIdMapping& idMap);

	Nano::ErrorStatus updateFillet(const NcDbObjectIdArray& ids);
	Nano::ErrorStatus updateAssociativity(const NcDbObjectIdArray& ids);
	Nano::ErrorStatus updateXrefSubentPath();
	Nano::ErrorStatus updateSubentPath(NcDbIdMapping& idMap);
	void updateDueToMirror(bool wasInMirror);

protected:
	Nano::ErrorStatus setPointRefReactor(int ptType, bool isAdd = true);
	Nano::ErrorStatus removeDimExtDict(void);
	bool isPointBetweenRays(const NcGePoint3d& vertex, const NcGePoint3d& firstPt, const NcGePoint3d& secondPt,
	                        const NcGePoint3d& angPt, const NcGeVector3d& normal);
	Nano::ErrorStatus updateDimension(NcDbRotatedDimension* pRotDim, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimension(NcDbAlignedDimension* pAlnDim, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimension(NcDbRadialDimension* pRadDim, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimension(NcDbRadialDimensionLarge* pRadDimLarge, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimension(NcDbDiametricDimension* pDiaDim, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimension(NcDb2LineAngularDimension* pA2Dim, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimension(NcDb3PointAngularDimension* pA3Dim, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimension(NcDbOrdinateDimension* pOrdDim, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimension(NcDbArcDimension* pArcDim, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimension(NcDbLeader* pLeader, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimension(NcDbMLeader* pMLeader, NcGePoint3d* pNewPts,
	                                  bool bUpdate = true);
	Nano::ErrorStatus updateDimLineAndTextLocation(NcDbRotatedDimension* pAlnDim,
	                                               const NcGePoint3d* kpOldPts, const NcGePoint3d* kpNewPts);
	Nano::ErrorStatus updateDimLineAndTextLocation(NcDbAlignedDimension* pAlnDim,
	                                               const NcGePoint3d* pOldPts, const NcGePoint3d* pNewPts);
	Nano::ErrorStatus updateDimLineAndTextLocation(NcDb2LineAngularDimension* pA2Dim,
	                                               const NcGePoint3d* pOldPts, const NcGePoint3d* pNewPts);
	Nano::ErrorStatus updateDimLineAndTextLocation(NcDb3PointAngularDimension* pA3Dim,
	                                               const NcGePoint3d* pOldPts, const NcGePoint3d* pNewPts);
	Nano::ErrorStatus updateDimLineAndTextLocation(NcDbArcDimension* pArcDim,
	                                               const NcGePoint3d* kpOldPts, const NcGePoint3d* kpNewPts);
	Nano::ErrorStatus calculate3PointAngDimArcLocation(const NcGePoint3d* kpOldPts,
	                                                   const NcGePoint3d& kOldArcPt, const NcGePoint3d& kOldTextPt,
	                                                   const NcGePoint3d* kpNewPts, const NcGeVector3d& normal,
	                                                   NcGePoint3d& newArcPt, NcGePoint3d& newTextPt);
	Nano::ErrorStatus calculate2LineAngDimArcLocation(const NcGePoint3d* kpOldPts,
	                                                  const NcGePoint3d& kOldArcPt, const NcGePoint3d& kOldTextPt,
	                                                  const NcGePoint3d* kpNewPts, const NcGeVector3d& kNormal,
	                                                  NcGePoint3d& newArcPt, NcGePoint3d& newTextPt);

public:
	OdDbDimAssoc* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbCurve
class OdDbCurve;
class NRXDBGATE_EXPORT NcDbCurve : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbCurve);

public:
	typedef OdDbCurve  native_class;

protected:
	NcDbCurve();

public:
	NcDbCurve(OdRxObject* _object);

	virtual NRX::Boolean isClosed() const;
	virtual NRX::Boolean isPeriodic() const;

	virtual Nano::ErrorStatus getStartParam(double& param) const;
	virtual Nano::ErrorStatus getEndParam(double& param) const;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const;

	virtual Nano::ErrorStatus getPointAtParam(double param, NcGePoint3d& point) const;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& dist) const;
	virtual Nano::ErrorStatus getParamAtDist(double dist, double& param) const;
	virtual Nano::ErrorStatus getDistAtPoint(const NcGePoint3d& point, double& dist) const;
	virtual Nano::ErrorStatus getPointAtDist(double dist, NcGePoint3d& point) const;

	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const;

	virtual Nano::ErrorStatus getClosestPointTo(const NcGePoint3d& given, NcGePoint3d& pointOnCurve,
	                                            NRX::Boolean extend = NRX::kFalse) const;
	virtual Nano::ErrorStatus getClosestPointTo(const NcGePoint3d& given, const NcGeVector3d& direction,
	                                            NcGePoint3d& pointOnCurve,
	                                            NRX::Boolean extend = NRX::kFalse) const;

	virtual Nano::ErrorStatus getOrthoProjectedCurve(const NcGePlane& plane, NcDbCurve*& curve) const;

	virtual Nano::ErrorStatus getProjectedCurve(const NcGePlane& plane, const NcGeVector3d& direction,
	                                            NcDbCurve*& curve) const;

	virtual Nano::ErrorStatus getOffsetCurves(double distance, NcDbVoidPtrArray& curves) const;

	virtual Nano::ErrorStatus getOffsetCurvesGivenPlaneNormal(const NcGeVector3d& normal, double distance,
	                                                          NcDbVoidPtrArray& segments) const;

	virtual Nano::ErrorStatus getSpline(NcDbSpline*& spline) const;

	virtual Nano::ErrorStatus getSplitCurves(const NcGeDoubleArray& params, NcDbVoidPtrArray& segments) const;
	virtual Nano::ErrorStatus getSplitCurves(const NcGePoint3dArray& points, NcDbVoidPtrArray& segments) const;

	virtual Nano::ErrorStatus extend(double newParam);
	virtual Nano::ErrorStatus extend(NRX::Boolean extend, const NcGePoint3d& to);

	virtual Nano::ErrorStatus getArea(double& area) const;

	virtual Nano::ErrorStatus reverseCurve();

	virtual Nano::ErrorStatus getNcGeCurve(NcGeCurve3d*& pGeCurve, const NcGeTol& tol = NcGeContext::gTol) const;

	static Nano::ErrorStatus createFromNcGeCurve(const NcGeCurve3d& geCurve, NcDbCurve*& pDbCurve,
	                                             NcGeVector3d * normal = NULL,
	                                             const NcGeTol& tol = NcGeContext::gTol);
	virtual Nano::ErrorStatus setFromNcGeCurve(const NcGeCurve3d& geCurve, NcGeVector3d *normal = NULL,
	                                           const NcGeTol& tol = NcGeContext::gTol);

public:
	OdDbCurve* native() const;

protected:
	virtual OdRxObject* GetNativeObject() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbVertex
class OdDbVertex;
class NRXDBGATE_EXPORT NcDbVertex : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbVertex);

public:
	typedef NcDbVertex  wrapper_class;
	typedef OdDbVertex  native_class;

public:
	NcDbVertex();

	NcDbVertex(OdRxObject* _object);

	virtual ~NcDbVertex();

	// NcDbObject
public:
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	// NcDbEntity
public:
	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const;

public:
	OdDbVertex* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDb3dPolylineVertex
class OdDb3dPolylineVertex;
class NRXDBGATE_EXPORT NcDb3dPolylineVertex : public NcDbVertex
{
	NCDB_DECLARE_MEMBERS(NcDb3dPolylineVertex);

public:
	NcDb3dPolylineVertex();
	NcDb3dPolylineVertex(const NcGePoint3d& point);

	NcDb3dPolylineVertex(OdRxObject* _object);

public:
	typedef NcDb3dPolylineVertex  wrapper_class;
	typedef OdDb3dPolylineVertex  native_class;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	// NcDbEntity
public:
	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const;
	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

public:
	NcDb::Vertex3dType vertexType() const;

	NcGePoint3d position() const;
	Nano::ErrorStatus setPosition(const NcGePoint3d& position);

public:
	OdDb3dPolylineVertex* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbPolygonMeshVertex
class OdDbPolygonMeshVertex;
class NRXDBGATE_EXPORT NcDbPolygonMeshVertex : public NcDbVertex
{
	NCDB_DECLARE_MEMBERS(NcDbPolygonMeshVertex);

public:
	NcDbPolygonMeshVertex();
	NcDbPolygonMeshVertex(const NcGePoint3d& position);

	NcDbPolygonMeshVertex(OdRxObject* _object);

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) ; //+Overload
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload
	virtual Nano::ErrorStatus subErase(NRX::Boolean erase) ; //+Overload2

public:
	typedef NcDbPolygonMeshVertex  wrapper_class;
	typedef OdDbPolygonMeshVertex  native_class;

public:
	NcDb::Vertex3dType vertexType() const;
	NcGePoint3d position() const;
	Nano::ErrorStatus setPosition(const NcGePoint3d& pos);

public:
	OdDbPolygonMeshVertex* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbPolygonMesh
class OdDbPolygonMesh;
class NRXDBGATE_EXPORT NcDbPolygonMesh : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbPolygonMesh);

public:
	NcDbPolygonMesh();
	NcDbPolygonMesh(NcDb::PolyMeshType type, NRX::Int16 mSize, NRX::Int16 nSize,
	                const NcGePoint3dArray& vertices, NRX::Boolean mClosed = NRX::kTrue,
	                NRX::Boolean nClosed = NRX::kTrue);

	NcDbPolygonMesh(OdRxObject* _object);

	virtual ~NcDbPolygonMesh();

	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) ; //+Overload
	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) ; //+Overload
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) ; //+Overload
	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload
	virtual NRX::Boolean isPlanar() const; //+Overload2
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const; //+Overload2

public:
	typedef NcDbPolygonMesh  wrapper_class;
	typedef OdDbPolygonMesh  native_class;

public:
	NcDb::PolyMeshType polyMeshType() const;
	Nano::ErrorStatus setPolyMeshType(NcDb::PolyMeshType polyMeshType);
	Nano::ErrorStatus convertToPolyMeshType(NcDb::PolyMeshType newVal);
	NRX::Int16 mSize() const;
	Nano::ErrorStatus setMSize(NRX::Int16 mSize);
	NRX::Int16 nSize() const;
	Nano::ErrorStatus setNSize(NRX::Int16 nSize);
	NRX::Boolean isMClosed() const;
	Nano::ErrorStatus makeMClosed();
	Nano::ErrorStatus makeMOpen();
	NRX::Boolean isNClosed() const;
	Nano::ErrorStatus makeNClosed();
	Nano::ErrorStatus makeNOpen();
	NRX::Int16 mSurfaceDensity() const;
	Nano::ErrorStatus setMSurfaceDensity(NRX::Int16 mSurfaceDensity);
	NRX::Int16 nSurfaceDensity() const;
	Nano::ErrorStatus setNSurfaceDensity(NRX::Int16 nSurfaceDensity);
	Nano::ErrorStatus straighten();
	Nano::ErrorStatus surfaceFit();
	Nano::ErrorStatus surfaceFit(NcDb::PolyMeshType surfType, NRX::Int16 surfu, NRX::Int16 surfv);
	Nano::ErrorStatus appendVertex(NcDbPolygonMeshVertex* pVertex);
	Nano::ErrorStatus appendVertex(NcDbObjectId& id, NcDbPolygonMeshVertex* pVertex);

	Nano::ErrorStatus openVertex(NcDbPolygonMeshVertex*& pVertex, NcDbObjectId vertId, NcDb::OpenMode eMode,
	                             bool openErasedOne = false);

	Nano::ErrorStatus openSequenceEnd(NcDbSequenceEnd*& pSequenceEnd, NcDb::OpenMode mode);

	NcDbObjectIterator* vertexIterator() const;

	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source);

protected:
	NcArray< NcDbPolygonMeshVertex* > m_arrVertex;

public:
	OdDbPolygonMesh* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbPolyFaceMeshVertex
class OdDbPolyFaceMeshVertex;
class NRXDBGATE_EXPORT NcDbPolyFaceMeshVertex : public NcDbVertex
{
	NCDB_DECLARE_MEMBERS(NcDbPolyFaceMeshVertex);

public:
	NcDbPolyFaceMeshVertex();
	NcDbPolyFaceMeshVertex(const NcGePoint3d& position);

	NcDbPolyFaceMeshVertex(OdRxObject* _object);

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) ; //+Overload
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload
	virtual Nano::ErrorStatus subErase(NRX::Boolean erase) ; //+Overload2

public:
	typedef NcDbPolyFaceMeshVertex  wrapper_class;
	typedef OdDbPolyFaceMeshVertex  native_class;

public:
	NcGePoint3d position() const;
	Nano::ErrorStatus setPosition(const NcGePoint3d& pos);

public:
	OdDbPolyFaceMeshVertex* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbPolyFaceMesh
class OdDbPolyFaceMesh;
class NRXDBGATE_EXPORT NcDbPolyFaceMesh : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbPolyFaceMesh);

public:
	NcDbPolyFaceMesh();
	NcDbPolyFaceMesh(OdRxObject* _object);

	virtual ~NcDbPolyFaceMesh();

	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) ; //+Overload
	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) ; //+Overload
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) ; //+Overload
	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload
	virtual NRX::Boolean isPlanar() const; //+Overload2
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const; //+Overload2

public:
	typedef NcDbPolyFaceMesh  wrapper_class;
	typedef OdDbPolyFaceMesh  native_class;

public:
	NRX::Int16 numVertices() const;
	NRX::Int16 numFaces() const;
	Nano::ErrorStatus appendVertex(NcDbPolyFaceMeshVertex* pVertex);
	Nano::ErrorStatus appendVertex(NcDbObjectId& id, NcDbPolyFaceMeshVertex* pVertex);
	Nano::ErrorStatus appendFaceRecord(NcDbFaceRecord* rec);
	Nano::ErrorStatus appendFaceRecord(NcDbObjectId& id, NcDbFaceRecord* rec);

	Nano::ErrorStatus openVertex(NcDbVertex*& pVertex, NcDbObjectId subObjId, NcDb::OpenMode mode,
	                             bool openErasedOne = false);

	Nano::ErrorStatus openSequenceEnd(NcDbSequenceEnd*& pSequenceEnd, NcDb::OpenMode mode);

	NcDbObjectIterator* vertexIterator() const;

	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source);
	Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const; 

protected:
	NcArray< NcDbVertex* > m_arrVertex;

public:
	OdDbPolyFaceMesh* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDb2dVertex
class OdDb2dVertex;
class NRXDBGATE_EXPORT NcDb2dVertex : public NcDbVertex
{
	NCDB_DECLARE_MEMBERS(NcDb2dVertex);

public:
	NcDb2dVertex();
	NcDb2dVertex(const NcGePoint3d& position, double bulge = 0, double start_width = 0, double end_width = 0,
	             double tangent = 0, NRX::Int32 vertexIdentifier = 0);

	NcDb2dVertex(OdRxObject* _object);

	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload

public:
	typedef NcDb2dVertex  wrapper_class;
	typedef OdDb2dVertex  native_class;

public:
	Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform);
	NcDb::Vertex2dType vertexType() const;

	NcGePoint3d position() const;
	Nano::ErrorStatus setPosition(const NcGePoint3d& position);

	double startWidth() const;
	Nano::ErrorStatus setStartWidth(double width);

	double endWidth() const;
	Nano::ErrorStatus setEndWidth(double width);

	double bulge() const;
	Nano::ErrorStatus setBulge(double bulge);

	NRX::Boolean isTangentUsed() const;
	Nano::ErrorStatus useTangent();
	Nano::ErrorStatus ignoreTangent();

	double tangent() const;
	Nano::ErrorStatus setTangent(double tangent);

	Nano::ErrorStatus  setVertexIdentifier(NRX::Int32 suggestedValue);
	int vertexIdentifier() const;

public:
	OdDb2dVertex* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSequenceEnd
class OdDbSequenceEnd;
class NRXDBGATE_EXPORT NcDbSequenceEnd : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbSequenceEnd);

public:
	NcDbSequenceEnd();

	NcDbSequenceEnd(OdRxObject* _object);

	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload
	virtual Nano::ErrorStatus subErase(NRX::Boolean erase) ; //+Overload2

public:
	typedef NcDbSequenceEnd  wrapper_class;
	typedef OdDbSequenceEnd  native_class;

public:
	OdDbSequenceEnd* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbCircle
class OdDbCircle;
class NRXDBGATE_EXPORT NcDbCircle : public NcDbCurve
{
	NCDB_DECLARE_MEMBERS(NcDbCircle);

public:
	NcDbCircle();
	NcDbCircle(const NcGePoint3d& center, const NcGeVector3d& normal, double radius);

	NcDbCircle(OdRxObject* _object);

	virtual Nano::ErrorStatus getParamAtDist(double dist, double& param) const; //+Overload2

public:
	typedef NcDbCircle  wrapper_class;
	typedef OdDbCircle  native_class;

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	// NcDEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane&, NcDb::Planarity&) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;

	// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getPointAtDist(double distance, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getArea(double& area) const override;

public:
	NcGePoint3d center() const;
	Nano::ErrorStatus setCenter(const NcGePoint3d& center);

	double radius() const;
	Nano::ErrorStatus setRadius(double radius);

	double thickness() const;
	Nano::ErrorStatus setThickness(double thickness);

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

public:
	OdDbCircle* native() const;

protected:
	virtual OdRxObject* GetNativeObject() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDb3dPolyline
class OdDb3dPolyline;
class NRXDBGATE_EXPORT NcDb3dPolyline : public NcDbCurve
{
	NCDB_DECLARE_MEMBERS(NcDb3dPolyline);

public:
	NcDb3dPolyline();
	NcDb3dPolyline(NcDb::Poly3dType type, NcGePoint3dArray& vertices, NRX::Boolean closed = NRX::kFalse);

	NcDb3dPolyline(OdRxObject* _object);

	virtual ~NcDb3dPolyline();

	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload

public:
	typedef NcDb3dPolyline  wrapper_class;
	typedef OdDb3dPolyline  native_class;

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	// NcDEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane&, NcDb::Planarity&) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const override;

	// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getParamAtDist(double distance, double& param) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getArea(double& area) const override;

public:
	Nano::ErrorStatus makeClosed();
	Nano::ErrorStatus makeOpen();

	NcDb::Poly3dType polyType() const;
	Nano::ErrorStatus setPolyType(NcDb::Poly3dType type);
	Nano::ErrorStatus convertToPolyType(NcDb::Poly3dType type);

	Nano::ErrorStatus straighten();
	Nano::ErrorStatus splineFit();
	Nano::ErrorStatus splineFit(NcDb::Poly3dType type, NRX::Int16 segments);

	Nano::ErrorStatus appendVertex(NcDb3dPolylineVertex* vertex);
	Nano::ErrorStatus appendVertex(NcDbObjectId& id, NcDb3dPolylineVertex* vertex);

	Nano::ErrorStatus insertVertexAt(const NcDb3dPolylineVertex* after, NcDb3dPolylineVertex* vertex);
	Nano::ErrorStatus insertVertexAt(NcDbObjectId& id, const NcDbObjectId& after, NcDb3dPolylineVertex* vertex);

	Nano::ErrorStatus openVertex(NcDb3dPolylineVertex*& vertex, NcDbObjectId id, NcDb::OpenMode mode,
	                             bool open_erased = false);
	Nano::ErrorStatus openSequenceEnd(NcDbSequenceEnd*& pSequenceEnd, NcDb::OpenMode mode);

	NcDbObjectIterator* vertexIterator() const;

	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source);

public:
	OdDb3dPolyline* native() const;
	OdRxObject* GetNativeObject() const;

protected:
	NcArray< NcDb3dPolylineVertex* > m_arrVertex;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDb2dPolyline
class OdDb2dPolyline;
class NRXDBGATE_EXPORT NcDb2dPolyline : public NcDbCurve
{
	NCDB_DECLARE_MEMBERS(NcDb2dPolyline);

public:
	NcDb2dPolyline();
	NcDb2dPolyline(NcDb::Poly2dType type, NcGePoint3dArray& vertices, double elevation = 0,
	               NRX::Boolean closed = NRX::kFalse, double defStartWidth = 0, double defEndWidth = 0,
	               NcGeDoubleArray* bulges = NULL, NcArray<NRX::Int32>* vertexIdentifiers = NULL);

	NcDb2dPolyline(OdRxObject* _object);

	virtual ~NcDb2dPolyline();

	virtual Nano::ErrorStatus dxfIn(NcDbDxfFiler* filer) const; //+Overload

public:
	typedef NcDb2dPolyline  wrapper_class;
	typedef OdDb2dPolyline  native_class;

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	// NcDEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane&, NcDb::Planarity&) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const override;

	// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getParamAtDist(double distance, double& param) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getArea(double& area) const override;

public:
	NcDb::Poly2dType polyType() const;
	Nano::ErrorStatus setPolyType(NcDb::Poly2dType type);
	Nano::ErrorStatus convertToPolyType(NcDb::Poly2dType type);

	Nano::ErrorStatus makeClosed();
	Nano::ErrorStatus makeOpen();

	double defaultStartWidth() const;
	Nano::ErrorStatus setDefaultStartWidth(double width);

	double defaultEndWidth() const;
	Nano::ErrorStatus setDefaultEndWidth(double width);

	double thickness() const;
	Nano::ErrorStatus setThickness(double thickness);

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

	double elevation() const;
	Nano::ErrorStatus setElevation(double elevation);

	NRX::Boolean isLinetypeGenerationOn() const;
	Nano::ErrorStatus setLinetypeGenerationOn();
	Nano::ErrorStatus setLinetypeGenerationOff();

	Nano::ErrorStatus straighten();
	Nano::ErrorStatus splineFit();
	Nano::ErrorStatus splineFit(NcDb::Poly2dType splineType, NRX::Int16 splineSegs);
	Nano::ErrorStatus curveFit();

	Nano::ErrorStatus appendVertex(NcDb2dVertex* vertex);
	Nano::ErrorStatus appendVertex(NcDbObjectId& id, NcDb2dVertex* vertex);

	Nano::ErrorStatus insertVertexAt(const NcDb2dVertex* after, NcDb2dVertex* vertex);
	Nano::ErrorStatus insertVertexAt(NcDbObjectId& id, const NcDbObjectId& after, NcDb2dVertex* vertex);

	Nano::ErrorStatus openVertex(NcDb2dVertex*& vertex, NcDbObjectId id, NcDb::OpenMode mode,
	                             bool open_erased = false) const;
	Nano::ErrorStatus openSequenceEnd(NcDbSequenceEnd*& pSequenceEnd, NcDb::OpenMode mode);

	NcDbObjectIterator* vertexIterator() const;

	NcGePoint3d vertexPosition(const NcDb2dVertex& vert) const;

	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source);

public:
	OdDb2dPolyline* native() const;

public:
	OdRxObject* GetNativeObject() const;

protected:
	NcArray< NcDb2dVertex* > m_arrVertex;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbPolyline
class OdDbPolyline;
class NRXDBGATE_EXPORT NcDbPolyline : public NcDbCurve
{
	NCDB_DECLARE_MEMBERS(NcDbPolyline);

public:
	NcDbPolyline();
	NcDbPolyline(unsigned int num_verts);

	NcDbPolyline(OdRxObject* _object);

public:
	typedef NcDbPolyline  wrapper_class;
	typedef OdDbPolyline  native_class;

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual void saveAs(NcGiWorldDraw* mode, NcDb::SaveType st) override;

	// NcDEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane&, NcDb::Planarity&) const override;

	virtual void getEcs(NcGeMatrix3d& mat) const override;

	virtual Nano::ErrorStatus applyPartialUndo(NcDbDwgFiler* filer, NcRxClass* rxclass) override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;

	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const override;

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                      const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const override;

	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& markers) const override;

	// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getParamAtDist(double distance, double& param) const override;
	virtual Nano::ErrorStatus getDistAtPoint(const NcGePoint3d& point, double& distance) const override;
	virtual Nano::ErrorStatus getPointAtDist(double distance, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getClosestPointTo(const NcGePoint3d& given, NcGePoint3d& point,
	                                            NRX::Boolean = NRX::kFalse) const override;
	virtual Nano::ErrorStatus getClosestPointTo(const NcGePoint3d& given, const NcGeVector3d& direction,
	                                            NcGePoint3d& point,
	                                            NRX::Boolean = NRX::kFalse) const override;
	virtual Nano::ErrorStatus getOrthoProjectedCurve(const NcGePlane& plane, NcDbCurve*& curve) const override;
	virtual Nano::ErrorStatus getProjectedCurve(const NcGePlane& plane, const NcGeVector3d& direction,
	                                            NcDbCurve*& curve) const override;
	virtual Nano::ErrorStatus getOffsetCurves(double distance, NcDbVoidPtrArray& curves) const override;
	virtual Nano::ErrorStatus getOffsetCurvesGivenPlaneNormal(const NcGeVector3d& normal, double distance,
	                                                          NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus getSpline(NcDbSpline*& spline) const override;
	virtual Nano::ErrorStatus getSplitCurves(const NcGeDoubleArray& params, NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus getSplitCurves(const NcGePoint3dArray& points, NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus extend(double param) override;
	virtual Nano::ErrorStatus extend(NRX::Boolean start, const NcGePoint3d& point) override;
	virtual Nano::ErrorStatus getArea(double& area) const override;
	virtual Nano::ErrorStatus reverseCurve() override;

public:
	Nano::ErrorStatus convertFrom(NcDbEntity*& pline, NRX::Boolean transferId = NRX::kTrue);
	Nano::ErrorStatus convertTo(NcDb2dPolyline*& pline, NRX::Boolean transferId = NRX::kTrue) const;

	Nano::ErrorStatus getPointAt(unsigned int, NcGePoint3d& pt) const;

	enum SegType
	{
		kLine,        // Straight segment with length > 0.
		kArc,         // Arc segment with length > 0.
		kCoincident,  // Segment with length == 0.
		kPoint,       // Polyline with 1 vertex.
		kEmpty        // Polyline with 0 vertices.
	};

	SegType segType(unsigned int index) const;

	Nano::ErrorStatus getLineSegAt(unsigned int index, NcGeLineSeg2d& line) const;
	Nano::ErrorStatus getLineSegAt(unsigned int index, NcGeLineSeg3d& line) const;
	Nano::ErrorStatus getArcSegAt(unsigned int index, NcGeCircArc2d& arc) const;
	Nano::ErrorStatus getArcSegAt(unsigned int index, NcGeCircArc3d& arc) const;
	virtual NRX::Boolean onSegAt(unsigned int index, const NcGePoint2d& pt2d, double& param) const;

	void setClosed(NRX::Boolean);
	void setPlinegen(NRX::Boolean);
	void setElevation(double);
	Nano::ErrorStatus setThickness(double);
	Nano::ErrorStatus setConstantWidth(double);
	Nano::ErrorStatus setNormal(const NcGeVector3d&);

	NRX::Boolean isOnlyLines() const;
	NRX::Boolean hasPlinegen() const;
	double elevation() const;
	double thickness() const;
	Nano::ErrorStatus getConstantWidth(double&) const;
	NcGeVector3d normal() const;

	Nano::ErrorStatus addVertexAt(unsigned int index, const NcGePoint2d& pt, double bulge = 0.,
	                              double startWidth = -1., double endWidth = -1., NRX::Int32 vertexIdentifier = 0);

	Nano::ErrorStatus removeVertexAt(unsigned int index);

	unsigned int numVerts() const;

	Nano::ErrorStatus getPointAt(unsigned int index, NcGePoint2d& pt) const;
	Nano::ErrorStatus getBulgeAt(unsigned int index, double& bulge) const;
	Nano::ErrorStatus getVertexIdentifierAt(unsigned int index, NRX::Int32& vertexIdentifier) const;
	Nano::ErrorStatus getWidthsAt(unsigned int index, double& startWidth, double& endWidth) const;

	Nano::ErrorStatus setPointAt(unsigned int index, const NcGePoint2d& pt);
	Nano::ErrorStatus setBulgeAt(unsigned int index, double bulge);
	Nano::ErrorStatus setVertexIdentifierAt(unsigned int index, NRX::Int32 suggestedValue);
	Nano::ErrorStatus setWidthsAt(unsigned int index, double startWidth, double endWidth);

	Nano::ErrorStatus minimizeMemory();
	Nano::ErrorStatus maximizeMemory();

	void reset(NRX::Boolean reuse, unsigned int numVerts);

	NRX::Boolean hasBulges() const;
	NRX::Boolean hasVertexIdentifiers() const;
	NRX::Boolean hasWidth() const;

protected:
	virtual OdRxObject* GetNativeObject() const;

public:
	OdDbPolyline* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbLine
class OdDbLine;
class NRXDBGATE_EXPORT NcDbLine : public NcDbCurve
{
	NCDB_DECLARE_MEMBERS(NcDbLine);

public:
	typedef NcDbLine  wrapper_class;
	typedef OdDbLine  native_class;

public:
	NcDbLine();
	NcDbLine(const NcGePoint3d& start, const NcGePoint3d& end);

	NcDbLine(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	// NcDEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane&, NcDb::Planarity&) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const override;

	// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	Nano::ErrorStatus getOffsetCurvesGivenPlaneNormal(const NcGeVector3d& normal, double offsetDist,
	                                                  NcDbVoidPtrArray& offsetCurves) const;
	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getParamAtDist(double distance, double& param) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getArea(double& area) const override;

public:
	NcGePoint3d startPoint() const;
	Nano::ErrorStatus setStartPoint(const NcGePoint3d& point);

	NcGePoint3d endPoint() const;
	Nano::ErrorStatus setEndPoint(const NcGePoint3d& point);

	double thickness() const;
	Nano::ErrorStatus setThickness(double thickness);

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

protected:
	virtual OdRxObject* GetNativeObject() const;

public:
	OdDbLine* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbXline
class OdDbXline;
class NRXDBGATE_EXPORT NcDbXline : public NcDbCurve
{
	NCDB_DECLARE_MEMBERS(NcDbXline);

public:
	typedef NcDbXline  wrapper_class;
	typedef OdDbXline  native_class;

public:
	NcDbXline();

	NcDbXline(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	// NcDEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane&, NcDb::Planarity&) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

	// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getParamAtDist(double distance, double& param) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getArea(double& area) const override;
	virtual Nano::ErrorStatus getOffsetCurvesGivenPlaneNormal(const NcGeVector3d& normal, double distance,
	                                                          NcDbVoidPtrArray& segments) const override;

public:
	NcGePoint3d basePoint() const;
	void setBasePoint(const NcGePoint3d& base);

	NcGeVector3d unitDir() const;
	void setUnitDir(const NcGeVector3d& vec);

public:
	OdDbXline* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbPoint
class OdDbPoint;
class NRXDBGATE_EXPORT NcDbPoint : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbPoint);

public:
	typedef NcDbPoint  wrapper_class;
	typedef OdDbPoint  native_class;

public:
	NcDbPoint();
	NcDbPoint(const NcGePoint3d& position);

	NcDbPoint(OdRxObject* _object);

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) ; //+Overload

	// NcGiDrawable interface
protected:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

public:
	NcGePoint3d position() const;
	Nano::ErrorStatus setPosition(const NcGePoint3d& position);

	double thickness() const;
	Nano::ErrorStatus setThickness(double thickness);

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

	double ecsRotation() const;
	Nano::ErrorStatus setEcsRotation(double angle);

public:
	OdDbPoint* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbArc
class OdDbArc;
class NRXDBGATE_EXPORT NcDbArc : public NcDbCurve
{
	NCDB_DECLARE_MEMBERS(NcDbArc);

public:
	typedef NcDbArc  wrapper_class;
	typedef OdDbArc  native_class;

public:
	NcDbArc();
	NcDbArc(const NcGePoint3d& center, double radius, double startAngle, double endAngle);
	NcDbArc(const NcGePoint3d& center, const NcGeVector3d& normal, double radius, double startAngle, double endAngle);

	NcDbArc(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	// NcDEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane&, NcDb::Planarity&) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;

	// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getParamAtDist(double distance, double& param) const override;
	virtual Nano::ErrorStatus getDistAtPoint(const NcGePoint3d& point, double& distance) const override;
	virtual Nano::ErrorStatus getPointAtDist(double distance, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getClosestPointTo(const NcGePoint3d& given, NcGePoint3d& point,
	                                            NRX::Boolean = NRX::kFalse) const override;
	virtual Nano::ErrorStatus getClosestPointTo(const NcGePoint3d& given, const NcGeVector3d& direction,
	                                            NcGePoint3d& point,
	                                            NRX::Boolean = NRX::kFalse) const override;
	virtual Nano::ErrorStatus getOrthoProjectedCurve(const NcGePlane& plane, NcDbCurve*& curve) const override;
	virtual Nano::ErrorStatus getProjectedCurve(const NcGePlane& plane, const NcGeVector3d& direction,
	                                            NcDbCurve*& curve) const override;
	virtual Nano::ErrorStatus getOffsetCurves(double distance, NcDbVoidPtrArray& curves) const override;
	virtual Nano::ErrorStatus getOffsetCurvesGivenPlaneNormal(const NcGeVector3d& normal, double distance,
	                                                          NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus getSpline(NcDbSpline*& spline) const override;
	virtual Nano::ErrorStatus getSplitCurves(const NcGeDoubleArray& params, NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus getSplitCurves(const NcGePoint3dArray& points,
	                                         NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus extend(double param) override;
	virtual Nano::ErrorStatus extend(NRX::Boolean start, const NcGePoint3d& point) override;
	virtual Nano::ErrorStatus getArea(double& area) const override;
	virtual Nano::ErrorStatus reverseCurve() override;

public:
	NcGePoint3d center() const;
	Nano::ErrorStatus setCenter(const NcGePoint3d& center);

	double radius() const;
	Nano::ErrorStatus setRadius(double radius);

	double startAngle() const;
	Nano::ErrorStatus setStartAngle(double angle);

	double endAngle() const;
	Nano::ErrorStatus setEndAngle(double angle);

	double thickness() const;
	Nano::ErrorStatus setThickness(double thickness);

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

protected:
	virtual OdRxObject* GetNativeObject() const;

public:
	OdDbArc* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbRay
class OdDbRay;
class NRXDBGATE_EXPORT NcDbRay : public NcDbCurve
{
	NCDB_DECLARE_MEMBERS(NcDbRay);

public:
	NcDbRay();

	NcDbRay(OdRxObject* _object);

public:
	typedef NcDbRay  wrapper_class;
	typedef OdDbRay  native_class;

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;

	// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane&, NcDb::Planarity&) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;

	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const override;

	// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getParamAtDist(double distance, double& param) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getOffsetCurvesGivenPlaneNormal(const NcGeVector3d& normal, double distance,
	                                                          NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus getArea(double& area) const override;

public:
	NcGePoint3d basePoint() const;
	void setBasePoint(const NcGePoint3d& point);

	NcGeVector3d unitDir() const;
	void setUnitDir(const NcGeVector3d& vector);

public:
	OdDbRay* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbEllipse
class OdDbEllipse;
class NRXDBGATE_EXPORT NcDbEllipse : public NcDbCurve
{
	NCDB_DECLARE_MEMBERS(NcDbEllipse);

public:
	typedef NcDbEllipse  wrapper_class;
	typedef OdDbEllipse  native_class;

public:
	NcDbEllipse();
	NcDbEllipse(const NcGePoint3d& center, const NcGeVector3d& normal, const NcGeVector3d& majorAxis, double radius,
	            double start_angle = 0.0, double end_angle = 6.28318530717958647692);

	NcDbEllipse(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual void saveAs(NcGiWorldDraw* mode, NcDb::SaveType st) override;

	// NcDEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane&, NcDb::Planarity&) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

	// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getParamAtDist(double distance, double& param) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getArea(double& area) const override;

public:
	NcGePoint3d center() const;
	Nano::ErrorStatus setCenter(const NcGePoint3d& center);

	NcGeVector3d normal() const;

	NcGeVector3d majorAxis() const;
	NcGeVector3d minorAxis() const;

	double radiusRatio() const;
	Nano::ErrorStatus setRadiusRatio(double ratio);

	double startAngle() const;
	Nano::ErrorStatus setStartAngle(double start_angle);

	double endAngle() const;
	Nano::ErrorStatus setEndAngle(double end_angle);

	Nano::ErrorStatus setStartParam(double start_param);
	Nano::ErrorStatus setEndParam(double end_param);

	double paramAtAngle(double angle) const;
	double angleAtParam(double param) const;

	Nano::ErrorStatus get(NcGePoint3d& center, NcGeVector3d& normal, NcGeVector3d& major_axis, double& radius_ratio,
	                      double& start_angle, double& end_angle) const;
	Nano::ErrorStatus set(const NcGePoint3d& center, const NcGeVector3d& normal, const NcGeVector3d& major_axis,
	                      double radius_ratio, double start_angle = 0.0,
	                      double end_angle = 6.28318530717958647692);

	NRX::Boolean isNull() const;

protected:
	virtual OdRxObject* GetNativeObject() const;

public:
	OdDbEllipse* native() const;
};

enum SplineType {kFitPoints = 0, kControlPoints = 1};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSpline
class OdDbSpline;
class NRXDBGATE_EXPORT NcDbSpline : public NcDbCurve
{
public:
	NCDB_DECLARE_MEMBERS(NcDbSpline);

public:
	typedef NcDbSpline  wrapper_class;
	typedef OdDbSpline  native_class;

public:
	NcDbSpline();
	NcDbSpline(const NcGePoint3dArray& points, int order = 4, double fitTolerance = 0.0);
	NcDbSpline(const NcGePoint3dArray& points, const NcGeVector3d& startTangent, const NcGeVector3d& endTangent,
	           int order = 4, double fitTolerance = 0.0);
	NcDbSpline(int degree, NRX::Boolean rational, NRX::Boolean closed, NRX::Boolean periodic,
	           const NcGePoint3dArray& controlPoints, const NcGeDoubleArray& knots, const NcGeDoubleArray& weights,
	           double controlPtTol = 0.0, double knotTol = 0.0);
	NcDbSpline(const NcGePoint3d& center, const NcGeVector3d& normal, const NcGeVector3d& majorAxis,
	           double radiusRatio, double startAngle = 0.0, double endAngle = 6.28318530717958647692);

	NcDbSpline(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus decomposeForSave(NcDb::NcDbDwgVersion ver, NcDbObject*& replaceObj,
	                                           NcDbObjectId& replaceId, NRX::Boolean& exchangeXData) override;

	// NcDEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane&, NcDb::Planarity&) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const override;

	// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getParamAtDist(double distance, double& param) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getOffsetCurves(double distance, NcDbVoidPtrArray& curves) const override;
	virtual Nano::ErrorStatus getSplitCurves(const NcGeDoubleArray& params, NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus getSplitCurves(const NcGePoint3dArray& points, NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus getArea(double& area) const override;
	virtual Nano::ErrorStatus reverseCurve() override;

public:
	NRX::Boolean isNull() const;

	NRX::Boolean isRational() const;

	int degree() const;
	Nano::ErrorStatus elevateDegree(int degree);

	int numControlPoints() const;
	Nano::ErrorStatus getControlPointAt(int index, NcGePoint3d& point) const;
	Nano::ErrorStatus setControlPointAt(int index, const NcGePoint3d& point);

	int numFitPoints() const;
	Nano::ErrorStatus getFitPointAt(int index, NcGePoint3d& point) const;
	Nano::ErrorStatus setFitPointAt(int index, const NcGePoint3d& point);

	Nano::ErrorStatus insertFitPointAt(int index, const NcGePoint3d& point);
	Nano::ErrorStatus removeFitPointAt(int index);

	double fitTolerance() const;
	Nano::ErrorStatus setFitTol(double tolerance);

	Nano::ErrorStatus getFitTangents(NcGeVector3d& startTangent, NcGeVector3d& endTangent) const;
	Nano::ErrorStatus setFitTangents(const NcGeVector3d& startTangent, const NcGeVector3d& endTangent);

	NRX::Boolean hasFitData() const;

	Nano::ErrorStatus getFitData(NcGePoint3dArray& points, int& degree, double& tolerance,
	                             NRX::Boolean& tangents_exist, NcGeVector3d& start, NcGeVector3d& end) const;
	Nano::ErrorStatus setFitData(const NcGePoint3dArray& points, int degree, double tolerance,
	                             const NcGeVector3d& start, const NcGeVector3d& end);

	Nano::ErrorStatus purgeFitData();
	Nano::ErrorStatus updateFitData();

	Nano::ErrorStatus getNurbsData(int& degree, NRX::Boolean& rational, NRX::Boolean& closed,
	                               NRX::Boolean& periodic, NcGePoint3dArray& controlPoints,
	                               NcGeDoubleArray& knots, NcGeDoubleArray& weights, double& controlPtTol,
	                               double& knotTol) const;
	Nano::ErrorStatus setNurbsData(int degree, NRX::Boolean rational, NRX::Boolean closed,
	                               NRX::Boolean periodic, const NcGePoint3dArray& controlPoints,
	                               const NcGeDoubleArray& knots, const NcGeDoubleArray& weights, double controlPtTol,
	                               double knotTol);

	double weightAt(int index) const;
	Nano::ErrorStatus setWeightAt(int index, double weight);
	Nano::ErrorStatus insertKnot(double param);

	Nano::ErrorStatus getOffsetCurvesGivenPlaneNormal(
	                    const NcGeVector3d& normal, double offsetDist,NcDbVoidPtrArray& offsetCurves) const;
	Nano::ErrorStatus insertControlPointAt(double knotParam, const NcGePoint3d& ctrlPt, double weight = 1.0);
	Nano::ErrorStatus rebuild(int degree, int numCtrlPts);
	Nano::ErrorStatus removeControlPointAt(int index);
	Nano::ErrorStatus setType(SplineType type);
	Nano::ErrorStatus toPolyline(NcDbCurve*& pCurve, int precision = 10,
	                             int* maxSuggestedPrecision = NULL,
	                             unsigned int numOfVerticesThreshold = nc_constants::kPlineVerticesThrehold) const;
	SplineType type() const;

public:
	OdDbSpline* native() const;

public:
	virtual OdRxObject* GetNativeObject() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbText
class OdDbText;
class NRXDBGATE_EXPORT NcDbText : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbText);

public:
	NcDbText();
	NcDbText(const NcGePoint3d& position, const NCHAR* text, NcDbObjectId style = NcDbObjectId::kNull,
	         double height = 0, double rotation = 0);

	NcDbText(OdRxObject* _object);

public:
	typedef NcDbText  wrapper_class;
	typedef OdDbText  native_class;

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subClose() override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;

	virtual void subSetDatabaseDefaults(NcDbDatabase* database) override;

public:
	NcGePoint3d position() const;
	Nano::ErrorStatus setPosition(const NcGePoint3d& position);

	NcGePoint3d alignmentPoint() const;
	Nano::ErrorStatus setAlignmentPoint(const NcGePoint3d& alignment_point);

	NRX::Boolean isDefaultAlignment() const;

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

	double thickness() const;
	Nano::ErrorStatus setThickness(double thickness);

	double oblique() const;
	Nano::ErrorStatus setOblique(double oblique);

	double rotation() const;
	Nano::ErrorStatus setRotation(double angle);

	double height() const;
	Nano::ErrorStatus setHeight(double height);

	double widthFactor() const;
	Nano::ErrorStatus setWidthFactor(double factor);

	TCHAR* textString() const;
	const TCHAR* textStringConst() const;

	Nano::ErrorStatus setTextString(LPCTSTR string);

	NcDbObjectId textStyle() const;
	Nano::ErrorStatus setTextStyle(NcDbObjectId style);

	NRX::Boolean isMirroredInX() const;
	Nano::ErrorStatus mirrorInX(NRX::Boolean mirror);

	NRX::Boolean isMirroredInY() const;
	Nano::ErrorStatus mirrorInY(NRX::Boolean mirror);

	NcDb::TextHorzMode horizontalMode() const;
	Nano::ErrorStatus setHorizontalMode(NcDb::TextHorzMode mode);

	NcDb::TextVertMode verticalMode() const;
	Nano::ErrorStatus setVerticalMode(NcDb::TextVertMode mode);

	int correctSpelling();

	virtual Nano::ErrorStatus adjustAlignment(const NcDbDatabase* database);

	Nano::ErrorStatus getField(const NCHAR* name, NcDbObjectId& id) const;
	Nano::ErrorStatus getField(const NCHAR* name, NcDbField*& field, NcDb::OpenMode mode) const;

	Nano::ErrorStatus setField(const NCHAR* pszPropName, NcDbField* pField, NcDbObjectId& fieldId);

	Nano::ErrorStatus removeField(NcDbObjectId id);
	Nano::ErrorStatus removeField(const NCHAR* pszPropName, NcDbObjectId& returnId);
	Nano::ErrorStatus removeField(const NCHAR* pszPropName);

	Nano::ErrorStatus convertFieldToText();

public:
	OdDbText* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbAttributeDefinition
class OdDbAttributeDefinition;
class NRXDBGATE_EXPORT NcDbAttributeDefinition : public NcDbText
{
	NCDB_DECLARE_MEMBERS(NcDbAttributeDefinition);

public:
	NcDbAttributeDefinition();
	NcDbAttributeDefinition(const NcGePoint3d& position, const NCHAR* text, const NCHAR* tag, const NCHAR* prompt,
	                        NcDbObjectId style = NcDbObjectId::kNull);

	NcDbAttributeDefinition(OdRxObject* _object);

	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) ; //+Overload
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) ; //+Overload
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) ; //+Overload
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload

public:
	typedef NcDbAttributeDefinition  wrapper_class;
	typedef OdDbAttributeDefinition  native_class;

public:
	NCHAR* prompt() const;
	const NCHAR* promptConst() const;
	Nano::ErrorStatus setPrompt(const NCHAR* prompt);

	NCHAR* tag() const;
	const NCHAR* tagConst() const;
	Nano::ErrorStatus setTag(const NCHAR* tag);

	NRX::Boolean isInvisible() const;
	Nano::ErrorStatus setInvisible(NRX::Boolean invisible);

	NRX::Boolean isConstant() const;
	Nano::ErrorStatus setConstant(NRX::Boolean constant);

	NRX::Boolean isVerifiable() const;
	Nano::ErrorStatus setVerifiable(NRX::Boolean verifiable);

	NRX::Boolean isPreset() const;
	Nano::ErrorStatus setPreset(NRX::Boolean preset);

	NRX::UInt16 fieldLength() const;
	Nano::ErrorStatus setFieldLength(NRX::UInt16 length);

	bool lockPositionInBlock() const;
	Nano::ErrorStatus setLockPositionInBlock(bool lock);

	//virtual Nano::ErrorStatus   adjustAlignment(const NcDbDatabase* pDb = NULL);
	Nano::ErrorStatus convertIntoMTextAttributeDefinition (NRX::Boolean val = NRX::kTrue);
	NcDbMText *       getMTextAttributeDefinition         () const;
	const NcDbMText * getMTextAttributeDefinitionConst    () const;
	bool              isMTextAttributeDefinition          () const;
	Nano::ErrorStatus setMTextAttributeDefinition         (NcDbMText*);

	//virtual Nano::ErrorStatus   subGetClassID(CLSID* pClsid) const;
	Nano::ErrorStatus updateMTextAttributeDefinition      ();

public:
	OdDbAttributeDefinition* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbAttribute
class OdDbAttribute;
class NRXDBGATE_EXPORT NcDbAttribute : public NcDbText
{
	NCDB_DECLARE_MEMBERS(NcDbAttribute);

public:
	NcDbAttribute();
	NcDbAttribute(const NcGePoint3d& position, const NCHAR* text, const NCHAR* tag,
	              NcDbObjectId style = NcDbObjectId::kNull);

	NcDbAttribute(OdRxObject* _object);

	virtual ~NcDbAttribute();

	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) ; //+Overload
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) ; //+Overload
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) ; //+Overload
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) ; //+Overload
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload

public:
	typedef NcDbAttribute  wrapper_class;
	typedef OdDbAttribute  native_class;

public:
	NCHAR* tag() const;
	const NCHAR* tagConst() const;
	Nano::ErrorStatus setTag(const NCHAR* tag);

	NRX::Boolean isInvisible() const;
	Nano::ErrorStatus setInvisible(NRX::Boolean invisible);

	NRX::Boolean isConstant() const;
	NRX::Boolean isVerifiable() const;
	NRX::Boolean isPreset() const;

	NRX::UInt16 fieldLength() const;
	Nano::ErrorStatus setFieldLength(NRX::UInt16 length);

	Nano::ErrorStatus setAttributeFromBlock(const NcGeMatrix3d& xfrm);
	Nano::ErrorStatus setAttributeFromBlock(const NcDbAttributeDefinition* definition, const NcGeMatrix3d& xfrm);

	bool lockPositionInBlock() const;
	Nano::ErrorStatus setLockPositionInBlock(bool lock);

	Nano::ErrorStatus convertIntoMTextAttribute (NRX::Boolean val = NRX::kTrue);
	NcDbMText *       getMTextAttribute         ()                        const;
	const NcDbMText * getMTextAttributeConst    ()                        const;
	bool              isMTextAttribute          ()                        const;
	bool              isReallyLocked            ()                        const;
	Nano::ErrorStatus setMTextAttribute         (NcDbMText *);

	//virtual Nano::ErrorStatus   subGetClassID(CLSID* pClsid) const;
	Nano::ErrorStatus updateMTextAttribute      ();

public:
	OdDbAttribute* native() const;

private:
	mutable NcDbMText* m_mtext;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbHatch
class OdDbHatch;
class NRXDBGATE_EXPORT NcDbHatch : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbHatch);

public:
	typedef NcDbHatch  wrapper_class;
	typedef OdDbHatch  native_class;

public:
	// Enum Definition
	enum HatchObjectType
	{
		kHatchObject    = 0,
		kGradientObject = 1
	};

	enum HatchLoopType
	{
		kDefault          = 0,
		kExternal         = 1,
		kPolyline         = 2,
		kDerived          = 4,
		kTextbox          = 8,
		kOutermost        = 0x10,
		kNotClosed        = 0x20,
		kSelfIntersecting = 0x40,
		kTextIsland       = 0x80,
		kDuplicate        = 0x100
	};

	enum HatchEdgeType
	{
		kLine   = 1,
		kCirArc = 2,
		kEllArc = 3,
		kSpline = 4
	};

	enum HatchPatternType
	{
		kUserDefined   = 0,
		kPreDefined    = 1,
		kCustomDefined = 2
	};

	enum HatchStyle
	{
		kNormal = 0,
		kOuter  = 1,
		kIgnore = 2
	};

	enum GradientPatternType
	{
		kPreDefinedGradient  = 0,
		kUserDefinedGradient = 1
	};

public:
	NcDbHatch();

	NcDbHatch(OdRxObject* _object);

	~NcDbHatch();

	virtual Nano::ErrorStatus getArea(double& area) const; // +Overload

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subClose() override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;
	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const override;

	virtual void subSetDatabaseDefaults(NcDbDatabase* database) override;

	virtual void modifiedGraphics(const NcDbEntity* entity) override;

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                      const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const override;
	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& markers) const override;
	virtual NcDbEntity* subSubentPtr(const NcDbFullSubentPath& id) const override;

public:
	double elevation() const;
	Nano::ErrorStatus setElevation(double elevation);

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

	// Hatch Boundary Methods
	int numLoops() const;

	NRX::Int32 loopTypeAt(int index) const;

	Nano::ErrorStatus getLoopAt(int index, NRX::Int32& type, NcGeVoidPointerArray& edges,
	                            NcGeIntArray& edge_types) const;
	Nano::ErrorStatus getLoopAt(int index, NRX::Int32& type, NcGePoint2dArray& vertices,
	                            NcGeDoubleArray& bulges) const;

	Nano::ErrorStatus appendLoop(NRX::Int32 type, const NcGeVoidPointerArray& edges,
	                             const NcGeIntArray& edge_types);
	Nano::ErrorStatus appendLoop(NRX::Int32 type, const NcGePoint2dArray& vertices, const NcGeDoubleArray& bulges);
	Nano::ErrorStatus appendLoop(NRX::Int32 type, const NcDbObjectIdArray& ids);

	Nano::ErrorStatus insertLoopAt(int index, NRX::Int32 type, const NcGeVoidPointerArray& edges,
	                               const NcGeIntArray& edge_types);
	Nano::ErrorStatus insertLoopAt(int index, NRX::Int32 type, const NcGePoint2dArray& vertices,
	                               const NcGeDoubleArray& bulges);

	Nano::ErrorStatus removeLoopAt(int index);

	// Hatch Association Methods
	bool associative() const;
	Nano::ErrorStatus setAssociative(bool isAssociative);

	Nano::ErrorStatus insertLoopAt(int index, NRX::Int32 type, const NcDbObjectIdArray& ids);

	Nano::ErrorStatus getAssocObjIdsAt(int index, NcDbObjectIdArray& ids) const;

	Nano::ErrorStatus getAssocObjIds(NcDbObjectIdArray& ids) const;

	Nano::ErrorStatus removeAssocObjIds();

	// determines Hatch or Gradient object type
	NcDbHatch::HatchObjectType hatchObjectType() const;
	Nano::ErrorStatus setHatchObjectType(NcDbHatch::HatchObjectType type);

	// Gradient Style Methods
	NcDbHatch::GradientPatternType gradientType() const;

	const NCHAR* gradientName() const;

	Nano::ErrorStatus setGradient(NcDbHatch::GradientPatternType type, const NCHAR* name);

	double gradientAngle() const;
	Nano::ErrorStatus setGradientAngle(double angle);

	Nano::ErrorStatus getGradientColors(unsigned int& count, NcCmColor*& colors, float*& values);

	Nano::ErrorStatus setGradientColors(unsigned int count, NcCmColor* colors, float* values);

	NRX::Boolean getGradientOneColorMode() const;
	Nano::ErrorStatus setGradientOneColorMode(NRX::Boolean oneColorMode);

	double getShadeTintValue() const;
	Nano::ErrorStatus setShadeTintValue(float value);

	double gradientShift() const;
	Nano::ErrorStatus setGradientShift(float shiftValue);

	Nano::ErrorStatus evaluateGradientColorAt(float value, NcCmColor& color);

	// Hatch Pattern Methods
	NcDbHatch::HatchPatternType patternType() const;

	const NCHAR* patternName() const;

	Nano::ErrorStatus setPattern(NcDbHatch::HatchPatternType type, const NCHAR* pattern);

	double patternAngle() const;
	Nano::ErrorStatus setPatternAngle(double angle);

	double patternSpace() const;
	Nano::ErrorStatus setPatternSpace(double space);

	double patternScale() const;
	Nano::ErrorStatus setPatternScale(double scale);

	bool patternDouble() const;
	Nano::ErrorStatus setPatternDouble(bool isDouble);

	int numPatternDefinitions() const;
	Nano::ErrorStatus getPatternDefinitionAt(int index, double& angle, double& baseX, double& baseY, double& offsetX,
	                                         double& offsetY, NcGeDoubleArray& dashes) const;

	// Hatch Style Methods
	NcDbHatch::HatchStyle hatchStyle() const;
	Nano::ErrorStatus setHatchStyle(NcDbHatch::HatchStyle style);

	// Hatch Graphics Display Control Methods
	Nano::ErrorStatus evaluateHatch(bool bUnderestimateNumLines = false);

	bool lineGenerationEnabled() const;
	bool setLineGenerationEnabled(bool bEnable);

	int numHatchLines() const;

	bool isSolidFill() const;

	Nano::ErrorStatus getHatchLineDataAt(int index, NcGePoint2d& start, NcGePoint2d& end) const;

	Nano::ErrorStatus getHatchLinesData(NcGePoint2dArray& start_points, NcGePoint2dArray& end_points) const;

	virtual NRX::Boolean isGradient() const;
	virtual NRX::Boolean isHatch() const;

	NcCmColor backgroundColor() const;
	NcDbRegion* getRegionArea() const;
	NcGePoint2d originPoint() const;
	void removeHatchLines();
	Nano::ErrorStatus setBackgroundColor(const NcCmColor& color);
	Nano::ErrorStatus setOriginPoint(const NcGePoint2d& pt);
	Nano::ErrorStatus setShadeTintValueAndColor2( float value );
	virtual Nano::ErrorStatus subSwapIdWith(NcDbObjectId otherId,
	                                        NRX::Boolean swapXdata = false,
	                                        NRX::Boolean swapExtDict = false);
	virtual Nano::ErrorStatus  swapReferences(const NcDbIdMapping& idMap);

public:
	OdDbHatch* native() const;

private:
	mutable NcGeVoidPointerArray m_loops;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbSolid
class OdDbSolid;
class NRXDBGATE_EXPORT NcDbSolid : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbSolid);

public:
	typedef NcDbSolid  wrapper_class;
	typedef OdDbSolid  native_class;

public:
	NcDbSolid();
	NcDbSolid(const NcGePoint3d& pt0, const NcGePoint3d& pt1, const NcGePoint3d& pt2);
	NcDbSolid(const NcGePoint3d& pt0, const NcGePoint3d& pt1, const NcGePoint3d& pt2, const NcGePoint3d& pt3);

	NcDbSolid(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                      const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const sealed;

	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& markers) const sealed;

public:
	Nano::ErrorStatus getPointAt(NRX::UInt16 idx, NcGePoint3d& point) const;
	Nano::ErrorStatus setPointAt(NRX::UInt16 idx, const NcGePoint3d& point);

	double thickness() const;
	Nano::ErrorStatus setThickness(double thickness);

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

public:
	OdDbSolid* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbTrace
class OdDbTrace;
class NRXDBGATE_EXPORT NcDbTrace : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbTrace);

public:
	typedef NcDbTrace  wrapper_class;
	typedef OdDbTrace  native_class;

public:
	NcDbTrace();
	NcDbTrace(const NcGePoint3d& pt0, const NcGePoint3d& pt1, const NcGePoint3d& pt2, const NcGePoint3d& pt3);

	NcDbTrace(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                      const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const sealed;

	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& markers) const sealed;

public:
	Nano::ErrorStatus getPointAt(NRX::UInt16 index, NcGePoint3d& point) const;
	Nano::ErrorStatus setPointAt(NRX::UInt16 index, const NcGePoint3d& point);

	double thickness() const;
	Nano::ErrorStatus setThickness(double thickness);

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

public:
	OdDbTrace* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbShape
class OdDbShape;
class NRXDBGATE_EXPORT NcDbShape : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbShape);

public:
	typedef NcDbShape  wrapper_class;
	typedef OdDbShape  native_class;

public:
	NcDbShape();
	NcDbShape(const NcGePoint3d& position, double size, double angle = 0, double width_factor = 0);

	NcDbShape(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

public:
	NcGePoint3d position() const;
	Nano::ErrorStatus setPosition(const NcGePoint3d& position);

	double size() const;
	Nano::ErrorStatus setSize(double size);

	NCHAR* name() const;
	Nano::ErrorStatus setName(const NCHAR* name);

	double rotation() const;
	Nano::ErrorStatus setRotation(double angle);

	double widthFactor() const;
	Nano::ErrorStatus setWidthFactor(double factor);

	double oblique() const;
	Nano::ErrorStatus setOblique(double oblique);

	double thickness() const;
	Nano::ErrorStatus setThickness(double thickness);

	NcGeVector3d normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

	NRX::Int16 shapeNumber() const;
	Nano::ErrorStatus setShapeNumber(NRX::Int16 number);

	NcDbObjectId styleId() const;
	Nano::ErrorStatus setStyleId(NcDbObjectId id);

	Nano::ErrorStatus setShapeIndex(NcDbObjectId id){ return this->setStyleId(id); }
	NcDbObjectId shapeIndex() const{ return this->styleId(); }

public:
	OdDbShape* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbFace
class OdDbFace;
class NRXDBGATE_EXPORT NcDbFace : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbFace);

public:
	typedef NcDbFace  wrapper_class;
	typedef OdDbFace  native_class;

public:
	NcDbFace();
	NcDbFace(const NcGePoint3d& pt0, const NcGePoint3d& pt1, const NcGePoint3d& pt2,
	         NRX::Boolean e0vis = NRX::kTrue, NRX::Boolean e1vis = NRX::kTrue,
	         NRX::Boolean e2vis = NRX::kTrue, NRX::Boolean e3vis = NRX::kTrue);
	NcDbFace(const NcGePoint3d& pt0, const NcGePoint3d& pt1, const NcGePoint3d& pt2, const NcGePoint3d& pt3,
	         NRX::Boolean e0vis = NRX::kTrue, NRX::Boolean e1vis = NRX::kTrue,
	         NRX::Boolean e2vis = NRX::kTrue, NRX::Boolean e3vis = NRX::kTrue);

	NcDbFace(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                      const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const sealed;

	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& markers) const sealed;

public:
	Nano::ErrorStatus getVertexAt(NRX::UInt16 index, NcGePoint3d& point) const;
	Nano::ErrorStatus setVertexAt(NRX::UInt16 index, const NcGePoint3d& point);

	Nano::ErrorStatus isEdgeVisibleAt(NRX::UInt16, NRX::Boolean&) const;
	Nano::ErrorStatus makeEdgeVisibleAt(NRX::UInt16 index);
	Nano::ErrorStatus makeEdgeInvisibleAt(NRX::UInt16 index);

	bool set(const NcGePoint3d& pnt0, const NcGePoint3d& pnt1, const NcGePoint3d& pnt2, const NcGePoint3d& pnt3,
	         bool vis0, bool vis1, bool vis2, bool vis3);

public:
	OdDbFace* native() const;
};

//////////////////////////////////////////////////////////////////////////
//    NcDbFaceRecord
class OdDbFaceRecord;
class NRXDBGATE_EXPORT NcDbFaceRecord : public NcDbVertex
{
	NCDB_DECLARE_MEMBERS(NcDbFaceRecord);

public:
	typedef NcDbFaceRecord  wrapper_class;
	typedef OdDbFaceRecord  native_class;

public:
	NcDbFaceRecord();
	NcDbFaceRecord(NRX::Int16 vtx0, NRX::Int16 vtx1, NRX::Int16 vtx2, NRX::Int16 vtx3);

	NcDbFaceRecord(OdRxObject* _object);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;

	// NcDbEntity
public:
	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const override;

public:
	Nano::ErrorStatus getVertexAt(NRX::UInt16 faceIdx, NRX::Int16& vtxIdx) const;
	Nano::ErrorStatus setVertexAt(NRX::UInt16 faceIdx, NRX::Int16 vtxIdx);

	Nano::ErrorStatus isEdgeVisibleAt(NRX::UInt16 faceIndex, NRX::Boolean& visible) const;
	Nano::ErrorStatus makeEdgeVisibleAt(NRX::UInt16 faceIndex);

	Nano::ErrorStatus makeEdgeInvisibleAt(NRX::UInt16 faceIndex);

public:
	OdDbFaceRecord* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbViewport
class OdDbViewport;
class NRXDBGATE_EXPORT NcDbViewport : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbViewport);

public:
	typedef NcDbViewport  wrapper_class;
	typedef OdDbViewport  native_class;

public:
	NcDbViewport();

	NcDbViewport(OdRxObject* _object);

	virtual void modified(const NcDbObject* object) ; // +Overload
	virtual void erased(const NcDbObject* object, NRX::Boolean pErasing) ; // +Overload
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) ; //+Overload
	virtual void setGsView(NcGsView* view) ; //+Overload2

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler*) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler*) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler*) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler*) const override;

	virtual Nano::ErrorStatus subClose() override;
	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;

	// NcDbEntity
public:
	virtual void subSetDatabaseDefaults(NcDbDatabase* database) override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const;

	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const override;

public:
	Nano::ErrorStatus setModelView(const NcDbXrefObjectId& id);
	Nano::ErrorStatus getModelView(NcDbXrefObjectId& id) const;
	Nano::ErrorStatus removeModelView(void);

	Nano::ErrorStatus setSheetView(NcDbObjectId id);
	Nano::ErrorStatus getSheetView(NcDbObjectId& id) const;
	Nano::ErrorStatus removeSheetView(void);

	Nano::ErrorStatus setLabelBlock(NcDbObjectId id);
	Nano::ErrorStatus getLabelBlock(NcDbObjectId& id) const;
	Nano::ErrorStatus removeLabelBlock(void);

	Nano::ErrorStatus syncModelView(void);

	Nano::ErrorStatus getThumbnail(BITMAPINFO*& thumbnail) const;
	Nano::ErrorStatus setThumbnail(const BITMAPINFO* thumbnail);

	double height() const;
	Nano::ErrorStatus setHeight(double height);

	double width() const;
	Nano::ErrorStatus setWidth(double width);

	NcGePoint3d centerPoint() const;
	Nano::ErrorStatus setCenterPoint(const NcGePoint3d& point);

	NRX::Int16 number() const;

	bool isOn() const;
	Nano::ErrorStatus setOn();
	Nano::ErrorStatus setOff();

	NcGePoint3d viewTarget() const;
	Nano::ErrorStatus setViewTarget(const NcGePoint3d& target);

	NcGeVector3d viewDirection() const;
	Nano::ErrorStatus setViewDirection(const NcGeVector3d& direction);

	double viewHeight() const;
	Nano::ErrorStatus setViewHeight(double height);

	NcGePoint2d viewCenter() const;
	Nano::ErrorStatus setViewCenter(const NcGePoint2d& center);

	double twistAngle() const;
	Nano::ErrorStatus setTwistAngle(double angle);

	double lensLength() const;
	Nano::ErrorStatus setLensLength(double length);

	bool isFrontClipOn() const;
	Nano::ErrorStatus setFrontClipOn();
	Nano::ErrorStatus setFrontClipOff();

	bool isBackClipOn() const;
	Nano::ErrorStatus setBackClipOn();
	Nano::ErrorStatus setBackClipOff();

	bool isFrontClipAtEyeOn() const;
	Nano::ErrorStatus setFrontClipAtEyeOn();
	Nano::ErrorStatus setFrontClipAtEyeOff();

	double frontClipDistance() const;
	Nano::ErrorStatus setFrontClipDistance(double distance);

	double backClipDistance() const;
	Nano::ErrorStatus setBackClipDistance(double distance);

	bool isPerspectiveOn() const;
	Nano::ErrorStatus setPerspectiveOn();
	Nano::ErrorStatus setPerspectiveOff();

	bool isUcsFollowModeOn() const;
	Nano::ErrorStatus setUcsFollowModeOn();
	Nano::ErrorStatus setUcsFollowModeOff();

	bool isUcsIconVisible() const;
	Nano::ErrorStatus setUcsIconVisible();
	Nano::ErrorStatus setUcsIconInvisible();

	bool isUcsIconAtOrigin() const;
	Nano::ErrorStatus setUcsIconAtOrigin();
	Nano::ErrorStatus setUcsIconAtCorner();

	bool isFastZoomOn() const { return true; }
	Nano::ErrorStatus setFastZoomOn() { return Nano::eOk; }
	Nano::ErrorStatus setFastZoomOff() { return Nano::eOk; }

	NRX::UInt16 circleSides() const;
	Nano::ErrorStatus setCircleSides(NRX::UInt16 aproxnum);

	bool isSnapOn() const;
	Nano::ErrorStatus setSnapOn();
	Nano::ErrorStatus setSnapOff();

	bool isSnapIsometric() const;
	Nano::ErrorStatus setSnapIsometric();
	Nano::ErrorStatus setSnapStandard();

	double snapAngle() const;
	Nano::ErrorStatus setSnapAngle(double angle);

	NcGePoint2d snapBasePoint() const;
	Nano::ErrorStatus setSnapBasePoint(const NcGePoint2d& point);

	NcGeVector2d snapIncrement() const;
	Nano::ErrorStatus setSnapIncrement(const NcGeVector2d& point);

	NRX::UInt16 snapIsoPair() const;
	Nano::ErrorStatus setSnapIsoPair(NRX::UInt16 pair);

	bool isGridOn() const;
	Nano::ErrorStatus setGridOn();
	Nano::ErrorStatus setGridOff();

	bool isGridBoundToLimits() const;
	Nano::ErrorStatus setGridBoundToLimits(bool bound_to_limits);

	bool isGridAdaptive() const;
	Nano::ErrorStatus setGridAdaptive(bool adaptive);

	bool isGridSubdivisionRestricted() const;
	Nano::ErrorStatus setGridSubdivisionRestricted(bool restricted);

	bool isGridFollow() const;
	Nano::ErrorStatus setGridFollow(bool follow);

	NRX::UInt16 gridMajor() const;
	Nano::ErrorStatus setGridMajor(NRX::UInt16 major);

	NcGeVector2d gridIncrement() const;
	Nano::ErrorStatus setGridIncrement(const NcGeVector2d& vector);

	bool hiddenLinesRemoved() const;
	Nano::ErrorStatus showHiddenLines();
	Nano::ErrorStatus removeHiddenLines();

	Nano::ErrorStatus freezeLayersInViewport(const NcDbObjectIdArray& layers);
	Nano::ErrorStatus thawLayersInViewport(const NcDbObjectIdArray& layers);
	Nano::ErrorStatus thawAllLayersInViewport();
	bool isLayerFrozenInViewport(const NcDbObjectId& layer) const;
	Nano::ErrorStatus getFrozenLayerList(NcDbObjectIdArray& layers) const;

	Nano::ErrorStatus updateDisplay() const;

	NcDbObjectId background() const;
	Nano::ErrorStatus setBackground(NcDbObjectId id);

	NcDbObjectId visualStyle() const;
	Nano::ErrorStatus setVisualStyle(const NcDbObjectId id);

	bool isDefaultLightingOn() const;
	Nano::ErrorStatus setDefaultLightingOn(bool on);
	NcGiViewportTraits::DefaultLightingType defaultLightingType() const;
	Nano::ErrorStatus setDefaultLightingType(NcGiViewportTraits::DefaultLightingType type);

	double brightness() const;
	Nano::ErrorStatus setBrightness(double brightness);

	double contrast() const;
	Nano::ErrorStatus setContrast(double contrast);

	NcCmColor ambientLightColor() const;
	Nano::ErrorStatus setAmbientLightColor(const NcCmColor& color);

	NcDbObjectId sunId() const;
	Nano::ErrorStatus setSun(NcDbObjectId& id, NcDbObject* sun);

	bool isLocked() const;
	Nano::ErrorStatus setLocked();
	Nano::ErrorStatus setUnlocked();

	bool isTransparent() const;
	Nano::ErrorStatus setTransparent();
	Nano::ErrorStatus setOpaque();

	enum StandardScaleType
	{
		kScaleToFit, // Scaled to Fit
		kCustomScale, // Scale is not a standard scale
		k1_1, // 1:1
		k1_2, // 1:2
		k1_4, // 1:4
		k1_5, // 1:5
		k1_8, // 1:8
		k1_10, // 1:10
		k1_16, // 1:16
		k1_20, // 1:20
		k1_30, // 1:30
		k1_40, // 1:40
		k1_50, // 1:50
		k1_100, // 1:100
		k2_1, // 2:1
		k4_1, // 4:1
		k8_1, // 8:1
		k10_1, // 10:1
		k100_1, // 100:1
		k1_128in_1ft, // 1/128"= 1'
		k1_64in_1ft, // 1/64"= 1'
		k1_32in_1ft, // 1/32"= 1'
		k1_16in_1ft, // 1/16"= 1'
		k3_32in_1ft, // 3/32"= 1'
		k1_8in_1ft, // 1/8" = 1'
		k3_16in_1ft, // 3/16"= 1'
		k1_4in_1ft, // 1/4" = 1'
		k3_8in_1ft, // 3/8" = 1'
		k1_2in_1ft, // 1/2" = 1'
		k3_4in_1ft, // 3/4" = 1'
		k1in_1ft, // 1"= 1'
		k1and1_2in_1ft, // 1 1/2"= 1'
		k3in_1ft, // 3"= 1'
		k6in_1ft, // 6"= 1'
		k1ft_1ft // 1'= 1'
	};

	double customScale() const;
	Nano::ErrorStatus setCustomScale(double scale);

	StandardScaleType standardScale() const;
	Nano::ErrorStatus setStandardScale(const NcDbViewport::StandardScaleType type);

	Nano::ErrorStatus plotStyleSheet(NCHAR*& name) const;
	Nano::ErrorStatus plotStyleSheet(const NCHAR*& name) const;
	Nano::ErrorStatus effectivePlotStyleSheet(const NCHAR*& name);
	Nano::ErrorStatus setPlotStyleSheet(const NCHAR* name);

	bool isNonRectClipOn() const;
	Nano::ErrorStatus setNonRectClipOn();
	Nano::ErrorStatus setNonRectClipOff();

	NcDbObjectId nonRectClipEntityId() const;
	Nano::ErrorStatus setNonRectClipEntityId(NcDbObjectId id);

	Nano::ErrorStatus getUcs(NcGePoint3d& origin, NcGeVector3d& x, NcGeVector3d& y) const;
	bool isUcsOrthographic(NcDb::OrthographicView& view) const;
	NcDbObjectId ucsName() const;
	double elevation() const;

	Nano::ErrorStatus setUcs(const NcGePoint3d& origin, const NcGeVector3d& x, const NcGeVector3d& y);
	Nano::ErrorStatus setUcs(NcDb::OrthographicView view);
	Nano::ErrorStatus setUcs(const NcDbObjectId& id);
	Nano::ErrorStatus setUcsToWorld();
	Nano::ErrorStatus setElevation(double elevation);

	bool isViewOrthographic(NcDb::OrthographicView& view) const;
	Nano::ErrorStatus setViewDirection(NcDb::OrthographicView view);

	bool isUcsSavedWithViewport() const;
	void setUcsPerViewport(bool ucsvp);

	void setRenderMode(NcDbAbstractViewTableRecord::RenderMode mode);
	NcDbAbstractViewTableRecord::RenderMode renderMode() const;

	enum ShadePlotType
	{
		kAsDisplayed  = 0,
		kWireframe    = 1,
		kHidden       = 2,
		kRendered     = 3,
		kVisualStyle  = 4,
		kRenderPreset = 5
	};

	NcDbViewport::ShadePlotType shadePlot() const;
	Nano::ErrorStatus setShadePlot(const ShadePlotType type);

	NcDbObjectId shadePlotId() const;
	Nano::ErrorStatus setShadePlot(const ShadePlotType type, const NcDbObjectId id);

	bool plotWireframe() const;
	bool plotAsRaster() const;

	NcGsView* gsView() const;

	void zoomExtents();

	NcDbAnnotationScale* annotationScale() const;
	virtual void copied(const NcDbObject* pDbObj,const NcDbObject* pNewObj);
	NcDbObjectId previousBackground(NcGiDrawable::DrawableType type= NcGiDrawable::kGeometry) const;
	bool previousBackgroundForcedSwitch (void) const;
	Nano::ErrorStatus setAnnotationScale(const NcDbAnnotationScale *pScaleObj);
	Nano::ErrorStatus  setPreviousBackground(NcDbObjectId backgroundId,NcGiDrawable::DrawableType type= NcGiDrawable::kGeometry);
	Nano::ErrorStatus setPreviousBackground(NcDbObjectId backgroundId, NcGiDrawable::DrawableType type,
	                                        bool bForcedSwitch);
	Nano::ErrorStatus setSun(NcDbObjectId &retId, NcDbObject*pSun, bool eraseOldSun);
	Nano::ErrorStatus setToneOperatorParameters(const NcGiToneOperatorParameters& params);
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
	virtual void subObjModified(const NcDbObject* pDbObj, 
	                            const NcDbObject* pSubObj);
	Nano::ErrorStatus toneOperatorParameters(NcGiToneOperatorParameters& params) const;

public:
	OdDbViewport* native() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbExtents
class OdGeExtents3d;
class NRXDBGATE_EXPORT NcDbExtents
{
public:
	NcDbExtents();
	NcDbExtents(const NcDbExtents& src);
	NcDbExtents(const OdGeExtents3d& src);
	NcDbExtents(const NcGePoint3d& min, const NcGePoint3d& max);
	virtual ~NcDbExtents();

	NcDbExtents &operator = (const NcDbExtents& src);

public:
	NcGePoint3d minPoint() const;
	NcGePoint3d maxPoint() const;

	Nano::ErrorStatus set(const NcGePoint3d& min, const NcGePoint3d& max);

	void addPoint(const NcGePoint3d& point);
	void addExt(const NcDbExtents& src);

	Nano::ErrorStatus addBlockExt(NcDbBlockTableRecord* record);

	void expandBy(const NcGeVector3d& vector);
	void transformBy(const NcGeMatrix3d& matrix);

	bool operator == (const NcDbExtents& other) const;
	bool operator != (const NcDbExtents& other) const;

public:
	OdGeExtents3d* native() const;

private:
	OdGeExtents3d* m_pNative;
};

//////////////////////////////////////////////////////////////////////////
//    NcDbDataCell
class OdDbDataCell;
class NRXDBGATE_EXPORT NcDbDataCell : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbDataCell);

	enum CellType
	{
		kUnknown = 0,
		kInteger,
		kDouble,
		kCharPtr,
		kPoint,
		kObjectId,
		kHardOwnerId,
		kSoftOwnerId,
		kHardPtrId,
		kSoftPtrId,
		kBool,
		kVector
	};

public:
	// Constructors
	NcDbDataCell();
	NcDbDataCell(const NcDbDataCell& source);
	NcDbDataCell(int i);
	NcDbDataCell(bool b);
	NcDbDataCell(double d);
	NcDbDataCell(const NcDbObjectId& id);
	NcDbDataCell(const NCHAR* string);
	NcDbDataCell(const NcGePoint3d& point);
	NcDbDataCell(const NcGeVector3d& vec);
	NcDbDataCell(const NcDbHardOwnershipId& hoId);
	NcDbDataCell(const NcDbSoftOwnershipId& soId);
	NcDbDataCell(const NcDbHardPointerId& hpId);
	NcDbDataCell(const NcDbSoftPointerId& spId);

	NcDbDataCell(OdRxObject* _object);

public:
	virtual ~NcDbDataCell();

public:
	typedef NcDbDataCell  wrapper_class;
	typedef OdDbDataCell  native_class;

public:
	virtual void init();

	virtual NcDbDataCell& operator=(const NcDbDataCell& cell);
	virtual NcDbDataCell& operator=(bool b);
	virtual NcDbDataCell& operator=(int i);
	virtual NcDbDataCell& operator=(double d);
	virtual NcDbDataCell& operator=(const NCHAR* pChar);
	virtual NcDbDataCell& operator=(const NcGePoint3d& pt);
	virtual NcDbDataCell& operator=(const NcGeVector3d& vec);
	virtual NcDbDataCell& operator=(const NcDbObjectId& id);
	virtual NcDbDataCell& operator=(const NcDbHardOwnershipId& hoId);
	virtual NcDbDataCell& operator=(const NcDbSoftOwnershipId& soId);
	virtual NcDbDataCell& operator=(const NcDbHardPointerId& hpId);
	virtual NcDbDataCell& operator=(const NcDbSoftPointerId& spId);

	virtual operator bool() const;
	virtual operator int() const;
	virtual operator double() const;
	virtual operator const NCHAR*() const;
	virtual operator NcGePoint3d&() const;
	virtual operator NcGeVector3d&() const;
	virtual operator NcDbObjectId&() const;
	virtual operator NcDbHardOwnershipId&() const;
	virtual operator NcDbSoftOwnershipId&() const;
	virtual operator NcDbHardPointerId&() const;
	virtual operator NcDbSoftPointerId&() const;

	virtual bool operator==(const NcDbDataCell& cell) const;
	virtual bool operator!=(const NcDbDataCell& cell) const;

	virtual NcDbDataCell::CellType type() const;

	static void copyCell(OdDbDataCell* src, OdDbDataCell* dst);

private:
	NcDbDataCellImpl *pImpl;

public:
	OdDbDataCell* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcValue
class NcValue : public NcRxObject {
public:
	enum DataType
	{
		kUnknown            = 0,
		kLong               = (0x1 << 0),
		kDouble             = (0x1 << 1),
		kString             = (0x1 << 2),
		kDate               = (0x1 << 3),
		kPoint              = (0x1 << 4),
		k3dPoint            = (0x1 << 5),
		kObjectId           = (0x1 << 6),
		kBuffer             = (0x1 << 7),
		kResbuf             = (0x1 << 8),
		kGeneral            = (0x1 << 9),
		kColor              = (0x1 << 10),
	};
	enum UnitType
	{
		kUnitless           = 0,
		kDistance           = (0x1 << 0),
		kAngle              = (0x1 << 1),
		kArea               = (0x1 << 2),
		kVolume             = (0x1 << 3),
		kCurrency           = (0x1 << 4),
		kPercentage         = (0x1 << 5),
	};
	enum ParseOption
	{
		kParseOptionNone        = 0,
		kSetDefaultFormat       = (0x1 << 0),
		kPreserveMtextFormat    = (0x1 << 1),
		kConvertTextToValue     = (0x1 << 2),
		kChangeDataType         = (0x1 << 3),
		kParseTextForFieldCode  = (0x1 << 4),
	};
	enum FormatOption
	{
		kFormatOptionNone       = 0,
		kForEditing             = (0x1 << 0),
		kForExpression          = (0x1 << 1),
		kUseMaximumPrecision    = (0x1 << 2),
		kIgnoreMtextFormat      = (0x1 << 3),
	};
public:
	static bool     isValidDataType         (const VARIANT& var);
public:
	NCRX_DECLARE_MEMBERS(NcValue);
	NRXDBGATE_EXPORT NcValue(void);
	NRXDBGATE_EXPORT NcValue(NcValue::DataType nDataType);
	NRXDBGATE_EXPORT NcValue(const NcValue& value);
	NRXDBGATE_EXPORT NcValue(const NCHAR * pszValue);
	NRXDBGATE_EXPORT NcValue(NRX::Int32 lValue);
	NRXDBGATE_EXPORT NcValue(double fValue);
	NRXDBGATE_EXPORT NcValue(const __time64_t& date);
	NRXDBGATE_EXPORT NcValue(const SYSTEMTIME& date);
	NRXDBGATE_EXPORT NcValue(const NcGePoint2d& pt);
	NRXDBGATE_EXPORT NcValue(double x, double y);
	NRXDBGATE_EXPORT NcValue(const NcGePoint3d& pt);
	NRXDBGATE_EXPORT NcValue(double x, double y, double z);
	NRXDBGATE_EXPORT NcValue(const NcDbObjectId& id);
	NRXDBGATE_EXPORT NcValue(const resbuf& rb);
	NRXDBGATE_EXPORT NcValue(const NcDbEvalVariant& evalVar);
	NRXDBGATE_EXPORT NcValue(const VARIANT& var);
	NRXDBGATE_EXPORT NcValue(const NcCmColor& var);
	NRXDBGATE_EXPORT NcValue(const void* pBuf, DWORD dwBufSize);
	NRXDBGATE_EXPORT ~NcValue(void);
	NRXDBGATE_EXPORT bool  reset                   (void);
	NRXDBGATE_EXPORT bool  reset                   (NcValue::DataType nDataType);
	NRXDBGATE_EXPORT bool  resetValue              (void);
	NRXDBGATE_EXPORT NcValue::DataType dataType     (void) const;
	NRXDBGATE_EXPORT NcValue::UnitType unitType     (void) const;
	NRXDBGATE_EXPORT bool  setUnitType             (NcValue::UnitType nUnitType);
	NRXDBGATE_EXPORT const NCHAR* getFormat        (void) const;
	NRXDBGATE_EXPORT bool  setFormat               (const NCHAR* pszFormat);
	NRXDBGATE_EXPORT bool  isValid                 (void) const;
	NRXDBGATE_EXPORT       operator const NCHAR *  (void) const;
	NRXDBGATE_EXPORT       operator NRX::Int32  (void) const;
	NRXDBGATE_EXPORT       operator double         (void) const;
	NRXDBGATE_EXPORT       operator __time64_t     (void) const;
	NRXDBGATE_EXPORT       operator NcGePoint2d    (void) const;
	NRXDBGATE_EXPORT       operator NcGePoint3d    (void) const;
	NRXDBGATE_EXPORT       operator NcDbObjectId   (void) const;
	NRXDBGATE_EXPORT NcValue& operator=            (const NcValue& value);
	NRXDBGATE_EXPORT NcValue& operator=            (const NCHAR * pszValue);
	NRXDBGATE_EXPORT NcValue& operator=            (NRX::Int32 lValue);
	NRXDBGATE_EXPORT NcValue& operator=            (double fValue);
	NRXDBGATE_EXPORT NcValue& operator=            (__time64_t date);
	NRXDBGATE_EXPORT NcValue& operator=            (const NcGePoint2d& pt);
	NRXDBGATE_EXPORT NcValue& operator=            (const NcGePoint3d& pt);
	NRXDBGATE_EXPORT NcValue& operator=            (const NcDbObjectId& objId);
	NRXDBGATE_EXPORT NcValue& operator=            (const resbuf& rb);
	NRXDBGATE_EXPORT NcValue& operator=            (const NcDbEvalVariant& evalVar);
	NRXDBGATE_EXPORT NcValue& operator=            (const VARIANT& var);
	NRXDBGATE_EXPORT NcValue& operator=            (const NcCmColor& clr);
	NRXDBGATE_EXPORT bool  operator==              (const NcValue& val) const;
	NRXDBGATE_EXPORT bool  operator!=              (const NcValue& val) const;
	NRX::Boolean  isEqualTo               (const NcRxObject* pOther) const;
	NRXDBGATE_EXPORT bool  get                     (const NCHAR *& pszValue) const;
	NRXDBGATE_EXPORT bool  get                     (NCHAR *& pszValue) const;
	NRXDBGATE_EXPORT bool  get                     (NRX::Int32& lValue) const;
	NRXDBGATE_EXPORT bool  get                     (double& fValue) const;
	NRXDBGATE_EXPORT bool  get                     (__time64_t& date) const;
	NRXDBGATE_EXPORT bool  get                     (SYSTEMTIME& date) const;
	NRXDBGATE_EXPORT bool  get                     (NcGePoint2d& pt) const;
	NRXDBGATE_EXPORT bool  get                     (double& x,
	                                                double& y) const;
	NRXDBGATE_EXPORT bool  get                     (NcGePoint3d& pt) const;
	NRXDBGATE_EXPORT bool  get                     (double& x,
	                                                double& y,
	                                                double& z) const;
	NRXDBGATE_EXPORT bool  get                     (NcDbObjectId& objId) const;
	NRXDBGATE_EXPORT bool  get                     (resbuf** pRb) const;
	NRXDBGATE_EXPORT bool  get                     (NcDbEvalVariant& evalVar) const;
	NRXDBGATE_EXPORT bool  get                     (VARIANT& var) const;
	NRXDBGATE_EXPORT bool  get                     (NcCmColor& clr) const;
	NRXDBGATE_EXPORT bool  get                     (void*& pBuf,
	                                                DWORD& dwBufSize) const;
	NRXDBGATE_EXPORT bool  set                     (const NcValue& value);
	NRXDBGATE_EXPORT bool  set                     (const NCHAR* pszValue);
	NRXDBGATE_EXPORT bool  set                     (NcValue::DataType nDataType,
	                                                const NCHAR* pszValue);
	NRXDBGATE_EXPORT bool  set                     (NRX::Int32 lValue);
	NRXDBGATE_EXPORT bool  set                     (double fValue);
	NRXDBGATE_EXPORT bool  set                     (const __time64_t& date);
	NRXDBGATE_EXPORT bool  set                     (const SYSTEMTIME& date);
	NRXDBGATE_EXPORT bool  set                     (const NcGePoint2d& pt);
	NRXDBGATE_EXPORT bool  set                     (double x,
	                                                double y);
	NRXDBGATE_EXPORT bool  set                     (const NcGePoint3d& pt);
	NRXDBGATE_EXPORT bool  set                     (double x,
	                                                double y,
	                                                double z);
	NRXDBGATE_EXPORT bool  set                     (const NcDbObjectId& objId);
	NRXDBGATE_EXPORT bool  set                     (const resbuf& rb);
	NRXDBGATE_EXPORT bool  set                     (const NcDbEvalVariant& evalVar);
	NRXDBGATE_EXPORT bool  set                     (const VARIANT& var);
	NRXDBGATE_EXPORT bool  set                     (const NcCmColor& clr);
	NRXDBGATE_EXPORT bool  set                     (const void* pBuf,
	                                                DWORD dwBufSize);
	NRXDBGATE_EXPORT bool  parse                   (const NCHAR* pszText,
	                                                NcValue::DataType nDataType,
	                                                NcValue::UnitType nUnitType,
	                                                const NCHAR* pszFormat,
	                                                NcValue::ParseOption nOption,
	                                                const NcDbObjectId* pTextStyleId);
	NRXDBGATE_EXPORT const NCHAR* format           (void) const;
	NRXDBGATE_EXPORT NcString format               (const NCHAR* pszFormat) const;
	NRXDBGATE_EXPORT bool  format                  (NCHAR*& pszValue) const;
	NRXDBGATE_EXPORT bool  format                  (const NCHAR* pszFormat,
	                                                NCHAR*& pszValue) const;
	NRXDBGATE_EXPORT NcString format               (NcValue::FormatOption nOption);
	NRXDBGATE_EXPORT NcString format               (const NCHAR* pszFormat,
	                                                NcValue::FormatOption nOption);
	NRXDBGATE_EXPORT bool  convertTo               (NcValue::DataType nDataType,
	                                                NcValue::UnitType nUnitType);
	NRXDBGATE_EXPORT bool  convertTo               (NcValue::DataType nDataType,
	                                                NcValue::UnitType nUnitType,
	                                                bool bResetIfIncompatible);
	Nano::ErrorStatus dwgInFields           (NcDbDwgFiler* pFiler);
	Nano::ErrorStatus dwgOutFields          (NcDbDwgFiler* pFiler) const;
	Nano::ErrorStatus dxfInFields           (NcDbDxfFiler* pFiler);
	Nano::ErrorStatus dxfOutFields          (NcDbDxfFiler* pFiler) const;
private:
	friend class NcSystemInternals;
};

typedef NcArray< NcDbDataCell, NcArrayObjectCopyReallocator< NcDbDataCell > >  NcDbDataCellArray;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbDataTable
class OdDbDataTable;
class NRXDBGATE_EXPORT NcDbDataTable : public NcDbObject
{
	NCDB_DECLARE_MEMBERS(NcDbDataTable);

public:
	NcDbDataTable();
	NcDbDataTable(OdRxObject* _object);

public:
	typedef NcDbDataTable  wrapper_class;
	typedef OdDbDataTable  native_class;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;

	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo);

public:
	virtual NcDbDataTable& operator=(const NcDbDataTable& table);

	virtual NRX::UInt32 numColumns() const;
	virtual NRX::UInt32 numRows() const;

	virtual Nano::ErrorStatus setNumRowsPhysicalSize(NRX::UInt32 n);
	virtual Nano::ErrorStatus setNumRowsGrowSize(NRX::UInt32 n);
	virtual NRX::UInt32 numRowsPhysicalSize() const;
	virtual NRX::UInt32 numRowsGrowSize() const;
	virtual Nano::ErrorStatus setNumColsPhysicalSize(NRX::UInt32 n);
	virtual Nano::ErrorStatus setNumColsGrowSize(NRX::UInt32 n);
	virtual NRX::UInt32 numColsPhysicalSize() const;
	virtual NRX::UInt32 numColsGrowSize() const;

	virtual const NCHAR* tableName() const;
	virtual Nano::ErrorStatus setTableName(const NCHAR* pName);

	virtual Nano::ErrorStatus getColumnAt(NRX::UInt32 index, const NcDbDataColumn *&column) const;
	virtual Nano::ErrorStatus getColumnNameAt(NRX::UInt32 index, NCHAR*& pName) const;
	virtual Nano::ErrorStatus getColumnTypeAt(NRX::UInt32 index, NcDbDataCell::CellType& type) const;
	virtual Nano::ErrorStatus getColumnIndexAtName(const NCHAR* pName, NRX::UInt32& index) const;

	virtual Nano::ErrorStatus appendColumn(NcDbDataCell::CellType type, const NCHAR* pColName = NULL);
	virtual Nano::ErrorStatus insertColumnAt(NRX::UInt32 index, NcDbDataCell::CellType type,
	                                         const NCHAR* pColName = NULL);
	virtual Nano::ErrorStatus removeColumnAt(NRX::UInt32 index);

	virtual Nano::ErrorStatus getRowAt(NRX::UInt32 index, NcDbDataCellArray& outRow) const;
	virtual Nano::ErrorStatus setRowAt(NRX::UInt32 index, const NcDbDataCellArray& row, bool bValidate = true);
	virtual Nano::ErrorStatus appendRow(const NcDbDataCellArray& row, bool bValidate = true);

	virtual Nano::ErrorStatus insertRowAt(NRX::UInt32 index, const NcDbDataCellArray& row, bool bValidate = true);
	virtual Nano::ErrorStatus removeRowAt(NRX::UInt32 index);

	virtual Nano::ErrorStatus getCellAt(NRX::UInt32 row, NRX::UInt32 col, NcDbDataCell& outCell) const;
	virtual Nano::ErrorStatus setCellAt(NRX::UInt32 row, NRX::UInt32 col, const NcDbDataCell& cell);

public:
	OdDbDataTable* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDataLink
class NcDbDataLink : public NcDbObject {
public:
	NCDB_DECLARE_MEMBERS(NcDbDataLink);
	NRXDBGATE_EXPORT NcDbDataLink(void);
	NRXDBGATE_EXPORT virtual ~NcDbDataLink(void);
	NRXDBGATE_EXPORT NcString name                 (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setName     (const NCHAR* pszName);
	NRXDBGATE_EXPORT const NCHAR* description      (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setDescription(const NCHAR* pszDescription);
	NRXDBGATE_EXPORT NcString getToolTip           (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setToolTip  (const NCHAR* pszToolTip);
	NRXDBGATE_EXPORT const NCHAR* dataAdapterId    (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setDataAdapterId(const NCHAR* pszAdapterId);
	NRXDBGATE_EXPORT const NCHAR* connectionString (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setConnectionString(const NCHAR* pszConnectionString);
	NRXDBGATE_EXPORT NcDb::DataLinkOption option   (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setOption   (NcDb::DataLinkOption nOption);
	NRXDBGATE_EXPORT int   updateOption            (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setUpdateOption(int nOption);
	NRXDBGATE_EXPORT Nano::ErrorStatus update      (NcDb::UpdateDirection nDir,
	                                                NcDb::UpdateOption nOption);
	NRXDBGATE_EXPORT Nano::ErrorStatus getUpdateStatus(NcDb::UpdateDirection* pDir,
	                                                   SYSTEMTIME* pTime,
	                                                   NcString* pErrMessage) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setUpdateStatus(const NCHAR* pszErrMessage);
	NRXDBGATE_EXPORT bool  isValid                 (void) const;
	NRXDBGATE_EXPORT int   getTargets              (NcDbObjectIdArray& targetIds) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getSourceFiles(NcDb::DataLinkGetSourceContext nContext,
	                                                  NcStringArray& files) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus repathSourceFiles(LPCTSTR pszBasePath,
	                                                     NcDb::PathOption nOption);
	NRXDBGATE_EXPORT Nano::ErrorStatus getCustomData(const NCHAR* pszKey,
	                                                 NcValue* pData) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setCustomData(const NCHAR* pszKey,
	                                                 const NcValue* pData);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
};

//////////////////////////////////////////////////////////////////////////
/// NcDbTable
class OdDbTable;
class NRXDBGATE_EXPORT NcDbTable : public NcDbBlockReference
{
	NCDB_DECLARE_MEMBERS(NcDbTable);

public:
	typedef NcDbTable  wrapper_class;
	typedef OdDbTable  native_class;

	enum TableStyleOverrides
	{
		//table
		kTitleSuppressed            = 1,
		kHeaderSuppressed           = 2,
		kFlowDirection              = 3,
		kHorzCellMargin             = 4,
		kVertCellMargin             = 5,
		kTitleRowColor              = 6,
		kHeaderRowColor             = 7,
		kDataRowColor               = 8,
		kTitleRowFillNone           = 9,
		kHeaderRowFillNone          = 10,
		kDataRowFillNone            = 11,
		kTitleRowFillColor          = 12,
		kHeaderRowFillColor         = 13,
		kDataRowFillColor           = 14,
		kTitleRowAlignment          = 15,
		kHeaderRowAlignment         = 16,
		kDataRowAlignment           = 17,
		kTitleRowTextStyle          = 18,
		kHeaderRowTextStyle         = 19,
		kDataRowTextStyle           = 20,
		kTitleRowTextHeight         = 21,
		kHeaderRowTextHeight        = 22,
		kDataRowTextHeight          = 23,
		kTitleRowDataType           = 24, // For internal use only
		kHeaderRowDataType          = 25, // For internal use only
		kDataRowDataType            = 26, // For internal use only

		// grid color
		kTitleHorzTopColor          = 40,
		kTitleHorzInsideColor       = 41,
		kTitleHorzBottomColor       = 42,
		kTitleVertLeftColor         = 43,
		kTitleVertInsideColor       = 44,
		kTitleVertRightColor        = 45,

		kHeaderHorzTopColor         = 46,
		kHeaderHorzInsideColor      = 47,
		kHeaderHorzBottomColor      = 48,
		kHeaderVertLeftColor        = 49,
		kHeaderVertInsideColor      = 50,
		kHeaderVertRightColor       = 51,

		kDataHorzTopColor           = 52,
		kDataHorzInsideColor        = 53,
		kDataHorzBottomColor        = 54,
		kDataVertLeftColor          = 55,
		kDataVertInsideColor        = 56,
		kDataVertRightColor         = 57,

		// grid line weight
		kTitleHorzTopLineWeight     = 70,
		kTitleHorzInsideLineWeight  = 71,
		kTitleHorzBottomLineWeight  = 72,
		kTitleVertLeftLineWeight    = 73,
		kTitleVertInsideLineWeight  = 74,
		kTitleVertRightLineWeight   = 75,

		kHeaderHorzTopLineWeight    = 76,
		kHeaderHorzInsideLineWeight = 77,
		kHeaderHorzBottomLineWeight = 78,
		kHeaderVertLeftLineWeight   = 79,
		kHeaderVertInsideLineWeight = 80,
		kHeaderVertRightLineWeight  = 81,

		kDataHorzTopLineWeight      = 82,
		kDataHorzInsideLineWeight   = 83,
		kDataHorzBottomLineWeight   = 84,
		kDataVertLeftLineWeight     = 85,
		kDataVertInsideLineWeight   = 86,
		kDataVertRightLineWeight    = 87,

		// grid visibility
		kTitleHorzTopVisibility     = 100,
		kTitleHorzInsideVisibility  = 101,
		kTitleHorzBottomVisibility  = 102,
		kTitleVertLeftVisibility    = 103,
		kTitleVertInsideVisibility  = 104,
		kTitleVertRightVisibility   = 105,

		kHeaderHorzTopVisibility    = 106,
		kHeaderHorzInsideVisibility = 107,
		kHeaderHorzBottomVisibility = 108,
		kHeaderVertLeftVisibility   = 109,
		kHeaderVertInsideVisibility = 110,
		kHeaderVertRightVisibility  = 111,

		kDataHorzTopVisibility      = 112,
		kDataHorzInsideVisibility   = 113,
		kDataHorzBottomVisibility   = 114,
		kDataVertLeftVisibility     = 115,
		kDataVertInsideVisibility   = 116,
		kDataVertRightVisibility    = 117,

		//cell
		kCellAlignment              = 130,
		kCellBackgroundFillNone     = 131,
		kCellBackgroundColor        = 132,
		kCellContentColor           = 133,
		kCellTextStyle              = 134,
		kCellTextHeight             = 135,
		kCellTopGridColor           = 136,
		kCellRightGridColor         = 137,
		kCellBottomGridColor        = 138,
		kCellLeftGridColor          = 139,
		kCellTopGridLineWeight      = 140,
		kCellRightGridLineWeight    = 141,
		kCellBottomGridLineWeight   = 142,
		kCellLeftGridLineWeight     = 143,
		kCellTopVisibility          = 144,
		kCellRightVisibility        = 145,
		kCellBottomVisibility       = 146,
		kCellLeftVisibility         = 147,
		kCellDataType               = 148,
	};

public:
	NcDbTable();
	NcDbTable(OdRxObject* object);
	NcDbTable(const NcDbLinkedTableData* pTable, NcDb::TableCopyOption nCopyOption);

	// NcRxClass
public:
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source) override;

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler*) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler*) const override;

	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler*) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler*) const override;

	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo) override;

	virtual Nano::ErrorStatus subClose() override;
	virtual void objectClosed(const NcDbObjectId objId) override;
	virtual void erased(const NcDbObject* dbObj, NRX::Boolean pErasing = true) override;

	// NcDbEntity
public:
	virtual void subSetDatabaseDefaults(NcDbDatabase* database) override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const;
	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const override;
	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const override;

public:
	virtual NcDbObjectId tableStyle() const;
	virtual Nano::ErrorStatus setTableStyle(const NcDbObjectId& id);

	virtual NcGeVector3d direction() const;
	virtual Nano::ErrorStatus setDirection(const NcGeVector3d& vector);

	virtual NRX::UInt32 numRows() const;

	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setNumRows(int nRows);

	virtual NRX::UInt32 numColumns() const;

	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setNumColumns(int nCols);

	virtual double width() const;
	virtual Nano::ErrorStatus setWidth(double width);

	virtual double columnWidth(int col) const;
	virtual Nano::ErrorStatus setColumnWidth(int col, double width);
	virtual Nano::ErrorStatus setColumnWidth(double width);

	virtual double height() const;
	virtual Nano::ErrorStatus setHeight(double height);

	virtual double rowHeight(int row) const;
	virtual Nano::ErrorStatus setRowHeight(int row, double height);
	virtual Nano::ErrorStatus setRowHeight(double height);
	virtual double minimumColumnWidth(int col) const;
	virtual double minimumRowHeight(int row) const;
	virtual double minimumTableWidth() const;
	virtual double minimumTableHeight() const;

	/* __declspec(deprecated) */ virtual double horzCellMargin() const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setHorzCellMargin(double gap);

	/* __declspec(deprecated) */ virtual double vertCellMargin() const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setVertCellMargin(double gap);

	virtual NcDb::FlowDirection flowDirection() const;
	virtual Nano::ErrorStatus setFlowDirection(NcDb::FlowDirection flow);

	/* __declspec(deprecated) */ virtual bool isTitleSuppressed() const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus suppressTitleRow(bool value);

	/* __declspec(deprecated) */ virtual bool isHeaderSuppressed() const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus suppressHeaderRow(bool value);

	/* __declspec(deprecated) */ virtual NcDb::CellAlignment alignment(NcDb::RowType type = NcDb::kDataRow) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setAlignment(NcDb::CellAlignment align,
	                                                                    int rowTypes = NcDb::kAllRows);

	/* __declspec(deprecated) */ virtual bool isBackgroundColorNone(NcDb::RowType type = NcDb::kDataRow) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setBackgroundColorNone(bool value,
	                                                                              int rowTypes = NcDb::kAllRows);

	/* __declspec(deprecated) */ virtual NcCmColor backgroundColor(NcDb::RowType type = NcDb::kDataRow) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setBackgroundColor(const NcCmColor& color,
	                                                                          int rowTypes = NcDb::kAllRows);

	/* __declspec(deprecated) */ virtual NcCmColor contentColor(NcDb::RowType type = NcDb::kDataRow) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setContentColor(const NcCmColor& color,
	                                                                       int nRowType = NcDb::kAllRows);

	/* __declspec(deprecated) */virtual Nano::ErrorStatus getDataType(NcValue::DataType& nDataType,
	                                                                  NcValue::UnitType& nUnitType,
	                                                                  NcDb::RowType type) const;
	/* __declspec(deprecated) */virtual Nano::ErrorStatus setDataType(NcValue::DataType nDataType,
	                                                                  NcValue::UnitType nUnitType);

	/* __declspec(deprecated) */virtual Nano::ErrorStatus setDataType(NcValue::DataType nDataType,
	                                                                  NcValue::UnitType nUnitType,
	                                                                  int nRowTypes);

	/* __declspec(deprecated) */ virtual const NCHAR* format(NcDb::RowType type);
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setFormat(const NCHAR* pszFormat);
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setFormat(const NCHAR* pszFormat, int nRowTypes);

	/* __declspec(deprecated) */ virtual NcDbObjectId textStyle(NcDb::RowType type = NcDb::kDataRow) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setTextStyle(const NcDbObjectId& id,
	                                                                    int rowTypes = NcDb::kAllRows);

	/* __declspec(deprecated) */ virtual double textHeight(NcDb::RowType type = NcDb::kDataRow) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setTextHeight(double height, int rowTypes = NcDb::kAllRows);

	/* __declspec(deprecated) */ virtual NcDb::LineWeight gridLineWeight(NcDb::GridLineType gridlineType,
	                                                                     NcDb::RowType type = NcDb::kDataRow) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setGridLineWeight(NcDb::LineWeight lwt, int nBorders,
	                                                                         int nRows);

	/* __declspec(deprecated) */ virtual NcCmColor gridColor(NcDb::GridLineType gridlineType,
	                                                         NcDb::RowType type = NcDb::kDataRow) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setGridColor(const NcCmColor& color, int nBorders,
	                                                                    int nRows);

	/* __declspec(deprecated) */ virtual NcDb::Visibility gridVisibility(NcDb::GridLineType gridlineType,
	                                                                     NcDb::RowType type = NcDb::kDataRow) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setGridVisibility(NcDb::Visibility visible, int nBorders,
	                                                                         int nRows);

	/* __declspec(deprecated) */ virtual bool tableStyleOverrides(NcDbIntArray& overrides) const;
	/* __declspec(deprecated) */ virtual void clearTableStyleOverrides(int options = 0);

	virtual NcDb::CellType cellType(int row, int col) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setCellType(int row, int col, NcDb::CellType type);

	virtual Nano::ErrorStatus getCellExtents(int row, int col, bool isOuterCell, NcGePoint3dArray& pts) const;

	virtual NcGePoint3d attachmentPoint(int row, int col) const;

	virtual NcDb::CellAlignment alignment(int row, int col) const;
	virtual Nano::ErrorStatus setAlignment(int row, int col, NcDb::CellAlignment align);

	virtual bool isBackgroundColorNone(int row, int col) const;
	virtual Nano::ErrorStatus setBackgroundColorNone(int row, int col, bool value);

	virtual NcCmColor backgroundColor(int row, int col) const;
	virtual Nano::ErrorStatus setBackgroundColor(int row, int col, const NcCmColor& color);

	virtual NcCmColor contentColor(int row, int col) const;
	virtual Nano::ErrorStatus setContentColor(int row, int col, const NcCmColor& color);

	virtual bool cellStyleOverrides(int row, int col, NcDbIntArray& overrides) const;

	void clearCellOverrides(int row, int column);

	/* __declspec(deprecated) */ virtual Nano::ErrorStatus deleteCellContent(int row, int col);
	/* __declspec(deprecated) */ virtual NcDb::RowType rowType(int row) const;

	Nano::ErrorStatus getDataType(int row, int col, NcValue::DataType& nDataType, NcValue::UnitType& nUnitType) const;
	Nano::ErrorStatus setDataType(int row, int col, NcValue::DataType nDataType, NcValue::UnitType nUnitType);

	NcValue value(int row, int col) const;

	Nano::ErrorStatus setValue(int row, int col, const NcValue& val);
	Nano::ErrorStatus setValue(int row, int col, LPCTSTR pszText, NcValue::ParseOption nOption);

	Nano::ErrorStatus resetValue(int row, int col);

	const NCHAR* format(int row, int col) const;

	/* __declspec(deprecated) */ Nano::ErrorStatus setFormat(int row, int col, const NCHAR* pszFormat);
	virtual const NCHAR* textStringConst(int row, int col) const;
	virtual NCHAR* textString(int row, int col) const;
	virtual Nano::ErrorStatus textString(int row, int col, NcValue::FormatOption nOption, NcString& sText) const;
	virtual Nano::ErrorStatus setTextString(int row, int col, const NCHAR* text);

	virtual NcDbObjectId fieldId(int row, int col) const;
	virtual Nano::ErrorStatus setFieldId(int row, int col, const NcDbObjectId& fieldId);
	virtual Nano::ErrorStatus setFieldId(int row, int col, const NcDbObjectId& fieldId, NcDb::CellOption nFlag);

	virtual NcDbObjectId textStyle(int row, int col) const;
	virtual Nano::ErrorStatus setTextStyle(int row, int col, const NcDbObjectId& id);

	virtual double textHeight(int row, int col) const;
	virtual Nano::ErrorStatus setTextHeight(int row, int col, double height);

	/* __declspec(deprecated) */ virtual NcDb::RotationAngle textRotation(int row, int col) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setTextRotation(int row, int col, NcDb::RotationAngle rot);

	/* __declspec(deprecated) */ virtual bool isAutoScale(int row, int col) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setAutoScale(int row, int col, bool autoFit);

	virtual NcDbObjectId blockTableRecordId(int row, int col) const;

	virtual Nano::ErrorStatus setBlockTableRecordId(int row, int col, const NcDbObjectId& blkId, bool autoFit = false);

	/* __declspec(deprecated) */ virtual double blockScale(int row, int col) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setBlockScale(int row, int col, double scale);

	/* __declspec(deprecated) */ virtual double blockRotation(int row, int col) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setBlockRotation(int row, int col, double rotAng);

	virtual Nano::ErrorStatus getBlockAttributeValue(int row, int col, const NcDbObjectId& attdefId,
	                                                 NCHAR*& value) const;
	virtual Nano::ErrorStatus setBlockAttributeValue(int row, int col, const NcDbObjectId& attdefId,
	                                                 const NCHAR* value);

	virtual NcCmColor gridColor(int row, int col, NcDb::CellEdgeMask iEdge) const;
	virtual Nano::ErrorStatus setGridColor(int row, int col, short nEdges, const NcCmColor& color);

	virtual NcDb::Visibility gridVisibility(int row, int col, NcDb::CellEdgeMask iEdge) const;
	virtual Nano::ErrorStatus setGridVisibility(int row, int col, short nEdges, NcDb::Visibility value);

	virtual NcDb::LineWeight gridLineWeight(int row, int col, NcDb::CellEdgeMask iEdge) const;
	virtual Nano::ErrorStatus setGridLineWeight(int row, int col, short nEdges, NcDb::LineWeight value);

	virtual Nano::ErrorStatus insertColumns(int col, double width, int nCols = 1);
	virtual Nano::ErrorStatus deleteColumns(int col, int nCols = 1);

	virtual Nano::ErrorStatus insertRows(int row, double height, int nRows = 1);
	virtual Nano::ErrorStatus deleteRows(int row, int nRows = 1);

	virtual Nano::ErrorStatus mergeCells(int minRow, int maxRow, int minCol, int maxCol);
	virtual Nano::ErrorStatus unmergeCells(int minRow, int maxRow, int minCol, int maxCol);

	virtual bool isMergedCell(int row, int col, int* minRow = NULL, int* maxRow = NULL, int* minCol = NULL,
	                          int* maxCol = NULL) const;

	virtual Nano::ErrorStatus generateLayout();
	virtual Nano::ErrorStatus recomputeTableBlock(bool forceUpdate = true);

	virtual bool hitTest(const NcGePoint3d& wpt, const NcGeVector3d& wviewVec, double wxaper, double wyaper,
	                     int& resultRowIndex, int& resultColumnIndex);
	bool hitTest(const NcGePoint3d& wpt, const NcGeVector3d& wviewVec, double wxaper, double wyaper,
	             int& resultRowIndex, int& resultColumnIndex, int& contentIndex, NcDb::TableHitItem& nItem);

	virtual Nano::ErrorStatus select(const NcGePoint3d& wpt, const NcGeVector3d& wvwVec, const NcGeVector3d& wvwxVec,
	                                 double wxaper, double wyaper, bool allowOutside, bool bInPickFirst,
	                                 int& resultRowIndex, int& resultColumnIndex,
	                                 NcDbFullSubentPathArray* pPaths = NULL) const;

	virtual Nano::ErrorStatus selectSubRegion(const NcGePoint3d& wpt1, const NcGePoint3d& wpt2,
	                                          const NcGeVector3d& wvwVec, const NcGeVector3d& wvwxVec, double wxaper,
	                                          double wyaper, NcDb::SelectType seltype,
	                                          bool bIncludeCurrentSelection, bool bInPickFirst, int& rowMin,
	                                          int& rowMax, int& colMin, int& colMax,
	                                          NcDbFullSubentPathArray* pPaths = NULL) const;

	virtual bool reselectSubRegion(NcDbFullSubentPathArray& paths) const;

	virtual Nano::ErrorStatus getSubSelection(int& rowMin, int& rowMax, int& colMin, int& colMax) const;
	NcCellRange getSubSelection (void) const;

	virtual Nano::ErrorStatus setSubSelection(int rowMin, int rowMax, int colMin, int colMax);
	Nano::ErrorStatus setSubSelection (const NcCellRange& range);

	virtual void clearSubSelection();

	virtual bool hasSubSelection() const;

	virtual Nano::ErrorStatus setPosition(const NcGePoint3d&);
	virtual Nano::ErrorStatus setNormal(const NcGeVector3d& newVal);

	virtual Nano::ErrorStatus select_next_cell(int dir, int& resultRowIndex, int& resultColumnIndex,
	                                           NcDbFullSubentPathArray* pPaths = NULL,
	                                           bool bSupportTextCellOnly = true) const;

	virtual void setRegen();
	virtual void suppressInvisibleGrid(bool value);
	virtual Nano::ErrorStatus getCellExtents(int row, int col, double& cellWidth, double& cellHeight,
	                                         bool bAdjustForMargins) const;
	bool isRegenerateTableSuppressed() const;
	void suppressRegenerateTable(bool bSuppress);

	Nano::ErrorStatus setSize(int nRows, int nCols);
	bool canInsert(int nIndex, bool bRow) const;
	Nano::ErrorStatus insertRowsAndInherit(int nIndex, int nInheritFrom, int nNumRows);
	Nano::ErrorStatus insertColumnsAndInherit(int col, int nInheritFrom, int nNumCols);
	bool canDelete(int nIndex, int nCount, bool bRow) const;
	bool isEmpty(int nRow, int nCol) const;
	NcCellRange getMergeRange (int nRow, int nCol) const;
	NcDbTableIterator* getIterator (void) const;
	NcDbTableIterator* getIterator (const NcCellRange* pRange, NcDb::TableIteratorOption nOption) const;
	bool isContentEditable(int nRow, int nCol) const;
	bool isFormatEditable(int nRow, int nCol) const;
	NcDb::CellState cellState(int nRow, int nCol) const;
	Nano::ErrorStatus setCellState(int nRow, int nCol, NcDb::CellState nLock);

	int numContents(int nRow, int nCol) const;
	int createContent(int nRow, int nCol, int nIndex);
	Nano::ErrorStatus moveContent(int nRow, int nCol, int nFromIndex, int nToIndex);
	Nano::ErrorStatus deleteContent(int nRow, int nCol);
	Nano::ErrorStatus deleteContent(int nRow, int nCol, int nIndex);
	Nano::ErrorStatus deleteContent (const NcCellRange& range);

	NcDb::CellContentType contentType(int nRow, int nCol) const;
	NcDb::CellContentType contentType(int nRow, int nCol, int nIndex) const;

	NcValue value (int row, int col, int nContent) const;
	NcValue value (int row, int col, int nContent, NcValue::FormatOption nOption) const;
	Nano::ErrorStatus setValue (int row, int col, int nContent, const NcValue& val);
	Nano::ErrorStatus setValue (int row, int col, int nContent, const NcValue& val, NcValue::ParseOption nOption);
	Nano::ErrorStatus setValue (int row, int col, int nContent, LPCTSTR pszText, NcValue::ParseOption nOption);
	NcString dataFormat(int row, int col) const;
	NcString dataFormat(int row, int col, int nContent) const;
	Nano::ErrorStatus setDataFormat(int row, int col, const NCHAR* pszFormat);
	Nano::ErrorStatus setDataFormat(int row, int col, int nContent, const NCHAR* pszFormat);
	NcString textString (int row, int col, int nContent) const;
	Nano::ErrorStatus textString (int row, int col, int nContent, NcValue::FormatOption nOption, NcString& sText) const;
	Nano::ErrorStatus setTextString(int row, int col, int nContent, const NCHAR* text);
	bool hasFormula(int nRow, int nCol, int nContent) const;
	NcString getFormula (int nRow, int nCol, int nContent) const;
	Nano::ErrorStatus setFormula(int nRow, int nCol, int nContent, const NCHAR* pszFormula);
	NcDbObjectId fieldId(int row, int col, int nContent) const;
	Nano::ErrorStatus setFieldId(int row, int col, int nContent, const NcDbObjectId& fieldId, NcDb::CellOption nFlag);
	NcDbObjectId blockTableRecordId(int row, int col, int nContent) const;
	Nano::ErrorStatus setBlockTableRecordId(int row, int col, int nContent, const NcDbObjectId& blkId, bool autoFit);
	Nano::ErrorStatus getBlockAttributeValue(int row, int col, int nContent, const NcDbObjectId& attdefId,
	                                         NCHAR*& value) const;
	Nano::ErrorStatus setBlockAttributeValue(int row, int col, int nContent, const NcDbObjectId& attdefId,
	                                         const NCHAR* value);
	int getCustomData(int nRow, int nCol) const;
	Nano::ErrorStatus setCustomData(int nRow, int nCol, int nData);
	Nano::ErrorStatus getCustomData (int nRow, int nCol, const NCHAR* pszKey, NcValue* pData) const;
	Nano::ErrorStatus setCustomData (int nRow, int nCol, const NCHAR* pszKey, const NcValue* pData);
	const NCHAR* cellStyle(int nRow, int nCol) const;
	Nano::ErrorStatus setCellStyle(int nRow, int nCol, const NCHAR* pszCellStyle);
	double margin(int nRow, int nCol, NcDb::CellMargin nMargin) const;
	Nano::ErrorStatus setMargin(int nRow, int nCol, NcDb::CellMargin nMargins, double fMargin);
	NcGePoint3d attachmentPoint(int row, int col, int content) const;
	NcCmColor contentColor(int row, int col, int nContent) const;
	Nano::ErrorStatus setContentColor(int row, int col, int nContent, const NcCmColor& color);
	Nano::ErrorStatus getDataType (int row, int col, int nContent, NcValue::DataType& nDataType,
	                               NcValue::UnitType& nUnitType) const;
	Nano::ErrorStatus setDataType (int row, int col, int nContent, NcValue::DataType nDataType,
	                               NcValue::UnitType nUnitType);
	NcDbObjectId textStyle(int row, int col, int nContent) const;
	Nano::ErrorStatus setTextStyle(int row, int col, int nContent, const NcDbObjectId& id);
	double textHeight(int row, int col, int nContent) const;
	Nano::ErrorStatus setTextHeight(int row, int col, int nContent, double height);
	double rotation(void) const;
	double rotation(int row, int col, int nContent) const;
	Nano::ErrorStatus setRotation(double fAngle);
	Nano::ErrorStatus setRotation(int row, int col, int nContent, double fAngle);
	bool isAutoScale(int row, int col, int nContent) const;
	Nano::ErrorStatus setAutoScale(int row, int col, int nContent, bool autoFit);
	double scale(int row, int col, int nContent) const;
	Nano::ErrorStatus setScale(int row, int col, int nContent, double scale);
	NcDb::CellContentLayout contentLayout(int row, int col) const;
	Nano::ErrorStatus setContentLayout(int row, int col, NcDb::CellContentLayout nLayout);
	bool isMergeAllEnabled(int nRow, int nCol) const;
	Nano::ErrorStatus enableMergeAll(int nRow, int nCol, bool bEnable);
	NcDb::CellProperty getOverride(int nRow, int nCol, int nContent) const;
	NcDb::GridProperty getOverride(int nRow, int nCol, NcDb::GridLineType nGridLineType) const;
	Nano::ErrorStatus setOverride(int nRow, int nCol, int nContent, NcDb::CellProperty nOverride);
	Nano::ErrorStatus setOverride(int nRow, int nCol, NcDb::GridLineType nGridLineType, NcDb::GridProperty nOverride);
	Nano::ErrorStatus removeAllOverrides(int nRow, int nCol);
	NcDb::GridLineStyle gridLineStyle(int nRow, int nCol, NcDb::GridLineType nGridLineType) const;
	Nano::ErrorStatus setGridLineStyle(int nRow, int nCol, NcDb::GridLineType nGridLineTypes,
	                                   NcDb::GridLineStyle nLineStyle);
	NcDb::LineWeight gridLineWeight(int nRow, int nCol, NcDb::GridLineType nGridLineType) const;
	Nano::ErrorStatus setGridLineWeight(int nRow, int nCol, NcDb::GridLineType nGridLineTypes,
	                                    NcDb::LineWeight nLineWeight);
	NcDbObjectId gridLinetype(int nRow, int nCol, NcDb::GridLineType nGridLineType) const;
	Nano::ErrorStatus setGridLinetype(int nRow, int nCol, NcDb::GridLineType nGridLineTypes,
	                                  const NcDbObjectId& idLinetype);
	NcCmColor gridColor(int nRow, int nCol, NcDb::GridLineType nGridLineType) const;
	Nano::ErrorStatus setGridColor(int nRow, int nCol, NcDb::GridLineType nGridlineTypes, const NcCmColor& color);
	NcDb::Visibility gridVisibility(int nRow, int nCol, NcDb::GridLineType nGridLineType) const;
	Nano::ErrorStatus setGridVisibility(int nRow, int nCol, NcDb::GridLineType nGridLineTypes,
	                                    NcDb::Visibility nVisibility);
	double gridDoubleLineSpacing(int nRow, int nCol, NcDb::GridLineType nGridLineType) const;
	Nano::ErrorStatus setGridDoubleLineSpacing(int nRow, int nCol, NcDb::GridLineType nGridLineTypes, double fSpacing);
	Nano::ErrorStatus getGridProperty(int nRow, int nCol, NcDb::GridLineType nGridLineType,
	                                  NcGridProperty& gridProp) const;
	Nano::ErrorStatus setGridProperty(int nRow, int nCol, NcDb::GridLineType nGridLineTypes,
	                                  const NcGridProperty& gridProp);
	Nano::ErrorStatus setGridProperty(const NcCellRange& rangeIn, NcDb::GridLineType nGridLineTypes,
	                                  const NcGridProperty& gridProp);

	bool isLinked(int nRow, int nCol) const;
	NcDbObjectId getDataLink(int nRow, int nCol) const;
	Nano::ErrorStatus getDataLink (int nRow, int nCol, NcDbDataLink*& pDataLink, NcDb::OpenMode mode) const;
	int getDataLink (const NcCellRange* pRange, NcDbObjectIdArray& dataLinkIds) const;
	Nano::ErrorStatus setDataLink(int nRow, int nCol, const NcDbObjectId& idDataLink, bool bUpdate);
	Nano::ErrorStatus setDataLink (const NcCellRange& range, const NcDbObjectId& idDataLink, bool bUpdate);
	NcCellRange getDataLinkRange (int nRow, int nCol) const;
	Nano::ErrorStatus removeDataLink(int nRow, int nCol);
	Nano::ErrorStatus removeDataLink(void);
	Nano::ErrorStatus updateDataLink(int nRow, int nCol, NcDb::UpdateDirection nDir, NcDb::UpdateOption nOption);
	Nano::ErrorStatus updateDataLink(NcDb::UpdateDirection nDir, NcDb::UpdateOption nOption);

	bool isBreakEnabled(void) const;
	Nano::ErrorStatus enableBreak(bool bEnable);
	NcDb::TableBreakFlowDirection breakFlowDirection(void) const;
	Nano::ErrorStatus setBreakFlowDirection(NcDb::TableBreakFlowDirection nDir);
	double breakHeight(int nIndex) const;
	Nano::ErrorStatus setBreakHeight(int nIndex, double fHeight);
	NcGeVector3d breakOffset(int nIndex) const;
	Nano::ErrorStatus setBreakOffset(int nIndex, const NcGeVector3d& vec);
	NcDb::TableBreakOption breakOption(void) const;
	Nano::ErrorStatus setBreakOption(NcDb::TableBreakOption nOption);
	double breakSpacing(void) const;
	Nano::ErrorStatus setBreakSpacing(double fSpacing);
	Nano::ErrorStatus copyFrom (const NcDbLinkedTableData* pSrc, NcDb::TableCopyOption nOption);
	Nano::ErrorStatus copyFrom (const NcDbLinkedTableData* pSrc, NcDb::TableCopyOption nOption,
	                            const NcCellRange& srcRange, const NcCellRange& targetRange,
	                            NcCellRange* pNewTargetRangeOut);
	Nano::ErrorStatus copyFrom (const NcDbTable* pSrc, NcDb::TableCopyOption nOption, const NcCellRange& srcRange,
	                            const NcCellRange& targetRange, NcCellRange* pNewTargetRangeOut);
	Nano::ErrorStatus fill (const NcCellRange& fillRange, const NcCellRange& srcRange, NcDb::TableFillOption nOption);
	const NCHAR* getColumnName(int nIndex) const;
	Nano::ErrorStatus setColumnName(int nIndex, const NCHAR* pszName);
	NcString getToolTip (int nRow, int nCol) const;
	Nano::ErrorStatus setToolTip(int nRow, int nCol, const NCHAR* pszToolTip);
	Nano::ErrorStatus createTemplate (NcDbTableTemplate*& Template, NcDb::TableCopyOption nCopyOption);
	Nano::ErrorStatus getIndicatorSize(double& fWidth, double& fHeight) const;

protected:
	virtual OdRxObject* GetNativeObject() const;

public:
	OdDbTable* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbTableStyle
class OdDbTableStyle;
class NRXDBGATE_EXPORT NcDbTableStyle : public NcDbObject
{
public:
	NCDB_DECLARE_MEMBERS(NcDbTableStyle);

public:
	NcDbTableStyle();
	NcDbTableStyle(OdRxObject* _object);

public:
	typedef NcDbTableStyle  wrapper_class;
	typedef OdDbTableStyle  native_class;

	// NcDbObject protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo);

public:
	virtual Nano::ErrorStatus getName(NCHAR*& pszName) const;
	virtual Nano::ErrorStatus setName(const NCHAR* pszName);

	virtual const NCHAR* description(void) const;
	virtual Nano::ErrorStatus setDescription(const NCHAR* pszDescription);

	virtual NRX::UInt32 bitFlags() const;
	virtual Nano::ErrorStatus setBitFlags(NRX::UInt32 flags);

	virtual NcDb::FlowDirection flowDirection(void) const;
	virtual Nano::ErrorStatus setFlowDirection(NcDb::FlowDirection flow);

	// Use margin(NcDb::CellMargin nMargin, const NCHAR* pszCellStyle)
	/* __declspec(deprecated) */ virtual double horzCellMargin(void) const;
	// Use setMargin(NcDb::CellMargin nMargins, double fMargin, const NCHAR* pszCellStyle)
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setHorzCellMargin(double dCellMargin);

	// Use margin(NcDb::CellMargin nMargin, const NCHAR* pszCellStyle)
	/* __declspec(deprecated) */ virtual double vertCellMargin(void) const;
	// Use setMargin(NcDb::CellMargin nMargins, double fMargin, const NCHAR* pszCellStyle)
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setVertCellMargin(double dCellMargin);

	/* __declspec(deprecated) */ virtual bool isTitleSuppressed(void) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus suppressTitleRow(bool bValue);

	/* __declspec(deprecated) */ virtual bool isHeaderSuppressed(void) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus suppressHeaderRow(bool bValue);

	virtual NcDbObjectId textStyle(NcDb::RowType rowType = NcDb::kDataRow) const;
	virtual Nano::ErrorStatus setTextStyle(const NcDbObjectId id, int rowTypes = NcDb::kAllRows);

	virtual double textHeight(NcDb::RowType rowType = NcDb::kDataRow) const;
	virtual Nano::ErrorStatus setTextHeight(double dHeight, int rowTypes = NcDb::kAllRows);

	virtual NcDb::CellAlignment alignment(NcDb::RowType rowType = NcDb::kDataRow) const;
	virtual Nano::ErrorStatus setAlignment(NcDb::CellAlignment alignment, int rowTypes = NcDb::kAllRows);

	virtual NcCmColor color(NcDb::RowType rowType = NcDb::kDataRow) const;
	virtual Nano::ErrorStatus setColor(const NcCmColor& color, int rowTypes = NcDb::kAllRows);

	virtual NcCmColor backgroundColor(NcDb::RowType rowType = NcDb::kDataRow) const;
	virtual Nano::ErrorStatus setBackgroundColor(const NcCmColor& color, int rowTypes = NcDb::kAllRows);

	/* __declspec(deprecated) */ virtual bool isBackgroundColorNone(NcDb::RowType rowType = NcDb::kDataRow) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setBackgroundColorNone(bool bValue,
	                                                                              int rowTypes = NcDb::kAllRows);
	virtual Nano::ErrorStatus getDataType(NcValue::DataType& nDataType, NcValue::UnitType& nUnitType) const;

	/* __declspec(deprecated) */virtual Nano::ErrorStatus getDataType(NcValue::DataType& nDataType,
	                                                                  NcValue::UnitType& nUnitType,
	                                                                  NcDb::RowType rowType) const;
	virtual Nano::ErrorStatus setDataType(NcValue::DataType nDataType, NcValue::UnitType nUnitType);
	/* __declspec(deprecated) */virtual Nano::ErrorStatus setDataType(NcValue::DataType nDataType,
	                                                                  NcValue::UnitType nUnitType, int rowTypes);

	/* __declspec(deprecated) */ virtual const NCHAR* format(void) const;
	/* __declspec(deprecated) */ virtual const NCHAR* format(NcDb::RowType rowType) const;
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setFormat(const NCHAR* pszFormat);
	/* __declspec(deprecated) */ virtual Nano::ErrorStatus setFormat(const NCHAR* pszFormat, int rowTypes);

	virtual NcDb::LineWeight gridLineWeight(NcDb::GridLineType gridLineType,
	                                        NcDb::RowType rowType = NcDb::kDataRow) const;
	virtual Nano::ErrorStatus setGridLineWeight(NcDb::LineWeight lineWeight, int gridLineTypes = NcDb::kAllGridLines,
	                                            int rowTypes = NcDb::kAllRows);
	virtual NcCmColor gridColor(NcDb::GridLineType gridLineType, NcDb::RowType rowType = NcDb::kDataRow) const;
	virtual Nano::ErrorStatus setGridColor(const NcCmColor color, int gridLineTypes = NcDb::kAllGridLines,
	                                       int rowTypes = NcDb::kAllRows);
	virtual NcDb::Visibility gridVisibility(NcDb::GridLineType gridLineType,
	                                        NcDb::RowType rowType = NcDb::kDataRow) const;
	virtual Nano::ErrorStatus setGridVisibility(NcDb::Visibility visible, int gridLineTypes = NcDb::kAllGridLines,
	                                            int rowTypes = NcDb::kAllRows);

	virtual Nano::ErrorStatus postTableStyleToDb(NcDbDatabase* pDb, const NCHAR* styleName, NcDbObjectId& tableStyleId);

	const NCHAR* createCellStyle(void);
	Nano::ErrorStatus createCellStyle(const NCHAR* pszCellStyle);
	Nano::ErrorStatus createCellStyle(const NCHAR* pszCellStyle, const NCHAR* pszFromCellStyle);
	Nano::ErrorStatus renameCellStyle(const NCHAR* pszOldName, const NCHAR* pszNewName);
	Nano::ErrorStatus deleteCellStyle(const NCHAR* pszCellStyle);
	Nano::ErrorStatus copyCellStyle(const NCHAR* pszSrcCellStyle, const NCHAR* pszTargetCellStyle);
	Nano::ErrorStatus copyCellStyle(const NcDbTableStyle* pSrc, const NCHAR* pszSrcCellStyle,
	                                const NCHAR* pszTargetCellStyle);
	Nano::ErrorStatus getUniqueCellStyleName(const NCHAR* pszBaseName, NcString& sUniqueName) const;
	bool isCellStyleInUse(const NCHAR* pszCellStyle) const;
	int numCellStyles(void) const;
	int getCellStyles(NcStringArray& cellstyles) const;

	NcDbObjectId textStyle(const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setTextStyle(const NcDbObjectId& id, const NCHAR* pszCellStyle);

	double textHeight(const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setTextHeight(double dHeight, const NCHAR* pszCellStyle);

	NcDb::CellAlignment alignment(const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setAlignment(NcDb::CellAlignment alignment, const NCHAR* pszCellStyle);

	NcCmColor color(const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setColor(const NcCmColor& color, const NCHAR* pszCellStyle);

	NcCmColor backgroundColor(const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setBackgroundColor(const NcCmColor& color, const NCHAR* pszCellStyle);

	Nano::ErrorStatus getDataType (NcValue::DataType& nDataType, NcValue::UnitType& nUnitType,
	                               const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setDataType (NcValue::DataType nDataType, NcValue::UnitType nUnitType, const NCHAR* pszCellStyle);

	const NCHAR* format(const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setFormat(const NCHAR* pszFormat, const NCHAR* pszCellStyle);

	int cellClass(const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setCellClass(int nClass, const NCHAR* pszCellStyle);

	double rotation(const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setRotation(double fRotation, const NCHAR* pszCellStyle);

	bool isMergeAllEnabled(const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus enableMergeAll(bool bEnable, const NCHAR* pszCellStyle);

	double margin(NcDb::CellMargin nMargin, const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setMargin(NcDb::CellMargin nMargins, double fMargin, const NCHAR* pszCellStyle);

	NcDb::LineWeight gridLineWeight(NcDb::GridLineType gridLineType, const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setGridLineWeight(NcDb::LineWeight lineWeight, NcDb::GridLineType gridLineTypes,
	                                    const NCHAR* pszCellStyle);
	NcCmColor gridColor(NcDb::GridLineType gridLineType, const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setGridColor(const NcCmColor color, NcDb::GridLineType gridLineTypes, const NCHAR* pszCellStyle);
	NcDb::Visibility gridVisibility(NcDb::GridLineType gridLineType, const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setGridVisibility(NcDb::Visibility visible, NcDb::GridLineType gridLineTypes,
	                                    const NCHAR* pszCellStyle);
	double gridDoubleLineSpacing(NcDb::GridLineType gridLineType, const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setGridDoubleLineSpacing(double fSpacing, NcDb::GridLineType gridLineTypes,
	                                           const NCHAR* pszCellStyle);
	NcDb::GridLineStyle gridLineStyle(NcDb::GridLineType gridLineType, const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setGridLineStyle(NcDb::GridLineStyle nLineStyle, NcDb::GridLineType gridLineTypes,
	                                   const NCHAR* pszCellStyle);
	NcDbObjectId gridLinetype(NcDb::GridLineType gridLineType, const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setGridLinetype(const NcDbObjectId& id, NcDb::GridLineType gridLineTypes,
	                                  const NCHAR* pszCellStyle);
	Nano::ErrorStatus getGridProperty(NcGridProperty& gridProp, NcDb::GridLineType nGridLineTypes,
	                                  const NCHAR* pszCellStyle) const;
	Nano::ErrorStatus setGridProperty(const NcGridProperty& gridProp, NcDb::GridLineType nGridLineTypes,
	                                  const NCHAR* pszCellStyle);

	NcDbObjectId getTemplate(void) const;
	Nano::ErrorStatus getTemplate(NcDbTableTemplate*& pTemplate, NcDb::OpenMode mode);
	Nano::ErrorStatus setTemplate(const NcDbObjectId& templateId, NcDb::MergeCellStyleOption nOption);
	Nano::ErrorStatus setTemplate(NcDbTableTemplate* pTemplate, NcDb::MergeCellStyleOption nOption,
	                              NcDbObjectId& templateId);
	NcDbObjectId removeTemplate(void);

public:
	inline OdDbTableStyle* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbObjectReactor
class OdDbObjectReactor;
class NRXDBGATE_EXPORT NcDbObjectReactor : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbObjectReactor);

	NcDbObjectReactor();
	NcDbObjectReactor(OdRxObject* _rxobject);

	virtual ~NcDbObjectReactor();

public:
	typedef NcDbObjectReactor  wrapper_class;
	typedef OdDbObjectReactor  native_class;

public:
	virtual void cancelled(const NcDbObject* object);
	virtual void copied(const NcDbObject* object, const NcDbObject* newObj);
	virtual void erased(const NcDbObject* object, NRX::Boolean pErasing = true);
	virtual void goodbye(const NcDbObject* object);
	virtual void openedForModify(const NcDbObject* object);
	virtual void modified(const NcDbObject* object);
	virtual void subObjModified(const NcDbObject* object, const NcDbObject* subObj);
	virtual void modifyUndone(const NcDbObject* object);
	virtual void modifiedXData(const NcDbObject* object);
	virtual void unappended(const NcDbObject* object);
	virtual void reappended(const NcDbObject* object);
	virtual void objectClosed(const NcDbObjectId id);

public:
	OdDbObjectReactor* native();
};

//////////////////////////////////////////////////////////////////////////
// NcDbEntityReactor
class NRXDBGATE_EXPORT NcDbEntityReactor : public NcDbObjectReactor
{
public:
	NCRX_DECLARE_MEMBERS(NcDbEntityReactor);

	NcDbEntityReactor();
	NcDbEntityReactor(OdRxObject* _object);
	//
	//virtual ~NcDbEntityReactor();

public:
	typedef NcDbEntityReactor  wrapper_class;
	typedef OdDbObjectReactor  native_class;

public:
	virtual void modifiedGraphics(const NcDbEntity* object);
	virtual void dragCloneToBeDeleted(const NcDbEntity* pOriginalObj, const NcDbEntity* pClone);

public:
	OdDbObjectReactor* native();
};

//////////////////////////////////////////////////////////////////////////
// NcDbObjectReactor
class OdDbDatabaseReactor;
class NRXDBGATE_EXPORT NcDbDatabaseReactor : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbDatabaseReactor);

	NcDbDatabaseReactor();
	NcDbDatabaseReactor(OdRxObject* _rxobject);
	//
	//virtual ~NcDbDatabaseReactor();
	//
public:
	typedef NcDbDatabaseReactor  wrapper_class;
	typedef OdDbDatabaseReactor  native_class;

public:
	virtual void objectAppended(const NcDbDatabase* dwg, const NcDbObject* object);
	virtual void objectUnAppended(const NcDbDatabase* dwg, const NcDbObject* object);
	virtual void objectReAppended(const NcDbDatabase* dwg, const NcDbObject* object);
	virtual void objectOpenedForModify(const NcDbDatabase* dwg, const NcDbObject* object);
	virtual void objectModified(const NcDbDatabase* dwg, const NcDbObject* object);
	virtual void objectErased(const NcDbDatabase* dwg, const NcDbObject* object, NRX::Boolean pErased = true);
	virtual void headerSysVarWillChange(const NcDbDatabase* dwg, const NCHAR* name);
	virtual void headerSysVarChanged(const NcDbDatabase* dwg, const NCHAR* name, NRX::Boolean bSuccess);
	virtual void proxyResurrectionCompleted(const NcDbDatabase* dwg, const NCHAR* appname, NcDbObjectIdArray& objects);
	virtual void goodbye(const NcDbDatabase* dwg);

public:
	OdDbDatabaseReactor* native();
};

//////////////////////////////////////////////////////////////////////////
// NcDbMatchProperties
class NRXDBGATE_EXPORT NcDbMatchProperties : public NcRxObject
{
public:
	enum Flags
	{
		kColorFlag         = 0x1,
		kLayerFlag         = 0x2,
		kLtypeFlag         = 0x4,
		kThicknessFlag     = 0x8,
		kLtscaleFlag       = 0x10,
		kTextFlag          = 0x20,
		kDimensionFlag     = 0x40,
		kHatchFlag         = 0x80,
		kLweightFlag       = 0x100,
		kPlotstylenameFlag = 0x200,
		kPolylineFlag      = 0x400,
		kViewportFlag      = 0x800,
		kTableFlag         = 0x1000,
		kMaterialFlag      = 0x2000,
		kShadowDisplayFlag = 0x4000,
		kMultileaderFlag   = 0x8000,
		kSetAllFlagsOn     = 0xFFFF
	};

	NCRX_DECLARE_MEMBERS(NcDbMatchProperties);

	NcDbMatchProperties();
	NcDbMatchProperties(OdRxObject* _objext);

	virtual ~NcDbMatchProperties();

	virtual void copyProperties(NcDbEntity* pSrcEntity, NcDbEntity* pTrgEntity, unsigned int flag) const = 0;

public:
	//inline OdDbMatchPropertiesThunk *native()
	//{
	//    return (OdDbMatchPropertiesThunk*)m_pNative;
	//}
};

//////////////////////////////////////////////////////////////////////////
// NcDb3dSolid
class OdDb3dSolid;
class NRXDBGATE_EXPORT NcDb3dSolid : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDb3dSolid);

public:
	NcDb3dSolid();
	NcDb3dSolid(OdRxObject* _object);

public:
	typedef NcDb3dSolid  wrapper_class;
	typedef OdDb3dSolid  native_class;

	// NcGiDrawable interface
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	virtual Nano::ErrorStatus decomposeForSave(NcDb::NcDbDwgVersion ver, NcDbObject*& replaceObj,
	                                           NcDbObjectId& replaceId, NRX::Boolean& exchangeXData) override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;
	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const override;

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                      const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const override;
	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& markers) const override;

	virtual NcDbEntity* subSubentPtr(const NcDbFullSubentPath& id) const override;

public:
	virtual Nano::ErrorStatus createBox(double xLen, double yLen, double zLen);
	virtual Nano::ErrorStatus createFrustum(double height, double xRadius, double yRadius, double topXRadius);
	virtual Nano::ErrorStatus createSphere(double radius);
	virtual Nano::ErrorStatus createTorus(double majorRadius, double minorRadius);
	virtual Nano::ErrorStatus createPyramid(double height, int sides, double radius, double topRadius = 0.0);
	virtual Nano::ErrorStatus createWedge(double xLen, double yLen, double zLen);
	virtual Nano::ErrorStatus extrude(const NcDbRegion* region, double height, double taperAngle = 0.0);
	virtual Nano::ErrorStatus extrudeAlongPath(const NcDbRegion* region, const NcDbCurve* path,
	                                           double taperAngle = 0.0);

	virtual Nano::ErrorStatus revolve(const NcDbRegion* region, const NcGePoint3d& axisPoint,
	                                  const NcGeVector3d& axisDir, double angleOfRevolution);

	virtual Nano::ErrorStatus createRevolvedSolid(NcDbEntity* pRevEnt, const NcGePoint3d& axisPnt,
	                                              const NcGeVector3d& axisDir, double revAngle, double startAngle,
	                                              NcDbRevolveOptions& revolveOptions);
	virtual Nano::ErrorStatus createRevolvedSolid(NcDbEntity* pRevEnt, const NcDbSubentId& faceSubentId,
	                                              const NcGePoint3d& axisPnt, const NcGeVector3d& axisDir,
	                                              double revAngle, double startAngle,
	                                              NcDbRevolveOptions& revolveOptions);

	virtual Nano::ErrorStatus createSweptSolid(NcDbEntity* pSweepEnt, NcDbEntity* pPathEnt,
	                                           NcDbSweepOptions& sweepOptions);
	virtual Nano::ErrorStatus createSweptSolid(NcDbEntity* pSweepEnt, const NcDbSubentId& faceSubentId,
	                                           NcDbEntity* pPathEnt, NcDbSweepOptions& sweepOptions);

	virtual Nano::ErrorStatus createExtrudedSolid(NcDbEntity* pSweepEnt, const NcGeVector3d& directionVec,
	                                              NcDbSweepOptions& sweepOptions);
	virtual Nano::ErrorStatus createExtrudedSolid(NcDbEntity* pSweepEnt, const NcDbSubentId& faceSubentId,
	                                              const NcGeVector3d& directionVec, NcDbSweepOptions& sweepOptions);
	virtual Nano::ErrorStatus createExtrudedSolid(NcDbEntity* pSweepEnt, const NcDbSubentId& faceSubentId,
	                                              double height, NcDbSweepOptions& sweepOptions);

	virtual Nano::ErrorStatus createLoftedSolid(NcArray< NcDbEntity* >& crossSectionCurves,
	                                            NcArray< NcDbEntity* >& guideCurves, NcDbEntity* pPathCurve,
	                                            NcDbLoftOptions& loftOptions);

	virtual Nano::ErrorStatus createFrom(const NcDbEntity* pFromEntity);

	virtual Nano::ErrorStatus getArea(double& area) const;
	virtual void* body() const;

	virtual Nano::ErrorStatus checkInterference(const NcDb3dSolid* otherSolid, NRX::Boolean createNewSolid,
	                                            NRX::Boolean& solidsInterfere,
	                                            NcDb3dSolid*& commonVolumeSolid) const;

	virtual Nano::ErrorStatus getMassProp(double& volume, NcGePoint3d & centroid, double momInertia[3],
	                                      double prodInertia[3], double prinMoments[3], NcGeVector3d prinAxes[3],
	                                      double radiiGyration[3], NcDbExtents & extents) const;

	virtual NRX::Boolean isNull() const;

	virtual Nano::ErrorStatus getSection(const NcGePlane& plane, NcDbRegion*& sectionRegion) const;

	virtual Nano::ErrorStatus stlOut(const NCHAR* fileName, NRX::Boolean asciiFormat) const;

	virtual NcDbSubentId internalSubentId(void* ent) const;
	virtual void* internalSubentPtr(const NcDbSubentId& id) const;

	virtual Nano::ErrorStatus booleanOper(NcDb::BoolOperType operation, NcDb3dSolid* solid);
	virtual Nano::ErrorStatus setBody(const void* modelerBody);

	virtual Nano::ErrorStatus getSlice(const NcGePlane& plane, NRX::Boolean getNegHalfToo,
	                                   NcDb3dSolid*& negHalfSolid);
	virtual Nano::ErrorStatus getSlice(NcDbSurface* pSurface, bool bGetNegHalfToo, NcDb3dSolid*& pNegHalfSolid);

	virtual NRX::UInt32 numChanges() const;

	virtual Nano::ErrorStatus copyEdge(const NcDbSubentId& subentId, NcDbEntity*& newEntity);
	virtual Nano::ErrorStatus copyFace(const NcDbSubentId& subentId, NcDbEntity*& newEntity);
	virtual Nano::ErrorStatus extrudeFaces(const NcArray< NcDbSubentId* >& subents, double height, double taper);
	virtual Nano::ErrorStatus extrudeFacesAlongPath(const NcArray< NcDbSubentId* >& subents, const NcDbCurve* path);
	virtual Nano::ErrorStatus imprintEntity(const NcDbEntity* pEntity);
	virtual Nano::ErrorStatus cleanBody();
	virtual Nano::ErrorStatus offsetBody(double distance);
	virtual Nano::ErrorStatus offsetFaces(const NcArray< NcDbSubentId* >& subents, double distance);
	virtual Nano::ErrorStatus removeFaces(const NcArray< NcDbSubentId* >& subents);
	virtual Nano::ErrorStatus separateBody(NcArray< NcDb3dSolid* >& newSolids);
	virtual Nano::ErrorStatus shellBody(const NcArray< NcDbSubentId* >& subents, double distance);
	virtual Nano::ErrorStatus taperFaces(const NcArray< NcDbSubentId* >& subents, const NcGePoint3d& basePoint,
	                                     const NcGeVector3d& draftVector, double draftAngle);
	virtual Nano::ErrorStatus transformFaces(const NcArray< NcDbSubentId* >& subents, const NcGeMatrix3d& matrix);

	virtual Nano::ErrorStatus setSubentColor(const NcDbSubentId& subentId, const NcCmColor& color);
	virtual Nano::ErrorStatus getSubentColor(const NcDbSubentId& subentId, NcCmColor& color) const;

	virtual Nano::ErrorStatus setSubentMaterial(const NcDbSubentId& subentId, NcDbObjectId matId);
	virtual Nano::ErrorStatus getSubentMaterial(const NcDbSubentId& subentId, NcDbObjectId& matId) const;

	virtual Nano::ErrorStatus setSubentMaterialMapper(const NcDbSubentId& subentId, const NcGiMapper& mapper);
	virtual Nano::ErrorStatus getSubentMaterialMapper(const NcDbSubentId& subentId, NcGiMapper& mapper) const;

	virtual bool recordHistory() const;

	virtual Nano::ErrorStatus setRecordHistory(bool bRecord);

	virtual bool showHistory() const;

	virtual Nano::ErrorStatus setShowHistory(bool bShow);

	virtual Nano::ErrorStatus convertToBrepAtSubentPaths(const NcDbFullSubentPathArray& paths);

	virtual Nano::ErrorStatus chamferEdges(const NcArray< NcDbSubentId* >& edgeSubentIds,
	                                       const NcDbSubentId& baseFaceSubentId, double baseDist, double otherDist);

	virtual Nano::ErrorStatus filletEdges(const NcArray< NcDbSubentId* >& edgeSubentIds, const NcGeDoubleArray& radius,
	                                      const NcGeDoubleArray& startSetback, const NcGeDoubleArray& endSetback);

	Nano::ErrorStatus createSculptedSolid(
	    const NcArray<NcDbEntity*>& limitingBodies,
	    const NcGeIntArray& limitingFlags);
	Nano::ErrorStatus projectOnToSolid(const NcDbEntity* pEntityToProject,
	                                   const NcGeVector3d& projectionDirection,
	                                   NcArray<NcDbEntity*>& projectedEntities) const;

protected:
	virtual OdRxObject* GetNativeObject() const;

public:
	OdDb3dSolid* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbRegion
class OdDbRegion;
class NRXDBGATE_EXPORT NcDbRegion : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbRegion);

public:
	typedef NcDbRegion  wrapper_class;
	typedef OdDbRegion  native_class;

public:
	NcDbRegion();
	NcDbRegion(OdRxObject* _object);

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus decomposeForSave(NcDb::NcDbDwgVersion ver, NcDbObject*& replaceObj,
	                                           NcDbObjectId& replaceId, NRX::Boolean& exchangeXData) override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;
	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const override;

	virtual void saveAs(NcGiWorldDraw* mode, NcDb::SaveType st);

	virtual Nano::ErrorStatus subIntersectWith(const NcDbEntity* ent, NcDb::Intersect intType,
	                                           NcGePoint3dArray& points, NRX::GsMarker thisGsMarker = 0,
	                                           NRX::GsMarker otherGsMarker = 0) const;
	virtual Nano::ErrorStatus subIntersectWith(const NcDbEntity* ent, NcDb::Intersect intType,
	                                           const NcGePlane& projPlane, NcGePoint3dArray& points,
	                                           NRX::GsMarker thisGsMarker = 0,
	                                           NRX::GsMarker otherGsMarker = 0) const;

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                      const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const override;
	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& markers) const override;

	virtual NcDbEntity* subSubentPtr(const NcDbFullSubentPath& id) const override;

	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const override;

public:
	virtual Nano::ErrorStatus getPerimeter(double&) const;
	virtual Nano::ErrorStatus getArea(double& regionArea) const;
	virtual void* body() const;
	virtual Nano::ErrorStatus getAreaProp(const NcGePoint3d &origin, const NcGeVector3d &xAxis,
	                                      const NcGeVector3d &yAxis, double& perimeter, double& area, NcGePoint2d &
	                                      centroid, double momInertia[2], double& prodInertia, double prinMoments[2],
	                                      NcGeVector2d prinAxes[2], double radiiGyration[2], NcGePoint2d & extentsLow,
	                                      NcGePoint2d & extentsHigh) const;

	virtual Nano::ErrorStatus getPlane(NcGePlane& regionPlane) const;

	virtual NRX::Boolean isNull() const;
	virtual Nano::ErrorStatus getNormal(NcGeVector3d&) const;

	virtual NcDbSubentId internalSubentId(void* ent) const;
	virtual void* internalSubentPtr(const NcDbSubentId& id) const;

	virtual Nano::ErrorStatus booleanOper(NcDb::BoolOperType operation, NcDbRegion* otherRegion);
	virtual Nano::ErrorStatus setBody(const void* modelerBody);

	virtual NRX::UInt32 numChanges() const;

public:
	static Nano::ErrorStatus createFromCurves(const NcDbVoidPtrArray& segments, NcDbVoidPtrArray& regions);

public:
	OdDbRegion* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbGroup
class OdDbGroup;
class NRXDBGATE_EXPORT NcDbGroup : public NcDbObject
{
	NCDB_DECLARE_MEMBERS(NcDbGroup);

public:
	NcDbGroup();
	NcDbGroup(OdRxObject* native);
	NcDbGroup(const NCHAR* grpDesc, bool selectable = true);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus applyPartialUndo(NcDbDwgFiler* filer, NcRxClass* rxclass) override;
	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;
	virtual Nano::ErrorStatus subClose() override;
	virtual void copied(const NcDbObject* object, const NcDbObject* newObj);

public:
	typedef NcDbGroup  wrapper_class;
	typedef OdDbGroup  native_class;

public:
	NcDbGroupIterator* newIterator();

	const NCHAR* description() const;
	Nano::ErrorStatus setDescription(const NCHAR* grpDesc);
	bool isSelectable() const;
	Nano::ErrorStatus setSelectable(bool selectable);

	const NCHAR* name() const;
	Nano::ErrorStatus getName(NCHAR*& name) const;
	Nano::ErrorStatus setName(const NCHAR* newName);

	bool isNotAccessible() const;
	bool isAnonymous() const;
	Nano::ErrorStatus setAnonymous();

	Nano::ErrorStatus append(NcDbObjectId id);
	Nano::ErrorStatus append(NcDbObjectIdArray ids);
	Nano::ErrorStatus prepend(NcDbObjectId id);
	Nano::ErrorStatus prepend(NcDbObjectIdArray ids);
	Nano::ErrorStatus insertAt(NRX::UInt32 idx, NcDbObjectId id);
	Nano::ErrorStatus insertAt(NRX::UInt32 idx, NcDbObjectIdArray ids);
	Nano::ErrorStatus remove(NcDbObjectId id);
	Nano::ErrorStatus removeAt(NRX::UInt32 idx);
	Nano::ErrorStatus remove(NcDbObjectIdArray ids);
	Nano::ErrorStatus removeAt(NRX::UInt32 idx, NcDbObjectIdArray ids);
	Nano::ErrorStatus replace(NcDbObjectId oldId, NcDbObjectId newId);
	Nano::ErrorStatus transfer(NRX::UInt32 fromIndex, NRX::UInt32 toIndex, NRX::UInt32 numItems);
	Nano::ErrorStatus clear();
	NRX::UInt32 numEntities() const;
	bool has(const NcDbEntity* pEntity) const;
	NRX::UInt32 allEntityIds(NcDbObjectIdArray& ids) const;
	Nano::ErrorStatus getIndex(NcDbObjectId id, NRX::UInt32& idx) const;
	Nano::ErrorStatus reverse();

	Nano::ErrorStatus setColor(const NcCmColor& color);
	Nano::ErrorStatus setColorIndex(NRX::UInt16 color);
	Nano::ErrorStatus setLayer(const NCHAR* newVal);
	Nano::ErrorStatus setLayer(NcDbObjectId newVal);
	Nano::ErrorStatus setLinetype(const NCHAR* newVal);
	Nano::ErrorStatus setLinetype(NcDbObjectId newVal);
	Nano::ErrorStatus setLinetypeScale(double newVal);
	Nano::ErrorStatus setVisibility(NcDb::Visibility newVal);
	Nano::ErrorStatus setHighlight(bool newVal);

	Nano::ErrorStatus setMaterial(const NCHAR* newVal);
	Nano::ErrorStatus setMaterial(NcDbObjectId newVal);

public:
	OdDbGroup* native() const;
};
//////////////////////////////////////////////////////////////////////////
// NcDbMPolygonCrossing
class NcDbMPolygonCrossing {
public:
	NcDbMPolygonCrossing();
	~NcDbMPolygonCrossing();
	int getLoopIndex() const;
	void setLoopIndex(int index);
	int getEdgeIndex() const;
	void setEdgeIndex(int index);
	NcGePoint2d getCrossingPoint() const;
	void setCrossingPoint(const NcGePoint2d& pt);
private:
	void* pImp;
};

//////////////////////////////////////////////////////////////////////////
// NcDbMPolygonCrossingArray
const double NcDbMPolygonCrossingFuzz = 1E-6;

class NcDbMPolygonCrossingArray {
public:
	~NcDbMPolygonCrossingArray();
	NcArray<NcDbMPolygonCrossing *> mCrossingArray;
};

//////////////////////////////////////////////////////////////////////////
// NcDbMPolygonNode
class NcDbMPolygonNode {
public:
	NcDbMPolygonNode();
public:
	NcDbMPolygonNode * mParent;
	NcArray<NcDbMPolygonNode*> mChildren;
	int mLoopIndex;
};


//////////////////////////////////////////////////////////////////////////
// NcDbMPolygon
class OdDbMPolygon;
class NRXDBGATE_EXPORT NcDbMPolygon : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbMPolygon);

public:
	enum loopDir {
		kExterior     = 0,            // counter clockwise
		kInterior,                    // clockwise
		kAnnotation                   // text
	};

	NcDbMPolygon();
	NcDbMPolygon(OdRxObject* _object);

public:
	typedef NcDbMPolygon  wrapper_class;
	typedef OdDbMPolygon  native_class;

	virtual Nano::ErrorStatus getArea(double& area) const; // +Overload

	// NcGiDrawable
public:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* mode);

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;

	// NcDbEntity
public:
	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	virtual void saveAs(NcGiWorldDraw* mode, NcDb::SaveType st);

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker gsMark,
	                                                      const NcGePoint3d& pickPoint, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const;
	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& gsMarkers) const;

	virtual NcDbEntity* subSubentPtr(const NcDbFullSubentPath& id) const;

	virtual Nano::ErrorStatus subIntersectWith(const NcDbEntity* ent, NcDb::Intersect intType,
	                                           NcGePoint3dArray& points, NRX::GsMarker thisGsMarker = 0,
	                                           NRX::GsMarker otherGsMarker = 0) const;
	virtual Nano::ErrorStatus subIntersectWith(const NcDbEntity* ent, NcDb::Intersect intType,
	                                           const NcGePlane& projPlane, NcGePoint3dArray& points,
	                                           NRX::GsMarker thisGsMarker = 0,
	                                           NRX::GsMarker otherGsMarker = 0) const;

	virtual Nano::ErrorStatus subGetOsnapPoints(NcDb::OsnapMode osnapMode, NRX::GsMarker gsSelectionMark,
	                                            const NcGePoint3d& pickPoint, const NcGePoint3d& lastPoint,
	                                            const NcGeMatrix3d& xform, NcGePoint3dArray& snapPoints,
	                                            NcDbIntArray& markers) const;

	virtual Nano::ErrorStatus subGetGripPoints(NcGePoint3dArray& gripPoints, NcDbIntArray& osnapModes,
	                                           NcDbIntArray& markers) const;
	virtual Nano::ErrorStatus subMoveGripPointsAt(const NcDbIntArray& indices, const NcGeVector3d& offset);

	virtual Nano::ErrorStatus subGetStretchPoints(NcGePoint3dArray& stretchPoints) const;
	virtual Nano::ErrorStatus subMoveStretchPointsAt(const NcDbIntArray& indices, const NcGeVector3d& offset);

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform);

	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const;

	virtual void subList() const;

	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const;

	virtual void subSetDatabaseDefaults(NcDbDatabase* database) override;
	virtual Nano::ErrorStatus audit(NcDbAuditInfo* );
public:
	virtual NcDbHatch* hatch();

	virtual double elevation() const;
	virtual Nano::ErrorStatus setElevation(double elevation);

	virtual NcGeVector3d normal() const;
	virtual Nano::ErrorStatus setNormal(const NcGeVector3d& normal);

	virtual Nano::ErrorStatus evaluateHatch(bool bUnderestimateNumLines = false);

	virtual NcDbHatch::HatchPatternType patternType() const;

	virtual const TCHAR* patternName() const;
#if !defined(HOST_NO_MFC)
	virtual Nano::ErrorStatus setPattern(NcDbHatch::HatchPatternType patType, const TCHAR* patName);
#endif
	virtual double patternAngle() const;
	virtual Nano::ErrorStatus setPatternAngle(double angle);

	virtual double patternSpace() const;
	virtual Nano::ErrorStatus setPatternSpace(double space);

	virtual double patternScale() const;
	virtual Nano::ErrorStatus setPatternScale(double scale);

	virtual bool patternDouble() const;
	virtual Nano::ErrorStatus setPatternDouble(bool isDouble);

	virtual int numPatternDefinitions() const;
	virtual Nano::ErrorStatus getPatternDefinitionAt(int index, double& angle, double& baseX, double& baseY,
	                                                 double& offsetX, double& offsetY, NcGeDoubleArray& dashes) const;

	Nano::ErrorStatus setGradientAngle(double angle);
	Nano::ErrorStatus setGradientShift(float shiftValue);
	Nano::ErrorStatus setGradientOneColorMode(NRX::Boolean oneColorMode);
	Nano::ErrorStatus setGradientColors(unsigned int count, NcCmColor* colors, float* values);
	Nano::ErrorStatus setGradient(NcDbHatch::GradientPatternType gradType, const TCHAR* gradName);

	virtual NcCmColor patternColor() const;
	virtual Nano::ErrorStatus setPatternColor(const NcCmColor& pc);

	virtual double getArea() const;
	virtual double getPerimeter() const;

	virtual bool isBalanced() const;

	virtual NcGeVector2d getOffsetVector() const;

	virtual Nano::ErrorStatus getMPolygonTree(NcDbMPolygonNode*& loopNode) const;
	virtual void deleteMPolygonTree(NcDbMPolygonNode* loopNode) const;

	virtual Nano::ErrorStatus appendLoopFromBoundary(const NcDbCircle* pCircle, bool excludeCrossing = true,
	                                                 double tol = NcDbMPolygonCrossingFuzz);
	virtual Nano::ErrorStatus appendLoopFromBoundary(const NcDbPolyline* pPoly, bool excludeCrossing = true,
	                                                 double tol = NcDbMPolygonCrossingFuzz);
	virtual Nano::ErrorStatus appendLoopFromBoundary(const NcDb2dPolyline* pPoly, bool excludeCrossing = true,
	                                                 double tol = NcDbMPolygonCrossingFuzz);

	virtual int numMPolygonLoops() const;
	virtual Nano::ErrorStatus getMPolygonLoopAt(int loopIndex, NcGePoint2dArray& vertices,
	                                            NcGeDoubleArray& bulges) const;

	virtual Nano::ErrorStatus insertMPolygonLoopAt(int loopIndex, const NcGePoint2dArray& vertices,
	                                               const NcGeDoubleArray& bulges, bool excludeCrossing = true,
	                                               double tol = NcDbMPolygonCrossingFuzz);

	virtual Nano::ErrorStatus appendMPolygonLoop(const NcGePoint2dArray& vertices, const NcGeDoubleArray& bulges,
	                                             bool excludeCrossing = true, double tol = NcDbMPolygonCrossingFuzz);
	virtual Nano::ErrorStatus removeMPolygonLoopAt(int loopIndex);

	virtual Nano::ErrorStatus balanceTree();
	virtual Nano::ErrorStatus balanceDisplay();

	virtual Nano::ErrorStatus getLoopDirection(int lindex, NcDbMPolygon::loopDir& dir) const;
	virtual Nano::ErrorStatus setLoopDirection(int lindex, NcDbMPolygon::loopDir dir);

	virtual Nano::ErrorStatus getLoopAtGsMarker(int gsMark, int& loop) const;
	virtual void getChildLoops(int curLoop, NcGeIntArray& selectedLoopIndexes) const;
	virtual int getParentLoop(int curLoop) const;
	virtual int getClosestLoopTo(const NcGePoint3d& worldPt) const;

	virtual int isPointInsideMPolygon(const NcGePoint3d& worldPt, NcGeIntArray& loopsArray,
	                                  double tol = NcDbMPolygonCrossingFuzz) const;
	virtual bool isPointOnLoopBoundary(const NcGePoint3d& worldPt, int loop,
	                                   double tol = NcDbMPolygonCrossingFuzz) const;

	virtual Nano::ErrorStatus loopCrossesItself(bool& crosses, bool findAll, NcDbMPolygonCrossingArray& crossingsArray,
	                                            const NcGePoint2dArray& vertexPts, const NcGeDoubleArray &vertexBulges,
	                                            double tol = NcDbMPolygonCrossingFuzz) const;

	virtual bool loopCrossesItself(const NcGePoint2dArray& vertexPts, const NcGeDoubleArray& vertexBulges,
	                               double tol = NcDbMPolygonCrossingFuzz) const;

	virtual Nano::ErrorStatus loopCrossesMPolygon(bool& crosses, bool findAll,
	                                              NcDbMPolygonCrossingArray& crossingsArray,
	                                              const NcGePoint2dArray& testVertexPts,
	                                              const NcGeDoubleArray& testVertexBulges,
	                                              double tol = NcDbMPolygonCrossingFuzz) const;

	virtual bool selfCrosses(const NcGePoint2dArray& vertexPts, const NcGeDoubleArray& vertexBulges,
	                         double tol = NcDbMPolygonCrossingFuzz) const;

	virtual bool includesTouchingLoops(double tol = NcDbMPolygonCrossingFuzz) const;

	virtual Nano::ErrorStatus createLoopsFromBoundaries(const NcDbObjectIdArray& ids, NcDbIntArray& rejectedObjs,
	                                                    bool excludeCrossing = true,
	                                                    double tol = NcDbMPolygonCrossingFuzz);
	virtual Nano::ErrorStatus createLoops(const NcArray< NcGePoint2dArray,
	                                      NcArrayObjectCopyReallocator< NcGePoint2dArray > >& vertices,
	                                      const NcArray< NcGeDoubleArray,
	                                      NcArrayObjectCopyReallocator< NcGeDoubleArray > >& bulges,
	                                      NcDbIntArray& rejectedObjs, bool excludeCrossing = true,
	                                      double tol = NcDbMPolygonCrossingFuzz);
#if !defined(HOST_NO_MFC)
	virtual Nano::ErrorStatus decomposeForSave(NcDb::NcDbDwgVersion ver,NcDbObject*& replaceObj,NcDbObjectId& replaceId,
	                                           NRX::Boolean& exchangeXData);
#endif
public:
	OdDbMPolygon* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcLyLayerFilter
class OdLyLayerFilter;
class NRXDBGATE_EXPORT NcLyLayerFilter : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcLyLayerFilter);

	typedef NcLyLayerFilter  wrapper_class;
	typedef OdLyLayerFilter  native_class;

	enum DialogResult
	{
		kOk         = 0,
		kCancel     = 1,
		kUseDefault = 2
	};

public:
	NcLyLayerFilter();
	NcLyLayerFilter(OdRxObject* _object);

public:
	virtual const NCHAR* name() const;
	virtual Nano::ErrorStatus setName(const NCHAR* strName);
	virtual bool allowRename() const;
	virtual Nano::ErrorStatus getImages(HIMAGELIST& imageList, NRX::UInt32& normalImage,
	                                    NRX::UInt32& selected) const;
	virtual NcLyLayerFilter* parent() const;

	virtual const NcArray< NcLyLayerFilter* >& getNestedFilters() const;
	virtual Nano::ErrorStatus addNested(NcLyLayerFilter* filter);
	virtual Nano::ErrorStatus removeNested(NcLyLayerFilter* filter);
	virtual Nano::ErrorStatus generateNested();

	virtual bool dynamicallyGenerated() const;
	virtual bool allowNested() const;
	virtual bool allowDelete() const;
	virtual bool isProxy() const;
	virtual bool isIdFilter() const;
	virtual bool filter(NcDbLayerTableRecord* layer) const;

	virtual DialogResult showEditor();
	virtual const NCHAR* filterExpression() const;
	virtual Nano::ErrorStatus setFilterExpression(const NCHAR* expr);
	virtual const NcLyBoolExpr* filterExpressionTree() const;

	virtual bool compareTo(const NcLyLayerFilter* pOther) const;

	virtual Nano::ErrorStatus readFrom(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus writeTo(NcDbDxfFiler* filer) const;

public:
	OdLyLayerFilter* native() const;

private:
	mutable NcArray< NcLyLayerFilter* > m_arrFilters;
};

//////////////////////////////////////////////////////////////////////////
// NcLyLayerFilter
class OdLyLayerGroup;
class NRXDBGATE_EXPORT NcLyLayerGroup : public NcLyLayerFilter
{
public:
	NCRX_DECLARE_MEMBERS(NcLyLayerGroup);

	NcLyLayerGroup();
	NcLyLayerGroup(OdRxObject* _object);

public:
	typedef NcLyLayerGroup  wrapper_class;
	typedef OdLyLayerGroup  native_class;

public:
	virtual Nano::ErrorStatus addLayerId(const NcDbObjectId& id);
	virtual Nano::ErrorStatus removeLayerId(const NcDbObjectId& id);
	virtual const NcDbObjectIdArray& layerIds() const;

public:
	OdLyLayerGroup* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcLyLayerFilterManager
class OdLyLayerFilterManager;
class NRXDBGATE_EXPORT NcLyLayerFilterManager : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcLyLayerFilterManager);

	NcLyLayerFilterManager(OdRxObject* _object);

public:
	typedef NcLyLayerFilterManager  wrapper_class;
	typedef OdLyLayerFilterManager  native_class;

public:
	virtual Nano::ErrorStatus getFilters(NcLyLayerFilter*& pRoot, NcLyLayerFilter*& pCurrent);
	virtual Nano::ErrorStatus setFilters(const NcLyLayerFilter* pRoot, const NcLyLayerFilter* pCurrent);

public:
	OdLyLayerFilterManager* native() const;
};

////////////////////////////////////////////////////////////////////////
// nclyGetLayerFilterManager
NRXDBGATE_EXPORT NcLyLayerFilterManager* nclyGetLayerFilterManager(NcDbDatabase* database_);

////////////////////////////////////////////////////////////////////////
// class NcDbEvalVariant
class NRXDBGATE_EXPORT NcDbEvalVariant : public resbuf, public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbEvalVariant);

	enum Type
	{
		kNone    = NcDb::kDxfInvalid,
		kShort   = NcDb::kDxfInt16,
		kLong    = NcDb::kDxfInt32,
		kDouble  = NcDb::kDxfReal,
		kString  = NcDb::kDxfText,
		kOldId   = NcDb::kDxfInt32 + 1,
		kPoint2d = NcDb::kDxfXCoord,
		kPoint3d = NcDb::kDxfXCoord + 1
	};

public:
	NcDbEvalVariant();
	NcDbEvalVariant(const NcDbEvalVariant& source);
	NcDbEvalVariant(const NcDbEvalVariant* source);

	NcDbEvalVariant(const double& value);
	NcDbEvalVariant(short value);
	NcDbEvalVariant(const NCHAR* string);
	NcDbEvalVariant(long value);
	NcDbEvalVariant(const NcDbObjectId& id);
	NcDbEvalVariant(const NcGePoint2d& point);
	NcDbEvalVariant(const NcGePoint3d& point);
	NcDbEvalVariant(const resbuf& rb);

public:
	~NcDbEvalVariant();

public:
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source);

	NcDbEvalVariant& operator=(const NcDbEvalVariant& source);
	NcDbEvalVariant& operator=(const double& value);
	NcDbEvalVariant& operator=(short value);
	NcDbEvalVariant& operator=(const NCHAR* string);
	NcDbEvalVariant& operator=(long value);
	NcDbEvalVariant& operator=(const NcDbObjectId& id);
	NcDbEvalVariant& operator=(const NcGePoint2d& point);
	NcDbEvalVariant& operator=(const NcGePoint3d& point);
	NcDbEvalVariant& operator=(const resbuf& rb);

	bool operator != ( const NcDbEvalVariant& val ) const;
	bool operator < ( const NcDbEvalVariant& val ) const;
	bool operator <= ( const NcDbEvalVariant& val ) const;
	bool operator == ( const NcDbEvalVariant& val ) const;
	bool operator > ( const NcDbEvalVariant& val ) const;
	bool operator >= ( const NcDbEvalVariant& val ) const;

	Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	NcDb::DwgDataType getType() const;

	Nano::ErrorStatus getValue(double& value) const;
	Nano::ErrorStatus getValue(NcDbObjectId& value, NcDbDatabase*pDb = NULL) const;
	Nano::ErrorStatus getValue(NcGePoint2d& value) const;
	Nano::ErrorStatus getValue(NcGePoint3d& value) const;
	Nano::ErrorStatus getValue(NcString& value) const;
	Nano::ErrorStatus getValue(NRX::Int32& value) const;
	Nano::ErrorStatus getValue(short& value) const;

	Nano::ErrorStatus setValue(NcDb::DxfCode groupcode, const double value);
	Nano::ErrorStatus setValue(NcDb::DxfCode groupcode, const NcDbObjectId value);
	Nano::ErrorStatus setValue(NcDb::DxfCode groupcode, const NcGePoint2d& value);
	Nano::ErrorStatus setValue(NcDb::DxfCode groupcode, const NcGePoint3d& value);
	Nano::ErrorStatus setValue(NcDb::DxfCode groupcode, const NcString& value);
	Nano::ErrorStatus setValue(NcDb::DxfCode groupcode, const NRX::Int32 value);
	Nano::ErrorStatus setValue(NcDb::DxfCode groupcode, const short value);

	void clear();

protected:
	void init();

	// Frees memory allocated by current node for strings or arrays
	void free_extra();
};

class NcDbImpDynBlockReferenceProperty;
//////////////////////////////////////////////////////////////////////////
// NcDbDynBlockReferenceProperty
class NRXDBGATE_EXPORT NcDbDynBlockReferenceProperty
{
public:
	enum  UnitsType
	{
		kNoUnits = 0,
		kAngular,
		kDistance,
		kArea
	};

public:
	NcDbDynBlockReferenceProperty();
	NcDbDynBlockReferenceProperty(const NcDbDynBlockReferenceProperty& other);

	virtual ~NcDbDynBlockReferenceProperty();

	NcDbDynBlockReferenceProperty& operator=(const NcDbDynBlockReferenceProperty& other);

	NcDbObjectId blockId() const;
	NcString propertyName() const;
	NcDbEvalVariant::Type propertyType() const;
	bool readOnly() const;
	bool show() const;
	NcString description() const;
	UnitsType unitsType() const;

	Nano::ErrorStatus getAllowedValues(NcDbEvalVariantArray& values);

	NcDbEvalVariant value() const;
	Nano::ErrorStatus setValue(const NcDbEvalVariant& value);
	bool visibleInCurrentVisibilityState() const;

private:

	NcDbImpDynBlockReferenceProperty* m_pImp;
	friend class NcDbImpDynBlockReferenceProperty;
	friend class NcDbImpDynBlockReference;
};

class NcDbImpDynBlockReference;
////////////////////////////////////////////////////////////////////////////
// NcDbDynBlockReference
class NRXDBGATE_EXPORT NcDbDynBlockReference
{
public:
	NcDbDynBlockReference(NcDbObjectId blockRefId);
	NcDbDynBlockReference(NcDbBlockReference* pRef);

	virtual ~NcDbDynBlockReference();

	void getBlockProperties(NcDbDynBlockReferencePropertyArray& properties) const;

	static bool isDynamicBlock(NcDbObjectId blockTableRecordId);
	bool isDynamicBlock() const;

	NcDbObjectId blockId() const;
	Nano::ErrorStatus resetBlock();

	Nano::ErrorStatus convertToStaticBlock();
	Nano::ErrorStatus convertToStaticBlock(const LPCTSTR& newBlockName);

	NcDbObjectId dynamicBlockTableRecord() const;
	NcDbObjectId anonymousBlockTableRecord() const;

private:
	NcDbDynBlockReference();

	NcDbImpDynBlockReference* mpImp;
};

//////////////////////////////////////////////////////////////////////////
// NcDbObjectContext
class OdDbObjectContext;
class NRXDBGATE_EXPORT NcDbObjectContext : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbObjectContext);

	NcDbObjectContext();

	NcDbObjectContext(OdRxObject* _object);

public:
	typedef NcDbObjectContext  wrapper_class;
	typedef OdDbObjectContext  native_class;

public:
	virtual Nano::ErrorStatus getName(NcString& name) const;
	virtual Nano::ErrorStatus setName(const NCHAR* name);
	virtual NRX::LongPtr uniqueIdentifier() const;
	//virtual const NCHAR* collectionName() const;
	virtual NcString collectionName() const;

public:
	OdDbObjectContext* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbObjectContextInterface
class OdDbObjectContextInterface;
class NRXDBGATE_EXPORT NcDbObjectContextInterface : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbObjectContextInterface);

	NcDbObjectContextInterface(OdRxObject* _object);

public:
	typedef OdDbObjectContextInterface  native_class;

public:
	virtual bool supportsCollection(const NcDbObject* object, const NCHAR* collectionName) const;
	virtual bool hasContext(const NcDbObject* object, const NcDbObjectContext& context) const;
	virtual Nano::ErrorStatus addContext(NcDbObject* object, const NcDbObjectContext& context) const;
	virtual Nano::ErrorStatus removeContext(NcDbObject* object, const NcDbObjectContext& context) const;

public:
	OdDbObjectContextInterface* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbObjectContextCollection
class OdDbObjectContextCollection;
class NRXDBGATE_EXPORT NcDbObjectContextCollection : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbObjectContextCollection);

	NcDbObjectContextCollection(OdRxObject* _object);

public:
	typedef NcDbObjectContextCollection  wrapper_class;
	typedef OdDbObjectContextCollection  native_class;

public:
	virtual NcString name() const;
	virtual NcDbObjectContext* currentContext(const NcDbObject* pRequestingObject) const;
	virtual Nano::ErrorStatus setCurrentContext(const NcDbObjectContext* pContext);
	virtual Nano::ErrorStatus addContext(const NcDbObjectContext* pContext);
	virtual Nano::ErrorStatus removeContext(const NCHAR* contextName);
	virtual NcDbObjectContext* getContext(const NCHAR* contextName) const;
	virtual bool hasContext(const NCHAR* contextName) const;
	virtual NcDbObjectContextCollectionIterator* newIterator() const;

	virtual Nano::ErrorStatus   lockContext(const NcDbObjectContext* pContext);
	virtual bool locked() const;
	virtual Nano::ErrorStatus unlockContext();

public:
	OdDbObjectContextCollection* native() const;

	//private:
	//    mutable OdString m_strName;
};

//////////////////////////////////////////////////////////////////////////
// NcDbObjectContextManager
class OdDbObjectContextManager;
class NRXDBGATE_EXPORT NcDbObjectContextManager : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbObjectContextManager);

	NcDbObjectContextManager(OdRxObject* _object);
	//virtual ~NcDbObjectContextManager();

public:
	typedef NcDbObjectContextManager  wrapper_class;
	typedef OdDbObjectContextManager  native_class;

public:
	Nano::ErrorStatus registerContextCollection(const NCHAR* collectionName, NcDbObjectContextCollection* pCollection);
	Nano::ErrorStatus unregisterContextCollection(const NCHAR* collectionName);
	NcDbObjectContextCollection* const contextCollection(const NCHAR* collectionName) const;

public:
	OdDbObjectContextManager* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAnnotativeObjectPE
class OdDbAnnotativeObjectPE;
class NRXDBGATE_EXPORT NcDbAnnotativeObjectPE : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbAnnotativeObjectPE);

	NcDbAnnotativeObjectPE(OdRxObject* _object);

public:
	typedef OdDbAnnotativeObjectPE  native_class;

public:
	virtual bool annotative(NcDbObject* object) const;
	virtual Nano::ErrorStatus setAnnotative(NcDbObject* object, const bool bAnnotative);
	virtual Nano::ErrorStatus setFromStyle(NcDbObject* object, bool& bUpdated);
	virtual bool forceAnnoAllVisible(NcDbObject* pObj) const;
	virtual Nano::ErrorStatus setForceAnnoAllVisible(NcDbObject* pObj, bool bForce) const;
	virtual Nano::ErrorStatus resetScaleDependentProperties(NcDbObject* object);

public:
	OdDbAnnotativeObjectPE* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbRasterImageDef
class OdDbRasterImageDef;
class NRXDBGATE_EXPORT NcDbRasterImageDef : public NcDbObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbRasterImageDef);

	typedef NcDbRasterImageDef  wrapper_class;
	typedef OdDbRasterImageDef  native_class;

public:
	NcDbRasterImageDef();
	NcDbRasterImageDef(OdRxObject* _object);

public:
	virtual ~NcDbRasterImageDef() {}

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subErase(NRX::Boolean erasing) override;
	virtual Nano::ErrorStatus subHandOverTo(NcDbObject* newObject) override;

public:
	RasterImageDefImp* ptrImp() const;
	RasterImageDefImp* setPtrImp(RasterImageDefImp* pImp);

public:
	virtual NcGiSentScanLines* makeScanLines(const NcGiRequestScanLines* pReq, const NcGeMatrix2d& pixToScreen,
	                                         NcGePoint2dArray* pActiveClipBndy = 0,
	                                         NRX::Boolean draftQuality = false,
	                                         NRX::Boolean isTransparent = false,
	                                         const double brightness = 50.0, const double contrast = 50.0,
	                                         const double fade = 0.0) const;

	virtual Nano::ErrorStatus setSourceFileName(const NCHAR* path);
	virtual Nano::ErrorStatus setActiveFileName(const NCHAR* path);
	virtual const NCHAR* searchForActivePath();

	virtual const NCHAR* sourceFileName() const;
	virtual const NCHAR* activeFileName() const;

	virtual Nano::ErrorStatus embed();
	virtual NRX::Boolean isEmbedded() const;

	virtual Nano::ErrorStatus load();
	virtual Nano::ErrorStatus unload(NRX::Boolean modifyDatabase = true);
	virtual NRX::Boolean isLoaded() const;

	virtual NcGeVector2d size() const;

	virtual NcGiImageOrg organization() const;
	virtual int colorDepth() const;

	virtual const NCHAR* fileType() const;
	virtual int entityCount(NRX::Boolean* pbLocked = 0) const;
	virtual void updateEntities() const;

	enum Units
	{
		kNone         = 0,
		kMillimeter   = 1,
		kCentimeter   = 2,
		kMeter        = 3,
		kKilometer    = 4,
		kInch         = 5,
		kFoot         = 6,
		kYard         = 7,
		kMile         = 8,
		kMicroinches  = 9,
		kMils         = 10,
		kAngstroms    = 11,
		kNanometers   = 12,
		kMicrons      = 13,
		kDecimeters   = 14,
		kDekameters   = 15,
		kHectometers  = 16,
		kGigameters   = 17,
		kAstronomical = 18,
		kLightYears   = 19,
		kParsecs      = 20
	};

	virtual Nano::ErrorStatus setResolutionMMPerPixel(const NcGeVector2d& resMMPerPixel);
	virtual NcGeVector2d resolutionMMPerPixel() const;
	virtual void setResolutionUnits(NcDbRasterImageDef::Units units);
	virtual Units resolutionUnits() const;

	virtual Nano::ErrorStatus loadThumbnail(NRX::UInt16& maxWidth, NRX::UInt16& maxHeight,
	                                        NRX::UInt8* pPalette = 0, int nPaletteEntries = 0);
	virtual Nano::ErrorStatus unloadThumbnail();
	virtual void* createThumbnailBitmap(BITMAPINFO*& pBitmapInfo, NRX::UInt8 brightness = 50,
	                                    NRX::UInt8 contrast = 50, NRX::UInt8 fade = 0);

	virtual Ntil::Image* imageCopy(NRX::Boolean bForceImageLoad = true) const;
	virtual Ntil::FileReadDescriptor* fileDescCopy() const;

	virtual Nano::ErrorStatus openImage(Ntil::Image*& pImage);

	virtual Nano::ErrorStatus closeImage();

	virtual Nano::ErrorStatus setImage(const Ntil::Image* pImage, const Ntil::FileReadDescriptor* pFileDesc,
	                                   NRX::Boolean modifyDatabase = true);

	virtual Nano::ErrorStatus setUndoStoreSize(unsigned int maxImages = 10);
	virtual unsigned int undoStoreSize() const;

	virtual NRX::Boolean imageModified() const;
	virtual Nano::ErrorStatus setImageModified(NRX::Boolean modified);

	virtual INcReadStream* getReadStream();

	Nano::ErrorStatus forceImageFileClosed(NRX::Boolean modifyDatabase);

	static Nano::ErrorStatus createImageDictionary(NcDbDatabase* pDb, NcDbObjectId& dictId);
	static NcDbObjectId imageDictionary(NcDbDatabase* pDb);

	enum { kMaxSuggestNameSize = 2049 };

	/* __declspec(deprecated) */ static Nano::ErrorStatus suggestName(NcDbDictionary* pImageDictionary,
	                                                                  const NCHAR* pNewImagePathName,
	                                                                  NCHAR* newImageName);

	static Nano::ErrorStatus suggestName(NcDbDictionary* dictionary, const NCHAR* path, NCHAR* name, size_t size);

	static ClassVersion classVersion();
	virtual Nano::ErrorStatus subClose();


public:
	OdDbRasterImageDef* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbImage
class OdDbImage;
class NRXDBGATE_EXPORT NcDbImage : public NcDbEntity
{
public:
	NCRX_DECLARE_MEMBERS(NcDbImage);

	typedef NcDbImage  wrapper_class;
	typedef OdDbImage  native_class;

public:
	NcDbImage();
	NcDbImage(OdRxObject* _object);

	virtual NRX::Boolean freeScanLines(NcGiSentScanLines*) const;
	virtual NcGiSentScanLines* getScanLines(const NcGiRequestScanLines&) const;

public:
	OdDbImage* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbRasterImage
class OdDbRasterImage;
class NRXDBGATE_EXPORT NcDbRasterImage : public NcDbImage
{
public:
	NCRX_DECLARE_MEMBERS(NcDbRasterImage);

	typedef NcDbRasterImage  wrapper_class;
	typedef OdDbRasterImage  native_class;

public:
	NcDbRasterImage();
	NcDbRasterImage(OdRxObject* _object);

	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) ; // +Overload
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) ; // +Overload
	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) ; // +Overload
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) ; // +Overload
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; // +Overload

public:
	virtual ~NcDbRasterImage() {}

public:
	virtual NcGiSentScanLines* getScanLines(const NcGiRequestScanLines& req) const;
	virtual NRX::Boolean freeScanLines(NcGiSentScanLines* pSSL) const;
	virtual Nano::ErrorStatus setImageDefId(NcDbObjectId imageId);
	virtual NcDbObjectId imageDefId() const;
	virtual void setReactorId(NcDbObjectId reactorId);
	virtual NcDbObjectId reactorId() const;
	virtual NRX::Boolean setOrientation(const NcGePoint3d& origin, const NcGeVector3d& uCorner,
	                                    const NcGeVector3d& vOnPlane);
	virtual void getOrientation(NcGePoint3d& origin, NcGeVector3d& u, NcGeVector3d& v) const;
	virtual NcGeVector2d scale() const;
	virtual NcGeVector2d imageSize(NRX::Boolean bGetCachedValue = NRX::kFalse) const;

	enum ClipBoundaryType
	{
		kInvalid,
		kRect,
		kPoly
	};

	virtual Nano::ErrorStatus setClipBoundaryToWholeImage(NcGeVector2d& size = NcGeVector2d(0, 0));
	virtual Nano::ErrorStatus setClipBoundary(ClipBoundaryType type, const NcGePoint2dArray& points);
	virtual const NcGePoint2dArray& clipBoundary() const;
	virtual ClipBoundaryType clipBoundaryType() const;
	virtual Nano::ErrorStatus getVertices(NcGePoint3dArray& verts) const;
	virtual Nano::ErrorStatus getPixelToModelTransform(NcGeMatrix3d& mtx) const;

	enum ImageDisplayOpt
	{
		kShow          = 1,
		kShowUnAligned = 2,
		kClip          = 4,
		kTransparent   = 8
	};

	virtual void setDisplayOpt(ImageDisplayOpt option, NRX::Boolean bValue);
	virtual NRX::Boolean isSetDisplayOpt(ImageDisplayOpt option) const;
	virtual Nano::ErrorStatus setBrightness(NRX::Int8 value);
	virtual NRX::Int8 brightness() const;
	virtual Nano::ErrorStatus setContrast(NRX::Int8 value);
	virtual NRX::Int8 contrast() const;
	virtual Nano::ErrorStatus setFade(NRX::Int8 value);
	virtual NRX::Int8 fade() const;
	NRX::Boolean isClipped() const;

	        void                baseList() const;
	virtual bool                castShadows() const;


	static ClassVersion         classVersion();
	virtual Nano::ErrorStatus   dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus   dxfOutFields(NcDbDxfFiler* filer) const;
	virtual NRX::Boolean      isClipInverted() const;
	RasterImageImp*             ptrImp() const;
	virtual bool                receiveShadows() const;
	virtual void                saveAs(NcGiWorldDraw* mode,NcDb::SaveType st);
	virtual void                setCastShadows(bool newVal);
	virtual void                setClipInverted(NRX::Boolean newVal);
	RasterImageImp*             setPtrImp(RasterImageImp* pImp);
	virtual void                setReceiveShadows(bool newVal);

	virtual Nano::ErrorStatus   subExplode(NcDbVoidPtrArray& entitySet) const;
	virtual Nano::ErrorStatus   subGetClassID(CLSID* pClsid) const;
	virtual Nano::ErrorStatus   subGetGeomExtents(NcDbExtents& extents) const;
	virtual Nano::ErrorStatus subGetGripPoints(NcDbGripDataPtrArray& grips,
	                                           const double curViewUnitSize,
	                                           const int gripSize,
	                                           const NcGeVector3d& curViewDir,
	                                           const int bitflags
	                                           ) const;
	virtual Nano::ErrorStatus   subGetGsMarkersAtSubentPath(
	                                const NcDbFullSubentPath& subPath,NcArray<NRX::GsMarker>& gsMarkers
	                            ) const;
	virtual Nano::ErrorStatus   subGetOsnapPoints(NcDb::OsnapMode     osnapMode,
	                                              NRX::GsMarker     gsSelectionMark,
	                                              const NcGePoint3d&  pickPoint,
	                                              const NcGePoint3d&  lastPoint,
	                                              const NcGeMatrix3d& viewXform,NcGePoint3dArray&   snapPoints,NcDbIntArray &   geomIds
	                                              ) const;
	virtual Nano::ErrorStatus   subGetStretchPoints(NcGePoint3dArray&  stretchPoints
	                            ) const;

	virtual Nano::ErrorStatus   subGetSubentPathsAtGsMarker(NcDb::SubentType      type,
	                                                        NRX::GsMarker       gsMark,
	                                                        const NcGePoint3d&    pickPoint,
	                                                        const NcGeMatrix3d&   viewXform,
	                                                        int&                  numPaths,NcDbFullSubentPath*&  subentPaths,
	                                                        int                   numInserts = 0,NcDbObjectId*         entAndInsertStack = 0
	                                                        ) const;
	virtual Nano::ErrorStatus   subGetTransformedCopy(
	                                const NcGeMatrix3d& xform,NcDbEntity*& ent
	                            ) const;
	virtual Nano::ErrorStatus   subIntersectWith(
	                                const NcDbEntity*   ent,NcDb::Intersect     intType,NcGePoint3dArray&   points,
	                                NRX::GsMarker     thisGsMarker  = 0,
	                                NRX::GsMarker     otherGsMarker = 0
	                            ) const;
	virtual void                subList() const;
	virtual Nano::ErrorStatus   subMoveGripPointsAt(
	                                    const NcDbVoidPtrArray& gripAppData,
	                                    const NcGeVector3d& offset, 
	                                    const int bitflags);
	virtual Nano::ErrorStatus   subMoveStretchPointsAt(
	                                    const NcDbIntArray& indices,
	                                    const NcGeVector3d& offset
	                            );
	virtual NcDbEntity*         subSubentPtr(const NcDbFullSubentPath& id) const;
	virtual Nano::ErrorStatus   subSwapIdWith(NcDbObjectId otherId,
	                                          NRX::Boolean swapXdata = NRX::kFalse,
	                                          NRX::Boolean swapExtDict = NRX::kFalse
	                                          );

public:
	OdDbRasterImage* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbWipeout
class OdDbWipeout;
class NRXDBGATE_EXPORT NcDbWipeout : public NcDbRasterImage
{
public:
	NCRX_DECLARE_MEMBERS(NcDbWipeout);

	typedef NcDbWipeout  wrapper_class;
	typedef OdDbWipeout  native_class;

public:
	NcDbWipeout();
	NcDbWipeout(OdRxObject* _object);

	virtual Nano::ErrorStatus setClipBoundary(ClipBoundaryType type, const NcGePoint2dArray& points);

	static Nano::ErrorStatus fitPointsToImage(NcGePoint2dArray& pointArray, NcGePoint2d& minPoint, double& scale,
	                                          NRX::Boolean bFlipY = NRX::kFalse);

	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) ; //+Overload
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload

	Nano::ErrorStatus           append(NcDbObjectId& id);
	static Nano::ErrorStatus    createImageDefinition();
	NRX::Boolean              frame() const;
	NRX::Boolean              setFrame(NRX::Boolean bFrame);

public:
	OdDbWipeout* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbBlockBegin
class OdDbBlockBegin;
class NRXDBGATE_EXPORT NcDbBlockBegin : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbBlockBegin);

public:
	typedef NcDbBlockBegin  wrapper_class;
	typedef OdDbBlockBegin  native_class;

public:
	NcDbBlockBegin();

	NcDbBlockBegin(OdRxObject* _object);

public:
	OdDbBlockBegin* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbBlockEnd
class OdDbBlockEnd;
class NRXDBGATE_EXPORT NcDbBlockEnd : public NcDbEntity
{
public:
	NCRX_DECLARE_MEMBERS(NcDbBlockEnd);

	typedef NcDbBlockEnd  wrapper_class;
	typedef OdDbBlockEnd  native_class;

public:
	NcDbBlockEnd();

	NcDbBlockEnd(OdRxObject* _object);

public:
	OdDbBlockEnd* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbProxyObject
class OdDbProxyObject;
class NRXDBGATE_EXPORT NcDbProxyObject : public NcDbObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbProxyObject);

	typedef NcDbProxyObject  wrapper_class;
	typedef OdDbProxyObject  native_class;

public:
	NcDbProxyObject(OdRxObject* _object);

public:
	virtual int proxyFlags() const;
	virtual const NCHAR* originalClassName() const;
	virtual const NCHAR* originalDxfName() const;
	virtual const NCHAR* applicationDescription() const;
	virtual Nano::ErrorStatus getReferences(NcDbObjectIdArray&, NcDbIntArray&) const;

	virtual NcDb::DuplicateRecordCloning mergeStyle() const;

	enum
	{
		kNoOperation          = 0,
		kEraseAllowed         = 0x01,
		kCloningAllowed       = 0x80,
		kAllButCloningAllowed = 0x01,
		kAllAllowedBits       = 0x81,
		kMergeIgnore          = 0, // Keep existing (= default)
		kMergeReplace         = 0x100, // Use clone
		kMergeMangleName      = 0x200, // anonymous name
		kDisableProxyWarning  = 0x400
	};

public:
	OdDbProxyObject* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbProxyEntity
class OdDbProxyEntity;
class NRXDBGATE_EXPORT NcDbProxyEntity : public NcDbEntity
{
public:
	NCRX_DECLARE_MEMBERS(NcDbProxyEntity);

	typedef NcDbProxyEntity  wrapper_class;
	typedef OdDbProxyEntity  native_class;

public:
	NcDbProxyEntity(OdRxObject* _object);

public:
	virtual int proxyFlags() const;
	virtual const NCHAR* originalClassName() const;
	virtual const NCHAR* originalDxfName() const;
	virtual const NCHAR* applicationDescription() const;
	virtual Nano::ErrorStatus getReferences(NcDbObjectIdArray&, NcDbIntArray&) const;

	enum GraphicsMetafileType
	{
		kNoMetafile   = 0,
		kBoundingBox  = 1,
		kFullGraphics = 2
	};

	virtual NcDbProxyEntity::GraphicsMetafileType graphicsMetafileType() const;

	enum
	{
		kNoOperation                = 0,
		kEraseAllowed               = 0x1,
		kTransformAllowed           = 0x2,
		kColorChangeAllowed         = 0x4,
		kLayerChangeAllowed         = 0x8,
		kLinetypeChangeAllowed      = 0x10,
		kLinetypeScaleChangeAllowed = 0x20,
		kVisibilityChangeAllowed    = 0x40,
		kCloningAllowed             = 0x80,
		kLineWeightChangeAllowed    = 0x100,
		kPlotStyleNameChangeAllowed = 0x200,
		kAllButCloningAllowed       = 0x37F,
		kAllAllowedBits             = 0xBFF,
		kDisableProxyWarning        = 0x400,
		kMaterialChangeAllowed      = 0x800,
	};

public:
	OdDbProxyEntity* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbPlaceHolder
class OdDbPlaceHolder;
class NRXDBGATE_EXPORT NcDbPlaceHolder : public NcDbObject
{
	NCDB_DECLARE_MEMBERS(NcDbPlaceHolder);

public:
	typedef NcDbPlaceHolder  wrapper_class;
	typedef OdDbPlaceHolder  native_class;

public:
	NcDbPlaceHolder();

	NcDbPlaceHolder(OdRxObject* _object);

	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

public:
	OdDbPlaceHolder* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbMlineStyle
class OdDbMlineStyle;
class NRXDBGATE_EXPORT NcDbMlineStyle : public NcDbObject
{
	NCDB_DECLARE_MEMBERS(NcDbMlineStyle);

public:
	typedef NcDbMlineStyle  wrapper_class;
	typedef OdDbMlineStyle  native_class;

public:
	NcDbMlineStyle();

	NcDbMlineStyle(OdRxObject* _object);

	// NcRxObject
public:
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* source) override;

	// NcDbObject
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus subErase(NRX::Boolean erase = NRX::kTrue) override;

public:
	void initMlineStyle();
	void set(const NcDbMlineStyle& source, bool checkIfReferenced = true);

	Nano::ErrorStatus setDescription(const NCHAR* description);
	const NCHAR* description() const;

	Nano::ErrorStatus setName(const NCHAR* name);
	const NCHAR* name() const;

	void setShowMiters(bool showThem);
	bool showMiters() const;

	void setStartSquareCap(bool showIt);
	bool startSquareCap() const;

	void setStartRoundCap(bool showIt);
	bool startRoundCap() const;

	void setStartInnerArcs(bool showThem);
	bool startInnerArcs() const;

	void setEndSquareCap(bool showIt);
	bool endSquareCap() const;

	void setEndRoundCap(bool showIt);
	bool endRoundCap() const;

	void setEndInnerArcs(bool showThem);
	bool endInnerArcs() const;

	Nano::ErrorStatus setFillColor(const NcCmColor& color);
	const NcCmColor& fillColor() const;

	void setFilled(bool onOff);
	bool filled() const;

	Nano::ErrorStatus setStartAngle(double ang);
	double startAngle() const;

	Nano::ErrorStatus setEndAngle(double ang);
	double endAngle() const;

	Nano::ErrorStatus addElement(int& index, double offset, const NcCmColor& color, NcDbObjectId linetype,
	                             bool checkIfReferenced = true);
	Nano::ErrorStatus removeElementAt(int elem);

	int numElements() const;

	Nano::ErrorStatus setElement(int& elem, double offset, const NcCmColor& color, NcDbObjectId linetype);

	Nano::ErrorStatus getElementAt(int elem, double& offset, NcCmColor& color, NcDbObjectId& linetype) const;

public:
	OdDbMlineStyle* native() const;

protected:
	NcCmColor m_fill_color;
};

//////////////////////////////////////////////////////////////////////////
// NcDbGeomRef
class NRXDBGATE_EXPORT NcDbGeomRef : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbGeomRef);
	virtual ~NcDbGeomRef() {}
	virtual void reset() = NULL;
	virtual bool isValid() const = NULL;
	virtual bool isEmpty() const = NULL;
};

//////////////////////////////////////////////////////////////////////////
// NcDbCompoundObjectId
class NRXDBGATE_EXPORT NcDbCompoundObjectId : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbCompoundObjectId);
	NcDbCompoundObjectId();
	NcDbCompoundObjectId(const NcDbObjectId& id, NcDbDatabase* pHostDatabase = NULL);
	NcDbCompoundObjectId(const NcDbCompoundObjectId&);
	NcDbCompoundObjectId(const NcDbObjectId& id, const NcDbObjectIdArray& path, NcDbDatabase* pHostDatabase = NULL);
	virtual ~NcDbCompoundObjectId();
	NcDbCompoundObjectId& operator =(const NcDbObjectId&);
	NcDbCompoundObjectId& operator =(const NcDbCompoundObjectId&);
	bool operator ==(const NcDbCompoundObjectId&) const;
	bool operator !=(const NcDbCompoundObjectId& other) const { return !(*this == other); }
	NcDbObjectId topId() const;
	NcDbObjectId leafId() const;
	Nano::ErrorStatus getFullPath(NcDbObjectIdArray& fullPath) const;
	Nano::ErrorStatus getPath(NcDbObjectIdArray& path) const;
	void setEmpty();
	Nano::ErrorStatus set(const NcDbObjectId&, NcDbDatabase* pHostDatabase = NULL);
	Nano::ErrorStatus set(const NcDbCompoundObjectId&, NcDbDatabase* pHostDatabase = NULL);
	Nano::ErrorStatus set(const NcDbObjectId& id, const NcDbObjectIdArray& path, NcDbDatabase* pHostDatabase = NULL);
	Nano::ErrorStatus setFullPath(const NcDbObjectIdArray& fullPath, NcDbDatabase* pHostDatabase = NULL);
	bool isEmpty() const;
	bool isValid(int validityCheckingLevel = 1) const;
	bool isExternal() const;
	bool isSimpleObjectId() const;
	enum Status
	{
		kValid                      = 0,
		kWasLoadedNowUnloaded       = 1,
		kCouldNotResolveNonTerminal = 2,
		kCouldNotResolveTerminal    = 3,
		kCouldNotResolveTooEarly    = 4,
		kIncompatibleIdType         = 1000,
	};
	Status status() const;
	Nano::ErrorStatus getTransform(NcGeMatrix3d& trans) const;
	bool remap(const NcDbIdMapping& idMap);
	Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler, NcDbDatabase* pHostDatabase) const;
	Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler, int ownerVersion);
	Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler, NcDbDatabase* pHostDatabase) const;
	Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler, NcDbDatabase* pHostDatabase, int ownerVersion);
	static const NcDbCompoundObjectId& nullId();
};

//////////////////////////////////////////////////////////////////////////
// NcDbSubentRef
class NRXDBGATE_EXPORT NcDbSubentRef : public NcDbGeomRef {
public:
	NCRX_DECLARE_MEMBERS(NcDbSubentRef);
	NcDbSubentRef() {}
	NcDbSubentRef(const NcDbCompoundObjectId&, const NcDbSubentId& = kNullSubentId);
	NcDbSubentRef& operator =(const NcDbSubentRef&);
	virtual Nano::ErrorStatus copyFrom(const NcRxObject*);
	virtual void reset();
	virtual bool isEmpty() const { return mEntityId.isEmpty(); }
	const NcDbCompoundObjectId& entity() const { return mEntityId; }
	NcDbSubentId subentId() const { return mSubentId; }
	bool hasEntity() const { return !mEntityId.isEmpty(); }
	bool hasSubent() const { return mSubentId != kNullSubentId; }
	NcDbEntity* createEntity() const;
protected:
	void setEntity(const NcDbCompoundObjectId& entityId) { mEntityId = entityId; }
	void setSubent(const NcDbSubentId& subentId) { mSubentId = subentId; }
	void setFromSubentPath(const NcDbFullSubentPath&);
private:
	NcDbCompoundObjectId mEntityId;
	NcDbSubentId         mSubentId;
};

//////////////////////////////////////////////////////////////////////////
// NcDbFaceRef
class NRXDBGATE_EXPORT NcDbFaceRef : public NcDbSubentRef {
public:
	NCRX_DECLARE_MEMBERS(NcDbFaceRef);
	NcDbFaceRef();
	NcDbFaceRef(const NcDbFaceRef&);
	virtual ~NcDbFaceRef();
	NcDbFaceRef(const NcDbCompoundObjectId&, const NcDbSubentId& = kNullSubentId, class BODY* = NULL);
	NcDbFaceRef& operator =(const NcDbFaceRef&);
	virtual Nano::ErrorStatus copyFrom(const NcRxObject*);
	virtual void reset();
	virtual bool isValid() const;
	virtual bool isEmpty() const { return __super::isEmpty() && mpAsmBody == NULL; }
	class BODY* asmBody() const { return mpAsmBody; }
	NcDbEntity* createEntity() const;
private:
	class BODY* mpAsmBody;
};

//////////////////////////////////////////////////////////////////////////
// NcDbEdgeRef
class NRXDBGATE_EXPORT NcDbEdgeRef : public NcDbSubentRef {
public:
	NCRX_DECLARE_MEMBERS(NcDbEdgeRef);
	NcDbEdgeRef();
	NcDbEdgeRef(const NcDbEdgeRef&);
	virtual ~NcDbEdgeRef();
	NcDbEdgeRef(const NcDbCompoundObjectId&,
	            const NcDbSubentId& edgeSubentId = kNullSubentId,
	            const NcDbSubentId& faceSubentId = kNullSubentId,
	            const NcGeCurve3d* pCurve        = NULL);
	NcDbEdgeRef(const NcDbFullSubentPath&);
	NcDbEdgeRef(const NcDbEntity* pEntity);
	NcDbEdgeRef(const NcGeCurve3d* pGeCurve);
	NcDbEdgeRef& operator =(const NcDbEdgeRef&);
	virtual Nano::ErrorStatus copyFrom(const NcRxObject*);
	virtual void reset();
	virtual bool isValid() const;
	virtual bool isEmpty() const { return __super::isEmpty() && mpCurve == NULL; }
	void setFaceSubentity(const NcDbSubentId& faceSubentId);
	NcDbSubentId faceSubentId() const { return mFaceSubentId; }
	const NcGeCurve3d* curve() const { return mpCurve; }
	NcDbEntity* createEntity() const;
private:
	NcDbSubentId mFaceSubentId;
	NcGeCurve3d* mpCurve;
};

//////////////////////////////////////////////////////////////////////////
// NcDbPathRef
class NRXDBGATE_EXPORT NcDbPathRef : public NcDbGeomRef {
public:
	NCRX_DECLARE_MEMBERS(NcDbPathRef);
	NcDbPathRef();
	NcDbPathRef(const NcDbPathRef&);
	NcDbPathRef(const NcArray<NcDbEdgeRef> &edges);
	NcDbPathRef(const NcDbFullSubentPathArray& edgeSubentPathArr,
	            const NcDbFullSubentPathArray& faceSubentPathArr );
	virtual ~NcDbPathRef();
	virtual Nano::ErrorStatus copyFrom(const NcRxObject*);
	virtual void reset();
	virtual bool isValid() const;
	virtual bool isEmpty() const;
	void setEdgeRefs(const NcArray<NcDbEdgeRef>& edges);
	void getEntityArray(NcArray<NcDbEntity*>& entities, bool concatenate);
	const NcArray<NcDbEdgeRef>& edgeRefs() const { return mEdgeRefs; }
	bool isEqualTo(const NcGeCurve3d*);
	bool isReferencePath();
private:
	NcArray<NcDbEdgeRef> mEdgeRefs;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSurface
class OdDbSurface;
class NRXDBGATE_EXPORT NcDbSurface : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbSurface);

public:
	typedef NcDbSurface  wrapper_class;
	typedef OdDbSurface  native_class;

	enum WireframeType {
		kIsolines = 0,
		kIsoparms = 1
	};

	enum EdgeExtensionType {
		kExtendEdge  = 0x000,
		kStretchEdge = 0x001,
	};

public:
	NcDbSurface();
	NcDbSurface(OdRxObject* _object);

	virtual Nano::ErrorStatus setSubentMaterialMapper(const NcDbSubentId& subentId, const NcGiMapper& mapper) ; // +Overload
	virtual Nano::ErrorStatus setSubentColor(const NcDbSubentId& subentId, const NcCmColor& color) ; // +Overload
	virtual Nano::ErrorStatus setBody(const void* modelerBody) ; // +Overload
	virtual void* internalSubentPtr(const NcDbSubentId& id) const; // +Overload
	virtual NcDbSubentId internalSubentId(void* ent) const; // +Overload
	virtual Nano::ErrorStatus getSubentMaterialMapper(const NcDbSubentId& subentId, NcGiMapper& mapper) const; // +Overload
	virtual Nano::ErrorStatus getSubentMaterial(const NcDbSubentId& subentId, NcDbObjectId& matId) const; // +Overload
	virtual Nano::ErrorStatus getSubentColor(const NcDbSubentId& subentId, NcCmColor& color) const; // +Overload
	virtual Nano::ErrorStatus getArea(double& area) const; // +Overload
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) ; // +Overload
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; // +Overload
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;
	virtual void* body() const; // +Overload
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) ; //+Overload
	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) ; //+Overload
	virtual NRX::Boolean isNull() const; //+Overload

public:
	static Nano::ErrorStatus createFrom(const NcDbEntity* entity, NcDbSurface*& surface);

	virtual Nano::ErrorStatus booleanIntersect(const NcDbSurface* pSurface2,NcArray<NcDbEntity*>& intersectionEntities);
	virtual Nano::ErrorStatus booleanSubtract(const NcDbSurface* pSurface2,NcDbSurface*& pNewSurface);
	virtual Nano::ErrorStatus booleanUnion(const NcDbSurface* pSurface2,NcDbSurface*& pNewSurface);
	virtual Nano::ErrorStatus chamferEdges(
	    const NcArray<NcDbSubentId *> &edgeSubentIds,
	    const NcDbSubentId& baseFaceSubentId, 
	    double baseDist, double otherDist);
	Nano::ErrorStatus convertToNurbSurface(NcDbNurbSurfaceArray& nsArray);
	virtual Nano::ErrorStatus convertToRegion ( NcArray<NcDbEntity*>& regions );
	static Nano::ErrorStatus createBlendSurface ( NcDbLoftProfile* startProfile,NcDbLoftProfile* endProfile,NcDbBlendOptions* blendOptions,NcDbSurface*& blendSurface);
	static Nano::ErrorStatus createExtendSurface ( NcDbObjectId sourceSurface, 
	                                               const NcArray<NcDbSubentId>& edges,  
	                                               double extDist, 
	                                               EdgeExtensionType extOption, 
	                                               bool  bAssociativeEnabled,NcDbObjectId& newExtendSurfaceId );
	static Nano::ErrorStatus createExtrudedSurface ( NcDb3dProfile *pSweep,
	                                                const NcGeVector3d& directionVec,NcDbSweepOptions& sweepOptions,NcDbExtrudedSurface*& newExtrudedSurface );
	static Nano::ErrorStatus createFilletSurface ( const NcDbObjectId& surfId1,
	                                              const NcGePoint3d& pickPt1,
	                                              const NcDbObjectId& surfId2,
	                                              const NcGePoint3d& pickPt2,
	                                              double radius,NcDb::FilletTrimMode trimMode,
	                                              const NcGeVector3d& projDir,NcDbSurface*& filletSurface);
	virtual Nano::ErrorStatus createInterferenceObjects(NcArray<NcDbEntity*>& interferenceObjects,NcDbEntity* pEntity, unsigned int flags ) const;
	static Nano::ErrorStatus createLoftedSurface ( const NcArray<NcDbLoftProfile*>& crossSections,
	                                              const NcArray<NcDbLoftProfile*>& guides,NcDbLoftProfile *pPath,NcDbLoftOptions& loftOptions,NcDbSurface*& newSurface );
	static Nano::ErrorStatus createNetworkSurface ( const NcArray<NcDb3dProfile*>& uProfiles,
	                                               const NcArray<NcDb3dProfile*>& vProfiles,NcDbSurface*& newSurface);
	static Nano::ErrorStatus createOffsetSurface ( NcDbEntity* pInputSurface,
	                                              double offsetDistance,NcDbEntity*& offsetSurface);
	static Nano::ErrorStatus createPatchSurface ( const NcDbPathRef& pathRef,
	                                             const NcDbObjectIdArray& constraintIds,
	                                             int continuity,
	                                             double bulge,NcDbSurface*& newSurface);
	static Nano::ErrorStatus createRevolvedSurface ( NcDb3dProfile *pRev,
	                                                const NcGePoint3d& axisPnt,
	                                                const NcGeVector3d& axisDir,
	                                                double revAngle, double startAngle,NcDbRevolveOptions& revolveOptions,NcDbRevolvedSurface*& newRevolvedSurface );
	virtual Nano::ErrorStatus createSectionObjects(const NcGePlane& sectionPlane,NcArray<NcDbEntity*>& sectionObjects) const;
	static Nano::ErrorStatus createSweptSurface ( NcDb3dProfile *pSweep,NcDb3dProfile *pPath,NcDbSweepOptions& sweepOptions,NcDbSweptSurface*& newSweptSurface);
	NcDbObjectId creationActionBodyId() const;
	Nano::ErrorStatus extendEdges(NcDbFullSubentPathArray& edges,
	                              double extDist, EdgeExtensionType extOption, bool  bAssociativeEnabled);
	virtual Nano::ErrorStatus filletEdges(
	    const NcArray<NcDbSubentId *> &edgeSubentIds,
	    const NcGeDoubleArray& radius, 
	    const NcGeDoubleArray& startSetback, 
	    const NcGeDoubleArray& endSetback);
	Nano::ErrorStatus getPerimeter(double& perimeter) const;
	WireframeType getWireframeType() const;
	virtual Nano::ErrorStatus imprintEntity(const NcDbEntity* pEntity);
	Nano::ErrorStatus modificationActionBodyIds(NcDbObjectIdArray& modificationActionBodyIds) const;

	Nano::ErrorStatus projectOnToSurface(const NcDbEntity* pEntityToProject,
	                                     const NcGeVector3d& projectionDirection,NcArray<NcDbEntity*>& projectedEntities) const;
	Nano::ErrorStatus rayTest(const NcGePoint3d& rayBasePoint, const NcGeVector3d& rayDir,
	                          double rayRadius,NcArray<NcDbSubentId>& subEntIds,NcGeDoubleArray& parameters) const;
	virtual Nano::ErrorStatus setSubentMaterial(const NcDbSubentId& subentId,
	                                            const NcDbObjectId& matId);
	virtual Nano::ErrorStatus   setUIsolineDensity(NRX::UInt16 numIsolines);
	virtual Nano::ErrorStatus   setVIsolineDensity(NRX::UInt16 numIsolines);
	Nano::ErrorStatus   setWireframeType(WireframeType type);
	virtual Nano::ErrorStatus sliceByPlane(const NcGePlane& slicePlane,NcDbSurface*& pNegHalfSurface,NcDbSurface*& pNewSurface);
	virtual Nano::ErrorStatus sliceBySurface(
	    const NcDbSurface* pSlicingSurface,NcDbSurface*& pNegHalfSurface,NcDbSurface*& pNewSurface);


	//virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
	virtual Nano::ErrorStatus thicken(double thickness,
	                                  bool bBothSides,NcDb3dSolid*& pSolid) const;
	static Nano::ErrorStatus trimSurface( const NcDbObjectId &blankSurfaceId, 
	                                      const NcDbObjectIdArray &toolIds,
	                                      const NcDbObjectIdArray &toolCurveIds, 
	                                      const NcArray<NcGeVector3d> projVectors,
	                                      const NcGePoint3d& pickPoint, 
	                                      const NcGeVector3d& viewVector,
	                                      bool bAutoExtend,
	                                      bool bAssociativeEnabled);
	virtual NRX::UInt16       uIsolineDensity() const;
	virtual NRX::UInt16       vIsolineDensity() const;

	virtual Nano::ErrorStatus booleanIntersect(const NcDb3dSolid* pSolid,
	                                           NcArray<NcDbEntity*>& intersectionEntities);
	virtual Nano::ErrorStatus booleanSubtract(const NcDb3dSolid* pSolid,
	                                          NcDbSurface*& pNewSurface);
	Nano::ErrorStatus chamferEdges(const NcArray<NcDbSubentId*> &edgeSubentIds,
	                               const NcDbSubentId& baseFaceSubentId,
	                               double baseDist, double otherDist, bool bAssociativeEnabled);
	static Nano::ErrorStatus createBlendSurface ( NcDbLoftProfile* startProfile,
	                                              NcDbLoftProfile* endProfile,
	                                              NcDbBlendOptions* blendOptions,
	                                              bool  bAssociativeEnabled,
	                                              NcDbObjectId& blendSurfaceId);
	static Nano::ErrorStatus createExtrudedSurface ( NcDb3dProfile*pSweep,
	                                                 const NcGeVector3d& directionVec,
	                                                 NcDbSweepOptions& sweepOptions,
	                                                 bool  bAssociativeEnabled,
	                                                 NcDbObjectId& newExtrudedSurfaceId );
	static Nano::ErrorStatus createFilletSurface ( const NcDbObjectId& surfId1,
	                                               const NcGePoint3d& pickPt1,
	                                               const NcDbObjectId& surfId2,
	                                               const NcGePoint3d& pickPt2,
	                                               double radius,
	                                               NcDb::FilletTrimMode trimMode,
	                                               const NcGeVector3d& projDir,
	                                               bool  bAssociativeEnabled,
	                                               NcDbObjectId& filletSurfaceId);
	static Nano::ErrorStatus createLoftedSurface ( const NcArray<NcDbLoftProfile*>& crossSections,
	                                               const NcArray<NcDbLoftProfile*>& guides,
	                                               NcDbLoftProfile*pPath, NcDbLoftOptions& loftOptions,
	                                               bool  bAssociativeEnabled,
	                                               NcDbObjectId& newSurfaceId );
	static Nano::ErrorStatus createNetworkSurface ( const NcArray<NcDb3dProfile*>& uProfiles,
	                                                const NcArray<NcDb3dProfile*>& vProfiles,
	                                                bool  bAssociativeEnabled,
	                                                NcDbObjectId& newSurfaceId );
	static Nano::ErrorStatus createOffsetSurface ( NcDbEntity* pInputSurface,
	                                               double offsetDistance,
	                                               bool  bAssociativeEnabled,
	                                               NcDbObjectId& offsetSurfaceId);
	static Nano::ErrorStatus createPatchSurface ( const NcDbPathRef& pathRef,
	                                              const NcDbObjectIdArray& constraintIds,
	                                              int continuity,
	                                              double bulge,
	                                              bool  bAssociativeEnabled,
	                                              NcDbObjectId& newSurfaceId);
	static Nano::ErrorStatus createRevolvedSurface ( NcDb3dProfile*pRev,
	                                                 NcDb3dProfile*pAxis,
	                                                 bool flipAxisDirection,
	                                                 double revAngle, double startAngle,
	                                                 NcDbRevolveOptions& revolveOptions,
	                                                 NcDbRevolvedSurface*& newRevolvedSurface );
	static Nano::ErrorStatus createRevolvedSurface ( NcDb3dProfile*pRev,
	                                                 NcDb3dProfile*pAxis,
	                                                 bool flipAxisDirection,
	                                                 double revAngle, double startAngle,
	                                                 NcDbRevolveOptions& revolveOptions,
	                                                 bool  bAssociativeEnabled,
	                                                 NcDbObjectId& newRevolvedSurfaceId );
	static Nano::ErrorStatus createRevolvedSurface ( NcDb3dProfile*pRev,
	                                                 const NcGePoint3d& axisPnt,
	                                                 const NcGeVector3d& axisDir,
	                                                 double revAngle, double startAngle,
	                                                 NcDbRevolveOptions& revolveOptions,
	                                                 bool  bAssociativeEnabled,
	                                                 NcDbObjectId& newSurfaceId );
	static Nano::ErrorStatus createSweptSurface ( NcDb3dProfile*pSweep,
	                                              NcDb3dProfile*pPath,
	                                              NcDbSweepOptions& sweepOptions,
	                                              bool  bAssociativeEnabled,
	                                              NcDbObjectId& newSurfaceId );
	                                              Nano::ErrorStatus filletEdges(
	                                              const NcArray<NcDbSubentId*> &edgeSubentIds,
	                                              double radius, bool bAssociativeEnabled);

public:
	OdDbSurface* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbBody
class OdDbBody;
class NRXDBGATE_EXPORT NcDbBody : public NcDbEntity
{
	NCDB_DECLARE_MEMBERS(NcDbBody);

public:
	typedef NcDbBody  wrapper_class;
	typedef OdDbBody  native_class;

public:
	NcDbBody();
	NcDbBody(OdRxObject* _object);

	virtual Nano::ErrorStatus setBody(const void* modelerBody) ; // +Overload
	virtual NRX::UInt32 numChanges() const; // +Overload
	virtual NRX::Boolean isNull() const; // +Overload
	virtual void* internalSubentPtr(const NcDbSubentId& id) const; // +Overload
	virtual NcDbSubentId internalSubentId(void* ent) const; // +Overload
	virtual void* body() const; // +Overload
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) ; //+Overload
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) ; //+Overload
	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) ; //+Overload
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) ; //+Overload
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload

	void invalidateCachedBodySubentIds();

public:
	static Nano::ErrorStatus acisOut(const NCHAR* file, const NcDbVoidPtrArray& entities);
	static Nano::ErrorStatus acisIn(const NCHAR* file, NcDbVoidPtrArray& entities);

public:
	OdDbBody* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbLeader
class OdDbLeader;
class NRXDBGATE_EXPORT NcDbLeader : public NcDbCurve
{
	NCDB_DECLARE_MEMBERS(NcDbLeader);

public:
	typedef NcDbLeader  wrapper_class;
	typedef OdDbLeader  native_class;

public:
	NcDbLeader();
	NcDbLeader(OdRxObject* _object);

// NcGiDrawable interface
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;

// NcDbObject Protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual void erased(const NcDbObject* object, NRX::Boolean erasing = true);
	virtual Nano::ErrorStatus subClose() override;

	virtual void modifiedGraphics(const NcDbEntity* entity);

// NcDbEntity
public:
	virtual NRX::Boolean isPlanar() const override;
	virtual Nano::ErrorStatus getPlane(NcGePlane& plane, NcDb::Planarity& planarity) const override;

	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) override;
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d& xform, NcDbEntity*& entity) const override;
	virtual Nano::ErrorStatus subExplode(NcDbVoidPtrArray& set) const override;

	virtual void subSetDatabaseDefaults(NcDbDatabase* database) override;

	virtual Nano::ErrorStatus subGetCompoundObjectTransform(NcGeMatrix3d& matrix) const override;

	virtual Nano::ErrorStatus subGetClassID(CLSID* clsid) const;

	virtual Nano::ErrorStatus subGetSubentPathsAtGsMarker(NcDb::SubentType type, NRX::GsMarker marker,
	                                                      const NcGePoint3d& pick, const NcGeMatrix3d& xform,
	                                                      int& numPaths, NcDbFullSubentPath*& subentPaths,
	                                                      int numInserts = 0,
	                                                      NcDbObjectId* entAndInsertStack = NULL) const override;

	virtual Nano::ErrorStatus subGetGsMarkersAtSubentPath(const NcDbFullSubentPath& subPath,
	                                                      NcArray< NRX::GsMarker >& markers) const override;

// NcDbCurve methods.
public:
	virtual NRX::Boolean isClosed() const override;
	virtual NRX::Boolean isPeriodic() const override;

	virtual Nano::ErrorStatus getStartParam(double& param) const override;
	virtual Nano::ErrorStatus getEndParam(double& param) const override;
	virtual Nano::ErrorStatus getStartPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getEndPoint(NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getPointAtParam(double, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getParamAtPoint(const NcGePoint3d& point, double& param) const override;
	virtual Nano::ErrorStatus getDistAtParam(double param, double& distance) const override;
	virtual Nano::ErrorStatus getParamAtDist(double distance, double& param) const override;
	virtual Nano::ErrorStatus getDistAtPoint(const NcGePoint3d& point, double& distance) const override;
	virtual Nano::ErrorStatus getPointAtDist(double distance, NcGePoint3d& point) const override;
	virtual Nano::ErrorStatus getFirstDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getFirstDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(double param, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getSecondDeriv(const NcGePoint3d& point, NcGeVector3d& deriv) const override;
	virtual Nano::ErrorStatus getClosestPointTo(const NcGePoint3d& given, NcGePoint3d& point,
	                                            NRX::Boolean = NRX::kFalse) const override;
	virtual Nano::ErrorStatus getClosestPointTo(const NcGePoint3d& given, const NcGeVector3d& direction,
	                                            NcGePoint3d& point,
	                                            NRX::Boolean = NRX::kFalse) const override;
	virtual Nano::ErrorStatus getOrthoProjectedCurve(const NcGePlane& plane, NcDbCurve*& curve) const override;
	virtual Nano::ErrorStatus getProjectedCurve(const NcGePlane& plane, const NcGeVector3d& direction,
	                                            NcDbCurve*& curve) const override;
	virtual Nano::ErrorStatus getOffsetCurves(double distance, NcDbVoidPtrArray& curves) const override;
	virtual Nano::ErrorStatus getOffsetCurvesGivenPlaneNormal(const NcGeVector3d& normal, double distance,
	                                                          NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus getSpline(NcDbSpline*& spline) const override;
	virtual Nano::ErrorStatus getSplitCurves(const NcGeDoubleArray& params, NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus getSplitCurves(const NcGePoint3dArray& points, NcDbVoidPtrArray& segments) const override;
	virtual Nano::ErrorStatus extend(double param) override;
	virtual Nano::ErrorStatus extend(NRX::Boolean start, const NcGePoint3d& point) override;
	virtual Nano::ErrorStatus getArea(double& area) const override;
	virtual Nano::ErrorStatus reverseCurve() override;

public:
	virtual void setPlane(const NcGePlane &plane);
	virtual NcGeVector3d normal() const;

	virtual int numVertices() const;
	virtual NRX::Boolean appendVertex(const NcGePoint3d&);
	virtual void removeLastVertex  ();
	virtual NcGePoint3d firstVertex() const;
	virtual NcGePoint3d lastVertex() const;
	virtual NcGePoint3d vertexAt(int) const;
	virtual NRX::Boolean setVertexAt(int, const NcGePoint3d&);

	virtual NRX::Boolean hasArrowHead() const;
	virtual void enableArrowHead();
	virtual void disableArrowHead();
	virtual NRX::Boolean hasHookLine() const;

	virtual void setToSplineLeader();
	virtual void setToStraightLeader();
	virtual NRX::Boolean isSplined() const;

	virtual NcDbHardPointerId dimensionStyle() const;
	virtual void setDimensionStyle (const NcDbHardPointerId &id);

	Nano::ErrorStatus getDimstyleData(NcDbDimStyleTableRecord*& record) const;
	Nano::ErrorStatus setDimstyleData(NcDbDimStyleTableRecord* data);
	Nano::ErrorStatus setDimstyleData(NcDbObjectId id);

	virtual Nano::ErrorStatus attachAnnotation(const NcDbObjectId& id);
	virtual Nano::ErrorStatus detachAnnotation();
	virtual NcDbObjectId annotationObjId() const;
	virtual Nano::ErrorStatus evaluateLeader();

	virtual NcGeVector3d annotationOffset() const;
	virtual Nano::ErrorStatus setAnnotationOffset(const NcGeVector3d& offset);

	enum AnnoType
	{
		kMText = 0,
		kFcf,
		kBlockRef,
		kNoAnno
	};

	AnnoType annoType() const;
	double annoHeight() const;
	double annoWidth() const;

	virtual double dimasz() const;
	virtual NcCmColor dimclrd() const;
	virtual double dimgap() const;
	virtual NcDb::LineWeight dimlwd() const;
	virtual NcDbObjectId dimldrblk() const;
	virtual bool dimsah() const;
	virtual double dimscale() const;
	virtual int dimtad() const;
	virtual NcDbObjectId dimtxsty() const;
	virtual double dimtxt() const;

	virtual Nano::ErrorStatus setDimasz(double val);
	virtual Nano::ErrorStatus setDimclrd(NcCmColor& val);
	virtual Nano::ErrorStatus setDimgap(double val);
	virtual Nano::ErrorStatus setDimldrblk(NcDbObjectId val);
	virtual Nano::ErrorStatus setDimldrblk(const NCHAR *val);
	virtual Nano::ErrorStatus setDimlwd(NcDb::LineWeight v);
	virtual Nano::ErrorStatus setDimsah(bool val);
	virtual Nano::ErrorStatus setDimscale(double val);
	virtual Nano::ErrorStatus setDimtad(int val);
	virtual Nano::ErrorStatus setDimtxsty(NcDbObjectId val);
	virtual Nano::ErrorStatus setDimtxt(double val);

	virtual void setDimVars();
	virtual Nano::ErrorStatus setColorIndex(NRX::UInt16, NRX::Boolean doSubents = NRX::kTrue);

	virtual void copied (const NcDbObject*, const NcDbObject*);
	virtual void goodbye (const NcDbObject*);
	virtual void modified (const NcDbObject*);

public:
	OdDbLeader* native() const;

protected:
	virtual OdRxObject* GetNativeObject() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbRasterImageDefReactor
namespace Ntil
{
	class Image;
};
class OdDbRasterImageDefReactor;
class NRXDBGATE_EXPORT NcDbRasterImageDefReactor : public NcDbObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbRasterImageDefReactor);

	typedef NcDbRasterImageDefReactor  wrapper_class;
	typedef OdDbRasterImageDefReactor  native_class;

public:
	NcDbRasterImageDefReactor();
	NcDbRasterImageDefReactor(OdRxObject* _rxobject);

public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;

	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;

	virtual void erased(const NcDbObject* object, NRX::Boolean erasing = true);
	virtual void modified(const NcDbObject* object);

public:
	enum DeleteImageEvent
	{
		kUnload = 1,
		kErase  = 2,
	};

	virtual NRX::Boolean onDeleteImage(const NcDbRasterImageDef* pImageDef, Ntil::Image* pImage,
	                                   DeleteImageEvent event, NRX::Boolean cancelAllowed);

	static void setEnable(NRX::Boolean enable);
	static ClassVersion classVersion();

protected:
	virtual OdRxObject* GetNativeObject() const;

public:
	OdDbRasterImageDefReactor* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbLongTransWorkSetIterator
class OdDbLongTransWorkSetIterator;
class NRXDBGATE_EXPORT NcDbLongTransWorkSetIterator : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbLongTransWorkSetIterator);

	typedef NcDbLongTransWorkSetIterator  wrapper_class;
	typedef OdDbLongTransWorkSetIterator  native_class;

public:
	NcDbLongTransWorkSetIterator(OdRxObject* object);

	virtual void start(bool incRemovedObjs = false, bool incSecondaryObjs = false) = 0;

	virtual bool done() = 0;
	virtual void step() = 0;

	virtual NcDbObjectId objectId() const = 0;

	virtual bool curObjectIsErased() const = 0;
	virtual bool curObjectIsRemoved() const = 0;
	virtual bool curObjectIsPrimary() const = 0;

public:
	OdDbLongTransWorkSetIterator* native() const;
};

//////////////////////////////////////////////////////////////////////////
//NcDbLongTransaction
class OdDbLongTransaction;
class NRXDBGATE_EXPORT NcDbLongTransaction : public NcDbObject
{
	NCDB_DECLARE_MEMBERS(NcDbLongTransaction);

public:
	NcDbLongTransaction();
	NcDbLongTransaction(OdRxObject* _object);

	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload
	virtual Nano::ErrorStatus subErase(NRX::Boolean erase) ; //+Overload2

public:
	typedef NcDbLongTransaction  wrapper_class;
	typedef OdDbLongTransaction  native_class;

public:
	enum
	{
		kSameDb      = 0,
		kXrefDb      = 1,
		kUnrelatedDb = 2
	};

	int type() const;
	NcDbObjectId originBlock() const;
	NcDbObjectId destinationBlock() const;

	Nano::ErrorStatus getLongTransactionName(NCHAR*& name) const;

	Nano::ErrorStatus addToWorkSet(NcDbObjectId id);
	Nano::ErrorStatus removeFromWorkSet(NcDbObjectId id);
	Nano::ErrorStatus syncWorkSet();

	Nano::ErrorStatus newWorkSetIterator(NcDbLongTransWorkSetIterator*& iterator, bool incRemovedObjs = false,
	                                     bool incSecondaryObjs = false) const;

	NcDbObjectId originObject(NcDbObjectId id) const;
	bool workSetHas(NcDbObjectId id, bool bIncErased = false) const;

	NcDbIdMapping* activeIdMap();
	void regenWorkSetWithDrawOrder();
	bool disallowDrawOrder();

public:
	OdDbLongTransaction* native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbMInsertBlock
class OdDbMInsertBlock;
class NRXDBGATE_EXPORT NcDbMInsertBlock : public NcDbBlockReference
{
	NCDB_DECLARE_MEMBERS(NcDbMInsertBlock);

public:
	typedef NcDbMInsertBlock    wrapper_class;
	typedef OdDbMInsertBlock    native_class;

public:
	NcDbMInsertBlock();
	NcDbMInsertBlock(OdRxObject *_object);
	NcDbMInsertBlock(
	    const NcGePoint3d&  position,
	    NcDbObjectId        blockTableRec,
	    NRX::UInt16       columns,
	    NRX::UInt16       rows,
	    double              colSpacing,
	    double              rowSpacing);

	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) ; //+Overload2
	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform) ; //+Overload2
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) ; //+Overload2
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) ; //+Overload2

	NRX::UInt16 columns() const;
	Nano::ErrorStatus setColumns(NRX::UInt16);
	NRX::UInt16 rows() const;
	Nano::ErrorStatus setRows(NRX::UInt16);
	double columnSpacing() const;
	Nano::ErrorStatus setColumnSpacing(double);
	double rowSpacing() const;
	Nano::ErrorStatus setRowSpacing(double);

public:
	OdDbMInsertBlock *native() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbGroupIterator
class OdDbGroupIterator;
class NRXDBGATE_EXPORT NcDbGroupIterator : public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbGroupIterator);

	NcDbGroupIterator(OdRxObject* _object);

public:
	typedef NcDbGroupIterator  wrapper_class;
	typedef OdDbGroupIterator  native_class;

public:
	virtual Nano::ErrorStatus getObject(NcDbObject*& pObject, NcDb::OpenMode mode);
	virtual NcDbObjectId objectId () const;

	virtual bool done() const;
	virtual bool next ();

public:
	OdDbGroupIterator* native() const;
};

// AutoGen:

//////////////////////////////////////////////////////////////////////////
// NcDbCamera
class NRXDBGATE_EXPORT NcDbCamera: public NcDbEntity {
public:
	NcDbCamera ();
	virtual ~NcDbCamera();
	NCDB_DECLARE_MEMBERS(NcDbCamera);
	NcDbObjectId view() const;
	Nano::ErrorStatus    setView(const NcDbObjectId viewId);
	virtual Nano::ErrorStatus   subErase(NRX::Boolean erasing);
	virtual Nano::ErrorStatus   subOpen(NcDb::OpenMode openMode);
	virtual Nano::ErrorStatus   subClose();
	virtual Nano::ErrorStatus    dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus    dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus    dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus    dxfOutFields(NcDbDxfFiler* filer) const;
protected:
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw*    mode);
	virtual void subViewportDraw(NcGiViewportDrawNrx* mode);
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* pTraits);
	virtual void              subList() const;
	virtual Nano::ErrorStatus subGetGripPoints(NcDbGripDataPtrArray& grips,
	                                           const double curViewUnitSize,
	                                           const int gripSize,
	                                           const NcGeVector3d& curViewDir,
	                                           const int bitflags) const;
	virtual Nano::ErrorStatus subMoveGripPointsAt(
	                                        const NcDbVoidPtrArray& gripAppData,
	                                        const NcGeVector3d& offset,
	                                        const int bitflags);
	virtual Nano::ErrorStatus subGetStretchPoints(
	                                        NcGePoint3dArray&  stretchPoints)
	                                        const;
	virtual Nano::ErrorStatus subMoveStretchPointsAt(
	                                        const NcDbIntArray& indices,
	                                        const NcGeVector3d&     offset);
	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform);
	virtual Nano::ErrorStatus subDeepClone(NcDbObject* pOwnerObject,
	                                       NcDbObject*& pClonedObject,
	                                       NcDbIdMapping& idMap,
	                                       NRX::Boolean isPrimary
	                                       = NRX::kTrue) const;
	virtual Nano::ErrorStatus subWblockClone(NcRxObject* pOwnerObject,
	                                         NcDbObject*& pClonedObject,
	                                         NcDbIdMapping& idMap,
	                                         NRX::Boolean isPrimary
	                                         = NRX::kTrue) const;
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
	virtual Nano::ErrorStatus subHighlight(const NcDbFullSubentPath& subId = kNullSubent,
	                                       const NRX::Boolean highlightAll = NRX::kFalse) const;
	virtual Nano::ErrorStatus subUnhighlight(const NcDbFullSubentPath& subId = kNullSubent,
	                                         const NRX::Boolean highlightAll = NRX::kFalse) const;
private:
	NRX::UInt32       baseSetAttributes(NcGiDrawableTraits* pTraits);
	Nano::ErrorStatus   baseGetStretchPoints(NcGePoint3dArray&  stretchPoints) const;
	Nano::ErrorStatus   baseMoveStretchPointsAt(const NcDbIntArray & indices, const NcGeVector3d& offset);
	Nano::ErrorStatus   baseDeepClone(NcDbObject* pOwner,NcDbObject*& pClonedObject,
	                                  NcDbIdMapping& idMap,NRX::Boolean isPrimary) const;
	Nano::ErrorStatus   baseWblockClone(NcRxObject* pOwnerObject, NcDbObject*& pClonedObject,
	                                    NcDbIdMapping& idMap, NRX::Boolean isPrimary) const;
	Nano::ErrorStatus   baseHighlight(const NcDbFullSubentPath& subId,
	                                  const NRX::Boolean highlightAll) const;
	Nano::ErrorStatus   baseUnhighlight(const NcDbFullSubentPath& subId,
	                                    const NRX::Boolean highlightAll) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbClassIterator
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcDbClassIterator {
public:
	static NcDbClassIterator * newIterator(); // !!! CS_STDCALL
	static void deleteIterator(NcDbClassIterator *pIter); // !!! CS_STDCALL
	enum { kAllClasses = 0x01,
	       kCustomClasses   = 0x02,
	       kProxyClasses    = 0x04 };
	virtual Nano::ErrorStatus start(NcDbDatabase *pDb, int nFlags) = 0;
	virtual bool next() = 0;
	virtual bool done() const = 0;
	virtual void detach() = 0;
	virtual const NCHAR *name() const = 0;
	virtual const NCHAR *appName() const = 0;
	virtual const NCHAR *dxfName() const = 0;
	virtual NRX::UInt32 numInstances() const = 0;
#if !defined(HOST_IN_QT)
	virtual bool isProxy() const = 0;
#endif
	virtual bool isEntity() const = 0;
protected:
	NcDbClassIterator() {};
	virtual ~NcDbClassIterator() {};
};


//////////////////////////////////////////////////////////////////////////
// NcDbVertexRef
class NRXDBGATE_EXPORT NcDbVertexRef : public NcDbSubentRef {
public:
	NCRX_DECLARE_MEMBERS(NcDbVertexRef);
	NcDbVertexRef();
	NcDbVertexRef(const NcDbVertexRef&);
	virtual ~NcDbVertexRef();
	NcDbVertexRef(const NcDbCompoundObjectId&, const NcDbSubentId& = kNullSubentId, const NcGePoint3d& = NcGePoint3d::kOrigin);
	NcDbVertexRef(const NcDbFullSubentPath&);
	NcDbVertexRef(const NcDbEntity*);
	NcDbVertexRef(const NcGePoint3d&);
	NcDbVertexRef& operator =(const NcDbVertexRef&);
	virtual Nano::ErrorStatus copyFrom(const NcRxObject*);
	virtual void reset();
	virtual bool isValid() const;
	NcGePoint3d point() const;
	class NcDbPoint* createEntity()const;
private:
	NcGePoint3d mPoint;
};


//////////////////////////////////////////////////////////////////////////
// NcDbSurfaceTrimInfo
class NRXDBGATE_EXPORT NcDbSurfaceTrimInfo {
public:
	enum TrimRelation {
		outside_tool,
		inside_tool,
	};
	NcDbSurfaceTrimInfo();
	virtual ~NcDbSurfaceTrimInfo();
	void setTrimInfo( const NcDbCompoundObjectId& curveId, const NcGeVector3d & projVector, TrimRelation relation );
	void setTrimInfo( ENTITY *pWireBody, const NcGeVector3d& projVector, TrimRelation relation);
	void setTrimInfo( const NcDbCompoundObjectId &surfaceId, TrimRelation relation, const NcDbSubentId& subentId);
	void setTrimInfo( ENTITY *pAsmBody, TrimRelation relation, const NcDbSubentId& subentId );
	bool isCurve() const;
	ENTITY *toolBody() const;
	void setToolBody(ENTITY *pEntity);
	NcDbCompoundObjectId toolBodyId() const;
	void setToolBodyId( const NcDbCompoundObjectId &toolId );
	TrimRelation relation() const;
	void setRelation( TrimRelation relation );
	NcGeVector3d projVector() const;
	void setProjVector(const NcGeVector3d& projVector);
	NcDbSubentId faceSubentId() const;
private:
	bool mbCurve;
	NcGeVector3d mProjVector;
	NcDbCompoundObjectId mToolBodyId;
	NcDbSubentId mToolFaceSubentId;
	mutable ENTITY *mToolBody;
	TrimRelation mRelation;
};

//////////////////////////////////////////////////////////////////////////
// NcFdFieldEvaluator
class NcFdFieldEvaluator : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcFdFieldEvaluator);
	NRXDBGATE_EXPORT NcFdFieldEvaluator(void);
	NRXDBGATE_EXPORT virtual ~NcFdFieldEvaluator(void);
	NRXDBGATE_EXPORT virtual const NCHAR * evaluatorId(void) const;
	NRXDBGATE_EXPORT virtual const NCHAR * evaluatorId(NcDbField* pField);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus initialize(NcDbField* pField);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus compile(NcDbField* pField,
	                                                   NcDbDatabase* pDb,
	                                                   NcFdFieldResult* pResult);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus evaluate(NcDbField* pField,
	                                                    int nContext,
	                                                    NcDbDatabase* pDb,
	                                                    NcFdFieldResult* pResult);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus format(NcDbField* pField,
	                                                  NCHAR *& pszValue);
protected:
	NcFdFieldEvaluator(void*);
private:
	friend class NcFdSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcFdFieldEvaluatorLoader
class NcFdFieldEvaluatorLoader : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcFdFieldEvaluatorLoader);
	NRXDBGATE_EXPORT NcFdFieldEvaluatorLoader(void);
	NRXDBGATE_EXPORT NcFdFieldEvaluatorLoader(void*);
	NRXDBGATE_EXPORT ~NcFdFieldEvaluatorLoader(void);
	NRXDBGATE_EXPORT virtual NcFdFieldEvaluator* getEvaluator(
	                                            const NCHAR * pszEvalId);
	NRXDBGATE_EXPORT virtual NcFdFieldEvaluator * findEvaluator(NcDbField* pField,
	                                                            const NCHAR *& pszEvalId);
private:
	friend class NcFdSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcFdFieldEngine
class NcFdFieldEngine : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcFdFieldEngine);
	NRXDBGATE_EXPORT NcFdFieldEngine();
	NRXDBGATE_EXPORT virtual ~NcFdFieldEngine();
	NRXDBGATE_EXPORT Nano::ErrorStatus registerEvaluatorLoader(NcFdFieldEvaluatorLoader* pLoader);
	NRXDBGATE_EXPORT Nano::ErrorStatus unregisterEvaluatorLoader(NcFdFieldEvaluatorLoader* pLoader);
	NRXDBGATE_EXPORT int   evaluatorLoaderCount    (void) const;
	NRXDBGATE_EXPORT NcFdFieldEvaluatorLoader * getEvaluatorLoader(int iIndex);
	NRXDBGATE_EXPORT NcFdFieldEvaluator * getEvaluator (const NCHAR * pszEvalId);
	NRXDBGATE_EXPORT NcFdFieldEvaluator * findEvaluator(NcDbField* pField,
	                                                    const NCHAR *& pszEvalId);
private:
	friend class NcFdSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcFdFieldResult
class NRXDBGATE_EXPORT NcFdFieldResult : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcFdFieldResult);
	NcFdFieldResult(void);
	virtual Nano::ErrorStatus setFieldValue(const NcValue* pValue);
	virtual Nano::ErrorStatus setEvaluationStatus(int nStatus,
	                                                               int dwErrCode = 0,
	                                                               const NCHAR * pszMsg = NULL);
};

//////////////////////////////////////////////////////////////////////////
// NcFdFieldValue
class NcFdFieldValue : public NcValue {
public:
	NCRX_DECLARE_MEMBERS(NcFdFieldValue);
	NRXDBGATE_EXPORT NcFdFieldValue(void);
	NRXDBGATE_EXPORT NcFdFieldValue(NcFdFieldValue::DataType nDataType);
	NRXDBGATE_EXPORT NcFdFieldValue(const NcFdFieldValue& value);
	NRXDBGATE_EXPORT NcFdFieldValue(const NCHAR * pszValue);
	NRXDBGATE_EXPORT NcFdFieldValue(NRX::Int32 lValue);
	NRXDBGATE_EXPORT NcFdFieldValue(double fValue);
	NRXDBGATE_EXPORT NcFdFieldValue(const __time64_t& date);
	NRXDBGATE_EXPORT NcFdFieldValue(const SYSTEMTIME& date);
	NRXDBGATE_EXPORT NcFdFieldValue(const NcGePoint2d& pt);
	NRXDBGATE_EXPORT NcFdFieldValue(double x, double y);
	NRXDBGATE_EXPORT NcFdFieldValue(const NcGePoint3d& pt);
	NRXDBGATE_EXPORT NcFdFieldValue(double x, double y, double z);
	NRXDBGATE_EXPORT NcFdFieldValue(const NcDbObjectId& id);
	NRXDBGATE_EXPORT NcFdFieldValue(const resbuf& rb);
	NRXDBGATE_EXPORT NcFdFieldValue(const NcDbEvalVariant& evalVar);
	NRXDBGATE_EXPORT NcFdFieldValue(const VARIANT& var);
	NRXDBGATE_EXPORT NcFdFieldValue(const void* pBuf, DWORD dwBufSize);
};

class NcDbFieldFactory;
class NcDbField : public NcDbObject
{
public:
	enum State
	{
		kInitialized        = (0x1 << 0),       // Field has been initialized by the evaluator
		kCompiled           = (0x1 << 1),       // Field has been compiled
		kModified           = (0x1 << 2),       // Field code has been modified, but not yet evaluated
		kEvaluated          = (0x1 << 3),       // Field has been evaluated
		kHasCache           = (0x1 << 4),       // Field has evaluated cache
		kHasFormattedString = (0x1 << 5),       // For internal use only. Field has cached formatted string. 
	};

	enum EvalOption
	{
		kDisable            = 0,                // Disable evaluation of field
		kOnOpen             = (0x1 << 0),       // Evaluate on drawing open
		kOnSave             = (0x1 << 1),       // Evaluate on drawing save
		kOnPlot             = (0x1 << 2),       // Evaluate on drawing plot
		kOnEtransmit        = (0x1 << 3),       // Evaluate on drawing etransmit
		kOnRegen            = (0x1 << 4),       // Evaluate on drawing regen
		kOnDemand           = (0x1 << 5),       // Evaluate on demand
		kAutomatic          = (kOnOpen | kOnSave | kOnPlot | 
		kOnEtransmit | kOnRegen | kOnDemand),    // No restriction
	};

	enum EvalContext
	{
		kOpen               = (0x1 << 0),       // Field is being evaluated during open
		kSave               = (0x1 << 1),       // Field is being evaluated during save
		kPlot               = (0x1 << 2),       // Field is being evaluated during plot
		kEtransmit          = (0x1 << 3),       // Field is being evaluated during etransmit
		kRegen              = (0x1 << 4),       // Field is being evaluated during regen
		kDemand             = (0x1 << 5),       // Field is being evaluated on demand
		kPreview            = (0x1 << 6),       // Field is being evaluated for preview of field result
		//kPlotPreview        = (0x1 << 7),       // Field is being evaluated during plot preview <<<<<<<<<<<<<<<<<<<<<<<<< OdUnsupported
	};

	enum EvalStatus
	{
		kNotYetEvaluated    = (0x1 << 0),       // Not yet evaluated
		kSuccess            = (0x1 << 1),       // Evaluated successfully
		kEvaluatorNotFound  = (0x1 << 2),       // Evaluator not found
		kSyntaxError        = (0x1 << 3),       // Field code syntax error
		kInvalidCode        = (0x1 << 4),       // Invalid field code
		kInvalidContext     = (0x1 << 5),       // Invalid context to evaluate field
		kOtherError         = (0x1 << 6),       // Evaluation error
	};

	enum FieldCodeFlag
	{
		kFieldCode          = (0x1 << 0),       // Get raw field code. Used only in getFieldCode().
		kEvaluatedText      = (0x1 << 1),       // Get evaluated text. Used only in getFieldCode().
		kEvaluatedChildren  = (0x1 << 2),       // Get field code with evaluated text for child fields. Used only in getFieldCode().
		kObjectReference    = (0x1 << 3),       // Get child fields as object references if this is text field or 
		// this field as object reference if this is not text field. Used only in getFieldCode().
		kAddMarkers         = (0x1 << 4),       // Include markers around field codes. Used only in getFieldCode().
		kEscapeBackslash    = (0x1 << 5),       // Convert single backslashes to double backslashes. Used only in getFieldCode().
		kStripOptions       = (0x1 << 6),       // Strip the standard options from field code. Used only in getFieldCode().
		kPreserveFields     = (0x1 << 7),       // Try to preserve existing fields. Used only in setFieldCode().
		kTextField          = (0x1 << 8),       // Treat the field as text with embedded fields. Used only in setFieldCode().
		kPreserveOptions    = (0x1 << 9),       // Preserve the current standard options. Used only in setFieldCode(). For internal use.
		kDetachChildren     = (0x1 << 10),      // For internal use. Detach the child fields without erasing/deleting them. 
		// Used only in setFieldCode().
		kChildObjectReference = (0x1 << 11),    // For internal use. Get child fields as object references. 
		// Used only in getFieldCode().
		kForExpression      = (0x1 << 12),      // For internal use. Used with kEvaluatedText/kEvaluatedChildren.
		// Get the value in a format which can be used in arithmatic expressions. Used only in getFieldCode().
	};

	enum FilingOption
	{
		kSkipFilingResult   = (0x1 << 0),       // Don't file field value
	};

public:
	NCDB_DECLARE_MEMBERS(NcDbField);

	NRXDBGATE_EXPORT NcDbField(void);
	NRXDBGATE_EXPORT NcDbField(const NCHAR * pszFieldCode, bool bTextField = false);
	NRXDBGATE_EXPORT ~NcDbField(void);

	NRXDBGATE_EXPORT Nano::ErrorStatus setInObject (NcDbObject* pObj, 
		const NCHAR * pszPropName);
	NRXDBGATE_EXPORT Nano::ErrorStatus postInDatabase(NcDbDatabase* pDb);
	NRXDBGATE_EXPORT NcDbField::State state        (void) const;
	NRXDBGATE_EXPORT NcDbField::EvalStatus evaluationStatus(int* pnErrCode = NULL, 
		NCHAR ** pszErrMsg = NULL) const;
	NRXDBGATE_EXPORT NcDbField::EvalOption evaluationOption(void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setEvaluationOption(NcDbField::EvalOption nEvalOption);
	NRXDBGATE_EXPORT NcDbField::FilingOption filingOption(void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setFilingOption(NcDbField::FilingOption nOption);

	NRXDBGATE_EXPORT const NCHAR  * evaluatorId    (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setEvaluatorId(const NCHAR * pszEvaluatorId);
	bool            isTextField             (void) const;
	Nano::ErrorStatus convertToTextField    (void);

	NRXDBGATE_EXPORT const NCHAR * getFieldCode     (NcDbField::FieldCodeFlag nFlag,
		NcArray<NcDbField*>* pChildFields = NULL, 
		NcDb::OpenMode mode = NcDb::kForRead) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getFieldCode(NCHAR*& pszFieldCode, 
		NcDbField::FieldCodeFlag nFlag,
		NcArray<NcDbField*>* pChildFields = NULL, 
		NcDb::OpenMode mode = NcDb::kForRead) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setFieldCode(const NCHAR* pszFieldCode, 
		NcDbField::FieldCodeFlag nFlag = (NcDbField::FieldCodeFlag) 0,
		NcDbFieldArray* pChildFields = NULL);

	NRXDBGATE_EXPORT int   childCount              (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getChild    (int iIndex, 
		NcDbField*& pField, 
		NcDb::OpenMode mode);

	NRXDBGATE_EXPORT const NCHAR * getFormat       (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getFormat   (NCHAR*& pszFormat) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setFormat   (const NCHAR* pszFormat);

	NRXDBGATE_EXPORT Nano::ErrorStatus evaluate    (int nContext, 
		NcDbDatabase* pDb, 
		int* pNumFound     = NULL,
		int* pNumEvaluated = NULL);
	NRXDBGATE_EXPORT NcValue::DataType dataType    (void) const;

	NRXDBGATE_EXPORT const NCHAR * getValue        (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getValue    (NCHAR*& pszValue) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getValue    (NcValue& value) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getValue    (NcFdFieldValue& value) const;

	NRXDBGATE_EXPORT bool  hasHyperlink            (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getHyperlink(NcHyperlink& hlink) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getHyperlink(NCHAR** pszName,
		NCHAR** pszDescription, 
		NCHAR** pszSubLocation,
		NCHAR** pszDisplayString,
		NRX::Int32* pFlag) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setHyperlink(const NcHyperlink& hlink);
	NRXDBGATE_EXPORT Nano::ErrorStatus setHyperlink(const NCHAR* pszName, 
		const NCHAR* pszDescription, 
		const NCHAR* pszSubLocation = NULL);
	NRXDBGATE_EXPORT Nano::ErrorStatus setHyperlink(const NCHAR* pszName, 
		const NCHAR* pszDescription, 
		const NCHAR* pszSubLocation,
		NRX::Int32 lFlag);
	NRXDBGATE_EXPORT Nano::ErrorStatus removeHyperlink(void);

	NRXDBGATE_EXPORT Nano::ErrorStatus getData     (const NCHAR* pszKey, 
		NcValue* pData) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setData     (const NCHAR* pszKey, 
		const NcValue* pData);
	NRXDBGATE_EXPORT Nano::ErrorStatus setData     (const NCHAR* pszKey, 
		const NcValue* pData,
		bool bRecursive);

public:
	// Base class overrides
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler* pFiler);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler* pFiler);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus subClose();

	friend class NcDbFieldFactory;
	void* native() { return m_native; }
protected:
	void* m_native;
	void  setNative(void* native);
};


//////////////////////////////////////////////////////////////////////////
// NcFdFieldReactor
class NRXDBGATE_EXPORT NcFdFieldReactor : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcFdFieldReactor);
	virtual Nano::ErrorStatus beginEvaluateFields(int nContext,
	                                                               NcDbDatabase* pDb);
	virtual Nano::ErrorStatus endEvaluateFields(int nContext,
	                                                             NcDbDatabase* pDb);
};

//////////////////////////////////////////////////////////////////////////
// NcDbHyperlink
class NcDbHyperlink {
public:
	NcDbHyperlink() {};
	virtual ~NcDbHyperlink(){};
	enum HLinkFlags {
		kUndefined = 0,
		kConvertDwgToDwf = 0x1
	};
	virtual const NCHAR * name() const = 0;
	virtual void setName(const NCHAR * cName) = 0;
	virtual const NCHAR * description() const = 0;
	virtual void setDescription(const NCHAR * cDescription) = 0;
	virtual const NCHAR * subLocation() const = 0;
	virtual void setSubLocation(const NCHAR * cSubLocation) = 0;
	virtual const NCHAR * getDisplayString() const = 0;
	virtual bool isOutermostContainer() const = 0;
	virtual const int getNestedLevel() const = 0;
	virtual const NRX::Int32 flags() const;
	virtual void setFlags(const NRX::Int32 lFlags);
};

//////////////////////////////////////////////////////////////////////////
// NcDbHyperlinkCollection
class NcDbHyperlinkCollection {
public:
	NcDbHyperlinkCollection() {};
	virtual ~NcDbHyperlinkCollection(){};
	virtual void addHead(const NCHAR * sName, const NCHAR * sDescription,
	                     const NCHAR * sSubLocation = NULL) = 0;
	virtual void addTail(const NCHAR * sName, const NCHAR * sDescription,
	                     const NCHAR * sSubLocation = NULL) = 0;
	virtual void addAt(const int nIndex, const NCHAR * sName,
	                   const NCHAR * sDescription,
	                   const NCHAR * sSubLocation = NULL) = 0;
	virtual void removeHead() = 0;
	virtual void removeTail() = 0;
	virtual void removeAt(const int nIndex) = 0;
	virtual int count() const = 0;
	virtual NcDbHyperlink * item(const int nIndex) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbEntityHyperlinkPE
class NRXDBGATE_EXPORT NcDbEntityHyperlinkPE : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbEntityHyperlinkPE);
	virtual Nano::ErrorStatus getHyperlinkCollection(NcDbObject * pObj,
	                                                 NcDbHyperlinkCollection *& pcHCL,
	                                                 bool bOneOnly = false,
	                                                 bool bIgnoreBlockDefinition = true) = 0;
	virtual Nano::ErrorStatus getHyperlinkCollection(const NcArray<NcDbObjectId> *& idContainers,
	                                                 NcDbHyperlinkCollection *& pcHCL,
	                                                 bool bOneOnly = false,
	                                                 bool bIgnoreBlockDefinition = true) = 0;
	virtual Nano::ErrorStatus setHyperlinkCollection(NcDbObject * pObj,
	                                                 NcDbHyperlinkCollection * pcHCL) = 0;
	virtual Nano::ErrorStatus getHyperlinkCount(NcDbObject * pObj,
	                                            UINT & nCount,
	                                            bool bIgnoreBlockDefinition = true) = 0;
	virtual Nano::ErrorStatus getHyperlinkCount(const NcArray<NcDbObjectId> *& idContainers,
	                                            UINT & nCount,
	                                            bool bIgnoreBlockDefinition = true) = 0;
	virtual Nano::ErrorStatus hasHyperlink(NcDbObject * pObj,
	                                       bool & bHasHyperlink,
	                                       bool bIgnoreBlockDefinition = true) = 0;
	virtual Nano::ErrorStatus hasHyperlink(const NcArray<NcDbObjectId> *& idContainers,
	                                       bool & bHasHyperlink,
	                                       bool bIgnoreBlockDefinition = true) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDb3dProfile
class NRXDBGATE_EXPORT NcDb3dProfile : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDb3dProfile);
	NcDb3dProfile ();
	NcDb3dProfile ( NcDbEntity *pEntity );
	NcDb3dProfile ( const NcDbFullSubentPath& faceSubentPath );
	NcDb3dProfile ( const NcDbPathRef & pathRef);
	NcDb3dProfile ( const NcDbVertexRef & vertexRef);
	NcDb3dProfile ( const NcDb3dProfile& src );
	virtual ~NcDb3dProfile();
	NcDbEntity*  entity () const;
	Nano::ErrorStatus getPathRef( NcDbPathRef &pathRef ) const;
	Nano::ErrorStatus getVertexRef( NcDbVertexRef &vertexRef ) const;
	Nano::ErrorStatus  convertProfile ( bool explodeMultiFaceRegions, bool convertSurfaceToEdges,
	                                   bool nonPlanarOnly, bool outerLoopOnly,
	                                   NcArray<NcDb3dProfile*>& convertedProfileArr ) const;
	static NcDb3dProfile* convertProfile(const NcArray<NcDbPathRef>&);
	Nano::ErrorStatus set ( const NcDbPathRef &pathRef );
	Nano::ErrorStatus set ( const NcDbVertexRef &vertexRef );
	Nano::ErrorStatus set ( NcDbEntity *pEntity );
	bool  isClosed () const;
	bool  isPlanar () const;
	bool  isSubent () const;
	bool  isFace () const;
	bool  isEdge () const;
	bool  isValid () const;
	static Nano::ErrorStatus mergeProfiles ( const NcArray<NcDb3dProfile*>& profileArr,
	                                        bool mergeEdges, bool mergeCurves,
	                                        NcArray<NcDb3dProfile*>& mergedProfileArr );
	NcDb3dProfile& operator = ( const NcDb3dProfile& src );
private:
	friend class NcDb3dProfileData;
	friend class NcDbLoftProfile;
	NcDb3dProfileData *mProfileData;
	NcDbEntity *pEntity;
};

//////////////////////////////////////////////////////////////////////////
// NcDbLoftProfile
class NRXDBGATE_EXPORT NcDbLoftProfile : public NcDb3dProfile {
public:
	NCRX_DECLARE_MEMBERS(NcDbLoftProfile);
	NcDbLoftProfile ();
	NcDbLoftProfile ( NcDbEntity *pEntity );
	NcDbLoftProfile ( const NcDbPathRef & pathRef);
	NcDbLoftProfile ( const NcGePoint3d& pnt );
	NcDbLoftProfile ( const NcDbLoftProfile& src );
	NRX::Int16  continuity () const;
	void          setContinuity ( NRX::Int16 value );
	double        magnitude () const;
	void          setMagnitude ( double value );
	NcDbLoftProfile& operator = ( const NcDbLoftProfile& src );
	NcDbLoftProfile& operator = ( const NcDb3dProfile& src );
};

//////////////////////////////////////////////////////////////////////////
// NcDbAlignment
class NRXDBGATE_EXPORT NRX_NO_VTABLE NcDbAlignment : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAlignment);
	virtual Nano::ErrorStatus getAlignment(
	    NcDbEntity*           pEnt,
	    const NcArray< NcDbObjectIdArray,
	        NcArrayObjectCopyReallocator< NcDbObjectIdArray > >&
	            nestedPickedEntities,
	    const NcGePoint3d&    pickPoint,
	    const NcGeVector3d&   normal,
	    NcGePoint3d&          closestPoint,
	    NcGeVector3d&         direction) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAnnotationScale
class NcDbAnnotationScaleImpl;
class OdDbAnnotationScale;
class NRXDBGATE_EXPORT NcDbAnnotationScale : public NcDbObjectContext, public NcHeapOperators {
public:
	NCRX_DECLARE_MEMBERS(NcDbAnnotationScale);
	typedef NcDbAnnotationScale  wrapper_class;
	typedef OdDbAnnotationScale  native_class;
	NcDbAnnotationScale ();
	NcDbAnnotationScale (OdRxObject* _object);
	virtual ~NcDbAnnotationScale ();
	virtual Nano::ErrorStatus getName (NcString& name) const;
	virtual Nano::ErrorStatus setName (const NcString& name);
	virtual NRX::LongPtr uniqueIdentifier () const;
	virtual NcString collectionName () const;
	virtual Nano::ErrorStatus copyFrom ( const NcRxObject *pOther);
	virtual Nano::ErrorStatus getPaperUnits (double& dPaperUnits) const;
	virtual Nano::ErrorStatus setPaperUnits (double dPaperUnits);
	virtual Nano::ErrorStatus getDrawingUnits (double&  dDrawingUnits) const;
	virtual Nano::ErrorStatus setDrawingUnits (const double dDrawingUnits);
	virtual Nano::ErrorStatus getScale (double& dScale) const;
	virtual Nano::ErrorStatus  getIsTemporaryScale (bool& bTemporary) const;
	virtual bool matchScaleId(NRX::LongPtr id) const;
	//friend class NcDbSystemInternals;
	NcDbAnnotationScale ( bool );
public:
	OdDbAnnotationScale* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAnnotationScaleReactor
class NRXDBGATE_EXPORT NcDbAnnotationScaleReactor: public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAnnotationScaleReactor);
	virtual void annotationScaleChanged (const NcDbDatabase* pDb,
	                                     const NcDbViewport* pVP,
	                                     const NcDbAnnotationScale* pScale,
	                                     const bool bInitializing);
};

//////////////////////////////////////////////////////////////////////////
// NcDbPaperOrientationPE
class NRXDBGATE_EXPORT NcDbPaperOrientationPE : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbPaperOrientationPE);
	virtual bool paperOrientation(NcDbObject* pObject) const = 0;
	virtual Nano::ErrorStatus setPaperOrientation(
	                                     NcDbObject* pObject,
	                                     const bool  bPaperOrientation ) = 0;
	virtual Nano::ErrorStatus applyPaperOrientationTransform (
	                                     NcDbObject* pObject,
	                                     const NcDbViewport *pVport ) const
	    { return Nano::eNotImplementedYet; }
};

//////////////////////////////////////////////////////////////////////////
// NcDbAppEntityGrips
class NRXDBGATE_EXPORT NcDbAppEntityGrips : public NcRxProtocolReactor {
public:
	NCRX_DECLARE_MEMBERS(NcDbAppEntityGrips);
	virtual Nano::ErrorStatus getGripPoints (
	                                    NcDbGripDataPtrArray& grips,
	                                    const double          curViewUnitSize,
	                                    const int             gripSize,
	                                    const NcGeVector3d&   curViewDir,
	                                    const int             bitflags,
	                                    NcDbEntity*           pEntity) = 0;
	virtual Nano::ErrorStatus moveGripPointsAt (
	                     const NcDbVoidPtrArray&        gripAppData,
	                     const NcGeVector3d&            offset,
	                     const int                      bitflags,
	                     NcDbEntity*                    pEntity) = 0;
	virtual void gripStatus(const NcDb::GripStat status,
	                        NcDbEntity*          pEntity) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbBlockInsertionPoints
class NRXDBGATE_EXPORT NcDbBlockInsertionPoints :  public NcRxProtocolReactor {
	public:
	    NCRX_DECLARE_MEMBERS(NcDbBlockInsertionPoints);
	    virtual Nano::ErrorStatus getInsertionPoints (
	                    const NcDbBlockTableRecord* pBlock,
	                    const NcDbBlockReference*   pBlkRef,
	                    NcGePoint3dArray&           insPts,
	                    NcGeVector3dArray&          alignmentDirections) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbRecover
class NcDbRecover {
	public:
	virtual  int callBack(NcDbDatabase*) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbRecoverCallBack
class NRXDBGATE_EXPORT NcDbRecoverCallBack {
	public:
	NcDbRecoverCallBack();
	virtual ~NcDbRecoverCallBack();
	virtual  Nano::ErrorStatus registerCallBack(NcDbRecover*);
	virtual  Nano::ErrorStatus removeCallBack();
};

//////////////////////////////////////////////////////////////////////////
// NcDbAuditRecreatePE
class NRXDBGATE_EXPORT NcDbAuditRecreatePE : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbAuditRecreatePE);
	virtual bool replace(NcDbObject*&   pNewObj,
	                     NcDbObjectId   originalObjId,
	                     NcRxClass*     pObjClass,
	                     NcDbDatabase*  pDb,
	                     NcDbAuditInfo* pAuditInfo)
	{ return false; };
	virtual bool redirect(NcDbObjectId&  newObjId,
	                      NcDbObjectId   originalObjId,
	                      NcRxClass*     pObjClass,
	                      NcDbDatabase*  pDb,
	                      NcDbAuditInfo* pAuditInfo)
	{ return false; };
};

//////////////////////////////////////////////////////////////////////////
// NcDbBackground
Nano::ErrorStatus NRXDBGATE_EXPORT getBackgroundDictionary (NcDbDatabase* pDb, NcDbDictionary*& pDict,
                                                            NcDb::OpenMode mode, bool createIfNonExist);

Nano::ErrorStatus NRXDBGATE_EXPORT getBackgroundDictionary (NcDbDatabase* pDb, NcDbDictionary*& pDict,
                                                            NcDb::OpenMode mode);

class NRXDBGATE_EXPORT NcDbBackground : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbBackground);
	virtual ~NcDbBackground();
	NcDbBackground() {};
	virtual NcGiDrawable*  drawable ();
};

//////////////////////////////////////////////////////////////////////////
// NcDbSolidBackground
class NRXDBGATE_EXPORT NcDbSolidBackground : public NcDbBackground {
public:
	NCRX_DECLARE_MEMBERS(NcDbSolidBackground);
	NcDbSolidBackground();
	virtual ~NcDbSolidBackground();
	void            setColorSolid   (const NcCmEntityColor & color);
	NcCmEntityColor colorSolid      (void) const;
	virtual Nano::ErrorStatus dwgInFields  (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields (NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields  (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields (NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus copyFrom     (const NcRxObject* other);
	virtual NcGiDrawable::DrawableType    drawableType() const;
protected:
	virtual NRX::UInt32  subSetAttributes (NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbGradientBackground
class NRXDBGATE_EXPORT NcDbGradientBackground : public NcDbBackground {
public:
	NCRX_DECLARE_MEMBERS(NcDbGradientBackground);
	NcDbGradientBackground();
	virtual ~NcDbGradientBackground();
	void            setColorTop    (const NcCmEntityColor & color);
	NcCmEntityColor colorTop       (void) const;
	void            setColorMiddle (const NcCmEntityColor & color);
	NcCmEntityColor colorMiddle    (void) const;
	void            setColorBottom (const NcCmEntityColor & color);
	NcCmEntityColor colorBottom    (void) const;
	void            setHorizon     (double horizon);
	double          horizon        (void) const;
	void            setHeight      (double height);
	double          height         (void) const ;
	void            setRotation    (double rotation);
	double          rotation       (void) const;
	virtual Nano::ErrorStatus dwgInFields  (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields (NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields  (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields (NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus copyFrom     (const NcRxObject* other);
	virtual NcGiDrawable::DrawableType    drawableType() const;
protected:
	virtual NRX::UInt32  subSetAttributes (NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbImageBackground
class NRXDBGATE_EXPORT NcDbImageBackground : public NcDbBackground {
public:
	NCRX_DECLARE_MEMBERS(NcDbImageBackground);
	NcDbImageBackground();
	virtual ~NcDbImageBackground();
	void            setImageFilename        (const NCHAR* filename);
	const NCHAR *   imageFilename           (void) const;
	void            setFitToScreen          (bool bFitToScreen);
	bool            fitToScreen             (void) const;
	void            setMaintainAspectRatio  (bool bMaintainAspectRatio);
	bool            maintainAspectRatio     (void) const;
	void            setUseTiling            (bool bUseTiling);
	bool            useTiling               (void) const;
	void            setXOffset              (double xOffset);
	double          xOffset                 (void) const;
	void            setYOffset              (double yOffset);
	double          yOffset                 (void) const;
	void            setXScale               (double xScale);
	double          xScale                  (void) const;
	void            setYScale               (double yScale);
	double          yScale                  (void) const;
	virtual Nano::ErrorStatus dwgInFields  (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields (NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields  (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields (NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus copyFrom     (const NcRxObject* other);
	virtual NcGiDrawable::DrawableType    drawableType() const;
protected:
	virtual NRX::UInt32  subSetAttributes (NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbGroundPlaneBackground
class NRXDBGATE_EXPORT NcDbGroundPlaneBackground : public NcDbBackground {
public:
	NCRX_DECLARE_MEMBERS(NcDbGroundPlaneBackground);
	NcDbGroundPlaneBackground();
	virtual ~NcDbGroundPlaneBackground();
	void            setColorSkyZenith       (const NcCmEntityColor & color);
	NcCmEntityColor colorSkyZenith          (void) const;
	void            setColorSkyHorizon      (const NcCmEntityColor & color);
	NcCmEntityColor colorSkyHorizon         (void) const;
	void            setColorUndergroundHorizon  (const NcCmEntityColor & color);
	NcCmEntityColor colorUndergroundHorizon     (void) const;
	void            setColorUndergroundAzimuth  (const NcCmEntityColor & color);
	NcCmEntityColor colorUndergroundAzimuth     (void) const;
	void            setColorGroundPlaneNear (const NcCmEntityColor & color);
	NcCmEntityColor colorGroundPlaneNear    (void) const;
	void            setColorGroundPlaneFar  (const NcCmEntityColor & color);
	NcCmEntityColor colorGroundPlaneFar     (void) const;
	virtual Nano::ErrorStatus dwgInFields  (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields (NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields  (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields (NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus copyFrom     (const NcRxObject* other);
	virtual NcGiDrawable::DrawableType    drawableType() const;
protected:
	virtual NRX::UInt32  subSetAttributes (NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbSkyBackground
class NRXDBGATE_EXPORT NcDbSkyBackground : public NcDbBackground {
public:
	NCRX_DECLARE_MEMBERS(NcDbSkyBackground);
	NcDbSkyBackground();
	virtual ~NcDbSkyBackground();
	Nano::ErrorStatus         setSunId     (NcDbObjectId sunId);
	NcDbObjectId              sunId        (void) const;
	virtual Nano::ErrorStatus dwgInFields  (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields (NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields  (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields (NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus copyFrom     (const NcRxObject* other);
	virtual NcGiDrawable::DrawableType    drawableType() const;
protected:
	virtual NRX::UInt32  subSetAttributes (NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbBlendOptions
class NRXDBGATE_EXPORT NcDbBlendOptions {
public:
	NcDbBlendOptions ();
	~NcDbBlendOptions ();
	enum DriveModeType {
		kDriveModeFirst  = 0,
		kDriveModeSecond = 1,
		kDriveModeBoth   = 2
	};
	NcDbBlendOptions& operator = ( const NcDbBlendOptions& src );
	bool  simplify () const;
	Nano::ErrorStatus  setSimplify ( bool val );
	bool  solid () const;
	Nano::ErrorStatus  setSolid ( bool val );
	unsigned int  quality () const;
	Nano::ErrorStatus  setQuality ( unsigned int val );
	NcGePoint3d*  coplanarPoint () const;
	Nano::ErrorStatus  setCoplanarPoint ( const NcGePoint3d* pPt );
	NcGeVector3d*  coplanarDirection () const;
	Nano::ErrorStatus  setCoplanarDirection ( const NcGeVector3d* pDir );
	NcDbBlendOptions::DriveModeType  driveMode () const;
	Nano::ErrorStatus  setDriveMode( NcDbBlendOptions::DriveModeType val );
};

//////////////////////////////////////////////////////////////////////////
// NcDbBreakData
class NRXDBGATE_EXPORT NcDbBreakData : public NcDbObject {
public:
	NCDB_DECLARE_MEMBERS(NcDbBreakData);
	NcDbBreakData();
	virtual ~NcDbBreakData();
	NcDbObjectId dimObjId() const;
	Nano::ErrorStatus setDimObjId(const NcDbObjectId& dimId);
	Nano::ErrorStatus addBreakPointRef(NcDbBreakPointRef* ptRef);
	Nano::ErrorStatus getBreakPointRef(int lineIndex,
	                                   NcArray<NcDbBreakPointRef*>& ptRefs) const;
	Nano::ErrorStatus getBreakPointRef(NcArray<NcDbBreakPointRef*>& ptRefs) const;
	Nano::ErrorStatus deleteAllBreakPointRefs();
	Nano::ErrorStatus removeAssociativity(bool force = true);
	Nano::ErrorStatus postToDb(NcDbObjectId& breakObjId);
	Nano::ErrorStatus eraseFromDb(void);
	virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler*);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler*) const;
	virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler*);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler*) const;
	virtual void  modifiedGraphics(const NcDbEntity* pEnt);
	Nano::ErrorStatus updateAssociativity(const NcDbObjectIdArray& ids, int cmdType);
};

//////////////////////////////////////////////////////////////////////////
// NcDbBreakPointRef
class NRXDBGATE_EXPORT NcDbBreakPointRef : public NcDbObject {
public:
	NCDB_DECLARE_MEMBERS(NcDbBreakPointRef);
	enum BreakPointType {
		kDynamic           = 0,
		kStatic            = 1,
		kStatic2Point      = 2
	};
	NcDbBreakPointRef();
	virtual ~NcDbBreakPointRef();
	NcDbBreakPointRef::BreakPointType pointType() const;
	Nano::ErrorStatus setPointType(NcDbBreakPointRef::BreakPointType newVal);
	NRX::Int32 lineIndex() const;
	Nano::ErrorStatus setLineIndex(NRX::Int32 index);
	NcGePoint3d breakPoint() const;
	Nano::ErrorStatus setBreakPoint(const NcGePoint3d& pt);
	NcGePoint3d breakPoint2() const;
	Nano::ErrorStatus setBreakPoint2(const NcGePoint3d& pt);
	Nano::ErrorStatus getBreakPointId(NcDbFullSubentPath& idPath) const;
	Nano::ErrorStatus setBreakPointId(const NcDbFullSubentPath& idPath);
	NcDbEntity *subentPtr() const;
	Nano::ErrorStatus intersectWith(const NcDbEntity* pEnt,
	                                NcGePoint3dArray& points,
	                                NcGePoint3dArray& textBoxPts);
	virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler*);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler*) const;
	virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler*);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
// NcDbDataLinkManager
class NcDbDataLinkManager : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbDataLinkManager);
	NRXDBGATE_EXPORT virtual ~NcDbDataLinkManager(void);
	NRXDBGATE_EXPORT Nano::ErrorStatus createDataLink(const NCHAR* pszAdapterId,
	                                                  const NCHAR* pszName,
	                                                  const NCHAR* pszDescription,
	                                                  const NCHAR* pszConnectionString,
	                                                  NcDbObjectId& idDataLink);
	NRXDBGATE_EXPORT Nano::ErrorStatus getDataLink (const NCHAR* pszName,
	                                                NcDbObjectId& idDataLink) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getDataLink (const NCHAR* pszName,
	                                                NcDbDataLink*& pDataLink,
	                                                NcDb::OpenMode mode) const;
	NRXDBGATE_EXPORT int   dataLinkCount           (void) const;
	NRXDBGATE_EXPORT int   getDataLink             (NcDbObjectIdArray& dataLinks) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus addDataLink (NcDbDataLink* pDataLink);
	NRXDBGATE_EXPORT Nano::ErrorStatus addDataLink (NcDbDataLink* pDataLink,
	                                                NcDbObjectId& idDataLink);
	Nano::ErrorStatus removeDataLink        (const NCHAR* pszKey,
	                                         NcDbObjectId& idDataLink);
	NRXDBGATE_EXPORT Nano::ErrorStatus removeDataLink(const NcDbObjectId& idDataLink);
	NRXDBGATE_EXPORT Nano::ErrorStatus update      (const NcDbObjectIdArray& dataIds,
	                                                NcDb::UpdateDirection nDir,
	                                                NcDb::UpdateOption nOption);
	NRXDBGATE_EXPORT Nano::ErrorStatus update      (NcDb::UpdateDirection nDir,
	                                                NcDb::UpdateOption nOption);
protected:
	NRXDBGATE_EXPORT NcDbDataLinkManager(void);
private:
	friend class NcTableSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDataColumn
class NRXDBGATE_EXPORT NcDbDataColumn : public NcRxObject {
public:
	NcDbDataColumn();
	NcDbDataColumn(const NcDbDataColumn& rCol);
	NcDbDataColumn(const NcDbDataCell::CellType type,
	               const NCHAR * pColName = NULL);
	virtual ~NcDbDataColumn();
	NCRX_DECLARE_MEMBERS(NcDbDataColumn);
	virtual NRX::UInt32 physicalLength() const;
	virtual NRX::UInt32 growLength() const;
	virtual Nano::ErrorStatus setPhysicalLength(NRX::UInt32 n);
	virtual Nano::ErrorStatus setGrowLength(NRX::UInt32 n);
	virtual NcDbDataColumn& operator = (const NcDbDataColumn& col);
	virtual Nano::ErrorStatus setColumnType(NcDbDataCell::CellType type);
	virtual NcDbDataCell::CellType columnType() const;
	virtual Nano::ErrorStatus setColumnName(const NCHAR * pName);
	virtual const NCHAR * columnName() const;
	virtual Nano::ErrorStatus getCellAt(NRX::UInt32 index, NcDbDataCell& outCell) const;
	virtual Nano::ErrorStatus setCellAt(NRX::UInt32 index, const NcDbDataCell& cell);
	virtual Nano::ErrorStatus appendCell(const NcDbDataCell& cell);
	virtual Nano::ErrorStatus insertCellAt(NRX::UInt32 index, const NcDbDataCell& cell);
	virtual Nano::ErrorStatus removeCellAt(NRX::UInt32 index);
	virtual Nano::ErrorStatus getIndexAtCell(const NcDbDataCell& cell, NRX::UInt32& index) const;
	virtual NRX::UInt32 numCells() const;
private:
	friend class NcDbSystemInternals;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDynamicUCSPE
class NRXDBGATE_EXPORT NcDbDynamicUCSPE    : public NcRxObject {
public:
	enum Flags {
		kDefault     = 0x00,
	};
NCRX_DECLARE_MEMBERS(NcDbDynamicUCSPE);
	virtual Nano::ErrorStatus
		getCandidatePlanes(NcArray<NcGePlane>& results,
		                   double &distToEdge,
		                   double &objWidth,
		                   double &objHeight,
		                   NcDbEntity* pEnt,
		                   const NcDbSubentId& subentId,
		                   const NcGePlane& viewplane,
		                   NcDbDynamicUCSPE::Flags flags = kDefault
		                   ) const = 0;
};

// NcRxClassExtPE
class NRXDBGATE_EXPORT NcRxClassExtPE : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcRxClassExtPE);
	virtual NcRxClass* ext_isA(NcDbEntity * pEnt);
};

//////////////////////////////////////////////////////////////////////////
// NcDbDynBlockTableRecord
class NcDbDynBlockTableRecord : public NcHeapOperators {
public:
	NRXDBGATE_EXPORT NcDbDynBlockTableRecord(NcDbObjectId blockTableRecordId);
	NRXDBGATE_EXPORT virtual ~NcDbDynBlockTableRecord();
	NRXDBGATE_EXPORT bool isDynamicBlock () const;
	NRXDBGATE_EXPORT NcDbObjectId blockTableRecordId() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getAnonymousBlockIds
	                            (NcDbObjectIdArray& anonymousIds) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus updateAnonymousBlocks() const;
private:
	NcDbDynBlockTableRecord();
};

//////////////////////////////////////////////////////////////////////////
// NcDbEvalIdMap
class NcDbEvalIdMap {
public:
	virtual NcDbEvalNodeId find(const NcDbEvalNodeId& key) = 0;
	virtual void kill() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbEvalGraph
class NRXDBGATE_EXPORT NcDbEvalGraph : public NcDbObject {
public:
	enum NodeId {
		kNullNodeId = 0
	};
	NCDB_DECLARE_MEMBERS(NcDbEvalGraph);
	NcDbEvalGraph();
	virtual ~NcDbEvalGraph();
	static bool hasGraph(const NcDbObject*    pObj,
	                     const NCHAR*          pKey);
	static Nano::ErrorStatus getGraph(const NcDbObject*    pObj,
	                                  const NCHAR*          pKey,
	                                  NcDbEvalGraph**      pGraph,
	                                  const NcDb::OpenMode mode);
	static Nano::ErrorStatus createGraph(NcDbObject* pObj,
	                                     const NCHAR* pKey);
	static Nano::ErrorStatus removeGraph(NcDbObject* pObj,
	                                     const NCHAR* pKey);
	static bool hasGraph(NcDbDatabase*        pDb,
	                     const NCHAR*          pKey);
	static Nano::ErrorStatus getGraph(NcDbDatabase*        pDb,
	                                  const NCHAR*          pKey,
	                                  NcDbEvalGraph**      pGraph,
	                                  const NcDb::OpenMode mode);
	static Nano::ErrorStatus createGraph(NcDbDatabase* pDb,
	                                     const NCHAR*   pKey);
	static Nano::ErrorStatus removeGraph(NcDbDatabase* pDb,
	                                     const NCHAR*   pKey);
	static Nano::ErrorStatus replaceGraph(NcDbObject* pObj,
	                                      const NCHAR* pKey,
	                                      NcDbObjectId grphId);
	virtual Nano::ErrorStatus addNode     (NcDbEvalExpr*   pNode,
	                                       NcDbEvalNodeId& id);
	virtual Nano::ErrorStatus removeNode  (const NcDbEvalNodeId& id);
	virtual Nano::ErrorStatus removeNode  (NcDbEvalExpr* pNode);
	virtual Nano::ErrorStatus getAllNodes (NcDbEvalNodeIdArray& nodes) const;
	virtual Nano::ErrorStatus getNode     (const NcDbEvalNodeId& nodeId,
	                                       NcDb::OpenMode        mode,
	                                       NcDbObject**        ppNode) const;
	virtual Nano::ErrorStatus addEdge(const NcDbEvalNodeId& idFrom,
	                                  const NcDbEvalNodeId& idTo);
	virtual Nano::ErrorStatus addEdge(const NcDbEvalNodeId& idFrom,
	                                  const NcDbEvalNodeId& idTo,
	                                  bool  bInvertible);
	virtual Nano::ErrorStatus removeEdge(const NcDbEvalNodeId& idFrom,
	                                     const NcDbEvalNodeId& idTo);
	virtual Nano::ErrorStatus getIncomingEdges(const NcDbEvalNodeId& nodeId,
	                                           NcDbEvalEdgeInfoArray& edges) const;
	virtual Nano::ErrorStatus getOutgoingEdges(const NcDbEvalNodeId& nodeId,
	                                           NcDbEvalEdgeInfoArray& edges) const;
	virtual Nano::ErrorStatus getEdgeInfo(const NcDbEvalNodeId& nodeFrom,
	                                      const NcDbEvalNodeId& nodeTo, NcDbEvalEdgeInfo& einfo) const;
	virtual Nano::ErrorStatus addGraph(NcDbEvalGraph* pGraphToAdd,
	                                   NcDbEvalIdMap*& idMap);
	virtual Nano::ErrorStatus evaluate() const;
	virtual Nano::ErrorStatus evaluate(
	        const NcDbEvalContext*     pContext) const;
	virtual Nano::ErrorStatus evaluate(
	        const NcDbEvalContext*     pContext,
	        const NcDbEvalNodeIdArray* activatedNodes) const;
	virtual Nano::ErrorStatus activate(
	        const NcDbEvalNodeIdArray& activatedNodes) const;
	virtual Nano::ErrorStatus activate(
	        const NcDbEvalNodeIdArray& activatedNodes,
	        NcDbEvalNodeIdArray*       pActiveSubgraph) const;
	virtual Nano::ErrorStatus activate(
	        const NcDbEvalNodeIdArray& activatedNodes,
	        NcDbEvalNodeIdArray*       pActiveSubgraph,
	        NcDbEvalNodeIdArray*       pCycleNodes) const;
	virtual Nano::ErrorStatus getIsActive(const NcDbEvalNodeId& id,
	                                      bool& bIsActive) const;
	virtual bool equals(const NcDbEvalGraph* pOther) const;
	virtual bool isSubgraphOf(const NcDbEvalGraph* pOther) const;
	virtual Nano::ErrorStatus postInDatabase(NcDbObjectId& objId, NcDbDatabase* pDb);
};

//////////////////////////////////////////////////////////////////////////
// NcDbEvalEdgeInfo
class NRXDBGATE_EXPORT NcDbEvalEdgeInfo {
public:
	NcDbEvalEdgeInfo()
	    : mFlags(0), mRefCount(0)
	{
		mIdFrom = NcDbEvalGraph::kNullNodeId;
		mIdTo = NcDbEvalGraph::kNullNodeId;
	}
	NcDbEvalEdgeInfo(NcDbEvalNodeId from,
	                 NcDbEvalNodeId to,
	                 NRX::Int32   flags,
	                 NRX::UInt32  count)
	    : mIdFrom(from), mIdTo(to), mFlags(flags), mRefCount(count)
	    {}
	NcDbEvalNodeId from () const;
	NcDbEvalNodeId to   () const;
	NRX::UInt32 refCount() const;
	bool isInvertible () const;
	bool isSuppressed  () const;
	bool operator == (const NcDbEvalEdgeInfo& other) const;
private:
	NcDbEvalNodeId mIdFrom;
	NcDbEvalNodeId mIdTo;
	NRX::Int32 mFlags;
	NRX::UInt32 mRefCount;
};

//////////////////////////////////////////////////////////////////////////
// NcDbEvalExpr
class NRXDBGATE_EXPORT NcDbEvalExpr : public NcDbObject {
public:
	NCDB_DECLARE_MEMBERS(NcDbEvalExpr);
	NcDbEvalExpr();
	virtual ~NcDbEvalExpr();
	Nano::ErrorStatus getGraph(NcDbEvalGraph** pGraph,
	                           NcDb::OpenMode  mode) const;
	NcDbEvalNodeId    nodeId() const;
	virtual void addedToGraph       (NcDbEvalGraph*  pGraph);
	virtual void removedFromGraph   (NcDbEvalGraph*  pGraph);
	virtual void adjacentNodeRemoved (const NcDbEvalNodeId& adjNodeId);
	virtual void adjacentEdgeRemoved (const NcDbEvalNodeId& adjEdgeNodeId);
	virtual void adjacentEdgeAdded (const NcDbEvalNodeId& fromId,
	                                const NcDbEvalNodeId& toId,
	                                bool bIsInvertible);
	virtual void movedFromGraph (NcDbEvalGraph* pFromGraph);
	virtual void movedIntoGraph (NcDbEvalGraph* pIntoGraph);
	virtual void remappedNodeIds (NcDbEvalIdMap& idMap);
	virtual void copiedIntoGraph(NcDbEvalGraph* pIntoGraph);
	virtual bool isActivatable  ();
	virtual void activated           (NcDbEvalNodeIdArray& argumentActiveList);
	virtual void graphEvalStart      (bool bNodeIsActive);
	virtual void graphEvalEnd        (bool bNodeIsActive);
	virtual void graphEvalAbort      (bool bNodeIsActive);
	virtual Nano::ErrorStatus evaluate(const NcDbEvalContext* ctxt);
	virtual bool equals(const NcDbEvalExpr* pOther) const;
	NcDbEvalVariant value() const;
	virtual Nano::ErrorStatus postInDatabase(NcDbObjectId& objId, NcDbDatabase* pDb);
protected:
	NcDbEvalVariant m_lastValue;
};

//////////////////////////////////////////////////////////////////////////
// NcDbEvalConnectable
class NRXDBGATE_EXPORT NcDbEvalConnectable : public NcDbEvalExpr {
public:
	NCDB_DECLARE_MEMBERS(NcDbEvalConnectable);
	virtual ~NcDbEvalConnectable();
	virtual Nano::ErrorStatus getConnectionNames (NcStringArray& names) const;
	virtual bool              hasConnectionNamed (const NcString& name) const;
	virtual Nano::ErrorStatus getConnectionType  (
	                                const NcString&        name,
	                                NcDb::DwgDataType& type) const;
	virtual Nano::ErrorStatus getConnectionValue (
	                                const NcString&    name,
	                                NcDbEvalVariant&    value) const;
	virtual Nano::ErrorStatus setConnectionValue (
	                                const NcString&       name,
	                                const NcDbEvalVariant& value);
	virtual Nano::ErrorStatus connectTo (
	                            const NcString&      thisConnection,
	                            const NcDbEvalNodeId sourceConnectableId,
	                            const NcString&      sourceConnectionName);
	virtual Nano::ErrorStatus disconnectFrom (
	                            const NcString&      thisConnection,
	                            const NcDbEvalNodeId sourceConnectableId,
	                            const NcString&      sourceConnectionName);
	virtual bool connectionAllowed (
	                        const NcString&      thisConnection,
	                        const NcDbEvalNodeId sourceConnectableId,
	                        const NcString&      sourceConnectionName) const;
	virtual Nano::ErrorStatus getConnectedObjects (
	                            const NcString&      thisConnection,
	                            NcDbEvalNodeIdArray& connectedObjects) const;
	virtual Nano::ErrorStatus getConnectedNames (
	                            const NcString&      thisConnection,
	                            const NcDbEvalNodeId sourceConnectableId,
	                            NcStringArray&       sourceConnectionNames) const;
protected:
	NcDbEvalConnectable();
};

//////////////////////////////////////////////////////////////////////////
// NcDbEvalContext
class NRXDBGATE_EXPORT NcDbEvalContext : public NcRxObject, public NcHeapOperators {
public:
	NcDbEvalContext();
	virtual ~NcDbEvalContext();
	NCRX_DECLARE_MEMBERS(NcDbEvalContext);
	virtual void        insertAt (const NcDbEvalContextPair& pair);
	virtual void        removeAt (const NCHAR*                szKey);
	virtual Nano::ErrorStatus getAt (NcDbEvalContextPair& pair) const;
	virtual NcDbEvalContextIterator* newIterator() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbEvalContextPair
class NRXDBGATE_EXPORT NcDbEvalContextPair : public NcHeapOperators {
public:
	NcDbEvalContextPair();
	NcDbEvalContextPair(const NCHAR* szKey, void *pValue);
	virtual ~NcDbEvalContextPair();
	void        setKey   (const NCHAR* szKey);
	const NCHAR* key      () const;
	void        setValue (void* pValue);
	void*       value    () const;
private:
	NCHAR* mKey;
	void* mValue;
};

//////////////////////////////////////////////////////////////////////////
// NcDbEvalContextIterator
class NRXDBGATE_EXPORT NcDbEvalContextIterator : public NcRxObject, public NcHeapOperators {
public:
	NcDbEvalContextIterator();
	virtual ~NcDbEvalContextIterator();
	NCRX_DECLARE_MEMBERS(NcDbEvalContextIterator);
	virtual void   start();
	virtual bool   next();
	virtual bool   done() const;
	virtual NcDbEvalContextPair contextPair() const;
private:
	NcDbEvalContextIterator(NcDbEvalContext* pContext);
};

//////////////////////////////////////////////////////////////////////////
// NcDbExtrudedSurface
class NRXDBGATE_EXPORT NcDbExtrudedSurface: public NcDbSurface {
public:
	NcDbExtrudedSurface ();
	NcDbExtrudedSurface::NcDbExtrudedSurface(OdRxObject* _object);
	virtual ~NcDbExtrudedSurface();
	NCDB_DECLARE_MEMBERS(NcDbExtrudedSurface);
	virtual Nano::ErrorStatus createExtrudedSurface ( NcDbEntity* pSweepEnt,
	                                                 const NcGeVector3d& directionVec, NcDbSweepOptions& sweepOptions );
	NcDbEntity*    getSweepEntity () const;
	NcDb3dProfile* sweepProfile () const;
	NcGeVector3d       getSweepVec () const;
	Nano::ErrorStatus  setSweepVec ( const NcGeVector3d& sweepVec );
	double             getHeight () const;
	Nano::ErrorStatus  setHeight ( double height );
	void               getSweepOptions ( NcDbSweepOptions& sweepOptions ) const;
	Nano::ErrorStatus  setSweepOptions ( const NcDbSweepOptions& sweepOptions );
	Nano::ErrorStatus  setExtrude ( const NcGeVector3d& sweepVec,
	                               const NcDbSweepOptions& sweepOptions );
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;
	virtual bool isDependent () const;
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbFcf
class NRXDBGATE_EXPORT NcDbFcf: public  NcDbEntity {
public:
	NCDB_DECLARE_MEMBERS(NcDbFcf);
	                          NcDbFcf();
	                          NcDbFcf(const NCHAR *, const NcGePoint3d&,
	                                  const NcGeVector3d&, const NcGeVector3d&);
	virtual ~NcDbFcf();
	enum whichLine {kAll = -1};
	virtual void              setText          (const NCHAR *);
	virtual NCHAR *           text             (const int lineNo = kAll) const;
	virtual void              setLocation      (const NcGePoint3d&);
	virtual NcGePoint3d       location         () const;
	virtual void              setOrientation   (const NcGeVector3d& norm,
	                                            const NcGeVector3d& dir);
	virtual NcGeVector3d normal()    const;
	virtual NcGeVector3d direction() const;
	virtual void getBoundingPoints(NcGePoint3dArray&) const;
	virtual void getBoundingPline(NcGePoint3dArray&)  const;
	virtual void              setDimensionStyle(NcDbHardPointerId);
	virtual NcDbHardPointerId dimensionStyle() const;
	Nano::ErrorStatus   getDimstyleData(NcDbDimStyleTableRecord*& pRecord) const;
	Nano::ErrorStatus   setDimstyleData(NcDbDimStyleTableRecord* pNewData);
	Nano::ErrorStatus   setDimstyleData(NcDbObjectId newDataId);
	virtual void        setDimVars();
	NcCmColor      dimclrd () const;
	NcCmColor      dimclrt () const;
	double         dimgap  () const;
	double         dimscale() const;
	NcDbObjectId   dimtxsty() const;
	double         dimtxt  () const;
	Nano::ErrorStatus setDimclrd (NcCmColor&     val);
	Nano::ErrorStatus setDimclrt (NcCmColor&     val);
	Nano::ErrorStatus setDimgap  (double         val);
	Nano::ErrorStatus setDimscale(double         val);
	Nano::ErrorStatus setDimtxsty(NcDbObjectId   val);
	Nano::ErrorStatus setDimtxt  (double         val);
protected:
	virtual Nano::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbFilter
class NRXDBGATE_EXPORT NcDbFilter: public NcDbObject { // OdDbFilter
public:
	NCDB_DECLARE_MEMBERS(NcDbFilter);
	     NcDbFilter();
	virtual ~NcDbFilter();
	virtual NcRxClass* indexClass() const;
};


//////////////////////////////////////////////////////////////////////////
// NcDbLayerFilter
class NRXDBGATE_EXPORT NcDbLayerFilter: public  NcDbFilter  { // OdDbLayerFilter
public:
	NCDB_DECLARE_MEMBERS(NcDbLayerFilter);
	         NcDbLayerFilter();
	virtual ~NcDbLayerFilter();
	virtual NcRxClass* indexClass() const;
	virtual NRX::Boolean isValid() const;
	Nano::ErrorStatus add(const NCHAR * pLayer);
	Nano::ErrorStatus remove(const NCHAR * pLayer);
	Nano::ErrorStatus getAt(int index, const NCHAR *& pName) const;
	int layerCount() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSpatialFilter
class NRXDBGATE_EXPORT NcDbSpatialFilter: public  NcDbFilter {
public:
	NCDB_DECLARE_MEMBERS(NcDbSpatialFilter);
	     NcDbSpatialFilter();
	virtual ~NcDbSpatialFilter();
	virtual NcRxClass* indexClass() const;
	virtual void queryBounds(NcDbExtents& ext,
	                         const NcDbBlockReference * pRefBlkRef) const;
	NcDbSpatialFilter(const NcGePoint2dArray& pts,
	                  const NcGeVector3d&     normal,
	                  double                  elevation,
	                  double                  frontClip,
	                  double                  backClip,
	                  NRX::Boolean          enabled);
	void queryBounds(NcDbExtents& ext) const;
	Nano::ErrorStatus  getVolume(NcGePoint3d&  fromPt,
	                             NcGePoint3d&  toPt,
	                             NcGeVector3d& upDir,
	                             NcGeVector2d& viewField) const;
	Nano::ErrorStatus setDefinition(const NcGePoint2dArray& pts,
	                                const NcGeVector3d&     normal,
	                                double                  elevation,
	                                double                  frontClip,
	                                double                  backClip,
	                                NRX::Boolean          enabled);
	Nano::ErrorStatus getDefinition(NcGePoint2dArray& pts,
	                                NcGeVector3d&     normal,
	                                double&           elevation,
	                                double&           frontClip,
	                                double&           backClip,
	                                NRX::Boolean&   enabled) const;
	NcGeMatrix3d& getClipSpaceToWCSMatrix(NcGeMatrix3d& mat) const;
	NcGeMatrix3d& getOriginalInverseBlockXform(NcGeMatrix3d& mat) const;
	Nano::ErrorStatus setPerspectiveCamera(const NcGePoint3d& fromPt);
	NRX::Boolean    clipVolumeIntersectsExtents(const NcDbExtents& ext) const;
	NRX::Boolean    hasPerspectiveCamera() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbLinkedData
class NRXDBGATE_EXPORT NcDbLinkedData : public NcDbObject {
public:
	NCDB_DECLARE_MEMBERS(NcDbLinkedData);
	NcDbLinkedData(void);
	virtual ~NcDbLinkedData(void);
	virtual Nano::ErrorStatus clear(void);
	virtual bool isEmpty          (void) const;
	virtual const NCHAR* name     (void) const;
	virtual Nano::ErrorStatus setName(const NCHAR* pszName);
	virtual const NCHAR* description(void) const;
	virtual Nano::ErrorStatus setDescription(const NCHAR* pszDescription);
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbLinkedTableData
class NRXDBGATE_EXPORT NcDbLinkedTableData : public NcDbLinkedData {
public:
	NCDB_DECLARE_MEMBERS(NcDbLinkedTableData);
	NcDbLinkedTableData(void);
	virtual ~NcDbLinkedTableData(void);
	virtual Nano::ErrorStatus clear(void);
	virtual Nano::ErrorStatus copyFrom(const NcDbLinkedTableData* pSrc,
	                                   NcDb::TableCopyOption nOption);
	virtual Nano::ErrorStatus copyFrom(const NcDbLinkedTableData* pSrc,
	                                   NcDb::TableCopyOption nOption,
	                                   const NcCellRange& srcRange,
	                                   const NcCellRange& targetRange,
	                                   NcCellRange* pNewTargetRange);
	NcDbTableIterator* getIterator(void) const;
	NcDbTableIterator* getIterator(const NcCellRange* pRange,
	                               NcDb::TableIteratorOption nOption) const;
	virtual Nano::ErrorStatus setSize(int nRows, int nCols);
	virtual int numColumns        (void) const;
	virtual const NCHAR* getColumnName(int nIndex) const;
	virtual Nano::ErrorStatus setColumnName(int nIndex,
	                                        const NCHAR* pszName);
	virtual int appendColumn      (int nNumCols);
	virtual int insertColumn      (int nIndex,
	                               int nNumCols);
	virtual Nano::ErrorStatus deleteColumn(int nIndex,
	                                       int nNumColsToDelete);
	virtual int numRows           (void) const;
	virtual bool canInsert        (int nIndex,
	                               bool bRow) const;
	virtual int appendRow         (int nNumRows);
	virtual int insertRow         (int nIndex,
	                               int nNumRows);
	virtual bool canDelete        (int nIndex,
	                               int nCount,
	                               bool bRow) const;
	virtual Nano::ErrorStatus deleteRow(int nIndex,
	                                    int nNumRowsToDelete);
	virtual bool isContentEditable(int nRow,
	                               int nCol) const;
	virtual NcDb::CellState cellState(int nRow,
	                                  int nCol) const;
	virtual Nano::ErrorStatus setCellState(int nRow,
	                                       int nCol,
	                                       NcDb::CellState nCellState);
	virtual NcString getToolTip   (int nRow,
	                               int nCol) const;
	virtual Nano::ErrorStatus setToolTip(int nRow,
	                                     int nCol,
	                                     const NCHAR* pszToolTip);
	virtual int getCustomData     (int nRow,
	                               int nCol) const;
	virtual Nano::ErrorStatus setCustomData(int nRow,
	                                        int nCol,
	                                        int nData);
	virtual Nano::ErrorStatus getCustomData(int nRow,
	                                        int nCol,
	                                        const NCHAR* pszKey,
	                                        NcValue* pData) const;
	virtual Nano::ErrorStatus setCustomData(int nRow,
	                                        int nCol,
	                                        const NCHAR* pszKey,
	                                        const NcValue* pData);
	virtual bool isLinked         (int nRow,
	                               int nCol) const;
	virtual NcDbObjectId getDataLink(int nRow,
	                                 int nCol) const;
	virtual Nano::ErrorStatus getDataLink(int nRow,
	                                      int nCol,
	                                      NcDbDataLink*& pDataLink,
	                                      NcDb::OpenMode mode) const;
	virtual int getDataLink       (const NcCellRange* pRange,
	                               NcDbObjectIdArray& dataLinkIds) const;
	virtual Nano::ErrorStatus setDataLink(int nRow,
	                                      int nCol,
	                                      const NcDbObjectId& idDataLink,
	                                      bool bUpdate);
	virtual Nano::ErrorStatus setDataLink(const NcCellRange& range,
	                                      const NcDbObjectId& idDataLink,
	                                      bool bUpdate);
	virtual NcCellRange getDataLinkRange(int nRow,
	                                     int nCol) const;
	virtual Nano::ErrorStatus removeDataLink(int nRow,
	                                         int nCol);
	virtual Nano::ErrorStatus removeDataLink(void);
	virtual Nano::ErrorStatus updateDataLink(int nRow,
	                                         int nCol,
	                                         NcDb::UpdateDirection nDir,
	                                         NcDb::UpdateOption nOption);
	virtual Nano::ErrorStatus updateDataLink(NcDb::UpdateDirection nDir,
	                                         NcDb::UpdateOption nOption);
	virtual int numContents       (int nRow,
	                               int nCol) const;
	virtual int createContent     (int nRow,
	                               int nCol,
	                               int nIndex);
	virtual Nano::ErrorStatus moveContent(int nRow,
	                                      int nCol,
	                                      int nFromIndex,
	                                      int nToIndex);
	virtual Nano::ErrorStatus deleteContent(int nRow,
	                                        int nCol,
	                                        int nContent);
	virtual Nano::ErrorStatus deleteContent(int nRow,
	                                        int nCol);
	virtual Nano::ErrorStatus deleteContent(const NcCellRange& range);
	virtual NcDb::CellContentType contentType(int nRow,
	                                          int nCol) const;
	virtual NcDb::CellContentType contentType(int nRow,
	                                          int nCol,
	                                          int nContent) const;
	virtual Nano::ErrorStatus getDataType(int nRow,
	                                      int nCol,
	                                      NcValue::DataType& nDataType,
	                                      NcValue::UnitType& nUnitType) const;
	virtual Nano::ErrorStatus getDataType(int nRow,
	                                      int nCol,
	                                      int nContent,
	                                      NcValue::DataType& nDataType,
	                                      NcValue::UnitType& nUnitType) const;
	virtual Nano::ErrorStatus setDataType(int nRow,
	                                      int nCol,
	                                      NcValue::DataType nDataType,
	                                      NcValue::UnitType nUnitType);
	virtual Nano::ErrorStatus setDataType(int nRow,
	                                      int nCol,
	                                      int nContent,
	                                      NcValue::DataType nDataType,
	                                      NcValue::UnitType nUnitType);
	virtual NcString dataFormat   (int nRow,
	                               int nCol) const;
	virtual NcString dataFormat   (int nRow,
	                               int nCol,
	                               int nContent) const;
	virtual Nano::ErrorStatus setDataFormat(int nRow,
	                                        int nCol,
	                                        const NCHAR* pszFormat);
	virtual Nano::ErrorStatus setDataFormat(int nRow,
	                                        int nCol,
	                                        int nContent,
	                                        const NCHAR* pszFormat);
	virtual Nano::ErrorStatus getValue(int nRow,
	                                   int nCol,
	                                   NcValue& value) const;
	virtual Nano::ErrorStatus getValue(int nRow,
	                                   int nCol,
	                                   int nContent,
	                                   NcValue::FormatOption nOption,
	                                   NcValue& value) const;
	virtual Nano::ErrorStatus setValue(int nRow,
	                                   int nCol,
	                                   const NcValue& value);
	virtual Nano::ErrorStatus setValue(int nRow,
	                                   int nCol,
	                                   int nContent,
	                                   const NcValue& value);
	virtual Nano::ErrorStatus setValue(int nRow,
	                                   int nCol,
	                                   int nContent,
	                                   const NcValue& value,
	                                   NcValue::ParseOption nOption);
	virtual NcString getText      (int nRow,
	                               int nCol) const;
	virtual NcString getText      (int nRow,
	                               int nCol,
	                               int nContent) const;
	virtual NcString getText      (int nRow,
	                               int nCol,
	                               int nContent,
	                               NcValue::FormatOption nOption) const;
	virtual Nano::ErrorStatus setText(int nRow,
	                                  int nCol,
	                                  const NCHAR* pszText);
	virtual Nano::ErrorStatus setText(int nRow,
	                                  int nCol,
	                                  int nContent,
	                                  const NCHAR* pszText);
	virtual bool hasFormula       (int nRow,
	                               int nCol,
	                               int nContent) const;
	virtual NcString getFormula   (int nRow,
	                               int nCol,
	                               int nContent) const;
	virtual Nano::ErrorStatus setFormula(int nRow,
	                                     int nCol,
	                                     int nContent,
	                                     const NCHAR* pszFormula);
	virtual NcDbObjectId getFieldId(int nRow,
	                                int nCol) const;
	virtual NcDbObjectId getFieldId(int nRow,
	                                int nCol,
	                                int nContent) const;
	virtual Nano::ErrorStatus setFieldId(int nRow,
	                                     int nCol,
	                                     const NcDbObjectId& idField);
	virtual Nano::ErrorStatus setFieldId(int nRow,
	                                     int nCol,
	                                     int nContent,
	                                     const NcDbObjectId& idField);
	virtual Nano::ErrorStatus getField(int nRow,
	                                   int nCol,
	                                   int nContent,
	                                   NcDbField*& pField,
	                                   NcDb::OpenMode mode) const;
	virtual NcDbObjectId getBlockTableRecordId(int nRow,
	                                           int nCol) const;
	virtual NcDbObjectId getBlockTableRecordId(int nRow,
	                                           int nCol,
	                                           int nContent) const;
	virtual Nano::ErrorStatus setBlockTableRecordId(int nRow,
	                                                int nCol,
	                                                const NcDbObjectId& idBTR);
	virtual Nano::ErrorStatus setBlockTableRecordId(int nRow,
	                                                int nCol,
	                                                int nContent,
	                                                const NcDbObjectId& idBTR);
	virtual NcString getBlockAttributeValue(int nRow,
	                                        int nCol,
	                                        const NcDbObjectId& idAttDef) const;
	virtual NcString getBlockAttributeValue(int nRow,
	                                        int nCol,
	                                        int nContent,
	                                        const NcDbObjectId& idAttDef) const;
	virtual Nano::ErrorStatus setBlockAttributeValue(int nRow,
	                                                 int nCol,
	                                                 const NcDbObjectId& idAttDef,
	                                                 const NCHAR* pszAttValue);
	virtual Nano::ErrorStatus setBlockAttributeValue(int nRow,
	                                                 int nCol,
	                                                 int nContent,
	                                                 const NcDbObjectId& idAttDef,
	                                                 const NCHAR* pszAttValue);
	virtual Nano::ErrorStatus evaluateFormula(void);
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbFormattedTableData
class NRXDBGATE_EXPORT NcDbFormattedTableData : public NcDbLinkedTableData {
public:
	NCDB_DECLARE_MEMBERS(NcDbFormattedTableData);
	NcDbFormattedTableData(void);
	~NcDbFormattedTableData(void);
	virtual int insertRowAndInherit(int nIndex,
	                                int nInheritFrom,
	                                int nNumRows);
	virtual int insertColumnAndInherit(int nIndex,
	                                   int nInheritFrom,
	                                   int nNumCols);
	virtual Nano::ErrorStatus setFieldId(int nRow,
	                                     int nCol,
	                                     const NcDbObjectId& idField,
	                                     NcDb::CellOption nFlag);
	virtual Nano::ErrorStatus setFieldId(int nRow,
	                                     int nCol,
	                                     int nIndex,
	                                     const NcDbObjectId& idField,
	                                     NcDb::CellOption nFlag);
	virtual Nano::ErrorStatus merge(const NcCellRange& range);
	virtual Nano::ErrorStatus unmerge(const NcCellRange& range);
	virtual bool isMerged         (int nRow,
	                               int nCol) const;
	virtual NcCellRange getMergeRange(int nRow,
	                                  int nCol) const;
	virtual bool isFormatEditable (int nRow,
	                               int nCol) const;
	virtual double rotation       (int nRow,
	                               int nCol) const;
	virtual double rotation       (int nRow,
	                               int nCol,
	                               int nIndex) const;
	virtual Nano::ErrorStatus setRotation(int nRow,
	                                      int nCol,
	                                      double fRotation);
	virtual Nano::ErrorStatus setRotation(int nRow,
	                                      int nCol,
	                                      int nContent,
	                                      double fRotation);
	virtual double scale          (int nRow,
	                               int nCol) const;
	virtual double scale          (int nRow,
	                               int nCol,
	                               int nContent) const;
	virtual Nano::ErrorStatus setScale(int nRow,
	                                   int nCol,
	                                   double fScale);
	virtual Nano::ErrorStatus setScale(int nRow,
	                                   int nCol,
	                                   int nIndex,
	                                   double fScale);
	virtual bool isAutoScale      (int nRow,
	                               int nCol) const;
	virtual bool isAutoScale      (int nRow,
	                               int nCol,
	                               int nContent) const;
	virtual Nano::ErrorStatus setAutoScale(int nRow,
	                                       int nCol,
	                                       bool bAutoScale);
	virtual Nano::ErrorStatus setAutoScale(int nRow,
	                                       int nCol,
	                                       int nContent,
	                                       bool bAutoScale);
	virtual NcDb::CellAlignment alignment(int nRow,
	                                      int nCol) const;
	virtual Nano::ErrorStatus setAlignment(int nRow,
	                                       int nCol,
	                                       NcDb::CellAlignment nAlignment);
	virtual NcCmColor contentColor(int nRow,
	                               int nCol) const;
	virtual NcCmColor contentColor(int nRow,
	                               int nCol,
	                               int nContent) const;
	virtual Nano::ErrorStatus setContentColor(int nRow,
	                                          int nCol,
	                                          const NcCmColor& color);
	virtual Nano::ErrorStatus setContentColor(int nRow,
	                                          int nCol,
	                                          int nContent,
	                                          const NcCmColor& color);
	virtual NcDbObjectId textStyle(int nRow,
	                               int nCol) const;
	virtual NcDbObjectId textStyle(int nRow,
	                               int nCol,
	                               int nContent) const;
	virtual Nano::ErrorStatus setTextStyle(int nRow,
	                                       int nCol,
	                                       const NcDbObjectId& idTextStyle);
	virtual Nano::ErrorStatus setTextStyle(int nRow,
	                                       int nCol,
	                                       int nContent,
	                                       const NcDbObjectId& idTextStyle);
	virtual double textHeight     (int nRow,
	                               int nCol) const;
	virtual double textHeight     (int nRow,
	                               int nCol,
	                               int nContent) const;
	virtual Nano::ErrorStatus setTextHeight(int nRow,
	                                        int nCol,
	                                        double fTextHeight);
	virtual Nano::ErrorStatus setTextHeight(int nRow,
	                                        int nCol,
	                                        int nContent,
	                                        double fTextHeight);
	virtual NcCmColor backgroundColor(int nRow,
	                                  int nCol) const;
	virtual Nano::ErrorStatus setBackgroundColor(int nRow,
	                                             int nCol,
	                                             const NcCmColor& color);
	virtual NcDb::CellContentLayout contentLayout(int nRow,
	                                              int nCol) const;
	virtual Nano::ErrorStatus setContentLayout(int nRow,
	                                           int nCol,
	                                           NcDb::CellContentLayout nLayout);
	virtual NcDb::FlowDirection flowDirection(void) const;
	virtual Nano::ErrorStatus setFlowDirection(NcDb::FlowDirection nDir);
	virtual double margin         (int nRow,
	                               int nCol,
	                               NcDb::CellMargin nMargin) const;
	virtual Nano::ErrorStatus setMargin(int nRow,
	                                    int nCol,
	                                    NcDb::CellMargin nMargins,
	                                    double fMargin);
	virtual bool isMergeAllEnabled(int nRow,
	                               int nCol) const;
	virtual Nano::ErrorStatus enableMergeAll(int nRow,
	                                         int nCol,
	                                         bool bEnable);
	virtual NcDb::GridLineStyle gridLineStyle(int nRow,
	                                          int nCol,
	                                          NcDb::GridLineType nGridLineType) const;
	virtual Nano::ErrorStatus setGridLineStyle(int nRow,
	                                           int nCol,
	                                           NcDb::GridLineType nGridLineTypes,
	                                           NcDb::GridLineStyle nLineStyle);
	virtual NcDb::LineWeight gridLineWeight(int nRow,
	                                        int nCol,
	                                        NcDb::GridLineType nGridLineType) const;
	virtual Nano::ErrorStatus setGridLineWeight(int nRow,
	                                            int nCol,
	                                            NcDb::GridLineType nGridLineTypes,
	                                            NcDb::LineWeight nLineWeight);
	virtual NcDbObjectId gridLinetype(int nRow,
	                                  int nCol,
	                                  NcDb::GridLineType nGridLineType) const;
	virtual Nano::ErrorStatus setGridLinetype(int nRow,
	                                          int nCol,
	                                          NcDb::GridLineType nGridLineTypes,
	                                          const NcDbObjectId& idLinetype);
	virtual NcCmColor gridColor   (int nRow,
	                               int nCol,
	                               NcDb::GridLineType nGridLineType) const;
	virtual Nano::ErrorStatus setGridColor(int nRow,
	                                       int nCol,
	                                       NcDb::GridLineType nGridLineTypes,
	                                       const NcCmColor& color);
	virtual NcDb::Visibility gridVisibility(int nRow,
	                                        int nCol,
	                                        NcDb::GridLineType nGridLineType) const;
	virtual Nano::ErrorStatus setGridVisibility(int nRow,
	                                            int nCol,
	                                            NcDb::GridLineType nGridLineTypes,
	                                            NcDb::Visibility nVisibility);
	virtual double gridDoubleLineSpacing(int nRow,
	                                     int nCol,
	                                     NcDb::GridLineType nGridLineType) const;
	virtual Nano::ErrorStatus setGridDoubleLineSpacing(int nRow,
	                                                   int nCol,
	                                                   NcDb::GridLineType nGridLineTypes,
	                                                   double fSpacing);
	virtual Nano::ErrorStatus getGridProperty(int nRow,
	                                          int nCol,
	                                          NcDb::GridLineType nGridLineType,
	                                          NcGridProperty& gridProp) const;
	virtual Nano::ErrorStatus setGridProperty(int nRow,
	                                          int nCol,
	                                          NcDb::GridLineType nGridLineTypes,
	                                          const NcGridProperty& gridProp);
	virtual Nano::ErrorStatus setGridProperty(const NcCellRange& range,
	                                          NcDb::GridLineType nGridLineTypes,
	                                          const NcGridProperty& gridProp);
	virtual NcDb::CellProperty getOverride(int nRow,
	                                       int nCol,
	                                       int nContent) const;
	virtual NcDb::GridProperty getOverride(int nRow,
	                                       int nCol,
	                                       NcDb::GridLineType nGridLineType) const;
	virtual Nano::ErrorStatus setOverride(int nRow,
	                                      int nCol,
	                                      int nContent,
	                                      NcDb::CellProperty nOverride);
	virtual Nano::ErrorStatus setOverride(int nRow,
	                                      int nCol,
	                                      NcDb::GridLineType nGridLineType,
	                                      NcDb::GridProperty nOverride);
	virtual Nano::ErrorStatus removeAllOverrides(int nRow,
	                                             int nCol);
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbFrame
class NRXDBGATE_EXPORT NRX_NO_VTABLE NcDbFrame: public NcDbEntity {
protected:
	NcDbFrame();
public:
	NCDB_DECLARE_MEMBERS(NcDbFrame);
	virtual ~NcDbFrame();
};

//////////////////////////////////////////////////////////////////////////
// NcDbGeoData
class NcDbGeoData : public NcDbObject {
public:
	enum TypeOfCoordinates
	{
		kCoordTypUnknown = 0,
		kCoordTypLocal,
		kCoordTypGrid,
		kCoordTypGeographic
	};
	enum ScaleEstimationMethod {
		kScaleEstMethodUnity = 1,
		kScaleEstMethodUserDefined,
		kScaleEstMethodReferencePoint,
		kScaleEstMethodPrismoidal
	};
	NCDB_DECLARE_MEMBERS(NcDbGeoData);
	NRXDBGATE_EXPORT NcDbGeoData();
	NRXDBGATE_EXPORT virtual ~NcDbGeoData();
	NRXDBGATE_EXPORT NcDbObjectId blockTableRecordId() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setBlockTableRecordId(const NcDbObjectId& blockId);
	NRXDBGATE_EXPORT Nano::ErrorStatus postToDb(NcDbObjectId& objId);
	NRXDBGATE_EXPORT Nano::ErrorStatus eraseFromDb(void);
	NRXDBGATE_EXPORT TypeOfCoordinates coordinateType() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setCoordinateType(TypeOfCoordinates designCoordinateType);
	NRXDBGATE_EXPORT NcGePoint3d designPoint() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setDesignPoint(const NcGePoint3d& point);
	NRXDBGATE_EXPORT NcGePoint3d referencePoint() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setReferencePoint(const NcGePoint3d& point);
	NRXDBGATE_EXPORT double horizontalUnitScale() const;
	NRXDBGATE_EXPORT NcDb::UnitsValue horizontalUnits () const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setHorizontalUnitScale(double horzUnitScale);
	NRXDBGATE_EXPORT Nano::ErrorStatus setHorizontalUnits (NcDb::UnitsValue horizUnits);
	NRXDBGATE_EXPORT double verticalUnitScale() const;
	NRXDBGATE_EXPORT NcDb::UnitsValue verticalUnits () const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setVerticalUnitScale(double vertUnitScale);
	NRXDBGATE_EXPORT Nano::ErrorStatus setVerticalUnits(NcDb::UnitsValue vertUnits);
	NRXDBGATE_EXPORT const NCHAR* coordinateSystem() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setCoordinateSystem(const NCHAR* coordinateSystem);
	typedef bool (*NCDBGEODATA_VALIDATE_CS)(const NCHAR* coordinateSystem);
	static NRXDBGATE_EXPORT Nano::ErrorStatus setValidateCoordinateSystemCallback(NCDBGEODATA_VALIDATE_CS pFuncValidateCs);
	static NRXDBGATE_EXPORT NCDBGEODATA_VALIDATE_CS getValidateCoordinateSystemCallback();
	NRXDBGATE_EXPORT NcGeVector3d upDirection() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setUpDirection(const NcGeVector3d& vec);
	NRXDBGATE_EXPORT double northDirection() const;
	NRXDBGATE_EXPORT NcGeVector2d northDirectionVector() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setNorthDirectionVector(const NcGeVector2d& north);
	NRXDBGATE_EXPORT ScaleEstimationMethod scaleEstimationMethod() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setScaleEstimationMethod(ScaleEstimationMethod value);
	NRXDBGATE_EXPORT double scaleFactor() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setScaleFactor(double value);
	NRXDBGATE_EXPORT bool doSeaLevelCorrection() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setDoSeaLevelCorrection(bool seaLevelCorrectionOn);
	NRXDBGATE_EXPORT double seaLevelElevation() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setSeaLevelElevation(double value);
	NRXDBGATE_EXPORT double coordinateProjectionRadius() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setCoordinateProjectionRadius(double value);
	NRXDBGATE_EXPORT const NCHAR* geoRSSTag() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setGeoRSSTag(const NCHAR* rssTag);
	NRXDBGATE_EXPORT const NCHAR* observationFrom() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setObservationFrom(const NCHAR* from);
	NRXDBGATE_EXPORT const NCHAR* observationTo() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setObservationTo(const NCHAR* to);
	NRXDBGATE_EXPORT const NCHAR* observationCoverage() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setObservationCoverage(const NCHAR* coverage);
	NRXDBGATE_EXPORT int numMeshPoints() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getMeshPointMap(int index, NcGePoint2d& sourcePt, NcGePoint2d& destPt) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getMeshPointMaps(NcGePoint2dArray& sourcePts, NcGePoint2dArray& destPts) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus addMeshPointMap(int index, const NcGePoint2d& sourcePt, const NcGePoint2d& destPt);
	NRXDBGATE_EXPORT Nano::ErrorStatus setMeshPointMaps(const NcGePoint2dArray& sourcePts, const NcGePoint2dArray& destPts);
	NRXDBGATE_EXPORT Nano::ErrorStatus resetMeshPointMaps();
	NRXDBGATE_EXPORT int numMeshFaces() const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getMeshFace(int faceIndex, int& p0, int& p1, int& p2) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus addMeshFace(int faceIndex, int p0, int p1,int p2);
	NRXDBGATE_EXPORT Nano::ErrorStatus updateTransformationMatrix();
	NRXDBGATE_EXPORT Nano::ErrorStatus transformToLonLatAlt(const NcGePoint3d& dwgPt,
	                                                        NcGePoint3d& geoPt) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus transformToLonLatAlt(double x,
	                                                        double y,
	                                                        double z,
	                                                        double& lon,
	                                                        double& lat,
	                                                        double& alt) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus transformFromLonLatAlt(const NcGePoint3d& geoPt,
	                                                          NcGePoint3d& dwgPt) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus transformFromLonLatAlt(double lon,
	                                                          double lat,
	                                                          double alt,
	                                                          double& x,
	                                                          double& y,
	                                                          double& z) const;
	typedef Nano::ErrorStatus (*NCDBGEODATA_GEOGRAPHICTODWG)(const NcDbGeoData* pGeoData,
	                                                         const double& dblLongitude,
	                                                         const double& dblLatitude,
	                                                         const double& dblAltitude,
	                                                         double& dblDwgX,
	                                                         double& dblDwgY,
	                                                         double& dblDwgZ );
	typedef Nano::ErrorStatus (*NCDBGEODATA_DWGTOGEOGRAPHIC)(const NcDbGeoData* pGeoData,
	                                                         const double& dblDwgX,
	                                                         const double& dblDwgY,
	                                                         const double& dblDwgZ,
	                                                         double& dblLongitude,
	                                                         double& dblLatitude,
	                                                         double& dblAltitude );
	static NRXDBGATE_EXPORT Nano::ErrorStatus setTransformCallbacks(const NCHAR* zoneDescription,
	                                                                NCDBGEODATA_GEOGRAPHICTODWG pFuncGeoToDwg,
	                                                                NCDBGEODATA_DWGTOGEOGRAPHIC pFuncDwgToGeo);
	static NRXDBGATE_EXPORT const NCHAR* getTransformCallbacks(NCDBGEODATA_GEOGRAPHICTODWG& pFuncGeoToDwg,
	                                                           NCDBGEODATA_DWGTOGEOGRAPHIC& pFuncDwgToGeo);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler*);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler*) const;
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler*);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler*) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbHelix
class NRXDBGATE_EXPORT NcDbHelix: public NcDbSpline {
public:
	enum ConstrainType {
		kTurnHeight = 0,
		kTurns      = 1,
		kHeight     = 2
	};
public:
	NCDB_DECLARE_MEMBERS(NcDbHelix);
	NcDbHelix();
	virtual ~NcDbHelix();
	Nano::ErrorStatus createHelix();
	virtual NcGePoint3d axisPoint() const;
	virtual Nano::ErrorStatus setAxisPoint(const NcGePoint3d &axisPoint,
	                                       const bool bMoveStartPoint = true);
	virtual NcGePoint3d startPoint() const;
	virtual Nano::ErrorStatus setStartPoint(const NcGePoint3d &startPoint);
	virtual NcGeVector3d axisVector() const;
	virtual Nano::ErrorStatus setAxisVector(const NcGeVector3d &axisVector);
	virtual double height() const;
	virtual Nano::ErrorStatus setHeight(double dHeight);
	virtual double baseRadius() const;
	virtual Nano::ErrorStatus setBaseRadius(double dRadius);
	virtual double topRadius() const;
	virtual Nano::ErrorStatus setTopRadius(double dRadius);
	virtual double turns() const;
	virtual Nano::ErrorStatus setTurns(double dTurns);
	virtual double turnHeight() const;
	virtual Nano::ErrorStatus setTurnHeight(double dTurnHeight);
	virtual NRX::Boolean twist() const;
	virtual Nano::ErrorStatus setTwist(NRX::Boolean bTwist);
	virtual ConstrainType constrain() const;
	virtual Nano::ErrorStatus setConstrain(ConstrainType constrain);
	virtual double turnSlope() const;
	virtual double totalLength() const;
	virtual Nano::ErrorStatus reverseCurve();
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbR13ObjectId
class NRXDBGATE_EXPORT NcDbR13ObjectId : public NcDbObjectId {
public:
	bool operator < (const NcDbR13ObjectId& id) const;
	bool operator > (const NcDbR13ObjectId& id) const;
	bool operator <= (const NcDbR13ObjectId& id) const;
	bool operator >= (const NcDbR13ObjectId& id) const;
	bool operator == (const NcDbR13ObjectId& id) const;
	bool operator != (const NcDbR13ObjectId& id) const;
	bool operator < (const NcDbStub* pStub) const;
	bool operator > (const NcDbStub* pStub) const;
	bool operator <= (const NcDbStub* pStub) const;
	bool operator >= (const NcDbStub* pStub) const;
	bool operator == (const NcDbStub* pStub) const;
	bool operator != (const NcDbStub* pStub) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbIndex
class NRXDBGATE_EXPORT NcDbIndex : public NcDbObject {
public:
	NCDB_DECLARE_MEMBERS(NcDbIndex);
	NcDbIndex();
	virtual ~NcDbIndex();
	virtual NcDbFilteredBlockIterator*
	              newIterator(const NcDbFilter* pFilter) const;
	virtual Nano::ErrorStatus rebuildFull(NcDbIndexUpdateData* pIdxData);
	virtual NcDbObjectId objectBeingIndexedId()  const;
	void           setLastUpdatedAt(const NcDbDate& time);
	NcDbDate       lastUpdatedAt() const;
	void           setLastUpdatedAtU(const NcDbDate& time);
	NcDbDate       lastUpdatedAtU() const;
	NRX::Boolean isUptoDate   () const;
protected:
	virtual Nano::ErrorStatus rebuildModified(NcDbBlockChangeIterator* iter);
	friend Nano::ErrorStatus processBTRIndexObjects(
	                               NcDbBlockTableRecord* pBTR,
	                               int indexCtlVal,
	                               NcDbBlockChangeIterator* pBlkChgIter,
	                               NcDbIndexUpdateData*     pIdxUpdData);
};

//////////////////////////////////////////////////////////////////////////
// NcDbFilteredBlockIterator
class NRXDBGATE_EXPORT NcDbFilteredBlockIterator {
public:
	NcDbFilteredBlockIterator()          {}
	virtual ~NcDbFilteredBlockIterator() {}
	virtual Nano::ErrorStatus start()               = 0;
	virtual NcDbObjectId      next()                = 0;
	virtual NcDbObjectId      id() const            = 0;
	virtual Nano::ErrorStatus seek(NcDbObjectId id) = 0;
	virtual double estimatedHitFraction() const             = 0;
	virtual Nano::ErrorStatus accepts(NcDbObjectId id,
	                                  NRX::Boolean& idPassesFilter) const = 0;
	virtual NRX::Boolean    buffersForComposition() const;
	virtual Nano::ErrorStatus addToBuffer(NcDbObjectId id);
};

//////////////////////////////////////////////////////////////////////////
// NcDbCompositeFilteredBlockIterator
class NRXDBGATE_EXPORT NcDbCompositeFilteredBlockIterator {
private:
	NcDbCompositeFilteredBlockIterator(
	    const NcDbCompositeFilteredBlockIterator& copyFrom);
protected:
	NcDbCompositeFilteredBlockIterator() {}
public:
	virtual ~NcDbCompositeFilteredBlockIterator() {}
	virtual Nano::ErrorStatus init(NcDbFilter* const * ppFilters,
	                               int numFilters,
	                               const NcDbBlockTableRecord* pBtr) = 0;
	virtual Nano::ErrorStatus start()    = 0;
	virtual NcDbObjectId      next()     = 0;
	virtual NcDbObjectId      id() const = 0;
	virtual Nano::ErrorStatus seek(NcDbObjectId id)  = 0;
	static NcDbCompositeFilteredBlockIterator* newIterator();
};

//////////////////////////////////////////////////////////////////////////
// NcDbIndexUpdateData
class NcDbIndexUpdateData {
	public:
	    enum UpdateFlags
	    {
		    kModified   = 1,
		    kDeleted    = 2,
		    kProcessed  = 4,
		    kUnknownKey = 8
	    };
	    Nano::ErrorStatus addId      (NcDbObjectId id);
	    Nano::ErrorStatus setIdFlags (NcDbObjectId id, NRX::UInt8 flags);
	    Nano::ErrorStatus setIdData  (NcDbObjectId id, NRX::ULongPtr data);
	    Nano::ErrorStatus getIdData       (NcDbObjectId id, NRX::ULongPtr& data)  const;
	    Nano::ErrorStatus getIdFlags      (NcDbObjectId id, NRX::UInt8&  flags) const;
	    Nano::ErrorStatus getFlagsAndData (NcDbObjectId   id,
	                                       NRX::UInt8&  flags,
	                                       NRX::ULongPtr& data) const;
	private:
	    NcDbIndexUpdateData();
	    ~NcDbIndexUpdateData();
	    NcDbIndexUpdateData(const NcDbIndexUpdateData&);
	    NcDbHandleTable* mpTable;
	    friend class NcDbIndexUpdateDataIterator;
};

//////////////////////////////////////////////////////////////////////////
// NcDbIndexUpdateDataIterator
class NRXDBGATE_EXPORT NcDbIndexUpdateDataIterator {
	public:
	    NcDbIndexUpdateDataIterator  (const NcDbIndexUpdateData* p);
	    ~NcDbIndexUpdateDataIterator ();
	    void start   ();
	    void next    ();
	    bool done    ();
	    Nano::ErrorStatus currentData (NcDbObjectId&  id,
	                                   NRX::UInt8&  flags,
	                                   NRX::ULongPtr& data) const;
	private:
	    NcDbHandleTableIterator* mpIter;
};

//////////////////////////////////////////////////////////////////////////
// NcDbBlockChangeIterator
class NRXDBGATE_EXPORT NcDbBlockChangeIterator {
private:
	NcDbBlockChangeIterator();
	NcDbBlockChangeIterator(const NcDbBlockChangeIterator&);
	NcDbBlockChangeIterator (NcDbObjectId         btrId,
	                         NcDbIndexUpdateData* pIdxUpdData);
	~NcDbBlockChangeIterator();
public:
	void         start ();
	NcDbObjectId id    () const;
	void         next  ();
	bool         done  ();
	Nano::ErrorStatus    curIdInfo    (NcDbObjectId&  id,
	                                   NRX::UInt8&  flags,
	                                   NRX::ULongPtr& data) const;
	Nano::ErrorStatus    setCurIdInfo (NRX::UInt8   flags,
	                                   NRX::ULongPtr data);
	NcDbIndexUpdateData* updateData () const;
	void clearProcessedFlags();
private:
	NcDbIndexUpdateData*         mpIds;
	NcDbObjectId                 mBTRId;
	NcDbIndexUpdateDataIterator* mpIter;
};

//////////////////////////////////////////////////////////////////////////
// NcDbInterferencePE
class NRXDBGATE_EXPORT NcDbInterferencePE : public NcRxObject {
public:
	enum Flags {
		kDefault     = 0x00,
	};
	NCRX_DECLARE_MEMBERS(NcDbInterferencePE);
	virtual Nano::ErrorStatus
	    createInterferenceObjects(  NcArray<NcDbEntity*>& interferenceObjects,
	                              NcDbEntity* pEnt1,
	                              NcDbEntity* pEnt2,
	                              unsigned int flags ) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbJoinEntityPE
class NRXDBGATE_EXPORT NcDbJoinEntityPE : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbJoinEntityPE);
	virtual Nano::ErrorStatus
	    joinEntity(NcDbEntity* pPrimaryEntity,
	               NcDbEntity* pSecondaryEntity) const = 0;
	virtual Nano::ErrorStatus
	    joinEntities(NcDbEntity* pPrimaryEntity,
	                 const NcArray<NcDbEntity*>& otherEntities,
	                 NcGeIntArray& joinedEntityIndices) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbLight
class NRXDBGATE_EXPORT NcDbLight : public NcDbEntity {
public:
	NCRX_DECLARE_MEMBERS(NcDbLight);
private:
	static NRX::UInt32 kCurrentVersionNumber ;
public:
	NcDbLight ();
	~NcDbLight();
	virtual Nano::ErrorStatus subClose();
	virtual Nano::ErrorStatus dwgOutFields (NcDbDwgFiler *pFiler) const ;
	virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler *pFiler) ;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus decomposeForSave(
	        NcDb::NcDbDwgVersion ver,
	        NcDbObject*& replaceObj,
	        NcDbObjectId& replaceId,
	        NRX::Boolean& exchangeXData);
	virtual NcGiDrawable::DrawableType    drawableType() const;
	virtual bool castShadows() const;
	virtual void setCastShadows(bool newVal);
	virtual bool receiveShadows() const;
	virtual void setReceiveShadows(bool newVal);
	virtual Nano::ErrorStatus copyFrom (const NcRxObject* other);
	virtual const NcString& name() const;
	virtual Nano::ErrorStatus setName(const NcString & name);
	virtual NcGiDrawable::DrawableType lightType() const;
	virtual Nano::ErrorStatus setLightType(NcGiDrawable::DrawableType type);
	virtual  bool isOn() const;
	virtual Nano::ErrorStatus setOn(bool value);
	virtual bool isPlottable() const;
	virtual Nano::ErrorStatus setIsPlottable(bool plot);
	virtual const NcCmColor& lightColor() const;
	virtual Nano::ErrorStatus setLightColor(const NcCmColor& color);
	virtual double intensity() const;
	virtual Nano::ErrorStatus setIntensity(double intensity);
	virtual void setShadowParameters(const NcGiShadowParameters& params);
	virtual const NcGiShadowParameters& shadowParameters() const;
	virtual void setLightAttenuation(const NcGiLightAttenuation& params);
	virtual const NcGiLightAttenuation& lightAttenuation() const;
	virtual Nano::ErrorStatus setPosition(const NcGePoint3d& pos);
	virtual const NcGePoint3d& position() const;
	virtual const NcGePoint3d& targetLocation() const;
	virtual Nano::ErrorStatus setTargetLocation(const NcGePoint3d& newVal);
	virtual Nano::ErrorStatus setHotspotAndFalloff(double hotspot, double falloff);
	virtual double hotspotAngle() const;
	virtual double falloffAngle() const;
	virtual const NcGeVector3d& lightDirection() const;
	virtual Nano::ErrorStatus setLightDirection(const NcGeVector3d& lightvec);
	enum PhysicalIntensityMethod {
		kPeakIntensity = 0,
		kFlux,
		kIlluminance
	};
	NcDbLight::PhysicalIntensityMethod physicalIntensityMethod() const;
	Nano::ErrorStatus setPhysicalIntensityMethod(NcDbLight::PhysicalIntensityMethod method);
	double physicalIntensity() const;
	Nano::ErrorStatus setPhysicalIntensity(double physicalIntensity);
	double illuminanceDistance() const;
	Nano::ErrorStatus setIlluminanceDistance(double distance);
	enum LampColorType {
		kKelvin = 0,
		kPreset
	};
	NcDbLight::LampColorType lampColorType() const;
	Nano::ErrorStatus setLampColorType(NcDbLight::LampColorType colorType);
	double lampColorTemp() const;
	Nano::ErrorStatus setLampColorTemp(double colorTemp);
	enum LampColorPreset {
		kD65White = 0,
		kFluorescent,
		kCoolWhite,
		kWhiteFluorescent,
		kDaylightFluorescent,
		kIncandescent,
		kXenon,
		kHalogen,
		kQuartz,
		kMetalHalide,
		kMercury,
		kPhosphorMercury,
		kHighPressureSodium,
		kLowPressureSodium,
		kCustom
	};
	NcDbLight::LampColorPreset lampColorPreset() const;
	Nano::ErrorStatus setLampColorPreset(NcDbLight::LampColorPreset colorPreset);
	Nano::ErrorStatus lampColorRGB(NcGiColorRGB& rgbColor) const;
	Nano::ErrorStatus setLampColorRGB(NcGiColorRGB rgbColor);
	Nano::ErrorStatus resultingColor(NcCmColor& rgbColor) const;
	Nano::ErrorStatus webFile(NcString& webFile) const;
	Nano::ErrorStatus setWebFile(const NCHAR* webFile);
	Nano::ErrorStatus webRotation(NcGeVector3d& rotation) const;
	Nano::ErrorStatus setWebRotation(NcGeVector3d rotation);
	bool hasTarget() const;
	Nano::ErrorStatus setHasTarget(bool hasTarget);
	Nano::ErrorStatus shadowParameters(NcGiShadowParameters2& params) const;
	Nano::ErrorStatus setShadowParameters(const NcGiShadowParameters2& params);
	enum GlyphDisplayType {
		kGlyphDisplayAuto = 0,
		kGlyphDisplayOn,
		kGlyphDisplayOff
	};
	GlyphDisplayType glyphDisplay() const;
	Nano::ErrorStatus setGlyphDisplay(GlyphDisplayType type);
protected:
	virtual void subViewportDraw (NcGiViewportDrawNrx *mode) ;
	virtual NRX::Boolean subWorldDraw (NcGiWorldDraw *mode) ;
	virtual NRX::UInt32  subSetAttributes(NcGiDrawableTraits* pTraits);
	virtual Nano::ErrorStatus   subGetOsnapPoints(
	                                    NcDb::OsnapMode     osnapMode,
	                                    NRX::GsMarker     gsSelectionMark,
	                                    const NcGePoint3d&  pickPoint,
	                                    const NcGePoint3d&  lastPoint,
	                                    const NcGeMatrix3d& viewXform,
	                                    NcGePoint3dArray&   snapPoints,
	                                    NcDbIntArray &   geomIds) const;
	virtual Nano::ErrorStatus   subGetOsnapPoints(
	                                    NcDb::OsnapMode     osnapMode,
	                                    NRX::GsMarker     gsSelectionMark,
	                                    const NcGePoint3d&  pickPoint,
	                                    const NcGePoint3d&  lastPoint,
	                                    const NcGeMatrix3d& viewXform,
	                                    NcGePoint3dArray&   snapPoints,
	                                    NcDbIntArray &   geomIds,
	                                    const NcGeMatrix3d& insertionMat) const;
	virtual Nano::ErrorStatus subTransformBy(const NcGeMatrix3d& xform);
	virtual Nano::ErrorStatus subGetTransformedCopy(const NcGeMatrix3d & xform,NcDbEntity *& pEnt) const;
	virtual void subList() const;
	virtual Nano::ErrorStatus subGetGripPoints (NcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize, const NcGeVector3d &curViewDir, const int bitflags) const ;
	virtual Nano::ErrorStatus subMoveGripPointsAt (const NcDbVoidPtrArray &gripAppData, const NcGeVector3d &offset, const int bitflags) ;
	virtual Nano::ErrorStatus subDeepClone(NcDbObject* pOwner,NcDbObject*& pClonedObject,
	                                       NcDbIdMapping& idMap,NRX::Boolean isPrimary = true) const;
	virtual Nano::ErrorStatus subWblockClone(NcRxObject* pOwnerObject, NcDbObject*& pClonedObject,
	                                         NcDbIdMapping& idMap, NRX::Boolean isPrimary ) const;
	virtual Nano::ErrorStatus subHighlight(const NcDbFullSubentPath& subId,
	                                       const NRX::Boolean highlightAll) const;
	virtual Nano::ErrorStatus subUnhighlight(const NcDbFullSubentPath& subId,
	                                         const NRX::Boolean highlightAll) const;
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const ;
	virtual Nano::ErrorStatus subGetGeomExtents(NcDbExtents& extents) const;
private:
	NRX::UInt32 baseSetAttributes(NcGiDrawableTraits* pTraits);
	Nano::ErrorStatus baseDeepClone(NcDbObject* pOwner,NcDbObject*& pClonedObject,
	                                NcDbIdMapping& idMap,NRX::Boolean isPrimary) const;
	Nano::ErrorStatus baseWblockClone(NcRxObject* pOwnerObject, NcDbObject*& pClonedObject,
	                                  NcDbIdMapping& idMap, NRX::Boolean isPrimary) const;
	Nano::ErrorStatus baseHighlight(const NcDbFullSubentPath& subId,
	                                const NRX::Boolean highlightAll) const;
	Nano::ErrorStatus baseUnhighlight(const NcDbFullSubentPath& subId,
	                                  const NRX::Boolean highlightAll) const;
	bool mSelected;
};

//////////////////////////////////////////////////////////////////////////
// NcDbLoftedSurface
class NcDbLoftedSurface: public NcDbSurface {
public:
	NcDbLoftedSurface ();
	virtual ~NcDbLoftedSurface();
	NCDB_DECLARE_MEMBERS(NcDbLoftedSurface);
	virtual Nano::ErrorStatus createLoftedSurface (
	    NcArray<NcDbEntity*>& crossSectionCurves,
	    NcArray<NcDbEntity*>& guideCurves,
	    NcDbEntity* pPathCurve, NcDbLoftOptions& loftOptions );
	int           numCrossSections () const;
	NcDbEntity*   getCrossSection ( int idx ) const;
	int           numGuideCurves () const;
	NcDbEntity*   getGuideCurve ( int idx ) const;
	NcDbEntity*   getPathEntity () const;
	void          getLoftOptions ( NcDbLoftOptions& loftOptions ) const;
	NRXDBGATE_EXPORT NcDbLoftProfile*  crossSection ( int idx ) const;
	NRXDBGATE_EXPORT void              getCrossSections ( NcArray<NcDbLoftProfile*>& crossSections ) const;
	NRXDBGATE_EXPORT NcDbLoftProfile*  guide ( int idx ) const;
	NRXDBGATE_EXPORT void              getGuides ( NcArray<NcDbLoftProfile*>& guides ) const;
	NRXDBGATE_EXPORT NcDbLoftProfile*  path () const;
	NRXDBGATE_EXPORT int               startContinuity ( bool isCrossSection = true ) const;
	NRXDBGATE_EXPORT int               endContinuity ( bool isCrossSection = true ) const;
	NRXDBGATE_EXPORT double            startMagnitude ( bool isCrossSection = true ) const;
	NRXDBGATE_EXPORT double            endMagnitude ( bool isCrossSection = true ) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setStartContinuity ( int val, bool isCrossSection = true );
	NRXDBGATE_EXPORT Nano::ErrorStatus setEndContinuity ( int val, bool isCrossSection = true );
	NRXDBGATE_EXPORT Nano::ErrorStatus setStartMagnitude ( double val, bool isCrossSection = true );
	NRXDBGATE_EXPORT Nano::ErrorStatus setEndMagnitude ( double val, bool isCrossSection = true );
	NRXDBGATE_EXPORT Nano::ErrorStatus setLoftOptions ( const NcDbLoftOptions& loftOptions );
	enum LoftSurfaceType
	{
		kLoftSurf,
		kLoftBlendSurf,
		kLoftNetworkSurf
	};
	NRXDBGATE_EXPORT NcDbLoftedSurface::LoftSurfaceType  loftSurfaceType () const;
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;
	virtual bool isDependent() const;
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbLoftOptions
class OdDbLoftOptions;
class NRXDBGATE_EXPORT NcDbLoftOptions {
public:
	NcDbLoftOptions ();
	NcDbLoftOptions ( const NcDbLoftOptions& src );
	~NcDbLoftOptions ();

public:
	typedef NcDbLoftOptions wrapper_class;
	typedef OdDbLoftOptions native_class;

	NcDbLoftOptions& operator = ( const NcDbLoftOptions& src );
	enum NormalOption {
		    kNoNormal,
		    kFirstNormal,
		    kLastNormal,
		    kEndsNormal,
		    kAllNormal,
		    kUseDraftAngles
	};
	double  draftStart () const;
	void  setDraftStart ( double ang );
	double  draftEnd () const;
	void  setDraftEnd ( double ang );
	double  draftStartMag () const;
	void  setDraftStartMag ( double val );
	double  draftEndMag () const;
	void  setDraftEndMag ( double val );
	bool  arcLengthParam () const;
	void  setArcLengthParam ( bool val );
	bool  noTwist () const;
	void  setNoTwist ( bool val );
	bool  alignDirection () const;
	void  setAlignDirection ( bool val );
	bool  simplify () const;
	void  setSimplify ( bool val );
	bool  closed () const;
	void  setClosed ( bool val );
	bool  periodic () const;
	void  setPeriodic ( bool val );
	bool  ruled () const;
	void  setRuled ( bool val );
	bool  virtualGuide () const;
	void  setVirtualGuide ( bool val );
	NcDbLoftOptions::NormalOption  normal () const;
	void  setNormal ( NcDbLoftOptions::NormalOption val );
	Nano::ErrorStatus  setOptionsFromSysvars ();
	Nano::ErrorStatus  setSysvarsFromOptions ();
	Nano::ErrorStatus  checkOptions ( bool displayErrorMessages = false  );
	Nano::ErrorStatus checkLoftCurves (
	    NcArray<NcDbEntity*>& crossSectionCurves,
	    NcArray<NcDbEntity*>& guideCurves,
	    NcDbEntity* pPathCurve,
	    bool& allOpen, bool& allClosed, bool& allPlanar,
	    bool displayErrorMessages = false );
	Nano::ErrorStatus checkCrossSectionCurves (
	    NcArray<NcDbEntity*>& crossSectionCurves,
	    bool& allOpen, bool& allClosed, bool& allPlanar,
	    bool displayErrorMessages = false );
	Nano::ErrorStatus checkGuideCurves ( NcArray<NcDbEntity*>& guideCurves,
	                                    bool displayErrorMessages = false );
	Nano::ErrorStatus checkPathCurve ( NcDbEntity *pPathCurve,
	                                  bool displayErrorMessages = false );

public:
	OdDbLoftOptions* native() const;

private:

	OdDbLoftOptions *m_pNative;
};


//////////////////////////////////////////////////////////////////////////
// NcDbLayerIndex
class NRXDBGATE_EXPORT NcDbLayerIndex: public NcDbIndex {
public:
	NCDB_DECLARE_MEMBERS(NcDbLayerIndex);
	     NcDbLayerIndex();
	virtual ~NcDbLayerIndex();
	virtual NcDbFilteredBlockIterator* newIterator(const NcDbFilter* pFilter)
	                                               const;
	virtual Nano::ErrorStatus rebuildFull(NcDbIndexUpdateData* pIdxData);
	Nano::ErrorStatus compute(NcDbLayerTable*       pLT,
	                          NcDbBlockTableRecord* pBTR);
protected:
	virtual Nano::ErrorStatus rebuildModified(NcDbBlockChangeIterator* iter);
};

//////////////////////////////////////////////////////////////////////////
// NcDbLayerIndexIterator
class NRXDBGATE_EXPORT NcDbLayerIndexIterator : public NcDbFilteredBlockIterator {
public:
	NcDbLayerIndexIterator(const NcDbLayerIndex*  pIndex,
	                       const NcDbLayerFilter* pFilter);
	virtual ~NcDbLayerIndexIterator();
	virtual Nano::ErrorStatus start();
	virtual NcDbObjectId      next();
	virtual NcDbObjectId      id() const;
	virtual Nano::ErrorStatus seek(NcDbObjectId id);
	virtual double estimatedHitFraction() const;
	virtual Nano::ErrorStatus accepts(NcDbObjectId id,
	                                  NRX::Boolean& idPassesFilter) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbXObject
class NRXDBGATE_EXPORT NRX_NO_VTABLE NcDbXObject: public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbXObject);
	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo);
	Nano::ErrorStatus dwgIn(NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	Nano::ErrorStatus dwgOut(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	Nano::ErrorStatus dxfIn(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	Nano::ErrorStatus dxfOut(NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	protected:
	NcDbXObject();
};

//////////////////////////////////////////////////////////////////////////
// NcCmComplexColor
class NRXDBGATE_EXPORT NcCmComplexColor: public  NcDbXObject {
public:
	NCRX_DECLARE_MEMBERS(NcCmComplexColor);
	virtual NcCmComplexColor* incReference();
	virtual void              decReference();
	virtual Nano::ErrorStatus getDescription(NCHAR*& desc) const;
	virtual Nano::ErrorStatus getExplanation(NCHAR*& expl) const;
	virtual NcCmEntityColor::ColorMethod  colorMethod() const;
	virtual Nano::ErrorStatus setColorMethod(
	    NcCmEntityColor::ColorMethod eColorMethod);
	virtual bool              isByColor() const;
	virtual bool              isByLayer() const;
	virtual bool              isByBlock() const;
	virtual bool              isByACI()   const;
	virtual bool              isByPen ()  const;
	virtual bool              isForeground()   const;
	virtual NRX::UInt32     color() const;
	virtual Nano::ErrorStatus setColor(NRX::UInt32 color);
	virtual Nano::ErrorStatus setRGB  (NRX::UInt8 red,
	                                   NRX::UInt8 green,
	                                   NRX::UInt8 blue);
	virtual Nano::ErrorStatus setRed  (NRX::UInt8 red);
	virtual Nano::ErrorStatus setGreen(NRX::UInt8 green);
	virtual Nano::ErrorStatus setBlue (NRX::UInt8 blue);
	virtual NRX::UInt8      red  () const;
	virtual NRX::UInt8      green() const;
	virtual NRX::UInt8      blue () const;
	virtual NRX::UInt16     colorIndex() const;
	virtual Nano::ErrorStatus setColorIndex(NRX::UInt16 colorIndex);
	virtual NRX::UInt16     penIndex() const;
	virtual Nano::ErrorStatus setPenIndex (NRX::UInt16 penIndex);
	virtual Nano::ErrorStatus copyFrom(const NcRxObject*);
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo);
private:
	NRX::UInt16 refCount;
	NcCmEntityColor mColor;
};

//////////////////////////////////////////////////////////////////////////
// NcDbColor
class NRXDBGATE_EXPORT NcDbColor: public NcDbObject {
public:
	NCDB_DECLARE_MEMBERS(NcDbColor);
	NcDbColor();
	virtual ~NcDbColor();
	void getColor(NcCmColor& color) const;
	void setColor(const NcCmColor& color);
	const NcCmEntityColor& entityColor(void) const;
	virtual Nano::ErrorStatus   decomposeForSave(
	                            NcDb::NcDbDwgVersion ver,
	                            NcDbObject*& replaceObj,
	                            NcDbObjectId& replaceId,
	                            NRX::Boolean& exchangeXData);
	virtual Nano::ErrorStatus   dwgInFields(NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus   dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus   dxfInFields(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus   dxfOutFields(NcDbDxfFiler* pFiler) const;
private:
	NcCmColor           m_color;
	NcCmEntityColor     m_ecol;
protected:
	virtual Nano::ErrorStatus subWblockClone(NcRxObject* pOwnerObject,
	                                         NcDbObject*& pClonedObject,
	                                         NcDbIdMapping& idMap,
	                                         NRX::Boolean isPrimary
	                                         = true) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbMaterial
class OdDbMaterial;
class NRXDBGATE_EXPORT NcDbMaterial : public NcDbObject {
public:
	NCDB_DECLARE_MEMBERS(NcDbMaterial);

public:
	typedef NcDbMaterial  wrapper_class;
	typedef OdDbMaterial  native_class;

	NcDbMaterial();
	NcDbMaterial(OdRxObject* _object);

	virtual ~NcDbMaterial();
	virtual Nano::ErrorStatus   setName (const NCHAR * pName);
	virtual const NCHAR *       name    (void) const;
	virtual Nano::ErrorStatus   setDescription(const NCHAR * pDescription);
	virtual const NCHAR *       description(void) const;
	virtual void setAmbient     (const NcGiMaterialColor & color);
	virtual void ambient        (NcGiMaterialColor & color) const;
	virtual void setDiffuse     (const NcGiMaterialColor & color,
	                             const NcGiMaterialMap & map);
	virtual void diffuse        (NcGiMaterialColor & color,
	                             NcGiMaterialMap & map) const;
	virtual void setSpecular    (const NcGiMaterialColor & color,
	                             const NcGiMaterialMap & map,
	                             double dGloss);
	virtual void specular       (NcGiMaterialColor & color,
	                             NcGiMaterialMap & map,
	                             double & dGloss) const;
	virtual void setReflection  (const NcGiMaterialMap & map);
	virtual void reflection     (NcGiMaterialMap & map) const;
	virtual void setOpacity     (double dPercentage,
	                             const NcGiMaterialMap & map);
	virtual void opacity        (double & dPercentage,
	                             NcGiMaterialMap & map) const;
	virtual void setBump        (const NcGiMaterialMap & map);
	virtual void bump           (NcGiMaterialMap & map) const;
	virtual void setRefraction  (double dIndex,
	                             const NcGiMaterialMap & map);
	virtual void refraction     (double & dIndex,
	                             NcGiMaterialMap & map) const;
	virtual double translucence() const;
	virtual Nano::ErrorStatus setTranslucence(double value);
	virtual double selfIllumination() const;
	virtual Nano::ErrorStatus setSelfIllumination(double value);
	virtual double reflectivity() const;
	virtual Nano::ErrorStatus setReflectivity(double value);
	virtual NcGiMaterialTraits::IlluminationModel illuminationModel() const;
	virtual Nano::ErrorStatus setIlluminationModel(NcGiMaterialTraits::IlluminationModel model);
	virtual NcGiMaterialTraits::ChannelFlags channelFlags() const;
	virtual Nano::ErrorStatus setChannelFlags(NcGiMaterialTraits::ChannelFlags value);
	virtual NcGiMaterialTraits::Mode mode() const;
	virtual Nano::ErrorStatus setMode(NcGiMaterialTraits::Mode value);
	virtual Nano::ErrorStatus dwgInFields  (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields (NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields  (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields (NcDbDxfFiler* pFiler) const;
	virtual NcGiDrawable*     drawable     (void);
	virtual void              setGsNode    (NcGsNode* pNode);
	virtual NcGsNode*         gsNode       (void) const;
	double              colorBleedScale         () const;
	Nano::ErrorStatus   setColorBleedScale      (double value);
	double              indirectBumpScale       () const;
	Nano::ErrorStatus   setIndirectBumpScale    (double value);
	double              reflectanceScale        () const;
	Nano::ErrorStatus   setReflectanceScale     (double value);
	double              transmittanceScale      () const;
	Nano::ErrorStatus   setTransmittanceScale   (double value);
	NRX::Boolean      twoSided                () const;
	Nano::ErrorStatus   setTwoSided             (NRX::Boolean value);
	NcGiMaterialTraits2::LuminanceMode luminanceMode () const;
	Nano::ErrorStatus   setLuminanceMode        (NcGiMaterialTraits2::LuminanceMode value);
	double              luminance               () const;
	Nano::ErrorStatus   setLuminance            (double value);
	double              shininess               () const;
	Nano::ErrorStatus   setShininess            (double value);
	Nano::ErrorStatus   normalMap               (NcGiMaterialMap & map,
	                                             NcGiMaterialTraits2::NormalMapMethod & method,
	                                             double & strength) const;
	Nano::ErrorStatus   setNormalMap            (const NcGiMaterialMap & map,
	                                             NcGiMaterialTraits2::NormalMapMethod method,
	                                             double strength);
	NRX::Boolean      isAnonymous             () const;
	Nano::ErrorStatus   setAnonymous            (NRX::Boolean isAnonymous);
	NcGiMaterialTraits2::GlobalIlluminationMode globalIllumination() const;
	void                setGlobalIllumination   (NcGiMaterialTraits2::GlobalIlluminationMode mode);
	NcGiMaterialTraits2::FinalGatherMode        finalGather() const;
	void                setFinalGather          (NcGiMaterialTraits2::FinalGatherMode mode);
	void* getAdskMaterialData() const;
	Nano::ErrorStatus setAdskMaterialData(const void* pMatObj, bool bCacheIt = false);
	void clearAdskMaterialCache();
	enum MaterialFlags {
		kNone               = 0,
		kIsLegacy           = 0x1,
		kIsModifiedIsValid  = 0x2,
		kIsModified         = 0x4,
		kIsModifiedAndValid = 0x6
	};
	Nano::ErrorStatus getAdskMaterialFlags(MaterialFlags& flags) const;
	Nano::ErrorStatus setAdskMaterialFlags(MaterialFlags flags);
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;

public:
	OdDbMaterial* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbMLeaderStyle
class OdDbMLeaderStyle;
class NRXDBGATE_EXPORT NcDbMLeaderStyle : public NcDbObject {
public:
	enum ContentType {
		kNoneContent                = 0,
		kBlockContent               = 1,
		kMTextContent               = 2,
		kToleranceContent           = 3,
	};
	enum DrawMLeaderOrderType {
		kDrawContentFirst           = 0,
		kDrawLeaderFirst            = 1
	};
	enum DrawLeaderOrderType {
		kDrawLeaderHeadFirst        = 0,
		kDrawLeaderTailFirst        = 1
	};
	enum LeaderType {
		kInVisibleLeader            = 0,
		kStraightLeader             = 1,
		kSplineLeader               = 2
	};
	enum TextAttachmentDirection {
		kAttachmentHorizontal       = 0,
		kAttachmentVertical         = 1
	};
	enum TextAttachmentType {
		kAttachmentTopOfTop         = 0,
		kAttachmentMiddleOfTop      = 1,
		kAttachmentMiddle           = 2,
		kAttachmentMiddleOfBottom   = 3,
		kAttachmentBottomOfBottom   = 4,
		kAttachmentBottomLine       = 5,
		kAttachmentBottomOfTopLine  = 6,
		kAttachmentBottomOfTop      = 7,
		kAttachmentAllLine          = 8,
		kAttachmentCenter           = 9,
		kAttachmentLinedCenter      = 10
	};
	enum TextAngleType {
		kInsertAngle                = 0,
		kHorizontalAngle            = 1,
		kAlwaysRightReadingAngle    = 2
	};
	enum TextAlignmentType {
		kLeftAlignment              = 0,
		kCenterAlignment            = 1,
		kRightAlignment             = 2
	};
	enum BlockConnectionType {
		kConnectExtents             = 0,
		kConnectBase                = 1
	};
	enum LeaderDirectionType {
		kUnknownLeader              = 0,
		kLeftLeader                 = 1,
		kRightLeader                = 2,
		kTopLeader                  = 3,
		kBottomLeader               = 4
	};
	enum SegmentAngleType {
		kAny                        = 0,
		k15                         = 1,
		k30                         = 2,
		k45                         = 3,
		k60                         = 4,
		k90                         = 6,
		kHorz                       = 12
	};
public:
	NcDbMLeaderStyle();
	NcDbMLeaderStyle(OdRxObject* _object);
	NCDB_DECLARE_MEMBERS(NcDbMLeaderStyle);
public:
	typedef NcDbMLeaderStyle  wrapper_class;
	typedef OdDbMLeaderStyle  native_class;

	// NcDbObject protocol
public:
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer) override;
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const override;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer) override;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const override;

	virtual Nano::ErrorStatus audit(NcDbAuditInfo* pAuditInfo);

public:
	virtual Nano::ErrorStatus   getName(NCHAR*& pszName) const;
	virtual Nano::ErrorStatus   setName(const NCHAR * pszName);
	virtual const NCHAR*        description(void) const;
	virtual Nano::ErrorStatus   setDescription(const NCHAR * pszDescription);
	virtual NRX::UInt32       bitFlags() const;
	virtual Nano::ErrorStatus   setBitFlags(NRX::UInt32 flags);
	Nano::ErrorStatus         setContentType                (ContentType contentType);
	ContentType               contentType                   () const;
	Nano::ErrorStatus         setDrawMLeaderOrderType       (DrawMLeaderOrderType drawMLeaderOrderType);
	DrawMLeaderOrderType      drawMLeaderOrderType          () const;
	Nano::ErrorStatus         setDrawLeaderOrderType        (DrawLeaderOrderType drawLeaderOrderType);
	DrawLeaderOrderType       drawLeaderOrderType           () const;
	Nano::ErrorStatus         setMaxLeaderSegmentsPoints    (int maxLeaderSegmentsPoints);
	int                       maxLeaderSegmentsPoints       () const;
	Nano::ErrorStatus         setFirstSegmentAngleConstraint (SegmentAngleType angle);
	SegmentAngleType          firstSegmentAngleConstraint    () const;
	Nano::ErrorStatus         setSecondSegmentAngleConstraint(SegmentAngleType angle);
	SegmentAngleType          secondSegmentAngleConstraint   () const;
	Nano::ErrorStatus         setLeaderLineType             (LeaderType leaderLineType);
	LeaderType                leaderLineType                () const;
	Nano::ErrorStatus         setLeaderLineColor            (const NcCmColor& leaderLineColor);
	NcCmColor                 leaderLineColor               () const;
	Nano::ErrorStatus         setLeaderLineTypeId           (NcDbObjectId leaderLineTypeId);
	NcDbObjectId              leaderLineTypeId              () const;
	Nano::ErrorStatus         setLeaderLineWeight           (NcDb::LineWeight leaderLineWeight);
	NcDb::LineWeight          leaderLineWeight              () const;
	Nano::ErrorStatus         setEnableLanding              (bool enableLanding);
	bool                      enableLanding                 () const;
	Nano::ErrorStatus         setLandingGap                 (double landingGap);
	double                    landingGap                    () const;
	Nano::ErrorStatus         setEnableDogleg               (bool enableDogleg);
	bool                      enableDogleg                  () const;
	Nano::ErrorStatus         setDoglegLength               (double doglegLength);
	double                    doglegLength                  () const;
	Nano::ErrorStatus         setArrowSymbolId              (const NCHAR* name);
	Nano::ErrorStatus         setArrowSymbolId              (NcDbObjectId arrowSymbolId);
	NcDbObjectId              arrowSymbolId                 () const;
	Nano::ErrorStatus         setArrowSize                  (double arrowSize);
	double                    arrowSize                     () const;
	Nano::ErrorStatus         setDefaultMText               (const NcDbMText* defaultMText);
	NcDbMText*                defaultMText                  () const;
	Nano::ErrorStatus         setTextStyleId                (NcDbObjectId textStyleId);
	NcDbObjectId              textStyleId                   () const;
	Nano::ErrorStatus         setTextAttachmentType         (TextAttachmentType textAttachmentType,
	                                                         LeaderDirectionType leaderDirection);
	TextAttachmentType        textAttachmentType            (LeaderDirectionType leaderDirection) const;
	Nano::ErrorStatus         setTextAttachmentType         (TextAttachmentType textAttachmentType);
	TextAttachmentType        textAttachmentType            () const;
	Nano::ErrorStatus         setTextAngleType              (TextAngleType textAngleType);
	TextAngleType             textAngleType                 () const;
	Nano::ErrorStatus         setTextAlignmentType          (TextAlignmentType textAlignmentType);
	TextAlignmentType         textAlignmentType             () const;
	Nano::ErrorStatus         setTextAlignAlwaysLeft        (bool bAlwaysLeft);
	bool                      textAlignAlwaysLeft           () const;
	Nano::ErrorStatus         setTextColor                  (const NcCmColor& textColor);
	NcCmColor                 textColor                     () const;
	Nano::ErrorStatus         setTextHeight                 (double textHeight);
	double                    textHeight                    () const;
	Nano::ErrorStatus         setEnableFrameText            (bool enableFrameText);
	bool                      enableFrameText               () const;
	Nano::ErrorStatus         setAlignSpace                 (double alignSpace);
	double                    alignSpace                    () const;
	Nano::ErrorStatus         setBlockId                    (const NCHAR* name);
	Nano::ErrorStatus         setBlockId                    (NcDbObjectId blockId);
	NcDbObjectId              blockId                       () const;
	Nano::ErrorStatus         setBlockColor                 (const NcCmColor& blockColor);
	NcCmColor                 blockColor                    () const;
	Nano::ErrorStatus         setBlockScale                 (const NcGeScale3d& scale);
	NcGeScale3d               blockScale                    () const;
	Nano::ErrorStatus         setEnableBlockScale           (bool enableBlockScale);
	bool                      enableBlockScale              () const;
	Nano::ErrorStatus         setBlockRotation              (double rotation);
	double                    blockRotation                 () const;
	Nano::ErrorStatus         setEnableBlockRotation        (bool enableBlockRotation);
	bool                      enableBlockRotation           () const;
	Nano::ErrorStatus         setBlockConnectionType        (BlockConnectionType blockConnectionType);
	BlockConnectionType       blockConnectionType           () const;
	Nano::ErrorStatus         setScale                      (double scale);
	double                    scale                         () const;
	bool                      overwritePropChanged          () const;
	Nano::ErrorStatus         postMLeaderStyleToDb          (NcDbDatabase* pDb, const NCHAR* styleName, NcDbObjectId & mleaderStyleId);
	Nano::ErrorStatus         setAnnotative              (bool isAnnotative);
	bool                      annotative                 () const;
	Nano::ErrorStatus         setBreakSize (double size);
	double                    breakSize () const;
	Nano::ErrorStatus         setTextAttachmentDirection(NcDbMLeaderStyle::TextAttachmentDirection textAttachmentDirection);
	TextAttachmentDirection   textAttachmentDirection() const;
	OdDbMLeaderStyle* native() const;
protected:
	virtual Nano::ErrorStatus subGetClassID                    (CLSID* pClsid) const;
};

#ifndef OD_MLEADER_H
#define MAX_LEADER_NUMBER     5000
#define MAX_LEADERLINE_NUMBER 5000
#endif

//////////////////////////////////////////////////////////////////////////
// NcDbMLeader
class OdDbMLeader;
class NRXDBGATE_EXPORT NcDbMLeader : public NcDbEntity {
public:
	enum MoveType {
		kMoveAllPoints                  = 0,
		kMoveAllExceptArrowHeaderPoints = 1,
		kMoveContentAndDoglegPoints     = 2
	};
	enum gsMarkType {
		kNone               = 0,
		kArrowMark          = 1,
		kLeaderLineMark     = kArrowMark  + MAX_LEADERLINE_NUMBER,
		kDoglegMark         = kLeaderLineMark + MAX_LEADERLINE_NUMBER,
		kMTextMark          = kDoglegMark + MAX_LEADER_NUMBER,
		kMTextUnderLineMark = kMTextMark + 1,
		kToleranceMark      = kMTextUnderLineMark + 1,
		kBlockMark          = kToleranceMark + 1,
		kBlockAttribute     = kBlockMark + 1
	};
	enum PropertyOverrideType {
		kLeaderLineType         = 0,
		kLeaderLineColor        = 1,
		kLeaderLineTypeId       = 2,
		kLeaderLineWeight       = 3,
		kEnableLanding          = 4,
		kLandingGap             = 5,
		kEnableDogleg           = 6,
		kDoglegLength           = 7,
		kArrowSymbolId          = 8,
		kArrowSize              = 9,
		kContentType            = 10,
		kTextStyleId            = 11,
		kTextLeftAttachmentType     = 12,
		kTextAngleType          = 13,
		kTextAlignmentType      = 14,
		kTextColor              = 15,
		kTextHeight             = 16,
		kEnableFrameText        = 17,
		kDefaultMText           = 18,
		kBlockId                = 19,
		kBlockColor             = 20,
		kBlockScale             = 21,
		kBlockRotation          = 22,
		kBlockConnectionType    = 23,
		kScale                  = 24,
		kTextRightAttachmentType = 25,
		kTextSwitchAlignmentType = 26,
		kTextAttachmentDirection = 27,
		kTextTopAttachmentType = 28,
		kTextBottomAttachmentType = 29,
		kSize = kTextBottomAttachmentType + 1
	};
	NcDbMLeader();
	~NcDbMLeader();
	NCDB_DECLARE_MEMBERS(NcDbMLeader);

	NcDbMLeader(OdRxObject* _object);

	// NcGiDrawable interface
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* traits) override;
	virtual NRX::Boolean subWorldDraw(NcGiWorldDraw* wd) override;
	virtual void subViewportDraw(NcGiViewportDrawNrx* vd) override;
public:
	typedef NcDbMLeader  wrapper_class;
	typedef OdDbMLeader  native_class;

	virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;
	virtual Nano::ErrorStatus subClose                    ();
	virtual Nano::ErrorStatus subErase                    (NRX::Boolean erasing);
	virtual void              objectClosed                (const NcDbObjectId dbObjId);
	virtual void              modified                    (const NcDbObject* dbObj);
	Nano::ErrorStatus         setOverride                 (PropertyOverrideType propertyType,
	                                                       bool isOverride = true);
	bool                      isOverride                  (PropertyOverrideType propertyType) const;
	Nano::ErrorStatus         setScale                    (double scale);
	double                    scale                       () const;
	Nano::ErrorStatus         getBlockAttributeValue(const NcDbObjectId& attdefId,
	                                                 NcDbAttribute*& pAtt) const;
	Nano::ErrorStatus         setBlockAttributeValue(const NcDbObjectId& attdefId,
	                                                 const NcDbAttribute* pAtt);
	Nano::ErrorStatus         getBlockAttributeValue      (const NcDbObjectId& attdefId,
	                                                       NCHAR*& value) const;
	Nano::ErrorStatus         setBlockAttributeValue      (const NcDbObjectId& attdefId,
	                                                       const NCHAR* value);
	NcGePlane         plane               () const;
	void              setPlane            (const NcGePlane& plane);
	NcGeVector3d      normal              () const;
	Nano::ErrorStatus moveMLeader         (const NcGeVector3d& vector,
	                                       MoveType moveType,
	                                       bool bAutoSwitchDogleg = true);
	Nano::ErrorStatus getContentGeomExtents(NcDbExtents& extents) const;
	int               numLeaders          () const;
	Nano::ErrorStatus getLeaderIndexes(NcArray<int>& leaderIndexes) const;
	Nano::ErrorStatus addLeader           (int& leaderIndex);
	Nano::ErrorStatus removeLeader        (int leaderIndex);
	int               numLeaderLines      () const;
	Nano::ErrorStatus getLeaderLineIndexes(NcArray<int>& leaderLineIndexes) const;
	Nano::ErrorStatus addLeaderLine       (int leaderIndex, int& leaderLineIndex);
	Nano::ErrorStatus addLeaderLine       (const NcGePoint3d& point, int& leaderLineIndex);
	Nano::ErrorStatus removeLeaderLine    (int leaderLineIndex);
	Nano::ErrorStatus addFirstVertex      (int leaderLineIndex, const NcGePoint3d& point);
	Nano::ErrorStatus removeFirstVertex   (int leaderLineIndex);
	Nano::ErrorStatus getFirstVertex      (int leaderLineIndex, NcGePoint3d& point) const;
	Nano::ErrorStatus setFirstVertex      (int leaderLineIndex, const NcGePoint3d& point);
	Nano::ErrorStatus addLastVertex       (int leaderLineIndex, const NcGePoint3d& point);
	Nano::ErrorStatus removeLastVertex    (int leaderLineIndex);
	Nano::ErrorStatus getLastVertex       (int leaderLineIndex, NcGePoint3d& point) const;
	Nano::ErrorStatus setLastVertex       (int leaderLineIndex, const NcGePoint3d& point);
	Nano::ErrorStatus numVertices         (int leaderLineIndex, int& num) const;
	Nano::ErrorStatus setVertex           (int leaderLineIndex, int index, const NcGePoint3d& point);
	Nano::ErrorStatus getVertex           (int leaderLineIndex, int index, NcGePoint3d& point) const;
	Nano::ErrorStatus getLeaderIndex      (int leaderLineIndex, int& leaderIndex) const;
	Nano::ErrorStatus getLeaderLineIndexes(int leaderIndex, NcArray<int>& leaderLineIndexes) const;
	Nano::ErrorStatus setDoglegDirection           (int leaderIndex, const NcGeVector3d& vector);
	Nano::ErrorStatus getDoglegDirection           (int leaderIndex, NcGeVector3d& vector) const;
	Nano::ErrorStatus                     setLeaderLineType      (NcDbMLeaderStyle::LeaderType leaderLineType);
	NcDbMLeaderStyle::LeaderType          leaderLineType         () const;
	Nano::ErrorStatus setLeaderLineType(int leaderLineIndex,
	                                    NcDbMLeaderStyle::LeaderType  leaderLineType);
	Nano::ErrorStatus getLeaderLineType(int leaderLineIndex,
	                                    NcDbMLeaderStyle::LeaderType& leaderLineType) const;
	Nano::ErrorStatus                     setLeaderLineColor     (const NcCmColor& leaderLineColor);
	NcCmColor                             leaderLineColor        () const;
	Nano::ErrorStatus setLeaderLineColor(int leaderLineIndex,
	                                     const NcCmColor& leaderLineColor);
	Nano::ErrorStatus getLeaderLineColor(int leaderLineIndex,
	                                     NcCmColor& leaderLineColor) const;
	Nano::ErrorStatus                     setLeaderLineTypeId    (NcDbObjectId leaderLineTypeId);
	NcDbObjectId                          leaderLineTypeId       () const;
	Nano::ErrorStatus setLeaderLineTypeId(int leaderLineIndex,
	                                      NcDbObjectId  leaderLineTypeId);
	Nano::ErrorStatus getLeaderLineTypeId(int leaderLineIndex,
	                                      NcDbObjectId& leaderLineTypeId) const;
	Nano::ErrorStatus                     setLeaderLineWeight    (NcDb::LineWeight leaderLineWeight);
	NcDb::LineWeight                      leaderLineWeight       () const;
	Nano::ErrorStatus setLeaderLineWeight(int leaderLineIndex,
	                                      NcDb::LineWeight  leaderLineWeight);
	Nano::ErrorStatus getLeaderLineWeight(int leaderLineIndex,
	                                      NcDb::LineWeight& leaderLineWeight) const;
	Nano::ErrorStatus                     setLandingGap          (double landingGap);
	double                                landingGap             () const;
	Nano::ErrorStatus                     setEnableLanding       (bool enableLanding);
	bool                                  enableLanding          () const;
	Nano::ErrorStatus                     setEnableDogleg        (bool enableDogleg);
	bool                                  enableDogleg           () const;
	Nano::ErrorStatus                     setDoglegLength        (int leaderIndex, double doglegLength);
	Nano::ErrorStatus                     doglegLength           (int leaderIndex, double& doglegLength) const;
	Nano::ErrorStatus                     setDoglegLength        (double doglegLength);
	double                                doglegLength           () const;
	Nano::ErrorStatus                     setArrowSymbolId       (NcDbObjectId arrowSymbolId);
	NcDbObjectId                          arrowSymbolId          () const;
	Nano::ErrorStatus setArrowSymbolId(int leaderLineIndex,
	                                   NcDbObjectId  arrowSymbolId);
	Nano::ErrorStatus getArrowSymbolId(int leaderLineIndex,
	                                   NcDbObjectId& arrowSymbolId) const;
	NcDbObjectId      arrowSymbolId(int leaderLineIndex) const;
	Nano::ErrorStatus                     setArrowSize           (double arrowSize);
	double                                arrowSize              () const;
	Nano::ErrorStatus setArrowSize(int leaderLineIndex, double  arrowSize);
	Nano::ErrorStatus getArrowSize(int leaderLineIndex, double& arrowSize) const;
	Nano::ErrorStatus                     setContentType         (NcDbMLeaderStyle::ContentType contentType);
	NcDbMLeaderStyle::ContentType         contentType            () const;
	Nano::ErrorStatus                     setTextStyleId         (NcDbObjectId textStyleId);
	NcDbObjectId                          textStyleId            () const;
	Nano::ErrorStatus                     setTextAttachmentType  (NcDbMLeaderStyle::TextAttachmentType textAttachmentType,
	                                                              NcDbMLeaderStyle::LeaderDirectionType leaderDirection);
	NcDbMLeaderStyle::TextAttachmentType  textAttachmentType     (NcDbMLeaderStyle::LeaderDirectionType leaderDirection) const;
	Nano::ErrorStatus                     setTextAttachmentType  (NcDbMLeaderStyle::TextAttachmentType textAttachmentType);
	NcDbMLeaderStyle::TextAttachmentType  textAttachmentType     () const;
	Nano::ErrorStatus                     setTextAngleType       (NcDbMLeaderStyle::TextAngleType textAngleType);
	NcDbMLeaderStyle::TextAngleType       textAngleType          () const;
	Nano::ErrorStatus                     setTextAlignmentType   (NcDbMLeaderStyle::TextAlignmentType textAlignmentType);
	NcDbMLeaderStyle::TextAlignmentType   textAlignmentType      () const;
	Nano::ErrorStatus                     setTextColor           (const NcCmColor& textColor);
	NcCmColor                             textColor              () const;
	Nano::ErrorStatus                     setTextHeight          (double textHeight);
	double                                textHeight             () const;
	Nano::ErrorStatus                     setEnableFrameText     (bool enableFrameText);
	bool                                  enableFrameText        () const;
	Nano::ErrorStatus                     setMText               (const NcDbMText* pMText);
	NcDbMText*                            mtext                  () const;
	Nano::ErrorStatus                     setBlockContentId             (NcDbObjectId blockId);
	NcDbObjectId                          blockContentId                () const;
	Nano::ErrorStatus                     setBlockColor          (const NcCmColor& blockColor);
	NcCmColor                             blockColor             () const;
	Nano::ErrorStatus                     setBlockScale          (const NcGeScale3d& scale);
	NcGeScale3d                           blockScale             () const;
	Nano::ErrorStatus                     setBlockRotation       (double rotation);
	double                                blockRotation          () const;
	Nano::ErrorStatus                     setBlockConnectionType (NcDbMLeaderStyle::BlockConnectionType blockConnectionType);
	NcDbMLeaderStyle::BlockConnectionType blockConnectionType    () const;
	Nano::ErrorStatus                     setEnableAnnotationScale(bool enableAnnotationScale);
	bool                                  enableAnnotationScale   () const;
	Nano::ErrorStatus                     setMLeaderStyle        (NcDbObjectId newStyleId);
	NcDbObjectId                          MLeaderStyle           ();
	Nano::ErrorStatus                     getOverridedMLeaderStyle(NcDbMLeaderStyle& mleaderStyle);
	Nano::ErrorStatus                     setContextDataManager  (void* pContextDataManager);
	void*                                 getContextDataManager  () const;
	Nano::ErrorStatus                     setBlockPosition       (const NcGePoint3d& position);
	Nano::ErrorStatus                     getBlockPosition       (NcGePoint3d& position) const;
	Nano::ErrorStatus                     setTextLocation        (const NcGePoint3d& location);
	Nano::ErrorStatus                     getTextLocation        (NcGePoint3d& location) const;
	Nano::ErrorStatus                     setToleranceLocation   (const NcGePoint3d& location);
	Nano::ErrorStatus                     getToleranceLocation   (NcGePoint3d& location) const;
	bool                                  hasContent             () const;
	Nano::ErrorStatus                     connectionPoint        (const NcGeVector3d& vect,
	                                                              NcGePoint3d& point) const;
	Nano::ErrorStatus                     connectionPoint        (const NcGeVector3d& vect,
	                                                              NcGePoint3d& point,
	                                                              NcDbMLeaderStyle::TextAttachmentDirection textAttachmentDirection) const;
	Nano::ErrorStatus                     recomputeBreakPoints   ();
	Nano::ErrorStatus                     postMLeaderToDb        (NcDbDatabase* pDb);
	Nano::ErrorStatus                     updateLeaderLinePosition();
	Nano::ErrorStatus                     removeLeaderLineRefAssoc(int leaderLineIndex) const;
	Nano::ErrorStatus                     updateContentScale(NcDbMLeaderObjectContextData* pContext);
	Nano::ErrorStatus                     setTextAttachmentDirection(NcDbMLeaderStyle::TextAttachmentDirection textAttachmentDirection);
	NcDbMLeaderStyle::TextAttachmentDirection textAttachmentDirection() const;

	OdDbMLeader* native() const;
protected:
	virtual Nano::ErrorStatus subGetClassID                  (CLSID* pClsid) const;
};

typedef signed char HostInt8;
#ifndef OD_DBMLINE_H
struct Mline
{
	typedef HostInt8 MlineJustification;
	enum
	{
		kTop = 0,
		kZero,
		kBottom
	};
	enum
	{
		kOpen = 0,
		kClosed,
		kMerged
	};
};
#endif

//////////////////////////////////////////////////////////////////////////
// NcDbMline
struct HostMline
{
	typedef HostInt8 MlineJustification;
	enum
	{
		kTop = 0,
		kZero,
		kBottom
	};
	enum
	{
		kOpen = 0,
		kClosed,
		kMerged
	};
};
class OdDbMline;
class NRXDBGATE_EXPORT NcDbMline: public  NcDbEntity
{
public:
	typedef NcDbMline  wrapper_class;
	typedef OdDbMline  native_class;

public:
	NCDB_DECLARE_MEMBERS(NcDbMline);
	NcDbMline();
	NcDbMline(OdRxObject* _object);
	~NcDbMline();

	Nano::ErrorStatus setStyle(const NcDbObjectId &newStyleId);
	NcDbObjectId      style() const;
	Nano::ErrorStatus setJustification(HostMline::MlineJustification newJust);
	HostMline::MlineJustification justification() const;
	Nano::ErrorStatus setScale(double newScale);
	double            scale() const;
	NcGeVector3d      normal            () const;
	Nano::ErrorStatus setNormal(const NcGeVector3d & newNormal);
	Nano::ErrorStatus appendSeg(const NcGePoint3d& newVertex);
	Nano::ErrorStatus removeLastSeg(NcGePoint3d& lastVertex);
	Nano::ErrorStatus moveVertexAt(int index, const NcGePoint3d& newPosition);
	Nano::ErrorStatus setClosedMline(bool closed);
	bool              closedMline() const;
	void              setSupressStartCaps(bool supressIt);
	bool              supressStartCaps() const;
	void              setSupressEndCaps(bool supressIt);
	bool              supressEndCaps() const;
	int               numVertices() const;
	int               element(const NcGePoint3d & pt) const;
	NcGePoint3d       vertexAt(int index) const;
	NcGeVector3d      axisAt(int index) const;
	NcGeVector3d      miterAt(int index) const;
	Nano::ErrorStatus getParametersAt(int index,
	                                  NcGeVoidPointerArray& params) const;
	Nano::ErrorStatus setParametersAt(int index,
	                                  NcGeVoidPointerArray& params);
	Nano::ErrorStatus getClosestPointTo(
	                     const NcGePoint3d& givenPoint,
	                     NcGePoint3d& pointOnCurve,
	                     bool extend,
	                     bool excludeCaps = false) const;
	Nano::ErrorStatus getClosestPointTo(
	                     const NcGePoint3d& givenPoint,
	                     const NcGeVector3d& normal,
	                     NcGePoint3d& pointOnCurve,
	                     bool extend,
	                     bool excludeCaps = false) const;
	void              getPlane(NcGePlane&) const;
	OdDbMline*        native() const;
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbMotionPath
class NRXDBGATE_EXPORT NcDbMotionPath : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbMotionPath);
	NcDbMotionPath();
	virtual ~NcDbMotionPath();
	NcDbObjectId        cameraPath() const;
	Nano::ErrorStatus   setCameraPath(const NcDbObjectId& id);
	NcDbObjectId        targetPath() const;
	Nano::ErrorStatus   setTargetPath(const NcDbObjectId& id);
	NcDbObjectId        viewTableRecordId() const;
	Nano::ErrorStatus   setViewTableRecordId(const NcDbObjectId& id);
	NRX::UInt32       frames() const;
	Nano::ErrorStatus   setFrames(NRX::UInt16 frames);
	NRX::UInt32       frameRate() const;
	Nano::ErrorStatus   setFrameRate(NRX::UInt16 rate);
	bool                cornerDecel() const;
	Nano::ErrorStatus   setCornerDecel(bool cornerDecel);
	virtual Nano::ErrorStatus dwgInFields  (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields (NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields  (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields (NcDbDxfFiler* pFiler) const;
protected:
	virtual NRX::UInt32  subSetAttributes (NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbMpolygonLoops
class NcDbMpolygonLoops {
public:
	NcDbMpolygonLoops(int lindex, int gindex = 0, int gcnt = 0);
	int mLoopIndex;
	bool mIsText;
	int mGripIndex;
	int mGripCount;
	NcGePoint2dArray mVertexPoints;
	NcGeDoubleArray mVertexBulges;
};

//////////////////////////////////////////////////////////////////////////
// NcDbNamedPath
class NRXDBGATE_EXPORT NcDbNamedPath : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbNamedPath);
	virtual ~NcDbNamedPath();
	NcDbNamedPath() {};
	virtual Nano::ErrorStatus   getGeometry(NcGeCurve3d *& pCurveGeometry) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbCurvePath
class NRXDBGATE_EXPORT NcDbCurvePath : public NcDbNamedPath {
public:
	NCRX_DECLARE_MEMBERS(NcDbCurvePath);
	NcDbCurvePath();
	virtual ~NcDbCurvePath();
	virtual Nano::ErrorStatus   getGeometry(NcGeCurve3d *& pCurveGeometry) const;
	Nano::ErrorStatus   setGeometry(const NcDbObjectId& id);
	NcDbObjectId        entityId() const;
	virtual Nano::ErrorStatus dwgInFields  (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields (NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields  (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields (NcDbDxfFiler* pFiler) const;
protected:
	virtual NRX::UInt32  subSetAttributes (NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbPointPath
class NRXDBGATE_EXPORT NcDbPointPath : public NcDbNamedPath {
public:
	NCRX_DECLARE_MEMBERS(NcDbPointPath);
	NcDbPointPath();
	virtual ~NcDbPointPath();
	virtual Nano::ErrorStatus   getGeometry(NcGeCurve3d *& pCurveGeometry) const;
	Nano::ErrorStatus   setGeometry(const NcGePoint3d& pt);
	virtual Nano::ErrorStatus dwgInFields  (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields (NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields  (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields (NcDbDxfFiler* pFiler) const;
protected:
	virtual NRX::UInt32  subSetAttributes (NcGiDrawableTraits* pTraits);
private:
	friend class NcDbPointPath;
};

//////////////////////////////////////////////////////////////////////////
// NcDbHomeView
class NcDbHomeView {
public:
	NRXDBGATE_EXPORT NcDbHomeView();
	NRXDBGATE_EXPORT NcDbHomeView(const NcDbHomeView& rhvw);
	NRXDBGATE_EXPORT virtual ~NcDbHomeView();
	NRXDBGATE_EXPORT const NcGePoint3d&     eye()           const;
	NRXDBGATE_EXPORT const NcGePoint3d&     center()        const;
	NRXDBGATE_EXPORT const NcGeVector3d&    up()            const;
	NRXDBGATE_EXPORT const double           width()         const;
	NRXDBGATE_EXPORT const double           height()        const;
	NRXDBGATE_EXPORT const bool             isPerspective() const;
	NRXDBGATE_EXPORT void setEye         (const NcGePoint3d& ptEye);
	NRXDBGATE_EXPORT void setCenter      (const NcGePoint3d& ptCenter);
	NRXDBGATE_EXPORT void setUp          (const NcGeVector3d& vUp);
	NRXDBGATE_EXPORT void setWidth       (double dWidth);
	NRXDBGATE_EXPORT void setHeight      (double dHeight);
	NRXDBGATE_EXPORT void setPerspective (bool bPerspective);
	NRXDBGATE_EXPORT Nano::ErrorStatus setHomeView(NcDbDatabase * pDb) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getHomeView(NcDbDatabase * pDb,
	                                               bool           bCreateDefault = false);
	NRXDBGATE_EXPORT void toggleDefaultSettings();
	NRXDBGATE_EXPORT bool            operator == (const NcDbHomeView& rhvw) const;
	NRXDBGATE_EXPORT bool            operator != (const NcDbHomeView& rhvw) const;
	NRXDBGATE_EXPORT NcDbHomeView&   operator  = (const NcDbHomeView& rhvw);
	NRXDBGATE_EXPORT bool isDefaultHomeView() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbNurbSurface
class NRXDBGATE_EXPORT NcDbNurbSurface: public NcDbSurface {
public:
	NcDbNurbSurface();
	NcDbNurbSurface(int uDegree, int vDegree, bool rational,
	                int uNumControlPoints, int vNumControlPoints,
	                const NcGePoint3dArray& ctrlPts,
	                const NcGeDoubleArray& weights,
	                const NcGeKnotVector& uKnots, const NcGeKnotVector& vKnots );
	virtual ~NcDbNurbSurface();
	NCDB_DECLARE_MEMBERS(NcDbNurbSurface);
	Nano::ErrorStatus get (int& uDegree, int& vDegree, bool& rational,
	                       int& uNumControlPoints, int& vNumControlPoints,
	                       NcGePoint3dArray& ctrlPts,
	                       NcGeDoubleArray& weights,
	                       NcGeKnotVector& uKnots, NcGeKnotVector& vKnots) const;
	Nano::ErrorStatus set (int uDegree, int vDegree, bool rational,
	                       int uNumControlPoints, int vNumControlPoints,
	                       const NcGePoint3dArray& ctrlPts,
	                       const NcGeDoubleArray& weights,
	                       const NcGeKnotVector& uKnots, const NcGeKnotVector& vKnots);
	Nano::ErrorStatus getControlPoints(int& uCount, int& vCount, NcGePoint3dArray& points) const;
	Nano::ErrorStatus setControlPoints(int uCount, int vCount, const NcGePoint3dArray& points);
	Nano::ErrorStatus getControlPointAt(int uIndex, int vIndex, NcGePoint3d& point) const;
	Nano::ErrorStatus setControlPointAt(int uIndex, int vIndex, const NcGePoint3d& point);
	Nano::ErrorStatus getNumberOfControlPointsInU(int& count) const;
	Nano::ErrorStatus getNumberOfControlPointsInV(int& count) const;
	Nano::ErrorStatus getUKnots(NcGeKnotVector& knots) const;
	Nano::ErrorStatus getVKnots(NcGeKnotVector& knots) const;
	Nano::ErrorStatus getNumberOfKnotsInU(int& count) const;
	Nano::ErrorStatus getNumberOfKnotsInV(int& count) const;
	Nano::ErrorStatus getWeight(int uIndex, int vIndex, double& weight ) const;
	Nano::ErrorStatus setWeight(int uIndex, int vIndex, double weight );
	Nano::ErrorStatus evaluate(double u, double v, NcGePoint3d& pos) const;
	Nano::ErrorStatus evaluate(double u, double v, NcGePoint3d& pos, NcGeVector3d& uDeriv, NcGeVector3d& vDeriv) const;
	Nano::ErrorStatus evaluate(double u, double v, NcGePoint3d& pos, NcGeVector3d& uDeriv, NcGeVector3d& vDeriv,
	                           NcGeVector3d& uuDeriv, NcGeVector3d& uvDeriv, NcGeVector3d& vvDeriv) const;
	Nano::ErrorStatus evaluate(double u, double v, int derivDegree, NcGePoint3d& point, NcGeVector3dArray& derivatives) const;
	Nano::ErrorStatus getDegreeInU(int& degree) const;
	Nano::ErrorStatus getDegreeInV(int& degree) const;
	Nano::ErrorStatus isClosedInU(bool& isClosed) const;
	Nano::ErrorStatus isClosedInV(bool& isClosed) const;
	Nano::ErrorStatus isPeriodicInU(bool& isPeriodic) const;
	Nano::ErrorStatus isPeriodicInV(bool& isPeriodic) const;
	Nano::ErrorStatus getPeriodInU(double& period) const;
	Nano::ErrorStatus getPeriodInV(double& period) const;
	Nano::ErrorStatus isRational(bool& isRational) const;
	Nano::ErrorStatus isPlanar(bool& isPlanar, NcGePoint3d& ptOnSurface, NcGeVector3d& normal) const;
	Nano::ErrorStatus isPointOnSurface(const NcGePoint3d& point, bool& onSurface) const;
	Nano::ErrorStatus getNormal(double u, double v, NcGeVector3d& normal) const;
	Nano::ErrorStatus getNumberOfSpansInU(int& span) const;
	Nano::ErrorStatus getNumberOfSpansInV(int& span) const;
	Nano::ErrorStatus getIsolineAtU(double u, NcArray<NcDbCurve*>& lineSegments) const;
	Nano::ErrorStatus getIsolineAtV(double v, NcArray<NcDbCurve*>& lineSegments) const;
	Nano::ErrorStatus InsertKnotAtU(double u);
	Nano::ErrorStatus InsertKnotAtV(double v);
	Nano::ErrorStatus InsertControlPointsAtU(double u, const NcGePoint3dArray& vCtrlPts, const NcGeDoubleArray& vWeights);
	Nano::ErrorStatus InsertControlPointsAtV(double v, const NcGePoint3dArray& uCtrlPts, const NcGeDoubleArray& uWeights);
	Nano::ErrorStatus RemoveControlPointsAtU(int uIndex);
	Nano::ErrorStatus RemoveControlPointsAtV(int vIndex);
	Nano::ErrorStatus rebuild(int uDegree, int vDegree, int numUCtrlPts, int numVCtrlPts, bool bRestore = false);
	Nano::ErrorStatus modifyPositionAndTangent(double u, double v, const NcGePoint3d& point,
	                                           const NcGeVector3d* uDeriv = NULL, const NcGeVector3d* vDeriv = NULL);
	Nano::ErrorStatus getParameterOfPoint(const NcGePoint3d& point, double& u, double& v) const;
	void              dragStatus         (const NcDb::DragStat status);
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbObjectContextCollectionIterator
class NRXDBGATE_EXPORT NRX_NO_VTABLE NcDbObjectContextCollectionIterator : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbObjectContextCollectionIterator);
	virtual Nano::ErrorStatus start() = 0;
	virtual bool              next() = 0;
	virtual bool              done() const = 0;
	virtual Nano::ErrorStatus getContext(NcDbObjectContext*& pObjectContext) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// ReadableNcDbObject
template<class NCDB_CLASS>
class ReadableNcDbObject {
public:
	ReadableNcDbObject()
	 :  mpObj(NULL),
	    mEs(Nano::eNotOpenForRead)
	{
	}
	ReadableNcDbObject(NCDB_CLASS*& pObj, NcDbObjectId id,
	                   bool bOpenErased, bool enableNow = true)
	 :  mpObj(NULL),
	    mEs(Nano::eNotOpenForRead)
	{
		if (enableNow)
			enableRead(pObj, id, bOpenErased);
	}
	void enableRead(NCDB_CLASS*& pObj,
	                NcDbObjectId id,
	                bool bOpenErased)
	{
		revertRead();
		pObj = NULL;
		if (Nano::eNotOpenForRead == mEs) {
			mEs = accessNcDbObjectForRead((NcDbObject*&) pObj,
			                              id,
			                              NCDB_CLASS::desc(),
			                              mbWasOpened,
			                              bOpenErased);
			DbObjPtr_Assert((Nano::eOk == mEs) == (NULL != pObj));
			DbObjPtr_Assert((NULL != pObj) ? pObj->isReadEnabled() : true);
			mpObj = pObj;
		}
	};
	void revertRead()
	{
		if ((Nano::eOk == mEs) && mbWasOpened &&
		    (mpObj != NULL) && !mpObj->objectId().isNull())
		    mEs = mpObj->close();
		mpObj = NULL;
		mEs = Nano::eNotOpenForRead;
	};
	~ReadableNcDbObject()
	{
		revertRead();
	};
	bool isReadable() const
	{
		return ((NULL != mpObj) && mpObj->isReadEnabled());
	};
	const NCDB_CLASS* object() const
	{
		return Nano::eOk == mEs ? mpObj : NULL;
	};
	NCDB_CLASS*       object()
	{
		return Nano::eOk == mEs ? mpObj : NULL;
	};
	Nano::ErrorStatus statusCode() const
	{
		return mEs;
	};
private:
	NCDB_CLASS*       mpObj;
	Nano::ErrorStatus mEs;
	bool              mbWasOpened;
	friend class NcDbSmartObjectPointer<NCDB_CLASS>;

	ReadableNcDbObject(NcDbObjectId id, bool bOpenErased, bool enableNow = true)
	:  mpObj(NULL),
	mEs(Nano::eNotOpenForRead)
	{
		if(enableNow) {
			enableRead(mpObj, id, bOpenErased);
		}
	}

	void forgetCurrentAndAcceptNewAsIs(NCDB_CLASS* pNewObj)
	{
		if (mpObj != pNewObj) {
			mpObj = pNewObj;
			mEs = (NULL == mpObj) ? Nano::eNotOpenForRead : Nano::eOk;
			mbWasOpened = (NULL != mpObj);
		}
	};
};

//////////////////////////////////////////////////////////////////////////
// WritableNcDbObject
class WritableNcDbObject {
public:
	WritableNcDbObject()
	    : mpObj(NULL), mEs(Nano::eNullObjectPointer), mbOpenOnLockedLayer(false)
	{
	}
	WritableNcDbObject(NcDbObject* pObj, bool enableNow = true, bool openOnLockedLayer = false)
	    : mpObj(NULL), mEs(Nano::eNullObjectPointer),
	      mbOpenOnLockedLayer(openOnLockedLayer)
	{
		replaceObject(pObj, enableNow);
	}
	void replaceObject(NcDbObject* pObj, bool enableNow = true)
	{
		revertWrite();
		mpObj = pObj;
		if (NULL == pObj) {
			mEs = Nano::eNullObjectPointer;
			return;
		}
		mEs = Nano::eNotOpenForWrite;
		if (enableNow)
			enableWrite();
	}
	bool enableWrite() {
		if (isWritable())
			return true;
		if (NULL == mpObj)
			return false;
		mEs = accessNcDbObjectForWrite(mpObj,
		                               mbWasNotifyEnabled,
		                               mbWasWriteEnabled,
		                               mReadCountClosed,
		                               mbOpenOnLockedLayer);
		return isWritable();
	};
	void revertWrite()
	{
		if ((NULL != mpObj) && !mpObj->objectId().isNull())
			mEs = revertNcDbObjectFromWrite(mpObj,
			                                mEs,
			                                mbWasNotifyEnabled,
			                                mbWasWriteEnabled,
			                                mReadCountClosed);
		forget();
	};
	~WritableNcDbObject()
	{
		revertWrite();
	};
	bool isWritable() const
	{
		return (Nano::eOk == mEs);
	};
	Nano::ErrorStatus statusCode() const
	{
		return mEs;
	};
	void forget()
	{
		mpObj = NULL;
		mEs = Nano::eNullObjectPointer;
	};
	void setOpenOnLockedLayer(bool openOnLockedLayer)
	{
		mbOpenOnLockedLayer = openOnLockedLayer;
	}
private:
	NcDbObject*       mpObj;
	Nano::ErrorStatus mEs;
	bool              mbWasNotifyEnabled;
	bool              mbWasWriteEnabled;
	bool              mbOpenOnLockedLayer;
	int               mReadCountClosed;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSmartObjectPointer
template<class NCDB_CLASS>
class NcDbSmartObjectPointer {
public:
	NcDbSmartObjectPointer();
	NcDbSmartObjectPointer(NcDbObjectId   objId,
	                       NcDb::OpenMode mode,
	                       bool           openErased = false,
	                       bool           openOnLockedLayer = false);
	virtual ~NcDbSmartObjectPointer();
	const NCDB_CLASS* object() const;
	NCDB_CLASS*       object();
	const NCDB_CLASS* operator->() const;
	NCDB_CLASS*       operator->();
	                  operator const NCDB_CLASS*() const;
#if DBOBJPTR_EXPOSE_PTR_REF
	                  NcDbSmartObjectPointer(NCDB_CLASS *pObject);
	                  operator NCDB_CLASS* &();
	void              operator=(NCDB_CLASS *pObject);
#else
	                  operator NCDB_CLASS*();
#endif
	Nano::ErrorStatus openStatus() const;
	Nano::ErrorStatus open(NcDbObjectId   objId,
	                       NcDb::OpenMode mode,
	                       bool           openErased = false,
	                       bool           openOnLockedLayer = false);
	Nano::ErrorStatus acquire(NCDB_CLASS *& pObjToAcquire);
	Nano::ErrorStatus release(NCDB_CLASS *& pReleasedObj);
	Nano::ErrorStatus close();
	Nano::ErrorStatus create();
protected:
	ReadableNcDbObject<NCDB_CLASS> mReadable;
	WritableNcDbObject             mWritable;
private:
	NcDbSmartObjectPointer(NcDbSmartObjectPointer & pObject);
	NcDbSmartObjectPointer& operator=(NcDbSmartObjectPointer & pObject);
	Nano::ErrorStatus closeInternal();
};

// --------- Inline definitions ---------

template<class NCDB_CLASS> inline
NcDbSmartObjectPointer<NCDB_CLASS>::NcDbSmartObjectPointer()
	: mReadable(),
	mWritable()
{
}

template<class NCDB_CLASS> inline
NcDbSmartObjectPointer<NCDB_CLASS>::NcDbSmartObjectPointer(
	NcDbObjectId   objId,
	NcDb::OpenMode mode,
	bool           openErased,
	bool           openOnLockedLayer)
	: mReadable(objId, openErased),
	mWritable(mReadable.object(), NcDb::kForWrite == mode, openOnLockedLayer)
{
}

template<class NCDB_CLASS> inline
NcDbSmartObjectPointer<NCDB_CLASS>::~NcDbSmartObjectPointer()
{
}

template<class NCDB_CLASS> inline Nano::ErrorStatus 
NcDbSmartObjectPointer<NCDB_CLASS>::open(
	NcDbObjectId   objId,
	NcDb::OpenMode mode,
	bool           openErased,
	bool           openOnLockedLayer)
{
	if (mReadable.isReadable()) {
		Nano::ErrorStatus closeStatus = closeInternal();
		if (closeStatus != Nano::eOk)
			return closeStatus;
	}
	mReadable.enableRead(mReadable.mpObj, objId, openErased);
	if (mReadable.isReadable()) {
		mWritable.setOpenOnLockedLayer(openOnLockedLayer);
		mWritable.replaceObject(mReadable.object(), (NcDb::kForWrite == mode));
	}
	return openStatus();
}

template<class NCDB_CLASS> inline const NCDB_CLASS *
NcDbSmartObjectPointer<NCDB_CLASS>::object() const
{
	DbObjPtr_Assert(mReadable.object() == NULL || mReadable.isReadable());
	return mReadable.object();
}

template<class NCDB_CLASS> inline NCDB_CLASS *
NcDbSmartObjectPointer<NCDB_CLASS>::object()
{
	DbObjPtr_Assert(mReadable.object() == NULL || mReadable.isReadable());
	return mReadable.object();
}

template<class NCDB_CLASS> inline const NCDB_CLASS *
NcDbSmartObjectPointer<NCDB_CLASS>::operator->() const
{
	return object();
}

template<class NCDB_CLASS> inline NCDB_CLASS *
NcDbSmartObjectPointer<NCDB_CLASS>::operator->()
{
	return object();
}

template<class NCDB_CLASS> inline 
NcDbSmartObjectPointer<NCDB_CLASS>::operator const NCDB_CLASS*() const
{
	return object();
}

#if DBOBJPTR_EXPOSE_PTR_REF
template<class NCDB_CLASS> inline 
NcDbSmartObjectPointer<NCDB_CLASS>::operator NCDB_CLASS* &()
{
	mWritable.forget();
	mReadable.forgetCurrentAndAcceptNewAsIs(mReadable.object());
	return mReadable.mpObj;
}
#else
template<class NCDB_CLASS> inline 
NcDbSmartObjectPointer<NCDB_CLASS>::operator NCDB_CLASS*()
{
	return object();
}
#endif

template<class NCDB_CLASS> inline Nano::ErrorStatus
NcDbSmartObjectPointer<NCDB_CLASS>::openStatus() const
{
	return (mWritable.isWritable() ||
		((mWritable.statusCode() != Nano::eNullObjectPointer) &&
		(mWritable.statusCode() != Nano::eNotOpenForWrite)))
		? mWritable.statusCode()
		: mReadable.statusCode();
}

template<class NCDB_CLASS> inline Nano::ErrorStatus
NcDbSmartObjectPointer<NCDB_CLASS>::acquire(NCDB_CLASS *& pObjToAcquire)
{
	closeInternal();
	mReadable.forgetCurrentAndAcceptNewAsIs(pObjToAcquire);
	pObjToAcquire = NULL;
	return Nano::eOk;
}

template<class NCDB_CLASS> inline Nano::ErrorStatus
NcDbSmartObjectPointer<NCDB_CLASS>::release(NCDB_CLASS *& pReleasedObj)
{
	pReleasedObj = mReadable.object();
	mWritable.forget();
	mReadable.forgetCurrentAndAcceptNewAsIs(NULL);
	return Nano::eOk;
}

template<class NCDB_CLASS> inline Nano::ErrorStatus
NcDbSmartObjectPointer<NCDB_CLASS>::close()
{
	closeInternal();
	return Nano::eOk;
}

template<class NCDB_CLASS> inline Nano::ErrorStatus
NcDbSmartObjectPointer<NCDB_CLASS>::create()
{
	NCDB_CLASS * pObject = new NCDB_CLASS;
	if (pObject == NULL)
		return Nano::eNullObjectPointer;
	closeInternal();
	mReadable.forgetCurrentAndAcceptNewAsIs(pObject);
	return Nano::eOk;
}

template<class NCDB_CLASS> inline Nano::ErrorStatus
NcDbSmartObjectPointer<NCDB_CLASS>::closeInternal()
{
	mWritable.revertWrite();
	mReadable.revertRead();

	return Nano::eOk;
}

#if DBOBJPTR_EXPOSE_PTR_REF

template<class NCDB_CLASS> inline
NcDbSmartObjectPointer<NCDB_CLASS>::NcDbSmartObjectPointer(NCDB_CLASS *pObject)
{
	acquire(pObject);
}

template<class NCDB_CLASS> inline void
NcDbSmartObjectPointer<NCDB_CLASS>::operator=(NCDB_CLASS *pObject)
{
	acquire(pObject);
}

#endif  // DBOBJPTR_EXPOSE_PTR_REF

//////////////////////////////////////////////////////////////////////////
// CRectangle3d
class CRectangle3d {
public:
	NcGePoint3d upLeft;
	NcGePoint3d upRight;
	NcGePoint3d lowLeft;
	NcGePoint3d lowRight;
};

//////////////////////////////////////////////////////////////////////////
// NcDbOleFrame
class NRXDBGATE_EXPORT NcDbOleFrame: public NcDbFrame {
public:
	NCDB_DECLARE_MEMBERS(NcDbOleFrame);
	NcDbOleFrame();
	virtual ~NcDbOleFrame();
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;
	virtual void* getOleObject(void) const;
	virtual void setOleObject(const void *pItem);
protected:
};

//////////////////////////////////////////////////////////////////////////
// NcDbCustomOsnapManager
class NcDbCustomOsnapManager {
public:
	virtual Nano::ErrorStatus addCustomOsnapMode(NcDbCustomOsnapMode* pMode) = 0;
	virtual Nano::ErrorStatus removeCustomOsnapMode(NcDbCustomOsnapMode* pMode) = 0;
	virtual Nano::ErrorStatus activateOsnapMode(const NCHAR * modeStr) = 0;
	virtual Nano::ErrorStatus deactivateOsnapMode(const NCHAR * modeStr) = 0;
	virtual NRX::Boolean modeIsActive(const NCHAR * modeStr) = 0;
	virtual int osnapGlyphSize() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbCustomOsnapMode2
class NRXDBGATE_EXPORT NcDbCustomOsnapMode2 : public NcDbCustomOsnapMode {
public:
	virtual HICON menuIcon()
	{
		return NULL;
	}
	virtual const NCHAR * displayString()
	{
		return localModeString();
	}
};

//////////////////////////////////////////////////////////////////////////
// NcDbPlaneSurface
class NRXDBGATE_EXPORT NcDbPlaneSurface: public NcDbSurface {
public:
	NcDbPlaneSurface ();
	virtual ~NcDbPlaneSurface();
	NCDB_DECLARE_MEMBERS(NcDbPlaneSurface);
	virtual Nano::ErrorStatus createFromRegion ( NcDbRegion *pRegion );
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;
	virtual bool isDependent() const;
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbPropertyFilterCustomizationPE
class NRXDBGATE_EXPORT NcDbPropertyFilterCustomizationPE : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbPropertyFilterCustomizationPE);
	virtual bool vetoCustomization(NcFilterablePropertyContext context,
	                               NcRxClass* pCls) const = 0;
	virtual bool createObject(NcDbDatabase* pDb,
	                          NcRxClass* pCls,
	                          NcDbEntity** ppEnt,
	                          NcDbObjectId& objId,
	                          const NcString& sGUID) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbRenderSettings
class NRXDBGATE_EXPORT NcDbRenderSettings : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbRenderSettings);
	NcDbRenderSettings();
	virtual ~NcDbRenderSettings();
	virtual NcGiDrawable* drawable();
	Nano::ErrorStatus setName(const NcString& strName);
	NcString name() const;
	void setDescription(const NcString& strDes);
	NcString description() const;
	void setDisplayIndex(int idx);
	int displayIndex() const;
	void setMaterialsEnabled(bool bEnabled);
	bool materialsEnabled() const;
	void setTextureSampling(bool bSampling);
	bool textureSampling() const;
	void setBackFacesEnabled(bool bEnabled);
	bool backFacesEnabled() const;
	void setShadowsEnabled(bool bEnabled);
	bool shadowsEnabled() const;
	Nano::ErrorStatus setPreviewImageFileName(const NcString& strFileName);
	NcString previewImageFileName() const;
	void setDiagnosticBackgroundEnabled(bool bEnabled);
	bool diagnosticBackgroundEnabled() const;
	virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	virtual Nano::ErrorStatus copyFrom(const NcRxObject* other);
	virtual bool operator==(const NcDbRenderSettings& settings);
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbMentalRayRenderSettings
class NRXDBGATE_EXPORT NcDbMentalRayRenderSettings : public NcDbRenderSettings {
public:
	NCRX_DECLARE_MEMBERS(NcDbMentalRayRenderSettings);
	NcDbMentalRayRenderSettings();
	virtual ~NcDbMentalRayRenderSettings();
	Nano::ErrorStatus setSampling(int iMin, int iMax);
	void sampling(int& iMin, int& iMax) const;
	Nano::ErrorStatus setSamplingFilter(NcGiMrFilter eFilter, double fWidth,
	                                    double fHeight);
	void SamplingFilter(NcGiMrFilter& eFilter, double& fWidth, double& fHeight)
	    const;
	Nano::ErrorStatus setSamplingContrastColor(float r, float g, float b,
	                                           float a);
	void samplingContrastColor(float& r, float& g, float& b, float& a) const;
	void setShadowMode(NcGiMrShadowMode eShadowMode);
	NcGiMrShadowMode shadowMode() const;
	void setShadowMapsEnabled(bool bEnabled);
	bool shadowMapsEnabled() const;
	void setRayTracingEnabled(bool bEnabled);
	bool rayTracingEnabled() const;
	Nano::ErrorStatus setRayTraceDepth(int iReflection, int iRefraction,
	                                   int iSum);
	void rayTraceDepth(int& iReflection, int& iRefraction, int& iSum) const;
	void setGlobalIlluminationEnabled(bool bEnabled);
	bool globalIlluminationEnabled() const;
	Nano::ErrorStatus setGISampleCount(int iNum);
	int giSampleCount() const;
	void setGISampleRadiusEnabled(bool bEnabled);
	bool giSampleRadiusEnabled() const;
	Nano::ErrorStatus setGISampleRadius(double fRadius);
	double giSampleRadius() const;
	Nano::ErrorStatus setGIPhotonsPerLight(int iNum);
	int giPhotonsPerLight() const;
	Nano::ErrorStatus setPhotonTraceDepth(int iReflection, int iRefraction,
	                                      int iSum);
	void photonTraceDepth(int& iReflection, int& iRefraction, int& iSum) const;
	void setFinalGatheringEnabled(bool bEnabled);
	bool finalGatheringEnabled() const;
	Nano::ErrorStatus setFinalGatheringMode(NcGiMrFinalGatheringMode mode);
	NcGiMrFinalGatheringMode finalGatheringMode() const;
	Nano::ErrorStatus setFGRayCount(int iNum);
	int fgRayCount() const;
	void setFGRadiusState(bool bMin, bool bMax, bool bPixels);
	void fgSampleRadiusState(bool& bMin, bool& bMax, bool& bPixels) const;
	Nano::ErrorStatus setFGSampleRadius(double fMin, double fMax);
	void fgSampleRadius(double& fMin, double& fMax) const;
	Nano::ErrorStatus setLightLuminanceScale(double fLuminance);
	double lightLuminanceScale() const;
	Nano::ErrorStatus setEnergyMultiplier(float fScale);
	float energyMultiplier() const;
	void setDiagnosticMode(NcGiMrDiagnosticMode eDiagnosticMode);
	NcGiMrDiagnosticMode diagnosticMode() const;
	Nano::ErrorStatus setDiagnosticGridMode(
	    NcGiMrDiagnosticGridMode eDiagnosticGridMode, float fSize);
	void diagnosticGridMode(
	    NcGiMrDiagnosticGridMode& eDiagnosticGridMode, float& fSize) const;
	void setDiagnosticPhotonMode(
	    NcGiMrDiagnosticPhotonMode eDiagnosticPhotonMode);
	NcGiMrDiagnosticPhotonMode diagnosticPhotonMode() const;
	void setDiagnosticSamplesMode(bool bDiagnosticSamplesMode);
	bool diagnosticSamplesMode() const;
	void setDiagnosticBSPMode(NcGiMrDiagnosticBSPMode eDiagnosticBSPMode);
	NcGiMrDiagnosticBSPMode diagnosticBSPMode() const;
	void setExportMIEnabled(bool bEnabled);
	bool exportMIEnabled() const;
	Nano::ErrorStatus setExportMIMode(NcGiMrExportMIMode eExportMIMode);
	NcGiMrExportMIMode exportMIMode() const;
	Nano::ErrorStatus setExportMIFileName(const NcString& strFileName);
	NcString exportMIFileName() const;
	Nano::ErrorStatus setTileSize(int iTileSize);
	int tileSize() const;
	void setTileOrder(NcGiMrTileOrder eTileOrder);
	NcGiMrTileOrder tileOrder() const;
	Nano::ErrorStatus setMemoryLimit(int iMemoryLimit);
	int memoryLimit() const;
	enum ShadowSamplingMultiplier {
		kSamplingMultiplierZero = 0,
		kSamplingMultiplierOneEighth,
		kSamplingMultiplierOneFourth,
		kSamplingMultiplierOneHalf,
		kSamplingMultiplierOne,
		kSamplingMultiplierTwo
	};
	Nano::ErrorStatus setShadowSamplingMultiplier(
	    NcDbMentalRayRenderSettings::ShadowSamplingMultiplier multiplier);
	NcDbMentalRayRenderSettings::ShadowSamplingMultiplier shadowSamplingMultiplier() const;
	virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	virtual bool operator==(const NcDbMentalRayRenderSettings& settings);
Nano::ErrorStatus copyFrom(const NcRxObject* other);
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* pTraits);
private:
	NRX::UInt32 baseSetAttributes(NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbRenderEnvironment
class NRXDBGATE_EXPORT NcDbRenderEnvironment : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbRenderEnvironment);
	NcDbRenderEnvironment();
	virtual ~NcDbRenderEnvironment();
	virtual NcGiDrawable* drawable();
	void setFogEnabled(bool bEnable);
	bool fogEnabled() const;
	void setFogBackgroundEnabled(bool bEnable);
	bool fogBackgroundEnabled() const;
	void setFogColor(const NcCmEntityColor& color);
	NcCmEntityColor fogColor() const;
	Nano::ErrorStatus setFogDensity(double dNear, double dFar);
	void fogDensity(double& dNear, double& dFar) const;
	Nano::ErrorStatus setDistances(double dNear, double dFar);
	void distances(double& dNear, double& dFar) const;
	void setEnvironmentImageEnabled(bool bEnabled);
	bool environmentImageEnabled() const;
	Nano::ErrorStatus setEnvironmentImageFileName(const NcString& strFileName);
	NcString environmentImageFileName() const;
	virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	virtual bool operator==(const NcDbRenderEnvironment& environment);
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbRenderGlobal
class NRXDBGATE_EXPORT NcDbRenderGlobal : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbRenderGlobal);
	enum Procedure
	{
		krView = 0,
		krCrop,
		krSelected
	};
	enum Destination
	{
		krWindow = 0,
		krViewport
	};
	NcDbRenderGlobal();
	virtual ~NcDbRenderGlobal();
	void setProcedureAndDestination(Procedure eProcedure,
	                                Destination eDestination);
	void procedureAndDestination(Procedure& eProcedure,
	                             Destination& eDestination) const;
	void setSaveEnabled(bool bEnabled);
	bool saveEnabled() const;
	Nano::ErrorStatus setSaveFileName(const NcString& strFileName);
	NcString saveFileName() const;
	Nano::ErrorStatus setDimensions(int w, int h);
	void dimensions(int& w, int& h) const;
	void setPredefinedPresetsFirst(bool bPredefinedPresetsFirst);
	bool predefinedPresetsFirst() const;
	void setHighInfoLevel(bool bHighInfoLevel);
	bool highInfoLevel() const;
	Nano::ErrorStatus setExposureType(NcGiMrExposureType type);
	NcGiMrExposureType exposureType() const;
	virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	Nano::ErrorStatus copyFrom( const NcRxObject* other );
};

//////////////////////////////////////////////////////////////////////////
// NcDbRevolvedSurface
class NRXDBGATE_EXPORT NcDbRevolvedSurface: public NcDbSurface {
public:
	NcDbRevolvedSurface ();
	virtual ~NcDbRevolvedSurface();
	NCDB_DECLARE_MEMBERS(NcDbRevolvedSurface);
	virtual Nano::ErrorStatus createRevolvedSurface ( NcDbEntity* pRevEnt,
	                                                 const NcGePoint3d& axisPnt, const NcGeVector3d& axisDir,
	                                                 double revAngle, double startAngle,
	                                                 NcDbRevolveOptions& revolveOptions );
	NcDbEntity*   getRevolveEntity () const;
	NcDb3dProfile* revolveProfile () const;
	NcGePoint3d        getAxisPnt () const;
	Nano::ErrorStatus  setAxisPnt ( const NcGePoint3d& pnt );
	NcGeVector3d       getAxisVec () const;
	Nano::ErrorStatus  setAxisVec ( const NcGeVector3d& vec );
	double             getRevolveAngle () const;
	Nano::ErrorStatus  setRevolveAngle ( double ang );
	double             getStartAngle () const;
	void               getRevolveOptions ( NcDbRevolveOptions& revolveOptions ) const;
	Nano::ErrorStatus  setRevolveOptions ( const NcDbRevolveOptions& revolveOptions );
	Nano::ErrorStatus  setRevolve ( const NcGePoint3d& axisPnt, const NcGeVector3d& axisVec,
	                               double revAngle, const NcDbRevolveOptions& revolveOptions );
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;
	virtual bool isDependent() const;
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbRevolveOptions
class OdDbRevolveOptions;
class NRXDBGATE_EXPORT NcDbRevolveOptions {
public:
	NcDbRevolveOptions ();
	NcDbRevolveOptions ( const NcDbRevolveOptions& src );
	~NcDbRevolveOptions ();

	typedef NcDbRevolveOptions wrapper_class;
	typedef OdDbRevolveOptions native_class;

	NcDbRevolveOptions& operator = ( const NcDbRevolveOptions& src );
	double  draftAngle () const;
	void  setDraftAngle ( double ang );
	double  twistAngle () const;
	void  setTwistAngle ( double ang );
	bool  closeToAxis () const;
	void  setCloseToAxis ( bool val );
	Nano::ErrorStatus  checkRevolveCurve ( NcDbEntity* pRevEnt,
	                                      const NcGePoint3d& axisPnt, const NcGeVector3d& axisDir,
	                                      bool& closed, bool& endPointsOnAxis, bool& planar,
	                                      bool displayErrorMessages = false );

	OdDbRevolveOptions* native() const;

private:
	OdDbRevolveOptions *m_pNative;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSweepOptions
class OdDbSweepOptions;
class NRXDBGATE_EXPORT NcDbSweepOptions
{
public:
		NcDbSweepOptions ();
		NcDbSweepOptions ( const NcDbSweepOptions& src );
		~NcDbSweepOptions ();

		NcDbSweepOptions& operator = ( const NcDbSweepOptions& src );

		enum AlignOption {
			kNoAlignment,
			kAlignSweepEntityToPath,
			kTranslateSweepEntityToPath,
			kTranslatePathToSweepEntity
		};

		enum MiterOption {
			kDefaultMiter,
			kOldMiter,
			kNewMiter,
			kCrimpMiter,
			kBendMiter
		};

		double  draftAngle () const;
		void  setDraftAngle ( double ang );
		double  startDraftDist () const;
		void  setStartDraftDist ( double val );
		double  endDraftDist () const;
		void  setEndDraftDist ( double val );
		double  twistAngle () const;
		void  setTwistAngle ( double ang );
		double  scaleFactor () const;
		void  setScaleFactor ( double val );
		double  alignAngle () const;
		void  setAlignAngle ( double ang );
		NcDbSweepOptions::AlignOption  align () const;
		void  setAlign ( NcDbSweepOptions::AlignOption val );
		NcDbSweepOptions::MiterOption  miterOption () const;
		void  setMiterOption ( NcDbSweepOptions::MiterOption val );
		bool  alignStart () const;
		void  setAlignStart ( bool val );
		NcGePoint3d  basePoint () const;
		void  setBasePoint ( NcGePoint3d& pnt );
		bool  bank () const;
		void  setBank ( bool val );
		bool  checkIntersections () const;
		void  setCheckIntersections ( bool val );
		NcGeVector3d  twistRefVec () const;
		void  setTwistRefVec ( const NcGeVector3d& vec );
		bool  getSweepEntityTransform ( NcGeMatrix3d& mat );
		void  setSweepEntityTransform ( NcGeMatrix3d& mat ); 
		Nano::ErrorStatus  setSweepEntityTransform ( NcArray<NcDbEntity*>& sweepEntities,
		                                             bool displayErrorMessages = false );

		bool  getPathEntityTransform ( NcGeMatrix3d& mat );
		void  setPathEntityTransform ( NcGeMatrix3d& mat ); 
		Nano::ErrorStatus  setPathEntityTransform ( NcDbEntity *pPathEnt,
		                                            bool displayErrorMessages = false );
		Nano::ErrorStatus  checkSweepCurve ( NcDbEntity *pSweepEnt,
		                                     NcDb::Planarity& planarity, NcGePoint3d& pnt, NcGeVector3d& vec,
		                                     bool& closed, double& approxArcLen, bool displayErrorMessages = false );
		Nano::ErrorStatus  checkPathCurve ( NcDbEntity *pPathEnt,
		                                    bool displayErrorMessages = false );

	OdDbSweepOptions* native() const;

private:
	OdDbSweepOptions *m_pNative;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSection
class NcDbSection : public NcDbEntity {
public:
	enum State
	{
		kPlane              = (0x1 << 0),
		kBoundary           = (0x1 << 1),
		kVolume             = (0x1 << 2),
	};

	enum SubItem
	{
		kNone               = 0,
		kSectionLine        = (0x1 << 0),
		kSectionLineTop     = (0x1 << 1),
		kSectionLineBottom  = (0x1 << 2),
		kBackLine           = (0x1 << 3),
		kBackLineTop        = (0x1 << 4),
		kBackLineBottom     = (0x1 << 5),
		kVerticalLineTop    = (0x1 << 6),
		kVerticalLineBottom = (0x1 << 7),
	};

	enum Height
	{
		kHeightAboveSectionLine = 0x1,
		kHeightBelowSectionLine = 0x2,
	};

public:
	NCDB_DECLARE_MEMBERS(NcDbSection);
	NRXDBGATE_EXPORT NcDbSection(void);
	NRXDBGATE_EXPORT NcDbSection(const NcGePoint3dArray& pts,
	                             const NcGeVector3d& verticalDir);
	NRXDBGATE_EXPORT NcDbSection(const NcGePoint3dArray& pts,
	                             const NcGeVector3d& verticalDir, const NcGeVector3d& vecViewingDir);
	NRXDBGATE_EXPORT ~NcDbSection(void);
	NRXDBGATE_EXPORT NcDbSection::State state      (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setState    (NcDbSection::State nState);
	NRXDBGATE_EXPORT const NCHAR* getName          (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getName     (NcString& sName) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getName     (NCHAR*& pszName) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setName     (const NCHAR* pszName);
	NRXDBGATE_EXPORT NcGeVector3d viewingDirection (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setViewingDirection(const NcGeVector3d& dir);
	NRXDBGATE_EXPORT NcGeVector3d verticalDirection(void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setVerticalDirection(const NcGeVector3d& dir);
	NRXDBGATE_EXPORT NcGeVector3d normal           (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus plane       (NcGeVector3d& uAxis,
	                                                NcGeVector3d& vAxis) const;
	NRXDBGATE_EXPORT int   indicatorTransparency   (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setIndicatorTransparency(int nTransparency);
	NRXDBGATE_EXPORT NcCmColor indicatorFillColor  (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setIndicatorFillColor(const NcCmColor& color);
	NRXDBGATE_EXPORT int numVertices               (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getVertex   (int nIndex,
	                                                NcGePoint3d& pt) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setVertex   (int nIndex,
	                                                const NcGePoint3d& pt);
	NRXDBGATE_EXPORT Nano::ErrorStatus addVertex   (int nInsertAt,
	                                                const NcGePoint3d& pt);
	NRXDBGATE_EXPORT Nano::ErrorStatus removeVertex(int nIndex);
	NRXDBGATE_EXPORT Nano::ErrorStatus getVertices (NcGePoint3dArray& pts) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setVertices (const NcGePoint3dArray& pts);
	NRXDBGATE_EXPORT double height                 (NcDbSection::Height nHeightType) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setHeight   (NcDbSection::Height nHeightType,
	                                                double fHeight);
	NRXDBGATE_EXPORT bool  hitTest                 (const NcGePoint3d& ptHit,
	                                                int* pSegmentIndex,
	                                                NcGePoint3d* ptOnSegment,
	                                                NcDbSection::SubItem* pSubItem) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus createJog   (const NcGePoint3d& ptOnSection);
	NRXDBGATE_EXPORT NcDbObjectId getSettings      (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getSettings (NcDbSectionSettings*& pSettings,
	                                                NcDb::OpenMode mode) const;
	NRXDBGATE_EXPORT bool  isLiveSectionEnabled    (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus enableLiveSection(bool bEnable);
	NRXDBGATE_EXPORT Nano::ErrorStatus generateSectionGeometry (NcDbEntity *pEnt,
	                                                            NcArray<NcDbEntity*>& intBoundaryEnts,
	                                                            NcArray<NcDbEntity*>& intFillEnts,
	                                                            NcArray<NcDbEntity*>& backgroundEnts,
	                                                            NcArray<NcDbEntity*>& foregroundEnts,
	                                                            NcArray<NcDbEntity*>& curveTangencyEnts) const;
public:
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler* pFiler);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler* pFiler);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus subClose();
	NRXDBGATE_EXPORT Nano::ErrorStatus generateSectionGeometry (const NcArray<NcDbEntity*>& entset,
	                                                            NcArray<NcDbEntity*>& intBoundaryEnts,
	                                                            NcArray<NcDbEntity*>& intFillEnts,
	                                                            NcArray<NcDbEntity*>& backgroundEnts,
	                                                            NcArray<NcDbEntity*>& foregroundEnts,
	                                                            NcArray<NcDbEntity*>& curveTangencyEnts) const;
protected:
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSectionSettings
class NcDbSectionSettings : public NcDbObject {
public:
	enum SectionType
	{
		kLiveSection                = (0x1 << 0),
		k2dSection                  = (0x1 << 1),
		k3dSection                  = (0x1 << 2),
	};
	enum Geometry
	{
		kIntersectionBoundary       = (0x1 << 0),
		kIntersectionFill           = (0x1 << 1),
		kBackgroundGeometry         = (0x1 << 2),
		kForegroundGeometry         = (0x1 << 3),
		kCurveTangencyLines         = (0x1 << 4),
	};
	enum Generation
	{
		kSourceAllObjects           = (0x1 << 0),
		kSourceSelectedObjects      = (0x1 << 1),
		kDestinationNewBlock        = (0x1 << 4),
		kDestinationReplaceBlock    = (0x1 << 5),
		kDestinationFile            = (0x1 << 6),
	};
public:
	NCDB_DECLARE_MEMBERS(NcDbSectionSettings);
	NcDbSectionSettings();
	~NcDbSectionSettings();
	NRXDBGATE_EXPORT Nano::ErrorStatus reset(void);
	NRXDBGATE_EXPORT Nano::ErrorStatus reset(NcDbSectionSettings::SectionType nSecType);
	NRXDBGATE_EXPORT NcDbSectionSettings::SectionType currentSectionType(void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setCurrentSectionType(NcDbSectionSettings::SectionType nSecType);
	NRXDBGATE_EXPORT NcDbSectionSettings::Generation generationOptions(NcDbSectionSettings::SectionType nSecType) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setGenerationOptions(NcDbSectionSettings::SectionType nSecType,
	                                                        NcDbSectionSettings::Generation nOptions);
	NRXDBGATE_EXPORT Nano::ErrorStatus getSourceObjects(NcDbSectionSettings::SectionType nSecType,
	                                                    NcDbObjectIdArray& ids) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setSourceObjects(NcDbSectionSettings::SectionType nSecType,
	                                                    const NcDbObjectIdArray& ids);
	NRXDBGATE_EXPORT NcDbObjectId destinationBlock(NcDbSectionSettings::SectionType nSecType) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setDestinationBlock(NcDbSectionSettings::SectionType nSecType,
	                                                       const NcDbObjectId& id);
	NRXDBGATE_EXPORT const NCHAR* destinationFile(NcDbSectionSettings::SectionType nSecType) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setDestinationFile(NcDbSectionSettings::SectionType nSecType,
	                                                      const NCHAR* pszFileName);
	NRXDBGATE_EXPORT bool  visibility              (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setVisibility(NcDbSectionSettings::SectionType nSecType,
	                                                 NcDbSectionSettings::Geometry nGeometry,
	                                                 bool bVisible);
	NRXDBGATE_EXPORT NcCmColor color               (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setColor    (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry,
	                                                const NcCmColor& color);
	NRXDBGATE_EXPORT const NCHAR* layer            (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setLayer    (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry,
	                                                const NCHAR* pszLayer);
	NRXDBGATE_EXPORT const NCHAR* linetype         (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setLinetype (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry,
	                                                const NCHAR* pszLinetype);
	NRXDBGATE_EXPORT double linetypeScale          (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setLinetypeScale(NcDbSectionSettings::SectionType nSecType,
	                                                    NcDbSectionSettings::Geometry nGeometry,
	                                                    double fScale);
	NRXDBGATE_EXPORT const NCHAR* plotStyleName    (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setPlotStyleName(NcDbSectionSettings::SectionType nSecType,
	                                                    NcDbSectionSettings::Geometry nGeometry,
	                                                    const NCHAR* pszPlotStyleName);
	NRXDBGATE_EXPORT NcDb::LineWeight lineWeight   (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setLineWeight(NcDbSectionSettings::SectionType nSecType,
	                                                 NcDbSectionSettings::Geometry nGeometry,
	                                                 NcDb::LineWeight nLineWeight);
	NRXDBGATE_EXPORT int   faceTransparency        (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setFaceTransparency(NcDbSectionSettings::SectionType nSecType,
	                                                       NcDbSectionSettings::Geometry nGeometry,
	                                                       int nTransparency);
	NRXDBGATE_EXPORT int   edgeTransparency        (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setEdgeTransparency(NcDbSectionSettings::SectionType nSecType,
	                                                       NcDbSectionSettings::Geometry nGeometry,
	                                                       int nTransparency);
	NRXDBGATE_EXPORT bool  hatchVisibility         (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setHatchVisibility(NcDbSectionSettings::SectionType nSecType,
	                                                      NcDbSectionSettings::Geometry nGeometry,
	                                                      bool bVisible);
	NRXDBGATE_EXPORT Nano::ErrorStatus getHatchPattern(NcDbSectionSettings::SectionType nSecType,
	                                                   NcDbSectionSettings::Geometry nGeometry,
	                                                   NcDbHatch::HatchPatternType& nPatternType,
	                                                   const NCHAR*& pszPatternName) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setHatchPattern(NcDbSectionSettings::SectionType nSecType,
	                                                   NcDbSectionSettings::Geometry nGeometry,
	                                                   NcDbHatch::HatchPatternType nPatternType,
	                                                   const NCHAR* pszPatternName);
	NRXDBGATE_EXPORT double hatchAngle             (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setHatchAngle(NcDbSectionSettings::SectionType nSecType,
	                                                 NcDbSectionSettings::Geometry nGeometry,
	                                                 double fAngle);
	NRXDBGATE_EXPORT double hatchSpacing           (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setHatchSpacing(NcDbSectionSettings::SectionType nSecType,
	                                                   NcDbSectionSettings::Geometry nGeometry,
	                                                   double fSpacing);
	NRXDBGATE_EXPORT double hatchScale             (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setHatchScale(NcDbSectionSettings::SectionType nSecType,
	                                                 NcDbSectionSettings::Geometry nGeometry,
	                                                 double fScale);
	NRXDBGATE_EXPORT bool  hiddenLine              (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setHiddenLine(NcDbSectionSettings::SectionType nSecType,
	                                                 NcDbSectionSettings::Geometry nGeometry,
	                                                 bool bHiddenLine);
	NRXDBGATE_EXPORT bool  divisionLines           (NcDbSectionSettings::SectionType nSecType,
	                                                NcDbSectionSettings::Geometry nGeometry) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus setDivisionLines(NcDbSectionSettings::SectionType nSecType,
	                                                    NcDbSectionSettings::Geometry nGeometry,
	                                                    bool bShow);
protected:
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSectionManager
class NcDbSectionManager : public NcDbObject {
public:
	NCDB_DECLARE_MEMBERS(NcDbSectionManager);
	NRXDBGATE_EXPORT Nano::ErrorStatus getSection  (const NCHAR* pszName,
	                                                NcDbObjectId& id) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getSection  (const NCHAR* pszName,
	                                                NcDbSection*& pSecPlane,
	                                                NcDb::OpenMode mode) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getLiveSection(NcDbObjectId& id) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getLiveSection(NcDbSection*& pSecPlane,
	                                                  NcDb::OpenMode mode) const;
	NRXDBGATE_EXPORT int   numSections             (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus newIterator (NcDbSectionManagerIterator*& pIterator) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getUniqueSectionName(const NCHAR* pszBaseName,
	                                                        NCHAR*& pszUniqueName) const;
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler* pFiler);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler* pFiler);
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
public:
	NRXDBGATE_EXPORT NcDbSectionManager(void);
	NRXDBGATE_EXPORT ~NcDbSectionManager(void);
protected:
	NRXDBGATE_EXPORT virtual Nano::ErrorStatus subGetClassID  (CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSectionManagerIterator
class NcDbSectionManagerIterator {
public:
	NRXDBGATE_EXPORT virtual ~NcDbSectionManagerIterator(void);
	NRXDBGATE_EXPORT void  start                   (void);
	NRXDBGATE_EXPORT void  step                    (void);
	NRXDBGATE_EXPORT bool  done                    (void) const;
	NRXDBGATE_EXPORT NcDbObjectId      getSection  (void) const;
	NRXDBGATE_EXPORT Nano::ErrorStatus getSection  (NcDbSection*& pSecPlane,
	                                                NcDb::OpenMode openMode) const;
protected:
	NRXDBGATE_EXPORT NcDbSectionManagerIterator(NcDbSectionManager* pMgr);
};

//////////////////////////////////////////////////////////////////////////
// NcDbSelectGrip
class NRXDBGATE_EXPORT NRX_NO_VTABLE NcDbSelectGrip : public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbSelectGrip);
	virtual bool SelectGrip(const NcDbEntity * pEnt,
	                        const NcGiViewportDrawNrx* pVd,
	                        const void * pAppData) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSpatialIndex
class NRXDBGATE_EXPORT NcDbSpatialIndex: public NcDbIndex {
public:
	NCDB_DECLARE_MEMBERS(NcDbSpatialIndex);
	     NcDbSpatialIndex();
	virtual ~NcDbSpatialIndex();
	virtual NcDbFilteredBlockIterator* newIterator(const NcDbFilter* pFilter)
	                                               const;
	virtual Nano::ErrorStatus rebuildFull(NcDbIndexUpdateData* pIdxData);
protected:
	virtual Nano::ErrorStatus rebuildModified(NcDbBlockChangeIterator* iter);
};

//////////////////////////////////////////////////////////////////////////
// NcDbSpatialIndexIterator
class NRXDBGATE_EXPORT NcDbSpatialIndexIterator : public NcDbFilteredBlockIterator {
public:
	NcDbSpatialIndexIterator(const NcDbSpatialIndex*  pIndex,
	                         const NcDbSpatialFilter* pFilter);
	virtual ~NcDbSpatialIndexIterator();
	virtual Nano::ErrorStatus start();
	virtual NcDbObjectId      next();
	virtual NcDbObjectId      id() const;
	virtual Nano::ErrorStatus seek(NcDbObjectId id);
	virtual double estimatedHitFraction() const;
	virtual Nano::ErrorStatus accepts(NcDbObjectId id,
	                                  NRX::Boolean& stat) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSubDMesh
class OdDbSubDMesh;
class NRXDBGATE_EXPORT NcDbSubDMesh: public NcDbEntity {
	NCDB_DECLARE_MEMBERS(NcDbSubDMesh);
public:
	typedef NcDbSubDMesh  wrapper_class;
	typedef OdDbSubDMesh  native_class;

	                            NcDbSubDMesh            ();
	                            NcDbSubDMesh            (OdRxObject *_object);
	virtual                    ~NcDbSubDMesh            ();
	virtual NRX::Boolean        subWorldDraw            (NcGiWorldDraw * wd) override;     // NcGiDrawable
	Nano::ErrorStatus           setSubDMesh             (const NcGePoint3dArray& vertexArray,
	                                                     const NcArray<NRX::Int32>& faceArray,
	                                                     int subDLevel);
	Nano::ErrorStatus           setSphere               (double radius,
	                                                     int divAxis,
	                                                     int divHeight,
	                                                     int subDLevel);
	Nano::ErrorStatus           setCylinder             (double majorRadius,
	                                                     double minorRadius,
	                                                     double height,
	                                                     int divAxis,
	                                                     int divHeight,
	                                                     int divCap,
	                                                     int subDLevel);
	Nano::ErrorStatus           setCone                 (double majorRadius,
	                                                     double minorRadius,
	                                                     double height,
	                                                     int divAxis,
	                                                     int divHeight,
	                                                     int divCap,
	                                                     double radiusRatio,
	                                                     int subDLevel);
	Nano::ErrorStatus           setTorus                (double majorRadius,
	                                                     int divSection,
	                                                     int divSweepPath,
	                                                     double sectionRadiusRatio,
	                                                     double sectionRotate,
	                                                     int subDLevel);
	Nano::ErrorStatus           setBox                  (double xLen,
	                                                     double yLen,
	                                                     double zLen,
	                                                     int divX,
	                                                     int divY,
	                                                     int divZ,
	                                                     int subDLevel);
	Nano::ErrorStatus           setWedge                (double xLen,
	                                                     double yLen,
	                                                     double zLen,
	                                                     int divLength,
	                                                     int divWidth,
	                                                     int divHeight,
	                                                     int divSlope,
	                                                     int divCap,
	                                                     int subDLevel);
	Nano::ErrorStatus           setPyramid              (double radius,
	                                                     double height,
	                                                     int divLength,
	                                                     int divHeight,
	                                                     int divCap,
	                                                     int nSides,
	                                                     double radiusRatio,
	                                                     int subDLevel);
	Nano::ErrorStatus           subdDivideUp            ();
	Nano::ErrorStatus           subdDivideDown          ();
	Nano::ErrorStatus           subdRefine              ();
	Nano::ErrorStatus           subdRefine              (const NcDbFullSubentPathArray& subentPaths);
	Nano::ErrorStatus           subdLevel               (NRX::Int32& result) const;
	Nano::ErrorStatus           splitFace               (const NcDbSubentId& subentFaceId,
	                                                     const NcDbSubentId& subent0,
	                                                     const NcGePoint3d& point0,
	                                                     const NcDbSubentId& subent1,
	                                                     const NcGePoint3d& point1);
	Nano::ErrorStatus           extrudeFaces            (const NcDbFullSubentPathArray& subentPaths,
	                                                     double length,
	                                                     const NcGeVector3d& dir,
	                                                     double taper);
	Nano::ErrorStatus           extrudeFaces            (const NcDbFullSubentPathArray& subentPaths,
	                                                     const NcGePoint3dArray& alongPath,
	                                                     double taper);
	Nano::ErrorStatus           extrudeConnectedFaces   (const NcDbFullSubentPathArray& subentPaths,
	                                                     double length,
	                                                     const NcGeVector3d& dir,
	                                                     double taper);
	Nano::ErrorStatus           extrudeConnectedFaces   (const NcDbFullSubentPathArray& subentPaths,
	                                                     const NcGePoint3dArray& alongPath,
	                                                     double taper);
	Nano::ErrorStatus           mergeFaces              (const NcDbFullSubentPathArray& subentPaths);
	Nano::ErrorStatus           collapse                (const NcDbSubentId& subent);
	Nano::ErrorStatus           cap                     (const NcDbFullSubentPathArray& edgePaths);
	Nano::ErrorStatus           spin                    (const NcDbSubentId& subent);
	Nano::ErrorStatus           isWatertight            (bool& result) const;
	Nano::ErrorStatus           numOfFaces              (NRX::Int32& result) const;
	Nano::ErrorStatus           numOfSubDividedFaces    (NRX::Int32& result) const;
	Nano::ErrorStatus           numOfSubDividedFacesAt  (const NcDbFullSubentPathArray& subentPaths, NRX::Int32& result) const;
	Nano::ErrorStatus           numOfVertices           (NRX::Int32& result) const;
	Nano::ErrorStatus           numOfSubDividedVertices (NRX::Int32& result) const;
	Nano::ErrorStatus           numOfEdges              (NRX::Int32& result) const;
	Nano::ErrorStatus           getVertices             (NcGePoint3dArray& vertexArray) const;
	Nano::ErrorStatus           getEdgeArray            (NcArray<NRX::Int32>& edgeArray) const;
	Nano::ErrorStatus           getFaceArray            (NcArray<NRX::Int32>& faceArray) const;
	Nano::ErrorStatus           getNormalArray          (NcGeVector3dArray& normalArray) const;
	Nano::ErrorStatus           getSubDividedVertices   (NcGePoint3dArray& vertexArray) const;
	Nano::ErrorStatus           getSubDividedFaceArray  (NcArray<NRX::Int32>& faceArray) const;
	Nano::ErrorStatus           getSubDividedNormalArray(NcGeVector3dArray& normalArray) const;
	Nano::ErrorStatus           getVertexAt             (NRX::Int32 nIndex, NcGePoint3d& vertex) const;
	Nano::ErrorStatus           setVertexAt             (NRX::Int32 nIndex, const NcGePoint3d& vertex);
	Nano::ErrorStatus           getVertexAt             (const NcDbSubentId& id, NcGePoint3d& vertex) const;
	Nano::ErrorStatus           setVertexAt             (const NcDbSubentId& id, const NcGePoint3d& vertex);
	Nano::ErrorStatus           getSubDividedVertexAt   (NRX::Int32 nIndex, NcGePoint3d& vertex) const;
	Nano::ErrorStatus           getSubDividedVertexAt   (const NcDbSubentId& id, NcGePoint3d& vertex) const;
	Nano::ErrorStatus           setCrease               (double creaseVal);
	Nano::ErrorStatus           setCrease               (const NcDbFullSubentPathArray& subentPaths, double creaseVal);
	Nano::ErrorStatus           getCrease               (const NcDbFullSubentPathArray& subentPaths, NcArray<double>& result) const;
	Nano::ErrorStatus           getCrease               (const NcDbSubentId& id, double& result) const;
	Nano::ErrorStatus           getAdjacentSubentPath   (const NcDbFullSubentPath& path,
	                                                     NcDb::SubentType type,
	                                                     NcDbFullSubentPathArray& subentPaths) const;
	Nano::ErrorStatus           getSubentPath           (NRX::Int32 nIndex,
	                                                     NcDb::SubentType type,
	                                                     NcDbFullSubentPathArray& subentPaths) const;
	Nano::ErrorStatus           convertToSurface        (bool bConvertAsSmooth, const NcDbSubentId& id, NcDbSurface*& pSurface) const;
	Nano::ErrorStatus           convertToSurface        (bool bConvertAsSmooth, bool optimize, NcDbSurface*& pSurface) const;
	Nano::ErrorStatus           convertToSolid          (bool bConvertAsSmooth, bool optimize, NcDb3dSolid*& pSolid) const;
	Nano::ErrorStatus           getSubentColor          (const NcDbSubentId& id, NcCmColor& color) const;
	Nano::ErrorStatus           setSubentColor          (const NcDbSubentId& id, const NcCmColor& color);
	Nano::ErrorStatus           getSubentMaterial       (const NcDbSubentId& id, NcDbObjectId& material) const;
	Nano::ErrorStatus           setSubentMaterial       (const NcDbSubentId& id, const NcDbObjectId& material);
	Nano::ErrorStatus           getSubentMaterialMapper (const NcDbSubentId& id, NcGiMapper& mapper) const;
	Nano::ErrorStatus           setSubentMaterialMapper (const NcDbSubentId& id, const NcGiMapper& mapper);
	Nano::ErrorStatus           getFacePlane            (const NcDbSubentId& id, NcGePlane& facePlane) const;
	Nano::ErrorStatus           computeVolume           (double &retVolume) const;
	Nano::ErrorStatus           computeSurfaceArea      (double &retSurfArea) const;
	virtual void                dragStatus              (const NcDb::DragStat status);
	virtual Nano::ErrorStatus   subGetClassID           (CLSID* pClsid) const;
	virtual bool                bounds                  ( NcDbExtents& retBounds ) const;
	Nano::ErrorStatus           setSphere               (const NcGeMatrix3d& xForm,
	                                                     int divAxis,
	                                                     int divHeight,
	                                                     int subDLevel);
	Nano::ErrorStatus           setCylinder             (const NcGeMatrix3d& xForm,
	                                                     int divAxis,
	                                                     int divHeight,
	                                                     int divCap,
	                                                     int subDLevel);
	Nano::ErrorStatus           setCone                 (const NcGeMatrix3d& xForm,
	                                                     int divAxis,
	                                                     int divHeight,
	                                                     int divCap,
	                                                     double radiusRatio,
	                                                     int subDLevel);
	Nano::ErrorStatus           setTorus                (const NcGeMatrix3d& xForm,
	                                                     int divSection,
	                                                     int divSweepPath,
	                                                     double sectionRadiusRatio,
	                                                     double sectionRotate,
	                                                     int subDLevel);
	Nano::ErrorStatus           setBox                  (const NcGeMatrix3d& xForm,
	                                                     int divX,
	                                                     int divY,
	                                                     int divZ,
	                                                     int subDLevel);
	Nano::ErrorStatus           setWedge                (const NcGeMatrix3d& xForm,
	                                                     int divLength,
	                                                     int divWidth,
	                                                     int divHeight,
	                                                     int divSlope,
	                                                     int divCap,
	                                                     int subDLevel);
	Nano::ErrorStatus           setPyramid              (const NcGeMatrix3d& xForm,
	                                                     int divLength,
	                                                     int divHeight,
	                                                     int divCap,
	                                                     int nSides,
	                                                     double radiusRatio,
	                                                     int subDLevel);
	Nano::ErrorStatus           computeRayIntersection  (const NcGePoint3d &rayStart,
	                                                     const NcGeVector3d &rayDir,
	                                                     NcArray<NcDbSubentId> &retSubents,
	                                                     NcArray<double> &retIntersectDist,
	                                                     NcGePoint3dArray& retIntersectPoint) const;
	Nano::ErrorStatus           setVertexNormalArray(NcGeVector3dArray &arr);
	Nano::ErrorStatus           setVertexTextureArray(NcGePoint3dArray &arr);
	Nano::ErrorStatus           setVertexColorArray(NcArray<NcCmEntityColor> &arr);
	Nano::ErrorStatus           getVertexNormalArray(NcGeVector3dArray &arr);
	Nano::ErrorStatus           getVertexTextureArray(NcGePoint3dArray &arr);
	Nano::ErrorStatus           getVertexColorArray(NcArray<NcCmEntityColor> &arr);

public:
	OdDbSubDMesh * native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbSun
class NRXDBGATE_EXPORT NcDbSun : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbSun);
private:
	static NRX::UInt32 kCurrentVersionNumber;
public:
	NcDbSun();
	~NcDbSun();
	virtual NcGiDrawable* drawable();
	virtual DrawableType  drawableType() const { return NcGiDrawable::kDistantLight; }
	virtual void          setGsNode(NcGsNode* gsnode);
	virtual NcGsNode*     gsNode() const;
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler *pFiler) const;
	virtual Nano::ErrorStatus dxfInFields (NcDbDxfFiler *pFiler);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler *pFiler) const;
	virtual Nano::ErrorStatus dwgInFields (NcDbDwgFiler *pFiler);
	virtual Nano::ErrorStatus decomposeForSave(
	        NcDb::NcDbDwgVersion ver,
	        NcDbObject*& replaceObj,
	        NcDbObjectId& replaceId,
	        NRX::Boolean& exchangeXData);
	virtual bool isOn() const;
	virtual Nano::ErrorStatus setOn(bool value);
	virtual double intensity() const;
	virtual Nano::ErrorStatus setIntensity(double intensity);
	virtual const NcCmColor& sunColor() const;
	virtual Nano::ErrorStatus setSunColor(const NcCmColor& color);
	virtual const NcGiShadowParameters& shadowParameters() const;
	virtual void setShadowParameters(const NcGiShadowParameters& params);
	virtual Nano::ErrorStatus setDateTime(const NcDbDate& datetime);
	virtual const NcDbDate& dateTime() const;
	virtual Nano::ErrorStatus setDayLightSavingsOn(bool value);
	virtual bool isDayLightSavingsOn() const;
	virtual Nano::ErrorStatus setAzimuth(double azimuth);
	virtual double azimuth() const;
	virtual Nano::ErrorStatus setAltitude(double altitude);
	virtual double altitude() const;
	virtual const NcGeVector3d& sunDirection() const;
	virtual void setSunDirection(const NcGeVector3d& sundir);
	Nano::ErrorStatus setSkyParameters(const NcGiSkyParameters& params);
	Nano::ErrorStatus skyParameters(NcGiSkyParameters& params) const;
protected:
	virtual NRX::UInt32 subSetAttributes(NcGiDrawableTraits* pTraits);
};

//////////////////////////////////////////////////////////////////////////
// NcDbSweptSurface
class NcDbSweptSurface: public NcDbSurface {
public:
	NcDbSweptSurface ();
	virtual ~NcDbSweptSurface();
	NCDB_DECLARE_MEMBERS(NcDbSweptSurface);
	virtual Nano::ErrorStatus createSweptSurface ( NcDbEntity* pSweepEnt,
	                                              NcDbEntity* pPathEnt, NcDbSweepOptions& sweepOptions );
	NcDbEntity*   getSweepEntity () const;
	NcDbEntity*   getPathEntity () const;
	NRXDBGATE_EXPORT NcDb3dProfile* sweepProfile () const;
	NRXDBGATE_EXPORT NcDb3dProfile* pathProfile () const;
	void               getSweepOptions ( NcDbSweepOptions& sweepOptions ) const;
	Nano::ErrorStatus  setSweepOptions ( const NcDbSweepOptions& sweepOptions );
	Nano::ErrorStatus  getPathLength ( double& len ) const;
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;
	virtual bool isDependent() const;
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbBlockReferenceIdIterator
class NRXDBGATE_EXPORT NcDbBlockReferenceIdIterator {
public:
	~NcDbBlockReferenceIdIterator();
	void              start () { mPos = 0; }
	bool              done  () const { return mPos >= mAry.length(); }
	Nano::ErrorStatus getBlockReferenceId (NcDbObjectId& id) const;
	Nano::ErrorStatus getDatabase (NcDbDatabase*& pDb) const;
	Nano::ErrorStatus getBlockReference(NcDbBlockReference*& pBlkRef,
	                                    NcDb::OpenMode openMode, bool openErasedEntity = false) const;
	void              step () { mPos++; }
	Nano::ErrorStatus seek (NcDbObjectId id);
private:
	NcDbBlockReferenceIdIterator();
	friend class NcDbBlockTableRecord;
	int               mPos;
	NcDbObjectIdArray mAry;
};

//////////////////////////////////////////////////////////////////////////
// NcDbTableContent
class NRXDBGATE_EXPORT NcDbTableContent : public NcDbFormattedTableData {
public:
	NCDB_DECLARE_MEMBERS(NcDbTableContent);
	NcDbTableContent(void);
	virtual ~NcDbTableContent(void);
	virtual NcDbObjectId tableStyleId(void) const;
	virtual Nano::ErrorStatus setTableStyleId(const NcDbObjectId& idTableStyle);
	virtual const NCHAR* cellStyle(int nRow,
	                               int nCol) const;
	virtual Nano::ErrorStatus setCellStyle(int nRow,
	                                       int nCol,
	                                       const NCHAR* pszCellStyle);
	virtual double rowHeight      (int nRow) const;
	virtual Nano::ErrorStatus setRowHeight(int nRow,
	                                       double fWidth);
	virtual double columnWidth    (int nCol) const;
	virtual Nano::ErrorStatus setColumnWidth(int nCol,
	                                         double fWidth);
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* pFiler) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbTableIterator
class NRXDBGATE_EXPORT NcDbTableIterator {
public:
	NcDbTableIterator(const NcDbTable* pTable);
	NcDbTableIterator(const NcDbTable* pTable, const NcCellRange* pRange,
	                  NcDb::TableIteratorOption nOption);
	NcDbTableIterator(const NcDbLinkedTableData* pTable);
	NcDbTableIterator(const NcDbLinkedTableData* pTable, const NcCellRange* pRange,
	                  NcDb::TableIteratorOption nOption);
	NcDbTableIterator(const NcCellRange& range);
	NcDbTableIterator(const NcCellRange& range, NcDb::TableIteratorOption nOption);
	~NcDbTableIterator();
	void            start                   (void);
	void            step                    (void);
	bool            done                    (void);
	bool            seek                    (const NcCell& cell);
	const NcCell&   getCell                 (void) const;
	int             getRow                  (void) const;
	int             getColumn               (void) const;
protected:
	NcDbTableIterator(void);
};

//////////////////////////////////////////////////////////////////////////
// NcDbTableTemplate
class NRXDBGATE_EXPORT NcDbTableTemplate : public NcDbTableContent {
public:
	NCDB_DECLARE_MEMBERS(NcDbTableTemplate);
	NcDbTableTemplate(void);
	NcDbTableTemplate(const NcDbTable* pTable, NcDb::TableCopyOption nCopyOption);
	virtual ~NcDbTableTemplate(void);
	virtual Nano::ErrorStatus capture       (const NcDbTable* pTable, NcDb::TableCopyOption nCopyOption);
	virtual Nano::ErrorStatus createTable   (NcDbTable*& pTable, NcDb::TableCopyOption nCopyOption);
	virtual Nano::ErrorStatus dwgInFields   (NcDbDwgFiler* pFiler);
	virtual Nano::ErrorStatus dwgOutFields  (NcDbDwgFiler* pFiler) const;
	virtual Nano::ErrorStatus dxfInFields   (NcDbDxfFiler* pFiler);
	virtual Nano::ErrorStatus dxfOutFields  (NcDbDxfFiler* pFiler) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbUnderlayDefinition
class NRXDBGATE_EXPORT NRX_NO_VTABLE NcDbUnderlayDefinition: public NcDbObject {
public:
	NCDB_DECLARE_MEMBERS(NcDbUnderlayDefinition);
	NcDbUnderlayDefinition();
	virtual ~NcDbUnderlayDefinition() = 0;
	Nano::ErrorStatus setSourceFileName(const NCHAR* file);
	const NCHAR* getSourceFileName() const;
	INcReadStream* getReadStream() const;
	Nano::ErrorStatus getActiveFileName(const NCHAR*& file) const;
	Nano::ErrorStatus getActiveFileName(NcString& file) const;
	Nano::ErrorStatus setItemName(const NCHAR* item);
	const NCHAR* getItemName() const;
	Nano::ErrorStatus setUnderlayItem(const NCHAR* sourceFileName, const NCHAR* activeFileName, NcDbUnderlayItem* pItem);
	const NcDbUnderlayItem* getUnderlayItem() const;
	Nano::ErrorStatus load(const wchar_t* password);
	void unload();
	bool isLoaded() const;
	static NcString dictionaryKey(const NcRxClass* underlayDefinitionType);
private:
	virtual const NcDbUnderlayHost* getUnderlayHost() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDwfDefinition
class NRXDBGATE_EXPORT NcDbDwfDefinition: public NcDbUnderlayDefinition {
public:
	NCDB_DECLARE_MEMBERS(NcDbDwfDefinition);
	NcDbDwfDefinition();
	virtual ~NcDbDwfDefinition();
	NRX::Boolean isDWFx(void) const;
private:
	virtual  const NcDbUnderlayHost* getUnderlayHost() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDgnDefinition
class NRXDBGATE_EXPORT NcDbDgnDefinition: public NcDbUnderlayDefinition {
public:
	NCDB_DECLARE_MEMBERS(NcDbDgnDefinition);
	NcDbDgnDefinition();
	virtual ~NcDbDgnDefinition();
	bool useMasterUnits() const;
	void setUseMasterUnits(bool useMaster);
	int xrefDepth() const;
	void setXrefDepth(int depth);
	bool showRasterRef() const;
	void setShowRasterRef(bool bShow);
private:
	virtual const NcDbUnderlayHost* getUnderlayHost() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbPdfDefinition
class NcDbPdfDefinition: public NcDbUnderlayDefinition {
public:
	NCDB_DECLARE_MEMBERS(NcDbPdfDefinition);
	NRXDBGATE_EXPORT NcDbPdfDefinition();
	NRXDBGATE_EXPORT virtual ~NcDbPdfDefinition();
private:
	virtual  const NcDbUnderlayHost* getUnderlayHost() const;
};

//////////////////////////////////////////////////////////////////////////
// NcUnderlayLayer
class OdUnderlayLayer;
class NRXDBGATE_EXPORT NcUnderlayLayer {
public:
	NcUnderlayLayer();
	~NcUnderlayLayer();

	typedef enum {
		kOff = 0,
		kOn = 1
	} State;

	NcString name() const;
	State state() const;
	Nano::ErrorStatus setName(const NcString& name);
	Nano::ErrorStatus setState(State state);

	const OdUnderlayLayer* native() const;
	OdUnderlayLayer* native();

private:
	OdUnderlayLayer* _native;
};
////////////////////////////////////////////////////////////////////////
// NcDbUnderlayDrawContext
struct OdDbUnderlayDrawContext;
struct NcDbUnderlayDrawContext
{
	NRX::UInt8 contrast;
	NRX::UInt8 fade;
	bool monochrome;
	bool adjustColorForBackground;
	NcArray<NcUnderlayLayer> layers;
};

//////////////////////////////////////////////////////////////////////////
// NcDbUnderlayItem
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcDbUnderlayItem {
public:
	virtual ~NcDbUnderlayItem() = 0;
	virtual NcString getName() const = 0;
	virtual Nano::ErrorStatus getThumbnail(
	                            BITMAPINFO*& thumbnail) const = 0;
	virtual Nano::ErrorStatus getExtents(
	                            NcGePoint2d& min,
	                            NcGePoint2d& max) const = 0;
	virtual NcDb::UnitsValue getUnits() const = 0;
	virtual bool usingPartialContent() const = 0;
	virtual Nano::ErrorStatus draw(
	    NcGiWorldDraw* pWorldDraw,
	    NcGiViewportDrawNrx* pViewportDraw,
	    const NcDbUnderlayDrawContext& context) const = 0;
	virtual NcGeMatrix3d modelTransform() const = 0;
	virtual Nano::ErrorStatus getOsnapPoints(const NcGeMatrix3d& modelToWorld,
	                                         NcDb::OsnapMode osnapMode,
	                                         NRX::GsMarker   gsSelectionMark,
	                                         const NcGePoint3d&  pickPoint,
	                                         const NcGePoint3d&  lastPoint,
	                                         const NcGeMatrix3d& viewXform,
	                                         NcGePoint3dArray&      snapPoints,
	                                         NcDbIntArray &   geomIds)
	                                         const = 0;
	virtual NcDbEntity* getSubEntityAtGsMarker(const NcGeMatrix3d& modelToWorld,NRX::GsMarker gsSelectionMark) const = 0;
	virtual Nano::ErrorStatus intersectWith(const NcGeMatrix3d& modelToWorld,
	                                        const NcDbEntity* pEnt,
	                                        NcDb::Intersect intType,
	                                        const NcGePlane* projPlane,
	                                        NcGePoint3dArray& points,
	                                        NRX::GsMarker thisGsMarker,
	                                        NRX::GsMarker otherGsMarker) const = 0;
	virtual NRX::UInt32 underlayLayerCount() const { return 0; }
	virtual Nano::ErrorStatus getUnderlayLayer(int idx, NcUnderlayLayer& layer) const { return Nano::eNotImplementedYet; }
	int version() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDgnUnderlayItem
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcDbDgnUnderlayItem : public NcDbUnderlayItem {
public:
	virtual bool useMasterUnits() const = 0;
	virtual void setUseMasterUnits(bool bUseMasterUnits) = 0;
	virtual bool showRasterRef() const = 0;
	virtual void setShowRasterRef(bool bShow) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbUnderlayFile
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcDbUnderlayFile {
public:
	virtual ~NcDbUnderlayFile() = 0;
	virtual int getItemCount() const = 0;
	virtual Nano::ErrorStatus getItem(
	                            int i,
	                            NcDbUnderlayItem*& pItem) const = 0;
	virtual Nano::ErrorStatus getItem(
	                            const NCHAR* name,
	                            NcDbUnderlayItem*& pItem) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbUnderlayHost
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcDbUnderlayHost {
public:
	virtual Nano::ErrorStatus getFile(
	                            const NCHAR* fullPath,
	                            const wchar_t* password,
	                            NcDbUnderlayFile*& pFile) const = 0;
	virtual Nano::ErrorStatus getFile(
	                            INcReadStream* pFileStream,
	                            const wchar_t* password,
	                            NcDbUnderlayFile*& pFile) const = 0;
	static void getAdjustedColor(
	                           NcGeVector3d& rgbResult,
	                           const NcGeVector3d& rgbInputColor,
	                           const NcGeVector3d& rgbCurrentBackgroundColor,
	                           const NcGeVector3d& hslFadedContrastColor,
	                           const NcDbUnderlayDrawContext& drawContext);
protected:
	virtual ~NcDbUnderlayHost() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbUnderlayReference
class NRX_NO_VTABLE NRXDBGATE_EXPORT NcDbUnderlayReference: public NcDbEntity {
public:
	NCDB_DECLARE_MEMBERS(NcDbUnderlayReference);
	virtual ~NcDbUnderlayReference() = 0;
	NcGePoint3d       position() const;
	Nano::ErrorStatus setPosition(const NcGePoint3d& position);
	NcGeScale3d       scaleFactors() const;
	Nano::ErrorStatus setScaleFactors(const NcGeScale3d& scale);
	double            rotation() const;
	Nano::ErrorStatus setRotation(double rotation);
	NcGeVector3d      normal() const;
	Nano::ErrorStatus setNormal(const NcGeVector3d& normal);
	NcGeMatrix3d transform() const;
	Nano::ErrorStatus setTransform(const NcGeMatrix3d& transform);
	NcDbObjectId      definitionId() const;
	Nano::ErrorStatus setDefinitionId(NcDbObjectId id);
	const NcGePoint2dArray&  clipBoundary() const;
	Nano::ErrorStatus        setClipBoundary(const NcGePoint2dArray& clipBoundary);
	bool                     isClipped() const;
	Nano::ErrorStatus        setIsClipped(bool value);
	NRX::UInt8      contrast() const;
	Nano::ErrorStatus setContrast(NRX::UInt8 value);
	NRX::UInt8      fade() const;
	Nano::ErrorStatus setFade(NRX::UInt8 value);
	bool              isOn() const;
	Nano::ErrorStatus setIsOn(bool value);
	bool              isMonochrome() const;
	Nano::ErrorStatus setIsMonochrome(bool value);
	bool              isAdjustedForBackground() const;
	Nano::ErrorStatus setIsAdjustedForBackground(bool value);
	virtual bool isFrameVisible() const;
	virtual bool isFramePlottable() const;
	NRX::UInt32 underlayLayerCount() const;
	Nano::ErrorStatus getUnderlayLayer(int index, NcUnderlayLayer& layer) const;
	Nano::ErrorStatus setUnderlayLayer(int index, const NcUnderlayLayer& layer);
	static NRX::UInt8 contrastLowerLimit();
	static NRX::UInt8 contrastUpperLimit();
	static NRX::UInt8 contrastDefault();
	static NRX::UInt8 fadeLowerLimit();
	static NRX::UInt8 fadeUpperLimit();
	static NRX::UInt8 fadeDefault();
	bool isClipInverted() const;
	Nano::ErrorStatus setClipInverted(bool value);
	Nano::ErrorStatus generateClipBoundaryFromPline(NcDbObjectId polyId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbDwfReference
class NRXDBGATE_EXPORT NcDbDwfReference: public NcDbUnderlayReference {
public:
	NCDB_DECLARE_MEMBERS(NcDbDwfReference);
	NcDbDwfReference();
	virtual ~NcDbDwfReference();
protected:
	virtual Nano::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDgnReference
class NRXDBGATE_EXPORT NcDbDgnReference: public NcDbUnderlayReference {
public:
	NCDB_DECLARE_MEMBERS(NcDbDgnReference);
	NcDbDgnReference();
	virtual ~NcDbDgnReference();
	void setXrefDepth(int depth);
protected:
	virtual Nano::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbPdfReference
class NcDbPdfReference: public NcDbUnderlayReference {
public:
	NCDB_DECLARE_MEMBERS(NcDbPdfReference);
	NRXDBGATE_EXPORT NcDbPdfReference();
	NRXDBGATE_EXPORT virtual ~NcDbPdfReference();
protected:
	virtual Nano::ErrorStatus   subGetClassID(CLSID* pClsid) const;
public:
	static NRX::UInt8 contrastDefault();
	static NRX::UInt8 fadeDefault();
};

//////////////////////////////////////////////////////////////////////////
// NcDbXrecordIterator
class NRXDBGATE_EXPORT NcDbXrecordIterator: public NcRxObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbXrecordIterator);
	NcDbXrecordIterator(const NcDbXrecord* pXrecord);
	virtual ~NcDbXrecordIterator();
	void              start();
	bool              done() const;
	Nano::ErrorStatus next();
	int               curRestype() const;
	Nano::ErrorStatus getCurResbuf(resbuf& outItem, NcDbDatabase* db) const;
protected:
	NcDbXrecordIterator() {};
private:
	friend class NcDbXrecord;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDisableAnnoAutoScale
class NRXDBGATE_EXPORT NcDbDisableAnnoAutoScale {
public:
	NcDbDisableAnnoAutoScale ();
	~NcDbDisableAnnoAutoScale ();
private:
	short mSaveAnnoAutoScale;
	short mSaveAnnoAutoScaleLayout;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDgnRefFileRepath
class NRXDBGATE_EXPORT NcDbDgnRefFileRepath {
public:
	NcDbDgnRefFileRepath() : m_fileHandle(NULL)  {};
	Nano::ErrorStatus setFile(const NcString& dgnPathAndFilename, const NCHAR* pwd);
	~NcDbDgnRefFileRepath();
	Nano::ErrorStatus getReferenceFilePaths(NcDbRefFileDataPtrArray& refFiles);
	Nano::ErrorStatus rePath(const NcDbDgnRefFileIdArray& refFileIds,
	                         const NcStringArray& newRefFileNames);
private:
	void* m_fileHandle;
};

//////////////////////////////////////////////////////////////////////////
// NcDbRasterVariables
class NRXDBGATE_EXPORT NcDbRasterVariables : public NcDbObject {
public:
	static ClassVersion        classVersion();
	NCRX_DECLARE_MEMBERS(NcDbRasterVariables);
	enum FrameSettings {
		kImageFrameInvalid  = -1,
		kImageFrameOff      =  0,
		kImageFrameAbove    =  1,
		kImageFrameBelow    =  2,
		kImageFrameOnNoPlot =  3
	};
	enum ImageQuality {
		kImageQualityInvalid = -1,
		kImageQualityDraft = 0,
		kImageQualityHigh  = 1
	};
	static NcDbRasterVariables* create();
	NcDbRasterVariables();
	virtual     ~NcDbRasterVariables();
	virtual Nano::ErrorStatus   dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus   dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus   dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus   dxfOutFields(NcDbDxfFiler* filer) const;
	virtual FrameSettings       imageFrame() const;
	virtual Nano::ErrorStatus   setImageFrame( FrameSettings value );
	virtual ImageQuality        imageQuality() const;
	virtual Nano::ErrorStatus   setImageQuality( ImageQuality value );
	virtual NcDbRasterImageDef::Units userScale() const;
	virtual Nano::ErrorStatus   setUserScale(
	                                NcDbRasterImageDef::Units units );
	static NcDbRasterVariables* openRasterVariables(
	                                NcDb::OpenMode mode,
	                                NcDbDatabase* pDatabase = 0
	                                );
private:
#ifdef MEM_DEBUG
#undef new
#undef delete
#endif
	void *operator new[](size_t nSize) { return 0;}
	void operator delete[](void *p) {};
	void *operator new[](size_t nSize, const char *file, int line) { return 0;}
#ifdef MEM_DEBUG
#define new DEBUG_NEW
#define delete DEBUG_DELETE
#endif
	static ClassVersion         mVersion;
};

//////////////////////////////////////////////////////////////////////////
// NcDbRasterImageDefFileAccessReactor
class NRXDBGATE_EXPORT NcDbRasterImageDefFileAccessReactor : public NcDbObjectReactor {
public:
	NCRX_DECLARE_MEMBERS(NcDbRasterImageDefFileAccessReactor);
	virtual     ~NcDbRasterImageDefFileAccessReactor();
	virtual void                onAttach(
	                                const NcDbRasterImageDef*,
	                                const NCHAR * pPath) = 0;
	virtual void                onDetach(
	                                const NcDbRasterImageDef*,
	                                const NCHAR * pPath) = 0;
	virtual NRX::Boolean      onOpen(
	                                const NcDbRasterImageDef*,
	                                const NCHAR * pPath,
	                                const NCHAR * pActivePath,
	                                NRX::Boolean& replacePath,
	                                NCHAR *& replacementPath) = 0;
	virtual NRX::Boolean      onPathChange(
	                                const NcDbRasterImageDef*,
	                                const NCHAR * pPath,
	                                const NCHAR * pActivePath,
	                                NRX::Boolean& replacePath,
	                                NCHAR *& replacementPath) = 0;
	virtual void                onClose(
	                                const NcDbRasterImageDef*,
	                                const NCHAR * pPath) = 0;
	virtual void                onDialog(
	                                 NcDbRasterImageDef*,
	                                 const NCHAR * pCaption,
	                                 const NCHAR * pFileExtensions
	                             ) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbAuditInfo
class NcDbAuditInfoFactory;
class NRXDBGATE_EXPORT NcDbAuditInfo
{
public:
	enum AuditPass
	{
		PASS1 = 1,
		PASS2 = 2
	};

	NcDbAuditInfo();
	~NcDbAuditInfo();

	bool  fixErrors(void) const;
	int numErrors() const;
	int numFixes(void) const;
	void errorsFound(int count);    
	void errorsFixed(int count);    
	AuditPass auditPass(void) const;
	void printError(NCHAR const * name, NCHAR const * value, NCHAR const * validation = nullptr, NCHAR const * defaultValue = nullptr);
	void printError(const NcDbObject *pObj, const NCHAR * value, const NCHAR * validation, const NCHAR * defaultValue);
	void requestRegen();
	void resetNumEntities();
	void incNumEntities();
	int numEntities();
	void printNumEntities(const NCHAR* msg);
	Nano::ErrorStatus fetchObject(NcDbObjectId originalObjId, NcDbObjectId& newObjId, NcRxClass* pObjClass, bool uneraseIfPossible = false, bool createIfNotFound = true, bool externalDbOk = false);
	Nano::ErrorStatus registerObject(NcDbHandle handle, bool objIsValid, NcRxClass* pObjClass);
	Nano::ErrorStatus updateObject(NcDbHandle   handle,
		bool         setFileObjIsValid,
		bool         setNewObjIsValid,
		bool         setFileObjClass,
		bool         setNewObjClass,
		bool         setNewObjId,
		bool         fileObjIsValid,
		bool         newObjIsValid,
		NcRxClass*   pFileObjClass,
		NcRxClass*   pNewObjClass,
		NcDbObjectId newObjId);
	protected:
		friend class NcDbAuditInfoFactory;
		void* m_pImp;
		NcDbAuditInfo(void* imp);
private:
		bool         m_bAutoDelete;
};

class NcDbImpSortentsTable;
//////////////////////////////////////////////////////////////////////////
// NcDbSortentsTable
class NRXDBGATE_EXPORT NcDbSortentsTable : public NcDbObject {
public:
	NCRX_DECLARE_MEMBERS(NcDbSortentsTable);
	                    NcDbSortentsTable();
	virtual             ~NcDbSortentsTable();
	NRX::Boolean        sortAs(NcDbObjectId, NcDbHandle&) const;
	void                getSortHandle(NcDbObjectId id, NcDbHandle& h) const;
	Nano::ErrorStatus   remove(NcDbObjectId);
	Nano::ErrorStatus   moveToBottom(const NcDbObjectIdArray& ar);
	Nano::ErrorStatus   moveToTop(const NcDbObjectIdArray& ar);
	Nano::ErrorStatus   moveBelow(const NcDbObjectIdArray& ar,
	                              NcDbObjectId target);
	Nano::ErrorStatus   moveAbove(const NcDbObjectIdArray& ar,
	                              NcDbObjectId target);
	Nano::ErrorStatus   swapOrder(NcDbObjectId, NcDbObjectId);
	Nano::ErrorStatus   setBlockId(NcDbObjectId);
	NcDbObjectId        blockId() const;
	Nano::ErrorStatus   firstEntityIsDrawnBeforeSecond(NcDbObjectId first,
	                                                   NcDbObjectId second,
	                                                   bool& result) const;
	Nano::ErrorStatus   getFullDrawOrder(NcDbObjectIdArray& ents,
	                                     NRX::UInt8 honorSortentsMask=0) const;
	Nano::ErrorStatus   getRelativeDrawOrder(NcDbObjectIdArray& ar,
	                                         NRX::UInt8 honorSortentsMask=0) const;
	Nano::ErrorStatus   setRelativeDrawOrder(const NcDbObjectIdArray& ar);
	virtual Nano::ErrorStatus   applyPartialUndo(NcDbDwgFiler*, NcRxClass*);
	virtual Nano::ErrorStatus   dwgInFields(NcDbDwgFiler*);
	virtual Nano::ErrorStatus   dwgOutFields(NcDbDwgFiler*) const;
	virtual Nano::ErrorStatus   dxfInFields(NcDbDxfFiler*);
	virtual Nano::ErrorStatus   dxfOutFields(NcDbDxfFiler*) const;
	virtual Nano::ErrorStatus   audit(NcDbAuditInfo* pAuditInfo);
private:
	friend class NcDbSystemInternals;
	friend class NcDbImpSortentsTable;
	NcDbImpSortentsTable*   m_pImp;
protected:
	virtual Nano::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbDatabaseSummaryInfo
class OdDbDatabaseSummaryInfo;
class NRXDBGATE_EXPORT NcDbDatabaseSummaryInfo : public NcRxObject { //  NRX_NO_VTABLE
public:
	NCRX_DECLARE_MEMBERS(NcDbDatabaseSummaryInfo);

public:
	typedef NcDbDatabaseSummaryInfo  wrapper_class;
	typedef OdDbDatabaseSummaryInfo  native_class;

public:
	NcDbDatabaseSummaryInfo(NcDbDatabase* pDb);

	virtual Nano::ErrorStatus copyFrom(const NcRxObject* other);


	virtual Nano::ErrorStatus getTitle(NCHAR*& title) const; // = 0;
	virtual Nano::ErrorStatus setTitle(const NCHAR* title); // = 0;
	virtual Nano::ErrorStatus getSubject(NCHAR*& subject) const; // = 0;
	virtual Nano::ErrorStatus setSubject(const NCHAR* subject); // = 0;
	virtual Nano::ErrorStatus getAuthor(NCHAR*& author) const; // = 0;
	virtual Nano::ErrorStatus setAuthor(const NCHAR* author); // = 0;
	virtual Nano::ErrorStatus getKeywords(NCHAR*& keywordlist) const; // = 0;
	virtual Nano::ErrorStatus setKeywords(const NCHAR* keywordlist); // = 0;
	virtual Nano::ErrorStatus getComments(NCHAR*& comments) const; // = 0;
	virtual Nano::ErrorStatus setComments(const NCHAR* comments); // = 0;
	virtual Nano::ErrorStatus getLastSavedBy(NCHAR*& lastSavedBy) const; // = 0;
	virtual Nano::ErrorStatus setLastSavedBy(const NCHAR* lastSavedBy); // = 0;
	virtual Nano::ErrorStatus getRevisionNumber(NCHAR*& revisionNumber) const; // = 0;
	virtual Nano::ErrorStatus setRevisionNumber(const NCHAR* revisionNumber); // = 0;
	virtual Nano::ErrorStatus getHyperlinkBase(NCHAR*& HyperlinkBase) const; // = 0;
	virtual Nano::ErrorStatus setHyperlinkBase(const NCHAR* HyperlinkBase); // = 0;
	virtual int numCustomInfo() const; // = 0;
	virtual Nano::ErrorStatus addCustomSummaryInfo(const NCHAR* key, const NCHAR* value ); // = 0;
	virtual Nano::ErrorStatus deleteCustomSummaryInfo(const int index); // = 0;
	virtual Nano::ErrorStatus deleteCustomSummaryInfo(const NCHAR* key); // = 0;
	virtual Nano::ErrorStatus getCustomSummaryInfo(const int index, NCHAR*& key,
	                                               NCHAR *& value ) const; // = 0;
	virtual Nano::ErrorStatus setCustomSummaryInfo (const int index, const NCHAR* key,
	                                                const NCHAR *value ); // = 0;
	virtual Nano::ErrorStatus getCustomSummaryInfo(const NCHAR *customInfoKey,
	                                               NCHAR *& value ) const; // = 0;
	virtual Nano::ErrorStatus setCustomSummaryInfo (const NCHAR *customInfoKey,
	                                                const NCHAR *value ); // = 0;
	virtual NcDbDatabase* database() const; // = 0;
	virtual void setDatabase(NcDbDatabase *pDb); // = 0;
	virtual ~NcDbDatabaseSummaryInfo() {};
protected:
	NcDbDatabaseSummaryInfo();
public:
	OdDbDatabaseSummaryInfo* native() const;};

//////////////////////////////////////////////////////////////////////////
// NcDbSummaryInfoReactor
class NRX_NO_VTABLE NcDbSummaryInfoReactor {
public:
	virtual void summaryInfoHasChanged(
	                 const NcDbDatabase* pDb,
	                 const NcDbDatabaseSummaryInfo* pDbProp) {};
	virtual ~NcDbSummaryInfoReactor() {};
};

//////////////////////////////////////////////////////////////////////////
// NcDbSummaryInfoManager
class NRX_NO_VTABLE NcDbSummaryInfoManager {
public:
	virtual void  addReactor(NcDbSummaryInfoReactor* pReact) = 0;
	virtual void  removeReactor(NcDbSummaryInfoReactor* pReact) = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcDbOle2Frame
class NRXDBGATE_EXPORT NcDbOle2Frame: public NcDbOleFrame {
public:
	NCDB_DECLARE_MEMBERS(NcDbOle2Frame);
	NcDbOle2Frame();
	virtual ~NcDbOle2Frame();
	virtual Nano::ErrorStatus dwgInFields(NcDbDwgFiler* filer);
	virtual Nano::ErrorStatus dwgOutFields(NcDbDwgFiler* filer) const;
	virtual Nano::ErrorStatus dxfInFields(NcDbDxfFiler* filer);
	virtual Nano::ErrorStatus dxfOutFields(NcDbDxfFiler* filer) const;
	NcCmTransparency            transparency() const;
	virtual Nano::ErrorStatus   setTransparency(const NcCmTransparency& trans,
	                                            NRX::Boolean doSubents = true);
	NcDb::Visibility            visibility() const;
	virtual Nano::ErrorStatus   setVisibility(NcDb::Visibility newVal,
	                                          NRX::Boolean doSubents = true);
	virtual void                saveAs(NcGiWorldDraw* mode, NcDb::SaveType st);
	virtual void* getOleObject(void) const;
	virtual void setOleObject(const void *pItem);
	void* getOleItemHost() const;
	COleClientItem* getOleClientItem(void) const;
	Nano::ErrorStatus setOleClientItem(const COleClientItem* pItem);
	virtual void getLocation(NcGePoint3d& point3d) const;
	void setLocation(const NcGePoint3d& point3d);
	virtual void position(CRectangle3d& rect3d) const;
	virtual void setPosition(const CRectangle3d& rect3d);
	virtual void position(RECT& rect) const;
	virtual void setPosition(const RECT& rect);
	virtual void getUserType(NCHAR * pszName, int nNameSize) const;
	virtual int getType(void) const;
	virtual NRX::Boolean getLinkName(NCHAR * pszName, int nNameSize) const;
	virtual NRX::Boolean getLinkPath(NCHAR * pszPath, int nPathSize) const;
	virtual NRX::UInt8 outputQuality() const;
	virtual void setOutputQuality(NRX::UInt8);
	NRX::Boolean autoOutputQuality() const;
	void setAutoOutputQuality(NRX::UInt8);
	double rotation() const;
	Nano::ErrorStatus setRotation(const double rotation);
	double wcsWidth() const;
	Nano::ErrorStatus setWcsWidth(const double wcsWidth);
	double wcsHeight() const;
	Nano::ErrorStatus setWcsHeight(const double wcsHeight);
	double scaleWidth() const;
	Nano::ErrorStatus setScaleWidth(const double scaleWidth);
	double scaleHeight() const;
	Nano::ErrorStatus setScaleHeight(const double scaleHeight);
	NRX::Boolean lockAspect() const;
	Nano::ErrorStatus setLockAspect(const NRX::Boolean bLockAspect);
protected:
	virtual Nano::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

// AutoGen:

//////////////////////////////////////////////////////////////////////////
// NcDbDimensionStyleOverrule
class NRXDBGATE_EXPORT NcDbDimensionStyleOverrule : public NcRxOverrule {
public:
	NCRX_DECLARE_MEMBERS(NcDbDimensionStyleOverrule);
	NcDbDimensionStyleOverrule();
	virtual NcDbObjectId   dimensionStyle  (const NcDbDimension* pSubject);
	virtual Nano::ErrorStatus   setDimensionStyle (NcDbDimension* pSubject,
	                                                                NcDbObjectId dimStyleId);
	virtual Nano::ErrorStatus   getDimstyleData   (const NcDbDimension* pSubject,
	                                                                NcDbDimStyleTableRecord*& pRecord);
	virtual Nano::ErrorStatus   setDimstyleData   (NcDbDimension* pSubject,
	                                                                NcDbDimStyleTableRecord* pRecord);
	virtual Nano::ErrorStatus   setDimstyleData   (NcDbDimension* pSubject,
	                                                                NcDbObjectId dimstyleId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbPropertiesOverrule
class NRXDBGATE_EXPORT NcDbPropertiesOverrule : public NcRxOverrule {
public:
	NCRX_DECLARE_MEMBERS(NcDbPropertiesOverrule);
	NcDbPropertiesOverrule();
	virtual void list(const NcDbEntity* pSubject);
	virtual Nano::ErrorStatus getClassID(const NcDbObject* pSubject, CLSID* pClsid);
};

//////////////////////////////////////////////////////////////////////////
// NcDbOsnapOverrule
class OdDbOsnapOverrule;
class NRXDBGATE_EXPORT NcDbOsnapOverrule : public NcRxOverrule
{
public:
	NCRX_DECLARE_MEMBERS(NcDbOsnapOverrule);

  typedef NcDbOsnapOverrule  wrapper_class;
  typedef OdDbOsnapOverrule  native_class;

public:
  NcDbOsnapOverrule();
  ~NcDbOsnapOverrule();
  NcDbOsnapOverrule(OdRxObject* _object);

	virtual Nano::ErrorStatus getOsnapPoints(
	                            const NcDbEntity*   pSubject,
	                            NcDb::OsnapMode     osnapMode,
	                            NRX::GsMarker     gsSelectionMark,
	                            const NcGePoint3d&  pickPoint,
	                            const NcGePoint3d&  lastPoint,
	                            const NcGeMatrix3d& viewXform,
	                            NcGePoint3dArray&   snapPoints,
	                            NcDbIntArray &   geomIds);
	virtual Nano::ErrorStatus getOsnapPoints(
	                            const NcDbEntity*   pSubject,
	                            NcDb::OsnapMode     osnapMode,
	                            NRX::GsMarker     gsSelectionMark,
	                            const NcGePoint3d&  pickPoint,
	                            const NcGePoint3d&  lastPoint,
	                            const NcGeMatrix3d& viewXform,
	                            NcGePoint3dArray&   snapPoints,
	                            NcDbIntArray &   geomIds,
	                            const NcGeMatrix3d& insertionMat);
	virtual bool isContentSnappable(const NcDbEntity*   pSubject);

public:
  OdDbOsnapOverrule* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbTransformOverrule
class NRXDBGATE_EXPORT NcDbTransformOverrule : public NcRxOverrule {
public:
	NCRX_DECLARE_MEMBERS(NcDbTransformOverrule);
	NcDbTransformOverrule();
	virtual Nano::ErrorStatus   transformBy(NcDbEntity* pSubject, const NcGeMatrix3d& xform);
	virtual Nano::ErrorStatus   getTransformedCopy(const NcDbEntity* pSubject, const NcGeMatrix3d& xform,
	                                                                NcDbEntity*& pEnt);
	virtual Nano::ErrorStatus   explode(const NcDbEntity* pSubject, NcDbVoidPtrArray& entitySet);
	virtual NRX::Boolean      cloneMeForDragging(NcDbEntity* pSubject);
	virtual bool                hideMeForDragging(const NcDbEntity* pSubject);
};

//////////////////////////////////////////////////////////////////////////
// NcDbGripOverrule
class NRXDBGATE_EXPORT NcDbGripOverrule : public NcRxOverrule {
public:
	NCRX_DECLARE_MEMBERS(NcDbGripOverrule);
	NcDbGripOverrule();
	virtual Nano::ErrorStatus   getGripPoints(const NcDbEntity* pSubject,
	                                                           NcGePoint3dArray&  gripPoints,
	                                                           NcDbIntArray &     osnapModes,
	                                                           NcDbIntArray &  geomIds);
	virtual Nano::ErrorStatus   moveGripPointsAt(NcDbEntity* pSubject,
	                                                              const NcDbIntArray & indices,
	                                                              const NcGeVector3d& offset);
	virtual Nano::ErrorStatus   getGripPoints(const NcDbEntity* pSubject,
	                                                           NcDbGripDataPtrArray& grips,
	                                                           const double curViewUnitSize,
	                                                           const int gripSize,
	                                                           const NcGeVector3d& curViewDir,
	                                                           const int bitflags);
	virtual Nano::ErrorStatus   moveGripPointsAt(NcDbEntity* pSubject,
	                                                              const NcDbVoidPtrArray& gripAppData,
	                                                              const NcGeVector3d& offset,
	                                                              const int bitflags);
	virtual Nano::ErrorStatus   getStretchPoints(const NcDbEntity* pSubject,
	                                                              NcGePoint3dArray& stretchPoints);
	virtual Nano::ErrorStatus   moveStretchPointsAt(NcDbEntity* pSubject,
	                                                                 const NcDbIntArray & indices,
	                                                                 const NcGeVector3d& offset);
	virtual void gripStatus(NcDbEntity* pSubject, const NcDb::GripStat status);
};

//////////////////////////////////////////////////////////////////////////
// NcDbSubentityOverrule
class NRXDBGATE_EXPORT NcDbSubentityOverrule : public NcRxOverrule {
public:
	NCRX_DECLARE_MEMBERS(NcDbSubentityOverrule);
	NcDbSubentityOverrule();
	virtual Nano::ErrorStatus addSubentPaths(NcDbEntity* pSubject, const NcDbFullSubentPathArray& newPaths);
	virtual Nano::ErrorStatus deleteSubentPaths(NcDbEntity* pSubject, const NcDbFullSubentPathArray& paths);
	virtual Nano::ErrorStatus transformSubentPathsBy(NcDbEntity* pSubject,
	                                                                  const NcDbFullSubentPathArray& paths,
	                                                                  const NcGeMatrix3d&            xform);
	virtual Nano::ErrorStatus getGripPointsAtSubentPath(
	                               const NcDbEntity*              pSubject,
	                               const NcDbFullSubentPath&      path,
	                               NcDbGripDataPtrArray&          grips,
	                               const double                   curViewUnitSize,
	                               const int                      gripSize,
	                               const NcGeVector3d&            curViewDir,
	                               const int                      bitflags);
	virtual Nano::ErrorStatus moveGripPointsAtSubentPaths(
	                                NcDbEntity*                    pSubject,
	                                const NcDbFullSubentPathArray& paths,
	                                const NcDbVoidPtrArray&        gripAppData,
	                                const NcGeVector3d&            offset,
	                                const int                      bitflags);
	virtual  Nano::ErrorStatus getSubentPathsAtGsMarker(
	                                const NcDbEntity*      pSubject,
	                                NcDb::SubentType       type,
	                                NRX::GsMarker        gsMark,
	                                const NcGePoint3d&     pickPoint,
	                                const NcGeMatrix3d&    viewXform,
	                                int&                   numPaths,
	                                NcDbFullSubentPath*&   subentPaths,
	                                int                    numInserts = 0,
	                                NcDbObjectId*          entAndInsertStack = NULL);
	virtual  Nano::ErrorStatus getGsMarkersAtSubentPath(
	                                const NcDbEntity*         pSubject,
	                                const NcDbFullSubentPath& subPath,
	                                NcArray<NRX::GsMarker>& gsMarkers);
	virtual NcDbEntity* subentPtr(const NcDbEntity* pSubject, const NcDbFullSubentPath& id);
	virtual void        subentGripStatus(
	                                    NcDbEntity*               pSubject,
	                                    const NcDb::GripStat      status,
	                                    const NcDbFullSubentPath& subentity);
	virtual Nano::ErrorStatus getCompoundObjectTransform(const NcDbEntity* pSubject, NcGeMatrix3d & xMat);
	virtual Nano::ErrorStatus getSubentPathGeomExtents(const NcDbEntity* pSubject,
	                                                                    const NcDbFullSubentPath& path,
	                                                                    NcDbExtents&              extents);
	virtual Nano::ErrorStatus getSubentClassId(const NcDbEntity* pSubject,
	                                                            const NcDbFullSubentPath& path,
	                                                            CLSID*                    clsId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbHighlightOverrule
class OdDbHighlightOverrule;
class NRXDBGATE_EXPORT NcDbHighlightOverrule : public NcRxOverrule
{
public:

	NCRX_DECLARE_MEMBERS(NcDbHighlightOverrule);

	typedef NcDbHighlightOverrule  wrapper_class;
	typedef OdDbHighlightOverrule  native_class;

public:
	NcDbHighlightOverrule();
	~NcDbHighlightOverrule();
	NcDbHighlightOverrule(OdRxObject* _object);

	virtual Nano::ErrorStatus highlight(
	                            const NcDbEntity*      pSubject,
	                            const NcDbFullSubentPath& subId = kNullSubent,
	                            const NRX::Boolean highlightAll = false);
	virtual Nano::ErrorStatus unhighlight(
	                            const NcDbEntity*      pSubject,
	                            const NcDbFullSubentPath& subId = kNullSubent,
	                            const NRX::Boolean highlightAll = false);

public:
	OdDbHighlightOverrule* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbHighlightStateOverrule
class NRXDBGATE_EXPORT NcDbHighlightStateOverrule : public NcRxOverrule {
public:
	NCRX_DECLARE_MEMBERS(NcDbHighlightStateOverrule);
	NcDbHighlightStateOverrule();
	virtual Nano::ErrorStatus  pushHighlight(
	                                NcDbEntity*               pSubject,
	                                const NcDbFullSubentPath& subId,
	                                NcGiHighlightStyle        highlightStyle);
	virtual Nano::ErrorStatus  popHighlight(
	                                NcDbEntity*               pSubject,
	                                const NcDbFullSubentPath& subId);
	virtual NcGiHighlightStyle highlightState(
	                                NcDbEntity*               pSubject,
	                                const NcDbFullSubentPath& subId);
};

//////////////////////////////////////////////////////////////////////////
// NcDbVisibilityOverrule
class NRXDBGATE_EXPORT NcDbVisibilityOverrule : public NcRxOverrule {
public:
	NCRX_DECLARE_MEMBERS(NcDbVisibilityOverrule);
	NcDbVisibilityOverrule();
	virtual NcDb::Visibility visibility(const NcDbEntity* pSubject);
	virtual Nano::ErrorStatus setVisibility(NcDbEntity* pSubject,
	                                                         NcDb::Visibility newVal,
	                                                         NRX::Boolean doSubents = true);
};

//////////////////////////////////////////////////////////////////////////
// NcDbGeometryOverrule
class OdDbGeometryOverrule;
class NRXDBGATE_EXPORT NcDbGeometryOverrule : public NcRxOverrule
{
public:
	NCRX_DECLARE_MEMBERS(NcDbGeometryOverrule);
  
  typedef NcDbGeometryOverrule  wrapper_class;
  typedef NcDbGeometryOverrule  native_class;

public:
  NcDbGeometryOverrule();
  ~NcDbGeometryOverrule();
  NcDbGeometryOverrule(OdRxObject* _object);

	virtual  Nano::ErrorStatus intersectWith(
	                                        const NcDbEntity* pSubject,
	                                        const NcDbEntity* pEnt,
	                                        NcDb::Intersect intType,
	                                        NcGePoint3dArray& points,
	                                        NRX::GsMarker thisGsMarker = 0,
	                                        NRX::GsMarker otherGsMarker = 0);
	virtual  Nano::ErrorStatus intersectWith(
	                                        const NcDbEntity* pSubject,
	                                        const NcDbEntity* pEnt,
	                                        NcDb::Intersect intType,
	                                        const NcGePlane& projPlane,
	                                        NcGePoint3dArray& points,
	                                        NRX::GsMarker thisGsMarker = 0,
	                                        NRX::GsMarker otherGsMarker = 0);
	virtual  Nano::ErrorStatus getGeomExtents(const NcDbEntity* pSubject, NcDbExtents& extents);

public:
  OdDbGeometryOverrule* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbObjectOverrule
class NRXDBGATE_EXPORT NcDbObjectOverrule : public NcRxOverrule {
public:
	NCRX_DECLARE_MEMBERS(NcDbObjectOverrule);
	NcDbObjectOverrule();
	virtual Nano::ErrorStatus open(NcDbObject* pSubject, NcDb::OpenMode mode);
	virtual Nano::ErrorStatus close(NcDbObject* pSubject);
	virtual Nano::ErrorStatus cancel(NcDbObject* pSubject);
	virtual Nano::ErrorStatus erase(NcDbObject* pSubject, NRX::Boolean erasing);
	virtual Nano::ErrorStatus deepClone(const NcDbObject* pSubject,
	                                                     NcDbObject* pOwnerObject,
	                                                     NcDbObject*& pClonedObject,
	                                                     NcDbIdMapping& idMap,
	                                                     NRX::Boolean isPrimary = true);
	virtual Nano::ErrorStatus wblockClone(const NcDbObject* pSubject,
	                                                       NcRxObject* pOwnerObject,
	                                                       NcDbObject*& pClonedObject,
	                                                       NcDbIdMapping& idMap,
	                                                       NRX::Boolean isPrimary = true);
};

//////////////////////////////////////////////////////////////////////////
// NcDbGraphNode
class OdDbGraphNode;
class NRXDBGATE_EXPORT NcDbGraphNode : public NcHeapOperators {
	friend class NcDbGraph;
public:
	NcDbGraphNode(void* pData = NULL);
	NcDbGraphNode(OdDbGraphNode* _object);

	virtual ~NcDbGraphNode();
	enum Flags    { kNone               = 0x00,
	                kVisited            = 0x01,
	                kOutsideRefed       = 0x02,
	                kSelected           = 0x04,
	                kInList             = 0x08,
	                kListAll            = 0x0E,
	                kFirstLevel         = 0x10,
	                kUnresTree          = 0x20,
	                kAll                = 0x2F };
	void*               data            () const;
	void                setData         (void*);
	int                 numOut          () const;
	int                 numIn           () const;
	NcDbGraphNode*      in              (int) const;
	NcDbGraphNode*      out             (int) const;
	Nano::ErrorStatus   addRefTo        (NcDbGraphNode*);
	Nano::ErrorStatus   removeRefTo     (NcDbGraphNode*);
	Nano::ErrorStatus   disconnectAll   ();
	NcDbGraph*          owner           () const;
	bool                isMarkedAs      (NRX::UInt8 flags) const;
	Nano::ErrorStatus   markAs          (NRX::UInt8 flags);
	Nano::ErrorStatus   clear           (NRX::UInt8 flags);
	Nano::ErrorStatus   markTree        (NRX::UInt8 flags,
	                                     NcDbVoidPtrArray* = NULL);
	int                 numCycleOut     () const;
	int                 numCycleIn      () const;
	NcDbGraphNode*      cycleIn         (int) const;
	NcDbGraphNode*      cycleOut        (int) const;
	NcDbGraphNode*      nextCycleNode   () const;
	bool                isCycleNode     () const;
	void                setEdgeGrowthRate(int outEdgeRate, int inEdgeRate);
private:
	NcDbGraphNode(const NcDbGraphNode&);
	NcDbGraphNode&      operator =      (const NcDbGraphNode&);
	NcDbVoidPtrArray    mOutgoing;
	NcDbVoidPtrArray    mIncoming;
	void*               mpData;
	void                setFirstLevel   (NRX::Boolean);
	NRX::UInt8        mFlags;
	Nano::ErrorStatus   setOwner        (NcDbGraph*);
	Nano::ErrorStatus   resetCycles     ();
	Nano::ErrorStatus   removeCycleRefTo (NcDbGraphNode*);
	Nano::ErrorStatus   clearCycles     ();
	NcDbGraph*          mpOwner;
	NcDbVoidPtrArray*   mpCycleOut;
	NcDbVoidPtrArray*   mpCycleIn;

public:
	OdDbGraphNode* native() const;

protected:
	OdDbGraphNode* m_pNative;
};

//////////////////////////////////////////////////////////////////////////
// NcDbGraph
class OdDbGraph;
class NRXDBGATE_EXPORT NcDbGraph : public NcHeapOperators {
	friend class NcDbGraphNode;
public:
	NcDbGraph(NcDbGraphNode* pRoot = NULL);
	NcDbGraph(OdDbGraph* _object);

	virtual ~NcDbGraph();
	NcDbGraphNode*      node            (int index) const;
	NcDbGraphNode*      rootNode        () const;
	int                 numNodes        () const;
	bool                isEmpty         () const;
	Nano::ErrorStatus   addNode         (NcDbGraphNode*);
	Nano::ErrorStatus   addEdge         (NcDbGraphNode* pFrom,
	                                     NcDbGraphNode* pTo);
	Nano::ErrorStatus   delNode         (NcDbGraphNode*);
	void                reset           ();
	void                clearAll        (NRX::UInt8 flags);
	void                getOutgoing     (NcDbVoidPtrArray&);
	virtual NRX::Boolean findCycles   (NcDbGraphNode* pStart = NULL);
	Nano::ErrorStatus   breakCycleEdge  (NcDbGraphNode* pFrom,
	                                     NcDbGraphNode* pTo);
	void                setNodeGrowthRate(int rate);
protected:
	Nano::ErrorStatus   clearAllCycles  ();
private:
	NcDbGraph(const NcDbGraph&);
	NcDbGraph&          operator =      (const NcDbGraph&);
	NcDbVoidPtrArray    mNodes;
	NcDbVoidPtrArray*   mpCycleNodes;
	void                setDirty        ();
	bool                mDirty;

public:
	OdDbGraph* native() const;

protected:
	OdDbGraph* m_pNative;
};

//////////////////////////////////////////////////////////////////////////
// NcDbGraphStack
class NRXDBGATE_EXPORT NcDbGraphStack : public NcHeapOperators {
public:
	NcDbGraphStack(int initPhysicalLength = 0, int initGrowLength = 8);
	~NcDbGraphStack();
	Nano::ErrorStatus   push            (NcDbGraphNode*);
	NcDbGraphNode*      pop             ();
	NcDbGraphNode*      top             () const;
	bool                isEmpty         () const;
private:
	NcDbVoidPtrArray    mStack;
};

class OdDbObjectIdGraphNode;

//////////////////////////////////////////////////////////////////////////
// NcDbObjectIdGraphNode
class NRXDBGATE_EXPORT NcDbObjectIdGraphNode : public NcDbGraphNode {
public:
	NcDbObjectIdGraphNode(const NcDbObjectId id);
	virtual ~NcDbObjectIdGraphNode();
	NcDbObjectId id() const;
private:
	NcDbObjectId mId;

public:
	OdDbObjectIdGraphNode* native() const;
};

class OdDbObjectIdGraph;

//////////////////////////////////////////////////////////////////////////
// NcDbObjectIdGraph
class NRXDBGATE_EXPORT NcDbObjectIdGraph : public NcDbGraph {
public:
	NcDbObjectIdGraph();
	NcDbObjectIdGraph(OdDbGraph* _object);
	virtual ~NcDbObjectIdGraph();
	Nano::ErrorStatus       addNode     (NcDbObjectIdGraphNode *);
	Nano::ErrorStatus       delNode     (NcDbObjectIdGraphNode *);
	NcDbObjectIdGraphNode*  findNode    (const NcDbObjectId) const;
	NcDbObjectIdGraphNode*  idNode      (int idx) const;
private:
	NcDbIdMapping       mIdNodeMap;
public:
	OdDbObjectIdGraph* native() const;
};

//////////////////////////////////////////////////////////////////////////
// NcDbXrefGraphNode
class NRXDBGATE_EXPORT NcDbXrefGraphNode : public NcDbGraphNode {
public:
	NcDbXrefGraphNode(const NCHAR * pName = NULL,
	                  const NcDbObjectId& btrId = NcDbObjectId::kNull,
	                  NcDbDatabase* pDb = NULL,
	                  NcDb::XrefStatus status = NcDb::kXrfResolved);
	virtual ~NcDbXrefGraphNode();
	const NCHAR * name() const;
	NcDbObjectId btrId() const;
	NcDbDatabase* database() const;
	Nano::ErrorStatus setName(const NCHAR * pName);
	void setBtrId(const NcDbObjectId& id);
	void setDatabase(NcDbDatabase* pDb);
	bool isNested() const;
	NcDb::XrefStatus xrefStatus() const;
	void setXrefStatus(NcDb::XrefStatus stat);
	NcDb::XrefNotificationStatus xrefNotificationStatus() const;
	void setXrefNotificationStatus(NcDb::XrefNotificationStatus stat);
	void*   xData() { return mpxdata; }
	void    setxData(void *pXData) { mpxdata = pXData; }
	Nano::ErrorStatus xrefReadSubstatus() const;
private:
	void* mpxdata;
	NCHAR * mpName;
	NcDbObjectId mBtrId;
	NcDb::XrefStatus mStatus;
	NcDb::XrefNotificationStatus mNotifyStatus;
};

//////////////////////////////////////////////////////////////////////////
// NcDbXrefGraph
class NRXDBGATE_EXPORT NcDbXrefGraph : public NcDbGraph {
public:
	NcDbXrefGraph(NcDbXrefGraphNode* pHostDwg = NULL);
	virtual ~NcDbXrefGraph();
	NcDbXrefGraphNode* xrefNode(const NCHAR * pName) const;
	NcDbXrefGraphNode* xrefNode(NcDbObjectId btrId) const;
	NcDbXrefGraphNode* xrefNode(const NcDbDatabase* pDb) const;
	NcDbXrefGraphNode* xrefNode(int idx) const;
	NcDbXrefGraphNode*  hostDwg() const;
	NRX::Boolean markUnresolvedTrees ();
	virtual NRX::Boolean findCycles(NcDbGraphNode* pStart = NULL);
};

Nano::ErrorStatus
ncdbGetHostDwgXrefGraph(NcDbDatabase* pHostDb, NcDbXrefGraph& graph,
                        NRX::Boolean includeGhosts = NRX::kFalse);

NRXDBGATE_EXPORT bool ncdbAddAnnotationScaleReactor(NcDbAnnotationScaleReactor *pReactor);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbAddConstrainedGeometryDraggingInfo(
                const NcConstrainedGeometryDraggingInfo* pDraggingInfo);
NRXDBGATE_EXPORT Nano::ErrorStatus   ncdbAddFieldReactor     (NcFdFieldReactor* pReactor);
const NRXDBGATE_EXPORT NcString& ncdbAnnotationScaleCollectionName();

Nano::ErrorStatus ncdbAttachXref(NcDbDatabase* pHostDb,
                                 const NCHAR * pFilename,
                                 const NCHAR * pBlockName,
                                 NcDbObjectId& xrefBlkId);

Nano::ErrorStatus ncdbBindXrefs(NcDbDatabase*      pHostDb,
                                const NcDbObjectIdArray& xrefBlkIds,
                                const bool               bInsertBind,
                                const bool               bAllowUnresolved = false,
                                const bool               bQuiet = true);

Nano::ErrorStatus ncdbCleanUp();
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbConvertFieldsToText(NcDbDatabase* pDb,
                                                           const NcStringArray* pEvalIds,
                                                           NcFd::ConvertFieldToText nOption);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbConvertFieldsToText(const NcDbObjectIdArray& objIds,
                                                           const NcStringArray* pEvalIds,
                                                           NcFd::ConvertFieldToText nOption);
NRXDBGATE_EXPORT void
ncdbConvertHslToRgb(
           const NcGeVector3d& hsl,
           NcGeVector3d& rgb);
NRXDBGATE_EXPORT void
ncdbConvertRgbToHsl(
           const NcGeVector3d& rgb,
           NcGeVector3d& hsl
           );

Nano::ErrorStatus ncdbCopyLayout (const NCHAR* copyname,
                                  const NCHAR* newname,
                                  NcDbDatabase* pDb = NULL);

Nano::ErrorStatus
ncdbCreateViewByViewport( NcDbDatabase *pDb,
                         NcDbObjectId viewportId,
                         const NCHAR* name,
                         const NCHAR* categoryName,
                         NcDbObjectId labelBlockId,
                         NcDbObjectId& view);

NRXDBGATE_EXPORT NcDbCustomOsnapManager* ncdbCustomOsnapManager();

Nano::ErrorStatus ncdbDeleteLayout (const NCHAR* delname, NcDbDatabase* pDb = NULL);

Nano::ErrorStatus ncdbDetachXref(NcDbDatabase* pHostDb,
                                 const NcDbObjectId& xrefBlkId);
bool CS_STDCALL ncdbDwkFileExists(const NCHAR *pszFileName);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbEvaluateFields(const NcDbObjectId& objId,
                                                      int nContext,
                                                      const NCHAR* pszPropName = NULL,
                                                      NcDbDatabase* pDb        = NULL,
                                                      NcFd::EvalFields nEvalFlag = NcFd::kEvalRecursive,
                                                      int* pNumFound           = NULL,
                                                      int* pNumEvaluated       = NULL);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbEvaluateFields(const NcDbObjectId& objId,
                                                      int nContext,
                                                      const NcDbObjectIdArray* pFieldsToEvaluate,
                                                      const NCHAR* pszEvaluatorId,
                                                      NcDbDatabase* pDb,
                                                      NcFd::EvalFields nEvalFlag,
                                                      int* pNumFound,
                                                      int* pNumEvaluated);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbEvaluateFields(const NcDbObjectIdArray& objIds,
                                                      int nContext,
                                                      const NcDbObjectIdArray* pFieldsToEvaluate,
                                                      const NCHAR* pszEvaluatorId,
                                                      NcDbDatabase* pDb,
                                                      NcFd::EvalFields nEvalFlag,
                                                      int* pNumFound,
                                                      int* pNumEvaluated);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbEvaluateFields(const NcDbObjectIdArray& objIds,
                                                      int nContext,
                                                      const NCHAR* pszPropName  = NULL,
                                                      NcDbDatabase* pDb         = NULL,
                                                      NcFd::EvalFields nEvalFlag = NcFd::kEvalRecursive,
                                                      int* pNumFound            = NULL,
                                                      int* pNumEvaluated        = NULL);
NRXDBGATE_EXPORT bool      ncdbFindField           (const NCHAR * pszText,
                                                    int iSearchFrom,
                                                    int& nStartPos,
                                                    int& nEndPos);

Nano::ErrorStatus ncdbForceTextAdjust(const NcDbObjectIdArray& objIds);
bool
ncdbGetArcLengthSymbolPlacement(NcDbObject *pObj,
                                int& nValue);

Nano::ErrorStatus ncdbGetBreakSubentIndex(NcDbEntity* pEnt,
                                          const NcGePoint3d& pickPt,
                                          const NcGeVector3d& viewDir,
                                          int& subentIndex,
                                          NcGePoint3d& ptOnEnt,
                                          const NcGeTol& tol = NcGeContext::gTol);
NRXDBGATE_EXPORT NcDbUnderlayHost*
ncdbGetCurrentDgnDocHost();
NRXDBGATE_EXPORT NcDbUnderlayHost*
ncdbGetCurrentDgnHost();
NRXDBGATE_EXPORT NcDbUnderlayHost*
ncdbGetCurrentDwfHost();
NRXDBGATE_EXPORT NcDbUnderlayHost*
ncdbGetCurrentPdfHost();

Nano::ErrorStatus ncdbGetCurUserViewportId(NcDbDatabase* pDb,  NcDbObjectId& vpId);

NcDbObjectId      ncdbGetCurVportId(NcDbDatabase* pDb);

NcDbObjectId      ncdbGetCurVportTableRecordId(NcDbDatabase* pDb);

Nano::ErrorStatus ncdbGetDgnFileReferences(const NCHAR* fileName, const NCHAR* pwd,
                                           NcDbRefFileDataPtrArray& files);
bool ncdbGetDimAngExtOn(NcDbObject *pObj,
                        int& dimExtFlag);
bool ncdbGetDimBreakSize(NcDbObject *pObj,
                         double& dimBreakSize);
bool ncdbGetDimExt1Linetype(NcDbObject *pObj,
                            NcDbObjectId& oidValue);
bool ncdbGetDimExt2Linetype(NcDbObject *pObj,
                            NcDbObjectId& oidValue);
bool ncdbGetDimExtensionLength(NcDbObject *pObj,
                               double& fValue);
bool ncdbGetDimFlipArrow(NcDbObject *pObj,
                         int& nValue);
bool ncdbGetDimFlipArrowWhich(NcDbObject *pObj,
                              int& nValue);
bool ncdbGetDimJogSymbolPosition(NcDbObject *pObj,
                                 int& dimJagFlag,
                                 NcGePoint3d& pos);

bool ncdbGetDimJogSymbolSize(NcDbObject *pObj,
                             int& dimJagFlag,
                             double& dimJagSize);

bool ncdbGetDimLineLinetype(NcDbObject *pObj,
                            NcDbObjectId& oidValue);

bool ncdbGetDimTextBackground(NcDbObject *pObj,
                              int& bgFlag,
                              NcCmColor& bgColor);

bool ncdbGetDimTextDirection(NcDbObject *pObj,
                             int& nValue);
bool ncdbGetDimTolAlign(NcDbObject *pObj,
                        int& dimTolAlignFlag);
bool ncdbGetExemptCheckFlag(NcDbObject *pObj, int& bitFlags);
NRXDBGATE_EXPORT NcFdFieldEngine* ncdbGetFieldEngine(void);
NRXDBGATE_EXPORT bool ncdbGetFieldMarkers(const NCHAR*& pszPrefix, const NCHAR*& pszSuffix);
bool ncdbGetFixedLengthExtLineEnabled(NcDbObject *pObj, int& nValue);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbGetGeoDataObjId(NcDbDatabase *pDb, NcDbObjectId& objId);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbGetGeoDataTransform(NcDbDatabase*   pDbSource,
                                                           NcDbDatabase*   pDbTarget,
                                                           NcGePoint3d&    insertionPt,
                                                           double&         rotation,
                                                           double&         scale);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbGetHomeView(NcDbDatabase *        pDb,
                                                   NcDbHomeView&         hmView);
bool ncdbGetLargeRadDimJogAngle(NcDbObject *pObj,
                                double& fJogAngle);
NRXDBGATE_EXPORT const NCHAR* ncdbGetMappedFontName(const NCHAR *fontName);

Nano::ErrorStatus NRXDBGATE_EXPORT ncdbGetMotionPathDictionary   (NcDbDatabase* pDb, NcDbDictionary*& pDict,
                                                                  NcDb::OpenMode mode, bool createIfNonExist);
Nano::ErrorStatus NRXDBGATE_EXPORT ncdbGetMotionPathDictionary   (NcDbDatabase* pDb, NcDbDictionary*& pDict,
                                                                  NcDb::OpenMode mode);
Nano::ErrorStatus NRXDBGATE_EXPORT ncdbGetNamedPathDictionary   (NcDbDatabase* pDb, NcDbDictionary*& pDict,
                                                                 NcDb::OpenMode mode, bool createIfNonExist);
Nano::ErrorStatus NRXDBGATE_EXPORT ncdbGetNamedPathDictionary   (NcDbDatabase* pDb, NcDbDictionary*& pDict,
                                                                 NcDb::OpenMode mode);
NRXDBGATE_EXPORT  Nano::ErrorStatus ncdbGetObjectMesh(NcDbObject *pObj,
                                                      const NcDbFaceterSettings *faceter,
                                                      NcGePoint3dArray& vertexArray,
                                                      NcArray<NRX::Int32>& faceArray,
                                                      NcGiFaceData*& faceData);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbGetProxyInfo(NcDbObject *pObj, NCHAR*& dxfName,
                                                    NCHAR*& className, NCHAR*& appName);

bool ncdbGetRadialExtensionAngles(NcDbObject *pObj,
                                  int& dimExtFlag,
                                  double& dimExtAng1,
                                  double& dimExtAng2);

NRXDBGATE_EXPORT Nano::ErrorStatus
ncdbGetShowCompass(NcDbDatabase *         pDb,
                   bool &                 bShow);

NRXDBGATE_EXPORT Nano::ErrorStatus CS_STDCALL ncdbGetSummaryInfo(NcDbDatabase* pDb,
                                                                 NcDbDatabaseSummaryInfo*& pInfo);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbGetThumbnailBitmapFromDxfFile(const NCHAR* filename, void*& pBitmap);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbGetUnitsConversion (NcDb::UnitsValue from,
                                                           NcDb::UnitsValue to,
                                                           double& conversionFactor);

NRXDBGATE_EXPORT NcDbObjectId ncdbGetViewportVisualStyle();

NRXDBGATE_EXPORT NcDb::DwgDataType ncdbGroupCodeToType(NcDb::DxfCode pCode);
NRXDBGATE_EXPORT bool      ncdbHasFields           (const NCHAR * pszText);
NRXDBGATE_EXPORT int ncdbHostAppMinorVersion();
NRXDBGATE_EXPORT bool ncdbIsDgnToDwgInProgress();
NRXDBGATE_EXPORT bool ncdbIsInLongTransaction(NcDbObjectId id);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbLoadMlineStyleFile(const NCHAR *sname, const NCHAR *fname);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbMakeFieldCode(const NCHAR * pszFieldExpr,
                                                     NCHAR*& pszFieldCode);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbMakeFieldCode(const NCHAR* pszFieldExpr,
                                                     NCHAR*& pszFieldCode,
                                                     const NCHAR* pszEvalId,
                                                     const NCHAR* pszFormat,
                                                     const NcHyperlink* pHyperlink);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleGetOriginalSelectedFontName(const NcDbOle2Frame* pOleEnt,
                                                                      NCHAR*& fontName);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleGetOriginalSelectedFontPointSize(const NcDbOle2Frame* pOleEnt,
                                                                           int& pointSize);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleGetOriginalSelectedTextSizeInNcadUnits(const NcDbOle2Frame* pOleEnt,
                                                                                 double& sizeInNcadUnits);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleGetOriginalWidthHeight(const NcDbOle2Frame* pOleEnt,
                                                                 double& width,
                                                                 double& height);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleGetRotationMatrix(const NcDbOle2Frame* pOleEnt,
                                                            NcGeMatrix3d& rotMat);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleGetSelectedFontName(const NcDbOle2Frame* pOleEnt,
                                                              NCHAR*& fontName);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleGetSelectedFontPointSize(const NcDbOle2Frame* pOleEnt,
                                                                   int& pointSize);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleGetSelectedTextSizeInNcadUnits(const NcDbOle2Frame* pOleEnt,
                                                                         double& sizeInNcadUnits);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleHitTest(const NcDbOle2Frame* pOleEnt,
                                                  const NcGePoint3d&  wvpt,
                                                  const NcGeVector3d& wvwdir);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleSetOriginalSelectedFontName(const NcDbOle2Frame* pOleEnt,
                                                                      const NCHAR* fontName);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleSetOriginalSelectedFontPointSize(const NcDbOle2Frame* pOleEnt,
                                                                           const int pointSize);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleSetOriginalSelectedTextSizeInNcadUnits(const NcDbOle2Frame* pOleEnt,
                                                                                 const double sizeInNcadUnits);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleSetOriginalWidthHeight(const NcDbOle2Frame* pOleEnt,
                                                                 const double width,
                                                                 const double height);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleSetSelectedFontName(const NcDbOle2Frame* pOleEnt,
                                                              const NCHAR* fontName);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleSetSelectedFontPointSize(const NcDbOle2Frame* pOleEnt,
                                                                   const int pointSize);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOleSetSelectedTextSizeInNcadUnits(const NcDbOle2Frame* pOleEnt,
                                                                         const double sizeInNcadUnits);

NRXDBGATE_EXPORT const NCHAR* ncdbOriginalXrefFullPathFor(const NcDbDatabase*);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbOverlayXref(NcDbDatabase* pHostDb,
                                                   const NCHAR * pFilename,
                                                   const NCHAR * pBlockName,
                                                   NcDbObjectId& xrefBlkId);
NRXDBGATE_EXPORT bool ncdbPSLayoutAnnoAllVisible(NcDbObjectId viewportEntityId);
NRXDBGATE_EXPORT bool ncdbPSLayoutAnnoAllVisible(NcDbViewport* pVport);

NRXDBGATE_EXPORT Nano::ErrorStatus CS_STDCALL ncdbPutSummaryInfo(const NcDbDatabaseSummaryInfo* pInfo,
                                                                 NcDbDatabase *pDb);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbPutSummaryInfo(const NcDbDatabaseSummaryInfo* pInfo);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbQueueAnnotationEntitiesForRegen(NcDbDatabase* pDb);
NRXDBGATE_EXPORT int CS_STDCALL ncdbQueueForRegen(const NcDbObjectId *pIdArray, int nNumIds);

#ifdef MEM_DEBUG
	void*             ncdbAlloc_dbg(size_t NCDBG_FORMAL);
	void*             ncdbRealloc_dbg(void *, size_t NCDBG_FORMAL);
#endif
NRXDBGATE_EXPORT void ncdbReleaseHostDwg(NcDbDatabase* pHostDb);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbReloadXrefs(NcDbDatabase* pHostDb,
                                                   const NcDbObjectIdArray& xrefBlkIds,
                                                   bool  bQuiet = true);
NRXDBGATE_EXPORT bool ncdbRemoveAnnotationScaleReactor(NcDbAnnotationScaleReactor *pReactor);
NRXDBGATE_EXPORT Nano::ErrorStatus   ncdbRemoveFieldReactor  (NcFdFieldReactor* pReactor);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbRenameLayout (const NCHAR* oldname,
                                                     const NCHAR* newname,
                                                     NcDbDatabase* pDb = NULL);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbResolveCurrentXRefs(NcDbDatabase* pHostDb,
                                                           bool useThreadEngine = true, bool doNewOnly = false);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbResurrectMeNow(const NcDbObjectId& id);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSendInitialDwgFileOpenComplete(NcDbDatabase* pDb);

NRXDBGATE_EXPORT NcDbServices* ncdbServices();
NRXDBGATE_EXPORT bool ncdbSetArcLengthSymbolPlacement(NcDbObject *pObj,
                                                      int nValue,
                                                      bool autoClearOverride = true);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSetBreak3dQueueForRegen(bool);
NRXDBGATE_EXPORT NcDbUnderlayHost* ncdbSetCurrentDgnDocHost(NcDbUnderlayHost* pHost);
NRXDBGATE_EXPORT NcDbUnderlayHost* ncdbSetCurrentDgnHost(NcDbUnderlayHost* pHost);
NRXDBGATE_EXPORT NcDbUnderlayHost* ncdbSetCurrentDwfHost(NcDbUnderlayHost* pHost);
NRXDBGATE_EXPORT NcDbUnderlayHost* ncdbSetCurrentPdfHost(NcDbUnderlayHost* pHost);

NRXDBGATE_EXPORT NcGiContext * ncdbSetDefaultNcGiContext(NcGiContext *);
NRXDBGATE_EXPORT bool ncdbSetDimAngExtOn(NcDbObject *pObj, int dimExtFlag);
NRXDBGATE_EXPORT bool ncdbSetDimBreakSize(NcDbObject *pObj,
                                          double dimBreakSize,
                                          bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimExt1Linetype(NcDbObject *pObj,
                                             NcDbObjectId oidValue,
                                             bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimExt2Linetype(NcDbObject *pObj,
                                             NcDbObjectId oidValue,
                                             bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimExtensionLength(NcDbObject *pObj,
                                                double fValue,
                                                bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimFlipArrow(NcDbObject *pObj,
                                          int nValue,
                                          bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimFlipArrowWhich(NcDbObject *pObj,
                                               int nValue,
                                               bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimJogSymbolPosition(NcDbObject *pObj,
                                                  int& dimJagFlag,
                                                  const NcGePoint3d& pos,
                                                  bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimJogSymbolSize(NcDbObject *pObj,
                                              int dimJagFlag,
                                              const double dimJagSize,
                                              bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimLineLinetype(NcDbObject *pObj,
                                             NcDbObjectId oidValue,
                                             bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimTextBackground(NcDbObject *pObj,
                                               int bgFlag,
                                               NcCmColor* pBgColor,
                                               bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimTextDirection(NcDbObject *pObj,
                                              int nValue,
                                              bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetDimTolAlign(NcDbObject *pObj,
                                         int dimTolAlignFlag,
                                         bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetExemptCheckFlag(NcDbObject *pObj, int bitFlags);
NRXDBGATE_EXPORT bool ncdbSetFixedLengthExtLineEnabled(NcDbObject *pObj,
                                                       int nValue,
                                                       bool autoClearOverride=true);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSetHomeView(NcDbDatabase *pDb, const NcDbHomeView&   hmView);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSetHostApplicationServices(NcDbHostApplicationServices * pServices);
NRXDBGATE_EXPORT bool ncdbSetLargeRadDimJogAngle(NcDbObject *pObj,
                                                 double fJogAngle,
                                                 bool autoClearOverride = true);
NRXDBGATE_EXPORT bool ncdbSetRadialExtensionAngles(NcDbObject *pObj,
                                                   int dimExtFlag,
                                                   double dimExtAng1,
                                                   double dimExtAng2);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSetReferenced(NcDbObjectId objId);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSetShowCompass(NcDbDatabase *pDb, bool bShow);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbSetViewportVisualStyle(NcDbObjectId visualStyleId);

NRXDBGATE_EXPORT NcDbSummaryInfoManager* CS_STDCALL ncdbSummaryInfoManager();

#define NC_SRCH_BLOCK         0x01
#define NC_SRCH_DIM_TEXT      0x02
#define NC_SRCH_TEXT          0x04
#define NC_SRCH_LINK_DESC     0x08
#define NC_SRCH_LINK_URL      0x10
#define NC_SRCH_MATCH_CASE    0x20
#define NC_SRCH_WHOLE_WORD    0x40
#define NC_SRCH_DEFAULT       0x1F

bool ncdbTextFind(NcDbDatabase* pDatabase,
                  NcDbObjectIdArray& resultSet,
                  const NCHAR* findString,
                  const NCHAR* replaceString = NULL,
                  NRX::UInt8 searchOptions = NC_SRCH_DEFAULT,
                  const NcDbObjectIdArray& selSet = 0);

NRXDBGATE_EXPORT void ncdbTriggerNcadOctTreeReclassification();

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbUnloadXrefs(NcDbDatabase*      pHostDb,
                                                   const NcDbObjectIdArray& xrefBlkIds,
                                                   const bool               bQuiet = true);

NRXDBGATE_EXPORT Nano::ErrorStatus CS_STDCALL ncdbValidateCustomSummaryInfoKey(const TCHAR* key, const NcDbDatabaseSummaryInfo* pInfo = NULL);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbValidateDbConsistency(NcDbObject*     pHostObject,
                                                             NcDbObjectId    objId,
                                                             Nano::ErrorStatus   es = Nano::eOk);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbValidateDbConsistency(NcDbObject*     pHostObject,
                                                             NcDbDatabase*   pDatabase,
                                                             Nano::ErrorStatus   es = Nano::eOk);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbValidateSetup(NRX::Int32 lcid);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbValKey(const nds_name lname);

NRXDBGATE_EXPORT Nano::ErrorStatus ncdbXBindXrefs(NcDbDatabase*     pHostDb,
                                                  const NcDbObjectIdArray xrefSymbolIds,
                                                  const bool              bInsertBind,
                                                  const bool              bQuiet = true);

/////////////////////////////////////////////////////////////////////////
// Point Cloud

class NcPointCloudViewFrustum;

//////////////////////////////////////////////////////////////////////////
// NcViewFrustum
class NRXDBGATE_EXPORT NcViewFrustum {
public:
	NcViewFrustum();
	~NcViewFrustum();
	void setNearUpperRight(double x, double y, double z);
	void setNearUpperLeft(double x, double y, double z);
	void setNearLowerLeft(double x, double y, double z);
	void setNearLowerRight(double x, double y, double z);
	void setFarUpperRight(double x, double y, double z);
	void setFarUpperLeft(double x, double y, double z);
	void setFarLowerLeft(double x, double y, double z);
	void setFarLowerRight(double x, double y, double z);
	void nearUpperRight(double& x, double& y, double& z) const;
	void nearUpperLeft(double& x, double& y, double& z) const;
	void nearLowerLeft(double& x, double& y, double& z) const;
	void nearLowerRight(double& x, double& y, double& z) const;
	void farUpperRight(double& x, double& y, double& z) const;
	void farUpperLeft(double& x, double& y, double& z) const;
	void farLowerLeft(double& x, double& y, double& z) const;
	void farLowerRight(double& x, double& y, double& z) const;
	void setNearClip(bool clip);
	bool nearClip() const;
	void setFarClip(bool clip);
	bool farClip() const;
	NcPointCloudViewFrustum* asPointCloudFrustum() const;
private:
	void* m_pData;
};

//////////////////////////////////////////////////////////////////////////
// NcPcPointFloat
class NRXDBGATE_EXPORT NcPcPointFloat {
public:
	float m_x, m_y, m_z;
	DWORD m_argb;
};

//////////////////////////////////////////////////////////////////////////
// NcPcPointDouble
class NRXDBGATE_EXPORT NcPcPointDouble {
public:
	double m_x, m_y, m_z;
	DWORD m_argb;
};

//////////////////////////////////////////////////////////////////////////
// INcPcDataBuffer
class NRXDBGATE_EXPORT INcPcDataBuffer {
public:
	virtual ~INcPcDataBuffer()              = 0 {};
	virtual bool nativeDbl()                = 0;
	virtual bool resize(DWORD size)         = 0;
	virtual bool shrink(DWORD size)         = 0;
	virtual DWORD size() const              = 0;
	virtual NcPcPointFloat*  floatPoints () = 0;
	virtual NcPcPointDouble* doublePoints() = 0;
	virtual bool floatPoint  (DWORD ptIx, NcPcPointFloat&  pt) const    = 0;
	virtual bool doublePoint (DWORD ptIx, NcPcPointDouble& pt) const    = 0;
	virtual bool setFloatPoint  (DWORD ptIx, NcPcPointFloat&  pt)       = 0;
	virtual bool setDoublePoint (DWORD ptIx, NcPcPointDouble& pt)       = 0;
	virtual bool offset   (double& x, double& y, double& z) const       = 0;
	virtual bool entityTransform(NcGeMatrix3d& matrix) const            = 0;
	virtual void copyFrom(INcPcDataBuffer const & from)                 = 0;
};

//////////////////////////////////////////////////////////////////////////
// INcPcIndexProgress
class NRXDBGATE_EXPORT INcPcIndexProgress {
public:
	virtual void finished(float progress, Nano::ErrorStatus nResult) = 0;
};

//////////////////////////////////////////////////////////////////////////
// INcPcPointFilter
class NRXDBGATE_EXPORT INcPcPointFilter {
public:
	virtual void doFilter(
	    const INcPcDataBuffer& inBuffer,
	    INcPcDataBuffer&       outBuffer) = 0;
};

//////////////////////////////////////////////////////////////////////////
// INcPcPointProcessor
class NRXDBGATE_EXPORT INcPcPointProcessor {
public:
	virtual bool cancel()   = 0;
	virtual void abort()    = 0;
	virtual void finished() = 0;
	virtual bool processPoints() = 0;
	virtual INcPcPointFilter*  filter() = 0;
	INcPcDataBuffer* buffer();
	void setBuffer(INcPcDataBuffer* buffer);
private:
	INcPcDataBuffer* mpBuffer;
};
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbCreatePointCloudEntity(
NcDbEntity*& newPointCloud,
    const NcString& indexFile,
    const NcString& sourceFile,
    NcGePoint3d&    location,
    double          scale = 1.0,
    double          rotation = 0.0);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbModifyPointCloudDataView(
    NcDbEntity* pEnt,
    INcPcPointFilter* pFilter
    );
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbProcessPointCloudData(
    NcDbEntity* pEnt,
    const NcDbExtents& ext,
    int levelOfDetail,
    INcPcPointProcessor* pCallback);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbProcessPointCloudData(
    NcDbEntity* pEnt,
    const NcViewFrustum& frustum,
    int levelOfDetail,
    INcPcPointProcessor* pCallback);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbResetPointCloudDataView(
    NcDbEntity* pEnt
    );
NRXDBGATE_EXPORT Nano::ErrorStatus ncpcIndexPointCloud(
    const NcString& inputFile,
    const NcString& outputFile,
    INcPcIndexProgress* pCallback);

NRXDBGATE_EXPORT BOOL NcFdExtractData(NcDbField* pField,
                                      NCHAR *& pszSheetSetFile,
                                      NCHAR *& pszSheetSetId,
                                      NCHAR *& pszCompName,
                                      NCHAR *& pszCompId,
                                      NCHAR *& pszPropName);
NRXDBGATE_EXPORT BOOL NcFdExtractData(NcDbField* pField,
                                      NcDbObjectId& objId,
                                      NCHAR*& pszPropName);
NRXDBGATE_EXPORT BOOL NcFdMakeFieldCode(const NcDbObjectId& objId,
                                        NcDbEvalNodeId blockParamId,
                                        const NCHAR * pszPropOrConnectionName,
                                        NcFdEval::ObjectFieldOption nOption,
                                        const NCHAR * pszFormat,
                                        NcHyperlink* pHyperlink,
                                        NCHAR*& pszFieldCode);
NRXDBGATE_EXPORT BOOL NcFdMakeFieldCode(const NcDbObjectId& tableId,
                                        const NcDbObjectId& targetTableId,
                                        NcFdEval::ExpressionFieldOption nOption,
                                        const NcCellRangeArray& cellRanges,
                                        const NCHAR* pszFormat,
                                        NcHyperlink* pHyperlink,
                                        NCHAR*& pszFieldCode);
NRXDBGATE_EXPORT BOOL NcFdMakeFieldCode(INcSmDatabase* pSmDb,
                                        INcSmSheetSet* pSmSheetSet,
                                        INcSmComponent* pSmComp,
                                        const NCHAR* pszCompName,
                                        const NCHAR* pszPropName,
                                        NcFdEval::SheetSetFieldOption nOption,
                                        const NCHAR* pszFormat,
                                        NCHAR*& pszFieldCode);

namespace NcDmUtil
{
	int dimatfit(int dimfit);
	int dimfit  (int dimatfit, int dimtmove);
	int dimfrac (int dimunit);
	int dimlunit(int dimunit);
	int dimtmove(int dimfit);
	int dimunit (int dimlunit, int dimfrac );
	const NCHAR* globalArrowName(const NCHAR* pName);
	const NCHAR* globalArrowName(NcDbObjectId blockId);
	const NCHAR* arrowName(const NCHAR* pName);
	const NCHAR* arrowName(NcDbObjectId blockId);
	bool isBuiltInArrow(const NCHAR* pName);
	bool isZeroLengthArrow(const NCHAR* pName);
	Nano::ErrorStatus findArrowId(const NCHAR* pName,
	                              NcDbObjectId& blockId,
	                              NcDbDatabase* pDb = 0);
	Nano::ErrorStatus getArrowId(const NCHAR* pName,
	                             NcDbObjectId& blockId,
	                             NcDbDatabase* pDb = 0);
};

namespace NcDbIndexFilterManager
{
	Nano::ErrorStatus updateIndexes(NcDbDatabase* pDb);

	Nano::ErrorStatus addIndex (NcDbBlockTableRecord* pBTR,
	                            NcDbIndex* pIndex);

	Nano::ErrorStatus removeIndex (NcDbBlockTableRecord* pBTR,
	                               const NcRxClass* key);

	Nano::ErrorStatus getIndex(const NcDbBlockTableRecord* pBTR,
	                           const NcRxClass* key,
	                           NcDb::OpenMode readOrWrite,
	                           NcDbIndex*& pIndex);

	Nano::ErrorStatus getIndex(const NcDbBlockTableRecord* pBTR,
	                           int index,
	                           NcDb::OpenMode readOrWrite,
	                           NcDbIndex*& pIndex);

	int numIndexes(const NcDbBlockTableRecord* pBtr);


	Nano::ErrorStatus addFilter(NcDbBlockReference* pBlkRef,
	                            NcDbFilter* pFilter);

	Nano::ErrorStatus removeFilter(NcDbBlockReference* pBlkRef,
	                               const NcRxClass*    key);

	Nano::ErrorStatus getFilter(const NcDbBlockReference* pRef,
	                            const NcRxClass*          key,
	                            NcDb::OpenMode readOrWrite,
	                            NcDbFilter*&   pFilter);

	Nano::ErrorStatus getFilter(const NcDbBlockReference* pRef,
	                            int index,
	                            NcDb::OpenMode readOrWrite,
	                            NcDbFilter*& pFilter);

	int numFilters(const NcDbBlockReference* pBlkRef);
};

namespace NcDbDictUtil
{
	NRXDBGATE_EXPORT Nano::ErrorStatus dictionaryGetAt(NcDbObjectId& id, const NCHAR* name, NcDbObjectId ownerDictId);
	NRXDBGATE_EXPORT Nano::ErrorStatus dictionaryNameAt(NcString& name, NcDbObjectId itemId, NcDbObjectId ownerDictId);
	NRXDBGATE_EXPORT Nano::ErrorStatus dictionaryNameAt(NCHAR*& pName, NcDbObjectId itemId, NcDbObjectId ownerDictId);
	NRXDBGATE_EXPORT Nano::ErrorStatus dictionaryNameAt(NCHAR*& pName, NcDbObjectId itemId);
	NRXDBGATE_EXPORT Nano::ErrorStatus dictionaryNameAt(NcString& name, NcDbObjectId itemId);
} // namespace NcDbDictUtil

NRXDBGATE_EXPORT void ncdbAcisSetDeleteBulletins(NRX::Boolean onOff);
NRXDBGATE_EXPORT void ncdbAcisDeleteModelerBulletins(void);
NRXDBGATE_EXPORT NRX::Boolean ncdbAcisGetDeleteBulletins();
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbAcisRestoreEntityFromDwgFiler(NcDbDwgFiler* filer, ENTITY*& ent);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbAcisRestoreEntityFromDxfFiler(NcDbDxfFiler* filer, ENTITY*& ent);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbAcisSaveEntityToDwgFiler     (NcDbDwgFiler* filer, ENTITY* ent);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbAcisSaveEntityToDwgFiler2    (NcDbDwgFiler* filer, ENTITY* ent, NcDbDatabase* pDb);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbAcisSaveEntityToDxfFiler     (NcDbDxfFiler* filer, ENTITY* ent);
NRXDBGATE_EXPORT Nano::ErrorStatus ncdbAcisSaveEntityToDxfFiler2    (NcDbDxfFiler* filer, ENTITY* ent, NcDbDatabase* pDb);
NRXDBGATE_EXPORT NRX::Boolean ncdbIsModelerStarted();
NRXDBGATE_EXPORT void ncdbModelerEnd();
NRXDBGATE_EXPORT void ncdbModelerStart();
NRXDBGATE_EXPORT NRX::Boolean ncdbSetAcisDwgVer(int version);

NRXDBGATE_EXPORT Nano::ErrorStatus ncedGetCurDwgXrefGraph(NcDbXrefGraph&, NRX::Boolean includeGhosts = NRX::kFalse);
NRXDBGATE_EXPORT Nano::ErrorStatus getTableStyleNameFromDbById(const NcDbObjectId& objId, NCHAR*& pName);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NcDbMultiModesGripPE

class NRXDBGATE_EXPORT NcDbMultiModesGripPE  :  public NcRxObject
{
public:
	NCRX_DECLARE_MEMBERS(NcDbMultiModesGripPE);

	enum GripType 
	{ 
		kPrimary,
		kSecondary 
	};

	enum GripModeIdentifier
	{
		kNone = 0,
		kMove,
		kCustomStart = 100,
	};

	enum GripActionType
	{
		kDragOn = 0,
		kImmediate,
		kCommand,
	};

	enum GripCursorType
	{
		kcNone = 0,
		kcCrosshairPlus,         
		kcCrosshairMinus,
		kcCrosshairCurve,
		kcCrosshairLine,      
		kcCrosshairAngle,      
	};
	struct GripMode
	{
		GripMode();
		unsigned int    Mode;
		NcString        DisplayString;
		NcString        ToolTip;
		NcString        CLIDisplayString;
		NcString        CLIPromptString;
		NcString        CLIKeywordList;
		GripCursorType  CursorType;
		GripActionType  ActionType;
		NcString        CommandString;
	};
	virtual bool getGripModes(NcDbEntity* pThis, 
		NcDbGripData* pGripData, 
		NcArray<GripMode>& modes, 
		unsigned int& curMode) const = 0;
	virtual unsigned int mode(NcDbEntity* pThis, NcDbGripData* pGripData) const = 0;
	virtual GripMode modeEx(NcDbEntity* pThis, NcDbGripData* pGripData) const = 0;
	virtual bool setMode(NcDbEntity* pThis, NcDbGripData* pGripData, unsigned int newMode) = 0;
	virtual GripType gripType(NcDbEntity* pThis, NcDbGripData* pGripData) const = 0;
	virtual void reset(NcDbEntity* pThis) = 0;
};

inline NcDbMultiModesGripPE::GripMode::GripMode()
	: Mode(NcDbMultiModesGripPE::kMove)
	, ActionType(kDragOn)
{
}



class NRXDBGATE_EXPORT NcDbTextFieldsPE : public NcRxObject
{
public:
	typedef std::map<OdString, OdString> NcDbTextFieldsContainer;//Property 'name - value'
public:
	NCRX_DECLARE_MEMBERS(NcDbTextFieldsPE);
	virtual bool getAllTextFields(NcDbObject* pObj, NcDbTextFieldsContainer& textFields) const = 0;
};


#endif // __OPENDWG_DATABASE_H__
