#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

#define     MOD    2147483647 

using   namespace   std;
const   int N = 1e5 + 5;

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

struct Item
{
    bool mark;
    int x, y, x_, l, r, u, d;

    bool operator < (const Item &b) const
    {
        return y < b.y || (y == b.y && x < b.x);
    }
} e[N];

int node[N], C[N][11], dic[N], last[N], n, m, w, K;

inline int lowbit(int x) {return x & (-x);}

inline void Modify(int p, int x)
{
    while(p < N)
        node[p] += x, p += lowbit(p);
    return ;
}

inline int Query(int p)
{
    int r = 0;
    while(p)
        r += node[p], p -= lowbit(p);
    return r;
}

int main()
{
    n = in(), m = in(), w = in();
    for(int i = 1; i <= w; i ++)
        e[i].x = in(), e[i].y = in(), dic[i] = e[i].x;
    K = in();
    for(int i = 0; i <= w; i ++)
    {
        C[i][0] = 1;
        for(int j = 1; j <= min(10, i); j ++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    sort(dic + 1, dic + w + 1);
    int W = unique(dic + 1, dic + w + 1) - dic - 1;
    for(int i = 1; i <= w; i ++)
        e[i].x_ = lower_bound(dic + 1, dic + W + 1, e[i].x) - dic;
    sort(e + 1, e + w + 1);
    int ans = 0;
    e[0].x = e[0].y = e[0].u = e[0].d = e[w + 1].x = e[w + 1].y = -1;
    for(int i = 1; i <= w; i ++) {
        if(e[i].y != e[i - 1].y) e[i].l = 0;
        else e[i].l = e[i - 1].l + 1;
        e[i].d = e[last[e[i].x_]].d + 1;
        last[e[i].x_] = i;
    }
    memset(last, 0, sizeof(last));
    for(int i = w; i >= 1; i --) {
        if(e[i].y != e[i + 1].y) e[i].r = 0;
        else e[i].r = e[i + 1].r + 1;
        e[i].u = e[last[e[i].x_]].u + 1;
        last[e[i].x_] = i;
    }
    for(int i = 1; i <= w; i ++)
    {
        Modify(e[i].x_, C[e[i].u][K] * C[e[i].d + 1][K] - (Query(e[i].x_) - Query(e[i].x_ - 1)));
        if(e[i].y == e[i + 1].y)
            ans += C[e[i].l + 1][K] * C[e[i + 1].r + 1][K] * (Query(e[i + 1].x_ - 1) - Query(e[i].x_));
    }
    printf("%d", ans & MOD);
    return 0;
}
