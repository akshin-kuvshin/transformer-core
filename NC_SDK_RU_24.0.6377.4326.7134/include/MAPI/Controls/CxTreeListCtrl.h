#if !defined(AFX_TREELISTCTRL_H__3AD0AA0B_377B_489C_B1FD_3374DAFFEC0F__INCLUDED_)
#define AFX_TREELISTCTRL_H__3AD0AA0B_377B_489C_B1FD_3374DAFFEC0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////////////////////////
//
// TreeListCtrl.h : header file
//
/*** Пример использования: ***

	treelist.Create(WS_CHILD|WS_VISIBLE|LVS_SHOWSELALWAYS|LVS_REPORT|LVS_SINGLESEL, CRect(0,0,300,300), this, IDC_TREE_LIST);
	CxTreeListCtrl::CSelection sel;
	sel.iSelType = TL_SELECTION_CATEGORIES; // Установить режим - свойства разделенные по категориям, как окно properties в VS2005.
	sel.iCol = sel.nDefValCol = 1;			// 1 столбец - редактируемый.
	treelist.SetSelectionType(&sel);
	treelist.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 125);
	treelist.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 70);
	treelist.SetItemBorder(NULL,0,TL_BORDER_AROUND); // Установим рамку-решетку вокруг
	treelist.SetItemBorder(NULL,1,TL_BORDER_AROUND);	// всех ячеек.
	treelist.EnableDlgKey(VK_ESCAPE); // Разрешим контролу перехватывать и отрабатывать ESC,RET
	treelist.EnableDlgKey(VK_RETURN);
	//
	HTItem hCat1 = treelist.InsertItem(_T("Category1"));
	HTItem hParam = treelist.InsertItem(_T(""),hCat1);
	treelist.SetItemText(hParam, 0, _T("Param0"));
	m_listTable.SetItemEditCtrl(hParam, 1, IDC_INPLACE_EDIT);
	hParam = treelist.InsertItem(_T(""),hCat1);
	treelist.SetItemText(hParam, 0, _T("Param0"));
	m_listTable.SetItemEditCtrl(hParam, 1, IDC_INPLACE_EDIT);

******************************/

//////////////////////////////////////////////////////////////////////////////////////////////
// Include section
//

#include "assert.h"
#include <afxtempl.h>
#include <afxdtctl.h>
#include "CxEditLt.h"
#include "MechCtl.h"

class CFlatHeaderCtrl;

//////////////////////////////////////////////////////////////////////////////////////////////
// Define section
//

#define TL_NOTSELECTED	0
#define TL_SELECTED		1
#define TL_FOCUSED		2

#define TL_DEFAULT	-1

#define TL_NOIMAGE	-2
#define TL_NOCHECK	-2

//	Эти контстанты используются в следующих методах
//

// см. SetItemCheckState/GetItemCheckState
#define TL_CHECKED   1
#define TL_UNCHECKED 0

#define TL_CHECKED_DISABLED		 11
#define TL_UNCHECKED_DISABLED	 10


// см. SetItemBorder/GetItemBorder
#define TL_BORDER_NONE		0
#define TL_BORDER_LEFT		0x02
#define TL_BORDER_RIGHT		0x04
#define TL_BORDER_TOP		0x08
#define TL_BORDER_BOTTOM	0x10
#define TL_BORDER_AROUND	TL_BORDER_BOTTOM|TL_BORDER_TOP|TL_BORDER_RIGHT|TL_BORDER_LEFT

// Text format.
// for items & columns
// см. SetItemTextFormat/GetItemTextFormat
#define TL_TEXT_LEFTALIGN	DT_LEFT
#define TL_TEXT_CENTERED	DT_CENTER
#define TL_TEXT_RIGHTALIGN	DT_RIGHT

#define TL_TEXT_SIMPLE		0
#define TL_TEXT_ITALIC		0x04
#define TL_TEXT_BOLD		0x08
#define TL_TEXT_UNDERLINE	0x10
#define TL_TEXT_DISABLED	0x20

#define TL_IMAGE_PLUS		ID_IMG_EMPTY_TREE_PLUS
#define TL_IMAGE_MINUS		ID_IMG_EMPTY_TREE_MINUS
#define TL_IMAGE_EMPTY		ID_IMG_EMPTY

// Тип селекции
//
#define TL_SELECTION_NONE		0
#define TL_SELECTION_BOX		1
#define TL_SELECTION_FULLROW	2
#define TL_SELECTION_PROPERTIES	3
#define TL_SELECTION_CATEGORIES	4

typedef void* HTItem;

#define TL_ROOT		((HTItem) TVI_ROOT)
#define TL_FIRST	((HTItem) TVI_FIRST)
#define TL_LAST		((HTItem) TVI_LAST)

#define TL_PARENT		0
#define TL_PREV			1
#define TL_NEXT			2

#define TL_BEFORE		1
#define TL_AFTER		2
#define TL_FIRSTCHILD	3
#define TL_LASTCHILD	4

#define TL_LEAF			0

// см. Expand().
#define TL_EXPAND	 TVE_EXPAND	
#define TL_COLLAPSE	 TVE_COLLAPSE
#define TL_COLLAPSERESET TVE_COLLAPSERESET
#define TL_EXPANDED  TL_EXPAND
#define TL_COLLAPSED TL_COLLAPSE

//	см. SetTItemControlType/GetTItemControlType
#define	TL_READONLY					0		// значение не редактируется

#define IDC_INPLACE_EDIT			301		//для редактирования используется edit

#define IDC_INPLACE_COMBO			302		// для редактирования используется combobox

#define IDC_INPLACE_CUSTOMDIALOG	303		// справа кнопка с ... (TLNM_INPLACE_ACTION)

#define IDC_INPLACE_BUTTON			304		// Вообще говоря читый недоделаный toolbar.

// батон типа тулбара
// (делает кнопку из текущего итема, при наведении курсора мыши всплывает, 
// click - TLNM_INPLACE_ACTION).
#define IDC_INPLACE_HIGHLITEBUTTON	305

#define IDC_INPLACE_LIST			306		// выпадающий список 

#define IDC_INPLACE_EDITBTN			307		// едит с кнопкой

#define IDC_INPLACE_EDITFT			308		// едит с форматированием

#define IDC_INPLACE_EDITFT_READONLY	309		// едит с форматированием readonly

#define IDC_INPLACE_LIST_NO_SORT	310		// выпадающий список без сортировки

#define IDC_INPLACE_COMBO_NO_SORT	311		// combobox без сортировки

#define IDC_INPLACE_COLOR 315		// combobox с цветом
//#define NONE_COLOR 0xAA000000 // Отсутствиее цвета, ничего не выбрано находится в константах McColorCombo

#define IDC_INPLACE_LINETYPE 316		// combobox с типами линий

#define IDC_INPLACE_LINEWEIGHT 317		// combobox с толщинами линий

// А дальше делайте свои controlы, или создавайте имеющиеся, но с другим инитом.
#define IDC_INPLACE_USER			400

#define IDC_INPLACE_DATE_TIME		401		// DateTimeCtrl

// служебные сообщения родительскому окну
//
#define TLNM_EXPAND				WM_USER + 90
#define TLNM_COLLAPSE			WM_USER + 91

#define TLNM_CHECK				WM_USER + 92

#define TLNM_SELCHANGED			WM_USER + 93
#define TLNM_SELCHANGING		WM_USER + 94

#define TLNM_EDITPREPARE		WM_USER + 95
#define TLNM_EDITAFTER			WM_USER + 96

#define TLNM_INPLACE_NEEDINIT	WM_USER + 97
#define TLNM_INPLACE_ACTION		WM_USER + 98

#define TLNM_GETITEM			WM_USER + 100
#define TLNM_SETITEM			WM_USER + 101

#define TLNM_CONTEXTMENU		WM_USER + 102

#define TLNM_EDITBEGIN			WM_USER + 103

//martinov 16.04.2015. Сообщение посылается в случае нажатия на энтер во время редактирования.
//Пока посылается только из CInPlaceEditCtrl.
#define TLNM_PRESSED_VK_RETURN  WM_USER + 104

// for private use only(for CxTreeListCtrl)
#define TLNM_END_INPLACE_EDIT	WM_USER	+ 200

