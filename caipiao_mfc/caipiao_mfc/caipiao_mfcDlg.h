
// caipiao_mfcDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// Ccaipiao_mfcDlg �Ի���
class Ccaipiao_mfcDlg : public CDialogEx
{
// ����
public:
	Ccaipiao_mfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CAIPIAO_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_programLangList;
};
