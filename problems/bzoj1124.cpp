#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

#define     foreach(u)     for(int i = head[u]; i; i = e[i].next)

using	namespace	std;
const   int INF = 0x3f3f3f3f;
typedef pair<int, int> Item;
typedef long long   data;

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
        if((c = getchar()) == '-')
            f = 0;
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

const   int N = 1e6 + 5;

int n, m, next[N], degree[N];

namespace Min
{
    int q[N];
    bool dead[N], vis[N];

    inline int Solve()
    {
        int head = 1, tail = 0, r = 0;
        for(int i = 1; i <= n; i ++)
            if(!degree[i]) q[++ tail] = i;
        while(head <= tail)
        {
            int u = q[head ++];
            vis[u] = 1;
            if(!dead[next[u]])
            {
                dead[next[u]] = vis[next[u]] = 1, r ++;
                if(-- degree[next[next[u]]] == 0)
                   q[++ tail] = next[next[u]];
            }
        }
        for(int i = 1; i <= n; i ++)
        {
            if(vis[i]) continue ;
            int cnt = 0, p = i;
            while(true)
            {
                if(vis[p]) break ;
                vis[p] = 1, cnt ++;
                p = next[p];
            }
            r += (cnt + 1) >> 1;
        }
        return r;
    }
};

namespace Max
{
    struct Edge {int v, next;} e[N + N];

    int sig, top, head[N], stack[N];
    bool vis[N];

    inline void AddEdge(int u, int v)
    {
        e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
    }

    inline void DFS(int u)
    {
        vis[u] = 1, stack[++ top] = u;
        for(int i = head[u]; i; i = e[i].next)
            if(!vis[e[i].v]) DFS(e[i].v);
        return ;
    }

    inline int Solve()
    {
        int r = 0;
        for(int i = 1; i <= n; i ++)
            AddEdge(i, next[i]), AddEdge(next[i], i);
        for(int i = 1; i <= n; i ++)
        {
            if(vis[i]) continue ;
            top = 0, DFS(i);
            if(top == 1) r ++;
            else
            {
                int cnt = 0, size = top;
                while(top) cnt += degree[stack[top --]] == 0;
                if(!cnt) r += size - 1;
                else r += size - cnt;
            }
        }
        return r;
    }
};

int main(int argc, char **argv)
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    n = in();
    for(int i = 1; i <= n; i ++)
        degree[next[i] = in()] ++;
    int r2 = Max::Solve();
    int r1 = Min::Solve();
    printf("%d %d", r1, r2);
    return 0;
}
