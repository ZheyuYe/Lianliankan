#pragma once
#include "GameLogic.h"

class CGameControl
{
public:
	//静态成员变量
	static int s_nRows;				//游戏行数
	static int s_nCols;					//游戏列数
	static int s_nPicNum;				//图片数

protected:
	//数据成员
	Vertex m_svSelFst;					//选中的第一个点
	Vertex m_svSelSec;				//选中的第二个点
	int **m_mGameMap;			//游戏地图数组指针
    CGameLogic m_GameLogic;	//游戏逻辑操作对象
public:
	CGameControl();
	~CGameControl();
	//成员函数
	void StartGame(void);			//开始游戏
	int GetElement(int nRow, int nCol);	//得到某一个元素
	void SetFirstPoint(int nRow, int nCol);		//设置第一个点
	void SetSecPoint(int nRow, int nCol);		//设置第二个点
	void SetFirstPointInfo(int  nBOOL);		//设置第一个点的信息
	void SetSecPointInfo(int  nBOOL);		//设置第二个点的信息
	int GetFirstPointInfo();		//得到第一个点的信息
	int GetSecPointInfo();		//得到第二个点的信息
	int GetFirstPointRow();
	int GetFirstPointCol();
	BOOL Link(Vertex avPath[4], int &nVexnum);//消子判断（路径暂定为两个顶点）
};

