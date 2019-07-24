
// ע�����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ע�����.h"
#include "ע�����Dlg.h"
#include "afxdialogex.h"
#include "NewKey.h"
#include "NewVal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cע�����Dlg �Ի���



Cע�����Dlg::Cע�����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cע�����Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cע�����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_REG, m_regTree);
	DDX_Control(pDX, IDC_LIST_REG, m_regList);
}

BEGIN_MESSAGE_MAP(Cע�����Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_OPENREG,OnOpenReg)
	ON_COMMAND(ID_OPENREG,OnRefreshReg)
	ON_COMMAND(ID_OPENREG,OnCloseReg)
	ON_COMMAND(ID_NEWKEY,OnNewKey)
	ON_COMMAND(ID_DELKEY,OnDelKey)
	ON_COMMAND(ID_REFRESHKEY,OnRefreshKey)
	ON_COMMAND(ID_NEWVAL,OnNewVal)
	ON_COMMAND(ID_DELVAL,OnDelVal)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_REG, &Cע�����Dlg::OnTvnSelchangedTreeReg)
	ON_NOTIFY(TVN_SELCHANGING, IDC_TREE_REG, &Cע�����Dlg::OnTvnSelchangingTreeReg)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_REG, &Cע�����Dlg::OnNMDblclkTreeReg)
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_TREE_REG, &Cע�����Dlg::OnNMRClickTreeReg)
	ON_MESSAGE(WM_ADDNEWKEY,&Cע�����Dlg::OnAddNewKey)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_REG, &Cע�����Dlg::OnNMRClickListReg)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// Cע�����Dlg ��Ϣ�������

BOOL Cע�����Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	DWORD dwStyle = GetWindowLong(m_regTree.m_hWnd,GWL_STYLE);
	dwStyle |= TVS_LINESATROOT | TVS_HASLINES | TVS_HASBUTTONS;
	SetWindowLong(m_regTree.m_hWnd,GWL_STYLE,dwStyle);
	m_regTree.SetIndent(10);
	m_regList.InsertColumn(0,_T("KEY"),LVCFMT_LEFT,70);
	m_regList.InsertColumn(1,_T("TYPE"),LVCFMT_LEFT,100);
	m_regList.InsertColumn(2,_T("VALUE"),LVCFMT_LEFT,350);

	m_htree[0]=m_regTree.InsertItem(_T("HKEY_CLASSES_ROOT"));
	m_htree[1]=m_regTree.InsertItem(_T("HKEY_CURRENT_CONFIG"));
	m_htree[2]=m_regTree.InsertItem(_T("HKEY_CURRENT_USER"));
	m_htree[3]=m_regTree.InsertItem(_T("HKEY_LOCAL_MACHINE"));
	m_htree[4]=m_regTree.InsertItem(_T("HKEY_USERS"));
	RootKeys[0]=HKEY_CLASSES_ROOT;
	RootKeys[1]=HKEY_CURRENT_CONFIG;
	RootKeys[2]=HKEY_CURRENT_USER;
	RootKeys[3]=HKEY_LOCAL_MACHINE;
	RootKeys[4]=HKEY_USERS;

	m_toolbar.Create(this);
	m_statusbar.Create(this);
	UINT sbn[] = {1001};
	m_statusbar.SetIndicators(sbn,1);
	m_statusbar.SetPaneInfo(0,0,SBPS_NORMAL ,400);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cע�����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cע�����Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cע�����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cע�����Dlg::OnOpenReg()
{
	//��ע����ȡ�������Ӽ�
	wchar_t valName[256],value[256];
	DWORD dwSubKeyNums,dwMaxSubKey,dwNameSize=256,dwValSize;
	
	for (int i = 0; i < 5; i++)
	{
		if(ERROR_SUCCESS == RegOpenKeyEx(RootKeys[i],_T(""),0,KEY_ALL_ACCESS,&keys[i]))
		{
			if(ERROR_SUCCESS == RegQueryInfoKey(keys[i],NULL,0,0,&dwSubKeyNums,&dwMaxSubKey,NULL,NULL,NULL,NULL,NULL,NULL))
			{
				for (int j = 0; j < dwSubKeyNums; j++)
				{
					if(ERROR_SUCCESS == RegEnumKeyEx(keys[i],j,valName,&dwNameSize,NULL,NULL,NULL,NULL))
					{
						m_regTree.InsertItem(TVIF_TEXT,valName,0,0,0,0,0,m_htree[i],0);
						dwNameSize=256;
					}
				}
			}
		}
		RegCloseKey(keys[i]);
		RegCloseKey(RootKeys[i]);
	}

	CRect rt;
	m_regTree.GetClientRect(&rt);
	InvalidateRect(rt);
}

