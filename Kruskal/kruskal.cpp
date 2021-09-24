#include <iostream>
#include <vector>
#include <algorithm> 
#include <string.h> 
#include <fstream>
#include <bits/stdc++.h>
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

class Graph
{
	int V; 
	vector<Edge> edges; 

public:

	Graph(int V)
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

bool readGraphByFile(Graph &graph, string file)
{
    string line;
    ifstream myfile;

    myfile.open(file);
    if (!myfile.is_open())
    {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
	if ( myfile.is_open() ) 
    {
		int nv,ne;
        getline(myfile,line);
        stringstream ss(line);
        ss >> nv >> ne;

		Graph graph_temp(nv);

		while (getline(myfile, line))
		{
			int x, y, w;
            stringstream ss(line);

            if (ss.str().length() > 4)
                ss >> x >> y >> w;
            else
            {
                ss >> x >> y;
                w = 1;
            }
			graph_temp.addEdge(x, y, w);
		}
		graph = graph_temp;
	}

    return true;
}

bool readGraph(Graph &graph)
{
	int nv,ne;
	char character;

	cout << "Insert vertices and edges: \n";
	cin >> nv >> ne;

	Graph graph_temp(nv);

	cout << "Do you want to include the weights? (y/n) \n";
    cin >> character;

	if (character == 'y')
    {
        cout << "Enter the pair of vertices and the weights (Example: x y w): \n";
		for (int i = 0; i < ne; i++)
		{
			int x, y, w;

            cin >> x >> y >> w;

            graph_temp.addEdge(x, y, w);
		}
    }
    else if (character == 'n')
    {
        cout << "Enter the pair of vertices (Example: x y): \n";
        for (int i = 0; i < ne; i++)
		{
			int x, y;

            cin >> x >> y;

            graph_temp.addEdge(x, y, 1);
		}
    }
    else
    {
        cout << "Invalid Input \n";
        return false;
    }

	graph = graph_temp;
	return true;
}

int main(int argc, char *argv[])
{
	Graph graph(1); // grafo
	bool flag;

	if (argc > 1 && string(argv[1]) == "-f")
		flag = readGraphByFile(graph, argv[2]);
	else
		flag = readGraph(graph);
	

	if (flag)
		graph.kruskal(); // roda o algoritmo de Kruskal
	
	return 0;
}