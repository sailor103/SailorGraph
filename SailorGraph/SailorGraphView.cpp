
// SailorGraphView.cpp : CSailorGraphView ���ʵ��
//

#include "stdafx.h"
#include "SailorGraph.h"

#include "SailorGraphDoc.h"
#include "SailorGraphView.h"
// ----------�Լ���ӵ�ͷ�ļ�--------
#include "4PY.h"//����ƽ�ƵĶԻ���
#include "4FS.h"//���÷����ĶԻ���
#include "4XZ.h"//����ѡ��ĶԻ���
#include "SetTing.h"
#include "Tips.h"
#include "S1GraphLine.h"
#include "S1GraphCircle.h"
#include "S1GraphRect.h"
#include "S1GraphDbx.h"
#include "S2DDALine.h"
#include "S2BreLine.h"
#include "S2DDACircle.h"
#include "S2BreCircle.h"
#include "S2MidCircle.h"
#include "S4GraphDbx.h"
#include "S5GraphLine.h"
#include "S5GraphDbx.h"
#include "S6GraphPt.h"
// --------------------------------------

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSailorGraphView

IMPLEMENT_DYNCREATE(CSailorGraphView, CView)

BEGIN_MESSAGE_MAP(CSailorGraphView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSailorGraphView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_1_Line, &CSailorGraphView::On1Line)
	ON_COMMAND(ID_EDIT_UNDO, &CSailorGraphView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CSailorGraphView::OnUpdateEditUndo)
	ON_COMMAND(ID_FILE_SAVE, &CSailorGraphView::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CSailorGraphView::OnFileOpen)
	ON_COMMAND(ID_SETTING, &CSailorGraphView::OnSetting)
	ON_COMMAND(ID_1_CIRCLE, &CSailorGraphView::On1Circle)
	ON_COMMAND(ID_1_RECT, &CSailorGraphView::On1Rect)
	ON_UPDATE_COMMAND_UI(ID_SETTING, &CSailorGraphView::OnUpdateSetting)
	ON_WM_CLOSE()
	ON_COMMAND(ID_2_DDA, &CSailorGraphView::On2Dda)
	ON_COMMAND(ID_2_BRELine, &CSailorGraphView::On2Breline)
	ON_COMMAND(ID_2_ZengLiang, &CSailorGraphView::On2Zengliang)
	ON_COMMAND(ID_2_BRECIR, &CSailorGraphView::On2Brecir)
	ON_COMMAND(ID_2_ZhongDian, &CSailorGraphView::On2Zhongdian)
	ON_COMMAND(ID_ONSELECT, &CSailorGraphView::OnOnselect)
	ON_UPDATE_COMMAND_UI(ID_ONSELECT, &CSailorGraphView::OnUpdateOnselect)
	ON_COMMAND(ID_DBX, &CSailorGraphView::OnDbx)

	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_3_BXG, &CSailorGraphView::On3Bxg)
	ON_COMMAND(ID_3_SMXZZ, &CSailorGraphView::On3Smxzz)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_4_DBX, &CSailorGraphView::On4Dbx)
	ON_COMMAND(ID_PY, &CSailorGraphView::OnPy)
	ON_COMMAND(ID_4_XZ, &CSailorGraphView::On4Xz)
	ON_COMMAND(ID_4_FS, &CSailorGraphView::On4Fs)
	ON_COMMAND(ID_5_DrawLine, &CSailorGraphView::On5Drawline)
	ON_COMMAND(ID_5_Cohen_Sutherland, &CSailorGraphView::On5CohenSutherland)
	ON_COMMAND(ID_5_LiangBarsky, &CSailorGraphView::On5Liangbarsky)
	ON_COMMAND(ID_5_DrawSbx, &CSailorGraphView::On5Drawsbx)
	ON_COMMAND(ID_5_CJDBX, &CSailorGraphView::On5Cjdbx)
	ON_COMMAND(ID_6_Berier, &CSailorGraphView::On6Berier)
	ON_COMMAND(ID_6_BYT, &CSailorGraphView::On6Byt)
