//
// lab10.cpp
//
//
// created by Malak Abdelhalim on 16/05/2023
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct Edge
{
	int source;
	int destination;
	int weight;
};

class UndirectedWeightedGraph
{
private:
	int numberOfVertices;
	vector<vector<Edge>> adjacencyList;

public:
	int numberOfVertices;
	UndirectedWeightedGraph(int count)
	{
		numberOfVertices = count;
		adjacencyList.resize(numberOfVertices);
	}

	void addEdge(int source, int destination, int weight)
	{
		Edge edge;
		edge.source = source;
		edge.destination = destination;
		edge.weight = weight;
		adjacencyList[source].push_back(edge);
		adjacencyList[destination].push_back(edge);
	}

	void BFS(int source)
	{
		queue<int> queue;
		vector<bool> visited(numberOfVertices, false);

		queue.push(source);
		visited[source] = true;

		while (!queue.empty())
		{
			int currentVertex = queue.front();
			queue.pop();

			cout << currentVertex << " ";

			for (Edge edge : adjacencyList[currentVertex])
			{
				if (!visited[edge.destination])
				{
					queue.push(edge.destination);
					visited[edge.destination] = true;
				}
			}
		}

		cout << endl;
	}

	void DFS(int source)
	{
		vector<bool> visited(numberOfVertices, false);

		DFSRec(source, visited);
	}

	void DFSRec(int vertex, vector<bool>& visited)
	{
		visited[vertex] = true;

		cout << vertex << " ";

		for (Edge edge : adjacencyList[vertex])
		{
			if (!visited[edge.destination])
			{
				DFSRec(edge.destination, visited);
			}
		}
	}
};

int main()
{
  UndirectedWeightedGraph graph(10);
  int source, destination, weight;
  ifstream input("Board.txt");
  string s;

	while (getline(input, s))
	{
		stringstream ss(s);
		ss >> source >> destination >> weight;
		graph.addEdge(source, destination, weight);
	}

	cout << "The graph:" << endl;
	for (int i = 0; i < graph.numberOfVertices; i++)
	{
		cout << i << ": ";
		for (Edge edge : graph.adjacencyList[i])
		{
			cout << edge.destination << " ";
		}
		cout << endl;
	}

	cout << "Breadth-first search:" << endl;
	graph.BFS(0);

	cout << "Depth-first search:" << endl;
	graph.DFS(0);

	return 0;
}
