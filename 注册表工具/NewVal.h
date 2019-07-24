#pragma once
#include "afxwin.h"


// CNewVal 对话框

class CNewVal : public CDialogEx
{
	DECLARE_DYNAMIC(CNewVal)

public:
	CNewVal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewVal();

// 对话框数据
	enum { IDD = IDD_DLG_NEWVAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CComboBox m_combo;
	CComboBox m_comb;
	afx_msg void OnBnClickedOk();
};
