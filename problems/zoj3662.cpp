#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e3 + 5;
const   int MOD = 1e9 + 7;

inline int gcd(int i, int j)
{
    if(j == 0)
        return i;
    return gcd(j, i % j);
}

int lcm[N][N], num[N];
int n, m, K, d[2][N][N];

int main()
{
    for(int i = 1; i < N; i ++)
        for(int j = 1; j <= i; j ++)
            lcm[i][j] = lcm[j][i] = i / gcd(i, j) * j;
    while(scanf("%d%d%d", &n, &m, &K) == 3)
    {
        int tik = 0;
        for(int i = 1; i <= m; i ++)
            if(m % i == 0)
                num[++tik] = i;
        for(int i = 0; i <= n; i ++)
            for(int j = 1; j <= tik; j ++)
                d[0][i][num[j]] = 0;
        d[0][0][1] = 1;
        for(int k = 1; k <= K; k ++)
        {
            int p = k & 1, q = p ^ 1;
            for(int s = 0; s <= n; s ++)
                for(int x = 1; x <= tik; x ++)
                    d[p][s][num[x]] = 0;
            for(int s = k - 1; s <= n; s ++)
            {
                for(int x = 1; x <= tik; x ++)
                {
                    if(d[q][s][num[x]] == 0)
                        continue ;
                    for(int y = 1; y <= tik; y ++)
                    {
                        int s_ = s + num[y];
                        int x_ = lcm[num[x]][num[y]];
                        if(s_ > n || m % x_)
                            continue ;
                        d[p][s_][x_] += d[q][s][num[x]];
                        if(d[p][s_][x_] >= MOD)
                            d[p][s_][x_] %= MOD;
                    }
                }
            }
        }
        printf("%d\n", d[K&1][n][m]);
    }
    return 0;
}
