#pragma once
#include "afxwin.h"


// CNewVal �Ի���

class CNewVal : public CDialogEx
{
	DECLARE_DYNAMIC(CNewVal)

public:
	CNewVal(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewVal();

// �Ի�������
	enum { IDD = IDD_DLG_NEWVAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CComboBox m_combo;
	CComboBox m_comb;
	afx_msg void OnBnClickedOk();
};
