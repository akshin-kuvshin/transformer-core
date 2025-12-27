#ifndef __OPENDWG_SQLINTERFACE_H__
#define __OPENDWG_SQLINTERFACE_H__

#pragma once
#include "nrxdbgate_impexp.h"

class NRXDBGATE_EXPORT CNsiObject;           // Superclass for all classes
class NRXDBGATE_EXPORT CNsiIdent;            // Identifier
class NRXDBGATE_EXPORT CNsiData;             // NSI Data generic class
class NRXDBGATE_EXPORT CNsiNum;              // Numeric data
class NRXDBGATE_EXPORT CNsiExactNum;         // Exact numeric data
class NRXDBGATE_EXPORT CNsiSmallInt;         // Small Integer
class NRXDBGATE_EXPORT CNsiInt;              // Integer
class NRXDBGATE_EXPORT CNsiNumeric;          // Numeric
class NRXDBGATE_EXPORT CNsiDecimal;          // Decimal
class NRXDBGATE_EXPORT CNsiApproxNum;        // Approximate numeric data
class NRXDBGATE_EXPORT CNsiFloat;            // Float
class NRXDBGATE_EXPORT CNsiReal;             // Real
class NRXDBGATE_EXPORT CNsiDouble;           // Double precision
class NRXDBGATE_EXPORT CNsiChar;             // Character
class NRXDBGATE_EXPORT CNsiBinary;           // Bit
class NRXDBGATE_EXPORT CNsiIQualifier;       // Interval qualifier
class NRXDBGATE_EXPORT CNsiInterval;         // Interval
class NRXDBGATE_EXPORT CNsiYM;               // Year month intervals
class NRXDBGATE_EXPORT CNsiDT;               // Day Time intervals
class NRXDBGATE_EXPORT CNsiDatetime;         // Datetime data
class NRXDBGATE_EXPORT CNsiDate;             // Date
class NRXDBGATE_EXPORT CNsiTime;             // Time
class NRXDBGATE_EXPORT CNsiTimeStamp;        // Timestamp
class NRXDBGATE_EXPORT CNsiBlob;             // OLEDB BLOBs

class NRXDBGATE_EXPORT CNsiColumn;               // Column definition
class NRXDBGATE_EXPORT CNsiRow;                  // Array of columns
class NRXDBGATE_EXPORT CNsiHostBuffer;           // Host program buffer
class NRXDBGATE_EXPORT CNsiParameter;            // Parameter desriptor
class NRXDBGATE_EXPORT CNsiImplDefFunc;          // Function

// Class collections
class NRXDBGATE_EXPORT CNsiIRow;                 // Array of data pointers
class NRXDBGATE_EXPORT CNsiList;                 // List of CNsiObject's

class NRXDBGATE_EXPORT CNsiUcStr;                // Unicode string
class NRXDBGATE_EXPORT CNsiUcChar;               // Unicode character

class NRXDBGATE_EXPORT CNsiObjPack;              // Communication buffer access


class CNsiException;
class CNsiDSProperties;
class CNsiTCCond;
class CNsiObject;
//class CNsiObjPack;
////class CNsiUcStr;
//class CNsiDSProperties;
//class CNsiIdent;

#define NSI_MAX(x,y) ((x)>(y)?(x):(y))
#define NSI_MIN(x,y) ((x)<(y)?(x):(y))

typedef unsigned char  uchar;         /* Unsigned char */
#if !defined(hpux) || !defined(_SYS_TYPES_INCLUDED)
typedef unsigned short ushort;        /* Unsigned short */
typedef unsigned int   uint;          /* Unsigned int */
#endif /* !hpux  || !_SYS_TYPES_INCLUDED */
typedef unsigned long  ulong;         /* Unsigned long */
typedef double         real;          /* Real */
typedef long           integer;       /* Integer */
typedef short          smallint;      /* Small integer */


/* Interval data */

typedef struct asi_year {
	long        sign;       /* kNsiTrue if negative */
	ulong       years;      /* Years */
} NSI_IYEAR;

typedef struct asi_yeartomonth {
	long        sign;       /* kNsiTrue if negative */
	ulong       years;      /* Years */
	ulong       months;     /* Months (0-11) */
} NSI_IYEARTOMONTH;

typedef struct asi_month {
	long        sign;       /* kNsiTrue if negative */
	ulong       months;     /* Months */
} NSI_IMONTH;

typedef struct asi_day  {
	long        sign;       /* kNsiTrue if negative */
	ulong       days;       /* Days */
} NSI_IDAY;

typedef struct asi_daytohour  {
	long        sign;       /* kNsiTrue if negative */
	ulong       days;       /* Days */
	ulong       hours;      /* Hours (0-23) */
} NSI_IDAYTOHOUR;

typedef struct asi_daytominute {
	long        sign;       /* kNsiTrue if negative */
	ulong       days;       /* Days */
	ulong       hours;      /* Hours (0-23) */
	ulong       minutes;    /* Minutes (0-59) */
} NSI_IDAYTOMINUTE;

typedef struct asi_daytosecond {
	double      seconds;    /* Seconds (0-59.99..9) */
	long        sign;       /* kNsiTrue if negative */
	ulong       days;       /* Days */
	ulong       hours;      /* Hours (0-23) */
	ulong       minutes;    /* Minutes (0-59) */
} NSI_IDAYTOSECOND;

typedef struct asi_hour {
	long        sign;       /* kNsiTrue if negative */
	ulong       hours;      /* Hours */
} NSI_IHOUR;

typedef struct asi_hourtominute {
	long        sign;       /* kNsiTrue if negative */
	ulong       hours;      /* Hours */
	ulong       minutes;    /* Minutes (0-59)  */
} NSI_IHOURTOMINUTE;

typedef struct asi_hourtosecond {
	double      seconds;    /* Seconds (0-59.99..9) */
	long        sign;       /* kNsiTrue if negative */
	ulong       hours;      /* Hours */
	ulong       minutes;    /* Minutes (0-59) */
} NSI_IHOURTOSECOND;

typedef struct asi_minute {
	long        sign;       /* kNsiTrue if negative */
	ulong       minutes;    /* Minutes */
} NSI_IMINUTE;

typedef struct asi_minuteitosecond {
	double      seconds;    /* Seconds (0-59.99..9) */
	long        sign;       /* kNsiTrue if negative */
	ulong       minutes;    /* Minutes */
} NSI_IMINUTETOSECOND;

typedef struct asi_second {
	double      seconds;    /* Seconds */
	long        sign;       /* kNsiTrue if negative */
} NSI_ISECOND;

/* Datetime data */
/* */
typedef struct asi_date {  /* Date */
	ushort year;             /* Year */
	ushort month;            /* Month (0-11) */
	ushort day;              /* Day (0-31) */
	short  pad;              /* pad short */
} NSI_DTDATE;

typedef struct asi_time {       /* Time with time zone */
	double            second;   /* Second (0-59.99..9) */
	NSI_IHOURTOMINUTE timezone; /* time zone */
	ushort            hour;     /* Hour (0-23) */
	ushort            minute;   /* Minute (0-59) */
} NSI_DTTIME;

typedef struct asi_timestamp {  /* Timestamp with time zone */
	NSI_DTTIME   time;          /* Time */
	NSI_DTDATE   date;          /* Date */
} NSI_DTTIMESTAMP;


/* */
typedef enum {
	kNsiUnknown = -1,           /* Boolean value is undefined */
	kNsiFalse = 0,
	kNsiTrue = 1,
	kNsiBad = 0,
	kNsiGood = 1
} ENsiBoolean;

#define ENsiFlag ENsiBoolean

/* SQL data types */
typedef enum {
	kNsiVector      = -2,       /* Row */
	kNsiImplDefined = -1,       /* Implementation-defined data type */
	kNsiTUnknown = 0,
	kNsiChar = 1,
	kNsiNumeric,
	kNsiDecimal,
	kNsiInteger,
	kNsiSmallInt,
	kNsiFloat,
	kNsiReal,
	kNsiDouble,
	kNsiDateTime,
	kNsiInterval,
	kNsiCharVar = 12,
	kNsiBit = 14,
	kNsiBitVar,
	kNsiPoint,    /* n-dimentional point  */
	kNsiBlob
} ENsiDataType;

/* Date time types */
typedef enum {
	kNsiDTUnknown = 0,
	kNsiDate = 1,
	kNsiTime,
	kNsiTimeStamp,
	kNsiTimeTZ,
	kNsiTimeStampTZ
} ENsiDTType;

/* Interval types */
typedef enum {
	kNsiIUnknown = 0,
	kNsiYear = 1,
	kNsiMonth,
	kNsiDay,
	kNsiHour,
	kNsiMinute,
	kNsiSecond,
	kNsiYear2Month,
	kNsiDay2Hour,
	kNsiDay2Minute,
	kNsiDay2Second,
	kNsiHour2Minute,
	kNsiHour2Second,
	kNsiMinute2Second
} ENsiIType;


typedef unsigned int uint;

/* //////////////////////////////////////////////////////////// */
/* */
/* Trim specification */
/* */
typedef enum {
	kNsiLeading = 0,
	kNsiTrailing,
	kNsiBoth
} ENsiTrimSpec;


/* Host variable type */
/* */
typedef enum {
	kNsiHnull  = 0,           /* Type undefined */
	kNsiHshort = 1,           /* short int */
	kNsiHlong,                /* long int */
	kNsiHfloat,               /* float */
	kNsiHreal,                /* double */
	kNsiHchar,                /* null terminated character string */
	kNsiHunicode,             /* unicode string (wide characters string) */
	kNsiHbinary,              /* binary buffer */
	kNsiHdate,                /* date  (NSI_DTDATE) */
	kNsiHtime,                /* time  (NSI_DTTIME) */
	kNsiHtimestamp,           /* timestamp (NSI_DTTIMESTAMP) */
	kNsiHyear,                /* Year (NSI_IYEAR) */
	kNsiHyeartomonth,         /* Year to Month (NSI_IYEARTOMONTH) */
	kNsiHmonth,               /* Month (NSI_IMONTH) */
	kNsiHday,                 /* Day (NSI_IDAY) */
	kNsiHdaytohour,           /* Day to hour (NSI_IDAYTOHOUR) */
	kNsiHdaytominute,         /* Day to minute (NSI_IDAYTOMINUTE) */
	kNsiHdaytosecond,         /* Day to second (NSI_IDAYTOSECOND) */
	kNsiHhour,                /* Hour (NSI_IHOUR) */
	kNsiHhourtominute,        /* Hour to minute (NSI_IHOURTOMINUTE) */
	kNsiHhourtosecond,        /* Hour to second (NSI_IHOURTOSECOND) */
	kNsiHminute,              /* Minute (NSI_IMINUTE) */
	kNsiHminutetosecond,      /* Minute to second (NSI_IMINUTETOSECOND) */
	kNsiHsecond               /* Second (NSI_ISECOND) */
} ENsiHostType;

/* */
/*  ENsiDrvStatus, ENsiSIDataType, and ENsiSITransactionType  */
/*  sepecify features and capabilities that connection supports. */
/*  They can be retrieved by means of CNsiSQLObject::GetStatus function */
/* */

/* Supported general features codes */
/* */
typedef enum {
	kNsiStatUsername       = (int)0x00000001      /* User name */
	,kNsiStatPassword       = (int)0x00000002      /* Password */
	,kNsiStatCatalog        = (int)0x00000004      /* Catalog feature */
	,kNsiStatSchema         = (int)0x00000008      /* Schema feature */
	,kNsiStatTimeZone       = (int)0x00000010      /* Time zone */
	,kNsiStatNames          = (int)0x00000020      /* Character set names */
	,kNsiStatTranslation    = (int)0x00000040      /* Translations */
	,kNsiStatInfoSchema     = (int)0x00000080      /* Information schema facility */
	,kNsiStatCDCatalog      = (int)0x00000100      /* Catalog definition/drop catalog */
	,kNsiStatCDSchema       = (int)0x00000200      /* Schema definition/drop schema */
	,kNsiStatCDTable        = (int)0x00000400      /* Table definition/drop table */
	,kNsiStatCDView         = (int)0x00000800      /* View definition/drop view */
	,kNsiStatCDIndex        = (int)0x00001000      /* Index definition/drop index */
	,kNsiStatCDTranslation  = (int)0x00002000      /* Translation definition/drop translation */
	,kNsiStatCDAssertion    = (int)0x00004000      /* Create assertion/drop assertion */
	,kNsiStatCDCharset      = (int)0x00008000      /* Character set definition/drop character set */
	,kNsiStatCDCollation    = (int)0x00010000      /* Collation definition/drop collation */
	,kNsiStatCDDomain       = (int)0x00020000      /* Domain definition/drop domain */
	,kNsiStatADomain        = (int)0x00040000      /* Alter domain */
	,kNsiStatATable         = (int)0x00080000      /* Alter table */
	,kNsiStatPrivileges     = (int)0x00100000      /* Grant/revoke privileges */
	,kNsiStatCommitRollback = (int)0x00200000      /* Commit work/Rollback work */
	,kNsiStatSetTrans       = (int)0x00400000      /* Set transaction */
	,kNsiStatSetConstr      = (int)0x00800000      /* Set constraint */
	,kNsiStatCursor         = (int)0x01000000      /* Cursor manipulation (open, close, fetch next) */
	,kNsiStatFetch          = (int)0x02000000      /* Fetches Prior, First, Last, Absolute, Relative */
	,kNsiStatSingSelect     = (int)0x04000000      /* Select statement: single row  */
	,kNsiStatDeletePos      = (int)0x08000000      /* Delete: positioned */
	,kNsiStatUpdatePos      = (int)0x10000000      /* Update: positioned */
	,kNsiStatDeleteSearch   = (int)0x20000000      /* Delete: searched */
	,kNsiStatUpdateSearch   = (int)0x40000000      /* Update: searched */
	,kNsiStatInsert         = (int)0x80000000      /* Insert */

} ENsiDrvStatus;


/* Supported data type  */
typedef enum {
	kNsiSDImplDefined = (int)0x00000001,
	kNsiSDChar        = (int)0x00000002,
	kNsiSDNumeric     = (int)0x00000004,
	kNsiSDDecimal     = (int)0x00000008,
	kNsiSDInteger     = (int)0x00000010,
	kNsiSDSmallInt    = (int)0x00000020,
	kNsiSDFloat       = (int)0x00000040,
	kNsiSDReal        = (int)0x00000080,
	kNsiSDDouble      = (int)0x00000100,
	kNsiSDDate        = (int)0x00000200,
	kNsiSDTime        = (int)0x00000400,
	kNsiSDTimeTZ      = (int)0x00000800,
	kNsiSDTimestamp   = (int)0x00001000,
	kNsiSDTimestampTZ = (int)0x00002000,
	kNsiSDYM          = (int)0x00004000,
	kNsiSDDT          = (int)0x00008000,
	kNsiSDCharVar     = (int)0x00010000,
	kNsiSDBit         = (int)0x00020000,
	kNsiSDBitVar      = (int)0x00040000,
	kNsiSDBLOB          = (int)0x00080000,
	kNsiSDCharAsStr      = (int)0x00100000      // provider may use STR rather that WSTR to
	                                      // accept char input paramters

} ENsiSIDataType;


/* Supported transaction types */
typedef enum {
	kNsiTSUndefined = (int )0,         /* Undefined */
	                                 /* Read/Write, Read Uncommitted is not possible */
	kNsiTSRWRC = (int)0x00000001,    /* Read/Write, Read Committed */
	kNsiTSRWRR = (int)0x00000002,    /* Read/Write, Repeatable Read */
	kNsiTSRWSR = (int)0x00000004,    /* Read/Write, Serializable */
	kNsiTSRORU = (int)0x00000008,    /* Read Only, Read Uncommitted  */
	kNsiTSRORC = (int)0x00000010,    /* Read Only, Read Committed */
	kNsiTSRORR = (int)0x00000020,    /* Read Only, Repeatable Read */
	kNsiTSROSR = (int)0x00000040     /* Read Only, Serializable */

} ENsiSITransactionType;


/* Driver features, capabilities and status codes */
typedef enum {
	kNsiSISupportedFeatures            /* Supported base features codes (ENsiDrvStatus) */
	,kNsiSITransaction                  /* Transaction state (ENsiBoolean) */
	,kNsiSICsrState                     /* Open/Close cursor (ENsiBoolean) */
	,kNsiSICsrSns                       /* Sensitive/insensitive cursor (ENsiBoolean) */
	,kNsiSICsrScr                       /* Scroll/non scroll cursor (ENsiBoolean) */
	,kNsiSICsrPos                       /* Cursor position (long) */
	,kNsiSICsrUpd                       /* Cursor updatability (ENsiBoolean) */
	,kNsiSIDataType                     /* Supported data types (ENsiSIDataType) */
	,kNsiSIBindDataType                 /* Supported bind data types  (ENsiSIDataType) */
	,kNsiSITransactionType              /* Supported types of tranactions (ENsiSITransactionType) */
} ENsiStatInfo;

//#ifdef A
/* SQL statement types */
/* */
typedef enum {
	kNsiTYPE_UNDEFINED = 0,   /*  undefined */
	kNsiALLOC_CURSOR,         /*  allocate cursor  */
	kNsiALLOC_STATEMENT,      /*  allocate statement */
	kNsiALTER_DOMAIN,         /*  alter domain */
	kNsiALTER_TABLE,          /*  alter table */
	kNsiCREATE_ASSERTION,     /*  assertion definition */
	kNsiCREATE_CATALOG,       /*  create catalog */
	kNsiCREATE_CHARACTER_SET, /*  character set definition */
	kNsiCREATE_COLLATION,     /*  collation definition */
	kNsiCREATE_DOMAIN,        /*  domain definition */
	kNsiCLOSE_CURSOR,         /*  close cursor  */
	kNsiCOMMIT,               /*  commit work */
	kNsiCONNECT,              /*  connect  */
	kNsiCREATE_SCHEMA,        /*  schema definition */
	kNsiCREATE_TABLE,         /*  table definition */
	kNsiCREATE_VIEW,          /*  view definition */
	kNsiCREATE_INDEX,         /*  index definition */
	kNsiCREATE_TRANSLATION,   /*  translation definition */
	kNsiCURSOR,               /*  cursor specification */
	kNsiDELETE_CURSOR,        /*  delete positioned */
	kNsiDELETE_WHERE,         /*  delete searched */
	kNsiDEALLOCATE_STATEMENT, /*  deallocate statement */
	kNsiDISCONNECT,           /*  disconnect */
	kNsiDROP_ASSERTION,       /*  drop assertion */
	kNsiDROP_CATALOG,         /*  drop catalog */
	kNsiDROP_CHARACTER_SET,   /*  drop character set */
	kNsiDROP_COLLATION,       /*  drop collation */
	kNsiDROP_DOMAIN,          /*  drop domain */
	kNsiDROP_SCHEMA,          /*  drop schema */
	kNsiDROP_TABLE,           /*  drop table */
	kNsiDROP_TRANSLATION,     /*  drop translation */
	kNsiDROP_VIEW,            /*  drop view */
	kNsiDROP_INDEX,           /*  drop index */
	kNsiEXECUTE_IMMEDIATE,    /*  immediate execute */
	kNsiEXECUTE,              /*  execute */
	kNsiFETCH,                /*  fetch */
	kNsiGRANT,                /*  grant privileges */
	kNsiINSERT,               /*  insert */
	kNsiOPEN,                 /*  open cursor */
	kNsiPREPARE,              /*  prepare */
	kNsiREVOKE,               /*  revoke privileges */
	kNsiROLLBACK,             /*  rollback work */
	kNsiSELECT,               /*  select statement: single row */
	kNsiSET_CATALOG,          /*  set catalog */
	kNsiSET_SCHEMA,           /*  set schema */
	kNsiSET_TIME_ZONE,        /*  set time zone */
	kNsiSET_NAMES,            /*  set names  */
	kNsiSET_TRANSACTION,      /*  set transaction */
	kNsiSET_CONSTRAINT,       /*  set constraint mode  */
	kNsiSET_AUTHORIZATION,    /*  set authorization identifier */
	kNsiUPDATE_CURSOR,        /*  update: positioned */
	kNsiUPDATE_WHERE          /*  update: searched */
} ENsiStatement;
//#endif


/* Transaction isolation level */
typedef enum {
	kNsiTIUndefined = 0,
	kNsiReadUncommitted = 1,
	kNsiReadCommitted,
	kNsiRepeatableRead,
	kNsiSerializable
} ENsiTILevel;

/* Transaction mode */
typedef enum {
	kNsiTMUndefined = 0,
	kNsiTReadOnly = 1,
	kNsiTReadWrite
} ENsiTMode;

/* default diagnostics size */
#define  DefaultDiagSize 32

/* Defer or immediate constriant checking */
typedef enum {
	kNsiCDefer = 1,
	kNsiCImmediate
} ENsiConstrCheck;


/* Cursor scrollability */
typedef enum {
	kNsiNonScroll = 0,
	kNsiScroll = 1
} ENsiCurScr;

/* Cursor Sensitivity */
typedef enum {
	kNsiSnsUndef = 0,      /* Cursor sensitivity is undefined */
	kNsiInsensitive = 1
} ENsiCurSns;

/* Fetch direction */
typedef enum {
	kNsiNext = 1,
	kNsiPrior,
	kNsiFirst,
	kNsiLast,
	kNsiAbsolute,
	kNsiRelative
} ENsiDirection;

/* Cursor position */
/* */
typedef enum {
	kNsiCPUnknown = 0,     /* Position unknown */
	kNsiTos       = 1,     /* Before the first row */
	kNsiEos       = 2,     /* After the last row */
	kNsiBnr       = 3,     /* Before row (on deleted row) */
	kNsiOcr       = 4      /* Current row */
} ENsiCurPos;

/*  Coercibility attributes */
/* */
typedef enum {
	kNsiCACoercible = 0,    /* Coercible */
	kNsiCAImplicit  = 1,    /* Implicit */
	kNsiNoCollation = 2,    /* No collating sequence  */
	kNsiCAExplicit  = 3     /* Explicit */
} ENsiCAttr;


/* Information schema tables */
typedef enum {
	 kNsiISUnknown                    = 0

	// Logical tables
	,kNsiIS_ASSERTIONS                = 1
	,kNsiIS_CHARACTER_SETS            = 2
	,kNsiIS_CHECK_CONSTRAINTS        = 3
	,kNsiIS_COLLATIONS                = 4
	,kNsiIS_COLUMN_DOMAIN_USAGE        = 5
	,kNsiIS_COLUMN_PRIVILEGES        = 6
	,kNsiIS_COLUMNS                    = 7
	,kNsiIS_CONSTRAINT_COLUMN_USAGE    = 8
	,kNsiIS_CONSTRAINT_TABLE_USAGE    = 9
	,kNsiIS_FOREIGN_KEYS            = 10
	,kNsiIS_KEY_COLUMN_USAGE        = 11
	,kNsiIS_PRIMARY_KEYS            = 12
	,kNsiIS_PROCEDURE_COLUMNS        = 13
	,kNsiIS_PROCEDURE_PARAMETERS       = 14
	,kNsiIS_PROCEDURES                 = 15
	,kNsiIS_REFERENTIAL_CONSTRAINTS    = 16
	,kNsiIS_SCHEMATA                   = 17
	,kNsiIS_SQL_LANGUAGES              = 18
	,kNsiIS_TABLE_CONSTRAINTS          = 19
	,kNsiIS_TABLE_PRIVILEGES           = 20
	,kNsiIS_TABLES                     = 21
	,kNsiIS_TRANSLATIONS               = 22
	,kNsiIS_USAGE_PRIVILEGES           = 23
	,kNsiIS_VIEW_COLUMN_USAGE          = 24
	,kNsiIS_VIEW_TABLE_USAGE           = 25
	,kNsiIS_VIEWS                      = 26

	// Physical
	,kNsiIS_CATALOGS                = 27
	,kNsiIS_INDEXES                    = 28
	,kNsiIS_PROVIDER_TYPES            = 29
	,kNsiIS_STATISTICS                = 30

} ENsiInfSchTab;


/* Datasource type */
typedef enum {
	kNsiDSSOURCETYPE_BOTH       = 0,
	kNsiDSSOURCETYPE_DATASOURCE = 1,
	kNsiDSSOURCETYPE_ENUMERATOR = 2
} ENsiDataSourceType;




/* //////////////////////////////////////////////////////////////// */
/* */
/* Default, minimal and maximal setting for NSI data */
/*  */
#define MaxCharLength             256
#define DefaultCharLength         1

#define MaxBinaryLength           (256*8)
#define DefaultBinaryLength       1

#define SmallIntPrecision         6

#define IntegerPrecision          10

#define MaxNumericPrecision       32
#define MaxNumericScale           MaxNumericPrecision
#define DefaultNumericPrecision   18
#define DefaultNumericScale       0

#define MaxDecimalPrecision       32
#define MaxDecimalScale           MaxDecimalPrecision
#define DefaultDecimalPrecision   18
#define DefaultDecimalScale       0

#define MaxFloatPrecision         32
#define DefaultFloatPrecision     16

#define RealPrecision             32

#define DoublePrecision           64

#define MaxLeadingFieldPrec       6    /* Interval  */
#define MaxFracSecondPrec         8
#define MinLeadingFieldPrec       2
#define MinFracSecondPrec         0
#define DefaultLeadingFieldPrec   4
#define DefaultFracSecondPrec     0

#define MaxTimePrecision          6
#define DefaultTimePrecision      0

#define MaxTimeStampPrecision     6
#define DefaultTimeStampPrecision 6

#define MaxIdentLength            256

#define DefaultPointDimension     3


/* //////////////////////////////////////////////////////////////// */
/* */
/* Implementation defined data definition */
/* */
#define NsiImplDefFxdMin          0000 /* 0000 - 1999 reserved for NSI */
#define NsiImplDefFxdUser         2000 /* 2000 - 3999 avail for User */
#define NsiImplDefFxdMax          3999
#define NsiImplDefRawMin          4000 /* 4000 - 5999 reserved for NSI */
#define NsiImplDefRawUser         6000 /* 6000 - 8000 avail for User */
#define NsiImplDefRawMax          8000


/* //////////////////////////////////////////////////////////////////// */
/* */
/* Condition information item names */
/* */
typedef enum {                /* Type of data in buffer */
	kNsiConditionNumber = 1,  /* Integer */
	kNsiMessageLength,        /* Integer */
	kNsiMessageOctetLength,   /* Integer */

	kNsiHRESULT          =  4,/* HRESULT */

	kNsiConditionStrings = 20,
	kNsiReturnedSQLSTATE,     /* Char */
	kNsiClassOrigin,          /* Char */
	kNsiSubClassOrigin,       /* Char */
	kNsiServerName,           /* Char */
	kNsiConnectionName,       /* Char */
	kNsiConstraintCatalog,    /* Char */
	kNsiConstraintSchema,     /* Char */
	kNsiConstraintName,       /* Char */
	kNsiCatalogName,          /* Char */
	kNsiSchemaName,           /* Char */
	kNsiTableName,            /* Char */
	kNsiColumnName,           /* Char */
	kNsiCursorName,           /* Char */
	kNsiMessageText,          /* Char */

	kNsiInterface        = 35 /*IID*/

} ENsiDiag;

typedef unsigned int NsiDiag;
#define MinUserDefDiagParam         0x0400

