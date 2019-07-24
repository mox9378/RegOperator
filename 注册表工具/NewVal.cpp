// NewVal.cpp : 实现文件
//

#include "stdafx.h"
#include "注册表工具.h"
#include "NewVal.h"
#include "afxdialogex.h"
#include "注册表工具Dlg.h"

// CNewVal 对话框

IMPLEMENT_DYNAMIC(CNewVal, CDialogEx)

CNewVal::CNewVal(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewVal::IDD, pParent)
{
}

CNewVal::~CNewVal()
{
}

void CNewVal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VALTYPE, m_combo);
}


BEGIN_MESSAGE_MAP(CNewVal, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CNewVal::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewVal 消息处理程序
BOOL CNewVal::OnInitDialog(){
	CDialogEx::OnInitDialog();

	//TODO 
	//m_combo.InitStorage(256,10);
	m_combo.AddString(L"REG_NONE");
	m_combo.AddString(L"REG_SZ");
	m_combo.AddString(L"REG_EXPAND_SZ");
	m_combo.AddString(L"REG_BINARY");
	m_combo.AddString(L"REG_DWORD");
	m_combo.AddString(L"REG_DWORD_BIG_ENDIAN");
	m_combo.AddString(L"REG_LINK");
	m_combo.AddString(L"REG_MULTI_SZ");
	m_combo.AddString(L"REG_RESOURCE_LIST");
	m_combo.AddString(L"REG_FULL_RESOURCE_DESCRIPTOR");
	m_combo.AddString(L"REG_RESOURCE_REQUIREMENTS_LIST");
	m_combo.AddString(L"REG_QWORD");
	return TRUE;
}

int CNewVal::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	return 0;
}