// GetItemInfo/SetItemInfo callback functions constants.
//
#define TLI_ITEM				1
#define TLI_SUBITEM				2

#define TLI_TEXT				4
#define TLI_IMAGE				8
#define	TLI_CHECKEDIMAGE		16
#define	TLI_UNCHECKEDIMAGE		32
#define	TLI_CHECKSTATE			64
#define TLI_EDITCONTROL			128
#define TLI_BORDER				256
#define TLI_TEXTCOLOR			512
#define TLI_BKCOLOR				1024
#define TLI_TEXTFORMAT			2048
#define TLI_DATA				4096
#define TLI_PADDING				8192

#define TLI_DRAWINGINFO			TLI_CHECKSTATE | TLI_IMAGE | TLI_CHECKEDIMAGE | TLI_UNCHECKEDIMAGE \
								| TLI_BORDER | TLI_TEXTCOLOR | TLI_BKCOLOR | TLI_TEXTFORMAT | TLI_PADDING

#define TLI_FULLINFO			0xffffffff

#define TL_ONITEMTREEIMAGE	0x01
#define TL_ONITEMCHECKIMAGE	0x02
#define TL_ONITEMIMAGE		0x04
#define TL_ONITEMLABEL		0x08

#define LVIR_TREEICON		16
#define LVIR_CHECK			32
#define LVIR_ITEM			64

// Структура описывающая как рисовать итем.
//
struct TLItemDrawingInfo
{
	int		iImage;
	int		iCheckedImage;
	int		iUncheckedImage;

	UINT	uiBorder;
	UINT	nFormat;

	COLORREF	crTextColor;
	COLORREF	crBkColor;

	int cxPaddingLeft;
	int cxPaddingRight;

	TLItemDrawingInfo() 
	{
		iImage          = TL_DEFAULT;
		iCheckedImage   = TL_DEFAULT;
		iUncheckedImage = TL_DEFAULT;
		uiBorder        = TL_DEFAULT;
		nFormat         = TL_DEFAULT;
		crTextColor     = TL_DEFAULT;
		crBkColor       = TL_DEFAULT;
		cxPaddingLeft   = TL_DEFAULT;
		cxPaddingRight  = TL_DEFAULT;
	}
};

// Структура описывающая собственно итем.
//
struct TLItemInfo
{
	// Item info
	CString	strText;
	int		iChecked;

	TLItemDrawingInfo	drawingInfo;
	int					iControlType;
	LPARAM    	dwData;

	TLItemInfo() {
		iChecked	  = TL_DEFAULT;
		iControlType  = TL_DEFAULT;
		dwData = 0;
	}

	TLItemInfo& operator=(const TLItemInfo &rhs)
	{
		strText = rhs.strText;
		iChecked = rhs.iChecked;
		iControlType = rhs.iControlType;
		dwData = rhs.dwData;
		drawingInfo = rhs.drawingInfo;
		return *this;
	};
};

// Для сортировки
//
struct TLItem 
{
	HTItem		hItem;
	int			iSubItem;
	UINT		mask;
	TLItemInfo	item;

	LPARAM lSortParam;
};

typedef int (__cdecl *TLCompareFunc )(const void *elem1, const void *elem2 );

struct TLSORTCB 
{
	HTItem	hItemParent;
	int		iSubItem;
    TLCompareFunc lpfnCompare;
    LPARAM	lSortParam;
};

// Структура notification message для всех сообщений.
//
struct TLNM_ITEM 
{
	NMHDR	hdr;
    HTItem	hItem;
	int		iSubItem;
	DWORD	dwNotifyData;
	UINT	mask;			// Meaningful fields of TLItemInfo item.
	TLItemInfo item;		// Итем заполняется не всегда и не полностью, поэтому надо проверять mask.

	TLNM_ITEM() {
		memset(&hdr,0,sizeof(NMHDR));
	    hItem = NULL;
		iSubItem = 0;
		dwNotifyData = 0;
		mask = 0; 
	}

	TLNM_ITEM(const TLNM_ITEM& cf) {
		this->TLNM_ITEM::TLNM_ITEM();
		*this = cf;
	}

	TLNM_ITEM& operator=(const TLNM_ITEM& rhs) 
	{
		memcpy(&hdr,&rhs.hdr,sizeof(NMHDR));
	    hItem			= rhs.hItem;
		iSubItem		= rhs.iSubItem;
		dwNotifyData	= rhs.dwNotifyData;
		mask			= rhs.mask;
		item			= rhs.item;
		return *this;
	}
};

// Класс шиблон дерева. Можно использовать и отдельно от CxTreeListCtrl.
//
#define CTree CTreeNode

template<class T>
class CTreeNode {
public:
	CTreeNode(CTreeNode* parent = NULL)
	{
		m_pParentNode = NULL; 
	};
	~CTreeNode() { 
		RemoveChildren();
	}

	//
	// Methods
	//
	CTreeNode<T>*	GetParentNode() { return m_pParentNode; }

	int GetDeep() {
		if(m_pParentNode == 0) return 0;
		return m_pParentNode->GetDeep() + 1;
	}

	CTreeNode<T>*	GetNext() 
	{  
		if(m_pParentNode == NULL) return NULL;
		return m_pParentNode->GetChildNext(this);
	}
	
	CTreeNode<T>* GetPrev() 
	{ 
		if(m_pParentNode == NULL) return NULL;
		return m_pParentNode->GetChildPrev(this);
	}
			
	CTreeNode<T>* GetChildFirst() 
	{
		if(m_lstChildren.GetCount()==0) return NULL;
		return m_lstChildren.GetHead();
	}

	CTreeNode<T>* GetChildLast() 
	{
		if(m_lstChildren.GetCount()==0) return NULL;
		return m_lstChildren.GetTail();
	}

	CTreeNode<T>* GetChildNext(CTreeNode<T> *pChild)
	{
		POSITION pos = m_lstChildren.Find(pChild);
		if(pos) {
			m_lstChildren.GetNext(pos);
			if(pos) return m_lstChildren.GetAt(pos);
		}
		return NULL;
	}

	CTreeNode<T>* GetChildPrev(CTreeNode<T> *pChild)
	{
		POSITION pos = m_lstChildren.Find(pChild);
		if(pos) {
			m_lstChildren.GetPrev(pos);
			if(pos) return m_lstChildren.GetAt(pos);
		}
		return NULL;
	}

	BOOL AttachChildFirst(CTreeNode<T>* child)
	{
		m_lstChildren.AddHead(child);
		child->m_pParentNode = this;
		return TRUE;
	}

	BOOL AttachChildLast(CTreeNode<T>* child)
	{
		m_lstChildren.AddTail(child);
		child->m_pParentNode = this;
		return TRUE;
	}

	BOOL AttachChild(CTreeNode<T>* child, CTreeNode<T>* position,BOOL fInsertAfter = TRUE) 
	{
		POSITION pos = m_lstChildren.Find(position);
		if(pos) {
			if(fInsertAfter) m_lstChildren.InsertAfter(pos,child);
			else m_lstChildren.InsertBefore(pos,child);
			child->m_pParentNode = this;
			return TRUE;
		}
		return FALSE;
	}

	BOOL ReplaceChildAtPosition(POSITION pos,CTreeNode<T>* child)
	{
		m_lstChildren.SetAt(pos,child);
		return TRUE;
	}

	BOOL DetachChild(CTreeNode<T>* child) 
	{
		POSITION pos = m_lstChildren.Find(child);
		if(pos) {
			m_lstChildren.RemoveAt(pos);
			return TRUE;
		}
		return FALSE;
	}

	void DetachChildren()
	{
		m_lstChildren.RemoveAll();
	}

	BOOL RemoveChild(CTreeNode<T>* child) 
	{
		POSITION pos = m_lstChildren.Find(child);
		if(pos) {
			m_lstChildren.RemoveAt(pos);
			delete child;
			return TRUE;
		}
		return FALSE;
	}

	void RemoveChildren()
	{
		POSITION pos = m_lstChildren.GetHeadPosition();
		for (int i=0;i < m_lstChildren.GetCount();i++)
		{
		   delete m_lstChildren.GetNext(pos);
		}
	   m_lstChildren.RemoveAll();
	}

	int GetChildrenCount() { return (int)m_lstChildren.GetCount(); }

