#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>

using   namespace   std;
const   int N = 2e2 + 5;
const   int M = 2e4 + 5;
const   int INF = 0x3f3f3f3f;

inline int in()
{
	int k = 0, c = '\0', o = 1;
	for(; c > '9' || c < '0';)
    {
		c = getchar();
        if(c == '-')
            o = -1;
    }
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
    if(o == -1)
        return -k;
	return k;
}

bool vis[N];
int E[N][N], sum[N], cnt[N], head[N];
int N1, N2, sig, dis[N], pre[N], g[N][N];

struct Edge
{
    int v, cost, next;
} e[M];

struct Point
{
    int x, y, c;
} buil[N], shel[N];

inline void AddEdge(int u, int v, int c)
{
    e[++sig].v = v, e[sig].cost = c;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

inline int Distance(Point &a, Point &b)
{
    return abs(a.x - b.x) + abs(a.y - b.y) + 1;
}

inline int SPFA(int s, int n)
{
    memset(dis, INF, sizeof(dis));
    queue<int> q;
    q.push(s), dis[s] = 0;
    while(!q.empty())
    {
        int u =  q.front(); q.pop();
        vis[u] = 0;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(dis[v] > dis[u] + e[i].cost)
            {
                pre[v] = u;
                dis[v] = dis[u] + e[i].cost;
                if(!vis[v])
                {
                    vis[v] = 1;
                    q.push(v);
                    if(++ cnt[v] > n)
                        return v;
                }
            }
        }
    }
    return -1;
}

int main()
{
    N1 = in(), N2 = in();
    for(int i = 0; i < N1; i ++)
        buil[i].x = in(), buil[i].y = in(), buil[i].c = in();
    for(int i = 0; i < N2; i ++)
        shel[i].x = in(), shel[i].y = in(), shel[i].c = in();
    for(int i = 0; i < N1; i ++)
        for(int j = 0; j < N2; j ++)
            E[i][j] = in();
    for(int i = 0; i < N1; i ++)
        for(int j = 0; j < N2; j ++)
            g[i][j] = Distance(buil[i], shel[j]);
    int s = N1 + N2;
    for(int i = 0; i < N1; i ++)
    {
        for(int j = 0; j < N2; j ++)
        {
            sum[j] += E[i][j];
            AddEdge(i, j + N1, g[i][j]);
            if(E[i][j])
                AddEdge(j + N1, i, -g[i][j]);
        }
    }
    for(int i = 0; i < N2; i ++)
    {
        if(sum[i] < shel[i].c)
            AddEdge(i + N1, s, 0);
        if(sum[i] > 0)
            AddEdge(s, i + N1, 0);
    }
    int v = SPFA(s, s + 1);
    if(v == -1)
    {
        printf("OPTIMAL\n");
        return 0;
    }
    printf("SUBOPTIMAL\n");
    memset(vis, 0, sizeof(vis));
    int u = v;
    while(!vis[u])
    {
        vis[u] = 1;
        u = pre[u];
    }
    v = u;
    do
    {
        int a = pre[u], b = u;
        if(a < N1 && b >= N1 && b < s)
            E[a][b-N1] ++;
        if(b < N1 && a >= N1 && a < s)
            E[b][a-N1] --;
        u = pre[u];
    }
    while(u != v);
    for(int i = 0; i < N1; i ++)
    {
        printf("%d", E[i][0]);
        for(int j = 1; j < N2; j ++)
            printf(" %d", E[i][j]);
        printf("\n");
    }
    return 0;
}