void CNewVal::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString val,value,strType;
	GetDlgItemText(IDC_EDIT_VALNAME,val);
	GetDlgItemText(IDC_EDIT_VALUE,value);
	UpdateData();
	if(val.GetLength() <=0 || value.GetLength() <= 0){
		MessageBox(L"值不能为空");
		return;
	}

	int CurInx = m_combo.GetCurSel();
	if(CB_ERR == CurInx){
		MessageBox(L"当前未选择类型");
		return;
	}
	m_combo.GetLBText(CurInx,strType);

	C注册表工具Dlg* pMainWnd = (C注册表工具Dlg*)AfxGetMainWnd();

	//获取键路径
	HTREEITEM ht;
	ht = pMainWnd->m_regTree.GetSelectedItem();
	CString regPath;
	regPath.Format(L"\\%s",pMainWnd->m_regTree.GetItemText(ht));
	CString tmp;
	while(1){
		ht = pMainWnd->m_regTree.GetParentItem(ht);
		if(ht != NULL){
			tmp = regPath;
			regPath.Format(L"\\%s%s",pMainWnd->m_regTree.GetItemText(ht) , tmp);
		}else{
			break;
		}
	}
	pMainWnd->m_statusbar.SetPaneText(0,regPath);
	int subInx = regPath.Find(L'\\',1);
	CString RootKey = regPath.Left(subInx);
	RootKey.Replace(L"\\",L"");
	regPath = regPath.Right(regPath.GetLength()-subInx-1);

	int Curkey;
	if(L"HKEY_CLASSES_ROOT" == RootKey)
		Curkey = 0;
	else if(L"HKEY_CURRENT_CONFIG" == RootKey)
		Curkey = 1;
	else if(L"HKEY_CURRENT_USER" == RootKey)
		Curkey = 2;
	else if(L"HKEY_LOCAL_MACHINE" == RootKey)
		Curkey = 3;
	else if(L"HKEY_USERS" == RootKey)
		Curkey = 4;
	else
		return;

	if(Curkey <0 && Curkey >4)
		return;

	if(regPath == L"" || regPath == L"\\")
	{
		MessageBox(L"错误,子键路径不能为空");
		return;
	}

	HKEY key;
	if(ERROR_SUCCESS != RegOpenKeyEx(pMainWnd->RootKeys[Curkey],regPath,0,KEY_ALL_ACCESS,&key))
	{
		MessageBox(L"打开注册表失败!");
		return;
	}
	DWORD dwType=-1;
	if(L"REG_NONE" == strType)
		dwType=0;
	else if(L"REG_SZ" == strType)
		dwType=1;
	else if(L"REG_EXPAND_SZ" == strType)
		dwType=2;
	else if(L"REG_BINARY" == strType)
		dwType=3;
	else if(L"REG_DWORD" == strType)
		dwType=4;
	else if(L"REG_DWORD_BIG_ENDIAN" == strType)
		dwType=5;
	else if(L"REG_LINK" == strType)
		dwType=6;
	else if(L"REG_MULTI_SZ" == strType)
		dwType=7;
	else if(L"REG_RESOURCE_LIST" == strType)
		dwType=8;
	else if(L"REG_FULL_RESOURCE_DESCRIPTOR" == strType)
		dwType=9;
	else if(L"REG_RESOURCE_REQUIREMENTS_LIST" == strType)
		dwType=10;
	else if(L"REG_QWORD" == strType)
		dwType=11;

	if(dwType == -1)
		return;


	if(ERROR_SUCCESS != RegSetValueEx(key,val,0,dwType,(BYTE*)value.GetBuffer(value.GetLength()),value.GetLength()*sizeof(wchar_t)))
		MessageBox(L"创建值失败");
	
	//刷新值
	int SearchInx=0,Inx=0;
	wchar_t nameBuf[256]={0},TypeBuf[256]={0},valBuf[256]={0};
	DWORD dwNameSize=256,dwValSize=256;

	pMainWnd->m_regList.DeleteAllItems();
	while(ERROR_SUCCESS == RegEnumValue(key,SearchInx,nameBuf,&dwNameSize,NULL,&dwType,(BYTE*)valBuf,&dwValSize))
	{
		if(!nameBuf || wcslen(nameBuf)==0){
			memset(nameBuf,0,256);
			wmemcpy(nameBuf,L"默认值",wcslen(L"默认值"));
		}
		pMainWnd->m_regList.InsertItem(Inx,nameBuf);
		pMainWnd->m_regList.SetItemText(Inx,2,valBuf);
		memset(TypeBuf,0,256);
		switch(dwType)
		{
		case 0:
			wmemcpy(TypeBuf,L"REG_NONE",wcslen(L"REG_NONE"));
			break;
		case 1:
			wmemcpy(TypeBuf,L"REG_SZ",wcslen(L"REG_SZ"));
			break;
		case 2:
			wmemcpy(TypeBuf,L"REG_EXPAND_SZ",wcslen(L"REG_EXPAND_SZ"));
			break;
		case 3:
			wmemcpy(TypeBuf,L"REG_BINARY",wcslen(L"REG_BINARY"));
			break;
		case 4:
			wmemcpy(TypeBuf,L"REG_DWORD",wcslen(L"REG_DWORD"));
			break;
		case 5:
			wmemcpy(TypeBuf,L"REG_DWORD_BIG_ENDIAN",wcslen(L"REG_DWORD_BIG_ENDIAN"));
			break;
		case 6:
			wmemcpy(TypeBuf,L"REG_LINK",wcslen(L"REG_LINK"));
			break;
		case 7:
			wmemcpy(TypeBuf,L"REG_MULTI_SZ",wcslen(L"REG_MULTI_SZ"));
			break;
		case 8:
			wmemcpy(TypeBuf,L"REG_RESOURCE_LIST",wcslen(L"REG_RESOURCE_LIST"));
			break;
		case 9:
			wmemcpy(TypeBuf,L"REG_FULL_RESOURCE_DESCRIPTOR",wcslen(L"REG_FULL_RESOURCE_DESCRIPTOR"));
			break;
		case 10:
			wmemcpy(TypeBuf,L"REG_RESOURCE_REQUIREMENTS_LIST",wcslen(L"REG_RESOURCE_REQUIREMENTS_LIST"));
			break;
		case 11:
			wmemcpy(TypeBuf,L"REG_QWORD",wcslen(L"REG_QWORD"));
			break;
		default:
			break;
		}
		pMainWnd->m_regList.SetItemText(Inx,1,TypeBuf);

		Inx++;
		SearchInx++;
		dwNameSize=256;
		dwValSize=256;
	}
	RegCloseKey(key);
	CDialogEx::OnOK();
}
