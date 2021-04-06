#include "Light.h"
#include <time.h>

Light::Light(sf::Vector2f location, int  index) : m_point(pointSize), m_whoIm(index)
{
	m_point.setOrigin(m_point.getRadius(), m_point.getRadius());
	m_point.setPosition(location);
	m_point.setFillColor(sf::Color(128, 128, 128));
}

void Light::draw(sf::RenderTarget& target) const
{
	target.draw(m_point);
	for (const auto& e : m_edges)
		target.draw(e);
}

bool Light::click(sf::Vector2f location, bool clock)
{
	if (m_point.getGlobalBounds().contains(location))
	{
		rotate(clock);
		return true;
	}
	return false;
}

void Light::setOn()
{
	m_on = true;
	m_point.setFillColor(pointColor);
}

void Light::setOff()
{
	m_on = false;
	m_point.setFillColor(sf::Color(128, 128, 128));
}

bool Light::getOn() const
{
	return m_on;
}

void Light::setEdges(int angle)
{
	m_edges.push_back(sf::RectangleShape({ edgeWidth, edgeLength+1 }));
	auto& e = m_edges.back();
	e.setFillColor(edgeColor);
	e.setOrigin(e.getSize().x / 2, -m_point.getRadius());
	e.setPosition(m_point.getPosition());
	e.setRotation(rotation * angle + 30);	
}

sf::CircleShape Light::getPoint() const
{
	return m_point;
}

std::vector<sf::RectangleShape> Light::getEdge() const
{
	return m_edges;
}

void Light::rotate(bool clock)
{
	for (auto& e : m_edges)
	{
		if (clock)
			e.rotate(rotation);
		else
			e.rotate(-rotation);
	}
}
