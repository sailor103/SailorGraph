// SetTing.cpp : 实现文件
//

#include "stdafx.h"
#include "SailorGraph.h"
#include "SetTing.h"


// CSetTing 对话框

IMPLEMENT_DYNAMIC(CSetTing, CDialog)

CSetTing::CSetTing(CWnd* pParent /*=NULL*/)
	: CDialog(CSetTing::IDD, pParent)
	, m_sliderValues(0)
{

}

CSetTing::~CSetTing()
{
}

void CSetTing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_SETWITH, m_slider);
	DDX_Control(pDX, IDC_COMBO_SETSTYLE, m_combox);
	DDX_Text(pDX, IDC_EDIT_SLIDER, m_sliderValues);
}


BEGIN_MESSAGE_MAP(CSetTing, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SETCOLOR, &CSetTing::OnBnClickedButtonSetcolor)
	ON_BN_CLICKED(IDOK, &CSetTing::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &CSetTing::OnBnClickedButtonPreview)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SETWITH, &CSetTing::OnNMCustomdrawSliderSetwith)
END_MESSAGE_MAP()


// CSetTing 消息处理程序

BOOL CSetTing::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	m_slider.SetRange(0,30);
	m_combox.InsertString(0,_T("实线"));
	m_combox.InsertString(1,_T("--------------"));
	m_combox.InsertString(2,_T("....................."));
	m_combox.InsertString(3,_T("_._._._._._._._"));
	m_combox.InsertString(4,_T("_.._.._.._.._.._"));
	m_combox.SetCurSel(0);
	return 0;
}

void CSetTing::OnBnClickedButtonSetcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	if(cDlg.DoModal()==IDOK)
	{
		m_color=cDlg.m_cc.rgbResult;
	}
}

void CSetTing::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_With=m_slider.GetPos();
	m_ps=m_combox.GetCurSel();
	OnOK();
}

void CSetTing::OnBnClickedButtonPreview()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}

void CSetTing::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CPen pen(m_combox.GetCurSel(),m_slider.GetPos(),cDlg.m_cc.rgbResult);

	dc.SelectObject(&pen);
	CRect rect;
	GetDlgItem(IDC_STATIC_PREVIEW)->GetWindowRect(&rect);  //获得一个相对于Windows桌面的矩形
	ScreenToClient(&rect); //将它们转化为相对于应用程序对话框的矩形
	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);  //在示例框的中部画线
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);
	// 不为绘图消息调用 CDialog::OnPaint()
}

void CSetTing::OnNMCustomdrawSliderSetwith(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_sliderValues=m_slider.GetPos();
	UpdateData(FALSE);
	*pResult = 0;
}
