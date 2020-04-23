#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
 
using   namespace   std;
typedef long long   data;
const   int N = 1e6 + 5;
 
bool vis[N];
data d[N][2];
int root1, root2, cur;
int n, sig, w[N], head[N];
 
struct Edge
{
    int v, next;
} e[N+N];
 
inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u];
    return (void) (head[u] = sig);
}
 
void FindCycle(int u, int p)
{
    vis[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        // (u, v), (v, u) ...
        if(v == p) continue ;
        if(!vis[v])
            FindCycle(v, u);
        else
            cur = i, root1 = u, root2 = v;
    }
    return ;
}
 
void DP(int u, int p)
{
    d[u][0] = 0, d[u][1] = w[u];
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(cur == i || ((i + 1) ^ 1) - 1 == cur || v == p)
            continue ;
        DP(v, u);
        d[u][1] += d[v][0];
        d[u][0] += max(d[v][0], d[v][1]);
    }
    return ;
}
 
inline data Compute(int u)
{
    FindCycle(u, 0);
    // u and v can't be selected together
    DP(root1, 0);
    data a = d[root1][0];
    DP(root2, 0);
    data b = d[root2][0];
    return max(a, b);
}
 
int main(int argc, char **argv)
{
    scanf("%d", &n);
    for(int i = 1, u; i <= n; i ++)
    {
        scanf("%d%d", &w[i], &u);
        AddEdge(u, i), AddEdge(i, u);
    }
    data ans = 0;
    for(int i = 1; i <= n; i ++)
        if(!vis[i])
            ans += Compute(i);
    printf("%lld\n", ans);
    return 0;
}
