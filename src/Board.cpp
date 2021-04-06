#include "Board.h"
#include "Exception.h"
#include <queue>

void Board::printScreen()
{
	do
	{
		try
		{
			m_in.setOk();
			m_in.setSize();
		}
		catch (Exception & e)
		{
			e.show();
		}
		catch (std::ios_base::failure  e)
		{
			std::cout << e.what() << std::endl;
			std::cin.clear();
			std::cin.seekg(0);
		}
		catch (...)
		{
			std::cin.clear();
			std::cin.seekg(0);
		}
	}
	while (!m_in.getOk());
	Tree m_graph(m_in);
	
	auto window = sf::RenderWindow(sf::VideoMode(screenSize, screenSize), "Game");	
	
	racordingTheLigthByBfs(m_graph);
	while (window.isOpen())
	{
		window.clear();
		for (const auto& l : m_graph.getLights())
			l->m_point->draw(window);
		window.display();

		finishGame(m_graph, window);

		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				const auto location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					for (auto& l : m_graph.getLights())
						if(l->m_point->click(location, true))
							racordingTheLigthByBfs(m_graph);
					break;
				case sf::Mouse::Button::Right:
					for (auto& l : m_graph.getLights())
						if (l->m_point->click(location, false))
							racordingTheLigthByBfs(m_graph);
					break;
				}
			}
		}
	}
}

void Board::racordingTheLigthByBfs(Tree& m_graph)
{
	for (auto& i : m_graph.getLights())
	{
		i->m_point->m_visited = false;
		i->m_point->setOff();
	}
	std::queue<std::shared_ptr<Light>> queue;
	m_graph.getLights()[0]->m_point->m_visited = true;
	m_graph.getLights()[0]->m_point->setOn();
	//auto l = m_graph.getLights()[0]->m_point;
	std::shared_ptr<Light> vertice = m_graph.getLights()[0]->m_point;
	queue.push(vertice);

	while (!queue.empty())
	{
		for (auto& neigh : m_graph.getLights()[vertice->m_whoIm]->m_neighborn)
			if (!neigh->m_visited)				
				if (isConnected(vertice, neigh))
				{
					neigh->m_visited = true;
					queue.push(neigh);
				}
		queue.pop();
		if (queue.empty())
			break;
		vertice = queue.front();
	}
}

void Board::finishGame(Tree& m_graph, sf::RenderWindow& window)
{
	if (m_conected == m_graph.getLights().size()) // checking if the game is ended
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));
		window.close();
		char choice;
		std::cout << "You won\n";
		bool on = true;
		std::cin.exceptions(std::ios::failbit | std::ios::badbit);			
		std::cout << "If do you want to continue to play press 'y', if not press other key to finish the game\n";
		std::cin >> choice;		
	
		if (choice == 'y')
		{
			m_graph.clear();
			m_in.clearLight();
			m_conected = 1;
			printScreen();
		}
		else
			exit(0);
	}
	else
		m_conected = 1;
}

bool Board::isConnected(std::shared_ptr<Light> vertice, std::shared_ptr<Light> neigh)
{
	for (auto& i : vertice->getEdge())
		for (auto& j : neigh->getEdge())
			if (i.getGlobalBounds().intersects(j.getGlobalBounds()))
			{
				neigh->setOn();
				m_conected++;
				return true;
			}
	return false;
}