	POSITION GetFirstChildPosition() { return m_lstChildren.GetHeadPosition(); }
	POSITION GetLastChildPosition() { return m_lstChildren.GetTailPosition(); }
	CTreeNode<T>* GetChildAtPosition(POSITION position) { return m_lstChildren.GetAt(position); }
	CTreeNode<T>* GetNextChildPos(POSITION &rPosition)	{ return m_lstChildren.GetNext(rPosition); }
	CTreeNode<T>* GetPrevChildPos(POSITION &rPosition)	{ return m_lstChildren.GetPrev(rPosition); }

	typedef void (*TREELOOK_FUNC)(CTreeNode<T>*, UINT_PTR dwAppData);
	void LookOver(TREELOOK_FUNC func, UINT_PTR dwAppData)
	{
		func(this,dwAppData);
		POSITION pos = GetFirstChildPosition();
		while(pos) 
		{
			CTreeNode<T>* pNode = GetNextChildPos(pos);
			pNode->LookOver(func,dwAppData);
		};
	};

public:
	T   m_data;
	
//
// Data
//
protected:
	CTreeNode<T>*	   m_pParentNode;
	CTypedPtrList<CPtrList, CTreeNode<T>*> m_lstChildren;
};

class CInPlaceCtrl;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CxTreeListCtrl window
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// 

class MECHCTL_API CxTreeListCtrl : public CListCtrl
{
// Construction
public:
	CxTreeListCtrl();

public:
//	Attributes

public:
//
	struct CSelection
	{
		CSelection()
		{
			iSelType = TL_SELECTION_NONE;
			iBoxColor = -1;
			iBoxPenWidth = 1;
			iBoxArea = LVIR_LABEL;
			nDefValCol = 0;
			bSelectOnMouseMove = FALSE;

			iRow = -1;
			iCol = -1;
			iHotRow = -1;
			iHotCol = -1;
		};

		int iSelType;			// Тип селекции
								// TL_SELECTION_PROPERTIES
								// TL_SELECTION_FULLROW
								// TL_SELECTION_CATEGORIES

		int iRow;				// Строка выделенная по умолчанию.
		int iCol;				// Столбец выделенный по умолчанию.

		int iHotRow;			// Строка над которой нах-ся курсор мыши.
		int iHotCol;			// Столбец над которой нах-ся курсор мыши.
		
		COLORREF	iBoxColor;	// Цвет п/у селекции.
		COLORREF	iBoxPenWidth;	// Толщина пера п/у селекции.
		int			iBoxArea;	// LVIS_ICON/LVIS_LABEL/LVIS_BOUNDS выделять (текст, текст + icon,...)
		int			nDefValCol;	// Редактиреумый столбец(для TL_SELECTION_PROPERTIES)
		BOOL	bSelectOnMouseMove; // Селектировать за курсором мыши.
	};

	// Тип селекции
	//
	// TL_SELECTION_NONE		- нет селекции.
	// TL_SELECTION_PROPERTIES
	// TL_SELECTION_FULLROW		- целиком столбец(как в ListCtrl)
	// TL_SELECTION_BOX			- properties (один столбец редактируется).
	// TL_SELECTION_CATEGORIES	- столбцы дерева(не листья) выделяются как кнопка и рисууются целиком как один итем
	//
	BOOL SetSelectionType(int iSelType = TL_SELECTION_FULLROW);
	BOOL SetSelectionType(CSelection *sel);
	int GetSelectionType(CSelection *sel = NULL);
	void SetSelectionBGcolor(COLORREF clBG);
	
	BOOL SetImageList(CImageList *pImageList) 
	{
		if(CListCtrl::SetImageList(pImageList, LVSIL_SMALL) &&
			CListCtrl::SetImageList(pImageList, LVSIL_STATE))	return TRUE;
		return FALSE;
	}

	// Для заголовка /////////////////////////////////////////////////////////////////////
	//
	struct COLUMNEX
	{
		BOOL bFixed;
	};


	// Вставляет колонку
	int		InsertColumn( int nCol, LPCTSTR lpszText, int nFormat = LVCFMT_LEFT, int nWidth = -1, int nImage = TL_NOIMAGE, LPARAM lParam = NULL, LPCTSTR strTooltip = NULL);
	// см. также: DeleteColumn
	BOOL	DeleteColumn(int nCol);

	// Устанавливает картинку колонки
	BOOL SetColumnImage(int nCol, int nImage);
	// Возвращает картинку колонки
	int  GetColumnImage(int nCol);

	// Устанавливает текст колонки
	CString GetColumnName(int iCol);
	// Возвращает текст колонки
	BOOL SetColumnName(int iCol, LPCTSTR strName);

	// Устанавливает данные, связанные с колонкой
	BOOL SetColumnData(int nCol, LPARAM lParam);
	// Возвращает данные, связанные с колонкой
	BOOL GetColumnData(int nCol, LPARAM& lParam);

	// Возвращает число колонок
	int GetColumnCount();

	int GetTreeColumn() { return m_nTreeColumn; }
	BOOL SetTreeColumn(int nCol, BOOL bMovableCol = TRUE) 
	{ 
		m_nTreeColumn = nCol; 
		m_bMovableTreeColumn = bMovableCol;
		return TRUE; 		
	};
	void ShowTreeLines(BOOL bShow = TRUE) { m_bShowTreeLines = bShow; }

	// Для итемов дерева
	// Вoзвращает предыдущее значение attr.m_fSameAs.

	// Вставляет строку до, после, как потомок hTargetNode.
	// Возвращает вставленный Item.
	HTItem InsertItem(HTItem hTargetItem, UINT insertMode, UINT uiCollapseStatus = TL_LEAF, DWORD_PTR dwData = 0);
	HTItem InsertItem(LPCTSTR lpszItem, HTItem hParent = TVI_ROOT,HTItem hInsertAfter = TVI_LAST);
	//см. также: DeleteItem, DeleteTree

	// Удаляет строку
	BOOL DeleteItem(HTItem hItem);
	//см. также: InsertItem, DeleteTree
	BOOL DeleteAllChilds(HTItem hItem);
	// Deletes all items in a tree view control. 
	BOOL DeleteAllItems( );

	// Возвращает Item до, после, предка, первого,последнего потомка.
	HTItem GetItem(HTItem hTargetItem, UINT uiLocation);

	// Возвращает HTItem элемента в itemIndex строке ListCtrl'а
	// см. GetVisibleCount() - текущее кол-во строк ListCtrl'а.
	HTItem GetItem(int itemIndex) 
	{ 
		if(itemIndex>=0 && itemIndex<m_aDisplayedItems.GetSize()) return m_aDisplayedItems[itemIndex]; 
		return NULL;
	}

	// Returns nonzero if the specified item has child items. 
	BOOL ItemHasChildren( HTItem hItem );

	// Navigation
	//
	// Retrieves the child of a specified tree view item.
	HTItem GetChildItem( HTItem hItem )
	{
		return GetItem(hItem,TL_FIRSTCHILD);
	}

	// Retrieves the next sibling of the specified tree view item. 
	HTItem GetNextSiblingItem( HTItem hItem ) 
	{
		return GetItem(hItem,TL_NEXT);
	}

	// Retrieves the previous sibling of the specified tree view item. 
	HTItem GetPrevSiblingItem( HTItem hItem ) {
		return GetItem(hItem,TL_PREV);
	}

	// Retrieves the parent of the specified tree view item. 
	HTItem GetParentItem( HTItem hItem )
	{
		return GetItem(hItem,TL_PARENT);
	}

	// Retrieves the first visible item of the specified tree view item. 
	HTItem GetFirstVisibleItem()
	{
		if(GetVisibleCount()) return GetItem(0);
		return NULL;
	}

	// Retrieves the next visible item of the specified tree view item. 
	HTItem GetNextVisibleItem( HTItem hItem )
	{
		int iRow = FindItem(hItem);
		if(iRow>=0 && iRow+1<GetVisibleCount()) return GetItem(iRow+1);
		else return NULL;
	}
	
	// Retrieves the previous visible item of the specified tree view item. 
	HTItem GetPrevVisibleItem( HTItem hItem )
	{
		int iRow = FindItem(hItem);
		if(--iRow>=0) return GetItem(iRow);
		else return NULL;
	}

	// Retrieves the number of visible tree items associated with a tree view control. 
	int GetVisibleCount() { return GetItemCount(); };

