#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 2e3 + 5;

int n, m, ans, a[N][N];
int f[N][N], h[N][N], stack[N];

inline int Update(int *H)
{
    int top = 0, r = 0;
    H[m+1] = -1;
    for(int i = 1; i <= m + 1; i ++)
    {
        while(top && H[stack[top]] > H[i])
        {
            r = max((i - stack[top-1] - 1) * H[stack[top]], r);
            top --;
        }
        stack[++top] = i;
    }
    return r;
}

inline void Construct()
{
    memset(h, 0, sizeof(h));
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            if(a[i][j])
                h[i][j] = h[i-1][j] + 1;
    for(int i = 1; i <= n; i ++)
        ans = max(ans, Update(h[i]));
    return ;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            scanf("%d", &a[i][j]);
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= m; j ++)
        {
            int tmp = min(min(f[i-1][j], f[i][j-1]),f[i-1][j-1]);
            if(a[i][j] != a[i-1][j] && a[i][j] != a[i][j-1])
                f[i][j] = tmp + 1;
            else
                f[i][j] = 1;
            ans = max(ans, f[i][j]);
        }
    }
    printf("%d\n", ans * ans);
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= m; j ++)
        {
            if(((i & 1) == (j & 1) && a[i][j]) || ((i & 1) != (j & 1) && !a[i][j]))
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    }
    ans = 0;
    Construct();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            a[i][j] = !a[i][j];
    Construct();
    printf("%d\n", ans);
    return 0;
}
