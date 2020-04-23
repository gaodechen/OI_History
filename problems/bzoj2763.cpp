#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

#define     inc(i, l, r)        for(int i = l; i <= n; i ++)
#define     dec(i, l, r)        for(int i = r; i >= l; i --)
#define     foreach(u)          for(int i = head[u]; i; i = e[i].next)

using namespace	std;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> Pair;
typedef long long data;
const int N = 1e4 + 1;
const int M = 5e4 + 1;

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

struct Edge {int v, w, next;} e[M + M];

int sig, head[N];

inline void AddEdge(int u, int v, int w)
{
	e[++ sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
}

bool vis[N][11];
int n, m, K, S, T, f[N][11];

struct Item
{
    int u, k;

    bool operator < (const Item &b) const
    {
        return f[u][k] > f[b.u][b.k];
    }
};

inline int SPFA()
{
    memset(f, 0x3f, sizeof(f));
    priority_queue<Item> q;
    q.push((Item) {S, 0});
    f[S][0] = 0, vis[S][0] = 1;
    while(!q.empty())
    {
        Item t = q.top(); q.pop();
        int u = t.u, k = t.k;
        vis[u][k] = 0;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v, w = e[i].w;
            if(f[u][k] + w < f[v][k])
            {
                f[v][k] = f[u][k] + w;
                if(!vis[v][k])
                {
                    q.push((Item) {v, k});
                    vis[v][k] = 1;
                }
            }
            if(k < K && f[u][k] < f[v][k + 1])
            {
                f[v][k + 1] = f[u][k];
                if(!vis[v][k + 1])
                {
                    q.push((Item) {v, k + 1});
                    vis[v][k + 1] = 1;
                }
            }
        }
    }
    int r = INF;
    for(int i = 0; i <= K; i ++)
        r = min(r, f[T][i]);
    return r;
}

int main(int argc, char **argv)
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    n = in(), m = in(), K = in(), S = in() + 1, T = in() + 1;
    for(int i = 0; i < m; i ++)
    {
        int u = in() + 1, v = in() + 1, w = in();
        AddEdge(u, v, w), AddEdge(v, u, w);
    }
    int ans = SPFA();
    printf("%d\n", ans);
    return 0;
}
