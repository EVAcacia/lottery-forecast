
// caipiao_mfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "caipiao_mfc.h"
#include "caipiao_mfcDlg.h"
#include "windows.h"
#include "afxdialogex.h"
#include <iostream>
#include "locale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ccaipiao_mfcDlg �Ի���




Ccaipiao_mfcDlg::Ccaipiao_mfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ccaipiao_mfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ccaipiao_mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_programLangList);
}

BEGIN_MESSAGE_MAP(Ccaipiao_mfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// Ccaipiao_mfcDlg ��Ϣ�������

BOOL Ccaipiao_mfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	Sleep(1000);
	CString str;
	//FILE* pFile = fopen("xc.txt", "r");
	CStdioFile myFile, File;

	//char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//unicode ��������
	//setlocale(LC_CTYPE, "chs");// �趨

	if (myFile.Open(_T("xc.txt"), CFile::modeRead))
	{
		//��ȡ
		myFile.ReadString(str);
		myFile.Close();
	}
	else
	{
		MessageBox(_T("Open txt Error"), _T("ERROR"), MB_OK);
	}
	//setlocale(LC_CTYPE, old_locale);
	//free(old_locale);// ��ԭ

	//�б�����
	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_programLangList.GetClientRect(&rect);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_programLangList.SetExtendedStyle(m_programLangList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������   
	m_programLangList.InsertColumn(0, _T("�ں�"), LVCFMT_CENTER, rect.Width() / 3, 0);//Column����
	m_programLangList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 3, 1);
	m_programLangList.InsertColumn(2, _T("Ԥ��"), LVCFMT_CENTER, rect.Width() / 3, 2);
	m_programLangList.InsertColumn(3, _T("���"), LVCFMT_CENTER, rect.Width() / 3, 3);

	TCHAR *p = str.GetBuffer();
	str.ReleaseBuffer();
	//----------�½ṹ------
	typedef struct data
	{
		int one;
		int tow;
		int three;
		int add;
	}data_3;
	typedef struct lottery_profile
	{
		CString			number;
		data_3			result;
		int				forecast[2]; //Ԥ������ ��ʾ��˫�ʹ�С��
		bool			iftrue;      //Ԥ���Ƿ���ȷ��
		lottery_profile * next;
	}profile_versin;
	//----------------------

	profile_versin *view_list = new profile_versin;//ͷ��㡣 
	int i = 0; //������ʾ
	int numberNum = 0; //���ֵĸ����� 
	char numberBuffer[6] = {0};  //��������ָ���߹������֡�
	memset(numberBuffer, -1, 6);
	int j = 0;  //numberBuffer��������
	int plus_num = 0;

	while (p != NULL)
	{
		if ((*p < 48) || (*p > 57) || (*p != ' ') || (*p != '+') || (*p != '='))  //�ж���ָ������ݲ������ֵĻ�����ʼ������������
		{
			memset(numberBuffer, -1, 6);
			p++;
			numberNum = 0;
			j = 0;
			continue;
		}

		if (numberNum >= 6)
		{
			view_list->number = numberBuffer;
			numberNum = 0;
			p++;
			j = 0;
			continue;
		}

		if (*p == '+')
		{
			plus_num++;
			if (plus_num == 2)
			{

			}
		}
		if ((*p >= 48) && (*p <= 57))
		{
			numberNum++;
			numberBuffer[j] = *p;
			j++;
			p++;
			if (j > 6)
			{
				j = 0;
			}
			continue;
		}

		// ���б���ͼ�ؼ��в����б���������б������ı�   
		m_programLangList.InsertItem(0, _T("Java"));
		m_programLangList.SetItemText(0, 1, _T("1"));
		m_programLangList.SetItemText(0, 2, _T("99"));

		m_programLangList.InsertItem(1, _T("C"));
		m_programLangList.SetItemText(1, 1, _T("2"));
		m_programLangList.SetItemText(1, 2, _T("98"));

		m_programLangList.InsertItem(2, _T("C#"));
		m_programLangList.SetItemText(2, 1, _T("3"));
		m_programLangList.SetItemText(2, 2, _T("97"));

		m_programLangList.InsertItem(3, _T("C++"));
		m_programLangList.SetItemText(3, 1, _T("4"));
		m_programLangList.SetItemText(3, 2, _T("96"));

		i++;
		p++;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Ccaipiao_mfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Ccaipiao_mfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Ccaipiao_mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