void Cע�����Dlg::OnRefreshReg()
{}

void Cע�����Dlg::OnCloseReg()
{}

void Cע�����Dlg::OnTvnSelchangedTreeReg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void Cע�����Dlg::OnTvnSelchangingTreeReg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void Cע�����Dlg::OnNMDblclkTreeReg(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	HTREEITEM ht;
	ht = m_regTree.GetSelectedItem();
	CString regPath;
	regPath.Format(L"\\%s",m_regTree.GetItemText(ht));
	CString tmp;
	while(1){
		ht = m_regTree.GetParentItem(ht);
		if(ht != NULL){
			tmp = regPath;
			regPath.Format(L"\\%s%s",m_regTree.GetItemText(ht) , tmp);
		}else{
			break;
		}
	}
	m_statusbar.SetPaneText(0,regPath);
	int subInx = regPath.Find(L'\\',1);
	CString RootKey = regPath.Left(subInx);
	RootKey.Replace(L"\\",L"");
	regPath = regPath.Right(regPath.GetLength()-subInx-1);

	HKEY key;
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

	if(ERROR_SUCCESS != RegOpenKeyEx(RootKeys[Curkey],regPath,0,KEY_ALL_ACCESS,&key)){
		MessageBoxW(L"Open RootKey Fail!");
		return;
	}
	unsigned short SearchInx=0,Inx=0;
	wchar_t nameBuf[256]={0},TypeBuf[256]={0},valBuf[256]={0};
	DWORD dwSize = 256,dwKeyNums,dwKeyMaxNums,dwType,dwNameSize,dwValSize=256;
	if(ERROR_SUCCESS != RegQueryInfoKey(key,NULL,0,0,&dwKeyNums,&dwKeyMaxNums,0,0,0,0,0,0))
	{
		RegCloseKey(RootKeys[Curkey]);
		RegCloseKey(key);
		MessageBoxW(L"Query Key Info Fail!");
		return;
	}
	//m_regList.DeleteAllItems();
	ht = m_regTree.GetSelectedItem();

	while(m_regTree.ItemHasChildren(ht))
	{
		m_regTree.DeleteItem(m_regTree.GetChildItem(ht));
	}
	for (int j = 0; j < dwKeyNums; j++)
	{
		if(ERROR_SUCCESS == RegEnumKeyEx(key,j,nameBuf,&dwNameSize,0,NULL,NULL,NULL))
		{
			//m_regList.InsertItem(j,nameBuf);
			m_regTree.InsertItem(TVIF_TEXT,nameBuf,0,0,0,0,0,ht,NULL);
		}
		dwNameSize=256;
	}
	m_regList.DeleteAllItems();
	while(ERROR_SUCCESS == RegEnumValue(key,SearchInx,nameBuf,&dwNameSize,NULL,&dwType,(BYTE*)valBuf,&dwValSize))
	{
		if(!nameBuf || wcslen(nameBuf)==0){
			memset(nameBuf,0,256);
			wmemcpy(nameBuf,L"Ĭ��ֵ",wcslen(L"Ĭ��ֵ"));
		}
		m_regList.InsertItem(Inx,nameBuf);
		m_regList.SetItemText(Inx,2,valBuf);
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
		m_regList.SetItemText(Inx,1,TypeBuf);

		Inx++;
		SearchInx++;
		dwNameSize=256;
		dwValSize=256;
	}

	RegCloseKey(RootKeys[Curkey]);
	RegCloseKey(key);

}


void Cע�����Dlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������
}


void Cע�����Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

void Cע�����Dlg::OnNewKey(){
	CNewKey dlg;
	dlg.DoModal();

}

