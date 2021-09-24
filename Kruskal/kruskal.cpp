#include <iostream>
#include <vector>
#include <algorithm> 
#include <string.h> 
using namespace std;

class Edge
{
	int vertex1, vertex2, weight;

public:

	Edge(int v1, int v2, int weight)
	{
		vertex1 = v1;
		vertex2 = v2;
		this->weight = weight;
	}

	int getVertex1()
	{
		return vertex1;
	}

	int getVertex2()
	{
		return vertex2;
	}

	int getWeight()
	{
		return weight;
	}

	bool operator < (const Edge& aresta2) const
	{
		return (weight < aresta2.weight);
	}
};

class Grafo
{
	int V; 
	vector<Edge> edges; 

public:

	Grafo(int V)
	{
		this->V = V;
	}
    
	void addEdge(int v1, int v2, int weight)
	{
		Edge edge(v1, v2, weight);
		edges.push_back(edge);
	}

	// função que busca o subconjunto de um elemento "i"
	int search(int subset[], int i)
	{
		if(subset[i] == -1)
			return i;
		return search(subset, subset[i]);
	}

	// função para join dois subconjuntos em um único subconjunto
	void join(int subset[], int v1, int v2)
	{
		int v1_set = search(subset, v1);
		int v2_set = search(subset, v2);
		subset[v1_set] = v2_set;
	}

    void showTree(int s_arvore,vector<Edge> tree)
    {
        for(int i = 0; i < s_arvore; i++)
		{
			char v1 = 'A' + tree[i].getVertex1();
			char v2 = 'A' + tree[i].getVertex2();
			cout << "(" << v1 << ", " << v2 << ") = " << tree[i].getWeight() << endl;
		}
    }

	/// função que roda o algoritmo de Kruskal
	void kruskal()
	{
		vector<Edge> tree;
		int size_arestas = edges.size();

		// ordena as edges pelo menor weight
		sort(edges.begin(), edges.end());


		int * subset = new int[V];

		memset(subset, -1, sizeof(int) * V);

		for(int i = 0; i < size_arestas; i++)
		{
			int v1 = search(subset, edges[i].getVertex1());
			int v2 = search(subset, edges[i].getVertex2());

			if(v1 != v2)
			{
				tree.push_back(edges[i]);
				join(subset, v1, v2); 
			}
		}
        showTree(tree.size(),tree);

	}
};

int main(int argc, char *argv[])
{
	Grafo g(5); // grafo
	
	// adiciona as edges
	g.addEdge(0, 1, 2);
	g.addEdge(1, 2, 3);
	g.addEdge(1, 4, 5);
	g.addEdge(2, 4, 7);
	g.addEdge(0, 3, 6);
    g.addEdge(2, 4, 7);
	g.addEdge(1, 3, 8);
    g.addEdge(3, 4, 9);
	
	g.kruskal(); // roda o algoritmo de Kruskal
	
	return 0;
}