#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e5 + 5;
const   int M = 3e5 + 5;

struct Edge
{
    int v, next;
} e[M];

bool ins[N];
int n, m, sig, head[N], dfn[N], low[N], in[N];
int top, cnt, ind, stack[N], mark[N], size[N];

inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u];
    return (void) (head[u] = sig);
}

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
            size[cnt] ++;
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
        int u, v;
        scanf("%d%d", &u, &v);
        AddEdge(u, v);
    }
    for(int i = 1; i <= n; i ++)
        if(!dfn[i])
            Tarjan(i);
    for(int u = 1; u <= n; u ++)
    {
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(mark[u] != mark[v])
                in[mark[v]] ++;
        }
    }
    int sum = 0;
    for(int i = 1; i <= cnt; i ++)
        if(!in[i])
            sum += 1;
    for(int u = 1; u <= n; u ++)
    {
        if(size[mark[u]] == 1 && !in[mark[u]])
        {
            bool flag = true;
            for(int i = head[u]; i; i = e[i].next)
            {
                if(in[mark[e[i].v]] == 1)
                {
                    flag = false;
                    break ;
                }
            }
            if(flag)
            {
                sum --;
                break ;
            }
        }
    }
    printf("%.6lf", 1.0 - (double) sum / n);
    return 0;
}
