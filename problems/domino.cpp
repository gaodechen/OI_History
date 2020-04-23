#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

using namespace	std;
const int N = 10005;
const int MOD = 1000000007;

int n, X, Y, d[N][8];
bool S[N][3], G[N][3];
char buf[N];

inline int BIT(int i)
{
    return G[i][2] | (G[i][1] << 1) | (G[i][0] << 2);
}

inline bool Judge(int s, int i)
{
    return (BIT(i) & s) == 0;
}

inline void U(int &x)
{
    if(X >= MOD) X %= MOD;
    return ;
}

inline int F()
{
    int temp = 0;
    for(int i = 1; i <= n; i ++)
        for(int j = 0; j < 3; j ++)
            temp += G[i][j];
    if((3 * n - temp) & 1) return 0;
    memset(d, 0, sizeof(d));
    {
        d[1][0] = 1;
        int t = G[1][0] + G[1][1] + G[1][2], k = BIT(1);
        if(t == 0)
            d[1][3] = d[1][6] = 1;
        else if(t == 1)
        {
            if(k == 1) d[1][6] = 1;
            else if(k == 4) d[1][3] = 1;
        }
    }
    for(int i = 2; i <= n; i ++)
    {
        for(int s1 = 0, s2; s1 < 8; s1 ++)
        {
            if(!d[i - 1][s1]) continue ;
            s2 = ~(s1 | BIT(i - 1)) & 7;
            if(!Judge(s2, i)) continue ;
            d[i][s2] += d[i - 1][s1], U(d[i][s2]);
            if(s2 == 1 && Judge(7, i))
                d[i][7] += d[i - 1][s1], U(d[i][7]);
            else if(s2 == 4 && Judge(7, i))
                d[i][7] += d[i - 1][s1], U(d[i][7]);
            else if(s2 == 0)
            {
                if(Judge(3, i)) d[i][3] += d[i - 1][s1], U(d[i][3]);
                if(Judge(6, i)) d[i][6] += d[i - 1][s1], U(d[i][6]);
            }
        }
    }
    int s = ~BIT(n) & 7;
    return d[n][s];
}

int main(int argc, char **argv)
{
    freopen("domino.in", "r", stdin);
    freopen("domino.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 0; i < 3; i ++)
    {
        scanf("%s", buf + 1);
        for(int j = 1; j <= n; j ++)
        {
            S[j][i] = !(buf[j] == '.');
            if(buf[j] == 'O') X = j, Y = i;
        }
    }
    if(Y == 1)
    {
        int a = 0, b = 0, c = 0;
        if(X >= 3)
        {
            memcpy(G, S, sizeof(S)), G[X - 1][1] = G[X - 2][1] = 1, a = F();
            if(X + 2 <= n) G[X + 1][1] = G[X + 2][1] = 1, c = F();
        }
        memcpy(G, S, sizeof(S)), G[X + 1][1] = G[X + 2][1] = 1, b = F();
        int ans = a + b - c;
        return printf("%d\n", ans), 0;
    }
    if(Y == 2) for(int i = 1; i <= n; i ++)
        swap(S[i][0], S[i][2]);
    int a, b, c, d, e, f, g;
    a = b = c = d = e = f = g = 0;
    if(X >= 3)
    {
        memcpy(G, S, sizeof(S)), G[X - 1][0] = G[X - 2][0] = 1, a = F();
        G[X][1] = G[X][2] = 1, d = F();
        if(X + 2 <= n) G[X + 1][0] = G[X + 2][0] = 1, g = F();
    }
    if(X + 2 <= n)
    {
        memcpy(G, S, sizeof(S)), G[X + 1][0] = G[X + 2][0] = 1, b = F();
        G[X][1] = G[X][2] = 1, e = F();
    }
    if(X >= 3 && X + 2 <= n)
    {
        memcpy(G, S, sizeof(S)), G[X - 1][0] = G[X - 2][0] = 1;
        G[X + 1][0] = G[X + 2][0] = 1, f = F();
    }
    memcpy(G, S, sizeof(S)), G[X][1] = G[X][2] = 1, c = F();
    int ans = (a + b + c - d - e - f + g) % MOD;
    printf("%d\n", ans);
    return 0;
}

