 #ifndef  S1GRAPHDBX_H_H
 #define S1GRAPHDBX_H_H
#include "SGraphBasic.h"
#include <vector>
#include<stack>           //����ɨ������������㷨��ջ
#include "my_stack.h"
using namespace std;
#define WINDOW_HEIGHT 1024
typedef struct tEdge
{
	int yUpper;                        //y����
	float xIntersect,dxPerScan;        //xIntersectΪ���x����,dxPerScanΪΪֱ��б�ʵĵ���
	struct tEdge *next;                //
}Edge;
class S1GraphDbx : public SGraphBasic
{
public://��Ϣ��Ӧ�ĺ���
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	void OnSelect(CPoint pntStart,CPoint pntEnd);
	void BXG(CDC *pDC);//�����
	void seedline(CPoint p,CDC *pDC);//ɨ��������
	
	BOOL    isEqual();
public://Ĭ�Ϲ�����������
	S1GraphDbx(){m_num=0;}
	~S1GraphDbx(){}
public://��ӵĺ���
	S1GraphDbx(CPoint point[],int num,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);

	void dbx(CPoint point[],int num,CDC *pDC);
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
	vector<S1GraphDbx>m_dbx;
	CPoint m_point[100];//�������εĶ��㼯�ϣ�Ĭ��100���㣩
	int m_num;//����������
	CPoint s_point;
};

//-------------------����ʵ�ֲ���-------------------------
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
void S1GraphDbx::OnLButtonUp(UINT nFlags, CPoint point)
{
	
}

S1GraphDbx::S1GraphDbx(CPoint point[],int num,int ps,int with,COLORREF color)//���캯��
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
void S1GraphDbx::DrawGraph(CDC *pDC)//��ͼ����
{
	
	int index=m_dbx.size();
	while (index)
	{
		m_dbx.at(index-1).Draw(pDC);
		index--;
	}
}
void S1GraphDbx::OnEditUndo()//undo����
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
void S1GraphDbx::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("dbc Files (*.dbc)|*.dbc"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("dbc Files (*.dbc)|*.dbc||"));
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
void S1GraphDbx::OnFileOpen(CString pathname)//���ļ�
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
void S1GraphDbx::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
//�ж��Ƿ���ѡ���ڵĺ���
bool isIn(CPoint pntStart,CPoint pntEnd,CPoint point[],int num)//�жϵ��Ƿ���ѡ���ڵĺ���
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
//ѡ���ܵ�ʵ��
void S1GraphDbx::OnSelect(CPoint pntStart,CPoint pntEnd)
{
	int index=m_dbx.size();
	while (index)
	{		
		if (isIn(pntStart,pntEnd,m_dbx.at(index-1).m_point,m_dbx.at(index-1).m_num))
		{
			m_dbx.at(index-1).m_color=RGB(255,0,0);
			//AfxMessageBox(_T("ͼ�α�ѡ��"));
			m_dbx.at(index-1).isSelect=1;
		}
		index--;
	}
}


//������ǽ��б����ɨ��ĺ������ϡ�����������������������������������������������������������������������������������
void insertEdge(Edge *list, Edge *edge)  //��ɨ��ı���X����������(������ҽ�������)
{
	Edge *p,*q=list;
	p=q->next;
	while(p!=NULL)
	{
		if(edge->xIntersect<p->xIntersect)  //�������е�ɨ����ĵ��Ѿ�������������
			p=NULL;                         //����ѭ��
		else 
		{
			q=p; 
			p=p->next;
		}
	}                                        //����
	edge->next=q->next;      //����
	q->next=edge;
}
int yNext(int k, int cnt, CPoint *pts)//������һ����ˮƽ�ߵ�Yֵ
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

void makeEdgeRec(CPoint lower, CPoint upper, int yComp, Edge *edge, Edge *edges[])//��������߱��һ����
{
	edge->dxPerScan=(float)(upper.x-lower.x)/(upper.y-lower.y);
	edge->xIntersect=lower.x;
	if(upper.y<yComp)
		edge->yUpper=upper.y-1;
	else
		edge->yUpper=upper.y;
	insertEdge(edges[lower.y],edge);
}

