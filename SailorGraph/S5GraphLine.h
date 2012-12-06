 #ifndef  S5GRAPHLINE_H_H
 #define S5GRAPHLINE_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;
class S5GraphLine : public SGraphBasic
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
	S5GraphLine(){}
	~S5GraphLine(){}
public://添加的函数
	S5GraphLine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
	void C_S(CPoint p1,CPoint p2,CDC *pDC);//c-s直线剪裁
	void L_B(CPoint p1,CPoint p2,CDC *pDC);//l-b直线剪裁
private:
	CPoint m_pntStart;//起点
	CPoint m_pntEnd;// 终点
public:
	vector<S5GraphLine>m_Lines;
};

//-------------------函数实现部分-------------------------

void S5GraphLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S5GraphLine::OnMouseMove(UINT nFlags, CPoint point)
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
void S5GraphLine::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_Lines.push_back(S5GraphLine(m_pntStart,point,m_ps,m_with,m_color));
}
S5GraphLine::S5GraphLine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//构造函数
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S5GraphLine::Draw(CDC *pDC)
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
void S5GraphLine::DrawGraph(CDC *pDC)//绘图功能
{
	
	int index=m_Lines.size();
	while (index)
	{
		m_Lines.at(index-1).Draw(pDC);
		index--;
	}
}
void S5GraphLine::OnEditUndo()//undo功能
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
void S5GraphLine::OnFileSave()//保存文件
{
	CFileDialog saveDlg(FALSE,_T("5Line Files (*.5line)|*.5line"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("5Line Files (*.5line)|*.5line||"));
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
void S5GraphLine::OnFileOpen(CString pathname)//打开文件
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
void S5GraphLine::getSeting(int ps,int with,COLORREF color)//得到设置
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
//**********************下面是进行c-s裁剪的函数集合************************************************************
unsigned char code(CPoint rect1,CPoint rect2,float x,float y)	//对某点位置进行编码，有5种情况
{
	unsigned char c=0;					//裁剪窗体里面，0000
	if(((int)(x+0.5))<((int)(0.5+rect1.x)))				//裁剪窗体左面，0001
		c=c|1;
	else if(((int)(x+0.5))>((int)(0.5+rect2.x)))	//裁剪窗体右边，0010
		c=c|2;	
	if(((int)(y+0.5))<((int)(0.5+rect1.y)))				//裁剪窗体上面，0100
		c=c|4;
	else if(((int)(y+0.5))>((int)(0.5+rect2.y)))	//裁剪窗体下面，1000
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
		c1=code(p1,p2,m_Lines.at(i).m_pntStart.x,m_Lines.at(i).m_pntStart.y);			//对第一点进行编码
		c2=code(p1,p2,m_Lines.at(i).m_pntEnd.x,m_Lines.at(i).m_pntEnd.y);			//对第二点进行编码

		while((!(c1==0))||(!(c2==0)))	//当两个点其中一个的编码不为零就进行循环，也就是说有一点不在裁剪窗体里面就进行循环
		{
			if(c1&c2)					//当两个点都在裁剪窗体外面时删除这条线段，然后结束函数
			{
				CPoint p(-1,-1);
                m_Lines.at(i).m_pntStart=p;
				m_Lines.at(i).m_pntEnd=p;
				break;
			}
			else
			{
				c=c1;
				if(c==0)					//找出在裁剪窗口外的一点
					c=c2;
				wx=m_Lines.at(i).m_pntEnd.x-m_Lines.at(i).m_pntStart.x;
				wy=m_Lines.at(i).m_pntEnd.y-m_Lines.at(i).m_pntStart.y;

				if((c&1)==1)				//如果线段的一部分在窗体左面，那么根据窗口左边届的x坐标修计算其y坐标
				{
					y=m_Lines.at(i).m_pntStart.y+wy*((float)(p1.x)-m_Lines.at(i).m_pntStart.x)/wx;
					x=(float)(p1.x);
				}
				else if((c&2)==2)			//如果线段的一部分在窗体右面，那么根据窗口右边届的x坐标修计算其y坐标
				{
					y=m_Lines.at(i).m_pntStart.y+wy*((float)(p2.x)-m_Lines.at(i).m_pntStart.x)/wx;
					x=(float)(p2.x);
				}
				else if((c&4)==4)			//如果线段的一部分在窗体上面，那么根据窗口上边届的y坐标修计算其x坐标
				{
					x=m_Lines.at(i).m_pntStart.x+wx*((float)(p1.y)-m_Lines.at(i).m_pntStart.y)/wy;
					y=(float)(p1.y);
				}
				else if((c&8)==8)			//如果线段的一部分在窗体下面，那么根据窗口下边届的y坐标修计算其x坐标
				{
					x=m_Lines.at(i).m_pntStart.x+wx*((float)(p2.y)-m_Lines.at(i).m_pntStart.y)/wy;
					y=(float)(p2.y);
				}
				if(c==c1)					//如果c1是窗口外的点，那么更新原来的线段数据到m_Lines.at(i).m_pntStart.x
				{
					m_Lines.at(i).m_pntStart.x=x;
					m_Lines.at(i).m_pntStart.y=y;
					c1=code(p1,p2,m_Lines.at(i).m_pntStart.x,m_Lines.at(i).m_pntStart.y);
				}
				else						//如果c2是窗口外的点，那么更新原来的线段数据到m_Lines.at(i).m_pntEnd.x,然后继续循环进行裁剪，直到线段在裁剪窗口里面为止
				{
					m_Lines.at(i).m_pntEnd.x=x;
					m_Lines.at(i).m_pntEnd.y=y;
					c2=code(p1,p2,m_Lines.at(i).m_pntEnd.x,m_Lines.at(i).m_pntEnd.y);
				}
			}
		}	
	}

}

//××××××××××××××××××××××下面要进行l-b直线剪裁××××××××××××××××××

/*boolean ClipT(float q,float d,float *t0,float *t1)
{                                     //当线段完全不可见时，返回FALSE,否则返回TURE           
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
int ClipTest(double u,double v,double *tmax,double *tmin)//裁剪测试函数
{//顺序左右下上
	double t;int ReturnValue=TRUE;
	if(u<0.0)//外部到内部,计算起点处的tmax
	{
		t=v/u;
		if(t>*tmin)
			ReturnValue=FALSE;
		else if(t>*tmax)
			*tmax=t;
	}
	else
	{
		if(u>0.0)//内部到外部，计算终点处的tmin
		{
			t=v/u;
			if(t<*tmax)
				ReturnValue=FALSE;
			else if(t<*tmin)
				*tmin=t;
		}
		else//平行于窗口边界的直线
		{
			if(v<0.0)//直线在窗口外可直接删除
				ReturnValue=FALSE;
		}
	}
	return(ReturnValue);
}
void S5GraphLine::L_B(CPoint p1,CPoint p2,CDC *pDC)//裁剪函数
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
		//窗口边界的左、右、下、上顺序裁剪直线
		if(ClipTest(-dx,x1-p1.x,&tmax,&tmin))//n＝1,左边界u1＝－△x，v1＝x1－wxl
		{
			if(ClipTest(dx,p2.x-x1,&tmax,&tmin))//n＝2，右边界u2＝△x，v2＝wxr－x1
			{			
				if(ClipTest(-dy,y1-p1.y,&tmax,&tmin))//n＝3，下边界u3＝－△y，v3＝y1-wyb
				{
					if(ClipTest(dy,p2.y-y1,&tmax,&tmin))//n＝4，上边界u4＝△y，v4＝wyt-y1
					{
						if(tmin<1.0)//判断直线的终点
						{
							x2=x1+tmin*dx;//重新计算直线端点
							y2=y1+tmin*dy;//x＝x1＋t(x2－x1)格式
							int a=x2;
							int b=y2;
							CPoint p(a,b);
							m_Lines.at(i).m_pntEnd=p;
						}
						if(tmax>0.0)//判断直线的起点
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

