#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 201500;

struct Edge
{
    int v, next;
} e[N];

bool ins[N];
int n, m, sig, top, cnt, ind, head[N];
int stack[N], low[N], dfn[N], mark[N];

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

inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
    return ;
}

int main()
{
    scanf("%d%d", &n, &m);
    int x[501], y[501];
    for(int i = 1; i <= m; i ++)
    {
        scanf("%d%d", &x[i], &y[i]);
        if(x[i] > y[i])
            swap(x[i], y[i]);
    }
    for(int i = 1; i <= m; i ++)
    {
        for(int j = 1; j < i; j ++)
        {
            if((x[i] <= x[j] && x[j] <= y[i] && y[i] <= y[j]) || (x[i] >= x[j] && x[i] <= y[j] && y[j] <= y[i]))
            {
                AddEdge(i, j + m), AddEdge(j + m, i);
                AddEdge(j, i + m), AddEdge(i + m, j);
            }
        }
    }
    for(int i = 1; i <= m + m; i ++)
        if(!dfn[i])
            Tarjan(i);
    for(int i = 1; i <= m; i ++)
    {
        if(mark[i] == mark[i+m])
        {
            printf("the evil panda is lying again\n");
            return 0;
        }
    }
    printf("panda is telling the truth...\n");
    return 0;
}
