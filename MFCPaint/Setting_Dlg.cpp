// Setting_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCPaint.h"
#include "Setting_Dlg.h"

#include "CMy_Global.h"
#include "MainFrm.h"
#include "MFCPaintView.h"

// Setting_Dlg

IMPLEMENT_DYNCREATE(Setting_Dlg, CFormView)

Setting_Dlg::Setting_Dlg()
	: CFormView(IDD_Setting_Dlg)
	, m_text(_T(""))
{

}

Setting_Dlg::~Setting_Dlg()
{
}

void Setting_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO3, m_combo3);
	DDX_Control(pDX, IDC_COMBO4, m_combo4);
	DDX_Control(pDX, IDC_COMBO5, m_combo5);
	//  DDX_Control(pDX, IDC_COMBO6, m_combo5);
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDX_Control(pDX, IDC_COMBO6, m_combo6);
}

BEGIN_MESSAGE_MAP(Setting_Dlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Setting_Dlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &Setting_Dlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &Setting_Dlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &Setting_Dlg::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO5, &Setting_Dlg::OnCbnSelchangeCombo5)
	ON_CBN_SELCHANGE(IDC_COMBO6, &Setting_Dlg::OnCbnSelchangeCombo6)
	ON_BN_CLICKED(IDC_BUTTON3, &Setting_Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &Setting_Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &Setting_Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Setting_Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &Setting_Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Setting_Dlg 诊断

#ifdef _DEBUG
void Setting_Dlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Setting_Dlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Setting_Dlg 消息处理程序


void Setting_Dlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	m_combo1.AddString(TEXT("直线"));
	m_combo1.AddString(TEXT("矩形"));
	m_combo1.AddString(TEXT("正圆"));
	m_combo1.AddString(TEXT("椭圆"));
	m_combo1.AddString(TEXT("曲线"));
	m_combo1.AddString(TEXT("画笔"));
	m_combo1.SetCurSel(0);

	m_combo2.AddString(TEXT("有填充"));
	m_combo2.AddString(TEXT("无填充"));
	m_combo2.SetCurSel(0);

	m_combo3.AddString(TEXT("实线"));
	m_combo3.AddString(TEXT("虚线"));
	m_combo3.SetCurSel(0);

	m_combo4.AddString(TEXT("1"));
	m_combo4.AddString(TEXT("2"));
	m_combo4.AddString(TEXT("3"));
	m_combo4.AddString(TEXT("4"));
	m_combo4.AddString(TEXT("5"));
	m_combo4.AddString(TEXT("6"));
	m_combo4.SetCurSel(0);

	m_combo5.AddString(TEXT("红色"));
	m_combo5.AddString(TEXT("橙色"));
	m_combo5.AddString(TEXT("黄色"));
	m_combo5.AddString(TEXT("绿色"));
	m_combo5.AddString(TEXT("青色"));
	m_combo5.AddString(TEXT("蓝色"));
	m_combo5.AddString(TEXT("紫色"));
	m_combo5.AddString(TEXT("黑色"));
	m_combo5.SetCurSel(0);

	m_combo6.AddString(TEXT("红色"));
	m_combo6.AddString(TEXT("橙色"));
	m_combo6.AddString(TEXT("黄色"));
	m_combo6.AddString(TEXT("绿色"));
	m_combo6.AddString(TEXT("青色"));
	m_combo6.AddString(TEXT("蓝色"));
	m_combo6.AddString(TEXT("紫色"));
	m_combo6.AddString(TEXT("黑色"));
	m_combo6.SetCurSel(0);
}


void Setting_Dlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	Shape_Type = m_combo1.GetCurSel() + 1;

	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(pMainWnd);
		if (pMainFrame != nullptr)
		{
			pMainFrame->m_wndStatusBar.SetPaneText(0, TEXT("切换绘图类型！"));//修改原有的状态栏上就绪一栏的信息 
		}
	}
}


void Setting_Dlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo2.GetCurSel();

	if (index == 0) isfill = true;
	else isfill = false;

	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(pMainWnd);
		if (pMainFrame != nullptr)
		{
			pMainFrame->m_wndStatusBar.SetPaneText(0, TEXT("切换填充类型！"));//修改原有的状态栏上就绪一栏的信息 
		}
	}
}


void Setting_Dlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo3.GetCurSel();

	if (index == 0) Line_Type = 0;
	else Line_Type = 1;

	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(pMainWnd);
		if (pMainFrame != nullptr)
		{
			pMainFrame->m_wndStatusBar.SetPaneText(0, TEXT("切换线型！"));//修改原有的状态栏上就绪一栏的信息 
		}
	}
}


