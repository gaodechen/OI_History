#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

#define     inc(i, n)       for(int i = 1; i <= n; i ++)
#define     dec(i, n)       for(int i = n; i >= 1; i --)
#define     foreach(u)      for(int i = head[u]; i; i = e[i].next)

using namespace	std;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> Item;
typedef unsigned long long data;

inline int Bit(int s, int i) {return (1 << i) & s;}

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
        if((c = getchar()) == '-')
            f = 0;
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

/*
   struct Edge {int v, next;};

   int sig, head[N];

   inline void AddEdge(int u, int v)
   {
   e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
   }
   */

const int M = 1 << 13, N = 101;

bool G[13][13];
data f[13][M];
int n, m, q, lowbit[M], a[N], b[N], c[N];
vector<Item> e;

inline bool Check1(int u, int mask)
{
    for(int i = 0; i < q; i ++)
    {
        if(a[i] == u && Bit(mask, b[i]) && c[i] != u)
            return false;
        if(Bit(mask, a[i]) && b[i] == u && c[i] != u)
            return false;
    }
    return true;
}

inline bool Check2(int m1, int m2, int u)
{
    for(int i = 0; i < q; i ++)
    {
        if(Bit(m1, a[i]) && Bit(m2, b[i]) && c[i] != u)
            return false;
        if(Bit(m2, a[i]) && Bit(m1, b[i]) && c[i] != u)
            return false;
    }
    for(int i = 0; i < (int) e.size(); i ++)
    {
        int u = e[i].first, v = e[i].second;
        if(Bit(m1, u) && Bit(m2, v)) return false;
        if(Bit(m1, v) && Bit(m2, u)) return false;
    }
    return true;
}

inline bool Check3(int u, int mask)
{
    for(int i = 0; i < 13; i ++)
        if(Bit(mask, i) && G[u][i]) return false;
    return true;
}

int main(int argc, char **argv)
{
#define LOCAL
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    n = in(), m = in(), q = in();
    for(int i = 0; i < M; i ++)
    {
        for(int j = 0; j < 13; j ++) if(Bit(i, j))
        {
            lowbit[i] = j;
            break ;
        }
    }
    for(int i = 0; i < m; i ++)
    {
        int u = in() - 1, v = in() - 1;
        G[u][v] = G[v][u] = 1;
        e.push_back(Item(u, v));
    }
    for(int i = 0; i < q; i ++)
    {
        a[i] = in(), b[i] = in(), c[i] = in();
        a[i] --, b[i] --, c[i] --;
    }
    for(int mask = 0; mask < (1 << n); mask ++)
    {
        for(int i = 0; i < 13; i ++) if(Bit(mask, i))
        {
            int mask_ = mask & (~(1 << i));
            if(!Check1(i, mask)) continue ;
            if(mask_ == 0)
            {
                f[i][mask] = 1;
                continue ;
            }
            for(int mask1 = mask_; mask1; mask1 = mask_ & (mask1 - 1))
            {
                if(!Bit(mask1, lowbit[mask_])) continue ;
                int mask2 = mask_ ^ mask1;
                if(!Check2(mask1, mask2, i)) continue ;
                for(int j = 0; j < 13; j ++)
                    if(Bit(mask1, j) && Check3(i, mask1 & (~(1 << j))))
                        f[i][mask] += f[j][mask1] * f[i][mask2 | (1 << i)];
            }
        }
    }
    cout << f[0][(1 << n) - 1];
    return 0;
}
