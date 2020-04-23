#include    <cstdio>
#include    <iostream>

using   namespace   std;
const   int N = 2e3 + 5;
const   int M = 1e6 + 5;

struct Edge
{
    int v, next;
} e[M+M];

int sig, head[N];

inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
    return ;
}

bool ins[N];
int n, m, top, cnt, ind;
int dfn[N], low[N], mark[N], stack[N];

void Tarjan(int u)
{
    dfn[u] = low[u] = ++ ind;
    stack[++top] = u, ins[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(!dfn[v])
        {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        int v;
        cnt ++;
        do
        {
            v = stack[top--];
            mark[v] = cnt;
            ins[v] = 0;
        }
        while(u != v);
    }
    return ;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i ++)
    {
        char buf[3];
        int u, v, w;
        scanf("%d%d%d%s", &u, &v, &w, buf);
        u ++, v ++;
        if(buf[0] == 'A')
        {
            if(w == 0)
                AddEdge(u + n, v), AddEdge(v + n, u);
            else
                AddEdge(u, u + n), AddEdge(v, v + n);
        }
        else if(buf[0] == 'O')
        {
            if(w == 0)
                AddEdge(u + n, u), AddEdge(v + n, v);
            else
                AddEdge(u, v + n), AddEdge(v, u + n);
        }
    }
    for(int i = 1; i <= n + n; i ++)
        if(!dfn[i])
            Tarjan(i);
    for(int i = 1; i <= n; i ++)
    {
        if(mark[i] == mark[i+n])
        {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    return 0;
}
