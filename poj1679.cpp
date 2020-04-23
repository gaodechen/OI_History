#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e2 + 1;
const   int M = 1e4 + 1;

struct Edge
{
    int u, v, w;

    bool operator < (const Edge &b) const
    {
        return w < b.w;
    }
} e[N*N];

bool mark[M];
int t, n, m;
int bot[N][N], pre[N], G[N][N];

inline int Find(int u)
{
    if(u != pre[u])
        pre[u] = Find(pre[u]);
    return pre[u];
}

inline void Union(int u, int v)
{
    return (void) (pre[v] = u);
}

inline int Kruskal()
{
    int cnt = 0, cost = 0;
    for(int i = 1; i <= n; i ++)
        pre[i] = i;
    sort(e, e + m);
    for(int i = 0; i < m; i ++)
    {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if(Find(u) != Find(v))
        {
            Union(u, v);
            mark[i] = 1;
            cost += w, cnt ++;
            G[u][v] = G[v][u] = w;
        }
        if(cnt == n - 1)
            break ;
    }
    return cost;
}

int main()
{
    scanf("%d", &t);
    while(t --)
    {
        memset(G, 0x3f, sizeof(G));
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i ++)
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
        int cost = Kruskal();
        for(int k = 1; k <= n; k ++)
            for(int i = 1; i <= n; i ++)
                for(int j = 1; j <= n; j ++)
                    G[i][j] = min(G[i][j], max(G[i][k], G[k][j]));
        bool flag = false;
        for(int i = 1; i <= m; i ++)
        {
            if(mark[i])
                continue ;
            if(G[e[i].u][e[i].v] == e[i].w)
            {
                flag =true;
                break ;
            }
        }
        if(flag)
            printf("Not Unique!\n");
        else
            printf("%d\n", cost);
    }
    return 0;
}
