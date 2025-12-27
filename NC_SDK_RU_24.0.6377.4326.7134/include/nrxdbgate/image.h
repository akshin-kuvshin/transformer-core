#ifndef  NTIL_H
#define  NTIL_H
#include "nrxdbgate_impexp.h"

namespace Ntil
{

class FileReadDescriptorRep;
class FileSpecifier;
class FileWriteDescriptorRep;
class FindFileInterface;
class FormatCodecApiVersionInterface;
class FormatCodecPropertySetIterator;
class ImageContextRep;
class ImageFormatCodec;
class ImageReactorInterface;
class ImageRep;
class Matrix2d;
class PropertyStringProviderInterface;
class ReadImageFileInterface;
class RgbGrayModel;
class RowProviderInterface;
class Vector2d;
class WriteImageFileInterface;
class Size;
class Offset;
struct ImagePixel;

NRXDBGATE_EXPORT RowProviderInterface* newScaleFilter(RowProviderInterface* pInput, const Size& output);
NRXDBGATE_EXPORT RowProviderInterface* newScaleFilter(const Image* pImage, const Size& szOutput);
NRXDBGATE_EXPORT RowProviderInterface* newScaleFilter(const Image* pImage, const Size& size, const Offset& offset, const Size& szOutput);

struct NRXDBGATE_EXPORT Resample {
	enum FilterTypes { 
		kNearest, 
		kTriangle, 
		kCubic, 
		kBell, 
		kBSpline, 
		kLanczos3, 
		kMitchell 
	};
};

NRXDBGATE_EXPORT RowProviderInterface* newResampleFilter(const Image* pImage, const Size& size, const Offset& offset, Resample::FilterTypes filterMethod, bool bAdaptive, bool bProcessAlpha, const Size& szOutput);
NRXDBGATE_EXPORT RowProviderInterface* newResampleFilter(RowProviderInterface* pInput, const Size& output, Resample::FilterTypes filterMethod, bool bAdaptive = false, bool bProcessAlpha = false, bool bReturnRaw = false, ImagePixel const* pVoidPixel = NULL);

struct NRXDBGATE_EXPORT Shear {
	enum Quality {
		kInterpolate,
		kRound
	};
};

NRXDBGATE_EXPORT RowProviderInterface* newXShearFilter(RowProviderInterface* pInput, const double& dXShear, ImagePixel clearColor, Shear::Quality quality, bool bProcessAlpha = false , bool bReturnRaw = false);
NRXDBGATE_EXPORT RowProviderInterface* newYShearFilter(RowProviderInterface* pInput, const double& dYShear, ImagePixel clearColor, Shear::Quality quality, bool bProcessAlpha = false , bool bReturnRaw = false);
NRXDBGATE_EXPORT RowProviderInterface* newRotateFilter(RowProviderInterface* pInput, const double& dAngle, ImagePixel clearColor, Shear::Quality method, bool bProcessAlpha = false, bool bReturnRaw = false);

enum Orientation
{
	kTopDownLeftRight,
	kTopDownRightLeft,
	kBottomUpLeftRight,
	kBottomUpRightLeft,
	kLeftRightTopDown,
	kRightLeftTopDown,
	kLeftRightBottomUp,
	kRightLeftBottomUp 
};

const double kPi = 3.14159265358979323846;

const double kTwoPi = 6.28318530717958647692;
const double kHalfPi = 1.57079632679489661923;
const double kTolerance = 1.0e-10;
const double kEpsilon = 1.0e-10;

#ifdef _WIN32
	typedef unsigned char Data8;
	typedef unsigned short Data16;
	typedef unsigned int Data32;
	typedef unsigned __int64 Data64;
	typedef struct _NTIL_DATA128 { \
		union { \
			struct { unsigned int a; unsigned int b; unsigned int c; unsigned int d; } ui; \
			struct { float a; float b; float c; float d; } fl; \
			struct { Data64 high64; Data64 low64; } db; \
		} value; \
		bool operator== (const struct _NTIL_DATA128& rhs) const { return (value.ui.a == rhs.value.ui.a && value.ui.b == rhs.value.ui.b && value.ui.c == rhs.value.ui.c && value.ui.d == rhs.value.ui.d); } \
		bool operator!= (const struct _NTIL_DATA128& rhs) const { return (value.ui.a != rhs.value.ui.a || value.ui.b != rhs.value.ui.b || value.ui.c != rhs.value.ui.c || value.ui.d != rhs.value.ui.d); } \
		void setToZero() {value.db.high64 = 0; value.db.low64 = 0;} \
	} Data128;

	typedef unsigned char Byte;

	typedef signed char Int8;
	typedef unsigned char UInt8;

	typedef signed short Int16;
	typedef unsigned short UInt16;

	typedef signed int Int32;
	typedef unsigned int UInt32;

	typedef signed __int64 Int64;
	typedef unsigned __int64 UInt64;

#ifndef INT32_MAX
	#define INT32_MAX 2147483647
#endif
#ifndef INT32_MIN
	#define INT32_MIN -2147483647-1
#endif
#ifndef UINT32_MAX
	#define UINT32_MAX 4294967295
#endif
#ifndef NULL
#define NULL 0
#endif

#ifdef UNICODE
	typedef wchar_t char_t;
#else
	typedef char char_t;
#endif

#else

#ifdef __INTEL_COMPILER
	typedef unsigned char Data8;
	typedef unsigned short Data16;
	typedef unsigned int Data32;
	typedef unsigned __int64 Data64;
	typedef struct _NTIL_DATA128 { \
		union { \
			struct { unsigned int a; unsigned int b; unsigned int c; unsigned int d; } ui; \
			struct { float a; float b; float c; float d; } fl; \
			struct { Data64 high64; Data64 low64; } db; \
		} value; \
		bool operator== (const struct _NTIL_DATA128& rhs) const { return (value.ui.a == rhs.value.ui.a && value.ui.b == rhs.value.ui.b && value.ui.c == rhs.value.ui.c && value.ui.d == rhs.value.ui.d); } \
		bool operator!= (const struct _NTIL_DATA128& rhs) const { return (value.ui.a != rhs.value.ui.a || value.ui.b != rhs.value.ui.b || value.ui.c != rhs.value.ui.c || value.ui.d != rhs.value.ui.d); } \
		void setToZero() {value.db.high64 = 0; value.db.low64 = 0;} \
	} Data128;

	typedef unsigned char Byte;

	typedef signed char Int8;
	typedef unsigned char UInt8;

	typedef signed short Int16;
	typedef unsigned short UInt16;

	typedef signed int Int32;
	typedef unsigned int UInt32;

	typedef signed __int64 Int64;
	typedef unsigned __int64 UInt64;

