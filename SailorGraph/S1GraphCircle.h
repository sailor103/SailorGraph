 #ifndef  S1GRAPHCIRCLE_H_H
 #define S1GRAPHCIRCLE_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;

class S1GraphCircle : public SGraphBasic
{
public://消息响应的函数
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	void OnSelect(CPoint pntStart,CPoint pntEnd);
	BOOL    isEqual();
public://默认构造析构函数
	S1GraphCircle(){}
	~S1GraphCircle(){}
public://添加的函数
	S1GraphCircle(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//起点
	CPoint m_pntEnd;// 终点
	vector<S1GraphCircle>m_Circles;
};

//-------------------函数实现部分-------------------------

void S1GraphCircle::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S1GraphCircle::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(pv);
	//设置画笔
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//设置透明画刷
	CPen pen_v(m_ps,m_with,m_color);//加载线条设置
	//选择画笔
	dc.SelectObject(pen_v);
	dc.SelectObject(pBrush);
	//画图
	dc.SetROP2(R2_NOTXORPEN);
	dc.Ellipse(m_pntStart.x,m_pntStart.y,m_pntEnd.x,m_pntEnd.y);
	dc.Ellipse(m_pntStart.x,m_pntStart.y,point.x,point.y);
	m_pntEnd=point;
    //删除画笔
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S1GraphCircle::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_Circles.push_back(S1GraphCircle(m_pntStart,point,m_ps,m_with,m_color));
}
S1GraphCircle::S1GraphCircle(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//构造函数
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S1GraphCircle::Draw(CDC *pDC)
{
	//设置画笔
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//设置透明画刷
	CPen pen_v(m_ps,m_with,m_color);//加载线条设置

	pDC->SelectObject(pen_v);
	pDC->SelectObject(pBrush);

	pDC->Ellipse(m_pntStart.x,m_pntStart.y,m_pntEnd.x,m_pntEnd.y);
	//删除画笔
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S1GraphCircle::DrawGraph(CDC *pDC)//绘图功能
{
	
	int index=m_Circles.size();
	while (index)
	{
		m_Circles.at(index-1).Draw(pDC);
		index--;
	}
}
void S1GraphCircle::OnEditUndo()//undo功能
{
	int index;
	index=m_Circles.size()-1;
	if (index>=0)
	{
		m_Circles.pop_back();
	}
}
void S1GraphCircle::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Circles.size());
}
BOOL S1GraphCircle::isEqual()
{
	return (m_Circles.size()==m_number);
}
void S1GraphCircle::OnFileSave()//保存文件
{
	CFileDialog saveDlg(FALSE,_T("1Circle Files (*.1cir)|*.1cir"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("1Circle Files (*.1cir)|*.1cir||"));
	CString pathname;//路径
	saveDlg.m_ofn.lpstrTitle=_T("保存您的文件");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_Circles.size();
		int i=0;
		for (i=0;i<m_Circles.size();i++)
		{
			ar<<m_Circles[i].m_pntStart;
			ar<<m_Circles[i].m_pntEnd;
			ar<<m_Circles[i].m_ps<<m_Circles[i].m_with<<m_Circles[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S1GraphCircle::OnFileOpen(CString pathname)//打开文件
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_Circles.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_Circles[i].m_pntStart;
		ar>>m_Circles[i].m_pntEnd;
		ar>>m_Circles[i].m_ps>>m_Circles[i].m_with>>m_Circles[i].m_color;
	}
	m_number=m_Circles.size();
	ar.Close();
	flieSave.Close();
}
void S1GraphCircle::getSeting(int ps,int with,COLORREF color)//得到设置
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}

bool isIn(CPoint pntStart,CPoint pntEnd,CPoint isStart,CPoint isEnd)//判断点是否在选框内的函数
{
    //先判断起点是否在选框内
	int temp1=0;
	int temp2=0;
	int x_a=pntStart.x-isStart.x;
	int x_b=pntStart.x-isEnd.x;
	int y_a=pntStart.y-isStart.y;
	int y_b=pntStart.y-isEnd.y;
	if (x_a*x_b<0&&y_a*y_b<0)
	{
		temp1=1;
	}
	//判断终点是否在选框内
	x_a=pntEnd.x-isStart.x;
	x_b=pntEnd.x-isEnd.x;
	y_a=pntEnd.y-isStart.y;
	y_b=pntEnd.y-isEnd.y;
	if (x_a*x_b<0&&y_a*y_b<0)
	{
		temp2=1;
	}
	if (temp1==1&&temp2==1)
	{
		return true;
	}
	else
		return false;
}

void S1GraphCircle::OnSelect(CPoint pntStart,CPoint pntEnd)//选择功能实现
{
	int index=m_Circles.size();
	while (index)
	{		
		if (isIn(m_Circles.at(index-1).m_pntStart,m_Circles.at(index-1).m_pntEnd,pntStart,pntEnd))
		{
			m_Circles.at(index-1).m_color=RGB(255,0,0);
		}
		index--;
	}
}
#endif