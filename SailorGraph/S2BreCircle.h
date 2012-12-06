 #ifndef  S2BRECIRCLE_H_H
 #define S2BRECIRCLE_H_H
#include "SGraphBasic.h"
#include <cmath>
#include <vector>
using namespace std;
class S2BreCircle : public SGraphBasic
{
public://��Ϣ��Ӧ�ĺ���
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	BOOL isEqual();
	void BreCircle(CPoint pntStart,CPoint pntEnd,CDC *pDC);
	void CirPot(int cx, int cy, int x, int y, CDC* pDC);//�˷ַ�
public://Ĭ�Ϲ�����������
	S2BreCircle(){}
	~S2BreCircle(){}
public://��ӵĺ���
	S2BreCircle(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
	vector<S2BreCircle>m_breCirs;
};

//-------------------����ʵ�ֲ���-------------------------

void S2BreCircle::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S2BreCircle::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(pv);
	dc.SetROP2(R2_NOTXORPEN);
    BreCircle(m_pntStart,m_pntEnd,&dc);
	BreCircle(m_pntStart,point,&dc);
	m_pntEnd=point;
}
void S2BreCircle::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_breCirs.push_back(S2BreCircle(m_pntStart,point,m_ps,m_with,m_color));
}
S2BreCircle::S2BreCircle(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//���캯��
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S2BreCircle::Draw(CDC *pDC)
{
	BreCircle(m_pntStart,m_pntEnd,pDC);
}
void S2BreCircle::DrawGraph(CDC *pDC)//��ͼ����
{
	
	int index=m_breCirs.size();
	while (index)
	{
		m_breCirs.at(index-1).Draw(pDC);
		index--;
	}
}
void S2BreCircle::OnEditUndo()//undo����
{
	int index;
	index=m_breCirs.size()-1;
	if (index>=0)
	{
		m_breCirs.pop_back();
	}
}
void S2BreCircle::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_breCirs.size());
}
BOOL S2BreCircle::isEqual()
{
	return (m_breCirs.size()==m_number);
}
void S2BreCircle::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("2BreCircle Files (*.2brec)|*.2brec"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("2BreCircle Files (*.2brec)|*.2brec||"));
	CString pathname;//·��
	saveDlg.m_ofn.lpstrTitle=_T("���������ļ�");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_breCirs.size();
		int i=0;
		for (i=0;i<m_breCirs.size();i++)
		{
			ar<<m_breCirs[i].m_pntStart;
			ar<<m_breCirs[i].m_pntEnd;
			ar<<m_breCirs[i].m_ps<<m_breCirs[i].m_with<<m_breCirs[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S2BreCircle::OnFileOpen(CString pathname)//���ļ�
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_breCirs.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_breCirs[i].m_pntStart;
		ar>>m_breCirs[i].m_pntEnd;
		ar>>m_breCirs[i].m_ps>>m_breCirs[i].m_with>>m_breCirs[i].m_color;
	}
	m_number=m_breCirs.size();
	ar.Close();
	flieSave.Close();
}
void S2BreCircle::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S2BreCircle::BreCircle(CPoint pntStart,CPoint pntEnd,CDC *pDC)
{
	
	int t1=abs(pntEnd.x-pntStart.x)*abs(pntEnd.x-pntStart.x);
	int t2=abs(pntEnd.y-pntStart.y)*abs(pntEnd.y-pntStart.y);
	double r=sqrt(double(t1+t2))/2;
	int cx=(pntStart.x+pntEnd.x)/2;
	int cy=(pntStart.y+pntEnd.y)/2;
	int x=0,y=r,F=3-2*r;
	while(x < y)
	{
		CirPot(cx,cy,x,y,pDC);
		if(F<0)
			F += 4*x+6;
		else
		{
			F += 4*(x-y)+10;
			y--;
		}
		x++;
	}
	if (x == y)
		CirPot(cx,cy,x,y,pDC);
}
void S2BreCircle::CirPot(int cx, int cy, int x, int y, CDC* pDC)//�˷ַ�
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