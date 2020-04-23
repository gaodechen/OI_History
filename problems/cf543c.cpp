#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

#define     foreach(u)     for(int i = head[u]; i; i = e[i].next)

using	namespace	std;
const   int INF = 0x3f3f3f3f;
typedef pair<int, int> Item;
typedef long long   data;

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

const   int N = 21, M = 1 << 20;

char s[N][N];
int cost[N][N], f[M], state[N][N], w[N][N];

int main(int argc, char **argv)
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int n = in(), m = in();
    for(int i = 0; i < n; i ++)
        scanf("%s", s[i]);
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++)
            cost[i][j] = in();
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < m; j ++)
        {
            int cur = 0;
            for(int k = 0; k < n; k ++)
            {
                if(s[i][j] == s[k][j])
                {
                    state[i][j] |= (1 << k);
                    w[i][j] += cost[k][j];
                    cur = max(cur, cost[k][j]);
                }
            }
            w[i][j] -= cur;
        }
    }
    memset(f, INF, sizeof(f));
    f[0] = 0;
    for(int s = 0; s < (1 << n); s ++)
    {
        if(s == 0) continue ;
        int p = -1;
        for(int i = 0; i < n; i ++) {
            if((s >> i) & 1) {
                p = i; break ;
            }
        }
        for(int i = 0; i < m; i ++)
        {
            f[s] = min(f[s], f[s ^ (1 << p)] + cost[p][i]);
            f[s] = min(f[s], f[s & (s ^ state[p][i])] + w[p][i]);
        }
    }
    printf("%d", f[(1 << n) - 1]);
    return 0;
}
