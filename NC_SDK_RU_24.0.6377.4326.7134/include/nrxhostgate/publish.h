#pragma once
#include "nrxhostgate_impexp.h"

class NcNameValuePair;
class NcDMMEPlotProperties;
//class NcDMMStringVec;
class NcDMMSheetReactorInfo;
class NcDMMXMLAttribute;
class Nc3dDwfNavTreeNode;
class NcDMMReactor;

typedef NcArray<NcNameValuePair> NcNameValuePairVec;
typedef const wchar_t * PCWIDESTR;
typedef wchar_t * PWIDESTR;

typedef void (__cdecl *NCGLOBADDDMMREACTOR)(NcDMMReactor * pReactor);
typedef void (__cdecl *NCGLOBREMOVEDMMREACTOR)(NcDMMReactor * pReactor);


//////////////////////////////////////////////////////////////////////////
// NcDMMNode
class NRXHOSTGATE_EXPORT NcDMMNode {
public:
	NcDMMNode()
	: m_nodeNumber(0),
	  m_nodeName(NULL)
	{
	}
	NcDMMNode(int number, wchar_t * name)
	{
		m_nodeNumber = number;
		if (NULL != name) {
			size_t nSize = ::wcslen(name) + 1;
			m_nodeName = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_nodeName, nSize, name);
			assert(err == 0);
		} else
			m_nodeName = NULL;
	}
	NcDMMNode(const NcDMMNode &src)
	: m_nodeName(NULL)
	{
		*this = src;
	}
	~NcDMMNode()
	{
		if (NULL != m_nodeName)
			delete [] m_nodeName;
	}
	int nodeNumber() const {return m_nodeNumber;};
	void SetNodeNumber(int number) {m_nodeNumber = number;};
	const wchar_t * nodeName() const {return m_nodeName;};
	void SetNodeName(const wchar_t * name)
	{
		if (NULL != m_nodeName) {
			delete [] m_nodeName;
			m_nodeName = NULL;
		}
		if (NULL != name) {
			size_t nSize = ::wcslen(name) + 1;
			m_nodeName = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_nodeName, nSize, name);
			assert(err == 0);
		} else
			m_nodeName = NULL;
	}
	NcDMMNode & operator= (const NcDMMNode &src)
	{
		if (this == &src)
			return *this;
		SetNodeNumber(src.m_nodeNumber);
		SetNodeName(src.m_nodeName);
		return *this;
	}
private:
	int m_nodeNumber;
	wchar_t * m_nodeName;
};

//////////////////////////////////////////////////////////////////////////
// NcDMMWideString
class NRXHOSTGATE_EXPORT NcDMMWideString {
public:
	NcDMMWideString();
	NcDMMWideString(const NcDMMWideString& ws);
	NcDMMWideString(PCWIDESTR pwsz);
	virtual ~NcDMMWideString();
	const NcDMMWideString& operator= (const NcDMMWideString& ws);
	const NcDMMWideString& operator= (PCWIDESTR pwsz);
	operator PCWIDESTR() const;
	void   Empty();
	bool   IsEmpty() const;
	unsigned GetLength() const;
	const NcDMMWideString& operator+= (NcDMMWideString ws);
	friend NcDMMWideString operator+
		(const NcDMMWideString& wsLeft, wchar_t wch);
	friend NcDMMWideString operator+
		(wchar_t wch, const NcDMMWideString& wsRight);
	friend NcDMMWideString operator+
		(const NcDMMWideString& wsLeft, const NcDMMWideString& wsRight);
private:
	void Alloc(size_t iLen);
	void Alloc(PCWIDESTR pwsz,size_t iLen);
	void Alloc(PCWIDESTR pwsz);
	static void Release(PWIDESTR pwsz);
	void Release();
	void MoveChars(int iStartOffset,PCWIDESTR pwsz,size_t iChars);
	PWIDESTR  m_pData;
	unsigned  m_iLength;
};

typedef NcArray<NcDMMWideString> NcDMMStringVec;



