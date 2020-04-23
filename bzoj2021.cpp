#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 101, M = 1001;

struct Item
{
    int w, h;

    bool operator < (const Item &b) const
    {
        return h < b.h;
    }
} e[N];

inline int pack(int x)
{
    return x * 4 / 5;
}

int n, t, k, f[M];

int main()
{
    scanf("%d%d%d", &n, &t, &k);
    for(int i = 1; i <= n; i ++)
        scanf("%d%d", &e[i].w, &e[i].h);
    sort(e + 1, e + n + 1);
    int cur = n + 1;
    for(int i = 1; i <= n; i ++)
    {
        if(e[i].h >= k)
        {
            cur = i;
            break ;
        }
        for(int j = e[i].h; j <= t; j ++)
            f[j] = max(f[j], f[j-e[i].h] + e[i].w);
    }
    int ans = f[t];
    memset(f, 0, sizeof(f));
    for(int i = 1; i <= n; i ++)
        for(int j = pack(e[i].h); j <= t; j ++)
            f[j] = max(f[j], f[j-pack(e[i].h)] + e[i].w);
    for(int i = cur; i <= n; i ++)
        ans = max(ans, f[t-e[i].h] + e[i].w);
    printf("%d\n", ans);
    return 0;
}

