#ifndef  S5GRAPHDBX_H_H
#define S5GRAPHDBX_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;

class S5GraphDbx : public SGraphBasic
{
public://��Ϣ��Ӧ�ĺ���
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	BOOL    isEqual();
public://Ĭ�Ϲ�����������
	S5GraphDbx(){m_num=0;}
	~S5GraphDbx(){}
public://��ӵĺ���
	S5GraphDbx(CPoint point[],int num,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
    void JC_DBC(CPoint p1,CPoint p2,CDC *pDC);//����βü�
	void dbx(CPoint point[],int num,CDC *pDC);
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
	vector<S5GraphDbx>m_dbx;
	CPoint m_point[100];//�������εĶ��㼯�ϣ�Ĭ��100���㣩
	int m_num;//����������

};

//-------------------����ʵ�ֲ���-------------------------
void S5GraphDbx::dbx(CPoint point[],int num,CDC *pDC)
{

	for (int i=0;i<num-1;i++)
	{
		pDC->MoveTo(point[i]);
		pDC->LineTo(point[i+1]);
	}
	pDC->MoveTo(point[0]);
	pDC->LineTo(point[num-1]);
}
void S5GraphDbx::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
    m_point[m_num]=point;
	m_num++;
}
void S5GraphDbx::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(pv);
	//���û���
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//����͸����ˢ
	CPen pen_v(m_ps,m_with,m_color);//������������
	//ѡ�񻭱�
	dc.SelectObject(pen_v);
	dc.SelectObject(pBrush);
	//��ͼ
	dc.SetROP2(R2_NOTXORPEN);
	dc.MoveTo(m_pntStart);
	dc.LineTo(m_pntEnd);
	dc.MoveTo(m_point[0]);
	dc.LineTo(m_pntEnd);
	dc.MoveTo(m_pntStart);
	dc.LineTo(point);
	dc.MoveTo(m_point[0]);
	dc.LineTo(point);
	m_pntEnd=point;
    //ɾ������
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S5GraphDbx::OnLButtonUp(UINT nFlags, CPoint point)
{
	
}

S5GraphDbx::S5GraphDbx(CPoint point[],int num,int ps,int with,COLORREF color)//���캯��
{
	for (int i=0;i<num;i++)
	{
		m_point[i]=point[i];
	}
	m_num=num;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S5GraphDbx::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_dbx.push_back(S5GraphDbx(m_point,m_num,m_ps,m_with,m_color));
	m_num=0;
}
void S5GraphDbx::Draw(CDC *pDC)
{
	//���û���
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//����͸����ˢ
	CPen pen_v(m_ps,m_with,m_color);//������������

	pDC->SelectObject(pen_v);
	pDC->SelectObject(pBrush);

    dbx(m_point,m_num,pDC);
	//ɾ������
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S5GraphDbx::DrawGraph(CDC *pDC)//��ͼ����
{
	int index=m_dbx.size();
	while (index)
	{
		m_dbx.at(index-1).Draw(pDC);
		index--;
	}
}
void S5GraphDbx::OnEditUndo()//undo����
{
	int index;
	index=m_dbx.size()-1;
	if (index>=0)
	{
		m_dbx.pop_back();
	}
}
void S5GraphDbx::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_dbx.size());
}
BOOL S5GraphDbx::isEqual()
{
	return (m_dbx.size()==m_number);
}
void S5GraphDbx::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("4dbc Files (*.5dbc)|*.5dbc"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("dbc Files (*.5dbc)|*.5dbc||"));
	CString pathname;//·��
	saveDlg.m_ofn.lpstrTitle=_T("���������ļ�");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_dbx.size();
		int i=0;
		for (i=0;i<m_dbx.size();i++)
		{
			for (int j=0;j<100;j++)//������100����
			{
				ar<<m_dbx[i].m_point[j];
			}
			ar<<m_dbx[i].m_num;
			ar<<m_dbx[i].m_ps<<m_dbx[i].m_with<<m_dbx[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S5GraphDbx::OnFileOpen(CString pathname)//���ļ�
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_dbx.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		for (int j=0;j<100;j++)//������100����
		{
			ar>>m_dbx[i].m_point[j];
		}
		
		ar>>m_dbx[i].m_num;
		ar>>m_dbx[i].m_ps>>m_dbx[i].m_with>>m_dbx[i].m_color;
	}
	m_number=m_dbx.size();
	ar.Close();
	flieSave.Close();
}
void S5GraphDbx::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}