//////////////////////////////////////////////////////////////////////////
// NcDMMEntityReactorInfo
class NRXHOSTGATE_EXPORT NcDMMEntityReactorInfo {
public:
	virtual bool isCancelled()    const = 0;
	virtual const wchar_t * UniqueEntityId() = 0;
	virtual NcDbEntity* entity()             const = 0;
	virtual NcDbObjectId effectiveBlockLayerId()  const = 0;
	virtual bool GetCurrentEntityNode(NcDMMNode & node, NcDbObjectIdArray objIds) const = 0;
	virtual int GetNextAvailableNodeId() const = 0;
	virtual bool GetEntityNode(NcDbObjectId id, NcDbObjectIdArray objIds,
	                           int & nodeId) const = 0;
	virtual const NcDMMNode * GetNode(int nodeId) const = 0;
	virtual NcPlPlotLogger * GetPlotLogger() = 0;
	virtual bool SetCurrentNode(int nodeId, NcDbObjectIdArray objIds) = 0;
	virtual bool SetNodeName(int nodeNumber, const wchar_t *name) = 0;
	virtual bool AddProperties(const NcDMMEPlotProperties * props) = 0;
	virtual bool AddPropertiesIds(NcDMMStringVec * IdVec, NcDMMNode & node) = 0;
	virtual void flush()      = 0;
	virtual void cancelTheJob()        = 0;
	virtual bool AddNodeToMap(NcDbObjectId Id, NcDbObjectIdArray objIds, int nodeId) = 0;
	virtual bool add3DDwfProperty(const wchar_t *category, const wchar_t *name, const wchar_t *value) = 0;
	virtual bool add3DDwfAttribute(const wchar_t *category, const wchar_t *name,
	                               const wchar_t *ns, const wchar_t *nsUrl,
	                               const wchar_t *attName, const wchar_t *attVal) = 0;
	virtual const NcArray<long>& getGraphicIDs() = 0;
	virtual const NcDbObjectIdArray& getEntityBlockRefPath() = 0;
public:
	~NcDMMEntityReactorInfo() {};
protected:
	NcDMMEntityReactorInfo() {};
};

//////////////////////////////////////////////////////////////////////////
// NcDMMReactor
class NRXHOSTGATE_EXPORT NcDMMReactor : public NcRxObject {
public:
	virtual void OnBeginSheet(NcDMMSheetReactorInfo * pInfo);
	virtual void OnBeginEntity(NcDMMEntityReactorInfo * pInfo);
	virtual void OnEndEntity(NcDMMEntityReactorInfo * pInfo);
	virtual void OnEndSheet(NcDMMSheetReactorInfo * pInfo);
	virtual ~NcDMMReactor() {};
protected:
	NcDMMReactor() {};
};

//////////////////////////////////////////////////////////////////////////
// NcDMMXMLAttribute
class NRXHOSTGATE_EXPORT NcDMMXMLAttribute {
public:
	NcDMMXMLAttribute()
	{
		setNull();
	}
	NcDMMXMLAttribute(const wchar_t *ns, const wchar_t *nsUrl,
	                  const wchar_t *attName, const wchar_t *attValue)
	{
		setNull();
		SetNamespace(ns);
		SetNamespaceUrl(nsUrl);
		SetAttributeName(attName);
		SetAttributeValue(attValue);
	}
	const NcDMMXMLAttribute& operator= (const NcDMMXMLAttribute& src)
	{
		if (this != &src)
		{
			setNull();
			SetNamespace(src.GetNamespace());
			SetNamespaceUrl(src.GetNamespaceUrl());
			SetAttributeName(src.GetAttributeName());
			SetAttributeValue(src.GetAttributeValue());
		}
		return *this;
	}
	NcDMMXMLAttribute(const NcDMMXMLAttribute& src)
	{
		*this = src;
	}
	~NcDMMXMLAttribute()
	{
		if (NULL != m_namespace)
			delete [] m_namespace;
		if (NULL != m_namespaceUrl)
			delete [] m_namespaceUrl;
		if (NULL != m_attributeName)
			delete [] m_attributeName;
		if (NULL != m_attributeValue)
			delete [] m_attributeValue;
	}
	void SetNamespace(const wchar_t* ns)
	{
		delete [] m_namespace;
		if (NULL != ns) {
			size_t nSize = ::wcslen(ns) + 1;
			m_namespace = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_namespace, nSize, ns);
			assert(err == 0);
		} else {
			m_namespace = NULL;
		}
	}
	const wchar_t* GetNamespace() const
	{
		return m_namespace;
	}
	void SetNamespaceUrl(const wchar_t* nsUrl)
	{
		delete [] m_namespaceUrl;
		if (NULL != nsUrl) {
			size_t nSize = ::wcslen(nsUrl) + 1;
			m_namespaceUrl = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_namespaceUrl, nSize, nsUrl);
			assert(err == 0);
		} else {
			m_namespaceUrl = NULL;
		}
	}
	const wchar_t* GetNamespaceUrl() const
	{
		return m_namespaceUrl;
	}
	void SetAttributeName(const wchar_t* attName)
	{
		delete [] m_attributeName;
		if (NULL != attName) {
			size_t nSize = ::wcslen(attName) + 1;
			m_attributeName = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_attributeName, nSize, attName);
			assert(err == 0);
		} else {
			m_attributeName = NULL;
		}
	}
	const wchar_t* GetAttributeName() const
	{
		return m_attributeName;
	}
	void SetAttributeValue(const wchar_t* attValue)
	{
		delete [] m_attributeValue;
		if (NULL != attValue) {
			size_t nSize = ::wcslen(attValue) + 1;
			m_attributeValue = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_attributeValue, nSize, attValue);
			assert(err == 0);
		} else {
			m_attributeValue = NULL;
		}
	}
	const wchar_t* GetAttributeValue() const
	{
		return m_attributeValue;
	}
