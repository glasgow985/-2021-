#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000
# define max_dis 100000

typedef char vextype[20];
typedef struct {
    int N, E;//N�Ƕ�������E�Ǳ���
    int **matrix;//�����ڽӾ���
    vextype *vertex;//�洢�ڵ������
} Graph;


Graph createGraph(int n);
int isConnected(Graph g);
void nodeDegree(Graph g, int *node_degree);
double clusteringCoefficient(Graph g);
void computeEcc(Graph g, int *diameter, int *radius);
int dijkstra(Graph g, int start, int end, int *path);
void printPath(int d, int *diameter_path, Graph g);
void DFS(Graph g,int i);
int visited[max];


/**
 * ����һ���ڵ���Ϊn��ͼ
 * @param n �ڵ����
 * @return �������ͼ
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **) malloc(sizeof(int *) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype *) malloc(sizeof(vextype) * g.N);
    return g;
}

/**
 * ���ݾ���d��·������path���·���������Ͳ���Ҫ·���Ľڵ���Ҳ����ȷ���·��
 * @param d ·������
 * @param path ����·��������
 * @param g ͼ
 */
void printPath(int d, int *path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s ", g.vertex[path[k]]);
        path_length += g.matrix[path[k]][path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[path[k]]);
}

/**
 * �ж�ͼ�Ƿ���ͨ
 * @param g ͼ
 * @return ��ͨ����1�����򷵻�0
 */
int isConnected(Graph g) {
    //TODO
    int v;
    //��ʼ��������־
    for(v=0;v<g.N;v++)
	{
		visited[v]=0;
	}
	//������ȱ���ͼ
    DFS(g,0);
    for(v=0;v<g.N;v++)
    {
        //������δ����ǵĵ㼴����ͨ
        if(visited[v]==0)
            return 0;
    }
    return 1;
}

void DFS(Graph g,int i)
{
    int j;
    visited[i]=1;
    for(j = 0; j < g.N; j++)
    {
        if(g.matrix[i][j] != 0 && g.matrix[i][j] != max_dis && !visited[j])
            DFS(g, j);
    }
}

/**
 * ����ÿ����Ķ�
 * @param g ͼ
 * @param node_degree ��ÿ����Ķ�д�����������
 */
void nodeDegree(Graph g, int *node_degree) {
    //TODO
    int i,j;
    for(i = 0;i < g.N;i++)
        node_degree[i] = 0;
    for(i = 0;i < g.N;i++)
    {
        //����ͼ��ÿ����
        for(j = 0; j < g.N ;j++)
        {
            //����������������ϵ
            if(g.matrix[i][j] != max_dis && i != j)
                node_degree[i]++;
        }
    }
}

/**
 * ����ͼ�ľ���ϵ��
 * @param g ͼ
 * @return ���ؾ���ϵ��
 */
double clusteringCoefficient(Graph g) {
    //TODO
    /**
    * neibour[][] ������ھ�
    * neibourarc[] ������ھ�֮���������
    * neibournum[] ������ھ���
    * clco[] ����ľ���ϵ��
    * all_clco ���е����ϵ��֮��
    * aver_clco ͼ�ľ���ϵ��
    */
    int neibour[g.N][g.N],neibourarc[g.N],neibournum[g.N];
    double all_clco,aver_clco,clco[g.N];
    all_clco = 0;
    int i,j,k;
    for(i = 0;i < g.N;i++)
        neibourarc[i]=0;
    for(i = 0;i < g.N;i++)
    {
        k = 0;
        for(j = 0;j < g.N;j++)
        {
            //��¼������ھ�
            if(g.matrix[i][j] != max_dis && i != j)
            {
                neibour[i][k] = j;
                k++;
            }
        }
        //��¼������ھ���
        neibournum[i] = k;
    }
    for(i = 0;i < g.N ;i++)
    {
        for(j = 0;j < neibournum[i];j++)
        {
            for(k = j+1;k < neibournum[i];k++)
            {
                //��¼�����ھ�֮���������
                if(g.matrix[neibour[i][j]][neibour[i][k]] != max_dis )
                    neibourarc[i]++;
            }
        }
    }
    for(i = 0;i < g.N;i++)
    {
        //�������ϵ��
        if(neibournum[i] <= 1)
            clco[i] = 0;
        else
            clco[i] = (double)(neibourarc[i])/((double)(neibournum[i]*(neibournum[i]-1)*(0.5)));
        all_clco += clco[i];
    }
    aver_clco = all_clco/g.N;
    return aver_clco;
}

