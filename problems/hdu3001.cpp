#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
const   int INF = 0x3f3f3f3f;
const   int N = 11, M = 60000;

int n, m, G[N][N], f[N][M], state[N], fac[N], cnt[N][M];

int main(int argc, char **argv)
{
    fac[0] = 1;
    for(int i = 1; i <= 10; i ++)
        fac[i] = fac[i - 1] * 3;
    for(int s = 0; s <= fac[10]; s ++)
    {
        int s_ = s;
        for(int i = 0; i <= 10; i ++)
            cnt[i][s] = s_ % 3, s_ /= 3;
    }
    while(scanf("%d%d", &n, &m) == 2)
    {
        int ans = INF;
        memset(f, INF, sizeof(f));
        memset(G, INF, sizeof(G));
        for(int i = 0; i < m; i ++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u --, v --;
            G[u][v] = G[v][u] = min(G[u][v], w);
        }
        for(int i = 0; i < n; i ++)
            f[i][fac[i]] = 0;
        for(int s = 0; s < fac[n]; s ++)
        {
            bool tmp = 1;
            for(int i = 0; i < n; i ++)
            {
                if(cnt[i][s] == 0) tmp = 0;
                for(int j = 0; j < n; j ++)
                {
                    if(i == j || G[i][j] == INF || f[i][s] == INF || cnt[j][s] > 1) continue ;
                    f[j][s + fac[j]] = min(f[j][s + fac[j]], f[i][s] + G[i][j]);
                }
            }
            if(tmp) for(int i = 0; i < n; i ++)
                ans = min(ans, f[i][s]);
        }
        printf("%d\n", ans == INF ? -1 : ans);
    }
    return 0;
}
