#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		set(p, k)		memset(p, k, sizeof(p))
#define		cpy(p, k)		memcpy(p, k, sizeof(k))

using	namespace	std;
const   int INF = 0x3f3f3f3f;
const   int N = 505, M = 1605;

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

int s, t, n, head[N];

struct Edge {int v, cap, next;} e[M];

inline void AddEdge(int u, int v, int w)
{
    static int i = 0;
    e[++ i].v = v, e[i].cap = w;
    e[i].next = head[u], head[u] = i;
}

inline int F( int i ) {return ((i - 1) ^ 1) + 1;}

inline void Emit(int u, int v, int w)
{
    AddEdge(u, v, w), AddEdge(v, u, w);
}

int gap[N], pre[N], cur[N], d[N];

inline void BFS()
{
    queue<int> q;
    set(gap, 0), set(d, -1);
    q.push(t), d[t] = 0;
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        gap[d[u]] ++;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(d[v] == -1 && e[F(i)].cap > 0)
                q.push(v), d[v] = d[u] + 1;
        }
    }
    return ;
}

inline int Augment()
{
    int sur = INF, u = t;
    while(u != s)
    {
        sur = min(sur, e[pre[u]].cap);
        u = e[F(pre[u])].v;
    }
    u = t;
    while(u != s)
    {
        e[pre[u]].cap -= sur;
        e[F(pre[u])].cap += sur;
        u = e[F(pre[u])].v;
    }
    return sur;
}

inline bool Advance(int &u)
{
    bool r = false;
    for(int &i = cur[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(d[v] + 1 == d[u] && e[i].cap > 0)
        {
            r = true, u = v, pre[v] = i;
            break ;
        }
    }
    return r;
}

inline void Retreat(int &u)
{
    int k = n - 1;
    for(int i = head[u]; i; i = e[i].next)
        if(e[i].cap > 0) k = min(d[e[i].v], k);
    d[u] = k + 1, gap[d[u]] ++, cur[u] = head[u];
    if(u != s) u = e[F(pre[u])].v;
    return ;
}

inline int MaxFlow()
{
    BFS(), cpy(cur, head);
    int u = s, flow = 0;
    while(d[s] < n)
    {
        if(u == t)
            flow += Augment(), u = s;
        if(!Advance(u))
        {
            if(-- gap[d[u]] == 0) break ;
            Retreat(u);
        }
    }
    return flow;
}

struct Item {int u, v, w;} g[M];

int main(int argc, char **argv)
{
    n = in(); int E = in(), K = in();
    for(int i = 1; i <= E; i ++)
        g[i].u = in(), g[i].v = in(), g[i].w = in();
    s = g[K].u, t = g[K].v;
    for(int i = 1; i <= E; i ++)
        if(i != K && g[i].w <= g[K].w)
            Emit(g[i].u, g[i].v, g[K].w - g[i].w + 1);
    printf("%d\n", MaxFlow());
    return 0;
}
