#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <set>
#include    <queue>
#include    <vector>

using   namespace   std;
const   int N = 25001;
const   int M = 50001;
const   int INF = 0x3f3f3f3f;

inline int in()
{
	int k = 0, c = '\0', o = 1;
	for(; c > '9' || c < '0';)
    {
		c = getchar();
        if(c == '-')
            o = -1;
    }
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
    if(o == -1)
        return -k;
	return k;
}

bool vis[N];
int m1, m2, sig1, sig2, pre[N], dis[N];
int n, s, head1[N], head2[N], deg[N];
vector<int> comp[N];

struct Item
{
    int u, d;

    Item(int u = 0, int d = 0): u(u), d(d)
    {
    }

    bool operator < (const Item &b) const
    {
        return d > b.d;
    }
} ;

struct Edge
{
    int v, w, next;
} e[M+M], g[M];

inline void AddEdge(int u, int v, int w, Edge *E, int *H, int &C)
{
    E[++C].v = v, E[C].w = w;
    E[C].next = H[u], H[u] = C;
    return ;
}

inline int Find(int u)
{
    if(u != pre[u])
        pre[u] = Find(pre[u]);
    return pre[u];
}

inline void Union(int u, int v)
{
    return (void) (pre[Find(v)] = Find(u));
}

inline void Dijkstra(int k)
{
    priority_queue<Item> q;
    int r = (int) comp[k].size();
    for(int i = 0; i < r; i ++)
        q.push(Item(comp[k][i], dis[comp[k][i]]));
    while(!q.empty())
    {
        int u = q.top().u; q.pop();
        if(vis[u] || dis[u] == INF)
            continue ;
        vis[u] = 1;
        for(int i = head1[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(dis[v] > dis[u] + e[i].w)
            {
                dis[v] = dis[u] + e[i].w;
                q.push(Item(v, dis[v]));
            }
        }
    }
    return ;
}

inline void Interface()
{
    for(int i = 1; i <= n; i ++)
        comp[Find(i)].push_back(i);
    for(int u = 1; u <= n; u ++)
        for(int i = head2[u]; i; i = g[i].next)
            if(pre[u] != pre[g[i].v])
                deg[pre[g[i].v]] ++;
    memset(vis, 0, sizeof(vis));
    memset(dis, INF, sizeof(dis));
    queue<int> q;
    dis[s] = 0;
    for(int i = 1; i <= n; i ++)
        if(comp[i].size() && !deg[i])
            q.push(i);
    while(!q.empty())
    {
        int t = q.front(); q.pop();
        int k = comp[t].size();
        Dijkstra(t);
        for(int j = 0; j < k; j ++)
        {
            int u = comp[t][j];
            for(int i = head2[u]; i; i = g[i].next)
            {
                int v = g[i].v;
                if(dis[v] > dis[u] + g[i].w && dis[u] != INF)
                    dis[v] = dis[u] + g[i].w;
                if(-- deg[pre[v]] == 0)
                    q.push(pre[v]);
            }
        }
    }
    return ;
}

int main()
{
    freopen("in", "r", stdin);
    n = in(), m1 = in(), m2 = in();
    for(int i = 1; i <= n; i ++)
        pre[i] = i;
    dis[s = in()] = 0;
    for(int i = 0; i < m1; i ++)
    {
        int u = in(), v = in(), w = in();
        Union(u, v);
        AddEdge(u, v, w, e, head1, sig1);
        AddEdge(v, u, w, e, head1, sig1);
    }
    for(int i = 0; i < m2; i ++)
    {
        int u = in(), v = in(), w = in();
        AddEdge(u, v, w, g, head2, sig2);
    }
    Interface();
    for(int i = 1; i <= n; i ++)
    {
        if(dis[i] < INF)
            printf("%d\n", dis[i]);
        else
            printf("NO PATH\n");
    }
    return 0;
}
