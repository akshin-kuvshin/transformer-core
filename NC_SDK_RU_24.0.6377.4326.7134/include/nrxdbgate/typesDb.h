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

#ifndef __OPENDWGTHUNKTYPES_H__
#define __OPENDWGTHUNKTYPES_H__
#include "nrxdbgate_impexp.h"

#if __LP64__
#define Nano_Boolean_is_bool 1
#endif

#ifdef X
#undef X
#endif
#ifdef Y
#undef Y
#endif
#ifdef Z
#undef Z
#endif
#ifdef T
#undef T
#endif

#ifndef _XYZT_DEFINED
#define _XYZT_DEFINED
enum { X = 0, Y = 1, Z = 2 };
enum { T = 3 };
#endif


// String Constants
//
#define NCDB_SERVICES                     _T("AcDbServices")
#define NCDB_MODEL_SPACE                  _T("*Model_Space")
#define NCDB_PAPER_SPACE                  _T("*Paper_Space")
#define NCDB_NULL_HANDLE                  _T("\0\0\0\0\0\0\0")
#define NCDB_BROKEN_HANDLE                _T("FFFFFFFF")
#define NCDB_OPEN_BRACE_STR               _T("{")
#define NCDB_OPEN_BRACE_CHAR              _T('{')
#define NCDB_CLOSE_BRACE_STR              _T("}")
#define NCDB_CLOSE_BRACE_CHAR             _T('}')
#define NCDB_GROUP_DICTIONARY             _T("ACAD_GROUP")
#define NCDB_MLINESTYLE_DICTIONARY        _T("ACAD_MLINESTYLE")
#define NCDB_LAYOUT_DICTIONARY            _T("ACAD_LAYOUT")
#define NCDB_PLOTSETTINGS_DICTIONARY      _T("ACAD_PLOTSETTINGS")
#define NCDB_PLOTSTYLENAME_DICTIONARY     _T("ACAD_PLOTSTYLENAME")
#define NCDB_MATERIAL_DICTIONARY          _T("ACAD_MATERIAL")
#define NCDB_VISUALSTYLE_DICTIONARY       _T("ACAD_VISUALSTYLE")
#define NCDB_COLOR_DICTIONARY             _T("ACAD_COLOR")
#define NCDB_TABLESTYLE_DICTIONARY        _T("ACAD_TABLESTYLE")
#define NCDB_EMBEDDED_OBJECT_STR          _T("Embedded Object")
#define NCDB_LAYERSTATES_DICTIONARY       _T("ACAD_LAYERSTATES")
#define NCDB_FIELD_DICTIONARY             _T("ACAD_FIELD")
#define NCDB_FIELDLIST                    _T("ACAD_FIELDLIST")
#define NCDB_ENHANCED_BLOCK               _T("ACAD_ENHANCEDBLOCK")
#define NCDB_ENHANCED_BLOCK_EVALKEY       _T("ACAD_ENHANCEDBLOCKEVALKEY")
#define NCDB_ENHANCED_BLOCK_REF           _T("ACAD_ENHANCEDBLOCK_REFERENCE")
#define NCDB_SECTION_MANAGER              _T("ACAD_SECTION_MANAGER")
#define NCDB_ANNOTATIONSCALES_COLLECTION  _T("ACDB_ANNOTATIONSCALES")

class OdRxObject;
class NRXDBGATE_EXPORT NcBaseObjectPtr
{
protected:
	OdRxObject* m_pObject;

	NcBaseObjectPtr() : m_pObject(0) {}
	explicit NcBaseObjectPtr(const OdRxObject* pSource) : m_pObject(const_cast<OdRxObject*>(pSource)) {}
public:
	OdRxObject* get() const { return m_pObject; }

	bool isNull() const { return m_pObject == 0; }
};
enum NcRxObjMod { kNcRxObjAttach };
class NRXDBGATE_EXPORT NcRxObjectPtr : public NcBaseObjectPtr
{
	inline void internalAddRef();
	void assign(
		const OdRxObject* pObject);

public:
	NcRxObjectPtr();
	NcRxObjectPtr(
		const OdRxObject* pSource,
		NcRxObjMod);

	NcRxObjectPtr(
		const OdRxObject* pSource);

	NcRxObjectPtr(
		const NcRxObjectPtr& pSource);

	NcRxObjectPtr(
		const NcBaseObjectPtr& pSource);

	void attach(
		const OdRxObject* pObject);
	~NcRxObjectPtr();
	inline void release();
	OdRxObject* detach();
	NcRxObjectPtr& operator = (
		const NcRxObjectPtr& source);

	NcRxObjectPtr& operator = (
		const OdRxObject* source);

	NcRxObjectPtr& operator = (
		const NcBaseObjectPtr& source);

	OdRxObject* get();
	const OdRxObject* get() const;
	OdRxObject* operator ->();
	const OdRxObject* operator ->() const;
	operator OdRxObject* () { return get(); }

	operator const OdRxObject* () const { return get(); };

	bool operator==(
		const OdRxObject* pObject) const {
		return (m_pObject == pObject);
	};

	bool operator!=(
		const OdRxObject* pObject) const {
		return (m_pObject != pObject);
	};
};
class NcRxObject;
NRXDBGATE_EXPORT NcRxObjectPtr convertObjectFromNcToOd(NcRxObject* obj);

#define NCRX_DECLARE_MEMBERS(CLASS_NAME) \
	public: \
	virtual NcRxClass* isA() const; \
	static NcRxClass* desc(); \
	static CLASS_NAME* cast(const NcRxObject* source) \
{ \
	return ((source == NULL) || !source->isKindOf(CLASS_NAME::desc())) ? NULL : (CLASS_NAME*)source; \
}; \
	static void rxInit(); \
	static NcRxClass* gpDesc;

#define NCDB_DECLARE_MEMBERS(CLASSNAME) \
	public: \
	NCRX_DECLARE_MEMBERS(CLASSNAME)

