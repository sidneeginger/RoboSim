// RoboSimer.h : RoboSimer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CRoboSimerApp:
// �йش����ʵ�֣������ RoboSimer.cpp
//

class CRoboSimerApp : public CWinApp
{
public:
	CRoboSimerApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRoboSimerApp theApp;
