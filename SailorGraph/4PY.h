#pragma once


// C4PY �Ի���

class C4PY : public CDialog
{
	DECLARE_DYNAMIC(C4PY)

public:
	C4PY(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C4PY();

// �Ի�������
	enum { IDD = IDD_DIALOG_PY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