END_MESSAGE_MAP()

//----------------����Զ������------------------------
SGraphBasic *pBase;//�������ָ��
int mark=0;//�������״̬
int isClick=0;//����Ƿ�������״̬����
int isSelect=0;//��¼�Ƿ���ѡ��״̬
int isDbc=0;//����һ���������εı���
int isseed=0;//����������
int is2D=0;//��Ƕ�ά�任
CPoint ps,pe;//ѡ����¼��
int C_S;//���Cohen_Sutherland����ֱ��
int L_B;//���Liang_Barsky����ֱ��
int dbx_cj;//��Ƕ���βü�
int isBer;//���berier���ߵĻ���
S1GraphLine tempLine;
S1GraphCircle temp1Circle;
S1GraphRect   temp1Rect;
S1GraphDbx    temp1dbx;
S2DDALine      temp2dda;
S2BreLine        temp2brel;
S2DDACircle   temp2dcir;
S2BreCircle     temp2bcir;
S2MidCircle    temp2mcir;
S4GraphDbx   temp4dbx;
S5GraphLine   temp5line;
S5GraphDbx   temp5dbx;
S6GraphPt       temp6pt;
int m_ps=1;
int m_with=1;
COLORREF m_color=RGB(0,0,0);

//---------------------------------------------------------


// CSailorGraphView ����/����

CSailorGraphView::CSailorGraphView()
{
	// TODO: �ڴ˴���ӹ������

}

CSailorGraphView::~CSailorGraphView()
{
// 	if (isClick==1)
// 	{
// 		if (!(pBase->isEqual()))
// 		{
//              CTips tipDlg;
// 			 if (tipDlg.DoModal()==IDOK)
// 			 {
// 				 pBase->OnFileSave();
// 			 }
// 		}
// 	}
}

BOOL CSailorGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSailorGraphView ����

void CSailorGraphView::OnDraw(CDC* pDC)
{
	CSailorGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if (isClick==1)
	{
		pBase->DrawGraph(pDC);
	}
	if (isDbc==1)
	{
		pDC->TextOut(240,30,_T("�����������ʼ��ͼ���������Ҽ�ֹͣ��ͼ"));
		pDC->TextOut(240,50,_T("����ʱ����ѡ��˵��е�  ѡ�񹤾�  ����ͼ��ѡ��"));
	}
	if (isseed==1)
	{
		pDC->TextOut(240,70,_T("˫��ͼ����Ϊ����"));
	}
	if (is2D==1)
	{
		CPen pen(0,1,RGB(0,0,0));
		pDC->SelectObject(pen);
		pDC->MoveTo(0,350);
		pDC->LineTo(1500,350);
		pDC->MoveTo(600,0);
		pDC->LineTo(600,1200);
		pen.DeleteObject();
	}
	
}


// CSailorGraphView ��ӡ


void CSailorGraphView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSailorGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSailorGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSailorGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CSailorGraphView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSailorGraphView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CSailorGraphView ���

