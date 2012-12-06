 #ifndef  S1GRAPHLINE_H_H
 #define S1GRAPHLINE_H_H
#include "SGraphBasic.h"
#include <vector>
using namespace std;
class S1GraphLine : public SGraphBasic
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
	S1GraphLine(){}
	~S1GraphLine(){}
public://��ӵĺ���
	S1GraphLine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
	vector<S1GraphLine>m_Lines;
};

//-------------------����ʵ�ֲ���-------------------------

void S1GraphLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pntEnd=point;
	m_pntStart=point;
}
void S1GraphLine::OnMouseMove(UINT nFlags, CPoint point)
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
void S1GraphLine::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_Lines.push_back(S1GraphLine(m_pntStart,point,m_ps,m_with,m_color));
}
S1GraphLine::S1GraphLine(CPoint pntStart,CPoint pntEnd,int ps,int with,COLORREF color)//���캯��
{
	m_pntStart=pntStart;
	m_pntEnd=pntEnd;
	m_ps=ps;
	m_with=with;
	m_color=color;
}
void S1GraphLine::Draw(CDC *pDC)
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
void S1GraphLine::DrawGraph(CDC *pDC)//��ͼ����
{
	
	int index=m_Lines.size();
	while (index)
	{
		m_Lines.at(index-1).Draw(pDC);
		index--;
	}
}
void S1GraphLine::OnEditUndo()//undo����
{
	int index;
	index=m_Lines.size()-1;
	if (index>=0)
	{
		m_Lines.pop_back();
	}
}
void S1GraphLine::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Lines.size());
}
BOOL S1GraphLine::isEqual()
{
	return (m_Lines.size()==m_number);
}
void S1GraphLine::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("1Line Files (*.1line)|*.1line"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("1Line Files (*.1line)|*.1line||"));
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
void S1GraphLine::OnFileOpen(CString pathname)//���ļ�
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
void S1GraphLine::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
#endif