
// 注册表工具Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// C注册表工具Dlg 对话框
class C注册表工具Dlg : public CDialogEx
{
// 构造
public:
	C注册表工具Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenReg();
	afx_msg void OnRefreshReg();
	afx_msg void OnCloseReg();
	afx_msg void OnNewKey();
	afx_msg void OnDelKey();
	afx_msg void OnRefreshKey();
	afx_msg void OnNewVal();
	afx_msg void OnDelVal();
	afx_msg LRESULT OnAddNewKey(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	
public:
	CListCtrl m_regList;
	HTREEITEM m_htree[5];
	HKEY RootKeys[5],keys[5];
	CToolBar m_toolbar;
	CStatusBar m_statusbar;
	CTreeCtrl m_regTree;
	afx_msg void OnTvnSelchangedTreeReg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangingTreeReg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTreeReg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMRClickTreeReg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListReg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
};