#ifdef _DEBUG
void CSailorGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CSailorGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSailorGraphDoc* CSailorGraphView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSailorGraphDoc)));
	return (CSailorGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CSailorGraphView ��Ϣ�������

void CSailorGraphView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (isClick==1&&isSelect==0&&C_S!=1&&L_B!=1&&dbx_cj!=1)
	{
		SetCapture();
		RECT rect;
		GetClientRect(&rect);
		ClientToScreen(&rect);
		ClipCursor(&rect);
		mark=1;
	    pBase->OnLButtonDown(nFlags,point);
	}
	if (isSelect==1||C_S==1||L_B==1||dbx_cj==1)
	{
		ps=point;
		pe=point;
		mark=1;
	}
	if (isClick==2)
	{
		SetCapture();
		RECT rect;
		GetClientRect(&rect);
		ClientToScreen(&rect);
		ClipCursor(&rect);
		mark=1;
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CSailorGraphView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (isClick==1&&isSelect==0&&C_S!=1&&L_B!=1&&dbx_cj!=1)
	{
		SetCursor(LoadCursor(NULL,IDC_CROSS));//���ù��Ϊ��+������
		if (mark==1)
		{
			pBase->OnMouseMove(nFlags,point);
		}
	}
	if (isSelect==1||C_S==1||L_B==1||dbx_cj==1)
	{
		if (mark==1)
		{
			CClientDC dc(this);
			//���û���
			CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//����͸����ˢ
			CPen pen_v(2,1,RGB(0,0,0));//������������
			//ѡ�񻭱�
			dc.SelectObject(pen_v);
			dc.SelectObject(pBrush);
			//��ͼ
			dc.SetROP2(R2_NOTXORPEN);
			dc.Rectangle(ps.x,ps.y,pe.x,pe.y);
			dc.Rectangle(ps.x,ps.y,point.x,point.y);
			pe=point;
			//ɾ������
			pen_v.DeleteObject();
			pBrush->DeleteObject();
		}
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CSailorGraphView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (isClick==1&&isSelect==0&&isDbc==0&&C_S!=1&&L_B!=1&&dbx_cj!=1)
	{
		ReleaseCapture();
		ClipCursor(NULL);
		pBase->OnLButtonUp(nFlags,point);
		mark=0;
	}
	if (isDbc==1)
	{
		ReleaseCapture();
		ClipCursor(NULL);
		pBase->OnLButtonUp(nFlags,point);
	}
	if (isSelect==1)
	{
		mark=0;
		Invalidate();
		UpdateWindow();
		pBase->OnSelect(ps,point);
		CDC *pDC;
		pDC=this->GetDC();
		pBase->DrawGraph(pDC);
		ReleaseDC(pDC);
	}
	if (C_S==1)
	{
		mark=0;
		CDC *pDC=GetDC();
		if (ps.x>point.x||ps.y>point.y)
		{
			CPoint t;
			t=ps;
			ps=point;
			point=t;
		}
		pBase->C_S(ps,point,pDC);
		ReleaseDC(pDC);
		Invalidate();
		UpdateWindow();
	}
	if (L_B==1)
	{
		mark=0;
		CDC *pDC=GetDC();
		if (ps.x>point.x||ps.y>point.y)
		{
			CPoint t;
			t=ps;
			ps=point;
			point=t;
		}
		pBase->L_B(ps,point,pDC);
		ReleaseDC(pDC);
		Invalidate();
		UpdateWindow();
	}
	if (dbx_cj==1)
	{
		mark=0;
		CDC *pDC=GetDC();
		if (ps.x>point.x||ps.y>point.y)
		{
			CPoint t;
			t=ps;
			ps=point;
			point=t;
		}
		pBase->L_B(ps,point,pDC);
		ReleaseDC(pDC);
		Invalidate();
		UpdateWindow();
	}

	CView::OnLButtonUp(nFlags, point);
}

void CSailorGraphView::OnEditUndo()
{
	// TODO: �ڴ���������������
	pBase->OnEditUndo();
	Invalidate();
    UpdateWindow();
}

void CSailorGraphView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (isClick==1)
	{
		pBase->OnUpdateEditUndo(pCmdUI);
	}
	else
		pCmdUI->Enable(FALSE);
	
}
//�����ļ�ģ��
void CSailorGraphView::OnFileSave()
{
	// TODO: �ڴ���������������
	if (isClick==1)
	{
		pBase->OnFileSave();
	}
	else
		MessageBox(_T("�Բ�����û�ж��ļ����й����ģ�"),_T("��ʾ"),MB_ICONINFORMATION);

}
//���ļ�ģ��
void CSailorGraphView::OnFileOpen()
{
	// TODO: �ڴ���������������
	CFileDialog saveDlg(TRUE);
	CString pathname;//·��
	CString ext;
	if (saveDlg.DoModal()==IDOK)
	{
		isClick=1;//�趨�ɵ��״̬
		isDbc=0;//���Ƕ����
		pathname=saveDlg.GetPathName();
		ext=saveDlg.GetFileExt();
		if (ext=="1line")
		{
			tempLine.getView(this);
			pBase=&tempLine;	
		}
		if (ext=="1cir")
		{
			temp1Circle.getView(this);
			pBase=&temp1Circle;
		}
		if (ext=="1rec")
		{
			temp1Rect.getView(this);
			pBase=&temp1Rect;
		}
		if (ext=="2dda")
		{
			temp2dda.getView(this);
			pBase=&temp2dda;
		}
		if (ext=="2brel")
		{
			temp2brel.getView(this);
			pBase=&temp2brel;
		}
		if (ext=="2ddac")
		{
			temp2dcir.getView(this);
			pBase=&temp2dcir;
		}
		if (ext=="2brec")
		{
			temp2bcir.getView(this);
			pBase=&temp2bcir;
		}
		if (ext=="2midc")
		{
			temp2mcir.getView(this);
			pBase=&temp2mcir;
		}
		if (ext=="dbc")
		{
			temp1dbx.getView(this);
			pBase=&temp1dbx;
			isDbc=1;
		}
		if (ext=="4dbc")
		{
			temp4dbx.getView(this);
			pBase=&temp4dbx;
			isDbc=1;
		}
		if (ext=="5line")
		{
			temp5line.getView(this);
			pBase=&temp5line;
		}
		if (ext=="5dbx")
		{
			temp5line.getView(this);
			pBase=&temp5line;
		}
		if (ext=="bez")
		{
			temp6pt.getView(this);
			pBase=&temp6pt;
		}
		pBase->OnFileOpen(pathname);
		
	}

	Invalidate();
	UpdateWindow();
}

void CSailorGraphView::OnSetting()//������������
{
	// TODO: �ڴ���������������
	CSetTing setDlg;
	if (setDlg.DoModal()==IDOK)
	{
		m_ps=setDlg.m_ps;
		m_with=setDlg.m_With;
		m_color=setDlg.m_color;
	}
	else
	{
		m_ps=1;
		m_with=1;
		m_color=RGB(0,0,0);
	}	
	pBase->getSeting(m_ps,m_with,m_color);
}

void CSailorGraphView::OnUpdateSetting(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(isClick);
}


void CSailorGraphView::On1Line()
{
	// TODO: �ڴ���������������
	tempLine.getView(this);
	pBase=&tempLine;
	isClick=1;
	isSelect=0;
	isDbc=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

}
void CSailorGraphView::On1Circle()
{
	// TODO: �ڴ���������������
	temp1Circle.getView(this);
	pBase=&temp1Circle;
	isClick=1;
	isSelect=0;
	isDbc=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

}
//���ƾ��ε���Ӧ����
void CSailorGraphView::On1Rect()
{
	// TODO: �ڴ���������������
	temp1Rect.getView(this);
	pBase=&temp1Rect;
	isClick=1;
	isSelect=0;
	isDbc=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

}
//�����������ε���Ӧ����
void CSailorGraphView::OnDbx()
{
	// TODO: �ڴ���������������
	temp1dbx.getView(this);
	pBase=&temp1dbx;
	isClick=1;
	isDbc=1;
	isSelect=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

	CDC *pdc;
	pdc=GetDC();
	pdc->TextOut(240,30,_T("�����������ʼ��ͼ���������Ҽ�ֹͣ��ͼ"));
	pdc->TextOut(240,50,_T("����ʱ����ѡ��˵��е�  ѡ�񹤾�  ����ͼ��ѡ��"));
	ReleaseDC(pdc);
}

void CSailorGraphView::On2Dda()
{
	// TODO: �ڴ���������������
	temp2dda.getView(this);
	pBase=&temp2dda;
	isClick=1;
	isSelect=0;
	isDbc=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

}

void CSailorGraphView::On2Breline()
{
	// TODO: �ڴ���������������
	temp2brel.getView(this);
	pBase=&temp2brel;
	isClick=1;
	isSelect=0;
	isDbc=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

}

void CSailorGraphView::On2Zengliang()
{
	// TODO: �ڴ���������������
    temp2dcir.getView(this);
	pBase=&temp2dcir;
	isClick=1;
	isSelect=0;
	isDbc=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

}

void CSailorGraphView::On2Brecir()
{
	// TODO: �ڴ���������������
	temp2bcir.getView(this);
	pBase=&temp2bcir;
	isClick=1;
	isSelect=0;
	isDbc=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

}

void CSailorGraphView::On2Zhongdian()
{
	// TODO: �ڴ���������������
	temp2mcir.getView(this);
	pBase=&temp2mcir;
	isClick=1;
	isSelect=0;
	isDbc=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

}

void CSailorGraphView::OnOnselect()
{
	// TODO: �ڴ���������������
	isSelect=1;
}

void CSailorGraphView::OnUpdateOnselect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(isClick);
}

