 #ifndef  S1GRAPHRECT_H_H
 #define S1GRAPHRECT_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;
class S1GraphRect : public SGraphBasic
{
public://��Ϣ��Ӧ�ĺ���
    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGraph(CDC *pDC);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI *pCmdUI);
	BOOL    isEqual();
public://Ĭ�Ϲ�����������
	S1GraphRect(){}
	~S1GraphRect(){}
public://��ӵĺ���
	S1GraphRect(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
	vector<S1GraphRect>m_Rects;
};

//-------------------����ʵ�ֲ���-------------------------

void S1GraphRect::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S1GraphRect::OnMouseMove(UINT nFlags, CPoint point)
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
    dc.Rectangle(m_pntStart.x,m_pntStart.y,m_pntEnd.x,m_pntEnd.y);
	dc.Rectangle(m_pntStart.x,m_pntStart.y,point.x,point.y);
	m_pntEnd=point;
    //ɾ������
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S1GraphRect::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_Rects.push_back(S1GraphRect(m_pntStart,point,m_ps,m_with,m_color));
}
S1GraphRect::S1GraphRect(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//���캯��
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S1GraphRect::Draw(CDC *pDC)
{
	//���û���
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//����͸����ˢ
	CPen pen_v(m_ps,m_with,m_color);//������������

	pDC->SelectObject(pen_v);
	pDC->SelectObject(pBrush);

    pDC->Rectangle(m_pntStart.x,m_pntStart.y,m_pntEnd.x,m_pntEnd.y);
	//ɾ������
	pen_v.DeleteObject();
	pBrush->DeleteObject();
}
void S1GraphRect::DrawGraph(CDC *pDC)//��ͼ����
{
	
	int index=m_Rects.size();
	while (index)
	{
		m_Rects.at(index-1).Draw(pDC);
		index--;
	}
}
void S1GraphRect::OnEditUndo()//undo����
{
	int index;
	index=m_Rects.size()-1;
	if (index>=0)
	{
		m_Rects.pop_back();
	}
}
void S1GraphRect::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Rects.size());
}
BOOL S1GraphRect::isEqual()
{
	return (m_Rects.size()==m_number);
}
void S1GraphRect::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("1Rect Files (*.1rec)|*.1rec"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("1Rect Files (*.1rec)|*.1rec||"));
	CString pathname;//·��
	saveDlg.m_ofn.lpstrTitle=_T("���������ļ�");
	if (saveDlg.DoModal()==IDOK)
	{
		pathname=saveDlg.GetPathName();
		CFile flieSave(pathname,CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&flieSave,CArchive::store);
		ar<<m_Rects.size();
		int i=0;
		for (i=0;i<m_Rects.size();i++)
		{
			ar<<m_Rects[i].m_pntStart;
			ar<<m_Rects[i].m_pntEnd;
			ar<<m_Rects[i].m_ps<<m_Rects[i].m_with<<m_Rects[i].m_color;
		}
		ar.Close();
		flieSave.Close();

	}
	
}
void S1GraphRect::OnFileOpen(CString pathname)//���ļ�
{
	CFile flieSave(pathname,CFile::modeRead);
	CArchive ar(&flieSave,CArchive::load);
	int num;
	ar>>num;
	m_Rects.resize(num);
	int i=0;
	for (i=0;i<num;i++)
	{
		ar>>m_Rects[i].m_pntStart;
		ar>>m_Rects[i].m_pntEnd;
		ar>>m_Rects[i].m_ps>>m_Rects[i].m_with>>m_Rects[i].m_color;
	}
	m_number=m_Rects.size();
	ar.Close();
	flieSave.Close();
}
void S1GraphRect::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
#endif