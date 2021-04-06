#include "In.h"
#include <iostream>
#include "Exception.h"

void In::setSize()
{
	std::cout << "Enter a size of your game : " << std::endl;
	std::cin.exceptions(std::ios::failbit | std::ios::badbit);
	std::cin >> m_size;
	if (m_size == 1)
		throw Exception("It's too small");
	if(m_size % 2 != 1)
		throw Exception("you cannot enter an odd number");
	isOk = true;
	initLights();
}

void In::initLights()
{
	if (m_size == 3)
		m_lights = 7;
	else
	{
		for (int i = m_size - 1; i >= 3; i--)		
			m_lights += 2 * i;
		m_lights += m_size;
	}
}

int In::getLights() const
{
	return m_lights;
}

int In::getSize() const
{
	return m_size;
}
