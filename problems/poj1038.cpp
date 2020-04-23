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

/*
struct Edge {int v, next;};

int sig, head[N];

inline void AddEdge(int u, int v)
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
}
*/

int f[151][11][2];

int main(int argc, char **argv)
{
#define LOCAL
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T = in();
    while(T --)
    {
        int n = in(), m = in(), K = in();
    }
    return 0;
}
