#pragma once
#include "GameLogic.h"

class CGameControl
{
public:
	//��̬��Ա����
	static int s_nRows;				//��Ϸ����
	static int s_nCols;					//��Ϸ����
	static int s_nPicNum;				//ͼƬ��

protected:
	//���ݳ�Ա
	Vertex m_svSelFst;					//ѡ�еĵ�һ����
	Vertex m_svSelSec;				//ѡ�еĵڶ�����
	int **m_mGameMap;			//��Ϸ��ͼ����ָ��
    CGameLogic m_GameLogic;	//��Ϸ�߼���������
public:
	CGameControl();
	~CGameControl();
	//��Ա����
	void StartGame(void);			//��ʼ��Ϸ
	int GetElement(int nRow, int nCol);	//�õ�ĳһ��Ԫ��
	void SetFirstPoint(int nRow, int nCol);		//���õ�һ����
	void SetSecPoint(int nRow, int nCol);		//���õڶ�����
	void SetFirstPointInfo(int  nBOOL);		//���õ�һ�������Ϣ
	void SetSecPointInfo(int  nBOOL);		//���õڶ��������Ϣ
	int GetFirstPointInfo();		//�õ���һ�������Ϣ
	int GetSecPointInfo();		//�õ��ڶ��������Ϣ
	int GetFirstPointRow();
	int GetFirstPointCol();
	BOOL Link(Vertex avPath[4], int &nVexnum);//�����жϣ�·���ݶ�Ϊ�������㣩
};

