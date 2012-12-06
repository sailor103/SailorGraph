 #ifndef  S1GRAPHRECT_H_H
 #define S1GRAPHRECT_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;
class S1GraphRect : public SGraphBasic
{
public://消息响应的函数
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	BOOL    isEqual();
public://默认构造析构函数
	S1GraphRect(){}
	~S1GraphRect(){}
public://添加的函数
	S1GraphRect(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//起点
	CPoint m_pntEnd;// 终点
	vector<S1GraphRect>m_Rects;
};

//-------------------函数实现部分-------------------------

void S1GraphRect::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S1GraphRect::OnMouseMove(UINT nFlags, CPoint point)
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
    dc.Rectangle(m_pntStart.x,m_pntStart.y,m_pntEnd.x,m_pntEnd.y);
	dc.Rectangle(m_pntStart.x,m_pntStart.y,point.x,point.y);
	m_pntEnd=point;
    //删除画笔
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S1GraphRect::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_Rects.push_back(S1GraphRect(m_pntStart,point,m_ps,m_with,m_color));
}
S1GraphRect::S1GraphRect(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//构造函数
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S1GraphRect::Draw(CDC *pDC)
{
	//设置画笔
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//设置透明画刷
	CPen pen_v(m_ps,m_with,m_color);//加载线条设置

	pDC->SelectObject(pen_v);
	pDC->SelectObject(pBrush);

    pDC->Rectangle(m_pntStart.x,m_pntStart.y,m_pntEnd.x,m_pntEnd.y);
	//删除画笔
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S1GraphRect::DrawGraph(CDC *pDC)//绘图功能
{
	
	int index=m_Rects.size();
	while (index)
	{
		m_Rects.at(index-1).Draw(pDC);
		index--;
	}
}
void S1GraphRect::OnEditUndo()//undo功能
{
	int index;
	index=m_Rects.size()-1;
	if (index>=0)
	{
		m_Rects.pop_back();
	}
}
void S1GraphRect::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Rects.size());
}
BOOL S1GraphRect::isEqual()
{
	return (m_Rects.size()==m_number);
}
void S1GraphRect::OnFileSave()//保存文件
{
	CFileDialog saveDlg(FALSE,_T("1Rect Files (*.1rec)|*.1rec"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("1Rect Files (*.1rec)|*.1rec||"));
	CString pathname;//路径
	saveDlg.m_ofn.lpstrTitle=_T("保存您的文件");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_Rects.size();
		int i=0;
		for (i=0;i<m_Rects.size();i++)
		{
			ar<<m_Rects[i].m_pntStart;
			ar<<m_Rects[i].m_pntEnd;
			ar<<m_Rects[i].m_ps<<m_Rects[i].m_with<<m_Rects[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S1GraphRect::OnFileOpen(CString pathname)//打开文件
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_Rects.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_Rects[i].m_pntStart;
		ar>>m_Rects[i].m_pntEnd;
		ar>>m_Rects[i].m_ps>>m_Rects[i].m_with>>m_Rects[i].m_color;
	}
	m_number=m_Rects.size();
	ar.Close();
	flieSave.Close();
}
void S1GraphRect::getSeting(int ps,int with,COLORREF color)//得到设置
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
#endif