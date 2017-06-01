#pragma once
#include"global.h"

class CGameLogic
{
protected:
	Vertex m_avPath[4];				//保存在进行连接判断时经过的顶点
	int m_nVexNum;					//顶点数
public:
	CGameLogic();
	~CGameLogic();
	int ** InitMap();								//初始化游戏地图
	void ReleaseMap(int ** &pGameMap);		//释放地图
	BOOL IsLink(int **pGameMap, Vertex V1, Vertex V2);	//判断是否联通
	void Clear(int **pGameMap, Vertex V1, Vertex V2);		//消子
	int GetVerPath(Vertex avPath[4]);								//得到路径，返回的是顶点数
protected:
	BOOL LinkInRow(int **pGameMap, Vertex V1, Vertex V2);	//判断横向是否连通
	BOOL LinkInCol(int **pGameMap, Vertex V1, Vertex V2);		//判断纵向是否联通
	BOOL OneCornerLink(int **pGameMap, Vertex V1, Vertex V2);	//一个拐点连通判断
	BOOL LineY(int **pGameMap, int nRow1, int nRow2, int nCol);		//直线连通Y轴
	BOOL LineX(int **pGameMap, int nRow, int nCol1, int nCol2);		//直线连通X轴
	void PushVertex(Vertex X);							//添加一个路径顶点
	void PopVertex();										//取出一个顶点
	void ClearStack();										//清除栈
	BOOL TwoCornerLink(int **pGameMap, Vertex V1, Vertex V2);	//三条直线消子判断
};

