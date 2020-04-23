#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int INF = 0x3f3f3f3f;
const   int N = 1e4 + 5;
const   int M = 1e3 + 5;

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

int n, m, k; bool A[N];
int X[N], Y[N], low[N], up[N], f[N][M];

int main(int argc, char **argv)
{
    n = in(), m = in(), k = in();
    for(int i = 0; i < n; i ++)
        X[i] = in(), Y[i] = in();
    for(int i = 0; i <= n; i ++)
        low[i] = 1, up[i] = m;
    for(int i = 0, x; i < k; i ++)
        low[x = in()] = in() + 1, up[x] = in() - 1, A[x] = 1;
    memset(f, INF, sizeof(f));
    for(int i = low[0]; i <= up[0]; i ++)
        f[0][i] = 0;
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= m; j ++)
        {
            if(j - X[i - 1] >= low[i - 1] && j - X[i - 1] <= up[i - 1])
                f[i][j] = min(f[i][j], f[i - 1][j - X[i - 1]] + 1);
            if(j - X[i - 1] > 0)
                f[i][j] = min(f[i][j], f[i][j - X[i - 1]] + 1);
        }
        for(int j = m - X[i - 1]; j <= m; j ++)
            f[i][m] = min(f[i][m], min(f[i - 1][j], f[i][j]) + 1);
        for(int j = 1; j <= m - Y[i - 1]; j ++)
            f[i][j] = min(f[i][j], f[i - 1][j + Y[i - 1]]);
        for(int j = 1; j < low[i]; j ++) f[i][j] = INF;
        for(int j = up[i] + 1; j <= m; j ++) f[i][j] = INF;
        bool flag = false;
        for(int j = 1; j <= m; j ++) {
            if(f[i][j] < INF) {
                flag = true; break ;
            }
        }
        if(!flag) break ;
    }
    int ans = INF;
    for(int i = 1; i <= m; i ++)
        ans = min(ans, f[n][i]);
    if(ans < INF) {
        printf("1\n%d\n", ans);
        return 0;
    }
    for(int i = n - 1; i >= 0; i --) {
        for(int j = low[i]; j <= up[i]; j ++) {
            if(f[i][j] < INF) {
                int r = 0;
                for(int k = 0; k <= i; k ++)
                    r += A[k];
                printf("0\n%d\n", r);
                return 0;
            }
        }
    }
    return 0;
}
