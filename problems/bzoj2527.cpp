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
const int INF = 1000000007;
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

const int N = 300005;


struct Meteoric {int l, r, w;} met[N];

vector<int> list[N];
int n, m, K, P[N], num[N];
data bit[N];

inline int lowbit(int x)
{
    return x & (-x);
}

inline data Query(int p)
{
    data r = 0;
    for(; p; p -= lowbit(p))
        r += bit[p];
    return r;
}

inline void ModifyBIT(int p, data x)
{
    for(; p <= m; p += lowbit(p))
        bit[p] += x;
    return ;
}

inline void Modify(int l, int r, data x)
{
    ModifyBIT(l, x), ModifyBIT(r + 1, -x);
    return ;
}

int ans[N], pos[N];
data cur[N], sum[N];
int listL[N], listR[N];

void Solve(int l, int r, int L, int R)
{
    if(R < L) return ;
    if(l == r)
    {
        for(int i = L; i <= R; i ++)
            ans[pos[i]] = l;
        return ;
    }

    int mid = (l + r) >> 1;

    for(int i = l; i <= mid; i ++)
    {
        if(met[i].l <= met[i].r)
            Modify(met[i].l, met[i].r, met[i].w);
        else
        {
            Modify(met[i].l, m, met[i].w);
            Modify(1, met[i].r, met[i].w);
        }
    }

    int numL = 0, numR = 0;

    for(int j = L; j <= R; j ++)
    {
        sum[pos[j]] = 0;
        int t = pos[j], size = list[t].size();
        for(int i = 0; i < size; i ++)
        {
            sum[t] += Query(list[t][i]);
            if(cur[t] + sum[t] >= P[t])
                break ;
        }
        if(cur[t] + sum[t] >= P[t])
            listL[++ numL] = t;
        else
            listR[++ numR] = t, cur[t] += sum[t];
    }

    // Recovery
    // Every level of bisection must be computed from left to right

    for(int i = l; i <= mid; i ++)
    {
        if(met[i].l <= met[i].r)
            Modify(met[i].l, met[i].r, -met[i].w);
        else
        {
            Modify(met[i].l, m, -met[i].w);
            Modify(1,met[i].r, -met[i].w);
        }
    }

    for(int i = 0; i < numL; i ++)
        pos[L + i] = listL[i + 1];
    for(int i = 0; i < numR; i ++)
        pos[L + numL + i] = listR[i + 1];

    Solve(l, mid, L, L + numL - 1);
    Solve(mid + 1, r, L + numL, R);

    return ;
}

int main(int argc, char **argv)
{
    n = in(), m = in();
    for(int i = 1; i <= m; i ++)
        list[num[i] = in()].push_back(i);
    for(int i = 1; i <= n; i ++)
        P[i] = in(), pos[i] = i;
    K = in();
    for(int i = 1; i <= K; i ++)
        met[i].l = in(), met[i].r = in(), met[i].w = in();
    met[++ K].l = 1, met[K].r = m, met[K].w = INF;

    Solve(1, K, 1, n);

    for(int i = 1; i <= n; i ++)
        ans[i] < K ? printf("%d\n", ans[i]) : puts("NIE");

    return 0;
}
