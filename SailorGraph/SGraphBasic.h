#ifndef   SGRAPHBASIC_H_H
#define  SGRAPHBASIC_H_H
class SGraphBasic
{
public:
    SGraphBasic(){}//���캯��
	virtual void OnLButtonDown(UINT nFlags, CPoint point){}
	virtual void OnMouseMove(UINT nFlags, CPoint point){}
	virtual void OnLButtonUp(UINT nFlags, CPoint point){}
	virtual void OnRButtonDown(UINT nFlags, CPoint point){}
	virtual void DrawGraph(CDC *pDC){}//��ͼ����
	virtual void OnEditUndo(){}//undo����
	virtual void OnUpdateEditUndo(CCmdUI *pCmdUI){}
	virtual BOOL    isEqual(){return 0;}//�õ���Ŀ
	virtual void OnFileSave(){}//���溯��
	virtual void OnFileOpen(CString pathname){}//�򿪺���
	virtual void getSeting(int ps,int with,COLORREF m_color){}
	virtual void OnSelect(CPoint pntStart,CPoint pntEnd){}//ͼ��ѡ��ĺ���
	virtual void BXG(CDC *pDC){}//�������亯��
	virtual void PY(int x,int y,CDC *pDC){}//ƽ�ƺ���
	virtual void FS(float x,float y,CDC *pDC){}//��������
	virtual void XZ(float x,CDC *pDC){}//��ת����
	virtual void seedline(CPoint p,CDC *pDC){}//ɨ�����������ĺ���
	virtual void C_S(CPoint p1,CPoint p2,CDC *pDC){}//c_sֱ�߼����㷨
	virtual void L_B(CPoint p1,CPoint p2,CDC *pDC){}//l_bֱ�߼����㷨
	virtual void JC_DBC(CPoint p1,CPoint p2,CDC *pDC){}//����м���
	virtual ~SGraphBasic(){}//��������
public:
	void getView(CSailorGraphView *pvv);//�õ���ͼָ��
	
public:
	CSailorGraphView *pv;
	int m_ps;
	int m_with;
	int m_number;//�����ж��Ƿ��޸�
	int isSelect;//�����ж��Ƿ�ѡ��ͼ��
	COLORREF m_color;
};

void SGraphBasic::getView(CSailorGraphView *pvv)
{
	pv=pvv;
}

#endif