#pragma once

struct IMcInObjectPainter : public IMcObject
{
	IMCS_INTERFACE_DEF_CONSTRUSTOR_4KINDOF(IMcInObjectPainter);
	IMCS_STD_METHOD_DEFINITION(IMcInObjectPainter, IMcObject);
	virtual void Init(const mcsWorkID& dc) = 0;
	virtual void AddCustom(const mcsWorkID& id, McsEntityGeometry& geometry) = 0;
	virtual void AddCustom(const mcsWorkID& id, mcsGeomEntArray& geometry) = 0;
	virtual void RemoveAll() = 0;
	virtual bool RemoveCustom(const mcsWorkID& id) = 0;
	virtual void Highlight(const mcsWorkID& id) = 0;
	virtual void Unhighlight(const mcsWorkID& id) = 0;
	virtual void UnhighlightAll() = 0;
	virtual bool GetEntitiesByPoint(
		OUT OPTIONAL mcsWorkIDArray& ids,
		IN OPTIONAL  const mcsPoint& point,
		IN OPTIONAL  bool            fSingleNearest = true,
		IN OPTIONAL  int             apertureRadius_pix = 3) = 0;
	virtual void Update() = 0;
	virtual void Disconnect() = 0;
};