	// Retrieves the root of the specified tree view item.
	HTItem GetRootItem( ) { return &m_root; };

	int GetChildrenCount(HTItem hParentItem);

	//	возвращает уровень вложенности для элементов, начиная с нуля для корневых элементов
	int GetDeep(HTItem hTItem);

	//Устанавливает данные для строки
	BOOL SetItemData(HTItem hItem, UINT_PTR dwData);
	//см. также: GetItemData

	//Возвращает данные для строки.
	UINT_PTR GetItemData(HTItem hItem);
	//см. также: SetItemData

	// Retrieves the currently selected tree view item.
	HTItem	GetSelectedItem();
	int		GetSelectedColumn();
	BOOL	GetSelectedItem(HTItem &hItem, int& nCol);

	//выделяет указанную строку
	//выделяет указанную ячейку в строке
	// if hItem == NULL => ResetSelection
	BOOL SelectItem(HTItem hItem, int nCol = -1, BOOL bResetOldSelection = TRUE, BOOL bEditPrepare = TRUE, BOOL bSetFocus = TRUE);
	BOOL SelectAll();
	virtual BOOL OnSelChanged(HTItem hItem, int iSubItem);

	//Узел раскрыт
	BOOL IsExpanded(HTItem hItem) { return GetStatus(hItem) == TL_EXPANDED; };
	BOOL IsCollapsed(HTItem hItem) { return !(GetStatus(hItem) == TL_EXPANDED); };
	BOOL IsLeaf(HTItem hItem) { return GetStatus(hItem) == TL_LEAF; };

	// Expands, or collapses, the child items of the specified tree view item.
	virtual BOOL Expand( HTItem hItem, UINT nCode = TL_EXPAND );

	// Если значение аргумента FALSE, то появляется возможность выделять отедльные ячейки списка
	// кроме того, можно назначить каждой ячейке свой элемент управления, с помощью которого она будет редактироваться
	BOOL GetReadOnly() { return FALSE; };
	void SetReadOnly(BOOL bReadOnly=TRUE);

	BOOL MoveChildTo(HTItem hItem, HTItem hItemPos, BOOL bInsertAfter = TRUE);
	BOOL MoveSelItemsUp();
	BOOL MoveSelItemsDown();

	// Sorts the children of a given parent item. 
	BOOL SortChildren( HTItem hItem );

	// Sorts the children of a given parent item using an application-defined sort function. 
	BOOL SortChildrenCB( LPTVSORTCB pSort );

	BOOL SortChildren( HTItem hItem, int iSubItem, BOOL bAscending = TRUE);
	BOOL SortChildrenCB( TLSORTCB *pSort );

	// Влючить/выключить filterbar
	BOOL EnableFilterBar(BOOL bFilterBar, int iTimeout = -1);
	BOOL IsFilterBarEnabled();
	CString GetColumnFilter(int i);
	void SetColumnFilter(int i, LPCTSTR strFilter);
	// Фильтр выбрасывает сообщения
	//ON_NOTIFY(HDN_FILTERCHANGE, 0, OnFilterChange)
	//ON_NOTIFY(HDN_FILTERBTNCLICK, 0, OnFilterButtonClicked)

	void SetHeaderHeight(int iHeight); // -1 - default
	int GetHeaderHeight();

	// Если есть желание хранить информацию о subitemaх в другом месте
	// то необходимо переопределить следующие методы,
	// либо в родительском окне ловить TLNM_GETITEM/TLNM_SETITEM.
	//
	virtual BOOL OnGetItemInfo(HTItem hItem,int nCol,UINT mask,TLItemInfo &item);
	virtual BOOL OnSetItemInfo(HTItem hItem,int nCol,UINT mask,TLItemInfo &item);
	BOOL EnableParentItemInfoMsg(BOOL bEnable)
	{
		BOOL bOldEnable = m_bEnableParentItemInfoMsg;
		m_bEnableParentItemInfoMsg = bEnable;
		return bOldEnable;
	}

	//
	// SubItem attributes
	// если hItem==0, то свойства устанавливаются для столбца целиком.
	//

	BOOL GetItem(HTItem hItem,int nCol,UINT mask,TLItemInfo &item) 
	{
		return OnGetItemInfo(hItem,nCol,mask,item);
	}
	
	BOOL SetItem(HTItem hItem, int nCol, UINT mask, TLItemInfo &item);

	BOOL SetItemRow(HTItem hItem, UINT mask, TLItemInfo &item); // для всей строки

	// Все то же самое, но по одному
	//
	BOOL SetItemEditCtrl(HTItem hItem, int nCol, UINT nCtrlId )
	{
		TLItemInfo itemInfo;
		itemInfo.iControlType = nCtrlId;
		return SetItem(hItem,nCol,TLI_EDITCONTROL,itemInfo);
	}

	BOOL SetItemText(HTItem hItem, int nCol, LPCTSTR str)
	{
		TLItemInfo itemInfo;
		itemInfo.strText = str;
		if (nCol == -1) return SetItemRow(hItem,TLI_BORDER,itemInfo);
		return SetItem(hItem,nCol,TLI_TEXT,itemInfo);
	}

	BOOL SetItemData(HTItem hItem, int nCol,LPARAM dwData)
	{
		TLItemInfo itemInfo;
		itemInfo.dwData = dwData;
		return SetItem(hItem,nCol,TLI_DATA,itemInfo);
	}

	BOOL SetItemCheckState(HTItem hItem, int nCol, UINT nCheck)
	{
		TLItemInfo itemInfo;
		itemInfo.iChecked = nCheck;
		return SetItem(hItem,nCol,TLI_CHECKSTATE,itemInfo);
	}

	BOOL SetItemImage(HTItem hItem, int nCol, int iImage)
	{
		TLItemInfo itemInfo;
		itemInfo.drawingInfo.iImage = iImage;
		return SetItem(hItem,nCol,TLI_IMAGE,itemInfo);
	}

	BOOL SetItemCheckImages(HTItem hItem, int nCol, int iCheckImage,int iUncheckedImage)
	{
		TLItemInfo itemInfo;
		itemInfo.iChecked = TL_UNCHECKED;
		itemInfo.drawingInfo.iCheckedImage	 = iCheckImage;
		itemInfo.drawingInfo.iUncheckedImage = iUncheckedImage;
		return SetItem(hItem,nCol, TLI_CHECKSTATE |	TLI_CHECKEDIMAGE | TLI_UNCHECKEDIMAGE, itemInfo);
	}

	BOOL SetItemColor(HTItem hItem, int nCol, COLORREF textColor,COLORREF bkColor)
	{
		TLItemInfo itemInfo;
		itemInfo.drawingInfo.crTextColor = textColor;
		itemInfo.drawingInfo.crBkColor = bkColor;
		if (nCol == -1) return SetItemRow(hItem,TLI_BORDER,itemInfo);
		return SetItem(hItem,nCol,TLI_TEXTCOLOR | TLI_BKCOLOR,itemInfo); 
	}

	BOOL SetItemTextFormat(HTItem hItem, int nCol, UINT nFormat)
	{
		TLItemInfo itemInfo;
		itemInfo.drawingInfo.nFormat = nFormat;
		if (nCol == -1) return SetItemRow(hItem,TLI_BORDER,itemInfo);
		return SetItem(hItem,nCol,TLI_TEXTFORMAT,itemInfo);
	}

	BOOL SetItemBorder(HTItem hItem, int nCol, UINT uiBorder)
	{
		TLItemInfo itemInfo;
		itemInfo.drawingInfo.uiBorder = uiBorder;
		if (nCol == -1) return SetItemRow(hItem,TLI_BORDER,itemInfo);
		return SetItem(hItem,nCol,TLI_BORDER,itemInfo);
	}

	UINT GetItemEditCtrl(HTItem hItem, int nCol)
	{
		TLItemInfo itemInfo;
		GetItem(hItem,nCol,TLI_EDITCONTROL,itemInfo);
		return itemInfo.iControlType;
	}

	CString GetItemText(HTItem hItem, int nCol)
	{
		TLItemInfo itemInfo;
		GetItem(hItem,nCol,TLI_TEXT,itemInfo);
		return itemInfo.strText;
	}
	
