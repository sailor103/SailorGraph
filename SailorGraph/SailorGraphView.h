
// SailorGraphView.h : CSailorGraphView ��Ľӿ�
//


#pragma once


class CSailorGraphView : public CView
{
protected: // �������л�����
	CSailorGraphView();
	DECLARE_DYNCREATE(CSailorGraphView)

// ����
public:
	CSailorGraphDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSailorGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
#ifndef _DEBUG  // SailorGraphView.cpp �еĵ��԰汾
inline CSailorGraphDoc* CSailorGraphView::GetDocument() const
   { return reinterpret_cast<CSailorGraphDoc*>(m_pDocument); }
#endif

