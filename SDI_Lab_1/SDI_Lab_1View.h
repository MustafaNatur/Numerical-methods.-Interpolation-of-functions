
// SDI_Lab_1View.h: интерфейс класса CSDILab1View
//

#pragma once

#include "SDI_Lab_1Doc.h"

struct MyPenParam {
	int r;
	int g;
	int b;
	int thikness;
};
class CSDILab1View : public CView
{
protected: // создать только из сериализации
	CSDILab1View() noexcept;
	DECLARE_DYNCREATE(CSDILab1View)

// Атрибуты
public:
	CSDILab1Doc* GetDocument() const;

// Операции
public:
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	int deltaX = 0;
	int deltaY = 0;
	double k = 1.0;
	CPoint point1;
	void CSDILab1View::DrawCords(CDC* pDC, int w, int h);
	void CSDILab1View::DrawPoints(CDC* pDC, std::vector <MyPoint>Arr, int w, int h, MyPenParam color);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CSDILab1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // версия отладки в SDI_Lab_1View.cpp
inline CSDILab1Doc* CSDILab1View::GetDocument() const
   { return reinterpret_cast<CSDILab1Doc*>(m_pDocument); }
#endif



