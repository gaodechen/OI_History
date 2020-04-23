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

template <typename T> inline T in()
{
	T k = 0; int f = 1, c = '\0';
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

/*
struct Edge {int v, next;};

int sig, head[N];

inline void AddEdge(int u, int v)
{
	e[++ sig].v = v, e[sig].next = head[u], head[u] = sig;
}
*/

int main(int argc, char **argv)
{
#define LOCAL
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    return 0;
}
