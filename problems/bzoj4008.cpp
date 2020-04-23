#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 221;

int T, n, r, a[N], d[N];
double p[N], pow[N][N], f[N][N];

int main()
{
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d%d", &n, &r);
        memset(f, 0, sizeof(f));
        for(int i = 1; i <= n; i ++)
            scanf("%lf%d", &p[i], &d[i]);
        for(int i = 1; i <= n; i ++)
        {
            pow[i][0] = 1;
            for(int j = 1; j <= r; j ++)
                pow[i][j] = pow[i][j-1] * (1.0 - p[i]);
        }
        f[0][r] = 1;
        double ans = 0;
        for(int i = 0; i <= n; i ++)
        {
            for(int j = 0; j <= r; j ++)
            {
                f[i+1][j] += f[i][j] * pow[i+1][j];
                if(j >= 1)
                {
                    double tmp = f[i][j] * (1 - pow[i+1][j]);
                    f[i+1][j-1] += tmp, ans += tmp * d[i+1];
                }
            }
        }
        printf("%.10lf\n", ans);
    }
    return 0;
}

