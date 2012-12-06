 #ifndef  S1GRAPHDBX_H_H
 #define S1GRAPHDBX_H_H
#include "SGraphBasic.h"
#include <vector>
#include<stack>           //用于扫描线种子填充算法的栈
#include "my_stack.h"
using namespace std;
#define WINDOW_HEIGHT 1024
typedef struct tEdge
{
	int yUpper;                        //y坐标
	float xIntersect,dxPerScan;        //xIntersect为点的x坐标,dxPerScan为为直线斜率的倒数
	struct tEdge *next;                //
}Edge;
class S1GraphDbx : public SGraphBasic
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
	void BXG(CDC *pDC);//边相关
	void seedline(CPoint p,CDC *pDC);//扫描线种子
	
	BOOL    isEqual();
public://默认构造析构函数
	S1GraphDbx(){m_num=0;}
	~S1GraphDbx(){}
public://添加的函数
	S1GraphDbx(CPoint point[],int num,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);

	void dbx(CPoint point[],int num,CDC *pDC);
private:
	CPoint m_pntStart;//起点
	CPoint m_pntEnd;// 终点
	vector<S1GraphDbx>m_dbx;
	CPoint m_point[100];//定义多边形的定点集合（默认100个点）
	int m_num;//定义点的数量
	CPoint s_point;
};

//-------------------函数实现部分-------------------------
void S1GraphDbx::dbx(CPoint point[],int num,CDC *pDC)
{

	for (int i=0;i<num-1;i++)
	{
		pDC->MoveTo(point[i]);
		pDC->LineTo(point[i+1]);
	}
	pDC->MoveTo(point[0]);
	pDC->LineTo(point[num-1]);
}
void S1GraphDbx::OnLButtonDown(UINT nFlags, CPoint point)
{

		m_pntEnd=point;
		m_pntStart=point;
		m_point[m_num]=point;
		m_num++;

	
}
void S1GraphDbx::OnMouseMove(UINT nFlags, CPoint point)
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
void S1GraphDbx::OnLButtonUp(UINT nFlags, CPoint point)
{
	
}