//�����Ҽ���Ӧ����
void CSailorGraphView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if (isDbc==1)
    {
		pBase->OnRButtonDown(nFlags,point);
		mark=0;
    }
	if (isBer==1)
	{
		pBase->OnRButtonDown(nFlags,point);
		mark=0;
	}
	CView::OnRButtonDown(nFlags, point);
}

void CSailorGraphView::On3Bxg()//�����ɨ�������
{
	// TODO: �ڴ���������������
	if (isSelect!=1)
	{
		AfxMessageBox(_T("������ѡ��Ҫ����ͼ��"));
	}
	else
	{
		CDC *pDC=GetWindowDC();
		pBase->BXG(pDC);
		ReleaseDC(pDC);
	}

}

void CSailorGraphView::On3Smxzz()//ɨ�����������
{
	// TODO: �ڴ���������������
	if (isSelect!=1)
	{
		AfxMessageBox(_T("������ѡ��Ҫ����ͼ��"));
	}
	else
	{
		CDC *pDC=GetWindowDC();
		pDC->TextOut(240,70,_T("˫��ͼ����Ϊ����"));
		isseed=1;
	}
}

void CSailorGraphView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonDblClk(nFlags, point);
	if (isseed==1)
	{
        CDC *pDC=GetWindowDC();
		pBase->seedline(point,pDC);
		ReleaseDC(pDC);
	}
}

