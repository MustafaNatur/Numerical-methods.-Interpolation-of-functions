
// SDI_Lab_1Doc.cpp: реализация класса CSDILab1Doc 
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
#include <propkey.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSDILab1Doc

IMPLEMENT_DYNCREATE(CSDILab1Doc, CDocument)

BEGIN_MESSAGE_MAP(CSDILab1Doc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CSDILab1Doc

CSDILab1Doc::CSDILab1Doc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CSDILab1Doc::~CSDILab1Doc()
{
}

BOOL CSDILab1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	type1 = false;
	type2 = false;
	type3 = false;
	m_pTreeView->FillTree();
	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CSDILab1Doc

void CSDILab1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		
		PointsData.clear();
		PointsDraw.clear();
		// TODO: добавьте код загрузки
		std::ifstream file(ar.m_strFileName);

		while (!file.eof())
		{
			float x = 0;
			float y = 0;
			char buf[100];
			file.getline(buf, 100);
			sscanf_s(buf, "%f %f", &x, &y);
			PointsData.push_back(MyPoint{ x,y });
		}
		length = PointsData.size();
		ok = true;
	}
}


void CSDILab1Doc::calculate() {
	PointsDraw.clear();
	if (ok) {
		if (type1) {
			for (int j = 0; j < length - 1; j++)
			{
				for (double currentX = PointsData[j].x + step; currentX < PointsData[j + 1].x; currentX += step) {
					double y = linearInterpolation(PointsData[j].x, PointsData[j].y, PointsData[j + 1].x, PointsData[j + 1].y, currentX);
					PointsDraw.push_back(MyPoint{ currentX,y });
				}
			}
		}
		if (type2) {
			double max = PointsData[length - 1].x;
			double min = PointsData[0].x;
			for (double currentX = min; currentX < max; currentX += step) {
				double y = Polinom(currentX);
				PointsDraw.push_back(MyPoint{ currentX,y });
			}
		}

		if (type3) {

			gsl_interp_accel* acc = gsl_interp_accel_alloc();
			gsl_spline* spline = gsl_spline_alloc(gsl_interp_cspline, length);
			std::vector <double>xArr;
			std::vector <double>yArr;
			for (int i = 0; i < length; i++) {
				xArr.push_back(PointsData[i].x);
				yArr.push_back(PointsData[i].y);
			}
			gsl_spline_init(spline, xArr.data(), yArr.data(), length);
			for (double xi = xArr[0]; xi < xArr[length - 1]; xi += step)
			{
				double yi = gsl_spline_eval(spline, xi, acc);
				PointsDraw.push_back(MyPoint{ xi,yi });
			}
			gsl_spline_free(spline);
			gsl_interp_accel_free(acc);
		}
		m_pView->Invalidate();
	}

}

double linearInterpolation(double x1, double y1, double x2, double y2, double currentX) {
	return (y1 - y2) * (currentX - x1) / (x1 - x2) + y1;
}

double CSDILab1Doc::basePolinom(double currentX, int indexWithOut) {
	double a = 1.0;
	double b = 1.0;
	for (int j = 0; j < length; j++) {
		if (j == indexWithOut) { continue; }
		a *= (currentX - PointsData[j].x);
		b *= (PointsData[indexWithOut].x - PointsData[j].x);
	}
	double res = a / b;
	return res;
}

double CSDILab1Doc::Polinom(double currnetX) {
	double y = 0;
	for (int i = 0; i < length; i++) {
		y += PointsData[i].y * basePolinom(currnetX, i);
	}
	return y;
}
#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSDILab1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFontGetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CSDILab1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CSDILab1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunkSetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CSDILab1Doc

#ifdef _DEBUG
void CSDILab1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDILab1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CSDILab1Doc
