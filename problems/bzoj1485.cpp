#include    <cstdio>
#include    <iostream>

using   namespace   std;
const   int N = 1e6 + 5;

bool mark[N+N];
int n, tot, MOD, prime[N], cnt[N], cur[N+N];

inline void InitPrime(int q)
{
    for(int i = 2; i < q; i ++)
    {
        if(!mark[i])
            cur[i] = tot, prime[tot++] = i;
        for(int j = 0; j < tot; j ++)
        {
            int tmp = i * prime[j];
            if(tmp >= q)
                break ;
            mark[tmp] = 1, cur[tmp] = j;
            if(i % prime[j] == 0)
                break ;
        }
    }
    return ;
}

inline void Factorize(int s, int k)
{
    while(s != 1)
    {
        cnt[cur[s]] += k;
        s /= prime[cur[s]];
    }
    return ;
}

int main()
{
    scanf("%d%d", &n, &MOD);
    InitPrime(n + n);
    for(int i = n + 2; i <= n + n; i ++)
        Factorize(i, 1);
    for(int i = 2; i <= n; i ++)
        Factorize(i, -1);
    long long ans = 1;
    for(int i = 0; i < tot; i ++)
    {
        while(cnt[i] --)
        {
            ans = (ans * prime[i]) % MOD;
            if(ans >= MOD)
                ans %= MOD;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
