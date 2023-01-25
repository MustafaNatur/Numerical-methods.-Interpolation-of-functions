// MyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "SDI_Lab_1.h"
#include "CMyTreeView.h"

#include "SDI_Lab_1Doc.h"
// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_hInterpolationMethodsRoot = tree.InsertItem(L"Методы интерполяции", -1, -1, NULL, TVI_FIRST);

	m_hLinear = tree.InsertItem(L"Кусочно-линейная", -1, -1, m_hInterpolationMethodsRoot, TVI_FIRST);
	m_hLagrange = tree.InsertItem(L"Многочлен Лагранжа", -1, -1, m_hInterpolationMethodsRoot, TVI_FIRST);
	m_hSpline = tree.InsertItem(L"Кубическими сплайнами", -1, -1, m_hInterpolationMethodsRoot, TVI_FIRST);

	tree.Expand(m_hInterpolationMethodsRoot, TVE_EXPAND);
}

// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_CHECKBOXES;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}


void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CTreeCtrl& tree = GetTreeCtrl();
	CTreeView::OnLButtonDown(nFlags, point);

	CRect rc;
	tree.GetItemRect(m_hInterpolationMethodsRoot, &rc, false);

	m_pDoc->type1 = tree.GetCheck(m_hLinear);
	m_pDoc->type2 = tree.GetCheck(m_hLagrange);
	m_pDoc->type3 = tree.GetCheck(m_hSpline);
	m_pDoc->calculate();
}
