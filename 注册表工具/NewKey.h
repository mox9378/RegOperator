#pragma once


// CNewKey �Ի���

class CNewKey : public CDialogEx
{
	DECLARE_DYNAMIC(CNewKey)

public:
	CNewKey(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewKey();

// �Ի�������
	enum { IDD = IDD_DLG_NEWKEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
};
