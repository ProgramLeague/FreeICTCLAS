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
// ICTCLAS_WinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICTCLAS_Win.h"
#include "ICTCLAS_WinDlg.h"
#include "Utility\\Utility.h"
#include <time.h>//Calculate the time
#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CICTCLAS_WinDlg dialog

CICTCLAS_WinDlg::CICTCLAS_WinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CICTCLAS_WinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CICTCLAS_WinDlg)
	m_sResult = _T("");
	m_sSource = _T("");
	m_nTime = 0;
	m_nOutputFormat = -1;
	m_nOperateType = -1;
	m_nResultNum = 0;
	m_sScore = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CICTCLAS_WinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CICTCLAS_WinDlg)
	DDX_Text(pDX, IDC_EDT_RESULT, m_sResult);
	DDX_Text(pDX, IDC_EDT_SOURCE, m_sSource);
	DDV_MaxChars(pDX, m_sSource, 2048);
	DDX_Text(pDX, IDC_EDT_TIME, m_nTime);
	DDX_Radio(pDX, IDC_RADIO_PKU, m_nOutputFormat);
	DDX_Radio(pDX, IDC_RADIO_SEG, m_nOperateType);
	DDX_Text(pDX, IDC_EDT_RESULTNUM, m_nResultNum);
	DDV_MinMaxUInt(pDX, m_nResultNum, 1, 10);
	DDX_Text(pDX, IDC_EDT_SCORE, m_sScore);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CICTCLAS_WinDlg, CDialog)
	//{{AFX_MSG_MAP(CICTCLAS_WinDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	ON_BN_CLICKED(IDC_BTN_RUN, OnBtnRun)
	ON_BN_CLICKED(IDC_BTN_FILEOPEN, OnBtnFileopen)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CICTCLAS_WinDlg message handlers

BOOL CICTCLAS_WinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_nOperateType=2;
	m_nOutputFormat=0;
	m_nTime=0;
	m_nResultNum=1;
	m_sScore.Format("None");
	m_bDisable=true;
	if(!IsDataExists())
	{
		m_sResult="错误：Data文件夹不存在或者缺少数据文件！";
	}
    UpdateData(FALSE);
	m_fileLog.Open("log.txt",CFile::modeWrite|CFile::typeText|CFile::modeCreate|CFile::modeNoTruncate|CFile::shareDenyWrite);//Open log file to write
	m_fileLog.SeekToEnd();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CICTCLAS_WinDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CICTCLAS_WinDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CICTCLAS_WinDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CICTCLAS_WinDlg::OnBtnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
	//IDOK
}

void CICTCLAS_WinDlg::OnBtnRun() 
{
	// TODO: Add your control notification handler code here
	if(m_bDisable)
		return;
	char *sResult,*sSource;
	UpdateData();
	if(m_sSource.IsEmpty())
	{//Empty sentence and return.
		return ;
	}
	m_ICTCLAS.m_nOutputFormat=m_nOutputFormat;
	m_ICTCLAS.m_nOperateType=m_nOperateType;
	clock_t start, finish;
	if(m_nOutputFormat!=2)
		sResult=new char [(strlen((char *)(LPCTSTR)m_sSource)+13)*3];
	else
		sResult=new char [(strlen((char *)(LPCTSTR)m_sSource)+13)*50];
	if(m_nResultNum==1)
	{
			start=clock();
			if(!m_ICTCLAS.ParagraphProcessing((char *)(LPCTSTR)m_sSource,sResult))
				m_sResult.Format("错误：程序初始化异常！");
			else
				m_sResult.Format("%s",sResult);
			finish=clock();
			m_nTime=1000*(finish-start)/CLOCKS_PER_SEC;
			m_sScore.Format("%f",m_ICTCLAS.m_dResultPossibility[0]);
			UpdateData(FALSE);
			//write  log file
	}
	else
	{
		if(m_sSource.GetLength()>1024)
		{
			m_sResult.Format("多个结果处理的文本不能超过1K!");
			UpdateData(FALSE);
			return;
		}
		else if(m_nResultNum>10)
		{
			m_sResult.Format("结果数不能超过10!");
			UpdateData(FALSE);
			return;
		}
		start=clock();
		sSource=new char[strlen((char *)(LPCTSTR)m_sSource)+20];
		strcpy(sSource,SENTENCE_BEGIN);
		strcat(sSource,(char *)(LPCTSTR)m_sSource);
		strcat(sSource,SENTENCE_END);
		if(!m_ICTCLAS.Processing(sSource,m_nResultNum))
			m_sResult.Format("错误：程序初始化异常！");
		else
		{
			finish=clock();
			m_nTime=1000*(finish-start)/CLOCKS_PER_SEC;
			m_sResult.Empty();
			CString sTemp;
			for(int i=0;i<m_ICTCLAS.m_nResultCount;i++)
			{
				sTemp.Format("Result %d(Score=%f):",i+1,m_ICTCLAS.m_dResultPossibility[i]);
				m_sResult+=sTemp;
				m_ICTCLAS.Output(m_ICTCLAS.m_pResult[i],sResult,true);
				m_sResult+=sResult;
				m_sResult+="\r\n";
			}
		}
		delete [] sSource;
		UpdateData(FALSE);
	}
	delete [] sResult;
	m_fileLog.WriteString((LPCTSTR)m_sSource);//Record the source sentence in the log file
	m_fileLog.WriteString("\r\n");	
	m_fileLog.WriteString((LPCTSTR)m_sResult);//Record the result in the log file
	m_fileLog.WriteString("\r\n");	

}

