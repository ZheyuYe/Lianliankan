
// LLKDlg.h : ͷ�ļ�
//

#pragma once

// CLLKDlg �Ի���
class CLLKDlg : public CDialogEx
{
// ����
public:
	CLLKDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CDC m_dcMem;		//��ʾλͼ�ڴ�

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
	void InitBackground();
public:
	afx_msg void OnBnClickedBtnBasic();
	afx_msg void OnBnClickedBtnRelax();
	afx_msg void OnBnClickedBtnLevel();
	afx_msg void OnBnClickedBtnRank2();
};