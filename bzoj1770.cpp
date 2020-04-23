#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int N = 36;

int n, m, ans, G[N][N];

inline void Gauss()
{
    for(int i = 0, p; i < n; i ++)
    {
        for(p = i; p < n; p ++)
            if(G[p][i] != 0)
                break ;
        if(p != i) for(int j = 0; j <= n; j ++)
            swap(G[p][j], G[i][j]);
        for(int j = 0; j < n; j ++)
            if(i != j && G[j][i])
                for(int k = 0; k <= n; k ++)
                    G[j][k] ^= G[i][k];
    }
    return ;
}

bool f[N];

void DFS(int p, int tot)
{
    if(tot >= ans) return ;
    if(p == -1) return (void) (ans = min(ans, tot));
    if(G[p][p])
    {
        int F = G[p][n];
        for(int i = p + 1; i < n; i ++)
            if(G[p][i])
                F ^= f[i];
        f[p] = F;
        DFS(p - 1, tot + F);
    }
    else
    {
        f[p] = 1, DFS(p - 1, tot + 1);
        f[p] = 0, DFS(p - 1, tot);
    }
    return ;
}

int main(int argc, char **argv)
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i ++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u --, v --, G[u][v] = G[v][u] = 1;
    }
    for(int i = 0; i < n; i ++)
        G[i][n] = G[i][i] = 1;
    Gauss();
    ans = N, DFS(n - 1, 0);
    printf("%d\n", ans);
    return 0;
}

