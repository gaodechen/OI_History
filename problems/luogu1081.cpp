#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <set>
#include    <map>

using   namespace   std;
typedef long long   data;
const   data INF = 6000000000;
const   int N = 100001, K = 17;

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

struct Item
{
    data d, h;

    bool operator < (const Item &b) const
    {
        return d < b.d || (d == b.d && h < b.h);
    }
} e[4];

int n, q, h[N];
int minPos[N], secPos[N];
int minPath[N], secPath[N];
data p[N][K], f[N][K], g[N][K];
set<data> S; map<data, int> M;

inline void Query(int s, int x, data &a, data &b)
{
    a = 0, b = 0;
    for(int i = K - 1; i >= 0; i --)
    {
        if(p[s][i] && f[s][i] + g[s][i] <= x)
        {
            a += f[s][i], b += g[s][i];
            x -= f[s][i] + g[s][i];
            s = p[s][i];
        }
    }
    return ;
}

int main()
{
    n = in();
    for(int i = 1; i <= n; i ++)
        M[h[i]=in()] = i;
    S.insert(-INF), S.insert(INF);
    for(int i = n; i >= 1; i --)
    {
        S.insert(h[i]);
        e[0].h = *-- S.lower_bound(h[i]);
        e[1].h = *S.upper_bound(h[i]);
        e[2].h = e[0].h == -INF ? -INF : *-- S.lower_bound(e[0].h);
        e[3].h = e[1].h == INF ? INF : *S.upper_bound(e[1].h);
        for(int j = 0; j < 4; j ++)
            e[j].d = abs(h[i] - e[j].h);
        sort(e, e + 4);
        minPath[i] = e[0].d, minPos[i] = M[e[0].h];
        secPath[i] = e[1].d, secPos[i] = M[e[1].h];
    }
    for(int i = 1; i <= n; i ++) if(secPos[i])
        p[i][0] = secPos[i], f[i][0] = secPath[i];
    for(int i = 1; i <= n; i ++) if(minPos[i])
        p[i][1] = minPos[p[i][0]], f[i][1] = f[i][0], g[i][1] = minPath[p[i][0]];
    for(int j = 2; j < K; j ++)
    {
        for(int i = 1; i <= n; i ++)
        {
            p[i][j] = p[p[i][j-1]][j-1];
            f[i][j] = f[i][j-1] + f[p[i][j-1]][j-1];
            g[i][j] = g[i][j-1] + g[p[i][j-1]][j-1];
        }
    }
    int s, k = 0, x = in();
    double r = 1e18; data a, b;
    for(int i = 1; i <= n; i ++)
    {
        Query(i, x, a, b);
        double t = (double) a / b;
        if(b && (t < r || (r == t && h[i] > h[k])))
            r = t, k = i;
    }
    printf("%d\n", k);
    q = in();
    while(q --)
    {
        s = in(), x = in();
        Query(s, x, a, b);
        printf("%lld %lld\n", a, b);
    }
    return 0;
}