private:
	wchar_t * m_namespace;
	wchar_t * m_namespaceUrl;
	wchar_t * m_attributeName;
	wchar_t * m_attributeValue;
	void setNull()
	{
		m_namespace = NULL;
		m_namespaceUrl = NULL;
		m_attributeName = NULL;
		m_attributeValue = NULL;
	}
};

typedef NcArray<NcDMMXMLAttribute> NcDMMXMLAttributeVec;

//////////////////////////////////////////////////////////////////////////
// NcDMMEPlotProperty
class NRXHOSTGATE_EXPORT NcDMMEPlotProperty {
public:
	NcDMMEPlotProperty()
	{
		m_name = NULL;
		m_value = NULL;
		m_type = NULL;
		m_units = NULL;
		m_category = NULL;
	}
	NcDMMEPlotProperty(const wchar_t *name, const wchar_t * value)
	{
		if (NULL != name) {
			size_t nSize = ::wcslen(name) + 1;
			m_name = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_name, nSize, name);
			assert(err == 0);
		} else {
			m_name = NULL;
		}
		if (NULL != value) {
			size_t nSize = ::wcslen(value) + 1;
			m_value = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_value, nSize, value);
			assert(err == 0);
		} else {
			m_value = NULL;
		}
		m_category = NULL;
		m_type = NULL;
		m_units = NULL;
	}
	NcDMMEPlotProperty(const NcDMMEPlotProperty &src)
	{
		m_name = NULL;
		m_value = NULL;
		m_type = NULL;
		m_units = NULL;
		m_category = NULL;
		{*this = src;}
	}
	~NcDMMEPlotProperty()
	{
		if (NULL != m_name)
			delete [] m_name;
		if (NULL != m_value)
			delete [] m_value;
		if (NULL != m_category)
			delete [] m_category;
		if (NULL != m_type)
			delete [] m_type;
		if (NULL != m_units)
			delete [] m_units;
	}
	void SetType(const wchar_t * type)
	{
		if (m_type) {
			delete [] m_type;
			m_type = NULL;
		}
		if (NULL != type) {
			size_t nSize = ::wcslen(type) + 1;
			m_type = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_type, nSize, type);
			assert(err == 0);
		} else {
			m_type = NULL;
		}
	}
	const wchar_t * GetType() const
	{
		return m_type;
	}
	void SetUnits(const wchar_t * units)
	{
		if (m_units) {
			delete [] m_units;
			m_units = NULL;
		}
		if (NULL != units) {
			size_t nSize = ::wcslen(units) + 1;
			m_units = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_units, nSize, units);
			assert(err == 0);
		} else {
			m_units = NULL;
		}
	}
	const wchar_t * GetUnits() const
	{
		return m_units;
	}
	void SetCategory(const wchar_t * category)
	{
		if (m_category) {
			delete [] m_category;
			m_category = NULL;
		}
		if (NULL != category) {
			size_t nSize = ::wcslen(category) + 1;
			m_category = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_category, nSize, category);
			assert(err == 0);
		} else {
			m_category = NULL;
		}
	}
	const wchar_t * GetCategory() const
	{
		return m_category;
	}
	void SetName(const wchar_t * name)
	{
		if (m_name) {
			delete [] m_name;
			m_name = NULL;
		}
		if (NULL != name) {
			size_t nSize = ::wcslen(name) + 1;
			m_name = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_name, nSize, name);
			assert(err == 0);
		} else {
			m_name = NULL;
		}
	}
	const wchar_t * GetName() const
	{
		return m_name;
	}
	void SetValue(const wchar_t * value)
	{
		if (m_value) {
			delete [] m_value;
			m_value = NULL;
		}
		if (NULL != value) {
			size_t nSize = ::wcslen(value) + 1;
			m_value = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_value, nSize, value);
			assert(err == 0);
		} else {
			m_value = NULL;
		}
	}
	const wchar_t * GetValue() const
	{
		return m_value;
	}
	NcDMMEPlotProperty& operator= (const NcDMMEPlotProperty& src)
	{
		if (this == &src)
			return *this;
		SetName(src.m_name);
		SetValue(src.m_value);
		SetType(src.m_type);
		SetUnits(src.m_units);
		SetCategory(src.m_category);
		m_XMLAttributes = src.m_XMLAttributes;
		return *this;
	}
	void AddXMLAttribute(const NcDMMXMLAttribute * attrib)
	{
		if(attrib)
			AddXMLAttribute(attrib->GetNamespace(),
		                    attrib->GetNamespaceUrl(),
		                    attrib->GetAttributeName(),
		                    attrib->GetAttributeValue());
	}
	void AddXMLAttribute(const wchar_t *ns, const wchar_t *nsUrl, const wchar_t *attName, const wchar_t *attValue)
	{
		if (NULL != ns && NULL != nsUrl && NULL != attName && NULL != attValue)
			m_XMLAttributes.append(NcDMMXMLAttribute(ns,nsUrl,attName,attValue));
	}
	const NcDMMXMLAttributeVec& GetXMLAttributes() const
	{
		return m_XMLAttributes;
	}
