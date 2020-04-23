#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long data;
const int N = 220;
const int M = 100100;
const data BASE = 233;
const data BASE2 = 131;

char *s[N], S[M];
int n, m, len[N], maxLen, P = 1;

data f[N][N], G[N][N], g[N][N];
data pow[M], pow2[M], *hash[N], *hash2[N], HASH[M], HASH2[M];

inline data H(data *hash, int l, int r)
{
    return hash[r] - hash[l - 1] * pow[r - l + 1];
}

inline data H2(data *hash, int l, int r)
{
    return hash[r] - hash[l - 1] * pow2[r - l + 1];
}

inline int F(int x, int y)
{
    for(int i = min(len[x], len[y]) - (len[y] <= len[x]); i >= 0; i --)
        if(H(hash[x], len[x] - i, len[x] - 1) == H(hash[y], 0, i - 1))
            if(H2(hash2[x], len[x] - i, len[x] - 1) == H2(hash2[y], 0, i - 1))
                return i;
    return 0;
}

int main(int argc, char **argv)
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%s", S + P);
        s[i] = S + P, hash[i] = HASH + P, hash2[i] = HASH2 + P;
        len[i] = strlen(s[i]), maxLen = max(maxLen, len[i]);
        P ++, P += len[i];
        for(int j = 0; j < len[i]; j ++)
        {
            hash[i][j] = hash[i][j - 1] * BASE + s[i][j];
            hash2[i][j] = hash2[i][j - 1] * BASE2 + s[i][j];
        }
    }

    pow[0] = pow2[0] = 1;
    for(int i = 1; i <= maxLen; i ++)
    {
        pow[i] = pow[i - 1] * BASE;
        pow2[i] = pow2[i - 1] * BASE2;
    }

    memset(f, 0x3f, sizeof(f));
    memset(G, 0x3f, sizeof(G));

    for(int i = 1; i <= n; i ++)
    {
        f[0][i] = len[i], G[i][i] = 0;
        for(int j = 1; j <= n; j ++)
            f[i][j] = len[j] - F(i, j);
    }

    for(int T = 0; (1 << T) <= m; T ++)
    {
        if(T != 0)
        {
            memset(g, 0x3f, sizeof(g));
            for(int k = 0; k <= n; k ++)
                for(int i = 0; i <= n; i ++)
                    for(int j = 0; j <= n; j ++)
                        g[i][j] = min(g[i][j], f[i][k] + f[k][j]);
            memcpy(f, g, sizeof(g));
        }
        if(m & (1 << T))
        {
            memset(g, 0x3f, sizeof(g));
            for(int k = 0; k <= n; k ++)
                for(int i = 0; i <= n; i ++)
                    for(int j = 0; j <= n; j ++)
                        g[i][j] = min(g[i][j], f[i][k] + G[k][j]);
            memcpy(G, g, sizeof(G));
        }
    }

    data r = 0x3f3f3f3f3f3f3f3fLL;
    for(int i = 1; i <= n; i ++)
        r = min(r, G[0][i]);
    // printf("%I64d", r);
    printf("%lld", r);
    // cout << r << endl;

    return 0;
}

