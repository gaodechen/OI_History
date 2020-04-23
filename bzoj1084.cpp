#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const   int N = 101;

int n, m, K;

inline void Interface1()
{
    int a[N], f[N] = {0}, g[N] = {0};
    for(int j = 1; j <= n; j ++)
        scanf("%d", &a[j]);
    for(int i = 1; i <= n; i ++)
    {
        f[i] = max(f[i - 1] + a[i], a[i]);
        g[i] = max(g[i - 1], f[i]);
    }
    for(int i = 2; i <= K; i ++)
    {
        for(int j = 1; j <= n; j ++)
            f[j] = max(f[j - 1], g[j - 1]) + a[j];
        for(int j = 1; j <= n; j ++)
            g[j] = max(g[j - 1], f[j]);
    }
    cout << g[n] << endl;
    return ;
}

int f[N][N][11], A[N], B[N];

inline void Interface2()
{
    memset(f, 0, sizeof(f));
    for(int j = 1; j <= n; j ++)
        scanf("%d%d", &A[j], &B[j]);
    for(int j = 2; j <= n; j ++)
        A[j] += A[j-1], B[j] += B[j-1];
    for(int k = 1; k <= K; k ++)
    {
        for(int i = 1; i <= n; i ++)
        {
            for(int j = 1; j <= n; j ++)
            {
                f[i][j][k] = max(f[i - 1][j][k], f[i][j - 1][k]);
                for(int a = 0; a < i; a ++)
                    f[i][j][k] = max(f[i][j][k], f[a][j][k - 1] + A[i] - A[a]);
                for(int b = 0; b < j; b ++)
                    f[i][j][k] = max(f[i][j][k], f[i][b][k - 1] + B[j] - B[b]);
                if(i == j) for(int a = 0; a < i; a ++)
                    f[i][j][k] = max(f[i][j][k], f[a][a][k - 1] + A[i] - A[a] + B[j] - B[a]);
            }
        }
    }
    cout << f[n][n][K] << endl;
    return ;
}

int main(int argc, char **argv)
{
    scanf("%d%d%d", &n, &m, &K);
    if(m == 1)
        Interface1();
    else
        Interface2();
    return 0;
}
