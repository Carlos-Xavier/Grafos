#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>

#define MAX 30
#define INF 999
using namespace std;

typedef struct edge
{
  int src;
  int dest;
  int wt;
}edge;

void print(int nv,int dis[MAX])
{
   cout<<"\nVertice "<<"  Distancia da fonte";
  for(int i=1;i<=nv;i++)
  {
    cout<<"\n"<<i<<"\t"<<dis[i];
  }
  cout << "\n";
}

void bellman_ford(int nv,edge e[],int src,int ne)
{
  int u,v,weight;
  int dis[MAX];

  for(int i = 1;i <= nv;i++)
  {
    dis[i]= INF;
  }

  dis[src] = 0;

  for(int i = 1 ;i <= nv - 1; i++)
  {
    for(int j = 0;j < ne;j++)
    {
      u=e[j].src;
      v=e[j].dest;
      weight=e[j].wt;
    
      if(dis[u] != INF && dis[u] + weight < dis[v])
      {
        dis[v] = dis[u] + weight;
      }  
    }
    
  }
  
  for(int j=0;j < ne;j++)
  {
    u=e[j].src;
    v=e[j].dest;
    weight=e[j].wt;
    
    if(dis[u] != MAX && dis[u] + weight < dis[v])
    {
      cout << "Contém ciclo negativo";
      return;
    }  
  }
  /*Exibindo a distância do vertice 1 aos demais*/
    print(nv,dis);
}

int main()
{
  edge e[MAX];
  ifstream myfile;
  int nv,ne,wt,src,edges,dest;
  string line;
  myfile.open("input.txt");

  if ( myfile.is_open() ) {
    getline(myfile,line);
    stringstream ss(line);
    ss >> nv >> ne;
    edges = 0;
    while (getline(myfile,line))  {
      int x, y, w;
      stringstream ss(line);
      ss >> x >> y >> w;

      e[edges].src = static_cast<int> (x);
      e[edges].dest = static_cast<int> (y);
      e[edges].wt  = static_cast<int> (w);
    
      edges++;
  }

   myfile.close();
  }
  
  /*Analisando a distância do vertice 1 aos demais*/
  int source = 1;
  bellman_ford(nv,e,source,ne);
  return 0;
}