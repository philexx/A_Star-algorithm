#include "Game.h"

void cGame::Init()
{
	//Note: Change the Height and Width in Sprite.cpp too
	m_TileHeight = 15;
	m_TileWidth = 15;
	float ToReserve = (SCREENWIDTH / m_TileWidth) * (SCREENHEIGHT / m_TileHeight);

	bRanOnce = false;
	m_Node = nullptr;
	NodeStart = nullptr;
	DestinationNode = nullptr;
	m_gameRun = true;
	m_Selecter = new CSelecter;
	m_ConnectionSprite = new cSprite;
	vNode.reserve(ToReserve);
	DrawGrid();
}//initialize

void cGame::Run()
{
	while (m_gameRun)
	{
		PollEvent();
		cFramerwork::Get()->Update();
		cFramerwork::Get()->Clear();
		/// <Game Relevant Operations>
		RenderGrid();
		SelectNode();
		m_Selecter->Render();
		Navigate();
		ConnectNeighbours();
		/// </Game Relevant Operations>
		cFramerwork::Get()->Render();
	}
}//Game loop

void cGame::PollEvent()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case(SDL_QUIT):
			{
				m_gameRun = false;
			}
		}
	}
}// Poll Event

void cGame::Del()
{
	for (auto node : vNode)
	{
		delete node;
	}
	vNode.clear();
}//Free Memory

void cGame::DrawGrid()
{
	float x = 0, y = 0;
	while (y <= SCREENHEIGHT - 10)
	{
		m_Node = new CNode;
		m_Node->Init(vec2(x, y));
		m_Node->SetNodeType(NODE_DEFAULT);
		vNode.emplace_back(m_Node);
		x += m_TileWidth;
		if (x >= SCREENWIDTH)
		{
			x = 0;
			y += m_TileWidth;
		}
	}
}

void cGame::RenderGrid()
{
	for (auto node : vNode)
	{
		node->Render();
		//node->DrawConnection();
	}
}

void cGame::SelectNode()
{
	for (auto node : vNode)
	{
		if (node->GetPosition().x == m_Selecter->GetPosition().x && node->GetPosition().y == m_Selecter->GetPosition().y)
		{
			if (cFramerwork::Get()->Keyboard(SDL_SCANCODE_DELETE))
			{
				for (auto nodes : vNode)
				{
					nodes->Reset();
				}
			}
			if (cFramerwork::Get()->Keyboard(SDL_SCANCODE_RETURN))
			{
				AStar();
				FindPath();
			}
			if (cFramerwork::Get()->Keyboard(SDL_SCANCODE_S))
			{
				ClearNode(NODE_START);
				node->SetNodeType(NODE_START);
				node->GetSprite()->SetColor(0, 255, 0);
				NodeStart = node;
				break;
			}
			if (cFramerwork::Get()->Keyboard(SDL_SCANCODE_D))
			{
				ClearNode(NODE_DESTINATION);
				node->SetNodeType(NODE_DESTINATION);
				node->GetSprite()->SetColor(254, 90, 29);
				DestinationNode = node;
				break;
			}
			if (cFramerwork::Get()->Keyboard(SDL_SCANCODE_W))
			{
				node->SetNodeType(NODE_WALL);
				node->GetSprite()->SetColor(105, 105, 105);
			}
			if (cFramerwork::Get()->Keyboard(SDL_SCANCODE_C))
			{
				node->Reset();
				node->GetSprite()->SetColor(0, 0, 139);
			}
		}
	}
}

void cGame::Navigate()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Rect mouseRect;
	mouseRect.w = 5;
	mouseRect.h = 5;
	mouseRect.x = x;
	mouseRect.y = y;

	for (auto node : vNode)
	{
		SDL_Rect nodeRect = node->GetSprite()->GetRect();
		if (SDL_HasIntersection(&mouseRect, &nodeRect))
		{
			m_Selecter->SetPosition(vec2(node->GetPosition().x, node->GetPosition().y));
		}
	}
}

void cGame::ClearNode(int Type)
{
	if (Type < 0 || Type > NODE_MAX)
	{
		std::cout << "Invalid Type!" << "\n";
		return;
	}

	for (auto node : vNode)
	{
		switch (Type)
		{
			case(NODE_START):
			{
				if (node->GetType() == NODE_START)
				{
					node->SetNodeType(NODE_DEFAULT);
					node->GetSprite()->SetColor(0, 0, 139);
					NodeStart = node;
					break;
				}
			}
			case(NODE_DESTINATION):
			{
				if (node->GetType() == NODE_DESTINATION)
				{
					node->SetNodeType(NODE_DEFAULT);
					node->GetSprite()->SetColor(0, 0, 139);
					break;
				}
			}
		}
	}
}


