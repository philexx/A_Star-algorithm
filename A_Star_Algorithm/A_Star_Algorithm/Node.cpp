#include "Node.h"

#include <iostream>

void CNode::Init(const vec2& Position)
{
	m_Sprite = new cSprite;
	m_line = new cSprite;
	m_Width = 50;
	m_Height = 50;
	m_Position = Position;
	m_NodeType = 0; //Default
	m_SelectedNode = 0;
	bVisited = false;
	fHScore = std::numeric_limits<float>::max();
	fGScore = std::numeric_limits<float>::max();
	Parent = nullptr;
}

void CNode::Render() const
{
	if (!bVisited)
	{
		switch (m_NodeType)
		{
		case(1):
			m_Sprite->SetColor(0, 255, 0);
			break;
		case(2):
			m_Sprite->SetColor(254, 90, 29);
			break;
		case(3):
			m_Sprite->SetColor(105, 105, 105);
			break;
		case(4):
			m_Sprite->SetColor(162, 124, 91);
			break;
		default:
			m_Sprite->SetColor(0, 64, 255);
			break;
		}
	}
	else
	{
		m_Sprite->SetColor(65, 105, 225);
	}

	m_Sprite->SetPos(m_Position);
	m_Sprite->DrawRect();
}

void CNode::SetPosition(const vec2& Position)
{
	m_Sprite->SetPos(Position);
}

void CNode::SetNodeType(int type)
{
	m_NodeType = type;
}

void CNode::ShowNeighbors()
{
	std::cout << "*****************************************************************************************" << std::endl;
	std::cout << "My Position X: " << this->GetPosition().x << " Y: " << this->GetPosition().y << std::endl;
	std::cout << "******> MY NEIGHBORS <********" << std::endl;
	std::cout << std::endl;
	for (const auto neigh : vNeighbours)
	{
		std::cout << "->>> X: " << neigh->GetPosition().x << " Y: <<<-" << neigh->GetPosition().y << std::endl;
		CNode const* parent = neigh->GetParent();
		if (parent != nullptr)
		{
			std::cout << "->>> Parent: " << parent->GetPosition().x << " Y: " << parent->GetPosition().y << std::endl;
		}

	}
	std::cout << std::endl;
	std::cout << "*****************************************************************************************" << std::endl;
}

void CNode::DrawConnection() const
{
	for (auto n : vNeighbours)
	{
		m_line->RenderLine(m_Sprite->GetRect().x + 22, m_Sprite->GetRect().y + 22, n->GetSprite()->GetRect().x + 22, n->GetSprite()->GetRect().y + 22);
	}
}

void CNode::RenderConnection()
{
}

void CNode::Reset()
{
	m_NodeType = 0; //Default
	m_SelectedNode = 0;
	bVisited = false;
	fHScore = std::numeric_limits<float>::max();
	fGScore = std::numeric_limits<float>::max();
	Parent = nullptr;
}

