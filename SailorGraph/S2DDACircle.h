 #ifndef  S2DDACIRCLE_H_H
 #define S2DDACIRCLE_H_H
#include "SGraphBasic.h"
#include <cmath>
#include <vector>
using namespace std;
class S2DDACircle : public SGraphBasic
{
public://消息响应的函数
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	BOOL    isEqual();
	void DDACircle(CPoint pntStart,CPoint pntEnd,CDC *pDC);
	void CirPot(int cx, int cy, int x, int y, CDC* pDC);//八分法
public://默认构造析构函数
	S2DDACircle(){}
	~S2DDACircle(){}
public://添加的函数
	S2DDACircle(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//起点
	CPoint m_pntEnd;// 终点
	vector<S2DDACircle>m_ddaCirs;
};

//-------------------函数实现部分-------------------------

void S2DDACircle::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S2DDACircle::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(pv);
	dc.SetROP2(R2_NOTXORPEN);
    DDACircle(m_pntStart,m_pntEnd,&dc);
	DDACircle(m_pntStart,point,&dc);
	m_pntEnd=point;
}
void S2DDACircle::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_ddaCirs.push_back(S2DDACircle(m_pntStart,point,m_ps,m_with,m_color));
}
S2DDACircle::S2DDACircle(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//构造函数
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S2DDACircle::Draw(CDC *pDC)
{
	DDACircle(m_pntStart,m_pntEnd,pDC);
}
void S2DDACircle::DrawGraph(CDC *pDC)//绘图功能
{
	
	int index=m_ddaCirs.size();
	while (index)
	{
		m_ddaCirs.at(index-1).Draw(pDC);
		index--;
	}
}
void S2DDACircle::OnEditUndo()//undo功能
{
	int index;
	index=m_ddaCirs.size()-1;
	if (index>=0)
	{
		m_ddaCirs.pop_back();
	}
}
void S2DDACircle::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_ddaCirs.size());
}
BOOL S2DDACircle::isEqual()
{
	return (m_ddaCirs.size()==m_number);
}
void S2DDACircle::OnFileSave()//保存文件
{
	CFileDialog saveDlg(FALSE,_T("2ddaCircle Files (*.2ddac)|*.2ddac"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("2ddaCircle Files (*.2ddac)|*.2ddac||"));
	CString pathname;//路径
	saveDlg.m_ofn.lpstrTitle=_T("保存您的文件");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_ddaCirs.size();
		int i=0;
		for (i=0;i<m_ddaCirs.size();i++)
		{
			ar<<m_ddaCirs[i].m_pntStart;
			ar<<m_ddaCirs[i].m_pntEnd;
			ar<<m_ddaCirs[i].m_ps<<m_ddaCirs[i].m_with<<m_ddaCirs[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S2DDACircle::OnFileOpen(CString pathname)//打开文件
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_ddaCirs.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_ddaCirs[i].m_pntStart;
		ar>>m_ddaCirs[i].m_pntEnd;
		ar>>m_ddaCirs[i].m_ps>>m_ddaCirs[i].m_with>>m_ddaCirs[i].m_color;
	}
	m_number=m_ddaCirs.size();
	ar.Close();
	flieSave.Close();
}
void S2DDACircle::getSeting(int ps,int with,COLORREF color)//得到设置
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S2DDACircle::DDACircle(CPoint pntStart,CPoint pntEnd,CDC *pDC)
{
	int t1=abs(pntEnd.x-pntStart.x)*abs(pntEnd.x-pntStart.x);
	int t2=abs(pntEnd.y-pntStart.y)*abs(pntEnd.y-pntStart.y);
	double r=sqrt(double(t1+t2))/2;
	int cx=(pntStart.x+pntEnd.x)/2;
	int cy=(pntStart.y+pntEnd.y)/2;
	int x=0,y=r,n=r;
	double cr = (double)r;
	double z=1.0/cr;
	double a=x,b=y;
	double tmp;
	while(n > 0)
	{

		CirPot(cx,cy,x,y,pDC);
		tmp=a;
		a-=b*z;
		b+=tmp*z;
		x = (int)(a);
		y = (int)(b);
		n--;
	}
	if(x == y)
		CirPot(cx,cy,x,y,pDC);
}
void S2DDACircle::CirPot(int cx, int cy, int x, int y, CDC* pDC)//八分法
{
	pDC->SetPixelV((cx+x),(cy+y),m_color);
	pDC->SetPixelV((cx+y),(cy+x),m_color);
	pDC->SetPixelV((cx+y),(cy-x),m_color);
	pDC->SetPixelV((cx+x),(cy-y),m_color);
	pDC->SetPixelV((cx-x),(cy-y),m_color);
	pDC->SetPixelV((cx-y),(cy-x),m_color);
	pDC->SetPixelV((cx-y),(cy+x),m_color);
	pDC->SetPixelV((cx-x),(cy+y),m_color);
}
#endif