void buildEdgeList(int cnt, CPoint *pts, Edge *edges[])//��������߱�
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
			edge=(Edge*)new(Edge);//�����µĿռ�
			if(v1.y<v2.y)
				makeEdgeRec(v1,v2,yNext(i,cnt,pts),edge,edges);
			else
				makeEdgeRec(v2,v1,yPrev,edge,edges);
		}
		yPrev=v1.y;
		v1=v2;
	}
}

void buildActiveList(int scan, Edge *active, Edge *edges[])//������߱�
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
void fillScan(int scan,Edge *active,COLORREF color,CDC *pDC)//�Ե�ǰɨ���߽������
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

void deleteAfter(Edge *q)//ɾ�������ཻ�ı�
{
	Edge *p=q->next;
	q->next=p->next;
	delete(p);
}

void updateActiveList(int scan, Edge *active)//Ϊ����ɨ���߽��и���
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

void resortActiveList(Edge *active)//���Ż�߱�
{
	Edge *q,*p=active->next;
	active->next=NULL;
	while(p){
		q=p->next;
		insertEdge(active,p);
		p=q;
	}
}
void scanFill(int cnt,CPoint *pts,COLORREF color,CDC *pDC)//ѭ���ظ���� 
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

//������������������������������������Ҫ���е���ɨ�����������ĺ�������������������������������
 void S1GraphDbx::seedline(CPoint p,CDC *pDC)
{
	//�����ε������Сֵ
	int index=m_dbx.size();
	int i;
	COLORREF fill=RGB(255,0,0);
	COLORREF boundary=RGB(0,0,0);
	for (i=0;i<index;i++)
	{
		if (m_dbx.at(i).isSelect==1)
		{
			CPoint seed, newSeed; 
			int xLeft, xRight, x, y;  //[xLeft, xRight]��ʾɨ���ߵ����Σ�x��y��ʾ��ǰ�����ص����
			int needFill = FALSE; 

		    //stack<node>st;   //����stack����ʵ�ֶ����ص�Ĳ��������������STL�е�stack�������Ҫ�ڼ����ڴ棬�����Լ�����ջ
			my_Stack<CPoint>st;
			seed.x = p.x;  //��������
			seed.y = p.y; 

			// ������ջ 
			st.Add(seed);    

			while ( !st.IsEmpty() )   //ջ�ǿ�
			{ 
				//* ���ӳ�ջ��������ɫ 
				seed=st.Top();
				st.Delete();
				pDC->SetPixel(seed.x,seed.y,fill);

				//* ��䵱ǰɨ����λ��������ߵĲ���  
				x = seed.x - 1; 
				y = seed.y; 
				while ( pDC->GetPixel(x,y) != fill && 
					pDC->GetPixel(x,y) != boundary ) 
				{ 
					pDC->SetPixel(x,y,fill);
					x -= 1; 
				} 
				//* ��¼�������ڵ� 
				xLeft = x + 1; 

				//* ��䵱ǰɨ����λ�������ұߵĲ��� 
				x = seed.x + 1; 
				y = seed.y; 
				while ( pDC->GetPixel(x,y) != fill && 
					pDC->GetPixel(x,y) != boundary )
				{ 
					pDC->SetPixel(x,y,fill);
					x += 1; 
				} 
				///* ��¼���Ҳ���ڵ� 
				xRight = x - 1;  

				///* ����һ��ɨ���� 
				y = seed.y - 1; 
				x = xLeft; 
				//* �������Ҽ��Ǳ߽硢δ�������� 
				while ( x < xRight ) 
				{ 
					while ( pDC->GetPixel(x,y) != fill && 
						pDC->GetPixel(x,y) != boundary )
					{ 
						///* ����δ�������أ�����Ҫ��� 
						needFill = TRUE; 
						x += 1; 
					} 
					//* ���Ҳ�������ջ 
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
				///* ����һ��ɨ����
				y = seed.y + 1; 
				x = xLeft; 
				/////* �������Ҽ��Ǳ߽硢δ�������� 
				while ( x < xRight ) 
				{ 
					while ( pDC->GetPixel(x,y) != fill && 
						pDC->GetPixel(x,y) != boundary ) 
					{ 
						////* ����δ�������أ�����Ҫ��� 
						needFill = TRUE; 
						x += 1; 
					} 
					/////* ���Ҳ�������ջ 
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