S1GraphDbx::S1GraphDbx(CPoint point[],int num,int ps,int with,COLORREF color)//构造函数
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
void S1GraphDbx::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_dbx.push_back(S1GraphDbx(m_point,m_num,m_ps,m_with,m_color));
	m_num=0;
}
void S1GraphDbx::Draw(CDC *pDC)
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
void S1GraphDbx::DrawGraph(CDC *pDC)//绘图功能
{
	
	int index=m_dbx.size();
	while (index)
	{
		m_dbx.at(index-1).Draw(pDC);
		index--;
	}
}
void S1GraphDbx::OnEditUndo()//undo功能
{
	int index;
	index=m_dbx.size()-1;
	if (index>=0)
	{
		m_dbx.pop_back();
	}
}
void S1GraphDbx::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_dbx.size());
}
BOOL S1GraphDbx::isEqual()
{
	return (m_dbx.size()==m_number);
}
void S1GraphDbx::OnFileSave()//保存文件
{
	CFileDialog saveDlg(FALSE,_T("dbc Files (*.dbc)|*.dbc"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("dbc Files (*.dbc)|*.dbc||"));
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
void S1GraphDbx::OnFileOpen(CString pathname)//打开文件
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
void S1GraphDbx::getSeting(int ps,int with,COLORREF color)//得到设置
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
//判断是否在选框内的函数
bool isIn(CPoint pntStart,CPoint pntEnd,CPoint point[],int num)//判断点是否在选框内的函数
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
void S1GraphDbx::OnSelect(CPoint pntStart,CPoint pntEnd)
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


//下面的是进行边相关扫描的函数集合××××××××××××××××××××××××××××××××××××××××××
void insertEdge(Edge *list, Edge *edge)  //将扫描的边以X的升序排序(插入边且进行排序)
{
	Edge *p,*q=list;
	p=q->next;
	while(p!=NULL)
	{
		if(edge->xIntersect<p->xIntersect)  //升序排列当扫描道的点已经按升序排列了
			p=NULL;                         //跳出循环
		else 
		{
			q=p; 
			p=p->next;
		}
	}                                        //否则
	edge->next=q->next;      //插入
	q->next=edge;
}
int yNext(int k, int cnt, CPoint *pts)//计算下一条非水平线的Y值
{
	int j;
	if((k+1)>(cnt-1))
		j=0;
	else
		j=k+1;
	while(pts[k].y==pts[j].y)
		if((j+1)>(cnt-1))
			j=0;
		else
			j++;
	return (pts[j].y);
}

void makeEdgeRec(CPoint lower, CPoint upper, int yComp, Edge *edge, Edge *edges[])//生成有序边表的一条边
{
	edge->dxPerScan=(float)(upper.x-lower.x)/(upper.y-lower.y);
	edge->xIntersect=lower.x;
	if(upper.y<yComp)
		edge->yUpper=upper.y-1;
	else
		edge->yUpper=upper.y;
	insertEdge(edges[lower.y],edge);
}

void buildEdgeList(int cnt, CPoint *pts, Edge *edges[])//建立有序边表
{
	Edge *edge;
	CPoint v1,v2;
	int i,yPrev=pts[cnt-2].y;
	v1.x=pts[cnt-1].x;
	v1.y=pts[cnt-1].y;
	for(i=0;i<cnt;i++)
	{
		v2=pts[i];
		if(v1.y!=v2.y)
		{
			edge=(Edge*)new(Edge);//开辟新的空间
			if(v1.y<v2.y)
				makeEdgeRec(v1,v2,yNext(i,cnt,pts),edge,edges);
			else
				makeEdgeRec(v2,v1,yPrev,edge,edges);
		}
		yPrev=v1.y;
		v1=v2;
	}
}

void buildActiveList(int scan, Edge *active, Edge *edges[])//建立活化边表
{
	Edge *p, * q;
	p=edges[scan]->next;
	while (p)
	{
		q=p->next;
		insertEdge(active,p);
		p = q;
	}
}
void fillScan(int scan,Edge *active,COLORREF color,CDC *pDC)//对当前扫描线进行填充
{
	Edge *p1,*p2;
	int i;int dell=1000000;
	p1=active->next;
	//CDC *pDC = GetDC();                                           //tianjia
	while(p1){
		p2=p1->next;
		for(i=p1->xIntersect;i<p2->xIntersect;i++)
			pDC->SetPixel((int) i,scan,color);
		while(dell!=0){dell--;}
		p1=p2->next;	
	}
}

void deleteAfter(Edge *q)//删除不再相交的边
{
	Edge *p=q->next;
	q->next=p->next;
	delete(p);
}

void updateActiveList(int scan, Edge *active)//为下条扫描线进行更新
{
	Edge * q=active, *p=active->next;
	while(p)
		if(scan>=p->yUpper){
			p=p->next;
			deleteAfter(q);
		}
		else{
			p->xIntersect = p->xIntersect+p->dxPerScan;
			q=p;
			p=p->next;
		}
}

void resortActiveList(Edge *active)//重排活化边表
{
	Edge *q,*p=active->next;
	active->next=NULL;
	while(p){
		q=p->next;
		insertEdge(active,p);
		p=q;
	}
}
void scanFill(int cnt,CPoint *pts,COLORREF color,CDC *pDC)//循环重复填空 
{
	// TODO: Add your command handler code here
	Edge *edges[WINDOW_HEIGHT],* active;
	int i,scan;

	for(i=0;i<WINDOW_HEIGHT;i++){
		edges[i]=(Edge *)malloc(sizeof(Edge));
		edges[i]->next = NULL;
	}
	buildEdgeList(cnt,pts,edges);
	active = (Edge *)new(Edge);
	active->next=NULL;

	for(scan=0;scan<WINDOW_HEIGHT;scan++){
		buildActiveList(scan,active,edges);
		if(active->next){
			fillScan(scan,active,color,pDC);
			updateActiveList(scan,active);
			resortActiveList(active);
		}
	}
}
void S1GraphDbx::BXG(CDC *pDC)
{	
    int index=m_dbx.size();
	for (int i=0;i<index;i++)
	{
		if (m_dbx.at(i).isSelect==1)
		{
			scanFill(m_dbx.at(i).m_num,m_dbx.at(i).m_point,m_dbx.at(i).m_color,pDC);
		}
	}
}

//××××××××××××××××下面要进行的是扫描线种子填充的函数××××××××××××××
 void S1GraphDbx::seedline(CPoint p,CDC *pDC)
{
	//求多边形的最大最小值
	int index=m_dbx.size();
	int i;
	COLORREF fill=RGB(255,0,0);
	COLORREF boundary=RGB(0,0,0);
	for (i=0;i<index;i++)
	{
		if (m_dbx.at(i).isSelect==1)
		{
			CPoint seed, newSeed; 
			int xLeft, xRight, x, y;  //[xLeft, xRight]表示扫描线的区段，x，y表示当前的像素点左边
			int needFill = FALSE; 

		    //stack<node>st;   //建立stack用于实现对像素点的操作，这里调用了STL中的stack，如果需要在减少内存，可以自己建立栈
			my_Stack<CPoint>st;
			seed.x = p.x;  //种子坐标
			seed.y = p.y; 

			// 种子入栈 
			st.Add(seed);    

			while ( !st.IsEmpty() )   //栈非空
			{ 
				//* 种子出栈并给点上色 
				seed=st.Top();
				st.Delete();
				pDC->SetPixel(seed.x,seed.y,fill);

				//* 填充当前扫描线位于种子左边的部分  
				x = seed.x - 1; 
				y = seed.y; 
				while ( pDC->GetPixel(x,y) != fill && 
					pDC->GetPixel(x,y) != boundary ) 
				{ 
					pDC->SetPixel(x,y,fill);
					x -= 1; 
				} 
				//* 记录最左侧的内点 
				xLeft = x + 1; 

				//* 填充当前扫描线位于种子右边的部分 
				x = seed.x + 1; 
				y = seed.y; 
				while ( pDC->GetPixel(x,y) != fill && 
					pDC->GetPixel(x,y) != boundary )
				{ 
					pDC->SetPixel(x,y,fill);
					x += 1; 
				} 
				///* 记录最右侧的内点 
				xRight = x - 1;  

				///* 上移一条扫描线 
				y = seed.y - 1; 
				x = xLeft; 
				//* 从左向右检测非边界、未填充的象素 
				while ( x < xRight ) 
				{ 
					while ( pDC->GetPixel(x,y) != fill && 
						pDC->GetPixel(x,y) != boundary )
					{ 
						///* 存在未填充的像素，则需要填充 
						needFill = TRUE; 
						x += 1; 
					} 
					//* 最右侧像素入栈 
					if ( needFill == TRUE ) 
					{ 
						newSeed.x = x - 1; 
						newSeed.y = y; 
						st.Add(newSeed);
						needFill = FALSE; 
						break; 
					} 
					x++; 
				} 
				//        delay(DELAYTIME); 

				needFill = FALSE; 
				///* 下移一条扫描线
				y = seed.y + 1; 
				x = xLeft; 
				/////* 从左向右检测非边界、未填充的象素 
				while ( x < xRight ) 
				{ 
					while ( pDC->GetPixel(x,y) != fill && 
						pDC->GetPixel(x,y) != boundary ) 
					{ 
						////* 存在未填充的像素，则需要填充 
						needFill = TRUE; 
						x += 1; 
					} 
					/////* 最右侧像素入栈 
					if ( needFill == TRUE ) 
					{ 
						newSeed.x = x - 1; 
						newSeed.y = y; 
						st.Add(newSeed);

						needFill = FALSE; 

						break; 
					} 
					x++; 
				} 
			} 
		}
	}
	
}

#endif