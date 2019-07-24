#pragma once


// CNewKey 对话框

class CNewKey : public CDialogEx
{
	DECLARE_DYNAMIC(CNewKey)

public:
	CNewKey(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewKey();

// 对话框数据
	enum { IDD = IDD_DLG_NEWKEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
};
