#pragma once
#include"global.h"

class CGameLogic
{
protected:
	Vertex m_avPath[4];				//�����ڽ��������ж�ʱ�����Ķ���
	int m_nVexNum;					//������
public:
	CGameLogic();
	~CGameLogic();
	int ** InitMap();								//��ʼ����Ϸ��ͼ
	void ReleaseMap(int ** &pGameMap);		//�ͷŵ�ͼ
	BOOL IsLink(int **pGameMap, Vertex V1, Vertex V2);	//�ж��Ƿ���ͨ
	void Clear(int **pGameMap, Vertex V1, Vertex V2);		//����
	int GetVerPath(Vertex avPath[4]);								//�õ�·�������ص��Ƕ�����
protected:
	BOOL LinkInRow(int **pGameMap, Vertex V1, Vertex V2);	//�жϺ����Ƿ���ͨ
	BOOL LinkInCol(int **pGameMap, Vertex V1, Vertex V2);		//�ж������Ƿ���ͨ
	BOOL OneCornerLink(int **pGameMap, Vertex V1, Vertex V2);	//һ���յ���ͨ�ж�
	BOOL LineY(int **pGameMap, int nRow1, int nRow2, int nCol);		//ֱ����ͨY��
	BOOL LineX(int **pGameMap, int nRow, int nCol1, int nCol2);		//ֱ����ͨX��
	void PushVertex(Vertex X);							//���һ��·������
	void PopVertex();										//ȡ��һ������
	void ClearStack();										//���ջ
	BOOL TwoCornerLink(int **pGameMap, Vertex V1, Vertex V2);	//����ֱ�������ж�
};

