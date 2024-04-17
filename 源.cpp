#include<iostream>
#include<string>
#include<stdio.h>
#include<string.h>
#include<fstream>
using namespace std;
#define MAX 99999
#define maxsize 200
typedef int Distance[maxsize][maxsize];//��̾������
typedef int Path[maxsize][maxsize];//���·��
typedef float Time[maxsize][maxsize];//���ʱ�����
//������Ŵ�1��ʼ���ڶ����������±��0��ʼ
typedef struct Node {
	string name;//��������
	int num;//�������
}Node;//����ṹ��
typedef struct Graph{
	Node vexs[maxsize];//��������
	int Darcs[maxsize][maxsize];//·�̵��ڽӾ���
	float Tarcs[maxsize][maxsize];//ʱ����ڽӾ���
	int vexCount, arcCount;//��ǰ�������ͱ���
}Graph;//ͼ
void Mune()//�˵�����
{
	cout << "**********************************************" << endl;
	cout << "-------****��ӭʹ��У԰��ͨ��ѯϵͳ****-------" << endl;
	cout << "                 || �˵��� ||                 " << endl;
	cout << "----------------------------------------------" << endl;
	cout << "*     | 1,������Ϣ����Ӧ���н�ʱ���·�� |   *" << endl;
	cout << "*     |        2,��ӽ�����Ϣ            |   *" << endl;
	cout << "*     |        3,ɾ��������Ϣ            |   *" << endl;
	cout << "*     |        4,�޸Ľ�����Ϣ            |   *" << endl;
	cout << "*     |    5����ѯ���·�������ʱ��     |   *" << endl;
	cout << "*     |          0,�˳�ϵͳ              |   *" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "**********************************************" << endl;
}
void Init(Graph& G)//��ʼ����ͼ
{
	G.vexs[0].name = "ͼ���"; G.vexs[1].name = "����";
	G.vexs[2].name = "�������"; G.vexs[3].name = "�ݷ��";
	G.vexs[4].name = "����ѵ������"; G.vexs[5].name = "�����ںϴ�¥";
	G.vexs[6].name = "���������"; G.vexs[7].name = "������";
	G.vexs[8].name = "����������"; G.vexs[9].name = "��ѧ�������";
	G.vexs[10].name = "����糡"; G.vexs[11].name = "��ѧ¥C��";
	G.vexs[12].name = "��ѧ¥B��"; G.vexs[13].name = "��ѧ¥A��";
	G.vexs[14].name = "����ʳ��"; G.vexs[15].name = "��������";
	G.vexs[16].name = "��������"; G.vexs[17].name = "��������";
	G.vexs[18].name = "����ʳ��"; G.vexs[19].name = "����";
	G.vexs[20].name = "��������";
	G.vexCount = 21; G.arcCount = 29;
	for (int i = 0; i < G.vexCount; i++)
	{
		G.vexs[i].num = i + 1;
	}
	for (int i = 0; i < G.arcCount; i++)
	{
		for (int j = 0; j < G.arcCount; j++)
		{
			if (i == j)
			{
				G.Darcs[i][j] = G.Darcs[j][i] = 0;
				G.Tarcs[i][j] = G.Tarcs[j][i] = 0;
			}
			else
			{
				G.Darcs[i][j] = G.Darcs[j][i] = MAX;
				G.Tarcs[i][j] = G.Tarcs[j][i] = MAX;
			}
		}
	}
	G.Darcs[0][1] = G.Darcs[1][0] = 600; G.Tarcs[0][1] = G.Tarcs[1][0] = 6;
	G.Darcs[0][2] = G.Darcs[2][0] = 180; G.Tarcs[0][2] = G.Tarcs[2][0] = 1.8;
	G.Darcs[0][3] = G.Darcs[3][0] = 390; G.Tarcs[0][2] = G.Tarcs[2][0] = 3.9;
	G.Darcs[0][4] = G.Darcs[4][0] = 250; G.Tarcs[0][4] = G.Tarcs[4][0] = 2.5;
	G.Darcs[0][5] = G.Darcs[5][0] = 300; G.Tarcs[0][5] = G.Tarcs[5][0] = 3;
	G.Darcs[0][6] = G.Darcs[6][0] = 150; G.Tarcs[0][6] = G.Tarcs[6][0] = 1.5;
	G.Darcs[0][7] = G.Darcs[7][0] = 200; G.Tarcs[0][7] = G.Tarcs[7][0] = 2;
	G.Darcs[0][11] = G.Darcs[11][0] = 190; G.Tarcs[0][11] = G.Tarcs[11][0] = 1.9;
	G.Darcs[1][2] = G.Darcs[2][1] = 430; G.Tarcs[1][2] = G.Tarcs[2][1] = 4.3;
	G.Darcs[1][13] = G.Darcs[13][1] = 400; G.Tarcs[1][13] = G.Tarcs[13][1] = 4;
	G.Darcs[2][3] = G.Darcs[3][2] = 290; G.Tarcs[2][3] = G.Tarcs[3][2] = 2.9;
	G.Darcs[3][4] = G.Darcs[4][3] = 160; G.Tarcs[3][4] = G.Tarcs[4][3] = 1.6;
	G.Darcs[4][5] = G.Darcs[5][4] = 80; G.Tarcs[4][5] = G.Tarcs[5][4] = 0.8;
	G.Darcs[5][6] = G.Darcs[6][5] = 280; G.Tarcs[5][6] = G.Tarcs[6][5] = 2.8;
	G.Darcs[6][7] = G.Darcs[7][6] = 70; G.Tarcs[6][7] = G.Tarcs[7][6] = 0.7;
	G.Darcs[7][8] = G.Darcs[8][7] = 150; G.Tarcs[7][8] = G.Tarcs[8][7] = 1.5;
	G.Darcs[8][9] = G.Darcs[9][8] = 150; G.Tarcs[8][9] = G.Tarcs[9][8] = 1.5;
	G.Darcs[9][10] = G.Darcs[10][9] = 70; G.Tarcs[9][10] = G.Tarcs[10][9] = 0.7;
	G.Darcs[10][11] = G.Darcs[11][10] = 300; G.Tarcs[10][11] = G.Tarcs[11][10] = 3;
	G.Darcs[11][12] = G.Darcs[12][11] = 70; G.Tarcs[11][12] = G.Tarcs[12][11] = 0.7;
	G.Darcs[12][13] = G.Darcs[13][12] = 60; G.Tarcs[12][13] = G.Tarcs[13][12] = 0.6;
	G.Darcs[8][14] = G.Darcs[14][8] = 90; G.Tarcs[8][14] = G.Tarcs[14][8] = 0.9;
	G.Darcs[14][15] = G.Darcs[15][14] = 40; G.Tarcs[14][15] = G.Tarcs[15][14] = 0.4;
	G.Darcs[15][16] = G.Darcs[16][15] = 170; G.Tarcs[15][16] = G.Tarcs[16][15] = 1.7;
	G.Darcs[10][18] = G.Darcs[18][10] = 210; G.Tarcs[10][18] = G.Tarcs[18][10] = 2.1;
	G.Darcs[11][17] = G.Darcs[17][11] = 270; G.Tarcs[11][17] = G.Tarcs[17][11] = 2.7;
	G.Darcs[17][18] = G.Darcs[18][17] = 120; G.Tarcs[17][18] = G.Tarcs[18][17] = 1.2;
	G.Darcs[18][19] = G.Darcs[19][18] = 180; G.Tarcs[18][19] = G.Tarcs[19][18] = 1.8;
	G.Darcs[18][20] = G.Darcs[20][18] = 100; G.Tarcs[18][20] = G.Tarcs[20][18] = 1;
}
void Map(Graph& G)//�����ͼ����
{
	cout << "*������Ϣ������:" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		cout << G.vexs[i].num << "��" << G.vexs[i].name << endl;
	}
	cout << "*�������·�̵��ڽӾ���Ϊ������λ��m��" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			cout << G.Darcs[i][j] << "|";
		}
		cout << endl;
		cout << endl;
	}
	cout << "*�������ʱ����ڽӾ���Ϊ������λ��min��" << endl;
	cout << "*ע��ʱ�����˲��е��ٶ�Ϊ100m/min����" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			cout << G.Tarcs[i][j] << "|";
		}
		cout << endl;
		cout << endl;
	}
}
void FileMap(Graph& G)
{
	ofstream fout("C:\\Users\\�����\\Desktop\\У԰��ͨ��ѯϵͳ.txt");
	fout << "*������Ϣ������" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		fout << i + 1 << "��" << G.vexs[i].name << endl;
	}
	fout << "*�������·�̵��ڽӾ���Ϊ������λ��m��" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			fout << G.Darcs[i][j] << "|";
		}
		fout << endl;
		fout << endl;
	}
	fout << "*�������ʱ����ڽӾ���Ϊ������λ��min��" << endl;
	fout << "*ע��ʱ�����˲��е��ٶ�Ϊ100m/min����" << endl;
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			fout << G.Tarcs[i][j] << "|";
		}
		fout << endl;
		fout << endl;
	}
	fout.close();
}
void ShortDistance(Graph& G, Distance& D, Path& P,Time& T)//���������㷨����������·����ʱ��
{
	int t;//��㽨�����
	int r;//�յ㽨�����
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			D[i][j] = G.Darcs[i][j];
			T[i][j] = G.Tarcs[i][j];
			P[i][j] = j;
		}
	}
	for (int i = 0; i < G.vexCount; i++)
	{
		for (int j = 0; j < G.vexCount; j++)
		{
			for (int k = 0; k < G.vexCount; k++)
			{
				if (D[j][k] > D[j][i] + D[i][k])
				{
					D[j][k] = D[j][i] + D[i][k];
					P[j][k] = P[j][i];
				}
				if (T[j][k] > T[j][i] + T[i][k])
				{
					T[j][k] = T[j][i] + T[i][k];
				}
			}
		}
	}
	cout << "*������Ҫ��ѯ·������㽨�����:" << endl;
	cin >> t;
	cout << "*������Ҫ��ѯ·�����յ㽨�����:" << endl;
	cin >> r;
	cout << "*"<<G.vexs[t - 1].name << "��" << G.vexs[r - 1].name << "�����·����Ϊ��" << D[t - 1][r - 1] << " m" << endl;
	cout << "*"<<G.vexs[t - 1].name << "��" << G.vexs[r - 1].name << "�����ʱ��Ϊ��" << T[t - 1][r - 1] << " min" << endl;
	int k = P[t - 1][r - 1];
	cout << "*���·��Ϊ��";
	cout << G.vexs[t - 1].name;
	while (k != (r-1))
	{
		cout << "����>" << G.vexs[k].name;
		k = P[k][r - 1];
	}
	cout << "����>" << G.vexs[r - 1].name << endl;
}
void Add(Graph& G)//�����½�������·��
{
	int a;//����·����
	int x;//�������
	int y;//��������ľ���
	string str;
	int v = G.vexCount;//�������еĶ�����
	cout << "*������Ҫ���ӵĽ�����Ϊ��" << endl;
	cin >> str;
	G.vexs[G.vexCount].name = str;
	G.vexs[G.vexCount].num = G.vexCount + 1;
	cout << "*������������·������" << endl;
	cin >> a;
	G.arcCount += a;
	G.Darcs[v - 1][v - 1] = 0;
	for (int i = 0; i < G.vexCount - 1; i++)
	{
		G.Darcs[i][v - 1] = MAX;
		G.Darcs[v - 1][i] = MAX;
		G.Tarcs[i][v - 1] = MAX;
		G.Tarcs[v - 1][i] = MAX;
	}
	for (int j = 1; j <= a; j++)
	{
		cout << "*�������" << j << "�����½�����·�ߵĽ�����ţ�"<<endl;
		cin >> x;
		if ((x <= 0) || (x > G.vexCount))
		{
			cout << "��������������" << endl;
			return;
			break;
		}
		cout << "*�������½�����ý���֮��ľ��룺" << endl;
		cin >> y;
		G.Darcs[x - 1][v - 1] = y;
		G.Darcs[v - 1][x - 1] = y;
		G.Tarcs[x - 1][v - 1] = y / 100.0;
		G.Tarcs[v - 1][x - 1] = y / 100.0;
	}
	G.vexCount++;
	cout << "�½�������·�����ӳɹ���" << endl;
}
void Delet(Graph& G)//ɾ��ԭ�н�����·��
{
	int b;//Ҫɾ���Ľ������
	cout << "*������Ҫɾ���Ľ������" << endl;
	cin >> b;
	if ((b <= 0) || (b > G.vexCount))
	{
		cout << "��������������" << endl;
		return;
	}
	string s = G.vexs[b - 1].name;
	for (int i = b - 1; i < G.vexCount; i++)
	{
		G.vexs[i] = G.vexs[i + 1];
	}
	for (int i = b - 1; i < G.vexCount; i++)
	{
		for (int j = b - 1; j < G.vexCount; j++)
		{
			G.Darcs[i][j] = G.Darcs[i + 1][j + 1];
			G.Tarcs[i][j] = G.Tarcs[i + 1][j + 1];
		}
	}
	G.vexCount--;
	for (int j = 0; j < G.vexCount; j++)
	{
		G.vexs[j].num = j + 1;
	}
	cout << "����" << s << "��ɾ��" << endl;
}
void Modify(Graph& G)//�����е�ͼ�����޸�
{
	int d;//�û�ѡ����޸�ѡ��
	int m;//Ҫ�޸Ľ������Ƶı��
	int x, y;//��Ҫ�޸�·�������Ľ������
	int r;//�µ�·�߳���
	string str;//�޸ĺ��µĽ�������
	cout << "*��ѡ��Ҫ�޸ĵ�ѡ��*" << endl;
	while (1)
	{
		cout << "********************" << endl;
		cout << "  1���޸Ľ�������   " << endl;
		cout << "  2���޸�·�߳���   " << endl;
		cout << "********************" << endl;
		cin >> d;
		switch (d)
		{
		case 1: 
		{
			cout << "������Ҫ�޸ĵĽ������:" << endl;
			cin >> m;
			if ((m <= 0) || (m > G.vexCount))
			{
				cout << "��������������" << endl;
				break;
			}
			cout << "�������µĽ������ƣ�" << endl;
			cin >> str;
			G.vexs[m - 1].name = str;
			cout << "���������޸ĳɹ�" << endl;
			break;
		}
		case 2:
		{
			cout << "��������Ҫ�޸ĵ�·�������������������:" << endl;
			cin >> x >> y;
			if ((x < 1) || (y < 1) || (x > G.vexCount) || (y > G.vexCount))
			{
				cout << "��������������" << endl;
				break;
			}
				cout << "�������µ�·�߳��ȣ�" << endl;
				cin >> r;
				G.Darcs[x - 1][y - 1] = r;
				G.Darcs[y - 1][x - 1] = r;
				G.Tarcs[x - 1][y - 1] = r / 100.0;
				G.Tarcs[y - 1][x - 1] = r / 100.0;
				cout << "�µ�·�߳����޸ĳɹ�" << endl;
				break;
		}
		}
		break;
	}
}
int main()
{
	Graph G;
	Init(G);
	Distance D;
	Time T;
	Path P;
	int x;//�û�ѡ��Ĳ���
	while (1)
	{
		Mune();
		cout << "������Ҫѡ��Ĳ�����" << endl;
		cin >> x;
		switch (x)
		{
		case 1://��ʾ��ͼ��Ϣ
		{
			Map(G);
			FileMap(G);
			break;
		}
		case 2://�����½���
		{
			Add(G);
			break;
		}
		case 3://ɾ������
		{
			Delet(G);
			break;
		}
		case 4://�޸Ľ���
		{
			Modify(G);
			break;
		}
		case 5://�����·��
		{
			ShortDistance(G, D, P, T);
			break;
		}
		case 0://�˳�
		{
			cout << "-----**** ��ӭ�´�ʹ��! ****-----" << endl;
			return 0;
			break;
		}
		}
	}
}