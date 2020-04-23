#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 100001;

int Q, E[N];

struct SuffixArray
{
    char S[N];
    int *Rank, A[N], X[N], Y[N], v[N];
    int sa[N], height[N], d[N][20];

    inline bool cmp(int *p, int a, int b, int l)
    {
        return p[a] == p[b] && p[a + l] == p[b + l];
    }

    inline void InitSA(int n, int m)
    {
        int *x = X, *y = Y;

        for(int i = 0; i < m; i ++) v[i] = 0;
        for(int i = 0; i < n; i ++) v[x[i] = A[i]] ++;
        for(int i = 1; i < m; i ++) v[i] += v[i - 1];
        for(int i = 0; i < n; i ++) sa[-- v[x[i]]] = i;

        for(int k = 1; k <= n; k <<= 1)
        {
            int p = 0;
            for(int i = n - 1; i >= n - k; i --) y[p ++] = i;
            for(int i = 0; i < n; i ++) if(sa[i] >= k) y[p ++] = sa[i] - k;

            for(int i = 0; i < m; i ++) v[i] = 0;
            for(int i = 0; i < n; i ++) v[x[y[i]]] ++;
            for(int i = 1; i < m; i ++) v[i] += v[i - 1];
            for(int i = n - 1; i >= 0; i --) sa[-- v[x[y[i]]]] = y[i];

            swap(x, y), p = 1, x[sa[0]] = 0;
            for(int i = 1; i < n; i ++)
            {
                if(cmp(y,sa[i], sa[i - 1], k)) x[sa[i]] = p - 1;
                else x[sa[i]] = p ++;
            }

            if((m = p) >= n) break ;
        }

        return (void) (Rank = x);
    }

    inline void InitHeight(int n)
    {
        int k = 0;
        for(int i = 0; i < n; i ++)
            Rank[sa[i]] = i;
        for(int i = 0; i < n; i ++)
        {
            if(k != 0) k --;
            if(!Rank[i]) continue ;
            int j = sa[Rank[i] - 1];
            while(S[i + k] == S[j + k]) k ++;
            height[Rank[i]] = k;
        }
        return ;
    }

    inline void InitRMQ(int n)
    {
        for(int i = 0; i < n; i ++)
            d[i][0] = height[i];
        for(int i = 1; i <= E[n]; i ++)
            for(int j = 0; j + (1 << i) - 1 < n; j ++)
                d[j][i] = min(d[j][i - 1], d[j + (1 << (i - 1))][i - 1]);
        return ;
    }

    inline int RMQ(int l, int r)
    {
        int k = E[r - l + 1];
        return min(d[l][k], d[r - (1 << k) + 1][k]);
    }

    inline int LCP(int a, int b)
    {
        a = Rank[a], b = Rank[b];
        if(a > b) swap(a, b);
        return RMQ(a + 1, b);
    }
} A, B;

int d[N][20];

inline void InitRMQ(int n)
{
    for(int i = 0; i < n; i ++)
        d[i][0] = A.Rank[i];
    for(int j = 1; (1 << j) <= n; j ++)
        for(int i = 0; i + (1 << j) - 1 < n; i ++)
            d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
    return ;
}

inline int RMQ(int l, int r)
{
    int k = E[r - l + 1];
    return min(d[l][k], d[r - (1 << k) + 1][k]);
}

int main(int argc, char **argv)
{
#ifdef LOCAL
    freopen("in", "r", stdin);
    // freopen("my.out", "w", stdout);
#endif
    E[0] = -1;
    for(int i = 1; i < N; i ++)
        E[i] = E[i - 1] + ((i & (i - 1)) == 0);
    while(scanf("%s", A.S) == 1)
    {
        if(A.S[0] == '#') break ;
        int n = strlen(A.S);
        memset(B.S, 0, sizeof(B.S));
        memset(B.A, 0, sizeof(B.A));
        memset(B.X, 0, sizeof(B.X));
        memset(A.X, 0, sizeof(B.X));

        for(int i = 0; i < n; i ++)
        {
            A.A[i] = A.S[i] - 'a';
            int j = n - i - 1;
            B.S[j] = A.S[i], B.A[j] = A.A[i];
        }

        A.InitSA(n, 27), B.InitSA(n, 27);
        A.InitHeight(n), B.InitHeight(n);
        A.InitRMQ(n), B.InitRMQ(n), InitRMQ(n);

        int ansR = 1, ansP = INF, sideL, sideR;

        for(int L = 1; L <= n / 2; L ++)
        {
            for(int i = 0; i + L - 1 < n; i += L)
            {
                int suf = A.LCP(i, i + L), pre;
                if(n - i - L < 0 || n - i < 0) pre = 0;
                else pre = B.LCP(n - i, n - i - L);
                int tmpR = (suf + pre) / L + 1;
                
                if(tmpR <= 1) continue ;

                if(tmpR > ansR)
                    ansR = tmpR, ansP = INF;
                if(tmpR == ansR)
                {
                    int r = i - pre + (pre + suf) % L;
                    r = max(r, 0), r = min(r, n - 1);
                    int Rank = RMQ(max(i - pre, 0), r);
                    if(Rank < ansP)
                        ansP = Rank, sideL = A.sa[Rank], sideR = sideL + tmpR * L;
                }
            }
        }

        printf("Case %d: ", ++ Q);

        if(ansR == 1)
        {
            char r = 'z';
            for(int i = 0; i < n; i ++)
                r = min(r, A.S[i]);
            putchar(r), puts("");
            continue ;
        }
        for(int i = sideL; i < sideR; i ++)
            putchar(A.S[i]);
        puts("");

    }
    return 0;
}