	LPARAM GetItemData(HTItem hItem, int nCol)
	{
		TLItemInfo itemInfo;
		GetItem(hItem,nCol,TLI_DATA,itemInfo);
		return itemInfo.dwData;
	}

	int	GetItemCheckState(HTItem hItem, int nCol)
	{
		TLItemInfo itemInfo;
		GetItem(hItem,nCol,TLI_CHECKSTATE,itemInfo);
		return itemInfo.iChecked;
	}

	int	GetItemImage(HTItem hItem, int nCol)
	{
		TLItemInfo itemInfo;
		GetItem(hItem,nCol,TLI_IMAGE,itemInfo);
		return itemInfo.drawingInfo.iImage;
	}

	BOOL GetItemCheckImages(HTItem hItem, int nCol, int &iCheckImage,int &iUncheckedImage)
	{
		TLItemInfo itemInfo;
		BOOL bRes =	GetItem(hItem,nCol,TLI_CHECKEDIMAGE | TLI_UNCHECKEDIMAGE,itemInfo);
		iCheckImage = itemInfo.drawingInfo.iCheckedImage;
		iUncheckedImage = itemInfo.drawingInfo.iUncheckedImage;
		return bRes;
	}

	BOOL GetItemColor(HTItem hItem, int nCol, COLORREF& textColor,COLORREF& bkColor)
	{
		TLItemInfo itemInfo;
		BOOL bRes	= GetItem(hItem,nCol,TLI_TEXTCOLOR | TLI_BKCOLOR, itemInfo);
		textColor	= itemInfo.drawingInfo.crTextColor;
		bkColor		= itemInfo.drawingInfo.crBkColor;
		return bRes;
	}

	BOOL GetItemTextFormat(HTItem hItem, int nCol, UINT& nFormat)
	{
		TLItemInfo itemInfo;
		BOOL bRes = GetItem(hItem,nCol,TLI_TEXTFORMAT, itemInfo);
		nFormat = itemInfo.drawingInfo.nFormat;
		return bRes;
	}

	BOOL GetItemBorder(HTItem hItem, int nCol, UINT& uiBorder)
	{
		TLItemInfo itemInfo;
		BOOL bRes = GetItem(hItem,nCol,TLI_BORDER,itemInfo);
		uiBorder = itemInfo.drawingInfo.uiBorder;
		return bRes;
	}

	//	Service
	int HitTestEx(CPoint &point, int &col, UINT &flags);
	int HitTestEx(CPoint &point, int &col) const;
	//
	//
	//

	// Возвращает N строки hItem.
	int FindItem(HTItem hItem,int nStart = -1)
	{
		if(hItem==NULL || nStart<-1) return -1;
		for(int i=nStart + 1;i<m_aDisplayedItems.GetSize();i++) {
			if(m_aDisplayedItems[i]==hItem) return i;
		}
		return -1;
	}

	void Update(int nItem = -1,int nCol = -1);
	void Update(HTItem hItem,int nCol = -1);
	void RefreshSelection() 
	{
		Update(m_selection.iRow,m_selection.iCol);
	}

	// Позволяет отключить методы Update() и тем самым предотвратить
	// перерисовку контрола после каждой операции.
	// Метод работает через подсчет вызовов,
	// т. е. для каждого DisableUpdate(true) должен быть свой DisableUpdate(false).
	// Также с 17.06.2013 обработка сообщения WM_SETREDRAW и функции CWnd::SetRedraw()
	// полностью эквивалентна вызову данных методов.
	void DisableUpdate(bool bDisable = true);
	bool IsUpdateDisabled();

	static BOOL IsNavigationKey(UINT nChar);
	static BOOL IsAlphaKey(UINT nChar);

	int OrderToIndex(int iColumnOrder)
	{
		return GetHeaderCtrl()->OrderToIndex(iColumnOrder);
	}

	int IndexToOrder(int nColumn)
	{
		LVCOLUMN col;
		col.mask = LVCF_ORDER;
		GetColumn(nColumn,&col);
		return col.iOrder;
	}


	BOOL EnableColumnsAutoSize(BOOL bEnable = TRUE);
	BOOL IsColumnAutoSize();

	void RedrawAllContent() 
	{
		CListCtrl::DeleteAllItems();
		m_aDisplayedItems.RemoveAll();
		m_root.m_data.uiStatus = TL_COLLAPSED;
		Expand(&m_root,TL_EXPAND);
	}

	// Разрешить перехватывать родительскому диалогу такие клавиши, как
	// VK_RETURN,VK_ESC.
	void EnableDlgKey(UINT key, BOOL bEnable = TRUE);
	BOOL IsDlgKeyEnabled(UINT key);
	
	void EnableContextMenu(BOOL bEnable = TRUE) { m_bEnableContextMenu = bEnable; }
	BOOL IsContextMenuEnabled() const { return m_bEnableContextMenu; }

	void SetRegKey(LPCTSTR strRegFolderKey, LPCTSTR strRegKey = NULL);

	void SaveState();
	void LoadState();
	void RestoreColumnState(int iCol, LPCTSTR strKeyInfo);
		
	//
	// Drag and drop
	//
	BOOL EnableDragNDrop(BOOL bEnable = TRUE) 
	{ 
		BOOL bOld = m_bDragNDropEnabled; 
		m_bDragNDropEnabled = bEnable;
		return bOld;
	};
	BOOL EnableParentManagedDragNDrop(BOOL bEnable = TRUE) 
	{
		BOOL bOld = m_bParentManagedDragEnabled;
		m_bParentManagedDragEnabled = bEnable;
		if (bEnable)
			m_bDragNDropEnabled = bEnable;
		return bOld;
	};

	virtual BOOL IsItemsCanBeDroppedOn(HTItem* hSource, int iSrcCount, HTItem hTarget) { return TRUE; }
	virtual BOOL IsItemsCanBeDragged(HTItem* hSource, int iSrcCount) { return TRUE; }
	virtual BOOL OnItemsDropped(HTItem* hSource, int iSrcCount, HTItem hTarget, UINT nFlags);
	virtual CImageList* CreateDragImage( int iItem);

	BOOL  AddInPlaceCtrl(UINT nCtrlId,CInPlaceCtrl *pNewCtrl);

	CInPlaceCtrl* GetInPlaceCtrl(UINT_PTR nCtrlId);

//	Notify default actions
	virtual void OnNotifyFromIPCtrl(TLNM_ITEM &nmItem) {};

	//	Вспомогательные функции рисования
	//
	CFont* FontForSubItem(UINT nFormat); //  возвращает NULL если фонт по умолчанию.

	// Проверка валидности итемов
	BOOL IsValid(HTItem hItem) { WORD val; return m_trueItems.Lookup(hItem,val); }
	void MakeValid(HTItem hItem, BOOL bValid = TRUE) 
	{ 
		if(bValid) m_trueItems.SetAt(hItem,0); 
		else m_trueItems.RemoveKey(hItem);
	};
	
	// Tooltip control
	int SetMaxTooltipWidth(int nWidth = -1)
	{
		int nOldMaxWidth = m_nMaxTooltipWidth;
		if (nWidth >= -1)
			m_nMaxTooltipWidth = nWidth;
		return nOldMaxWidth;
	}
	
	// Учитывать текст в заголовке при двойном клике на колонку
	BOOL UseHeaderTextAtDoubleClick(BOOL bUse)
	{
		BOOL bOldUseHeaderText = m_bUseHeaderTextAtDoubleClick;
		m_bUseHeaderTextAtDoubleClick = bUse;
		return bOldUseHeaderText;
	}

	// Включить отрисовку согласно текущей платформенной теме
	BOOL EnablePlatformTheme(BOOL bEnable);
	BOOL IsPlatformThemeEnabled();
	COLORREF GetPlatformColor(int idx); // IMcTheme::McThemeElement

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxTreeListCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CxTreeListCtrl();
	BOOL HitTestMouseClick(CPoint point, BOOL bRightButton = FALSE);

