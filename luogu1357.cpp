#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long data;
const   int MOD = 1000000007;
const   int N = 32;

data n;
int m, k, tot, R, C;
bool legal[N];

struct Matrix
{
    data a[N][N];

    Matrix() {memset(a, 0, sizeof(a));}

    Matrix operator * (const Matrix &b) const
    {
        Matrix c;
        for(int i = 0; i < R; i ++)
            for(int k = 0; k < R; k ++) if(a[i][k])
                for(int j = 0; j < C; j ++) if(b.a[k][j]) {
                    c.a[i][j] += (a[i][k] * b.a[k][j]) % MOD;
                    // Don't forget to MOD here!
                    if(c.a[i][j] >= MOD) c.a[i][j] %= MOD;
                }
        return c;
    }
} A, E;

inline Matrix pow(Matrix a, data k)
{
    Matrix r = E;
    while(k)
    {
        if(k & 1) r = r * a;
        a = a * a, k >>= 1LL;
    }
    return r;
}

inline bool Judge(int s)
{
    int r = 0;
    while(s != 0)
        s &= (s - 1), r ++;
    return r <= k;
}

int main(int argc, char **argv)
{
    for(int i = 0; i < N; i ++)
        E.a[i][i] = 1;
    cin >> n >> m >> k;
    const int S = (1 << m);
    R = C = S;
    for(int s = 0; s < S; s ++)
        legal[s] = Judge(s);
    for(int s = 0; s < S; s ++) if(legal[s])
    {
        int s1 = (s << 1) & (S - 1), s2 = ((s << 1) & (S - 1)) | 1;
        if(legal[s1]) A.a[s1][s] = 1;
        if(legal[s2]) A.a[s2][s] = 1;
    }
    data r = 0;
    Matrix P = pow(A, n);
    for(int i = 0; i < S; i ++)
    {
        if(!legal[i]) continue ;
        Matrix M;
        M.a[0][i] = 1, M = M * P;
        r = (r + M.a[0][i]) % MOD;
    }
    cout << r << endl;
    return 0;
}
