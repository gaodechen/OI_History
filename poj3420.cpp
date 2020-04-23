#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 16;

int n, MOD, cnt[N][N];

struct Matrix
{
    int a[N][N];

    Matrix()
    {
        memset(a, 0, sizeof(a));
    }

    Matrix operator * (const Matrix &b) const
    {
        Matrix c;
        for(int i = 0; i < N; i ++)
        {
            for(int k = 0; k < N; k ++) if(a[i][k]) {
                for(int j = 0; j < N; j ++) if(b.a[k][j])
                {
                    c.a[i][j] += a[i][k] * b.a[k][j];
                    if(c.a[i][j] >= MOD)
                        c.a[i][j] %= MOD;
                }
            }
        }
        return c;
    }
} G;

Matrix Pow(Matrix a, int p)
{
    Matrix r;
    for(int i = 0; i < N; i ++)
        r.a[i][i] = 1;
    while(p)
    {
        if(p & 1)
            r = r * a;
        a = a * a;
        p >>= 1;
    }
    return r;
}

void DFS(int p, int pre, int mask)
{
    if(p == 4)
    {
        cnt[pre][mask] ++;
        return ;
    }
    DFS(p + 1, (mask << 1) | 1, (pre << 1));
    DFS(p + 1, (mask << 1), (pre << 1) | 1);
    if(p < 3)
        DFS(p + 2, (mask << 2) | 3, (pre << 2) | 3);
    return ;
}

int main()
{
    DFS(0, 0, 0);
    memcpy(G.a, cnt, sizeof(cnt));
    while(scanf("%d%d", &n, &MOD) && n)
    {
        if(MOD == 1)
        {
            printf("0\n");
            continue ;
        }
        Matrix ans = Pow(G, n);
        printf("%d\n", ans.a[15][15]);
    }
    return 0;
}
