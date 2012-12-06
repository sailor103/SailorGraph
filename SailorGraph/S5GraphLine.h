 #ifndef  S5GRAPHLINE_H_H
 #define S5GRAPHLINE_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;
class S5GraphLine : public SGraphBasic
{
public://��Ϣ��Ӧ�ĺ���
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	BOOL  isEqual();
public://Ĭ�Ϲ�����������
	S5GraphLine(){}
	~S5GraphLine(){}
public://��ӵĺ���
	S5GraphLine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
	void C_S(CPoint p1,CPoint p2,CDC *pDC);//c-sֱ�߼���
	void L_B(CPoint p1,CPoint p2,CDC *pDC);//l-bֱ�߼���
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
public:
	vector<S5GraphLine>m_Lines;
};

//-------------------����ʵ�ֲ���-------------------------

void S5GraphLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S5GraphLine::OnMouseMove(UINT nFlags, CPoint point)
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
	dc.MoveTo(this->m_pntStart);
	dc.LineTo(this->m_pntEnd);
	dc.MoveTo(this->m_pntStart);
	dc.LineTo(point);
	m_pntEnd=point;
    //ɾ������
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S5GraphLine::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_Lines.push_back(S5GraphLine(m_pntStart,point,m_ps,m_with,m_color));
}
S5GraphLine::S5GraphLine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//���캯��
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S5GraphLine::Draw(CDC *pDC)
{
	//���û���
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//����͸����ˢ
	CPen pen_v(m_ps,m_with,m_color);//������������

	pDC->SelectObject(pen_v);
	pDC->SelectObject(pBrush);

	pDC->MoveTo(m_pntStart);
	pDC->LineTo(m_pntEnd);
	//ɾ������
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S5GraphLine::DrawGraph(CDC *pDC)//��ͼ����
{
	
	int index=m_Lines.size();
	while (index)
	{
		m_Lines.at(index-1).Draw(pDC);
		index--;
	}
}
void S5GraphLine::OnEditUndo()//undo����
{
	int index;
	index=m_Lines.size()-1;
	if (index>=0)
	{
		m_Lines.pop_back();
	}
}
void S5GraphLine::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Lines.size());
}
BOOL S5GraphLine::isEqual()
{
	return (m_Lines.size()==m_number);
}
void S5GraphLine::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("5Line Files (*.5line)|*.5line"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("5Line Files (*.5line)|*.5line||"));
	CString pathname;//·��
	saveDlg.m_ofn.lpstrTitle=_T("���������ļ�");
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
void S5GraphLine::OnFileOpen(CString pathname)//���ļ�
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
void S5GraphLine::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
//**********************�����ǽ���c-s�ü��ĺ�������************************************************************
unsigned char code(CPoint rect1,CPoint rect2,float x,float y)	//��ĳ��λ�ý��б��룬��5�����
{
	unsigned char c=0;					//�ü��������棬0000
	if(((int)(x+0.5))<((int)(0.5+rect1.x)))				//�ü��������棬0001
		c=c|1;
	else if(((int)(x+0.5))>((int)(0.5+rect2.x)))	//�ü������ұߣ�0010
		c=c|2;	
	if(((int)(y+0.5))<((int)(0.5+rect1.y)))				//�ü��������棬0100
		c=c|4;
	else if(((int)(y+0.5))>((int)(0.5+rect2.y)))	//�ü��������棬1000
		c=c|8;
	return c;
}

