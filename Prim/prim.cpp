#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
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

int main()
{
    int nv, ne, src, dist,wt, minimumCost;
    cin >> nv >> ne;
    for(int i = 0;i < ne;++i)
    {
        cin >> src >> dist >> wt;
        adj[src].push_back(make_pair(wt, dist));
        adj[dist].push_back(make_pair(wt, src));
    }
    /*Calcula o custo da AGM com o grafo de entrada "arquivo-entrada.dat" e vértice inicial 1.*/
    minimumCost = primAlgorithm(1);
    cout << "Custo minimo " << minimumCost << endl;
    return 0;
}