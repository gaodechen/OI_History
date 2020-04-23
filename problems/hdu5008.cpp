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
typedef long long data;
const int N = 100010;

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

char S[N];
int A[N], *x, *y, *Rank, X[N], Y[N], v[N], sa[N], height[N];

inline bool cmp(int *p, int a, int b, int l)
{
    return p[a] == p[b] && p[a + l] == p[b + l];
}

inline void Construct(int n, int m)
{
    x = X, y = Y;

    for(int i = 0; i < m; i ++) v[i] = 0;
    for(int i = 0; i < n; i ++) v[x[i] = A[i]] ++;
    for(int i = 1; i < m; i ++) v[i] += v[i - 1];
    for(int i = 0; i < n; i ++) sa[-- v[x[i]]] = i;

    for(int k = 1; k <= n; k <<= 1)
    {
        int p = 0;
        for(int i = n - 1; i >= n - k; i --) y[p ++] = i;
        for(int i = 0; i < n; i ++) if(sa[i] >= k) y[p ++] = sa[i] - k;

        for(int i = 0; i < m; i ++) v[i] = 0;
        for(int i = 0; i < n; i ++) v[x[y[i]]] ++;
        for(int i = 1; i < m; i ++) v[i] += v[i - 1];
        for(int i = n - 1; i >= 0; i --) sa[-- v[x[y[i]]]] = y[i];

        swap(x, y), p = 1, x[sa[0]] = 0;
        for(int i = 1; i < n; i ++)
        {
            if(cmp(y, sa[i], sa[i - 1], k)) x[sa[i]] = p - 1;
            else x[sa[i]] = p ++;
        }

        if((m = p) >= n) break ;
    }

    return (void) (Rank = x);
}

// LCP(i, j) = the length of LCP between sa[i] and sa[j]
// height[i] = LCP(i - 1, i)
// H[i] = height[rank[i]] = LCP(rank[i] - 1, rank[i])
// H[i] >= H[i  - 1] - 1

inline void InitHeight(int n)
{
    int k = 0;
    for(int i = 0; i < n; i ++)
        Rank[sa[i]] = i;
    for(int i = 0; i < n; i ++)
    {
        if(k != 0) k --;
        if(!Rank[i]) continue ;
        int j = sa[Rank[i] - 1];
        while(S[i + k] == S[j + k]) k ++;
        height[Rank[i]] = k;
    }
    return ;
}

int E[N];
data sum[N];

inline void InitRMQ(int *a, int (*d)[20], int n)
{
    for(int i = 0; i < n; i ++)
        d[i][0] = a[i];
    for(int i = 1; i <= E[n]; i ++)
        for(int j = 0; j + (1 << i) - 1 < n; j ++)
            d[j][i] = min(d[j][i - 1], d[j + (1 << (i - 1))][i - 1]);
    return ;
}

inline int RMQ(int (*d)[20], int l, int r)
{
    int k = E[r - l + 1];
    return min(d[l][k], d[r - (1 << k) + 1][k]);
}

int dSA[N][20], dH[N][20];

inline int LCP(int i, int j)
{
    i = Rank[i], j = Rank[j];
    if(i > j) swap(i, j);
    return RMQ(dH, i + 1, j);
}

int main(int argc, char **argv)
{
    E[0] = -1;
    for(int i = 1; i < N; i ++)
        E[i] = E[i - 1] + ((i & (i - 1)) == 0);
    while(scanf("%s", S) == 1)
    {
        int n = strlen(S);
        for(int i = 0; i < n; i ++)
            A[i] = S[i] - 'a';
        Construct(n, 27);
        InitHeight(n);
        InitRMQ(sa, dSA, n);
        InitRMQ(height, dH, n);
        for(int i = 0; i < n; i ++)
            sum[i] = sum[i - 1] + n - height[i] - sa[i];
        int Q = in();
        data L = 0, R = 0;
        while(Q --)
        {
            data v;
            scanf("%I64d", &v);
            data k = (v ^ L ^ R) + 1;
            if(k > sum[n - 1])
            {
                puts("0 0"),  L = R = 0;
                continue ;
            }
            int p = lower_bound(sum, sum + n, k) - sum;
            if(p) k -= sum[p - 1];
            int len = height[p] + k;

            /*
            lSide is p as sum exactly >= k here,
            the substring must be sa[i] or after sa[i]

            int l = 0, r = p, lSide, rSide;
            while(l < r)
            {
                int mid = (l + r) >> 1;
                if(sa[mid] + len - 1 < n && LCP(mid, p) >= len)
                    r = mid;
                else
                    l = mid + 1;
            } */
            int l = p, r = n - 1;
            while(l < r)
            {
                int mid = (l + r + 1) >> 1;
                if(sa[mid] + len - 1 < n && LCP(sa[mid], sa[p]) >= len)
                    l = mid;
                else
                    r = mid - 1;
            }

            p = RMQ(dSA, p, l);
            L = p + 1, R = p + len;
            printf("%I64d %I64d\n", L, R);
        }
    }
    return 0;
}
