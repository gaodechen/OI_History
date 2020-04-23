#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 3e3 + 5;

struct Edge
{
	int v, w, next;
} e[N+N];

int head[N], d[N][N], n, m, sig;

void AddEdge( int u, int v, int w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

int DFS(int u, int p)
{
    if(u > n - m)
        return 1;
    int sum = 0;
    for(int k = head[u]; k; k = e[k].next)
    {
        int v = e[k].v;
        if(v == p)
            continue ;
        sum += DFS(v, u);
        for(int i = sum; i; i --)
            for(int j = 0; j <= i; j ++)
                d[u][i] = max(d[u][i], d[v][j] + d[u][i-j] - e[k].w);
    }
    return sum;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n - m; i ++)
    {
        int k, a, c;
        scanf("%d", &k);
        for(int j = 0; j < k; j ++)
        {
            scanf("%d%d", &a, &c);
            AddEdge(i, a, c);
            AddEdge(a, i, c);
        }
    }
    memset(d, 128, sizeof(d));
    for(int i = 1; i <= n; i ++)
        d[i][0] = 0;
    for(int i = n - m + 1; i <= n; i ++)
        scanf("%d", &d[i][1]);
    DFS(1, 1);
    for(int i = m; i >= 0; i --)
    {
        if(d[1][i] >= 0)
        {
            printf("%d", i);
            return 0;
        }
    }
    return 0;
}
