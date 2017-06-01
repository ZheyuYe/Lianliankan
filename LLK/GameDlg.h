#pragma once
#include "GameControl.h"
#include "GameLogic.h"

// CGameDlg 对话框
class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	HICON m_hIcon;		//对话框图标
	CDC m_dcBG;			//背景DC
	CDC m_dcMem;		//内存DC
	CDC m_dcElement;	//元素内存DC
	CDC m_dcMask;		//掩码内存DC
	CPoint m_ptGameTop;	//游戏区起始点（游戏第一张图片的顶点坐标，坐标相对于窗口客户区域）
	CSize m_sizeElem;		//元素图片大小
	CRect m_rtGameRect;	//游戏区域大小
	CGameControl m_GameC;	//游戏控制

	void InitBackground(void);			//初始化窗口背景
	void InitElement(void);			//初始化元素图片与DC
	void UpdateWindow(void);	//更新界面
	void UpdateMap(void);			//更新游戏地图
	void ClearVertex(Vertex V1,Vertex V2);	//消去V1,V2

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnFinalRelease();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipFrame(int nRow, int nCol);		//绘制提示框
	void DrawTipLine(Vertex asvPath[4], int nVexnum);		//绘制提示框
};
