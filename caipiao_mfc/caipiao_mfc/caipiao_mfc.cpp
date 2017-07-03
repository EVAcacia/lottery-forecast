
// caipiao_mfc.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "caipiao_mfc.h"
#include "caipiao_mfcDlg.h"
#include <stdio.h>  
#include <iostream>  
#include <Windows.h>    
#include "curl.h"    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#pragma comment(lib, "libcurl.lib")     
#pragma comment(lib, "wldap32.lib")     
#pragma comment(lib, "ws2_32.lib")     
#pragma comment(lib, "winmm.lib")     

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcaipiaoApp

BEGIN_MESSAGE_MAP(CcaipiaoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CcaipiaoApp ����

CcaipiaoApp::CcaipiaoApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CcaipiaoApp ����

CcaipiaoApp theApp;


size_t write_data(char *buffer,size_t size, size_t nitems,void *outstream)  
{  
	int written = fwrite(buffer, size, nitems, (FILE*)outstream);  
	return written;  
}  

// CcaipiaoApp ��ʼ��

BOOL CcaipiaoApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//ſ�������ϵ����ݡ�
	// ��note.xmlд��myxml.xml�ļ���  
	CURL *pCurl;    
	FILE* pFile = fopen( "..\\Debug\\myxml.xml", "wb" );  
	pCurl = curl_easy_init();    
	curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, (void*)pFile);  
	curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, write_data);  
	curl_easy_setopt(pCurl, CURLOPT_URL, "http://www.pc28yc.com/pre.php/");  
	curl_easy_perform(pCurl);  
	fclose(pFile);  
	curl_easy_cleanup( pCurl );  

	//��ҳ�Ѿ���down�����ˡ�
	////��ʼ������ߵ�����
	/*if( system( "xcyk.exe") == -1 )
	{
		perror( "execl error " );
		MessageBox(NULL,_T("xcyk.exe Error"),_T("ERROR"),MB_ERR_INVALID_CHARS);
		exit(1);
	}*/
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = _T("xcyk.exe");
	ShExecInfo.lpParameters = _T("");
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	Ccaipiao_mfcDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

