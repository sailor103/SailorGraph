#pragma once


// C4FS �Ի���

class C4FS : public CDialog
{
	DECLARE_DYNAMIC(C4FS)

public:
	C4FS(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C4FS();

// �Ի�������
	enum { IDD = IDD_DIALOG_FS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_x;
	float m_y;
};
