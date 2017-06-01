#include "stdafx.h"
#include "GameControl.h"

int CGameControl::s_nRows = 10;
int CGameControl::s_nCols = 16;
int CGameControl::s_nPicNum = 16;

void CGameControl::StartGame(void)
{
	m_mGameMap =m_GameLogic.InitMap();
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_mGameMap[nRow][nCol];
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}

void CGameControl::SetFirstPointInfo(int nBOOL)
{
	m_svSelFst.info = nBOOL;
}

void CGameControl::SetSecPointInfo(int nBOOL)
{
	m_svSelSec.info = nBOOL;
}

int CGameControl::GetFirstPointInfo()
{
	return m_svSelFst.info;
}

int CGameControl::GetSecPointInfo()
{
	return m_svSelSec.info;
}

int CGameControl::GetFirstPointRow()
{
	return m_svSelFst.row;
}

int CGameControl::GetFirstPointCol()
{
	return m_svSelFst.col;
}

BOOL CGameControl::Link(Vertex avPath[4], int & nVexnum)
{
	//判断图片是否相同
	if (m_mGameMap[m_svSelFst.row][m_svSelFst.col] != m_mGameMap[m_svSelSec.row][m_svSelSec.col])
		return false;
	if (m_GameLogic.IsLink(m_mGameMap, m_svSelFst, m_svSelSec))
	{
		//消子
		m_GameLogic.Clear(m_mGameMap, m_svSelFst, m_svSelSec);

		//返回路径顶点
		nVexnum = m_GameLogic.GetVerPath(avPath);
		return true;
	}
	return false;
}

CGameControl::CGameControl()
{
	//开辟空间
	m_mGameMap = new int *[s_nRows];
	for (int i = 0; i < s_nRows; i++)
	{
		m_mGameMap[i] = new int[s_nCols];
		if (m_mGameMap == NULL)
		{
			//throw new CGameException(_T("内存操作异常！\n"));
		}
		memset(m_mGameMap[i], NULL, sizeof(int)*s_nCols);
	}
	//初始化Vertex
	m_svSelFst.info = FALSE;
	m_svSelSec.info = FALSE;
}


CGameControl::~CGameControl()
{
}