#pragma once


// CTips �Ի���

class CTips : public CDialog
{
	DECLARE_DYNAMIC(CTips)

public:
	CTips(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTips();

// �Ի�������
	enum { IDD = IDD_DIALOG_SAVEORNOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