private:
	wchar_t * m_name;
	wchar_t * m_value;
	wchar_t * m_type;
	wchar_t * m_units;
	wchar_t * m_category;
	NcDMMXMLAttributeVec    m_XMLAttributes;
};

typedef NcArray<NcDMMEPlotProperty> NcDMMEPlotPropertyVec;


//////////////////////////////////////////////////////////////////////////
// NcDMMResourceInfo
class NRXHOSTGATE_EXPORT NcDMMResourceInfo {
public:
	NcDMMResourceInfo()
	: m_mime(NULL),
	  m_role(NULL),
	  m_path(NULL)
	{
	}
	NcDMMResourceInfo(const wchar_t *role, const wchar_t *mime,
	                  const wchar_t *path)
	{
		if (NULL != role) {
			size_t nSize = ::wcslen(role) + 1;
			m_role = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_role, nSize, role);
			assert(err == 0);
		} else
			m_role = NULL;
		if (NULL != mime) {
			size_t nSize = ::wcslen(mime) + 1;
			m_mime = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_mime, nSize, mime);
			assert(err == 0);
		} else
			m_mime = NULL;
		if (NULL != path) {
			size_t nSize = ::wcslen(path) + 1;
			m_path = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_path, nSize, path);
			assert(err == 0);
		} else
			m_path = NULL;
	}
	NcDMMResourceInfo(const NcDMMResourceInfo & src)
	: m_role(NULL),
	  m_mime(NULL),
	  m_path(NULL)
	{
		*this = src;
	}
	~NcDMMResourceInfo()
	{
		if (NULL != m_role)
			delete [] m_role;
		if (NULL != m_mime)
			delete [] m_mime;
		if (NULL != m_path)
			delete [] m_path;
	}
	void SetRole(wchar_t * role)
	{
		if (NULL != m_role) {
			delete [] m_role;
			m_role = NULL;
		}
		if (NULL != role) {
			size_t nSize = ::wcslen(role) + 1;
			m_role = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_role, nSize, role);
			assert(err == 0);
		} else
			m_role = NULL;
	}
	void SetRole(const wchar_t * role)
	{
		if (NULL != m_role) {
			delete [] m_role;
			m_role = NULL;
		}
		if (NULL != role) {
			size_t nSize = ::wcslen(role) + 1;
			m_role = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_role, nSize, role);
			assert(err == 0);
		} else
			m_role = NULL;
	}
	const wchar_t * GetRole() const {return m_role;};
	void SetMime(wchar_t * mime)
	{
		if (NULL != m_mime) {
			delete [] m_mime;
			m_mime = NULL;
		}
		if (NULL != mime) {
			size_t nSize = ::wcslen(mime) + 1;
			m_mime = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_mime, nSize, mime);
			assert(err == 0);
		} else
			m_mime = NULL;
	}
	void SetMime(const wchar_t * mime)
	{
		if (NULL != m_mime) {
			delete [] m_mime;
		}
		if (NULL != mime) {
			size_t nSize = ::wcslen(mime) + 1;
			m_mime = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_mime, nSize, mime);
			assert(err == 0);
		} else
			m_mime = NULL;
	}
	const wchar_t * GetMime() const {return m_mime;};
	void SetPath(wchar_t * path)
	{
		if (NULL != m_path) {
			delete [] m_path;
			m_path = NULL;
		}
		if (NULL != path) {
			size_t nSize = ::wcslen(path) + 1;
			m_path = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_path, nSize, path);
			assert(err == 0);
		} else
			m_path = NULL;
	}
	void SetPath(const wchar_t * path)
	{
		if (NULL != m_path) {
			delete [] m_path;
			m_path = NULL;
		}
		if (NULL != path) {
			size_t nSize = ::wcslen(path) + 1;
			m_path = new wchar_t[nSize];
			errno_t err = ::wcscpy_s(m_path, nSize, path);
			assert(err == 0);
		} else
			m_path = NULL;
	}
	const wchar_t * GetPath() const {return m_path;};
	NcDMMResourceInfo& operator= (const NcDMMResourceInfo &src)
	{
		if (this == &src)
			return *this;
		SetRole(src.m_role);
		SetMime(src.m_mime);
		SetPath(src.m_path);
		return *this;
	}