	// Generated message map functions
protected:
	//{{AFX_MSG(CxTreeListCtrl)
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEndEdit( NMHDR * pNotifyStruct, LRESULT * result );
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDividerdblclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegintrack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginColumndrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnPopupFtMenu(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPrint(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG

//
// Draw functions
//

	// Если IsPrePaint, то вызывается OnDraw перед началом рисования итемов.
	// Если мы вообще не хотим рисовать итемы OnDraw возвращаем TRUE.
	//
	virtual BOOL IsPrePaint() { return TRUE; }
	virtual BOOL OnPrePaint(CDC* pDC) { return FALSE; }
	
	// Если IsSubItemDraw, то рисуем итемы сами, а не ListCtrl,
	// а мы их сами рисуем.
	// Если пронаследовали OnSubItemDraw, то возвращаем TRUE,
	// чтобы случайно ListCtrl не нарисовал что-нить от себя
	// (если конечно не хотим рисования ListCtrl'a)
	//
	virtual BOOL IsSubItemDraw() { return TRUE; }
	virtual BOOL OnSubItemDraw(CDC* pDC, int nItem, int nSubItem, UINT nState, LPARAM lParam);

	// Если IsItemPostDraw(), то мы обрабатываем после итемное рисование
	// например рисуем п/y или фокус, если селектирован.
	//
	virtual BOOL IsItemPostDraw() { return TRUE; }
	virtual BOOL OnItemPostDraw(CDC* pDC, int nItem, UINT nState, LPARAM lParam);

	// Если IsPostDraw(), то завершающие штрихи.
	// (Фото программиста в нижнем правом углу).
	//
	virtual BOOL IsPostDraw() { return FALSE; }
	virtual BOOL OnPostDraw(CDC *pDC) { return FALSE; }
	
//
// Internal structures
//
	BOOL HitTestCollapse(HTItem hItem, CPoint point);
	BOOL HitTestCheckbox(CPoint point, HTItem hItem, int iTItem);

	LRESULT NotifyOwner(TLNM_ITEM &nmItem);
	void MakeNotify(TLNM_ITEM &nmItem,UINT code);

	virtual BOOL EditDraw(int nItem,int nSubItem,UINT nFlags = 0,CPoint *pt = NULL);
	virtual BOOL EditPrepare(int iRow = -1, int iCol = -1,UINT nFlags = 0, CPoint *pt = 0);

public:
	virtual BOOL EditBegin(UINT nChar=0);
	virtual BOOL EditFinish(TLNM_ITEM &nmItem);

	BOOL EnsureVisible(int iItem, int iSubItem, BOOL bPartialOK = FALSE);
protected:
	BOOL Navigation(UINT nChar, BOOL bControlLostTocus);

	BOOL ExpandR(HTItem hItem, UINT nCode,int &iItem); // True expand

	BOOL GetSubItemRect( int iItem, int iSubItem, int nArea, CRect& ref );

	void DrawCheckBox(CDC *pDC, CRect &rc, int iState);
	void DrawButton(CDC* pDC, CRect &rc, BOOL bArrow = FALSE);

	public:
	struct  TLSubItem;
	typedef CMap<UINT,UINT,CInPlaceCtrl*,CInPlaceCtrl*> IP_CTRLS;

	class TREE_SUBITEMS
	{
		// Идея следующая.
		// Класс - массив указателей на subitemы.
		// Размер <= GetColumnCount().
		// По умолчанию все указатели = NULL.
		// Если хоть раз вызывали в TreeListCtrl SetItem(,nCol)
		// то для элемента iIndex = nCol, создается TLSubItem.
		// Причем, соответственно, если определить ф-ии OnGetItemInfo/OnSetItemInfo
		// (что приветствуется) и хранить данные в другом месте, 
		// то память дополнительно не расходуется.
	public:
		TREE_SUBITEMS() 
		{
			m_pItems = NULL;
		}
		~TREE_SUBITEMS() { RemoveAll(); } 

		INT_PTR GetSize() { return m_pItems ? m_pItems->GetSize() : 0; }

		TLItemInfo* GetAt(int iIndex)
		{
			if(m_pItems && iIndex>=0 && iIndex<GetSize()) return m_pItems->GetAt(iIndex);
			else return NULL;
		}

		BOOL SetAt(int iIndex, TLItemInfo* pItem)
		{
			delete GetAt(iIndex);

			if(m_pItems==NULL) m_pItems = new CTypedPtrArray<CPtrArray,TLItemInfo*>;

			if(iIndex>=GetSize())
			{
				SetSize(iIndex+1);
				m_pItems->SetAt(iIndex,pItem);
			}
			else m_pItems->SetAt(iIndex,pItem);
			return TRUE;
		}
		
		BOOL InsertAt(int iIndex, TLItemInfo* pItem)
		{
			if(m_pItems==NULL) m_pItems = new CTypedPtrArray<CPtrArray,TLItemInfo*>;

			if(iIndex>GetSize())  // Знак болше стоит умышлено.
			{				
				SetSize(iIndex+1);
				m_pItems->SetAt(iIndex,pItem);
			}
			else m_pItems->InsertAt(iIndex,pItem);
			return TRUE;
		}
		
		void SetSize( int nNewSize, int nGrowBy = -1 )
		{
			if(m_pItems==NULL) m_pItems = new CTypedPtrArray<CPtrArray,TLItemInfo*>;

			INT_PTR oldSize = GetSize(); 
			m_pItems->SetSize(nNewSize, nGrowBy);
			for(INT_PTR i=oldSize; i<nNewSize; i++) 
			{
				m_pItems->SetAt(i,NULL);
			}
		};

		void RemoveAt(int nIndex)
		{
			if(m_pItems) {
				if(nIndex>=0 && nIndex<GetSize()) {
					delete m_pItems->GetAt(nIndex);
					m_pItems->RemoveAt(nIndex);
				}
			}
		}

		void RemoveAll()
		{
			if(m_pItems)
			{
				for(int i=0;i<GetSize();i++) delete m_pItems->GetAt(i);
				m_pItems->RemoveAll();
				delete m_pItems;
				m_pItems = NULL;
			}
		}

	protected:
		CTypedPtrArray<CPtrArray,TLItemInfo*> *m_pItems;
	};

	struct CTreeItemData
	{
		UINT		  uiStatus;
		UINT_PTR  dwData;
		TREE_SUBITEMS subItems;

		CTreeItemData()
		{
			uiStatus = TL_LEAF;
			dwData = 0;
		}
	};

	typedef CTreeNode<CTreeItemData> CTLItem;

	int GetImageWidth() 
	{
		CImageList* pImageList = GetImageList(LVSIL_SMALL);
		if(pImageList ==NULL) 
		{
			CRect rc;
			CListCtrl::GetSubItemRect(0,0,LVIR_BOUNDS,rc);
			return rc.Height();
		}
		IMAGEINFO iminfo;
		pImageList->GetImageInfo(0, &iminfo);
		return iminfo.rcImage.right - iminfo.rcImage.left;
	}

	BOOL CheckTreeColumnWidth();

	void UpdateGDIObjects();
	void FreeGDIObjects();

protected:
//
// For private use only
//
	BOOL InsertItem(int item,HTItem hItem);
	void DeleteItem(int item);

	void SetItem(INT_PTR item,HTItem hItem) { m_aDisplayedItems[item] = hItem; }

	int GetStatus(HTItem hItem) 
	{
		if(!IsValid(hItem)) return 0;
		return ((CTLItem*)hItem)->m_data.uiStatus;
	};

	static LRESULT __stdcall _ToolTipWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
// Data
//
protected:
	CTLItem			m_root;
	CPtrArray		m_aDisplayedItems;
	IP_CTRLS		m_ipCtrls;
	TREE_SUBITEMS	m_columnInfo;
	int				m_nTreeColumn;
	BOOL			m_bMovableTreeColumn;
	BOOL			m_bShowTreeLines;
	CSelection		m_selection;
	BOOL			m_bEnableParentItemInfoMsg;
	BOOL			m_bUseHeaderTextAtDoubleClick;

	CString			m_strRegKey;
	CString			m_strRegFolderKey;

	// All for drag & drop
	//
	BOOL m_bDragNDropEnabled;
	BOOL m_bParentManagedDragEnabled;
	BOOL m_bDragging;
	HTItem *m_dragItems;
	int		m_dragItemCount;
	CSize m_szDragDelta;
	CImageList *m_pDragImageList;

	BOOL    m_bCreated;
	int     m_iUpdateDisabledCount;

	CUIntArray m_dlgkeys;
	BOOL m_bEnableContextMenu;	

	// Коллекция исключительно для проверки итемов на валидность
	// Все реально существующие элементы дерева добавляются в эту колекцию,
	// после их уничтожения удаляются из коллекции, если в коллекции нет,
	// значит итемом пользоваться нельзя
	CMapPtrToWord m_trueItems;

	// Ip ctrl storage methods.
	//
	void RemoveAllInPlaceCtrls();
	void HideAllInPlaceCtrls();
	BOOL CreateWindowsForInPlaceCtrls();
	void CreateStdInPlaceCtrls();

	void DoInitialization();

	DECLARE_MESSAGE_MAP()
protected:
	// Gdi objects
	COLORREF m_crBkColor;
	COLORREF m_crTextColor;
	COLORREF m_crTextBkColor;
	COLORREF m_crHighlite;
	COLORREF m_crHighliteText;
	COLORREF m_crLineColor;
	COLORREF m_crBtnHighlite;
	COLORREF m_crBtnShadow;
	COLORREF m_crBtnFace;
	COLORREF m_crBtnText;
	COLORREF m_crTextDisabled;

	HBRUSH m_hBrushBtnFace;
	HBRUSH m_hBrushHighlite;
	HBRUSH m_hBrushHighliteWithoutFocus;
	HBRUSH m_hBrushText;
	HBRUSH m_hBrushTextBk;
	HBRUSH m_hBrushNull;

	HPEN m_hPenBtnHighlite;
	HPEN m_hPenBtnShadow;
	HPEN m_hPenLine;
	HPEN m_hPenTextColor;
	HPEN m_hPenTextDisabled;
	HPEN m_hPenCheckFrame;
	HPEN m_hPenCheck;
	HPEN m_hPenSelection;

	// ToolTip's data
	HWND     m_hwndTT;
	UINT_PTR m_dwTT_TimerID;
	WNDPROC  m_lpTT_OldWndProc;
	int      m_nItemTT, m_nSubItemTT;
	int      m_nMaxTooltipWidth;

	// Поддержка платформенных тем
	BOOL	m_bPlmThemeActive;
	HBRUSH	m_hbrThemeBkgnd;
	McsMap<int, int, COLORREF, COLORREF> m_mapPlmColors;

public:
	CFlatHeaderCtrl *m_pWndFlatHeader;
};

typedef CxTreeListCtrl::CTLItem*	  ItemPtr;
/////////////////////////////////////////////////////////////////////////////

//
//	CInPlaceCtrl
//

// При потере фокуса посылает сообщение об изменении данных.
// Родительское окно либо прячет, либо удаляет, либо возвращает фокус
// Если нужны дополнительные данные WM_NOTIFY родительскому окну TLNM_INPLACE_NEEDINIT
// Реакция на события TLNM_INPLACE_ACTION
// !Замечание(скорее даже для самого себя): при создании производного класса,
// вначале необходимо наследовать от класса окна, а потом уже от CInPlaceCtrl.
//

class CInPlaceCtrl
{
public:
	virtual ~CInPlaceCtrl() {};

	// Инициализируется 1 раз при создании.
	virtual BOOL CreateOneTime(CWnd* parent, UINT nCtrlId) = 0;

	// Функция инициализации (в каждом производном классе своя).
	// При реакции на TLNM_INPLACE_NEEDINIT нужно ее вызвать,
	// либо можно вызвать один раз !после CreateOneTime!.
	virtual BOOL Init(WPARAM wParam, LPARAM lParam) { return FALSE; };

	virtual HWND GetHWND() { return NULL; }

	// В общем-то можно всегда оставаться выведенным,
	// но только для этого необходимо нарисовать себя в контексте 
	// родительского окна.
	virtual BOOL IsEditDraw() {	return FALSE; };
	virtual BOOL IsEditDrawOnMove() { return FALSE; };
	virtual BOOL EditDraw(CRect& rc, TLNM_ITEM& item, CDC *pDC, UINT nFlags = 0, CPoint *point = NULL) { return FALSE; };

	virtual BOOL CanSelect() { return TRUE; }; // пока пустышка.

	// Вызывается когда селектируют итем.
	// Если переместили стрелками point = 0.
	// Если селекция была мышевой, то вызывается только втом случае,
	// если контрол редактирования себя рисует(IsEditDraw==TRUE), 
	// В этом случае point!=0, nFlags!=0 и если EditPrepare вернет FALSE, 
	// то переместим селекцию(!Снова будет попытка EditPrepare point=0). 
	// Если TRUE, то оставим на месте.
	// т.е. ctrl должен различать EditPrepare от мыши и от клавиатуры.
	//
	virtual BOOL IsEditPrepare() { return FALSE; };
	virtual BOOL EditPrepare(CRect& rc, TLNM_ITEM& item, UINT nFlags = 0, CPoint *point = NULL) { return FALSE; };

	// Double click or Enter, or other alpha key - начало редактирования.
	virtual BOOL IsEditBegin() { return FALSE; };
	virtual BOOL EditBegin(CRect& rc, TLNM_ITEM& item, UINT nChar) { return FALSE; };

	// Показать меню по правой кнопке на неактивированном контроле
	virtual BOOL ShowContextMenu(TLNM_ITEM& item, CPoint *point) { return FALSE; };
	void KillFocusNotify(CWnd* me, CWnd* newWindow);
};

//
//	CInPlaceEditCtrl
//
class CInPlaceEditCtrl : public CEdit, public CInPlaceCtrl
{
// Construction
public:
	CInPlaceEditCtrl(BOOL bResizing = FALSE, BOOL bTreeIsParent = TRUE) : CEdit() 
	{
		m_bCancel = FALSE;
		m_bResizing = bResizing;
		m_bTreeIsParent = bTreeIsParent;
	};
	~CInPlaceEditCtrl() {};

	virtual BOOL CreateOneTime(CWnd* parent, UINT nCtrlId);

	virtual HWND GetHWND() { return this->m_hWnd; }

	// Double click or Enter, or other alpha key - начало редактирования.
	virtual BOOL IsEditBegin() { return TRUE; };
	virtual BOOL EditBegin(CRect& rc, TLNM_ITEM& item, UINT nChar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceEditCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	//}}AFX_VIRTUAL

// Implementation
public:
	void ResizeEditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceEditCtrl)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nTlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nTlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	TLNM_ITEM m_nmItem;
	BOOL	m_bCancel;
	BOOL	m_bResizing;
	BOOL	m_bTreeIsParent;
};

//
//	CInPlaceCustomDlg
//
class CInPlaceCustomDlg : public CxButtonLt, public CInPlaceCtrl
{
// Construction
public:
	CInPlaceCustomDlg();
	virtual ~CInPlaceCustomDlg();

	virtual BOOL CreateOneTime(CWnd* parent, UINT nCtrlId);

	virtual HWND GetHWND() { return this->m_hWnd; }

	// Вызывается когда курсор над контролом.
	virtual BOOL IsEditPrepare() { return TRUE; };
	virtual BOOL EditPrepare(CRect& rc, TLNM_ITEM& item, UINT nFlags = NULL, CPoint *point = NULL);

	BOOL Action();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceEditCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceCustomDlg)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nTlags);
	afx_msg void OnLButtonUp(UINT nTlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nTlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	TLNM_ITEM	m_nmItem;
	BOOL		m_bAction;
	BOOL		m_bCapture;
};

//
struct structInPlaceComboItem 
{
	CString strText;
	DWORD	dwData;
};
typedef CArray<structInPlaceComboItem, structInPlaceComboItem&> ARR_INPLACE_COMBOITEM;

//
//		CInPlaceList
//

// Flags for wParam
#define IP_LIST_MCSSTRINGARRAY		  0x00000001 // в lParam - передается mcsStringArray, в противном случае CStringArray.
#define IP_LIST_DISABLE_AUTO_COMPLETE 0x80000000 // Запретить автозаполнение подбором из списка.

class CInPlaceList : public CComboBox, public CInPlaceCtrl
{
// Construction
public:
	CInPlaceList(int bCanEdit = TRUE, BOOL bSort = TRUE);
	virtual ~CInPlaceList();

