
// PlantsVsZombiesDlg.h: 头文件
//

#pragma once


// CPlantsVsZombiesDlg 对话框
class CPlantsVsZombiesDlg : public CDialogEx
{
// 构造
public:
	CPlantsVsZombiesDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLANTSVSZOMBIES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	HANDLE hProcess = 0;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	HANDLE getProccessByTitle(CString title);
	DWORD ReadProcessMemory(int address, int size = 4);
	void WriteProcessMemory(int address, LPCVOID bValue, int size = 4);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	BOOL is_no_cd;
	afx_msg void OnBnClickedButton2();
};