	#define INT32_MAX   2147483647
	#define INT32_MIN  -2147483647-1
	#define UINT32_MAX  4294967295

#ifndef NULL
#define NULL    0
#endif

#ifdef UNICODE
	typedef wchar_t char_t;
#else
	typedef char char_t;
#endif

#else // Gnu

typedef unsigned char Data8;
typedef unsigned short Data16;
typedef unsigned int Data32;
typedef unsigned long long Data64;
typedef struct _NTIL_DATA128 { \
	union { \
	    struct { unsigned int a; unsigned int b; unsigned int c; unsigned int d; } ui; \
	    struct { float a; float b; float c; float d; } fl; \
	    struct { Data64 high64; Data64 low64; } db; \
	} value; \
	bool operator== (const struct _NTIL_DATA128& rhs) const { return (value.ui.a == rhs.value.ui.a && value.ui.b == rhs.value.ui.b && value.ui.c == rhs.value.ui.c && value.ui.d == rhs.value.ui.d); } \
	bool operator!= (const struct _NTIL_DATA128& rhs) const { return (value.ui.a != rhs.value.ui.a || value.ui.b != rhs.value.ui.b || value.ui.c != rhs.value.ui.c || value.ui.d != rhs.value.ui.d); } \
	void setToZero() {value.db.high64 = 0; value.db.low64 = 0;} \
} Data128;


typedef unsigned char Byte;

typedef signed char Int8;
typedef unsigned char UInt8;

typedef signed short Int16;
typedef unsigned short UInt16;

typedef signed int Int32;
typedef unsigned int UInt32;

typedef signed long long Int64;
typedef unsigned long long UInt64;

#define INT32_MAX   2147483647
#define INT32_MIN  -2147483647-1
#define UINT32_MAX  4294967295

#ifndef NULL
#define NULL 0
#endif

#ifdef UNICODE
typedef wchar_t char_t;
#else
typedef char char_t;
#endif

#endif
#endif

typedef union _NTIL_LARGE_INTEGER {
	struct {
		UInt32 LowPart;
		int HighPart;
	} s;
	struct {
		UInt32 LowPart;
		int HighPart;
	} u;
	UInt64 QuadPart;
} NTIL_LARGE_INTEGER;

#ifndef PNG_H
struct png_info_struct;
typedef struct png_info_struct png_info;
typedef png_info* png_infop;

struct png_struct_def;
typedef struct png_struct_def png_struct;
typedef png_struct* png_structp;
#endif

//////////////////////////////////////////////////////////////////////////
// Ntil:DataModelAttributes
class NRXDBGATE_EXPORT DataModelAttributes {
public:
	enum BitsPerPixel { k1, k8, k16, k32, k64, k128 };
	enum DataModelType {
		kDataModel,
		kRgbModel,
		kPalettedRgbModel,
		kGrayModel,
		kBitonalModel,
		kRgbModel5b,
		kRgbModel10,
		kRgbModel16i,
		kRgbModel16f,
		kRgbModel32f,
		kGrayModel16i,
		kGrayModel16f,
		kGrayModel32f
	};
	enum PixelType {
		kData1,
		kData8,
		kData16,
		kData32,
		kData64,
		kData128,
		kBitonal,
		kGray,
		kPalettedRgb,
		kRgba,
		kBgra,
		kGray16i,
		kGray16f,
		kGray32f
	};
	enum DataType {
		kUnknown,
		kUnsignedShort,
		kSignedShort,
		kUnsignedInteger,
		kSignedInteger,
		kFloat16,
		kFloat,
		kBitFields
	};
	enum BitFields {
		kFull,
		k5551,
		k565
	};
	enum ChannelOrder {
		kSingleChannel,
		kRedGreenBlueAlpha,
		kBlueGreenRedAlpha
	};
public:
	static DataModelAttributes::BitsPerPixel bitsPerPixel (DataModelAttributes::PixelType pixType);
	virtual BitsPerPixel bitsPerPixel () const = 0;
	virtual int bitsUsedPerPixel () const = 0;
	virtual DataModelType dataModelType () const = 0;
	virtual PixelType pixelType () const = 0;
	virtual DataType dataType () const = 0;
	virtual BitFields bitFields () const = 0;
	virtual DataModelAttributes::ChannelOrder channelOrder() const = 0;
protected:
	virtual ~DataModelAttributes ();
};

//////////////////////////////////////////////////////////////////////////
// half
class NRXDBGATE_EXPORT half {
public:
	half ();
	half (float f);
	operator        float () const;
	half        operator - () const;
	half &        operator = (half  h);
	half &        operator = (float f);
	half &        operator += (half  h);
	half &        operator += (float f);
	half &        operator -= (half  h);
	half &        operator -= (float f);
	half &        operator*= (half  h);
	half &        operator*= (float f);
	half &        operator /= (half  h);
	half &        operator /= (float f);
	half        round (unsigned int n) const;
	bool        isFinite () const;
	bool        isNormalized () const;
	bool        isDenormalized () const;
	bool        isZero () const;
	bool        isNan () const;
	bool        isInfinity () const;
	bool        isNegative () const;
	static half        posInf ();
	static half        negInf ();
	static half        qNan ();
	static half        sNan ();
	unsigned short    bits () const;
	void        setBits (unsigned short bits);
public:
	union uif
	{
		unsigned int    i;
		float        f;
	};
private:
	static short    convert (int i);
	static float    overflow ();
	unsigned short    _h;
#ifndef OPENEXR_DLL
	static const uif            _toFloat[1 << 16];
	static const unsigned short _eLut[1 << 9];
#endif
};

//////////////////////////////////////////////////////////////////////////
// Ntil:RgbColor
struct NRXDBGATE_EXPORT RgbColor {
public:
	RgbColor ( );
	RgbColor ( Data32 color );
	RgbColor (Data8 red, Data8 green, Data8 blue);
	RgbColor (Data8 first, Data8 second, Data8 third, Data8 alpha);
	const RgbColor& set (Data8 red, Data8 green, Data8 blue);
	const RgbColor& set (Data8 red, Data8 green, Data8 blue, Data8 alpha,
	                     DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kRedGreenBlueAlpha);
	Data8 asGray (DataModelAttributes::ChannelOrder format = DataModelAttributes::kRedGreenBlueAlpha) const;
	union {
		struct {
			Data8 red;
			Data8 green;
			Data8 blue;
			Data8 alpha;
		} rgba;
		struct {
			Data8 blue;
			Data8 green;
			Data8 red;
			Data8 alpha;
		} bgra;
		Data32 packed;
	};
	const RgbColor& operator=( const RgbColor& rhs );
	const RgbColor& operator=( Data32 rhs );
	operator Data32() const;
	bool operator==( const RgbColor& rhs ) const;
	bool operator==( Data32 rhs ) const;
	bool operator!=( const RgbColor& rhs ) const;
	bool operator!=( Data32 rhs ) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:RgbColor5b
struct NRXDBGATE_EXPORT RgbColor5b {
public:
	enum Fields {
		k5551,
		k565,
	};
public:
	RgbColor5b ( );
	RgbColor5b ( Data16 color );
	RgbColor5b (Data8 red, Data8 green, Data8 blue);
	RgbColor5b (Data8 first, Data8 second, Data8 third, Data8 alpha
	    , DataModelAttributes::BitFields fields = DataModelAttributes::k5551);
	const RgbColor5b& set (Data8 red, Data8 green, Data8 blue);
	const RgbColor5b& set (Data8 red, Data8 green, Data8 blue, Data8 alpha
	    , DataModelAttributes::BitFields fields = DataModelAttributes::k5551
	    , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);
	void getChannelData (Data8& red, Data8& green, Data8& blue, Data8& alpha
	    , DataModelAttributes::BitFields fields, DataModelAttributes::ChannelOrder fmt) const;
	RgbColor asRgbColor (DataModelAttributes::BitFields fields, DataModelAttributes::ChannelOrder fmt) const;
	RgbColor asBgrColor (DataModelAttributes::BitFields fields, DataModelAttributes::ChannelOrder fmt) const;
	Data8 asGray (DataModelAttributes::BitFields fields
	    , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;
	Data16 packed;
	const RgbColor5b& operator=( const RgbColor5b& rhs );
	const RgbColor5b& operator=( Data16 rhs );
	operator Data16() const;
	bool operator==( const RgbColor5b& rhs ) const;
	bool operator==( Data16 rhs ) const;
	bool operator!=( const RgbColor5b& rhs ) const;
	bool operator!=( Data16 rhs ) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:RgbColor10
struct NRXDBGATE_EXPORT RgbColor10 {
public:
	RgbColor10 ( );
	RgbColor10 ( Data32 color );
	RgbColor10 (Data16 red, Data16 green, Data16 blue);
	RgbColor10 (Data16 first, Data16 second, Data16 third, Data16 alpha);
	const RgbColor10& set (Data16 red, Data16 green, Data16 blue);
	const RgbColor10& set (Data16 red, Data16 green, Data16 blue, Data16 alpha
	    , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);
	void getChannelData (Data16& red, Data16& green, Data16& blue, Data16& alpha
	    , DataModelAttributes::ChannelOrder fmt) const;
	RgbColor asRgbColor (DataModelAttributes::ChannelOrder fmt) const;
	RgbColor asBgrColor (DataModelAttributes::ChannelOrder fmt) const;
	Data16 asGray (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;
	Data32 packed;
	const RgbColor10& operator=( const RgbColor10& rhs );
	const RgbColor10& operator=( Data32 rhs );
	operator Data32() const;
	bool operator==( const RgbColor10& rhs ) const;
	bool operator==( Data32 rhs ) const;
	bool operator!=( const RgbColor10& rhs ) const;
	bool operator!=( Data32 rhs ) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:RgbColor16i
struct NRXDBGATE_EXPORT RgbColor16i {
public:
	RgbColor16i ( );
	RgbColor16i ( Data64 color );
	RgbColor16i (Data16 red, Data16 green, Data16 blue);
	RgbColor16i (Data16 first, Data16 second, Data16 third, Data16 alpha);
	const RgbColor16i& set (Data16 red, Data16 green, Data16 blue);
	const RgbColor16i& set (Data16 red, Data16 green, Data16 blue, Data16 alpha
	    , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);
	RgbColor asRgbColor (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;
	RgbColor asBgrColor (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;
	Data16 asGray (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;
	union {
		struct {
			Data16 red;
			Data16 green;
			Data16 blue;
			Data16 alpha;
		} rgba;
		struct {
			Data16 blue;
			Data16 green;
			Data16 red;
			Data16 alpha;
		} bgra;
		Data64 packed;
	};
	const RgbColor16i& operator=( const RgbColor16i& rhs );
	const RgbColor16i& operator=( Data64 rhs );
	operator Data64() const;
	bool operator==( const RgbColor16i& rhs ) const;
	bool operator==( Data64 rhs ) const;
	bool operator!=( const RgbColor16i& rhs ) const;
	bool operator!=( Data64 rhs ) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:RgbColor16f
struct NRXDBGATE_EXPORT RgbColor16f {
public:
	RgbColor16f ( );
	RgbColor16f ( Data64 color );
	RgbColor16f (half red, half green, half blue);
	RgbColor16f (half first, half second, half third, half alpha);
	const RgbColor16f& set (half red, half green, half blue);
	const RgbColor16f& set (half red, half green, half blue, half alpha
	    , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);
	RgbColor asRgbColor (DataModelAttributes::ChannelOrder fmt) const;
	RgbColor asBgrColor (DataModelAttributes::ChannelOrder fmt) const;
	half asGray (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;
	typedef struct {
		half blue;
		half green;
		half red;
		half alpha;
	} Channels;
	Data64 packed;
	Channels getChannelData() const;
	const RgbColor16f& operator=( const RgbColor16f& rhs );
	const RgbColor16f& operator=( Data64 rhs );
	operator Data64() const;
	bool operator==( const RgbColor16f& rhs ) const;
	bool operator==( Data64 rhs ) const;
	bool operator!=( const RgbColor16f& rhs ) const;
	bool operator!=( Data64 rhs ) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:RgbColor32f
struct NRXDBGATE_EXPORT RgbColor32f {
public:
	RgbColor32f ( );
	RgbColor32f ( Data128 color );
	RgbColor32f (float red, float green, float blue);
	RgbColor32f (float first, float second, float third, float alpha);
	const RgbColor32f& set (float red, float green, float blue);
	const RgbColor32f& set (float red, float green, float blue, float alpha
	    , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);
	RgbColor asRgbColor (DataModelAttributes::ChannelOrder fmt) const;
	RgbColor asBgrColor (DataModelAttributes::ChannelOrder fmt) const;
	float asGray (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;
	Data128 pixel;
	const RgbColor32f& operator=( const RgbColor32f& rhs );
	const RgbColor32f& operator=( Data128 rhs );
	operator Data128() const;
	bool operator==( const RgbColor32f& rhs ) const;
	bool operator==( Data128 rhs ) const;
	bool operator!=( const RgbColor32f& rhs ) const;
	bool operator!=( Data128 rhs ) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ImagePixel
struct NRXDBGATE_EXPORT ImagePixel {
	union {
		Data8  data1;
		Data8  data8;
		Data16 data16;
		Data32 data32;
		Data64 data64;
		Data128 data128;
		Data8  bitonal;
		Data8  gray;
		Data8  index;
		Data32 rgba;
		float  gray32f;
	} value;
	DataModelAttributes::PixelType type;
	ImagePixel (DataModelAttributes::PixelType pixTpe = DataModelAttributes::kData1);
	const ImagePixel& setToZero ();
	bool operator==(const ImagePixel& rhs) const;
	bool operator!=(const ImagePixel& rhs) const;
};


//////////////////////////////////////////////////////////////////////////
// Ntil:StringBuffer
class NRXDBGATE_EXPORT StringBuffer {
public:
	enum CharacterType {
		kASCII,
		kUTF_8,
		kUTF_16,
		kUTF_32,
		kMBCS
	};
	static int bytesInString (const Byte* pString, CharacterType type );
	static void convertString (const StringBuffer& sbString,
	                           StringBuffer& sbResult, CharacterType type );
	static CharacterType defaultCharacterType ();
public:
	StringBuffer ();
	StringBuffer (int nNumBytes, CharacterType type = StringBuffer::kASCII);
	StringBuffer (int nNumBytes, const Byte* pBytes, CharacterType type = StringBuffer::kASCII);
	StringBuffer (const StringBuffer& x);
	virtual ~StringBuffer ();
	virtual const Byte* data () const;
	virtual int numDataBytes () const;
	virtual CharacterType type () const;
	virtual StringBuffer& set (const StringBuffer& string);
	virtual StringBuffer& set (int numBytes, const Byte* pChar, CharacterType type = StringBuffer::kASCII);
	virtual bool isZero () const;
	StringBuffer& operator=( const StringBuffer& rhs );
	bool operator==( const StringBuffer& rhs ) const;
	bool operator!=( const StringBuffer& rhs ) const;
private:
	int mNumBytes;
	Byte* mpData;
	CharacterType  meCharType;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:NTILException
class NRXDBGATE_EXPORT NTILException {
public:
	NTILException (const StringBuffer& sbMessage);
	NTILException ();
	NTILException (const NTILException& x);
	virtual ~NTILException ();
	virtual const StringBuffer* getMessage ();
protected:
	StringBuffer msbMessage;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:DataModel
class NRXDBGATE_EXPORT DataModel : public DataModelAttributes {
public:
	enum TileSize {
		k64x64,
		k128x128,
		k256x256,
		k512x512,
		k1024x1024,
		kUnspecified,
		kDefault
	};
	static int bytesPerRow ( Int32 nPixels, DataModelAttributes::BitsPerPixel bpp );
	static int bitsPerPixel ( DataModelAttributes::BitsPerPixel bpp );
	static void tileSize ( TileSize size, int& nRows, int& nColumns );
public:
	DataModel (DataModelAttributes::DataType format,
	           DataModelAttributes::BitsPerPixel bpp, int dataBits);
	virtual ~DataModel ();
	virtual DataModel* clone () const;
	virtual DataModel::TileSize defaultTileSize () const;
	virtual bool isCompatibleTileSize (DataModel::TileSize size) const;
	virtual bool isCompatibleDataSize ( DataModelAttributes::BitsPerPixel dataSize ) const;
	virtual DataModelAttributes::BitsPerPixel bitsPerPixel () const;
	virtual int bitsUsedPerPixel () const;
	virtual DataModelAttributes::DataModelType dataModelType () const;
	virtual DataModelAttributes::PixelType pixelType () const;
	virtual DataModelAttributes::DataType dataType () const;
	virtual DataModelAttributes::BitFields bitFields () const;
	virtual DataModelAttributes::ChannelOrder channelOrder() const;
	virtual bool operator==(const DataModel& dm) const;
	virtual bool operator!=(const DataModel& dm) const;
protected:
	DataModel (DataModelAttributes::DataModelType dmt, DataModelAttributes::DataType format,
	           DataModelAttributes::BitsPerPixel bpp );
	DataModel (DataModelAttributes::DataModelType dmt, DataModelAttributes::DataType format,
	           DataModelAttributes::BitsPerPixel bpp, int dataBits);
	DataModel& operator=(const DataModel& rhs);
	DataModel ();
	DataModelAttributes::DataModelType mDMType;
	DataModelAttributes::BitsPerPixel mPackedBits;
	DataModelAttributes::DataType mDataType;
	int mnBitsPerPixel;
	int mnDataBits;
	TileSize mDefaultTileSize;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ColorModelInterface
class NRXDBGATE_EXPORT ColorModelInterface {
public:
	virtual ~ColorModelInterface ();
	virtual bool canConvertTo (const ColorModelInterface* colorModel) const = 0;
	virtual RowProviderInterface* getModelConversionTo (
	    const ColorModelInterface* colorModel, RowProviderInterface* pInput ) const = 0;
	virtual bool canConvertFrom (const ColorModelInterface* colorModel) const = 0;
	virtual RowProviderInterface* getModelConversionFrom (
	    const ColorModelInterface* colorModel, RowProviderInterface* pInput ) const = 0;
};


namespace RgbModelAttributes
{
	enum Channels {
		k3Channels,
		k4Channels
	};

	enum Masks {
		kLowMask = 0x001F,
		kMidMask5551 = 0x03E0,
		kMidMask565 = 0x07E0,
		kHighMask5551 = 0x7C00,
		kHighMask565= 0xF800,
		kAlphaMask = 0x8000
	};
}


//////////////////////////////////////////////////////////////////////////
// Ntil:RgbModel
class NRXDBGATE_EXPORT RgbModel : public DataModel, public ColorModelInterface {
public:
	static bool isRgb(DataModelAttributes::DataModelType dmt);
	static RowProviderInterface* convertToRgba (RowProviderInterface* pPipe);
public:
	RgbModel ();
	RgbModel (RgbModelAttributes::Channels channels, DataModelAttributes::ChannelOrder order);
	RgbModel (int dataBits);
	virtual ~RgbModel ();
	virtual DataModel* clone () const;
	virtual DataModelAttributes::DataModelType dataModelType () const;
	virtual DataModelAttributes::PixelType pixelType () const;
	virtual bool canConvertTo (const ColorModelInterface* colorModel) const;
	virtual RowProviderInterface* getModelConversionTo (
	    const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;
	virtual bool canConvertFrom (const ColorModelInterface* colorModel) const;
	virtual RowProviderInterface* getModelConversionFrom (
	    const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;
	DataModelAttributes::ChannelOrder channelOrder() const;
protected:
	RgbModel (DataModelAttributes::DataModelType dmt,
	          DataModelAttributes::BitsPerPixel bpp );
	RgbModel (DataModelAttributes::DataModelType dmt,
	          DataModelAttributes::BitsPerPixel bpp, int nBitsUsedPerPixel );
	DataModelAttributes::ChannelOrder mOrder;
};


//////////////////////////////////////////////////////////////////////////
// Ntil:RgbGrayModel
class NRXDBGATE_EXPORT RgbGrayModel : public RgbModel {
public:
	RgbGrayModel ();
	RgbGrayModel (DataModelAttributes::DataModelType dm, DataModelAttributes::BitsPerPixel bpp);
	virtual ~RgbGrayModel ();
	virtual DataModel* clone () const;
	virtual DataModelAttributes::DataModelType dataModelType () const;
	virtual DataModelAttributes::PixelType pixelType () const;
	virtual bool canConvertTo (const ColorModelInterface* colorModel) const;
	virtual RowProviderInterface* getModelConversionTo (
	    const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;
	virtual bool canConvertFrom (const ColorModelInterface* colorModel) const;
	virtual RowProviderInterface* getModelConversionFrom (
	    const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;
	bool isTransparent ( Data8 intensity ) const;
	void setTransparent ( Data8 intensity ) const;
	bool isOpaque (Data8 intensity) const;
	void setOpaque (Data8 intensity) const;
	Data8 alpha ( Data8 intensity ) const;
	void setAlpha ( Data8 intensity, Data8 alpha ) const;
protected:
	mutable Data8 maAlphas[256];
};

//////////////////////////////////////////////////////////////////////////
// Ntil:BitonalModel
class NRXDBGATE_EXPORT BitonalModel : public RgbGrayModel {
public:
	BitonalModel ();
	virtual ~BitonalModel ();
	virtual DataModel* clone () const;
	DataModelAttributes::DataModelType dataModelType () const;
	virtual DataModelAttributes::PixelType pixelType () const;
	virtual bool canConvertTo (const ColorModelInterface* colorModel) const;
	virtual RowProviderInterface* getModelConversionTo (
	    const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;
	virtual bool canConvertFrom (const ColorModelInterface* colorModel) const;
	virtual RowProviderInterface* getModelConversionFrom (
	    const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:Offset
class NRXDBGATE_EXPORT Offset {
public:
	Int32 x;
	Int32 y;
	Offset ();
	Offset ( Int32 nX, Int32 nY );
	~Offset ();
	const Offset& set( Int32 x, Int32 y);
	Offset& operator=( const Offset& rhs );
	Offset operator+( Int32 nOffset ) const;
	Offset& operator+=( Int32 nOffset );
	Offset operator-( Int32 nOffset ) const;
	Offset& operator-=( Int32 nOffset );
	Offset operator*( Int32 nValue ) const;
	Offset& operator*=( Int32 nValue );
	Offset operator+( const Offset& rhs ) const;
	Offset& operator+=( const Offset& rhs );
	Offset operator-( const Offset& rhs ) const;
	Offset& operator-=( const Offset& rhs );
	bool operator==( const Offset& rhs ) const;
	bool operator!=( const Offset& rhs ) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:Size
class NRXDBGATE_EXPORT Size {
public:
	Int32 width;
	Int32 height;
	Size ();
	Size (Int32 width, Int32 height);
	Size ( const Size& rhs );
	~Size ();
	bool operator <= (const Size& rhs) const;
	bool operator >= (const Size& rhs) const;
	bool operator == (const Size& rhs) const;
	bool operator != (const Size& rhs) const;
	const Size& operator = (const Size& rhs);
	const Size& set( Int32 nWidth, Int32 nHeight );
	const Size& grow (Int32 width, Int32 height);
	const Size& grow (Int32 toEach);
	const Size& shrink (Int32 width, Int32 height);
	const Size& shrink (Int32 eachBy);
};
//////////////////////////////////////////////////////////////////////////
// Ntil:Point2d

class NRXDBGATE_EXPORT Point2d {
public:
	double x;
	double y;
public:
	Point2d ();
	Point2d ( int x, int  y );
	Point2d ( double x, double y );
	~Point2d ();
	const Point2d& set ( int x, int  y );
	const Point2d& set ( double x, double y );
	Point2d& transformBy (const Matrix2d& leftSide);
	double distance( const Point2d& ipPoint ) const;
	Vector2d operator-(const Point2d& rhs) const;
	Point2d operator+(const Vector2d& rhs) const;
	Point2d& operator+=(const Vector2d& rhs);
	bool operator==(const Point2d& rhs) const;
	bool operator!=(const Point2d& rhs) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:BoundingBox
class NRXDBGATE_EXPORT BoundingBox {
public:
	BoundingBox ();
	BoundingBox (Offset origin, Size size);
	BoundingBox (Offset origin, Offset extent);
	BoundingBox (int nPoints, const Offset* aOffsets);
	~BoundingBox ();
	void set (Offset offset, Size size);
	void set (Offset origin, Offset extent);
	void set (int nPoints, const Offset* aOffsets);
	void expandToInclude (Offset offset);
	void expandToInclude (int nPoints, const Offset* aOffsets);
	void getExtents (Offset& origin, Offset& extent) const;
	Size size () const;
	Offset origin () const;
	bool inBounds (const Offset& offset) const;
	bool inBounds ( int x, int y ) const;
	Offset clipToBounds (const Offset& offset) const;
	bool contains( const BoundingBox& box ) const;
	bool intersects ( const BoundingBox& bbOther ) const;
	bool getIntersection (const BoundingBox& bbOther,
	                      BoundingBox& bbIntersection ) const;
	bool getIntersection(int nPoints, const Point2d* aPolygon,
	                     BoundingBox& bbIntersection ) const;
	void getUnion ( const BoundingBox& bbOther, BoundingBox& bbUnion ) const;
private:
	Offset mOrigin;
	Offset mExtent;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:DataBuffer
class NRXDBGATE_EXPORT DataBuffer {
public:
	typedef Byte* DataPtr;
public:
	DataBuffer ();
	DataBuffer ( int nBytes );
	DataBuffer ( const DataBuffer& other );
	virtual ~DataBuffer ();
	virtual int numBytes () const;
	virtual  unsigned char* dataPtr ();
	virtual  const unsigned char* dataPtr() const;
	virtual void setSize (int nBytes);
	virtual DataBuffer& operator= (const DataBuffer& rhs);
protected:
	int mnBufferBytes;
	DataPtr mpBuffer;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:DataStreamInterface
class NRXDBGATE_EXPORT DataStreamInterface {
public:
	enum StreamMode    {
		kClosed,
		kForRead,
		kForWrite
	};
public:
	virtual ~DataStreamInterface ();
	virtual void read (int nBytes, unsigned char* pBytes, int& nRead) = 0;
	virtual bool write (int nBytes, const unsigned char* cpBytes) = 0;
	virtual bool open(StreamMode mode) = 0;
	virtual bool reset() = 0;
	virtual void close () = 0;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:SeekableDataStreamInterface
class NRXDBGATE_EXPORT SeekableDataStreamInterface : public Ntil::DataStreamInterface {
public:
	enum SeekBase {
		kFromStart,
		kFromEnd,
		kFromCurrent
	};
public:
	virtual ~SeekableDataStreamInterface();
	virtual Int32 seek ( Int32 nOffset, SeekBase from ) = 0;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecPropertyInterface
class NRXDBGATE_EXPORT FormatCodecPropertyInterface {
public:
	enum PropertyIdentifier {
		kIdCustom = 0,
		kSimpleType,
		 kCompression,
		kDensity,
		kDataOrganization,
		kAssociation,
		kTransparency,
		kCorrelation,
		kColor,
		kMultispectralReferenceName,
		kMultispectralBandName,
		kMultispectralBucket,
		kLatLon,
		kPoint,
		kSampleFormat,
		kVoidData,
		kCorrelationSet,
		kChannelOrder
	};
	enum PropertyDataType {
		kCustom = 0,
		kVoid,
		kBoolean,
		kInteger,
		kDouble,
		kString,
		kInclusiveSet,
		kExclusiveSet,
		kDate,
		kClass
	};
	enum PropertyUsage
	{
		kUsageUnknown,
		kReadOnly,
		kReadWrite,
		kWriteOnly
	};
	enum PropertyLevel
	{
		kLevelUnknown,
		kLevelFrame,
		kLevelAssociation,
		kLevelFile
	};
	virtual ~FormatCodecPropertyInterface ();
	virtual FormatCodecPropertyInterface* clone () const = 0;
	virtual PropertyIdentifier getIdentifier () const;
	virtual PropertyDataType getDataType () const;
	virtual bool isRequired () const;
	virtual bool isContextSensitive () const;
	virtual const StringBuffer& getDescription () const;
	virtual const StringBuffer& getName () const;
	virtual PropertyUsage getUsage() const;
	virtual PropertyLevel getLevel() const;
protected:
	FormatCodecPropertyInterface ();
	FormatCodecPropertyInterface (const FormatCodecPropertyInterface& from);
	PropertyIdentifier mId;
	PropertyDataType mType;
	bool mbRequired;
	bool mbContextSensitive;
	StringBuffer msbName;
	StringBuffer msbDescription;
	PropertyUsage mUsage;
	PropertyLevel mLevel;
	FormatCodecPropertyInterface& operator= (const FormatCodecPropertyInterface& from);
private:
};


//////////////////////////////////////////////////////////////////////////
// Ntil:ImageFormatCodec
class NRXDBGATE_EXPORT ImageFormatCodec {
public:
	enum CodecCapability {
		kCanRead = 0x0001,
		kCanWrite = 0x0010,
		kCanReadAndWrite = 0x0011
	};
	enum FormatType {
		kStronglyTyped,
		kLooselyTyped
	};
	enum FormatOrganization {
		kSingleFile,
		kMultipleFiles
	};
	enum FormatDecodability {
		kReadable,
		kNonSupported,
		kNonReadable,
		kCorrupted
	};
	enum FormatFeature {
		kLosslessCompression,
		kLossyCompression,
		kDirectLoadable,
		kDelayLoadable,
		kMultipleFrames,
		kThumbnailFrames,
		kStreamable
	};
	enum FormatFrameType {
		kImage,
		kBand
	};
public:
	virtual ~ImageFormatCodec ();
	virtual void getLibVersionInfo (unsigned int& nLibMajor,
	                                unsigned int& nLibMinor, unsigned int& nBuild) const = 0;
	virtual void getApiVersionInfo (unsigned int& nMajor, unsigned int& nMinor) const = 0;
	virtual CodecCapability codecCapability () const = 0;
	virtual bool isValidFileName (const FileSpecifier& fs) const = 0;
	virtual FormatType getFormatDecodabilityType () const = 0;
	virtual FormatOrganization getFormatOrganization () const = 0;
	virtual FormatFrameType getFormatFrameType () const = 0;
	virtual bool isFormatFeature ( FormatFeature feature ) const = 0;
	virtual bool isSupportedProperty (
	    FormatCodecPropertyInterface::PropertyIdentifier propId,
	    StringBuffer* pCustomPropertyName = (StringBuffer*) NULL) const = 0;
	virtual int getNumExtensions () const = 0;
	virtual void getExtensionText (int nExtensionIndex,
	                               StringBuffer& sbExtension) const = 0;
	virtual void getFormatName (StringBuffer& sbFormatName) const = 0;
	virtual void getDescriptionText (StringBuffer& sbDescription) const = 0;
	virtual void getCopyrightText (StringBuffer& sbCopyright) const = 0;
	virtual FormatDecodability isDecodableFile (const FileSpecifier& fileSpecifier,
	                                            FindFileInterface* ff = (FindFileInterface*) NULL) const = 0;
	virtual bool isEncodableImage (const DataModelAttributes& allAboutImageData,
	                               Size size ) const = 0;
	virtual ReadImageFileInterface* openImage (
	    const FileSpecifier* fsThisImage) const = 0;
	virtual ReadImageFileInterface* openImage (
	    const FileSpecifier* fsThisImage, FindFileInterface& ff) const = 0;
	virtual WriteImageFileInterface* writeImage ( ) const = 0;
	virtual ReadImageFileInterface* cloneOpenImage (
	    const ReadImageFileInterface* pOpenImage ) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FileReadDescriptor
class NRXDBGATE_EXPORT FileReadDescriptor {
public:
	enum MethodType {
		kFullRead,
		kDirectRead,
		kMultipleResolution,
		kPartialLoad,
		kThumbnail,
		kStream
	};
public:
	static ImageFormatCodec::FormatDecodability findImageFileCodec(const FileSpecifier& fs,
	                                                               const ImageFormatCodec*& pIsThisCodec);
	static ImageFormatCodec::FormatDecodability isDecodableFile (const FileSpecifier& fs,
	                                                             const ImageFormatCodec* useThisCodec);
	FileReadDescriptor (const FileSpecifier& fs);
	FileReadDescriptor (const FileSpecifier& fs, FindFileInterface* pFindFile );
	FileReadDescriptor (const FileSpecifier& fs, const ImageFormatCodec* useThisCodec);
	FileReadDescriptor (const FileSpecifier& fs, const ImageFormatCodec* useThisCodec,
	                    FindFileInterface* pFindFile);
	FileReadDescriptor (DataStreamInterface* pdsStream, const ImageFormatCodec* useThisCodec);
	FileReadDescriptor (const FileReadDescriptor& copyThis);
	~FileReadDescriptor ();
	void open () const;
	void close () const;
	void getFileSpecifier (FileSpecifier& fs) const;
	const ImageFormatCodec* formatCodec () const;
	int numFrames () const;
	int selectedFrame () const;
	bool setFrame (int frame);
	FileReadDescriptor::MethodType loadMethod () const;
	void getDataSize (Size& size) const;
	Ntil::Orientation dataOrientation() const;
	void getOrientedSize (Size& size) const;
	const DataModel& dataModel () const;
	FormatCodecPropertySetIterator* newPropertySetIterator () const;
	FormatCodecPropertyInterface* getProperty ( FormatCodecPropertyInterface::PropertyIdentifier id ) const;
	FormatCodecPropertyInterface* getProperty ( StringBuffer sbPropertyName ) const;
	 RowProviderInterface* read ();
	 RowProviderInterface* scaledRead (const double& dScale, Resample::FilterTypes filterMethod);
	int numClosureSetFiles () const;
	FileSpecifier getClosureSetFilename (int nIndex) const;
private:
	FileReadDescriptorRep* mpImplementation;
	friend class Internal;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FileReadDescriptorRep
class NRXDBGATE_EXPORT FileReadDescriptorRep {
public:
	virtual void construct (const FileSpecifier& fs, FindFileInterface* pFF ) = 0;
	virtual void construct (const FileSpecifier& fs, const ImageFormatCodec* useThisCodec, FindFileInterface* pFF ) = 0;
	virtual void construct (DataStreamInterface* pdsStream, const ImageFormatCodec* useThisCodec) = 0;
	virtual void construct (FileReadDescriptorRep* pCloneRep) = 0;
	virtual void open () const = 0;
	virtual void close () const = 0;
	virtual void getFileSpecifier (FileSpecifier& fs) const = 0;
	virtual void getDataSize (Size& size) const = 0;
	virtual Ntil::Orientation dataOrientation() const = 0;
	virtual void getOrientedSize (Size& size) const = 0;
	virtual const DataModel& dataModel () const = 0;
	virtual const ImageFormatCodec* formatCodec () const = 0;
	virtual int numFrames () const = 0;
	virtual int selectedFrame () const = 0;
	virtual bool setFrame (int frame) = 0;
	virtual FileReadDescriptor::MethodType loadMethod () const = 0;
	virtual FormatCodecPropertySetIterator* newPropertySetIterator () const = 0;
	virtual FormatCodecPropertyInterface* getProperty ( FormatCodecPropertyInterface::PropertyIdentifier id ) const = 0;
	virtual FormatCodecPropertyInterface* getProperty ( StringBuffer sbPropertyName ) const = 0;
	virtual RowProviderInterface* read () = 0;
	virtual RowProviderInterface* scaledRead (const double& dScale, Resample::FilterTypes filterMethod) = 0;
	virtual int numClosureSetFiles () const = 0;
	virtual FileSpecifier getClosureSetFilename (int nIndex) const = 0;
	virtual ~FileReadDescriptorRep ();
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FileSpecifier
class NRXDBGATE_EXPORT FileSpecifier {
public:
	enum Type {
		kFilePath,
		kOther,
		kStorageProtocol
	};
public:
	FileSpecifier ( );
	FileSpecifier (const StringBuffer& sbString, Type type);
	FileSpecifier ( const FileSpecifier& x );
	virtual ~FileSpecifier ();
	virtual FileSpecifier::Type type () const;
	virtual const StringBuffer& string () const;
	virtual const FileSpecifier& operator= ( const FileSpecifier& rhs );
	virtual bool operator== ( const FileSpecifier& rhs );
	virtual bool operator!= ( const FileSpecifier& rhs );
	virtual void set (const StringBuffer& sbString, Type type);
private:
	StringBuffer msbString;
	FileSpecifier::Type mType;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FileWriteDescriptor
class NRXDBGATE_EXPORT FileWriteDescriptor {
public:
	static bool isCompatibleFormatCodec (const ImageFormatCodec* codec,
	                                     const DataModel* dataModel, Size size);
	static void getCompatibleFormatCodecs (const DataModel* cpDataModel,
	                                       const Size& size, const ImageFormatCodec**& codecs, int& numCodecs);
public:
	friend class Internal;
	FileWriteDescriptor (const ImageFormatCodec* pCodec);
	virtual ~FileWriteDescriptor ();
	const ImageFormatCodec* formatCodec () const;
	void getFileSpecifier (FileSpecifier& fs) const;
	bool setFileSpecifier (const FileSpecifier& fs);
	void setOutputStream (DataStreamInterface* pdsStream);
	void createImageFrame (const DataModel& dataModel, Size size);
	bool requiredPropertiesSet () const;
	FormatCodecPropertySetIterator* newPropertySetIterator ();
	FormatCodecPropertyInterface* getProperty (FormatCodecPropertyInterface::PropertyIdentifier id) const;
	FormatCodecPropertyInterface* getProperty (StringBuffer sbPropertyName) const;
	bool setProperty (const FormatCodecPropertyInterface* pProperty);
	bool setProperties (const FileReadDescriptor* fd);
	int writeImageFrame (RowProviderInterface* pPipe);
private:
	FileWriteDescriptorRep* mpImplementation;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FileWriteDescriptorRep
class NRXDBGATE_EXPORT FileWriteDescriptorRep {
public:
	virtual ~FileWriteDescriptorRep ();
	virtual void construct (const ImageFormatCodec* codec) = 0;
	virtual const ImageFormatCodec* formatCodec () const = 0;
	virtual void getFileSpecifier (FileSpecifier& fs) const = 0;
	virtual bool setFileSpecifier (const FileSpecifier& fs) = 0;
	virtual void setOutputStream (DataStreamInterface* pdsStream) = 0;
	virtual void createImageFrame (const DataModel& dataModel, Size size) = 0;
	virtual bool requiredPropertiesSet () const = 0;
	virtual FormatCodecPropertySetIterator* newPropertySetIterator () = 0;
	virtual FormatCodecPropertyInterface* getProperty ( FormatCodecPropertyInterface::PropertyIdentifier id ) const = 0;
	virtual FormatCodecPropertyInterface* getProperty ( StringBuffer sbPropertyName ) const = 0;
	virtual bool setProperty ( const FormatCodecPropertyInterface* pProperty ) = 0;
	virtual bool setProperties (const FileReadDescriptor* fd) = 0;
	virtual int writeImageFrame (RowProviderInterface* rowProvider) = 0;
};


//////////////////////////////////////////////////////////////////////////
// Ntil:ImageContext
class NRXDBGATE_EXPORT ImageContext {
public:
	enum Access {
		kRead,
		kWrite
	};
	enum Behavior {
		kDefaultColor,
		kException
	};
public:
	~ImageContext ();
	DataModelAttributes::PixelType getPixelType () const;
	void setOutOfBoundsBehavior ( Behavior likeThis );
	void setOutOfBoundsColor ( ImagePixel color );
	ImagePixel getPixel (Int32 x, Int32 y);
	void putPixel (Int32 x, Int32 y, ImagePixel value);
	void getRow (Int32 y, Int32 x, int nCount, void* pBuffer );
	void putRow (Int32 y, Int32 x, int nCount, void* pBuffer );
	void setRow (Int32 y, Int32 x, int nCount, ImagePixel value );
	int get1 (Int32 x, Int32 y);
	UInt8 get8 (Int32 x, Int32 y);
	UInt16 get16 (Int32 x, Int32 y);
	UInt32 get32 (Int32 x, Int32 y);
	UInt64 get64 (Int32 x, Int32 y);
	Data128 get128 (Int32 x, Int32 y);
	void put1 (Int32 x, Int32 y, int value);
	void put8 (Int32 x, Int32 y, UInt8 value);
	void put16 (Int32 x, Int32 y, UInt16 value);
	void put32 (Int32 x, Int32 y, UInt32 value);
	void put64 (Int32 x, Int32 y, UInt64 value);
	void put128 (Int32 x, Int32 y, Data128 value);
	void flush ( );
	bool getTile (int row, int col, UInt8*& pTileData);
	void releaseTile ( );
	bool putTile ( );
	bool tileHasData (int Row, int Col);
private:
	friend class Image;
	friend class Internal;
	ImageContext ( ImageContextRep* mpImplementation );
	ImageContextRep* mpImplementation;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:Image
class NRXDBGATE_EXPORT Image {
public:
	friend class Internal;
	Image ();
	Image (const Image & image);
	Image (const Size& size, const DataModel* colorspace, ImagePixel initialColor,
	       DataModel::TileSize sz = DataModel::kUnspecified);
	Image (void* pData, int nBytesInBuffer, int nBytesPerRow, const Size& size, const DataModel* pDm);
	Image (RowProviderInterface* pPipe,
	       DataModel::TileSize sz = DataModel::kUnspecified);
	Image (RowProviderInterface* pPipe, Ntil::Orientation orient,
	       DataModel::TileSize sz = DataModel::kUnspecified);
	Image (FileReadDescriptor& readDesc,
	       DataModel::TileSize sz = DataModel::kUnspecified);
	~Image ();
	const Image& operator= (const Image& image);
	const Image& operator= (RowProviderInterface* pPipe);
	bool operator== (const Image& image) const;
	bool operator!= (const Image& image) const;
	const Size& size () const;
	Size tileSize () const;
	const DataModel& dataModel () const;
	const FileReadDescriptor* fileReadDescriptor () const;
	int numTiles (int& nRows, int& nColumns) const;
	const ImagePixel& clearColor () const;
	void setDataModel ( const DataModel& dataModel );
	void setClearColor ( ImagePixel value );
	void paste (RowProviderInterface* pPipe, const Offset& at, bool bRespectTransparency = false);
	void blend (RowProviderInterface* pPipe, const Offset& at, int nAlphaValue
	    , bool bRespectTransparency = false);
	RowProviderInterface* read (const Size& size, const Offset& offset) const;
	RowProviderInterface* read (const Size& size, const Offset& offset,
	                            Ntil::Orientation orient) const;
	ImageContext* createContext (ImageContext::Access accessNeeded, int numTilesToCache = 4 );
	ImageContext* createContext (ImageContext::Access accessNeeded,
	                             const Size& size, const Offset& offset, int numTilesToCache = 4 );
	void addReactor ( ImageReactorInterface* pReactor );
	void removeReactor ( ImageReactorInterface* pReactor );
	bool disablePerTileLocking ( bool bDisable );
	void clear ();
	bool isValid () const;
	bool isModified () const;
	bool usesUserBuffer () const;
private:
	ImageRep* mImplementation;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ImageReactorInterface
class NRXDBGATE_EXPORT ImageReactorInterface {
public:
	virtual ~ImageReactorInterface();
	virtual void onModified( int row, int column );
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ImageConstructionException
class NRXDBGATE_EXPORT ImageConstructionException : public NTILException {
public:
	enum ExceptionType {
		kIncompatibleTileSize,
		kInvalidClearColor,
		kInvalidSize,
		kNonClonal,
		kUnsafeClone,
		kInsufficentStorage,
		kInvalidRowAlignment,
		kInvalidData,
		kUnSpecified
	};
public:
	ImageConstructionException (const StringBuffer& sbMessage,
	                            ExceptionType type = ImageConstructionException::kUnSpecified);
	ImageConstructionException (const ImageConstructionException& x);
	virtual ~ImageConstructionException ();
	virtual ExceptionType getExceptionType ();
private:
	ExceptionType eType;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ImageException
class NRXDBGATE_EXPORT ImageException : public NTILException {
public:
	enum ExceptionType {
		kInvalidSubRegion,
		kIncompatibleDataModel,
		kUnableToRegisterReactor,
		kInvalidBlendTarget,
		kInvalidPixelType,
		kNullConstruction,
		kUnSpecified
	};
public:
	ImageException (const StringBuffer& sbMessage,
	                ExceptionType type = ImageException::kUnSpecified);
	ImageException (const ImageException& x);
	virtual ~ImageException ();
	virtual ExceptionType getExceptionType ();
private:
	ExceptionType eType;
};


//////////////////////////////////////////////////////////////////////////
// Ntil:ImageContextException
class NRXDBGATE_EXPORT ImageContextException : public NTILException {
public:
	enum ExceptionType {
		kTileAlreadyAllocated,
		kNotOpenForWrite,
		kOutOfBounds,
		kInvalidObject,
		kUnSpecified
	};
public:
	ImageContextException (const StringBuffer& sbMessage,
	                       ExceptionType type = ImageContextException::kUnSpecified);
	ImageContextException (const ImageContextException& x);
	virtual ~ImageContextException ();
	virtual ExceptionType getExceptionType ();
private:
	ExceptionType eType;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ImageContextRep
class NRXDBGATE_EXPORT ImageContextRep {
public:
	virtual ~ImageContextRep ();
	virtual DataModelAttributes::PixelType getPixelType () const = 0;
	virtual void setOutOfBoundsBehavior ( int likeThis ) = 0;
	virtual void setOutOfBoundsColor ( ImagePixel color ) = 0;
	virtual int get1 (Int32 x, Int32 y) = 0;
	virtual UInt8 get8 (Int32 x, Int32 y) = 0;
	virtual UInt16 get16 (Int32 x, Int32 y) = 0;
	virtual UInt32 get32 (Int32 x, Int32 y) = 0;
	virtual UInt64 get64 (Int32 x, Int32 y) = 0;
	virtual Data128 get128 (Int32 x, Int32 y) = 0;
	virtual void put1 (Int32 x, Int32 y, int value) = 0;
	virtual void put8 (Int32 x, Int32 y, UInt8 value) = 0;
	virtual void put16 (Int32 x, Int32 y, UInt16 value) = 0;
	virtual void put32 (Int32 x, Int32 y, UInt32 value) = 0;
	virtual void put64 (Int32 x, Int32 y, UInt64 value) = 0;
	virtual void put128 (Int32 x, Int32 y, Data128 value) = 0;
	virtual void flush ( ) = 0;
	virtual ImagePixel getPixel (Int32 x, Int32 y) = 0;
	virtual void putPixel (Int32 x, Int32 y, ImagePixel value) = 0;
	virtual void getRow (Int32 y, Int32 x, int nCount, void* pBuffer ) = 0;
	virtual void putRow (Int32 y, Int32 x, int nCount, void* pBuffer ) = 0;
	virtual void setRow (Int32 y, Int32 x, int nCount, ImagePixel value ) = 0;
	virtual bool getTile (int row, int col, UInt8*& pTileData) = 0;
	virtual void releaseTile () = 0;
	virtual bool putTile () = 0;
	virtual bool tileHasData (int Row, int Col) = 0;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:RowProviderInterface
class NRXDBGATE_EXPORT RowProviderInterface {
public:
	virtual ~RowProviderInterface () ;
	virtual void getNextRow (DataBuffer& oneRow) = 0;
	virtual int rowsRemaining () = 0;
	virtual Size size () const = 0;
	virtual const DataModel& dataModel () const = 0;
	virtual bool hasSpanInfo () const = 0;
	virtual bool getNextSpan (int& nStart, int& nCount) = 0;
	virtual void restartSpans () = 0;
	virtual int numSpans () = 0;
	virtual int bytesPerRow () const = 0;
	virtual bool isValid () const = 0;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ImageFilter
class NRXDBGATE_EXPORT ImageFilter : public RowProviderInterface {
public:
	virtual Size size () const;
	virtual const DataModel& dataModel () const;
	virtual int bytesPerRow () const;
	virtual bool isValid () const;
	virtual bool hasSpanInfo () const;
	virtual int rowsRemaining () = 0;
	virtual void getNextRow (DataBuffer &oneRow) = 0;
	virtual bool getNextSpan (int& nStart, int& nCount);
	virtual void restartSpans ();
	virtual int numSpans ();
	virtual void convertColor ( ImagePixel& color ) const;
protected:
	ImageFilter ( );
	virtual ~ImageFilter ();
	bool connectInput (RowProviderInterface*& input );
	bool connectInput (RowProviderInterface*& input,
	                   const DataModel& dmConvertTo );
	void init ( const Size& size );
	void init ( const Size& size, const DataModel& colorspace );
	int numInputs () const;
	RowProviderInterface* input ( int nInputIndex ) const;
private:
	RowProviderInterface* mapDefault[5];
	RowProviderInterface** mapInputs;
	int mnElements;
	int mnInputs;
	DataModel* mpOutputDm;
	Size mOutputSize;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ImageFilterException
class NRXDBGATE_EXPORT ImageFilterException : public NTILException {
public:
	enum ExceptionType {
		kNotInitialized,
		kNoValidInput,
		kInvalidClearColor,
		kOverConnected,
		kAlreadyInitialized,
		kUnSpecified
	};
public:
	ImageFilterException (const StringBuffer& sbMessage,
	                      ExceptionType type = ImageFilterException::kUnSpecified);
	ImageFilterException (const ImageFilterException& x);
	virtual ~ImageFilterException ();
	virtual ExceptionType getExceptionType ();
private:
	ExceptionType eType;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ImageFormatCodecStreamingInterface
class NRXDBGATE_EXPORT ImageFormatCodecStreamingInterface {
public:
	virtual ~ImageFormatCodecStreamingInterface();
	virtual ReadImageFileInterface* openImage (DataStreamInterface* pdsStream) const = 0;
	virtual WriteImageFileInterface* writeImage (DataStreamInterface* pdsStream) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ImageRep
class NRXDBGATE_EXPORT ImageRep {
public:
	virtual ~ImageRep ();
	virtual ImageRep* construct (ImageRep*  ToClone) = 0;
	virtual ImageRep* construct (const Size& size, const DataModel* colorspace,
	                             ImagePixel clearColor, DataModel::TileSize sz) = 0;
	virtual ImageRep* construct (void* pDataBuffer, int nBytesInBuffer, int nBytesPerRow, const Size& size,
	                             const DataModel* pDm) = 0;
	virtual ImageRep* construct (RowProviderInterface* pPipe, int oriented,
	                             DataModel::TileSize sz) = 0;
	virtual ImageRep* construct (FileReadDescriptor& readDesc,
	                             DataModel::TileSize sz) = 0;
	virtual bool operator== (const ImageRep& imageRep) const = 0;
	virtual const Size& size () const = 0;
	virtual int   numTiles (int& nRows, int& nCols) const = 0;
	virtual Size  tileSize () const = 0;
	virtual const DataModel& dataModel () const = 0;
	virtual const FileReadDescriptor* fileReadDescriptor () const = 0;
	virtual const ImagePixel& clearColor () const = 0;
	virtual void setClearColor (ImagePixel clearValue)  = 0;
	virtual bool isValid () const = 0;
	virtual bool isModified () const  = 0;
	virtual bool usesUserBuffer () const = 0;
	virtual void setDataModel ( const DataModel& dataModel ) = 0;
	virtual ImageContextRep* createContext (ImageContext::Access accessMethod,
	                                        const Size& size, const Offset& offset, int numTilesToCache)  = 0;
	virtual RowProviderInterface* read (const Size& size,
	                                    const Offset& offset) const = 0;
	virtual RowProviderInterface* read (const Size& size,
	                                    const Offset& offset, int oriented) const = 0;
	virtual void clear () = 0;
	virtual void paste (RowProviderInterface* pPipe, const Offset& at,
	                    bool bRespectTransparency ) = 0;
	virtual void blend (RowProviderInterface* pPipe, const Offset& at,
	                    int nAlphaValue, bool bRespectTransparency ) = 0;
	virtual void addReactor ( ImageReactorInterface* pReactor ) = 0;
	virtual void removeReactor ( ImageReactorInterface* pReactor ) = 0;
	virtual bool disablePerTileLocking ( bool bDisable ) = 0;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:Matrix2d
class NRXDBGATE_EXPORT Matrix2d {
public:
	static Matrix2d translation(const Vector2d& vec);
	static Matrix2d rotation(double angle, const Point2d& center);
	static Matrix2d scaling(double scaleAll, const Point2d& center);
	static Matrix2d mirroring(const Point2d& pnt);
	static Matrix2d alignCoordSys(const Point2d& fromOrigin,
	                              const Vector2d& fromE0, const Vector2d& fromE1,
	                              const Point2d& toOrigin, const Vector2d& toE0, const Vector2d& toE1);
public:
	Matrix2d();
	Matrix2d(const Matrix2d& src);
	static const Matrix2d kIdentity;
	Matrix2d& setToIdentity();
	Matrix2d operator*(const Matrix2d& mat) const;
	Matrix2d& operator*=(const Matrix2d& mat);
	Matrix2d& preMultBy(const Matrix2d& leftSide);
	Matrix2d& postMultBy(const Matrix2d& rightSide);
	Matrix2d& setToProduct(const Matrix2d& mat1, const Matrix2d& mat2);
	Matrix2d& invert();
	Matrix2d inverse() const;
	bool isSingular() const;
	Matrix2d& transposeIt();
	Matrix2d transpose() const;
	bool operator== (const Matrix2d& mat) const;
	bool operator!= (const Matrix2d& mat) const;
	bool isEqualTo (const Matrix2d& mat) const;
	double scale(void);
	double det() const;
	Matrix2d& setTranslation(const Vector2d& vec);
	Vector2d translation() const;
	bool isConformal (double& scale, double& angle,
	                  bool& isMirror, Vector2d& reflex) const;
	Matrix2d& setCoordSystem(const Point2d& origin,
	                         const Vector2d& e0, const Vector2d& e1);
	void getCoordSystem(Point2d& origin,
	                    Vector2d& e0, Vector2d& e1) const;
	Matrix2d& setToTranslation(const Vector2d& vec);
	Matrix2d& setToRotation(double angle, const Point2d& center);
	Matrix2d& setToScaling(double scaleAll, const Point2d& center);
	Matrix2d& setToScaling(double scaleX, double scaleY,
	                       const Point2d& center);
	Matrix2d& setToMirroring(const Point2d& pnt);
	Matrix2d& setToAlignCoordSys(const Point2d&  fromOrigin,
	                             const Vector2d& fromE0, const Vector2d& fromE1,
	                             const Point2d&  toOrigin, const Vector2d& toE0, const Vector2d& toE1);
	double operator()(unsigned int row, unsigned int column) const;
	double& operator()(unsigned int row, unsigned int column);
	double entry[3][3];
};

//////////////////////////////////////////////////////////////////////////
// NtilFilters:PixelSelectorInterface
class NRXDBGATE_EXPORT PixelSelectorInterface {
public:
	virtual ~PixelSelectorInterface () {};
	virtual bool isSelected (Ntil::Int32 x, Ntil::Int32 y) = 0;
	virtual void setSelected (Ntil::Int32 y, Ntil::Int32 x, int nCount ) = 0;
	virtual void flush () = 0;
};

//////////////////////////////////////////////////////////////////////////
// NtilFilters:SpanProviderInterface
class NRXDBGATE_EXPORT SpanProviderInterface {
public:
	enum Mode
	{
		kInclusive,
		kExclusive
	};
public:
	virtual ~SpanProviderInterface ();
	virtual SpanProviderInterface* clone () const = 0;
	virtual Mode mode () = 0;
	virtual void begin () = 0;
	virtual void end () = 0;
	virtual bool nextRow () = 0;
	virtual int numRows () = 0;
	virtual bool getNextSpan (int& nStart, int& nCount) = 0;
	virtual int numSpans () = 0;
	virtual const Ntil::BoundingBox& bounds () const = 0;
};

////////////////////////////////////////////////////////////////////////////
//// NtilFilters:PolygonalClip
//class NRXDBGATE_EXPORT PolygonalClip : public SpanProviderInterface {
//public:
//    enum Operation
//    {
//        kClipCrop,
//        kWindow
//    };
//public:
//    PolygonalClip (int nPoints, const Ntil::Point2d* cpaPolygon, Operation op);
//    ~PolygonalClip ();
//    Operation operation () const;
//    virtual SpanProviderInterface* clone () const;
//    virtual void begin ();
//    virtual Mode mode ();
//    virtual void end ();
//    virtual bool nextRow ();
//    virtual int numRows ();
//    virtual bool getNextSpan (int& nStart, int& nCount);
//    virtual int numSpans ();
//    virtual const Ntil::BoundingBox& bounds () const;
//    NtilFiltersVersion version;
//private:
//    void preUpdateActiveEdgeTable ( int nCurrentY );
//    void postUpdateActiveEdgeTable ();
//    int roundAndClipToInt( const double& dValue ) const;
//    int mnPoints;
//    Ntil::Point2d* mpPolygon;
//    int mnRows;
//    int mnOnRow;
//    int mnSpans;
//    PolyList** mapEdgeBucketSortList;
//    PolyList* mpActiveEdgeSortList;
//    Edge* mpCurEdge;
//    Ntil::BoundingBox mBounds;
//    Operation mOp;
//    bool mbValidRegion;
//};


//////////////////////////////////////////////////////////////////////////
// Ntil:RgbPaletteModel
class NRXDBGATE_EXPORT RgbPaletteModel : public RgbModel {
public:
	RgbPaletteModel (int nPaletteEntries = 256);
	RgbPaletteModel (int nEntries, const RgbColor* colors);
	RgbPaletteModel (int nBitsUsedPerPixel, int nEntries, const RgbColor* colors);
	virtual ~RgbPaletteModel ();
	virtual DataModel* clone () const;
	virtual DataModelAttributes::DataModelType dataModelType () const;
	virtual DataModelAttributes::PixelType pixelType () const;
	virtual bool canConvertTo (const ColorModelInterface* colorModel) const;
	virtual RowProviderInterface* getModelConversionTo (
	    const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;
	virtual bool canConvertFrom (const ColorModelInterface* colorModel) const;
	virtual RowProviderInterface* getModelConversionFrom (
	    const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;
	virtual int numEntries () const;
	virtual void setEntries (int startAt, int numEntries, const RgbColor* colors);
	virtual void getEntries (int startAt, int numEntries, RgbColor* colors) const;
	bool isTransparent (int index) const;
	void setTransparent (int index) const;
	bool isOpaque (int index) const;
	void setOpaque (int index) const;
	Data8 alpha (int index) const;
	void setAlpha (int index, Data8 alpha) const;
	virtual bool operator==(const DataModel& rhs) const;
	virtual bool operator!=(const DataModel& rhs) const;
	Ntil::UInt8 nearestColorIndex (Ntil::RgbColor color ) const;
	DataModelAttributes::ChannelOrder channelOrder() const;
protected:
	RgbPaletteModel (DataModelAttributes::DataModelType dm,
	                 DataModelAttributes::BitsPerPixel bpp, int nEntries );
	mutable RgbColor maPalette[256];
	int mnEntries;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:RgbPaletteModelException
class NRXDBGATE_EXPORT RgbPaletteModelException : public NTILException {
public:
	enum ExceptionType {
		kInvalidPaletteIndex
	};
public:
	RgbPaletteModelException (const StringBuffer& sbMessage,
	                          ExceptionType eType = kInvalidPaletteIndex );
	RgbPaletteModelException (const RgbPaletteModelException& x);
	virtual ~RgbPaletteModelException ();
	virtual ExceptionType getExceptionType ();
private:
	ExceptionType eType;
};

////////////////////////////////////////////////////////////////////////////
//// NtilFilters:SpanFilter
//class NRXDBGATE_EXPORT SpanFilter : public Ntil::ImageFilter {
//public:
//    enum Operation
//    {
//        kClip,
//        kCrop
//    };
//public:
//    SpanFilter (Ntil::RowProviderInterface* pInput);
//    virtual ~SpanFilter ();
//    virtual void getNextRow (Ntil::DataBuffer& oneRow);
//    virtual int rowsRemaining ();
//    virtual bool hasSpanInfo () const;
//    virtual bool getNextSpan (int& nStart, int& nCount);
//    virtual void restartSpans ();
//    virtual int numSpans ();
//    virtual Ntil::Size size () const;
//    void appendSpanProvider ( const SpanProviderInterface& provider,
                               //        Ntil::Offset offsetFromPipeOrigin, Operation op );
//    NtilFiltersVersion version;
//private:
//    bool isActive ( int nIndex );
//    struct SpanProvider {
//        SpanProviderInterface* pProvider;
//        SpanProviderInterface::Mode mode;
//        SpanFilter::Operation op;
//        Ntil::Offset offset;
//        bool bActive;
//    };
//    struct SpanProvider* maProviderList;
//    int mnProviders;
//    int mnArrayElements;
//    struct Span
//    {
//        int nStart;
//        int nEnd;
//        struct Span* next;
//    };
//    int mnSpans;
//    int mnOnSpan;
//    int collateProviderSpans( int nProvider );
//    int collateProviderSpans( int nProvider, struct Span*& aSpans );
//    void mergeSpan ( SpanProviderInterface::Mode mode, int nSpans, struct Span* aSpans );
//    void clearToEnd ( int nEnd );
//    struct Span* newSpan ();
//    void deleteSpanList ();
//    void appendToList ( struct Span* pAppend );
//    void insertSpanIntoList (struct Span* pInsert, struct Span* pAfter);
//    void removeSpanFromList (struct Span* pRemove );
//    struct Span* mpSpanList;
//    struct Span* mpTail;
//    int mnColumns;
//    int mnRows;
//    int mnOnRow;
//    bool mbShowInactiveRows;
//    bool mbActiveProviderOnRow;
//};

//////////////////////////////////////////////////////////////////////////
// Ntil:Vector2d
class NRXDBGATE_EXPORT Vector2d {
public:
	double x;
	double y;
	Vector2d ();
	Vector2d ( double dx, double dy );
	Vector2d ( const Vector2d& x );
	virtual ~Vector2d ();
	virtual const Vector2d& set ( const Vector2d& v2d );
	virtual const Vector2d& set ( double x, double y );
	virtual Vector2d& transformBy (const Matrix2d& leftSide);
	virtual const Vector2d& rotate ( double dRads );
	virtual double length () const;
	virtual double angle () const;
	virtual double angleTo ( const Vector2d& bvTo ) const;
	virtual double ccwAngleTo ( const Vector2d& bvTo ) const;
	virtual const Vector2d& normalize();
	virtual Vector2d normal() const;
	virtual const Vector2d& negate();
	virtual Vector2d perpVector( ) const;
	virtual double dotProduct(const Vector2d& v) const;
	virtual bool isCodirectionalTo( const Vector2d& iv ) const;
	virtual bool isParallelTo ( const Vector2d& v ) const;
	virtual bool isEqualTo (const Vector2d& v) const;
	virtual Vector2d  getOrthoVector ( ) const;
	virtual Vector2d operator-() const;
	virtual Vector2d operator-(const Vector2d& rhs) const;
	virtual Vector2d& operator-=(const Vector2d& rhs);
	virtual Point2d operator-(const Point2d& rhs) const;
	virtual Point2d operator+(const Point2d& rhs) const;
	virtual Vector2d operator+(const Vector2d& rhs) const;
	virtual Vector2d& operator+=(const Vector2d& rhs);
	virtual Vector2d operator*(const double& rhs) const;
	virtual Vector2d& operator*=( const double& rhs);
	virtual Vector2d operator/(const double&rhs) const;
	virtual Vector2d& operator/=( const double& rhs);
	virtual bool operator==(const Vector2d& rhs) const;
	virtual bool operator!=(const Vector2d& rhs) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:ImageView
class NRXDBGATE_EXPORT ImageView {
public:
	enum RotationMethod {
		kInterpolated,
		kNearestNeighbor
	};
public:
	ImageView ( const Image& image, const Size& output );
	ImageView ( const Size& input, ImagePixel clearColor, const Size& output );
	~ImageView ();
	RowProviderInterface* getViewedImageData (
	    Resample::FilterTypes filter = Resample::kNearest, bool bAdaptive = false,
	    RotationMethod rotate = kInterpolated );
	RowProviderInterface* getViewedImageData (RowProviderInterface* pInput,
	                                          Resample::FilterTypes filter = Resample::kNearest, bool bAdaptive = false,
	                                          RotationMethod rotate = kInterpolated );
	const Size& output ( ) const;
	Point2d origin () const;
	double rotation ( ) const;
	Vector2d xAxis ( ) const;
	Vector2d yAxis ( ) const;
	ImagePixel fillColor () const;
	bool transparency () const;
	bool returnRawData () const;
	void setRotation ( const double& dRads );
	void setRotation ( int n90DegreeIncrements );
	void rotateBy ( const double& dRads );
	void rotateBy ( int n90DegreeIncrements );
	void setFillColor ( ImagePixel color );
	void setTransparency ( bool bTurnOn );
	void setReturnRawData ( bool bReturnRaw );
	void setSize ( const double& dXLength, const double& dYLength );
	void scaleBy ( const double& dScale );
	void moveTo ( const Point2d& origin );
	void moveBy ( const double& dPanX, const double& dPanY );
	void setByVectors (const Point2d& origin, const Vector2d& xAxis,
	                   const Vector2d& yAxis );
	void setRegionOfInterest ( const Size& size, const Offset& offset );
	bool imageInView ( Size& size, Offset& offset );
	Point2d transform ( Point2d imageOffset ) const;
	Matrix2d getTransformation () const;
	bool getInputandOrientation (Offset& origin, Size& size,
	                             Ntil::Orientation& orientation) const;
	RowProviderInterface* getViewedImageData (ImagePixel voidPixel,
	                                          Resample::FilterTypes filter = Resample::kNearest, bool bAdaptive = false,
	                                          RotationMethod rotate = kInterpolated );
	RowProviderInterface* getViewedImageData (RowProviderInterface* pInput, ImagePixel voidPixel,
	                                          Resample::FilterTypes filter = Resample::kNearest, bool bAdaptive = false,
	                                          RotationMethod rotate = kInterpolated );
private:
	RowProviderInterface* getViewedImageDataImp (const ImagePixel*, Resample::FilterTypes, bool, RotationMethod );
	RowProviderInterface* getViewedImageDataImp (RowProviderInterface*, const ImagePixel*,
	                                             Resample::FilterTypes, bool, RotationMethod );
	BoundingBox mbbRegion;
	const Image* mpImage;
	ImagePixel mFillColor;
	Point2d mOrigin;
	Vector2d mvXAxis;
	Vector2d mvYAxis;
	Size mImageSize;
	Size mOutput;
	bool mbFillColorSet;
	bool mbTransparencyOn;
	bool mbReturnRawData;
};


//////////////////////////////////////////////////////////////////////////
// Ntil:VectorUL
class NRXDBGATE_EXPORT VectorUL : public Vector2d {
public:
	VectorUL ();
	VectorUL ( double dx, double dy );
	VectorUL ( const Vector2d& x );
	virtual ~VectorUL ();
	virtual const Vector2d& rotate ( double dRads );
	virtual Vector2d perpVector( ) const;
	virtual double angle () const;
	virtual double ccwAngleTo ( const Vector2d& bvTo ) const;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecAssociation
class NRXDBGATE_EXPORT FormatCodecAssociation : public FormatCodecPropertyInterface {
public:
	enum AssociationType {
		kThumbnail,
		kPage,
		kTransparencyMask,
		kOther,
		kDisplayAbove,
		kSpatialLink
	};
public:
	virtual ~FormatCodecAssociation ();
	virtual FormatCodecPropertyInterface* clone () const;
	virtual AssociationType getType () const;
	virtual void setType ( AssociationType type );
	virtual int associatedTo () const;
	virtual void setAssociatedFrameIndex ( int nFrameIndex );
protected:
	FormatCodecAssociation (AssociationType type, int nFrameIndex);
protected:
	AssociationType mAType;
	int mnFrameIndex;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecBooleanProperty
class NRXDBGATE_EXPORT FormatCodecBooleanProperty : public FormatCodecPropertyInterface {
public:
	FormatCodecBooleanProperty(){}; // !!!
	FormatCodecBooleanProperty (bool bDefault);
	virtual ~FormatCodecBooleanProperty ();
	virtual FormatCodecPropertyInterface* clone () const;
	bool getDefaultValue (bool& bDefault) const;
	void setValue (bool bState);
	void getValue (bool& bState) const;
protected:
	bool mbDefault;
	bool mbValue;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecColorProperty
class NRXDBGATE_EXPORT FormatCodecColorProperty : public FormatCodecPropertyInterface {
public:
	enum ColorType {
		kTransparent,
		kForeground,
		kBackground,
		kCustom
	};
public:
	FormatCodecColorProperty (ColorType type);
	virtual ~FormatCodecColorProperty ();
	virtual FormatCodecPropertyInterface* clone () const;
	virtual ImagePixel getColor ( ) const;
	virtual ColorType getType ( ) const;
	virtual bool setColor (ImagePixel color, ColorType type );
protected:
	ImagePixel mColor;
	ColorType mColorType;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecDensity
class NRXDBGATE_EXPORT FormatCodecDensity : public FormatCodecPropertyInterface {
public:
	enum Mode {
		kIntegralUnified,
		kIntegralDifferential,
		kDoubleUnified,
		kDoubleDifferential
	};
	enum Units {
		kNone,
		kCentimeters,
		kInches
	};
public:
	FormatCodecDensity (const double& dXDefault, const double& dYDefault, Units units );
	virtual ~FormatCodecDensity ();
	virtual FormatCodecPropertyInterface* clone () const = 0;
	virtual void getDefaultValue (double& dXDefault, double& dYDefault) const;
	virtual bool setValues (double dXDensity, double dYDensity);
	virtual void getValues (double& dXDensity, double& dYDensity) const;
	virtual void getDefaultUnits (Units& units) const;
	virtual void getUnits (Units& units) const;
	virtual bool setUnits (Units units);
	virtual Mode getCapabilty () const = 0;
protected:
	double mdXDefault;
	double mdYDefault;
	double mdXDensity;
	double mdYDensity;
	Units  mDefaultUnits;
	Units  mUnits;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecDoubleProperty
class NRXDBGATE_EXPORT FormatCodecDoubleProperty : public FormatCodecPropertyInterface {
public:
	virtual ~FormatCodecDoubleProperty ();
	virtual FormatCodecPropertyInterface* clone () const;
	virtual void getDefaultValue (double& dDefault) const;
	virtual bool setValue (const double& dValue);
	virtual void getValue (double& dValue ) const;
	virtual void getPropertyLimits (double& dMinimum, double& dMaximum) const;
protected:
	FormatCodecDoubleProperty(){}; // !!!
	FormatCodecDoubleProperty (const double& dMin, const double& dMax,
	                           const double& dDefault);
protected:
	double mdDefault;
	double mdMax;
	double mdMin;
	double mdValue;
};
//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecInclusivePropertySetInterface
class NRXDBGATE_EXPORT FormatCodecInclusivePropertySetInterface : public FormatCodecPropertyInterface {
public:
	virtual ~FormatCodecInclusivePropertySetInterface ();
	virtual int getNumProperties () const;
	virtual FormatCodecPropertyInterface* getProperty (int nIndex) const;
protected:
	FormatCodecInclusivePropertySetInterface (const FormatCodecInclusivePropertySetInterface& iter);
	FormatCodecInclusivePropertySetInterface ();
	FormatCodecInclusivePropertySetInterface (int nNumToAlloc);
	void setProperty (int nIndex, FormatCodecPropertyInterface* pProperty);
	void appendProperty (FormatCodecPropertyInterface* pProperty);
	FormatCodecPropertyInterface** mppProperties;
	int mnNumProperties;
	int mnArraySize;
private:
	FormatCodecInclusivePropertySetInterface& operator= (const FormatCodecInclusivePropertySetInterface& from);
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecExclusivePropertySetInterface
class NRXDBGATE_EXPORT FormatCodecExclusivePropertySetInterface : public FormatCodecInclusivePropertySetInterface {
public:
	virtual ~FormatCodecExclusivePropertySetInterface ();
	virtual int getDefaultPropertyIndex () const;
	virtual int getSelectedIndex () const;
	virtual void setSelectedIndex (int nSelectionIndex);
protected:
	FormatCodecExclusivePropertySetInterface ();
	FormatCodecExclusivePropertySetInterface (int nNumProperties);
	FormatCodecExclusivePropertySetInterface (const FormatCodecExclusivePropertySetInterface& from);
	int mnDefaultPropertyIndex;
	int mnSelectedIndex;
private:
	FormatCodecExclusivePropertySetInterface& operator= (const FormatCodecExclusivePropertySetInterface& from);
};


//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecIntProperty
class NRXDBGATE_EXPORT FormatCodecIntProperty : public FormatCodecPropertyInterface {
public:
	virtual ~FormatCodecIntProperty ();
	virtual FormatCodecPropertyInterface* clone () const;
	virtual void getDefaultValue (int& defaultValue);
	virtual int getValue () const;
	virtual bool setValue (int value);
	virtual void getPropertyLimits (int& nMinimum, int& nMaximum) const;
protected:
	FormatCodecIntProperty(){}; // !!!
	FormatCodecIntProperty (int nMinValue, int nMaxValue, int nDefaultValue);
protected:
	int mnValue;
	int mnDefaultValue;
	int mnMaxValue;
	int mnMinValue;
};


//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecPropertySetIterator
class NRXDBGATE_EXPORT FormatCodecPropertySetIterator {
public:
	virtual ~FormatCodecPropertySetIterator ();
	virtual void start ();
	virtual void step ();
	virtual bool endOfList ();
	virtual int numProperties ();
	virtual FormatCodecPropertyInterface* openProperty ();
	virtual FormatCodecPropertyInterface* openProperty (FormatCodecPropertyInterface::PropertyIdentifier identifier);
	virtual void closeProperty ();
protected:
	FormatCodecPropertySetIterator (const FormatCodecPropertySetIterator& iter);
	FormatCodecPropertySetIterator ();
	FormatCodecPropertySetIterator (int nNumToAlloc);
	void setProperty (int nIndex, const FormatCodecPropertyInterface* pProperty);
	void appendProperty (const FormatCodecPropertyInterface* pProperty);
	FormatCodecPropertyInterface** mppProperties;
	int mnNumProperties;
	int mnArraySize;
	int mnIndex;
private:
	FormatCodecPropertySetIterator& operator= (const FormatCodecPropertySetIterator& from);
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecStringProperty
class NRXDBGATE_EXPORT FormatCodecStringProperty : public FormatCodecPropertyInterface {
public:
	enum StringType {
		kSingleLine,
		kMultiLine
	};
	virtual ~FormatCodecStringProperty ();
	virtual FormatCodecPropertyInterface* clone () const;
	virtual void getDefaultValue (StringBuffer& sbDefault);
	virtual void getValue (StringBuffer& sbValue) const;
	virtual bool setValue (const StringBuffer& sbValue);
	virtual int maximumStringBytes () const;
	virtual StringType getStringType() const;
protected:
	FormatCodecStringProperty() {}; // !!!
	FormatCodecStringProperty (const StringBuffer& sbDefault, int nMaximumBytes);
protected:
	StringBuffer msbDefault;
	StringBuffer msbValue;
	int mnMaximumBytes;
	StringType    mStringType;
};

//////////////////////////////////////////////////////////////////////////
// Ntil:FormatCodecTransparency
class NRXDBGATE_EXPORT FormatCodecTransparency : public FormatCodecPropertyInterface {
public:
	enum Model {
		k32BitAlpha,
		kPaletteAlpha,
		kGrayAlpha,
		kKeyColorList
	};
public:
	virtual ~FormatCodecTransparency ();
	virtual FormatCodecPropertyInterface* clone () const;
	virtual Model getTransparencyModel ( ) const;
	virtual int numKeyColors () const;
	virtual int keyColorComponentBits () const;
	virtual bool getKeyColors (UInt8* aTransparentRgbTriplets) const;
	virtual bool getKeyColors (RgbColor* aTransparentColors) const;
	virtual bool getKeyColors (Data16* aKeyColorData) const;
	virtual bool getKeyColors (Data32* aKeyColorData) const;
	virtual bool getKeyColors (Data64* aKeyColorData) const;
	virtual void setKeyColors (int nKeyColors, const UInt8* aTransparentRgbTriplets);
	virtual void setKeyColors (int nKeyColors, const Data16* aKeyColorData);
	virtual void setKeyColors (int nKeyColors, const Data32* aKeyColorData);
	virtual void setKeyColors (int nKeyColors, const Data64* aKeyColorData);
	virtual bool getPaletteAlphas (UInt8* aAlphas) const;
	virtual void setPaletteAlphas (UInt8* aAlphas);
	virtual bool getGrayAlphas (UInt8* aAlphas) const;
	virtual void setGrayAlphas (UInt8* aAlphas);
protected:
	FormatCodecTransparency ( Model transparencyType );
	FormatCodecTransparency ( const FormatCodecTransparency& other );
protected:
	Model mModel;
	int mnColors;
	int mnBytes;
	int mnComponentBits;
	UInt8* maTransparencies;
};

//////////////////////////////////////////////////////////////////////////
// BmpFormatCodec
class NRXDBGATE_EXPORT BmpFormatCodec : public Ntil::ImageFormatCodec, public Ntil::ImageFormatCodecStreamingInterface {
public:
	BmpFormatCodec ();
	virtual ~BmpFormatCodec ();
	virtual void getLibVersionInfo (unsigned int& nLibMajor,
	                                unsigned int& nLibMinor, unsigned int& nBuild) const;
	virtual void getApiVersionInfo (unsigned int& nMajor, unsigned int& nMinor) const;
	virtual Ntil::ImageFormatCodec::CodecCapability codecCapability () const;
	virtual bool isValidFileName (const Ntil::FileSpecifier& fs) const;
	virtual Ntil::ImageFormatCodec::FormatType getFormatDecodabilityType () const;
	virtual FormatOrganization getFormatOrganization () const;
	virtual FormatFrameType getFormatFrameType () const;
	virtual bool isFormatFeature ( FormatFeature feature ) const;
	virtual bool isSupportedProperty (
	    Ntil::FormatCodecPropertyInterface::PropertyIdentifier propId,
	    Ntil::StringBuffer* pCustomPropertyName = (Ntil::StringBuffer*) NULL ) const;
	virtual int getNumExtensions () const;
	virtual void getExtensionText (int nExtensionIndex,
	                               Ntil::StringBuffer& sbExtension) const;
	virtual void getFormatName (Ntil::StringBuffer& sbFormatName) const;
	virtual void getDescriptionText (Ntil::StringBuffer& sbDescription) const;
	virtual void getCopyrightText (Ntil::StringBuffer& sbCopyright) const;
	virtual Ntil::ImageFormatCodec::FormatDecodability isDecodableFile (
	    const Ntil::FileSpecifier& fileSpecifier, Ntil::FindFileInterface* ff = NULL ) const;
	virtual bool isEncodableImage (const Ntil::DataModelAttributes& allAboutImageData,
	                               Ntil::Size size ) const;
	virtual Ntil::ReadImageFileInterface* openImage (
	    const Ntil::FileSpecifier* fsThisImage) const;
	virtual Ntil::ReadImageFileInterface* openImage (
	    const Ntil::FileSpecifier* fsThisImage, Ntil::FindFileInterface& ff) const;
	virtual Ntil::ReadImageFileInterface* openImage (Ntil::DataStreamInterface* pdsStream) const;
	virtual Ntil::WriteImageFileInterface* writeImage ( ) const;
	virtual Ntil::WriteImageFileInterface* writeImage (Ntil::DataStreamInterface* pdsStream) const;
	virtual Ntil::ReadImageFileInterface* cloneOpenImage (
	    const Ntil::ReadImageFileInterface* pOpenImage ) const;
};

//////////////////////////////////////////////////////////////////////////
// JfifFormatCodec
class NRXDBGATE_EXPORT JfifFormatCodec : public Ntil::ImageFormatCodec, public Ntil::ImageFormatCodecStreamingInterface {
public:
	enum JfifPropertyIdentifier {
		kComment,
		kProgressiveOutput
	};
public:
	JfifFormatCodec ();
	virtual ~JfifFormatCodec ();
	virtual void getLibVersionInfo (unsigned int& nLibMajor,
	                                unsigned int& nLibMinor, unsigned int& nBuild) const;
	virtual void getApiVersionInfo (unsigned int& nMajor, unsigned int& nMinor) const;
	virtual Ntil::ImageFormatCodec::CodecCapability codecCapability () const;
	virtual bool isValidFileName (const Ntil::FileSpecifier& fs) const;
	virtual Ntil::ImageFormatCodec::FormatType getFormatDecodabilityType () const;
	virtual bool isFormatFeature ( FormatFeature feature ) const;
	virtual FormatOrganization getFormatOrganization () const;
	virtual FormatFrameType getFormatFrameType () const;
	virtual bool isSupportedProperty (
	    Ntil::FormatCodecPropertyInterface::PropertyIdentifier propId,
	    Ntil::StringBuffer* pCustomPropertyName = NULL ) const;
	virtual bool getJfifPropertyName ( JfifPropertyIdentifier id, Ntil::StringBuffer& sbName  ) const;
	virtual int getNumExtensions () const;
	virtual void getExtensionText (int nExtensionIndex,
	                               Ntil::StringBuffer& sbExtension) const;
	virtual void getFormatName (Ntil::StringBuffer& sbFormatName) const;
	virtual void getDescriptionText (Ntil::StringBuffer& sbDescription) const;
	virtual void getCopyrightText (Ntil::StringBuffer& sbCopyright) const;
	virtual Ntil::ImageFormatCodec::FormatDecodability isDecodableFile (
	    const Ntil::FileSpecifier& fileSpecifier, Ntil::FindFileInterface* ff = NULL ) const;
	virtual bool isEncodableImage (const Ntil::DataModelAttributes& allAboutImageData,
	                               Ntil::Size size ) const;
	virtual Ntil::ReadImageFileInterface* openImage (
	    const Ntil::FileSpecifier* fsThisImage) const;
	virtual Ntil::ReadImageFileInterface* openImage (
	    const Ntil::FileSpecifier* fsThisImage, Ntil::FindFileInterface& ff) const;
	virtual Ntil::WriteImageFileInterface* writeImage ( ) const;
	virtual Ntil::ReadImageFileInterface* cloneOpenImage (
	    const Ntil::ReadImageFileInterface* pOpenImage ) const;
	virtual Ntil::ReadImageFileInterface* openImage (Ntil::DataStreamInterface* pdsStream) const;
	virtual Ntil::WriteImageFileInterface* writeImage (Ntil::DataStreamInterface* pdsStream) const;
};
//////////////////////////////////////////////////////////////////////////
// PngFormatCodec
class NRXDBGATE_EXPORT PngFormatCodec : public Ntil::ImageFormatCodec, public Ntil::ImageFormatCodecStreamingInterface {
public:
	enum PngIdentifier {
		kGamma,
		kScale,
		kOffset,
		kSRGB,
		kHistogram,
		kGraySignificantBits,
		kTitle,
		kAuthor,
		kDescription,
		kCopyright,
		kCreationTime,
		kSoftware,
		kDisclaimer,
		kWarning,
		kSource,
		kComment,
		kInterlace
	};
public:
	PngFormatCodec ();
	virtual ~PngFormatCodec ();
	virtual void getLibVersionInfo (unsigned int& nLibMajor,
	                                unsigned int& nLibMinor, unsigned int& nBuild) const;
	virtual void getApiVersionInfo (unsigned int& nMajor, unsigned int& nMinor) const;
	virtual Ntil::ImageFormatCodec::CodecCapability codecCapability () const;
	virtual bool isValidFileName (const Ntil::FileSpecifier& fs) const;
	virtual Ntil::ImageFormatCodec::FormatType getFormatDecodabilityType () const;
	virtual bool isFormatFeature ( FormatFeature feature ) const;
	virtual FormatOrganization getFormatOrganization () const;
	virtual FormatFrameType getFormatFrameType () const;
	virtual bool isSupportedProperty (
	    Ntil::FormatCodecPropertyInterface::PropertyIdentifier propId,
	    Ntil::StringBuffer* pCustomPropertyName = (Ntil::StringBuffer*) NULL) const;
	virtual bool isSupportedProperty ( PngFormatCodec::PngIdentifier propId ) const;
	virtual bool getPngPropertyName ( PngIdentifier id, Ntil::StringBuffer& sbName  ) const;
	virtual int getNumExtensions () const;
	virtual void getExtensionText (int nExtensionIndex,
	                               Ntil::StringBuffer& sbExtension) const;
	virtual void getFormatName (Ntil::StringBuffer& sbFormatName) const;
	virtual void getDescriptionText (Ntil::StringBuffer& sbDescription) const;
	virtual void getCopyrightText (Ntil::StringBuffer& sbCopyright) const;
	virtual Ntil::ImageFormatCodec::FormatDecodability isDecodableFile (
	    const Ntil::FileSpecifier& fileSpecifier,
	    Ntil::FindFileInterface* ff = (Ntil::FindFileInterface*) NULL) const;
	 virtual bool isEncodableImage (const Ntil::DataModelAttributes& allAboutImageData,
	                                Ntil::Size size ) const;
	virtual Ntil::ReadImageFileInterface* openImage (
	    const Ntil::FileSpecifier* fsThisImage) const;
	virtual Ntil::ReadImageFileInterface* openImage (
	    const Ntil::FileSpecifier* fsThisImage, Ntil::FindFileInterface& ff) const;
	virtual Ntil::WriteImageFileInterface* writeImage ( ) const;
	virtual Ntil::ReadImageFileInterface* cloneOpenImage (
	    const Ntil::ReadImageFileInterface* pOpenImage ) const;
	virtual Ntil::ReadImageFileInterface* openImage (Ntil::DataStreamInterface* pdsStream) const;
	virtual Ntil::WriteImageFileInterface* writeImage (Ntil::DataStreamInterface* pdsStream) const;
};

//////////////////////////////////////////////////////////////////////////
// PngCustomProperty
class NRXDBGATE_EXPORT PngCustomProperty {
public:
	virtual ~PngCustomProperty();
	PngFormatCodec::PngIdentifier pngId ( ) const;
	virtual bool writeBefore ( ) const;
	virtual bool write ( png_structp pPng, png_infop pInfo ) const = 0;
protected:
	PngFormatCodec::PngIdentifier mPngId;
	bool mbWriteBeforePLTE;
};

//////////////////////////////////////////////////////////////////////////
// PngGamma
class NRXDBGATE_EXPORT PngGamma : public Ntil::FormatCodecDoubleProperty, public PngCustomProperty {
public:
	PngGamma ();
	PngGamma (png_structp pPng, png_infop pInfo);
	~PngGamma ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	bool write ( png_structp pPng, png_infop pInfo ) const;
};

//////////////////////////////////////////////////////////////////////////
// PngScale
class NRXDBGATE_EXPORT PngScale : public Ntil::FormatCodecInclusivePropertySetInterface, public PngCustomProperty {
public:
	PngScale ();
	PngScale (png_structp pPng, png_infop pInfo);
	~PngScale ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	bool write ( png_structp pPng, png_infop pInfo ) const;
};

//////////////////////////////////////////////////////////////////////////
// PngPageOffset
class NRXDBGATE_EXPORT PngPageOffset : public Ntil::FormatCodecInclusivePropertySetInterface, public PngCustomProperty {
public:
	PngPageOffset ();
	PngPageOffset (png_structp pPng, png_infop pInfo);
	~PngPageOffset ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	bool write ( png_structp pPng, png_infop pInfo ) const;
};

//////////////////////////////////////////////////////////////////////////
// PngText
class NRXDBGATE_EXPORT PngText : public Ntil::FormatCodecStringProperty, public PngCustomProperty {
public:
	enum Keyword {
		kComment = 0,
		kTitle,
		kAuthor,
		kDescription,
		kCopyright,
		kCreationTime,
		kSoftware,
		kDisclaimer,
		kWarning,
		kSource
	};
	static const char* getString ( Keyword key );
public:
	PngText ( const Ntil::StringBuffer& sbDefault, int nMaximumBytes, Keyword key = kComment );
	~PngText ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	void getKeyword ( const char*& pKeyword ) const;
	bool write ( png_structp pPng, png_infop pInfo ) const;
protected:
	Keyword mKeyword;
	static char* mcpKeywords[10];
};

//////////////////////////////////////////////////////////////////////////
// PngSRGB
class NRXDBGATE_EXPORT PngSRGB : public Ntil::FormatCodecExclusivePropertySetInterface, public PngCustomProperty {
	enum Intent {
		kPerceptual = 0,
		kRelative,
		kSaturation,
		kAbsolute
	};
public:
	PngSRGB ( );
	PngSRGB ( png_structp pPng, png_infop pInfo );
	~PngSRGB ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	virtual void setSelectedIndex (int nSelectionIndex);
	bool write ( png_structp pPng, png_infop pInfo ) const;
private:
	Intent mSRgbIntent;
};

//////////////////////////////////////////////////////////////////////////
// PngHistogram
class NRXDBGATE_EXPORT PngHistogram : public Ntil::FormatCodecPropertyInterface, public PngCustomProperty {
public:
	PngHistogram ();
	PngHistogram (png_structp pPng, png_infop pInfo);
	~PngHistogram ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	int numEntries () const;
	void getHistogram ( int nEntries, unsigned short* pEntries ) const;
	void setHistogram ( int nEntries, unsigned short* pEntries );
	bool write ( png_structp pPng, png_infop pInfo ) const;
private:
	unsigned short* masHistogram;
	int mnEntries;
};

//////////////////////////////////////////////////////////////////////////
// PngGraySignificantBits
class NRXDBGATE_EXPORT PngGraySignificantBits : public Ntil::FormatCodecIntProperty, public PngCustomProperty {
public:
	PngGraySignificantBits ();
	PngGraySignificantBits (png_structp pPng, png_infop pInfo);
	~PngGraySignificantBits ();
	bool write ( png_structp pPng, png_infop pInfo ) const;
};

//////////////////////////////////////////////////////////////////////////
// PngCompressionType
class NRXDBGATE_EXPORT PngCompressionType : public Ntil::FormatCodecPropertyInterface {
public:
	enum Compression {
		kNone = 0,
		kLow = 1,
		kMedium = 3,
		kNormal = 6,
		kHigh = 9
	};
public:
	PngCompressionType(Compression type);
	~PngCompressionType();
	virtual Ntil::FormatCodecPropertyInterface* clone() const;
	Compression type();
private:
	Compression mCompressionType;
};

//////////////////////////////////////////////////////////////////////////
// PngCompression
class NRXDBGATE_EXPORT PngCompression : public Ntil::FormatCodecExclusivePropertySetInterface {
public:
	PngCompression(PngCompressionType::Compression type = PngCompressionType::kNormal);
	~PngCompression();
public:
	virtual Ntil::FormatCodecPropertyInterface* clone() const;
	PngCompressionType::Compression getCompressionType(int nIndex)const;
	bool selectCompression(PngCompressionType::Compression use);
	bool write(png_structp pPng, png_infop pInfo) const;
};

//////////////////////////////////////////////////////////////////////////
// PngInterlacing
class NRXDBGATE_EXPORT PngInterlacing : public Ntil::FormatCodecBooleanProperty, public PngCustomProperty {
public:
	PngInterlacing ();
	PngInterlacing (png_structp pPng, png_infop pInfo);
	~PngInterlacing ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	bool write(png_structp pPng, png_infop pInfo) const;
};
//////////////////////////////////////////////////////////////////////////
// TiffFormatCodec
class NRXDBGATE_EXPORT TiffFormatCodec : public Ntil::ImageFormatCodec, public Ntil::ImageFormatCodecStreamingInterface {
public:
	enum TiffId {
		kMember,
		kByteOrder,
		kPhotometricInterpretation,
		kArtist,
		kCopyright,
		kDateTime,
		kFillOrder,
		kGrayResponse,
		kHostComputer,
		kImageDescription,
		kScannerMake,
		kScannerModel,
		kSoftware,
		kCompressionType,
		kPrivateTag,
		kSampleRange,
		kPageInformation
	};
public:
	TiffFormatCodec (int enabledPatentedEncoding = 3);
	virtual ~TiffFormatCodec ();
	virtual void getLibVersionInfo (unsigned int& nLibMajor,
	                                unsigned int& nLibMinor, unsigned int& nBuild) const;
	virtual void getApiVersionInfo (unsigned int& nMajor, unsigned int& nMinor) const;
	virtual Ntil::ImageFormatCodec::CodecCapability codecCapability () const;
	virtual bool isValidFileName (const Ntil::FileSpecifier& fs) const;
	virtual ImageFormatCodec::FormatType getFormatDecodabilityType () const;
	virtual bool getTiffPropertyName(TiffId id, Ntil::StringBuffer& sbName) const;
	virtual bool isFormatFeature ( FormatFeature feature ) const;
	virtual FormatOrganization getFormatOrganization () const;
	virtual FormatFrameType getFormatFrameType () const;
	virtual bool isSupportedProperty (
	    Ntil::FormatCodecPropertyInterface::PropertyIdentifier propId,
	    Ntil::StringBuffer* pCustomPropertyName = (Ntil::StringBuffer*) NULL) const;
	virtual int getNumExtensions () const;
	virtual void getExtensionText (int nExtensionIndex,
	                               Ntil::StringBuffer& sbExtension) const;
	virtual void getFormatName (Ntil::StringBuffer& sbFormatName) const;
	virtual void getDescriptionText (Ntil::StringBuffer& sbDescription) const;
	virtual void getCopyrightText (Ntil::StringBuffer& sbCopyright) const;
	void getPrivateTagName(unsigned short tagID, Ntil::StringBuffer& sbName) const;
	virtual ImageFormatCodec::FormatDecodability isDecodableFile (
	    const Ntil::FileSpecifier& fileSpecifier,
	    Ntil::FindFileInterface* ff = (Ntil::FindFileInterface*) NULL) const;
	virtual bool isEncodableImage (const Ntil::DataModelAttributes& allAboutImageData,
	                               Ntil::Size size ) const;
	virtual Ntil::ReadImageFileInterface* openImage (
	    const Ntil::FileSpecifier* fsThisImage) const;
	virtual Ntil::ReadImageFileInterface* openImage (
	    const Ntil::FileSpecifier* fsThisImage, Ntil::FindFileInterface& ff) const;
	virtual Ntil::WriteImageFileInterface* writeImage () const;
	virtual Ntil::ReadImageFileInterface* cloneOpenImage (
	    const Ntil::ReadImageFileInterface* pOpenImage ) const;
	virtual Ntil::ReadImageFileInterface* openImage (
	    Ntil::DataStreamInterface* pdsStream) const;
	virtual Ntil::WriteImageFileInterface* writeImage (
	    Ntil::DataStreamInterface* pdsStream) const;
	virtual int patentedEncodingEnabled () const;
	void setPathToCsvFiles(const Ntil::StringBuffer& sbPath);
	void getPathToCsvFiles(Ntil::StringBuffer& sbPath) const;
private:
	bool mbPatentedReadEnabled;
	bool mbPatentedWriteEnabled;
	static Ntil::StringBuffer    msbCsvPath;
};


//////////////////////////////////////////////////////////////////////////
// TiffProperty
class NRXDBGATE_EXPORT TiffProperty {
public:
	virtual ~TiffProperty () {};
	virtual TiffFormatCodec::TiffId getTiffId () const { return mTiffId; }
protected:
	TiffFormatCodec::TiffId    mTiffId;
public:
	virtual bool write( struct tiff* pTIFF ) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// TiffCompressionType
class NRXDBGATE_EXPORT TiffCompressionType : public Ntil::FormatCodecPropertyInterface, public TiffProperty {
public:
	enum Compression {
		kNone = 0,
		kCCITT_RLE,
		kCCITT_RLEW,
		kCCITT_FAX3,
		kCCITT_FAX4,
		kLZW,
		kPackbits,
		kJPEG,
		kDeflate
	};
public:
	TiffCompressionType ( Compression type );
	~TiffCompressionType ( );
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	Compression type ();
	bool write ( struct tiff* pTIFF ) const;
private:
	Compression mCompressionType;
};

//////////////////////////////////////////////////////////////////////////
// TiffCompression
class NRXDBGATE_EXPORT TiffCompression : public Ntil::FormatCodecExclusivePropertySetInterface, public TiffProperty {
public:
	TiffCompression (int nBitsPerPixel, unsigned short usPhotometric, unsigned short usSamplesPerPixel
	    , TiffCompressionType::Compression selected = TiffCompressionType::kNone
	    , bool bWriting = false, bool bPatentedEncoding = false );
	~TiffCompression ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	TiffCompressionType::Compression getCompressionType (int nIndex) const;
	bool selectCompression (TiffCompressionType::Compression use);
	bool write ( struct tiff* pTIFF ) const;
};

//////////////////////////////////////////////////////////////////////////
// TiffPhotometricInterpretation
class NRXDBGATE_EXPORT TiffPhotometricInterpretation : public Ntil::FormatCodecExclusivePropertySetInterface, public TiffProperty {
public:
	enum Interpretation {
		kMinIsWhite,
		kMinIsBlack
	};
public:
	TiffPhotometricInterpretation (
	    TiffPhotometricInterpretation::Interpretation interp =
	    TiffPhotometricInterpretation::kMinIsWhite );
	~TiffPhotometricInterpretation ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	Interpretation photometricInterpretation () const;
	bool write ( struct tiff* pTIFF ) const;
};

//////////////////////////////////////////////////////////////////////////
// TiffFillOrder
class NRXDBGATE_EXPORT TiffFillOrder : public Ntil::FormatCodecExclusivePropertySetInterface, public TiffProperty {
public:
	enum Order {
		kMSBtoLSB,
		kLSBtoMSB
	};
public:
	TiffFillOrder ( TiffFillOrder::Order order = TiffFillOrder::kMSBtoLSB );
	~TiffFillOrder ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	Order fillOrder () const;
	bool write ( struct tiff* pTIFF ) const;
private:
	Order mOrder;
};

//////////////////////////////////////////////////////////////////////////
// TiffGrayResponseCurve
class NRXDBGATE_EXPORT TiffGrayResponseCurve : public Ntil::FormatCodecPropertyInterface, public TiffProperty {
public:
	TiffGrayResponseCurve ( );
	virtual ~TiffGrayResponseCurve ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	virtual int responseLevels () const;
	virtual void getResponseLevels ( float* pValues ) const;
	virtual void setResponseLevels ( int nLevels, unsigned short* pValues, int nTenthDivisor );
	virtual unsigned short tenthDivisor () const;
	virtual unsigned short* unscaledData () const;
	bool write ( struct tiff* pTIFF ) const;
private:
	unsigned short* mpScaledLevels;
	int mnLevels;
	int mnTenthScaler;
};

//////////////////////////////////////////////////////////////////////////
// TiffText
class NRXDBGATE_EXPORT TiffText : public Ntil::FormatCodecStringProperty, public TiffProperty {
public:
	TiffText (TiffFormatCodec::TiffId tiffId);
	TiffText (TiffFormatCodec::TiffId tiffId, Ntil::StringBuffer* psbText);
	~TiffText ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	bool setValue (const Ntil::StringBuffer& sbValue);
	bool write ( struct tiff* pTIFF ) const;
};

//////////////////////////////////////////////////////////////////////////
// TiffPrivateTag
class NRXDBGATE_EXPORT TiffPrivateTag : public Ntil::FormatCodecPropertyInterface, public TiffProperty {
public:
	enum TiffDataType
	{
		  kUnknown
		, kByte
		, kAscii
		, kShort
		, kLong
		, kRational
		, kSignedByte
		, kUndefined
		, kSignedShort
		, kSignedLong
		, kSignedRational
		, kFloat
		, kDouble
	};
	typedef unsigned char TTiffByte;
	typedef unsigned char TTiffAscii;
	typedef unsigned short TTiffShort;
	typedef unsigned int TTiffLong;
	typedef float TTiffRational;
	typedef char TTiffSignedByte;
	typedef unsigned char TTiffUndefined;
	typedef short TTiffSignedShort;
	typedef int TTiffSignedLong;
	typedef float TTiffSignedRational;
	typedef float TTiffFloat;
	typedef double TTiffDouble;
public:
	TiffPrivateTag(unsigned short tagId, TiffDataType dataType);
	virtual    ~TiffPrivateTag();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	virtual bool write(struct tiff* pTiff) const;
	bool isValid() const;
	TiffDataType dataType() const;
	unsigned short tagId() const;
	unsigned int numItems() const;
	unsigned int numDataBytes() const;
	bool getValue(TTiffByte* pData, const unsigned int nItems);
	bool setValue(TTiffByte const* pData, const unsigned int nItems);
	bool getValue(TTiffShort* pData, const unsigned int nItems);
	bool setValue(TTiffShort const* pData, const unsigned int nItems);
	bool getValue(TTiffLong* pData, const unsigned int nItems);
	bool setValue(TTiffLong const* pData, const unsigned int nItems);
	bool getValue(TTiffSignedByte* pData, const unsigned int nItems);
	bool setValue(TTiffSignedByte const* pData, const unsigned int nItems);
	bool getValue(TTiffSignedShort* pData, const unsigned int nItems);
	bool setValue(TTiffSignedShort const* pData, const unsigned int nItems);
	bool getValue(TTiffSignedLong* pData, const unsigned int nItems);
	bool setValue(TTiffSignedLong const* pData, const unsigned int nItems);
	bool getValue(TTiffFloat* pData, const unsigned int nItems);
	bool setValue(TTiffFloat const* pData, const unsigned int nItems);
	bool getValue(TTiffDouble* pData, const unsigned int nItems);
	bool setValue(TTiffDouble const* pData, const unsigned int nItems);
private:
	bool storeValue(void const* pData, const unsigned int numBytes);
	bool retrieveValue(void* pData, const unsigned int numBytes);
	TiffDataType mDataType;
	unsigned int mNumItems;
	void* mpTagValue;
	unsigned short mTagId;
	bool mbValid;
};

//////////////////////////////////////////////////////////////////////////
// TiffSampleRange
class NRXDBGATE_EXPORT TiffSampleRange : public Ntil::FormatCodecInclusivePropertySetInterface, public TiffProperty {
public:
	TiffSampleRange ();
	virtual ~TiffSampleRange ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	virtual void getRange (unsigned short& nMinValue, unsigned short& nMaxValue) const;
	virtual void setRange (unsigned short nMinValue, unsigned short nMaxValue);
	bool write ( struct tiff* pTIFF ) const;
};

//////////////////////////////////////////////////////////////////////////
// TiffPageInformation
class NRXDBGATE_EXPORT TiffPageInformation : public Ntil::FormatCodecInclusivePropertySetInterface, public TiffProperty {
public:
	TiffPageInformation (Ntil::StringBuffer* pDoc, Ntil::StringBuffer* pPage,
	                     int nPage, int nPages, double* pX, double* pY );
	virtual ~TiffPageInformation ();
	virtual Ntil::FormatCodecPropertyInterface* clone () const;
	virtual bool getDocumentName ( Ntil::StringBuffer& sbName ) const;
	virtual bool getPageName ( Ntil::StringBuffer& sbName ) const;
	virtual bool getPageNumber ( int& nNumber ) const;
	virtual bool getPosition ( double& dX, double& dY ) const;
private:
	bool write ( struct tiff* pTIFF ) const;
};

//////////////////////////////////////////////////////////////////////////
// NtilFormatCodecLibrary
struct NRXDBGATE_EXPORT NtilFormatCodecLibrary {
	enum AvailableFormats {
		kJfif,
		kPng,
		kTiff,
		kBmp,
		kCals,
		kSpot,
		kIg4,
		kPict,
		kRlc,
		kTarga,
		kPcx,
		kFlic,
		kGif
	};
	static int numberOfCodecs ();
	static const Ntil::FormatCodecApiVersionInterface* getFormatCodecApiVersion (int nCodec);
	static Ntil::ImageFormatCodec* loadFormatCodec ( int nCodec );
	static void unloadFormatCodec ( int nCodec );
	static Ntil::ImageFormatCodec* getFormatCodec (AvailableFormats cdc);
	static const Ntil::FormatCodecApiVersionInterface* findFormatCodecApiVersion (AvailableFormats cdc);
	static int getFormatPosition ( AvailableFormats cdc );
	static void setResourceFileName ( const Ntil::char_t* pResourceFile );
	static void setPatentedEncodingSupportEnabled ( bool bTurnOnRead, bool bTurnOnWrite );
	static void registerPropertyStringProvider(Ntil::PropertyStringProviderInterface const* pcProvider );
};

typedef enum {
  kAcGiBitonal,
  kAcGiPalette,
  kAcGiGray,
  kAcGiRGBA,
  kAcGiBGRA,
  kAcGiARGB,
  kAcGiABGR,
  kAcGiBGR,
  kAcGiRGB                              
} NcGiImageOrg;

typedef enum {
  kAcGiXLeftToRightTopFirst,
  kAcGiXLeftToRightBottomFirst,
  kAcGiXRightToLeftTopFirst,
  kAcGiXRightToLeftBottomFirst,
  kAcGiYTopToBottomLeftFirst,
  kAcGiYTopToBottomRightFirst,
  kAcGiYBottomToTopLeftFirst,
  kAcGiYBottomToTopRightFirst
} NcGiImageOrient;

typedef enum {
  kDefaultScale,                  // classic scaling scheme
  kRelativeScale,                 // relative to original image, do rotation
  kUnTransformedScale             // original pixels, unscaled, unrotated
} NcGiScaleType;

typedef enum {
  kDefaultScaleFilter,
  kNearestScaleFilter,
  kBellScaleFilter,
  kMitchellScaleFilter,
  kTriangleScaleFilter,
  kCubicScaleFilter,
  kBsplineScaleFilter,
  kLanczos3ScaleFilter
} NcGiScaleFilterType;

typedef enum {
  kDefaultRotationFilter,
  kInterpolatedRotationFilter,
  kNearestRotationFilter,
} NcGiRotationFilterType;

struct NRXDBGATE_EXPORT NcGiRequestScanLines 
{
  enum IEDitherMethod 
  {
    kIEAnyPalette,
    kCustomDithering,
    kCustomDitheringMethod
  };

  enum IEColorSystem
  {
    kBitonal,
    kCMY,
    kCMYK,
    kRGB
  };

  enum ImagePaletteType
  {
    kFromDevice,
    kFromIeWholeImage
  };

  NcGiRequestScanLines()
    : mPixelMinX          (0)
    , mPixelMinY          (0)
    , mPixelMaxX          (0)
    , mPixelMaxY          (0)
    , mpImageId           (0)
    , mImageOrg           (kAcGiBitonal)
    , mImageOrient        (kAcGiXLeftToRightTopFirst)
    , mWindowId           (0)
    , mColorDepth         (8)
    , mPaletteIncarnation (0)
    , mpPalette           (0)
    , mIsDisplay          (0)
    , mRasterRatio        (1.0)
    , mPaletteType        (kFromDevice)
    , mpDataBuffer        (0)
    , mRowWidth           (0)
    , mpBoundaryPoints    (0)
    , mnContours          (0)
    , mpCounts            (0)
    , mScalingType        (kDefaultScale)
    , mScaleFilterType    (kDefaultScaleFilter)
    , mRotationFilterType (kDefaultRotationFilter)
    , mnTotalChunks       (0)
    , mnThisChunk         (0)
  {
  }

  NRX::UInt32       mPixelMinX;             // requested pixel corners
  NRX::UInt32       mPixelMinY;
  NRX::UInt32       mPixelMaxX;
  NRX::UInt32       mPixelMaxY;
  NcGePoint2d         mLowerLeft;             // requested lower left corner
  NcGePoint2d         mUpperRight;            // requested upper right corner
  void *              mpImageId;              // image handle
  NcGiImageOrg        mImageOrg;              // enum type: palette, RGB 
  NcGiImageOrient     mImageOrient;           // enum type
  NRX::Int16        mWindowId;              // acad window id
  NRX::Int16        mColorDepth;            // bits per pixel
  union {
    NRX::Int16 mBackgroundIndex;
    NRX::Int8 mBackgroundRGB[3];
  }                   mBackgroundColor;       // current background color
  union {
    NRX::Int16 mTransparentIndex;
    NRX::Int8 mTransparentRGB[3];
  } mTransparentColor;                        // current background color
  union {
    NRX::Int16 mEntityIndex;
    NRX::Int8 mEntityRGB[3];
  }                   mEntityColor;           // bitonal image foregrnd color
  NRX::Int32        mPaletteIncarnation;    // unique palette indentifier
  NRX::Int8 *       mpPalette;              // pointer to 256 RGB triples
  NRX::Int16        mIsDisplay;             // boolean: TRUE=dsply, FALSE=hrdcpy
  double              mRasterRatio;           // raster resolution
  NcGeMatrix2d        mPixelToDc;             // source pixel-to-dc transform
  ImagePaletteType    mPaletteType;
  void *              mpDataBuffer;
  NRX::Int32        mRowWidth;
  NRX::Int32        mNumRows;
  NRX::Int32 const *mpBoundaryPoints;        // array of x,y pairs
  NRX::UInt32       mnContours;              // number of contours 
  NRX::Int32 const *mpCounts;                // pt count for each contour
  NcGiScaleType          mScalingType;
  NcGiScaleFilterType    mScaleFilterType;
  NcGiRotationFilterType mRotationFilterType;
  short                  mnTotalChunks;       // how many chunks will be requested
  short                  mnThisChunk;         // 1 based count of chunks
};

} // namespace Ntil
#endif