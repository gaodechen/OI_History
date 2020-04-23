#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

using   namespace   std;
const   int N = 3e5 + 5;
const   int M = 6e5 + 5;
const   int INF = 0x3f3f3f3f;

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
    int v, w, next;
} e[M];

bool mark[M], vis[N];
int L[N], R[N], dis[N], path[N], q[N], f[N], pre[N];
int n, lim, sig, tik, front, tail, head[N], x[N], y[N];

inline void AddEdge(int u, int v, int w)
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
    return ;
}

inline int BFS(int s)
{
    memset(vis, 0, sizeof(vis));
    queue<int> q; q.push(s);
    dis[s] = 0, vis[s] = 1;
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(vis[v])
                continue ;
            if(mark[i])
                dis[v] = dis[u];
            else
                dis[v] = dis[u] + e[i].w;
            vis[v] = 1, pre[v] = i;
            q.push(v);
        }
    }
    int v = 1;
    for(int i = 2; i <= n; i ++)
        if(dis[i] > dis[v])
            v = i;
    return v;
}

inline void BFS2()
{
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    for(int i = 1; i <= tik; i ++)
    {
        int u = path[i];
        q.push(u), vis[u] = 1;
        dis[u] = 0, pre[u] = i;
    }
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(vis[v])
                continue ;
            if(mark[i])
                dis[v] = dis[u];
            else
                dis[v] = dis[u] + e[i].w;
            vis[v] = 1, pre[v] = pre[u];
            q.push(v);
        }
    }
    return ;
}

inline int g(int x)
{
    return ((x - 1) ^ 1) + 1;
}

int main()
{
    n = in(), lim = in();
    for(int i = 1; i < n; i ++)
    {
        int u, v, w;
        u = in(), v = in(), w = in();
        AddEdge(u, v, w);
        AddEdge(v, u, w);
    }
    int l = BFS(1), r = BFS(l);
    memcpy(L, dis, sizeof(dis));
    int len = dis[r], u = r;
    while(true)
    {
        int i = pre[u];
        path[++tik] = u;
        mark[i] = mark[g(i)] = 1;
        R[u] = len - L[u];
        if(u == l)
            break ;
        u = e[g(i)].v;
    }
    BFS2();
    for(int i = 1; i <= n; i ++)
        f[pre[i]] = max(f[pre[i]], dis[i]);
    n = tik;
    for(int i = 1; i <= n; i ++)
        x[i] = R[path[i]], y[i] = L[path[i]];
    int ans = INF;
    for(int i = 1, j = 0; i <= n; i ++)
    {
        while(j < n && y[i] - y[j+1] <= lim)
        {
            j ++;
            while(front < tail && f[q[tail]] < f[j])
                tail --;
            q[++tail] = j;
        }
        if(front < tail && q[front] < i)
            front ++;
        ans = min(ans, max(max(x[i], y[j]), f[q[front]]));
    }
    printf("%d\n", ans);
    return 0;
}
