#pragma once

#include "Sprite.h"
#include <vector>

class CNode
{
private:
	cSprite* m_Sprite;
	cSprite* m_line;
	int m_Width;
	int m_Height;
	int m_NodeType;
	int m_SelectedNode;
	vec2 m_Position;

private:
	bool bVisited;
	float fHScore;
	float fGScore;
	float fFScore;
	std::vector<CNode*> vNeighbours;
	CNode* Parent;

public:
	void Init(const vec2& Position);
	void Render();
	void SetPosition(const vec2& Position);
	void SetNodeType(int type);
	void ShowNeighbors();
	void DrawConnection();
	void RenderConnection();
	void Reset();

public:
	//Getter
	int GetType() const { return m_NodeType; }
	cSprite* GetSprite() { return m_Sprite; }
	SDL_Rect GetPosition() const { return m_Sprite->GetRect(); }
	std::vector<CNode*>* GetVector() { return &vNeighbours; }
	CNode* GetParent() { return Parent; }

	void SetHScore(float score) { fHScore = score; }
	void SetGScore(float score) { fGScore = score; }
	void SetFScore(float FScore) { fFScore = FScore; };
	void SetVisited(bool visited) { bVisited = visited; }
	void SetParent(CNode* _parent) { Parent = _parent; }

public:
	//Setter
	float GetHScore()	const { return fHScore; }
	float GetGScore()	const { return fGScore; }
	float GetFScore()	const { return fFScore; }
	bool GetVisited()	const { return bVisited; }
};
