#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 600, M = 6000;

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

struct Edge
{
    int v, next, cap;
} e[M];

int head[N], cur[N];

inline void AddEdge(int u, int v, int w)
{
    static int i = 0;
    e[++ i].v = v, e[i].cap = w;
    e[i].next = head[u], head[u] = i;
    return ;
}

int n, m, s, t, level[N];

inline bool BFS()
{
    queue<int> q;
    memset(level, -1, sizeof(level));
    q.push(s), level[s] = 0;
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(level[v] == -1 && e[i].cap > 0)
            {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] != -1;
}

inline int F(int x)
{
    return ((x - 1) ^ 1) + 1;
}

inline int DFS(int u, int sur)
{
    if(u == t || sur == 0)
        return sur;
    int flow = 0;
    for(int i = cur[u]; i; i = e[i].next)
    {
        int v = e[i].v, del;
        if(e[i].cap >= flow && level[v] == level[u] + 1)
        {
            del = DFS(v, min(sur, e[i].cap - flow));
            e[i].cap -= del, e[F(i)].cap += del;
            flow += del, sur -= del;
            if(sur == 0) break ;
        }
        cur[u] = e[i].next;
    }
    return flow;
}

inline int MaxFlow()
{
    int flow = 0;
    while(BFS())
    {
        memcpy(cur, head, sizeof(head));
        flow += DFS(s, INF);
    }
    return flow;
}

struct Item {int u, v;} E[M];

int w[N];

inline void Construct(int k)
{
    memset(head, 0, sizeof(head));
    for(int i = 1; i <= n; i ++)
    {
        if(w[i] < 0) continue ;
        if(w[i] & k)
            AddEdge(s, i, INF), AddEdge(i, s, 0);
        else
            AddEdge(i, t, INF), AddEdge(t, i, 0);
    }
    for(int i = 0; i < m; i ++)
    {
        int u = E[i].u, v = E[i].v;
        AddEdge(u, v, 1), AddEdge(v, u, 1);
    }
    return ;
}

bool vis[N];

void DFS(int u)
{
    vis[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(vis[v] || !e[i].cap) continue ;
        DFS(v);
    }
    return ;
}

int main(int argc, char **argv)
{
    n = in(), m = in(), s = n + 1, t = s + 1;
    for(int i = 1; i <= n; i ++)
        w[i] = in();
    for(int i = 0; i < m; i ++)
        E[i].u = in(), E[i].v = in();
    long long ansE = 0, ansV = 0;
    for(int i = 1; i <= n; i ++)
        if(w[i] > 0)
            ansV += w[i];
    for(int i = 0; i <= 30; i ++)
    {
        Construct(1 << i);
        ansE += MaxFlow() * (1LL << i);
        memset(vis, 0, sizeof(vis));
        DFS(t);
        for(int j = 1; j <= n; j ++)
            if(!vis[j] && w[i] < 0)
                ansV += (1LL << i);
    }
    cout << ansE << endl;
    cout << ansV << endl;
    return 0;
}
