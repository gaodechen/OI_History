#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 50, MOD = 10000;

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

int n, m, S, T, K, F, p[20], mark[12][N];

struct Matrix
{
    int a[N][N];

    Matrix() {memset(a, 0, sizeof(a));}

    Matrix operator * (const Matrix &b) const
    {
        Matrix c;
        for(int i = 0; i < n; i ++)
            for(int k = 0; k < n; k ++) if(a[i][k])
                for(int j = 0; j < n; j ++) if(b.a[k][j]) {
                    c.a[i][j] += (a[i][k] * b.a[k][j]) % MOD;
                    if(c.a[i][j] >= MOD) c.a[i][j] %= MOD;
                }
        return c;
    }
} E, M[12];

inline Matrix pow(Matrix a, int k)
{
    Matrix r = E;
    while(k)
    {
        if(k & 1) r = r * a;
        a = a * a, k >>= 1;
    }
    return r;
}

int main(int argc, char **argv)
{
    n = in(), m = in(), S = in(), T = in(), K = in();
    for(int i = 0; i < n; i ++)
        E.a[i][i] = 1;
    for(int i = 0; i < m; i ++)
    {
        int u = in(), v = in();
        for(int j = 0; j < 12; j ++)
            M[j].a[u][v] = M[j].a[v][u] = 1;
    }
    F = in();
    for(int i = 0; i < F; i ++)
    {
        int t = in();
        for(int j = 0; j < t; j ++) p[j] = in();
        for(int j = 0; j < 12; j ++) mark[j][p[j % t]] = 1;
    }
    for(int j = 0; j < 12; j ++)
    {
        for(int i = 0; i < n; i ++) if(mark[j][i])
        {
            for(int k = 0; k < n; k ++) M[j].a[i][k] = 0;
            for(int k = 0; k < n; k ++) M[(j + 11) % 12].a[k][i] = 0;
        }
    }
    for(int i = 1; i < 12; i ++)
        M[i] = M[i - 1] * M[i];
    Matrix r;
    r = pow(M[11], K / 12);
    if(K % 12) r = r * M[K % 12 - 1];
    printf("%d", r.a[S][T]);
    return 0;
}
