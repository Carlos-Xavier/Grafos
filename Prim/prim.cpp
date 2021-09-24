#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <fstream>
#include <utility>
#include <bits/stdc++.h>


#define MAX 100

using namespace std;

typedef pair<int , int> Num;
bool flags[MAX];vector <Num> adj[MAX];

  /*Selecionando arestas com pesos mínimos*/
int  primAlgorithm(int x)
{
    priority_queue<Num, vector<Num>, greater<Num> > queue;

    int y,minimumCost = 0;
    Num element;
    queue.push(make_pair(0, x));
    while(!queue.empty())
    {
    
        element = queue.top();
        queue.pop();
        x = element.second;
        if(flags[x] == true)continue;
        minimumCost+= element.first;
        flags[x] = true;
        for(int i = 0;i < adj[x].size();++i){
            y = adj[x][i].second;
            if(flags[y] == false)queue.push(adj[x][i]);
        }

    }
    return minimumCost;
}

bool readGraphByFile(string file)
{
    int i = 1;
    string line;
    ifstream myfile;
    int nv, ne, src, dist,wt;

    myfile.open(file);
    if (!myfile.is_open())
    {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    if ( myfile.is_open() ) {
        getline(myfile,line);
        stringstream ss(line);
        ss >> nv >> ne;

        while (getline(myfile, line))
        {
            stringstream ss(line);

            if (ss.str().length() > 4)
                ss >> src >> dist >> wt;
            else
            {
                ss >> src >> dist;
                wt = 1;
            }

            adj[src].push_back(make_pair(wt, dist));
            adj[dist].push_back(make_pair(wt, src));
        }
    }

    return true;
}


bool readGraph()
{
    int nv, ne, src, dist,wt, minimumCost;
    char character;
    bool flag = true;

    cout << "Insert vertices and edges: \n";
    cin >> nv >> ne;

    cout << "Do you want to include the weights? (y/n) \n";
    cin >> character;

    if (character == 'y')
    {
        cout << "Enter the pair of vertices and the weights (Example: x y w): \n";
        for(int i = 0;i < ne;++i)
        {
            cin >> src >> dist >> wt;
            adj[src].push_back(make_pair(wt, dist));
            adj[dist].push_back(make_pair(wt, src));
        }
    }
    else if (character == 'n')
    {
        cout << "Enter the pair of vertices (Example: x y): \n";
        for(int i = 0;i < ne;++i)
        {
            cin >> src >> dist;
            adj[src].push_back(make_pair(1, dist));
            adj[dist].push_back(make_pair(1, src));
        }
    }
    else
    {
        cout << "Invalid Input \n";
        flag = false;
    }

    return flag;
}


int main(int argc, char *argv[])
{
    int minimumCost;
    bool flag;

    if (argc > 1 && string(argv[1]) == "-f")
        flag = readGraphByFile(argv[2]);
    else
        flag = readGraph();
    
    if (flag)
    {
        /*Calcula o custo da AGM com o grafo de entrada "arquivo-entrada.dat" e vértice inicial 1.*/
        minimumCost = primAlgorithm(1);
        cout << "Minimum cost " << minimumCost << endl;
    }
    return 0;
}