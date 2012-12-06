 #ifndef  S6GRAPHPT_H_H
 #define S6GRAPHPT_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;
class S6GraphPt : public SGraphBasic
{
public://消息响应的函数
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	void OnRButtonDown(UINT nFlags, CPoint point);//右键点击的函数重载
	void Bezier(CDC *pDC);//Bezier曲线
	BOOL  isEqual();
public://默认构造析构函数
	S6GraphPt(){}
	~S6GraphPt(){}
public://添加的函数
	//S6GraphPt(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//起点
	CPoint m_pntEnd;// 终点
	vector<CPoint>m_points;
	int isdraw;
};

//-------------------函数实现部分-------------------------

void S6GraphPt::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (isdraw==1)
	{
		m_points.clear();
		isdraw=0;
	}
	m_points.push_back(point);//压入第一个点
	CDC *pDC=pv->GetDC();
	CPen pen_v(m_ps,m_with,m_color);//加载线条设置
	pDC->SelectObject(pen_v);
	pDC->TextOut(point.x,point.y,_T("点"));
	pen_v.DeleteObject();
}
void S6GraphPt::OnMouseMove(UINT nFlags, CPoint point)
{
}
void S6GraphPt::OnLButtonUp(UINT nFlags, CPoint point)
{
}
void S6GraphPt::OnRButtonDown(UINT nFlags, CPoint point)
{
	pv->Invalidate();
	pv->UpdateWindow();
	isdraw=1;
	CDC *pDC=pv->GetDC();
	CPen pen_v(m_ps,m_with,m_color);//加载线条设置
	pDC->SelectObject(pen_v);
	Bezier(pDC);
	pen_v.DeleteObject();

}
void S6GraphPt::Draw(CDC *pDC)
{
}
void S6GraphPt::DrawGraph(CDC *pDC)//绘图功能
{
	CPen pen_v(m_ps,m_with,m_color);//加载线条设置
	pDC->SelectObject(pen_v);
	int index=m_points.size();
	for(int i=0;i<index-1;i++)
	{
		pDC->TextOut(m_points.at(i).x,m_points.at(i).y,_T("点"));
		pDC->TextOut(m_points.at(i+1).x,m_points.at(i+1).y,_T("点"));
		pDC->MoveTo(m_points.at(i));
		pDC->LineTo(m_points.at(i+1));

	}
	Bezier(pDC);
	pen_v.DeleteObject();

}
void S6GraphPt::OnEditUndo()//undo功能
{
	int index;
	index=m_points.size()-1;
	if (index>=0)
	{
		m_points.pop_back();
	}
}
void S6GraphPt::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_points.size());
}
BOOL S6GraphPt::isEqual()
{
	return (m_points.size()==m_number);
}
void S6GraphPt::OnFileSave()//保存文件
{
	CFileDialog saveDlg(FALSE,_T("Bezier Files (*.bez)|*.bez"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Bezier Files (*.bez)|*.bez||"));
	CString pathname;//路径
	saveDlg.m_ofn.lpstrTitle=_T("保存您的文件");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_points.size();
		int i=0;
		for (i=0;i<m_points.size();i++)
		{
			ar<<m_points.at(i);
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S6GraphPt::OnFileOpen(CString pathname)//打开文件
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_points.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_points.at(i);
	}
	m_number=m_points.size();
	ar.Close();
	flieSave.Close();
}
void S6GraphPt::getSeting(int ps,int with,COLORREF color)//得到设置
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
//×××××××××××××××××下面是bezier曲线的函数×××××××××××××××
//求n!
int JieCheng(int n)
{
	if(n==1||n==0)
	{
		return 1;
	}
	else
	{
		return n*JieCheng(n-1);
	}
}
//求组合排列
double C(int n,int i)
{
	return ((double)JieCheng(n))/((double)(JieCheng(i)*JieCheng(n-i)));
}
//求一个数u的num次方
double N(double u,int n)
{
	double sum=1.0;
	if (n==0)
	{
		return 1;
	}
	for(int i=0;i<n;i++)
	{
		sum*=u;
	}
	return sum;
}

void S6GraphPt::Bezier(CDC *pDC)//Bezier曲线
{
	int iNumber=m_points.size();
	pDC->MoveTo(m_points.at(0));
	if (iNumber==1)
	{
		pDC->SetPixel(m_points.at(0),m_color);
		return;
	}
	for(int i=0;i<iNumber-1;i++)
	{
		pDC->SetPixel(m_points.at(i),m_color);
		pDC->SetPixel(m_points.at(i+1),m_color);
		pDC->LineTo(m_points.at(i+1));
	}
	double u,x,y;
	pDC->SetPixel(m_points.at(0), m_color);
	pDC->MoveTo(m_points.at(0));
	for(u=0;u<=1;u=u+0.001)
	{
		x=0;y=0;
		for (int i=0;i<iNumber;i++)
		{
			x+=C(iNumber-1,i)*N(u,i)*N((1-u),(iNumber-1-i))*m_points.at(i).x;
			y+=C(iNumber-1,i)*N(u,i)*N((1-u),(iNumber-1-i))*m_points.at(i).y;
		}
		pDC->LineTo((int)x,(int)y);
	}
}
#endif