/* //////////////////////////////////////////////////////////////////// */
/* */
/* Exception conditions used in NSI. */
/* */
typedef enum {
	kNsiErrUndefined = -1

	,kNsiNoError = 0   /* Successful completion */
	,kNsiOKAY = 0


	/* The following error codes are for standard SQLSTATE values */
	/* */
	,kNsiSQLWARN =           0x0100  /* warning  */
	,kNsiSQLWARNCUROP                /* cursor operation conflict  */
	,kNsiSQLWARNDISC                 /* disconnect error  */
	,kNsiSQLNULLSET                  /* null value eliminated in set function  */
	,kNsiSQLWARNRTRUNC               /* string data, right truncation  */
	,kNsiSQLWARNINSUFDESC            /* insufficient item descriptor areas  */
	,kNsiSQLWARNREVOKE               /* privilege not revoked  */
	,kNsiSQLWARNGRANT                /* privilege not granted  */
	,kNsiSQLWARNBITPAD               /* implicit zero-bit padding  */
	,kNsiSQLWARNLONGCOND             /* search condition too long for information schema  */
	,kNsiSQLWARNLONGEXPR             /* query expression too long for information schema  */

	,kNsiSQLNODATA =         0x0200  /* no data  */
	,kNsiSQLNDSearchStm              /* rows were not modified by searched statement */
	,kNsiSQLNDSingSelect             /* row doesn't match single select */
	,kNsiSQLNDEOS                    /* fetch: end of selection set */
	,kNsiSQLNDTOS                    /* fetch: top of selection set */

	,kNsiSQLDYN    =         0x0700  /* dynamic SQL error  */
	,kNsiSQLDYNUPMISMATCH            /* using clause does not match dynamic parameter specification  */
	,kNsiSQLDYNUTMISMATCH            /* using clause does not match target specification  */
	,kNsiSQLDYNEXECUR                /* cursor specification cannot be executed  */
	,kNsiSQLDYNUSINGMIS              /* using clause required for dynamic parameter  */
	,kNsiSQLDYNNOTCURSOR             /* prepared statement not a cursor specification  */
	,kNsiSQLDYNAVIOLATION            /* restricted data type attribute violation  */
	,kNsiSQLDYNINTOMIS               /* using clause required for result fields  */
	,kNsiSQLDYNINVDSCCOUN            /* invalid descriptor count  */
	,kNsiSQLDYNINVDSCIDX             /* invalid descriptor index  */
	,kNsiSQLDYNNOTPREPARED           /* statement was not prepared */
	,kNsiSQLDYNAlreadyBound          /* columns were already bound with host buffers */

	,kNsiSQLCON     =        0x0800  /* connection exception  */
	,kNsiSQLCONCLIENT                /* SQL-client unable to establish SQL- connection  */
	,kNsiSQLCONNAMEUSE               /* connection name in use  */
	,kNsiSQLCONNOTEXIST              /* connection does not exist */
	,kNsiSQLCONSERVER                /* SQL-server rejected establishment of SQL-connection  */
	,kNsiSQLCONOPENOBJS                /* open objects associated with session */
	,kNsiSQLCONFAILURE               /* connection failure    */
	,kNsiSQLCONTRANS                 /* transaction resolution unknown  */

	,kNsiSQLCURCONFLICT =    0x0900  /* cursor operation conflict   */

	,kNsiSQLNOTSUPPORTED =   0x0A00  /* feature not supported  */
	,kNsiSQLMULTRANS                 /* multiple environment transaction  */

	,kNsiSQLCARVIOLATION  =  0x2100  /* cardinality violation  */

	,kNsiSQLDATA          =  0x2200  /* data exception  */
	,kNsiSQLDATASRTRUN               /* string data, right truncation  */
	,kNsiSQLDATANOIND                /* null value, no indicator parameter */
	,kNsiSQLDATANUMRANGE             /* numeric value out of range  */
	,kNsiSQLDATANUMTRUNC             /* decimal fractional part was rounded */
	,kNsiSQLDATAASSIGN               /* error in assignment  */
	,kNsiSQLDATAFETSEQ               /* invalid fetch sequence */
	,kNsiSQLDATADTFORMAT             /* invalid datetime format */
	,kNsiSQLDATADTOVF                /* datetime field overflow */
	,kNsiSQLDATATZDISP               /* invalid time zone displacement value  */
	,kNsiSQLDATA10                   /* Undefined */
	,kNsiSQLDATASUBSTRERR            /* substring error  */
	,kNsiSQLDATAZERODIV              /* division by zero */
	,kNsiSQLDATA13                   /* Undefined */
	,kNsiSQLDATAINFORMAT             /* invalid interval format (NSI extra) */
	,kNsiSQLINTEROVF                 /* interval field overflow  */
	,kNsiSQLColRO                    /* column is read only */
	,kNsiSQLDATA17                   /* Undefined */
	,kNsiSQLDATACHARCAST             /* invalid character value for cast */
	,kNsiSQLDATAESCCHAR              /* invalid escape character  */
	,kNsiSQLDATA20                   /* Undefined */
	,kNsiSQLDATACHAR                 /* character not in repertoire */
	,kNsiSQLDATAINDIVF               /* indicator overflow  */
	,kNsiSQLDATAPARVAL               /* invalid parameter value  */
	,kNsiSQLDATACSTR                 /* unterminated C string  */
	,kNsiSQLDATAESCSEQ               /* invalid escape sequence  */
	,kNsiSQLDATASTRLEN               /* string data, length mismatch  */
	,kNsiSQLDATATRIMERR              /* trim error  */
	,kNsiSQLDATADTUNDF               /* datetime field underflow */

	,kNsiSQLINTCONSTR     =  0x2300  /* integrity constraint violation  */

	,kNsiSQLINVCURSTATE   =  0x2400  /* invalid cursor state  */
	,kNsiSQLICSDeallocStm =  0x2401  /* deallocate statement associated with open cursor */
	,kNsiSQLICSClose      =  0x2402  /* cursor is in close state */
	,kNsiSQLICSNotScroll  =  0x2403  /* can only fetch next in non-scroll cursor */
	,kNsiSQLICSReadOnly   =  0x2404  /* cursor is read only */
	,kNsiSQLICSNoCurRow   =  0x2405  /* cursor is not positioned on row */
	,kNsiSQLICSOpen       =  0x2406  /* cursor is in open state */

	,kNsiSQLINVTRSTATE    =  0x2500  /* invalid transaction state  */
	,kNsiSQLITSActive     =  0x2501  /* disconnect while transaction is active */
	,kNsiSQLITSNotActive  =  0x2502  /* transaction is in-active */
	,kNsiSQLITSSetTrans   =  0x2503  /* set transaction (transaction is active) */
	,kNsiSQLINVTSTabRO    =  0x2504  /* Table is read only */
	,kNsiSQLINVTSTrsRO    =  0x2505  /* Transaction is read only */
	,kNsiSQLINVTSAuth     =  0x2506  /* Set authorization id but transaction is active */


	,kNsiSQLINVSTMNAME    =  0x2600  /* invalid SQL statement name  */

	,kNsiSQLTRIGCHNVIOL   =  0x2700  /* triggered data change violation  */

	,kNsiSQLINVAUTHID     =  0x2800  /* invalid authorization specification  */

	,kNsiSQLDIRSYNACS     =  0x2A00  /* syntax error or access rule violation in direct SQL statement  */

	,kNsiSQLPRIVEXIST     =  0x2B00  /* dependent privilege descriptor still exist  */

	,kNsiSQLINVCHARSET    =  0x2C00  /* invalid character set name    */

	,kNsiSQLINVTRTERM     =  0x2D00  /* invalid transaction termination     */

	,kNsiSQLINVDESC       =  0x3300  /* invalid SQL descriptor name  */

	,kNsiSQLINVCURNAME    =  0x3400  /* invalid cursor name  */

	,kNsiSQLINVCONDNUM    =  0x3500  /* invalid condition number  */

	,kNsiSQLDYNSYNACS     =  0x3700  /* syntax error or access rule violation in dynamic SQL statement  */
	/* NSI syntax errors */
	,kNsiErSynWrStr                  /* Wrong string format */
	,kNsiErSynLongStr                /* String is too long (character, binary) */
	,kNsiErSynMisQuot                /* Missing right quotas  */
	,kNsiErSynHexDigit               /* Wrong Hexadecimal digit */
	,kNsiErSynBinDigit               /* Wrong Binary digit */
	,kNsiErSynInterval               /* Wrong interval string */
	,kNsiErSynTypeMatch              /* Data types mismatch  */
	,kNsiErSynCollate                /* Invalid collate clause */
	,kNsiErSynWrTimeZone             /* Misleading time zone specification  */
	,kNsiErSynMisZone                /* Missing ZONE keyword   */
	,kNsiErSynNotTimeZone            /* Not a time zone interval */
	,kNsiErSynUnbalPar               /* Unbalance parenthesis */
	,kNsiErSynExprEx                 /* Expression expected */
	,kNsiErSynMisCol                 /* Missing column specification  */
	,kNsiErSynWrColSpec              /* Wrong column specification  */
	,kNsiErSynNoLeftPar              /* Left parenthesis expected  */
	,kNsiErSynMlStar                 /* Misleading star symbol */
	,kNsiErSynMisIn                  /* Expected IN keyword */
	,kNsiErSynWrDTField              /* Wrong datetime field for extraction */
	,kNsiErSynMisFrom                /* Expected FROM keyword */
	,kNsiErSynMisUsing               /* Expected USING keyword */
	,kNsiErSynFOUorTR                /* Form-of-use or translation name expected */
	,kNsiErSynMisTimePrec            /* Missing time precision */
	,kNsiErSynWrCollName             /* Wrong collation name */
	,kNsiErSynWrSetSq                /* Set function or subquery can't be set function argument */
	,kNsiErSynNoComma                /* Missing comma */
	,kNsiErSynNoWhen                 /* Missing when clause */
	,kNsiErSynMisThen                /* Missing then clause */
	,kNsiErSynMisEnd                 /* Missing END  */
	,kNsiErSynWrNot                  /* Wrong usage of NOT  */
	,kNsiErSynNull                   /* NULL expected  */
	,kNsiErSynCompare                /* Compare operator expected  */
	,kNsiErSynWrComma                /* Wrong comma position */
	,kNsiErSynMask                   /* Mask should be of character type */
	,kNsiErSynEsc                    /* Escape character expected  */
	,kNsiErSynMisSq                  /* Subquery expected */
	,kNsiErSynAndBet                 /* AND was missed in BETWEEN predicate  */
	,kNsiErSynNotJoin                /* Not a joined table */
	,kNsiErSynMisJoin                /* Missing JOIN keyword */
	,kNsiErSynWrNatural              /* Union join can't be natural union  */
	,kNsiErSynMisJoinSpec            /* Misleading join specification */
	,kNsiErSynMisCorName             /* Missing correlation name  */
	,kNsiErSynWrTabSpec              /* Wrong table specification  */
	,kNsiErSynEmptyList              /* List of columns is empty  */
	,kNsiErSynNoJoinSpec             /* Missing join specification */
	,kNsiErSynMisName                /* Missing database object name  */
	,kNsiErSynMisQueryPrimary        /* Missing query primary */
	,kNsiErSynEEEEEEEEEEEEEEE        /* Not Used              */
	,kNsiErSynNotJoinedTable         /* Not a joined table */
	,kNsiErSynMisTabValConstr        /* Missing table value constructor */
	,kNsiErSynMisSelect              /* Missing SELECT keyword */
	,kNsiErSynMisColName             /* Missing column name */
	,kNsiErSynMisGroup               /* Selection list contains set functions and columns  */
	                                /* references but GROUP BY clause was missed  */
	,kNsiErSynNotScalar              /* Scalar expression expected */
	,kNsiErSynElementInParen         /* Element can't be in parenthesis */
	,kNsiErSynOvrlDegree             /* Wrong overlaps operand degree  */
	,kNsiErSynDegreeViolation        /* Degree violation */
	,kNsiErSynMisAs                  /* Missing keyword AS  */
	,kNsiErSynWrongCast              /* Wrong cast */
	,kNsiErSynInvalidDomain          /* Invalid domain name */
	,kNsiErSynCharExpected           /* CHAR expected */
	,kNsiErSynTypeExpected           /* Data type specification expected  */
	,kNsiErSynWrongPrecLength        /* Wrong precision or length */
	,kNsiErSynScaleExpected          /* Scale expected */
	,kNsiErSynWrongScale             /* Wrong scale */
	,kNsiErSynWithTimeZoneExpected   /* Wrong WITH TIME ZONE sentence */
	,kNsiErSynNoVarLength            /* Missing varying length */
	,kNsiErSynOrderByExpected        /* ORDER BY expected */
	,kNsiErSynReadOnlyExpected       /* READ ONLY expected */
	,kNsiErSynWrongSortKey           /* Wrong sort key */
	,kNsiErSynEmptySortList          /* Empty sort list */
	,kNsiErSynWrongToken             /* Wrong token was met  */
	,kNsiErSynWrTabName              /* Wrong table name */
	,kNsiErSynMisOf                  /* Missing keyword OF  */
	,kNsiErSynMisCursorName          /* Missing cursor name */
	,kNsiErSynMisSet                 /* Missing keyword SET */
	,kNsiErSynMisBecome              /* = expected in UPDATE set clause */
	,kNsiErSynMisInto                /* Missing INTO keyword  */
	,kNsiErSynMisValues              /* Missing VALUES keyword  */
	,kNsiErSynMisTarget              /* Missing target specification */
	,kNsiErSynDubTransMode           /* Diplicate definition of transaction mode */
	,kNsiErSynMisSize                /* Missing SIZE keyword */
	,kNsiErSynWrDiagSize             /* Wrong diagnostics area size */
	,kNsiErSynMisTransMode           /* Transaction modes are not specified */
	,kNsiErSynInCompLevelMode        /* Incompatible transaction access mode and isolation level */
	,kNsiErSynWrConstrChkMode        /* Wrong constraint checking mode */
	,kNsiErSynWrConstrName           /* Wrong constraint name */
	,kNsiErSynMisRead                /* Missing READ keyword  */
	,kNsiErSynMisAuthorization       /* Missing AUTHORIZATION keyword */
	,kNsiErSynMisTemporary           /* Missing TEMPORARY keyword */
	,kNsiErSynMisTable               /* Missing TABLE keyword */
	,kNsiErSynOnCommit               /* Shall be ON COMMIT */
	,kNsiErSynNotTemporary           /* Commit behaviour only for temporary table */
	,kNsiErSynWrComBehaviour         /* Wrong commit behaviour */
	,kNsiErSynMisRows                /* Missing ROWS keyword */
	,kNsiErSynMisTableName           /* Missing table name */
	,kNsiErSynWrCheckTime            /* Wrong constraint time specification */
	,kNsiErSynMisDeferrable          /* Keyword DEFERRABLE expected */
	,kNsiErSynWrNotDefer             /* Initialy deferred constraint can't be not deferrable */
	,kNsiErSynNotNull                /* Not Null shall be specified for constraint */
	,kNsiErSynPrimaryKey             /* Primary key shall be specified for constraint */
	,kNsiErSynMisConstr              /* Missing constraint specification */
	,kNsiErSynMisRefSpec             /* Missing references specification */
	,kNsiErSynMisRefTable            /* Referenced table and columns expected */
	,kNsiErSynWrMatchType            /* Wrong match type of constraint  */
	,kNsiErSynSetAction              /* Set triggered action expected */
	,kNsiErSynDuplAction             /* Duplicated triggered action specification */
	,kNsiErSynMisTrigRule            /* Missing triggered rule    */
	,kNsiErSynForeignKey             /* Foreign key shall be specified for constraint */
	,kNsiErSynNoColDef               /* No column definitions */
	,kNsiErSynMisAlterAction         /* Missing alter action */
	,kNsiErSynDropDefault            /* Drop default action expected */
	,kNsiErSynSetDefault             /* Set default action expected */
	,kNsiErSynMisDropBehaviour       /* Missing drop behaviour */
	,kNsiErSynNotCheckConstr         /* Domain constraint shall be check constraint */
	,kNsiErSynMisCheckOption         /* CHECK OPTION expected */
	,kNsiErSynMisCharSet             /* CHARACTER SET expected */
	,kNsiErSynMisCharSetSource       /* Character set source expected */
	,kNsiErSynCharSetExp             /* Character set expected */
	,kNsiErSynPadAttr                /* Pad attribute expected */
	,kNsiErSynMisTransName           /* Missing translation name */
	,kNsiErSynCollationExp           /* Collation expected */
	,kNsiErSynMisExternColl          /* Missing external collation */
	,kNsiErSynMisTo                  /* Missing TO keyword  */
	,kNsiErSynMisOn                  /* Missing ON keyword  */
	,kNsiErSynMisGrantOption         /* GRANT OPTION expected */
	,kNsiErSynMisFor                 /* Missing FOR keyword  */
	,kNsiErSynMisObjectName          /* Missing object name */
	,kNsiErSynMisGrantee             /* Missing grantee */
	,kNsiErSynAllPrivileges          /* ALL PRIVILEGES expected */
	,kNsiErSynMisIndex               /* INDEX keyword expected */
	,kNsiErSynAuthorExpected         /* Authorization identifier expected */
	,kNsiSynErDublColumnName         /* Duplicate column name */
	,kNsiSynErAmbTabRef              /* Ambigious table reference */
	,kNsiSynErTableNotFound          /* Table name is not found (+ table name) */
	,kNsiSynErColumnNotFound         /* Column name is not found (+ column name) */
	,kNsiSynErAmbColRef              /* Ambigious column reference (+ column name) */
	,kNsiSynErWrongParameterUsage    /* Parameter was specified in wrong place */
	,kNsiSynErLocalCol               /* Column shall be local reference */
	,kNsiSynErOuterCol               /* Column shall be outer reference */
	,kNsiSynErDuplDistinct           /* Duplicate distinct in query specification */
	,kNsiSynErArgNotColumn           /* Distinct argument shall be column reference */
	,kNsiSynErNoCorrColumns          /* Corresponding column were not found */
	,kNsiSynErWrongCorrColumn        /* Wrong corresponding column name */
	,kNsiSynErMustBeGroupCol         /* Column reference must be a group column */
	,kNsiErSynMisLeadSetFunc         /* Misleading set function usage */
	,kNsiErSynWrongEscLength         /* Escape character must be 1 symbol length */
	,kNsiErSynSimpleValue            /* Should be simple value */
	,kNsiErSynInvOrderSpec           /* Invalid order specification */
	,kNsiErSynMustBeOnlyCol          /* Column shall be the single outer reference */
	,kNsiErSynCursorNotFound         /* Cursor name not found */
	,kNsiErSynUpdateColDupl          /* Column name duplicates in the set clause */
	,kNsiErSynDefaultUse             /* DEFAULT shall be specified in INSERT  */
	,kNsiErSynWrColInsert            /* Wrong column name in insert list */
	,kNsiErSynNotCastable            /* Expression can't be casted to the specified type */
	,kNsiErSynMisDefValue            /* Missing default value */
	,kNsiErSynMisServerName          /* Missing server name */
	,kNsiErSynMisCorNameForRemote    /* Missing correlation name for remote table */
	,kNsiErSynWrongForUpdateColSpec  /* Wrong column name in FOR UPDATE specification */
	,kNsiErSynNotUpdateCol           /* Not updatable column */
	,kNsiErSynTransMode              /* Invalid transaction mode specification */
	,kNsiErSynMisLevel               /* Missing LEVEL keyword */
	,kNsiErSynUncommComm             /* Uncommitted/committed expected */
	,kNsiErSynDubIsoLevel            /* Duplicated specification of isolation level */
	,kNsiErSynDubDiagSize            /* Duplicated diagnostics size specification */
	,kNsiErSynMisIsoLevel            /* missing isolation level specification */
	,kNsiErSynCharSetUsage           /* character set usage */
	,kNsiErSynCollatingSeq           /* collating sequence invalid syntax */
	,kNsiErSynNotCharCollate         /* collation can be specified only for character data */
	,kNsiErSynColCharSetMisMatch     /* character set doesn't has specified collation */
	,kNsiErSynDuplJoinCol            /* Duplicate column name in natural or named column join */
	,kNsiSynErCorrJoinColNotFound    /* common join columns not found */
	,kNsiSynErFunctionNotExists      /* function doesn't exist */
	,kNsiSynErNoMatchFunction        /* no implemetation-defined function match argument list */
	,kNsiSynErWrongBoolFuncUsage     /* wrong boolean function usage */
	,kNsiSynErWrongValueFuncUsage    /* wrong value function usage */


	,kNsiSQLAMBCURSOR     =  0x3C00  /* ambiguous cursor name  */

	,kNsiSQLINVCATNAME    =  0x3D00  /* invalid catalog name     */

	,kNsiSQLINVSCHNAME    =  0x3F00  /* invalid schema name      */

	,kNsiSQLTR            =  0x4000  /* transaction rollback  */
	,kNsiSQLTRINTEGRITY              /* integrity constrint violation      */
	,kNsiSQLTRSER                    /* serialization failure   */
	,kNsiSQLTRSTMCOMP                /* statement completition unknown  */

	,kNsiSQLSYNACS        =  0x4200  /* access rule violation (permission denied) */

	,kNsiSQLCHECKOPT      =  0x4400  /* with check option violation  */

	,kNsiSQLRDA           =  0x8000  /* Remote Database Access   */


	/* Generic NSI excpetions */
	/*                     */
	,kNsiEXCP             =  0xA000  /* NSI Exception  */
	,kNsiEXCPINIT                    /* unable to initialize NSI  */
	,kNsiEXCPTERM                    /* error during NSI termination  */
	,kNsiEXCPDUPLINIT                /* NSI was already initialized */
	,kNsiEXCPNOTINIT                 /* NSI was not initialized */
	,kNsiEXCPBADINI                  /* initialization file has errors or is corrupted */
	,kNsiEXCPWRONGENV                /* environment is not defined in AST configuration */
	,kNsiEXCPWRENVPAR                /* invalid environment parameter in AST configuration */
	,kNsiNoMemory                    /* insufficient memory             */
	,kNsiErStkOvrFlw                 /* Stack overflow  */
	,kNsiErStkUnrFlw                 /* Stack underflow */
	,kNsiInvalidParam                /* Invalid parameter */
	,kNsiInternalError               /* Iternal error  */
	,kNsiFunctionNotSupported        /* Function overflow */
	,kNsiTryTableOverflow
	,kNsiOperationNotSupported
	,kNsiCannotOpenTable
	,kNsiOutOfRange
	,kNsiInvalidUcObject
	,kNsiInvalidDDAObject            /* Invalid DDA object */
	,kNsiErrEofFound                 /* EOF found */
	,kNsiErrFileLocked               /* File was locked during the timeout period */
	,kNsiRecLocked                   /* Record is locked */
	,kNsiTableLocked                 /* Table is locked */
	,kNsiNativePrepare               /* Native statement cannot be prepared */
	,kNsiNativeExecute               /* Native statement cannot be executed */
	,kNsiRemoteTabModification       /* Remote table has read only access */
	,kNsiInterDBExecution            /* Can't execute interdatabase statement */
	,kNsiErrCodePageNotDefined       /* Code page not supported */
	,kNsiErrCodePageFileNotFound     /* Code page not supported */
	,kNsiErrCodePageFormat           /* Corrupted code page data */
	,kNsiErrCollationNotDefined      /* Collation not supported */
	,kNsiErrCollationFileNotFound    /* Collation not supported */
	,kNsiErrCollationFormat          /* Corrupted collation data */
	,kNsiErrNsilocNotFound           /* Cannot find asiloc.xmx */

	/* Interprocess Communication Exceptions */
	/*                                   */
	,kNsiErrDrv          = 0xB000    /* IPC exceptions */
	,kNsiErrOpenDrv                  /* OLEDB provider not registered */
	,kNsiErrPathNotFound             /* Path not found */
	,kNsiErrProvNotSpecified         /* OLEDB Provider not specified */
	,kNsiErrToManyFileOpen           /* Too many open files */
	,kNsiErrAccessDenied             /* Access denied */
	,kNsiErrFileHandle               /* Invalid file handle */
	,kNsiErrSrvNotReg                /* Services not registered */
	,kNsiErrCannotRegSrv                /* Unable to register services */
	,kNsiErrCannotFindSrv            /* csp.dll not found */
	,kNsiErrNoRegEntryPoint             /* Server doesn't have DllRegisterServer entry point */
	,kNsiErrCannotLoadSrvDll         /* Cannot load services DLL */
	,kNsiErrOutPhysicalMemory        /* Out of physical memory */
	,kNsiErrOutSwapSpace             /* Out of swap space */
	,kNsiErrOLEDB20NotInstalled      /* OLEDB 2.0 not installed */
	,kNsiErrOLENotInit                /* Cannot initialize OLE or one of its components */
	,kNsiErrNoVirtualMemory          /* Insufficient virtual memory space */
	,kNsiErrNoConvMemory             /* Insufficient conventional memory space */
	,kNsiErrMDLNotFound              /* MDL file not found */
	,kNsiErrOpenIni                  /* Cannot get AST configuration information */
	,kNsiErrNoEnv                    /* Environment name not specified */
	,kNsiErrIncompEnv                /* Incompatible environment */
	,kNsiErrNoPath                   /* Driver path and name was not specified */
	,kNsiErrLostConnection           /* Server died, connection lost */
	,kNsiErrToManyDrivers            /* Too many driver loaded */
	,kNsiErrInvalidName              /* Driver name is invalid */
	,kNsiErrNotNsiDrv                /* Program referenced in AST configuration
	                                /* is not an NSI driver */
	,kNsiErrOsEnv                    /* Bad format for OS environment */
	,kNsiErrDrvInit                  /* Error found durring driver initialization */
	,kNsiErrDrvThunk                 /* Trap in DBMS communication */
	,kNsiErrComBuf                   /* Cannot create communication buffer */
	,kNsiErrBlockByTSR               /* User has loaded TSR from NanoCAD shell command */
	,kNsiErrNoDrv                    /* Driver not found in AST configuration */
	,kNsiErrMemoryAccess             /* Memory access violatation */
	,kNsiErrOS                       /* OS error */
	,kNsiErrDrvOld                   /* Old driver's version */

	,kNsiErrDBMSServer =  0xCF00     /* Exception raised by DBMS driver  */
	,kNsiErrHRESULT                  /* Generate HRESULT description     */

} ENsiError;

typedef unsigned int NsiError;

typedef wchar_t             NsiUcChar;
typedef NsiUcChar*          NsiUcStr;
typedef const NsiUcChar*    NsiCUcStr;
typedef unsigned long       NsiUcIdCCT;     /* Id of the CodePage */
typedef const char*         NsiUcNmCCT;     /* Name of the CodePage */
typedef unsigned long       NsiUcIdCLT;     /* Id of the Collation */
                                            /*    LCID win alalog  */