void Cע�����Dlg::OnDelKey(){
	CString regPath,substr;
	HTREEITEM curentItem,htTmp,parentItem;
	curentItem = m_regTree.GetSelectedItem();
	parentItem = m_regTree.GetParentItem(curentItem);
	substr=m_regTree.GetItemText(curentItem);
	//regPath.Format(L"\\%s",m_regTree.GetItemText(curentItem));
	while(1)
	{
		curentItem = m_regTree.GetParentItem(curentItem);
		if(!curentItem)
			break;
		regPath.Format(L"\\%s%s",m_regTree.GetItemText(curentItem),regPath);
	}
	CString RootKey = regPath.Left(regPath.Find(L"\\",1));
	RootKey.Replace(L"\\",L"");
	CString SubKey = regPath.Right(regPath.GetLength()-regPath.Find(L"\\",1)-1);
	
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
	
	HKEY key;

	if(ERROR_SUCCESS != RegOpenKeyEx(RootKeys[Curkey],SubKey,0,KEY_ALL_ACCESS,&key))
	{
		MessageBox(L"��ע���ʧ��!");
		return;
	}
	if(ERROR_SUCCESS != RegDeleteKey(key,substr))
		MessageBox(L"ɾ����ʧ��!");

	RegCloseKey(key);
	m_regTree.SelectItem(parentItem);
	OnRefreshKey();
}

void Cע�����Dlg::OnRefreshKey(){
	HTREEITEM ht;
	ht = m_regTree.GetSelectedItem();
	CString regPath;
	regPath.Format(L"\\%s",m_regTree.GetItemText(ht));
	CString tmp;
	while(1){
		ht = m_regTree.GetParentItem(ht);
		if(ht != NULL){
			tmp = regPath;
			regPath.Format(L"\\%s%s",m_regTree.GetItemText(ht) , tmp);
		}else{
			break;
		}
	}
	m_statusbar.SetPaneText(0,regPath);
	int subInx = regPath.Find(L'\\',1);
	CString RootKey = regPath.Left(subInx);
	RootKey.Replace(L"\\",L"");
	regPath = regPath.Right(regPath.GetLength()-subInx-1);

	HKEY key;
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
	
	if(ERROR_SUCCESS != RegOpenKeyEx(RootKeys[Curkey],regPath,0,KEY_ALL_ACCESS,&key)){
		MessageBoxW(L"Open RootKey Fail!");
		return;
	}
	unsigned short SearchInx=0,Inx=0;
	wchar_t nameBuf[256]={0},TypeBuf[256]={0},valBuf[256]={0};
	DWORD dwSize = 256,dwKeyNums,dwKeyMaxNums,dwType,dwNameSize,dwValSize=256;
	if(ERROR_SUCCESS != RegQueryInfoKey(key,NULL,0,0,&dwKeyNums,&dwKeyMaxNums,0,0,0,0,0,0))
	{
		RegCloseKey(RootKeys[Curkey]);
		RegCloseKey(key);
		MessageBoxW(L"Query Key Info Fail!");
		return;
	}
	//m_regList.DeleteAllItems();
	ht = m_regTree.GetSelectedItem();

	while(m_regTree.ItemHasChildren(ht))
	{
		m_regTree.DeleteItem(m_regTree.GetChildItem(ht));
	}
	for (int j = 0; j < dwKeyNums; j++)
	{
		if(ERROR_SUCCESS == RegEnumKeyEx(key,j,nameBuf,&dwNameSize,0,NULL,NULL,NULL))
		{
			//m_regList.InsertItem(j,nameBuf);
			m_regTree.InsertItem(TVIF_TEXT,nameBuf,0,0,0,0,0,ht,NULL);
		}
		dwNameSize=256;
	}
	m_regList.DeleteAllItems();
	while(ERROR_SUCCESS == RegEnumValue(key,SearchInx,nameBuf,&dwNameSize,NULL,&dwType,(BYTE*)valBuf,&dwValSize))
	{
		if(!nameBuf || wcslen(nameBuf)==0){
			memset(nameBuf,0,256);
			wmemcpy(nameBuf,L"Ĭ��ֵ",wcslen(L"Ĭ��ֵ"));
		}
		m_regList.InsertItem(Inx,nameBuf);
		m_regList.SetItemText(Inx,2,valBuf);
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
		m_regList.SetItemText(Inx,1,TypeBuf);

		Inx++;
		SearchInx++;
		dwNameSize=256;
		dwValSize=256;
	}
	RegCloseKey(key);
}

