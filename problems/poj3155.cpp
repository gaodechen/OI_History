// Using Max Weighted Closure, Dinic TLE, iSAP AC

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 2000, M = 50000;
const double EPS = 1e-8;
const double INF = 0x3fffffff;

struct Edge
{
    int v, next;
    double cap;
} e[M];

int head[N], cur[N], sig;

inline void Emit(int u, int v, double w)
{
    e[++ sig].v = v, e[sig].cap = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

inline void AddEdge(int u, int v, double w)
{
    Emit(u, v, w), Emit(v, u, 0);
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
            if(level[v] == -1 && e[i].cap > EPS)
            {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] != -1;
}

inline int D(int x)
{
    return ((x - 1) ^ 1) + 1;
}

double Augment(int u, double sur)
{
	if(u == t || sur <= EPS)
		return sur;
	double flow = 0;
	for(int i = cur[u]; i; i = e[i].next)
	{
		int v = e[i].v; double del;
		if(e[i].cap > EPS && level[v] == level[u] + 1)
		{
			del = Augment(v, min(e[i].cap - flow, sur));
            // There must be this!
            if(del < EPS) continue ;
			e[i].cap -= del, e[D(i)].cap += del;
			flow += del, sur -= del;
            if(sur < EPS) break ;
		}
		cur[u] = e[i].next;
	}
	return flow;
}

inline double MaxFlow()
{
    double flow = 0;
    while(BFS())
    {
        memcpy(cur, head, sizeof(head));
        flow += Augment(s, INF);
    }
    return flow;
}

struct Item {int u, v;} E[M];

inline double Construct(double g)
{
    memset(head, 0, sizeof(head)), sig = 0;
    for(int i = 1; i <= m; i ++)
    {
        AddEdge(i, E[i].u + m, INF);
        AddEdge(i, E[i].v + m, INF);
        AddEdge(s, i, 1);
    }
    for(int i = 1; i <= n; i ++)
        AddEdge(i + m, t, g);
    double flow = MaxFlow();
    return (double) m - flow;
}

bool vis[M];

void DFS(int u)
{
    vis[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(!vis[v] && e[i].cap > EPS)
            DFS(v);
    }
    return ;
}

bool ans[N];

int main(int argc, char **argv)
{
    while(scanf("%d%d", &n, &m) == 2)
    {
        if(m == 0)
        {
            puts("1\n1");
            continue ;
        }
        s = n + m + 1, t = s + 1;
        for(int i = 1; i <= m; i ++)
            scanf("%d%d", &E[i].u, &E[i].v);
        double l = 1 / n, r = m, Q = 1.0 / n / n;
        while(r - l >= Q)
        {
            double mid = (l + r) / 2;
            double w = Construct(mid);
            if(w < EPS) r = mid;
            else l = mid;
        }
        memset(vis, 0, sizeof(vis));
        Construct(l), DFS(s);
        int sum = 0;
        for(int i = 1; i <= n; i ++)
            sum += vis[i + m];
        printf("%d\n", sum);
        for(int i = 1; i <= n; i ++)
            if(vis[i + m])
                printf("%d\n", i);
    }
    return 0;
}
