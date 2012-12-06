// 4PY.cpp : 实现文件
//

#include "stdafx.h"
#include "SailorGraph.h"
#include "4PY.h"


// C4PY 对话框

IMPLEMENT_DYNAMIC(C4PY, CDialog)

C4PY::C4PY(CWnd* pParent /*=NULL*/)
	: CDialog(C4PY::IDD, pParent)
	, m_x(0)
	, m_y(0)
	, m_x_l(0)
	, m_x_r(0)
	, m_y_u(0)
	, m_y_d(0)
{

}

C4PY::~C4PY()
{
}

void C4PY::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PY_X, m_x);
	DDX_Text(pDX, IDC_EDIT_PY_Y, m_y);
}


BEGIN_MESSAGE_MAP(C4PY, CDialog)
	
	ON_BN_CLICKED(IDC_RADIO_PY_X_L, &C4PY::OnBnClickedRadioPyXL)
	ON_BN_CLICKED(IDC_RADIO_PY_X_R, &C4PY::OnBnClickedRadioPyXR)
	ON_BN_CLICKED(IDC_RADIO_PY_Y_U, &C4PY::OnBnClickedRadioPyYU)
	ON_BN_CLICKED(IDC_RADIO_PY_Y_D, &C4PY::OnBnClickedRadioPyYD)
END_MESSAGE_MAP()


// C4PY 消息处理程序



void C4PY::OnBnClickedRadioPyXL()
{
	// TODO: 在此添加控件通知处理程序代码
	m_x_l=1;
}

void C4PY::OnBnClickedRadioPyXR()
{
	// TODO: 在此添加控件通知处理程序代码
	m_x_l=0;
}

void C4PY::OnBnClickedRadioPyYU()
{
	// TODO: 在此添加控件通知处理程序代码
	m_y_u=1;
}

void C4PY::OnBnClickedRadioPyYD()
{
	// TODO: 在此添加控件通知处理程序代码
	m_y_u=0;
}
