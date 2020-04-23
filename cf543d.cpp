#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <queue>
#include    <vector>

#define     foreach(u)      for(int i = head[u]; i; i = e[i].next)
#define     INC(i, l, r)    for(int i = l; i <= r; i ++)
#define     DEC(i, r, l)    for(int i = r; i >= l; i --)

using	namespace	std;
typedef pair<int, int> Item;
typedef long long   data;

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

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

struct Edge {int v, next;} e[N + N];

int sig, head[N];

inline void AddEdge(int u, int v)
{
	e[++ sig].v = v, e[sig].next = head[u], head[u] = sig;
}

data d[N], f[N], L[N], R[N];
int pos[N];
vector<int> list[N];

void DFS(int u, int p)
{
    d[u] = 1;
    foreach(u)
    {
        int v = e[i].v;
        if(v != p)
        {
            DFS(v, u);
            d[u] = d[u] * (d[v] + 1) % MOD;
            pos[v] = list[u].size();
            list[u].push_back(v);
        }
    }
    int size = list[u].size();
    if(!size) return ;
    L[list[u][0]] = d[list[u][0]] + 1;
    INC(i, 1, size - 1)
    {
        int v = list[u][i];
        L[v] = L[list[u][i - 1]] * (d[v] + 1) % MOD;
    }
    R[list[u][size - 1]] = d[list[u][size - 1]] + 1;
    DEC(i, size - 2, 0)
    {
        int v = list[u][i];
        R[v] = R[list[u][i + 1]] * (d[v] + 1) % MOD;
    }
    return ;
}

void DFS2(int u, int p)
{
    data a = 1, b = 1;
    int size = list[p].size();
    if(pos[u])
        a = L[list[p][pos[u] - 1]];
    if(pos[u] < size - 1)
        b = R[list[p][pos[u] + 1]];
    f[u] = (a * b % MOD * f[p] % MOD + 1) % MOD;
    foreach(u) if(e[i].v != p)
        DFS2(e[i].v, u);
    return ;
}

int main(int argc, char **argv)
{
    int n = in();
    INC(i, 2, n) AddEdge(in(), i);
    DFS(1, 0), DFS2(1, 0);
    printf("%lld", d[1]);
    INC(i, 2, n) printf(" %lld", d[i] * f[i] % MOD);
    return 0;
}
