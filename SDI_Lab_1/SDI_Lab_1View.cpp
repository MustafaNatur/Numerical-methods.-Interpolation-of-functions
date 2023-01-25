
// SDI_Lab_1View.cpp: реализация класса CSDILab1View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDI_Lab_1.h"
#endif

#include "SDI_Lab_1Doc.h"
#include "SDI_Lab_1View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
// CSDILab1View

IMPLEMENT_DYNCREATE(CSDILab1View, CView)

BEGIN_MESSAGE_MAP(CSDILab1View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSDILab1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// Создание или уничтожение CSDILab1View

CSDILab1View::CSDILab1View() noexcept
{
	// TODO: добавьте код создания

}

CSDILab1View::~CSDILab1View()
{
}

BOOL CSDILab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CSDILab1View

void CSDILab1View::OnDraw(CDC* pDC)
{
	CSDILab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(&rect);
	DrawCords(pDC, rect.Width(), rect.Height());

	if (pDoc->ok) {

		DrawPoints(pDC, pDoc->PointsData, rect.Width(), rect.Height(), MyPenParam{255, 0, 0, 5});
		DrawPoints(pDC, pDoc->PointsDraw, rect.Width(), rect.Height(), MyPenParam{ 0, 255, 0, 1 });
	}
}


void CSDILab1View::DrawCords(CDC* pDC, int w, int h) {
	pDC->MoveTo(0 + deltaX, 0);
	pDC->LineTo(0 + deltaX, h);

	pDC->MoveTo(0, h / 2 + deltaY);
	pDC->LineTo(w, h / 2 + deltaY);
	pDC->MoveTo(0, h / 2 + deltaY);
}

void CSDILab1View::DrawPoints(CDC* pDC, std::vector <MyPoint>Arr, int w, int h, MyPenParam color) {
	CPen pen1(PS_SOLID, 10, RGB(color.r, color.g, color.b));
	CPen* OldPen = pDC->SelectObject(&pen1);
	for (int i = 0; i < Arr.size(); i++) {
		int X = Arr[i].x * (w / (M_PI * 2)) * k + deltaX;
		int Y = Arr[i].y * (h / 2) * k + h / 2 + deltaY;
		pDC->MoveTo(X, Y);
		pDC->AngleArc(X, Y, color.thikness, 0, 360);
	}
}


// Печать CSDILab1View


void CSDILab1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSDILab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CSDILab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CSDILab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CSDILab1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSDILab1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CSDILab1View

#ifdef _DEBUG
void CSDILab1View::AssertValid() const
{
	CView::AssertValid();
}

void CSDILab1View::Dump(CDumpContext& dc) const
{
	
	CView::Dump(dc);
}

CSDILab1Doc* CSDILab1View::GetDocument() const // встроена неотлаженная версия
{
	
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDILab1Doc)));
	return (CSDILab1Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSDILab1View


void CSDILab1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CSDILab1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CSDILab1View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CSDILab1Doc* pDoc = GetDocument();
	pDoc->m_pView = this;
	//SetTimer(0, 500, NULL);
	// TODO: добавьте специализированный код или вызов базового класса
}


BOOL CSDILab1View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CSDILab1Doc* pDoc = GetDocument();
	if (k > 0) {
		k -= zDelta / 1000.0;
	}
	else {
		k += zDelta / 1000.0;
	}
	
	Invalidate();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CSDILab1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (nFlags&VK_LBUTTON) {
		deltaX -= (point1.x - point.x);
		deltaY -= (point1.y - point.y);
		Invalidate();
	}
	point1 = point;
	
	CView::OnMouseMove(nFlags, point);
}
