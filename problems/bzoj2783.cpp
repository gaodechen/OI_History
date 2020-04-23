#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <set>

using   namespace   std;
typedef pair<int, int> item;
const   int N = 1e5 + 5;

set<item> m;
set<item>::iterator iter;
int n, s, sig, ans, val[N], head[N];

struct Edge
{
    int v, next;
} e[N+N];

inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
    return ;
}

void DFS(int u, int p, int d, int sum)
{
    sum += val[u];
    set<item>::iterator k, t;
    set<item> tmp = m;
    k = m.insert(item(d, val[u])).first;
    while(sum > s && !m.empty())
    {
        t = m.begin();
        sum -= t -> second;
        m.erase(t);
    }
    if(sum == s)
        ans ++;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if( v == p )
            continue ;
        DFS(v, u, d + 1, sum);
    }
    m = tmp;
    return ;
}

int main()
{
    scanf("%d%d", &n, &s);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &val[i]);
    for(int i = 1; i < n; i ++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        AddEdge(u, v);
        AddEdge(v, u);
    }
    DFS(1, 1, 0, 0);
    printf("%d\n", ans );
    return 0;
}
