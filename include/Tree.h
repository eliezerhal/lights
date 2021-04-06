#pragma once
#include <vector>
#include <array>
#include <memory>
#include "Light.h"
#include "In.h"
#include <iosfwd>
const int screenSize = 1000;

class Tree
{
public:
	Tree(In& in);
	~Tree() = default;
	struct lightPoint
	{
		std::shared_ptr<Light> m_point;
		std::vector<std::shared_ptr<Light>> m_neighborn;
	};
	
private:
	std::vector<std::shared_ptr<lightPoint>> m_lights;
	In m_in;
	std::vector<sf::Vector2f> m_position;
	int m_size;

public:
	void clear();
	void setPosition();
	void myNeighborn();
	bool isNeighborn(int i, int j);
	void makeTree();
	void BFS(int s);
	void messNeighborn(int index);// std::vector < std::shared_ptr<Light>>& neighborn);
	void makeEdges(std::shared_ptr<Light> cur, std::shared_ptr<Light> other);
	std::vector< std::shared_ptr<lightPoint>> getLights() { return m_lights; };
	void turnEdge();
};