#define NCRX_DXF_DEFINE_MEMBERS(CLASS_NAME, PARENT_CLASS, DWG_VERSION, MAINTENANCE_VERSION, PROXY_FLAGS, DXF_NAME, APP) \
	NCRX_DEFINE_MEMBERS(CLASS_NAME); \
	static NcRxObject* make##CLASS_NAME() \
{ \
	return new CLASS_NAME(); \
} \
	static NcRxObjectPtr make##CLASS_NAME##PlatformThunk() \
{ \
	NcRxObject* object = make##CLASS_NAME(); \
	return convertObjectFromNcToOd(object); \
} \
	void CLASS_NAME::rxInit() \
{ \
	CLASS_NAME::gpDesc = NewRxClass(_NCRX_T(#CLASS_NAME), _NCRX_T(#PARENT_CLASS), DWG_VERSION, MAINTENANCE_VERSION, \
	PROXY_FLAGS, &make##CLASS_NAME##PlatformThunk, &make##CLASS_NAME, \
	_NCRX_T(#DXF_NAME), _NCRX_T(#APP)); \
}

#define NCRX_CONS_DEFINE_MEMBERS(CLASS_NAME, PARENT_CLASS, VERNO) \
	NCRX_DEFINE_MEMBERS(CLASS_NAME); \
	static NcRxObject* make##CLASS_NAME() \
{ \
	return new CLASS_NAME(); \
} \
	static NcRxObjectPtr make##CLASS_NAME##PlatformThunk() \
{ \
	NcRxObject* object = make##CLASS_NAME(); \
	return convertObjectFromNcToOd(object); \
} \
	void CLASS_NAME::rxInit() \
{ \
	CLASS_NAME::gpDesc = NewRxClass(_NCRX_T(#CLASS_NAME), _NCRX_T(#PARENT_CLASS), 0, 0, VERNO, \
	&make##CLASS_NAME##PlatformThunk, &make##CLASS_NAME); \
}

#define NCRX_DEFINE_MEMBERS(CLASS_NAME) \
	NcRxClass* CLASS_NAME::desc() \
{ \
	if (CLASS_NAME::gpDesc != NULL) \
	return CLASS_NAME::gpDesc; \
	return CLASS_NAME::gpDesc = NcRxClass::find(_NCRX_T(#CLASS_NAME)); \
} \
	NcRxClass* CLASS_NAME::isA() const \
{ \
	return desc(); \
} \
	NcRxClass* CLASS_NAME::gpDesc = NULL;


#define NCRX_NO_CONS_DEFINE_MEMBERS(CLASS_NAME, PARENT_CLASS) \
	NCRX_DEFINE_MEMBERS(CLASS_NAME); \
	void CLASS_NAME::rxInit() \
{ \
	CLASS_NAME::gpDesc = NewRxClass(_NCRX_T(#CLASS_NAME), _NCRX_T(#PARENT_CLASS), 0, 0, 0, 0, 0, 0, 0); \
}

#define NCRX_PE_PTR(RxObj, PEClass)  PEClass::cast(RxObj->queryX(PEClass::desc()))
#define NCRX_X_CALL(RxObj,PEClass) PEClass::cast(RxObj->x(PEClass::desc()))

#define ncrxProtocolReactors \
	NcRxProtocolReactorManagerFactory::cast(ncrxServiceDictionary-> \
	at(NCRX_PROTOCOL_REACTOR_MANAGER))
#define NCRX_PROTOCOL_REACTOR_MANAGER_AT(ncrxClass) \
	ncrxProtocolReactors->createReactorManager(ncrxClass)
#define NCRX_PROTOCOL_REACTOR_LIST_AT(ncrxClass, reactorClass) \
	NCRX_PROTOCOL_REACTOR_MANAGER_AT(ncrxClass)->createReactorList(reactorClass)


#define ncrxDynamicLinker \
	GetDynamicLinker()

class NcDxfCode
{
public:
	/** \details
	  Defines codes for data types.
	*/
	enum Type
	{
		Unknown = 0,
		Name = 1,
		String = 2,
		Bool = 3,
		Integer8 = 4,
		Integer16 = 5,
		Integer32 = 6,
		Double = 7,
		Angle = 8,
		Point = 9,
		BinaryChunk = 10,
		LayerName = 11,
		Handle = 12,
		ObjectId = 13,
		SoftPointerId = 14,
		HardPointerId = 15,
		SoftOwnershipId = 16,
		HardOwnershipId = 17,
		Integer64 = 18
	};

	/** \details
	  Returns the data type for the specified group code (DXF code).

	  \sa
	  <link db_rb_verify, Determining the Data Type by Group Code>

	  \sa
	  <link db_rb_type, Getting and Setting Tagged Data>
	*/
	NRXDBGATE_EXPORT static Type _getType(int code);
};
struct Nano
{
	enum NcRxObjMod { kOdRxObjAttach };
	enum ErrorStatus 
	{
		eOk = 0,
		eMakeMeProxy,
		eInvalidDrawing,
		eNotImplementedYet,
		eNotApplicable,
		eInvalidInput,
		eInvalidFiler,
		eAmbiguousInput,
		eAmbiguousOutput,
		eOutOfMemory,
		eNoInterface,
		eBufferTooSmall,
		eInvalidOpenState,
		eUnsupportedMethod,
		eEntityInInactiveLayout,
		eDuplicateHandle,
		eNullHandle,
		eBrokenHandle,
		eUnknownHandle,
		eHandleInUse,
		eNullObjectPointer,
		eNullObjectId,
		eNullBlockName,
		eContainerNotEmpty,
		eNullEntityPointer,
		eIllegalEntityType,
		eKeyNotFound,
		eDuplicateKey,
		eInvalidIndex,
		eCharacterNotFound,
		eDuplicateIndex,
		eAlreadyInDb,
		eOutOfDisk,
		eDeletedEntry,
		eNegativeValueNotAllowed,
		eInvalidExtents,
		eInvalidAdsName,
		eInvalidSymbolTableName,
		eInvalidKey,
		eWrongObjectType,
		eWrongDatabase,
		eObjectToBeDeleted,
		eInvalidFileVersion,
		eAnonymousEntry,
		eIllegalReplacement,
		eEndOfObject,
		eEndOfFile,
		eFileExists,
		eCantOpenFile,
		eFileCloseError,
		eFileWriteError,
		eNoFileName,
		eFilerError,
		eFileAccessErr,
		eFileSystemErr,
		eFileInternalErr,
		eFileTooManyOpen,
		eFileNotFound,
		eUnknownFileType,
		eIsReading,
		eIsWriting,
		eNotOpenForRead,
		eNotOpenForWrite,
		eNotThatKindOfClass,
		eInvalidBlockName,
		eMissingDxfField,
		eDuplicateDxfField,
		eInvalidGroupCode,
		eInvalidResBuf,
		eBadDxfSequence,
		eInvalidRoundTripR14Data,
		eVertexAfterFace,
		eInvalidVertexIndex,
		eOtherObjectsBusy,
		eMustFirstAddBlockToDb,
		eCannotNestBlockDefs,
		eDwgRecoveredOK,
		eDwgNotRecoverable,
		eDxfPartiallyRead,
		eDxfReadAborted,
		eDxbPartiallyRead,
		eDwgCRCError,
		eDwgSentinelDoesNotMatch,
		eDwgObjectImproperlyRead,
		eNoInputFiler,
		eDwgNeedsAFullSave,
		eDxbReadAborted,
		eDwkLockFileFound,
		eWasErased,
		ePermanentlyErased,
		eWasOpenForRead,
		eWasOpenForWrite,
		eWasOpenForUndo,
		eWasNotifying,
		eWasOpenForNotify,
		eOnLockedLayer,
		eMustOpenThruOwner,
		eSubentitiesStillOpen,
		eAtMaxReaders,
		eIsWriteProtected,
		eIsXRefObject,
		eNotAnEntity,
		eHadMultipleReaders,
		eInvalidBlkRecordName,
		eDuplicateRecordName,
		eNotXrefBlock,
		eEmptyRecordName,
		eXRefDependent,
		eSelfReference,
		eMissingSymbolTable,
		eMissingSymbolTableRec,
		eWasNotOpenForWrite,
		eCloseWasNotifying,
		eCloseModifyAborted,
		eClosePartialFailure,
		eCloseFailObjectDamaged,
		eCannotBeErasedByCaller,
		eCannotBeResurrected,
		eInsertAfter,
		eFixedAllErrors,
		eLeftErrorsUnfixed,
		eUnrecoverableErrors,
		eNoDatabase,
		eXdataSizeExceeded,
		eCannotSaveHatchRoundtrip,
		eHatchHasInconsistentPatParams,
		eRegappIdNotFound,
		eRepeatEntity,
		eRecordNotInTable,
		eIteratorDone,
		eNullIterator,
		eNotInBlock,
		eOwnerNotInDatabase,
		eOwnerNotOpenForRead,
		eOwnerNotOpenForWrite,
		eExplodeBeforeTransform,
		eCannotScaleNonOrtho,
		eCannotScaleNonUniformly,
		eNotInDatabase,
		eNotCurrentDatabase,
		eIsAnEntity,
		eCannotChangeActiveViewport,
		eNotInPaperspace,
		eCommandWasInProgress,
		eGeneralModelingFailure,
		eOutOfRange,
		eNonCoplanarGeometry,
		eDegenerateGeometry,
		eInvalidAxis,
		ePointNotOnEntity,
		eSingularPoint,
		eInvalidOffset,
		eNonPlanarEntity,
		eCannotExplodeEntity,
		eStringTooLong,
		eInvalidSymTableFlag,
		eUndefinedLineType,
		eInvalidTextStyle,
		eTooFewLineTypeElements,
		eTooManyLineTypeElements,
		eExcessiveItemCount,
		eIgnoredLinetypeRedef,
		eBadUCS,
		eBadPaperspaceView,
		eSomeInputDataLeftUnread,
		eNoInternalSpace,
		eInvalidDimStyle,
		eInvalidLayer,
		eInvalidMlineStyle,
		eDwgNeedsRecovery,
		eRecoveryFailed,
		eDeleteEntity,
		eInvalidFix,
		eBadLayerName,
		eLayerGroupCodeMissing,
		eBadColor,
		eBadColorIndex,
		eBadLinetypeName,
		eBadLinetypeScale,
		eBadVisibilityValue,
		eProperClassSeparatorExpected,
		eBadLineWeightValue,
		ePagerError,
		eOutOfPagerMemory,
		ePagerWriteError,
		eWasNotForwarding,
		eInvalidIdMap,
		eInvalidOwnerObject,
		eOwnerNotSet,
		eWrongSubentityType,
		eTooManyVertices,
		eTooFewVertices,
		eNoActiveTransactions,
		eTransactionIsActive,
		eNotTopTransaction,
		eTransactionOpenWhileCommandEnded,
		eInProcessOfCommitting,
		eNotNewlyCreated,
		eLongTransReferenceError,
		eNoWorkSet,
		eAlreadyInGroup,
		eNotInGroup,
		eBadDwgFile,
		eInvalidREFIID,
		eInvalidNormal,
		eInvalidStyle,
		eCannotRestoreFromAcisFile,
		eEmptyAcisFile,
		eNLSFileNotAvailable,
		eNotAllowedForThisProxy,
		eNotSupportedInDwgApi,
		ePolyWidthLost,
		eNullExtents,
		eExplodeAgain,
		eBadDwgHeader,
		eLockViolation,
		eLockConflict,
		eDatabaseObjectsOpen,
		eLockChangeInProgress,
		eVetoed,
		eNoDocument,
		eNotFromThisDocument,
		eLISPActive,
		eTargetDocNotQuiescent,
		eDocumentSwitchDisabled,
		eInvalidContext,
		eCreateFailed,
		eCreateInvalidName,
		eSetFailed,
		eDelDoesNotExist,
		eDelIsModelSpace,
		eDelLastLayout,
		eDelUnableToSetCurrent,
		eDelUnableToFind,
		eRenameDoesNotExist,
		eRenameIsModelSpace,
		eRenameInvalidLayoutName,
		eRenameLayoutAlreadyExists,
		eRenameInvalidName,
		eCopyDoesNotExist,
		eCopyIsModelSpace,
		eCopyFailed,
		eCopyInvalidName,
		eCopyNameExists,
		eProfileDoesNotExist,
		eInvalidProfileName,
		eProfileIsInUse,
		eRegistryAccessError,
		eRegistryCreateError,
		eBadDxfFile,
		eUnknownDxfFileFormat,
		eMissingDxfSection,
		eInvalidDxfSectionName,
		eNotDxfHeaderGroupCode,
		eUndefinedDxfGroupCode,
		eNotInitializedYet,
		eInvalidDxf2dPoint,
		eInvalidDxf3dPoint,
		eBadlyNestedAppData,
		eIncompleteBlockDefinition,
		eIncompleteComplexObject,
		eBlockDefInEntitySection,
		eNoBlockBegin,
		eDuplicateLayerName,
		eBadPlotStyleName,
		eDuplicateBlockName,
		eBadPlotStyleType,
		eBadPlotStyleNameHandle,
		eUndefineShapeName,
		eDuplicateBlockDefinition,
		eMissingBlockName,
		eBinaryDataSizeExceeded,
		eObjectIsReferenced,
		eInvalidThumbnailBitmap,
		eGuidNoAddress,
		eMustBe0to2,
		eMustBe0to3,
		eMustBe0to4,
		eMustBe0to5,
		eMustBe0to8,
		eMustBe1to8,
		eMustBe1to15,
		eMustBePositive,
		eMustBeNonNegative,
		eMustBeNonZero,
		eMustBe1to6,
		eNoPlotStyleTranslationTable,
		ePlotStyleInColorDependentMode,
		eMaxLayouts,
		eNoClassId,
		eUndoOperationNotAvailable,
		eUndoNoGroupBegin,
		eHatchTooDense,
		eOpenFileCancelled,
		eNotHandled,
		eLibIntegrityBroken,
		eAlreadyActive,
		eAlreadyInactive,
		eCodepageNotFound,
		eIncorrectInitFileVersion,
		eInternalFreetypeError,
		eNoUCSPresent,
		eBadObjType,
		eBadProtocolExtension,
		eHatchInvalidPatternName,
		eNotTransactionResident,
		eDwgFileIsEncrypted,
		eInvalidPassword,
		eDecryptionError,
		eArithmeticOverflow,
		eSkipObjPaging,
		eStopPaging,
		eInvalidDimStyleResBufData,
		eExtendedError,
		eGripOpFailure,	//In NcDbGripOperations
		eGripOpNoRedrawGrip, //In NcDbGripOperations
		eGripOpGripHotToWarm, //In NcDbGripOperations
		eGripOpGetNewGripPoints, //In NcDbGripOperations
		eUnsupportedEarlyDwgVersion = 318,
		eCannotChangeColumnType,
		eCustomSizeNotPossible,
		eDataLinkAdapterNotFound,
		eDataLinkBadConnectionString,
		eDataLinkConnectionFailed,
		eDataLinkInvalidAdapterId,
		eDataLinkNotFound,
		eDataLinkNotUpdatedYet,
		eDataLinkOtherError,
		eDataLinkSourceIsWriteProtected,
		eDataLinkSourceNotFound,
		eDeviceNotFound,
		eDwgCrcDoesNotMatch,
		eDwgCRCDoesNotMatch = eDwgCrcDoesNotMatch,
		eDwgShareDemandLoad,
		eDwgShareReadAccess,
		eDwgShareWriteAccess,
		eFileMissingSections,
		eFileSharingViolation,
		eFiniteStateMachineError,
		eGraphicsNotGenerated,
		eHandleExists,
		eIgnoredLinetypeRedefinition,
		eIncompatiblePlotSettings,
		eInternetBadPath,
		eInternetBase,
		eInternetCreateInternetSessionFailed,
		eInternetDirectoryFull,
		eInternetDiskFull,
		eInternetFileAccessDenied,
		eInternetFileGenericError,
		eInternetFileNotFound,
		eInternetFileOpenFailed,
		eInternetGenericException,
		eInternetHardwareError,
		eInternetHttpAccessDenied,
		eInternetHttpBadGateway,
		eInternetHttpBadMethod,
		eInternetHttpBadRequest,
		eInternetHttpConflict,
		eInternetHttpGatewayTimeout,
		eInternetHttpLengthRequired,
		eInternetHttpNoAcceptableResponse,
		eInternetHttpNotSupported,
		eInternetHttpObjectNotFound,
		eInternetHttpOpenRequestFailed,
		eInternetHttpPaymentRequired,
		eInternetHttpPreconditionFailure,
		eInternetHttpProxyAuthorizationRequired,
		eInternetHttpRequestForbidden,
		eInternetHttpRequestTooLarge,
		eInternetHttpResourceGone,
		eInternetHttpServerError,
		eInternetHttpServiceUnavailable,
		eInternetHttpTimedOut,
		eInternetHttpUnsupportedMedia,
		eInternetHttpUriTooLong,
		eInternetHttpVersionNotSupported,
		eInternetInCache,
		eInternetInternetError,
		eInternetInternetSessionConnectFailed,
		eInternetInternetSessionOpenFailed,
		eInternetInvalidAccessType,
		eInternetInvalidFileHandle,
		eInternetNoInternetSupport,
		eInternetNotAnUrl,
		eInternetNotImplemented,
		eInternetNoWinInternet,
		eInternetOK,
		eInternetOldWinInternet,
		eInternetProtocolNotSupported,
		eInternetSharingViolation,
		eInternetTooManyOpenFiles,
		eInternetUnknownError,
		eInternetUserCancelledTransfer,
		eInternetValidUrl,
		eInvalidEngineState,
		eInvalidFaceVertexIndex,
		eInvalidFileExtension,
		eInvalidMeshVertexIndex,
		eInvalidObjectId,
		eInvalidPlotArea,
		eInvalidPlotInfo,
		eInvalidView,
		eInvalidWindowArea,
		eInvalidXrefObjectId,
		eLayoutNotCurrent,
		eMakeMeProxyAndResurrect,
		eMustPlotToFile,
		eCannotPlotToFile,
		eNoCurrentConfig,
		eNoErrorHandler,
		eNoLabelBlock,
		eNoLayout,
		eNoMatchingMedia,
		eNonePlotDevice,
		eNoThumbnailBitmap,
		eNotMultiPageCapable,
		eNoViewAssociation,
		eNullPtr,
		eNumberOfCopiesNotSupported,
		eObsoleteFileFormat,
		ePageCancelled,
		ePlotAlreadyStarted,
		ePlotCancelled,
		eRepeatedDwgRead,
		eRowsMustMatchColumns,
		eSecErrorCipherNotSupported,
		eSecErrorComputingSignature,
		eSecErrorDecryptingData,
		eSecErrorEncryptingData,
		eSecErrorGeneratingTimestamp,
		eSecErrorReadingFile,
		eSecErrorWritingFile,
		eSecErrorWritingSignature,
		eSecInitializationFailure,
		eSecInvalidDigitalId,
		eSecInvalidDigitalID = eSecInvalidDigitalId,
		eLoadFailed,
		eSubSelectionSetEmpty,
		eUnableToGetLabelBlock,
		eUnableToGetViewAssociation,
		eUnableToRemoveAssociation,
		eUnableToSetLabelBlock,
		eUnableToSetViewAssociation,
		eUnableToSyncModelView,
		eUnsupportedFileFormat,
		eUserBreak,
		eWasNotErased,
		eWrongCellType,
		eTxError,
		eHiddenLayerNotAllowed,
		eInvalidLicense,
		eIncorrectDatabaseType,
		eInvalidCategory,

		eCryptProviderUnavailable,
		eInvalidNumPCurves,
		eNoTrimmigLoop,
		eBrokenTrimmingLoop,
		eBadApexLoop,
		eLoopNotClosed,
		eLoopIsNotOnFace,
		eLoopSelfIntersecting,
		eInvalidIntervals,
		eEmptySet,
		eInfinite,

		eDataTooLarge,

		eSyntaxError,
		eDisabledInConfig,
		eCantSetEnvVar,
		eInvalidSurface,
		eInvalidOrientation,
		eLoopsIntersecting,
		eInvalidEdge,
		eNullEdgeCurve,
		eNullFaceSurface,
		eStartOrEndPntNotSet,
		eIntervalIsTooShort,
		eCurveLengthIsTooShort,
		eCurveEndsMissed,
		ePointNotOnCurve,
		eInvalidProps,
		eInvalidCurve,
		eDiscontinuousCurve,
		eParamHasNoValue,

		eBrFileMissed,
		eBrBrepMissed,
		eBrComplexMissed,
		eBrShellMissed,
		eBrFaceMissed,
		eBrLoopMissed,
		eBrEdgeMissed,
		eBrVertexMissed,
		eBrEmptyLoop,
		eCellNotFound,
		eInvalidElementState,
		//eNoIntersections,
		eMSmemcpySecureInvalidParameter = 494,
		eMSmemmoveSecureInvalidParameter,

		eDaiInternalError,
		eIncorrectSchema,
		eUnsupportedSchema,
		eEmptyRepository,

		//eFailedToEvaluate,
		//eFailedToEvaluateDependents,
		//eInvalidExpression,
		//eCyclicDependency,

		// ObjectARX specific error statuses

		eInvalidDwgVersion                      = 1024,
		eInvalidDxfCode,
		eFileLockedByNCAD,
		eUserUnloaded,
		eFSMError,
		eBadMaterialName,
		eAlreadyInferred,
		eNotClonedPrimaryProxy,
		eSilentOpenFileCancelled,
		eNullNodeId,
		eNoNodeActive,
		eGraphContainsProxies,
		eBackgroundPlotInProgress,
		eNotShownInPropertyPalette,
		eNoIntersections,
		eEmbeddedIntersections,
		eNoOverride,
		eNoStoredOverrides,
		eUnableToRetrieveOverrides,
		eUnableToStoreOverrides,
		eUnableToRemoveOverrides,
		eNoStoredReconcileStatus,
		eUnableToStoreReconcileStatus,
		eDataLinkSourceUpdateNotAllowed,
		eDataLinkExcelNotFound,
		eXrefReloaded,
		eXrefReloadImpossibleAtThisTime,
		eNoNcDbHostApplication,               // eNoAcDbHostApplication
		eNoUnderlayHost,
		ePCUnknown,
		ePCLargeData,
		ePCUnknownFileType,
		ePCFileNotFound,
		ePCFileNotCreated,
		ePCFileNotOpened,
		ePCFileNotClosed,
		ePCFileNotWritten,
		ePCFileWrongFormat,
		ePCFileDataSelectorInvalid,
		ePCCoordSysReprojectFail,
		ePCDiskSpaceTooSmall,
		ePCThreadTerminated,
		ePCFileNotErased,
		ePCCoordSysAssignFail,
		ePCLastImporterUnfinished,
		ePCNoEngineInfo,
		ePCInProgress,
		eInetBase,
		eInetOk,
		eInetInCache,
		eInetFileNotFound,
		eInetBadPath,
		eInetTooManyOpenFiles,
		eInetFileAccessDenied,
		eInetInvalidFileHandle,
		eInetDirectoryFull,
		eInetHardwareError,
		eInetSharingViolation,
		eInetDiskFull,
		eInetFileGenericError,
		eInetValidURL,
		eInetNotAnURL,
		eInetNoWinInet,
		eInetOldWinInet,
		eInetNoAcadInet,
		eInetNotImplemented,
		eInetProtocolNotSupported,
		eInetCreateInternetSessionFailed,
		eInetInternetSessionConnectFailed,
		eInetInternetSessionOpenFailed,
		eInetInvalidAccessType,
		eInetFileOpenFailed,
		eInetHttpOpenRequestFailed,
		eInetUserCancelledTransfer,
		eInetHttpBadRequest,
		eInetHttpAccessDenied,
		eInetHttpPaymentRequired,
		eInetHttpRequestForbidden,
		eInetHttpObjectNotFound,
		eInetHttpBadMethod,
		eInetHttpNoAcceptableResponse,
		eInetHttpProxyAuthorizationRequired,
		eInetHttpTimedOut,
		eInetHttpConflict,
		eInetHttpResourceGone,
		eInetHttpLengthRequired,
		eInetHttpPreconditionFailure,
		eInetHttpRequestTooLarge,
		eInetHttpUriTooLong,
		eInetHttpUnsupportedMedia,
		eInetHttpServerError,
		eInetHttpNotSupported,
		eInetHttpBadGateway,
		eInetHttpServiceUnavailable,
		eInetHttpGatewayTimeout,
		eInetHttpVersionNotSupported,
		eInetInternetError,
		eInetGenericException,
		eInetUnknownError,
		eGraphEdgeNotFound,
		eGraphNodeNotFound,
		eGraphNodeAlreadyExists,
		eGraphEdgeAlreadyExists,
		eGraphCyclesFound,
		eAlreadyHasRepresentation,
		eNoRepresentation,
		eFailedToSetEdgeChamfers,
		eNoConnectedBlendSet,
		eFailedToBlend,
		eFailedToSetEdgeRounds,
		eFailedToSetVertexRounds,
		eVSNotFound,
		eVSTrue,
		eVSFalse,
		eVSAlreadyExists,
		eVSOneOffCreated,
		eVSAPIOnlyValues,
		eVSIsInUse,
		eVSIsAcadDefault,
		eEmptyOperand,
		eNoEntitiesFromPersistentIds,
		eFailedCurveCheck,
		eMaxNodes,
		eFailedToEvaluate,
		eFailedToEvaluateDependents,
		eInvalidExpression,
		eCyclicDependency,
		eInconsistentConstraint,
		eOverDefinedConstraint,
		eAllInSameRigidSet,
		eInvalidParameterName,
		eReferencedInEquation,
		eEntityRestricedInDOF,
		eNearSizeLimit,
		eStringNotAllowedInExpression,
		eTooManyActiveCommands,
		eUnableToTrimLastPiece,
		eUnableToTrimSurface,
		eModifyingAssociativeEntity,
		eModifyingDimensionWithExpression,
		eDependentOnObjectErased,
		eSelfIntersecting,
		eNotOnBoundary,
		eNotConnected,
		eNoInputPath,
		eNotAssociative,
		eNotG1Continuous,
		eOwnerToBeTransformed,
		eMustBeInteger,
		eMustBePositiveInteger,
		eChangedAgainstAssociativity,
		eItemCountChanged,
		eGetAdIntImgServicesFailed,
		eReadImageBufferFailed,
		eWriteImageBufferFailed,
		eGetImageBytesFailed,
		eGetImageDIBFailed,
		eConvertImageFormatFailed,
		eGetPreviewImageFailed,
		eInvalidPreviewImage,
		eDelayMore,
		ePreviewFailed,
		eAbortPreview,
		eEndPreview,
		eNoPreviewContext,
		eFileNotInCloud
	};

	enum PointHistory
	{
		eTablet         = 0x0001,
		eNotDigitizer   = 0x0002,
		eLastPt         = 0x0004,
		eGripped        = 0x008,
		eCartSnapped    = 0x0010,
		eOrtho          = 0x0020,
		eCyclingPt      = 0x0040,
		eOsnapped       = 0x0080,
		ePolarAngle     = 0x0100,
		eAligned        = 0x0400,
		eAppFiltered    = 0x0800,
		eForcedPick     = 0x1000,
		ePickMask       = 0xE000,
		eDidNotPick     = 0x0000,
		eUsedPickBox    = 0x2000,
		eUsedOsnapBox   = 0x4000,
		ePickAborted    = 0x8000,
		eXPending       = 0x10000,
		eYPending       = 0x20000,
		eZPending       = 0x40000,
		eCoordPending   = 0x70000,
		eFromKeyboard   = 0x80000,
		eNotInteractive = 0x100000,
	};

	enum PromptStatus
	{
		eNone     = 5000,
		eNormal   = 5100,
		eError    = -5001,
		eCancel   = -5002,
		eRejected = -5003,
		eFailed   = -5004,
		eKeyword  = -5005,
		eDirect   = -5999
	};
};

typedef wchar_t NCHAR;
#define _NCRX_T(x)  L ## x
#define NCRX_T(x)  _NCRX_T(x)
#define _NCRX_T_STR(y) NCRX_T(#y)    // Stringize argument, e.g.                              NcDbClass -> "NcDbClass"
#define NCRX_T_STR(y) _NCRX_T_STR(y) // Allow argument to be a #define found in nc2ac.h, e.g. AcDbClass -> "NcDbClass"

struct NRX
{
	typedef signed char     Int8;
	typedef short           Int16;
	typedef long            Int32;
	typedef __int64         Int64;

	typedef unsigned char   UInt8;
	typedef unsigned short  UInt16;
	typedef unsigned long   UInt32;
	typedef unsigned __int64 UInt64;

	typedef unsigned char   uchar;
	typedef unsigned short  ushort;
	typedef unsigned int    uint;
	typedef unsigned long   ulong;

#ifndef Nano_Boolean_is_bool
	typedef int             Boolean;
	enum  { kFalse = 0, kTrue = 1 };
#else
	typedef bool            Boolean;
	enum { kFalse = false, kTrue = true };
#endif

#ifdef _WIN64
	typedef unsigned __int64  Size_t;
	typedef __int64           SSize_t;
	typedef __int64           LongPtr;
	typedef unsigned __int64  ULongPtr;
	typedef __int64           IntPtr;
	typedef unsigned __int64  UIntPtr;
#else
	typedef unsigned long     Size_t;
	typedef long              SSize_t;
	typedef long              LongPtr;
	typedef unsigned long     ULongPtr;
	typedef int               IntPtr;
	typedef unsigned int      UIntPtr;
#endif
	typedef ptrdiff_t         GsMarker;

	typedef LongPtr           IntDbId;
};

enum
{
	kTrue  = NRX::kTrue,
	kFalse = NRX::kFalse
};

struct NcRx
{
	typedef void (*FcnPtr)();

	enum DictIterType
	{
		kDictSorted   = 0,
		kDictCollated = 1
	};

	enum Ordering
	{
		kLessThan     =-1, // This object < Specified Object
		kEqual        = 0, // This object == Specified Object
		kGreaterThan  = 1, // This object > Specified Object
		kNotOrderable = 2  // These objects cannot be ordered.
	};

	enum AppMsgCode
	{
		kNullMsg         = 0,
		kInitAppMsg      = 1,
		kUnloadAppMsg    = 2,
		kLoadDwgMsg      = 3,
		kUnloadDwgMsg    = 4,
		kInvkSubrMsg     = 5,
		kCfgMsg          = 6,
		kEndMsg          = 7,
		kQuitMsg         = 8,
		kSaveMsg         = 9,
		kDependencyMsg   = 10,
		kNoDependencyMsg = 11,
		kOleUnloadAppMsg = 12,
		kPreQuitMsg      = 13,
		kInitDialogMsg   = 14,
		kEndDialogMsg    = 15,
		kSuspendMsg      = 16
	};

	enum AppRetCode
	{
		kRetOK    = 0,
		kRetError = 3
	};
};

struct NcDb
{
	enum OpenMode
	{
		kForRead   = 0,
		kForWrite  = 1,
		kForNotify = 2
	};

	enum CoordAxis
	{
		kX = 0,
		kY = 1,
		kZ = 2
	};

	enum CoordSystem
	{
		kWorldCS        = 0,
		kUserCS         = 1,
		kCurDisplayCS   = 2,
		kPaperDisplayCS = 3,
		kEntityCS       = 4
	};

	enum Intersect
	{
		kOnBothOperands    = 0,
		kExtendThis        = 1,
		kExtendArg         = 2,
		kExtendBoth        = 3
	};

	enum Visibility
	{
		kInvisible = 1,
		kVisible   = 0
	};

	typedef NRX::Int16  DxfCode;

	enum
	{
		kDxfInvalid             = -9999,
		kDxfXDictionary         = -6,
		kDxfPReactors           = -5,
		kDxfOperator            = -4,
		kDxfXDataStart          = -3,
		kDxfHeaderId            = -2,
		kDxfFirstEntId          = -2,
		kDxfEnd                 = -1,
		kDxfStart               = 0,
		kDxfText                = 1,
		kDxfXRefPath            = 1,
		kDxfShapeName           = 2,
		kDxfBlockName           = 2,
		kDxfAttributeTag        = 2,
		kDxfSymbolTableName     = 2,
		kDxfMstyleName          = 2,
		kDxfSymTableRecName     = 2,
		kDxfAttributePrompt     = 3,
		kDxfDimStyleName        = 3,
		kDxfLinetypeProse       = 3,
		kDxfTextFontFile        = 3,
		kDxfDescription         = 3,
		kDxfDimPostStr          = 3,
		kDxfTextBigFontFile     = 4,
		kDxfDimAPostStr         = 4,
		kDxfCLShapeName         = 4,
		kDxfSymTableRecComments = 4,
		kDxfHandle              = 5,
		kDxfDimBlk              = 5,
		kDxfDimBlk1             = 6,
		kDxfLinetypeName        = 6,
		kDxfDimBlk2             = 7,
		kDxfTextStyleName       = 7,
		kDxfLayerName           = 8,
		kDxfCLShapeText         = 9,

		kDxfXCoord              = 10,

		kDxfYCoord              = 20,

		kDxfZCoord              = 30,

		kDxfElevation           = 38,
		kDxfThickness           = 39,

		kDxfReal                = 40,
		kDxfViewportHeight      = 40,
		kDxfTxtSize             = 40,
		kDxfTxtStyleXScale      = 41,
		kDxfViewWidth           = 41,
		kDxfViewportAspect      = 41,
		kDxfTxtStylePSize       = 42,
		kDxfViewLensLength      = 42,
		kDxfViewFrontClip       = 43,
		kDxfViewBackClip        = 44,
		kDxfShapeXOffset        = 44,
		kDxfShapeYOffset        = 45,
		kDxfViewHeight          = 45,
		kDxfShapeScale          = 46,
		kDxfPixelScale          = 47,

		kDxfLinetypeScale       = 48,

		kDxfDashLength          = 49,
		kDxfMlineOffset         = 49,
		kDxfLinetypeElement     = 49,

		kDxfAngle               = 50,
		kDxfViewportSnapAngle   = 50,
		kDxfViewportTwist       = 51,

		kDxfVisibility          = 60,
		kDxfViewportGridDisplay = 60,
		kDxfLayerLinetype       = 61,
		kDxfViewportGridMajor   = 61,
		kDxfColor               = 62,

		kDxfHasSubentities      = 66,
		kDxfViewportVisibility  = 67,
		kDxfViewportActive      = 68,
		kDxfViewportNumber      = 69,

		kDxfInt16               = 70,
		kDxfViewMode            = 71,
		kDxfCircleSides         = 72,
		kDxfViewportZoom        = 73,
		kDxfViewportIcon        = 74,
		kDxfViewportSnap        = 75,
		kDxfViewportGrid        = 76,
		kDxfViewportSnapStyle   = 77,
		kDxfViewportSnapPair    = 78,

		kDxfRegAppFlags         = 71,

		kDxfTxtStyleFlags       = 71,
		kDxfLinetypeAlign       = 72,
		kDxfLinetypePDC         = 73,

		kDxfInt32               = 90,

		kDxfSubclass            = 100,
		kDxfEmbeddedObjectStart = 101,
		kDxfControlString       = 102,

		kDxfDimVarHandle        = 105,

		kDxfUCSOrg              = 110,
		kDxfUCSOriX             = 111,
		kDxfUCSOriY             = 112,

		kDxfXReal               = 140,
		kDxfViewBrightness      = 141,
		kDxfViewContrast        = 142,

		kDxfInt64               = 160,
		kDxfXInt16              = 170,

		kDxfNormalX             = 210,
		kDxfNormalY             = 220,
		kDxfNormalZ             = 230,

		kDxfXXInt16             = 270,

		kDxfInt8                = 280,
		kDxfRenderMode          = 281,
		kDxfDefaultLightingType = 282,
		kDxfShadowFlags         = 284,

		kDxfBool                = 290,
		kDxfDefaultLightingOn   = 292,

		kDxfXTextString         = 300,

		kDxfBinaryChunk         = 310,

		kDxfArbHandle           = 320,

		kDxfSoftPointerId       = 330,
		kDxfViewBackgroundId    = 332,
		kDxfShadePlotId         = 333,
		kDxfLiveSectionId       = 334,
		kDxfLiveSectionName     = 309,

		kDxfHardPointerId       = 340,
		kDxfObjVisualStyleId    = 345,
		kDxfVpVisualStyleId     = 346,
		kDxfMaterialId          = 347,
		kDxfVisualStyleId       = 348,
		kDxfDragVisualStyleId   = 349,

		kDxfSoftOwnershipId     = 350,

		kDxfHardOwnershipId     = 360,
		kDxfSunId               = 361,

		kDxfLineWeight          = 370,
		kDxfPlotStyleNameType   = 380,
		kDxfPlotStyleNameId     = 390,
		kDxfXXXInt16            = 400,

		kDxfLayoutName          = 410,

		kDxfColorRGB            = 420,
		kDxfColorName           = 430,

		kDxfAlpha               = 440,

		kDxfGradientObjType     = 450,
		kDxfGradientPatType     = 451,
		kDxfGradientTintType    = 452,
		kDxfGradientColCount    = 453,
		kDxfGradientAngle       = 460,
		kDxfGradientShift       = 461,
		kDxfGradientTintVal     = 462,
		kDxfGradientColVal      = 463,
		kDxfGradientName        = 470,

		kDxfFaceStyleId         = 480,
		kDxfEdgeStyleId         = 481,

		kDxfComment             = 999,

		kDxfXdAsciiString       = 1000,
		kDxfRegAppName          = 1001,
		kDxfXdControlString     = 1002,
		kDxfXdLayerName         = 1003,
		kDxfXdBinaryChunk       = 1004,
		kDxfXdHandle            = 1005,

		kDxfXdXCoord            = 1010,
		kDxfXdYCoord            = 1020,
		kDxfXdZCoord            = 1030,

		kDxfXdWorldXCoord       = 1011,
		kDxfXdWorldYCoord       = 1021,
		kDxfXdWorldZCoord       = 1031,

		kDxfXdWorldXDisp        = 1012,
		kDxfXdWorldYDisp        = 1022,
		kDxfXdWorldZDisp        = 1032,

		kDxfXdWorldXDir         = 1013,
		kDxfXdWorldYDir         = 1023,
		kDxfXdWorldZDir         = 1033,

		kDxfXdReal              = 1040,
		kDxfXdDist              = 1041,
		kDxfXdScale             = 1042,

		kDxfXdInteger16         = 1070,
		kDxfXdInteger32         = 1071
	};

	enum DwgDataType
	{
		kDwgNull            = 0,
		kDwgReal            = 1,
		kDwgInt32           = 2,
		kDwgInt16           = 3,
		kDwgInt8            = 4,
		kDwgText            = 5,
		kDwgBChunk          = 6,
		kDwgHandle          = 7,
		kDwgHardOwnershipId = 8,
		kDwgSoftOwnershipId = 9,
		kDwgHardPointerId   = 10,
		kDwgSoftPointerId   = 11,
		kDwg3Real           = 12,
		kDwgInt64           = 13,
		kDwgNotRecognized   = 19
	};

	enum OsnapMask
	{
		kOsMaskEnd          = 1,
		kOsMaskMid          = 2,
		kOsMaskCen          = 4,
		kOsMaskNode         = 8,
		kOsMaskQuad         = 0x10,
		kOsMaskInt          = 0x20,
		kOsMaskIns          = 0x40,
		kOsMaskPerp         = 0x80,
		kOsMaskTan          = 0x100,
		kOsMaskNear         = 0x200,
		kOsMaskQuick        = 0x400,
		kOsMaskApint        = 0x800,
		kOsMaskImmediate    = 0x10000,
		kOsMaskAllowTan     = 0x20000,
		kOsMaskDisablePerp  = 0x40000,
		kOsMaskRelCartesian = 0x80000,
		kOsMaskRelPolar     = 0x100000,
		kOsMaskNoneOverride = 0x200000
	};

	enum OsnapMode
	{
		kOsModeEnd      = 1,  // Endpoint
		kOsModeMid      = 2,  // Midpoint
		kOsModeCen      = 3,  // Center
		kOsModeNode     = 4,  // Node
		kOsModeQuad     = 5,  // Quadrant
		kOsModeIntersec = 6,  // Intersection
		kOsModeIns      = 7,  // Insertion point
		kOsModePerp     = 8,  // Perpendicular
		kOsModeTan      = 9,  // Tangent
		kOsModeNear     = 10, // Nearest
		kOsModeApint    = 11, // Apparent intersection
		kOsModePar      = 12, // Parallel
		kOsModeStart    = 13  // Startpoint
	};

	enum ShowImagesMode
	{
		kNeverShow       = 0,
		kAlwaysShow      = 1,
		kBoundingBoxShow = 2
	};

	enum SaveImagesMode
	{
		kNeverSave  = 0,
		kAlwaysSave = 1
	};

	enum TextHorzMode
	{
		kTextLeft   = 0,
		kTextCenter = 1,
		kTextRight  = 2,
		kTextAlign  = 3,
		kTextMid    = 4,
		kTextFit    = 5
	};

	enum TextVertMode
	{
		kTextBase    = 0,
		kTextBottom  = 1,
		kTextVertMid = 2,
		kTextTop     = 3
	};

	enum LineSpacingStyle
	{
		kAtLeast = 1,
		kExactly = 2
	};

	enum Planarity
	{
		kNonPlanar = 0,
		kPlanar    = 1,
		kLinear    = 2
	};

	enum PointIndex
	{
		kMPoint1 = 0,
		kMPoint2 = 1,
		kMPoint3 = 2,
		kMPoint4 = 3
	};

	enum EdgeIndex
	{
		kMEdge1 = 0,
		kMEdge2 = 1,
		kMEdge3 = 2,
		kMEdge4 = 3
	};

	enum Poly2dType
	{
		k2dSimplePoly      = 0,
		k2dFitCurvePoly    = 1,
		k2dQuadSplinePoly  = 2,
		k2dCubicSplinePoly = 3
	};

	enum Poly3dType
	{
		k3dSimplePoly      = 0,
		k3dQuadSplinePoly  = 1,
		k3dCubicSplinePoly = 2
	};

	enum PolyMeshType
	{
		kSimpleMesh        = 0,
		kQuadSurfaceMesh   = 5,
		kCubicSurfaceMesh  = 6,
		kBezierSurfaceMesh = 8
	};

	enum Vertex2dType
	{
		k2dVertex          = 0,
		k2dSplineCtlVertex = 1,
		k2dSplineFitVertex = 2,
		k2dCurveFitVertex  = 3
	};

	enum Vertex3dType
	{
		k3dSimpleVertex  = 0,
		k3dControlVertex = 1,
		k3dFitVertex     = 2
	};

	enum SpaceValueType
	{
		kUndefined,
		kStubPtr,
		kEndOfFile,
		kBackwardBranch,
		kForwardBranch,
		kDetour
	};

	enum BoolOperType
	{
		kBoolUnite     = 0,
		kBoolIntersect = 1,
		kBoolSubtract  = 2
	};

	typedef NRX::UInt32  SubentType;

	enum
	{
		kNullSubentType   = 0,
		kFaceSubentType   = 1,
		kEdgeSubentType   = 2,
		kVertexSubentType = 3,
		kMlineSubentCache = 4,
		kClassSubentType  = 5,
		kAxisSubentType = 6
	};

	typedef NRX::UInt32  GeomId;

	enum
	{
		kNoGeom = 0
	};

	enum GeomType
	{
		kInvalidGeom = 0,
		kPointGeom,
		kLineGeom,
		kCircleGeom,
		kPlaneGeom
	};

	enum FilerType
	{
		kFileFiler        = 0,
		kCopyFiler        = 1,
		kUndoFiler        = 2,
		kBagFiler         = 3,
		kIdXlateFiler     = 4,
		kPageFiler        = 5,
		kDeepCloneFiler   = 6,
		kIdFiler          = 7,
		kPurgeFiler       = 8,
		kWblockCloneFiler = 9
	};

	enum FilerSeekType
	{
		kSeekFromStart   = 0,
		kSeekFromCurrent = 1,
		kSeekFromEnd     = 2
	};

	enum NcDbDwgVersion
	{
		kDHL_MC0_0   = 0,
		kDHL_AC1_2   = 1,
		kDHL_AC1_40  = 2,
		kDHL_AC1_50  = 3,
		kDHL_AC2_20  = 4,
		kDHL_AC2_10  = 5,
		kDHL_AC2_21  = 6,
		kDHL_AC2_22  = 7,
		kDHL_1001    = 8,
		kDHL_1002    = 9,
		kDHL_1003    = 10,
		kDHL_1004    = 11,
		kDHL_1005    = 12,
		kDHL_1006    = 13,
		kDHL_1007    = 14,
		kDHL_1008    = 15,
		kDHL_1009    = 16,
		kDHL_1010    = 17,
		kDHL_1011    = 18,
		kDHL_1012    = 19,
		kDHL_1013    = 20,
		kDHL_1014    = 21,
		kDHL_1500    = 22,
		kDHL_1015    = 23,
		kDHL_1800a   = 24,
		kDHL_1800    = 25,
		kDHL_2100a   = 26,
		kDHL_1021    = 27,
		kDHL_2400a   = 28,
		kDHL_1024    = 29,
		kDHL_2700a   = 30,
		kDHL_1027    = 31,
		kDHL_Newest  = kDHL_1027,
		kDHL_CURRENT = kDHL_Newest,
		kDHL_Unknown = 32766,
		kDHL_Max     = 32767
	};


	enum MaintenanceReleaseVersion
	{
		kMRelease0              = 0,
		kMRelease1              = 1,
		kMRelease2              = 2,
		kMRelease3              = 3,
		kMRelease4              = 4,
		kMRelease5              = 5,
		kMRelease6              = 6,
		kMRelease7              = 7,
		kMRelease8              = 8,
		kMRelease9              = 9,
		kMRelease10             = 10,
		kMRelease11             = 11,
		kMRelease12             = 12,
		kMRelease13             = 13,
		kMRelease14             = 14,
		kMRelease15             = 15,
		kMRelease16             = 16,
		kMRelease17             = 17,
		kMRelease18             = 18,
		kMRelease19             = 19,
		kMRelease20             = 20,
		kMRelease21             = 21,
		kMRelease22             = 22,
		kMRelease23             = 23,
		kMRelease24             = 24,
		kMRelease25             = 25,
		kMRelease26             = 26,
		kMRelease27             = 27,
		kMRelease28             = 28,
		kMRelease29             = 29,
		kMRelease30             = 30,
		kMRelease31             = 31,
		kMRelease32             = 32,
		kMRelease33             = 33,
		kMRelease34             = 34,
		kMRelease35             = 35,
		kMRelease36             = 36,
		kMRelease37             = 37,
		kMRelease38             = 38,
		kMRelease39             = 39,
		kMRelease40             = 40,
		kMRelease41             = 41,
		kMReleaseFirstValid1500 = kMRelease41,
		kMRelease42             = 42,
		kMRelease43             = 43,
		kMRelease44             = 44,
		kMRelease45             = 45,
		kMRelease46             = 46,
		kMRelease47             = 47,
		kMRelease48             = 48,
		kMRelease49             = 49,
		kMRelease55             = 55,
		kMRelease56             = 56,
		kMRelease57             = 57,
		kMRelease58             = 58,
		kMRelease59             = 59,
		kMRelease60             = 60,
		kMRelease61             = 61,
		kMRelease62             = 62,
		kMRelease63             = 63,
		kMRelease64             = 64,
		kMRelease65             = 65,
		kMRelease66             = 66,
		kMRelease67             = 67,
		kMRelease68             = 68,
		kMRelease69             = 69,
		kMRelease70             = 70,
		kMRelease71             = 71,
		kMRelease72             = 72,
		kMRelease73             = 73,
		kMRelease74             = 74,
		kMRelease75             = 75,
		kMRelease76             = 76,
		kMRelease100            = 100,
		kMRelease101            = 101,
		kMRelease102            = 102,
		kMRelease103            = 103,
		kMRelease104            = 104,

		kMReleaseNewest         = kMRelease1,
		kMReleaseCurrent        = kMReleaseNewest,
		kMReleaseUnknown        = 126,
		kMReleaseMax            = 127
	};

	enum SaveType
	{
		kNoSave = 0,
		kR12Save,
		kR13Save,
		kR14Save
	};

	enum GroupOperType
	{
		kNoOp     = 0,
		kAdd      = 1,
		kRemove   = 2,
		kRename   = 3,
		kOrdered  = 4,
		kGrpDesc  = 5,
		kSelect   = 6,
		kCreate   = 7,
		kPrepend  = 8,
		kInsert   = 9,
		kGrpFlags = 10
	};

	enum DeepCloneType
	{
		kDcCopy          = 0,
		kDcExplode       = 1,
		kDcBlock         = 2,
		kDcXrefBind      = 3,
		kDcSymTableMerge = 4,
		kDcInsert        = 6,
		kDcWblock        = 7,
		kDcObjects       = 8,
		kDcXrefInsert    = 9,
		kDcInsertCopy    = 10,
		kDcWblkObjects   = 11
	};

	enum DuplicateRecordCloning
	{
		kDrcNotApplicable  = 0,   // Not applicable to the object.
		kDrcIgnore         = 1,   // If a duplicate record exists, use the existing record
		// in the *database*, and ignore the clone.
		kDrcReplace        = 2,   // If a duplicate record exists, replace it with the cloned record.
		kDrcXrefMangleName = 3,   // Incoming record names are mangled with <Xref>$0$<name>
		kDrcMangleName     = 4,   // Incoming record names are mangled with $0$<name>
		kDrcUnmangleName   = 5,   // Unmangle the names mangled by kDrcMangleName, then default to kDrcIgnore.
		// Typically used by RefEdit when checking records into the original *database*.  
		kDrcMax            = kDrcUnmangleName //  The maximum value of this enum.
	};

	enum XrefStatus
	{
		kXrfNotAnXref    = 0,
		kXrfResolved     = 1,
		kXrfUnloaded     = 2,
		kXrfUnreferenced = 3,
		kXrfFileNotFound = 4,
		kXrfUnresolved   = 5
	};

	enum XrefNotificationStatus
	{
		kXrfNotifyNone                    = 0,
		kXrfNotifyResolvedMatch           = 1,
		kXrfNotifyResolvedElsewhere       = 2,
		kXrfNotifyResolvedWithUpdate      = 3,
		kXrfNotifyResolvedUpdateAvailable = 4
	};

	enum MeasurementValue
	{
		kEnglish = 0,
		kMetric  = 1,
	};

	enum UnitsValue
	{
		kUnitsUndefined    = 0,
		kUnitsInches       = 1,
		kUnitsFeet         = 2,
		kUnitsMiles        = 3,
		kUnitsMillimeters  = 4,
		kUnitsCentimeters  = 5,
		kUnitsMeters       = 6,
		kUnitsKilometers   = 7,
		kUnitsMicroinches  = 8,
		kUnitsMils         = 9,
		kUnitsYards        = 10,
		kUnitsAngstroms    = 11,
		kUnitsNanometers   = 12,
		kUnitsMicrons      = 13,
		kUnitsDecimeters   = 14,
		kUnitsDekameters   = 15,
		kUnitsHectometers  = 16,
		kUnitsGigameters   = 17,
		kUnitsAstronomical = 18,
		kUnitsLightYears   = 19,
		kUnitsParsecs      = 20,
		kUnitsMax          = kUnitsParsecs
	};

	enum TimeZone
	{
		kInternationalDateLine = -12000,
		kMidwayIsland          = -11000,
		kHawaii                = -10000,
		kAlaska                = -9000,
		kPacific               = -8000,
		kMountain              = -7000,
		kArizona               = -7001,
		kMazatlan              = -7002,
		kCentral               = -6000,
		kCentralAmerica        = -6001,
		kMexicoCity            = -6002,
		kSaskatchewan          = -6003,
		kEastern               = -5000,
		kIndiana               = -5001,
		kBogota                = -5002,
		kAtlanticCanada        = -4000,
		kCaracas               = -4001,
		kSantiago              = -4002,
		kNewfoundland          = -3300,
		kBrasilia              = -3000,
		kBuenosAires           = -3001,
		kGreenland             = -3002,
		kMidAtlantic           = -2000,
		kAzores                = -1000,
		kCapeVerde             = -1001,
		kUTC                   = 0,
		kGMT                   = 1,
		kMonrovia              = 2,
		kBerlin                = 1000,
		kParis                 = 1001,
		kPrague                = 1002,
		kSarajevo              = 1003,
		kWestCentralAfrica     = 1004,
		kAthens                = 2000,
		kEasternEurope         = 2001,
		kCairo                 = 2002,
		kHarare                = 2003,
		kHelsinki              = 2004,
		kJerusalem             = 2005,
		kMoscow                = 3000,
		kRiyadh                = 3001,
		kBaghdad               = 3002,
		kEastAfrica            = 3003,
		kTehran                = 3300,
		kAbuDhabi              = 4000,
		kCaucasus              = 4001,
		kKabul                 = 4300,
		kEkaterinburg          = 5000,
		kIslamabad             = 5001,
		kKolkata               = 5300,
		kKathmandu             = 5450,
		kAlmaty                = 6000,
		kDhaka                 = 6001,
		kSriLanka              = 6002,
		kRangoon               = 6300,
		kBangkok               = 7000,
		kKrasnoyarsk           = 7001,
		kBeijing               = 8000,
		kSingapore             = 8001,
		kTaipei                = 8002,
		kIrkutsk               = 8003,
		kPerth                 = 8004,
		kTokyo                 = 9000,
		kSeoul                 = 9001,
		kYakutsk               = 9002,
		kAdelaide              = 9300,
		kDarwin                = 9301,
		kSydney                = 10000,
		kGuam                  = 10001,
		kBrisbane              = 10002,
		kHobart                = 10003,
		kVladivostock          = 10004,
		kMagadan               = 11000,
		kWellington            = 12000,
		kFiji                  = 12001,
		kTonga                 = 13000,
	};

	enum LineWeight
	{
		kLnWt000          =   0,
		kLnWt005          =   5,
		kLnWt009          =   9,
		kLnWt013          =  13,
		kLnWt015          =  15,
		kLnWt018          =  18,
		kLnWt020          =  20,
		kLnWt025          =  25,
		kLnWt030          =  30,
		kLnWt035          =  35,
		kLnWt040          =  40,
		kLnWt050          =  50,
		kLnWt053          =  53,
		kLnWt060          =  60,
		kLnWt070          =  70,
		kLnWt080          =  80,
		kLnWt090          =  90,
		kLnWt100          = 100,
		kLnWt106          = 106,
		kLnWt120          = 120,
		kLnWt140          = 140,
		kLnWt158          = 158,
		kLnWt200          = 200,
		kLnWt211          = 211,
		kLnWtByLayer      =  -1,
		kLnWtByBlock      =  -2,
		kLnWtByLwDefault  =  -3
	};

	enum EndCaps
	{
		kEndCapNone   = 0,
		kEndCapRound  = 1,
		kEndCapAngle  = 2,
		kEndCapSquare = 3
	};

	enum JoinStyle
	{
		kJnStylNone  = 0,
		kJnStylRound = 1,
		kJnStylAngle = 2,
		kJnStylFlat  = 3
	};

	enum PlotStyleNameType
	{
		kPlotStyleNameByLayer       = 0,
		kPlotStyleNameByBlock       = 1,
		kPlotStyleNameIsDictDefault = 2,
		kPlotStyleNameById          = 3
	};

	enum DimArrowFlags
	{
		kFirstArrow  = 0, // First arrowhead
		kSecondArrow = 1  // Second arrowhead
	};

	enum DimblkFlags
	{
		kDimblk = 0,
		kDimblk1,
		kDimblk2,
		kDimLdrBlk
	};

	enum OrthographicView
	{
		kNonOrthoView = 0,
		kTopView      = 1,
		kBottomView   = 2,
		kFrontView    = 3,
		kBackView     = 4,
		kLeftView     = 5,
		kRightView    = 6
	};

	enum VpFreezeOps
	{
		kFreeze = 0,
		kThaw,
		kReset
	};

	enum reservedStringEnumType
	{
		kByLayer       = 0,
		kByBlock       = 1,
		kNone          = 2,
		kContinuous    = 3,
		kStandard      = 4,
		kNormal        = 5,
		kDefPoints     = 6,
		kDefault       = 7,
		kMissing       = 8,
		kByColor       = 9,
		kModel         = 10,
		kGlobal        = 11,
		kVS2DWireframe = 12,
		kVS3DWireframe = 13,
		kVS3DHidden    = 14,
		kVSRealistic   = 15,
		kVSConceptual  = 16,
		kReservedStringCount
	};

	enum SortEntsFlags
	{
		kSortEntsSelection = 0x01,
		kSortEntsOsnap     = 0x02,
		kSortEntsRedraw    = 0x04,
		kSortEntsSlide     = 0x08,
		kSortEntsRegen     = 0x10,
		kSortEntsPlot      = 0x20,
		kSortEntsPsout     = 0x40
	};

	enum DragStat
	{
		kDragStart = 0,
		kDragEnd   = 1,
		kDragAbort = 2
	};


	enum GripStat
	{
		kGripsDone          = 0,
		kGripsToBeDeleted   = 1,
		kDimDataToBeDeleted = 2
	};

	enum DataLinkOption
	{
		kDataLinkOptionNone         = 0,
		kDataLinkOptionAnonymous    = 0x1,
		kDataLinkOptionPersistCache = 0x2,
		kDataLinkOptionDisableInLT  = 0x4,
		kDataLinkHasCutomData       = 0x8,
	};

	enum PathOption
	{
		kNoPath       = 1,
		kRelativePath = 2,
		kAbsolutePath = 3,
		kPathAndFile  = 4,
	};

	enum UpdateDirection
	{
		kUpdateDirSourceToData = 0x1,
		kUpdateDirDataToSource = 0x2,
	};

	enum UpdateOption
	{
		kUpdateOptionNone                                = 0,
		kUpdateOptionSkipFormat                          = 0x20000,
		kUpdateOptionUpdateRowHeight                     = 0x40000,
		kUpdateOptionUpdateColumnWidth                   = 0x80000,
		kUpdateOptionAllowSourceUpdate                   = 0x100000,
		kUpdateOptionForceFullSourceUpdate               = 0x200000,
		kUpdateOptionOverwriteContentModifiedAfterUpdate = 0x400000,
		kUpdateOptionOverwriteFormatModifiedAfterUpdate  = 0x800000,
		kUpdateOptionForPreview                          = 0x1000000,
		kUpdateOptionIncludeXrefs                        = 0x2000000,
		kSkipFormatAfterFirstUpdate                      = 0x4000000,
	};

	enum DataLinkGetSourceContext
	{
		kDataLinkGetSourceContextUnknown     = 0,
		kDataLinkGetSourceContextEtransmit   = 1,
		kDataLinkGetSourceContextXrefManager = 2,
		kDataLinkGetSourceContextFileWatcher = 3,
		kDataLinkGetSourceContextOther       = 4,
		kDataLinkGetSourceContextOrignalPath = (0x1 << 8),
	};

	enum CellType
	{
		kUnknownCell = 0,
		kTextCell    = 1,
		kBlockCell   = 2
	};

	enum CellContentType
	{
		kCellContentTypeUnknown = 0,
		kCellContentTypeValue   = 0x1,
		kCellContentTypeField   = 0x2,
		kCellContentTypeBlock   = 0x4,
	};

	enum CellEdgeMask
	{
		kTopMask    = 1,
		kRightMask  = 2,
		kBottomMask = 4,
		kLeftMask   = 8
	};

	enum CellMargin
	{
		kCellMarginTop         = 0x1,
		kCellMarginLeft        = 0x2,
		kCellMarginBottom      = 0x4,
		kCellMarginRight       = 0x8,
		kCellMarginHorzSpacing = 0x10,
		kCellMarginVertSpacing = 0x20
	};

	enum CellClass {
		kCellClassNone = 0,
		kCellClassLabel = 0x1,
		kCellClassData = 0x2
	};

	enum CellContentLayout
	{
		kCellContentLayoutFlow              = 0x1,
		kCellContentLayoutStackedHorizontal = 0x2,
		kCellContentLayoutStackedVertical   = 0x4,
	};

	enum CellState
	{
		kCellStateNone                       = 0,
		kCellStateContentLocked              = 0x1,
		kCellStateContentReadOnly            = 0x2,
		kCellStateLinked                     = 0x4,
		kCellStateContentModifiedAfterUpdate = 0x8,
		kCellStateFormatLocked               = 0x10,
		kCellStateFormatReadOnly             = 0x20,
		kCellStateFormatModifiedAfterUpdate  = 0x40,
		kAllCellStates                       = kCellStateContentLocked | kCellStateContentReadOnly | kCellStateLinked |
		kCellStateContentModifiedAfterUpdate | kCellStateFormatLocked |
		kCellStateFormatReadOnly | kCellStateFormatModifiedAfterUpdate,
	};

	enum CellProperty
	{
		kCellPropInvalid           = 0,
		kCellPropDataType          = 0x1,
		kCellPropDataFormat        = 0x2,
		kCellPropRotation          = 0x4,
		kCellPropScale             = 0x8,
		kCellPropAlignment         = 0x10,
		kCellPropContentColor      = 0x20,
		kCellPropTextStyle         = 0x40,
		kCellPropTextHeight        = 0x80,
		kCellPropAutoScale         = 0x100,
		kCellPropBackgroundColor   = 0x200,
		kCellPropMarginLeft        = 0x400,
		kCellPropMarginTop         = 0x800,
		kCellPropMarginRight       = 0x1000,
		kCellPropMarginBottom      = 0x2000,
		kCellPropMarginHorzSpacing = 0x20000,
		kCellPropMarginVertSpacing = 0x40000,
		kCellPropContentLayout     = 0x4000,
		kCellPropMergeAll          = 0x8000,
		kCellPropFlowDirBtoT       = 0x10000,
		kCellPropDataTypeAndFormat = (kCellPropDataType | kCellPropDataFormat),
		kCellPropContent           = (kCellPropDataType | kCellPropDataFormat | kCellPropRotation | kCellPropScale |
		kCellPropContentColor | kCellPropTextStyle | kCellPropTextHeight |
		kCellPropAutoScale),
		kCellPropBitProperties     = (kCellPropAutoScale | kCellPropMergeAll | kCellPropFlowDirBtoT),
		kCellPropAll               = (kCellPropDataType | kCellPropDataFormat | kCellPropRotation | kCellPropScale |
		kCellPropAlignment | kCellPropContentColor | kCellPropBackgroundColor |
		kCellPropTextStyle | kCellPropTextHeight | kCellPropMarginLeft |
		kCellPropMarginTop | kCellPropMarginRight | kCellPropMarginBottom |
		kCellPropMarginHorzSpacing | kCellPropMarginVertSpacing | kCellPropAutoScale |
		kCellPropMergeAll | kCellPropFlowDirBtoT | kCellPropContentLayout),
	};

	enum GridProperty
	{
		kGridPropInvalid           = 0,
		kGridPropLineStyle         = 0x1,
		kGridPropLineWeight        = 0x2,
		kGridPropLinetype          = 0x4,
		kGridPropColor             = 0x8,
		kGridPropVisibility        = 0x10,
		kGridPropDoubleLineSpacing = 0x20,
		kGridPropAll               = (kGridPropLineStyle | kGridPropLineWeight | kGridPropLinetype | kGridPropColor |
		kGridPropVisibility | kGridPropDoubleLineSpacing),
	};

	enum GridLineStyle
	{
		kGridLineStyleSingle = 1,
		kGridLineStyleDouble = 2,
	};

	enum CellOption
	{
		kCellOptionNone    = 0,
		kInheritCellFormat = 0x1,
	};

	enum SelectType
	{
		kWindow   = 1,
		kCrossing = 2
	};

	enum FlowDirection
	{
		kTtoB = 0,
		kBtoT = 1
	};

	enum RotationAngle
	{
		kDegreesUnknown = -1,
		kDegrees000     = 0,
		kDegrees090     = 1,
		kDegrees180     = 2,
		kDegrees270     = 3
	};

	enum CellAlignment
	{
		kTopLeft      = 1,
		kTopCenter    = 2,
		kTopRight     = 3,
		kMiddleLeft   = 4,
		kMiddleCenter = 5,
		kMiddleRight  = 6,
		kBottomLeft   = 7,
		kBottomCenter = 8,
		kBottomRight  = 9
	};

	enum GridLineType
	{
		kInvalidGridLine    = 0,
		kHorzTop            = 1,
		kHorzInside         = 2,
		kHorzBottom         = 4,
		kVertLeft           = 8,
		kVertInside         = 0x10,
		kVertRight          = 0x20,
		kHorzGridLineTypes  = kHorzTop | kHorzBottom | kHorzInside,
		kVertGridLineTypes  = kVertLeft | kVertRight | kVertInside,
		kOuterGridLineTypes = kHorzTop | kHorzBottom | kVertLeft | kVertRight,
		kInnerGridLineTypes = kHorzInside | kVertInside,
		kAllGridLineTypes   = kOuterGridLineTypes | kInnerGridLineTypes
	};

	enum RowType
	{
		kUnknownRow = 0,
		kDataRow    = 1,
		kTitleRow   = 2,
		kHeaderRow  = 4
	};

	enum TableStyleFlags
	{
		kHorzInsideLineFirst        = 0x1,
		kHorzInsideLineSecond       = 0x2,
		kHorzInsideLineThird        = 0x4,kTableStyleModified         = 0x8,
		kTableStyleDataTypeModified = 0x10,
	};

	enum TableBreakOption
	{
		kTableBreakNone                 = 0,
		kTableBreakEnableBreaking       = 0x1,
		kTableBreakRepeatTopLabels      = 0x2,
		kTableBreakRepeatBottomLabels   = 0x4,
		kTableBreakAllowManualPositions = 0x8,
		kTableBreakAllowManualHeights   = 0x10,
	};

	enum TableBreakFlowDirection
	{
		kTableBreakFlowRight    = 0x1,
		kTableBreakFlowDownOrUp = 0x2,
		kTableBreakFlowLeft     = 0x4,
	};

	enum TableFillOption
	{
		kTableFillNone                     = 0,
		kTableFillRow                      = 0x1,
		kTableFillReverse                  = 0x2,
		kTableFillGenerateSeries           = 0x4,
		kTableFillCopyContent              = 0x8,
		kTableFillCopyFormat               = 0x10,
		kTableFillOverwriteReadOnlyContent = 0x20,
		kTableFillOverwriteReadOnlyFormat  = 0x40,
	};

	enum TableCopyOption
	{
		kTableCopyNone                                = 0,
		kTableCopyExpandOrContractTable               = 0x1,
		kTableCopySkipContent                         = 0x2,
		kTableCopySkipValue                           = 0x4,
		kTableCopySkipField                           = 0x8,
		kTableCopySkipFormula                         = 0x10,
		kTableCopySkipBlock                           = 0x20,
		kTableCopySkipDataLink                        = 0x40,
		kTableCopySkipLabelCell                       = 0x80,
		kTableCopySkipDataCell                        = 0x100,
		kTableCopySkipFormat                          = 0x200,
		kTableCopySkipCellStyle                       = 0x400,
		kTableCopyConvertFormatToOverrides            = 0x800,
		kTableCopySkipCellState                       = 0x1000,
		kTableCopySkipContentFormat                   = 0x2000,
		kTableCopySkipDissimilarContentFormat         = 0x4000,
		kTableCopySkipGeometry                        = 0x8000,
		kTableCopySkipMerges                          = 0x10000,
		kTableCopyFillTarget                          = 0x20000,
		kTableCopyOverwriteReadOnlyContent            = 0x40000,
		kTableCopyOverwriteReadOnlyFormat             = 0x80000,
		kTableCopyOverwriteContentModifiedAfterUpdate = 0x100000,
		kTableCopyOverwriteFormatModifiedAfterUpdate  = 0x200000,
		kTableCopyOnlyContentModifiedAfterUpdate      = 0x400000,
		kTableCopyOnlyFormatModifiedAfterUpdate       = 0x800000,
		kTableCopyRowHeight                           = 0x1000000,
		kTableCopyColumnWidth                         = 0x2000000,
		kTableCopyFullCellState                       = 0x4000000,
		kTableCopyForRountrip                         = 0x8000000,
		kTableCopyConvertFieldToValue                 = 0x10000000,
		kTableCopySkipFieldTranslation                = 0x20000000,
	};

	enum TableIteratorOption
	{
		kTableIteratorNone                = 0,
		kTableIteratorIterateSelection    = 0x1,
		kTableIteratorIterateRows         = 0x2,
		kTableIteratorIterateColumns      = 0x4,
		kTableIteratorIterateDataLinks    = 0x80,
		kTableIteratorReverseOrder        = 0x8,
		kTableIteratorSkipReadOnlyContent = 0x10,
		kTableIteratorSkipReadOnlyFormat  = 0x20,
		kTableIteratorSkipMerged          = 0x40,
	};

	enum MergeCellStyleOption
	{
		kMergeCellStyleNone                         = 0,
		kMergeCellStyleCopyDuplicates               = 0x1,
		kMergeCellStyleOverwriteDuplicates          = 0x2,
		kMergeCellStyleConvertDuplicatesToOverrides = 0x4,
		kMergeCellStyleIgnoreNewStyles              = 0x8,
	};

	enum TableHitItem
	{
		kTableHitNone            = 0,
		kTableHitCell            = 0x1,
		kTableHitRowIndicator    = 0x2,
		kTableHitColumnIndicator = 0x4,
		kTableHitGridLine        = 0x8,
	};

	enum RowTypes
	{
		kAllRows = kDataRow | kTitleRow | kHeaderRow
	};

	enum GridLineTypes
	{
		kAllGridLines = kHorzTop | kHorzInside | kHorzBottom | kVertLeft | kVertInside | kVertRight
	};

	enum DrawOrderFlags
	{
		kDrawOrderInPlaceEditOn = 0x01,
		kDrawOrderInheritanceOn = 0x02
	};

	enum UpdateThumbnailFlags
	{
		kUpdateModelViews   = 0x01,
		kUpdateSheetViews   = 0x02,
		kUpdateSheets       = 0x04,
		kUpdateWhenAccessed = 0x08,
		kUpdateWhenSaving   = 0x10
	};

	enum EnhancedBlockEvalType
	{
		kInitialization = 1,
		kForUpdate      = 2,
		kForRefresh     = 3
	};

	enum SliceModelType
	{
		kKeepBothSides   = 0x01,
		kUseCurrentColor = 0x02
	};

	enum CollisionType
	{
		kCollisionTypeNone  = 0,
		kCollisionTypeSolid = 1
	};

	enum LoftParamType
	{
		kLoftNoParam        = 0x00,
		kLoftNoTwist        = 0x01,
		kLoftAlignDirection = 0x02,
		kLoftSimplify       = 0x04,
		kLoftClose          = 0x08,
		kLoftDefault        = kLoftNoTwist | kLoftAlignDirection | kLoftSimplify
	};

	enum LoftNormalsType
	{
		kLoftRuled          = 0,
		kLoftSmooth         = 1,
		kLoftFirstNormal    = 2,
		kLoftLastNormal     = 3,
		kLoftEndsNormal     = 4,
		kLoftAllNormal      = 5,
		kLoftUseDraftAngles = 6
	};

	enum ShadowFlags
	{
		kShadowsCastAndReceive = 0x00,
		kShadowsDoesNotReceive = 0x01,
		kShadowsDoesNotCast    = 0x02,
		kShadowsIgnore         = kShadowsDoesNotCast | kShadowsDoesNotReceive
	};

	enum LightingUnits
	{
		kLightingUnitsGeneric = 0,
		kLightingUnitsAmerican = 1,
		kLightingUnitsInternational = 2
	};

	enum IndexCreation {
		kNoIndex = 0,
		kIndexByLayer = 1,
		kIndexSpatially = 2
	};

	enum LayerEvaluation {
		kNoNewLayerEvaluation = 0,
		kEvalNewXrefLayers = 1,
		kEvalAllNewLayers = 2
	};

	enum NewLayerNotification {
		kNoNewLayerNotification = 0,
		kNotifyOnPlot = 1,
		kNotifyOnOpen = 2,
		kNotifyOnXrefAttachAndReload = 4,
		kNotifyOnLayerStateRestore = 8,
		kNotifyOnSave = 16,
		kNotifyOnInsert = 32
	};

	enum FilletTrimMode {
		kTrimNone      = 0,
		kTrimFirst     = 1,
		kTrimSecond    = 2,
		kTrimBoth      = 3
	};

}; // struct NcDb

const NcDb::OpenMode kForRead   = NcDb::kForRead;
const NcDb::OpenMode kForWrite  = NcDb::kForWrite;
const NcDb::OpenMode kForNotify = NcDb::kForNotify;

struct NcadApp
{
	enum LoadReasons
	{
		kOnProxyDetection       = 0x01,
		kOnAutoCADStartup       = 0x02,
		kOnCommandInvocation    = 0x04,
		kOnLoadRequest          = 0x08,
		kLoadDisabled           = 0x10,
		kTransparentlyLoadable  = 0x20
	};

	enum ErrorStatus
	{
		eOk              = 0,
		eInvalidKey      = 1,
		eInvalidSubKey   = 2,
		eKeyNotFound     = 3,
		eOutOfMemory     = 4,
		eInvalidValue    = 5,
		eValueNotFound   = 6,
		eKeyExists       = 7,
		eRegAccessDenied = 8,
		eRejected        = 9,
		eUnknownError    = 10
	};
};

typedef enum
{
	kNcGiFillAlways = 1,  // Always fill closed graphic primitives.
	kNcGiFillNever  = 2   // Never fill closed graphic primitives.
} NcGiFillType;

typedef enum
{
	kNcGiInvisible = 0,
	kNcGiVisible,
	kNcGiSilhouette
} NcGiVisibility;

typedef enum
{
	eNcGiRegenTypeInvalid         = 0,  // Invalid regen type. 
	kNcGiStandardDisplay          = 2,  // Regenerating for 2D wireframe display. 
	kNcGiHideOrShadeCommand       = 3,  // Regenerating for legacy hide or shade commands. 
	kNcGiRenderCommand            = 4,  // Regenerating for rendered display.
	kNcGiForExplode               = 5,  // Regenerating for explode.  
	kNcGiSaveWorldDrawForProxy    = 6,  // Regenerating for proxy. 
	kNcGiShadedDisplay            = kNcGiRenderCommand,
	kNcGiForExtents               = 7   // Regenerating for extents. 
} NcGiRegenType;

// No longer supported and will be removed
//
#define kNcGiSaveWorldDrawForR12 kNcGiForExplode

typedef enum
{
	kNcGiArcSimple = 0,
	kNcGiArcSector,
	kNcGiArcChord
} NcGiArcType;

typedef enum
{
	kNcGiCounterClockwise = -1,
	kNcGiNoOrientation    = 0,
	kNcGiClockwise        = 1
} NcGiOrientationType;

typedef enum
{
	kNcGiMaxDevForCircle      = 0,  // Set maximum deviation for circles.
	kNcGiMaxDevForCurve       = 1,  // Set maximum deviation for curves.
	kNcGiMaxDevForBoundary    = 2,  // Set maximum deviation for boundaries.
	kNcGiMaxDevForIsoline     = 3,  // Set maximum deviation for isolines.
	kNcGiMaxDevForFacet       = 4   // Set maximum deviation for facets.
} NcGiDeviationType;

typedef enum
{
	kNcGiBitonal,
	kNcGiPalette,
	kNcGiGray,
	kNcGiRGBA,
	kNcGiBGRA,
	kNcGiARGB,
	kNcGiABGR,
	kNcGiBGR,
	kNcGiRGB
} NcGiImageOrg;

typedef enum
{
	kNcGiXLeftToRightTopFirst,
	kNcGiXLeftToRightBottomFirst,
	kNcGiXRightToLeftTopFirst,
	kNcGiXRightToLeftBottomFirst,
	kNcGiYTopToBottomLeftFirst,
	kNcGiYTopToBottomRightFirst,
	kNcGiYBottomToTopLeftFirst,
	kNcGiYBottomToTopRightFirst
} NcGiImageOrient;

typedef enum
{
	kDefaultScaleFilter,
	kNearestScaleFilter,
	kBellScaleFilter,
	kMitchellScaleFilter,
	kTriangleScaleFilter,
	kCubicScaleFilter,
	kBsplineScaleFilter,
	kLanczos3ScaleFilter
} NcGiScaleFilterType;

typedef enum
{
	kDefaultRotationFilter,
	kInterpolatedRotationFilter,
	kNearestRotationFilter,
} NcGiRotationFilterType;

typedef enum
{
	kDefaultScale,
	kRelativeScale,
	kUnTransformedScale
} NcGiScaleType;

enum NcGiEdgeStyleMaskValues
{
	kNcGiNoEdgeStyleMask = 0,
	kNcGiJitterMask      = 1,
	kNcGiOverhangMask    = 2,
	kNcGiEdgeColorMask   = 4
};

typedef unsigned int  NcGiEdgeStyleMask;

//namespace NcCm moved to hostTypes

enum
{
	RSG_NONULL     = 0x01,
	RSG_NOZERO     = 0x02,
	RSG_NONEG      = 0x04,
	RSG_NOLIM      = 0x08,
	RSG_GETZ       = 0x10,
	RSG_DASH       = 0x20,
	RSG_2D         = 0x40,
	RSG_OTHER      = 0x80,
	RSG_DDISTFIRST = 0x100,
        RSG_TRACKUCS   = 0x0200,
        RSG_NOORTHOZ   = 0x0400,
        RSG_NOOSNAP    = 0x0800,
        RSG_NODDIST    = 0x1000,

};

//enum moved to hostTypes
//	INP_NNULL   = RSG_NONULL,


//typedef enum moved to hostTypes
//	kNdUiNotify_Nothing,

//typedef enum moved to hostTypes
//	kNdUiReply_Nothing,

//typedef enum moved to hostTypes
//	kNdUiCommand_Cancelled = -1,

//enum NcEdDrawOrderCmdType moved to hostTypes

//enum NcadContextMenuMode moved to hostTypes

//enum xrefSubcommandActivities moved to hostTypes

//enum undoSubcommandActivities moved to hostTypes


namespace NcDbGripOperations
{
	enum ReturnValue
	{
		eOk = 0,
		eFailure = 314,//eGripOpFailure,
		eNoRedrawGrip = 315,//eGripOpNoRedrawGrip,
		eGripHotToWarm = 316,//eGripOpGripHotToWarm,
		eGetNewGripPoints = 317//eGripOpGetNewGripPoints
	};

	enum DrawType
	{
		kWarmGrip = 0,
		kHoverGrip,
		kHotGrip,
		kDragImageGrip
	};

	enum GripStatus
	{
		kGripStart = 0,
		kGripEnd,
		kGripAbort,
		kStretch,
		kMove,
		kRotate,
		kScale,
		kMirror,
		kDimFocusChanged,
		kPopUpMenu
	};

	enum GripFlags
	{
		kSkipWhenShared           = 0x1,
		kDisableRubberBandLine    = 0x2,
		kDisableModeKeywords      = 0x4,
		kDrawAtDragImageGripPoint = 0x8,
		kTriggerGrip              = 0x10,
		kTurnOnForcedPick         = 0x20,
		kMapGripHotToRtClk        = 0x40,
		kGizmosEnabled            = 0x80
	};

	enum GripContextFlags
	{
		kSharedGrip   = 0x1,
		kMultiHotGrip = 0x2
	};

	enum GetGripPointsFlags
	{
		kGripPointsOnly    = 0x1,
		kCyclableGripsOnly = 0x02,
		kDynamicDimMode    = 0x04
	};

	enum MoveGripPointsFlags
	{
		kOsnapped = 0x1,
		kPolar    = 0x2,
		kOtrack   = 0x4,
		kZdir     = 0x8,
		kKeyboard = 0x10
	};
};

typedef unsigned long  NcDbEvalNodeId;

typedef double         nds_real;
typedef nds_real       nds_point[3];
typedef LONG_PTR       nds_name[2];
typedef nds_real       nds_matrix[4][4];

#define ncdbNameClear(v)       v[0] = v[1] = 0
#define ncdbNameNil(v)         (v[0] == 0 && v[1] == 0)
#define ncdbNameEqual(v1, v2)  (v1[0] == v2[0] && v1[1] == v2[1])
#define ncdbNameSet(from, to)  ((to)[0] = (from)[0], (to)[1] = (from)[1])

struct nds_binary
{
	short clen;
	char* buf;
};

union nds_u_val
{
	nds_real          rreal;
	nds_real          rpoint[3];
	short             rint;
	LPTSTR            rstring;
	long              rlong;
#ifndef _WIN64
	long              rlname[2];
	long              mnLongPtr;
#else
	__int64           rlname[2];
	__int64           mnLongPtr;
#endif

	__int64           mnInt64;
	struct nds_binary rbinary;
};

typedef void *nds_hdlg;
typedef void *nds_htile;

////////////////////////////////////////////////////////////////////////////////////////////////////
// resbuf
struct NRXDBGATE_EXPORT resbuf
{
	resbuf();

	struct resbuf*  rbnext;
	short           restype;
	union nds_u_val resval;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// resbuf
typedef struct resbuf* pResbuf;

#define RSRSLT            1
#define RSERR             3

#define RTNONE            5000
#define RTREAL            5001
#define RTPOINT           5002
#define RTSHORT           5003
#define RTANG             5004
#define RTSTR             5005
#define RTENAME           5006
#define RTPICKS           5007
#define RTORINT           5008
#define RT3DPOINT         5009
#define RTLONG            5010
#define RTVOID            5014
#define RTLB              5016
#define RTLE              5017
#define RTDOTE            5018
#define RTNIL             5019
#define RTDXF0            5020
#define RTT               5021
#define RTRESBUF          5023
#define RTMODELESS        5027

#define RTNORM            5100

#define RTERROR           (-5001)
#define RTCAN             (-5002)
#define RTREJ             (-5003)
#define RTFAIL            (-5004)
#define RTKWORD           (-5005)
#define RTINPUTTRUNCATED  (-5008)


#define  OL_GOOD        0
#define  OL_ESNVALID    1
#define  OL_ENAMEVALID  2
#define  OL_ESSMAX      3
#define  OL_ESSVALID    4
#define  OL_EBDEVALID   5
#define  OL_EXDEVALID   6
#define  OL_ENTSELPICK  7
#define  OL_EEOEF       8
#define  OL_EEOBD       9
#define  OL_EEMPDB      10
#define  OL_EDELVPORT   11
#define  OL_EACQPLINE   12
#define  OL_EHANDLE     13
#define  OL_ENOHAND     14
#define  OL_ETRANS      15
#define  OL_EXSPACE     16
#define  OL_EDELENT     17
#define  OL_ETBLNAME    18
#define  OL_ETBLARG     19
#define  OL_ERDONLY     20
#define  OL_ENONZERO    21
#define  OL_ERANGE      22
#define  OL_ERGBUSY     23
#define  OL_EMMTYPE     24
#define  OL_EMMLAY      25
#define  OL_EMMLT       26
#define  OL_EMMCOLOR    27
#define  OL_EMMSTYLE    28
#define  OL_EMMSHAPE    29
#define  OL_EMMFTYPE    30
#define  OL_EMODDEL     31
#define  OL_EMODSEQ     32
#define  OL_EMODHAND    33
#define  OL_EMODVPVIS   34
#define  OL_EMMLL       35
#define  OL_EMKTYPE     36
#define  OL_EMKPLINE    37
#define  OL_EMKCMPLX    38
#define  OL_EMKBNAME    39
#define  OL_EMKBFLAG    40
#define  OL_EMKDBNAME   41
#define  OL_EMKNORM     42
#define  OL_EMKNOBNM    43
#define  OL_EMKNOBFLG   44
#define  OL_EMKANON     45
#define  OL_EMKBLOCK    46
#define  OL_EMKMANDF    47
#define  OL_EMMXDTYPE   48
#define  OL_EMMXDNEST   49
#define  OL_EMMXDAPPID  50
#define  OL_EMMXDSIZE   51
#define  OL_ENTSELNULL  52
#define  OL_EMXDAPPID   53
#define  OL_EMMVPORT    54
#define  OL_INVEXT      55
#define  OL_EFLTR1      56
#define  OL_EFLTR2      57
#define  OL_EFLTR3      58
#define  OL_EFLTR4      59
#define  OL_EFLTR5      60
#define  OL_EFLTR6      61
#define  OL_EFLTR7      62
#define  OL_EFLTR8      63
#define  OL_EFLTR9      64
#define  OL_EFLTR10     65
#define  OL_EFLTR11     66
#define  OL_EFLTR12     67
#define  OL_TABNOT      68
#define  OL_TABNOCAL    69
#define  OL_TABERR      70
#define  OL_ENEWRB      71
#define  OL_ENULLPTR    72
#define  OL_EOPEN       73
#define  OL_ELOADED     74
#define  OL_EMAXAPP     75
#define  OL_EEXEC       76
#define  OL_EVERSION    77
#define  OL_EDENIED     78
#define  OL_EREFUSE     79
#define  OL_ENOTLOADED  80
#define  OL_ENOMEM      81
#define  OL_EXFMVALID   82
#define  OL_ESYMNAM     83
#define  OL_ESYMVAL     84
#define  OL_NONDIALOG   85
#define  OL_ECMDINP     92
#define  OL_EBADTYPE    93
#define  OL_EBADVPID    94
#define  OL_EBADVIEW    95
#define  OL_EGCODE      96
#define  OL_EGDUP       97
#define  OL_EBADSSMOD   98
#define  OL_EARGMATCH   99
#define  OL_SVRECURSE   100
#define  OL_MODOPEN     101
#define  OL_NOTENTITY   102
#define  OL_BADPLMOD    103
#define  OL_BADCTLSTR   104
#define  OL_EXDICT_PR   105
#define  MAX_OL_ERRNO   105


#define MSTYLE_NAME_LENGTH         32
#define MSTYLE_DESCRIPTION_LENGTH  256
#define LTYPE_LENGTH               32
#define MLINE_MAX_ELEMENTS         16


#define MSTYLE_DXF_FILL_ON           (0x1)
#define MSTYLE_DXF_SHOW_MITERS       (0x2)
#define MSTYLE_DXF_START_SQUARE_CAP  (0x10)
#define MSTYLE_DXF_START_INNER_ARCS  (0x20)
#define MSTYLE_DXF_START_ROUND_CAP   (0x40)
#define MSTYLE_DXF_END_SQUARE_CAP    (0x100)
#define MSTYLE_DXF_END_INNER_ARCS    (0x200)
#define MSTYLE_DXF_END_ROUND_CAP     (0x400)
#define MSTYLE_DXF_JUST_TOP          (0x1000)
#define MSTYLE_DXF_JUST_ZERO         (0x2000)
#define MSTYLE_DXF_JUST_BOT          (0x4000)

//class OdCmTransparency;
class OdDbStub;
#define NcDbStub                 OdDbStub

inline LPTSTR CloneString(LPCTSTR source)
{
	LPTSTR clone = new TCHAR[(size_t)lstrlen(source) + 1];
	lstrcpy(clone, source);
	return clone;
}

inline void DeleteString(LPTSTR& string)
{
	if(string) {
		delete [] string;
		string = NULL;
	}
}

#endif // __OPENDWGTHUNKTYPES_H__