	virtual BOOL CreateOneTime(CWnd* parent, UINT nCtrlId);

	virtual HWND GetHWND() { return this->m_hWnd; }

	// lParam - IP_LIST_* flags.
	// wParam - указатель на CStringArray.
	virtual BOOL Init(WPARAM wParam, LPARAM lParam);

	virtual BOOL IsEditPrepare() { return TRUE; }
	virtual BOOL EditPrepare(CRect& rc,TLNM_ITEM& item, UINT nFlags = NULL, CPoint *point = NULL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	int FindStringExact(int nIndexStart,LPCTSTR lpszFind)
	{
		int iStr = CComboBox::FindStringExact(-1,m_nmItem.item.strText);
		CString str;
		if(iStr != CB_ERR ) 
		{
			GetLBText(iStr, str);
			if(str!=m_nmItem.item.strText) iStr = CB_ERR;
		}
		return iStr;
	}

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceList)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nTlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg void OnSelchange();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEndEdit( NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnEditUpdate();
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDrowDown();
	//}}AFX_MSG

	void DrawArrow(CDC* pDC,CRect &rcButton, BOOL bPressed = FALSE);

	DECLARE_MESSAGE_MAP()
private:
	TLNM_ITEM		m_nmItem;
	int				m_iSelItem;
	BOOL			m_bCanEdit;
	CInPlaceEditCtrl*	m_pEdit;
	BOOL			m_bAlphaKeyPressed;
	BOOL			m_bModified;
	BOOL			m_bSort;
	BOOL			m_bDisableAutoComplete;
};

//
//	CHighliteButton
//
class CHighliteButton : public CStatic, public CInPlaceCtrl
{
public:
	CHighliteButton(); 
	~CHighliteButton() {};

