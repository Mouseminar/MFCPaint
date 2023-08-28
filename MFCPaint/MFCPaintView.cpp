
// MFCPaintView.cpp: CMFCPaintView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCPaint.h"
#endif

#include "MFCPaintDoc.h"
#include "MFCPaintView.h"
#include "CMy_Global.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCPaintView

IMPLEMENT_DYNCREATE(CMFCPaintView, CView)

BEGIN_MESSAGE_MAP(CMFCPaintView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFCPaintView 构造/析构

CMFCPaintView::CMFCPaintView() noexcept
{
	// TODO: 在此处添加构造代码
	isPainting = false;
	isLoading = false;
	isWriting = false;
}

CMFCPaintView::~CMFCPaintView()
{
}

BOOL CMFCPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCPaintView 绘图

void CMFCPaintView::OnDraw(CDC* /*pDC*/)
{
	CMFCPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCPaintView 打印

BOOL CMFCPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCPaintView 诊断

#ifdef _DEBUG
void CMFCPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCPaintDoc* CMFCPaintView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCPaintDoc)));
	return (CMFCPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCPaintView 消息处理程序


void CMFCPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	P_Start = point;
	isPainting = true;

	CView::OnLButtonDown(nFlags, point);
}


void CMFCPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isWriting)
	{
		CDC* pdc = GetDC();
		CFont new_font;
		//创建字体宋体格式  100为字高
		VERIFY(new_font.CreatePointFont(250, _T("宋体"), pdc));
		//选择该字体进入PDC
		CFont* default_font = pdc->SelectObject(&new_font);
		//设置字体颜色
		pdc->SetTextColor(Line_Color);

		pdc->TextOut(point.x, point.y, Text);
		isWriting = false;
		isPainting = false;
		return;
	}

	if (isLoading)
	{
		isLoading = false;
		return;
	}

	if (Shape_Type == 6)
	{
		isPainting = false;
		return;
	}

	P_End = point;

	CPen* pNewPen;
	CPen* pOldPen;

	CBrush* pNewBrush1;
	CBrush* pOldBrush1;

	CDC* pdc = GetDC();

	if (Shape_Type == 4)
	{
		pNewPen = new CPen;
		pNewPen->CreatePen(Line_Type, Line_Width, Line_Color);
		pOldPen = pdc->SelectObject(pNewPen); //选择新笔，并保存旧笔 
		//画矩形 
		pdc->Ellipse(P_Start.x, P_Start.y, P_End.x, P_End.y);
		//恢复原有的笔 
		pdc->SelectObject(pOldPen);
		delete pNewPen;

		if (isfill)
		{
			pNewBrush1 = new CBrush;
			pNewBrush1->CreateSolidBrush(Fill_Color);
			//选择新画刷 
			pOldBrush1 = pdc->SelectObject(pNewBrush1);
			//绘制圆 
			pdc->Ellipse(P_Start.x, P_Start.y, P_End.x, P_End.y);
			//恢复原有画刷 
			pdc->SelectObject(pOldBrush1);
			delete pNewBrush1;
		}
	}
	else if (Shape_Type == 2)
	{
		pNewPen = new CPen;
		pNewPen->CreatePen(Line_Type, Line_Width, Line_Color);
		pOldPen = pdc->SelectObject(pNewPen); //选择新笔，并保存旧笔 
		//画矩形 
		pdc->Rectangle(P_Start.x, P_Start.y, P_End.x, P_End.y);
		//恢复原有的笔 
		pdc->SelectObject(pOldPen);
		delete pNewPen;

		if (isfill)
		{
			pNewBrush1 = new CBrush;
			pNewBrush1->CreateSolidBrush(Fill_Color);
			//选择新画刷 
			pOldBrush1 = pdc->SelectObject(pNewBrush1);
			//绘制矩形 
			pdc->Rectangle(P_Start.x, P_Start.y, P_End.x, P_End.y);
			//恢复原有画刷 
			pdc->SelectObject(pOldBrush1);
			delete pNewBrush1;
		}
	}
	else if (Shape_Type == 1)
	{
		pNewPen = new CPen;
		pNewPen->CreatePen(Line_Type, Line_Width, Line_Color);
		pOldPen = pdc->SelectObject(pNewPen); //选择新笔，并保存旧笔 
		//画直线 
		pdc->MoveTo(P_Start.x, P_Start.y);
		pdc->LineTo(P_End.x, P_End.y);
		//恢复原有的笔 
		pdc->SelectObject(pOldPen);
		delete pNewPen;
	}
	else if (Shape_Type == 3)
	{
		pNewPen = new CPen;
		pNewPen->CreatePen(Line_Type, Line_Width, Line_Color);
		pOldPen = pdc->SelectObject(pNewPen); //选择新笔，并保存旧笔 
		//画矩形 
		int d = P_End.x - P_Start.x;
		pdc->Ellipse(P_Start.x, P_Start.y, P_Start.x + d, P_Start.y + d);
		//恢复原有的笔 
		pdc->SelectObject(pOldPen);
		delete pNewPen;

		if (isfill)
		{
			pNewBrush1 = new CBrush;
			pNewBrush1->CreateSolidBrush(Fill_Color);
			//选择新画刷 
			pOldBrush1 = pdc->SelectObject(pNewBrush1);
			//绘制圆 
			pdc->Ellipse(P_Start.x, P_Start.y, P_Start.x + d, P_Start.y + d);
			//恢复原有画刷 
			pdc->SelectObject(pOldBrush1);
			delete pNewBrush1;
		}
	}
	else if (Shape_Type == 5)
	{
		pNewPen = new CPen;
		pNewPen->CreatePen(Line_Type, Line_Width, Line_Color);
		pOldPen = pdc->SelectObject(pNewPen); //选择新笔，并保存旧笔 
		// 定义一个矩形，用于确定弧线的边界
		CRect rect(P_Start.x, P_Start.y, P_End.x, P_End.y);
		// 绘制一条从point1到point2的弧线
		pdc->Arc(rect, P_Start, P_End);
		//恢复原有的笔 
		pdc->SelectObject(pOldPen);
		delete pNewPen;
	}

	isPainting = false;

	CView::OnLButtonUp(nFlags, point);
}


void CMFCPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (Shape_Type == 6 && isPainting)
	{
		CPen* pNewPen;

		CDC* pdc = GetDC();
		pNewPen = new CPen;
		pNewPen->CreatePen(0, Line_Width, Line_Color);
		pdc->SelectObject(pNewPen); //选择新笔，并保存旧笔 
		pdc->MoveTo(P_Start);
		pdc->LineTo(point);
		P_Start = point;
		delete pNewPen;
	}

	CView::OnMouseMove(nFlags, point);
}

void CMFCPaintView::ClearDrawing()
{
	// 示例代码：将绘图缓冲区清空为白色背景
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}

void CMFCPaintView::LoadMyImage()
{
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, _T("image Files(*.bmp; *.jpeg;*.jpg;*.png)|*.JPG;*.PNG;*.BMP|All Files (*.*) |*.*|"), this);
	fileDlg.DoModal();
	CString StrFilePath = fileDlg.GetPathName();
	if (StrFilePath == _T(""))
	{
		return;
	}
	CDC* pdc = GetDC();
	CRect rect;
	GetClientRect(&rect);
	CImage image;
	image.Load(StrFilePath);
	image.BitBlt(*pdc, 40, 40, rect.Width(), rect.Height(), 0, 0);
	image.Destroy();    //没有Destroy()会有内存泄漏。Detach();不行的。
	isLoading = true;
}

void CMFCPaintView::SavePainting()
{
	CClientDC dc(this);
	CRect rect;
	//BOOL  showMsgTag;                  //是否要弹出”图像保存成功对话框" 
	GetClientRect(&rect);                  //获取画布大小
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);

	//创建兼容位图
	HDC hdc = CreateCompatibleDC(dc);      //创建兼容DC，以便将图像保存为不同的格式
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);
	//将位图选入DC，并保存返回值 
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);
	//将屏幕DC的图像复制到内存DC中

	CImage image;
	image.Attach(hbitmap);                //将位图转化为一般图像

	CString  strFilter = _T("位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|GIF图像文件 | *.gif | PNG图像文件 | *.png |其他格式(*.*) | *.* || ");
	CFileDialog dlg(FALSE, _T("bmp"), _T("iPaint1.bmp"), NULL, strFilter);
	if (dlg.DoModal() != IDOK) return;

	CString strFileName;          //如果用户没有指定文件扩展名，则为其添加一个
	CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;

	if (dlg.m_ofn.nFileExtension == 0)               //扩展名项目为0
	{

		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			strExtension = "bmp"; break;
		case 2:
			strExtension = "jpg"; break;
		case 3:
			strExtension = "gif"; break;
		case 4:
			strExtension = "png"; break;
		default:
			break;
		}
		strFileName = strFileName + "." + strExtension;
	}

	saveFilePath = strFileName;     //saveFilePath为视类中的全局变量,类型为CString

	HRESULT hResult = image.Save(saveFilePath);     //保存图像
	if (FAILED(hResult))
	{
		MessageBox(_T("保存图像文件失败！"));
	}
	else
	{
		MessageBox(_T("文件保存成功！"));
	}
	image.Detach();
	SelectObject(hdc, hOldMap);
}
