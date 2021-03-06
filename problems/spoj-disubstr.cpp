#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e3 + 1;

char s[N];
int v[N], sa[N], X[N], Y[N];
int *x, *y, *rank, height[N];

inline bool cmp(int *p, int a, int b, int l)
{
    return p[a] == p[b] && p[a + l] == p[b + l];
}

inline void Construct(int n, int m)
{
    x = X, y = Y;

    for(int i = 0; i < m; i ++) v[i] = 0;
    for(int i = 0; i < n; i ++) v[x[i] = s[i]] ++;
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
    return (void) (rank = x);
}

inline void InitHeight(int n)
{
	int k = 0;
    for(int i = 0; i < n; i ++)
        rank[sa[i]] = i;
    // LCP(i, rank[i] - 1) >= LCP(i - 1, rank[i - 1] - 1) - 1
	for(int i = 0; i < n; i++)
	{
		if(k != 0) k--;
		if(!rank[i]) continue;
		int j = sa[rank[i] - 1];
		while(s[i + k] == s[j + k]) k ++;
		height[rank[i]] = k;
	}
    return ;
}
int main(int argc, char **argv)
{
    int T, n;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%s", s);
        n = strlen(s);
        Construct(n, 256);
        InitHeight(n);
        int r = n * (n + 1) / 2;
        for(int i = 1; i < n; i ++)
            r -= height[i];
        printf("%d\n", r);
    }
    return 0;
}
