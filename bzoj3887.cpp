#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <queue>

using	namespace	std;
const   int N = 2e5 + 5;

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

int mark[N], size[N];

struct TopoGraph
{
    int inDeg[N], head[N];
    struct Edge {int v, next;} e[N];

    inline void AddEdge(int u, int v) {
        static int i = 0;
        e[++i].v = v, e[i].next = head[u], head[u] = i, inDeg[v] ++;
    }

    inline void TopoSort(int *f, int n)
    {
        queue<int> q;
        memset(f, 0xc0, sizeof(inDeg));
        for(int i = 1; i <= n; i ++)
            if(!inDeg[i]) q.push(i);
        f[mark[1]] = size[mark[1]];
        while(!q.empty())
        {
            int u = q.front(); q.pop();
            for(int i = head[u]; i; i = e[i].next)
            {
                int v = e[i].v;
                f[v] = max(f[v], f[u] + size[v]);
                if(-- inDeg[v] == 0) q.push(v);
            }
        }
        return ;
    }
} g1, g2;

bool inStack[N];
int Count, top, number;
int low[N], stack[N], dfn[N], head[N];

struct Edge {int v, next;} e[N];

inline void AddEdge(int u, int v) {
    static int i = 0;
    e[++i].v = v, e[i].next = head[u], head[u] = i;
}

void Tarjan(int u) {
    dfn[u] = low[u] = ++ number;
    stack[++ top] = u, inStack[u] = 1;
    for(int i = head[u]; i; i = e[i].next) {
        int v = e[i].v;
        if(!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(inStack[v])
            low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        int v;
        Count ++;
        do
        {
            v = stack[top --], inStack[v] = 0;
            mark[v] = Count, size[Count] ++;
        }
        while(u != v);
    }
    return ;
}

int f[N], d[N];

int main(int argc, char **argv)
{
    int n = in(), m = in();
    for(int i = 0; i < m; i ++)
        AddEdge(in(), in());
    for(int i = 1; i <= n; i ++)
        if(!dfn[i]) Tarjan(i);
    for(int u = 1; u <= n; u ++) {
        for(int i = head[u]; i; i = e[i].next) {
            int v = e[i].v;
            if(mark[u] != mark[v]) {
                g1.AddEdge(mark[u], mark[v]);
                g2.AddEdge(mark[v], mark[u]);
            }
        }
    }
    g1.TopoSort(f, Count);
    g2.TopoSort(d, Count);
    int r = size[mark[1]] << 1;
    for(int u = 1; u <= n; u ++)
        for(int i = head[u]; i; i = e[i].next)
            r = max(r, d[mark[u]] + f[mark[e[i].v]]);
    printf("%d\n", r - size[mark[1]]);
    return 0;
}
