#include    <cstdio>
#include    <cstring>
#include    <cstring>

#define     rep(i, S, T)       for(int i = S; i <= T; i ++)

using   namespace   std;
const   int N = 1001, INF = 0x3f3f3f3f;

int T, n, B, a[N], b[N], f[N][1<<8][17];

inline int p(int x) {return x + 8;}
inline void g(int &x, int y) {if(x > y) x = y;}

int main()
{
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++)
            scanf("%d%d", &a[i], &b[i]);
        memset(f, INF, sizeof(f));
        f[1][0][p(-1)] = 0;
        rep(i, 1, n) rep(s, 0, (1 << 8) - 1) rep(k, -8, 7)
        {
            if(f[i][s][p(k)] < INF && i + k >= 0 && i + k <= n)
            {
                if(s & 1)
                    g(f[i+1][s>>1][p(k-1)], f[i][s][p(k)]);
                else
                {
                    int tmp = INF;
                    for(int l = 0; l <= b[i] && i + l <= n; l ++)
                    {
                        if((s & (1 << l)) == 0)
                        {
                            g(tmp, i + l + b[i+l]);
                            if(i + l > tmp)
                                break ;
                            int x = (i + k == 0 ? 0 : a[i+k] ^ a[i+l]);
                            g(f[i][s|(1<<l)][p(l)], x + f[i][s][p(k)]);
                        }
                    }
                }
            }
        }
        int ans = INF;
        for(int i = -8; i <= 0; i ++)
            g(ans, f[n][1][p(i)]);
        printf("%d\n", ans);
    }
    return 0;
}
