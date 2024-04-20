#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define OK 1
#define ERROR 0
#define MAX_NAME 20
#define MAXCLASS 100
#define MAX_VERTEX_NUM 100//最大顶点数
#define STACK_INIT_SIZE 10//栈初始化大小 
typedef int SElemType;//栈元素类型 
typedef int Status;
typedef int InfoType;
typedef char VertexType[MAX_NAME];
typedef int pathone[MAXCLASS];
typedef struct ArcNode
{
 int adjvex;//该边所指向的顶点位置 
 struct ArcNode *nextarc;//指向下一条边的指针 
} ArcNode;
typedef struct VNode
{
 VertexType data;//顶点信息
 ArcNode *firstarc;//指向第一条依附该顶点的边的指针
} VNode,AdjList[MAX_VERTEX_NUM];//AdjList表示邻接表类型 
typedef struct
{
 AdjList vertices;//邻接表 
 int vexnum,arcnum;//图的当前顶点数和边数 
} ALGraph;
int LocateVex(ALGraph G,VertexType u)//确定点u在G中的位置 
{
 int i;
 for(i=0; i<G.vexnum; ++i)
  if(strcmp(u,G.vertices[i].data)==0)
   return i;
 return -1;
}
//创建有向图G的邻接表
Status CreateGraph(ALGraph &G)
{
 int i,j;
 VertexType va,vb;//弧头，弧尾 
 printf(" 请输入教学计划的课程数 : ");
 scanf("%d",&G.vexnum);
 printf(" 请输入拓扑排序所形成的课程先修关系的边数 : ");
 scanf("%d",&G.arcnum);
 printf(" 输入%d 个课程的名称:\n",G.vexnum);
 for(int i=0; i<G.vexnum; ++i)
  {
   ap:scanf("%s",G.vertices[i].data);
   while(strlen(G.vertices[i].data)>MAX_NAME)
   {
   	printf("输入错误，请重新输入！"); 
   	goto ap;
   } 
   G.vertices[i].firstarc=NULL;
  }//for循环输入已知课程信息（名称）
 printf(" \n请顺序输入每条弧的弧尾和弧头 (以空格作为间隔，弧尾表示弧头所对应的先修课程) :\n");
 for(int k=0; k<G.arcnum; ++k)
  {
   scanf("%s%s",va,vb);
   i=LocateVex(G,va);//确定顶点在G.vertices中的序号 
   j=LocateVex(G,vb);//确定顶点在G.vertices中的序号 
  ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));//生成一个新的边结点p
   p->adjvex=j;//邻接点序号为j 
   p->nextarc=G.vertices[i].firstarc;
   G.vertices[i].firstarc=p;//将新结点p插入顶点的链接头部（头插）
  }
  printf("\n");
 return OK;
}
void FindInDegree(ALGraph G,int indegree[])//FindInDegree找入度 
{
 int i;
 ArcNode *p;
 for(i=0; i<G.vexnum; i++)
  indegree[i]=0;
 for(i=0; i<G.vexnum; i++)
  {
   p=G.vertices[i].firstarc;
   while(p)
    {
     indegree[p->adjvex]++;
     p=p->nextarc;
    }
  }
}
typedef struct SqStack//栈的相关操作 
{
 SElemType *base;
 SElemType *top;
 int stacksize;
} SqStack;
Status InitStack(SqStack &S)//初始化栈 
{
 S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
 if(!S.base)
  exit(OVERFLOW);
 S.top=S.base;
 S.stacksize=STACK_INIT_SIZE;
 return OK;
}
Status StackEmpty(SqStack S)//判断栈空 
{
 if(S.top==S.base)
  return OK;
 else
  return ERROR;
}
Status Pop(SqStack &S,SElemType &e)//出栈
{
 if(S.top==S.base)
  return ERROR;
 e=*--S.top;
 return OK;
}
Status Push(SqStack &S,SElemType e)//入栈 
{
 if(S.top-S.base>=S.stacksize)
  {
   if(!S.base)
    exit(OVERFLOW);
   S.top=S.base+S.stacksize;
  }
 *(S.top)++=e;
 return OK;
}
Status TopologicalSort(ALGraph G)//拓扑排序 
{
 int i,k,q=1,j=0,count,indegree[MAX_VERTEX_NUM];
 //q表示实际课程数，当实际课程数超过顶点数时，将该课程标记 
 SqStack S;
 pathone a;
 ArcNode *p;
 FindInDegree(G,indegree);
 InitStack(S);//栈初始化为空
 for(i=0; i<G.vexnum; ++i)
  if(!indegree[i])//入度为零则进栈
   Push(S,i);
 count=0;//统计拓扑序列中元素个数 
 while(!StackEmpty(S))//栈S非空
  {
   Pop(S,i);//将栈顶顶点i出栈 
   a[i]=*G.vertices[i].data;
   if(q<=G.vexnum )
    {
    	printf("课程%d为: %s\n",q,G.vertices[i].data);
     q++;
    }
   else
    {
    	printf("*** 课程%s\n",G.vertices[i].data);
    }
   ++count;
   for(p=G.vertices[i].firstarc; p; p=p->nextarc)
    {
     k=p->adjvex;//k为i的邻接点 
     if(!(--indegree[k]))//i的每个邻接点入度减一为零 
	  Push(S,k);//入栈 
    }
  }
 if(count<G.vexnum)
  {
   printf("不合理，此有向图有回路 \n");
   return ERROR;
  }
 else
  {
   printf(" 为一个拓扑序列，课程编排合理\n");
  }
 return 0;
}
int main()
{
 ALGraph f;
 printf(" 以下为大学课程排序的求解过程 :\n");
 //CreateGraph(f);
 while(CreateGraph(f))
 {
 	TopologicalSort(f);
  } 
 
}