void S5GraphLine::C_S(CPoint p1,CPoint p2,CDC *pDC)
{
	int index=m_Lines.size();
	for (int i=0;i<index;i++)
	{
		unsigned char c1,c2,c;
		float x,y,wx,wy;
		c1=code(p1,p2,m_Lines.at(i).m_pntStart.x,m_Lines.at(i).m_pntStart.y);			//�Ե�һ����б���
		c2=code(p1,p2,m_Lines.at(i).m_pntEnd.x,m_Lines.at(i).m_pntEnd.y);			//�Եڶ�����б���

		while((!(c1==0))||(!(c2==0)))	//������������һ���ı��벻Ϊ��ͽ���ѭ����Ҳ����˵��һ�㲻�ڲü���������ͽ���ѭ��
		{
			if(c1&c2)					//�������㶼�ڲü���������ʱɾ�������߶Σ�Ȼ���������
			{
				CPoint p(-1,-1);
                m_Lines.at(i).m_pntStart=p;
				m_Lines.at(i).m_pntEnd=p;
				break;
			}
			else
			{
				c=c1;
				if(c==0)					//�ҳ��ڲü��������һ��
					c=c2;
				wx=m_Lines.at(i).m_pntEnd.x-m_Lines.at(i).m_pntStart.x;
				wy=m_Lines.at(i).m_pntEnd.y-m_Lines.at(i).m_pntStart.y;

				if((c&1)==1)				//����߶ε�һ�����ڴ������棬��ô���ݴ�����߽��x�����޼�����y����
				{
					y=m_Lines.at(i).m_pntStart.y+wy*((float)(p1.x)-m_Lines.at(i).m_pntStart.x)/wx;
					x=(float)(p1.x);
				}
				else if((c&2)==2)			//����߶ε�һ�����ڴ������棬��ô���ݴ����ұ߽��x�����޼�����y����
				{
					y=m_Lines.at(i).m_pntStart.y+wy*((float)(p2.x)-m_Lines.at(i).m_pntStart.x)/wx;
					x=(float)(p2.x);
				}
				else if((c&4)==4)			//����߶ε�һ�����ڴ������棬��ô���ݴ����ϱ߽��y�����޼�����x����
				{
					x=m_Lines.at(i).m_pntStart.x+wx*((float)(p1.y)-m_Lines.at(i).m_pntStart.y)/wy;
					y=(float)(p1.y);
				}
				else if((c&8)==8)			//����߶ε�һ�����ڴ������棬��ô���ݴ����±߽��y�����޼�����x����
				{
					x=m_Lines.at(i).m_pntStart.x+wx*((float)(p2.y)-m_Lines.at(i).m_pntStart.y)/wy;
					y=(float)(p2.y);
				}
				if(c==c1)					//���c1�Ǵ�����ĵ㣬��ô����ԭ�����߶����ݵ�m_Lines.at(i).m_pntStart.x
				{
					m_Lines.at(i).m_pntStart.x=x;
					m_Lines.at(i).m_pntStart.y=y;
					c1=code(p1,p2,m_Lines.at(i).m_pntStart.x,m_Lines.at(i).m_pntStart.y);
				}
				else						//���c2�Ǵ�����ĵ㣬��ô����ԭ�����߶����ݵ�m_Lines.at(i).m_pntEnd.x,Ȼ�����ѭ�����вü���ֱ���߶��ڲü���������Ϊֹ
				{
					m_Lines.at(i).m_pntEnd.x=x;
					m_Lines.at(i).m_pntEnd.y=y;
					c2=code(p1,p2,m_Lines.at(i).m_pntEnd.x,m_Lines.at(i).m_pntEnd.y);
				}
			}
		}	
	}

}

//������������������������������������������������Ҫ����l-bֱ�߼��á�����������������������������������

