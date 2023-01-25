
// SDI_Lab_1Doc.h: интерфейс класса CSDILab1Doc 
//

#include <vector>
#pragma once

#include "CMyTreeView.h"
class CMyTreeView;
class CSDILab1View;
# define M_PI           3.14159265358979323846
struct MyPoint {
	double x;
	double y;
};
class CSDILab1Doc : public CDocument
{
protected: // создать только из сериализации
	CSDILab1Doc() noexcept;
	DECLARE_DYNCREATE(CSDILab1Doc)

// Атрибуты
public:
	bool type1, type2, type3 = false;
	CSDILab1View* m_pView;
	CMyTreeView* m_pTreeView;
// Операции
public:
	//std::vector <double> xArr = {0};
	//std::vector <double> yArr = {0};
	//std::vector <double> xDraw = {0};
	//std::vector <double> yDraw = {0};
	std::vector <MyPoint> PointsDraw = { {0,0} };
	std::vector <MyPoint> PointsData = { {0,0} };
	int length = PointsData.size();
	
	bool ok = false;
	double step = 0.01;
	void calculate();
	double basePolinom(double currentX, int indexWithOut);
	double Polinom(double currnetX);
	
// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSDILab1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};



double linearInterpolation(double x1, double y1, double x2, double y2, double currentX);
