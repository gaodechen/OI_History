#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 2e4 + 5;

int *x, *y, *rank, a[N], v[N];
int X[N], Y[N], sa[N], height[N];

inline bool cmp(int *p, int a, int b, int l)
{
    return p[a] == p[b] && p[a + l] == p[b + l];
}

inline void Construct(int n, int m)
{
    x = X, y = Y;
    memset(v, 0, sizeof(v));
    for(int i = 0; i < n; i ++) v[x[i] = a[i]] ++;
    for(int i = 1; i < m; i ++) v[i] += v[i - 1];
    for(int i = 0; i < n; i ++) sa[-- v[x[i]]] = i;
    for(int k = 1; k <= n; k <<= 1)
    {
        int p = 0;
        for(int i = 0; i < m; i ++) v[i] = 0;
        for(int i = n - k; i < n; i ++) y[p ++] = i;
        for(int i = 0; i < n; i ++) if(sa[i] >= k) y[p ++] = sa[i] - k;
        for(int i = 0; i < p; i ++) v[x[y[i]]] ++;
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
    return (void) (rank = x);
}

// height[i] = LCP(sa[i], sa[i - 1])
// h[i] = LCP(i, sa[rank[i] - 1])
// h[i] >= h[i - 1] - 1
// LCP(i, sa[rank[i] - 1]) >= LCP(i - 1, sa[rank[i - 1] - 1]) - 1
// Clearly!

inline void Compute(int n)
{
    int p, k = 0;
    for(int i = 0; i < n; i ++)
    {
        k = k > 0 ? k - 1 : 0, p = sa[rank[i] - 1];
        while(a[i + k] == a[p + k]) k ++;
        height[rank[i]] = k;
    }
    return ;
}

inline bool Judge(int k, int n)
{
    int l = sa[0], r = sa[0];
    for(int i = 1; i <= n; i ++)
    {
        if(height[i] >= k)
        {
            l = min(l, sa[i]), r = max(r, sa[i]);
            if(r - l >= k) return 1;
            // The length of non-intersect >= k!
        }
        else l = r = sa[i];
    }
    return 0;
}

int main()
{
    int n;
    while(scanf("%d", &n) && n)
    {
        for(int i = 0; i < n; i ++)
            scanf("%d", &a[i]);
        for(int i = 0; i < n - 1; i ++)
            a[i] = a[i + 1] - a[i] + 90;
        a[-- n] = 0;
        Construct(n + 1, 200);
        Compute(n);
        int l = 1, r = n + 1;
        while(l < r)
        {
            int mid = (l + r + 1) >> 1;
            if(Judge(mid, n))
                l = mid;
            else
                r = mid - 1;
        }
        if(l < 4) puts("0");
        else printf("%d\n", l + 1);
    }
    return 0;
}
