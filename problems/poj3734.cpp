#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int MOD = 10007;

struct Matrix
{
    int a[3][3];

    Matrix()
    {
        memset(a, 0, sizeof(a));
    }

    Matrix operator * (const Matrix &b) const
    {
        Matrix c;
        for(int i = 0; i < 3; i ++)
        {
            for(int k = 0; k < 3; k ++) if(a[i][k])
            {
                for(int j = 0; j < 3; j ++) if(b.a[k][j])
                {
                    c.a[i][j] += a[i][k] * b.a[k][j];
                    if(c.a[i][j] >= MOD)
                        c.a[i][j] %= MOD;
                }
            }
        }
        return c;
    }
} A, E;

inline Matrix Pow(Matrix M, int k)
{
    Matrix R = E;
    while(k)
    {
        if(k & 1)
            R = R * M;
        M = M * M;
        k >>= 1;
    }
    return R;
}

int T, n;

int main()
{
    A.a[0][0] = A.a[1][0] = A.a[1][1] = A.a[1][2] = A.a[2][2] = 2;
    A.a[0][1] = A.a[2][1] = E.a[0][0] = E.a[1][1] = E.a[2][2] = 1;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);
        Matrix tmp = Pow(A, n);
        printf("%d\n", tmp.a[0][0] % MOD);
    }
    return 0;
}