void CSailorGraphView::On4Dbx()
{
	// TODO: �ڴ���������������
	temp4dbx.getView(this);
	pBase=&temp4dbx;
	isClick=1;
	isDbc=1;
	isSelect=0;
	is2D=1;
	C_S=0;
	L_B=0;
	dbx_cj=0;

	CDC *pdc;
	pdc=GetDC();
	pdc->TextOut(240,30,_T("�����������ʼ��ͼ���������Ҽ�ֹͣ��ͼ"));
	pdc->TextOut(240,50,_T("����ʱ����ѡ��˵��е�  ѡ�񹤾�  ����ͼ��ѡ��"));
	pdc->MoveTo(0,350);
	pdc->LineTo(1500,350);
	pdc->MoveTo(600,0);
	pdc->LineTo(600,1200);
	ReleaseDC(pdc);
}

void CSailorGraphView::OnPy()//ƽ�Ʊ任
{
	// TODO: �ڴ���������������
	if (isSelect!=1)
	{
		AfxMessageBox(_T("������ѡ��Ҫƽ�Ƶ�ͼ��"));
	}
	else
	{
		CDC *pDC=GetDC();

        int x,y;
		C4PY pyDlg;
		if (pyDlg.DoModal()==IDOK)
		{
			UpdateData(TRUE);
			if (pyDlg.m_x_l)
			{
				pyDlg.m_x=-1*pyDlg.m_x;
			}
			if (pyDlg.m_y_u)
			{
				pyDlg.m_y=-1*pyDlg.m_y;
			}
			x=pyDlg.m_x;
			y=pyDlg.m_y;
			pBase->PY(x,y,pDC);
		}
		
		ReleaseDC(pDC);
		Invalidate();
		UpdateWindow();
	}
	
}