private:
	wchar_t * m_role;
	wchar_t * m_mime;
	wchar_t * m_path;
};

typedef NcArray<NcDMMResourceInfo> NcDMMResourceVec;


//////////////////////////////////////////////////////////////////////////
// NcDMMSheetReactorInfo
class NRXHOSTGATE_EXPORT NcDMMSheetReactorInfo {
public:
	enum PlotArea {
		kDisplay = 0,
		kExtents = 1,
		kLimits = 2,
		kView,
		kWindow,
		kLayout
	};
	enum PlotRotation {
		k0degrees,
		k90degrees,
		k180degrees,
		k270degrees
	};
	enum PlotMediaUnits {
		kInches,
		kMillimeters,
		kPixels
	};
	virtual NcPlPlotLogger * GetPlotLogger() = 0;
	virtual NcDbDatabase* database()      const = 0;
	virtual bool    isPlotJobCancelled()    const = 0;
	virtual void AddPageProperties(NcDMMEPlotPropertyVec props) = 0;
	virtual void AddPageResources(NcDMMResourceVec resources) = 0;
	virtual const NCHAR * UniqueLayoutId() = 0;
	virtual NcDbObjectId   plotLayoutId()           const = 0;
	virtual bool           isModelLayout()          const = 0;
	virtual PlotArea plotArea() const = 0;
	virtual PlotRotation plotRotation() const = 0;
	virtual PlotMediaUnits plotMediaUnits() const = 0;
	virtual double paperScale()                     const = 0;
	virtual double drawingScale()                   const = 0;
	virtual double originX()                        const = 0;
	virtual double originY()                        const = 0;
	virtual double plotWindowMinX()                 const = 0;
	virtual double plotWindowMinY()                 const = 0;
	virtual double plotWindowMaxX()                 const = 0;
	virtual double plotWindowMaxY()                 const = 0;
	virtual const TCHAR*  viewPlotted()             const = 0;
	virtual bool isScaleSpecified()                 const = 0;
	virtual bool areLinesHidden()                   const = 0;
	virtual bool arePlottingLineWeights()           const = 0;
	virtual bool areScalingLineWeights()            const = 0;
	virtual double displayMinX()                    const = 0;
	virtual double displayMinY()                    const = 0;
	virtual double displayMaxX()                    const = 0;
	virtual double displayMaxY()                    const = 0;
	virtual double layoutMarginMinX()               const = 0;
	virtual double layoutMarginMinY()               const = 0;
	virtual double layoutMarginMaxX()               const = 0;
	virtual double layoutMarginMaxY()               const = 0;
	virtual double printableBoundsX()               const = 0;
	virtual double printableBoundsY()               const = 0;
	virtual double maxBoundsX()                     const = 0;
	virtual double maxBoundsY()                     const = 0;
	virtual double stepsPerInch()                  const = 0;
	virtual const TCHAR* configuration()            const = 0;
	virtual const TCHAR* plotToFilePath()           const = 0;
	virtual const TCHAR* plotToFileName()           const = 0;
	virtual const TCHAR* canonicalMediaName()       const = 0;
	virtual double plotBoundsMinX()                 const = 0;
	virtual double plotBoundsMinY()                 const = 0;
	virtual double plotBoundsMaxX()                 const = 0;
	virtual double plotBoundsMaxY()                 const = 0;
	virtual double layoutBoundsMinX()               const = 0;
	virtual double layoutBoundsMinY()               const = 0;
	virtual double layoutBoundsMaxX()               const = 0;
	virtual double layoutBoundsMaxY()               const = 0;
	virtual double effectivePlotOffsetX()           const = 0;
	virtual double effectivePlotOffsetY()           const = 0;
	virtual int    effectivePlotOffsetXdevice()     const = 0;
	virtual int    effectivePlotOffsetYdevice()     const = 0;
	virtual bool    publishingTo3DDwf()     const = 0;
	virtual bool set3dDwfNavigationTreeNode(const Nc3dDwfNavTreeNode* root) = 0;
	virtual Nc3dDwfNavTreeNode* get3dDwfNavigationTreeNode() = 0;
public:
	virtual ~NcDMMSheetReactorInfo() {};
protected:
	NcDMMSheetReactorInfo() {};
};



//////////////////////////////////////////////////////////////////////////
// NcDMMEPlotProperties
class NRXHOSTGATE_EXPORT NcDMMEPlotProperties {
public:
	NcDMMEPlotProperties()
		: m_id(NULL)
	{
	}
	NcDMMEPlotProperties(const NcDMMEPlotProperties &src)
		: m_id(NULL)
	{
		*this = src;
	}
	~NcDMMEPlotProperties()
	{
		m_properties.removeAll();
		m_refs.removeAll();
		if (NULL != m_id)
			delete m_id;
	}
	void AddProperty(const NcDMMEPlotProperty * property)
	{
		if (NULL == property)
			return;
		m_properties.append(*property);
	}
	void AddProperty(wchar_t * name, wchar_t *value)
	{
		NcDMMEPlotProperty newProp(name, value);
		m_properties.append(newProp);
	}
	const NcDMMEPlotPropertyVec& GetProperties() const
	{
		return m_properties;
	}
	const NcDMMEPlotProperty * GetProperty(unsigned long index) const
	{
		if (m_properties.length() <= (int)index)
			return NULL;
		return &m_properties[index];
	}
	void NcDMMEPlotProperties::SetId(const wchar_t * id)
	{
		if (NULL != m_id)
			delete m_id;
		if (NULL != id) {
			size_t nSize = ::wcslen(id) + 1;
			m_id = new wchar_t[nSize];
			errno_t err =::wcscpy_s(m_id, nSize, id);
			assert(err == 0);
		} else
			m_id = NULL;
	}
	const wchar_t * GetId() const
	{
		return m_id;
	}
	void NcDMMEPlotProperties::SetRefs(const NcDMMStringVec& refs)
	{
		m_refs.removeAll();
		for (int i = 0; i < refs.length(); i++)
			m_refs.append(refs.at(i));
	}
	const NcDMMStringVec * NcDMMEPlotProperties::GetRefs() const
	{
		return &m_refs;
	}
	NcDMMEPlotProperties& operator= (const NcDMMEPlotProperties &src)
	{
		if (this == &src)
			return *this;
		m_properties.removeAll();
		for (int i = 0; i < src.m_properties.length(); i++)
			m_properties.append(src.m_properties.at(i));
		SetId(src.m_id);
		SetRefs(src.m_refs);
		return *this;
	}
private:
	NcDMMEPlotPropertyVec m_properties;
	wchar_t * m_id;
	NcDMMStringVec m_refs;
};



