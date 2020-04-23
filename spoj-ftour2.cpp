#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int N = 2e5 + 5;
const	int INF = 0x3f3f3f3f;

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

struct Edge
{
	int u, v, w, next;
} e[N + N];

int sig, head[N];

inline void AddEdge(int u, int v, int w)
{
	e[++ sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

int n, K, m, ans, color[N], size[N], maxSon[N];
bool vis[N];

void DFS(int u, int p)
{
    size[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p || vis[v]) continue ;
        DFS(v, u);
        maxSon[u] = max(maxSon[u], size[v]);
        size[u] += size[v];
    }
    return ;
}

int FindRoot(int sum, int u, int p)
{
    int r = u;
    maxSon[u] = max(maxSon[u], sum - size[u]);
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p || vis[v]) continue ;
        int x = FindRoot(sum, v, u);
        if(maxSon[x] < maxSon[r]) r = x;
    }
    return r;
}

int g[N], dep[N];

int DepthDFS(int u, int p)
{
    int r = 0;
    dep[u] = color[u];
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p || vis[v]) continue ;
        r = max(r, DepthDFS(v, u));
    }
    return dep[u] += r;
}

void gDFS(int u, int p, int d, int c)
{
    g[c] = max(g[c], d);
    if(c > K) return ;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p || vis[v]) continue ;
        gDFS(v, u, d + e[i].w, c + color[v]);
    }
    return ;
}

bool cmp(const int &i, const int &j)
{
    return dep[e[i].v] < dep[e[j].v];
}

int node[N], temp[N];

void Divide(int u)
{
    DFS(u, 0);
    int root = FindRoot(size[u], u, 0);
    vis[root] = 1;
    for(int i = head[root]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v != root && !vis[v]) Divide(v);
    }
    int top = 0;
    for(int i = head[root]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == root || vis[v]) continue ;
        DepthDFS(v, root), node[top ++] = i;
    }
    sort(node, node + top, cmp);
    for(int i = 0; i <= dep[e[node[top - 1]].v]; i ++)
        temp[i] = -INF;
    for(int i = 0; i < top; i ++)
    {
        int v = e[node[i]].v, w = e[node[i]].w;
        for(int j = 0; j <= dep[v]; j ++) g[j] = -INF;
        gDFS(v, root, w, color[v]);
        if(i != 0)
        {
            for(int j = 0; j <= K - color[root] && j <= dep[v]; j ++)
            {
                int r = min(dep[e[node[i - 1]].v], K - color[root] - j);
                if(temp[r] == -INF) break ;
                if(g[j] != -INF) ans = max(ans, temp[r] + g[j]);
            }
        }
        for(int j = 0; j <= dep[v]; j ++)
        {
            temp[j] = max(g[j], temp[j]);
            if(j) temp[j] = max(temp[j], temp[j - 1]);
            if(j + color[root] <= K) ans = max(ans, temp[j]);
            else break ;
        }
    }
    return ;
}

int main(int argc, char **argv)
{
    freopen("in", "r", stdin);
    n = in(), K = in(), m = in();
	for(int i = 0; i < m; i ++)
		color[in()] = 1;
	for(int i = 1; i < n; i ++)
	{
		int u = in(), v = in(), w = in();
		AddEdge(u, v, w), AddEdge(v, u, w);
    }
    ans = 0, Divide(1);
    printf("%d", ans);
	return 0;
}
