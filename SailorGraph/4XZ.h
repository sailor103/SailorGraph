#pragma once


// C4XZ 对话框

class C4XZ : public CDialog
{
	DECLARE_DYNAMIC(C4XZ)

public:
	C4XZ(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C4XZ();

// 对话框数据
	enum { IDD = IDD_DIALOG_XZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_jd;
};
