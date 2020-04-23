#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;

inline int SG(int x, int y)
{
    int t = (1 << 30), r = 31;
    for(int i = 30; i; i --, t >>= 1)
    {
        if(x <= t && y <= t) r = i;
        else
        {
            x -= x > t ? t : 0;
            y -= y > t ? t : 0;
        }
    }
    return x == 1 && y == 1 ? 0 : r;
}

int main(int argc, char **argv)
{
    int T, n;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);
        n >>= 1;
        int sg = 0;
        for(int i = 1; i <= n; i ++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            sg ^= SG(a, b);
        }
        puts(sg ? "YES" : "NO");
    }
    return 0;
}