//////////////////////////////////////////////////////////////////////////
// NcNameValuePair
class NRXHOSTGATE_EXPORT NcNameValuePair {
public:
	NcNameValuePair()
	{
		m_pName = NULL;
		m_pValue = NULL;
	};
	~NcNameValuePair()
	{
		if (NULL != m_pName)
			delete [] m_pName;
		if (NULL != m_pValue)
			delete [] m_pValue;
	};
	NcNameValuePair(const NCHAR *name, const NCHAR *value)
	{
		if (NULL != name) {
			size_t nSize = ::wcslen(name) + 1;
			m_pName = new NCHAR[nSize];
			errno_t err = ::wcscpy_s(m_pName, nSize, name);
			assert(err == 0);
		} else
			m_pName = NULL;
		if (NULL != value) {
			size_t nSize = ::wcslen(value) + 1;
			m_pValue = new NCHAR[nSize];
			errno_t err = ::wcscpy_s(m_pValue, nSize, value);
			assert(err == 0);
		} else
			m_pValue = NULL;
	}
	NcNameValuePair(const NcNameValuePair &src)
	: m_pName(NULL),
	  m_pValue(NULL)
	{
		*this = src;
	}
	const NCHAR * name() const {return m_pName;};
	const NCHAR * value() const {return m_pValue;};
	void setName(const NCHAR * name)
	{
		if (NULL != m_pName)
			delete [] m_pName;
		if (NULL != name) {
			size_t nSize = ::wcslen(name) + 1;
			m_pName = new NCHAR[nSize];
			errno_t err = ::wcscpy_s(m_pName, nSize, name);
			assert(err == 0);
		} else
			m_pName = NULL;
	}
	void setValue(const NCHAR * value)
	{
		if (NULL != m_pValue)
			delete [] m_pValue;
		if (NULL != value) {
			size_t nSize = ::wcslen(value) + 1;
			m_pValue = new NCHAR[nSize];
			errno_t err = ::wcscpy_s(m_pValue, nSize, value);
			assert(err == 0);
		} else
			m_pValue = NULL;
	}
	NcNameValuePair & operator= (const NcNameValuePair &src)
	{
		if (this == &src)
			return *this;
		setName(src.m_pName);
		setValue(src.m_pValue);
		return *this;
	}
private:
	NCHAR * m_pName;
	NCHAR * m_pValue;
};

