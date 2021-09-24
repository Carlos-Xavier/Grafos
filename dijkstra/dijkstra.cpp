#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> Edge;

class Graph
{
    public:
        vector <Edge> graph_adj[6];
        int vertices = 0;

        Graph(int size)
        {
            this->vertices = size;
        }

        void Add(int x, int y, int weight)
        {

            graph_adj[x].push_back(make_pair(y, weight));
        }
};

void dijkstra(Graph graph, int vertices)
{
	priority_queue <Edge, vector<Edge>, greater<Edge>> pq;

	cout << "Starting with V0 = 0\n";
	int node = 0;

	vector <int> parents(vertices, -1);
	vector <int> cost(vertices, INT32_MAX);
	vector <bool> visited(vertices, false);

	pq.push(make_pair(0, node));
	cost[node] = 0;

	while(!pq.empty())
	{
		int v =  pq.top().second;
		pq.pop();

		visited[v] = true;

		for(auto item: graph.graph_adj[v])
		{
			int u = item.first;
			int wt = item.second;
			if(visited[u] == false && cost[u] > cost[v] + wt)
			{
				cost[u] = cost[v] + wt; // dijkstra 
				pq.push(make_pair(cost[u], u));
				parents[u] = v;
			}
		}
	}
	
	cout << "Dijkstra tree:\n";
	for (int i = 1; i < vertices; ++i) 
        cout << parents[i] << " -> " << i << '\n';
}

Graph set_graph(string s)
{
    int vertex, edges;
    stringstream ss(s);
    ss >> vertex >> edges;

    Graph graph(vertex);
    return graph;
}

void mount_graph(Graph &graph, string s)
{
    int x, y, w;
    stringstream ss(s);

    if (ss.str().length() > 4)
        ss >> x >> y >> w;
    else
    {
        ss >> x >> y;
        w = 1;
    }

    graph.Add(x, y, w);
}

bool readGraphByFile(Graph &graph, string file)
{
    int i = 1;
    string line;
    ifstream myfile;

    myfile.open(file);
    if (!myfile.is_open())
    {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    while (getline(myfile, line))
    {
        if (i == 1)
            graph = set_graph(line);
        else
            mount_graph(graph, line);
        i++;
    }

    return true;
}

bool readGraph(Graph &graph)
{
    int vertex, edges;
    char character;

    cout << "Insert vertices and edges: \n";
    cin >> vertex >> edges;

    Graph graphTemp(vertex);

    cout << "Do you want to include the weights? (y/n) \n";
    cin >> character;

    if (character == 'y')
    {
        cout << "Enter the pair of vertices and the weights (Example: x y w): \n";
        for (int i = 0; i < edges; i++)
        {
            int x, y, w;

            cin >> x >> y >> w;

            graphTemp.Add(x, y, w);
        }
    }
    else if (character == 'n')
    {
        cout << "Enter the pair of vertices (Example: x y): \n";
        for (int i = 0; i < edges; i++)
        {
            int x, y;

            cin >> x >> y;

            graphTemp.Add(x, y, 1);
        }
    }
    else
    {
        cout << "Invalid Input \n";
        return false;
    }

    graph = graphTemp;
    return true;
}

int main(int argc, char *argv[])
{
    Graph graph(1);
    bool flag;

    if (argc > 1 && string(argv[1]) == "-f")
        flag = readGraphByFile(graph, argv[2]);
    else
        flag = readGraph(graph);

    if (flag)
        dijkstra(graph, graph.vertices);

    return 0;
}