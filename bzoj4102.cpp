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

const int N = 1001, M = 2000001;

struct Edge {int v, next;} e[M];

int sig, head[N];

inline void AddEdge(int u, int v)
{
    e[++ sig].v = v, e[sig].next = head[u], head[u] = sig;
}

bool vis[N];
int n, m, C, d[N][N];
Pair item[N];

inline void BFS(int s)
{
    queue<int> q;
    memset(vis, 0, sizeof(vis));
    q.push(s), vis[s] = 1, d[s][s] = 0;
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(!vis[v])
            {
                d[s][v] = d[s][u] + C;
                q.push(v), vis[v] = 1;
            }
        }
    }
    return ;
}

int f[N];

int main(int argc, char **argv)
{
    n = in(), C = in();
    for(int i = 1; i <= n; i ++)
    {
        item[i].first = in(), item[i].second = i;
        int k = in();
        while(k --) AddEdge(i, in());
    }
    memset(d, INF, sizeof(d));
    for(int i = 1; i <= n; i ++)
        BFS(i), f[i] = item[i].first;
    sort(item + 1, item + n + 1);
    for(int i = 1; i <= n; i ++)
    {
        int u = item[i].second, w = item[i].first;
        for(int j = 1; j < i; j ++)
        {
            int v = item[j].second;
            f[u] = max(f[u], f[v] - d[u][v] + w);
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i ++)
        ans = max(f[i], ans);
    printf("%d", ans);
    return 0;
} 
