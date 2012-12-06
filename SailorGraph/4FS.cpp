// 4FS.cpp : 实现文件
//

#include "stdafx.h"
#include "SailorGraph.h"
#include "4FS.h"


// C4FS 对话框

IMPLEMENT_DYNAMIC(C4FS, CDialog)

C4FS::C4FS(CWnd* pParent /*=NULL*/)
	: CDialog(C4FS::IDD, pParent)
	, m_x(0)
	, m_y(0)
{

}

C4FS::~C4FS()
{
}

void C4FS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FS_X, m_x);
	DDX_Text(pDX, IDC_EDIT_FS_Y, m_y);
}


BEGIN_MESSAGE_MAP(C4FS, CDialog)
END_MESSAGE_MAP()


// C4FS 消息处理程序
