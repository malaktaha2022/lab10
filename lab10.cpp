//
//  main.cpp
//  lab10
//
//  Created by Malak Abdelhalim on 16/05/2023.
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
    
    Edge() : source(0), destination(0), weight(0) {}
};

class UndirectedWeightedGraph
{
private:
    int numberOfVertices;
    vector<vector<Edge>> adjacencyList;
public:
    UndirectedWeightedGraph(int count)
    {
        numberOfVertices = count;
        adjacencyList.resize(numberOfVertices);
    }
    
    int getNumberOfVertices() const
    {
        return numberOfVertices;
    }
    
    const vector<vector<Edge>>& getAdjacencyList() const
    {
        return adjacencyList;
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
        queue<int> vertexQueue;
        vector<bool> visited(numberOfVertices, false);

        vertexQueue.push(source);
        visited[source] = true;

        while (!vertexQueue.empty())
        {
            int currentVertex = vertexQueue.front();
            vertexQueue.pop();

            cout << currentVertex << " ";

            for (Edge edge : adjacencyList[currentVertex])
            {
                if (!visited[edge.destination])
                {
                    vertexQueue.push(edge.destination);
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
    const vector<vector<Edge>>& adjacencyList = graph.getAdjacencyList();
    for (int i = 0; i < graph.getNumberOfVertices(); i++)
    {
        cout << i << ": ";
        for (const Edge& edge : adjacencyList[i])
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
