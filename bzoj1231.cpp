#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;

inline unsigned long long ABS(int x)
{
    return x > 0 ? x : -x;
}

int n, k, a[17];
unsigned long long f[17][(1 << 16)];

int main(int argc, char **argv)
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    for(int i = 1; i <= n; i ++)
        f[i][1 << (i - 1)] = 1;
    for(int s = 1; s < (1 << 16); s ++)
        for(int i = 1; i <= n; i ++)
            if(s & (1 << (i - 1)))
                for(int j = 1; j <= n; j ++)
                    if(!(s & (1 << (j - 1))) && ABS(a[i] - a[j]) > k)
                        f[j][s | (1 << (j - 1))] += f[i][s];
    unsigned long long r = 0;
    for(int i = 1; i <= n; i ++)
        r += f[i][(1 << n) - 1];
    cout << r << endl;
    return 0;
}
