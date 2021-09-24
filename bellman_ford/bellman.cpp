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

void readGraphByFile()
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

      if (ss.str().length() > 4)
        ss >> x >> y >> w;
      else
      {
        ss >> x >> y;
        w = 1;
      }

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
}

void readGraph()
{
    edge e[MAX];
    int nv,ne,wt,src,dest;
    char character;
    bool flag = true;

    cout << "Insert vertices and edges: \n";
    cin >> nv >> ne;

    cout << "Do you want to include the weights? (y/n) \n";
    cin >> character;

    if (character == 'y')
    {
      cout << "Enter the pair of vertices and the weights (Example: x y w): \n";
      for (int i = 0; i < ne; i++)
      {
        int x, y, w;
        cin >> x >> y >> w;

        e[i].src = static_cast<int> (x);
        e[i].dest = static_cast<int> (y);
        e[i].wt  = static_cast<int> (w);
      }
    }
    else if (character == 'n')
    {
      cout << "Enter the pair of vertices (Example: x y): \n";
      for (int i = 0; i < ne; i++)
      {
        int x, y;
        cin >> x >> y;

        e[i].src = static_cast<int> (x);
        e[i].dest = static_cast<int> (y);
        e[i].wt  = static_cast<int> (1);
      }
    }
    else
    {
        cout << "Invalid Input \n";
        flag = false;
    }

    if (flag)
    {  
      /*Analisando a distância do vertice 1 aos demais*/
      int source = 1;
      bellman_ford(nv,e,source,ne);
    }
}

int main(int argc, char *argv[])
{
  if (argc > 1 && string(argv[1]) == "-f")
    readGraphByFile();
  else
    readGraph();
  return 0;
}