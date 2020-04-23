#include    <cstdio>
#include    <cstring>
#include    <iostream>

#define     A       node[p].lson
#define     B       node[p].rson

using   namespace   std;
const   int MOD = 1000000007;
const   int N = 760, M = 600000;

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

struct Node
{
    int lson, rson, val;
} node[M*10];

inline void f(int &a, int x)
{
    a += x;
    if(a < 0)
        a += MOD;
    if(a >= MOD)
        a %= MOD;
    return ;
}

int root[N*N], row[N], sum[N][N];
int n, m, size, a[N][N], d[N][N];

void Modify(int &p, int l, int r, int k, int x)
{
    if(p == 0)
        p = ++ size;
    if(l == r)
        return (void) (f(node[p].val, x));
    int mid = (l + r) >> 1;
    if(k <= mid)
        Modify(A, l, mid, k, x);
    else
        Modify(B, mid + 1, r, k, x);
    f(node[p].val = 0, node[A].val + node[B].val);
    return ;
}

int Query(int p, int l, int r, int L, int R)
{
    if(!p || (L <= l && r <= R) || !node[p].val)
        return node[p].val;
    int mid = (l + r) >> 1, ans = 0;
    if(L <= mid)
        f(ans, Query(A, l, mid, L, R));
    if(R > mid)
        f(ans, Query(B, mid + 1, r, L, R));
    return ans;
}

int main()
{
    scanf("%d%d%*d", &n, &m);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            scanf("%d", &a[i][j]);
    for(int j = 1; j <= m; j ++)
        sum[1][j] = 1;
    Modify(root[a[1][1]], 1, m, 1, d[1][1] = 1);
    for(int i = 2; i <= n; i ++)
    {
        for(int j = m; j >= 1; j --)
        {
            int x = Query(root[a[i][j]], 1, m, 1, j - 1);
            f(d[i][j], sum[i-1][j-1] - x);
            Modify(root[a[i][j]], 1, m, j, d[i][j]);
        }
        for(int j = 1; j <= m; j ++)
        {
            f(row[j] = 0, row[j-1] + d[i][j]);
            f(sum[i][j], sum[i-1][j] + row[j]);
        }
    }
    printf("%d\n", d[n][m]);
    return 0;
}

