 #ifndef  S4GRAPHDBX_H_H
 #define S4GRAPHDBX_H_H
#include "SGraphBasic.h"
#include <vector>
#include <cmath>
using namespace std;

class S4GraphDbx : public SGraphBasic
{
public://消息响应的函数
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	void OnSelect(CPoint pntStart,CPoint pntEnd);
	bool isIn(CPoint pntStart,CPoint pntEnd,CPoint point[],int num);//判断点是否在选框内的函数
	void PY(int x,int y,CDC *pDC);//平移函数
	void FS(float x,float y,CDC *pDC);//放缩函数
	void XZ(float x,CDC *pDC);//函数
	BOOL    isEqual();
public://默认构造析构函数
	S4GraphDbx(){m_num=0;}
	~S4GraphDbx(){}
public://添加的函数
	S4GraphDbx(CPoint point[],int num,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);

	void dbx(CPoint point[],int num,CDC *pDC);
private:
	CPoint m_pntStart;//起点
	CPoint m_pntEnd;// 终点
	vector<S4GraphDbx>m_dbx;
	CPoint m_point[100];//定义多边形的定点集合（默认100个点）
	int m_num;//定义点的数量

};

//-------------------函数实现部分-------------------------
void S4GraphDbx::dbx(CPoint point[],int num,CDC *pDC)
{

	for (int i=0;i<num-1;i++)
	{
		pDC->MoveTo(point[i]);
		pDC->LineTo(point[i+1]);
	}
	pDC->MoveTo(point[0]);
	pDC->LineTo(point[num-1]);
}
void S4GraphDbx::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
    m_point[m_num]=point;
	m_num++;
}
void S4GraphDbx::OnMouseMove(UINT nFlags, CPoint point)
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
	dc.MoveTo(m_pntStart);
	dc.LineTo(m_pntEnd);
	dc.MoveTo(m_point[0]);
	dc.LineTo(m_pntEnd);
	dc.MoveTo(m_pntStart);
	dc.LineTo(point);
	dc.MoveTo(m_point[0]);
	dc.LineTo(point);
	m_pntEnd=point;
    //删除画笔
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S4GraphDbx::OnLButtonUp(UINT nFlags, CPoint point)
{
	
}

S4GraphDbx::S4GraphDbx(CPoint point[],int num,int ps,int with,COLORREF color)//构造函数
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
void S4GraphDbx::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_dbx.push_back(S4GraphDbx(m_point,m_num,m_ps,m_with,m_color));
	m_num=0;
}
void S4GraphDbx::Draw(CDC *pDC)
{
	//设置画笔
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//设置透明画刷
	CPen pen_v(m_ps,m_with,m_color);//加载线条设置

	pDC->SelectObject(pen_v);
	pDC->SelectObject(pBrush);

    dbx(m_point,m_num,pDC);
	//删除画笔
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S4GraphDbx::DrawGraph(CDC *pDC)//绘图功能
{
	
	int index=m_dbx.size();
	while (index)
	{
		m_dbx.at(index-1).Draw(pDC);
		index--;
	}
}
void S4GraphDbx::OnEditUndo()//undo功能
{
	int index;
	index=m_dbx.size()-1;
	if (index>=0)
	{
		m_dbx.pop_back();
	}
}
void S4GraphDbx::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_dbx.size());
}
BOOL S4GraphDbx::isEqual()
{
	return (m_dbx.size()==m_number);
}
void S4GraphDbx::OnFileSave()//保存文件
{
	CFileDialog saveDlg(FALSE,_T("4dbc Files (*.4dbc)|*.4dbc"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("dbc Files (*.4dbc)|*.4dbc||"));
	CString pathname;//路径
	saveDlg.m_ofn.lpstrTitle=_T("保存您的文件");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_dbx.size();
		int i=0;
		for (i=0;i<m_dbx.size();i++)
		{
			for (int j=0;j<100;j++)//储存那100个点
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
void S4GraphDbx::OnFileOpen(CString pathname)//打开文件
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_dbx.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		for (int j=0;j<100;j++)//储存那100个点
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
void S4GraphDbx::getSeting(int ps,int with,COLORREF color)//得到设置
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
//判断是否在选框内的函数
bool S4GraphDbx::isIn(CPoint pntStart,CPoint pntEnd,CPoint point[],int num)//判断点是否在选框内的函数
{
	int temp1=1;
	for (int i=0;i<num;i++)
	{
		int x_a=pntStart.x-point[i].x;
		int x_b=pntEnd.x-point[i].x;
		int y_a=pntStart.y-point[i].y;
		int y_b=pntEnd.y-point[i].y;
		if (x_a*x_b<0&&y_a*y_b<0)
		{
			temp1=1;
		}
		else
			return false;
	}
   return true;
		
}
//选择功能的实现
void S4GraphDbx::OnSelect(CPoint pntStart,CPoint pntEnd)
{
	int index=m_dbx.size();
	while (index)
	{		
		if (isIn(pntStart,pntEnd,m_dbx.at(index-1).m_point,m_dbx.at(index-1).m_num))
		{
			m_dbx.at(index-1).m_color=RGB(255,0,0);
			//AfxMessageBox(_T("图形被选中"));
			m_dbx.at(index-1).isSelect=1;
		}
		index--;
	}
}

void S4GraphDbx::PY(int x,int y,CDC *pDC)//平移
{
	int index=m_dbx.size();
	for (int i=0;i<index;i++)
	{
		if (m_dbx.at(i).isSelect==1)
		{
			for (int j=0;j<m_dbx.at(i).m_num;j++)
			{
				m_dbx.at(i).m_point[j].x+=x;
				m_dbx.at(i).m_point[j].y+=y;
			}
		}
	}
	while (index)
	{
		m_dbx.at(index-1).Draw(pDC);
		index--;
	}
}
void S4GraphDbx::FS(float x,float y,CDC *pDC)//放缩
{
	int index=m_dbx.size();
	for (int i=0;i<index;i++)
	{
		if (m_dbx.at(i).isSelect==1)
		{
			for (int j=0;j<m_dbx.at(i).m_num;j++)
			{
				m_dbx.at(i).m_point[j].x*=x;
				m_dbx.at(i).m_point[j].y*=y;
			}
		}
	}
	while (index)
	{
		m_dbx.at(index-1).Draw(pDC);
		index--;
	}
}

//*******************************旋转的一系列函数**********************************
void allpoints(float x,CPoint p[],int m)
{
	for (int i=0;i<m;i++)
	{
		int tx=p[i].x-600;
		int ty=350-p[i].y;
		//求r
		float r=sqrtf((tx)*(tx)+(ty)*(ty));
		//求初始角度
		//float iniJD=acosf(tx/r);
		//float nowJD=x/180*3.1415926;
		float iniJD;
		if (ty>0)
		{
			iniJD=acosf(tx/r)/3.1415926*180;
		}
		else
		{
			//iniJD=asinf(ty/r)/3.1415926*180;
			iniJD=-1*acosf(tx/r)/3.1415926*180;
		}
		
		float temp=(iniJD-x)/180*3.1415926;
		p[i].x=r*cosf(temp)+600;
		p[i].y=-1*r*sinf(temp)+350;
	}
}
void S4GraphDbx::XZ(float x,CDC *pDC)//旋转的函数
{
	int index=m_dbx.size();
	for (int i=0;i<index;i++)
	{
		if (m_dbx.at(i).isSelect==1)
		{
			allpoints(x,m_dbx.at(i).m_point,m_dbx.at(i).m_num);
		}
	}
	while (index)
	{
		m_dbx.at(index-1).Draw(pDC);
		index--;
	}
}
#endif