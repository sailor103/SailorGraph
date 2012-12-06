
// SailorGraphDoc.cpp : CSailorGraphDoc 类的实现
//

#include "stdafx.h"
#include "SailorGraph.h"

#include "SailorGraphDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSailorGraphDoc

IMPLEMENT_DYNCREATE(CSailorGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CSailorGraphDoc, CDocument)
END_MESSAGE_MAP()


// CSailorGraphDoc 构造/析构

CSailorGraphDoc::CSailorGraphDoc()
{
	// TODO: 在此添加一次性构造代码

}

CSailorGraphDoc::~CSailorGraphDoc()
{
}

BOOL CSailorGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CSailorGraphDoc 序列化

void CSailorGraphDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CSailorGraphDoc 诊断

#ifdef _DEBUG
void CSailorGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSailorGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSailorGraphDoc 命令

