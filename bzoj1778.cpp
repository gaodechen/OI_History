#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;
const int N = 301;

struct Edge
{
    int v, next;
} e[N * N];

int sig, head[N], deg[N];

inline void AddEdge(int u, int v)
{
    deg[u] ++, e[++ sig].next = head[u];
    e[sig].v = v, head[u] = sig;
    return ;
}

double a[N][N], ans[N], P;

int main(int argc, char **argv)
{
    int n, m, p, q;
    scanf("%d%d%d%d", &n, &m, &p, &q);
    P = (double) p / q;
    for(int i = 0; i < m; i ++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        AddEdge(u, v), AddEdge(v, u);
    }
    for(int u = 1; u <= n; u ++)
    {
        a[u][u] = 1;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            a[u][v] = - (1.0 - P) / deg[v];
        }
    }
    a[1][n + 1] = P;
    for(int i = 1; i <= n; i ++)
    {
        int p = i;
        for(int k = i; k <= n; k ++)
            if(fabs(a[k][i]) > fabs(a[p][i]))
                p = k;
        for(int k = i; k <= n + 1; k ++)
            swap(a[i][k], a[p][k]);
        for(int k = i + 1; k <= n; k ++)
        {
            double tmp = a[k][i] / a[i][i];
            for(int j = i; j <= n + 1; j ++)
                a[k][j] -= a[i][j] * tmp;
        }
    }
    for(int i = n; i; i --)
    {
        for(int j = i + 1; j <= n; j ++)
            a[i][n + 1] -= a[i][j] * ans[j];
        ans[i] = a[i][n + 1] / a[i][i];
    }
    for(int i = 1; i <= n; i ++)
        printf("%.9lf\n", ans[i]);
    return 0;
}