void Setting_Dlg::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
	Line_Width = m_combo4.GetCurSel() + 1;

	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(pMainWnd);
		if (pMainFrame != nullptr)
		{
			pMainFrame->m_wndStatusBar.SetPaneText(0, TEXT("切换线宽！"));//修改原有的状态栏上就绪一栏的信息 
		}
	}
}


void Setting_Dlg::OnCbnSelchangeCombo5()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo5.GetCurSel();
	if (index == 0) Line_Color = RGB(255, 0, 0);
	else if (index == 1) Line_Color = RGB(255, 165, 0);
	else if (index == 2) Line_Color = RGB(255, 255, 0);
	else if (index == 3) Line_Color = RGB(0, 255, 0);
	else if (index == 4) Line_Color = RGB(0, 255, 255);
	else if (index == 5) Line_Color = RGB(0, 0, 255);
	else if (index == 6)  Line_Color = RGB(128, 0, 128);
	else Line_Color = RGB(0, 0, 0);

	//CString str;
	//str.Format(TEXT("%d"), index);
	//MessageBox(str);
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(pMainWnd);
		if (pMainFrame != nullptr)
		{
			pMainFrame->m_wndStatusBar.SetPaneText(0, TEXT("切换线条颜色！"));//修改原有的状态栏上就绪一栏的信息 
		}
	}
}


void Setting_Dlg::OnCbnSelchangeCombo6()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo6.GetCurSel();
	if (index == 0) Fill_Color = RGB(255, 0, 0);
	else if (index == 1) Fill_Color = RGB(255, 165, 0);
	else if (index == 2) Fill_Color = RGB(255, 255, 0);
	else if (index == 3) Fill_Color = RGB(0, 255, 0);
	else if (index == 4) Fill_Color = RGB(0, 255, 255);
	else if (index == 5) Fill_Color = RGB(0, 0, 255);
	else if (index == 6) Fill_Color = RGB(128, 0, 128);
	else Fill_Color = RGB(0, 0, 0);

	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(pMainWnd);
		if (pMainFrame != nullptr)
		{
			pMainFrame->m_wndStatusBar.SetPaneText(0, TEXT("切换填充颜色！"));//修改原有的状态栏上就绪一栏的信息 
		}
	}
}


void Setting_Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(pMainWnd);
		if (pMainFrame != nullptr)
		{
			CMFCPaintView* pView = static_cast<CMFCPaintView*>(pMainFrame->GetUpPane());
			if (pView != nullptr)
			{
				pView->ClearDrawing();
				pMainFrame->m_wndStatusBar.SetPaneText(0, TEXT("清空绘画区！"));//修改原有的状态栏上就绪一栏的信息 
			}
		}
	}
}

void Setting_Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(pMainWnd);
		if (pMainFrame != nullptr)
		{
			CMFCPaintView* pView = static_cast<CMFCPaintView*>(pMainFrame->GetUpPane());
			if (pView != nullptr)
			{
				pMainFrame->m_wndStatusBar.SetPaneText(0, TEXT("加载图片！"));//修改原有的状态栏上就绪一栏的信息 
				pView->LoadMyImage();
			}
		}
	}
}

void Setting_Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(pMainWnd);
		if (pMainFrame != nullptr)
		{
			CMFCPaintView* pView = static_cast<CMFCPaintView*>(pMainFrame->GetUpPane());
			if (pView != nullptr)
			{
				pMainFrame->m_wndStatusBar.SetPaneText(0, TEXT("保存"));//修改原有的状态栏上就绪一栏的信息 
				pView->SavePainting();
			}
		}
	}
}


void Setting_Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void Setting_Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_text == TEXT(""))
	{
		MessageBox(TEXT("文字不能为空！"), TEXT("提示"));
		return;
	}
	Text = m_text;

	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(pMainWnd);
		if (pMainFrame != nullptr)
		{
			CMFCPaintView* pView = static_cast<CMFCPaintView*>(pMainFrame->GetUpPane());
			if (pView != nullptr)
			{
				pMainFrame->m_wndStatusBar.SetPaneText(0, TEXT("添加文字！"));//修改原有的状态栏上就绪一栏的信息 
				pView->isWriting = true;
				MessageBox(TEXT("单击绘图区域即可添加文字"), TEXT("提示"));
			}
		}
	}
}
