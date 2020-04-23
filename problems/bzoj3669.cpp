#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <deque>
#include    <vector>

using namespace	std;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> Pair;
typedef long long data;

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

const int N = 5e4 + 1;
const int M = 1e5 + 1;

struct Item
{
    int u, v, a, b;

    bool operator < (const Item &y) const
    {
        return a < y.a || (a == y.a && b < y.b);
    }
} g[M];

int n, m, f[N];
bool vis[N];

struct Edge {int v, a, b, next;} e[M + M];

deque<int> q;
int sig, head[N];

inline void AddEdge(int u, int v, int a, int b)
{
    e[++ sig].v = v, e[sig].a = a, e[sig].b = b;
    e[sig].next = head[u], head[u] = sig;
}

inline int Max(int a, int b)
{
    return a > b ? a : b;
}

inline void Push(int u)
{
    if(vis[u]) return ;
    vis[u] = 1;
    if(q.empty()) q.push_back(u);
    else if(f[u] <= f[q.front()]) q.push_front(u);
    else q.push_back(u);
    return ;
}

inline void SPFA()
{
    while(!q.empty())
    {
        int u = q.front();
        q.pop_front(), vis[u] = 0;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v, w = Max(f[u], e[i].b);
            if(f[v] > w) Push(v), f[v] = w;
        }
    }
    return ;
}

int main(int argc, char **argv)
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    n = in(), m = in();
    for(int i = 0; i < m; i ++)
        g[i].u = in(), g[i].v = in(), g[i].a = in(), g[i].b = in();
    sort(g, g + m);
    memset(f, INF, sizeof(f));
    f[1] = 0, vis[1] = 1;
    q.push_back(1);
    int i = 0, ans = INF;
    while(i < m)
    {
        int t = g[i].a, update = 0;
        if(t + g[i].b >= ans) {i ++; continue ;}
        while(g[i].a == t && i < m)
        {
            int u = g[i].u, v = g[i].v;
            AddEdge(u, v, t, g[i].b), AddEdge(v, u, t, g[i].b);
            if(!vis[u] || !vis[v]) update = 1;
            Push(u), Push(v), i ++;
        }
        if(update) SPFA();
        if(ans > f[n] + t) ans = f[n] + t;
    }
    if(ans == INF) puts("-1");
    else printf("%d", ans);
    return 0;
}

