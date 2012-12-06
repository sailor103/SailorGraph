#pragma once


// C4PY 对话框

class C4PY : public CDialog
{
	DECLARE_DYNAMIC(C4PY)

public:
	C4PY(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C4PY();

// 对话框数据
	enum { IDD = IDD_DIALOG_PY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_x;
	int m_y;
	int m_x_l;
	int m_x_r;
	int m_y_u;
	int m_y_d;
	afx_msg void OnBnClickedRadioPyXL();
	afx_msg void OnBnClickedRadioPyXR();
	afx_msg void OnBnClickedRadioPyYU();
	afx_msg void OnBnClickedRadioPyYD();
};