	BOOL CreateOneTime(CWnd* parent, UINT nCtrlId);

	virtual HWND GetHWND() { return this->m_hWnd; }

	virtual BOOL Init(WPARAM wParam, LPARAM lParam) 
	{
		m_crHighliteColor = (COLORREF)wParam; 
		return FALSE; 
	};
	
	virtual BOOL IsEditDraw() {	return TRUE; };
	virtual BOOL IsEditDrawOnMove() { return TRUE; };
	virtual BOOL EditDraw(CRect& rc, TLNM_ITEM& item, CDC *pDC, UINT nFlags = 0, CPoint *point = NULL);

	virtual BOOL CanSelect() { return FALSE; };
	
	// Вызывается когда курсор над контролом.
	virtual BOOL IsEditPrepare() { return TRUE; };
	virtual BOOL EditPrepare(CRect& rc, TLNM_ITEM& item, UINT nFlags = 0, CPoint *point = NULL);

	// Double click or Enter, or other alpha key - начало редактирования.
	virtual BOOL IsEditBegin() { return TRUE; };
	virtual BOOL EditBegin(CRect& rc, TLNM_ITEM& item, UINT nChar) 
	{
		return TRUE;
	};

	//// 
	//
	BOOL Action();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceList)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	TLNM_ITEM m_nmItem;
	BOOL	 m_bButtonPressed;
	CPoint	 m_curMousePt;
	COLORREF m_crHighliteColor;
};


//
//	CInPlaceButton
//
class CInPlaceButton : public CToolBar, public CInPlaceCtrl
{
	BOOL m_bCapture;
// Construction
public:
	CInPlaceButton();

	virtual BOOL CreateOneTime(CWnd* parent, UINT nCtrlId);

	virtual HWND GetHWND() { return this->m_hWnd; }

	// Рисовать выключенную кнопку.
	virtual BOOL IsEditDraw() {	return TRUE; };
	virtual BOOL EditDraw(CRect& rc, TLNM_ITEM& item, CDC *pDC, UINT nFlags = NULL, CPoint *point = NULL);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceButton)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInPlaceButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
private:
	UINT	m_uChar;
	BOOL	m_bTracking;
	BOOL	m_bMoving;
};


//
//	CInPlaceEditBtn
//
class CInPlaceEditBtn : public CxEditLt, public CInPlaceCtrl
{
// Construction
public:
	CInPlaceEditBtn();
	virtual ~CInPlaceEditBtn();

	virtual BOOL CreateOneTime(CWnd* parent, UINT nCtrlId);

	virtual HWND GetHWND() { return this->m_hWnd; }

	// Вызывается когда курсор над контролом.
	virtual BOOL IsEditPrepare() { return TRUE; };
	virtual BOOL EditPrepare(CRect& rc, TLNM_ITEM& item, UINT nFlags = NULL, CPoint *point = NULL);

	virtual BOOL IsEditBegin() { return TRUE; };
	virtual BOOL EditBegin(CRect&rc, TLNM_ITEM &item, UINT nChar);

	virtual BOOL Init(WPARAM wParam, LPARAM lParam);

	BOOL Action();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceEditBtn)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceEditBtn)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nTlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	//}}AFX_MSG
	afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam);


	DECLARE_MESSAGE_MAP()
private:
	TLNM_ITEM	m_nmItem;
	BOOL		m_bAction;
	BOOL		m_bCapture;
};

//
//	CInPlaceEditCtrl
//
class CInPlaceEditFt : public CxFtEdit, public CInPlaceCtrl
{
// Construction
public:
	CInPlaceEditFt(BOOL bReadOnly = FALSE, BOOL bResizing = FALSE, BOOL bTreeIsParent = TRUE) : CxFtEdit() 
	{
		m_bCancel = FALSE;
		m_bResizing = bResizing;
		m_bTreeIsParent = bTreeIsParent;
		m_bReadOnly = bReadOnly;
	};
	~CInPlaceEditFt() {};

	virtual BOOL CreateOneTime(CWnd* parent, UINT nCtrlId);

	virtual HWND GetHWND() { return this->m_hWnd; }

	// Функция инициализации (в каждом производном классе своя).
	// При реакции на TLNM_INPLACE_NEEDINIT нужно ее вызвать,
	// либо можно вызвать один раз !после CreateOneTime!.
	virtual BOOL Init(WPARAM wParam, LPARAM lParam);

	// Double click or Enter, or other alpha key - начало редактирования.
	virtual BOOL IsEditBegin();
	virtual BOOL EditBegin(CRect& rc, TLNM_ITEM& item, UINT nChar);

	virtual BOOL IsEditDraw() {	return TRUE; };
	virtual BOOL IsEditDrawOnMove() { return FALSE; };
	virtual BOOL EditDraw(CRect& rc, TLNM_ITEM& item, CDC *pDC, UINT nFlags = NULL, CPoint *point = NULL);

	virtual BOOL ShowContextMenu(TLNM_ITEM& item, CPoint *point);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceEditCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	//}}AFX_VIRTUAL

// Implementation
public:
	void ResizeEditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceEditCtrl)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nTlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nTlags);
	afx_msg LRESULT OnPopupFtMenu(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMeasured( NMHDR * pNotifyStruct, LRESULT * result);	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	TLNM_ITEM m_nmItem;
	BOOL	m_bCancel;
	BOOL	m_bResizing;
	BOOL	m_bTreeIsParent;
	BOOL	m_bReadOnly;
};

//
//	CInPlaceDateTimeCtrl
//
class CInPlaceDateTimeCtrl : public CDateTimeCtrl, public CInPlaceCtrl
{
// Construction
public:
	CInPlaceDateTimeCtrl();
	virtual ~CInPlaceDateTimeCtrl();

	virtual BOOL CreateOneTime(CWnd* parent, UINT nCtrlId);

	virtual HWND GetHWND() { return this->m_hWnd; }

	// wParam - указатель LPCTSTR - формат отображения
	// lParam - указатель LPSYSTEMTIME - дата
	virtual BOOL Init(WPARAM wParam, LPARAM lParam);

	// Вызывается когда курсор над контролом.
	virtual BOOL IsEditPrepare() { return TRUE; };
	virtual BOOL EditPrepare(CRect& rc, TLNM_ITEM& item, UINT nFlags = NULL, CPoint *point = NULL);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceEditCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceCustomDlg)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCloseUp(NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnChange(NMHDR* pNotifyStruct, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	TLNM_ITEM  m_nmItem;
	SYSTEMTIME m_time;
	bool       m_bManualChanged;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

BOOL GetCategoryTreeItems(CxTreeListCtrl *pTreeList, CArray<HTItem,HTItem> &items);

#endif // !defined(AFX_TREELISTCTRL_H__3AD0AA0B_377B_489C_B1FD_3374DAFFEC0F__INCLUDED_)

