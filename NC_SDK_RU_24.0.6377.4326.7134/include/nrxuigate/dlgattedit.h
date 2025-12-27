// atteditDlg.h : header file
//

#pragma once

#define ATTEDIT_MAX_STEP  8 // размер максимального шага между атрибутами
#ifndef HOST_IN_QT
#include "hostUI.h"
// CNrxDlgAttEdit dialog
class CNrxDlgAttEdit : public CDialog
{
// Construction
public:
	CNrxDlgAttEdit(const OdDbObjectId& blockId, const OdDbObjectIdArray& attrIds, CWnd* pParent = NULL);    // standard constructor

	// Dialog Data
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	int m_min;
	int m_max;
	int m_currPage;
	//void FillEditBoxes(, std::map<CString, CString>);
	// массив указателей на элементы управления
	void UpdateValues(const int pageNumber);
	std::vector< CWnd* > m_valueEditBoxes;
	std::vector< CWnd* > m_promptLabels;
	CString              m_attrValue01;
	CString              m_attrValue02;
	CString              m_attrValue03;
	CString              m_attrValue04;
	CString              m_attrValue05;
	CString              m_attrValue06;
	CString              m_attrValue07;
	CString              m_attrValue08;
	OdDbObjectId         m_blockId;
public:
	OdDbObjectIdArray    m_attrIds;
	OdDbObjectIdArray    m_subAttrIds;
	afx_msg void OnBnClickedAtteditNextBtn();
	afx_msg void OnBnClickedAtteditPrevBtn();
	//const std::map<OdDbObjectId, CString>& id2Prompt;
	std::map< OdDbObjectId, CString > m_id2Value;
	std::map< CWnd*, OdDbObjectId >   m_edit2Id;
	std::vector< OdString >           m_prompts;
	afx_msg void OnEnChangeAttrValueEdit();
	afx_msg void OnEnChangeAttrValueEdit2();
	afx_msg void OnEnChangeAttrValueEdit3();
	afx_msg void OnEnChangeAttrValueEdit4();
	afx_msg void OnEnChangeAttrValueEdit5();
	afx_msg void OnEnChangeAttrValueEdit6();
	afx_msg void OnEnChangeAttrValueEdit7();
	afx_msg void OnEnChangeAttrValueEdit8();

	void SetAttributeText();
	void SetNewValue(const UINT ctrlId, CString* attrValue01);

	afx_msg void OnBnClickedOk();

public:
	static int GetPromptFromBlockAttrDef(OdDbBlockTableRecord* pBlock, std::vector< OdString >& prompts);
	static int GetPromptFromAttrDef(const OdDbObjectIdArray& attDefIds, std::vector< OdString >& prompts);
};
#endif