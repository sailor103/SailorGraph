#pragma once


// C4XZ �Ի���

class C4XZ : public CDialog
{
	DECLARE_DYNAMIC(C4XZ)

public:
	C4XZ(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C4XZ();

// �Ի�������
	enum { IDD = IDD_DIALOG_XZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_jd;
};
