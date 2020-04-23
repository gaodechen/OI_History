#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 501;

bool vis[N];
int tot, a[N][N], prime[N];

inline void InitTable()
{
    for(int i = 2; i < N; i ++)
    {
        if(vis[i]) continue ;
        prime[tot++] = i;
        for(int j = i * i; j < N; j += i)
            vis[j] = 1;
    }
    return ;
}

int Gauss(int n, int m)
{
    for(int i = 0, k; i < m; i ++)
    {
        for(k = 0; k < n; k ++)
            if(a[k][i]) break ;
        if(k == n) continue ;
        if(k != i) for(int j = 0; j <= m; j ++)
            swap(a[k][j], a[i][j]);
        for(int j = 0; j < n; j ++)
            if(i != j && a[j][i])
                for(int k = 0; k <= m; k ++)
                    a[j][k] ^= a[i][k];
    }
    int r = 0;
    for(int i = 0; i < n; i ++)
    {
        int sum = 0;
        for(int j = 0; j <= m; j ++)
            sum += a[i][j];
        r += sum == 0;
    }
    return r;
}

int main()
{
    int T, n, m;
    InitTable();
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n), m = 0;
        memset(a, 0, sizeof(a));
        for(int i = 0; i < n; i ++)
        {
            long long x;
            scanf("%lld", &x);
            for(int j = 0; j < tot && prime[j] <= x; j ++)
            {
                m = max(j, m);
                while(x % prime[j] == 0)
                    a[j][i] ^= 1, x /= prime[j];
            }
        }
        long long r = ((1LL << Gauss(n, m + 1)) - 1);
        printf("%lld\n", r);
    }
    return 0;
}
