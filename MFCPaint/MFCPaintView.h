
// MFCPaintView.h: CMFCPaintView 类的接口
//

#pragma once

#include "MFCPaintDoc.h"

class CMFCPaintView : public CView
{
protected: // 仅从序列化创建
	CMFCPaintView() noexcept;
	DECLARE_DYNCREATE(CMFCPaintView)

// 特性
public:
	CMFCPaintDoc* GetDocument() const;

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
	virtual ~CMFCPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	CPoint P_Start, P_End;
	bool isPainting;
	bool isLoading;
	bool isWriting;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void ClearDrawing();
	void LoadMyImage();
	void SavePainting();
	CString saveFilePath;
};

#ifndef _DEBUG  // MFCPaintView.cpp 中的调试版本
inline CMFCPaintDoc* CMFCPaintView::GetDocument(A) const
   { return reinterpret_cast<CMFCPaintDoc*>(m_pDocument); }
#endif