typedef const char*         NsiUcNmCLT;     /* Name of the Collation */
#if !defined(HOST_IN_QT)
//////////////////////////////////////////////////////////////////////////
// CNsiUcStr
class CNsiUcStr {
public:
	CNsiUcStr();
	CNsiUcStr(const char*,NsiUcNmCCT);
	CNsiUcStr(const char*,NsiUcIdCCT);
	CNsiUcStr(const char*);
	CNsiUcStr(NsiCUcStr);
	CNsiUcStr(const CNsiUcStr&);
	CNsiUcStr(const CNsiUcStr*);
	~CNsiUcStr();
	void           Clear(void);
	const           NsiUcStr UcStr(void) const;
	int            Size(void) const;
	int            Length(void) const;
	int            Chlen(void) const;
	int            Chlen(NsiUcNmCCT) const;
	int            Chlen(NsiUcIdCCT) const;
	int            MultibyteLen() const;
	int            MultibyteLen(NsiUcNmCCT) const;
	int            MultibyteLen(NsiUcIdCCT) const;
	int            ChlenChk(void) const;
	int            ChlenChk(NsiUcNmCCT) const;
	int            ChlenChk(NsiUcIdCCT) const;
	void           Update(int,int);
	void           Update(int,int,NsiUcNmCCT);
	void           Update(int,int,NsiUcIdCCT);
	void           Update(int,NsiUcChar);
	void           Update(int,const CNsiUcChar&);
	void           Update(int,const CNsiUcChar*);
	void           toLower(void);
	void           toUpper(void);
	double         Atof(void) const;
	int            Atoi(void) const;
	long           Atol(void) const;
	double         Strtod(int*) const;
	long           Strtol(int*,int) const;
	int            Sprintf(const NsiUcStr,...);
	char*          getToChar(char*,int) const;
	char*          getToChar(char*,int,NsiUcNmCCT) const;
	char*          getToChar(char*,int,NsiUcIdCCT) const;
	wchar_t*       getToChar(wchar_t*,int) const;
	wchar_t*       getToChar(wchar_t*,int,NsiUcNmCCT) const;
	wchar_t*       getToChar(wchar_t*,int,NsiUcIdCCT) const;
	char*          getToCharChk(char*,int) const;
	char*          getToCharChk(char*,int,NsiUcNmCCT) const;
	char*          getToCharChk(char*,int,NsiUcIdCCT) const;
	NsiUcStr       getToUcChar(NsiUcStr,int) const;
	void           Append(const char*);
	void           Append(const char*,NsiUcNmCCT);
	void           Append(const char*,NsiUcIdCCT);
	void           Append(const wchar_t*,NsiUcNmCCT);
	void           Append(const wchar_t*,NsiUcIdCCT);
	void           Append(const NsiUcStr);
	void           Append(const CNsiUcStr&);
	void           Append(const CNsiUcStr*);
	void           Append(const char*,int);
	void           Append(const char*,int,NsiUcNmCCT);
	void           Append(const char*,int,NsiUcIdCCT);
	void           Append(const wchar_t*,int,NsiUcNmCCT);
	void           Append(const wchar_t*,int,NsiUcIdCCT);
	void           Append(const NsiUcStr,int);
	void           Append(const CNsiUcStr&,int);
	void           Append(const CNsiUcStr*,int);
	void           Append(int);
	void           Append(int,NsiUcNmCCT);
	void           Append(int,NsiUcIdCCT);
	void           Append(NsiUcChar);
	void           Append(const CNsiUcChar&);
	void           Append(const CNsiUcChar*);
	int            FindFirst(const char*) const;
	int            FindFirst(const char*,NsiUcNmCCT) const;
	int            FindFirst(const char*,NsiUcIdCCT) const;
	int            FindFirst(const NsiUcStr) const;
	int            FindFirst(const CNsiUcStr&) const;
	int            FindFirst(const CNsiUcStr*) const;
	int            FindLast(const char*) const;
	int            FindLast(const char*,NsiUcNmCCT) const;
	int            FindLast(const char*,NsiUcIdCCT) const;
	int            FindLast(const NsiUcStr) const;
	int            FindLast(const CNsiUcStr&) const;
	int            FindLast(const CNsiUcStr*) const;
	int            FindFirst(int) const;
	int            FindFirst(int,NsiUcNmCCT) const;
	int            FindFirst(int,NsiUcIdCCT) const;
	int            FindFirst(NsiUcChar) const;
	int            FindFirst(const CNsiUcChar&) const;
	int            FindFirst(const CNsiUcChar*) const;
	int            FindLast(int) const;
	int            FindLast(int,NsiUcNmCCT) const;
	int            FindLast(int,NsiUcIdCCT) const;
	int            FindLast(NsiUcChar) const;
	int            FindLast(const CNsiUcChar&) const;
	int            FindLast(const CNsiUcChar*) const;
	int            Comp(const char*) const;
	int            Comp(const char*,NsiUcNmCCT) const;
	int            Comp(const char*,NsiUcIdCCT) const;
	int            Comp(const NsiUcStr) const;
	int            Comp(const CNsiUcStr&) const;
	int            Comp(const CNsiUcStr*) const;
	int            Comp(const char*,int) const;
	int            Comp(const char*,int,NsiUcNmCCT) const;
	int            Comp(const char*,int,NsiUcIdCCT) const;
	int            Comp(const NsiUcStr,int) const;
	int            Comp(const CNsiUcStr&,int) const;
	int            Comp(const CNsiUcStr*,int) const;
	int            Compi(const char*) const;
	int            Compi(const char*,NsiUcNmCCT) const;
	int            Compi(const char*,NsiUcIdCCT) const;
	int            Compi(const wchar_t*,NsiUcNmCCT) const;
	int            Compi(const wchar_t*,NsiUcIdCCT) const;
	int            Compi(const NsiUcStr) const;
	int            Compi(const CNsiUcStr&) const;
	int            Compi(const CNsiUcStr*) const;
	int            Compi(const char*,int) const;
	int            Compi(const char*,int,NsiUcNmCCT) const;
	int            Compi(const char*,int,NsiUcIdCCT) const;
	int            Compi(const wchar_t*,int,NsiUcNmCCT) const;
	int            Compi(const wchar_t*,int,NsiUcIdCCT) const;
	int            Compi(const NsiUcStr,int) const;
	int            Compi(const CNsiUcStr&,int) const;
	int            Compi(const CNsiUcStr*,int) const;
	void           Copy(const char*);
	void           Copy(const char*,NsiUcNmCCT);
	void           Copy(const char*,NsiUcIdCCT);
	void           Copy(const wchar_t*);
	void           Copy(const wchar_t*,NsiUcNmCCT);
	void           Copy(const wchar_t*,NsiUcIdCCT);
	void           Copy(const NsiUcStr);
	void           Copy(const CNsiUcStr&);
	void           Copy(const CNsiUcStr*);
	void           Copy(const char*,int);
	void           Copy(const char*,int,NsiUcNmCCT);
	void           Copy(const char*,int,NsiUcIdCCT);
	void           Copy(const wchar_t*,int,NsiUcNmCCT);
	void           Copy(const wchar_t*,int,NsiUcIdCCT);
	void           Copy(const NsiUcStr,int);
	void           Copy(const CNsiUcStr&,int);
	void           Copy(const CNsiUcStr*,int);
	const CNsiUcChar & operator [] (int) const;
	CNsiUcStr&  operator =  (const char*);
	CNsiUcStr&  operator =  (const NsiUcStr);
	CNsiUcStr&  operator =  (const CNsiUcStr &);
	CNsiUcStr&  operator =  (const CNsiUcStr *);
	friend int NRXDBGATE_EXPORT operator == (const CNsiUcStr&, const char*);
	friend int NRXDBGATE_EXPORT operator == (const char*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator == (const CNsiUcStr&, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator == (const CNsiUcStr*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator == (const NsiUcStr, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator == (const CNsiUcStr&, const CNsiUcStr*);
	friend int NRXDBGATE_EXPORT operator == (const CNsiUcStr&, const NsiUcStr);
	friend int NRXDBGATE_EXPORT operator != (const CNsiUcStr&, const char*);
	friend int NRXDBGATE_EXPORT operator != (const char*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator != (const CNsiUcStr&, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator != (const CNsiUcStr*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator != (const NsiUcStr, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator != (const CNsiUcStr&, const CNsiUcStr*);
	friend int NRXDBGATE_EXPORT operator != (const CNsiUcStr&, const NsiUcStr);
	friend int NRXDBGATE_EXPORT operator >  (const CNsiUcStr&, const char*);
	friend int NRXDBGATE_EXPORT operator >  (const char*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator >  (const CNsiUcStr&, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator >  (const CNsiUcStr*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator >  (const NsiUcStr, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator >  (const CNsiUcStr&, const CNsiUcStr*);
	friend int NRXDBGATE_EXPORT operator >  (const CNsiUcStr&, const NsiUcStr);
	friend int NRXDBGATE_EXPORT operator <  (const CNsiUcStr&, const char*);
	friend int NRXDBGATE_EXPORT operator <  (const char*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator <  (const CNsiUcStr&, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator <  (const CNsiUcStr*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator <  (const NsiUcStr, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator <  (const CNsiUcStr&, const CNsiUcStr*);
	friend int NRXDBGATE_EXPORT operator <  (const CNsiUcStr&, const NsiUcStr);
	friend int NRXDBGATE_EXPORT operator >= (const CNsiUcStr&, const char*);
	friend int NRXDBGATE_EXPORT operator >= (const char*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator >= (const CNsiUcStr&, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator >= (const CNsiUcStr*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator >= (const NsiUcStr, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator >= (const CNsiUcStr&, const CNsiUcStr*);
	friend int NRXDBGATE_EXPORT operator >= (const CNsiUcStr&, const NsiUcStr);
	friend int NRXDBGATE_EXPORT operator <= (const CNsiUcStr&, const char*);
	friend int NRXDBGATE_EXPORT operator <= (const char*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator <= (const CNsiUcStr&, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator <= (const CNsiUcStr*, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator <= (const NsiUcStr, const CNsiUcStr&);
	friend int NRXDBGATE_EXPORT operator <= (const CNsiUcStr&, const CNsiUcStr*);
	friend int NRXDBGATE_EXPORT operator <= (const CNsiUcStr&, const NsiUcStr);
#ifdef ibmrs
	void* operator new(unsigned long);
#else
	void* operator new(size_t);
#endif
	void operator delete(void*);
#if defined(__WATCOMC__)
	void* operator new[](unsigned int);
	void operator delete[](void*);
#endif
private:
	void *pUcStrData;
};

typedef enum {
	kOpNodeUndefined = 0,       /* Undefined node */

	/* Boolean operations */
	kOpNot,                     /* Not */
	kOpOr,                      /* Or */
	kOpAnd,                     /* And */
	kOpTest,                    /* Boolean test */

	/* Comparision predicate */
	kOpNull,                    /* is Null */
	kOpGtr,                     /* > */
	kOpGeq,                     /* >= */
	kOpEq,                      /* = */
	kOpLeq,                     /* <= */
	kOpLss,                     /* < */
	kOpNeq                      /* <> */
} ENsiCompType;

//struct ListItem {
//  struct ListItem *next;
//  CNsiObject *item;
//};


typedef ULONG_PTR NSILISTPOS;   // List position
//////////////////////////////////////////////////////////////////////////
// CNsiUcChar
class CNsiUcChar {
public:
	NsiUcChar Symbol;
	int       isUpper(void) const;
	int       isLower(void) const;
	int       isAlpha(void) const;
	int       isDigit(void) const;
	int       isXdigit(void) const;
	int       isSpace(void) const;
	int       isPunct(void) const;
	int       isAlnum(void) const;
	int       isGraph(void) const;
	int       isPrint(void) const;
	int       isCntrl(void) const;
	void      setUpper(void);
	void      setLower(void);
	void      setChar(int,NsiUcIdCCT);
	void      setChar(int,NsiUcNmCCT);
	void      setChar(NsiUcChar);
	int       getChar(void) const;
	int       getChar(NsiUcIdCCT) const;
	int       getChar(NsiUcNmCCT) const;
	NsiUcChar getUcChar(void) const;
	CNsiUcChar Upper(void) const;
	CNsiUcChar Lower(void) const;
	int  Comp(int) const;
	int  Comp(int,NsiUcIdCCT) const;
	int  Comp(int,NsiUcNmCCT) const;
	int  Comp(NsiUcChar) const;
	int  Comp(CNsiUcChar*) const;
	int  Comp(const CNsiUcChar&) const;
	int  Compi(int) const;
	int  Compi(int,NsiUcIdCCT) const;
	int  Compi(int,NsiUcNmCCT) const;
	int  Compi(NsiUcChar) const;
	int  Compi(CNsiUcChar*) const;
	int  Compi(const CNsiUcChar&) const;
	CNsiUcChar&  operator =  (const char);
	CNsiUcChar&  operator =  (const NsiUcChar);
	CNsiUcChar&  operator =  (const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator == (const CNsiUcChar&, const char);
	friend NRXDBGATE_EXPORT int operator == (const char, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator == (const CNsiUcChar&, const NsiUcChar);
	friend NRXDBGATE_EXPORT int operator == (const NsiUcChar, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator == (const CNsiUcChar&, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator != (const CNsiUcChar&, const char);
	friend NRXDBGATE_EXPORT int operator != (const char, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator != (const CNsiUcChar&, const NsiUcChar);
	friend NRXDBGATE_EXPORT int operator != (const NsiUcChar, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator != (const CNsiUcChar&, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator >  (const CNsiUcChar&, const char);
	friend NRXDBGATE_EXPORT int operator >  (const char, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator >  (const CNsiUcChar&, const NsiUcChar);
	friend NRXDBGATE_EXPORT int operator >  (const NsiUcChar, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator >  (const CNsiUcChar&, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator <  (const CNsiUcChar&, const char);
	friend NRXDBGATE_EXPORT int operator <  (const char, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator <  (const CNsiUcChar&, const NsiUcChar);
	friend NRXDBGATE_EXPORT int operator <  (const NsiUcChar, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator <  (const CNsiUcChar&, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator >= (const CNsiUcChar&, const char);
	friend NRXDBGATE_EXPORT int operator >= (const char, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator >= (const CNsiUcChar&, const NsiUcChar);
	friend NRXDBGATE_EXPORT int operator >= (const NsiUcChar, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator >= (const CNsiUcChar&, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator <= (const CNsiUcChar&, const char);
	friend NRXDBGATE_EXPORT int operator <= (const char, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator <= (const CNsiUcChar&, const NsiUcChar);
	friend NRXDBGATE_EXPORT int operator <= (const NsiUcChar, const CNsiUcChar&);
	friend NRXDBGATE_EXPORT int operator <= (const CNsiUcChar&, const CNsiUcChar&);
#ifdef ibmrs
	void* operator new(unsigned long);
#else
	void* operator new(size_t);
#endif
	void operator delete(void*);
#if defined(__WATCOMC__)
	void* operator new[](unsigned int);
	void operator delete[](void*);
#endif
};


//////////////////////////////////////////////////////////////////////////
// CNsiExceptionHandler
class CNsiExceptionHandler {
public:
	CNsiExceptionHandler(void);
	~CNsiExceptionHandler(void);
	CNsiException*        pException;
	CNsiExceptionHandler* pPrevHandler;
	ENsiBoolean           wasThrown;
};

//////////////////////////////////////////////////////////////////////////
// CNsiObject
class CNsiObject {
public:
	        CNsiObject                (void);
	virtual ~CNsiObject               (void);
	        void*         operator new    (size_t);
	        void          operator delete (void*);
#if defined(__WATCOMC__)
	        void*         operator new[]    (unsigned int);
	        void          operator delete[] (void*);
#endif
	 virtual CNsiObject  * duplicate  (void) const;
	 virtual void          Clear      (void);
	 virtual unsigned long packSize        (void) const;
	 virtual unsigned long packTo          (CNsiObjPack *) const;
	 virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	 virtual unsigned long packValueSize   (void) const;
	 virtual unsigned long packValueTo     (CNsiObjPack *) const;
	 virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *);
};


//////////////////////////////////////////////////////////////////////////
// CNsiException
class CNsiException : public CNsiObject {
	friend class CNsiSQLObject;
public:
	                        CNsiException (void);
	virtual                    ~CNsiException (void);
	int                        CondQty    (void) const;
	NsiError                Err        (int d = 0) const;
	CNsiUcStr        *        ErrMsg     (int d = 0) const;
	char            *        SQLSTATE   (int d = 0) const;
	int                        ErrPosition (void) const;
	ENsiBoolean                getDiagPar (int, NsiDiag, integer *) const;
	ENsiBoolean                getDiagPar (int, NsiDiag, CNsiUcStr *) const;
	ENsiBoolean                setErr      (NsiError);
	ENsiBoolean                setErrMsg   (const CNsiUcStr &);
	ENsiBoolean                setSQLSTATE (const char *);
	ENsiBoolean                setDiagPar    (NsiDiag, integer);
	ENsiBoolean                setDiagPar    (NsiDiag, const CNsiUcStr &);
	ENsiBoolean                pushCond    (void);
	ENsiBoolean                flushCond    (void);
	void            *          getDiagData (void) const;
	void                    setErrPosition (int);
	virtual CNsiObject *    duplicate    (void) const;
private:
	void        *            pExceptionBody;
};


//////////////////////////////////////////////////////////////////////////
// CNsiSQLObject
class CNsiSQLObject : public CNsiObject {
	friend class CNsiCsr;
	friend class CNsiExecStm;
	friend class CNsiBinding;
public:
protected:
	                            CNsiSQLObject   ();
protected:
	virtual ENsiBoolean         setErr      (ENsiError);
	virtual ENsiBoolean         setErrMsg   (const CNsiUcStr &);
	virtual ENsiBoolean         setSQLSTATE (const char *);
	virtual ENsiBoolean         setDiagPar (ENsiDiag, integer);
	virtual ENsiBoolean         setDiagPar (ENsiDiag, const CNsiUcStr &);
	virtual ENsiBoolean            pushCond   (void);
	virtual ENsiBoolean            flushCond  (void);
	virtual ENsiBoolean            pushErr    (ENsiError);
	virtual ENsiBoolean            pushHResult(HRESULT);
public:
	virtual                     ~CNsiSQLObject  ();
	ENsiStatement               StmType         (void) const;
	LONG_PTR                    RowCount        (void) const;
	virtual ENsiBoolean         IsRowset        (void) const;
	virtual int                 ErrPosition     (void) const;
	virtual int                 CondQty         (void) const;
	virtual ENsiError           Err             (int d = 0) const;
	virtual CNsiUcStr       *   ErrMsg          (int d = 0);
	virtual char            *   SQLSTATE        (int d = 0);
	virtual ENsiBoolean         getDiagPar      (int d,
	                                             ENsiDiag,
	                                             integer *) const;
	virtual ENsiBoolean         getDiagPar      (int d,
	                                             ENsiDiag,
	                                             CNsiUcStr *) const;
	ENsiBoolean                 DBMS            (CNsiUcStr *) const;
	ENsiBoolean                 SQLObject       (CNsiUcStr *) const;
	ENsiBoolean                 DrvMessage      (CNsiUcStr *) const;
	ENsiBoolean                 CheckOp         (ulong);
	virtual ENsiBoolean         GetStatus       (ENsiStatInfo, ULONG_PTR *);
	const char             *    Version         (void) const;
protected:
	ENsiBoolean                 isInit      (void) const;
	ENsiBoolean                 InitErrorInfo (HRESULT, IUnknown *, GUID);
	void                        ReleaseErrorInfo ();
	void                        InheritStatusInfo (const CNsiSQLObject &);
protected:
	IErrorInfo          *       m_pIErrorInfo;
	HRESULT                     m_HResult;
private:
	static const char   *       m_pNsiVersion;
	CNsiException               m_Except;
protected:
	ENsiBoolean                 m_CSP;
protected:
	ENsiStatement               m_eStmType;
	LONG_PTR                m_lRowCount;
	CNsiDSProperties       *    m_pDSProperties;
};


//////////////////////////////////////////////////////////////////////////
// CNsiAppl
class CNsiAppl: public CNsiSQLObject {
	friend class CNsiSession;
	friend class CNsiEnumerator;
	friend class CNsiCsr;
public:
	                            CNsiAppl        ();
	  virtual                   ~CNsiAppl       ();
	  ENsiBoolean               Init            (void);
	  ENsiBoolean               Term            (void);
	  ENsiBoolean               Abort           (void);
	  ENsiBoolean               DisconnectAll   (void);
protected:
	  ENsiBoolean               addConnection   (CNsiSession *);
	  ENsiBoolean               removeConnection(CNsiSession *);
//private:
//      ENsiBoolean               rollbackAll     (void);
//private:
//      IClassFactory        *        m_pIClassFactory;
//      IDataInitialize    *        m_pIDataInitialize;
//      IDataConvert        *        m_pIDataConvert;
//      CNsiObject        *       m_pSessions;
};


//////////////////////////////////////////////////////////////////////////
// CNsiSession
class CNsiSession: public CNsiSQLObject {
	friend class CNsiStm;
	friend class CNsiCsr;
	friend class CNsiExecStm;
	friend class CNsiAppl;
	friend class CNsiCsrTable;
	friend class CNsiCsrInfSchema;
	friend class CNsiCsrRegTable;
public:
	                        CNsiSession         (CNsiAppl *);
	virtual                 ~CNsiSession        ();
	ENsiBoolean             Connect             (const CNsiUcStr & LinkFile,
	                                             const CNsiUcStr & Username,
	                                             const CNsiUcStr & Password,
	                                             ENsiBoolean       fPrompt = kNsiFalse);
	ENsiBoolean                ConnectIniString    (const CNsiUcStr & IniString);
	ENsiBoolean                GetConnectionString (CNsiUcStr *);
	ENsiBoolean             Disconnect          (void);
	ENsiBoolean             SetCatalog          (const CNsiUcStr &);
	ENsiBoolean             SetSchema           (const CNsiUcStr &);
	ENsiBoolean             SetNames            (const CNsiUcStr &);
	ENsiBoolean             SetTimeZone         (const CNsiDT &);
	ENsiBoolean             SetTimeZone         (void);
	ENsiBoolean             SetAuthor           (const CNsiUcStr &);
	ENsiBoolean             SetTrans            (ENsiTILevel, ENsiTMode, uint dSize = 64);
	ENsiBoolean             DeferrConstr        (CNsiIdent * cnst = 0);
	ENsiBoolean             ImmConstr           (CNsiIdent * cnst = 0);
	ENsiBoolean             Commit              (void);
	ENsiBoolean             Rollback            (void);
	const CNsiUcStr      &  Name                (void) const;
	virtual ENsiBoolean     GetStatus            (ENsiStatInfo, ULONG_PTR *);
protected:
	ENsiBoolean             Disconnect          (CNsiObject *);
	ENsiBoolean                GetCatalog            (CNsiUcStr *);
private:
	virtual CNsiObject  *   duplicate           (void) const;
	ENsiBoolean                CreateSession        (IDBInitialize *);
	ENsiBoolean             Execute             (const CNsiUcStr &);
	ENsiBoolean                CheckForNotNull        (ENsiInfSchTab, int);
	ENsiBoolean                CanRetrieveCatalogs    (void);
	ENsiBoolean                CanRetrieveSchemas    (void);
	void                    GetProviderTypes    (void);
	ENsiBoolean                GetStatusInfo         ();
	void                    AttachStm            (CNsiExecStm *);
	void                    DetachStm            (CNsiExecStm *);
	void                    DetachAllStm         (void);
	void                    DeallocateAllStm    (void);
	void                    AttachCsr            (CNsiCsr *);
	void                    DetachCsr             (CNsiCsr *);
	void                    DetachAllCsr         (void);
	ENsiBoolean                HasOpenedObjects    (void);
private:
	CNsiAppl            *   m_pAppl;
	CNsiUcStr               m_LinkFileName ;
	CNsiUcStr                m_ConnectionString;
	IUnknown            *   m_pISession;
	CNsiUcStr                m_ucCatalog;
	ULONG                   m_BLOBStorage;
	CNsiList            *    m_pStms;
	CNsiList            *    m_pCsrs;
};


//////////////////////////////////////////////////////////////////////////
// CNsiStm
class CNsiStm: public CNsiSQLObject {
	friend class CNsiSession;
public:
	                            CNsiStm         (void);
	virtual                     ~CNsiStm        (void);
	        void                SetSession      (CNsiSession *);
	virtual int                 ParamQty        (void) const;
	virtual CNsiParameter   *   ParamDsc        (int) const;
	virtual ENsiBoolean         Bind            (int, CNsiData *);
	virtual ENsiBoolean         Bind            (int, void *, short *,
	                                             int, ENsiHostType);
	virtual ENsiBoolean         Bind            (const CNsiIdent &, CNsiData *);
	virtual ENsiBoolean         Bind            (const CNsiIdent &, void *, short *,
	                                             int, ENsiHostType);
	virtual int                 ColQty          (void) const;
	virtual CNsiColumn *        ColDsc          (int) const;
	virtual ENsiBoolean         Sob             (int, CNsiData *);
	virtual ENsiBoolean         Sob             (int, void *, short *,
	                                             int, ENsiHostType);
	virtual ENsiBoolean         Cvl             (int, CNsiData *);
	virtual ENsiBoolean         Cvl             (int, void *, short *,
	                                             int, ENsiHostType);
protected:
	ENsiBoolean                 CvlInt          (int, CNsiData *) const;
	ENsiBoolean                 pInput          (void);
	ENsiBoolean                    InitColsDsc        ();
protected:
	CNsiBinding             *   m_pInput;
	CNsiBinding             *   m_pOutput;
	CNsiSession             *   m_pSession;
	ULONG_PTR                   m_lColNumber;
	DBCOLUMNINFO            *   m_pColumnInfo;
	OLECHAR                 *   m_pStringBuff;
	CNsiRow                 *   m_pNsiRow;
};


//////////////////////////////////////////////////////////////////////////
// CNsiExecStm
class CNsiExecStm: public CNsiStm {
	friend class CNsiCsr;
	friend class CNsiSession;
public:
	                            CNsiExecStm         (void);
	virtual                     ~CNsiExecStm        (void);
	virtual ENsiBoolean         IsRowset            (void) const;
	virtual ENsiBoolean         Prepare             (CNsiSession *,
	                                                 const CNsiUcStr &,
	                                                 ENsiBoolean trans = kNsiTrue);
	virtual ENsiBoolean         Deallocate          (void);
	virtual ENsiBoolean         Execute             (void);
	virtual ENsiBoolean         ImmediateExecute    (CNsiSession *,
	                                                 const CNsiUcStr &,
	                                                 ENsiBoolean trans = kNsiTrue);
	ENsiBoolean                    Cancel              (void);
	virtual int                 ParamQty            (void) const;
	virtual CNsiParameter   *   ParamDsc            (int) const;
	virtual ENsiBoolean         Bind                (int, CNsiData *);
	virtual ENsiBoolean         Bind                (int, void *, short *, int, ENsiHostType);
	virtual ENsiBoolean         Bind                (const CNsiIdent &, CNsiData *);
	virtual ENsiBoolean         Bind                (const CNsiIdent &, void *, short *, int, ENsiHostType);
	virtual int                 ColQty              (void) const;
	virtual CNsiColumn *        ColDsc              (int) const;
	virtual ENsiBoolean            GetStatus            (ENsiStatInfo, ULONG_PTR *);
private:
	virtual CNsiObject      *   duplicate           (void) const;
	ENsiBoolean                 Prepare             (void);
	ENsiBoolean                    IsPrepared            (void) const;
	void                        AttachCsr            (CNsiCsr *);
	void                        DetachCsr            (CNsiCsr *);
	void                        DetachAllCsr         (void);
	void                        CloseAllCsr            (void);
protected:
	ICommandText            *   m_pICommand;
	ULONG                       m_lParNumber;
	DBPARAMINFO             *   m_pParamInfo;
	OLECHAR                 *   m_pStringBuffParam;
	CNsiList                *    m_pCsrs;
};

//////////////////////////////////////////////////////////////////////////
// CNsiIdent
class CNsiIdent : public CNsiObject {
public:
	                        CNsiIdent       (void);
	                        CNsiIdent       (const char *);
	                        CNsiIdent       (const NsiUcStr);
	                        CNsiIdent       (const CNsiUcStr &);
	                        CNsiIdent       (const CNsiUcStr &, const CNsiUcStr &);
	                        CNsiIdent       (const CNsiIdent &);
	virtual                 ~CNsiIdent      (void);
	void                    set             (ENsiBoolean,
	                                         const CNsiUcStr &,
	                                         const CNsiUcStr &);
	void                    setDelimited    (ENsiBoolean);
	void                    setDelimited    (void);
	void                    setCharSet      (const CNsiUcStr &);
	void                    setBody         (const CNsiUcStr &, ENsiBoolean fParse = kNsiTrue);
	ENsiBoolean             isDelimited     (void) const;
	const CNsiUcStr         & CharSet       (void) const;
	const CNsiUcStr         & Body          (void) const;
	int                     Length          (void) const;
	virtual void            Clear           (void);
	CNsiIdent       &       operator=       (const CNsiIdent &);
	CNsiIdent       &       operator=       (const CNsiUcStr &);
	int                     operator==      (const CNsiIdent &) const;
	void                    ToString        (CNsiUcStr *) const;
	virtual CNsiObject   *  duplicate       (void) const;
	virtual unsigned long   packSize        (void) const;
	virtual unsigned long   packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean     unpackFrom      (CNsiObjPack *);
private:
	ENsiBoolean             isDelim;
	CNsiUcStr               charset;
	CNsiUcStr               ident;
};

//////////////////////////////////////////////////////////////////////////
// CNsiCsr
class CNsiCsr: public CNsiStm {
	friend class CNsiExecStm;
public:
	                            CNsiCsr             (void);
	virtual                     ~CNsiCsr            (void);
	ENsiBoolean                 Allocate            (CNsiExecStm * csrspec,
	                                                 const CNsiIdent & csrname,
	                                                 ENsiCurScr sc = kNsiNonScroll,
	                                                 ENsiCurSns sn = kNsiSnsUndef,
	                                                 ENsiBoolean upd = kNsiUnknown,
	                                                 ENsiBoolean fIns = kNsiFalse);
	virtual int                 ParamQty            (void) const;
	virtual CNsiParameter   *   ParamDsc            (int) const;
	virtual ENsiBoolean         Bind                (int, CNsiData *);
	virtual ENsiBoolean         Bind                (int, void *, short *, int, ENsiHostType);
	virtual ENsiBoolean         Bind                (const CNsiIdent &, CNsiData *);
	virtual ENsiBoolean         Bind                (const CNsiIdent &, void *, short *, int, ENsiHostType);
	virtual ENsiBoolean         Sob                 (int, CNsiData *);
	virtual ENsiBoolean         Sob                 (int, void *, short *, int, ENsiHostType);
	virtual ENsiBoolean         Open                (void);
	virtual ENsiBoolean         Close               (void);
	ENsiBoolean                    Cancel              (void);
	virtual ENsiBoolean         Fetch               (void);
	virtual ENsiBoolean         FetchPrior          (void);
	virtual ENsiBoolean         FetchFirst          (void);
	virtual ENsiBoolean         FetchLast           (void);
	virtual ENsiBoolean         FetchRelative       (long);
	virtual ENsiBoolean         FetchAbsolute       (long);
	virtual ENsiBoolean         CheckCCondition     (CNsiData **);
	CNsiRow             *       getCurrentRow       (void);
	virtual ENsiBoolean         Delete              (void);
	virtual ENsiBoolean         Update              (const CNsiRow &);
	virtual ENsiBoolean            Insert                (const CNsiRow &);
	virtual ENsiBoolean            Insert                (void);
	virtual int                 ColQty              (void) const;
	virtual CNsiColumn *        ColDsc              (int) const;
	virtual ENsiBoolean         Cvl                 (int, CNsiData *);
	virtual ENsiBoolean         Cvl                 (int, void *, short *,
	                                                 int, ENsiHostType);
	virtual ENsiBoolean            GetStatus            (ENsiStatInfo, ULONG_PTR *);
	virtual ENsiBoolean         IsRowset            (void) const;
	virtual ENsiBoolean         is_updatable        (void) const;
	virtual ENsiBoolean         is_insertable       (void) const;
	virtual ENsiBoolean         is_scrollable       (void) const;
	virtual ENsiBoolean         is_insensitive      (void) const;
	virtual ENsiBoolean         is_open             (void) const;
	virtual ENsiCurPos          position            (void) const;
private:
	virtual CNsiObject  *       duplicate           (void) const;
protected:
	ENsiBoolean                 InitOutputBind      ();
	ENsiBoolean                 MakeCursorProp      (DBPROPSET  * pRowsetPropSet);
	ENsiBoolean                 QueryCursorProp     (void);
	ENsiBoolean                    SobValues           (void);
	ENsiBoolean                    Svl                 (int);
	ENsiBoolean                 ReadData            (void);
	ENsiBoolean                 GetColValue         (int, CNsiData *);
	ENsiBoolean                    StoreValueFromDBType(CNsiData *, DBTYPE, void *);
	ENsiBoolean                    InitAccessor        (ULONG_PTR, DBCOLUMNINFO *, const CNsiRow &,
	                                                    ULONG *, DBBINDING    **,    HACCESSOR *,
	                                                    ENsiBoolean);
	ENsiBoolean                    DoChangeErrors        (HRESULT hr, ULONG, DBBINDING *);
	ENsiBoolean                 UpdateRow           (ULONG_PTR, DBCOLUMNINFO *, const CNsiRow &);
	ENsiBoolean                 InsertRow           (ULONG_PTR, DBCOLUMNINFO *, const CNsiRow &);
protected:
	CNsiExecStm         *       m_pCursorSpec;
	IRowset             *       m_pIRowset;
	IRowsetChange       *       m_pIRowsetChange;
	IRowsetLocate       *       m_pIRowsetLocate;
	IAccessor           *       m_pIAccessor;
	HACCESSOR                   m_hAccessor;
	DWORD_PTR                   m_lRowCount;
	DWORD                       m_lCurrRow;
	//IDataConvert        *        m_pIDataConvert;
	HROW                *       m_rghRows;
	BYTE                *       m_pData;
	DWORD_PTR                   m_dwOffset;
	DBBINDING           *       m_rgBind;
	int                         m_iNumBind;
	ENsiBoolean                 m_fDataRead;
	ENsiBoolean                    m_fBlkStorObj;
	ENsiBoolean                 m_fBLOBExpected;
	IUnknown            *        m_pIUnknown;
	CNsiIdent                   m_CsrName;
	ENsiCurScr                  m_ScrFlag;
	ENsiCurSns                  m_SnsFlag;
	ENsiBoolean                 m_fUpd;
	ENsiBoolean                 m_fIns;
	ENsiBoolean                    m_fOwnInserts;
	ENsiBoolean                    m_fOwnUpdates;
	ENsiBoolean                    m_fIsOpen;
	ENsiCurPos                  m_CsrPos;
	ULONG_PTR                   m_ulColumns;
	ULONG                       m_ulCurrentRowNo;
	ULONG                       m_ulMaxRowNo;
	ULONG                       m_ulRows;
	CNsiTCCond              *   m_pTCCond;
};


//////////////////////////////////////////////////////////////////////////
// CNsiCsrTable
class CNsiCsrTable : public CNsiCsr {
public:
	                            CNsiCsrTable        (void);
	virtual                     ~CNsiCsrTable       (void);
	virtual int                 ColQty              (void) const;
	virtual CNsiColumn *        ColDsc              (int) const;
	virtual ENsiBoolean         Open                (void);
	virtual ENsiBoolean         Close               (void);
	virtual ENsiBoolean         Update              (const CNsiRow &);
	virtual ENsiBoolean         Cvl                 (int, CNsiData *);
	virtual ENsiBoolean         Cvl                 (int, void *, short *,
	                                                 int, ENsiHostType);
	virtual ENsiBoolean         SetFilter           (CNsiTCCond *);
	virtual ENsiBoolean         SetOrder            ();
protected:
	void                        DeallocCsr          (void);
protected:
};


//////////////////////////////////////////////////////////////////////////
// CNsiCsrRegTable
class CNsiCsrRegTable : public CNsiCsrTable {
public:
	                            CNsiCsrRegTable     (void);
	virtual                     ~CNsiCsrRegTable    (void);
	ENsiBoolean                 Allocate            (CNsiSession * ses,
	                                                 const CNsiUcStr & catalog,
	                                                 const CNsiUcStr & schema,
	                                                 const CNsiUcStr & table,
	                                                 ENsiCurScr    sc = kNsiNonScroll,
	                                                 ENsiBoolean   upd = kNsiUnknown
	                                                 );
protected:
	CNsiUcStr                   m_pCatalog ;
	CNsiUcStr                   m_pSchema;
	CNsiUcStr                   m_pName;
};


//////////////////////////////////////////////////////////////////////////
// CNsiCsrInfSchema
class CNsiCsrInfSchema : public CNsiCsrTable {
public:
	                            CNsiCsrInfSchema    (void);
	virtual                     ~CNsiCsrInfSchema   (void);
	ENsiBoolean                 Allocate            (CNsiSession * ses,
	                                                 ENsiInfSchTab ischema,
	                                                 ENsiCurScr    sc = kNsiNonScroll
	                                                 );
protected:
	ENsiInfSchTab               m_istType;
};

//////////////////////////////////////////////////////////////////////////
// CNsiEnumerator
class CNsiEnumerator: public CNsiCsrTable {
public:
	                            CNsiEnumerator      (void);
	virtual                     ~CNsiEnumerator     (void);
	ENsiBoolean                 Allocate            (CNsiAppl *);
	ENsiBoolean                 Allocate            (CNsiAppl *, CLSID & clsidEnum);
	void                        SetFilter           (ENsiDataSourceType dst,
	                                                 const CNsiUcStr & pName,
	                                                 ENsiBoolean isParent = kNsiUnknown);
	virtual ENsiBoolean         Fetch               (void);
protected:
	CLSID                       m_clsidEnum;
	ENsiDataSourceType          m_eDsType;
	CNsiUcStr                   m_pName;
	ENsiBoolean                 m_fIsParent;
};

//////////////////////////////////////////////////////////////////////////
// CNsiList
class CNsiList: public CNsiObject {
public:
	                        CNsiList ();
	 virtual              ~ CNsiList ();
	         ENsiBoolean    addFirst (CNsiObject *);
	         ENsiBoolean    addLast  (CNsiObject *);
	         ENsiBoolean    del         (CNsiObject *);
	         ENsiBoolean    del         (int);
	         ENsiBoolean    detach      (CNsiObject *);
	         ENsiBoolean    detach      (int);
	         ENsiBoolean    delFirst    (void);
	         ENsiBoolean    delLast     (void);
	         ENsiBoolean    delTail     (int);
	         ENsiBoolean    detachFirst (void);
	         ENsiBoolean    detachLast  (void);
	         ENsiBoolean    detachTail  (int);
	         ENsiBoolean    replace     (int,
	                                     CNsiObject *);
	         ENsiBoolean    overwrite   (int,
	                                     CNsiObject *);
	         CNsiObject   * first      (void);
	         CNsiObject   * next       (void);
	         CNsiObject   * next       (NSILISTPOS);
	         CNsiObject   * last       (void);
	         int            qnty       (void) const;
	         void           detachAll  (void);
	         NSILISTPOS     position   (void) const;
	         CNsiObject   * getCurrent (void) const;
	         CNsiObject   * getAt      (NSILISTPOS) const;
	         CNsiObject    *operator [] (int);
	 virtual  CNsiObject   *duplicate () const;
	 virtual  void          Clear     (void);
private:
	 //struct ListItem *head;
	 //struct ListItem *tail;
	 //struct ListItem *current;
};

//////////////////////////////////////////////////////////////////////////
// CNsiTACond
class CNsiTACond: public CNsiObject {
	friend class CNsiTCCond;
public:
	                            CNsiTACond          (void);
	                            CNsiTACond          (const CNsiTACond &);
	virtual                      ~CNsiTACond        (void);
	virtual CNsiObject      *   duplicate           (void) const;
	CNsiData                *   m_pData;
	int                         m_cColnum;
	ENsiCompType                m_CompOp;
};

//////////////////////////////////////////////////////////////////////////
// CNsiTCCond
class CNsiTCCond: public CNsiObject {
public:
	                            CNsiTCCond          (void);
	                            CNsiTCCond          (int);
	                            CNsiTCCond          (const CNsiTCCond &);
	virtual                     ~CNsiTCCond         (void);
	        int                 Count               (void) const;
	        void                Append              (const CNsiTACond &);
	        CNsiTACond      &   operator []         (int);
	virtual CNsiObject      *   duplicate           (void) const;
private:
	int                         m_cQnty;
	CNsiList                    m_Conds;
};


//////////////////////////////////////////////////////////////////////////
// CNsiData
class CNsiData : public CNsiObject {
	friend class CNsiColumn;
public:
	        CNsiData  (void);
	virtual ~CNsiData (void);
	virtual ENsiDataType    Type                (void) const = 0;
	virtual ENsiDTType      DateTimeType        (void) const;
	virtual ENsiIType       IntervalType        (void) const;
	virtual int             ImplDataType        (void) const;
	virtual uint            Length              (void) const;
	virtual uint            Precision           (void) const;
	virtual uint            Scale               (void) const;
	virtual uint            TimePrec            (void) const;
	virtual uint            TimeStampPrec       (void) const;
	virtual uint            LeadFieldPrec       (void) const;
	virtual uint            FracSecPrec         (void) const;
	virtual uint            ReturnLength        (void) const;
	virtual ENsiBoolean     is_numeric          (void) const;
	virtual ENsiBoolean     is_exactnumeric     (void) const;
	virtual ENsiBoolean     is_approxnumeric    (void) const;
	virtual ENsiBoolean     is_character        (void) const;
	virtual ENsiBoolean     is_binary           (void) const;
	virtual ENsiBoolean     is_datetime         (void) const;
	virtual ENsiBoolean     is_interval         (void) const;
	virtual ENsiBoolean     is_yminterval       (void) const;
	virtual ENsiBoolean     is_dtinterval       (void) const;
	virtual ENsiBoolean     is_implement        (void) const;
	virtual ENsiBoolean     is_comparable       (const CNsiData *) const;
	virtual ENsiBoolean     is_storable         (const CNsiData *) const;
	virtual ENsiBoolean     is_castable         (const CNsiData *) const;
	virtual CNsiData *      checkAdd            (const CNsiData *) const;
	virtual CNsiData *      checkSub            (const CNsiData *) const;
	virtual CNsiData *      checkMul            (const CNsiData *) const;
	virtual CNsiData *      checkDiv            (const CNsiData *) const;
	virtual CNsiData *      checkCat            (const CNsiData *) const;
	virtual CNsiData *      checkSet            (const CNsiData *) const;
	virtual ENsiBoolean     isEqualTo           (const CNsiData &) const;
	virtual ENsiBoolean     isGreaterThan       (const CNsiData &) const;
	virtual CNsiImplDefFunc *  getFuncDsc       (const CNsiIdent &, const CNsiRow &) const;
	virtual void            setNull             (void);
	virtual ENsiBoolean     isNull              (void) const;
	virtual ENsiBoolean     storeValue          (real);
	virtual ENsiBoolean     storeValue          (integer);
	virtual ENsiBoolean     storeValue          (smallint);
	virtual ENsiBoolean     storeValue          (char *, uint);
	virtual ENsiBoolean     storeValue          (const CNsiUcStr &);
	virtual ENsiBoolean     storeValue          (char *, uint, uint *);
	virtual ENsiBoolean     storeValue          (const CNsiData &);
	virtual ENsiBoolean     storeValue          (const NsiUcStr);
	virtual ENsiBoolean        storeValue            (const DECIMAL &);
	virtual ENsiBoolean        storeValue            (const DB_NUMERIC *);
	virtual ENsiBoolean        storeValue            (const DBDATE *);
	virtual ENsiBoolean        storeValue            (const DBTIME *);
	virtual ENsiBoolean        storeValue            (const DBTIMESTAMP *);
	virtual ENsiBoolean     getValue            (real *) const;
	virtual ENsiBoolean     getValue            (integer *) const;
	virtual ENsiBoolean     getValue            (smallint *) const;
	virtual ENsiBoolean     getValue            (char *, uint) const;
	virtual ENsiBoolean     getValue            (CNsiUcStr *) const;
	virtual ENsiBoolean     getValue            (char *, uint, uint *) const;
	virtual ENsiBoolean     getValue            (NsiUcStr, uint) const;
	virtual ENsiBoolean     getValue            (CNsiData &) const;
	virtual ENsiBoolean        getValue            (DECIMAL *) const;
	virtual ENsiBoolean        getValue            (DB_NUMERIC *) const;
	virtual ENsiBoolean        getValue            (DBDATE *) const;
	virtual ENsiBoolean        getValue            (DBTIME *) const;
	virtual ENsiBoolean        getValue            (DBTIMESTAMP *) const;
	virtual ENsiBoolean     SQLType             (CNsiUcStr *) const = 0;
	virtual ENsiBoolean     SQLLiteral          (CNsiUcStr *) const = 0;
	static CNsiData *       MapColumnInfoToNsi  (DBCOLUMNINFO * pColumnInfo);
	static CNsiData *       MapParamInfoToNsi    (DBPARAMINFO * pParamInfo);
	virtual DBCOLUMNINFO *  MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO *   MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual CNsiObject*     duplicate           (void) const = 0;
	virtual void            Clear               (void);
protected:
	ENsiBoolean             isnull;
};

//////////////////////////////////////////////////////////////////////////
// CNsiNum
class CNsiNum : public CNsiData {
	friend class CNsiLex;
protected:
	                            CNsiNum ();
public:
	virtual                        ~CNsiNum ();
	virtual uint                Precision       (void) const;
	virtual uint                Scale           (void) const;
	    virtual ENsiBoolean     is_numeric      (void) const;
	virtual ENsiBoolean         is_exactnumeric (void) const;
	virtual ENsiBoolean         is_approxnumeric(void) const;
	virtual ENsiBoolean         is_comparable   (const CNsiData *) const;
	virtual ENsiBoolean         is_storable     (const CNsiData *) const;
	virtual ENsiBoolean         is_castable     (const CNsiData *) const;
	virtual CNsiData    *       checkAdd        (const CNsiData *) const;
	virtual CNsiData    *       checkSub        (const CNsiData *) const;
	virtual CNsiData    *       checkMul        (const CNsiData *) const;
	virtual CNsiData    *       checkDiv        (const CNsiData *) const;
	virtual integer             intValue        (void) const;
	virtual real                realValue       (void) const;
	virtual int                 operator>  (const CNsiSmallInt &) const;
	virtual int                 operator>  (const CNsiInt &)      const;
	virtual int                 operator>  (const CNsiNumeric &)  const;
	virtual int                 operator>  (const CNsiDecimal &)  const;
	virtual int                 operator>  (const CNsiFloat &)    const;
	virtual int                 operator>  (const CNsiReal &)     const;
	virtual int                 operator>  (const CNsiDouble &)   const;
	virtual int                 operator>  (const smallint)       const;
	virtual int                 operator>  (const integer)        const;
	virtual int                 operator>  (const real)           const;
	virtual int                 operator>  (const int)            const;
	virtual int                 operator>= (const CNsiSmallInt &) const;
	virtual int                 operator>= (const CNsiInt &)      const;
	virtual int                 operator>= (const CNsiNumeric &)  const;
	virtual int                 operator>= (const CNsiDecimal &)  const;
	virtual int                 operator>= (const CNsiFloat &)    const;
	virtual int                 operator>= (const CNsiReal &)     const;
	virtual int                 operator>= (const CNsiDouble &)   const;
	virtual int                 operator>= (const smallint)       const;
	virtual int                 operator>= (const integer)        const;
	virtual int                 operator>= (const real)           const;
	virtual int                 operator>= (const int)            const;
	virtual int                 operator== (const CNsiSmallInt &) const;
	virtual int                 operator== (const CNsiInt &)      const;
	virtual int                 operator== (const CNsiNumeric &)  const;
	virtual int                 operator== (const CNsiDecimal &)  const;
	virtual int                 operator== (const CNsiFloat &)    const;
	virtual int                 operator== (const CNsiReal &)     const;
	virtual int                 operator== (const CNsiDouble &)   const;
	virtual int                 operator== (const smallint)       const;
	virtual int                 operator== (const integer)        const;
	virtual int                 operator== (const real)           const;
	virtual int                 operator== (const int)            const;
	virtual int                 operator<= (const CNsiSmallInt &) const;
	virtual int                 operator<= (const CNsiInt &)      const;
	virtual int                 operator<= (const CNsiNumeric &)  const;
	virtual int                 operator<= (const CNsiDecimal &)  const;
	virtual int                 operator<= (const CNsiFloat &)    const;
	virtual int                 operator<= (const CNsiReal &)     const;
	virtual int                 operator<= (const CNsiDouble &)   const;
	virtual int                 operator<= (const smallint)       const;
	virtual int                 operator<= (const integer)        const;
	virtual int                 operator<= (const real)           const;
	virtual int                 operator<= (const int)            const;
	virtual int                 operator<  (const CNsiSmallInt &) const;
	virtual int                 operator<  (const CNsiInt &)      const;
	virtual int                 operator<  (const CNsiNumeric &)  const;
	virtual int                 operator<  (const CNsiDecimal &)  const;
	virtual int                 operator<  (const CNsiFloat &)    const;
	virtual int                 operator<  (const CNsiReal &)     const;
	virtual int                 operator<  (const CNsiDouble &)   const;
	virtual int                 operator<  (const smallint)       const;
	virtual int                 operator<  (const integer)        const;
	virtual int                 operator<  (const real)           const;
	virtual int                 operator<  (const int)            const;
	virtual int                 operator!= (const CNsiSmallInt &) const;
	virtual int                 operator!= (const CNsiInt &)      const;
	virtual int                 operator!= (const CNsiNumeric &)  const;
	virtual int                 operator!= (const CNsiDecimal &)  const;
	virtual int                 operator!= (const CNsiFloat &)    const;
	virtual int                 operator!= (const CNsiReal &)     const;
	virtual int                 operator!= (const CNsiDouble &)   const;
	virtual int                 operator!= (const smallint)       const;
	virtual int                 operator!= (const integer)        const;
	virtual int                 operator!= (const real)           const;
	virtual int                 operator!= (const int)            const;
protected:
	uint        precision;
	uint        scale;
};

//////////////////////////////////////////////////////////////////////////
// CNsiExactNum
class CNsiExactNum : public CNsiNum {
protected:
	                        CNsiExactNum ();
public:
	virtual                    ~CNsiExactNum ();
	virtual ENsiBoolean        is_exactnumeric       (void) const;
	CNsiData              * checkAdd                      (const CNsiData *) const;
	virtual int         operator>  (const CNsiSmallInt &) const;
	virtual int         operator>  (const CNsiInt &)      const;
	virtual int         operator>  (const CNsiNumeric &)  const;
	virtual int         operator>  (const CNsiDecimal &)  const;
	virtual int         operator>  (const CNsiFloat &)    const;
	virtual int         operator>  (const CNsiReal &)     const;
	virtual int         operator>  (const CNsiDouble &)   const;
	virtual int         operator>  (const smallint)       const;
	virtual int         operator>  (const integer)        const;
	virtual int         operator>  (const real)           const;
	virtual int         operator>  (const int)            const;
	virtual int         operator>= (const CNsiSmallInt &) const;
	virtual int         operator>= (const CNsiInt &)      const;
	virtual int         operator>= (const CNsiNumeric &)  const;
	virtual int         operator>= (const CNsiDecimal &)  const;
	virtual int         operator>= (const CNsiFloat &)    const;
	virtual int         operator>= (const CNsiReal &)     const;
	virtual int         operator>= (const CNsiDouble &)   const;
	virtual int         operator>= (const smallint)       const;
	virtual int         operator>= (const integer)        const;
	virtual int         operator>= (const real)           const;
	virtual int         operator>= (const int)            const;
	virtual int         operator== (const CNsiSmallInt &) const;
	virtual int         operator== (const CNsiInt &)      const;
	virtual int         operator== (const CNsiNumeric &)  const;
	virtual int         operator== (const CNsiDecimal &)  const;
	virtual int         operator== (const CNsiFloat &)    const;
	virtual int         operator== (const CNsiReal &)     const;
	virtual int         operator== (const CNsiDouble &)   const;
	virtual int         operator== (const smallint)       const;
	virtual int         operator== (const integer)        const;
	virtual int         operator== (const real)           const;
	virtual int         operator== (const int)            const;
	virtual int         operator<= (const CNsiSmallInt &) const;
	virtual int         operator<= (const CNsiInt &)      const;
	virtual int         operator<= (const CNsiNumeric &)  const;
	virtual int         operator<= (const CNsiDecimal &)  const;
	virtual int         operator<= (const CNsiFloat &)    const;
	virtual int         operator<= (const CNsiReal &)     const;
	virtual int         operator<= (const CNsiDouble &)   const;
	virtual int         operator<= (const smallint)       const;
	virtual int         operator<= (const integer)        const;
	virtual int         operator<= (const real)           const;
	virtual int         operator<= (const int)            const;
	virtual int         operator<  (const CNsiSmallInt &) const;
	virtual int         operator<  (const CNsiInt &)      const;
	virtual int         operator<  (const CNsiNumeric &)  const;
	virtual int         operator<  (const CNsiDecimal &)  const;
	virtual int         operator<  (const CNsiFloat &)    const;
	virtual int         operator<  (const CNsiReal &)     const;
	virtual int         operator<  (const CNsiDouble &)   const;
	virtual int         operator<  (const smallint)       const;
	virtual int         operator<  (const integer)        const;
	virtual int         operator<  (const real)           const;
	virtual int         operator<  (const int)            const;
	virtual int         operator!= (const CNsiSmallInt &) const;
	virtual int         operator!= (const CNsiInt &)      const;
	virtual int         operator!= (const CNsiNumeric &)  const;
	virtual int         operator!= (const CNsiDecimal &)  const;
	virtual int         operator!= (const CNsiFloat &)    const;
	virtual int         operator!= (const CNsiReal &)     const;
	virtual int         operator!= (const CNsiDouble &)   const;
	virtual int         operator!= (const smallint)       const;
	virtual int         operator!= (const integer)        const;
	virtual int         operator!= (const real)           const;
	virtual int         operator!= (const int)            const;
protected:
	        int         cmpeqlen(const  CNsiExactNum *)   const;
	        int         cmpeqlan(const  CNsiNum *)        const;
	        int         cmpeqlenC(const real)             const;
	        int         cmpneqen(const  CNsiExactNum *)   const;
	        int         cmpneqan(const  CNsiNum *)        const;
	        int         cmpneqenC(const real)             const;
	        int         cmpltren(const  CNsiExactNum *)   const;
	        int         cmpltran(const  CNsiNum *)        const;
	        int         cmpltrenC(const real)             const;
	        int         cmplteen(const  CNsiExactNum *)   const;
	        int         cmpltean(const  CNsiNum *)        const;
	        int         cmplteenC(const real)             const;
	        int         cmpgtren(const  CNsiExactNum *)   const;
	        int         cmpgtran(const  CNsiNum *)        const;
	        int         cmpgtrenC(const real)             const;
	        int         cmpgteen(const  CNsiExactNum *)   const;
	        int         cmpgtean(const  CNsiNum *)        const;
	        int         cmpgteenC(const real)             const;
};

//////////////////////////////////////////////////////////////////////////
// CNsiApproxNum
class CNsiApproxNum : public CNsiNum {
protected:
	                    CNsiApproxNum ();
public:
	virtual                ~CNsiApproxNum ();
	virtual ENsiBoolean is_approxnumeric    (void) const;
	virtual int         operator>  (const CNsiSmallInt &) const;
	virtual int         operator>  (const CNsiInt &)      const;
	virtual int         operator>  (const CNsiNumeric &)  const;
	virtual int         operator>  (const CNsiDecimal &)  const;
	virtual int         operator>  (const CNsiFloat &)    const;
	virtual int         operator>  (const CNsiReal &)     const;
	virtual int         operator>  (const CNsiDouble &)   const;
	virtual int         operator>  (const smallint)       const;
	virtual int         operator>  (const integer)        const;
	virtual int         operator>  (const real)           const;
	virtual int         operator>  (const int)            const;
	virtual int         operator>= (const CNsiSmallInt &) const;
	virtual int         operator>= (const CNsiInt &)      const;
	virtual int         operator>= (const CNsiNumeric &)  const;
	virtual int         operator>= (const CNsiDecimal &)  const;
	virtual int         operator>= (const CNsiFloat &)    const;
	virtual int         operator>= (const CNsiReal &)     const;
	virtual int         operator>= (const CNsiDouble &)   const;
	virtual int         operator>= (const smallint)       const;
	virtual int         operator>= (const integer)        const;
	virtual int         operator>= (const real)           const;
	virtual int         operator>= (const int)            const;
	virtual int         operator== (const CNsiSmallInt &) const;
	virtual int         operator== (const CNsiInt &)      const;
	virtual int         operator== (const CNsiNumeric &)  const;
	virtual int         operator== (const CNsiDecimal &)  const;
	virtual int         operator== (const CNsiFloat &)    const;
	virtual int         operator== (const CNsiReal &)     const;
	virtual int         operator== (const CNsiDouble &)   const;
	virtual int         operator== (const smallint)       const;
	virtual int         operator== (const integer)        const;
	virtual int         operator== (const real)           const;
	virtual int         operator== (const int)            const;
	virtual int         operator<= (const CNsiSmallInt &) const;
	virtual int         operator<= (const CNsiInt &)      const;
	virtual int         operator<= (const CNsiNumeric &)  const;
	virtual int         operator<= (const CNsiDecimal &)  const;
	virtual int         operator<= (const CNsiFloat &)    const;
	virtual int         operator<= (const CNsiReal &)     const;
	virtual int         operator<= (const CNsiDouble &)   const;
	virtual int         operator<= (const smallint)       const;
	virtual int         operator<= (const integer)        const;
	virtual int         operator<= (const real)           const;
	virtual int         operator<= (const int)            const;
	virtual int         operator<  (const CNsiSmallInt &) const;
	virtual int         operator<  (const CNsiInt &)      const;
	virtual int         operator<  (const CNsiNumeric &)  const;
	virtual int         operator<  (const CNsiDecimal &)  const;
	virtual int         operator<  (const CNsiFloat &)    const;
	virtual int         operator<  (const CNsiReal &)     const;
	virtual int         operator<  (const CNsiDouble &)   const;
	virtual int         operator<  (const smallint)       const;
	virtual int         operator<  (const integer)        const;
	virtual int         operator<  (const real)           const;
	virtual int         operator<  (const int)            const;
	virtual int         operator!= (const CNsiSmallInt &) const;
	virtual int         operator!= (const CNsiInt &)      const;
	virtual int         operator!= (const CNsiNumeric &)  const;
	virtual int         operator!= (const CNsiDecimal &)  const;
	virtual int         operator!= (const CNsiFloat &)    const;
	virtual int         operator!= (const CNsiReal &)     const;
	virtual int         operator!= (const CNsiDouble &)   const;
	virtual int         operator!= (const smallint)       const;
	virtual int         operator!= (const integer)        const;
	virtual int         operator!= (const real)           const;
	virtual int         operator!= (const int)            const;
protected:
};

//////////////////////////////////////////////////////////////////////////
// CNsiSmallInt
class CNsiSmallInt : public CNsiExactNum {
public:
	                    CNsiSmallInt (void);
	                    CNsiSmallInt (const CNsiSmallInt &);
	virtual                ~CNsiSmallInt (void);
	virtual ENsiDataType Type           (void) const;
	virtual uint         ReturnLength   (void) const;
	virtual ENsiBoolean  isEqualTo      (const CNsiData &) const;
	virtual ENsiBoolean  isGreaterThan  (const CNsiData &) const;
	virtual CNsiData *   checkAdd       (const CNsiData *) const;
	virtual CNsiData *   checkSub       (const CNsiData *) const;
	virtual CNsiData *   checkMul       (const CNsiData *) const;
	virtual CNsiData *   checkDiv       (const CNsiData *) const;
	virtual CNsiData *   checkSet       (const CNsiData *) const;
	virtual ENsiBoolean   storeValue (real) ;
	virtual ENsiBoolean   storeValue (integer) ;
	virtual ENsiBoolean   storeValue (smallint) ;
	virtual ENsiBoolean   storeValue (char *, uint) ;
	virtual ENsiBoolean   storeValue (const CNsiUcStr &) ;
	virtual ENsiBoolean   storeValue (const CNsiData &);
	virtual ENsiBoolean   storeValue (char *, uint, uint *);
	virtual ENsiBoolean   storeValue (const NsiUcStr);
	virtual integer       intValue  (void) const;
	virtual real          realValue (void) const;
	virtual ENsiBoolean   getValue (real *) const;
	virtual ENsiBoolean   getValue (integer *) const;
	virtual ENsiBoolean   getValue (smallint *) const;
	virtual ENsiBoolean   getValue (char *, uint) const;
	virtual ENsiBoolean   getValue (CNsiUcStr *) const;
	virtual ENsiBoolean   getValue (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue (CNsiData &) const;
	virtual DBCOLUMNINFO *  MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO *   MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean   SQLType    (CNsiUcStr *) const;
	virtual ENsiBoolean   SQLLiteral (CNsiUcStr *) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *) ;
	virtual CNsiObject   *duplicate (void) const;
	        CNsiSmallInt &operator= (const CNsiSmallInt &);
	        CNsiSmallInt &operator= (const CNsiInt &);
	        CNsiSmallInt &operator= (const CNsiNumeric &);
	        CNsiSmallInt &operator= (const CNsiDecimal &);
	        CNsiSmallInt &operator= (const CNsiFloat &);
	        CNsiSmallInt &operator= (const CNsiReal &);
	        CNsiSmallInt &operator= (const CNsiDouble &);
	        CNsiSmallInt &operator= (const smallint);
	        CNsiSmallInt &operator= (const integer);
	        CNsiSmallInt &operator= (const real);
	        CNsiSmallInt &operator= (const int);
	        CNsiSmallInt &operator+= (const CNsiSmallInt &);
	        CNsiSmallInt &operator+= (const CNsiInt &);
	        CNsiSmallInt &operator+= (const CNsiNumeric &);
	        CNsiSmallInt &operator+= (const CNsiDecimal &);
	        CNsiSmallInt &operator+= (const CNsiFloat &);
	        CNsiSmallInt &operator+= (const CNsiReal &);
	        CNsiSmallInt &operator+= (const CNsiDouble &);
	        CNsiSmallInt &operator+= (const smallint);
	        CNsiSmallInt &operator+= (const integer);
	        CNsiSmallInt &operator+= (const real);
	        CNsiSmallInt &operator+= (const int);
	        CNsiSmallInt &operator-= (const CNsiSmallInt &);
	        CNsiSmallInt &operator-= (const CNsiInt &);
	        CNsiSmallInt &operator-= (const CNsiNumeric &);
	        CNsiSmallInt &operator-= (const CNsiDecimal &);
	        CNsiSmallInt &operator-= (const CNsiFloat &);
	        CNsiSmallInt &operator-= (const CNsiReal &);
	        CNsiSmallInt &operator-= (const CNsiDouble &);
	        CNsiSmallInt &operator-= (const smallint);
	        CNsiSmallInt &operator-= (const integer);
	        CNsiSmallInt &operator-= (const real);
	        CNsiSmallInt &operator-= (const int);
	        CNsiSmallInt &operator*= (const CNsiSmallInt &);
	        CNsiSmallInt &operator*= (const CNsiInt &);
	        CNsiSmallInt &operator*= (const CNsiNumeric &);
	        CNsiSmallInt &operator*= (const CNsiDecimal &);
	        CNsiSmallInt &operator*= (const CNsiFloat &);
	        CNsiSmallInt &operator*= (const CNsiReal &);
	        CNsiSmallInt &operator*= (const CNsiDouble &);
	        CNsiSmallInt &operator*= (const smallint);
	        CNsiSmallInt &operator*= (const integer);
	        CNsiSmallInt &operator*= (const real);
	        CNsiSmallInt &operator*= (const int);
	        CNsiSmallInt &operator/= (const CNsiSmallInt &);
	        CNsiSmallInt &operator/= (const CNsiInt &);
	        CNsiSmallInt &operator/= (const CNsiNumeric &);
	        CNsiSmallInt &operator/= (const CNsiDecimal &);
	        CNsiSmallInt &operator/= (const CNsiFloat &);
	        CNsiSmallInt &operator/= (const CNsiReal &);
	        CNsiSmallInt &operator/= (const CNsiDouble &);
	        CNsiSmallInt &operator/= (const smallint);
	        CNsiSmallInt &operator/= (const integer);
	        CNsiSmallInt &operator/= (const real);
	        CNsiSmallInt &operator/= (const int);
	        CNsiDouble operator+ (const CNsiSmallInt &) const;
	        CNsiDouble operator+ (const smallint)       const;
	        CNsiDouble operator+ (const integer)        const;
	        CNsiDouble operator+ (const real)           const;
	        CNsiDouble operator+ (const int)            const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const smallint, const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const integer,  const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const real,     const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const int,      const CNsiSmallInt &);
	        CNsiDouble operator- (const CNsiSmallInt &) const;
	        CNsiDouble operator- (const smallint)       const;
	        CNsiDouble operator- (const integer)        const;
	        CNsiDouble operator- (const real)           const;
	        CNsiDouble operator- (const int)            const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const smallint, const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const integer,  const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const real,     const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const int,      const CNsiSmallInt &);
	        CNsiDouble operator* (const CNsiSmallInt &) const;
	        CNsiDouble operator* (const smallint)       const;
	        CNsiDouble operator* (const integer)        const;
	        CNsiDouble operator* (const real)           const;
	        CNsiDouble operator* (const int)            const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const smallint, const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const integer,  const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const real,     const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const int,      const CNsiSmallInt &);
	        CNsiDouble operator/ (const CNsiSmallInt &) const;
	        CNsiDouble operator/ (const smallint)  const;
	        CNsiDouble operator/ (const integer)   const;
	        CNsiDouble operator/ (const real)      const;
	        CNsiDouble operator/ (const int)       const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const smallint, const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const integer,  const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const real,     const CNsiSmallInt &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const int,      const CNsiSmallInt &);
	        CNsiSmallInt &operator-- (void);
	        CNsiSmallInt &operator++ (void);
	        CNsiSmallInt &operator-  (void);
private:
	smallint sivalue;
};

//////////////////////////////////////////////////////////////////////////
// CNsiInt
class CNsiInt : public CNsiExactNum {
public:
	                    CNsiInt ();
	                    CNsiInt (const CNsiInt &);
	virtual                ~CNsiInt ();
	virtual ENsiDataType Type           (void) const;
	virtual uint         ReturnLength   (void) const;
	virtual CNsiData *   checkAdd       (const CNsiData *) const;
	virtual CNsiData *   checkSub       (const CNsiData *) const;
	virtual CNsiData *   checkMul       (const CNsiData *) const;
	virtual CNsiData *   checkDiv       (const CNsiData *) const;
	virtual CNsiData *   checkSet       (const CNsiData *) const;
	virtual ENsiBoolean  isEqualTo      (const CNsiData &) const;
	virtual ENsiBoolean  isGreaterThan  (const CNsiData &) const;
	virtual ENsiBoolean   storeValue (real);
	virtual ENsiBoolean   storeValue (integer);
	virtual ENsiBoolean   storeValue (smallint);
	virtual ENsiBoolean   storeValue (char *, uint);
	virtual ENsiBoolean   storeValue (const CNsiUcStr &);
	virtual ENsiBoolean   storeValue (const CNsiData &);
	virtual ENsiBoolean   storeValue (char *, uint, uint *);
	virtual ENsiBoolean   storeValue (const NsiUcStr);
	virtual integer       intValue  (void) const;
	virtual real          realValue (void) const;
	virtual ENsiBoolean   getValue (real *) const;
	virtual ENsiBoolean   getValue (integer *) const;
	virtual ENsiBoolean   getValue (smallint *) const;
	virtual ENsiBoolean   getValue (char *, uint) const;
	virtual ENsiBoolean   getValue (CNsiUcStr *) const;
	virtual ENsiBoolean   getValue (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue (CNsiData &) const;
	virtual DBCOLUMNINFO *  MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO *   MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean   SQLType    (CNsiUcStr *) const;
	virtual ENsiBoolean   SQLLiteral (CNsiUcStr *) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *) ;
	virtual CNsiObject   *duplicate (void) const;
	        CNsiInt &operator= (const CNsiSmallInt &);
	        CNsiInt &operator= (const CNsiInt &);
	        CNsiInt &operator= (const CNsiNumeric &);
	        CNsiInt &operator= (const CNsiDecimal &);
	        CNsiInt &operator= (const CNsiFloat &);
	        CNsiInt &operator= (const CNsiReal &);
	        CNsiInt &operator= (const CNsiDouble &);
	        CNsiInt &operator= (const smallint);
	        CNsiInt &operator= (const integer);
	        CNsiInt &operator= (const real);
	        CNsiInt &operator= (const int);
	        CNsiInt &operator+= (const CNsiSmallInt &);
	        CNsiInt &operator+= (const CNsiInt &);
	        CNsiInt &operator+= (const CNsiNumeric &);
	        CNsiInt &operator+= (const CNsiDecimal &);
	        CNsiInt &operator+= (const CNsiFloat &);
	        CNsiInt &operator+= (const CNsiReal &);
	        CNsiInt &operator+= (const CNsiDouble &);
	        CNsiInt &operator+= (const smallint);
	        CNsiInt &operator+= (const integer);
	        CNsiInt &operator+= (const real);
	        CNsiInt &operator+= (const int);
	        CNsiInt &operator-= (const CNsiSmallInt &);
	        CNsiInt &operator-= (const CNsiInt &);
	        CNsiInt &operator-= (const CNsiNumeric &);
	        CNsiInt &operator-= (const CNsiDecimal &);
	        CNsiInt &operator-= (const CNsiFloat &);
	        CNsiInt &operator-= (const CNsiReal &);
	        CNsiInt &operator-= (const CNsiDouble &);
	        CNsiInt &operator-= (const smallint);
	        CNsiInt &operator-= (const integer);
	        CNsiInt &operator-= (const real);
	        CNsiInt &operator-= (const int);
	        CNsiInt &operator*= (const CNsiSmallInt &);
	        CNsiInt &operator*= (const CNsiInt &);
	        CNsiInt &operator*= (const CNsiNumeric &);
	        CNsiInt &operator*= (const CNsiDecimal &);
	        CNsiInt &operator*= (const CNsiFloat &);
	        CNsiInt &operator*= (const CNsiReal &);
	        CNsiInt &operator*= (const CNsiDouble &);
	        CNsiInt &operator*= (const smallint);
	        CNsiInt &operator*= (const integer);
	        CNsiInt &operator*= (const real);
	        CNsiInt &operator*= (const int);
	        CNsiInt &operator/= (const CNsiSmallInt &);
	        CNsiInt &operator/= (const CNsiInt &);
	        CNsiInt &operator/= (const CNsiNumeric &);
	        CNsiInt &operator/= (const CNsiDecimal &);
	        CNsiInt &operator/= (const CNsiFloat &);
	        CNsiInt &operator/= (const CNsiReal &);
	        CNsiInt &operator/= (const CNsiDouble &);
	        CNsiInt &operator/= (const smallint);
	        CNsiInt &operator/= (const integer);
	        CNsiInt &operator/= (const real);
	        CNsiInt &operator/= (const int);
	        CNsiDouble operator+ (const CNsiSmallInt &) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiSmallInt &, const CNsiInt &);
	        CNsiDouble operator+ (const CNsiInt &) const;
	        CNsiDouble operator+ (const smallint)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const smallint, const CNsiInt &);
	        CNsiDouble operator+ (const integer) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const integer, const CNsiInt &);
	        CNsiDouble operator+ (const real) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const real, const CNsiInt &);
	        CNsiDouble operator+ (const int) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const int, const CNsiInt &);
	        CNsiDouble operator- (const CNsiSmallInt &) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiSmallInt &, const CNsiInt &);
	        CNsiDouble operator- (const CNsiInt &) const;
	        CNsiDouble operator- (const smallint)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const smallint, const CNsiInt &);
	        CNsiDouble operator- (const integer) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const integer, const CNsiInt &);
	        CNsiDouble operator- (const real) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const real, const CNsiInt &);
	        CNsiDouble operator- (const int) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const int, const CNsiInt &);
	        CNsiDouble operator* (const CNsiSmallInt &) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiSmallInt &, const CNsiInt &);
	        CNsiDouble operator* (const CNsiInt &) const;
	        CNsiDouble operator* (const smallint)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const smallint, const CNsiInt &);
	        CNsiDouble operator* (const integer) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const integer, const CNsiInt &);
	        CNsiDouble operator* (const real) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const real, const CNsiInt &);
	        CNsiDouble operator* (const int) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const int, const CNsiInt &);
	        CNsiDouble operator/ (const CNsiSmallInt &) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiSmallInt &, const CNsiInt &);
	        CNsiDouble operator/ (const CNsiInt &) const;
	        CNsiDouble operator/ (const smallint) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const smallint, const CNsiInt &);
	        CNsiDouble operator/ (const integer) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const integer, const CNsiInt &);
	        CNsiDouble operator/ (const real) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const real, const CNsiInt &);
	        CNsiDouble operator/ (const int) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const int, const CNsiInt &);
	        CNsiInt &operator-- (void);
	        CNsiInt &operator++ (void);
	        CNsiInt &operator-  (void);
private:
	integer ivalue;
};

//////////////////////////////////////////////////////////////////////////
// CNsiNumeric
class CNsiNumeric: public CNsiExactNum {
	friend class CNsiDecimal;
private:
	        ENsiBoolean SetNumeric (real);
public:
	                            CNsiNumeric     (uint, uint);
	                            CNsiNumeric     (uint);
	                            CNsiNumeric     (const CNsiNumeric &);
	                            CNsiNumeric     (void);
	virtual                     ~CNsiNumeric    (void);
	virtual ENsiDataType Type           (void) const;
	virtual uint         ReturnLength   (void) const;
	virtual CNsiData *   checkAdd       (const CNsiData *) const;
	virtual CNsiData *   checkSub       (const CNsiData *) const;
	virtual CNsiData *   checkMul       (const CNsiData *) const;
	virtual CNsiData *   checkDiv       (const CNsiData *) const;
	virtual CNsiData *   checkSet       (const CNsiData *) const;
	virtual ENsiBoolean  isEqualTo      (const CNsiData &) const;
	virtual ENsiBoolean  isGreaterThan  (const CNsiData &) const;
	virtual ENsiBoolean   storeValue (real);
	virtual ENsiBoolean   storeValue (integer);
	virtual ENsiBoolean   storeValue (smallint);
	virtual ENsiBoolean   storeValue (char *, uint);
	virtual ENsiBoolean   storeValue (const CNsiUcStr &);
	virtual ENsiBoolean   storeValue (const CNsiData &);
	virtual ENsiBoolean   storeValue (const DB_NUMERIC *);
	virtual ENsiBoolean   storeValue (char *, uint, uint *);
	virtual ENsiBoolean   storeValue (const NsiUcStr);
	virtual DBCOLUMNINFO *  MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO *   MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean   SQLType    (CNsiUcStr *) const;
	virtual ENsiBoolean   SQLLiteral (CNsiUcStr *) const;
	virtual integer       intValue  (void) const;
	virtual real          realValue (void) const;
	virtual ENsiBoolean   getValue (real *) const;
	virtual ENsiBoolean   getValue (integer *) const;
	virtual ENsiBoolean   getValue (smallint *) const;
	virtual ENsiBoolean   getValue (char *, uint) const;
	virtual ENsiBoolean   getValue (CNsiUcStr *) const;
	virtual ENsiBoolean   getValue (DB_NUMERIC *) const;
	virtual ENsiBoolean   getValue (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue (CNsiData &) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *) ;
	virtual CNsiObject     *duplicate (void) const;
	        CNsiNumeric &operator= (const CNsiSmallInt &);
	        CNsiNumeric &operator= (const CNsiInt &);
	        CNsiNumeric &operator= (const CNsiNumeric &);
	        CNsiNumeric &operator= (const CNsiDecimal &);
	        CNsiNumeric &operator= (const CNsiFloat &);
	        CNsiNumeric &operator= (const CNsiReal &);
	        CNsiNumeric &operator= (const CNsiDouble &);
	        CNsiNumeric &operator= (const smallint);
	        CNsiNumeric &operator= (const integer);
	        CNsiNumeric &operator= (const real);
	        CNsiNumeric &operator= (const int);
	        CNsiNumeric &operator+= (const CNsiSmallInt &);
	        CNsiNumeric &operator+= (const CNsiInt &);
	        CNsiNumeric &operator+= (const CNsiNumeric &);
	        CNsiNumeric &operator+= (const CNsiDecimal &);
	        CNsiNumeric &operator+= (const CNsiFloat &);
	        CNsiNumeric &operator+= (const CNsiReal &);
	        CNsiNumeric &operator+= (const CNsiDouble &);
	        CNsiNumeric &operator+= (const smallint);
	        CNsiNumeric &operator+= (const integer);
	        CNsiNumeric &operator+= (const real);
	        CNsiNumeric &operator+= (const int);
	        CNsiNumeric &operator-= (const CNsiSmallInt &);
	        CNsiNumeric &operator-= (const CNsiInt &);
	        CNsiNumeric &operator-= (const CNsiNumeric &);
	        CNsiNumeric &operator-= (const CNsiDecimal &);
	        CNsiNumeric &operator-= (const CNsiFloat &);
	        CNsiNumeric &operator-= (const CNsiReal &);
	        CNsiNumeric &operator-= (const CNsiDouble &);
	        CNsiNumeric &operator-= (const smallint);
	        CNsiNumeric &operator-= (const integer);
	        CNsiNumeric &operator-= (const real);
	        CNsiNumeric &operator-= (const int);
	        CNsiNumeric &operator*= (const CNsiSmallInt &);
	        CNsiNumeric &operator*= (const CNsiInt &);
	        CNsiNumeric &operator*= (const CNsiNumeric &);
	        CNsiNumeric &operator*= (const CNsiDecimal &);
	        CNsiNumeric &operator*= (const CNsiFloat &);
	        CNsiNumeric &operator*= (const CNsiReal &);
	        CNsiNumeric &operator*= (const CNsiDouble &);
	        CNsiNumeric &operator*= (const smallint);
	        CNsiNumeric &operator*= (const integer);
	        CNsiNumeric &operator*= (const real);
	        CNsiNumeric &operator*= (const int);
	        CNsiNumeric &operator/= (const CNsiSmallInt &);
	        CNsiNumeric &operator/= (const CNsiInt &);
	        CNsiNumeric &operator/= (const CNsiNumeric &);
	        CNsiNumeric &operator/= (const CNsiDecimal &);
	        CNsiNumeric &operator/= (const CNsiFloat &);
	        CNsiNumeric &operator/= (const CNsiReal &);
	        CNsiNumeric &operator/= (const CNsiDouble &);
	        CNsiNumeric &operator/= (const smallint);
	        CNsiNumeric &operator/= (const integer);
	        CNsiNumeric &operator/= (const real);
	        CNsiNumeric &operator/= (const int);
	        CNsiDouble operator+ (const CNsiSmallInt &) const;
	        CNsiDouble operator+ (const CNsiInt &)      const;
	        CNsiDouble operator+ (const CNsiNumeric &)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiSmallInt &, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiInt &, const CNsiNumeric &);
	        CNsiDouble operator+ (const smallint) const;
	        CNsiDouble operator+ (const integer)  const;
	        CNsiDouble operator+ (const real)     const;
	        CNsiDouble operator+ (const int)      const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const smallint, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const integer, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const real, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const int, const CNsiNumeric &);
	        CNsiDouble operator- (const CNsiSmallInt &) const;
	        CNsiDouble operator- (const CNsiInt &)      const;
	        CNsiDouble operator- (const CNsiNumeric &)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiSmallInt &, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiInt &, const CNsiNumeric &);
	        CNsiDouble operator- (const smallint) const;
	        CNsiDouble operator- (const integer)  const;
	        CNsiDouble operator- (const real)     const;
	        CNsiDouble operator- (const int)      const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const smallint, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const integer, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const real, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const int, const CNsiNumeric &) ;
	        CNsiDouble operator* (const CNsiSmallInt &) const;
	        CNsiDouble operator* (const CNsiInt &)      const;
	        CNsiDouble operator* (const CNsiNumeric &)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiSmallInt &, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiInt &, const CNsiNumeric &);
	        CNsiDouble operator* (const smallint) const;
	        CNsiDouble operator* (const integer)  const;
	        CNsiDouble operator* (const real)     const;
	        CNsiDouble operator* (const int)      const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const smallint, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const integer, const CNsiNumeric &) ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const real, const CNsiNumeric &)    ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const int, const CNsiNumeric &)     ;
	        CNsiDouble operator/ (const CNsiSmallInt &) const;
	        CNsiDouble operator/ (const CNsiInt &)      const;
	        CNsiDouble operator/ (const CNsiNumeric &)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiSmallInt &, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiInt &, const CNsiNumeric &)     ;
	        CNsiDouble operator/ (const smallint) const;
	        CNsiDouble operator/ (const integer)  const;
	        CNsiDouble operator/ (const real)     const;
	        CNsiDouble operator/ (const int)      const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const smallint, const CNsiNumeric &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const integer, const CNsiNumeric &) ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const real, const CNsiNumeric &)    ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const int, const CNsiNumeric &)     ;
	        CNsiNumeric &operator++ (void);
	        CNsiNumeric &operator-- (void);
	        CNsiNumeric &operator- (void);
//private:
//        NSIBCD  bcdvalue;
};

//////////////////////////////////////////////////////////////////////////
// CNsiDecimal
class CNsiDecimal: public CNsiExactNum {
	friend class CNsiNumeric;
private:
	        ENsiBoolean SetDecimal (real);
public:
	        CNsiDecimal  (uint, uint);
	        CNsiDecimal  (uint);
	        CNsiDecimal  (const CNsiDecimal &);
	        CNsiDecimal  (void);
	virtual ~CNsiDecimal (void);
	virtual ENsiDataType Type          (void) const;
	virtual uint         ReturnLength  (void) const;
	virtual CNsiData *   checkAdd      (const CNsiData *) const;
	virtual CNsiData *   checkSub      (const CNsiData *) const;
	virtual CNsiData *   checkMul      (const CNsiData *) const;
	virtual CNsiData *   checkDiv      (const CNsiData *) const;
	virtual CNsiData *   checkSet      (const CNsiData *) const;
	virtual ENsiBoolean  isEqualTo     (const CNsiData &) const;
	virtual ENsiBoolean  isGreaterThan (const CNsiData &) const;
	virtual ENsiBoolean   storeValue (real);
	virtual ENsiBoolean   storeValue (integer);
	virtual ENsiBoolean   storeValue (smallint);
	virtual ENsiBoolean   storeValue (char *, uint);
	virtual ENsiBoolean   storeValue (const CNsiUcStr &);
	virtual ENsiBoolean   storeValue (const CNsiData &);
	virtual ENsiBoolean   storeValue (LARGE_INTEGER);
	virtual ENsiBoolean   storeValue (ULARGE_INTEGER);
	virtual ENsiBoolean   storeValue (const DECIMAL &);
	virtual ENsiBoolean   storeValue (char *, uint, uint *);
	virtual ENsiBoolean   storeValue (const NsiUcStr);
	virtual DBCOLUMNINFO *  MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO *   MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean   SQLType    (CNsiUcStr *) const;
	virtual ENsiBoolean   SQLLiteral (CNsiUcStr *) const;
	virtual integer       intValue  (void) const;
	virtual real          realValue (void) const;
	virtual ENsiBoolean   getValue (real *) const;
	virtual ENsiBoolean   getValue (integer *) const;
	virtual ENsiBoolean   getValue (smallint *) const;
	virtual ENsiBoolean   getValue (char *, uint) const;
	virtual ENsiBoolean   getValue (CNsiUcStr *) const;
	virtual ENsiBoolean   getValue (LARGE_INTEGER *) const;
	virtual ENsiBoolean   getValue (ULARGE_INTEGER *) const;
	virtual ENsiBoolean   getValue (DECIMAL *) const;
	virtual ENsiBoolean   getValue (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue (CNsiData &) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject   *duplicate (void) const;
	        CNsiDecimal &operator= (const CNsiSmallInt &);
	        CNsiDecimal &operator= (const CNsiInt &);
	        CNsiDecimal &operator= (const CNsiNumeric &);
	        CNsiDecimal &operator= (const CNsiDecimal &);
	        CNsiDecimal &operator= (const CNsiFloat &);
	        CNsiDecimal &operator= (const CNsiReal &);
	        CNsiDecimal &operator= (const CNsiDouble &);
	        CNsiDecimal &operator= (const smallint);
	        CNsiDecimal &operator= (const integer);
	        CNsiDecimal &operator= (const real);
	        CNsiDecimal &operator= (const int);
	        CNsiDecimal &operator+= (const CNsiSmallInt &);
	        CNsiDecimal &operator+= (const CNsiInt &);
	        CNsiDecimal &operator+= (const CNsiNumeric &);
	        CNsiDecimal &operator+= (const CNsiDecimal &);
	        CNsiDecimal &operator+= (const CNsiFloat &);
	        CNsiDecimal &operator+= (const CNsiReal &);
	        CNsiDecimal &operator+= (const CNsiDouble &);
	        CNsiDecimal &operator+= (const smallint);
	        CNsiDecimal &operator+= (const integer);
	        CNsiDecimal &operator+= (const real);
	        CNsiDecimal &operator+= (const int);
	        CNsiDecimal &operator-= (const CNsiSmallInt &);
	        CNsiDecimal &operator-= (const CNsiInt &);
	        CNsiDecimal &operator-= (const CNsiNumeric &);
	        CNsiDecimal &operator-= (const CNsiDecimal &);
	        CNsiDecimal &operator-= (const CNsiFloat &);
	        CNsiDecimal &operator-= (const CNsiReal &);
	        CNsiDecimal &operator-= (const CNsiDouble &);
	        CNsiDecimal &operator-= (const smallint);
	        CNsiDecimal &operator-= (const integer);
	        CNsiDecimal &operator-= (const real);
	        CNsiDecimal &operator-= (const int);
	        CNsiDecimal &operator*= (const CNsiSmallInt &);
	        CNsiDecimal &operator*= (const CNsiInt &);
	        CNsiDecimal &operator*= (const CNsiNumeric &);
	        CNsiDecimal &operator*= (const CNsiDecimal &);
	        CNsiDecimal &operator*= (const CNsiFloat &);
	        CNsiDecimal &operator*= (const CNsiReal &);
	        CNsiDecimal &operator*= (const CNsiDouble &);
	        CNsiDecimal &operator*= (const smallint);
	        CNsiDecimal &operator*= (const integer);
	        CNsiDecimal &operator*= (const real);
	        CNsiDecimal &operator*= (const int);
	        CNsiDecimal &operator/= (const CNsiSmallInt &);
	        CNsiDecimal &operator/= (const CNsiInt &);
	        CNsiDecimal &operator/= (const CNsiNumeric &);
	        CNsiDecimal &operator/= (const CNsiDecimal &);
	        CNsiDecimal &operator/= (const CNsiFloat &);
	        CNsiDecimal &operator/= (const CNsiReal &);
	        CNsiDecimal &operator/= (const CNsiDouble &);
	        CNsiDecimal &operator/= (const smallint);
	        CNsiDecimal &operator/= (const integer);
	        CNsiDecimal &operator/= (const real);
	        CNsiDecimal &operator/= (const int);
	        CNsiDouble operator+ (const CNsiSmallInt &) const;
	        CNsiDouble operator+ (const CNsiInt &)      const;
	        CNsiDouble operator+ (const CNsiNumeric &)  const;
	        CNsiDouble operator+ (const CNsiDecimal &)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiSmallInt &, const CNsiDecimal &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiInt &, const CNsiDecimal &)     ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiNumeric &, const CNsiDecimal &) ;
	        CNsiDouble operator+ (const smallint) const;
	        CNsiDouble operator+ (const integer)  const;
	        CNsiDouble operator+ (const real)     const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const smallint, const CNsiDecimal &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const integer, const CNsiDecimal &) ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const real, const CNsiDecimal &)    ;
	        CNsiDouble operator+ (const int) const;
	 friend CNsiDouble operator+ (const int, const CNsiDecimal &);
	        CNsiDouble operator- (const CNsiSmallInt &) const;
	        CNsiDouble operator- (const CNsiInt &)      const;
	        CNsiDouble operator- (const CNsiNumeric &)  const;
	        CNsiDouble operator- (const CNsiDecimal &)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiSmallInt &, const CNsiDecimal &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiInt &, const CNsiDecimal &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiNumeric &, const CNsiDecimal &);
	        CNsiDouble operator- (const smallint) const;
	        CNsiDouble operator- (const integer)  const;
	        CNsiDouble operator- (const real)     const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const smallint, const CNsiDecimal &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const integer, const CNsiDecimal &) ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const real, const CNsiDecimal &)    ;
	        CNsiDouble operator- (const int) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const int, const CNsiDecimal &);
	        CNsiDouble operator* (const CNsiSmallInt &) const;
	        CNsiDouble operator* (const CNsiInt &)      const;
	        CNsiDouble operator* (const CNsiNumeric &)  const;
	        CNsiDouble operator* (const CNsiDecimal &)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiSmallInt &, const CNsiDecimal &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiInt &, const CNsiDecimal &)     ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiNumeric &, const CNsiDecimal &) ;
	        CNsiDouble operator* (const smallint) const;
	        CNsiDouble operator* (const integer)  const;
	        CNsiDouble operator* (const real)     const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const smallint, const CNsiDecimal &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const integer, const CNsiDecimal &) ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const real, const CNsiDecimal &)    ;
	        CNsiDouble operator* (const int) const                         ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const int, const CNsiDecimal &)     ;
	        CNsiDouble operator/ (const CNsiSmallInt &) const;
	        CNsiDouble operator/ (const CNsiInt &)      const;
	        CNsiDouble operator/ (const CNsiNumeric &)  const;
	        CNsiDouble operator/ (const CNsiDecimal &)  const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiSmallInt &, const CNsiDecimal &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiInt &, const CNsiDecimal &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiNumeric &, const CNsiDecimal &);
	        CNsiDouble operator/ (const smallint) const;
	        CNsiDouble operator/ (const integer)  const;
	        CNsiDouble operator/ (const real)     const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const smallint, const CNsiDecimal &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const integer, const CNsiDecimal &) ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const real, const CNsiDecimal &)    ;
	        CNsiDouble operator/ (const int) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const int, const CNsiDecimal &);
	        CNsiDecimal &operator++ (void);
	        CNsiDecimal &operator-- (void);
	        CNsiDecimal &operator- (void);
