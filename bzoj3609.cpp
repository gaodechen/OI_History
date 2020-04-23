/* #include    <cstdio>
#include    <cstring>
#include    <iostream>

const   int N = 100;

int n, m, a[N];

bool Judge()
{
    int cnt = 0;
    for(int i = 1; i <= n; i ++)
        cnt += a[i];
    if(cnt == 1)
        return false;
    int a_[N];
    memcpy(a_, a, sizeof(a));
    for(int i = 1; i <= n; i ++)
    {
        for(int j = i; j <= n; j ++)
        {
            memcpy(a, a_, sizeof(a_));
            if(i == j)
            {
                if(a[i] < 2 || m < i + i)
                    continue ;
                a[i] -= 2, a[i+i] ++;
                if(!Judge())
                    return true;
            }
            else
            {
                if(!a[i] || !a[j] || i + j > m)
                    continue ;
                a[i] --, a[j] --, a[i+j] ++;
                if(!Judge())
                    return true;
            }
        }
    }
    return false;
}

int main()
{
    freopen("out", "w", stdout);
    for(n = 1; n <= 15; n ++)
    {
        for(m = 1; m <= 10; m ++)
        {
            memset(a, 0, sizeof(a));
            a[1] = n;
            if(Judge())
            {
                // print m, n and m % n
            }
        }
        puts("");
    }
    return 0;
} */

#include <cstdio>

int T, n, m;

int main(int argc, char **argv)
{
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d%d", &n, &m);
        int t = n / m + ((n % m) != 0);
        printf("%d\n", !((n - t) & 1));
    }
    return 0;
}

