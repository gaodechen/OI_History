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

const int N = 2001;

int v[N], d[N][N];

int main(int argc, char **argv)
{
    int n = in();
    for(int i = 1; i <= n; i ++)
        v[i] = in();
    memset(d, 0, sizeof(d));
    for(int i = 1; i <= n; i ++)
        d[i][i] = v[i];
    for(int i = 1; i <= n; i ++)
        v[i] += v[i - 1];
    for(int l = 2; l <= n; l ++)
    {
        for(int i = 1; i + l - 1 <= n; i ++)
        {
            int j = i + l - 1, x = d[i][i], y = d[j][j];
            d[i][j] = max(d[i + 1][j] + v[j] - v[i] + x, d[i][j - 1] + v[j - 1] - v[i - 1] + y);
        }
    }
    printf("%d\n", d[1][n]);
    return 0;
}
