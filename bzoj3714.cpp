#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;

char buf[1 << 15], *S = buf, *T = buf;

#define GetChar() (S == T && (T = (S = buf) + fread(buf, 1, 1 << 15, stdin), S == T) ? 0 : *S ++)

inline int in()
{
	int k = 0, c = '\0';
	for(; c > '9' || c < '0';)
        c = GetChar();
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = GetChar();
	}
	return k;
}

const int N = 2005, M = N * N;

struct Edge
{
    int u, v, w;

    bool operator < (const Edge &b) const
    {
        return w < b.w;
    }
} e[M];

int pre[N], rank[N];

inline int Find(int u)
{
    while(u != pre[u])
    {
        pre[u] = pre[pre[u]];
        u = pre[u];
    }
    return u;
}

inline bool Union(int u, int v)
{
    u = Find(u), v = Find(v);
    if(u == v) return false;
    if(rank[u] > rank[v])
        pre[v] = u;
    else
    {
        pre[u] = v;
        if(rank[u] == rank[v])
            rank[v] ++;
    }
    return true;
}

int main(int argc, char **argv)
{
    int n = in();
    for(int i = 1; i <= n + 1; i ++)
        pre[i] = i, rank[i] = 1;
    int m = 0;
    for(int i = 1; i <= n; i ++)
        for(int j = i; j <= n; j ++)
            e[m].u = i, e[m].v = j + 1, e[m ++].w = in();
    sort(e, e + m);
    unsigned long long ans = 0;
    int Count = 0;
    for(int i = 0; i < m; i ++)
    {
        if(Union(e[i].u, e[i].v))
        {
            ans += e[i].w;
            if(++ Count == n)
                break ;
        }
    }
    printf("%lld", ans);
    return 0;
}
