#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSetTing 对话框

class CSetTing : public CDialog
{
	DECLARE_DYNAMIC(CSetTing)

public:
	CSetTing(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetTing();

// 对话框数据
	enum { IDD = IDD_DIALOG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_slider;
	CComboBox m_combox;
	CColorDialog cDlg;
	int m_With;
	COLORREF m_color;
	int m_ps;
	virtual BOOL OnInitDialog(void);
	afx_msg void OnBnClickedButtonSetcolor();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonPreview();
	afx_msg void OnPaint();
	int m_sliderValues;
	afx_msg void OnNMCustomdrawSliderSetwith(NMHDR *pNMHDR, LRESULT *pResult);
};