void CICTCLAS_WinDlg::OnBtnFileopen() 
{
	// TODO: Add your control notification handler code here
	if(m_bDisable)
		return;
	CFileDialog dlg(true,(LPCTSTR)("txt"),(LPCTSTR)("test"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text File (*.txt)|*.txt");
	char sSourceFile[100],sResultFile[100];
	if(dlg.DoModal()==IDOK)
	{
		UpdateData();
		m_ICTCLAS.m_nOutputFormat=m_nOutputFormat;
		m_ICTCLAS.m_nOperateType=m_nOperateType;
		clock_t start, finish;
		strcpy(sSourceFile,(LPCTSTR)dlg.GetPathName());//Get file name and path
		strcpy(sResultFile,sSourceFile);//Set the result file name and path
		unsigned int nLen=strlen(sSourceFile);
		strncpy(sResultFile+nLen-4,"_cla.txt",10);//Change the extension
        sResultFile[nLen+4]=0;
		start=clock();
		if(!m_ICTCLAS.FileProcessing(sSourceFile,sResultFile))
			m_sResult.Format("错误：程序初始化异常！");
		else
		{
			finish=clock();
			m_nTime=1000*(finish-start)/CLOCKS_PER_SEC;
			m_sResult.Format("处理结果已经存在文件%s中!",sResultFile);
		}
		UpdateData(FALSE);
	}
}

//DEL void CICTCLAS_WinDlg::OnBtnFilesave() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	CFileDialog dlg(false,(LPCTSTR)("cla"),(LPCTSTR)("temp"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "CLA File (*.cla)|*.cla");
//DEL 	if(dlg.DoModal()==IDOK)
//DEL 	{
//DEL 		CStdioFile file((LPCTSTR)dlg.GetPathName(),CFile::modeWrite|CFile::typeText|CFile::modeCreate|CFile::modeNoTruncate);
//DEL 		file.SeekToEnd();
//DEL 		file.WriteString("\r\n");	
//DEL 		file.WriteString((LPCTSTR)m_sResult);
//DEL 	}
//DEL }

void CICTCLAS_WinDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_fileLog.Close();
	CDialog::OnClose();
}

void CICTCLAS_WinDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}


BOOL CICTCLAS_WinDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	//cs.
	return CDialog::PreCreateWindow(cs);
}

bool CICTCLAS_WinDlg::IsDataExists()
{
	char sDataFiles[][40]={"data\\BigramDict.dct",
		                   "data\\coreDict.dct",
						   "data\\lexical.ctx",
		                   "data\\nr.dct",
						   "data\\nr.ctx",
		                   "data\\ns.dct",
						   "data\\ns.ctx",
		                   "data\\tr.dct",
						   "data\\tr.ctx",
						   ""

	};
	int i=0;
	while(sDataFiles[i][0]!=0)
	{
		if((_access( sDataFiles[i], 0 ))==-1)
			return false;
		i++;
	}
	m_bDisable=false;
	return true;
}
