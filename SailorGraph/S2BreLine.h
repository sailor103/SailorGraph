 #ifndef  S2BRELINE_H_H
 #define S2BRELINE_H_H
#include "SGraphBasic.h"
#include <cmath>
#include <vector>
using namespace std;
class S2BreLine : public SGraphBasic
{
public://消息响应的函数
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	BOOL    isEqual();
	void BreLine(CPoint pntStart,CPoint pntEnd,CDC *pDC);
public://默认构造析构函数
	S2BreLine(){}
	~S2BreLine(){}
public://添加的函数
	S2BreLine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//起点
	CPoint m_pntEnd;// 终点
	vector<S2BreLine>m_BreLines;
};

//-------------------函数实现部分-------------------------

void S2BreLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S2BreLine::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(pv);
	dc.SetROP2(R2_NOTXORPEN);
    BreLine(m_pntStart,m_pntEnd,&dc);
	BreLine(m_pntStart,point,&dc);
	m_pntEnd=point;
}
void S2BreLine::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_BreLines.push_back(S2BreLine(m_pntStart,point,m_ps,m_with,m_color));
}
S2BreLine::S2BreLine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//构造函数
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S2BreLine::Draw(CDC *pDC)
{
	BreLine(m_pntStart,m_pntEnd,pDC);
}
void S2BreLine::DrawGraph(CDC *pDC)//绘图功能
{
	
	int index=m_BreLines.size();
	while (index)
	{
		m_BreLines.at(index-1).Draw(pDC);
		index--;
	}
}
void S2BreLine::OnEditUndo()//undo功能
{
	int index;
	index=m_BreLines.size()-1;
	if (index>=0)
	{
		m_BreLines.pop_back();
	}
}
void S2BreLine::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_BreLines.size());
}
BOOL S2BreLine::isEqual()
{
	return (m_BreLines.size()==m_number);
}
void S2BreLine::OnFileSave()//保存文件
{
	CFileDialog saveDlg(FALSE,_T("2BreLine Files (*.2brel)|*.2brel"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("2BreLine Files (*.2brel)|*.2brel||"));
	CString pathname;//路径
	saveDlg.m_ofn.lpstrTitle=_T("保存您的文件");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_BreLines.size();
		int i=0;
		for (i=0;i<m_BreLines.size();i++)
		{
			ar<<m_BreLines[i].m_pntStart;
			ar<<m_BreLines[i].m_pntEnd;
			ar<<m_BreLines[i].m_ps<<m_BreLines[i].m_with<<m_BreLines[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S2BreLine::OnFileOpen(CString pathname)//打开文件
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_BreLines.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_BreLines[i].m_pntStart;
		ar>>m_BreLines[i].m_pntEnd;
		ar>>m_BreLines[i].m_ps>>m_BreLines[i].m_with>>m_BreLines[i].m_color;
	}
	m_number=m_BreLines.size();
	ar.Close();
	flieSave.Close();
}
void S2BreLine::getSeting(int ps,int with,COLORREF color)//得到设置
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S2BreLine::BreLine(CPoint pntStart,CPoint pntEnd,CDC *pDC)
{
	int s1,s2,interchange;
	int X = pntStart.x;
	int Y = pntStart.y;
	int deltax,deltay,f,Temp;
	deltax=abs(pntEnd.x-pntStart.x);
	deltay=abs(pntEnd.y-pntStart.y);

	if(pntEnd.x-pntStart.x>=0) s1=1; else s1=-1;//设置步进值
	if(pntEnd.y-pntStart.y>=0) s2=1; else s2=-1; 
	f=2*deltay-deltax;//2dy-dx
	if(deltay>deltax)//斜率大于一，进行坐标转换
	{
		Temp=deltax;
		deltax=deltay;
		deltay=Temp;
		interchange=1;
	} 
	else interchange=0;
	for(int i=1;i<=deltax+deltay;i++)
	{
		if(f>=0)
		{
			if(interchange==1) X+=s1;
			else Y+=s2;
			pDC->SetPixel(X,Y,m_color);
			f=f-2*deltax;
		}
		else
		{
			if(interchange==1) Y+=s2;
			else X+=s1;
			pDC->SetPixel(X,Y,m_color);
			f=f+2*deltay;
		}
	}
}
#endif