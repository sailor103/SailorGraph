#pragma once


// CTips 对话框

class CTips : public CDialog
{
	DECLARE_DYNAMIC(CTips)

public:
	CTips(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTips();

// 对话框数据
	enum { IDD = IDD_DIALOG_SAVEORNOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
