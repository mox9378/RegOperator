// NewKey.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ע�����.h"
#include "NewKey.h"
#include "afxdialogex.h"


// CNewKey �Ի���

IMPLEMENT_DYNAMIC(CNewKey, CDialogEx)

CNewKey::CNewKey(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewKey::IDD, pParent)
{

}

CNewKey::~CNewKey()
{
}

void CNewKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewKey, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CNewKey::OnBnClickedBtnAdd)
END_MESSAGE_MAP()


// CNewKey ��Ϣ�������


void CNewKey::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str,*pstr;
	GetDlgItemText(IDC_EDIT_NEWKEY,str);
	if(str.GetLength()==0)
	{
		MessageBoxW(L"��������Ϊ�գ����ܴ����ռ�");
		return;
	}
	pstr = new CString(str);
	CNewKey::OnOK();
	AfxGetMainWnd()->PostMessageW(WM_ADDNEWKEY,0,(LPARAM)pstr); 
}
