#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

#define     foreach(u)     for(int i = head[u]; i; i = e[i].next)

using	namespace	std;
const   int INF = 0x3f3f3f3f;
typedef pair<int, int> Item;
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

const   int N = 10001, M = 100000;

struct Edge
{
    int u, v, w;

    bool operator < (const Edge &b) const
    {
        return w < b.w;
    }
} e[M];

int pre[N], cost[N];

int Find(int u)
{
    if(pre[u] != u)
        pre[u] = Find(pre[u]);
    return pre[u];
}

int main(int argc, char **argv)
{
    int n = in(), m = in(), x = INF;
    for(int i = 1; i <= n; i ++)
        pre[i] = i, cost[i] = in(), x = min(x, cost[i]);
    for(int i = 0; i < m; i ++)
        e[i].u = in(), e[i].v = in(), e[i].w = in() * 2;
    for(int i = 0; i < m; i ++)
        e[i].w += cost[e[i].u] + cost[e[i].v];
    sort(e, e + m);
    int r = 0, cnt = 0;
    for(int i = 0; i < m; i ++)
    {
        int u = Find(e[i].u), v = Find(e[i].v);
        if(u != v) pre[u] = v, r += e[i].w, cnt ++;
        if(cnt == n - 1) break ;
    }
    printf("%d", r + x);
    return 0;
}
