// 4XZ.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SailorGraph.h"
#include "4XZ.h"


// C4XZ �Ի���

IMPLEMENT_DYNAMIC(C4XZ, CDialog)

C4XZ::C4XZ(CWnd* pParent /*=NULL*/)
	: CDialog(C4XZ::IDD, pParent)
	, m_jd(0)
{

}

C4XZ::~C4XZ()
{
}

void C4XZ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XZ, m_jd);
}


BEGIN_MESSAGE_MAP(C4XZ, CDialog)
END_MESSAGE_MAP()


// C4XZ ��Ϣ�������
