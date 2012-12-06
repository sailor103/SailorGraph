// Tips.cpp : 实现文件
//

#include "stdafx.h"
#include "SailorGraph.h"
#include "Tips.h"


// CTips 对话框

IMPLEMENT_DYNAMIC(CTips, CDialog)

CTips::CTips(CWnd* pParent /*=NULL*/)
	: CDialog(CTips::IDD, pParent)
{

}

CTips::~CTips()
{
}

void CTips::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTips, CDialog)
END_MESSAGE_MAP()


// CTips 消息处理程序