/**
 * ʹ��dijkstra�㷨���㵥Դ���·��
 * @param g ͼ
 * @param start ���
 * @param end �յ�
 * @param path ��start��end��·��, [start,...,end]
 * @return ·������
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    //TODO
    /**
    * Dis[] start�������·������
    * path1[] start��end�����·����ļ�¼
    */
    int i,j,k,m,Dis[g.N],min,path1[g.N];
    for(i = 0;i < g.N ;i++)
    {
        visited[i] = 0;
        Dis[i] = max_dis;
    }
    k = start;
    visited[start]=1;
    Dis[start] = 0;
    for(i = 1;i < g.N;i++)
    {
        //һ��ѭ�����start��һ��������·��
        for(j = 0; j < g.N ;j++)
        {
            min=Dis[k];
            if(g.matrix[k][j] == max_dis || j == k)
                continue;
            //�ҵ��м�㣬�޸����·�������ڵ����path1
            if(!visited[j] && (min+g.matrix[k][j] < Dis[j]) )
            {
                path1[j] = k;
                Dis[j] = min + g.matrix[k][j];
            }
        }
        min = max_dis;
        //�ҵ���һ�����·�����м��
        for(j = 0;j < g.N;j++)
        {
            if(Dis[j]<min && visited[j] == 0)
            {
                k = j;
                min = Dis[j];
            }
        }
        visited[k] = 1;
    }
    m = end;
    //������·�����м�����
    for(i = 0; m != start; i++)
        m = path1[m];
    m = end;
    //�ҳ����·��
    for(j = i; j >= 0; j--)
    {
        path[j] = m;
        m = path1[m];
    }
    return Dis[end];
}

/**
 * ����ͼ��ֱ���Ͱ뾶����ʾ: Floyd�㷨
 * @param g ͼ
 * @param diameter ָ��ֱ��������ָ��
 * @param radius ָ��뾶������ָ��
 * @return void
 */
void computeEcc(Graph g, int *diameter, int *radius)
{
    //TODO
    /**
    * Dis[][] ���·������ʱ������
    * Ecc[] ƫ����
    */
    int Dis[g.N][g.N];
    int Ecc[g.N];
    int i,j,k;
    //��ʼ��Dia[][]
    for(i = 0; i < g.N;i++)
    {
        for(j = 0;j < g.N;j++)
            Dis[i][j]=g.matrix[i][j];
    }
    //ʹ��Floyd�㷨�����·����������Dis[][]��
    for(i = 0;i < g.N;i++)
    {
        for(j = 0;j < g.N;j++)
        {
            for(k = 0;k < g.N;k++)
            {
                if(Dis[j][k]>Dis[j][i] + Dis[i][k])
                    Dis[j][k] = Dis[j][i] + Dis[i][k];
            }
        }
    }
    //���ƫ����
    for(i = 0; i < g.N;i++)
    {
        Ecc[i] = Dis[i][0];
        for(j = 0;j < g.N;j++)
        {
            if(Dis[i][j] > Ecc[i])
                Ecc[i] = Dis[i][j];
        }
    }
    //���ֱ���Ͱ뾶
    *diameter = Ecc[0];
    *radius = Ecc[0];
    for(i = 0;i < g.N;i++)
    {
        if(Ecc[i] > *diameter)
            *diameter = Ecc[i];
        if(Ecc[i] < *radius)
            *radius = Ecc[i];
    }
}

int main() {
    int node_num;
    int edge_num;
    int i,j,pathnode_num,node,t,x1,x2;
    printf("20810205 ����� ʵ���� �����\n");
    FILE *fp;
    fp = freopen("no2metro.txt", "r", stdin);
    if ( fp == NULL) {
        printf("There is an error in reading file no2metro.txt");
    }

    scanf("%d\n", &node_num);
    char name[max];
    Graph g = createGraph(node_num);
    for(i = 0; i < node_num; i++)
    {
        scanf("%d %s\n",&node,name);
        strcpy(g.vertex[node],name);
    }

    fp = freopen("metro.txt", "r", stdin);
    if ( fp == NULL) {
        printf("There is an error in reading file metro.txt");
    }
    scanf("%d\n%d\n", &node_num, &edge_num);
    for (i = 0; i < edge_num; i++)
    {
        scanf("%d\n", &pathnode_num);
        x1 = -1;
        for (j = 0; j < pathnode_num; j++)
        {
            scanf("%d %d\n",&x2, &t);
            if (x1 == -1)
            {
                x1 = x2;
                continue;
            }
            g.matrix[x1][x2] = t;
            g.matrix[x2][x1] = t;
            x1 = x2;
        }
    }
    fclose(fp);
    //����һ
    if(isConnected(g))
        printf("����ͼ��ͨ\n");
    else
        printf("����ͼ����ͨ!\n");
    //�����
    int degree[max],maxnode;
    nodeDegree(g,degree);
    maxnode = 0;
    for(i = 1; i < node_num; i++)
    {
        if(degree[maxnode] < degree[i])
            maxnode = i;
    }
    printf("������·����վ�ǣ�%s ������ %d ��·��ͨ��\n",g.vertex[maxnode],degree[maxnode]);

    if(isConnected(g))
    {
    //������
        int diameter, radius;
        computeEcc(g, &diameter, &radius);
        printf("ֱ��Ϊ:%d\n", diameter);
        printf("�뾶Ϊ:%d\n", radius);
    //������
        int short_path[max];
        int dis = dijkstra(g, 82, 1, short_path);
        printf("�Ӵ�ѧ��վ������վ�����Ҫ %d ����\n", dis);
        printf("·���ϵ�վ������Ϊ��\n");
        printPath(dis, short_path, g);
    }
    return 0;
}

