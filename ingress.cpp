#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
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

const int N = 1005, M = 5005;

struct Network
{
	int sig, head[N];
	int s, t, d[N], cur[N], gap[N], pre[N];

	struct Edge
	{
		int v, cap, next;
	} e[M + M];

	inline void Init(int x, int y)
	{
        return (void) (s = x, t = y, sig = 0);
	}

    inline void Emit(int u, int v, int w)
    {
		e[++ sig].v = v, e[sig].cap = w;
		e[sig].next = head[u], head[u] = sig;
		return ;
    }

	inline void AddEdge(int u, int v, int w)
	{
        // printf("%d %d %d\n", u, v, w);
		return (void) (Emit(u, v, w), Emit(v, u, 0));
	}

	inline int F(int i)
	{
        return ((i - 1) ^ 1) + 1;
	}

    inline void BFS()
    {
        memset(d, -1, sizeof(d));
        memset(gap, 0, sizeof(gap));
        queue<int> q;
        q.push(t), d[t] = 0;
        while(!q.empty())
        {
            int u = q.front(); q.pop();
            gap[d[u]] ++;
            for(int i = head[u]; i; i = e[i].next)
            {
                int v = e[i].v;
                if(d[v] == -1 && e[F(i)].cap > 0)
                {
                    d[v] = d[u] + 1;
                    q.push(v); 
                }
            }
        }
        return ;
    }

    inline int Augment()
    {
        int sur = INF, u = t;
        while(u != s)
        {
            sur = min(e[pre[u]].cap, sur);
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
        bool flag = false;
        for(int &i = cur[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(d[v] + 1 == d[u] && e[i].cap > 0)
            {
                pre[v] = i, u = v;
                flag = true;
                break ;
            }
        }
        return flag;
    }

    inline void Retreat(int &u)
    {
        int k = t - 1;
        for(int i = head[u]; i; i = e[i].next)
            if(e[i].cap > 0)
                k = min(k, d[e[i].v]);
        d[u] = k + 1;
        gap[d[u]] ++;
        cur[u] = head[u];
        if( u != s )
            u = e[F(pre[u])].v;
        return ;
    }

    inline int MaxFlow()
    {
        BFS();
        memcpy(cur, head, sizeof(head));
        int u = s, flow = 0;
        while(d[s] < t)
        {
            if(u == t)
                flow += Augment(), u = s;
            if(!Advance( u ))
            {
                if(-- gap[d[u]] == 0) break ;
                Retreat(u);
            }
        }
        return flow;
    }
} g;

struct Item
{
    int u, v, w;
} edge[M], even[N];

struct Edge
{
    int v, w, next;
} T[N + N];

int headT[N];

inline void AddEdge(int u, int v)
{
    static int i = 0;
    T[++ i].v = v, T[i].next = headT[u], headT[u] = i;
    return ;
}

const int K = 11;

int pre[N][K], dep[N];

void DFS(int u, int p)
{
    pre[u][0] = p, dep[u] = dep[p] + 1;
    for(int i = 1; i < K; i ++)
        pre[u][i] = pre[pre[u][i - 1]][i - 1];
    for(int i = headT[u]; i; i = T[i].next)
    {
        int v = T[i].v;
        if(v != p) DFS(v, u);
    }
    return ;
}

inline int LCA(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);
    int del = dep[u] - dep[v];
    for(int i = 0; i < K; i ++)
        if(del & (1 << i))
            u = pre[u][i];
    if(u == v) return u;
    for(int i = K - 1; i >= 0; i --)
        if(pre[u][i] != pre[v][i])
            u = pre[u][i], v = pre[v][i];
    return pre[u][0];
}

int n, m, X, E, ans, lca[N][N];
bool G[M][M];

inline bool U(int a, int p)
{
    return lca[a][p] == a;
}

inline bool onPath(int a, int b, int p)
{
    if(dep[a] < dep[b]) swap(a, b);
    int q = lca[a][b];
    return U(q, p) && (U(p, a) || U(p, b));
}

inline bool Intersect(Item a, Item b)
{
    int p = lca[a.u][a.v], q = lca[b.u][b.v];
    if(dep[p] < dep[q])
        return onPath(a.u, a.v, q);
    return onPath(b.u, b.v, p);
}

int main(int argc, char **argv)
{
    freopen("ingress.in", "r", stdin);
    // freopen("ingress.out", "w", stdout);
    n = in(), m = in(), X = 0, E = 0;
    for(int i = 0; i < m; i ++)
    {
        int u = in(), v = in(), w = in();
        if(w == 0)
            AddEdge(u, v), AddEdge(v, u);
        else
            edge[X ++] = (Item) {u, v, w};
    }
    DFS(1, 0);
    for(int i = 1; i <= n; i ++)
        for(int j = i + 1; j <= n; j ++)
            lca[i][j] = lca[j][i] = LCA(i, j);
    for(int i = 0; i < X; i ++)
    {
        int u = edge[i].u, v = edge[i].v, p = lca[u][v];
        int d = dep[u] + dep[v] - 2 * dep[p];
        if(!(d & 1)) even[++ E] = edge[i];
        else ans += edge[i].w;
    }
    cout << ans << endl;
    int V = E + E, s = V + 1, t = V + 2;
    g.Init(s, t);
    for(int i = 1; i <= E; i ++)
        for(int j = i + 1; j <= E; j ++)
            if(Intersect(even[i], even[j]))
                g.AddEdge(i, j + E, INF);
    for(int i = 1; i <= E; i ++)
        g.AddEdge(s, i, even[i].w);
    for(int i = 1; i <= E; i ++)
        g.AddEdge(i + E, t, even[i].w);
    ans += g.MaxFlow();
    printf("%d\n", ans);
    return 0;
}
