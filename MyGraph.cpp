#include<iostream>
#include<stack>
using namespace std;

/*ADT 图(Graph)
Data
  顶点的有穷非空集合和边的集合
Operation
  CreateGraph(*G,V,VR);  构造
  DestroyGraph;          销毁
  LocateVex(G,u);        返回顶点u的位置
  GetVex(G,v);           返回图G中顶点v的位置
  PutVex(G,v,value);     将图中顶点v赋值为value
  FirstAdjVex(G,*v);     返回顶点v的一个邻接顶点，若顶点在G中无邻接顶点则返回空
  NextAdjVex(G,v,*w);    返回顶点v相对于顶点w的下一个邻接顶点
  InsertVex(*G,v);       在图中新添顶点v
  DeleteVex(*G,v);       删除图中顶点v以及相关的弧
  InsertArc(*G,v,w);     在图G中增添弧<v,w>，若G是无向图，还需要增添对称弧<w,v>
  DeleteArc(*G,v,w);     在图G中删除弧<v,w>，若G是无向图，则还删除对称弧<w,v>。
  DFS(G);                对图G中进行深度优先遍历，在遍历过程对每个顶点调用。
  HFS(G);                对图G中进行广度优先遍历，在遍历过程对每个顶点调用。
*/

//1. 图的存储结构
//(1)邻接矩阵
#define MAXVEX 100
#define INFINITY 65535
struct MyGraph{
  char vexs[MAXVEX];
  int arc[MAXVEX][MAXVEX];
  int numVex,numEdge;
};

/*构建图*/
void CreateMtGraph(MyGraph *G){
  cout<<"请输入顶点个数以及边的个数"<<endl;
  cin>>G->numVex>>G->numEdge;
  for(int i=0;i<G->numVex;i++){
    cin>>G->vexs[i];
  }
  for(int i=0;i<G->numEdge;i++){
    for(int j=0;j<G->numEdge;j++){
      G->arc[i][j]=INFINITY;
    }
  }

  int i,j,w;
  for(int k=0;k<G->numEdge;k++){
    cin>>i>>j>>w;
    G->arc[i][j]=w;

    G->arc[j][i]=G->arc[i][j];
  }
}



//(2)邻接表
struct EdgeNode{
  int adjvex;
  int weight;
  struct EdgeNode *next;
};

struct VertexNode{
  int data;
  EdgeNode *firstedge;
};
struct GraphAdjList{
  VertexNode adjList[MAXVEX];
  int numVex,numEdge;
};

/*构建图的邻接表结构*/
void CreatGraph2(GraphAdjList* G){
  cout<<"输入顶点数以及边的个数"<<endl;
  cin>>G->numVex>>G->numEdge;
  for(int i=0;i<G->numVex;i++){
    cin>>G->adjList[i].data;
    G->adjList[i].firstedge=NULL;
  }
  int i,j;
  for(int k=0;k<G->numEdge;k++){
    cout<<"输入边上的顶点序号"<<endl;
    EdgeNode *e=new EdgeNode;
    cin>>i>>j;
    e->adjvex=j;
    e->next=G->adjList[i].firstedge;
    G->adjList[i].firstedge=e;
    e=new EdgeNode;
    e->adjvex=i;
    e->next=G->adjList[j].firstedge;
    G->adjList[j].firstedge=e;
  }
}

//2.遍历操作
//（1）深度优先遍历
//a.邻接矩阵版本
int visited[MAXVEX]={0};
//* 递归版本：DFS递归算法
void DFS1(MyGraph G,int v){
  if(G.numVex==0||v<0||v>=G.numVex){
    return;
  }
  cout<<v;
  visited[v]=1;
  for(int i=0;i<G.numVex;i++){
    if((G.arc[v][i]!=0)&&(!visited[i]))
      DFS1(G,i);
  }
}
//DFS递归操作
void DFS1(MyGraph G){
  for(int i=0;i<G.numVex;i++){
    visited[i]=0;
  }

  for(int i=0;i<G.numVex;i++){
    if(!visited[i]){
      DFS1(G,i);
    }
  }
}

//* 非递归：非递归算法（需要用到栈）
void DFS2(MyGraph G,int v){
  stack<int> Node;
  Node.push(v);
  
  while(!Node.empty()){
    int u=Node.top();
    Node.pop();

    if(visited[u]) continue;;
    visited[u]=1;
    cout<<u<<" ";
    for(int k=G.numVex-1;k>=0;--k){
      if(G.arc[u][k]&&!visited[k]){
        Node.push(k);
      }
    }

  }
}

//(2)
