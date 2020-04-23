#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int S = 256, N = 2e5 + 5;

char s[N];
int n, m, *x, *y;
int v[N], X[N], Y[N], sa[N];

inline bool cmp(int *p, int a, int b, int l)
{
    return p[a] == p[b] && p[(a+l)%n] == p[(b+l)%n];
}

inline void Construct()
{
    x = X, y = Y, m = 256;
    memset(v, 0, sizeof(v));
    for(int i = 0; i < n; i ++) v[x[i]=s[i]] ++;
    for(int i = 1; i < S; i ++) v[i] += v[i-1];
    for(int i = 0; i < n; i ++) sa[--v[x[i]]] = i;
    for(int k = 1; k <= n; k <<= 1)
    {
        int p = 0;
        for(int i = 0; i < m; i ++) v[i] = 0;
        for(int i = 0; i < n; i ++) y[p++] = (sa[i] - k + n) % n;
        for(int i = 0; i < n; i ++) v[x[y[i]]] ++;
        for(int i = 1; i < m; i ++) v[i] += v[i-1];
        for(int i = n - 1; i >= 0; i --) sa[-- v[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1, x[sa[0]] = 0;
        for(int i = 1; i < n; i ++)
        {
            if(cmp(y, sa[i], sa[i-1], k))
                x[sa[i]] = p - 1;
            else
                x[sa[i]] = p ++;
        }
        if(p >= n) break ;
        m = p;
    }
    return ;
}

int main()
{
    scanf("%s", s);
    n = strlen(s);
    Construct();
    for(int i = 0; i < n; i ++)
        printf("%c", s[(sa[i]+n-1)%n]);
    return 0;
}
