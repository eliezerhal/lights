#pragma once
#include <SFML/Graphics.hpp>

class Tree;
class Board;
constexpr auto pointSize = 10;
constexpr auto edgeWidth = pointSize / 2;
constexpr auto edgeLength = pointSize * 3;
constexpr auto& pointColor = sf::Color::Yellow;
constexpr auto& edgeColor = sf::Color::Red;
constexpr auto maxEdges = 6;
constexpr auto rotation = 360.f / maxEdges;

class Light
{
public:
	Light(sf::Vector2f location, int  index);
	void draw(sf::RenderTarget& target) const;
	bool click(sf::Vector2f location, bool clock);
	void setOn();
	void setOff();
	bool getOn() const;
	void setEdges(int angle);
	sf::CircleShape getPoint() const;
	std::vector<sf::RectangleShape> getEdge() const;
	friend class Tree;
	friend class Board;

private:
	void rotate(bool clock);
	std::vector<sf::RectangleShape> m_edges;
	sf::CircleShape m_point;
	bool m_on = false;
	int m_edg;
	bool m_visited = false;
	int m_whoIm = 0;
};
