
// GraphicEditTool.h : GraphicEditTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CGraphicEditToolApp:
// �� Ŭ������ ������ ���ؼ��� GraphicEditTool.cpp�� �����Ͻʽÿ�.
//

class CGraphicEditToolApp : public CWinApp
{
public:
	CGraphicEditToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphicEditToolApp theApp;
