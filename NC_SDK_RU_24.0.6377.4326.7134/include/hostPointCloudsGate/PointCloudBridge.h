#ifndef __POINTCLOUDBRIDGE_H__
#define __POINTCLOUDBRIDGE_H__

#include "Exports.h"
#include "PointCloudDefs.h"
#include "PointCloudInsertion.h"
#include "PointCloudDefinition.h"

namespace NPC_API
{
	class PointCloudBridge
	{
	public:
		//@}
		//! point clouds import/creation
		//@{ 
		_EXPORT static bool createPointCloudFromFile(NcApDocument* _pDocument,
																								 const NCHAR* _fileName,
																								 NcDbObjectIdArray& _CreatedClouds,
																								 bool _bProgress = false);

		_EXPORT static bool createPointCloudsFromFiles(NcApDocument* _pDocument,
			std::vector<CStringW> _fileNames,
			NcDbObjectIdArray& _CreatedClouds,
			bool _bProgress = false);


		typedef enum : int {
			_LAS = 0x01,
			_laz = 0x02,
			_bin = 0x03,
			_ptx = 0x04,
			_pts = 0x05,
			_pcd = 0x06,
			_txt = 0x07,
			_xyz = 0x08,
			_xyb = 0x09,
			_ply = 0x10,
			_e57 = 0x11,
			_rcs = 0x12,
			_rcp = 0x13,
			_fbx = 0x14,
			_3ds = 0x15,
		} _FileDataType;
		_EXPORT static bool createPointCloudsFromFilesInMemory(NcApDocument* _pDocument,
																												 std::vector<unsigned __int64> _nByteSize,
																												 std::vector<BYTE*> _pFileDataVec,
																												 std::vector<_FileDataType> _FileType,
																												 NcDbObjectIdArray& _CreatedClouds,
																												 bool _bProgress = false);

		struct _EXPORT _PointCloudData
		{
			_CompositeIndexType	_nPointsCount;
			_Point3d*						_pXYZ;
			_RGBType*		        _pRGB;
			_SourceIDType*		 _pSource;
			_IntencityType*    _pIntencity;

			_PointCloudData()
				: _nPointsCount(0)
				, _pXYZ(NULL)
				, _pIntencity(NULL)
				, _pRGB(NULL)
				, _pSource(NULL)
			{}
		};
		_EXPORT static bool createPointCloudFromMemory(NcApDocument*		_pDocument,
										 															 unsigned					_nChunksCount,
																								   _PointCloudData*	_DataChunks,
																									 NcDbObjectId&    _CreatedCloud,
																									 bool							_bProgress = false);

		_EXPORT static bool savePointCloudAsFile(const NcDbObjectIdArray& aObjIds,
																						 _FileDataType _FileType,
																						 const NCHAR* _Name,
																						 const NCHAR* _filePath,
																						 bool _bViewport = false,
																						 bool _bProgress = false);
		//@}
		//! point clouds access
		//@{ 
		_EXPORT static bool HasPointClouds(NcApDocument* pDoc = nullptr);
		_EXPORT static bool AllPointClouds(NcDbObjectIdArray& aObjIds, NcApDocument* pDoc = nullptr);
		_EXPORT static bool AllVisiblePointClouds(NcDbObjectIdArray& aObjIds, NcApDocument* pDoc = nullptr);
		_EXPORT static bool PointCloudSingleSelect(NcDbObjectId& Id, NcApDocument* pDoc = nullptr);
		_EXPORT static bool PointCloudsMultiSelect(NcDbObjectIdArray& aObjIds, NcApDocument* pDoc = nullptr, bool bForceSelect = false);
		//@}
		//! utillity
		//@{ 
		_EXPORT static bool isPointCloudInsertion(NcDbObjectId Id);
		_EXPORT static bool isPointCloudInsertion(NcDbEntity* _pEntity);
		_EXPORT static PointCloudInsertion asPointCloudInsertion(NcDbObjectId Id, NcDb::OpenMode _mode = NcDb::kForRead);// throws PointCloudException;
		_EXPORT static PointCloudInsertion asPointCloudInsertion(NcDbEntity* _pEntity, NcDb::OpenMode _mode = NcDb::kForRead);// throws PointCloudException;
		_EXPORT static bool isPointCloudDefinition(NcDbObjectId Id);
		_EXPORT static bool isPointCloudDefinition(NcDbObject* _pObject);
		_EXPORT static PointCloudDefinition asPointCloudDefinition(NcDbObjectId Id, NcDb::OpenMode _mode = NcDb::kForRead);// throws PointCloudException;
		_EXPORT static PointCloudDefinition asPointCloudDefinition(NcDbObject* _pObject, NcDb::OpenMode _mode = NcDb::kForRead);// throws PointCloudException;
	};

} //PintCloudAPI

#endif