void Cע�����Dlg::OnNewVal(){

	// show Dialog
	CNewVal dlg;
	dlg.DoModal();
}

void Cע�����Dlg::OnDelVal(){
	//��ȡѡ����
	POSITION pt = m_regList.GetFirstSelectedItemPosition();
	int Inp = (int)pt;

	//ɾ��ָ����
	HTREEITEM ht;
	ht = m_regTree.GetSelectedItem();
	CString regPath;
	regPath.Format(L"\\%s",m_regTree.GetItemText(ht));
	CString tmp;
	while(1){
		ht = m_regTree.GetParentItem(ht);
		if(ht != NULL){
			tmp = regPath;
			regPath.Format(L"\\%s%s",m_regTree.GetItemText(ht) , tmp);
		}else{
			break;
		}
	}
	m_statusbar.SetPaneText(0,regPath);
	int subInx = regPath.Find(L'\\',1);
	CString RootKey = regPath.Left(subInx);
	RootKey.Replace(L"\\",L"");
	regPath = regPath.Right(regPath.GetLength()-subInx-1);

	HKEY key;
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

	if(ERROR_SUCCESS != RegOpenKeyEx(RootKeys[Curkey],regPath,0,KEY_ALL_ACCESS,&key))
	{
		MessageBox(L"��ע���ʧ��!");
		return;
	}

	CString val,temp;
	temp = m_regList.GetItemText(Inp-1,0);
	UpdateData();
	val.Format(L"%s\\%s",regPath,temp);
	if(ERROR_SUCCESS != RegDeleteValue(key,temp))
		MessageBox(L"ɾ��ʧ��!");
	RegCloseKey(key);
	OnRefreshKey();
}

void Cע�����Dlg::OnNMRClickTreeReg(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CMenu pMenu;
	POINT pt;
	GetCursorPos(&pt);
	pMenu.LoadMenuW(IDR_MENU2);
	CMenu* pSubMenu = pMenu.GetSubMenu(0);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN ,pt.x,pt.y,this);

}

LRESULT Cע�����Dlg::OnAddNewKey(WPARAM wParam,LPARAM lParam){
	CString *pstr = (CString*)lParam;
	wchar_t buf[256] ={0};
	memcpy(buf,pstr->GetBuffer(pstr->GetLength()),256);
	CString tmp,regPath;
	
	HTREEITEM curentItem;
	curentItem = m_regTree.GetSelectedItem();
	regPath.Format(L"\\%s",m_regTree.GetItemText(curentItem));
	while(1)
	{
		curentItem = m_regTree.GetParentItem(curentItem);
		if(!curentItem)
			break;
		regPath.Format(L"\\%s%s",m_regTree.GetItemText(curentItem),regPath);
	}
	CString RootKey = regPath.Left(regPath.Find(L"\\",1));
	RootKey.Replace(L"\\",L"");
	CString SubKey = regPath.Right(regPath.GetLength()-regPath.Find(L"\\",1)-1);
	
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
		return 1;
	
	HKEY key;
	DWORD dwOpenType;
	CString FullPath;
	FullPath.Format(L"%s\\%s",SubKey,buf);
	if(ERROR_SUCCESS != RegCreateKeyEx(RootKeys[Curkey],FullPath,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&key,&dwOpenType))
	{
		MessageBox(L"��ע���ʧ��!");
		return -1;
	}
	/*
	REG_CREATED_NEW_KEY			0x00000001L
	REG_OPENED_EXISTING_KEY     0x00000002L
	*/
	CString tmp1;
	tmp1.Format(L"��:[ %s ]�Ѵ���",buf);
	if(dwOpenType==0x00000002L){
		MessageBox(tmp1);
		RegCloseKey(key);
		return 1;
	}
	OnRefreshKey();
	return 0;
}

void Cע�����Dlg::OnNMRClickListReg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CMenu Menu,*pMenu;
	Menu.LoadMenuW(IDR_MENU3);
	pMenu = Menu.GetSubMenu(0);

	POINT pt;
	GetCursorPos(&pt);

	pMenu->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
}


void Cע�����Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(IDYES != MessageBoxW(L"ȷ���˳�������?",L"��ʾ��Ϣ",MB_YESNO))
		return;
	CDialogEx::OnClose();
}
