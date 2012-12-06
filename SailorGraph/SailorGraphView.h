
// SailorGraphView.h : CSailorGraphView 类的接口
//


#pragma once


class CSailorGraphView : public CView
{
protected: // 仅从序列化创建
	CSailorGraphView();
	DECLARE_DYNCREATE(CSailorGraphView)

// 属性
public:
	CSailorGraphDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSailorGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void On1Line();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnSetting();
	afx_msg void On1Circle();
	afx_msg void On1Rect();
	afx_msg void OnUpdateSetting(CCmdUI *pCmdUI);

	afx_msg void On2Dda();
	afx_msg void On2Breline();
	afx_msg void On2Zengliang();
	afx_msg void On2Brecir();
	afx_msg void On2Zhongdian();
	afx_msg void OnClearstation();
	afx_msg void OnUpdateClearstation(CCmdUI *pCmdUI);
	afx_msg void OnOnselect();
	afx_msg void OnUpdateOnselect(CCmdUI *pCmdUI);
	afx_msg void OnDbx();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void On3Bxg();
	afx_msg void On3Smxzz();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void On4Dbx();
	afx_msg void OnPy();
	afx_msg void On4Xz();
	afx_msg void On4Fs();
	afx_msg void On5Drawline();
	afx_msg void On5CohenSutherland();
	afx_msg void On5Liangbarsky();
	afx_msg void On5Drawsbx();
	afx_msg void On5Cjdbx();
	afx_msg void On6Berier();
	afx_msg void On6Byt();
};
#ifndef _DEBUG  // SailorGraphView.cpp 中的调试版本
inline CSailorGraphDoc* CSailorGraphView::GetDocument() const
   { return reinterpret_cast<CSailorGraphDoc*>(m_pDocument); }
#endif