void cGame::ConnectNeighbours()
{
	if (!bRanOnce)
	{
		for (auto node : vNode)
		{
			std::vector<CNode*>* Temporary = node->GetVector();
			auto it = std::find_if(vNode.begin(), vNode.end(), [node](CNode* n) { return n->GetPosition().x == node->GetPosition().x + 15 && n->GetPosition().y == node->GetPosition().y; });

			std::cout << "****************************************************************************************" << std::endl;
			std::cout << "***FIRST***: Neighbors of X:  " << node->GetPosition().x << "Y: " << node->GetPosition().y << std::endl;
			if (it != vNode.end())
			{
				CNode* temp = *it;
				Temporary->emplace_back(temp);
				std::cout << "Neighbor is: X(+): " << temp->GetPosition().x << " Y: " << temp->GetPosition().y << std::endl;
			}
			it = std::find_if(vNode.begin(), vNode.end(), [node](CNode* n) { return n->GetPosition().x == (node->GetPosition().x - 15) && n->GetPosition().y == node->GetPosition().y; });
			if (it != vNode.end())
			{
				CNode* temp = *it;
				Temporary->emplace_back(temp);
				std::cout << "Neighbor is: X(-): " << temp->GetPosition().x << " Y: " << temp->GetPosition().y << std::endl;
			}
			it = std::find_if(vNode.begin(), vNode.end(), [node](CNode* n) { return n->GetPosition().y == node->GetPosition().y + 15 && n->GetPosition().x == node->GetPosition().x; });
			if (it != vNode.end())
			{
				CNode* temp = *it;
				Temporary->emplace_back(temp);
				std::cout << "Neighbor is: X: " << temp->GetPosition().x << " Y: " << temp->GetPosition().y << std::endl;
			}
			it = std::find_if(vNode.begin(), vNode.end(), [node](CNode* n) { return n->GetPosition().y == node->GetPosition().y - 15 && n->GetPosition().x == node->GetPosition().x; });
			if (it != vNode.end())
			{
				CNode* temp = *it;
				Temporary->emplace_back(temp);
				std::cout << "Neighbor is: X: " << temp->GetPosition().x << " Y: " << temp->GetPosition().y << std::endl;
				std::cout << "****************************************************************************************" << std::endl;
			}
		}
	}
	bRanOnce = true;
}//Connecting each Nodes neighbors


void cGame::ShowNeigh()
{
	for (auto node : vNode)
	{
		std::cout << "Neighbors of " << node->GetPosition().y << std::endl;
		node->ShowNeighbors();
	}
}


void cGame::FindPath()
{
	auto it = std::find_if(vNode.begin(), vNode.end(), [](const CNode* n) { return n->GetType() == NODE_DESTINATION; });
	if (it != vNode.end())
	{
		std::cout << "Parent found!" << std::endl;
		CNode* Parent = *it;

		while (Parent != nullptr)
		{
			Parent->SetVisited(false);
			if (Parent->GetType() != NODE_DESTINATION && Parent->GetType() != NODE_START)
			{
				Parent->SetNodeType(NODE_PATH);
			}
			Parent = Parent->GetParent();
		}
	}
} 


void cGame::AStar()
{
	float g = 0.0f;

	if (NodeStart == nullptr || DestinationNode == nullptr)
	{
		return;
	}

	std::list<CNode*> lOpen;
	std::list<CNode*> lClosed;

	//Initalize Starting Node
	CNode* CurrentNode = NodeStart;
	CurrentNode->SetGScore(g);
	CurrentNode->SetHScore(CalculateHeuristic(CurrentNode, DestinationNode));

	//Move Starting node into the Open List
	lOpen.push_back(CurrentNode);

	while (!lOpen.empty())
	{
		g++; //Increase the G-Score per tile

		//Get the neighbor with the lowest F-Score  F(N) = G(N) + H(N)
		lOpen.sort([](const CNode* lhs, const CNode* rhs) { return lhs->GetFScore() < rhs->GetFScore(); });

		//Remove the Node with the best F Score from the Open list and move it to the closed list
		CurrentNode = lOpen.front();
		lClosed.push_back(CurrentNode);
		lOpen.pop_front();
		CurrentNode->SetVisited(true);

		//Is the node the Destination?
		auto dest = std::find_if(lClosed.begin(), lClosed.end(), [](CNode* N) { return N->GetType() == NodeType::NODE_DESTINATION; });
		if (dest != lClosed.end())
		{
			break;
		}

		//Iterate through the Nodes neighbors
		for (auto neighbor : *CurrentNode->GetVector())
		{
			if (neighbor->GetType() == NodeType::NODE_WALL)
			{
				continue;
			}
			//is the current neighbor in the closed list already?
			auto it = std::find_if(lClosed.begin(), lClosed.end(), [neighbor](CNode* N) { return N->GetPosition().x == neighbor->GetPosition().x && N->GetPosition().y == neighbor->GetPosition().y; });
			if (it != lClosed.end())
			{
				continue;
			}

			auto itOpen = std::find_if(lOpen.begin(), lOpen.end(), [neighbor](CNode* N) { return N->GetPosition().x == neighbor->GetPosition().x && N->GetPosition().y == neighbor->GetPosition().y; });
			if (itOpen != lOpen.end())
			{
				//neighbor is in the Openlist
				if (g + CalculateHeuristic(neighbor, DestinationNode) < neighbor->GetHScore())
				{
					neighbor->SetGScore(CurrentNode->GetGScore());
					neighbor->SetFScore(g + CalculateHeuristic(neighbor, DestinationNode));
					neighbor->SetParent(CurrentNode);
				}
			}
			else
			{
				//neighbor is not in the openlist
				neighbor->SetGScore(g);
				neighbor->SetHScore(CalculateHeuristic(neighbor, DestinationNode));
				neighbor->SetFScore(g + CalculateHeuristic(neighbor, DestinationNode));
				neighbor->SetParent(CurrentNode);
				lOpen.push_back(neighbor);
			}
		}
	}
}//A*

float cGame::CalculateHeuristic(const CNode* a, const CNode* b)
{
	return (pow(a->GetPosition().x - b->GetPosition().x, 2)) + (pow(a->GetPosition().y - b->GetPosition().y, 2));
}