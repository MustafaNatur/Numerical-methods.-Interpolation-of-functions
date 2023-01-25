
// SDI_Lab_1.h: основной файл заголовка для приложения SDI_Lab_1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CSDILab1App:
// Сведения о реализации этого класса: SDI_Lab_1.cpp
//

class CSDILab1App : public CWinAppEx
{
public:
	CSDILab1App() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSDILab1App theApp;
