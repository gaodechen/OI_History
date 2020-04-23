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
const int N = 100;
const int MOD = 1000000007;
typedef long long data;
typedef pair<data, data> Hash;

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

const data A = 131, B = 233;

struct Edge
{
    int v, k, next;
    Hash h;
} e[N * 10];

int head[N];

inline void AddEdge(int u, int v, int k, Hash h)
{
    static int i = 0;
    e[++ i].v = v, e[i].k = k, e[i].h = h;
    e[i].next = head[u], head[u] = i;
    return ;
}

int n, m, ans[N];
data fac1[N + N], fac2[N + N];

void DFS(int u, int dep, Hash H1, Hash H2)
{
    if(H1 == H2)
    {
        ans[dep] ++;
        if(ans[dep] >= MOD) ans[dep] %= MOD;
    }
    if(dep == n + n) return ;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        Hash H1_, H2_;
        H1_.first = H1.first * A + v;
        H1_.second = H1.second * B + v;
        H2_.first = H2.first * fac1[e[i].k] + e[i].h.first;
        H2_.second = H2.second * fac2[e[i].k] + e[i].h.second;
        DFS(v, dep + 1, H1_, H2_);
    }
    return ;
}

int main(int argc, char **argv)
{
    freopen("sightseeing.in", "r", stdin);
    freopen("sightseeing.out", "w", stdout);
    n = in(), m = in(), fac1[0] = fac2[0] = 1;
    for(int i = 1; i <= n; i ++)
    {
        fac1[i] = fac1[i - 1] * A;
        fac2[i] = fac2[i - 1] * B;
    }
    for(int i = 1; i <= m; i ++)
    {
        int u = in(), v = in(), k = in();
        data w1 = 0, w2 = 0;
        for(int j = 0; j < k; j ++)
        {
            data x = (data) in();
            w1 = w1 * A + x, w2 = w2 * B + x;
        }
        AddEdge(u, v, k, Hash(w1, w2));
    }
    for(int i = 1; i <= n; i ++)
        DFS(i, 0, Hash(i, i), Hash(0, 0));
    for(int i = 1; i <= n + n; i ++)
        printf("%d\n", ans[i]);
    return 0;
}
