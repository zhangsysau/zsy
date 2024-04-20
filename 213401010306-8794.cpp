#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define OK 1
#define ERROR 0
#define MAX_NAME 20
#define MAXCLASS 100
#define MAX_VERTEX_NUM 100//��󶥵���
#define STACK_INIT_SIZE 10//ջ��ʼ����С 
typedef int SElemType;//ջԪ������ 
typedef int Status;
typedef int InfoType;
typedef char VertexType[MAX_NAME];
typedef int pathone[MAXCLASS];
typedef struct ArcNode
{
 int adjvex;//�ñ���ָ��Ķ���λ�� 
 struct ArcNode *nextarc;//ָ����һ���ߵ�ָ�� 
} ArcNode;
typedef struct VNode
{
 VertexType data;//������Ϣ
 ArcNode *firstarc;//ָ���һ�������ö���ıߵ�ָ��
} VNode,AdjList[MAX_VERTEX_NUM];//AdjList��ʾ�ڽӱ����� 
typedef struct
{
 AdjList vertices;//�ڽӱ� 
 int vexnum,arcnum;//ͼ�ĵ�ǰ�������ͱ��� 
} ALGraph;
int LocateVex(ALGraph G,VertexType u)//ȷ����u��G�е�λ�� 
{
 int i;
 for(i=0; i<G.vexnum; ++i)
  if(strcmp(u,G.vertices[i].data)==0)
   return i;
 return -1;
}
//��������ͼG���ڽӱ�
Status CreateGraph(ALGraph &G)
{
 int i,j;
 VertexType va,vb;//��ͷ����β 
 printf(" �������ѧ�ƻ��Ŀγ��� : ");
 scanf("%d",&G.vexnum);
 printf(" �����������������γɵĿγ����޹�ϵ�ı��� : ");
 scanf("%d",&G.arcnum);
 printf(" ����%d ���γ̵�����:\n",G.vexnum);
 for(int i=0; i<G.vexnum; ++i)
  {
   ap:scanf("%s",G.vertices[i].data);
   while(strlen(G.vertices[i].data)>MAX_NAME)
   {
   	printf("����������������룡"); 
   	goto ap;
   } 
   G.vertices[i].firstarc=NULL;
  }//forѭ��������֪�γ���Ϣ�����ƣ�
 printf(" \n��˳������ÿ�����Ļ�β�ͻ�ͷ (�Կո���Ϊ�������β��ʾ��ͷ����Ӧ�����޿γ�) :\n");
 for(int k=0; k<G.arcnum; ++k)
  {
   scanf("%s%s",va,vb);
   i=LocateVex(G,va);//ȷ��������G.vertices�е���� 
   j=LocateVex(G,vb);//ȷ��������G.vertices�е���� 
  ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));//����һ���µı߽��p
   p->adjvex=j;//�ڽӵ����Ϊj 
   p->nextarc=G.vertices[i].firstarc;
   G.vertices[i].firstarc=p;//���½��p���붥�������ͷ����ͷ�壩
  }
  printf("\n");
 return OK;
}
void FindInDegree(ALGraph G,int indegree[])//FindInDegree����� 
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
typedef struct SqStack//ջ����ز��� 
{
 SElemType *base;
 SElemType *top;
 int stacksize;
} SqStack;
Status InitStack(SqStack &S)//��ʼ��ջ 
{
 S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
 if(!S.base)
  exit(OVERFLOW);
 S.top=S.base;
 S.stacksize=STACK_INIT_SIZE;
 return OK;
}
Status StackEmpty(SqStack S)//�ж�ջ�� 
{
 if(S.top==S.base)
  return OK;
 else
  return ERROR;
}
Status Pop(SqStack &S,SElemType &e)//��ջ
{
 if(S.top==S.base)
  return ERROR;
 e=*--S.top;
 return OK;
}
Status Push(SqStack &S,SElemType e)//��ջ 
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
Status TopologicalSort(ALGraph G)//�������� 
{
 int i,k,q=1,j=0,count,indegree[MAX_VERTEX_NUM];
 //q��ʾʵ�ʿγ�������ʵ�ʿγ�������������ʱ�����ÿγ̱�� 
 SqStack S;
 pathone a;
 ArcNode *p;
 FindInDegree(G,indegree);
 InitStack(S);//ջ��ʼ��Ϊ��
 for(i=0; i<G.vexnum; ++i)
  if(!indegree[i])//���Ϊ�����ջ
   Push(S,i);
 count=0;//ͳ������������Ԫ�ظ��� 
 while(!StackEmpty(S))//ջS�ǿ�
  {
   Pop(S,i);//��ջ������i��ջ 
   a[i]=*G.vertices[i].data;
   if(q<=G.vexnum )
    {
    	printf("�γ�%dΪ: %s\n",q,G.vertices[i].data);
     q++;
    }
   else
    {
    	printf("*** �γ�%s\n",G.vertices[i].data);
    }
   ++count;
   for(p=G.vertices[i].firstarc; p; p=p->nextarc)
    {
     k=p->adjvex;//kΪi���ڽӵ� 
     if(!(--indegree[k]))//i��ÿ���ڽӵ���ȼ�һΪ�� 
	  Push(S,k);//��ջ 
    }
  }
 if(count<G.vexnum)
  {
   printf("������������ͼ�л�· \n");
   return ERROR;
  }
 else
  {
   printf(" Ϊһ���������У��γ̱��ź���\n");
  }
 return 0;
}
int main()
{
 ALGraph f;
 printf(" ����Ϊ��ѧ�γ������������ :\n");
 //CreateGraph(f);
 while(CreateGraph(f))
 {
 	TopologicalSort(f);
  } 
 
}
