#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1005, INF = 0x3f3f3f3f;

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
        c = getchar();
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

inline void InitMin(int *f, int *a, int n, int k)
{
    memset(f, 127, sizeof(int) * N);
    int head = 1, tail = 0, q[N];
    for(int i = 1; i <= n; i ++)
    {
        while(head <= tail && a[q[tail]] >= a[i])
            tail --;
        q[++tail] = i;
        while(head <= tail && q[head] < i - k + 1)
            head ++;
        f[i] = a[q[head]];
    }
    return ;
}

inline void InitMax(int *f, int *a, int n, int k)
{
    memset(f, 128, sizeof(int) * N);
    int head = 1, tail = 0, q[N];
    for(int i = 1; i <= n; i ++)
    {
        while(head <= tail && a[q[tail]] <= a[i])
            tail --;
        q[++tail] = i;
        while(head <= tail && q[head] < i - k + 1)
            head ++;
        f[i] = a[q[head]];
    }
    return ;
}

int a[N][N], f[N][N], g[N][N], x[N][N], y[N][N];

int main()
{
    int n = in(), m = in(), k = in();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            a[i][j] = in();
    for(int i = 1; i <= n; i ++)
    {
        InitMin(f[i], a[i], m, k);
        InitMax(g[i], a[i], m, k);
    }
    int head, tail, q[N];
    for(int j = k; j <= m; j ++)
    {
        head = 1, tail = 0;
        for(int i = 1; i <= n; i ++)
        {
            while(head <= tail && f[q[tail]][j] >= f[i][j])
                tail --;
            q[++tail] = i;
            while(head <= tail && q[head] < i - k + 1)
                head ++;
            x[i][j] = f[q[head]][j];
        }
    }
    for(int j = k; j <= m; j ++)
    {
        head = 1, tail = 0;
        for(int i = 1; i <= n; i ++)
        {
            while(head <= tail && g[q[tail]][j] <= g[i][j])
                tail --;
            q[++tail] = i;
            while(head <= tail && q[head] < i - k + 1)
                head ++;
            y[i][j] = g[q[head]][j];
        }
    }
    int ans = INF;
    for(int i = k; i <= n; i ++)
        for(int j = k; j <= m; j ++)
            ans = min(ans, y[i][j] - x[i][j]);
    printf("%d\n", ans);
    return 0;
}
