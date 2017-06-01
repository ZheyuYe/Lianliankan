#include "stdafx.h"
#include "GameLogic.h"
#include "GameControl.h"


CGameLogic::CGameLogic()
{
	m_nVexNum = 0;
}


CGameLogic::~CGameLogic()
{
	
}


int ** CGameLogic::InitMap()
{

	//获取地图大小和花色
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;

	//开辟内存区域
	int **pGameMap = new int *[nRows];
	if (pGameMap == NULL)
	{	
		//throw new CGameException(_T("内存操作异常！\n"));
	}
	else
	{
		for (int i = 0; i < nRows; i++)
		{
			pGameMap[i] = new int[nCols];
			if (pGameMap == NULL)
			{
				//throw new CGameException(_T("内存操作异常！\n"));
			}
			memset(pGameMap[i], NULL, sizeof(int)*nCols);
		}
	}

	//多少花色
	if ((nRows*nCols) % (nPicNum * 2) != 0)
	{
		ReleaseMap(pGameMap);
		//throw new CGameException(_T("游戏花色与游戏地图大小不匹配！\n"));
	}
	int nRepetNum = nRows*nCols / nPicNum;			//花色
	int nCount = 0;
	for (int i = 0; i < nPicNum; i++)
	{
		//重复数
		for (int j = 0; j < nRepetNum; j++)
		{
			pGameMap[nCount / nCols][nCount%nCols] = i;
			nCount++;
		}
	}

	//设置种子
	srand((int)time(NULL));

	//随机任意交换两个数字
	int nVertexNum = nRows*nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;

		//交换两个数值
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1%nCols];
		pGameMap[nIndex1 / nCols][nIndex1%nCols] = pGameMap[nIndex2 / nCols][nIndex2%nCols];
		pGameMap[nIndex2 / nCols][nIndex2%nCols] = nTmp;
	}
	return pGameMap;
}

void CGameLogic::ReleaseMap(int **& pGameMap)
{
	for (int i = 0; i < CGameControl::s_nRows; i++)
	{
		delete []pGameMap[i];
	}
	delete[]pGameMap;
}

BOOL CGameLogic::IsLink(int ** pGameMap, Vertex V1, Vertex V2)
{
	ClearStack();
	PushVertex(V1);
	//X直连方式
	if (V1.row == V2.row)
	{
		if(LinkInRow(pGameMap, V1, V2))
			return true;
	}
	//Y直连方式
	if(V1.col==V2.col)
	{
		if(LinkInCol(pGameMap, V1, V2))
			return true;		
	}
	//直角消子
	if (OneCornerLink(pGameMap, V1, V2))
	{
		PushVertex(V2);
		return true;
	}
	if (TwoCornerLink(pGameMap, V1, V2))
	{
		PushVertex(V2);
		return true;
	}
	ClearStack();
	return false;
}

void CGameLogic::Clear(int ** pGameMap, Vertex V1, Vertex V2)
{
	pGameMap[V1.row][V1.col] = BLANK;
	pGameMap[V2.row][V2.col] = BLANK;
}

int CGameLogic::GetVerPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return  m_nVexNum;
}

BOOL CGameLogic::LinkInRow(int ** pGameMap, Vertex V1, Vertex V2)
{
	int nCol1 = V1.col;
	int nCol2 = V2.col;
	int nRow = V1.row;
	//保证nCol1的值小于nCol2
	if (nCol1>nCol2)
	{
		int temp = nCol1;
		nCol1 = nCol2;
		nCol2 = temp;
	}
	//X直通
	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (nCol2 == i)
		{
			PushVertex(V2);
			return true;
		}
		if (pGameMap[nRow][i] != BLANK)
			break;
	}
	ClearStack();
	return false;
}

BOOL CGameLogic::LinkInCol(int ** pGameMap, Vertex V1, Vertex V2)
{
	int nRow1 = V1.row;
	int nRow2 = V2.row;
	int nCol = V1.col;
	//保证nRow1的值小于nRow2
	if (nRow1 > nRow2)
	{
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;
	}
	//Y直通
	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (nRow2 == i)
		{
			PushVertex(V2);
			return true;
		}
		if (pGameMap[i][nCol] != BLANK)
			break;
	}
	ClearStack();
	return false;
}

