#include "Tree.h"
#include <time.h>
#include <queue>
#include <iostream>

Tree::Tree(In& in) :m_size(in.getSize()), m_in(in)
{
	setPosition();
	for (auto i = 0; i < m_in.getLights(); i++)
		m_lights.emplace_back(std::make_shared<lightPoint>(lightPoint{ std::make_shared<Light>(m_position[i], i), {} }));
	myNeighborn();	
	makeTree();
	turnEdge();
}; 

void Tree::clear()
{
	m_lights.clear();
	m_position.clear();
	m_in.clearLight();
}; 

void Tree::setPosition()
{
	Light l(sf::Vector2f(screenSize / 2, (screenSize / 2)), 0);
	float newEdgeLength = edgeLength + (l.m_point.getRadius());
	float hight = (float)sqrt(3) * (edgeLength + l.m_point.getRadius());
	float size = 2;
	m_position.push_back(sf::Vector2f(screenSize / 2, (screenSize / 2)));
	for (float j = 1; j <= m_in.getSize() / 2; j++) // its for the middle ligne of the game
	{
		m_position.push_back(sf::Vector2f((screenSize / 2) + newEdgeLength * j * 2, screenSize / 2));
		m_position.push_back(sf::Vector2f((screenSize / 2) - newEdgeLength * j * 2, screenSize / 2));
	}
	if (m_in.getSize() == 3)  size = 1;
	for (int i = m_in.getSize() - 1; i > size; i--)
		if (i % 2 == 1)
		{
			m_position.push_back(sf::Vector2f(screenSize / 2, (screenSize / 2) + hight * (m_in.getSize() - i)));
			m_position.push_back(sf::Vector2f(screenSize / 2, (screenSize / 2) - hight * (m_in.getSize() - i)));
			for (float j = 1; j <= i / 2; j++)
			{
				m_position.push_back(sf::Vector2f((screenSize / 2) + newEdgeLength * j * 2, (screenSize / 2) + hight * (m_in.getSize() - i)));
				m_position.push_back(sf::Vector2f((screenSize / 2) - newEdgeLength * j * 2, (screenSize / 2) + hight * (m_in.getSize() - i)));
				m_position.push_back(sf::Vector2f((screenSize / 2) + newEdgeLength * j * 2, (screenSize / 2) - hight * (m_in.getSize() - i)));
				m_position.push_back(sf::Vector2f((screenSize / 2) - newEdgeLength * j * 2, (screenSize / 2) - hight * (m_in.getSize() - i)));
			}
		}
		else
			for (int j = 0; j < i / 2; j++)
			{
				m_position.push_back(sf::Vector2f((screenSize / 2) + (newEdgeLength)+newEdgeLength * j * 2, (screenSize / 2) + hight * (m_in.getSize() - i)));
				m_position.push_back(sf::Vector2f((screenSize / 2) - (newEdgeLength)-newEdgeLength * j * 2, (screenSize / 2) + hight * (m_in.getSize() - i)));
				m_position.push_back(sf::Vector2f((screenSize / 2) + (newEdgeLength)+newEdgeLength * j * 2, (screenSize / 2) - hight * (m_in.getSize() - i)));
				m_position.push_back(sf::Vector2f((screenSize / 2) - (newEdgeLength)-newEdgeLength * j * 2, (screenSize / 2) - hight * (m_in.getSize() - i)));
			}
}

void Tree::myNeighborn()
{
	for (int i = 0; i < m_lights.size(); i++)
		for (int j = 0; j < m_lights.size(); j++)
			if (isNeighborn(i, j))
				m_lights[i]->m_neighborn.emplace_back(m_lights[j]->m_point);
}

bool Tree::isNeighborn(int i, int j)
{
	float newEdgeLength = edgeLength + (m_lights[0]->m_point->getPoint().getRadius());
	float hight = (float)sqrt(3) * (edgeLength + m_lights[0]->m_point->getPoint().getRadius());
	float x[2] = { m_lights[i]->m_point->getPoint().getPosition().x, m_lights[j]->m_point->getPoint().getPosition().x };
	float y[2] = { m_lights[i]->m_point->getPoint().getPosition().y, m_lights[j]->m_point->getPoint().getPosition().y };
	if (i != j)
		if ((abs(x[0] + (newEdgeLength * 2) - x[1]) < 5 && abs(y[0] - y[1]) < 5) ||
			(abs(x[0] - (newEdgeLength * 2) - x[1]) < 5 && abs(y[0] - y[1]) < 5) ||
			(abs(y[0] + hight - y[1]) < 5 && abs(x[0] + newEdgeLength - x[1]) < 5) ||
			(abs(y[0] - hight - y[1]) < 5 && abs(x[0] - newEdgeLength - x[1]) < 5) ||
			(abs(y[0] - hight - y[1]) < 5 && abs(x[0] + newEdgeLength - x[1]) < 5) ||
			(abs(y[0] + hight - y[1]) < 5 && abs(x[0] - newEdgeLength - x[1]) < 5))
			return true;
	return false;
}

void Tree::makeTree()
{
	srand((unsigned int)time(NULL));
	BFS(rand() % m_lights.size());
}

void Tree::BFS(int s)
{		
	std::queue<std::shared_ptr<Light>> queue;
	m_lights[s]->m_point->m_visited = true;
	auto vertice = (m_lights[s]->m_point);
	queue.push(vertice);

	while (!queue.empty())
	{
		//auto& n = (m_lights[vertice->m_whoIm]->m_neighborn);
		messNeighborn(vertice->m_whoIm);
		for (auto& neigh : m_lights[vertice->m_whoIm]->m_neighborn)
			if (!neigh->m_visited)
			{
				neigh->m_visited = true;
				queue.push(neigh);
				makeEdges(vertice, neigh);
			}
		queue.pop();
		if (queue.empty())
			break;
		vertice = queue.front();
	}
}

void Tree::messNeighborn(int index)
{
	srand((unsigned int)time(NULL));
	std::array< int , 6> arr;
	for (size_t i = 0; i < arr.size(); i++)
		arr[i] = -1;
	int i = 0;
	for (auto& n : m_lights[index]->m_neighborn)
		while (true)
			if (arr[rand() % m_lights[index]->m_neighborn.size()] == -1)
			{
				arr[rand() % m_lights[index]->m_neighborn.size()] = i++;
				break;
			}
	int j = 0;
	for (size_t i = 0; i < arr.size(); i++)
		if (arr[i] != -1)
			std::swap(m_lights[index]->m_neighborn[i] , m_lights[index]->m_neighborn[arr[i]]);
}
	
void Tree::makeEdges(std::shared_ptr<Light> cur, std::shared_ptr <Light> other)
{
	int angle;
	if (cur->getPoint().getPosition().y == other->getPoint().getPosition().y )
		angle = (cur->getPoint().getPosition().x < other->getPoint().getPosition().x) ? 0 : 3;
	else if(cur->getPoint().getPosition().y < other->getPoint().getPosition().y)
		angle = (cur->getPoint().getPosition().x < other->getPoint().getPosition().x) ? 1 : 2;
	else
		angle = (cur->getPoint().getPosition().x < other->getPoint().getPosition().x) ? 5 : 4;
	cur->setEdges(angle);
	other->setEdges((angle + 3) % 6);
	
}

void Tree::turnEdge()
{
	
	for (auto& i : m_lights)
	{
		srand(time(NULL)+i->m_point->m_whoIm);
		int turn = rand() % 6;
		for (auto& e :i->m_point->m_edges)		
			e.rotate(rotation +( turn * rotation));
	}
}