/*boolean ClipT(float q,float d,float *t0,float *t1)
{                                     //���߶���ȫ���ɼ�ʱ������FALSE,���򷵻�TURE           
	float r;
	if(q<0)
	{
		r=d/q;
		if(r>*t1)
			return(false);
		else if(r>*t0)
		{
			*t0=r;
			return(true);
		}
	}
	else if(q>0)
	{
		r=d/q;
		if(r<*t0)
			return(false);
		else if(r<*t1)
		{
			*t1=r;
			return(true);
		}
	}
	else if(d<0)
		return(false);
	return(true);

}
void S5GraphLine::L_B(CPoint p1,CPoint p2,CDC *pDC)
{
	int index=m_Lines.size();
	for (int i=0;i<index;i++)
	{
		float deltax,deltay,t0,t1;
		t0=0,t1=1;
		deltax=m_Lines.at(i).m_pntEnd.x-m_Lines.at(i).m_pntStart.x;
		if(ClipT(-deltax,m_Lines.at(i).m_pntStart.x-p1.x,&t0,&t1))
			if(ClipT(deltax,p2.x-m_Lines.at(i).m_pntStart.x,&t0,&t1))
			{
				deltay=m_Lines.at(i).m_pntEnd.y-m_Lines.at(i).m_pntStart.y;
				if(ClipT(-deltay,m_Lines.at(i).m_pntStart.y-p1.y,&t0,&t1))
					if(ClipT(deltay,p2.y-m_Lines.at(i).m_pntStart.y,&t0,&t1))
					{
						pDC->MoveTo((int)(m_Lines.at(i).m_pntStart.x+t0*deltax),(int)(m_Lines.at(i).m_pntStart.y+t0*deltay));
						pDC->LineTo((int)(m_Lines.at(i).m_pntStart.x+t1*deltax),(int)(m_Lines.at(i).m_pntStart.y+t1*deltay));
						return;
					}
			}

	}
}*/
int ClipTest(double u,double v,double *tmax,double *tmin)//�ü����Ժ���
{//˳����������
	double t;int ReturnValue=TRUE;
	if(u<0.0)//�ⲿ���ڲ�,������㴦��tmax
	{
		t=v/u;
		if(t>*tmin)
			ReturnValue=FALSE;
		else if(t>*tmax)
			*tmax=t;
	}
	else
	{
		if(u>0.0)//�ڲ����ⲿ�������յ㴦��tmin
		{
			t=v/u;
			if(t<*tmax)
				ReturnValue=FALSE;
			else if(t<*tmin)
				*tmin=t;
		}
		else//ƽ���ڴ��ڱ߽��ֱ��
		{
			if(v<0.0)//ֱ���ڴ������ֱ��ɾ��
				ReturnValue=FALSE;
		}
	}
	return(ReturnValue);
}
void S5GraphLine::L_B(CPoint p1,CPoint p2,CDC *pDC)//�ü�����
{
	double x1;
	double y1;
	double x2;
	double y2;
	int index=m_Lines.size();
	for(int i=0;i<index;i++)
	{
		
		x1=m_Lines.at(i).m_pntStart.x;
		x2=m_Lines.at(i).m_pntEnd.x;
		y1=m_Lines.at(i).m_pntStart.y;
		y2=m_Lines.at(i).m_pntEnd.y;
		double tmax,tmin,dx,dy;
		dx=x2-x1;dy=y2-y1;tmax=0.0,tmin=1.0;
		//���ڱ߽�����ҡ��¡���˳��ü�ֱ��
		if(ClipTest(-dx,x1-p1.x,&tmax,&tmin))//n��1,��߽�u1������x��v1��x1��wxl
		{
			if(ClipTest(dx,p2.x-x1,&tmax,&tmin))//n��2���ұ߽�u2����x��v2��wxr��x1
			{			
				if(ClipTest(-dy,y1-p1.y,&tmax,&tmin))//n��3���±߽�u3������y��v3��y1-wyb
				{
					if(ClipTest(dy,p2.y-y1,&tmax,&tmin))//n��4���ϱ߽�u4����y��v4��wyt-y1
					{
						if(tmin<1.0)//�ж�ֱ�ߵ��յ�
						{
							x2=x1+tmin*dx;//���¼���ֱ�߶˵�
							y2=y1+tmin*dy;//x��x1��t(x2��x1)��ʽ
							int a=x2;
							int b=y2;
							CPoint p(a,b);
							m_Lines.at(i).m_pntEnd=p;
						}
						if(tmax>0.0)//�ж�ֱ�ߵ����
						{
							x1=x1+tmax*dx;
							y1=y1+tmax*dy;
							int a=x1;
							int b=y1;
							CPoint p(a,b);
							m_Lines.at(i).m_pntStart=p;
						}
					}
					else
					{
						CPoint a(-1,-1);
						m_Lines.at(i).m_pntStart=a;
						m_Lines.at(i).m_pntEnd=a;
					}
				}
				else
				{
					CPoint a(-1,-1);
					m_Lines.at(i).m_pntStart=a;
					m_Lines.at(i).m_pntEnd=a;
				}
			}
			else
			{
				CPoint a(-1,-1);
				m_Lines.at(i).m_pntStart=a;
				m_Lines.at(i).m_pntEnd=a;
			}
		}
        else
		{
			CPoint a(-1,-1);
			m_Lines.at(i).m_pntStart=a;
			m_Lines.at(i).m_pntEnd=a;
		}
	}
}



#endif

