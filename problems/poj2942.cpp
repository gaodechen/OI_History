#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <vector>

using   namespace   std;
const   int N = 1e3 + 5;
const   int M = 2e6 + 5;

inline int in()
{
	int k = 0, c = '\0';
	for(; c > '9' || c < '0';)
		c = getchar();
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

int n, m, sig, head[N];
bool G[N][N], odd[N];

struct Edge {int u, v, next, vis;} e[M + M];

inline void AddEdge(int u, int v)
{
    e[++ sig].u = u, e[sig].v = v, e[sig].vis = 0;
    e[sig].next = head[u], head[u] = sig;
}

int dfn[N], low[N], stack[N], number, top;
int color[N], mark[N];

bool Color(int u)
{
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(!mark[v]) continue ;
        if(color[v] == -1)
        {
            color[v] = color[u] ^ 1;
            if(!Color(v)) return false;
        }
        else if(color[u] == color[v])
            return false;
    }
    return true;
}

inline void Extract(int u)
{
    int i;
    memset(mark, 0, sizeof(mark));
    do
    {
        i = stack[top --];
        mark[e[i].u] = 1;
        mark[e[i].v] = 1;
    }
    while(e[i].u != u);
    memset(color, -1, sizeof(color));
    color[u] = 0;
    if(Color(u)) return ;
    for(int i = 1; i <= n; i ++)
        if(mark[i]) odd[i] = 1;
    return ;
}

#define     F(i)        ((i - 1) ^ 1) + 1

void Tarjan(int u)
{
    dfn[u] = low[u] = ++ number;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(e[i].vis) continue ;
        e[i].vis = e[F(i)].vis = 1;
        stack[++ top] = i;
        if(!dfn[v])
        {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            if(dfn[u] <= low[v]) Extract(u);
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
    return ;
}

int main(int argc, char **argv)
{
    while(scanf("%d%d", &n, &m) == 2 && n)
    {
        memset(G, 0, sizeof(G));
        memset(head, 0, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(odd, 0, sizeof(odd));
        sig = top = number = 0;
        for(int i = 0; i < m; i ++)
        {
            int u = in(), v = in();
            G[u][v] = 1, G[v][u] = 1;
        }
        for(int i = 1; i <= n; i ++)
            for(int j = i + 1; j <= n; j ++)
                if(!G[i][j]) AddEdge(i, j), AddEdge(j, i);
        int ans = 0;
        for(int i = 1; i <= n; i ++)
            if(!dfn[i]) Tarjan(i);
        for(int i = 1; i <= n; i ++)
            if(!odd[i]) ans ++;
        printf("%d\n", ans);
    }
    return 0;
}
