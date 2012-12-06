 #ifndef  S2DDALINE_H_H
 #define S2DDALINE_H_H
#include "SGraphBasic.h"
#include <cmath>
#include <vector>
using namespace std;
class S2DDALine : public SGraphBasic
{
public://��Ϣ��Ӧ�ĺ���
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	BOOL    isEqual();
	void DDA(CPoint pntStart,CPoint pntEnd,CDC *pDC);
public://Ĭ�Ϲ�����������
	S2DDALine(){}
	~S2DDALine(){}
public://��ӵĺ���
	S2DDALine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
	vector<S2DDALine>m_DDALines;
};

//-------------------����ʵ�ֲ���-------------------------

void S2DDALine::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S2DDALine::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(pv);
	dc.SetROP2(R2_NOTXORPEN);
    DDA(m_pntStart,m_pntEnd,&dc);
	DDA(m_pntStart,point,&dc);
	m_pntEnd=point;
}
void S2DDALine::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_DDALines.push_back(S2DDALine(m_pntStart,point,m_ps,m_with,m_color));
}
S2DDALine::S2DDALine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//���캯��
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S2DDALine::Draw(CDC *pDC)
{
	DDA(m_pntStart,m_pntEnd,pDC);
}
void S2DDALine::DrawGraph(CDC *pDC)//��ͼ����
{
	
	int index=m_DDALines.size();
	while (index)
	{
		m_DDALines.at(index-1).Draw(pDC);
		index--;
	}
}
void S2DDALine::OnEditUndo()//undo����
{
	int index;
	index=m_DDALines.size()-1;
	if (index>=0)
	{
		m_DDALines.pop_back();
	}
}
void S2DDALine::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_DDALines.size());
}
BOOL S2DDALine::isEqual()
{
	return (m_DDALines.size()==m_number);
}
void S2DDALine::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("2dda Files (*.2dda)|*.2dda"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("2dda Files (*.2dda)|*.2dda||"));
	CString pathname;//·��
	saveDlg.m_ofn.lpstrTitle=_T("���������ļ�");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_DDALines.size();
		int i=0;
		for (i=0;i<m_DDALines.size();i++)
		{
			ar<<m_DDALines[i].m_pntStart;
			ar<<m_DDALines[i].m_pntEnd;
			ar<<m_DDALines[i].m_ps<<m_DDALines[i].m_with<<m_DDALines[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S2DDALine::OnFileOpen(CString pathname)//���ļ�
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_DDALines.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_DDALines[i].m_pntStart;
		ar>>m_DDALines[i].m_pntEnd;
		ar>>m_DDALines[i].m_ps>>m_DDALines[i].m_with>>m_DDALines[i].m_color;
	}
	m_number=m_DDALines.size();
	ar.Close();
	flieSave.Close();
}
void S2DDALine::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S2DDALine::DDA(CPoint pntStart,CPoint pntEnd,CDC *pDC)
{
	float x,y;
	float dx,dy,k;
	dx=(float)(pntEnd.x-pntStart.x);
	dy=(float)(pntEnd.y-pntStart.y);
	k=dy/dx;//��б��
	if(abs(k)<1)
	{
		if (pntStart.x>pntEnd.x)//�����û�
		{
			CPoint temp;
			temp=pntStart;
			pntStart=pntEnd;
			pntEnd=temp;
		}
		y=pntStart.y;
		for (x=pntStart.x;x<=pntEnd.x;x++)
		{
			pDC->SetPixel(x,int(y+0.5),m_color);
			y=y+k;
		}
	}
	if (abs(k)>=1)
	{
		if (pntStart.y>pntEnd.y)//�����û�
		{
			CPoint temp;
			temp=pntStart;
			pntStart=pntEnd;
			pntEnd=temp;
		}
		x=pntStart.x;
		for (y=pntStart.y;y<=pntEnd.y;y++)
		{
			pDC->SetPixel(int(x+0.5),y,m_color);
			x=x+1/k;
		}
	}

}
#endif