#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
// typedef unsigned long long data;
typedef long long data;
const data INF = 0x3f3f3f3f3f3f3f3f;

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

const int N = 200001;

struct Item {int u, v, w;} E[N];

vector<int> list[N];
int n, m, K;

struct Edge
{
    int v, w, next;
};

int cut[N];
data bypass[N];

struct Graph
{
    int head[N];

    Edge e[N + N];

    inline void AddEdge(int u, int v, int w)
    {
        static int i = 0;
        e[++ i].v = v, e[i].w = w;
        e[i].next = head[u], head[u] = i;
        return ;
    }

    struct Vertex
    {
        int u; data d;

        Vertex(int u = 0, data d = 0): u(u), d(d) {}

        bool operator < (const Vertex &b) const
        {
            return d > b.d;
        }
    };

    bool vis[N];
    data dS[N], dT[N];
    priority_queue<Vertex> q;

    inline void Dijkstra(int s, int t, data *d)
    {
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; i ++)
            d[i] = INF;

        d[s] = 0;
        q.push(Vertex(s, 0));

        while(!q.empty())
        {
            int u = q.top().u; q.pop();
            if(vis[u]) continue ;
            vis[u] = 1;
            if(u == t) continue ;
            for(int i = head[u]; i; i = e[i].next)
            {
                int v = e[i].v;
                if(!vis[v] && d[v] > d[u] + e[i].w)
                {
                    d[v] = d[u] + e[i].w;
                    q.push(Vertex(v, d[v]));
                }
            }
        }

        return ;
    }

} g;

struct GraphS
{
    int head[N];

    Edge e[N + N];

    inline void AddEdge(int u, int v, int w)
    {
        static int i = 0;
        e[++ i].v = v, e[i].w = w;
        e[i].next = head[u], head[u] = i;
        return ;
    }
} S;

struct GraphST
{
    int head[N];

    Edge e[N + N];

    inline void AddEdge(int u, int v, int w)
    {
        static int i = 0;
        e[++ i].v = v, e[i].w = w;
        e[i].next = head[u], head[u] = i;
        return ;
    }

    int dfn[N], low[N], d[N], Count;

    void DFS(int u, int p)
    {
        dfn[u] = low[u] = ++ Count;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(v == p) continue ;
            if(!dfn[v])
            {
                DFS(v, u);
                low[u] = min(low[u], low[v]);
                if(dfn[u] < low[v])
                    cut[u] = v, K ++;
            }
            else
                low[u] = min(low[u], low[v]);
        }
        return ;
    }

    struct Vertex
    {
        data w; int d;

        bool operator < (const Vertex &b) const
        {
            return w > b.w || (w == b.w && d > b.d);
        }
    };

    inline void Initialize(int s, int t, int *D)
    {
        priority_queue<Vertex> q;

        for(int i = 1; i <= n; i ++)
            if(D[i] <= K)
                list[D[i]].push_back(i);
        for(int k = 0; k <= K; k ++)
        {
            int size = list[k].size();
            while(!q.empty() && q.top().d <= k)
                q.pop();
            for(int j = 0; j < size; j ++)
            {
                int u = list[k][j];
                for(int i = g.head[u]; i; i = g.e[i].next)
                {
                    int v = g.e[i].v;
                    if(D[u] > D[v] || cut[u] == v || D[v] <= k) continue ;
                    data w = g.dS[u] + g.e[i].w + g.dT[v];
                    if(w >= INF) continue ;
                    q.push((Vertex) {w, D[v]});
                }
            }
            if(!q.empty())
                bypass[k] = q.top().w;
        }
        return ;
    }

} ST;

bool vis[N];
int d[N];

inline void BFS(int s)
{
    deque<int> q;
    memset(vis, 0, sizeof(vis));
    q.push_front(s), vis[s] = 1;

    while(!q.empty())
    {
        int u = q.front(); q.pop_front();
        for(int i = S.head[u]; i; i = S.e[i].next)
        {
            int v = S.e[i].v;
            if(vis[v]) continue ;
            d[v] = d[u] + (cut[u] == v);
            vis[v] = 1;
            if(cut[u] == v)
                q.push_back(v);
            else
                q.push_front(v);
        }
    }
    return ;
}

int main(int argc, char **argv)
{
    memset(cut, -1, sizeof(cut));
    n = in(), m = in();

    for(int i = 0; i < m; i ++)
    {
        int u = in(), v = in(), w = in();
        E[i].u = u, E[i].v = v, E[i].w = w;
        g.AddEdge(u, v, w), g.AddEdge(v, u, w);
    }
    int s = in(), t = in();

    g.Dijkstra(s, t, g.dS);
    g.Dijkstra(t, s, g.dT);

    for(int i = 0; i < m; i ++)
    {
        int u = E[i].u, v = E[i].v, w = E[i].w;
        if(g.dS[u] + w + g.dT[v] == g.dS[t])
            ST.AddEdge(u, v, w), ST.AddEdge(v, u, w);
        else if(g.dS[v] + w + g.dT[u] == g.dS[t])
            ST.AddEdge(u, v, w), ST.AddEdge(v, u, w);
        if(g.dS[u] + w == g.dS[v])
            S.AddEdge(u, v, w);
        else if(g.dS[v] + w == g.dS[u])
            S.AddEdge(v, u, w);
    }

    ST.DFS(s, 0), BFS(s), ST.Initialize(s, t, d);
    
    int Q = in();

    while(Q --)
    {
        int u = in(), v = in();
        if(cut[u] == v || cut[v] == u)
        {
            data r = bypass[min(d[u], d[v])];
            r ? printf("%lld\n", r) : puts("Infinity");
        }
        else
            printf("%lld\n", g.dS[t]);
    }

    return 0;
}
