
// ע�����Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// Cע�����Dlg �Ի���
class Cע�����Dlg : public CDialogEx
{
// ����
public:
	Cע�����Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
