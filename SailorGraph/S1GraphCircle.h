 #ifndef  S1GRAPHCIRCLE_H_H
 #define S1GRAPHCIRCLE_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;

class S1GraphCircle : public SGraphBasic
{
public://��Ϣ��Ӧ�ĺ���
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	void OnSelect(CPoint pntStart,CPoint pntEnd);
	BOOL    isEqual();
public://Ĭ�Ϲ�����������
	S1GraphCircle(){}
	~S1GraphCircle(){}
public://��ӵĺ���
	S1GraphCircle(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
	vector<S1GraphCircle>m_Circles;
};

//-------------------����ʵ�ֲ���-------------------------

void S1GraphCircle::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S1GraphCircle::OnMouseMove(UINT nFlags, CPoint point)
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
	dc.Ellipse(m_pntStart.x,m_pntStart.y,m_pntEnd.x,m_pntEnd.y);
	dc.Ellipse(m_pntStart.x,m_pntStart.y,point.x,point.y);
	m_pntEnd=point;
    //ɾ������
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S1GraphCircle::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_Circles.push_back(S1GraphCircle(m_pntStart,point,m_ps,m_with,m_color));
}
S1GraphCircle::S1GraphCircle(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//���캯��
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S1GraphCircle::Draw(CDC *pDC)
{
	//���û���
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//����͸����ˢ
	CPen pen_v(m_ps,m_with,m_color);//������������

	pDC->SelectObject(pen_v);
	pDC->SelectObject(pBrush);

	pDC->Ellipse(m_pntStart.x,m_pntStart.y,m_pntEnd.x,m_pntEnd.y);
	//ɾ������
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S1GraphCircle::DrawGraph(CDC *pDC)//��ͼ����
{
	
	int index=m_Circles.size();
	while (index)
	{
		m_Circles.at(index-1).Draw(pDC);
		index--;
	}
}
void S1GraphCircle::OnEditUndo()//undo����
{
	int index;
	index=m_Circles.size()-1;
	if (index>=0)
	{
		m_Circles.pop_back();
	}
}
void S1GraphCircle::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Circles.size());
}
BOOL S1GraphCircle::isEqual()
{
	return (m_Circles.size()==m_number);
}
void S1GraphCircle::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("1Circle Files (*.1cir)|*.1cir"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("1Circle Files (*.1cir)|*.1cir||"));
	CString pathname;//·��
	saveDlg.m_ofn.lpstrTitle=_T("���������ļ�");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_Circles.size();
		int i=0;
		for (i=0;i<m_Circles.size();i++)
		{
			ar<<m_Circles[i].m_pntStart;
			ar<<m_Circles[i].m_pntEnd;
			ar<<m_Circles[i].m_ps<<m_Circles[i].m_with<<m_Circles[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S1GraphCircle::OnFileOpen(CString pathname)//���ļ�
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_Circles.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_Circles[i].m_pntStart;
		ar>>m_Circles[i].m_pntEnd;
		ar>>m_Circles[i].m_ps>>m_Circles[i].m_with>>m_Circles[i].m_color;
	}
	m_number=m_Circles.size();
	ar.Close();
	flieSave.Close();
}
void S1GraphCircle::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}

bool isIn(CPoint pntStart,CPoint pntEnd,CPoint isStart,CPoint isEnd)//�жϵ��Ƿ���ѡ���ڵĺ���
{
    //���ж�����Ƿ���ѡ����
	int temp1=0;
	int temp2=0;
	int x_a=pntStart.x-isStart.x;
	int x_b=pntStart.x-isEnd.x;
	int y_a=pntStart.y-isStart.y;
	int y_b=pntStart.y-isEnd.y;
	if (x_a*x_b<0&&y_a*y_b<0)
	{
		temp1=1;
	}
	//�ж��յ��Ƿ���ѡ����
	x_a=pntEnd.x-isStart.x;
	x_b=pntEnd.x-isEnd.x;
	y_a=pntEnd.y-isStart.y;
	y_b=pntEnd.y-isEnd.y;
	if (x_a*x_b<0&&y_a*y_b<0)
	{
		temp2=1;
	}
	if (temp1==1&&temp2==1)
	{
		return true;
	}
	else
		return false;
}

void S1GraphCircle::OnSelect(CPoint pntStart,CPoint pntEnd)//ѡ����ʵ��
{
	int index=m_Circles.size();
	while (index)
	{		
		if (isIn(m_Circles.at(index-1).m_pntStart,m_Circles.at(index-1).m_pntEnd,pntStart,pntEnd))
		{
			m_Circles.at(index-1).m_color=RGB(255,0,0);
		}
		index--;
	}
}
#endif