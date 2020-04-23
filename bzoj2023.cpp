#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using namespace	std;
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

const int T = 1001, N = 1000001;
const int MOD = 1000000;

int a[T], d[N], sum[N];

inline int M(int x)
{
    if(x < 0) x %= MOD, x += MOD;
    return x >= MOD ? x % MOD : x;
}

int main(int argc, char **argv)
{
    int t = in(), n = in(), S = in(), B = in();
    for(int i = 1; i <= n; i ++)
        a[in()] ++;
    for(int i = 0; i <= n; i ++)
        sum[i] = 1;
    int total = 0;
    for(int k = 1; k <= t; k ++)
    {
        total += a[k];
        for(int v = total; v >= 0; v --)
        {
            if(v - a[k] - 1 >= 0)
                d[v] = M(sum[v] - sum[v - a[k] - 1]);
            else
                d[v] = sum[v];
        }
        for(int v = 1; v <= n; v ++)
            sum[v] = d[v] + sum[v - 1], sum[v] = M(sum[v]);
    }
    int ans = 0;
    for(int i = S; i <= B; i ++)
        ans = M(ans + d[i]);
    printf("%d\n", ans);
    return 0;
}
