#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long   data;
const   int N = 500;

int deg[N];
data a[N][N];

data det(int n)
{
    data r = 1;
    for(int i = 1; i < n; i ++)
    {
        for(int j = i + 1; j < n; j ++)
        {
            while(a[j][i])
            {
                data t = a[i][i] / a[j][i];
                for(int k = i; k < n; k ++)
                    a[i][k] -= a[j][k] * t;
                for(int k = i; k < n; k ++)
                    swap(a[i][k], a[j][k]);
                r = -r;
            }
        }
        if(!a[i][i]) return 0;
        r *= a[i][i];
    }
    if(r < 0) r = -r;
    return r;
}

inline void AddEdge(int i, int j)
{
    a[i][j] = a[j][i] = -1;
    deg[i] ++, deg[j] ++;
    return ;
}

int main()
{
    freopen("in", "r", stdin);
    int T, n, k;
    scanf("%d", &T);
    while(T --)
    {
        memset(a, 0, sizeof(a));
        memset(deg, 0, sizeof(deg));
        scanf("%d", &n);
        k = n;
        for(int i = 0; i < n; i ++)
        {
            AddEdge(i, (i + 1) % n);
            AddEdge(i, k);
            AddEdge(k, k + 1);
            AddEdge(k + 1, k + 2);
            AddEdge(k + 2, (i + 1) % n);
            k += 3;
        }
        for(int i = 0; i < k; i ++)
            a[i][i] = deg[i];
        data ans = det(k);
        printf("%lld\n", ans);
    }
    return 0;
}

