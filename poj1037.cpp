#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;

bool used[21];
long long f[21][21][2];

int main()
{
    f[1][1][0] = f[1][1][1] = 1;
    for(int i = 2; i <= 20; i ++) {
        for(int k = 1; k <= i; k ++) {
            for(int j = 1; j < k; j ++)
                f[i][k][0] += f[i - 1][j][1];
            for(int j = k; j <= i; j ++)
                f[i][k][1] += f[i - 1][j][0];
        }
    }
    int T, n; long long m;
    scanf("%d", &T);
    while(T --)
    {
        memset(used, 0, sizeof(used));
        scanf("%d%lld", &n, &m);
        bool flag = false; int l, r, j;
        for(int i = 1; i <= n && !flag; i ++)
        {
            for(j = 0; j <= 1; j ++)
            {
                m -= f[n][i][j];
                if(m <= 0)
                {
                    m += f[n][i][j], used[i] = 1;
                    printf("%d", i);
                    if(j == 0) l = 1, r = i - 1;
                    else l = i + 1, r = n;
                    flag = true, j ^= 1;
                    break ;
                }
            }
        }
        for(int len = n - 1; len >= 1; len --)
        {
            int cnt = 0;
            for(int i = 1; i < l; i ++)
                cnt += !used[i];
            for(int i = l; i <= r; i ++) if(!used[i])
            {
                m -= f[len][++ cnt][j];
                if(m <= 0)
                {
                    m += f[len][cnt][j];
                    used[i] = 1;
                    printf(" %d", i);
                    if(j == 0) l = 1, r = i - 1;
                    else l = i + 1, r = n;
                    j ^= 1; break ;
                }
            }
        }
        puts("");
    }
    return 0;
}
