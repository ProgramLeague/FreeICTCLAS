//////////////////////////////////////////////////////////////////////
//ICTCLAS简介：计算所汉语词法分析系统ICTCLAS(Institute of Computing Technology, Chinese Lexical Analysis System)，
//             功能有：中文分词；词性标注；未登录词识别。
//             分词正确率高达97.58%(973专家评测结果)，
//             未登录词识别召回率均高于90%，其中中国人名的识别召回率接近98%;
//             处理速度为31.5Kbytes/s。
//著作权：  Copyright?2002-2005中科院计算所 职务著作权人：张华平 刘群
//遵循协议：自然语言处理开放资源许可证1.0
//Email: zhanghp@software.ict.ac.cn
//Homepage:www.nlp.org.cn;mtgroup.ict.ac.cn
// ICTCLAS_Win.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ICTCLAS_Win.h"
#include "ICTCLAS_WinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CICTCLAS_WinApp

BEGIN_MESSAGE_MAP(CICTCLAS_WinApp, CWinApp)
	//{{AFX_MSG_MAP(CICTCLAS_WinApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CICTCLAS_WinApp construction

CICTCLAS_WinApp::CICTCLAS_WinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CICTCLAS_WinApp object

CICTCLAS_WinApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CICTCLAS_WinApp initialization

BOOL CICTCLAS_WinApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CICTCLAS_WinDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
