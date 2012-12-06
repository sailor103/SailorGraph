 #ifndef  S2MIDCIRCLE_H_H
 #define S2MIDCIRCLE_H_H
#include "SGraphBasic.h"
#include <cmath>
#include <vector>
using namespace std;
class S2MidCircle : public SGraphBasic
{
public://��Ϣ��Ӧ�ĺ���
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	BOOL isEqual();
	void MidCircle(CPoint pntStart,CPoint pntEnd,CDC *pDC);
	void CirPot(int cx, int cy, int x, int y, CDC* pDC);//�˷ַ�
public://Ĭ�Ϲ�����������
	S2MidCircle(){}
	~S2MidCircle(){}
public://��ӵĺ���
	S2MidCircle(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
	vector<S2MidCircle>m_midCirs;
};

//-------------------����ʵ�ֲ���-------------------------

void S2MidCircle::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S2MidCircle::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(pv);
	dc.SetROP2(R2_NOTXORPEN);
    MidCircle(m_pntStart,m_pntEnd,&dc);
	MidCircle(m_pntStart,point,&dc);
	m_pntEnd=point;
}
void S2MidCircle::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_midCirs.push_back(S2MidCircle(m_pntStart,point,m_ps,m_with,m_color));
}
S2MidCircle::S2MidCircle(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//���캯��
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S2MidCircle::Draw(CDC *pDC)
{
	MidCircle(m_pntStart,m_pntEnd,pDC);
}
void S2MidCircle::DrawGraph(CDC *pDC)//��ͼ����
{
	
	int index=m_midCirs.size();
	while (index)
	{
		m_midCirs.at(index-1).Draw(pDC);
		index--;
	}
}
void S2MidCircle::OnEditUndo()//undo����
{
	int index;
	index=m_midCirs.size()-1;
	if (index>=0)
	{
		m_midCirs.pop_back();
	}
}
void S2MidCircle::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_midCirs.size());
}
BOOL S2MidCircle::isEqual()
{
	return (m_midCirs.size()==m_number);
}
void S2MidCircle::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("2MidCircle Files (*.2midc)|*.2midc"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("2MidCircle Files (*.2midc)|*.2midc||"));
	CString pathname;//·��
	saveDlg.m_ofn.lpstrTitle=_T("���������ļ�");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_midCirs.size();
		int i=0;
		for (i=0;i<m_midCirs.size();i++)
		{
			ar<<m_midCirs[i].m_pntStart;
			ar<<m_midCirs[i].m_pntEnd;
			ar<<m_midCirs[i].m_ps<<m_midCirs[i].m_with<<m_midCirs[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S2MidCircle::OnFileOpen(CString pathname)//���ļ�
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_midCirs.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_midCirs[i].m_pntStart;
		ar>>m_midCirs[i].m_pntEnd;
		ar>>m_midCirs[i].m_ps>>m_midCirs[i].m_with>>m_midCirs[i].m_color;
	}
	m_number=m_midCirs.size();
	ar.Close();
	flieSave.Close();
}
void S2MidCircle::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S2MidCircle::MidCircle(CPoint pntStart,CPoint pntEnd,CDC *pDC)
{
	int t1=abs(pntEnd.x-pntStart.x)*abs(pntEnd.x-pntStart.x);
	int t2=abs(pntEnd.y-pntStart.y)*abs(pntEnd.y-pntStart.y);
	double r=sqrt(double(t1+t2))/2;
	int cx=(pntStart.x+pntEnd.x)/2;
	int cy=(pntStart.y+pntEnd.y)/2;
	int x,y;
	float d;
	x=0;
	y=r;
	d=1-r;
	CirPot(cx,cy,x,y,pDC);
	while(x<y)
	{
		if(d<0)
		{
			d+=2*x+3;
			x++;
		}
		else
		{
			d+=2*(x-y)+5;
			x++;
			y--;
		}
		CirPot(cx,cy,x,y,pDC);
	}
}
void S2MidCircle::CirPot(int cx, int cy, int x, int y, CDC* pDC)//�˷ַ�
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