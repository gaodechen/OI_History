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

using	namespace	std;
const   int INF = 0x3f3f3f3f;
typedef pair<int, int> Pair;
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

const int N = 1e5 + 5;

struct Item {int u, v, w; data k;} item[N];

struct Edge {int v, w, next;} e[N + N];

int sig, head[N];

inline void AddEdge(int u, int v, int w)
{
	e[++ sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
}

data size[N];
int dep[N];

void DFS(int u, int p)
{
    size[u] = 1, dep[u] = dep[p] + 1;
    foreach(u)
    {
        int v = e[i].v;
        if(v == p) continue ;
        DFS(v, u);
        size[u] += size[v];
    }
    return ;
}

int main(int argc, char **argv)
{
#define LOCAL
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    int n = in();
    for(int i = 0; i < n - 1; i ++)
    {
        int u = in(), v = in(), w = in();
        item[i] = (Item) {u, v, w};
        AddEdge(u, v, w), AddEdge(v, u, w);
    }
    DFS(1, 0);
    inc(i, 0, n - 2)
    {
        if(dep[item[i].u] > dep[item[i].v]) swap(item[i].u, item[i].v);
        item[i].k = size[item[i].v] * (size[1] - size[item[i].v]) * 2;
    }
    double S = 0, K = (double) 3 / ((double) (n - 1) * n);
    inc(i, 0, n - 2) S += (double) item[i].w * item[i].k;
    int q = in();
    while(q --)
    {
        int i = in() - 1, x = in();
        S -= (double) (item[i].w - x) * item[i].k;
        item[i].w = x;
        printf("%.10lf\n", S * K);
    }
    return 0;
}
