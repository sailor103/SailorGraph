
// SailorGraphDoc.cpp : CSailorGraphDoc ���ʵ��
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


// CSailorGraphDoc ����/����

CSailorGraphDoc::CSailorGraphDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CSailorGraphDoc::~CSailorGraphDoc()
{
}

BOOL CSailorGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CSailorGraphDoc ���л�

void CSailorGraphDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CSailorGraphDoc ���

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


// CSailorGraphDoc ����

