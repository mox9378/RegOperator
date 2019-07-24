// NewKey.cpp : 实现文件
//

#include "stdafx.h"
#include "注册表工具.h"
#include "NewKey.h"
#include "afxdialogex.h"


// CNewKey 对话框

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


// CNewKey 消息处理程序


void CNewKey::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str,*pstr;
	GetDlgItemText(IDC_EDIT_NEWKEY,str);
	if(str.GetLength()==0)
	{
		MessageBoxW(L"键名不能为空，不能创建空键");
		return;
	}
	pstr = new CString(str);
	CNewKey::OnOK();
	AfxGetMainWnd()->PostMessageW(WM_ADDNEWKEY,0,(LPARAM)pstr); 
}
