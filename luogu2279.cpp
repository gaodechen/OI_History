#include    <cstdio>
#include    <iostream>
#include    <queue>

using   namespace   std;
const   int N = 1e4 + 5;

bool vis[N];
int n, sig, tik;
int head[N], seq[N], pre[N];

struct Edge
{
    int v, next;
} e[N];

inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u];
    return (void) (head[u] = sig);
}

void Color(int u, int d)
{
    vis[u] = 1;
    if(d == 2)
        return ;
    for(int i = head[u]; i; i = e[i].next)
        Color(e[i].v, d + 1);
    return ;
}

int main()
{
    scanf("%d", &n);
    for(int i = 2, v; i <= n; i ++)
    {
        scanf("%d", &v);
        AddEdge(v, i);
        AddEdge(i, v);
        pre[i] = v;
    }
    queue<int> q; q.push(1);
    bool inq[N] = {0};
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        seq[++tik] = u, inq[u] = 1;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(!inq[v])
                q.push(v);
        }
    }
    int ans = 0;
    for(int i = tik; i; i --)
    {
        int u = seq[i];
        if(!vis[u])
        {
            int p = pre[u];
            if(pre[p])
                p = pre[p];
            Color(p, 0);
            ans ++;
        }
    }
    printf("%d\n", ans);
    return 0;
}

