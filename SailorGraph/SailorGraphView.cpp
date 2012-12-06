
// SailorGraphView.cpp : CSailorGraphView 类的实现
//

#include "stdafx.h"
#include "SailorGraph.h"

#include "SailorGraphDoc.h"
#include "SailorGraphView.h"
// ----------自己添加到头文件--------
#include "4PY.h"//设置平移的对话框
#include "4FS.h"//设置放缩的对话框
#include "4XZ.h"//设置选择的对话框
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
	// 标准打印命令
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

//----------------添加自定义变量------------------------
SGraphBasic *pBase;//定义基类指针
int mark=0;//标记鼠标的状态
int isClick=0;//标记是否进行鼠标状态捕获
int isSelect=0;//记录是否是选择状态
int isDbc=0;//定义一个任意多边形的变量
int isseed=0;//标记种子填充
int is2D=0;//标记二维变换
CPoint ps,pe;//选择框记录点
int C_S;//标记Cohen_Sutherland剪裁直线
int L_B;//标记Liang_Barsky剪裁直线
int dbx_cj;//标记多边形裁剪
int isBer;//标记berier曲线的绘制
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


// CSailorGraphView 构造/析构

CSailorGraphView::CSailorGraphView()
{
	// TODO: 在此处添加构造代码

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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSailorGraphView 绘制

void CSailorGraphView::OnDraw(CDC* pDC)
{
	CSailorGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (isClick==1)
	{
		pBase->DrawGraph(pDC);
	}
	if (isDbc==1)
	{
		pDC->TextOut(240,30,_T("点击鼠标左键开始绘图，点击鼠标右键停止绘图"));
		pDC->TextOut(240,50,_T("操作时请先选择菜单中的  选择工具  进行图形选中"));
	}
	if (isseed==1)
	{
		pDC->TextOut(240,70,_T("双击图形作为种子"));
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


// CSailorGraphView 打印


void CSailorGraphView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSailorGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSailorGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSailorGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CSailorGraphView 诊断

#ifdef _DEBUG
void CSailorGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CSailorGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSailorGraphDoc* CSailorGraphView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSailorGraphDoc)));
	return (CSailorGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CSailorGraphView 消息处理程序

void CSailorGraphView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isClick==1&&isSelect==0&&C_S!=1&&L_B!=1&&dbx_cj!=1)
	{
		SetCursor(LoadCursor(NULL,IDC_CROSS));//设置光标为“+”字形
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
			//设置画笔
			CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//设置透明画刷
			CPen pen_v(2,1,RGB(0,0,0));//加载线条设置
			//选择画笔
			dc.SelectObject(pen_v);
			dc.SelectObject(pBrush);
			//画图
			dc.SetROP2(R2_NOTXORPEN);
			dc.Rectangle(ps.x,ps.y,pe.x,pe.y);
			dc.Rectangle(ps.x,ps.y,point.x,point.y);
			pe=point;
			//删除画笔
			pen_v.DeleteObject();
			pBrush->DeleteObject();
		}
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CSailorGraphView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加命令处理程序代码
	pBase->OnEditUndo();
	Invalidate();
    UpdateWindow();
}

void CSailorGraphView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (isClick==1)
	{
		pBase->OnUpdateEditUndo(pCmdUI);
	}
	else
		pCmdUI->Enable(FALSE);
	
}
//保存文件模块
void CSailorGraphView::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	if (isClick==1)
	{
		pBase->OnFileSave();
	}
	else
		MessageBox(_T("对不起，你没有对文件进行过更改！"),_T("提示"),MB_ICONINFORMATION);

}
//打开文件模块
void CSailorGraphView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog saveDlg(TRUE);
	CString pathname;//路径
	CString ext;
	if (saveDlg.DoModal()==IDOK)
	{
		isClick=1;//设定成点击状态
		isDbc=0;//不是多边形
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

void CSailorGraphView::OnSetting()//设置线条参数
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(isClick);
}


