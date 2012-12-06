 #ifndef  S4GRAPHDBX_H_H
 #define S4GRAPHDBX_H_H
#include "SGraphBasic.h"
#include <vector>
#include <cmath>
using namespace std;

class S4GraphDbx : public SGraphBasic
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
	bool isIn(CPoint pntStart,CPoint pntEnd,CPoint point[],int num);//�жϵ��Ƿ���ѡ���ڵĺ���
	void PY(int x,int y,CDC *pDC);//ƽ�ƺ���
	void FS(float x,float y,CDC *pDC);//��������
	void XZ(float x,CDC *pDC);//����
	BOOL    isEqual();
public://Ĭ�Ϲ�����������
	S4GraphDbx(){m_num=0;}
	~S4GraphDbx(){}
public://��ӵĺ���
	S4GraphDbx(CPoint point[],int num,int ps,int with,COLORREF color);
	void Draw(CDC *pDC);
	void OnFileSave();
	void OnFileOpen(CString pathname);
	void getSeting(int ps,int with,COLORREF m_color);

	void dbx(CPoint point[],int num,CDC *pDC);
private:
	CPoint m_pntStart;//���
	CPoint m_pntEnd;// �յ�
	vector<S4GraphDbx>m_dbx;
	CPoint m_point[100];//�������εĶ��㼯�ϣ�Ĭ��100���㣩
	int m_num;//����������

};

//-------------------����ʵ�ֲ���-------------------------
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
void S4GraphDbx::OnLButtonUp(UINT nFlags, CPoint point)
{
	
}

S4GraphDbx::S4GraphDbx(CPoint point[],int num,int ps,int with,COLORREF color)//���캯��
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
void S4GraphDbx::DrawGraph(CDC *pDC)//��ͼ����
{
	
	int index=m_dbx.size();
	while (index)
	{
		m_dbx.at(index-1).Draw(pDC);
		index--;
	}
}
void S4GraphDbx::OnEditUndo()//undo����
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
void S4GraphDbx::OnFileSave()//�����ļ�
{
	CFileDialog saveDlg(FALSE,_T("4dbc Files (*.4dbc)|*.4dbc"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("dbc Files (*.4dbc)|*.4dbc||"));
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
void S4GraphDbx::OnFileOpen(CString pathname)//���ļ�
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
void S4GraphDbx::getSeting(int ps,int with,COLORREF color)//�õ�����
{
	m_ps=ps;
	m_with=with;
	m_color=color;
}
//�ж��Ƿ���ѡ���ڵĺ���
bool S4GraphDbx::isIn(CPoint pntStart,CPoint pntEnd,CPoint point[],int num)//�жϵ��Ƿ���ѡ���ڵĺ���
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
void S4GraphDbx::OnSelect(CPoint pntStart,CPoint pntEnd)
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

void S4GraphDbx::PY(int x,int y,CDC *pDC)//ƽ��
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
void S4GraphDbx::FS(float x,float y,CDC *pDC)//����
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

//*******************************��ת��һϵ�к���**********************************
void allpoints(float x,CPoint p[],int m)
{
	for (int i=0;i<m;i++)
	{
		int tx=p[i].x-600;
		int ty=350-p[i].y;
		//��r
		float r=sqrtf((tx)*(tx)+(ty)*(ty));
		//���ʼ�Ƕ�
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
void S4GraphDbx::XZ(float x,CDC *pDC)//��ת�ĺ���
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