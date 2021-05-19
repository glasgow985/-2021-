#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000
# define max_dis 100000

typedef char vextype[20];
typedef struct {
    int N, E;//N是顶点数，E是边数
    int **matrix;//储存邻接矩阵
    vextype *vertex;//存储节点的名字
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
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
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
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param path 储存路径的数组
 * @param g 图
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
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g) {
    //TODO
    int v;
    //初始化遍历标志
    for(v=0;v<g.N;v++)
	{
		visited[v]=0;
	}
	//深度优先遍历图
    DFS(g,0);
    for(v=0;v<g.N;v++)
    {
        //若存在未被标记的点即不连通
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
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree) {
    //TODO
    int i,j;
    for(i = 0;i < g.N;i++)
        node_degree[i] = 0;
    for(i = 0;i < g.N;i++)
    {
        //遍历图中每个点
        for(j = 0; j < g.N ;j++)
        {
            //遍历点与其余点的联系
            if(g.matrix[i][j] != max_dis && i != j)
                node_degree[i]++;
        }
    }
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g) {
    //TODO
    /**
    * neibour[][] 各点的邻居
    * neibourarc[] 各点的邻居之间的连接数
    * neibournum[] 各点的邻居数
    * clco[] 各点的聚类系数
    * all_clco 所有点聚类系数之和
    * aver_clco 图的聚类系数
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
            //记录各点的邻居
            if(g.matrix[i][j] != max_dis && i != j)
            {
                neibour[i][k] = j;
                k++;
            }
        }
        //记录各点的邻居数
        neibournum[i] = k;
    }
    for(i = 0;i < g.N ;i++)
    {
        for(j = 0;j < neibournum[i];j++)
        {
            for(k = j+1;k < neibournum[i];k++)
            {
                //记录各点邻居之间的连接数
                if(g.matrix[neibour[i][j]][neibour[i][k]] != max_dis )
                    neibourarc[i]++;
            }
        }
    }
    for(i = 0;i < g.N;i++)
    {
        //计算聚类系数
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
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    //TODO
    /**
    * Dis[] start到各点的路径长度
    * path1[] start到end的最短路径点的记录
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
        //一次循环求得start到一个点的最短路径
        for(j = 0; j < g.N ;j++)
        {
            min=Dis[k];
            if(g.matrix[k][j] == max_dis || j == k)
                continue;
            //找到中间点，修改最短路径，将节点加入path1
            if(!visited[j] && (min+g.matrix[k][j] < Dis[j]) )
            {
                path1[j] = k;
                Dis[j] = min + g.matrix[k][j];
            }
        }
        min = max_dis;
        //找到下一个最短路径的中间点
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
    //求出最短路径的中间点个数
    for(i = 0; m != start; i++)
        m = path1[m];
    m = end;
    //找出最短路径
    for(j = i; j >= 0; j--)
    {
        path[j] = m;
        m = path1[m];
    }
    return Dis[end];
}

/**
 * 计算图的直径和半径，提示: Floyd算法
 * @param g 图
 * @param diameter 指向直径变量的指针
 * @param radius 指向半径变量的指针
 * @return void
 */
void computeEcc(Graph g, int *diameter, int *radius)
{
    //TODO
    /**
    * Dis[][] 最短路径（暂时）长度
    * Ecc[] 偏心率
    */
    int Dis[g.N][g.N];
    int Ecc[g.N];
    int i,j,k;
    //初始化Dia[][]
    for(i = 0; i < g.N;i++)
    {
        for(j = 0;j < g.N;j++)
            Dis[i][j]=g.matrix[i][j];
    }
    //使用Floyd算法求最短路径，储存在Dis[][]中
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
    //求出偏心率
    for(i = 0; i < g.N;i++)
    {
        Ecc[i] = Dis[i][0];
        for(j = 0;j < g.N;j++)
        {
            if(Dis[i][j] > Ecc[i])
                Ecc[i] = Dis[i][j];
        }
    }
    //求出直径和半径
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
    printf("20810205 林世铮 实验四 任务二\n");
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
    //任务一
    if(isConnected(g))
        printf("地铁图连通\n");
    else
        printf("地铁图不连通!\n");
    //任务二
    int degree[max],maxnode;
    nodeDegree(g,degree);
    maxnode = 0;
    for(i = 1; i < node_num; i++)
    {
        if(degree[maxnode] < degree[i])
            maxnode = i;
    }
    printf("换乘线路最多的站是：%s ，共有 %d 条路线通过\n",g.vertex[maxnode],degree[maxnode]);

    if(isConnected(g))
    {
    //任务三
        int diameter, radius;
        computeEcc(g, &diameter, &radius);
        printf("直径为:%d\n", diameter);
        printf("半径为:%d\n", radius);
    //任务四
        int short_path[max];
        int dis = dijkstra(g, 82, 1, short_path);
        printf("从大学城站到机场站最短需要 %d 分钟\n", dis);
        printf("路径上的站点名称为：\n");
        printPath(dis, short_path, g);
    }
    return 0;
}


