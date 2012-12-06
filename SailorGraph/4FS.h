#pragma once


// C4FS 对话框

class C4FS : public CDialog
{
	DECLARE_DYNAMIC(C4FS)

public:
	C4FS(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C4FS();

// 对话框数据
	enum { IDD = IDD_DIALOG_FS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_x;
	float m_y;
};
