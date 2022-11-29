#ifndef GAME_H
#define GAME_H

#include <random>
#include "Node.h"
#include "Selecter.h"
#include <limits>
#include <list>
#include <cmath>


enum NodeType
{
	NODE_DEFAULT,
	NODE_START,
	NODE_DESTINATION,
	NODE_WALL,
	NODE_PATH,
	NODE_MAX = NODE_PATH,
};

class cGame
{
private:
	bool bRanOnce;
	bool m_gameRun;

	CNode* m_Node;
	CNode* DestinationNode;
	CNode* NodeStart;

	CSelecter* m_Selecter;
	cSprite* m_ConnectionSprite;

	int m_TileWidth;
	int m_TileHeight;

private:

	std::vector<CNode*> vNode;

private:

public:
	void Init();
	void Run();
	void PollEvent();
	void Del();
	void DrawGrid();
	void RenderGrid() const;
	void SelectNode();
	void Navigate() const;
	void ClearNode(int Type);
	void ConnectNeighbours();
	void ShowNeigh() const;
	void FindPath();
	float CalculateHeuristic(const CNode* a, const CNode* b) const;
	void AStar() const;

private:

	template <class T>
	void Delete(T Object)
	{
		if (Object)
		{
			delete Object;
			Object = nullptr;
		}
	}
};

#endif // !GAME_H
