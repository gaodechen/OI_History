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

const int N = 5001;

int n, C[N], d[N], sum[N];

int main(int argc, char **argv)
{
    n = in();
    for(int i = 1; i <= n; i ++)
        sum[i] = (d[i] = C[i] = in()) + sum[i - 1];
    for(int i = 2; i <= n; i ++)
        for(int j = 1; j + i - 1 <= n; j ++)
            d[j] = sum[j + i - 1] - sum[j - 1] - min(d[j], d[j + 1]);
    printf("%d", d[1]);
    return 0;
}