void CSailorGraphView::On1Line()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	temp1Circle.getView(this);
	pBase=&temp1Circle;
	isClick=1;
	isSelect=0;
	isDbc=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

}
//绘制矩形的响应函数
void CSailorGraphView::On1Rect()
{
	// TODO: 在此添加命令处理程序代码
	temp1Rect.getView(this);
	pBase=&temp1Rect;
	isClick=1;
	isSelect=0;
	isDbc=0;
	C_S=0;
	L_B=0;
	dbx_cj=0;

}
//绘制任意多边形的响应函数
void CSailorGraphView::OnDbx()
{
	// TODO: 在此添加命令处理程序代码
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
	pdc->TextOut(240,30,_T("点击鼠标左键开始绘图，点击鼠标右键停止绘图"));
	pdc->TextOut(240,50,_T("操作时请先选择菜单中的  选择工具  进行图形选中"));
	ReleaseDC(pdc);
}

void CSailorGraphView::On2Dda()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	isSelect=1;
}

void CSailorGraphView::OnUpdateOnselect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(isClick);
}

//单击右键响应函数
void CSailorGraphView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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

void CSailorGraphView::On3Bxg()//边相关扫描线填充
{
	// TODO: 在此添加命令处理程序代码
	if (isSelect!=1)
	{
		AfxMessageBox(_T("请你先选择要填充的图形"));
	}
	else
	{
		CDC *pDC=GetWindowDC();
		pBase->BXG(pDC);
		ReleaseDC(pDC);
	}

}

void CSailorGraphView::On3Smxzz()//扫描线种子填充
{
	// TODO: 在此添加命令处理程序代码
	if (isSelect!=1)
	{
		AfxMessageBox(_T("请你先选择要填充的图形"));
	}
	else
	{
		CDC *pDC=GetWindowDC();
		pDC->TextOut(240,70,_T("双击图形作为种子"));
		isseed=1;
	}
}

void CSailorGraphView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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
	// TODO: 在此添加命令处理程序代码
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
	pdc->TextOut(240,30,_T("点击鼠标左键开始绘图，点击鼠标右键停止绘图"));
	pdc->TextOut(240,50,_T("操作时请先选择菜单中的  选择工具  进行图形选中"));
	pdc->MoveTo(0,350);
	pdc->LineTo(1500,350);
	pdc->MoveTo(600,0);
	pdc->LineTo(600,1200);
	ReleaseDC(pdc);
}

void CSailorGraphView::OnPy()//平移变换
{
	// TODO: 在此添加命令处理程序代码
	if (isSelect!=1)
	{
		AfxMessageBox(_T("请你先选择要平移的图形"));
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

void CSailorGraphView::On4Xz()//旋转变换
{
	// TODO: 在此添加命令处理程序代码
	if (isSelect!=1)
	{
		AfxMessageBox(_T("请你先选择要旋转的图形"));
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
	// TODO: 在此添加命令处理程序代码
	if (isSelect!=1)
	{
		AfxMessageBox(_T("请你先选择要放缩的图形"));
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
	// TODO: 在此添加命令处理程序代码
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

void CSailorGraphView::On5CohenSutherland()//Cohen_Sutherland剪裁算法
{
	// TODO: 在此添加命令处理程序代码
	if (isClick!=1)
	{
		AfxMessageBox(_T("请先绘制直线"));
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
	// TODO: 在此添加命令处理程序代码
	if (isClick!=1)
	{
		AfxMessageBox(_T("请先绘制直线"));
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

void CSailorGraphView::On5Drawsbx()//绘制多边形的函数
{
	// TODO: 在此添加命令处理程序代码
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
// 	pdc->TextOut(240,30,_T("点击鼠标左键开始绘图，点击鼠标右键停止绘图"));
// 	pdc->TextOut(240,50,_T("操作时请先选择菜单中的  选择工具  进行图形选中"));
// 	ReleaseDC(pdc);
}

void CSailorGraphView::On5Cjdbx()//对多边形进行裁剪的函数
{
	// TODO: 在此添加命令处理程序代码
	if (isClick!=1)
	{
		AfxMessageBox(_T("请先绘制多边形"));
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

void CSailorGraphView::On6Berier()//Berier曲线
{
	// TODO: 在此添加命令处理程序代码
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

void CSailorGraphView::On6Byt()//B样条曲线
{
	// TODO: 在此添加命令处理程序代码
}
