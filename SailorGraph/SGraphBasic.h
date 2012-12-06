#ifndef   SGRAPHBASIC_H_H
#define  SGRAPHBASIC_H_H
class SGraphBasic
{
public:
    SGraphBasic(){}//构造函数
	virtual void OnLButtonDown(UINT nFlags, CPoint point){}
	virtual void OnMouseMove(UINT nFlags, CPoint point){}
	virtual void OnLButtonUp(UINT nFlags, CPoint point){}
	virtual void OnRButtonDown(UINT nFlags, CPoint point){}
	virtual void DrawGraph(CDC *pDC){}//绘图函数
	virtual void OnEditUndo(){}//undo函数
	virtual void OnUpdateEditUndo(CCmdUI *pCmdUI){}
	virtual BOOL    isEqual(){return 0;}//得到数目
	virtual void OnFileSave(){}//保存函数
	virtual void OnFileOpen(CString pathname){}//打开函数
	virtual void getSeting(int ps,int with,COLORREF m_color){}
	virtual void OnSelect(CPoint pntStart,CPoint pntEnd){}//图形选择的函数
	virtual void BXG(CDC *pDC){}//边相关填充函数
	virtual void PY(int x,int y,CDC *pDC){}//平移函数
	virtual void FS(float x,float y,CDC *pDC){}//放缩函数
	virtual void XZ(float x,CDC *pDC){}//旋转函数
	virtual void seedline(CPoint p,CDC *pDC){}//扫描线种子填充的函数
	virtual void C_S(CPoint p1,CPoint p2,CDC *pDC){}//c_s直线剪裁算法
	virtual void L_B(CPoint p1,CPoint p2,CDC *pDC){}//l_b直线剪裁算法
	virtual void JC_DBC(CPoint p1,CPoint p2,CDC *pDC){}//多变行剪裁
	virtual ~SGraphBasic(){}//析构函数
public:
	void getView(CSailorGraphView *pvv);//得到绘图指针
	
public:
	CSailorGraphView *pv;
	int m_ps;
	int m_with;
	int m_number;//用于判断是否修改
	int isSelect;//用于判断是否选中图像
	COLORREF m_color;
};

void SGraphBasic::getView(CSailorGraphView *pvv)
{
	pv=pvv;
}

#endif