// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"

// CGameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
		m_hIcon = AfxGetApp()->LoadIcon(IDR_GAMEBASIC);
		//ͼƬ��С40*40
		m_sizeElem.cx = 40;
		m_sizeElem.cy = 40;
		//��������(20,50)
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


// CGameDlg ��Ϣ�������


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
	//��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);

	//����BMPͼƬ��Դ
	CBitmap hElement;
	hElement.LoadBitmapW(IDB_GAME_ELEMENT1);
	//HANDLE hElement = ::LoadImageW(NULL, _T("theme\\picture\\animal_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(hElement);

	//��������BMPͼƬ��Դ
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
	//�������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//��ô��ڴ�С
	this->GetClientRect(rtClient);		    //��ÿͻ�����С

	//����������߿�Ĵ�С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	//���ô��ڴ�С
	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT + nSpanHeight);
	CenterWindow();
}

void CGameDlg::UpdateMap(void)
{
	//����ͼƬ�Ķ���������ͼƬ��С
	//����
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;	//��������(20,50)
	int nElemH = m_sizeElem.cx;
	int nElemW = m_sizeElem.cy;	//ͼƬ��С40*40
	//����������
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
			//�õ�ͼƬ��ŵ�ֵ
			int nElemVal = m_GameC.GetElement(i, j);
			if (nElemVal !=BLANK)
			{
				//������ͼƬ��������򣬱߱�����ͼ������Ϊ1
				m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal*nElemH, SRCPAINT);

				//��Ԫ��ͼƬ���룬�߱�����ͼ������ΪԪ��ͼƬ
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
		//����CPaintDC����
		CPaintDC dc(this);
		//���Ʊ���ͼƬ
		dc.BitBlt(0, 0, GAMEWND_WIDTH, GAMEWND_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	UpdateWindow();
	InitBackground();
	InitElement();
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CGameDlg::OnFinalRelease()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnFinalRelease();
}


void CGameDlg::OnBnClickedBtnStart()
{
	m_GameC.StartGame();	
	UpdateMap();
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	//�ж������������
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
						//����ʾ��
						DrawTipLine(avPath, nVexnum);
						//���µ�ͼ
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
	//������ʾ��
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
	int nTop = m_ptGameTop.y;	//��������(20,50)
	int nElemH = m_sizeElem.cx;
	int nElemW = m_sizeElem.cy;	//ͼƬ��С40*40
	m_dcMem.BitBlt(nLeft + V1.col*nElemW, nTop + V1.row*nElemH, nElemW, nElemH, &m_dcBG, nLeft + V1.col*nElemW, nTop + V1.row*nElemH, SRCCOPY);
	m_dcMem.BitBlt(nLeft + V2.col*nElemW, nTop + V2.row*nElemH, nElemW, nElemH, &m_dcBG, nLeft + V2.col*nElemW, nTop + V2.row*nElemH, SRCCOPY);
	InvalidateRect(NULL, TRUE);
}