BOOL CGameLogic::OneCornerLink(int ** pGameMap, Vertex V1, Vertex V2)
{
	//直角能够消子，那么顶点一定在与两个点的行和列相交的点
	//只有这个点为空，才有可能实现两条直线消子
	if (pGameMap[V1.row][V2.col] == BLANK)
	{
		if (LineY(pGameMap, V1.row, V2.row, V2.col) && LineX(pGameMap, V1.row, V1.col, V2.col))
		{
			Vertex V = { V1.row,V2.col,BLANK };
			PushVertex(V);
			return true;
		}
	}
	if (pGameMap[V2.row][V1.col] == BLANK)
	{
		if (LineY(pGameMap, V1.row, V2.row, V1.col) && LineX(pGameMap, V2.row, V1.col, V2.col))
		{
			Vertex V = { V2.row,V1.col,BLANK };
			PushVertex(V);
			return true;
		}
	}
	return false;
}

BOOL CGameLogic::LineY(int ** pGameMap, int nRow1, int nRow2, int nCol)
{
	int mRow1 = nRow1;
	int mRow2 = nRow2;
	//保证mRow1的值小于mRow2
	if (mRow1 > mRow2)
	{
		int temp = mRow1;
		mRow1 = mRow2;
		mRow2 = temp;
	}
	for (int i = mRow1 + 1; i <= mRow2; i++)
	{
		if (mRow2 == i)
			return true;
		if (pGameMap[i][nCol] != BLANK)
			break;
	}
	return false;
}

BOOL CGameLogic::LineX(int ** pGameMap, int nRow, int nCol1, int nCol2)
{
	int mCol1 = nCol1;
	int mCol2 = nCol2;
	//保证mCol1的值小于mCol2
	if (mCol1>mCol2)
	{
		int temp = mCol1;
		mCol1 = mCol2;
		mCol2 = temp;
	}
	//X直通
	for (int i = mCol1 + 1; i <= mCol2; i++)
	{
		if (mCol2 == i)
			return true;
		if (pGameMap[nRow][i] != BLANK)
			break;
	}
	return false;
}

void CGameLogic::PushVertex(Vertex X)
{
	m_avPath[m_nVexNum++] = X;
}

void CGameLogic::PopVertex()
{
	m_nVexNum--;
}

void CGameLogic::ClearStack()
{
	m_nVexNum = 0;
}

BOOL CGameLogic::TwoCornerLink(int ** pGameMap, Vertex V1, Vertex V2)
{
	//
	for (int nCol = 0; nCol < CGameControl::s_nCols; nCol++)
	{
		//找到一条与Y轴平行的连通线段
		if (pGameMap[V1.row][nCol] == BLANK && pGameMap[V2.row][nCol] == BLANK)
		{
			if (LineY(pGameMap, V1.row, V2.row, nCol))
			{
				if (LineX(pGameMap, V1.row, V1.col, nCol) && LineX(pGameMap, V2.row, V2.col, nCol))
				{
					//保存节点
					Vertex Vx1 = { V1.row,nCol,BLANK };
					Vertex Vx2 = { V2.row,nCol,BLANK };
					PushVertex(Vx1);
					PushVertex(Vx2);
					return true;
				}
			}
		}
	}
	for (int nRow = 0; nRow < CGameControl::s_nRows; nRow++)
	{
		//找到一条与X轴平行的连通线段
		if (pGameMap[nRow][V1.col] == BLANK && pGameMap[nRow][V2.col] == BLANK)
		{
			if (LineX(pGameMap, nRow, V1.col, V2.col))
			{
				if (LineY(pGameMap, nRow, V1.row, V1.col) && LineY(pGameMap, nRow, V2.row, V2.col))
				{
					//保存节点
					Vertex Vx1 = { nRow,V1.col,BLANK };
					Vertex Vx2 = { nRow,V2.col,BLANK };
					PushVertex(Vx1);
					PushVertex(Vx2);
					return true;
				}
			}
		}
	}
	return false;
}
