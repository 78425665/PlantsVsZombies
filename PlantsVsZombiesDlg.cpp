
// PlantsVsZombiesDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PlantsVsZombies.h"
#include "PlantsVsZombiesDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPlantsVsZombiesDlg 对话框



CPlantsVsZombiesDlg::CPlantsVsZombiesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLANTSVSZOMBIES_DIALOG, pParent)
	, is_no_cd(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlantsVsZombiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, is_no_cd);
}

BEGIN_MESSAGE_MAP(CPlantsVsZombiesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPlantsVsZombiesDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CPlantsVsZombiesDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CPlantsVsZombiesDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPlantsVsZombiesDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPlantsVsZombiesDlg 消息处理程序

BOOL CPlantsVsZombiesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPlantsVsZombiesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPlantsVsZombiesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPlantsVsZombiesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HANDLE CPlantsVsZombiesDlg::getProccessByTitle(CString title) {
	if (!hProcess) {
		HWND hwnd = ::FindWindow(NULL, title);
		if (!hwnd) {
			this->MessageBox(_T("未找到窗口：" + title));
			return 0;
		}
		DWORD pid = 0;
		GetWindowThreadProcessId(hwnd, &pid);

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
		if (!hProcess) {
			this->MessageBox(_T("打开进程失败"));
			return 0;
		}
	}
	return hProcess;
}

DWORD CPlantsVsZombiesDlg::ReadProcessMemory(int address, int size) {
	getProccessByTitle(_T("植物大战僵尸中文版"));
	DWORD bValue = 0;
	if (!::ReadProcessMemory(hProcess, (DWORD*)address, &bValue, size, NULL)) {
		this->MessageBox(_T("读取数据失败"));
	}
	return bValue;
}
void CPlantsVsZombiesDlg::WriteProcessMemory(int address, LPCVOID bValue, int size) {
	getProccessByTitle(_T("植物大战僵尸中文版"));
	BOOL result = FALSE;
	if (size < 4) {
		result = ::WriteProcessMemory(hProcess, (DWORD*)address, (UCHAR*)bValue, size, NULL);
	}
	else {
		result = ::WriteProcessMemory(hProcess, (DWORD*)address, bValue, size, NULL);
	}
	if (!result) {
		this->MessageBox(_T("写入数据失败"));
	}
}

/*
阳光+9999
*/
void CPlantsVsZombiesDlg::OnBnClickedOk()
{
	int addr[3] = { 0x006AA00C ,0x768, 0x5560 };
	DWORD bValue = this->ReadProcessMemory(addr[0]);
	bValue = this->ReadProcessMemory(bValue + addr[1]);
	DWORD old = this->ReadProcessMemory(bValue + addr[2]);

	
	unsigned int yValue = 9999 + old;
	this->WriteProcessMemory(bValue + addr[2], &yValue);
}


/*
金币+9999
*/
void CPlantsVsZombiesDlg::OnBnClickedButton1()
{
	int addr[3] = { 0x006AA00C ,0x82c, 0x28 };
	DWORD bValue = this->ReadProcessMemory(addr[0]);
	bValue = this->ReadProcessMemory(bValue + addr[1]);
	DWORD old = this->ReadProcessMemory(bValue + addr[2]);


	unsigned int yValue = 999 + old;
	this->WriteProcessMemory(bValue + addr[2], &yValue);
}


void CPlantsVsZombiesDlg::OnBnClickedCheck1()
{
	UpdateData();
	int addr = 0x487296;// 冷却跳转指令地址
	UCHAR data[2] = { 0x90, 0x90};//空操作指令: nop nop
	if (!this->is_no_cd) {
		data[0] = 0x7E;
		data[1] = 0x14;
	}
	this->WriteProcessMemory(addr, data, sizeof(data));
}

void CPlantsVsZombiesDlg::OnBnClickedButton2()
{
	/*
		push - 1				// 固定值
		push 2					// 植物类型，2=爆炸樱桃
		mov eax, 2				// 九宫格，y坐标（0-5）
		push 2					// 九宫格，x坐标（0-8）
		mov edx, [6AA00C]		
		mov edx, [edx + 768]
		push edx				// 通过基址+偏移计算得到的值，一定要有而且每次会变（用途未知）
		call 0040D120			// 放置植物函数
	*/
}
