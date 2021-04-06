#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Light.h"
#include <iostream>
#include <memory>
#include "In.h"
#include "Tree.h"
#include <thread>         
#include <chrono>        

class Board
{
private:
	In m_in;
	std::vector<sf::Vector2f> m_position;
	int m_conected = 1;
public:
	bool isConnected(std::shared_ptr<Light> vertice, std::shared_ptr<Light> neigh);
	Board() = default;
	~Board() = default;
	void printScreen();	
	void racordingTheLigthByBfs(Tree& m_graph);
	void finishGame(Tree& m_graph, sf::RenderWindow& window);
};
