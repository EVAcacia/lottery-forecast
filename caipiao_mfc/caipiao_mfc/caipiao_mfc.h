
// caipiao_mfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CcaipiaoApp:
// �йش����ʵ�֣������ caipiao_mfc.cpp
//

class CcaipiaoApp : public CWinApp
{
public:
	CcaipiaoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CcaipiaoApp theApp;