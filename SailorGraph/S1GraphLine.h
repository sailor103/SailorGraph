 #ifndef  S1GRAPHLINE_H_H
 #define S1GRAPHLINE_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;
class S1GraphLine : public SGraphBasic
{
public://消息响应的函数
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	BOOL  isEqual();
public://默认构造析构函数
	S1GraphLine(){}
	~S1GraphLine(){}
public://添加的函数
	S1GraphLine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//起点
	CPoint m_pntEnd;// 终点
	vector<S1GraphLine>m_Lines;
};

//-------------------函数实现部分-------------------------

void S1GraphLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S1GraphLine::OnMouseMove(UINT nFlags, CPoint point)
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
	dc.MoveTo(this->m_pntStart);
	dc.LineTo(this->m_pntEnd);
	dc.MoveTo(this->m_pntStart);
	dc.LineTo(point);
	m_pntEnd=point;
    //删除画笔
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S1GraphLine::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_Lines.push_back(S1GraphLine(m_pntStart,point,m_ps,m_with,m_color));
}
S1GraphLine::S1GraphLine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//构造函数
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S1GraphLine::Draw(CDC *pDC)
{
	//设置画笔
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//设置透明画刷
	CPen pen_v(m_ps,m_with,m_color);//加载线条设置

	pDC->SelectObject(pen_v);
	pDC->SelectObject(pBrush);

	pDC->MoveTo(m_pntStart);
	pDC->LineTo(m_pntEnd);
	//删除画笔
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S1GraphLine::DrawGraph(CDC *pDC)//绘图功能
{
	
	int index=m_Lines.size();
	while (index)
	{
		m_Lines.at(index-1).Draw(pDC);
		index--;
	}
}
void S1GraphLine::OnEditUndo()//undo功能
{
	int index;
	index=m_Lines.size()-1;
	if (index>=0)
	{
		m_Lines.pop_back();
	}
}
void S1GraphLine::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Lines.size());
}
BOOL S1GraphLine::isEqual()
{
	return (m_Lines.size()==m_number);
}
void S1GraphLine::OnFileSave()//保存文件
{
	CFileDialog saveDlg(FALSE,_T("1Line Files (*.1line)|*.1line"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("1Line Files (*.1line)|*.1line||"));
	CString pathname;//路径
	saveDlg.m_ofn.lpstrTitle=_T("保存您的文件");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_Lines.size();
		int i=0;
		for (i=0;i<m_Lines.size();i++)
		{
			ar<<m_Lines[i].m_pntStart;
			ar<<m_Lines[i].m_pntEnd;
			ar<<m_Lines[i].m_ps<<m_Lines[i].m_with<<m_Lines[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S1GraphLine::OnFileOpen(CString pathname)//打开文件
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_Lines.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_Lines[i].m_pntStart;
		ar>>m_Lines[i].m_pntEnd;
		ar>>m_Lines[i].m_ps>>m_Lines[i].m_with>>m_Lines[i].m_color;
	}
	m_number=m_Lines.size();
	ar.Close();
	flieSave.Close();
}
void S1GraphLine::getSeting(int ps,int with,COLORREF color)//得到设置
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
#endif