void CSailorGraphView::On4Xz()//��ת�任
{
	// TODO: �ڴ���������������
	if (isSelect!=1)
	{
		AfxMessageBox(_T("������ѡ��Ҫ��ת��ͼ��"));
	}
	else
	{	
		CDC *pDC=GetDC();
		C4XZ xzDlg;
		if (xzDlg.DoModal()==IDOK)
		{
			UpdateData(TRUE);
			 pBase->XZ(xzDlg.m_jd,pDC);
		}
       
		ReleaseDC(pDC);
		Invalidate();
		UpdateWindow();
	}
}

void CSailorGraphView::On4Fs()
{
	// TODO: �ڴ���������������
	if (isSelect!=1)
	{
		AfxMessageBox(_T("������ѡ��Ҫ������ͼ��"));
	}
	else
	{
		CDC *pDC=GetDC();
		C4FS FSDlg;
		if (FSDlg.DoModal()==IDOK)
		{
			UpdateData(TRUE);
            pBase->FS(FSDlg.m_x,FSDlg.m_y,pDC);
		}
	
		ReleaseDC(pDC);
		Invalidate();
		UpdateWindow();
	}
	
}

void CSailorGraphView::On5Drawline()
{
	// TODO: �ڴ���������������
	temp5line.getView(this);
	pBase=&temp5line;
	isClick=1;
	isSelect=0;
	isDbc=0;
	is2D=0;
	C_S=0;
	L_B=0;
	isseed=0;
	dbx_cj=0;


}

void CSailorGraphView::On5CohenSutherland()//Cohen_Sutherland�����㷨
{
	// TODO: �ڴ���������������
	if (isClick!=1)
	{
		AfxMessageBox(_T("���Ȼ���ֱ��"));
	}
	else
	{
		isDbc=0;
		is2D=0;
		isseed=0;
		L_B=0;
		C_S=1;
		dbx_cj=0;

	}
	
}

void CSailorGraphView::On5Liangbarsky()
{
	// TODO: �ڴ���������������
	if (isClick!=1)
	{
		AfxMessageBox(_T("���Ȼ���ֱ��"));
	}
	else
	{
		isDbc=0;
		is2D=0;
		isseed=0;
		L_B=1;
		C_S=0;
		dbx_cj=0;

	}
}

void CSailorGraphView::On5Drawsbx()//���ƶ���εĺ���
{
	// TODO: �ڴ���������������
	isClick=1;
	isSelect=0;
	isDbc=0;
	is2D=0;
	C_S=0;
	L_B=0;
	isseed=0;
	dbx_cj=0;
// 	temp5dbx.getView(this);
// 	pBase=&temp5dbx;
	temp5line.getView(this);
	pBase=&temp5line;
// 	CDC *pdc;
// 	pdc=GetDC();
// 	pdc->TextOut(240,30,_T("�����������ʼ��ͼ���������Ҽ�ֹͣ��ͼ"));
// 	pdc->TextOut(240,50,_T("����ʱ����ѡ��˵��е�  ѡ�񹤾�  ����ͼ��ѡ��"));
// 	ReleaseDC(pdc);
}

void CSailorGraphView::On5Cjdbx()//�Զ���ν��вü��ĺ���
{
	// TODO: �ڴ���������������
	if (isClick!=1)
	{
		AfxMessageBox(_T("���Ȼ��ƶ����"));
	}
	else
	{
		isDbc=0;
		is2D=0;
		isseed=0;
		L_B=0;
		C_S=0;
		dbx_cj=1;
	}
}

void CSailorGraphView::On6Berier()//Berier����
{
	// TODO: �ڴ���������������
	isClick=1;
	isSelect=0;
	isDbc=0;
	is2D=0;
	C_S=0;
	L_B=0;
	isseed=0;
	dbx_cj=0;
	temp6pt.getView(this);
	pBase=&temp6pt;
	isBer=1;

}

void CSailorGraphView::On6Byt()//B��������
{
	// TODO: �ڴ���������������
}
