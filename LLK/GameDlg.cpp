// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
		m_hIcon = AfxGetApp()->LoadIcon(IDR_GAMEBASIC);
		//图片大小40*40
		m_sizeElem.cx = 40;
		m_sizeElem.cy = 40;
		//顶点坐标(20,50)
		m_ptGameTop.x = 20;
		m_ptGameTop.y = 50;		
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitBackground(void)
{
	CBitmap hBg;
	hBg.LoadBitmapW(IDB_GAME_BG1);
	//HANDLE hBg = ::LoadImageW(NULL, _T("theme\\picture\\animal_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(hBg);
}

void CGameDlg::InitElement(void)
{
	//获得当前对话框的视频内存
	CClientDC dc(this);

	//加载BMP图片资源
	CBitmap hElement;
	hElement.LoadBitmapW(IDB_GAME_ELEMENT1);
	//HANDLE hElement = ::LoadImageW(NULL, _T("theme\\picture\\animal_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(hElement);

	//加载掩码BMP图片资源
	CBitmap hMask;
	hMask.LoadBitmapW(IDB_GAME_MASK1);
	//HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\animal_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);

	CBitmap hBg;
	hBg.LoadBitmapW(IDB_GAME_BG1);
	//HANDLE hBg = ::LoadImageW(NULL, _T("theme\\picture\\animal_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(hBg);
}

void CGameDlg::UpdateWindow(void)
{
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//获得窗口大小
	this->GetClientRect(rtClient);		    //获得客户区大小

	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	//设置窗口大小
	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT + nSpanHeight);
	CenterWindow();
}

void CGameDlg::UpdateMap(void)
{
	//计算图片的顶点坐标与图片大小
	//……
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;	//顶点坐标(20,50)
	int nElemH = m_sizeElem.cx;
	int nElemW = m_sizeElem.cy;	//图片大小40*40
	//行数和列树
	int nRows = m_GameC.s_nRows;
	int nCols = m_GameC.s_nCols;

	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.bottom = m_ptGameTop.y+nRows*nElemH;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_ptGameTop.x + nCols*nElemW;

	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			//得到图片编号的值
			int nElemVal = m_GameC.GetElement(i, j);
			if (nElemVal !=BLANK)
			{
				//将背景图片与掩码相或，边保留，图像区域为1
				m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal*nElemH, SRCPAINT);

				//与元素图片相与，边保留，图像区域为元素图片
				m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal*nElemH, SRCAND);
			}
			else
			{
				m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcBG, nLeft + j*nElemW, nTop + i*nElemH, SRCCOPY);
			}
		}
	}
	InvalidateRect(NULL, TRUE);
}

void CGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//创建CPaintDC对象
		CPaintDC dc(this);
		//绘制背景图片
		dc.BitBlt(0, 0, GAMEWND_WIDTH, GAMEWND_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	UpdateWindow();
	InitBackground();
	InitElement();
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CGameDlg::OnFinalRelease()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnFinalRelease();
}


void CGameDlg::OnBnClickedBtnStart()
{
	m_GameC.StartGame();	
	UpdateMap();
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	//判断鼠标点击的区域
	if (point.y > m_rtGameRect.top && point.y<m_rtGameRect.bottom && point.x>m_rtGameRect.left && point.x < m_rtGameRect.right)
	{
		int nRow = (point.y - m_rtGameRect.top) / m_sizeElem.cx;
		int nCol = (point.x - m_rtGameRect.left) / m_sizeElem.cy;
		if(m_GameC.GetElement(nRow,nCol)!=BLANK)
		{
			if (m_GameC.GetFirstPointInfo() == FALSE)
			{
				DrawTipFrame(nRow, nCol);
				m_GameC.SetFirstPoint(nRow, nCol);
				m_GameC.SetFirstPointInfo(TRUE);
			}
			else if (m_GameC.GetSecPointInfo() == FALSE && !(nRow == m_GameC.GetFirstPointRow() && nCol == m_GameC.GetFirstPointCol()))
			{
				DrawTipFrame(nRow, nCol);
				m_GameC.SetSecPoint(nRow, nCol);
				m_GameC.SetSecPointInfo(TRUE);

				if (m_GameC.GetFirstPointInfo() == TRUE && m_GameC.GetFirstPointInfo() == TRUE)
				{
					Vertex avPath[4];
					int nVexnum;
					if (m_GameC.Link(avPath, nVexnum))
					{
						//画提示线
						DrawTipLine(avPath, nVexnum);
						//更新地图
						ClearVertex(avPath[0],avPath[nVexnum-1]);
					}
					m_GameC.SetFirstPointInfo(FALSE);
					m_GameC.SetSecPointInfo(FALSE);
					InvalidateRect(NULL, TRUE);
				}
			}
		}
	}
	return CDialogEx::OnLButtonUp(nFlags, point);
}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	HDC hDc = ::GetDC(m_hWnd);
	HPEN hPen =CreatePen(PS_INSIDEFRAME,2,RGB(233,43,43));
	SelectObject(hDc, hPen);
	//绘制提示框
	MoveToEx(hDc, m_rtGameRect.left + nCol * 40, m_rtGameRect.top + nRow * 40,NULL);
	LineTo(hDc, m_rtGameRect.left + nCol * 40+40, m_rtGameRect.top + nRow * 40);
	LineTo(hDc, m_rtGameRect.left + nCol * 40 + 40, m_rtGameRect.top + nRow * 40+40);
	LineTo(hDc, m_rtGameRect.left + nCol * 40 , m_rtGameRect.top + nRow * 40+40);
	LineTo(hDc, m_rtGameRect.left + nCol * 40, m_rtGameRect.top + nRow * 40);
	Sleep(200);
}

void CGameDlg::DrawTipLine(Vertex asvPath[4], int nVexnum)
{
	HDC hDc = ::GetDC(m_hWnd);
	HPEN hPen = CreatePen(PS_INSIDEFRAME, 2, RGB(0, 255, 0));
	SelectObject(hDc, hPen);

	MoveToEx(hDc,m_ptGameTop.x + asvPath[0].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y+asvPath[0].row*m_sizeElem.cy + m_sizeElem.cy / 2,NULL);
	for (int i = 1; i < nVexnum; i++)
	{
		LineTo(hDc,m_ptGameTop.x + asvPath[i].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[i].row*m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	Sleep(300);
}
void CGameDlg::ClearVertex(Vertex V1,Vertex V2)
{
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;	//顶点坐标(20,50)
	int nElemH = m_sizeElem.cx;
	int nElemW = m_sizeElem.cy;	//图片大小40*40
	m_dcMem.BitBlt(nLeft + V1.col*nElemW, nTop + V1.row*nElemH, nElemW, nElemH, &m_dcBG, nLeft + V1.col*nElemW, nTop + V1.row*nElemH, SRCCOPY);
	m_dcMem.BitBlt(nLeft + V2.col*nElemW, nTop + V2.row*nElemH, nElemW, nElemH, &m_dcBG, nLeft + V2.col*nElemW, nTop + V2.row*nElemH, SRCCOPY);
	InvalidateRect(NULL, TRUE);
}