//////////////////////////////////////////////////////////////////////////
// NcPublishBeforeJobInfo
class NRXHOSTGATE_EXPORT NcPublishBeforeJobInfo {
public:
	NcPublishBeforeJobInfo() {};
	virtual ~NcPublishBeforeJobInfo() {};
	virtual const NcPlDSDData * GetDSDData() = 0;
	virtual const NcNameValuePairVec
		GetPrivateData(const NCHAR * sectionName) = 0;
	virtual bool WritePrivateSection(const NCHAR * sectionName,
		const NcNameValuePairVec nameValuePairVec) = 0;
	virtual bool JobWillPublishInBackground() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcPublishBeginJobInfo
class NRXHOSTGATE_EXPORT NcPublishBeginJobInfo {
public:
	NcPublishBeginJobInfo() {};
	virtual ~NcPublishBeginJobInfo() {};
	virtual const NcPlDSDData * GetDSDData() = 0;
	virtual const NcNameValuePairVec
		GetPrivateData(const NCHAR * sectionName) = 0;
	virtual bool WritePrivateSection(const NCHAR * sectionName,
		const NcNameValuePairVec nameValuePairVec) = 0;
	virtual bool JobWillPublishInBackground() = 0;
	virtual NcPlPlotLogger * GetPlotLogger() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcPublishSheetInfo
class NRXHOSTGATE_EXPORT NcPublishSheetInfo {
public:
	NcPublishSheetInfo() {};
	virtual ~NcPublishSheetInfo() {};
	virtual const NcPlDSDEntry * GetDSDEntry() = 0;
	virtual const NCHAR * GetUniqueId() = 0;
	virtual NcPlPlotLogger * GetPlotLogger() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcPublishReactorInfo
class NRXHOSTGATE_EXPORT NcPublishReactorInfo {
public:
	NcPublishReactorInfo() {};
	virtual ~NcPublishReactorInfo() {};
	virtual const NCHAR* dwfFileName() = 0;
	virtual const NCHAR* tempDwfFileName() = 0;
	virtual const NCHAR* dwfPassword() = 0;
	virtual bool isMultiSheetDwf() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcPublishUIReactorInfo
class NRXHOSTGATE_EXPORT NcPublishUIReactorInfo {
public:
	NcPublishUIReactorInfo() {};
	virtual ~NcPublishUIReactorInfo() {};
	virtual const NcPlDSDData * GetDSDData() = 0;
	virtual const NcNameValuePairVec
		GetPrivateData(const NCHAR * sectionName) = 0;
	virtual bool WritePrivateSection(const NCHAR * sectionName,
		const NcNameValuePairVec nameValuePairVec) = 0;
	virtual bool JobWillPublishInBackground() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcPublishUIReactor
class NRXHOSTGATE_EXPORT NcPublishUIReactor : public NcRxObject {
public:
	virtual void OnInitPublishOptionsDialog(IUnknown **pUnk,
	                                        NcPublishUIReactorInfo *pInfo);
	virtual void OnInitExportOptionsDialog(IUnknown **pUnk,
	                                       NcPublishUIReactorInfo *pInfo);
	virtual void PersistenceRegistryForExportOptionsDialog(const NCHAR* lpszRegRoot,
	                                                       bool bIsReadRegistry = true);
	virtual void OnInitAutoPublishSettingsDialog(IUnknown **pUnk,
	                                             NcPublishUIReactorInfo *pInfo);
	virtual void PersistenceRegistryForAutoPublishDialog(const NCHAR* lpszRegRoot,
	                                                     bool bIsReadRegistry = true);
	virtual ~NcPublishUIReactor() {};
protected:
	NcPublishUIReactor() {};
};

//////////////////////////////////////////////////////////////////////////
// NcPublishUIReactor2
class NRXHOSTGATE_EXPORT NcPublishUIReactor2 : public NcPublishUIReactor {
public:
	virtual void PersistenceRegistryForPubishOptionsDialog(const NCHAR* lpszRegRoot,
	                                                       bool bIsReadRegistry = true) {}
	virtual ~NcPublishUIReactor2() {}
protected:
	NcPublishUIReactor2() {}
};

//////////////////////////////////////////////////////////////////////////
// NcPublishAggregationInfo
class NRXHOSTGATE_EXPORT NcPublishAggregationInfo {
public:
	NcPublishAggregationInfo() {};
	virtual ~NcPublishAggregationInfo() {};
	virtual void AddGlobalProperties(NcDMMEPlotPropertyVec props) = 0;
	virtual void AddGlobalResources(NcDMMResourceVec resources) = 0;
	virtual NcPlPlotLogger * GetPlotLogger() = 0;
	virtual const NCHAR* dwfFileName() = 0;
	virtual const NCHAR* dwfPassword() = 0;
};

//////////////////////////////////////////////////////////////////////////
// NcPublishReactor
class NRXHOSTGATE_EXPORT NcPublishReactor : public NcRxObject {
public:
	virtual void OnAboutToBeginBackgroundPublishing(NcPublishBeforeJobInfo
	    *pInfo);
	virtual void OnAboutToBeginPublishing(NcPublishBeginJobInfo *pInfo);
	virtual void OnBeginPublishingSheet(NcPublishSheetInfo *pInfo);
	virtual void OnBeginAggregation(NcPublishAggregationInfo *pInfo);
	virtual void OnAboutToEndPublishing(NcPublishReactorInfo *pInfo);
	virtual void OnAboutToMoveFile(NcPublishReactorInfo *pInfo);
	virtual void OnEndPublish(NcPublishReactorInfo *pInfo);
	virtual void OnCancelledOrFailedPublishing(NcPublishReactorInfo *pInfo);
	virtual ~NcPublishReactor() {};
protected:
	NcPublishReactor() {};
};

void NcGlobAddDMMReactor(NcDMMReactor * pReactor);
void NcGlobAddPublishReactor(NcPublishReactor *pReactor);
void NcGlobAddPublishUIReactor(NcPublishUIReactor *pReactor);
void NcGlobRemoveDMMReactor(NcDMMReactor * pReactor);
void NcGlobRemovePublishReactor(NcPublishReactor *pReactor);
void NcGlobRemovePublishUIReactor(NcPublishUIReactor *pReactor);

typedef void (__cdecl * NCGLOBADDPUBLISHREACTOR)(NcPublishReactor * pReactor);
typedef void (__cdecl * NCGLOBREMOVEPUBLISHREACTOR)(NcPublishReactor * pReactor);