//******************����Ҫ���ж���εļ�����ҵ***********************


void S5GraphDbx::JC_DBC(CPoint p1,CPoint p2,CDC *pDC)//����βü�
{
	int index=m_dbx.size();
	for (int count=0;count<index;count++)
	{
		int i,k;
		int code1,code2;
		int	M=m_dbx.at(count).m_num;
		CPoint pt[100];
		CPoint pts[100];
		CPoint ptse[100];
		CPoint p[100];
		// �����˵���������code
		k=0;
		for(i=0;i<M;i++)
		{	
			int c=0;
			if(m_dbx.at(count).m_point[i].x<p1.x) c=1;
			else if (m_dbx.at(count).m_point[i].x>p1.x)c=0;
			code1=c;
			c=0;
			if(m_dbx.at(count).m_point[i+1].x<p1.x) c=1;
			else if(m_dbx.at(count).m_point[i+1].x>p1.x) c=0;
			code2=c;
			if(code1!=0&&code2==0)
			{
				pt[k].x=p1.x;
				pt[k].y=m_dbx.at(count).m_point[i].y+(m_dbx.at(count).m_point[i+1].y-m_dbx.at(count).m_point[i].y)*(p1.x-m_dbx.at(count).m_point[i].x)/(m_dbx.at(count).m_point[i+1].x-m_dbx.at(count).m_point[i].x);
				pt[k+1].x=m_dbx.at(count).m_point[i+1].x;
				pt[k+1].y=m_dbx.at(count).m_point[i+1].y;
				k=k+2;
			}				
			if(code1==0&&code2==0)
			{			
				if(k==0)
				{
					pt[k].x=m_dbx.at(count).m_point[i].x;
					pt[k].y=m_dbx.at(count).m_point[i].y;
					pt[k+1].x=m_dbx.at(count).m_point[i+1].x;
					pt[k+1].y=m_dbx.at(count).m_point[i+1].y;
					k=k+2;
				}
				if(k!=0)
				{
					pt[k].x=m_dbx.at(count).m_point[i+1].x;
					pt[k].y=m_dbx.at(count).m_point[i+1].y;
					k=k+1;
				}
			}
			if(code1==0&&code2!=0)
			{
				pt[k].x=p1.x;
				pt[k].y=m_dbx.at(count).m_point[i].y+(m_dbx.at(count).m_point[i+1].y-m_dbx.at(count).m_point[i].y)*(p1.x-m_dbx.at(count).m_point[i].x)/(m_dbx.at(count).m_point[i+1].x-m_dbx.at(count).m_point[i].x);
				k++;
			}						
		}
		pt[k].x=pt[0].x;
		pt[k].y=pt[0].y;
		M=k+1;

		k=0;		
		for(i=0;i<M;i++)
		{		
			int c=0;
			if(pt[i].x<p2.x) c=0;
			else if(pt[i].x>p2.x) c=2;
			code1=c;
			c=0;
			if(pt[i+1].x<p2.x) c=0;
			else if(pt[i+1].x>p2.x) c=2;
			code2=c;
			if(code1==0&&code2==0)
			{
				if(k==0)
				{
					pts[k].x=pt[i].x;
					pts[k].y=pt[i].y;
					pts[k+1].x=pt[i+1].x;
					pts[k+1].y=pt[i+1].y;
					k=k+2;
				}
				if(k!=0)
				{
					pts[k].x=pt[i+1].x;
					pts[k].y=pt[i+1].y;
					k++;
				}
			}
			if(code1!=0&&code2==0)
			{

				pts[k].x=p2.x;
				pts[k].y=pt[i].y+(pt[i+1].y-pt[i].y)*(p2.x-pt[i].x)/(pt[i+1].x-pt[i].x);
				pts[k+1].x=pt[i+1].x;
				pts[k+1].y=pt[i+1].y;
				k=k+2;
			}	

			if(code1==0&&code2!=0)
			{
				pts[k].x=p2.x;
				pts[k].y=pt[i].y+(pt[i+1].y-pt[i].y)*(p2.x-pt[i].x)/(pt[i+1].x-pt[i].x);
				k=k+1;
			}		
		}
		//���Ӷ����һ���ߵ��ж�
		pts[k]=pts[0];
		M=k+1;
		k=0;
		for(i=0;i<M;i++)
		{			
			int c=0;
			if(pts[i].y>p2.y) c=4;
			else if(pts[i].y<p2.y) c=0;
			code1=c;
			c=0;
			if(pts[i+1].y>p2.y) c=4;
			else if(pts[i+1].y<p2.y) c=0;
			code2=c;	

			if(code1==0&&code2==0)
			{
				if(k==0)
				{
					ptse[k].x=pts[i].x;
					ptse[k].y=pts[i].y;
					ptse[k+1].x=pts[i+1].x;
					ptse[k+1].y=pts[i+1].y;
					k=k+2;
				}
				if(k!=0)
				{
					ptse[k].x=pts[i+1].x;
					ptse[k].y=pts[i+1].y;
					k=k+1;
				}
			}


			if(code1!=0&&code2==0)
			{
				ptse[k].y=p2.y;
				ptse[k].x=pts[i].x+(pts[i+1].x-pts[i].x)*(p2.y-pts[i].y)/(pts[i+1].y-pts[i+1].y);
				ptse[k+1].x=pts[i+1].x;
				ptse[k+1].y=pts[i+1].y;
				k=k+2;
			}
		}
		if(code1==0&&code2!=0)
		{
			ptse[k].y=p2.y;
			ptse[k].x=pts[i].x+(pts[i+1].x-pts[i].x)*(p2.y-pts[i].y)/(pts[i+1].y-pts[i+1].y);
			k=k+1;
		}
		ptse[k]=ptse[0];		
		M=k+1;

		k=0;
		for(i=0;i<M;i++)
		{	
			int c=0;
			if(ptse[i].y>p1.y) c=0;
			else if(ptse[i].y<p1.y) c=1;
			code1=c;
			c=0;
			if(ptse[i+1].y>p1.y) c=0;
			else if(ptse[i+1].y<p1.y) c=1;
			code2=c;
			if(code1!=0&&code2==0)
			{
				p[k].y=p1.y;
				p[k].x=ptse[i].x+(ptse[i+1].x-ptse[i].x)*(p1.y-ptse[i].y)/(ptse[i+1].y-ptse[i].y);
				p[k+1].x=ptse[i+1].x;
				p[k+1].y=ptse[i+1].y;
				k=k+2;
			}
			if(code1==0&&code2==0)
			{
				if(k==0)
				{
					p[k].x=ptse[i].x;
					p[k].y=ptse[i].y;
					p[k+1].x=ptse[i+1].x;
					p[k+1].y=ptse[i+1].y;
					k=k+2;
				}
				if(k!=0)
				{
					p[k].x=ptse[i+1].x;
					p[k].y=ptse[i+1].y;
					k=k+1;
				}
			}
			if(code1==0&&code2!=0)
			{
				p[k].y=p1.y;
				p[k].x=ptse[i].x+(ptse[i+1].x-ptse[i].x)*(p1.y-ptse[i].y)/(ptse[i+1].y-ptse[i].y);
				k++;
			}
		}
		p[k]=p[0];
		M=k+1;
		pDC->MoveTo(p[0]);
		for(int j=1;j<=M;j++)
		{
			pDC->LineTo(p[j]);
		}
	}
}
#endif