//private:
//    ENsiBoolean fmt;
//    NSIBCD      bcdvalue;
//    double      realvalue;
};

//////////////////////////////////////////////////////////////////////////
// CNsiFloat
class CNsiFloat: public CNsiApproxNum {
public:
	                            CNsiFloat               (void);
	                            CNsiFloat               (uint);
	                            CNsiFloat               (const CNsiFloat &);
	virtual                     ~CNsiFloat              (void);
	virtual ENsiDataType Type           (void) const;
	virtual uint         ReturnLength   (void) const;
	virtual CNsiData *   checkAdd       (const CNsiData *) const;
	virtual CNsiData *   checkSub       (const CNsiData *) const;
	virtual CNsiData *   checkMul       (const CNsiData *) const;
	virtual CNsiData *   checkDiv       (const CNsiData *) const;
	virtual CNsiData *   checkSet       (const CNsiData *) const;
	virtual ENsiBoolean  isEqualTo      (const CNsiData &) const;
	virtual ENsiBoolean  isGreaterThan  (const CNsiData &) const;
	virtual ENsiBoolean   storeValue    (real);
	virtual ENsiBoolean   storeValue    (integer);
	virtual ENsiBoolean   storeValue    (smallint);
	virtual ENsiBoolean   storeValue    (char *, uint);
	virtual ENsiBoolean   storeValue    (const CNsiUcStr &);
	virtual ENsiBoolean   storeValue    (const CNsiData &);
	virtual ENsiBoolean   storeValue    (char *, uint, uint *);
	virtual ENsiBoolean   storeValue    (const NsiUcStr);
	virtual DBCOLUMNINFO *MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO * MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean   SQLType       (CNsiUcStr *) const;
	virtual ENsiBoolean   SQLLiteral    (CNsiUcStr *) const;
	virtual integer       intValue      (void) const;
	virtual real          realValue     (void) const;
	virtual ENsiBoolean   getValue              (real *) const;
	virtual ENsiBoolean   getValue              (integer *) const;
	virtual ENsiBoolean   getValue              (smallint *) const;
	virtual ENsiBoolean   getValue              (char *, uint) const;
	virtual ENsiBoolean   getValue              (CNsiUcStr *) const;
	virtual ENsiBoolean   getValue              (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue              (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue              (CNsiData &) const;
	virtual unsigned long packSize      (void) const;
	virtual unsigned long packTo        (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom    (CNsiObjPack *);
	virtual unsigned long packValueSize (void)  const;
	virtual unsigned long packValueTo   (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject   *duplicate     (void) const;
	        CNsiFloat &operator= (const CNsiSmallInt &);
	        CNsiFloat &operator= (const CNsiInt &);
	        CNsiFloat &operator= (const CNsiNumeric &);
	        CNsiFloat &operator= (const CNsiDecimal &);
	        CNsiFloat &operator= (const CNsiFloat &);
	        CNsiFloat &operator= (const CNsiReal &);
	        CNsiFloat &operator= (const CNsiDouble &);
	        CNsiFloat &operator= (const smallint);
	        CNsiFloat &operator= (const integer);
	        CNsiFloat &operator= (const real);
	        CNsiFloat &operator= (const int);
	        CNsiFloat &operator+= (const CNsiSmallInt &);
	        CNsiFloat &operator+= (const CNsiInt &);
	        CNsiFloat &operator+= (const CNsiNumeric &);
	        CNsiFloat &operator+= (const CNsiDecimal &);
	        CNsiFloat &operator+= (const CNsiFloat &);
	        CNsiFloat &operator+= (const CNsiReal &);
	        CNsiFloat &operator+= (const CNsiDouble &);
	        CNsiFloat &operator+= (const smallint);
	        CNsiFloat &operator+= (const integer);
	        CNsiFloat &operator+= (const real);
	        CNsiFloat &operator+= (const int);
	        CNsiFloat &operator-= (const CNsiSmallInt &);
	        CNsiFloat &operator-= (const CNsiInt &);
	        CNsiFloat &operator-= (const CNsiNumeric &);
	        CNsiFloat &operator-= (const CNsiDecimal &);
	        CNsiFloat &operator-= (const CNsiFloat &);
	        CNsiFloat &operator-= (const CNsiReal &);
	        CNsiFloat &operator-= (const CNsiDouble &);
	        CNsiFloat &operator-= (const smallint);
	        CNsiFloat &operator-= (const integer);
	        CNsiFloat &operator-= (const real);
	        CNsiFloat &operator-= (const int);
	        CNsiFloat &operator*= (const CNsiSmallInt &);
	        CNsiFloat &operator*= (const CNsiInt &);
	        CNsiFloat &operator*= (const CNsiNumeric &);
	        CNsiFloat &operator*= (const CNsiDecimal &);
	        CNsiFloat &operator*= (const CNsiFloat &);
	        CNsiFloat &operator*= (const CNsiReal &);
	        CNsiFloat &operator*= (const CNsiDouble &);
	        CNsiFloat &operator*= (const smallint);
	        CNsiFloat &operator*= (const integer);
	        CNsiFloat &operator*= (const real);
	        CNsiFloat &operator*= (const int);
	        CNsiFloat &operator/= (const CNsiSmallInt &);
	        CNsiFloat &operator/= (const CNsiInt &);
	        CNsiFloat &operator/= (const CNsiNumeric &);
	        CNsiFloat &operator/= (const CNsiDecimal &);
	        CNsiFloat &operator/= (const CNsiFloat &);
	        CNsiFloat &operator/= (const CNsiReal &);
	        CNsiFloat &operator/= (const CNsiDouble &);
	        CNsiFloat &operator/= (const smallint);
	        CNsiFloat &operator/= (const integer);
	        CNsiFloat &operator/= (const real);
	        CNsiFloat &operator/= (const int);
	        CNsiFloat operator+ (const CNsiSmallInt &) const;
	        CNsiFloat operator+ (const CNsiInt &)      const;
	        CNsiFloat operator+ (const CNsiNumeric &)  const;
	        CNsiFloat operator+ (const CNsiDecimal &)  const;
	        CNsiFloat operator+ (const CNsiFloat &)    const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator+ (const CNsiSmallInt &, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator+ (const CNsiInt &, const CNsiFloat &)     ;
	 friend CNsiFloat NRXDBGATE_EXPORT operator+ (const CNsiNumeric &, const CNsiFloat &) ;
	 friend CNsiFloat NRXDBGATE_EXPORT operator+ (const CNsiDecimal &, const CNsiFloat &) ;
	        CNsiFloat operator+ (const smallint) const;
	        CNsiFloat operator+ (const integer)  const;
	        CNsiFloat operator+ (const real)     const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator+ (const smallint, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator+ (const integer, const CNsiFloat &) ;
	 friend CNsiFloat NRXDBGATE_EXPORT operator+ (const real, const CNsiFloat &)    ;
	        CNsiFloat operator+ (const int) const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator+ (const int, const CNsiFloat &);
	        CNsiFloat operator- (const CNsiSmallInt &) const;
	        CNsiFloat operator- (const CNsiInt &)      const;
	        CNsiFloat operator- (const CNsiNumeric &)  const;
	        CNsiFloat operator- (const CNsiDecimal &)  const;
	        CNsiFloat operator- (const CNsiFloat &)    const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator- (const CNsiSmallInt &, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator- (const CNsiInt &, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator- (const CNsiNumeric &, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator- (const CNsiDecimal &, const CNsiFloat &);
	        CNsiFloat operator- (const smallint) const;
	        CNsiFloat operator- (const integer)  const;
	        CNsiFloat operator- (const real)     const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator- (const smallint, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator- (const integer, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator- (const real, const CNsiFloat &);
	        CNsiFloat operator- (const int) const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator- (const int, const CNsiFloat &);
	        CNsiFloat operator* (const CNsiSmallInt &) const;
	        CNsiFloat operator* (const CNsiInt &)      const;
	        CNsiFloat operator* (const CNsiNumeric &)  const;
	        CNsiFloat operator* (const CNsiDecimal &)  const;
	        CNsiFloat operator* (const CNsiFloat &)    const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator* (const CNsiSmallInt &, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator* (const CNsiInt &, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator* (const CNsiNumeric &, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator* (const CNsiDecimal &, const CNsiFloat &);
	        CNsiFloat operator* (const smallint) const;
	        CNsiFloat operator* (const integer)  const;
	        CNsiFloat operator* (const real)     const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator* (const smallint, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator* (const integer, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator* (const real, const CNsiFloat &);
	        CNsiFloat operator* (const int) const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator* (const int, const CNsiFloat &);
	        CNsiFloat operator/ (const CNsiSmallInt &) const;
	        CNsiFloat operator/ (const CNsiInt &)      const;
	        CNsiFloat operator/ (const CNsiNumeric &)  const;
	        CNsiFloat operator/ (const CNsiDecimal &)  const;
	        CNsiFloat operator/ (const CNsiFloat &)    const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator/ (const CNsiSmallInt &, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator/ (const CNsiInt &, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator/ (const CNsiNumeric &, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator/ (const CNsiDecimal &, const CNsiFloat &);
	        CNsiFloat operator/ (const smallint) const;
	        CNsiFloat operator/ (const integer)  const;
	        CNsiFloat operator/ (const real)     const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator/ (const smallint, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator/ (const integer, const CNsiFloat &);
	 friend CNsiFloat NRXDBGATE_EXPORT operator/ (const real, const CNsiFloat &)   ;
	        CNsiFloat operator/ (const int) const;
	 friend CNsiFloat NRXDBGATE_EXPORT operator/ (const int, const CNsiFloat &);
	        CNsiFloat &operator++ (void);
	        CNsiFloat &operator-- (void);
	        CNsiFloat &operator- (void);
private:
	real fvalue;
};

//////////////////////////////////////////////////////////////////////////
// CNsiReal
class CNsiReal: public CNsiApproxNum {
public:
	                            CNsiReal                (void);
	                            CNsiReal                (const CNsiReal &);
	    virtual                 ~CNsiReal               (void);
	virtual ENsiDataType        Type                    (void) const;
	virtual uint                ReturnLength    (void) const;
	virtual CNsiData *          checkAdd        (const CNsiData *) const;
	virtual CNsiData *          checkSub        (const CNsiData *) const;
	virtual CNsiData *          checkMul        (const CNsiData *) const;
	virtual CNsiData *          checkDiv        (const CNsiData *) const;
	virtual CNsiData *          checkSet        (const CNsiData *) const;
	virtual ENsiBoolean         isEqualTo       (const CNsiData &) const;
	virtual ENsiBoolean         isGreaterThan   (const CNsiData &) const;
	virtual ENsiBoolean         storeValue              (real);
	virtual ENsiBoolean         storeValue              (integer);
	virtual ENsiBoolean         storeValue              (smallint);
	virtual ENsiBoolean         storeValue              (char *, uint);
	virtual ENsiBoolean         storeValue              (const CNsiUcStr &);
	virtual ENsiBoolean         storeValue              (const CNsiData &);
	virtual ENsiBoolean         storeValue              (char *, uint, uint *);
	virtual ENsiBoolean         storeValue              (const NsiUcStr);
	virtual ENsiBoolean         SQLType                 (CNsiUcStr *) const;
	virtual ENsiBoolean         SQLLiteral              (CNsiUcStr *) const;
	virtual integer             intValue                (void) const;
	virtual real                realValue               (void) const;
	virtual ENsiBoolean         getValue                (real *) const;
	virtual ENsiBoolean         getValue                (integer *) const;
	virtual ENsiBoolean         getValue                (smallint *) const;
	virtual ENsiBoolean         getValue                (char *, uint) const;
	virtual ENsiBoolean         getValue                (CNsiUcStr *) const;
	virtual ENsiBoolean         getValue                (char *, uint, uint *) const;
	virtual ENsiBoolean         getValue                (NsiUcStr, uint) const;
	virtual ENsiBoolean         getValue                (CNsiData &) const;
	virtual DBCOLUMNINFO *        MapNsiToColumnInfo        (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO *        MapNsiToParamInfo        (DBPARAMINFO *) const;
	virtual unsigned long       packSize        (void) const;
	virtual unsigned long       packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean         unpackFrom      (CNsiObjPack *);
	virtual unsigned long       packValueSize   (void)  const;
	virtual unsigned long       packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean         unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject   *      duplicate               (void) const;
	        CNsiReal &operator= (const CNsiSmallInt &);
	        CNsiReal &operator= (const CNsiInt &);
	        CNsiReal &operator= (const CNsiNumeric &);
	        CNsiReal &operator= (const CNsiDecimal &);
	        CNsiReal &operator= (const CNsiFloat &);
	        CNsiReal &operator= (const CNsiReal &);
	        CNsiReal &operator= (const CNsiDouble &);
	        CNsiReal &operator= (const smallint);
	        CNsiReal &operator= (const integer);
	        CNsiReal &operator= (const real);
	        CNsiReal &operator= (const int);
	        CNsiReal &operator+= (const CNsiSmallInt &);
	        CNsiReal &operator+= (const CNsiInt &);
	        CNsiReal &operator+= (const CNsiNumeric &);
	        CNsiReal &operator+= (const CNsiDecimal &);
	        CNsiReal &operator+= (const CNsiFloat &);
	        CNsiReal &operator+= (const CNsiReal &);
	        CNsiReal &operator+= (const CNsiDouble &);
	        CNsiReal &operator+= (const smallint);
	        CNsiReal &operator+= (const integer);
	        CNsiReal &operator+= (const real);
	        CNsiReal &operator+= (const int);
	        CNsiReal &operator-= (const CNsiSmallInt &);
	        CNsiReal &operator-= (const CNsiInt &);
	        CNsiReal &operator-= (const CNsiNumeric &);
	        CNsiReal &operator-= (const CNsiDecimal &);
	        CNsiReal &operator-= (const CNsiFloat &);
	        CNsiReal &operator-= (const CNsiReal &);
	        CNsiReal &operator-= (const CNsiDouble &);
	        CNsiReal &operator-= (const smallint);
	        CNsiReal &operator-= (const integer);
	        CNsiReal &operator-= (const real);
	        CNsiReal &operator-= (const int);
	        CNsiReal &operator*= (const CNsiSmallInt &);
	        CNsiReal &operator*= (const CNsiInt &);
	        CNsiReal &operator*= (const CNsiNumeric &);
	        CNsiReal &operator*= (const CNsiDecimal &);
	        CNsiReal &operator*= (const CNsiFloat &);
	        CNsiReal &operator*= (const CNsiReal &);
	        CNsiReal &operator*= (const CNsiDouble &);
	        CNsiReal &operator*= (const smallint);
	        CNsiReal &operator*= (const integer);
	        CNsiReal &operator*= (const real);
	        CNsiReal &operator*= (const int);
	        CNsiReal &operator/= (const CNsiSmallInt &);
	        CNsiReal &operator/= (const CNsiInt &);
	        CNsiReal &operator/= (const CNsiNumeric &);
	        CNsiReal &operator/= (const CNsiDecimal &);
	        CNsiReal &operator/= (const CNsiFloat &);
	        CNsiReal &operator/= (const CNsiReal &);
	        CNsiReal &operator/= (const CNsiDouble &);
	        CNsiReal &operator/= (const smallint);
	        CNsiReal &operator/= (const integer);
	        CNsiReal &operator/= (const real);
	        CNsiReal &operator/= (const int);
	        CNsiReal operator+ (const CNsiSmallInt &) const;
	        CNsiReal operator+ (const CNsiInt &)      const;
	        CNsiReal operator+ (const CNsiNumeric &)  const;
	        CNsiReal operator+ (const CNsiDecimal &)  const;
	        CNsiReal operator+ (const CNsiFloat &)    const;
	        CNsiReal operator+ (const CNsiReal &)     const;
	 friend CNsiReal NRXDBGATE_EXPORT operator+ (const CNsiSmallInt &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator+ (const CNsiInt &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator+ (const CNsiNumeric &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator+ (const CNsiDecimal &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator+ (const CNsiFloat &, const CNsiReal &)  ;
	        CNsiReal operator+ (const smallint) const;
	        CNsiReal operator+ (const integer)  const;
	        CNsiReal operator+ (const real)     const;
	 friend CNsiReal NRXDBGATE_EXPORT operator+ (const smallint, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator+ (const integer, const CNsiReal &) ;
	 friend CNsiReal NRXDBGATE_EXPORT operator+ (const real, const CNsiReal &)    ;
	        CNsiReal operator+ (const int) const;
	 friend CNsiReal NRXDBGATE_EXPORT operator+ (const int, const CNsiReal &);
	        CNsiReal operator- (const CNsiSmallInt &) const;
	        CNsiReal operator- (const CNsiInt &)      const;
	        CNsiReal operator- (const CNsiNumeric &)  const;
	        CNsiReal operator- (const CNsiDecimal &)  const;
	        CNsiReal operator- (const CNsiFloat &)    const;
	        CNsiReal operator- (const CNsiReal &)     const;
	 friend CNsiReal NRXDBGATE_EXPORT operator- (const CNsiSmallInt &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator- (const CNsiInt &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator- (const CNsiNumeric &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator- (const CNsiDecimal &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator- (const CNsiFloat &, const CNsiReal &)  ;
	        CNsiReal operator- (const smallint) const;
	        CNsiReal operator- (const integer)  const;
	        CNsiReal operator- (const real)     const;
	 friend CNsiReal NRXDBGATE_EXPORT operator- (const smallint, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator- (const integer, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator- (const real, const CNsiReal &);
	        CNsiReal operator- (const int) const;
	 friend CNsiReal NRXDBGATE_EXPORT operator- (const int, const CNsiReal &);
	        CNsiReal operator* (const CNsiSmallInt &) const;
	        CNsiReal operator* (const CNsiInt &)      const;
	        CNsiReal operator* (const CNsiNumeric &)  const;
	        CNsiReal operator* (const CNsiDecimal &)  const;
	        CNsiReal operator* (const CNsiFloat &)    const;
	        CNsiReal operator* (const CNsiReal &)     const;
	 friend CNsiReal NRXDBGATE_EXPORT operator* (const CNsiSmallInt &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator* (const CNsiInt &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator* (const CNsiNumeric &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator* (const CNsiDecimal &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator* (const CNsiFloat &, const CNsiReal &)  ;
	        CNsiReal operator* (const smallint) const;
	        CNsiReal operator* (const integer)  const;
	        CNsiReal operator* (const real)     const;
	 friend CNsiReal NRXDBGATE_EXPORT operator* (const smallint, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator* (const integer, const CNsiReal &) ;
	 friend CNsiReal NRXDBGATE_EXPORT operator* (const real, const CNsiReal &)    ;
	        CNsiReal operator* (const int) const;
	 friend CNsiReal NRXDBGATE_EXPORT operator* (const int, const CNsiReal &);
	        CNsiReal operator/ (const CNsiSmallInt &) const;
	        CNsiReal operator/ (const CNsiInt &)      const;
	        CNsiReal operator/ (const CNsiNumeric &)  const;
	        CNsiReal operator/ (const CNsiDecimal &)  const;
	        CNsiReal operator/ (const CNsiFloat &)    const;
	        CNsiReal operator/ (const CNsiReal &)     const;
	 friend CNsiReal NRXDBGATE_EXPORT operator/ (const CNsiSmallInt &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator/ (const CNsiInt &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator/ (const CNsiNumeric &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator/ (const CNsiDecimal &, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator/ (const CNsiFloat &, const CNsiReal &)  ;
	        CNsiReal operator/ (const smallint) const;
	        CNsiReal operator/ (const integer)  const;
	        CNsiReal operator/ (const real)     const;
	 friend CNsiReal NRXDBGATE_EXPORT operator/ (const smallint, const CNsiReal &);
	 friend CNsiReal NRXDBGATE_EXPORT operator/ (const integer, const CNsiReal &) ;
	 friend CNsiReal NRXDBGATE_EXPORT operator/ (const real, const CNsiReal &);
	        CNsiReal operator/ (const int) const;
	 friend CNsiReal NRXDBGATE_EXPORT operator/ (const int, const CNsiReal &);
	        CNsiReal &operator++ (void);
	        CNsiReal &operator-- (void);
	        CNsiReal &operator- (void);
private:
	real rvalue;
};

//////////////////////////////////////////////////////////////////////////
// CNsiDouble
class CNsiDouble: public CNsiApproxNum {
public:
	                            CNsiDouble              (void);
	                            CNsiDouble              (const CNsiDouble &);
	virtual                     ~CNsiDouble     (void);
	virtual ENsiDataType Type           (void) const;
	virtual uint         ReturnLength   (void) const;
	virtual CNsiData *   checkAdd       (const CNsiData *) const;
	virtual CNsiData *   checkSub       (const CNsiData *) const;
	virtual CNsiData *   checkMul       (const CNsiData *) const;
	virtual CNsiData *   checkDiv       (const CNsiData *) const;
	virtual CNsiData *   checkSet       (const CNsiData *) const;
	virtual ENsiBoolean  isEqualTo      (const CNsiData &) const;
	virtual ENsiBoolean  isGreaterThan  (const CNsiData &) const;
	virtual ENsiBoolean   storeValue    (real);
	virtual ENsiBoolean   storeValue    (integer);
	virtual ENsiBoolean   storeValue    (smallint);
	virtual ENsiBoolean   storeValue    (char *, uint);
	virtual ENsiBoolean   storeValue    (const CNsiUcStr &);
	virtual ENsiBoolean   storeValue    (const CNsiData &);
	virtual ENsiBoolean   storeValue    (char *, uint, uint *);
	virtual ENsiBoolean   storeValue    (const NsiUcStr);
	virtual integer       intValue      (void) const;
	virtual real          realValue     (void) const;
	virtual ENsiBoolean   getValue              (real *) const;
	virtual ENsiBoolean   getValue              (integer *) const;
	virtual ENsiBoolean   getValue              (smallint *) const;
	virtual ENsiBoolean   getValue              (char *, uint) const;
	virtual ENsiBoolean   getValue              (CNsiUcStr *) const;
	virtual ENsiBoolean   getValue              (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue              (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue              (CNsiData &) const;
	virtual DBCOLUMNINFO *  MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO *   MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean   SQLType       (CNsiUcStr *) const;
	virtual ENsiBoolean   SQLLiteral    (CNsiUcStr *) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject   *duplicate (void) const;
	        CNsiDouble &operator= (const CNsiSmallInt &);
	        CNsiDouble &operator= (const CNsiInt &);
	        CNsiDouble &operator= (const CNsiNumeric &);
	        CNsiDouble &operator= (const CNsiDecimal &);
	        CNsiDouble &operator= (const CNsiFloat &);
	        CNsiDouble &operator= (const CNsiReal &);
	        CNsiDouble &operator= (const CNsiDouble &);
	        CNsiDouble &operator= (const smallint);
	        CNsiDouble &operator= (const integer);
	        CNsiDouble &operator= (const real);
	        CNsiDouble &operator= (const int);
	        CNsiDouble &operator+= (const CNsiSmallInt &);
	        CNsiDouble &operator+= (const CNsiInt &);
	        CNsiDouble &operator+= (const CNsiNumeric &);
	        CNsiDouble &operator+= (const CNsiDecimal &);
	        CNsiDouble &operator+= (const CNsiFloat &);
	        CNsiDouble &operator+= (const CNsiReal &);
	        CNsiDouble &operator+= (const CNsiDouble &);
	        CNsiDouble &operator+= (const smallint);
	        CNsiDouble &operator+= (const integer);
	        CNsiDouble &operator+= (const real);
	        CNsiDouble &operator+= (const int);
	        CNsiDouble &operator-= (const CNsiSmallInt &);
	        CNsiDouble &operator-= (const CNsiInt &);
	        CNsiDouble &operator-= (const CNsiNumeric &);
	        CNsiDouble &operator-= (const CNsiDecimal &);
	        CNsiDouble &operator-= (const CNsiFloat &);
	        CNsiDouble &operator-= (const CNsiReal &);
	        CNsiDouble &operator-= (const CNsiDouble &);
	        CNsiDouble &operator-= (const smallint);
	        CNsiDouble &operator-= (const integer);
	        CNsiDouble &operator-= (const real);
	        CNsiDouble &operator-= (const int);
	        CNsiDouble &operator*= (const CNsiSmallInt &);
	        CNsiDouble &operator*= (const CNsiInt &);
	        CNsiDouble &operator*= (const CNsiNumeric &);
	        CNsiDouble &operator*= (const CNsiDecimal &);
	        CNsiDouble &operator*= (const CNsiFloat &);
	        CNsiDouble &operator*= (const CNsiReal &);
	        CNsiDouble &operator*= (const CNsiDouble &);
	        CNsiDouble &operator*= (const smallint);
	        CNsiDouble &operator*= (const integer);
	        CNsiDouble &operator*= (const real);
	        CNsiDouble &operator*= (const int);
	        CNsiDouble &operator/= (const CNsiSmallInt &);
	        CNsiDouble &operator/= (const CNsiInt &);
	        CNsiDouble &operator/= (const CNsiNumeric &);
	        CNsiDouble &operator/= (const CNsiDecimal &);
	        CNsiDouble &operator/= (const CNsiFloat &);
	        CNsiDouble &operator/= (const CNsiReal &);
	        CNsiDouble &operator/= (const CNsiDouble &);
	        CNsiDouble &operator/= (const smallint);
	        CNsiDouble &operator/= (const integer);
	        CNsiDouble &operator/= (const real);
	        CNsiDouble &operator/= (const int);
	        CNsiDouble operator+ (const CNsiSmallInt &) const;
	        CNsiDouble operator+ (const CNsiInt &)      const;
	        CNsiDouble operator+ (const CNsiNumeric &)  const;
	        CNsiDouble operator+ (const CNsiDecimal &)  const;
	        CNsiDouble operator+ (const CNsiFloat &)    const;
	        CNsiDouble operator+ (const CNsiReal &)     const;
	        CNsiDouble operator+ (const CNsiDouble &)   const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiSmallInt &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiInt &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiNumeric &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiDecimal &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiFloat &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const CNsiReal &, const CNsiDouble &);
	        CNsiDouble operator+ (const smallint) const;
	        CNsiDouble operator+ (const integer)  const;
	        CNsiDouble operator+ (const real)     const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const smallint, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const integer, const CNsiDouble &) ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const real, const CNsiDouble &)    ;
	        CNsiDouble operator+ (const int) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator+ (const int, const CNsiDouble &);
	        CNsiDouble operator- (const CNsiSmallInt &) const;
	        CNsiDouble operator- (const CNsiInt &)      const;
	        CNsiDouble operator- (const CNsiNumeric &)  const;
	        CNsiDouble operator- (const CNsiDecimal &)  const;
	        CNsiDouble operator- (const CNsiFloat &)    const;
	        CNsiDouble operator- (const CNsiReal &)     const;
	        CNsiDouble operator- (const CNsiDouble &)   const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiSmallInt &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiInt &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiNumeric &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiDecimal &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiFloat &, const CNsiDouble &)  ;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const CNsiReal &, const CNsiDouble &);
	        CNsiDouble operator- (const smallint) const;
	        CNsiDouble operator- (const integer)  const;
	        CNsiDouble operator- (const real)     const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const smallint, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const integer, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const real, const CNsiDouble &);
	        CNsiDouble operator- (const int) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator- (const int, const CNsiDouble &);
	        CNsiDouble operator* (const CNsiSmallInt &) const;
	        CNsiDouble operator* (const CNsiInt &)      const;
	        CNsiDouble operator* (const CNsiNumeric &)  const;
	        CNsiDouble operator* (const CNsiDecimal &)  const;
	        CNsiDouble operator* (const CNsiFloat &)    const;
	        CNsiDouble operator* (const CNsiReal &)     const;
	        CNsiDouble operator* (const CNsiDouble &)   const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiSmallInt &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiInt &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiNumeric &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiDecimal &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiFloat &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const CNsiReal &, const CNsiDouble &);
	        CNsiDouble operator* (const smallint) const;
	        CNsiDouble operator* (const integer) const;
	        CNsiDouble operator* (const real) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const smallint, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const integer, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const real, const CNsiDouble &);
	        CNsiDouble operator* (const int) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator* (const int, const CNsiDouble &);
	        CNsiDouble operator/ (const CNsiSmallInt &) const;
	        CNsiDouble operator/ (const CNsiInt &)      const;
	        CNsiDouble operator/ (const CNsiNumeric &)  const;
	        CNsiDouble operator/ (const CNsiDecimal &)  const;
	        CNsiDouble operator/ (const CNsiFloat &)    const;
	        CNsiDouble operator/ (const CNsiReal &)     const;
	        CNsiDouble operator/ (const CNsiDouble &)   const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiSmallInt &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiInt &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiNumeric &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiDecimal &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiFloat &, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const CNsiReal &, const CNsiDouble &);
	        CNsiDouble operator/ (const smallint) const;
	        CNsiDouble operator/ (const integer)  const;
	        CNsiDouble operator/ (const real)     const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const smallint, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const integer, const CNsiDouble &);
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const real, const CNsiDouble &);
	        CNsiDouble operator/ (const int) const;
	 friend CNsiDouble NRXDBGATE_EXPORT operator/ (const int, const CNsiDouble &);
	        CNsiDouble &operator++ (void);
	        CNsiDouble &operator-- (void);
	        CNsiDouble &operator- (void);
private:
	real dvalue;
};

//////////////////////////////////////////////////////////////////////////
// CNsiChar
class CNsiChar: public CNsiData {
	friend class CNsiTempTable;
public:
	                                    CNsiChar                ();
	                                    CNsiChar                (uint);
	                                    CNsiChar                (const CNsiChar &);
	    virtual                                 ~CNsiChar               ();
	void                                setVarying      (void);
	void                                setNational     (void);
	void                                setCharSet      (const CNsiUcStr &);
	void                                setDefCharSet   (void);
	void                                setCollName     (const CNsiUcStr &);
	void                                setCollIdent    (NsiUcIdCLT);
	void                                setCoerc        (ENsiCAttr);
	virtual ENsiDataType    Type                (void) const;
	virtual uint            Length              (void) const;
	virtual uint            ReturnLength        (void) const;
	uint                        ByteSize        (void) const;
	const CNsiUcStr   &         CollName        (void) const;
	const CNsiUcStr   &         CharSetName     (void) const;
	NsiUcIdCLT                  CollIdent       (void) const;
	NsiUcIdCCT                  CharSetIdent    (void) const;
	ENsiCAttr                   Coercibility    (void) const;
	virtual ENsiBoolean         is_character    (void) const;
	virtual ENsiBoolean         is_comparable   (const CNsiData *) const;
	virtual ENsiBoolean         is_storable     (const CNsiData *) const;
	virtual ENsiBoolean         is_castable     (const CNsiData *) const;
	        ENsiBoolean         is_national     (void) const;
	virtual CNsiData *          checkCat        (const CNsiData *) const;
	virtual CNsiData *          checkSet        (const CNsiData *) const;
	virtual ENsiBoolean         isEqualTo       (const CNsiData &) const;
	virtual ENsiBoolean         isGreaterThan   (const CNsiData &) const;
	virtual ENsiBoolean         storeValue              (real);
	virtual ENsiBoolean         storeValue              (integer);
	virtual ENsiBoolean         storeValue              (smallint);
	virtual ENsiBoolean         storeValue              (char *, uint);
	        ENsiBoolean         storeValue              (char *, uint, NsiUcIdCCT);
	virtual ENsiBoolean         storeValue              (const CNsiUcStr &);
	virtual ENsiBoolean         storeValue              (const CNsiData &);
	virtual ENsiBoolean         storeValue              (const NsiUcStr);
	        ENsiBoolean         storeValue              (GUID *);
	virtual ENsiBoolean         storeValue              (char *, uint, uint *);
	    const CNsiUcStr  &      charValue (void) const;
	virtual ENsiBoolean         getValue                (real *) const;
	virtual ENsiBoolean         getValue                (integer *) const;
	virtual ENsiBoolean         getValue                (smallint *) const;
	virtual ENsiBoolean         getValue                (char *, uint) const;
	virtual ENsiBoolean         getValue                (CNsiUcStr *) const;
	virtual ENsiBoolean         getValue                (char *, uint, uint *) const;
	virtual ENsiBoolean         getValue                (NsiUcStr, uint) const;
	virtual ENsiBoolean         getValue                (CNsiData &) const;
	        ENsiBoolean         getValue                (GUID *) const;
	virtual DBCOLUMNINFO *        MapNsiToColumnInfo        (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO *        MapNsiToParamInfo        (DBPARAMINFO *) const;
	virtual ENsiBoolean         SQLType                 (CNsiUcStr *) const;
	virtual ENsiBoolean         SQLLiteral              (CNsiUcStr *) const;
	virtual unsigned long       packSize        (void)  const;
	virtual unsigned long       packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean         unpackFrom      (CNsiObjPack *);
	virtual unsigned long       packValueSize   (void)  const;
	virtual unsigned long       packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean         unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject   *      duplicate               (void) const;
	virtual void                Clear                   (void);
	ENsiBoolean                         Like                    (const CNsiChar &, const CNsiChar &) const;
	CNsiChar                            Substring               (uint) const;
	CNsiChar                            Substring               (uint, uint) const;
	CNsiChar                            Upper                   (void) const;
	CNsiChar                            Lower                   (void) const;
	CNsiChar                            Trim                    (ENsiTrimSpec, const CNsiChar &) const;
	CNsiNumeric                         Position                (const CNsiChar &) const;
	        CNsiChar  & operator=  (const CNsiChar &);
	        CNsiChar  & operator=  (const CNsiUcStr &);
	        CNsiChar    operator+  (const CNsiChar &) const;
	        CNsiChar    operator+  (const CNsiUcStr &) const;
	        int         operator>  (const CNsiChar &) const;
	        int         operator>  (const CNsiUcStr &) const;
	 friend int         NRXDBGATE_EXPORT operator>  (const CNsiUcStr &, const CNsiChar &);
	        int         operator>=  (const CNsiChar &) const;
	        int         operator>=  (const CNsiUcStr &) const;
	 friend int         NRXDBGATE_EXPORT operator>=  (const CNsiUcStr &, const CNsiChar &);
	        int         operator==  (const CNsiChar &) const;
	        int         operator==  (const CNsiUcStr &) const;
	 friend int         NRXDBGATE_EXPORT operator==  (const CNsiUcStr &, const CNsiChar &);
	        int         operator<=  (const CNsiChar &) const;
	        int         operator<=  (const CNsiUcStr &) const;
	 friend int         NRXDBGATE_EXPORT operator<=  (const CNsiUcStr &, const CNsiChar &);
	        int         operator<  (const CNsiChar &) const;
	        int         operator<  (const CNsiUcStr &) const;
	 friend int         NRXDBGATE_EXPORT operator<  (const CNsiUcStr &, const CNsiChar &);
	        int         operator!=  (const CNsiChar &) const;
	        int         operator!=  (const CNsiUcStr &) const;
	 friend int         NRXDBGATE_EXPORT operator!=  (const CNsiUcStr &, const CNsiChar &);
private:
	ENsiBoolean     isCompColSet(const NsiUcIdCLT, ENsiCAttr) const;
	NsiUcIdCLT      CompColSet(const NsiUcIdCLT, ENsiCAttr) const;
	ENsiBoolean     isDyadicOpColSet(const NsiUcIdCLT, ENsiCAttr) const;
	NsiUcIdCLT      DyadicOpColSet(const NsiUcIdCLT, ENsiCAttr *, ENsiCAttr) const;
private:
	uint                maxlength;
	uint                retlength;
	CNsiUcStr           chvalue;
	short           mod;
	NsiUcIdCCT      CharSetId;
	CNsiUcStr       CharSet;
	NsiUcIdCLT      ColId;
	CNsiUcStr       CName;
	ENsiCAttr       coercibility;
};

//////////////////////////////////////////////////////////////////////////
// CNsiBinary
class CNsiBinary: public CNsiData {
	friend class CNsiTempTable;
public:
	        CNsiBinary  ();
	        CNsiBinary  (uint);
	        CNsiBinary  (const CNsiBinary &);
	virtual ~CNsiBinary ();
	       void          setVarying    (void);
	virtual ENsiDataType Type         (void) const;
	virtual uint         Length       (void) const;
	virtual uint         ReturnLength (void) const;
	virtual ENsiBoolean   is_binary     (void) const;
	virtual ENsiBoolean   is_comparable (const CNsiData *) const;
	virtual ENsiBoolean   is_storable   (const CNsiData *) const;
	virtual ENsiBoolean   is_castable   (const CNsiData *) const;
	virtual CNsiData *    checkCat      (const CNsiData *) const;
	virtual CNsiData *    checkSet      (const CNsiData *) const;
	virtual ENsiBoolean   isEqualTo     (const CNsiData &) const;
	virtual ENsiBoolean   isGreaterThan (const CNsiData &) const;
	        ENsiBoolean   storeHexValue (char *, uint, uint *);
	        ENsiBoolean   storeHexValue (const CNsiUcStr &);
	        ENsiBoolean   storeBinValue (char *, uint, uint *);
	        ENsiBoolean   storeBinValue (const CNsiUcStr &);
	virtual ENsiBoolean   storeValue    (char *, uint);
	virtual ENsiBoolean   storeValue    (char *, uint, uint *);
	virtual ENsiBoolean   storeValue    (const CNsiData &);
	virtual ENsiBoolean   storeValue (real);
	virtual ENsiBoolean   storeValue (integer);
	virtual ENsiBoolean   storeValue (smallint);
	virtual ENsiBoolean   storeValue (const CNsiUcStr &);
	virtual ENsiBoolean   storeValue (const NsiUcStr);
	        ENsiBoolean   getHexValue (char *, uint, uint *) const;
	        ENsiBoolean   getHexValue (CNsiUcStr *) const;
	        ENsiBoolean   getBinValue (char *, uint, uint *) const;
	        ENsiBoolean   getBinValue (CNsiUcStr *) const;
	virtual ENsiBoolean   getValue    (char *, uint) const;
	virtual ENsiBoolean   getValue    (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue (real *) const;
	virtual ENsiBoolean   getValue (integer *) const;
	virtual ENsiBoolean   getValue (smallint *) const;
	virtual ENsiBoolean   getValue (CNsiUcStr *) const;
	virtual ENsiBoolean   getValue (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue (CNsiData &) const;
	virtual DBCOLUMNINFO *MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO * MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean   SQLType    (CNsiUcStr *) const;
	virtual ENsiBoolean   SQLLiteral (CNsiUcStr *) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject   *duplicate(void) const;
	virtual void          Clear     (void);
	CNsiBinary Substring(uint);
	CNsiBinary Substring(uint,uint);
	        CNsiBinary   &operator= (const CNsiBinary &);
	        CNsiBinary  operator+  (const CNsiBinary &) const;
	        int         operator>  (const CNsiBinary &) const;
	        int         operator>= (const CNsiBinary &) const;
	        int         operator== (const CNsiBinary &) const;
	        int         operator<= (const CNsiBinary &) const;
	        int         operator<  (const CNsiBinary &) const;
	        int         operator!= (const CNsiBinary &) const;
private:
	uint       blength;
	uint       alength;
	uint       buflen;
	uchar    * value;
	short      mod;
};

//////////////////////////////////////////////////////////////////////////
// CNsiIQualifier
class CNsiIQualifier : public CNsiData {
	friend class CNsiInterval;
	friend class CNsiDatetime;
public:
	           CNsiIQualifier (void);
	           CNsiIQualifier (ENsiIType);
	           CNsiIQualifier (ENsiIType, uint);
	           CNsiIQualifier (ENsiIType, uint, uint);
	           CNsiIQualifier (const CNsiIQualifier &);
	virtual   ~CNsiIQualifier (void);
	virtual ENsiBoolean  setIType         (ENsiIType);
	        void         setLeadFieldPrec (uint);
	        void         setFracSecPrec   (uint);
	virtual ENsiDataType Type          (void) const;
	virtual ENsiIType    IntervalType  (void) const;
	virtual uint         LeadFieldPrec (void) const;
	virtual uint         FracSecPrec   (void) const;
	virtual uint         ReturnLength  (void) const;
	virtual ENsiBoolean  is_interval     (void) const;
	virtual ENsiBoolean  is_yminterval   (void) const;
	virtual ENsiBoolean  is_dtinterval   (void) const;
	virtual ENsiBoolean  is_storable     (const CNsiData *) const;
	virtual ENsiBoolean  is_comparable   (const CNsiData *) const;
	        ENsiBoolean  is_moreaccurate (const CNsiIQualifier *) const;
	virtual ENsiBoolean  SQLType       (CNsiUcStr *) const;
private:
	virtual ENsiBoolean  SQLLiteral    (CNsiUcStr *) const;
public:
	        CNsiIQualifier &operator= (const CNsiIQualifier &);
	virtual CNsiObject   *duplicate(void) const;
protected:
	ENsiIType itype;
	uint lfp;
	uint fsp;
};

//////////////////////////////////////////////////////////////////////////
// CNsiInterval
class CNsiInterval : public CNsiIQualifier {
	friend class CNsiDate;
	friend class CNsiTime;
	friend class CNsiTimeStamp;
public:
	        CNsiInterval                (void);
	virtual ~CNsiInterval               (void);
	virtual ENsiBoolean   SQLType       (CNsiUcStr *)      const;
	virtual CNsiData *    checkAdd      (const CNsiData *) const;
	virtual CNsiData *    checkSub      (const CNsiData *) const;
	virtual CNsiData *    checkMul      (const CNsiData *) const;
	virtual CNsiData *    checkDiv      (const CNsiData *) const;
	virtual CNsiData *    checkSet      (const CNsiData *) const;
	        void          setSign  (ENsiBoolean);
	        ENsiBoolean   Sign          (void)             const;
protected:
	ENsiBoolean sign;
};

//////////////////////////////////////////////////////////////////////////
// CNsiYM
class CNsiYM : public CNsiInterval {
	friend class CNsiDate;
	friend class CNsiTime;
	friend class CNsiTimeStamp;
	friend class CNsiTempTable;
public:
	        CNsiYM (void);
	        CNsiYM (ENsiIType);
	        CNsiYM (ENsiIType, uint);
	        CNsiYM (const CNsiYM &);
	virtual ~CNsiYM (void);
	virtual ENsiBoolean   setIType      (ENsiIType);
	virtual ENsiBoolean   is_castable   (const CNsiData *) const;
	virtual ENsiBoolean   isEqualTo     (const CNsiData &) const;
	virtual ENsiBoolean   isGreaterThan (const CNsiData &) const;
	virtual ENsiBoolean   storeValue (integer);
	virtual ENsiBoolean   storeValue (smallint);
	virtual ENsiBoolean   storeValue (char *, uint);
	virtual ENsiBoolean   storeValue (const CNsiUcStr &);
	virtual ENsiBoolean   storeValue (const CNsiData &);
	virtual ENsiBoolean   storeValue (real);
	virtual ENsiBoolean   storeValue (char *, uint, uint *);
	virtual ENsiBoolean   storeValue (const NsiUcStr);
	   ENsiBoolean   set       (NSI_IYEAR *);
	   ENsiBoolean   set       (NSI_IYEARTOMONTH *);
	   ENsiBoolean   set       (NSI_IMONTH *);
	   ENsiBoolean   set       (ENsiBoolean, uint, uint);
	   ENsiBoolean   setYears  (uint);
	   ENsiBoolean   setMonths (uint);
	virtual ENsiBoolean   getValue (integer *) const;
	virtual ENsiBoolean   getValue (smallint *) const;
	virtual ENsiBoolean   getValue (char *, uint) const;
	virtual ENsiBoolean   getValue (CNsiUcStr *) const;
	virtual ENsiBoolean   getValue (real *) const;
	virtual ENsiBoolean   getValue (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue (CNsiData &) const;
	virtual DBCOLUMNINFO *MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO * MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean   SQLLiteral (CNsiUcStr *) const;
	        ENsiBoolean   get       (NSI_IYEAR *)        const;
	        ENsiBoolean   get       (NSI_IYEARTOMONTH *) const;
	        ENsiBoolean   get       (NSI_IMONTH *)       const;
	        ENsiBoolean   get       (ENsiBoolean *, uint *, uint *) const;
	        ENsiBoolean   getYears  (uint *) const;
	        ENsiBoolean   getMonths (uint *) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject   *duplicate (void) const;
	    CNsiYM       &operator=  (const CNsiYM &);
	    CNsiYM       &operator=  (const CNsiSmallInt &);
	    CNsiYM       &operator=  (const CNsiInt &);
	    CNsiYM       &operator=  (const CNsiNumeric &);
	    CNsiYM       &operator=  (const CNsiDecimal &);
	    CNsiYM       &operator=  (integer);
	    CNsiYM       operator+  (const CNsiYM &) const;
	friend  CNsiDate NRXDBGATE_EXPORT operator+  (const CNsiYM &, const CNsiDate &);
	    CNsiYM       operator-  (const CNsiYM &) const;
	   CNsiYM       operator*  (const CNsiSmallInt &) const;
	   CNsiYM       operator*  (const CNsiInt &) const;
	   CNsiYM       operator*  (const CNsiNumeric &) const;
	   CNsiYM       operator*  (const CNsiDecimal &) const;
	   CNsiYM       operator*  (integer) const;
friend CNsiYM NRXDBGATE_EXPORT operator*  (const CNsiSmallInt &,const CNsiYM &);
friend CNsiYM NRXDBGATE_EXPORT operator*  (const CNsiInt &,     const CNsiYM &);
friend CNsiYM NRXDBGATE_EXPORT operator*  (const CNsiNumeric &, const CNsiYM &);
friend CNsiYM NRXDBGATE_EXPORT operator*  (const CNsiDecimal &, const CNsiYM &);
friend CNsiYM NRXDBGATE_EXPORT operator*  (integer,             const CNsiYM &);
        CNsiYM       operator/  (const CNsiSmallInt &) const;
        CNsiYM       operator/  (const CNsiInt &)      const;
        CNsiYM       operator/  (const CNsiNumeric &)  const;
        CNsiYM       operator/  (const CNsiDecimal &)  const;
        CNsiYM       operator/  (integer)              const;
        CNsiYM       &operator-  (void);
       int           operator>  (const CNsiYM &) const;
       int           operator>= (const CNsiYM &) const;
       int           operator== (const CNsiYM &) const;
       int           operator<= (const CNsiYM &) const;
       int           operator<  (const CNsiYM &) const;
       int           operator!= (const CNsiYM &) const;
private:
	   char *        getYMString (char *, size_t) const;
protected:
	ulong ivalue;
};

//////////////////////////////////////////////////////////////////////////
// CNsiDT
class CNsiDT : public CNsiInterval {

	friend class CNsiDate;
	friend class CNsiTime;
	friend class CNsiTimeStamp;
	friend class CNsiTempTable;
private:
	            void        ChkMul     (real);
	            void        ChkDiv     (real);
	            int         cmpDTI     (const CNsiDT&) const;
	            ENsiBoolean ChkSet     (double);
	            void        ChkSet2    (double);
	            double      LocalToUTC (double) const;
	            double      UTCToLocal (double) const;
public:
	        CNsiDT (void);
	        CNsiDT (ENsiIType);
	        CNsiDT (ENsiIType, uint);
	        CNsiDT (ENsiIType, uint, uint);
	        CNsiDT (const CNsiDT &);
	virtual ~CNsiDT (void);
	virtual ENsiBoolean   setIType      (ENsiIType);
	virtual ENsiBoolean   is_castable   (const CNsiData *) const;
	virtual ENsiBoolean   isEqualTo     (const CNsiData &) const;
	virtual ENsiBoolean   isGreaterThan (const CNsiData &) const;
	virtual ENsiBoolean   storeValue (integer);
	virtual ENsiBoolean   storeValue (smallint);
	virtual ENsiBoolean   storeValue (char *, uint);
	virtual ENsiBoolean   storeValue (const CNsiUcStr &);
	virtual ENsiBoolean   storeValue (const CNsiData &);
	virtual ENsiBoolean   storeValue (real);
	virtual ENsiBoolean   storeValue (char *, uint, uint *);
	virtual ENsiBoolean   storeValue (const NsiUcStr);
	        ENsiBoolean   set        (NSI_IDAY *);
	        ENsiBoolean   set        (NSI_IHOUR *);
	        ENsiBoolean   set        (NSI_IMINUTE *);
	        ENsiBoolean   set        (NSI_ISECOND *);
	        ENsiBoolean   set        (NSI_IDAYTOHOUR *);
	        ENsiBoolean   set        (NSI_IDAYTOMINUTE *);
	        ENsiBoolean   set        (NSI_IDAYTOSECOND *);
	        ENsiBoolean   set        (NSI_IHOURTOMINUTE *);
	        ENsiBoolean   set        (NSI_IHOURTOSECOND *);
	        ENsiBoolean   set        (NSI_IMINUTETOSECOND *);
	        ENsiBoolean   set        (ENsiBoolean, uint, uint, uint, double);
	        ENsiBoolean   setDays    (uint);
	        ENsiBoolean   setHours   (uint);
	        ENsiBoolean   setMinutes (uint);
	        ENsiBoolean   setSeconds (double);
	virtual ENsiBoolean   getValue   (integer *)      const;
	virtual ENsiBoolean   getValue   (smallint *)     const;
	virtual ENsiBoolean   getValue   (char *, uint)   const;
	virtual ENsiBoolean   getValue   (CNsiUcStr *)    const;
	virtual ENsiBoolean   getValue (real *) const;
	virtual ENsiBoolean   getValue (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue (CNsiData &) const;
	virtual DBCOLUMNINFO *MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO * MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean   SQLLiteral (CNsiUcStr *) const;
	        ENsiBoolean   get        (NSI_IDAY *)            const;
	        ENsiBoolean   get        (NSI_IHOUR *)           const;
	        ENsiBoolean   get        (NSI_IMINUTE *)         const;
	        ENsiBoolean   get        (NSI_ISECOND *)         const;
	        ENsiBoolean   get        (NSI_IDAYTOHOUR *)      const;
	        ENsiBoolean   get        (NSI_IDAYTOMINUTE *)    const;
	        ENsiBoolean   get        (NSI_IDAYTOSECOND *)    const;
	        ENsiBoolean   get        (NSI_IHOURTOMINUTE *)   const;
	        ENsiBoolean   get        (NSI_IHOURTOSECOND *)   const;
	        ENsiBoolean   get        (NSI_IMINUTETOSECOND *) const;
	        ENsiBoolean   get        (ENsiBoolean *, uint *, uint *, uint *,
	                                  double *) const;
	        ENsiBoolean   getDays    (uint *) const;
	        ENsiBoolean   getHours   (uint *) const;
	        ENsiBoolean   getMinutes (uint *) const;
	        ENsiBoolean   getSeconds (double *) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject   *duplicate (void) const;
	        CNsiDT       &operator=  (const CNsiDT &);
	        CNsiDT       &operator=  (const CNsiSmallInt &);
	        CNsiDT       &operator=  (const CNsiInt &);
	        CNsiDT       &operator=  (const CNsiNumeric &);
	        CNsiDT       &operator=  (const CNsiDecimal &);
	        CNsiDT       &operator=  (integer);
	        CNsiDT       operator+  (const CNsiDT &) const;
	        CNsiDT       operator-  (const CNsiDT &) const;
	        CNsiDT       operator*  (const CNsiSmallInt &) const;
	        CNsiDT       operator*  (const CNsiInt &)      const;
	        CNsiDT       operator*  (const CNsiNumeric &)  const;
	        CNsiDT       operator*  (const CNsiDecimal &)  const;
	        CNsiDT       operator*  (integer)              const;
	 friend CNsiDT NRXDBGATE_EXPORT operator*  (const CNsiSmallInt &,const CNsiDT &);
	 friend CNsiDT NRXDBGATE_EXPORT operator*  (const CNsiInt &,     const CNsiDT &);
	 friend CNsiDT NRXDBGATE_EXPORT operator*  (const CNsiNumeric &, const CNsiDT &);
	 friend CNsiDT NRXDBGATE_EXPORT operator*  (const CNsiDecimal &, const CNsiDT &);
	 friend CNsiDT NRXDBGATE_EXPORT operator*  (integer,             const CNsiDT &);
	        CNsiDT       operator/  (const CNsiSmallInt &) const;
	        CNsiDT       operator/  (const CNsiInt &)      const;
	        CNsiDT       operator/  (const CNsiNumeric &)  const;
	        CNsiDT       operator/  (const CNsiDecimal &)  const;
	        CNsiDT       operator/  (integer)              const;
	        CNsiDT       &operator-  (void);
	        int           operator>  (const CNsiDT &) const;
	        int           operator>= (const CNsiDT &) const;
	        int           operator== (const CNsiDT &) const;
	        int           operator<= (const CNsiDT &) const;
	        int           operator<  (const CNsiDT &) const;
	        int           operator!= (const CNsiDT &) const;
private:
	char * getDTString (char * , size_t) const;
protected:
	double ivalue;
};

//////////////////////////////////////////////////////////////////////////
// CNsiDatetime
class CNsiDatetime : public CNsiData {
public:
	        CNsiDatetime ();
	virtual ~CNsiDatetime ();
	virtual ENsiDataType Type          (void) const;
	virtual ENsiBoolean   is_datetime   (void) const;
	virtual ENsiBoolean   is_comparable (const CNsiData *) const;
	virtual CNsiData *    checkAdd      (const CNsiData *) const;
	virtual CNsiData *    checkSub      (const CNsiData *) const;
	virtual CNsiData  *   checkSet      (const CNsiData *) const;
	virtual ushort Year                 (void) const = 0;
	virtual ushort Month                (void) const = 0;
	virtual ushort Day                  (void) const = 0;
	virtual ushort Hour                 (void) const = 0;
	virtual ushort Minute               (void) const = 0;
	virtual double Second               (void) const = 0;
protected:
};

//////////////////////////////////////////////////////////////////////////
// CNsiDate
class CNsiDate: public CNsiDatetime {
	friend class CNsiTimeStamp;
	friend class CNsiTempTable;
public:
	        CNsiDate ();
	        CNsiDate (const CNsiDate &);
	virtual ~CNsiDate (void);
	virtual ENsiDTType   DateTimeType  (void) const;
	virtual uint         ReturnLength  (void) const;
	virtual ENsiBoolean  is_storable   (const CNsiData *) const;
	virtual ENsiBoolean  is_castable   (const CNsiData *) const;
	virtual ENsiBoolean   isEqualTo     (const CNsiData &) const;
	virtual ENsiBoolean   isGreaterThan (const CNsiData &) const;
	virtual ENsiBoolean  storeValue (char *, uint);
	virtual ENsiBoolean  storeValue (const CNsiUcStr &);
	virtual ENsiBoolean  storeValue (const CNsiData &);
	virtual ENsiBoolean  storeValue (const DBDATE *);
	virtual ENsiBoolean  storeValue (DATE);
	virtual ENsiBoolean   storeValue (integer);
	virtual ENsiBoolean   storeValue (smallint);
	virtual ENsiBoolean   storeValue (char *, uint, uint *);
	virtual ENsiBoolean   storeValue (const NsiUcStr);
	        ENsiBoolean  set      (NSI_DTDATE *);
	        ENsiBoolean  set      (const DBDATE *);
	        ENsiBoolean  set      (ushort, ushort, ushort);
	        ENsiBoolean  setYear  (ushort);
	        ENsiBoolean  setMonth (ushort);
	        ENsiBoolean  setDay   (ushort);
	        ENsiBoolean  get      (NSI_DTDATE *)  const;
	        ENsiBoolean  get      (DBDATE *)      const;
	virtual ENsiBoolean  getValue (char *, uint)  const;
	virtual ENsiBoolean  getValue (CNsiUcStr *)   const;
	virtual ENsiBoolean  getValue (DBDATE *)      const;
	virtual ENsiBoolean  getValue (DATE *)        const;
	virtual ENsiBoolean   getValue (integer *) const;
	virtual ENsiBoolean   getValue (smallint *) const;
	virtual ENsiBoolean   getValue (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue (CNsiData &) const;
	virtual DBCOLUMNINFO *MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO * MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean  SQLType    (CNsiUcStr *) const;
	virtual ENsiBoolean  SQLLiteral (CNsiUcStr *) const;
	virtual ushort       Year      (void) const;
	virtual ushort       Month     (void) const;
	virtual ushort       Day       (void) const;
	virtual ushort       Hour      (void) const;
	virtual ushort       Minute    (void) const;
	virtual double       Second    (void) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject   *duplicate (void) const;
	        CNsiDate    &operator=     (const CNsiDate &);
	        CNsiDate     operator+     (const CNsiYM &) const;
	        CNsiDate     operator+     (const CNsiDT &) const;
	 friend CNsiDate NRXDBGATE_EXPORT operator+     (const CNsiYM &, const CNsiDate &);
	 friend CNsiDate NRXDBGATE_EXPORT operator+     (const CNsiDT &, const CNsiDate &);
	        CNsiDate     operator-     (const CNsiYM &) const;
	        CNsiDate     operator-     (const CNsiDT &) const;
	        CNsiYM YMDiff (const CNsiDate &, const CNsiYM &)   const;
	        CNsiDT DTDiff (const CNsiDate &, const CNsiDT &)   const;
	        int          operator>     (const CNsiDate &)      const;
	        int          operator>=    (const CNsiDate &)      const;
	        int          operator==    (const CNsiDate &)      const;
	        int          operator<=    (const CNsiDate &)      const;
	        int          operator<     (const CNsiDate &)      const;
	        int          operator!=    (const CNsiDate &)      const;
protected:
	ulong month;
	ushort day;
};

//////////////////////////////////////////////////////////////////////////
// CNsiTime
class CNsiTime : public CNsiDatetime {
	friend class CNsiTimeStamp;
	friend class CNsiTempTable;
public:
	        CNsiTime  (void);
	        CNsiTime  (const CNsiDT&);
	        CNsiTime  (uint);
	        CNsiTime  (uint, const CNsiDT&);
	        CNsiTime  (const CNsiTime &);
	virtual ~CNsiTime (void);
	        void         setWithTimeZone (ENsiBoolean f = kNsiTrue );
	virtual ENsiDTType    DateTimeType  (void) const;
	virtual uint          TimePrec      (void) const;
	virtual uint          ReturnLength  (void) const;
	virtual ENsiBoolean   is_storable   (const CNsiData *) const;
	virtual ENsiBoolean   is_castable   (const CNsiData *) const;
	virtual ENsiBoolean   isEqualTo     (const CNsiData &) const;
	virtual ENsiBoolean   isGreaterThan (const CNsiData &) const;
	virtual ENsiBoolean  storeValue   (char *, uint);
	virtual ENsiBoolean  storeValue   (const CNsiUcStr &);
	virtual ENsiBoolean  storeValue   (const CNsiData &);
	virtual ENsiBoolean  storeValue   (const DBTIME *);
	virtual ENsiBoolean   storeValue (real);
	virtual ENsiBoolean   storeValue (integer);
	virtual ENsiBoolean   storeValue (smallint);
	virtual ENsiBoolean   storeValue (char *, uint, uint *);
	virtual ENsiBoolean   storeValue (const NsiUcStr);
	        ENsiBoolean  set           (NSI_DTTIME *);
	        ENsiBoolean  set           (const DBTIME *);
	        ENsiBoolean  set           (ushort, ushort, double);
	        ENsiBoolean  setHour       (ushort);
	        ENsiBoolean  setMinute     (ushort);
	        ENsiBoolean  setSecond     (double);
	        ENsiBoolean  setTimeZone   (const CNsiDT &);
	        ENsiBoolean  get          (NSI_DTTIME *) const;
	        ENsiBoolean  get          (DBTIME *)     const;
	virtual ENsiBoolean  getValue     (char *, uint) const;
	virtual ENsiBoolean  getValue     (CNsiUcStr *)  const;
	virtual ENsiBoolean  getValue     (DBTIME *)     const;
	virtual ENsiBoolean   getValue (real *) const;
	virtual ENsiBoolean   getValue (integer *) const;
	virtual ENsiBoolean   getValue (smallint *) const;
	virtual ENsiBoolean   getValue (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue (CNsiData &) const;
	virtual DBCOLUMNINFO *MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO * MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean  SQLType      (CNsiUcStr *) const;
	virtual ENsiBoolean  SQLLiteral   (CNsiUcStr *) const;
	virtual ushort       Year         (void) const {return 0;};
	virtual ushort       Month        (void) const {return 0;};
	virtual ushort       Day          (void) const {return 0;};
	virtual ushort       Hour         (void) const;
	virtual ushort       Minute       (void) const;
	virtual double       Second       (void) const;
	  const CNsiDT      &TimeZone     (void) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject  *duplicate (void) const;
	        CNsiTime    &operator=     (const CNsiTime &);
	        CNsiTime     operator+     (const CNsiDT &) const;
	 friend CNsiTime NRXDBGATE_EXPORT operator+     (const CNsiDT &, const CNsiTime &);
	        CNsiTime     operator-     (const CNsiDT &) const;
	        CNsiDT       DTDiff        (const CNsiTime &,const CNsiDT &) const;
	        int          operator>     (const CNsiTime &) const;
	        int          operator>=    (const CNsiTime &) const;
	        int          operator==    (const CNsiTime &) const;
	        int          operator<=    (const CNsiTime &) const;
	        int          operator<     (const CNsiTime &) const;
	        int          operator!=    (const CNsiTime &) const;
private:
	ushort timeprec;
	double seconds;
	short  mod;
	CNsiDT timezone;
};

//////////////////////////////////////////////////////////////////////////
// CNsiTimeStamp
class CNsiTimeStamp: public CNsiDatetime {
	friend class CNsiDate;
	friend class CNsiTime;
	friend class CNsiTempTable;
public:
	                    CNsiTimeStamp ();
	                    CNsiTimeStamp (uint);
	                    CNsiTimeStamp (const CNsiDT &);
	                    CNsiTimeStamp (uint, const CNsiDT &);
	                    CNsiTimeStamp (const CNsiTimeStamp &);
	virtual                ~CNsiTimeStamp (void);
	virtual void         setNull         (void);
	        void         setWithTimeZone (ENsiBoolean f = kNsiTrue );
	virtual ENsiDTType   DateTimeType  (void) const;
	virtual uint         TimeStampPrec (void) const;
	virtual uint         ReturnLength  (void) const;
	virtual ENsiBoolean  is_storable   (const CNsiData *) const;
	virtual ENsiBoolean  is_castable   (const CNsiData *) const;
	virtual ENsiBoolean  isEqualTo     (const CNsiData &) const;
	virtual ENsiBoolean  isGreaterThan (const CNsiData &) const;
	virtual ENsiBoolean  storeValue  (char *, uint);
	virtual ENsiBoolean  storeValue  (const CNsiUcStr &);
	virtual ENsiBoolean  storeValue  (const CNsiData &);
	virtual ENsiBoolean  storeValue  (const DBTIMESTAMP *);
	virtual ENsiBoolean   storeValue (real);
	virtual ENsiBoolean   storeValue (integer);
	virtual ENsiBoolean   storeValue (smallint);
	virtual ENsiBoolean   storeValue (char *, uint, uint *);
	virtual ENsiBoolean   storeValue (const NsiUcStr);
	        ENsiBoolean  set         (NSI_DTTIMESTAMP *);
	        ENsiBoolean  set         (const DBTIMESTAMP *);
	        ENsiBoolean  set         (const CNsiDate &, const CNsiTime &);
	        ENsiBoolean  set         (ushort, ushort, ushort, ushort,
	                                  ushort, double);
	        ENsiBoolean  setYear     (ushort);
	        ENsiBoolean  setMonth    (ushort);
	        ENsiBoolean  setDay      (ushort);
	        ENsiBoolean  setHour     (ushort);
	        ENsiBoolean  setMinute   (ushort);
	        ENsiBoolean  setSecond   (double);
	        ENsiBoolean  setTimeZone (const CNsiDT &);
	        ENsiBoolean  get           (NSI_DTTIMESTAMP *) const;
	        ENsiBoolean  get           (DBTIMESTAMP *)     const;
	virtual ENsiBoolean  getValue      (char *, uint)      const;
	virtual ENsiBoolean  getValue      (CNsiUcStr *)       const;
	virtual ENsiBoolean  getValue      (DBTIMESTAMP *)     const;
	virtual ENsiBoolean   getValue (real *) const;
	virtual ENsiBoolean   getValue (integer *) const;
	virtual ENsiBoolean   getValue (smallint *) const;
	virtual ENsiBoolean   getValue (char *, uint, uint *) const;
	virtual ENsiBoolean   getValue (NsiUcStr, uint) const;
	virtual ENsiBoolean   getValue (CNsiData &) const;
	virtual DBCOLUMNINFO *MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO * MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean  SQLType       (CNsiUcStr *) const;
	virtual ENsiBoolean  SQLLiteral    (CNsiUcStr *) const;
	virtual ushort       Year          (void) const;
	virtual ushort       Month         (void) const;
	virtual ushort       Day           (void) const;
	virtual ushort       Hour          (void) const;
	virtual ushort       Minute        (void) const;
	virtual double       Second        (void) const;
	  const CNsiDT      &TimeZone      (void) const;
	virtual unsigned long packSize        (void) const;
	virtual unsigned long packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackFrom      (CNsiObjPack *);
	virtual unsigned long packValueSize   (void)  const;
	virtual unsigned long packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean   unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject  *duplicate (void) const;
	        CNsiTimeStamp    &operator=     (const CNsiTimeStamp &);
	        CNsiTimeStamp    &operator=     (const CNsiDate &);
	        CNsiTimeStamp    &operator=     (const CNsiTime &);
	        CNsiTimeStamp    operator+     (const CNsiYM &) const;
	        CNsiTimeStamp    operator+     (const CNsiDT &) const;
	 friend CNsiTimeStamp NRXDBGATE_EXPORT operator+     (const CNsiYM &, CNsiTimeStamp &);
	 friend CNsiTimeStamp NRXDBGATE_EXPORT operator+     (const CNsiDT &, CNsiTimeStamp &);
	        CNsiTimeStamp    operator-     (const CNsiYM &) const;
	        CNsiTimeStamp    operator-     (const CNsiDT &) const;
	        CNsiYM    YMDiff (const CNsiTimeStamp &, const CNsiYM &) const;
	        CNsiDT    DTDiff (const CNsiTimeStamp &, const CNsiDT &) const;
	        int               operator>     (const CNsiTimeStamp &) const;
	        int               operator>=    (const CNsiTimeStamp &) const;
	        int               operator==    (const CNsiTimeStamp &) const;
	        int               operator<=    (const CNsiTimeStamp &) const;
	        int               operator<     (const CNsiTimeStamp &) const;
	        int               operator!=    (const CNsiTimeStamp &) const;
private:
	CNsiTime time;
	CNsiDate date;
};

//////////////////////////////////////////////////////////////////////////
// CNsiBlob
class CNsiBlob : public CNsiData {
public:
	typedef enum {
		kUnknown        = 0,
		kBlob,
		kIPersist,
		kNonIPersist,
		kADT
	} EBlobType;
	typedef enum {
		kUnk            = 0,
		kHex,
		kDec,
		kChr,
		kOct,
		kBin
	} EBlobFormat;
	                        CNsiBlob        ();
	                        CNsiBlob        (const CNsiBlob &);
	virtual                 ~CNsiBlob       ();
	        void            SetType         (EBlobType);
	        EBlobType       GetType         ()                      const;
	virtual ENsiDataType    Type            ()                      const;
	virtual uint            Length          ()                      const;
	virtual uint            ReturnLength    ()                      const;
	virtual ENsiBoolean     storeValue      (real);
	virtual ENsiBoolean     storeValue      (integer);
	virtual ENsiBoolean     storeValue      (smallint);
	virtual ENsiBoolean     storeValue      (char *, uint);
	virtual ENsiBoolean     storeValue      (const CNsiUcStr &);
	virtual ENsiBoolean     storeValue      (const CNsiData &);
	virtual ENsiBoolean     storeValue      (char *, uint, uint *);
	        ENsiBoolean     set             (IUnknown *);
	virtual ENsiBoolean     getValue        (real *)                const;
	virtual ENsiBoolean     getValue        (integer *)             const;
	virtual ENsiBoolean     getValue        (smallint *)            const;
	virtual ENsiBoolean     getValue        (char *, uint)          const;
	virtual ENsiBoolean     getValue        (CNsiUcStr *)           const;
	virtual ENsiBoolean     getValue        (CNsiData &)            const;
	        ENsiBoolean     get             (IUnknown **);
	virtual DBCOLUMNINFO *  MapNsiToColumnInfo  (DBCOLUMNINFO *) const;
	virtual DBPARAMINFO *   MapNsiToParamInfo   (DBPARAMINFO *) const;
	virtual ENsiBoolean     SQLType         (CNsiUcStr *)           const;
	virtual ENsiBoolean     SQLLiteral      (CNsiUcStr *)           const;
	virtual unsigned long   packSize        (void)                  const;
	virtual unsigned long   packTo          (CNsiObjPack *)         const;
	virtual ENsiBoolean     unpackFrom      (CNsiObjPack *);
	virtual unsigned long   packValueSize   ()                      const;
	virtual unsigned long   packValueTo     (CNsiObjPack *)         const;
	virtual ENsiBoolean     unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject  *   duplicate       ()                      const;
	virtual void            Clear           ();
	        HRESULT         Read            (void *, ulong, ulong *);
	        HRESULT         Write           (void *, ulong, ulong *);
	        void            SetFormat       (EBlobFormat);
	        void            SetPrintLen     (int);
	        HRESULT         ReadHead        ();
private:
	IUnknown            *   m_pIUnknown;
	EBlobType               m_eBlobType;
	EBlobFormat             m_eBlobFormat;
	int                     m_iHeadLen;
	char                    m_cBlobHead[MaxCharLength];
};

//////////////////////////////////////////////////////////////////////////
// CNsiColumn
class CNsiColumn : public CNsiObject {
public:
	                        CNsiColumn      (void);
	                        CNsiColumn      (const CNsiIdent &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiSmallInt &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiInt &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiNumeric &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiDecimal &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiFloat &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiReal &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiDouble &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiChar &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiBinary &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiDate &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiTime &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiTimeStamp &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiYM &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiDT &);
	                        CNsiColumn      (const CNsiIdent &, const CNsiIdent &);
	                        CNsiColumn      (const CNsiIdent &, CNsiData *);
	                        CNsiColumn      (const CNsiColumn &);
	                        CNsiColumn      (const DBCOLUMNINFO *);
	virtual                 ~CNsiColumn     ();
	void                    setName         (const CNsiIdent &);
	void                    setNullable     (ENsiBoolean);
	void                    setNative       (ENsiBoolean);
	void                    setCollation    (const CNsiUcStr &);
	void                    setDefault      (CNsiData *);
	void                    setDomain       (const CNsiIdent &);
	void                    setDataDsc      (CNsiData *);
	void                    setOffset       (uint);
	const CNsiIdent     &   Name            (void) const;
	ENsiBoolean             Nullable        (void) const;
	ENsiBoolean             Native          (void) const;
	const CNsiUcStr     *   Collation       (void) const;
	CNsiData            *   Default         (void) const;
	const CNsiIdent     &   Domain          (void) const;
	uint                    Offset          (void) const;
	ENsiBoolean             IsBookmark      (void) const;
	unsigned long           ColumnFlags     (void) const;
	const DBCOLUMNINFO    &    ColumnInfo        (void) const;
	CNsiData          *     getData         (void) const;
	CNsiColumn      &       operator=       (const CNsiColumn &);
	CNsiColumn      &       operator=       (CNsiData *);
	virtual unsigned long   packSize        (void) const;
	virtual unsigned long   packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean     unpackFrom      (CNsiObjPack *);
	virtual unsigned long   packValueSize   (void)  const;
	virtual unsigned long   packValueTo     (CNsiObjPack *) const;
	virtual ENsiBoolean     unpackValueFrom (CNsiObjPack *);
	virtual CNsiObject  *   duplicate       (void) const;
	virtual void            Clear           (void);
private:
	static void                setColumn        (CNsiColumn * t, const CNsiIdent & colname,
	                                             CNsiData *   datadsc);
protected:
	CNsiIdent               m_idName;
	CNsiData            *   m_pData;
	ENsiBoolean             m_fNullable;
	ENsiBoolean             m_fNative;
	CNsiData            *   m_pDefval;
	CNsiIdent               m_idDomain;
	uint                    m_uiOffset;
	unsigned long           m_dwColFlags;
	DBCOLUMNINFO            m_sColumnInfo;
};

//////////////////////////////////////////////////////////////////////////
// CNsiRow
class CNsiRow : public CNsiObject {
public:
	                        CNsiRow            (int ColNum);
	                        CNsiRow            (const CNsiRow &);
	virtual                    ~CNsiRow        ();
	int                        ColNum            (void) const;
	CNsiColumn            &    operator []        (int) const;
	int                        findCol            (const CNsiIdent &) const;
	ENsiBoolean                isDistinct        (void) const;
	virtual CNsiObject    *    duplicate        (void) const;
	virtual void            Clear            (void);
private:
	CNsiColumn            *    m_pColumns;
	int                        m_iColnum;
};

//////////////////////////////////////////////////////////////////////////
// CNsiHostBuffer
class CNsiHostBuffer: public CNsiObject {
	friend class CNsiCsr;
	friend class CNsiStm;
public:
	                    CNsiHostBuffer ();
	virtual                ~CNsiHostBuffer ();
	virtual ENsiBoolean getBind (CNsiData **) const;
protected:
	virtual ENsiBoolean setBind (CNsiData *);
protected:
	CNsiData *pData;
};

//////////////////////////////////////////////////////////////////////////
// CNsiParameter
class CNsiParameter: public CNsiHostBuffer {

friend class CNsiParser;
friend class CNsiStm;
friend class CNsiDDAParams;
friend class CNsiHostLink;
friend class CNsiInterDBCursor;
friend class CNsiEmulCursor;
friend class CNsiEmulTable;
public:
	                        CNsiParameter ();
	                        CNsiParameter (const DBPARAMINFO *);
	virtual                    ~CNsiParameter ();
protected:
	virtual ENsiBoolean        setBind     (CNsiData *);
public:
	void                    setName     (const CNsiIdent &);
	void                    setNullable (ENsiBoolean);
	void                    setDsc      (CNsiData*);
	const CNsiIdent  &        Name        (void) const;
	ENsiBoolean                isNullable  (void) const;
	CNsiData        *        Dsc         (void) const;
	virtual unsigned long    packSize        (void) const;
	virtual unsigned long    packTo          (CNsiObjPack *) const;
	virtual ENsiBoolean        unpackFrom      (CNsiObjPack *);
private:
	virtual CNsiObject *    duplicate   (void) const;
	virtual void            Clear        (void);
private:
	CNsiIdent                ucParName;
	CNsiData            *    pDataDescriptor;
	ENsiBoolean                eNul;
};


//////////////////////////////////////////////////////////////////////////
// CNsiIRow
class CNsiIRow : public CNsiObject {
public:
	                        CNsiIRow    (void);
	                        CNsiIRow    (const int);
	                        CNsiIRow    (const CNsiIRow &);
	virtual                 ~CNsiIRow   (void);
	int                     Quantity    (void) const;
	ENsiBoolean             setItem     (int, CNsiData *);
	        CNsiData    *   operator [] (const int item) const;
	virtual CNsiObject  *   duplicate (void) const;
	virtual void            Clear (void);
private:
	CNsiData **values;
	int        items;
};

/* The Database Object attribute masks */
#define        NSE_DO_CURRENT       0x01  /* The DOis the current */
#define        NSE_DO_REG           0x02  /* The DO is registered */
#define        NSE_DO_EXIST         0x04  /* The DO exists in the SQL database*/
#define        NSE_DO_CON           0x08  /* The DO belong to the connected env*/
#define        NSE_DO_UNKNOWN       0x10  /* Can't check the DO existence  */
#define        NSE_DO_WRONGKEY      0x20  /* Some registered key columns */
                                          /* doesn't exist in the real table */
#define        NSE_DO_WRONGKEYTYPE  0x40  /* Some registered key columns */
                                          /* types, precisions and scales */
                                          /* differ from the ones, taken */
                                          /* from the real table.*/

/* NULL definition */
#ifndef NULL
#define NULL 0L
#endif /*NULL*/

/* The link and link selection predefined values */
#define        LINKID_NULL     -1L
#define        LINKSELID_NULL     -1L

/* TYPEDEFS */

typedef long     LinkSelID ;     /* The link selection identifier */
typedef LONG_PTR LinkID ;         /* The link identifier */

/* The Link type codes */
typedef enum {
	kNseUnknownLinkType = 0,
	kNseEntityLink=1,  /* Ordinary Entity link */
	kNseDALink=2,         /* DA (MText Label) link */
	kNseLeaderLink=3         /* DA (Leader Label) link */
} ENseLinkType ;

/* The link attribute identification codes */
typedef enum  {
	/* Normal attributes */
	kNseAttrAll=0,     /* All link attributes */
	kNseAttrId=1,      /* link identifier (valid in the one drawing session) */
	kNseAttrType=2,     /* link type code */
	kNseAttrStatus=3,     /* link status */
	kNseAttrEnt=4,     /* entity name */
	kNseAttrName=5,     /* Link Table Name */
	kNseAttrKeyValue=6,     /* key value */
	kNseAttrDAColumns=7,     /* the DA column names list (for DA link) */
	kNseAttrDAParms=8,     /* the DA entity parameters (for DA link) */
	kNseAttrDAValues=9,     /* the known DA entity values (for DA link) */
	kNseAttrXName=10,     /* the Xref/Block name (for enclosed link) */
	kNseAttrReserved1=11,  /* internal reserved attribute */
	kNseAttrParKeyValue=12,/* partial key value */
	
	/* Extended attributes */
	kNseExtAttrTextCond=-1,/* text condition */
	kNseExtAttrEntities=-2,/* selection set name */
	kNseExtAttrDoPath=-3     /* The Database Object Path */
} ENseLinkAttr;


/* Database Object Reference definition codes */
typedef enum {
	kNseUnknownNameCode=0, /* Unknown DO name code */
	kNseEnvCode=1,         /* DataSource / Environment */
	kNseCatCode=2,         /* Catalog */
	kNseSchemaCode=3,         /* Schema */
	kNseTableCode=4,         /* Table */
	kNseLpnCode=5,         /* Link Path Name */
	kNsePathCode=6,         /* Full path code */
	kNseDOCode=7,          /* DO path only */
	kNseSQLCode=8          /* SQL object path */
} ENseDoNameCode ;

/* NSE error code in the ASI error codes sequence */
#define eNseErrEntry   (MinUserDefErrorCode+1)

/* Detects whether or not the error entry contains NSE error data */
#define isNseErr(x)   (x == eNseErrEntry ? kAsiTrue : kAsiFalse)

/* Status of Nse Path. Set and get by CNsePath::GetStatus, CNsePath::SetStatus */
#define            NSEPATH_STAT_EMPTY        0        /* void */

/* Query and table are mutual exclusive */
#define            NSEPATH_STAT_TABLE        0x01     /* Table */
#define            NSEPATH_STAT_QUERY        0x02     /* Query */


/* The NSE error description codes */
typedef enum {

	eNseEDscUnknown = 0, /* Unknown error  */

	eNseEDscInternal = 1,  /* Internal NSE error. This code hasn't be assigned*/
	           /* in the normal situation. It indicates about an */
	           /* internally detected NSE bug. See ENseErrCodes. */

	eNseEDscNse = 2,       /* Logical common error, see ENseErrCodes. */

	eNseEDscFile = 3,       /* File I/O error, see ASI error diagnostic */

	eNseEDscAsi = 4,       /* ASI error, see ASI error diagnostic */

	eNseEDscDb = 5,       /* ASI group error qualificator, see ENseDbErrCodes */

	eNseEDscDwg = 6,       /* Drawing error, see ENseDwgErrCodes for error codes */

	eNseEDscDlg = 7,       /* Dialogue errors, see ENseDlgErrCodes for error codes */

	eNseEDscApi = 8,       /* API errors, see ENseApiErrCodes for error codes */

	eNseEDscLink = 9       /* Internal error with the Link Information,*/
	           /* see ENseLinkErrCodes */
} ENseErrDsc ;

/* The common NSE error codes */
typedef enum {
	eNseErrUnknown=0,       /* Unknown NSE error */
	eNseErrInternal=1,       /* Internal NSE error, inconsistent call of the*/
	           /* internal NSE functions.*/
	eNseErrMemory=2,       /* No memory*/
	eNseErrInfo=3,       /* Information message entry*/
	eNseErrMaxQty=4,       /* The maximum quantity of the errors is exceded*/


	eNseErrNoReg=10,          /* No one DO is registered*/
	eNseErrDoReg=11,          /* The DO isn't registered*/
	eNseErrEnvNotConnected=12,     /* Environment isn't connected*/
	eNseErrNoLpn=13,          /* LPN isn't set*/
	eNseErrNoEnvName=14,      /* Environment name isn't specified*/
	eNseErrNoCatName=15,      /* Catalog name isn't specified*/
	eNseErrNoSchemaName=16,   /* Schema name isn't specified*/
	eNseErrNoTableName=17,    /* Table name isn't specified*/
	eNseErrLpnExist=18,       /* Link Path Name already exists*/
	eNseErrWrongKey=19,       /* Some of the key columns doesn't exist in table*/
	eNseErrWrongKeyType=20,   /* Wrong key column type is detected:*/
	              /* table structure was changed or BIT, BITVAR*/
	              /* column types are specified*/
	eNseErrNoSelEnts=21,      /* No one entity is selected*/
	eNseErrNoSelLinks=22,     /* No one links exist in the specified entities*/
	eNseErrNoSelDALinks=23,   /* No one links exist in the specified entities*/
	eNseErrNoDoLinks=24,      /* No one links to the DO is specified*/
	eNseErrDAUpd=25,           /* Some of the DAs aren't updatable */

	eNseErrWrongDoName=26,  /* Invalid DO Name */
	eNseErrWrongResbuf=27,  /* Invalid resbuf*/
	eNseErrBadR12DOR=28,    /* Can't find the R13 terms for R12 DOR */
	eNseErrWrongLPN=29,     /* Invalid LPN */
	eNseErrWrongPath=30,    /* Invalid DO path */
	eNseErrLinkUpd=31,        /* Some of the links aren't updatable */
	eNseErrLinkSynch=32,    /* The links(s) can't be synchronized */
	eNseErrLPSynch=33,        /* The Link Path(s) can't be synchronized */
	eNseErrCharSet=34        /* Can't find character set */

} ENseErrCodes ;

/* The File I/O related error codes */
typedef enum {
	eNseFileErrUnknown=400,   /* Unknown error*/
	eNseFileNotFound,          /* File not found*/
	eNseFileErrOpen,          /* Can't open file*/
	eNseFileErrRead,          /* Read error*/
	eNseFileErrWrite          /* Write error*/
} ENseFileErrCodes;


/* ASI group error codes*/
typedef enum {
	eNseDbErrUnknown=500,    /* Unknown NSE error*/
	eNseDbErrSyntax=501,     /* SQL syntax error*/
	eNseDbErrPrepare=502,    /* Can't prepare SQL statement*/
	eNseDbErrExecute=503,    /* Can't execute the statement*/
	eNseDbErrOpenCsr=504,    /* Can't open the cursor*/
	eNseDbErrEntry=505,      /* Wrong entry format in NSE_R12 section of*/
	             /* ASI.INI file*/
	eNseDbErrIni=506,         /* Can't get ASI.INI file*/
	eNseDbErrFetch=507         /* Can't fetch */
} ENseDbErrCodes ;

/* The AutoCAD drawing related codes*/
typedef enum {
	eNseDwgErrUnknown         = 700,
	eNseDwgErrOpenReadEntity     = 701,
/*
	Error openning entity for read. Object is to be opened for read as soon as
	any entity information, such as name of the layer, name of the parent block,
	XData ant etc. is requested.
*/
	eNseDwgErrTranslateHandle     = 702,
/* Error translation entity handle, stored in the R12 Link, to the R13
	NcDbObjectId
*/
	eNseDwgErrAdsNameId         = 703,
/*
	Can not convert NcDbObjectId to ads_name
*/
	eNseDwgErrXEDAppidNotFound     = 704,
/*
	XData is corrupt - APPID group not found
*/
	eNseDwgErrXEDCorrupt      = 705,
/*
	R13 XData is corrupt
*/
	eNseDwgErrUpdateXED         = 706,
/*
	Can not write/update XData.
*/
	eNseDwgErrParcingLink     = 707,
/*
	Can not parce NSE Link XData
*/
	eNseDwgErrParcingLPN      = 708,
/*
	Can not parce NSE LPN XData
*/
	eNseDwgErrOpenWriteEntity     = 709,
/*
	Can not open entity for write
*/
	eNseDwgErrConvertingLink     = 710,
/*
	Error converting link to the result buffer
*/
	eNseDwgErrOpenBlockTable     = 711,
/*
	Can not open block table
*/
	eNseDwgErrAppendBlockTable     = 712,
/*
	Can not add DA block definition to the block table
*/
	eNseDwgErrAppendObjBlockTable = 713,
/*
	Can not append DA to the MODEL_SPACE or PAPER_SPACE sections
*/
	eNseDwgErrOpenBlock         = 714,
/*
	Can not open Block Table Record
*/
	eNseDwgErrDelSelSet         = 715,
/*
	Error releasing selection set
*/
	eNseDwgErrFilterSelSet     = 716,
/*
	Error scanning block hierarchy
*/
	eNseDwgErrCreateLPNTable     = 717,
/*
	Can not create LPN dictionary in the Drawing Database
*/
	eNseDwgErrFindLPNTable     = 718,
/*
	Can not find LPN dictionary in the Drawing Database
*/
	eNseDwgErrFindAppid         = 719,
/*
	Can not find NSE APPID
*/
	eNseDwgErrOpenLPNDict     = 720,
/*
	Can not open LPN Dictionary
*/
	eNseDwgErrAddEntry         = 721,
/*
	Can not add entry to the LPN dictionary
*/
	eNseDwgErrRemoveEntry     = 722,
/*
    Can not remove entry from the LPN dictionary
*/
	eNseDwgErrUnexpSymb         = 723,
/*
    Unexpected symbol in NSE XData found. XData is corrupted.
*/
	eNseDwgErrDwgInit         = 724,
/*
	Can not initialize Drawing Subsystem
*/
	eNseDwgErrBlockIterator     = 725,
/*
	Can not open Block Table Record iterator
*/
	eNseDwgErrTransOpen         = 726,
/*
	Previous drawing transaction is not closed
*/
	eNseDwgErrTransClose      = 727,
/*
	Current Drawing transaction has not been opened
*/
	eNseDwgErrGrips         = 728,
/*
	Can not store selection set in the AutoCAD via ads_sssetfirst() function.
	The error can accure in NSEROWS and NSESELECT commands
*/
	eNseDwgErrFindBlock         = 729,
/*
	Block not found in the Block Table
*/
	eNseDwgErrOpenRegapTable     = 730,
/*
	Can not open AutoCAD REGAPP table. This operation is to be fulfilled as
	soon as NSE information should be stored in the drawing for the first
	time in the NSE session.
*/
	eNseDwgErrRegisterAppid     = 731,
/*
	Can not register NSE APPID. APPID should be registered before NSE
	information should be stored in the drawing for the first time in the
	NSE session.
*/
	eNseDwgErrInitObject      = 732,
/*
	Can not initialize CNseDEntity object
*/
	eNseDwgErrAddLink         = 733,
/*
	Can not write link in the drawing
*/
	eNseDwgErrAddLPN         = 734,
/*
	Can not write LPN in the drawing
*/
	eNseDwgErrDelLink         = 735,
/*
	Can not delete link from the drawing
*/
	eNseDwgErrDelLPN         = 736,
/*
	Can not delet LPN from the drawing
*/
	eNseDwgErrUpdLink         = 737,
/*
	Can not update link in the drawing
*/
	eNseDwgErrUpdLPN         = 738,
/*
	Can not update LPN in the drawing
*/
	eNseDwgErrDeleteObj         = 739,
/*
	Can not delete DA object from the drawing
*/
	eNseDwgErrCorruptDA         = 740,
/*
	Can not read DA column values from DA block attributes
*/
	eNseDwgErrErasedObj         = 741,
/*
	Can not open object    - it has been erased
*/
	eNseDwgErrOpenNotify      = 742,
/*
	Object can not be updated - it is opened for notify
*/
	eNseDwgErrOpenUndo         = 743,
/*
	Object can not be updated - it is opened for undo
*/
	eNseDwgErrOpenWrite         = 744,
/*
	Object can not be updated - it is opened for write
*/
	eNseDwgErrOpenRead         = 744,
/*
	Object can not be updated - it is opened for read
	*/
	eNseDwgErrOpenXref         = 745,
/*
	Object can not be updated - it is object from XRef
*/
	eNseDwgErrOpenLocked      = 746,
/*
	Object can not be updated - it is on the locked layer
*/
	eNseDwgErrDelR12DOMesh     = 747,
/*
	Can not delete R12 DO Mesh
*/
	eNseDwgErrDelR12LinkMesh     = 748,
/*
	Can not delete R12 Link Mesh
*/
	eNseDwgErrReadLTypeTable     = 749,
/*
	Can not read line style table
*/
	eNseDwgErrReadLayerTable     = 750,
/*
	Can not read layer table
*/
	eNseDwgErrReadStyleTable        = 751,
/*
	Can not read style table
*/
	eNseDwgErrOpenLPNEntry     = 752,
/*
	Can not open LPN dictionary entry
*/
	eNseDwgErrAppendBlkBlockHierarchy= 753,
/*
    Can not add block to NSE block hierarchy
*/
    eNseDwgErrAppendRefBlockHierarchy= 754,
/*
    Can not add block reference to NSE block hierarchy
*/
    eNseDwgErrFindBlkBlockHierarchy= 755,
/*
    Can not find block in NSE block hierarchy
*/
    eNseDwgErrDelBlkBlockHierarchy   = 756,
/*
    Can not delete block from NSE block hierarchy
*/
    eNseDwgErrInvR12Mesh      = 757,
/*
    Invalid R12 Polimesh found.
*/
    eNseDwgErrEOR         = 758,
/*
    Unexpected End of NSE XData found
*/
    eNseDwgErrBraceExpected     = 758,
/*
    Brace is mismatched in NSE XData
*/
    eNseDwgErrBlockName         = 759,
/*
    Can not get name of the block  from NcDbBlockTableRecord
*/
    eNseDwgErrOpenLayer         = 760
/*
    Can not open layer table record for update
*/
} ENseDwgErrCodes ;

/* The AutoCAD Dialog related codes */
typedef enum {
	eNseDlgErrUnknown=800,    /* Unknown NSE error */
	eNseDlgWrongObj,
	eNseDlgNoDsc,
	eNseDlgMakeKey,
	eNseDlgReadStyleTable
} ENseDlgErrCodes ;

/* NSE API related error codes */
typedef enum {
	eNseApiErrUnknown=900,     /* Unknown NSE error */
	eNseApiErrWrongData=901,       /* Input data in the wrong format */
	eNseApiErrInitObj=902,       /* The API class isn't initialized */
	eNseApiErrInitApp=903,       /* Communication with NSE isn't extablished */
	eNseApiErrWrongAttr=904,       /* Wrong link attribute code */
	eNseApiErrXmx=905,           /* Can't load XMX file */
	eNseApiErrWrongFunc=906,       /* Wrong call of API func. */
	eNseApiErrEmptyList=907,       /* Can't find DO list */
	eNseApiErrMissingTable=908,    /* Missing table path in filter */
	eNseApiErrLinkNotFound=909,    /* Can't find link by link ID */
	eNseApiErrLinkMake=910,       /* Error in link creation */
	eNseApiErrLinkUpdate=911,       /* Error in link updating */
	eNseApiErrLinkDelete=912,       /* Error in link deleting */
	eNseApiErrMissingLinkType=913, /* Missing link type */
	eNseApiErrWrongLinkType=914,   /* Wrong link type value */
	eNseApiErrMissingLinkID=915,   /* Missing link ID */
	eNseApiErrWrongLinkID=916,       /* Wrong link ID value */
	eNseApiErrMissingEntName=917,  /* Missing entity name */
	eNseApiErrWrongEntName=918,    /* Wrong entity name value */
	eNseApiErrMissingLpn=919,       /* Missing LPN */
	eNseApiErrWrongLpn=920,       /* Invalid LPN */
	eNseApiErrMissingKeyVal=921,   /* Missing Key value list */
	eNseApiErrWrongKeyVal=922,       /* Invalid Key valie list */
	eNseApiErrSelNotFound=923,       /* Can't find link selection by ID */
	eNseApiErrSelAddLink=924,       /* Can't add link to the link sel. */
	eNseApiErrSelDelLink=925,       /* Can't delete link from the link sel. */
	eNseApiErrSelFree=926,       /* Can't free the link sel. */
	eNseApiErrSelEmpty=927,       /* Empty link sel. */
	eNseApiErrMissingKeyNames=928, /* Missing Key names list */
	eNseApiErrWrongKeyNames=929,   /* Invalid Key names list */
	eNseApiErrKeyNameNotFound=930, /* Key column name is not found in the table */
	eNseApiErrDupKeyNames=931,       /* Duplicated Key names */
	eNseApiErrLpnNew=932,       /* Error in creation of new LPN */
	eNseApiErrLpnDel=933,       /* Error in deleting of LPN */
	eNseApiErrLpnNotFound=934,       /* LPN is not exist */
	eNseApiErrLpnRen=935,       /* Error in renaming of LPN */
	eNseApiErrWrongEntSel=936,       /* Invalid entity sel. set name */
	eNseApiErrWrongBlock=937,       /* Invalid Xref/Block name */
	eNseApiErrWrongWhere=938,       /* Invalid WHERE condition */
	eNseApiErrSelUnite=939,       /* Error in union */
	eNseApiErrSelSubtract=940,       /* Error in subtract */
	eNseApiErrSelIntersect=941,    /* Error in intersect */
	eNseApiErrSelErase=942,       /* Can't erase link sel. with links */
	eNseApiErrSelEraseLinks=943,   /* Can't erase some links */
	eNseApiErrCurrent=944,       /* Can't set current path */
	eNseApiErrWrongRowVal=945,       /* Invalid row values */
	eNseApiErrDuplicatedLink=946,  /* Attempt of duplicated link creation */
	eNseApiErrMissingDANames=947,  /* Missing DA names list */
	eNseApiErrWrongDANames=948,    /* Invalid DA names list */
	eNseApiErrWrongDAVal=949,       /* Invalid DA values list */
	eNseApiErrMissingDAPar=950,    /* Missing DA parameters */
	eNseApiErrWrongDAPar=951,       /* Invalid DA parameters */
	eNseApiErrMakeDA=952       /* Error in make DA */
} ENseApiErrCodes ;

/* Internal Link Information related codes*/
typedef enum {
eNseLinkErrUnknown        = 1000, /* Unknown NSE error*/
eNseLinkErrWrongRegPath     = 1001,
/*
    a) Invalid path to register table.
    b) LPN syntax error. LPN with prefix can't
       be registered.
    c) LPN syntax error. Wrong Xref name syntax.
*/

eNseLinkErrWrongRegDsc        = 1002,
/*
    a) Wrong column desriptor.                registration
    b) Invalid list of the key columns to register.
*/

eNseLinkErrWrongPath12        = 1003,
/*
    Invalid path to Database Object Release 12 to    registration
    register.
*/

eNseLinkErrWrongTypeDsc     = 1005,
/*
    a) Unknown column descriptor data type.        registration
    b) Length of the key value can't be defined.        access to key value
*/

eNseLinkErrWrongLsAddOp     = 1007,
/*
    Wrong Link Selection Identifier            Link Selection addition
*/

eNseLinkErrWrongLsSubOp     = 1008,
/*
    Wrong Link Selection Identifier            Link Selection subraction
*/

eNseLinkErrWrongLsId        = 1009,
/*
    Wrong Link Selection Identifier            Access to Link Selection
*/

eNseLinkErrWrongEntityId    = 1010,
/*
    Undefined drawing object to link            DA Link creation
*/

eNseLinkErrUndefDa        = 1011,
/*
    Undefined DA list                    DA link creation
*/

eNseLinkErrNoMemForLs        = 1012,
/*
    Out of memory                    Link Selection manipulation
*/

eNseLinkErrWrongPtrToLnk    = 1013,
/*
    Wrong Link Identifier                Access to Link
*/

eNseLinkErrNoLinkInLMem     = 1014,
/*
    Link was lost                    Access to Link
*/

eNseLinkErrNoEntityForLink    = 1016,
/*
    Invalid Link in the memory                Access to Link
*/

eNseLinkErrWrongPtrToLs     = 1017,
/*
    Wrong Link Selection Identifier            Access to Link Selection
*/

eNseLinkErrNoLsInLMem        = 1018,
/*
    Link Selection was lost                Access to Link Selection
*/

eNseLinkErrMLsNotValid        = 1019,
/*
    Invalid Link Selection                Access to Link Selection
*/

eNseLinkErrMLinkNotValid    = 1020,
/*
    Invalid Link in the memory                NSE Transaction
*/

eNseLinkErrTabNoChanges     = 1021,
/*
    Link Information assosiated with            Erase LPN
    LPN can't be changed
*/

eNseLinkErrRnmWrongOldLPN    = 1022,
/*
    Old LPN is invalid                    LPN Renaming
*/

eNseLinkErrRnmWrongNewLPN    = 1023,
/*
    New LPN is invalid                    LPN Renaming
*/

eNseLinkErrRnmNoUpd        = 1024,
/*
    Link Information associated with LPN        LPN Renaming
    isn't updatable
*/

eNseLinkErrLLinkNotValid    = 1025,
/*
    CNseLLink object is not valid. Object        Link Manipulations
    had not been initialized
*/

eNseLinkErrLLinkNotUpdate    = 1026,
/*
    Link can't be modified. Drawing object              Link modification
    isn't updatable
*/

eNseLinkErrLLinkNoMakeDup    = 1027,
/*
    Can't create duplicated link                        Link creation
*/

eNseLinkErrLLinkNoMakeKey    = 1029,
/*
      Can't create link. Wrong keys                     Link creation
*/

eNseLinkErrLLinkNoMakeStore    = 1030,
/*
      Can't store Link into drawing                     Link creation
*/

eNseLinkErrLLinkWrongId     = 1031,
/*
      Can't intialize CNseLLink object.                 Access to Link
      Wrong Link Identifier
*/

eNseLinkErrLLinkWrongType    = 1032,
/*
    a) Can't intialize CNseLLink object.                Access to Link
       Wrong Link type
    b) Can't update DA. Link isn't DA link              DA Link updating
*/

eNseLinkErrLLinkManyLinks    = 1033,
/*
    Can't intialize CNseLLink object by                 CNseLLink object initialization
    drawing object. Drawing object contains
    several links.
*/

eNseLinkErrLLinkNoMake        = 1034,
/*
    a) Can't make link. Duplicate link.                 Link creation
    b) Can't store Link in the memory.
    c) Can't make link. Wrong keys.
*/

eNseLinkErrLLinkNoDel        = 1035,
/*
    a) Can't delete link. Link is not valid             Link deleting
    b) Can't delete link. Link is not updatable
    c) Can't delete Xdata assocoated with link
*/

eNseLinkErrLLinkNoUpd        = 1036,
/*
    a) Can't update link. Link Information              Link modification
       was not changed.
    b) Can't update link. Link isn't valid
    c) Can't update link. Drawing object is
       not updatable.
*/

eNseLinkErrLLinkNoDATab     = 1037,
/*
      Wrong DA Link modification.            DA link modification.
      Table name can't be changed for DA link
*/

eNseLinkErrLLinkNoDAEnt     = 1038,
/*
      Wrong  DA Link modification            DA link modification
      Drawing object can't be changed for DA link
*/

eNseLinkErrLLinkWrongEnt    = 1039,
/*
      CNseLLink obejct was not initialized correctly    Access to link
*/

eNseLinkErrLLinkWrongDA     = 1040,
/*
      Wrong DA columns                    DA Link creation
*/

eNseLinkErrLLinkAbsent        = 1041,
/*
      Can't find out Link by Link Identifier            Access to Link
*/

eNseLinkErrLSWrongFilter    = 1042,
/*
      Wrong filter                    Link Selection filtering
*/

eNseLinkErrInLMem        = 1045,
/*
      Can't clear Link Selection.                       Access to Link Selection
*/

eNseLinkErrKeyNotValid        = 1046,
/*
      Key isn't valid                                   Access to key values
*/

eNseLinkErrWrongKeyVal        = 1047,
/*
      Wrong key value                    Row registration
*/

eNseLinkErrCantStoreKeyVal    = 1048,
/*
      Key value can't be stored. It is possible
      if NSE have not enough memory or key column
      descriptor is not correct.
*/

eNseLinkErrWrongDsc        = 1049,
/*
      Can't store key value. Descriptor is not          Row registration
      correct
*/

eNseLinkErrWrongKeyInit     = 1050,
/*
      Can't initialize CNseLKey object.                 Row registration
      LPN is not valid.
*/

eNseLinkErrValid        = 1051,
/*
      Link Subsystem is not valid. Internal error.
*/

eNseLinkErrStart        = 1052,
/*
      Link subsystem can't begin NSE transaction.
      Internal error.
*/

eNseLinkErrLMemWrongId        = 1053,
/*
      Wrong Link Identifier                Access to link
*/

eNseLinkErrLMemInternal     = 1054,
/*
      Link Subsystem internal error            Access to link
*/

eNseLinkErrLMemRBack        = 1055,
/*
      Can't restore link                                Rollback of the NSE Transaction
*/

eNseLinkErrWrongTransForUpd    = 1056,
/*
      Can't update link. Transaction wasn't opend.      Updating of the link
*/

eNseLinkErrEnameEIdConvert    = 1059,
/*
      Can't convert ads_name to NcDbEntityId.           Link making
*/

eNseLinkErrEntNoUpd        = 1060,
/*
      Entity is not updatable. Link can't be created.   Link making
*/

eNseLinkErrContainerItem    = 1061,
/*
      Can't intialize Link Selection for container.     NSELINKS command
*/

eNseLinkErrNtfEraseUnlinkedEntity = 1062,
/*
    Link Subsystem has got notification to delete     Processing of the notifications
    links, but specified object has no links.          from linked drawing object
*/

eNseLinkErrNtfCopyUnlinkedEntity = 1063,
/*
    Link Subsystem has got notification to copy       Processing of the notifications
    links, but specified object has no links.          from linked drawing object
*/

eNseLinkErrNtfCanTProcess    = 1064,
/*
      Link Subsysten can't process the notification.    Processing of the notifications
*/

eNseLinkErrNtfUnXED        = 1065,
/*
      Can't restore link. Wrong Xdata.                  Processing of the notifications
                            from linked drawing objects.
                            Undo command
*/

eNseLinkErrNtfUnKey        = 1066,
/*
      Can't restore link. Row can't be registered.      Processing of the notifications
                            from linked drawing objects.
                            Undo command
*/

eNseLinkErrNtfUnDA        = 1067,
/*
    Can't restore link. Can't store DA columns          Processing of the notifications
                            from linked drawing objects.
                            Undo command
*/

eNseLinkErrNtfUnErase        = 1069,
/*
    Can't restore link. Link isn't found out in the     Processing of the notifications
    Link memory                     from linked drawing objects.
                            Undo command
*/

eNseLinkErrInternal        = 1070,
/*
    Internal error of the Link Subsystem.
*/

eNseLinkErrWrongRecordLpnPos    = 1071,
/*
    Link subsystem can't set the position of the Lpn  Reading link information
    in the Xdata                      from drawing
*/

eNseLinkErrWrongLpnSyntax    = 1073,
/*
    LPN syntax error.                      Reading link information from
                              drawing
*/

eNseLinkErrCantRegLink        = 1076,
/*
    Can't store link. Link Path Name isn't            Reading link information from
    registered yet.                      drawing. Undo command
*/

eNseLinkErrCantInitKey        = 1077,
/*
    Can't initilize key row to register.              Reading link information from
                              drawing. Undo command
*/

eNseLinkErrWrongLinkNumber    = 1078,
/*
    Wrong link structure in the drawing object.       Reading link information from
                              drawing. Undo command
*/

eNseLinkErrDuplicateReg     = 1079,
/*
    Duplicate registration.                  LPN registration
*/

eNseLinkErrTrRbackUndel     = 1081,
/*
    Can't restore the deleted link.                   Rollback NSE Transaction
*/

eNseLinkErrTrRbackTable     = 1082,
/*
    Link subsystem can't execute rollback NSE         Rollback NSE Transaction
    Transaction for link table.
*/

eNseLinkErrTrRback        = 1083,
/*
    Link subsystem can't execute rollback NSE         Rollback NSE Transaction
    Transaction, because transaction wasn't opened.
*/

eNseLinkErrTrCommit        = 1084,
/*
    Link subsystem can't execute commit NSE
    Transaction, because transaction wasn't
    opened.
*/

eNseLinkErrTrCommitTable    = 1085,
/*
    Link subsystem can't execute commit for
    Link Table.
*/

eNseLinkErrTrCommitDelLink    = 1086,
/*
    Link subsystem can't delete link data from        Commit NSE Transaction
    Xdata of the drawing object.
*/

eNseLinkErrTrCommitAddLink    = 1087,
/*
    Link subsystem can't add new link Xdata of        Commit NSE Transaction
    drawing object.
*/

eNseLinkErrLnkDestroed        = 1088,
/*
    Linked row is deleted from link memory before     Commands: Open, New Rx/Unload
    accosiated link have been erased              Quit
*/

eNseLinkErrDupUpdLnk        = 1090,
/*
    Can't update link. Duplicated links.              Link updating.
*/

eNseLinkErrRubbNoMem        = 1091,
/*
    Can't execute rubbish collector algorithm.        Commit NSE Transaction
    Out of memory
*/

eNseLinkErrCommitNoMem        = 1092,
/*
    Can't execute commit NSE Transaction.             Commit NSE Transaction
*/

eNseLinkErrCommit        = 1093,
/*
    Link Sybsystem can't commit NSE Transaction       Commit NSE Transaction
*/

eNseLinkErrTrExportLpn        = 1094,
/*
    Can't store the export LPN to external database   Wblock command
*/

eNseLinkErrLostLink        = 1095,
/*
    Can't store the link from Xdata
*/

eNseLinkErrLinkToLeaderLink        = 1096
/*
    Can't create link because the entity is leader link component
*/

} ENseLinkErrCodes ;

/* NSE Diagnostic Parameters*/
typedef enum {
	kNseDiagErrDsc    =     MinUserDefDiagParam+1, /* NSE error description - Int*/
	kNseDiagErrCode   =     MinUserDefDiagParam+2, /* Error Code             - Int*/
	kNseDiagErrMsg    =     MinUserDefDiagParam+3, /* NSE Error Message - Char*/
	kNseDiagStatement =  MinUserDefDiagParam+4, /* SQL statement     - Char*/
	kNseDiagSynErrPos =  MinUserDefDiagParam+5, /* Syntax error position - Int*/
	kNseDiagLPName    =     MinUserDefDiagParam+6, /* Link Path Name     - Char*/
	kNseDiagEnvName   =     MinUserDefDiagParam+7, /* Environment name     - Char*/
	kNseDiagEntHandle =  MinUserDefDiagParam+8, /* Entity handle     - Char*/
	kNseDiagBlockName =  MinUserDefDiagParam+9, /* Block name         - Char*/
	kNseDiagLayerName =  MinUserDefDiagParam+10,/* Layer name        - Char*/
	kNseDiagLabelName =  MinUserDefDiagParam+11,/* Label name        - Char*/
	kNseDiagAcApDoc   =  MinUserDefDiagParam+12,/* AcApDocument Address  - Int*/
	kNseDiagGroupName =  MinUserDefDiagParam+13,/* LinkTemplateGroup - Char*/
	kNseDiagQueryName =  MinUserDefDiagParam+14,/* QueryName         - Char*/
	kNseDiagTableName =  MinUserDefDiagParam+15 /* TableName         - Char*/
} ENseDiagParms ;

/* API class codes*/
typedef enum {
	kNseApiUnknownId,/* Unknown API class*/
	kNseApiAppl,     /* for class CNseAppl and descriptor NSE_APPLDSC*/
	kNseApiLinkPath, /* for class CNseLinkPath and descriptor NSE_LPDSC*/
	kNseApiLink,     /* for class CNseLink and descriptor NSE_LINKDSC*/
	kNseApiLinkSel     /* for class CNseLinkSel and descriptor NSE_LSELDSC*/
} ENseApiClassId ;


// Data source translation codes
//
enum DatasourceTranslationCode {
	kTranslateFromR14toR15 = 0,
	kTranslateFromR15toR14
};

#define WORKINGDWG()  NULL

//////////////////////////////////////////////////////////////////////////
// CNseApiObj
class CNseApiObj {
public:
	                     CNseApiObj(CNseApiObj *pObj) ;
	                     CNseApiObj(CNseApiObj &Obj) ;
	virtual                ~CNseApiObj() ;
	virtual ENsiBoolean    init() ;
	virtual ENseApiClassId isA() const = 0 ;
	virtual CNseApiObj    *clone() const = 0 ;
	virtual ENsiBoolean    copyFrom(const CNseApiObj *pObj) ;
	virtual CNseApiObj&    operator=(const CNseApiObj &Obj) ;
	virtual int            operator==(const CNseApiObj *pObj) const = 0 ;
	virtual int            operator==(const CNseApiObj &Obj) const = 0 ;
	virtual ENsiBoolean    isInit() const ;
	const NCHAR            *version() const ;
	const CNsiException   *errGet() const ;
	int                    errQty() const ;
	ENseErrDsc             errDsc(int ErrNum) const ;
	int                    errCode(int ErrNum) const ;
	ENsiBoolean            errMsg(int ErrNum,
                                  NCHAR *pBuf,
                                  int BufLen) const;
	ENsiBoolean            errClear() ;
	void                   appThrow() const ;
	const NCHAR            *errDiagParNameCode(int ParNum,
	                                           int *pParCode,
	                                           int *pIsStr) const ;
	ENsiBoolean            errDiagPar(int ErrNum,
	                                  int ParCode,
	                                  int *pIntValue) const ;
	ENsiBoolean            errDiagPar(int ErrNum,
	                                  int ParCode,
	                                  NCHAR *pStrValue,
	                                  int BufLen) const ;
	ENsiBoolean errInitNsi(CNsiException *pErr) ;
	ENsiBoolean errInitNsi(CNsiSQLObject *pSQLObj) ;
	ENsiBoolean errInitNsi(CNsiSQLObject &sqlObj) ;
	friend class CNseApiErr ;
	friend class CNseAppl ;
protected:
	struct resbuf         *getLast(const struct resbuf *bufptr) const ;
	struct resbuf         *allocAttr(ENseLinkAttr attr, const NCHAR *pStr=NULL) const ;
	struct resbuf         *copyBuf(const struct resbuf *bufptr,
                                   const struct resbuf *pBorder=NULL) const ;
	struct resbuf         *nextAttr(const struct resbuf *bufptr) const ;
	struct resbuf         *getAttrType(const struct resbuf *bufptr,
	                                   ENseLinkAttr lattr) const ;
	const struct resbuf   *getAttrPtr(const struct resbuf *bufptr,
	                                  ENseLinkAttr lattr) const ;
	ENsiBoolean            setAttrPtr(struct resbuf *bufptr,
	                                  ENseLinkAttr LinkAttr,
	                                  struct resbuf *pAttrValue) const ;
	struct resbuf         *delAttrPtr(struct resbuf *bufptr,
	                                  struct resbuf *pAttr) const ;
	ENsiBoolean            parseLisp(struct resbuf *bufptr) ;
	CNseAppl              *getAppl() const ;
	void                   freeStr(struct resbuf *pBuf) const ;
	ENsiBoolean            isDiffChar() const ;
	void                  *mpErr ;
};

//////////////////////////////////////////////////////////////////////////
// CNseAppl
class CNseAppl : public CNseApiObj {
public:
	                     CNseAppl(CNseApiObj *pObj=NULL) ;
	                     CNseAppl(CNseApiObj &Obj) ;
	virtual                ~CNseAppl() ;
	virtual ENsiBoolean    init() ;
	virtual ENseApiClassId isA() const ;
	virtual CNseApiObj    *clone() const ;
	virtual ENsiBoolean    copyFrom(const CNseApiObj *pObj) ;
	virtual CNseApiObj&    operator=(const CNseApiObj &Obj) ;
	virtual int            operator==(const CNseApiObj *pObj) const ;
	virtual int            operator==(const CNseApiObj &Obj) const ;
	virtual ENsiBoolean    isInit() const ;
	void                   term() ;
	LPCTSTR                 getNcadDsPath();
	ENsiBoolean            getNseErr() ;
	ENsiBoolean            clearNseErr();
	CNsiSession*connectNse(CNsiAppl *pAppl,
                           const TCHAR *pEnvName,
                           const NCHAR *pUserName=NULL,
                           const NCHAR *pPassWord=NULL,
                           ENsiBoolean fPrompt = kNsiFalse) ;
	ENsiBoolean            isIndexExist(NcDbDatabase *pDwg=NULL);
	ENsiBoolean            isIndexUpToDate(NcDbDatabase *pDwg=WORKINGDWG());
	ENsiBoolean            createIndex(NcDbDatabase *pDwg=WORKINGDWG());
	ENsiBoolean            removeIndex(NcDbDatabase *pDwg=WORKINGDWG());
	int                     setIndexSaveMode (int mode);
	ENsiBoolean            openDwg(NcDbDatabase *pDwg=WORKINGDWG()) ;
	ENsiBoolean            openLazyDwg(NcDbDatabase *pDwg=WORKINGDWG()) ;
	ENsiBoolean            isDwgOpened(NcDbDatabase *pDwg=WORKINGDWG()) ;
	ENsiBoolean            isDwgLazyOpened(NcDbDatabase *pDwg=WORKINGDWG()) ;
	ENsiBoolean            closeDwg(NcDbDatabase *pDwg=WORKINGDWG()) ;
	ENsiBoolean            swapEntIds(NcDbObjectId objectId,
	                                  NcDbObjectId otherId,
	                                  NcDbDatabase *pDwg=WORKINGDWG());
	ENsiBoolean            swapBTRIds(NcDbObjectId blockId,
	                                  NcDbObjectId otherId,
	                                  NcDbDatabase *pDwg=WORKINGDWG());
	ENsiBoolean            loadLinks(NcDbEntity *pObj);
	ENsiBoolean            loadLinks(NcDbObjectId objId);
	ENsiBoolean            translateDataSource(DatasourceTranslationCode xCode,
	                                           unsigned int buflen,
	                                           const NCHAR * szFromEnv,
	                                           const NCHAR * szFromCat,
	                                           const NCHAR * szFromSchema,
	                                           const NCHAR * szFromTable,
	                                           const NCHAR * szFromLpn,
	                                           NCHAR * szToEnv,
	                                           NCHAR * szToCat,
	                                           NCHAR * szToSchema,
	                                           NCHAR * szToTable,
	                                           NCHAR * szToLpn);
	ENsiBoolean           beginNseTransaction();
	ENsiBoolean           commitNseTransaction();
	ENsiBoolean           abortNseTransaction();
	typedef enum {
		  kTransAutomatic = 0,
		  kTransUserManaged,
	} ETransactionMode;
	void                  setNseTransactionMode( ETransactionMode eMode );
	ETransactionMode      getNseTransactionMode();
protected:
	struct resbuf *        nseiCallNse(int funCode,
                                       struct resbuf* pParms,
                                       void *pErr,
                                       void *pNcDbDatabase=NULL,
                                       ENsiBoolean needFullOpen=kNsiFalse)  ;
	struct resbuf *        nse_invoke(int funCode,
	                                  struct resbuf* pParms,
	                                  void *pErr,
	                                  void *pNse)  ;
	struct resbuf *        nse_fromNse(struct resbuf *pBuf) ;
	ENsiBoolean nse_toNse(struct resbuf *pBuf) ;
	ENsiBoolean            addObj(const CNseApiObj *pObj) ;
	ENsiBoolean            remObj(const CNseApiObj *pObj) ;
	ENsiBoolean            mapErrFromNse(void *pNse, void *pErr);
	friend class CNseApiObj ;
	friend class CNseLinkPath ;
	friend class CNseLink ;
	friend class CNseLinkSel ;
	friend class CNseApiErr ;
	TCHAR                  *mpVersion ;
	void                  *mpRes ;
	void                  *mpObjs ;
	ENsiBoolean            mIsDiffChar ;
	TCHAR                  *mpDefChar ;
	ETransactionMode      meTransMode;
};

//////////////////////////////////////////////////////////////////////////
// CNseLinkPath
class CNseLinkPath : public CNseApiObj {
public:
	                     CNseLinkPath(CNseApiObj *pObj) ;
	                     CNseLinkPath(CNseApiObj &Obj) ;
	virtual                ~CNseLinkPath() ;
	virtual ENsiBoolean    init() ;
	virtual ENseApiClassId isA() const ;
	virtual CNseApiObj    *clone() const ;
	virtual ENsiBoolean    copyFrom(const CNseApiObj *pObj) ;
	virtual CNseApiObj&    operator=(const CNseApiObj &Obj) ;
	virtual int            operator==(const CNseApiObj *pObj) const ;
	virtual int            operator==(const CNseApiObj &Obj) const ;
	virtual ENsiBoolean    isInit() const ;
	ENsiBoolean            initPath(const NCHAR *pPath) ;
	ENsiBoolean            initName(const NCHAR *pName) ;
	ENsiBoolean            initCurrent() ;
	ENsiBoolean            reInit();
	ENsiBoolean            setName(const NCHAR *pName,
                                   ENseDoNameCode NameCode=kNseLpnCode) ;
ENsiBoolean            getName(NCHAR *pBuf, int BufLen,
                               ENseDoNameCode NameCode=kNseLpnCode) const ;
int                    getNameSize(ENseDoNameCode NameCode=kNseLpnCode) const;
int                    cmpName(const NCHAR *pName,
                               ENseDoNameCode NameCode=kNseLpnCode) const ;
int                    cmpName(const CNseLinkPath *pLinkPath,
                               ENseDoNameCode NameCode=kNseLpnCode) const ;
ENseDoNameCode         getPathCode() const;
int                    getStatus() const;
ENsiBoolean            isUpdatable() const ;
ENsiBoolean            getKeyDsc(CNsiRow **pKeyDsc) const;
ENsiBoolean            getKeyDsc(CNsiColumn **pKeyDsc[], int *pColQty) const;
ENsiBoolean            create(const CNsiRow *pKeyDsc) ;
ENsiBoolean            create(const CNsiRow &KeyDsc) ;
ENsiBoolean            create(const CNsiColumn *pKeyDsc[], int ColQty) ;
ENsiBoolean            erase() ;
ENsiBoolean            rename(const NCHAR *pLinkPathName) ;
ENsiBoolean            setCurrent() const ;
struct resbuf         *getLinkNames() const ;
struct resbuf         *getPaths(int Status) const ;
ENsiBoolean connectNse(const NCHAR *pUsername=NULL,
                       const NCHAR *pPassword=NULL,
                       ENsiBoolean fPrompt=kNsiFalse) ;
ENsiBoolean            connectNseIniString (const NCHAR *pIniString);
ENsiBoolean disconnectNse();
ENsiBoolean            checkOp(ulong status) const;
ENsiBoolean            getTableDsc(CNsiRow **pColumns) const;
ENsiBoolean            getTableDsc(CNsiColumn **pKeyDsc[],
                                   int *pColQty) const;
ENsiBoolean            createTable(const CNsiRow *pCols);
ENsiBoolean            createTable(const CNsiColumn *pCols[],
                                   int colNum);
ENsiBoolean            dropTable();
ENsiBoolean            updRow(const CNsiRow *pKey,
                              const CNsiRow *pValue,
                              long *pRowsQty=NULL) const;
ENsiBoolean            updRow(const CNsiColumn *pKey[],
                              int numKeys,
                              const CNsiColumn *pValue[],
                              int numValues,
                              long *pRowsQty=NULL) const;
ENsiBoolean            delRow(const CNsiRow *pValue,
                              long *pRowsQty=NULL) const;
ENsiBoolean            delRow(const CNsiColumn *pValue[],
                              int numKeys,
                              long *pRowsQty=NULL) const;
ENsiBoolean            addRow(const CNsiRow *pValue) const;
ENsiBoolean            addRow(const CNsiColumn *pValue[],
                              int numValues) const;
ENsiBoolean            getRow(const CNsiRow *pKeyValue,
                              CNsiRow *pRowBuffer) const;
ENsiBoolean            setDwg(const NcDbDatabase *pDwg=WORKINGDWG()) ;
const NcDbDatabase*    getDwg() const ;
ENsiBoolean            allocCursor(const CNsiRow *pKeyDsc,
                                   const CNsiRow *pRow,
                                   long *pCursorNum) const;
ENsiBoolean            getCursorRow(long cursorNum,
                                    const CNsiRow *pKeyValue,
                                    CNsiRow *pRow) const;
ENsiBoolean            delCursor(long cursorNum) const;
protected:
	void                   *mpPath ;
	void                   *mpDwg ;
};

//////////////////////////////////////////////////////////////////////////
// CNseLink
class CNseLink : public CNseApiObj {
public:
	                     CNseLink(CNseApiObj *pObj) ;
	                     CNseLink(CNseApiObj &Obj) ;
	virtual                ~CNseLink() ;
	virtual ENsiBoolean    init() ;
	ENsiBoolean            initType(ENseLinkType lType) ;
	ENsiBoolean            initId(LinkID linkId) ;
	ENsiBoolean            initEnt(const NCHAR *pName,
                                   const CNsiRow *pKeyValue,
                                   nds_name EntName) ;
	ENsiBoolean            initEnt(const NCHAR *pName,
	                               const CNsiRow &KeyValue,
	                               nds_name EntName) ;
	ENsiBoolean            initEnt(const NCHAR *pName,
	                               const CNsiColumn *pKeyValue[],
	                               int ColQty,
	                               nds_name EntName) ;
	ENsiBoolean            initDA(const NCHAR *pName,
	                              const CNsiRow *pKeyValue,
	                              const CNsiRow *pDACols,
	                              const struct resbuf *pDAParms) ;
	ENsiBoolean            initDA(const NCHAR *pName,
	                              const CNsiRow &KeyValue,
	                              const CNsiRow &DACols,
	                              const struct resbuf *pDAParms) ;
	ENsiBoolean            initDA(const NCHAR *pName,
	                              const CNsiColumn *pKeyValue[],
	                              int ColQty,
	                              const CNsiColumn *pDACols[],
	                              int DAColQty,
	                              const struct resbuf *pDAParms) ;
	virtual ENseApiClassId isA() const ;
	virtual CNseApiObj    *clone() const ;
	virtual ENsiBoolean    copyFrom(const CNseApiObj *pObj) ;
	virtual CNseApiObj&    operator=(const CNseApiObj &Obj) ;
	virtual int            operator==(const CNseApiObj *pObj) const ;
	virtual int            operator==(const CNseApiObj &Obj) const ;
	virtual ENsiBoolean    isInit() const ;
	LinkID                 getId () const ;
	ENseLinkType           getType() const ;
	ENsiBoolean            getName(NCHAR *pBuf, int len) const;
	int                    getNameSize() const ;
	ENsiBoolean            setName(const NCHAR *pName) ;
	ENsiBoolean            getEntity(nds_name EntName) const ;
	ENsiBoolean            setEntity(nds_name EntName) ;
	ENsiBoolean            getKey(CNsiRow *pKeyValue) const ;
	ENsiBoolean            getKey(CNsiRow &KeyValue) const ;
	ENsiBoolean            getKey(CNsiColumn *pKeyValue[], int ColQty) const ;
	ENsiBoolean            setKey(const CNsiRow *pKeyValue) ;
	ENsiBoolean            setKey(const CNsiRow &KeyValue) ;
	ENsiBoolean            setKey(const CNsiColumn *pKeyValue[], int ColQty) ;
	ENsiBoolean            setDACols (const CNsiRow *pCols) ;
	ENsiBoolean            setDACols (const CNsiRow &Cols) ;
	ENsiBoolean            setDACols(CNsiColumn *pCols[], int ColQty) ;
	ENsiBoolean            getDACols (CNsiRow **pCols) const ;
	ENsiBoolean            getDACols(CNsiColumn **pCols[], int *pColQty) const ;
	ENsiBoolean            setDAParms(const struct resbuf *pParms) ;
	ENsiBoolean            setDAValues(const CNsiRow *pDAValues) ;
	ENsiBoolean            setDAValues(const CNsiRow &DAValues) ;
	ENsiBoolean            setDAValues(CNsiColumn *pCols[], int ColQty) ;
	ENsiBoolean            create () ;
	ENsiBoolean            remove () ;
	ENsiBoolean            update () ;
	ENsiBoolean            getXName(NCHAR *pBuf, int len) const ;
	ENsiBoolean            isUpdatable() const ;
	ENsiBoolean            setDwg(const NcDbDatabase *pDwg=WORKINGDWG()) ;
	const NcDbDatabase*    getDwg() const ;
	struct resbuf         *getAttr(ENseLinkAttr LinkAttr) const ;
	ENsiBoolean            setAttr(ENseLinkAttr LinkAttr,
	                               const struct resbuf *pAttrValue) ;
private:
	struct resbuf      *mpBuf ;
	void               *mpDwg ;
};

//////////////////////////////////////////////////////////////////////////
// CNseLinkSel
class CNseLinkSel : public CNseApiObj {
public:
	                     CNseLinkSel(CNseApiObj *pObj) ;
	                     CNseLinkSel(CNseApiObj &Obj) ;
	virtual                ~CNseLinkSel() ;
	virtual ENsiBoolean    init() ;
	ENsiBoolean            initType(ENseLinkType LinkType) ;
	ENsiBoolean            initSel(nds_name EntSelName,
                                   ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initEnt(nds_name EntName,
	                               ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initXName(const NCHAR *pXName,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLp(const NCHAR *pName,
	                              ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLp(const CNseLinkPath *pLinkPath,
	                              ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLp(const CNseLinkPath &LinkPath,
	                              ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpEnt(const NCHAR *pName,
	                                 nds_name EntName,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpEnt(const CNseLinkPath *pLinkPath,
	                                 nds_name EntName,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpEnt(const CNseLinkPath &LinkPath,
	                                 nds_name EntName,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpKey(const NCHAR *pName,
	                                 const CNsiRow *pKeyValue,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpKey(const NCHAR *pName,
	                                 const CNsiRow &KeyValue,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpKey(const CNseLinkPath *pLinkPath,
	                                 const CNsiRow *pKeyValue,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpKey(const CNseLinkPath &LinkPath,
	                                 const CNsiRow &KeyValue,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpKey(const NCHAR *pName,
	                                 const CNsiColumn *pKeyValue[],
	                                 int ColQty,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpKey(const CNseLinkPath *pLinkPath,
	                                 const CNsiColumn *pKeyValue[],
	                                 int ColQty,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpCond(const NCHAR *pName,
	                                  const NCHAR *pTextCondition,
	                                  ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpCond(const CNseLinkPath *pLinkPath,
	                                  const NCHAR *pTextCondition,
	                                  ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpCond(const CNseLinkPath &LinkPath,
	                                  const NCHAR *pTextCondition,
	                                  ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpSel(const NCHAR *pName,
	                                 nds_name EntSelName,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpSel(const CNseLinkPath *pLinkPath,
	                                 nds_name EntSelName,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initLpSel(const CNseLinkPath &LinkPath,
	                                 nds_name EntSelName,
	                                 ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initPartialKey(const NCHAR *pName,
	                                      const CNsiRow *pKeyValue,
	                                      ENseLinkType LinkType=kNseUnknownLinkType) ;
	ENsiBoolean            initPartialKey(const CNseLinkPath *pLinkPath,
	                                      const CNsiRow *pKeyValue,
	                                      ENseLinkType LinkType=kNseUnknownLinkType) ;
	virtual ENseApiClassId isA() const ;
	virtual CNseApiObj    *clone() const ;
	virtual ENsiBoolean    copyFrom(const CNseApiObj *pObj) ;
	virtual CNseApiObj&    operator=(const CNseApiObj &Obj) ;
	virtual int            operator==(const CNseApiObj *pObj) const ;
	virtual int            operator==(const CNseApiObj &Obj) const ;
	virtual ENsiBoolean    isInit() const ;
	ENsiBoolean            isUpdatable() const ;
	long                   getQty() const ;
	LinkID                 getId(long ItemNum) const ;
	ENsiBoolean            addId(LinkID linkId) ;
	ENsiBoolean            delId(long ItemNum) ;
	long                   membId(LinkID linkId) const ;
	ENsiBoolean            unite(const CNseLinkSel *pSel) ;
	ENsiBoolean            unite(const CNseLinkSel &Sel) ;
	ENsiBoolean            subtract(const CNseLinkSel *pSel) ;
	ENsiBoolean            subtract(const CNseLinkSel &Sel) ;
	ENsiBoolean            intersect(const CNseLinkSel *pSel) ;
	ENsiBoolean            intersect(const CNseLinkSel &Sel) ;
	ENsiBoolean            intersectType(ENseLinkType LinkType) ;
	ENsiBoolean            intersectEnt(nds_name EntName) ;
	ENsiBoolean            intersectSel(nds_name EntSelName) ;
	ENsiBoolean            intersectXName(const NCHAR *pXName) ;
	ENsiBoolean            intersectLp(const NCHAR *pName) ;
	ENsiBoolean            intersectLp(const CNseLinkPath *pLinkPath) ;
	ENsiBoolean            intersectLp(const CNseLinkPath &LinkPath) ;
	ENsiBoolean            intersectLpKey(const NCHAR *pName,
	                                      const CNsiRow *pKeyValue) ;
	ENsiBoolean            intersectLpKey(const NCHAR *pName,
	                                      const CNsiRow &KeyValue) ;
	ENsiBoolean            intersectLpKey(const CNseLinkPath *pLinkPath,
	                                      const CNsiRow *pKeyValue) ;
	ENsiBoolean            intersectLpKey(const CNseLinkPath &LinkPath,
	                                      const CNsiRow &KeyValue) ;
	ENsiBoolean            intersectLpKey(const NCHAR *pName,
	                                      const CNsiColumn *pKeyValue[],
	                                      int ColQty) ;
	ENsiBoolean            intersectLpKey(const CNseLinkPath *pLinkPath,
	                                      const CNsiColumn *pKeyValue[],
	                                      int ColQty);
	ENsiBoolean            intersectLpCond(const NCHAR *pName,
	                                       const NCHAR *pTextCondition) ;
	ENsiBoolean            intersectLpCond(const CNseLinkPath *pLinkPath,
	                                       const NCHAR *pTextCondition) ;
	ENsiBoolean            intersectLpCond(const CNseLinkPath &LinkPath,
	                                       const NCHAR *pTextCondition) ;
	ENsiBoolean            intersectPartialKey(const NCHAR *pName,
	                                           const CNsiRow *pKeyValue) ;
	ENsiBoolean            intersectPartialKey(const CNseLinkPath *pLinkPath,
	                                           const CNsiRow *pKeyValue) ;
	ENsiBoolean            getLinkName(long ItemNum,
	                                   TCHAR *pNameBuf,
	                                   int nameBufLen) const;
	ENsiBoolean            getLinkKey(long ItemNum, CNsiRow *pKeyValue);
	ENsiBoolean            getLinkEnt(long ItemNum, nds_name ename);
	int                    getIdArray(NcDbObjectIdArray *pLinkedEntities) const;
	ENsiBoolean            getLinkEnt(long ItemNum, NcDbObjectId *pId);
	ENsiBoolean            setDwg(const NcDbDatabase *pDwg=WORKINGDWG()) ;
	const NcDbDatabase*    getDwg() const ;
	struct resbuf         *getXNames() const ;
	struct resbuf         *getLinkNames() const ;
	ENsiBoolean            getEntSel(nds_name EntSelName) const ;
	ENsiBoolean            erase() ;
	virtual ENsiBoolean    initFilter(struct resbuf *pLinkFilter,
	                                  ENsiBoolean needFullOpen=kNsiFalse) ;
	virtual ENsiBoolean    intersectFilter(const struct resbuf *pLinkFilter) ;
protected:
	void                   freeSel() ;
	struct resbuf         *makeFilter(ENseLinkType LinkType,
                                      const NCHAR *pXName,
                                      nds_name EntName,
                                      nds_name EntSelName,
                                      const NCHAR *pName,
                                      const CNseLinkPath *pLinkPath,
                                      const CNsiRow *pKeyValue,
                                      const NCHAR *pTextCondition,
                                      const CNsiRow *pParKeyValue = NULL) ;
LinkSelID              mSelId ;
void                   *mpDwg ;
};



NRXDBGATE_EXPORT NsiUcChar  NsiCh2Uc          (int,NsiUcNmCCT);
NRXDBGATE_EXPORT int        NsiChStrUclnIdCCT (const char*,NsiUcIdCCT);

#define NSI_THROW_LAST    NsiExceptionThrow(0);

ENsiBoolean NsiAllocateDSEnumerator (
	CNsiAppl        *        pAppl,
	const GUID      *       guidEnum,
	const CNsiUcStr &       pDS,
	CNsiEnumerator  **      pEnum
);

ENsiBoolean NsiGetDSEnumerator (
	CNsiAppl        *        pAppl,
	const GUID      *       guidEnum,
	const CNsiUcStr &       pDS,
	GUID            *       guidDsEnum
);

NRXDBGATE_EXPORT int        NsiUc2Ch          (NsiUcChar,NsiUcNmCCT);
NRXDBGATE_EXPORT double     NsiUcAtof         (const NsiUcStr);
NRXDBGATE_EXPORT int        NsiUcAtoi         (const NsiUcStr);
NRXDBGATE_EXPORT long       NsiUcAtol         (const NsiUcStr);
NRXDBGATE_EXPORT int        NsiUcCh2UcCCT     (NsiUcStr,int,const char*,int,NsiUcIdCCT);
NRXDBGATE_EXPORT int        NsiUcCiChcmp      (NsiUcIdCLT,NsiUcChar,NsiUcChar);
NRXDBGATE_EXPORT int        NsiUcCiStrcmp     (NsiUcIdCLT,const NsiUcStr,const NsiUcStr);
NRXDBGATE_EXPORT int        NsiUcCiStrIcmp    (NsiUcIdCLT,const NsiUcStr,const NsiUcStr);
NRXDBGATE_EXPORT int        NsiUcCiStrncmp    (NsiUcIdCLT,const NsiUcStr,const NsiUcStr,int);
NRXDBGATE_EXPORT int        NsiUcCiStrStrcmpA (NsiUcIdCLT,NsiUcIdCCT,const char*,const char*);
NRXDBGATE_EXPORT int        NsiUcCiStrStrcmpW (NsiUcIdCLT,NsiUcIdCCT,const wchar_t*,const wchar_t*);
NRXDBGATE_EXPORT int        NsiUcCiStrStrIcmpA(NsiUcIdCLT,NsiUcIdCCT,const char*,const char*);
NRXDBGATE_EXPORT int        NsiUcCiStrStrIcmpW(NsiUcIdCLT,NsiUcIdCCT,const wchar_t*,const wchar_t*);
NRXDBGATE_EXPORT int        NsiUcCiStrweight  (NsiUcIdCLT,const NsiUcStr,unsigned char *,int);
NRXDBGATE_EXPORT int        NsiUcCiUcChStrcmp (NsiUcIdCLT,NsiUcIdCCT,const NsiUcStr,const char*);
NRXDBGATE_EXPORT int        NsiUcCmpUCandUC   (const NsiUcStr,const NsiUcStr);
NRXDBGATE_EXPORT int        NsiUcCnChcmp      (NsiUcNmCLT,NsiUcChar,NsiUcChar);
NRXDBGATE_EXPORT int        NsiUcCnStrcmp     (NsiUcNmCLT,const NsiUcStr,const NsiUcStr);
NRXDBGATE_EXPORT int        NsiUcCnStrncmp    (NsiUcNmCLT,const NsiUcStr,const NsiUcStr,int);
NRXDBGATE_EXPORT NsiUcNmCCT NsiUcDefaultCCT   (void);
NRXDBGATE_EXPORT NsiUcNmCLT NsiUcDefaultCLT   (void);
NRXDBGATE_EXPORT NsiUcIdCCT NsiUcGetIdCCT     (NsiUcNmCCT);
NRXDBGATE_EXPORT NsiUcIdCLT NsiUcGetIdCLT     (NsiUcNmCLT);
NRXDBGATE_EXPORT NsiUcNmCCT NsiUcGetNmCCT     (NsiUcIdCCT);
NRXDBGATE_EXPORT NsiUcNmCLT NsiUcGetNmCLT     (NsiUcIdCLT);

NRXDBGATE_EXPORT int         NsiUcIsAlnum      (NsiUcChar);
NRXDBGATE_EXPORT int          NsiUcIsAlpha      (NsiUcChar);
NRXDBGATE_EXPORT int          NsiUcIsCntrl      (NsiUcChar);
NRXDBGATE_EXPORT int          NsiUcIsDigit      (NsiUcChar);
NRXDBGATE_EXPORT int          NsiUcIsGraph      (NsiUcChar);
NRXDBGATE_EXPORT int          NsiUcIsLower      (NsiUcChar);
NRXDBGATE_EXPORT int          NsiUcIsPrint      (NsiUcChar);
NRXDBGATE_EXPORT int          NsiUcIsPunct      (NsiUcChar);
NRXDBGATE_EXPORT int          NsiUcIsSpace      (NsiUcChar);
NRXDBGATE_EXPORT int          NsiUcIsUpper      (NsiUcChar);
NRXDBGATE_EXPORT int          NsiUcIsXdigit     (NsiUcChar);
NRXDBGATE_EXPORT int        NsiUcSprintf      (NsiUcStr,const NsiUcStr, ...);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrcat       (NsiUcStr,const NsiUcStr);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrCh2Uc     (NsiUcStr,int,const char*,int,NsiUcNmCCT);
NRXDBGATE_EXPORT int        NsiUcStrchln      (const NsiUcStr,NsiUcNmCCT);
NRXDBGATE_EXPORT int        NsiUcStrchlnIdCCT (const NsiUcStr,NsiUcIdCCT);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrchr       (const NsiUcStr,NsiUcChar);
NRXDBGATE_EXPORT int        NsiUcStrcmp       (const NsiUcStr,const NsiUcStr);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrcpy       (NsiUcStr,const NsiUcStr);
NRXDBGATE_EXPORT int        NsiUcStricmp      (const NsiUcStr,const NsiUcStr);
NRXDBGATE_EXPORT int        NsiUcStrlen       (const NsiUcStr);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrLower     (NsiUcStr);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrncat      (NsiUcStr,const NsiUcStr,int);
NRXDBGATE_EXPORT int        NsiUcStrncmp      (const NsiUcStr,const NsiUcStr,int);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrncpy      (NsiUcStr,const NsiUcStr,int);
NRXDBGATE_EXPORT int        NsiUcStrnicmp     (const NsiUcStr,const NsiUcStr,int);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrrchr      (const NsiUcStr,NsiUcChar);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrrstr      (const NsiUcStr,const NsiUcStr);
NRXDBGATE_EXPORT int        NsiUcStrsize      (const NsiUcStr);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrstr       (const NsiUcStr,const NsiUcStr);
NRXDBGATE_EXPORT double     NsiUcStrtod       (const NsiUcStr,NsiUcStr*);
NRXDBGATE_EXPORT long       NsiUcStrtol       (const NsiUcStr,NsiUcStr*,int);
NRXDBGATE_EXPORT char        *NsiUcStrUc2Ch     (char*,int,const NsiUcStr,int,NsiUcNmCCT);
NRXDBGATE_EXPORT NsiUcStr   NsiUcStrUpper     (NsiUcStr);
NRXDBGATE_EXPORT NsiUcChar  NsiUcToLower      (NsiUcChar);
NRXDBGATE_EXPORT NsiUcChar  NsiUcToUpper      (NsiUcChar);
NRXDBGATE_EXPORT int        NsiUcUc2ChCCT     (char*,int,const NsiUcStr,int,NsiUcIdCCT);

#endif
#endif // __OPENDWG_SQLINTERFACE_H__
