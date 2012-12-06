 #ifndef  S6GRAPHPT_H_H
 #define S6GRAPHPT_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;
class S6GraphPt : public SGraphBasic
{
public://��Ϣ��Ӧ�ĺ���
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	void OnRButtonDown(UINT nFlags, CPoint point);//�Ҽ�����ĺ�������
	void Bezier(CDC *pDC);//Bezier����
	BOOL  isEqual();
public://Ĭ�Ϲ�����������
	S6GraphPt(){}
	~S6GraphPt(){}
public://��ӵĺ���
	//S6GraphPt(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
	vector<CPoint>m_points;
	int isdraw;
};

//-------------------����ʵ�ֲ���-------------------------

void S6GraphPt::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (isdraw==1)
	{
		m_points.clear();
		isdraw=0;
	}
	m_points.push_back(point);//ѹ���һ����
	CDC *pDC=pv->GetDC();
	CPen pen_v(m_ps,m_with,m_color);//������������
	pDC->SelectObject(pen_v);
	pDC->TextOut(point.x,point.y,_T("��"));
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
	CPen pen_v(m_ps,m_with,m_color);//������������
	pDC->SelectObject(pen_v);
	Bezier(pDC);
	pen_v.DeleteObject();

}
void S6GraphPt::Draw(CDC *pDC)
{
}
void S6GraphPt::DrawGraph(CDC *pDC)//��ͼ����
{
	CPen pen_v(m_ps,m_with,m_color);//������������
	pDC->SelectObject(pen_v);
	int index=m_points.size();
	for(int i=0;i<index-1;i++)
	{
		pDC->TextOut(m_points.at(i).x,m_points.at(i).y,_T("��"));
		pDC->TextOut(m_points.at(i+1).x,m_points.at(i+1).y,_T("��"));
		pDC->MoveTo(m_points.at(i));
		pDC->LineTo(m_points.at(i+1));

	}
	Bezier(pDC);
	pen_v.DeleteObject();

}
void S6GraphPt::OnEditUndo()//undo����
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
void S6GraphPt::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("Bezier Files (*.bez)|*.bez"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Bezier Files (*.bez)|*.bez||"));
	CString pathname;//·��
	saveDlg.m_ofn.lpstrTitle=_T("���������ļ�");
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
void S6GraphPt::OnFileOpen(CString pathname)//���ļ�
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
void S6GraphPt::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
//����������������������������������������bezier���ߵĺ���������������������������������
//��n!
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
//���������
double C(int n,int i)
{
	return ((double)JieCheng(n))/((double)(JieCheng(i)*JieCheng(n-i)));
}
//��һ����u��num�η�
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

void S6GraphPt::Bezier(CDC *pDC)//Bezier����
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
