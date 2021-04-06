#pragma once
#include <queue>

template <class T1, T2>
class Algorithm
{
	void Tree::BFS(T1& s)
	{
		std::queue<T2*> queue;
		s.m_point.m_visited = true;
		T* vertice = &s.m_point;
		queue.push(vertice);

		while (!queue.empty())
		{
			for (auto& neigh : m_lights[vertice->m_whoIm].m_neighborn)
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
};
