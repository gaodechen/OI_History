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
const int INF = 0x3f3f3f3f;
typedef pair<int, int> Pair;
typedef long long data;

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

const int N = 1e4 + 5;

int m, L, W;

struct Task
{
    int l, r, w;

    bool operator < (const Task &b) const
    {
        return l < b.l;
    }
} e[N];

struct Item
{
    int r, t;

    bool operator < (const Item &b) const
    {
        return r > b.r;
    }
};

inline bool Check(int k)
{
    priority_queue<Item> q;
    for(int i = 1, p = 0; i <= L; i ++)
    {
        while(e[p].l < i && p < m)
            q.push((Item) {e[p].r, e[p].w}), p ++;
        int cur = k;
        while(!q.empty() && cur)
        {
            Item t = q.top(); q.pop();
            if(t.r < i) return false;
            if(t.t > cur) t.t -= cur, cur = 0, q.push(t);
            else cur -= t.t;
        }
        if(p == m && q.empty()) return true;
    }
    return q.empty();
}

int main(int argc, char **argv)
{
#define LOCAL
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T = in();
    while(T --)
    {
        m = in(), L = -1, W = 0;
        for(int i = 0; i < m; i ++)
        {
            e[i].l = in(), e[i].r = in(), e[i].w = in();
            if(e[i].r > L) L = e[i].r; W += e[i].w;
        }
        sort(e, e + m);
        int l = 0, r = W;
        while(l < r)
        {
            int mid = (l + r) >> 1;
            if(Check(mid))
                r = mid;
            else
                l = mid + 1;
        }
        printf("%d\n", l);
    }
    return 0;
}
