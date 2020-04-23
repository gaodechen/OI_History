#include    <cstdio>
#include    <cstring>
#include    <iostream>

#define     A       first
#define     B       second

using   namespace   std;
typedef long long   data;
typedef pair<int, int> Item;
const   int N = 1e5 + 5;
const   int M = 1e6 + 5;
const   int MOD = 1e6 + 3;
const   data INF = 0x3f3f3f3f;
const   Item PINF = Item(INF, INF);

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

struct Edge {int v, next;} e[N + N];

Item ans;
int n, sig, head[N]; 
data K, P, val[N], inv[M], f[M];

inline void AddEdge(int u, int v)
{
    e[++ sig].v = v, e[sig].next = head[u], head[u] = sig;
}

bool vis[N];
int maxSon[N], size[N];

void DFS(int u, int p)
{
    maxSon[u] = 0, size[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p || vis[v]) continue ;
        DFS(v, u);
        size[u] += size[v];
        maxSon[u] = max(maxSon[u], size[v]);
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

void Update(int u, int p, data d, int flag)
{
    d = d * val[u] % MOD;
    for(int i = head[u]; i; i = e[i].next)
    {
        if(e[i].v == p || vis[e[i].v]) continue ;
        Update(e[i].v, u, d, flag);
    }
    if(flag)
    {
        if(f[K * inv[d] % MOD] > P)
        {
            int x = f[K * inv[d] % MOD] - P, y = u;
            if(x > y) swap(x, y);
            ans = min(ans, Item(x, y));
        }
    }
    else if(f[d] <= P) f[d] = P + u;
    else f[d] = min(f[d], P + u);
    return ;
}

void Divide(int u)
{
    DFS(u, 0);
    int root = FindRoot(size[u], u, 0);
    vis[root] = 1, P += 100000, f[val[root]] = P + root;
    for(int i = head[root]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(vis[v]) continue ;
        // Using the path containing root only to update ans
        // Using the path not containint root only to update f[]
        Update(v, root, 1, 1);
        Update(v, root, val[root], 0);
    }
    for(int i = head[root]; i; i = e[i].next)
        if(!vis[e[i].v]) Divide(e[i].v);
    return ;
}

int main(int argc, char **argv)
{
    inv[1] = 1;
    for(int i = 2; i < MOD; i ++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    while(scanf("%d%lld", &n, &K) == 2)
    {
        memset(vis, 0, sizeof(vis));
        memset(head, 0, sizeof(head)), sig = 0;
        for(int i = 1; i <= n; i ++)
            val[i] = in();
        for(int i = 1; i < n; i ++)
        {
            int u = in(), v = in();
            AddEdge(u, v), AddEdge(v, u);
        }
        ans = PINF, Divide(1);
        if(ans == PINF) puts("No solution");
        else printf("%d %d\n", ans.A, ans.B);
    }
    return 0;
}
