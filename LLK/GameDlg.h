#pragma once
#include "GameControl.h"
#include "GameLogic.h"

// CGameDlg �Ի���
class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

protected:
	HICON m_hIcon;		//�Ի���ͼ��
	CDC m_dcBG;			//����DC
	CDC m_dcMem;		//�ڴ�DC
	CDC m_dcElement;	//Ԫ���ڴ�DC
	CDC m_dcMask;		//�����ڴ�DC
	CPoint m_ptGameTop;	//��Ϸ����ʼ�㣨��Ϸ��һ��ͼƬ�Ķ������꣬��������ڴ��ڿͻ�����
	CSize m_sizeElem;		//Ԫ��ͼƬ��С
	CRect m_rtGameRect;	//��Ϸ�����С
	CGameControl m_GameC;	//��Ϸ����

	void InitBackground(void);			//��ʼ�����ڱ���
	void InitElement(void);			//��ʼ��Ԫ��ͼƬ��DC
	void UpdateWindow(void);	//���½���
	void UpdateMap(void);			//������Ϸ��ͼ
	void ClearVertex(Vertex V1,Vertex V2);	//��ȥV1,V2

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnFinalRelease();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipFrame(int nRow, int nCol);		//������ʾ��
	void DrawTipLine(Vertex asvPath[4], int nVexnum);		//������ʾ��
};
